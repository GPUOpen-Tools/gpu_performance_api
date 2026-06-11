//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA GL Context Implementation.
//==============================================================================

#include "gpu_perf_api_gl/gl_gpa_context.h"

#include <memory>
#include <unordered_map>
#include <vector>

#include "gpu_perf_api_common/gpa_context_counter_mediator.h"
#include "gpu_perf_api_common/gpa_unique_object.h"

#include "gpu_perf_api_counter_generator/gpa_hardware_counters.h"

#include "gpu_perf_api_gl/gl_gpa_session.h"

GlGpaContext::GlGpaContext(GlContextPtr context, const GpaHwInfo& hw_info, GpaOpenContextFlags context_flags)
    : GpaContext(hw_info, context_flags)
    , gl_context_(context)
    , clock_mode_(ogl_utils::kAmdXDefaultMode)
    , driver_supports_GL1CG_(false)
    , driver_supports_ATC_(false)
    , driver_supports_ATCL2_(false)
    , driver_supports_CHCG_(false)
    , driver_supports_GUS_(false)
    , driver_supports_UMC_(false)
    , driver_supports_RPB_(false)
    , driver_supports_PC_(false)
    , driver_supports_GRBMSE_(false)
{
}

GlGpaContext::~GlGpaContext()
{
    GpaStatus set_stable_clocks_status = SetStableClocks(false);

    if (kGpaStatusOk != set_stable_clocks_status)
    {
        GpaLogger::Instance().LogError("Driver was unable to set stable clocks back to default.");
#ifdef __linux__
        GpaLogger::Instance().LogMessage("In Linux, make sure to run your application with root privileges.");
#endif
    }
}

GpaSessionId GlGpaContext::CreateSession(GpaSessionSampleType sample_type)
{
    auto          new_gpa_gl_gpa_session = std::make_unique<GlGpaSession>(this, sample_type);
    GlGpaSession* raw_session            = new_gpa_gl_gpa_session.get();

    AddGpaSession(std::move(new_gpa_gl_gpa_session));

    return reinterpret_cast<GpaSessionId>(GpaUniqueObjectManager::Instance().CreateObject(raw_session));
}

bool GlGpaContext::DeleteSession(GpaSessionId session_id)
{
    bool is_deleted = false;

    GlGpaSession* gl_session = reinterpret_cast<GlGpaSession*>(session_id->Object());

    if (nullptr != gl_session)
    {
        GpaUniqueObjectManager::Instance().DeleteObject(gl_session);
        // Removing from the session list triggers destruction via unique_ptr.
        RemoveGpaSession(gl_session);
        is_deleted = true;
    }

    return is_deleted;
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
        GpaLogger::Instance().LogError("Driver was unable to set stable clocks for profiling.");
#ifdef __linux__
        GpaLogger::Instance().LogMessage("In Linux, make sure to run your application with root privileges.");
#endif
    }

    if (!PopulateDriverCounterGroupInfo())
    {
        GpaLogger::Instance().LogError("Failed to populate driver counter group info.");
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
        GpaLogger::Instance().LogMessage("glSetGpaDeviceClockModeAMDX extension is not available.");
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

            unsigned int clock_result = ogl_utils::ogl_set_gpa_device_clock_mode_amd_x(&clock_mode);
            result                    = (ogl_utils::kGlSetClockSuccess == clock_result) ? kGpaStatusOk : kGpaStatusErrorDriverNotSupported;

            if (clock_result != ogl_utils::kGlSetClockSuccess)
            {
                GpaLogger::Instance().LogError("Failed to set ClockMode for profiling.");
            }
        }
    }

    return result;
}

