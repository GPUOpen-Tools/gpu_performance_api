//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA Common Context class implementation.
//==============================================================================

#include "gpu_perf_api_common/gpa_context.h"

#include "gpu_perf_api_counter_generator/gpa_counter_group_accessor.h"
#include "gpu_perf_api_counter_generator/gpa_hardware_counters.h"

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_common/gpa_context_counter_mediator.h"
#include "gpu_perf_api_common/gpa_unique_object.h"

GpaContext::GpaContext(GpaHwInfo& hw_info, GpaOpenContextFlags flags)
    : supported_sample_types_(0)
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
}

GpaStatus GpaContext::GetSupportedSampleTypes(GpaContextSampleTypeFlags* sample_types) const
{
    GPA_INTERNAL_CHECK_NULL_PARAM(sample_types);

    *sample_types = supported_sample_types_;
    return kGpaStatusOk;
}

bool GpaContext::ArePublicCountersExposed() const
{
    return (context_flags_ & kGpaOpenContextHidePublicCountersBit) == 0;
}

bool GpaContext::AreHardwareCountersExposed() const
{
    return (context_flags_ & kGpaOpenContextEnableHardwareCountersBit) == 0;
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

void GpaContext::UpdateHwInfo(GpaUInt32 num_shader_engines, GpaUInt32 num_compute_units, GpaUInt32 num_simds, GpaUInt32 num_waves_per_simd)
{
    hw_info_.SetNumberShaderEngines(num_shader_engines);
    hw_info_.SetNumberCus(num_compute_units);
    hw_info_.SetNumberSimds(num_simds);
    hw_info_.SetWavesPerSimd(num_waves_per_simd);
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

GpaObjectType GpaContext::ObjectType() const
{
    return GpaObjectType::kGpaObjectTypeContext;
}

bool GpaContext::DoesSessionExist(GpaSessionId gpa_session_id) const
{
    return GetIndex(gpa_session_id->Object());
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

GpaStatus GpaContext::EndSession(IGpaSession* gpa_session, bool force_end)
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

    if (force_end || kGpaStatusOk == ret_status)
    {
        ret_status = gpa_session->End();

        if (force_end || kGpaStatusOk == ret_status)
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

void GpaContext::IterateGpaSessionList(const std::function<bool(IGpaSession* gpa_session)>& function) const
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

uint32_t GpaContext::GetShaderEngineCount() const
{
    GPA_LOG_ERROR("Unable to determine Shader Engine count.");
    return 0;
}
