//==============================================================================
// Copyright (c) 2010-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  This file contains the main entrypoints into GPA
//==============================================================================

/// macro to mark a function for exporting
#ifdef _LINUX
    #define GPALIB_DECL extern "C"
#else
    #define GPALIB_DECL extern "C" __declspec( dllexport )
#endif

#include "GPUPerfAPI-Private.h"

#include "GPUPerfAPIImp.h"
#include <string.h>
#include <assert.h>
#include <sstream>
#include <cstdio>
#include <map>

#include "Logging.h"
#include "GPAProfiler.h"

#include "ADLUtil.h"
#if defined(WIN32)
    #include "Adapter.h"
    #include "..\GPUPerfAPICounterGenerator\GPASwCounterManager.h"
#endif // WIN32

vector< GPA_ContextState* > g_Contexts;        ///< list of open contexts
GPA_ContextState* g_pCurrentContext = nullptr; ///< pointer to current context

//-----------------------------------------------------------------------------
/// Lookup context
/// \param pContext the context to lookup
/// \return the found ContextState or nullptr if not found
GPA_ContextState* lookupContext(void* pContext)
{
    for (std::vector<GPA_ContextState*>::iterator contextIter = g_Contexts.begin(); contextIter != g_Contexts.end(); ++contextIter)
    {
        if ((*contextIter)->m_pContext == pContext)
        {
            return *contextIter;
        }
    }

    return nullptr;
}

//-----------------------------------------------------------------------------
/// Lookup context state
/// \param pContextState the context to lookup
/// \return the index of the found ContextState or -1 if not found
int lookupContextState(GPA_ContextState* pContextState)
{
    int contextCount = static_cast<int>(g_Contexts.size());

    for (int i = 0 ; i < contextCount ; i++)
    {
        if (g_Contexts[i] == pContextState)
        {
            return i;
        }
    }

    return -1;
}

