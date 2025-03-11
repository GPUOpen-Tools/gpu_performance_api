//==============================================================================
// Copyright (c) 2017-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief A Vulkan-specific implementation of the GPA Session interface
//==============================================================================

#include "gpu_perf_api_vk/vk_gpa_session.h"

#include "gpu_perf_api_common/gpa_unique_object.h"

#include "gpu_perf_api_vk/vk_gpa_command_list.h"
#include "gpu_perf_api_vk/vk_gpa_pass.h"

VkGpaSession::VkGpaSession(IGpaContext* parent_context_id, GpaSessionSampleType sample_type)
    : GpaSession(parent_context_id, sample_type)
{
}

GpaApiType VkGpaSession::GetApiType() const
{
    return kGpaApiVulkan;
}

GpaStatus VkGpaSession::ContinueSampleOnCommandList(GpaUInt32 src_sample_id, GpaCommandListId primary_command_list_id)
{
    bool succeed = false;

    if (primary_command_list_id->Object()->GetApiType() == GetApiType() && primary_command_list_id->ObjectType() == GpaObjectType::kGpaObjectTypeCommandList)
    {
        VkGpaCommandList* vk_gpa_command_list = reinterpret_cast<VkGpaCommandList*>(primary_command_list_id->Object());
        VkGpaPass*        vk_gpa_pass         = reinterpret_cast<VkGpaPass*>(vk_gpa_command_list->GetPass());

        if (nullptr != vk_gpa_pass)
        {
            // Continue the sample.
            if (vk_gpa_pass->ContinueSample(src_sample_id, vk_gpa_command_list))
            {
                succeed = true;
            }
            else
            {
                GPA_LOG_ERROR("Unable to continue sample.");
            }
        }
        else
        {
            GPA_LOG_ERROR("Pass doesn't exist.");
        }
    }
    else
    {
        GPA_LOG_ERROR("Invalid Parameter.");
    }

    return succeed ? kGpaStatusOk : kGpaStatusErrorFailed;
}

GpaStatus VkGpaSession::CopySecondarySamples(GpaCommandListId secondary_command_list_id,
                                             GpaCommandListId primary_command_list_id,
                                             GpaUInt32        num_samples,
                                             GpaUInt32*       new_sample_ids)
{
    bool is_copied = false;

    if (secondary_command_list_id->Object()->GetApiType() == kGpaApiVulkan &&
        secondary_command_list_id->ObjectType() == GpaObjectType::kGpaObjectTypeCommandList &&
        primary_command_list_id->Object()->GetApiType() == kGpaApiVulkan && primary_command_list_id->ObjectType() == GpaObjectType::kGpaObjectTypeCommandList)
    {
        VkGpaCommandList* vk_priamry_command_list   = reinterpret_cast<VkGpaCommandList*>(primary_command_list_id->Object());
        VkGpaCommandList* vk_secondary_command_list = reinterpret_cast<VkGpaCommandList*>(secondary_command_list_id->Object());

        VkGpaPass* vk_pass = reinterpret_cast<VkGpaPass*>(vk_priamry_command_list->GetPass());

        if (nullptr != vk_pass)
        {
            if (vk_pass->CopySecondarySamples(vk_secondary_command_list, vk_priamry_command_list, num_samples, new_sample_ids))
            {
                is_copied = true;
            }
        }
    }
    else
    {
        GPA_LOG_ERROR("Invalid Parameter.");
    }

    return is_copied ? kGpaStatusOk : kGpaStatusErrorFailed;
}

GpaPass* VkGpaSession::CreateApiPass(PassIndex pass_index)
{
    GpaPass* ret_pass = nullptr;

    CounterList*     pass_counters  = GetCountersForPass(pass_index);
    assert(pass_counters != nullptr);
    if (pass_counters != nullptr && pass_counters->size() > 0)
    {
        GpaCounterSource counter_source = GetCounterSource((*pass_counters)[0]);

        VkGpaPass* vk_gpa_pass = new (std::nothrow) VkGpaPass(this, pass_index, counter_source, pass_counters);

        if (nullptr != vk_gpa_pass)
        {
            ret_pass = vk_gpa_pass;
        }
    }

    return ret_pass;
}
