//==============================================================================
// Copyright (c) 2012-2023 Advanced Micro Devices, Inc. All rights reserved.
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
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_vk_gfx11.h"

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_vk_gfx8.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_vk_gfx9.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_vk_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_vk_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_vk_gfx11.h"

#include "gpu_perf_api_unit_tests/counter_generator_tests.h"
#include "gpu_perf_api_unit_tests/counters/gpa_counter_desc.h"

static void GetExpectedCountersForGeneration(GpaHwGeneration           generation,
                                             std::vector<const char*>& derived_counter_names,
                                             std::vector<const char*>& hardware_counter_names)
{
    derived_counter_names.clear();
    hardware_counter_names.clear();

    const GpaCounterDesc* public_counters      = nullptr;
    size_t                public_counter_count = 0;

    std::vector<std::vector<GpaHardwareCounterDesc>*> hardware_counter_groups;

    switch (generation)
    {
    case kGpaHwGenerationGfx8:
        public_counters         = kVkGfx8PublicCounters;
        public_counter_count    = kVkGfx8PublicCounterCount;
        hardware_counter_groups = counter_vk_gfx8::kVkCounterGroupArrayGfx8;
        break;

    case kGpaHwGenerationGfx9:
        public_counters         = kVkGfx9PublicCounters;
        public_counter_count    = kVkGfx9PublicCounterCount;
        hardware_counter_groups = counter_vk_gfx9::kVkCounterGroupArrayGfx9;
        break;

    case kGpaHwGenerationGfx10:
        public_counters         = kVkGfx10PublicCounters;
        public_counter_count    = kVkGfx10PublicCounterCount;
        hardware_counter_groups = counter_vk_gfx10::kVkCounterGroupArrayGfx10;
        break;

    case kGpaHwGenerationGfx103:
        public_counters         = kVkGfx103PublicCounters;
        public_counter_count    = kVkGfx103PublicCounterCount;
        hardware_counter_groups = counter_vk_gfx103::kVkCounterGroupArrayGfx103;
        break;

    case kGpaHwGenerationGfx11:
        public_counters         = kVkGfx11PublicCounters;
        public_counter_count    = kVkGfx11PublicCounterCount;
        hardware_counter_groups = counter_vk_gfx11::kVkCounterGroupArrayGfx11;
        break;

    default:
        assert(!"Unrecognized hardware generation in GetExpectedCountersForGeneration");
        break;
    }

    for (size_t i = 0; i < public_counter_count; i++)
    {
        derived_counter_names.push_back(public_counters[i].name);
    }

    const size_t num_hardware_counter_groups = hardware_counter_groups.size();
    for (size_t i = 0; i < num_hardware_counter_groups; ++i)
    {
        const size_t num_counters_in_group = hardware_counter_groups[i]->size();
        for (size_t j = 0; j < num_counters_in_group; ++j)
        {
            hardware_counter_names.push_back(hardware_counter_groups[i]->at(j).name);
        }
    }
}

static std::vector<GpaCounterDesc> GetExpectedPublicCounters(GpaHwGeneration generation)
{
    const GpaCounterDesc* public_counters      = nullptr;
    size_t                public_counter_count = 0;

    switch (generation)
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

    case kGpaHwGenerationGfx11:
        public_counters      = kVkGfx11PublicCounters;
        public_counter_count = kVkGfx11PublicCounterCount;
        break;

    default:
        assert(!"Unrecognized hardware generation in GetExpectedPublicCounters");
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

TEST(CounterDllTests, VkUnsupportedHardwareGenerations)
{
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationNone, FALSE);
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationNvidia, FALSE);
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationIntel, FALSE);
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationGfx6, FALSE);
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationGfx7, FALSE);
}

