//==============================================================================
// Copyright (c) 2018-2022 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GL GPA Pass Object Implementation.
//==============================================================================

#include "gpu_perf_api_gl/gl_gpa_pass.h"

#include "gpu_perf_api_counter_generator/gpa_hardware_counters.h"

#include "gpu_perf_api_common/gpa_context_counter_mediator.h"

#include "gpu_perf_api_gl/gl_gpa_command_list.h"
#include "gpu_perf_api_gl/gl_gpa_context.h"
#include "gpu_perf_api_gl/gl_gpa_sample.h"

GlGpaPass::GlGpaPass(IGpaSession* gpa_session, PassIndex pass_index, GpaCounterSource counter_source, CounterList* pass_counters)
    : GpaPass(gpa_session, pass_index, counter_source, pass_counters)
{
    if (GpaCounterSource::kHardware == GetCounterSource())
    {
        if (!pass_counters->empty())
        {
            if (IsTimingPass())
            {
                EnableCounterForPass(counter_list_->at(0));
            }
            else
            {
                for (size_t i = 0; i < pass_counters->size(); ++i)
                {
                    CounterIndex counter_index = (*pass_counters)[i];

                    // Need to Enable counters.
                    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(GetGpaSession()->GetParentContext());
                    const GpaHardwareCounters*       hardware_counters = counter_accessor->GetHardwareCounters();
                    const GpaHardwareCounterDescExt* counter           = counter_accessor->GetHardwareCounterExt(counter_index);

                    unsigned int group_index = counter->group_index;

                    GLint  num_counters_in_group = 0;
                    GLuint group_instance        = 0;

                    if (group_index < static_cast<unsigned int>(hardware_counters->internal_counter_groups_.size()))
                    {
                        num_counters_in_group = static_cast<GLint>(hardware_counters->internal_counter_groups_.at(group_index).num_counters);
                        group_instance        = static_cast<GLuint>(hardware_counters->internal_counter_groups_.at(group_index).block_instance);
                    }
                    else
                    {
                        num_counters_in_group = static_cast<GLint>(hardware_counters->additional_groups_[group_index - hardware_counters->counter_groups_array_.size()].num_counters);
                        group_instance = static_cast<GLuint>(hardware_counters->additional_groups_[group_index - hardware_counters->counter_groups_array_.size()].block_instance);
                    }

                    assert(counter->hardware_counters->counter_index_in_group <= static_cast<unsigned int>(num_counters_in_group));
                    UNREFERENCED_PARAMETER(num_counters_in_group);

                    // If the block instance to enable does not exist on this hardware, then disable the counter in this pass.
                    // This will basically just fake the result as returning 0.
                    if (reinterpret_cast<GlGpaContext*>(GetGpaSession()->GetParentContext())->GetNumInstances(counter->group_id_driver) <= group_instance)
                    {
                        DisableCounterForPass(counter_index);
                        continue;
                    }

                    // Handle the padded counters that may not exist on certain hardware (based on version-specific register spec files).
                    if (reinterpret_cast<GlGpaContext*>(GetGpaSession()->GetParentContext())->GetMaxEventId(counter->group_id_driver) <=
                        counter->hardware_counters->counter_index_in_group)
                    {
                        DisableCounterForPass(counter_index);
                        continue;
                    }

                    EnableCounterForPass(counter_index);
                }
            }
        }
    }
}

GlGpaPass::~GlGpaPass()
{
    for (auto iter = gl_perf_monitor_info_list_.begin(); iter != gl_perf_monitor_info_list_.end(); ++iter)
    {
        iter->second.Clear(true);
    }
}

GpaSample* GlGpaPass::CreateApiSpecificSample(IGpaCommandList* cmd_list, GpaSampleType sample_type, ClientSampleId sampleId)
{
    GpaSample* ret_sample = nullptr;

    GlGpaSample* gl_gpa_sample = new (std::nothrow) GlGpaSample(this, cmd_list, sample_type, sampleId);

    if (nullptr == gl_gpa_sample)
    {
        GPA_LOG_ERROR("Unable to allocate memory for the sample.");
    }
    else
    {
        ret_sample = gl_gpa_sample;
    }

    return ret_sample;
}

bool GlGpaPass::ContinueSample(ClientSampleId src_sample_id, IGpaCommandList* primary_gpa_cmd_list)
{
    // Continuing samples not supported for OpenGL.
    UNREFERENCED_PARAMETER(src_sample_id);
    UNREFERENCED_PARAMETER(primary_gpa_cmd_list);
    return false;
}

