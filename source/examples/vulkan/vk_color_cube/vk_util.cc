//==============================================================================
// Copyright (c) 2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Utility functions to handle vulkan loading, and initializing vulkan entry points
//==============================================================================

#include "vk_util.h"

#ifdef _LINUX
#include <dlfcn.h>
#define LOAD_SYMBOL dlsym
#else
#include <Windows.h>
#define LOAD_SYMBOL GetProcAddress
#endif

#define DEFINE_VK_FUNC(X) PFN_##X _##X = nullptr;
VK_MODULE_FUNC(DEFINE_VK_FUNC)
VK_INSTANCE_FUNC(DEFINE_VK_FUNC)
VK_PLATFORM_INSTANCE_FUNC(DEFINE_VK_FUNC)
VK_DEVICE_FUNC(DEFINE_VK_FUNC)
#undef DEFINE_VK_FUNC

bool AMDVulkanDemoVkUtils::kIsEntryPointsInitialized = false;

bool AMDVulkanDemoVkUtils::InitVulkanModule()
{
    if (!kIsEntryPointsInitialized)
    {
#ifdef _WIN32
        HMODULE vulkan_module = ::GetModuleHandleW(L"vulkan-1.dll");

        if (nullptr == vulkan_module)
        {
            vulkan_module = LoadLibrary(L"vulkan-1.dll");
        }
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
            return false;
        }

        bool success = true;

#define LOAD_VULKAN_FUNC_PTR(X)                                         \
    _##X = reinterpret_cast<PFN_##X>(LOAD_SYMBOL(vulkan_module, #X));   \
        if (nullptr == _##X)                                            \
        {                                                               \
            success &= false;                                           \
        }                                                               \

        VK_MODULE_FUNC(LOAD_VULKAN_FUNC_PTR);
#undef LOAD_VULKAN_FUNC_PTR

        kIsEntryPointsInitialized = success;
        return kIsEntryPointsInitialized;
    }

    return true;
}

bool AMDVulkanDemoVkUtils::InitInstanceFunctions(VkInstance vk_instance)
{
    if (nullptr != vk_instance && nullptr != _vkGetInstanceProcAddr)
    {
        bool success = true;

#define LOAD_VULKAN_INSTANCE_PTR(X)                                            \
    _##X = reinterpret_cast<PFN_##X>(_vkGetInstanceProcAddr(vk_instance, #X)); \
    if (nullptr == _##X)                                                       \
    {                                                                          \
        success &= false;                                                      \
    }

        VK_INSTANCE_FUNC(LOAD_VULKAN_INSTANCE_PTR);
        VK_PLATFORM_INSTANCE_FUNC(LOAD_VULKAN_INSTANCE_PTR);

#undef LOAD_VULKAN_INSTANCE_PTR
        return success;
    }

    return false;
}

bool AMDVulkanDemoVkUtils::InitDeviceFunctions(VkDevice vk_device)
{
    if (nullptr != vk_device && nullptr != _vkGetDeviceProcAddr)
    {
        bool success = true;

#define LOAD_VULKAN_DEVICE_PTR(X)                                           \
    _##X = reinterpret_cast<PFN_##X>(_vkGetDeviceProcAddr(vk_device, #X));  \
    if (nullptr == _##X)                                                    \
    {                                                                       \
        success &= false;                                                   \
    }

        VK_DEVICE_FUNC(LOAD_VULKAN_DEVICE_PTR);

#undef LOAD_VULKAN_DEVICE_PTR

        return success;
    }

    return false;
}