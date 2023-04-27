//==============================================================================
// Copyright (c) 2016-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Base class for counter generation.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator_base.h"

GpaCounterGeneratorBase::GpaCounterGeneratorBase()
    : do_allow_public_counters_(false)
    , do_allow_hardware_counters_(false)
    , do_allow_hardware_exposed_counters_(false)
{
}

void GpaCounterGeneratorBase::SetAllowedCounters(bool allow_public_counters, bool allow_hardware_counters)
{
    do_allow_public_counters_ = allow_public_counters;

    do_allow_hardware_counters_         = false;
    do_allow_hardware_exposed_counters_ = allow_hardware_counters;
}

GpaStatus GpaCounterGeneratorBase::GenerateCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GpaUInt8 generate_asic_specific_counters)
{
    GpaStatus status = kGpaStatusErrorNotEnabled;

    public_counters_.Clear();
    hardware_counters_.Clear();

    if (do_allow_public_counters_)
    {
        status = GeneratePublicCounters(desired_generation, asic_type, generate_asic_specific_counters, &public_counters_);

        if (status != kGpaStatusOk)
        {
            GPA_LOG_ERROR("Failed to generate public counters.");
            return status;
        }
    }

    // Hw counters are required if generating public counters.
    if (do_allow_public_counters_ || do_allow_hardware_counters_ || do_allow_hardware_exposed_counters_)
    {
        status = GenerateHardwareCounters(desired_generation, asic_type, generate_asic_specific_counters, &hardware_counters_);

        if (status != kGpaStatusOk)
        {
            GPA_LOG_ERROR("Failed to generate hardware counters.");
            return status;
        }
    }

    if (!do_allow_hardware_counters_ && do_allow_hardware_exposed_counters_)
    {
        status = GenerateHardwareExposedCounters(desired_generation, asic_type, generate_asic_specific_counters, &hardware_counters_);

        if (status != kGpaStatusOk)
        {
            GPA_LOG_ERROR("Failed to generate hardware exposed counters.");
            return status;
        }
    }

    if (0 == GetNumCounters())
    {
        // No counters reported, return hardware not supported.
        GPA_LOG_ERROR("No counters were available to expose.");
        status = kGpaStatusErrorHardwareNotSupported;
    }

    return status;
}

GpaUInt32 GpaCounterGeneratorBase::GetNumCounters() const
{
    GpaUInt32 count = 0;

    if (do_allow_public_counters_)
    {
        count += public_counters_.GetNumCounters();
    }

    if (do_allow_hardware_counters_)
    {
        count += hardware_counters_.GetNumCounters();
    }
    else if (do_allow_hardware_exposed_counters_)
    {
        count += hardware_counters_.GetNumHardwareExposedCounters();
    }

    return count;
}

GpaUInt32 GpaCounterGeneratorBase::GetNumAmdCounters() const
{
    // To be used for SW D3D counters for AMD.
    GpaUInt32 count = 0;

    if (do_allow_public_counters_)
    {
        count += public_counters_.GetNumCounters();
    }

    if (do_allow_hardware_counters_)
    {
        count += hardware_counters_.GetNumCounters();
    }
    else if (do_allow_hardware_exposed_counters_)
    {
        count += hardware_counters_.GetNumHardwareExposedCounters();
    }

    return count;
}

GpaStatus GpaCounterGeneratorBase::GenerateHardwareExposedCounters(GDT_HW_GENERATION    desired_generation,
                                                                   GDT_HW_ASIC_TYPE     asic_type,
                                                                   GpaUInt8             generate_asic_specific_counters,
                                                                   GpaHardwareCounters* hardware_counters)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);
    UNREFERENCED_PARAMETER(hardware_counters);
    return kGpaStatusOk;
}

