//==============================================================================
// Copyright (c) 2012-2021 Advanced Micro Devices, Inc. All rights reserved.
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

#ifdef AMDT_INTERNAL
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_cl_gfx8.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_cl_gfx9.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_cl_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_cl_gfx103.h"
#endif

#include "gpu_perf_api_unit_tests/counter_generator_tests.h"
#include "gpu_perf_api_unit_tests/counters/gpa_counter_desc.h"

static void GetExpectedCountersForGeneration(GpaHwGeneration gen, std::vector<const char*>& counter_names)
{
    counter_names.clear();

    const GpaCounterDesc* public_derived_counters      = nullptr;
    size_t                public_derived_counter_count = 0;

    GpaCounterGroupDesc*     hardware_groups   = nullptr;
    GpaHardwareCounterDesc** hardware_counters = nullptr;
    unsigned int             group_count       = 0;

    switch (gen)
    {
    case kGpaHwGenerationGfx8:
        public_derived_counters      = kClGfx8PublicCounters;
        public_derived_counter_count = kClGfx8PublicCounterCount;
#ifdef AMDT_INTERNAL
        hardware_groups   = counter_cl_gfx8::kHwClGroupsGfx8;
        group_count       = counter_cl_gfx8::kHwClGroupCountGfx8;
        hardware_counters = counter_cl_gfx8::kClCounterGroupArrayGfx8;
#endif
        break;

    case kGpaHwGenerationGfx9:
        public_derived_counters      = kClGfx9PublicCounters;
        public_derived_counter_count = kClGfx9PublicCounterCount;
#ifdef AMDT_INTERNAL
        hardware_groups   = counter_cl_gfx9::kHwClGroupsGfx9;
        group_count       = counter_cl_gfx9::kHwClGroupCountGfx9;
        hardware_counters = counter_cl_gfx9::kClCounterGroupArrayGfx9;
#endif
        break;

    case kGpaHwGenerationGfx10:
        public_derived_counters      = kClGfx10PublicCounters;
        public_derived_counter_count = kClGfx10PublicCounterCount;
#ifdef AMDT_INTERNAL
        hardware_groups   = counter_cl_gfx10::kHwClGroupsGfx10;
        group_count       = counter_cl_gfx10::kHwClGroupCountGfx10;
        hardware_counters = counter_cl_gfx10::kClCounterGroupArrayGfx10;
#endif
        break;

    case kGpaHwGenerationGfx103:
        public_derived_counters      = kClGfx103PublicCounters;
        public_derived_counter_count = kClGfx103PublicCounterCount;
#ifdef AMDT_INTERNAL
        hardware_groups   = counter_cl_gfx103::kHwClGroupsGfx103;
        group_count       = counter_cl_gfx103::kHwClGroupCountGfx103;
        hardware_counters = counter_cl_gfx103::kClCounterGroupArrayGfx103;
#endif
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

#ifdef AMDT_INTERNAL
    GpaGetInternalDerivedCounters(kGpaApiOpencl, gen, &kInternalDerivedCounters, &internal_derived_counter_count);
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
}

// Test the openCL counter names on each generation
TEST(CounterDllTests, OpenClCounterNamesByGeneration)
{
    VerifyHardwareNotSupported(kGpaApiOpencl, kGpaHwGenerationNvidia, FALSE);
    VerifyHardwareNotSupported(kGpaApiOpencl, kGpaHwGenerationIntel, FALSE);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx8, counterNames);
    VerifyCounterNames(kGpaApiOpencl, kGpaHwGenerationGfx8, FALSE, counterNames);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx9, counterNames);
    VerifyCounterNames(kGpaApiOpencl, kGpaHwGenerationGfx9, FALSE, counterNames);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counterNames);
    VerifyCounterNames(kGpaApiOpencl, kGpaHwGenerationGfx10, FALSE, counterNames);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counterNames);
    VerifyCounterNames(kGpaApiOpencl, kDevIdGfx10_3, FALSE, counterNames);
}

TEST(CounterDllTests, ClCounterLibTest)
{
    VerifyCounterLibInterface(kGpaApiOpencl, kDevIdVI, REVISION_ID_ANY, false);
    VerifyCounterLibInterface(kGpaApiOpencl, kDevIdGfx9, REVISION_ID_ANY, false);
    VerifyCounterLibInterface(kGpaApiOpencl, kDevIdGfx10, REVISION_ID_ANY, false);
    VerifyCounterLibInterface(kGpaApiOpencl, kDevIdGfx10_3, REVISION_ID_ANY, false);
}

TEST(CounterDllTests, ClCounterFormulaTest)
{
    std::vector<const char*> counterNames;
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx8));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx9));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx10));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx103));
}

TEST(CounterDllTests, OpenClMultipleGenerations)
{
    LibHandle libHandle = LoadLib(kCountersLibName);
    ASSERT_NE((LibHandle) nullptr, libHandle);

    UnloadLib(libHandle);
}