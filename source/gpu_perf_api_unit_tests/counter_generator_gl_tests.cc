//==============================================================================
// Copyright (c) 2012-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Unit Tests for GL Counter Generator.
//==============================================================================

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_counter_generator/gpa_counter.h"

#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_oglp_gfx10.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_oglp_gfx103.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_oglp_gfx11.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_oglp_gfx12.h"

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_oglp_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_oglp_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_oglp_gfx11.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_oglp_gfx12.h"

#include "gpu_perf_api_unit_tests/counter_generator_tests.h"

static void GetExpectedCountersForGeneration(GpaHwGeneration           generation,
                                             std::vector<const char*>& derived_counter_names,
                                             std::vector<const char*>& hardware_counter_names)
{
    derived_counter_names.clear();
    hardware_counter_names.clear();

    const GpaCounterDesc* public_counters      = nullptr;
    size_t                public_counter_count = 0;

    gpa_array_view<gpa_array_view<GpaHardwareCounterDesc>> hardware_counter_groups;

    switch (generation)
    {
    case kGpaHwGenerationGfx10:
        public_counters         = kOglpGfx10PublicCounters;
        public_counter_count    = kOglpGfx10PublicCounterCount;
        hardware_counter_groups = counter_oglp_gfx10::kOglpCounterGroupArrayGfx10;
        break;

    case kGpaHwGenerationGfx103:
        public_counters         = kOglpGfx103PublicCounters;
        public_counter_count    = kOglpGfx103PublicCounterCount;
        hardware_counter_groups = counter_oglp_gfx103::kOglpCounterGroupArrayGfx103;
        break;

    case kGpaHwGenerationGfx11:
        public_counters         = kOglpGfx11PublicCounters;
        public_counter_count    = kOglpGfx11PublicCounterCount;
        hardware_counter_groups = counter_oglp_gfx11::kOglpCounterGroupArrayGfx11;
        break;

    case kGpaHwGenerationGfx12:
        public_counters         = kOglpGfx12PublicCounters;
        public_counter_count    = kOglpGfx12PublicCounterCount;
        hardware_counter_groups = counter_oglp_gfx12::kOglpCounterGroupArrayGfx12;
        break;

    default:
        assert(!"Unrecognized hardware generation in GetExpectedCountersForGeneration");
        break;
    }

    if (public_counters == nullptr || public_counter_count == 0)
    {
        assert(!"Failed to set public counters for unit tests.");
        return;
    }

    for (size_t i = 0; i < public_counter_count; i++)
    {
        derived_counter_names.push_back(public_counters[i].name);
    }

    const size_t num_hardware_counter_groups = hardware_counter_groups.size();
    for (size_t i = 0; i < num_hardware_counter_groups; ++i)
    {
        const size_t num_counters_in_group = hardware_counter_groups[i].size();
        for (size_t j = 0; j < num_counters_in_group; ++j)
        {
            hardware_counter_names.push_back(hardware_counter_groups[i][j].name);
        }
    }
}

static gpa_array_view<GpaCounterDesc> GetExpectedPublicCounters(GpaHwGeneration generation)
{
    const GpaCounterDesc*       public_counters      = nullptr;
    size_t                      public_counter_count = 0;

    switch (generation)
    {
    case kGpaHwGenerationGfx10:
        public_counters      = kOglpGfx10PublicCounters;
        public_counter_count = kOglpGfx10PublicCounterCount;
        break;

    case kGpaHwGenerationGfx103:
        public_counters      = kOglpGfx103PublicCounters;
        public_counter_count = kOglpGfx103PublicCounterCount;
        break;

    case kGpaHwGenerationGfx11:
        public_counters      = kOglpGfx11PublicCounters;
        public_counter_count = kOglpGfx11PublicCounterCount;
        break;

    case kGpaHwGenerationGfx12:
        public_counters      = kOglpGfx12PublicCounters;
        public_counter_count = kOglpGfx12PublicCounterCount;
        break;

    default:
        assert(!"Unrecognized hardware generation in GetExpectedPublicCounters");
        break;
    }

    return gpa_array_view<GpaCounterDesc>(public_counters, public_counter_count);
}

