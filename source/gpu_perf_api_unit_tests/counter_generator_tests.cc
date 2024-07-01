//==============================================================================
// Copyright (c) 2012-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Helper functions for Counter Generator Unit Tests.
//==============================================================================

#include "gpu_perf_api_unit_tests/counter_generator_tests.h"

#include <algorithm>
#include <map>

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_common/gpa_hw_info.h"
#include "gpu_perf_api_counter_generator/gpa_derived_counter_evaluator.hpp"
#include "gpu_perf_api_counter_generator/gpa_split_counters_interfaces.h"

#ifdef _WIN32
const char* kCountersLibName = "GPUPerfAPICounters" AMDT_PLATFORM_SUFFIX AMDT_DEBUG_SUFFIX AMDT_BUILD_SUFFIX ".dll";
#else
const char* kCountersLibName = "libGPUPerfAPICounters" AMDT_PLATFORM_SUFFIX AMDT_DEBUG_SUFFIX AMDT_BUILD_SUFFIX ".so";
#endif

LibHandle LoadLib(const char* lib_name)
{
    LibHandle lib_handle = nullptr;
    if (lib_name != NULL && strlen(lib_name) > 0)
    {
#ifdef _WIN32
        // raise an error if the library is already loaded
        lib_handle = GetModuleHandleA(lib_name);
        EXPECT_TRUE(lib_handle == nullptr);
        lib_handle = LoadLibraryA(lib_name);
#else
        // raise an error if the library is already loaded
        lib_handle = dlopen(lib_name, RTLD_NOLOAD);
        EXPECT_TRUE(lib_handle == nullptr);
        lib_handle = dlopen(lib_name, RTLD_NOW);
#endif
    }
    EXPECT_TRUE(lib_handle != nullptr);
    return lib_handle;
}

bool LoadAndVerifyCounterLib(LibHandle* lib_handle, void* fn_table)
{
    GpaStatus gpa_status = kGpaStatusErrorLibLoadFailed;

    *lib_handle = LoadLib(kCountersLibName);
    EXPECT_NE((LibHandle) nullptr, *lib_handle);

    if (*lib_handle != nullptr)
    {
        GpaCounterLibGetFuncTablePtrType get_func_table_ptr =
            reinterpret_cast<GpaCounterLibGetFuncTablePtrType>(GetEntryPoint(*lib_handle, "GpaCounterLibGetFuncTable"));
        EXPECT_NE((GpaCounterLibGetFuncTablePtrType) nullptr, get_func_table_ptr);

        if (get_func_table_ptr != nullptr)
        {
            gpa_status = get_func_table_ptr(fn_table);
            EXPECT_EQ(kGpaStatusOk, gpa_status);
        }
    }

    return kGpaStatusOk == gpa_status;
}

// Give meaningful names to event IDs being used in several tests.
const GpaUInt32 kSqPerfSelWaves  = 4;
const GpaUInt32 kGl1cPerfSelReq  = 14;
const GpaUInt32 kGl2cPerfSelMiss = 43;

static std::map<GpaHwGeneration, unsigned int> generation_device_map = {{kGpaHwGenerationNone, 0},
                                                                        {kGpaHwGenerationNvidia, 0},
                                                                        {kGpaHwGenerationIntel, 0},
                                                                        {kGpaHwGenerationGfx6, kDevIdSI},
                                                                        {kGpaHwGenerationGfx7, kDevIdCI},
                                                                        {kGpaHwGenerationGfx8, kDevIdGfx8},
                                                                        {kGpaHwGenerationGfx9, kDevIdGfx9},
                                                                        {kGpaHwGenerationGfx10, kDevIdGfx10},
                                                                        {kGpaHwGenerationGfx103, kDevIdGfx10_3},
                                                                        {kGpaHwGenerationGfx11, kDevIdGfx11},
                                                                        {kGpaHwGenerationCdna, 0},
                                                                        {kGpaHwGenerationCdna2, 0},
                                                                        {kGpaHwGenerationCdna3, 0}};

void UnloadLib(LibHandle lib_handle)
{
#ifdef _WIN32
    BOOL freed = FreeLibrary(lib_handle);
    EXPECT_EQ(TRUE, freed);
#else
    int freed = dlclose(lib_handle);
    EXPECT_EQ(0, freed);
#endif
}

void* GetEntryPoint(LibHandle lib_handle, const char* entry_point_name)
{
    void* proc_address = nullptr;
#ifdef _WIN32
    proc_address = GetProcAddress(lib_handle, entry_point_name);
#else
    proc_address = dlsym(lib_handle, entry_point_name);
#endif
    EXPECT_NE(nullptr, proc_address);

    return proc_address;
}

void VerifyDerivedCounterCount(const GpaApiType api, GpaHwGeneration generation, const std::vector<GpaCounterDesc> counter_descriptions)
{
    LibHandle                     lib_handle                    = nullptr;
    const GpaCounterInfo*         counter_info                  = nullptr;
    GpaCounterLibFuncTable        fn_table                      = {};
    GpaCounterContext             counter_context               = {};
    GpaCounterParam               counter_parameters            = {};
    GpaUInt32                     counter_index                 = 0;
    GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, generation_device_map[generation], REVISION_ID_ANY, nullptr, 0};

    if (!LoadAndVerifyCounterLib(&lib_handle, &fn_table))
    {
        return;
    }

    EXPECT_EQ(kGpaStatusOk, fn_table.GpaCounterLibOpenCounterContext(api, counter_context_hardware_info, kGpaOpenContextDefaultBit, TRUE, &counter_context));

    if (counter_context != nullptr)
    {
        // Verify the number of hardware counters referenced by each derived counter.
        counter_parameters.is_derived_counter = true;
        for (const auto& counter_desc : counter_descriptions)
        {
            // Set counter parameters.
            counter_parameters.derived_counter_name = counter_desc.name;
            EXPECT_EQ(kGpaStatusOk, fn_table.GpaCounterLibGetCounterIndex(counter_context, &counter_parameters, &counter_index)) << "Failed to get counter index for " << counter_desc.name;

            // Get counter information.
            EXPECT_EQ(kGpaStatusOk, fn_table.GpaCounterLibGetCounterInfo(counter_context, counter_index, &counter_info))
                << "Failed to get counter info for " << counter_desc.name;
            EXPECT_NE(nullptr, counter_info);
            if (counter_info != nullptr)
            {
                EXPECT_EQ(counter_info->gpa_derived_counter->gpa_hw_counter_count, counter_desc.num_hardware_counters) << "Received incorrect number of hardware counters for " << counter_desc.name;
            }
        }
    }

    EXPECT_EQ(kGpaStatusOk, fn_table.GpaCounterLibCloseCounterContext(counter_context));

    UnloadLib(lib_handle);
}

