//==============================================================================
// Copyright (c) 2012-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit Tests for VK Counter Generator
//==============================================================================

#include "counter_generator_tests.h"
#include "gpu_perf_api_types.h"
#include "gpa_counter.h"

#include "counters/gpa_counter_desc.h"

#include "counters/public_derived_counters_vk_gfx8.h"
#include "counters/public_derived_counters_vk_gfx9.h"
#include "counters/public_derived_counters_vk_gfx10.h"
#include "counters/public_derived_counters_vk_gfx103.h"

#ifdef AMDT_INTERNAL
#include "gpa_hw_counter_vk_gfx8.h"
#include "gpa_hw_counter_vk_gfx9.h"
#include "gpa_hw_counter_vk_gfx10.h"
#include "gpa_hw_counter_vk_gfx103.h"
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
        pHardwareGroups    = counter_vk_gfx8::hw_vk_groups_gfx8;
        hwGroupCount       = counter_vk_gfx8::hw_vk_group_count_gfx8;
        ppHardwareCounters = counter_vk_gfx8::vk_counter_group_array_gfx8;
#endif
        break;

    case GPA_HW_GENERATION_GFX9:
        pPublicCounters    = VKGFX9_PUBLIC_COUNTERS;
        publicCounterCount = VKGFX9_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
        pHardwareGroups    = counter_vk_gfx9::hw_vk_groups_gfx9;
        hwGroupCount       = counter_vk_gfx9::hw_vk_group_count_gfx9;
        ppHardwareCounters = counter_vk_gfx9::vk_counter_group_array_gfx9;
#endif
        break;

    case GPA_HW_GENERATION_GFX10:
        pPublicCounters    = VKGFX10_PUBLIC_COUNTERS;
        publicCounterCount = VKGFX10_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
        pHardwareGroups    = counter_vk_gfx10::hw_vk_groups_gfx10;
        hwGroupCount       = counter_vk_gfx10::hw_vk_group_count_gfx10;
        ppHardwareCounters = counter_vk_gfx10::vk_counter_group_array_gfx10;
#endif
        break;

    case GPA_HW_GENERATION_GFX103:
        pPublicCounters    = VKGFX103_PUBLIC_COUNTERS;
        publicCounterCount = VKGFX103_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
        pHardwareGroups    = counter_vk_gfx103::hw_vk_groups_gfx103;
        hwGroupCount       = counter_vk_gfx103::hw_vk_group_count_gfx103;
        ppHardwareCounters = counter_vk_gfx103::vk_counter_group_array_gfx103;
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

static std::vector<GPACounterDesc> GetExpectedPublicCounters(GPA_Hw_Generation gen)
{
    const GPACounterDesc* public_counters    = nullptr;
    size_t                public_counter_count = 0;

    switch (gen)
    {
    case GPA_HW_GENERATION_GFX8:
        public_counters    = VKGFX8_PUBLIC_COUNTERS;
        public_counter_count = VKGFX8_PUBLIC_COUNTER_COUNT;
        break;

    case GPA_HW_GENERATION_GFX9:
        public_counters    = VKGFX9_PUBLIC_COUNTERS;
        public_counter_count = VKGFX9_PUBLIC_COUNTER_COUNT;
        break;

    case GPA_HW_GENERATION_GFX10:
        public_counters    = VKGFX10_PUBLIC_COUNTERS;
        public_counter_count = VKGFX10_PUBLIC_COUNTER_COUNT;
        break;

    case GPA_HW_GENERATION_GFX103:
        public_counters    = VKGFX103_PUBLIC_COUNTERS;
        public_counter_count = VKGFX103_PUBLIC_COUNTER_COUNT;
        break;

    default:
        break;
    }

    std::vector<GPACounterDesc> public_counter_list;
    public_counter_list.reserve(public_counter_count);
    for (size_t i = 0; i < public_counter_count; i++)
    {
        public_counter_list.push_back(public_counters[i]);
    }

    return public_counter_list;
}

#ifdef _WIN32
// Test the Vulkan derived counter blocks
TEST(CounterDLLTests, VulkanDerivedCounterBlocks)
{
    VerifyDerivedCounterCount(GPA_API_VULKAN, GPA_HW_GENERATION_GFX8, FALSE, GetExpectedPublicCounters(GPA_HW_GENERATION_GFX8));
    VerifyDerivedCounterCount(GPA_API_VULKAN, GPA_HW_GENERATION_GFX9, FALSE, GetExpectedPublicCounters(GPA_HW_GENERATION_GFX9));
    VerifyDerivedCounterCount(GPA_API_VULKAN, GPA_HW_GENERATION_GFX10, FALSE, GetExpectedPublicCounters(GPA_HW_GENERATION_GFX10));
    VerifyDerivedCounterCount(GPA_API_VULKAN, GPA_HW_GENERATION_GFX103, FALSE, GetExpectedPublicCounters(GPA_HW_GENERATION_GFX103));
}
#endif

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
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX103, counterNames);
    VerifyCounterNames(GPA_API_VULKAN, GPA_HW_GENERATION_GFX103, FALSE, counterNames);
}

#ifdef _WIN32
TEST(CounterDLLTests, VkCounterLibTest)
{
    VerifyCounterLibInterface(GPA_API_VULKAN, gDevIdVI, REVISION_ID_ANY, false);
    VerifyCounterLibInterface(GPA_API_VULKAN, gDevIdGfx9, REVISION_ID_ANY, false);
    VerifyCounterLibInterface(GPA_API_VULKAN, gDevIdGfx10, REVISION_ID_ANY, false);
    VerifyCounterLibInterface(GPA_API_VULKAN, gDevIdGfx10_3, REVISION_ID_ANY, false);
    VerifyCounterByPassCounterLibEntry(GPA_API_VULKAN, gDevIdGfx9, REVISION_ID_ANY, false);
    VerifyCounterByPassCounterLibEntry(GPA_API_VULKAN, gDevIdGfx10, REVISION_ID_ANY, false);
}
#endif

TEST(CounterDLLTests, VkCounterFormulaTest)
{
    std::vector<const char*> counterNames;
    VerifyCounterFormula(GetExpectedPublicCounters(GPA_HW_GENERATION_GFX8));
    VerifyCounterFormula(GetExpectedPublicCounters(GPA_HW_GENERATION_GFX9));
    VerifyCounterFormula(GetExpectedPublicCounters(GPA_HW_GENERATION_GFX10));
    VerifyCounterFormula(GetExpectedPublicCounters(GPA_HW_GENERATION_GFX103));
}