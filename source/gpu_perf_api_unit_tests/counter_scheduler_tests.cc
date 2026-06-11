//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Unit tests for Counter Scheduler.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "gpu_perf_api_counter_generator/gpa_split_counters_interfaces.h"

#ifdef _WIN32
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx11_gfx10.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx11_gfx11.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx12_gfx10.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx12_gfx11.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx12_gfx115.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_dx12_gfx12.h"

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx11_gfx11.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_dx12_gfx11.h"
#endif

#ifdef GL
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_oglp_gfx11.h"
#endif

#ifdef VK
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_vk_gfx11.h"
#endif

#include "gpu_perf_api_unit_tests/counter_generator_tests.h"

#ifdef GL
TEST(CounterDllTests, OpenGlCounterScheduling)
{
    auto constexpr kCounters = std::to_array<uint32_t>({
        DISCRETE_GPUTIME_PUBLIC_OGLP_GFX11,
        DISCRETE_GPUBUSY_PUBLIC_OGLP_GFX11,
        DISCRETE_TESSELLATORBUSY_PUBLIC_OGLP_GFX11,
    });
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiOpengl, kDevIdGfx11, kCounters), 2);
}
#endif

#ifdef VK
TEST(CounterDllTests, VulkanCounterScheduling)
{
    auto constexpr kCounters = std::to_array<uint32_t>({
        DISCRETE_GPUTIME_PUBLIC_VK_GFX11,
        DISCRETE_GPUBUSY_PUBLIC_VK_GFX11,
        DISCRETE_TESSELLATORBUSY_PUBLIC_VK_GFX11,
    });
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiVulkan, kDevIdGfx11, kCounters), 2);
}
#endif

#ifdef _WIN32

TEST(CounterDllTests, Dx12GetPassCountNullPointerValidation)
{
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    auto                   lib_guard                  = LoadAndVerifyCounterLib(&gpa_counter_lib_func_table);

    if (!lib_guard)
    {
        return;
    }

    GpaCounterContextHardwareInfo counter_context_hardware_info = {device_info::kAmdVendorId, kDevIdGfx12_0_1, device_info::kRevisionIdAny, nullptr, 0};
    GpaCounterContext             gpa_counter_context           = nullptr;
    GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
        kGpaApiDirectx12, kGpaSessionSampleTypeDiscreteCounter, counter_context_hardware_info, kGpaOpenContextDefaultBit, &gpa_counter_context);
    EXPECT_EQ(kGpaStatusOk, gpa_status);

    std::vector<GpaUInt32> counter_list = {0};

    // Null pass count output pointer.
    gpa_status =
        gpa_counter_lib_func_table.GpaCounterLibGetPassCount(gpa_counter_context, counter_list.data(), static_cast<GpaUInt32>(counter_list.size()), nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, gpa_status);

    // Null counter indices pointer with non-zero count.
    GpaUInt32 req_pass = 0u;
    gpa_status         = gpa_counter_lib_func_table.GpaCounterLibGetPassCount(gpa_counter_context, nullptr, 1, &req_pass);
    EXPECT_EQ(kGpaStatusErrorNullPointer, gpa_status);

    // Null context.
    gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetPassCount(nullptr, counter_list.data(), static_cast<GpaUInt32>(counter_list.size()), &req_pass);
    EXPECT_EQ(kGpaStatusErrorNullPointer, gpa_status);

    gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
}

TEST(CounterDllTests, Dx12GetPassCountZeroCounters)
{
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    auto                   lib_guard                  = LoadAndVerifyCounterLib(&gpa_counter_lib_func_table);

    if (!lib_guard)
    {
        return;
    }

    GpaCounterContextHardwareInfo counter_context_hardware_info = {device_info::kAmdVendorId, kDevIdGfx12_0_1, device_info::kRevisionIdAny, nullptr, 0};
    GpaCounterContext             gpa_counter_context           = nullptr;
    GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
        kGpaApiDirectx12, kGpaSessionSampleTypeDiscreteCounter, counter_context_hardware_info, kGpaOpenContextDefaultBit, &gpa_counter_context);
    EXPECT_EQ(kGpaStatusOk, gpa_status);

    // Zero counter count should be an error.
    GpaUInt32                req_pass     = 0u;
    std::array<GpaUInt32, 2> counter_list = {};
    gpa_status                            = gpa_counter_lib_func_table.GpaCounterLibGetPassCount(gpa_counter_context, counter_list.data(), 0, &req_pass);
    EXPECT_EQ(kGpaStatusErrorInvalidParameter, gpa_status);

    gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
}

TEST(CounterDllTests, Dx12GetPassCountInvalidCounterIndex)
{
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    auto                   lib_guard                  = LoadAndVerifyCounterLib(&gpa_counter_lib_func_table);

    if (!lib_guard)
    {
        return;
    }

    GpaCounterContextHardwareInfo counter_context_hardware_info = {device_info::kAmdVendorId, kDevIdGfx12_0_1, device_info::kRevisionIdAny, nullptr, 0};
    GpaCounterContext             gpa_counter_context           = nullptr;
    GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
        kGpaApiDirectx12, kGpaSessionSampleTypeDiscreteCounter, counter_context_hardware_info, kGpaOpenContextDefaultBit, &gpa_counter_context);
    EXPECT_EQ(kGpaStatusOk, gpa_status);

    // Get total counter count so we can use an out-of-range index.
    GpaUInt32 counter_count = 0;
    gpa_status              = gpa_counter_lib_func_table.GpaCounterLibGetNumCounters(gpa_counter_context, &counter_count);
    EXPECT_EQ(kGpaStatusOk, gpa_status);
    EXPECT_GT(counter_count, 0u);

    // Use an index that is out of range.
    GpaUInt32              req_pass     = 0u;
    std::vector<GpaUInt32> counter_list = {counter_count + 100};
    gpa_status =
        gpa_counter_lib_func_table.GpaCounterLibGetPassCount(gpa_counter_context, counter_list.data(), static_cast<GpaUInt32>(counter_list.size()), &req_pass);
    EXPECT_NE(kGpaStatusOk, gpa_status);

    gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
}

TEST(CounterDllTests, Dx12SingleCounterRequiresOnePass)
{
    // Any single derived counter should require at least 1 pass (and most simple ones exactly 1).
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    auto                   lib_guard                  = LoadAndVerifyCounterLib(&gpa_counter_lib_func_table);

    if (!lib_guard)
    {
        return;
    }

    GpaCounterContextHardwareInfo counter_context_hardware_info = {device_info::kAmdVendorId, kDevIdGfx12_0_1, device_info::kRevisionIdAny, nullptr, 0};
    GpaCounterContext             gpa_counter_context           = nullptr;
    GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
        kGpaApiDirectx12, kGpaSessionSampleTypeDiscreteCounter, counter_context_hardware_info, kGpaOpenContextDefaultBit, &gpa_counter_context);
    EXPECT_EQ(kGpaStatusOk, gpa_status);

    GpaUInt32 counter_count = 0;
    gpa_status              = gpa_counter_lib_func_table.GpaCounterLibGetNumCounters(gpa_counter_context, &counter_count);
    EXPECT_EQ(kGpaStatusOk, gpa_status);

    // Test each counter individually to confirm it can be scheduled.
    for (GpaUInt32 i = 0; i < counter_count; ++i)
    {
        GpaUInt32 req_pass = 0u;
        gpa_status         = gpa_counter_lib_func_table.GpaCounterLibGetPassCount(gpa_counter_context, &i, 1, &req_pass);
        EXPECT_EQ(kGpaStatusOk, gpa_status) << "Failed to get pass count for counter index " << i;
        EXPECT_GE(req_pass, 1u) << "Counter index " << i << " requires 0 passes, which is unexpected.";
    }

    gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
}

TEST(CounterDllTests, Dx12GpuTimeAloneRequiresOnePass)
{
    // GPUTime by itself should always be 1 pass.
    auto constexpr kCounters = std::to_array<uint32_t>({DISCRETE_GPUTIME_PUBLIC_DX12_GFX12});
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCounters), 1u);
}

TEST(CounterDllTests, Dx12GpuTimeWithOtherCountersRequiresExtraPass)
{
    // GPUTime must be in its own pass, so adding it to any other counter should add at least 1 more pass.
    auto constexpr kCountersNoGpuTime   = std::to_array<uint32_t>({DISCRETE_CSBUSY_PUBLIC_DX12_GFX12});
    auto constexpr kCountersWithGpuTime = std::to_array<uint32_t>({DISCRETE_GPUTIME_PUBLIC_DX12_GFX12, DISCRETE_CSBUSY_PUBLIC_DX12_GFX12});

    const uint32_t passes_without_gpu_time = GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCountersNoGpuTime);
    const uint32_t passes_with_gpu_time    = GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCountersWithGpuTime);

    EXPECT_GT(passes_with_gpu_time, passes_without_gpu_time);
}

TEST(CounterDllTests, Dx12StreamingSingleCounterOnePass)
{
    // A single streaming counter should always fit in 1 pass.
    auto constexpr kCounters = std::to_array<uint32_t>({STREAMING_CSBUSY_PUBLIC_DX12_GFX12});
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeStreamingCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCounters), 1u);
}

TEST(CounterDllTests, Dx12StreamingGpuBusyOnePass)
{
    auto constexpr kCounters = std::to_array<uint32_t>({STREAMING_GPUBUSY_PUBLIC_DX12_GFX12});
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeStreamingCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCounters), 1u);
}

TEST(CounterDllTests, Dx12StreamingAllBusyCountersMinimalPasses)
{
    // PIX commonly enables multiple "Busy" counters together via streaming.
    // These should all be schedulable efficiently.
    auto constexpr kCounters = std::to_array<uint32_t>({
        STREAMING_GPUBUSY_PUBLIC_DX12_GFX12,
        STREAMING_CSBUSY_PUBLIC_DX12_GFX12,
        STREAMING_PSBUSY_PUBLIC_DX12_GFX12,
        STREAMING_VSGSBUSY_PUBLIC_DX12_GFX12,
    });

    const uint32_t pass_count = GetPassCount<kGpaSessionSampleTypeStreamingCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCounters);
    // Streaming counters of the same type should ideally fit in very few passes.
    // The exact number depends on SQ isolation rules, but it should be small.
    EXPECT_LE(pass_count, 4u);
}

TEST(CounterDllTests, Dx12StreamingOccupancyCounters)
{
    // Occupancy and wave-related counters used by PIX.
    auto constexpr kCounters = std::to_array<uint32_t>({
        STREAMING_WAVEOCCUPANCYPCT_PUBLIC_DX12_GFX12,
        STREAMING_GPUBUSY_PUBLIC_DX12_GFX12,
    });

    const uint32_t pass_count = GetPassCount<kGpaSessionSampleTypeStreamingCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCounters);
    EXPECT_GE(pass_count, 1u);
    EXPECT_LE(pass_count, 2u);
}

