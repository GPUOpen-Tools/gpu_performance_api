//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Declares Vk Entrypoints
//==============================================================================

#include "gpu_perf_api_vk/vk_entry_points.h"

#include "gpu_perf_api_common/gpa_common_defs.h"

#ifdef _LINUX
#include <dlfcn.h>
#endif

PFN_vkGetPhysicalDeviceProperties            _vkGetPhysicalDeviceProperties            = nullptr;
PFN_vkGetPhysicalDeviceQueueFamilyProperties _vkGetPhysicalDeviceQueueFamilyProperties = nullptr;
PFN_vkGetPhysicalDeviceMemoryProperties      _vkGetPhysicalDeviceMemoryProperties      = nullptr;
PFN_vkGetPhysicalDeviceFeatures              _vkGetPhysicalDeviceFeatures              = nullptr;
PFN_vkGetBufferMemoryRequirements            _vkGetBufferMemoryRequirements            = nullptr;
PFN_vkGetPhysicalDeviceProperties2KHR        _vkGetPhysicalDeviceProperties2KHR        = nullptr;
PFN_vkGetPhysicalDeviceFeatures2KHR          _vkGetPhysicalDeviceFeatures2KHR          = nullptr;

PFN_vkGetDeviceQueue          _vkGetDeviceQueue          = nullptr;
PFN_vkCreateQueryPool         _vkCreateQueryPool         = nullptr;
PFN_vkDestroyQueryPool        _vkDestroyQueryPool        = nullptr;
PFN_vkCreateBuffer            _vkCreateBuffer            = nullptr;
PFN_vkDestroyBuffer           _vkDestroyBuffer           = nullptr;
PFN_vkAllocateMemory          _vkAllocateMemory          = nullptr;
PFN_vkBindBufferMemory        _vkBindBufferMemory        = nullptr;
PFN_vkFreeMemory              _vkFreeMemory              = nullptr;
PFN_vkMapMemory               _vkMapMemory               = nullptr;
PFN_vkUnmapMemory             _vkUnmapMemory             = nullptr;
PFN_vkFlushMappedMemoryRanges _vkFlushMappedMemoryRanges = nullptr;
PFN_vkCmdResetQueryPool       _vkCmdResetQueryPool       = nullptr;
PFN_vkCmdBeginQuery           _vkCmdBeginQuery           = nullptr;
PFN_vkCmdEndQuery             _vkCmdEndQuery             = nullptr;
PFN_vkCmdWriteTimestamp       _vkCmdWriteTimestamp       = nullptr;
PFN_vkCmdCopyQueryPoolResults _vkCmdCopyQueryPoolResults = nullptr;
PFN_vkGetQueryPoolResults     _vkGetQueryPoolResults     = nullptr;
PFN_vkCmdCopyBuffer           _vkCmdCopyBuffer           = nullptr;
PFN_vkDeviceWaitIdle          _vkDeviceWaitIdle          = nullptr;

PFN_vkCreateGpaSessionAMD         _vkCreateGpaSessionAMD         = nullptr;
PFN_vkDestroyGpaSessionAMD        _vkDestroyGpaSessionAMD        = nullptr;
PFN_vkSetGpaDeviceClockModeAMD    _vkSetGpaDeviceClockModeAMD    = nullptr;
PFN_vkCmdBeginGpaSessionAMD       _vkCmdBeginGpaSessionAMD       = nullptr;
PFN_vkCmdEndGpaSessionAMD         _vkCmdEndGpaSessionAMD         = nullptr;
PFN_vkCmdBeginGpaSampleAMD        _vkCmdBeginGpaSampleAMD        = nullptr;
PFN_vkCmdEndGpaSampleAMD          _vkCmdEndGpaSampleAMD          = nullptr;
PFN_vkGetGpaSessionStatusAMD      _vkGetGpaSessionStatusAMD      = nullptr;
PFN_vkGetGpaSessionResultsAMD     _vkGetGpaSessionResultsAMD     = nullptr;
PFN_vkResetGpaSessionAMD          _vkResetGpaSessionAMD          = nullptr;
PFN_vkCmdCopyGpaSessionResultsAMD _vkCmdCopyGpaSessionResultsAMD = nullptr;

