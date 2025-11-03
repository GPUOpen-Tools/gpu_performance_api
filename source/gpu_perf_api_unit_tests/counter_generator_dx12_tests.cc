//==============================================================================
// Copyright (c) 2012-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Unit Tests for Dx12 Counter Generator.
//==============================================================================

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_counter_generator/gpa_counter.h"

#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx12_gfx10.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx12_gfx103.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx12_gfx11.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx12_gfx12.h"

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx11.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx12.h"

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

    gpa_array_view<gpa_array_view<GpaHardwareCounterDesc>> hardware_counter_groups;

    switch (generation)
    {
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

    case kGpaHwGenerationGfx12:
        public_counters         = kDx12Gfx12PublicCounters;
        public_counter_count    = kDx12Gfx12PublicCounterCount;
        hardware_counter_groups = counter_dx12_gfx12::kDx12CounterGroupArrayGfx12;
        break;

    default:
        assert(!"Unrecognized hardware generation in GetExpectedCountersForGeneration");
        break;
    }

    for (size_t i = 0; i < public_counter_count; i++)
    {
        // Skip all the SPM counters which aren't discrete counters
        if (public_counters[i].spm_counter && !public_counters[i].discrete_counter)
        {
            continue;
        }

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
    const GpaCounterDesc* public_counters      = nullptr;
    size_t                public_counter_count = 0;

    switch (generation)
    {
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

    case kGpaHwGenerationGfx12:
        public_counters      = kDx12Gfx12PublicCounters;
        public_counter_count = kDx12Gfx12PublicCounterCount;
        break;

    default:
        assert(!"Unrecognized hardware generation in GetExpectedPublicCounters");
        break;
    }

    return gpa_array_view<GpaCounterDesc>(public_counters, public_counter_count);
}

TEST(CounterDllTests, Dx12UnsupportedHardwareGenerations)
{
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationNone);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationNvidia);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationIntel);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationGfx6);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationGfx7);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationGfx8);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationGfx9);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationCdna);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationCdna2);
    VerifyHardwareNotSupported(kGpaApiDirectx12, kGpaHwGenerationCdna3);
}

TEST(CounterDllTests, Dx12VerifyInvalidOpenContextParameters)
{
    VerifyInvalidOpenContextParameters(kGpaApiDirectx12, kDevIdGfx11);
}

// Test the Dx12 derived counter blocks
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

TEST(CounterDllTests, Dx12DerivedCounterBlocksGfx12)
{
    VerifyDerivedCounterCount(kGpaApiDirectx12, kGpaHwGenerationGfx12, GetExpectedPublicCounters(kGpaHwGenerationGfx12));
}

// Test the Dx12 counter names on all supported hardware
TEST(CounterDllTests, Dx12CounterNamesByDeviceId)
{
    for (auto const& device_id : kUnsupportedDeviceIds)
    {
        VerifyHardwareNotSupported(kGpaApiDirectx12, device_id);
    }

    std::vector<const char*> derived_counter_names;
    std::vector<const char*> hardware_counter_names;
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
    VerifyCounterNames(kGpaApiDirectx12, kDevIdGfx11_5_3, derived_counter_names, empty_list_to_skip_tests);

    GetExpectedCountersForGeneration(kGpaHwGenerationGfx12, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kDevIdGfx12_0_0, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kDevIdGfx12_0_1, derived_counter_names, hardware_counter_names);
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

TEST(CounterDllTests, Dx12CounterNamesGfx12)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx12, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx12, counter_names, hardware_counter_names);
}

// Test the Dx12 counter names on all generations
TEST(CounterDllTests, Dx12CounterNamesByGeneration)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx12, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiDirectx12, kGpaHwGenerationGfx12, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, Dx12OpenCounterContext)
{
    VerifyOpenCounterContext(kGpaApiDirectx12, kGpaHwGenerationGfx10);
    VerifyOpenCounterContext(kGpaApiDirectx12, kGpaHwGenerationGfx103);
    VerifyOpenCounterContext(kGpaApiDirectx12, kGpaHwGenerationGfx11);
    VerifyOpenCounterContext(kGpaApiDirectx12, kGpaHwGenerationGfx12);
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

TEST(CounterDllTests, Dx12CounterLibTestGfx1153)
{
    VerifyCounterLibInterface(kGpaApiDirectx12, kDevIdGfx11_5_3, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiDirectx12, kDevIdGfx11_5_3, REVISION_ID_ANY);
}

TEST(CounterDllTests, Dx12CounterFormulaTest)
{
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx10));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx103));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx11));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx12));
}

