//==============================================================================
// Copyright (c) 2016-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for CL counter generation
//==============================================================================

#include "gpa_counter_generator_cl.h"
#include "logging.h"

#ifdef EXTRA_COUNTER_INFO
#include <sstream>
#endif

#include "public_counter_definitions_cl_gfx8.h"
#include "public_counter_definitions_cl_gfx9.h"
#include "public_counter_definitions_cl_gfx10.h"

#include "public_counter_definitions_cl_gfx8_asics.h"
#include "public_counter_definitions_cl_gfx9_asics.h"
#include "public_counter_definitions_cl_gfx10_asics.h"

#include "gpa_hw_counter_cl_gfx8.h"
#include "gpa_hw_counter_cl_gfx9.h"
#include "gpa_hw_counter_cl_gfx10.h"

#include "gpa_counter_generator_scheduler_manager.h"

GPA_CounterGeneratorCL::GPA_CounterGeneratorCL()
{
    GPA_CounterGeneratorBase::SetAllowedCounters(true, true, false);

    for (int gen = GDT_HW_GENERATION_FIRST_AMD; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(GPA_API_OPENCL, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GPA_Status GPA_CounterGeneratorCL::GeneratePublicCounters(GDT_HW_GENERATION    desired_generation,
                                                          GDT_HW_ASIC_TYPE     asic_type,
                                                          gpa_uint8            generate_asic_specific_counters,
                                                          GPA_DerivedCounters* public_counters)
{
    auto status = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;

    if (nullptr == public_counters)
    {
        status = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else if (public_counters->m_countersGenerated)
    {
        status = GPA_STATUS_OK;
    }
    else
    {
        public_counters->Clear();

        if (desired_generation == GDT_HW_GENERATION_VOLCANICISLAND)
        {
            AutoDefinePublicDerivedCountersCLGfx8(*public_counters);

            if (generate_asic_specific_counters)
            {
                clgfx8asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = GPA_STATUS_OK;
        }
        else if (desired_generation == GDT_HW_GENERATION_GFX9)
        {
            AutoDefinePublicDerivedCountersCLGfx9(*public_counters);

            if (generate_asic_specific_counters)
            {
                clgfx9asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = GPA_STATUS_OK;
        }
        else if (desired_generation == GDT_HW_GENERATION_GFX10)
        {
            AutoDefinePublicDerivedCountersCLGfx10(*public_counters);

            if (generate_asic_specific_counters)
            {
                clgfx10asics::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, *public_counters);
            }

            status = GPA_STATUS_OK;
        }
    }

    auto internal_status = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;

#ifdef AMDT_INTERNAL
    internal_status = GenerateInternalDerivedCounters(desired_generation, asic_type, generate_asic_specific_counters, public_counters);
#endif

    if (GPA_STATUS_OK == status)
    {
        public_counters->m_countersGenerated = true;
    }
    else
    {
        status = internal_status;
    }

    return status;
}

int GPA_CounterGeneratorCL::GetDriverGroupId(GDT_HW_GENERATION desired_generation, int blockIndex) const
{
    int result = blockIndex;

    if (GDT_HW_GENERATION_GFX9 == desired_generation)
    {
        // for GFX9, the driver has MC, SRBM at index 92, 93, but we don't have those groups for GFX9
        static const int GFX9_MC_BLOCK_INDEX = 92;

        if (blockIndex >= GFX9_MC_BLOCK_INDEX)
        {
            result += 2;
        }
    }
    else if (GDT_HW_GENERATION_SEAISLAND == desired_generation)
    {
        // for GFX7 (CI), the driver has TCS at index 79, but we don't have that group for GFX7
        static const int GFX9_TCS_BLOCK_INDEX = 79;

        if (blockIndex >= GFX9_TCS_BLOCK_INDEX)
        {
            result++;
        }
    }

    return result;
}

GPA_Status GPA_CounterGeneratorCL::GenerateHardwareCounters(GDT_HW_GENERATION     desired_generation,
                                                            GDT_HW_ASIC_TYPE      asic_type,
                                                            gpa_uint8             generate_asic_specific_counters,
                                                            GPA_HardwareCounters* hardware_counters)
{
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);

    if (nullptr == hardware_counters)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (hardware_counters->m_countersGenerated)
    {
        return GPA_STATUS_OK;
    }

    if (desired_generation == GDT_HW_GENERATION_VOLCANICISLAND)
    {
        hardware_counters->m_ppCounterGroupArray = countergfx8::cl_counter_group_array_gfx8;
        hardware_counters->m_pGroups             = countergfx8::hw_cl_groups_gfx8;
        hardware_counters->m_groupCount          = countergfx8::hw_cl_group_count_gfx8;
        hardware_counters->m_pSQCounterGroups    = countergfx8::hw_cl_sq_groups_gfx8;
        hardware_counters->m_sqGroupCount        = countergfx8::hw_cl_sq_group_count_gfx8;
        hardware_counters->m_pIsolatedGroups     = countergfx8::hw_cl_sq_isolated_groups_gfx8;
        hardware_counters->m_isolatedGroupCount  = countergfx8::hw_cl_sq_isolated_group_count_gfx8;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX9)
    {
        hardware_counters->m_ppCounterGroupArray = countergfx9::cl_counter_group_array_gfx9;
        hardware_counters->m_pGroups             = countergfx9::hw_cl_groups_gfx9;
        hardware_counters->m_groupCount          = countergfx9::hw_cl_group_count_gfx9;
        hardware_counters->m_pSQCounterGroups    = countergfx9::hw_cl_sq_groups_gfx9;
        hardware_counters->m_sqGroupCount        = countergfx9::hw_cl_sq_group_count_gfx9;
        hardware_counters->m_pIsolatedGroups     = countergfx9::hw_cl_sq_isolated_groups_gfx9;
        hardware_counters->m_isolatedGroupCount  = countergfx9::hw_cl_sq_isolated_group_count_gfx9;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX10)
    {
        hardware_counters->m_ppCounterGroupArray = countergfx10::cl_counter_group_array_gfx10;
        hardware_counters->m_pGroups             = countergfx10::hw_cl_groups_gfx10;
        hardware_counters->m_groupCount          = countergfx10::hw_cl_group_count_gfx10;
        hardware_counters->m_pSQCounterGroups    = countergfx10::hw_cl_sq_groups_gfx10;
        hardware_counters->m_sqGroupCount        = countergfx10::hw_cl_sq_group_count_gfx10;
        hardware_counters->m_pIsolatedGroups     = countergfx10::hw_cl_sq_isolated_groups_gfx10;
        hardware_counters->m_isolatedGroupCount  = countergfx10::hw_cl_sq_isolated_group_count_gfx10;
    }
    else
    {
        GPA_LogError("Unrecognized or unhandled hardware generation.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    // need to count total number of internal counters, since split into groups
    if (!hardware_counters->m_countersGenerated)
    {
        if (!GenerateInternalCounters(hardware_counters, desired_generation))
        {
            GPA_LogError("Unable to generate internal or whitelist counters.");
            hardware_counters->m_currentGroupUsedCounts.resize(0);
            return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
        }

        hardware_counters->m_countersGenerated = true;
    }

    // resize the counts that indicate how many counters from each group are being used
    unsigned int uGroupCount = hardware_counters->m_groupCount;
    hardware_counters->m_currentGroupUsedCounts.resize(uGroupCount);
    hardware_counters->block_instance_counters_index_cache_.clear();
    hardware_counters->gpa_hw_block_hardware_block_group_cache_.clear();
    hardware_counters->counter_hardware_info_map_.clear();
    return GPA_STATUS_OK;
}

bool GPA_CounterGeneratorCL::GenerateInternalCounters(GPA_HardwareCounters* hardware_counters, GDT_HW_GENERATION generation) const
{
    hardware_counters->m_counters.clear();
    GPA_HardwareCounterDescExt counter = {};

#if defined(_DEBUG) && defined(_WIN32) && defined(AMDT_INTERNAL)
    // Debug builds will generate a file that lists the counter names in a format that can be
    // easily copy/pasted into the GPUPerfAPIUnitTests project
    FILE* pFile = nullptr;
    fopen_s(&pFile, "HardwareCounterNamesCL.txt", "w");
#endif

    for (gpa_uint32 i = 0; i < hardware_counters->m_groupCount; i++)
    {
        GPA_HardwareCounterDesc* pClGroup         = (*(hardware_counters->m_ppCounterGroupArray + i));
        const int                numGroupCounters = static_cast<int>(hardware_counters->m_pGroups[i].m_numCounters);

        for (int j = 0; j < numGroupCounters; j++)
        {
            counter.m_pHardwareCounter = &(pClGroup[j]);
            counter.m_groupIndex       = i;
            counter.m_groupIdDriver    = GetDriverGroupId(generation, i);

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
            hardware_counters->m_counters.push_back(counter);
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

GPA_Status GPA_CounterGeneratorCL::GenerateSoftwareCounters(GDT_HW_GENERATION     desired_generation,
                                                            GDT_HW_ASIC_TYPE      asic_type,
                                                            gpa_uint8             generate_asic_specific_counters,
                                                            GPA_SoftwareCounters* software_counters)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);
    UNREFERENCED_PARAMETER(software_counters);
    return GPA_STATUS_OK;
}

GPA_Status GPA_CounterGeneratorCL::GenerateHardwareExposedCounters(GDT_HW_GENERATION     desired_generation,
                                                                   GDT_HW_ASIC_TYPE      asic_type,
                                                                   gpa_uint8             generate_asic_specific_counters,
                                                                   GPA_HardwareCounters* hardware_counters)
{
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);

    if (hardware_counters->m_hardwareExposedCountersGenerated)
    {
        return GPA_STATUS_OK;
    }

    if (desired_generation == GDT_HW_GENERATION_VOLCANICISLAND)
    {
        hardware_counters->m_ppHardwareExposedCounter         = countergfx8::cl_exposed_counters_group_array_gfx8;
        hardware_counters->m_pHardwareExposedCounterGroups    = countergfx8::hw_cl_exposed_counters_by_group_gfx8;
        hardware_counters->m_hardwareExposedCounterGroupCount = countergfx8::hw_cl_exposed_counters_group_count_gfx8;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX9)
    {
        hardware_counters->m_ppHardwareExposedCounter         = countergfx9::cl_exposed_counters_group_array_gfx9;
        hardware_counters->m_pHardwareExposedCounterGroups    = countergfx9::hw_cl_exposed_counters_by_group_gfx9;
        hardware_counters->m_hardwareExposedCounterGroupCount = countergfx9::hw_cl_exposed_counters_group_count_gfx9;
    }
    else if (desired_generation == GDT_HW_GENERATION_GFX10)
    {
        hardware_counters->m_ppHardwareExposedCounter         = countergfx10::cl_exposed_counters_group_array_gfx10;
        hardware_counters->m_pHardwareExposedCounterGroups    = countergfx10::hw_cl_exposed_counters_by_group_gfx10;
        hardware_counters->m_hardwareExposedCounterGroupCount = countergfx10::hw_cl_exposed_counters_group_count_gfx10;
    }
    else
    {
        GPA_LogError("Unrecognized or unhandled hardware generation.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    hardware_counters->m_hardwareExposedCountersGenerated = MapHardwareExposedCounter(hardware_counters);
    return hardware_counters->m_hardwareExposedCountersGenerated ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}
