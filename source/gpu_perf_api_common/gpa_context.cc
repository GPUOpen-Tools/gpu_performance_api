//==============================================================================
// Copyright (c) 2017-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA Common Context class implementation.
//==============================================================================

#include "gpu_perf_api_common/gpa_context.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator.h"
#include "gpu_perf_api_counter_generator/gpa_counter_group_accessor.h"
#include "gpu_perf_api_counter_generator/gpa_hardware_counters.h"

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_common/gpa_context_counter_mediator.h"
#include "gpu_perf_api_common/gpa_unique_object.h"

GpaContext::GpaContext(GpaHwInfo& hw_info, GpaOpenContextFlags flags)
    : supported_sample_types_(kGpaContextSampleTypeDiscreteCounter)
    , context_flags_(flags)
    , hw_info_(hw_info)
    , invalidate_and_flush_l2_cache_enabled_(false)
    , is_open_(false)
    , is_amd_device_(false)
    , active_session_(nullptr)
{
    GpaUInt32 vendor_id;

    if (hw_info_.GetVendorId(vendor_id) && kAmdVendorId == vendor_id)
    {
        is_amd_device_ = true;
    }
}

GpaContext::~GpaContext()
{
    GpaContextCounterMediator::Instance()->RemoveContext(this);
}

GpaStatus GpaContext::GetSupportedSampleTypes(GpaContextSampleTypeFlags* sample_types) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(sample_types);

    *sample_types = supported_sample_types_;
    return kGpaStatusOk;
}

GpaStatus GpaContext::GetNumCounters(GpaUInt32* counter_count) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(counter_count);
    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == counter_accessor)
    {
        GPA_LOG_DEBUG_ERROR("Accessor is unassigned.");
        return kGpaStatusErrorFailed;
    }

    *counter_count = counter_accessor->GetNumCounters();
    return kGpaStatusOk;
}

GpaStatus GpaContext::GetCounterName(GpaUInt32 index, const char** counter_name) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(counter_name);

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == counter_accessor)
    {
        GPA_LOG_DEBUG_ERROR("Accessor is unassigned.");
        return kGpaStatusErrorFailed;
    }

    *counter_name = counter_accessor->GetCounterName(index);
    return kGpaStatusOk;
}

GpaStatus GpaContext::GetCounterGroup(GpaUInt32 index, const char** counter_group) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(counter_group);

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == counter_accessor)
    {
        GPA_LOG_DEBUG_ERROR("Accessor is unassigned.");
        return kGpaStatusErrorFailed;
    }

    *counter_group = counter_accessor->GetCounterGroup(index);
    return kGpaStatusOk;
}

GpaStatus GpaContext::GetCounterDescription(GpaUInt32 index, const char** counter_description) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(counter_description);

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == counter_accessor)
    {
        GPA_LOG_DEBUG_ERROR("Accessor is unassigned.");
        return kGpaStatusErrorFailed;
    }

    *counter_description = counter_accessor->GetCounterDescription(index);
    return kGpaStatusOk;
}

GpaStatus GpaContext::GetCounterDataType(GpaUInt32 index, GpaDataType* counter_data_type) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(counter_data_type);

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == counter_accessor)
    {
        GPA_LOG_DEBUG_ERROR("Accessor is unassigned.");
        return kGpaStatusErrorFailed;
    }

    *counter_data_type = counter_accessor->GetCounterDataType(index);
    return kGpaStatusOk;
}

GpaStatus GpaContext::GetCounterUsageType(GpaUInt32 index, GpaUsageType* counter_usage_type) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(counter_usage_type);

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == counter_accessor)
    {
        GPA_LOG_DEBUG_ERROR("Accessor is unassigned.");
        return kGpaStatusErrorFailed;
    }

    *counter_usage_type = counter_accessor->GetCounterUsageType(index);
    return kGpaStatusOk;
}

GpaStatus GpaContext::GetCounterUuid(GpaUInt32 index, GpaUuid* counter_uuid) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(counter_uuid);

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == counter_accessor)
    {
        GPA_LOG_DEBUG_ERROR("Accessor is unassigned.");
        return kGpaStatusErrorFailed;
    }

    *counter_uuid = counter_accessor->GetCounterUuid(index);
    return kGpaStatusOk;
}

