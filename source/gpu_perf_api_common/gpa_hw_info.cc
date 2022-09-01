//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  A class for managing hardware information.
//==============================================================================

#include "gpu_perf_api_common/gpa_hw_info.h"

#include <assert.h>

#include <DeviceInfoUtils.h>

#include "gpu_perf_api_common/logging.h"

GpaHwInfo::GpaHwInfo()
    : device_id_(0)
    , device_id_set_(false)
    , revision_id_(0)
    , revision_id_set_(false)
    , vendor_id_(0)
    , vendor_id_set_(false)
    , device_name_set_(false)
    , gpu_index_(0)
    , gpu_index_set_(false)
    , generation_(GDT_HW_GENERATION_NONE)
    , generation_set_(false)
    , timestamp_frequency_(1)
    , timestamp_frequency_set_(false)
    , num_simd_(0)
    , num_simd_set_(false)
    , num_cu_(0)
    , num_cu_set_(false)
    , asic_type_(GDT_ASIC_TYPE_NONE)
    , num_shader_engines_(0)
    , num_shader_engines_set_(false)
    , num_shader_arrays_(0)
    , num_shader_arrays_set_(false)
    , su_clock_prim_(0)
    , su_clock_prim_set_(false)
    , num_prim_pipes_(0)
    , num_prim_pipes_set_(false)
{
}

bool GpaHwInfo::GetDeviceId(GpaUInt32& id) const
{
    id = device_id_;
    return device_id_set_;
}

bool GpaHwInfo::GetRevisionId(GpaUInt32& id) const
{
    id = revision_id_;
    return revision_id_set_;
}

bool GpaHwInfo::GetVendorId(GpaUInt32& vid) const
{
    vid = vendor_id_;
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

bool GpaHwInfo::GetHwGeneration(GDT_HW_GENERATION& gen) const
{
    gen = generation_;
    return generation_set_;
}

bool GpaHwInfo::GetHwAsicType(GDT_HW_ASIC_TYPE& type) const
{
    type = asic_type_;
    return asic_type_ != GDT_ASIC_TYPE_NONE;
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

void GpaHwInfo::SetVendorId(const GpaUInt32& vid)
{
    vendor_id_set_ = true;
    vendor_id_     = vid;
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

void GpaHwInfo::SetHwGeneration(const GDT_HW_GENERATION& generation)
{
    generation_set_ = true;
    generation_     = generation;
}

void GpaHwInfo::SetTimeStampFrequency(const GpaUInt64& frequency)
{
    timestamp_frequency_set_ = true;
    timestamp_frequency_     = frequency;
}

void GpaHwInfo::SetNumberSimds(const size_t& num_simd)
{
    num_simd_set_ = true;
    num_simd_     = num_simd;
}

void GpaHwInfo::SetNumberCus(const size_t& num_cu)
{
    num_cu_set_ = true;
    num_cu_     = num_cu;
}

void GpaHwInfo::SetNumberShaderEngines(const size_t& num_se)
{
    num_shader_engines_set_ = true;
    num_shader_engines_     = num_se;
}

void GpaHwInfo::SetNumberShaderArrays(const size_t& num_sa)
{
    num_shader_arrays_set_ = true;
    num_shader_arrays_     = num_sa;
}

void GpaHwInfo::SetSuClocksPrim(const size_t& su_clock_primitives)
{
    su_clock_prim_set_ = true;
    su_clock_prim_     = su_clock_primitives;
}

void GpaHwInfo::SetNumberPrimPipes(const size_t& num_primitive_pipes)
{
    num_prim_pipes_set_ = true;
    num_prim_pipes_     = num_primitive_pipes;
}

bool GpaHwInfo::UpdateDeviceInfoBasedOnDeviceId()
{
    std::vector<GDT_GfxCardInfo> card_list;
    GDT_GfxCardInfo              card_info         = {};
    GDT_DeviceInfo               device_info       = {};
    bool                         device_info_found = false;

    if (device_name_set_)
    {
        if (AMDTDeviceInfoUtils::Instance()->GetAllCardsWithDeviceId(device_id_, card_list))
        {
            for (auto it = card_list.begin(); it != card_list.end(); ++it)
            {
                if (revision_id_set_ && revision_id_ != REVISION_ID_ANY && it->m_revID != revision_id_)
                {
                    continue;
                }

                // First check for CAL name matches.
                std::string this_cal_name(it->m_szCALName);

                if (0 == this_cal_name.compare(device_name_))
                {
                    card_info = *it;

                    if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(it->m_szCALName, device_info))
                    {
                        device_info_found = true;
                        break;
                    }
                }

                // Next check for marketing name matches.
                std::string this_marketing_name(it->m_szMarketingName);

                if (0 == this_marketing_name.compare(device_name_))
                {
                    card_info = *it;

                    if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(card_info.m_deviceID, card_info.m_revID, device_info))
                    {
                        device_info_found = true;
                        break;
                    }
                }
            }
        }
    }

    if (!device_info_found)
    {
        if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(device_id_, revision_id_, card_info))
        {
            GPA_LOG_DEBUG_MESSAGE("Found device ID: %X which is generation %d.", card_info.m_deviceID, card_info.m_generation);

            if (AMDTDeviceInfoUtils::Instance()->GetDeviceInfo(device_id_, revision_id_, device_info))
            {
                device_info_found = true;
            }
        }
    }

    if (device_info_found)
    {
        if (!num_shader_engines_set_)
        {
            SetNumberShaderEngines(device_info.m_nNumShaderEngines);
        }

        if (!num_shader_arrays_set_)
        {
            SetNumberShaderArrays(device_info.numberSHs());
        }

        if (!num_cu_set_)
        {
            SetNumberCus(device_info.numberCUs());
        }

        if (!num_simd_set_)
        {
            SetNumberSimds(device_info.numberSIMDs());
        }

        if (!su_clock_prim_set_)
        {
            SetSuClocksPrim(device_info.m_suClocksPrim);
        }

        if (!num_prim_pipes_set_)
        {
            SetNumberPrimPipes(device_info.m_nNumPrimPipes);
        }

        asic_type_ = card_info.m_asicType;
        SetDeviceName(card_info.m_szMarketingName);
        SetHwGeneration(card_info.m_generation);
        return true;
    }

    // Only emit an error for AMD devices.
    if (IsAmdOrSamsung())
    {
        std::stringstream ss;
        ss << "Unrecognized device ID: " << device_id_ << ".";
        GPA_LOG_ERROR(ss.str().c_str());
    }

    return false;
}

