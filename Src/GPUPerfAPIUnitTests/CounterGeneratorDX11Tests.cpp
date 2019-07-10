//==============================================================================
// Copyright (c) 2012-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit Tests for DX11 Counter Generator
//==============================================================================

#include "CounterGeneratorTests.h"
#include "GPUPerfAPITypes.h"
#include "GPACounter.h"

#include "counters/PublicDerivedCountersDX11Gfx8.h"
#include "counters/PublicDerivedCountersDX11Gfx9.h"
#include "counters/PublicDerivedCountersDX11Gfx10.h"

#ifdef AMDT_INTERNAL
#include "GPAHWCounterDX11Gfx8.h"
#include "GPAHWCounterDX11Gfx9.h"
#include "GPAHWCounterDX11Gfx10.h"
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
        pPublicCounters    = DX11GFX8_PUBLIC_COUNTERS;
        publicCounterCount = DX11GFX8_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
        pHardwareGroups    = CounterGfx8::HWDX11GroupsGfx8;
        hwGroupCount       = CounterGfx8::HWDX11GroupCountGfx8;
        ppHardwareCounters = CounterGfx8::DX11CounterGroupArrayGfx8;
#endif
        break;

    case GPA_HW_GENERATION_GFX9:
        pPublicCounters    = DX11GFX9_PUBLIC_COUNTERS;
        publicCounterCount = DX11GFX9_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
        pHardwareGroups    = CounterGfx9::HWDX11GroupsGfx9;
        hwGroupCount       = CounterGfx9::HWDX11GroupCountGfx9;
        ppHardwareCounters = CounterGfx9::DX11CounterGroupArrayGfx9;
#endif
        break;

    case GPA_HW_GENERATION_GFX10:
        pPublicCounters    = DX11GFX10_PUBLIC_COUNTERS;
        publicCounterCount = DX11GFX10_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
        pHardwareGroups    = CounterGfx10::HWDX11GroupsGfx10;
        hwGroupCount       = CounterGfx10::HWDX11GroupCountGfx10;
        ppHardwareCounters = CounterGfx10::DX11CounterGroupArrayGfx10;
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
    GPA_GetInternalDerivedCounters(GPA_API_DIRECTX_11, gen, &pInternalDerivedCounters, &internalDerivedCounterCount);
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

// Test the DX11 counter names on all supported hardware
TEST(CounterDLLTests, DX11CounterNames)
{
    VerifyHardwareNotSupported(GPA_API_DIRECTX_11, gDevIdUnknown, FALSE);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_11, gDevIdVI, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_11, gDevIdGfx9, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX10, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_11, gDevIdGfx10, FALSE, counterNames);
}

// Test the DX11 counter names on all generations
TEST(CounterDLLTests, DX11CounterNamesByGeneration)
{
    VerifyHardwareNotSupported(GPA_API_DIRECTX_11, GPA_HW_GENERATION_NONE, FALSE);
    VerifyHardwareNotSupported(GPA_API_DIRECTX_11, GPA_HW_GENERATION_NVIDIA, FALSE);
    VerifyHardwareNotSupported(GPA_API_DIRECTX_11, GPA_HW_GENERATION_INTEL, FALSE);
    VerifyHardwareNotSupported(GPA_API_DIRECTX_11, GPA_HW_GENERATION_GFX6, FALSE);
    VerifyHardwareNotSupported(GPA_API_DIRECTX_11, GPA_HW_GENERATION_GFX7, FALSE);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_11, GPA_HW_GENERATION_GFX8, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_11, GPA_HW_GENERATION_GFX9, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX10, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_11, GPA_HW_GENERATION_GFX10, FALSE, counterNames);
}
