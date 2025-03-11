//==============================================================================
// Copyright (c) 2006-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Utility routines for retrieving ASIC information
//==============================================================================

#include <assert.h>
#include <sstream>
#include <string>

#ifdef _LINUX
#include <string.h>
#include <stdlib.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#include "ADLUtil.h"
#include "asic_info.h"

#include "gpu_perf_api_common/logging.h"

#include "gpu_perf_api_counter_generator/gl_entry_points.h"

#define ASIC_GROUP "GPIN"                        ///< Driver-defined ASIC info group.
constexpr unsigned char kAsicRevisionIndex = 0;  ///< Driver-defined counter index for ASIC Id/Revision.
constexpr unsigned char kAsicNumSimdIndex  = 1;  ///< Driver-defined counter index for number of SIMDs.
constexpr unsigned char kAsicNumRbIndex    = 2;  ///< Driver-defined counter index for number of RBs.
constexpr unsigned char kAsicNumSpiIndex   = 3;  ///< Driver-defined counter index for number of SPIs.
constexpr unsigned char kAsicNumSeIndex    = 4;  ///< Driver-defined counter index for number of SEs.
constexpr unsigned char kAsicNumSaIndex    = 5;  ///< Driver-defined counter index for number of SAs.
constexpr unsigned char kAsicNumCuIndex    = 6;  ///< Driver-defined counter index for number of CUs.
constexpr unsigned char kAsicDevIdIndex    = 7;  ///< Driver-defined counter index for device id.
constexpr unsigned char kAsicDevRevIndex   = 8;  ///< Driver-defined counter index for revision id.

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
            GLuint* performance_counter_groups          = new (std::nothrow) GLuint[num_groups];
            GLuint* performance_counter_group_instances = new (std::nothrow) GLuint[num_groups];

            if (nullptr != performance_counter_groups && nullptr != performance_counter_group_instances)
            {
                // Get the group Ids.
                ogl_get_perf_monitor_groups_2_amd(nullptr, num_groups, performance_counter_groups, performance_counter_group_instances);

                for (int i = 0; i < num_groups; i++)
                {
                    char group_string[256];

                    // Get the group name.
                    ogl_get_perf_monitor_group_string_amd(performance_counter_groups[i], 255, nullptr, group_string);

                    if (!strcmp(group_string, ASIC_GROUP))
                    {
                        GLint group_id = performance_counter_groups[i];
                        delete[] performance_counter_groups;
                        delete[] performance_counter_group_instances;
                        return group_id;
                    }
                }

                delete[] performance_counter_groups;
                delete[] performance_counter_group_instances;
            }
        }

        return -1;
    }

    bool GetAsicInfoFromDriver(AsicInfo& asic_info)
    {
        if (nullptr == ogl_get_perf_monitor_counters_amd || nullptr == ogl_get_perf_monitor_group_string_amd ||
            nullptr == ogl_get_perf_monitor_counter_info_amd || nullptr == ogl_get_perf_monitor_counter_string_amd || nullptr == ogl_gen_perf_monitors_amd ||
            nullptr == ogl_delete_perf_monitors_amd || nullptr == ogl_begin_perf_monitor_amd || nullptr == ogl_end_perf_monitor_amd ||
            nullptr == ogl_get_perf_monitor_counter_data_amd)
        {
            // No AMD_performance_monitor support, means no ASIC info.
            GPA_LOG_ERROR("One or more of the common GL_AMD_performance_monitor functions were not found.");
            return false;
        }

        bool found_oglp_entrypoints = (nullptr != ogl_get_perf_monitor_groups_2_amd && nullptr != ogl_select_perf_monitor_counters_2_amd);

        if (!found_oglp_entrypoints)
        {
            // One of the other AMD_performance_monitor extension entrypoints was missing.
            GPA_LOG_ERROR("One or more of the other GL_AMD_performance_monitor_2 functions were not found.");
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
            GPA_LOG_ERROR("The Mesa driver is not supported.");
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
            GPA_LOG_ERROR("GL_VERSION: %s.", (const char*)gl_version_string);
#endif
            GPA_LOG_ERROR("OpenGL driver version is too old. Please update your driver.");
            return false;
        }

        GLint group = GetAsicInfoGroupId();

        if (-1 == group)
        {
            GPA_LOG_ERROR("Unable to find the GPIN group.");
            return false;
        }

        // Start by getting the list of counters in the group.
        ogl_get_perf_monitor_counters_amd(group, &num_counters, nullptr, 0, nullptr);
        GLenum error_getting_num_gpin_counters = ogl_get_error();
        if (error_getting_num_gpin_counters != GL_NO_ERROR)
        {
            GPA_LOG_ERROR("Error getting the number of GPIN counters.");
            return false;
        }

        GLuint* counter_list = new (std::nothrow) GLuint[num_counters];

        if (nullptr == counter_list)
        {
            GPA_LOG_ERROR("Failed to allocate counter list to get ASIC info.");
            return false;
        }
        else
        {
            memset(counter_list, 0, num_counters * sizeof(GLuint));

            // Get the list of counters in the group.
            ogl_get_perf_monitor_counters_amd(group, nullptr, nullptr, num_counters, counter_list);
            GLenum error_getting_counter_ids = ogl_get_error();
            if (error_getting_counter_ids != GL_NO_ERROR)
            {
                GPA_LOG_ERROR("Error getting GPIN counter IDs.");
            }
            else
            {
                // Create a monitor for all GPIN counters.
                GLuint monitor = 0;
                ogl_gen_perf_monitors_amd(1, &monitor);
                GLenum error_gening_gpin_monitor = ogl_get_error();
                if (error_gening_gpin_monitor != GL_NO_ERROR)
                {
                    GPA_LOG_ERROR("Error generating monitor for GPIN counters.");
                }
                else
                {
                    // Enable all GPIN counters.
                    ogl_select_perf_monitor_counters_2_amd(monitor, GL_TRUE, group, 0, num_counters, &counter_list[0]);

                    // Begin / end the monitor so that the data is obtained.
                    ogl_begin_perf_monitor_amd(monitor);
                    GLenum error_begin_gpin_monitor = ogl_get_error();
                    if (error_begin_gpin_monitor != GL_NO_ERROR)
                    {
                        GPA_LOG_ERROR("Error beginning GPIN monitor.");
                    }
                    else
                    {
                        ogl_end_perf_monitor_amd(monitor);
                        GLenum error_end_gpin_monitor = ogl_get_error();
                        if (error_end_gpin_monitor != GL_NO_ERROR)
                        {
                            GPA_LOG_ERROR("Error ending GPIN monitor.");
                        }

                        // Get the counter result size.
                        GLuint result_size = 0;
                        ogl_get_perf_monitor_counter_data_amd(monitor, GL_PERFMON_RESULT_SIZE_AMD, sizeof(result_size), &result_size, nullptr);

                        // Result should be 4 GLuint per counter.
                        GLint expected_result_size = (4 * sizeof(GLuint)) * num_counters;

                        assert(static_cast<GLint>(result_size) == expected_result_size);
                        if (static_cast<GLint>(result_size) == expected_result_size)
                        {
                            GLubyte* counter_data = new (std::nothrow) GLubyte[result_size];

                            if (nullptr != counter_data)
                            {
                                // Get the counter results.
                                ogl_get_perf_monitor_counter_data_amd(
                                    monitor, GL_PERFMON_RESULT_AMD, result_size, reinterpret_cast<GLuint*>(counter_data), nullptr);

                                for (int i = 0; i < num_counters; i++)
                                {
                                    // Index into the result array for each counter.
                                    unsigned int value = (reinterpret_cast<GLuint*>(counter_data))[(i * 4) + 3];

                                    std::stringstream message;

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
                                        GPA_LOG_MESSAGE("Retrieved ASIC device ID: 0x%04x.", value);
                                        break;

                                    case kAsicDevRevIndex:
                                        asic_info.device_rev = value;
                                        GPA_LOG_MESSAGE("Retrieved ASIC device revision: 0x%04x.", value);
                                        break;
                                    }

                                    ogl_select_perf_monitor_counters_2_amd(monitor, GL_FALSE, group, 0, 1, &counter_list[i]);
                                }

                                delete[] counter_data;

                                // Treat this as successful if there were 9 counters available.
                                // This makes the assumption that we successfully read all values and they mean what we think they do.
                                result = (9 == num_counters);
                            }
                        }
                    }
                }

                ogl_delete_perf_monitors_amd(1, &monitor);
            }

            delete[] counter_list;
        }

        if (result)
        {
            if (asic_info.device_rev == asic_info.kUnassignedAsicInfo || asic_info.device_id == asic_info.kUnassignedAsicInfo)
            {
                GPA_LOG_MESSAGE("WARNING: Did not receive either a Device ID or Revision ID from the OpenGL implementation.");
            }
            else
            {
                GPA_LOG_MESSAGE(
                    "Driver version %d returned Device ID 0x%04X and Revision ID 0x%02X.", asic_info.driver_version, asic_info.device_id, asic_info.device_rev);
            }
        }

        return result;
    }

}  // namespace ogl_utils