void VerifyNotImplemented(GpaApiType api, unsigned int device_Id)
{
    LibHandle              lib_handle                 = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    if (!LoadAndVerifyCounterLib(&lib_handle, &gpa_counter_lib_func_table))
    {
        return;
    }

    GpaCounterContext             gpa_counter_context           = nullptr;
    GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, device_Id, REVISION_ID_ANY, nullptr, 0};
    GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(api,
                                                                                      counter_context_hardware_info,
                                                                                      kGpaOpenContextDefaultBit,
                                                                                      TRUE,
                                                                                      &gpa_counter_context);
    EXPECT_EQ(kGpaStatusErrorHardwareNotSupported, gpa_status);

    gpa_status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
    EXPECT_EQ(kGpaStatusErrorContextNotOpen, gpa_status);

    UnloadLib(lib_handle);
}

void VerifyNotImplemented(GpaApiType api, GpaHwGeneration generation)
{
    LibHandle              lib_handle                 = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    if (!LoadAndVerifyCounterLib(&lib_handle, &gpa_counter_lib_func_table))
    {
        return;
    }

    GpaCounterContext             gpa_counter_context           = nullptr;
    GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, generation_device_map[generation], REVISION_ID_ANY, nullptr, 0};
    GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(api,
                                                                                      counter_context_hardware_info,
                                                                                      kGpaOpenContextDefaultBit,
                                                                                      TRUE,
                                                                                      &gpa_counter_context);
    EXPECT_EQ(kGpaStatusErrorHardwareNotSupported, gpa_status);

    gpa_status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
    EXPECT_EQ(kGpaStatusErrorContextNotOpen, gpa_status);

    UnloadLib(lib_handle);
}

void VerifyHardwareNotSupported(GpaApiType api, unsigned int device_id)
{
    LibHandle              lib_handle                 = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    if (!LoadAndVerifyCounterLib(&lib_handle, &gpa_counter_lib_func_table))
    {
        return;
    }

    GpaCounterContext             gpa_counter_context           = nullptr;
    GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, device_id, REVISION_ID_ANY, nullptr, 0};
    GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(api,
                                                                                      counter_context_hardware_info,
                                                                                      kGpaOpenContextDefaultBit,
                                                                                      TRUE,
                                                                                      &gpa_counter_context);
    EXPECT_EQ(kGpaStatusErrorHardwareNotSupported, gpa_status);

    gpa_status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
    EXPECT_EQ(kGpaStatusErrorNullPointer, gpa_status);

    UnloadLib(lib_handle);
}

void VerifyHardwareNotSupported(GpaApiType api, GpaHwGeneration generation)
{
    LibHandle              lib_handle                 = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    if (!LoadAndVerifyCounterLib(&lib_handle, &gpa_counter_lib_func_table))
    {
        return;
    }

    GpaCounterContext             gpa_counter_context           = nullptr;
    GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, generation_device_map[generation], REVISION_ID_ANY, nullptr, 0};
    GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(api,
                                                                                      counter_context_hardware_info,
                                                                                      kGpaOpenContextDefaultBit,
                                                                                      TRUE,
                                                                                      &gpa_counter_context);
    EXPECT_EQ(kGpaStatusErrorHardwareNotSupported, gpa_status);

    gpa_status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
    EXPECT_EQ(kGpaStatusErrorNullPointer, gpa_status);

    UnloadLib(lib_handle);
}

void VerifyInvalidOpenContextParameters(GpaApiType api, unsigned int device_id)
{
    LibHandle              lib_handle                 = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    if (!LoadAndVerifyCounterLib(&lib_handle, &gpa_counter_lib_func_table))
    {
        return;
    }

    // GPA always generates ASIC-specific counters now, and so passing in FALSE for this parameter is now an invalid parameter.
    GpaUInt8                      generate_asic_specific_counters_deprecated = FALSE;
    GpaCounterContext             gpa_counter_context                        = nullptr;
    GpaCounterContextHardwareInfo counter_context_hardware_info              = {kAmdVendorId, device_id, REVISION_ID_ANY, nullptr, 0};
    GpaStatus                     gpa_status                                 = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(api,
                                                                                      counter_context_hardware_info,
                                                                                      kGpaOpenContextDefaultBit,
                                                                                      generate_asic_specific_counters_deprecated,
                                                                                      &gpa_counter_context);
    EXPECT_EQ(kGpaStatusErrorInvalidParameter, gpa_status);
    EXPECT_EQ(nullptr, gpa_counter_context);
    if (gpa_status == kGpaStatusOk)
    {
        EXPECT_NE(nullptr, gpa_counter_context);
        gpa_status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
        EXPECT_EQ(kGpaStatusErrorNullPointer, gpa_status);
    }

    // It is also an InvalidParameter error to hide the derived counters without exposing the hardware counters,
    // because that would result in 0 counters being exposed.
    gpa_counter_context = nullptr;
    gpa_status          = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(api,
                                                                            counter_context_hardware_info,
                                                                            kGpaOpenContextHideDerivedCountersBit,
                                                                            TRUE,
                                                                            &gpa_counter_context);
    EXPECT_EQ(kGpaStatusErrorInvalidParameter, gpa_status);
    EXPECT_EQ(nullptr, gpa_counter_context);
    if (gpa_status == kGpaStatusOk)
    {
        EXPECT_NE(nullptr, gpa_counter_context);
        gpa_status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
        EXPECT_EQ(kGpaStatusErrorNullPointer, gpa_status);
    }

    UnloadLib(lib_handle);
}

