//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Utility routines for retrieving ASIC information
//==============================================================================

#include <array>
#include <assert.h>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <string.h>
#include <stdlib.h>
#endif

#include "asic_info.h"

#include "gpu_perf_api_common/logging.h"

#include "gpu_perf_api_counter_generator/gl_entry_points.h"

namespace
{
    constexpr std::string_view kAsicGroupName                = "GPIN";  ///< Driver-defined ASIC info group.
    constexpr GLint            kAsicInfoGroupNotFound        = -1;
    constexpr size_t           kPerfMonitorGroupStringLength = 256;
    constexpr GLint            kSingleMonitorCount           = 1;
    constexpr GLint            kSingleCounterCount           = 1;
    constexpr GLint            kResultUintsPerCounter        = 4;
    constexpr GLint            kResultValueUintOffset        = 3;
    constexpr GLint            kExpectedAsicCounterCount     = 9;

    constexpr unsigned char kAsicRevisionIndex = 0;  ///< Driver-defined counter index for ASIC Id/Revision.
    constexpr unsigned char kAsicNumSimdIndex  = 1;  ///< Driver-defined counter index for number of SIMDs.
    constexpr unsigned char kAsicNumRbIndex    = 2;  ///< Driver-defined counter index for number of RBs.
    constexpr unsigned char kAsicNumSpiIndex   = 3;  ///< Driver-defined counter index for number of SPIs.
    constexpr unsigned char kAsicNumSeIndex    = 4;  ///< Driver-defined counter index for number of SEs.
    constexpr unsigned char kAsicNumSaIndex    = 5;  ///< Driver-defined counter index for number of SAs.
    constexpr unsigned char kAsicNumCuIndex    = 6;  ///< Driver-defined counter index for number of CUs.
    constexpr unsigned char kAsicDevIdIndex    = 7;  ///< Driver-defined counter index for device id.
    constexpr unsigned char kAsicDevRevIndex   = 8;  ///< Driver-defined counter index for revision id.
}  // namespace

namespace ogl_utils
{
    /// @brief Get the group ID for ASICInfo group.
    /// @return -1 if group not found, group ID otherwise.
    GLint GetAsicInfoGroupId()
    {
        GLint num_groups = 0;

        // Get the number of performance counter groups.
        ogl_get_perf_monitor_groups_2_amd(&num_groups, 0, nullptr, nullptr);

        if (num_groups > 0)
        {
            std::vector<GLuint> performance_counter_groups(num_groups);
            std::vector<GLuint> performance_counter_group_instances(num_groups);

            // Get the group Ids.
            ogl_get_perf_monitor_groups_2_amd(nullptr, num_groups, performance_counter_groups.data(), performance_counter_group_instances.data());

            for (GLint i = 0; i < num_groups; i++)
            {
                std::array<char, kPerfMonitorGroupStringLength> group_string = {};

                // ogl_get_perf_monitor_group_string_amd requires a GLsizei.
                constexpr GLsizei kGroupStringSize = static_cast<GLsizei>(group_string.size());

                // Get the group name.
                ogl_get_perf_monitor_group_string_amd(performance_counter_groups[i], kGroupStringSize, nullptr, group_string.data());

                if (kAsicGroupName == group_string.data())
                {
                    return performance_counter_groups[i];
                }
            }
        }

        return kAsicInfoGroupNotFound;
    }

