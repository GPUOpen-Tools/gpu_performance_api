//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for VK counter generation.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator_vk.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_vk_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_vk_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_vk_gfx11.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_vk_gfx115.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_vk_gfx12.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_vk_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_vk_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_vk_gfx11.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_vk_gfx115.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_vk_gfx12.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_vk_gfx10_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_vk_gfx103_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_vk_gfx11_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_vk_gfx115_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_vk_gfx12_asics.h"

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
static std::optional<GpaUInt32> CalculateBlockIdVk(device_info::HwGeneration generation, const GpaCounterGroupDesc& group)
{
    GpaUInt32 group_index = static_cast<GpaUInt32>(group.group_index);

    switch (generation)
    {
    case device_info::HwGeneration::kGfx10:
        return static_cast<GpaUInt32>(counter_vk_gfx10::kHwVkDriverBlockIdGfx10[group_index]);
    case device_info::HwGeneration::kGfx10_3:
        return static_cast<GpaUInt32>(counter_vk_gfx103::kHwVkDriverBlockIdGfx103[group_index]);
    case device_info::HwGeneration::kGfx11:
        return static_cast<GpaUInt32>(counter_vk_gfx11::kHwVkDriverBlockIdGfx11[group_index]);
    case device_info::HwGeneration::kGfx11_5:
        return static_cast<GpaUInt32>(counter_vk_gfx115::kHwVkDriverBlockIdGfx115[group_index]);
    case device_info::HwGeneration::kGfx12:
        return static_cast<GpaUInt32>(counter_vk_gfx12::kHwVkDriverBlockIdGfx12[group_index]);
    default:
        static_assert(static_cast<uint32_t>(device_info::HwGeneration::kTotalHwGenerations) == 16);
        GpaLogger::Instance().LogError("Unrecognized or unhandled hardware generation.");
    }
    return std::nullopt;
}

GpaCounterGeneratorVk::GpaCounterGeneratorVk(GpaSessionSampleType sample_type)
    : GpaCounterGeneratorVkBase(sample_type)
{
    // Enable public and hw counters.
    GpaCounterGeneratorBase::SetAllowedCounters(true, true);

    for (const device_info::HwGeneration gen : kSupportedGenerations)
    {
        CounterGeneratorSchedulerManager::Instance().RegisterCounterGenerator(kGpaApiVulkan, gen, this);
    }
}

