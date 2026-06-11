//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPUPerfAPI Counter Generator function.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator.h"

#include <cctype>

#include "gpu_perf_api_common/gpa_hw_info.h"
#include "gpu_perf_api_common/logging.h"
#include "gpu_perf_api_common/utility.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_base.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

/// @brief BlockMap for updating ASIC block data on initialization.
class BlockMap
{
public:
    /// @brief Add a block to the map.
    ///
    /// @param [in] counter_group Counter group to add to the map.
    void AddBlock(GpaCounterGroupDesc* counter_group)
    {
        std::string block(counter_group->name);

        for (char* p = (char*)block.data() + block.length() - 1; (p >= block.data()) && (std::isdigit(*p)); --p)
        {
            block.resize(block.length() - 1);
        }

        std::string index = counter_group->name + block.length();

        uint32_t block_index = std::atoi(index.c_str());

        if (0 == block_index)
        {
            blocks_[block].push_back(counter_group);
        }
        else
        {
            // Handle the case where the block ends in a number, e.g.: ATCL2.
            if (blocks_.find(block) == blocks_.end())
            {
                blocks_[counter_group->name].push_back(counter_group);
            }
            else
            {
                blocks_[block].push_back(counter_group);
            }
        }
    }

    /// @brief Get block list by name.
    ///
    /// @param [in] block Name of the block to retrieve.
    ///
    /// @return Vector of blocks.
    std::vector<GpaCounterGroupDesc*> GetBlockList(const std::string& block)
    {
        auto iter = blocks_.find(block);
        if (blocks_.end() == iter)
        {
            return std::vector<GpaCounterGroupDesc*>();
        }

        return iter->second;
    }

    std::map<std::string, std::vector<GpaCounterGroupDesc*>> blocks_;  ///< Map of ASIC blocks by name.
};

std::shared_ptr<BlockMap> BuildBlockMap(std::vector<GpaCounterGroupDesc>& counter_group_list, uint32_t max_count)
{
    std::shared_ptr<BlockMap> block_map = std::make_shared<BlockMap>();

    for (uint32_t i = 0; i < max_count; ++i)
    {
        block_map->AddBlock(&counter_group_list[i]);
    }

    return block_map;
}

void UpdateMaxDiscreteBlockEvents(BlockMap* block_map, const char* block_name, uint32_t max_discrete_events)
{
    auto block = block_map->GetBlockList(block_name);
    if (block.empty())
    {
        if (0 == max_discrete_events)
        {
            // If the block is not found, and max events are zero, it's not an error.
        }
        else
        {
            assert(0);
        }
    }
    else
    {
        for (auto entry : block)
        {
            entry->max_active_discrete_counters = max_discrete_events;
        }
    }
}

void UpdateMaxSpmBlockEvents(BlockMap* block_map, const char* block_name, uint32_t max_spm_events)
{
    auto block = block_map->GetBlockList(block_name);
    if (block.empty())
    {
        if (0 == max_spm_events)
        {
            // If the block is not found, and max events are zero, it's not an error.
        }
    }
    else
    {
        for (auto entry : block)
        {
            entry->max_active_spm_counters = max_spm_events;
        }
    }
}

GpaStatus GenerateCounters(GpaApiType             desired_api,
                           GpaSessionSampleType   sample_type,
                           const GpaHwInfo&       hw_info,
                           GpaOpenContextFlags    flags,
                           IGpaCounterAccessor**  counter_accessor_out,
                           IGpaCounterScheduler** counter_scheduler_out)
{
    GPA_CHECK_NULLPTR(counter_accessor_out);
    GPA_CHECK_NULLPTR(counter_scheduler_out);

    assert(kGpaSessionSampleTypeSqtt != sample_type);

    static_assert(kGpaSessionSampleTypeLast == 4);

    if (kGpaSessionSampleTypeStreamingCounterAndSqtt == sample_type)
    {
        // To help find the right counter generator
        sample_type = kGpaSessionSampleTypeStreamingCounter;
    }

    const device_info::HwGeneration desired_generation = hw_info.GetHwGeneration().value();
    GpaStatus                       status             = kGpaStatusOk;
    GpaCounterGeneratorBase*        tmp_accessor       = nullptr;
    IGpaCounterScheduler*           tmp_scheduler      = nullptr;

    if (!CounterGeneratorSchedulerManager::Instance().GetCounterGenerator(desired_api, sample_type, desired_generation, tmp_accessor))
    {
        GpaLogger::Instance().LogError("Requesting available counters from an unsupported API or hardware generation.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    const bool allow_public   = (flags & kGpaOpenContextHidePublicCountersBit) == 0;
    const bool allow_hardware = [&flags]() -> bool {
        const bool enable_hw_counters = (flags & kGpaOpenContextEnableHardwareCountersBit) == kGpaOpenContextEnableHardwareCountersBit;

        // See documentation/sphinx/source/gpa_env_variables.rst for details on this environment variable.
        const bool force_hw = gpa_util::IsEnvVarForceEnabled("GPA_EXPOSE_HW_COUNTERS");
        return enable_hw_counters || force_hw;
    }();

    tmp_accessor->SetAllowedCounters(allow_public, allow_hardware);
    status = tmp_accessor->GenerateCounters(desired_generation, hw_info.GetHwAsicType().value());

    if (status == kGpaStatusOk)
    {
        *counter_accessor_out = tmp_accessor;

        if (!CounterGeneratorSchedulerManager::Instance().GetCounterScheduler(desired_api, sample_type, desired_generation, tmp_scheduler))
        {
            GpaLogger::Instance().LogError("Requesting available counters from an unsupported API or hardware generation.");
            return kGpaStatusErrorHardwareNotSupported;
        }

        *counter_scheduler_out = tmp_scheduler;
        status                 = tmp_scheduler->SetCounterAccessor(tmp_accessor, hw_info);
    }

    return status;
}
