//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Vulkan utility functions implementation
//==============================================================================

#include "gpu_perf_api_vk/vk_utils.h"

#include <assert.h>

#include "gpu_perf_api_common/logging.h"

#include "gpu_perf_api_vk/vk_entry_points.h"

bool vk_utils::GetPhysicalDeviceGpaFeaturesAMD(VkPhysicalDevice physical_device, VkPhysicalDeviceGpaFeaturesAMD* gpa_features_amd)
{
    bool status = false;

    assert(nullptr != gpa_features_amd);

    if (nullptr != gpa_features_amd && vk_utils::are_entry_points_initialized && nullptr != _vkGetPhysicalDeviceFeatures2KHR)
    {
        *gpa_features_amd       = {};
        gpa_features_amd->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GPA_FEATURES_AMD;

        VkPhysicalDeviceFeatures2KHR features = {};
        features.sType                        = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2_KHR;
        features.pNext                        = gpa_features_amd;

        _vkGetPhysicalDeviceFeatures2KHR(physical_device, &features);
        status = true;
    }
    else
    {
        GPA_LOG_ERROR("Vulkan entrypoints are not initialized.");
    }

    return status;
}

bool vk_utils::GetPhysicalDeviceGpaPropertiesAMD(VkPhysicalDevice physical_device, VkPhysicalDeviceGpaPropertiesAMD* gpa_properties_amd)
{
    bool status = false;

    assert(nullptr != gpa_properties_amd);

    VkPhysicalDeviceGpaFeaturesAMD gpa_features_amd = {};

    if (nullptr != gpa_properties_amd && GetPhysicalDeviceGpaFeaturesAMD(physical_device, &gpa_features_amd))
    {
        if (VK_TRUE == gpa_features_amd.perfCounters)
        {
            // For now it is assumed that Vk MGPU support is exposed to the app
            // and the app always opens the device on the correct GPU.
            // In case where MGPU support hides the GPU from the app, then
            // we will need to use Vk MGPU extension (and possibly ADL util)
            // to get the correct HW info.
            *gpa_properties_amd       = {};
            gpa_properties_amd->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GPA_PROPERTIES_AMD;

            VkPhysicalDeviceProperties2KHR properties = {};
            properties.sType                          = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2_KHR;
            properties.pNext                          = gpa_properties_amd;

            _vkGetPhysicalDeviceProperties2KHR(physical_device, &properties);

            if (gpa_properties_amd->perfBlockCount > 0)
            {
                gpa_properties_amd->pPerfBlocks = new (std::nothrow) VkGpaPerfBlockPropertiesAMD[gpa_properties_amd->perfBlockCount];

                if (nullptr != gpa_properties_amd->pPerfBlocks)
                {
                    _vkGetPhysicalDeviceProperties2KHR(physical_device, &properties);
                    status = true;
                }
                else
                {
                    GPA_LOG_ERROR("Failed to allocate memory for PerfBlocks.");
                }
            }
            else
            {
                GPA_LOG_ERROR("Active physical device does not expose any perf counter blocks.");
            }
        }
        else
        {
            GPA_LOG_ERROR("Active physical device does not support performance counters.");
        }
    }
    else
    {
        GPA_LOG_ERROR("Failed to get physical device features.");
    }

    return status;
}

void vk_utils::ReleasePhysicalDeviceGpaPropertiesAMD(VkPhysicalDeviceGpaPropertiesAMD* gpa_properties_amd)
{
    if (nullptr != gpa_properties_amd)
    {
        if (nullptr != gpa_properties_amd->pPerfBlocks)
        {
            delete[] gpa_properties_amd->pPerfBlocks;
            gpa_properties_amd->pPerfBlocks    = nullptr;
            gpa_properties_amd->perfBlockCount = 0;
        }
    }
}