TEST(CounterDllTests, OpenGlUnsupportedHardwareGeneration)
{
    VerifyHardwareNotSupported(kGpaApiOpengl, kGpaHwGenerationNone);
    VerifyHardwareNotSupported(kGpaApiOpengl, kGpaHwGenerationNvidia);
    VerifyHardwareNotSupported(kGpaApiOpengl, kGpaHwGenerationIntel);
    VerifyHardwareNotSupported(kGpaApiOpengl, kGpaHwGenerationGfx6);
    VerifyHardwareNotSupported(kGpaApiOpengl, kGpaHwGenerationGfx7);
    VerifyHardwareNotSupported(kGpaApiOpengl, kGpaHwGenerationGfx8);
    VerifyHardwareNotSupported(kGpaApiOpengl, kGpaHwGenerationGfx9);
    VerifyHardwareNotSupported(kGpaApiOpengl, kGpaHwGenerationCdna);
    VerifyHardwareNotSupported(kGpaApiOpengl, kGpaHwGenerationCdna2);
    VerifyHardwareNotSupported(kGpaApiOpengl, kGpaHwGenerationCdna3);
}

TEST(CounterDllTests, OpenGlVerifyInvalidOpenContextParameters)
{
    VerifyInvalidOpenContextParameters(kGpaApiOpengl, kDevIdGfx11);
}

#ifdef _WIN32
// Test the OpenGl derived counter blocks
TEST(CounterDllTests, OpenGlDerivedCounterBlocksGfx10)
{
    VerifyDerivedCounterCount(kGpaApiOpengl, kGpaHwGenerationGfx10, GetExpectedPublicCounters(kGpaHwGenerationGfx10));
}

TEST(CounterDllTests, OpenGlDerivedCounterBlocksGfx103)
{
    VerifyDerivedCounterCount(kGpaApiOpengl, kGpaHwGenerationGfx103, GetExpectedPublicCounters(kGpaHwGenerationGfx103));
}

TEST(CounterDllTests, OpenGlDerivedCounterBlocksGfx11)
{
    VerifyDerivedCounterCount(kGpaApiOpengl, kGpaHwGenerationGfx11, GetExpectedPublicCounters(kGpaHwGenerationGfx11));
}

TEST(CounterDllTests, OpenGlDerivedCounterBlocksGfx12)
{
    VerifyDerivedCounterCount(kGpaApiOpengl, kGpaHwGenerationGfx12, GetExpectedPublicCounters(kGpaHwGenerationGfx12));
}

#endif

TEST(CounterDllTests, OpenGlUnsupportedDeviceId)
{
    // Verify that any unsupported Device IDs properly report that the hardware is not supported.
    for (auto const& device_id : kUnsupportedDeviceIds)
    {
        VerifyHardwareNotSupported(kGpaApiOpengl, device_id);
    }
}

TEST(CounterDllTests, OpenGlCounterNamesDeviceIdUnknown)
{
    VerifyHardwareNotSupported(kGpaApiOpengl, kDevIdUnknown);
}

TEST(CounterDllTests, OpenGlCounterNamesDeviceIdGfx10)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpengl, kDevIdGfx10, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, OpenGlCounterNamesDeviceIdGfx103)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpengl, kDevIdGfx10_3, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, OpenGlCounterNamesDeviceIdGfx11)
{
    std::vector<const char*> derived_counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpengl, kDevIdGfx11, derived_counter_names, hardware_counter_names);

    // The variant hardware can only have the derived counter names verified.
    // GetExpectedCountersForGeneration() method in our tests is not thorough enough to create
    // the expected list of hardware counters for each variant.
    std::vector<const char*> empty_list_to_skip_tests;
    VerifyCounterNames(kGpaApiOpengl, kDevIdGfx11_0_3, derived_counter_names, empty_list_to_skip_tests);
    VerifyCounterNames(kGpaApiOpengl, kDevIdGfx11_0_3B, derived_counter_names, empty_list_to_skip_tests);
    VerifyCounterNames(kGpaApiOpengl, kDevIdGfx11_5_0, derived_counter_names, empty_list_to_skip_tests);
    VerifyCounterNames(kGpaApiOpengl, kDevIdGfx11_5_3, derived_counter_names, empty_list_to_skip_tests);
}

TEST(CounterDllTests, OpenGlCounterNamesDeviceIdGfx12)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx12, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpengl, kDevIdGfx12_0_0, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, OpenGlCounterNamesGfx10)
{
    std::vector<const char*> derived_counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpengl, kGpaHwGenerationGfx10, derived_counter_names, hardware_counter_names);
}

TEST(CounterDllTests, OpenGlCounterNamesGfx103)
{
    std::vector<const char*> derived_counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpengl, kGpaHwGenerationGfx103, derived_counter_names, hardware_counter_names);
}

TEST(CounterDllTests, OpenGlCounterNamesGfx11)
{
    std::vector<const char*> derived_counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpengl, kGpaHwGenerationGfx11, derived_counter_names, hardware_counter_names);
}

