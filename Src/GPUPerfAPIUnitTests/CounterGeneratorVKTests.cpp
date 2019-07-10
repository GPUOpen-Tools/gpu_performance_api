//==============================================================================
// Copyright (c) 2012-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit Tests for VK Counter Generator
//==============================================================================

#include "CounterGeneratorTests.h"
#include "GPUPerfAPITypes.h"
#include "GPACounter.h"

#include "counters/GPACounterDesc.h"

#include "counters/PublicDerivedCountersVKGfx8.h"
#include "counters/PublicDerivedCountersVKGfx9.h"
#include "counters/PublicDerivedCountersVKGfx10.h"

#ifdef AMDT_INTERNAL
#include "GPAHWCounterVKGfx8.h"
#include "GPAHWCounterVKGfx9.h"
#include "GPAHWCounterVKGfx10.h"
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
        pPublicCounters    = VKGFX8_PUBLIC_COUNTERS;
        publicCounterCount = VKGFX8_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
        pHardwareGroups    = CounterGfx8::HWVKGroupsGfx8;
        hwGroupCount       = CounterGfx8::HWVKGroupCountGfx8;
        ppHardwareCounters = CounterGfx8::VKCounterGroupArrayGfx8;
#endif
        break;

    case GPA_HW_GENERATION_GFX9:
        pPublicCounters    = VKGFX9_PUBLIC_COUNTERS;
        publicCounterCount = VKGFX9_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
        pHardwareGroups    = CounterGfx9::HWVKGroupsGfx9;
        hwGroupCount       = CounterGfx9::HWVKGroupCountGfx9;
        ppHardwareCounters = CounterGfx9::VKCounterGroupArrayGfx9;
#endif
        break;

    case GPA_HW_GENERATION_GFX10:
        pPublicCounters    = VKGFX10_PUBLIC_COUNTERS;
        publicCounterCount = VKGFX10_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
        pHardwareGroups    = CounterGfx10::HWVKGroupsGfx10;
        hwGroupCount       = CounterGfx10::HWVKGroupCountGfx10;
        ppHardwareCounters = CounterGfx10::VKCounterGroupArrayGfx10;
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
    GPA_GetInternalDerivedCounters(GPA_API_VULKAN, gen, &pInternalDerivedCounters, &internalDerivedCounterCount);
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

// Test the VK counter names on all supported hardware
TEST(CounterDLLTests, VKCounterNames)
{
    VerifyHardwareNotSupported(GPA_API_VULKAN, gDevIdUnknown, FALSE);
    VerifyHardwareNotSupported(GPA_API_VULKAN, gDevIdSI, FALSE);
    VerifyHardwareNotSupported(GPA_API_VULKAN, gDevIdCIHawaii, FALSE);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_VULKAN, gDevIdVI, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_VULKAN, gDevIdGfx9, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX10, counterNames);
    VerifyCounterNames(GPA_API_VULKAN, gDevIdGfx10, FALSE, counterNames);
}

// Test the VK counter names on all generations
TEST(CounterDLLTests, VKCounterNamesByGeneration)
{
    VerifyHardwareNotSupported(GPA_API_VULKAN, GPA_HW_GENERATION_NONE, FALSE);
    VerifyHardwareNotSupported(GPA_API_VULKAN, GPA_HW_GENERATION_GFX6, FALSE);
    VerifyHardwareNotSupported(GPA_API_VULKAN, GPA_HW_GENERATION_NVIDIA, FALSE);
    VerifyHardwareNotSupported(GPA_API_VULKAN, GPA_HW_GENERATION_INTEL, FALSE);
    VerifyHardwareNotSupported(GPA_API_VULKAN, GPA_HW_GENERATION_GFX6, FALSE);
    VerifyHardwareNotSupported(GPA_API_VULKAN, GPA_HW_GENERATION_GFX7, FALSE);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_VULKAN, GPA_HW_GENERATION_GFX8, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_VULKAN, GPA_HW_GENERATION_GFX9, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX10, counterNames);
    VerifyCounterNames(GPA_API_VULKAN, GPA_HW_GENERATION_GFX10, FALSE, counterNames);
}
