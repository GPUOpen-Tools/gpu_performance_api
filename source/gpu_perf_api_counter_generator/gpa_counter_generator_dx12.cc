//==============================================================================
// Copyright (c) 2015-2021 Advanced Micro Devices, Inc. All rights reserved.
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

#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx8.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx9.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx103.h"

#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx8_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx9_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx10_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx103_asics.h"

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

        // Don't recognize the specified hardware generation.
        // Need to add support or fix a bug.
        assert(generation == GDT_HW_GENERATION_SOUTHERNISLAND);
    }

    return group_index;
}

GpaCounterGeneratorDx12::GpaCounterGeneratorDx12()
{
    // Enable public, hw, and sw counters.
    GpaCounterGeneratorBase::SetAllowedCounters(true, true, true);

    for (int gen = GDT_HW_GENERATION_SOUTHERNISLAND; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(kGpaApiDirectx12, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GpaStatus GpaCounterGeneratorDx12::GeneratePublicCounters(GDT_HW_GENERATION   desired_generation,
                                                          GDT_HW_ASIC_TYPE    asic_type,
                                                          GpaUInt8            generate_asic_specific_counters,
                                                          GpaDerivedCounters* public_counters)
{
    auto status = kGpaStatusErrorHardwareNotSupported;

    if (nullptr == public_counters)
    {
        status = kGpaStatusErrorNullPointer;
    }
    else if (public_counters->counters_generated_)
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

        default:
            break;
        }
    }

    auto internal_status = kGpaStatusErrorHardwareNotSupported;

#ifdef AMDT_INTERNAL
    internal_status = GenerateInternalDerivedCounters(desired_generation, asic_type, generate_asic_specific_counters, public_counters);
#endif

    if (kGpaStatusOk == status)
    {
        public_counters->counters_generated_ = true;
    }
    else
    {
        status = internal_status;
    }

    return status;
}

bool GpaCounterGeneratorDx12::GenerateInternalCounters(GpaHardwareCounters* hardware_counters, GDT_HW_GENERATION generation)
{
    hardware_counters->hardware_counters_.clear();
    GpaHardwareCounterDescExt counter = {};

#if defined(_DEBUG) && defined(AMDT_INTERNAL)
    // Debug builds will generate a file that lists the counter names in a format that can be
    // easily copy/pasted into the GPUPerfAPIUnitTests project.
    FILE* counter_names_file = nullptr;
    fopen_s(&counter_names_file, "HardwareCounterNamesDX12.txt", "w");
#endif

    unsigned int global_counter_index = 0;

    // For each group, get the group name, number of counters, and max counters (and maybe validate them).
    for (unsigned int g = 0; g < hardware_counters->group_count_; g++)
    {
        GpaHardwareCounterDesc* group_counters = hardware_counters->counter_groups_array_[g];
        GpaCounterGroupDesc     group          = hardware_counters->internal_counter_groups_[g];

        // Calculate per-block values outside the for loop.
        GpaUInt32 block_id = CalculateBlockIdDx12(generation, &group);

        // Only add the number of counters that are supported; but no more than the number that we expect.
        const GpaUInt64 num_counters_in_group = hardware_counters->internal_counter_groups_[g].num_counters;

        for (GpaUInt64 c = 0; c < num_counters_in_group; c++)
        {
            counter.group_index       = g;
            counter.hardware_counters = &(group_counters[c]);
            counter.group_id_driver   = block_id;

#if defined(_DEBUG) && defined(AMDT_INTERNAL)

            if (nullptr != counter_names_file)
            {
                fwrite("    \"", 1, 5, counter_names_file);
                std::string tmp_name(counter.hardware_counters->name);
                size_t      size = tmp_name.size();
                fwrite(counter.hardware_counters->name, 1, size, counter_names_file);
                fwrite("\",", 1, 2, counter_names_file);
#ifdef EXTRA_COUNTER_INFO
                // This can be useful for debugging counter definitions.
                std::stringstream ss;
                ss << " " << counter.group_index << ", " << counter.group_id_driver << ", " << counter.hardware_counters->counter_index_in_group << ", "
                   << counter.counter_id_driver;
                std::string tmp_counter_info(ss.str());
                size = tmp_counter_info.size();
                fwrite(tmp_counter_info.c_str(), 1, size, counter_names_file);
#endif
                fwrite("\n", 1, 1, counter_names_file);
            }

#endif
            hardware_counters->hardware_counters_.push_back(counter);
            ++global_counter_index;
        }
    }

#if defined(_DEBUG) && defined(AMDT_INTERNAL)
    if (nullptr != counter_names_file)
    {
        fclose(counter_names_file);
    }
#endif

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
        hardware_counters->group_count_                                      = counter_dx12_gfx8::kHwDx12GroupCountGfx8;
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
        hardware_counters->group_count_                                      = counter_dx12_gfx9::kHwDx12GroupCountGfx9;
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
        hardware_counters->group_count_                                      = counter_dx12_gfx10::kHwDx12GroupCountGfx10;
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
        hardware_counters->group_count_                                      = counter_dx12_gfx103::kHwDx12GroupCountGfx103;
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

    unsigned int group_count = hardware_counters->group_count_;
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
        hardware_counters->hardware_exposed_counters_            = counter_dx12_gfx8::kDx12ExposedCountersGroupArrayGfx8;
        hardware_counters->hardware_exposed_counter_groups_      = counter_dx12_gfx8::kHwDx12ExposedCountersByGroupGfx8;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_dx12_gfx8::kHwDx12ExposedCountersGroupCountGfx8;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX9)
    {
        hardware_counters->hardware_exposed_counters_            = counter_dx12_gfx9::kDx12ExposedCountersGroupArrayGfx9;
        hardware_counters->hardware_exposed_counter_groups_      = counter_dx12_gfx9::kHwDx12ExposedCountersByGroupGfx9;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_dx12_gfx9::kHwDx12ExposedCountersGroupCountGfx9;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX10)
    {
        hardware_counters->hardware_exposed_counters_            = counter_dx12_gfx10::kDx12ExposedCountersGroupArrayGfx10;
        hardware_counters->hardware_exposed_counter_groups_      = counter_dx12_gfx10::kHwDx12ExposedCountersByGroupGfx10;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_dx12_gfx10::kHwDx12ExposedCountersGroupCountGfx10;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX103)
    {
        hardware_counters->hardware_exposed_counters_            = counter_dx12_gfx103::kDx12ExposedCountersGroupArrayGfx103;
        hardware_counters->hardware_exposed_counter_groups_      = counter_dx12_gfx103::kHwDx12ExposedCountersByGroupGfx103;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_dx12_gfx103::kHwDx12ExposedCountersGroupCountGfx103;
    }
    else
    {
        GPA_LOG_ERROR("Unrecognized or unhandled hardware generation.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    hardware_counters->hardware_exposed_counters_generated_ = MapHardwareExposedCounter(hardware_counters);
    return hardware_counters->hardware_exposed_counters_generated_ ? kGpaStatusOk : kGpaStatusErrorFailed;
}
