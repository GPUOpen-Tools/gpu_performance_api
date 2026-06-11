//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GPA VK Context Definition
//==============================================================================

#include "gpu_perf_api_vk/vk_gpa_context.h"

#include <memory>
#include <mutex>
#include <assert.h>

#include "gpu_perf_api_counter_generator/gpa_counter_generator.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_base.h"

#include "gpu_perf_api_common/gpa_unique_object.h"

#include "gpu_performance_api/gpu_perf_api_vk.h"

#include "gpu_perf_api_vk/vk_entry_points.h"
#include "gpu_perf_api_vk/vk_gpa_session.h"
#include "gpu_perf_api_vk/vk_utils.h"

namespace
{
    /// @brief Obtains the GpaFeaturesAMD data from the physical device.
    ///
    /// @param [in] physical_device Vulkan physical device.
    /// @param [out] gpa_features_amd The physical device's profiling features.
    ///
    /// @return True if the features were queried; false otherwise.
    bool GetPhysicalDeviceGpaFeaturesAMD(VkPhysicalDevice physical_device, VkPhysicalDeviceGpaFeaturesAMD* gpa_features_amd)
    {
        bool status = false;

        if (nullptr == gpa_features_amd) [[unlikely]]
        {
            GpaLogger::Instance().LogError("Output parameter gpa_features_amd is null.");
            return false;
        }

        if (!vk_utils::are_entry_points_initialized) [[unlikely]]
        {
            GpaLogger::Instance().LogError("Vulkan entrypoints are not initialized.");
            return false;
        }

        if (nullptr == _vkGetPhysicalDeviceFeatures2KHR) [[unlikely]]
        {
            GpaLogger::Instance().LogError("VK_KHR_get_physical_device_properties2 extension entrypoint not available.");
            return false;
        }

        *gpa_features_amd       = {};
        gpa_features_amd->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GPA_FEATURES_AMD;

        VkPhysicalDeviceFeatures2KHR features = {};
        features.sType                        = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2_KHR;
        features.pNext                        = gpa_features_amd;

        _vkGetPhysicalDeviceFeatures2KHR(physical_device, &features);
        status = true;

        return status;
    }
}  // namespace

VkGpaContext::VkGpaContext(const GpaVkContextOpenInfo* open_info, const GpaHwInfo& hw_info, GpaOpenContextFlags flags)
    : GpaContext(hw_info, flags)
{
    physical_device_       = open_info->physical_device;
    device_                = open_info->device;
    amd_device_properties_ = {};
    clock_mode_            = VK_GPA_DEVICE_CLOCK_MODE_DEFAULT_AMD;
}

VkGpaContext::~VkGpaContext()
{
    GpaStatus set_stable_clock_status = SetStableClocks(false);

    if (kGpaStatusOk != set_stable_clock_status)
    {
        GpaLogger::Instance().LogError("Driver was unable to set stable clocks back to default.");
#ifdef __linux__
        GpaLogger::Instance().LogMessage("In Linux, make sure to run your application with root privileges.");
#endif
    }

    // ClearSessionList() destroys the owned sessions via unique_ptr. Unique-object manager wrappers are removed first.
    IterateGpaSessionList([](IGpaSession* gpa_session) -> bool {
        GpaUniqueObjectManager::Instance().DeleteObject(gpa_session);
        return true;
    });
    ClearSessionList();
}

