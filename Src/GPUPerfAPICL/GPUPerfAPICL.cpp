//==============================================================================
// Copyright (c) 2009-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  OpenCL version of GPUPerfAPI
//==============================================================================

#include <math.h>
#include <map>
#include <sstream>
#include <CL/cl.h>
#include <CL/internal/cl_profile_amd.h>

#include "../GPUPerfAPI-Common/GPUPerfAPIImp.h"
#include "../GPUPerfAPI-Common/GPUPerfAPI-Private.h"
#include "../GPUPerfAPICounterGenerator/GPACounterGenerator.h"

#include "DeviceInfoUtils.h"
#include "CLRTModuleLoader.h"
#include "GPUPerfAPICL.h"

#include <vector>
#include <string>
#include <stdlib.h>
#include <assert.h>

#include "CLPerfCounterBlock.h"
#include "CLPerfCounterAMDExtension.h"
#include "CLCounterDataRequest.h"

using std::string;
using std::min;

GPA_ContextStateCL* getCurrentContext()
{
    return static_cast<GPA_ContextStateCL* >(g_pCurrentContext);
}


static bool g_bInitPerfCounterAMDExtension = false; ///< static global to track if the perf counter extension has been initialized

gpa_uint32 GPA_IMP_GetPreferredCheckResultFrequency()
{
    return 0;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_GetHWInfo(void* pContext, GPA_HWInfo* pHwInfo)
{
    assert(nullptr != pHwInfo);

    if (nullptr == pHwInfo)
    {
        GPA_LogError("Parameter 'pHwInfo' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    OpenCLModule* pOclModule = OCLRTModuleLoader::Instance()->GetAPIRTModule();

    if (nullptr == pOclModule)
    {
        GPA_LogError("OpenCL runtime module is NULL.");
        return GPA_STATUS_ERROR_FAILED;
    }

    cl_command_queue cmdQueue = static_cast<cl_command_queue>(pContext);

    cl_device_id device;

    // get device from the command queue
    if (CL_SUCCESS != pOclModule->GetCommandQueueInfo(cmdQueue, CL_QUEUE_DEVICE, sizeof(cl_device_id), &device, nullptr))
    {
        GPA_LogError("Unable to get device from command queue.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    cl_device_type deviceType;

    if (CL_SUCCESS != pOclModule->GetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(cl_device_type), &deviceType, nullptr) ||
        CL_DEVICE_TYPE_GPU != deviceType)
    {
        GPA_LogError("Unable to get device info or the device is not a GPU device.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    static const gpa_uint32 MAX_STR = 1024;
    char str[MAX_STR];

    if (CL_SUCCESS != pOclModule->GetDeviceInfo(device, CL_DEVICE_NAME, MAX_STR, str, nullptr))
    {
        GPA_LogError("Unable to get device name.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    string realDeviceName = AMDTDeviceInfoUtils::Instance()->TranslateDeviceName(str);

    std::stringstream message;
    message << "Device name from Queue: " << str << ".";
    GPA_LogDebugMessage(message.str().c_str());

    // Note for some ASICs, there isn't a revision 0, so we default to zero
    // here, but then override the revision id to a valid non-zero value below
    pHwInfo->SetRevisionID(0);

    // get the device ID
    // the string comes from maswp4p1.amd.com:1666 \\depot\stg\opencl\drivers\opencl\runtime\device\gpu\gpudefs.hpp as the static const char* TargetName[] array
    if (realDeviceName.compare("Tahiti") == 0)
    {
        pHwInfo->SetDeviceID(0x6798);
    }
    else if (realDeviceName.compare("Pitcairn") == 0)
    {
        pHwInfo->SetDeviceID(0x6818);
    }
    else if (realDeviceName.compare("Capeverde") == 0)
    {
        pHwInfo->SetDeviceID(0x6838);
    }
    else if (realDeviceName.compare("Bonaire") == 0)
    {
        pHwInfo->SetDeviceID(0x6650);
    }
    else if (realDeviceName.compare("Hawaii") == 0)
    {
        pHwInfo->SetDeviceID(0x67B0);
    }
    else if (realDeviceName.compare("Oland") == 0)
    {
        pHwInfo->SetDeviceID(0x6610);
    }
    else if (realDeviceName.compare("Hainan") == 0)
    {
        pHwInfo->SetDeviceID(0x6660);
    }
    else if (realDeviceName.compare("Kalindi") == 0)
    {
        pHwInfo->SetDeviceID(0x9830);
    }
    else if (realDeviceName.compare("Mullins") == 0)
    {
        pHwInfo->SetDeviceID(0x9855);
        pHwInfo->SetRevisionID(0x02);
    }
    else if (realDeviceName.compare("Spectre") == 0)
    {
        pHwInfo->SetDeviceID(0x1304);
    }
    else if (realDeviceName.compare("Spooky") == 0)
    {
        pHwInfo->SetDeviceID(0x1316);
    }
    else if (realDeviceName.compare("Iceland") == 0)
    {
        pHwInfo->SetDeviceID(0x6900);
    }
    else if (realDeviceName.compare("Tonga") == 0)
    {
        pHwInfo->SetDeviceID(0x6920);
    }
    else if (realDeviceName.compare("Carrizo") == 0)
    {
        pHwInfo->SetDeviceID(0x9870);
    }
    else if (realDeviceName.compare("Bristol Ridge") == 0)
    {
        pHwInfo->SetDeviceID(0x9874);
    }
    else if (realDeviceName.compare("Fiji") == 0)
    {
        pHwInfo->SetDeviceID(0x7300);
    }
    else if (realDeviceName.compare("Ellesmere") == 0)
    {
        pHwInfo->SetDeviceID(0x67DF);
        pHwInfo->SetRevisionID(0x04);
    }
    else if (realDeviceName.compare("Baffin") == 0)
    {
        pHwInfo->SetDeviceID(0x67FF);
        pHwInfo->SetRevisionID(0x08);
    }
    else if (realDeviceName.compare("gfx804") == 0)
    {
        pHwInfo->SetDeviceID(0x699F);
        pHwInfo->SetRevisionID(0x81);
    }
    else
    {
        GPA_LogError("Available device is not supported.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    pHwInfo->SetDeviceName(str);

    cl_uint vendorID;

    if (CL_SUCCESS != pOclModule->GetDeviceInfo(device, CL_DEVICE_VENDOR_ID, sizeof(cl_uint), &vendorID, nullptr))
    {
        GPA_LogError("Unable to get Vendor ID.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    pHwInfo->SetVendorID(vendorID);

#ifdef WIN32

    if (vendorID == NVIDIA_VENDOR_ID)
    {
        pHwInfo->SetHWGeneration(GDT_HW_GENERATION_NVIDIA);
    }
    else if (vendorID == INTEL_VENDOR_ID)
    {
        pHwInfo->SetHWGeneration(GDT_HW_GENERATION_INTEL);
    }

#endif

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_CompareHWInfo(void* pContext, GPA_HWInfo* pHwInfo)
{
    assert(nullptr != pHwInfo);

    if (nullptr == pHwInfo)
    {
        GPA_LogError("Parameter 'pHwInfo' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    OpenCLModule* pOclModule = OCLRTModuleLoader::Instance()->GetAPIRTModule();

    if (nullptr == pOclModule)
    {
        GPA_LogError("OpenCL runtime module is NULL.");
        return GPA_STATUS_ERROR_FAILED;
    }

    cl_command_queue cmdQueue = static_cast<cl_command_queue>(pContext);

    cl_device_id device;

    // get device from the command queue
    if (CL_SUCCESS != pOclModule->GetCommandQueueInfo(cmdQueue, CL_QUEUE_DEVICE, sizeof(cl_device_id), &device, nullptr))
    {
        GPA_LogError("Unable to get device from command queue.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    cl_device_type deviceType;

    if (CL_SUCCESS != pOclModule->GetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(cl_device_type), &deviceType, nullptr) ||
        CL_DEVICE_TYPE_GPU != deviceType)
    {
        GPA_LogError("Unable to get device info or the device is not a GPU device.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    cl_uint vendorID;

    if (CL_SUCCESS != pOclModule->GetDeviceInfo(device, CL_DEVICE_VENDOR_ID, sizeof(cl_uint), &vendorID, nullptr))
    {
        GPA_LogError("Unable to get Vendor ID.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    static const gpa_uint32 MAX_STR = 1024;
    char str[MAX_STR];

    if (CL_SUCCESS != pOclModule->GetDeviceInfo(device, CL_DEVICE_NAME, MAX_STR, str, nullptr))
    {
        GPA_LogError("Unable to get device name.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    std::stringstream message;
    message << "Device name from Queue: " << str << ".";
    GPA_LogDebugMessage(message.str().c_str());

    // don't care exactly which device ID it is,
    // as long as it matches what the API returned as the device name.
    GDT_HW_ASIC_TYPE asic = GDT_ASIC_TYPE_NONE;
    pHwInfo->GetHWAsicType(asic);

    std::string strTranslatedDeviceName = AMDTDeviceInfoUtils::Instance()->TranslateDeviceName(str);

    // get the device ID
    // the string comes from maswp4p1.amd.com:1666 \\depot\stg\opencl\drivers\opencl\runtime\device\gpu\gpudefs.hpp as the static const char* TargetName[] array
    if ((strTranslatedDeviceName.compare("Tahiti") == 0 && (asic == GDT_TAHITI_PRO || asic == GDT_TAHITI_XT)) ||
        (strTranslatedDeviceName.compare("Pitcairn") == 0 && (asic == GDT_PITCAIRN_PRO || asic == GDT_PITCAIRN_XT)) ||
        (strTranslatedDeviceName.compare("Capeverde") == 0 && (asic == GDT_CAPEVERDE_PRO || asic == GDT_CAPEVERDE_XT)) ||
        (strTranslatedDeviceName.compare("Bonaire") == 0 && asic == GDT_BONAIRE) ||
        (strTranslatedDeviceName.compare("Hawaii") == 0 && asic == GDT_HAWAII) ||
        (strTranslatedDeviceName.compare("Oland") == 0 && asic == GDT_OLAND) ||
        (strTranslatedDeviceName.compare("Hainan") == 0 && asic == GDT_HAINAN) ||
        ((strTranslatedDeviceName.compare("Kalindi") == 0 || strTranslatedDeviceName.compare("Mullins") == 0) && asic == GDT_KALINDI) ||
        (strTranslatedDeviceName.compare("Spectre") == 0 && (asic == GDT_SPECTRE || asic == GDT_SPECTRE_LITE || asic == GDT_SPECTRE_SL)) ||
        (strTranslatedDeviceName.compare("Spooky") == 0 && asic == GDT_SPOOKY) ||
        (strTranslatedDeviceName.compare("Iceland") == 0 && asic == GDT_ICELAND) ||
        (strTranslatedDeviceName.compare("Tonga") == 0 && asic == GDT_TONGA) ||
        (strTranslatedDeviceName.compare("Carrizo") == 0 && asic == GDT_CARRIZO) ||
        (strTranslatedDeviceName.compare("Bristol Ridge") == 0 && asic == GDT_CARRIZO) ||
        (strTranslatedDeviceName.compare("Fiji") == 0 && asic == GDT_FIJI) ||
        (strTranslatedDeviceName.compare("Stoney") == 0 && asic == GDT_STONEY) ||
        (strTranslatedDeviceName.compare("Ellesmere") == 0 && asic == GDT_ELLESMERE) ||
        (strTranslatedDeviceName.compare("Baffin") == 0 && asic == GDT_BAFFIN) ||
        (strTranslatedDeviceName.compare("gfx804") == 0 && asic == GDT_GFX8_0_4) ||
        (strTranslatedDeviceName.compare("AMD HSA Device") == 0 && (asic == GDT_SPOOKY || asic == GDT_SPECTRE || asic == GDT_SPECTRE_LITE || asic == GDT_SPECTRE_SL))
       )
    {
        return GPA_STATUS_OK;
    }

    GPA_LogError("Available device is not supported.");
    return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
}

//-----------------------------------------------------------------------------
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

    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_CreateContext(GPA_ContextState** ppNewContext)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == ppNewContext)
    {
        GPA_LogError("Unable to create context. Parameter 'ppNewContext' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }

    GPA_ContextStateCL* pContext = new(std::nothrow) GPA_ContextStateCL;

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

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_Initialize()
{
    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_IMP_Destroy()
{
    return GPA_STATUS_OK;
}

//-----------------------------------------------------------------------------
// Startup / exit
GPA_Status GPA_IMP_OpenContext(void* pContext)
{
    if (nullptr == pContext)
    {
        GPA_LogError("Parameter 'pContext' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (!OCLRTModuleLoader::Instance()->IsModuleLoaded())
    {
        GPA_LogError("Unable to load and initialize OpenCL runtime module.");
        return GPA_STATUS_ERROR_FAILED;
    }

    OpenCLModule* pOclModule = OCLRTModuleLoader::Instance()->GetAPIRTModule();

    if (nullptr == pOclModule)
    {
        GPA_LogError("OpenCL runtime module is NULL.");
        return GPA_STATUS_ERROR_FAILED;
    }

    // set the device
    cl_command_queue cmdQueue = static_cast<cl_command_queue>(pContext);

    // get device from the command queue and store it
    cl_int status = pOclModule->GetCommandQueueInfo(cmdQueue,
                                                    CL_QUEUE_DEVICE,
                                                    sizeof(cl_device_id),
                                                    &getCurrentContext()->m_clDevice,
                                                    nullptr);

    if (CL_SUCCESS != status)
    {
        GPA_LogError("Unable to get device from command queue.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    // initialize AMD perf counter's extension
    if (!g_bInitPerfCounterAMDExtension)
    {
        cl_platform_id platform;

        status = pOclModule->GetDeviceInfo(getCurrentContext()->m_clDevice,
                                           CL_DEVICE_PLATFORM,
                                           sizeof(cl_platform_id),
                                           &platform,
                                           nullptr);

        if (CL_SUCCESS != status)
        {
            GPA_LogError("Unable to get platform from device.");
            return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
        }

        if (!InitPerfCounterAMDExtension(platform))
        {
            GPA_LogError("Unable to initialize the PerfCounter AMD Extension.");
            return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
        }

        g_bInitPerfCounterAMDExtension = true;
    }

    GDT_HW_GENERATION gen = GDT_HW_GENERATION_NONE;

    if (getCurrentContext()->m_hwInfo.GetHWGeneration(gen) == false)
    {
        GPA_LogError("Unable to get hardware generation.");
        return GPA_STATUS_ERROR_FAILED;
    }

    gpa_uint32 vendorId = 0;

    if (getCurrentContext()->m_hwInfo.GetVendorID(vendorId) == false)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    gpa_uint32 deviceId = 0;

    if (getCurrentContext()->m_hwInfo.GetDeviceID(deviceId) == false)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    gpa_uint32 revisionId = 0;

    if (getCurrentContext()->m_hwInfo.GetRevisionID(revisionId) == false)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    return GenerateCounters(GPA_API_OPENCL, vendorId, deviceId, revisionId, (GPA_ICounterAccessor**) & (getCurrentContext()->m_pCounterAccessor), &(getCurrentContext()->m_pCounterScheduler));
}


GPA_Status GPA_IMP_CloseContext()
{
    return GPA_STATUS_OK;
}


// Context
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

    return GPA_STATUS_OK;
}


GPA_Status GPA_IMP_EndSample()
{
    return GPA_STATUS_OK;
}


gpa_uint32 GPA_IMP_GetDefaultMaxSessions()
{
    // maximum latency is 4 for dx10-capable cards
    return 4;
}


GPA_DataRequest* GPA_IMP_CreateDataRequest()
{
    return new(std::nothrow) CLCounterDataRequest();
}
