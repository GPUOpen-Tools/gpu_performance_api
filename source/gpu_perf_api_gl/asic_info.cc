//==============================================================================
// Copyright (c) 2006-2021 Advanced Micro Devices, Inc. All rights reserved.
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
#include "DeviceInfo.h"

#include "gpu_perf_api_common/logging.h"

#include "gpu_perf_api_counter_generator/gl_entry_points.h"

#define ASIC_GROUP "GPIN"                       ///< Driver-defined ASIC info group.
constexpr unsigned char kAsicTypeIndex    = 0;  ///< Driver-defined counter index for ASIC type.
constexpr unsigned char kAsicNumSimdIndex = 1;  ///< Driver-defined counter index for number of SIMDs.
constexpr unsigned char kAsicNumRbIndex   = 2;  ///< Driver-defined counter index for number of RBs.
constexpr unsigned char kAsicNumSpiIndex  = 3;  ///< Driver-defined counter index for number of SPIs.
constexpr unsigned char kAsicNumSeIndex   = 4;  ///< Driver-defined counter index for number of SEs.
constexpr unsigned char kAsicNumSaIndex   = 5;  ///< Driver-defined counter index for number of SAs.
constexpr unsigned char kAsicNumCuIndex   = 6;  ///< Driver-defined counter index for number of CUs.
constexpr unsigned char kAsicDevIdIndex   = 7;  ///< Driver-defined counter index for device id.
constexpr unsigned char kAsicDevRevIndex  = 8;  ///< Driver-defined counter index for revision id.

namespace ogl_utils
{
    /// @brief Get the group ID for ASICInfo group.
    /// @return -1 if group not found, group ID otherwise.
    GLint GetAsicInfoGroupId()
    {
        GLint num_groups = 0;

        // Get the number of performance counter groups.
        ogl_get_perf_monitor_groups_amd(&num_groups, 0, nullptr);

        if (num_groups > 0)
        {
            GLuint* performance_counter_groups = new (std::nothrow) GLuint[num_groups];

            if (nullptr != performance_counter_groups)
            {
                // Get the group Ids.
                ogl_get_perf_monitor_groups_amd(nullptr, num_groups, performance_counter_groups);

                for (int i = 0; i < num_groups; i++)
                {
                    char group_string[256];

                    // Get the group name.
                    ogl_get_perf_monitor_group_string_amd(performance_counter_groups[i], 255, nullptr, group_string);

                    if (!strcmp(group_string, ASIC_GROUP))
                    {
                        GLint group_id = performance_counter_groups[i];
                        delete[] performance_counter_groups;
                        return group_id;
                    }
                }

                delete[] performance_counter_groups;
            }
        }

        return -1;
    }

#ifndef GLES

    /// @brief Parses a version number like this: "4.2.12325 Compatibility Profile Context 13.100.0.0".
    /// to extract the "12325" portion.
    ///
    /// @param version_gl_string The version string to extract the number from.
    ///
    /// @return 0 on failure, the build version number on success
    int ExtractDriverVersionNumber(const GLubyte* version_gl_string)
    {
        // Initialize to INT_MAX to simulate most recent driver.
        int version = INT_MAX;

        if (nullptr != version_gl_string)
        {
            const char* version_c_string = reinterpret_cast<const char*>(version_gl_string);

            std::string version_string(version_c_string);

            // The build number ends at the first space.
            const size_t end_build = version_string.find_first_of(' ');

            // Truncate the input at the first space.
            version_string = version_string.substr(0, end_build);

            // The build number starts after the last decimal point.
            const size_t first_pos = version_string.find_first_of('.');
            const size_t last_pos  = version_string.find_last_of('.');

            if (first_pos < last_pos)
            {
                // The build number starts one character after the decimal.
                const size_t start_build = last_pos + 1;

                // Parse the version number.
                std::istringstream iss(version_string.substr(start_build, end_build - start_build));
                iss >> version;

                // Couldn't extract version -- return INT_MAX to simulate most recent driver.
                if (iss.fail())
                {
                    version = INT_MAX;
                }
            }

            if (version == INT_MAX)
            {
                std::string message = "Unable to parse driver version from GL_VERSION string: '";
                message.append((char*)version_gl_string);
                message.append("', so assuming it is the most recent driver version.");
                GPA_LOG_MESSAGE(message.c_str());
            }
            else if (version == 0)
            {
                std::string message = "Detected pre-release driver based on '";
                message.append((char*)version_gl_string);
                message.append("', so assuming it is the most recent driver version.");
                GPA_LOG_MESSAGE(message.c_str());

                version = INT_MAX;
            }
        }

        return version;
    }

#endif

