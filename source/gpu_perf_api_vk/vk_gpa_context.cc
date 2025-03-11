//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GPA VK Context Definition
//==============================================================================

#include "gpu_perf_api_vk/vk_gpa_context.h"

#include <mutex>
#include <assert.h>

#include <DeviceInfoUtils.h>

#include "gpu_perf_api_counter_generator/gpa_counter_generator.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_base.h"

#include "gpu_perf_api_common/gpa_unique_object.h"

#include "gpu_performance_api/gpu_perf_api_vk.h"

#include "gpu_perf_api_vk/vk_entry_points.h"
#include "gpu_perf_api_vk/vk_gpa_session.h"
#include "gpu_perf_api_vk/vk_utils.h"

VkGpaContext::VkGpaContext(const GpaVkContextOpenInfo* open_info, GpaHwInfo& hw_info, GpaOpenContextFlags flags)
    : GpaContext(hw_info, flags)
{
    supported_sample_types_ = kGpaContextSampleTypeDiscreteCounter;
    physical_device_        = open_info->physical_device;
    device_                 = open_info->device;
    amd_device_properties_  = {};
    clock_mode_             = VK_GPA_DEVICE_CLOCK_MODE_DEFAULT_AMD;
}

VkGpaContext::~VkGpaContext()
{
    GpaStatus set_stable_clock_status = SetStableClocks(false);

    if (kGpaStatusOk != set_stable_clock_status)
    {
        GPA_LOG_ERROR("Driver was unable to set stable clocks back to default.");
#ifdef __linux__
        GPA_LOG_MESSAGE("In Linux, make sure to run your application with root privileges.");
#endif  // __linux__
    }

    vk_utils::ReleasePhysicalDeviceGpaPropertiesAMD(&amd_device_properties_);

    auto delete_vk_session = [](IGpaSession* gpa_session) -> bool {
        if (nullptr != gpa_session)
        {
            GpaUniqueObjectManager::Instance()->DeleteObject(gpa_session);
            delete gpa_session;
        }

        return true;
    };

    IterateGpaSessionList(delete_vk_session);
    ClearSessionList();
}

GpaStatus VkGpaContext::Open()
{
    GpaStatus result = kGpaStatusOk;

#ifdef _DEBUG
    vk_utils::DebugReportQueueFamilyTimestampBits(physical_device_);
#endif

    if (vk_utils::GetPhysicalDeviceGpaPropertiesAMD(physical_device_, &amd_device_properties_))
    {
        // Counters are supported, set stable clocks.
        // We don't want a failure when setting stable clocks to result in a
        // fatal error returned from here. So we use a local status object
        // instead of modifying "result". We will still output log messages.
        GpaStatus set_stable_clocks = SetStableClocks(true);

        if (kGpaStatusOk != set_stable_clocks)
        {
            GPA_LOG_ERROR("Driver was unable to set stable clocks for profiling.");
#ifdef __linux__
            GPA_LOG_MESSAGE("In Linux, make sure to run your application with root privileges.");
#endif  // __linux__
        }

        SetAsOpened(true);
    }
    else
    {
        GPA_LOG_ERROR("Unable to obtain profiler functionality from the driver / hardware.");
        result = kGpaStatusErrorHardwareNotSupported;
    }

    return result;
}