// Currently this test will only work with the DX12 API. Since only DX12 supports kGpaSessionSampleTypeStreamingCounter
TEST(ComputeDerivedCounterResult, WaveOccupancyPct)
{
    LibHandle              handle                     = {};
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    GpaCounterContext      gpa_counter_context        = {};
    if (LoadAndVerifyCounterLib(&handle, &gpa_counter_lib_func_table))
    {
        GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, kDevIdGfx10, REVISION_ID_ANY, nullptr, 0};
        GpaStatus                     status                        = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
            kGpaApiDirectx12, kGpaSessionSampleTypeStreamingCounter, counter_context_hardware_info, kGpaOpenContextDefaultBit, &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, status);

        if (status == kGpaStatusOk)
        {
            uint32_t        index      = {};
            GpaCounterParam param      = {};
            param.is_derived_counter   = true;
            param.derived_counter_name = "WaveOccupancyPct";
            status                     = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param, &index);
            EXPECT_EQ(kGpaStatusOk, status);

            if (status == kGpaStatusOk)
            {
                GpaFloat64 result = {};

                // Trigger various invalid parameter issues
                {
                    const GpaCounterContext bad_context = reinterpret_cast<GpaCounterContext>(0xBADF00D);
                    constexpr uint64_t      foo         = {};

                    status = gpa_counter_lib_func_table.GpaCounterLibComputeDerivedCounterResult(nullptr, index, &foo, 1, &result);
                    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

                    status = gpa_counter_lib_func_table.GpaCounterLibComputeDerivedCounterResult(bad_context, index, &foo, 1, &result);
                    EXPECT_EQ(kGpaStatusErrorContextNotOpen, status);

                    status = gpa_counter_lib_func_table.GpaCounterLibComputeDerivedCounterResult(gpa_counter_context, index, &foo, 0, &result);
                    EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);

                    status = gpa_counter_lib_func_table.GpaCounterLibComputeDerivedCounterResult(gpa_counter_context, index, nullptr, 1, &result);
                    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

                    status = gpa_counter_lib_func_table.GpaCounterLibComputeDerivedCounterResult(gpa_counter_context, index, &foo, 1, nullptr);
                    EXPECT_EQ(kGpaStatusErrorNullPointer, status);
                }

                // name=WaveOccupancyPct
                // desc=#WaveDistribution#The percentage of the maximum wavefront occupancy that is currently being used.
                // type=gpa_float64
                // usage=percentage
                // spm=1
                // discrete=0
                // [DX12Gfx10]
                // SQ*_PERF_SEL_LEVEL_WAVES[0..1]
                // eqn=0,1,+,MAX_WAVES,/,(100),*
                std::array<uint64_t, 2> fake_counter_data      = {0, 0};
                constexpr uint32_t      fake_counter_data_size = static_cast<uint32_t>(fake_counter_data.size());

                // Intentially get 0% WaveOccupancyPct
                {
                    status = gpa_counter_lib_func_table.GpaCounterLibComputeDerivedCounterResult(
                        gpa_counter_context, index, fake_counter_data.data(), fake_counter_data_size, &result);

                    EXPECT_EQ(kGpaStatusOk, status);
                    EXPECT_EQ(result, 0.0);
                }

                // Intentially get 100% WaveOccupancyPct
                //
                // NOTE: This value is hard coded for this test to get 100% based on a GFX10 GPU with no revision ID.
                // (num_simds * num_waves_per_simd) / num_shader_engines
                constexpr uint64_t kMaxWavesPerSe = (80 * 20) / 2;
                {
                    fake_counter_data.fill(kMaxWavesPerSe);

                    status = gpa_counter_lib_func_table.GpaCounterLibComputeDerivedCounterResult(
                        gpa_counter_context, index, fake_counter_data.data(), fake_counter_data_size, &result);

                    EXPECT_EQ(kGpaStatusOk, status);
                    EXPECT_EQ(result, 100.0);
                }

                // Intentially get 50% WaveOccupancyPct
                {
                    fake_counter_data.fill(kMaxWavesPerSe / 2);

                    status = gpa_counter_lib_func_table.GpaCounterLibComputeDerivedCounterResult(
                        gpa_counter_context, index, fake_counter_data.data(), fake_counter_data_size, &result);
                    EXPECT_EQ(kGpaStatusOk, status);
                    EXPECT_EQ(result, 50.0);
                }

                // Intentially pass incorrect amount of fake counter data
                {
                    const uint32_t bad_counter_data_size = fake_counter_data_size + 1;
                    status                               = gpa_counter_lib_func_table.GpaCounterLibComputeDerivedCounterResult(
                        gpa_counter_context, index, fake_counter_data.data(), bad_counter_data_size, &result);
                    EXPECT_EQ(kGpaStatusErrorFailed, status);
                }

                // Intentially pass invalid index
                {
                    const uint32_t bad_index = index + 1;
                    status                   = gpa_counter_lib_func_table.GpaCounterLibComputeDerivedCounterResult(
                        gpa_counter_context, bad_index, fake_counter_data.data(), fake_counter_data_size, &result);
                    EXPECT_EQ(kGpaStatusErrorFailed, status);
                }
            }
        }

        status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, status);

        UnloadLib(handle);
    }
}

