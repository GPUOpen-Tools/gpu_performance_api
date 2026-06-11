//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for DX12 counter generation.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx12.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx11.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx115.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx12.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx11.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx115.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx12.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx10_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx103_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx11_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx115_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx12_asics.h"

#include "gpu_perf_api_common/gpa_hw_support.h"

/// @brief Logic inside this function is based on the AmdExtGpuBlock enum in AmdExtGpaInterface in DXCP driver.
///
/// The driver gives each block an ID, but ignores the instance. GPA treats each instance as a different
/// block, so we need to translate.
///
/// @param [in] generation The generation whose block id needs to be calculated.
/// @param [in] group The group for which the block id needs to be calculated.
///
/// @return The block id according to the driver if the HW is supported, std::nullopt otherwise.
static std::optional<GpaUInt32> CalculateBlockIdDx12(device_info::HwGeneration generation, const GpaCounterGroupDesc& group)
{
    const GpaUInt32 group_index = static_cast<GpaUInt32>(group.group_index);

    switch (generation)
    {
    case device_info::HwGeneration::kGfx10:
        return static_cast<GpaUInt32>(counter_dx12_gfx10::kHwDx12DriverBlockIdGfx10[group_index]);
    case device_info::HwGeneration::kGfx10_3:
        return static_cast<GpaUInt32>(counter_dx12_gfx103::kHwDx12DriverBlockIdGfx103[group_index]);
    case device_info::HwGeneration::kGfx11:
        return static_cast<GpaUInt32>(counter_dx12_gfx11::kHwDx12DriverBlockIdGfx11[group_index]);
    case device_info::HwGeneration::kGfx11_5:
        return static_cast<GpaUInt32>(counter_dx12_gfx115::kHwDx12DriverBlockIdGfx115[group_index]);
    case device_info::HwGeneration::kGfx12:
        return static_cast<GpaUInt32>(counter_dx12_gfx12::kHwDx12DriverBlockIdGfx12[group_index]);
    }

    static_assert(static_cast<uint32_t>(device_info::HwGeneration::kTotalHwGenerations) == 16);
    GpaLogger::Instance().LogError("Unrecognized or unhandled hardware generation.");

    return std::nullopt;
}

GpaCounterGeneratorDx12::GpaCounterGeneratorDx12(GpaSessionSampleType sample_type)
    : GpaCounterGeneratorDx12Base(sample_type)
{
    // Enable public and hw counters.
    GpaCounterGeneratorBase::SetAllowedCounters(true, true);

    for (const device_info::HwGeneration gen : kSupportedGenerations)
    {
        CounterGeneratorSchedulerManager::Instance().RegisterCounterGenerator(kGpaApiDirectx12, gen, this);
    }
}

GpaStatus GpaCounterGeneratorDx12::GeneratePublicCounters(device_info::HwGeneration desired_generation,
                                                          device_info::AsicType     asic_type,
                                                          GpaDerivedCounters*       public_counters)
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
        case device_info::HwGeneration::kGfx10:
        {
            AutoDefinePublicDerivedCountersDx12Gfx10(*public_counters);
            dx12_gfx10_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            status = kGpaStatusOk;
            break;
        }
        case device_info::HwGeneration::kGfx10_3:
        {
            AutoDefinePublicDerivedCountersDx12Gfx103(*public_counters);
            dx12_gfx103_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            status = kGpaStatusOk;
            break;
        }
        case device_info::HwGeneration::kGfx11:
        {
            AutoDefinePublicDerivedCountersDx12Gfx11(*public_counters);
            dx12_gfx11_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            status = kGpaStatusOk;
            break;
        }
        case device_info::HwGeneration::kGfx11_5:
        {
            AutoDefinePublicDerivedCountersDx12Gfx115(*public_counters);
            dx12_gfx115_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            status = kGpaStatusOk;
            break;
        }
        case device_info::HwGeneration::kGfx12:
        {
            AutoDefinePublicDerivedCountersDx12Gfx12(*public_counters);
            dx12_gfx12_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            status = kGpaStatusOk;
            break;
        }
        default:
        {
            static_assert(static_cast<uint32_t>(device_info::HwGeneration::kTotalHwGenerations) == 16);
            GpaLogger::Instance().LogError("Unrecognized or unhandled hardware generation.");
            return kGpaStatusErrorHardwareNotSupported;
        }
        }
    }

    if (kGpaStatusOk == status)
    {
        public_counters->SetCountersGenerated(true);
    }

    return status;
}