bool vk_utils::are_entry_points_initialized = false;

bool vk_utils::InitializeVkEntryPointsFromLayer(VkInstance instance, VkDevice device, 
        GpaVkApiEntrypoints_v1* pVkEntry
    )
{
    if (!are_entry_points_initialized) 
    {
        _vkGetPhysicalDeviceProperties            = pVkEntry->vkGetPhysicalDeviceProperties;
        _vkGetPhysicalDeviceQueueFamilyProperties = pVkEntry->vkGetPhysicalDeviceQueueFamilyProperties;
        _vkGetPhysicalDeviceMemoryProperties = pVkEntry->vkGetPhysicalDeviceMemoryProperties;
        _vkGetPhysicalDeviceFeatures = pVkEntry->vkGetPhysicalDeviceFeatures;
        _vkGetBufferMemoryRequirements = pVkEntry->vkGetBufferMemoryRequirements;
        _vkGetPhysicalDeviceProperties2KHR = pVkEntry->vkGetPhysicalDeviceProperties2KHR;
        _vkGetPhysicalDeviceFeatures2KHR = pVkEntry->vkGetPhysicalDeviceFeatures2KHR;

        _vkGetDeviceQueue = pVkEntry->vkGetDeviceQueue;
        _vkCreateQueryPool = pVkEntry->vkCreateQueryPool;
        _vkDestroyQueryPool = pVkEntry->vkDestroyQueryPool;
        _vkCreateBuffer = pVkEntry->vkCreateBuffer;
        _vkDestroyBuffer = pVkEntry->vkDestroyBuffer;


        _vkAllocateMemory = pVkEntry->vkAllocateMemory;
        _vkBindBufferMemory = pVkEntry->vkBindBufferMemory;
        _vkFreeMemory = pVkEntry->vkFreeMemory;
        _vkMapMemory = pVkEntry->vkMapMemory;
        _vkUnmapMemory = pVkEntry->vkUnmapMemory;
        _vkFlushMappedMemoryRanges = pVkEntry->vkFlushMappedMemoryRanges;
        _vkCmdResetQueryPool = pVkEntry->vkCmdResetQueryPool;
        _vkCmdBeginQuery = pVkEntry->vkCmdBeginQuery;
        _vkCmdEndQuery = pVkEntry->vkCmdEndQuery;
        _vkCmdWriteTimestamp = pVkEntry->vkCmdWriteTimestamp;
        _vkCmdCopyQueryPoolResults = pVkEntry->vkCmdCopyQueryPoolResults;
        _vkGetQueryPoolResults = pVkEntry->vkGetQueryPoolResults;
        _vkCmdCopyBuffer = pVkEntry->vkCmdCopyBuffer;
        _vkDeviceWaitIdle = pVkEntry->vkDeviceWaitIdle;

        _vkCreateGpaSessionAMD = reinterpret_cast<PFN_vkCreateGpaSessionAMD>(pVkEntry->vkCreateGpaSessionAMD);
        _vkDestroyGpaSessionAMD = reinterpret_cast<PFN_vkDestroyGpaSessionAMD>(pVkEntry->vkDestroyGpaSessionAMD);
        _vkSetGpaDeviceClockModeAMD = reinterpret_cast<PFN_vkSetGpaDeviceClockModeAMD>(pVkEntry->vkSetGpaDeviceClockModeAMD);
        _vkCmdBeginGpaSessionAMD = reinterpret_cast<PFN_vkCmdBeginGpaSessionAMD>(pVkEntry->vkCmdBeginGpaSessionAMD);
        _vkCmdEndGpaSessionAMD = reinterpret_cast<PFN_vkCmdEndGpaSessionAMD>(pVkEntry->vkCmdEndGpaSessionAMD);
        _vkCmdBeginGpaSampleAMD = reinterpret_cast<PFN_vkCmdBeginGpaSampleAMD>(pVkEntry->vkCmdBeginGpaSampleAMD);
        _vkCmdEndGpaSampleAMD = reinterpret_cast<PFN_vkCmdEndGpaSampleAMD>(pVkEntry->vkCmdEndGpaSampleAMD);

        _vkGetGpaSessionStatusAMD = reinterpret_cast<PFN_vkGetGpaSessionStatusAMD>(pVkEntry->vkGetGpaSessionStatusAMD);
        _vkGetGpaSessionResultsAMD = reinterpret_cast<PFN_vkGetGpaSessionResultsAMD>(pVkEntry->vkGetGpaSessionResultsAMD);

        _vkResetGpaSessionAMD = reinterpret_cast<PFN_vkResetGpaSessionAMD>(pVkEntry->vkResetGpaSessionAMD);
        _vkCmdCopyGpaSessionResultsAMD = reinterpret_cast<PFN_vkCmdCopyGpaSessionResultsAMD>(pVkEntry->vkCmdCopyGpaSessionResultsAMD);

        are_entry_points_initialized = true;
    }   

    return true;
}

