//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief CL GPA Implementation
//==============================================================================

#include <assert.h>

#include <CL/cl.h>
#include <CL/internal/cl_profile_amd.h>

#include <ADLUtil.h>
#include <DeviceInfoUtils.h>

#include "CLRTModuleLoader.h"

#include "CLGPAImplementor.h"
#include "CLGPAContext.h"
#include "CLPerfCounterAMDExtension.h"

IGPAImplementor* s_pGpaImp = CLGPAImplementor::Instance();

GPA_API_Type CLGPAImplementor::GetAPIType() const
{
    return GPA_API_OPENCL;
}

bool CLGPAImplementor::GetHwInfoFromAPI(const GPAContextInfoPtr pContextInfo,
                                        GPA_HWInfo& hwInfo) const
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

                static const gpa_uint32 MAX_STR = 1024;
                char str[MAX_STR];

                if (CL_SUCCESS != pOclModule->GetDeviceInfo(device, CL_DEVICE_NAME, MAX_STR, str, nullptr))
                {
                    GPA_LogError("Unable to get device name.");
                    isSuccess = false;
                }
                else
                {
                    string realDeviceName = AMDTDeviceInfoUtils::Instance()->TranslateDeviceName(str);

                    std::stringstream message;
                    message << "Device name from Queue: " << str << ".";
                    GPA_LogDebugMessage(message.str().c_str());

                    // Note for some ASICs, there isn't a revision 0, so we default to zero
                    // here, but then override the revision id to a valid non-zero value below
                    hwInfo.SetRevisionID(0);

                    // get the device ID
                    // the string comes from stg\opencl\drivers\opencl\runtime\device\gpu\gpudefs.hpp as the static const char* TargetName[] array
                    if (realDeviceName.compare("Tahiti") == 0)
                    {
                        hwInfo.SetDeviceID(0x6798);
                    }
                    else if (realDeviceName.compare("Pitcairn") == 0)
                    {
                        hwInfo.SetDeviceID(0x6818);
                    }
                    else if (realDeviceName.compare("Capeverde") == 0)
                    {
                        hwInfo.SetDeviceID(0x6838);
                    }
                    else if (realDeviceName.compare("Bonaire") == 0)
                    {
                        hwInfo.SetDeviceID(0x6650);
                    }
                    else if (realDeviceName.compare("Hawaii") == 0)
                    {
                        hwInfo.SetDeviceID(0x67B0);
                    }
                    else if (realDeviceName.compare("Oland") == 0)
                    {
                        hwInfo.SetDeviceID(0x6610);
                    }
                    else if (realDeviceName.compare("Hainan") == 0)
                    {
                        hwInfo.SetDeviceID(0x6660);
                    }
                    else if (realDeviceName.compare("Kalindi") == 0)
                    {
                        hwInfo.SetDeviceID(0x9830);
                    }
                    else if (realDeviceName.compare("Mullins") == 0)
                    {
                        hwInfo.SetDeviceID(0x9855);
                        hwInfo.SetRevisionID(0x02);
                    }
                    else if (realDeviceName.compare("Spectre") == 0)
                    {
                        hwInfo.SetDeviceID(0x1304);
                    }
                    else if (realDeviceName.compare("Spooky") == 0)
                    {
                        hwInfo.SetDeviceID(0x1316);
                    }
                    else if (realDeviceName.compare("Iceland") == 0)
                    {
                        hwInfo.SetDeviceID(0x6900);
                    }
                    else if (realDeviceName.compare("Tonga") == 0)
                    {
                        hwInfo.SetDeviceID(0x6920);
                    }
                    else if (realDeviceName.compare("Carrizo") == 0)
                    {
                        hwInfo.SetDeviceID(0x9870);
                    }
                    else if (realDeviceName.compare("Bristol Ridge") == 0)
                    {
                        hwInfo.SetDeviceID(0x9874);
                    }
                    else if (realDeviceName.compare("Fiji") == 0)
                    {
                        hwInfo.SetDeviceID(0x7300);
                    }
                    else if (realDeviceName.compare("Ellesmere") == 0)
                    {
                        hwInfo.SetDeviceID(0x67DF);
                        hwInfo.SetRevisionID(0x04);
                    }
                    else if (realDeviceName.compare("Baffin") == 0)
                    {
                        hwInfo.SetDeviceID(0x67FF);
                        hwInfo.SetRevisionID(0x08);
                    }
                    else if (realDeviceName.compare("gfx804") == 0)
                    {
                        hwInfo.SetDeviceID(0x699F);
                        hwInfo.SetRevisionID(0x81);
                    }
                    else if (realDeviceName.compare("gfx900") == 0)
                    {
                        hwInfo.SetDeviceID(0x687F);
                        hwInfo.SetRevisionID(0xC1);
                    }
                    else if (realDeviceName.compare("gfx901") == 0)
                    {
                        hwInfo.SetDeviceID(0x687F);
                        hwInfo.SetRevisionID(0xC1);
                    }
                    else if (realDeviceName.compare("gfx902") == 0)
                    {
                        hwInfo.SetDeviceID(0x15DD);
                        hwInfo.SetRevisionID(0xC3);
                    }
                    else if (realDeviceName.compare("gfx903") == 0)
                    {
                        hwInfo.SetDeviceID(0x15DD);
                        hwInfo.SetRevisionID(0xC3);
                    }
                    else
                    {
                        GPA_LogError("Available device is not supported.");
                        isSuccess = false;
                    }

                    if (isSuccess)
                    {
                        hwInfo.SetDeviceName(str);

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

#endif

                    }
                }
            }
        }
    }


    return isSuccess;
}

