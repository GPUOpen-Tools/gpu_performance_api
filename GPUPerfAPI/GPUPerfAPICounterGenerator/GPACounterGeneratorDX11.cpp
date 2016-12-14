//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
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

#include "InternalCountersDX11Gfx6.h"
#include "InternalCountersDX11Gfx7.h"
#include "InternalCountersDX11Gfx8.h"

#include "GPASoftwareCounters.h"

#include "AmdDxCounter.h"

#include "GPACounterGeneratorCommon.h"
#include "GPASwCounterManager.h"
#include "GPACounterGeneratorSchedulerManager.h"

GPA_CounterGeneratorDX11::GPA_CounterGeneratorDX11()
{
    SetAllowedCounters(true, true, true); //enable all counters

    for (int gen = GDT_HW_GENERATION_FIRST_AMD; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(GPA_API_DIRECTX_11, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

/// Logic inside this function is based on the r*00perfcounter.h files from the DX driver.
/// The driver gives each block an ID, but ignores the instance. GPA treats each instance as a different
/// block, so we need to translate.
/// \param generation the generation whose block id needs to be calculated
/// \param pGroup the group for which the block id needs to be calculated
/// \return the block id according to the driver
static UINT CalculateBlockIdDX11(GDT_HW_GENERATION generation, GPA_CounterGroupDesc* pGroup)
{
    UINT groupIndex = (UINT)pGroup->m_groupIndex;
    UINT delta = 0;

    if (GPA_CounterGeneratorDX11Base::IsAMDGPU(generation))
    {
        if (generation == GDT_HW_GENERATION_SOUTHERNISLAND)
        {
            static const UINT firstDRMDMAIndex = 0;
            static const UINT firstCBIndex = 4;
            static const UINT firstDBIndex = 12;
            static const UINT firstGRBMSEIndex = 21;
            static const UINT firstPASUIndex = 24;
            static const UINT firstPASCIndex = 26;
            static const UINT firstSXIndex = 28;
            static const UINT firstSPIIndex = 32;
            static const UINT firstSQIndex = 34;
            static const UINT firstTAIndex = 36;
            static const UINT firstTDIndex = 68;
            static const UINT firstTCPIndex = 100;
            static const UINT firstTCCIndex = 132;
            static const UINT firstTCAIndex = 144;
            static const UINT firstVGTIndex = 148;
            static const UINT firstMCIndex = 150;

            // need to account for 2 DRMDMA blocks
            delta += CalculateBlockDelta(groupIndex, firstDRMDMAIndex, 2);

            // need to account for 8 CB blocks
            delta += CalculateBlockDelta(groupIndex, firstCBIndex, 8);

            // need to account for 8 DB blocks
            delta += CalculateBlockDelta(groupIndex, firstDBIndex, 8);

            // need to account for 2 GRBMSE blocks
            delta += CalculateBlockDelta(groupIndex, firstGRBMSEIndex, 2);

            // need to account for 2 PA_SU blocks
            delta += CalculateBlockDelta(groupIndex, firstPASUIndex, 2);

            // need to account for 2 PA_SC blocks
            delta += CalculateBlockDelta(groupIndex, firstPASCIndex, 2);

            // need to account for 4 SX blocks
            delta += CalculateBlockDelta(groupIndex, firstSXIndex, 4);

            // need to account for 2 SPI blocks
            delta += CalculateBlockDelta(groupIndex, firstSPIIndex, 2);

            // need to account for 2 SQ blocks
            delta += CalculateBlockDelta(groupIndex, firstSQIndex, 2);

            // need to account for 32 TA blocks
            delta += CalculateBlockDelta(groupIndex, firstTAIndex, 32);

            // need to account for 32 TD blocks
            delta += CalculateBlockDelta(groupIndex, firstTDIndex, 32);

            // need to account for 32 TCP blocks
            delta += CalculateBlockDelta(groupIndex, firstTCPIndex, 32);

            // need to account for 12 TCC blocks
            delta += CalculateBlockDelta(groupIndex, firstTCCIndex, 12);

            // need to account for 2 TCA blocks
            delta += CalculateBlockDelta(groupIndex, firstTCAIndex, 2);

            // need to account for 2 VGT blocks
            delta += CalculateBlockDelta(groupIndex, firstVGTIndex, 2);

            // need to account for 12 MC blocks
            delta += CalculateBlockDelta(groupIndex, firstMCIndex, 12);

            groupIndex = groupIndex - delta;
        }
        else if (generation == GDT_HW_GENERATION_SEAISLAND)
        {
            static const UINT firstSDMAIndex = 0;
            static const UINT firstCBIndex = 4;
            static const UINT firstDBIndex = 20;
            static const UINT firstGRBMSEIndex = 37;
            static const UINT firstPASUIndex = 42;
            static const UINT firstPASCIndex = 46;
            static const UINT firstSXIndex = 50;
            static const UINT firstSPIIndex = 54;
            static const UINT firstSQIndex = 58;
            static const UINT firstTAIndex = 90;
            static const UINT firstTDIndex = 134;
            static const UINT firstTCPIndex = 178;
            static const UINT firstTCCIndex = 222;
            static const UINT firstTCAIndex = 238;
            static const UINT firstIAIndex = 241;
            static const UINT firstVGTIndex = 243;
            static const UINT firstMCIndex = 247;

            // need to account for 2 SDMA blocks
            delta += CalculateBlockDelta(groupIndex, firstSDMAIndex, 2);

            // need to account for 16 CB blocks
            delta += CalculateBlockDelta(groupIndex, firstCBIndex, 16);

            // need to account for 16 DB blocks
            delta += CalculateBlockDelta(groupIndex, firstDBIndex, 16);

            // need to account for 4 GRBMSE blocks
            delta += CalculateBlockDelta(groupIndex, firstGRBMSEIndex, 4);

            // need to account for 4 PA_SU blocks
            delta += CalculateBlockDelta(groupIndex, firstPASUIndex, 4);

            // need to account for 4 PA_SC blocks
            delta += CalculateBlockDelta(groupIndex, firstPASCIndex, 4);

            // need to account for 4 SX blocks
            delta += CalculateBlockDelta(groupIndex, firstSXIndex, 4);

            // need to account for 4 SPI blocks
            delta += CalculateBlockDelta(groupIndex, firstSPIIndex, 4);

            // need to account for 4 SQ blocks ( * 8 for all the stage-specific versions )
            delta += CalculateBlockDelta(groupIndex, firstSQIndex, 32);

            // need to account for 44 TA blocks
            delta += CalculateBlockDelta(groupIndex, firstTAIndex, 44);

            // need to account for 44 TD blocks
            delta += CalculateBlockDelta(groupIndex, firstTDIndex, 44);

            // need to account for 44 TCP blocks
            delta += CalculateBlockDelta(groupIndex, firstTCPIndex, 44);

            // need to account for 16 TCC blocks
            delta += CalculateBlockDelta(groupIndex, firstTCCIndex, 16);

            // need to account for 2 TCA blocks
            delta += CalculateBlockDelta(groupIndex, firstTCAIndex, 2);

            // need to account for 2 IA blocks
            delta += CalculateBlockDelta(groupIndex, firstIAIndex, 2);

            // need to account for 4 VGT blocks
            delta += CalculateBlockDelta(groupIndex, firstVGTIndex, 4);

            // need to account for 16 MC blocks
            delta += CalculateBlockDelta(groupIndex, firstMCIndex, 16);

            groupIndex = groupIndex - delta;
        }
        else if (generation == GDT_HW_GENERATION_VOLCANICISLAND)
        {
            static const UINT firstSDMAIndex = 0;
            static const UINT firstCBIndex = 4;
            static const UINT firstDBIndex = 20;
            static const UINT firstGRBMSEIndex = 37;
            static const UINT firstPASUIndex = 42;
            static const UINT firstPASCIndex = 46;
            static const UINT firstSXIndex = 50;
            static const UINT firstSPIIndex = 54;
            static const UINT firstSQIndex = 58;
            static const UINT firstTAIndex = 90;
            static const UINT firstTDIndex = 154;
            static const UINT firstTCPIndex = 218;
            static const UINT firstTCCIndex = 282;
            static const UINT firstTCAIndex = 298;
            static const UINT firstIAIndex = 301;
            static const UINT firstVGTIndex = 303;
            static const UINT firstMCIndex = 307;

            // need to account for 2 SDMA blocks
            delta += CalculateBlockDelta(groupIndex, firstSDMAIndex, 2);

            // need to account for 16 CB blocks
            delta += CalculateBlockDelta(groupIndex, firstCBIndex, 16);

            // need to account for 16 DB blocks
            delta += CalculateBlockDelta(groupIndex, firstDBIndex, 16);

            // need to account for 4 GRBMSE blocks
            delta += CalculateBlockDelta(groupIndex, firstGRBMSEIndex, 4);

            // need to account for 4 PA_SU blocks
            delta += CalculateBlockDelta(groupIndex, firstPASUIndex, 4);

            // need to account for 4 PA_SC blocks
            delta += CalculateBlockDelta(groupIndex, firstPASCIndex, 4);

            // need to account for 4 SX blocks
            delta += CalculateBlockDelta(groupIndex, firstSXIndex, 4);

            // need to account for 4 SPI blocks
            delta += CalculateBlockDelta(groupIndex, firstSPIIndex, 4);

            // need to account for 4 SQ blocks ( * 8 for all the stage-specific versions )
            delta += CalculateBlockDelta(groupIndex, firstSQIndex, 32);

            // need to account for 64 TA blocks
            delta += CalculateBlockDelta(groupIndex, firstTAIndex, 64);

            // need to account for 64 TD blocks
            delta += CalculateBlockDelta(groupIndex, firstTDIndex, 64);

            // need to account for 64 TCP blocks
            delta += CalculateBlockDelta(groupIndex, firstTCPIndex, 64);

            // need to account for 16 TCC blocks
            delta += CalculateBlockDelta(groupIndex, firstTCCIndex, 16);

            // need to account for 2 TCA blocks
            delta += CalculateBlockDelta(groupIndex, firstTCAIndex, 2);

            // need to account for 2 IA blocks
            delta += CalculateBlockDelta(groupIndex, firstIAIndex, 2);

            // need to account for 4 VGT blocks
            delta += CalculateBlockDelta(groupIndex, firstVGTIndex, 4);

            // need to account for 32 MC blocks
            delta += CalculateBlockDelta(groupIndex, firstMCIndex, 32);

            groupIndex = groupIndex - delta;
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

/// Adds 1 to block instance because supplying 0 means sum all instances, so the driver is essentially 1-based, not 0-based
static UINT CalculateCounterIndexDX11(GDT_HW_GENERATION generation, UINT blockId, unsigned int globalCounterIndex)
{
    UINT counterIndex = 0;

    if (GPA_CounterGeneratorDX11Base::IsAMDGPU(generation))
    {
        if (generation == GDT_HW_GENERATION_SOUTHERNISLAND)
        {
            static unsigned int firstCounterIndex = 0;

            if (blockId == 22)
            {
                // GPUTimeStamp and GPUTime are exposed through the DX API, so need to reset the first counter index at the GPUTimeStamp Group.
                firstCounterIndex = globalCounterIndex;
            }

            counterIndex = AmdCtrEncodeApiCounter((AmdApiCounterId)(globalCounterIndex - firstCounterIndex));
        }
        else if (generation == GDT_HW_GENERATION_SEAISLAND)
        {
            static unsigned int firstCounterIndex = 0;

            if (blockId == 26)
            {
                // GPUTimeStamp and GPUTime are exposed through the DX API, so need to reset the first counter index at the GPUTimeStamp Group.
                firstCounterIndex = globalCounterIndex;
            }

            counterIndex = AmdCtrEncodeApiCounter((AmdApiCounterId)(globalCounterIndex - firstCounterIndex));
        }
        else if (generation == GDT_HW_GENERATION_VOLCANICISLAND)
        {
            static unsigned int firstCounterIndex = 0;

            if (blockId == 25)
            {
                // GPUTimeStamp and GPUTime are exposed through the DX API, so need to reset the first counter index at the GPUTimeStamp Group.
                firstCounterIndex = globalCounterIndex;
            }

            counterIndex = AmdCtrEncodeApiCounter((AmdApiCounterId)(globalCounterIndex - firstCounterIndex));
        }
        else
        {
            // don't recognize the specified hardware generation.
            // need to add support or fix a bug.
            assert(generation == GDT_HW_GENERATION_SOUTHERNISLAND);
            counterIndex = 0;
        }
    }

    return counterIndex;
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

        if (g == pHardwareCounters->m_gpuTimestampIndex)
        {
            pHardwareCounters->m_gpuTimestampTopCounterIndex = (gpa_uint32)pHardwareCounters->m_counters.size();
        }
        else if (g == pHardwareCounters->m_gpuTimeIndex)
        {
            pHardwareCounters->m_gpuTimeBottomToBottomCounterIndex = (gpa_uint32)pHardwareCounters->m_counters.size();
            pHardwareCounters->m_gpuTimeTopToBottomCounterIndex = (gpa_uint32)pHardwareCounters->m_counters.size() + 1;
        }

        // calculate per-block values outside the for loop
        UINT blockId = CalculateBlockIdDX11(generation, &group);

        // only add the number of counters that are supported; but no more than the number that we expect
        const gpa_uint64 numCountersInGroup = pHardwareCounters->m_pGroups[g].m_numCounters;

        for (int c = 0; c < numCountersInGroup; c++)
        {
            counter.m_groupIndex = g;
            counter.m_pHardwareCounter = &(pGroupCounters[c]);
            counter.m_groupIdDriver = blockId;

            // counterIdDriver is used primarily for pre-SI.  In SI and later, it is used for GPUTimeStamp and GPUTime counters only.
            if (counter.m_groupIndex >= pHardwareCounters->m_gpuTimeIndex - 1)
            {
                counter.m_counterIdDriver = CalculateCounterIndexDX11(generation, blockId, globalCounterIndex);
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


GPA_Status GPA_CounterGeneratorDX11::GeneratePublicCounters(GDT_HW_GENERATION desiredGeneration, GPA_PublicCounters* pPublicCounters)
{
    if (true == pPublicCounters->m_countersGenerated) //only generate counters once to improve performance
    {
        return GPA_STATUS_OK;
    }

    pPublicCounters->Clear();

    if (desiredGeneration == GDT_HW_GENERATION_SOUTHERNISLAND)
    {
        AutoDefinePublicCountersDX11Gfx6(*pPublicCounters);
    }
    else if (desiredGeneration == GDT_HW_GENERATION_SEAISLAND)
    {
        AutoDefinePublicCountersDX11Gfx7(*pPublicCounters);
    }
    else if (desiredGeneration == GDT_HW_GENERATION_VOLCANICISLAND)
    {
        AutoDefinePublicCountersDX11Gfx8(*pPublicCounters);
    }
    else
    {
        GPA_LogError("Unsupported or unrecognized hardware generation. Cannot generate public counters.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    pPublicCounters->m_countersGenerated = true;

    return GPA_STATUS_OK;
}

GPA_Status GPA_CounterGeneratorDX11::GenerateHardwareCounters(GDT_HW_GENERATION desiredGeneration, GPA_HardwareCounters* pHardwareCounters)
{
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
        pHardwareCounters->m_gpuTimestampIndex = HWDX11GPUTimeStampIndexGfx6;
        pHardwareCounters->m_gpuTimeIndex = HWDX11GPUTimeIndexGfx6;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_SEAISLAND)
    {
        pHardwareCounters->m_ppCounterGroupArray = DX11CounterGroupArrayGfx7;
        pHardwareCounters->m_pGroups = HWDX11GroupsGfx7;
        pHardwareCounters->m_groupCount = HWDX11GroupCountGfx7;
        pHardwareCounters->m_pSQCounterGroups = HWDX11SQGroupsGfx7;
        pHardwareCounters->m_sqGroupCount = HWDX11SQGroupCountGfx7;
        pHardwareCounters->m_gpuTimestampIndex = HWDX11GPUTimeStampIndexGfx7;
        pHardwareCounters->m_gpuTimeIndex = HWDX11GPUTimeIndexGfx7;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_VOLCANICISLAND)
    {
        pHardwareCounters->m_ppCounterGroupArray = DX11CounterGroupArrayGfx8;
        pHardwareCounters->m_pGroups = HWDX11GroupsGfx8;
        pHardwareCounters->m_groupCount = HWDX11GroupCountGfx8;
        pHardwareCounters->m_pSQCounterGroups = HWDX11SQGroupsGfx8;
        pHardwareCounters->m_sqGroupCount = HWDX11SQGroupCountGfx8;
        pHardwareCounters->m_gpuTimestampIndex = HWDX11GPUTimeStampIndexGfx8;
        pHardwareCounters->m_gpuTimeIndex = HWDX11GPUTimeIndexGfx8;
    }
    else
    {
        GPA_LogError("Unrecognized or unhandled hardware generation.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    // need to count total number of internal counters, since split into groups
    if (!pHardwareCounters->m_countersGenerated)
    {
        if (generateInternalCounters(pHardwareCounters, desiredGeneration) == false)
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


