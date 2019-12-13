//==============================================================================
// Copyright (c) 2016-2019 Advanced Micro Devices, Inc. All rights reserved.
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

#include "PublicCounterDefsGLGfx8.h"
#include "PublicCounterDefsGLGfx9.h"
#include "PublicCounterDefsGLGfx10.h"

#include "PublicCounterDefsGLGfx8Asics.h"
#include "PublicCounterDefsGLGfx9Asics.h"
#include "PublicCounterDefsGLGfx10Asics.h"

#include "GPAHWCounterGLGfx8.h"
#include "GPAHWCounterGLGfx9.h"
#include "GPAHWCounterGLGfx10.h"

#include "GPACounterGeneratorSchedulerManager.h"

static const char* gs_pDriverSuppliedCounter = GPA_HIDE_NAME("OpenGL Driver-Supplied Counter");  ///< default counter name for a driver-supplied counter

GPA_CounterGeneratorGL::GPA_CounterGeneratorGL()
    : m_pDriverSuppliedGroups(nullptr)
    , m_driverSuppliedGroupCount(0)
{
    GPA_CounterGeneratorBase::SetAllowedCounters(
        true, true, false);  // TODO: investigate allowing software counters in public build (i.e. GPUTime for all hardware)

    // TODO: need to make some changes to support GPUTime counter on Intel and NVidia in public build
    for (int gen = GDT_HW_GENERATION_FIRST_AMD; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(GPA_API_OPENGL, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GPA_CounterGeneratorGL::~GPA_CounterGeneratorGL()
{
    Cleanup();
}

bool GPA_CounterGeneratorGL::GenerateDriverSuppliedInternalCounters(GPA_HardwareCounters* pHardwareCounters)
{
    if (oglUtils::InitializeGLFunctions() && m_driverSuppliedGroupCount == 0 && nullptr != oglUtils::_oglGetPerfMonitorGroupsAMD &&
        nullptr != oglUtils::_oglGetPerfMonitorGroupStringAMD && nullptr != oglUtils::_oglGetPerfMonitorCountersAMD &&
        nullptr != oglUtils::_oglGetPerfMonitorCounterStringAMD)
    {
        // clean up previously allocated memory, if any (there shouldn't be...)
        Cleanup();

        GLint nNumGroups = 0;
        oglUtils::_oglGetPerfMonitorGroupsAMD(&nNumGroups, 0, nullptr);

        if (0 == nNumGroups)
        {
            return false;
        }

        if (static_cast<unsigned int>(nNumGroups) < pHardwareCounters->m_groupCount)
        {
            return false;
        }

        // Get the group Ids
        GLuint* pPerfGroups = new (std::nothrow) GLuint[nNumGroups];

        if (nullptr == pPerfGroups)
        {
            GPA_LogError("Unable to allocate memory to store the group IDs.");
            return false;
        }

        oglUtils::_oglGetPerfMonitorGroupsAMD(nullptr, nNumGroups, pPerfGroups);

        m_driverSuppliedGroupCount = nNumGroups - (pHardwareCounters->m_groupCount - 1);

        m_pDriverSuppliedGroups = new (std::nothrow) GPA_CounterGroupDesc[m_driverSuppliedGroupCount];

        if (nullptr == m_pDriverSuppliedGroups)
        {
            GPA_LogError("Unable to allocate memory to store the group IDs.");
            return false;
        }

        // declare this outside the loops
        GPA_HardwareCounterDescExt counter = {};

        for (unsigned int i = 0; i < m_driverSuppliedGroupCount; i++)
        {
            GLuint driverPerfGroupId = pPerfGroups[pHardwareCounters->m_groupCount - 1 + i];  //offset by one to take the "GPUTime" group into account
            char   strGroupName[64];
            memset(strGroupName, 0, 64);
            GLint nCounters  = 0;
            GLint nMaxActive = 0;

            // Get the group name
            oglUtils::_oglGetPerfMonitorGroupStringAMD(driverPerfGroupId, 64, nullptr, strGroupName);

            size_t groupNameLen                = strlen(strGroupName) + 1;
            m_pDriverSuppliedGroups[i].m_pName = new (std::nothrow) char[groupNameLen];

            if (nullptr == m_pDriverSuppliedGroups[i].m_pName)
            {
                GPA_LogError("Unable to allocate memory to store the counter group name.");
                return false;
            }

            strcpy_s(m_pDriverSuppliedGroups[i].m_pName, groupNameLen, strGroupName);

            m_counterBuffers.push_back(m_pDriverSuppliedGroups[i].m_pName);

            // Get the number of counters and max active counters
            oglUtils::_oglGetPerfMonitorCountersAMD(driverPerfGroupId, &nCounters, &nMaxActive, 0, nullptr);

            m_pDriverSuppliedGroups[i].m_groupIndex                = pHardwareCounters->m_groupCount - 1 + i;
            m_pDriverSuppliedGroups[i].m_maxActiveDiscreteCounters = nMaxActive;
            m_pDriverSuppliedGroups[i].m_maxActiveSpmCounters      = 0;
            m_pDriverSuppliedGroups[i].m_numCounters               = nCounters;
            m_pDriverSuppliedGroups[i].m_blockInstance             = 0;

            for (int c = 0; c < nCounters; c++)
            {
                counter.m_groupIndex       = m_pDriverSuppliedGroups[i].m_groupIndex + 1;  //i + 1;
                counter.m_pHardwareCounter = new (std::nothrow) GPA_HardwareCounterDesc;

                if (nullptr == counter.m_pHardwareCounter)
                {
                    GPA_LogError("Unable to allocate memory to store the hardwareCounter.");
                    return false;
                }

                m_hardwareCounterDescs.push_back(counter.m_pHardwareCounter);

                counter.m_pHardwareCounter->m_counterIndexInGroup = c;

                GLsizei nNameLength;
                oglUtils::_oglGetPerfMonitorCounterStringAMD(driverPerfGroupId, c, 0, &nNameLength, nullptr);

                char* pCounterName = new (std::nothrow) char[nNameLength + 1];

                if (nullptr == pCounterName)
                {
                    GPA_LogError("Unable to allocate memory to store the counter name.");
                    return false;
                }

                m_counterBuffers.push_back(pCounterName);

                memset(pCounterName, 0, nNameLength + 1);

                oglUtils::_oglGetPerfMonitorCounterStringAMD(driverPerfGroupId, c, nNameLength, nullptr, pCounterName);

                counter.m_pHardwareCounter->m_pName = GPA_HIDE_NAME(pCounterName);

                size_t nDescSize                           = 1 + strlen(gs_pDriverSuppliedCounter);  // 1 for the terminating null
                counter.m_pHardwareCounter->m_pDescription = new (std::nothrow) char[nDescSize];

                if (nullptr == counter.m_pHardwareCounter->m_pDescription)
                {
                    GPA_LogError("Unable to allocate memory to store the counter description.");
                    return false;
                }

                m_counterBuffers.push_back(counter.m_pHardwareCounter->m_pDescription);

                memset(counter.m_pHardwareCounter->m_pDescription, 0, nDescSize);
                strcpy_s(counter.m_pHardwareCounter->m_pDescription, nDescSize, GPA_HIDE_NAME(gs_pDriverSuppliedCounter));

                size_t nGroupSize                    = 1 + strlen(strGroupName);  // 1 for the terminating null
                counter.m_pHardwareCounter->m_pGroup = new (std::nothrow) char[nGroupSize];

                if (nullptr == counter.m_pHardwareCounter->m_pGroup)
                {
                    GPA_LogError("Unable to allocate memory to store the counter group.");
                    return false;
                }

                m_counterBuffers.push_back(counter.m_pHardwareCounter->m_pGroup);

                memset(counter.m_pHardwareCounter->m_pGroup, 0, nGroupSize);
                strcpy_s(counter.m_pHardwareCounter->m_pGroup, nGroupSize, GPA_HIDE_NAME(strGroupName));

                counter.m_pHardwareCounter->m_type = GPA_DATA_TYPE_UINT64;
                counter.m_groupIdDriver            = driverPerfGroupId;
                counter.m_counterIdDriver          = 0;

                m_driverSuppliedCounters.push_back(counter);
            }
        }

        m_counterGroupDescs.push_back(m_pDriverSuppliedGroups);

        delete[] pPerfGroups;
    }

    pHardwareCounters->m_pAdditionalGroups    = m_pDriverSuppliedGroups;
    pHardwareCounters->m_additionalGroupCount = m_driverSuppliedGroupCount;
    pHardwareCounters->m_counters.insert(pHardwareCounters->m_counters.end(), m_driverSuppliedCounters.begin(), m_driverSuppliedCounters.end());

    return true;
}

GPA_Status GPA_CounterGeneratorGL::GenerateInternalCounters(GPA_HardwareCounters* pHardwareCounters, GDT_HW_GENERATION generation)
{
    UNREFERENCED_PARAMETER(generation);
    pHardwareCounters->m_counters.clear();
    // declare this outside the loops
    GPA_HardwareCounterDescExt counter = {};

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

        for (gpa_uint64 c = 0; c < numCountersInGroup; c++)
        {
            counter.m_groupIndex       = g;
            counter.m_pHardwareCounter = &(pGlGroup[c]);

            // Temporarily set the groupIdDriver to be g, but we actually need to query the group IDs from GL.
            // GPUPerfAPIGL will query the runtime in OpenContext for this information and will update the group Ids.
            counter.m_groupIdDriver   = g;
            counter.m_counterIdDriver = 0;

#if defined(_DEBUG) && defined(_WIN32) && defined(AMDT_INTERNAL)

            if (nullptr != pFile)
            {
                fwrite("    \"", 1, 5, pFile);
                std::string tmpName(counter.m_pHardwareCounter->m_pName);
                size_t      size = tmpName.size();
                fwrite(counter.m_pHardwareCounter->m_pName, 1, size, pFile);
                fwrite("\",", 1, 2, pFile);
#ifdef EXTRA_COUNTER_INFO
                // this can be useful for debugging counter definitions
                std::stringstream ss;
                ss << " " << counter.m_groupIndex << ", " << counter.m_groupIdDriver << ", " << counter.m_pHardwareCounter->m_counterIndexInGroup << ", "
                   << counter.m_counterIdDriver;
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

    // now add extra groups/counters exposed by the driver
    GenerateDriverSuppliedInternalCounters(pHardwareCounters);

#if defined(_DEBUG) && defined(_WIN32) && defined(AMDT_INTERNAL)
    if (nullptr != pFile)
    {
        fclose(pFile);
    }
#endif

    return GPA_STATUS_OK;
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

GPA_Status GPA_CounterGeneratorGL::GeneratePublicCounters(GDT_HW_GENERATION    desiredGeneration,
                                                          GDT_HW_ASIC_TYPE     asicType,
                                                          gpa_uint8            generateAsicSpecificCounters,
                                                          GPA_DerivedCounters* pPublicCounters)
{
    auto status = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;

    if (nullptr == pPublicCounters)
    {
        status = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else if (pPublicCounters->m_countersGenerated)
    {
        status = GPA_STATUS_OK;
    }
    else
    {
        pPublicCounters->Clear();

        switch (desiredGeneration)
        {
        case GDT_HW_GENERATION_VOLCANICISLAND:
        {
            AutoDefinePublicDerivedCountersGLGfx8(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                GLGfx8Asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
        }
        break;

        case GDT_HW_GENERATION_GFX9:
        {
            AutoDefinePublicDerivedCountersGLGfx9(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                GLGfx9Asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
        }
        break;

        case GDT_HW_GENERATION_GFX10:
        {
            AutoDefinePublicDerivedCountersGLGfx10(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                GLGfx10Asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
        }
        break;

        default:
            GPA_LogError("Unsupported or unrecognized hardware generation. Cannot generate public counters.");
            break;
        }
    }

    auto internalStatus = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;

#ifdef AMDT_INTERNAL
    internalStatus = GenerateInternalDerivedCounters(desiredGeneration, asicType, generateAsicSpecificCounters, pPublicCounters);
#endif

    if (GPA_STATUS_OK == status)
    {
        pPublicCounters->m_countersGenerated = true;
    }
    else
    {
        status = internalStatus;
    }

    return status;
}

GPA_Status GPA_CounterGeneratorGL::GenerateHardwareCounters(GDT_HW_GENERATION     desiredGeneration,
                                                            GDT_HW_ASIC_TYPE      asicType,
                                                            gpa_uint8             generateAsicSpecificCounters,
                                                            GPA_HardwareCounters* pHardwareCounters)
{
    UNREFERENCED_PARAMETER(asicType);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);

    GPA_Status status = GPA_STATUS_OK;

    if (nullptr == pHardwareCounters)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (pHardwareCounters->m_countersGenerated)  //only generate counters once to improve performance
    {
        return GPA_STATUS_OK;
    }

    pHardwareCounters->Clear();

    switch (desiredGeneration)
    {
    case GDT_HW_GENERATION_VOLCANICISLAND:
        pHardwareCounters->m_ppCounterGroupArray                       = CounterGfx8::GLCounterGroupArrayGfx8;
        pHardwareCounters->m_pGroups                                   = CounterGfx8::HWGLGroupsGfx8;
        pHardwareCounters->m_groupCount                                = CounterGfx8::HWGLGroupCountGfx8;
        pHardwareCounters->m_pSQCounterGroups                          = CounterGfx8::HWGLSQGroupsGfx8;
        pHardwareCounters->m_sqGroupCount                              = CounterGfx8::HWGLSQGroupCountGfx8;
        pHardwareCounters->m_pIsolatedGroups                           = CounterGfx8::HWGLSQIsolatedGroupsGfx8;
        pHardwareCounters->m_isolatedGroupCount                        = CounterGfx8::HWGLSQIsolatedGroupCountGfx8;
        pHardwareCounters->m_timestampBlockIds                         = CounterGfx8::HWGLTimestampBlockIdsGfx8;
        pHardwareCounters->m_timeCounterIndices                        = CounterGfx8::HWGLTimeCounterIndicesGfx8;
        pHardwareCounters->m_gpuTimeBottomToBottomDurationCounterIndex = CounterGfx8::HWGLGputimeBottomToBottomDurationIndexGfx8;
        pHardwareCounters->m_gpuTimeBottomToBottomStartCounterIndex    = CounterGfx8::HWGLGputimeBottomToBottomStartIndexGfx8;
        pHardwareCounters->m_gpuTimeBottomToBottomEndCounterIndex      = CounterGfx8::HWGLGputimeBottomToBottomEndIndexGfx8;
        pHardwareCounters->m_gpuTimeTopToBottomDurationCounterIndex    = CounterGfx8::HWGLGputimeTopToBottomDurationIndexGfx8;
        pHardwareCounters->m_gpuTimeTopToBottomStartCounterIndex       = CounterGfx8::HWGLGputimeTopToBottomStartIndexGfx8;
        pHardwareCounters->m_gpuTimeTopToBottomEndCounterIndex         = CounterGfx8::HWGLGputimeTopToBottomEndIndexGfx8;
        pHardwareCounters->m_pPaddedCounters                           = CounterGfx8::GLPaddedCounterByGroupGfx8;
        pHardwareCounters->m_paddedCounterCount                        = CounterGfx8::GLPaddedCounterGroupCountGfx8;
        break;

    case GDT_HW_GENERATION_GFX9:
        pHardwareCounters->m_ppCounterGroupArray                       = CounterGfx9::GLCounterGroupArrayGfx9;
        pHardwareCounters->m_pGroups                                   = CounterGfx9::HWGLGroupsGfx9;
        pHardwareCounters->m_groupCount                                = CounterGfx9::HWGLGroupCountGfx9;
        pHardwareCounters->m_pSQCounterGroups                          = CounterGfx9::HWGLSQGroupsGfx9;
        pHardwareCounters->m_sqGroupCount                              = CounterGfx9::HWGLSQGroupCountGfx9;
        pHardwareCounters->m_pIsolatedGroups                           = CounterGfx9::HWGLSQIsolatedGroupsGfx9;
        pHardwareCounters->m_isolatedGroupCount                        = CounterGfx9::HWGLSQIsolatedGroupCountGfx9;
        pHardwareCounters->m_timestampBlockIds                         = CounterGfx9::HWGLTimestampBlockIdsGfx9;
        pHardwareCounters->m_timeCounterIndices                        = CounterGfx9::HWGLTimeCounterIndicesGfx9;
        pHardwareCounters->m_gpuTimeBottomToBottomDurationCounterIndex = CounterGfx9::HWGLGputimeBottomToBottomDurationIndexGfx9;
        pHardwareCounters->m_gpuTimeBottomToBottomStartCounterIndex    = CounterGfx9::HWGLGputimeBottomToBottomStartIndexGfx9;
        pHardwareCounters->m_gpuTimeBottomToBottomEndCounterIndex      = CounterGfx9::HWGLGputimeBottomToBottomEndIndexGfx9;
        pHardwareCounters->m_gpuTimeTopToBottomDurationCounterIndex    = CounterGfx9::HWGLGputimeTopToBottomDurationIndexGfx9;
        pHardwareCounters->m_gpuTimeTopToBottomStartCounterIndex       = CounterGfx9::HWGLGputimeTopToBottomStartIndexGfx9;
        pHardwareCounters->m_gpuTimeTopToBottomEndCounterIndex         = CounterGfx9::HWGLGputimeTopToBottomEndIndexGfx9;
        pHardwareCounters->m_pPaddedCounters                           = CounterGfx9::GLPaddedCounterByGroupGfx9;
        pHardwareCounters->m_paddedCounterCount                        = CounterGfx9::GLPaddedCounterGroupCountGfx9;
        break;

    case GDT_HW_GENERATION_GFX10:
        pHardwareCounters->m_ppCounterGroupArray                       = CounterGfx10::GLCounterGroupArrayGfx10;
        pHardwareCounters->m_pGroups                                   = CounterGfx10::HWGLGroupsGfx10;
        pHardwareCounters->m_groupCount                                = CounterGfx10::HWGLGroupCountGfx10;
        pHardwareCounters->m_pSQCounterGroups                          = CounterGfx10::HWGLSQGroupsGfx10;
        pHardwareCounters->m_sqGroupCount                              = CounterGfx10::HWGLSQGroupCountGfx10;
        pHardwareCounters->m_pIsolatedGroups                           = CounterGfx10::HWGLSQIsolatedGroupsGfx10;
        pHardwareCounters->m_isolatedGroupCount                        = CounterGfx10::HWGLSQIsolatedGroupCountGfx10;
        pHardwareCounters->m_timestampBlockIds                         = CounterGfx10::HWGLTimestampBlockIdsGfx10;
        pHardwareCounters->m_timeCounterIndices                        = CounterGfx10::HWGLTimeCounterIndicesGfx10;
        pHardwareCounters->m_gpuTimeBottomToBottomDurationCounterIndex = CounterGfx10::HWGLGputimeBottomToBottomDurationIndexGfx10;
        pHardwareCounters->m_gpuTimeBottomToBottomStartCounterIndex    = CounterGfx10::HWGLGputimeBottomToBottomStartIndexGfx10;
        pHardwareCounters->m_gpuTimeBottomToBottomEndCounterIndex      = CounterGfx10::HWGLGputimeBottomToBottomEndIndexGfx10;
        pHardwareCounters->m_gpuTimeTopToBottomDurationCounterIndex    = CounterGfx10::HWGLGputimeTopToBottomDurationIndexGfx10;
        pHardwareCounters->m_gpuTimeTopToBottomStartCounterIndex       = CounterGfx10::HWGLGputimeTopToBottomStartIndexGfx10;
        pHardwareCounters->m_gpuTimeTopToBottomEndCounterIndex         = CounterGfx10::HWGLGputimeTopToBottomEndIndexGfx10;
        pHardwareCounters->m_pPaddedCounters                           = CounterGfx10::GLPaddedCounterByGroupGfx10;
        pHardwareCounters->m_paddedCounterCount                        = CounterGfx10::GLPaddedCounterGroupCountGfx10;
        break;

    default:
        GPA_LogError("Unrecognized or unhandled hardware generation.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    // need to count total number of internal counters, since split into groups
    status = GenerateInternalCounters(pHardwareCounters, desiredGeneration);

    if (status != GPA_STATUS_OK)
    {
        GPA_LogError("Unable to generate internal counters.");
        pHardwareCounters->m_currentGroupUsedCounts.clear();
        return status;
    }

    pHardwareCounters->m_countersGenerated = true;

    unsigned int uGroupCount = pHardwareCounters->m_groupCount;
    pHardwareCounters->m_currentGroupUsedCounts.resize(uGroupCount);

    return status;
}

GPA_Status GPA_CounterGeneratorGL::GenerateSoftwareCounters(GDT_HW_GENERATION     desiredGeneration,
                                                            GDT_HW_ASIC_TYPE      asicType,
                                                            gpa_uint8             generateAsicSpecificCounters,
                                                            GPA_SoftwareCounters* pSoftwareCounters)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(asicType);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);
    UNREFERENCED_PARAMETER(pSoftwareCounters);
    GPA_Status retVal = GPA_STATUS_OK;

    return retVal;
}

GPA_Status GPA_CounterGeneratorGL::GenerateHardwareExposedCounters(GDT_HW_GENERATION     desiredGeneration,
                                                                   GDT_HW_ASIC_TYPE      asicType,
                                                                   gpa_uint8             generateAsicSpecificCounters,
                                                                   GPA_HardwareCounters* pHardwareCounters)
{
    UNREFERENCED_PARAMETER(asicType);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);

    if (nullptr == pHardwareCounters)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (pHardwareCounters->m_hardwareExposedCountersGenerated)
    {
        return GPA_STATUS_OK;
    }

    switch (desiredGeneration)
    {
    case GDT_HW_GENERATION_VOLCANICISLAND:
        pHardwareCounters->m_ppHardwareExposedCounter         = CounterGfx8::GLExposedCountersGroupArrayGfx8;
        pHardwareCounters->m_pHardwareExposedCounterGroups    = CounterGfx8::HWGLExposedCountersByGroupGfx8;
        pHardwareCounters->m_hardwareExposedCounterGroupCount = CounterGfx8::HWGLExposedCountersGroupCountGfx8;
        break;

    case GDT_HW_GENERATION_GFX9:
        pHardwareCounters->m_ppHardwareExposedCounter         = CounterGfx9::GLExposedCountersGroupArrayGfx9;
        pHardwareCounters->m_pHardwareExposedCounterGroups    = CounterGfx9::HWGLExposedCountersByGroupGfx9;
        pHardwareCounters->m_hardwareExposedCounterGroupCount = CounterGfx9::HWGLExposedCountersGroupCountGfx9;
        break;

    case GDT_HW_GENERATION_GFX10:
        pHardwareCounters->m_ppHardwareExposedCounter         = CounterGfx10::GLExposedCountersGroupArrayGfx10;
        pHardwareCounters->m_pHardwareExposedCounterGroups    = CounterGfx10::HWGLExposedCountersByGroupGfx10;
        pHardwareCounters->m_hardwareExposedCounterGroupCount = CounterGfx10::HWGLExposedCountersGroupCountGfx10;
        break;

    default:
        GPA_LogError("Unrecognized or unhandled hardware generation.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    pHardwareCounters->m_hardwareExposedCountersGenerated = MapHardwareExposedCounter(pHardwareCounters);
    return pHardwareCounters->m_hardwareExposedCountersGenerated ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}
