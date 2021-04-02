//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class to manage the D3D11 Query-based software counters.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_sw_counter_manager.h"

SwCounterManager::SwCounterManager()
    : amd_counters_(0)
    , sw_gpu_time_counter_(0)
    , sw_gpu_time_enabled_(false)
    , sw_counters_generated_(false)
{
    sw_counters_.clear();
    enabled_sw_counters_.clear();
}

SwCounterManager::~SwCounterManager()
{
    sw_counters_.clear();
    enabled_sw_counters_.clear();

    sw_counters_generated_ = false;
}

void SwCounterManager::AddSwCounter(const GpaSoftwareCounterDesc& counter_desc)
{
    sw_counters_.push_back(counter_desc);
}

void SwCounterManager::EnableSwCounter(GpaUInt32 index)
{
    enabled_sw_counters_.insert(index);
}

void SwCounterManager::DisableSwCounter(GpaUInt32 index)
{
    enabled_sw_counters_.erase(index);
}

void SwCounterManager::AddSwCounterMap(const GpaUInt32 pub_index, const GpaUInt32 sw_index)
{
    sw_counter_index_map_[sw_index] = pub_index;
}

void SwCounterManager::ClearSwCounterMap()
{
    sw_counter_index_map_.clear();
}

void SwCounterManager::SetSwGpuTimeCounterIndex(const GpaUInt32 pub_index)
{
    sw_gpu_time_counter_ = pub_index;
}

void SwCounterManager::SetSwGpuTimeCounterEnabled(const bool enabled)
{
    sw_gpu_time_enabled_ = enabled;
}

bool SwCounterManager::SwGpuTimeCounterEnabled() const
{
    return sw_gpu_time_enabled_;
}

GpaUInt32 SwCounterManager::GetSwGpuTimeCounterIndex() const
{
    return sw_gpu_time_counter_;
}

GpaUInt32 SwCounterManager::GetSwCounterPubIndex(const GpaUInt32 sw_index) const
{
    GpaUInt32 pubIndex = 0;
    auto       search   = sw_counter_index_map_.find(sw_index);

    if (search != sw_counter_index_map_.end())
    {
        pubIndex = search->second;
    }

    return pubIndex;
}

void SwCounterManager::SetNumAmdCounters(const GpaUInt32 counters)
{
    amd_counters_ = counters;
}

GpaUInt32 SwCounterManager::GetNumAmdCounters() const
{
    return amd_counters_;
}

bool SwCounterManager::SwCountersGenerated() const
{
    return sw_counters_generated_;
}

bool SwCounterManager::SwCounterEnabled() const
{
    return (enabled_sw_counters_.empty() == false);
}

void SwCounterManager::ClearEnabledSwCounters()
{
    enabled_sw_counters_.clear();
}

const SwCounterDescVec* SwCounterManager::GetSwCounters() const
{
    return &sw_counters_;
}

GpaUInt32 SwCounterManager::GetNumSwCounters() const
{
    return static_cast<GpaUInt32>(sw_counters_.size());
}

const EnabledSwCounterSet* SwCounterManager::GetEnabledSwCounters() const
{
    return &enabled_sw_counters_;
}

void SwCounterManager::SetSwCountersGenerated(const bool set)
{
    sw_counters_generated_ = set;
}
