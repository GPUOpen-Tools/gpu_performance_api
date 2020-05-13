//==============================================================================
// Copyright (c) 2009-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A utility function to get the AMD internal performance counters' interface via
///         clGetExtensionFunctionAddress.
//==============================================================================

#include <CL/cl.h>
#include <CL/internal/cl_profile_amd.h>
#include "cl_perf_counter_amd_extension.h"
#include "cl_rt_module_loader.h"

pfn_clCreatePerfCounterAMD       my_clCreatePerfCounterAMD       = nullptr;
pfn_clReleasePerfCounterAMD      my_clReleasePerfCounterAMD      = nullptr;
pfn_clRetainPerfCounterAMD       my_clRetainPerfCounterAMD       = nullptr;
pfn_clEnqueueBeginPerfCounterAMD my_clEnqueueBeginPerfCounterAMD = nullptr;
pfn_clEnqueueEndPerfCounterAMD   my_clEnqueueEndPerfCounterAMD   = nullptr;
pfn_clGetPerfCounterInfoAMD      my_clGetPerfCounterInfoAMD      = nullptr;
pfn_clSetDeviceClockModeAMD      my_clSetDeviceClockModeAMD      = nullptr;

bool InitPerfCounterAMDExtension(cl_platform_id platform)
{
    OpenCLModule* pOclModule = OCLRTModuleLoader::Instance()->GetAPIRTModule();

    if (nullptr == pOclModule)
    {
        return false;
    }

    if (nullptr == my_clCreatePerfCounterAMD)
    {
        my_clCreatePerfCounterAMD = (pfn_clCreatePerfCounterAMD)pOclModule->GetExtensionFunctionAddressForPlatform(platform, "clCreatePerfCounterAMD");

        if (nullptr == my_clCreatePerfCounterAMD)
        {
            return false;
        }
    }

    if (nullptr == my_clReleasePerfCounterAMD)
    {
        my_clReleasePerfCounterAMD = (pfn_clReleasePerfCounterAMD)pOclModule->GetExtensionFunctionAddressForPlatform(platform, "clReleasePerfCounterAMD");

        if (nullptr == my_clReleasePerfCounterAMD)
        {
            return false;
        }
    }

    if (nullptr == my_clRetainPerfCounterAMD)
    {
        my_clRetainPerfCounterAMD = (pfn_clRetainPerfCounterAMD)pOclModule->GetExtensionFunctionAddressForPlatform(platform, "clRetainPerfCounterAMD");

        if (nullptr == my_clRetainPerfCounterAMD)
        {
            return false;
        }
    }

    if (nullptr == my_clEnqueueBeginPerfCounterAMD)
    {
        my_clEnqueueBeginPerfCounterAMD =
            (pfn_clEnqueueBeginPerfCounterAMD)pOclModule->GetExtensionFunctionAddressForPlatform(platform, "clEnqueueBeginPerfCounterAMD");

        if (nullptr == my_clEnqueueBeginPerfCounterAMD)
        {
            return false;
        }
    }

    if (nullptr == my_clEnqueueEndPerfCounterAMD)
    {
        my_clEnqueueEndPerfCounterAMD =
            (pfn_clEnqueueEndPerfCounterAMD)pOclModule->GetExtensionFunctionAddressForPlatform(platform, "clEnqueueEndPerfCounterAMD");

        if (nullptr == my_clEnqueueEndPerfCounterAMD)
        {
            return false;
        }
    }

    if (nullptr == my_clGetPerfCounterInfoAMD)
    {
        my_clGetPerfCounterInfoAMD = (pfn_clGetPerfCounterInfoAMD)pOclModule->GetExtensionFunctionAddressForPlatform(platform, "clGetPerfCounterInfoAMD");

        if (nullptr == my_clGetPerfCounterInfoAMD)
        {
            return false;
        }
    }

    if (nullptr == my_clSetDeviceClockModeAMD)
    {
        my_clSetDeviceClockModeAMD = (pfn_clSetDeviceClockModeAMD)pOclModule->GetExtensionFunctionAddressForPlatform(platform, "clSetDeviceClockModeAMD");

        // TODO: return false once we no longer need to support pre-19.10 drivers
        //if (nullptr == my_clSetDeviceClockModeAMD)
        //{
        //    return false;
        //}
    }

    return true;
}
