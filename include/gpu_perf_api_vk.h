//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Deprecated header; use gpu_performance_api/gpu_perf_api_vk.h
//==============================================================================

#ifndef GPU_PERF_API_VK_H_
#define GPU_PERF_API_VK_H_

#pragma message("Warning: You are including a deprecated header. Please use gpu_performance_api/gpu_perf_api_vk.h")

#include "vulkan/vulkan.h"

#include "gpu_performance_api/gpu_perf_api_vk.h"

/// The struct that should be supplied to GPA_OpenContext().
/// The instance, physical_device, and device should be set prior to
/// calling OpenContext() to reflect the Vulkan objects on which profiling
/// will take place.
typedef struct GPA_vkContextOpenInfo
{
    VkInstance       instance;        ///< The instance on which to profile
    VkPhysicalDevice physicalDevice;  ///< The physical device on which to profile
    VkDevice         device;          ///< The device on which to profile
} GPA_vkContextOpenInfo;

#endif  // GPU_PERF_API_VK_H_
