//==============================================================================
// Copyright (c) 2009-2020 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  A utility function to get the AMD internal performance counters' interface via
///         clGetExtensionFunctionAddress.
//==============================================================================

#include <CL/cl.h>
#include <CL/internal/cl_profile_amd.h>
#include "cl_perf_counter_amd_extension.h"
#include "cl_rt_module_loader.h"

PfnClCreatePerfCounterAmd       my_cl_create_perf_counter_amd        = nullptr;
PfnClReleasePerfCounterAmd      my_cl_release_perf_counter_amd       = nullptr;
PfnClRetainPerfCounterAmd       my_cl_retain_perf_counter_amd        = nullptr;
PfnClEnqueueBeginPerfCounterAmd my_cl_enqueue_begin_perf_counter_amd = nullptr;
PfnClEnqueueEndPerfCounterAmd   my_cl_enqueue_end_perf_counter_amd   = nullptr;
PfnClGetPerfCounterInfoAmd      my_cl_get_perf_counter_info_amd      = nullptr;
PfnClSetDeviceClockModeAmd      my_cl_set_device_clock_mode_amd      = nullptr;

bool InitPerfCounterAmdExtension(cl_platform_id platform)
{
    OpenCLModule* cl_module = ClRuntimeModuleLoader::Instance()->GetApiRuntimeModule();

    if (nullptr == cl_module)
    {
        return false;
    }

    if (nullptr == my_cl_create_perf_counter_amd)
    {
        my_cl_create_perf_counter_amd =
            static_cast<PfnClCreatePerfCounterAmd>(cl_module->GetExtensionFunctionAddressForPlatform(platform, "clCreatePerfCounterAMD"));

        if (nullptr == my_cl_create_perf_counter_amd)
        {
            return false;
        }
    }

    if (nullptr == my_cl_release_perf_counter_amd)
    {
        my_cl_release_perf_counter_amd =
            static_cast<PfnClReleasePerfCounterAmd>(cl_module->GetExtensionFunctionAddressForPlatform(platform, "clReleasePerfCounterAMD"));

        if (nullptr == my_cl_release_perf_counter_amd)
        {
            return false;
        }
    }

    if (nullptr == my_cl_retain_perf_counter_amd)
    {
        my_cl_retain_perf_counter_amd =
            static_cast<PfnClRetainPerfCounterAmd>(cl_module->GetExtensionFunctionAddressForPlatform(platform, "clRetainPerfCounterAMD"));

        if (nullptr == my_cl_retain_perf_counter_amd)
        {
            return false;
        }
    }

    if (nullptr == my_cl_enqueue_begin_perf_counter_amd)
    {
        my_cl_enqueue_begin_perf_counter_amd =
            static_cast<PfnClEnqueueBeginPerfCounterAmd>(cl_module->GetExtensionFunctionAddressForPlatform(platform, "clEnqueueBeginPerfCounterAMD"));

        if (nullptr == my_cl_enqueue_begin_perf_counter_amd)
        {
            return false;
        }
    }

    if (nullptr == my_cl_enqueue_end_perf_counter_amd)
    {
        my_cl_enqueue_end_perf_counter_amd =
            static_cast<PfnClEnqueueEndPerfCounterAmd>(cl_module->GetExtensionFunctionAddressForPlatform(platform, "clEnqueueEndPerfCounterAMD"));

        if (nullptr == my_cl_enqueue_end_perf_counter_amd)
        {
            return false;
        }
    }

    if (nullptr == my_cl_get_perf_counter_info_amd)
    {
        my_cl_get_perf_counter_info_amd =
            static_cast<PfnClGetPerfCounterInfoAmd>(cl_module->GetExtensionFunctionAddressForPlatform(platform, "clGetPerfCounterInfoAMD"));

        if (nullptr == my_cl_get_perf_counter_info_amd)
        {
            return false;
        }
    }

    if (nullptr == my_cl_set_device_clock_mode_amd)
    {
        my_cl_set_device_clock_mode_amd =
            static_cast<PfnClSetDeviceClockModeAmd>(cl_module->GetExtensionFunctionAddressForPlatform(platform, "clSetDeviceClockModeAMD"));

        // TODO: return false once we no longer need to support pre-19.10 drivers
        //if (nullptr == my_clSetDeviceClockModeAMD)
        //{
        //    return false;
        //}
    }

    return true;
}
