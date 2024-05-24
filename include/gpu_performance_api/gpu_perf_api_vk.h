//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  This file should be included by an application that wishes to use
///         the Vulkan version of GPUPerfAPI. It defines structures that should
///         be passed to the GPA_OpenContext calls when using GPUPerfAPI with
///         Vulkan.
//==============================================================================

#ifndef GPU_PERFORMANCE_API_GPU_PERF_API_VK_H_
#define GPU_PERFORMANCE_API_GPU_PERF_API_VK_H_

#include <vulkan/vulkan.h>
#include "vk_amd_gpa_interface.h"


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

typedef struct GpaVkApiEntrypoints_v1_Type
{
    PFN_vkGetPhysicalDeviceProperties vkGetPhysicalDeviceProperties;
    PFN_vkGetPhysicalDeviceQueueFamilyProperties vkGetPhysicalDeviceQueueFamilyProperties;
    PFN_vkGetPhysicalDeviceMemoryProperties      vkGetPhysicalDeviceMemoryProperties;
    PFN_vkGetPhysicalDeviceFeatures              vkGetPhysicalDeviceFeatures;
    PFN_vkGetBufferMemoryRequirements            vkGetBufferMemoryRequirements;
    PFN_vkGetPhysicalDeviceProperties2KHR        vkGetPhysicalDeviceProperties2KHR;
    PFN_vkGetPhysicalDeviceFeatures2KHR          vkGetPhysicalDeviceFeatures2KHR;

    PFN_vkGetDeviceQueue          vkGetDeviceQueue;
    PFN_vkCreateQueryPool         vkCreateQueryPool;
    PFN_vkDestroyQueryPool        vkDestroyQueryPool;
    PFN_vkCreateBuffer            vkCreateBuffer;
    PFN_vkDestroyBuffer           vkDestroyBuffer;
    PFN_vkAllocateMemory          vkAllocateMemory;
    PFN_vkBindBufferMemory        vkBindBufferMemory;
    PFN_vkFreeMemory              vkFreeMemory;
    PFN_vkMapMemory               vkMapMemory;
    PFN_vkUnmapMemory             vkUnmapMemory;
    PFN_vkFlushMappedMemoryRanges vkFlushMappedMemoryRanges;
    PFN_vkCmdResetQueryPool       vkCmdResetQueryPool;
    PFN_vkCmdBeginQuery           vkCmdBeginQuery;
    PFN_vkCmdEndQuery             vkCmdEndQuery;
    PFN_vkCmdWriteTimestamp       vkCmdWriteTimestamp;
    PFN_vkCmdCopyQueryPoolResults vkCmdCopyQueryPoolResults;
    PFN_vkGetQueryPoolResults     vkGetQueryPoolResults;
    PFN_vkCmdCopyBuffer           vkCmdCopyBuffer;
    PFN_vkDeviceWaitIdle          vkDeviceWaitIdle;

    PFN_vkCreateGpaSessionAMD         vkCreateGpaSessionAMD;
    PFN_vkDestroyGpaSessionAMD        vkDestroyGpaSessionAMD;
    PFN_vkSetGpaDeviceClockModeAMD    vkSetGpaDeviceClockModeAMD;
    PFN_vkCmdBeginGpaSessionAMD       vkCmdBeginGpaSessionAMD;
    PFN_vkCmdEndGpaSessionAMD         vkCmdEndGpaSessionAMD;
    PFN_vkCmdBeginGpaSampleAMD        vkCmdBeginGpaSampleAMD;
    PFN_vkCmdEndGpaSampleAMD          vkCmdEndGpaSampleAMD;
    PFN_vkGetGpaSessionStatusAMD      vkGetGpaSessionStatusAMD;
    PFN_vkGetGpaSessionResultsAMD     vkGetGpaSessionResultsAMD;
    PFN_vkResetGpaSessionAMD          vkResetGpaSessionAMD;
    PFN_vkCmdCopyGpaSessionResultsAMD vkCmdCopyGpaSessionResultsAMD;
} GpaVkApiEntrypoints_v1;


/// @brief The struct that should be supplied to GpaOpenContext().
///
/// The instance, physical device, and device should be set prior to calling GpaOpenContext()
/// to reflect the Vulkan objects on which profiling will take place.
typedef struct GpaVkContextOpenInfoType
{
    VkInstance       instance;         ///< The instance on which to profile.
    VkPhysicalDevice physical_device;  ///< The physical device on which to profile.
    VkDevice         device;           ///< The device on which to profile.
    union 
    {
        struct
        {
            uint32_t callFromLayer : 1;
            uint32_t reserved      : 31;
        };

        uint32_t flags;
    };

    union
    {
        GpaVkApiEntrypoints_v1 vkEntry;
    };
} GpaVkContextOpenInfo;




#endif  // GPU_PERFORMANCE_API_GPU_PERF_API_VK_H_
