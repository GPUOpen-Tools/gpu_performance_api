//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for HSA counter generation
//==============================================================================

#include "GPACounterGeneratorHSA.h"
#include "Logging.h"

#ifdef EXTRA_COUNTER_INFO
    #include <sstream>
#endif

#include "PublicCounterDefsHSAGfx8.h"
#include "PublicCounterDefsHSAGfx9.h"

#include "PublicCounterDefsHSAGfx8Asics.h"
#include "PublicCounterDefsHSAGfx9Asics.h"

#include "InternalCountersHSAGfx8.h"
#include "InternalCountersHSAGfx9.h"

GPA_CounterGeneratorHSA::GPA_CounterGeneratorHSA()
{
    GPA_CounterGeneratorBase::SetAllowedCounters(true, true, false);

    for (int gen = GDT_HW_GENERATION_VOLCANICISLAND; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(GPA_API_ROCM, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GPA_Status GPA_CounterGeneratorHSA::GeneratePublicCounters(
    GDT_HW_GENERATION desiredGeneration,
    GDT_HW_ASIC_TYPE asicType,
    gpa_uint8 generateAsicSpecificCounters,
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
        if (desiredGeneration == GDT_HW_GENERATION_SOUTHERNISLAND)
        {
            GPA_LogError("HSA is not supported on Gfx6 hardware.");
        }
        else if (desiredGeneration == GDT_HW_GENERATION_SEAISLAND)
        {
            GPA_LogError("HSA is not supported on Gfx7 hardware.");
        }
        else if (desiredGeneration == GDT_HW_GENERATION_VOLCANICISLAND)
        {
            AutoDefinePublicDerivedCountersHSAGfx8(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                HSAGfx8Asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
        }
        else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
        {
            AutoDefinePublicDerivedCountersHSAGfx9(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                HSAGfx9Asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
        }
    }

    auto internalStatus = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;

#ifdef AMDT_INTERNAL
    internalStatus = GPA_LoadInternalCounters(GPA_API_ROCM, desiredGeneration,asicType, generateAsicSpecificCounters, pPublicCounters);
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

GPA_Status GPA_CounterGeneratorHSA::GenerateHardwareCounters(
    GDT_HW_GENERATION desiredGeneration,
    GDT_HW_ASIC_TYPE asicType,
    gpa_uint8 generateAsicSpecificCounters,
    GPA_HardwareCounters* pHardwareCounters)
{
    UNREFERENCED_PARAMETER(asicType);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);

    if (desiredGeneration == GDT_HW_GENERATION_SOUTHERNISLAND)
    {
        // HSA does not support Gfx6 hardware
        GPA_LogError("HSA is not supported on Gfx6 hardware.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_SEAISLAND)
    {
        // HSA does not support Gfx7 hardware
        GPA_LogError("HSA is not supported on Gfx7 hardware.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_VOLCANICISLAND)
    {
        pHardwareCounters->m_ppCounterGroupArray = HSACounterGroupArrayGfx8;
        pHardwareCounters->m_pGroups             = HWHSAGroupsGfx8;
        pHardwareCounters->m_groupCount          = HWHSAGroupCountGfx8;
        pHardwareCounters->m_pSQCounterGroups    = HWHSASQGroupsGfx8;
        pHardwareCounters->m_sqGroupCount        = HWHSASQGroupCountGfx8;
        pHardwareCounters->m_pIsolatedGroups     = HWHSASQIsolatedGroupsGfx8;
        pHardwareCounters->m_isolatedGroupCount  = HWHSASQIsolatedGroupCountGfx8;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
    {
        pHardwareCounters->m_ppCounterGroupArray = HSACounterGroupArrayGfx9;
        pHardwareCounters->m_pGroups             = HWHSAGroupsGfx9;
        pHardwareCounters->m_groupCount          = HWHSAGroupCountGfx9;
        pHardwareCounters->m_pSQCounterGroups    = HWHSASQGroupsGfx9;
        pHardwareCounters->m_sqGroupCount        = HWHSASQGroupCountGfx9;
        pHardwareCounters->m_pIsolatedGroups     = HWHSASQIsolatedGroupsGfx9;
        pHardwareCounters->m_isolatedGroupCount  = HWHSASQIsolatedGroupCountGfx9;
    }
    else
    {
        GPA_LogError("Unrecognized or unhandled hardware generation.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    // need to count total number of internal counters, since split into groups
    if (!pHardwareCounters->m_countersGenerated)
    {
        pHardwareCounters->m_counters.clear();

        GPA_HardwareCounterDescExt counter;
#if defined(_DEBUG) && defined(_WIN32) && defined(AMDT_INTERNAL)
        // Debug builds will generate a file that lists the counter names in a format that can be
        // easily copy/pasted into the GPUPerfAPIUnitTests project
        FILE* pFile = nullptr;
        fopen_s(&pFile, "HardwareCounterNamesHSA.txt", "w");
#endif

        for (gpa_uint32 i = 0; i < pHardwareCounters->m_groupCount; i++)
        {
            // for each group
            GPA_HardwareCounterDesc* pGroup = (*(pHardwareCounters->m_ppCounterGroupArray + i));

            const int numGroupCounters = (int)pHardwareCounters->m_pGroups[i].m_numCounters;

            for (int j = 0; j < numGroupCounters; j++)
            {
                // for each internal counter
                counter.m_pHardwareCounter = &(pGroup[j]);
                counter.m_groupIndex      = i;
                counter.m_groupIdDriver = i;
                counter.m_counterIdDriver = 0;

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
            }
        }

#if defined(_DEBUG) && defined(_WIN32) && defined(AMDT_INTERNAL)

        if (nullptr != pFile)
        {
            fclose(pFile);
        }

#endif

        pHardwareCounters->m_countersGenerated = true;
    }

    // resize the counts that indicate how many counters from each group are being used
    unsigned int uGroupCount = pHardwareCounters->m_groupCount;
    pHardwareCounters->m_currentGroupUsedCounts.resize(uGroupCount);

    return GPA_STATUS_OK;
}

GPA_Status GPA_CounterGeneratorHSA::GenerateSoftwareCounters(
    GDT_HW_GENERATION desiredGeneration,
    GDT_HW_ASIC_TYPE asicType,
    gpa_uint8 generateAsicSpecificCounters,
    GPA_SoftwareCounters* pSoftwareCounters)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(asicType);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);
    UNREFERENCED_PARAMETER(pSoftwareCounters);
    return GPA_STATUS_OK;
}
