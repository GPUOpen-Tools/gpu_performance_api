//==============================================================================
// Copyright (c) 2015-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for DX12 counter generation
//==============================================================================

#include "GPACounterGeneratorDX12.h"
#include "GPACounterGeneratorSchedulerManager.h"

#include "GPAHWCounterDX12Gfx8.h"
#include "GPAHWCounterDX12Gfx9.h"
#include "GPAHWCounterDX12Gfx10.h"

#include "PublicCounterDefsDX12Gfx8.h"
#include "PublicCounterDefsDX12Gfx9.h"
#include "PublicCounterDefsDX12Gfx10.h"

#include "PublicCounterDefsDX12Gfx8Asics.h"
#include "PublicCounterDefsDX12Gfx9Asics.h"
#include "PublicCounterDefsDX12Gfx10Asics.h"

bool GPA_CounterGeneratorDX12::IsAMDGPU(GDT_HW_GENERATION generation)
{
    return generation >= GDT_HW_GENERATION_FIRST_AMD && generation < GDT_HW_GENERATION_LAST;
}

/// Logic inside this function is based on the AmdExtGpuBlock enum in AmdExtGpaInterface in DXCP driver.
/// The driver gives each block an ID, but ignores the instance. GPA treats each instance as a different
/// block, so we need to translate.
/// \param generation the generation whose block id needs to be calculated
/// \param pGroup the group for which the block id needs to be calculated
/// \return the block id according to the driver
UINT GPA_CounterGeneratorDX12::CalculateBlockIdDX12(GDT_HW_GENERATION generation, const GPA_CounterGroupDesc* pGroup)
{
    UINT groupIndex = static_cast<UINT>(pGroup->m_groupIndex);

    if (IsAMDGPU(generation))
    {
        if (generation == GDT_HW_GENERATION_VOLCANICISLAND)
        {
            return static_cast<UINT>(CounterGfx8::HWDX12DriverEnumGfx8[groupIndex]);
        }

        if (generation == GDT_HW_GENERATION_GFX9)
        {
            return static_cast<UINT>(CounterGfx9::HWDX12DriverEnumGfx9[groupIndex]);
        }

        if (generation == GDT_HW_GENERATION_GFX10)
        {
            return static_cast<UINT>(CounterGfx10::HWDX12DriverEnumGfx10[groupIndex]);
        }

        // don't recognize the specified hardware generation.
        // need to add support or fix a bug.
        assert(generation == GDT_HW_GENERATION_SOUTHERNISLAND);
    }

    return groupIndex;
}

