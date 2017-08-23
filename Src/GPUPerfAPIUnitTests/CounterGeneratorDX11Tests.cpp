//==============================================================================
// Copyright (c) 2012-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit Tests for DX11 Counter Generator
//==============================================================================


#include "CounterGeneratorTests.h"
#include "GPUPerfAPITypes.h"
#include "GPAInternalCounter.h"

#include "counters/PublicCountersDX11Gfx6.h"
#include "counters/PublicCountersDX11Gfx7.h"
#include "counters/PublicCountersDX11Gfx8.h"
#include "counters/PublicCountersDX11Gfx9.h"

#include "counters/SWCountersDX11.h"

#ifdef AMDT_INTERNAL
    #include "InternalCountersDX11Gfx6.h"
    #include "InternalCountersDX11Gfx7.h"
    #include "InternalCountersDX11Gfx8.h"
    #include "InternalCountersDX11Gfx9.h"
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

        case GPA_HW_GENERATION_GFX6:
            pPublicCounters = DX11GFX6_PUBLIC_COUNTERS;
            publicCounterCount = DX11GFX6_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWDX11GroupsGfx6;
            hwGroupCount = HWDX11GroupCountGfx6;
            ppHardwareCounters = DX11CounterGroupArrayGfx6;
#endif
            break;

        case GPA_HW_GENERATION_GFX7:
            pPublicCounters = DX11GFX7_PUBLIC_COUNTERS;
            publicCounterCount = DX11GFX7_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWDX11GroupsGfx7;
            hwGroupCount = HWDX11GroupCountGfx7;
            ppHardwareCounters = DX11CounterGroupArrayGfx7;
#endif
            break;

        case GPA_HW_GENERATION_GFX8:
            pPublicCounters = DX11GFX8_PUBLIC_COUNTERS;
            publicCounterCount = DX11GFX8_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWDX11GroupsGfx8;
            hwGroupCount = HWDX11GroupCountGfx8;
            ppHardwareCounters = DX11CounterGroupArrayGfx8;
#endif
            break;

        case GPA_HW_GENERATION_GFX9:
            pPublicCounters = DX11GFX9_PUBLIC_COUNTERS;
            publicCounterCount = DX11GFX9_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWDX11GroupsGfx9;
            hwGroupCount = HWDX11GroupCountGfx9;
            ppHardwareCounters = DX11CounterGroupArrayGfx9;
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

    for (size_t i = 0; i < DX11SW_COUNTER_COUNT; i++)
    {
        counterNames.push_back(DX11SW_COUNTERS[i].m_pName);
    }

    if (GPA_HW_GENERATION_NVIDIA == gen || GPA_HW_GENERATION_INTEL == gen)
    {
        counterNames[0] = "GPUTime";
    }
}

// Test the DX11 counter names on all supported hardware
TEST(CounterDLLTests, DX11CounterNames)
{
    VerifyHardwareNotSupported(GPA_API_DIRECTX_11, gDevIdUnknown);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX6, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_11, gDevIdSI, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX7, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_11, gDevIdCI, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_11, gDevIdVI, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_11, gDevIdGfx9, counterNames);
}

// Test the DX11 counter names on all generations
TEST(CounterDLLTests, DX11CounterNamesByGeneration)
{
    VerifyHardwareNotSupported(GPA_API_DIRECTX_11, GPA_HW_GENERATION_NONE);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_NVIDIA, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_11, GPA_HW_GENERATION_NVIDIA, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_INTEL, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_11, GPA_HW_GENERATION_INTEL, counterNames);

    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX6, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_11, GPA_HW_GENERATION_GFX6, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX7, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_11, GPA_HW_GENERATION_GFX7, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_11, GPA_HW_GENERATION_GFX8, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_11, GPA_HW_GENERATION_GFX9, counterNames);
}
