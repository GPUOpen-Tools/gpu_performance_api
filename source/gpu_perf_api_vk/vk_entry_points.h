//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Declares Vk Entrypoints
//==============================================================================

#ifndef GPU_PERF_API_VK_VK_ENTRYPOINTS_H_
#define GPU_PERF_API_VK_VK_ENTRYPOINTS_H_

#include "gpu_perf_api_vk/vk_includes.h"

extern PFN_vkGetPhysicalDeviceProperties            _vkGetPhysicalDeviceProperties;             ///< Vulkan entrypoint.
extern PFN_vkGetPhysicalDeviceQueueFamilyProperties _vkGetPhysicalDeviceQueueFamilyProperties;  ///< Vulkan entrypoint.
extern PFN_vkGetPhysicalDeviceMemoryProperties      _vkGetPhysicalDeviceMemoryProperties;       ///< Vulkan entrypoint.
extern PFN_vkGetPhysicalDeviceFeatures              _vkGetPhysicalDeviceFeatures;               ///< Vulkan entrypoint.
extern PFN_vkGetPhysicalDeviceProperties2KHR        _vkGetPhysicalDeviceProperties2KHR;         ///< Vulkan entrypoint.
extern PFN_vkGetPhysicalDeviceFeatures2KHR          _vkGetPhysicalDeviceFeatures2KHR;           ///< Vulkan entrypoint.

extern PFN_vkGetDeviceQueue              _vkGetDeviceQueue;               ///< Vulkan entrypoint.
extern PFN_vkCreateQueryPool             _vkCreateQueryPool;              ///< Vulkan entrypoint.
extern PFN_vkDestroyQueryPool            _vkDestroyQueryPool;             ///< Vulkan entrypoint.
extern PFN_vkCreateBuffer                _vkCreateBuffer;                 ///< Vulkan entrypoint.
extern PFN_vkDestroyBuffer               _vkDestroyBuffer;                ///< Vulkan entrypoint.
extern PFN_vkGetBufferMemoryRequirements _vkGetBufferMemoryRequirements;  ///< Vulkan entrypoint.
extern PFN_vkAllocateMemory              _vkAllocateMemory;               ///< Vulkan entrypoint.
extern PFN_vkBindBufferMemory            _vkBindBufferMemory;             ///< Vulkan entrypoint.
extern PFN_vkFreeMemory                  _vkFreeMemory;                   ///< Vulkan entrypoint.
extern PFN_vkMapMemory                   _vkMapMemory;                    ///< Vulkan entrypoint.
extern PFN_vkUnmapMemory                 _vkUnmapMemory;                  ///< Vulkan entrypoint.
extern PFN_vkFlushMappedMemoryRanges     _vkFlushMappedMemoryRanges;      ///< Vulkan entrypoint.
extern PFN_vkCmdResetQueryPool           _vkCmdResetQueryPool;            ///< Vulkan entrypoint.
extern PFN_vkCmdBeginQuery               _vkCmdBeginQuery;                ///< Vulkan entrypoint.
extern PFN_vkCmdEndQuery                 _vkCmdEndQuery;                  ///< Vulkan entrypoint.
extern PFN_vkCmdWriteTimestamp           _vkCmdWriteTimestamp;            ///< Vulkan entrypoint.
extern PFN_vkCmdCopyQueryPoolResults     _vkCmdCopyQueryPoolResults;      ///< Vulkan entrypoint.
extern PFN_vkGetQueryPoolResults         _vkGetQueryPoolResults;          ///< Vulkan entrypoint.
extern PFN_vkCmdCopyBuffer               _vkCmdCopyBuffer;                ///< Vulkan entrypoint.
extern PFN_vkDeviceWaitIdle              _vkDeviceWaitIdle;               ///< Vulkan entrypoint.

extern PFN_vkCreateGpaSessionAMD         _vkCreateGpaSessionAMD;          ///< Vulkan entrypoint.
extern PFN_vkDestroyGpaSessionAMD        _vkDestroyGpaSessionAMD;         ///< Vulkan entrypoint.
extern PFN_vkSetGpaDeviceClockModeAMD    _vkSetGpaDeviceClockModeAMD;     ///< Vulkan entrypoint.
extern PFN_vkCmdBeginGpaSessionAMD       _vkCmdBeginGpaSessionAMD;        ///< Vulkan entrypoint.
extern PFN_vkCmdEndGpaSessionAMD         _vkCmdEndGpaSessionAMD;          ///< Vulkan entrypoint.
extern PFN_vkCmdBeginGpaSampleAMD        _vkCmdBeginGpaSampleAMD;         ///< Vulkan entrypoint.
extern PFN_vkCmdEndGpaSampleAMD          _vkCmdEndGpaSampleAMD;           ///< Vulkan entrypoint.
extern PFN_vkGetGpaSessionStatusAMD      _vkGetGpaSessionStatusAMD;       ///< Vulkan entrypoint.
extern PFN_vkGetGpaSessionResultsAMD     _vkGetGpaSessionResultsAMD;      ///< Vulkan entrypoint.
extern PFN_vkResetGpaSessionAMD          _vkResetGpaSessionAMD;           ///< Vulkan entrypoint.
extern PFN_vkCmdCopyGpaSessionResultsAMD _vkCmdCopyGpaSessionResultsAMD;  ///< Vulkan entrypoint.

/// Macro to get a procedure address from a Vulkan instance.
#define VK_GET_INSTANCE_PROC_ADDR(func)                                                         \
    if (result)                                                                                 \
    {                                                                                           \
        result &= (nullptr != (_##func = (PFN_##func)_vkGetInstanceProcAddr(instance, #func))); \
        if (!result)                                                                            \
        {                                                                                       \
            GPA_LOG_ERROR("Unable to initialize Instance entry point " #func ".");              \
        }                                                                                       \
    }
/// Macro to get a procedure address from a Vulkan device.
#define VK_GET_DEVICE_PROC_ADDR(func)                                                       \
    if (result)                                                                             \
    {                                                                                       \
        result &= (nullptr != (_##func = (PFN_##func)_vkGetDeviceProcAddr(device, #func))); \
        if (!result)                                                                        \
        {                                                                                   \
            GPA_LOG_ERROR("Unable to initialize Device entry point " #func ".");            \
        }                                                                                   \
    }

namespace vk_utils
{
    /// Flag indicating the initialization status of vulkan entrypoints.
    extern bool are_entry_points_initialized;

    /// @brief Initialize the Vulkan entry points.
    ///
    /// @param [in] instance The Vulkan instance.
    /// @param [in] device The Vulkan device.
    ///
    /// @return True if all entrypoints cuold be initialized.
    bool InitializeVkEntryPoints(VkInstance instance, VkDevice device);
}  // namespace vk_utils

#endif  // GPU_PERF_API_VK_VK_ENTRYPOINTS_H_
