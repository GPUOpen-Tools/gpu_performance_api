//==============================================================================
// Copyright (c) 2016-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for DX11 counter generation for AMD HW.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx11.h"

#ifdef EXTRA_COUNTER_INFO
#include <sstream>
#endif

#include <d3d11.h>

#include "AmdDxCounter.h"
#include "AmdDxExtPerfProfile.h"

#include "gpu_perf_api_common/logging.h"

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx11.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx12.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx11.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx12.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx10_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx103_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx11_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx12_asics.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

GpaCounterGeneratorDx11::GpaCounterGeneratorDx11(GpaSessionSampleType sample_type)
    : GpaCounterGeneratorDx11Base(sample_type)
{
    // Enable all counters.
    GpaCounterGeneratorBase::SetAllowedCounters(true, true);

    for (int gen = GDT_HW_GENERATION_GFX10; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(kGpaApiDirectx11, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

/// @brief Function translates between GPA's block id and the DX11 driver's PE_BLOCK_ID enum.
///
/// The driver gives each block an ID, but ignores the instance. GPA treats each instance as a different
/// block, so we need to translate.
///
/// @param [in] generation The generation whose block id needs to be calculated.
/// @param [in] group The group for which the block id needs to be calculated.
///
/// @return The block id according to the driver.
static GpaUInt32 CalculateBlockIdDx11(GDT_HW_GENERATION generation, const GpaCounterGroupDesc& group)
{
    const GpaUInt32 group_index = group.group_index;

    if (GpaCounterGeneratorDx11Base::IsAmdGpu(generation))
    {
        if (generation == GDT_HW_GENERATION_GFX10)
        {
            return counter_dx11_gfx10::kHwDx11DriverBlockIdGfx10[group_index];
        }

        if (generation == GDT_HW_GENERATION_GFX103)
        {
            return counter_dx11_gfx103::kHwDx11DriverBlockIdGfx103[group_index];
        }

        if (generation == GDT_HW_GENERATION_GFX11)
        {
            return counter_dx11_gfx11::kHwDx11DriverBlockIdGfx11[group_index];
        }

        if (generation == GDT_HW_GENERATION_GFX12)
        {
            return counter_dx11_gfx12::kHwDx11DriverBlockIdGfx12[group_index];
        }

        // Don't recognize the specified hardware generation.
        // Need to add support or fix a bug.
        assert(generation == GDT_HW_GENERATION_SOUTHERNISLAND);
    }

    return group_index;
}

bool GpaCounterGeneratorDx11::GenerateInternalCounters(GpaHardwareCounters* hardware_counters, GDT_HW_GENERATION generation)
{
    hardware_counters->hardware_counters_.clear();

    GpaHardwareCounterDescExt counter = {};

    unsigned int global_counter_index      = 0;
    unsigned int global_counter_group_base = 0;
    unsigned int offset                    = 0;

    const unsigned int counter_array_size = static_cast<unsigned int>(hardware_counters->counter_groups_array_.size());
    // Iterate over counter array, which will either be populated with only exposed counters or all counters in internal builds.
    for (unsigned int g = 0; g < counter_array_size; g++)
    {
        const gpa_array_view<GpaHardwareCounterDesc>& group_counters = hardware_counters->counter_groups_array_[g];
        const GpaCounterGroupDesc&                    group          = hardware_counters->internal_counter_groups_[g + offset];

        const unsigned int num_exposed_counters_in_group = static_cast<unsigned int>(group_counters.size());
        const unsigned int total_counters_in_group       = static_cast<unsigned int>(group.num_counters);

        if (strcmp(group_counters[0].group, group.name) != 0)
        {
            global_counter_group_base += total_counters_in_group;
            offset++;
            g--;
            continue;
        }

        // Calculate per-block values outside the for loop.
        const GpaUInt32 block_id = CalculateBlockIdDx11(generation, group);

        for (unsigned int c = 0; c < num_exposed_counters_in_group; c++)
        {
            counter.group_index       = g + offset;
            counter.hardware_counters = &(group_counters[c]);
            counter.group_id_driver   = block_id;

            global_counter_index = static_cast<GpaUInt32>(global_counter_group_base + group_counters[c].counter_index_in_group);

            if (hardware_counters->IsTimestampBlockId(counter.group_index))
            {
                if (hardware_counters->IsTimeCounterIndex(global_counter_index))
                {
                    counter.counter_id_driver = AmdCtrEncodeApiCounter(AmdGpuTime);
                }
                else
                {
                    counter.counter_id_driver = AmdCtrEncodeApiCounter(AmdStartOfPipeTimestamp);
                }
            }
            else
            {
                counter.counter_id_driver = 0;
            }

            hardware_counters->hardware_counters_.insert(std::pair<GpaUInt32, GpaHardwareCounterDescExt>(global_counter_index, counter));
        }
        // Adding total number of counters in group to "skip" past counters just added above.
        global_counter_group_base += total_counters_in_group;
    }

    return true;
}

GpaStatus GpaCounterGeneratorDx11::GeneratePublicCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GpaDerivedCounters* public_counters)
{
    GpaStatus status = kGpaStatusErrorHardwareNotSupported;

    if (nullptr == public_counters)
    {
        status = kGpaStatusErrorNullPointer;
    }
    else if (public_counters->GetCountersGenerated())
    {
        status = kGpaStatusOk;
    }
    else
    {
        public_counters->Clear();

        if (desired_generation == GDT_HW_GENERATION_GFX10)
        {
            AutoDefinePublicDerivedCountersDx11Gfx10(*public_counters);
            dx11_gfx10_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            status = kGpaStatusOk;
        }
        else if (desired_generation == GDT_HW_GENERATION_GFX103)
        {
            AutoDefinePublicDerivedCountersDx11Gfx103(*public_counters);
            dx11_gfx103_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            status = kGpaStatusOk;
        }
        else if (desired_generation == GDT_HW_GENERATION_GFX11)
        {
            AutoDefinePublicDerivedCountersDx11Gfx11(*public_counters);
            dx11_gfx11_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            status = kGpaStatusOk;
        }
        else if (desired_generation == GDT_HW_GENERATION_GFX12)
        {
            AutoDefinePublicDerivedCountersDx11Gfx12(*public_counters);
            dx11_gfx12_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            status = kGpaStatusOk;
        }
        else
        {
            GPA_LOG_ERROR("Unrecognized or unhandled hardware generation.");
        }
    }

    GpaStatus internal_status = kGpaStatusErrorHardwareNotSupported;

    if (kGpaStatusOk == status)
    {
        public_counters->SetCountersGenerated(true);
    }
    else
    {
        status = internal_status;
    }

    return status;
}

GpaStatus GpaCounterGeneratorDx11::GenerateHardwareCounters(GDT_HW_GENERATION    desired_generation,
                                                            GDT_HW_ASIC_TYPE     asic_type,
                                                            GpaHardwareCounters* hardware_counters)
{
    UNREFERENCED_PARAMETER(asic_type);

    if (nullptr == hardware_counters)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (hardware_counters->counters_generated_)  // Only generate counters once to improve performance.
    {
        return kGpaStatusOk;
    }

    hardware_counters->Clear();

    if (desired_generation == GDT_HW_GENERATION_GFX10)
    {
        hardware_counters->counter_groups_array_                             = counter_dx11_gfx10::kDx11CounterGroupArrayGfx10;
        hardware_counters->internal_counter_groups_                          = counter_dx11_gfx10::kHwDx11GroupsGfx10;
        hardware_counters->sq_counter_groups_                                = counter_dx11_gfx10::kHwDx11SqGroupsGfx10;
        hardware_counters->sq_group_count_                                   = counter_dx11_gfx10::kHwDx11SqGroupCountGfx10;
        hardware_counters->timestamp_block_ids_                              = counter_dx11_gfx10::kHwDx11TimestampBlockIdsGfx10;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_dx11_gfx10::kHwDx11GpuTimeBottomToBottomDurationIndexGfx10;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_dx11_gfx10::kHwDx11GpuTimeBottomToBottomStartIndexGfx10;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_dx11_gfx10::kHwDx11GpuTimeBottomToBottomEndIndexGfx10;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_dx11_gfx10::kHwDx11GpuTimeTopToBottomDurationIndexGfx10;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_dx11_gfx10::kHwDx11GpuTimeTopToBottomStartIndexGfx10;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_dx11_gfx10::kHwDx11GpuTimeTopToBottomEndIndexGfx10;
        hardware_counters->isolated_groups_                                  = counter_dx11_gfx10::kHwDx11SqIsolatedGroupsGfx10;
        hardware_counters->isolated_group_count_                             = counter_dx11_gfx10::kHwDx11SqIsolatedGroupCountGfx10;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX103)
    {
        hardware_counters->counter_groups_array_                             = counter_dx11_gfx103::kDx11CounterGroupArrayGfx103;
        hardware_counters->internal_counter_groups_                          = counter_dx11_gfx103::kHwDx11GroupsGfx103;
        hardware_counters->sq_counter_groups_                                = counter_dx11_gfx103::kHwDx11SqGroupsGfx103;
        hardware_counters->sq_group_count_                                   = counter_dx11_gfx103::kHwDx11SqGroupCountGfx103;
        hardware_counters->timestamp_block_ids_                              = counter_dx11_gfx103::kHwDx11TimestampBlockIdsGfx103;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_dx11_gfx103::kHwDx11GpuTimeBottomToBottomDurationIndexGfx103;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_dx11_gfx103::kHwDx11GpuTimeBottomToBottomStartIndexGfx103;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_dx11_gfx103::kHwDx11GpuTimeBottomToBottomEndIndexGfx103;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_dx11_gfx103::kHwDx11GpuTimeTopToBottomDurationIndexGfx103;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_dx11_gfx103::kHwDx11GpuTimeTopToBottomStartIndexGfx103;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_dx11_gfx103::kHwDx11GpuTimeTopToBottomEndIndexGfx103;
        hardware_counters->isolated_groups_                                  = counter_dx11_gfx103::kHwDx11SqIsolatedGroupsGfx103;
        hardware_counters->isolated_group_count_                             = counter_dx11_gfx103::kHwDx11SqIsolatedGroupCountGfx103;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX11)
    {
        hardware_counters->counter_groups_array_                             = counter_dx11_gfx11::kDx11CounterGroupArrayGfx11;
        hardware_counters->internal_counter_groups_                          = counter_dx11_gfx11::kHwDx11GroupsGfx11;
        hardware_counters->sq_counter_groups_                                = counter_dx11_gfx11::kHwDx11SqGroupsGfx11;
        hardware_counters->sq_group_count_                                   = counter_dx11_gfx11::kHwDx11SqGroupCountGfx11;
        hardware_counters->timestamp_block_ids_                              = counter_dx11_gfx11::kHwDx11TimestampBlockIdsGfx11;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_dx11_gfx11::kHwDx11GpuTimeBottomToBottomDurationIndexGfx11;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_dx11_gfx11::kHwDx11GpuTimeBottomToBottomStartIndexGfx11;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_dx11_gfx11::kHwDx11GpuTimeBottomToBottomEndIndexGfx11;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_dx11_gfx11::kHwDx11GpuTimeTopToBottomDurationIndexGfx11;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_dx11_gfx11::kHwDx11GpuTimeTopToBottomStartIndexGfx11;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_dx11_gfx11::kHwDx11GpuTimeTopToBottomEndIndexGfx11;
        hardware_counters->isolated_groups_                                  = counter_dx11_gfx11::kHwDx11SqIsolatedGroupsGfx11;
        hardware_counters->isolated_group_count_                             = counter_dx11_gfx11::kHwDx11SqIsolatedGroupCountGfx11;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX12)
    {
        hardware_counters->counter_groups_array_                             = counter_dx11_gfx12::kDx11CounterGroupArrayGfx12;
        hardware_counters->internal_counter_groups_                          = counter_dx11_gfx12::kHwDx11GroupsGfx12;
        hardware_counters->sq_counter_groups_                                = counter_dx11_gfx12::kHwDx11SqGroupsGfx12;
        hardware_counters->sq_group_count_                                   = counter_dx11_gfx12::kHwDx11SqGroupCountGfx12;
        hardware_counters->timestamp_block_ids_                              = counter_dx11_gfx12::kHwDx11TimestampBlockIdsGfx12;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_dx11_gfx12::kHwDx11GpuTimeBottomToBottomDurationIndexGfx12;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_dx11_gfx12::kHwDx11GpuTimeBottomToBottomStartIndexGfx12;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_dx11_gfx12::kHwDx11GpuTimeBottomToBottomEndIndexGfx12;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_dx11_gfx12::kHwDx11GpuTimeTopToBottomDurationIndexGfx12;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_dx11_gfx12::kHwDx11GpuTimeTopToBottomStartIndexGfx12;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_dx11_gfx12::kHwDx11GpuTimeTopToBottomEndIndexGfx12;
        hardware_counters->isolated_groups_                                  = counter_dx11_gfx12::kHwDx11SqIsolatedGroupsGfx12;
        hardware_counters->isolated_group_count_                             = counter_dx11_gfx12::kHwDx11SqIsolatedGroupCountGfx12;
    }
    else
    {
        GPA_LOG_ERROR("Unrecognized or unhandled hardware generation.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    hardware_counters->eop_time_counter_indices_.insert(hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_);
    hardware_counters->eop_time_counter_indices_.insert(hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_);
    hardware_counters->eop_time_counter_indices_.insert(hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_);

    hardware_counters->top_time_counter_indices_.insert(hardware_counters->gpu_time_top_to_bottom_duration_counter_index_);
    hardware_counters->top_time_counter_indices_.insert(hardware_counters->gpu_time_top_to_bottom_start_counter_index_);
    hardware_counters->top_time_counter_indices_.insert(hardware_counters->gpu_time_top_to_bottom_end_counter_index_);

    // Need to count total number of internal counters, since split into groups.
    if (!GenerateInternalCounters(hardware_counters, desired_generation))
    {
        GPA_LOG_ERROR("Unable to generate internal or whitelist counters.");
        hardware_counters->current_group_used_counts_.clear();
        return kGpaStatusErrorContextNotOpen;
    }

    hardware_counters->counters_generated_ = true;

    unsigned int group_count = static_cast<unsigned int>(hardware_counters->counter_groups_array_.size());
    hardware_counters->current_group_used_counts_.resize(group_count);
    hardware_counters->block_instance_counters_index_cache_.clear();
    hardware_counters->gpa_hw_block_hardware_block_group_cache_.clear();
    hardware_counters->counter_hardware_info_map_.clear();
    return kGpaStatusOk;
}

GpaStatus GpaCounterGeneratorDx11::GenerateHardwareExposedCounters(GDT_HW_GENERATION    desired_generation,
                                                                   GDT_HW_ASIC_TYPE     asic_type,
                                                                   GpaHardwareCounters* hardware_counters)
{
    UNREFERENCED_PARAMETER(asic_type);

    if (hardware_counters->hardware_exposed_counters_generated_)
    {
        return kGpaStatusOk;
    }

    if (desired_generation == GDT_HW_GENERATION_GFX10)
    {
        hardware_counters->hardware_exposed_counters_       = counter_dx11_gfx10::kDx11CounterGroupArrayGfx10;
        hardware_counters->hardware_exposed_counter_groups_ = counter_dx11_gfx10::kHwDx11ExposedCountersByGroupGfx10;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX103)
    {
        hardware_counters->hardware_exposed_counters_       = counter_dx11_gfx103::kDx11CounterGroupArrayGfx103;
        hardware_counters->hardware_exposed_counter_groups_ = counter_dx11_gfx103::kHwDx11ExposedCountersByGroupGfx103;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX11)
    {
        hardware_counters->hardware_exposed_counters_       = counter_dx11_gfx11::kDx11CounterGroupArrayGfx11;
        hardware_counters->hardware_exposed_counter_groups_ = counter_dx11_gfx11::kHwDx11ExposedCountersByGroupGfx11;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX12)
    {
        hardware_counters->hardware_exposed_counters_       = counter_dx11_gfx12::kDx11CounterGroupArrayGfx12;
        hardware_counters->hardware_exposed_counter_groups_ = counter_dx11_gfx12::kHwDx11ExposedCountersByGroupGfx12;
    }
    else
    {
        GPA_LOG_ERROR("Unrecognized or unhandled hardware generation.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    hardware_counters->hardware_exposed_counters_generated_ = MapHardwareExposedCounter(hardware_counters);
    return hardware_counters->hardware_exposed_counters_generated_ ? kGpaStatusOk : kGpaStatusErrorFailed;
}
