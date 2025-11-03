//==============================================================================
// Copyright (c) 2012-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Unit Tests for VK Counter Generator.
//==============================================================================

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_counter_generator/gpa_counter.h"

#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_vk_gfx10.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_vk_gfx103.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_vk_gfx11.h"
#include "auto_generated/gpu_perf_api_unit_tests/counters/public_derived_counters_vk_gfx12.h"

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_vk_gfx10.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_vk_gfx103.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_vk_gfx11.h"
#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_vk_gfx12.h"

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
        public_counters         = kVkGfx10PublicCounters;
        public_counter_count    = kVkGfx10PublicCounterCount;
        hardware_counter_groups = counter_vk_gfx10::kVkCounterGroupArrayGfx10;
        break;

    case kGpaHwGenerationGfx103:
        public_counters         = kVkGfx103PublicCounters;
        public_counter_count    = kVkGfx103PublicCounterCount;
        hardware_counter_groups = counter_vk_gfx103::kVkCounterGroupArrayGfx103;
        break;

    case kGpaHwGenerationGfx11:
        public_counters         = kVkGfx11PublicCounters;
        public_counter_count    = kVkGfx11PublicCounterCount;
        hardware_counter_groups = counter_vk_gfx11::kVkCounterGroupArrayGfx11;
        break;

    case kGpaHwGenerationGfx12:
        public_counters         = kVkGfx12PublicCounters;
        public_counter_count    = kVkGfx12PublicCounterCount;
        hardware_counter_groups = counter_vk_gfx12::kVkCounterGroupArrayGfx12;
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
    const GpaCounterDesc* public_counters      = nullptr;
    size_t                public_counter_count = 0;

    switch (generation)
    {
    case kGpaHwGenerationGfx10:
        public_counters      = kVkGfx10PublicCounters;
        public_counter_count = kVkGfx10PublicCounterCount;
        break;

    case kGpaHwGenerationGfx103:
        public_counters      = kVkGfx103PublicCounters;
        public_counter_count = kVkGfx103PublicCounterCount;
        break;

    case kGpaHwGenerationGfx11:
        public_counters      = kVkGfx11PublicCounters;
        public_counter_count = kVkGfx11PublicCounterCount;
        break;

    case kGpaHwGenerationGfx12:
        public_counters      = kVkGfx12PublicCounters;
        public_counter_count = kVkGfx12PublicCounterCount;
        break;

    default:
        assert(!"Unrecognized hardware generation in GetExpectedPublicCounters");
        break;
    }

    return gpa_array_view<GpaCounterDesc>(public_counters, public_counter_count);
}

TEST(CounterDllTests, VkUnsupportedHardwareGenerations)
{
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationNone);
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationNvidia);
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationIntel);
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationGfx6);
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationGfx7);
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationGfx8);
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationGfx9);
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationCdna);
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationCdna2);
    VerifyHardwareNotSupported(kGpaApiVulkan, kGpaHwGenerationCdna3);
}

TEST(CounterDllTests, VkVerifyInvalidOpenContextParameters)
{
    VerifyInvalidOpenContextParameters(kGpaApiVulkan, kDevIdGfx11);
}

#ifdef _WIN32
// Test the Vulkan derived counter blocks.
TEST(CounterDllTests, VulkanDerivedCounterBlocks)
{
    VerifyDerivedCounterCount(kGpaApiVulkan, kGpaHwGenerationGfx10, GetExpectedPublicCounters(kGpaHwGenerationGfx10));
    VerifyDerivedCounterCount(kGpaApiVulkan, kGpaHwGenerationGfx103, GetExpectedPublicCounters(kGpaHwGenerationGfx103));
    VerifyDerivedCounterCount(kGpaApiVulkan, kGpaHwGenerationGfx11, GetExpectedPublicCounters(kGpaHwGenerationGfx11));
    VerifyDerivedCounterCount(kGpaApiVulkan, kGpaHwGenerationGfx12, GetExpectedPublicCounters(kGpaHwGenerationGfx12));
}
#endif

