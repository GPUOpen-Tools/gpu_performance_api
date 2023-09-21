//==============================================================================
// Copyright (c) 2012-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Unit Tests for CL Counter Generator.
//==============================================================================

#include <algorithm>

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_counter_generator/gpa_counter.h"

#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_cl_gfx8.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_cl_gfx9.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_cl_gfx10.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_cl_gfx103.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_cl_gfx11.h"

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_cl_gfx8.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_cl_gfx9.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_cl_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_cl_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_cl_gfx11.h"

#include "gpu_perf_api_unit_tests/counter_generator_tests.h"
#include "gpu_perf_api_unit_tests/counters/gpa_counter_desc.h"

static void GetExpectedCountersForGeneration(GpaHwGeneration           generation,
                                             std::vector<const char*>& derived_counter_names,
                                             std::vector<const char*>& hardware_counter_names)
{
    derived_counter_names.clear();
    hardware_counter_names.clear();

    const GpaCounterDesc* public_derived_counters      = nullptr;
    size_t                public_derived_counter_count = 0;

    std::vector<std::vector<GpaHardwareCounterDesc>*> hardware_counter_groups;

    switch (generation)
    {
    case kGpaHwGenerationGfx8:
        public_derived_counters      = kClGfx8PublicCounters;
        public_derived_counter_count = kClGfx8PublicCounterCount;
        hardware_counter_groups      = counter_cl_gfx8::kClCounterGroupArrayGfx8;
        break;

    case kGpaHwGenerationGfx9:
        public_derived_counters      = kClGfx9PublicCounters;
        public_derived_counter_count = kClGfx9PublicCounterCount;
        hardware_counter_groups      = counter_cl_gfx9::kClCounterGroupArrayGfx9;
        break;

    case kGpaHwGenerationGfx10:
        public_derived_counters      = kClGfx10PublicCounters;
        public_derived_counter_count = kClGfx10PublicCounterCount;
        hardware_counter_groups      = counter_cl_gfx10::kClCounterGroupArrayGfx10;
        break;

    case kGpaHwGenerationGfx103:
        public_derived_counters      = kClGfx103PublicCounters;
        public_derived_counter_count = kClGfx103PublicCounterCount;
        hardware_counter_groups      = counter_cl_gfx103::kClCounterGroupArrayGfx103;
        break;

    case kGpaHwGenerationGfx11:
        public_derived_counters      = kClGfx11PublicCounters;
        public_derived_counter_count = kClGfx11PublicCounterCount;
        hardware_counter_groups      = counter_cl_gfx11::kClCounterGroupArrayGfx11;
        break;

    default:
        assert(!"Unrecognized hardware generation in GetExpectedCountersForGeneration");
        break;
    }

    for (size_t i = 0; i < public_derived_counter_count; i++)
    {
        derived_counter_names.push_back(public_derived_counters[i].name);
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
        public_counters      = kClGfx8PublicCounters;
        public_counter_count = kClGfx8PublicCounterCount;
        break;

    case kGpaHwGenerationGfx9:
        public_counters      = kClGfx9PublicCounters;
        public_counter_count = kClGfx9PublicCounterCount;
        break;

    case kGpaHwGenerationGfx10:
        public_counters      = kClGfx10PublicCounters;
        public_counter_count = kClGfx10PublicCounterCount;
        break;

    case kGpaHwGenerationGfx103:
        public_counters      = kClGfx103PublicCounters;
        public_counter_count = kClGfx103PublicCounterCount;
        break;

    case kGpaHwGenerationGfx11:
        public_counters      = kClGfx11PublicCounters;
        public_counter_count = kClGfx11PublicCounterCount;
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

TEST(CounterDllTests, OpenClUnsupportedHardwareGenerations)
{
    VerifyHardwareNotSupported(kGpaApiOpencl, kGpaHwGenerationNone, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kGpaHwGenerationNvidia, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kGpaHwGenerationIntel, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kGpaHwGenerationGfx6, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kGpaHwGenerationGfx7, FALSE);
}

// Test the OpenCL derived counter blocks
TEST(CounterDllTests, OpenClDerivedCounterBlocks)
{
    VerifyDerivedCounterCount(kGpaApiOpencl, kGpaHwGenerationGfx8, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx8));
    VerifyDerivedCounterCount(kGpaApiOpencl, kGpaHwGenerationGfx9, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx9));
    VerifyDerivedCounterCount(kGpaApiOpencl, kGpaHwGenerationGfx10, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx10));
    VerifyDerivedCounterCount(kGpaApiOpencl, kGpaHwGenerationGfx103, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx103));
    VerifyDerivedCounterCount(kGpaApiOpencl, kGpaHwGenerationGfx11, FALSE, GetExpectedPublicCounters(kGpaHwGenerationGfx11));
}