void VerifyCounterNames(GpaApiType               api,
                        unsigned int             device_id,
                        std::vector<const char*> expected_derived_names,
                        std::vector<const char*> expected_hardware_names)
{
    LibHandle              lib_handle                 = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    if (!LoadAndVerifyCounterLib(&lib_handle, &gpa_counter_lib_func_table))
    {
        return;
    }

    std::vector<std::pair<GpaOpenContextFlags, std::vector<const char*>&>> counter_combinations;
    counter_combinations.push_back({kGpaOpenContextDefaultBit, expected_derived_names});

    if (!expected_hardware_names.empty())
    {
        counter_combinations.push_back({kGpaOpenContextHideDerivedCountersBit | kGpaOpenContextEnableHardwareCountersBit, expected_hardware_names});
    }

    for (auto counter_combination = counter_combinations.begin(); counter_combination != counter_combinations.end(); ++counter_combination)
    {
        GpaOpenContextFlags       open_context_flags = counter_combination->first;
        std::vector<const char*>& expectedNames      = counter_combination->second;

        GpaCounterContext             gpa_counter_context           = nullptr;
        GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, device_id, REVISION_ID_ANY, nullptr, 0};
        GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(api,
                                                                                          counter_context_hardware_info,
                                                                                          open_context_flags,
                                                                                          TRUE,
                                                                                          &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        if (gpa_status != kGpaStatusOk)
        {
            continue;
        }

        GpaUInt32 num_counters = 0u;
        gpa_status             = gpa_counter_lib_func_table.GpaCounterLibGetNumCounters(gpa_counter_context, &num_counters);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        EXPECT_EQ(expectedNames.size(), static_cast<GpaUInt32>(num_counters));

        if (num_counters <= expectedNames.size())
        {
            const char* temp_str = nullptr;
            for (unsigned int i = 0; i < expectedNames.size(); ++i)
            {
                EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetCounterName(gpa_counter_context, i, &temp_str));
                EXPECT_STREQ(expectedNames[i], temp_str);

                EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetCounterGroup(gpa_counter_context, i, &temp_str));
                EXPECT_NE((const char*)nullptr, temp_str);
                if (temp_str != nullptr)
                {
                    EXPECT_NE(0, strcmp("", temp_str));
                }

                EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetCounterDescription(gpa_counter_context, i, &temp_str));
                EXPECT_NE((const char*)nullptr, temp_str);

                if (temp_str != nullptr)
                {
                    EXPECT_NE(0, strcmp("", temp_str));
                    // the format of the description used to be "#GROUP#counter description", but isn't any longer, so make sure the description does NOT start with '#'
                    EXPECT_NE('#', temp_str[0]);
                }
            }
        }

        if (num_counters > expectedNames.size())
        {
            const char* temp_str = nullptr;
            for (unsigned int i = (unsigned int)expectedNames.size(); i < num_counters; ++i)
            {
                gpa_counter_lib_func_table.GpaCounterLibGetCounterName(gpa_counter_context, i, &temp_str);
                EXPECT_STREQ(temp_str, "") << "This counter is not expected to be exposed.";
            }
        }

        gpa_status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
    }

    UnloadLib(lib_handle);
}

// Verifies that GpaCounterLibOpenCounterContext() succeeds with all values of GpaOpenContextBits.
void VerifyOpenCounterContext(GpaApiType api, GpaHwGeneration generation)
{
    LibHandle              lib_handle                 = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    if (!LoadAndVerifyCounterLib(&lib_handle, &gpa_counter_lib_func_table))
    {
        return;
    }

    GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, generation_device_map[generation], REVISION_ID_ANY, nullptr, 0};

    GpaOpenContextBits context_bits_values[] = {
        kGpaOpenContextDefaultBit,

        // This alone will generate an error--requested no counters
        // kGpaOpenContextHideDerivedCountersBit,

        kGpaOpenContextClockModeNoneBit,
        kGpaOpenContextClockModePeakBit,
        kGpaOpenContextClockModeMinMemoryBit,
        kGpaOpenContextClockModeMinEngineBit,
        kGpaOpenContextEnableHardwareCountersBit,

        // Ask for only the HW counters (exclude derived counters)
        (GpaOpenContextBits)(kGpaOpenContextHideDerivedCountersBit | kGpaOpenContextEnableHardwareCountersBit),
    };

    // Make sure the options work that are expected to pass.
    for (GpaOpenContextBits context_bits : context_bits_values)
    {
        GpaCounterContext gpa_counter_context = nullptr;
        EXPECT_EQ(kGpaStatusOk,
                  gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(api, counter_context_hardware_info, context_bits, TRUE, &gpa_counter_context));
        EXPECT_NE(gpa_counter_context, nullptr);

        EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context));
    }

    // Can't open a context with hidden derived counters, because that would result no counters being exposed - don't set the user up for a faulty situation.
    {
        GpaCounterContext gpa_counter_context = nullptr;

        EXPECT_NE(kGpaStatusOk,
                  gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
                      api, counter_context_hardware_info, (GpaOpenContextBits)kGpaOpenContextHideDerivedCountersBit, TRUE, &gpa_counter_context));
        EXPECT_EQ(gpa_counter_context, nullptr);

        // Only close the context if it was actually created, but it should have failed to open.
        if (gpa_counter_context != nullptr)
        {
            EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context));
        }
    }

    // Normally, the GPA libraries will not accept more than one ClockMode bit to be specified at the same time, because
    // they would be conflicting eachother. However... the GPUPerfAPICounter library does not actually do any profiling itself,
    // so it has no restrictions about what ClockModes are specified. The tests below confirm that it will still successfully
    // open a context with these unexpected combinations of bits.
    GpaOpenContextBits mulitiple_clockmode_context_bits_values[] = {
        (GpaOpenContextBits)(kGpaOpenContextClockModeNoneBit | kGpaOpenContextClockModePeakBit),
        (GpaOpenContextBits)(kGpaOpenContextClockModeNoneBit | kGpaOpenContextClockModeMinMemoryBit),
        (GpaOpenContextBits)(kGpaOpenContextClockModeNoneBit | kGpaOpenContextClockModeMinEngineBit),
        (GpaOpenContextBits)(kGpaOpenContextClockModePeakBit | kGpaOpenContextClockModeMinMemoryBit),
        (GpaOpenContextBits)(kGpaOpenContextClockModePeakBit | kGpaOpenContextClockModeMinEngineBit),
        (GpaOpenContextBits)(kGpaOpenContextClockModeMinMemoryBit | kGpaOpenContextClockModeMinEngineBit),
        (GpaOpenContextBits)(kGpaOpenContextClockModeNoneBit | kGpaOpenContextClockModePeakBit | kGpaOpenContextClockModeMinMemoryBit),
        (GpaOpenContextBits)(kGpaOpenContextClockModeNoneBit | kGpaOpenContextClockModePeakBit | kGpaOpenContextClockModeMinEngineBit),
        (GpaOpenContextBits)(kGpaOpenContextClockModeNoneBit | kGpaOpenContextClockModeMinMemoryBit | kGpaOpenContextClockModeMinEngineBit),
        (GpaOpenContextBits)(kGpaOpenContextClockModePeakBit | kGpaOpenContextClockModeMinEngineBit | kGpaOpenContextClockModeMinMemoryBit),
        (GpaOpenContextBits)(kGpaOpenContextClockModeNoneBit | kGpaOpenContextClockModePeakBit | kGpaOpenContextClockModeMinMemoryBit |
                             kGpaOpenContextClockModeMinEngineBit),
    };

    for (GpaOpenContextBits clockmode_context_bits : mulitiple_clockmode_context_bits_values)
    {
        GpaCounterContext gpa_counter_context = nullptr;

        EXPECT_EQ(
            kGpaStatusOk,
            gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(api, counter_context_hardware_info, clockmode_context_bits, TRUE, &gpa_counter_context));
        EXPECT_NE(gpa_counter_context, nullptr);

        // Only close the context if it was actually created.
        if (gpa_counter_context != nullptr)
        {
            EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context));
        }
    }

    // Now test that combinations of public and hardware counters actually expose a different number of counters.
    {
        GpaUInt32 num_default_counters              = 0;
        GpaUInt32 num_hardware_counters             = 0;
        GpaUInt32 num_default_and_hardware_counters = 0;

        // Default counters.
        {
            GpaCounterContext gpa_counter_context = nullptr;
            EXPECT_EQ(kGpaStatusOk,
                      gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
                          api, counter_context_hardware_info, kGpaOpenContextDefaultBit, TRUE, &gpa_counter_context));
            EXPECT_NE(gpa_counter_context, nullptr);

            if (gpa_counter_context != nullptr)
            {
                EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetNumCounters(gpa_counter_context, &num_default_counters));
                EXPECT_GT(num_default_counters, 0);

                EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context));
            }
        }
        // Hardware counters.
        {
            GpaCounterContext gpa_counter_context = nullptr;
            EXPECT_EQ(
                kGpaStatusOk,
                gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(api,
                                                                           counter_context_hardware_info,
                                                                           kGpaOpenContextHidePublicCountersBit | kGpaOpenContextEnableHardwareCountersBit,
                                                                           TRUE,
                                                                           &gpa_counter_context));
            EXPECT_NE(gpa_counter_context, nullptr);

            if (gpa_counter_context != nullptr)
            {
                EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetNumCounters(gpa_counter_context, &num_hardware_counters));
                EXPECT_GT(num_hardware_counters, 0);

                EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context));
            }
        }
        // Default and hardware counters.
        {
            GpaCounterContext gpa_counter_context = nullptr;
            EXPECT_EQ(
                kGpaStatusOk,
                gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
                    api, counter_context_hardware_info, kGpaOpenContextDefaultBit | kGpaOpenContextEnableHardwareCountersBit, TRUE, &gpa_counter_context));
            EXPECT_NE(gpa_counter_context, nullptr);

            if (gpa_counter_context != nullptr)
            {
                EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetNumCounters(gpa_counter_context, &num_default_and_hardware_counters));
                EXPECT_GT(num_default_and_hardware_counters, 0);

                EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context));
            }
        }

        // Now compare all three values relative to eachother.
        EXPECT_LT(num_default_counters, num_hardware_counters);
        EXPECT_LT(num_hardware_counters, num_default_and_hardware_counters);
        EXPECT_EQ(num_default_counters + num_hardware_counters, num_default_and_hardware_counters);
    }

    UnloadLib(lib_handle);
}

