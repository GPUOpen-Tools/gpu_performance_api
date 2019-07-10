//==============================================================================
// Copyright (c) 2016-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for CL counter generation
//==============================================================================

#include "GPACounterGeneratorCL.h"
#include "Logging.h"

#ifdef EXTRA_COUNTER_INFO
#include <sstream>
#endif

#include "PublicCounterDefsCLGfx8.h"
#include "PublicCounterDefsCLGfx9.h"
#include "PublicCounterDefsCLGfx10.h"

#include "PublicCounterDefsCLGfx8Asics.h"
#include "PublicCounterDefsCLGfx9Asics.h"
#include "PublicCounterDefsCLGfx10Asics.h"

#include "GPAHWCounterCLGfx8.h"
#include "GPAHWCounterCLGfx9.h"
#include "GPAHWCounterCLGfx10.h"

#include "GPACounterGeneratorSchedulerManager.h"

GPA_CounterGeneratorCL::GPA_CounterGeneratorCL()
{
    GPA_CounterGeneratorBase::SetAllowedCounters(true, true, false);

    for (int gen = GDT_HW_GENERATION_FIRST_AMD; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(GPA_API_OPENCL, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GPA_Status GPA_CounterGeneratorCL::GeneratePublicCounters(GDT_HW_GENERATION    desiredGeneration,
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
            AutoDefinePublicDerivedCountersCLGfx8(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                CLGfx8Asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
        }
        else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
        {
            AutoDefinePublicDerivedCountersCLGfx9(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                CLGfx9Asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
        }
        else if (desiredGeneration == GDT_HW_GENERATION_GFX10)
        {
            AutoDefinePublicDerivedCountersCLGfx10(*pPublicCounters);

            if (generateAsicSpecificCounters)
            {
                CLGfx10Asics::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, *pPublicCounters);
            }

            status = GPA_STATUS_OK;
        }
    }

    auto internalStatus = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;

#ifdef AMDT_INTERNAL
    internalStatus = GPA_LoadInternalCounters(GPA_API_OPENCL, desiredGeneration, asicType, generateAsicSpecificCounters, pPublicCounters);
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

int GPA_CounterGeneratorCL::GetDriverGroupId(GDT_HW_GENERATION desiredGeneration, int blockIndex) const
{
    int result = blockIndex;

    if (GDT_HW_GENERATION_GFX9 == desiredGeneration)
    {
        // for GFX9, the driver has MC, SRBM at index 92, 93, but we don't have those groups for GFX9
        static const int GFX9_MC_BLOCK_INDEX = 92;

        if (blockIndex >= GFX9_MC_BLOCK_INDEX)
        {
            result += 2;
        }
    }
    else if (GDT_HW_GENERATION_SEAISLAND == desiredGeneration)
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

GPA_Status GPA_CounterGeneratorCL::GenerateHardwareCounters(GDT_HW_GENERATION     desiredGeneration,
                                                            GDT_HW_ASIC_TYPE      asicType,
                                                            gpa_uint8             generateAsicSpecificCounters,
                                                            GPA_HardwareCounters* pHardwareCounters)
{
    UNREFERENCED_PARAMETER(asicType);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);

    if (desiredGeneration == GDT_HW_GENERATION_VOLCANICISLAND)
    {
        pHardwareCounters->m_ppCounterGroupArray = CounterGfx8::CLCounterGroupArrayGfx8;
        pHardwareCounters->m_pGroups             = CounterGfx8::HWCLGroupsGfx8;
        pHardwareCounters->m_groupCount          = CounterGfx8::HWCLGroupCountGfx8;
        pHardwareCounters->m_pSQCounterGroups    = CounterGfx8::HWCLSQGroupsGfx8;
        pHardwareCounters->m_sqGroupCount        = CounterGfx8::HWCLSQGroupCountGfx8;
        pHardwareCounters->m_pIsolatedGroups     = CounterGfx8::HWCLSQIsolatedGroupsGfx8;
        pHardwareCounters->m_isolatedGroupCount  = CounterGfx8::HWCLSQIsolatedGroupCountGfx8;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
    {
        pHardwareCounters->m_ppCounterGroupArray = CounterGfx9::CLCounterGroupArrayGfx9;
        pHardwareCounters->m_pGroups             = CounterGfx9::HWCLGroupsGfx9;
        pHardwareCounters->m_groupCount          = CounterGfx9::HWCLGroupCountGfx9;
        pHardwareCounters->m_pSQCounterGroups    = CounterGfx9::HWCLSQGroupsGfx9;
        pHardwareCounters->m_sqGroupCount        = CounterGfx9::HWCLSQGroupCountGfx9;
        pHardwareCounters->m_pIsolatedGroups     = CounterGfx9::HWCLSQIsolatedGroupsGfx9;
        pHardwareCounters->m_isolatedGroupCount  = CounterGfx9::HWCLSQIsolatedGroupCountGfx9;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX10)
    {
        pHardwareCounters->m_ppCounterGroupArray = CounterGfx10::CLCounterGroupArrayGfx10;
        pHardwareCounters->m_pGroups             = CounterGfx10::HWCLGroupsGfx10;
        pHardwareCounters->m_groupCount          = CounterGfx10::HWCLGroupCountGfx10;
        pHardwareCounters->m_pSQCounterGroups    = CounterGfx10::HWCLSQGroupsGfx10;
        pHardwareCounters->m_sqGroupCount        = CounterGfx10::HWCLSQGroupCountGfx10;
        pHardwareCounters->m_pIsolatedGroups     = CounterGfx10::HWCLSQIsolatedGroupsGfx10;
        pHardwareCounters->m_isolatedGroupCount  = CounterGfx10::HWCLSQIsolatedGroupCountGfx10;
    }
    else
    {
        GPA_LogError("Unrecognized or unhandled hardware generation.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    // need to count total number of internal counters, since split into groups
    if (!pHardwareCounters->m_countersGenerated)
    {
        if (!GenerateInternalCounters(pHardwareCounters, desiredGeneration))
        {
            GPA_LogError("Unable to generate internal or whitelist counters.");
            pHardwareCounters->m_currentGroupUsedCounts.resize(0);
            return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
        }

        pHardwareCounters->m_countersGenerated = true;
    }

    // resize the counts that indicate how many counters from each group are being used
    unsigned int uGroupCount = pHardwareCounters->m_groupCount;
    pHardwareCounters->m_currentGroupUsedCounts.resize(uGroupCount);

    return GPA_STATUS_OK;
}

bool GPA_CounterGeneratorCL::GenerateInternalCounters(GPA_HardwareCounters* pHardwareCounters, GDT_HW_GENERATION generation) const
{
    pHardwareCounters->m_counters.clear();
    GPA_HardwareCounterDescExt counter = {};

#if defined(_DEBUG) && defined(_WIN32) && defined(AMDT_INTERNAL)
    // Debug builds will generate a file that lists the counter names in a format that can be
    // easily copy/pasted into the GPUPerfAPIUnitTests project
    FILE* pFile = nullptr;
    fopen_s(&pFile, "HardwareCounterNamesCL.txt", "w");
#endif

    for (gpa_uint32 i = 0; i < pHardwareCounters->m_groupCount; i++)
    {
        GPA_HardwareCounterDesc* pClGroup         = (*(pHardwareCounters->m_ppCounterGroupArray + i));
        const int                numGroupCounters = static_cast<int>(pHardwareCounters->m_pGroups[i].m_numCounters);

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
            pHardwareCounters->m_counters.push_back(counter);
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

GPA_Status GPA_CounterGeneratorCL::GenerateSoftwareCounters(GDT_HW_GENERATION     desiredGeneration,
                                                            GDT_HW_ASIC_TYPE      asicType,
                                                            gpa_uint8             generateAsicSpecificCounters,
                                                            GPA_SoftwareCounters* pSoftwareCounters)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(asicType);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);
    UNREFERENCED_PARAMETER(pSoftwareCounters);
    return GPA_STATUS_OK;
}

GPA_Status GPA_CounterGeneratorCL::GenerateHardwareExposedCounters(GDT_HW_GENERATION     desiredGeneration,
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
        pHardwareCounters->m_ppHardwareExposedCounter         = CounterGfx8::CLExposedCountersGroupArrayGfx8;
        pHardwareCounters->m_pHardwareExposedCounterGroups    = CounterGfx8::HWCLExposedCountersByGroupGfx8;
        pHardwareCounters->m_hardwareExposedCounterGroupCount = CounterGfx8::HWCLExposedCountersGroupCountGfx8;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX9)
    {
        pHardwareCounters->m_ppHardwareExposedCounter         = CounterGfx9::CLExposedCountersGroupArrayGfx9;
        pHardwareCounters->m_pHardwareExposedCounterGroups    = CounterGfx9::HWCLExposedCountersByGroupGfx9;
        pHardwareCounters->m_hardwareExposedCounterGroupCount = CounterGfx9::HWCLExposedCountersGroupCountGfx9;
    }
    else if (desiredGeneration == GDT_HW_GENERATION_GFX10)
    {
        pHardwareCounters->m_ppHardwareExposedCounter         = CounterGfx10::CLExposedCountersGroupArrayGfx10;
        pHardwareCounters->m_pHardwareExposedCounterGroups    = CounterGfx10::HWCLExposedCountersByGroupGfx10;
        pHardwareCounters->m_hardwareExposedCounterGroupCount = CounterGfx10::HWCLExposedCountersGroupCountGfx10;
    }
    else
    {
        GPA_LogError("Unrecognized or unhandled hardware generation.");
        return GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    pHardwareCounters->m_hardwareExposedCountersGenerated = MapHardwareExposedCounter(pHardwareCounters);
    return pHardwareCounters->m_hardwareExposedCountersGenerated ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
}