// Test all sorts of invalid parameters / situations for GpaCounterlibComputeDerivedSpmCounterResults
// Some are as simple as checking for nullptr. But others are verifying the counter data, and sizes passed in.
TEST(ComputeDerivedSpmCounterResults, InvalidParameters)
{
    LibHandle              handle                     = {};
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    GpaCounterContext      gpa_counter_context        = {};
    if (LoadAndVerifyCounterLib(&handle, &gpa_counter_lib_func_table))
    {
        GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, kDevIdGfx12_0_0, REVISION_ID_ANY, nullptr, 0};
        GpaStatus                     status                        = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
            kGpaApiDirectx12, kGpaSessionSampleTypeStreamingCounter, counter_context_hardware_info, kGpaOpenContextDefaultBit, &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, status);

        if (status == kGpaStatusOk)
        {
            GpaUInt32       wave_occupancy_index = {};
            GpaCounterParam param                = {};
            param.is_derived_counter             = true;
            param.derived_counter_name           = "WaveOccupancyPct";
            status                               = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param, &wave_occupancy_index);
            EXPECT_EQ(kGpaStatusOk, status);

            if (status == kGpaStatusOk)
            {
                GpaSpmData spm_data = {};

                constexpr std::array<GpaUInt64, 3> kTimeStampData = {0, 0, 0};
                spm_data.timestamps                               = kTimeStampData.data();
                spm_data.number_of_timestamps                     = static_cast<uint32_t>(kTimeStampData.size());

                // There are 32 SQWGP*_SQ_PERF_SEL_LEVEL_WAVES[0..31] IDs for WaveOccupancyPct on GFX12
                std::array<GpaSpmCounterInfo, 32> spm_counter_info = {};
                for (uint32_t i = 0; i < spm_counter_info.size(); ++i)
                {
                    // We are able to verify the block id, event index, and instance.
                    // So this information needs to be valid.
                    spm_counter_info[i].gpu_block_id       = kGpaHwBlockSqWgp;
                    spm_counter_info[i].event_index        = 7;
                    spm_counter_info[i].gpu_block_instance = i;
                    spm_counter_info[i].data_offset        = i * static_cast<uint32_t>(kTimeStampData.size());
                }
                spm_data.spm_counter_info           = spm_counter_info.data();
                spm_data.number_of_spm_counter_info = static_cast<uint32_t>(spm_counter_info.size());

                constexpr size_t counter_data_size = spm_counter_info.size() * kTimeStampData.size();

                const std::array<uint16_t, counter_data_size> counter_data = {};
                spm_data.counter_data_16bit                                = counter_data.data();
                spm_data.number_of_counter_data                            = static_cast<uint32_t>(counter_data_size);
                spm_data.number_of_bytes_per_counter_data                  = 2;

                const std::array<GpaUInt32, 1> gpa_counter_indices = {wave_occupancy_index};

                // Note: This is the only array we can't validate.
                std::array<GpaFloat64, kTimeStampData.size()> results = {};

                // Keep a copy of the original spm data so we can easily restore it.
                // Not the most optimal way but easy to maintain.
                const GpaSpmData original_spm_data = spm_data;

                // The counterlibrary cannot validate this information for the user.
                static_assert(results.size() == gpa_counter_indices.size() * kTimeStampData.size());

                // Pass in all "valid" data. The result will be nonsense but it doesn't matter.
                // The goal is just to make sure we go through the function successfully once.
                // Then slowly start testing invalid parameters/situations.
                status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                    gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                EXPECT_EQ(kGpaStatusOk, status);

                // Test all nullptr situations.
                {
                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        nullptr, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, nullptr, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), nullptr, results.data());
                    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), nullptr);
                    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

                    spm_data.counter_data_16bit = nullptr;

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

                    spm_data                  = original_spm_data;
                    spm_data.spm_counter_info = nullptr;

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

                    spm_data            = original_spm_data;
                    spm_data.timestamps = nullptr;

                    // It should be noted that the timestamp data isn't utilized by GPA in any meaningful way.
                    // Aside from a quick nullptr check. GPA really only cares about the number of timestamps in order
                    // to properly index the counter_data_16bit.
                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusErrorNullPointer, status);

                    spm_data = original_spm_data;
                }

                // Invalid context
                {
                    const GpaCounterContext bad_context = reinterpret_cast<GpaCounterContext>(0xBADF00D);

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        bad_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusErrorContextNotOpen, status);
                }

                // Invalid parameter checks
                {
                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, 0, gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);

                    spm_data.number_of_counter_data = 0;

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);

                    spm_data                      = original_spm_data;
                    spm_data.number_of_timestamps = 0;

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);

                    spm_data                            = original_spm_data;
                    spm_data.number_of_spm_counter_info = 0;

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);

                    // Test to ensure the sizes being passed are validated.
                    // number_of_timestamps * number_of_spm_counter_info == number_of_counter_data
                    {
                        ++spm_data.spm_counter_info;
                        status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                            gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                        EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);

                        spm_data = original_spm_data;
                        ++spm_data.number_of_timestamps;

                        status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                            gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                        EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);

                        spm_data = original_spm_data;
                        ++spm_data.number_of_counter_data;

                        status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                            gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                        EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);

                        spm_data = original_spm_data;
                    }

                    spm_data = original_spm_data;
                    // Test various invalid bytes per counter.
                    for (GpaUInt32 i : {0, 1, 3, 5, 6, 7, 8})
                    {
                        spm_data.number_of_bytes_per_counter_data = i;
                        status                                    = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                            gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                        EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);
                    }
                    spm_data = original_spm_data;
                }

                // Invalid GpaSpmCounterInfo data.
                {
                    for (GpaSpmCounterInfo& info : spm_counter_info)
                    {
                        // Invalid block id.
                        info.gpu_block_id = 0;
                    }
                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);
                    for (GpaSpmCounterInfo& info : spm_counter_info)
                    {
                        info.gpu_block_id = kGpaHwBlockSqWgp;

                        // Now test an invalid offset. data_offset must be a multiple of the number of timestamps.
                        --info.data_offset;
                    }
                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);
                }
            }
        }

        status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, status);

        UnloadLib(handle);
    }
}

