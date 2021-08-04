//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Base class for counter generation.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator_base.h"

GpaCounterGeneratorBase::GpaCounterGeneratorBase()
    : do_allow_public_counters_(false)
    , do_allow_hardware_counters_(false)
    , do_allow_software_counters_(false)
    , do_allow_hardware_exposed_counters_(false)
{
}

void GpaCounterGeneratorBase::SetAllowedCounters(bool allow_public_counters, bool allow_hardware_counters, bool allow_software_counters)
{
    do_allow_public_counters_ = allow_public_counters;

#ifdef AMDT_INTERNAL
    // Only allow HW counters for internal builds.
    do_allow_hardware_counters_         = allow_hardware_counters;
    do_allow_hardware_exposed_counters_ = false;
#else
    UNREFERENCED_PARAMETER(allow_hardware_counters);
    // Force HW counters to OFF for non internal builds.
    do_allow_hardware_counters_         = false;
    do_allow_hardware_exposed_counters_ = allow_hardware_counters;
#endif

    do_allow_software_counters_ = allow_software_counters;
}

GpaStatus GpaCounterGeneratorBase::GenerateCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GpaUInt8 generate_asic_specific_counters)
{
    GpaStatus status = kGpaStatusErrorNotEnabled;

    public_counters_.Clear();
    hardware_counters_.Clear();
    software_counters_.Clear();

    if (do_allow_public_counters_)
    {
        status = GeneratePublicCounters(desired_generation, asic_type, generate_asic_specific_counters, &public_counters_);

        if (status != kGpaStatusOk)
        {
            return status;
        }
    }

    // Hw counters are required if generating public counters.
    if (do_allow_public_counters_ || do_allow_hardware_counters_ || do_allow_hardware_exposed_counters_)
    {
        status = GenerateHardwareCounters(desired_generation, asic_type, generate_asic_specific_counters, &hardware_counters_);

        if (status != kGpaStatusOk)
        {
            return status;
        }
    }

    if (!do_allow_hardware_counters_ && do_allow_hardware_exposed_counters_)
    {
        status = GenerateHardwareExposedCounters(desired_generation, asic_type, generate_asic_specific_counters, &hardware_counters_);

        if (status != kGpaStatusOk)
        {
            return status;
        }
    }

    if (do_allow_software_counters_)
    {
        status = GenerateSoftwareCounters(desired_generation, asic_type, generate_asic_specific_counters, &software_counters_);

        if (status != kGpaStatusOk)
        {
            return status;
        }
    }

    if (0 == GetNumCounters())
    {
        // No counters reported, return hardware not supported.
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

    if (do_allow_software_counters_)
    {
        count += software_counters_.GetNumCounters();
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
            GpaHardwareCounterDesc* whitelist_counter = hardware_counters->hardware_exposed_counters_[g] + count_iter;
            hardware_counters->hardware_exposed_counters_list_.push_back(*whitelist_counter);
            hardware_counters->hardware_exposed_counter_internal_indices_list_.push_back(block_counter_start_index + (*iter));
            hardware_counters->hardware_counters_[block_counter_start_index + (*iter)].hardware_counters = whitelist_counter;
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

    if (do_allow_software_counters_)
    {
        if (index < software_counters_.GetNumCounters())
        {
            return software_counters_.GetCounterName(index);
        }
    }

    return nullptr;
}

#ifdef AMDT_INTERNAL
bool GpaCounterGeneratorBase::SetCounterName(GpaUInt32 index, const char* counter_name)
{
    if (do_allow_public_counters_)
    {
        if (index < public_counters_.GetNumCounters())
        {
            return false;  // Not allowed to change name of derived counters.
        }

        index -= public_counters_.GetNumCounters();
    }

    if (do_allow_hardware_counters_)
    {
        if (index < hardware_counters_.GetNumCounters())
        {
            return hardware_counters_.SetCounterName(index, counter_name);
        }

        index -= hardware_counters_.GetNumCounters();
    }
    else if (do_allow_hardware_exposed_counters_)
    {
        if (index < hardware_counters_.GetNumHardwareExposedCounters())
        {
            return false;  // Not allowed to change name of exposed hardware counters.
        }

        index -= hardware_counters_.GetNumHardwareExposedCounters();
    }

    if (do_allow_software_counters_)
    {
        if (index < software_counters_.GetNumCounters())
        {
            return false;  // Not allowed to change name of derived counters.
        }
    }

    return false;
}

GpaStatus GpaCounterGeneratorBase::GenerateInternalDerivedCounters(GDT_HW_GENERATION   desired_generation,
                                                                   GDT_HW_ASIC_TYPE    asic_type,
                                                                   GpaUInt8            generate_asic_specific_counters,
                                                                   GpaDerivedCounters* public_counters)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);
    UNREFERENCED_PARAMETER(public_counters);
    return kGpaStatusOk;
}
#endif

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

