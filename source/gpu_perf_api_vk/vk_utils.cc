//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Vulkan utility functions implementation
//==============================================================================

#include "gpu_perf_api_vk/vk_utils.h"

#include <assert.h>

#include <vector>

#include "gpu_perf_api_common/logging.h"

#include "gpu_perf_api_vk/vk_entry_points.h"

#include "gpa_hw_info.h"

#ifdef _DEBUG
void vk_utils::DebugReportQueueFamilyTimestampBits(VkPhysicalDevice vk_physical_device)
{
    if (vk_utils::are_entry_points_initialized)
    {
        uint32_t queue_family_count = 0;
        _vkGetPhysicalDeviceQueueFamilyProperties(vk_physical_device, &queue_family_count, nullptr);

        if (queue_family_count != 0)
        {
            std::vector<VkQueueFamilyProperties> queue_family_properties(queue_family_count);

            _vkGetPhysicalDeviceQueueFamilyProperties(vk_physical_device, &queue_family_count, queue_family_properties.data());

            for (unsigned int i = 0; i < queue_family_count; ++i)
            {
                if ((queue_family_properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) || (queue_family_properties[i].queueFlags & VK_QUEUE_COMPUTE_BIT))
                {
                    // GPA is only really applicable to queues that support graphics or compute.
                    if (queue_family_properties[i].timestampValidBits == 0)
                    {
                        GpaLogger::Instance().LogError(
                            "QueueFamily {} supports Graphics or Compute, but does NOT have any valid timestamp bits; it cannot support profiling.", i);
                    }
                    else
                    {
                        GpaLogger::Instance().LogDebugMessage(
                            "QueueFamily {} supports Graphics or Compute, and has {} valid timestamp bits; it will support profiling.",
                            i,
                            queue_family_properties[i].timestampValidBits);
                    }
                }
            }
        }
        else
        {
            GpaLogger::Instance().LogError("Device does not support any queue families; profiling cannot be supported.");
        }
    }
    else
    {
        GpaLogger::Instance().LogError("Vulkan entrypoints are not initialized.");
    }
}
#endif

bool vk_utils::IsDeviceSupportedForProfiling(VkPhysicalDevice vk_physical_device)
{
    if (!vk_utils::are_entry_points_initialized)
    {
        GpaLogger::Instance().LogError("Vulkan entrypoints are not initialized.");
        return false;
    }

#ifdef __linux__
    VkPhysicalDeviceDriverPropertiesKHR driver_properties = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES_KHR,
    };

    VkPhysicalDeviceProperties2KHR device_properties = {
        .sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2_KHR,
        .pNext = &driver_properties,
    };

    _vkGetPhysicalDeviceProperties2KHR(vk_physical_device, &device_properties);

    const VkDriverIdKHR driver_id = driver_properties.driverID;

    if (driver_id == VK_DRIVER_ID_MESA_RADV_KHR)
    {
        GpaLogger::Instance().LogError("The Mesa RADV Vulkan driver is not currently supported.");
        return false;
    }

    if (driver_id == VK_DRIVER_ID_AMD_PROPRIETARY_KHR || driver_id == VK_DRIVER_ID_AMD_OPEN_SOURCE_KHR)
    {
        const GpaUInt32 device_id      = device_properties.properties.deviceID;
        const uint32_t  driver_version = device_properties.properties.driverVersion;

        // https://gpuopen.com/learn/decoding-radeon-vulkan-versions/
        // https://gpuopen.com/version-table/
        // Extract the version
        const uint32_t major = VK_API_VERSION_MAJOR(driver_version);
        const uint32_t minor = VK_API_VERSION_MINOR(driver_version);
        // Our pro drivers always set the minor version to 0!
        assert(minor == 0);
        const uint32_t patch = VK_API_VERSION_PATCH(driver_version);

        // IE: Anything less than 2.0.342 is not supported
        const bool known_bad_driver_rx_9070 = (major <= 2) && (minor == 0) && (patch < 342);
        const bool amd_radeon_rx_9070       = (device_id == 0x7550);

        if (amd_radeon_rx_9070 && known_bad_driver_rx_9070)
        {
            GpaLogger::Instance().LogError("The Radeon RX 9070 requires AMD Vulkan driver 2.0.342 or newer.");
            return false;
        }
    }
#endif

    bool     is_supported       = false;
    uint32_t queue_family_count = 0;
    _vkGetPhysicalDeviceQueueFamilyProperties(vk_physical_device, &queue_family_count, nullptr);

    if (queue_family_count != 0)
    {
        std::vector<VkQueueFamilyProperties> queue_family_properties(queue_family_count);

        _vkGetPhysicalDeviceQueueFamilyProperties(vk_physical_device, &queue_family_count, queue_family_properties.data());

        if (queue_family_properties[0].timestampValidBits == 0)
        {
            GpaLogger::Instance().LogError("QueueFamily 0 does not have any valid timestamp bits; cannot be supported.");
        }
        else
        {
            VkPhysicalDeviceGpaFeaturesAMD features_amd = {};
            features_amd.sType                          = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GPA_FEATURES_AMD;

            VkPhysicalDeviceFeatures2KHR features = {};
            features.sType                        = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2_KHR;
            features.pNext                        = &features_amd;

            _vkGetPhysicalDeviceFeatures2KHR(vk_physical_device, &features);

            if (features_amd.perfCounters == VK_TRUE)
            {
                is_supported = true;
            }
        }
    }
    else
    {
        GpaLogger::Instance().LogError("Device does not support any queue families; cannot be supported.");
    }

    return is_supported;
}

bool vk_utils::GetTimestampFrequency(VkPhysicalDevice vk_physical_device, GpaUInt64& timestamp_frequency)
{
    bool success = false;

    if (are_entry_points_initialized)
    {
        VkPhysicalDeviceProperties properties;
        _vkGetPhysicalDeviceProperties(vk_physical_device, &properties);

        // Vulkan's timestamp_period is expressed in nanoseconds per clock tick, convert to frequency in seconds.
        float timestamp_period = properties.limits.timestampPeriod;
        timestamp_frequency    = static_cast<GpaUInt64>(1000000000.0f / (timestamp_period));

        success = true;
    }
    else
    {
        GpaLogger::Instance().LogError("Vulkan entrypoints are not initialized.");
    }

    return success;
}