IGpaCommandList* GlGpaPass::CreateApiSpecificCommandList(void* cmd, CommandListId command_list_id, GpaCommandListType cmd_type)
{
    UNREFERENCED_PARAMETER(cmd);
    UNREFERENCED_PARAMETER(cmd_type);

    GlGpaCommandList* ret_cmd_list = new (std::nothrow) GlGpaCommandList(GetGpaSession(), this, command_list_id);
    return ret_cmd_list;
}

bool GlGpaPass::EndSample(IGpaCommandList* cmd_list)
{
    bool ret_val = false;

    if (nullptr != cmd_list)
    {
        ret_val = cmd_list->CloseLastSample();
    }

    return ret_val;
}

bool GlGpaPass::GetPerfMonitor(GlPerfMonitorId& gl_perf_monitor_id)
{
    bool success                = false;
    bool perf_monitor_available = false;

    GlPerfMonitor gl_perf_monitor_found;

    if (!gl_perf_monitor_info_list_.empty())
    {
        for (auto perf_monitor_list_const_iter = gl_perf_monitor_info_list_.cbegin(); perf_monitor_list_const_iter != gl_perf_monitor_info_list_.cend();
             ++perf_monitor_list_const_iter)
        {
            if (perf_monitor_list_const_iter->second.IsDataCollected())
            {
                perf_monitor_available = true;
                gl_perf_monitor_found  = perf_monitor_list_const_iter->second;
                success                = true;
                break;
            }
        }
    }

    if (!perf_monitor_available)
    {
        GlPerfMonitor new_perf_monitor;

        if (new_perf_monitor.Initialize())
        {
            GlPerfMonitorId new_perf_monitor_id = new_perf_monitor.GetPerfMonitorId();

            if (InitializeCounters(new_perf_monitor_id))
            {
                gl_perf_monitor_info_list_.insert(std::pair<GlPerfMonitorId, GlPerfMonitor>(new_perf_monitor_id, new_perf_monitor));
                success               = true;
                gl_perf_monitor_found = new_perf_monitor;
            }
        }
    }

    if (success)
    {
        gl_perf_monitor_id = gl_perf_monitor_found.GetPerfMonitorId();
        gl_perf_monitor_found.AddRef();
    }

    return success;
}

void GlGpaPass::MarkDataCollected(const GlPerfMonitorId gl_perf_monitor_id)
{
    gl_perf_monitor_info_list_.at(gl_perf_monitor_id).Release();
}

const GlCounter* GlGpaPass::GetGLCounter(const GLuint& counter_group,
                                         const GLuint& counter_group_instance,
                                         const GLuint& counter_index,
                                         unsigned int& index_of_counter_within_pass) const
{
    const GlCounter* ret_gl_counter            = nullptr;
    unsigned int     counter_index_within_pass = 0;
    bool             found                     = false;

    for (auto gl_counter_iter = gl_counter_list_.cbegin(); gl_counter_iter != gl_counter_list_.cend(); ++gl_counter_iter)
    {
        if (gl_counter_iter->counter_group == counter_group && gl_counter_iter->counter_group_instance == counter_group_instance &&
            gl_counter_iter->counter_index == counter_index)
        {
            found = true;
            break;
        }

        counter_index_within_pass++;
    }

    if (found)
    {
        ret_gl_counter               = &(gl_counter_list_.data()[counter_index_within_pass]);
        index_of_counter_within_pass = counter_index_within_pass;
    }

    return ret_gl_counter;
}

