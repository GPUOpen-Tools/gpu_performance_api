//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief HSA GPA Implementation
//==============================================================================

#include <assert.h>
#include <sstream>

#include <ADLUtil.h>
#include <DeviceInfoUtils.h>

#include "HSARTModuleLoader.h"
#include "GPUPerfAPI-HSA.h"
#include "GPUPerfAPIHSAGlobals.h"
#include "HSAGPAImplementor.h"
#include "HSAGPAContext.h"

IGPAImplementor* s_pGpaImp = HSAGPAImplementor::Instance();

GPA_Status HSAGPAImplementor::Initialize(GPA_InitializeFlags flags)
{
    GPA_Status gpaStatus = GPAImplementor::Initialize(flags);

    if (GPA_STATUS_OK == gpaStatus)
    {
        HSAGlobalFlags::Instance()->m_wasInitializeCalled = true;

        if (!HSAGlobalFlags::Instance()->m_softCPModeEnabled)
        {
            std::string strErrorMessage;

            if (!SetHSASoftCPEnvVar(strErrorMessage))
            {
                GPA_LogError(strErrorMessage.c_str());
                gpaStatus = GPA_STATUS_ERROR_FAILED;
            }
            else
            {
                HSAGlobalFlags::Instance()->m_softCPModeEnabled = true;
            }
        }

        if (!HSAGlobalFlags::Instance()->m_isToolsLibSet)
        {
            if (!SetHSAToolsLibEnvVar())
            {
                GPA_LogError("Unable to set Tools Lib Environment Variable.");
                gpaStatus = GPA_STATUS_ERROR_FAILED;
            }
            else
            {
                HSAGlobalFlags::Instance()->m_isToolsLibSet = true;
            }
        }
    }

    return gpaStatus;
}

GPA_Status HSAGPAImplementor::Destroy()
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

    GPA_Status gpaStatus = GPAImplementor::Destroy();

    return gpaStatus;
}

GPA_API_Type HSAGPAImplementor::GetAPIType() const
{
    return GPA_API_HSA;
}

