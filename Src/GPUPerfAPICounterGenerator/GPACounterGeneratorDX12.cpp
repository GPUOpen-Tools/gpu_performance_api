//==============================================================================
// Copyright (c) 2015-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for DX12 counter generation
//==============================================================================


/// \author GPU Developer Tools
/// \brief GPA_CounterGeneratorDX12 implementation

#include "GPACounterGeneratorDX12.h"
#include "GPACounterGeneratorSchedulerManager.h"

#include "InternalCountersDX12Gfx7.h"
#include "InternalCountersDX12Gfx8.h"
#include "InternalCountersDX12Gfx9.h"

#include "PublicCounterDefsDX12Gfx7.h"
#include "PublicCounterDefsDX12Gfx8.h"
#include "PublicCounterDefsDX12Gfx9.h"

#include "PublicCounterDefsDX12Gfx7Asics.h"
#include "PublicCounterDefsDX12Gfx8Asics.h"
#include "PublicCounterDefsDX12Gfx9Asics.h"

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
UINT GPA_CounterGeneratorDX12::CalculateBlockIdDX12(GDT_HW_GENERATION generation, GPA_CounterGroupDesc* pGroup)
{
    UINT groupIndex = static_cast<UINT>(pGroup->m_groupIndex);

    if (IsAMDGPU(generation))
    {
        if (generation == GDT_HW_GENERATION_SEAISLAND)
        {
            return static_cast<UINT>(HWDX12DriverEnumGfx7[groupIndex]);
        }
        else if (generation == GDT_HW_GENERATION_VOLCANICISLAND)
        {
            return static_cast<UINT>(HWDX12DriverEnumGfx8[groupIndex]);
        }
        else if (generation == GDT_HW_GENERATION_GFX9)
        {
            return static_cast<UINT>(HWDX12DriverEnumGfx9[groupIndex]);
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

GPA_CounterGeneratorDX12::GPA_CounterGeneratorDX12():
    GPA_CounterGeneratorDX12Base()
{
    GPA_CounterGeneratorBase::SetAllowedCounters(true, true, true); //enable public, hw, and sw counters

    for (int gen = GDT_HW_GENERATION_SOUTHERNISLAND; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(GPA_API_DIRECTX_12, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GPA_CounterGeneratorDX12::~GPA_CounterGeneratorDX12()
{
}


GPA_Status GPA_CounterGeneratorDX12::GeneratePublicCounters(
    GDT_HW_GENERATION desiredGeneration,
    GDT_HW_ASIC_TYPE asicType,
    gpa_uint8 generateAsicSpecificCounters,
    GPA_PublicCounters* pPublicCounters)
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
            {
                AutoDefinePublicCountersDX12Gfx7(*pPublicCounters);
                if (generateAsicSpecificCounters)
                {
                    DX12Gfx7Asics::UpdateAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
                }
                pPublicCounters->m_countersGenerated = true;
            }
            break;

            case GDT_HW_GENERATION_VOLCANICISLAND:
            {
                AutoDefinePublicCountersDX12Gfx8(*pPublicCounters);
                if (generateAsicSpecificCounters)
                {
                    DX12Gfx8Asics::UpdateAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
                }
                pPublicCounters->m_countersGenerated = true;
            }
            break;

            case GDT_HW_GENERATION_GFX9:
            {
                AutoDefinePublicCountersDX12Gfx9(*pPublicCounters);
                if (generateAsicSpecificCounters)
                {
                    DX12Gfx9Asics::UpdateAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
                }
                pPublicCounters->m_countersGenerated = true;
            }
            break;

            default:
                status = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
                break;
        }
    }

    return status;
}


bool GPA_CounterGeneratorDX12::GenerateInternalCounters(GPA_HardwareCounters* pHardwareCounters, GDT_HW_GENERATION generation)
{
    pHardwareCounters->m_counters.clear();

    GPA_HardwareCounterDescExt counter;
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
        UINT blockId = CalculateBlockIdDX12(generation, &group);

        // only add the number of counters that are supported; but no more than the number that we expect
        const gpa_uint64 numCountersInGroup = pHardwareCounters->m_pGroups[g].m_numCounters;

        for (int c = 0; c < numCountersInGroup; c++)
        {
            counter.m_groupIndex = g;
            counter.m_pHardwareCounter = &(pGroupCounters[c]);
            counter.m_groupIdDriver = blockId;

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

GPA_Status GPA_CounterGeneratorDX12::GenerateHardwareCounters(
    GDT_HW_GENERATION desiredGeneration,
    GDT_HW_ASIC_TYPE asicType,
    gpa_uint8 generateAsicSpecificCounters,
    GPA_HardwareCounters* pHardwareCounters)
{
    UNREFERENCED_PARAMETER(asicType);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);

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
            pHardwareCounters->m_ppCounterGroupArray = DX12CounterGroupArrayGfx7;
            pHardwareCounters->m_pGroups = HWDX12GroupsGfx7;
            pHardwareCounters->m_groupCount = HWDX12GroupCountGfx7;
            pHardwareCounters->m_pSQCounterGroups = HWDX12SQGroupsGfx7;
            pHardwareCounters->m_sqGroupCount = HWDX12SQGroupCountGfx7;
            pHardwareCounters->m_gpuTimestampIndex = static_cast<unsigned int>(-1);// HWDX12GPUTimeStampIndexGfx7;
            pHardwareCounters->m_gpuTimeIndex = HWDX12GPUTimeIndexGfx7;
            pHardwareCounters->m_pIsolatedGroups = HWDX12SQIsolatedGroupsGfx7;
            pHardwareCounters->m_isolatedGroupCount = HWDX12SQIsolatedGroupCountGfx7;
        }
        else if (desiredGeneration == GDT_HW_GENERATION_VOLCANICISLAND)
        {
            pHardwareCounters->m_ppCounterGroupArray = DX12CounterGroupArrayGfx8;
            pHardwareCounters->m_pGroups = HWDX12GroupsGfx8;
            pHardwareCounters->m_groupCount = HWDX12GroupCountGfx8;
            pHardwareCounters->m_pSQCounterGroups = HWDX12SQGroupsGfx8;
            pHardwareCounters->m_sqGroupCount = HWDX12SQGroupCountGfx8;
            pHardwareCounters->m_gpuTimestampIndex = static_cast<unsigned int>(-1);// HWDX12GPUTimeStampIndexGfx8;
            pHardwareCounters->m_gpuTimeIndex = HWDX12GPUTimeIndexGfx8;
            pHardwareCounters->m_pIsolatedGroups = HWDX12SQIsolatedGroupsGfx8;
            pHardwareCounters->m_isolatedGroupCount = HWDX12SQIsolatedGroupCountGfx8;
        }
        else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
        {
            pHardwareCounters->m_ppCounterGroupArray = DX12CounterGroupArrayGfx9;
            pHardwareCounters->m_pGroups = HWDX12GroupsGfx9;
            pHardwareCounters->m_groupCount = HWDX12GroupCountGfx9;
            pHardwareCounters->m_pSQCounterGroups = HWDX12SQGroupsGfx9;
            pHardwareCounters->m_sqGroupCount = HWDX12SQGroupCountGfx9;
            pHardwareCounters->m_gpuTimestampIndex = static_cast<unsigned int>(-1);// HWDX12GPUTimeStampIndexGfx9;
            pHardwareCounters->m_gpuTimeIndex = HWDX12GPUTimeIndexGfx9;
            pHardwareCounters->m_pIsolatedGroups = HWDX12SQIsolatedGroupsGfx9;
            pHardwareCounters->m_isolatedGroupCount = HWDX12SQIsolatedGroupCountGfx9;
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
