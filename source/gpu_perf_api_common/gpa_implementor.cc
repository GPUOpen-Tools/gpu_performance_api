//==============================================================================
// Copyright (c) 2017-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Common GPA Implementation
//==============================================================================

#include <ADLUtil.h>

#include "gpa_implementor.h"
#include "gpa_unique_object.h"
#include "logging.h"
#include "gpa_context_counter_mediator.h"

#if defined(WIN32)
#include "adapter.h"
#endif

GPAImplementor::GPAImplementor()
    : m_isInitialized(false)
    , m_initFlags(GPA_INITIALIZE_DEFAULT_BIT)
{
}

GPA_Status GPAImplementor::Initialize(GPA_InitializeFlags flags)
{
    m_initFlags = flags;

    GPA_Status gpaStatus = GPA_STATUS_ERROR_GPA_ALREADY_INITIALIZED;

    if (GPA_INITIALIZE_DEFAULT_BIT != flags && GPA_INITIALIZE_SIMULTANEOUS_QUEUES_ENABLE_BIT != flags)
    {
        GPA_LogError("Invalid flags passed to GPA_Initialize.");
        gpaStatus = GPA_STATUS_ERROR_INVALID_PARAMETER;
    }
    else
    {
        if (!m_isInitialized)
        {
            m_isInitialized                  = true;
            GPAContextCounterMediator* pTemp = GPAContextCounterMediator::Instance();

            if (nullptr == pTemp)
            {
                gpaStatus = GPA_STATUS_ERROR_FAILED;
            }
            else
            {
                gpaStatus = GPA_STATUS_OK;
            }
        }
    }

    return gpaStatus;
}

GPA_Status GPAImplementor::Destroy()
{
    GPA_Status gpaStatus = GPA_STATUS_ERROR_GPA_NOT_INITIALIZED;

    if (m_isInitialized)
    {
        m_isInitialized = false;
        GPAContextCounterMediator::DeleteInstance();
        gpaStatus = GPA_STATUS_OK;
    }

    return gpaStatus;
}

GPA_Status GPAImplementor::OpenContext(void* pContext, GPA_OpenContextFlags flags, GPA_ContextId* pContextId)
{
    // validate that only a single clock mode is specified
    unsigned int numClockModes = 0;

    if (GPA_OPENCONTEXT_CLOCK_MODE_NONE_BIT & flags)
    {
        numClockModes++;
    }

    if (GPA_OPENCONTEXT_CLOCK_MODE_PEAK_BIT & flags)
    {
        numClockModes++;
    }

    if (GPA_OPENCONTEXT_CLOCK_MODE_MIN_MEMORY_BIT & flags)
    {
        numClockModes++;
    }

    if (GPA_OPENCONTEXT_CLOCK_MODE_MIN_ENGINE_BIT & flags)
    {
        numClockModes++;
    }

    if (1 < numClockModes)
    {
        GPA_LogError("More than one clock mode specified.");
        return GPA_STATUS_ERROR_INVALID_PARAMETER;
    }

    GPA_Status gpaStatus = GPA_STATUS_OK;

    std::lock_guard<std::mutex> lock(m_deviceGpaContextMapMutex);

    if (!DoesContextInfoExist(pContext))
    {
        GPA_HWInfo hwInfo;

        if (GPA_STATUS_OK == IsDeviceSupported(pContext, &hwInfo))
        {
            IGPAContext* pNewGPAContext = nullptr;
            pNewGPAContext              = OpenAPIContext(pContext, hwInfo, flags);

            if (nullptr != pNewGPAContext)
            {
                *pContextId = reinterpret_cast<GPA_ContextId>(GPAUniqueObjectManager::Instance()->CreateObject(pNewGPAContext));
                m_appContextInfoGpaContextMap.insert(GPADeviceIdentifierGPAContextPair(GetDeviceIdentifierFromContextInfo(pContext), pNewGPAContext));
            }
            else
            {
                GPA_LogError("Failed to open API-specific GPA Context.");
                gpaStatus = GPA_STATUS_ERROR_FAILED;
            }
        }
        else
        {
            GPA_LogError("Device not supported.");
            gpaStatus = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
        }
    }
    else
    {
        GPA_LogError("Context is already open.");
        gpaStatus = GPA_STATUS_ERROR_CONTEXT_ALREADY_OPEN;
    }

    return gpaStatus;
}

