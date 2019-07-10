//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Vulkan utility functions implementation
//==============================================================================

#include <assert.h>

#include "VkUtils.h"
#include "VkEntrypoints.h"
#include "Logging.h"

bool VkUtils::GetPhysicalDeviceGpaFeaturesAMD(VkPhysicalDevice vkPhysicalDevice, VkPhysicalDeviceGpaFeaturesAMD* pGpaFeaturesAMD)
{
    bool bStatus = false;

    assert(nullptr != pGpaFeaturesAMD);

    if (nullptr != pGpaFeaturesAMD && VkUtils::s_isEntryPointsInitialized && nullptr != _vkGetPhysicalDeviceFeatures2KHR)
    {
        *pGpaFeaturesAMD       = {};
        pGpaFeaturesAMD->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GPA_FEATURES_AMD;

        VkPhysicalDeviceFeatures2KHR features = {};
        features.sType                        = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2_KHR;
        features.pNext                        = pGpaFeaturesAMD;

        _vkGetPhysicalDeviceFeatures2KHR(vkPhysicalDevice, &features);
        bStatus = true;
    }
    else
    {
        GPA_LogError("Vulkan entrypoints are not initialized.");
    }

    return bStatus;
}

bool VkUtils::GetPhysicalDeviceGpaPropertiesAMD(VkPhysicalDevice vkPhysicalDevice, VkPhysicalDeviceGpaPropertiesAMD* pGpaPropertiesAMD)
{
    bool bStatus = false;

    assert(nullptr != pGpaPropertiesAMD);

    VkPhysicalDeviceGpaFeaturesAMD gpaFeaturesAMD = {};

    if (nullptr != pGpaPropertiesAMD && GetPhysicalDeviceGpaFeaturesAMD(vkPhysicalDevice, &gpaFeaturesAMD))
    {
        if (VK_TRUE == gpaFeaturesAMD.perfCounters)
        {
            // For now it is assumed that Vk MGPU support is exposed to the app
            // and the app always opens the device on the correct GPU.
            // In case where MGPU support hides the GPU from the app, then
            // we will need to use Vk MGPU extension (and possibly ADL util)
            // to get the correct HW info
            *pGpaPropertiesAMD       = {};
            pGpaPropertiesAMD->sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GPA_PROPERTIES_AMD;

            VkPhysicalDeviceProperties2KHR properties = {};
            properties.sType                          = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2_KHR;
            properties.pNext                          = pGpaPropertiesAMD;

            _vkGetPhysicalDeviceProperties2KHR(vkPhysicalDevice, &properties);

            if (pGpaPropertiesAMD->perfBlockCount > 0)
            {
                pGpaPropertiesAMD->pPerfBlocks = new (std::nothrow) VkGpaPerfBlockPropertiesAMD[pGpaPropertiesAMD->perfBlockCount];

                if (nullptr != pGpaPropertiesAMD->pPerfBlocks)
                {
                    _vkGetPhysicalDeviceProperties2KHR(vkPhysicalDevice, &properties);
                    bStatus = true;
                }
                else
                {
                    GPA_LogError("Failed to allocate memory for PerfBlocks.");
                }
            }
            else
            {
                GPA_LogError("Active physical device does not expose any perf counter blocks.");
            }
        }
        else
        {
            GPA_LogError("Active physical device does not support performance counters.");
        }
    }
    else
    {
        GPA_LogError("Failed to get physical device features.");
    }

    return bStatus;
}

void VkUtils::ReleasePhysicalDeviceGpaPropertiesAMD(VkPhysicalDeviceGpaPropertiesAMD* pGpaPropertiesAMD)
{
    if (nullptr != pGpaPropertiesAMD)
    {
        if (nullptr != pGpaPropertiesAMD->pPerfBlocks)
        {
            delete[] pGpaPropertiesAMD->pPerfBlocks;
            pGpaPropertiesAMD->pPerfBlocks    = nullptr;
            pGpaPropertiesAMD->perfBlockCount = 0;
        }
    }
}