bool GpaCounterGeneratorBase::MapHardwareExposedCounter(GpaHardwareCounters* hardware_counters)
{
    bool success = true;

    if (nullptr == hardware_counters)
    {
        return !success;
    }

    hardware_counters->hardware_exposed_counters_list_.clear();
    for (unsigned int g = 0; g < hardware_counters->hardware_exposed_counter_group_count_; g++)
    {
        const GpaUInt32 block_counter_start_index = hardware_counters->hardware_exposed_counter_groups_[g].hardware_block_start_index;

        unsigned int count_iter = 0;
        for (auto iter = hardware_counters->hardware_exposed_counter_groups_[g].white_list_counters.cbegin();
             iter != hardware_counters->hardware_exposed_counter_groups_[g].white_list_counters.cend();
             ++iter)
        {
            GpaHardwareCounterDesc* whitelist_counter = &hardware_counters->hardware_exposed_counters_.at(g)->at(count_iter);
            hardware_counters->hardware_exposed_counters_list_.push_back(*whitelist_counter);
            unsigned int global_counter_index = block_counter_start_index + *iter;
            hardware_counters->hardware_exposed_counter_internal_indices_list_.push_back(global_counter_index);
            hardware_counters->hardware_counters_[global_counter_index].hardware_counters = whitelist_counter;
            count_iter++;
        }
    }

    return success;
}

const char* GpaCounterGeneratorBase::GetCounterName(GpaUInt32 index) const
{
    if (do_allow_public_counters_)
    {
        if (index < public_counters_.GetNumCounters())
        {
            return public_counters_.GetCounterName(index);
        }

        index -= public_counters_.GetNumCounters();
    }

    if (do_allow_hardware_counters_)
    {
        if (index < hardware_counters_.GetNumCounters())
        {
            return hardware_counters_.GetCounterName(index);
        }

        index -= hardware_counters_.GetNumCounters();
    }
    else if (do_allow_hardware_exposed_counters_)
    {
        if (index < hardware_counters_.GetNumHardwareExposedCounters())
        {
            return hardware_counters_.GetHardwareExposedCounterName(index);
        }

        index -= hardware_counters_.GetNumHardwareExposedCounters();
    }

    return nullptr;
}

bool GpaCounterGeneratorBase::GetCounterIndex(const char* counter_name, GpaUInt32* counter_index) const
{
    bool ret_val                = false;
    bool counter_found_in_cache = false;

    if (nullptr == counter_index)
    {
        return false;
    }

    CounterNameIndexMap::const_iterator it = counter_index_cache_.find(counter_name);

    if (counter_index_cache_.end() != it)
    {
        *counter_index         = counter_index_cache_[counter_name];
        counter_found_in_cache = true;
        ret_val                = kCounterNotFound != *counter_index;
    }

    if (!counter_found_in_cache)
    {
        GpaUInt32 num_counters = GetNumCounters();

        for (GpaUInt32 i = 0; i < num_counters; i++)
        {
            const char* temp_counter_name = GetCounterName(i);

            if (0 == _strcmpi(counter_name, temp_counter_name))
            {
                counter_index_cache_[counter_name] = i;
                *counter_index                     = i;
                ret_val                            = true;
                break;
            }
        }

        if (!ret_val)
        {
            // Cache the fact that it wasn't found.
            counter_index_cache_[counter_name] = kCounterNotFound;
        }
    }

    return ret_val;
}

bool GpaCounterGeneratorBase::GetCounterIndex(const GpaHwBlock&    gpa_hardware_block,
                                              const GpaUInt32&     block_instance,
                                              const GpaUInt32&     block_event_id,
                                              const GpaShaderMask& gpa_shader_mask,
                                              GpaUInt32*           counter_index) const
{
    GpaUInt32 ret_counter_index = 0u;
    bool      counter_found     = false;

    if (do_allow_public_counters_)
    {
        ret_counter_index += public_counters_.GetNumCounters();
    }

    GpaUInt32 hardware_counter_index = 0u;

    if (do_allow_hardware_counters_ || do_allow_hardware_exposed_counters_)
    {
        if (hardware_counters_.GetIndex(gpa_hardware_block, block_instance, block_event_id, gpa_shader_mask, &hardware_counter_index))
        {
            counter_found = true;
        }
    }

    if (counter_found && do_allow_hardware_counters_)
    {
        ret_counter_index += hardware_counter_index;
        *counter_index = ret_counter_index;
    }
    else if (counter_found && do_allow_hardware_exposed_counters_)
    {
        GpaUInt32 exposed_counter_index = 0u;
        if (hardware_counters_.GetHardwareExposedCounterIndex(hardware_counter_index, exposed_counter_index))
        {
            ret_counter_index += exposed_counter_index;
            *counter_index = ret_counter_index;
        }
        else
        {
            counter_found = false;
        }
    }

    return counter_found;
}