// Test the VK counter names on all supported hardware.
TEST(CounterDllTests, VkCounterNamesByDeviceId)
{
    for (auto const& device_id : kUnsupportedDeviceIds)
    {
        VerifyHardwareNotSupported(kGpaApiVulkan, device_id);
    }

    std::vector<const char*> derived_counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kDevIdGfx10, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kDevIdGfx10_3, derived_counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kDevIdGfx11, derived_counter_names, hardware_counter_names);

    // The variant hardware can only have the derived counter names verified.
    // GetExpectedCountersForGeneration() method in our tests is not thorough enough to create
    // the expected list of hardware counters for each variant.
    std::vector<const char*> empty_list_to_skip_tests;
    VerifyCounterNames(kGpaApiVulkan, kDevIdGfx11_0_3, derived_counter_names, empty_list_to_skip_tests);
    VerifyCounterNames(kGpaApiVulkan, kDevIdGfx11_0_3B, derived_counter_names, empty_list_to_skip_tests);
    VerifyCounterNames(kGpaApiVulkan, kDevIdGfx11_5_0, derived_counter_names, empty_list_to_skip_tests);
    VerifyCounterNames(kGpaApiVulkan, kDevIdGfx11_5_3, derived_counter_names, empty_list_to_skip_tests);

    GetExpectedCountersForGeneration(kGpaHwGenerationGfx12, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kDevIdGfx12_0_0, derived_counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kDevIdGfx12_0_1, derived_counter_names, hardware_counter_names);
}

TEST(CounterDllTests, VkCounterNamesGfx10)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, VkCounterNamesGfx103)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, VkCounterNamesGfx11)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, VkCounterNamesGfx12)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx12, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx12, counter_names, hardware_counter_names);
}

// Test the VK counter names on all generations.
TEST(CounterDllTests, VkCounterNamesByGeneration)
{
    std::vector<const char*> counter_names;
    std::vector<const char*> hardware_counter_names;
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx10, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx103, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx11, counter_names, hardware_counter_names);
    GetExpectedCountersForGeneration(kGpaHwGenerationGfx12, counter_names, hardware_counter_names);
    VerifyCounterNames(kGpaApiVulkan, kGpaHwGenerationGfx12, counter_names, hardware_counter_names);
}

TEST(CounterDllTests, VkOpenCounterContext)
{
    VerifyOpenCounterContext(kGpaApiVulkan, kGpaHwGenerationGfx10);
    VerifyOpenCounterContext(kGpaApiVulkan, kGpaHwGenerationGfx103);
    VerifyOpenCounterContext(kGpaApiVulkan, kGpaHwGenerationGfx11);
    VerifyOpenCounterContext(kGpaApiVulkan, kGpaHwGenerationGfx12);
}

#ifdef _WIN32
TEST(CounterDllTests, VkCounterLibTestGfx10)
{
    VerifyCounterLibInterface(kGpaApiVulkan, kDevIdGfx10, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiVulkan, kDevIdGfx10, REVISION_ID_ANY);
}

TEST(CounterDllTests, VkCounterLibTestGfx103)
{
    VerifyCounterLibInterface(kGpaApiVulkan, kDevIdGfx10_3, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiVulkan, kDevIdGfx10_3, REVISION_ID_ANY);
}

TEST(CounterDllTests, VkCounterLibTestGfx11)
{
    VerifyCounterLibInterface(kGpaApiVulkan, kDevIdGfx11, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiVulkan, kDevIdGfx11, REVISION_ID_ANY);
}

TEST(CounterDllTests, VkCounterLibTestGfx1103)
{
    VerifyCounterLibInterface(kGpaApiVulkan, kDevIdGfx11_0_3, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiVulkan, kDevIdGfx11_0_3, REVISION_ID_ANY);
}

