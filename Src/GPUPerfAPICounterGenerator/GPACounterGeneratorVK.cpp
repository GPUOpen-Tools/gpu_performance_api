//==============================================================================
// Copyright (c) 2015-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for VK counter generation
//==============================================================================

#include "GPACounterGeneratorVK.h"
#include "GPACounterGeneratorSchedulerManager.h"

#include "GPAHWCounterVKGfx8.h"
#include "GPAHWCounterVKGfx9.h"
#include "GPAHWCounterVKGfx10.h"

#include "PublicCounterDefsVKGfx8.h"
#include "PublicCounterDefsVKGfx9.h"
#include "PublicCounterDefsVKGfx10.h"

#include "PublicCounterDefsVKGfx8Asics.h"
#include "PublicCounterDefsVKGfx9Asics.h"
#include "PublicCounterDefsVKGfx10Asics.h"

bool GPA_CounterGeneratorVK::IsAMDGPU(GDT_HW_GENERATION generation)
{
    return generation >= GDT_HW_GENERATION_FIRST_AMD && generation < GDT_HW_GENERATION_LAST;
}

UINT GPA_CounterGeneratorVK::CalculateBlockIdVK(GDT_HW_GENERATION generation, GPA_CounterGroupDesc* pGroup)
{
    UINT groupIndex = static_cast<UINT>(pGroup->m_groupIndex);

    if (IsAMDGPU(generation))
    {
        if (generation == GDT_HW_GENERATION_VOLCANICISLAND)
        {
            return static_cast<UINT>(CounterGfx8::HWVKDriverEnumGfx8[groupIndex]);
        }

        if (generation == GDT_HW_GENERATION_GFX9)
        {
            return static_cast<UINT>(CounterGfx9::HWVKDriverEnumGfx9[groupIndex]);
        }

        if (generation == GDT_HW_GENERATION_GFX10)
        {
            return static_cast<UINT>(CounterGfx10::HWVKDriverEnumGfx10[groupIndex]);
        }

        // don't recognize the specified hardware generation.
        // need to add support or fix a bug.
        assert(generation == GDT_HW_GENERATION_SEAISLAND);
    }

    return groupIndex;
}

