//==============================================================================
// Copyright (c) 2018-2022 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA GL Context Implementation.
//==============================================================================

#include "gpu_perf_api_gl/gl_gpa_context.h"

#include "gpu_perf_api_common/gpa_context_counter_mediator.h"
#include "gpu_perf_api_common/gpa_unique_object.h"

#include "gpu_perf_api_counter_generator/gpa_hardware_counters.h"

#include "gpu_perf_api_gl/gl_gpa_session.h"

GlGpaContext::GlGpaContext(GlContextPtr context, GpaHwInfo& hw_info, GpaOpenContextFlags context_flags, int driver_version)
    : GpaContext(hw_info, context_flags)
    , gl_context_(context)
    , clock_mode_(ogl_utils::kAmdXDefaultMode)
    , driver_version_(driver_version)
    , driver_supports_GL1CG_(false)
    , driver_supports_ATCL2_(false)
    , driver_supports_CHCG_(false)
    , driver_supports_GUS_(false)
    , driver_supports_UMC_(false)
{
}

GlGpaContext::~GlGpaContext()
{
    GpaStatus set_stable_clocks_status = SetStableClocks(false);

    if (kGpaStatusOk != set_stable_clocks_status)
    {
        GPA_LOG_ERROR("Driver was unable to set stable clocks back to default.");
#ifdef __linux__
        GPA_LOG_MESSAGE("In Linux, make sure to run your application with root privileges.");
#endif  //__linux__
    }
}

GpaSessionId GlGpaContext::CreateSession(GpaSessionSampleType sample_type)
{
    GpaSessionId ret_session_id = nullptr;

    GlGpaSession* new_gpa_gl_gpa_session = new (std::nothrow) GlGpaSession(this, sample_type);

    if (nullptr == new_gpa_gl_gpa_session)
    {
        GPA_LOG_ERROR("Unable to allocate memory for the session.");
    }
    else
    {
        AddGpaSession(new_gpa_gl_gpa_session);

        if (nullptr != new_gpa_gl_gpa_session)
        {
            ret_session_id = reinterpret_cast<GpaSessionId>(GpaUniqueObjectManager::Instance()->CreateObject(new_gpa_gl_gpa_session));
        }
    }

    return ret_session_id;
}

bool GlGpaContext::DeleteSession(GpaSessionId session_id)
{
    bool is_deleted = false;

    GlGpaSession* gl_session = reinterpret_cast<GlGpaSession*>(session_id->Object());

    if (nullptr != gl_session)
    {
        RemoveGpaSession(gl_session);
        GpaUniqueObjectManager::Instance()->DeleteObject(gl_session);
        delete gl_session;
        is_deleted = true;
    }

    return is_deleted;
}

GpaUInt32 GlGpaContext::GetMaxGpaSessions() const
{
    // Maximum latency is 4 for dx10-capable cards.
    return 4;
}

GpaApiType GlGpaContext::GetApiType() const
{
    return kGpaApiOpengl;
}

bool GlGpaContext::Initialize()
{
    GpaStatus set_stable_clocks_status = SetStableClocks(true);

    if (kGpaStatusOk != set_stable_clocks_status)
    {
        GPA_LOG_ERROR("Driver was unable to set stable clocks for profiling.");
#ifdef __linux__
        GPA_LOG_MESSAGE("In Linux, make sure to run your application with root privileges.");
#endif  //__linux__
    }

    if (!PopulateDriverCounterGroupInfo())
    {
        GPA_LOG_ERROR("Failed to populate driver counter group info.");
        return false;
    }

    if (!OpenCounters())
    {
        GPA_LOG_ERROR("Failed to open counters.");
        return false;
    }

    if (!ValidateAndUpdateGlCounters())
    {
        GPA_LOG_ERROR("Failed to validate the available counters.");
        return false;
    }

    SetAsOpened(true);

    return true;
}

const GlContextPtr& GlGpaContext::GetGlContext() const
{
    return gl_context_;
}

