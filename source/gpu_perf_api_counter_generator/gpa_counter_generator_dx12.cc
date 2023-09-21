//==============================================================================
// Copyright (c) 2015-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for DX12 counter generation.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx12.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx8.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx9.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx11.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx8.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx9.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx11.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx8_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx9_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx10_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx103_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx11_asics.h"

bool GpaCounterGeneratorDx12::IsAmdGpu(GDT_HW_GENERATION generation)
{
    return generation >= GDT_HW_GENERATION_FIRST_AMD && generation < GDT_HW_GENERATION_LAST;
}

GpaUInt32 GpaCounterGeneratorDx12::CalculateBlockIdDx12(GDT_HW_GENERATION generation, const GpaCounterGroupDesc* group)
{
    GpaUInt32 group_index = static_cast<GpaUInt32>(group->group_index);

    if (IsAmdGpu(generation))
    {
        if (generation == GDT_HW_GENERATION_VOLCANICISLAND)
        {
            return static_cast<GpaUInt32>(counter_dx12_gfx8::kHwDx12DriverEnumGfx8[group_index]);
        }

        if (generation == GDT_HW_GENERATION_GFX9)
        {
            return static_cast<GpaUInt32>(counter_dx12_gfx9::kHwDx12DriverEnumGfx9[group_index]);
        }

        if (generation == GDT_HW_GENERATION_GFX10)
        {
            return static_cast<GpaUInt32>(counter_dx12_gfx10::kHwDx12DriverEnumGfx10[group_index]);
        }

        if (generation == GDT_HW_GENERATION_GFX103)
        {
            return static_cast<GpaUInt32>(counter_dx12_gfx103::kHwDx12DriverEnumGfx103[group_index]);
        }

        if (generation == GDT_HW_GENERATION_GFX11)
        {
            return static_cast<GpaUInt32>(counter_dx12_gfx11::kHwDx12DriverEnumGfx11[group_index]);
        }

        // Don't recognize the specified hardware generation.
        // Need to add support or fix a bug.
        assert(generation == GDT_HW_GENERATION_SOUTHERNISLAND);
    }

    return group_index;
}