GPA_CounterGeneratorDX12::GPA_CounterGeneratorDX12()
{
    GPA_CounterGeneratorBase::SetAllowedCounters(true, true, true);  //enable public, hw, and sw counters

    for (int gen = GDT_HW_GENERATION_SOUTHERNISLAND; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(GPA_API_DIRECTX_12, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GPA_Status GPA_CounterGeneratorDX12::GeneratePublicCounters(GDT_HW_GENERATION    desiredGeneration,
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
            AutoDefinePublicDerivedCountersDX12Gfx8(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                DX12Gfx8Asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
        }
        break;

        case GDT_HW_GENERATION_GFX9:
        {
            AutoDefinePublicDerivedCountersDX12Gfx9(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                DX12Gfx9Asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
        }
        break;

        case GDT_HW_GENERATION_GFX10:
        {
            AutoDefinePublicDerivedCountersDX12Gfx10(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                DX12Gfx10Asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
        }
        break;

        default:
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

bool GPA_CounterGeneratorDX12::GenerateInternalCounters(GPA_HardwareCounters* pHardwareCounters, GDT_HW_GENERATION generation)
{
    pHardwareCounters->m_counters.clear();
    GPA_HardwareCounterDescExt counter = {};

#if defined(_DEBUG) && defined(AMDT_INTERNAL)
    // Debug builds will generate a file that lists the counter names in a format that can be
    // easily copy/pasted into the GPUPerfAPIUnitTests project
    FILE* pFile = nullptr;
    fopen_s(&pFile, "HardwareCounterNamesDX12.txt", "w");
#endif

    unsigned int globalCounterIndex = 0;

    // for each group, get the group name, number of counters, and max counters (and maybe validate them)
    for (unsigned int g = 0; g < pHardwareCounters->m_groupCount; g++)
    {
        GPA_HardwareCounterDesc* pGroupCounters = pHardwareCounters->m_ppCounterGroupArray[g];
        GPA_CounterGroupDesc     group          = pHardwareCounters->m_pGroups[g];

        // calculate per-block values outside the for loop
        UINT blockId = CalculateBlockIdDX12(generation, &group);

        // only add the number of counters that are supported; but no more than the number that we expect
        const gpa_uint64 numCountersInGroup = pHardwareCounters->m_pGroups[g].m_numCounters;

        for (gpa_uint64 c = 0; c < numCountersInGroup; c++)
        {
            counter.m_groupIndex       = g;
            counter.m_pHardwareCounter = &(pGroupCounters[c]);
            counter.m_groupIdDriver    = blockId;

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

GPA_Status GPA_CounterGeneratorDX12::GenerateHardwareCounters(GDT_HW_GENERATION     desiredGeneration,
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

    if (pHardwareCounters->m_countersGenerated)
    {
        return GPA_STATUS_OK;
    }

    pHardwareCounters->Clear();

    if (desiredGeneration == GDT_HW_GENERATION_VOLCANICISLAND)
    {
        pHardwareCounters->m_ppCounterGroupArray                       = CounterGfx8::DX12CounterGroupArrayGfx8;
        pHardwareCounters->m_pGroups                                   = CounterGfx8::HWDX12GroupsGfx8;
        pHardwareCounters->m_groupCount                                = CounterGfx8::HWDX12GroupCountGfx8;
        pHardwareCounters->m_pSQCounterGroups                          = CounterGfx8::HWDX12SQGroupsGfx8;
        pHardwareCounters->m_sqGroupCount                              = CounterGfx8::HWDX12SQGroupCountGfx8;
        pHardwareCounters->m_timestampBlockIds                         = CounterGfx8::HWDX12TimestampBlockIdsGfx8;
        pHardwareCounters->m_timeCounterIndices                        = CounterGfx8::HWDX12TimeCounterIndicesGfx8;
        pHardwareCounters->m_gpuTimeBottomToBottomDurationCounterIndex = CounterGfx8::HWDX12GputimeBottomToBottomDurationIndexGfx8;
        pHardwareCounters->m_gpuTimeBottomToBottomStartCounterIndex    = CounterGfx8::HWDX12GputimeBottomToBottomStartIndexGfx8;
        pHardwareCounters->m_gpuTimeBottomToBottomEndCounterIndex      = CounterGfx8::HWDX12GputimeBottomToBottomEndIndexGfx8;
        pHardwareCounters->m_gpuTimeTopToBottomDurationCounterIndex    = CounterGfx8::HWDX12GputimeTopToBottomDurationIndexGfx8;
        pHardwareCounters->m_gpuTimeTopToBottomStartCounterIndex       = CounterGfx8::HWDX12GputimeTopToBottomStartIndexGfx8;
        pHardwareCounters->m_gpuTimeTopToBottomEndCounterIndex         = CounterGfx8::HWDX12GputimeTopToBottomEndIndexGfx8;
        pHardwareCounters->m_pIsolatedGroups                           = CounterGfx8::HWDX12SQIsolatedGroupsGfx8;
        pHardwareCounters->m_isolatedGroupCount                        = CounterGfx8::HWDX12SQIsolatedGroupCountGfx8;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
    {
        pHardwareCounters->m_ppCounterGroupArray                       = CounterGfx9::DX12CounterGroupArrayGfx9;
        pHardwareCounters->m_pGroups                                   = CounterGfx9::HWDX12GroupsGfx9;
        pHardwareCounters->m_groupCount                                = CounterGfx9::HWDX12GroupCountGfx9;
        pHardwareCounters->m_pSQCounterGroups                          = CounterGfx9::HWDX12SQGroupsGfx9;
        pHardwareCounters->m_sqGroupCount                              = CounterGfx9::HWDX12SQGroupCountGfx9;
        pHardwareCounters->m_timestampBlockIds                         = CounterGfx9::HWDX12TimestampBlockIdsGfx9;
        pHardwareCounters->m_timeCounterIndices                        = CounterGfx9::HWDX12TimeCounterIndicesGfx9;
        pHardwareCounters->m_gpuTimeBottomToBottomDurationCounterIndex = CounterGfx9::HWDX12GputimeBottomToBottomDurationIndexGfx9;
        pHardwareCounters->m_gpuTimeBottomToBottomStartCounterIndex    = CounterGfx9::HWDX12GputimeBottomToBottomStartIndexGfx9;
        pHardwareCounters->m_gpuTimeBottomToBottomEndCounterIndex      = CounterGfx9::HWDX12GputimeBottomToBottomEndIndexGfx9;
        pHardwareCounters->m_gpuTimeTopToBottomDurationCounterIndex    = CounterGfx9::HWDX12GputimeTopToBottomDurationIndexGfx9;
        pHardwareCounters->m_gpuTimeTopToBottomStartCounterIndex       = CounterGfx9::HWDX12GputimeTopToBottomStartIndexGfx9;
        pHardwareCounters->m_gpuTimeTopToBottomEndCounterIndex         = CounterGfx9::HWDX12GputimeTopToBottomEndIndexGfx9;
        pHardwareCounters->m_pIsolatedGroups                           = CounterGfx9::HWDX12SQIsolatedGroupsGfx9;
        pHardwareCounters->m_isolatedGroupCount                        = CounterGfx9::HWDX12SQIsolatedGroupCountGfx9;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX10)
    {
        pHardwareCounters->m_ppCounterGroupArray                       = CounterGfx10::DX12CounterGroupArrayGfx10;
        pHardwareCounters->m_pGroups                                   = CounterGfx10::HWDX12GroupsGfx10;
        pHardwareCounters->m_groupCount                                = CounterGfx10::HWDX12GroupCountGfx10;
        pHardwareCounters->m_pSQCounterGroups                          = CounterGfx10::HWDX12SQGroupsGfx10;
        pHardwareCounters->m_sqGroupCount                              = CounterGfx10::HWDX12SQGroupCountGfx10;
        pHardwareCounters->m_timestampBlockIds                         = CounterGfx10::HWDX12TimestampBlockIdsGfx10;
        pHardwareCounters->m_timeCounterIndices                        = CounterGfx10::HWDX12TimeCounterIndicesGfx10;
        pHardwareCounters->m_gpuTimeBottomToBottomDurationCounterIndex = CounterGfx10::HWDX12GputimeBottomToBottomDurationIndexGfx10;
        pHardwareCounters->m_gpuTimeBottomToBottomStartCounterIndex    = CounterGfx10::HWDX12GputimeBottomToBottomStartIndexGfx10;
        pHardwareCounters->m_gpuTimeBottomToBottomEndCounterIndex      = CounterGfx10::HWDX12GputimeBottomToBottomEndIndexGfx10;
        pHardwareCounters->m_gpuTimeTopToBottomDurationCounterIndex    = CounterGfx10::HWDX12GputimeTopToBottomDurationIndexGfx10;
        pHardwareCounters->m_gpuTimeTopToBottomStartCounterIndex       = CounterGfx10::HWDX12GputimeTopToBottomStartIndexGfx10;
        pHardwareCounters->m_gpuTimeTopToBottomEndCounterIndex         = CounterGfx10::HWDX12GputimeTopToBottomEndIndexGfx10;
        pHardwareCounters->m_pIsolatedGroups                           = CounterGfx10::HWDX12SQIsolatedGroupsGfx10;
        pHardwareCounters->m_isolatedGroupCount                        = CounterGfx10::HWDX12SQIsolatedGroupCountGfx10;
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

    return status;
}

GPA_Status GPA_CounterGeneratorDX12::GenerateHardwareExposedCounters(GDT_HW_GENERATION     desiredGeneration,
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
        pHardwareCounters->m_ppHardwareExposedCounter         = CounterGfx8::DX12ExposedCountersGroupArrayGfx8;
        pHardwareCounters->m_pHardwareExposedCounterGroups    = CounterGfx8::HWDX12ExposedCountersByGroupGfx8;
        pHardwareCounters->m_hardwareExposedCounterGroupCount = CounterGfx8::HWDX12ExposedCountersGroupCountGfx8;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
    {
        pHardwareCounters->m_ppHardwareExposedCounter         = CounterGfx9::DX12ExposedCountersGroupArrayGfx9;
        pHardwareCounters->m_pHardwareExposedCounterGroups    = CounterGfx9::HWDX12ExposedCountersByGroupGfx9;
        pHardwareCounters->m_hardwareExposedCounterGroupCount = CounterGfx9::HWDX12ExposedCountersGroupCountGfx9;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX10)
    {
        pHardwareCounters->m_ppHardwareExposedCounter         = CounterGfx10::DX12ExposedCountersGroupArrayGfx10;
        pHardwareCounters->m_pHardwareExposedCounterGroups    = CounterGfx10::HWDX12ExposedCountersByGroupGfx10;
        pHardwareCounters->m_hardwareExposedCounterGroupCount = CounterGfx10::HWDX12ExposedCountersGroupCountGfx10;
    }
    else
    {
        GPA_LogError("Unrecognized or unhandled hardware generation.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    pHardwareCounters->m_hardwareExposedCountersGenerated = MapHardwareExposedCounter(pHardwareCounters);
    return pHardwareCounters->m_hardwareExposedCountersGenerated ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}
