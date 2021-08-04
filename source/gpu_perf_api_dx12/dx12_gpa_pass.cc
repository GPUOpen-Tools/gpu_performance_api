//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX12 GPA Pass Object Implementation
//==============================================================================

#include "gpu_perf_api_dx12/dx12_gpa_pass.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx12_base.h"

#include "gpu_perf_api_common/gpa_context_counter_mediator.h"

#include "gpu_perf_api_dx12/dx12_gpa_command_list.h"
#include "gpu_perf_api_dx12/dx12_gpa_context.h"
#include "gpu_perf_api_dx12/dx12_gpa_sample.h"
#include "gpu_perf_api_dx12/dx12_utils.h"

Dx12GpaPass::Dx12GpaPass(IGpaSession* gpa_session, PassIndex pass_index, GpaCounterSource counter_source, CounterList* pass_counters)
    : GpaPass(gpa_session, pass_index, counter_source, pass_counters)
    , amd_ext_sample_config_()
    , is_sample_config_initialized_(false)
{
    InitializeSampleConfig();
}

GpaSample* Dx12GpaPass::CreateApiSpecificSample(IGpaCommandList* cmd_list, GpaSampleType sample_type, ClientSampleId sample_id)
{
    Dx12GpaSample*      ret_dx12_gpa_sample = nullptr;
    Dx12GpaCommandList* dx12_gpa_cmd_list   = reinterpret_cast<Dx12GpaCommandList*>(cmd_list);

    // First Check whether the command list is opened and last sample is closed.
    if (nullptr != dx12_gpa_cmd_list && nullptr == dx12_gpa_cmd_list->GetSample(sample_id) && dx12_gpa_cmd_list->IsCommandListRunning() &&
        dx12_gpa_cmd_list->IsLastSampleClosed())
    {
        ret_dx12_gpa_sample = new (std::nothrow) Dx12GpaSample(this, cmd_list, sample_type, sample_id);
    }

    return ret_dx12_gpa_sample;
}

bool Dx12GpaPass::UpdateResults()
{
    bool is_completed = false;

    if (kGpaStatusOk == IsComplete())
    {
        is_completed = GpaPass::UpdateResults();

        if (is_completed)
        {
            ResetPass();
        }
    }

    return is_completed;
}

IGpaCommandList* Dx12GpaPass::CreateApiSpecificCommandList(void* cmd, CommandListId command_list_id, GpaCommandListType cmd_type)
{
    IGpaCommandList* ret_cmd_list = nullptr;

    D3D12_COMMAND_LIST_TYPE command_list_type;

    if (dx12_utils::IsD3D12CommandList(cmd, &command_list_type))
    {
        if (command_list_type != D3D12_COMMAND_LIST_TYPE_COPY)
        {
            Dx12GpaCommandList* dx12_gpa_cmd_list =
                new (std::nothrow) Dx12GpaCommandList(reinterpret_cast<Dx12GpaSession*>(GetGpaSession()), this, cmd, command_list_id, cmd_type);

            if (nullptr != dx12_gpa_cmd_list)
            {
                ret_cmd_list = dx12_gpa_cmd_list;
            }
        }
        else
        {
            GPA_LOG_ERROR("Copy command lists are not supported.");
        }
    }

    return ret_cmd_list;
}

bool Dx12GpaPass::EndSample(IGpaCommandList* cmd_list)
{
    bool success = false;

    if (nullptr != cmd_list && cmd_list->IsCommandListRunning() && !cmd_list->IsLastSampleClosed())
    {
        GpaSample* gpa_sample = cmd_list->GetLastSample();

        if (nullptr != gpa_sample && !gpa_sample->IsClosed())
        {
            success = cmd_list->CloseLastSample();
        }
    }
    else
    {
        GPA_LOG_ERROR("Either the command list is closed or there is no open sample on the command list.");
    }

    return success;
}