TEST(CounterDllTests, VkCounterLibTestGfx1103B)
{
    VerifyCounterLibInterface(kGpaApiVulkan, kDevIdGfx11_0_3B, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiVulkan, kDevIdGfx11_0_3B, REVISION_ID_ANY);
}

TEST(CounterDllTests, VkCounterLibTestGfx1150)
{
    VerifyCounterLibInterface(kGpaApiVulkan, kDevIdGfx11_5_0, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiVulkan, kDevIdGfx11_5_0, REVISION_ID_ANY);
}

TEST(CounterDllTests, VkCounterLibTestGfx1153)
{
    VerifyCounterLibInterface(kGpaApiVulkan, kDevIdGfx11_5_3, REVISION_ID_ANY);
    VerifyCounterByPassCounterLibEntry(kGpaApiVulkan, kDevIdGfx11_5_3, REVISION_ID_ANY);
}

#endif

TEST(HardwareCounterTests, VkGfx1034SqSqcPerfSelLdsBankConflict)
{
    LibHandle              handle                     = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    GpaCounterContext      gpa_counter_context        = nullptr;
    if (LoadAndVerifyCounterLib(&handle, &gpa_counter_lib_func_table))
    {
        GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, kDevIdGfx10_3_4, REVISION_ID_ANY, nullptr, 0};
        GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
            kGpaApiVulkan, kGpaSessionSampleTypeDiscreteCounter, counter_context_hardware_info, kGpaOpenContextEnableHardwareCountersBit, &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        // The counter information that corresponds to SQ0_SQC_PERF_SEL_LDS_BANK_CONFLICT.
        GpaCounterParam param;
        param.is_derived_counter                   = false;
        param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockSq;
        param.gpa_hw_counter.gpa_hw_block_instance = 0;
        param.gpa_hw_counter.gpa_hw_block_event_id = 285;
        param.gpa_hw_counter.gpa_shader_mask       = kGpaShaderMaskAll;
        GpaUInt32 index                            = 0;
        gpa_status                                 = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param, &index);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        const char* counter_name = nullptr;
        gpa_status               = gpa_counter_lib_func_table.GpaCounterLibGetCounterName(gpa_counter_context, index, &counter_name);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        EXPECT_STREQ("SQ0_SQC_PERF_SEL_LDS_BANK_CONFLICT", counter_name);

        // Now make sure that getting the counter information for that index properly returns the same counter information that was supplied above.
        const GpaCounterInfo* counter_info = nullptr;
        gpa_status                         = gpa_counter_lib_func_table.GpaCounterLibGetCounterInfo(gpa_counter_context, index, &counter_info);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        EXPECT_EQ(param.is_derived_counter, counter_info->is_derived_counter);
        EXPECT_EQ(param.gpa_hw_counter.gpa_hw_block, counter_info->gpa_hw_counter->gpa_hw_block);
        EXPECT_EQ(param.gpa_hw_counter.gpa_hw_block_instance, counter_info->gpa_hw_counter->gpa_hw_block_instance);
        EXPECT_EQ(param.gpa_hw_counter.gpa_hw_block_event_id, counter_info->gpa_hw_counter->gpa_hw_block_event_id);
        EXPECT_EQ(param.gpa_hw_counter.gpa_shader_mask, counter_info->gpa_hw_counter->gpa_shader_mask);

        gpa_status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        UnloadLib(handle);
    }
}