    void AsicInfoManager::InitializeAsicInfo()
    {
        // This static assert will help to find error when we update the AsicIdEnum for new hardware.
        // Upon failure, we need to add suitable entry for public device and update the static assert for update count.
        static_assert(kAsicIdLast == 43, "AsicIdEnum has changed, add suitable entry for asic info.");

        if (!is_asic_info_initialized_)
        {
            for (uint32_t asic_id_iter = kAsicIdFirst; asic_id_iter != kAsicIdLast; ++asic_id_iter)
            {
                AsicIdInfo asic_id_info = {};
                asic_id_info.is_apu     = false;

                switch (asic_id_iter)
                {
                case kAsicIdTahitiP:
                    asic_id_info.asic_type         = kAsicGfx6;
                    asic_id_info.gdt_asic_type     = GDT_TAHITI_PRO;
                    asic_id_info.default_device_id = 0x679A;
                    break;

                case kAsicIdPitcairnPm:
                    asic_id_info.asic_type         = kAsicGfx6;
                    asic_id_info.gdt_asic_type     = GDT_PITCAIRN_PRO;
                    asic_id_info.default_device_id = 0x6819;
                    break;

                case kAsicIdCapeverdeM:
                    asic_id_info.asic_type         = kAsicGfx6;
                    asic_id_info.gdt_asic_type     = GDT_CAPEVERDE_PRO;
                    asic_id_info.default_device_id = 0x6822;
                    break;

                case kAsicIdOlandM:
                    asic_id_info.asic_type         = kAsicGfx6;
                    asic_id_info.gdt_asic_type     = GDT_OLAND;
                    asic_id_info.default_device_id = 0x6610;
                    break;

                case kAsicIdHainanM:
                    asic_id_info.asic_type         = kAsicGfx6;
                    asic_id_info.gdt_asic_type     = GDT_HAINAN;
                    asic_id_info.default_device_id = 0x6660;
                    break;

                case kAsicIdBonaireM:
                    asic_id_info.asic_type         = kAsicGfx7;
                    asic_id_info.gdt_asic_type     = GDT_BONAIRE;
                    asic_id_info.default_device_id = 0x665C;
                    break;

                case kAsicIdHawaiiP:
                    asic_id_info.asic_type         = kAsicGfx7;
                    asic_id_info.gdt_asic_type     = GDT_HAWAII;
                    asic_id_info.default_device_id = 0x67B0;
                    break;

                case kAsicIdKalindi:
                    asic_id_info.asic_type         = kAsicGfx7;
                    asic_id_info.gdt_asic_type     = GDT_KALINDI;
                    asic_id_info.default_device_id = 0x9830;
                    asic_id_info.is_apu            = true;
                    break;

                case kAsicIdGodavari:
                    asic_id_info.asic_type         = kAsicGfx7;
                    asic_id_info.gdt_asic_type     = GDT_KALINDI;
                    asic_id_info.default_device_id = 0x9855;
                    asic_id_info.is_apu            = true;
                    break;

                case kAsicIdSpectre:
                    asic_id_info.asic_type         = kAsicGfx7;
                    asic_id_info.gdt_asic_type     = GDT_SPECTRE;
                    asic_id_info.default_device_id = 0x130C;
                    asic_id_info.is_apu            = true;
                    break;

                case kAsicIdSpooky:
                    asic_id_info.asic_type         = kAsicGfx7;
                    asic_id_info.gdt_asic_type     = GDT_SPOOKY;
                    asic_id_info.default_device_id = 0x130B;
                    asic_id_info.is_apu            = true;
                    break;

                case kAsicIdIcelandM:
                    asic_id_info.asic_type         = kAsicGfx8;
                    asic_id_info.gdt_asic_type     = GDT_ICELAND;
                    asic_id_info.default_device_id = 0x6900;
                    break;

                case kAsicIdTongaP:
                    asic_id_info.asic_type         = kAsicGfx8;
                    asic_id_info.gdt_asic_type     = GDT_TONGA;
                    asic_id_info.default_device_id = 0x6920;
                    break;

                case kAsicIdFijiP:
                    asic_id_info.asic_type         = kAsicGfx8;
                    asic_id_info.gdt_asic_type     = GDT_FIJI;
                    asic_id_info.default_device_id = 0x7300;
                    break;

                case kAsicIdEllesmere:
                    asic_id_info.asic_type         = kAsicGfx8;
                    asic_id_info.gdt_asic_type     = GDT_ELLESMERE;
                    asic_id_info.default_device_id = 0x67DF;
                    break;

                case kAsicIdBaffin:
                    asic_id_info.asic_type         = kAsicGfx8;
                    asic_id_info.gdt_asic_type     = GDT_BAFFIN;
                    asic_id_info.default_device_id = 0x67FF;
                    break;

                case kAsicIdLexa:
                    asic_id_info.asic_type         = kAsicGfx8;
                    asic_id_info.gdt_asic_type     = GDT_GFX8_0_4;
                    asic_id_info.default_device_id = 0x699F;
                    break;

                case kAsicIdVegaM:
                    asic_id_info.asic_type         = kAsicGfx8;
                    asic_id_info.gdt_asic_type     = GDT_VEGAM1;
                    asic_id_info.default_device_id = 0x694C;
                    break;

                case kAsicIdCarrizo:
                    asic_id_info.asic_type         = kAsicGfx8;
                    asic_id_info.gdt_asic_type     = GDT_CARRIZO;
                    asic_id_info.default_device_id = 0x9874;
                    asic_id_info.is_apu            = true;
                    break;

                case kAsicIdStoney:
                    asic_id_info.asic_type         = kAsicGfx8;
                    asic_id_info.gdt_asic_type     = GDT_STONEY;
                    asic_id_info.default_device_id = 0x98E4;
                    asic_id_info.is_apu            = true;
                    break;

                case kAsicIdGfx900:
                    asic_id_info.asic_type         = kAsicGfx9;
                    asic_id_info.gdt_asic_type     = GDT_GFX9_0_0;
                    asic_id_info.default_device_id = 0x687F;
                    break;

                case kAsicIdGfx902:
                    asic_id_info.asic_type         = kAsicGfx9;
                    asic_id_info.gdt_asic_type     = GDT_GFX9_0_2;
                    asic_id_info.default_device_id = 0x15DD;
                    asic_id_info.is_apu            = true;
                    break;

                case kAsicIdPlaceholder:
                    asic_id_info.asic_type = kAsicGfx9;
                    asic_id_info.is_apu    = true;
                    break;

                case kAsicIdPlaceholder1:
                    asic_id_info.asic_type = kAsicGfx9;
                    break;

                case kAsicIdGfx906:
                    asic_id_info.asic_type         = kAsicGfx9;
                    asic_id_info.gdt_asic_type     = GDT_GFX9_0_6;
                    asic_id_info.default_device_id = 0x66AF;
                    break;

                case kAsicIdGfx90C:
                    asic_id_info.asic_type = kAsicGfx9;
                    asic_id_info.gdt_asic_type = GDT_GFX9_0_C;
                    asic_id_info.default_device_id = 0x1636;
                    asic_id_info.is_apu    = true;
                    break;

                case kAsicIdPlaceholder3:
                    asic_id_info.asic_type = kAsicGfx9;
                    asic_id_info.is_apu    = true;
                    break;

                case kAsicIdGfx1010:
                case kAsicIdGfx1010Lite:
                    asic_id_info.asic_type         = kAsicGfx10;
                    asic_id_info.gdt_asic_type     = GDT_GFX10_1_0;
                    asic_id_info.default_device_id = 0x731F;
                    break;

                case kAsicIdGfx1011:
                case kAsicIdGfx1011Lite:
                    asic_id_info.asic_type = kAsicGfx10;
                    asic_id_info.gdt_asic_type = GDT_GFX10_1_1;
                    asic_id_info.default_device_id = 0x7360;
                    break;

                case kAsicIdGfx1012:
                    asic_id_info.asic_type         = kAsicGfx10;
                    asic_id_info.gdt_asic_type     = GDT_GFX10_1_2;
                    asic_id_info.default_device_id = 0x7340;
                    break;

                case kAsicIdGfx1030:
                case kAsicIdGfx1030Lite:
                    asic_id_info.asic_type         = kAsicGfx103;
                    asic_id_info.gdt_asic_type     = GDT_GFX10_3_0;
                    asic_id_info.default_device_id = 0x73BF;
                    break;

                case kAsicIdGfx1031:
                    asic_id_info.asic_type = kAsicGfx103;
                    asic_id_info.gdt_asic_type = GDT_GFX10_3_1;
                    asic_id_info.default_device_id = 0x73DF;
                    break;

                case kAsicIdGfx1032:
                    asic_id_info.asic_type = kAsicGfx103;
                    asic_id_info.gdt_asic_type = GDT_GFX10_3_2;
                    asic_id_info.default_device_id = 0x73FF;
                    break;

                case kAsicIdGfx1034:
                    asic_id_info.asic_type = kAsicGfx103;
                    asic_id_info.gdt_asic_type = GDT_GFX10_3_4;
                    asic_id_info.default_device_id = 0x743F;
                    break;

                case kAsicIdPlaceholder6:
                case kAsicIdPlaceholder9:
                case kAsicIdPlaceholder10:
                case kAsicIdPlaceholder11:
                    asic_id_info.asic_type     = kAsicGfx103;
                    asic_id_info.gdt_asic_type = GDT_GFX10_3_0;
                    break;

                default:
                    continue;
                }

                asic_id_info_map_.insert(std::pair<AsicIdEnum, AsicIdInfo>(static_cast<AsicIdEnum>(asic_id_iter), asic_id_info));
            }

            is_asic_info_initialized_ = true;
        }
    }

