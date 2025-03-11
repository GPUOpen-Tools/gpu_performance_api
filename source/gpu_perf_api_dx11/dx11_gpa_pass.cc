//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX11 GPA Pass Object Implementation
//==============================================================================

#include "gpu_perf_api_dx11/dx11_gpa_pass.h"

#include "gpu_perf_api_common/gpa_context_counter_mediator.h"

#include "gpu_perf_api_counter_generator/gpa_hardware_counters.h"

#include "gpu_perf_api_dx11/dx11_gpa_command_list.h"
#include "gpu_perf_api_dx11/dx11_gpa_sample.h"

Dx11GpaPass::Dx11GpaPass(IGpaSession* gpa_session, PassIndex pass_index, GpaCounterSource counter_source, CounterList* pass_counters)
    : GpaPass(gpa_session, pass_index, counter_source, pass_counters)
{
    InitializeCounterInfo();
}

GpaSample* Dx11GpaPass::CreateApiSpecificSample(IGpaCommandList* cmd_list, GpaSampleType sample_type, ClientSampleId sample_id)
{
    GpaSample* ret_sample = nullptr;

    Dx11GpaSample* dx11_gpa_sample = new (std::nothrow) Dx11GpaSample(this, cmd_list, sample_type, sample_id);

    if (nullptr != dx11_gpa_sample)
    {
        ret_sample = dx11_gpa_sample;
    }

    return ret_sample;
}

bool Dx11GpaPass::ContinueSample(ClientSampleId src_sample_id, IGpaCommandList* primary_gpa_cmd_list)
{
    UNREFERENCED_PARAMETER(src_sample_id);
    UNREFERENCED_PARAMETER(primary_gpa_cmd_list);
    bool status = static_cast<bool>(kGpaStatusErrorApiNotSupported);  // This is only to show that this functionality is not supported in DX11.
    status      = false;
    return status;
}

IGpaCommandList* Dx11GpaPass::CreateApiSpecificCommandList(void* cmd, CommandListId command_list_id, GpaCommandListType cmdType)
{
    UNREFERENCED_PARAMETER(cmd);
    UNREFERENCED_PARAMETER(cmdType);

    Dx11GpaCommandList* ret_cmd_list = new (std::nothrow) Dx11GpaCommandList(GetGpaSession(), this, command_list_id);

    return ret_cmd_list;
}

bool Dx11GpaPass::EndSample(IGpaCommandList* cmd_list)
{
    bool retVal = false;

    if (nullptr != cmd_list)
    {
        retVal = cmd_list->CloseLastSample();
    }

    return retVal;
}

bool Dx11GpaPass::GetSqEngineParamValue(CounterIndex counter_index, SqEngineParamValue& sq_engine_param_value)
{
    bool ret_val = false;

    if (counter_shader_mask_value_map_.find(counter_index) != counter_shader_mask_value_map_.end())
    {
        sq_engine_param_value = counter_shader_mask_value_map_[counter_index];
        ret_val               = true;
    }

    return ret_val;
}

