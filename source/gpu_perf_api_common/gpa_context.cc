//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
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

namespace
{
#ifdef _WIN32
    HANDLE gpa_mutex_handle = nullptr;  // IPC Mutex to prevent TDRs from multiple apps trying to profile GPU

    void CloseIpcMutex(HANDLE& mutex_handle)
    {
        if (mutex_handle != nullptr)
        {
            ReleaseMutex(mutex_handle);
            CloseHandle(mutex_handle);
            mutex_handle = nullptr;
        }
    }
#endif
}  // namespace

GpaContext::GpaContext(const GpaHwInfo& hw_info, GpaOpenContextFlags flags)
    : context_flags_(flags)
    , hw_info_(hw_info)
    , is_open_(false)
    , active_session_(nullptr)
{
}

std::optional<GpaContextSampleTypeFlags> GpaContext::GetSupportedSampleTypes() const
{
    const GpaApiType    api         = GetApiType();
    const GpaDriverInfo driver_info = GpaQueryDriverInfo();

    // GpaContext is initialized with a valid GpaHwInfo that contains a valid DeviceDescription,
    // so the value can be safely accessed without checking for std::nullopt.
    const device_info::AdapterId adapter_id = hw_info_.GetDeviceDescription().value();

    const GpaContextSampleTypeFlags supported_sample_types_ = CalculateSupportedSampleTypes(adapter_id, api, driver_info);

    // This should never occur! GpaOpenContext should have validated that a proper device was utilized!
    // GPA has enough testing to ensure that this is the case.
    assert(supported_sample_types_ != 0);
    return supported_sample_types_;
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
    if (gpa_session == nullptr) [[unlikely]]
    {
        return kGpaStatusErrorNullPointer;
    }

    GpaStatus ret_status = kGpaStatusOk;
    {
        std::scoped_lock lock(active_session_mutex_);
        if (active_session_ != nullptr)
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
#ifdef _WIN32
        // Our hardware does NOT support parallel execution using the counters.
        // We have global controls at this time and no UMD to UMD synchronization to prevent collision.
        // Depending on the queue usage and granularity, it could be expected to work, but that makes
        // many assumptions of work scheduling on the GPU.
        //
        // Use a named mutex to allow for inter-process synchronization.
        // This helps ensure only 1 app has access to the counters at a time.
        // As long as they are using GPA to access the HW counters.
        if (gpa_mutex_handle = CreateMutexA(nullptr, FALSE, "Global\\GpaSession"); gpa_mutex_handle == nullptr)
        {
            GpaLogger::Instance().LogError("Failed to create mutex.");
            return kGpaStatusErrorFailed;
        }

        GpaLogger::Instance().LogMessage("Waiting on Global GPA Session Mutex (INFINITE).");

        if (const DWORD wait_result = WaitForSingleObject(gpa_mutex_handle, INFINITE); wait_result == WAIT_OBJECT_0)
        {
            GpaLogger::Instance().LogMessage("Global GPA Session Mutex acquired successfully.");
        }
        else if (wait_result == WAIT_ABANDONED)
        {
            GpaLogger::Instance().LogMessage("Mutex was abandoned. Previous process may have been killed or crashed.");
        }
        else
        {
            GpaLogger::Instance().LogError("Failed to acquire mutex. Wait result: {}", wait_result);
            CloseHandle(gpa_mutex_handle);
            gpa_mutex_handle = NULL;
            return kGpaStatusErrorFailed;
        }
#else
        GpaLogger::Instance().LogMessage("Warning: No inter-process synchronization mechanism in place for non-Windows platforms. See README.md known issues.");
#endif

        ret_status = gpa_session->Begin();

        if (ret_status == kGpaStatusOk)
        {
            std::scoped_lock lock(active_session_mutex_);
            active_session_ = gpa_session;
        }
#ifdef _WIN32
        else
        {
            // Release and close the IPC mutex if session begin failed
            CloseIpcMutex(gpa_mutex_handle);
        }
#endif
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
            std::scoped_lock lock(active_session_mutex_);
            active_session_ = nullptr;
        }
    }

#ifdef _WIN32
    // Release and close the IPC mutex
    CloseIpcMutex(gpa_mutex_handle);
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

void GpaContext::AddGpaSession(std::unique_ptr<IGpaSession> gpa_session)
{
    std::lock_guard<std::mutex> lock_session_list(gpa_session_list_mutex_);
    gpa_session_list_.push_back(std::move(gpa_session));
}

void GpaContext::RemoveGpaSession(IGpaSession* gpa_session)
{
    std::lock_guard<std::mutex> lock_session_list(gpa_session_list_mutex_);
    gpa_session_list_.remove_if([gpa_session](const std::unique_ptr<IGpaSession>& session) { return session.get() == gpa_session; });
}

void GpaContext::IterateGpaSessionList(const std::function<bool(IGpaSession* gpa_session)>& function) const
{
    std::lock_guard<std::mutex> lock_session_list(gpa_session_list_mutex_);
    bool                        next = true;

    for (auto it = gpa_session_list_.cbegin(); it != gpa_session_list_.cend() && next; ++it)
    {
        next = function(it->get());
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
        if (gpa_session == iter->get())
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
    GpaLogger::Instance().LogError("Unable to determine Shader Engine count.");
    return 0;
}
