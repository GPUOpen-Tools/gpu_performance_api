//==============================================================================
// Copyright (c) 2012-2022 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Unit Tests for Dx11 Counter Generator.
//==============================================================================

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_counter_generator/gpa_counter.h"

#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx11_gfx8.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx11_gfx9.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx11_gfx10.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx11_gfx103.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx11_gfx11.h"

#include "gpu_perf_api_unit_tests/counter_generator_tests.h"
#include "gpu_perf_api_unit_tests/counters/gpa_counter_desc.h"

static void GetExpectedCountersForGeneration(GpaHwGeneration gen, std::vector<const char*>& counter_names)
{
    counter_names.clear();

    const GpaCounterDesc* kPublicCounters      = nullptr;
    size_t                public_counter_count = 0;

    std::vector<GpaCounterGroupDesc>                  hardware_groups;
    std::vector<std::vector<GpaHardwareCounterDesc>*> hardware_counters;
    unsigned int                                      group_count = 0;

    switch (gen)
    {
    case kGpaHwGenerationGfx8:
        kPublicCounters      = kDx11Gfx8PublicCounters;
        public_counter_count = kDx11Gfx8PublicCounterCount;
        break;

    case kGpaHwGenerationGfx9:
        kPublicCounters      = kDx11Gfx9PublicCounters;
        public_counter_count = kDx11Gfx9PublicCounterCount;
        break;

    case kGpaHwGenerationGfx10:
        kPublicCounters      = kDx11Gfx10PublicCounters;
        public_counter_count = kDx11Gfx10PublicCounterCount;
        break;

    case kGpaHwGenerationGfx103:
        kPublicCounters      = kDx11Gfx103PublicCounters;
        public_counter_count = kDx11Gfx103PublicCounterCount;
        break;

    case kGpaHwGenerationGfx11:
        kPublicCounters      = kDx11Gfx11PublicCounters;
        public_counter_count = kDx11Gfx11PublicCounterCount;
        break;

    default:
        break;
    }

    for (size_t i = 0; i < public_counter_count; i++)
    {
        counter_names.push_back(kPublicCounters[i].name);
    }

    // Optionally, get internal derived counters
    const GpaCounterDesc* kInternalDerivedCounters       = nullptr;
    size_t                internal_derived_counter_count = 0;

    for (size_t i = 0; i < internal_derived_counter_count; i++)
    {
        counter_names.push_back(kInternalDerivedCounters[i].name);
    }

    for (unsigned int i = 0; i < group_count; i++)
    {
        for (unsigned int j = 0; j < hardware_groups.at(i).num_counters; j++)
        {
            counter_names.push_back(hardware_counters.at(i)->at(j).name);
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
        public_counters      = kDx11Gfx8PublicCounters;
        public_counter_count = kDx11Gfx8PublicCounterCount;
        break;

    case kGpaHwGenerationGfx9:
        public_counters      = kDx11Gfx9PublicCounters;
        public_counter_count = kDx11Gfx9PublicCounterCount;
        break;

    case kGpaHwGenerationGfx10:
        public_counters      = kDx11Gfx10PublicCounters;
        public_counter_count = kDx11Gfx10PublicCounterCount;
        break;

    case kGpaHwGenerationGfx103:
        public_counters      = kDx11Gfx103PublicCounters;
        public_counter_count = kDx11Gfx103PublicCounterCount;
        break;

    case kGpaHwGenerationGfx11:
        public_counters      = kDx11Gfx11PublicCounters;
        public_counter_count = kDx11Gfx11PublicCounterCount;
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

// Test the Dx11 derived counter blocks
TEST(CounterDllTests, Dx11DerivedCounterBlocks)
{
    VerifyDerivedCounterCount(kGpaApiDirectx11, kGpaHwGenerationGfx8, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx8));
    VerifyDerivedCounterCount(kGpaApiDirectx11, kGpaHwGenerationGfx9, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx9));
    VerifyDerivedCounterCount(kGpaApiDirectx11, kGpaHwGenerationGfx10, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx10));
    VerifyDerivedCounterCount(kGpaApiDirectx11, kGpaHwGenerationGfx103, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx103));
    VerifyDerivedCounterCount(kGpaApiDirectx11, kGpaHwGenerationGfx11, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx11));
}

// Test the Dx11 counter names on all supported hardware
TEST(CounterDllTests, Dx11CounterNames)
{
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdUnknown, FALSE);

    std::vector<const char*> counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kDevIdVI, FALSE, counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kDevIdGfx9, FALSE, counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kDevIdGfx10, FALSE, counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kDevIdGfx10_3, FALSE, counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kDevIdGfx11, FALSE, counter_names);
}

// Test the Dx11 counter names on all generations
TEST(CounterDllTests, Dx11CounterNamesByGeneration)
{
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationNone, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationNvidia, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationIntel, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationGfx6, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationGfx7, FALSE);

    std::vector<const char*> counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx8, FALSE, counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx9, FALSE, counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx10, FALSE, counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx103, FALSE, counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx11, FALSE, counter_names);
}

TEST(CounterDllTests, Dx11CounterLibTestGfx8)
{
    VerifyCounterLibInterface(kGpaApiDirectx11, kDevIdVI, REVISION_ID_ANY, false);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx11, kDevIdVI, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, Dx11CounterLibTestGfx9)
{
    VerifyCounterLibInterface(kGpaApiDirectx11, kDevIdGfx9, REVISION_ID_ANY, false);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx11, kDevIdGfx9, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, Dx11CounterLibTestGfx10)
{
    VerifyCounterLibInterface(kGpaApiDirectx11, kDevIdGfx10, REVISION_ID_ANY, false);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx11, kDevIdGfx10, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, Dx11CounterLibTestGfx103)
{
    VerifyCounterLibInterface(kGpaApiDirectx11, kDevIdGfx10_3, REVISION_ID_ANY, false);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx11, kDevIdGfx10_3, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, Dx11CounterLibTestGfx11)
{
    VerifyCounterLibInterface(kGpaApiDirectx11, kDevIdGfx11, REVISION_ID_ANY, false);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx11, kDevIdGfx11, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, Dx11CounterFormulaTest)
{
    std::vector<const char*> counter_names;
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx8));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx9));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx10));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx103));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx11));
}