//==============================================================================
// Copyright (c) 2009-2020 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  A utility class for interfacing with the performance counter from the OpenCL runtime.
//==============================================================================

#include <assert.h>
#include <math.h>
#include <iostream>
#include <map>
#include <vector>
#include <CL/cl.h>
#include <CL/internal/cl_profile_amd.h>
#include "cl_perf_counter_block.h"
#include "cl_perf_counter_amd_extension.h"
#include "cl_rt_module_loader.h"
#include "logging.h"

ClPerfCounterBlock::ClPerfCounterBlock(cl_device_id cl_device, cl_ulong block_id, cl_uint max_active, std::vector<cl_ulong> counters)
    : cl_device_(cl_device)
    , block_id_(block_id)
    , max_active_(max_active)
    , counters_list_(counters)
    , cl_perf_counters_amd_(nullptr)
    , is_counter_result_ready_(false)
{
    Create();
}

ClPerfCounterBlock::~ClPerfCounterBlock()
{
    ReleaseCounters();
}

void ClPerfCounterBlock::ReleaseCounters()
{
    if (nullptr != cl_perf_counters_amd_)
    {
        for (cl_uint i = 0; i < counters_list_.size(); ++i)
        {
            my_cl_release_perf_counter_amd(cl_perf_counters_amd_[i]);
        }

        delete[] cl_perf_counters_amd_;
        cl_perf_counters_amd_ = nullptr;
    }
}

void ClPerfCounterBlock::Create()
{
    if (counters_list_.empty())
    {
        return;
    }

    cl_int                  error;
    cl_perfcounter_property properties[4][2];

    cl_perf_counters_amd_ = new (std::nothrow) cl_perfcounter_amd[counters_list_.size()];

    if (nullptr == cl_perf_counters_amd_)
    {
        GPA_LOG_ERROR("ClPerfCounterBlock: Unable to allocate memory.");
        return;
    }

    properties[0][0] = CL_PERFCOUNTER_GPU_BLOCK_INDEX;
    properties[1][0] = CL_PERFCOUNTER_GPU_COUNTER_INDEX;
    properties[2][0] = CL_PERFCOUNTER_GPU_EVENT_INDEX;
    properties[3][0] = CL_PERFCOUNTER_NONE;

    properties[0][1] = block_id_;

    for (cl_uint i = 0; i < GetNumPasses(); ++i)
    {
        for (cl_uint j = 0; j < max_active_; ++j)
        {
            cl_uint index = i * max_active_ + j;

            if (index >= counters_list_.size())
            {
                break;
            }

            properties[1][1] = j;
            properties[2][1] = counters_list_[index];

            cl_perf_counters_amd_[index] = my_cl_create_perf_counter_amd(cl_device_, &properties[0][0], &error);

            if (CL_SUCCESS != error)
            {
                std::stringstream ss;
                ss << "clCreatePerfCounterAMD failed (pass: " << i << ", index in pass: " << j << ", global index: " << index
                   << ", counter: " << counters_list_[index] << "). Error code=" << error << ".";
                GPA_LOG_ERROR(ss.str().c_str());

                return;
            }
        }
    }
}

bool ClPerfCounterBlock::CollectData(const cl_event* cl_event_param)
{
    if (is_counter_result_ready_)
    {
        return true;
    }

    assert(nullptr != cl_perf_counters_amd_);

    if (counters_list_.empty() || nullptr == cl_perf_counters_amd_)
    {
        return false;
    }

    cl_int   error;
    cl_ulong result;

    ClRuntimeModuleLoader::Instance()->GetApiRuntimeModule()->WaitForEvents(1, cl_event_param);

    for (cl_uint i = 0; i < counters_list_.size(); ++i)
    {
        error = my_cl_get_perf_counter_info_amd(cl_perf_counters_amd_[i], CL_PERFCOUNTER_DATA, sizeof(cl_ulong), &result, nullptr);

        if (CL_SUCCESS != error)
        {
            std::stringstream ss;
            ss << "clGetPerfCounterInfoAMD failed (counter index: " << i << ", counter: " << counters_list_[i] << "). Error code=" << error << ".";
            GPA_LOG_ERROR(ss.str().c_str());

            return false;
        }

        counter_result_map_[counters_list_[i]] = result;
    }

    is_counter_result_ready_ = true;
    return true;
}
