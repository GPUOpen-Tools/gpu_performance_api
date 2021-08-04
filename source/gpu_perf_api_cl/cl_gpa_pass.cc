//==============================================================================
// Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  CL GPA Pass Object Implementation
//==============================================================================

#include <cassert>

#include "cl_gpa_pass.h"
#include "cl_gpa_command_list.h"
#include "cl_gpa_sample.h"
#include "gpa_hardware_counters.h"
#include "gpa_context_counter_mediator.h"

ClGpaPass::ClGpaPass(IGpaSession* gpa_session, PassIndex pass_index, GpaCounterSource counter_source, CounterList* pass_counters)
    : GpaPass(gpa_session, pass_index, counter_source, pass_counters)
{
    EnableAllCountersForPass();
    InitializeClCounterInfo();
}

GpaSample* ClGpaPass::CreateApiSpecificSample(IGpaCommandList* cmd_list, GpaSampleType sample_type, ClientSampleId sample_id)
{
    GpaSample* ret_sample = nullptr;

    ClGpaSample* cl_gpa_sample = new (std::nothrow) ClGpaSample(this, cmd_list, sample_type, sample_id);

    if (nullptr == cl_gpa_sample)
    {
        GPA_LOG_ERROR("Unable to allocate memory for the sample.");
    }
    else
    {
        ret_sample = cl_gpa_sample;
    }

    return ret_sample;
}

bool ClGpaPass::ContinueSample(ClientSampleId src_sample_id, IGpaCommandList* primary_gpa_cmd_list)
{
    // continuing samples not supported for OpenCL
    UNREFERENCED_PARAMETER(src_sample_id);
    UNREFERENCED_PARAMETER(primary_gpa_cmd_list);
    return false;
}

IGpaCommandList* ClGpaPass::CreateApiSpecificCommandList(void* cmd, CommandListId command_list_id, GpaCommandListType cmd_type)
{
    UNREFERENCED_PARAMETER(cmd);
    UNREFERENCED_PARAMETER(cmd_type);

    ClGpaCommandList* ret_cmd_list = new (std::nothrow) ClGpaCommandList(GetGpaSession(), this, command_list_id);

    if (nullptr == ret_cmd_list)
    {
        GPA_LOG_ERROR("Unable to allocate memory for the command list.");
    }

    return ret_cmd_list;
}

bool ClGpaPass::EndSample(IGpaCommandList* cmd_list)
{
    bool ret_val = false;

    if (nullptr != cmd_list)
    {
        ret_val = cmd_list->CloseLastSample();
    }

    return ret_val;
}

void ClGpaPass::IterateClCounterMap(std::function<bool(GroupCountersPair group_counters_pair)> function) const
{
    bool next = true;

    for (auto it = group_counters_map_.cbegin(); it != group_counters_map_.cend() && next; ++it)
    {
        next = function(*it);
    }
}

void ClGpaPass::InitializeClCounterInfo()
{
    ClGpaContext*              cl_gpa_context    = reinterpret_cast<ClGpaContext*>(GetGpaSession()->GetParentContext());
    IGpaCounterAccessor*       counter_accessor  = GpaContextCounterMediator::Instance()->GetCounterAccessor(cl_gpa_context);
    const GpaHardwareCounters* hardware_counters = counter_accessor->GetHardwareCounters();
    GpaUInt32                  group_count       = static_cast<GpaUInt32>(hardware_counters->group_count_);
    UNREFERENCED_PARAMETER(group_count);

    auto add_counter_to_cl_counter_info = [&](CounterIndex counter_index) -> bool {
        const GpaHardwareCounterDescExt* counter = counter_accessor->GetHardwareCounterExt(counter_index);

        GpaUInt32 group_index = counter->group_id_driver;
        assert(group_index <= group_count);

        GpaUInt64 num_counters = hardware_counters->internal_counter_groups_[group_index].num_counters;
        UNREFERENCED_PARAMETER(num_counters);
        assert(counter->hardware_counters->counter_index_in_group <= num_counters);

        group_counters_map_[group_index].push_back(counter->hardware_counters->counter_index_in_group);
        return true;
    };

    IterateEnabledCounterList(add_counter_to_cl_counter_info);
}
