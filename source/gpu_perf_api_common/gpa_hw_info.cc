//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  A class for managing hardware information.
//==============================================================================

#include "gpu_perf_api_common/gpa_hw_info.h"
#include "gpu_perf_api_common/logging.h"
#include "gpu_perf_api_common/gpa_hw_support.h"

#include <assert.h>
#include <cinttypes>
#include <string_view>
#include "device_info.hpp"

bool GpaHwInfo::GetDeviceId(GpaUInt32& id) const
{
    id = device_id_;
    return device_id_set_;
}

bool GpaHwInfo::IsUnsupportedDevice(const GpaApiType api, GpaDriverInfo const& driver_info) const
{
    if (const std::optional<device_info::AdapterId> device_description = GetDeviceDescription(); device_description.has_value())
    {
        return IsDeviceUnprofilable(*device_description, api, driver_info);
    }
    return true;
}

bool GpaHwInfo::GetRevisionId(GpaUInt32& id) const
{
    id = revision_id_;
    return revision_id_set_;
}

bool GpaHwInfo::GetVendorId(GpaUInt32& vendor_id) const
{
    vendor_id = vendor_id_;
    return vendor_id_set_;
}

bool GpaHwInfo::GetDeviceName(const char*& device_name) const
{
    device_name = device_name_.c_str();
    return device_name_set_;
}

bool GpaHwInfo::GetGpuIndex(unsigned int& gpu_index) const
{
    gpu_index = gpu_index_;
    return gpu_index_set_;
}

void GpaHwInfo::SetDeviceId(const GpaUInt32& id)
{
    device_id_set_ = true;
    device_id_     = id;
}

void GpaHwInfo::SetRevisionId(const GpaUInt32& id)
{
    revision_id_set_ = true;
    revision_id_     = id;
}

void GpaHwInfo::SetVendorId(const GpaUInt32& vendor_id)
{
    vendor_id_set_ = true;
    vendor_id_     = vendor_id;
}

void GpaHwInfo::SetDeviceName(const char* device_name)
{
    device_name_set_ = true;
    device_name_     = device_name;
}

void GpaHwInfo::SetGpuIndex(const unsigned int& gpu_index)
{
    gpu_index_set_ = true;
    gpu_index_     = gpu_index;
}

void GpaHwInfo::SetTimeStampFrequency(const GpaUInt64& frequency)
{
    timestamp_frequency_set_ = true;
    timestamp_frequency_     = frequency;
}

void GpaHwInfo::SetNumberSimds(const GpaUInt32 num_simd)
{
    num_simd_set_ = true;
    num_simd_     = num_simd;
}

void GpaHwInfo::SetNumberCus(const GpaUInt32 num_cu)
{
    num_cu_set_ = true;
    num_cu_     = num_cu;
}

void GpaHwInfo::SetWavesPerSimd(const GpaUInt32 numWaves)
{
    num_waves_per_simd_set_ = true;
    num_waves_per_simd_     = numWaves;
}

void GpaHwInfo::SetNumberShaderEngines(const GpaUInt32 num_se)
{
    num_shader_engines_set_ = true;
    num_shader_engines_     = num_se;
}

void GpaHwInfo::SetNumberShaderArrays(const GpaUInt32 num_sa)
{
    num_shader_arrays_set_ = true;
    num_shader_arrays_     = num_sa;
}

void GpaHwInfo::SetSuClocksPrim(const GpaUInt32 su_clock_primitives)
{
    su_clock_prim_set_ = true;
    su_clock_prim_     = su_clock_primitives;
}

void GpaHwInfo::SetNumberPrimPipes(const GpaUInt32 num_primitive_pipes)
{
    num_prim_pipes_set_ = true;
    num_prim_pipes_     = num_primitive_pipes;
}

void GpaHwInfo::SetNumberVgprs(const GpaUInt32 num_vgpr)
{
    num_vgpr_set_ = true;
    num_vgpr_     = num_vgpr;
}

bool GpaHwInfo::UpdateDeviceInfoBasedOnDeviceDescription()
{
    const std::optional<device_info::AdapterId> adapter_id = GetDeviceDescription();

    if (!adapter_id.has_value())
    {
        GpaLogger::Instance().LogError("Device description is not set; cannot update device info.");
        return false;
    }

    const std::optional<device_info::CardInfo> card_info = device_info::GetCardInfo(*adapter_id);
    if (!card_info.has_value())
    {
        GpaLogger::Instance().LogError("Failed to get card info based on device description.");
        return false;
    }

    const std::optional<device_info::DeviceInfo> dev_info = device_info::GetDeviceInfo(*card_info);
    if (!dev_info.has_value())
    {
        GpaLogger::Instance().LogError("Failed to get device info based on card info.");
        return false;
    }

    if (!num_shader_engines_set_)
    {
        SetNumberShaderEngines(static_cast<GpaUInt32>(dev_info->num_shader_engines));
    }

    if (!num_shader_arrays_set_)
    {
        SetNumberShaderArrays(static_cast<GpaUInt32>(device_info::TotalShaderArrays(*dev_info)));
    }

    if (!num_cu_set_)
    {
        SetNumberCus(static_cast<GpaUInt32>(dev_info->num_cus));
    }

    if (!num_simd_set_)
    {
        SetNumberSimds(static_cast<GpaUInt32>(device_info::TotalSimds(*dev_info)));
    }

    if (!su_clock_prim_set_)
    {
        SetSuClocksPrim(static_cast<GpaUInt32>(dev_info->clocks_per_primitive));
    }

    if (!num_waves_per_simd_set_)
    {
        SetWavesPerSimd(static_cast<GpaUInt32>(dev_info->max_wave_per_simd));
    }

    if (!num_prim_pipes_set_)
    {
        SetNumberPrimPipes(static_cast<GpaUInt32>(dev_info->num_prim_pipes));
    }

    if (!num_vgpr_set_)
    {
        SetNumberVgprs(static_cast<GpaUInt32>(device_info::TotalVgprs(*dev_info)));
    }

    if (!num_lds_bytes_.has_value())
    {
        num_lds_bytes_ = device_info::GetTotalLdsSizeInBytes(card_info->generation, *dev_info);
    }

    if (!max_sq_counters_.has_value() && dev_info->num_sq_counters > 0)
    {
        max_sq_counters_ = dev_info->num_sq_counters;
    }

    asic_type_ = card_info->asic_type;
    SetDeviceName(card_info->marketing_name);

    if (!generation_.has_value())
    {
        generation_ = card_info->generation;
    }

    return true;
}
