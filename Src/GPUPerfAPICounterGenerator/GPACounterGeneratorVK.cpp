//==============================================================================
// Copyright (c) 2015-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for VK counter generation
//==============================================================================
/// \author GPU Developer Tools
/// \brief GPA_CounterGeneratorVK implementation

#include "GPACounterGeneratorVK.h"
#include "GPACounterGeneratorSchedulerManager.h"

#include "InternalCountersVKGfx7.h"
#include "InternalCountersVKGfx8.h"
#include "InternalCountersVKGfx9.h"

#include "PublicCounterDefsVKGfx7.h"
#include "PublicCounterDefsVKGfx8.h"
#include "PublicCounterDefsVKGfx9.h"

bool GPA_CounterGeneratorVK::IsAMDGPU(GDT_HW_GENERATION generation)
{
    return generation >= GDT_HW_GENERATION_FIRST_AMD && generation < GDT_HW_GENERATION_LAST;
}

UINT GPA_CounterGeneratorVK::CalculateBlockIdVK(GDT_HW_GENERATION generation, GPA_CounterGroupDesc* pGroup)
{
    UINT groupIndex = static_cast<UINT>(pGroup->m_groupIndex);

    if (IsAMDGPU(generation))
    {
        if (generation == GDT_HW_GENERATION_SEAISLAND)
        {
            return static_cast<UINT>(HWVKDriverEnumGfx7[groupIndex]);
        }
        else if (generation == GDT_HW_GENERATION_VOLCANICISLAND)
        {
            return static_cast<UINT>(HWVKDriverEnumGfx8[groupIndex]);
        }
        else if (generation == GDT_HW_GENERATION_GFX9)
        {
            return static_cast<UINT>(HWVKDriverEnumGfx9[groupIndex]);
        }
        else
        {
            // don't recognize the specified hardware generation.
            // need to add support or fix a bug.
            assert(generation == GDT_HW_GENERATION_SEAISLAND);
        }
    }

    return groupIndex;
}

