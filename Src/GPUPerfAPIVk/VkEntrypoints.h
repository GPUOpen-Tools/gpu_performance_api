//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Declares Vk Entrypoints
//==============================================================================

#ifndef _VK_ENTRYPOINTS_H_
#define _VK_ENTRYPOINTS_H_

#include <vulkan.h>
#include "vk_amd_gpa_interface.h"

// Instance entrypoints
extern PFN_vkGetPhysicalDeviceProperties _vkGetPhysicalDeviceProperties;
extern PFN_vkGetPhysicalDeviceQueueFamilyProperties _vkGetPhysicalDeviceQueueFamilyProperties;
extern PFN_vkGetPhysicalDeviceMemoryProperties _vkGetPhysicalDeviceMemoryProperties;
extern PFN_vkGetPhysicalDeviceFeatures _vkGetPhysicalDeviceFeatures;
extern PFN_vkGetPhysicalDeviceProperties2KHR _vkGetPhysicalDeviceProperties2KHR;
extern PFN_vkGetPhysicalDeviceFeatures2KHR _vkGetPhysicalDeviceFeatures2KHR;

// Device entrypoints
extern PFN_vkGetDeviceQueue _vkGetDeviceQueue;
extern PFN_vkCreateQueryPool _vkCreateQueryPool;
extern PFN_vkDestroyQueryPool _vkDestroyQueryPool;
extern PFN_vkCreateBuffer _vkCreateBuffer;
extern PFN_vkDestroyBuffer _vkDestroyBuffer;
extern PFN_vkGetBufferMemoryRequirements _vkGetBufferMemoryRequirements;
extern PFN_vkAllocateMemory _vkAllocateMemory;
extern PFN_vkBindBufferMemory _vkBindBufferMemory;
extern PFN_vkFreeMemory _vkFreeMemory;
extern PFN_vkMapMemory _vkMapMemory;
extern PFN_vkUnmapMemory _vkUnmapMemory;
extern PFN_vkFlushMappedMemoryRanges _vkFlushMappedMemoryRanges;
extern PFN_vkCmdResetQueryPool _vkCmdResetQueryPool;
extern PFN_vkCmdBeginQuery _vkCmdBeginQuery;
extern PFN_vkCmdEndQuery _vkCmdEndQuery;
extern PFN_vkCmdWriteTimestamp _vkCmdWriteTimestamp;
extern PFN_vkCmdCopyQueryPoolResults _vkCmdCopyQueryPoolResults;
extern PFN_vkGetQueryPoolResults _vkGetQueryPoolResults;
extern PFN_vkCmdCopyBuffer _vkCmdCopyBuffer;
extern PFN_vkDeviceWaitIdle _vkDeviceWaitIdle;

// vk_amd_gpa_interface device extension
extern PFN_vkCreateGpaSessionAMD _vkCreateGpaSessionAMD;
extern PFN_vkDestroyGpaSessionAMD _vkDestroyGpaSessionAMD;
extern PFN_vkSetGpaDeviceClockModeAMD _vkSetGpaDeviceClockModeAMD;
extern PFN_vkCmdBeginGpaSessionAMD _vkCmdBeginGpaSessionAMD;
extern PFN_vkCmdEndGpaSessionAMD _vkCmdEndGpaSessionAMD;
extern PFN_vkCmdBeginGpaSampleAMD _vkCmdBeginGpaSampleAMD;
extern PFN_vkCmdEndGpaSampleAMD _vkCmdEndGpaSampleAMD;
extern PFN_vkGetGpaSessionStatusAMD _vkGetGpaSessionStatusAMD;
extern PFN_vkGetGpaSessionResultsAMD _vkGetGpaSessionResultsAMD;
extern PFN_vkResetGpaSessionAMD _vkResetGpaSessionAMD;
extern PFN_vkCmdCopyGpaSessionResultsAMD _vkCmdCopyGpaSessionResultsAMD;

#define VK_GET_INSTANCE_PROC_ADDR(func) if (bResult) { bResult &= (nullptr != (_##func = (PFN_##func)_vkGetInstanceProcAddr(instance, #func ))); }
#define VK_GET_DEVICE_PROC_ADDR(func) if (bResult) { bResult &= (nullptr != (_##func = (PFN_##func)_vkGetDeviceProcAddr(device, #func ))); }

bool Initialize_Vk_Entrypoints(VkInstance instance, VkDevice device);

#endif // _VK_ENTRYPOINTS_H_
