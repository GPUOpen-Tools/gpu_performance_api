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
#include "GLInclude.h"
#include "ASICInfo.h"

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

    /// Get the corresponding ASIC type for the specified ASIC ID
    /// \param asicID the ASIC ID whose tpye is needed
    /// \return the ASIC type of the specified ASIC ID
    ASICType GetASICTypeFromAsicID(AsicID asicID)
    {
        ASICType retVal = ASIC_UNKNOWN;

        // Decode the ASIC Type
        switch (asicID)
        {
        case ASIC_ID_TAHITI_P:
        case ASIC_ID_PITCAIRN_PM:
        case ASIC_ID_CAPEVERDE_M:
        case ASIC_ID_OLAND_M:
        case ASIC_ID_HAINAN_M:
            GPA_LogMessage("Recognized a GFX6 card.");
            retVal = ASIC_Gfx6;
            break;

        case ASIC_ID_BONAIRE_M:
        case ASIC_ID_HAWAII_P:
            GPA_LogMessage("Recognized a GFX7 card.");
            retVal = ASIC_Gfx7;
            break;

        case ASIC_ID_KALINDI:
        case ASIC_ID_GODAVARI:
        case ASIC_ID_SPECTRE:
        case ASIC_ID_SPOOKY:
            GPA_LogMessage("Recognized an APU with GFX7 graphics.");
            retVal = ASIC_Gfx7;
            break;

        case ASIC_ID_ICELAND_M:
        case ASIC_ID_TONGA_P:
        case ASIC_ID_FIJI_P:
        case ASIC_ID_ELLESMERE:
        case ASIC_ID_BAFFIN:
        case ASIC_ID_LEXA:
        case ASIC_ID_VEGAM:
            GPA_LogMessage("Recognized a GFX8 card.");
            retVal = ASIC_Gfx8;
            break;

        case ASIC_ID_CARRIZO:
        case ASIC_ID_STONEY:
            GPA_LogMessage("Recognized an APU with GFX8 graphics.");
            retVal = ASIC_Gfx8;
            break;

        case ASIC_ID_GFX900:
        case ASIC_ID_PLACEHOLDER1:
        case ASIC_ID_GFX906:
            GPA_LogMessage("Recognized a GFX9 card.");
            retVal = ASIC_Gfx9;
            break;

        case ASIC_ID_GFX902:
        case ASIC_ID_PLACEHOLDER:
        case ASIC_ID_PLACEHOLDER2:
        case ASIC_ID_PLACEHOLDER3:
            GPA_LogMessage("Recognized an APU with GFX9 graphics.");
            retVal = ASIC_Gfx9;
            break;

        case ASIC_ID_GFX1010:
        case ASIC_ID_GFX1010LITE:
        case ASIC_ID_PLACEHOLDER4:
        case ASIC_ID_PLACEHOLDER5:
        case ASIC_ID_GFX1012:
        case ASIC_ID_PLACEHOLDER6:
        case ASIC_ID_PLACEHOLDER7:
            GPA_LogMessage("Recognized a GFX10 card.");
            retVal = ASIC_Gfx10;
            break;

        default:
            std::stringstream errorMessage;
            errorMessage << "Unrecognized asic type: " << asicID << ".";
            GPA_LogError(errorMessage.str().c_str());
            assert(0);  // Unknown ASIC Type, need to update enums list from UGL driver
            retVal = ASIC_UNKNOWN;
        }

        return retVal;
    }

#ifndef GLES

    /// Parses a version number like this: "4.2.12325 Compatibility Profile Context 13.100.0.0"
    /// to extract the "12325" portion.
    /// \param pVersion the version string to extract the number from
    /// \return 0 on failure, the build version number on success
    int ExtractVersionNumber(const GLubyte* pVersion)
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

    /// Populate the ASIC Info struct with the GPIN counters
    /// \param[out] asicInfo AsicInfo struct populated by GPIN group
    /// \return false if unable to query GPIN counters, true otherwise
    bool GetAsicInfo(ASICInfo& asicInfo)
    {
        GLint numCounters = 0;
        bool  bResult     = false;

#ifndef GLES
        const GLubyte* pVersion  = _oglGetString(GL_VERSION);
        asicInfo.m_driverVersion = ExtractVersionNumber(pVersion);
#else
        int nVersion = INT_MAX;
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
            assert((GLint)resultSize == expectedResultSize);

            if ((GLint)resultSize == expectedResultSize)
            {
                GLubyte* pCounterData = new (std::nothrow) GLubyte[resultSize];

                if (nullptr != pCounterData)
                {
                    // Get the counter results
                    _oglGetPerfMonitorCounterDataAMD(monitor, GL_PERFMON_RESULT_AMD, resultSize, (GLuint*)pCounterData, nullptr);

                    for (int i = 0; i < numCounters; i++)
                    {
                        // index into the result array for each counter -- the result is the third GLuint out of the three
                        unsigned int value = ((GLuint*)pCounterData)[(i * 3) + 2];

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

        return bResult;
    }

    bool GetASICInfo(ASICInfo& asicInfo)
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

        if (!GetAsicInfo(asicInfo))
        {
            GPA_LogError("Unable to get the asic info.");
            return false;
        }

        std::stringstream message;
        message << "ASIC ID returned from driver is: " << asicInfo.m_asicID << " and GL_VERSION is: " << asicInfo.m_driverVersion << ".";
        GPA_LogMessage(message.str().c_str());

        return true;
    }
}  // namespace oglUtils