GPA_CounterGeneratorVK::GPA_CounterGeneratorVK():
    GPA_CounterGeneratorVKBase()
{
    SetAllowedCounters(true, true, true); //enable public, hw, and sw counters

    for (int gen = GDT_HW_GENERATION_SOUTHERNISLAND; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(GPA_API_VULKAN, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GPA_CounterGeneratorVK::~GPA_CounterGeneratorVK()
{
}

GPA_Status GPA_CounterGeneratorVK::GeneratePublicCounters(
    GDT_HW_GENERATION desiredGeneration, GPA_PublicCounters* pPublicCounters)
{
    GPA_Status status = GPA_STATUS_OK;

    if (nullptr == pPublicCounters)
    {
        status = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        pPublicCounters->Clear();

        switch (desiredGeneration)
        {
            case GDT_HW_GENERATION_SEAISLAND:
                AutoDefinePublicCountersVKGfx7(*pPublicCounters);
                pPublicCounters->m_countersGenerated = true;
                break;

            case GDT_HW_GENERATION_VOLCANICISLAND:
                AutoDefinePublicCountersVKGfx8(*pPublicCounters);
                pPublicCounters->m_countersGenerated = true;
                break;

            case GDT_HW_GENERATION_GFX9:
                AutoDefinePublicCountersVKGfx9(*pPublicCounters);
                pPublicCounters->m_countersGenerated = true;
                break;

            default:
                status = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
                break;
        }
    }

    return status;
}

bool GPA_CounterGeneratorVK::GenerateInternalCounters(GPA_HardwareCounters* pHardwareCounters, GDT_HW_GENERATION generation)
{
    pHardwareCounters->m_counters.clear();

    GPA_HardwareCounterDescExt counter;
#if defined(_DEBUG) && defined(_WIN32) && defined(AMDT_INTERNAL)
    // Debug builds will generate a file that lists the counter names in a format that can be
    // easily copy/pasted into the GPUPerfAPIUnitTests project
    FILE* pFile = nullptr;
    fopen_s(&pFile, "HardwareCounterNamesVK.txt", "w");
#endif

    unsigned int globalCounterIndex = 0;

    // for each group, get the group name, number of counters, and max counters (and maybe validate them)
    for (unsigned int g = 0; g < pHardwareCounters->m_groupCount; g++)
    {
        GPA_HardwareCounterDesc* pGroupCounters = pHardwareCounters->m_ppCounterGroupArray[g];
        GPA_CounterGroupDesc group = pHardwareCounters->m_pGroups[g];

        if (g == pHardwareCounters->m_gpuTimestampIndex)
        {
            pHardwareCounters->m_gpuTimestampTopCounterIndex = static_cast<gpa_uint32>(pHardwareCounters->m_counters.size());
        }
        else if (g == pHardwareCounters->m_gpuTimeIndex)
        {
            pHardwareCounters->m_gpuTimeBottomToBottomCounterIndex = static_cast<gpa_uint32>(pHardwareCounters->m_counters.size());
            pHardwareCounters->m_gpuTimeTopToBottomCounterIndex = static_cast<gpa_uint32>(pHardwareCounters->m_counters.size()) + 1;
        }

        // calculate per-block values outside the for loop
        UINT blockId = CalculateBlockIdVK(generation, &group);

        // only add the number of counters that are supported; but no more than the number that we expect
        const gpa_uint64 numCountersInGroup = pHardwareCounters->m_pGroups[g].m_numCounters;

        for (int c = 0; c < numCountersInGroup; c++)
        {
            counter.m_groupIndex = g;
            counter.m_pHardwareCounter = &(pGroupCounters[c]);
            counter.m_groupIdDriver = blockId;

#if defined(_DEBUG) && defined(_WIN32) && defined(AMDT_INTERNAL)

            if (nullptr != pFile)
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
            ++globalCounterIndex;
        }
    }

#if defined(_DEBUG) && defined(_WIN32) && defined(AMDT_INTERNAL)

    if (nullptr != pFile)
    {
        fclose(pFile);
    }

#endif

    pHardwareCounters->m_countersGenerated = true;

    return true;
}

GPA_Status GPA_CounterGeneratorVK::GenerateHardwareCounters(
    GDT_HW_GENERATION desiredGeneration, GPA_HardwareCounters* pHardwareCounters)
{
    GPA_Status status = GPA_STATUS_OK;

    if (nullptr == pHardwareCounters)
    {
        status = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        pHardwareCounters->Clear();

        if (true == pHardwareCounters->m_countersGenerated) //only generate counters once to improve performance
        {
            return GPA_STATUS_OK;
        }

        pHardwareCounters->Clear();

        if (desiredGeneration == GDT_HW_GENERATION_SEAISLAND)
        {
            pHardwareCounters->m_ppCounterGroupArray = VKCounterGroupArrayGfx7;
            pHardwareCounters->m_pGroups = HWVKGroupsGfx7;
            pHardwareCounters->m_groupCount = HWVKGroupCountGfx7;
            pHardwareCounters->m_pSQCounterGroups = HWVKSQGroupsGfx7;
            pHardwareCounters->m_sqGroupCount = HWVKSQGroupCountGfx7;
            pHardwareCounters->m_gpuTimestampIndex = static_cast<unsigned int>(-1);// HWVKGPUTimeStampIndexGfx7;
            pHardwareCounters->m_gpuTimeIndex = HWVKGPUTimeIndexGfx7;
            pHardwareCounters->m_pIsolatedGroups = HWVKSQIsolatedGroupsGfx7;
            pHardwareCounters->m_isolatedGroupCount = HWVKSQIsolatedGroupCountGfx7;
        }
        else if (desiredGeneration == GDT_HW_GENERATION_VOLCANICISLAND)
        {
            pHardwareCounters->m_ppCounterGroupArray = VKCounterGroupArrayGfx8;
            pHardwareCounters->m_pGroups = HWVKGroupsGfx8;
            pHardwareCounters->m_groupCount = HWVKGroupCountGfx8;
            pHardwareCounters->m_pSQCounterGroups = HWVKSQGroupsGfx8;
            pHardwareCounters->m_sqGroupCount = HWVKSQGroupCountGfx8;
            pHardwareCounters->m_gpuTimestampIndex = static_cast<unsigned int>(-1);// HWVKGPUTimeStampIndexGfx8;
            pHardwareCounters->m_gpuTimeIndex = HWVKGPUTimeIndexGfx8;
            pHardwareCounters->m_pIsolatedGroups = HWVKSQIsolatedGroupsGfx8;
            pHardwareCounters->m_isolatedGroupCount = HWVKSQIsolatedGroupCountGfx8;
        }
        else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
        {
            pHardwareCounters->m_ppCounterGroupArray = VKCounterGroupArrayGfx9;
            pHardwareCounters->m_pGroups = HWVKGroupsGfx9;
            pHardwareCounters->m_groupCount = HWVKGroupCountGfx9;
            pHardwareCounters->m_pSQCounterGroups = HWVKSQGroupsGfx9;
            pHardwareCounters->m_sqGroupCount = HWVKSQGroupCountGfx9;
            pHardwareCounters->m_gpuTimestampIndex = static_cast<unsigned int>(-1);// HWVKGPUTimeStampIndexGfx9;
            pHardwareCounters->m_gpuTimeIndex = HWVKGPUTimeIndexGfx9;
            pHardwareCounters->m_pIsolatedGroups = HWVKSQIsolatedGroupsGfx9;
            pHardwareCounters->m_isolatedGroupCount = HWVKSQIsolatedGroupCountGfx9;
        }
        else
        {
            GPA_LogError("Unrecognized or unhandled hardware generation.");
            return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
        }
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

    return status;
}

