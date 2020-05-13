//==============================================================================
// Copyright (c) 2017-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GPA Common Context class implementation
//==============================================================================

#include "gpa_context.h"
#include "gpa_common_defs.h"
#include "gpa_counter_generator.h"
#include "gpa_counter_group_accessor.h"
#include "gpa_hardware_counters.h"
#include "gpa_software_counters.h"
#include "gpa_unique_object.h"
#include "gpa_context_counter_mediator.h"

GPAContext::GPAContext(GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags)
    : m_supportedSampleTypes(GPA_CONTEXT_SAMPLE_TYPE_DISCRETE_COUNTER)
    ,  // by default enable only discrete counters, descendants can override as necessary
    m_contextFlags(flags)
    , m_hwInfo(hwInfo)
    , m_invalidateAndFlushL2CacheEnabled(false)
    , m_isOpen(false)
    , m_isAmdDevice(false)
    , m_pActiveSession(nullptr)
{
    gpa_uint32 vendorId;

    if (m_hwInfo.GetVendorID(vendorId) && AMD_VENDOR_ID == vendorId)
    {
        m_isAmdDevice = true;
    }
}

GPAContext::~GPAContext()
{
    GPAContextCounterMediator::Instance()->RemoveContext(this);
}

GPA_Status GPAContext::GetSupportedSampleTypes(GPA_ContextSampleTypeFlags* pSampleTypes) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(pSampleTypes);

    *pSampleTypes = m_supportedSampleTypes;
    return GPA_STATUS_OK;
}

GPA_Status GPAContext::GetNumCounters(gpa_uint32* pCount) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(pCount);
    IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == pCounterAccessor)
    {
        GPA_LogDebugError("Accessor is unassigned.");
        return GPA_STATUS_ERROR_FAILED;
    }

    *pCount = pCounterAccessor->GetNumCounters();
    return GPA_STATUS_OK;
}

GPA_Status GPAContext::GetCounterName(gpa_uint32 index, const char** ppName) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(ppName);

    IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == pCounterAccessor)
    {
        GPA_LogDebugError("Accessor is unassigned.");
        return GPA_STATUS_ERROR_FAILED;
    }

    *ppName = pCounterAccessor->GetCounterName(index);
    return GPA_STATUS_OK;
}

GPA_Status GPAContext::GetCounterGroup(gpa_uint32 index, const char** ppGroup) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(ppGroup);

    IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == pCounterAccessor)
    {
        GPA_LogDebugError("Accessor is unassigned.");
        return GPA_STATUS_ERROR_FAILED;
    }

    *ppGroup = pCounterAccessor->GetCounterGroup(index);
    return GPA_STATUS_OK;
}

GPA_Status GPAContext::GetCounterDescription(gpa_uint32 index, const char** ppDescription) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(ppDescription);

    IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == pCounterAccessor)
    {
        GPA_LogDebugError("Accessor is unassigned.");
        return GPA_STATUS_ERROR_FAILED;
    }

    *ppDescription = pCounterAccessor->GetCounterDescription(index);
    return GPA_STATUS_OK;
}

GPA_Status GPAContext::GetCounterDataType(gpa_uint32 index, GPA_Data_Type* pCounterDataType) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(pCounterDataType);

    IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == pCounterAccessor)
    {
        GPA_LogDebugError("Accessor is unassigned.");
        return GPA_STATUS_ERROR_FAILED;
    }

    *pCounterDataType = pCounterAccessor->GetCounterDataType(index);
    return GPA_STATUS_OK;
}

GPA_Status GPAContext::GetCounterUsageType(gpa_uint32 index, GPA_Usage_Type* pCounterUsageType) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(pCounterUsageType);

    IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == pCounterAccessor)
    {
        GPA_LogDebugError("Accessor is unassigned.");
        return GPA_STATUS_ERROR_FAILED;
    }

    *pCounterUsageType = pCounterAccessor->GetCounterUsageType(index);
    return GPA_STATUS_OK;
}

GPA_Status GPAContext::GetCounterUuid(gpa_uint32 index, GPA_UUID* pCounterUuid) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(pCounterUuid);

    IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == pCounterAccessor)
    {
        GPA_LogDebugError("Accessor is unassigned.");
        return GPA_STATUS_ERROR_FAILED;
    }

    *pCounterUuid = pCounterAccessor->GetCounterUuid(index);
    return GPA_STATUS_OK;
}

GPA_Status GPAContext::GetCounterSampleType(gpa_uint32 index, GPA_Counter_Sample_Type* pCounterSampleType) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(pCounterSampleType);

    IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == pCounterAccessor)
    {
        GPA_LogDebugError("Accessor is unassigned.");
        return GPA_STATUS_ERROR_FAILED;
    }

    *pCounterSampleType = pCounterAccessor->GetCounterSampleType(index);
    return GPA_STATUS_OK;
}

GPA_Status GPAContext::GetCounterIndex(const char* pCounterName, gpa_uint32* pIndex) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(pIndex);

    IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == pCounterAccessor)
    {
        GPA_LogDebugError("Accessor is unassigned.");
        return GPA_STATUS_ERROR_FAILED;
    }

    return pCounterAccessor->GetCounterIndex(pCounterName, pIndex) ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}

