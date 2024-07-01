//==============================================================================
// Copyright (c) 2012-2024 Advanced Micro Devices, Inc. All rights reserved.
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
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx12_gfx11.h"

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx8.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx9.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx11.h"

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
        public_counters         = kDx12Gfx8PublicCounters;
        public_counter_count    = kDx12Gfx8PublicCounterCount;
        hardware_counter_groups = counter_dx12_gfx8::kDx12CounterGroupArrayGfx8;
        break;

    case kGpaHwGenerationGfx9:
        public_counters         = kDx12Gfx9PublicCounters;
        public_counter_count    = kDx12Gfx9PublicCounterCount;
        hardware_counter_groups = counter_dx12_gfx9::kDx12CounterGroupArrayGfx9;
        break;

    case kGpaHwGenerationGfx10:
        public_counters         = kDx12Gfx10PublicCounters;
        public_counter_count    = kDx12Gfx10PublicCounterCount;
        hardware_counter_groups = counter_dx12_gfx10::kDx12CounterGroupArrayGfx10;
        break;

    case kGpaHwGenerationGfx103:
        public_counters         = kDx12Gfx103PublicCounters;
        public_counter_count    = kDx12Gfx103PublicCounterCount;
        hardware_counter_groups = counter_dx12_gfx103::kDx12CounterGroupArrayGfx103;
        break;

    case kGpaHwGenerationGfx11:
        public_counters         = kDx12Gfx11PublicCounters;
        public_counter_count    = kDx12Gfx11PublicCounterCount;
        hardware_counter_groups = counter_dx12_gfx11::kDx12CounterGroupArrayGfx11;
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

    case kGpaHwGenerationGfx11:
        public_counters      = kDx12Gfx11PublicCounters;
        public_counter_count = kDx12Gfx11PublicCounterCount;
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

TEST(CounterDllTests, Dx12UnsupportedHardwareGenerations)
{
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationNone);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationNvidia);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationIntel);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationGfx6);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationGfx7);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationCdna);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationCdna2);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationCdna3);
}

TEST(CounterDllTests, Dx12VerifyInvalidOpenContextParameters)
{
    VerifyInvalidOpenContextParameters(kGpaApiDirectx12, kDevIdGfx11);
}

// Test the Dx12 derived counter blocks
TEST(CounterDllTests, Dx12DerivedCounterBlocksGfx8)
{
    VerifyDerivedCounterCount(kGpaApiDirectx12, kGpaHwGenerationGfx8, GetExpectedPublicCounters(kGpaHwGenerationGfx8));
}

TEST(CounterDllTests, Dx12DerivedCounterBlocksGfx9)
{
    VerifyDerivedCounterCount(kGpaApiDirectx12, kGpaHwGenerationGfx9, GetExpectedPublicCounters(kGpaHwGenerationGfx9));
}

TEST(CounterDllTests, Dx12DerivedCounterBlocksGfx10)
{
    VerifyDerivedCounterCount(kGpaApiDirectx12, kGpaHwGenerationGfx10, GetExpectedPublicCounters(kGpaHwGenerationGfx10));
}

TEST(CounterDllTests, Dx12DerivedCounterBlocksGfx103)
{
    VerifyDerivedCounterCount(kGpaApiDirectx12, kGpaHwGenerationGfx103, GetExpectedPublicCounters(kGpaHwGenerationGfx103));
}

TEST(CounterDllTests, Dx12DerivedCounterBlocksGfx11)
{
    VerifyDerivedCounterCount(kGpaApiDirectx12, kGpaHwGenerationGfx11, GetExpectedPublicCounters(kGpaHwGenerationGfx11));
}

