//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for DX11 counter generation for AMD HW
//==============================================================================

#include <D3D11.h>

#ifdef EXTRA_COUNTER_INFO
    #include <sstream>
#endif

#include "GPACounterGeneratorDX11.h"
#include "Logging.h"

#include "PublicCounterDefsDX11Gfx6.h"
#include "PublicCounterDefsDX11Gfx7.h"
#include "PublicCounterDefsDX11Gfx8.h"
#include "PublicCounterDefsDX11Gfx9.h"

#include "PublicCounterDefsDX11Gfx6Asics.h"
#include "PublicCounterDefsDX11Gfx7Asics.h"
#include "PublicCounterDefsDX11Gfx8Asics.h"
#include "PublicCounterDefsDX11Gfx9Asics.h"

#include "InternalCountersDX11Gfx6.h"
#include "InternalCountersDX11Gfx7.h"
#include "InternalCountersDX11Gfx8.h"
#include "InternalCountersDX11Gfx9.h"

#include "GPASoftwareCounters.h"

#include "AmdDxCounter.h"
#include "AmdDxExtPerfProfile.h"

#include "GPASwCounterManager.h"
#include "GPACounterGeneratorSchedulerManager.h"

GPA_CounterGeneratorDX11::GPA_CounterGeneratorDX11()
{
    GPA_CounterGeneratorBase::SetAllowedCounters(true, true, true); //enable all counters

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
        if (generation == GDT_HW_GENERATION_SOUTHERNISLAND)
        {
            return HWDX11DriverEnumGfx6[groupIndex];
        }
        else if (generation == GDT_HW_GENERATION_SEAISLAND)
        {
            return HWDX11DriverEnumGfx7[groupIndex];
        }
        else if (generation == GDT_HW_GENERATION_VOLCANICISLAND)
        {
            return HWDX11DriverEnumGfx8[groupIndex];
        }
        else if (generation == GDT_HW_GENERATION_GFX9)
        {
            return HWDX11DriverEnumGfx9[groupIndex];
        }
        else
        {
            // don't recognize the specified hardware generation.
            // need to add support or fix a bug.
            assert(generation == GDT_HW_GENERATION_SOUTHERNISLAND);
        }
    }

    return groupIndex;
}