bool GlGpaContext::PopulateDriverCounterGroupInfo()
{
    if (driver_counter_group_info_.empty())
    {
        GLint num_groups = 0;
        ogl_utils::ogl_get_perf_monitor_groups_2_amd(&num_groups, 0, nullptr, nullptr);
        assert(num_groups > 0);

        if (num_groups == 0)
        {
            GpaLogger::Instance().LogError("No counter groups are exposed by GL_AMD_performance_monitor.");
            return false;
        }
        else
        {
            driver_counter_group_info_.reserve(num_groups);

            std::vector<GLuint> perf_groups(num_groups);
            std::vector<GLuint> group_instances(num_groups);

            ogl_utils::ogl_get_perf_monitor_groups_2_amd(nullptr, num_groups, perf_groups.data(), group_instances.data());

            // Iterate over all performance monitor groups and populate driver_counter_group_info_ with data returned from these groups.
            for (GLint index = 0; index < num_groups; ++index)
            {
                GpaGlPerfMonitorGroupData group_data;
                group_data.group_id      = perf_groups[index];
                group_data.num_instances = group_instances[index];

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
                else if (strncmp(group_data.group_name, "ATC", 3) == 0)
                {
                    driver_supports_ATC_ = true;
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
                else if (strncmp(group_data.group_name, "RPB", 3) == 0)
                {
                    driver_supports_RPB_ = true;
                }
                else if (strncmp(group_data.group_name, "PC", 2) == 0)
                {
                    driver_supports_PC_ = true;
                }
                else if (strncmp(group_data.group_name, "GRBM_SE", 7) == 0)
                {
                    driver_supports_GRBMSE_ = true;
                }
            }
        }
    }
    else
    {
        GpaLogger::Instance().LogDebugMessage("Driver counter group info is not empty and has already been populated.");
    }

    return true;
}

bool GlGpaContext::ValidateAndUpdateGlCounters(IGpaSession* session) const
{
    bool             success = false;
    const GpaHwInfo& hw_info = GetHwInfo();

    if (!hw_info.GetDeviceDescription().has_value()) [[unlikely]]
    {
        GpaLogger::Instance().LogError("Unable to get necessary hardware info.");
        return success;
    }

    const device_info::HwGeneration generation = hw_info.GetHwGeneration().value();

    if (driver_counter_group_info_.empty())
    {
        GpaLogger::Instance().LogError("No counter groups are exposed by GL_AMD_performance_monitor.");
    }
    else
    {
        // Use const_cast to GpaHardwareCounters* here as a feasible and simple workaround. OpenGL is the only API in which we are changing the hardware counter info.
        IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::GetCounterAccessor(session);
        assert(counter_accessor != nullptr);
        if (counter_accessor == nullptr)
        {
            GpaLogger::Instance().LogError("Unable to get the counter accessor.");
            return false;
        }

        GpaHardwareCounters& hardware_counters = const_cast<GpaHardwareCounters&>(counter_accessor->GetHardwareCounters());
        const GpaUInt32      num_expected_driver_groups =
            static_cast<GpaUInt32>(hardware_counters.counter_groups_array_.size() + hardware_counters.additional_group_count_) - 1;

        // Accumulate the total number of block instances available, since that is what GPA uses internally.
        // The driver only exposes block instances on the current hardware, so this total will be less than what GPA expects if lower-end hardware is used.
        // The extra block instances in GPA will be ignored when profiling.
        const GpaUInt32 total_group_instances = std::accumulate(
            driver_counter_group_info_.begin(), driver_counter_group_info_.end(), 0, [](GpaUInt32 total, const GpaGlPerfMonitorGroupData& data) {
                return total + data.num_instances;
            });

        if (total_group_instances > num_expected_driver_groups)
        {
            // Report a message if the driver exposes more groups than expected but allow the code to continue.
            GpaLogger::Instance().LogMessage("GL_AMD_performance_monitor exposes {} counter group instances, but GPUPerfAPI only expected {}.",
                                             total_group_instances,
                                             num_expected_driver_groups);
        }

        // Build a mapping from GPA group index to driver group ID by iterating GPA groups in order
        // and matching them against the driver's sequential group list.
        // This decouples the group-name matching logic from hardware_counters_ iteration, which is
        // necessary because in internal builds the global counter index ordering in hardware_counters_
        // differs from the internal_counter_groups_ ordering.
        std::unordered_map<GpaUInt32, GpaUInt32> gpa_group_index_to_driver_id;

        auto            driver_group_iter             = driver_counter_group_info_.cbegin();
        const GpaUInt32 internal_counter_groups_count = static_cast<GpaUInt32>(hardware_counters.internal_counter_groups_.size());

        for (GpaUInt32 gpa_group_index = 0; gpa_group_index < internal_counter_groups_count; ++gpa_group_index)
        {
            const GpaCounterGroupDesc& gpa_group = hardware_counters.internal_counter_groups_[gpa_group_index];
            const std::string          gpa_group_name(gpa_group.name);

            // These groups only exist on some hardware. If the driver doesn't expose them, skip this GPA group.
            auto is_unsupported_group = [&](bool driver_supports, const std::string& prefix) -> bool {
                return !driver_supports && gpa_group_name.find(prefix) == 0;
            };

            if (is_unsupported_group(driver_supports_GL1CG_, "GL1CG") || is_unsupported_group(driver_supports_ATCL2_, "ATCL2") ||
                is_unsupported_group(driver_supports_ATC_, "ATC") || is_unsupported_group(driver_supports_CHCG_, "CHCG") ||
                is_unsupported_group(driver_supports_GUS_, "GUS") || is_unsupported_group(driver_supports_UMC_, "UMC") ||
                is_unsupported_group(driver_supports_RPB_, "RPB") || is_unsupported_group(driver_supports_PC_, "PC") ||
                is_unsupported_group(driver_supports_GRBMSE_, "GRBMSE"))
            {
                continue;
            }

            // Increment the driver_group_iter if this is not the first iteration of the loop.
            if (gpa_group_index != 0)
            {
                // Block instance index reset back to 0 because a new block has started.
                if (gpa_group.block_instance == 0)
                {
                    ++driver_group_iter;
                }

                if (driver_group_iter == driver_counter_group_info_.cend())
                {
                    // Exit loop now, but note there will be other GPA groups (such as GPUTime) that are not exposed by the driver.
                    break;
                }
            }

            // Get the driver group name and then extend it to include the block instance.
            std::string driver_group_name_extended(driver_group_iter->group_name);

            // GPA does not yet support DF_MALL.
            if (driver_group_name_extended.find("DF_MALL") == 0)
            {
                // Decrement index for GPA group so that same group is used on next iteration of loop.
                gpa_group_index -= 1;
                continue;
            }

            // On GFX11.5 APUs the driver exposes DMA, RPB, UMCCH, and GE groups that GPA has no corresponding entries for.
            if (generation == device_info::HwGeneration::kGfx11_5 && (driver_group_name_extended == "DMA" || driver_group_name_extended == "RPB" ||
                                                                      driver_group_name_extended == "UMCCH" || driver_group_name_extended == "GE"))
            {
                gpa_group_index -= 1;
                continue;
            }

            // On GFX11 and newer, OGLP may expose SQ_ES, SQ_VS, and SQ_LS, even though they are not actually supported on the hardware.
            if (generation >= device_info::HwGeneration::kGfx11 &&
                (driver_group_name_extended.find("SQ_ES") == 0 || driver_group_name_extended.find("SQ_VS") == 0 ||
                 driver_group_name_extended.find("SQ_LS") == 0))
            {
                gpa_group_index -= 1;
                continue;
            }

            // Address blocks with slightly different names in the following conditionals.
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
                // Unreachable on GFX11.5: the generation-scoped skip above consumes DMA before this point.
                driver_group_name_extended = "SDMA";
            }
            else if (driver_group_name_extended == "EA")
            {
                driver_group_name_extended = "GCEA";
            }
            else if (generation <= device_info::HwGeneration::kGfx11 && driver_group_name_extended == "UMCCH")
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
            else if ((generation == device_info::HwGeneration::kGfx11_5 || generation >= device_info::HwGeneration::kGfx12) &&
                     driver_group_name_extended == "GE_SE")
            {
                // GE2_SE is the actual hardware block name in GFX11.5 and GFX12. The driver keeps "GE_SE"
                // for backwards compatibility, but GPA aligns with hardware docs and profiling tools rather
                // than the driver name.
                // GFX115 is listed explicitly because its enum value (15) is numerically greater than GFX12 (13),
                // so a bare ">= GFX12" would also catch it — but that ordering is non-obvious and fragile.
                driver_group_name_extended = "GE2_SE";
            }
            else if (generation >= device_info::HwGeneration::kGfx11 && driver_group_name_extended == "SQ")
            {
                driver_group_name_extended = "SQG";
            }
            else if (generation >= device_info::HwGeneration::kGfx11 && driver_group_name_extended == "SQ_GS")
            {
                driver_group_name_extended = "SQG_GS";
            }
            else if (generation >= device_info::HwGeneration::kGfx11 && driver_group_name_extended == "SQ_PS")
            {
                driver_group_name_extended = "SQG_PS";
            }
            else if (generation >= device_info::HwGeneration::kGfx11 && driver_group_name_extended == "SQ_HS")
            {
                driver_group_name_extended = "SQG_HS";
            }
            else if (generation >= device_info::HwGeneration::kGfx11 && driver_group_name_extended == "SQ_CS")
            {
                driver_group_name_extended = "SQG_CS";
            }
            else if ((generation == device_info::HwGeneration::kGfx11 || generation == device_info::HwGeneration::kGfx11_5) &&
                     driver_group_name_extended == "MCVML2")
            {
                // GFX11 and GFX11.5 expose this as "MCVML2" but GPA uses "GCVML2" internally.
                driver_group_name_extended = "GCVML2";
            }
            else if (driver_group_name_extended == "EACPWD")
            {
                driver_group_name_extended = "GC_EA_CPWD";
            }
            else if (driver_group_name_extended == "EASE")
            {
                driver_group_name_extended = "GC_EA_SE";
            }

            if (driver_group_iter->num_instances > 1)
            {
                // Append the current GPA block instance to the current driver group name on OGLP driver when the hardware has more than one instance of this group.
                driver_group_name_extended.append(std::to_string(gpa_group.block_instance));
            }

            // Check if current gpa_group_name matches current driver_group_name and then validate and update if match is found.
            // The first condition will occur if the groups are an exact match and the second condition will occur if GPA knows about multiple block instances but the current hardware only has one.
            if (gpa_group_name == driver_group_name_extended || gpa_group_name.find(driver_group_name_extended) == 0)
            {
                // Make sure the GPA number of counters and maximum active counters match for this block (regardless of which block instance).
                // Remove the number of counters added for padding which are used to account for other hardware, so the driver will not be returning them on the current hardware.
                const GpaUInt32 num_padding_counters = hardware_counters.GetPaddedCounterCount(gpa_group.group_index);
                const GpaUInt32 gpa_num_counters     = (gpa_group.num_counters - num_padding_counters);
                if (static_cast<GpaUInt32>(driver_group_iter->num_counters) != gpa_num_counters)
                {
                    GpaLogger::Instance().LogMessage("GPA's group {} is expecting {} counters but the driver is reporting {}.",
                                                     gpa_group_name,
                                                     gpa_num_counters,
                                                     driver_group_iter->num_counters);
                }
                const GpaUInt32 gpa_num_max_active = gpa_group.max_active_discrete_counters;
                if (static_cast<GpaUInt32>(driver_group_iter->max_active_discrete_counters_per_instance) != gpa_num_max_active)
                {
                    GpaLogger::Instance().LogMessage("GPA's group {} is expecting {} max active discrete counters, but the driver is reporting {}.",
                                                     gpa_group_name,
                                                     gpa_num_max_active,
                                                     driver_group_iter->max_active_discrete_counters_per_instance);
                }

                gpa_group_index_to_driver_id[gpa_group_index] = driver_group_iter->group_id;
            }
            else
            {
                GpaLogger::Instance().LogError("GPA is expecting group {} but the driver is exposing group {}. This GPA group will not be updated.",
                                               gpa_group_name,
                                               driver_group_iter->group_name);

                // Advance past the unexpected driver group and retry the same GPA group, so that a
                // single run surfaces all mismatches rather than stopping at the first.
                ++driver_group_iter;
                if (driver_group_iter == driver_counter_group_info_.cend())
                {
                    break;
                }
                gpa_group_index -= 1;
            }
        }

        for (auto& [counter_index, counter_ext] : hardware_counters.hardware_counters_)
        {
            auto it = gpa_group_index_to_driver_id.find(counter_ext.group_index);
            if (it != gpa_group_index_to_driver_id.end())
            {
                counter_ext.group_id_driver = it->second;
            }
        }

        success = true;
    }

    return success;
}

GpaUInt32 GlGpaContext::GetNumInstances(unsigned int driver_group_id) const
{
    GpaUInt32 num_instances = 0;
    for (const GpaGlPerfMonitorGroupData& group : driver_counter_group_info_)
    {
        if (driver_group_id == group.group_id)
        {
            num_instances = static_cast<GpaUInt32>(group.num_instances);
            break;
        }
    }
    return num_instances;
}

GpaUInt32 GlGpaContext::GetMaxEventId(unsigned int driver_group_id) const
{
    GpaUInt32 max_event_id = 0;
    for (const GpaGlPerfMonitorGroupData& group : driver_counter_group_info_)
    {
        if (driver_group_id == group.group_id)
        {
            // Subtract one to get the maximum event ID (0-based) from the number of counters (1-based).
            max_event_id = static_cast<GpaUInt32>(group.num_counters - 1);
            break;
        }
    }
    return max_event_id;
}