TEST(HardwareCounterTests, VkGfx10Gl2cPerfSelMiss)
{
    LibHandle              handle                     = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    GpaCounterContext      gpa_counter_context        = nullptr;
    if (LoadAndVerifyCounterLib(&handle, &gpa_counter_lib_func_table))
    {
        GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, kDevIdGfx10, REVISION_ID_ANY, nullptr, 0};
        GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
            kGpaApiVulkan, kGpaSessionSampleTypeDiscreteCounter, counter_context_hardware_info, kGpaOpenContextEnableHardwareCountersBit, &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        // The counter information that corresponds to GL2C0_PERF_SEL_MISS (which is at index 35 on Gfx10).
        GpaCounterParam param;
        param.is_derived_counter                   = false;
        param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockGl2C;
        param.gpa_hw_counter.gpa_hw_block_instance = 0;
        param.gpa_hw_counter.gpa_hw_block_event_id = 35;
        param.gpa_hw_counter.gpa_shader_mask       = kGpaShaderMaskAll;
        GpaUInt32 index                            = 0;
        gpa_status                                 = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param, &index);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        // Make sure the index points back to the same counter name.
        const char* counter_name = nullptr;
        gpa_status               = gpa_counter_lib_func_table.GpaCounterLibGetCounterName(gpa_counter_context, index, &counter_name);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        EXPECT_STREQ("GL2C0_PERF_SEL_MISS", counter_name);

        // The counter should also be queriable by name as a derived counter, and point to the same index.
        GpaCounterParam param_by_name;
        param_by_name.is_derived_counter   = true;
        param_by_name.derived_counter_name = "GL2C0_PERF_SEL_MISS";
        GpaUInt32 index_by_name            = 0;
        gpa_status                         = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param_by_name, &index_by_name);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        EXPECT_EQ(index, index_by_name);

        // Now make sure that getting the counter information for that index properly returns the same counter information that was supplied above.
        const GpaCounterInfo* counter_info = nullptr;
        gpa_status                         = gpa_counter_lib_func_table.GpaCounterLibGetCounterInfo(gpa_counter_context, index, &counter_info);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        EXPECT_EQ(param.is_derived_counter, counter_info->is_derived_counter);
        EXPECT_EQ(param.gpa_hw_counter.gpa_hw_block, counter_info->gpa_hw_counter->gpa_hw_block);
        EXPECT_EQ(param.gpa_hw_counter.gpa_hw_block_instance, counter_info->gpa_hw_counter->gpa_hw_block_instance);
        EXPECT_EQ(param.gpa_hw_counter.gpa_hw_block_event_id, counter_info->gpa_hw_counter->gpa_hw_block_event_id);
        EXPECT_EQ(param.gpa_hw_counter.gpa_shader_mask, counter_info->gpa_hw_counter->gpa_shader_mask);

        gpa_status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        UnloadLib(handle);
    }
}

