//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA Vk API implementation
//==============================================================================

#include "GPUPerfAPIVk.h"

#include <DeviceInfoUtils.h>
#include "GPUPerfAPIImp.h"
#include "GPUPerfAPI.h"
#include "GPACounterGenerator.h"
#include "GPAContextStateVk.h"
#include "VkCounterDataRequestProxy.h"
#include "VkEntrypoints.h"

#ifdef _LINUX
    #include <dlfcn.h>
#endif

// Instance entrypoints
PFN_vkGetPhysicalDeviceProperties _vkGetPhysicalDeviceProperties;
PFN_vkGetPhysicalDeviceQueueFamilyProperties _vkGetPhysicalDeviceQueueFamilyProperties;
PFN_vkGetPhysicalDeviceMemoryProperties _vkGetPhysicalDeviceMemoryProperties;
PFN_vkGetPhysicalDeviceFeatures _vkGetPhysicalDeviceFeatures;
PFN_vkGetBufferMemoryRequirements _vkGetBufferMemoryRequirements;
PFN_vkGetPhysicalDeviceProperties2KHR _vkGetPhysicalDeviceProperties2KHR;
PFN_vkGetPhysicalDeviceFeatures2KHR _vkGetPhysicalDeviceFeatures2KHR;

// Device entrypoints
PFN_vkGetDeviceQueue _vkGetDeviceQueue;
PFN_vkCreateQueryPool _vkCreateQueryPool;
PFN_vkDestroyQueryPool _vkDestroyQueryPool;
PFN_vkCreateBuffer _vkCreateBuffer;
PFN_vkDestroyBuffer _vkDestroyBuffer;
PFN_vkAllocateMemory _vkAllocateMemory;
PFN_vkBindBufferMemory _vkBindBufferMemory;
PFN_vkFreeMemory _vkFreeMemory;
PFN_vkMapMemory _vkMapMemory;
PFN_vkUnmapMemory _vkUnmapMemory;
PFN_vkFlushMappedMemoryRanges _vkFlushMappedMemoryRanges;
PFN_vkCmdResetQueryPool _vkCmdResetQueryPool;
PFN_vkCmdBeginQuery _vkCmdBeginQuery;
PFN_vkCmdEndQuery _vkCmdEndQuery;
PFN_vkCmdWriteTimestamp _vkCmdWriteTimestamp;
PFN_vkCmdCopyQueryPoolResults _vkCmdCopyQueryPoolResults;
PFN_vkGetQueryPoolResults _vkGetQueryPoolResults;
PFN_vkCmdCopyBuffer _vkCmdCopyBuffer;
PFN_vkDeviceWaitIdle _vkDeviceWaitIdle;

// vk_amd_gpa_interface device extension
PFN_vkCreateGpaSessionAMD _vkCreateGpaSessionAMD;
PFN_vkDestroyGpaSessionAMD _vkDestroyGpaSessionAMD;
PFN_vkSetGpaDeviceClockModeAMD _vkSetGpaDeviceClockModeAMD;
PFN_vkCmdBeginGpaSessionAMD _vkCmdBeginGpaSessionAMD;
PFN_vkCmdEndGpaSessionAMD _vkCmdEndGpaSessionAMD;
PFN_vkCmdBeginGpaSampleAMD _vkCmdBeginGpaSampleAMD;
PFN_vkCmdEndGpaSampleAMD _vkCmdEndGpaSampleAMD;
PFN_vkGetGpaSessionStatusAMD _vkGetGpaSessionStatusAMD;
PFN_vkGetGpaSessionResultsAMD _vkGetGpaSessionResultsAMD;
PFN_vkResetGpaSessionAMD _vkResetGpaSessionAMD;
PFN_vkCmdCopyGpaSessionResultsAMD _vkCmdCopyGpaSessionResultsAMD;

