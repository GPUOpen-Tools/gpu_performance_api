//==============================================================================
// Copyright (c) 2012-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit Tests for ROCm Counter Generator
//==============================================================================

#include "CounterGeneratorTests.h"
#include "GPUPerfAPITypes.h"
#include "GPACounter.h"

#include "counters/PublicDerivedCountersHSAGfx8.h"
#include "counters/PublicDerivedCountersHSAGfx9.h"

#ifdef AMDT_INTERNAL
#include "GPAHWCounterHSAGfx8.h"
#include "GPAHWCounterHSAGfx9.h"
#endif

static void GetExpectedCountersForGeneration(GPA_Hw_Generation gen, std::vector<const char*>& counterNames)
{
    counterNames.clear();

    const GPACounterDesc* pPublicCounters    = nullptr;
    size_t                publicCounterCount = 0;

    GPA_CounterGroupDesc*     pHardwareGroups    = nullptr;
    GPA_HardwareCounterDesc** ppHardwareCounters = nullptr;
    unsigned int              hwGroupCount       = 0;

    switch (gen)
    {
    case GPA_HW_GENERATION_GFX8:
        pPublicCounters    = HSAGFX8_PUBLIC_COUNTERS;
        publicCounterCount = HSAGFX8_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
        pHardwareGroups    = CounterGfx8::HWHSAGroupsGfx8;
        hwGroupCount       = CounterGfx8::HWHSAGroupCountGfx8;
        ppHardwareCounters = CounterGfx8::HSACounterGroupArrayGfx8;
#endif
        break;

    case GPA_HW_GENERATION_GFX9:
        pPublicCounters    = HSAGFX9_PUBLIC_COUNTERS;
        publicCounterCount = HSAGFX9_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
        pHardwareGroups    = CounterGfx9::HWHSAGroupsGfx9;
        hwGroupCount       = CounterGfx9::HWHSAGroupCountGfx9;
        ppHardwareCounters = CounterGfx9::HSACounterGroupArrayGfx9;
#endif
        break;

    default:
        break;
    }

    for (size_t i = 0; i < publicCounterCount; i++)
    {
        counterNames.push_back(pPublicCounters[i].m_pName);
    }

    // Optionally, get internal derived counters
    const GPACounterDesc* pInternalDerivedCounters    = nullptr;
    size_t                internalDerivedCounterCount = 0;

#ifdef AMDT_INTERNAL
    GPA_GetInternalDerivedCounters(GPA_API_ROCM, gen, &pInternalDerivedCounters, &internalDerivedCounterCount);
#endif

    for (size_t i = 0; i < internalDerivedCounterCount; i++)
    {
        counterNames.push_back(pInternalDerivedCounters[i].m_pName);
    }

    for (unsigned int i = 0; i < hwGroupCount; i++)
    {
        for (unsigned int j = 0; j < pHardwareGroups[i].m_numCounters; j++)
        {
            counterNames.push_back(ppHardwareCounters[i][j].m_pName);
        }
    }
}

// Test the ROCm counter names on all supported hardware
TEST(CounterDLLTests, ROCmCounterNames)
{
    VerifyHardwareNotSupported(GPA_API_ROCM, gDevIdUnknown, FALSE);
    VerifyHardwareNotSupported(GPA_API_ROCM, gDevIdSI, FALSE);
    VerifyHardwareNotSupported(GPA_API_ROCM, gDevIdCI, FALSE);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_ROCM, gDevIdVI, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_ROCM, gDevIdGfx9, FALSE, counterNames);
}

// Test the ROCm counter names on all generations
TEST(CounterDLLTests, ROCmCounterNamesByGeneration)
{
    VerifyHardwareNotSupported(GPA_API_ROCM, GPA_HW_GENERATION_NVIDIA, FALSE);
    VerifyHardwareNotSupported(GPA_API_ROCM, GPA_HW_GENERATION_INTEL, FALSE);
    VerifyHardwareNotSupported(GPA_API_ROCM, GPA_HW_GENERATION_GFX6, FALSE);
    VerifyHardwareNotSupported(GPA_API_ROCM, GPA_HW_GENERATION_GFX7, FALSE);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_ROCM, GPA_HW_GENERATION_GFX8, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_ROCM, GPA_HW_GENERATION_GFX9, FALSE, counterNames);
}
