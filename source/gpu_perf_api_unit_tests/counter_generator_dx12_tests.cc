//==============================================================================
// Copyright (c) 2012-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Unit Tests for Dx12 Counter Generator.
//==============================================================================

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_counter_generator/gpa_counter.h"

#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx12_gfx8.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx12_gfx9.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx12_gfx10.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx12_gfx103.h"

#ifdef AMDT_INTERNAL
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx8.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx9.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx103.h"
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
    unsigned int             group_count       = 0;

    switch (gen)
    {
    case kGpaHwGenerationGfx8:
        public_counters      = kDx12Gfx8PublicCounters;
        public_counter_count = kDx12Gfx8PublicCounterCount;
#ifdef AMDT_INTERNAL
        hardware_groups   = counter_dx12_gfx8::kHwDx12GroupsGfx8;
        group_count       = counter_dx12_gfx8::kHwDx12GroupCountGfx8;
        hardware_counters = counter_dx12_gfx8::kDx12CounterGroupArrayGfx8;
#endif
        break;

    case kGpaHwGenerationGfx9:
        public_counters      = kDx12Gfx9PublicCounters;
        public_counter_count = kDx12Gfx9PublicCounterCount;
#ifdef AMDT_INTERNAL
        hardware_groups   = counter_dx12_gfx9::kHwDx12GroupsGfx9;
        group_count       = counter_dx12_gfx9::kHwDx12GroupCountGfx9;
        hardware_counters = counter_dx12_gfx9::kDx12CounterGroupArrayGfx9;
#endif
        break;

    case kGpaHwGenerationGfx10:
        public_counters      = kDx12Gfx10PublicCounters;
        public_counter_count = kDx12Gfx10PublicCounterCount;
#ifdef AMDT_INTERNAL
        hardware_groups   = counter_dx12_gfx10::kHwDx12GroupsGfx10;
        group_count       = counter_dx12_gfx10::kHwDx12GroupCountGfx10;
        hardware_counters = counter_dx12_gfx10::kDx12CounterGroupArrayGfx10;
#endif
        break;

    case kGpaHwGenerationGfx103:
        public_counters      = kDx12Gfx103PublicCounters;
        public_counter_count = kDx12Gfx103PublicCounterCount;
#ifdef AMDT_INTERNAL
        hardware_groups   = counter_dx12_gfx103::kHwDx12GroupsGfx103;
        group_count       = counter_dx12_gfx103::kHwDx12GroupCountGfx103;
        hardware_counters = counter_dx12_gfx103::kDx12CounterGroupArrayGfx103;
#endif
        break;

    default:
        break;
    }

    for (size_t i = 0; i < public_counter_count; i++)
    {
        counter_names.push_back(public_counters[i].name);
    }

    // Optionally, get internal derived counters
    const GpaCounterDesc* kInternalDerivedCounters       = nullptr;
    size_t                internal_derived_counter_count = 0;

#ifdef AMDT_INTERNAL
    GpaGetInternalDerivedCounters(kGpaApiDirectx12, gen, &kInternalDerivedCounters, &internal_derived_counter_count);
#endif

    for (size_t i = 0; i < internal_derived_counter_count; i++)
    {
        counter_names.push_back(kInternalDerivedCounters[i].name);
    }

    for (unsigned int i = 0; i < group_count; i++)
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
        public_counters      = kDx12Gfx8PublicCounters;
        public_counter_count = kDx12Gfx8PublicCounterCount;
        break;

    case kGpaHwGenerationGfx9:
        public_counters      = kDx12Gfx9PublicCounters;
        public_counter_count = kDx12Gfx9PublicCounterCount;
        break;

    case kGpaHwGenerationGfx10:
        public_counters      = kDx12Gfx10PublicCounters;
        public_counter_count = kDx12Gfx10PublicCounterCount;
        break;

    case kGpaHwGenerationGfx103:
        public_counters      = kDx12Gfx103PublicCounters;
        public_counter_count = kDx12Gfx103PublicCounterCount;
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

// Test the Dx12 derived counter blocks
TEST(CounterDllTests, Dx12DerivedCounterBlocks)
{
    VerifyDerivedCounterCount(kGpaApiDirectx12, kGpaHwGenerationGfx8, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx8));
    VerifyDerivedCounterCount(kGpaApiDirectx12, kGpaHwGenerationGfx9, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx9));
    VerifyDerivedCounterCount(kGpaApiDirectx12, kGpaHwGenerationGfx10, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx10));
    VerifyDerivedCounterCount(kGpaApiDirectx12, kGpaHwGenerationGfx103, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx103));
}

// Test the Dx12 counter names on all supported hardware
TEST(CounterDllTests, Dx12CounterNames)
{
    VerifyHardwareNotSupported(kGpaApiDirectx12, kDevIdUnknown, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kDevIdSI, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kDevIdCI, FALSE);

    std::vector<const char*> counter_name;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, counter_name);
    VerifyCounterNames(kGpaApiDirectx12, kDevIdVI, FALSE, counter_name);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, counter_name);
    VerifyCounterNames(kGpaApiDirectx12, kDevIdGfx9, FALSE, counter_name);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counter_name);
    VerifyCounterNames(kGpaApiDirectx12, kDevIdGfx10, FALSE, counter_name);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counter_name);
    VerifyCounterNames(kGpaApiDirectx12, kDevIdGfx10_3, FALSE, counter_name);
}

// Test the Dx12 counter names on all generations
TEST(CounterDllTests, Dx12CounterNamesByGeneration)
{
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationNone, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationGfx6, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationNvidia, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationIntel, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationGfx7, FALSE);

    std::vector<const char*> counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx8, FALSE, counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx9, FALSE, counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx10, FALSE, counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx103, FALSE, counter_names);
}

TEST(CounterDllTests, Dx12CounterLibTest)
{
    VerifyCounterLibInterface(kGpaApiDirectx12, kDevIdVI, REVISION_ID_ANY, false);
    VerifyCounterLibInterface(kGpaApiDirectx12, kDevIdGfx9, REVISION_ID_ANY, false);
    VerifyCounterLibInterface(kGpaApiDirectx12, kDevIdGfx10, REVISION_ID_ANY, false);
    VerifyCounterLibInterface(kGpaApiDirectx12, kDevIdGfx10_3, REVISION_ID_ANY, true);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx12, kDevIdGfx9, REVISION_ID_ANY, false);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx12, kDevIdGfx10, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, Dx12CounterFormulaTest)
{
    std::vector<const char*> counter_names;
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx8));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx9));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx10));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx103));
}