TEST(HardwareCounterTests, VkGfx103Gl2cPerfSelMiss)
{
    LibHandle              handle                     = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    GpaCounterContext      gpa_counter_context        = nullptr;
    if (LoadAndVerifyCounterLib(&handle, &gpa_counter_lib_func_table))
    {
        GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, kDevIdGfx10_3, REVISION_ID_ANY, nullptr, 0};
        GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
            kGpaApiVulkan, kGpaSessionSampleTypeDiscreteCounter, counter_context_hardware_info, kGpaOpenContextEnableHardwareCountersBit, &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        // The counter information that corresponds to GL2C0_PERF_SEL_MISS (which is at index 43 on Gfx10_3).
        GpaCounterParam param;
        param.is_derived_counter                   = false;
        param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockGl2C;
        param.gpa_hw_counter.gpa_hw_block_instance = 0;
        param.gpa_hw_counter.gpa_hw_block_event_id = 43;
        param.gpa_hw_counter.gpa_shader_mask       = kGpaShaderMaskAll;
        GpaUInt32 index                            = 0;
        gpa_status                                 = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param, &index);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        // Make sure the index points back to the same counter name.
        const char* counter_name = nullptr;
        gpa_status               = gpa_counter_lib_func_table.GpaCounterLibGetCounterName(gpa_counter_context, index, &counter_name);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        EXPECT_STREQ("GL2C0_PERF_SEL_MISS", counter_name);

        // The counter should also be queriable by name as a derived counter, and point to the same index.
        GpaCounterParam param_by_name;
        param_by_name.is_derived_counter   = true;
        param_by_name.derived_counter_name = "GL2C0_PERF_SEL_MISS";
        GpaUInt32 index_by_name            = 0;
        gpa_status                         = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param_by_name, &index_by_name);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        EXPECT_EQ(index, index_by_name);

        // Now make sure that getting the counter information for that index properly returns the same counter information that was supplied above.
        const GpaCounterInfo* counter_info = nullptr;
        gpa_status                         = gpa_counter_lib_func_table.GpaCounterLibGetCounterInfo(gpa_counter_context, index, &counter_info);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        EXPECT_EQ(param.is_derived_counter, counter_info->is_derived_counter);
        EXPECT_EQ(param.gpa_hw_counter.gpa_hw_block, counter_info->gpa_hw_counter->gpa_hw_block);
        EXPECT_EQ(param.gpa_hw_counter.gpa_hw_block_instance, counter_info->gpa_hw_counter->gpa_hw_block_instance);
        EXPECT_EQ(param.gpa_hw_counter.gpa_hw_block_event_id, counter_info->gpa_hw_counter->gpa_hw_block_event_id);
        EXPECT_EQ(param.gpa_hw_counter.gpa_shader_mask, counter_info->gpa_hw_counter->gpa_shader_mask);

        gpa_status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        UnloadLib(handle);
    }
}

TEST(HardwareCounterTests, VkGfx1031Gl2cPerfSelMiss)
{
    LibHandle              handle                     = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    GpaCounterContext      gpa_counter_context        = nullptr;
    if (LoadAndVerifyCounterLib(&handle, &gpa_counter_lib_func_table))
    {
        GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, kDevIdGfx10_3_1, REVISION_ID_ANY, nullptr, 0};
        GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
            kGpaApiVulkan, kGpaSessionSampleTypeDiscreteCounter, counter_context_hardware_info, kGpaOpenContextEnableHardwareCountersBit, &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        // The counter information that corresponds to GL2C0_PERF_SEL_MISS (which is at index 43 on Gfx10_3_1).
        GpaCounterParam param;
        param.is_derived_counter                   = false;
        param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockGl2C;
        param.gpa_hw_counter.gpa_hw_block_instance = 0;
        param.gpa_hw_counter.gpa_hw_block_event_id = 43;
        param.gpa_hw_counter.gpa_shader_mask       = kGpaShaderMaskAll;
        GpaUInt32 index                            = 0;
        gpa_status                                 = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param, &index);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        // Make sure the index points back to the same counter name.
        const char* counter_name = nullptr;
        gpa_status               = gpa_counter_lib_func_table.GpaCounterLibGetCounterName(gpa_counter_context, index, &counter_name);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        EXPECT_STREQ("GL2C0_PERF_SEL_MISS", counter_name);

        // The counter should also be queriable by name as a derived counter, and point to the same index.
        GpaCounterParam param_by_name;
        param_by_name.is_derived_counter   = true;
        param_by_name.derived_counter_name = "GL2C0_PERF_SEL_MISS";
        GpaUInt32 index_by_name            = 0;
        gpa_status                         = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param_by_name, &index_by_name);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        EXPECT_EQ(index, index_by_name);

        // Now make sure that getting the counter information for that index properly returns the same counter information that was supplied above.
        const GpaCounterInfo* counter_info = nullptr;
        gpa_status                         = gpa_counter_lib_func_table.GpaCounterLibGetCounterInfo(gpa_counter_context, index, &counter_info);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        EXPECT_EQ(param.is_derived_counter, counter_info->is_derived_counter);
        EXPECT_EQ(param.gpa_hw_counter.gpa_hw_block, counter_info->gpa_hw_counter->gpa_hw_block);
        EXPECT_EQ(param.gpa_hw_counter.gpa_hw_block_instance, counter_info->gpa_hw_counter->gpa_hw_block_instance);
        EXPECT_EQ(param.gpa_hw_counter.gpa_hw_block_event_id, counter_info->gpa_hw_counter->gpa_hw_block_event_id);
        EXPECT_EQ(param.gpa_hw_counter.gpa_shader_mask, counter_info->gpa_hw_counter->gpa_shader_mask);

        gpa_status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        UnloadLib(handle);
    }
}

