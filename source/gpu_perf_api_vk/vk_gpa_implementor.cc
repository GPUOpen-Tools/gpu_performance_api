//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GPA Vk API implementation
//==============================================================================

#include "gpu_perf_api_vk/vk_gpa_implementor.h"

#include <cassert>
#include <memory>

#include "device_info.hpp"

#include "gpu_performance_api/gpu_perf_api_vk.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_vk.h"
#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_vk.h"

#include "gpu_perf_api_common/gpa_command_list_interface.h"
#include "gpu_perf_api_common/logging.h"

#include "gpu_perf_api_vk/vk_entry_points.h"
#include "gpu_perf_api_vk/vk_gpa_context.h"
#include "gpu_perf_api_vk/vk_includes.h"
#include "gpu_perf_api_vk/vk_utils.h"

namespace
{
    std::unique_ptr<GpaCounterGeneratorVk> generator_vk;  ///< Static instance of VK generator.
    std::unique_ptr<GpaCounterSchedulerVk> scheduler_vk;  ///< Static instance of VK scheduler.
}  // namespace

IGpaImplementor& CreateImplementor()
{
    generator_vk = std::make_unique<GpaCounterGeneratorVk>(kGpaSessionSampleTypeDiscreteCounter);
    scheduler_vk = std::make_unique<GpaCounterSchedulerVk>(kGpaSessionSampleTypeDiscreteCounter);
    return VkGpaImplementor::Instance();
}

void DestroyImplementor()
{
    generator_vk.reset();
    scheduler_vk.reset();
}