bool Initialize_Vk_Entrypoints(VkInstance instance, VkDevice device)
{
#ifdef _WIN32
    HMODULE vulkanModule = GetModuleHandle("Vulkan-1.dll");
#else
    void* vulkanModule = dlopen("libvulkan.so", RTLD_NOLOAD);

    if (vulkanModule == nullptr)
    {
        vulkanModule = dlopen("libvulkan.so", RTLD_NOW);
    }

    if (vulkanModule == nullptr)
    {
        vulkanModule = dlopen("libvulkan.so.1", RTLD_NOLOAD);
    }

    if (vulkanModule == nullptr)
    {
        vulkanModule = dlopen("libvulkan.so.1", RTLD_NOW);
    }
#endif

    if (vulkanModule == nullptr)
    {
        GPA_LogError("Failed to get handle to Vulkan Loader.");
        return false;
    }

#ifdef _WIN32
    PFN_vkGetInstanceProcAddr _vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)GetProcAddress(vulkanModule, "vkGetInstanceProcAddr");
#else
    PFN_vkGetInstanceProcAddr _vkGetInstanceProcAddr = (PFN_vkGetInstanceProcAddr)dlsym(vulkanModule, "vkGetInstanceProcAddr");
#endif

    bool bResult = (_vkGetInstanceProcAddr != nullptr);

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
    PFN_vkGetDeviceProcAddr _vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr)GetProcAddress(vulkanModule, "vkGetDeviceProcAddr");
#else
    PFN_vkGetDeviceProcAddr _vkGetDeviceProcAddr = (PFN_vkGetDeviceProcAddr)dlsym(vulkanModule, "vkGetDeviceProcAddr");
#endif

    bResult &= (_vkGetDeviceProcAddr != nullptr);

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
    }

    return bResult;
}


/// Access to the current GPA Vk context
/// \return The current Vk GPA context
inline GPA_ContextStateVk* GetCurrentContext()
{
    return static_cast<GPA_ContextStateVk* >(g_pCurrentContext);
}

