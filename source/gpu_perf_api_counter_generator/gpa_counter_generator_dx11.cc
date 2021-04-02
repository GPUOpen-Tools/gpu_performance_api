//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
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

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx8.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx9.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx8.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx9.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx8_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx9_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx10_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx103_asics.h"

#include "gpu_perf_api_counter_generator/gpa_software_counters.h"
#include "gpu_perf_api_counter_generator/gpa_sw_counter_manager.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

GpaCounterGeneratorDx11::GpaCounterGeneratorDx11()
{
    // Enable all counters.
    GpaCounterGeneratorBase::SetAllowedCounters(true, true, true);

    for (int gen = GDT_HW_GENERATION_FIRST_AMD; gen < GDT_HW_GENERATION_LAST; gen++)
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
/// \return The block id according to the driver.
static GpaUInt32 CalculateBlockIdDx11(GDT_HW_GENERATION generation, GpaCounterGroupDesc* group)
{
    GpaUInt32 group_index = group->group_index;

    if (GpaCounterGeneratorDx11Base::IsAmdGpu(generation))
    {
        if (generation == GDT_HW_GENERATION_VOLCANICISLAND)
        {
            return counter_dx11_gfx8::kHwDx11DriverEnumGfx8[group_index];
        }

        if (generation == GDT_HW_GENERATION_GFX9)
        {
            return counter_dx11_gfx9::kHwDx11DriverEnumGfx9[group_index];
        }

        if (generation == GDT_HW_GENERATION_GFX10)
        {
            return counter_dx11_gfx10::kHwDx11DriverEnumGfx10[group_index];
        }

        if (generation == GDT_HW_GENERATION_GFX103)
        {
            return counter_dx11_gfx103::kHwDx11DriverEnumGfx103[group_index];
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
#if defined(_DEBUG) && defined(AMDT_INTERNAL)
    // Debug builds will generate a file that lists the counter names in a format that can be
    // easily copy/pasted into the GPUPerfAPIUnitTests project.
    FILE* counter_names_file = nullptr;
    fopen_s(&counter_names_file, "HardwareCounterNamesDX11.txt", "w");
#endif

    unsigned int global_counter_index = 0;

    // For each group, get the group name, number of counters, and max counters (and maybe validate them).
    for (unsigned int g = 0; g < hardware_counters->group_count_; g++)
    {
        GpaHardwareCounterDesc* group_counters = hardware_counters->counter_groups_array_[g];
        GpaCounterGroupDesc     group          = hardware_counters->internal_counter_groups_[g];

        // Calculate per-block values outside the for loop.
        GpaUInt32 block_id = CalculateBlockIdDx11(generation, &group);

        // Only add the number of counters that are supported; but no more than the number that we expect.
        const GpaUInt64 num_counters_in_group = hardware_counters->internal_counter_groups_[g].num_counters;

        for (GpaUInt64 c = 0; c < num_counters_in_group; c++)
        {
            counter.group_index       = g;
            counter.hardware_counters = &(group_counters[c]);
            counter.group_id_driver   = block_id;

            if (hardware_counters->IsTimestampBlockId(counter.group_index))
            {
                counter.counter_id_driver =
                    AmdCtrEncodeApiCounter((AmdApiCounterId)(global_counter_index - hardware_counters->GetFirstHardwareTimeCounterIndex()));
            }
            else
            {
                counter.counter_id_driver = 0;
            }

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

GpaStatus GpaCounterGeneratorDx11::GeneratePublicCounters(GDT_HW_GENERATION   desired_generation,
                                                          GDT_HW_ASIC_TYPE    asic_type,
                                                          GpaUInt8            generate_asic_specific_counters,
                                                          GpaDerivedCounters* public_counters)
{
    GpaStatus status = kGpaStatusErrorHardwareNotSupported;

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

        if (desired_generation == GDT_HW_GENERATION_VOLCANICISLAND)
        {
            AutoDefinePublicDerivedCountersDx11Gfx8(*public_counters);

            if (generate_asic_specific_counters)
            {
                dx11_gfx8_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = kGpaStatusOk;
        }
        else if (desired_generation == GDT_HW_GENERATION_GFX9)
        {
            AutoDefinePublicDerivedCountersDx11Gfx9(*public_counters);

            if (generate_asic_specific_counters)
            {
                dx11_gfx9_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = kGpaStatusOk;
        }
        else if (desired_generation == GDT_HW_GENERATION_GFX10)
        {
            AutoDefinePublicDerivedCountersDx11Gfx10(*public_counters);

            if (generate_asic_specific_counters)
            {
                dx11_gfx10_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = kGpaStatusOk;
        }
        else if (desired_generation == GDT_HW_GENERATION_GFX103)
        {
            AutoDefinePublicDerivedCountersDx11Gfx103(*public_counters);

            if (generate_asic_specific_counters)
            {
                dx11_gfx103_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = kGpaStatusOk;
        }
    }

    GpaStatus internal_status = kGpaStatusErrorHardwareNotSupported;

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

GpaStatus GpaCounterGeneratorDx11::GenerateHardwareCounters(GDT_HW_GENERATION    desired_generation,
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

    if (hardware_counters->counters_generated_)  // Only generate counters once to improve performance.
    {
        return kGpaStatusOk;
    }

    hardware_counters->Clear();

    if (desired_generation == GDT_HW_GENERATION_VOLCANICISLAND)
    {
        hardware_counters->counter_groups_array_                             = counter_dx11_gfx8::kDx11CounterGroupArrayGfx8;
        hardware_counters->internal_counter_groups_                          = counter_dx11_gfx8::kHwDx11GroupsGfx8;
        hardware_counters->group_count_                                      = counter_dx11_gfx8::kHwDx11GroupCountGfx8;
        hardware_counters->sq_counter_groups_                                = counter_dx11_gfx8::kHwDx11SqGroupsGfx8;
        hardware_counters->sq_group_count_                                   = counter_dx11_gfx8::kHwDx11SqGroupCountGfx8;
        hardware_counters->timestamp_block_ids_                              = counter_dx11_gfx8::kHwDx11TimestampBlockIdsGfx8;
        hardware_counters->time_counter_indices_                             = counter_dx11_gfx8::kHwDx11TimeCounterIndicesGfx8;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_dx11_gfx8::kHwDx11GpuTimeBottomToBottomDurationIndexGfx8;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_dx11_gfx8::kHwDx11GpuTimeBottomToBottomStartIndexGfx8;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_dx11_gfx8::kHwDx11GpuTimeBottomToBottomEndIndexGfx8;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_dx11_gfx8::kHwDx11GpuTimeTopToBottomDurationIndexGfx8;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_dx11_gfx8::kHwDx11GpuTimeTopToBottomStartIndexGfx8;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_dx11_gfx8::kHwDx11GpuTimeTopToBottomEndIndexGfx8;
        hardware_counters->isolated_groups_                                  = counter_dx11_gfx8::kHwDx11SqIsolatedGroupsGfx8;
        hardware_counters->isolated_group_count_                             = counter_dx11_gfx8::kHwDx11SqIsolatedGroupCountGfx8;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX9)
    {
        hardware_counters->counter_groups_array_                             = counter_dx11_gfx9::kDx11CounterGroupArrayGfx9;
        hardware_counters->internal_counter_groups_                          = counter_dx11_gfx9::kHwDx11GroupsGfx9;
        hardware_counters->group_count_                                      = counter_dx11_gfx9::kHwDx11GroupCountGfx9;
        hardware_counters->sq_counter_groups_                                = counter_dx11_gfx9::kHwDx11SqGroupsGfx9;
        hardware_counters->sq_group_count_                                   = counter_dx11_gfx9::kHwDx11SqGroupCountGfx9;
        hardware_counters->timestamp_block_ids_                              = counter_dx11_gfx9::kHwDx11TimestampBlockIdsGfx9;
        hardware_counters->time_counter_indices_                             = counter_dx11_gfx9::kHwDx11TimeCounterIndicesGfx9;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_dx11_gfx9::kHwDx11GpuTimeBottomToBottomDurationIndexGfx9;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_dx11_gfx9::kHwDx11GpuTimeBottomToBottomStartIndexGfx9;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_dx11_gfx9::kHwDx11GpuTimeBottomToBottomEndIndexGfx9;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_dx11_gfx9::kHwDx11GpuTimeTopToBottomDurationIndexGfx9;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_dx11_gfx9::kHwDx11GpuTimeTopToBottomStartIndexGfx9;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_dx11_gfx9::kHwDx11GpuTimeTopToBottomEndIndexGfx9;
        hardware_counters->isolated_groups_                                  = counter_dx11_gfx9::kHwDx11SqIsolatedGroupsGfx9;
        hardware_counters->isolated_group_count_                             = counter_dx11_gfx9::kHwDx11SqIsolatedGroupCountGfx9;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX10)
    {
        hardware_counters->counter_groups_array_                             = counter_dx11_gfx10::kDx11CounterGroupArrayGfx10;
        hardware_counters->internal_counter_groups_                          = counter_dx11_gfx10::kHwDx11GroupsGfx10;
        hardware_counters->group_count_                                      = counter_dx11_gfx10::kHwDx11GroupCountGfx10;
        hardware_counters->sq_counter_groups_                                = counter_dx11_gfx10::kHwDx11SqGroupsGfx10;
        hardware_counters->sq_group_count_                                   = counter_dx11_gfx10::kHwDx11SqGroupCountGfx10;
        hardware_counters->timestamp_block_ids_                              = counter_dx11_gfx10::kHwDx11TimestampBlockIdsGfx10;
        hardware_counters->time_counter_indices_                             = counter_dx11_gfx10::kHwDx11TimeCounterIndicesGfx10;
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
        hardware_counters->group_count_                                      = counter_dx11_gfx103::kHwDx11GroupCountGfx103;
        hardware_counters->sq_counter_groups_                                = counter_dx11_gfx103::kHwDx11SqGroupsGfx103;
        hardware_counters->sq_group_count_                                   = counter_dx11_gfx103::kHwDx11SqGroupCountGfx103;
        hardware_counters->timestamp_block_ids_                              = counter_dx11_gfx103::kHwDx11TimestampBlockIdsGfx103;
        hardware_counters->time_counter_indices_                             = counter_dx11_gfx103::kHwDx11TimeCounterIndicesGfx103;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_dx11_gfx103::kHwDx11GpuTimeBottomToBottomDurationIndexGfx103;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_dx11_gfx103::kHwDx11GpuTimeBottomToBottomStartIndexGfx103;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_dx11_gfx103::kHwDx11GpuTimeBottomToBottomEndIndexGfx103;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_dx11_gfx103::kHwDx11GpuTimeTopToBottomDurationIndexGfx103;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_dx11_gfx103::kHwDx11GpuTimeTopToBottomStartIndexGfx103;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_dx11_gfx103::kHwDx11GpuTimeTopToBottomEndIndexGfx103;
        hardware_counters->isolated_groups_                                  = counter_dx11_gfx103::kHwDx11SqIsolatedGroupsGfx103;
        hardware_counters->isolated_group_count_                             = counter_dx11_gfx103::kHwDx11SqIsolatedGroupCountGfx103;
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
    return kGpaStatusOk;
}

GpaStatus GpaCounterGeneratorDx11::GenerateHardwareExposedCounters(GDT_HW_GENERATION    desired_generation,
                                                                   GDT_HW_ASIC_TYPE     asic_type,
                                                                   GpaUInt8             generate_asic_specific_counters,
                                                                   GpaHardwareCounters* hardware_counters)
{
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);

    if (hardware_counters->hardware_exposed_counters_generated_)
    {
        return kGpaStatusOk;
    }

    if (desired_generation == GDT_HW_GENERATION_VOLCANICISLAND)
    {
        hardware_counters->hardware_exposed_counters_            = counter_dx11_gfx8::kDx11ExposedCountersGroupArrayGfx8;
        hardware_counters->hardware_exposed_counter_groups_      = counter_dx11_gfx8::kHwDx11ExposedCountersByGroupGfx8;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_dx11_gfx8::kHwDx11ExposedCountersGroupCountGfx8;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX9)
    {
        hardware_counters->hardware_exposed_counters_            = counter_dx11_gfx9::kDx11ExposedCountersGroupArrayGfx9;
        hardware_counters->hardware_exposed_counter_groups_      = counter_dx11_gfx9::kHwDx11ExposedCountersByGroupGfx9;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_dx11_gfx9::kHwDx11ExposedCountersGroupCountGfx9;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX10)
    {
        hardware_counters->hardware_exposed_counters_            = counter_dx11_gfx10::kDx11ExposedCountersGroupArrayGfx10;
        hardware_counters->hardware_exposed_counter_groups_      = counter_dx11_gfx10::kHwDx11ExposedCountersByGroupGfx10;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_dx11_gfx10::kHwDx11ExposedCountersGroupCountGfx10;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX103)
    {
        hardware_counters->hardware_exposed_counters_            = counter_dx11_gfx103::kDx11ExposedCountersGroupArrayGfx103;
        hardware_counters->hardware_exposed_counter_groups_      = counter_dx11_gfx103::kHwDx11ExposedCountersByGroupGfx103;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_dx11_gfx103::kHwDx11ExposedCountersGroupCountGfx103;
    }
    else
    {
        GPA_LOG_ERROR("Unrecognized or unhandled hardware generation.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    hardware_counters->hardware_exposed_counters_generated_ = MapHardwareExposedCounter(hardware_counters);
    return hardware_counters->hardware_exposed_counters_generated_ ? kGpaStatusOk : kGpaStatusErrorFailed;
}