void VerifyCounterNames(GpaApiType api, GpaHwGeneration generation, std::vector<const char*> expectedNames, std::vector<const char*> expected_hardware_names)
{
    assert(generation_device_map.size() == GDT_HW_GENERATION_LAST);
    VerifyCounterNames(api, generation_device_map[generation], expectedNames, expected_hardware_names);
}

void VerifyCounterLibInterface(GpaApiType api, unsigned device_id, unsigned revision_id, std::vector<GpaDerivedCounterInfo> expected_derived_counter_list)
{
    UNREFERENCED_PARAMETER(expected_derived_counter_list);

    LibHandle              lib_handle                 = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    if (!LoadAndVerifyCounterLib(&lib_handle, &gpa_counter_lib_func_table))
    {
        return;
    }

    GpaCounterContext gpa_counter_context = nullptr;

    {
        if (device_id == kDevIdGfx10_3)
        {
            GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, device_id, revision_id, nullptr, 0};
            GpaStatus                     gpa_status =
                gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(api,
                                                                           counter_context_hardware_info,
                                                                           kGpaOpenContextDefaultBit | kGpaOpenContextEnableHardwareCountersBit,
                                                                           TRUE,
                                                                           &gpa_counter_context);
            EXPECT_EQ(kGpaStatusOk, gpa_status);

            GpaCounterParam counter_param;
            GpaUInt32       index                              = 0;
            counter_param.is_derived_counter                   = false;
            counter_param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockGl2C;
            counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
            counter_param.gpa_hw_counter.gpa_hw_block_event_id = 43;
            //counter.gpa_hw_counter.gpa_shader_mask             = kGpaShaderMaskAll;

            gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param, &index);
            EXPECT_EQ(gpa_status, kGpaStatusOk);

            const char* temp_char = nullptr;
            gpa_status            = gpa_counter_lib_func_table.GpaCounterLibGetCounterName(gpa_counter_context, index, &temp_char);
            EXPECT_EQ(gpa_status, kGpaStatusOk);

            gpa_status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
            EXPECT_EQ(kGpaStatusOk, gpa_status);
            gpa_counter_context = nullptr;
        }
    }
    {
        GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, device_id, revision_id, nullptr, 0};
        GpaStatus gpa_status = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(
            api, counter_context_hardware_info, kGpaOpenContextDefaultBit, TRUE, &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        if (gpa_status == kGpaStatusOk)
        {
            const GpaCounterInfo* temp_ptr = nullptr;
            EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetCounterInfo(gpa_counter_context, 8, &temp_ptr));

            if ((device_id == kDevIdGfx11 || device_id == kDevIdGfx11_0_3 || device_id == kDevIdGfx11_0_3B || device_id == kDevIdGfx11_5_0) &&
                (kGpaApiDirectx11 == api || kGpaApiOpengl == api || kGpaApiDirectx12 == api || kGpaApiVulkan == api))
            {
                GpaCounterParam counter_param;
                counter_param.is_derived_counter   = true;
                counter_param.derived_counter_name = "PSVALUInstCount";
                GpaUInt32 counter_index            = 0;
                gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param, &counter_index);
                EXPECT_EQ(kGpaStatusErrorCounterNotFound, gpa_status)
                    << "If PSVALUInstCount has been added back in for Gfx11, this conditional codepath can be removed.";
            }
            else if (device_id == kDevIdGfx10 || device_id == kDevIdGfx10_3)
            {
                GpaCounterParam counter_param;
                counter_param.is_derived_counter   = true;
                counter_param.derived_counter_name = "PSVALUInstCount";
                GpaUInt32 counter_index            = 0;
                gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param, &counter_index);
                EXPECT_EQ(kGpaStatusErrorCounterNotFound, gpa_status)
                    << "If PSVALUInstCount has been added back in for Gfx10 or Gfx10_3, this conditional codepath can be removed.";
            }
            else if (kGpaApiDirectx11 == api || kGpaApiOpengl == api || kGpaApiDirectx12 == api || kGpaApiVulkan == api)
            {
                {
                    // Graphics SQ-derived counters use a shader mask
                    GpaCounterParam counter_param;
                    counter_param.is_derived_counter   = true;
                    counter_param.derived_counter_name = "PSVALUInstCount";
                    GpaUInt32 counter_index            = GPA_UINT32_MAX;
                    EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param, &counter_index));
                    EXPECT_NE(counter_index, GPA_UINT32_MAX);
                    if (counter_index != GPA_UINT32_MAX)
                    {
                        EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetCounterInfo(gpa_counter_context, counter_index, &temp_ptr));
                        if (temp_ptr != nullptr)
                        {
                            EXPECT_TRUE(temp_ptr->is_derived_counter);
                            for (GpaUInt32 i = 0; i < temp_ptr->gpa_derived_counter->gpa_hw_counter_count; i++)
                            {
                                EXPECT_EQ(kGpaShaderMaskPs, temp_ptr->gpa_derived_counter->gpa_hw_counters[i].gpa_shader_mask);
                            }
                        }
                    }
                }

                {
                    GpaCounterParam counter_param;
                    counter_param.is_derived_counter   = true;
                    counter_param.derived_counter_name = "PSTime";
                    GpaUInt32 counter_index            = 0;
                    EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param, &counter_index));
                    EXPECT_NE(counter_index, GPA_UINT32_MAX);
                    if (counter_index != GPA_UINT32_MAX)
                    {
                        EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetCounterInfo(gpa_counter_context, counter_index, &temp_ptr));
                        if (temp_ptr != nullptr)
                        {
                            EXPECT_TRUE(temp_ptr->is_derived_counter);

                            bool does_gpu_time_block_exist = false;
                            for (GpaUInt32 i = 0; i < temp_ptr->gpa_derived_counter->gpa_hw_counter_count; i++)
                            {
                                does_gpu_time_block_exist |= temp_ptr->gpa_derived_counter->gpa_hw_counters[i].is_timing_block;
                            }

                            EXPECT_TRUE(does_gpu_time_block_exist);
                        }
                    }
                }
            }
            else if (kGpaApiOpencl == api)
            {
                // OpenCL SQ-derived counters do not use a shader mask
                GpaCounterParam counter_param;
                counter_param.is_derived_counter   = true;
                counter_param.derived_counter_name = "VALUInsts";
                GpaUInt32 counter_index            = 0;
                gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param, &counter_index);
                EXPECT_EQ(kGpaStatusOk, gpa_status);
                gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetCounterInfo(gpa_counter_context, counter_index, &temp_ptr);
                EXPECT_EQ(kGpaStatusOk, gpa_status);
                EXPECT_TRUE(temp_ptr->is_derived_counter);
                for (GpaUInt32 i = 0; i < temp_ptr->gpa_derived_counter->gpa_hw_counter_count; i++)
                {
                    EXPECT_TRUE(kGpaShaderMaskAll == temp_ptr->gpa_derived_counter->gpa_hw_counters[i].gpa_shader_mask);
                }
            }

            gpa_status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
            EXPECT_EQ(kGpaStatusOk, gpa_status);
            gpa_counter_context = nullptr;
        }
    }
    {
        GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, device_id, revision_id, nullptr, 0};
        GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(api,
                                                                                          counter_context_hardware_info,
                                                                                          kGpaOpenContextDefaultBit | kGpaOpenContextEnableHardwareCountersBit,
                                                                                          TRUE,
                                                                                          &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        {
            GpaCounterParam counter_param;
            counter_param.is_derived_counter = false;

            if (device_id == kDevIdGfx11 || device_id == kDevIdGfx11_0_3 || device_id == kDevIdGfx11_0_3B || device_id == kDevIdGfx11_5_0)
            {
                // On Gfx11, the previous SQ block was renamed to SQG, and the actual underlying SQ blocks were introduced as SQWGP.
                // This test is intended to ensure that we can access the SQ_PERF_SEL_WAVES event, which is now on the SQWGP blocks.
                counter_param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockSqWgp;
                counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
                counter_param.gpa_hw_counter.gpa_hw_block_event_id = kSqPerfSelWaves;
                counter_param.gpa_hw_counter.gpa_shader_mask       = kGpaShaderMaskPs;

                if (api == kGpaApiOpencl)
                {
                    // OpenCL doesn't need to concern itself with different wave-types, so it uses All for SqWgp.
                    counter_param.gpa_hw_counter.gpa_shader_mask = kGpaShaderMaskAll;
                }
            }
            else
            {
                counter_param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockSq;
                counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
                counter_param.gpa_hw_counter.gpa_hw_block_event_id = kSqPerfSelWaves;
                counter_param.gpa_hw_counter.gpa_shader_mask       = kGpaShaderMaskPs;
            }

            GpaUInt32 index = GPA_UINT32_MAX;
            EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param, &index));
            EXPECT_NE(index, GPA_UINT32_MAX);
            if (index != GPA_UINT32_MAX)
            {
                const char* temp_char = nullptr;
                gpa_status            = gpa_counter_lib_func_table.GpaCounterLibGetCounterName(gpa_counter_context, index, &temp_char);
                EXPECT_EQ(kGpaStatusOk, gpa_status);
                EXPECT_NE(temp_char, nullptr);

                if (gpa_status == kGpaStatusOk && temp_char != nullptr)
                {
                    GpaUInt32       index2 = 0;
                    GpaCounterParam counter_param2;
                    counter_param2.is_derived_counter   = true;
                    counter_param2.derived_counter_name = temp_char;
                    gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param2, &index2);
                    if (index != index2)
                    {
                        std::cout << "Index1 " << index << " counter name " << temp_char << " doesn't match with " << index2 << "and gpa status is "
                                  << gpa_status << std::endl;
                    }
                    EXPECT_EQ(index, index2);

                    const GpaCounterInfo* temp_ptr = nullptr;
                    gpa_counter_lib_func_table.GpaCounterLibGetCounterInfo(gpa_counter_context, index2, &temp_ptr);
                    EXPECT_FALSE(temp_ptr->is_derived_counter);
                    EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block, counter_param.gpa_hw_counter.gpa_hw_block);
                    EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block_instance, counter_param.gpa_hw_counter.gpa_hw_block_instance);
                    EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block_event_id, counter_param.gpa_hw_counter.gpa_hw_block_event_id);
                    EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_shader_mask, counter_param.gpa_hw_counter.gpa_shader_mask);
                }
            }
        }

        {
            GpaCounterParam counter_param;

            if (device_id == kDevIdGfx11 || device_id == kDevIdGfx11_0_3 || device_id == kDevIdGfx11_0_3B || device_id == kDevIdGfx11_5_0)
            {
                // On Gfx11, the previous SQ block was renamed to SQG, and the actual underlying SQ blocks were introduced as SQWGP.
                // This test is intended to ensure that we can access the SQ_PERF_SEL_WAVES event, which is now on the SQWGP blocks.
                counter_param.is_derived_counter                   = false;
                counter_param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockSqWgp;
                counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
                counter_param.gpa_hw_counter.gpa_hw_block_event_id = kSqPerfSelWaves;
                counter_param.gpa_hw_counter.gpa_shader_mask       = kGpaShaderMaskAll;
            }
            else
            {
                counter_param.is_derived_counter                   = false;
                counter_param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockSq;
                counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
                counter_param.gpa_hw_counter.gpa_hw_block_event_id = kSqPerfSelWaves;
                counter_param.gpa_hw_counter.gpa_shader_mask       = kGpaShaderMaskAll;
            }

            GpaUInt32 index = GPA_UINT32_MAX;
            EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param, &index));
            EXPECT_NE(index, GPA_UINT32_MAX);
            if (index != GPA_UINT32_MAX)
            {
                const char* temp_char = nullptr;
                gpa_status            = gpa_counter_lib_func_table.GpaCounterLibGetCounterName(gpa_counter_context, index, &temp_char);
                EXPECT_EQ(kGpaStatusOk, gpa_status);
                EXPECT_NE(temp_char, nullptr);

                GpaUInt32       index2 = 0u;
                GpaCounterParam counter_param2;
                counter_param2.is_derived_counter   = true;
                counter_param2.derived_counter_name = temp_char;
                const GpaCounterInfo* temp_ptr      = nullptr;
                EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param2, &index2));
                EXPECT_EQ(index, index2);
                EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetCounterInfo(gpa_counter_context, index2, &temp_ptr));
                EXPECT_NE(temp_ptr, nullptr);
                if (temp_ptr != nullptr)
                {
                    EXPECT_FALSE(temp_ptr->is_derived_counter);
                    EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block, counter_param.gpa_hw_counter.gpa_hw_block);
                    EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block_instance, counter_param.gpa_hw_counter.gpa_hw_block_instance);
                    EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block_event_id, counter_param.gpa_hw_counter.gpa_hw_block_event_id);
                    EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_shader_mask, counter_param.gpa_hw_counter.gpa_shader_mask);
                }

                if (device_id == kDevIdGfx11 || device_id == kDevIdGfx11_0_3 || device_id == kDevIdGfx11_0_3B || device_id == kDevIdGfx11_5_0)
                {
                    // On Gfx11, the previous SQ block was renamed to SQG, and the actual underlying SQ blocks were introduced as SQWGP.
                    // This test is intended to ensure that we can access the SQ_PERF_SEL_WAVES event, which is now on the SQWGP blocks.
                    // LS shader waves were removed from GFX11, so use HS instead.
                    counter_param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockSqWgp;
                    counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
                    counter_param.gpa_hw_counter.gpa_hw_block_event_id = kSqPerfSelWaves;
                    counter_param.gpa_hw_counter.gpa_shader_mask       = kGpaShaderMaskHs;

                    if (api == kGpaApiOpencl)
                    {
                        // OpenCL doesn't need to concern itself with different wave-types, so it uses All for SqWgp.
                        counter_param.gpa_hw_counter.gpa_shader_mask = kGpaShaderMaskAll;
                    }
                }
                else
                {
                    counter_param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockSq;
                    counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
                    counter_param.gpa_hw_counter.gpa_hw_block_event_id = kSqPerfSelWaves;
                    counter_param.gpa_hw_counter.gpa_shader_mask       = kGpaShaderMaskLs;
                }

                EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param, &index));

                temp_char = nullptr;
                EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetCounterName(gpa_counter_context, index, &temp_char));
                EXPECT_NE(temp_char, nullptr);
                if (temp_char != nullptr)
                {
                    counter_param2.derived_counter_name = temp_char;
                    EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param2, &index2));
                    EXPECT_NE(index2, GPA_UINT32_MAX);
                    EXPECT_EQ(index, index2);
                    temp_ptr = nullptr;
                    EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetCounterInfo(gpa_counter_context, index2, &temp_ptr));
                    EXPECT_NE(temp_ptr, nullptr);
                    if (temp_ptr != nullptr)
                    {
                        EXPECT_FALSE(temp_ptr->is_derived_counter);
                        EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block, counter_param.gpa_hw_counter.gpa_hw_block);
                        EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block_instance, counter_param.gpa_hw_counter.gpa_hw_block_instance);
                        EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block_event_id, counter_param.gpa_hw_counter.gpa_hw_block_event_id);
                        EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_shader_mask, counter_param.gpa_hw_counter.gpa_shader_mask);
                    }
                }
            }
        }

        if (device_id == kDevIdGfx10)
        {
            GpaCounterParam counter_param;
            counter_param.is_derived_counter                   = false;
            counter_param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockGl1C;
            counter_param.gpa_hw_counter.gpa_hw_block_instance = 33;  // Instance not available
            counter_param.gpa_hw_counter.gpa_hw_block_event_id = kGl1cPerfSelReq;
            counter_param.gpa_hw_counter.gpa_shader_mask       = kGpaShaderMaskLs;

            GpaUInt32 index = 0u;
            gpa_status      = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param, &index);
            EXPECT_EQ(gpa_status, kGpaStatusErrorCounterNotFound);

            counter_param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockGl1C;
            counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
            counter_param.gpa_hw_counter.gpa_hw_block_event_id = kGl1cPerfSelReq;
            counter_param.gpa_hw_counter.gpa_shader_mask       = kGpaShaderMaskLs;

            gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param, &index);
            EXPECT_EQ(gpa_status, kGpaStatusOk);

            const char* temp_char = nullptr;
            gpa_status            = gpa_counter_lib_func_table.GpaCounterLibGetCounterName(gpa_counter_context, index, &temp_char);
            EXPECT_EQ(gpa_status, kGpaStatusOk);

            GpaCounterParam counter_param2;
            counter_param2.is_derived_counter   = true;
            counter_param2.derived_counter_name = temp_char;
            GpaUInt32 index2                    = 0u;
            EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param2, &index2));
            EXPECT_EQ(index, index2);

            const GpaCounterInfo* temp_ptr = nullptr;
            EXPECT_EQ(kGpaStatusOk, gpa_counter_lib_func_table.GpaCounterLibGetCounterInfo(gpa_counter_context, index2, &temp_ptr));
            EXPECT_NE(temp_ptr, nullptr);
            if (temp_ptr != nullptr)
            {
                EXPECT_FALSE(temp_ptr->is_derived_counter);
                EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block, counter_param.gpa_hw_counter.gpa_hw_block);
                EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block_instance, counter_param.gpa_hw_counter.gpa_hw_block_instance);
                EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block_event_id, counter_param.gpa_hw_counter.gpa_hw_block_event_id);

                // Check for GPA_SHADER_MASK_ALL since the only the SQ block supports the shader mask.
                EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_shader_mask, kGpaShaderMaskAll);
            }
        }

        if (device_id == kDevIdGfx10_3)
        {
            GpaCounterParam counter_param;
            counter_param.is_derived_counter                   = false;
            counter_param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockGl2C;
            counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
            counter_param.gpa_hw_counter.gpa_hw_block_event_id = kGl2cPerfSelMiss;

            GpaUInt32 index = 0u;
            gpa_status      = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param, &index);
            EXPECT_EQ(gpa_status, kGpaStatusOk);

            const char* temp_char = nullptr;
            gpa_status            = gpa_counter_lib_func_table.GpaCounterLibGetCounterName(gpa_counter_context, index, &temp_char);
            EXPECT_EQ(gpa_status, kGpaStatusOk);
        }

        gpa_status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);
        gpa_counter_context = nullptr;
    }

    UnloadLib(lib_handle);
    lib_handle = nullptr;
}