#ifdef _DEBUG
void vk_utils::DebugReportQueueFamilyTimestampBits(VkPhysicalDevice vk_physical_device)
{
    if (vk_utils::are_entry_points_initialized)
    {
        uint32_t queue_family_count = 0;
        _vkGetPhysicalDeviceQueueFamilyProperties(vk_physical_device, &queue_family_count, nullptr);

        if (queue_family_count != 0)
        {
            VkQueueFamilyProperties* queue_family_properties = new (std::nothrow) VkQueueFamilyProperties[queue_family_count];

            if (nullptr == queue_family_properties)
            {
                GPA_LOG_ERROR("Failed to allocate memory for QueueFamilyProperties.");
            }
            else
            {
                _vkGetPhysicalDeviceQueueFamilyProperties(vk_physical_device, &queue_family_count, queue_family_properties);

                for (unsigned int i = 0; i < queue_family_count; ++i)
                {
                    if (queue_family_properties[i].timestampValidBits == 0)
                    {
                        GPA_LOG_ERROR("QueueFamily Does NOT have valid timestamp bits.");
                        GPA_LOG_DEBUG_MESSAGE("QueueFamily %u does not have any valid timestamp bits; cannot support profiling.", i);
                    }
                    else
                    {
                        GPA_LOG_DEBUG_MESSAGE(
                            "QueueFamily %u has %u valid timestamp bits; it will support profiling.", i, queue_family_properties[i].timestampValidBits);
                    }
                }

                delete[] queue_family_properties;
            }
        }
        else
        {
            GPA_LOG_ERROR("Device does not support any queue families; profiling cannot be supported.");
        }
    }
    else
    {
        GPA_LOG_ERROR("Vulkan entrypoints are not initialized.");
    }
}
#endif  // _DEBUG

bool vk_utils::IsDeviceSupportedForProfiling(VkPhysicalDevice vk_physical_device)
{
    bool is_supported = false;

    if (vk_utils::are_entry_points_initialized)
    {
        uint32_t queue_family_count = 0;
        _vkGetPhysicalDeviceQueueFamilyProperties(vk_physical_device, &queue_family_count, nullptr);

        if (queue_family_count != 0)
        {
            VkQueueFamilyProperties* queue_family_propert9es = new (std::nothrow) VkQueueFamilyProperties[queue_family_count];

            if (queue_family_propert9es == nullptr)
            {
                GPA_LOG_ERROR("Failed to allocate memory for QueueFamilyProperties.");
            }
            else
            {
                _vkGetPhysicalDeviceQueueFamilyProperties(vk_physical_device, &queue_family_count, queue_family_propert9es);

                if (queue_family_propert9es[0].timestampValidBits == 0)
                {
                    GPA_LOG_ERROR("QueueFamily 0 does not have any valid timestamp bits; cannot be supported.");
                }
                else
                {
                    VkPhysicalDeviceGpaFeaturesAMD features_amd = {};
                    features_amd.sType                          = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GPA_FEATURES_AMD;

                    VkPhysicalDeviceFeatures2KHR features = {};
                    features.sType                        = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2_KHR;
                    features.pNext                        = &features_amd;

                    _vkGetPhysicalDeviceFeatures2KHR(vk_physical_device, &features);

                    if (features_amd.perfCounters == VK_TRUE)
                    {
                        is_supported = true;
                    }
                }

                delete[] queue_family_propert9es;
            }
        }
        else
        {
            GPA_LOG_ERROR("Device does not support any queue families; cannot be supported.");
        }
    }
    else
    {
        GPA_LOG_ERROR("Vulkan entrypoints are not initialized.");
    }

    return is_supported;
}

bool vk_utils::GetTimestampFrequency(VkPhysicalDevice vk_physical_device, GpaUInt64& timestamp_frequency)
{
    bool success = false;

    if (are_entry_points_initialized)
    {
        VkPhysicalDeviceProperties properties;
        _vkGetPhysicalDeviceProperties(vk_physical_device, &properties);

        // Vulkan's timestamp_period is expressed in nanoseconds per clock tick, convert to frequency in seconds.
        float timestamp_period = properties.limits.timestampPeriod;
        timestamp_frequency    = static_cast<GpaUInt64>(1000000000.0f / (timestamp_period));

        success = true;
    }
    else
    {
        GPA_LOG_ERROR("Vulkan entrypoints are not initialized.");
    }

    return success;
}