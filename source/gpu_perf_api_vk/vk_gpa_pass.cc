//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Vulkan GPA Pass Object Implementation
//==============================================================================

#include "gpu_perf_api_vk/vk_gpa_pass.h"

#include "gpu_perf_api_common/gpa_context_counter_mediator.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_vk_base.h"

#include "gpu_perf_api_vk/vk_gpa_command_list.h"
#include "gpu_perf_api_vk/vk_gpa_context.h"
#include "gpu_perf_api_vk/vk_gpa_hardware_sample.h"

VkGpaPass::VkGpaPass(IGpaSession* gpa_session, PassIndex pass_index, GpaCounterSource counter_source, CounterList* pass_counters)
    : GpaPass(gpa_session, pass_index, counter_source, pass_counters)
    , is_sample_begin_info_initialized_(false)
{
    InitializeSampleConfig();
}

GpaSample* VkGpaPass::CreateApiSpecificSample(IGpaCommandList* command_list, GpaSampleType sample_type, unsigned int sample_id)
{
    GpaSample* sample = nullptr;

    if (GpaSampleType::kHardware == sample_type)
    {
        sample = new (std::nothrow) VkGpaHardwareSample(this, command_list, sample_id);
    }

    return sample;
}

IGpaCommandList* VkGpaPass::CreateApiSpecificCommandList(void* command, CommandListId command_list_id, GpaCommandListType command_type)
{
    VkGpaCommandList* vk_command_list =
        new (std::nothrow) VkGpaCommandList(reinterpret_cast<VkGpaSession*>(GetGpaSession()), this, command, command_list_id, command_type);

    return vk_command_list;
}

