//==============================================================================
// Copyright (c) 2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Utility functions to handle vulkan loading, and initializing vulkan entry points
//==============================================================================

#ifndef _VK_UTIL_H_
#define _VK_UTIL_H_

#ifdef ANDROID
#define VK_USE_PLATFORM_ANDROID_KHR
#include <android/asset_manager.h>
#else

#ifdef _WIN32
// Tell the linker that this is a windowed app, not a console app;
// defining this in code allows for flexibility with other operating systems.
#pragma comment(linker, "/subsystem:windows")
#define VK_USE_PLATFORM_WIN32_KHR
#endif  // _WIN32

#ifdef __linux__
#define VK_USE_PLATFORM_XCB_KHR
#endif  // __linux__

#endif

#include <vulkan/vulkan.h>

#define VK_MODULE_FUNC(X)                       \
    X(vkEnumerateInstanceExtensionProperties)   \
    X(vkEnumerateInstanceLayerProperties)       \
    X(vkCreateInstance)                         \
    X(vkGetDeviceProcAddr)                      \
    X(vkGetInstanceProcAddr)                    \

// Instance functions
#define VK_INSTANCE_FUNC(X)                     \
    X(vkEnumeratePhysicalDevices)               \
    X(vkGetPhysicalDeviceProperties)            \
    X(vkGetPhysicalDeviceFeatures)              \
    X(vkGetPhysicalDeviceMemoryProperties)      \
    X(vkGetPhysicalDeviceQueueFamilyProperties) \
    X(vkGetPhysicalDeviceSurfaceSupportKHR)     \
    X(vkEnumerateDeviceExtensionProperties)     \
    X(vkCreateDevice)                           \
    X(vkGetPhysicalDeviceSurfaceFormatsKHR)     \
    X(vkGetPhysicalDeviceSurfacePresentModesKHR)\
    X(vkGetPhysicalDeviceSurfaceCapabilitiesKHR)\
    X(vkDestroySurfaceKHR)                      \
    X(vkDestroyDebugReportCallbackEXT)          \
    X(vkDestroyInstance)                        \

#if defined(VK_USE_PLATFORM_WIN32_KHR)
#define VK_PLATFORM_INSTANCE_FUNC(X)            \
    X(vkCreateWin32SurfaceKHR)
#elif defined(VK_USE_PLATFORM_XCB_KHR)
#define VK_PLATFORM_INSTANCE_FUNC(X)            \
    X(vkCreateXcbSurfaceKHR)
#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
#define VK_PLATFORM_INSTANCE_FUNC(X)            \
    X(vkCreateAndroidSurfaceKHR)
#endif


// Device entrypoints
#define VK_DEVICE_FUNC(X)       \
    X(vkGetDeviceQueue)         \
    X(vkCreateShaderModule)     \
    X(vkCreateSwapchainKHR)     \
    X(vkGetSwapchainImagesKHR)  \
    X(vkCreateImageView)        \
    X(vkCreateRenderPass)       \
    X(vkCreateFramebuffer)      \
    X(vkCreatePipelineLayout)   \
    X(vkCreateGraphicsPipelines)\
    X(vkCreateCommandPool)      \
    X(vkCreateSemaphore)        \
    X(vkAllocateCommandBuffers) \
    X(vkBeginCommandBuffer)     \
    X(vkCmdBeginRenderPass)     \
    X(vkCmdSetViewport)         \
    X(vkCmdSetScissor)          \
    X(vkCmdBindPipeline)        \
    X(vkCmdDraw)                \
    X(vkCmdEndRenderPass)       \
    X(vkEndCommandBuffer)       \
    X(vkAcquireNextImageKHR)    \
    X(vkQueueSubmit)            \
    X(vkQueuePresentKHR)        \
    X(vkDeviceWaitIdle)         \
    X(vkDestroySemaphore)       \
    X(vkDestroyCommandPool)     \
    X(vkDestroyPipelineLayout)  \
    X(vkDestroyShaderModule)    \
    X(vkDestroyPipeline)        \
    X(vkDestroyRenderPass)      \
    X(vkDestroyFramebuffer)     \
    X(vkDestroyImageView)       \
    X(vkDestroySwapchainKHR)    \
    X(vkDestroyDevice)          \

#define DECLARE_VK_FUNC(X) extern PFN_##X _##X;

VK_MODULE_FUNC(DECLARE_VK_FUNC)
VK_INSTANCE_FUNC(DECLARE_VK_FUNC)
VK_PLATFORM_INSTANCE_FUNC(DECLARE_VK_FUNC)
VK_DEVICE_FUNC(DECLARE_VK_FUNC)

#undef DECLARE_VK_FUNC

namespace AMDVulkanDemoVkUtils
{
    /// Initializes the Vulkan Module
    /// \return true upon success otherwise false
    bool InitVulkanModule();

    /// Initializes the vulkan instance function
    /// \param[in] vk_instance vulkan instance
    /// \return true upon success otherwise false
    bool InitInstanceFunctions(VkInstance vk_instance);

    /// Initializes the vulkan device functions
    /// \param[in] vk_device vulkan device
    /// \return true upon success otherwise false
    bool InitDeviceFunctions(VkDevice vk_device);

    extern bool kIsEntryPointsInitialized;  ///< flag indicating the initialization status of vulkan entry points

};  // namespace AMDVulkanDemoVkUtils

#endif  // _VK_UTIL_H_
