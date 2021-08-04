//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPUPerfAPI Counter Generator function.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator.h"

#include <cctype>

#include "ADLUtil.h"
#include "DeviceInfoUtils.h"

#include "gpu_perf_api_common/gpa_hw_info.h"
#include "gpu_perf_api_common/logging.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_base.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

std::vector<std::string> GpaHardwareCounters::kHardwareBlockString;  ///< Static map of internal and counter interface hardware block.

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

std::shared_ptr<BlockMap> BuildBlockMap(GpaCounterGroupDesc* counter_group_list, uint32_t max_count)
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
        else
        {
            assert(0);
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
                           GpaUInt32              vendor_id,
                           GpaUInt32              device_id,
                           GpaUInt32              revision_id,
                           GpaOpenContextFlags    flags,
                           GpaUInt8               generate_asic_specific_counters,
                           IGpaCounterAccessor**  counter_accessor_out,
                           IGpaCounterScheduler** counter_scheduler_out)
{
    if (nullptr == counter_accessor_out)
    {
        GPA_LOG_ERROR("Parameter 'counter_accessor_out' is NULL.");
        return kGpaStatusErrorNullPointer;
    }

    // Get hardware generation from device Id.
    GDT_HW_GENERATION desired_generation = GDT_HW_GENERATION_NONE;

    GDT_GfxCardInfo card_info{};

    if (kNvidiaVendorId == vendor_id)
    {
        desired_generation = GDT_HW_GENERATION_NVIDIA;
    }
    else if (kIntelVendorId == vendor_id)
    {
        desired_generation = GDT_HW_GENERATION_INTEL;
    }
    else if (kAmdVendorId == vendor_id)
    {
        if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(device_id, revision_id, card_info))
        {
            desired_generation = card_info.m_generation;

            if ((kGpaApiDirectx12 == desired_api || (kGpaApiVulkan == desired_api)) && GDT_HW_GENERATION_VOLCANICISLAND > desired_generation)
            {
                return kGpaStatusErrorHardwareNotSupported;
            }
        }
    }

    if (desired_generation == GDT_HW_GENERATION_NONE)
    {
        GPA_LOG_ERROR("desiredGeneration is GDT_HW_GENERATION_NONE.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    GpaStatus                status        = kGpaStatusOk;
    GpaCounterGeneratorBase* tmp_accessor  = nullptr;
    IGpaCounterScheduler*    tmp_scheduler = nullptr;

    bool ret_code = CounterGeneratorSchedulerManager::Instance()->GetCounterGenerator(desired_api, desired_generation, tmp_accessor);

    if (!ret_code)
    {
        GPA_LOG_ERROR("Requesting available counters from an unsupported API or hardware generation.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    bool allow_public           = (flags & kGpaOpenContextHidePublicCountersBit) == 0;
    bool allow_software         = (flags & kGpaOpenContextHideSoftwareCountersBit) == 0;
    bool allow_hardware_exposed = (flags & kGpaOpenContextEnableHardwareCountersBit) == kGpaOpenContextEnableHardwareCountersBit;
    bool enable_hardware        = allow_hardware_exposed;

#ifdef AMDT_INTERNAL
    bool allow_all_hardware = (flags & kGpaOpenContextHideHardwareCountersBit) == 0;
    enable_hardware         = allow_all_hardware;
#endif

    tmp_accessor->SetAllowedCounters(allow_public, enable_hardware, allow_software);
    status = tmp_accessor->GenerateCounters(desired_generation, card_info.m_asicType, generate_asic_specific_counters);

    if (status == kGpaStatusOk)
    {
        *counter_accessor_out = tmp_accessor;

        if (nullptr != counter_scheduler_out)
        {
            ret_code = CounterGeneratorSchedulerManager::Instance()->GetCounterScheduler(desired_api, desired_generation, tmp_scheduler);

            if (!ret_code)
            {
                GPA_LOG_ERROR("Requesting available counters from an unsupported API or hardware generation.");
                return kGpaStatusErrorHardwareNotSupported;
            }

            *counter_scheduler_out = tmp_scheduler;
            tmp_scheduler->SetCounterAccessor(tmp_accessor, vendor_id, device_id, revision_id);
        }
    }

    return status;
}
