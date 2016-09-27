//==============================================================================
// Copyright (c) 2012-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  HSA version of GPUPerfAPI
//==============================================================================

#include "../GPUPerfAPI-Common/GPUPerfAPIImp.h"
#include "../GPUPerfAPICounterGenerator/GPACounterGenerator.h"
#include "DeviceInfoUtils.h"
#include "GPUPerfAPIRegistry.h"

#include "HSACounterDataRequest.h"

#include "GPUPerfAPIHSA.h"
#include "GPUPerfAPIHSAGlobals.h"
#include "GPAContextStateHSA.h"
#include "HSARTModuleLoader.h"

#include <vector>
#include <assert.h>
#include <string>
#include <sstream>

using namespace std;

#ifdef _LINUX
    #include "../GPUPerfAPI-Common/Logging.h"
#endif

GPA_ContextStateHSA* getCurrentContext()
{
    return static_cast<GPA_ContextStateHSA* >(g_pCurrentContext);
}


gpa_uint32 GPA_IMP_GetPreferredCheckResultFrequency()
{
    return 0;
}

// Extract hardware info from GPA_HSA_Context which is passed in as context.
GPA_Status GPA_IMP_GetHWInfo(void* pContext, GPA_HWInfo* pHwInfo)
{
    if (nullptr == pContext)
    {
        GPA_LogError("Parameter 'pContext' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (nullptr == pHwInfo)
    {
        GPA_LogError("Parameter 'pHwInfo' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    GPA_HSA_Context* pHSAContext = nullptr;
    GPA_HSA_Context localHSAContext;

    if (HSAGlobalFlags::Instance()->m_wasInitializeCalled)
    {
        pHSAContext = &localHSAContext;
        hsa_queue_t* pQueue = static_cast<hsa_queue_t*>(pContext);
        pHSAContext->m_pQueue = pQueue;
        pHSAContext->m_pAgent = &HSAGlobalFlags::Instance()->m_queueAgentMap[pQueue];
    }
    else
    {
        pHSAContext = static_cast<GPA_HSA_Context*>(pContext);
    }


    if (nullptr == pHSAContext->m_pAgent)
    {
        GPA_LogError("Invalid context");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    HSAModule* pHsaModule = HSARTModuleLoader::Instance()->GetAPIRTModule();

    if (nullptr == pHsaModule)
    {
        GPA_LogError("HSA runtime module is NULL.");
        return GPA_STATUS_ERROR_FAILED;
    }

    const hsa_agent_t device = *pHSAContext->m_pAgent;

    //----------------------------------------------------
    // Check device type
    hsa_device_type_t deviceType;
    hsa_status_t status = pHsaModule->agent_get_info(device, HSA_AGENT_INFO_DEVICE, &deviceType);

    if (HSA_STATUS_SUCCESS != status || HSA_DEVICE_TYPE_GPU != deviceType)
    {
        GPA_LogError("The device is not a GPU device.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    pHwInfo->SetVendorID(AMD_VENDOR_ID);

    // Set up device ID
    uint32_t deviceId;
    status = pHsaModule->agent_get_info(device, static_cast<hsa_agent_info_t>(HSA_AMD_AGENT_INFO_CHIP_ID), &deviceId);

    if (HSA_STATUS_SUCCESS != status)
    {
        GPA_LogError("Unable to get device id.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    // Get device name
    char deviceName[64];
    status = pHsaModule->agent_get_info(device, HSA_AGENT_INFO_NAME, &deviceName);

    if (HSA_STATUS_SUCCESS != status)
    {
        GPA_LogError("Unable to get device name.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    GDT_GfxCardInfo cardInfo;
    bool bSupported = false;

    // TODO: requested that the HSA runtime allows us to get revID -- for now hardcode to zero
    if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(deviceId, REVISION_ID_ANY, cardInfo))
    {
        if (static_cast<unsigned int>(cardInfo.m_generation) >= static_cast<unsigned int>(GDT_HW_GENERATION_SEAISLAND) &&
            _strcmpi(deviceName, cardInfo.m_szCALName) == 0)
        {
            pHwInfo->SetDeviceName(cardInfo.m_szCALName);
            pHwInfo->SetDeviceID(static_cast<gpa_uint32>(cardInfo.m_deviceID));
            pHwInfo->SetRevisionID(static_cast<gpa_uint32>(cardInfo.m_revID));
            bSupported = true;

            std::stringstream message;
            message << "Vendor ID: 0x" << hex << AMD_VENDOR_ID << ", ";
            message << "Device ID: 0x" << hex << cardInfo.m_deviceID << ", ";
            message << "Rev ID: 0x" << hex << cardInfo.m_revID << ", ";
            message << "Device Name: " << cardInfo.m_szCALName << ".";
            GPA_LogDebugMessage(message.str().c_str());
        }
    }

    if (!bSupported)
    {
        GPA_LogError("Unsupported device.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    return GPA_STATUS_OK;
} //GPA_Status GPA_IMP_GetHWInfo


// Compare the current context with the specified hwInfo
GPA_Status GPA_IMP_CompareHWInfo(void* pContext, GPA_HWInfo* pHwInfo)
{
    assert(nullptr != pHwInfo);

    if (nullptr == pHwInfo)
    {
        GPA_LogError("Parameter 'pHwInfo' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    // Get hwInfo of the current context
    GPA_HWInfo curInfo;
    GPA_Status status = GPA_IMP_GetHWInfo(pContext, &curInfo);

    if (GPA_STATUS_OK == status)
    {
        status = CompareHwInfo(pHwInfo, &curInfo);
    }

    if (GPA_STATUS_OK != status)
    {
        GPA_LogError("Available device is not supported.");
    }

    return status;
}


GPA_Status GPA_IMP_VerifyHWSupport(void* pContext, GPA_HWInfo* pHwInfo)
{
    UNREFERENCED_PARAMETER(pContext);

    if (nullptr == pHwInfo)
    {
        GPA_LogError("Parameter 'pHwInfo' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    GDT_HW_GENERATION generation = GDT_HW_GENERATION_NONE;

    if (pHwInfo->GetHWGeneration(generation) == false)
    {
        GPA_LogError("Unable to get hardware generation.");
        return GPA_STATUS_ERROR_FAILED;
    }

    switch (generation)
    {
        case GDT_HW_GENERATION_SEAISLAND :
        case GDT_HW_GENERATION_VOLCANICISLAND :
            break;

        default:
            GPA_LogError("HW generation is not supported.");
            return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_CreateContext(GPA_ContextState** ppNewContext)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == ppNewContext)
    {
        GPA_LogError("Unable to create context. Parameter 'ppNewContext' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }

    GPA_ContextStateHSA* pContext = new(std::nothrow) GPA_ContextStateHSA;

    if (nullptr == pContext)
    {
        GPA_LogError("Unable to create context");
        result = GPA_STATUS_ERROR_FAILED;
    }
    else
    {
        (*ppNewContext) = pContext;
    }

    return result;
}

#ifdef _WIN32
    extern "C" IMAGE_DOS_HEADER __ImageBase;
    #define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

/// Sets the necessary environment variable to enable the HSA runtime Tools lib
/// \return true on success
bool SetHSAToolsLibEnvVar()
{
    bool retVal = false;
    static const char* szHSAToolsLibEnvVar = "HSA_TOOLS_LIB";
    std::string thisLib;

#ifdef _WIN32
    std::string toolsLibVal = "hsa-runtime-tools64.dll";
#else
    std::string toolsLibVal = "libhsa-runtime-tools64.so.1";
#endif

#ifdef _WIN32
    char szEnvVarVal[MAX_PATH] = { 0 };
    GetEnvironmentVariable(szHSAToolsLibEnvVar, szEnvVarVal, MAX_PATH);
    toolsLibVal = szEnvVarVal;
    char szThisModuleName[MAX_PATH] = { 0 };
    retVal = 0 != GetModuleFileName(HINST_THISCOMPONENT, szThisModuleName, MAX_PATH);

    if (retVal)
    {
        if (!toolsLibVal.empty())
        {
            toolsLibVal.append(" ");
        }

        toolsLibVal.append(szThisModuleName);

        retVal = 0 != SetEnvironmentVariable(szHSAToolsLibEnvVar, toolsLibVal.c_str());
    }

#else
    char* szEnvVarVal = getenv(szHSAToolsLibEnvVar);

    if (nullptr != szEnvVarVal)
    {
        toolsLibVal = szEnvVarVal;
    }

    Dl_info dlInfo;
    retVal = 0 != dladdr(reinterpret_cast<void*>(SetHSAToolsLibEnvVar), &dlInfo);

    if (retVal)
    {
        if (!toolsLibVal.empty())
        {
            toolsLibVal.append(" ");
        }

        toolsLibVal.append(dlInfo.dli_fname);

        retVal = 0 == setenv(szHSAToolsLibEnvVar, toolsLibVal.c_str(), 1);
    }

#endif

    return retVal;
}

// Note: this must be called before hsa_init in order for SoftCP mode to be used
GPA_Status GPA_IMP_Initialize()
{
    HSAGlobalFlags::Instance()->m_wasInitializeCalled = true;

    if (!HSAGlobalFlags::Instance()->m_softCPModeEnabled)
    {
        std::string strErrorMessage;

        if (!SetHSASoftCPEnvVar(strErrorMessage))
        {
            GPA_LogError(strErrorMessage.c_str());
            return GPA_STATUS_ERROR_FAILED;
        }

        HSAGlobalFlags::Instance()->m_softCPModeEnabled = true;
    }

    if (!HSAGlobalFlags::Instance()->m_isToolsLibSet)
    {
        if (!SetHSAToolsLibEnvVar())
        {
            return GPA_STATUS_ERROR_FAILED;
        }

        HSAGlobalFlags::Instance()->m_isToolsLibSet = true;
    }

    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_Destroy()
{
    if (HSAGlobalFlags::Instance()->m_softCPModeEnabled)
    {
        std::string strErrorMessage;

        if (!UnsetHSASoftCPEnvVar(strErrorMessage))
        {
            GPA_LogError(strErrorMessage.c_str());
            return GPA_STATUS_ERROR_FAILED;
        }

        HSAGlobalFlags::Instance()->m_softCPModeEnabled = false;
    }

    return GPA_STATUS_OK;
}

/// Pre-dispatch callback function
/// \param pRTParam the pre-dispatch callback params
/// \param pUserArgs the user arguments
void HSA_PreDispatchCallback(const hsa_dispatch_callback_t* pRTParam, void* pUserArgs)
{
    UNREFERENCED_PARAMETER(pUserArgs);

    assert(nullptr != pRTParam && true == pRTParam->pre_dispatch);

    HSAToolsRTModule* pHsaToolsRTModule = HSAToolsRTModuleLoader::Instance()->GetAPIRTModule();

    if (nullptr == pHsaToolsRTModule || !pHsaToolsRTModule->IsModuleLoaded())
    {
        GPA_LogError("Unable to load HSA tools runtime module.");
    }
    else
    {
        GPA_ContextStateHSA* pContextState = getCurrentContext();

        if (nullptr != pContextState)
        {
            pContextState->m_pAqlTranslationHandle = pRTParam->aql_translation_handle;

            if (pContextState->m_currentPass > 0)
            {
                // issue request for counter data
                GPA_DataRequest* pRequest = pContextState->GetDataRequest(g_pCurrentContext->m_currentPass - 1);

                if (nullptr != pRequest)
                {
                    pRequest->SetSampleID(HSAGlobalFlags::Instance()->m_sampleID);

                    bool requestOk = pRequest->Begin(pContextState, pContextState->m_selectionID, pContextState->m_pCounterScheduler->GetCountersForPass(pContextState->m_currentPass - 1));

                    if (!requestOk)
                    {
                        GPA_LogError("Failed to begin request.");
                        return;
                    }

                    // add new request to current session requests list
                    g_pCurrentContext->m_pCurrentSessionRequests->Begin(pContextState->m_currentPass - 1, HSAGlobalFlags::Instance()->m_sampleID, pRequest);
                }
                else
                {
                    GPA_LogError("Failed to get data request.");
                }
            }
        }
    }
}

/// Post-dispatch callback function
/// \param pRTParam the post-dispatch callback params
/// \param pUserArgs the user arguments
void HSA_PostDispatchCallback(const hsa_dispatch_callback_t* pRTParam, void* pUserArgs)
{
    UNREFERENCED_PARAMETER(pRTParam);
    UNREFERENCED_PARAMETER(pUserArgs);

    assert(nullptr != pRTParam && false == pRTParam->pre_dispatch);

    if (g_pCurrentContext->m_currentPass > 0)
    {
        bool endedOk = g_pCurrentContext->m_pCurrentSessionRequests->End(g_pCurrentContext->m_currentPass - 1, g_pCurrentContext->m_currentSample);

        if (!endedOk)
        {
            GPA_LogError("Failed to end request.");
            return;
        }
    }
}

// Startup / exit
// Note: "pContext" is GPA_HSA_Context (for now anyway....)
GPA_Status GPA_IMP_OpenContext(void* pContext)
{
    assert(nullptr != pContext);

    if (nullptr == pContext)
    {
        GPA_LogError("Parameter 'pContext' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    HSAModule* pHsaModule = HSARTModuleLoader::Instance()->GetAPIRTModule();

    if (nullptr == pHsaModule || !pHsaModule->IsModuleLoaded())
    {
        GPA_LogError("Unable to load HSA runtime module.");
        return GPA_STATUS_ERROR_FAILED;
    }

    HSAToolsRTModule* pHsaToolsRTModule = HSAToolsRTModuleLoader::Instance()->GetAPIRTModule();

    if (nullptr == pHsaToolsRTModule || !pHsaToolsRTModule->IsModuleLoaded())
    {
        GPA_LogError("Unable to load HSA tools runtime module.");
        return GPA_STATUS_ERROR_FAILED;
    }

    // Get context
    GPA_ContextStateHSA* pContextState = getCurrentContext();


    GPA_HSA_Context* pHSAContext = nullptr;
    GPA_HSA_Context localHSAContext;

    if (HSAGlobalFlags::Instance()->m_wasInitializeCalled)
    {
        pHSAContext = &localHSAContext;
        hsa_queue_t* pQueue = static_cast<hsa_queue_t*>(pContext);
        pHSAContext->m_pQueue = pQueue;
        pHSAContext->m_pAgent = &HSAGlobalFlags::Instance()->m_queueAgentMap[pQueue];
    }
    else
    {
        pHSAContext = static_cast<GPA_HSA_Context*>(pContext);
    }

    if (nullptr == pHSAContext->m_pAgent || nullptr == pHSAContext->m_pQueue)
    {
        GPA_LogError("Invalid context");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    hsa_status_t status;

    if (HSAGlobalFlags::Instance()->m_softCPModeEnabled)
    {
        status = pHsaToolsRTModule->ext_tools_set_callback_functions(const_cast<hsa_queue_t*>(pHSAContext->m_pQueue), HSA_PreDispatchCallback, HSA_PostDispatchCallback);

        if (HSA_STATUS_SUCCESS != status)
        {
            GPA_LogError("Unable to set dispatch callback functions");
            return GPA_STATUS_ERROR_FAILED;
        }
    }

    pContextState->m_pDevice = pHSAContext->m_pAgent;

    status = pHsaToolsRTModule->ext_tools_create_pmu(*pContextState->m_pDevice, &pContextState->m_pmu);

    if (HSA_STATUS_SUCCESS != status)
    {
        GPA_LogError("Cannot create pmu object.");
        return GPA_STATUS_ERROR_FAILED;
    }

    pContextState->m_pQueue = pHSAContext->m_pQueue;
    pContextState->m_pAqlTranslationHandle = pHSAContext->m_pAqlTranslationHandle;

    GDT_HW_GENERATION gen = GDT_HW_GENERATION_NONE;

    if (pContextState->m_hwInfo.GetHWGeneration(gen) == false)
    {
        GPA_LogError("Unable to get hardware generation.");
        return GPA_STATUS_ERROR_FAILED;
    }

    gpa_uint32 vendorId = 0;

    if (pContextState->m_hwInfo.GetVendorID(vendorId) == false)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    gpa_uint32 deviceId = 0;

    if (pContextState->m_hwInfo.GetDeviceID(deviceId) == false)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    gpa_uint32 revisionId = 0;

    if (pContextState->m_hwInfo.GetRevisionID(revisionId) == false)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    return GenerateCounters(GPA_API_HSA, vendorId, deviceId, revisionId, (GPA_ICounterAccessor**) & (pContextState->m_pCounterAccessor), &(pContextState->m_pCounterScheduler));
}


GPA_Status GPA_IMP_CloseContext()
{
    GPA_ContextStateHSA* pContextState = getCurrentContext();

    if (nullptr != pContextState)
    {
        if (nullptr != pContextState->m_pmu)
        {
            hsa_status_t status = HSAToolsRTModuleLoader::Instance()->GetAPIRTModule()->ext_tools_release_pmu(pContextState->m_pmu);

            if (HSA_STATUS_SUCCESS != status)
            {
                GPA_LogError("Error when deleting pmu object.");
            }
        }
    }

    if (HSAGlobalFlags::Instance()->m_softCPModeEnabled)
    {
        hsa_status_t status = HSAToolsRTModuleLoader::Instance()->GetAPIRTModule()->ext_tools_set_callback_functions(const_cast<hsa_queue_t*>(pContextState->m_pQueue), nullptr, nullptr);

        if (HSA_STATUS_SUCCESS != status)
        {
            GPA_LogError("Unable to set dispatch callback functions");
            return GPA_STATUS_ERROR_FAILED;
        }
    }

    return GPA_STATUS_OK;
}


GPA_Status GPA_IMP_SelectContext(void* pContext)
{
    UNREFERENCED_PARAMETER(pContext);

    return GPA_STATUS_OK;
}


GPA_Status GPA_IMP_BeginSession(gpa_uint32* pSessionID, bool counterSelectionChanged)
{
    UNREFERENCED_PARAMETER(pSessionID);
    UNREFERENCED_PARAMETER(counterSelectionChanged);

    return GPA_STATUS_OK;
}


GPA_Status GPA_IMP_EndSession()
{
    return GPA_STATUS_OK;
}


GPA_Status GPA_IMP_BeginPass()
{
    return GPA_STATUS_OK;
}


GPA_Status GPA_IMP_EndPass()
{
    return GPA_STATUS_OK;
}


GPA_Status GPA_IMP_BeginSample(gpa_uint32 sampleID)
{
    UNREFERENCED_PARAMETER(sampleID);

    if (HSAGlobalFlags::Instance()->m_wasInitializeCalled)
    {
        if (HSAGlobalFlags::Instance()->m_sampleID != HSAGlobalFlags::ms_UNDEFINED_SAMPLE_ID)
        {
            return GPA_STATUS_ERROR_SAMPLE_ALREADY_STARTED;
        }

        HSAGlobalFlags::Instance()->m_sampleID = sampleID;
        return GPA_STATUS_OK_HANDLED;
    }

    return GPA_STATUS_OK;
}


GPA_Status GPA_IMP_EndSample()
{
    if (HSAGlobalFlags::Instance()->m_wasInitializeCalled)
    {
        if (HSAGlobalFlags::Instance()->m_sampleID == HSAGlobalFlags::ms_UNDEFINED_SAMPLE_ID)
        {
            return GPA_STATUS_ERROR_SAMPLE_NOT_STARTED;
        }

        HSAGlobalFlags::Instance()->m_sampleID = HSAGlobalFlags::ms_UNDEFINED_SAMPLE_ID;
        return GPA_STATUS_OK_HANDLED;
    }

    return GPA_STATUS_OK;
}


gpa_uint32 GPA_IMP_GetDefaultMaxSessions()
{
    return 4;
}


GPA_DataRequest* GPA_IMP_CreateDataRequest()
{
    return new(std::nothrow) HSACounterDataRequest();
}