TEST(CounterDllTests, Dx12StreamingRayTracingCounters)
{
    // Ray tracing counters that PIX uses on GFX12.
    auto constexpr kCounters = std::to_array<uint32_t>({
        STREAMING_RAYTRITESTS_PUBLIC_DX12_GFX12,
        STREAMING_RAYBOXTESTS_PUBLIC_DX12_GFX12,
        STREAMING_RAYTESTSPERWAVE_PUBLIC_DX12_GFX12,
    });

    const uint32_t pass_count = GetPassCount<kGpaSessionSampleTypeStreamingCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCounters);
    EXPECT_EQ(pass_count, 1u);
}

TEST(CounterDllTests, Dx12StreamingShaderLimitationCounters)
{
    // Test all shader limitation counters that PIX uses, grouped by shader stage.
    // CS limitation counters.
    auto constexpr kCsLimitCounters = std::to_array<uint32_t>({
        STREAMING_CSLIMITEDBYLDS_PUBLIC_DX12_GFX12,
        STREAMING_CSLIMITEDBYVGPR_PUBLIC_DX12_GFX12,
        STREAMING_CSLIMITEDBYSCRATCH_PUBLIC_DX12_GFX12,
        STREAMING_CSLIMITEDBYBARRIERS_PUBLIC_DX12_GFX12,
        STREAMING_CSLIMITEDBYTHREADGROUPLIMIT_PUBLIC_DX12_GFX12,
    });
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeStreamingCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCsLimitCounters), 1u);

    // PS limitation counters.
    auto constexpr kPsLimitCounters = std::to_array<uint32_t>({
        STREAMING_PSLIMITEDBYLDS_PUBLIC_DX12_GFX12,
        STREAMING_PSLIMITEDBYVGPR_PUBLIC_DX12_GFX12,
        STREAMING_PSLIMITEDBYSCRATCH_PUBLIC_DX12_GFX12,
    });
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeStreamingCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kPsLimitCounters), 1u);

    // GS limitation counters.
    auto constexpr kGsLimitCounters = std::to_array<uint32_t>({
        STREAMING_GSLIMITEDBYVGPR_PUBLIC_DX12_GFX12,
        STREAMING_GSLIMITEDBYLDS_PUBLIC_DX12_GFX12,
        STREAMING_GSLIMITEDBYSCRATCH_PUBLIC_DX12_GFX12,
    });
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeStreamingCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kGsLimitCounters), 1u);

    // HS limitation counters.
    auto constexpr kHsLimitCounters = std::to_array<uint32_t>({
        STREAMING_HSLIMITEDBYVGPR_PUBLIC_DX12_GFX12,
        STREAMING_HSLIMITEDBYLDS_PUBLIC_DX12_GFX12,
        STREAMING_HSLIMITEDBYSCRATCH_PUBLIC_DX12_GFX12,
        STREAMING_HSLIMITEDBYBARRIERS_PUBLIC_DX12_GFX12,
    });
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeStreamingCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kHsLimitCounters), 1u);
}

TEST(CounterDllTests, Dx12StreamingCounterOrderIndependence)
{
    // The pass count should be the same regardless of the order counters are enabled.
    // This is important for PIX since the order of counter selection is user-driven.
    auto constexpr kCountersOrderA = std::to_array<uint32_t>({
        STREAMING_CSBUSY_PUBLIC_DX12_GFX12,
        STREAMING_PSBUSY_PUBLIC_DX12_GFX12,
        STREAMING_VSGSBUSY_PUBLIC_DX12_GFX12,
    });

    auto constexpr kCountersOrderB = std::to_array<uint32_t>({
        STREAMING_VSGSBUSY_PUBLIC_DX12_GFX12,
        STREAMING_CSBUSY_PUBLIC_DX12_GFX12,
        STREAMING_PSBUSY_PUBLIC_DX12_GFX12,
    });

    auto constexpr kCountersOrderC = std::to_array<uint32_t>({
        STREAMING_PSBUSY_PUBLIC_DX12_GFX12,
        STREAMING_VSGSBUSY_PUBLIC_DX12_GFX12,
        STREAMING_CSBUSY_PUBLIC_DX12_GFX12,
    });

    const uint32_t passes_a = GetPassCount<kGpaSessionSampleTypeStreamingCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCountersOrderA);
    const uint32_t passes_b = GetPassCount<kGpaSessionSampleTypeStreamingCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCountersOrderB);
    const uint32_t passes_c = GetPassCount<kGpaSessionSampleTypeStreamingCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCountersOrderC);

    EXPECT_EQ(passes_a, passes_b);
    EXPECT_EQ(passes_b, passes_c);
}

TEST(CounterDllTests, Dx12DiscreteCounterOrderIndependence)
{
    // Same test for discrete counters.
    auto constexpr kCountersOrderA = std::to_array<uint32_t>({
        DISCRETE_CSBUSY_PUBLIC_DX12_GFX12,
        DISCRETE_PSBUSY_PUBLIC_DX12_GFX12,
        DISCRETE_VSGSBUSY_PUBLIC_DX12_GFX12,
    });

    auto constexpr kCountersOrderB = std::to_array<uint32_t>({
        DISCRETE_VSGSBUSY_PUBLIC_DX12_GFX12,
        DISCRETE_CSBUSY_PUBLIC_DX12_GFX12,
        DISCRETE_PSBUSY_PUBLIC_DX12_GFX12,
    });

    auto constexpr kCountersOrderC = std::to_array<uint32_t>({
        DISCRETE_PSBUSY_PUBLIC_DX12_GFX12,
        DISCRETE_VSGSBUSY_PUBLIC_DX12_GFX12,
        DISCRETE_CSBUSY_PUBLIC_DX12_GFX12,
    });

    const uint32_t passes_a = GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCountersOrderA);
    const uint32_t passes_b = GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCountersOrderB);
    const uint32_t passes_c = GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCountersOrderC);

    EXPECT_EQ(passes_a, passes_b);
    EXPECT_EQ(passes_b, passes_c);
}

TEST(CounterDllTests, Dx12GetCountersByPassNullPointerValidation)
{
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    auto                   lib_guard                  = LoadAndVerifyCounterLib(&gpa_counter_lib_func_table);

    if (!lib_guard)
    {
        return;
    }

    GpaCounterContextHardwareInfo counter_context_hardware_info = {device_info::kAmdVendorId, kDevIdGfx12_0_1, device_info::kRevisionIdAny, nullptr, 0};
    GpaCounterContext             gpa_counter_context           = nullptr;
    GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
        kGpaApiDirectx12, kGpaSessionSampleTypeDiscreteCounter, counter_context_hardware_info, kGpaOpenContextDefaultBit, &gpa_counter_context);
    EXPECT_EQ(kGpaStatusOk, gpa_status);

    std::vector<GpaUInt32> counter_list = {DISCRETE_CSBUSY_PUBLIC_DX12_GFX12};

    // Null pass_count pointer.
    gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetCountersByPass(
        gpa_counter_context, static_cast<GpaUInt32>(counter_list.size()), counter_list.data(), nullptr, nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, gpa_status);

    // Null counter_indices pointer with non-zero count.
    GpaUInt32 pass_count = 0;
    gpa_status           = gpa_counter_lib_func_table.GpaCounterLibGetCountersByPass(gpa_counter_context, 1, nullptr, &pass_count, nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, gpa_status);

    // Null context.
    gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetCountersByPass(
        nullptr, static_cast<GpaUInt32>(counter_list.size()), counter_list.data(), &pass_count, nullptr, nullptr);
    EXPECT_EQ(kGpaStatusErrorNullPointer, gpa_status);

    gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
}

TEST(CounterDllTests, Dx12StreamingVsDiscretePassCountComparison)
{
    // Streaming counters should generally require fewer (or equal) passes than discrete counters
    // for the same set of derived counters since streaming has no max-counters-per-pass limit.
    auto constexpr kDiscreteCounters = std::to_array<uint32_t>({
        DISCRETE_CSBUSY_PUBLIC_DX12_GFX12,
        DISCRETE_PSBUSY_PUBLIC_DX12_GFX12,
        DISCRETE_VSGSBUSY_PUBLIC_DX12_GFX12,
    });

    auto constexpr kStreamingCounters = std::to_array<uint32_t>({
        STREAMING_CSBUSY_PUBLIC_DX12_GFX12,
        STREAMING_PSBUSY_PUBLIC_DX12_GFX12,
        STREAMING_VSGSBUSY_PUBLIC_DX12_GFX12,
    });

    const uint32_t discrete_passes  = GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kDiscreteCounters);
    const uint32_t streaming_passes = GetPassCount<kGpaSessionSampleTypeStreamingCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kStreamingCounters);

    EXPECT_LE(streaming_passes, discrete_passes);
}

TEST(CounterDllTests, Dx12StreamingPixFullWorkload)
{
    // Simulate a full PIX workload: occupancy + busy counters + ray tracing + shader limitations.
    // This represents the maximum set of counters PIX might enable simultaneously.
    auto constexpr kCounters = std::to_array<uint32_t>({
        // Busy counters
        STREAMING_GPUBUSY_PUBLIC_DX12_GFX12,
        STREAMING_CSBUSY_PUBLIC_DX12_GFX12,
        STREAMING_PSBUSY_PUBLIC_DX12_GFX12,
        STREAMING_VSGSBUSY_PUBLIC_DX12_GFX12,

        // Occupancy
        STREAMING_WAVEOCCUPANCYPCT_PUBLIC_DX12_GFX12,

        // Ray tracing
        STREAMING_RAYTRITESTS_PUBLIC_DX12_GFX12,
        STREAMING_RAYBOXTESTS_PUBLIC_DX12_GFX12,
        STREAMING_RAYTESTSPERWAVE_PUBLIC_DX12_GFX12,

        // Shader limitations
        STREAMING_HSLIMITEDBYVGPR_PUBLIC_DX12_GFX12,
        STREAMING_HSLIMITEDBYLDS_PUBLIC_DX12_GFX12,
        STREAMING_HSLIMITEDBYSCRATCH_PUBLIC_DX12_GFX12,
        STREAMING_HSLIMITEDBYBARRIERS_PUBLIC_DX12_GFX12,
        STREAMING_GSLIMITEDBYVGPR_PUBLIC_DX12_GFX12,
        STREAMING_GSLIMITEDBYLDS_PUBLIC_DX12_GFX12,
        STREAMING_GSLIMITEDBYSCRATCH_PUBLIC_DX12_GFX12,
        STREAMING_PSLIMITEDBYLDS_PUBLIC_DX12_GFX12,
        STREAMING_PSLIMITEDBYVGPR_PUBLIC_DX12_GFX12,
        STREAMING_PSLIMITEDBYSCRATCH_PUBLIC_DX12_GFX12,
        STREAMING_CSLIMITEDBYLDS_PUBLIC_DX12_GFX12,
        STREAMING_CSLIMITEDBYVGPR_PUBLIC_DX12_GFX12,
        STREAMING_CSLIMITEDBYSCRATCH_PUBLIC_DX12_GFX12,
        STREAMING_CSLIMITEDBYBARRIERS_PUBLIC_DX12_GFX12,
        STREAMING_CSLIMITEDBYTHREADGROUPLIMIT_PUBLIC_DX12_GFX12,
    });

    const uint32_t pass_count = GetPassCount<kGpaSessionSampleTypeStreamingCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCounters);

    // With streaming, even this large set should be schedulable in a small number of passes.
    // The exact limit depends on SQ stage isolation rules, but should remain reasonable.
    EXPECT_GE(pass_count, 1u);
    EXPECT_LE(pass_count, 4u) << "Too many passes (" << pass_count << ") for full PIX streaming workload.";
}