// Verify WaveOccupancyPct is working correctly for 3 timestamps.
TEST(ComputeDerivedSpmCounterResults, WaveOccupancyPct)
{
    LibHandle              handle                     = {};
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    GpaCounterContext      gpa_counter_context        = {};
    if (LoadAndVerifyCounterLib(&handle, &gpa_counter_lib_func_table))
    {
        GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, kDevIdGfx12_0_0, REVISION_ID_ANY, nullptr, 0};
        GpaStatus                     status                        = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
            kGpaApiDirectx12, kGpaSessionSampleTypeStreamingCounter, counter_context_hardware_info, kGpaOpenContextDefaultBit, &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, status);

        if (status == kGpaStatusOk)
        {
            GpaUInt32       wave_occupancy_index = {};
            GpaCounterParam param                = {};
            param.is_derived_counter             = true;
            param.derived_counter_name           = "WaveOccupancyPct";
            status                               = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param, &wave_occupancy_index);
            EXPECT_EQ(kGpaStatusOk, status);

            if (status == kGpaStatusOk)
            {
                GpaSpmData spm_data = {};

                constexpr std::array<GpaUInt64, 3> kTimeStampData = {0, 1, 2};
                spm_data.timestamps                               = kTimeStampData.data();
                spm_data.number_of_timestamps                     = static_cast<uint32_t>(kTimeStampData.size());

                // There are 32 SQWGP*_SQ_PERF_SEL_LEVEL_WAVES[0..31] IDs for WaveOccupancyPct on GFX12
                std::array<GpaSpmCounterInfo, 32> spm_counter_info = {};
                for (uint32_t i = 0; i < spm_counter_info.size(); ++i)
                {
                    // We are able to verify the block id, event index, and instance.
                    // So this information needs to be valid.
                    spm_counter_info[i].gpu_block_id       = kGpaHwBlockSqWgp;
                    spm_counter_info[i].event_index        = 7;
                    spm_counter_info[i].gpu_block_instance = i;
                    spm_counter_info[i].data_offset        = i * static_cast<uint32_t>(kTimeStampData.size());
                }
                spm_data.spm_counter_info           = spm_counter_info.data();
                spm_data.number_of_spm_counter_info = static_cast<uint32_t>(spm_counter_info.size());

                constexpr size_t counter_data_size = spm_counter_info.size() * kTimeStampData.size();

                // We are only enabling 1 derived counter to keep it simple.
                const std::array<GpaUInt32, 1> gpa_counter_indices = {wave_occupancy_index};

                std::array<GpaFloat64, kTimeStampData.size()> results = {};

                // The counterlibrary cannot validate this information for the user.
                static_assert(results.size() == kTimeStampData.size());

                // Verify 16bit counter data is collected correctly.
                {
                    std::array<uint16_t, counter_data_size> counter_data = {};
                    for (size_t i = 0; i < counter_data_size; i += 3)
                    {
                        // 100% WaveOccupancyPct for the first timestamp
                        counter_data[i] = 32;
                        // 50% WaveOccupancyPct for the second timestamp
                        counter_data[i + 1] = 16;
                        // 0% WaveOccupancyPct for the third timestamp
                        counter_data[i + 2] = 0;
                    }

                    spm_data.counter_data_16bit               = counter_data.data();
                    spm_data.number_of_counter_data           = static_cast<uint32_t>(counter_data_size);
                    spm_data.number_of_bytes_per_counter_data = sizeof(counter_data[0]);

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusOk, status);

                    // Verify expected results.
                    EXPECT_EQ(results[0], 100.0);
                    EXPECT_EQ(results[1], 50.0);
                    EXPECT_EQ(results[2], 0.0);
                }

                // Verify 32bit counter data is collected correctly.
                {
                    std::array<uint32_t, counter_data_size> counter_data = {};
                    for (size_t i = 0; i < counter_data_size; i += 3)
                    {
                        // 100% WaveOccupancyPct for the first timestamp
                        counter_data[i] = 32;
                        // 50% WaveOccupancyPct for the second timestamp
                        counter_data[i + 1] = 16;
                        // 0% WaveOccupancyPct for the third timestamp
                        counter_data[i + 2] = 0;
                    }
                    spm_data.counter_data_16bit               = reinterpret_cast<const uint16_t*>(counter_data.data());
                    spm_data.number_of_counter_data           = static_cast<uint32_t>(counter_data_size);
                    spm_data.number_of_bytes_per_counter_data = sizeof(counter_data[0]);

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusOk, status);

                    // Verify expected results.
                    EXPECT_EQ(results[0], 100.0);
                    EXPECT_EQ(results[1], 50.0);
                    EXPECT_EQ(results[2], 0.0);
                }
            }
        }

        status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, status);

        UnloadLib(handle);
    }
}

// Get HW counter results from a hardware counter.
TEST(ComputeDerivedSpmCounterResults, HardwareCounter)
{
    LibHandle              handle                     = {};
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    GpaCounterContext      gpa_counter_context        = {};
    if (LoadAndVerifyCounterLib(&handle, &gpa_counter_lib_func_table))
    {
        GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, kDevIdGfx12_0_0, REVISION_ID_ANY, nullptr, 0};
        GpaStatus                     status                        = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(kGpaApiDirectx12,
                                                                                      kGpaSessionSampleTypeStreamingCounter,
                                                                                      counter_context_hardware_info,
                                                                                      kGpaOpenContextEnableHardwareCountersBit,
                                                                                      &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, status);

        if (status == kGpaStatusOk)
        {
            GpaUInt32       index    = {};
            GpaCounterParam param    = {};
            param.is_derived_counter = false;

            param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockSqWgp;
            param.gpa_hw_counter.gpa_hw_block_event_id = 7;
            param.gpa_hw_counter.gpa_hw_block_instance = 0;

            status = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param, &index);
            EXPECT_EQ(kGpaStatusOk, status);

            if (status == kGpaStatusOk)
            {
                GpaSpmData spm_data = {};

                constexpr std::array<GpaUInt64, 3> kTimeStampData = {0, 1, 2};
                spm_data.timestamps                               = kTimeStampData.data();
                spm_data.number_of_timestamps                     = static_cast<uint32_t>(kTimeStampData.size());

                // There are 32 SQWGP*_SQ_PERF_SEL_LEVEL_WAVES[0..31] IDs for WaveOccupancyPct on GFX12
                std::array<GpaSpmCounterInfo, 32> spm_counter_info = {};
                for (uint32_t i = 0; i < spm_counter_info.size(); ++i)
                {
                    // We are able to verify the block id, event index, and instance.
                    // So this information needs to be valid.
                    spm_counter_info[i].gpu_block_id       = kGpaHwBlockSqWgp;
                    spm_counter_info[i].event_index        = 7;
                    spm_counter_info[i].gpu_block_instance = i;
                    spm_counter_info[i].data_offset        = i * static_cast<uint32_t>(kTimeStampData.size());
                }
                spm_data.spm_counter_info           = spm_counter_info.data();
                spm_data.number_of_spm_counter_info = static_cast<uint32_t>(spm_counter_info.size());

                constexpr size_t counter_data_size = spm_counter_info.size() * kTimeStampData.size();

                // We are only enabling 1 HW counter to keep it simple.
                const std::array<GpaUInt32, 1> gpa_counter_indices = {index};

                std::array<GpaFloat64, kTimeStampData.size()> results = {};

                // The counterlibrary cannot validate this information for the user.
                static_assert(results.size() == kTimeStampData.size());

                // Verify 16bit counter data is collected correctly.
                {
                    std::array<uint16_t, counter_data_size> counter_data = {};
                    for (size_t i = 0; i < counter_data_size; i += 3)
                    {
                        // 100% WaveOccupancyPct for the first timestamp
                        counter_data[i] = 32;
                        // 50% WaveOccupancyPct for the second timestamp
                        counter_data[i + 1] = 16;
                        // 0% WaveOccupancyPct for the third timestamp
                        counter_data[i + 2] = 0;
                    }

                    spm_data.counter_data_16bit               = counter_data.data();
                    spm_data.number_of_counter_data           = static_cast<uint32_t>(counter_data_size);
                    spm_data.number_of_bytes_per_counter_data = sizeof(counter_data[0]);

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusOk, status);

                    // Verify expected results.
                    EXPECT_EQ(results[0], 32.0);
                    EXPECT_EQ(results[1], 16.0);
                    EXPECT_EQ(results[2], 0.0);
                }

                // Verify 32bit counter data is collected correctly.
                {
                    std::array<uint32_t, counter_data_size> counter_data = {};
                    for (size_t i = 0; i < counter_data_size; i += 3)
                    {
                        // 100% WaveOccupancyPct for the first timestamp
                        counter_data[i] = 32;
                        // 50% WaveOccupancyPct for the second timestamp
                        counter_data[i + 1] = 16;
                        // 0% WaveOccupancyPct for the third timestamp
                        counter_data[i + 2] = 0;
                    }
                    spm_data.counter_data_16bit               = reinterpret_cast<const uint16_t*>(counter_data.data());
                    spm_data.number_of_counter_data           = static_cast<uint32_t>(counter_data_size);
                    spm_data.number_of_bytes_per_counter_data = sizeof(counter_data[0]);

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusOk, status);

                    // Verify expected results.
                    EXPECT_EQ(results[0], 32.0);
                    EXPECT_EQ(results[1], 16.0);
                    EXPECT_EQ(results[2], 0.0);
                }

                // Verify querying with an invalid offset will fail
                {
                    ++spm_counter_info[0].data_offset;

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(gpa_counter_context, &spm_data, 1, &index, results.data());
                    EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);

                    --spm_counter_info[0].data_offset;
                }

                // Verify querying with an invalid HW counter will fail
                {
                    param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockCpf;
                    param.gpa_hw_counter.gpa_hw_block_event_id = 24;
                    param.gpa_hw_counter.gpa_hw_block_instance = 0;

                    status = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param, &index);
                    EXPECT_EQ(kGpaStatusOk, status);

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(gpa_counter_context, &spm_data, 1, &index, results.data());
                    EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);
                }
            }
        }

        status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, status);

        UnloadLib(handle);
    }
}