GPA_Status GPAImplementor::CloseContext(GPA_ContextId contextId)
{
    GPA_Status gpaStatus = GPA_STATUS_OK;

    if (GPAObjectType::GPA_OBJECT_TYPE_CONTEXT == contextId->ObjectType() && contextId->Object()->GetAPIType() == GetAPIType())
    {
        std::lock_guard<std::mutex> lock(m_deviceGpaContextMapMutex);

        IGPAContext* pContext = contextId->Object();

        // find the context
        bool                                       isFound   = false;
        GPADeviceIdentifierGPAContextMap::iterator foundIter = m_appContextInfoGpaContextMap.end();

        for (auto iter = m_appContextInfoGpaContextMap.begin(); !isFound && iter != m_appContextInfoGpaContextMap.end(); ++iter)
        {
            if (iter->second == pContext)
            {
                isFound   = true;
                foundIter = iter;
            }
        }

        if (isFound)
        {
            if (CloseAPIContext(foundIter->first, pContext))
            {
                m_appContextInfoGpaContextMap.erase(foundIter);
                GPAUniqueObjectManager::Instance()->DeleteObject(contextId);
            }
            else
            {
                GPA_LogDebugError("Unable to close the API-level GPA context.");
                gpaStatus = GPA_STATUS_ERROR_FAILED;
            }
        }
        else
        {
            GPA_LogError("Unable to close the GPAContext: context not found.");
            gpaStatus = GPA_STATUS_ERROR_INVALID_PARAMETER;
        }
    }
    else
    {
        GPA_LogError("Invalid context supplied.");
        gpaStatus = GPA_STATUS_ERROR_INVALID_PARAMETER;
    }

    return gpaStatus;
}

GPAObjectType GPAImplementor::ObjectType() const
{
    return GPAObjectType::GPA_OBJECT_TYPE_IMPLEMENTATION;
}

bool GPAImplementor::DoesContextExist(GPA_ContextId contextId) const
{
    bool contextFound = false;

    if (nullptr != contextId)
    {
        contextFound = GPAUniqueObjectManager::Instance()->DoesExist(contextId);

        if (contextFound && GPAObjectType::GPA_OBJECT_TYPE_CONTEXT == contextId->ObjectType() && GetAPIType() == contextId->Object()->GetAPIType())
        {
            contextFound = true;
        }
    }

    return contextFound;
}

bool GPAImplementor::DoesSessionExist(GPA_SessionId sessionId) const
{
    bool sessionFound = false;

    if (nullptr != sessionId)
    {
        sessionFound = GPAUniqueObjectManager::Instance()->DoesExist(sessionId);

        if (sessionFound && GPAObjectType::GPA_OBJECT_TYPE_SESSION == sessionId->ObjectType())
        {
            sessionFound = true;
        }
    }

    return sessionFound;
}

bool GPAImplementor::DoesCommandListExist(GPA_CommandListId commandListId) const
{
    bool commandListFound = false;

    if (nullptr != commandListId)
    {
        commandListFound = GPAUniqueObjectManager::Instance()->DoesExist(commandListId);

        if (commandListFound && GPAObjectType::GPA_OBJECT_TYPE_COMMAND_LIST == commandListId->ObjectType())
        {
            commandListFound = true;
        }
    }

    return commandListFound;
}

GPA_InitializeFlags GPAImplementor::GetInitializeFlags() const
{
    return m_initFlags;
}

bool GPAImplementor::IsCommandListRequired() const
{
    return false;
}

bool GPAImplementor::IsContinueSampleOnCommandListSupported() const
{
    return false;
}

bool GPAImplementor::IsCopySecondarySampleSupported() const
{
    return false;
}

bool GPAImplementor::DoesContextInfoExist(GPAContextInfoPtr pContextInfo) const
{
    return m_appContextInfoGpaContextMap.find(GetDeviceIdentifierFromContextInfo(pContextInfo)) != m_appContextInfoGpaContextMap.cend();
}

bool GPAImplementor::IsDeviceGenerationSupported(const GPA_HWInfo& hwInfo) const
{
    GDT_HW_GENERATION deviceGeneration = GDT_HW_GENERATION_NONE;
    if (hwInfo.GetHWGeneration(deviceGeneration))
    {
        if (deviceGeneration >= GDT_HW_GENERATION_VOLCANICISLAND)
        {
            return true;
        }
    }

    return false;
}