GPA_Status GPA_IMP_GetHWInfo(void* pContext, GPA_HWInfo* pHwInfo)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == pContext)
    {
        GPA_LogError("Parameter 'pContext' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else if (nullptr == pHwInfo)
    {
        GPA_LogError("Parameter 'pHwInfo' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        GPA_vkContextOpenInfo* pVkContext = static_cast<GPA_vkContextOpenInfo*>(pContext);
        if (pVkContext->instance == VK_NULL_HANDLE ||
            pVkContext->physicalDevice == VK_NULL_HANDLE ||
            pVkContext->device == VK_NULL_HANDLE)
        {
            GPA_LogError("Necessary member of 'pContext' is NULL.");
            result = GPA_STATUS_ERROR_NULL_POINTER;
        }
        else
        {
            // For Vulkan, the pContext contains the VkInstance
            if (false == Initialize_Vk_Entrypoints(pVkContext->instance, pVkContext->device))
            {
                GPA_LogError("Unable to initialize Vulkan entrypoints.");
                result = GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED;
            }
            else
            {
                GetCurrentContext()->SetVkDevice(pVkContext->device);
                VkPhysicalDevice physicalDevice = pVkContext->physicalDevice;

                uint32_t queueFamilyCount = 0;
                _vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

                if (queueFamilyCount == 0)
                {
                    GPA_LogError("Device does not support any queue families; cannot be supported.");
                    result = GPA_STATUS_ERROR_FAILED;
                }
                else
                {
                    VkQueueFamilyProperties* pQueueFamilyProperties = new (std::nothrow) VkQueueFamilyProperties[queueFamilyCount];
                    if (pQueueFamilyProperties == nullptr)
                    {
                        GPA_LogError("Failed to allocate memory for QueueFamilyProperties.");
                        result = GPA_STATUS_ERROR_FAILED;
                    }
                    else
                    {
                        _vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, pQueueFamilyProperties);

                        if (pQueueFamilyProperties[0].timestampValidBits == 0)
                        {
                            GPA_LogError("QueueFamily 0 does not have any valid timestamp bits; cannot be supported.");
                            result = GPA_STATUS_ERROR_FAILED;
                        }
                        else
                        {
                            gpa_uint64 freq = 0ull;
                            result = GetCurrentContext()->SetVkPhysicalDevice(physicalDevice);
                            if (GPA_STATUS_OK == result)
                            {
                                // if counters are supported, then set stable clocks
                                VkPhysicalDeviceGpaFeaturesAMD featuresAMD = {};
                                featuresAMD.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GPA_FEATURES_AMD;

                                VkPhysicalDeviceFeatures2KHR features = {};
                                features.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2_KHR;
                                features.pNext = &featuresAMD;

                                _vkGetPhysicalDeviceFeatures2KHR(physicalDevice, &features);
                                if (featuresAMD.perfCounters == VK_TRUE)
                                {
                                    // we don't want a failure when setting stable clocks to result in a
                                    // fatal error returned from GetHwInfo. So we use a local status object
                                    // instead of modifying "result".  We will still output log messages.
                                    GPA_Status setStableClocksStatus =  GetCurrentContext()->SetStableClocks(true);

                                    if (setStableClocksStatus != GPA_STATUS_OK)
                                    {
                                        GPA_LogError("Driver was unable to set stable clocks for profiling.");
#ifdef __linux__
                                        GPA_LogMessage("In Linux, make sure to run your application with root privileges.");
#endif //__linux__
                                    }
                                }
                                else
                                {
                                    GPA_LogError("Active GPU hardware does not support performance counters.");
                                    result = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
                                }

                                if (result == GPA_STATUS_OK)
                                {
                                    // For now it is assumed that Vk MGPU support is exposed to the app
                                    // and the app always opens the device on the correct GPU.
                                    // In case where MGPU support hides the GPU from the app, then
                                    // we will need to use Vk MGPU extension (and possibly ADL util)
                                    // to get the correct HW info
                                    VkPhysicalDeviceGpaPropertiesAMD propertiesAMD = {};
                                    propertiesAMD.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GPA_PROPERTIES_AMD;

                                    VkPhysicalDeviceProperties2KHR properties = {};
                                    properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2_KHR;
                                    properties.pNext = &propertiesAMD;

                                    _vkGetPhysicalDeviceProperties2KHR(physicalDevice, &properties);

                                    result = GetCurrentContext()->GetTimestampFrequency(freq);
                                    if (GPA_STATUS_OK != result)
                                    {
                                        GPA_LogError("GetTimestampFrequency() failed.");
                                    }
                                    else
                                    {
                                        pHwInfo->SetVendorID(properties.properties.vendorID);
                                        pHwInfo->SetDeviceID(properties.properties.deviceID);
                                        uint32_t deviceRevision = REVISION_ID_ANY; // < Vulkan doesn't have this
                                        pHwInfo->SetRevisionID(deviceRevision);

                                        std::string adapterName(properties.properties.deviceName);
                                        pHwInfo->SetDeviceName(adapterName.c_str());
                                        GDT_HW_GENERATION hwGen = GDT_HW_GENERATION_NONE;

                                        if (NVIDIA_VENDOR_ID == properties.properties.vendorID)
                                        {
                                            hwGen = GDT_HW_GENERATION_NVIDIA;
                                        }
                                        else if (INTEL_VENDOR_ID == properties.properties.vendorID)
                                        {
                                            hwGen = GDT_HW_GENERATION_INTEL;
                                        }
                                        else if (AMD_VENDOR_ID == properties.properties.vendorID)
                                        {
                                            GDT_GfxCardInfo cardInfo;

                                            if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(properties.properties.deviceID, deviceRevision, cardInfo))
                                            {
                                                hwGen = cardInfo.m_generation;

                                                // GPA Vk requires GFX8 or above (but also works on Hawaii)
                                                if (GDT_HW_GENERATION_VOLCANICISLAND > hwGen && GDT_HAWAII != cardInfo.m_asicType)
                                                {
                                                    result = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
                                                }
                                            }
                                        }

                                        pHwInfo->SetHWGeneration(hwGen);
                                        pHwInfo->SetTimeStampFrequency(freq);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return result;
}

GPA_Status GPA_IMP_CompareHWInfo(void* pContext, GPA_HWInfo* pHwInfo)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == pContext)
    {
        GPA_LogError("Parameter 'pContext' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else if (nullptr == pHwInfo)
    {
        GPA_LogError("Parameter 'pHwInfo' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        GPA_HWInfo hwInfo;
        result = GPA_IMP_GetHWInfo(pContext, &hwInfo);

        if (GPA_STATUS_OK == result)
        {
            result = CompareHwInfo(pHwInfo, &hwInfo);
        }
    }

    return result;
}

GPA_Status GPA_IMP_VerifyHWSupport(void* pContext, GPA_HWInfo* pHwInfo)
{
    GPA_Status result = GPA_STATUS_OK;

    if ((nullptr == pContext) || (nullptr == pHwInfo))
    {
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        GPA_vkContextOpenInfo* pVkContext = static_cast<GPA_vkContextOpenInfo*>(pContext);

        if (pVkContext->instance == VK_NULL_HANDLE ||
            pVkContext->physicalDevice == VK_NULL_HANDLE ||
            pVkContext->device == VK_NULL_HANDLE)
        {
            GPA_LogError("Necessary member of 'pContext' is NULL.");
            result = GPA_STATUS_ERROR_NULL_POINTER;
        }
        else
        {
            // TODO Once Vk performance extension is available, check
            //      it's possible to create a HW counter
        }
    }

    return result;
}

GPA_Status GPA_IMP_CreateContext(GPA_ContextState** ppNewContext)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == ppNewContext)
    {
        GPA_LogError("Unable to create context. Parameter 'pContext' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }

    GPA_ContextStateVk* pContext = new(std::nothrow) GPA_ContextStateVk;

    if (nullptr == pContext)
    {
        GPA_LogError("Unable to create context.");
        result = GPA_STATUS_ERROR_FAILED;
    }
    else
    {
        (*ppNewContext) = pContext;
    }

    return result;
}

GPA_Status GPA_IMP_Initialize()
{
    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_Destroy()
{
    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_OpenContext(void* pContext)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == pContext)
    {
        GPA_LogError("Unable to open context. Parameter 'pContext' is NULL.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        GPA_vkContextOpenInfo* pVkContext = static_cast<GPA_vkContextOpenInfo*>(pContext);
        if (pVkContext->instance == VK_NULL_HANDLE ||
            pVkContext->physicalDevice == VK_NULL_HANDLE ||
            pVkContext->device == VK_NULL_HANDLE)
        {
            GPA_LogError("Unable to open context. Necessary member of 'pContext' is NULL.");
            result = GPA_STATUS_ERROR_NULL_POINTER;
        }
        else
        {
            // For Vulkan, the pContext contains the VkInstance
            if (false == Initialize_Vk_Entrypoints(pVkContext->instance, pVkContext->device))
            {
                GPA_LogError("Unable to initialize Vulkan entrypoints.");
                result = GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED;
            }
            else
            {
                GetCurrentContext()->SetVkDevice(pVkContext->device);
                result = GetCurrentContext()->SetVkPhysicalDevice(pVkContext->physicalDevice);
       
                if (GPA_STATUS_OK == result)
                {
                    gpa_uint32 vendorId = 0;
                    gpa_uint32 deviceId = 0;
                    gpa_uint32 revisionId = 0;
       
                    if (false == (GetCurrentContext()->m_hwInfo.GetVendorID(vendorId)))
                    {
                        result = GPA_STATUS_ERROR_FAILED;
                    }
                    else if (false == (GetCurrentContext()->m_hwInfo.GetDeviceID(deviceId)))
                    {
                        result = GPA_STATUS_ERROR_FAILED;
                    }
                    else if (false == (GetCurrentContext()->m_hwInfo.GetRevisionID(revisionId)))
                    {
                        result = GPA_STATUS_ERROR_FAILED;
                    }
       
                    if (GPA_STATUS_OK == result)
                    {
                        GPA_ICounterAccessor* pCounterAccessor = nullptr;
                        GPA_ICounterScheduler* pCounterScheduler = nullptr;
                        result = GenerateCounters(
                                        GPA_API_VULKAN,
                                        vendorId,
                                        deviceId,
                                        revisionId,
                                        &pCounterAccessor,
                                        &pCounterScheduler);

                        pCounterAccessor->SetAllowedCounters(GetCurrentContext()->ExposePublicCounters(),
                            GetCurrentContext()->ExposeHardwareCounters(), 
                            GetCurrentContext()->ExposeSoftwareCounters());
       
                        if (GPA_STATUS_OK == result)
                        {
                            GetCurrentContext()->m_pCounterAccessor =
                                static_cast<GPA_CounterGeneratorBase*>(pCounterAccessor);
                            GetCurrentContext()->m_pCounterScheduler = pCounterScheduler;
                        }
                    }
                }
            }
        }
    }

    return result;
}

GPA_Status GPA_IMP_CloseContext()
{
    if (nullptr != GetCurrentContext())
    {
        GetCurrentContext()->Cleanup();
    }

    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_SelectContext(void* pContext)
{
    UNREFERENCED_PARAMETER(pContext);
    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_BeginSession(gpa_uint32* pSessionID, bool counterSelectionChanged)
{
    UNREFERENCED_PARAMETER(pSessionID);
    UNREFERENCED_PARAMETER(counterSelectionChanged);

    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_EndSession()
{
    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_BeginPass()
{
    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_EndPass()
{
    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_BeginSampleList(void* pSampleList)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == pSampleList)
    {
        GPA_LogError("Cannot begin a sample list for a null sample list.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        result = GetCurrentContext()->BeginCommandBuffer(pSampleList);

        if (GPA_STATUS_OK != result)
        {
            GPA_LogError("Unable to begin a sample list.");
        }
    }

    if (GPA_STATUS_OK == result)
    {
        g_pCurrentContext->SetInvalidateAndFlushL2Cache(true);
    }

    return result;
}

GPA_Status GPA_IMP_EndSampleList(void* pSampleList)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == pSampleList)
    {
        GPA_LogError("Cannot end a sample list for a null sample list.");
        result = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        result = GetCurrentContext()->EndCommandBuffer(pSampleList);

        if (GPA_STATUS_OK != result)
        {
            GPA_LogError("Unable to end a sample list.");
        }
    }

    return result;
}

GPA_Status GPA_IMP_BeginSampleInSampleList(gpa_uint32 sampleID, void* pSampleList)
{
    UNREFERENCED_PARAMETER(sampleID);
    UNREFERENCED_PARAMETER(pSampleList);
    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_EndSampleInSampleList(void* pSampleList)
{
    UNREFERENCED_PARAMETER(pSampleList);
    return GPA_STATUS_OK;
}

GPA_Status GPA_IMP_BeginSample(gpa_uint32 sampleID)
{
    UNREFERENCED_PARAMETER(sampleID);
    GPA_LogError("GPA_BeginSample is not supported. Use GPA_BeginSampleInSampleList instead.");
    return GPA_STATUS_ERROR_API_NOT_SUPPORTED;
}

GPA_Status GPA_IMP_EndSample()
{
    GPA_LogError("GPA_EndSample is not supported. Use GPA_EndSampleInSampleList instead.");
    return GPA_STATUS_ERROR_API_NOT_SUPPORTED;
}

gpa_uint32 GPA_IMP_GetDefaultMaxSessions()
{
    static const gpa_uint32 hwMaxSessions = 32;
    return hwMaxSessions;
}

gpa_uint32 GPA_IMP_GetPreferredCheckResultFrequency()
{
    // Don't check for results automatically, the app will request them as-needed.
    return 0;
}

GPA_DataRequest* GPA_IMP_CreateDataRequest()
{
    GPA_DataRequest* pDataRequest = nullptr;
    GDT_HW_GENERATION hwGen = GDT_HW_GENERATION_NONE;

    if (nullptr == GetCurrentContext())
    {
        GPA_LogError("No context available. Unable to create a data request.");
        return nullptr;
    }
    else if (false == GetCurrentContext()->m_hwInfo.GetHWGeneration(hwGen))
    {
        GPA_LogError("Unable to get hardware generation.");
    }
    else
    {
        if (GDT_HW_GENERATION_NONE == hwGen)
        {
            GPA_LogError("Invalid hardware generation.");
        }
        else
        {
            pDataRequest = new(std::nothrow) VkCounterDataRequestProxy;
        }
    }

    return pDataRequest;
}
