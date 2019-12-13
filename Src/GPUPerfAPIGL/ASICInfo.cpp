//==============================================================================
// Copyright (c) 2006-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Utility routines for retrieving ASIC information
//==============================================================================

#ifdef _WIN32
#include <windows.h>
#endif

#include <assert.h>
#include <string>
#include <sstream>

#ifdef _LINUX
#include <string.h>
#include <stdlib.h>
#endif

#include <ADLUtil.h>

#include "Logging.h"
#include "GLEntryPoints.h"
#include "ASICInfo.h"
#include "DeviceInfo.h"

#define ASIC_GROUP "GPIN"      ///< Driver-defined ASIC info group
#define ASIC_TYPE_INDEX     0  ///< Driver-defined counter index for asic type
#define ASIC_NUM_SIMD_INDEX 1  ///< Driver-defined counter index for number of SIMDs
#define ASIC_NUM_RB_INDEX   2  ///< Driver-defined counter index for number of RBs
#define ASIC_NUM_SPI_INDEX  3  ///< Driver-defined counter index for number of SPIs
#define ASIC_NUM_SE_INDEX   4  ///< Driver-defined counter index for number of SEs
#define ASIC_NUM_SA_INDEX   5  ///< Driver-defined counter index for number of SAs
#define ASIC_NUM_CU_INDEX   6  ///< Driver-defined counter index for number of CUs
#define ASIC_DEV_ID_INDEX   7  ///< Driver-defined counter index for device id
#define ASIC_DEV_REV_INDEX  8  ///< Driver-defined counter index for revision id

namespace oglUtils
{
    /// Get the group ID for ASICInfo group
    /// \return -1 if group not found, group ID otherwise
    GLint GetASICInfoGroupID()
    {
        GLint nNumGroups = 0;

        // Get the number of performance counter groups
        _oglGetPerfMonitorGroupsAMD(&nNumGroups, 0, nullptr);

        if (nNumGroups > 0)
        {
            GLuint* pPerfGroups = new (std::nothrow) GLuint[nNumGroups];

            if (nullptr != pPerfGroups)
            {
                // Get the group Ids
                _oglGetPerfMonitorGroupsAMD(nullptr, nNumGroups, pPerfGroups);

                for (int i = 0; i < nNumGroups; i++)
                {
                    char groupStr[256];

                    // Get the group name
                    _oglGetPerfMonitorGroupStringAMD(pPerfGroups[i], 255, nullptr, groupStr);

                    if (!strcmp(groupStr, ASIC_GROUP))
                    {
                        GLint nGroupID = pPerfGroups[i];
                        delete[] pPerfGroups;
                        return nGroupID;
                    }
                }

                delete[] pPerfGroups;
            }
        }

        return -1;
    }

#ifndef GLES

    /// Parses a version number like this: "4.2.12325 Compatibility Profile Context 13.100.0.0"
    /// to extract the "12325" portion.
    /// \param pVersion the version string to extract the number from
    /// \return 0 on failure, the build version number on success
    int ExtractDriverVersionNumber(const GLubyte* pVersion)
    {
        //initialize to INT_MAX to simulate most recent driver
        int version = INT_MAX;

        if (nullptr != pVersion)
        {
            const char* pcszVer = reinterpret_cast<const char*>(pVersion);

            std::string strVer(pcszVer);

            // the build number ends at the first space
            size_t endBuild = strVer.find_first_of(' ');

            // truncate the input at the first space
            strVer = strVer.substr(0, endBuild);

            // the build number starts after the last decimal point
            size_t startBuild = strVer.find_last_of('.') + 1;

            // parse the version number
            std::istringstream iss(strVer.substr(startBuild, endBuild - startBuild));
            iss >> version;

            // couldn't extract version -- return INT_MAX to simulate most recent driver
            if (iss.fail())
            {
                version = INT_MAX;
            }
        }

        return version;
    }

#endif