bool GpaCounterGeneratorBase::GetPublicInterfaceCounterIndex(const GpaUInt32& hardware_counter_index, GpaUInt32* public_interface_counter_index) const
{
    if (!do_allow_hardware_counters_ && !do_allow_public_counters_ && !do_allow_hardware_exposed_counters_)
    {
        return false;
    }

    GpaUInt32 ret_counter_index = hardware_counter_index;

    if (!do_allow_hardware_counters_ && do_allow_hardware_exposed_counters_)
    {
        hardware_counters_.GetHardwareExposedCounterIndex(ret_counter_index, ret_counter_index);
    }

    if (do_allow_public_counters_)
    {
        ret_counter_index += public_counters_.GetNumCounters();
    }

    *public_interface_counter_index = ret_counter_index;
    return true;
}

const char* GpaCounterGeneratorBase::GetCounterGroup(GpaUInt32 index) const
{
    if (do_allow_public_counters_)
    {
        if (index < public_counters_.GetNumCounters())
        {
            return public_counters_.GetCounterGroup(index);
        }

        index -= public_counters_.GetNumCounters();
    }

    if (do_allow_hardware_counters_)
    {
        if (index < hardware_counters_.GetNumCounters())
        {
            return hardware_counters_.GetCounterGroup(index);
        }

        index -= hardware_counters_.GetNumCounters();
    }
    else if (do_allow_hardware_exposed_counters_)
    {
        if (index < hardware_counters_.GetNumHardwareExposedCounters())
        {
            return hardware_counters_.GetHardwareExposedCounterGroup(index);
        }

        index -= hardware_counters_.GetNumHardwareExposedCounters();
    }

    return nullptr;
}

const char* GpaCounterGeneratorBase::GetCounterDescription(GpaUInt32 index) const
{
    if (do_allow_public_counters_)
    {
        if (index < public_counters_.GetNumCounters())
        {
            return public_counters_.GetCounterDescription(index);
        }
        else
        {
            index -= public_counters_.GetNumCounters();
        }
    }

    if (do_allow_hardware_counters_)
    {
        if (index < hardware_counters_.GetNumCounters())
        {
            return hardware_counters_.GetCounterDescription(index);
        }

        index -= hardware_counters_.GetNumCounters();
    }
    else if (do_allow_hardware_exposed_counters_)
    {
        if (index < hardware_counters_.GetNumHardwareExposedCounters())
        {
            return hardware_counters_.GetHardwareExposedCounterDescription(index);
        }

        index -= hardware_counters_.GetNumHardwareExposedCounters();
    }

    return nullptr;
}

GpaDataType GpaCounterGeneratorBase::GetCounterDataType(GpaUInt32 index) const
{
    if (do_allow_public_counters_)
    {
        if (index < public_counters_.GetNumCounters())
        {
            return public_counters_.GetCounterDataType(index);
        }

        index -= public_counters_.GetNumCounters();
    }

    if (do_allow_hardware_counters_)
    {
        if (index < hardware_counters_.GetNumCounters())
        {
            // Hardware counters are always 'uint64'.
            return kGpaDataTypeUint64;
        }

        index -= hardware_counters_.GetNumCounters();
    }
    else if (do_allow_hardware_exposed_counters_)
    {
        if (index < hardware_counters_.GetNumCounters())
        {
            // Hardware counters are always 'uint64'.
            return kGpaDataTypeUint64;
        }

        index -= hardware_counters_.GetNumHardwareExposedCounters();
    }

    return kGpaDataTypeUint64;
}