//-----------------------------------------------------------------------------
/// Local function which first tries to acquire device information
/// from the supplied hwInfo, which uses ADL to get the data.
/// If this method fails for any reason, this function will fall back
/// to having the API-specific implementation query the hw info.
/// If either of these methods succeeds, the API-specific implementation
/// is asked to verify support of the hardware, if not, then an error
/// code is returned.
/// \param pApiContext the context pointer supplied by the API
/// \param pHwInfo a pointer to the hwInfo structure that must be
/// filled in.
/// \return GPA_STATUS_OK if hardware is supported, an error status otherwise.
GPA_Status GetHWInfo(void* pApiContext, GPA_HWInfo* pHwInfo)
{
    if (nullptr == pHwInfo)
    {
        GPA_LogDebugError("Parameter 'pHwInfo' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    bool foundMatchingHWInfo = false;
    AsicInfoList asicInfoList;
    GPA_IMP_GetHWInfo(pApiContext, pHwInfo);

    if (pHwInfo->IsAMD())
    {
        AMDTADLUtils::Instance()->GetAsicInfoList(asicInfoList);

        // make sure there are available asics for AMD card.
        // In case there is no AMD driver, we output a message.
        if (0 == asicInfoList.size())
        {
            GPA_LogMessage("Cannot get asicInfoList from ADL.");
        }

        for (auto asicInfo : asicInfoList)
        {
            pHwInfo->SetVendorID(asicInfo.vendorID);
            pHwInfo->SetDeviceName(asicInfo.adapterName.c_str());
            pHwInfo->SetDeviceID(asicInfo.deviceID);
            pHwInfo->SetRevisionID(asicInfo.revID);
            pHwInfo->SetGpuIndex(asicInfo.gpuIndex);
            pHwInfo->UpdateDeviceInfoBasedOnDeviceID();

            if (GPA_IMP_CompareHWInfo(pApiContext, pHwInfo) == GPA_STATUS_OK)
            {
                // this device matches what the application is running on, so break from the loop.
                foundMatchingHWInfo = true;
                break;
            }
        }
    }

#if defined(WIN32)

    if (false == foundMatchingHWInfo) //NO ADL exist for clean system that has never had the AMD driver installed
    {
        Adapter adapter;
        asicInfoList.clear();

        if (adapter.getAsicInfoList(asicInfoList))
        {
            for (auto asicInfo : asicInfoList)
            {
                if (NVIDIA_VENDOR_ID == asicInfo.vendorID || INTEL_VENDOR_ID == asicInfo.vendorID) // support non-AMD use case (DX and GL only)
                {
                    pHwInfo->SetVendorID(asicInfo.vendorID);
                    pHwInfo->SetDeviceName(asicInfo.adapterName.c_str());
                    pHwInfo->SetDeviceID(asicInfo.deviceID);
                    pHwInfo->SetRevisionID(asicInfo.revID);

                    if (NVIDIA_VENDOR_ID == asicInfo.vendorID)
                    {
                        pHwInfo->SetHWGeneration(GDT_HW_GENERATION_NVIDIA);
                    }
                    else if (INTEL_VENDOR_ID == asicInfo.vendorID)
                    {
                        pHwInfo->SetHWGeneration(GDT_HW_GENERATION_INTEL);
                    }

                    if (GPA_STATUS_OK == GPA_IMP_CompareHWInfo(pApiContext, pHwInfo))
                    {
                        // this device matches what the application is running on, so break from the loop.
                        foundMatchingHWInfo = true;
                        break;
                    }
                }
            }
        }
        else
        {
            GPA_LogMessage("QueryAdapterInfo() failed.");
        }
    }

#endif // WIN32

    if (foundMatchingHWInfo == false)
    {
        // NOTE: we don't expect to have to take this code path, it is a fall back, as we expect ADL to be available on machines.
        // Hopefully in the future we can remove this path. One potential issue is that we need to make sure we expose the counters
        // for the device being used.
        GPA_Status status = GPA_IMP_GetHWInfo(pApiContext, pHwInfo);

        if (status != GPA_STATUS_OK)
        {
            // if this is not GPA_STATUS_OK, then the API-specific implementation could not get the hardware information,
            // so there is no way to know if GPA should support this device.
            GPA_LogError("Cannot identify graphics hardware.");
            return status;
        }

        // GPA_IMP_GetHWInfo mostly gets basic information (namely just needs to get VendorID and DeviceID), so we need to update
        // the device info with additional information that we store per-deviceID.
        bool deviceInfoOk = pHwInfo->UpdateDeviceInfoBasedOnDeviceID();

        if (deviceInfoOk == false)
        {
            // If this fails, then the hardware must not be supported because we don't know enough about it
            GPA_LogError("Cannot update device information.");
            return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
        }
    }

    // Give the API-specific implementation a chance to verify that the hardware is supported.
    GPA_Status status = GPA_IMP_VerifyHWSupport(pApiContext, pHwInfo);

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_RegisterLoggingCallback(GPA_Logging_Type loggingType, GPA_LoggingCallbackPtrType pCallbackFuncPtr)
{
    if (nullptr == pCallbackFuncPtr &&
        loggingType != GPA_LOGGING_NONE)
    {
        GPA_LogDebugError("Parameter 'pCallbackFuncPtr' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    g_loggerSingleton.SetLoggingCallback(loggingType, pCallbackFuncPtr);

    GPA_Log(GPA_LOG_MESSAGE, "Logging callback registered successfully.");
    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
#ifdef AMDT_INTERNAL
GPALIB_DECL GPA_Status GPA_RegisterLoggingDebugCallback(GPA_Log_Debug_Type loggingType, GPA_LoggingDebugCallbackPtrType pCallbackFuncPtr)
{
    if (nullptr == pCallbackFuncPtr &&
        loggingType != GPA_LOG_NONE)
    {
        GPA_LogDebugError("Parameter 'pCallbackFuncPtr' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    g_loggerSingleton.SetLoggingDebugCallback(loggingType, pCallbackFuncPtr);

    GPA_Log(GPA_LOG_DEBUG_MESSAGE, "Debug logging callback registered successfully.");
    return GPA_STATUS_OK;
}
#endif // AMDT_INTERNAL

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_Initialize()
{
    PROFILE_FUNCTION(GPA_Initialize);
    TRACE_FUNCTION(GPA_Initialize);

    GPA_Status retStatus = GPA_IMP_Initialize();

    return retStatus;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_Destroy()
{
    PROFILE_FUNCTION(GPA_Destroy);
    TRACE_FUNCTION(GPA_Destroy);

    GPA_Status retStatus = GPA_IMP_Destroy();

    return retStatus;
}

//-----------------------------------------------------------------------------
// Implementation API guaranteed that no functions called on context unless it's open
GPALIB_DECL GPA_Status GPA_OpenContext(void* pContext)
{
    PROFILE_FUNCTION(GPA_OpenContext);
    TRACE_FUNCTION(GPA_OpenContext);

    // sets the current context to be device
    // performs any initialization

    GPA_LogDebugMessage("GPA_OpenContext( 0x%08x ).", pContext);

    if (!pContext)
    {
        GPA_LogError("Parameter 'pContext' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    // see if context already exists
    GPA_ContextState* pRetrievedContext = lookupContext(pContext);

    if (nullptr != pRetrievedContext)
    {
        GPA_LogError("Context is already open.");
        return GPA_STATUS_ERROR_COUNTERS_ALREADY_OPEN;
    }

    // new context, need to create it
    // It can't be added to the list of contexts until
    // 1) we can successfully get HW info for it
    // 2) we can open counters for it

    GPA_ContextState* pNewContextState = nullptr;
    GPA_Status status = GPA_IMP_CreateContext(&pNewContextState);

    if (status != GPA_STATUS_OK)
    {
        return status;
    }

    GPA_ContextState* pOldContextState = g_pCurrentContext;
    g_pCurrentContext = pNewContextState;
    status = GetHWInfo(pContext, &(pNewContextState->m_hwInfo));

    if (status != GPA_STATUS_OK)
    {
        delete pNewContextState;
        g_pCurrentContext = pOldContextState;
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    // initialize context
    pNewContextState->m_pContext = pContext;
    pNewContextState->m_maxSessions = GPA_IMP_GetDefaultMaxSessions();
    // allocate for the max number of simultaneous sessions
    bool isSizeSet = pNewContextState->m_profileSessions.setSize(pNewContextState->m_maxSessions);

    if (!isSizeSet)
    {
        GPA_LogError("Error setting size of sessions.");
        return GPA_STATUS_ERROR_FAILED;
    }

    status = GPA_IMP_OpenContext(pContext);

    if (status != GPA_STATUS_OK)
    {
        g_pCurrentContext = nullptr;
        delete pNewContextState;
        return status;
    }

    // now that the counters could be opened, add the context
    g_Contexts.push_back(pNewContextState);

    gpa_uint32 vendorId = 0;
    g_pCurrentContext->m_hwInfo.GetVendorID(vendorId);
    gpa_uint32 deviceId = 0;
    g_pCurrentContext->m_hwInfo.GetDeviceID(deviceId);
    gpa_uint32 revisionId = 0;
    g_pCurrentContext->m_hwInfo.GetRevisionID(revisionId);

    GPA_Status retStatus = g_pCurrentContext->m_pCounterScheduler->SetCounterAccessor(g_pCurrentContext->m_pCounterAccessor, vendorId, deviceId, revisionId);

    return retStatus;
}

//-----------------------------------------------------------------------------
// context must have been called with OpenContext before SelectContext is called on it
GPALIB_DECL GPA_Status GPA_SelectContext(void* pContext)
{
    PROFILE_FUNCTION(GPA_SelectContext);
    TRACE_FUNCTION(GPA_SelectContext);

    GPA_Status retStatus = GPA_STATUS_OK;

    if (!pContext)
    {
        GPA_LogError("Parameter 'pContext' is NULL.");
        retStatus = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        GPA_ContextState* pContextState = lookupContext(pContext);

        if (!pContextState)
        {
            GPA_LogError("Specified context is not open. It cannot be selected.");
            return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
        }

        retStatus = GPA_IMP_SelectContext(pContext);
        g_pCurrentContext = pContextState;
    }

    return retStatus;
}

//-----------------------------------------------------------------------------
// when closed the first context is assigned to be the current
GPALIB_DECL GPA_Status GPA_CloseContext()
{
    PROFILE_FUNCTION(GPA_CloseContext);
    TRACE_FUNCTION(GPA_CloseContext);

    if (!g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_CloseContext.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (g_pCurrentContext->m_samplingStarted)
    {
        GPA_LogError("Please call GPA_EndSession before GPA_CloseContext.");
        return GPA_STATUS_ERROR_SAMPLING_NOT_ENDED;
    }

    GPA_LogDebugMessage("GPA_CloseContext( 0x%08x ).", g_pCurrentContext->m_pContext);

    g_pCurrentContext->m_pCounterScheduler->Reset();

    GPA_Status retStatus = GPA_IMP_CloseContext();

    // erase all profile sessions
    g_pCurrentContext->m_profileSessions.clear();

    // delete the context that's currently open
    int currentContextIndex = lookupContextState(g_pCurrentContext);
    assert(currentContextIndex != -1);
    g_Contexts.erase(g_Contexts.begin() + currentContextIndex);
    delete g_pCurrentContext;

    // reassign the current context
    if (g_Contexts.size() > 0)
    {
        g_pCurrentContext = g_Contexts[0];
    }
    else
    {
        g_pCurrentContext = nullptr;
    }

    return retStatus;
}

//-----------------------------------------------------------------------------
// Counter Interrogation
GPALIB_DECL GPA_Status GPA_GetNumCounters(gpa_uint32* pCount)
{
    PROFILE_FUNCTION(GPA_GetNumCounters);
    TRACE_FUNCTION(GPA_GetNumCounters);

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_GetNumCounters.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (!pCount)
    {
        GPA_LogError("Parameter 'pCount' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (nullptr == g_pCurrentContext->m_pCounterAccessor)
    {
        GPA_LogError("GPA_OpenContext must return successfully before calling GPA_GetNumCounters.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    *pCount = g_pCurrentContext->m_pCounterAccessor->GetNumCounters();

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetCounterName(gpa_uint32 index, const char** ppName)
{
    PROFILE_FUNCTION(GPA_GetCounterName);
    TRACE_FUNCTION(GPA_GetCounterName);

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("GPA_OpenContext must return successfully before calling GPA_GetNumCounters.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (nullptr == g_pCurrentContext->m_pCounterAccessor)
    {
        GPA_LogError("GPA_OpenContext must return successfully before calling GPA_GetNumCounters.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    gpa_uint32 numCounters = g_pCurrentContext->m_pCounterAccessor->GetNumCounters();

    if (index >= numCounters)
    {
        std::stringstream message;
        message << "Parameter 'index' is " << index << " but must be less than " << numCounters << ".";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE;
    }

    if (!ppName)
    {
        GPA_LogError("Parameter 'ppName' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    *ppName = g_pCurrentContext->m_pCounterAccessor->GetCounterName(index);

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetCounterDescription(gpa_uint32 index, const char** ppDescription)
{
    PROFILE_FUNCTION(GPA_GetCounterDescription);
    TRACE_FUNCTION(GPA_GetCounterDescription);

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("GPA_OpenContext must return successfully before calling GPA_GetCounterDescription.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (nullptr == g_pCurrentContext->m_pCounterAccessor)
    {
        GPA_LogError("GPA_OpenContext must return successfully before calling GPA_GetCounterDescription.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    gpa_uint32 numCounters = g_pCurrentContext->m_pCounterAccessor->GetNumCounters();

    if (index >= numCounters)
    {
        std::stringstream message;
        message << "Parameter 'index' is " << index << " but must be less than " << numCounters << ".";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE;
    }

    if (!ppDescription)
    {
        GPA_LogError("Parameter 'ppDescription' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    *ppDescription = g_pCurrentContext->m_pCounterAccessor->GetCounterDescription(index);

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetCounterDataType(gpa_uint32 index, GPA_Type* pCounterDataType)
{
    PROFILE_FUNCTION(GPA_GetCounterDataType);
    TRACE_FUNCTION(GPA_GetCounterDataType);

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("GPA_OpenContext must return successfully before calling GPA_GetCounterDataType.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (nullptr == g_pCurrentContext->m_pCounterAccessor)
    {
        GPA_LogError("GPA_OpenContext must return successfully before calling GPA_GetNumCounters.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    gpa_uint32 numCounters = g_pCurrentContext->m_pCounterAccessor->GetNumCounters();

    if (index >= numCounters)
    {
        std::stringstream message;
        message << "Parameter 'index' is " << index << " but must be less than " << numCounters << ".";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE;
    }

    if (!pCounterDataType)
    {
        GPA_LogError("Parameter 'pCounterDataType' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    *pCounterDataType = g_pCurrentContext->m_pCounterAccessor->GetCounterDataType(index);

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetCounterUsageType(gpa_uint32 index, GPA_Usage_Type* pCounterUsageType)
{
    PROFILE_FUNCTION(GPA_GetCounterUsageType);
    TRACE_FUNCTION(GPA_GetCounterUsageType);

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("GPA_OpenContext must return successfully before calling GPA_GetCounterUsageType.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (nullptr == g_pCurrentContext->m_pCounterAccessor)
    {
        GPA_LogError("GPA_OpenContext must return successfully before calling GPA_GetCounterUsageType.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    gpa_uint32 numCounters = g_pCurrentContext->m_pCounterAccessor->GetNumCounters();

    if (index >= numCounters)
    {
        std::stringstream message;
        message << "Parameter 'index' is " << index << " but must be less than " << numCounters << ".";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE;
    }

    if (!pCounterUsageType)
    {
        GPA_LogError("Parameter 'pCounterUsageType' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    *pCounterUsageType = g_pCurrentContext->m_pCounterAccessor->GetCounterUsageType(index);
    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_EnableCounter(gpa_uint32 index)
{
    PROFILE_FUNCTION(GPA_EnableCounter);
    TRACE_FUNCTION(GPA_EnableCounter);

    gpa_uint32 numCounters;
    GPA_Status status = GPA_GetNumCounters(&numCounters);

    if (status != GPA_STATUS_OK)
    {
        return status;
    }

    if (index >= numCounters)
    {
        std::stringstream message;
        message << "Parameter 'index' is " << index << " but must be less than " << numCounters << ".";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE;
    }

    if (g_pCurrentContext->m_samplingStarted)
    {
        GPA_LogError("Call GPA_EndSession before trying to change the enabled counters with GPA_EnableCounter.");
        return GPA_STATUS_ERROR_CANNOT_CHANGE_COUNTERS_WHEN_SAMPLING;
    }

    status = g_pCurrentContext->m_pCounterScheduler->EnableCounter(index);

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_DisableCounter(gpa_uint32 index)
{
    PROFILE_FUNCTION(GPA_DisableCounter);
    TRACE_FUNCTION(GPA_DisableCounter);

    gpa_uint32 numCounters;
    GPA_Status status = GPA_GetNumCounters(&numCounters);

    if (status != GPA_STATUS_OK)
    {
        return status;
    }

    if (index >= numCounters)
    {
        std::stringstream message;
        message << "Parameter 'index' is " << index << " but must be less than " << numCounters << ".";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE;
    }

    if (g_pCurrentContext->m_samplingStarted)
    {
        GPA_LogError("Call GPA_EndSession before trying to change the enabled counters with GPA_DisableCounter.");
        return GPA_STATUS_ERROR_CANNOT_CHANGE_COUNTERS_WHEN_SAMPLING;
    }

    status = g_pCurrentContext->m_pCounterScheduler->DisableCounter(index);

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetEnabledCount(gpa_uint32* pCount)
{
    PROFILE_FUNCTION(GPA_GetEnabledCount);
    TRACE_FUNCTION(GPA_GetEnabledCount);

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_GetEnabledCount.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (nullptr == pCount)
    {
        GPA_LogError("Parameter 'pCount' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    (*pCount) = g_pCurrentContext->m_pCounterScheduler->GetNumEnabledCounters();

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetEnabledIndex(gpa_uint32 enabledNumber, gpa_uint32* pEnabledCounterIndex)
{
    PROFILE_FUNCTION(GPA_GetEnabledIndex);
    TRACE_FUNCTION(GPA_GetEnabledIndex);

    if (!g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_GetEnabledIndex.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (!pEnabledCounterIndex)
    {
        GPA_LogError("Parameter 'pEnabledCounterIndex' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    GPA_Status status = g_pCurrentContext->m_pCounterScheduler->GetEnabledIndex(enabledNumber, pEnabledCounterIndex);
    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_IsCounterEnabled(gpa_uint32 counterIndex)
{
    PROFILE_FUNCTION(GPA_IsCounterEnabled);
    TRACE_FUNCTION(GPA_IsCounterEnabled);

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_GetEnabledCount.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    return g_pCurrentContext->m_pCounterScheduler->IsCounterEnabled(counterIndex);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_EnableAllCounters()
{
    PROFILE_FUNCTION(GPA_EnableAllCounters);
    TRACE_FUNCTION(GPA_EnableAllCounters);

    GPA_Status status = GPA_DisableAllCounters();

    if (GPA_STATUS_OK != status)
    {
        return status;
    }

    gpa_uint32 count;
    status = GPA_GetNumCounters(&count);

    if (GPA_STATUS_OK != status)
    {
        return status;
    }

    for (gpa_uint32 i = 0 ; i < count ; i++)
    {
        status = GPA_EnableCounter(i);

        if (GPA_STATUS_OK != status)
        {
            return status;
        }
    }

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_DisableAllCounters()
{
    PROFILE_FUNCTION(GPA_DisableAllCounters);
    TRACE_FUNCTION(GPA_DisableAllCounters);

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_DisableAllCounters.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (g_pCurrentContext->m_samplingStarted)
    {
        GPA_LogError("Call GPA_EndSession before trying to change the enabled counters with GPA_DisableAllCounters.");
        return GPA_STATUS_ERROR_CANNOT_CHANGE_COUNTERS_WHEN_SAMPLING;
    }

    g_pCurrentContext->m_pCounterScheduler->DisableAllCounters();

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetCounterIndex(const char* pCounter, gpa_uint32* pIndex)
{
    PROFILE_FUNCTION(GPA_GetCounterIndex);
    TRACE_FUNCTION(GPA_GetCounterIndex);

    if (nullptr == pCounter)
    {
        GPA_LogError("Parameter 'pCounter' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (nullptr == pIndex)
    {
        GPA_LogDebugError("Parameter 'pIndex' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("GPA_OpenContext must return successfully before calling GPA_GetCounterIndex.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (nullptr == g_pCurrentContext->m_pCounterAccessor)
    {
        GPA_LogError("GPA_OpenContext must return successfully before calling GPA_GetCounterIndex.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    bool counterFound = g_pCurrentContext->m_pCounterAccessor->GetCounterIndex(pCounter, pIndex);

    if (!counterFound)
    {
        std::string message = "Specified counter '";
        message += pCounter;
        message += "' was not found. Please check spelling or availability.";
        GPA_LogError(message.c_str());
        return GPA_STATUS_ERROR_NOT_FOUND;
    }

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_EnableCounterStr(const char* pCounter)
{
    PROFILE_FUNCTION(GPA_EnableCounterStr);
    TRACE_FUNCTION(GPA_EnableCounterStr);

    gpa_uint32 index;
    GPA_Status status = GPA_GetCounterIndex(pCounter, &index);

    if (GPA_STATUS_OK != status)
    {
        return status;
    }

    status = GPA_EnableCounter(index);

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_DisableCounterStr(const char* pCounter)
{
    PROFILE_FUNCTION(GPA_DisableCounterStr);
    TRACE_FUNCTION(GPA_DisableCounterStr);

    gpa_uint32 index;
    GPA_Status status = GPA_GetCounterIndex(pCounter, &index);

    if (GPA_STATUS_OK != status)
    {
        return status;
    }

    status = GPA_DisableCounter(index);

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetPassCount(gpa_uint32* pNumPasses)
{
    PROFILE_FUNCTION(GPA_GetPassCount);
    TRACE_FUNCTION(GPA_GetPassCount);

    if (nullptr == pNumPasses)
    {
        GPA_LogError("Parameter 'pNumPasses' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_GetPassCount.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    return g_pCurrentContext->m_pCounterScheduler->GetNumRequiredPasses(pNumPasses);
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_BeginSession(gpa_uint32* pSessionID)
{
    PROFILE_FUNCTION(GPA_BeginSession);
    TRACE_FUNCTION(GPA_BeginSession);

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_BeginSession.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (nullptr == pSessionID)
    {
        GPA_LogError("Parameter 'pSessionID' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    gpa_uint32 passCount = 0;
    GPA_Status status = GPA_GetPassCount(&passCount);

    if (GPA_STATUS_OK != status)
    {
        return status;
    }

    if (0 == passCount)
    {
        GPA_LogError("Please enable at least one counter before calling GPA_BeginSession.");
        return GPA_STATUS_ERROR_NO_COUNTERS_ENABLED;
    }

    if (g_pCurrentContext->m_samplingStarted)
    {
        std::stringstream message;
        message << "Session " << pSessionID << " has already started. Please end the session before starting it again.";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_SAMPLING_ALREADY_STARTED;
    }

    // inc selectionID if counter selection got changed since last sampling session
    bool selectionChanged = g_pCurrentContext->m_pCounterScheduler->GetCounterSelectionChanged();

    if (selectionChanged)
    {
        g_pCurrentContext->m_selectionID++;
    }

    // reset pass count
    g_pCurrentContext->m_pCounterScheduler->BeginProfile();
    g_pCurrentContext->m_currentPass = 0;

    // allocate session ID
    g_pCurrentContext->m_sessionID++;
    (*pSessionID) = g_pCurrentContext->m_sessionID;
    g_pCurrentContext->m_samplingStarted = true;

    // Allocate the next session
    bool lockedOk = false;
    g_pCurrentContext->m_pCurrentSessionRequests = &g_pCurrentContext->m_profileSessions.lockNext(lockedOk);

    // make sure all requests of the session about to be reused have completed
    g_pCurrentContext->m_pCurrentSessionRequests->Flush();
    assert(lockedOk == true);
    g_pCurrentContext->m_profileSessions.addLockedItem();

    g_pCurrentContext->m_pCurrentSessionRequests->SetPassCount(passCount);

    // prepare the current session for data requests
    g_pCurrentContext->m_pCurrentSessionRequests->m_sessionID = (*pSessionID);

    status = GPA_IMP_BeginSession(pSessionID, selectionChanged);

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_EndSession()
{
    PROFILE_FUNCTION(GPA_EndSession);
    TRACE_FUNCTION(GPA_EndSession);

    GPA_Status returnStatus = GPA_STATUS_OK;

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_EndSession.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (!g_pCurrentContext->m_samplingStarted)
    {
        GPA_LogError("A session must be started with GPA_BeginSession before it can be ended.");
        return GPA_STATUS_ERROR_SAMPLING_NOT_STARTED;
    }

    if (g_pCurrentContext->m_passStarted)
    {
        GPA_LogError("Please call GPA_EndPass before ending the session with GPA_EndSession.");
        return GPA_STATUS_ERROR_PASS_NOT_ENDED;
    }

    returnStatus = g_pCurrentContext->m_pCounterScheduler->EndProfile();

    if (GPA_STATUS_ERROR_NOT_ENOUGH_PASSES == returnStatus)
    {
        // potentially recoverable error (ignore session) so drop through with error return
        GPA_LogError("More passes must be completed before the session can be ended successfully.");
    }

    g_pCurrentContext->m_samplingStarted = false;

    GPA_Status impStatus = GPA_IMP_EndSession();

    if (GPA_STATUS_OK == returnStatus)
    {
        // return implementation EndPass status since we didn't have an error
        return impStatus;
    }
    else
    {
        // There was a problem before implementation EndSession was called, return that error
        return returnStatus;
    }
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_BeginPass()
{
    PROFILE_FUNCTION(GPA_BeginPass);
    TRACE_FUNCTION(GPA_BeginPass);

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_BeginPass.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (!g_pCurrentContext->m_samplingStarted)
    {
        GPA_LogError("A session must be started with GPA_BeginSession before a pass be started.");
        return GPA_STATUS_ERROR_SAMPLING_NOT_STARTED;
    }

    if (g_pCurrentContext->m_passStarted)
    {
        GPA_LogError("Please call GPA_EndPass before starting a new one.");
        return GPA_STATUS_ERROR_PASS_ALREADY_STARTED;
    }

    g_pCurrentContext->m_pCounterScheduler->BeginPass();

    g_pCurrentContext->m_passStarted = true;
    g_pCurrentContext->m_sampleCount = 0;
    g_pCurrentContext->m_currentPass++;

    GPA_Status status = GPA_IMP_BeginPass();

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_EndPass()
{
    PROFILE_FUNCTION(GPA_EndPass);
    TRACE_FUNCTION(GPA_EndPass);

    GPA_Status returnStatus = GPA_STATUS_OK;

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_EndPass.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (!g_pCurrentContext->m_samplingStarted)
    {
        GPA_LogError("A session must be started with GPA_BeginSession before a pass can be ended.");
        return GPA_STATUS_ERROR_SAMPLING_NOT_STARTED;
    }

    if (!g_pCurrentContext->m_passStarted)
    {
        GPA_LogError("A pass must be started with GPA_BeginPass before a pass can be ended.");
        return GPA_STATUS_ERROR_PASS_NOT_STARTED;
    }

    if (g_pCurrentContext->m_sampleStarted)
    {
        GPA_LogError("The current sample must be ended with GPA_EndSample before the pass can be ended.");
        return GPA_STATUS_ERROR_SAMPLE_NOT_ENDED;
    }

    if (1 == g_pCurrentContext->m_currentPass)
    {
        // first pass, set the sample per pass count
        g_pCurrentContext->m_firstPassSampleCount = g_pCurrentContext->m_sampleCount;
    }
    else
    {
        // test the sample per pass count
        if (g_pCurrentContext->m_sampleCount != g_pCurrentContext->m_firstPassSampleCount)
        {
            // use return status to signal error. Drop through to allow pass to close,
            // otherwise user will be stuck in this state.
            returnStatus = GPA_STATUS_ERROR_VARIABLE_NUMBER_OF_SAMPLES_IN_PASSES;
            GPA_LogError("A different number of samples were taken in this pass than a previous one. This must be corrected for GPA_EndPass to complete successfully.");
        }
    }

    g_pCurrentContext->m_passStarted = false;
    g_pCurrentContext->m_pCounterScheduler->EndPass();

    GPA_Status impStatus = GPA_IMP_EndPass();

    if (GPA_STATUS_OK == returnStatus)
    {
        // return implementation EndPass status since we didn't have an error
        return impStatus;
    }
    else
    {
        // There was a problem before implementation EndPass was called, return that error
        return returnStatus;
    }
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_BeginSample(gpa_uint32 sampleID)
{
    PROFILE_FUNCTION(GPA_BeginSample);
    TRACE_FUNCTION(GPA_BeginSample);

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_BeginSample.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (!g_pCurrentContext->m_samplingStarted)
    {
        GPA_LogError("A session must be started with GPA_BeginSession before a sample can be started.");
        return GPA_STATUS_ERROR_SAMPLING_NOT_STARTED;
    }

    if (!g_pCurrentContext->m_passStarted)
    {
        GPA_LogError("A pass must be started with GPA_BeginPass before a sample can be started.");
        return GPA_STATUS_ERROR_PASS_NOT_STARTED;
    }

    if (g_pCurrentContext->m_sampleStarted)
    {
        GPA_LogError("The previous sample must be ended with GPA_EndSample before a new one can be started.");
        return GPA_STATUS_ERROR_SAMPLE_ALREADY_STARTED;
    }

    //check if sample id is already in use for this pass
    if (g_pCurrentContext->m_pCurrentSessionRequests->ContainsSampleRequest(g_pCurrentContext->m_currentPass - 1, sampleID))
    {
        GPA_LogError("This pass already contains a sample with this sample id. Please ensure all sample ids are unique.");
        return GPA_STATUS_ERROR_SAMPLE_ALREADY_STARTED;
    }

    // Check if this pass is needed
    gpa_uint32 numRequiredPasses = 0;
    g_pCurrentContext->m_pCounterScheduler->GetNumRequiredPasses(&numRequiredPasses);

    gpa_uint32 passCount = g_pCurrentContext->m_pCurrentSessionRequests->GetPassCount();

    if (g_pCurrentContext->m_currentPass > numRequiredPasses &&
        g_pCurrentContext->m_currentPass > passCount)
    {
        // set the sample as started so that the call to EndSample will not generate errors
        g_pCurrentContext->m_sampleStarted = true;
        g_pCurrentContext->m_currentSample = sampleID;

        // just return successful since this pass is not needed (there are no counters for this pass).
        return GPA_STATUS_OK;
    }

    GPA_Status status = GPA_IMP_BeginSample(sampleID);

    if (GPA_STATUS_OK == status)
    {
        // issue request for counter data
        GPA_DataRequest* pRequest = g_pCurrentContext->GetDataRequest(g_pCurrentContext->m_currentPass - 1);
        pRequest->SetSampleID(sampleID);

        bool requestOk = pRequest->Begin(g_pCurrentContext, g_pCurrentContext->m_selectionID, g_pCurrentContext->m_pCounterScheduler->GetCountersForPass(g_pCurrentContext->m_currentPass - 1));

        if (!requestOk)
        {
            return GPA_STATUS_ERROR_FAILED;
        }

        // add new request to current session requests list
        g_pCurrentContext->m_pCurrentSessionRequests->Begin(g_pCurrentContext->m_currentPass - 1, sampleID, pRequest);

    }
    else if (GPA_STATUS_OK_HANDLED == status)
    {
        status = GPA_STATUS_OK;
    }

    if (GPA_STATUS_OK == status)
    {
        g_pCurrentContext->m_sampleStarted = true;
        g_pCurrentContext->m_currentSample = sampleID;
    }

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_EndSample()
{
    PROFILE_FUNCTION(GPA_EndSample);
    TRACE_FUNCTION(GPA_EndSample);

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_EndSample.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (!g_pCurrentContext->m_sampleStarted)
    {
        GPA_LogError("A sample must be started with GPA_BeginSample before one can be ended.");
        return GPA_STATUS_ERROR_SAMPLE_NOT_STARTED;
    }

    // make sure this pass is necessary
    if (g_pCurrentContext->m_currentPass > g_pCurrentContext->m_pCurrentSessionRequests->GetPassCount())
    {
        // mark the sample as ended so that EndPass does not generate an error
        g_pCurrentContext->m_sampleStarted = false;

        // just return successful since there were no counters enabled for this pass
        return GPA_STATUS_OK;
    }

    GPA_Status status = GPA_IMP_EndSample();

    if (GPA_STATUS_OK == status)
    {
        bool endedOk = g_pCurrentContext->m_pCurrentSessionRequests->End(g_pCurrentContext->m_currentPass - 1, g_pCurrentContext->m_currentSample);

        if (!endedOk)
        {
            return GPA_STATUS_ERROR_FAILED;
        }
    }
    else if (GPA_STATUS_OK_HANDLED == status)
    {
        status = GPA_STATUS_OK;
    }

    if (GPA_STATUS_OK == status)
    {
        g_pCurrentContext->m_sampleStarted = false;
    }

    g_pCurrentContext->m_sampleCount++;

    // test if other samples are completed
    // If at a proper interval, test for previous samples to be completed
    gpa_uint32 preferredCheckResultFrequency = GPA_IMP_GetPreferredCheckResultFrequency();

    if ((preferredCheckResultFrequency > 0) && g_pCurrentContext->m_currentSample % preferredCheckResultFrequency == 0)
    {
        g_pCurrentContext->m_pCurrentSessionRequests->CheckForAvailableResults(g_pCurrentContext->m_currentPass - 1);
    }

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_IsSampleReady(bool* pReadyResult, gpa_uint32 sessionID, gpa_uint32 sampleID)
{
    PROFILE_FUNCTION(GPA_IsSampleReady);
    TRACE_FUNCTION(GPA_IsSampleReady);

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_IsSampleReady.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (nullptr == pReadyResult)
    {
        GPA_LogError("Parameter 'pReadyResult' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    // result is not initially available
    (*pReadyResult) = false;

    // locate session
    GPA_SessionRequests* checkSession = g_pCurrentContext->FindSession(sessionID);

    if (!checkSession)
    {
        std::stringstream message;
        message << "Parameter 'sessionID' (" << sessionID << ") is not one of the existing sessions.";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_SESSION_NOT_FOUND;
    }

    // need to make sure the sample is ready in all passes
    GPA_Status result = checkSession->IsSampleReady(sampleID, pReadyResult);

    return result;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_IsSessionReady(bool* pReadyResult, gpa_uint32 sessionID)
{
    PROFILE_FUNCTION(GPA_IsSessionReady);
    TRACE_FUNCTION(GPA_IsSessionReady);

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_IsSessionReady.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (nullptr == pReadyResult)
    {
        GPA_LogError("Parameter 'pReadyResult' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    // locate session
    GPA_SessionRequests* checkSession = g_pCurrentContext->FindSession(sessionID);

    if (!checkSession)
    {
        std::stringstream message;
        message << "Parameter 'sessionID' (" << sessionID << ") is not one of the existing sessions.";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_SESSION_NOT_FOUND;
    }

    // check to see if the session is complete
    *pReadyResult = checkSession->IsComplete();

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
/// Array of type sizes
/// This array is dependent on the enum ordering of GPA_Type
static gpa_uint32 g_typeSizeArray[] =
{
    sizeof(gpa_float32),
    sizeof(gpa_float64),
    sizeof(gpa_uint32),
    sizeof(gpa_uint64),
    sizeof(gpa_int32),
    sizeof(gpa_int64),
};

/// Size of g_typeSizeArray
static const gpa_uint32 g_typeSizeArraySize = sizeof(g_typeSizeArray) / sizeof(gpa_uint32);

/// Array of type names
/// This array is dependent on the enum ordering of GPA_Type
static const char* g_typeNameArray[] =
{
    "gpa_float32",
    "gpa_float64",
    "gpa_uint32",
    "gpa_uint64",
    "gpa_int32",
    "gpa_int64",
};

/// Size of g_typeNameArray
static const gpa_uint32 g_typeNameArraySize = sizeof(g_typeNameArray) / sizeof(const char*);

GPALIB_DECL GPA_Status GPA_GetDataTypeAsStr(GPA_Type counterDataType, const char** ppTypeStr)
{
    PROFILE_FUNCTION(GPA_GetDataTypeAsStr);
    TRACE_FUNCTION(GPA_GetDataTypeAsStr);

    assert(g_typeNameArraySize == GPA_TYPE__LAST);

    // Confirm that enum matches assumed ordering of gTypeSizeArray
    assert(GPA_TYPE_FLOAT32 == 0);
    assert(GPA_TYPE_FLOAT64 == 1);
    assert(GPA_TYPE_UINT32 == 2);
    assert(GPA_TYPE_UINT64 == 3);
    assert(GPA_TYPE_INT32 == 4);
    assert(GPA_TYPE_INT64 == 5);

    if (counterDataType >= GPA_TYPE__LAST)
    {
        std::stringstream message;
        message << "Parameter 'counterDataType' (" << counterDataType << ") is not a valid type.";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_NOT_FOUND;
    }

    if (nullptr == ppTypeStr)
    {
        GPA_LogError("Parameter 'ppTypeStr' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    (*ppTypeStr) = g_typeNameArray[counterDataType];

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
/// Array of usage type names
/// This array is dependent on the enum ordering of GPA_Type
static const char* g_usageTypeNameArray[] =
{
    "ratio",
    "percentage",
    "cycles",
    "milliseconds",
    "bytes",
    "items",
    "kilobytes",
};

/// Size of g_usageTypeNameArray
static const gpa_uint32 g_usageTypeNameArraySize = sizeof(g_usageTypeNameArray) / sizeof(const char*);

GPALIB_DECL GPA_Status GPA_GetUsageTypeAsStr(GPA_Usage_Type counterUsageType, const char** ppUsageTypeStr)
{
    PROFILE_FUNCTION(GPA_GetUsageTypeAsStr);
    TRACE_FUNCTION(GPA_GetUsageTypeAsStr);

    assert(g_usageTypeNameArraySize == GPA_USAGE_TYPE__LAST);

    // Confirm that enum matches assumed ordering of the array
    assert(GPA_USAGE_TYPE_RATIO == 0);
    assert(GPA_USAGE_TYPE_PERCENTAGE == 1);
    assert(GPA_USAGE_TYPE_CYCLES == 2);
    assert(GPA_USAGE_TYPE_MILLISECONDS == 3);
    assert(GPA_USAGE_TYPE_BYTES == 4);
    assert(GPA_USAGE_TYPE_ITEMS == 5);
    assert(GPA_USAGE_TYPE_KILOBYTES == 6);

    if (counterUsageType >= GPA_USAGE_TYPE__LAST)
    {
        std::stringstream message;
        message << "Parameter 'counterUsageType' (" << counterUsageType << ") is not a valid type.";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_NOT_FOUND;
    }

    if (nullptr == ppUsageTypeStr)
    {
        GPA_LogError("Parameter 'ppUsageTypeStr' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    (*ppUsageTypeStr) = g_usageTypeNameArray[counterUsageType];

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
/// Template function to get counter sample result
/// \param sessionID the session ID whose sample data is needed
/// \param sampleID the sample ID whose counter result is needed
/// \param counterIndex the counter index of the counter whose result is needed
/// \param[out] pResult holds the value of the counter
/// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
template <class ResultType>
static GPA_Status GPA_GetSample(gpa_uint32 sessionID, gpa_uint32 sampleID, gpa_uint32 counterIndex, ResultType* pResult)
{
    PROFILE_FUNCTION(GPA_GetSample);
    TRACE_FUNCTION(GPA_GetSample);

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_GetSample.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (nullptr == pResult)
    {
        GPA_LogError("Parameter 'pResult' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    // locate session
    GPA_SessionRequests* checkSession = g_pCurrentContext->FindSession(sessionID);

    if (!checkSession)
    {
        std::stringstream message;
        message << "Parameter 'sessionID' (" << sessionID << ") is not one of the existing sessions.";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_SESSION_NOT_FOUND;
    }

    if (GPA_IsCounterEnabled(counterIndex) != GPA_STATUS_OK)
    {
        std::stringstream message;
        message << "Parameter 'counterIndex' (" << counterIndex << ") does not identify an enabled counter.";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_NOT_ENABLED;
    }

    gpa_uint32 numPublicCounters = g_pCurrentContext->m_pCounterAccessor->GetNumPublicCounters();

    if (counterIndex < numPublicCounters) // AMD public counter
    {
        // need to compute the result from the internal counters
        // look up the value for each required internal counter

        BEGIN_PROFILE_SECTION(GPA_GetSample::CalcPublicCounters);

        // counterIndex is the public counter index
        GPA_Status status;

        vector<char*> results;
        vector<GPA_Type> types;
        vector<gpa_uint32> internalCountersRequired = g_pCurrentContext->m_pCounterAccessor->GetInternalCountersRequired(counterIndex);

        size_t requiredCount = internalCountersRequired.size();
        results.reserve(requiredCount);
        types.reserve(requiredCount);

        char* pAllResults = new(std::nothrow) char[requiredCount * 8];

        if (nullptr == pAllResults)
        {
            GPA_LogError("Unable to allocate memory for results.");
            return GPA_STATUS_ERROR_FAILED;
        }

        CounterResultLocationMap* pResultLocations = g_pCurrentContext->m_pCounterScheduler->GetCounterResultLocations(counterIndex);

        unsigned int resultIndex = 0;

        for (std::vector<gpa_uint32>::iterator requiredCounterIter = internalCountersRequired.begin(); requiredCounterIter != internalCountersRequired.end(); ++requiredCounterIter)
        {
            char* pResultBuffer = &(pAllResults[resultIndex]);
            resultIndex += 8;
            results.push_back(pResultBuffer);
            GPA_Type type = GPA_TYPE_UINT64; // all hardware counters are UINT64
            types.push_back(type);

            std::map<unsigned int, GPA_CounterResultLocation>::iterator resultLocationIter = pResultLocations->find(*requiredCounterIter);

            if (resultLocationIter == pResultLocations->end())
            {
                GPA_LogError("Could not find required counter among the results.");
                return GPA_STATUS_ERROR_FAILED;
            }

            status = checkSession->GetResult(resultLocationIter->second.m_pass, sampleID, resultLocationIter->second.m_offset, pResultBuffer);

#ifdef AMDT_INTERNAL
            const char* pInternalName = g_pCurrentContext->m_pCounterAccessor->GetCounterName(numPublicCounters + *requiredCounterIter);
            const char* pPublicName = g_pCurrentContext->m_pCounterAccessor->GetCounterName(counterIndex);

            std::stringstream message;
            message << "Session " << sessionID << ", sample " << sampleID << ", pubCounter '" << pPublicName << "', iCounter: '" << pInternalName << "', [" << *requiredCounterIter << "] = ";

            if (type == GPA_TYPE_UINT32)
            {
                gpa_uint32* pValue = (gpa_uint32*)pResultBuffer;

                message << *pValue;
            }
            else if (type == GPA_TYPE_UINT64)
            {
                gpa_uint64* pValue = (gpa_uint64*)pResultBuffer;

                message << *pValue;
            }
            else if (type == GPA_TYPE_FLOAT32)
            {
                gpa_float32* pValue = (gpa_float32*)pResultBuffer;

                message << *pValue;
            }
            else if (type == GPA_TYPE_FLOAT64)
            {
                gpa_float64* pValue = reinterpret_cast<gpa_float64*>(pResultBuffer);

                message << *pValue;
            }
            else
            {
                // case not covered
                assert(false);
            }

            message << ".";
            GPA_LogDebugCounterDefs(message.str().c_str());
#endif

            if (status != GPA_STATUS_OK)
            {
                delete[] pAllResults;
                return status;
            }
        }

        // compute using supplied function. value order is as defined when registered
        g_pCurrentContext->m_pCounterAccessor->ComputePublicCounterValue(counterIndex, results, types, pResult, &(g_pCurrentContext->m_hwInfo));

        delete[] pAllResults;

        END_PROFILE_SECTION(GPA_GetSample::CalcPublicCounters);

        return GPA_STATUS_OK;
    }
    else  //counterIndex >= numPublicCounters
    {
        GPA_Status status = GPA_STATUS_OK;

        CounterResultLocationMap* const pLocations = g_pCurrentContext->m_pCounterScheduler->GetCounterResultLocations(counterIndex);

        gpa_uint32 numAMDCounters = g_pCurrentContext->m_pCounterAccessor->GetNumAMDCounters();

        if (counterIndex < numAMDCounters) // internal counter
        {
            gpa_uint32 hardwareCounterIndex = counterIndex - numPublicCounters;
            gpa_uint16 counterResultPass = (*pLocations)[hardwareCounterIndex].m_pass;
            gpa_uint16 counterResultOffset = (*pLocations)[hardwareCounterIndex].m_offset;
            status = checkSession->GetResult(counterResultPass, sampleID, counterResultOffset, pResult);
        }

#if defined(WIN32)
        else  //SW counter
        {
            counterIndex -= numAMDCounters;
            gpa_uint64 buf = 0;
            auto iter = pLocations->begin();
            gpa_uint16 counterResultOffset = iter->second.m_offset;
            gpa_uint16 counterResultPass = iter->second.m_pass;

            status = checkSession->GetResult(counterResultPass, sampleID, counterResultOffset, &buf);

            // compute using supplied function. value order is as defined when registered
            g_pCurrentContext->m_pCounterAccessor->ComputeSWCounterValue(counterIndex, buf, pResult, &(g_pCurrentContext->m_hwInfo));
        }

#endif // WIN32

        return status;
    }
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetSampleCount(gpa_uint32 sessionID, gpa_uint32* pSampleCount)
{
    PROFILE_FUNCTION(GPA_GetSampleCount);
    TRACE_FUNCTION(GPA_GetSampleCount);

    if (nullptr == pSampleCount)
    {
        GPA_LogError("Parameter 'pSampleCount' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    GPA_SessionRequests* checkSession = g_pCurrentContext->FindSession(sessionID);

    if (nullptr == checkSession)
    {
        std::stringstream message;
        message << "Parameter 'sessionID' (" << sessionID << ") is not one of the existing sessions.";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_SESSION_NOT_FOUND;
    }

    GPA_Status status = checkSession->GetSampleCount(pSampleCount);
    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetSampleUInt64(gpa_uint32 sessionID, gpa_uint32 sampleID, gpa_uint32 counterIndex, gpa_uint64* pResult)
{
    PROFILE_FUNCTION(GPA_GetSampleUInt64);
    TRACE_FUNCTION(GPA_GetSampleUInt64);

    if (nullptr == pResult)
    {
        GPA_LogError("Parameter 'pResult' cannot be NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    // verify type ( and index )
    GPA_Type counterType;
    GPA_Status status = GPA_GetCounterDataType(counterIndex, &counterType);

    if (GPA_STATUS_OK != status)
    {
        return status;
    }

    if (GPA_TYPE_UINT64 != counterType)
    {
        std::stringstream message;
        message << "Counter identified by 'counterIndex' (" << counterIndex << ") is not of type UInt64.";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_COUNTER_NOT_OF_SPECIFIED_TYPE;
    }

    status = GPA_GetSample< gpa_uint64 >(sessionID, sampleID, counterIndex, pResult);

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetSampleUInt32(gpa_uint32 sessionID, gpa_uint32 sampleID, gpa_uint32 counterIndex, gpa_uint32* pResult)
{
    PROFILE_FUNCTION(GPA_GetSampleUInt32);
    TRACE_FUNCTION(GPA_GetSampleUInt32);

    if (nullptr == pResult)
    {
        GPA_LogError("Parameter 'pResult' cannot be NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    // verify type ( and index )
    GPA_Type counterType;
    GPA_Status status = GPA_GetCounterDataType(counterIndex, &counterType);

    if (GPA_STATUS_OK != status)
    {
        return status;
    }

    if (GPA_TYPE_UINT32 != counterType)
    {
        std::stringstream message;
        message << "Counter identified by 'counterIndex' (" << counterIndex << ") is not of type UInt32.";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_COUNTER_NOT_OF_SPECIFIED_TYPE;
    }

    status = GPA_GetSample< gpa_uint32 >(sessionID, sampleID, counterIndex, pResult);

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetSampleFloat32(gpa_uint32 sessionID, gpa_uint32 sampleID, gpa_uint32 counterIndex, gpa_float32* pResult)
{
    PROFILE_FUNCTION(GPA_GetSampleFloat32);
    TRACE_FUNCTION(GPA_GetSampleFloat32);

    if (nullptr == pResult)
    {
        GPA_LogError("Parameter 'pResult' cannot be NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    // verify type ( and index )
    GPA_Type counterType;
    GPA_Status status = GPA_GetCounterDataType(counterIndex, &counterType);

    if (GPA_STATUS_OK != status)
    {
        return status;
    }

    if (GPA_TYPE_FLOAT32 != counterType)
    {
        std::stringstream message;
        message << "Counter identified by 'counterIndex' (" << counterIndex << ") is not of type Float32.";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_COUNTER_NOT_OF_SPECIFIED_TYPE;
    }

    status = GPA_GetSample< gpa_float32 >(sessionID, sampleID, counterIndex, pResult);

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetSampleFloat64(gpa_uint32 sessionID, gpa_uint32 sampleID, gpa_uint32 counterIndex, gpa_float64* pResult)
{
    PROFILE_FUNCTION(GPA_GetSampleFloat64);
    TRACE_FUNCTION(GPA_GetSampleFloat64);

    if (nullptr == pResult)
    {
        GPA_LogError("Parameter 'pResult' cannot be NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    // verify type ( and index )
    GPA_Type counterType;
    GPA_Status status = GPA_GetCounterDataType(counterIndex, &counterType);

    if (GPA_STATUS_OK != status)
    {
        return status;
    }

    if (GPA_TYPE_FLOAT64 != counterType)
    {
        std::stringstream message;
        message << "Counter identified by 'counterIndex' (" << counterIndex << ") is not of type Float64.";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_COUNTER_NOT_OF_SPECIFIED_TYPE;
    }

    status = GPA_GetSample< gpa_float64 >(sessionID, sampleID, counterIndex, pResult);

    return status;
}

//-----------------------------------------------------------------------------
GPALIB_DECL const char* GPA_GetStatusAsStr(GPA_Status status)
{
    PROFILE_FUNCTION(GPA_GetStatusStr);
    TRACE_FUNCTION(GPA_GetStatusStr);

    switch (status)
    {
        case GPA_STATUS_OK:
            return "Ok";

        case GPA_STATUS_ERROR_NULL_POINTER:
            return "Null Pointer";

        case GPA_STATUS_ERROR_COUNTERS_NOT_OPEN:
            return "Counters Not Open";

        case GPA_STATUS_ERROR_COUNTERS_ALREADY_OPEN:
            return "Counters Already Opened";

        case GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE:
            return "Index Out Of Range";

        case GPA_STATUS_ERROR_NOT_FOUND:
            return "Not Found";

        case GPA_STATUS_ERROR_ALREADY_ENABLED:
            return "Already Enabled";

        case GPA_STATUS_ERROR_NO_COUNTERS_ENABLED:
            return "No Counters Enabled";

        case GPA_STATUS_ERROR_NOT_ENABLED:
            return "Not Enabled";

        case GPA_STATUS_ERROR_SAMPLING_NOT_STARTED:
            return "Sampling Not Started";

        case GPA_STATUS_ERROR_SAMPLING_ALREADY_STARTED:
            return "Sampling Already Started";

        case GPA_STATUS_ERROR_SAMPLING_NOT_ENDED:
            return "Sampling Not Ended";

        case GPA_STATUS_ERROR_NOT_ENOUGH_PASSES:
            return "Not Enough Passes";

        case GPA_STATUS_ERROR_PASS_NOT_ENDED:
            return "Pass Not Ended";

        case GPA_STATUS_ERROR_PASS_NOT_STARTED:
            return "Pass Not Started";

        case GPA_STATUS_ERROR_PASS_ALREADY_STARTED:
            return "Pass Already Started";

        case GPA_STATUS_ERROR_SAMPLE_NOT_STARTED:
            return "Sample Not Started";

        case GPA_STATUS_ERROR_SAMPLE_ALREADY_STARTED:
            return "Sample Already Started";

        case GPA_STATUS_ERROR_SAMPLE_NOT_ENDED:
            return "Sample Not Ended";

        case GPA_STATUS_ERROR_CANNOT_CHANGE_COUNTERS_WHEN_SAMPLING:
            return "Cannot Change Counters When Sampling";

        case GPA_STATUS_ERROR_SESSION_NOT_FOUND:
            return "Session Not Found";

        case GPA_STATUS_ERROR_SAMPLE_NOT_FOUND:
            return "Sample Not Found";

        case GPA_STATUS_ERROR_SAMPLE_NOT_FOUND_IN_ALL_PASSES:
            return "Sample Not Found In All Passes";

        case GPA_STATUS_ERROR_COUNTER_NOT_OF_SPECIFIED_TYPE:
            return "Counter Not Of Specified Type";

        case GPA_STATUS_ERROR_READING_COUNTER_RESULT:
            return "Reading Counter Result";

        case GPA_STATUS_ERROR_VARIABLE_NUMBER_OF_SAMPLES_IN_PASSES:
            return "Variable Number Of Samples In Passes";

        case GPA_STATUS_ERROR_FAILED:
            return "Failed";

        case GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED:
            return "Hardware Not Supported";

        case GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED:
            return "Driver Not Supported";
        default:
            break;
    }

    return "Unknown error";
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_InternalProfileStart()
{
    TRACE_FUNCTION(GPA_InternalProfileStart);

    START_PROFILING();

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_InternalProfileStop(const char* pFilename)
{
    TRACE_FUNCTION(GPA_InternalProfileStop);

    WRITE_PROFILE_REPORT(pFilename);
    UNREFERENCED_PARAMETER(pFilename);

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetDeviceID(gpa_uint32* pDeviceID)
{
    TRACE_FUNCTION(GPA_GetDeviceID);

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_GetDeviceID.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (nullptr == pDeviceID)
    {
        GPA_LogError("Parameter 'pDeviceID' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (g_pCurrentContext->m_hwInfo.GetDeviceID(*pDeviceID))
    {
        return GPA_STATUS_OK;
    }

    GPA_LogError("Device ID could not be found.");
    return GPA_STATUS_ERROR_NOT_FOUND;
}

//-----------------------------------------------------------------------------
GPALIB_DECL GPA_Status GPA_GetDeviceDesc(const char** ppDesc)
{
    TRACE_FUNCTION(GPA_GetDeviceDesc);

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_GetDeviceDesc.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (nullptr == ppDesc)
    {
        GPA_LogError("Parameter 'ppDesc' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (g_pCurrentContext->m_hwInfo.GetDeviceName(*ppDesc))
    {
        return GPA_STATUS_OK;
    }

    GPA_LogError("Device description could not be found.");
    return GPA_STATUS_ERROR_NOT_FOUND;
}

#ifdef AMDT_INTERNAL
//---------------------------------------------------------------------------------
//This function must be called before GPA_BeginSession()
GPALIB_DECL GPA_Status GPA_InternalSetDrawCallCounts(const int iCounts)
{

    if (nullptr == g_pCurrentContext)
    {
        GPA_LogError("Please call GPA_OpenContext before GPA_BeginSession.");
        return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
    }

    if (g_pCurrentContext->m_samplingStarted)
    {
        std::stringstream message;
        message << "Session already started. Please set the draw call counts prior to starting a session.";
        GPA_LogError(message.str().c_str());
        return GPA_STATUS_ERROR_SAMPLING_ALREADY_STARTED;
    }

    g_pCurrentContext->m_pCounterScheduler->SetDrawCallCounts(iCounts);

    return GPA_STATUS_OK;
}
#endif
