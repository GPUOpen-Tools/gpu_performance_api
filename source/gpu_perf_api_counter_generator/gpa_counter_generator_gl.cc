//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for GL counter generation.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator_gl.h"

#ifdef EXTRA_COUNTER_INFO
#include <sstream>
#endif

#include "gpu_perf_api_common/logging.h"

#include "gpu_perf_api_counter_generator/gl_entry_points.h"

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_gl_gfx8.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_gl_gfx9.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_gl_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_gl_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_gl_gfx8.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_gl_gfx9.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_gl_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_gl_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_gl_gfx8_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_gl_gfx9_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_gl_gfx10_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_gl_gfx103_asics.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

static const char* kDriverSuppliedCounter = GPA_HIDE_NAME("OpenGL Driver-Supplied Counter");  ///< Default counter name for a driver-supplied counter.

GpaCounterGeneratorGl::GpaCounterGeneratorGl()
    : driver_supplied_groups_(nullptr)
    , driver_supplied_groups_count_(0)
{
    GpaCounterGeneratorBase::SetAllowedCounters(true, true, false);

    for (int gen = GDT_HW_GENERATION_FIRST_AMD; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(kGpaApiOpengl, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GpaCounterGeneratorGl::~GpaCounterGeneratorGl()
{
    Cleanup();
}

bool GpaCounterGeneratorGl::GenerateDriverSuppliedInternalCounters(GpaHardwareCounters* hardware_counters)
{
    if (ogl_utils::InitializeGlFunctions() && driver_supplied_groups_count_ == 0 && nullptr != ogl_utils::ogl_get_perf_monitor_groups_amd &&
        nullptr != ogl_utils::ogl_get_perf_monitor_group_string_amd && nullptr != ogl_utils::ogl_get_perf_monitor_counters_amd &&
        nullptr != ogl_utils::ogl_get_perf_monitor_counter_string_amd)
    {
        // Clean up previously allocated memory, if any (there shouldn't be...).
        Cleanup();

        GLint num_groups = 0;
        ogl_utils::ogl_get_perf_monitor_groups_amd(&num_groups, 0, nullptr);

        if (0 == num_groups)
        {
            return false;
        }

        if (static_cast<unsigned int>(num_groups) < hardware_counters->group_count_)
        {
            return false;
        }

        // Get the group Ids.
        GLuint* perf_groups = new (std::nothrow) GLuint[num_groups];

        if (nullptr == perf_groups)
        {
            GPA_LOG_ERROR("Unable to allocate memory to store the group IDs.");
            return false;
        }

        ogl_utils::ogl_get_perf_monitor_groups_amd(nullptr, num_groups, perf_groups);

        driver_supplied_groups_count_ = num_groups - (hardware_counters->group_count_ - 1);

        driver_supplied_groups_ = new (std::nothrow) GpaCounterGroupDesc[driver_supplied_groups_count_];

        if (nullptr == driver_supplied_groups_)
        {
            GPA_LOG_ERROR("Unable to allocate memory to store the group IDs.");
            return false;
        }

        // Declare this outside the loops.
        GpaHardwareCounterDescExt counter = {};

        for (unsigned int i = 0; i < driver_supplied_groups_count_; i++)
        {
            GLuint driver_perf_group_id = perf_groups[hardware_counters->group_count_ - 1 + i];  // Offset by one to take the "GPUTime" group into account.
            char   group_name[64];
            memset(group_name, 0, 64);
            GLint num_counters   = 0;
            GLint num_max_active = 0;

            // Get the group name.
            ogl_utils::ogl_get_perf_monitor_group_string_amd(driver_perf_group_id, 64, nullptr, group_name);

            size_t group_name_length        = strlen(group_name) + 1;
            driver_supplied_groups_[i].name = new (std::nothrow) char[group_name_length];

            if (nullptr == driver_supplied_groups_[i].name)
            {
                GPA_LOG_ERROR("Unable to allocate memory to store the counter group name.");
                return false;
            }

            strcpy_s(driver_supplied_groups_[i].name, group_name_length, group_name);

            counter_buffers_.push_back(driver_supplied_groups_[i].name);

            // Get the number of counters and max active counters.
            ogl_utils::ogl_get_perf_monitor_counters_amd(driver_perf_group_id, &num_counters, &num_max_active, 0, nullptr);

            driver_supplied_groups_[i].group_index                  = hardware_counters->group_count_ - 1 + i;
            driver_supplied_groups_[i].max_active_discrete_counters = num_max_active;
            driver_supplied_groups_[i].max_active_spm_counters      = 0;
            driver_supplied_groups_[i].num_counters                 = num_counters;
            driver_supplied_groups_[i].block_instance               = 0;

            for (int c = 0; c < num_counters; c++)
            {
                counter.group_index       = driver_supplied_groups_[i].group_index + 1;
                counter.hardware_counters = new (std::nothrow) GpaHardwareCounterDesc;

                if (nullptr == counter.hardware_counters)
                {
                    GPA_LOG_ERROR("Unable to allocate memory to store the hardwareCounter.");
                    return false;
                }

                hardware_counter_descs_.push_back(counter.hardware_counters);

                counter.hardware_counters->counter_index_in_group = c;

                GLsizei name_length;
                ogl_utils::ogl_get_perf_monitor_counter_string_amd(driver_perf_group_id, c, 0, &name_length, nullptr);

                char* counter_name = new (std::nothrow) char[name_length + 1];

                if (nullptr == counter_name)
                {
                    GPA_LOG_ERROR("Unable to allocate memory to store the counter name.");
                    return false;
                }

                counter_buffers_.push_back(counter_name);

                memset(counter_name, 0, name_length + 1);

                ogl_utils::ogl_get_perf_monitor_counter_string_amd(driver_perf_group_id, c, name_length, nullptr, counter_name);

                counter.hardware_counters->name = GPA_HIDE_NAME(counter_name);

                size_t description_length              = 1 + strlen(kDriverSuppliedCounter);  // 1 for the terminating null.
                counter.hardware_counters->description = new (std::nothrow) char[description_length];

                if (nullptr == counter.hardware_counters->description)
                {
                    GPA_LOG_ERROR("Unable to allocate memory to store the counter description.");
                    return false;
                }

                counter_buffers_.push_back(counter.hardware_counters->description);

                memset(counter.hardware_counters->description, 0, description_length);
                strcpy_s(counter.hardware_counters->description, description_length, GPA_HIDE_NAME(kDriverSuppliedCounter));

                size_t hw_group_name_length      = 1 + strlen(group_name);  // 1 for the terminating null.
                counter.hardware_counters->group = new (std::nothrow) char[hw_group_name_length];

                if (nullptr == counter.hardware_counters->group)
                {
                    GPA_LOG_ERROR("Unable to allocate memory to store the counter group.");
                    return false;
                }

                counter_buffers_.push_back(counter.hardware_counters->group);

                memset(counter.hardware_counters->group, 0, hw_group_name_length);
                strcpy_s(counter.hardware_counters->group, hw_group_name_length, GPA_HIDE_NAME(group_name));

                counter.hardware_counters->type = kGpaDataTypeUint64;
                counter.group_id_driver         = driver_perf_group_id;
                counter.counter_id_driver       = 0;

                driver_supplied_counters_.push_back(counter);
            }
        }

        counter_group_descs_.push_back(driver_supplied_groups_);

        delete[] perf_groups;
    }

    hardware_counters->additional_groups_      = driver_supplied_groups_;
    hardware_counters->additional_group_count_ = driver_supplied_groups_count_;
    hardware_counters->hardware_counters_.insert(
        hardware_counters->hardware_counters_.end(), driver_supplied_counters_.begin(), driver_supplied_counters_.end());

    return true;
}

GpaStatus GpaCounterGeneratorGl::GenerateInternalCounters(GpaHardwareCounters* hardware_counters, GDT_HW_GENERATION generation)
{
    UNREFERENCED_PARAMETER(generation);
    hardware_counters->hardware_counters_.clear();
    // Declare this outside the loops.
    GpaHardwareCounterDescExt counter = {};

#if defined(_DEBUG) && defined(_WIN32) && defined(AMDT_INTERNAL)
    // Debug builds will generate a file that lists the counter names in a format that can be
    // easily copy/pasted into the GPUPerfAPIUnitTests project.
    FILE* counter_names_file = nullptr;
    fopen_s(&counter_names_file, "HardwareCounterNamesGL.txt", "w");
#endif

    // For each group, get the group name, number of counters, and max counters (and maybe validate them).
    for (int g = 0; g < static_cast<int>(hardware_counters->group_count_); g++)
    {
        GpaHardwareCounterDesc* gl_group = hardware_counters->counter_groups_array_[g];

        // Only add the number of counters that are supported; but no more than the number that we expect.
        const GpaUInt64 num_counters_in_group = hardware_counters->internal_counter_groups_[g].num_counters;

        for (GpaUInt64 c = 0; c < num_counters_in_group; c++)
        {
            counter.group_index       = g;
            counter.hardware_counters = &(gl_group[c]);

            // Temporarily set the group_id_driver to be g, but we actually need to query the group IDs from GL.
            // GPUPerfAPIGL will query the runtime in OpenContext for this information and will update the group Ids.
            counter.group_id_driver   = g;
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

    // Now add extra groups/counters exposed by the driver.
    GenerateDriverSuppliedInternalCounters(hardware_counters);

#if defined(_DEBUG) && defined(_WIN32) && defined(AMDT_INTERNAL)
    if (nullptr != counter_names_file)
    {
        fclose(counter_names_file);
    }
#endif

    return kGpaStatusOk;
}

void GpaCounterGeneratorGl::Cleanup()
{
    for (auto buffer : counter_buffers_)
    {
        delete[] buffer;
    }

    for (auto counter_desc : hardware_counter_descs_)
    {
        delete counter_desc;
    }

    for (auto group_desc : counter_group_descs_)
    {
        delete[] group_desc;
    }

    counter_buffers_.clear();
    hardware_counter_descs_.clear();
    counter_group_descs_.clear();
    driver_supplied_counters_.clear();
}

GpaStatus GpaCounterGeneratorGl::GeneratePublicCounters(GDT_HW_GENERATION   desired_generation,
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

        switch (desired_generation)
        {
        case GDT_HW_GENERATION_VOLCANICISLAND:
        {
            AutoDefinePublicDerivedCountersGlGfx8(*public_counters);

            if (generate_asic_specific_counters)
            {
                gl_gfx8_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = kGpaStatusOk;
        }
        break;

        case GDT_HW_GENERATION_GFX9:
        {
            AutoDefinePublicDerivedCountersGlGfx9(*public_counters);

            if (generate_asic_specific_counters)
            {
                gl_gfx9_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = kGpaStatusOk;
        }
        break;

        case GDT_HW_GENERATION_GFX10:
        {
            AutoDefinePublicDerivedCountersGlGfx10(*public_counters);

            if (generate_asic_specific_counters)
            {
                gl_gfx10_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = kGpaStatusOk;
        }
        break;

        case GDT_HW_GENERATION_GFX103:
        {
            AutoDefinePublicDerivedCountersGlGfx103(*public_counters);

            if (generate_asic_specific_counters)
            {
                gl_gfx103_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = kGpaStatusOk;
        }
        break;

        default:
            GPA_LOG_ERROR("Unsupported or unrecognized hardware generation. Cannot generate public counters.");
            break;
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

GpaStatus GpaCounterGeneratorGl::GenerateHardwareCounters(GDT_HW_GENERATION    desired_generation,
                                                          GDT_HW_ASIC_TYPE     asic_type,
                                                          GpaUInt8             generate_asic_specific_counters,
                                                          GpaHardwareCounters* hardware_counters)
{
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);

    GpaStatus status = kGpaStatusOk;

    if (nullptr == hardware_counters)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (hardware_counters->counters_generated_)  // Only generate counters once to improve performance.
    {
        return kGpaStatusOk;
    }

    hardware_counters->Clear();

    switch (desired_generation)
    {
    case GDT_HW_GENERATION_VOLCANICISLAND:
        hardware_counters->counter_groups_array_                             = counter_gl_gfx8::kGlCounterGroupArrayGfx8;
        hardware_counters->internal_counter_groups_                          = counter_gl_gfx8::kHwGlGroupsGfx8;
        hardware_counters->group_count_                                      = counter_gl_gfx8::kHwGlGroupCountGfx8;
        hardware_counters->sq_counter_groups_                                = counter_gl_gfx8::kHwGlSqGroupsGfx8;
        hardware_counters->sq_group_count_                                   = counter_gl_gfx8::kHwGlSqGroupCountGfx8;
        hardware_counters->timestamp_block_ids_                              = counter_gl_gfx8::kHwGlTimestampBlockIdsGfx8;
        hardware_counters->time_counter_indices_                             = counter_gl_gfx8::kHwGlTimeCounterIndicesGfx8;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_gl_gfx8::kHwGlGpuTimeBottomToBottomDurationIndexGfx8;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_gl_gfx8::kHwGlGpuTimeBottomToBottomStartIndexGfx8;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_gl_gfx8::kHwGlGpuTimeBottomToBottomEndIndexGfx8;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_gl_gfx8::kHwGlGpuTimeTopToBottomDurationIndexGfx8;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_gl_gfx8::kHwGlGpuTimeTopToBottomStartIndexGfx8;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_gl_gfx8::kHwGlGpuTimeTopToBottomEndIndexGfx8;
        hardware_counters->isolated_groups_                                  = counter_gl_gfx8::kHwGlSqIsolatedGroupsGfx8;
        hardware_counters->isolated_group_count_                             = counter_gl_gfx8::kHwGlSqIsolatedGroupCountGfx8;
        hardware_counters->padded_counters_                                  = counter_gl_gfx8::kGlPaddedCounterByGroupGfx8;
        hardware_counters->padded_counter_count_                             = counter_gl_gfx8::kGlPaddedCounterGroupCountGfx8;
        break;

    case GDT_HW_GENERATION_GFX9:
        hardware_counters->counter_groups_array_                             = counter_gl_gfx9::kGlCounterGroupArrayGfx9;
        hardware_counters->internal_counter_groups_                          = counter_gl_gfx9::kHwGlGroupsGfx9;
        hardware_counters->group_count_                                      = counter_gl_gfx9::kHwGlGroupCountGfx9;
        hardware_counters->sq_counter_groups_                                = counter_gl_gfx9::kHwGlSqGroupsGfx9;
        hardware_counters->sq_group_count_                                   = counter_gl_gfx9::kHwGlSqGroupCountGfx9;
        hardware_counters->timestamp_block_ids_                              = counter_gl_gfx9::kHwGlTimestampBlockIdsGfx9;
        hardware_counters->time_counter_indices_                             = counter_gl_gfx9::kHwGlTimeCounterIndicesGfx9;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_gl_gfx9::kHwGlGpuTimeBottomToBottomDurationIndexGfx9;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_gl_gfx9::kHwGlGpuTimeBottomToBottomStartIndexGfx9;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_gl_gfx9::kHwGlGpuTimeBottomToBottomEndIndexGfx9;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_gl_gfx9::kHwGlGpuTimeTopToBottomDurationIndexGfx9;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_gl_gfx9::kHwGlGpuTimeTopToBottomStartIndexGfx9;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_gl_gfx9::kHwGlGpuTimeTopToBottomEndIndexGfx9;
        hardware_counters->isolated_groups_                                  = counter_gl_gfx9::kHwGlSqIsolatedGroupsGfx9;
        hardware_counters->isolated_group_count_                             = counter_gl_gfx9::kHwGlSqIsolatedGroupCountGfx9;
        hardware_counters->padded_counters_                                  = counter_gl_gfx9::kGlPaddedCounterByGroupGfx9;
        hardware_counters->padded_counter_count_                             = counter_gl_gfx9::kGlPaddedCounterGroupCountGfx9;
        break;

    case GDT_HW_GENERATION_GFX10:
        hardware_counters->counter_groups_array_                             = counter_gl_gfx10::kGlCounterGroupArrayGfx10;
        hardware_counters->internal_counter_groups_                          = counter_gl_gfx10::kHwGlGroupsGfx10;
        hardware_counters->group_count_                                      = counter_gl_gfx10::kHwGlGroupCountGfx10;
        hardware_counters->sq_counter_groups_                                = counter_gl_gfx10::kHwGlSqGroupsGfx10;
        hardware_counters->sq_group_count_                                   = counter_gl_gfx10::kHwGlSqGroupCountGfx10;
        hardware_counters->timestamp_block_ids_                              = counter_gl_gfx10::kHwGlTimestampBlockIdsGfx10;
        hardware_counters->time_counter_indices_                             = counter_gl_gfx10::kHwGlTimeCounterIndicesGfx10;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_gl_gfx10::kHwGlGpuTimeBottomToBottomDurationIndexGfx10;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_gl_gfx10::kHwGlGpuTimeBottomToBottomStartIndexGfx10;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_gl_gfx10::kHwGlGpuTimeBottomToBottomEndIndexGfx10;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_gl_gfx10::kHwGlGpuTimeTopToBottomDurationIndexGfx10;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_gl_gfx10::kHwGlGpuTimeTopToBottomStartIndexGfx10;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_gl_gfx10::kHwGlGpuTimeTopToBottomEndIndexGfx10;
        hardware_counters->isolated_groups_                                  = counter_gl_gfx10::kHwGlSqIsolatedGroupsGfx10;
        hardware_counters->isolated_group_count_                             = counter_gl_gfx10::kHwGlSqIsolatedGroupCountGfx10;
        hardware_counters->padded_counters_                                  = counter_gl_gfx10::kGlPaddedCounterByGroupGfx10;
        hardware_counters->padded_counter_count_                             = counter_gl_gfx10::kGlPaddedCounterGroupCountGfx10;
        break;

    case GDT_HW_GENERATION_GFX103:
        hardware_counters->counter_groups_array_                             = counter_gl_gfx103::kGlCounterGroupArrayGfx103;
        hardware_counters->internal_counter_groups_                          = counter_gl_gfx103::kHwGlGroupsGfx103;
        hardware_counters->group_count_                                      = counter_gl_gfx103::kHwGlGroupCountGfx103;
        hardware_counters->sq_counter_groups_                                = counter_gl_gfx103::kHwGlSqGroupsGfx103;
        hardware_counters->sq_group_count_                                   = counter_gl_gfx103::kHwGlSqGroupCountGfx103;
        hardware_counters->timestamp_block_ids_                              = counter_gl_gfx103::kHwGlTimestampBlockIdsGfx103;
        hardware_counters->time_counter_indices_                             = counter_gl_gfx103::kHwGlTimeCounterIndicesGfx103;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_gl_gfx103::kHwGlGpuTimeBottomToBottomDurationIndexGfx103;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_gl_gfx103::kHwGlGpuTimeBottomToBottomStartIndexGfx103;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_gl_gfx103::kHwGlGpuTimeBottomToBottomEndIndexGfx103;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_gl_gfx103::kHwGlGpuTimeTopToBottomDurationIndexGfx103;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_gl_gfx103::kHwGlGpuTimeTopToBottomStartIndexGfx103;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_gl_gfx103::kHwGlGpuTimeTopToBottomEndIndexGfx103;
        hardware_counters->isolated_groups_                                  = counter_gl_gfx103::kHwGlSqIsolatedGroupsGfx103;
        hardware_counters->isolated_group_count_                             = counter_gl_gfx103::kHwGlSqIsolatedGroupCountGfx103;
        hardware_counters->padded_counters_                                  = counter_gl_gfx103::kGlPaddedCounterByGroupGfx103;
        hardware_counters->padded_counter_count_                             = counter_gl_gfx103::kGlPaddedCounterGroupCountGfx103;
        break;

    default:
        GPA_LOG_ERROR("Unrecognized or unhandled hardware generation.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    // Need to count total number of internal counters, since split into groups.
    status = GenerateInternalCounters(hardware_counters, desired_generation);

    if (status != kGpaStatusOk)
    {
        GPA_LOG_ERROR("Unable to generate internal counters.");
        hardware_counters->current_group_used_counts_.clear();
        return status;
    }

    hardware_counters->counters_generated_ = true;

    unsigned int group_count = hardware_counters->group_count_;
    hardware_counters->current_group_used_counts_.resize(group_count);
    hardware_counters->block_instance_counters_index_cache_.clear();
    hardware_counters->gpa_hw_block_hardware_block_group_cache_.clear();
    hardware_counters->counter_hardware_info_map_.clear();

    return status;
}

GpaStatus GpaCounterGeneratorGl::GenerateSoftwareCounters(GDT_HW_GENERATION    desired_generation,
                                                          GDT_HW_ASIC_TYPE     asic_type,
                                                          GpaUInt8             generate_asic_specific_counters,
                                                          GpaSoftwareCounters* software_counters)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);
    UNREFERENCED_PARAMETER(software_counters);
    GpaStatus ret_val = kGpaStatusOk;

    return ret_val;
}

GpaStatus GpaCounterGeneratorGl::GenerateHardwareExposedCounters(GDT_HW_GENERATION    desired_generation,
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

    if (hardware_counters->hardware_exposed_counters_generated_)
    {
        return kGpaStatusOk;
    }

    switch (desired_generation)
    {
    case GDT_HW_GENERATION_VOLCANICISLAND:
        hardware_counters->hardware_exposed_counters_            = counter_gl_gfx8::kGlExposedCountersGroupArrayGfx8;
        hardware_counters->hardware_exposed_counter_groups_      = counter_gl_gfx8::kHwGlExposedCountersByGroupGfx8;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_gl_gfx8::kHwGlExposedCountersGroupCountGfx8;
        break;

    case GDT_HW_GENERATION_GFX9:
        hardware_counters->hardware_exposed_counters_            = counter_gl_gfx9::kGlExposedCountersGroupArrayGfx9;
        hardware_counters->hardware_exposed_counter_groups_      = counter_gl_gfx9::kHwGlExposedCountersByGroupGfx9;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_gl_gfx9::kHwGlExposedCountersGroupCountGfx9;
        break;

    case GDT_HW_GENERATION_GFX10:
        hardware_counters->hardware_exposed_counters_            = counter_gl_gfx10::kGlExposedCountersGroupArrayGfx10;
        hardware_counters->hardware_exposed_counter_groups_      = counter_gl_gfx10::kHwGlExposedCountersByGroupGfx10;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_gl_gfx10::kHwGlExposedCountersGroupCountGfx10;
        break;

    case GDT_HW_GENERATION_GFX103:
        hardware_counters->hardware_exposed_counters_            = counter_gl_gfx103::kGlExposedCountersGroupArrayGfx103;
        hardware_counters->hardware_exposed_counter_groups_      = counter_gl_gfx103::kHwGlExposedCountersByGroupGfx103;
        hardware_counters->hardware_exposed_counter_group_count_ = counter_gl_gfx103::kHwGlExposedCountersGroupCountGfx103;
        break;

    default:
        GPA_LOG_ERROR("Unrecognized or unhandled hardware generation.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    hardware_counters->hardware_exposed_counters_generated_ = MapHardwareExposedCounter(hardware_counters);
    return hardware_counters->hardware_exposed_counters_generated_ ? kGpaStatusOk : kGpaStatusErrorFailed;
}