GpaStatus VkGpaContext::SetStableClocks(bool use_profiling_clocks)
{
    GpaStatus result = kGpaStatusOk;

    if (nullptr == _vkSetGpaDeviceClockModeAMD)
    {
        // VK_AMD_gpa_interface extension is not available.
        GPA_LOG_ERROR("VK_AMD_gpa_interface extension is not available.");
        result = kGpaStatusErrorDriverNotSupported;
    }
    else
    {
        VkGpaDeviceClockModeInfoAMD clock_mode = {};
        clock_mode.sType                       = VK_STRUCTURE_TYPE_GPA_DEVICE_CLOCK_MODE_INFO_AMD;
        clock_mode.clockMode                   = VK_GPA_DEVICE_CLOCK_MODE_DEFAULT_AMD;

        if (use_profiling_clocks)
        {
            DeviceClockMode device_clock_mode = GetDeviceClockMode();

            switch (device_clock_mode)
            {
            case DeviceClockMode::kDefault:
                clock_mode.clockMode = VK_GPA_DEVICE_CLOCK_MODE_DEFAULT_AMD;
                break;

            case DeviceClockMode::kProfiling:
                clock_mode.clockMode = VK_GPA_DEVICE_CLOCK_MODE_PROFILING_AMD;
                break;

            case DeviceClockMode::kMinimumMemory:
                clock_mode.clockMode = VK_GPA_DEVICE_CLOCK_MODE_MIN_MEMORY_AMD;
                break;

            case DeviceClockMode::kMinimumEngine:
                clock_mode.clockMode = VK_GPA_DEVICE_CLOCK_MODE_MIN_ENGINE_AMD;
                break;

            case DeviceClockMode::kPeak:
                clock_mode.clockMode = VK_GPA_DEVICE_CLOCK_MODE_PEAK_AMD;
                break;

            default:
                assert(0);
                clock_mode.clockMode = VK_GPA_DEVICE_CLOCK_MODE_PROFILING_AMD;
                break;
            }
        }

        if (clock_mode.clockMode != clock_mode_)
        {
            clock_mode_           = clock_mode.clockMode;
            VkResult clock_result = _vkSetGpaDeviceClockModeAMD(device_, &clock_mode);
            result                = (clock_result == VK_SUCCESS) ? kGpaStatusOk : kGpaStatusErrorDriverNotSupported;

            if (VK_SUCCESS != clock_result)
            {
                GPA_LOG_ERROR("Failed to set ClockMode for profiling.");
            }
        }
    }

    return result;
}

GpaSessionId VkGpaContext::CreateSession(GpaSessionSampleType sample_type)
{
    GpaSessionId session_id = nullptr;

    VkGpaSession* session = new (std::nothrow) VkGpaSession(this, sample_type);

    if (nullptr != session)
    {
        AddGpaSession(session);
        session_id = reinterpret_cast<GpaSessionId>(GpaUniqueObjectManager::Instance()->CreateObject(session));
    }

    return session_id;
}

bool VkGpaContext::DeleteSession(GpaSessionId sessionId)
{
    bool is_deleted = false;

    std::lock_guard<std::mutex> lock_session_result(session_list_mutex_);

    VkGpaSession* vk_session = reinterpret_cast<VkGpaSession*>(sessionId->Object());
    is_deleted               = DeleteVkGpaSession(vk_session);

    return is_deleted;
}

bool VkGpaContext::DeleteVkGpaSession(VkGpaSession* gpa_session)
{
    if (nullptr != gpa_session)
    {
        RemoveGpaSession(gpa_session);
        GpaUniqueObjectManager::Instance()->DeleteObject(gpa_session);
        delete gpa_session;
    }

    return true;
}

GpaUInt32 VkGpaContext::GetMaxGpaSessions() const
{
    // There is no maximum number of sessions.
    return kGpaSessionNoLimit;
}

GpaApiType VkGpaContext::GetApiType() const
{
    return kGpaApiVulkan;
}

VkDevice VkGpaContext::GetVkDevice() const
{
    return device_;
}

VkPhysicalDevice VkGpaContext::GetVkPhysicalDevice() const
{
    return physical_device_;
}

GpaUInt32 VkGpaContext::GetNumInstances(VkGpaPerfBlockAMD block) const
{
    GpaUInt32 instance_count = 0;

    if (block < VK_GPA_PERF_BLOCK_RANGE_SIZE_AMD)
    {
        for (uint32_t i = 0; i < amd_device_properties_.perfBlockCount; i++)
        {
            if (amd_device_properties_.pPerfBlocks[i].blockType == block)
            {
                instance_count = static_cast<GpaUInt32>(amd_device_properties_.pPerfBlocks[i].instanceCount);
                break;
            }
        }
    }

    return instance_count;
}

GpaUInt32 VkGpaContext::GetMaxEventId(VkGpaPerfBlockAMD block) const
{
    GpaUInt32 max_event_id = 0;

    if (block < VK_GPA_PERF_BLOCK_RANGE_SIZE_AMD)
    {
        for (uint32_t i = 0; i < amd_device_properties_.perfBlockCount; i++)
        {
            if (amd_device_properties_.pPerfBlocks[i].blockType == block)
            {
                max_event_id = static_cast<GpaUInt32>(amd_device_properties_.pPerfBlocks[i].maxEventID);
                break;
            }
        }
    }

    return max_event_id;
}