bool Dx12GpaPass::CopySecondarySamples(std::vector<ClientSampleId> client_samples,
                                       Dx12GpaCommandList*         dx12_primary_gpa_cmd_list,
                                       Dx12GpaCommandList*         dx12_secondary_gpa_cmd_list)
{
    bool success = false;

    // 1. Validate all new sample id are unique.
    // 2. Create new samples for new passed sample id.
    // 3. Update the session <-> CommandList Map.

    bool is_all_unique_sample_ids = true;

    for (auto iter = client_samples.cbegin(); iter != client_samples.cend(); ++iter)
    {
        is_all_unique_sample_ids &= !DoesSampleExist(*iter);
    }

    if (is_all_unique_sample_ids)
    {
        if (kGpaCommandListPrimary == dx12_primary_gpa_cmd_list->GetCmdType() && kGpaCommandListSecondary == dx12_secondary_gpa_cmd_list->GetCmdType())
        {
            if (dx12_primary_gpa_cmd_list->GetPass()->GetIndex() == dx12_secondary_gpa_cmd_list->GetPass()->GetIndex())
            {
                // Validate.
                // 1. secondary command list is not open.
                // 2. No pending sample on the secondary command list.
                if (!dx12_secondary_gpa_cmd_list->IsCommandListRunning() && dx12_secondary_gpa_cmd_list->IsLastSampleClosed())
                {
                    // Validate.
                    // 1. primary command list is open.
                    // 2. No pending sample on the primary command list.
                    if (dx12_primary_gpa_cmd_list->IsCommandListRunning() && dx12_primary_gpa_cmd_list->IsLastSampleClosed())
                    {
                        // Validate - Number of sample ids must be equal to the created sample on the secondary command list.
                        if (dx12_secondary_gpa_cmd_list->GetSampleCount() == client_samples.size())
                        {
                            std::vector<ClientSampleId> original_client_sample_ids;
                            // Copy the results.

                            unsigned int                index = 0;
                            std::vector<Dx12GpaSample*> new_sample_list;

                            for (auto iter = client_samples.begin(); iter != client_samples.end(); ++iter)
                            {
                                GpaSampleType sample_type =
                                    GetCounterSource() == GpaCounterSource::kHardware ? GpaSampleType::kHardware : GpaSampleType::kSoftware;
                                Dx12GpaSample* new_sample =
                                    reinterpret_cast<Dx12GpaSample*>(CreateApiSpecificSample(dx12_primary_gpa_cmd_list, sample_type, *iter));

                                if (nullptr != new_sample)
                                {
                                    // Add this sample to command list as well to sample list.
                                    AddClientSample(*iter, new_sample);
                                    new_sample_list.push_back(new_sample);
                                }
                                else
                                {
                                    GPA_LOG_ERROR("Unable to copy secondary samples: Unable to create sample.");
                                }

                                index++;
                            }

                            success = true;

                            if (dx12_primary_gpa_cmd_list->CopyBundleSamples(client_samples, dx12_secondary_gpa_cmd_list, original_client_sample_ids))
                            {
                                index = 0;

                                for (auto iter = new_sample_list.begin(); iter != new_sample_list.end(); ++iter)
                                {
                                    // Driver sample id will be same as that of the original one.
                                    Dx12GpaSample* secondary_cmd_sample =
                                        reinterpret_cast<Dx12GpaSample*>(dx12_secondary_gpa_cmd_list->GetSample(original_client_sample_ids[index]));

                                    if (nullptr != secondary_cmd_sample)
                                    {
                                        (*iter)->SetAsCopied();
                                        (*iter)->SetDriverSampleId(secondary_cmd_sample->GetDriverSampleId());
                                    }
                                    else
                                    {
                                        success = false;
                                    }

                                    index++;
                                }
                            }
                            else
                            {
                                success = false;
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

    return success;
}

Dx12GpaPass::~Dx12GpaPass()
{
    if (AmdExtGpaSampleType::Timing != amd_ext_sample_config_.type)
    {
        delete[] amd_ext_sample_config_.perfCounters.pIds;
    }

    ResetPass();
}

void Dx12GpaPass::InitializeSampleConfig()
{
    if (!is_sample_config_initialized_ && GpaCounterSource::kHardware == GetCounterSource())
    {
        std::vector<AmdExtPerfCounterId> counter_ids;

        IGpaCounterAccessor*       counter_accessor  = GpaContextCounterMediator::Instance()->GetCounterAccessor(GetGpaSession()->GetParentContext());
        const GpaHardwareCounters* hardware_counters = counter_accessor->GetHardwareCounters();

        if (!counter_list_->empty())
        {
            if (IsTimingPass())
            {
                amd_ext_sample_config_.type         = AmdExtGpaSampleType::Timing;
                amd_ext_sample_config_.flags.u32All = 1;
                amd_ext_sample_config_.sqShaderMask = PerfShaderMaskAll;
                amd_ext_sample_config_.perfCounters = {};
                amd_ext_sample_config_.sqtt         = {};

                if (hardware_counters->IsBottomOfPipeCounterIndex(counter_list_->at(0)))
                {
                    amd_ext_sample_config_.timing.preSample = AmdExtHwPipePoint::HwPipeBottom;
                }
                else if (hardware_counters->IsTopOfPipeCounterIndex(counter_list_->at(0)))
                {
                    amd_ext_sample_config_.timing.preSample = AmdExtHwPipePoint::HwPipeTop;
                }

                amd_ext_sample_config_.timing.postSample = AmdExtHwPipePoint::HwPipeBottom;
                EnableCounterForPass(counter_list_->at(0));
            }
            else
            {
                AmdExtPerfExperimentShaderFlags mask_value = PerfShaderMaskAll;

                amd_ext_sample_config_.type         = AmdExtGpaSampleType::Cumulative;
                amd_ext_sample_config_.flags.u32All = 0;

                // Add all desired counters.
                for (size_t i = 0; i < counter_list_->size(); i++)
                {
                    const GpaHardwareCounterDescExt* counter = &hardware_counters->hardware_counters_[counter_list_->at(i)];
                    AmdExtGpuBlock                   block   = static_cast<AmdExtGpuBlock>(counter->group_id_driver);
                    UINT32 instance = static_cast<UINT32>(hardware_counters->internal_counter_groups_[counter->group_index].block_instance);
                    UINT32 event_id = static_cast<UINT32>(counter->hardware_counters->counter_index_in_group);

                    if (reinterpret_cast<Dx12GpaContext*>(GetGpaSession()->GetParentContext())->GetInstanceCount(block) <= instance)
                    {
                        DisableCounterForPass(counter_list_->at(i));
                        continue;
                    }

                    if (reinterpret_cast<Dx12GpaContext*>(GetGpaSession()->GetParentContext())->GetMaxEventIdCount(block) <= event_id)
                    {
                        DisableCounterForPass(counter_list_->at(i));
                        continue;
                    }

                    // Validate requested counter vs number of actual hardware counters and group index.
                    uint32_t group_index = counter->group_index;

                    uint32_t counters = 0;

                    if (group_index < hardware_counters->group_count_)
                    {
                        counters = hardware_counters->internal_counter_groups_[group_index].num_counters;
                    }
                    else
                    {
                        counters = hardware_counters->additional_groups_[group_index - hardware_counters->group_count_].num_counters;
                    }

                    if (counter->hardware_counters->counter_index_in_group > counters)
                    {
                        assert(counter->hardware_counters->counter_index_in_group <= counters);
                        DisableCounterForPass(counter_list_->at(i));
                        continue;
                    }

                    if (group_index > (hardware_counters->group_count_ + hardware_counters->additional_group_count_))
                    {
                        assert(group_index <= (hardware_counters->group_count_ + hardware_counters->additional_group_count_));
                        DisableCounterForPass(counter_list_->at(i));
                        continue;
                    }

                    // Add counter to valid vector.
                    AmdExtPerfCounterId this_counter = {block, instance, event_id};
                    counter_ids.push_back(this_counter);

                    // If dealing with an SQ counter, check if the the stage mask needs to be set.
                    if (counter->group_index >= hardware_counters->sq_counter_groups_[0].group_index &&
                        counter->group_index <= hardware_counters->sq_counter_groups_[hardware_counters->sq_group_count_ - 1].group_index)
                    {
                        GpaSqShaderStage stage = kSqAll;

                        for (unsigned int j = 0; j < hardware_counters->sq_group_count_ - 1; j++)
                        {
                            if (hardware_counters->sq_counter_groups_[j].group_index == counter->group_index)
                            {
                                stage = hardware_counters->sq_counter_groups_[j].sq_shader_stage;
                                break;
                            }
                        }

                        if (kSqEs == stage)
                        {
                            mask_value = PerfShaderMaskEs;
                        }
                        else if (kSqGs == stage)
                        {
                            mask_value = PerfShaderMaskGs;
                        }
                        else if (kSqVs == stage)
                        {
                            mask_value = PerfShaderMaskVs;
                        }
                        else if (kSqPs == stage)
                        {
                            mask_value = PerfShaderMaskPs;
                        }
                        else if (kSqLs == stage)
                        {
                            mask_value = PerfShaderMaskLs;
                        }
                        else if (kSqHs == stage)
                        {
                            mask_value = PerfShaderMaskHs;
                        }
                        else if (kSqCs == stage)
                        {
                            mask_value = PerfShaderMaskCs;
                        }
                    }

                    EnableCounterForPass(counter_list_->at(i));
                }

                amd_ext_sample_config_.perfCounters.numCounters = GetNumEnabledCountersForPass();
                AmdExtPerfCounterId* amd_ext_perf_counter_id    = new (std::nothrow) AmdExtPerfCounterId[counter_list_->size()];

                if (nullptr != amd_ext_perf_counter_id)
                {
                    memcpy(amd_ext_perf_counter_id, counter_ids.data(), sizeof(AmdExtPerfCounterId) * counter_ids.size());
                }

                amd_ext_sample_config_.perfCounters.pIds                   = amd_ext_perf_counter_id;
                amd_ext_sample_config_.perfCounters.spmTraceSampleInterval = 0;
                amd_ext_sample_config_.perfCounters.gpuMemoryLimit         = 0;
                amd_ext_sample_config_.sqtt                                = {};
                amd_ext_sample_config_.timing                              = {};

                // Set shader mask.
                amd_ext_sample_config_.flags.sqShaderMask = 1;
                amd_ext_sample_config_.sqShaderMask       = mask_value;
            }

            // Insert L2 cache invalidate and flush around counter sample.
            if (GetGpaSession()->GetParentContext()->IsInvalidateAndFlushL2CacheEnabled())
            {
                amd_ext_sample_config_.flags.cacheFlushOnCounterCollection = 1;
            }

            is_sample_config_initialized_ = true;
        }
    }
}

void Dx12GpaPass::ResetPass() const
{
    LockCommandListMutex();

    for (auto it = GetCmdList().begin(); it != GetCmdList().end(); ++it)
    {
        Dx12GpaCommandList* dx12_cmd_list = reinterpret_cast<Dx12GpaCommandList*>(*it);
        dx12_cmd_list->ReleaseNonGPAResources();
    }

    UnlockCommandListMutex();
}