// Verify negative counter results are interpreted correctly for Gfx10.
TEST(ComputeDerivedSpmCounterResults, WaveOccupancyPctWorkaroundGfx10)
{
    LibHandle              handle                     = {};
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    GpaCounterContext      gpa_counter_context        = {};
    if (LoadAndVerifyCounterLib(&handle, &gpa_counter_lib_func_table))
    {
        const GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, kDevIdGfx10, REVISION_ID_ANY, nullptr, 0};
        GpaStatus                           status                        = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
            kGpaApiDirectx12, kGpaSessionSampleTypeStreamingCounter, counter_context_hardware_info, kGpaOpenContextDefaultBit, &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, status);

        if (status == kGpaStatusOk)
        {
            GpaUInt32       wave_occupancy_index = {};
            GpaCounterParam param                = {};
            param.is_derived_counter             = true;
            param.derived_counter_name           = "WaveOccupancyPct";
            status                               = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param, &wave_occupancy_index);
            EXPECT_EQ(kGpaStatusOk, status);

            if (status == kGpaStatusOk)
            {
                GpaSpmData spm_data = {};

                constexpr std::array<GpaUInt64, 3> kTimeStampData = {0, 1, 2};
                spm_data.timestamps                               = kTimeStampData.data();
                spm_data.number_of_timestamps                     = static_cast<uint32_t>(kTimeStampData.size());

                // There are 2 SQ*_PERF_SEL_LEVEL_WAVES[0..1] IDs for WaveOccupancyPct on GFX10
                std::array<GpaSpmCounterInfo, 2> spm_counter_info = {};
                for (uint32_t i = 0; i < spm_counter_info.size(); ++i)
                {
                    // We are able to verify the block id, event index, and instance.
                    // So this information needs to be valid.
                    spm_counter_info[i].gpu_block_id       = kGpaHwBlockSq;
                    spm_counter_info[i].event_index        = 7;
                    spm_counter_info[i].gpu_block_instance = i;
                    spm_counter_info[i].data_offset        = i * static_cast<uint32_t>(kTimeStampData.size());
                }
                spm_data.spm_counter_info           = spm_counter_info.data();
                spm_data.number_of_spm_counter_info = static_cast<uint32_t>(spm_counter_info.size());

                constexpr size_t counter_data_size = spm_counter_info.size() * kTimeStampData.size();

                // We are only enabling 1 derived counter to keep it simple.
                const std::array<GpaUInt32, 1> gpa_counter_indices = {wave_occupancy_index};

                std::array<GpaFloat64, kTimeStampData.size()> results = {};

                // The counterlibrary cannot validate this information for the user.
                static_assert(results.size() == kTimeStampData.size());

                // Verify negative 16bit counter data is collected correctly.
                {
                    std::array<int16_t, counter_data_size> counter_data = {};
                    for (size_t i = 0; i < counter_data_size; i += 3)
                    {
                        // 100% WaveOccupancyPct for the first timestamp
                        counter_data[i] = 800;
                        // 50% WaveOccupancyPct for the second timestamp
                        counter_data[i + 1] = -400;
                        // 0% WaveOccupancyPct for the third timestamp
                        counter_data[i + 2] = 0;
                    }

                    spm_data.counter_data_16bit               = reinterpret_cast<const uint16_t*>(counter_data.data());
                    spm_data.number_of_counter_data           = static_cast<uint32_t>(counter_data_size);
                    spm_data.number_of_bytes_per_counter_data = sizeof(counter_data[0]);

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusOk, status);

                    // Verify expected results.
                    EXPECT_EQ(results[0], 100.0);
                    EXPECT_EQ(results[1], 50.0);
                    EXPECT_EQ(results[2], 0.0);
                }

                // Verify invalid negative 16bit counter data is collected correctly.
                {
                    std::array<int16_t, counter_data_size> counter_data = {};
                    for (size_t i = 0; i < counter_data_size; i += 3)
                    {
                        counter_data[i]     = -1;
                        counter_data[i + 1] = -1;
                        counter_data[i + 2] = -1;
                    }

                    spm_data.counter_data_16bit               = reinterpret_cast<const uint16_t*>(counter_data.data());
                    spm_data.number_of_counter_data           = static_cast<uint32_t>(counter_data_size);
                    spm_data.number_of_bytes_per_counter_data = sizeof(counter_data[0]);

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusOk, status);

                    // Verify expected results.
                    EXPECT_EQ(results[0], 0.0);
                    EXPECT_EQ(results[1], 0.0);
                    EXPECT_EQ(results[2], 0.0);
                }

                // Verify negative 32bit counter data is collected correctly.
                {
                    std::array<int32_t, counter_data_size> counter_data = {};
                    for (size_t i = 0; i < counter_data_size; i += 3)
                    {
                        // 100% WaveOccupancyPct for the first timestamp
                        counter_data[i] = 800;
                        // 50% WaveOccupancyPct for the second timestamp
                        counter_data[i + 1] = -400;
                        // 0% WaveOccupancyPct for the third timestamp
                        counter_data[i + 2] = 0;
                    }

                    spm_data.counter_data_16bit               = reinterpret_cast<const uint16_t*>(counter_data.data());
                    spm_data.number_of_counter_data           = static_cast<uint32_t>(counter_data_size);
                    spm_data.number_of_bytes_per_counter_data = sizeof(counter_data[0]);

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusOk, status);

                    // Verify expected results.
                    EXPECT_EQ(results[0], 100.0);
                    EXPECT_EQ(results[1], 50.0);
                    EXPECT_EQ(results[2], 0.0);
                }

                // Verify invalid negative 32bit counter data is collected correctly.
                {
                    std::array<int32_t, counter_data_size> counter_data = {};
                    for (size_t i = 0; i < counter_data_size; i += 3)
                    {
                        counter_data[i]     = -1;
                        counter_data[i + 1] = -1;
                        counter_data[i + 2] = -1;
                    }

                    spm_data.counter_data_16bit               = reinterpret_cast<const uint16_t*>(counter_data.data());
                    spm_data.number_of_counter_data           = static_cast<uint32_t>(counter_data_size);
                    spm_data.number_of_bytes_per_counter_data = sizeof(counter_data[0]);

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusOk, status);

                    // Verify expected results.
                    EXPECT_EQ(results[0], 0.0);
                    EXPECT_EQ(results[1], 0.0);
                    EXPECT_EQ(results[2], 0.0);
                }
            }
        }

        status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, status);

        UnloadLib(handle);
    }
}

