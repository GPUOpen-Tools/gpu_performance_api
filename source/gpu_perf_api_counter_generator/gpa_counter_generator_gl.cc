//==============================================================================
// Copyright (c) 2016-2023 Advanced Micro Devices, Inc. All rights reserved.
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

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_oglp_gfx8.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_oglp_gfx9.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_oglp_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_oglp_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_oglp_gfx11.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx8.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx9.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx11.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx8_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx9_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx10_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx103_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx11_asics.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

static const char* kDriverSuppliedCounter = GPA_HIDE_NAME("OpenGL Driver-Supplied Counter");  ///< Default counter name for a driver-supplied counter.

GpaCounterGeneratorGl::GpaCounterGeneratorGl()
    : driver_supplied_groups_(nullptr)
    , driver_supplied_groups_count_(0)
{
    GpaCounterGeneratorBase::SetAllowedCounters(true, true);

    for (int gen = GDT_HW_GENERATION_VOLCANICISLAND; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(kGpaApiOpengl, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GpaCounterGeneratorGl::~GpaCounterGeneratorGl()
{
    Cleanup();
}

bool GpaCounterGeneratorGl::GenerateDriverSuppliedInternalCounters(GpaHardwareCounters* hardware_counters, unsigned int global_counter_index)
{
    if (ogl_utils::InitializeGlFunctions() && driver_supplied_groups_count_ == 0 && nullptr != ogl_utils::ogl_get_perf_monitor_group_string_amd &&
        nullptr != ogl_utils::ogl_get_perf_monitor_counters_amd && nullptr != ogl_utils::ogl_get_perf_monitor_counter_string_amd &&
        (nullptr != ogl_utils::ogl_get_perf_monitor_groups_amd || nullptr != ogl_utils::ogl_get_perf_monitor_groups_2_amd))
    {
        // Clean up previously allocated memory, if any (there shouldn't be...).
        Cleanup();

        GLint num_groups = 0;
        if (ogl_utils::IsOglpDriver())
        {
            ogl_utils::ogl_get_perf_monitor_groups_2_amd(&num_groups, 0, nullptr, nullptr);
        }
        else
        {
            ogl_utils::ogl_get_perf_monitor_groups_amd(&num_groups, 0, nullptr);
        }

        if (0 == num_groups)
        {
            return false;
        }

        if (static_cast<unsigned int>(num_groups) < hardware_counters->counter_groups_array_.size())
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

        GLuint* group_instances = new (std::nothrow) GLuint[num_groups];
        if (nullptr == group_instances)
        {
            GPA_LOG_ERROR("Unable to allocate memory to store the group instances.");
            delete[] perf_groups;
            return false;
        }

        if (ogl_utils::IsOglpDriver())
        {
            ogl_utils::ogl_get_perf_monitor_groups_2_amd(nullptr, num_groups, perf_groups, group_instances);
        }
        else
        {
            ogl_utils::ogl_get_perf_monitor_groups_amd(nullptr, num_groups, perf_groups);
        }

        driver_supplied_groups_count_ = num_groups - (static_cast<unsigned int>(hardware_counters->counter_groups_array_.size()) - 1);

        driver_supplied_groups_ = new (std::nothrow) GpaCounterGroupDesc[driver_supplied_groups_count_];

        if (nullptr == driver_supplied_groups_)
        {
            GPA_LOG_ERROR("Unable to allocate memory to store the group IDs.");
            delete[] perf_groups;
            delete[] group_instances;
            return false;
        }

        // Declare this outside the loops.
        GpaHardwareCounterDescExt counter = {};

        for (unsigned int i = 0; i < driver_supplied_groups_count_; i++)
        {
            GLuint driver_perf_group_id = perf_groups[static_cast<unsigned int>(hardware_counters->counter_groups_array_.size()) - 1 +
                                                      i];  // Offset by one to take the "GPUTime" group into account.
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
                delete[] perf_groups;
                delete[] group_instances;
                return false;
            }

            strcpy_s(driver_supplied_groups_[i].name, group_name_length, group_name);

            counter_buffers_.push_back(driver_supplied_groups_[i].name);

            // Get the number of counters and max active counters.
            ogl_utils::ogl_get_perf_monitor_counters_amd(driver_perf_group_id, &num_counters, &num_max_active, 0, nullptr);

            driver_supplied_groups_[i].group_index                  = static_cast<unsigned int>(hardware_counters->internal_counter_groups_.size()) - 1 + i;
            driver_supplied_groups_[i].max_active_discrete_counters = num_max_active;
            driver_supplied_groups_[i].max_active_spm_counters      = 0;
            driver_supplied_groups_[i].num_counters                 = num_counters;
            driver_supplied_groups_[i].block_instance               = 0;

            assert(ogl_utils::IsUglDriver() && "The block_instance variable above needs to be updated to support OGLP.");

            for (int c = 0; c < num_counters; c++)
            {
                counter.group_index       = driver_supplied_groups_[i].group_index + 1;
                counter.hardware_counters = new (std::nothrow) GpaHardwareCounterDesc;

                if (nullptr == counter.hardware_counters)
                {
                    GPA_LOG_ERROR("Unable to allocate memory to store the hardwareCounter.");
                    delete[] perf_groups;
                    delete[] group_instances;
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
                    delete[] perf_groups;
                    delete[] group_instances;
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
                    delete[] perf_groups;
                    delete[] group_instances;
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
                    delete[] perf_groups;
                    delete[] group_instances;
                    return false;
                }

                counter_buffers_.push_back(counter.hardware_counters->group);

                memset(counter.hardware_counters->group, 0, hw_group_name_length);
                strcpy_s(counter.hardware_counters->group, hw_group_name_length, GPA_HIDE_NAME(group_name));

                counter.hardware_counters->type = kGpaDataTypeUint64;
                counter.group_id_driver         = driver_perf_group_id;
                counter.counter_id_driver       = 0;

                driver_supplied_counters_.insert(std::pair<GpaUInt32, GpaHardwareCounterDescExt>(global_counter_index, counter));
                global_counter_index++;
            }
        }

        counter_group_descs_.push_back(driver_supplied_groups_);

        delete[] perf_groups;
        delete[] group_instances;
    }

    hardware_counters->additional_groups_      = driver_supplied_groups_;
    hardware_counters->additional_group_count_ = driver_supplied_groups_count_;
    hardware_counters->hardware_counters_.insert(driver_supplied_counters_.begin(), driver_supplied_counters_.end());

    return true;
}

GpaStatus GpaCounterGeneratorGl::GenerateInternalCounters(GpaHardwareCounters* hardware_counters, GDT_HW_GENERATION generation)
{
    UNREFERENCED_PARAMETER(generation);
    hardware_counters->hardware_counters_.clear();
    // Declare this outside the loops.
    GpaHardwareCounterDescExt counter = {};

    unsigned int global_counter_index      = 0;
    unsigned int global_counter_group_base = 0;
    unsigned int offset                    = 0;

    const unsigned int counter_array_size = static_cast<unsigned int>(hardware_counters->counter_groups_array_.size());
    // Iterate over counter array, which will either be populated with only exposed counters or all counters in internal builds.
    for (unsigned int g = 0; g < counter_array_size; g++)
    {
        std::vector<GpaHardwareCounterDesc>* gl_group = hardware_counters->counter_groups_array_.at(g);
        GpaCounterGroupDesc                  group    = hardware_counters->internal_counter_groups_.at(g + offset);

        const unsigned int num_exposed_counters_in_group = static_cast<unsigned int>(gl_group->size());
        const unsigned int total_counters_in_group       = static_cast<int>(group.num_counters);

        if (strncmp(gl_group->at(0).group, group.name, strlen(group.name)) != 0)
        {
            global_counter_group_base += total_counters_in_group;
            offset++;
            g--;
            continue;
        }

        for (unsigned int c = 0; c < num_exposed_counters_in_group; c++)
        {
            counter.group_index       = g + offset;
            counter.hardware_counters = &(gl_group->at(c));

            // Temporarily set the group_id_driver to be group index, but we actually need to query the group IDs from GL.
            // GPUPerfAPIGL will query the runtime in OpenContext for this information and will update the group Ids.
            counter.group_id_driver   = g + offset;
            counter.counter_id_driver = 0;

            global_counter_index = static_cast<GpaUInt32>(global_counter_group_base + gl_group->at(c).counter_index_in_group);
            hardware_counters->hardware_counters_.insert(std::pair<GpaUInt32, GpaHardwareCounterDescExt>(global_counter_index, counter));
        }
        // Adding total number of counters in group to "skip" past counters just added above.
        global_counter_group_base += total_counters_in_group;
    }

    // Now add extra groups/counters exposed by the driver.
    GenerateDriverSuppliedInternalCounters(hardware_counters, global_counter_index);

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
    GpaStatus status = kGpaStatusErrorHardwareNotSupported;

    if (nullptr == public_counters)
    {
        status = kGpaStatusErrorNullPointer;
    }
    else if (public_counters->GetCountersGenerated())
    {
        status = kGpaStatusOk;
    }
    else
    {
        public_counters->Clear();

        if (ogl_utils::IsUglDriver())
        {
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
        else if (ogl_utils::IsNoDriver() || ogl_utils::IsOglpDriver())
        {
            switch (desired_generation)
            {
            case GDT_HW_GENERATION_VOLCANICISLAND:
            {
                AutoDefinePublicDerivedCountersOglpGfx8(*public_counters);

                if (generate_asic_specific_counters)
                {
                    oglp_gfx8_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
                }

                status = kGpaStatusOk;
            }
            break;

            case GDT_HW_GENERATION_GFX9:
            {
                AutoDefinePublicDerivedCountersOglpGfx9(*public_counters);

                if (generate_asic_specific_counters)
                {
                    oglp_gfx9_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
                }

                status = kGpaStatusOk;
            }
            break;

            case GDT_HW_GENERATION_GFX10:
            {
                AutoDefinePublicDerivedCountersOglpGfx10(*public_counters);

                if (generate_asic_specific_counters)
                {
                    oglp_gfx10_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
                }

                status = kGpaStatusOk;
            }
            break;

            case GDT_HW_GENERATION_GFX103:
            {
                AutoDefinePublicDerivedCountersOglpGfx103(*public_counters);

                if (generate_asic_specific_counters)
                {
                    oglp_gfx103_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
                }

                status = kGpaStatusOk;
            }
            break;

            case GDT_HW_GENERATION_GFX11:
            {
                AutoDefinePublicDerivedCountersOglpGfx11(*public_counters);

                if (generate_asic_specific_counters)
                {
                    oglp_gfx11_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
                }

                status = kGpaStatusOk;
            }
            break;

            default:
                GPA_LOG_ERROR("Unsupported or unrecognized hardware generation. Cannot generate public counters.");
                break;
            }
        }
        else
        {
            assert(!"Need to add other driver support.");
        }
    }

    if (kGpaStatusOk == status)
    {
        public_counters->SetCountersGenerated(true);
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

    if (ogl_utils::IsUglDriver())
    {
        switch (desired_generation)
        {
        case GDT_HW_GENERATION_VOLCANICISLAND:
            hardware_counters->counter_groups_array_                             = counter_gl_gfx8::kGlCounterGroupArrayGfx8;
            hardware_counters->internal_counter_groups_                          = counter_gl_gfx8::kHwGlGroupsGfx8;
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
    }
    else if (ogl_utils::IsNoDriver() || ogl_utils::IsOglpDriver())
    {
        switch (desired_generation)
        {
        case GDT_HW_GENERATION_VOLCANICISLAND:
            hardware_counters->counter_groups_array_                             = counter_oglp_gfx8::kOglpCounterGroupArrayGfx8;
            hardware_counters->internal_counter_groups_                          = counter_oglp_gfx8::kHwOglpGroupsGfx8;
            hardware_counters->sq_counter_groups_                                = counter_oglp_gfx8::kHwOglpSqGroupsGfx8;
            hardware_counters->sq_group_count_                                   = counter_oglp_gfx8::kHwOglpSqGroupCountGfx8;
            hardware_counters->timestamp_block_ids_                              = counter_oglp_gfx8::kHwOglpTimestampBlockIdsGfx8;
            hardware_counters->time_counter_indices_                             = counter_oglp_gfx8::kHwOglpTimeCounterIndicesGfx8;
            hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_oglp_gfx8::kHwOglpGpuTimeBottomToBottomDurationIndexGfx8;
            hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_oglp_gfx8::kHwOglpGpuTimeBottomToBottomStartIndexGfx8;
            hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_oglp_gfx8::kHwOglpGpuTimeBottomToBottomEndIndexGfx8;
            hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_oglp_gfx8::kHwOglpGpuTimeTopToBottomDurationIndexGfx8;
            hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_oglp_gfx8::kHwOglpGpuTimeTopToBottomStartIndexGfx8;
            hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_oglp_gfx8::kHwOglpGpuTimeTopToBottomEndIndexGfx8;
            hardware_counters->isolated_groups_                                  = counter_oglp_gfx8::kHwOglpSqIsolatedGroupsGfx8;
            hardware_counters->isolated_group_count_                             = counter_oglp_gfx8::kHwOglpSqIsolatedGroupCountGfx8;
            hardware_counters->padded_counters_                                  = counter_oglp_gfx8::kOglpPaddedCounterByGroupGfx8;
            hardware_counters->padded_counter_count_                             = counter_oglp_gfx8::kOglpPaddedCounterGroupCountGfx8;
            break;

        case GDT_HW_GENERATION_GFX9:
            hardware_counters->counter_groups_array_                             = counter_oglp_gfx9::kOglpCounterGroupArrayGfx9;
            hardware_counters->internal_counter_groups_                          = counter_oglp_gfx9::kHwOglpGroupsGfx9;
            hardware_counters->sq_counter_groups_                                = counter_oglp_gfx9::kHwOglpSqGroupsGfx9;
            hardware_counters->sq_group_count_                                   = counter_oglp_gfx9::kHwOglpSqGroupCountGfx9;
            hardware_counters->timestamp_block_ids_                              = counter_oglp_gfx9::kHwOglpTimestampBlockIdsGfx9;
            hardware_counters->time_counter_indices_                             = counter_oglp_gfx9::kHwOglpTimeCounterIndicesGfx9;
            hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_oglp_gfx9::kHwOglpGpuTimeBottomToBottomDurationIndexGfx9;
            hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_oglp_gfx9::kHwOglpGpuTimeBottomToBottomStartIndexGfx9;
            hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_oglp_gfx9::kHwOglpGpuTimeBottomToBottomEndIndexGfx9;
            hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_oglp_gfx9::kHwOglpGpuTimeTopToBottomDurationIndexGfx9;
            hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_oglp_gfx9::kHwOglpGpuTimeTopToBottomStartIndexGfx9;
            hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_oglp_gfx9::kHwOglpGpuTimeTopToBottomEndIndexGfx9;
            hardware_counters->isolated_groups_                                  = counter_oglp_gfx9::kHwOglpSqIsolatedGroupsGfx9;
            hardware_counters->isolated_group_count_                             = counter_oglp_gfx9::kHwOglpSqIsolatedGroupCountGfx9;
            hardware_counters->padded_counters_                                  = counter_oglp_gfx9::kOglpPaddedCounterByGroupGfx9;
            hardware_counters->padded_counter_count_                             = counter_oglp_gfx9::kOglpPaddedCounterGroupCountGfx9;
            break;

        case GDT_HW_GENERATION_GFX10:
            hardware_counters->counter_groups_array_                             = counter_oglp_gfx10::kOglpCounterGroupArrayGfx10;
            hardware_counters->internal_counter_groups_                          = counter_oglp_gfx10::kHwOglpGroupsGfx10;
            hardware_counters->sq_counter_groups_                                = counter_oglp_gfx10::kHwOglpSqGroupsGfx10;
            hardware_counters->sq_group_count_                                   = counter_oglp_gfx10::kHwOglpSqGroupCountGfx10;
            hardware_counters->timestamp_block_ids_                              = counter_oglp_gfx10::kHwOglpTimestampBlockIdsGfx10;
            hardware_counters->time_counter_indices_                             = counter_oglp_gfx10::kHwOglpTimeCounterIndicesGfx10;
            hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_oglp_gfx10::kHwOglpGpuTimeBottomToBottomDurationIndexGfx10;
            hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_oglp_gfx10::kHwOglpGpuTimeBottomToBottomStartIndexGfx10;
            hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_oglp_gfx10::kHwOglpGpuTimeBottomToBottomEndIndexGfx10;
            hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_oglp_gfx10::kHwOglpGpuTimeTopToBottomDurationIndexGfx10;
            hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_oglp_gfx10::kHwOglpGpuTimeTopToBottomStartIndexGfx10;
            hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_oglp_gfx10::kHwOglpGpuTimeTopToBottomEndIndexGfx10;
            hardware_counters->isolated_groups_                                  = counter_oglp_gfx10::kHwOglpSqIsolatedGroupsGfx10;
            hardware_counters->isolated_group_count_                             = counter_oglp_gfx10::kHwOglpSqIsolatedGroupCountGfx10;
            hardware_counters->padded_counters_                                  = counter_oglp_gfx10::kOglpPaddedCounterByGroupGfx10;
            hardware_counters->padded_counter_count_                             = counter_oglp_gfx10::kOglpPaddedCounterGroupCountGfx10;
            break;

        case GDT_HW_GENERATION_GFX103:
            hardware_counters->counter_groups_array_                             = counter_oglp_gfx103::kOglpCounterGroupArrayGfx103;
            hardware_counters->internal_counter_groups_                          = counter_oglp_gfx103::kHwOglpGroupsGfx103;
            hardware_counters->sq_counter_groups_                                = counter_oglp_gfx103::kHwOglpSqGroupsGfx103;
            hardware_counters->sq_group_count_                                   = counter_oglp_gfx103::kHwOglpSqGroupCountGfx103;
            hardware_counters->timestamp_block_ids_                              = counter_oglp_gfx103::kHwOglpTimestampBlockIdsGfx103;
            hardware_counters->time_counter_indices_                             = counter_oglp_gfx103::kHwOglpTimeCounterIndicesGfx103;
            hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_oglp_gfx103::kHwOglpGpuTimeBottomToBottomDurationIndexGfx103;
            hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_oglp_gfx103::kHwOglpGpuTimeBottomToBottomStartIndexGfx103;
            hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_oglp_gfx103::kHwOglpGpuTimeBottomToBottomEndIndexGfx103;
            hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_oglp_gfx103::kHwOglpGpuTimeTopToBottomDurationIndexGfx103;
            hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_oglp_gfx103::kHwOglpGpuTimeTopToBottomStartIndexGfx103;
            hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_oglp_gfx103::kHwOglpGpuTimeTopToBottomEndIndexGfx103;
            hardware_counters->isolated_groups_                                  = counter_oglp_gfx103::kHwOglpSqIsolatedGroupsGfx103;
            hardware_counters->isolated_group_count_                             = counter_oglp_gfx103::kHwOglpSqIsolatedGroupCountGfx103;
            hardware_counters->padded_counters_                                  = counter_oglp_gfx103::kOglpPaddedCounterByGroupGfx103;
            hardware_counters->padded_counter_count_                             = counter_oglp_gfx103::kOglpPaddedCounterGroupCountGfx103;
            break;

        case GDT_HW_GENERATION_GFX11:
            hardware_counters->counter_groups_array_                             = counter_oglp_gfx11::kOglpCounterGroupArrayGfx11;
            hardware_counters->internal_counter_groups_                          = counter_oglp_gfx11::kHwOglpGroupsGfx11;
            hardware_counters->sq_counter_groups_                                = counter_oglp_gfx11::kHwOglpSqGroupsGfx11;
            hardware_counters->sq_group_count_                                   = counter_oglp_gfx11::kHwOglpSqGroupCountGfx11;
            hardware_counters->timestamp_block_ids_                              = counter_oglp_gfx11::kHwOglpTimestampBlockIdsGfx11;
            hardware_counters->time_counter_indices_                             = counter_oglp_gfx11::kHwOglpTimeCounterIndicesGfx11;
            hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_oglp_gfx11::kHwOglpGpuTimeBottomToBottomDurationIndexGfx11;
            hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_oglp_gfx11::kHwOglpGpuTimeBottomToBottomStartIndexGfx11;
            hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_oglp_gfx11::kHwOglpGpuTimeBottomToBottomEndIndexGfx11;
            hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_oglp_gfx11::kHwOglpGpuTimeTopToBottomDurationIndexGfx11;
            hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_oglp_gfx11::kHwOglpGpuTimeTopToBottomStartIndexGfx11;
            hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_oglp_gfx11::kHwOglpGpuTimeTopToBottomEndIndexGfx11;
            hardware_counters->isolated_groups_                                  = counter_oglp_gfx11::kHwOglpSqIsolatedGroupsGfx11;
            hardware_counters->isolated_group_count_                             = counter_oglp_gfx11::kHwOglpSqIsolatedGroupCountGfx11;
            hardware_counters->padded_counters_                                  = counter_oglp_gfx11::kOglpPaddedCounterByGroupGfx11;
            hardware_counters->padded_counter_count_                             = counter_oglp_gfx11::kOglpPaddedCounterGroupCountGfx11;
            break;

        default:
            GPA_LOG_ERROR("Unrecognized or unhandled hardware generation.");
            return kGpaStatusErrorHardwareNotSupported;
        }
    }
    else
    {
        assert(!"Need to add other driver support.");
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

    unsigned int group_count = static_cast<unsigned int>(hardware_counters->counter_groups_array_.size());
    hardware_counters->current_group_used_counts_.resize(group_count);
    hardware_counters->block_instance_counters_index_cache_.clear();
    hardware_counters->gpa_hw_block_hardware_block_group_cache_.clear();
    hardware_counters->counter_hardware_info_map_.clear();

    return status;
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

    if (ogl_utils::IsUglDriver())
    {
        switch (desired_generation)
        {
        case GDT_HW_GENERATION_VOLCANICISLAND:
            hardware_counters->hardware_exposed_counters_            = counter_gl_gfx8::kGlCounterGroupArrayGfx8;
            hardware_counters->hardware_exposed_counter_groups_      = counter_gl_gfx8::kHwGlExposedCountersByGroupGfx8;
            hardware_counters->hardware_exposed_counter_group_count_ = counter_gl_gfx8::kHwGlExposedCountersGroupCountGfx8;
            break;

        case GDT_HW_GENERATION_GFX9:
            hardware_counters->hardware_exposed_counters_            = counter_gl_gfx9::kGlCounterGroupArrayGfx9;
            hardware_counters->hardware_exposed_counter_groups_      = counter_gl_gfx9::kHwGlExposedCountersByGroupGfx9;
            hardware_counters->hardware_exposed_counter_group_count_ = counter_gl_gfx9::kHwGlExposedCountersGroupCountGfx9;
            break;

        case GDT_HW_GENERATION_GFX10:
            hardware_counters->hardware_exposed_counters_            = counter_gl_gfx10::kGlCounterGroupArrayGfx10;
            hardware_counters->hardware_exposed_counter_groups_      = counter_gl_gfx10::kHwGlExposedCountersByGroupGfx10;
            hardware_counters->hardware_exposed_counter_group_count_ = counter_gl_gfx10::kHwGlExposedCountersGroupCountGfx10;
            break;

        case GDT_HW_GENERATION_GFX103:
            hardware_counters->hardware_exposed_counters_            = counter_gl_gfx103::kGlCounterGroupArrayGfx103;
            hardware_counters->hardware_exposed_counter_groups_      = counter_gl_gfx103::kHwGlExposedCountersByGroupGfx103;
            hardware_counters->hardware_exposed_counter_group_count_ = counter_gl_gfx103::kHwGlExposedCountersGroupCountGfx103;
            break;

        default:
            GPA_LOG_ERROR("Unrecognized or unhandled hardware generation.");
            return kGpaStatusErrorHardwareNotSupported;
        }
    }
    else if (ogl_utils::IsNoDriver() || ogl_utils::IsOglpDriver())
    {
        switch (desired_generation)
        {
        case GDT_HW_GENERATION_VOLCANICISLAND:
            hardware_counters->hardware_exposed_counters_            = counter_oglp_gfx8::kOglpCounterGroupArrayGfx8;
            hardware_counters->hardware_exposed_counter_groups_      = counter_oglp_gfx8::kHwOglpExposedCountersByGroupGfx8;
            hardware_counters->hardware_exposed_counter_group_count_ = counter_oglp_gfx8::kHwOglpExposedCountersGroupCountGfx8;
            break;

        case GDT_HW_GENERATION_GFX9:
            hardware_counters->hardware_exposed_counters_            = counter_oglp_gfx9::kOglpCounterGroupArrayGfx9;
            hardware_counters->hardware_exposed_counter_groups_      = counter_oglp_gfx9::kHwOglpExposedCountersByGroupGfx9;
            hardware_counters->hardware_exposed_counter_group_count_ = counter_oglp_gfx9::kHwOglpExposedCountersGroupCountGfx9;
            break;

        case GDT_HW_GENERATION_GFX10:
            hardware_counters->hardware_exposed_counters_            = counter_oglp_gfx10::kOglpCounterGroupArrayGfx10;
            hardware_counters->hardware_exposed_counter_groups_      = counter_oglp_gfx10::kHwOglpExposedCountersByGroupGfx10;
            hardware_counters->hardware_exposed_counter_group_count_ = counter_oglp_gfx10::kHwOglpExposedCountersGroupCountGfx10;
            break;

        case GDT_HW_GENERATION_GFX103:
            hardware_counters->hardware_exposed_counters_            = counter_oglp_gfx103::kOglpCounterGroupArrayGfx103;
            hardware_counters->hardware_exposed_counter_groups_      = counter_oglp_gfx103::kHwOglpExposedCountersByGroupGfx103;
            hardware_counters->hardware_exposed_counter_group_count_ = counter_oglp_gfx103::kHwOglpExposedCountersGroupCountGfx103;
            break;

        case GDT_HW_GENERATION_GFX11:
            hardware_counters->hardware_exposed_counters_            = counter_oglp_gfx11::kOglpCounterGroupArrayGfx11;
            hardware_counters->hardware_exposed_counter_groups_      = counter_oglp_gfx11::kHwOglpExposedCountersByGroupGfx11;
            hardware_counters->hardware_exposed_counter_group_count_ = counter_oglp_gfx11::kHwOglpExposedCountersGroupCountGfx11;
            break;

        default:
            GPA_LOG_ERROR("Unrecognized or unhandled hardware generation.");
            return kGpaStatusErrorHardwareNotSupported;
        }
    }
    else
    {
        assert(!"Need to add other driver support.");
    }

    hardware_counters->hardware_exposed_counters_generated_ = MapHardwareExposedCounter(hardware_counters);
    return hardware_counters->hardware_exposed_counters_generated_ ? kGpaStatusOk : kGpaStatusErrorFailed;
}
