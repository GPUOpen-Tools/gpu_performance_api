//==============================================================================
// Copyright (c) 2015-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA Vk API implementation
//==============================================================================

#include "VkGPAImplementor.h"

#include <assert.h>
#include "VkIncludes.h"
#include "GPACounterGenerator.h"
#include "IGPACommandList.h"
#include "VkEntrypoints.h"
#include "VkGPAContext.h"
#include "Logging.h"
#include "VkUtils.h"
#include "DeviceInfoUtils.h"
#include "GPUPerfAPI-VK.h"

IGPAImplementor* s_pGpaImp = VkGPAImplementor::Instance();

GPA_API_Type VkGPAImplementor::GetAPIType() const
{
    return GPA_API_VULKAN;
}

bool VkGPAImplementor::GetHwInfoFromAPI(const GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo) const
{
    bool isSucceeded = false;

    if (nullptr != pContextInfo)
    {
        // ? TODO: Is it safe to static_cast this ?
        // ? TODO: Is there could be a way of verifying that pointer is exactly GPA_vkContextOpenInfo ?
        // ? TODO: Or is there could be a way to restrict app dev to pass this struct in case of Vulkan ?
        GPA_vkContextOpenInfo* pVkContextInfo = static_cast<GPA_vkContextOpenInfo*>(pContextInfo);

        if (VK_NULL_HANDLE != pVkContextInfo->instance && VK_NULL_HANDLE != pVkContextInfo->physicalDevice && VK_NULL_HANDLE != pVkContextInfo->device)
        {
            // For Vulkan, the pContext contains the VkInstance and vKDevice
            if (VkUtils::Initialize_Vk_Entrypoints(pVkContextInfo->instance, pVkContextInfo->device))
            {
                if (VkUtils::IsDeviceSupportedForProfiling(pVkContextInfo->physicalDevice))
                {
                    // Device is supported, fill the hardware info

                    // For now it is assumed that Vk MGPU support is exposed to the app
                    // and the app always opens the device on the correct GPU.
                    // In case where MGPU support hides the GPU from the app, then
                    // we will need to use Vk MGPU extension (and possibly ADL util)
                    // to get the correct HW info
                    VkPhysicalDeviceShaderCorePropertiesAMD shaderCorePropertiesAMD = {};
                    shaderCorePropertiesAMD.sType                                   = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_AMD;

                    VkPhysicalDeviceProperties2KHR physicalDeviceProperties = {};
                    physicalDeviceProperties.sType                          = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2_KHR;
                    physicalDeviceProperties.pNext                          = &shaderCorePropertiesAMD;

                    _vkGetPhysicalDeviceProperties2KHR(pVkContextInfo->physicalDevice, &physicalDeviceProperties);

                    gpa_uint64 freq = 0ull;

                    if (VkUtils::GetTimestampFrequency(pVkContextInfo->physicalDevice, freq))
                    {
                        // We have almost all information to fill the hardware info

                        gpa_uint32 vendorId       = physicalDeviceProperties.properties.vendorID;
                        gpa_uint32 deviceId       = physicalDeviceProperties.properties.deviceID;
                        uint32_t   deviceRevision = REVISION_ID_ANY;  // Vulkan doesn't have this

                        std::string       adapterName(physicalDeviceProperties.properties.deviceName);
                        GDT_HW_GENERATION hwGen = GDT_HW_GENERATION_NONE;

                        if (NVIDIA_VENDOR_ID == vendorId)
                        {
                            hwGen = GDT_HW_GENERATION_NVIDIA;
                        }
                        else if (INTEL_VENDOR_ID == vendorId)
                        {
                            hwGen = GDT_HW_GENERATION_INTEL;
                        }
                        else if (AMD_VENDOR_ID == vendorId)
                        {
                            GDT_GfxCardInfo cardInfo = {};

                            if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(deviceId, deviceRevision, cardInfo))
                            {
                                hwGen = cardInfo.m_generation;

                                // GPA Vk requires GFX8 or above (but also works on Hawaii)
                                if (GDT_HW_GENERATION_VOLCANICISLAND > hwGen && GDT_HAWAII != cardInfo.m_asicType)
                                {
                                    GPA_LogError("Hardware not supported.");
                                }
                                else
                                {
                                    hwInfo.SetDeviceName(adapterName.c_str());
                                    hwInfo.SetVendorID(vendorId);
                                    hwInfo.SetDeviceID(deviceId);
                                    hwInfo.SetRevisionID(deviceRevision);
                                    hwInfo.SetHWGeneration(hwGen);
                                    hwInfo.SetTimeStampFrequency(freq);

                                    size_t numSEs        = static_cast<size_t>(shaderCorePropertiesAMD.shaderEngineCount);
                                    size_t numTotalSAs   = static_cast<size_t>(shaderCorePropertiesAMD.shaderArraysPerEngineCount * numSEs);
                                    size_t numTotalCUs   = static_cast<size_t>(shaderCorePropertiesAMD.computeUnitsPerShaderArray * numTotalSAs);
                                    size_t numTotalSIMDs = static_cast<size_t>(shaderCorePropertiesAMD.simdPerComputeUnit * numTotalCUs);

                                    if (0 != numTotalSIMDs)
                                    {
                                        hwInfo.SetNumberSIMDs(numTotalSIMDs);

                                        // for now, don't use the driver-reported number of CUs for GFX10
                                        // just use the number in the device info table
                                        // this will be reverted once a driver fix is available
                                        if (hwGen < GDT_HW_GENERATION_GFX10)
                                        {
                                            hwInfo.SetNumberCUs(numTotalCUs);
                                        }

                                        hwInfo.SetNumberShaderArrays(numTotalSAs);
                                        hwInfo.SetNumberShaderEngines(numSEs);
                                    }

                                    isSucceeded = true;
                                }
                            }
                            else
                            {
                                GPA_LogError("Unable to get device info from AMDTDeviceInfoUtils.");
                            }
                        }
                        else
                        {
                            GPA_LogError("Unknown Device.");
                        }
                    }
                    else
                    {
                        GPA_LogError("Unable to get timestamp frequency.");
                    }
                }
                else
                {
                    GPA_LogError("Device is not supported for profiling.");
                }
            }
            else
            {
                GPA_LogError("Unable to initialize Vulkan entrypoints.");
            }
        }
        else
        {
            GPA_LogError("Unable to open context. Necessary member of 'pContext' is NULL.");
        }
    }
    else
    {
        GPA_LogError("Unable to proceed. Parameter 'pContext' is NULL.");
    }

    return isSucceeded;
}

