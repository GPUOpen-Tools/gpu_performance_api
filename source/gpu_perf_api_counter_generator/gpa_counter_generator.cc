//==============================================================================
// Copyright (c) 2016-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPUPerfAPI Counter Generator function
//==============================================================================

#include <cctype>

#include "gpa_counter_generator.h"
#include "logging.h"
#include "ADLUtil.h"
#include "DeviceInfoUtils.h"
#include "gpa_hw_info.h"
#include "gpa_counter_generator_base.h"
#include "gpa_counter_generator_scheduler_manager.h"

std::vector<std::string> GPA_HardwareCounters::hardware_block_string_;  ///< static map of internal and counter interface hardware block

/// BlockMap for updating ASIC block data on initialization
class BlockMap
{
public:
    /// Add a block to the map
    /// \param counter_group counter group to add to map
    void AddBlock(GPA_CounterGroupDesc* counter_group)
    {
        std::string block(counter_group->m_pName);

        for (char* p = (char*)block.data() + block.length() - 1; (p >= block.data()) && (std::isdigit(*p)); --p)
        {
            block.resize(block.length() - 1);
        }

        std::string index = counter_group->m_pName + block.length();

        uint32_t block_index = std::atoi(index.c_str());

        if (0 == block_index)
        {
            blocks_[block].push_back(counter_group);
        }
        else
        {
            // Handle the case where the block ends in a number, e.g.: ATCL2
            if (blocks_.find(block) == blocks_.end())
            {
                blocks_[counter_group->m_pName].push_back(counter_group);
            }
            else
            {
                blocks_[block].push_back(counter_group);
            }
        }
    }

    /// Get block list by name
    /// \param block name of the block to retrieve
    /// \return vector of blocks
    std::vector<GPA_CounterGroupDesc*> GetBlockList(const std::string& block)
    {
        auto iter = blocks_.find(block);
        if (blocks_.end() == iter)
        {
            return std::vector<GPA_CounterGroupDesc*>();
        }

        return iter->second;
    }

    std::map<std::string, std::vector<GPA_CounterGroupDesc*>> blocks_;  /// map of ASIC blocks by name
};

std::shared_ptr<BlockMap> BuildBlockMap(GPA_CounterGroupDesc* counter_group_list, uint32_t max_count)
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
            // If the block is not found, and max events are zero, it's not an error
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
            entry->m_maxActiveDiscreteCounters = max_discrete_events;
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
            // If the block is not found, and max events are zero, it's not an error
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
            entry->m_maxActiveSpmCounters = max_spm_events;
        }
    }
}

GPA_Status GenerateCounters(GPA_API_Type           desiredAPI,
                            gpa_uint32             vendorId,
                            gpa_uint32             deviceId,
                            gpa_uint32             revisionId,
                            GPA_OpenContextFlags   flags,
                            gpa_uint8              generateAsicSpecificCounters,
                            IGPACounterAccessor**  ppCounterAccessorOut,
                            IGPACounterScheduler** ppCounterSchedulerOut)
{
    if (nullptr == ppCounterAccessorOut)
    {
        GPA_LogError("Parameter 'ppCounterAccessorOut' is NULL.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    // get hardware generation from device Id
    GDT_HW_GENERATION desiredGeneration = GDT_HW_GENERATION_NONE;

    GDT_GfxCardInfo cardInfo{};

    if (NVIDIA_VENDOR_ID == vendorId)
    {
        desiredGeneration = GDT_HW_GENERATION_NVIDIA;
    }
    else if (INTEL_VENDOR_ID == vendorId)
    {
        desiredGeneration = GDT_HW_GENERATION_INTEL;
    }
    else if (AMD_VENDOR_ID == vendorId)
    {
        if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(deviceId, revisionId, cardInfo))
        {
            desiredGeneration = cardInfo.m_generation;

            if ((GPA_API_DIRECTX_12 == desiredAPI || (GPA_API_VULKAN == desiredAPI)) && GDT_HW_GENERATION_VOLCANICISLAND > desiredGeneration)
            {
                return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
            }
        }
    }

    if (desiredGeneration == GDT_HW_GENERATION_NONE)
    {
        GPA_LogError("desiredGeneration is GDT_HW_GENERATION_NONE.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    GPA_Status                status        = GPA_STATUS_OK;
    GPA_CounterGeneratorBase* pTmpAccessor  = nullptr;
    IGPACounterScheduler*     pTmpScheduler = nullptr;

    bool retCode = CounterGeneratorSchedulerManager::Instance()->GetCounterGenerator(desiredAPI, desiredGeneration, pTmpAccessor);

    if (!retCode)
    {
        GPA_LogError("Requesting available counters from an unsupported API or hardware generation.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    bool allowPublic          = (flags & GPA_OPENCONTEXT_HIDE_PUBLIC_COUNTERS_BIT) == 0;
    bool allowSoftware        = (flags & GPA_OPENCONTEXT_HIDE_SOFTWARE_COUNTERS_BIT) == 0;
    bool allowHardwareExposed = (flags & GPA_OPENCONTEXT_ENABLE_HARDWARE_COUNTERS_BIT) == GPA_OPENCONTEXT_ENABLE_HARDWARE_COUNTERS_BIT;
    bool enableHardware       = allowHardwareExposed;

#ifdef AMDT_INTERNAL
    bool allowAllHardware = (flags & GPA_OPENCONTEXT_HIDE_HARDWARE_COUNTERS_BIT) == 0;
    enableHardware        = allowAllHardware;
#endif

    pTmpAccessor->SetAllowedCounters(allowPublic, enableHardware, allowSoftware);
    status = pTmpAccessor->GenerateCounters(desiredGeneration, cardInfo.m_asicType, generateAsicSpecificCounters);

    if (status == GPA_STATUS_OK)
    {
        *ppCounterAccessorOut = pTmpAccessor;

        if (nullptr != ppCounterSchedulerOut)
        {
            retCode = CounterGeneratorSchedulerManager::Instance()->GetCounterScheduler(desiredAPI, desiredGeneration, pTmpScheduler);

            if (!retCode)
            {
                GPA_LogError("Requesting available counters from an unsupported API or hardware generation.");
                return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
            }

            *ppCounterSchedulerOut = pTmpScheduler;
            pTmpScheduler->SetCounterAccessor(pTmpAccessor, vendorId, deviceId, revisionId);
        }
    }

    return status;
}