void VerifyCounterByPassCounterLibEntry(GpaApiType api, unsigned device_id, unsigned revision_id)
{
    if (kGpaApiOpencl == api)
    {
        // This verification is specifically for counters exposed by the graphics APIs.
        // There is not currently an equivalent for OpenCL.
        return;
    }

    LibHandle              lib_handle                 = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    if (!LoadAndVerifyCounterLib(&lib_handle, &gpa_counter_lib_func_table))
    {
        return;
    }

    GpaCounterContext gpa_counter_context = nullptr;

    auto GetPassCounters = [&](GpaCounterContext gpa_counter_context,
                               GpaUInt32         counter_count,
                               GpaUInt32*        derived_counter_list) -> std::map<unsigned int, std::vector<unsigned int>> {
        std::map<unsigned int, std::vector<unsigned int>> pass_counter_map;
        GpaUInt32                                         pass_count;
        GpaStatus                                         gpa_status =
            gpa_counter_lib_func_table.GpaCounterLibGetCountersByPass(gpa_counter_context, counter_count, derived_counter_list, &pass_count, nullptr, nullptr);

        if (kGpaStatusOk == gpa_status)
        {
            if (pass_count > 0)
            {
                GpaUInt32* counter_list = new (std::nothrow) GpaUInt32[pass_count];

                if (nullptr != counter_list)
                {
                    gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetCountersByPass(
                        gpa_counter_context, counter_count, derived_counter_list, &pass_count, counter_list, nullptr);

                    GpaPassCounter* pass_counters = new (std::nothrow) GpaPassCounter[pass_count];

                    if (nullptr != pass_counters)
                    {
                        for (unsigned int i = 0; i < pass_count; i++)
                        {
                            pass_counters[i].pass_index      = i;
                            pass_counters[i].counter_count   = counter_list[i];
                            pass_counters[i].counter_indices = new (std::nothrow) GpaUInt32[counter_list[i]];
                        }

                        gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetCountersByPass(
                            gpa_counter_context, counter_count, derived_counter_list, &pass_count, nullptr, pass_counters);

                        if (kGpaStatusOk == gpa_status)
                        {
                            for (unsigned int i = 0; i < pass_count; i++)
                            {
                                std::vector<unsigned int> counter_list_vec;
                                counter_list_vec.resize(pass_counters[i].counter_count);
                                memcpy(counter_list_vec.data(), pass_counters[i].counter_indices, sizeof(GpaUInt32) * pass_counters[i].counter_count);
                                pass_counter_map.insert(std::pair<unsigned int, std::vector<unsigned int>>(i, counter_list_vec));
                                delete[] pass_counters[i].counter_indices;
                            }
                        }
                    }

                    delete[] pass_counters;
                }

                delete[] counter_list;
            }
        }

        return pass_counter_map;
    };

    GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, device_id, revision_id, nullptr, 0};
    GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(api,
                                                                                      counter_context_hardware_info,
                                                                                      kGpaOpenContextDefaultBit | kGpaOpenContextEnableHardwareCountersBit,
                                                                                      TRUE,
                                                                                      &gpa_counter_context);

    GpaCounterParam counter_param;

    counter_param.is_derived_counter   = true;
    counter_param.derived_counter_name = "GPUTime";
    GpaUInt32 gpu_time_counter_index;
    gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param, &gpu_time_counter_index);
    EXPECT_EQ(kGpaStatusOk, gpa_status);
    EXPECT_EQ(0, gpu_time_counter_index);

    counter_param.is_derived_counter   = true;
    counter_param.derived_counter_name = "GPUBusy";
    GpaUInt32 gpu_busy_index;
    gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param, &gpu_busy_index);
    EXPECT_EQ(kGpaStatusOk, gpa_status);
    EXPECT_GT(gpu_busy_index, 0);

    if (device_id == kDevIdGfx11)
    {
        // On Gfx11, the previous SQ block was renamed to SQG, and the actual underlying SQ blocks were introduced as SQWGP.
        // This test is intended to ensure that we can access the SQ_PERF_SEL_WAVES event, which is now on the SQWGP blocks.
        counter_param.is_derived_counter                   = false;
        counter_param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockSqWgp;
        counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
        counter_param.gpa_hw_counter.gpa_hw_block_event_id = kSqPerfSelWaves;
        counter_param.gpa_hw_counter.gpa_shader_mask       = kGpaShaderMaskPs;
    }
    else
    {
        counter_param.is_derived_counter                   = false;
        counter_param.gpa_hw_counter.gpa_hw_block          = kGpaHwBlockSq;
        counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
        counter_param.gpa_hw_counter.gpa_hw_block_event_id = kSqPerfSelWaves;
        counter_param.gpa_hw_counter.gpa_shader_mask       = kGpaShaderMaskPs;
    }

    GpaUInt32 sq_counter_index;
    gpa_status = gpa_counter_lib_func_table.GpaCounterLibGetCounterIndex(gpa_counter_context, &counter_param, &sq_counter_index);

    std::map<unsigned int, std::vector<std::string>> pass_counter_names;

    if (device_id == kDevIdGfx11)
    {
        pass_counter_names = {{0, {"CPF_PERF_SEL_CPF_STAT_BUSY", "CPF_PERF_SEL_ALWAYS_COUNT", "SQWGP_PS0_SQ_PERF_SEL_WAVES"}},
                              {1, {"GPUTime_BOTTOM_TO_BOTTOM_DURATION"}}};
    }
    else if (device_id == kDevIdVI)
    {
        pass_counter_names = {{0, {"GRBM_PERF_SEL_GUI_ACTIVE", "GRBM_PERF_SEL_COUNT", "SQ_PS0_PERF_SEL_WAVES"}}, {1, {"GPUTime_BOTTOM_TO_BOTTOM_DURATION"}}};
    }
    else
    {
        pass_counter_names = {{0, {"CPF_PERF_SEL_CPF_STAT_BUSY", "CPF_PERF_SEL_ALWAYS_COUNT", "SQ_PS0_PERF_SEL_WAVES"}},
                              {1, {"GPUTime_BOTTOM_TO_BOTTOM_DURATION"}}};
    }

    if (kGpaStatusOk == gpa_status)
    {
        GpaUInt32                                         derived_counter_list[] = {gpu_time_counter_index, gpu_busy_index, sq_counter_index};
        std::map<unsigned int, std::vector<unsigned int>> pass_counter_map       = GetPassCounters(gpa_counter_context, 3, derived_counter_list);

        unsigned int pass_iter = 0;
        for (auto iter = pass_counter_map.cbegin(); iter != pass_counter_map.cend(); ++iter)
        {
            unsigned counter_index_iter = 0u;
            for (auto counter_iter = iter->second.cbegin(); counter_iter != iter->second.cend(); ++counter_iter)
            {
                const char* counter_name;
                gpa_counter_lib_func_table.GpaCounterLibGetCounterName(gpa_counter_context, *counter_iter, &counter_name);
                EXPECT_STREQ(counter_name, pass_counter_names[pass_iter][counter_index_iter].c_str());
                counter_index_iter++;
            }
            pass_iter++;
        }
    }

    gpa_status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
    EXPECT_EQ(kGpaStatusOk, gpa_status);
    gpa_counter_context = nullptr;

    UnloadLib(lib_handle);
    lib_handle = nullptr;
}

