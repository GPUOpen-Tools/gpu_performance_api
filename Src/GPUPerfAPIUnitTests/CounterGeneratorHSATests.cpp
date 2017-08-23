//==============================================================================
// Copyright (c) 2012-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit Tests for HSA Counter Generator
//==============================================================================

#include "CounterGeneratorTests.h"
#include "GPUPerfAPITypes.h"
#include "GPAInternalCounter.h"

#include "counters/PublicCountersHSAGfx7.h"
#include "counters/PublicCountersHSAGfx8.h"
#include "counters/PublicCountersHSAGfx9.h"

#ifdef AMDT_INTERNAL
    #include "InternalCountersHSAGfx7.h"
    #include "InternalCountersHSAGfx8.h"
    #include "InternalCountersHSAGfx9.h"
#endif

static void GetExpectedCountersForGeneration(GPA_HW_GENERATION gen, std::vector<const char*>& counterNames)
{
    counterNames.clear();

    const GPACounterDesc* pPublicCounters = nullptr;
    size_t publicCounterCount = 0;

    GPA_CounterGroupDesc* pHardwareGroups = nullptr;
    GPA_HardwareCounterDesc** ppHardwareCounters = nullptr;
    unsigned int hwGroupCount = 0;

    switch (gen)
    {

        case GPA_HW_GENERATION_GFX7:
            pPublicCounters = HSAGFX7_PUBLIC_COUNTERS;
            publicCounterCount = HSAGFX7_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWHSAGroupsGfx7;
            hwGroupCount = HWHSAGroupCountGfx7;
            ppHardwareCounters = HSACounterGroupArrayGfx7;
#endif
            break;

        case GPA_HW_GENERATION_GFX8:
            pPublicCounters = HSAGFX8_PUBLIC_COUNTERS;
            publicCounterCount = HSAGFX8_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWHSAGroupsGfx8;
            hwGroupCount = HWHSAGroupCountGfx8;
            ppHardwareCounters = HSACounterGroupArrayGfx8;
#endif
            break;

        case GPA_HW_GENERATION_GFX9:
            pPublicCounters = HSAGFX9_PUBLIC_COUNTERS;
            publicCounterCount = HSAGFX9_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWHSAGroupsGfx9;
            hwGroupCount = HWHSAGroupCountGfx9;
            ppHardwareCounters = HSACounterGroupArrayGfx9;
#endif
            break;
    }

    for (size_t i = 0; i < publicCounterCount; i++)
    {
        counterNames.push_back(pPublicCounters[i].m_pName);
    }

    for (unsigned int i = 0; i < hwGroupCount; i++)
    {
        for (unsigned int j = 0; j < pHardwareGroups[i].m_numCounters; j++)
        {
            counterNames.push_back(ppHardwareCounters[i][j].m_pName);
        }
    }
}

// Test the HSA counter names on all supported hardware
TEST(CounterDLLTests, HSACounterNames)
{
    VerifyHardwareNotSupported(GPA_API_HSA, gDevIdUnknown);
    VerifyHardwareNotSupported(GPA_API_HSA, gDevIdSI);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX7, counterNames);
    VerifyCounterNames(GPA_API_HSA, gDevIdCI, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_HSA, gDevIdVI, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_HSA, gDevIdGfx9, counterNames);
}

// Test the HSA counter names on all generations
TEST(CounterDLLTests, HSACounterNamesByGeneration)
{
    VerifyHardwareNotSupported(GPA_API_HSA, GPA_HW_GENERATION_NVIDIA);
    VerifyHardwareNotSupported(GPA_API_HSA, GPA_HW_GENERATION_INTEL);
    VerifyHardwareNotSupported(GPA_API_HSA, GPA_HW_GENERATION_GFX6);
    std::vector<const char*> counterNames;

    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX7, counterNames);
    VerifyCounterNames(GPA_API_HSA, GPA_HW_GENERATION_GFX7, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_HSA, GPA_HW_GENERATION_GFX8, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_HSA, GPA_HW_GENERATION_GFX9, counterNames);
}