GPA_Status GPAImplementor::IsDeviceSupported(GPAContextInfoPtr pContextInfo, GPA_HWInfo* pHwInfo) const
{
    bool         foundMatchingHWInfo = false;
    AsicInfoList asicInfoList;
    GPA_HWInfo   apiHwInfo;

    if (!GetHwInfoFromAPI(pContextInfo, apiHwInfo))
    {
        GPA_LogError("Unable to get hardware information from the API.");
        return GPA_STATUS_ERROR_FAILED;
    }

    if (apiHwInfo.IsAMD())
    {
        AMDTADLUtils::Instance()->GetAsicInfoList(asicInfoList);
        GPA_HWInfo asicHwInfo;

        // make sure there are available asics for AMD card.
        // In case there is no AMD driver, we output a message.
        if (asicInfoList.empty())
        {
            GPA_LogMessage("Cannot get asicInfoList from ADL.");
        }

        for (auto asicInfo : asicInfoList)
        {
            asicHwInfo.SetVendorID(asicInfo.vendorID);
            asicHwInfo.SetDeviceName(asicInfo.adapterName.c_str());
            asicHwInfo.SetDeviceID(asicInfo.deviceID);
            asicHwInfo.SetRevisionID(asicInfo.revID);
            asicHwInfo.SetGpuIndex(asicInfo.gpuIndex);
            asicHwInfo.UpdateDeviceInfoBasedOnDeviceID();

            if (CompareHwInfo(apiHwInfo, asicHwInfo))
            {
                gpa_uint32 apiRevId = 0;

                // make sure revision id is set correctly based on the actual hardware
                if (apiHwInfo.GetRevisionID(apiRevId) && REVISION_ID_ANY == apiRevId)
                {
                    apiHwInfo.SetRevisionID(asicInfo.revID);
                }

                apiHwInfo.UpdateDeviceInfoBasedOnDeviceID();

                // this device matches what the application is running on, so break from the loop.
                foundMatchingHWInfo = true;
                break;
            }
        }
    }

#if defined(WIN32)

    if (!foundMatchingHWInfo)  // ADL will not be available on a clean system that has never had the AMD driver installed
    {
        Adapter adapter;
        asicInfoList.clear();

        if (adapter.getAsicInfoList(asicInfoList))
        {
            for (auto asicInfo : asicInfoList)
            {
                GPA_HWInfo asicHwInfo;
                asicHwInfo.SetVendorID(asicInfo.vendorID);
                asicHwInfo.SetDeviceName(asicInfo.adapterName.c_str());
                asicHwInfo.SetDeviceID(asicInfo.deviceID);
                asicHwInfo.SetRevisionID(asicInfo.revID);

                if (NVIDIA_VENDOR_ID == asicInfo.vendorID)
                {
                    asicHwInfo.SetHWGeneration(GDT_HW_GENERATION_NVIDIA);
                }
                else if (INTEL_VENDOR_ID == asicInfo.vendorID)
                {
                    asicHwInfo.SetHWGeneration(GDT_HW_GENERATION_INTEL);
                }
                else
                {
                    // this call makes sure the hw generation is set correctly
                    asicHwInfo.UpdateDeviceInfoBasedOnDeviceID();
                }

                if (CompareHwInfo(apiHwInfo, asicHwInfo))
                {
                    gpa_uint32 apiRevId = 0;

                    // make sure revision id is set correctly based on the actual hardware
                    if (apiHwInfo.GetRevisionID(apiRevId) && REVISION_ID_ANY == apiRevId)
                    {
                        apiHwInfo.SetRevisionID(asicInfo.revID);
                    }

                    apiHwInfo.UpdateDeviceInfoBasedOnDeviceID();

                    // this device matches what the application is running on, so break from the loop.
                    foundMatchingHWInfo = true;
                    break;
                }
            }
        }
        else
        {
            GPA_LogMessage("Unable to get asic info from the Adapter.");
        }
    }

#endif  // WIN32

    if (!foundMatchingHWInfo)
    {
        // This code path is for systems where ADL is not available. ADL is not available on ROCm systems as well as on amdgpu systems.
        // API specific hardware information mostly gets basic information (namely just needs to get VendorID and DeviceID), so we need to update
        // the device info with additional information that we store per-deviceID.
        bool deviceInfoOk = apiHwInfo.UpdateDeviceInfoBasedOnDeviceID();

        if (!deviceInfoOk)
        {
            // If this fails, then the hardware must not be supported because we don't know enough about it
            GPA_LogError("Cannot update device information.");
            return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
        }
    }

    // Check we support the device generation
    if (!IsDeviceGenerationSupported(apiHwInfo))
    {
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    // Give the API-specific implementation a chance to verify that the hardware is supported.
    GPA_Status status = VerifyAPIHwSupport(pContextInfo, apiHwInfo) ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;

    if (GPA_STATUS_OK == status)
    {
        *pHwInfo = apiHwInfo;
    }

    return status;
}

bool GPAImplementor::CompareHwInfo(const GPA_HWInfo& first, const GPA_HWInfo& second) const
{
    return first == second;
}