GpaUsageType GpaCounterGeneratorBase::GetCounterUsageType(GpaUInt32 index) const
{
    if (do_allow_public_counters_)
    {
        if (index < public_counters_.GetNumCounters())
        {
            return public_counters_.GetCounterUsageType(index);
        }
        else
        {
            index -= public_counters_.GetNumCounters();
        }
    }

    if (do_allow_hardware_counters_)
    {
        if (index < hardware_counters_.GetNumCounters())
        {
            // Hardware counters are always 'items'.
            return kGpaUsageTypeItems;
        }

        index -= hardware_counters_.GetNumCounters();
    }
    else if (do_allow_hardware_exposed_counters_)
    {
        if (index < hardware_counters_.GetNumCounters())
        {
            // Hardware counters are always 'items'.
            return kGpaUsageTypeItems;
        }

        index -= hardware_counters_.GetNumHardwareExposedCounters();
    }

    return kGpaUsageTypeItems;
}

GpaUuid GpaCounterGeneratorBase::GetCounterUuid(GpaUInt32 index) const
{
    if (do_allow_public_counters_)
    {
        if (index < public_counters_.GetNumCounters())
        {
            return public_counters_.GetCounterUuid(index);
        }
        else
        {
            index -= public_counters_.GetNumCounters();
        }
    }

    if (do_allow_hardware_counters_)
    {
        if (index < hardware_counters_.GetNumCounters())
        {
            return hardware_counters_.GetCounterUuid(index);
        }

        index -= hardware_counters_.GetNumCounters();
    }
    else if (do_allow_hardware_exposed_counters_)
    {
        if (index < hardware_counters_.GetNumHardwareExposedCounters())
        {
            return hardware_counters_.GetHardwareExposedCounterUuid(index);
        }

        index -= hardware_counters_.GetNumHardwareExposedCounters();
    }

    return GpaUuid{};
}

GpaCounterSampleType GpaCounterGeneratorBase::GetCounterSampleType(GpaUInt32 index) const
{
    if (do_allow_public_counters_)
    {
        if (index < public_counters_.GetNumCounters())
        {
            return public_counters_.GetCounterSampleType(index);
        }
        else
        {
            index -= public_counters_.GetNumCounters();
        }
    }

    if (do_allow_hardware_counters_)
    {
        if (index < hardware_counters_.GetNumCounters())
        {
            return hardware_counters_.GetCounterSampleType(index);
        }

        index -= hardware_counters_.GetNumCounters();
    }
    else if (do_allow_hardware_exposed_counters_)
    {
        if (index < hardware_counters_.GetNumHardwareExposedCounters())
        {
            return hardware_counters_.GetHardwareExposedCounterSampleType(index);
        }

        index -= hardware_counters_.GetNumHardwareExposedCounters();
    }

    return kGpaCounterSampleTypeDiscrete;
}

const GpaDerivedCounterInfoClass* GpaCounterGeneratorBase::GetPublicCounter(GpaUInt32 index) const
{
    return public_counters_.GetCounter(index);
}

const GpaHardwareCounterDescExt* GpaCounterGeneratorBase::GetHardwareCounterExt(GpaUInt32 index) const
{
    return &(hardware_counters_.hardware_counters_.at(index));
}

GpaUInt32 GpaCounterGeneratorBase::GetNumPublicCounters() const
{
    GpaUInt32 count = 0;

    if (do_allow_public_counters_)
    {
        count += public_counters_.GetNumCounters();
    }

    return count;
}