#ifdef AMDT_INTERNAL
        if (!ret_val)
        {
            std::vector<std::string> tokens;
            std::string              token;
            const char*              local_name = counter_name;

            // First tokenize the input string on the ':' delimiter.
            while (*local_name != '\0')
            {
                if (*local_name == ':' && !token.empty())
                {
                    tokens.push_back(token);
                    token.clear();
                }
                else
                {
                    token.push_back(*local_name);
                }

                local_name++;
            }

            // Add the trailing token to the list.
            if (!token.empty())
            {
                tokens.push_back(token);
            }

            // Valid strings must have 3 or 4 tokens: block, instance, event id, alternate_name.
            // "alternate_name" is optional
            if (3 == tokens.size() || 4 == tokens.size())
            {
                std::string gpa_group_name = tokens[0] + tokens[1];
                std::string gpa_group_name_alt;
                bool        check_alt_group_name = false;

                // Special case instance 0 -- in cases where a block is single-instance,
                // the GPA name for the block won't have '0' appended to it. We need to
                // account for that situation here.
                if ("0" == tokens[1])
                {
                    gpa_group_name_alt   = tokens[0];
                    check_alt_group_name = true;
                }

                for (GpaUInt32 i = public_counters_.GetNumCounters(); i < num_counters; i++)
                {
                    const char* counter_group = GetCounterGroup(i);

                    if (nullptr != counter_group)
                    {
                        bool group_name_found     = false;
                        bool alt_group_name_found = false;

                        group_name_found = (0 == _strcmpi(gpa_group_name.c_str(), counter_group));

                        if (!group_name_found && check_alt_group_name)
                        {
                            group_name_found = (0 == _strcmpi(gpa_group_name_alt.c_str(), counter_group));

                            if (group_name_found)
                            {
                                alt_group_name_found = true;
                            }
                        }

                        if (group_name_found)
                        {
                            // This is the specified block, now just index to the specified event id.
                            GpaUInt32 ret_counter_index = i + atoi(tokens[2].c_str());

                            if (4 <= tokens.size())
                            {
                                // If user is asking for an alternate name, set the name so that subsequent calls to GetCounterName will return the modified name.
                                // It's not ideal casting away constness here, but it is required since we're in a const function
                                // (we don't want to change that since this is only used in internal builds).
                                const_cast<GpaCounterGeneratorBase*>(this)->SetCounterName(ret_counter_index, tokens[3].c_str());
                            }

                            counter_group = GetCounterGroup(ret_counter_index);

                            // Make sure the specified index is still in the specified block.
                            if (nullptr != counter_group)
                            {
                                bool correct_group_name = false;

                                if (alt_group_name_found)
                                {
                                    correct_group_name = (0 == _strcmpi(gpa_group_name_alt.c_str(), counter_group));
                                }
                                else
                                {
                                    correct_group_name = (0 == _strcmpi(gpa_group_name.c_str(), counter_group));
                                }

                                if (correct_group_name)
                                {
                                    counter_index_cache_[counter_name] = ret_counter_index;
                                    *counter_index                     = ret_counter_index;
                                    ret_val                            = true;
                                }
                            }

                            break;
                        }
                    }
                }
            }
        }
#endif

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
    if (!do_allow_hardware_counters_ && !do_allow_public_counters_ && !do_allow_hardware_exposed_counters_ && !do_allow_software_counters_)
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

    if (do_allow_software_counters_)
    {
        if (index < software_counters_.GetNumCounters())
        {
            return software_counters_.GetCounterGroup(index);
        }
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

    if (do_allow_software_counters_)
    {
        if (index < software_counters_.GetNumCounters())
        {
            return software_counters_.GetCounterDescription(index);
        }
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

    if (do_allow_software_counters_)
    {
        GpaDataType type = kGpaDataTypeUint64;

        if (SwCounterManager::Instance()->SwCounterEnabled())
        {
            if (index >= GetNumAmdCounters())
            {
                index -= GetNumAmdCounters();
            }
        }

        if (index < software_counters_.GetNumCounters())
        {
            type = software_counters_.GetCounterType(index);
        }

        return type;
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

    if (do_allow_software_counters_)
    {
        if (SwCounterManager::Instance()->SwCounterEnabled())
        {
            if (index >= GetNumAmdCounters())
            {
                index -= GetNumAmdCounters();
            }
        }

        // SW GPUTime counter.
        if (0 == index)
        {
            return kGpaUsageTypeMilliseconds;
        }

        return kGpaUsageTypeItems;
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

    if (do_allow_software_counters_)
    {
        if (index < software_counters_.GetNumCounters())
        {
            return software_counters_.GetCounterUuid(index);
        }
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

    if (do_allow_software_counters_)
    {
        if (index < software_counters_.GetNumCounters())
        {
            return software_counters_.GetCounterSampleType(index);
        }
    }

    return kGpaCounterSampleTypeDiscrete;
}

const GpaDerivedCounterInfoClass* GpaCounterGeneratorBase::GetPublicCounter(GpaUInt32 index) const
{
    return public_counters_.GetCounter(index);
}

const GpaHardwareCounterDescExt* GpaCounterGeneratorBase::GetHardwareCounterExt(GpaUInt32 index) const
{
    return &(hardware_counters_.hardware_counters_[index]);
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

    if (do_allow_software_counters_)
    {
        if (index < software_counters_.GetNumCounters())
        {
            // The index is now the same as the needed hardware counter.
            vec_internal_counters.push_back(index + hardware_counters_.GetNumCounters());
        }
        else
        {
            index -= software_counters_.GetNumCounters();
        }
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

const GpaSoftwareCounters* GpaCounterGeneratorBase::GetSoftwareCounters() const
{
    return &software_counters_;
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

    if (do_allow_software_counters_)
    {
        info.Set(global_index, GpaCounterSource::kSoftware);
        return info;
    }

    // Unknown counter.
    info.Set(global_index, GpaCounterSource::kUnknown);
    return info;
}