#ifdef _DEBUG
void VkUtils::DebugReportQueueFamilyTimestampBits(VkPhysicalDevice vkPhysicalDevice)
{
    if (VkUtils::s_isEntryPointsInitialized)
    {
        uint32_t queueFamilyCount = 0;
        _vkGetPhysicalDeviceQueueFamilyProperties(vkPhysicalDevice, &queueFamilyCount, nullptr);

        if (queueFamilyCount != 0)
        {
            VkQueueFamilyProperties* pQueueFamilyProperties = new (std::nothrow) VkQueueFamilyProperties[queueFamilyCount];

            if (nullptr == pQueueFamilyProperties)
            {
                GPA_LogError("Failed to allocate memory for QueueFamilyProperties.");
            }
            else
            {
                _vkGetPhysicalDeviceQueueFamilyProperties(vkPhysicalDevice, &queueFamilyCount, pQueueFamilyProperties);

                for (unsigned int i = 0; i < queueFamilyCount; ++i)
                {
                    if (pQueueFamilyProperties[i].timestampValidBits == 0)
                    {
                        GPA_LogError("QueueFamily Does NOT have valid timestamp bits.");
                        GPA_LogDebugMessage("QueueFamily %u does not have any valid timestamp bits; cannot support profiling.", i);
                    }
                    else
                    {
                        GPA_LogDebugMessage(
                            "QueueFamily %u has %u valid timestamp bits; it will support profiling.", i, pQueueFamilyProperties[i].timestampValidBits);
                    }
                }

                delete[] pQueueFamilyProperties;
            }
        }
        else
        {
            GPA_LogError("Device does not support any queue families; profiling cannot be supported.");
        }
    }
    else
    {
        GPA_LogError("Vulkan entrypoints are not initialized.");
    }
}
#endif  //_DEBUG

bool VkUtils::IsDeviceSupportedForProfiling(VkPhysicalDevice vkPhysicalDevice)
{
    bool isSupported = false;

    if (VkUtils::s_isEntryPointsInitialized)
    {
        uint32_t queueFamilyCount = 0;
        _vkGetPhysicalDeviceQueueFamilyProperties(vkPhysicalDevice, &queueFamilyCount, nullptr);

        if (queueFamilyCount != 0)
        {
            VkQueueFamilyProperties* pQueueFamilyProperties = new (std::nothrow) VkQueueFamilyProperties[queueFamilyCount];

            if (pQueueFamilyProperties == nullptr)
            {
                GPA_LogError("Failed to allocate memory for QueueFamilyProperties.");
            }
            else
            {
                _vkGetPhysicalDeviceQueueFamilyProperties(vkPhysicalDevice, &queueFamilyCount, pQueueFamilyProperties);

                if (pQueueFamilyProperties[0].timestampValidBits == 0)
                {
                    GPA_LogError("QueueFamily 0 does not have any valid timestamp bits; cannot be supported.");
                }
                else
                {
                    VkPhysicalDeviceGpaFeaturesAMD featuresAMD = {};
                    featuresAMD.sType                          = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GPA_FEATURES_AMD;

                    VkPhysicalDeviceFeatures2KHR features = {};
                    features.sType                        = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2_KHR;
                    features.pNext                        = &featuresAMD;

                    _vkGetPhysicalDeviceFeatures2KHR(vkPhysicalDevice, &features);

                    if (featuresAMD.perfCounters == VK_TRUE)
                    {
                        isSupported = true;
                    }
                }

                delete[] pQueueFamilyProperties;
            }
        }
        else
        {
            GPA_LogError("Device does not support any queue families; cannot be supported.");
        }
    }
    else
    {
        GPA_LogError("Vulkan entrypoints are not initialized.");
    }

    return isSupported;
}

bool VkUtils::GetTimestampFrequency(VkPhysicalDevice vkPhysicalDevice, gpa_uint64& timestampFrequency)
{
    bool success = false;

    if (s_isEntryPointsInitialized)
    {
        VkPhysicalDeviceProperties properties;
        _vkGetPhysicalDeviceProperties(vkPhysicalDevice, &properties);

        // Vulkan's timestampPeriod is expressed in nanoseconds per clock tick, convert to frequency in seconds
        float timestampPeriod = properties.limits.timestampPeriod;
        timestampFrequency    = static_cast<gpa_uint64>(1000000000.0f / (timestampPeriod));

        success = true;
    }
    else
    {
        GPA_LogError("Vulkan entrypoints are not initialized.");
    }

    return success;
}
