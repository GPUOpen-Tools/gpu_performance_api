//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Declares Vk Entrypoints
//==============================================================================

#include "VkEntrypoints.h"
#include "GPACommonDefs.h"

#ifdef _LINUX
    #include <dlfcn.h>
#endif

// Instance entrypoints
PFN_vkGetPhysicalDeviceProperties _vkGetPhysicalDeviceProperties = nullptr;
PFN_vkGetPhysicalDeviceQueueFamilyProperties _vkGetPhysicalDeviceQueueFamilyProperties = nullptr;
PFN_vkGetPhysicalDeviceMemoryProperties _vkGetPhysicalDeviceMemoryProperties = nullptr;
PFN_vkGetPhysicalDeviceFeatures _vkGetPhysicalDeviceFeatures = nullptr;
PFN_vkGetBufferMemoryRequirements _vkGetBufferMemoryRequirements = nullptr;
PFN_vkGetPhysicalDeviceProperties2KHR _vkGetPhysicalDeviceProperties2KHR = nullptr;
PFN_vkGetPhysicalDeviceFeatures2KHR _vkGetPhysicalDeviceFeatures2KHR = nullptr;

// Device entrypoints
PFN_vkGetDeviceQueue _vkGetDeviceQueue = nullptr;
PFN_vkCreateQueryPool _vkCreateQueryPool = nullptr;
PFN_vkDestroyQueryPool _vkDestroyQueryPool = nullptr;
PFN_vkCreateBuffer _vkCreateBuffer = nullptr;
PFN_vkDestroyBuffer _vkDestroyBuffer = nullptr;
PFN_vkAllocateMemory _vkAllocateMemory = nullptr;
PFN_vkBindBufferMemory _vkBindBufferMemory = nullptr;
PFN_vkFreeMemory _vkFreeMemory = nullptr;
PFN_vkMapMemory _vkMapMemory = nullptr;
PFN_vkUnmapMemory _vkUnmapMemory = nullptr;
PFN_vkFlushMappedMemoryRanges _vkFlushMappedMemoryRanges = nullptr;
PFN_vkCmdResetQueryPool _vkCmdResetQueryPool = nullptr;
PFN_vkCmdBeginQuery _vkCmdBeginQuery = nullptr;
PFN_vkCmdEndQuery _vkCmdEndQuery = nullptr;
PFN_vkCmdWriteTimestamp _vkCmdWriteTimestamp = nullptr;
PFN_vkCmdCopyQueryPoolResults _vkCmdCopyQueryPoolResults = nullptr;
PFN_vkGetQueryPoolResults _vkGetQueryPoolResults = nullptr;
PFN_vkCmdCopyBuffer _vkCmdCopyBuffer = nullptr;
PFN_vkDeviceWaitIdle _vkDeviceWaitIdle = nullptr;

// vk_amd_gpa_interface device extension
PFN_vkCreateGpaSessionAMD _vkCreateGpaSessionAMD = nullptr;
PFN_vkDestroyGpaSessionAMD _vkDestroyGpaSessionAMD = nullptr;
PFN_vkSetGpaDeviceClockModeAMD _vkSetGpaDeviceClockModeAMD = nullptr;
PFN_vkCmdBeginGpaSessionAMD _vkCmdBeginGpaSessionAMD = nullptr;
PFN_vkCmdEndGpaSessionAMD _vkCmdEndGpaSessionAMD = nullptr;
PFN_vkCmdBeginGpaSampleAMD _vkCmdBeginGpaSampleAMD = nullptr;
PFN_vkCmdEndGpaSampleAMD _vkCmdEndGpaSampleAMD = nullptr;
PFN_vkGetGpaSessionStatusAMD _vkGetGpaSessionStatusAMD = nullptr;
PFN_vkGetGpaSessionResultsAMD _vkGetGpaSessionResultsAMD = nullptr;
PFN_vkResetGpaSessionAMD _vkResetGpaSessionAMD = nullptr;
PFN_vkCmdCopyGpaSessionResultsAMD _vkCmdCopyGpaSessionResultsAMD = nullptr;

bool VkUtils::s_isEntryPointsInitialized = false;

bool VkUtils::Initialize_Vk_Entrypoints(VkInstance instance, VkDevice device)
{
    if (!s_isEntryPointsInitialized)
    {
#ifdef _WIN32
        HMODULE vulkanModule = GetModuleHandle("Vulkan-1.dll");
#else
        void* vulkanModule = dlopen("libvulkan.so", RTLD_NOLOAD);

        if (nullptr == vulkanModule)
        {
            vulkanModule = dlopen("libvulkan.so", RTLD_NOW);
        }

        if (nullptr == vulkanModule)
        {
            vulkanModule = dlopen("libvulkan.so.1", RTLD_NOLOAD);
        }

        if (nullptr == vulkanModule)
        {
            vulkanModule = dlopen("libvulkan.so.1", RTLD_NOW);
        }

#endif

        if (nullptr == vulkanModule)
        {
            GPA_LogError("Failed to get handle to Vulkan Loader.");
            return false;
        }

#ifdef _WIN32
        PFN_vkGetInstanceProcAddr _vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(GetProcAddress(vulkanModule, "vkGetInstanceProcAddr"));
#else
        PFN_vkGetInstanceProcAddr _vkGetInstanceProcAddr = reinterpret_cast<PFN_vkGetInstanceProcAddr>(dlsym(vulkanModule, "vkGetInstanceProcAddr"));
#endif

        bool bResult = (nullptr != _vkGetInstanceProcAddr);

        if (bResult)
        {
            // Get instance entrypoints that should always be available from Vulkan
            VK_GET_INSTANCE_PROC_ADDR(vkGetPhysicalDeviceProperties);
            VK_GET_INSTANCE_PROC_ADDR(vkGetPhysicalDeviceQueueFamilyProperties);
            VK_GET_INSTANCE_PROC_ADDR(vkGetPhysicalDeviceMemoryProperties);
            VK_GET_INSTANCE_PROC_ADDR(vkGetPhysicalDeviceFeatures);
            VK_GET_INSTANCE_PROC_ADDR(vkGetBufferMemoryRequirements);
        }

        if (bResult)
        {
            // Get entrypoints that will only be available if the 'VK_KHR_get_physical_device_properties2' extension is enabled.
            VK_GET_INSTANCE_PROC_ADDR(vkGetPhysicalDeviceProperties2KHR);
            VK_GET_INSTANCE_PROC_ADDR(vkGetPhysicalDeviceFeatures2KHR);

            if (!bResult)
            {
                GPA_LogError("Required VK Extension 'VK_KHR_get_physical_device_properties2' is not enabled.");
                return false;
            }
        }

#ifdef _WIN32
        PFN_vkGetDeviceProcAddr _vkGetDeviceProcAddr = reinterpret_cast<PFN_vkGetDeviceProcAddr>(GetProcAddress(vulkanModule, "vkGetDeviceProcAddr"));
#else
        PFN_vkGetDeviceProcAddr _vkGetDeviceProcAddr = reinterpret_cast<PFN_vkGetDeviceProcAddr>(dlsym(vulkanModule, "vkGetDeviceProcAddr"));
#endif

        bResult &= (nullptr != _vkGetDeviceProcAddr);

        if (bResult)
        {
            // Get device entrypoints that should always be available from Vulkan
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

        if (bResult)
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

            if (!bResult)
            {
                GPA_LogError("Required VK Extension 'VK_AMD_gpa_interface' is not enabled.");
                return false;
            }

            s_isEntryPointsInitialized = true;

        }
    }

    return s_isEntryPointsInitialized;
}