bool VkGPAImplementor::VerifyAPIHwSupport(const GPAContextInfoPtr pContextInfo, const GPA_HWInfo& hwInfo) const
{
    bool isSupported = false;

    UNREFERENCED_PARAMETER(hwInfo);

    if (nullptr != pContextInfo)
    {
        GPA_vkContextOpenInfo* pVkContextInfo = static_cast<GPA_vkContextOpenInfo*>(pContextInfo);

        if (VK_NULL_HANDLE != pVkContextInfo->instance && VK_NULL_HANDLE != pVkContextInfo->physicalDevice && VK_NULL_HANDLE != pVkContextInfo->device)
        {
            // For Vulkan, the pContext contains the VkInstance
            if (VkUtils::Initialize_Vk_Entrypoints(pVkContextInfo->instance, pVkContextInfo->device))
            {
                isSupported = VkUtils::IsDeviceSupportedForProfiling(pVkContextInfo->physicalDevice);
            }
            else
            {
                GPA_LogError("Unable to initialize Vulkan entrypoints.");
            }
        }
        else
        {
            GPA_LogError("Unable to open context. Necessary member of 'pContext' is NULL.");
        }
    }
    else
    {
        GPA_LogError("Unable to proceed. Parameter 'pContext' is NULL.");
    }

    return isSupported;
}

bool VkGPAImplementor::IsCommandListRequired() const
{
    return true;
}

bool VkGPAImplementor::IsContinueSampleOnCommandListSupported() const
{
    return true;
}

bool VkGPAImplementor::IsCopySecondarySampleSupported() const
{
    return true;
}

IGPAContext* VkGPAImplementor::OpenAPIContext(GPAContextInfoPtr pContextInfo, GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags)
{
    IGPAContext*           pRetGpaContext = nullptr;
    GPA_vkContextOpenInfo* pVkContextInfo = static_cast<GPA_vkContextOpenInfo*>(pContextInfo);

    if (VK_NULL_HANDLE != pVkContextInfo->instance && VK_NULL_HANDLE != pVkContextInfo->physicalDevice && VK_NULL_HANDLE != pVkContextInfo->device)
    {
        // ? TODO: Is there a chance of multiple instance in Vulkan while opening a context ?
        // ? TODO: In case of multiple instance, do we need to store this instance in a map ?
        m_vkInstance = pVkContextInfo->instance;

        if (VkUtils::IsDeviceSupportedForProfiling(pVkContextInfo->physicalDevice))
        {
            VkGPAContext* pVkGPAContext = new (std::nothrow) VkGPAContext(pVkContextInfo, hwInfo, flags);

            if (nullptr != pVkGPAContext)
            {
                GPA_Status status = pVkGPAContext->Open();

                if (GPA_STATUS_OK == status && pVkGPAContext->IsOpen())
                {
                    pRetGpaContext = pVkGPAContext;
                }
                else
                {
                    delete pVkGPAContext;
                    GPA_LogError("Unable to open a context.");
                }
            }
            else
            {
                GPA_LogError("Unable to allocate memory for the context.");
            }
        }
        else
        {
            GPA_LogError("Unable to open a context, device is not supported.");
        }
    }
    else
    {
        GPA_LogError("Unable to open context. Necessary member of 'pContext' is NULL.");
    }

    return pRetGpaContext;
}

bool VkGPAImplementor::CloseAPIContext(GPADeviceIdentifier pDeviceIdentifier, IGPAContext* pContext)
{
    UNREFERENCED_PARAMETER(pDeviceIdentifier);
    assert(nullptr != pContext);

    if (nullptr != pContext)
    {
        delete reinterpret_cast<VkGPAContext*>(pContext);
        pContext = nullptr;
    }

    return (nullptr == pContext);
}

GPADeviceIdentifier VkGPAImplementor::GetDeviceIdentifierFromContextInfo(GPAContextInfoPtr pContextInfo) const
{
    assert(nullptr != pContextInfo);

    GPA_vkContextOpenInfo* pVkContextOpenInfo = static_cast<GPA_vkContextOpenInfo*>(pContextInfo);
    return pVkContextOpenInfo->physicalDevice;
}