/// Generates internal counters
/// \param pHardwareCounters the hardware counters to generate
/// \param generation the generation for which counters need to be generated
/// \return true on success
static bool generateInternalCounters(GPA_HardwareCounters* pHardwareCounters, GDT_HW_GENERATION generation)
{
    pHardwareCounters->m_counters.clear();

    GPA_HardwareCounterDescExt counter;
#if defined(_DEBUG) && defined(AMDT_INTERNAL)
    // Debug builds will generate a file that lists the counter names in a format that can be
    // easily copy/pasted into the GPUPerfAPIUnitTests project
    FILE* pFile = nullptr;
    fopen_s(&pFile, "HardwareCounterNamesDX11.txt", "w");
#endif

    unsigned int globalCounterIndex = 0;

    // for each group, get the group name, number of counters, and max counters (and maybe validate them)
    for (unsigned int g = 0; g < (int)pHardwareCounters->m_groupCount; g++)
    {
        GPA_HardwareCounterDesc* pGroupCounters = pHardwareCounters->m_ppCounterGroupArray[g];
        GPA_CounterGroupDesc group = pHardwareCounters->m_pGroups[g];

        // calculate per-block values outside the for loop
        UINT blockId = CalculateBlockIdDX11(generation, &group);

        // only add the number of counters that are supported; but no more than the number that we expect
        const gpa_uint64 numCountersInGroup = pHardwareCounters->m_pGroups[g].m_numCounters;

        for (int c = 0; c < numCountersInGroup; c++)
        {
            counter.m_groupIndex = g;
            counter.m_pHardwareCounter = &(pGroupCounters[c]);
            counter.m_groupIdDriver = blockId;

            if (pHardwareCounters->IsTimestampBlockId(counter.m_groupIndex))
            {
                counter.m_counterIdDriver = AmdCtrEncodeApiCounter((AmdApiCounterId)(globalCounterIndex - pHardwareCounters->GetFirstHardwareTimeCounterIndex()));
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

#if defined(_DEBUG) && defined(AMDT_INTERNAL)

    if (nullptr != pFile)
    {
        fclose(pFile);
    }

#endif;

    pHardwareCounters->m_countersGenerated = true;

    return true;
}


GPA_Status GPA_CounterGeneratorDX11::GeneratePublicCounters(
    GDT_HW_GENERATION desiredGeneration,
    GDT_HW_ASIC_TYPE asicType,
    gpa_uint8 generateAsicSpecificCounters,
    GPA_DerivedCounters* pPublicCounters)
{
    if (true == pPublicCounters->m_countersGenerated) //only generate counters once to improve performance
    {
        return GPA_STATUS_OK;
    }

    pPublicCounters->Clear();

    if (desiredGeneration == GDT_HW_GENERATION_SOUTHERNISLAND)
    {
        AutoDefineDerivedCountersDX11Gfx6(*pPublicCounters);

        if (generateAsicSpecificCounters)
        {
            DX11Gfx6Asics::UpdateAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
        }
    }
    else if (desiredGeneration == GDT_HW_GENERATION_SEAISLAND)
    {
        AutoDefineDerivedCountersDX11Gfx7(*pPublicCounters);

        if (generateAsicSpecificCounters)
        {
            DX11Gfx7Asics::UpdateAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
        }
    }
    else if (desiredGeneration == GDT_HW_GENERATION_VOLCANICISLAND)
    {
        AutoDefineDerivedCountersDX11Gfx8(*pPublicCounters);

        if (generateAsicSpecificCounters)
        {
            DX11Gfx8Asics::UpdateAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
        }
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
    {
        AutoDefineDerivedCountersDX11Gfx9(*pPublicCounters);

        if (generateAsicSpecificCounters)
        {
            DX11Gfx9Asics::UpdateAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
        }
    }
    else
    {
        GPA_LogError("Unsupported or unrecognized hardware generation. Cannot generate public counters.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    pPublicCounters->m_countersGenerated = true;

    return GPA_STATUS_OK;
}

GPA_Status GPA_CounterGeneratorDX11::GenerateHardwareCounters(
    GDT_HW_GENERATION desiredGeneration,
    GDT_HW_ASIC_TYPE asicType,
    gpa_uint8 generateAsicSpecificCounters,
    GPA_HardwareCounters* pHardwareCounters)
{
    UNREFERENCED_PARAMETER(asicType);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);

    if (true == pHardwareCounters->m_countersGenerated) //only generate counters once to improve performance
    {
        return GPA_STATUS_OK;
    }

    pHardwareCounters->Clear();

    if (desiredGeneration == GDT_HW_GENERATION_SOUTHERNISLAND)
    {
        pHardwareCounters->m_ppCounterGroupArray = DX11CounterGroupArrayGfx6;
        pHardwareCounters->m_pGroups = HWDX11GroupsGfx6;
        pHardwareCounters->m_groupCount = HWDX11GroupCountGfx6;
        pHardwareCounters->m_pSQCounterGroups = HWDX11SQGroupsGfx6;
        pHardwareCounters->m_sqGroupCount = HWDX11SQGroupCountGfx6;
        pHardwareCounters->m_timestampBlockIds = HWDX11TimestampBlockIdsGfx6;
        pHardwareCounters->m_timeCounterIndices = HWDX11TimeCounterIndicesGfx6;
        pHardwareCounters->m_gpuTimeBottomToBottomCounterIndex = HWDX11GPUTimeBottomToBottomIndexGfx6;
        pHardwareCounters->m_gpuTimeTopToBottomCounterIndex = HWDX11GPUTimeTopToBottomIndexGfx6;
        pHardwareCounters->m_pIsolatedGroups = HWDX11SQIsolatedGroupsGfx6;
        pHardwareCounters->m_isolatedGroupCount = HWDX11SQIsolatedGroupCountGfx6;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_SEAISLAND)
    {
        pHardwareCounters->m_ppCounterGroupArray = DX11CounterGroupArrayGfx7;
        pHardwareCounters->m_pGroups = HWDX11GroupsGfx7;
        pHardwareCounters->m_groupCount = HWDX11GroupCountGfx7;
        pHardwareCounters->m_pSQCounterGroups = HWDX11SQGroupsGfx7;
        pHardwareCounters->m_sqGroupCount = HWDX11SQGroupCountGfx7;
        pHardwareCounters->m_timestampBlockIds = HWDX11TimestampBlockIdsGfx7;
        pHardwareCounters->m_timeCounterIndices = HWDX11TimeCounterIndicesGfx7;
        pHardwareCounters->m_gpuTimeBottomToBottomCounterIndex = HWDX11GPUTimeBottomToBottomIndexGfx7;
        pHardwareCounters->m_gpuTimeTopToBottomCounterIndex = HWDX11GPUTimeTopToBottomIndexGfx7;
        pHardwareCounters->m_pIsolatedGroups = HWDX11SQIsolatedGroupsGfx7;
        pHardwareCounters->m_isolatedGroupCount = HWDX11SQIsolatedGroupCountGfx7;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_VOLCANICISLAND)
    {
        pHardwareCounters->m_ppCounterGroupArray = DX11CounterGroupArrayGfx8;
        pHardwareCounters->m_pGroups = HWDX11GroupsGfx8;
        pHardwareCounters->m_groupCount = HWDX11GroupCountGfx8;
        pHardwareCounters->m_pSQCounterGroups = HWDX11SQGroupsGfx8;
        pHardwareCounters->m_sqGroupCount = HWDX11SQGroupCountGfx8;
        pHardwareCounters->m_timestampBlockIds = HWDX11TimestampBlockIdsGfx8;
        pHardwareCounters->m_timeCounterIndices = HWDX11TimeCounterIndicesGfx8;
        pHardwareCounters->m_gpuTimeBottomToBottomCounterIndex = HWDX11GPUTimeBottomToBottomIndexGfx8;
        pHardwareCounters->m_gpuTimeTopToBottomCounterIndex = HWDX11GPUTimeTopToBottomIndexGfx8;
        pHardwareCounters->m_pIsolatedGroups = HWDX11SQIsolatedGroupsGfx8;
        pHardwareCounters->m_isolatedGroupCount = HWDX11SQIsolatedGroupCountGfx8;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
    {
        pHardwareCounters->m_ppCounterGroupArray = DX11CounterGroupArrayGfx9;
        pHardwareCounters->m_pGroups = HWDX11GroupsGfx9;
        pHardwareCounters->m_groupCount = HWDX11GroupCountGfx9;
        pHardwareCounters->m_pSQCounterGroups = HWDX11SQGroupsGfx9;
        pHardwareCounters->m_sqGroupCount = HWDX11SQGroupCountGfx9;
        pHardwareCounters->m_timestampBlockIds = HWDX11TimestampBlockIdsGfx9;
        pHardwareCounters->m_timeCounterIndices = HWDX11TimeCounterIndicesGfx9;
        pHardwareCounters->m_gpuTimeBottomToBottomCounterIndex = HWDX11GPUTimeBottomToBottomIndexGfx9;
        pHardwareCounters->m_gpuTimeTopToBottomCounterIndex = HWDX11GPUTimeTopToBottomIndexGfx9;
        pHardwareCounters->m_pIsolatedGroups = HWDX11SQIsolatedGroupsGfx9;
        pHardwareCounters->m_isolatedGroupCount = HWDX11SQIsolatedGroupCountGfx9;
    }
    else
    {
        GPA_LogError("Unrecognized or unhandled hardware generation.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    // need to count total number of internal counters, since split into groups
    if (!pHardwareCounters->m_countersGenerated)
    {
        if (!generateInternalCounters(pHardwareCounters, desiredGeneration))
        {
            GPA_LogError("Unable to generate internal counters.");
            pHardwareCounters->m_currentGroupUsedCounts.resize(0);
            return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
        }
    }

    unsigned int uGroupCount = pHardwareCounters->m_groupCount;
    pHardwareCounters->m_currentGroupUsedCounts.resize(uGroupCount);

    return GPA_STATUS_OK;
}


