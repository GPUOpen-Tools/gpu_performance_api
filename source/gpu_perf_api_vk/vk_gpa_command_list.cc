//==============================================================================
// Copyright (c) 2017-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Vulkan GPA Command List Object Implementation
//==============================================================================

#include "gpu_perf_api_vk/vk_gpa_command_list.h"

#include "gpu_perf_api_vk/vk_entry_points.h"
#include "gpu_perf_api_vk/vk_gpa_context.h"
#include "gpu_perf_api_vk/vk_gpa_session.h"

VkGpaCommandList::VkGpaCommandList(VkGpaSession* gpa_session, GpaPass* pass, void* command, CommandListId command_list_id, GpaCommandListType command_list_type)
    : GpaCommandList(gpa_session, pass, command_list_id, command_list_type)
    , vk_command_buffer_(static_cast<VkCommandBuffer>(command))
    , gpa_ext_session_command_list_(VK_NULL_HANDLE)
    , is_command_list_open_in_driver_(false)
{
    UNREFERENCED_PARAMETER(command_list_id);
}

VkGpaCommandList::~VkGpaCommandList()
{
    VkGpaContext* vk_context = reinterpret_cast<VkGpaContext*>(GpaCommandList::GetParentSession()->GetParentContext());
    VkDevice      device     = vk_context->GetVkDevice();

    if (VK_NULL_HANDLE != gpa_ext_session_command_list_)
    {
        _vkDestroyGpaSessionAMD(device, gpa_ext_session_command_list_, nullptr);
    }

    gpa_ext_session_command_list_ = VK_NULL_HANDLE;

    for (auto extensions_iter = copied_amd_extensions_.cbegin(); extensions_iter != copied_amd_extensions_.cend(); ++extensions_iter)
    {
        _vkDestroyGpaSessionAMD(device, *extensions_iter, nullptr);
    }

    copied_amd_extensions_.clear();
    copied_sample_map_.clear();
}

GpaApiType VkGpaCommandList::GetApiType() const
{
    return kGpaApiVulkan;
}

void VkGpaCommandList::SetAmdExtSession(VkGpaSessionAMD gpa_ext_session_amd)
{
    if (VK_NULL_HANDLE == gpa_ext_session_command_list_)
    {
        gpa_ext_session_command_list_ = gpa_ext_session_amd;
    }
}

VkGpaSessionAMD VkGpaCommandList::GetAmdExtSession() const
{
    return gpa_ext_session_command_list_;
}

bool VkGpaCommandList::BeginCommandListRequest()
{
    bool began = false;

    if (GpaCounterSource::kHardware == GetPass()->GetCounterSource())
    {
        VkGpaContext* vk_context = reinterpret_cast<VkGpaContext*>(GetParentSession()->GetParentContext());
        VkDevice      device     = vk_context->GetVkDevice();

        bool is_ready_to_begin = false;

        if (VK_NULL_HANDLE != gpa_ext_session_command_list_)
        {
            if (VK_SUCCESS == _vkResetGpaSessionAMD(device, gpa_ext_session_command_list_))
            {
                is_ready_to_begin = true;
            }
            else
            {
                GPA_LOG_ERROR("Unable to reset extension for new command list.");
            }
        }
        else
        {
            // Create a new extension session.
            VkGpaSessionCreateInfoAMD create_info = {VK_STRUCTURE_TYPE_GPA_SESSION_CREATE_INFO_AMD, nullptr, VK_NULL_HANDLE};
            create_info.secondaryCopySource       = VK_NULL_HANDLE;

            if (VK_SUCCESS == _vkCreateGpaSessionAMD(device, &create_info, nullptr, &gpa_ext_session_command_list_))
            {
                is_ready_to_begin = true;
            }
            else
            {
                GPA_LOG_ERROR("Failed to create a session on the AMD GPA Extension.");
            }
        }

        if (is_ready_to_begin)
        {
            if (VK_SUCCESS == _vkCmdBeginGpaSessionAMD(vk_command_buffer_, gpa_ext_session_command_list_))
            {
                began = true;
                vk_command_list_mutex_.lock();
                is_command_list_open_in_driver_ = true;
                vk_command_list_mutex_.unlock();
            }
            else
            {
                GPA_LOG_ERROR("Unable to open command list for sampling.");
            }
        }
    }

    return began;
}