// Verify negative counter results are interpreted correctly for Gfx10.3
TEST(ComputeDerivedSpmCounterResults, WaveOccupancyPctWorkaroundGfx103)
{
    LibHandle              handle                     = {};
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    GpaCounterContext      gpa_counter_context        = {};
    if (LoadAndVerifyCounterLib(&handle, &gpa_counter_lib_func_table))
    {
        const GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, kDevIdGfx10_3, REVISION_ID_ANY, nullptr, 0};
        GpaStatus                           status                        = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
            kGpaApiDirectx12, kGpaSessionSampleTypeStreamingCounter, counter_context_hardware_info, kGpaOpenContextDefaultBit, &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, status);

        if (status == kGpaStatusOk)
        {
            GpaUInt32       wave_occupancy_index = {};
            GpaCounterParam param                = {};
            param.is_derived_counter             = true;
            param.derived_counter_name           = "WaveOccupancyPct";
            status                               = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param, &wave_occupancy_index);
            EXPECT_EQ(kGpaStatusOk, status);

            if (status == kGpaStatusOk)
            {
                GpaSpmData spm_data = {};

                constexpr std::array<GpaUInt64, 3> kTimeStampData = {0, 1, 2};
                spm_data.timestamps                               = kTimeStampData.data();
                spm_data.number_of_timestamps                     = static_cast<uint32_t>(kTimeStampData.size());

                // There are 4 SQ*_PERF_SEL_LEVEL_WAVES[0..1] IDs for WaveOccupancyPct on GFX10.3
                std::array<GpaSpmCounterInfo, 4> spm_counter_info = {};
                for (uint32_t i = 0; i < spm_counter_info.size(); ++i)
                {
                    // We are able to verify the block id, event index, and instance.
                    // So this information needs to be valid.
                    spm_counter_info[i].gpu_block_id       = kGpaHwBlockSq;
                    spm_counter_info[i].event_index        = 7;
                    spm_counter_info[i].gpu_block_instance = i;
                    spm_counter_info[i].data_offset        = i * static_cast<uint32_t>(kTimeStampData.size());
                }
                spm_data.spm_counter_info           = spm_counter_info.data();
                spm_data.number_of_spm_counter_info = static_cast<uint32_t>(spm_counter_info.size());

                constexpr size_t counter_data_size = spm_counter_info.size() * kTimeStampData.size();

                // We are only enabling 1 derived counter to keep it simple.
                const std::array<GpaUInt32, 1> gpa_counter_indices = {wave_occupancy_index};

                std::array<GpaFloat64, kTimeStampData.size()> results = {};

                // The counterlibrary cannot validate this information for the user.
                static_assert(results.size() == kTimeStampData.size());

                // Verify negative 16bit counter data is collected correctly.
                {
                    std::array<int16_t, counter_data_size> counter_data = {};
                    for (size_t i = 0; i < counter_data_size; i += 3)
                    {
                        // 100% WaveOccupancyPct for the first timestamp
                        counter_data[i] = 640;
                        // 50% WaveOccupancyPct for the second timestamp
                        counter_data[i + 1] = -320;
                        // 0% WaveOccupancyPct for the third timestamp
                        counter_data[i + 2] = 0;
                    }

                    spm_data.counter_data_16bit               = reinterpret_cast<const uint16_t*>(counter_data.data());
                    spm_data.number_of_counter_data           = static_cast<uint32_t>(counter_data_size);
                    spm_data.number_of_bytes_per_counter_data = sizeof(counter_data[0]);

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusOk, status);

                    // Verify expected results.
                    EXPECT_EQ(results[0], 100.0);
                    EXPECT_EQ(results[1], 50.0);
                    EXPECT_EQ(results[2], 0.0);
                }

                // Verify invalid negative 16bit counter data is collected correctly.
                {
                    std::array<int16_t, counter_data_size> counter_data = {};
                    for (size_t i = 0; i < counter_data_size; i += 3)
                    {
                        counter_data[i]     = -1;
                        counter_data[i + 1] = -1;
                        counter_data[i + 2] = -1;
                    }

                    spm_data.counter_data_16bit               = reinterpret_cast<const uint16_t*>(counter_data.data());
                    spm_data.number_of_counter_data           = static_cast<uint32_t>(counter_data_size);
                    spm_data.number_of_bytes_per_counter_data = sizeof(counter_data[0]);

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusOk, status);

                    // Verify expected results.
                    EXPECT_EQ(results[0], 0.0);
                    EXPECT_EQ(results[1], 0.0);
                    EXPECT_EQ(results[2], 0.0);
                }

                // Verify negative 32bit counter data is collected correctly.
                {
                    std::array<int32_t, counter_data_size> counter_data = {};
                    for (size_t i = 0; i < counter_data_size; i += 3)
                    {
                        // 100% WaveOccupancyPct for the first timestamp
                        counter_data[i] = 640;
                        // 50% WaveOccupancyPct for the second timestamp
                        counter_data[i + 1] = -320;
                        // 0% WaveOccupancyPct for the third timestamp
                        counter_data[i + 2] = 0;
                    }

                    spm_data.counter_data_16bit               = reinterpret_cast<const uint16_t*>(counter_data.data());
                    spm_data.number_of_counter_data           = static_cast<uint32_t>(counter_data_size);
                    spm_data.number_of_bytes_per_counter_data = sizeof(counter_data[0]);

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusOk, status);

                    // Verify expected results.
                    EXPECT_EQ(results[0], 100.0);
                    EXPECT_EQ(results[1], 50.0);
                    EXPECT_EQ(results[2], 0.0);
                }

                // Verify invalid negative 32bit counter data is collected correctly.
                {
                    std::array<int32_t, counter_data_size> counter_data = {};
                    for (size_t i = 0; i < counter_data_size; i += 3)
                    {
                        counter_data[i]     = -1;
                        counter_data[i + 1] = -1;
                        counter_data[i + 2] = -1;
                    }

                    spm_data.counter_data_16bit               = reinterpret_cast<const uint16_t*>(counter_data.data());
                    spm_data.number_of_counter_data           = static_cast<uint32_t>(counter_data_size);
                    spm_data.number_of_bytes_per_counter_data = sizeof(counter_data[0]);

                    status = gpa_counter_lib_func_table.GpaCounterlibComputeDerivedSpmCounterResults(
                        gpa_counter_context, &spm_data, gpa_counter_indices.size(), gpa_counter_indices.data(), results.data());
                    EXPECT_EQ(kGpaStatusOk, status);

                    // Verify expected results.
                    EXPECT_EQ(results[0], 0.0);
                    EXPECT_EQ(results[1], 0.0);
                    EXPECT_EQ(results[2], 0.0);
                }
            }
        }

        status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, status);

        UnloadLib(handle);
    }
}

