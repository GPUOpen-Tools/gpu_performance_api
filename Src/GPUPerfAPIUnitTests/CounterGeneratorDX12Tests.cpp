//==============================================================================
// Copyright (c) 2012-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit Tests for DX12 Counter Generator
//==============================================================================

#include "CounterGeneratorTests.h"
#include "GPUPerfAPITypes.h"
#include "GPACounter.h"

#include "counters/GPACounterDesc.h"

#include "counters/PublicDerivedCountersDX12Gfx8.h"
#include "counters/PublicDerivedCountersDX12Gfx9.h"
#include "counters/PublicDerivedCountersDX12Gfx10.h"

#ifdef AMDT_INTERNAL
#include "GPAHWCounterDX12Gfx8.h"
#include "GPAHWCounterDX12Gfx9.h"
#include "GPAHWCounterDX12Gfx10.h"
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
        pPublicCounters    = DX12GFX8_PUBLIC_COUNTERS;
        publicCounterCount = DX12GFX8_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
        pHardwareGroups    = CounterGfx8::HWDX12GroupsGfx8;
        hwGroupCount       = CounterGfx8::HWDX12GroupCountGfx8;
        ppHardwareCounters = CounterGfx8::DX12CounterGroupArrayGfx8;
#endif
        break;

    case GPA_HW_GENERATION_GFX9:
        pPublicCounters    = DX12GFX9_PUBLIC_COUNTERS;
        publicCounterCount = DX12GFX9_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
        pHardwareGroups    = CounterGfx9::HWDX12GroupsGfx9;
        hwGroupCount       = CounterGfx9::HWDX12GroupCountGfx9;
        ppHardwareCounters = CounterGfx9::DX12CounterGroupArrayGfx9;
#endif
        break;

    case GPA_HW_GENERATION_GFX10:
        pPublicCounters    = DX12GFX10_PUBLIC_COUNTERS;
        publicCounterCount = DX12GFX10_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
        pHardwareGroups    = CounterGfx10::HWDX12GroupsGfx10;
        hwGroupCount       = CounterGfx10::HWDX12GroupCountGfx10;
        ppHardwareCounters = CounterGfx10::DX12CounterGroupArrayGfx10;
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
    GPA_GetInternalDerivedCounters(GPA_API_DIRECTX_12, gen, &pInternalDerivedCounters, &internalDerivedCounterCount);
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

// Test the DX12 counter names on all supported hardware
TEST(CounterDLLTests, DX12CounterNames)
{
    VerifyHardwareNotSupported(GPA_API_DIRECTX_12, gDevIdUnknown, FALSE);
    VerifyHardwareNotSupported(GPA_API_DIRECTX_12, gDevIdSI, FALSE);
    VerifyHardwareNotSupported(GPA_API_DIRECTX_12, gDevIdCI, FALSE);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_12, gDevIdVI, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_12, gDevIdGfx9, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX10, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_12, gDevIdGfx10, FALSE, counterNames);
}

// Test the DX12 counter names on all generations
TEST(CounterDLLTests, DX12CounterNamesByGeneration)
{
    VerifyHardwareNotSupported(GPA_API_DIRECTX_12, GPA_HW_GENERATION_NONE, FALSE);
    VerifyHardwareNotSupported(GPA_API_DIRECTX_12, GPA_HW_GENERATION_GFX6, FALSE);
    VerifyHardwareNotSupported(GPA_API_DIRECTX_12, GPA_HW_GENERATION_NVIDIA, FALSE);
    VerifyHardwareNotSupported(GPA_API_DIRECTX_12, GPA_HW_GENERATION_INTEL, FALSE);
    VerifyHardwareNotSupported(GPA_API_DIRECTX_12, GPA_HW_GENERATION_GFX7, FALSE);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_12, GPA_HW_GENERATION_GFX8, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_12, GPA_HW_GENERATION_GFX9, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX10, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_12, GPA_HW_GENERATION_GFX10, FALSE, counterNames);
}