TEST(CounterDllTests, Dx12DiscreteGfx12BusyCountersScheduling)
{
    // Verify detailed pass scheduling for discrete busy counters on GFX12.
    auto constexpr kCounters = std::to_array<uint32_t>({
        DISCRETE_CSBUSY_PUBLIC_DX12_GFX12,
        DISCRETE_PSBUSY_PUBLIC_DX12_GFX12,
        DISCRETE_VSGSBUSY_PUBLIC_DX12_GFX12,
    });

    // These three counters require 3 passes due to SQ stage isolation.
    // Verify the pass count is as expected.
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCounters), 3u);
}

TEST(CounterDllTests, Dx12ContextReopenSchedulesCorrectly)
{
    // Test that closing and reopening the context produces consistent results.
    // PIX may open/close contexts multiple times during a session.
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    auto                   lib_guard                  = LoadAndVerifyCounterLib(&gpa_counter_lib_func_table);

    if (!lib_guard)
    {
        return;
    }

    GpaCounterContextHardwareInfo counter_context_hardware_info = {device_info::kAmdVendorId, kDevIdGfx12_0_1, device_info::kRevisionIdAny, nullptr, 0};

    std::vector<GpaUInt32> counter_list      = {DISCRETE_CSBUSY_PUBLIC_DX12_GFX12, DISCRETE_PSBUSY_PUBLIC_DX12_GFX12};
    GpaUInt32              pass_count_first  = 0;
    GpaUInt32              pass_count_second = 0;

    // First open.
    {
        GpaCounterContext gpa_counter_context = nullptr;
        GpaStatus         gpa_status          = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
            kGpaApiDirectx12, kGpaSessionSampleTypeDiscreteCounter, counter_context_hardware_info, kGpaOpenContextDefaultBit, &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetPassCount(
            gpa_counter_context, counter_list.data(), static_cast<GpaUInt32>(counter_list.size()), &pass_count_first);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
    }

    // Second open with same parameters.
    {
        GpaCounterContext gpa_counter_context = nullptr;
        GpaStatus         gpa_status          = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
            kGpaApiDirectx12, kGpaSessionSampleTypeDiscreteCounter, counter_context_hardware_info, kGpaOpenContextDefaultBit, &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetPassCount(
            gpa_counter_context, counter_list.data(), static_cast<GpaUInt32>(counter_list.size()), &pass_count_second);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
    }

    EXPECT_EQ(pass_count_first, pass_count_second);
}

TEST(CounterDllTests, Dx12Gfx11StreamingBusyCounters)
{
    // Test streaming counter scheduling on GFX11 hardware, another common PIX target.
    auto constexpr kCounters = std::to_array<uint32_t>({
        STREAMING_CSBUSY_PUBLIC_DX12_GFX11,
        STREAMING_PSBUSY_PUBLIC_DX12_GFX11,
        STREAMING_VSGSBUSY_PUBLIC_DX12_GFX11,
    });

    const uint32_t pass_count = GetPassCount<kGpaSessionSampleTypeStreamingCounter>(kGpaApiDirectx12, kDevIdGfx11, kCounters);
    // Streaming should be efficient even across different shader stages.
    EXPECT_GE(pass_count, 1u);
}

TEST(CounterDllTests, Dx12Gfx11DiscreteVsStreamingConsistency)
{
    // Streaming should never need more passes than discrete for the same logical counters.
    auto constexpr kDiscreteCounters = std::to_array<uint32_t>({
        DISCRETE_CSBUSY_PUBLIC_DX12_GFX11,
        DISCRETE_PSBUSY_PUBLIC_DX12_GFX11,
        DISCRETE_VSGSBUSY_PUBLIC_DX12_GFX11,
    });

    auto constexpr kStreamingCounters = std::to_array<uint32_t>({
        STREAMING_CSBUSY_PUBLIC_DX12_GFX11,
        STREAMING_PSBUSY_PUBLIC_DX12_GFX11,
        STREAMING_VSGSBUSY_PUBLIC_DX12_GFX11,
    });

    const uint32_t discrete_passes  = GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx12, kDevIdGfx11, kDiscreteCounters);
    const uint32_t streaming_passes = GetPassCount<kGpaSessionSampleTypeStreamingCounter>(kGpaApiDirectx12, kDevIdGfx11, kStreamingCounters);

    EXPECT_LE(streaming_passes, discrete_passes);
}

TEST(CounterDllTests, Dx12MultipleGetPassCountCallsSameContext)
{
    // PIX may call GetPassCount multiple times with different counter sets on the same context.
    // Each call should be independent and produce correct results.
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    auto                   lib_guard                  = LoadAndVerifyCounterLib(&gpa_counter_lib_func_table);

    if (!lib_guard)
    {
        return;
    }

    GpaCounterContextHardwareInfo counter_context_hardware_info = {device_info::kAmdVendorId, kDevIdGfx12_0_1, device_info::kRevisionIdAny, nullptr, 0};
    GpaCounterContext             gpa_counter_context           = nullptr;
    GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
        kGpaApiDirectx12, kGpaSessionSampleTypeDiscreteCounter, counter_context_hardware_info, kGpaOpenContextDefaultBit, &gpa_counter_context);
    EXPECT_EQ(kGpaStatusOk, gpa_status);

    // First call with a small set.
    std::vector<GpaUInt32> small_set    = {DISCRETE_CSBUSY_PUBLIC_DX12_GFX12};
    GpaUInt32              small_passes = 0;
    gpa_status =
        gpa_counter_lib_func_table.GpaCounterLibGetPassCount(gpa_counter_context, small_set.data(), static_cast<GpaUInt32>(small_set.size()), &small_passes);
    EXPECT_EQ(kGpaStatusOk, gpa_status);

    // Second call with a larger set.
    std::vector<GpaUInt32> large_set    = {DISCRETE_CSBUSY_PUBLIC_DX12_GFX12, DISCRETE_PSBUSY_PUBLIC_DX12_GFX12, DISCRETE_VSGSBUSY_PUBLIC_DX12_GFX12};
    GpaUInt32              large_passes = 0;
    gpa_status =
        gpa_counter_lib_func_table.GpaCounterLibGetPassCount(gpa_counter_context, large_set.data(), static_cast<GpaUInt32>(large_set.size()), &large_passes);
    EXPECT_EQ(kGpaStatusOk, gpa_status);

    // The larger set should need at least as many passes as the smaller set.
    EXPECT_GE(large_passes, small_passes);

    // Third call: repeat the small set to confirm it hasn't been corrupted.
    GpaUInt32 small_passes_again = 0;
    gpa_status                   = gpa_counter_lib_func_table.GpaCounterLibGetPassCount(
        gpa_counter_context, small_set.data(), static_cast<GpaUInt32>(small_set.size()), &small_passes_again);
    EXPECT_EQ(kGpaStatusOk, gpa_status);
    EXPECT_EQ(small_passes, small_passes_again);

    gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
}

TEST(CounterDllTests, Dx11CounterScheduling)
{
    auto constexpr kCounters = std::to_array<uint32_t>({
        DISCRETE_GPUTIME_PUBLIC_DX11_GFX11,
        DISCRETE_GPUBUSY_PUBLIC_DX11_GFX11,
        DISCRETE_TESSELLATORBUSY_PUBLIC_DX11_GFX11,
    });
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx11, kDevIdGfx11, kCounters), 2);
}

TEST(CounterDllTests, Dx12CounterScheduling)
{
    auto constexpr kCounters = std::to_array<uint32_t>({
        DISCRETE_CSBUSY_PUBLIC_DX12_GFX12,
        DISCRETE_PSBUSY_PUBLIC_DX12_GFX12,
        DISCRETE_VSGSBUSY_PUBLIC_DX12_GFX12,
    });
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCounters), 3u);
}

TEST(CounterDllTests, Dx12CounterSchedulingStreaming)
{
    auto constexpr kCounters = std::to_array<uint32_t>({
        STREAMING_CSBUSY_PUBLIC_DX12_GFX12,
        STREAMING_PSBUSY_PUBLIC_DX12_GFX12,
        STREAMING_VSGSBUSY_PUBLIC_DX12_GFX12,
    });
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeStreamingCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCounters), 1u);
}

TEST(CounterDllTests, Dx12CounterSchedulingStreamingPix)
{
    // Streaming counters used by PIX
    // To simulate a realistic PIX scenario, these are all the streaming counters used by PIX that are supported on GFX12.
    auto constexpr kCounters = std::to_array<uint32_t>({STREAMING_WAVEOCCUPANCYPCT_PUBLIC_DX12_GFX12,
                                                        STREAMING_RAYTRITESTS_PUBLIC_DX12_GFX12,
                                                        STREAMING_RAYBOXTESTS_PUBLIC_DX12_GFX12,
                                                        STREAMING_RAYTESTSPERWAVE_PUBLIC_DX12_GFX12,
                                                        STREAMING_HSLIMITEDBYVGPR_PUBLIC_DX12_GFX12,
                                                        STREAMING_HSLIMITEDBYLDS_PUBLIC_DX12_GFX12,
                                                        STREAMING_HSLIMITEDBYSCRATCH_PUBLIC_DX12_GFX12,
                                                        STREAMING_HSLIMITEDBYBARRIERS_PUBLIC_DX12_GFX12,
                                                        STREAMING_GSLIMITEDBYVGPR_PUBLIC_DX12_GFX12,
                                                        STREAMING_GSLIMITEDBYLDS_PUBLIC_DX12_GFX12,
                                                        STREAMING_GSLIMITEDBYSCRATCH_PUBLIC_DX12_GFX12,
                                                        STREAMING_PSLIMITEDBYLDS_PUBLIC_DX12_GFX12,
                                                        STREAMING_PSLIMITEDBYVGPR_PUBLIC_DX12_GFX12,
                                                        STREAMING_PSLIMITEDBYSCRATCH_PUBLIC_DX12_GFX12,
                                                        STREAMING_CSLIMITEDBYLDS_PUBLIC_DX12_GFX12,
                                                        STREAMING_CSLIMITEDBYVGPR_PUBLIC_DX12_GFX12,
                                                        STREAMING_CSLIMITEDBYSCRATCH_PUBLIC_DX12_GFX12,
                                                        STREAMING_CSLIMITEDBYBARRIERS_PUBLIC_DX12_GFX12,
                                                        STREAMING_CSLIMITEDBYTHREADGROUPLIMIT_PUBLIC_DX12_GFX12});

    // All these counters should fit into 1 pass. NOTE: PIX does not actually impose a requirement on this.
    // The point of this test is to make sure that even with a large number of streaming counters, they are still scheduled efficiently.
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeStreamingCounter>(kGpaApiDirectx12, kDevIdGfx12_0_1, kCounters), 1u);
}