// Test the Dx12 counter names on all supported hardware
TEST(CounterDllTests, Dx12CounterNamesByDeviceId)
{
    VerifyHardwareNotSupported(kGpaApiDirectx12, kDevIdUnknown);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kDevIdSI);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kDevIdCI);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kDevIdCIHawaii);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kDevIdMi250X);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kDevIdMi210);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kDevIdUnsupported1);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kDevIdUnsupported2);

    std::vector<const char*> derived_counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kDevIdVI, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kDevIdGfx9, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kDevIdGfx10, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kDevIdGfx10_3, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kDevIdGfx11, derived_counter_names, hardware_counter_names);

    // The variant hardware can only have the derived counter names verified.
    // GetExpectedCountersForGeneration() method in our tests is not thorough enough to create
    // the expected list of hardware counters for each variant.
    std::vector<const char*> empty_list_to_skip_tests;
    VerifyCounterNames(kGpaApiDirectx12, kDevIdGfx11_0_3, derived_counter_names, empty_list_to_skip_tests);
    VerifyCounterNames(kGpaApiDirectx12, kDevIdGfx11_0_3B, derived_counter_names, empty_list_to_skip_tests);
    VerifyCounterNames(kGpaApiDirectx12, kDevIdGfx11_5_0, derived_counter_names, empty_list_to_skip_tests);
}

TEST(CounterDllTests, Dx12CounterNamesGfx8)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx8, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, Dx12CounterNamesGfx9)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx9, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, Dx12CounterNamesGfx10)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, Dx12CounterNamesGfx103)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, Dx12CounterNamesGfx11)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
}

// Test the Dx12 counter names on all generations
TEST(CounterDllTests, Dx12CounterNamesByGeneration)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx8, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx9, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, Dx12OpenCounterContext)
{
    VerifyOpenCounterContext(kGpaApiDirectx12, kGpaHwGenerationGfx8);
    VerifyOpenCounterContext(kGpaApiDirectx12, kGpaHwGenerationGfx9);
    VerifyOpenCounterContext(kGpaApiDirectx12, kGpaHwGenerationGfx10);
    VerifyOpenCounterContext(kGpaApiDirectx12, kGpaHwGenerationGfx103);
    VerifyOpenCounterContext(kGpaApiDirectx12, kGpaHwGenerationGfx11);
}

TEST(CounterDllTests, Dx12CounterLibTestGfx8)
{
    VerifyCounterLibInterface(kGpaApiDirectx12, kDevIdVI, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx12, kDevIdVI, REVISION_ID_ANY);
}

TEST(CounterDllTests, Dx12CounterLibTestGfx9)
{
    VerifyCounterLibInterface(kGpaApiDirectx12, kDevIdGfx9, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx12, kDevIdGfx9, REVISION_ID_ANY);
}

TEST(CounterDllTests, Dx12CounterLibTestGfx10)
{
    VerifyCounterLibInterface(kGpaApiDirectx12, kDevIdGfx10, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx12, kDevIdGfx10, REVISION_ID_ANY);
}

TEST(CounterDllTests, Dx12CounterLibTestGfx103)
{
    VerifyCounterLibInterface(kGpaApiDirectx12, kDevIdGfx10_3, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx12, kDevIdGfx10_3, REVISION_ID_ANY);
}

TEST(CounterDllTests, Dx12CounterLibTestGfx11)
{
    VerifyCounterLibInterface(kGpaApiDirectx12, kDevIdGfx11, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx12, kDevIdGfx11, REVISION_ID_ANY);
}

TEST(CounterDllTests, Dx12CounterLibTestGfx1103)
{
    VerifyCounterLibInterface(kGpaApiDirectx12, kDevIdGfx11_0_3, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx12, kDevIdGfx11_0_3, REVISION_ID_ANY);
}

TEST(CounterDllTests, Dx12CounterLibTestGfx1103B)
{
    VerifyCounterLibInterface(kGpaApiDirectx12, kDevIdGfx11_0_3B, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx12, kDevIdGfx11_0_3B, REVISION_ID_ANY);
}

TEST(CounterDllTests, Dx12CounterLibTestGfx1150)
{
    VerifyCounterLibInterface(kGpaApiDirectx12, kDevIdGfx11_5_0, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx12, kDevIdGfx11_5_0, REVISION_ID_ANY);
}

TEST(CounterDllTests, Dx12CounterFormulaTest)
{
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx8));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx9));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx10));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx103));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx11));
}