TEST(GpaCounterLibGetSupportedSampleTypes, Directx12)
{
    VerifySupportedSampleTypes(kGpaApiDirectx12);
}

// DirectX12 is the only API that supports SPM and SQTT.
// Test to ensure this is working properly.
TEST(GpaCounterLibGetSupportedSampleTypes, SpmSqtt)
{
    constexpr GpaApiType   api                        = kGpaApiDirectx12;
    LibHandle              handle                     = {};
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    if (LoadAndVerifyCounterLib(&handle, &gpa_counter_lib_func_table))
    {
        GpaStatus                  status                = kGpaStatusOk;
        GpaSupportedSampleTypeInfo info                  = {};
        info.revision_id                                 = REVISION_ID_ANY;
        info.vendor_id                                   = kAmdVendorId;
        info.driver_info.driver_type                     = kIgnoreDriver;
        GpaContextSampleTypeFlags supported_sample_types = {};

        // Devices that support all counter types.
        for (const GpaUInt32 device_id : {kDevIdGfx10, kDevIdGfx11, kDevIdGfx11_5_0, kDevIdGfx11_5_3, kDevIdGfx12_0_0, kDevIdGfx12_0_1})
        {
            info.device_id = device_id;

            constexpr GpaContextSampleTypeFlags flags =
                kGpaContextSampleTypeDiscreteCounter | kGpaContextSampleTypeStreamingCounter | kGpaContextSampleTypeSqtt;

            status = gpa_counter_lib_func_table.GpaCounterLibGetSupportedSampleTypes(api, &info, &supported_sample_types);
            EXPECT_EQ(kGpaStatusOk, status);
            EXPECT_EQ(supported_sample_types, flags) << device_id;
        }

        // Devices that support discrete + sqtt.
        for (const GpaUInt32 device_id : {kDevIdGfx10_3_4, kDevIdGfx10_3_1, kDevIdGfx11_0_3H, kDevIdGfx11_0_3H2, kDevIdGfx10_3_3, kDevIdGfx10_3_5})
        {
            info.device_id = device_id;

            constexpr GpaContextSampleTypeFlags flags = kGpaContextSampleTypeDiscreteCounter | kGpaContextSampleTypeSqtt;

            status = gpa_counter_lib_func_table.GpaCounterLibGetSupportedSampleTypes(api, &info, &supported_sample_types);
            EXPECT_EQ(kGpaStatusOk, status);
            EXPECT_EQ(supported_sample_types, flags) << device_id;
        }

        // Devices that only support discrete.
        for (const GpaUInt32 device_id : {kDevIdGfx11_0_3, kDevIdGfx11_0_3B})
        {
            info.device_id = device_id;

            constexpr GpaContextSampleTypeFlags flags = kGpaContextSampleTypeDiscreteCounter;

            status = gpa_counter_lib_func_table.GpaCounterLibGetSupportedSampleTypes(api, &info, &supported_sample_types);
            EXPECT_EQ(kGpaStatusOk, status);
            EXPECT_EQ(supported_sample_types, flags) << device_id;
        }

        // Verify driver version checking for Phoenix.
        for (const GpaUInt32 device_id : {kDevIdGfx11_0_3, kDevIdGfx11_0_3B})
        {
            info.device_id               = device_id;
            info.driver_info.driver_type = kAmdProprietaryDriver;
            info.driver_info.major       = 22;

            status = gpa_counter_lib_func_table.GpaCounterLibGetSupportedSampleTypes(api, &info, &supported_sample_types);
            EXPECT_EQ(kGpaStatusErrorHardwareNotSupported, status);

            // Until 22.40 Pheonix wasn't supported at all.
            EXPECT_EQ(supported_sample_types, 0) << device_id;

            // Reset for next test
            info.driver_info.driver_type = kIgnoreDriver;
            info.driver_info.major       = 0;
        }

        // Verify driver version checking for gfx11.
        for (const GpaUInt32 device_id : {kDevIdGfx11, kDevIdGfx11_5_0})
        {
            info.device_id               = device_id;
            info.driver_info.driver_type = kAmdProprietaryDriver;
            info.driver_info.major       = 23;

            // Until 23.10 gfx11 didn't support SPM
            constexpr GpaContextSampleTypeFlags flags = kGpaContextSampleTypeDiscreteCounter | kGpaContextSampleTypeSqtt;

            status = gpa_counter_lib_func_table.GpaCounterLibGetSupportedSampleTypes(api, &info, &supported_sample_types);
            EXPECT_EQ(kGpaStatusOk, status);

            EXPECT_EQ(supported_sample_types, flags) << device_id;

            // Reset for next test
            info.driver_info.driver_type = kIgnoreDriver;
            info.driver_info.major       = 0;
        }

        // Verify environment variables are working.
        {
            BOOL ret = SetEnvironmentVariableW(L"AMD_GPA_ENABLE_SPM", L"1");
            EXPECT_GT(ret, 0);
            ret = SetEnvironmentVariableW(L"AMD_GPA_ENABLE_SQTT", L"1");
            EXPECT_GT(ret, 0);

            // All supported device ids should now support all sample types.
            for (const GpaUInt32 device_id : kSupportedDeviceIds)
            {
                info.device_id = device_id;

                constexpr GpaContextSampleTypeFlags flags =
                    kGpaContextSampleTypeDiscreteCounter | kGpaContextSampleTypeStreamingCounter | kGpaContextSampleTypeSqtt;

                status = gpa_counter_lib_func_table.GpaCounterLibGetSupportedSampleTypes(api, &info, &supported_sample_types);
                EXPECT_EQ(kGpaStatusOk, status);
                EXPECT_EQ(supported_sample_types, flags) << device_id;
            }

            ret = SetEnvironmentVariableW(L"AMD_GPA_ENABLE_SPM", L"0");
            EXPECT_GT(ret, 0);
            ret = SetEnvironmentVariableW(L"AMD_GPA_ENABLE_SQTT", L"0");
            EXPECT_GT(ret, 0);

            // Verify setting to 0 will disable the environment variables as well.
            {
                info.device_id = kDevIdGfx10_3_4;

                constexpr GpaContextSampleTypeFlags flags = kGpaContextSampleTypeDiscreteCounter | kGpaContextSampleTypeSqtt;

                status = gpa_counter_lib_func_table.GpaCounterLibGetSupportedSampleTypes(api, &info, &supported_sample_types);
                EXPECT_EQ(kGpaStatusOk, status);
                EXPECT_EQ(supported_sample_types, flags) << kDevIdGfx10_3_4;
            }
        }

        UnloadLib(handle);
    }
}

// Verify minimum driver version
TEST(GpaCounterLibGetSupportedSampleTypes, MinimumDriverVersion)
{
    constexpr GpaApiType   api                        = kGpaApiDirectx12;
    LibHandle              handle                     = {};
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    if (LoadAndVerifyCounterLib(&handle, &gpa_counter_lib_func_table))
    {
        GpaStatus                  status = kGpaStatusOk;
        GpaSupportedSampleTypeInfo info   = {};
        info.revision_id                  = REVISION_ID_ANY;
        info.vendor_id                    = kAmdVendorId;

        info.driver_info.driver_type = kAmdProprietaryDriver;
        info.driver_info.major       = 19;
        info.driver_info.minor       = 20;

        GpaContextSampleTypeFlags supported_sample_types = {};

        // All supported devices should FAIL because the minimum driver version is invalid.
        for (const GpaUInt32 device_id : kSupportedDeviceIds)
        {
            info.device_id = device_id;

            status = gpa_counter_lib_func_table.GpaCounterLibGetSupportedSampleTypes(api, &info, &supported_sample_types);

            EXPECT_EQ(kGpaStatusErrorHardwareNotSupported, status);
            EXPECT_EQ(supported_sample_types, 0);
        }

        UnloadLib(handle);
    }
}
