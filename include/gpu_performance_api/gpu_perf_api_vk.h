//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  This file should be included by an application that wishes to use
///         the Vulkan version of GPUPerfAPI. It defines structures that should
///         be passed to the GPA_OpenContext calls when using GPUPerfAPI with
///         Vulkan.
//==============================================================================

#ifndef GPU_PERFORMANCE_API_GPU_PERF_API_VK_H_
#define GPU_PERFORMANCE_API_GPU_PERF_API_VK_H_

#ifndef VULKAN_H_
#include <vulkan/vulkan.h>
#endif

#include "gpu_performance_api/gpu_perf_api_types.h"

/// Define the AMD GPA extension name.
#define VK_AMD_GPA_INTERFACE_EXTENSION_NAME "VK_AMD_gpa_interface"

/// Define the AMD shader core properties extension name.
#define VK_AMD_SHADER_CORE_PROPERTIES_EXTENSION_NAME "VK_AMD_shader_core_properties"

/// Define the AMD shader core properties 2 extension name.
#define VK_AMD_SHADER_CORE_PROPERTIES_EXTENSION_NAME2 "VK_AMD_shader_core_properties2"

/// Define a macro to help developers include all instance-level extensions required to support the AMD GPA Interface.
#define AMD_GPA_REQUIRED_INSTANCE_EXTENSION_NAME_LIST VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME

/// Define a macro to help developers include all device-level extensions required to support the AMD GPA Interface.
#define AMD_GPA_REQUIRED_DEVICE_EXTENSION_NAME_LIST VK_AMD_GPA_INTERFACE_EXTENSION_NAME, VK_AMD_SHADER_CORE_PROPERTIES_EXTENSION_NAME

/// Define a macro to help developers include optional device-level extensions to support the AMD GPA Interface.
#define AMD_GPA_OPTIONAL_DEVICE_EXTENSION_NAME_LIST VK_AMD_SHADER_CORE_PROPERTIES_EXTENSION_NAME2

/// @brief Additional Vulkan-specific flags that can be passed in along with GpaOpenContextBits when opening a GPA context.
typedef enum
{
    kGpaOpenContextVkUseInfoType2 = kGpaOpenContextApiSpecificOptionsStart  ///< Use GpaVkContextOpenInfoType2 struct as the parameter to GpaOpenContext.
} GpaOpenContextBitsVk;

/// @brief The struct that should be supplied to GpaOpenContext() when using GPUPerfAPI in a Vulkan application.
///
/// The instance, physical device, and device should be set prior to calling GpaOpenContext()
/// to reflect the Vulkan objects on which profiling will take place.
typedef struct GpaVkContextOpenInfoType
{
    VkInstance       instance;         ///< The instance on which to profile.
    VkPhysicalDevice physical_device;  ///< The physical device on which to profile.
    VkDevice         device;           ///< The device on which to profile.
} GpaVkContextOpenInfo;

/// @brief The struct that should be supplied to GpaOpenContext() when using GPUPerfAPI in a Vulkan layer.
///
/// The instance, physical device, and device should be set prior to calling GpaOpenContext()
/// to reflect the Vulkan objects on which profiling will take place.
/// The GetInstanceProcAddr and GetDeviceProcAddr should be set prior to calling GpaOpenContext()
/// to reflect the ProcAddr retrieval methods the profiling will use.
typedef struct GpaVkContextOpenInfoType2
{
    VkInstance                instance;                ///< The instance on which to profile.
    VkPhysicalDevice          physical_device;         ///< The physical device on which to profile.
    VkDevice                  device;                  ///< The device on which to profile.
    PFN_vkGetInstanceProcAddr get_instance_proc_addr;  ///< The vkGetInstanceProcAddr function pointer.
    PFN_vkGetDeviceProcAddr   get_device_proc_addr;    ///< The vkGetDeviceProcAddr function pointer.
} GpaVkContextOpenInfo2;

#endif