#define MakeExpectedCounterLocationEntry(x, y) {expected_counters_pass##x[y], MakeLocation(x, y)},

static inline GpaCounterResultLocation MakeLocation(const GpaUInt16 pass, const GpaUInt16 offset)
{
    GpaCounterResultLocation location = {pass, offset};
    return location;
}

TEST(CounterDllTests, Dx11Gfx11BusyCounters)
{
#pragma region Gfx11
    {
        // This test will build up incrementally to help with understanding.
        {
            // Part 1: just schedule the VSGSBUSY counter.
            // VSGSBUSY uses the following counters (as seen in public_counter_definitions_gfx11.txt):
            // SPI*_PERF_GS_BUSY[0..5]
            // SPI*_PERF_HS_WAVE[0..5]
            // CPF_PERF_SEL_CPF_STAT_BUSY
            //
            // The PublicCounterCompiler converts these names into indexes, as seen in public_counter_definitions_dx11_gfx11.cc.
            // It is these indexes that are used in the expected_counters_pass* arrays below.
            //
            // On Gfx11 hardware, there are 6 SPI block instances, and 1 CPF block. Each SPI block can collect 6 events simultaneously; CPF can collect 2.
            //
            // In the counter list above, there are 2 different events from the SPI block, and 1 event from CPF, so all of these can be collected in a single pass.
            // The actual number of hardware counters that gets scheduled will be (2 SPI events * 6 block instances) + (1 CPF event * 1 block instance) = 13 hardware counters.

            // clang-format off
            std::vector<uint32_t> counters = {DISCRETE_VSGSBUSY_PUBLIC_DX11_GFX11};

            // All 13 events from VSGSBUSY can be scheduled in a single pass. They are intentionally scheduled in the same order as they are listed in the public counter definition file.
            std::vector<uint32_t> expected_counters_pass0 = {
                36247, 36531, 36815, 37099, 37383, 37667,  // SPI*_PERF_GS_BUSY[0..5]
                36272, 36556, 36840, 37124, 37408, 37692,  // SPI*_PERF_HS_WAVE[0..5]
                24};                                       // CPF_PERF_SEL_CPF_STAT_BUSY

            std::vector<std::vector<uint32_t>> expected_hw_counters_per_pass = {expected_counters_pass0};

            std::map<uint32_t, GpaCounterResultLocation> expected_locations_vsgsbusy = {
                MakeExpectedCounterLocationEntry(0, 0) MakeExpectedCounterLocationEntry(0, 1) MakeExpectedCounterLocationEntry(0, 2)
                MakeExpectedCounterLocationEntry(0, 3) MakeExpectedCounterLocationEntry(0, 4) MakeExpectedCounterLocationEntry(0, 5)
                MakeExpectedCounterLocationEntry(0, 6) MakeExpectedCounterLocationEntry(0, 7) MakeExpectedCounterLocationEntry(0, 8)
                MakeExpectedCounterLocationEntry(0, 9) MakeExpectedCounterLocationEntry(0, 10) MakeExpectedCounterLocationEntry(0, 11)
                MakeExpectedCounterLocationEntry(0, 12)};

            std::map<uint32_t, std::map<uint32_t, GpaCounterResultLocation>> expected_result_locations = {
                {DISCRETE_VSGSBUSY_PUBLIC_DX11_GFX11, expected_locations_vsgsbusy}};
            // clang-format on

            VerifyCountersInPass(kGpaApiDirectx11, kDevIdGfx11, counters, expected_hw_counters_per_pass, expected_result_locations);
        }

        {
            // Part 2: Schedule VSGSBUSY and PRETESSELLATIONBUSY.
            // PRETESSELLATIONBUSY uses the following counters (as seen in public_counter_definitions_gfx11.txt):
            // SPI*_PERF_HS_BUSY[0..5]
            // SPI*_PERF_HS_WAVE[0..5]
            // CPF_PERF_SEL_CPF_STAT_BUSY

            // PRETESSELLATIONBUSY re-uses 1 of the SPI events VSGSBUSY (1 event * 6 instances = a total of 6 counters),
            // and adds 1 more event (6 additional counters) to the same pass.
            // The CPF event is the same as VSGSBUSY, so that can also be re-used.

            // clang-format off
            std::vector<uint32_t> counters = {DISCRETE_VSGSBUSY_PUBLIC_DX11_GFX11,
                                                  DISCRETE_PRETESSELLATIONBUSY_PUBLIC_DX11_GFX11};

            // The top three lines are the same as VSGSBUSY above, some of which will be shared with PRETESSELLATIONBUSY.
            // The second line is the 6 additional counters for PRETESSELLATIONBUSY.
            std::vector<uint32_t> expected_counters_pass0 = {
                36247, 36531, 36815, 37099, 37383, 37667,  // SPI*_PERF_GS_BUSY[0..5]
                36272, 36556, 36840, 37124, 37408, 37692,  // SPI*_PERF_HS_WAVE[0..5]
                24,                                        // CPF_PERF_SEL_CPF_STAT_BUSY
                36267, 36551, 36835, 37119, 37403, 37687}; // SPI*_PERF_HS_BUSY[0..5]

            std::vector<std::vector<uint32_t>> expected_hw_counters_per_pass = {
                expected_counters_pass0,
            };

            // All the required hardware counters should be scheduled according to the arrays above.
            // Below are maps of where (which pass and result index) each derived counter will be looking to find the values to input into the counter equation.
            // The macros below make assumptions about the variables names above, and the size of the arrays.
            // The first parameter is the pass (so needs to match with "pass0" above), and the second parameter is the index into the corresponding array above.

            std::map<uint32_t, GpaCounterResultLocation> expected_locations_vsgsbusy
            {
                MakeExpectedCounterLocationEntry(0, 0) MakeExpectedCounterLocationEntry(0, 1) MakeExpectedCounterLocationEntry(0, 2)
                MakeExpectedCounterLocationEntry(0, 3) MakeExpectedCounterLocationEntry(0, 4) MakeExpectedCounterLocationEntry(0, 5)
                MakeExpectedCounterLocationEntry(0, 6) MakeExpectedCounterLocationEntry(0, 7) MakeExpectedCounterLocationEntry(0, 8)
                MakeExpectedCounterLocationEntry(0, 9) MakeExpectedCounterLocationEntry(0, 10) MakeExpectedCounterLocationEntry(0, 11)
                MakeExpectedCounterLocationEntry(0, 12)};

            // For PreTessBusy, the first 6 counters are added to the end of pass 0, and the second 6 counters are re-used from earlier in the pass.
            // This re-ordering is okay, since they are all still being collected in the same pass.
            // The CPF counter is also re-used from the pass.
            std::map<uint32_t, GpaCounterResultLocation> expected_locations_pretessbusy
            {
                MakeExpectedCounterLocationEntry(0, 13) MakeExpectedCounterLocationEntry(0, 14) MakeExpectedCounterLocationEntry(0, 15)
                MakeExpectedCounterLocationEntry(0, 16) MakeExpectedCounterLocationEntry(0, 17) MakeExpectedCounterLocationEntry(0, 18)
                MakeExpectedCounterLocationEntry(0, 6) MakeExpectedCounterLocationEntry(0, 7) MakeExpectedCounterLocationEntry(0, 8)
                MakeExpectedCounterLocationEntry(0, 9) MakeExpectedCounterLocationEntry(0, 10) MakeExpectedCounterLocationEntry(0, 11)
                MakeExpectedCounterLocationEntry(0, 12)};

            std::map<uint32_t, std::map<uint32_t, GpaCounterResultLocation>> expected_result_locations = {
                {DISCRETE_VSGSBUSY_PUBLIC_DX11_GFX11,            expected_locations_vsgsbusy},
                {DISCRETE_PRETESSELLATIONBUSY_PUBLIC_DX11_GFX11, expected_locations_pretessbusy},
            };
            // clang-format on

            VerifyCountersInPass(kGpaApiDirectx11, kDevIdGfx11, counters, expected_hw_counters_per_pass, expected_result_locations);
        }

        {
            // Part 3: Add POSTTESSELLATIONBUSY to the other two counters.
            // POSTTESSELLATIONBUSY uses the following counters:
            // SPI*_PERF_GS_BUSY[0..5]
            // SPI*_PERF_HS_WAVE[0..5]
            // CPF_PERF_SEL_CPF_STAT_BUSY
            //
            // These are exactly the same events used by VSGSBUSY, so nothing needs to be added to the pass!

            // clang-format off
            std::vector<uint32_t> counters = {DISCRETE_VSGSBUSY_PUBLIC_DX11_GFX11,
                                                  DISCRETE_PRETESSELLATIONBUSY_PUBLIC_DX11_GFX11,
                                                  DISCRETE_POSTTESSELLATIONBUSY_PUBLIC_DX11_GFX11};

            // The top three lines are the same as VSGSBUSY above, some of which will be shared with PRETESSELLATIONBUSY and POSTTESSELLATIONBUSY.
            // The second line is the 6 counters for PRETESSELLATIONBUSY.
            std::vector<uint32_t> expected_counters_pass0 = {
                36247, 36531, 36815, 37099, 37383, 37667,  // SPI*_PERF_GS_BUSY[0..5]
                36272, 36556, 36840, 37124, 37408, 37692,  // SPI*_PERF_HS_WAVE[0..5]
                24,                                        // CPF_PERF_SEL_CPF_STAT_BUSY
                36267, 36551, 36835, 37119, 37403, 37687}; // SPI*_PERF_HS_BUSY[0..5]

            std::vector<std::vector<uint32_t>> expected_hw_counters_per_pass = {
                expected_counters_pass0,
            };

            // All the required hardware counters should be scheduled according to the arrays above.
            // Below are maps of where (which pass and result index) each derived counter will be looking to find the values to input into the counter equation.
            // The macros below make assumptions about the variables names above, and the size of the arrays.
            // The first parameter is the pass (so needs to match with "pass0" above), and the second parameter is the index into the corresponding array above.

            std::map<uint32_t, GpaCounterResultLocation> expected_locations_vsgsbusy
            {
                MakeExpectedCounterLocationEntry(0, 0) MakeExpectedCounterLocationEntry(0, 1) MakeExpectedCounterLocationEntry(0, 2)
                MakeExpectedCounterLocationEntry(0, 3) MakeExpectedCounterLocationEntry(0, 4) MakeExpectedCounterLocationEntry(0, 5)
                MakeExpectedCounterLocationEntry(0, 6) MakeExpectedCounterLocationEntry(0, 7) MakeExpectedCounterLocationEntry(0, 8)
                MakeExpectedCounterLocationEntry(0, 9) MakeExpectedCounterLocationEntry(0, 10) MakeExpectedCounterLocationEntry(0, 11)
                MakeExpectedCounterLocationEntry(0, 12)};

            std::map<uint32_t, GpaCounterResultLocation> expected_locations_pretessbusy
            {
                MakeExpectedCounterLocationEntry(0, 13) MakeExpectedCounterLocationEntry(0, 14) MakeExpectedCounterLocationEntry(0, 15)
                MakeExpectedCounterLocationEntry(0, 16) MakeExpectedCounterLocationEntry(0, 17) MakeExpectedCounterLocationEntry(0, 18)
                MakeExpectedCounterLocationEntry(0, 6) MakeExpectedCounterLocationEntry(0, 7) MakeExpectedCounterLocationEntry(0, 8)
                MakeExpectedCounterLocationEntry(0, 9) MakeExpectedCounterLocationEntry(0, 10) MakeExpectedCounterLocationEntry(0, 11)
                MakeExpectedCounterLocationEntry(0, 12)};

            // PostTessBusy uses the same result locations as vsgsbusy above.
            std::map<uint32_t, GpaCounterResultLocation> expected_locations_posttessbusy
            {
                MakeExpectedCounterLocationEntry(0, 0) MakeExpectedCounterLocationEntry(0, 1) MakeExpectedCounterLocationEntry(0, 2)
                MakeExpectedCounterLocationEntry(0, 3) MakeExpectedCounterLocationEntry(0, 4) MakeExpectedCounterLocationEntry(0, 5)
                MakeExpectedCounterLocationEntry(0, 6) MakeExpectedCounterLocationEntry(0, 7) MakeExpectedCounterLocationEntry(0, 8)
                MakeExpectedCounterLocationEntry(0, 9) MakeExpectedCounterLocationEntry(0, 10) MakeExpectedCounterLocationEntry(0, 11)
                MakeExpectedCounterLocationEntry(0, 12)};

            std::map<uint32_t, std::map<uint32_t, GpaCounterResultLocation>> expected_result_locations = {
                {DISCRETE_VSGSBUSY_PUBLIC_DX11_GFX11,            expected_locations_vsgsbusy},
                {DISCRETE_PRETESSELLATIONBUSY_PUBLIC_DX11_GFX11, expected_locations_pretessbusy},
                {DISCRETE_POSTTESSELLATIONBUSY_PUBLIC_DX11_GFX11, expected_locations_posttessbusy},
            };
            // clang-format on

            VerifyCountersInPass(kGpaApiDirectx11, kDevIdGfx11, counters, expected_hw_counters_per_pass, expected_result_locations);
        }

        {
            // Part 4: Add PSBUSY to shake things up, in an unexpected way!
            //
            // PSBUSY uses the following counters:
            // SPI*_PERF_PS0_BUSY[0..5]
            // SPI*_PERF_PS0_WAVE[0..5]
            // SPI*_PERF_PS1_BUSY[0..5]
            // SPI*_PERF_PS1_WAVE[0..5]
            // SPI*_PERF_PS2_BUSY[0..5]
            // SPI*_PERF_PS2_WAVE[0..5]
            // SPI*_PERF_PS3_BUSY[0..5]
            // SPI*_PERF_PS3_WAVE[0..5]
            // CPF_PERF_SEL_CPF_STAT_BUSY
            //
            // If you've been following along with Parts 1, 2, and 3, then you would probably expect that PSBUSY will be added after all of the other counters,
            // so we could easily add them where they fit into the pass from above. However, that is not the case.
            //
            //
            //
            // PSBUSY needs a total of 8 events from SPI, but since SPI can only collect 6 at a time, PSBUSY will need to be split up into 2 different passes.
            // It does not matter which SPI events are in which pass, so GPA will add as many as possible to pass 0, and the rest to pass 1. In the event that
            // other pre-selected counters would have caused PSBUSY to spill into a third pass, GPA would then NOT add any counters to pass 0, and it would be
            // scheduled in two new passes. Having said that, this is not the situation in this test, and PSBUSY can successfully be scheduled within pass 0 and pass 1.
            // Specifically, the SPI blocks already have 3 events scheduled and have room for 3 more, so PSBUSY will use those 3 events in pass 0, and the remaining
            // 5 events in pass 1. The same CPF event is used in PSBUSY as the previous derived counters, so that will also be re-used from pass 0.

            // clang-format off
            std::vector<uint32_t> counters = {DISCRETE_VSGSBUSY_PUBLIC_DX11_GFX11,
                                                  DISCRETE_PRETESSELLATIONBUSY_PUBLIC_DX11_GFX11,
                                                  DISCRETE_POSTTESSELLATIONBUSY_PUBLIC_DX11_GFX11,
                                                  DISCRETE_PSBUSY_PUBLIC_DX11_GFX11,
            };

            // Hmmm, Pass 0 now has the first 6 SPI events from PSBusy, plus the CPF event from PSBusy.
            // I'm not sure why things shifted around....?
            std::vector<uint32_t> expected_counters_pass0 = {36302, 36586, 36870, 37154, 37438, 37722,
                                                             36318, 36602, 36886, 37170, 37454, 37738,
                                                             36303, 36587, 36871, 37155, 37439, 37723,
                                                             36319, 36603, 36887, 37171, 37455, 37739,
                                                             36304, 36588, 36872, 37156, 37440, 37724,
                                                             36320, 36604, 36888, 37172, 37456, 37740,
                                                             24};

            // For some reason, pass 1 now contains what used to be in pass 0, plus the final 2 events (12 counters) from PSBusy.
            // Note that the CPF counter (24) is also collected in this pass, and this instance of it should be used by VSGSBUSY, PRETESSELLATIONBUSY, and POSTTESSELLATIONBUSY
            std::vector<uint32_t> expected_counters_pass1 = {36247, 36531, 36815, 37099, 37383, 37667, 36272, 36556, 36840, 37124, 37408, 37692, 24,
                                                             36267, 36551, 36835, 37119, 37403, 37687,
                                                             36305, 36589, 36873, 37157, 37441, 37725, 36321, 36605, 36889, 37173, 37457, 37741,
            };

            std::vector<std::vector<uint32_t>> expected_hw_counters_per_pass = {
                expected_counters_pass0,
                expected_counters_pass1,
            };

            // All the required hardware counters should be scheduled according to the arrays above.
            // Below are maps of where (which pass and result index) each derived counter will be looking to find the values to input into the counter equation.
            // The macros below make assumptions about the variables names above, and the size of the arrays.
            // The first parameter is the pass (so needs to match with "pass0" above), and the second parameter is the index into the corresponding array above.

            std::map<uint32_t, GpaCounterResultLocation> expected_locations_vsgsbusy
            {
                MakeExpectedCounterLocationEntry(1, 0) MakeExpectedCounterLocationEntry(1, 1) MakeExpectedCounterLocationEntry(1, 2)
                MakeExpectedCounterLocationEntry(1, 3) MakeExpectedCounterLocationEntry(1, 4) MakeExpectedCounterLocationEntry(1, 5)
                MakeExpectedCounterLocationEntry(1, 6) MakeExpectedCounterLocationEntry(1, 7) MakeExpectedCounterLocationEntry(1, 8)
                MakeExpectedCounterLocationEntry(1, 9) MakeExpectedCounterLocationEntry(1, 10) MakeExpectedCounterLocationEntry(1, 11)
                MakeExpectedCounterLocationEntry(1, 12)};

            std::map<uint32_t, GpaCounterResultLocation> expected_locations_pretessbusy
            {
                MakeExpectedCounterLocationEntry(1, 13) MakeExpectedCounterLocationEntry(1, 14) MakeExpectedCounterLocationEntry(1, 15)
                MakeExpectedCounterLocationEntry(1, 16) MakeExpectedCounterLocationEntry(1, 17) MakeExpectedCounterLocationEntry(1, 18)
                MakeExpectedCounterLocationEntry(1, 6) MakeExpectedCounterLocationEntry(1, 7) MakeExpectedCounterLocationEntry(1, 8)
                MakeExpectedCounterLocationEntry(1, 9) MakeExpectedCounterLocationEntry(1, 10) MakeExpectedCounterLocationEntry(1, 11)
                MakeExpectedCounterLocationEntry(1, 12)};

            // PostTessBusy uses the same result locations as vsgsbusy above.
            std::map<uint32_t, GpaCounterResultLocation> expected_locations_posttessbusy
            {
                MakeExpectedCounterLocationEntry(1, 0) MakeExpectedCounterLocationEntry(1, 1) MakeExpectedCounterLocationEntry(1, 2)
                MakeExpectedCounterLocationEntry(1, 3) MakeExpectedCounterLocationEntry(1, 4) MakeExpectedCounterLocationEntry(1, 5)
                MakeExpectedCounterLocationEntry(1, 6) MakeExpectedCounterLocationEntry(1, 7) MakeExpectedCounterLocationEntry(1, 8)
                MakeExpectedCounterLocationEntry(1, 9) MakeExpectedCounterLocationEntry(1, 10) MakeExpectedCounterLocationEntry(1, 11)
                MakeExpectedCounterLocationEntry(1, 12)};

            // The order here has to match the order of the counters in the public counter definition file.
            std::map<uint32_t, GpaCounterResultLocation> expected_location_psbusy
            {
                // SPI*_PERF_PS0_BUSY[0..5]
                MakeExpectedCounterLocationEntry(0, 0) MakeExpectedCounterLocationEntry(0, 1) MakeExpectedCounterLocationEntry(0, 2)
                MakeExpectedCounterLocationEntry(0, 3) MakeExpectedCounterLocationEntry(0, 4) MakeExpectedCounterLocationEntry(0, 5)

                // SPI*_PERF_PS0_WAVE[0..5]
                MakeExpectedCounterLocationEntry(0, 6) MakeExpectedCounterLocationEntry(0, 7) MakeExpectedCounterLocationEntry(0, 8)
                MakeExpectedCounterLocationEntry(0, 9) MakeExpectedCounterLocationEntry(0, 10) MakeExpectedCounterLocationEntry(0, 11)

                // SPI*_PERF_PS1_BUSY[0..5]
                MakeExpectedCounterLocationEntry(0, 12) MakeExpectedCounterLocationEntry(0, 13) MakeExpectedCounterLocationEntry(0, 14)
                MakeExpectedCounterLocationEntry(0, 15) MakeExpectedCounterLocationEntry(0, 16) MakeExpectedCounterLocationEntry(0, 17)

                // SPI*_PERF_PS1_WAVE[0..5]
                MakeExpectedCounterLocationEntry(0, 18) MakeExpectedCounterLocationEntry(0, 19) MakeExpectedCounterLocationEntry(0, 20)
                MakeExpectedCounterLocationEntry(0, 21) MakeExpectedCounterLocationEntry(0, 22) MakeExpectedCounterLocationEntry(0, 23)

                // SPI*_PERF_PS2_BUSY[0..5]
                MakeExpectedCounterLocationEntry(0, 24) MakeExpectedCounterLocationEntry(0, 25) MakeExpectedCounterLocationEntry(0, 26)
                MakeExpectedCounterLocationEntry(0, 27) MakeExpectedCounterLocationEntry(0, 28) MakeExpectedCounterLocationEntry(0, 29)

                // SPI*_PERF_PS2_WAVE[0..5]
                MakeExpectedCounterLocationEntry(0, 30) MakeExpectedCounterLocationEntry(0, 31) MakeExpectedCounterLocationEntry(0, 32)
                MakeExpectedCounterLocationEntry(0, 33) MakeExpectedCounterLocationEntry(0, 34) MakeExpectedCounterLocationEntry(0, 35)

                // SPI*_PERF_PS3_BUSY[0..5]
                MakeExpectedCounterLocationEntry(1, 19) MakeExpectedCounterLocationEntry(1, 20) MakeExpectedCounterLocationEntry(1, 21)
                MakeExpectedCounterLocationEntry(1, 22) MakeExpectedCounterLocationEntry(1, 23) MakeExpectedCounterLocationEntry(1, 24)

                // SPI*_PERF_PS3_WAVE[0..5]
                MakeExpectedCounterLocationEntry(1, 25) MakeExpectedCounterLocationEntry(1, 26) MakeExpectedCounterLocationEntry(1, 27)
                MakeExpectedCounterLocationEntry(1, 28) MakeExpectedCounterLocationEntry(1, 29) MakeExpectedCounterLocationEntry(1, 30)

                // CPF_PERF_SEL_CPF_STAT_BUSY
                MakeExpectedCounterLocationEntry(0, 36)
            };
            // clang-format on

            std::map<uint32_t, std::map<uint32_t, GpaCounterResultLocation>> expected_result_locations = {
                {DISCRETE_VSGSBUSY_PUBLIC_DX11_GFX11, expected_locations_vsgsbusy},
                {DISCRETE_PRETESSELLATIONBUSY_PUBLIC_DX11_GFX11, expected_locations_pretessbusy},
                {DISCRETE_POSTTESSELLATIONBUSY_PUBLIC_DX11_GFX11, expected_locations_posttessbusy},
                {DISCRETE_PSBUSY_PUBLIC_DX11_GFX11, expected_location_psbusy},
            };

            VerifyCountersInPass(kGpaApiDirectx11, kDevIdGfx11, counters, expected_hw_counters_per_pass, expected_result_locations);
        }

        {
            // Part 5: Add CSBUSY
            // CSBUSY uses the following counters:
            // SPI*_PERF_CSGN_BUSY[0..5]
            // SPI*_PERF_CSGN_WAVE[0..5]
            // SPI*_PERF_CSN_BUSY[0..5]
            // SPI*_PERF_CSN_WAVE[0..5]
            // CPF_PERF_SEL_CPF_STAT_BUSY
            //
            // 4 new SPI events, plus the same CPF event.
            // This can fit into a single pass, so GPA should never split it into multiple passes.
            // Neither of the existing passes can support 4 more SPI events, so this must become its own pass, but which pass will it be?

            // clang-format off
            std::vector<uint32_t> counters = {DISCRETE_VSGSBUSY_PUBLIC_DX11_GFX11,
                                                  DISCRETE_PRETESSELLATIONBUSY_PUBLIC_DX11_GFX11,
                                                  DISCRETE_POSTTESSELLATIONBUSY_PUBLIC_DX11_GFX11,
                                                  DISCRETE_PSBUSY_PUBLIC_DX11_GFX11,
                                                  DISCRETE_CSBUSY_PUBLIC_DX11_GFX11
            };

            // Pass 0 has most of the PSBusy counters; unchanged from Part 4.
            std::vector<uint32_t> expected_counters_pass0 = {36302, 36586, 36870, 37154, 37438, 37722,
                                                             36318, 36602, 36886, 37170, 37454, 37738,
                                                             36303, 36587, 36871, 37155, 37439, 37723,
                                                             36319, 36603, 36887, 37171, 37455, 37739,
                                                             36304, 36588, 36872, 37156, 37440, 37724,
                                                             36320, 36604, 36888, 37172, 37456, 37740,
                                                             24};

            // Pass 1 has all of the CSBusy counters (first 5 lines).
            // Then has the remaining PSBusy counters.
            std::vector<uint32_t> expected_counters_pass1 = {
                36283, 36567, 36851, 37135, 37419, 37703,  // SPI*_PERF_CSGN_BUSY[0..5]
                36287, 36571, 36855, 37139, 37423, 37707,  // SPI*_PERF_CSGN_WAVE[0..5]
                36291, 36575, 36859, 37143, 37427, 37711,  // SPI*_PERF_CSN_BUSY[0..5]
                36295, 36579, 36863, 37147, 37431, 37715,  // SPI*_PERF_CSN_WAVE[0..5]
                24,                                        // CPF_PERF_SEL_CPF_STAT_BUSY
                36247, 36531, 36815, 37099, 37383, 37667, 36272, 36556, 36840, 37124, 37408, 37692};

            std::vector<uint32_t> expected_counters_pass2 = {
                36267, 36551, 36835, 37119, 37403, 37687,
                36272, 36556, 36840, 37124, 37408, 37692,
                24,
                36305, 36589, 36873, 37157, 37441, 37725,
                36321, 36605, 36889, 37173, 37457, 37741,
            };

            std::vector<std::vector<uint32_t>> expected_hw_counters_per_pass = {
                expected_counters_pass0,
                expected_counters_pass1,
                expected_counters_pass2,
            };

            // All the required hardware counters should be scheduled according to the arrays above.
            // Below are maps of where (which pass and result index) each derived counter will be looking to find the values to input into the counter equation.
            // The macros below make assumptions about the variables names above, and the size of the arrays.
            // The first parameter is the pass (so needs to match with "pass0" above), and the second parameter is the index into the corresponding array above.

            std::map<uint32_t, GpaCounterResultLocation> expected_locations_vsgsbusy
            {
                MakeExpectedCounterLocationEntry(0, 0) MakeExpectedCounterLocationEntry(0, 1) MakeExpectedCounterLocationEntry(0, 2)
                MakeExpectedCounterLocationEntry(0, 3) MakeExpectedCounterLocationEntry(0, 4) MakeExpectedCounterLocationEntry(0, 5)
                MakeExpectedCounterLocationEntry(0, 6) MakeExpectedCounterLocationEntry(0, 7) MakeExpectedCounterLocationEntry(0, 8)
                MakeExpectedCounterLocationEntry(0, 9) MakeExpectedCounterLocationEntry(0, 10) MakeExpectedCounterLocationEntry(0, 11)
                MakeExpectedCounterLocationEntry(0, 12)};

            std::map<uint32_t, GpaCounterResultLocation> expected_locations_pretessbusy
            {
                MakeExpectedCounterLocationEntry(0, 13) MakeExpectedCounterLocationEntry(0, 14) MakeExpectedCounterLocationEntry(0, 15)
                MakeExpectedCounterLocationEntry(0, 16) MakeExpectedCounterLocationEntry(0, 17) MakeExpectedCounterLocationEntry(0, 18)
                MakeExpectedCounterLocationEntry(0, 6) MakeExpectedCounterLocationEntry(0, 7) MakeExpectedCounterLocationEntry(0, 8)
                MakeExpectedCounterLocationEntry(0, 9) MakeExpectedCounterLocationEntry(0, 10) MakeExpectedCounterLocationEntry(0, 11)
                MakeExpectedCounterLocationEntry(0, 12)};

            // PostTessBusy uses the same result locations as vsgsbusy above.
            std::map<uint32_t, GpaCounterResultLocation> expected_locations_posttessbusy
            {
                MakeExpectedCounterLocationEntry(0, 0) MakeExpectedCounterLocationEntry(0, 1) MakeExpectedCounterLocationEntry(0, 2)
                MakeExpectedCounterLocationEntry(0, 3) MakeExpectedCounterLocationEntry(0, 4) MakeExpectedCounterLocationEntry(0, 5)
                MakeExpectedCounterLocationEntry(0, 6) MakeExpectedCounterLocationEntry(0, 7) MakeExpectedCounterLocationEntry(0, 8)
                MakeExpectedCounterLocationEntry(0, 9) MakeExpectedCounterLocationEntry(0, 10) MakeExpectedCounterLocationEntry(0, 11)
                MakeExpectedCounterLocationEntry(0, 12)};

            // The order here has to match the order of the counters in the public counter definition file.
            std::map<uint32_t, GpaCounterResultLocation> expected_location_psbusy
            {
                // SPI*_PERF_PS0_BUSY[0..5]
                MakeExpectedCounterLocationEntry(0, 0) MakeExpectedCounterLocationEntry(0, 1) MakeExpectedCounterLocationEntry(0, 2)
                MakeExpectedCounterLocationEntry(0, 3) MakeExpectedCounterLocationEntry(0, 4) MakeExpectedCounterLocationEntry(0, 5)

                // SPI*_PERF_PS0_WAVE[0..5]
                MakeExpectedCounterLocationEntry(0, 6) MakeExpectedCounterLocationEntry(0, 7) MakeExpectedCounterLocationEntry(0, 8)
                MakeExpectedCounterLocationEntry(0, 9) MakeExpectedCounterLocationEntry(0, 10) MakeExpectedCounterLocationEntry(0, 11)

                // SPI*_PERF_PS1_BUSY[0..5]
                MakeExpectedCounterLocationEntry(0, 12) MakeExpectedCounterLocationEntry(0, 13) MakeExpectedCounterLocationEntry(0, 14)
                MakeExpectedCounterLocationEntry(0, 15) MakeExpectedCounterLocationEntry(0, 16) MakeExpectedCounterLocationEntry(0, 17)

                // SPI*_PERF_PS1_WAVE[0..5]
                MakeExpectedCounterLocationEntry(0, 18) MakeExpectedCounterLocationEntry(0, 19) MakeExpectedCounterLocationEntry(0, 20)
                MakeExpectedCounterLocationEntry(0, 21) MakeExpectedCounterLocationEntry(0, 22) MakeExpectedCounterLocationEntry(0, 23)

                // SPI*_PERF_PS2_BUSY[0..5]
                MakeExpectedCounterLocationEntry(0, 24) MakeExpectedCounterLocationEntry(0, 25) MakeExpectedCounterLocationEntry(0, 26)
                MakeExpectedCounterLocationEntry(0, 27) MakeExpectedCounterLocationEntry(0, 28) MakeExpectedCounterLocationEntry(0, 29)

                // SPI*_PERF_PS2_WAVE[0..5]
                MakeExpectedCounterLocationEntry(0, 30) MakeExpectedCounterLocationEntry(0, 31) MakeExpectedCounterLocationEntry(0, 32)
                MakeExpectedCounterLocationEntry(0, 33) MakeExpectedCounterLocationEntry(0, 34) MakeExpectedCounterLocationEntry(0, 35)

                // SPI*_PERF_PS3_BUSY[0..5]
                MakeExpectedCounterLocationEntry(1, 19) MakeExpectedCounterLocationEntry(1, 20) MakeExpectedCounterLocationEntry(1, 21)
                MakeExpectedCounterLocationEntry(1, 22) MakeExpectedCounterLocationEntry(1, 23) MakeExpectedCounterLocationEntry(1, 24)

                // SPI*_PERF_PS3_WAVE[0..5]
                MakeExpectedCounterLocationEntry(1, 25) MakeExpectedCounterLocationEntry(1, 26) MakeExpectedCounterLocationEntry(1, 27)
                MakeExpectedCounterLocationEntry(1, 28) MakeExpectedCounterLocationEntry(1, 29) MakeExpectedCounterLocationEntry(1, 30)

                // CPF_PERF_SEL_CPF_STAT_BUSY
                MakeExpectedCounterLocationEntry(0, 36)
            };

            std::map<uint32_t, GpaCounterResultLocation> expected_locations_csbusy
            {
                // SPI*_PERF_CSGN_BUSY[0..5]
                MakeExpectedCounterLocationEntry(1, 0) MakeExpectedCounterLocationEntry(1, 1) MakeExpectedCounterLocationEntry(1, 2)
                MakeExpectedCounterLocationEntry(1, 3) MakeExpectedCounterLocationEntry(1, 4) MakeExpectedCounterLocationEntry(1, 5)

                // SPI*_PERF_CSGN_WAVE[0..5]
                MakeExpectedCounterLocationEntry(1, 6) MakeExpectedCounterLocationEntry(1, 7) MakeExpectedCounterLocationEntry(1, 8)
                MakeExpectedCounterLocationEntry(1, 9) MakeExpectedCounterLocationEntry(1, 10) MakeExpectedCounterLocationEntry(1, 11)

                // SPI*_PERF_CSN_BUSY[0..5]
                MakeExpectedCounterLocationEntry(1, 12) MakeExpectedCounterLocationEntry(1, 13) MakeExpectedCounterLocationEntry(1, 14)
                MakeExpectedCounterLocationEntry(1, 15) MakeExpectedCounterLocationEntry(1, 16) MakeExpectedCounterLocationEntry(1, 17)

                // SPI*_PERF_CSN_WAVE[0..5]
                MakeExpectedCounterLocationEntry(1, 18) MakeExpectedCounterLocationEntry(1, 19) MakeExpectedCounterLocationEntry(1, 20)
                MakeExpectedCounterLocationEntry(1, 21) MakeExpectedCounterLocationEntry(1, 22) MakeExpectedCounterLocationEntry(1, 23)

                // CPF_PERF_SEL_CPF_STAT_BUSY
                MakeExpectedCounterLocationEntry(1, 24)
            };
            // clang-format on

            std::map<uint32_t, std::map<uint32_t, GpaCounterResultLocation>> expected_result_locations = {
                {DISCRETE_VSGSBUSY_PUBLIC_DX11_GFX11, expected_locations_vsgsbusy},
                {DISCRETE_PRETESSELLATIONBUSY_PUBLIC_DX11_GFX11, expected_locations_pretessbusy},
                {DISCRETE_POSTTESSELLATIONBUSY_PUBLIC_DX11_GFX11, expected_locations_posttessbusy},
                {DISCRETE_PSBUSY_PUBLIC_DX11_GFX11, expected_location_psbusy},
                {DISCRETE_CSBUSY_PUBLIC_DX11_GFX11, expected_locations_csbusy}};

            VerifyCountersInPass(kGpaApiDirectx11, kDevIdGfx11, counters, expected_hw_counters_per_pass, expected_result_locations);
        }
#pragma endregion
    }
}

