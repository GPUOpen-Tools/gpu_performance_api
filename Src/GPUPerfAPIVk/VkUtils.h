//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Vulkan utility functions declaration
//==============================================================================

#ifndef _VK_UTILS_H_
#define _VK_UTILS_H_

#include <vulkan/vulkan.h>
#include "vk_amd_gpa_interface.h"
#include "GPUPerfAPITypes.h"

namespace VkUtils
{
/// Obtains the GpaFeaturesAMD data from the physical device
/// \param[in] vkPhysicalDevice Vulkan physical device
/// \param[out] pGpaFeaturesAMD The physical device's profiling features
/// \return true if the features were queried; false otherwise
bool GetPhysicalDeviceGpaFeaturesAMD(VkPhysicalDevice vkPhysicalDevice, VkPhysicalDeviceGpaFeaturesAMD* pGpaFeaturesAMD);

/// Obtains the GpaPropertiesAMD data from the physical device
/// \param[in] vkPhysicalDevice Vulkan physical device
/// \param[out] pGpaPropertiesAMD The physical device's profiling properties
/// \return true if the properties were queried; false otherwise
bool GetPhysicalDeviceGpaPropertiesAMD(VkPhysicalDevice vkPhysicalDevice, VkPhysicalDeviceGpaPropertiesAMD* pGpaPropertiesAMD);

/// Release memory that was allocated by GetPhysicalDeviceGpaPropertiesAMD()
/// \param pGpaPropertiesAMD Pointer to the struct that contains the acquired properties.
void ReleasePhysicalDeviceGpaPropertiesAMD(VkPhysicalDeviceGpaPropertiesAMD* pGpaPropertiesAMD);

#ifdef _DEBUG
    // For debugging only: Prints out information about the QueueFamilyTimestamps bits
    void DebugReportQueueFamilyTimestampBits(VkPhysicalDevice vkPhysicalDevice);
#endif //_DEBUG

/// Checks whether the device is supported for profiling or not
/// \param[in] vkPhysicalDevice Vulkan physical device
/// \return true if device is supported otherwise false;
bool IsDeviceSupportedForProfiling(VkPhysicalDevice vkPhysicalDevice);

/// Gets the time stamp frequencey of Vulkan device to convert cycles to milliseconds.
/// \param[in] vkPhysicalDevice device pointer
/// \param[out] timestampFrequency The timestamp frequencey
/// \return true if timestamp frequencey access succeeded, otherwise false
bool GetTimestampFrequency(VkPhysicalDevice vkPhysicalDevice, gpa_uint64& timestampFrequency);

}

#endif // _VK_UTILS_H_
