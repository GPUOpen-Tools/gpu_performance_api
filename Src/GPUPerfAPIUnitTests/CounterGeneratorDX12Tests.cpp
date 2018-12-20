//==============================================================================
// Copyright (c) 2012-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit Tests for DX12 Counter Generator
//==============================================================================


#include "CounterGeneratorTests.h"
#include "GPUPerfAPITypes.h"
#include "GPAInternalCounter.h"

#include "counters/GPACounterDesc.h"

#include "counters/PublicDerivedCountersDX12Gfx7.h"
#include "counters/PublicDerivedCountersDX12Gfx8.h"
#include "counters/PublicDerivedCountersDX12Gfx9.h"

#ifdef AMDT_INTERNAL
    #include "InternalCountersDX12Gfx7.h"
    #include "InternalCountersDX12Gfx8.h"
    #include "InternalCountersDX12Gfx9.h"
#endif

static void GetExpectedCountersForGeneration(GPA_Hw_Generation gen, std::vector<const char*>& counterNames)
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
            pPublicCounters = DX12GFX7_PUBLIC_COUNTERS;
            publicCounterCount = DX12GFX7_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWDX12GroupsGfx7;
            hwGroupCount = HWDX12GroupCountGfx7;
            ppHardwareCounters = DX12CounterGroupArrayGfx7;
#endif
            break;

        case GPA_HW_GENERATION_GFX8:
            pPublicCounters = DX12GFX8_PUBLIC_COUNTERS;
            publicCounterCount = DX12GFX8_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWDX12GroupsGfx8;
            hwGroupCount = HWDX12GroupCountGfx8;
            ppHardwareCounters = DX12CounterGroupArrayGfx8;
#endif
            break;

        case GPA_HW_GENERATION_GFX9:
            pPublicCounters = DX12GFX9_PUBLIC_COUNTERS;
            publicCounterCount = DX12GFX9_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWDX12GroupsGfx9;
            hwGroupCount = HWDX12GroupCountGfx9;
            ppHardwareCounters = DX12CounterGroupArrayGfx9;
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
    const GPACounterDesc* pInternalDerivedCounters = nullptr;
    size_t internalDerivedCounterCount = 0;

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
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX7, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_12, gDevIdCIHawaii, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_12, gDevIdVI, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_12, gDevIdGfx9, FALSE, counterNames);
}

// Test the DX12 counter names on all generations
TEST(CounterDLLTests, DX12CounterNamesByGeneration)
{
    VerifyHardwareNotSupported(GPA_API_DIRECTX_12, GPA_HW_GENERATION_NONE, FALSE);
    VerifyHardwareNotSupported(GPA_API_DIRECTX_12, GPA_HW_GENERATION_GFX6, FALSE);
    VerifyHardwareNotSupported(GPA_API_DIRECTX_12, GPA_HW_GENERATION_NVIDIA, FALSE);
    VerifyHardwareNotSupported(GPA_API_DIRECTX_12, GPA_HW_GENERATION_INTEL, FALSE);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX7, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_12, GPA_HW_GENERATION_GFX7, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_12, GPA_HW_GENERATION_GFX8, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_DIRECTX_12, GPA_HW_GENERATION_GFX9, FALSE, counterNames);
}