GpaStatus GpaContext::GetCounterSampleType(GpaUInt32 index, GpaCounterSampleType* counter_sample_type) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(counter_sample_type);

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == counter_accessor)
    {
        GPA_LOG_DEBUG_ERROR("Accessor is unassigned.");
        return kGpaStatusErrorFailed;
    }

    *counter_sample_type = counter_accessor->GetCounterSampleType(index);
    return kGpaStatusOk;
}

GpaStatus GpaContext::GetCounterIndex(const char* pCounterName, GpaUInt32* counter_index) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(counter_index);

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    if (nullptr == counter_accessor)
    {
        GPA_LOG_DEBUG_ERROR("Accessor is unassigned.");
        return kGpaStatusErrorFailed;
    }

    return counter_accessor->GetCounterIndex(pCounterName, counter_index) ? kGpaStatusOk : kGpaStatusErrorFailed;
}

bool GpaContext::GetCounterSourceLocalIndex(GpaUInt32 exposed_counter_index, GpaCounterSource* counter_source, GpaUInt32* source_local_index) const
{
    assert(nullptr != counter_source);
    assert(nullptr != source_local_index);

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);
    assert(nullptr != counter_accessor);

    GpaCounterSourceInfo info = counter_accessor->GetCounterSourceInfo(exposed_counter_index);

    bool isValid = (GpaCounterSource::kUnknown != info.counter_source);

    if (isValid)
    {
        *counter_source     = info.counter_source;
        *source_local_index = info.local_counter_index;
    }

    return isValid;
}

bool GpaContext::ArePublicCountersExposed() const
{
    return (context_flags_ & kGpaOpenContextHidePublicCountersBit) == 0;
}

bool GpaContext::AreHardwareCountersExposed() const
{
    return (context_flags_ & kGpaOpenContextEnableHardwareCountersBit) == 0;
}

bool GpaContext::AreSoftwareCountersExposed() const
{
    // GPA no longer support SW counters
    return false;
}

GpaCounterSource GpaContext::GetCounterSource(GpaUInt32 internal_counter_index) const
{
    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);
    GpaCounterSource     source           = GpaCounterSource::kUnknown;

    if (nullptr != counter_accessor)
    {
        const GpaHardwareCounters* hardware_counters = counter_accessor->GetHardwareCounters();
        unsigned int               internal_counter_groups_count = static_cast<unsigned int>(hardware_counters->internal_counter_groups_.size());

        GpaCounterGroupAccessor counter_group_accessor(hardware_counters->internal_counter_groups_,
                                                       internal_counter_groups_count,
                                                       hardware_counters->additional_groups_,
                                                       hardware_counters->additional_group_count_);

        counter_group_accessor.SetCounterIndex(internal_counter_index);

        if (counter_group_accessor.IsHwCounter())
        {
            source = GpaCounterSource::kHardware;
        }
    }

    return source;
}

void GpaContext::SetInvalidateAndFlushL2Cache(bool should_invalidate_and_flush_l2_cache)
{
    invalidate_and_flush_l2_cache_enabled_ = should_invalidate_and_flush_l2_cache;
}

bool GpaContext::IsInvalidateAndFlushL2CacheEnabled() const
{
    return invalidate_and_flush_l2_cache_enabled_;
}

const GpaHwInfo* GpaContext::GetHwInfo() const
{
    return &hw_info_;
}

bool GpaContext::IsOpen() const
{
    return is_open_;
}

DeviceClockMode GpaContext::GetDeviceClockMode() const
{
    if (context_flags_ & kGpaOpenContextClockModeNoneBit)
    {
        return DeviceClockMode::kDefault;
    }

    if (context_flags_ & kGpaOpenContextClockModePeakBit)
    {
        return DeviceClockMode::kPeak;
    }

    if (context_flags_ & kGpaOpenContextClockModeMinMemoryBit)
    {
        return DeviceClockMode::kMinimumMemory;
    }

    if (context_flags_ & kGpaOpenContextClockModeMinEngineBit)
    {
        return DeviceClockMode::kMinimumEngine;
    }

    return DeviceClockMode::kProfiling;
}

bool GpaContext::OpenCounters()
{
    bool success = (kGpaStatusOk == GpaContextCounterMediator::Instance()->GenerateCounters(this, context_flags_, true));
    return success;
}