TEST(HardwareCounterTests, VkGfx11Gl2cPerfSelMiss)
{
    LibHandle              handle                     = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    GpaCounterContext      gpa_counter_context        = nullptr;
    if (LoadAndVerifyCounterLib(&handle, &gpa_counter_lib_func_table))
    {
        GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, kDevIdGfx11, REVISION_ID_ANY, nullptr, 0};
        GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
            kGpaApiVulkan, kGpaSessionSampleTypeDiscreteCounter, counter_context_hardware_info, kGpaOpenContextEnableHardwareCountersBit, &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        // The counter information that corresponds to GL2C0_PERF_SEL_MISS (which is at index 43 on Gfx11).
        GpaCounterParam param;
        param.is_derived_counter                   = false;
        param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockGl2C;
        param.gpa_hw_counter.gpa_hw_block_instance = 0;
        param.gpa_hw_counter.gpa_hw_block_event_id = 43;
        param.gpa_hw_counter.gpa_shader_mask       = kGpaShaderMaskAll;
        GpaUInt32 index                            = 0;
        gpa_status                                 = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param, &index);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        // Make sure the index points back to the same counter name.
        const char* counter_name = nullptr;
        gpa_status               = gpa_counter_lib_func_table.GpaCounterLibGetCounterName(gpa_counter_context, index, &counter_name);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        EXPECT_STREQ("GL2C0_PERF_SEL_MISS", counter_name);

        // The counter should also be queriable by name as a derived counter, and point to the same index.
        GpaCounterParam param_by_name;
        param_by_name.is_derived_counter   = true;
        param_by_name.derived_counter_name = "GL2C0_PERF_SEL_MISS";
        GpaUInt32 index_by_name            = 0;
        gpa_status                         = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param_by_name, &index_by_name);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        EXPECT_EQ(index, index_by_name);

        // Now make sure that getting the counter information for that index properly returns the same counter information that was supplied above.
        const GpaCounterInfo* counter_info = nullptr;
        gpa_status                         = gpa_counter_lib_func_table.GpaCounterLibGetCounterInfo(gpa_counter_context, index, &counter_info);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        EXPECT_EQ(param.is_derived_counter, counter_info->is_derived_counter);
        EXPECT_EQ(param.gpa_hw_counter.gpa_hw_block, counter_info->gpa_hw_counter->gpa_hw_block);
        EXPECT_EQ(param.gpa_hw_counter.gpa_hw_block_instance, counter_info->gpa_hw_counter->gpa_hw_block_instance);
        EXPECT_EQ(param.gpa_hw_counter.gpa_hw_block_event_id, counter_info->gpa_hw_counter->gpa_hw_block_event_id);
        EXPECT_EQ(param.gpa_hw_counter.gpa_shader_mask, counter_info->gpa_hw_counter->gpa_shader_mask);

        gpa_status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        UnloadLib(handle);
    }
}