GpaStatus VkGpaContext::Open()
{
    GpaStatus result = kGpaStatusOk;

#ifdef _DEBUG
    vk_utils::DebugReportQueueFamilyTimestampBits(physical_device_);
#endif

    if (GetPhysicalDeviceGpaPropertiesAMD(physical_device_, &amd_device_properties_))
    {
        // Counters are supported, set stable clocks.
        // We don't want a failure when setting stable clocks to result in a
        // fatal error returned from here. So we use a local status object
        // instead of modifying "result". We will still output log messages.
        GpaStatus set_stable_clocks = SetStableClocks(true);

        if (kGpaStatusOk != set_stable_clocks)
        {
            GpaLogger::Instance().LogError("Driver was unable to set stable clocks for profiling.");
#ifdef __linux__
            GpaLogger::Instance().LogMessage("In Linux, make sure to run your application with root privileges.");
#endif
        }

        SetAsOpened(true);
    }
    else
    {
        GpaLogger::Instance().LogError("Unable to obtain profiler functionality from the driver / hardware.");
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
        GpaLogger::Instance().LogError("VK_AMD_gpa_interface extension is not available.");
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
                GpaLogger::Instance().LogError("Failed to set ClockMode for profiling.");
            }
        }
    }

    return result;
}

GpaSessionId VkGpaContext::CreateSession(GpaSessionSampleType sample_type)
{
    auto          session     = std::make_unique<VkGpaSession>(this, sample_type);
    VkGpaSession* raw_session = session.get();

    AddGpaSession(std::move(session));
    return reinterpret_cast<GpaSessionId>(GpaUniqueObjectManager::Instance().CreateObject(raw_session));
}

bool VkGpaContext::DeleteSession(GpaSessionId sessionId)
{
    std::lock_guard<std::mutex> lock_session_result(session_list_mutex_);

    VkGpaSession* vk_session = reinterpret_cast<VkGpaSession*>(sessionId->Object());
    return DeleteVkGpaSession(vk_session);
}

bool VkGpaContext::DeleteVkGpaSession(VkGpaSession* gpa_session)
{
    assert(nullptr != gpa_session);
    GpaUniqueObjectManager::Instance().DeleteObject(gpa_session);
    // Removing from the session list triggers destruction via unique_ptr.
    RemoveGpaSession(gpa_session);
    return true;
}

bool VkGpaContext::GetPhysicalDeviceGpaPropertiesAMD(VkPhysicalDevice physical_device, VkPhysicalDeviceGpaPropertiesAMD* gpa_properties_amd)
{
    bool status = false;

    // This function is expected to be called only once during context open.
    // Otherwise we risk having dangling pointers in the VkPhysicalDeviceGpaPropertiesAMD
    // struct if the perf block count changes and we need to resize the storage vector.
    if (!perf_blocks_storage_.empty()) [[unlikely]]
    {
        assert(false);
        return false;
    }

    if (gpa_properties_amd == nullptr) [[unlikely]]
    {
        assert(false);
        return false;
    }

    VkPhysicalDeviceGpaFeaturesAMD gpa_features_amd = {};

    if (GetPhysicalDeviceGpaFeaturesAMD(physical_device, &gpa_features_amd))
    {
        if (VK_TRUE == gpa_features_amd.perfCounters)
        {
            // For now it is assumed that Vk MGPU support is exposed to the app
            // and the app always opens the device on the correct GPU.
            // In case where MGPU support hides the GPU from the app, then
            // we will need to use Vk MGPU extension to get the correct HW info.
            *gpa_properties_amd       = {};
            gpa_properties_amd->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GPA_PROPERTIES_AMD;

            VkPhysicalDeviceProperties2KHR properties = {};
            properties.sType                          = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2_KHR;
            properties.pNext                          = gpa_properties_amd;

            _vkGetPhysicalDeviceProperties2KHR(physical_device, &properties);

            if (gpa_properties_amd->perfBlockCount > 0)
            {
                perf_blocks_storage_.resize(gpa_properties_amd->perfBlockCount);
                gpa_properties_amd->pPerfBlocks = perf_blocks_storage_.data();

                _vkGetPhysicalDeviceProperties2KHR(physical_device, &properties);
                status = true;
            }
            else
            {
                GpaLogger::Instance().LogError("Active physical device does not expose any perf counter blocks.");
            }
        }
        else
        {
            GpaLogger::Instance().LogError("Active physical device does not support performance counters.");
        }
    }
    else
    {
        GpaLogger::Instance().LogError("Failed to get physical device features.");
    }

    return status;
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