bool CLGPAImplementor::VerifyAPIHwSupport(const GPAContextInfoPtr pContextInfo,
                                          const GPA_HWInfo& hwInfo) const
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

IGPAContext* CLGPAImplementor::OpenAPIContext(GPAContextInfoPtr pContextInfo,
                                              GPA_HWInfo& pHwInfo,
                                              GPA_OpenContextFlags flags)
{
    CLGPAContext* pRetGpaContext = nullptr;

    cl_command_queue clCmdQueue = static_cast<cl_command_queue>(pContextInfo);

    CLGPAContext* pCLGpaContext = new(std::nothrow) CLGPAContext(clCmdQueue, pHwInfo, flags);

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
            clStatus = pOclModule->GetCommandQueueInfo(clCmdQueue,
                                                       CL_QUEUE_DEVICE,
                                                       sizeof(cl_device_id),
                                                       &clDeviceId,
                                                       nullptr);

            if (CL_SUCCESS == clStatus)
            {
                // initialize AMD perf counter's extension
                if (!m_initPerfCounterAMDExtension)
                {
                    cl_platform_id platform;

                    clStatus = pOclModule->GetDeviceInfo(clDeviceId,
                                                         CL_DEVICE_PLATFORM,
                                                         sizeof(cl_platform_id),
                                                         &platform,
                                                         nullptr);

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


// TODO: what is GPADeviceIdentifier in OpenCL??
bool CLGPAImplementor::CloseAPIContext(GPADeviceIdentifier pDeviceIdentifier, IGPAContext* pGpaContext)
{
    assert(nullptr != pDeviceIdentifier);
    assert(nullptr != pGpaContext);

    if (nullptr != pDeviceIdentifier)
    {
    }

    if (nullptr != pGpaContext)
    {
        delete reinterpret_cast<CLGPAContext*>(pGpaContext);
    }

    return (nullptr != pGpaContext) && (nullptr != pDeviceIdentifier);
}

GPADeviceIdentifier CLGPAImplementor::GetDeviceIdentifierFromContextInfo(GPAContextInfoPtr pContextInfo) const
{
    // TODO: what should be returned here?
    return pContextInfo;
}