bool VkGpaCommandList::EndCommandListRequest()
{
    bool is_ended = false;

    // If a sample was started, then it was either previously ended, or it was closed above.
    // If the sample state is now ENDED, then we know we must also end the GPA Extension Session.
    // WORKAROUND: We only want to begin / end the session if it has at least one sample on it.
    if (GpaCounterSource::kHardware == GetPass()->GetCounterSource() && is_command_list_open_in_driver_)
    {
        if (VK_SUCCESS == _vkCmdEndGpaSessionAMD(vk_command_buffer_, gpa_ext_session_command_list_))
        {
            vk_command_list_mutex_.lock();
            is_command_list_open_in_driver_ = false;
            vk_command_list_mutex_.unlock();
            is_ended = true;
        }
        else
        {
            GPA_LOG_DEBUG_ERROR("AMD extension is unable to end the command list.");
        }
    }

    return is_ended;
}

bool VkGpaCommandList::BeginSampleRequest(ClientSampleId client_sample_id, GpaSample* gpa_sample)
{
    UNREFERENCED_PARAMETER(client_sample_id);
    UNREFERENCED_PARAMETER(gpa_sample);

    return true;
}

bool VkGpaCommandList::CloseLastSampleRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

bool VkGpaCommandList::IsResultReady() const
{
    bool is_result_ready = false;

    VkGpaContext* gpa_context = dynamic_cast<VkGpaContext*>(GetParentSession()->GetParentContext());

    if (nullptr == gpa_context)
    {
        GPA_LOG_ERROR("Invalid profiling session encountered when checking for available results.");
    }
    else
    {
        VkResult is_ready = _vkGetGpaSessionStatusAMD(gpa_context->GetVkDevice(), gpa_ext_session_command_list_);
        is_result_ready   = VK_SUCCESS == is_ready;
    }

    return is_result_ready;
}

VkCommandBuffer VkGpaCommandList::GetVkCommandBuffer() const
{
    return vk_command_buffer_;
}

bool VkGpaCommandList::CopySecondarySamples(VkGpaCommandList*            primary_command_list,
                                            GpaUInt32                    num_samples,
                                            GpaUInt32*                   new_sample_ids,
                                            std::vector<ClientSampleId>& original_sample_ids)
{
    UNREFERENCED_PARAMETER(num_samples);
    bool copied = false;

    // For now, we only support copying hardware counters.
    if (GpaCounterSource::kHardware == GetPass()->GetCounterSource())
    {
        VkGpaSessionCreateInfoAMD create_info = {VK_STRUCTURE_TYPE_GPA_SESSION_CREATE_INFO_AMD, nullptr, VK_NULL_HANDLE};
        create_info.secondaryCopySource       = gpa_ext_session_command_list_;

        VkGpaContext* vk_context = reinterpret_cast<VkGpaContext*>(GetParentSession()->GetParentContext());
        VkDevice      device     = vk_context->GetVkDevice();

        VkGpaSessionAMD session_copy = VK_NULL_HANDLE;

        if (VK_SUCCESS == _vkCreateGpaSessionAMD(device, &create_info, nullptr, &session_copy))
        {
            vk_command_list_mutex_.lock();
            copied_amd_extensions_.push_back(session_copy);

            unsigned int sample_index             = 0;
            auto         process_client_sample_id = [&](ClientSampleIdGpaSamplePair clientSampleIdGpaSamplePair) -> bool {
                ClientSampleId original_sample_id = clientSampleIdGpaSamplePair.second->GetClientSampleId();
                original_sample_ids.push_back(original_sample_id);

                CopiedSampleInfo copied_info                     = {};
                copied_info.original_sample_id                   = original_sample_id;
                copied_info.copied_amd_ext_session               = session_copy;
                copied_sample_map_[new_sample_ids[sample_index]] = copied_info;
                original_sample_id                               = clientSampleIdGpaSamplePair.second->GetClientSampleId();
                sample_index++;
                return true;
            };

            IterateSampleUnorderedMap(process_client_sample_id);
            vk_command_list_mutex_.unlock();

            // Schedule the data copy on the primary command buffer.
            _vkCmdCopyGpaSessionResultsAMD(primary_command_list->GetVkCommandBuffer(), session_copy);
            copied = true;
        }
    }

    return copied;
}

VkGpaSessionAMD VkGpaCommandList::GetCopiedAmdExtSession(ClientSampleId client_sample_id) const
{
    VkGpaSessionAMD copied_ext_session = VK_NULL_HANDLE;

    std::map<ClientSampleId, CopiedSampleInfo>::const_iterator copied_sample_map_iter = copied_sample_map_.find(client_sample_id);

    if (copied_sample_map_iter != copied_sample_map_.cend())
    {
        copied_ext_session = copied_sample_map_iter->second.copied_amd_ext_session;
    }

    return copied_ext_session;
}