void Dx11GpaPass::InitializeCounterInfo()
{
    Dx11GpaContext* dx11_gpa_context = reinterpret_cast<Dx11GpaContext*>(GetGpaSession()->GetParentContext());

    if (counter_list_ == nullptr)
    {
        GPA_LOG_ERROR("Invalid counter list.");
        return;
    }

    if (IsTimingPass())
    {
        for (CounterIndex counter_iter = 0; counter_iter < counter_list_->size(); counter_iter++)
        {
            EnableCounterForPass(counter_list_->at(counter_iter));
        }
    }
    else
    {
        if (nullptr != dx11_gpa_context)
        {
            IGpaCounterAccessor*       counter_accessor  = GpaContextCounterMediator::Instance()->GetCounterAccessor(GetGpaSession());
            assert(counter_accessor != nullptr);
            if (counter_accessor == nullptr)
            {
                GPA_LOG_ERROR("Invalid counter accessor. Disabling all counters in pass.");
                for (size_t i = 0; i < counter_list_->size(); ++i)
                {
                    CounterIndex counter_index = counter_list_->at(i);
                    DisableCounterForPass(counter_index);
                }

                return;
            }

            const GpaHardwareCounters* hardware_counters = counter_accessor->GetHardwareCounters();
            assert(hardware_counters != nullptr);
            if (hardware_counters == nullptr)
            {
                GPA_LOG_ERROR("Invalid hardware counters. Disabling all counters in pass.");
                for (size_t i = 0; i < counter_list_->size(); ++i)
                {
                    CounterIndex counter_index = counter_list_->at(i);
                    DisableCounterForPass(counter_index);
                }

                return;
            }

            for (CounterIndex counter_iter = 0; counter_iter < counter_list_->size(); counter_iter++)
            {
                const GpaHardwareCounterDescExt* counter  = &hardware_counters->hardware_counters_.at(counter_list_->at(counter_iter));
                PE_BLOCK_ID                      block_id = static_cast<PE_BLOCK_ID>(counter->group_id_driver);
                UINT32 instance = static_cast<UINT32>(hardware_counters->internal_counter_groups_[counter->group_index].block_instance);
                UINT32 event_id = static_cast<UINT32>(counter->hardware_counters->counter_index_in_group);

                if (PE_BLOCK_RLC == block_id)
                {
                    // RLC counters cause a reboot, so don't allow them to be enabled.
                    GPA_LOG_ERROR("An unstable counter is included in the counter selection. Please remove it and re-profile.");
                    DisableAllCountersForPass();
                    break;
                }

                // On mid and low end hardware, not all block instances are available. This logic makes sure that we only attempt to
                // enable counters for block instances which exist.
                if (instance >= dx11_gpa_context->GetNumInstances(block_id) || event_id > dx11_gpa_context->GetMaxEventId(block_id))
                {
                    // Don't try to enable this counter. When the results are collected, this will be given
                    // a result of 0, so that it has no contribution.
                    DisableCounterForPass(counter_list_->at(counter_iter));
                }
                else
                {
                    EnableCounterForPass(counter_list_->at(counter_iter));
                }
            }

            if (GetEnabledCounterCount() > 0)
            {
                InitializeCounterExperimentParameters();
            }
        }
    }
}

void Dx11GpaPass::InitializeCounterExperimentParameters()
{
    IGpaCounterAccessor*       counter_accessor  = GpaContextCounterMediator::Instance()->GetCounterAccessor(GetGpaSession());
    const GpaHardwareCounters* hardware_counters = counter_accessor->GetHardwareCounters();

    auto PopulateExperimentParams = [&](const CounterIndex& counter_index) -> bool {
        const GpaHardwareCounterDescExt* counter = &hardware_counters->hardware_counters_.at(counter_index);

        if (counter->group_id_driver == PE_BLOCK_SQ ||
            counter->group_id_driver == PE_BLOCK_SQWGP)
        {
            // Set the engine parameter if the SQ block is being used
            // convert the instance to a shader mask.
            unsigned int mask_value = PE_SHADER_MASK_ALL;

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
                mask_value = PE_SHADER_MASK_ES;
            }
            else if (kSqGs == stage)
            {
                mask_value = PE_SHADER_MASK_GS;
            }
            else if (kSqVs == stage)
            {
                mask_value = PE_SHADER_MASK_VS;
            }
            else if (kSqPs == stage)
            {
                mask_value = PE_SHADER_MASK_PS;
            }
            else if (kSqLs == stage)
            {
                mask_value = PE_SHADER_MASK_LS;
            }
            else if (kSqHs == stage)
            {
                mask_value = PE_SHADER_MASK_HS;
            }
            else if (kSqCs == stage)
            {
                mask_value = PE_SHADER_MASK_CS;
            }

            counter_shader_mask_value_map_.insert(std::pair<CounterIndex, SqEngineParamValue>(counter_index, mask_value));
        }

        return true;
    };

    IterateEnabledCounterList(PopulateExperimentParams);
}