static void TestGpuTimeVSBusyVSTimeCountersForDevice(uint32_t device_id)
{
    // Checks that different combinations of GPUTime / VSBusy / VSTime are scheduled correctly regardless of order of inclusion.
    uint32_t gpu_time_index  = 0;
    uint32_t vs_busy_index   = 0;
    uint32_t vs_time_index   = 0;
    uint32_t expected_passes = 0;

    if (kDevIdGfx10 == device_id)
    {
        gpu_time_index  = DISCRETE_GPUTIME_PUBLIC_DX11_GFX10;
        vs_busy_index   = DISCRETE_VSGSBUSY_PUBLIC_DX11_GFX10;
        vs_time_index   = DISCRETE_VSGSTIME_PUBLIC_DX11_GFX10;
        expected_passes = 2;
    }
    else if (kDevIdGfx11 == device_id)
    {
        gpu_time_index  = DISCRETE_GPUTIME_PUBLIC_DX11_GFX11;
        vs_busy_index   = DISCRETE_VSGSBUSY_PUBLIC_DX11_GFX11;
        vs_time_index   = DISCRETE_VSGSTIME_PUBLIC_DX11_GFX11;
        expected_passes = 2;
    }

    std::array<uint32_t, 2> counters_two{};

    // counters to enable (GPUTime, VSBusy)
    counters_two = {gpu_time_index, vs_busy_index};
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx11, device_id, counters_two), expected_passes);

    // counters to enable (VSBusy, GPUTime)
    counters_two = {vs_busy_index, gpu_time_index};
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx11, device_id, counters_two), expected_passes);

    // counters to enable (VSBusy, VSTime)
    counters_two = {vs_busy_index, vs_time_index};
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx11, device_id, counters_two), expected_passes);

    // counters to enable (VSTime, VSBusy)
    counters_two = {vs_time_index, vs_busy_index};
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx11, device_id, counters_two), expected_passes);

    // counters to enable (GPUTime, VSTime)
    counters_two = {gpu_time_index, vs_time_index};
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx11, device_id, counters_two), expected_passes);

    // counters to enable (VSTime, GPUTime)
    counters_two = {vs_time_index, gpu_time_index};
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx11, device_id, counters_two), expected_passes);

    // counters to enable (GPUTime, VSBusy, VSTime)
    std::vector<uint32_t> counters_three;
    counters_three = {gpu_time_index, vs_busy_index, vs_time_index};
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx11, device_id, counters_three), expected_passes);

    // counters to enable (GPUTime, VSTime, VSBusy)
    counters_three = {gpu_time_index, vs_time_index, vs_busy_index};
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx11, device_id, counters_three), expected_passes);

    // counters to enable (VSTime, GPUTime, VSBusy)
    counters_three = {vs_time_index, gpu_time_index, vs_busy_index};
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx11, device_id, counters_three), expected_passes);

    // counters to enable (VSTime, VSBusy, GPUTime)
    counters_three = {vs_time_index, vs_busy_index, gpu_time_index};
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx11, device_id, counters_three), expected_passes);

    // counters to enable (VSBusy, GPUTime, VSTime)
    counters_three = {vs_busy_index, gpu_time_index, vs_time_index};
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx11, device_id, counters_three), expected_passes);

    counters_three = {vs_busy_index, vs_time_index, gpu_time_index};
    // counters to enable (VSBusy, VSTime, GPUTime)
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx11, device_id, counters_three), expected_passes);
}