    void AsicInfoManager::InitializeAsicInfo()
    {
        /*
         * This static assert will help to find error when we update the AsicIdEnum for new hardware.
         * Upon failure, we need to add suitable entry for public device and update the static assert for update count.
         */
        static_assert(AsicId_LAST == 36, "AsicIdEnum has changed, add suitable entry for asic info.");

        if (!is_asic_info_initialized_)
        {
            for (uint32_t asic_id_iter = AsicId_First; asic_id_iter != AsicId_LAST; ++asic_id_iter)
            {
                AsicIdInfo asic_id_info = {};
                asic_id_info.is_apu     = false;

                switch (asic_id_iter)
                {
                case ASIC_ID_TAHITI_P:
                    asic_id_info.asic_type = ASIC_Gfx6;
                    asic_id_info.gdt_asic_type = GDT_TAHITI_PRO;
                    asic_id_info.default_device_id = 0x679A;
                    break;

                case ASIC_ID_PITCAIRN_PM:
                    asic_id_info.asic_type         = ASIC_Gfx6;
                    asic_id_info.gdt_asic_type     = GDT_PITCAIRN_PRO;
                    asic_id_info.default_device_id = 0x6819;
                    break;

                case ASIC_ID_CAPEVERDE_M:
                    asic_id_info.asic_type         = ASIC_Gfx6;
                    asic_id_info.gdt_asic_type     = GDT_CAPEVERDE_PRO;
                    asic_id_info.default_device_id = 0x6822;
                    break;

                case ASIC_ID_OLAND_M:
                    asic_id_info.asic_type         = ASIC_Gfx6;
                    asic_id_info.gdt_asic_type     = GDT_OLAND;
                    asic_id_info.default_device_id = 0x6610;
                    break;

                case ASIC_ID_HAINAN_M:
                    asic_id_info.asic_type         = ASIC_Gfx6;
                    asic_id_info.gdt_asic_type     = GDT_HAINAN;
                    asic_id_info.default_device_id = 0x6660;
                    break;

                case ASIC_ID_BONAIRE_M:
                    asic_id_info.asic_type         = ASIC_Gfx7;
                    asic_id_info.gdt_asic_type     = GDT_BONAIRE;
                    asic_id_info.default_device_id = 0x665C;
                    break;

                case ASIC_ID_HAWAII_P:
                    asic_id_info.asic_type         = ASIC_Gfx7;
                    asic_id_info.gdt_asic_type     = GDT_HAWAII;
                    asic_id_info.default_device_id = 0x67B0;
                    break;

                case ASIC_ID_KALINDI:
                    asic_id_info.asic_type         = ASIC_Gfx7;
                    asic_id_info.gdt_asic_type     = GDT_KALINDI;
                    asic_id_info.default_device_id = 0x9830;
                    asic_id_info.is_apu            = true;
                    break;

                case ASIC_ID_GODAVARI:
                    asic_id_info.asic_type         = ASIC_Gfx7;
                    asic_id_info.gdt_asic_type     = GDT_KALINDI;
                    asic_id_info.default_device_id = 0x9855;
                    asic_id_info.is_apu            = true;
                    break;

                case ASIC_ID_SPECTRE:
                    asic_id_info.asic_type         = ASIC_Gfx7;
                    asic_id_info.gdt_asic_type     = GDT_SPECTRE;
                    asic_id_info.default_device_id = 0x130C;
                    asic_id_info.is_apu            = true;
                    break;

                case ASIC_ID_SPOOKY:
                    asic_id_info.asic_type         = ASIC_Gfx7;
                    asic_id_info.gdt_asic_type     = GDT_SPOOKY;
                    asic_id_info.default_device_id = 0x130B;
                    asic_id_info.is_apu            = true;
                    break;

                case ASIC_ID_ICELAND_M:
                    asic_id_info.asic_type         = ASIC_Gfx8;
                    asic_id_info.gdt_asic_type     = GDT_ICELAND;
                    asic_id_info.default_device_id = 0x6900;
                    break;

                case ASIC_ID_TONGA_P:
                    asic_id_info.asic_type         = ASIC_Gfx8;
                    asic_id_info.gdt_asic_type     = GDT_TONGA;
                    asic_id_info.default_device_id = 0x6920;
                    break;

                case ASIC_ID_FIJI_P:
                    asic_id_info.asic_type         = ASIC_Gfx8;
                    asic_id_info.gdt_asic_type     = GDT_FIJI;
                    asic_id_info.default_device_id = 0x7300;
                    break;

                case ASIC_ID_ELLESMERE:
                    asic_id_info.asic_type         = ASIC_Gfx8;
                    asic_id_info.gdt_asic_type     = GDT_ELLESMERE;
                    asic_id_info.default_device_id = 0x67DF;
                    break;

                case ASIC_ID_BAFFIN:
                    asic_id_info.asic_type         = ASIC_Gfx8;
                    asic_id_info.gdt_asic_type     = GDT_BAFFIN;
                    asic_id_info.default_device_id = 0x67FF;
                    break;

                 case ASIC_ID_LEXA:
                    asic_id_info.asic_type         = ASIC_Gfx8;
                    asic_id_info.gdt_asic_type     = GDT_GFX8_0_4;
                    asic_id_info.default_device_id = 0x699F;
                    break;

                case ASIC_ID_VEGAM:
                     asic_id_info.asic_type         = ASIC_Gfx8;
                     asic_id_info.gdt_asic_type     = GDT_VEGAM1;
                     asic_id_info.default_device_id = 0x694C;
                     break;

                case ASIC_ID_CARRIZO:
                    asic_id_info.asic_type         = ASIC_Gfx8;
                    asic_id_info.gdt_asic_type     = GDT_CARRIZO;
                    asic_id_info.default_device_id = 0x9874;
                    asic_id_info.is_apu            = true;
                    break;

                case ASIC_ID_STONEY:
                    asic_id_info.asic_type         = ASIC_Gfx8;
                    asic_id_info.gdt_asic_type     = GDT_STONEY;
                    asic_id_info.default_device_id = 0x98E4;
                    asic_id_info.is_apu            = true;
                    break;

                case ASIC_ID_GFX900:
                    asic_id_info.asic_type         = ASIC_Gfx9;
                    asic_id_info.gdt_asic_type     = GDT_GFX9_0_0;
                    asic_id_info.default_device_id = 0x687F;
                    break;

                case ASIC_ID_GFX902:
                    asic_id_info.asic_type         = ASIC_Gfx9;
                    asic_id_info.gdt_asic_type     = GDT_GFX9_0_2;
                    asic_id_info.default_device_id = 0x15DD;
                    asic_id_info.is_apu            = true;
                    break;

                case ASIC_ID_PLACEHOLDER:
                    asic_id_info.asic_type = ASIC_Gfx9;
                    asic_id_info.is_apu    = true;
                    break;

                case ASIC_ID_PLACEHOLDER1:
                    asic_id_info.asic_type = ASIC_Gfx9;
                    break;

                case ASIC_ID_GFX906:
                    asic_id_info.asic_type         = ASIC_Gfx9;
                    asic_id_info.gdt_asic_type     = GDT_GFX9_0_6;
                    asic_id_info.default_device_id = 0x66A3;
                    break;

                case ASIC_ID_PLACEHOLDER2:
                    asic_id_info.asic_type = ASIC_Gfx9;
                    asic_id_info.is_apu    = true;
                    break;

                case ASIC_ID_PLACEHOLDER3:
                    asic_id_info.asic_type = ASIC_Gfx9;
                    asic_id_info.is_apu    = true;
                    break;

                case ASIC_ID_GFX1010:
                case ASIC_ID_GFX1010LITE:
                    asic_id_info.asic_type         = ASIC_Gfx10;
                    asic_id_info.gdt_asic_type     = GDT_GFX10_1_0;
                    asic_id_info.default_device_id = 0x7310;
                    break;

                case ASIC_ID_PLACEHOLDER4:
                    asic_id_info.asic_type = ASIC_Gfx10;
                    break;

                case ASIC_ID_PLACEHOLDER5:
                    asic_id_info.asic_type = ASIC_Gfx10;
                    break;

                case ASIC_ID_GFX1012:
                    asic_id_info.asic_type         = ASIC_Gfx10;
                    asic_id_info.gdt_asic_type     = GDT_GFX10_1_0;
                    asic_id_info.default_device_id = 0x7340;
                    break;

                case ASIC_ID_PLACEHOLDER6:
                    asic_id_info.asic_type = ASIC_Gfx10;
                    break;

                case ASIC_ID_PLACEHOLDER7:
                    asic_id_info.asic_type = ASIC_Gfx10;
                    break;

                default:
                    continue;
                }

                asic_id_info_map_.insert(std::pair<AsicIDEnum, AsicIdInfo>(static_cast<AsicIDEnum>(asic_id_iter), asic_id_info));
            }

            is_asic_info_initialized_ = true;
        }
    }