bool GlGpaPass::InitializeCounters(const GlPerfMonitorId& gl_perf_monitor_id)
{
    bool is_successful = true;

    auto enable_counter = [&](const CounterIndex& counter_index) -> bool {
        bool is_counter_enabled = false;

        // Need to Enable counters.
        IGpaCounterAccessor*             counter_accessor  = GpaContextCounterMediator::Instance()->GetCounterAccessor(GetGpaSession()->GetParentContext());
        const GpaHardwareCounters*       hardware_counters = counter_accessor->GetHardwareCounters();
        const GpaHardwareCounterDescExt* counter           = counter_accessor->GetHardwareCounterExt(counter_index);

        unsigned int group_index = counter->group_index;

        GLint  num_counters_in_group = 0;
        GLuint group_instance        = 0;
        unsigned int counter_groups_array_count = static_cast<unsigned int>(hardware_counters->counter_groups_array_.size());

        if (group_index < static_cast<unsigned int>(hardware_counters->internal_counter_groups_.size()))
        {
            num_counters_in_group = static_cast<GLint>(hardware_counters->internal_counter_groups_[group_index].num_counters);
            group_instance        = static_cast<GLuint>(hardware_counters->internal_counter_groups_[group_index].block_instance);
        }
        else
        {
            num_counters_in_group = static_cast<GLint>(hardware_counters->additional_groups_[group_index - counter_groups_array_count].num_counters);
            group_instance        = static_cast<GLuint>(hardware_counters->additional_groups_[group_index - counter_groups_array_count].block_instance);
        }

        assert(counter->hardware_counters->counter_index_in_group <= static_cast<unsigned int>(num_counters_in_group));

        // Validate Counter result type.
        GLuint result_type = 0;
        ogl_utils::ogl_get_perf_monitor_counter_info_amd(
            counter->group_id_driver, static_cast<GLuint>(counter->hardware_counters->counter_index_in_group), GL_COUNTER_TYPE_AMD, &result_type);

        if (!ogl_utils::CheckForGlError("glGetPerfMonitorCounterInfoAMD failed to get the counter type."))
        {
            if (ogl_utils::IsUglDriver())
            {
                ogl_utils::ogl_select_perf_monitor_counters_amd(
                    gl_perf_monitor_id, GL_TRUE, counter->group_id_driver, 1, reinterpret_cast<GLuint*>(&counter->hardware_counters->counter_index_in_group));
            }
            else
            {
                ogl_utils::ogl_select_perf_monitor_counters_2_amd(gl_perf_monitor_id,
                                                                  GL_TRUE,
                                                                  counter->group_id_driver,
                                                                  group_instance,
                                                                  1,
                                                                  reinterpret_cast<GLuint*>(&counter->hardware_counters->counter_index_in_group));
            }

            if (!ogl_utils::CheckForGlError("Unable to enable counter in GL driver."))
            {
                is_counter_enabled = true;
            }
            else
            {
                is_counter_enabled = false;
            }
        }

        is_successful &= is_counter_enabled;

        if (is_counter_enabled)
        {
            GlCounter gl_counter;
            gl_counter.counter_type           = result_type;
            gl_counter.counter_id             = counter_index;
            gl_counter.counter_group          = counter->group_id_driver;
            gl_counter.counter_group_instance = group_instance;
            gl_counter.counter_index          = static_cast<GLuint>(counter->hardware_counters->counter_index_in_group);
            gl_counter_list_.push_back(gl_counter);
        }
        else
        {
            char group_name[256];
            char counter_name[256];
            memset(group_name, 0, 256);
            memset(counter_name, 0, 256);
            GLsizei length = 0;

            if (group_index <= (counter_groups_array_count + hardware_counters->additional_group_count_))
            {
                ogl_utils::ogl_get_perf_monitor_group_string_amd(counter->group_id_driver, 256, &length, group_name);

                if (ogl_utils::CheckForGlError("glGetPerfMonitorGroupStringAMD failed to get the group name."))
                {
                    return false;
                }
            }

            if (counter->hardware_counters->counter_index_in_group <= static_cast<unsigned int>(num_counters_in_group))
            {
                ogl_utils::ogl_get_perf_monitor_counter_string_amd(
                    counter->group_id_driver, static_cast<GLuint>(counter->hardware_counters->counter_index_in_group), 256, &length, counter_name);

                ogl_utils::CheckForGlError("glGetPerfMonitorCounterStringAMD failed to get the counter name.");
            }

            std::stringstream error;
            error << "Failed to enable counter '" << counter_name << "' from group '" << group_name << "' instance " << counter->group_id_driver << ".";
            GPA_LOG_ERROR(error.str().c_str());
        }

        return is_counter_enabled;
    };

    IterateEnabledCounterList(enable_counter);

    return is_successful;
}

GlGpaPass::GlPerfMonitor::GlPerfMonitor()
    : gl_perf_monitor_id_(0u)
    , ref_count_(0u)
{
}

bool GlGpaPass::GlPerfMonitor::Initialize()
{
    // Create performance monitor.
    ogl_utils::ogl_gen_perf_monitors_amd(1, &gl_perf_monitor_id_);
    return !ogl_utils::CheckForGlError("Unable to create AMD PerfMonitor GL extension.");
}

GlPerfMonitorId GlGpaPass::GlPerfMonitor::GetPerfMonitorId() const
{
    return gl_perf_monitor_id_;
}

bool GlGpaPass::GlPerfMonitor::IsDataCollected() const
{
    // Even count will have no pending results.
    return (ref_count_ % 2 == 0);
}

unsigned int GlGpaPass::GlPerfMonitor::AddRef()
{
    return ++ref_count_;
}

unsigned int GlGpaPass::GlPerfMonitor::Release()
{
    return --ref_count_;
}

bool GlGpaPass::GlPerfMonitor::Clear(bool force_clear)
{
    if (!force_clear && ref_count_ != 0)
    {
        return false;
    }

    ogl_utils::ogl_delete_perf_monitors_amd(1, &gl_perf_monitor_id_);
    return !ogl_utils::CheckForGlError("Unable to delete AMD PerfMonitor GL extension.");
}