TEST(CounterDllTests, Dx11Gfx10GpuTimeVsGsBusyVsGsTimeCounters)
{
    TestGpuTimeVSBusyVSTimeCountersForDevice(kDevIdGfx10);
}

TEST(CounterDllTests, Dx11Gfx11GpuTimeVsGsBusyVsGsTimeCounters)
{
    TestGpuTimeVSBusyVSTimeCountersForDevice(kDevIdGfx11);
}

TEST(CounterDllTests, Dx11Gfx10PsBusyCounterResult)
{
    // Test the result of PSBusy, which uses 17 internal counters:
    // SPI*_PERF_PS0_BUSY[0..1]
    // SPI*_PERF_PS0_WAVE[0..1]
    // SPI*_PERF_PS1_BUSY[0..1]
    // SPI*_PERF_PS1_WAVE[0..1]
    // SPI*_PERF_PS2_BUSY[0..1]
    // SPI*_PERF_PS2_WAVE[0..1]
    // SPI*_PERF_PS3_BUSY[0..1]
    // SPI*_PERF_PS3_WAVE[0..1]
    // CPF_PERF_SEL_CPF_STAT_BUSY
    // eqn = (0),0,2,ifnotzero,(0),1,3,ifnotzero,max,(0),4,6,ifnotzero,(0),5,7,ifnotzero,max,(0),8,10,ifnotzero,(0),9,11,ifnotzero,max,(0),12,14,ifnotzero,(0),13,15,ifnotzero,max,max4,16,/,(100),*,(100),min

    // Fabricate some results that will allow us to confirm the PSBusy counter equation evaluation.
    constexpr auto kSampleResults = std::to_array<GpaUInt64>({
        // The values are chosen to pretend there is 1 wave on each PS, and that the PS is busy for 1 cycle.
        // Since all these SPI instances and PS pipes occur in parallel, all of that work takes place in 1 cycle.
        // Overall though, we are setting CPF_PERF_SEL_CPF_STAT_BUSY to indicate 2 cycles.
        // This means that the PS was only busy for 1 out of 2 cycles, or 50% busy.

        1,  // SPI0_PERF_PS0_BUSY
        1,  // SPI1_PERF_PS0_BUSY
        1,  // SPI0_PERF_PS0_WAVE
        1,  // SPI1_PERF_PS0_WAVE
        1,  // SPI0_PERF_PS1_BUSY
        1,  // SPI1_PERF_PS1_BUSY
        1,  // SPI0_PERF_PS1_WAVE
        1,  // SPI1_PERF_PS1_WAVE
        1,  // SPI0_PERF_PS2_BUSY
        1,  // SPI1_PERF_PS2_BUSY
        1,  // SPI0_PERF_PS2_WAVE
        1,  // SPI1_PERF_PS2_WAVE
        1,  // SPI0_PERF_PS3_BUSY
        1,  // SPI1_PERF_PS3_BUSY
        1,  // SPI0_PERF_PS3_WAVE
        1,  // SPI1_PERF_PS3_WAVE
        2   // CPF_PERF_SEL_CPF_STAT_BUSY
    });

    EXPECT_EQ(50.0f, GetCounterCalculation(kGpaApiDirectx11, kDevIdGfx10, "PSBusy", kSampleResults));
}

