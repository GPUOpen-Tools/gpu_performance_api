//==============================================================================
// Copyright (c) 2018-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX12 GPA Sample Configuration Header.
//==============================================================================

#include "dx12_gpa_sample_config.h"

#include "gpa_context_counter_mediator.h"
#include "gpa_hardware_counters.h"
#include "dx12_gpa_session.h"
#include "dx12_gpa_context.h"
#include "ADLUtil.h"

Dx12GpaSampleConfig::~Dx12GpaSampleConfig()
{
    if (amd_ext_sample_config_.perfCounters.pIds != nullptr)
    {
        delete[] amd_ext_sample_config_.perfCounters.pIds;
        amd_ext_sample_config_.perfCounters.pIds = nullptr;
    }
}

bool Dx12GpaSampleConfig::Initialize(IGpaSession*       session,
                                     GpaCounterSource   counter_source,
                                     const CounterList* counter_list,
                                     GpaPass*           gpa_pass,
                                     bool               is_timing_pass)
{
    assert(session);
    if (nullptr == session)
    {
        GPA_LOG_ERROR("Null session supplied to Dx12GpaSampleConfig::Initialize.");
        return false;
    }

    if (is_sample_config_initialized_)
    {
        return true;
    }

    amd_ext_sample_config_ = {};

    counter_result_entries_.clear();

    uint32_t sample_offset = 0;

    sample_type_ = session->GetSampleType();
    
    if (GpaCounterSource::kHardware == counter_source)
    {
        if (kGpaSessionSampleTypeDiscreteCounter == sample_type_ && nullptr == gpa_pass)
        {
            GPA_LOG_ERROR("Configuring discrete counters requires a GpaPass object.");
            return false;
        }

        if (nullptr == counter_list)
        {
            GPA_LOG_ERROR("Configuring discrete counters requires a list of counters.");
            return false;
        }

        std::vector<AmdExtPerfCounterId> counter_ids;

        IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(session->GetParentContext());
        const GpaHardwareCounters* hardware_counters = counter_accessor->GetHardwareCounters();

        if (!counter_list->empty())
        {
            if (is_timing_pass)
            {
                amd_ext_sample_config_.type = AmdExtGpaSampleType::Timing;
                amd_ext_sample_config_.timing.preSample = AmdExtHwPipePoint::HwPipeBottom;

                if (hardware_counters->IsTopOfPipeCounterIndex(counter_list->at(0)))
                {
                    amd_ext_sample_config_.timing.preSample = AmdExtHwPipePoint::HwPipeTop;
                }
                else if (hardware_counters->IsBottomOfPipeCounterIndex(counter_list->at(0)))
                {
                    amd_ext_sample_config_.timing.preSample = AmdExtHwPipePoint::HwPipeBottom;
                }

                amd_ext_sample_config_.timing.postSample = AmdExtHwPipePoint::HwPipeBottom;
                gpa_pass->EnableCounterForPass(counter_list->at(0));
            }
            else
            {
                AmdExtPerfExperimentShaderFlags mask_value = PerfShaderMaskAll;

                amd_ext_sample_config_.type         = AmdExtGpaSampleType::Cumulative;
                amd_ext_sample_config_.flags.u32All = 0;

                // Add all desired counters.
                for (size_t i = 0; i < counter_list->size(); i++)
                {
                    const GpaUInt32 global_counter_index  = (GpaUInt32)counter_list->at(i);
                    const auto      hardware_counter_iter = hardware_counters->hardware_counters_.find(global_counter_index);
                    if (hardware_counter_iter == hardware_counters->hardware_counters_.cend())
                    {
                        GPA_LOG_ERROR("Failed to locate hardware counter using global index %d.", global_counter_index);
                        return false;
                    }

                    const GpaHardwareCounterDescExt* hw_counter_desc = &(hardware_counter_iter->second);
                    AmdExtGpuBlock                   block           = static_cast<AmdExtGpuBlock>(hw_counter_desc->group_id_driver);
                    UINT32 instance = static_cast<UINT32>(hardware_counters->internal_counter_groups_[hw_counter_desc->group_index].block_instance);
                    UINT32 event_id = static_cast<UINT32>(hw_counter_desc->hardware_counters->counter_index_in_group);

                    if (reinterpret_cast<Dx12GpaContext*>(session->GetParentContext())->GetNumInstances(block) <= instance)
                    {
                        assert(nullptr != gpa_pass);
                        gpa_pass->DisableCounterForPass(counter_list->at(i));
                        GPA_LOG_DEBUG_MESSAGE("Disabling counter at index %s as number of block instances is less than the current instance.", i);
                        counter_result_entries_.push_back(CounterResultEntry{counter_list->at(i), 0, 0});
                        continue;
                    }

                    if (reinterpret_cast<Dx12GpaContext*>(session->GetParentContext())->GetMaxEventId(block) <= event_id)
                    {
                        assert(nullptr != gpa_pass);
                        gpa_pass->DisableCounterForPass(counter_list->at(i));
                        GPA_LOG_DEBUG_MESSAGE("Disabling counter at index %s as max event ID in context is less than the current event ID.", i);
                        counter_result_entries_.push_back(CounterResultEntry{counter_list->at(i), 0, 0});
                        continue;
                    }

                    // Validate requested counter vs number of actual hardware counters and group index.
                    const uint32_t group_index = hw_counter_desc->group_index;

                    uint32_t counters = 0;

                    if (group_index < hardware_counters->internal_counter_groups_.size())
                    {
                        counters = hardware_counters->internal_counter_groups_[group_index].num_counters;
                    }
                    else
                    {
                        counters = hardware_counters->additional_groups_[group_index - hardware_counters->internal_counter_groups_.size()].num_counters;
                    }

                    if (hw_counter_desc->hardware_counters->counter_index_in_group > counters)
                    {
                        assert(hw_counter_desc->hardware_counters->counter_index_in_group <= counters);
                        assert(nullptr != gpa_pass);
                        gpa_pass->DisableCounterForPass(counter_list->at(i));
                        GPA_LOG_ERROR("Disabling counter at index %s as the counter index in the group does not correspond to a known counter.", i);
                        counter_result_entries_.push_back(CounterResultEntry{counter_list->at(i), 0, 0});
                        continue;
                    }

                    if (group_index > (hardware_counters->internal_counter_groups_.size() + hardware_counters->additional_group_count_))
                    {
                        assert(group_index <= (hardware_counters->internal_counter_groups_.size() + hardware_counters->additional_group_count_));
                        assert(nullptr != gpa_pass);
                        gpa_pass->DisableCounterForPass(counter_list->at(i));
                        GPA_LOG_ERROR("Disabling counter at index %s as the counter's group index does not correspond to a known group.", i);
                        counter_result_entries_.push_back(CounterResultEntry{counter_list->at(i), 0, 0});
                        continue;
                    }

                    // Add counter to valid vector
                    AmdExtPerfCounterId this_counter = {block, instance, event_id};
                    counter_ids.push_back(this_counter);

                    // If dealing with an SQ counter, check if the stage mask needs to be set.
                    if (block == AmdExtGpuBlock::Sq || block == AmdExtGpuBlock::SqWgp)
                    {
                        GpaSqShaderStage stage = kSqAll;

                        for (unsigned int j = 0; j < hardware_counters->sq_group_count_ - 1; j++)
                        {
                            if (hardware_counters->sq_counter_groups_[j].group_index == hw_counter_desc->group_index)
                            {
                                stage = hardware_counters->sq_counter_groups_[j].sq_shader_stage;
                                break;
                            }
                        }

                        if (stage == kSqEs)
                        {
                            mask_value = PerfShaderMaskEs;
                        }
                        else if (stage == kSqGs)
                        {
                            mask_value = PerfShaderMaskGs;
                        }
                        else if (stage == kSqVs)
                        {
                            mask_value = PerfShaderMaskVs;
                        }
                        else if (stage == kSqPs)
                        {
                            mask_value = PerfShaderMaskPs;
                        }
                        else if (stage == kSqLs)
                        {
                            mask_value = PerfShaderMaskLs;
                        }
                        else if (stage == kSqHs)
                        {
                            mask_value = PerfShaderMaskHs;
                        }
                        else if (stage == kSqCs)
                        {
                            mask_value = PerfShaderMaskCs;
                        }
                    }

                    assert(nullptr != gpa_pass);
                    gpa_pass->EnableCounterForPass(counter_list->at(i));

                    counter_result_entries_.push_back(CounterResultEntry{counter_list->at(i), sample_offset, 1});

                    ++sample_offset;
                }

                amd_ext_sample_config_.perfCounters.numCounters = static_cast<UINT32>(counter_ids.size());
                AmdExtPerfCounterId* amd_ext_perf_counter_id = new (std::nothrow) AmdExtPerfCounterId[counter_ids.size()];

                if (nullptr != amd_ext_perf_counter_id)
                {
                    memcpy(amd_ext_perf_counter_id, counter_ids.data(), sizeof(AmdExtPerfCounterId) * counter_ids.size());
                }

                amd_ext_sample_config_.perfCounters.pIds = amd_ext_perf_counter_id;
                amd_ext_sample_config_.perfCounters.spmTraceSampleInterval = 0;
                amd_ext_sample_config_.perfCounters.gpuMemoryLimit         = 0;
                amd_ext_sample_config_.sqtt                                = {};
                amd_ext_sample_config_.timing                              = {};

                // set shader mask
                amd_ext_sample_config_.flags.sqShaderMask = 1;
                amd_ext_sample_config_.sqShaderMask       = mask_value;

                amd_ext_sample_config_.flags.sqWgpShaderMask = 1;
                amd_ext_sample_config_.sqWgpShaderMask       = mask_value;
            }

            // Insert L2 cache invalidate and flush around counter sample
            if (session->GetParentContext()->IsInvalidateAndFlushL2CacheEnabled())
            {
                amd_ext_sample_config_.flags.cacheFlushOnCounterCollection = 1;
            }

            amd_ext_sample_config_.flags.sampleInternalOperations = 1;

            is_sample_config_initialized_ = true;
        }
    }

    return true;
}
