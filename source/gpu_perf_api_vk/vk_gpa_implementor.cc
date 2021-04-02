//==============================================================================
// Copyright (c) 2015-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GPA Vk API implementation
//==============================================================================

#include "gpu_perf_api_vk/vk_gpa_implementor.h"

#include <assert.h>

#include "DeviceInfoUtils.h"

#include "gpu_performance_api/gpu_perf_api_vk.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_vk.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_vk_non_amd.h"
#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_vk.h"

#include "gpu_perf_api_common/gpa_command_list_interface.h"
#include "gpu_perf_api_common/logging.h"

#include "gpu_perf_api_vk/vk_entry_points.h"
#include "gpu_perf_api_vk/vk_gpa_context.h"
#include "gpu_perf_api_vk/vk_includes.h"
#include "gpu_perf_api_vk/vk_utils.h"

IGpaImplementor*                   gpa_imp = VkGpaImplementor::Instance();
static GpaCounterGeneratorVk       generator_vk;          ///< Static instance of VK generator.
static GpaCounterGeneratorVkNonAmd generator_vk_non_amd;  ///< Static instance of Vulkan non-AMD generator.
static GpaCounterSchedulerVk       scheduler_vk;          ///< Static instance of VK scheduler.

GpaApiType VkGpaImplementor::GetApiType() const
{
    return kGpaApiVulkan;
}

bool VkGpaImplementor::GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaHwInfo& hw_info) const
{
    bool is_succeeded = false;

    if (nullptr != context_info)
    {
        GpaVkContextOpenInfo* vk_context_info = static_cast<GpaVkContextOpenInfo*>(context_info);

        if (VK_NULL_HANDLE != vk_context_info->instance && VK_NULL_HANDLE != vk_context_info->physical_device && VK_NULL_HANDLE != vk_context_info->device)
        {
            // For Vulkan, the context contains the VkInstance and vKDevice.
            if (vk_utils::InitializeVkEntryPoints(vk_context_info->instance, vk_context_info->device))
            {
                if (vk_utils::IsDeviceSupportedForProfiling(vk_context_info->physical_device))
                {
                    // Device is supported, fill the hardware info.
                    // For now it is assumed that Vk MGPU support is exposed to the app
                    // and the app always opens the device on the correct GPU.
                    // In case where MGPU support hides the GPU from the app, then
                    // we will need to use Vk MGPU extension (and possibly ADL util)
                    // to get the correct HW info.
                    VkPhysicalDeviceShaderCoreProperties2AMD shader_core_properties_2_amd = {};
                    shader_core_properties_2_amd.sType                                    = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_2_AMD;

                    VkPhysicalDeviceShaderCorePropertiesAMD shader_core_properties_amd = {};
                    shader_core_properties_amd.sType                                   = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_AMD;
                    shader_core_properties_amd.pNext                                   = &shader_core_properties_2_amd;

                    VkPhysicalDeviceProperties2KHR physical_device_properties = {};
                    physical_device_properties.sType                          = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2_KHR;
                    physical_device_properties.pNext                          = &shader_core_properties_amd;

                    _vkGetPhysicalDeviceProperties2KHR(vk_context_info->physical_device, &physical_device_properties);

                    GpaUInt64 freq = 0ull;

                    if (vk_utils::GetTimestampFrequency(vk_context_info->physical_device, freq))
                    {
                        // We have almost all information to fill the hardware info.

                        GpaUInt32 vendor_id       = physical_device_properties.properties.vendorID;
                        GpaUInt32 device_id       = physical_device_properties.properties.deviceID;
                        uint32_t  device_revision = REVISION_ID_ANY;  // Vulkan doesn't have this.

                        std::string       adapter_name(physical_device_properties.properties.deviceName);
                        GDT_HW_GENERATION hardware_generation = GDT_HW_GENERATION_NONE;

                        if (kNvidiaVendorId == vendor_id)
                        {
                            hardware_generation = GDT_HW_GENERATION_NVIDIA;
                        }
                        else if (kIntelVendorId == vendor_id)
                        {
                            hardware_generation = GDT_HW_GENERATION_INTEL;
                        }
                        else if (kAmdVendorId == vendor_id)
                        {
                            GDT_GfxCardInfo card_info = {};

                            if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(device_id, device_revision, card_info))
                            {
                                hardware_generation = card_info.m_generation;

                                // GPA Vk requires GFX8 or above (but also works on Hawaii).
                                if (GDT_HW_GENERATION_VOLCANICISLAND > hardware_generation && GDT_HAWAII != card_info.m_asicType)
                                {
                                    GPA_LOG_ERROR("Hardware not supported.");
                                }
                                else
                                {
                                    hw_info.SetDeviceName(adapter_name.c_str());
                                    hw_info.SetVendorId(vendor_id);
                                    hw_info.SetDeviceId(device_id);
                                    hw_info.SetRevisionId(device_revision);
                                    hw_info.SetHwGeneration(hardware_generation);
                                    hw_info.SetTimeStampFrequency(freq);

                                    size_t num_shader_engines = static_cast<size_t>(shader_core_properties_amd.shaderEngineCount);
                                    size_t num_total_shader_arrays =
                                        static_cast<size_t>(shader_core_properties_amd.shaderArraysPerEngineCount * num_shader_engines);
                                    size_t num_total_compute_units = 0;

                                    if (shader_core_properties_2_amd.activeComputeUnitCount != 0)
                                    {
                                        num_total_compute_units = static_cast<size_t>(shader_core_properties_2_amd.activeComputeUnitCount);
                                    }
                                    else if (hardware_generation < GDT_HW_GENERATION_GFX10)
                                    {
                                        num_total_compute_units =
                                            static_cast<size_t>(shader_core_properties_amd.computeUnitsPerShaderArray * num_total_shader_arrays);
                                    }
                                    else
                                    {
                                        num_total_compute_units = hw_info.GetNumberCus();
                                    }

                                    size_t num_total_simds = static_cast<size_t>(shader_core_properties_amd.simdPerComputeUnit * num_total_compute_units);

                                    if (0 != num_total_simds)
                                    {
                                        hw_info.SetNumberSimds(num_total_simds);
                                        hw_info.SetNumberCus(num_total_compute_units);
                                        hw_info.SetNumberShaderArrays(num_total_shader_arrays);
                                        hw_info.SetNumberShaderEngines(num_shader_engines);
                                    }

                                    is_succeeded = true;
                                }
                            }
                            else
                            {
                                GPA_LOG_ERROR("Unable to get device info from AMDTDeviceInfoUtils.");
                            }
                        }
                        else
                        {
                            GPA_LOG_ERROR("Unknown Device.");
                        }
                    }
                    else
                    {
                        GPA_LOG_ERROR("Unable to get timestamp frequency.");
                    }
                }
                else
                {
                    GPA_LOG_ERROR("Device is not supported for profiling.");
                }
            }
            else
            {
                GPA_LOG_ERROR("Unable to initialize Vulkan entrypoints.");
            }
        }
        else
        {
            GPA_LOG_ERROR("Unable to open context. Necessary member of 'context' is NULL.");
        }
    }
    else
    {
        GPA_LOG_ERROR("Unable to proceed. Parameter 'context' is NULL.");
    }

    return is_succeeded;
}