TEST(CounterDllTests, Dx11EnableAndDisable)
{
    GpaApiType api       = kGpaApiDirectx11;
    uint32_t   device_id = kDevIdGfx10;

    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    auto                   lib_guard                  = LoadAndVerifyCounterLib(&gpa_counter_lib_func_table);

    if (!lib_guard)
    {
        return;
    }

    GpaCounterContextHardwareInfo counter_context_hardware_info = {device_info::kAmdVendorId, device_id, device_info::kRevisionIdAny, nullptr, 0};
    GpaCounterContext             gpa_counter_context           = nullptr;
    GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
        api, kGpaSessionSampleTypeDiscreteCounter, counter_context_hardware_info, kGpaOpenContextDefaultBit, &gpa_counter_context);
    EXPECT_EQ(kGpaStatusOk, gpa_status);

    std::vector<GpaUInt32> enable_counter_list;
    enable_counter_list.push_back(0);

    GpaUInt32 req_pass = 0u;
    gpa_status         = gpa_counter_lib_func_table.GpaCounterLibGetPassCount(
        gpa_counter_context, enable_counter_list.data(), static_cast<GpaUInt32>(enable_counter_list.size()), &req_pass);
    EXPECT_EQ(kGpaStatusOk, gpa_status);
    EXPECT_EQ(1, req_pass);

    enable_counter_list.push_back(1);
    req_pass   = 0u;
    gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetPassCount(
        gpa_counter_context, enable_counter_list.data(), static_cast<GpaUInt32>(enable_counter_list.size()), &req_pass);
    EXPECT_EQ(kGpaStatusOk, gpa_status);
    EXPECT_EQ(2, req_pass);

    enable_counter_list.clear();

    req_pass   = 0u;
    gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetPassCount(
        gpa_counter_context, enable_counter_list.data(), static_cast<GpaUInt32>(enable_counter_list.size()), &req_pass);
    EXPECT_EQ(kGpaStatusErrorInvalidParameter, gpa_status);

    enable_counter_list.push_back(1);
    req_pass   = 0u;
    gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetPassCount(
        gpa_counter_context, enable_counter_list.data(), static_cast<GpaUInt32>(enable_counter_list.size()), &req_pass);
    EXPECT_EQ(kGpaStatusOk, gpa_status);
    EXPECT_EQ(1, req_pass);

    gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
}