void VerifyPassCount(GpaApiType api, unsigned int device_id, const std::vector<unsigned int>& counters_to_enable, unsigned int expected_num_passes)
{
    LibHandle              lib_handle                 = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    if (!LoadAndVerifyCounterLib(&lib_handle, &gpa_counter_lib_func_table))
    {
        return;
    }

    GpaCounterContext             gpa_counter_context           = nullptr;
    GpaCounterContextHardwareInfo counter_context_hardware_info = {kAmdVendorId, device_id, REVISION_ID_ANY, nullptr, 0};
    GpaStatus                     gpa_status                    = gpa_counter_lib_func_table.GpaCounterLibOpenCounterContext(api,
                                                                                      counter_context_hardware_info,
                                                                                      kGpaOpenContextDefaultBit,
                                                                                      TRUE,
                                                                                      &gpa_counter_context);
    EXPECT_EQ(kGpaStatusOk, gpa_status);

    GpaUInt32 pass_count = 0u;
    gpa_status           = gpa_counter_lib_func_table.GpaCounterLibGetPassCount(
        gpa_counter_context, counters_to_enable.data(), static_cast<GpaUInt32>(counters_to_enable.size()), &pass_count);
    EXPECT_EQ(expected_num_passes, pass_count);

    gpa_status = gpa_counter_lib_func_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
    EXPECT_EQ(kGpaStatusOk, gpa_status);

    UnloadLib(lib_handle);
}