    ASICType AsicInfoManager::GetASICTypeFromAsicID(AsicID asic_id)
    {
        static const char* kAsicTypeStr[] = {"Gfx6", "Gfx7", "Gfx8", "Gfx9", "Gfx10", "Unknown"};
        ASICType retVal = ASIC_UNKNOWN;

        if (!is_asic_info_initialized_)
        {
            InitializeAsicInfo();
        }

        auto asic_type_iter = asic_id_info_map_.find(asic_id);

        if (asic_type_iter != asic_id_info_map_.end())
        {
            retVal = asic_type_iter->second.asic_type;

            std::stringstream ss;
            if (asic_type_iter->second.is_apu)
            {
                ss << "Recognized an APU with " << kAsicTypeStr[retVal] << " graphics.";
            }
            else
            {
                ss << "Recognized a " << kAsicTypeStr[retVal] << " card.";
            }

            GPA_LogMessage(ss.str().c_str());
        }
        else
        {
            std::stringstream errorMessage;
            errorMessage << "Unrecognized asic type: " << asic_id << ".";
            GPA_LogError(errorMessage.str().c_str());
            assert(0);  // Unknown ASIC Type, need to update enums list from UGL driver
            retVal = ASIC_UNKNOWN;
        }

        return retVal;
    }

    bool AsicInfoManager::GetFallbackAsicInfo(const AsicID& asic_id, GDT_HW_ASIC_TYPE& gdt_hw_asic_type, uint32_t& default_device_id)
    {
        if (!is_asic_info_initialized_)
        {
            InitializeAsicInfo();
        }

        auto asic_type_iter = asic_id_info_map_.find(asic_id);

        if (asic_type_iter != asic_id_info_map_.end())
        {
            gdt_hw_asic_type = asic_type_iter->second.gdt_asic_type;
            default_device_id = asic_type_iter->second.default_device_id;
            return true;
        }

        std::stringstream errorMessage;
        errorMessage << "Unrecognized asic type: " << asic_id << ".";
        GPA_LogError(errorMessage.str().c_str());
        assert(0);  // Unknown ASIC Type, need to update enums list from UGL driver
        return false;
    }

