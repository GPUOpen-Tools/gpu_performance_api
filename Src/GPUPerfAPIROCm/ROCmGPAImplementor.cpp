//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief ROCm GPA Implementation
//==============================================================================

#include <assert.h>
#include <sstream>

#include <ADLUtil.h>
#include <DeviceInfoUtils.h>

#include "HSARTModuleLoader.h"
#include "GPUPerfAPI-ROCm.h"
#include "GPUPerfAPIROCmGlobals.h"
#include "ROCmGPAImplementor.h"
#include "ROCmGPAContext.h"

IGPAImplementor* s_pGpaImp = ROCmGPAImplementor::Instance();

GPA_Status ROCmGPAImplementor::Initialize(GPA_InitializeFlags flags)
{
    GPA_Status gpaStatus = GPAImplementor::Initialize(flags);

    if (GPA_STATUS_OK == gpaStatus)
    {
        ROCmGlobalFlags::Instance()->m_wasInitializeCalled = true;

        if (!ROCmGlobalFlags::Instance()->m_rocpInterceptEnabled)
        {
            std::string strErrorMessage;

            if (!SetROCPInterceptEnvVar(strErrorMessage))
            {
                GPA_LogError(strErrorMessage.c_str());
                gpaStatus = GPA_STATUS_ERROR_FAILED;
            }
            else
            {
                ROCmGlobalFlags::Instance()->m_rocpInterceptEnabled = true;
            }
        }

        if (!ROCmGlobalFlags::Instance()->m_isToolsLibSet)
        {
            if (!SetToolsLibEnvVars())
            {
                GPA_LogError("Unable to set Tools Lib Environment Variable.");
                gpaStatus = GPA_STATUS_ERROR_FAILED;
            }
            else
            {
                ROCmGlobalFlags::Instance()->m_isToolsLibSet = true;
            }
        }
    }

    return gpaStatus;
}

GPA_Status ROCmGPAImplementor::Destroy()
{
    if (ROCmGlobalFlags::Instance()->m_rocpInterceptEnabled)
    {
        std::string strErrorMessage;

        if (!UnsetROCPInterceptEnvVar(strErrorMessage))
        {
            GPA_LogError(strErrorMessage.c_str());
            return GPA_STATUS_ERROR_FAILED;
        }

        ROCmGlobalFlags::Instance()->m_rocpInterceptEnabled = false;
    }

    GPA_Status gpaStatus = GPAImplementor::Destroy();

    return gpaStatus;
}

GPA_API_Type ROCmGPAImplementor::GetAPIType() const
{
    return GPA_API_ROCM;
}