bool GpaCounterGeneratorDx12::GenerateInternalCounters(GpaHardwareCounters* hardware_counters, device_info::HwGeneration generation)
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
        const gpa_array_view<GpaHardwareCounterDesc>& group_counters = *hardware_counters->counter_groups_array_[g];
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
        const std::optional<GpaUInt32> block_id = CalculateBlockIdDx12(generation, group);
        if (!block_id.has_value())
        {
            return false;
        }

        for (unsigned int c = 0; c < num_exposed_counters_in_group; c++)
        {
            counter.group_index       = g + offset;
            counter.hardware_counters = &(group_counters[c]);
            counter.group_id_driver   = *block_id;

            global_counter_index = static_cast<GpaUInt32>(global_counter_group_base + group_counters[c].counter_index_in_group);
            hardware_counters->hardware_counters_.insert(std::pair<GpaUInt32, GpaHardwareCounterDescExt>(global_counter_index, counter));
        }
        // Adding total number of counters in group to "skip" past counters just added above.
        global_counter_group_base += total_counters_in_group;
    }

    return true;
}

GpaStatus GpaCounterGeneratorDx12::GenerateHardwareCounters(device_info::HwGeneration desired_generation,
                                                            device_info::AsicType     asic_type,
                                                            GpaHardwareCounters*      hardware_counters)
{
    UNREFERENCED_PARAMETER(asic_type);

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

    switch (desired_generation)
    {
    case device_info::HwGeneration::kGfx10:
    {
        hardware_counters->counter_groups_array_                             = counter_dx12_gfx10::kDx12CounterGroupArrayGfx10;
        hardware_counters->internal_counter_groups_                          = counter_dx12_gfx10::kHwDx12GroupsGfx10;
        hardware_counters->sq_counter_groups_                                = counter_dx12_gfx10::kHwDx12SqGroupsGfx10;
        hardware_counters->sq_group_count_                                   = counter_dx12_gfx10::kHwDx12SqGroupCountGfx10;
        hardware_counters->timestamp_block_ids_                              = counter_dx12_gfx10::kHwDx12TimestampBlockIdsGfx10;
        hardware_counters->level_waves_indices_                              = counter_dx12_gfx10::kHwDx12LevelWavesCountersGfx10;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_dx12_gfx10::kHwDx12GpuTimeBottomToBottomDurationIndexGfx10;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_dx12_gfx10::kHwDx12GpuTimeBottomToBottomStartIndexGfx10;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_dx12_gfx10::kHwDx12GpuTimeBottomToBottomEndIndexGfx10;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_dx12_gfx10::kHwDx12GpuTimeTopToBottomDurationIndexGfx10;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_dx12_gfx10::kHwDx12GpuTimeTopToBottomStartIndexGfx10;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_dx12_gfx10::kHwDx12GpuTimeTopToBottomEndIndexGfx10;
        hardware_counters->isolated_groups_                                  = counter_dx12_gfx10::kHwDx12SqIsolatedGroupsGfx10;
        hardware_counters->isolated_group_count_                             = counter_dx12_gfx10::kHwDx12SqIsolatedGroupCountGfx10;
        break;
    }
    case device_info::HwGeneration::kGfx10_3:
    {
        hardware_counters->counter_groups_array_                             = counter_dx12_gfx103::kDx12CounterGroupArrayGfx103;
        hardware_counters->internal_counter_groups_                          = counter_dx12_gfx103::kHwDx12GroupsGfx103;
        hardware_counters->sq_counter_groups_                                = counter_dx12_gfx103::kHwDx12SqGroupsGfx103;
        hardware_counters->sq_group_count_                                   = counter_dx12_gfx103::kHwDx12SqGroupCountGfx103;
        hardware_counters->timestamp_block_ids_                              = counter_dx12_gfx103::kHwDx12TimestampBlockIdsGfx103;
        hardware_counters->level_waves_indices_                              = counter_dx12_gfx103::kHwDx12LevelWavesCountersGfx103;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_dx12_gfx103::kHwDx12GpuTimeBottomToBottomDurationIndexGfx103;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_dx12_gfx103::kHwDx12GpuTimeBottomToBottomStartIndexGfx103;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_dx12_gfx103::kHwDx12GpuTimeBottomToBottomEndIndexGfx103;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_dx12_gfx103::kHwDx12GpuTimeTopToBottomDurationIndexGfx103;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_dx12_gfx103::kHwDx12GpuTimeTopToBottomStartIndexGfx103;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_dx12_gfx103::kHwDx12GpuTimeTopToBottomEndIndexGfx103;
        hardware_counters->isolated_groups_                                  = counter_dx12_gfx103::kHwDx12SqIsolatedGroupsGfx103;
        hardware_counters->isolated_group_count_                             = counter_dx12_gfx103::kHwDx12SqIsolatedGroupCountGfx103;
        break;
    }
    case device_info::HwGeneration::kGfx11:
    {
        hardware_counters->counter_groups_array_                             = counter_dx12_gfx11::kDx12CounterGroupArrayGfx11;
        hardware_counters->internal_counter_groups_                          = counter_dx12_gfx11::kHwDx12GroupsGfx11;
        hardware_counters->sq_counter_groups_                                = counter_dx12_gfx11::kHwDx12SqGroupsGfx11;
        hardware_counters->sq_group_count_                                   = counter_dx12_gfx11::kHwDx12SqGroupCountGfx11;
        hardware_counters->timestamp_block_ids_                              = counter_dx12_gfx11::kHwDx12TimestampBlockIdsGfx11;
        hardware_counters->level_waves_indices_                              = counter_dx12_gfx11::kHwDx12LevelWavesCountersGfx11;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_dx12_gfx11::kHwDx12GpuTimeBottomToBottomDurationIndexGfx11;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_dx12_gfx11::kHwDx12GpuTimeBottomToBottomStartIndexGfx11;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_dx12_gfx11::kHwDx12GpuTimeBottomToBottomEndIndexGfx11;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_dx12_gfx11::kHwDx12GpuTimeTopToBottomDurationIndexGfx11;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_dx12_gfx11::kHwDx12GpuTimeTopToBottomStartIndexGfx11;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_dx12_gfx11::kHwDx12GpuTimeTopToBottomEndIndexGfx11;
        hardware_counters->isolated_groups_                                  = counter_dx12_gfx11::kHwDx12SqIsolatedGroupsGfx11;
        hardware_counters->isolated_group_count_                             = counter_dx12_gfx11::kHwDx12SqIsolatedGroupCountGfx11;
        break;
    }
    case device_info::HwGeneration::kGfx11_5:
    {
        hardware_counters->counter_groups_array_                             = counter_dx12_gfx115::kDx12CounterGroupArrayGfx115;
        hardware_counters->internal_counter_groups_                          = counter_dx12_gfx115::kHwDx12GroupsGfx115;
        hardware_counters->sq_counter_groups_                                = counter_dx12_gfx115::kHwDx12SqGroupsGfx115;
        hardware_counters->sq_group_count_                                   = counter_dx12_gfx115::kHwDx12SqGroupCountGfx115;
        hardware_counters->timestamp_block_ids_                              = counter_dx12_gfx115::kHwDx12TimestampBlockIdsGfx115;
        hardware_counters->level_waves_indices_                              = counter_dx12_gfx115::kHwDx12LevelWavesCountersGfx115;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_dx12_gfx115::kHwDx12GpuTimeBottomToBottomDurationIndexGfx115;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_dx12_gfx115::kHwDx12GpuTimeBottomToBottomStartIndexGfx115;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_dx12_gfx115::kHwDx12GpuTimeBottomToBottomEndIndexGfx115;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_dx12_gfx115::kHwDx12GpuTimeTopToBottomDurationIndexGfx115;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_dx12_gfx115::kHwDx12GpuTimeTopToBottomStartIndexGfx115;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_dx12_gfx115::kHwDx12GpuTimeTopToBottomEndIndexGfx115;
        hardware_counters->isolated_groups_                                  = counter_dx12_gfx115::kHwDx12SqIsolatedGroupsGfx115;
        hardware_counters->isolated_group_count_                             = counter_dx12_gfx115::kHwDx12SqIsolatedGroupCountGfx115;
        break;
    }
    case device_info::HwGeneration::kGfx12:
    {
        hardware_counters->counter_groups_array_                             = counter_dx12_gfx12::kDx12CounterGroupArrayGfx12;
        hardware_counters->internal_counter_groups_                          = counter_dx12_gfx12::kHwDx12GroupsGfx12;
        hardware_counters->sq_counter_groups_                                = counter_dx12_gfx12::kHwDx12SqGroupsGfx12;
        hardware_counters->sq_group_count_                                   = counter_dx12_gfx12::kHwDx12SqGroupCountGfx12;
        hardware_counters->timestamp_block_ids_                              = counter_dx12_gfx12::kHwDx12TimestampBlockIdsGfx12;
        hardware_counters->level_waves_indices_                              = counter_dx12_gfx12::kHwDx12LevelWavesCountersGfx12;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_dx12_gfx12::kHwDx12GpuTimeBottomToBottomDurationIndexGfx12;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_dx12_gfx12::kHwDx12GpuTimeBottomToBottomStartIndexGfx12;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_dx12_gfx12::kHwDx12GpuTimeBottomToBottomEndIndexGfx12;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_dx12_gfx12::kHwDx12GpuTimeTopToBottomDurationIndexGfx12;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_dx12_gfx12::kHwDx12GpuTimeTopToBottomStartIndexGfx12;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_dx12_gfx12::kHwDx12GpuTimeTopToBottomEndIndexGfx12;
        hardware_counters->isolated_groups_                                  = counter_dx12_gfx12::kHwDx12SqIsolatedGroupsGfx12;
        hardware_counters->isolated_group_count_                             = counter_dx12_gfx12::kHwDx12SqIsolatedGroupCountGfx12;
        break;
    }
    default:
    {
        static_assert(static_cast<uint32_t>(device_info::HwGeneration::kTotalHwGenerations) == 16);
        GpaLogger::Instance().LogError("Unrecognized or unhandled hardware generation.");
        return kGpaStatusErrorHardwareNotSupported;
    }
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
        GpaLogger::Instance().LogError("Unable to generate internal or whitelist counters.");
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

GpaStatus GpaCounterGeneratorDx12::GenerateHardwareExposedCounters(device_info::HwGeneration desired_generation,
                                                                   device_info::AsicType     asic_type,
                                                                   GpaHardwareCounters*      hardware_counters)
{
    UNREFERENCED_PARAMETER(asic_type);

    if (nullptr == hardware_counters)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (hardware_counters->hardware_exposed_counters_generated_)
    {
        return kGpaStatusOk;
    }

    switch (desired_generation)
    {
    case device_info::HwGeneration::kGfx10:
    {
        hardware_counters->hardware_exposed_counters_       = counter_dx12_gfx10::kDx12CounterGroupArrayGfx10;
        hardware_counters->hardware_exposed_counter_groups_ = counter_dx12_gfx10::kHwDx12ExposedCountersByGroupGfx10;
        break;
    }
    case device_info::HwGeneration::kGfx10_3:
    {
        hardware_counters->hardware_exposed_counters_       = counter_dx12_gfx103::kDx12CounterGroupArrayGfx103;
        hardware_counters->hardware_exposed_counter_groups_ = counter_dx12_gfx103::kHwDx12ExposedCountersByGroupGfx103;
        break;
    }
    case device_info::HwGeneration::kGfx11:
    {
        hardware_counters->hardware_exposed_counters_       = counter_dx12_gfx11::kDx12CounterGroupArrayGfx11;
        hardware_counters->hardware_exposed_counter_groups_ = counter_dx12_gfx11::kHwDx12ExposedCountersByGroupGfx11;
        break;
    }
    case device_info::HwGeneration::kGfx11_5:
    {
        hardware_counters->hardware_exposed_counters_       = counter_dx12_gfx115::kDx12CounterGroupArrayGfx115;
        hardware_counters->hardware_exposed_counter_groups_ = counter_dx12_gfx115::kHwDx12ExposedCountersByGroupGfx115;
        break;
    }
    case device_info::HwGeneration::kGfx12:
    {
        hardware_counters->hardware_exposed_counters_       = counter_dx12_gfx12::kDx12CounterGroupArrayGfx12;
        hardware_counters->hardware_exposed_counter_groups_ = counter_dx12_gfx12::kHwDx12ExposedCountersByGroupGfx12;
        break;
    }
    default:
    {
        static_assert(static_cast<uint32_t>(device_info::HwGeneration::kTotalHwGenerations) == 16);
        GpaLogger::Instance().LogError("Unrecognized or unhandled hardware generation.");
        return kGpaStatusErrorHardwareNotSupported;
    }
    }

    hardware_counters->hardware_exposed_counters_generated_ = MapHardwareExposedCounter(hardware_counters);
    return hardware_counters->hardware_exposed_counters_generated_ ? kGpaStatusOk : kGpaStatusErrorFailed;
}