TEST(HardwareCounterTests, VkGfx1103Gl2cPerfSelMiss)
{
    LibHandle              handle                     = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    GpaCounterContext      gpa_counter_context        = nullptr;
    if (LoadAndVerifyCounterLib(&handle, &gpa_counter_lib_func_table))
    {
        GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, kDevIdGfx11_0_3, REVISION_ID_ANY, nullptr, 0};
        GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
            kGpaApiVulkan, kGpaSessionSampleTypeDiscreteCounter, counter_context_hardware_info, kGpaOpenContextEnableHardwareCountersBit, &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        // The counter information that corresponds to GL2C0_PERF_SEL_MISS (which is at index 43 on Gfx11_0_3).
        GpaCounterParam param;
        param.is_derived_counter                   = false;
        param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockGl2C;
        param.gpa_hw_counter.gpa_hw_block_instance = 0;
        param.gpa_hw_counter.gpa_hw_block_event_id = 43;
        param.gpa_hw_counter.gpa_shader_mask       = kGpaShaderMaskAll;
        GpaUInt32 index                            = 0;
        gpa_status                                 = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param, &index);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        // Make sure the index points back to the same counter name.
        const char* counter_name = nullptr;
        gpa_status               = gpa_counter_lib_func_table.GpaCounterLibGetCounterName(gpa_counter_context, index, &counter_name);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        EXPECT_STREQ("GL2C0_PERF_SEL_MISS", counter_name);

        // The counter should also be queriable by name as a derived counter, and point to the same index.
        GpaCounterParam param_by_name;
        param_by_name.is_derived_counter   = true;
        param_by_name.derived_counter_name = "GL2C0_PERF_SEL_MISS";
        GpaUInt32 index_by_name            = 0;
        gpa_status                         = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param_by_name, &index_by_name);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        EXPECT_EQ(index, index_by_name);

        // Now make sure that getting the counter information for that index properly returns the same counter information that was supplied above.
        const GpaCounterInfo* counter_info = nullptr;
        gpa_status                         = gpa_counter_lib_func_table.GpaCounterLibGetCounterInfo(gpa_counter_context, index, &counter_info);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        EXPECT_EQ(param.is_derived_counter, counter_info->is_derived_counter);
        EXPECT_EQ(param.gpa_hw_counter.gpa_hw_block, counter_info->gpa_hw_counter->gpa_hw_block);
        EXPECT_EQ(param.gpa_hw_counter.gpa_hw_block_instance, counter_info->gpa_hw_counter->gpa_hw_block_instance);
        EXPECT_EQ(param.gpa_hw_counter.gpa_hw_block_event_id, counter_info->gpa_hw_counter->gpa_hw_block_event_id);
        EXPECT_EQ(param.gpa_hw_counter.gpa_shader_mask, counter_info->gpa_hw_counter->gpa_shader_mask);

        gpa_status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        UnloadLib(handle);
    }
}

TEST(CounterDllTests, VkCounterFormulaTest)
{
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx10));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx103));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx11));
    VerifyCounterFormula(GetExpectedPublicCounters(kGpaHwGenerationGfx12));
}

TEST(GpaCounterLibGetSupportedSampleTypes, Vulkan)
{
    VerifySupportedSampleTypes(kGpaApiVulkan);
}