// this interface to be used by APP only
bool vk_utils::InitializeVkEntryPoints(VkInstance instance, VkDevice device)
{
    if (!are_entry_points_initialized)
    {
#ifdef _WIN32
        HMODULE vulkan_module = ::GetModuleHandleW(L"Vulkan-1.dll");
#else

        void* vulkan_module = dlopen("libvulkan.so", RTLD_NOLOAD);

        if (nullptr == vulkan_module)
        {
            vulkan_module = dlopen("libvulkan.so", RTLD_NOW);
        }

        if (nullptr == vulkan_module)
        {
            vulkan_module = dlopen("libvulkan.so.1", RTLD_NOLOAD);
        }

        if (nullptr == vulkan_module)
        {
            vulkan_module = dlopen("libvulkan.so.1", RTLD_NOW);
        }

#endif

        if (nullptr == vulkan_module)
        {
            GPA_LOG_ERROR("Failed to get handle to Vulkan Loader.");
            return false;
        }

#ifdef _WIN32
        PFN_vkGetInstanceProcAddr _vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(GetProcAddress(vulkan_module, "vkGetInstanceProcAddr"));
#else
        PFN_vkGetInstanceProcAddr _vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(dlsym(vulkan_module, "vkGetInstanceProcAddr"));
#endif

        bool result = (nullptr != _vkGetInstanceProcAddr);

        if (result)
        {
            // Get instance entrypoints that should always be available from Vulkan.
            VK_GET_INSTANCE_PROC_ADDR(vkGetPhysicalDeviceProperties);
            VK_GET_INSTANCE_PROC_ADDR(vkGetPhysicalDeviceQueueFamilyProperties);
            VK_GET_INSTANCE_PROC_ADDR(vkGetPhysicalDeviceMemoryProperties);
            VK_GET_INSTANCE_PROC_ADDR(vkGetPhysicalDeviceFeatures);
            VK_GET_INSTANCE_PROC_ADDR(vkGetBufferMemoryRequirements);            
        }

        if (result)
        {
            // Get entrypoints that will only be available if the 'VK_KHR_get_physical_device_properties2' extension is enabled.
            VK_GET_INSTANCE_PROC_ADDR(vkGetPhysicalDeviceProperties2KHR);
            VK_GET_INSTANCE_PROC_ADDR(vkGetPhysicalDeviceFeatures2KHR);

            if (!result)
            {
                GPA_LOG_ERROR("Required VK Extension 'VK_KHR_get_physical_device_properties2' is not enabled.");
                return false;
            }
        }

#ifdef _WIN32
        PFN_vkGetDeviceProcAddr _vkGetDeviceProcAddr = reinterpret_cast<PFN_vkGetDeviceProcAddr>(GetProcAddress(vulkan_module, "vkGetDeviceProcAddr"));
#else
        PFN_vkGetDeviceProcAddr   _vkGetDeviceProcAddr   = reinterpret_cast<PFN_vkGetDeviceProcAddr>(dlsym(vulkan_module, "vkGetDeviceProcAddr"));
#endif

        result &= (nullptr != _vkGetDeviceProcAddr);

        if (result)
        {
            // Get device entrypoints that should always be available from Vulkan.
            VK_GET_DEVICE_PROC_ADDR(vkGetDeviceQueue);
            VK_GET_DEVICE_PROC_ADDR(vkCreateQueryPool);
            VK_GET_DEVICE_PROC_ADDR(vkDestroyQueryPool);
            VK_GET_DEVICE_PROC_ADDR(vkCreateBuffer);
            VK_GET_DEVICE_PROC_ADDR(vkDestroyBuffer);
            VK_GET_DEVICE_PROC_ADDR(vkAllocateMemory);
            VK_GET_DEVICE_PROC_ADDR(vkBindBufferMemory);
            VK_GET_DEVICE_PROC_ADDR(vkFreeMemory);
            VK_GET_DEVICE_PROC_ADDR(vkMapMemory);
            VK_GET_DEVICE_PROC_ADDR(vkUnmapMemory);
            VK_GET_DEVICE_PROC_ADDR(vkFlushMappedMemoryRanges);
            VK_GET_DEVICE_PROC_ADDR(vkCmdResetQueryPool);
            VK_GET_DEVICE_PROC_ADDR(vkCmdBeginQuery);
            VK_GET_DEVICE_PROC_ADDR(vkCmdEndQuery);
            VK_GET_DEVICE_PROC_ADDR(vkCmdWriteTimestamp);
            VK_GET_DEVICE_PROC_ADDR(vkCmdCopyQueryPoolResults);
            VK_GET_DEVICE_PROC_ADDR(vkGetQueryPoolResults);
            VK_GET_DEVICE_PROC_ADDR(vkCmdCopyBuffer);
            VK_GET_DEVICE_PROC_ADDR(vkDeviceWaitIdle);
        }

        if (result)
        {
            // Get entrypoints that will only be available if the 'VK_AMD_gpa_interface' extension is enabled.
            VK_GET_DEVICE_PROC_ADDR(vkCreateGpaSessionAMD);
            VK_GET_DEVICE_PROC_ADDR(vkDestroyGpaSessionAMD);
            VK_GET_DEVICE_PROC_ADDR(vkSetGpaDeviceClockModeAMD);
            VK_GET_DEVICE_PROC_ADDR(vkCmdBeginGpaSessionAMD);
            VK_GET_DEVICE_PROC_ADDR(vkCmdEndGpaSessionAMD);
            VK_GET_DEVICE_PROC_ADDR(vkCmdBeginGpaSampleAMD);
            VK_GET_DEVICE_PROC_ADDR(vkCmdEndGpaSampleAMD);
            VK_GET_DEVICE_PROC_ADDR(vkGetGpaSessionStatusAMD);
            VK_GET_DEVICE_PROC_ADDR(vkGetGpaSessionResultsAMD);
            VK_GET_DEVICE_PROC_ADDR(vkResetGpaSessionAMD);
            VK_GET_DEVICE_PROC_ADDR(vkCmdCopyGpaSessionResultsAMD);

            if (!result)
            {
                GPA_LOG_ERROR("Required VK Extension 'VK_AMD_gpa_interface' is not enabled.");
                return false;
            }

            are_entry_points_initialized = true;
        }
    }

    return are_entry_points_initialized;
}