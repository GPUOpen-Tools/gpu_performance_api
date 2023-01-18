//==============================================================================
// Copyright (c) 2012-2022 Advanced Micro Devices, Inc. All rights reserved.
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

#include "gpu_perf_api_unit_tests/counter_generator_tests.h"
#include "gpu_perf_api_unit_tests/counters/gpa_counter_desc.h"

static void GetExpectedCountersForGeneration(GpaHwGeneration gen, std::vector<const char*>& counter_names)
{
    counter_names.clear();

    const GpaCounterDesc* public_derived_counters      = nullptr;
    size_t                public_derived_counter_count = 0;

    std::vector<GpaCounterGroupDesc>     hardware_groups;
    std::vector<std::vector<GpaHardwareCounterDesc>*> hardware_counters;
    unsigned int             group_count       = 0;

    switch (gen)
    {
    case kGpaHwGenerationGfx8:
        public_derived_counters      = kClGfx8PublicCounters;
        public_derived_counter_count = kClGfx8PublicCounterCount;
        break;

    case kGpaHwGenerationGfx9:
        public_derived_counters      = kClGfx9PublicCounters;
        public_derived_counter_count = kClGfx9PublicCounterCount;
        break;

    case kGpaHwGenerationGfx10:
        public_derived_counters      = kClGfx10PublicCounters;
        public_derived_counter_count = kClGfx10PublicCounterCount;
        break;

    case kGpaHwGenerationGfx103:
        public_derived_counters      = kClGfx103PublicCounters;
        public_derived_counter_count = kClGfx103PublicCounterCount;
        break;

    case kGpaHwGenerationGfx11:
        public_derived_counters      = kClGfx11PublicCounters;
        public_derived_counter_count = kClGfx11PublicCounterCount;
        break;


    default:
        break;
    }

    for (size_t i = 0; i < public_derived_counter_count; i++)
    {
        counter_names.push_back(public_derived_counters[i].name);
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
TEST(CounterDllTests, OpenClCounterNames)
{
    VerifyHardwareNotSupported(kGpaApiOpencl, kDevIdUnknown, FALSE);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, counterNames);
    VerifyCounterNames(kGpaApiOpencl, kDevIdVI, FALSE, counterNames);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, counterNames);
    VerifyCounterNames(kGpaApiOpencl, kDevIdGfx9, FALSE, counterNames);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counterNames);
    VerifyCounterNames(kGpaApiOpencl, kDevIdGfx10, FALSE, counterNames);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counterNames);
    VerifyCounterNames(kGpaApiOpencl, kDevIdGfx10_3, FALSE, counterNames);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, counterNames);
    VerifyCounterNames(kGpaApiOpencl, kDevIdGfx11, FALSE, counterNames);
}

// Test the openCL counter names on each generation
TEST(CounterDllTests, OpenClCounterNamesByGeneration)
{
    VerifyHardwareNotSupported(kGpaApiOpencl, kGpaHwGenerationNone, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kGpaHwGenerationNvidia, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kGpaHwGenerationIntel, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kGpaHwGenerationGfx6, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kGpaHwGenerationGfx7, FALSE);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, counterNames);
    VerifyCounterNames(kGpaApiOpencl, kGpaHwGenerationGfx8, FALSE, counterNames);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, counterNames);
    VerifyCounterNames(kGpaApiOpencl, kGpaHwGenerationGfx9, FALSE, counterNames);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counterNames);
    VerifyCounterNames(kGpaApiOpencl, kGpaHwGenerationGfx10, FALSE, counterNames);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counterNames);
    VerifyCounterNames(kGpaApiOpencl, kGpaHwGenerationGfx103, FALSE, counterNames);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, counterNames);
    VerifyCounterNames(kGpaApiOpencl, kGpaHwGenerationGfx11, FALSE, counterNames);
}

TEST(CounterDllTests, ClOpenCounterContext)
{
    VerifyHardwareNotSupported(kGpaApiOpencl, kGpaHwGenerationNone, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kGpaHwGenerationNvidia, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kGpaHwGenerationIntel, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kGpaHwGenerationGfx6, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kGpaHwGenerationGfx7, FALSE);

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

TEST(CounterDllTests, ClCounterFormulaTest)
{
    std::vector<const char*> counterNames;
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