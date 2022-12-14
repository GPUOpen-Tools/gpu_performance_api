//==============================================================================
// Copyright (c) 2006-2022 Advanced Micro Devices, Inc. All rights reserved.
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
        if (ogl_get_perf_monitor_groups_amd != nullptr)
        {
            ogl_get_perf_monitor_groups_amd(&num_groups, 0, nullptr);
        }
        else if (ogl_get_perf_monitor_groups_2_amd != nullptr)
        {
            ogl_get_perf_monitor_groups_2_amd(&num_groups, 0, nullptr, nullptr);
        }
        else
        {
            assert(ogl_get_perf_monitor_groups_amd != nullptr || ogl_get_perf_monitor_groups_2_amd != nullptr);
            return -1;
        }

        if (num_groups > 0)
        {
            GLuint* performance_counter_groups          = new (std::nothrow) GLuint[num_groups];
            GLuint* performance_counter_group_instances = new (std::nothrow) GLuint[num_groups];

            if (nullptr != performance_counter_groups && nullptr != performance_counter_group_instances)
            {
                // Get the group Ids.
                if (ogl_get_perf_monitor_groups_amd != nullptr)
                {
                    ogl_get_perf_monitor_groups_amd(nullptr, num_groups, performance_counter_groups);
                }
                else if (ogl_get_perf_monitor_groups_2_amd != nullptr)
                {
                    ogl_get_perf_monitor_groups_2_amd(nullptr, num_groups, performance_counter_groups, performance_counter_group_instances);
                }
                else
                {
                    assert(ogl_get_perf_monitor_groups_amd != nullptr || ogl_get_perf_monitor_groups_2_amd != nullptr);
                    return -1;
                }

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

    AsicIdInfo GetAsicInfoForAsicRevision(AsicRevision asic_revision)
    {
        static_assert(kAsicRevisionLast == 0x30, "AsicRevision has changed, add necessary entry for asic info.");

        AsicIdInfo asic_id_info = {};

        // Default to not being an APU. Gets set to true as needed below.
        asic_id_info.is_apu = false;

        switch (asic_revision)
        {
        case kTahiti:
            asic_id_info.asic_generation   = kAsicGfx6;
            asic_id_info.gdt_asic_type     = GDT_TAHITI_PRO;
            asic_id_info.default_device_id = 0x679A;
            break;

        case kPitcairn:
            asic_id_info.asic_generation   = kAsicGfx6;
            asic_id_info.gdt_asic_type     = GDT_PITCAIRN_PRO;
            asic_id_info.default_device_id = 0x6819;
            break;

        case kCapeverde:
            asic_id_info.asic_generation   = kAsicGfx6;
            asic_id_info.gdt_asic_type     = GDT_CAPEVERDE_PRO;
            asic_id_info.default_device_id = 0x6822;
            break;

        case kOland:
            asic_id_info.asic_generation   = kAsicGfx6;
            asic_id_info.gdt_asic_type     = GDT_OLAND;
            asic_id_info.default_device_id = 0x6610;
            break;

        case kHainan:
            asic_id_info.asic_generation   = kAsicGfx6;
            asic_id_info.gdt_asic_type     = GDT_HAINAN;
            asic_id_info.default_device_id = 0x6660;
            break;

        case kBonaire:
            asic_id_info.asic_generation   = kAsicGfx7;
            asic_id_info.gdt_asic_type     = GDT_BONAIRE;
            asic_id_info.default_device_id = 0x665C;
            break;

        case kHawaii:
        case kHawaiiPro:
            asic_id_info.asic_generation   = kAsicGfx7;
            asic_id_info.gdt_asic_type     = GDT_HAWAII;
            asic_id_info.default_device_id = 0x67B0;
            break;

        case kKalindi:
            asic_id_info.asic_generation   = kAsicGfx7;
            asic_id_info.gdt_asic_type     = GDT_KALINDI;
            asic_id_info.default_device_id = 0x9830;
            asic_id_info.is_apu            = true;
            break;

        case kGodavari:
            asic_id_info.asic_generation   = kAsicGfx7;
            asic_id_info.gdt_asic_type     = GDT_KALINDI;
            asic_id_info.default_device_id = 0x9855;
            asic_id_info.is_apu            = true;
            break;

        case kSpectre:
            asic_id_info.asic_generation   = kAsicGfx7;
            asic_id_info.gdt_asic_type     = GDT_SPECTRE;
            asic_id_info.default_device_id = 0x130C;
            asic_id_info.is_apu            = true;
            break;

        case kSpooky:
            asic_id_info.asic_generation   = kAsicGfx7;
            asic_id_info.gdt_asic_type     = GDT_SPOOKY;
            asic_id_info.default_device_id = 0x130B;
            asic_id_info.is_apu            = true;
            break;

        case kIceland:
            asic_id_info.asic_generation   = kAsicGfx8;
            asic_id_info.gdt_asic_type     = GDT_ICELAND;
            asic_id_info.default_device_id = 0x6900;
            break;

        case kTonga:
            asic_id_info.asic_generation   = kAsicGfx8;
            asic_id_info.gdt_asic_type     = GDT_TONGA;
            asic_id_info.default_device_id = 0x6920;
            break;

        case kFiji:
            asic_id_info.asic_generation   = kAsicGfx8;
            asic_id_info.gdt_asic_type     = GDT_FIJI;
            asic_id_info.default_device_id = 0x7300;
            break;

        case kPolaris10:
            asic_id_info.asic_generation   = kAsicGfx8;
            asic_id_info.gdt_asic_type     = GDT_ELLESMERE;
            asic_id_info.default_device_id = 0x67DF;
            break;

        case kPolaris11:
            asic_id_info.asic_generation   = kAsicGfx8;
            asic_id_info.gdt_asic_type     = GDT_BAFFIN;
            asic_id_info.default_device_id = 0x67FF;
            break;

        case kPolaris12:
            asic_id_info.asic_generation   = kAsicGfx8;
            asic_id_info.gdt_asic_type     = GDT_GFX8_0_4;
            asic_id_info.default_device_id = 0x699F;
            break;

        case kPolaris22:
            asic_id_info.asic_generation   = kAsicGfx8;
            asic_id_info.gdt_asic_type     = GDT_VEGAM1;
            asic_id_info.default_device_id = 0x694C;
            break;

        case kCarrizo:
            asic_id_info.asic_generation   = kAsicGfx8;
            asic_id_info.gdt_asic_type     = GDT_CARRIZO;
            asic_id_info.default_device_id = 0x9874;
            asic_id_info.is_apu            = true;
            break;

        case kStoney:
            asic_id_info.asic_generation   = kAsicGfx8;
            asic_id_info.gdt_asic_type     = GDT_STONEY;
            asic_id_info.default_device_id = 0x98E4;
            asic_id_info.is_apu            = true;
            break;

        case kVega10:
            asic_id_info.asic_generation   = kAsicGfx9;
            asic_id_info.gdt_asic_type     = GDT_GFX9_0_0;
            asic_id_info.default_device_id = 0x687F;
            break;

        case kRaven:
            asic_id_info.asic_generation   = kAsicGfx9;
            asic_id_info.gdt_asic_type     = GDT_GFX9_0_2;
            asic_id_info.default_device_id = 0x15DD;
            asic_id_info.is_apu            = true;
            break;

        case kRaven2:
            asic_id_info.asic_generation   = kAsicGfx9;
            asic_id_info.gdt_asic_type     = GDT_ASIC_TYPE_NONE;
            asic_id_info.default_device_id = 0x0000;
            asic_id_info.is_apu            = true;
            break;

        case kVega12:
            asic_id_info.asic_generation   = kAsicGfx9;
            asic_id_info.gdt_asic_type     = GDT_GFX9_0_4;
            asic_id_info.default_device_id = 0x69A0;
            break;

        case kVega20:
            asic_id_info.asic_generation   = kAsicGfx9;
            asic_id_info.gdt_asic_type     = GDT_GFX9_0_6;
            asic_id_info.default_device_id = 0x66AF;
            break;

        case kRenoir:
            asic_id_info.asic_generation   = kAsicGfx9;
            asic_id_info.gdt_asic_type     = GDT_GFX9_0_C;
            asic_id_info.default_device_id = 0x1636;
            asic_id_info.is_apu            = true;
            break;

        case kNavi10:
            asic_id_info.asic_generation   = kAsicGfx10;
            asic_id_info.gdt_asic_type     = GDT_GFX10_1_0;
            asic_id_info.default_device_id = 0x731F;
            break;

        case kNavi12:
        case kNavi12Lite:
            asic_id_info.asic_generation   = kAsicGfx10;
            asic_id_info.gdt_asic_type     = GDT_GFX10_1_1;
            asic_id_info.default_device_id = 0x7360;
            break;

        case kNavi14:
        case kNavi14Lite:
            asic_id_info.asic_generation   = kAsicGfx10;
            asic_id_info.gdt_asic_type     = GDT_GFX10_1_2;
            asic_id_info.default_device_id = 0x7340;
            break;

        case kNavi21:
        case kNavi21Lite:
            asic_id_info.asic_generation   = kAsicGfx103;
            asic_id_info.gdt_asic_type     = GDT_GFX10_3_0;
            asic_id_info.default_device_id = 0x73BF;
            break;

        case kPlaceholder6:
            asic_id_info.asic_generation   = kAsicGfx103;
            asic_id_info.gdt_asic_type     = GDT_GFX10_3_0;
            asic_id_info.default_device_id = 0x0000;
            break;

        case kNavi22:
            asic_id_info.asic_generation   = kAsicGfx103;
            asic_id_info.gdt_asic_type     = GDT_GFX10_3_1;
            asic_id_info.default_device_id = 0x73DF;
            break;

        case kNavi23:
            asic_id_info.asic_generation   = kAsicGfx103;
            asic_id_info.gdt_asic_type     = GDT_GFX10_3_2;
            asic_id_info.default_device_id = 0x73FF;
            break;

        case kNavi24:
            asic_id_info.asic_generation   = kAsicGfx103;
            asic_id_info.gdt_asic_type     = GDT_GFX10_3_4;
            asic_id_info.default_device_id = 0x743F;
            break;

        case kGfx1035:
            asic_id_info.asic_generation   = kAsicGfx103;
            asic_id_info.gdt_asic_type     = GDT_GFX10_3_5;
            asic_id_info.default_device_id = 0x164D;
            break;

        case kGfx1100:
            asic_id_info.asic_generation   = kAsicGfx11;
            asic_id_info.gdt_asic_type     = GDT_GFX11_0_0;
            asic_id_info.default_device_id = 0x73A8;
            break;

        default:
            assert(!"Unhandled AsicRevision type");
            asic_id_info.asic_generation   = kAsicUnknown;
            asic_id_info.gdt_asic_type     = GDT_ASIC_TYPE_NONE;
            asic_id_info.default_device_id = 0x0000;
            break;
        }

        return asic_id_info;
    }

    AsicRevision GetAsicRevisionFromAsicId(AsicId asic_id)
    {
        AsicRevision revision = kUnknown;

        // This static assert will help to find error when we update the AsicIdEnum for new hardware.
        // Upon failure, we need to add suitable entry for public device and update the static assert for update count.
        static_assert(kAsicIdLast == 43, "AsicIdEnum has changed, add suitable entry for asic info.");

        switch (asic_id)
        {
        case kAsicIdTahitiP:
            revision = kTahiti;
            break;

        case kAsicIdPitcairnPm:
            revision = kPitcairn;
            break;

        case kAsicIdCapeverdeM:
            revision = kCapeverde;
            break;

        case kAsicIdOlandM:
            revision = kOland;
            break;

        case kAsicIdHainanM:
            revision = kHainan;
            break;

        case kAsicIdBonaireM:
            revision = kBonaire;
            break;

        case kAsicIdHawaiiP:
            revision = kHawaiiPro;
            break;

        case kAsicIdKalindi:
            revision = kKalindi;
            break;

        case kAsicIdGodavari:
            revision = kGodavari;
            break;

        case kAsicIdSpectre:
            revision = kSpectre;
            break;

        case kAsicIdSpooky:
            revision = kSpooky;
            break;

        case kAsicIdIcelandM:
            revision = kIceland;
            break;

        case kAsicIdTongaP:
            revision = kTongaPro;
            break;

        case kAsicIdFijiP:
            revision = kFiji;
            break;

        case kAsicIdEllesmere:
            revision = kPolaris10;
            break;

        case kAsicIdBaffin:
            revision = kPolaris11;
            break;

        case kAsicIdLexa:
            revision = kPolaris12;
            break;

        case kAsicIdVegaM:
            revision = kPolaris22;
            break;

        case kAsicIdCarrizo:
            revision = kCarrizo;
            break;

        case kAsicIdStoney:
            revision = kStoney;
            break;

        case kAsicIdGfx900:
            revision = kVega10;
            break;

        case kAsicIdGfx902:
            revision = kRaven;
            break;

        case kAsicIdPlaceholder:
            revision = kUnknown;
            break;

        case kAsicIdGfx904:
            revision = kVega12;
            break;

        case kAsicIdGfx906:
            revision = kVega20;
            break;

        case kAsicIdGfx90C:
            revision = kRenoir;
            break;

        case kAsicIdPlaceholder3:
            revision = kUnknown;
            break;

        case kAsicIdGfx1010:
        case kAsicIdGfx1010Lite:
            revision = kNavi10;
            break;

        case kAsicIdGfx1011:
            revision = kNavi12;
            break;

        case kAsicIdGfx1011Lite:
            revision = kNavi12Lite;
            break;

        case kAsicIdGfx1012:
            revision = kNavi14;
            break;

        case kAsicIdGfx1030:
            revision = kNavi21;
            break;

        case kAsicIdGfx1030Lite:
            revision = kNavi21Lite;
            break;

        case kAsicIdPlaceholder6:
            revision = kPlaceholder6;
            break;

        case kAsicIdGfx1031:
            revision = kNavi22;
            break;

        case kAsicIdGfx1032:
            revision = kNavi23;
            break;

        case kAsicIdGfx1034:
            revision = kNavi24;
            break;

        case kAsicIdGfx1035:
            revision = kGfx1035;
            break;

        case kAsicIdPlaceholder10:
        case kAsicIdPlaceholder11:
            revision = kUnknown;
            break;
        default:
            revision = kUnknown;

            std::stringstream error_message;
            error_message << "Unrecognized asic Id: " << asic_id << ".";
            GPA_LOG_ERROR(error_message.str().c_str());
            assert(!"Unrecognized AsicId");
            break;
        }

        return revision;
    }

    AsicGeneration GetAsicTypeFromAsicRevision(AsicRevision asic_revision)
    {
        AsicGeneration ret_val = kAsicUnknown;

        AsicIdInfo info = GetAsicInfoForAsicRevision(asic_revision);

        if (info.asic_generation != kAsicUnknown)
        {
            ret_val = info.asic_generation;

            std::stringstream ss;
            if (info.is_apu)
            {
                ss << "Recognized an APU with " << kAsicGenerationStrings[ret_val] << " graphics.";
            }
            else
            {
                ss << "Recognized a " << kAsicGenerationStrings[ret_val] << " card.";
            }

            GPA_LOG_MESSAGE(ss.str().c_str());
        }
        else
        {
            assert(!"Unknown AsicRevision, may need to update enum list from PAL.");
            std::stringstream error_message;
            error_message << "Unrecognized asic revision: " << asic_revision << ".";
            GPA_LOG_ERROR(error_message.str().c_str());
            ret_val = kAsicUnknown;
        }

        return ret_val;
    }

    bool GetFallbackAsicInfo(const AsicRevision& asic_revision, GDT_HW_ASIC_TYPE& gdt_hw_asic_type, uint32_t& default_device_id)
    {
        AsicIdInfo info = GetAsicInfoForAsicRevision(asic_revision);

        if (info.asic_generation != kAsicUnknown)
        {
            gdt_hw_asic_type  = info.gdt_asic_type;
            default_device_id = info.default_device_id;
            return true;
        }

        return false;
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

        bool found_ugl_entrypoints  = (nullptr != ogl_get_perf_monitor_groups_amd && nullptr != ogl_select_perf_monitor_counters_amd);
        bool found_oglp_entrypoints = (nullptr != ogl_get_perf_monitor_groups_2_amd && nullptr != ogl_select_perf_monitor_counters_2_amd);

        if (!found_ugl_entrypoints && !found_oglp_entrypoints)
        {
            // One of the other AMD_performance_monitor extension entrypoints was missing.
            GPA_LOG_ERROR("One or more of the other GL_AMD_performance_monitor functions were not found.");
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
            GPA_LOG_ERROR("The Mesa driver is not currently supported.");
            return false;
        }

        asic_info.driver_version = ogl_utils::GetDriverVersion();
#else
        asic_info.driver_version = INT_MAX;
#endif

        if (asic_info.driver_version < kGlDriverVerWithOnlyGcnSupport)
        {
            // Pre-GCN devices were removed from the driver starting with version 13452.
            // If the driver version is earlier than that we will return an error.
#ifndef GLES
            const GLubyte* gl_version_string      = ogl_get_string(GL_VERSION);
            std::string    driver_version_message = "GL_VERSION: '";
            driver_version_message.append((const char*)gl_version_string);
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
        GLenum error_getting_num_gpin_counters = ogl_get_error();
        if (error_getting_num_gpin_counters != GL_NO_ERROR)
        {
            GPA_LOG_ERROR("Error getting the number of GPIN counters.");
            return false;
        }

        AsicId ugl_asic_id = kAsicIdUnknown;

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
                    if (found_ugl_entrypoints)
                    {
                        ogl_select_perf_monitor_counters_amd(monitor, GL_TRUE, group, num_counters, &counter_list[0]);
                    }
                    else if (found_oglp_entrypoints)
                    {
                        ogl_select_perf_monitor_counters_2_amd(monitor, GL_TRUE, group, 0, num_counters, &counter_list[0]);
                    }

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

                        if (found_ugl_entrypoints)
                        {
                            // Result is only 3 GLuint per counter on ugl.
                            expected_result_size = (3 * sizeof(GLuint)) * num_counters;
                        }

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
                                    unsigned int value = 0;
                                    if (ogl_utils::IsUglDriver() || ogl_utils::IsMesaDriver())
                                    {
                                        value = (reinterpret_cast<GLuint*>(counter_data))[(i * 3) + 2];
                                    }
                                    else if (ogl_utils::IsOglpDriver())
                                    {
                                        value = (reinterpret_cast<GLuint*>(counter_data))[(i * 4) + 3];
                                    }

                                    std::stringstream message;

                                    switch (i)
                                    {
                                    case kAsicRevisionIndex:
                                        if (found_ugl_entrypoints)
                                        {
                                            ugl_asic_id             = static_cast<AsicId>(value);
                                            asic_info.asic_revision = GetAsicRevisionFromAsicId(ugl_asic_id);
                                        }
                                        else
                                        {
                                            asic_info.asic_revision = static_cast<AsicRevision>(value);
                                        }
                                        asic_info.asic_generation = GetAsicTypeFromAsicRevision(asic_info.asic_revision);
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

                                    if (ogl_utils::IsUglDriver() || ogl_utils::IsMesaDriver())
                                    {
                                        ogl_select_perf_monitor_counters_amd(monitor, GL_FALSE, group, 1, &counter_list[i]);
                                    }
                                    else if (ogl_utils::IsOglpDriver())
                                    {
                                        ogl_select_perf_monitor_counters_2_amd(monitor, GL_FALSE, group, 0, 1, &counter_list[i]);
                                    }
                                }

                                result = true;
                                delete[] counter_data;
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
            if (found_ugl_entrypoints)
            {
                std::stringstream message;
                message << "ASIC ID returned from driver is: " << ugl_asic_id << " and GL_VERSION is: " << asic_info.driver_version << ".";
                GPA_LOG_MESSAGE(message.str().c_str());
            }
            else if (found_oglp_entrypoints)
            {
                std::stringstream message;
                message << "ASIC revision returned from driver is: " << asic_info.asic_revision << " (decimal) and GL_VERSION is: " << asic_info.driver_version
                        << ".";
                GPA_LOG_MESSAGE(message.str().c_str());

                if (asic_info.asic_revision == kUnknown)
                {
                    GPA_LOG_MESSAGE("WARNING: Received an 'Unknown' ASIC Revision from the OpenGL implementation.");
                }
            }
        }

        return result;
    }

}  // namespace ogl_utils