GpaStatus VkGpaImplementor::GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, GpaHwInfo& hw_info) const
{
    GpaStatus status = kGpaStatusErrorHardwareNotSupported;

    if (nullptr != context_info)
    {
        PFN_vkGetDeviceProcAddr   get_device_proc_addr   = NULL;  ///< The vulkan device proc query.
        PFN_vkGetInstanceProcAddr get_instance_proc_addr = NULL;  ///< The vulkan instance proc query.

        if (flags & kGpaOpenContextVkUseInfoType2)
        {
            get_device_proc_addr   = (reinterpret_cast<GpaVkContextOpenInfo2*>(context_info))->get_device_proc_addr;
            get_instance_proc_addr = (reinterpret_cast<GpaVkContextOpenInfo2*>(context_info))->get_instance_proc_addr;
        }

        GpaVkContextOpenInfo* vk_context_info = static_cast<GpaVkContextOpenInfo*>(context_info);

        if (VK_NULL_HANDLE != vk_context_info->instance && VK_NULL_HANDLE != vk_context_info->physical_device && VK_NULL_HANDLE != vk_context_info->device)
        {
            // For Vulkan, the context contains the VkInstance and VkDevice.
            if (vk_utils::InitializeVkEntryPoints(vk_context_info->instance, vk_context_info->device, get_instance_proc_addr, get_device_proc_addr))
            {
                if (vk_utils::IsDeviceSupportedForProfiling(vk_context_info->physical_device))
                {
                    // Device is supported, fill the hardware info.
                    // For now it is assumed that Vk MGPU support is exposed to the app
                    // and the app always opens the device on the correct GPU.
                    // In case where MGPU support hides the GPU from the app, then
                    // we will need to use Vk MGPU extension to get the correct HW info.
                    VkPhysicalDeviceShaderCoreProperties2AMD shader_core_properties_2_amd = {};
                    shader_core_properties_2_amd.sType                                    = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_2_AMD;

                    VkPhysicalDeviceShaderCorePropertiesAMD shader_core_properties_amd = {};
                    shader_core_properties_amd.sType                                   = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SHADER_CORE_PROPERTIES_AMD;
                    shader_core_properties_amd.pNext                                   = &shader_core_properties_2_amd;

                    VkPhysicalDeviceGpaProperties2AMD physical_device_properties2 = {};
                    physical_device_properties2.sType                             = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GPA_PROPERTIES2_AMD;
                    physical_device_properties2.revisionId                        = device_info::kRevisionIdAny;
                    physical_device_properties2.pNext                             = &shader_core_properties_amd;

                    VkPhysicalDeviceProperties2KHR physical_device_properties = {};
                    physical_device_properties.sType                          = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2_KHR;
                    physical_device_properties.pNext                          = &physical_device_properties2;

                    _vkGetPhysicalDeviceProperties2KHR(vk_context_info->physical_device, &physical_device_properties);

                    GpaUInt64 freq = 0ull;

                    if (vk_utils::GetTimestampFrequency(vk_context_info->physical_device, freq))
                    {
                        hw_info.SetVendorId(physical_device_properties.properties.vendorID);
                        hw_info.SetDeviceId(physical_device_properties.properties.deviceID);
                        hw_info.SetRevisionId(physical_device_properties2.revisionId);

                        const std::string adapter_name(physical_device_properties.properties.deviceName);

                        if (const std::optional<device_info::CardInfo> card_info = device_info::GetCardInfo(hw_info.GetDeviceDescription().value());
                            card_info.has_value())
                        {
                            hw_info.SetDeviceName(adapter_name.c_str());
                            hw_info.SetHwGeneration(card_info->generation);
                            hw_info.SetTimeStampFrequency(freq);

                            status = kGpaStatusOk;

                            const uint32_t num_shader_engines = shader_core_properties_amd.shaderEngineCount;
                            hw_info.SetNumberShaderEngines(num_shader_engines);
                            if (num_shader_engines == 0)
                            {
                                GpaLogger::Instance().LogError("Vulkan returned invalid number of shader engines.");
                                status = kGpaStatusErrorHardwareNotSupported;
                            }

                            const uint32_t num_total_shader_arrays = shader_core_properties_amd.shaderArraysPerEngineCount * num_shader_engines;
                            hw_info.SetNumberShaderArrays(num_total_shader_arrays);
                            if (num_total_shader_arrays == 0)
                            {
                                GpaLogger::Instance().LogError("Vulkan returned invalid number of shader arrays.");
                                status = kGpaStatusErrorHardwareNotSupported;
                            }

                            const uint32_t num_total_compute_units = shader_core_properties_2_amd.activeComputeUnitCount;
                            hw_info.SetNumberCus(num_total_compute_units);
                            if (num_total_compute_units == 0)
                            {
                                GpaLogger::Instance().LogError("Vulkan returned invalid number of active compute units.");
                                status = kGpaStatusErrorHardwareNotSupported;
                            }

                            const uint32_t num_total_simds = shader_core_properties_amd.simdPerComputeUnit * num_total_compute_units;
                            hw_info.SetNumberSimds(num_total_simds);
                            if (num_total_simds == 0)
                            {
                                GpaLogger::Instance().LogError("Vulkan returned invalid number of SIMDs.");
                                status = kGpaStatusErrorHardwareNotSupported;
                            }

                            // NOTE: Vulkan is the only driver that allows us to query vgprsPerSimd from the driver itself.
                            // All other APIs utilize device_info as the source of truth.
                            const uint32_t num_total_vgprs = shader_core_properties_amd.vgprsPerSimd * num_total_simds;
                            hw_info.SetNumberVgprs(num_total_vgprs);
                            if (num_total_vgprs == 0)
                            {
                                GpaLogger::Instance().LogError("Vulkan returned invalid number of VGPRs.");
                                status = kGpaStatusErrorHardwareNotSupported;
                            }
                        }
                        else
                        {
                            GpaLogger::Instance().LogError("Unable to get device info from device_info library.");
                        }
                    }
                    else
                    {
                        GpaLogger::Instance().LogError("Unable to get timestamp frequency.");
                    }
                }
                else
                {
                    GpaLogger::Instance().LogError("Device is not supported for profiling.");
                }
            }
            else
            {
                GpaLogger::Instance().LogError("Unable to initialize Vulkan entrypoints.");
            }
        }
        else
        {
            GpaLogger::Instance().LogError("Unable to open context. Necessary member of 'context' is NULL.");
        }
    }
    else
    {
        GpaLogger::Instance().LogError("Unable to proceed. Parameter 'context' is NULL.");
    }

    return status;
}

