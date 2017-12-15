//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GPA Common Context class implementation
//==============================================================================

#include "GPAContext.h"
#include "GPACommonDefs.h"
#include "GPACounterGenerator.h"
#include "GPACounterGroupAccessor.h"
#include "GPAHardwareCounters.h"
#include "GPASoftwareCounters.h"

#define CHECK_FOR_NULL_COUNTER_ACCESSOR(X)                  \
    if(nullptr == X)                                        \
    {                                                       \
        GPA_LogDebugError("Accessor is unassigned.");       \
        return GPA_STATUS_ERROR_FAILED;                     \
    }

GPA_Status GPAContext::GetNumCounters(gpa_uint32* pCount) const
{
    CHECK_FOR_NULL_COUNTER_ACCESSOR(m_pCounterAccessor);
    GPA_INTERNAL_CHECK_NULL_PARAM(pCount);
    *pCount = m_pCounterAccessor->GetNumCounters();
    return GPA_STATUS_OK;
}

GPA_Status GPAContext::GetCounterName(gpa_uint32 index,
                                      const char** ppName) const
{
    CHECK_FOR_NULL_COUNTER_ACCESSOR(m_pCounterAccessor);
    GPA_INTERNAL_CHECK_NULL_PARAM(ppName);
    *ppName = m_pCounterAccessor->GetCounterName(index);
    return GPA_STATUS_OK;
}

GPA_Status GPAContext::GetCounterGroup(gpa_uint32 index,
                                       const char** ppGroup) const
{
    CHECK_FOR_NULL_COUNTER_ACCESSOR(m_pCounterAccessor);
    GPA_INTERNAL_CHECK_NULL_PARAM(ppGroup);
    *ppGroup = m_pCounterAccessor->GetCounterGroup(index);
    return GPA_STATUS_OK;
}

GPA_Status GPAContext::GetCounterDescription(gpa_uint32 index,
                                             const char** ppDescription) const
{
    CHECK_FOR_NULL_COUNTER_ACCESSOR(m_pCounterAccessor);
    GPA_INTERNAL_CHECK_NULL_PARAM(ppDescription);
    *ppDescription = m_pCounterAccessor->GetCounterDescription(index);
    return GPA_STATUS_OK;
}

GPA_Status GPAContext::GetCounterDataType(gpa_uint32 index,
                                          GPA_Data_Type* pCounterDataType) const
{
    CHECK_FOR_NULL_COUNTER_ACCESSOR(m_pCounterAccessor);
    GPA_INTERNAL_CHECK_NULL_PARAM(pCounterDataType);
    *pCounterDataType = m_pCounterAccessor->GetCounterDataType(index);
    return GPA_STATUS_OK;
}

GPA_Status GPAContext::GetCounterUsageType(gpa_uint32 index,
                                           GPA_Usage_Type* pCounterUsageType) const
{
    CHECK_FOR_NULL_COUNTER_ACCESSOR(m_pCounterAccessor);
    GPA_INTERNAL_CHECK_NULL_PARAM(pCounterUsageType);
    *pCounterUsageType = m_pCounterAccessor->GetCounterUsageType(index);
    return GPA_STATUS_OK;
}

GPA_Status GPAContext::GetCounterUuid(gpa_uint32 index, GPA_UUID* pCounterUuid) const
{
    CHECK_FOR_NULL_COUNTER_ACCESSOR(m_pCounterAccessor);
    GPA_INTERNAL_CHECK_NULL_PARAM(pCounterUuid);
    *pCounterUuid = m_pCounterAccessor->GetCounterUuid(index);
    return GPA_STATUS_OK;
}

GPA_Status GPAContext::GetCounterIndex(const char* pCounterName,
                                       gpa_uint32* pIndex) const
{
    CHECK_FOR_NULL_COUNTER_ACCESSOR(m_pCounterAccessor);
    GPA_INTERNAL_CHECK_NULL_PARAM(pIndex);
    m_pCounterAccessor->GetCounterIndex(pCounterName, pIndex);
    return GPA_STATUS_OK;
}

bool GPAContext::GetCounterSourceLocalIndex(gpa_uint32 exposedCounterIndex, GPACounterSource* pSource, gpa_uint32* pSourceLocalIndex) const
{
    assert(nullptr != pSource);
    assert(nullptr != pSourceLocalIndex);
    assert(nullptr != m_pCounterAccessor);

    GPACounterSourceInfo info = m_pCounterAccessor->GetCounterSourceInfo(exposedCounterIndex);

    bool isValid = (GPACounterSource::UNKNOWN != info.m_counterSource);

    if (isValid)
    {
        *pSource = info.m_counterSource;
        *pSourceLocalIndex = info.m_localIndex;
    }

    return isValid;
}

bool GPAContext::ArePublicCountersExposed() const
{
    return (m_contextFlags & GPA_OPENCONTEXT_HIDE_PUBLIC_COUNTERS_BIT) == 0;
}

bool GPAContext::AreHardwareCountersExposed() const
{
    return (m_contextFlags & GPA_OPENCONTEXT_HIDE_HARDWARE_COUNTERS_BIT) == 0;
}