TEST(GpaCounterLibGetSupportedSampleTypes, InvalidParameters)
{
    LibHandle              handle                     = {};
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    // The API is arbitrary for this test.
    constexpr GpaApiType api = kGpaApiVulkan;

    if (LoadAndVerifyCounterLib(&handle, &gpa_counter_lib_func_table))
    {
        GpaStatus                  status                = kGpaStatusOk;
        GpaSupportedSampleTypeInfo info                  = {};
        info.device_id                                   = kDevIdGfx12_0_0;
        info.revision_id                                 = REVISION_ID_ANY;
        info.vendor_id                                   = kAmdVendorId;
        info.driver_info.driver_type                     = kIgnoreDriver;
        GpaContextSampleTypeFlags supported_sample_types = {};

        // Invalid API.
        {
            status = gpa_counter_lib_func_table.GpaCounterLibGetSupportedSampleTypes(kGpaApiNoSupport, &info, &supported_sample_types);
            EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
            status = gpa_counter_lib_func_table.GpaCounterLibGetSupportedSampleTypes(kGpaApiLast, &info, &supported_sample_types);
            EXPECT_EQ(kGpaStatusErrorApiNotSupported, status);
        }

        // Check for nullptr.
        {
            status = gpa_counter_lib_func_table.GpaCounterLibGetSupportedSampleTypes(api, nullptr, &supported_sample_types);
            EXPECT_EQ(kGpaStatusErrorNullPointer, status);
            status = gpa_counter_lib_func_table.GpaCounterLibGetSupportedSampleTypes(api, &info, nullptr);
            EXPECT_EQ(kGpaStatusErrorNullPointer, status);
        }

        // Invalid HW.
        {
            // Invalid device id.
            info.device_id = 0;

            status = gpa_counter_lib_func_table.GpaCounterLibGetSupportedSampleTypes(api, &info, &supported_sample_types);
            EXPECT_EQ(kGpaStatusErrorHardwareNotSupported, status);

            info.device_id = kDevIdGfx12_0_0;

            // Valid device_id but invalid revision id
            info.device_id   = kDevIdGfx11_5_0;
            info.revision_id = 0;

            status = gpa_counter_lib_func_table.GpaCounterLibGetSupportedSampleTypes(api, &info, &supported_sample_types);
            EXPECT_EQ(kGpaStatusErrorHardwareNotSupported, status);

            info.revision_id = REVISION_ID_ANY;

            // Invalid vendor id.
            info.vendor_id = 0;

            status = gpa_counter_lib_func_table.GpaCounterLibGetSupportedSampleTypes(api, &info, &supported_sample_types);
            EXPECT_EQ(kGpaStatusErrorHardwareNotSupported, status);

            info.vendor_id = kAmdVendorId;
        }

        // Invalid driver information.
        {
            // This test will fail if a new driver type is added. Just increment the arbitrary value.
            info.driver_info.driver_type = static_cast<GpaDriverType>(2);

            status = gpa_counter_lib_func_table.GpaCounterLibGetSupportedSampleTypes(api, &info, &supported_sample_types);
            EXPECT_EQ(kGpaStatusErrorInvalidParameter, status);

            info.driver_info.driver_type = kIgnoreDriver;
        }

        UnloadLib(handle);
    }
}

// The main intent of this test is to ensure functionality RGP/RDP is relying on works.
TEST(GpaCounterLibGetCounterIndex, RadeonToolsSanityCheck)
{
    LibHandle              handle                     = {};
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};
    GpaCounterContext      gpa_counter_context        = {};
    if (LoadAndVerifyCounterLib(&handle, &gpa_counter_lib_func_table))
    {
        GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, kDevIdGfx11, REVISION_ID_ANY, nullptr, 0};
        GpaStatus                     status                        = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
            kGpaApiVulkan, kGpaSessionSampleTypeDiscreteCounter, counter_context_hardware_info, kGpaOpenContextDefaultBit, &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, status);

        // The following counters are supported as a discrete/spm counters which is why RGP/RDP can utilize it for SPM purposes.
        // Since Vulkan doesn't currently support SPM.
        constexpr std::array kRgpCounters = {
            "InstCacheHit",
            "ScalarCacheHit",
            "L0CacheHit",
            "L1CacheHit",  // NOTE: GFX12 doesn't have an L1 Cache. So for this test we use GFX11.
            "L2CacheHit",
        };

        if (status == kGpaStatusOk)
        {
            // If we can get the counter index then other functionality like GpaCounterLibComputeDerivedCounterResult and
            // GpaCounterlibComputeDerivedSpmCounterResults will also just work.
            for (auto const& counter : kRgpCounters)
            {
                uint32_t        index      = {};
                GpaCounterParam param      = {};
                param.is_derived_counter   = true;
                param.derived_counter_name = counter;
                status                     = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &param, &index);
                EXPECT_EQ(kGpaStatusOk, status) << counter << " not found!";
            }
        }

        status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, status);

        UnloadLib(handle);
    }
}