GPA_CounterGeneratorVK::GPA_CounterGeneratorVK()
{
    GPA_CounterGeneratorBase::SetAllowedCounters(true, true, true);  //enable public, hw, and sw counters

    for (int gen = GDT_HW_GENERATION_SOUTHERNISLAND; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(GPA_API_VULKAN, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GPA_Status GPA_CounterGeneratorVK::GeneratePublicCounters(GDT_HW_GENERATION    desiredGeneration,
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
            AutoDefinePublicDerivedCountersVKGfx8(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                VKGfx8Asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
        }
        break;

        case GDT_HW_GENERATION_GFX9:
        {
            AutoDefinePublicDerivedCountersVKGfx9(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                VKGfx9Asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
        }
        break;

        case GDT_HW_GENERATION_GFX10:
        {
            AutoDefinePublicDerivedCountersVKGfx10(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                VKGfx10Asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
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

bool GPA_CounterGeneratorVK::GenerateInternalCounters(GPA_HardwareCounters* pHardwareCounters, GDT_HW_GENERATION generation)
{
    pHardwareCounters->m_counters.clear();
    GPA_HardwareCounterDescExt counter = {};

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
        GPA_CounterGroupDesc     group          = pHardwareCounters->m_pGroups[g];

        // calculate per-block values outside the for loop
        UINT blockId = CalculateBlockIdVK(generation, &group);

        // only add the number of counters that are supported; but no more than the number that we expect
        const gpa_uint64 numCountersInGroup = pHardwareCounters->m_pGroups[g].m_numCounters;

        for (gpa_uint64 c = 0; c < numCountersInGroup; c++)
        {
            counter.m_groupIndex       = g;
            counter.m_pHardwareCounter = &(pGroupCounters[c]);
            counter.m_groupIdDriver    = blockId;

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
            ++globalCounterIndex;
        }
    }

#if defined(_DEBUG) && defined(_WIN32) && defined(AMDT_INTERNAL)
    if (nullptr != pFile)
    {
        fclose(pFile);
    }
#endif

    return true;
}

GPA_Status GPA_CounterGeneratorVK::GenerateHardwareCounters(GDT_HW_GENERATION     desiredGeneration,
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

    if (pHardwareCounters->m_countersGenerated)  //only generate counters once to improve performance
    {
        return GPA_STATUS_OK;
    }

    pHardwareCounters->Clear();

    if (desiredGeneration == GDT_HW_GENERATION_VOLCANICISLAND)
    {
        pHardwareCounters->m_ppCounterGroupArray                       = CounterGfx8::VKCounterGroupArrayGfx8;
        pHardwareCounters->m_pGroups                                   = CounterGfx8::HWVKGroupsGfx8;
        pHardwareCounters->m_groupCount                                = CounterGfx8::HWVKGroupCountGfx8;
        pHardwareCounters->m_pSQCounterGroups                          = CounterGfx8::HWVKSQGroupsGfx8;
        pHardwareCounters->m_sqGroupCount                              = CounterGfx8::HWVKSQGroupCountGfx8;
        pHardwareCounters->m_timestampBlockIds                         = CounterGfx8::HWVKTimestampBlockIdsGfx8;
        pHardwareCounters->m_timeCounterIndices                        = CounterGfx8::HWVKTimeCounterIndicesGfx8;
        pHardwareCounters->m_gpuTimeBottomToBottomDurationCounterIndex = CounterGfx8::HWVKGputimeBottomToBottomDurationIndexGfx8;
        pHardwareCounters->m_gpuTimeBottomToBottomStartCounterIndex    = CounterGfx8::HWVKGputimeBottomToBottomStartIndexGfx8;
        pHardwareCounters->m_gpuTimeBottomToBottomEndCounterIndex      = CounterGfx8::HWVKGputimeBottomToBottomEndIndexGfx8;
        pHardwareCounters->m_gpuTimeTopToBottomDurationCounterIndex    = CounterGfx8::HWVKGputimeTopToBottomDurationIndexGfx8;
        pHardwareCounters->m_gpuTimeTopToBottomStartCounterIndex       = CounterGfx8::HWVKGputimeTopToBottomStartIndexGfx8;
        pHardwareCounters->m_gpuTimeTopToBottomEndCounterIndex         = CounterGfx8::HWVKGputimeTopToBottomEndIndexGfx8;
        pHardwareCounters->m_pIsolatedGroups                           = CounterGfx8::HWVKSQIsolatedGroupsGfx8;
        pHardwareCounters->m_isolatedGroupCount                        = CounterGfx8::HWVKSQIsolatedGroupCountGfx8;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
    {
        pHardwareCounters->m_ppCounterGroupArray                       = CounterGfx9::VKCounterGroupArrayGfx9;
        pHardwareCounters->m_pGroups                                   = CounterGfx9::HWVKGroupsGfx9;
        pHardwareCounters->m_groupCount                                = CounterGfx9::HWVKGroupCountGfx9;
        pHardwareCounters->m_pSQCounterGroups                          = CounterGfx9::HWVKSQGroupsGfx9;
        pHardwareCounters->m_sqGroupCount                              = CounterGfx9::HWVKSQGroupCountGfx9;
        pHardwareCounters->m_timestampBlockIds                         = CounterGfx9::HWVKTimestampBlockIdsGfx9;
        pHardwareCounters->m_timeCounterIndices                        = CounterGfx9::HWVKTimeCounterIndicesGfx9;
        pHardwareCounters->m_gpuTimeBottomToBottomDurationCounterIndex = CounterGfx9::HWVKGputimeBottomToBottomDurationIndexGfx9;
        pHardwareCounters->m_gpuTimeBottomToBottomStartCounterIndex    = CounterGfx9::HWVKGputimeBottomToBottomStartIndexGfx9;
        pHardwareCounters->m_gpuTimeBottomToBottomEndCounterIndex      = CounterGfx9::HWVKGputimeBottomToBottomEndIndexGfx9;
        pHardwareCounters->m_gpuTimeTopToBottomDurationCounterIndex    = CounterGfx9::HWVKGputimeTopToBottomDurationIndexGfx9;
        pHardwareCounters->m_gpuTimeTopToBottomStartCounterIndex       = CounterGfx9::HWVKGputimeTopToBottomStartIndexGfx9;
        pHardwareCounters->m_gpuTimeTopToBottomEndCounterIndex         = CounterGfx9::HWVKGputimeTopToBottomEndIndexGfx9;
        pHardwareCounters->m_pIsolatedGroups                           = CounterGfx9::HWVKSQIsolatedGroupsGfx9;
        pHardwareCounters->m_isolatedGroupCount                        = CounterGfx9::HWVKSQIsolatedGroupCountGfx9;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX10)
    {
        pHardwareCounters->m_ppCounterGroupArray                       = CounterGfx10::VKCounterGroupArrayGfx10;
        pHardwareCounters->m_pGroups                                   = CounterGfx10::HWVKGroupsGfx10;
        pHardwareCounters->m_groupCount                                = CounterGfx10::HWVKGroupCountGfx10;
        pHardwareCounters->m_pSQCounterGroups                          = CounterGfx10::HWVKSQGroupsGfx10;
        pHardwareCounters->m_sqGroupCount                              = CounterGfx10::HWVKSQGroupCountGfx10;
        pHardwareCounters->m_timestampBlockIds                         = CounterGfx10::HWVKTimestampBlockIdsGfx10;
        pHardwareCounters->m_timeCounterIndices                        = CounterGfx10::HWVKTimeCounterIndicesGfx10;
        pHardwareCounters->m_gpuTimeBottomToBottomDurationCounterIndex = CounterGfx10::HWVKGputimeBottomToBottomDurationIndexGfx10;
        pHardwareCounters->m_gpuTimeBottomToBottomStartCounterIndex    = CounterGfx10::HWVKGputimeBottomToBottomStartIndexGfx10;
        pHardwareCounters->m_gpuTimeBottomToBottomEndCounterIndex      = CounterGfx10::HWVKGputimeBottomToBottomEndIndexGfx10;
        pHardwareCounters->m_gpuTimeTopToBottomDurationCounterIndex    = CounterGfx10::HWVKGputimeTopToBottomDurationIndexGfx10;
        pHardwareCounters->m_gpuTimeTopToBottomStartCounterIndex       = CounterGfx10::HWVKGputimeTopToBottomStartIndexGfx10;
        pHardwareCounters->m_gpuTimeTopToBottomEndCounterIndex         = CounterGfx10::HWVKGputimeTopToBottomEndIndexGfx10;
        pHardwareCounters->m_pIsolatedGroups                           = CounterGfx10::HWVKSQIsolatedGroupsGfx10;
        pHardwareCounters->m_isolatedGroupCount                        = CounterGfx10::HWVKSQIsolatedGroupCountGfx10;
    }
    else
    {
        GPA_LogError("Unrecognized or unhandled hardware generation.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    // need to count total number of internal counters, since split into groups
    if (!GenerateInternalCounters(pHardwareCounters, desiredGeneration))
    {
        GPA_LogError("Unable to generate internal counters.");
        pHardwareCounters->m_currentGroupUsedCounts.clear();
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
    }

    pHardwareCounters->m_countersGenerated = true;

    unsigned int uGroupCount = pHardwareCounters->m_groupCount;
    pHardwareCounters->m_currentGroupUsedCounts.resize(uGroupCount);

    return GPA_STATUS_OK;
}

GPA_Status GPA_CounterGeneratorVK::GenerateHardwareExposedCounters(GDT_HW_GENERATION     desiredGeneration,
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

    if (desiredGeneration == GDT_HW_GENERATION_VOLCANICISLAND)
    {
        pHardwareCounters->m_ppHardwareExposedCounter         = CounterGfx8::VKExposedCountersGroupArrayGfx8;
        pHardwareCounters->m_pHardwareExposedCounterGroups    = CounterGfx8::HWVKExposedCountersByGroupGfx8;
        pHardwareCounters->m_hardwareExposedCounterGroupCount = CounterGfx8::HWVKExposedCountersGroupCountGfx8;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
    {
        pHardwareCounters->m_ppHardwareExposedCounter         = CounterGfx9::VKExposedCountersGroupArrayGfx9;
        pHardwareCounters->m_pHardwareExposedCounterGroups    = CounterGfx9::HWVKExposedCountersByGroupGfx9;
        pHardwareCounters->m_hardwareExposedCounterGroupCount = CounterGfx9::HWVKExposedCountersGroupCountGfx9;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX10)
    {
        pHardwareCounters->m_ppHardwareExposedCounter         = CounterGfx10::VKExposedCountersGroupArrayGfx10;
        pHardwareCounters->m_pHardwareExposedCounterGroups    = CounterGfx10::HWVKExposedCountersByGroupGfx10;
        pHardwareCounters->m_hardwareExposedCounterGroupCount = CounterGfx10::HWVKExposedCountersGroupCountGfx10;
    }
    else
    {
        GPA_LogError("Unrecognized or unhandled hardware generation.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    pHardwareCounters->m_hardwareExposedCountersGenerated = MapHardwareExposedCounter(pHardwareCounters);
    return pHardwareCounters->m_hardwareExposedCountersGenerated ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}