#ifdef _WIN32
// Test the Vulkan derived counter blocks.
TEST(CounterDllTests, VulkanDerivedCounterBlocks)
{
    VerifyDerivedCounterCount(kGpaApiVulkan, kGpaHwGenerationGfx8, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx8));
    VerifyDerivedCounterCount(kGpaApiVulkan, kGpaHwGenerationGfx9, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx9));
    VerifyDerivedCounterCount(kGpaApiVulkan, kGpaHwGenerationGfx10, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx10));
    VerifyDerivedCounterCount(kGpaApiVulkan, kGpaHwGenerationGfx103, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx103));
    VerifyDerivedCounterCount(kGpaApiVulkan, kGpaHwGenerationGfx11, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx11));
}
#endif

// Test the VK counter names on all supported hardware.
TEST(CounterDllTests, VkCounterNamesByDeviceId)
{
    VerifyHardwareNotSupported(kGpaApiVulkan, kDevIdUnknown, FALSE);
    VerifyHardwareNotSupported(kGpaApiVulkan, kDevIdSI, FALSE);
    VerifyHardwareNotSupported(kGpaApiVulkan, kDevIdCI, FALSE);
    VerifyHardwareNotSupported(kGpaApiVulkan, kDevIdCIHawaii, FALSE);

    std::vector<const char*> derived_counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kDevIdVI, FALSE, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kDevIdGfx9, FALSE, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kDevIdGfx10, FALSE, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kDevIdGfx10_3, FALSE, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kDevIdGfx11, FALSE, derived_counter_names, hardware_counter_names);
}

TEST(CounterDllTests, VkCounterNamesGfx8)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx8, FALSE, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, VkCounterNamesGfx9)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx9, FALSE, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, VkCounterNamesGfx10)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx10, FALSE, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, VkCounterNamesGfx103)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx103, FALSE, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, VkCounterNamesGfx11)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx11, FALSE, counter_names, hardware_counter_names);
}

// Test the VK counter names on all generations.
TEST(CounterDllTests, VkCounterNamesByGeneration)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx8, FALSE, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx9, FALSE, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx10, FALSE, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx103, FALSE, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx11, FALSE, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, VkOpenCounterContext)
{
    VerifyOpenCounterContext(kGpaApiVulkan, kGpaHwGenerationGfx8);
    VerifyOpenCounterContext(kGpaApiVulkan, kGpaHwGenerationGfx9);
    VerifyOpenCounterContext(kGpaApiVulkan, kGpaHwGenerationGfx10);
    VerifyOpenCounterContext(kGpaApiVulkan, kGpaHwGenerationGfx103);
    VerifyOpenCounterContext(kGpaApiVulkan, kGpaHwGenerationGfx11);
}

#ifdef _WIN32
TEST(CounterDllTests, VkCounterLibTestGfx8)
{
    VerifyCounterLibInterface(kGpaApiVulkan, kDevIdVI, REVISION_ID_ANY, false);
    VerifyCounterByPassCounterLibEntry(kGpaApiVulkan, kDevIdVI, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, VkCounterLibTestGfx9)
{
    VerifyCounterLibInterface(kGpaApiVulkan, kDevIdGfx9, REVISION_ID_ANY, false);
    VerifyCounterByPassCounterLibEntry(kGpaApiVulkan, kDevIdGfx9, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, VkCounterLibTestGfx10)
{
    VerifyCounterLibInterface(kGpaApiVulkan, kDevIdGfx10, REVISION_ID_ANY, false);
    VerifyCounterByPassCounterLibEntry(kGpaApiVulkan, kDevIdGfx10, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, VkCounterLibTestGfx103)
{
    VerifyCounterLibInterface(kGpaApiVulkan, kDevIdGfx10_3, REVISION_ID_ANY, false);
    VerifyCounterByPassCounterLibEntry(kGpaApiVulkan, kDevIdGfx10_3, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, VkCounterLibTestGfx11)
{
    VerifyCounterLibInterface(kGpaApiVulkan, kDevIdGfx11, REVISION_ID_ANY, false);
    VerifyCounterByPassCounterLibEntry(kGpaApiVulkan, kDevIdGfx11, REVISION_ID_ANY, false);
}
#endif

TEST(CounterDllTests, VkCounterFormulaTest)
{
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx8));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx9));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx10));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx103));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx11));
}