bool GpaHwInfo::UpdateRevisionIdBasedOnDeviceIdAndName()
{
    std::vector<GDT_GfxCardInfo> card_list;

    if (device_name_set_)
    {
        if (AMDTDeviceInfoUtils::Instance()->GetAllCardsWithDeviceId(device_id_, card_list))
        {
            // First check for exact matches.
            for (auto it = card_list.begin(); it != card_list.end(); ++it)
            {
                std::string this_marketing_name(it->m_szMarketingName);

                if (0 == this_marketing_name.compare(device_name_))
                {
                    SetRevisionId(static_cast<GpaUInt32>(it->m_revID));
                    return true;
                }
            }

            // If no exact match is found, try a substring match (first part of string should match marketing name).
            for (auto it = card_list.begin(); it != card_list.end(); ++it)
            {
                std::string this_marketing_name(it->m_szMarketingName);

                if (0 == device_name_.find(this_marketing_name))
                {
                    SetRevisionId(static_cast<GpaUInt32>(it->m_revID));
                    return true;
                }
            }
        }
    }

    SetRevisionId(REVISION_ID_ANY);
    return false;
}

bool GpaHwInfo::UpdateDeviceInfoBasedOnAsicTypeAndName(GDT_HW_ASIC_TYPE asic_type)
{
    std::vector<GDT_GfxCardInfo> card_list;

    if (device_name_set_)
    {
        if (AMDTDeviceInfoUtils::Instance()->GetAllCardsWithAsicType(asic_type, card_list))
        {
            // First check for exact matches.
            for (auto it = card_list.begin(); it != card_list.end(); ++it)
            {
                std::string this_marketing_name(it->m_szMarketingName);

                if (0 == this_marketing_name.compare(device_name_))
                {
                    SetDeviceId(static_cast<GpaUInt32>(it->m_deviceID));
                    SetRevisionId(static_cast<GpaUInt32>(it->m_revID));
                    return true;
                }
            }

            // If no exact match is found, try a substring match (first part of string should match marketing name).
            for (auto it = card_list.begin(); it != card_list.end(); ++it)
            {
                std::string this_marketing_name(it->m_szMarketingName);

                if (0 == device_name_.find(this_marketing_name))
                {
                    SetDeviceId(static_cast<GpaUInt32>(it->m_deviceID));
                    SetRevisionId(static_cast<GpaUInt32>(it->m_revID));
                    return true;
                }
            }
        }
    }

    // If a match has not been found, try to match using the already set device id.
    return UpdateRevisionIdBasedOnDeviceIdAndName();
}

bool GpaHwInfo::operator==(GpaHwInfo other_hw_info) const
{
    bool is_same = false;

    if (!vendor_id_set_)
    {
        GPA_LOG_ERROR("Failed to get vendor Id.");
    }
    else if (!device_id_set_)
    {
        GPA_LOG_ERROR("Failed to get device Id.");
    }
    else if (!revision_id_set_)
    {
        GPA_LOG_ERROR("Failed to get revision Id.");
    }
    else if (vendor_id_ != other_hw_info.vendor_id_)
    {
        GPA_LOG_DEBUG_ERROR("Vendor ID mismatch.");
    }
    else if (device_id_ != other_hw_info.device_id_)
    {
        GPA_LOG_DEBUG_ERROR("Device Id Mismatch.");
    }
    else if (revision_id_ != REVISION_ID_ANY && other_hw_info.revision_id_ != REVISION_ID_ANY && revision_id_ != other_hw_info.revision_id_)
    {
        GPA_LOG_DEBUG_ERROR("Revision Id Mismatch.");
    }
    else
    {
        is_same = true;
    }

    return is_same;
}
