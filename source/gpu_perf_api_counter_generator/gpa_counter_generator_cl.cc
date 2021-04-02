//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for CL counter generation.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator_cl.h"

#include "gpu_perf_api_common/logging.h"

#ifdef EXTRA_COUNTER_INFO
#include <sstream>
#endif

#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_cl_gfx8.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_cl_gfx9.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_cl_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_cl_gfx103.h"

#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_cl_gfx8_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_cl_gfx9_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_cl_gfx10_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_cl_gfx103_asics.h"

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_cl_gfx8.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_cl_gfx9.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_cl_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_cl_gfx103.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

GpaCounterGeneratorCl::GpaCounterGeneratorCl()
{
    GpaCounterGeneratorBase::SetAllowedCounters(true, true, false);

    for (int gen = GDT_HW_GENERATION_FIRST_AMD; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(kGpaApiOpencl, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GpaStatus GpaCounterGeneratorCl::GeneratePublicCounters(GDT_HW_GENERATION   desired_generation,
                                                        GDT_HW_ASIC_TYPE    asic_type,
                                                        GpaUInt8            generate_asic_specific_counters,
                                                        GpaDerivedCounters* public_counters)
{
    auto status = kGpaStatusErrorHardwareNotSupported;

    if (nullptr == public_counters)
    {
        status = kGpaStatusErrorNullPointer;
    }
    else if (public_counters->counters_generated_)
    {
        status = kGpaStatusOk;
    }
    else
    {
        public_counters->Clear();

        if (desired_generation == GDT_HW_GENERATION_VOLCANICISLAND)
        {
            AutoDefinePublicDerivedCountersClGfx8(*public_counters);

            if (generate_asic_specific_counters)
            {
                cl_gfx8_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = kGpaStatusOk;
        }
        else if (desired_generation == GDT_HW_GENERATION_GFX9)
        {
            AutoDefinePublicDerivedCountersClGfx9(*public_counters);

            if (generate_asic_specific_counters)
            {
                cl_gfx9_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = kGpaStatusOk;
        }
        else if (desired_generation == GDT_HW_GENERATION_GFX10)
        {
            AutoDefinePublicDerivedCountersClGfx10(*public_counters);

            if (generate_asic_specific_counters)
            {
                cl_gfx10_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = kGpaStatusOk;
        }
        else if (desired_generation == GDT_HW_GENERATION_GFX103)
        {
            AutoDefinePublicDerivedCountersClGfx103(*public_counters);

            if (generate_asic_specific_counters)
            {
                cl_gfx103_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = kGpaStatusOk;
        }
    }

    auto internal_status = kGpaStatusErrorHardwareNotSupported;

#ifdef AMDT_INTERNAL
    internal_status = GenerateInternalDerivedCounters(desired_generation, asic_type, generate_asic_specific_counters, public_counters);
#endif

    if (kGpaStatusOk == status)
    {
        public_counters->counters_generated_ = true;
    }
    else
    {
        status = internal_status;
    }

    return status;
}

int GpaCounterGeneratorCl::GetDriverGroupId(GDT_HW_GENERATION desired_generation, int block_index) const
{
    int result = block_index;

    if (GDT_HW_GENERATION_GFX9 == desired_generation)
    {
        // For GFX9, the driver has MC, SRBM at index 92, 93, but we don't have those groups for GFX9.
        static const int GFX9_MC_BLOCK_INDEX = 92;

        if (block_index >= GFX9_MC_BLOCK_INDEX)
        {
            result += 2;
        }
    }
    else if (GDT_HW_GENERATION_SEAISLAND == desired_generation)
    {
        // For GFX7 (CI), the driver has TCS at index 79, but we don't have that group for GFX7.
        static const int GFX9_TCS_BLOCK_INDEX = 79;

        if (block_index >= GFX9_TCS_BLOCK_INDEX)
        {
            result++;
        }
    }

    return result;
}

GpaStatus GpaCounterGeneratorCl::GenerateHardwareCounters(GDT_HW_GENERATION    desired_generation,
                                                          GDT_HW_ASIC_TYPE     asic_type,
                                                          GpaUInt8             generate_asic_specific_counters,
                                                          GpaHardwareCounters* hardware_counters)
{
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);

    if (nullptr == hardware_counters)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (hardware_counters->counters_generated_)
    {
        return kGpaStatusOk;
    }

    if (desired_generation == GDT_HW_GENERATION_VOLCANICISLAND)
    {
        hardware_counters->counter_groups_array_    = counter_cl_gfx8::kClCounterGroupArrayGfx8;
        hardware_counters->internal_counter_groups_ = counter_cl_gfx8::kHwClGroupsGfx8;
        hardware_counters->group_count_             = counter_cl_gfx8::kHwClGroupCountGfx8;
        hardware_counters->sq_counter_groups_       = counter_cl_gfx8::kHwClSqGroupsGfx8;
        hardware_counters->sq_group_count_          = counter_cl_gfx8::kHwClSqGroupCountGfx8;
        hardware_counters->isolated_groups_         = counter_cl_gfx8::kHwClSqIsolatedGroupsGfx8;
        hardware_counters->isolated_group_count_    = counter_cl_gfx8::kHwClSqIsolatedGroupCountGfx8;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX9)
    {
        hardware_counters->counter_groups_array_    = counter_cl_gfx9::kClCounterGroupArrayGfx9;
        hardware_counters->internal_counter_groups_ = counter_cl_gfx9::kHwClGroupsGfx9;
        hardware_counters->group_count_             = counter_cl_gfx9::kHwClGroupCountGfx9;
        hardware_counters->sq_counter_groups_       = counter_cl_gfx9::kHwClSqGroupsGfx9;
        hardware_counters->sq_group_count_          = counter_cl_gfx9::kHwClSqGroupCountGfx9;
        hardware_counters->isolated_groups_         = counter_cl_gfx9::kHwClSqIsolatedGroupsGfx9;
        hardware_counters->isolated_group_count_    = counter_cl_gfx9::kHwClSqIsolatedGroupCountGfx9;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX10)
    {
        hardware_counters->counter_groups_array_    = counter_cl_gfx10::kClCounterGroupArrayGfx10;
        hardware_counters->internal_counter_groups_ = counter_cl_gfx10::kHwClGroupsGfx10;
        hardware_counters->group_count_             = counter_cl_gfx10::kHwClGroupCountGfx10;
        hardware_counters->sq_counter_groups_       = counter_cl_gfx10::kHwClSqGroupsGfx10;
        hardware_counters->sq_group_count_          = counter_cl_gfx10::kHwClSqGroupCountGfx10;
        hardware_counters->isolated_groups_         = counter_cl_gfx10::kHwClSqIsolatedGroupsGfx10;
        hardware_counters->isolated_group_count_    = counter_cl_gfx10::kHwClSqIsolatedGroupCountGfx10;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX103)
    {
        hardware_counters->counter_groups_array_    = counter_cl_gfx103::kClCounterGroupArrayGfx103;
        hardware_counters->internal_counter_groups_ = counter_cl_gfx103::kHwClGroupsGfx103;
        hardware_counters->group_count_             = counter_cl_gfx103::kHwClGroupCountGfx103;
        hardware_counters->sq_counter_groups_       = counter_cl_gfx103::kHwClSqGroupsGfx103;
        hardware_counters->sq_group_count_          = counter_cl_gfx103::kHwClSqGroupCountGfx103;
        hardware_counters->isolated_groups_         = counter_cl_gfx103::kHwClSqIsolatedGroupsGfx103;
        hardware_counters->isolated_group_count_    = counter_cl_gfx103::kHwClSqIsolatedGroupCountGfx103;
    }
    else
    {
        GPA_LOG_ERROR("Unrecognized or unhandled hardware generation.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    // Need to count total number of internal counters, since split into groups.
    if (!hardware_counters->counters_generated_)
    {
        if (!GenerateInternalCounters(hardware_counters, desired_generation))
        {
            GPA_LOG_ERROR("Unable to generate internal or whitelist counters.");
            hardware_counters->current_group_used_counts_.resize(0);
            return kGpaStatusErrorContextNotOpen;
        }

        hardware_counters->counters_generated_ = true;
    }

    // Resize the counts that indicate how many counters from each group are being used.
    unsigned int group_count = hardware_counters->group_count_;
    hardware_counters->current_group_used_counts_.resize(group_count);
    hardware_counters->block_instance_counters_index_cache_.clear();
    hardware_counters->gpa_hw_block_hardware_block_group_cache_.clear();
    hardware_counters->counter_hardware_info_map_.clear();
    return kGpaStatusOk;
}

bool GpaCounterGeneratorCl::GenerateInternalCounters(GpaHardwareCounters* hardware_counters, GDT_HW_GENERATION generation) const
{
    hardware_counters->hardware_counters_.clear();
    GpaHardwareCounterDescExt counter = {};

#if defined(_DEBUG) && defined(_WIN32) && defined(AMDT_INTERNAL)
    // Debug builds will generate a file that lists the counter names in a format that can be
    // easily copy/pasted into the GPUPerfAPIUnitTests project.
    FILE* counter_names_file = nullptr;
    fopen_s(&counter_names_file, "HardwareCounterNamesCL.txt", "w");
#endif

    for (GpaUInt32 i = 0; i < hardware_counters->group_count_; i++)
    {
        GpaHardwareCounterDesc* cl_group           = (*(hardware_counters->counter_groups_array_ + i));
        const int               num_group_counters = static_cast<int>(hardware_counters->internal_counter_groups_[i].num_counters);

        for (int j = 0; j < num_group_counters; j++)
        {
            counter.hardware_counters = &(cl_group[j]);
            counter.group_index       = i;
            counter.group_id_driver   = GetDriverGroupId(generation, i);

            counter.counter_id_driver = 0;

#if defined(_DEBUG) && defined(_WIN32) && defined(AMDT_INTERNAL)

            if (nullptr != counter_names_file)
            {
                fwrite("    \"", 1, 5, counter_names_file);
                std::string tmp_name(counter.hardware_counters->name);
                size_t      size = tmp_name.size();
                fwrite(counter.hardware_counters->name, 1, size, counter_names_file);
                fwrite("\",", 1, 2, counter_names_file);
#ifdef EXTRA_COUNTER_INFO
                // This can be useful for debugging counter definitions.
                std::stringstream ss;
                ss << " " << counter.group_index << ", " << counter.group_id_driver << ", " << counter.hardware_counters->counter_index_in_group << ", "
                   << counter.counter_id_driver;
                std::string tmp_counter_info(ss.str());
                size = tmp_counter_info.size();
                fwrite(tmp_counter_info.c_str(), 1, size, counter_names_file);
#endif
                fwrite("\n", 1, 1, counter_names_file);
            }

#endif
            hardware_counters->hardware_counters_.push_back(counter);
        }
    }

#if defined(_DEBUG) && defined(_WIN32) && defined(AMDT_INTERNAL)

    if (nullptr != counter_names_file)
    {
        fclose(counter_names_file);
    }

#endif

    return true;
}

GpaStatus GpaCounterGeneratorCl::GenerateSoftwareCounters(GDT_HW_GENERATION    desired_generation,
                                                          GDT_HW_ASIC_TYPE     asic_type,
                                                          GpaUInt8             generate_asic_specific_counters,
                                                          GpaSoftwareCounters* software_counters)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);
    UNREFERENCED_PARAMETER(software_counters);
    return kGpaStatusOk;
}

GpaStatus GpaCounterGeneratorCl::GenerateHardwareExposedCounters(GDT_HW_GENERATION    desired_generation,
                                                                 GDT_HW_ASIC_TYPE     asic_type,
                                                                 GpaUInt8             generate_asic_specific_counters,
                                                                 GpaHardwareCounters* hardware_counters)
{
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);

    if (hardware_counters->hardware_exposed_counters_generated_)
    {
        return kGpaStatusOk;
    }

    if (desired_generation == GDT_HW_GENERATION_VOLCANICISLAND)
    {
        hardware_counters->hardware_exposed_counters_            = counter_cl_gfx8::kClExposedCountersGroupArrayGfx8;
        hardware_counters->hardware_exposed_counter_groups_      = counter_cl_gfx8::kHwClExposedCountersByGroupGfx8;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_cl_gfx8::kHwClExposedCountersGroupCountGfx8;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX9)
    {
        hardware_counters->hardware_exposed_counters_            = counter_cl_gfx9::kClExposedCountersGroupArrayGfx9;
        hardware_counters->hardware_exposed_counter_groups_      = counter_cl_gfx9::kHwClExposedCountersByGroupGfx9;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_cl_gfx9::kHwClExposedCountersGroupCountGfx9;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX10)
    {
        hardware_counters->hardware_exposed_counters_            = counter_cl_gfx10::kClExposedCountersGroupArrayGfx10;
        hardware_counters->hardware_exposed_counter_groups_      = counter_cl_gfx10::kHwClExposedCountersByGroupGfx10;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_cl_gfx10::kHwClExposedCountersGroupCountGfx10;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX103)
    {
        hardware_counters->hardware_exposed_counters_            = counter_cl_gfx103::kClExposedCountersGroupArrayGfx103;
        hardware_counters->hardware_exposed_counter_groups_      = counter_cl_gfx103::kHwClExposedCountersByGroupGfx103;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_cl_gfx103::kHwClExposedCountersGroupCountGfx103;
    }
    else
    {
        GPA_LOG_ERROR("Unrecognized or unhandled hardware generation.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    hardware_counters->hardware_exposed_counters_generated_ = MapHardwareExposedCounter(hardware_counters);
    return hardware_counters->hardware_exposed_counters_generated_ ? kGpaStatusOk : kGpaStatusErrorFailed;
}
