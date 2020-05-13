//==============================================================================
// Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief CL GPA Implementation
//==============================================================================

#include <assert.h>

#include <CL/cl.h>

#include <ADLUtil.h>
#include <DeviceInfoUtils.h>

#include "cl_rt_module_loader.h"

#include "cl_gpa_implementor.h"
#include "cl_gpa_context.h"
#include "cl_perf_counter_amd_extension.h"

#include "gpa_counter_generator_cl.h"
#include "gpa_counter_scheduler_cl.h"

IGPAImplementor* s_pGpaImp = CLGPAImplementor::Instance();
static GPA_CounterGeneratorCL s_generatorCL;  ///< static instance of CL generator
static GPA_CounterSchedulerCL s_schedulerCL;  ///< static instance of CL scheduler

GPA_API_Type CLGPAImplementor::GetAPIType() const
{
    return GPA_API_OPENCL;
}

bool CLGPAImplementor::GetHwInfoFromAPI(const GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo) const
{
    bool isSuccess = true;

    OpenCLModule* pOclModule = OCLRTModuleLoader::Instance()->GetAPIRTModule();

    if (nullptr == pOclModule)
    {
        GPA_LogError("OpenCL runtime module is NULL.");
        isSuccess = false;
    }
    else
    {
        cl_command_queue cmdQueue = static_cast<cl_command_queue>(pContextInfo);

        cl_device_id device;

        // get device from the command queue
        if (CL_SUCCESS != pOclModule->GetCommandQueueInfo(cmdQueue, CL_QUEUE_DEVICE, sizeof(cl_device_id), &device, nullptr))
        {
            GPA_LogError("Unable to get device from command queue.");
            isSuccess = false;
        }
        else
        {
            cl_device_type deviceType;

            if (CL_SUCCESS != pOclModule->GetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(cl_device_type), &deviceType, nullptr) ||
                CL_DEVICE_TYPE_GPU != deviceType)
            {
                GPA_LogError("Unable to get device info or the device is not a GPU device.");
                isSuccess = false;
            }
            else
            {
                size_t      deviceNameSize = 0;
                std::string deviceNameStr;

                bool deviceNameValid = CL_SUCCESS == pOclModule->GetDeviceInfo(device, CL_DEVICE_NAME, 0, nullptr, &deviceNameSize);

                if (!deviceNameValid)
                {
                    GPA_LogError("Unable to get device name.");
                    isSuccess = false;
                }
                else
                {
                    char* pDeviceName = new char[deviceNameSize];

                    if (nullptr == pDeviceName)
                    {
                        GPA_LogError("Unable to allocate memory for the device name.");
                        return false;
                    }

                    deviceNameValid = CL_SUCCESS == pOclModule->GetDeviceInfo(device, CL_DEVICE_NAME, deviceNameSize, pDeviceName, &deviceNameSize);

                    if (!deviceNameValid)
                    {
                        GPA_LogError("Unable to get device name.");
                        isSuccess = false;
                    }
                    else
                    {
                        deviceNameStr.assign(pDeviceName);
                    }

                    delete[] pDeviceName;

                    if (deviceNameValid)
                    {
                        std::stringstream message;
                        message << "Device name from Queue: " << deviceNameStr << ".";
                        GPA_LogDebugMessage(message.str().c_str());

                        bool        boardNameValid = CL_SUCCESS == pOclModule->GetDeviceInfo(device, CL_DEVICE_BOARD_NAME_AMD, 0, nullptr, &deviceNameSize);
                        std::string boardNameStr;

                        if (boardNameValid)
                        {
                            char* pBoardName = new char[deviceNameSize];

                            if (nullptr == pBoardName)
                            {
                                GPA_LogError("Unable to allocate memory for the board name.");
                                return false;
                            }

                            boardNameValid =
                                CL_SUCCESS == pOclModule->GetDeviceInfo(device, CL_DEVICE_BOARD_NAME_AMD, deviceNameSize, pBoardName, &deviceNameSize);

                            if (boardNameValid)
                            {
                                boardNameStr.assign(pBoardName);
                            }

                            delete[] pBoardName;
                        }

                        std::vector<GDT_GfxCardInfo> cardListFromName;
                        bool cardFoundByName  = AMDTDeviceInfoUtils::Instance()->GetAllCardsWithName(deviceNameStr.c_str(), cardListFromName);
                        bool cardFound        = false;
                        bool preciseCardFound = false;

                        cl_uint pcieDeviceId  = 0;
                        bool    isPcieIdValid = false;

                        if (CL_SUCCESS == pOclModule->GetDeviceInfo(device, CL_DEVICE_PCIE_ID_AMD, sizeof(cl_uint), &pcieDeviceId, nullptr) &&
                            0 != pcieDeviceId)
                        {
                            // the CL_DEVICE_ID_AMD query can return a bogus device id in some drivers
                            std::vector<GDT_GfxCardInfo> cardListDeviceId;
                            isPcieIdValid = AMDTDeviceInfoUtils::Instance()->GetAllCardsWithDeviceId(pcieDeviceId, cardListDeviceId);

                            if (isPcieIdValid)
                            {
                                hwInfo.SetDeviceID(pcieDeviceId);
                                hwInfo.SetRevisionID(REVISION_ID_ANY);

                                for (auto card = cardListDeviceId.begin(); card != cardListDeviceId.end() && !preciseCardFound; ++card)
                                {
                                    cardFound = true;

                                    if (boardNameValid)
                                    {
                                        if ((0 == boardNameStr.compare(card->m_szMarketingName)) && (0 == deviceNameStr.compare(card->m_szCALName)))
                                        {
                                            hwInfo.SetRevisionID(static_cast<gpa_uint32>(card->m_revID));
                                            preciseCardFound = true;
                                        }
                                    }
                                }
                            }

                            if (!preciseCardFound && cardFoundByName)
                            {
                                for (auto card = cardListFromName.begin(); card != cardListFromName.end() && !preciseCardFound; ++card)
                                {
                                    if (isPcieIdValid && card->m_deviceID != pcieDeviceId)
                                    {
                                        // skip cards where the pcie device id is incorrect
                                        continue;
                                    }

                                    hwInfo.SetDeviceID(static_cast<gpa_uint32>(card->m_deviceID));
                                    hwInfo.SetRevisionID(static_cast<gpa_uint32>(card->m_revID));
                                    cardFound = true;

                                    if (boardNameValid)
                                    {
                                        if (0 == boardNameStr.compare(card->m_szMarketingName))
                                        {
                                            preciseCardFound = true;
                                        }
                                    }
                                }
                            }

                            if (!cardFound)
                            {
                                GPA_LogError("Unable to determine device id.");
                                isSuccess = false;
                            }

                            if (!preciseCardFound)
                            {
                                GPA_LogMessage("Unable to determine precise device. Best guess device identified.");
                            }
                        }
                        else
                        {
                            // unable to get device id from OCL runtime -- just use  first item in cardListFromName
                            if (cardFoundByName)
                            {
                                GPA_LogMessage("Unable to determine precise device. Best guess device identified.");
                                hwInfo.SetDeviceID(static_cast<gpa_uint32>(cardListFromName[0].m_deviceID));
                                hwInfo.SetRevisionID(static_cast<gpa_uint32>(cardListFromName[0].m_revID));
                            }
                            else
                            {
                                GPA_LogError("Unable to determine device id.");
                                isSuccess = false;
                            }
                        }
                    }

                    if (isSuccess)
                    {
                        hwInfo.SetDeviceName(deviceNameStr.c_str());

                        cl_uint vendorID;

                        if (CL_SUCCESS != pOclModule->GetDeviceInfo(device, CL_DEVICE_VENDOR_ID, sizeof(cl_uint), &vendorID, nullptr))
                        {
                            GPA_LogError("Unable to get Vendor ID.");
                            isSuccess = false;
                        }

                        hwInfo.SetVendorID(vendorID);

#ifdef WIN32

                        if (NVIDIA_VENDOR_ID == vendorID)
                        {
                            hwInfo.SetHWGeneration(GDT_HW_GENERATION_NVIDIA);
                        }
                        else if (INTEL_VENDOR_ID == vendorID)
                        {
                            hwInfo.SetHWGeneration(GDT_HW_GENERATION_INTEL);
                        }
                        else

#endif
                        {
                            hwInfo.UpdateDeviceInfoBasedOnDeviceID();
                        }

                        cl_uint numComputeUnits = 0;

                        if (CL_SUCCESS != pOclModule->GetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &numComputeUnits, nullptr))
                        {
                            GPA_LogError("Unable to get number of compute units.");
                            isSuccess = false;
                        }
                        else
                        {
                            GDT_HW_GENERATION generation;

                            if (hwInfo.GetHWGeneration(generation) && GDT_HW_GENERATION_GFX10 <= generation)
                            {
                                // Starting on GFX10, the OCL runtime reports the number of WGPs rather than number of CUs for the CL_DEVICE_MAX_COMPUTE_UNITS query
                                numComputeUnits *= 2;
                            }

                            hwInfo.SetNumberCUs(static_cast<size_t>(numComputeUnits));

                            cl_uint numSIMDsPerComputeUnit = 0;

                            if (CL_SUCCESS !=
                                pOclModule->GetDeviceInfo(device, CL_DEVICE_SIMD_PER_COMPUTE_UNIT_AMD, sizeof(cl_uint), &numSIMDsPerComputeUnit, nullptr))
                            {
                                GPA_LogError("Unable to get number of SIMDS per compute unit.");
                                isSuccess = false;
                            }
                            else
                            {
                                hwInfo.SetNumberSIMDs(static_cast<size_t>(numComputeUnits) * numSIMDsPerComputeUnit);
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
bool CLGPAImplementor::VerifyAPIHwSupport(const GPAContextInfoPtr pContextInfo, const GPA_HWInfo& hwInfo) const
{
    UNREFERENCED_PARAMETER(pContextInfo);

    bool isSupported = false;

    GDT_HW_GENERATION generation = GDT_HW_GENERATION_NONE;

    if (hwInfo.GetHWGeneration(generation) == false)
    {
        GPA_LogError("Unable to get hardware generation.");
    }
    else
    {
        isSupported = true;
    }

    return isSupported;
}

IGPAContext* CLGPAImplementor::OpenAPIContext(GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags)
{
    CLGPAContext* pRetGpaContext = nullptr;

    cl_command_queue clCmdQueue = static_cast<cl_command_queue>(pContextInfo);

    CLGPAContext* pCLGpaContext = new (std::nothrow) CLGPAContext(clCmdQueue, hwInfo, flags);

    if (nullptr == pCLGpaContext)
    {
        GPA_LogError("Unable to allocate memory for the context.");
    }
    else
    {
        OpenCLModule* pOclModule = OCLRTModuleLoader::Instance()->GetAPIRTModule();

        cl_int clStatus = CL_SUCCESS;

        if (nullptr == pOclModule)
        {
            GPA_LogError("OpenCL runtime module is NULL.");
        }
        else
        {
            cl_device_id clDeviceId;
            // get device from the command queue and store it
            clStatus = pOclModule->GetCommandQueueInfo(clCmdQueue, CL_QUEUE_DEVICE, sizeof(cl_device_id), &clDeviceId, nullptr);

            if (CL_SUCCESS == clStatus)
            {
                // initialize AMD perf counter's extension
                if (!m_initPerfCounterAMDExtension)
                {
                    cl_platform_id platform;

                    clStatus = pOclModule->GetDeviceInfo(clDeviceId, CL_DEVICE_PLATFORM, sizeof(cl_platform_id), &platform, nullptr);

                    if (CL_SUCCESS != clStatus)
                    {
                        GPA_LogError("Unable to get platform from device.");
                    }
                    else if (!InitPerfCounterAMDExtension(platform))
                    {
                        GPA_LogError("Unable to initialize the PerfCounter AMD Extension.");
                    }
                    else
                    {
                        m_initPerfCounterAMDExtension = true;
                    }
                }

                if (m_initPerfCounterAMDExtension)
                {
                    if (pCLGpaContext->Initialize(clDeviceId))
                    {
                        pRetGpaContext = pCLGpaContext;
                    }
                    else
                    {
                        delete pCLGpaContext;
                        GPA_LogError("Unable to open a context.");
                    }
                }
            }
            else
            {
                GPA_LogError("Unable to query CL device from CL command queue.");
            }
        }
    }

    return pRetGpaContext;
}

bool CLGPAImplementor::CloseAPIContext(GPADeviceIdentifier pDeviceIdentifier, IGPAContext* pContext)
{
    assert(nullptr != pDeviceIdentifier);
    assert(nullptr != pContext);

    if (nullptr != pContext)
    {
        delete reinterpret_cast<CLGPAContext*>(pContext);
        pContext = nullptr;
    }

    return (nullptr == pContext) && (nullptr != pDeviceIdentifier);
}

GPADeviceIdentifier CLGPAImplementor::GetDeviceIdentifierFromContextInfo(GPAContextInfoPtr pContextInfo) const
{
    return pContextInfo;
}