bool HSAGPAImplementor::GetHwInfoFromAPI(const GPAContextInfoPtr pContextInfo,
                                         GPA_HWInfo& hwInfo) const
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
        GPA_HSA_Context* pHSAContext = nullptr;
        GPA_HSA_Context localHSAContext;

        if (HSAGlobalFlags::Instance()->m_wasInitializeCalled)
        {
            pHSAContext = &localHSAContext;
            hsa_queue_t* pQueue = static_cast<hsa_queue_t*>(pContextInfo);
            pHSAContext->m_pQueue = pQueue;
            pHSAContext->m_pAgent = &HSAGlobalFlags::Instance()->m_queueAgentMap[pQueue];
        }
        else
        {
            pHSAContext = static_cast<GPA_HSA_Context*>(pContextInfo);
        }

        if (nullptr == pHSAContext->m_pAgent)
        {
            GPA_LogError("Invalid context.");
            isSuccess = false;
        }
        else
        {
            const hsa_agent_t device = *pHSAContext->m_pAgent;

            //----------------------------------------------------
            // Check device type
            hsa_device_type_t deviceType;
            hsa_status_t status = pHsaModule->agent_get_info(device, HSA_AGENT_INFO_DEVICE, &deviceType);

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
                        bool isDeviceSupported = false;

                        if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(deviceId, REVISION_ID_ANY, cardInfo))
                        {
                            if (static_cast<unsigned int>(cardInfo.m_generation) >= static_cast<unsigned int>(GDT_HW_GENERATION_SEAISLAND))
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
                            status = pHsaModule->agent_get_info(device, static_cast<hsa_agent_info_t>(HSA_AMD_AGENT_INFO_COMPUTE_UNIT_COUNT), &computeUnitCount);

                            if (HSA_STATUS_SUCCESS != status)
                            {
                                // intentionally not setting isSuccess to false here
                                // this is non-fatal and if it fails, we will fall back to the hardcoded simd count
                                GPA_LogError("Unable to get compute unit count.");
                            }
                            else
                            {
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
                                    hwInfo.SetNumberSIMDs(computeUnitCount * simdsPerCU);
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
bool HSAGPAImplementor::VerifyAPIHwSupport(const GPAContextInfoPtr pContextInfo,
                                           const GPA_HWInfo& hwInfo) const
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

IGPAContext* HSAGPAImplementor::OpenAPIContext(GPAContextInfoPtr pContextInfo,
                                               GPA_HWInfo& hwInfo,
                                               GPA_OpenContextFlags flags)
{
    HSAGPAContext* pRetGpaContext = nullptr;

    HSAModule* pHsaModule = HSARTModuleLoader::Instance()->GetAPIRTModule();

    if (nullptr == pHsaModule || !pHsaModule->IsModuleLoaded())
    {
        GPA_LogError("Unable to load HSA runtime module.");
    }
    else
    {
        HSAToolsRTModule* pHsaToolsRTModule = HSAToolsRTModuleLoader::Instance()->GetAPIRTModule();

        if (nullptr == pHsaToolsRTModule || !pHsaToolsRTModule->IsModuleLoaded())
        {
            GPA_LogError("Unable to load HSA tools runtime module.");
        }
        else
        {
            GPA_HSA_Context* pHSAContext = nullptr;
            GPA_HSA_Context localHSAContext;

            if (HSAGlobalFlags::Instance()->m_wasInitializeCalled)
            {
                pHSAContext = &localHSAContext;
                hsa_queue_t* pQueue = static_cast<hsa_queue_t*>(pContextInfo);
                pHSAContext->m_pQueue = pQueue;
                pHSAContext->m_pAgent = &HSAGlobalFlags::Instance()->m_queueAgentMap[pQueue];
            }
            else
            {
                pHSAContext = static_cast<GPA_HSA_Context*>(pContextInfo);
            }

            if (nullptr == pHSAContext->m_pAgent || nullptr == pHSAContext->m_pQueue)
            {
                GPA_LogError("Invalid context.");
            }
            else
            {
                HSAGPAContext* pHsaGpaContext = new(std::nothrow) HSAGPAContext(hwInfo, flags);

                if (nullptr == pHsaGpaContext)
                {
                    GPA_LogError("Unable to allocate memory for the context.");
                }
                else
                {
                    if (pHsaGpaContext->Initialize(pHSAContext))
                    {
                        pRetGpaContext = pHsaGpaContext;
                    }
                    else
                    {
                        delete pHsaGpaContext;
                        GPA_LogError("Unable to open a context.");
                    }
                }
            }
        }
    }

    return pRetGpaContext;
}

bool HSAGPAImplementor::CloseAPIContext(GPADeviceIdentifier pDeviceIdentifier, IGPAContext* pContext)
{
    assert(nullptr != pDeviceIdentifier);
    assert(nullptr != pContext);

    if (nullptr != pContext)
    {
        delete reinterpret_cast<HSAGPAContext*>(pContext);
    }

    return (nullptr != pContext) && (nullptr != pDeviceIdentifier);
}

GPADeviceIdentifier HSAGPAImplementor::GetDeviceIdentifierFromContextInfo(GPAContextInfoPtr pContextInfo) const
{
    return pContextInfo;
}

static const char* s_HSA_SOFTCP_ENV_VAR_NAME = "HSA_EMULATE_AQL"; ///< The SoftCP environment variable name
static const char* s_HSA_SOFTCP_ENV_VAR_VALUE = "1";              ///< The SoftCP environment variable value

bool HSAGPAImplementor::SetHSASoftCPEnvVar(std::string& strErrorMsg) const
{
    UNREFERENCED_PARAMETER(strErrorMsg);
    bool retVal = true;

#ifndef _WIN32
    int result = setenv(s_HSA_SOFTCP_ENV_VAR_NAME, s_HSA_SOFTCP_ENV_VAR_VALUE, 1);
    retVal = (0 == result);

    if (!retVal)
    {
        strErrorMsg = "Error: Unable to enable HSA Performance Counters in Driver";
    }
    else
    {
        strErrorMsg = "Successfully enabled HSA Performance Counters in Driver";
    }

#endif
    return retVal;
}

bool HSAGPAImplementor::UnsetHSASoftCPEnvVar(std::string strErrorMsg) const
{
    UNREFERENCED_PARAMETER(strErrorMsg);
    bool retVal = true;

#ifndef _WIN32
    int result = unsetenv(s_HSA_SOFTCP_ENV_VAR_NAME);
    retVal = (0 == result);

    if (!retVal)
    {
        strErrorMsg = "Error: Unable to disable HSA Performance Counters in Driver";
    }
    else
    {
        strErrorMsg = "Successfully disabled HSA Performance Counters in Driver";
    }

#endif

    return retVal;
}

/// Sets the necessary environment variable to enable the HSA runtime Tools lib
/// \return true on success
bool HSAGPAImplementor::SetHSAToolsLibEnvVar() const
{
    bool retVal = false;
#ifndef _WIN32
    static const char* szHSAToolsLibEnvVar = "HSA_TOOLS_LIB";

    std::string curToolsLibVal;
    std::string toolsLibVal = "libhsa-runtime-tools64.so.1";

    char* szEnvVarVal = getenv(szHSAToolsLibEnvVar);

    if (nullptr != szEnvVarVal)
    {
        curToolsLibVal.assign(szEnvVarVal);

        if (0 != curToolsLibVal.compare(0, toolsLibVal.length(), toolsLibVal))
        {
            // make sure libhsa-runtime-tools64.so.1 is first in the HSA_TOOLS_LIB var
            toolsLibVal.append(" ");
            toolsLibVal.append(curToolsLibVal);
        }
    }

    Dl_info dlInfo;
    retVal = 0 != dladdr(reinterpret_cast<void*>(&HSAGPAImplementor::SetHSAToolsLibEnvVar), &dlInfo);

    toolsLibVal.append(" ");
    toolsLibVal.append(dlInfo.dli_fname);

    retVal = 0 == setenv(szHSAToolsLibEnvVar, toolsLibVal.c_str(), 1);
#endif

    return retVal;
}
