//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Common GPA Implementation
//==============================================================================

#include <ADLUtil.h>

#include "GPAImplementor.h"
#include "GPAUniqueObject.h"
#include "Logging.h"

#if defined(WIN32)
    #include "Adapter.h"
#endif

GPAImplementor::GPAImplementor()
    : m_isInitialized(false)
{

}

GPA_Status GPAImplementor::Initialize()
{
    GPA_Status gpaStatus = GPA_STATUS_ERROR_GPA_ALREADY_INITIALIZED;

    if (!m_isInitialized)
    {
        m_isInitialized = true;
        gpaStatus = GPA_STATUS_OK;
    }

    return gpaStatus;
}

GPA_Status GPAImplementor::Destroy()
{
    GPA_Status gpaStatus = GPA_STATUS_ERROR_GPA_NOT_INITIALIZED;

    if (m_isInitialized)
    {
        m_isInitialized = false;
        gpaStatus = GPA_STATUS_OK;
    }

    return gpaStatus;
}

GPA_Status GPAImplementor::OpenContext(void* pContextInfo,
                                       GPA_OpenContextFlags flags,
                                       GPA_ContextId* pGpaContextId)
{
    GPA_Status gpaStatus = GPA_STATUS_OK;

    std::lock_guard<std::mutex> lock(m_deviceGpaContextMapMutex);

    if (!DoesContextInfoExist(pContextInfo))
    {
        GPA_HWInfo hwInfo;
        if (GPA_STATUS_OK == IsDeviceSupported(pContextInfo, &hwInfo))
        {
            IGPAContext* pNewGPAContext = nullptr;
            pNewGPAContext = OpenAPIContext(pContextInfo, hwInfo, flags);

            if (nullptr != pNewGPAContext)
            {
                *pGpaContextId =
                    reinterpret_cast<GPA_ContextId>(GPAUniqueObjectManager::Instance()->CreateObject(pNewGPAContext));
                m_appContextInfoGpaContextMap.insert(GPADeviceIdentifierGPAContextPair(GetDeviceIdentifierFromContextInfo(pContextInfo), pNewGPAContext));
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
        GPA_LogError("Device not supported.");
        gpaStatus = GPA_STATUS_ERROR_FAILED;
    }

    return gpaStatus;
}

GPA_Status GPAImplementor::CloseContext(GPA_ContextId gpaContextId)
{
    GPA_Status gpaStatus = GPA_STATUS_OK;

    if (GPAObjectType::GPA_OBJECT_TYPE_CONTEXT == gpaContextId->ObjectType() &&
        gpaContextId->Object()->GetAPIType() == GetAPIType())
    {
        std::lock_guard<std::mutex> lock(m_deviceGpaContextMapMutex);

        IGPAContext* pGpaContext = gpaContextId->Object();

        // find the context
        bool isFound = false;
        GPADeviceIdentifierGPAContextMap::iterator foundIter = m_appContextInfoGpaContextMap.end();

        for (auto iter = m_appContextInfoGpaContextMap.begin();
            !isFound && iter != m_appContextInfoGpaContextMap.end(); ++iter)
        {
            if (iter->second == pGpaContext)
            {
                isFound = true;
                foundIter = iter;
            }
        }

        if (isFound)
        {
            if (CloseAPIContext(foundIter->first, pGpaContext))
            {
                m_appContextInfoGpaContextMap.erase(foundIter);
                GPAUniqueObjectManager::Instance()->DeleteObject(gpaContextId);
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
        if (GPAObjectType::GPA_OBJECT_TYPE_CONTEXT == contextId->ObjectType() &&
            GetAPIType() != contextId->Object()->GetAPIType())
        {
            GPA_LogError("Invalid Parameter.");
            return false;
        }

        contextFound = GPAUniqueObjectManager::Instance()->DoesExist(contextId);
    }

    return contextFound;
}

bool GPAImplementor::DoesContextInfoExist(GPAContextInfoPtr pContextInfo) const
{
    return m_appContextInfoGpaContextMap.find(GetDeviceIdentifierFromContextInfo(pContextInfo)) != m_appContextInfoGpaContextMap.cend();
}

GPA_Status GPAImplementor::IsDeviceSupported(GPAContextInfoPtr pContextInfo, GPA_HWInfo* pHwInfo) const
{
    bool foundMatchingHWInfo = false;
    AsicInfoList asicInfoList;
    GPA_HWInfo apiHwInfo;

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

    if (!foundMatchingHWInfo) // ADL will not be available on a clean system that has never had the AMD driver installed
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

                if (GPA_STATUS_OK == CompareHwInfo(apiHwInfo, asicHwInfo))
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

#endif // WIN32

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

    // Give the API-specific implementation a chance to verify that the hardware is supported.
    GPA_Status status = VerifyAPIHwSupport(pContextInfo, apiHwInfo) ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;

    if(GPA_STATUS_OK == status)
    {
        *pHwInfo = apiHwInfo;
    }

    return status;
}

bool GPAImplementor::CompareHwInfo(const GPA_HWInfo& first, const GPA_HWInfo& second) const
{
    return first == second;
}