void VerifyCountersInPass(GpaApiType                                                                      api,
                          unsigned int                                                                    device_id,
                          const std::vector<unsigned int>&                                                counter_to_enable,
                          const std::vector<std::vector<unsigned int>>&                                   expected_hw_counters_per_pass,
                          const std::map<unsigned int, std::map<unsigned int, GpaCounterResultLocation>>& expected_result_location)
{
    LibHandle lib_handle = LoadLib(kCountersLibName);
    ASSERT_NE((LibHandle) nullptr, lib_handle);
    UNREFERENCED_PARAMETER(api);
    UNREFERENCED_PARAMETER(device_id);
    UNREFERENCED_PARAMETER(counter_to_enable);
    UNREFERENCED_PARAMETER(expected_hw_counters_per_pass);
    UNREFERENCED_PARAMETER(expected_result_location);

    UnloadLib(lib_handle);
}

void VerifyCounterCalculation(GpaApiType                           api,
                              unsigned int                         device_id,
                              char*                                counter_name,
                              const std::vector<const GpaUInt64*>& sample_results,
                              GpaFloat64                           expected_result)
{
    LibHandle lib_handle = LoadLib(kCountersLibName);
    ASSERT_NE((LibHandle) nullptr, lib_handle);
    UNREFERENCED_PARAMETER(api);
    UNREFERENCED_PARAMETER(device_id);
    UNREFERENCED_PARAMETER(counter_name);
    UNREFERENCED_PARAMETER(sample_results);
    UNREFERENCED_PARAMETER(expected_result);

    UnloadLib(lib_handle);
}

