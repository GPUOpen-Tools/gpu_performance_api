//==============================================================================
// Copyright (c) 2012-2023 Advanced Micro Devices, Inc. All rights reserved.
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

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx8.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx9.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx11.h"

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
        public_counters         = kDx11Gfx8PublicCounters;
        public_counter_count    = kDx11Gfx8PublicCounterCount;
        hardware_counter_groups = counter_dx11_gfx8::kDx11CounterGroupArrayGfx8;
        break;

    case kGpaHwGenerationGfx9:
        public_counters         = kDx11Gfx9PublicCounters;
        public_counter_count    = kDx11Gfx9PublicCounterCount;
        hardware_counter_groups = counter_dx11_gfx9::kDx11CounterGroupArrayGfx9;
        break;

    case kGpaHwGenerationGfx10:
        public_counters         = kDx11Gfx10PublicCounters;
        public_counter_count    = kDx11Gfx10PublicCounterCount;
        hardware_counter_groups = counter_dx11_gfx10::kDx11CounterGroupArrayGfx10;
        break;

    case kGpaHwGenerationGfx103:
        public_counters         = kDx11Gfx103PublicCounters;
        public_counter_count    = kDx11Gfx103PublicCounterCount;
        hardware_counter_groups = counter_dx11_gfx103::kDx11CounterGroupArrayGfx103;
        break;

    case kGpaHwGenerationGfx11:
        public_counters         = kDx11Gfx11PublicCounters;
        public_counter_count    = kDx11Gfx11PublicCounterCount;
        hardware_counter_groups = counter_dx11_gfx11::kDx11CounterGroupArrayGfx11;
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

TEST(CounterDllTests, Dx11UnsupportedHardwareGenerations)
{
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationNone, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationNvidia, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationIntel, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationGfx6, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationGfx7, FALSE);
}

// Test the Dx11 derived counter blocks
TEST(CounterDllTests, Dx11DerivedCounterBlocksGfx8)
{
    VerifyDerivedCounterCount(kGpaApiDirectx11, kGpaHwGenerationGfx8, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx8));
}

TEST(CounterDllTests, Dx11DerivedCounterBlocksGfx9)
{
    VerifyDerivedCounterCount(kGpaApiDirectx11, kGpaHwGenerationGfx9, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx9));
}

TEST(CounterDllTests, Dx11DerivedCounterBlocksGfx10)
{
    VerifyDerivedCounterCount(kGpaApiDirectx11, kGpaHwGenerationGfx10, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx10));
}

TEST(CounterDllTests, Dx11DerivedCounterBlocksGfx103)
{
    VerifyDerivedCounterCount(kGpaApiDirectx11, kGpaHwGenerationGfx103, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx103));
}

TEST(CounterDllTests, Dx11DerivedCounterBlocksGfx11)
{
    VerifyDerivedCounterCount(kGpaApiDirectx11, kGpaHwGenerationGfx11, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx11));
}

// Test the Dx11 counter names on all supported hardware
TEST(CounterDllTests, Dx11CounterNamesByDeviceId)
{
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdUnknown, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdSI, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdCI, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdCIHawaii, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdMi250X, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdMi210, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdUnsupported1, FALSE);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdUnsupported2, FALSE);

    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kDevIdVI, FALSE, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kDevIdGfx9, FALSE, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kDevIdGfx10, FALSE, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kDevIdGfx10_3, FALSE, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kDevIdGfx11, FALSE, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kDevIdGfx11_0_3, FALSE, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kDevIdGfx11_0_3B, FALSE, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, Dx11CounterNamesGfx8)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx8, FALSE, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, Dx11CounterNamesGfx9)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx9, FALSE, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, Dx11CounterNamesGfx10)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx10, FALSE, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, Dx11CounterNamesGfx103)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx103, FALSE, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, Dx11CounterNamesGfx11)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx11, FALSE, counter_names, hardware_counter_names);
}

// Test the Dx11 counter names on all generations
TEST(CounterDllTests, Dx11CounterNamesByGeneration)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx8, FALSE, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx9, FALSE, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx10, FALSE, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx103, FALSE, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx11, FALSE, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, Dx11OpenCounterContext)
{
    VerifyOpenCounterContext(kGpaApiDirectx11, kGpaHwGenerationGfx8);
    VerifyOpenCounterContext(kGpaApiDirectx11, kGpaHwGenerationGfx9);
    VerifyOpenCounterContext(kGpaApiDirectx11, kGpaHwGenerationGfx10);
    VerifyOpenCounterContext(kGpaApiDirectx11, kGpaHwGenerationGfx103);
    VerifyOpenCounterContext(kGpaApiDirectx11, kGpaHwGenerationGfx11);
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

TEST(CounterDllTests, Dx11CounterLibTestGfx1103)
{
    VerifyCounterLibInterface(kGpaApiDirectx11, kDevIdGfx11_0_3, REVISION_ID_ANY, false);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx11, kDevIdGfx11_0_3, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, Dx11CounterLibTestGfx1103B)
{
    VerifyCounterLibInterface(kGpaApiDirectx11, kDevIdGfx11_0_3B, REVISION_ID_ANY, false);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx11, kDevIdGfx11_0_3B, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, Dx11CounterFormulaTest)
{
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx8));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx9));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx10));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx103));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx11));
}
