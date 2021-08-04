//==============================================================================
// Copyright (c) 2012-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Unit Tests for VK Counter Generator.
//==============================================================================

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_counter_generator/gpa_counter.h"

#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_vk_gfx8.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_vk_gfx9.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_vk_gfx10.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_vk_gfx103.h"

#ifdef AMDT_INTERNAL
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_vk_gfx8.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_vk_gfx9.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_vk_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_vk_gfx103.h"
#endif

#include "gpu_perf_api_unit_tests/counter_generator_tests.h"
#include "gpu_perf_api_unit_tests/counters/gpa_counter_desc.h"

static void GetExpectedCountersForGeneration(GpaHwGeneration gen, std::vector<const char*>& counter_names)
{
    counter_names.clear();

    const GpaCounterDesc* public_counters      = nullptr;
    size_t                public_counter_count = 0;

    GpaCounterGroupDesc*     hardware_groups   = nullptr;
    GpaHardwareCounterDesc** hardware_counters = nullptr;
    unsigned int             hw_group_count    = 0;

    switch (gen)
    {
    case kGpaHwGenerationGfx8:
        public_counters      = kVkGfx8PublicCounters;
        public_counter_count = kVkGfx8PublicCounterCount;
#ifdef AMDT_INTERNAL
        hardware_groups   = counter_vk_gfx8::kHwVkGroupsGfx8;
        hw_group_count    = counter_vk_gfx8::kHwVkGroupCountGfx8;
        hardware_counters = counter_vk_gfx8::kVkCounterGroupArrayGfx8;
#endif
        break;

    case kGpaHwGenerationGfx9:
        public_counters      = kVkGfx9PublicCounters;
        public_counter_count = kVkGfx9PublicCounterCount;
#ifdef AMDT_INTERNAL
        hardware_groups   = counter_vk_gfx9::kHwVkGroupsGfx9;
        hw_group_count    = counter_vk_gfx9::kHwVkGroupCountGfx9;
        hardware_counters = counter_vk_gfx9::kVkCounterGroupArrayGfx9;
#endif
        break;

    case kGpaHwGenerationGfx10:
        public_counters      = kVkGfx10PublicCounters;
        public_counter_count = kVkGfx10PublicCounterCount;
#ifdef AMDT_INTERNAL
        hardware_groups   = counter_vk_gfx10::kHwVkGroupsGfx10;
        hw_group_count    = counter_vk_gfx10::kHwVkGroupCountGfx10;
        hardware_counters = counter_vk_gfx10::kVkCounterGroupArrayGfx10;
#endif
        break;

    case kGpaHwGenerationGfx103:
        public_counters      = kVkGfx103PublicCounters;
        public_counter_count = kVkGfx103PublicCounterCount;
#ifdef AMDT_INTERNAL
        hardware_groups   = counter_vk_gfx103::kHwVkGroupsGfx103;
        hw_group_count    = counter_vk_gfx103::kHwVkGroupCountGfx103;
        hardware_counters = counter_vk_gfx103::kVkCounterGroupArrayGfx103;
#endif
        break;

    default:
        break;
    }

    for (size_t i = 0; i < public_counter_count; i++)
    {
        counter_names.push_back(public_counters[i].name);
    }

    // Optionally, get internal derived counters.
    const GpaCounterDesc* kInternalDerivedCounters       = nullptr;
    size_t                internal_derived_counter_count = 0;

#ifdef AMDT_INTERNAL
    GpaGetInternalDerivedCounters(kGpaApiVulkan, gen, &kInternalDerivedCounters, &internal_derived_counter_count);
#endif

    for (size_t i = 0; i < internal_derived_counter_count; i++)
    {
        counter_names.push_back(kInternalDerivedCounters[i].name);
    }

    for (unsigned int i = 0; i < hw_group_count; i++)
    {
        for (unsigned int j = 0; j < hardware_groups[i].num_counters; j++)
        {
            counter_names.push_back(hardware_counters[i][j].name);
        }
    }
}