GpaCounterGeneratorDx12::GpaCounterGeneratorDx12()
{
    // Enable public and hw counters.
    GpaCounterGeneratorBase::SetAllowedCounters(true, true);

    for (int gen = GDT_HW_GENERATION_VOLCANICISLAND; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(kGpaApiDirectx12, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GpaStatus GpaCounterGeneratorDx12::GeneratePublicCounters(GDT_HW_GENERATION   desired_generation,
                                                          GDT_HW_ASIC_TYPE    asic_type,
                                                          GpaUInt8            generate_asic_specific_counters,
                                                          GpaDerivedCounters* public_counters)
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

        switch (desired_generation)
        {
        case GDT_HW_GENERATION_VOLCANICISLAND:
        {
            AutoDefinePublicDerivedCountersDx12Gfx8(*public_counters);

            if (generate_asic_specific_counters)
            {
                dx12_gfx8_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = kGpaStatusOk;
        }
        break;

        case GDT_HW_GENERATION_GFX9:
        {
            AutoDefinePublicDerivedCountersDx12Gfx9(*public_counters);

            if (generate_asic_specific_counters)
            {
                dx12_gfx9_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = kGpaStatusOk;
        }
        break;

        case GDT_HW_GENERATION_GFX10:
        {
            AutoDefinePublicDerivedCountersDx12Gfx10(*public_counters);

            if (generate_asic_specific_counters)
            {
                dx12_gfx10_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = kGpaStatusOk;
        }
        break;

        case GDT_HW_GENERATION_GFX103:
        {
            AutoDefinePublicDerivedCountersDx12Gfx103(*public_counters);

            if (generate_asic_specific_counters)
            {
                dx12_gfx103_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = kGpaStatusOk;
        }
        break;

        case GDT_HW_GENERATION_GFX11:
        {
            AutoDefinePublicDerivedCountersDx12Gfx11(*public_counters);

            if (generate_asic_specific_counters)
            {
                dx12_gfx11_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = kGpaStatusOk;
        }
        break;

        default:
            GPA_LOG_ERROR("Unrecognized or unhandled hardware generation.");
            break;
        }
    }

    if (kGpaStatusOk == status)
    {
        public_counters->SetCountersGenerated(true);
    }

    return status;
}

bool GpaCounterGeneratorDx12::GenerateInternalCounters(GpaHardwareCounters* hardware_counters, GDT_HW_GENERATION generation)
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
        std::vector<GpaHardwareCounterDesc>* group_counters = hardware_counters->counter_groups_array_.at(g);
        GpaCounterGroupDesc                  group          = hardware_counters->internal_counter_groups_.at(g + offset);

        const unsigned int num_exposed_counters_in_group = static_cast<unsigned int>(group_counters->size());
        const unsigned int total_counters_in_group       = static_cast<unsigned int>(group.num_counters);

        if (strcmp(group_counters->at(0).group, group.name) != 0)
        {
            global_counter_group_base += total_counters_in_group;
            offset++;
            g--;
            continue;
        }

        // Calculate per-block values outside the for loop.
        GpaUInt32 block_id = CalculateBlockIdDx12(generation, &group);

        for (unsigned int c = 0; c < num_exposed_counters_in_group; c++)
        {
            counter.group_index       = g + offset;
            counter.hardware_counters = &(group_counters->at(c));
            counter.group_id_driver   = block_id;

            global_counter_index = static_cast<GpaUInt32>(global_counter_group_base + group_counters->at(c).counter_index_in_group);
            hardware_counters->hardware_counters_.insert(std::pair<GpaUInt32, GpaHardwareCounterDescExt>(global_counter_index, counter));
        }
        // Adding total number of counters in group to "skip" past counters just added above.
        global_counter_group_base += total_counters_in_group;
    }

    return true;
}

GpaStatus GpaCounterGeneratorDx12::GenerateHardwareCounters(GDT_HW_GENERATION    desired_generation,
                                                            GDT_HW_ASIC_TYPE     asic_type,
                                                            GpaUInt8             generate_asic_specific_counters,
                                                            GpaHardwareCounters* hardware_counters)
{
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);

    GpaStatus status = kGpaStatusOk;

    if (nullptr == hardware_counters)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (hardware_counters->counters_generated_)
    {
        return kGpaStatusOk;
    }

    hardware_counters->Clear();

    if (desired_generation == GDT_HW_GENERATION_VOLCANICISLAND)
    {
        hardware_counters->counter_groups_array_                             = counter_dx12_gfx8::kDx12CounterGroupArrayGfx8;
        hardware_counters->internal_counter_groups_                          = counter_dx12_gfx8::kHwDx12GroupsGfx8;
        hardware_counters->sq_counter_groups_                                = counter_dx12_gfx8::kHwDx12SqGroupsGfx8;
        hardware_counters->sq_group_count_                                   = counter_dx12_gfx8::kHwDx12SqGroupCountGfx8;
        hardware_counters->timestamp_block_ids_                              = counter_dx12_gfx8::kHwDx12TimestampBlockIdsGfx8;
        hardware_counters->time_counter_indices_                             = counter_dx12_gfx8::kHwDx12TimeCounterIndicesGfx8;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_dx12_gfx8::kHwDx12GpuTimeBottomToBottomDurationIndexGfx8;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_dx12_gfx8::kHwDx12GpuTimeBottomToBottomStartIndexGfx8;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_dx12_gfx8::kHwDx12GpuTimeBottomToBottomEndIndexGfx8;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_dx12_gfx8::kHwDx12GpuTimeTopToBottomDurationIndexGfx8;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_dx12_gfx8::kHwDx12GpuTimeTopToBottomStartIndexGfx8;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_dx12_gfx8::kHwDx12GpuTimeTopToBottomEndIndexGfx8;
        hardware_counters->isolated_groups_                                  = counter_dx12_gfx8::kHwDx12SqIsolatedGroupsGfx8;
        hardware_counters->isolated_group_count_                             = counter_dx12_gfx8::kHwDx12SqIsolatedGroupCountGfx8;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX9)
    {
        hardware_counters->counter_groups_array_                             = counter_dx12_gfx9::kDx12CounterGroupArrayGfx9;
        hardware_counters->internal_counter_groups_                          = counter_dx12_gfx9::kHwDx12GroupsGfx9;
        hardware_counters->sq_counter_groups_                                = counter_dx12_gfx9::kHwDx12SqGroupsGfx9;
        hardware_counters->sq_group_count_                                   = counter_dx12_gfx9::kHwDx12SqGroupCountGfx9;
        hardware_counters->timestamp_block_ids_                              = counter_dx12_gfx9::kHwDx12TimestampBlockIdsGfx9;
        hardware_counters->time_counter_indices_                             = counter_dx12_gfx9::kHwDx12TimeCounterIndicesGfx9;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_dx12_gfx9::kHwDx12GpuTimeBottomToBottomDurationIndexGfx9;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_dx12_gfx9::kHwDx12GpuTimeBottomToBottomStartIndexGfx9;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_dx12_gfx9::kHwDx12GpuTimeBottomToBottomEndIndexGfx9;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_dx12_gfx9::kHwDx12GpuTimeTopToBottomDurationIndexGfx9;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_dx12_gfx9::kHwDx12GpuTimeTopToBottomStartIndexGfx9;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_dx12_gfx9::kHwDx12GpuTimeTopToBottomEndIndexGfx9;
        hardware_counters->isolated_groups_                                  = counter_dx12_gfx9::kHwDx12SqIsolatedGroupsGfx9;
        hardware_counters->isolated_group_count_                             = counter_dx12_gfx9::kHwDx12SqIsolatedGroupCountGfx9;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX10)
    {
        hardware_counters->counter_groups_array_                             = counter_dx12_gfx10::kDx12CounterGroupArrayGfx10;
        hardware_counters->internal_counter_groups_                          = counter_dx12_gfx10::kHwDx12GroupsGfx10;
        hardware_counters->sq_counter_groups_                                = counter_dx12_gfx10::kHwDx12SqGroupsGfx10;
        hardware_counters->sq_group_count_                                   = counter_dx12_gfx10::kHwDx12SqGroupCountGfx10;
        hardware_counters->timestamp_block_ids_                              = counter_dx12_gfx10::kHwDx12TimestampBlockIdsGfx10;
        hardware_counters->time_counter_indices_                             = counter_dx12_gfx10::kHwDx12TimeCounterIndicesGfx10;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_dx12_gfx10::kHwDx12GpuTimeBottomToBottomDurationIndexGfx10;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_dx12_gfx10::kHwDx12GpuTimeBottomToBottomStartIndexGfx10;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_dx12_gfx10::kHwDx12GpuTimeBottomToBottomEndIndexGfx10;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_dx12_gfx10::kHwDx12GpuTimeTopToBottomDurationIndexGfx10;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_dx12_gfx10::kHwDx12GpuTimeTopToBottomStartIndexGfx10;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_dx12_gfx10::kHwDx12GpuTimeTopToBottomEndIndexGfx10;
        hardware_counters->isolated_groups_                                  = counter_dx12_gfx10::kHwDx12SqIsolatedGroupsGfx10;
        hardware_counters->isolated_group_count_                             = counter_dx12_gfx10::kHwDx12SqIsolatedGroupCountGfx10;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX103)
    {
        hardware_counters->counter_groups_array_                             = counter_dx12_gfx103::kDx12CounterGroupArrayGfx103;
        hardware_counters->internal_counter_groups_                          = counter_dx12_gfx103::kHwDx12GroupsGfx103;
        hardware_counters->sq_counter_groups_                                = counter_dx12_gfx103::kHwDx12SqGroupsGfx103;
        hardware_counters->sq_group_count_                                   = counter_dx12_gfx103::kHwDx12SqGroupCountGfx103;
        hardware_counters->timestamp_block_ids_                              = counter_dx12_gfx103::kHwDx12TimestampBlockIdsGfx103;
        hardware_counters->time_counter_indices_                             = counter_dx12_gfx103::kHwDx12TimeCounterIndicesGfx103;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_dx12_gfx103::kHwDx12GpuTimeBottomToBottomDurationIndexGfx103;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_dx12_gfx103::kHwDx12GpuTimeBottomToBottomStartIndexGfx103;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_dx12_gfx103::kHwDx12GpuTimeBottomToBottomEndIndexGfx103;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_dx12_gfx103::kHwDx12GpuTimeTopToBottomDurationIndexGfx103;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_dx12_gfx103::kHwDx12GpuTimeTopToBottomStartIndexGfx103;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_dx12_gfx103::kHwDx12GpuTimeTopToBottomEndIndexGfx103;
        hardware_counters->isolated_groups_                                  = counter_dx12_gfx103::kHwDx12SqIsolatedGroupsGfx103;
        hardware_counters->isolated_group_count_                             = counter_dx12_gfx103::kHwDx12SqIsolatedGroupCountGfx103;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX11)
    {
        hardware_counters->counter_groups_array_                             = counter_dx12_gfx11::kDx12CounterGroupArrayGfx11;
        hardware_counters->internal_counter_groups_                          = counter_dx12_gfx11::kHwDx12GroupsGfx11;
        hardware_counters->sq_counter_groups_                                = counter_dx12_gfx11::kHwDx12SqGroupsGfx11;
        hardware_counters->sq_group_count_                                   = counter_dx12_gfx11::kHwDx12SqGroupCountGfx11;
        hardware_counters->timestamp_block_ids_                              = counter_dx12_gfx11::kHwDx12TimestampBlockIdsGfx11;
        hardware_counters->time_counter_indices_                             = counter_dx12_gfx11::kHwDx12TimeCounterIndicesGfx11;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_dx12_gfx11::kHwDx12GpuTimeBottomToBottomDurationIndexGfx11;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_dx12_gfx11::kHwDx12GpuTimeBottomToBottomStartIndexGfx11;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_dx12_gfx11::kHwDx12GpuTimeBottomToBottomEndIndexGfx11;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_dx12_gfx11::kHwDx12GpuTimeTopToBottomDurationIndexGfx11;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_dx12_gfx11::kHwDx12GpuTimeTopToBottomStartIndexGfx11;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_dx12_gfx11::kHwDx12GpuTimeTopToBottomEndIndexGfx11;
        hardware_counters->isolated_groups_                                  = counter_dx12_gfx11::kHwDx12SqIsolatedGroupsGfx11;
        hardware_counters->isolated_group_count_                             = counter_dx12_gfx11::kHwDx12SqIsolatedGroupCountGfx11;
    }
    else
    {
        GPA_LOG_ERROR("Unrecognized or unhandled hardware generation.");
        return kGpaStatusErrorHardwareNotSupported;
    }

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

    return status;
}

GpaStatus GpaCounterGeneratorDx12::GenerateHardwareExposedCounters(GDT_HW_GENERATION    desired_generation,
                                                                   GDT_HW_ASIC_TYPE     asic_type,
                                                                   GpaUInt8             generate_asic_specific_counters,
                                                                   GpaHardwareCounters* hardware_counters)
{
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);

    if (nullptr == hardware_counters)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (hardware_counters->hardware_exposed_counters_generated_)
    {
        return kGpaStatusOk;
    }

    if (desired_generation == GDT_HW_GENERATION_VOLCANICISLAND)
    {
        hardware_counters->hardware_exposed_counters_            = counter_dx12_gfx8::kDx12CounterGroupArrayGfx8;
        hardware_counters->hardware_exposed_counter_groups_      = counter_dx12_gfx8::kHwDx12ExposedCountersByGroupGfx8;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_dx12_gfx8::kHwDx12ExposedCountersGroupCountGfx8;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX9)
    {
        hardware_counters->hardware_exposed_counters_            = counter_dx12_gfx9::kDx12CounterGroupArrayGfx9;
        hardware_counters->hardware_exposed_counter_groups_      = counter_dx12_gfx9::kHwDx12ExposedCountersByGroupGfx9;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_dx12_gfx9::kHwDx12ExposedCountersGroupCountGfx9;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX10)
    {
        hardware_counters->hardware_exposed_counters_            = counter_dx12_gfx10::kDx12CounterGroupArrayGfx10;
        hardware_counters->hardware_exposed_counter_groups_      = counter_dx12_gfx10::kHwDx12ExposedCountersByGroupGfx10;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_dx12_gfx10::kHwDx12ExposedCountersGroupCountGfx10;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX103)
    {
        hardware_counters->hardware_exposed_counters_            = counter_dx12_gfx103::kDx12CounterGroupArrayGfx103;
        hardware_counters->hardware_exposed_counter_groups_      = counter_dx12_gfx103::kHwDx12ExposedCountersByGroupGfx103;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_dx12_gfx103::kHwDx12ExposedCountersGroupCountGfx103;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX11)
    {
        hardware_counters->hardware_exposed_counters_            = counter_dx12_gfx11::kDx12CounterGroupArrayGfx11;
        hardware_counters->hardware_exposed_counter_groups_      = counter_dx12_gfx11::kHwDx12ExposedCountersByGroupGfx11;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_dx12_gfx11::kHwDx12ExposedCountersGroupCountGfx11;
    }
    else
    {
        GPA_LOG_ERROR("Unrecognized or unhandled hardware generation.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    hardware_counters->hardware_exposed_counters_generated_ = MapHardwareExposedCounter(hardware_counters);
    return hardware_counters->hardware_exposed_counters_generated_ ? kGpaStatusOk : kGpaStatusErrorFailed;
}