    AsicInfoManager::AsicInfoManager() : is_asic_info_initialized_(false)
    {
    }

    AsicInfoManager::~AsicInfoManager()
    {
        asic_id_info_map_.clear();
        is_asic_info_initialized_ = false;
    }

    bool AsicInfoManager::GetAsicInfoFromDriver(ASICInfo& asicInfo)
    {
        if (nullptr == _oglGetPerfMonitorCountersAMD || nullptr == _oglGetPerfMonitorGroupStringAMD || nullptr == _oglGetPerfMonitorCounterInfoAMD ||
            nullptr == _oglGetPerfMonitorCounterStringAMD || nullptr == _oglGenPerfMonitorsAMD || nullptr == _oglDeletePerfMonitorsAMD ||
            nullptr == _oglSelectPerfMonitorCountersAMD || nullptr == _oglBeginPerfMonitorAMD || nullptr == _oglEndPerfMonitorAMD ||
            nullptr == _oglGetPerfMonitorCounterDataAMD)
        {
            // No AMD_performance_monitor support, means no ASIC info
            GPA_LogError("One or more of the GL_AMD_performance_monitor functions were not found.");
            return false;
        }

        GLint numCounters = 0;
        bool  bResult     = false;

#ifndef GLES
        const GLubyte* pVersion  = _oglGetString(GL_VERSION);
        asicInfo.m_driverVersion = ExtractDriverVersionNumber(pVersion);
#else
        asicInfo.m_driverVersion = INT_MAX;
#endif

        if (asicInfo.m_driverVersion < s_GL_DRIVER_VER_WITH_ONLY_GCN_SUPPORT)
        {
            // pre-GCN devices were removed from the driver starting with version 13452.
            // if the driver version is earlier than that we will return an error.
            GPA_LogError("OpenGL driver version is too old. Please update your driver.");
            return false;
        }

        GLint group = GetASICInfoGroupID();

        if (-1 == group)
        {
            GPA_LogError("Unable to find the GPIN group.");
            return false;
        }

        // Start by getting the list of counters in the group
        _oglGetPerfMonitorCountersAMD(group, &numCounters, nullptr, 0, nullptr);

        GLuint* pCounterList = new (std::nothrow) GLuint[numCounters];

        if (nullptr != pCounterList)
        {
            // Get the list of counters in the group
            _oglGetPerfMonitorCountersAMD(group, nullptr, nullptr, numCounters, pCounterList);

            GLuint monitor    = 0;
            GLuint resultSize = 0;

            // Create a monitor for all GPIN counters
            _oglGenPerfMonitorsAMD(1, &monitor);

            // Enable all GPIN counters
            for (int i = 0; i < numCounters; i++)
            {
                _oglSelectPerfMonitorCountersAMD(monitor, GL_TRUE, group, 1, &pCounterList[i]);
            }

            // begin / end the monitor so that the data is obtained
            _oglBeginPerfMonitorAMD(monitor);
            _oglEndPerfMonitorAMD(monitor);

            // Get the counter result size
            _oglGetPerfMonitorCounterDataAMD(monitor, GL_PERFMON_RESULT_SIZE_AMD, sizeof(resultSize), &resultSize, nullptr);

            // Result should be 3 GLuint per counter
            GLint expectedResultSize = (3 * sizeof(GLuint)) * numCounters;
            assert(static_cast<GLint>(resultSize) == expectedResultSize);

            if (static_cast<GLint>(resultSize) == expectedResultSize)
            {
                GLubyte* pCounterData = new (std::nothrow) GLubyte[resultSize];

                if (nullptr != pCounterData)
                {
                    // Get the counter results
                    _oglGetPerfMonitorCounterDataAMD(monitor, GL_PERFMON_RESULT_AMD, resultSize, reinterpret_cast<GLuint*>(pCounterData), nullptr);

                    for (int i = 0; i < numCounters; i++)
                    {
                        // index into the result array for each counter -- the result is the third GLuint out of the three
                        unsigned int value = (reinterpret_cast<GLuint*>(pCounterData))[(i * 3) + 2];

                        switch (i)
                        {
                        case ASIC_TYPE_INDEX:
                            asicInfo.m_asicID   = static_cast<AsicID>(value);
                            asicInfo.m_asicType = GetASICTypeFromAsicID(asicInfo.m_asicID);
                            break;

                        case ASIC_NUM_SIMD_INDEX:
                            if (s_GL_DRIVER_VER_WITH_GPIN_COUNTERS <= asicInfo.m_driverVersion)
                            {
                                asicInfo.m_numSIMD = value;
                            }
                            break;

                        case ASIC_NUM_RB_INDEX:
                            if (s_GL_DRIVER_VER_WITH_GPIN_COUNTERS <= asicInfo.m_driverVersion)
                            {
                                asicInfo.m_numRB = value;
                            }
                            break;

                        case ASIC_NUM_SPI_INDEX:
                            if (s_GL_DRIVER_VER_WITH_GPIN_COUNTERS <= asicInfo.m_driverVersion)
                            {
                                asicInfo.m_numSPI = value;
                            }
                            break;

                        case ASIC_NUM_SE_INDEX:
                            if (s_GL_DRIVER_VER_WITH_GPIN_COUNTERS <= asicInfo.m_driverVersion)
                            {
                                asicInfo.m_numSE = value;
                            }
                            break;

                        case ASIC_NUM_SA_INDEX:
                            if (s_GL_DRIVER_VER_WITH_GPIN_COUNTERS <= asicInfo.m_driverVersion)
                            {
                                asicInfo.m_numSA = value;
                            }
                            break;

                        case ASIC_NUM_CU_INDEX:
                            if (s_GL_DRIVER_VER_WITH_GPIN_COUNTERS <= asicInfo.m_driverVersion)
                            {
                                asicInfo.m_numCU = value;
                            }
                            break;

                        case ASIC_DEV_ID_INDEX:
                            if (s_GL_DRIVER_VER_WITH_GPIN_COUNTERS <= asicInfo.m_driverVersion)
                            {
                                asicInfo.m_deviceId = value;
                            }
                            break;

                        case ASIC_DEV_REV_INDEX:
                            if (s_GL_DRIVER_VER_WITH_GPIN_COUNTERS <= asicInfo.m_driverVersion)
                            {
                                asicInfo.m_deviceRev = value;
                            }
                            break;
                        }

                        _oglSelectPerfMonitorCountersAMD(monitor, GL_FALSE, group, 1, &pCounterList[i]);
                    }

                    bResult = true;
                    delete[] pCounterData;
                }
            }

            _oglDeletePerfMonitorsAMD(1, &monitor);
            delete[] pCounterList;
        }

        if (bResult)
        {
            std::stringstream message;
            message << "ASIC ID returned from driver is: " << asicInfo.m_asicID << " and GL_VERSION is: " << asicInfo.m_driverVersion << ".";
            GPA_LogMessage(message.str().c_str());
        }

        return bResult;
    }

}  // namespace oglUtils