GpaStatus GlGpaContext::SetStableClocks(bool use_profiling_clocks)
{
    GpaStatus result = kGpaStatusOk;

    if (nullptr == ogl_utils::ogl_set_gpa_device_clock_mode_amd_x)
    {
        GPA_LOG_MESSAGE("glSetGpaDeviceClockModeAMDX extension is not available.");
    }
    else
    {
        ogl_utils::ClockModeInfo clock_mode = {};

        if (use_profiling_clocks)
        {
            DeviceClockMode deviceClockMode = GetDeviceClockMode();

            switch (deviceClockMode)
            {
            case DeviceClockMode::kDefault:
                clock_mode.clock_mode = ogl_utils::kAmdXDefaultMode;
                break;

            case DeviceClockMode::kProfiling:
                clock_mode.clock_mode = ogl_utils::kAmdXProfilingClock;
                break;

            case DeviceClockMode::kMinimumMemory:
                clock_mode.clock_mode = ogl_utils::kAmdXMinimumMemoryClock;
                break;

            case DeviceClockMode::kMinimumEngine:
                clock_mode.clock_mode = ogl_utils::kAmdXMinimumEngineClock;
                break;

            case DeviceClockMode::kPeak:
                clock_mode.clock_mode = ogl_utils::kAmdXPeakClock;
                break;

            default:
                assert(0);
                clock_mode.clock_mode = ogl_utils::kAmdXProfilingClock;
                break;
            }
        }

        if (clock_mode.clock_mode != clock_mode_)
        {
            clock_mode_ = clock_mode.clock_mode;

#ifdef _LINUX
            if (ogl_utils::kGlDriverVerWithLinuxStableClockSupport > driver_version_)
            {
                // On Linux, earlier drivers claimed to support the stable clock extension, but it was broken
                // due to a driver bug. The driver bug has been fixed starting with the driver version referred
                // to in kGlDriverVerWithLinuxStableClockSupport. If using an earlier driver, just return
                // success without trying to set stable clocks.
                result = kGpaStatusOk;
            }
            else
#endif
            {
                unsigned int clock_result = ogl_utils::ogl_set_gpa_device_clock_mode_amd_x(&clock_mode);
                result                    = (ogl_utils::kGlSetClockSuccess == clock_result) ? kGpaStatusOk : kGpaStatusErrorDriverNotSupported;

                if (clock_result != ogl_utils::kGlSetClockSuccess)
                {
                    GPA_LOG_ERROR("Failed to set ClockMode for profiling.");
                }
            }
        }
    }

    return result;
}

bool GlGpaContext::PopulateDriverCounterGroupInfo()
{
    if (driver_counter_group_info_.empty())
    {
        GLint      num_groups = 0;
        const bool is_oglp    = ogl_utils::IsOglpDriver();
        if (is_oglp)
        {
            ogl_utils::ogl_get_perf_monitor_groups_2_amd(&num_groups, 0, nullptr, nullptr);
        }
        else
        {
            ogl_utils::ogl_get_perf_monitor_groups_amd(&num_groups, 0, nullptr);
        }

        assert(num_groups > 0);

        if (num_groups == 0)
        {
            GPA_LOG_ERROR("No counter groups are exposed by GL_AMD_performance_monitor.");
            return false;
        }
        else
        {
            driver_counter_group_info_.reserve(num_groups);

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

            if (is_oglp)
            {
                ogl_utils::ogl_get_perf_monitor_groups_2_amd(nullptr, num_groups, perf_groups, group_instances);
            }
            else
            {
                ogl_utils::ogl_get_perf_monitor_groups_amd(nullptr, num_groups, perf_groups);
            }

            for (GLint index = 0; index < num_groups; ++index)
            {
                GpaGlPerfMonitorGroupData group_data;
                group_data.group_id      = perf_groups[index];
                group_data.num_instances = is_oglp ? group_instances[index] : 1;

                // Get the group name.
                ogl_utils::ogl_get_perf_monitor_group_string_amd(
                    group_data.group_id, GpaGlPerfMonitorGroupData::kMaxNameLength, nullptr, group_data.group_name);

                // Get the number of counters, and max active discrete counters.
                ogl_utils::ogl_get_perf_monitor_counters_amd(
                    group_data.group_id, &group_data.num_counters, &group_data.max_active_discrete_counters_per_instance, 0, nullptr);

                driver_counter_group_info_.push_back(group_data);

                if (strncmp(group_data.group_name, "GL1CG", 5) == 0)
                {
                    driver_supports_GL1CG_ = true;
                }
                else if (strncmp(group_data.group_name, "ATCL2", 5) == 0)
                {
                    driver_supports_ATCL2_ = true;
                }
                else if (strncmp(group_data.group_name, "CHCG", 4) == 0)
                {
                    driver_supports_CHCG_ = true;
                }
                else if (strncmp(group_data.group_name, "GUS", 3) == 0)
                {
                    driver_supports_GUS_ = true;
                }
                else if (strncmp(group_data.group_name, "UMC", 3) == 0)
                {
                    driver_supports_UMC_ = true;
                }
            }

            delete[] perf_groups;
            delete[] group_instances;
        }
    }

    return true;
}

