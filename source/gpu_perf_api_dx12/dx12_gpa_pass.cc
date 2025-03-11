//==============================================================================
// Copyright (c) 2017-2023 Advanced Micro Devices, Inc. All rights reserved.
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
{
    if (!amd_ext_sample_config_.Initialize(gpa_session, GetCounterSource(), counter_list_, this, IsTimingPass()))
    {
        GPA_LOG_ERROR("Sample configuration failed to initialize for pass %u.", pass_index);
    }
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
    ResetPass();
}

void Dx12GpaPass::ResetPass() const
{
    LockCommandListMutex();

    for (auto it = GetCmdList().begin(); it != GetCmdList().end(); ++it)
    {
        Dx12GpaCommandList* dx12_cmd_list = reinterpret_cast<Dx12GpaCommandList*>(*it);
        dx12_cmd_list->ReleaseNonGpaResources();
    }

    UnlockCommandListMutex();
}

const Dx12GpaSampleConfig& Dx12GpaPass::GetAmdExtSampleConfig()
{
    // Update settings in case the SPM durations or sampling interval has been changed.
    amd_ext_sample_config_.UpdateSettings();
    return amd_ext_sample_config_;
}
