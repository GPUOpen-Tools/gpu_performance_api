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
#include "gpu_perf_api_common/gpa_hw_support.h"

GpaContext::GpaContext(const GpaHwInfo& hw_info, GpaOpenContextFlags flags)
    : context_flags_(flags)
    , hw_info_(hw_info)
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

GpaContextSampleTypeFlags GpaContext::GetSupportedSampleTypes() const
{
    const GpaApiType                api                     = GetApiType();
    const GpaDriverInfo             driver_info             = QueryDriverInfo();

    // Get device_id
    GpaUInt32                       device_id               = 0;
    [[maybe_unused]] bool           available               = hw_info_.GetDeviceId(device_id);
    assert(available);

    // Get revision_id
    GpaUInt32 revision_id = 0;
    available             = hw_info_.GetRevisionId(revision_id);
    assert(available);

    const GpaContextSampleTypeFlags supported_sample_types_ = CalculateSupportedSampleTypes(device_id, revision_id, api, driver_info);
    // This should never occur! GpaOpenContext should have validated that a proper device was utilized!
    assert(supported_sample_types_ != 0);
    return supported_sample_types_;
}

bool GpaContext::ArePublicCountersExposed() const
{
    return (context_flags_ & kGpaOpenContextHidePublicCountersBit) == 0;
}

bool GpaContext::AreHardwareCountersExposed() const
{
    return (context_flags_ & kGpaOpenContextEnableHardwareCountersBit) == 0;
}

const GpaHwInfo& GpaContext::GetHwInfo() const
{
    return hw_info_;
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
#ifdef _WIN32
    // Our hardware does NOT support parallel execution using the counters.
    // We have global controls at this time and no UMD to UMD synchronization to prevent collision.
    // Depending on the queue usage and granularity, it could be expected to work, but that makes
    // many assumptions of work scheduling on the GPU.
    //
    // Use a named mutex to allow for inter-process synchronization.
    // This helps ensure only 1 app has access to the counters at a time.
    // As long as they are using GPA to access the HW counters.
    gpa_mutex_handle = CreateMutexA(NULL, FALSE, "Global\\GpaSession");
    if (gpa_mutex_handle == NULL)
    {
        GPA_LOG_ERROR("Failed to create mutex.");
        return kGpaStatusErrorFailed;
    }

    DWORD wait_result = WaitForSingleObject(gpa_mutex_handle, INFINITE);
    if (wait_result == WAIT_OBJECT_0)
    {
        GPA_LOG_MESSAGE("Global GPA Session Mutex acquired successfully.");
    }
    else if (wait_result == WAIT_ABANDONED)
    {
        GPA_LOG_MESSAGE("Mutex was abandoned. Previous process may have been killed or crashed.");
    }
    else
    {
        GPA_LOG_ERROR("Failed to acquire mutex. Wait result: %lu", wait_result);
        CloseHandle(gpa_mutex_handle);
        gpa_mutex_handle = NULL;
        return kGpaStatusErrorFailed;
    }
#endif

    GpaStatus ret_status = kGpaStatusOk;

    if (nullptr == gpa_session)
    {
        ret_status = kGpaStatusErrorNullPointer;
    }
    else
    {
        {
            std::lock_guard<std::mutex> lock(active_session_mutex_);
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
        }

        if (kGpaStatusOk == ret_status)
        {
            ret_status = gpa_session->Begin();

            if (kGpaStatusOk == ret_status)
            {
                std::lock_guard<std::mutex> lock(active_session_mutex_);
                active_session_ = gpa_session;
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
        std::lock_guard<std::mutex> lock(active_session_mutex_);

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
    }

    if (force_end || kGpaStatusOk == ret_status)
    {
        ret_status = gpa_session->End();

        if (force_end || kGpaStatusOk == ret_status)
        {
            std::lock_guard<std::mutex> lock(active_session_mutex_);
            active_session_ = nullptr;
        }
    }

#ifdef _WIN32
    // Release and close the IPC mutex
    if (gpa_mutex_handle != NULL)
    {
        ReleaseMutex(gpa_mutex_handle);
        CloseHandle(gpa_mutex_handle);
        gpa_mutex_handle = NULL;
    }
#endif

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