GpaObjectType GpaContext::ObjectType() const
{
    return GpaObjectType::kGpaObjectTypeContext;
}

bool GpaContext::DoesSessionExist(GpaSessionId gpa_session_id) const
{
    return GetIndex(gpa_session_id->Object());
}

GpaUInt32 GpaContext::GetSessionCount() const
{
    return static_cast<GpaUInt32>(gpa_session_list_.size());
}

GpaStatus GpaContext::BeginSession(IGpaSession* gpa_session)
{
    GpaStatus ret_status = kGpaStatusOk;

    if (nullptr == gpa_session)
    {
        ret_status = kGpaStatusErrorNullPointer;
    }
    else
    {
        active_session_mutex_.lock();

        if (nullptr != active_session_)
        {
            if (active_session_ != gpa_session)
            {
                ret_status = kGpaStatusErrorOtherSessionActive;
            }
            else
            {
                ret_status = kGpaStatusErrorSessionAlreadyStarted;
            }
        }

        active_session_mutex_.unlock();

        if (kGpaStatusOk == ret_status)
        {
            ret_status = gpa_session->Begin();

            if (kGpaStatusOk == ret_status)
            {
                active_session_mutex_.lock();
                active_session_ = gpa_session;
                active_session_mutex_.unlock();
            }
        }
    }

    return ret_status;
}

GpaStatus GpaContext::EndSession(IGpaSession* gpa_session)
{
    GpaStatus ret_status = kGpaStatusOk;

    if (nullptr == gpa_session)
    {
        ret_status = kGpaStatusErrorNullPointer;
    }
    else
    {
        active_session_mutex_.lock();

        if (nullptr == active_session_)
        {
            ret_status = kGpaStatusErrorSessionNotStarted;
        }
        else
        {
            if (active_session_ != gpa_session)
            {
                ret_status = kGpaStatusErrorOtherSessionActive;
            }
        }

        active_session_mutex_.unlock();
    }

    if (kGpaStatusOk == ret_status)
    {
        ret_status = gpa_session->End();

        if (kGpaStatusOk == ret_status)
        {
            active_session_mutex_.lock();
            active_session_ = nullptr;
            active_session_mutex_.unlock();
        }
    }

    return ret_status;
}

const IGpaSession* GpaContext::GetActiveSession() const
{
    std::lock_guard<std::mutex> lock(active_session_mutex_);
    return active_session_;
}

void GpaContext::SetAsOpened(bool open)
{
    is_open_ = open;
}

bool GpaContext::IsAmdDevice() const
{
    GpaUInt32 vendor_id;
    bool      is_amd = false;

    if (hw_info_.GetVendorId(vendor_id) && kAmdVendorId == vendor_id)
    {
        is_amd = true;
    }

    return is_amd;
}

void GpaContext::AddGpaSession(IGpaSession* gpa_session)
{
    std::lock_guard<std::mutex> lock_session_list(gpa_session_list_mutex_);
    gpa_session_list_.push_back(gpa_session);
}

void GpaContext::RemoveGpaSession(IGpaSession* gpa_session)
{
    std::lock_guard<std::mutex> lock_session_list(gpa_session_list_mutex_);
    gpa_session_list_.remove(gpa_session);
}

void GpaContext::IterateGpaSessionList(std::function<bool(IGpaSession* gpa_session)> function) const
{
    std::lock_guard<std::mutex> lock_session_list(gpa_session_list_mutex_);
    bool                        next = true;

    for (auto it = gpa_session_list_.cbegin(); it != gpa_session_list_.cend() && next; ++it)
    {
        next = function(*it);
    }
}

void GpaContext::ClearSessionList()
{
    std::lock_guard<std::mutex> lock_session_list(gpa_session_list_mutex_);
    gpa_session_list_.clear();
}

bool GpaContext::GetIndex(IGpaSession* gpa_session, unsigned int* index) const
{
    bool         found      = false;
    unsigned int temp_index = 0;

    std::lock_guard<std::mutex> lock_session_list(gpa_session_list_mutex_);

    for (auto iter = gpa_session_list_.cbegin(); iter != gpa_session_list_.cend(); ++iter)
    {
        if (gpa_session == *iter)
        {
            found = true;

            if (nullptr != index)
            {
                *index = temp_index;
            }

            break;
        }

        temp_index++;
    }

    return found;
}