    AsicType AsicInfoManager::GetAsicTypeFromAsicId(AsicId asic_id)
    {
        static const char* kAsicTypeStr[] = {"Gfx6", "Gfx7", "Gfx8", "Gfx9", "Gfx10", "Gfx103", "Unknown"};
        AsicType           ret_val        = kAsicUnknown;

        static_assert(sizeof(kAsicTypeStr) / sizeof(char*) == (kAsicUnknown + 1), "AsicTypeStr does not have enough entries.");

        if (!is_asic_info_initialized_)
        {
            InitializeAsicInfo();
        }

        auto asic_type_iter = asic_id_info_map_.find(asic_id);

        if (asic_type_iter != asic_id_info_map_.end())
        {
            ret_val = asic_type_iter->second.asic_type;

            std::stringstream ss;
            if (asic_type_iter->second.is_apu)
            {
                ss << "Recognized an APU with " << kAsicTypeStr[ret_val] << " graphics.";
            }
            else
            {
                ss << "Recognized a " << kAsicTypeStr[ret_val] << " card.";
            }

            GPA_LOG_MESSAGE(ss.str().c_str());
        }
        else
        {
            std::stringstream error_message;
            error_message << "Unrecognized asic type: " << asic_id << ".";
            GPA_LOG_ERROR(error_message.str().c_str());
            assert(0);  // Unknown ASIC Type, need to update enums list from UGL driver.
            ret_val = kAsicUnknown;
        }

        return ret_val;
    }