bool VkGpaImplementor::VerifyApiHwSupport(const GpaContextInfoPtr context_info, const GpaHwInfo& hardware_info) const
{
    bool is_supported = false;

    UNREFERENCED_PARAMETER(hardware_info);

    if (nullptr != context_info)
    {
        GpaVkContextOpenInfo* vk_context_info = static_cast<GpaVkContextOpenInfo*>(context_info);

        if (VK_NULL_HANDLE != vk_context_info->instance && VK_NULL_HANDLE != vk_context_info->physical_device && VK_NULL_HANDLE != vk_context_info->device)
        {
            // For Vulkan, the context contains the VkInstance.
            if (vk_utils::InitializeVkEntryPoints(vk_context_info->instance, vk_context_info->device))
            {
                is_supported = vk_utils::IsDeviceSupportedForProfiling(vk_context_info->physical_device);
            }
            else
            {
                GPA_LOG_ERROR("Unable to initialize Vulkan entrypoints.");
            }
        }
        else
        {
            GPA_LOG_ERROR("Unable to open context. Necessary member of 'context' is NULL.");
        }
    }
    else
    {
        GPA_LOG_ERROR("Unable to proceed. Parameter 'context' is NULL.");
    }

    return is_supported;
}

bool VkGpaImplementor::IsCommandListRequired() const
{
    return true;
}

bool VkGpaImplementor::IsContinueSampleOnCommandListSupported() const
{
    return true;
}

bool VkGpaImplementor::IsCopySecondarySampleSupported() const
{
    return true;
}

IGpaContext* VkGpaImplementor::OpenApiContext(GpaContextInfoPtr context_info, GpaHwInfo& hardware_info, GpaOpenContextFlags flags)
{
    IGpaContext*          gpa_context     = nullptr;
    GpaVkContextOpenInfo* vk_context_info = static_cast<GpaVkContextOpenInfo*>(context_info);

    if (VK_NULL_HANDLE != vk_context_info->instance && VK_NULL_HANDLE != vk_context_info->physical_device && VK_NULL_HANDLE != vk_context_info->device)
    {
        vk_instance_ = vk_context_info->instance;

        if (vk_utils::IsDeviceSupportedForProfiling(vk_context_info->physical_device))
        {
            VkGpaContext* vk_gpa_context = new (std::nothrow) VkGpaContext(vk_context_info, hardware_info, flags);

            if (nullptr != vk_gpa_context)
            {
                GpaStatus status = vk_gpa_context->Open();

                if (kGpaStatusOk == status && vk_gpa_context->IsOpen())
                {
                    gpa_context = vk_gpa_context;
                }
                else
                {
                    delete vk_gpa_context;
                    GPA_LOG_ERROR("Unable to open a context.");
                }
            }
            else
            {
                GPA_LOG_ERROR("Unable to allocate memory for the context.");
            }
        }
        else
        {
            GPA_LOG_ERROR("Unable to open a context, device is not supported.");
        }
    }
    else
    {
        GPA_LOG_ERROR("Unable to open context. Necessary member of 'context' is NULL.");
    }

    return gpa_context;
}

bool VkGpaImplementor::CloseApiContext(GpaDeviceIdentifier device_identifier, IGpaContext* context)
{
    UNREFERENCED_PARAMETER(device_identifier);
    assert(nullptr != context);

    if (nullptr != context)
    {
        delete reinterpret_cast<VkGpaContext*>(context);
        context = nullptr;
    }

    return (nullptr == context);
}

GpaDeviceIdentifier VkGpaImplementor::GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const
{
    assert(nullptr != context_info);

    GpaVkContextOpenInfo* context_open_info = static_cast<GpaVkContextOpenInfo*>(context_info);
    return context_open_info->physical_device;
}
