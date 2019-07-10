//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage the D3D11 Query-based software counters
//==============================================================================

#include "GPASwCounterManager.h"

SwCounterManager::SwCounterManager()
    : m_amdCounters(0)
    , m_swGPUTimeCounter(0)
    , m_swGPUTimeEnabled(false)
    , m_swCountersGenerated(false)
{
    m_swCounters.clear();
    m_enabledSwCounters.clear();
}

SwCounterManager::~SwCounterManager()
{
    m_swCounters.clear();
    m_enabledSwCounters.clear();

    m_swCountersGenerated = false;
}

void SwCounterManager::AddSwCounter(const GPA_SoftwareCounterDesc& counterDesc)
{
    m_swCounters.push_back(counterDesc);
}

void SwCounterManager::EnableSwCounter(gpa_uint32 index)
{
    m_enabledSwCounters.insert(index);
}

void SwCounterManager::DisableSwCounter(gpa_uint32 index)
{
    m_enabledSwCounters.erase(index);
}

void SwCounterManager::AddSwCounterMap(const gpa_uint32 pubIndex, const gpa_uint32 swIndex)
{
    m_swCounterIndexMap[swIndex] = pubIndex;
}

void SwCounterManager::ClearSwCounterMap()
{
    m_swCounterIndexMap.clear();
}

void SwCounterManager::SetSwGPUTimeCounterIndex(const gpa_uint32 pubIndex)
{
    m_swGPUTimeCounter = pubIndex;
}

void SwCounterManager::SetSwGPUTimeCounterEnabled(const bool enabled)
{
    m_swGPUTimeEnabled = enabled;
}

bool SwCounterManager::SwGPUTimeCounterEnabled() const
{
    return m_swGPUTimeEnabled;
}

gpa_uint32 SwCounterManager::GetSwGPUTimeCounterIndex() const
{
    return m_swGPUTimeCounter;
}

gpa_uint32 SwCounterManager::GetSwCounterPubIndex(const gpa_uint32 swIndex) const
{
    gpa_uint32 pubIndex = 0;
    auto       search   = m_swCounterIndexMap.find(swIndex);

    if (search != m_swCounterIndexMap.end())
    {
        pubIndex = search->second;
    }

    return pubIndex;
}

void SwCounterManager::SetNumAmdCounters(const gpa_uint32 counters)
{
    m_amdCounters = counters;
}

gpa_uint32 SwCounterManager::GetNumAmdCounters() const
{
    return m_amdCounters;
}

bool SwCounterManager::SwCountersGenerated() const
{
    return m_swCountersGenerated;
}

bool SwCounterManager::SwCounterEnabled() const
{
    return (m_enabledSwCounters.empty() == false);
}

void SwCounterManager::ClearEnabledSwCounters()
{
    m_enabledSwCounters.clear();
}

const SwCounterDescVec* SwCounterManager::GetSwCounters() const
{
    return &m_swCounters;
}

gpa_uint32 SwCounterManager::GetNumSwCounters() const
{
    return static_cast<gpa_uint32>(m_swCounters.size());
}

const EnabledSwCounterSet* SwCounterManager::GetEnabledSwCounters() const
{
    return &m_enabledSwCounters;
}

void SwCounterManager::SetSwCountersGenerated(const bool set)
{
    m_swCountersGenerated = set;
}