    bool AsicInfoManager::GetFallbackAsicInfo(const AsicId& asic_id, GDT_HW_ASIC_TYPE& gdt_hw_asic_type, uint32_t& default_device_id)
    {
        if (!is_asic_info_initialized_)
        {
            InitializeAsicInfo();
        }

        auto asic_type_iter = asic_id_info_map_.find(asic_id);

        if (asic_type_iter != asic_id_info_map_.end())
        {
            gdt_hw_asic_type  = asic_type_iter->second.gdt_asic_type;
            default_device_id = asic_type_iter->second.default_device_id;
            return true;
        }

        std::stringstream error_message;
        error_message << "Unrecognized asic type: " << asic_id << ".";
        GPA_LOG_ERROR(error_message.str().c_str());
        assert(0);  // Unknown ASIC Type, need to update enums list from UGL driver.
        return false;
    }

    AsicInfoManager::AsicInfoManager()
        : is_asic_info_initialized_(false)
    {
    }

    AsicInfoManager::~AsicInfoManager()
    {
        asic_id_info_map_.clear();
        is_asic_info_initialized_ = false;
    }

    bool AsicInfoManager::GetAsicInfoFromDriver(AsicInfo& asic_info)
    {
        if (nullptr == ogl_get_perf_monitor_counters_amd || nullptr == ogl_get_perf_monitor_group_string_amd ||
            nullptr == ogl_get_perf_monitor_counter_info_amd || nullptr == ogl_get_perf_monitor_counter_string_amd || nullptr == ogl_gen_perf_monitors_amd ||
            nullptr == ogl_delete_perf_monitors_amd || nullptr == ogl_select_perf_monitor_counters_amd || nullptr == ogl_begin_perf_monitor_amd ||
            nullptr == ogl_end_perf_monitor_amd || nullptr == ogl_get_perf_monitor_counter_data_amd)
        {
            // No AMD_performance_monitor support, means no ASIC info.
            GPA_LOG_ERROR("One or more of the GL_AMD_performance_monitor functions were not found.");
            return false;
        }

        GLint num_counters = 0;
        bool  result       = false;

#ifndef GLES
        if (!ogl_utils::InitializeGlCoreFunctions())
        {
            return false;
        }

        const GLubyte* version_gl_string = ogl_get_string(GL_VERSION);
        std::string driver_string = (const char*)version_gl_string;
        if (driver_string.find("Mesa") != std::string::npos)
        {
            GPA_LOG_ERROR("The Mesa driver is not currently supported.");
            return false;
        }
        asic_info.driver_version         = ExtractDriverVersionNumber(version_gl_string);
#else
        asic_info.driver_version = INT_MAX;
#endif

        if (asic_info.driver_version < kGlDriverVerWithOnlyGcnSupport)
        {
            // Pre-GCN devices were removed from the driver starting with version 13452.
            // If the driver version is earlier than that we will return an error.
#ifndef GLES
            std::string driver_version_message = "GL_VERSION: '";
            driver_version_message.append((const char*)version_gl_string);
            driver_version_message.append("'.");
            GPA_LOG_ERROR(driver_version_message.c_str());
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

        GLuint* counter_list = new (std::nothrow) GLuint[num_counters];

        if (nullptr != counter_list)
        {
            // Get the list of counters in the group.
            ogl_get_perf_monitor_counters_amd(group, nullptr, nullptr, num_counters, counter_list);

            GLuint monitor     = 0;
            GLuint result_size = 0;

            // Create a monitor for all GPIN counters.
            ogl_gen_perf_monitors_amd(1, &monitor);

            // Enable all GPIN counters.
            for (int i = 0; i < num_counters; i++)
            {
                ogl_select_perf_monitor_counters_amd(monitor, GL_TRUE, group, 1, &counter_list[i]);
            }

            // Begin / end the monitor so that the data is obtained.
            ogl_begin_perf_monitor_amd(monitor);
            ogl_end_perf_monitor_amd(monitor);

            // Get the counter result size.
            ogl_get_perf_monitor_counter_data_amd(monitor, GL_PERFMON_RESULT_SIZE_AMD, sizeof(result_size), &result_size, nullptr);

            // Result should be 3 GLUint per counter.
            GLint expected_result_size = (3 * sizeof(GLuint)) * num_counters;
            assert(static_cast<GLint>(result_size) == expected_result_size);

            if (static_cast<GLint>(result_size) == expected_result_size)
            {
                GLubyte* counter_data = new (std::nothrow) GLubyte[result_size];

                if (nullptr != counter_data)
                {
                    // Get the counter results.
                    ogl_get_perf_monitor_counter_data_amd(monitor, GL_PERFMON_RESULT_AMD, result_size, reinterpret_cast<GLuint*>(counter_data), nullptr);

                    for (int i = 0; i < num_counters; i++)
                    {
                        // Index into the result array for each counter -- the result is the third GLuint out of the three.
                        unsigned int      value = (reinterpret_cast<GLuint*>(counter_data))[(i * 3) + 2];
                        std::stringstream message;

                        switch (i)
                        {
                        case kAsicTypeIndex:
                            asic_info.asic_id   = static_cast<AsicId>(value);
                            asic_info.asic_type = GetAsicTypeFromAsicId(asic_info.asic_id);
                            break;

                        case kAsicNumSimdIndex:
                            if (kGlDriverVerWithGpinCounters <= asic_info.driver_version)
                            {
                                asic_info.num_simd = value;
                            }
                            break;

                        case kAsicNumRbIndex:
                            if (kGlDriverVerWithGpinCounters <= asic_info.driver_version)
                            {
                                asic_info.num_rb = value;
                            }
                            break;

                        case kAsicNumSpiIndex:
                            if (kGlDriverVerWithGpinCounters <= asic_info.driver_version)
                            {
                                asic_info.num_spi = value;
                            }
                            break;

                        case kAsicNumSeIndex:
                            if (kGlDriverVerWithGpinCounters <= asic_info.driver_version)
                            {
                                asic_info.num_se = value;
                            }
                            break;

                        case kAsicNumSaIndex:
                            if (kGlDriverVerWithGpinCounters <= asic_info.driver_version)
                            {
                                asic_info.num_sa_per_se = value;
                            }
                            break;

                        case kAsicNumCuIndex:
                            if (kGlDriverVerWithGpinCounters <= asic_info.driver_version)
                            {
                                asic_info.num_cu = value;
                            }
                            break;

                        case kAsicDevIdIndex:
                            if (kGlDriverVerWithGpinCounters <= asic_info.driver_version)
                            {
                                asic_info.device_id = value;

                                message << "Retrieved ASIC device ID: " << std::hex << std::showbase << value << ".";
                                GPA_LOG_MESSAGE(message.str().c_str());
                            }
                            break;

                        case kAsicDevRevIndex:
                            if (kGlDriverVerWithGpinCounters <= asic_info.driver_version)
                            {
                                asic_info.device_rev = value;

                                message << "Retrieved ASIC device revision: " << std::hex << std::showbase << value << ".";
                                GPA_LOG_MESSAGE(message.str().c_str());
                            }
                            break;
                        }

                        ogl_select_perf_monitor_counters_amd(monitor, GL_FALSE, group, 1, &counter_list[i]);
                    }

                    result = true;
                    delete[] counter_data;
                }
            }

            ogl_delete_perf_monitors_amd(1, &monitor);
            delete[] counter_list;
        }

        if (result)
        {
            std::stringstream message;
            message << "ASIC ID returned from driver is: " << asic_info.asic_id << " and GL_VERSION is: " << asic_info.driver_version << ".";
            GPA_LOG_MESSAGE(message.str().c_str());

            // Given the age of Tahiti ASICs, this particular value is unlikely to be correct.
            if (asic_info.asic_id == 0)
            {
                GPA_LOG_MESSAGE(
                    "WARNING: Received an ASIC ID of '0' from the OpenGL implementation; if you do not have an AMD Radeon HD 7000 series GPU then this "
                    "indicates a driver error.");
            }
        }

        return result;
    }

}  // namespace ogl_utils
