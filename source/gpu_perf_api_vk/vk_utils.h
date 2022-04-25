//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Vulkan utility functions declaration
//==============================================================================

#ifndef GPU_PERF_API_VK_VK_UTILS_H_
#define GPU_PERF_API_VK_VK_UTILS_H_

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_vk/vk_includes.h"

namespace vk_utils
{
    /// @brief Obtains the GpaFeaturesAMD data from the physical device.
    ///
    /// @param [in] vk_physical_device Vulkan physical device.
    /// @param [out] gpa_features_amd The physical device's profiling features.
    ///
    /// @return True if the features were queried; false otherwise.
    bool GetPhysicalDeviceGpaFeaturesAMD(VkPhysicalDevice vk_physical_device, VkPhysicalDeviceGpaFeaturesAMD* gpa_features_amd);

    /// @brief Obtains the GpaPropertiesAMD data from the physical device.
    ///
    /// @param [in] vk_physical_device Vulkan physical device.
    /// @param [out] gpa_properties_amd The physical device's profiling properties.
    ///
    /// @return True if the properties were queried; false otherwise.
    bool GetPhysicalDeviceGpaPropertiesAMD(VkPhysicalDevice vk_physical_device, VkPhysicalDeviceGpaPropertiesAMD* gpa_properties_amd);

    /// @brief Release memory that was allocated by GetPhysicalDeviceGpaPropertiesAMD().
    ///
    /// @param [in] gpa_properties_amd Pointer to the struct that contains the acquired properties.
    void ReleasePhysicalDeviceGpaPropertiesAMD(VkPhysicalDeviceGpaPropertiesAMD* gpa_properties_amd);

#ifdef _DEBUG
    /// @brief For debugging only: Prints out information about the QueueFamilyTimestamps bits.
    ///
    /// @param [in] vk_physical_device The physical device to which the queue family belongs.
    void DebugReportQueueFamilyTimestampBits(VkPhysicalDevice vk_physical_device);
#endif  //_DEBUG

    /// @brief Checks whether the device is supported for profiling or not.
    ///
    /// @param [in] vk_physical_device Vulkan physical device.
    ///
    /// @return True if device is supported otherwise false.
    bool IsDeviceSupportedForProfiling(VkPhysicalDevice vk_physical_device);

    /// @brief Gets the time stamp frequency of Vulkan device to convert cycles to milliseconds.
    ///
    /// @param [in] vk_physical_device Device pointer.
    /// @param [out] timestamp_frequency The timestamp frequency.
    ///
    /// @return True if timestamp frequency access succeeded, otherwise false.
    bool GetTimestampFrequency(VkPhysicalDevice vk_physical_device, GpaUInt64& timestamp_frequency);

}  // namespace vk_utils

#endif  // GPU_PERF_API_VK_VK_UTILS_H_
