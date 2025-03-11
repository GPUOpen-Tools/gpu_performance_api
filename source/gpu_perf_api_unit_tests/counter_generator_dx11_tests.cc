//==============================================================================
// Copyright (c) 2012-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Unit Tests for Dx11 Counter Generator.
//==============================================================================

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_counter_generator/gpa_counter.h"

#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx11_gfx10.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx11_gfx103.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx11_gfx11.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx11_gfx12.h"

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx11.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx12.h"

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

    case kGpaHwGenerationGfx12:
        public_counters         = kDx11Gfx12PublicCounters;
        public_counter_count    = kDx11Gfx12PublicCounterCount;
        hardware_counter_groups = counter_dx11_gfx12::kDx11CounterGroupArrayGfx12;
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

    case kGpaHwGenerationGfx12:
        public_counters      = kDx11Gfx12PublicCounters;
        public_counter_count = kDx11Gfx12PublicCounterCount;
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
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationNone);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationNvidia);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationIntel);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationGfx6);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationGfx7);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationGfx8);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationGfx9);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationCdna);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationCdna2);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kGpaHwGenerationCdna3);
}

TEST(CounterDllTests, Dx11VerifyInvalidOpenContextParameters)
{
    VerifyInvalidOpenContextParameters(kGpaApiDirectx11, kDevIdGfx11);
}

// Test the Dx11 derived counter blocks
TEST(CounterDllTests, Dx11DerivedCounterBlocksGfx10)
{
    VerifyDerivedCounterCount(kGpaApiDirectx11, kGpaHwGenerationGfx10, GetExpectedPublicCounters(kGpaHwGenerationGfx10));
}

TEST(CounterDllTests, Dx11DerivedCounterBlocksGfx103)
{
    VerifyDerivedCounterCount(kGpaApiDirectx11, kGpaHwGenerationGfx103, GetExpectedPublicCounters(kGpaHwGenerationGfx103));
}

TEST(CounterDllTests, Dx11DerivedCounterBlocksGfx11)
{
    VerifyDerivedCounterCount(kGpaApiDirectx11, kGpaHwGenerationGfx11, GetExpectedPublicCounters(kGpaHwGenerationGfx11));
}

TEST(CounterDllTests, Dx11DerivedCounterBlocksGfx12)
{
    VerifyDerivedCounterCount(kGpaApiDirectx11, kGpaHwGenerationGfx12, GetExpectedPublicCounters(kGpaHwGenerationGfx12));
}

// Test the Dx11 counter names on all supported hardware
TEST(CounterDllTests, Dx11CounterNamesByDeviceId)
{
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdUnknown);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdSI);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdCI);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdCIHawaii);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdMi250X);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdMi210);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdUnsupported1);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdUnsupported2);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdVI);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdGfx8);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdGfx8Ellesmere);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdGfx8Tonga);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdGfx8Iceland);
    VerifyHardwareNotSupported(kGpaApiDirectx11, kDevIdGfx9);

    std::vector<const char*> derived_counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kDevIdGfx10, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kDevIdGfx10_3, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kDevIdGfx11, derived_counter_names, hardware_counter_names);

    // The variant hardware can only have the derived counter names verified.
    // GetExpectedCountersForGeneration() method in our tests is not thorough enough to create
    // the expected list of hardware counters for each variant.
    std::vector<const char*> empty_list_to_skip_tests;
    VerifyCounterNames(kGpaApiDirectx11, kDevIdGfx11_0_3, derived_counter_names, empty_list_to_skip_tests);
    VerifyCounterNames(kGpaApiDirectx11, kDevIdGfx11_0_3B, derived_counter_names, empty_list_to_skip_tests);
    VerifyCounterNames(kGpaApiDirectx11, kDevIdGfx11_5_0, derived_counter_names, empty_list_to_skip_tests);

    GetExpectedCountersForGeneration(kGpaHwGenerationGfx12, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kDevIdGfx12_0_1, derived_counter_names, hardware_counter_names);
}

TEST(CounterDllTests, Dx11CounterNamesGfx10)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, Dx11CounterNamesGfx103)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, Dx11CounterNamesGfx11)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, Dx11CounterNamesGfx12)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx12, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx12, counter_names, hardware_counter_names);
}

// Test the Dx11 counter names on all generations
TEST(CounterDllTests, Dx11CounterNamesByGeneration)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx11, kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, Dx11OpenCounterContext)
{
    VerifyOpenCounterContext(kGpaApiDirectx11, kGpaHwGenerationGfx10);
    VerifyOpenCounterContext(kGpaApiDirectx11, kGpaHwGenerationGfx103);
    VerifyOpenCounterContext(kGpaApiDirectx11, kGpaHwGenerationGfx11);
}

TEST(CounterDllTests, Dx11CounterLibTestGfx10)
{
    VerifyCounterLibInterface(kGpaApiDirectx11, kDevIdGfx10, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx11, kDevIdGfx10, REVISION_ID_ANY);
}

TEST(CounterDllTests, Dx11CounterLibTestGfx103)
{
    VerifyCounterLibInterface(kGpaApiDirectx11, kDevIdGfx10_3, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx11, kDevIdGfx10_3, REVISION_ID_ANY);
}

TEST(CounterDllTests, Dx11CounterLibTestGfx11)
{
    VerifyCounterLibInterface(kGpaApiDirectx11, kDevIdGfx11, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx11, kDevIdGfx11, REVISION_ID_ANY);
}

TEST(CounterDllTests, Dx11CounterLibTestGfx1103)
{
    VerifyCounterLibInterface(kGpaApiDirectx11, kDevIdGfx11_0_3, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx11, kDevIdGfx11_0_3, REVISION_ID_ANY);
}

TEST(CounterDllTests, Dx11CounterLibTestGfx1103B)
{
    VerifyCounterLibInterface(kGpaApiDirectx11, kDevIdGfx11_0_3B, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx11, kDevIdGfx11_0_3B, REVISION_ID_ANY);
}

TEST(CounterDllTests, Dx11CounterLibTestGfx1150)
{
    VerifyCounterLibInterface(kGpaApiDirectx11, kDevIdGfx11_5_0, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx11, kDevIdGfx11_5_0, REVISION_ID_ANY);
}

TEST(CounterDllTests, Dx11CounterFormulaTest)
{
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx10));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx103));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx11));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx12));
}
