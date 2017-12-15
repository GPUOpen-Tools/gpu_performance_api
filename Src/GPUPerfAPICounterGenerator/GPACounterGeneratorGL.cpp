//==============================================================================
// Copyright (c) 2016-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for GL counter generation
//==============================================================================

#include "GPACounterGeneratorGL.h"
#include "Logging.h"

#include "GLEntryPoints.h"
#ifdef EXTRA_COUNTER_INFO
    #include <sstream>
#endif

#include "PublicCounterDefsGLGfx6.h"
#include "PublicCounterDefsGLGfx7.h"
#include "PublicCounterDefsGLGfx8.h"
#include "PublicCounterDefsGLGfx9.h"

#include "InternalCountersGLGfx6.h"
#include "InternalCountersGLGfx7.h"
#include "InternalCountersGLGfx8.h"
#include "InternalCountersGLGfx9.h"

#include "GPACounterGeneratorSchedulerManager.h"


static const char* gs_pDriverSuppliedCounter = GPA_HIDE_NAME("OpenGL Driver-Supplied Counter"); ///< default counter name for a driver-supplied counter

GPA_CounterGeneratorGL::GPA_CounterGeneratorGL() :
    m_pDriverSuppliedGroups(nullptr),
    m_driverSuppliedGroupCount(0)
{
    GPA_CounterGeneratorBase::SetAllowedCounters(true, true, false); // TODO: investigate allowing software counters in public build (i.e. GPUTime for all hardware)

    // TODO: need to make some changes to support GPUTime counter on Intel and NVidia in public build
    for (int gen = GDT_HW_GENERATION_FIRST_AMD; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(GPA_API_OPENGL, static_cast<GDT_HW_GENERATION>(gen), this);
    }

    // AMD only for GLES (for now) -- will allow Intel and NVidia once GPUTime is supported in public builds
    for (int gen = GDT_HW_GENERATION_FIRST_AMD; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(GPA_API_OPENGLES, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GPA_CounterGeneratorGL::~GPA_CounterGeneratorGL()
{
    Cleanup();
}

bool GPA_CounterGeneratorGL::GenerateDriverSuppliedInternalCounters(GPA_HardwareCounters* pHardwareCounters)
{
    if (m_driverSuppliedGroupCount            == 0       &&
        _oglGetPerfMonitorGroupsAMD        != nullptr &&
        _oglGetPerfMonitorGroupStringAMD   != nullptr &&
        _oglGetPerfMonitorCountersAMD      != nullptr &&
        _oglGetPerfMonitorCounterStringAMD != nullptr)
    {
        // clean up previously allocated memory, if any (there shouldn't be...)
        Cleanup();

        GLint nNumGroups;
        _oglGetPerfMonitorGroupsAMD(&nNumGroups, 0, nullptr);

        // Get the group Ids
        GLuint* pPerfGroups = new(std::nothrow) GLuint[nNumGroups];

        if (pPerfGroups == nullptr)
        {
            GPA_LogError("Unable to allocate memory to store the group IDs.");
            return false;
        }

        _oglGetPerfMonitorGroupsAMD(nullptr, nNumGroups, pPerfGroups);

        m_driverSuppliedGroupCount = nNumGroups - (pHardwareCounters->m_groupCount - 1);

        m_pDriverSuppliedGroups = new(std::nothrow) GPA_CounterGroupDesc[m_driverSuppliedGroupCount];

        if (m_pDriverSuppliedGroups == nullptr)
        {
            GPA_LogError("Unable to allocate memory to store the group IDs.");
            return false;
        }

        // declare this outside the loops
        GPA_HardwareCounterDescExt counter;
        GLuint driverPerfGroupId;

        for (unsigned int i = 0; i < m_driverSuppliedGroupCount; i++)
        {
            driverPerfGroupId = pPerfGroups[pHardwareCounters->m_groupCount - 1 + i]; //offset by one to take the "GPUTime" group into account
            char strGroupName[64];
            memset(strGroupName, 0, 64);
            GLint nCounters = 0;
            GLint nMaxActive = 0;

            // Get the group name
            _oglGetPerfMonitorGroupStringAMD(driverPerfGroupId, 64, nullptr, strGroupName);

            size_t groupNameLen = strlen(strGroupName) + 1;
            m_pDriverSuppliedGroups[i].m_pName = new(std::nothrow) char[groupNameLen];

            if (m_pDriverSuppliedGroups[i].m_pName == nullptr)
            {
                GPA_LogError("Unable to allocate memory to store the counter group name.");
                return false;
            }

            strcpy_s(m_pDriverSuppliedGroups[i].m_pName, groupNameLen, strGroupName);

            m_counterBuffers.push_back(m_pDriverSuppliedGroups[i].m_pName);

            // Get the number of counters and max active counters
            _oglGetPerfMonitorCountersAMD(driverPerfGroupId, &nCounters, &nMaxActive, 0, nullptr);

            m_pDriverSuppliedGroups[i].m_groupIndex = pHardwareCounters->m_groupCount - 1 + i;
            m_pDriverSuppliedGroups[i].m_maxActiveCounters = nMaxActive;
            m_pDriverSuppliedGroups[i].m_numCounters = nCounters;
            m_pDriverSuppliedGroups[i].m_blockInstance = 0;

            for (int c = 0; c < nCounters; c++)
            {
                counter.m_groupIndex = m_pDriverSuppliedGroups[i].m_groupIndex + 1;//i + 1;
                counter.m_pHardwareCounter = new(std::nothrow) GPA_HardwareCounterDesc;

                if (counter.m_pHardwareCounter == nullptr)
                {
                    GPA_LogError("Unable to allocate memory to store the hardwareCounter.");
                    return false;
                }

                m_hardwareCounterDescs.push_back(counter.m_pHardwareCounter);

                counter.m_pHardwareCounter->m_counterIndexInGroup = c;

                GLsizei nNameLength;
                _oglGetPerfMonitorCounterStringAMD(driverPerfGroupId, c, 0, &nNameLength, nullptr);

                char* pCounterName = new(std::nothrow) char[nNameLength + 1];

                if (pCounterName == nullptr)
                {
                    GPA_LogError("Unable to allocate memory to store the counter name.");
                    return false;
                }

                m_counterBuffers.push_back(pCounterName);

                memset(pCounterName, 0, nNameLength + 1);

                _oglGetPerfMonitorCounterStringAMD(driverPerfGroupId, c, nNameLength, nullptr, pCounterName);

                counter.m_pHardwareCounter->m_pName = GPA_HIDE_NAME(pCounterName);

                size_t nDescSize = 3 + strlen(strGroupName) + strlen(gs_pDriverSuppliedCounter); // 3 = 2 # signs and the terminating null
                counter.m_pHardwareCounter->m_pDescription = new(std::nothrow) char[nDescSize];

                if (counter.m_pHardwareCounter->m_pDescription == nullptr)
                {
                    GPA_LogError("Unable to allocate memory to store the counter description.");
                    return false;
                }

                m_counterBuffers.push_back(counter.m_pHardwareCounter->m_pDescription);

                memset(counter.m_pHardwareCounter->m_pDescription, 0, nDescSize);
                strcpy_s(counter.m_pHardwareCounter->m_pDescription, nDescSize, GPA_HIDE_NAME("#"));
                strcat_s(counter.m_pHardwareCounter->m_pDescription, nDescSize, GPA_HIDE_NAME(strGroupName));
                strcat_s(counter.m_pHardwareCounter->m_pDescription, nDescSize, GPA_HIDE_NAME("#"));
                strcat_s(counter.m_pHardwareCounter->m_pDescription, nDescSize, GPA_HIDE_NAME(gs_pDriverSuppliedCounter));

                counter.m_pHardwareCounter->m_type = GPA_DATA_TYPE_UINT64;
                counter.m_groupIdDriver = driverPerfGroupId;
                counter.m_counterIdDriver = 0;

                m_driverSuppliedCounters.push_back(counter);
            }
        }

        m_counterGroupDescs.push_back(m_pDriverSuppliedGroups);

        delete[] pPerfGroups;
    } //if

    pHardwareCounters->m_pAdditionalGroups = m_pDriverSuppliedGroups;
    pHardwareCounters->m_additionalGroupCount = m_driverSuppliedGroupCount;
    pHardwareCounters->m_counters.insert(pHardwareCounters->m_counters.end(), m_driverSuppliedCounters.begin(), m_driverSuppliedCounters.end());

    return true;
}

bool GPA_CounterGeneratorGL::GenerateInternalCounters(GPA_HardwareCounters* pHardwareCounters, GDT_HW_GENERATION generation)
{
    UNREFERENCED_PARAMETER(generation);
    pHardwareCounters->m_counters.clear();
    // declare this outside the loops
    GPA_HardwareCounterDescExt counter;

#if defined(_DEBUG) && defined(_WIN32) && defined(AMDT_INTERNAL)
    // Debug builds will generate a file that lists the counter names in a format that can be
    // easily copy/pasted into the GPUPerfAPIUnitTests project
    FILE* pFile = nullptr;
    fopen_s(&pFile, "HardwareCounterNamesGL.txt", "w");
#endif

    // for each group, get the group name, number of counters, and max counters (and maybe validate them)
    for (int g = 0; g < static_cast<int>(pHardwareCounters->m_groupCount); g++)
    {
        GPA_HardwareCounterDesc* pGlGroup = pHardwareCounters->m_ppCounterGroupArray[g];

        // only add the number of counters that are supported; but no more than the number that we expect
        const gpa_uint64 numCountersInGroup = pHardwareCounters->m_pGroups[g].m_numCounters;

        for (int c = 0; c < numCountersInGroup; c++)
        {
            counter.m_groupIndex = g;
            counter.m_pHardwareCounter = &(pGlGroup[c]);

            // Temporarily set the groupIdDriver to be g, but we actually need to query the group IDs from GL.
            // GPUPerfAPIGL will query the runtime in OpenContext for this information and will update the group Ids.
            counter.m_groupIdDriver = g;
            counter.m_counterIdDriver = 0;

#if defined(_DEBUG) && defined(_WIN32) && defined(AMDT_INTERNAL)

            if (pFile != nullptr)
            {
                fwrite("    \"", 1, 5, pFile);
                std::string tmpName(counter.m_pHardwareCounter->m_pName);
                size_t size = tmpName.size();
                fwrite(counter.m_pHardwareCounter->m_pName, 1, size, pFile);
                fwrite("\",", 1, 2, pFile);
#ifdef EXTRA_COUNTER_INFO
                // this can be useful for debugging counter definitions
                std::stringstream ss;
                ss << " " << counter.m_groupIndex << ", " << counter.m_groupIdDriver << ", " << counter.m_pHardwareCounter->m_counterIndexInGroup << ", " << counter.m_counterIdDriver;
                std::string tmpCounterInfo(ss.str());
                size = tmpCounterInfo.size();
                fwrite(tmpCounterInfo.c_str(), 1, size, pFile);
#endif
                fwrite("\n", 1, 1, pFile);
            }

#endif
            pHardwareCounters->m_counters.push_back(counter);
        }
    }

    // In openGL we always tack the GPUTime counters onto the end
    pHardwareCounters->m_gpuTimeBottomToBottomCounterIndex = static_cast<gpa_int32>(pHardwareCounters->m_counters.size()) - 2;
    pHardwareCounters->m_gpuTimeTopToBottomCounterIndex = static_cast<gpa_uint32>(pHardwareCounters->m_counters.size()) - 1;

    // now add extra groups/counters exposed by the driver
    GenerateDriverSuppliedInternalCounters(pHardwareCounters);

#if defined(_DEBUG) && defined(_WIN32) && defined(AMDT_INTERNAL)

    if (pFile != nullptr)
    {
        fclose(pFile);
    }

#endif

    pHardwareCounters->m_countersGenerated = true;

    return true;
}

void GPA_CounterGeneratorGL::Cleanup()
{
    for (auto buffer : m_counterBuffers)
    {
        delete[] buffer;
    }

    for (auto counterDesc : m_hardwareCounterDescs)
    {
        delete counterDesc;
    }

    for (auto groupDesc : m_counterGroupDescs)
    {
        delete[] groupDesc;
    }

    m_counterBuffers.clear();
    m_hardwareCounterDescs.clear();
    m_counterGroupDescs.clear();
    m_driverSuppliedCounters.clear();
}

GPA_Status GPA_CounterGeneratorGL::GeneratePublicCounters(GDT_HW_GENERATION desiredGeneration, GPA_PublicCounters* pPublicCounters)
{
    pPublicCounters->Clear();

    switch (desiredGeneration)
    {
        case GDT_HW_GENERATION_SOUTHERNISLAND:
            AutoDefinePublicCountersGLGfx6(*pPublicCounters);
            break;

        case GDT_HW_GENERATION_SEAISLAND:
            AutoDefinePublicCountersGLGfx7(*pPublicCounters);
            break;

        case GDT_HW_GENERATION_VOLCANICISLAND:
            AutoDefinePublicCountersGLGfx8(*pPublicCounters);
            break;

        case GDT_HW_GENERATION_GFX9:
            AutoDefinePublicCountersGLGfx9(*pPublicCounters);
            break;

        default:
            GPA_LogError("Unsupported or unrecognized hardware generation. Cannot generate public counters.");
            return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    return GPA_STATUS_OK;
}

GPA_Status GPA_CounterGeneratorGL::GenerateHardwareCounters(GDT_HW_GENERATION desiredGeneration, GPA_HardwareCounters* pHardwareCounters)
{
    switch (desiredGeneration)
    {
        case GDT_HW_GENERATION_SOUTHERNISLAND:
            pHardwareCounters->m_ppCounterGroupArray = GLCounterGroupArrayGfx6;
            pHardwareCounters->m_pGroups             = HWGLGroupsGfx6;
            pHardwareCounters->m_groupCount          = HWGLGroupCountGfx6;
            pHardwareCounters->m_pSQCounterGroups    = HWGLSQGroupsGfx6;
            pHardwareCounters->m_sqGroupCount        = HWGLSQGroupCountGfx6;
            pHardwareCounters->m_gpuTimeIndex        = HWGLGPUTimeIndexGfx6;
            pHardwareCounters->m_pIsolatedGroups     = HWGLSQIsolatedGroupsGfx6;
            pHardwareCounters->m_isolatedGroupCount  = HWGLSQIsolatedGroupCountGfx6;
            break;

        case GDT_HW_GENERATION_SEAISLAND:
            pHardwareCounters->m_ppCounterGroupArray = GLCounterGroupArrayGfx7;
            pHardwareCounters->m_pGroups             = HWGLGroupsGfx7;
            pHardwareCounters->m_groupCount          = HWGLGroupCountGfx7;
            pHardwareCounters->m_pSQCounterGroups    = HWGLSQGroupsGfx7;
            pHardwareCounters->m_sqGroupCount        = HWGLSQGroupCountGfx7;
            pHardwareCounters->m_gpuTimeIndex        = HWGLGPUTimeIndexGfx7;
            pHardwareCounters->m_pIsolatedGroups     = HWGLSQIsolatedGroupsGfx7;
            pHardwareCounters->m_isolatedGroupCount  = HWGLSQIsolatedGroupCountGfx7;
            break;

        case GDT_HW_GENERATION_VOLCANICISLAND:
            pHardwareCounters->m_ppCounterGroupArray = GLCounterGroupArrayGfx8;
            pHardwareCounters->m_pGroups             = HWGLGroupsGfx8;
            pHardwareCounters->m_groupCount          = HWGLGroupCountGfx8;
            pHardwareCounters->m_pSQCounterGroups    = HWGLSQGroupsGfx8;
            pHardwareCounters->m_sqGroupCount        = HWGLSQGroupCountGfx8;
            pHardwareCounters->m_gpuTimeIndex        = HWGLGPUTimeIndexGfx8;
            pHardwareCounters->m_pIsolatedGroups     = HWGLSQIsolatedGroupsGfx8;
            pHardwareCounters->m_isolatedGroupCount  = HWGLSQIsolatedGroupCountGfx8;
            break;

        case GDT_HW_GENERATION_GFX9:
            pHardwareCounters->m_ppCounterGroupArray = GLCounterGroupArrayGfx9;
            pHardwareCounters->m_pGroups             = HWGLGroupsGfx9;
            pHardwareCounters->m_groupCount          = HWGLGroupCountGfx9;
            pHardwareCounters->m_pSQCounterGroups    = HWGLSQGroupsGfx9;
            pHardwareCounters->m_sqGroupCount        = HWGLSQGroupCountGfx9;
            pHardwareCounters->m_gpuTimeIndex        = HWGLGPUTimeIndexGfx9;
            pHardwareCounters->m_pIsolatedGroups     = HWGLSQIsolatedGroupsGfx9;
            pHardwareCounters->m_isolatedGroupCount  = HWGLSQIsolatedGroupCountGfx9;
            break;

        default:
            GPA_LogError("Unrecognized or unhandled hardware generation.");
            return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }


    // need to count total number of internal counters, since split into groups
    if (!pHardwareCounters->m_countersGenerated)
    {
        if (GenerateInternalCounters(pHardwareCounters, desiredGeneration) == false)
        {
            GPA_LogError("Unable to generate internal counters.");
            pHardwareCounters->m_currentGroupUsedCounts.resize(0);
            return GPA_STATUS_ERROR_COUNTERS_NOT_OPEN;
        }
    }

    unsigned int uGroupCount = pHardwareCounters->m_groupCount;
    pHardwareCounters->m_currentGroupUsedCounts.resize(uGroupCount);

    return GPA_STATUS_OK;
}

GPA_Status GPA_CounterGeneratorGL::GenerateSoftwareCounters(GDT_HW_GENERATION desiredGeneration, GPA_SoftwareCounters* pSoftwareCounters)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(pSoftwareCounters);
    GPA_Status retVal = GPA_STATUS_OK;

    return retVal;
}