GpaStatus GpaCounterGeneratorVk::GeneratePublicCounters(device_info::HwGeneration desired_generation,
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
            AutoDefinePublicDerivedCountersVkGfx10(*public_counters);
            vk_gfx10_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            status = kGpaStatusOk;
            break;
        }
        case device_info::HwGeneration::kGfx10_3:
        {
            AutoDefinePublicDerivedCountersVkGfx103(*public_counters);
            vk_gfx103_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            status = kGpaStatusOk;
            break;
        }
        case device_info::HwGeneration::kGfx11:
        {
            AutoDefinePublicDerivedCountersVkGfx11(*public_counters);
            vk_gfx11_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            status = kGpaStatusOk;
            break;
        }
        case device_info::HwGeneration::kGfx11_5:
        {
            AutoDefinePublicDerivedCountersVkGfx115(*public_counters);
            vk_gfx115_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            status = kGpaStatusOk;
            break;
        }
        case device_info::HwGeneration::kGfx12:
        {
            AutoDefinePublicDerivedCountersVkGfx12(*public_counters);
            vk_gfx12_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            status = kGpaStatusOk;
            break;
        }
        default:
        {
            static_assert(static_cast<uint32_t>(device_info::HwGeneration::kTotalHwGenerations) == 16);
            GpaLogger::Instance().LogError("Unsupported or unrecognized hardware generation. Cannot generate public counters.");
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

bool GpaCounterGeneratorVk::GenerateInternalCounters(GpaHardwareCounters* hardware_counters, device_info::HwGeneration generation)
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
        const std::optional<GpaUInt32> block_id = CalculateBlockIdVk(generation, group);
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

GpaStatus GpaCounterGeneratorVk::GenerateHardwareCounters(device_info::HwGeneration desired_generation,
                                                          device_info::AsicType     asic_type,
                                                          GpaHardwareCounters*      hardware_counters)
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

    switch (desired_generation)
    {
    case device_info::HwGeneration::kGfx10:
    {
        hardware_counters->counter_groups_array_                             = counter_vk_gfx10::kVkCounterGroupArrayGfx10;
        hardware_counters->internal_counter_groups_                          = counter_vk_gfx10::kHwVkGroupsGfx10;
        hardware_counters->sq_counter_groups_                                = counter_vk_gfx10::kHwVkSqGroupsGfx10;
        hardware_counters->sq_group_count_                                   = counter_vk_gfx10::kHwVkSqGroupCountGfx10;
        hardware_counters->timestamp_block_ids_                              = counter_vk_gfx10::kHwVkTimestampBlockIdsGfx10;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_vk_gfx10::kHwVkGpuTimeBottomToBottomDurationIndexGfx10;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_vk_gfx10::kHwVkGpuTimeBottomToBottomStartIndexGfx10;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_vk_gfx10::kHwVkGpuTimeBottomToBottomEndIndexGfx10;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_vk_gfx10::kHwVkGpuTimeTopToBottomDurationIndexGfx10;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_vk_gfx10::kHwVkGpuTimeTopToBottomStartIndexGfx10;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_vk_gfx10::kHwVkGpuTimeTopToBottomEndIndexGfx10;
        hardware_counters->isolated_groups_                                  = counter_vk_gfx10::kHwVkSqIsolatedGroupsGfx10;
        hardware_counters->isolated_group_count_                             = counter_vk_gfx10::kHwVkSqIsolatedGroupCountGfx10;
        break;
    }
    case device_info::HwGeneration::kGfx10_3:
    {
        hardware_counters->counter_groups_array_                             = counter_vk_gfx103::kVkCounterGroupArrayGfx103;
        hardware_counters->internal_counter_groups_                          = counter_vk_gfx103::kHwVkGroupsGfx103;
        hardware_counters->sq_counter_groups_                                = counter_vk_gfx103::kHwVkSqGroupsGfx103;
        hardware_counters->sq_group_count_                                   = counter_vk_gfx103::kHwVkSqGroupCountGfx103;
        hardware_counters->timestamp_block_ids_                              = counter_vk_gfx103::kHwVkTimestampBlockIdsGfx103;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_vk_gfx103::kHwVkGpuTimeBottomToBottomDurationIndexGfx103;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_vk_gfx103::kHwVkGpuTimeBottomToBottomStartIndexGfx103;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_vk_gfx103::kHwVkGpuTimeBottomToBottomEndIndexGfx103;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_vk_gfx103::kHwVkGpuTimeTopToBottomDurationIndexGfx103;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_vk_gfx103::kHwVkGpuTimeTopToBottomStartIndexGfx103;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_vk_gfx103::kHwVkGpuTimeTopToBottomEndIndexGfx103;
        hardware_counters->isolated_groups_                                  = counter_vk_gfx103::kHwVkSqIsolatedGroupsGfx103;
        hardware_counters->isolated_group_count_                             = counter_vk_gfx103::kHwVkSqIsolatedGroupCountGfx103;
        break;
    }
    case device_info::HwGeneration::kGfx11:
    {
        hardware_counters->counter_groups_array_                             = counter_vk_gfx11::kVkCounterGroupArrayGfx11;
        hardware_counters->internal_counter_groups_                          = counter_vk_gfx11::kHwVkGroupsGfx11;
        hardware_counters->sq_counter_groups_                                = counter_vk_gfx11::kHwVkSqGroupsGfx11;
        hardware_counters->sq_group_count_                                   = counter_vk_gfx11::kHwVkSqGroupCountGfx11;
        hardware_counters->timestamp_block_ids_                              = counter_vk_gfx11::kHwVkTimestampBlockIdsGfx11;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_vk_gfx11::kHwVkGpuTimeBottomToBottomDurationIndexGfx11;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_vk_gfx11::kHwVkGpuTimeBottomToBottomStartIndexGfx11;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_vk_gfx11::kHwVkGpuTimeBottomToBottomEndIndexGfx11;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_vk_gfx11::kHwVkGpuTimeTopToBottomDurationIndexGfx11;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_vk_gfx11::kHwVkGpuTimeTopToBottomStartIndexGfx11;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_vk_gfx11::kHwVkGpuTimeTopToBottomEndIndexGfx11;
        hardware_counters->isolated_groups_                                  = counter_vk_gfx11::kHwVkSqIsolatedGroupsGfx11;
        hardware_counters->isolated_group_count_                             = counter_vk_gfx11::kHwVkSqIsolatedGroupCountGfx11;
        break;
    }
    case device_info::HwGeneration::kGfx11_5:
    {
        hardware_counters->counter_groups_array_                             = counter_vk_gfx115::kVkCounterGroupArrayGfx115;
        hardware_counters->internal_counter_groups_                          = counter_vk_gfx115::kHwVkGroupsGfx115;
        hardware_counters->sq_counter_groups_                                = counter_vk_gfx115::kHwVkSqGroupsGfx115;
        hardware_counters->sq_group_count_                                   = counter_vk_gfx115::kHwVkSqGroupCountGfx115;
        hardware_counters->timestamp_block_ids_                              = counter_vk_gfx115::kHwVkTimestampBlockIdsGfx115;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_vk_gfx115::kHwVkGpuTimeBottomToBottomDurationIndexGfx115;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_vk_gfx115::kHwVkGpuTimeBottomToBottomStartIndexGfx115;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_vk_gfx115::kHwVkGpuTimeBottomToBottomEndIndexGfx115;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_vk_gfx115::kHwVkGpuTimeTopToBottomDurationIndexGfx115;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_vk_gfx115::kHwVkGpuTimeTopToBottomStartIndexGfx115;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_vk_gfx115::kHwVkGpuTimeTopToBottomEndIndexGfx115;
        hardware_counters->isolated_groups_                                  = counter_vk_gfx115::kHwVkSqIsolatedGroupsGfx115;
        hardware_counters->isolated_group_count_                             = counter_vk_gfx115::kHwVkSqIsolatedGroupCountGfx115;
        break;
    }
    case device_info::HwGeneration::kGfx12:
    {
        hardware_counters->counter_groups_array_                             = counter_vk_gfx12::kVkCounterGroupArrayGfx12;
        hardware_counters->internal_counter_groups_                          = counter_vk_gfx12::kHwVkGroupsGfx12;
        hardware_counters->sq_counter_groups_                                = counter_vk_gfx12::kHwVkSqGroupsGfx12;
        hardware_counters->sq_group_count_                                   = counter_vk_gfx12::kHwVkSqGroupCountGfx12;
        hardware_counters->timestamp_block_ids_                              = counter_vk_gfx12::kHwVkTimestampBlockIdsGfx12;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_vk_gfx12::kHwVkGpuTimeBottomToBottomDurationIndexGfx12;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_vk_gfx12::kHwVkGpuTimeBottomToBottomStartIndexGfx12;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_vk_gfx12::kHwVkGpuTimeBottomToBottomEndIndexGfx12;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_vk_gfx12::kHwVkGpuTimeTopToBottomDurationIndexGfx12;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_vk_gfx12::kHwVkGpuTimeTopToBottomStartIndexGfx12;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_vk_gfx12::kHwVkGpuTimeTopToBottomEndIndexGfx12;
        hardware_counters->isolated_groups_                                  = counter_vk_gfx12::kHwVkSqIsolatedGroupsGfx12;
        hardware_counters->isolated_group_count_                             = counter_vk_gfx12::kHwVkSqIsolatedGroupCountGfx12;
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
        GpaLogger::Instance().LogError("Unable to generate internal counters.");
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

GpaStatus GpaCounterGeneratorVk::GenerateHardwareExposedCounters(device_info::HwGeneration desired_generation,
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
        hardware_counters->hardware_exposed_counters_       = counter_vk_gfx10::kVkCounterGroupArrayGfx10;
        hardware_counters->hardware_exposed_counter_groups_ = counter_vk_gfx10::kHwVkExposedCountersByGroupGfx10;
        break;
    }
    case device_info::HwGeneration::kGfx10_3:
    {
        hardware_counters->hardware_exposed_counters_       = counter_vk_gfx103::kVkCounterGroupArrayGfx103;
        hardware_counters->hardware_exposed_counter_groups_ = counter_vk_gfx103::kHwVkExposedCountersByGroupGfx103;
        break;
    }
    case device_info::HwGeneration::kGfx11:
    {
        hardware_counters->hardware_exposed_counters_       = counter_vk_gfx11::kVkCounterGroupArrayGfx11;
        hardware_counters->hardware_exposed_counter_groups_ = counter_vk_gfx11::kHwVkExposedCountersByGroupGfx11;
        break;
    }
    case device_info::HwGeneration::kGfx11_5:
    {
        hardware_counters->hardware_exposed_counters_       = counter_vk_gfx115::kVkCounterGroupArrayGfx115;
        hardware_counters->hardware_exposed_counter_groups_ = counter_vk_gfx115::kHwVkExposedCountersByGroupGfx115;
        break;
    }
    case device_info::HwGeneration::kGfx12:
    {
        hardware_counters->hardware_exposed_counters_       = counter_vk_gfx12::kVkCounterGroupArrayGfx12;
        hardware_counters->hardware_exposed_counter_groups_ = counter_vk_gfx12::kHwVkExposedCountersByGroupGfx12;
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