    bool GetAsicInfoFromDriver(AsicInfo& asic_info)
    {
        if (nullptr == ogl_get_perf_monitor_counters_amd || nullptr == ogl_get_perf_monitor_group_string_amd ||
            nullptr == ogl_get_perf_monitor_counter_info_amd || nullptr == ogl_get_perf_monitor_counter_string_amd || nullptr == ogl_gen_perf_monitors_amd ||
            nullptr == ogl_delete_perf_monitors_amd || nullptr == ogl_begin_perf_monitor_amd || nullptr == ogl_end_perf_monitor_amd ||
            nullptr == ogl_get_perf_monitor_counter_data_amd)
        {
            // No AMD_performance_monitor support, means no ASIC info.
            GpaLogger::Instance().LogError("One or more of the common GL_AMD_performance_monitor functions were not found.");
            return false;
        }

        bool found_oglp_entrypoints = (nullptr != ogl_get_perf_monitor_groups_2_amd && nullptr != ogl_select_perf_monitor_counters_2_amd);

        if (!found_oglp_entrypoints)
        {
            // One of the other AMD_performance_monitor extension entrypoints was missing.
            GpaLogger::Instance().LogError("One or more of the other GL_AMD_performance_monitor_2 functions were not found.");
            return false;
        }

        GLint num_counters = 0;
        bool  result       = false;

#ifndef GLES
        if (!ogl_utils::InitializeGlCoreFunctions())
        {
            return false;
        }

        if (ogl_utils::IsMesaDriver())
        {
            GpaLogger::Instance().LogError("The Mesa driver is not supported.");
            return false;
        }

        asic_info.driver_version = ogl_utils::GetDriverVersion();
#else
        asic_info.driver_version = INT_MAX;
#endif

        if (!ogl_utils::IsOglpDriver())
        {
#ifndef GLES
            const GLubyte* gl_version_string = ogl_get_string(GL_VERSION);
            GpaLogger::Instance().LogError("GL_VERSION: {}.", (const char*)gl_version_string);
#endif
            GpaLogger::Instance().LogError("OpenGL driver version is too old. Please update your driver.");
            return false;
        }

        GLint group = GetAsicInfoGroupId();

        if (kAsicInfoGroupNotFound == group)
        {
            GpaLogger::Instance().LogError("Unable to find the GPIN group.");
            return false;
        }

        // Start by getting the list of counters in the group.
        ogl_get_perf_monitor_counters_amd(group, &num_counters, nullptr, 0, nullptr);
        GLenum error_getting_num_gpin_counters = ogl_get_error();
        if (error_getting_num_gpin_counters != GL_NO_ERROR)
        {
            GpaLogger::Instance().LogError("Error getting the number of GPIN counters.");
            return false;
        }

        if (num_counters <= 0) [[unlikely]]
        {
            GpaLogger::Instance().LogError("No counters were found.");
            return false;
        }

        std::vector<GLuint> counter_list(num_counters, 0);

        {
            // Get the list of counters in the group.
            ogl_get_perf_monitor_counters_amd(group, nullptr, nullptr, num_counters, counter_list.data());
            GLenum error_getting_counter_ids = ogl_get_error();
            if (error_getting_counter_ids != GL_NO_ERROR)
            {
                GpaLogger::Instance().LogError("Error getting GPIN counter IDs.");
            }
            else
            {
                // Create a monitor for all GPIN counters.
                GLuint monitor = 0;
                ogl_gen_perf_monitors_amd(kSingleMonitorCount, &monitor);
                GLenum error_gening_gpin_monitor = ogl_get_error();
                if (error_gening_gpin_monitor != GL_NO_ERROR)
                {
                    GpaLogger::Instance().LogError("Error generating monitor for GPIN counters.");
                }
                else
                {
                    // Enable all GPIN counters.
                    ogl_select_perf_monitor_counters_2_amd(monitor, GL_TRUE, group, 0, num_counters, counter_list.data());

                    // Begin / end the monitor so that the data is obtained.
                    ogl_begin_perf_monitor_amd(monitor);
                    GLenum error_begin_gpin_monitor = ogl_get_error();
                    if (error_begin_gpin_monitor != GL_NO_ERROR)
                    {
                        GpaLogger::Instance().LogError("Error beginning GPIN monitor.");
                    }
                    else
                    {
                        ogl_end_perf_monitor_amd(monitor);
                        GLenum error_end_gpin_monitor = ogl_get_error();
                        if (error_end_gpin_monitor != GL_NO_ERROR)
                        {
                            GpaLogger::Instance().LogError("Error ending GPIN monitor.");
                        }

                        // Get the counter result size.
                        GLuint result_size = 0;
                        ogl_get_perf_monitor_counter_data_amd(monitor, GL_PERFMON_RESULT_SIZE_AMD, sizeof(result_size), &result_size, nullptr);

                        // Result should be 4 GLuint per counter.
                        const GLint expected_result_size = (kResultUintsPerCounter * static_cast<GLint>(sizeof(GLuint))) * num_counters;

                        assert(static_cast<GLint>(result_size) == expected_result_size);
                        if (static_cast<GLint>(result_size) == expected_result_size)
                        {
                            // Use std::vector<GLuint> to ensure proper alignment for the buffer.
                            // std::vector<GLubyte> only guarantees 1-byte alignment, which could cause
                            // undefined behavior on platforms with strict alignment requirements when
                            // reinterpreting as GLuint* (which requires 4-byte alignment).
                            std::vector<GLuint> counter_data(result_size / sizeof(GLuint));

                            // Get the counter results.
                            ogl_get_perf_monitor_counter_data_amd(
                                monitor, GL_PERFMON_RESULT_AMD, result_size, counter_data.data(), nullptr);

                            for (int i = 0; i < num_counters; i++)
                            {
                                // Index into the result array for each counter.
                                const unsigned int value = counter_data[(i * kResultUintsPerCounter) + kResultValueUintOffset];

                                switch (i)
                                {
                                case kAsicRevisionIndex:
                                    asic_info.asic_revision = value;
                                    break;

                                case kAsicNumSimdIndex:
                                    asic_info.num_simd = value;
                                    break;

                                case kAsicNumRbIndex:
                                    asic_info.num_rb = value;
                                    break;

                                case kAsicNumSpiIndex:
                                    asic_info.num_spi = value;
                                    break;

                                case kAsicNumSeIndex:
                                    asic_info.num_se = value;
                                    break;

                                case kAsicNumSaIndex:
                                    asic_info.num_sa_per_se = value;
                                    break;

                                case kAsicNumCuIndex:
                                    asic_info.num_cu = value;
                                    break;

                                case kAsicDevIdIndex:
                                    asic_info.device_id = value;
                                    GpaLogger::Instance().LogMessage("Retrieved ASIC device ID: 0x{:04X}.", value);
                                    break;

                                case kAsicDevRevIndex:
                                    asic_info.device_rev = value;
                                    GpaLogger::Instance().LogMessage("Retrieved ASIC device revision: 0x{:04X}.", value);
                                    break;
                                }

                                ogl_select_perf_monitor_counters_2_amd(monitor, GL_FALSE, group, 0, kSingleCounterCount, &counter_list[i]);
                            }

                            // Treat this as successful if there were 9 counters available.
                            result = (kExpectedAsicCounterCount == num_counters);
                        }
                    }
                }

                ogl_delete_perf_monitors_amd(kSingleMonitorCount, &monitor);
            }
        }

        if (result)
        {
            if (asic_info.device_rev == asic_info.kUnassignedAsicInfo || asic_info.device_id == asic_info.kUnassignedAsicInfo)
            {
                GpaLogger::Instance().LogMessage("WARNING: Did not receive either a Device ID or Revision ID from the OpenGL implementation.");
            }
            else
            {
                GpaLogger::Instance().LogMessage("Driver version {} returned Device ID 0x{:04X} and Revision ID 0x{:02X}.",
                                                 asic_info.driver_version,
                                                 asic_info.device_id,
                                                 asic_info.device_rev);
            }
        }

        return result;
    }

}  // namespace ogl_utils
