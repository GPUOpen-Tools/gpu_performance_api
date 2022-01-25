//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GPA GL Context Implementation
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

    bool success = OpenCounters() && ValidateAndUpdateGlCounters();

    if (success)
    {
        SetAsOpened(true);
    }

    return success;
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
        // Query the GL API to get the hardware counter group names and Ids so that the expected groups can be verified and the group Ids can be updated.
        // Get the number of performance counter groups
        GLint num_groups = 0;
        ogl_utils::ogl_get_perf_monitor_groups_amd(&num_groups, 0, nullptr);

        assert(num_groups > 0);

        if (num_groups == 0)
        {
            GPA_LOG_ERROR("No counter groups are exposed by GL_AMD_performance_monitor.");
        }
        else
        {
            // A const_cast is a feasible and simple workaround here, as GL is the only API in which we are changing the hardware counter info.
            IGpaCounterAccessor* counter_accessor       = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);
            GpaHardwareCounters* hardware_counters      = const_cast<GpaHardwareCounters*>(counter_accessor->GetHardwareCounters());
            unsigned int         expected_driver_groups = hardware_counters->group_count_ + hardware_counters->additional_group_count_ - 1;

            if (num_groups < static_cast<int>(expected_driver_groups))
            {
                // We should not proceed if the driver exposes less groups that we expect
                std::stringstream error;
                error << "GL_AMD_performance_monitor exposes " << num_groups << " counter groups, but GPUPerfAPI requires at least "
                      << static_cast<int>(expected_driver_groups) << ".";
                GPA_LOG_ERROR(error.str().c_str());
            }
            else
            {
                if (num_groups > static_cast<int>(expected_driver_groups))
                {
                    // Report an error if the driver exposes more groups than we expect, but allow the code to continue.
                    std::stringstream error;
                    error << "GL_AMD_performance_monitor exposes " << num_groups << " counter groups, but GPUPerfAPI expected "
                          << static_cast<int>(expected_driver_groups) << ".";
                    GPA_LOG_ERROR(error.str().c_str());
                }

                // Get the group Ids.
                GLuint* perf_groups = new (std::nothrow) GLuint[num_groups];

                if (nullptr == perf_groups)
                {
                    GPA_LOG_ERROR("Unable to allocate memory to store the group IDs.");
                }
                else
                {
                    ogl_utils::ogl_get_perf_monitor_groups_amd(nullptr, num_groups, perf_groups);

                    // Declare this outside the loops.
                    std::vector<GpaHardwareCounterDescExt>::iterator internal_counter_iter = hardware_counters->hardware_counters_.begin();

                    int driver_group_num = -1;

                    // For each group, get the group name, number of counters, and max counters (and maybe validate them).
                    for (int g = 0; g < static_cast<int>(hardware_counters->group_count_); g++)
                    {
                        driver_group_num++;
                        char  str_name[64] = {};
                        GLint counters     = 0;
                        GLint max_active   = 0;

                        // Get the group name.
                        if (g < num_groups)
                        {
                            ogl_utils::ogl_get_perf_monitor_group_string_amd(perf_groups[driver_group_num], 64, nullptr, str_name);

                            // Get the number of counters and max active counters.
                            ogl_utils::ogl_get_perf_monitor_counters_amd(perf_groups[driver_group_num], &counters, &max_active, 0, nullptr);

                            // Validate the values
                            if (strncmp(hardware_counters->internal_counter_groups_[g].name, "GPUTime", 8) == 0)
                            {
                                // Ignore the GPUTime group -- it is not explicitly exposed by the driver -- it is handled separately by GPA.
                                // We break here because GPUTime is always the last group exposed by GPA.
                                break;
                            }

                            if (strncmp(hardware_counters->internal_counter_groups_[g].name, str_name, 64) != 0)
                            {
                                std::stringstream error;
#ifndef GLES
                                error << "GPUPerfAPI's group name '" << hardware_counters->internal_counter_groups_[g].name
                                      << "' does not match the OpenGL returned name of '" << str_name << "'.";
#else
                                error << "GPUPerfAPI's group name '" << hardware_counters->internal_counter_groups_[g].name
                                      << "' does not match the OpenGL ES returned name of '" << str_name << "'.";
#endif  // GLES
                                GPA_LOG_MESSAGE(error.str().c_str());
                            }
                            else
                            {
                                // Make sure GPA and the driver have same number of counters.
                                // There will be no catastrophic errors if the GPA expects less counters than GL exposes, but we may not have the right counters... and may be reporting bad results.
                                // There could be issues if GPA expects more counters than GL exposes, because we may try to enable a counter that doesn't exist,
                                // in which case we hope the driver will return a 0 result and nothing catastrophic occurs.
                                if (hardware_counters->internal_counter_groups_[g].num_counters != static_cast<unsigned int>(counters))
                                {
                                    std::stringstream error;
                                    error << "GPUPerfAPI's group '" << hardware_counters->internal_counter_groups_[g].name << "' has "
                                          << hardware_counters->internal_counter_groups_[g].num_counters << " counters, but OpenGL exposes " << counters << ".";

                                    // GPA pads few additional counter to some hardware blocks, we need to accommodate that case.
                                    if (hardware_counters->internal_counter_groups_[g].num_counters < static_cast<unsigned int>(counters))
                                    {
                                        // Log as a message, because this isn't so bad.
                                        GPA_LOG_MESSAGE(error.str().c_str());
                                    }
                                    else
                                    {
                                        GpaUInt32 padded_counters =
                                            hardware_counters->GetPaddedCounterCount(hardware_counters->internal_counter_groups_[g].group_index);
                                        if (counters + padded_counters != hardware_counters->internal_counter_groups_[g].num_counters)
                                        {
                                            // On Vega 10 driver exposes 1 extra counter in TCC block.
                                            if (generation == GDT_HW_GENERATION_GFX9 && strncmp(str_name, "TCC", 4) == 0 &&
                                                (counters + padded_counters - 1) != hardware_counters->internal_counter_groups_[g].num_counters)
                                            {
                                                // Counter should match with the driver after accounting padded counters.
                                                GPA_LOG_ERROR(error.str().c_str());
                                            }
                                        }
                                    }
                                }

                                // This assert is good for debugging, but it will fire on most EG cards, because we "expect" SQ to have 8 max counters on cypress (high end), but
                                // we know that it will actually have less on lower end EG cards, and the driver returns the correct values, so our 8 != what the driver returns.
                                // assert( pHardwareCounters->Groups[g].maxActiveCounters == (unsigned int)nMaxActive );
                            }
                        }

                        // Update the group Id based on what was returned from the driver.
                        const GpaUInt64 num_counters_in_group = hardware_counters->internal_counter_groups_[g].num_counters;

                        for (unsigned int c = 0; c < num_counters_in_group; c++)
                        {
                            internal_counter_iter->group_id_driver = perf_groups[driver_group_num];

                            if (internal_counter_iter != hardware_counters->hardware_counters_.end())
                            {
                                ++internal_counter_iter;
                            }
                        }
                    }

                    delete[] perf_groups;
                    success = true;
                }
            }
        }
    }

    return success;
}