TEST(CounterDllTests, OpenGlCounterNamesGfx12)
{
    std::vector<const char*> derived_counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx12, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpengl, kGpaHwGenerationGfx12, derived_counter_names, hardware_counter_names);
}

// Test the OpenGl counter names on all generations back-to-back.
TEST(CounterDllTests, OpenGlCounterNamesByGeneration)
{
    std::vector<const char*> derived_counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpengl, kGpaHwGenerationGfx10, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpengl, kGpaHwGenerationGfx103, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpengl, kGpaHwGenerationGfx11, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx12, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiOpengl, kGpaHwGenerationGfx12, derived_counter_names, hardware_counter_names);
}

TEST(CounterDllTests, OpenGlOpenCounterContext)
{
    VerifyOpenCounterContext(kGpaApiOpengl, kGpaHwGenerationGfx10);
    VerifyOpenCounterContext(kGpaApiOpengl, kGpaHwGenerationGfx103);
    VerifyOpenCounterContext(kGpaApiOpengl, kGpaHwGenerationGfx11);
    VerifyOpenCounterContext(kGpaApiOpengl, kGpaHwGenerationGfx12);
}

#ifdef _WIN32
TEST(CounterDllTests, GlCounterLibTestDeviceIdGfx10)
{
    VerifyCounterLibInterface(kGpaApiOpengl, kDevIdGfx10, AMDTDeviceInfoUtils::kRevisionIdAny);
    VerifyCounterByPassCounterLibEntry(kGpaApiOpengl, kDevIdGfx10, AMDTDeviceInfoUtils::kRevisionIdAny);
}

TEST(CounterDllTests, GlCounterLibTestDeviceIdGfx103)
{
    VerifyCounterLibInterface(kGpaApiOpengl, kDevIdGfx10_3, AMDTDeviceInfoUtils::kRevisionIdAny);
    VerifyCounterByPassCounterLibEntry(kGpaApiOpengl, kDevIdGfx10_3, AMDTDeviceInfoUtils::kRevisionIdAny);
}

TEST(CounterDllTests, GlCounterLibTestDeviceIdGfx11)
{
    VerifyCounterLibInterface(kGpaApiOpengl, kDevIdGfx11, AMDTDeviceInfoUtils::kRevisionIdAny);
    VerifyCounterByPassCounterLibEntry(kGpaApiOpengl, kDevIdGfx11, AMDTDeviceInfoUtils::kRevisionIdAny);
}

TEST(CounterDllTests, GlCounterLibTestDeviceIdGfx1103)
{
    VerifyCounterLibInterface(kGpaApiOpengl, kDevIdGfx11_0_3, AMDTDeviceInfoUtils::kRevisionIdAny);
    VerifyCounterByPassCounterLibEntry(kGpaApiOpengl, kDevIdGfx11_0_3, AMDTDeviceInfoUtils::kRevisionIdAny);
}

TEST(CounterDllTests, GlCounterLibTestDeviceIdGfx1103B)
{
    VerifyCounterLibInterface(kGpaApiOpengl, kDevIdGfx11_0_3B, AMDTDeviceInfoUtils::kRevisionIdAny);
    VerifyCounterByPassCounterLibEntry(kGpaApiOpengl, kDevIdGfx11_0_3B, AMDTDeviceInfoUtils::kRevisionIdAny);
}

TEST(CounterDllTests, GlCounterLibTestGfx1150)
{
    VerifyCounterLibInterface(kGpaApiOpengl, kDevIdGfx11_5_0, AMDTDeviceInfoUtils::kRevisionIdAny);
    VerifyCounterByPassCounterLibEntry(kGpaApiOpengl, kDevIdGfx11_5_0, AMDTDeviceInfoUtils::kRevisionIdAny);
}

TEST(CounterDllTests, GlCounterLibTestGfx1153)
{
    VerifyCounterLibInterface(kGpaApiOpengl, kDevIdGfx11_5_3, AMDTDeviceInfoUtils::kRevisionIdAny);
    VerifyCounterByPassCounterLibEntry(kGpaApiOpengl, kDevIdGfx11_5_3, AMDTDeviceInfoUtils::kRevisionIdAny);
}

#endif

TEST(CounterDllTests, GLCounterFormulaTest)
{
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx10));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx103));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx11));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx12));
}

TEST(GpaCounterLibGetSupportedSampleTypes, Opengl)
{
    VerifySupportedSampleTypes(kGpaApiOpengl);
}
