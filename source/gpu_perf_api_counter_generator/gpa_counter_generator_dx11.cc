//==============================================================================
// Copyright (c) 2016-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for DX11 counter generation for AMD HW
//==============================================================================

#include <d3d11.h>

#ifdef EXTRA_COUNTER_INFO
#include <sstream>
#endif

#include "gpa_counter_generator_dx11.h"
#include "logging.h"

#include "public_counter_definitions_dx11_gfx8.h"
#include "public_counter_definitions_dx11_gfx9.h"
#include "public_counter_definitions_dx11_gfx10.h"

#include "public_counter_definitions_dx11_gfx8_asics.h"
#include "public_counter_definitions_dx11_gfx9_asics.h"
#include "public_counter_definitions_dx11_gfx10_asics.h"

#include "gpa_hw_counter_dx11_gfx8.h"
#include "gpa_hw_counter_dx11_gfx9.h"
#include "gpa_hw_counter_dx11_gfx10.h"

#include "gpa_software_counters.h"

#include "AmdDxCounter.h"
#include "AmdDxExtPerfProfile.h"

#include "gpa_sw_counter_manager.h"
#include "gpa_counter_generator_scheduler_manager.h"

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
            return countergfx8::hw_dx11_driver_enum_gfx8[groupIndex];
        }

        if (generation == GDT_HW_GENERATION_GFX9)
        {
            return countergfx9::hw_dx11_driver_enum_gfx9[groupIndex];
        }

        if (generation == GDT_HW_GENERATION_GFX10)
        {
            return countergfx10::hw_dx11_driver_enum_gfx10[groupIndex];
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
                dx11gfx8asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
        }
        else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
        {
            AutoDefinePublicDerivedCountersDX11Gfx9(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                dx11gfx9asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
        }
        else if (desiredGeneration == GDT_HW_GENERATION_GFX10)
        {
            AutoDefinePublicDerivedCountersDX11Gfx10(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                dx11gfx10asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
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
        pHardwareCounters->m_ppCounterGroupArray                       = countergfx8::dx11_counter_group_array_gfx8;
        pHardwareCounters->m_pGroups                                   = countergfx8::hw_dx11_groups_gfx8;
        pHardwareCounters->m_groupCount                                = countergfx8::hw_dx11_group_count_gfx8;
        pHardwareCounters->m_pSQCounterGroups                          = countergfx8::hw_dx11_sq_groups_gfx8;
        pHardwareCounters->m_sqGroupCount                              = countergfx8::hw_dx11_sq_group_count_gfx8;
        pHardwareCounters->m_timestampBlockIds                         = countergfx8::hw_dx11_timestamp_block_ids_gfx8;
        pHardwareCounters->m_timeCounterIndices                        = countergfx8::hw_dx11_time_counter_indices_gfx8;
        pHardwareCounters->m_gpuTimeBottomToBottomDurationCounterIndex = countergfx8::hw_dx11_gputimebottomtobottomduration_index_gfx8;
        pHardwareCounters->m_gpuTimeBottomToBottomStartCounterIndex    = countergfx8::hw_dx11_gputimebottomtobottomstart_index_gfx8;
        pHardwareCounters->m_gpuTimeBottomToBottomEndCounterIndex      = countergfx8::hw_dx11_gputimebottomtobottomend_index_gfx8;
        pHardwareCounters->m_gpuTimeTopToBottomDurationCounterIndex    = countergfx8::hw_dx11_gputimetoptobottomduration_index_gfx8;
        pHardwareCounters->m_gpuTimeTopToBottomStartCounterIndex       = countergfx8::hw_dx11_gputimetoptobottomstart_index_gfx8;
        pHardwareCounters->m_gpuTimeTopToBottomEndCounterIndex         = countergfx8::hw_dx11_gputimetoptobottomend_index_gfx8;
        pHardwareCounters->m_pIsolatedGroups                           = countergfx8::hw_dx11_sq_isolated_groups_gfx8;
        pHardwareCounters->m_isolatedGroupCount                        = countergfx8::hw_dx11_sq_isolated_group_count_gfx8;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
    {
        pHardwareCounters->m_ppCounterGroupArray                       = countergfx9::dx11_counter_group_array_gfx9;
        pHardwareCounters->m_pGroups                                   = countergfx9::hw_dx11_groups_gfx9;
        pHardwareCounters->m_groupCount                                = countergfx9::hw_dx11_group_count_gfx9;
        pHardwareCounters->m_pSQCounterGroups                          = countergfx9::hw_dx11_sq_groups_gfx9;
        pHardwareCounters->m_sqGroupCount                              = countergfx9::hw_dx11_sq_group_count_gfx9;
        pHardwareCounters->m_timestampBlockIds                         = countergfx9::hw_dx11_timestamp_block_ids_gfx9;
        pHardwareCounters->m_timeCounterIndices                        = countergfx9::hw_dx11_time_counter_indices_gfx9;
        pHardwareCounters->m_gpuTimeBottomToBottomDurationCounterIndex = countergfx9::hw_dx11_gputimebottomtobottomduration_index_gfx9;
        pHardwareCounters->m_gpuTimeBottomToBottomStartCounterIndex    = countergfx9::hw_dx11_gputimebottomtobottomstart_index_gfx9;
        pHardwareCounters->m_gpuTimeBottomToBottomEndCounterIndex      = countergfx9::hw_dx11_gputimebottomtobottomend_index_gfx9;
        pHardwareCounters->m_gpuTimeTopToBottomDurationCounterIndex    = countergfx9::hw_dx11_gputimetoptobottomduration_index_gfx9;
        pHardwareCounters->m_gpuTimeTopToBottomStartCounterIndex       = countergfx9::hw_dx11_gputimetoptobottomstart_index_gfx9;
        pHardwareCounters->m_gpuTimeTopToBottomEndCounterIndex         = countergfx9::hw_dx11_gputimetoptobottomend_index_gfx9;
        pHardwareCounters->m_pIsolatedGroups                           = countergfx9::hw_dx11_sq_isolated_groups_gfx9;
        pHardwareCounters->m_isolatedGroupCount                        = countergfx9::hw_dx11_sq_isolated_group_count_gfx9;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX10)
    {
        pHardwareCounters->m_ppCounterGroupArray                       = countergfx10::dx11_counter_group_array_gfx10;
        pHardwareCounters->m_pGroups                                   = countergfx10::hw_dx11_groups_gfx10;
        pHardwareCounters->m_groupCount                                = countergfx10::hw_dx11_group_count_gfx10;
        pHardwareCounters->m_pSQCounterGroups                          = countergfx10::hw_dx11_sq_groups_gfx10;
        pHardwareCounters->m_sqGroupCount                              = countergfx10::hw_dx11_sq_group_count_gfx10;
        pHardwareCounters->m_timestampBlockIds                         = countergfx10::hw_dx11_timestamp_block_ids_gfx10;
        pHardwareCounters->m_timeCounterIndices                        = countergfx10::hw_dx11_time_counter_indices_gfx10;
        pHardwareCounters->m_gpuTimeBottomToBottomDurationCounterIndex = countergfx10::hw_dx11_gputimebottomtobottomduration_index_gfx10;
        pHardwareCounters->m_gpuTimeBottomToBottomStartCounterIndex    = countergfx10::hw_dx11_gputimebottomtobottomstart_index_gfx10;
        pHardwareCounters->m_gpuTimeBottomToBottomEndCounterIndex      = countergfx10::hw_dx11_gputimebottomtobottomend_index_gfx10;
        pHardwareCounters->m_gpuTimeTopToBottomDurationCounterIndex    = countergfx10::hw_dx11_gputimetoptobottomduration_index_gfx10;
        pHardwareCounters->m_gpuTimeTopToBottomStartCounterIndex       = countergfx10::hw_dx11_gputimetoptobottomstart_index_gfx10;
        pHardwareCounters->m_gpuTimeTopToBottomEndCounterIndex         = countergfx10::hw_dx11_gputimetoptobottomend_index_gfx10;
        pHardwareCounters->m_pIsolatedGroups                           = countergfx10::hw_dx11_sq_isolated_groups_gfx10;
        pHardwareCounters->m_isolatedGroupCount                        = countergfx10::hw_dx11_sq_isolated_group_count_gfx10;
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
    pHardwareCounters->block_instance_counters_index_cache_.clear();
    pHardwareCounters->gpa_hw_block_hardware_block_group_cache_.clear();
    pHardwareCounters->counter_hardware_info_map_.clear();
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
        pHardwareCounters->m_ppHardwareExposedCounter         = countergfx8::dx11_exposed_counters_group_array_gfx8;
        pHardwareCounters->m_pHardwareExposedCounterGroups    = countergfx8::hw_dx11_exposed_counters_by_group_gfx8;
        pHardwareCounters->m_hardwareExposedCounterGroupCount = countergfx8::hw_dx11_exposed_counters_group_count_gfx8;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
    {
        pHardwareCounters->m_ppHardwareExposedCounter         = countergfx9::dx11_exposed_counters_group_array_gfx9;
        pHardwareCounters->m_pHardwareExposedCounterGroups    = countergfx9::hw_dx11_exposed_counters_by_group_gfx9;
        pHardwareCounters->m_hardwareExposedCounterGroupCount = countergfx9::hw_dx11_exposed_counters_group_count_gfx9;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX10)
    {
        pHardwareCounters->m_ppHardwareExposedCounter         = countergfx10::dx11_exposed_counters_group_array_gfx10;
        pHardwareCounters->m_pHardwareExposedCounterGroups    = countergfx10::hw_dx11_exposed_counters_by_group_gfx10;
        pHardwareCounters->m_hardwareExposedCounterGroupCount = countergfx10::hw_dx11_exposed_counters_group_count_gfx10;
    }
    else
    {
        GPA_LogError("Unrecognized or unhandled hardware generation.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    pHardwareCounters->m_hardwareExposedCountersGenerated = MapHardwareExposedCounter(pHardwareCounters);
    return pHardwareCounters->m_hardwareExposedCountersGenerated ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}