std::vector<GpaUInt32> GpaCounterGeneratorBase::GetInternalCountersRequired(GpaUInt32 index) const
{
    if (do_allow_public_counters_)
    {
        if (index < public_counters_.GetNumCounters())
        {
            return public_counters_.GetInternalCountersRequired(index);
        }
        else
        {
            index -= public_counters_.GetNumCounters();
        }
    }

    std::vector<GpaUInt32> vec_internal_counters;

    if (do_allow_hardware_counters_)
    {
        if (index < hardware_counters_.GetNumCounters())
        {
            // The index is now the same as the needed hardware counter.
            vec_internal_counters.push_back(index);
            return vec_internal_counters;
        }

        index -= hardware_counters_.GetNumCounters();
    }
    else if (do_allow_hardware_exposed_counters_)
    {
        if (index < hardware_counters_.GetNumHardwareExposedCounters())
        {
            // The index is now the same as the needed hardware counter.
            vec_internal_counters.push_back(hardware_counters_.GetHardwareExposedCounterInternalIndex(index));
            return vec_internal_counters;
        }

        index -= hardware_counters_.GetNumHardwareExposedCounters();
    }

    return vec_internal_counters;
}

GpaStatus GpaCounterGeneratorBase::ComputePublicCounterValue(GpaUInt32                       counter_index,
                                                             const vector<const GpaUInt64*>& results,
                                                             vector<GpaDataType>&            internal_counter_types,
                                                             void*                           result,
                                                             const GpaHwInfo*                hardware_info) const
{
    return public_counters_.ComputeCounterValue(counter_index, results, internal_counter_types, result, hardware_info);
}

void GpaCounterGeneratorBase::ComputeSwCounterValue(GpaUInt32 software_counter_index, GpaUInt64 value, void* result, const GpaHwInfo* hardware_info) const
{
    UNREFERENCED_PARAMETER(software_counter_index);
    UNREFERENCED_PARAMETER(hardware_info);

    if (nullptr != result)
    {
        GpaUInt64* ret_value = static_cast<GpaUInt64*>(result);
        *ret_value           = value;
    }
}

const GpaHardwareCounters* GpaCounterGeneratorBase::GetHardwareCounters() const
{
    return &hardware_counters_;
}

GpaCounterInfo* GpaCounterGeneratorBase::GetCounterInfo(const GpaUInt32& counter_index) const
{
    GpaUInt32 internal_counter_index = counter_index;
    if (do_allow_public_counters_)
    {
        if (internal_counter_index > public_counters_.GetNumCounters())
        {
            internal_counter_index -= public_counters_.GetNumCounters();
        }
        else
        {
            GpaDerivedCounterInfoClass* derived_counter = const_cast<GpaDerivedCounterInfoClass*>(GetPublicCounter(counter_index));

            if (nullptr != derived_counter)
            {
                return derived_counter->GetCounterInfo(this);
            }
        }
    }

    if (do_allow_hardware_counters_ && internal_counter_index < hardware_counters_.GetNumCounters())
    {
        return hardware_counters_.GetCounterInfo(internal_counter_index);
    }

    if (do_allow_hardware_exposed_counters_ && internal_counter_index < hardware_counters_.GetNumCounters())
    {
        const GpaUInt32 exposed_counter_index = hardware_counters_.GetHardwareExposedCounterInternalIndex(internal_counter_index);
        return hardware_counters_.GetCounterInfo(exposed_counter_index);
    }

    return nullptr;
}

GpaCounterSourceInfo GpaCounterGeneratorBase::GetCounterSourceInfo(GpaUInt32 global_index) const
{
    GpaCounterSourceInfo info = GpaCounterSourceInfo();

    if (do_allow_public_counters_)
    {
        if (global_index < public_counters_.GetNumCounters())
        {
            info.Set(global_index, GpaCounterSource::kPublic);
            return info;
        }

        global_index -= public_counters_.GetNumCounters();
    }

    if (do_allow_hardware_counters_)
    {
        if (global_index < hardware_counters_.GetNumCounters())
        {
            info.Set(global_index, GpaCounterSource::kHardware);
            return info;
        }

        global_index -= hardware_counters_.GetNumCounters();
    }
    else if (do_allow_hardware_exposed_counters_)
    {
        if (global_index < hardware_counters_.GetNumHardwareExposedCounters())
        {
            info.Set(global_index, GpaCounterSource::kHardware);
            return info;
        }

        global_index -= hardware_counters_.GetNumHardwareExposedCounters();
    }

    // Unknown counter.
    info.Set(global_index, GpaCounterSource::kUnknown);
    return info;
}