bool GPAContext::AreSoftwareCountersExposed() const
{
    return (m_contextFlags & GPA_OPENCONTEXT_HIDE_SOFTWARE_COUNTERS_BIT) == 0;
}

GPACounterSource GPAContext::GetCounterSource(gpa_uint32 internalCounterIndex) const
{
    const GPA_HardwareCounters* pHwCounters = m_pCounterAccessor->GetHardwareCounters();
    const GPA_SoftwareCounters* pSwCounters = m_pCounterAccessor->GetSoftwareCounters();
    GPACounterGroupAccessor counterGroupAccessor(
        pHwCounters->m_pGroups,
        pHwCounters->m_groupCount,
        pHwCounters->m_pAdditionalGroups,
        pHwCounters->m_additionalGroupCount,
        pSwCounters->m_pGroups,
        pSwCounters->m_groupCount);

    counterGroupAccessor.SetCounterIndex(internalCounterIndex);

    GPACounterSource source;

    if (counterGroupAccessor.IsSWCounter())
    {
        source = GPACounterSource::SOFTWARE;
    }
    else if (counterGroupAccessor.IsHWCounter())
    {
        source = GPACounterSource::HARDWARE;
    }
    else
    {
        source = GPACounterSource::UNKNOWN;
        GPA_LogError("Unknown Counter type.");
    }

    return source;
}


void GPAContext::SetInvalidateAndFlushL2Cache(bool shouldInvalidateAndFlushL2Cache)
{
    m_invalidateAndFlushL2CacheEnabled = shouldInvalidateAndFlushL2Cache;
}

bool GPAContext::IsInvalidateAndFlushL2CacheEnabled() const
{
    return m_invalidateAndFlushL2CacheEnabled;
}

const GPA_HWInfo* GPAContext::GetHwInfo() const
{
    return &m_hwInfo;
}

bool GPAContext::IsOpen() const
{
    return m_isOpen;
}

DeviceClockMode GPAContext::GetDeviceClockMode() const
{
    if (m_contextFlags & GPA_OPENCONTEXT_CLOCK_MODE_NONE_BIT)
    {
        return DeviceClockMode::Default;
    }

    if (m_contextFlags & GPA_OPENCONTEXT_CLOCK_MODE_PEAK_BIT)
    {
        return DeviceClockMode::Peak;
    }

    if (m_contextFlags & GPA_OPENCONTEXT_CLOCK_MODE_MIN_MEMORY_BIT)
    {
        return DeviceClockMode::MinimumMemory;
    }

    if (m_contextFlags & GPA_OPENCONTEXT_CLOCK_MODE_MIN_ENGINE_BIT)
    {
        return DeviceClockMode::MinimumEngine;
    }

    return DeviceClockMode::Profiling;
}

bool GPAContext::OpenCounters()
{
    bool success = false;

    IGPACounterAccessor* pCounterAccessor = nullptr;
    IGPACounterScheduler* pCounterScheduler = nullptr;

    gpa_uint32 vendorId;
    gpa_uint32 deviceId;
    gpa_uint32 revisionId;

    if (m_hwInfo.GetVendorID(vendorId) &&
        m_hwInfo.GetDeviceID(deviceId) &&
        m_hwInfo.GetRevisionID(revisionId))
    {
        GPA_Status result = GenerateCounters(
                                GetAPIType(),
                                vendorId,
                                deviceId,
                                revisionId,
                                &pCounterAccessor,
                                &pCounterScheduler);

        if (GPA_STATUS_OK == result)
        {
            pCounterAccessor->SetAllowedCounters(ArePublicCountersExposed(),
                AreHardwareCountersExposed(),
                AreSoftwareCountersExposed());

            m_pCounterAccessor = pCounterAccessor;
            m_pCounterScheduler = pCounterScheduler;

            if (GPA_STATUS_OK == m_pCounterScheduler->SetCounterAccessor(m_pCounterAccessor, vendorId, deviceId, revisionId))
            {
                success = true;
            }
            else
            {
                GPA_LogError("Failed to set counter accessor.");
            }
        }
    }

    return success;
}

GPAObjectType GPAContext::ObjectType() const
{
    return GPAObjectType::GPA_OBJECT_TYPE_CONTEXT;
}

const IGPACounterAccessor* GPAContext::GetCounterAccessor() const noexcept
{
    return m_pCounterAccessor;
}

IGPACounterScheduler* GPAContext::GetCounterScheduler() const noexcept
{
    return m_pCounterScheduler;
}

gpa_uint32 GPAContext::GetSessionCount() const
{
    return static_cast<gpa_uint32>(m_gpaSessionList.size());
}

GPAContext::GPAContext(GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags)
{
    m_hwInfo = hwInfo;
    m_contextFlags = flags;
    m_invalidateAndFlushL2CacheEnabled = false;
    m_isOpen = false;
    m_pCounterScheduler = nullptr;
    m_pCounterAccessor = nullptr;
    m_isAmdDevice = false;

    gpa_uint32 vendorId;

    if (m_hwInfo.GetVendorID(vendorId) &&
        AMD_VENDOR_ID == vendorId)
    {
        m_isAmdDevice = true;
    }
}

void GPAContext::SetAsOpened(bool open)
{
    m_isOpen = open;
}