void VerifyCounterFormula(std::vector<GpaCounterDesc> public_counters)
{
    GpaHwInfo dummy_hardware_info;
    dummy_hardware_info.SetNumberShaderEngines(1);
    dummy_hardware_info.SetNumberShaderArrays(1);
    dummy_hardware_info.SetNumberSimds(1);
    dummy_hardware_info.SetSuClocksPrim(1);
    dummy_hardware_info.SetNumberPrimPipes(1);
    dummy_hardware_info.SetNumberCus(1);
    dummy_hardware_info.SetTimeStampFrequency(1);

    for (std::vector<GpaCounterDesc>::const_iterator it = public_counters.cbegin(); it != public_counters.cend(); ++it)
    {
        std::vector<const GpaUInt64*> results;
        GpaUInt64*                    result_mem = new (std::nothrow) GpaUInt64[it->num_hardware_counters];

        if (nullptr != result_mem)
        {
            memset(result_mem, 1, sizeof(GpaUInt64) * it->num_hardware_counters);
            results.reserve(it->num_hardware_counters);

            for (GpaUInt32 i = 0; i < it->num_hardware_counters; i++)
            {
                results.push_back(result_mem + i);
            }

            GpaFloat64 final_result;
            GpaStatus  gpa_status = EvaluateExpression<GpaFloat64, GpaUInt64>(it->equation, &final_result, results, it->data_type, &dummy_hardware_info);
            delete[] result_mem;
            EXPECT_EQ(kGpaStatusOk, gpa_status);
        }
    }
}