// Test the openCL counter names on all supported hardware
TEST(CounterDllTests, OpenClCounterNamesByDeviceId)
{
    VerifyHardwareNotSupported(kGpaApiOpencl, kDevIdUnknown, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kDevIdSI, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kDevIdCI, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kDevIdCIHawaii, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kDevIdMi250X, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kDevIdMi210, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kDevIdUnsupported1, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kDevIdUnsupported2, FALSE);

    std::vector<const char*> derived_counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpencl, kDevIdVI, FALSE, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpencl, kDevIdGfx9, FALSE, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpencl, kDevIdGfx10, FALSE, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpencl, kDevIdGfx10_3, FALSE, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpencl, kDevIdGfx11, FALSE, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpencl, kDevIdGfx11_0_3, FALSE, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpencl, kDevIdGfx11_0_3B, FALSE, derived_counter_names, hardware_counter_names);
}

// Test the openCL counter names on each generation
TEST(CounterDllTests, OpenClCounterNamesGfx8)
{
    std::vector<const char*> derived_counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpencl, kGpaHwGenerationGfx8, FALSE, derived_counter_names, hardware_counter_names);
}

TEST(CounterDllTests, OpenClCounterNamesGfx9)
{
    std::vector<const char*> derived_counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpencl, kGpaHwGenerationGfx9, FALSE, derived_counter_names, hardware_counter_names);
}

TEST(CounterDllTests, OpenClCounterNamesGfx10)
{
    std::vector<const char*> derived_counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpencl, kGpaHwGenerationGfx10, FALSE, derived_counter_names, hardware_counter_names);
}

TEST(CounterDllTests, OpenClCounterNamesGfx103)
{
    std::vector<const char*> derived_counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpencl, kGpaHwGenerationGfx103, FALSE, derived_counter_names, hardware_counter_names);
}

TEST(CounterDllTests, OpenClCounterNamesGfx11)
{
    std::vector<const char*> derived_counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpencl, kGpaHwGenerationGfx11, FALSE, derived_counter_names, hardware_counter_names);
}

TEST(CounterDllTests, ClOpenCounterContext)
{
    VerifyOpenCounterContext(kGpaApiOpencl, kGpaHwGenerationGfx8);
    VerifyOpenCounterContext(kGpaApiOpencl, kGpaHwGenerationGfx9);
    VerifyOpenCounterContext(kGpaApiOpencl, kGpaHwGenerationGfx10);
    VerifyOpenCounterContext(kGpaApiOpencl, kGpaHwGenerationGfx103);
    VerifyOpenCounterContext(kGpaApiOpencl, kGpaHwGenerationGfx11);
}

TEST(CounterDllTests, ClCounterLibTestGfx8)
{
    VerifyCounterLibInterface(kGpaApiOpencl, kDevIdVI, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, ClCounterLibTestGfx9)
{
    VerifyCounterLibInterface(kGpaApiOpencl, kDevIdGfx9, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, ClCounterLibTestGfx10)
{
    VerifyCounterLibInterface(kGpaApiOpencl, kDevIdGfx10, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, ClCounterLibTestGfx103)
{
    VerifyCounterLibInterface(kGpaApiOpencl, kDevIdGfx10_3, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, ClCounterLibTestGfx11)
{
    VerifyCounterLibInterface(kGpaApiOpencl, kDevIdGfx11, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, ClCounterLibTestGfx1103)
{
    VerifyCounterLibInterface(kGpaApiOpencl, kDevIdGfx11_0_3, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, ClCounterLibTestGfx1103B)
{
    VerifyCounterLibInterface(kGpaApiOpencl, kDevIdGfx11_0_3B, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, ClCounterFormulaTest)
{
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx8));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx9));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx10));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx103));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx11));
}

TEST(CounterDllTests, OpenClMultipleGenerations)
{
    LibHandle libHandle = LoadLib(kCountersLibName);
    ASSERT_NE((LibHandle) nullptr, libHandle);

    UnloadLib(libHandle);
}