TEST(CounterDllTests, Dx12Gfx10MultipleTimingCountersGpa159)
{
    std::vector<uint32_t> counters = {
        DISCRETE_PRETESSELLATIONBUSYCYCLES_PUBLIC_DX12_GFX10,
        DISCRETE_PRETESSELLATIONTIME_PUBLIC_DX12_GFX10,
        DISCRETE_PSBUSYCYCLES_PUBLIC_DX12_GFX10,
        DISCRETE_PSTIME_PUBLIC_DX12_GFX10,
    };

    // Pass: 0  Counters: 13
    std::vector<uint32_t> expected_counters_pass0 = {5580, 5909, 5600, 5929, 5581, 5910, 5601, 5930, 5582, 5911, 5602, 5931, 24};

    // Pass: 1  Counters: 9
    std::vector<uint32_t> expected_counters_pass1 = {5554, 5883, 5561, 5890, 24, 5583, 5912, 5603, 5932};

    // Pass: 2  Counters: 1
    std::vector<uint32_t> expected_counters_pass2 = {59893};

    std::vector<std::vector<uint32_t>> expected_hw_counters_per_pass = {expected_counters_pass0, expected_counters_pass1, expected_counters_pass2};

    // clang-format off
    // Result locations (Pass, Offset)
    // PreTessellationBusyCycles uses 4 hardware counters (5554, 5883, 5561, 5890).
    // Their results can be found in the passes and indices below.
    std::map<uint32_t, GpaCounterResultLocation> expected_locations0
    {
        MakeExpectedCounterLocationEntry(1, 0)
        MakeExpectedCounterLocationEntry(1, 1)
        MakeExpectedCounterLocationEntry(1, 2)
        MakeExpectedCounterLocationEntry(1, 3)
    };

    // PreTessellationTime uses 6 counters (59893, 5554, 5883, 5561, 5890, 24).
    std::map<uint32_t, GpaCounterResultLocation> expected_locations1
    {
        MakeExpectedCounterLocationEntry(2, 0)
        MakeExpectedCounterLocationEntry(1, 0)
        MakeExpectedCounterLocationEntry(1, 1)
        MakeExpectedCounterLocationEntry(1, 2)
        MakeExpectedCounterLocationEntry(1, 3)
        MakeExpectedCounterLocationEntry(1, 4)
    };

    // PSBusyCycles uses 16 counters:
    // 5580,
    // 5909,
    // 5600,
    // 5929,
    // 5581,
    // 5910,
    // 5601,
    // 5930,
    // 5582,
    // 5911,
    // 5602,
    // 5931,
    // 5583,
    // 5912,
    // 5603,
    // 5932

    std::map<uint32_t, GpaCounterResultLocation> expected_locations2
    {
        MakeExpectedCounterLocationEntry(0, 0) MakeExpectedCounterLocationEntry(0, 1)
        MakeExpectedCounterLocationEntry(0, 2) MakeExpectedCounterLocationEntry(0, 3)
        MakeExpectedCounterLocationEntry(0, 4) MakeExpectedCounterLocationEntry(0, 5)
        MakeExpectedCounterLocationEntry(0, 6) MakeExpectedCounterLocationEntry(0, 7)
        MakeExpectedCounterLocationEntry(0, 8) MakeExpectedCounterLocationEntry(0, 9)
        MakeExpectedCounterLocationEntry(0, 10) MakeExpectedCounterLocationEntry(0, 11)
        MakeExpectedCounterLocationEntry(1, 5) MakeExpectedCounterLocationEntry(1, 6)
        MakeExpectedCounterLocationEntry(1, 7) MakeExpectedCounterLocationEntry(1, 8)
    };

    // PSTime uses 18 counters (59893, the same 16 as PSBusyCycles, and 24)
    std::map<uint32_t, GpaCounterResultLocation> expected_locations3
    {
        // 59893
        MakeExpectedCounterLocationEntry(2, 0)

        // The same 16 as PSBusyCycles
        MakeExpectedCounterLocationEntry(0, 0) MakeExpectedCounterLocationEntry(0, 1)
        MakeExpectedCounterLocationEntry(0, 2) MakeExpectedCounterLocationEntry(0, 3)
        MakeExpectedCounterLocationEntry(0, 4) MakeExpectedCounterLocationEntry(0, 5)
        MakeExpectedCounterLocationEntry(0, 6) MakeExpectedCounterLocationEntry(0, 7)
        MakeExpectedCounterLocationEntry(0, 8) MakeExpectedCounterLocationEntry(0, 9)
        MakeExpectedCounterLocationEntry(0, 10) MakeExpectedCounterLocationEntry(0, 11)
        MakeExpectedCounterLocationEntry(1, 5) MakeExpectedCounterLocationEntry(1, 6)
        MakeExpectedCounterLocationEntry(1, 7) MakeExpectedCounterLocationEntry(1, 8)

        // 24
        MakeExpectedCounterLocationEntry(0, 12)
    };
    // clang-format on

    std::map<uint32_t, std::map<uint32_t, GpaCounterResultLocation>> expected_result_locations = {
        {DISCRETE_PRETESSELLATIONBUSYCYCLES_PUBLIC_DX12_GFX10, expected_locations0},
        {DISCRETE_PRETESSELLATIONTIME_PUBLIC_DX12_GFX10, expected_locations1},
        {DISCRETE_PSBUSYCYCLES_PUBLIC_DX12_GFX10, expected_locations2},
        {DISCRETE_PSTIME_PUBLIC_DX12_GFX10, expected_locations3}};

    // This function tests the enabled counters and uses expected_result_locations for self-consistency checks,
    // but it does not yet validate those locations against the library's actual output.
    VerifyCountersInPass(kGpaApiDirectx12, kDevIdGfx10, counters, expected_hw_counters_per_pass, expected_result_locations);
}

TEST(CounterDllTests, Dx12Gfx12VsGsVerticesInVsGsPrimsIn)
{
#pragma region Gfx12
    {
        // VsGsVerticesIn:
        // GE2_SE*_GE_SE_SPI_ESVERT_VALID[0..3]
        // SPI*_PERF_HS_WAVE[0..3]
        //
        // VsGsPrimsIn:
        // GE2_SE*_GE_SE_SPI_GSPRIM_VALID[0..3]
        // SPI*_PERF_HS_WAVE[0..3]

        // clang-format off
        std::vector<uint32_t> counters = {DISCRETE_VSGSVERTICESIN_PUBLIC_DX12_GFX12, DISCRETE_VSGSPRIMSIN_PUBLIC_DX12_GFX12};

        // Pass: 0  Counters: 12
        std::vector<uint32_t> expected_counters_pass0 = {
            103519, 103623, 103727, 103831,  // GE2_SE*_GE_SE_SPI_ESVERT_VALID[0..3]
            29691, 30010, 30329, 30648,      // SPI*_PERF_HS_WAVE[0..3]
            103524, 103628, 103732, 103836,  // GE2_SE*_GE_SE_SPI_GSPRIM_VALID[0..3]
        };

        std::vector<std::vector<uint32_t>> expected_hw_counters_per_pass = {
            expected_counters_pass0,
        };

        std::map<uint32_t, std::map<uint32_t, GpaCounterResultLocation>> expected_result_locations;
        VerifyCountersInPass(kGpaApiDirectx12, kDevIdGfx12_0_1, counters, expected_hw_counters_per_pass, expected_result_locations);
    }
#pragma endregion
}

TEST(CounterDllTests, Dx12SingleCounterRequiresOnePassGfx115)
{
    // Any single derived counter should require at least 1 pass (and most simple ones exactly 1).
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    auto                   lib_guard                  = LoadAndVerifyCounterLib(&gpa_counter_lib_func_table);

    if (!lib_guard)
    {
        return;
    }

    GpaCounterContextHardwareInfo counter_context_hardware_info = {
        device_info::kAmdVendorId, kDevIdGfx11_5_0, device_info::kRevisionIdAny, nullptr, 0};
    GpaCounterContext gpa_counter_context = nullptr;
    GpaStatus         gpa_status          = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
        kGpaApiDirectx12, kGpaSessionSampleTypeDiscreteCounter, counter_context_hardware_info, kGpaOpenContextDefaultBit, &gpa_counter_context);
    EXPECT_EQ(kGpaStatusOk, gpa_status);

    GpaUInt32 counter_count = 0;
    gpa_status              = gpa_counter_lib_func_table.GpaCounterLibGetNumCounters(gpa_counter_context, &counter_count);
    EXPECT_EQ(kGpaStatusOk, gpa_status);

    for (GpaUInt32 i = 0; i < counter_count; ++i)
    {
        GpaUInt32 req_pass = 0u;
        gpa_status         = gpa_counter_lib_func_table.GpaCounterLibGetPassCount(gpa_counter_context, &i, 1, &req_pass);
        EXPECT_EQ(kGpaStatusOk, gpa_status) << "Failed to get pass count for counter index " << i;
        EXPECT_GE(req_pass, 1u) << "Counter index " << i << " requires 0 passes, which is unexpected.";
    }

    gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
}

TEST(CounterDllTests, Dx12GpuTimeAloneRequiresOnePassGfx115)
{
    auto constexpr kCounters = std::to_array<uint32_t>({DISCRETE_GPUTIME_PUBLIC_DX12_GFX115});
    EXPECT_EQ(GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx12, kDevIdGfx11_5_0, kCounters), 1u);
}

TEST(CounterDllTests, Dx12GpuTimeWithOtherCountersRequiresExtraPassGfx115)
{
    auto constexpr kCountersNoGpuTime   = std::to_array<uint32_t>({DISCRETE_CSBUSY_PUBLIC_DX12_GFX115});
    auto constexpr kCountersWithGpuTime = std::to_array<uint32_t>({DISCRETE_GPUTIME_PUBLIC_DX12_GFX115, DISCRETE_CSBUSY_PUBLIC_DX12_GFX115});

    const uint32_t passes_without_gpu_time = GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx12, kDevIdGfx11_5_0, kCountersNoGpuTime);
    const uint32_t passes_with_gpu_time    = GetPassCount<kGpaSessionSampleTypeDiscreteCounter>(kGpaApiDirectx12, kDevIdGfx11_5_0, kCountersWithGpuTime);

    EXPECT_GT(passes_with_gpu_time, passes_without_gpu_time);
}

#endif