void VkGpaPass::InitializeSampleConfig()
{
    if (!is_sample_begin_info_initialized_ && GpaCounterSource::kHardware == GetCounterSource())
    {
        sample_begin_info_amd_       = {};
        sample_begin_info_amd_.sType = VK_STRUCTURE_TYPE_GPA_SAMPLE_BEGIN_INFO_AMD;
        sample_begin_info_amd_.pNext = nullptr;

        assert(counter_list_ != nullptr);
        if (counter_list_ == nullptr)
        {
            GPA_LOG_ERROR("There is no counter list to enable.");
            return;
        }

        IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::GetCounterAccessor(GetGpaSession());
        assert(counter_accessor != nullptr);
        if (counter_accessor == nullptr)
        {
            GPA_LOG_ERROR("Invalid counter accessor.");
            return;
        }

        if (!counter_list_->empty())
        {
            const GpaHardwareCounters& hardware_counters = counter_accessor->GetHardwareCounters();
            if (IsTimingPass())
            {
                sample_begin_info_amd_.sampleType = VK_GPA_SAMPLE_TYPE_TIMING_AMD;

                const CounterIndex front = counter_list_->front();
                if (hardware_counters.IsBottomToBottomTimeCounterIndex(front))
                {
                    sample_begin_info_amd_.timingPreSample = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
                }
                else if (hardware_counters.IsTopToBottomTimeCounterIndex(front))
                {
                    sample_begin_info_amd_.timingPreSample = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
                }

                sample_begin_info_amd_.timingPostSample = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;

                // Top-to-Bottom and Bottom-to-Bottom timestamps have already been separated into different
                // passes, so any additional counters scheduled for this pass can be automatically included.
                for (const CounterIndex counter : *counter_list_)
                {
                    EnableCounterForPass(counter);
                }
            }
            else
            {
                // All the shader stages.
                VkGpaSqShaderStageFlagBitsAMD mask_value = VK_GPA_SQ_SHADER_STAGE_FLAG_BITS_MAX_ENUM_AMD;

                sample_begin_info_amd_.sampleType = VK_GPA_SAMPLE_TYPE_CUMULATIVE_AMD;

                // Add all desired counters.
                for (const CounterIndex counter_index : *counter_list_)
                {
                    const GpaHardwareCounterDescExt* counter  = &hardware_counters.hardware_counters_.at(counter_index);
                    const VkGpaPerfBlockAMD          block    = static_cast<VkGpaPerfBlockAMD>(counter->group_id_driver);
                    const GpaUInt32                  instance = hardware_counters.internal_counter_groups_[counter->group_index].block_instance;
                    const GpaUInt32                  event_id = static_cast<GpaUInt32>(counter->hardware_counters->counter_index_in_group);

                    if (reinterpret_cast<VkGpaContext*>(GetGpaSession()->GetParentContext())->GetNumInstances(block) <= instance)
                    {
                        DisableCounterForPass(counter_index);
                        continue;
                    }

                    if (reinterpret_cast<VkGpaContext*>(GetGpaSession()->GetParentContext())->GetMaxEventId(block) <= event_id)
                    {
                        DisableCounterForPass(counter_index);
                        continue;
                    }

                    // Validate requested counter vs number of actual hardware counters and group index.
                    const uint32_t group_index = counter->group_index;
                    uint32_t       counters    = 0;

                    if (group_index < static_cast<GpaUInt32>(hardware_counters.internal_counter_groups_.size()))
                    {
                        counters = hardware_counters.internal_counter_groups_[group_index].num_counters;
                    }
                    else
                    {
                        counters = hardware_counters.additional_groups_[group_index - static_cast<GpaUInt32>(hardware_counters.internal_counter_groups_.size())]
                                       .num_counters;
                    }

                    if (counter->hardware_counters->counter_index_in_group > counters)
                    {
                        assert(counter->hardware_counters->counter_index_in_group <= counters);
                        DisableCounterForPass(counter_index);
                        continue;
                    }

                    if (group_index > (static_cast<GpaUInt32>(hardware_counters.internal_counter_groups_.size()) + hardware_counters.additional_group_count_))
                    {
                        assert(group_index <=
                               (static_cast<GpaUInt32>(hardware_counters.internal_counter_groups_.size()) + hardware_counters.additional_group_count_));
                        DisableCounterForPass(counter_index);
                        continue;
                    }

                    // Add counter to valid vector.
                    VkGpaPerfCounterAMD this_counter;
                    this_counter.blockType     = block;
                    this_counter.blockInstance = instance;
                    this_counter.eventID       = event_id;

                    counter_ids_.push_back(this_counter);

                    // If dealing with an SQ or SqWgp counter, check if the stage mask needs to be set.
                    if (block == VK_GPA_PERF_BLOCK_SQ_AMD || block == VK_GPA_PERF_BLOCK_SQWGP_AMD)
                    {
                        GpaSqShaderStage stage = kSqAll;

                        for (unsigned int j = 0; j < hardware_counters.sq_group_count_ - 1; j++)
                        {
                            if (hardware_counters.sq_counter_groups_[j].group_index == counter->group_index)
                            {
                                stage = hardware_counters.sq_counter_groups_[j].sq_shader_stage;
                                break;
                            }
                        }

                        if (stage == kSqEs)
                        {
                            mask_value = VK_GPA_SQ_SHADER_STAGE_ES_BIT_AMD;
                        }
                        else if (stage == kSqGs)
                        {
                            mask_value = VK_GPA_SQ_SHADER_STAGE_GS_BIT_AMD;
                        }
                        else if (stage == kSqVs)
                        {
                            mask_value = VK_GPA_SQ_SHADER_STAGE_VS_BIT_AMD;
                        }
                        else if (stage == kSqPs)
                        {
                            mask_value = VK_GPA_SQ_SHADER_STAGE_PS_BIT_AMD;
                        }
                        else if (stage == kSqLs)
                        {
                            mask_value = VK_GPA_SQ_SHADER_STAGE_LS_BIT_AMD;
                        }
                        else if (stage == kSqHs)
                        {
                            mask_value = VK_GPA_SQ_SHADER_STAGE_HS_BIT_AMD;
                        }
                        else if (stage == kSqCs)
                        {
                            mask_value = VK_GPA_SQ_SHADER_STAGE_CS_BIT_AMD;
                        }
                    }

                    EnableCounterForPass(counter_index);
                }

                sample_begin_info_amd_.perfCounterCount                 = GetNumEnabledCountersForPass();
                sample_begin_info_amd_.pPerfCounters                    = counter_ids_.data();
                sample_begin_info_amd_.streamingPerfTraceSampleInterval = 0;
                sample_begin_info_amd_.sqThreadTraceDeviceMemoryLimit   = 0;
                sample_begin_info_amd_.perfCounterDeviceMemoryLimit     = 0;

                // Set shader mask.
                sample_begin_info_amd_.sqShaderMaskEnable = VK_TRUE;
                sample_begin_info_amd_.sqShaderMask       = mask_value;

                // Sq Thread trace.
                sample_begin_info_amd_.sqThreadTraceEnable                    = VK_FALSE;
                sample_begin_info_amd_.sqThreadTraceSuppressInstructionTokens = VK_TRUE;
            }

            // Insert L2 cache invalidate and flush around counter sample.
            sample_begin_info_amd_.cacheFlushOnCounterCollection = 1;

            is_sample_begin_info_initialized_ = true;
        }
    }
}

bool VkGpaPass::EndSample(IGpaCommandList* command_list)
{
    bool success = false;

    if (nullptr == command_list)
    {
        GPA_LOG_ERROR("Null pointer to GPA CommandList supplied.");
    }
    else if (!command_list->IsCommandListRunning())
    {
        GPA_LOG_ERROR("CommandList is closed for sampling.");
    }
    else if (command_list->IsLastSampleClosed())
    {
        GPA_LOG_ERROR("There is no open sample on the CommandList.");
    }
    else
    {
        GpaSample* gpa_sample = command_list->GetLastSample();

        if (nullptr != gpa_sample && !gpa_sample->IsClosed())
        {
            success = command_list->CloseLastSample();
        }
    }

    return success;
}

