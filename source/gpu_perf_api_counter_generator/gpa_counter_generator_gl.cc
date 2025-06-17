//==============================================================================
// Copyright (c) 2016-2025 Advanced Micro Devices, Inc. All rights reserved.
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

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_oglp_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_oglp_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_oglp_gfx11.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_oglp_gfx12.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx11.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx12.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx10_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx103_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx11_asics.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx12_asics.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

static const char* kDriverSuppliedCounter = GPA_HIDE_NAME("OpenGL Driver-Supplied Counter");  ///< Default counter name for a driver-supplied counter.

GpaCounterGeneratorGl::GpaCounterGeneratorGl(GpaSessionSampleType sample_type)
    : GpaCounterGeneratorBase(sample_type)
    , driver_supplied_groups_(nullptr)
    , driver_supplied_groups_count_(0)
{
    GpaCounterGeneratorBase::SetAllowedCounters(true, true);

    for (int gen = GDT_HW_GENERATION_GFX10; gen < GDT_HW_GENERATION_LAST; gen++)
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
        ogl_utils::ogl_get_perf_monitor_groups_2_amd(&num_groups, 0, nullptr, nullptr);

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

        ogl_utils::ogl_get_perf_monitor_groups_2_amd(nullptr, num_groups, perf_groups, group_instances);

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

            size_t group_name_length           = strlen(group_name) + 1;
            auto   driver_supplied_groups_name = new (std::nothrow) char[group_name_length];

            if (nullptr == driver_supplied_groups_name)
            {
                GPA_LOG_ERROR("Unable to allocate memory to store the counter group name.");
                delete[] perf_groups;
                delete[] group_instances;
                return false;
            }

            strcpy_s(driver_supplied_groups_name, group_name_length, group_name);

            counter_buffers_.push_back(driver_supplied_groups_name);

            driver_supplied_groups_[i].name = driver_supplied_groups_name;

            // Get the number of counters and max active counters.
            ogl_utils::ogl_get_perf_monitor_counters_amd(driver_perf_group_id, &num_counters, &num_max_active, 0, nullptr);

            driver_supplied_groups_[i].group_index                  = static_cast<unsigned int>(hardware_counters->internal_counter_groups_.size()) - 1 + i;
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
                auto hw_group_desc = new (std::nothrow) char[description_length];

                if (nullptr == hw_group_desc)
                {
                    GPA_LOG_ERROR("Unable to allocate memory to store the counter description.");
                    delete[] perf_groups;
                    delete[] group_instances;
                    return false;
                }

                counter_buffers_.push_back(hw_group_desc);

                memset(hw_group_desc, 0, description_length);
                strcpy_s(hw_group_desc, description_length, GPA_HIDE_NAME(kDriverSuppliedCounter));

                counter.hardware_counters->description = hw_group_desc;

                size_t hw_group_name_length      = 1 + strlen(group_name);  // 1 for the terminating null.
                auto hw_group_name = new (std::nothrow) char[hw_group_name_length];

                if (nullptr == hw_group_name)
                {
                    GPA_LOG_ERROR("Unable to allocate memory to store the counter group.");
                    delete[] perf_groups;
                    delete[] group_instances;
                    return false;
                }

                counter_buffers_.push_back(hw_group_name);

                memset(hw_group_name, 0, hw_group_name_length);
                strcpy_s(hw_group_name, hw_group_name_length, GPA_HIDE_NAME(group_name));

                counter.hardware_counters->group = hw_group_name;
                counter.hardware_counters->type  = kGpaDataTypeUint64;
                counter.group_id_driver          = driver_perf_group_id;
                counter.counter_id_driver        = 0;

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

GpaStatus GpaCounterGeneratorGl::GeneratePublicCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GpaDerivedCounters* public_counters)
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

        switch (desired_generation)
        {
        case GDT_HW_GENERATION_GFX10:
        {
            AutoDefinePublicDerivedCountersOglpGfx10(*public_counters);
            oglp_gfx10_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            status = kGpaStatusOk;
        }
        break;

        case GDT_HW_GENERATION_GFX103:
        {
            AutoDefinePublicDerivedCountersOglpGfx103(*public_counters);
            oglp_gfx103_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            status = kGpaStatusOk;
        }
        break;

        case GDT_HW_GENERATION_GFX11:
        {
            AutoDefinePublicDerivedCountersOglpGfx11(*public_counters);
            oglp_gfx11_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            status = kGpaStatusOk;
        }
        break;

        case GDT_HW_GENERATION_GFX12:
        {
            AutoDefinePublicDerivedCountersOglpGfx12(*public_counters);
            oglp_gfx12_asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            status = kGpaStatusOk;
        }
        break;

        default:
            GPA_LOG_ERROR("Unsupported or unrecognized hardware generation. Cannot generate public counters.");
            break;
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
                                                          GpaHardwareCounters* hardware_counters)
{
    UNREFERENCED_PARAMETER(asic_type);

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
    case GDT_HW_GENERATION_GFX10:
        hardware_counters->counter_groups_array_                             = counter_oglp_gfx10::kOglpCounterGroupArrayGfx10;
        hardware_counters->internal_counter_groups_                          = counter_oglp_gfx10::kHwOglpGroupsGfx10;
        hardware_counters->sq_counter_groups_                                = counter_oglp_gfx10::kHwOglpSqGroupsGfx10;
        hardware_counters->sq_group_count_                                   = counter_oglp_gfx10::kHwOglpSqGroupCountGfx10;
        hardware_counters->timestamp_block_ids_                              = counter_oglp_gfx10::kHwOglpTimestampBlockIdsGfx10;
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

    case GDT_HW_GENERATION_GFX12:
        hardware_counters->counter_groups_array_                             = counter_oglp_gfx12::kOglpCounterGroupArrayGfx12;
        hardware_counters->internal_counter_groups_                          = counter_oglp_gfx12::kHwOglpGroupsGfx12;
        hardware_counters->sq_counter_groups_                                = counter_oglp_gfx12::kHwOglpSqGroupsGfx12;
        hardware_counters->sq_group_count_                                   = counter_oglp_gfx12::kHwOglpSqGroupCountGfx12;
        hardware_counters->timestamp_block_ids_                              = counter_oglp_gfx12::kHwOglpTimestampBlockIdsGfx12;
        hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_ = counter_oglp_gfx12::kHwOglpGpuTimeBottomToBottomDurationIndexGfx12;
        hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_    = counter_oglp_gfx12::kHwOglpGpuTimeBottomToBottomStartIndexGfx12;
        hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_      = counter_oglp_gfx12::kHwOglpGpuTimeBottomToBottomEndIndexGfx12;
        hardware_counters->gpu_time_top_to_bottom_duration_counter_index_    = counter_oglp_gfx12::kHwOglpGpuTimeTopToBottomDurationIndexGfx12;
        hardware_counters->gpu_time_top_to_bottom_start_counter_index_       = counter_oglp_gfx12::kHwOglpGpuTimeTopToBottomStartIndexGfx12;
        hardware_counters->gpu_time_top_to_bottom_end_counter_index_         = counter_oglp_gfx12::kHwOglpGpuTimeTopToBottomEndIndexGfx12;
        hardware_counters->isolated_groups_                                  = counter_oglp_gfx12::kHwOglpSqIsolatedGroupsGfx12;
        hardware_counters->isolated_group_count_                             = counter_oglp_gfx12::kHwOglpSqIsolatedGroupCountGfx12;
        hardware_counters->padded_counters_                                  = counter_oglp_gfx12::kOglpPaddedCounterByGroupGfx12;
        hardware_counters->padded_counter_count_                             = counter_oglp_gfx12::kOglpPaddedCounterGroupCountGfx12;
        break;

    default:
        GPA_LOG_ERROR("Unrecognized or unhandled hardware generation.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    hardware_counters->eop_time_counter_indices_.insert(hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_);
    hardware_counters->eop_time_counter_indices_.insert(hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_);
    hardware_counters->eop_time_counter_indices_.insert(hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_);

    hardware_counters->top_time_counter_indices_.insert(hardware_counters->gpu_time_top_to_bottom_duration_counter_index_);
    hardware_counters->top_time_counter_indices_.insert(hardware_counters->gpu_time_top_to_bottom_start_counter_index_);
    hardware_counters->top_time_counter_indices_.insert(hardware_counters->gpu_time_top_to_bottom_end_counter_index_);

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
                                                                 GpaHardwareCounters* hardware_counters)
{
    UNREFERENCED_PARAMETER(asic_type);

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
    case GDT_HW_GENERATION_GFX10:
        hardware_counters->hardware_exposed_counters_       = counter_oglp_gfx10::kOglpCounterGroupArrayGfx10;
        hardware_counters->hardware_exposed_counter_groups_ = counter_oglp_gfx10::kHwOglpExposedCountersByGroupGfx10;
        break;

    case GDT_HW_GENERATION_GFX103:
        hardware_counters->hardware_exposed_counters_       = counter_oglp_gfx103::kOglpCounterGroupArrayGfx103;
        hardware_counters->hardware_exposed_counter_groups_ = counter_oglp_gfx103::kHwOglpExposedCountersByGroupGfx103;
        break;

    case GDT_HW_GENERATION_GFX11:
        hardware_counters->hardware_exposed_counters_       = counter_oglp_gfx11::kOglpCounterGroupArrayGfx11;
        hardware_counters->hardware_exposed_counter_groups_ = counter_oglp_gfx11::kHwOglpExposedCountersByGroupGfx11;
        break;

    case GDT_HW_GENERATION_GFX12:
        hardware_counters->hardware_exposed_counters_       = counter_oglp_gfx12::kOglpCounterGroupArrayGfx12;
        hardware_counters->hardware_exposed_counter_groups_ = counter_oglp_gfx12::kHwOglpExposedCountersByGroupGfx12;
        break;

    default:
        GPA_LOG_ERROR("Unrecognized or unhandled hardware generation.");
        return kGpaStatusErrorHardwareNotSupported;
    }

    hardware_counters->hardware_exposed_counters_generated_ = MapHardwareExposedCounter(hardware_counters);
    return hardware_counters->hardware_exposed_counters_generated_ ? kGpaStatusOk : kGpaStatusErrorFailed;
}