bool GPAContext::GetCounterSourceLocalIndex(gpa_uint32 exposedCounterIndex, GPACounterSource* pSource, gpa_uint32* pSourceLocalIndex) const
{
    assert(nullptr != pSource);
    assert(nullptr != pSourceLocalIndex);

    IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(this);
    assert(nullptr != pCounterAccessor);

    GPACounterSourceInfo info = pCounterAccessor->GetCounterSourceInfo(exposedCounterIndex);

    bool isValid = (GPACounterSource::UNKNOWN != info.m_counterSource);

    if (isValid)
    {
        *pSource           = info.m_counterSource;
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
    IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(this);
    GPACounterSource     source           = GPACounterSource::UNKNOWN;

    if (nullptr != pCounterAccessor)
    {
        const GPA_HardwareCounters* pHwCounters = pCounterAccessor->GetHardwareCounters();

        GPACounterGroupAccessor counterGroupAccessor(
            pHwCounters->m_pGroups, pHwCounters->m_groupCount, pHwCounters->m_pAdditionalGroups, pHwCounters->m_additionalGroupCount);

        counterGroupAccessor.SetCounterIndex(internalCounterIndex);

        if (counterGroupAccessor.IsSWCounter())
        {
            source = GPACounterSource::SOFTWARE;
        }
        else if (counterGroupAccessor.IsHWCounter())
        {
            source = GPACounterSource::HARDWARE;
        }
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
    bool success = GPA_STATUS_OK == GPAContextCounterMediator::Instance()->GenerateCounters(this, m_contextFlags, true);
    return success;
}

GPAObjectType GPAContext::ObjectType() const
{
    return GPAObjectType::GPA_OBJECT_TYPE_CONTEXT;
}

bool GPAContext::DoesSessionExist(GPA_SessionId pSessionId) const
{
    return GetIndex(pSessionId->Object());
}

gpa_uint32 GPAContext::GetSessionCount() const
{
    return static_cast<gpa_uint32>(m_gpaSessionList.size());
}

GPA_Status GPAContext::BeginSession(IGPASession* pGpaSession)
{
    GPA_Status retStatus = GPA_STATUS_OK;

    if (nullptr == pGpaSession)
    {
        retStatus = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        m_activeSessionMutex.lock();

        if (nullptr != m_pActiveSession)
        {
            if (m_pActiveSession != pGpaSession)
            {
                retStatus = GPA_STATUS_ERROR_OTHER_SESSION_ACTIVE;
            }
            else
            {
                retStatus = GPA_STATUS_ERROR_SESSION_ALREADY_STARTED;
            }
        }

        m_activeSessionMutex.unlock();

        if (GPA_STATUS_OK == retStatus)
        {
            retStatus = pGpaSession->Begin();

            if (GPA_STATUS_OK == retStatus)
            {
                m_activeSessionMutex.lock();
                m_pActiveSession = pGpaSession;
                m_activeSessionMutex.unlock();
            }
        }
    }

    return retStatus;
}

GPA_Status GPAContext::EndSession(IGPASession* pGpaSession)
{
    GPA_Status retStatus = GPA_STATUS_OK;

    if (nullptr == pGpaSession)
    {
        retStatus = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        m_activeSessionMutex.lock();

        if (nullptr == m_pActiveSession)
        {
            retStatus = GPA_STATUS_ERROR_SESSION_NOT_STARTED;
        }
        else
        {
            if (m_pActiveSession != pGpaSession)
            {
                retStatus = GPA_STATUS_ERROR_OTHER_SESSION_ACTIVE;
            }
        }

        m_activeSessionMutex.unlock();
    }

    if (GPA_STATUS_OK == retStatus)
    {
        retStatus = pGpaSession->End();

        if (GPA_STATUS_OK == retStatus)
        {
            m_activeSessionMutex.lock();
            m_pActiveSession = nullptr;
            m_activeSessionMutex.unlock();
        }
    }

    return retStatus;
}

const IGPASession* GPAContext::GetActiveSession() const
{
    std::lock_guard<std::mutex> lock(m_activeSessionMutex);
    return m_pActiveSession;
}

void GPAContext::SetAsOpened(bool open)
{
    m_isOpen = open;
}

bool GPAContext::IsAMDDevice() const
{
    gpa_uint32 vendorId;
    bool       isAmd = false;

    if (m_hwInfo.GetVendorID(vendorId) && AMD_VENDOR_ID == vendorId)
    {
        isAmd = true;
    }

    return isAmd;
}

void GPAContext::AddGpaSession(IGPASession* pGpaSession)
{
    std::lock_guard<std::mutex> lockSessionList(m_gpaSessionListMutex);
    m_gpaSessionList.push_back(pGpaSession);
}

void GPAContext::RemoveGpaSession(IGPASession* pGpaSession)
{
    std::lock_guard<std::mutex> lockSessionList(m_gpaSessionListMutex);
    m_gpaSessionList.remove(pGpaSession);
}

void GPAContext::IterateGpaSessionList(std::function<bool(IGPASession* pGpaSession)> function) const
{
    std::lock_guard<std::mutex> lockSessionList(m_gpaSessionListMutex);
    bool                        next = true;

    for (auto it = m_gpaSessionList.cbegin(); it != m_gpaSessionList.cend() && next; ++it)
    {
        next = function(*it);
    }
}

void GPAContext::ClearSessionList()
{
    std::lock_guard<std::mutex> lockSessionList(m_gpaSessionListMutex);
    m_gpaSessionList.clear();
}

bool GPAContext::GetIndex(IGPASession* pGpaSession, unsigned int* pIndex) const
{
    bool         found = false;
    unsigned int index = 0;

    std::lock_guard<std::mutex> lockSessionList(m_gpaSessionListMutex);

    for (auto iter = m_gpaSessionList.cbegin(); iter != m_gpaSessionList.cend(); ++iter)
    {
        if (pGpaSession == *iter)
        {
            found = true;

            if (nullptr != pIndex)
            {
                *pIndex = index;
            }

            break;
        }

        index++;
    }

    return found;
}