bool VkGpaPass::CopySecondarySamples(VkGpaCommandList* secondary_vk_gpa_command_list,
                                     VkGpaCommandList* primary_vk_gpa_command_list,
                                     GpaUInt32         num_samples,
                                     GpaUInt32*        new_sample_ids)
{
    bool copied = false;

    // 1. Validate all new sample id are unique.
    // 2. Create new samples for new passed sample id.
    // 3. Update the session <-> Cmd Map.
    bool are_new_samples_unique = true;

    for (GpaUInt32 i = 0; i < num_samples; ++i)
    {
        are_new_samples_unique &= !DoesSampleExist(new_sample_ids[i]);
    }

    if (are_new_samples_unique)
    {
        if (kGpaCommandListPrimary == primary_vk_gpa_command_list->GetCmdType() && kGpaCommandListSecondary == secondary_vk_gpa_command_list->GetCmdType())
        {
            if (primary_vk_gpa_command_list->GetPass()->GetIndex() == secondary_vk_gpa_command_list->GetPass()->GetIndex())
            {
                // Validate.
                // 1. secondary command list is not open.
                // 2. No pending sample on the secondary command list.
                if (!secondary_vk_gpa_command_list->IsCommandListRunning() && secondary_vk_gpa_command_list->IsLastSampleClosed())
                {
                    // Validate.
                    // 1. primary command list is open.
                    // 2. No pending sample on the primary command list.
                    if (primary_vk_gpa_command_list->IsCommandListRunning() && primary_vk_gpa_command_list->IsLastSampleClosed())
                    {
                        // Validate - Number of sample ids must be equal to the created sample on the secondary command list/
                        if (secondary_vk_gpa_command_list->GetSampleCount() == num_samples)
                        {
                            std::vector<ClientSampleId> original_client_sample_ids;

                            // Create new sample objects to represent the copied samples.
                            unsigned int              index = 0;
                            std::vector<VkGpaSample*> new_sample_list;

                            for (GpaUInt32 i = 0; i < num_samples; ++i)
                            {
                                GpaSampleType sample_type =
                                    GetCounterSource() == GpaCounterSource::kHardware ? GpaSampleType::kHardware : GpaSampleType::kSoftware;
                                VkGpaSample* new_sample =
                                    reinterpret_cast<VkGpaSample*>(CreateApiSpecificSample(secondary_vk_gpa_command_list, sample_type, new_sample_ids[i]));

                                if (nullptr != new_sample)
                                {
                                    // Add this sample to command list as well to sample list.
                                    AddClientSample(new_sample_ids[i], new_sample);
                                    new_sample_list.push_back(new_sample);
                                }
                                else
                                {
                                    GPA_LOG_ERROR("Unable to copy secondary samples: Unable to create sample.");
                                }

                                index++;
                            }

                            // Assume they will succeed.
                            copied = true;

                            if (secondary_vk_gpa_command_list->CopySecondarySamples(
                                    primary_vk_gpa_command_list, num_samples, new_sample_ids, original_client_sample_ids))
                            {
                                index = 0;

                                for (auto iter = new_sample_list.begin(); iter != new_sample_list.end(); ++iter)
                                {
                                    // Driver sample id will be same as that of the original one.
                                    VkGpaSample* secondary_cmd_sample =
                                        reinterpret_cast<VkGpaSample*>(secondary_vk_gpa_command_list->GetSample(original_client_sample_ids[index]));

                                    if (nullptr != secondary_cmd_sample)
                                    {
                                        (*iter)->SetAsCopied();
                                        (*iter)->SetDriverSampleId(secondary_cmd_sample->GetDriverSampleId());
                                    }
                                    else
                                    {
                                        copied = false;
                                    }

                                    index++;
                                }
                            }
                            else
                            {
                                copied = false;
                            }
                        }
                        else
                        {
                            GPA_LOG_ERROR("Unable to copy secondary samples: Number of new sample ids is not same as that on secondary command list.");
                        }
                    }
                    else
                    {
                        GPA_LOG_ERROR("Unable to copy secondary samples: Either primary command list is closed or the last sample is not closed.");
                    }
                }
                else
                {
                    GPA_LOG_ERROR("Unable to copy secondary samples: Either secondary command list is not closed or the last sample is not closed.");
                }
            }
            else
            {
                GPA_LOG_ERROR("Unable to copy secondary samples: Primary and Secondary command list must be from the same pass.");
            }
        }
        else
        {
            GPA_LOG_ERROR("Unable to copy secondary samples: One primary command list and one secondary command list are required.");
        }
    }
    else
    {
        GPA_LOG_ERROR("Unable to copy secondary samples: Not all client sample ids are unique.");
    }

    return copied;
}

const VkGpaSampleBeginInfoAMD* VkGpaPass::GetVkSampleBeginInfo() const
{
    const VkGpaSampleBeginInfoAMD* info = nullptr;

    if (is_sample_begin_info_initialized_)
    {
        info = &sample_begin_info_amd_;
    }

    return info;
}