static std::vector<GpaCounterDesc> GetExpectedPublicCounters(GpaHwGeneration gen)
{
    const GpaCounterDesc* public_counters      = nullptr;
    size_t                public_counter_count = 0;

    switch (gen)
    {
    case kGpaHwGenerationGfx8:
        public_counters      = kVkGfx8PublicCounters;
        public_counter_count = kVkGfx8PublicCounterCount;
        break;

    case kGpaHwGenerationGfx9:
        public_counters      = kVkGfx9PublicCounters;
        public_counter_count = kVkGfx9PublicCounterCount;
        break;

    case kGpaHwGenerationGfx10:
        public_counters      = kVkGfx10PublicCounters;
        public_counter_count = kVkGfx10PublicCounterCount;
        break;

    case kGpaHwGenerationGfx103:
        public_counters      = kVkGfx103PublicCounters;
        public_counter_count = kVkGfx103PublicCounterCount;
        break;

    default:
        break;
    }

    std::vector<GpaCounterDesc> public_counter_list;
    public_counter_list.reserve(public_counter_count);
    for (size_t i = 0; i < public_counter_count; i++)
    {
        public_counter_list.push_back(public_counters[i]);
    }

    return public_counter_list;
}

#ifdef _WIN32
// Test the Vulkan derived counter blocks.
TEST(CounterDllTests, VulkanDerivedCounterBlocks)
{
    VerifyDerivedCounterCount(kGpaApiVulkan, kGpaHwGenerationGfx8, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx8));
    VerifyDerivedCounterCount(kGpaApiVulkan, kGpaHwGenerationGfx9, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx9));
    VerifyDerivedCounterCount(kGpaApiVulkan, kGpaHwGenerationGfx10, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx10));
    VerifyDerivedCounterCount(kGpaApiVulkan, kGpaHwGenerationGfx103, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx103));
}
#endif

// Test the VK counter names on all supported hardware.
TEST(CounterDllTests, VkCounterNames)
{
    VerifyHardwareNotSupported(kGpaApiVulkan, kDevIdUnknown, FALSE);
    VerifyHardwareNotSupported(kGpaApiVulkan, kDevIdSI, FALSE);
    VerifyHardwareNotSupported(kGpaApiVulkan, kDevIdCIHawaii, FALSE);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, counterNames);
    VerifyCounterNames(kGpaApiVulkan, kDevIdVI, FALSE, counterNames);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, counterNames);
    VerifyCounterNames(kGpaApiVulkan, kDevIdGfx9, FALSE, counterNames);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counterNames);
    VerifyCounterNames(kGpaApiVulkan, kDevIdGfx10, FALSE, counterNames);
}

// Test the VK counter names on all generations.
TEST(CounterDllTests, VkCounterNamesByGeneration)
{
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationNone, FALSE);
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationGfx6, FALSE);
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationNvidia, FALSE);
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationIntel, FALSE);
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationGfx6, FALSE);
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationGfx7, FALSE);

    std::vector<const char*> counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx8, FALSE, counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx9, FALSE, counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx10, FALSE, counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx103, FALSE, counter_names);
}

#ifdef _WIN32
TEST(CounterDllTests, VkCounterLibTest)
{
    VerifyCounterLibInterface(kGpaApiVulkan, kDevIdVI, REVISION_ID_ANY, false);
    VerifyCounterLibInterface(kGpaApiVulkan, kDevIdGfx9, REVISION_ID_ANY, false);
    VerifyCounterLibInterface(kGpaApiVulkan, kDevIdGfx10, REVISION_ID_ANY, false);
    VerifyCounterLibInterface(kGpaApiVulkan, kDevIdGfx10_3, REVISION_ID_ANY, false);
    VerifyCounterByPassCounterLibEntry(kGpaApiVulkan, kDevIdGfx9, REVISION_ID_ANY, false);
    VerifyCounterByPassCounterLibEntry(kGpaApiVulkan, kDevIdGfx10, REVISION_ID_ANY, false);
}
#endif

TEST(CounterDllTests, VkCounterFormulaTest)
{
    std::vector<const char*> counter_names;
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx8));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx9));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx10));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx103));
}