//==============================================================================
// Copyright (c) 2016-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for DX11 counter generation for AMD HW
//==============================================================================

#include <d3d11.h>

#ifdef EXTRA_COUNTER_INFO
#include <sstream>
#endif

#include "GPACounterGeneratorDX11.h"
#include "Logging.h"

#include "PublicCounterDefsDX11Gfx8.h"
#include "PublicCounterDefsDX11Gfx9.h"
#include "PublicCounterDefsDX11Gfx10.h"

#include "PublicCounterDefsDX11Gfx8Asics.h"
#include "PublicCounterDefsDX11Gfx9Asics.h"
#include "PublicCounterDefsDX11Gfx10Asics.h"

#include "GPAHWCounterDX11Gfx8.h"
#include "GPAHWCounterDX11Gfx9.h"
#include "GPAHWCounterDX11Gfx10.h"

#include "GPASoftwareCounters.h"

#include "AmdDxCounter.h"
#include "AmdDxExtPerfProfile.h"

#include "GPASwCounterManager.h"
#include "GPACounterGeneratorSchedulerManager.h"

GPA_CounterGeneratorDX11::GPA_CounterGeneratorDX11()
{
    GPA_CounterGeneratorBase::SetAllowedCounters(true, true, true);  //enable all counters

    for (int gen = GDT_HW_GENERATION_FIRST_AMD; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(GPA_API_DIRECTX_11, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

/// Function translates between GPA's block id and the DX11 driver's PE_BLOCK_ID enum
/// The driver gives each block an ID, but ignores the instance. GPA treats each instance as a different
/// block, so we need to translate.
/// \param generation the generation whose block id needs to be calculated
/// \param pGroup the group for which the block id needs to be calculated
/// \return the block id according to the driver
static UINT CalculateBlockIdDX11(GDT_HW_GENERATION generation, GPA_CounterGroupDesc* pGroup)
{
    UINT groupIndex = (UINT)pGroup->m_groupIndex;

    if (GPA_CounterGeneratorDX11Base::IsAMDGPU(generation))
    {
        if (generation == GDT_HW_GENERATION_VOLCANICISLAND)
        {
            return CounterGfx8::HWDX11DriverEnumGfx8[groupIndex];
        }

        if (generation == GDT_HW_GENERATION_GFX9)
        {
            return CounterGfx9::HWDX11DriverEnumGfx9[groupIndex];
        }

        if (generation == GDT_HW_GENERATION_GFX10)
        {
            return CounterGfx10::HWDX11DriverEnumGfx10[groupIndex];
        }

        // don't recognize the specified hardware generation.
        // need to add support or fix a bug.
        assert(generation == GDT_HW_GENERATION_SOUTHERNISLAND);
    }

    return groupIndex;
}

bool GPA_CounterGeneratorDX11::GenerateInternalCounters(GPA_HardwareCounters* pHardwareCounters, GDT_HW_GENERATION generation)
{
    pHardwareCounters->m_counters.clear();

    GPA_HardwareCounterDescExt counter = {};
#if defined(_DEBUG) && defined(AMDT_INTERNAL)
    // Debug builds will generate a file that lists the counter names in a format that can be
    // easily copy/pasted into the GPUPerfAPIUnitTests project
    FILE* pFile = nullptr;
    fopen_s(&pFile, "HardwareCounterNamesDX11.txt", "w");
#endif

    unsigned int globalCounterIndex = 0;

    // for each group, get the group name, number of counters, and max counters (and maybe validate them)
    for (unsigned int g = 0; g < pHardwareCounters->m_groupCount; g++)
    {
        GPA_HardwareCounterDesc* pGroupCounters = pHardwareCounters->m_ppCounterGroupArray[g];
        GPA_CounterGroupDesc     group          = pHardwareCounters->m_pGroups[g];

        // calculate per-block values outside the for loop
        UINT blockId = CalculateBlockIdDX11(generation, &group);

        // only add the number of counters that are supported; but no more than the number that we expect
        const gpa_uint64 numCountersInGroup = pHardwareCounters->m_pGroups[g].m_numCounters;

        for (gpa_uint64 c = 0; c < numCountersInGroup; c++)
        {
            counter.m_groupIndex       = g;
            counter.m_pHardwareCounter = &(pGroupCounters[c]);
            counter.m_groupIdDriver    = blockId;

            if (pHardwareCounters->IsTimestampBlockId(counter.m_groupIndex))
            {
                counter.m_counterIdDriver =
                    AmdCtrEncodeApiCounter((AmdApiCounterId)(globalCounterIndex - pHardwareCounters->GetFirstHardwareTimeCounterIndex()));
            }
            else
            {
                counter.m_counterIdDriver = 0;
            }

#if defined(_DEBUG) && defined(AMDT_INTERNAL)

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

#if defined(_DEBUG) && defined(AMDT_INTERNAL)
    if (nullptr != pFile)
    {
        fclose(pFile);
    }
#endif

    return true;
}

GPA_Status GPA_CounterGeneratorDX11::GeneratePublicCounters(GDT_HW_GENERATION    desiredGeneration,
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

        if (desiredGeneration == GDT_HW_GENERATION_VOLCANICISLAND)
        {
            AutoDefinePublicDerivedCountersDX11Gfx8(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                DX11Gfx8Asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
        }
        else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
        {
            AutoDefinePublicDerivedCountersDX11Gfx9(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                DX11Gfx9Asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
        }
        else if (desiredGeneration == GDT_HW_GENERATION_GFX10)
        {
            AutoDefinePublicDerivedCountersDX11Gfx10(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                DX11Gfx10Asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
        }
    }

    auto internalStatus = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;

#ifdef AMDT_INTERNAL
    internalStatus = GPA_LoadInternalCounters(GPA_API_DIRECTX_11, desiredGeneration, asicType, generateAsicSpecificCounters, pPublicCounters);
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

GPA_Status GPA_CounterGeneratorDX11::GenerateHardwareCounters(GDT_HW_GENERATION     desiredGeneration,
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
        pHardwareCounters->m_ppCounterGroupArray                       = CounterGfx8::DX11CounterGroupArrayGfx8;
        pHardwareCounters->m_pGroups                                   = CounterGfx8::HWDX11GroupsGfx8;
        pHardwareCounters->m_groupCount                                = CounterGfx8::HWDX11GroupCountGfx8;
        pHardwareCounters->m_pSQCounterGroups                          = CounterGfx8::HWDX11SQGroupsGfx8;
        pHardwareCounters->m_sqGroupCount                              = CounterGfx8::HWDX11SQGroupCountGfx8;
        pHardwareCounters->m_timestampBlockIds                         = CounterGfx8::HWDX11TimestampBlockIdsGfx8;
        pHardwareCounters->m_timeCounterIndices                        = CounterGfx8::HWDX11TimeCounterIndicesGfx8;
        pHardwareCounters->m_gpuTimeBottomToBottomDurationCounterIndex = CounterGfx8::HWDX11GputimeBottomToBottomDurationIndexGfx8;
        pHardwareCounters->m_gpuTimeBottomToBottomStartCounterIndex    = CounterGfx8::HWDX11GputimeBottomToBottomStartIndexGfx8;
        pHardwareCounters->m_gpuTimeBottomToBottomEndCounterIndex      = CounterGfx8::HWDX11GputimeBottomToBottomEndIndexGfx8;
        pHardwareCounters->m_gpuTimeTopToBottomDurationCounterIndex    = CounterGfx8::HWDX11GputimeBottomToBottomDurationIndexGfx8;
        pHardwareCounters->m_gpuTimeTopToBottomStartCounterIndex       = CounterGfx8::HWDX11GputimeTopToBottomStartIndexGfx8;
        pHardwareCounters->m_gpuTimeTopToBottomEndCounterIndex         = CounterGfx8::HWDX11GputimeTopToBottomEndIndexGfx8;
        pHardwareCounters->m_pIsolatedGroups                           = CounterGfx8::HWDX11SQIsolatedGroupsGfx8;
        pHardwareCounters->m_isolatedGroupCount                        = CounterGfx8::HWDX11SQIsolatedGroupCountGfx8;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
    {
        pHardwareCounters->m_ppCounterGroupArray                       = CounterGfx9::DX11CounterGroupArrayGfx9;
        pHardwareCounters->m_pGroups                                   = CounterGfx9::HWDX11GroupsGfx9;
        pHardwareCounters->m_groupCount                                = CounterGfx9::HWDX11GroupCountGfx9;
        pHardwareCounters->m_pSQCounterGroups                          = CounterGfx9::HWDX11SQGroupsGfx9;
        pHardwareCounters->m_sqGroupCount                              = CounterGfx9::HWDX11SQGroupCountGfx9;
        pHardwareCounters->m_timestampBlockIds                         = CounterGfx9::HWDX11TimestampBlockIdsGfx9;
        pHardwareCounters->m_timeCounterIndices                        = CounterGfx9::HWDX11TimeCounterIndicesGfx9;
        pHardwareCounters->m_gpuTimeBottomToBottomDurationCounterIndex = CounterGfx9::HWDX11GputimeBottomToBottomDurationIndexGfx9;
        pHardwareCounters->m_gpuTimeBottomToBottomStartCounterIndex    = CounterGfx9::HWDX11GputimeBottomToBottomStartIndexGfx9;
        pHardwareCounters->m_gpuTimeBottomToBottomEndCounterIndex      = CounterGfx9::HWDX11GputimeBottomToBottomEndIndexGfx9;
        pHardwareCounters->m_gpuTimeTopToBottomDurationCounterIndex    = CounterGfx9::HWDX11GputimeBottomToBottomDurationIndexGfx9;
        pHardwareCounters->m_gpuTimeTopToBottomStartCounterIndex       = CounterGfx9::HWDX11GputimeTopToBottomStartIndexGfx9;
        pHardwareCounters->m_gpuTimeTopToBottomEndCounterIndex         = CounterGfx9::HWDX11GputimeTopToBottomEndIndexGfx9;
        pHardwareCounters->m_pIsolatedGroups                           = CounterGfx9::HWDX11SQIsolatedGroupsGfx9;
        pHardwareCounters->m_isolatedGroupCount                        = CounterGfx9::HWDX11SQIsolatedGroupCountGfx9;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX10)
    {
        pHardwareCounters->m_ppCounterGroupArray                       = CounterGfx10::DX11CounterGroupArrayGfx10;
        pHardwareCounters->m_pGroups                                   = CounterGfx10::HWDX11GroupsGfx10;
        pHardwareCounters->m_groupCount                                = CounterGfx10::HWDX11GroupCountGfx10;
        pHardwareCounters->m_pSQCounterGroups                          = CounterGfx10::HWDX11SQGroupsGfx10;
        pHardwareCounters->m_sqGroupCount                              = CounterGfx10::HWDX11SQGroupCountGfx10;
        pHardwareCounters->m_timestampBlockIds                         = CounterGfx10::HWDX11TimestampBlockIdsGfx10;
        pHardwareCounters->m_timeCounterIndices                        = CounterGfx10::HWDX11TimeCounterIndicesGfx10;
        pHardwareCounters->m_gpuTimeBottomToBottomDurationCounterIndex = CounterGfx10::HWDX11GputimeBottomToBottomDurationIndexGfx10;
        pHardwareCounters->m_gpuTimeBottomToBottomStartCounterIndex    = CounterGfx10::HWDX11GputimeBottomToBottomStartIndexGfx10;
        pHardwareCounters->m_gpuTimeBottomToBottomEndCounterIndex      = CounterGfx10::HWDX11GputimeBottomToBottomEndIndexGfx10;
        pHardwareCounters->m_gpuTimeTopToBottomDurationCounterIndex    = CounterGfx10::HWDX11GputimeBottomToBottomDurationIndexGfx10;
        pHardwareCounters->m_gpuTimeTopToBottomStartCounterIndex       = CounterGfx10::HWDX11GputimeTopToBottomStartIndexGfx10;
        pHardwareCounters->m_gpuTimeTopToBottomEndCounterIndex         = CounterGfx10::HWDX11GputimeTopToBottomEndIndexGfx10;
        pHardwareCounters->m_pIsolatedGroups                           = CounterGfx10::HWDX11SQIsolatedGroupsGfx10;
        pHardwareCounters->m_isolatedGroupCount                        = CounterGfx10::HWDX11SQIsolatedGroupCountGfx10;
    }
    else
    {
        GPA_LogError("Unrecognized or unhandled hardware generation.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    // need to count total number of internal counters, since split into groups
    if (!GenerateInternalCounters(pHardwareCounters, desiredGeneration))
    {
        GPA_LogError("Unable to generate internal or whitelist counters.");
        pHardwareCounters->m_currentGroupUsedCounts.clear();
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
    }

    pHardwareCounters->m_countersGenerated = true;

    unsigned int uGroupCount = pHardwareCounters->m_groupCount;
    pHardwareCounters->m_currentGroupUsedCounts.resize(uGroupCount);

    return GPA_STATUS_OK;
}

GPA_Status GPA_CounterGeneratorDX11::GenerateHardwareExposedCounters(GDT_HW_GENERATION     desiredGeneration,
                                                                     GDT_HW_ASIC_TYPE      asicType,
                                                                     gpa_uint8             generateAsicSpecificCounters,
                                                                     GPA_HardwareCounters* pHardwareCounters)
{
    UNREFERENCED_PARAMETER(asicType);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);

    if (pHardwareCounters->m_hardwareExposedCountersGenerated)
    {
        return GPA_STATUS_OK;
    }

    if (desiredGeneration == GDT_HW_GENERATION_VOLCANICISLAND)
    {
        pHardwareCounters->m_ppHardwareExposedCounter         = CounterGfx8::DX11ExposedCountersGroupArrayGfx8;
        pHardwareCounters->m_pHardwareExposedCounterGroups    = CounterGfx8::HWDX11ExposedCountersByGroupGfx8;
        pHardwareCounters->m_hardwareExposedCounterGroupCount = CounterGfx8::HWDX11ExposedCountersGroupCountGfx8;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
    {
        pHardwareCounters->m_ppHardwareExposedCounter         = CounterGfx9::DX11ExposedCountersGroupArrayGfx9;
        pHardwareCounters->m_pHardwareExposedCounterGroups    = CounterGfx9::HWDX11ExposedCountersByGroupGfx9;
        pHardwareCounters->m_hardwareExposedCounterGroupCount = CounterGfx9::HWDX11ExposedCountersGroupCountGfx9;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX10)
    {
        pHardwareCounters->m_ppHardwareExposedCounter         = CounterGfx10::DX11ExposedCountersGroupArrayGfx10;
        pHardwareCounters->m_pHardwareExposedCounterGroups    = CounterGfx10::HWDX11ExposedCountersByGroupGfx10;
        pHardwareCounters->m_hardwareExposedCounterGroupCount = CounterGfx10::HWDX11ExposedCountersGroupCountGfx10;
    }
    else
    {
        GPA_LogError("Unrecognized or unhandled hardware generation.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    pHardwareCounters->m_hardwareExposedCountersGenerated = MapHardwareExposedCounter(pHardwareCounters);
    return pHardwareCounters->m_hardwareExposedCountersGenerated ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}