bool VkGpaImplementor::VerifyApiHwSupport(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, const GpaHwInfo& hardware_info) const
{
    bool is_supported = false;
    UNREFERENCED_PARAMETER(hardware_info);
    if (nullptr != context_info)
    {
        PFN_vkGetDeviceProcAddr   get_device_proc_addr   = NULL;  ///< The vulkan device proc query.
        PFN_vkGetInstanceProcAddr get_instance_proc_addr = NULL;  ///< The vulkan instance proc query.

        if (flags & kGpaOpenContextVkUseInfoType2)
        {
            get_device_proc_addr   = (reinterpret_cast<GpaVkContextOpenInfo2*>(context_info))->get_device_proc_addr;
            get_instance_proc_addr = (reinterpret_cast<GpaVkContextOpenInfo2*>(context_info))->get_instance_proc_addr;
        }

        GpaVkContextOpenInfo* vk_context_info = static_cast<GpaVkContextOpenInfo*>(context_info);

        if (VK_NULL_HANDLE != vk_context_info->instance && VK_NULL_HANDLE != vk_context_info->physical_device && VK_NULL_HANDLE != vk_context_info->device)
        {
            // For Vulkan, the context contains the VkInstance.
            if (vk_utils::InitializeVkEntryPoints(vk_context_info->instance, vk_context_info->device, get_instance_proc_addr, get_device_proc_addr))
            {
                is_supported = vk_utils::IsDeviceSupportedForProfiling(vk_context_info->physical_device);
            }
            else
            {
                GpaLogger::Instance().LogError("Unable to initialize Vulkan entrypoints.");
            }
        }
        else
        {
            GpaLogger::Instance().LogError("Unable to open context. Necessary member of 'context' is NULL.");
        }
    }
    else
    {
        GpaLogger::Instance().LogError("Unable to proceed. Parameter 'context' is NULL.");
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

std::unique_ptr<IGpaContext> VkGpaImplementor::OpenApiContext(GpaContextInfoPtr context_info, const GpaHwInfo& hardware_info, GpaOpenContextFlags flags)
{
    std::unique_ptr<IGpaContext> gpa_context;
    GpaVkContextOpenInfo*        vk_context_info = static_cast<GpaVkContextOpenInfo*>(context_info);

    if (VK_NULL_HANDLE != vk_context_info->instance && VK_NULL_HANDLE != vk_context_info->physical_device && VK_NULL_HANDLE != vk_context_info->device)
    {
        vk_instance_ = vk_context_info->instance;

        if (vk_utils::IsDeviceSupportedForProfiling(vk_context_info->physical_device))
        {
            auto vk_gpa_context = std::make_unique<VkGpaContext>(vk_context_info, hardware_info, flags);

            GpaStatus status = vk_gpa_context->Open();

            if (kGpaStatusOk == status && vk_gpa_context->IsOpen())
            {
                gpa_context = std::move(vk_gpa_context);
            }
            else
            {
                GpaLogger::Instance().LogError("Unable to open a context.");
            }
        }
        else
        {
            GpaLogger::Instance().LogError("Unable to open a context, device is not supported.");
        }
    }
    else
    {
        GpaLogger::Instance().LogError("Unable to open context. Necessary member of 'context' is NULL.");
    }

    return gpa_context;
}

bool VkGpaImplementor::CloseApiContext(std::unique_ptr<IGpaContext> context)
{
    assert(context);

    VkGpaContext*   vk_gpa_context            = reinterpret_cast<VkGpaContext*>(context.get());
    const GpaStatus set_default_clocks_result = vk_gpa_context->SetStableClocks(false);
    if (set_default_clocks_result != kGpaStatusOk)
    {
        assert(!"Unable to set clocks back to default");
        GpaLogger::Instance().LogError("Unable to set clocks back to default");
    }
    // context destroyed when unique_ptr goes out of scope.

    return set_default_clocks_result == kGpaStatusOk;
}

GpaDeviceIdentifier VkGpaImplementor::GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const
{
    assert(nullptr != context_info);

    GpaVkContextOpenInfo* context_open_info = static_cast<GpaVkContextOpenInfo*>(context_info);
    return context_open_info->physical_device;
}