bool GlGpaContext::ValidateAndUpdateGlCounters() const
{
    bool              success     = false;
    GDT_HW_GENERATION generation  = GDT_HW_GENERATION_NONE;
    GpaUInt32         device_id   = 0;
    GpaUInt32         revision_id = 0;
    GpaUInt32         vendor_id   = 0;

    GpaHwInfo hwInfo = *(GetHwInfo());

    if (!hwInfo.GetHwGeneration(generation) && !hwInfo.GetDeviceId(device_id) && !hwInfo.GetVendorId(vendor_id) && !hwInfo.GetRevisionId(revision_id))
    {
        GPA_LOG_ERROR("Unable to get necessary hardware info.");
    }
    else if (hwInfo.IsAmd())
    {
        if (driver_counter_group_info_.size() == 0)
        {
            GPA_LOG_ERROR("No counter groups are exposed by GL_AMD_performance_monitor.");
        }
        else
        {
            // A const_cast is a feasible and simple workaround here, as GL is the only API in which we are changing the hardware counter info.
            IGpaCounterAccessor* counter_accessor  = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);
            GpaHardwareCounters* hardware_counters = const_cast<GpaHardwareCounters*>(counter_accessor->GetHardwareCounters());
            unsigned int         expected_driver_groups =
                static_cast<unsigned int>(hardware_counters->counter_groups_array_.size() + hardware_counters->additional_group_count_) - 1;

            // Calculate the total number of block instances available, since that is what GPA uses internally.
            // Since the driver only exposes what is actually on the current hardware, it will be less than what GPA expects
            // if lower-end hardware is being used. The extra block instances in GPA will be ignored when profiling.
            unsigned int total_group_instances = 0;
            for (size_t i = 0; i < driver_counter_group_info_.size(); ++i)
            {
                total_group_instances += driver_counter_group_info_[i].num_instances;
            }

            if (ogl_utils::IsUglDriver() && total_group_instances < expected_driver_groups)
            {
                // We should not proceed if the driver exposes less groups that we expect
                GPA_LOG_ERROR("GL_AMD_performance_monitor exposes %d counter group instances, but GPUPerfAPI requires at least %d.",
                    total_group_instances, expected_driver_groups);
            }
            else
            {
                if (ogl_utils::IsUglDriver() && total_group_instances > expected_driver_groups)
                {
                    // Report an message if the driver exposes more groups than we expect, but allow the code to continue.
                    GPA_LOG_MESSAGE("GL_AMD_performance_monitor exposes %d counter group instances, but GPUPerfAPI expected %d.",
                          total_group_instances, expected_driver_groups);
                }

                // Iterate through all of GPA's expanded groups, verify the order, and
                // then update the group Id based on what was returned from the driver.
                std::map<GpaUInt32, GpaHardwareCounterDescExt>::iterator hardware_counter_iter = hardware_counters->hardware_counters_.begin();
                GpaGlPerfGroupVector::const_iterator                     driver_group_iter     = driver_counter_group_info_.cbegin();

                for (unsigned int gpa_group_index = 0; gpa_group_index < static_cast<unsigned int>(hardware_counters->internal_counter_groups_.size());
                     ++gpa_group_index)
                {
                    GpaCounterGroupDesc* gpa_group = &hardware_counters->internal_counter_groups_.at(gpa_group_index);
                    std::string          gpa_group_name(gpa_group->name);

                    if (gpa_group_name.find("GPUTime") == 0)
                    {
                        // This is the last group that GPA needs support from the driver, so we can exit here.
                        // The driver may expose more groups, but GPA doesn't reference them, so it is safe to exit early.
                        success = true;
                        break;
                    }

                    if (!driver_supports_GL1CG_)
                    {
                        // The GL1CG group only exists (and is only exposed) on some hardware,
                        // but GPA expects that it might always exist. If it doesn't exist, then skip this gpa group and continue to the next one.
                        if (gpa_group_name.find("GL1CG") == 0)
                        {
                            continue;
                        }
                    }
                    if (!driver_supports_ATCL2_)
                    {
                        // The ATCL2 group only exists (and is only exposed) on some hardware,
                        // but GPA expects that it might always exist. If it doesn't exist, then skip this gpa group and continue to the next one.
                        if (gpa_group_name.find("ATCL2") == 0)
                        {
                            continue;
                        }
                    }
                    if (!driver_supports_CHCG_)
                    {
                        // The CHCG group only exists (and is only exposed) on some hardware,
                        // but GPA expects that it might always exist. If it doesn't exist, then skip this gpa group and continue to the next one.
                        if (gpa_group_name.find("CHCG") == 0)
                        {
                            continue;
                        }
                    }
                    if (!driver_supports_GUS_)
                    {
                        // The GUS group only exists (and is only exposed) on some hardware,
                        // but GPA expects that it might always exist. If it doesn't exist, then skip this gpa group and continue to the next one.
                        if (gpa_group_name.find("GUS") == 0)
                        {
                            continue;
                        }
                    }
                    if (!driver_supports_UMC_)
                    {
                        if (gpa_group_name.find("UMC") == 0)
                        {
                            continue;
                        }
                    }

                    // Advance the driver_group_iter if this is not the very first iteration of the loop.
                    if (gpa_group_index != 0)
                    {
                        if (ogl_utils ::IsOglpDriver())
                        {
                            // If this is the OGLP driver and the gpa_group has a block instance of 0. This means the incrementing block instance has
                            // reset back to 0 because a new block has started.
                            if (gpa_group->block_instance == 0)
                            {
                                ++driver_group_iter;
                            }
                        }
                        else
                        {
                            // On other drivers, GPA should match the driver 1:1, so always increment to the next driver group.
                            ++driver_group_iter;
                        }

                        if (driver_group_iter == driver_counter_group_info_.cend())
                        {
                            // Should be done now!
                            // There will be other GPA groups (such as GPUTime), but those are not exposed by the driver.
                            success = true;
                            break;
                        }
                    }

                    // Make sure the name from GPA's group index matches the name from the driver,
                    // accounting for the fact that GPA will have the block instance in the group name, and may include more block instances.
                    bool should_validate_and_update = false;

                    // Get the driver group name, extended to include the block instance.
                    std::string driver_group_name_extended(driver_group_iter->group_name);

                    // GPA does not yet support DF_MALL.
                    if (driver_group_name_extended.find("DF_MALL") == 0)
                    {
                        // "Rewinding" index for GPA group so that same group is used on next iteration of loop.
                        gpa_group_index -= 1;
                        continue;
                    }

                    // GPA does not yet support GE_DIST or GE_SE on GFX11.
                    if (generation == GDT_HW_GENERATION::GDT_HW_GENERATION_GFX11 &&
                        (driver_group_name_extended.find("GE_DIST") == 0 || driver_group_name_extended.find("GE_SE") == 0))
                    {
                        // "Rewinding" index for GPA group so that same group is used on next iteration of loop.
                        gpa_group_index -= 1;
                        continue;
                    }

                    // On GFX11, OGLP may expose SQ_ES, SQ_VS, and SQ_LS, even though they are not actually supported on the hardware.
                    // Skip these blocks and "rewind" the gpa group index so that it used again on the next iteration of the loop.
                    if (generation == GDT_HW_GENERATION::GDT_HW_GENERATION_GFX11 &&
                        (driver_group_name_extended.find("SQ_ES") == 0 || driver_group_name_extended.find("SQ_VS") == 0 ||
                         driver_group_name_extended.find("SQ_LS") == 0))
                    {
                        gpa_group_index -= 1;
                        continue;
                    }

                    // Some blocks have slighty different names, so address them here.
                    if (driver_group_name_extended == "PA")
                    {
                        driver_group_name_extended = "PA_SU";
                    }
                    else if (driver_group_name_extended == "SC")
                    {
                        driver_group_name_extended = "PA_SC";
                    }
                    else if (driver_group_name_extended == "GRBM_SE")
                    {
                        driver_group_name_extended = "GRBMSE";
                    }
                    else if (driver_group_name_extended == "DMA")
                    {
                        driver_group_name_extended = "SDMA";
                    }
                    else if (driver_group_name_extended == "EA")
                    {
                        driver_group_name_extended = "GCEA";
                    }
                    else if (driver_group_name_extended == "UMCCH")
                    {
                        driver_group_name_extended = "UMC";
                    }
                    else if (driver_group_name_extended == "PH")
                    {
                        driver_group_name_extended = "PA_PH";
                    }
                    else if (driver_group_name_extended == "GE_DIST")
                    {
                        driver_group_name_extended = "GE2_DIST";
                    }
                    else if (ogl_utils::IsUglDriver() && driver_group_name_extended == "GE1")
                    {
                        driver_group_name_extended = "GE";
                    }
                    else if (ogl_utils::IsUglDriver() && driver_group_name_extended == "GE2_SE")
                    {
                        driver_group_name_extended = "GE_SE";
                    }
                    else if (generation == GDT_HW_GENERATION::GDT_HW_GENERATION_GFX11 && driver_group_name_extended == "SQ")
                    {
                        driver_group_name_extended = "SQG";
                    }
                    else if (generation == GDT_HW_GENERATION::GDT_HW_GENERATION_GFX11 && driver_group_name_extended == "SQ_GS")
                    {
                        driver_group_name_extended = "SQG_GS";
                    }
                    else if (generation == GDT_HW_GENERATION::GDT_HW_GENERATION_GFX11 && driver_group_name_extended == "SQ_PS")
                    {
                        driver_group_name_extended = "SQG_PS";
                    }
                    else if (generation == GDT_HW_GENERATION::GDT_HW_GENERATION_GFX11 && driver_group_name_extended == "SQ_HS")
                    {
                        driver_group_name_extended = "SQG_HS";
                    }
                    else if (generation == GDT_HW_GENERATION::GDT_HW_GENERATION_GFX11 && driver_group_name_extended == "SQ_CS")
                    {
                        driver_group_name_extended = "SQG_CS";
                    }
                    else if (generation == GDT_HW_GENERATION::GDT_HW_GENERATION_GFX11 && driver_group_name_extended == "MCVML2")
                    {
                        driver_group_name_extended = "GCVML2";
                    }

                    if (ogl_utils::IsOglpDriver() && driver_group_iter->num_instances > 1)
                    {
                        // This intentionally combines the driver group name, with GPA's block instance.
                        driver_group_name_extended.append(std::to_string(gpa_group->block_instance));
                    }

                    if (gpa_group_name == driver_group_name_extended)
                    {
                        // This group is an exact match.
                        // GPA and the driver agree that this block exists.
                        should_validate_and_update = true;
                    }
                    else if (gpa_group_name.find(driver_group_name_extended) == 0)
                    {
                        // This GPA group name starts with the driver group name.
                        // This will happen if GPA knows about multiple block instances, but the current hardware only has one.
                        should_validate_and_update = true;
                    }
                    else
                    {
                        // This is an error.
                        GPA_LOG_ERROR("GPA is expecting group %s but the driver is exposing group %s. This GPA group will not be updated.",
                            gpa_group_name.c_str(), driver_group_iter->group_name);

                        break;
                    }

                    if (should_validate_and_update)
                    {
                        // Make sure the num_counters, and Max Active Counters matches for this block (regardless of which block instance).
                        const GpaUInt32 gpa_num_counters = gpa_group->num_counters;
                        if (static_cast<GpaUInt32>(driver_group_iter->num_counters) != gpa_num_counters)
                        {
                            GPA_LOG_MESSAGE("GPA's group %s is expecting %d counters but the driver is reporting %d.",
                                gpa_group_name.c_str(), gpa_num_counters, driver_group_iter->num_counters);
                        }

                        const GpaUInt32 gpa_num_max_active = gpa_group->max_active_discrete_counters;
                        if (static_cast<GpaUInt32>(driver_group_iter->max_active_discrete_counters_per_instance) != gpa_num_max_active)
                        {
                            GPA_LOG_MESSAGE("GPA's group %s is expecting %d max active discrete counters, but the driver is reporting %d.",
                                gpa_group_name.c_str(), gpa_num_max_active, driver_group_iter->max_active_discrete_counters_per_instance);
                        }

                        // Iterate through each counter within this group and update the driver group id.
                        while ((hardware_counter_iter != hardware_counters->hardware_counters_.end()) &&
                               strncmp(gpa_group_name.c_str(), hardware_counter_iter->second.hardware_counters->name, gpa_group_name.size()) == 0)
                        {
                            hardware_counter_iter->second.group_id_driver = driver_group_iter->group_id;
                            ++hardware_counter_iter;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }

    return success;
}

GpaUInt32 GlGpaContext::GetNumInstances(unsigned int driver_group_id) const
{
    GpaUInt32 num_instances = 0;

    for (GpaGlPerfGroupVector::const_iterator group = driver_counter_group_info_.cbegin(); group != driver_counter_group_info_.cend(); ++group)
    {
        if (driver_group_id == group->group_id)
        {
            num_instances = static_cast<GpaUInt32>(group->num_instances);
            break;
        }
    }

    return num_instances;
}

GpaUInt32 GlGpaContext::GetMaxEventId(unsigned int driver_group_id) const
{
    GpaUInt32 max_event_id = 0;

    for (GpaGlPerfGroupVector::const_iterator group = driver_counter_group_info_.cbegin(); group != driver_counter_group_info_.cend(); ++group)
    {
        if (driver_group_id == group->group_id)
        {
            // Subtract one to get the maximum event Id (0-based) from the number of counters (1-based).
            max_event_id = static_cast<GpaUInt32>(group->num_counters - 1);
            break;
        }
    }

    return max_event_id;
}