bool ROCmGPAImplementor::GetHwInfoFromAPI(const GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo) const
{
    bool isSuccess = true;

    HSAModule* pHsaModule = HSARTModuleLoader::Instance()->GetAPIRTModule();

    if (nullptr == pHsaModule || !pHsaModule->IsModuleLoaded())
    {
        GPA_LogError("HSA runtime module is NULL.");
        isSuccess = false;
    }
    else
    {
        GPA_ROCm_Context* pROCmContext = nullptr;
        GPA_ROCm_Context  localROCmContext;

        if (ROCmGlobalFlags::Instance()->m_wasInitializeCalled)
        {
            pROCmContext           = &localROCmContext;
            hsa_queue_t* pQueue    = static_cast<hsa_queue_t*>(pContextInfo);
            pROCmContext->m_pQueue = pQueue;
            pROCmContext->m_pAgent = &ROCmGlobalFlags::Instance()->m_queueAgentMap[pQueue];
        }
        else
        {
            pROCmContext = static_cast<GPA_ROCm_Context*>(pContextInfo);
        }

        if (nullptr == pROCmContext->m_pAgent)
        {
            GPA_LogError("Invalid context.");
            isSuccess = false;
        }
        else
        {
            const hsa_agent_t device = *pROCmContext->m_pAgent;

            //----------------------------------------------------
            // Check device type
            hsa_device_type_t deviceType;
            hsa_status_t      status = pHsaModule->agent_get_info(device, HSA_AGENT_INFO_DEVICE, &deviceType);

            if (HSA_STATUS_SUCCESS != status || HSA_DEVICE_TYPE_GPU != deviceType)
            {
                GPA_LogError("The device is not a GPU device.");
                isSuccess = false;
            }
            else
            {
                hwInfo.SetVendorID(AMD_VENDOR_ID);

                // Set up device ID
                uint32_t deviceId;
                status = pHsaModule->agent_get_info(device, static_cast<hsa_agent_info_t>(HSA_AMD_AGENT_INFO_CHIP_ID), &deviceId);

                if (HSA_STATUS_SUCCESS != status)
                {
                    GPA_LogError("Unable to get device id.");
                    isSuccess = false;
                }
                else
                {
                    // Get device name
                    char deviceName[64];
                    status = pHsaModule->agent_get_info(device, HSA_AGENT_INFO_NAME, &deviceName);

                    if (HSA_STATUS_SUCCESS != status)
                    {
                        GPA_LogError("Unable to get device name.");
                        isSuccess = false;
                    }
                    else
                    {
                        GDT_GfxCardInfo cardInfo;
                        bool            isDeviceSupported = false;

                        if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(deviceId, REVISION_ID_ANY, cardInfo))
                        {
                            if (static_cast<unsigned int>(cardInfo.m_generation) >= static_cast<unsigned int>(GDT_HW_GENERATION_VOLCANICISLAND))
                            {
                                hwInfo.SetDeviceName(cardInfo.m_szCALName);
                                hwInfo.SetDeviceID(static_cast<gpa_uint32>(cardInfo.m_deviceID));
                                hwInfo.SetRevisionID(static_cast<gpa_uint32>(cardInfo.m_revID));
                                isDeviceSupported = true;

                                std::stringstream message;
                                message << "Vendor ID: 0x" << std::hex << AMD_VENDOR_ID << ", ";
                                message << "Device ID: 0x" << std::hex << cardInfo.m_deviceID << ", ";
                                message << "Rev ID: 0x" << std::hex << cardInfo.m_revID << ", ";
                                message << "Device Name: " << cardInfo.m_szCALName << ", ";
                                message << "HSA RT Device Name: " << deviceName << ".";
                                GPA_LogDebugMessage(message.str().c_str());
                            }
                        }

                        if (!isDeviceSupported)
                        {
                            GPA_LogError("Unsupported device.");
                            isSuccess = false;
                        }
                        else
                        {
                            uint32_t computeUnitCount = 0;
                            status =
                                pHsaModule->agent_get_info(device, static_cast<hsa_agent_info_t>(HSA_AMD_AGENT_INFO_COMPUTE_UNIT_COUNT), &computeUnitCount);

                            if (HSA_STATUS_SUCCESS != status)
                            {
                                // intentionally not setting isSuccess to false here
                                // this is non-fatal and if it fails, we will fall back to the hardcoded simd count
                                GPA_LogError("Unable to get compute unit count.");
                            }
                            else
                            {
                                hwInfo.SetNumberCUs(static_cast<size_t>(computeUnitCount));
                                uint32_t simdsPerCU = 0;
                                status = pHsaModule->agent_get_info(device, static_cast<hsa_agent_info_t>(HSA_AMD_AGENT_INFO_NUM_SIMDS_PER_CU), &simdsPerCU);

                                if (HSA_STATUS_SUCCESS != status)
                                {
                                    // intentionally not setting isSuccess to false here
                                    // this is non-fatal and if it fails, we will fall back to the hardcoded simd count
                                    GPA_LogError("Unable to get SIMDs per CU.");
                                }
                                else
                                {
                                    hwInfo.SetNumberSIMDs(static_cast<size_t>(computeUnitCount * simdsPerCU));
                                }
                            }

                            uint32_t shaderEngineCount = 0;
                            status =
                                pHsaModule->agent_get_info(device, static_cast<hsa_agent_info_t>(HSA_AMD_AGENT_INFO_NUM_SHADER_ENGINES), &shaderEngineCount);

                            if (HSA_STATUS_SUCCESS != status)
                            {
                                // intentionally not setting isSuccess to false here
                                // this is non-fatal and if it fails, we will fall back to the hardcoded shader engine count
                                GPA_LogError("Unable to get shader engine count.");
                            }
                            else
                            {
                                hwInfo.SetNumberShaderEngines(static_cast<size_t>(shaderEngineCount));
                                uint32_t ShaderArraysPerSE = 0;
                                status = pHsaModule->agent_get_info(device, static_cast<hsa_agent_info_t>(HSA_AMD_AGENT_INFO_NUM_SHADER_ARRAYS_PER_SE), &ShaderArraysPerSE);

                                if (HSA_STATUS_SUCCESS != status)
                                {
                                    // intentionally not setting isSuccess to false here
                                    // this is non-fatal and if it fails, we will fall back to the hardcoded simd count
                                    GPA_LogError("Unable to get shader arrays per shader engine.");
                                }
                                else
                                {
                                    hwInfo.SetNumberShaderArrays(static_cast<size_t>(shaderEngineCount * ShaderArraysPerSE));
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return isSuccess;
}

// TODO: this implementation doesn't do much -- is it needed?
bool ROCmGPAImplementor::VerifyAPIHwSupport(const GPAContextInfoPtr pContextInfo, const GPA_HWInfo& hwInfo) const
{
    UNREFERENCED_PARAMETER(pContextInfo);

    bool isSupported = false;

    GDT_HW_GENERATION generation = GDT_HW_GENERATION_NONE;

    if (!hwInfo.GetHWGeneration(generation))
    {
        GPA_LogError("Unable to get hardware generation.");
    }
    else
    {
        isSupported = true;
    }

    return isSupported;
}

IGPAContext* ROCmGPAImplementor::OpenAPIContext(GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags)
{
    ROCmGPAContext* pRetGpaContext = nullptr;

    HSAModule* pHsaModule = HSARTModuleLoader::Instance()->GetAPIRTModule();

    if (nullptr == pHsaModule || !pHsaModule->IsModuleLoaded())
    {
        GPA_LogError("Unable to load HSA runtime module.");
    }
    else
    {
        GPA_ROCm_Context* pROCmContext = nullptr;
        GPA_ROCm_Context  localROCmContext;

        if (ROCmGlobalFlags::Instance()->m_wasInitializeCalled)
        {
            pROCmContext           = &localROCmContext;
            hsa_queue_t* pQueue    = static_cast<hsa_queue_t*>(pContextInfo);
            pROCmContext->m_pQueue = pQueue;
            pROCmContext->m_pAgent = &ROCmGlobalFlags::Instance()->m_queueAgentMap[pQueue];
        }
        else
        {
            pROCmContext = static_cast<GPA_ROCm_Context*>(pContextInfo);
        }

        if (nullptr == pROCmContext->m_pAgent || nullptr == pROCmContext->m_pQueue)
        {
            GPA_LogError("Invalid context.");
        }
        else
        {
            ROCmGPAContext* pROCmGpaContext = new (std::nothrow) ROCmGPAContext(hwInfo, flags);

            if (nullptr == pROCmGpaContext)
            {
                GPA_LogError("Unable to allocate memory for the context.");
            }
            else
            {
                if (pROCmGpaContext->Initialize(pROCmContext))
                {
                    pRetGpaContext = pROCmGpaContext;
                }
                else
                {
                    delete pROCmGpaContext;
                    GPA_LogError("Unable to open a context.");
                }
            }
        }
    }

    return pRetGpaContext;
}

bool ROCmGPAImplementor::CloseAPIContext(GPADeviceIdentifier pDeviceIdentifier, IGPAContext* pContext)
{
    assert(nullptr != pDeviceIdentifier);
    assert(nullptr != pContext);

    if (nullptr != pContext)
    {
        delete reinterpret_cast<ROCmGPAContext*>(pContext);
        pContext = nullptr;
    }

    return (nullptr == pContext) && (nullptr != pDeviceIdentifier);
}

GPADeviceIdentifier ROCmGPAImplementor::GetDeviceIdentifierFromContextInfo(GPAContextInfoPtr pContextInfo) const
{
    return pContextInfo;
}

static const char* s_HSA_ROCP_INTERCEPT_ENV_VAR_NAME  = "ROCP_HSA_INTERCEPT";  ///< The ROCP Intercept environment variable name
static const char* s_HSA_ROCP_INTERCEPT_ENV_VAR_VALUE = "1";                   ///< The ROCP Intercept environment variable value

bool ROCmGPAImplementor::SetROCPInterceptEnvVar(std::string& strErrorMsg) const
{
    UNREFERENCED_PARAMETER(strErrorMsg);
    bool retVal = true;

#ifndef _WIN32
    int result = setenv(s_HSA_ROCP_INTERCEPT_ENV_VAR_NAME, s_HSA_ROCP_INTERCEPT_ENV_VAR_VALUE, 1);
    retVal     = (0 == result);

    if (!retVal)
    {
        strErrorMsg = "Error: Unable to enable ROCm Performance Counters in Driver";
    }
    else
    {
        strErrorMsg = "Successfully enabled ROCm Performance Counters in Driver";
    }

#endif
    return retVal;
}

bool ROCmGPAImplementor::UnsetROCPInterceptEnvVar(std::string& strErrorMsg) const
{
    UNREFERENCED_PARAMETER(strErrorMsg);
    bool retVal = true;

#ifndef _WIN32
    int result = unsetenv(s_HSA_ROCP_INTERCEPT_ENV_VAR_NAME);
    retVal     = (0 == result);

    if (!retVal)
    {
        strErrorMsg = "Error: Unable to disable ROCm Performance Counters in Driver";
    }
    else
    {
        strErrorMsg = "Successfully disabled ROCm Performance Counters in Driver";
    }

#endif

    return retVal;
}

bool ROCmGPAImplementor::SetToolsLibEnvVars()
{
    bool retVal = false;
#ifndef _WIN32
    static const char* szHSAToolsLibEnvVar = "HSA_TOOLS_LIB";
    static const char* szROCPToolLibEnvVar = "ROCP_TOOL_LIB";

    std::string curToolsLibVal;
    std::string toolsLibVal = "librocprofiler64.so";

    char* szEnvVarVal = getenv(szHSAToolsLibEnvVar);

    if (nullptr != szEnvVarVal)
    {
        curToolsLibVal.assign(szEnvVarVal);

        if (0 != curToolsLibVal.compare(0, toolsLibVal.length(), toolsLibVal))
        {
            // make sure we add librocprofiler64.so as first in the HSA_TOOLS_LIB var
            toolsLibVal.append(" ");
            toolsLibVal.append(curToolsLibVal);
        }
    }

    // get module addr of module containing this function
    Dl_info dlInfo;
    retVal = 0 != dladdr(reinterpret_cast<void*>(&ROCmGPAImplementor::SetToolsLibEnvVars), &dlInfo);

    toolsLibVal.append(" ");
    toolsLibVal.append(dlInfo.dli_fname);  // set this module as a tools lib so we can intercept hsa_queue_create

    retVal = 0 == setenv(szHSAToolsLibEnvVar, toolsLibVal.c_str(), 1);

    if (retVal)
    {
        retVal = 0 == setenv(szROCPToolLibEnvVar, dlInfo.dli_fname, 1);  // set this module as a rocprofiler lib so queue interception works
    }
#endif

    return retVal;
}
