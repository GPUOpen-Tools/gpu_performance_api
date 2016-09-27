//==============================================================================
// Copyright (c) 2012-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit Tests for HSA Counter Generator
//==============================================================================

#include "CounterGeneratorTests.h"
#include "GPUPerfAPITypes-Private.h"
#include "GPAInternalCounter.h"

#include "counters/PublicCountersHSAGfx7.h"
#include "counters/PublicCountersHSAGfx8.h"

#ifdef GDT_INTERNAL
    #include "InternalCountersHSAGfx7.h"
    #include "InternalCountersHSAGfx8.h"
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

        case GPA_HW_GENERATION_SEAISLAND:
            pPublicCounters = HSAGFX7_PUBLIC_COUNTERS;
            publicCounterCount = HSAGFX7_PUBLIC_COUNTER_COUNT;
#ifdef GDT_INTERNAL
            pHardwareGroups = HWHSAGroupsGfx7;
            hwGroupCount = HWHSAGroupCountGfx7;
            ppHardwareCounters = HSACounterGroupArrayGfx7;
#endif
            break;

        case GPA_HW_GENERATION_VOLCANICISLAND:
            pPublicCounters = HSAGFX8_PUBLIC_COUNTERS;
            publicCounterCount = HSAGFX8_PUBLIC_COUNTER_COUNT;
#ifdef GDT_INTERNAL
            pHardwareGroups = HWHSAGroupsGfx8;
            hwGroupCount = HWHSAGroupCountGfx8;
            ppHardwareCounters = HSACounterGroupArrayGfx8;
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
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_SEAISLAND, counterNames);
    VerifyCounterNames(GPA_API_HSA, gDevIdCI, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_VOLCANICISLAND, counterNames);
    VerifyCounterNames(GPA_API_HSA, gDevIdVI, counterNames);
}

// Test the HSA counter names on all generations
TEST(CounterDLLTests, HSACounterNamesByGeneration)
{
    VerifyHardwareNotSupported(GPA_API_HSA, GPA_HW_GENERATION_NVIDIA);
    VerifyHardwareNotSupported(GPA_API_HSA, GPA_HW_GENERATION_INTEL);
    VerifyHardwareNotSupported(GPA_API_HSA, GPA_HW_GENERATION_SOUTHERNISLAND);
    std::vector<const char*> counterNames;

    GetExpectedCountersForGeneration(GPA_HW_GENERATION_SEAISLAND, counterNames);
    VerifyCounterNames(GPA_API_HSA, GPA_HW_GENERATION_SEAISLAND, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_VOLCANICISLAND, counterNames);
    VerifyCounterNames(GPA_API_HSA, GPA_HW_GENERATION_VOLCANICISLAND, counterNames);
}
