//==============================================================================
// Copyright (c) 2012-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Helper functions for Counter Generator Unit Tests
//==============================================================================

#include <map>
#include <algorithm>

#include "counter_generator_tests.h"
#include "gpa_hw_info.h"
#include "gpa_split_counters_interfaces.h"

#ifdef _WIN32
const char* countersLibName = "GPUPerfAPICounters" AMDT_PLATFORM_SUFFIX AMDT_DEBUG_SUFFIX AMDT_BUILD_SUFFIX ".dll";
#else
const char* countersLibName = "libGPUPerfAPICounters" AMDT_PLATFORM_SUFFIX AMDT_DEBUG_SUFFIX AMDT_BUILD_SUFFIX ".so";
#endif

LibHandle LoadLib(const char* pLibName)
{
    LibHandle retVal = nullptr;
#ifdef _WIN32
    retVal = LoadLibraryA(pLibName);
#else
    retVal    = dlopen(pLibName, RTLD_NOW);
#endif

    return retVal;
}

static std::map<GPA_Hw_Generation, unsigned int> generation_device_map = {{GPA_HW_GENERATION_GFX6, gDevIdSI},
                                                                          {GPA_HW_GENERATION_GFX7, gDevIdCI},
                                                                          {GPA_HW_GENERATION_GFX8, gDevIdGfx8},
                                                                          {GPA_HW_GENERATION_GFX9, gDevIdGfx9},
                                                                          {GPA_HW_GENERATION_GFX10, gDevIdGfx10}};

void UnloadLib(LibHandle libHandle)
{
#ifdef _WIN32
    BOOL freed = FreeLibrary(libHandle);
    EXPECT_EQ(TRUE, freed);
#else
    int freed = dlclose(libHandle);
    EXPECT_EQ(0, freed);
#endif
}

void* GetEntryPoint(LibHandle libHandle, const char* pEntrypointName)
{
    void* pRetVal = nullptr;
#ifdef _WIN32
    pRetVal = GetProcAddress(libHandle, pEntrypointName);
#else
    pRetVal = dlsym(libHandle, pEntrypointName);
#endif
    EXPECT_NE(nullptr, pRetVal);

    return pRetVal;
}

void VerifyNotImplemented(GPA_API_Type api, unsigned int deviceId, gpa_uint8 generateAsicSpecificCounters)
{
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle) nullptr, libHandle);

    GpaCounterLib_GetFuncTablePtrType get_func_table_ptr =
        reinterpret_cast<GpaCounterLib_GetFuncTablePtrType>(GetEntryPoint(libHandle, "GpaCounterLib_GetFuncTable"));
    ASSERT_NE((GpaCounterLib_GetFuncTablePtrType) nullptr, get_func_table_ptr);

    GpaCounterLibFuncTable gpa_counter_lib_func_table;
    GPA_Status             gpa_status = get_func_table_ptr(&gpa_counter_lib_func_table);
    EXPECT_EQ(GPA_STATUS_OK, gpa_status);

    GPA_CounterContext gpa_counter_context = nullptr;
    gpa_status                             = gpa_counter_lib_func_table.GpaCounterLib_OpenCounterContext(
        api, AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, GPA_OPENCONTEXT_DEFAULT_BIT, generateAsicSpecificCounters, &gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED, gpa_status);

    gpa_status = gpa_counter_lib_func_table.GpaCounterLib_CloseCounterContext(gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_OPEN, gpa_status);

    UnloadLib(libHandle);
}

void VerifyNotImplemented(GPA_API_Type api, GPA_Hw_Generation generation, gpa_uint8 generateAsicSpecificCounters)
{
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle) nullptr, libHandle);

    GpaCounterLib_GetFuncTablePtrType get_func_table_ptr =
        reinterpret_cast<GpaCounterLib_GetFuncTablePtrType>(GetEntryPoint(libHandle, "GpaCounterLib_GetFuncTable"));
    ASSERT_NE((GpaCounterLib_GetFuncTablePtrType) nullptr, get_func_table_ptr);

    GpaCounterLibFuncTable gpa_counter_lib_func_table;
    GPA_Status             gpa_status = get_func_table_ptr(&gpa_counter_lib_func_table);
    EXPECT_EQ(GPA_STATUS_OK, gpa_status);

    GPA_CounterContext gpa_counter_context = nullptr;
    gpa_status                             = gpa_counter_lib_func_table.GpaCounterLib_OpenCounterContext(api,
                                                                             AMD_VENDOR_ID,
                                                                             generation_device_map[generation],
                                                                             REVISION_ID_ANY,
                                                                             GPA_OPENCONTEXT_DEFAULT_BIT,
                                                                             generateAsicSpecificCounters,
                                                                             &gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED, gpa_status);

    gpa_status = gpa_counter_lib_func_table.GpaCounterLib_CloseCounterContext(gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_OPEN, gpa_status);

    UnloadLib(libHandle);
}

void VerifyHardwareNotSupported(GPA_API_Type api, unsigned int deviceId, gpa_uint8 generateAsicSpecificCounters)
{
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle) nullptr, libHandle);
    GpaCounterLib_GetFuncTablePtrType get_func_table_ptr =
        reinterpret_cast<GpaCounterLib_GetFuncTablePtrType>(GetEntryPoint(libHandle, "GpaCounterLib_GetFuncTable"));
    ASSERT_NE((GpaCounterLib_GetFuncTablePtrType) nullptr, get_func_table_ptr);

    GpaCounterLibFuncTable gpa_counter_lib_func_table;
    GPA_Status             gpa_status = get_func_table_ptr(&gpa_counter_lib_func_table);
    EXPECT_EQ(GPA_STATUS_OK, gpa_status);

    GPA_CounterContext gpa_counter_context = nullptr;
    gpa_status                             = gpa_counter_lib_func_table.GpaCounterLib_OpenCounterContext(
        api, AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, GPA_OPENCONTEXT_DEFAULT_BIT, generateAsicSpecificCounters, &gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED, gpa_status);

    gpa_status = gpa_counter_lib_func_table.GpaCounterLib_CloseCounterContext(gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, gpa_status);

    UnloadLib(libHandle);
}

void VerifyHardwareNotSupported(GPA_API_Type api, GPA_Hw_Generation generation, gpa_uint8 generateAsicSpecificCounters)
{
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle) nullptr, libHandle);
    GpaCounterLib_GetFuncTablePtrType get_func_table_ptr =
        reinterpret_cast<GpaCounterLib_GetFuncTablePtrType>(GetEntryPoint(libHandle, "GpaCounterLib_GetFuncTable"));
    ASSERT_NE((GpaCounterLib_GetFuncTablePtrType) nullptr, get_func_table_ptr);

    GpaCounterLibFuncTable gpa_counter_lib_func_table;
    GPA_Status             gpa_status = get_func_table_ptr(&gpa_counter_lib_func_table);
    EXPECT_EQ(GPA_STATUS_OK, gpa_status);

    GPA_CounterContext gpa_counter_context = nullptr;
    gpa_status                             = gpa_counter_lib_func_table.GpaCounterLib_OpenCounterContext(api,
                                                                             AMD_VENDOR_ID,
                                                                             generation_device_map[generation],
                                                                             REVISION_ID_ANY,
                                                                             GPA_OPENCONTEXT_DEFAULT_BIT,
                                                                             generateAsicSpecificCounters,
                                                                             &gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED, gpa_status);

    gpa_status = gpa_counter_lib_func_table.GpaCounterLib_CloseCounterContext(gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, gpa_status);

    UnloadLib(libHandle);
}

void VerifyCounterNames(GPA_API_Type api, unsigned int deviceId, gpa_uint8 generateAsicSpecificCounters, std::vector<const char*> expectedNames)
{
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle) nullptr, libHandle);

    GpaCounterLib_GetFuncTablePtrType get_func_table_ptr =
        reinterpret_cast<GpaCounterLib_GetFuncTablePtrType>(GetEntryPoint(libHandle, "GpaCounterLib_GetFuncTable"));
    ASSERT_NE((GpaCounterLib_GetFuncTablePtrType) nullptr, get_func_table_ptr);

    GpaCounterLibFuncTable gpa_counter_lib_func_table;
    GPA_Status             gpa_status = get_func_table_ptr(&gpa_counter_lib_func_table);
    EXPECT_EQ(GPA_STATUS_OK, gpa_status);

    GPA_CounterContext gpa_counter_context = nullptr;
    gpa_status                             = gpa_counter_lib_func_table.GpaCounterLib_OpenCounterContext(
        api, AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, GPA_OPENCONTEXT_DEFAULT_BIT, generateAsicSpecificCounters, &gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_OK, gpa_status);

    gpa_uint32 numCounters = 0u;
    gpa_status             = gpa_counter_lib_func_table.GpaCounterLib_GetNumCounters(gpa_counter_context, &numCounters);
    EXPECT_EQ(GPA_STATUS_OK, gpa_status);
    EXPECT_EQ(expectedNames.size(), static_cast<gpa_uint32>(numCounters));

    if (expectedNames.size() == numCounters)
    {
        const char* temp_str = nullptr;
        for (unsigned int i = 0; i < numCounters; ++i)
        {
            gpa_counter_lib_func_table.GpaCounterLib_GetCounterName(gpa_counter_context, i, &temp_str);
            EXPECT_STREQ(expectedNames[i], temp_str);

            gpa_counter_lib_func_table.GpaCounterLib_GetCounterGroup(gpa_counter_context, i, &temp_str);
            EXPECT_NE((const char*)nullptr, temp_str);
            EXPECT_NE(0, strcmp("", temp_str));

            gpa_counter_lib_func_table.GpaCounterLib_GetCounterDescription(gpa_counter_context, i, &temp_str);
            EXPECT_NE((const char*)nullptr, temp_str);

#ifndef AMDT_INTERNAL
            EXPECT_NE(0, strcmp("", temp_str));
            // the format of the description used to be "#GROUP#counter description", but isn't any longer, so make sure the description does NOT start with '#'
            EXPECT_NE('#', temp_str[0]);
#endif
        }
    }

    gpa_status = gpa_counter_lib_func_table.GpaCounterLib_CloseCounterContext(gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_OK, gpa_status);
    UnloadLib(libHandle);
}

void VerifyCounterNames(GPA_API_Type api, GPA_Hw_Generation generation, gpa_uint8 generateAsicSpecificCounters, std::vector<const char*> expectedNames)
{
    VerifyCounterNames(api, generation_device_map[generation], generateAsicSpecificCounters, expectedNames);
}

void VerifyCounterLibInterface(GPA_API_Type                       api,
                               unsigned                           device_id,
                               unsigned                           revision_id,
                               gpa_uint8                          asic_specific,
                               std::vector<GpaDerivedCounterInfo> expected_derived_counter_list)
{
    UNREFERENCED_PARAMETER(expected_derived_counter_list);
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle) nullptr, libHandle);

    GpaCounterLib_GetFuncTablePtrType get_func_table_ptr =
        reinterpret_cast<GpaCounterLib_GetFuncTablePtrType>(GetEntryPoint(libHandle, "GpaCounterLib_GetFuncTable"));
    ASSERT_NE((GpaCounterLib_GetFuncTablePtrType) nullptr, get_func_table_ptr);

    GpaCounterLibFuncTable gpa_counter_lib_func_table;
    GPA_Status             gpa_status = get_func_table_ptr(&gpa_counter_lib_func_table);
    EXPECT_EQ(GPA_STATUS_OK, gpa_status);

    GPA_CounterContext gpa_counter_context = nullptr;

    {
        gpa_status = gpa_counter_lib_func_table.GpaCounterLib_OpenCounterContext(
            api, AMD_VENDOR_ID, device_id, revision_id, GPA_OPENCONTEXT_DEFAULT_BIT, asic_specific, &gpa_counter_context);
        EXPECT_EQ(GPA_STATUS_OK, gpa_status);

        const GpaDerivedCounterInfo* temp_ptr = nullptr;
        gpa_status                            = gpa_counter_lib_func_table.GpaCounterLib_GetDerivedCounterInfo(gpa_counter_context, 8, &temp_ptr);

        gpa_status = gpa_counter_lib_func_table.GpaCounterLib_CloseCounterContext(gpa_counter_context);
        EXPECT_EQ(GPA_STATUS_OK, gpa_status);
        gpa_counter_context = nullptr;
    }

    {
        gpa_status = gpa_counter_lib_func_table.GpaCounterLib_OpenCounterContext(api,
                                                                                 AMD_VENDOR_ID,
                                                                                 device_id,
                                                                                 revision_id,
                                                                                 GPA_OPENCONTEXT_DEFAULT_BIT | GPA_OPENCONTEXT_ENABLE_HARDWARE_COUNTERS_BIT,
                                                                                 asic_specific,
                                                                                 &gpa_counter_context);
        EXPECT_EQ(GPA_STATUS_OK, gpa_status);

        GpaCounterParam counter_param;
        counter_param.is_derived_counter = false;

        counter_param.gpa_hw_counter.gpa_hw_block          = GPA_HW_BLOCK_SQ;
        counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
        counter_param.gpa_hw_counter.gpa_hw_block_event_id = 4;
        counter_param.gpa_hw_counter.gpa_shader_mask       = GPA_SHADER_MASK_PS;

        gpa_uint32 index;
        gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param, &index);
        EXPECT_EQ(GPA_STATUS_OK, gpa_status);

        const char* temp_char = nullptr;
        gpa_status            = gpa_counter_lib_func_table.GpaCounterLib_GetCounterName(gpa_counter_context, index, &temp_char);
        EXPECT_EQ(GPA_STATUS_OK, gpa_status);

        counter_param.gpa_hw_counter.gpa_hw_block          = GPA_HW_BLOCK_SQ;
        counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
        counter_param.gpa_hw_counter.gpa_hw_block_event_id = 4;
        counter_param.gpa_hw_counter.gpa_shader_mask       = GPA_SHADER_MASK_ALL;

        gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param, &index);
        EXPECT_EQ(GPA_STATUS_OK, gpa_status);

        temp_char  = nullptr;
        gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterName(gpa_counter_context, index, &temp_char);
        EXPECT_EQ(GPA_STATUS_OK, gpa_status);

        counter_param.gpa_hw_counter.gpa_hw_block          = GPA_HW_BLOCK_SQ;
        counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
        counter_param.gpa_hw_counter.gpa_hw_block_event_id = 4;
        counter_param.gpa_hw_counter.gpa_shader_mask       = GPA_SHADER_MASK_LS;

        gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param, &index);
        EXPECT_EQ(GPA_STATUS_OK, gpa_status);

        temp_char  = nullptr;
        gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterName(gpa_counter_context, index, &temp_char);
        EXPECT_EQ(GPA_STATUS_OK, gpa_status);

        if (device_id == gDevIdGfx10)
        {
            counter_param.gpa_hw_counter.gpa_hw_block          = GPA_HW_BLOCK_GL1C;
            counter_param.gpa_hw_counter.gpa_hw_block_instance = 30; // Instance not available
            counter_param.gpa_hw_counter.gpa_hw_block_event_id = 14;
            counter_param.gpa_hw_counter.gpa_shader_mask       = GPA_SHADER_MASK_LS;

            gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param, &index);
            EXPECT_EQ(gpa_status, GPA_STATUS_ERROR_COUNTER_NOT_FOUND);

            counter_param.gpa_hw_counter.gpa_hw_block          = GPA_HW_BLOCK_GL1C;
            counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
            counter_param.gpa_hw_counter.gpa_hw_block_event_id = 14;
            counter_param.gpa_hw_counter.gpa_shader_mask       = GPA_SHADER_MASK_LS;

            gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param, &index);
            EXPECT_EQ(gpa_status, GPA_STATUS_OK);

            temp_char  = nullptr;
            gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterName(gpa_counter_context, index, &temp_char);
            EXPECT_EQ(gpa_status, GPA_STATUS_OK);
        }

        gpa_status = gpa_counter_lib_func_table.GpaCounterLib_CloseCounterContext(gpa_counter_context);
        EXPECT_EQ(GPA_STATUS_OK, gpa_status);
        gpa_counter_context = nullptr;
        UnloadLib(libHandle);
    }
}

void VerifyPassCount(GPA_API_Type                     api,
                     unsigned int                     deviceId,
                     gpa_uint8                        generateAsicSpecificCounters,
                     const std::vector<unsigned int>& countersToEnable,
                     unsigned int                     expectedNumPasses)
{
     LibHandle libHandle = LoadLib(countersLibName);
     ASSERT_NE((LibHandle) nullptr, libHandle);

     GpaCounterLib_GetFuncTablePtrType get_func_table_ptr =
         reinterpret_cast<GpaCounterLib_GetFuncTablePtrType>(GetEntryPoint(libHandle, "GpaCounterLib_GetFuncTable"));
     ASSERT_NE((GpaCounterLib_GetFuncTablePtrType) nullptr, get_func_table_ptr);

     GpaCounterLibFuncTable gpa_counter_lib_func_table;
     GPA_Status             gpa_status = get_func_table_ptr(&gpa_counter_lib_func_table);
     EXPECT_EQ(GPA_STATUS_OK, gpa_status);

     GPA_CounterContext gpa_counter_context = nullptr;
     gpa_status                             = gpa_counter_lib_func_table.GpaCounterLib_OpenCounterContext(
         api, AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, GPA_OPENCONTEXT_DEFAULT_BIT, generateAsicSpecificCounters, &gpa_counter_context);
     EXPECT_EQ(GPA_STATUS_OK, gpa_status);

     gpa_uint32 pass_count = 0u;
     gpa_status            = gpa_counter_lib_func_table.GpaCounterLib_GetPassCount(
         gpa_counter_context, countersToEnable.data(), static_cast<gpa_uint32>(countersToEnable.size()), &pass_count);
     EXPECT_EQ(expectedNumPasses, pass_count);

     gpa_status = gpa_counter_lib_func_table.GpaCounterLib_CloseCounterContext(gpa_counter_context);
     EXPECT_EQ(GPA_STATUS_OK, gpa_status);

     UnloadLib(libHandle);
}

void VerifyCountersInPass(GPA_API_Type                                                                      api,
                          unsigned int                                                                      deviceId,
                          gpa_uint8                                                                         generateAsicSpecificCounters,
                          const std::vector<unsigned int>&                                                  countersToEnable,
                          const std::vector<std::vector<unsigned int> >&                                    expectedHwCountersPerPass,
                          const std::map<unsigned int, std::map<unsigned int, GPA_CounterResultLocation> >& expectedResultLocations)
{
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle) nullptr, libHandle);
    UNREFERENCED_PARAMETER(api);
    UNREFERENCED_PARAMETER(deviceId);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);
    UNREFERENCED_PARAMETER(countersToEnable);
    UNREFERENCED_PARAMETER(expectedHwCountersPerPass);
    UNREFERENCED_PARAMETER(expectedResultLocations);
    //    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetEntryPoint(libHandle, "GPA_GetAvailableCounters");
    //
    //    if (nullptr != GPA_GetAvailableCounters_fn)
    //    {
    //        IGPACounterAccessor*  pCounterAccessor  = nullptr;
    //        IGPACounterScheduler* pCounterScheduler = nullptr;
    //
    //        // Get all the counters (based on API and the deviceID), an accessor, and a scheduler
    //        GPA_Status status = GPA_GetAvailableCounters_fn(
    //            api, AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, GPA_OPENCONTEXT_DEFAULT_BIT, generateAsicSpecificCounters, &pCounterAccessor, &pCounterScheduler);
    //
    //        EXPECT_EQ(GPA_STATUS_OK, status);
    //        EXPECT_NE((IGPACounterAccessor*)nullptr, pCounterAccessor);
    //        EXPECT_NE((IGPACounterScheduler*)nullptr, pCounterScheduler);
    //
    //        if (nullptr != pCounterScheduler)
    //        {
    //            pCounterScheduler->DisableAllCounters();
    //
    //            for (unsigned int i = 0; i < countersToEnable.size(); ++i)
    //            {
    //                GPA_Status enabled = pCounterScheduler->EnableCounter(countersToEnable[i]);
    //                EXPECT_EQ(GPA_STATUS_OK, enabled);
    //            }
    //
    //            gpa_uint32 requiredPasses = 0;
    //
    //            GPA_Status passCountStatus = pCounterScheduler->GetNumRequiredPasses(&requiredPasses);
    //            EXPECT_EQ(GPA_STATUS_OK, passCountStatus);
    //
    //            gpa_uint32 expectedNumPasses = (gpa_uint32)expectedHwCountersPerPass.size();
    //            EXPECT_EQ(expectedNumPasses, requiredPasses);
    //
    //            // make sure each pass has the expected set of hw counters
    //            for (unsigned int passIndex = 0; passIndex < expectedNumPasses; passIndex++)
    //            {
    //                std::vector<gpa_uint32>* pScheduledCountersInPass = pCounterScheduler->GetCountersForPass(passIndex);
    //
    //                if (!pScheduledCountersInPass)
    //                {
    //                    ADD_FAILURE();
    //                    return;
    //                }
    //
    //                const std::vector<unsigned int>& expectedCountersInPass = expectedHwCountersPerPass[passIndex];
    //
    //                // make sure the number of scheduled counters matches the expected number of scheduled counters
    //                if (expectedCountersInPass.size() != pScheduledCountersInPass->size())
    //                {
    //                    EXPECT_EQ(expectedCountersInPass.size(), pScheduledCountersInPass->size());
    //                    return;
    //                }
    //
    //                // make sure all the counters match what we expect
    //                for (unsigned int counterIndex = 0; counterIndex < expectedCountersInPass.size(); counterIndex++)
    //                {
    //                    if (expectedCountersInPass[counterIndex] != pScheduledCountersInPass->at(counterIndex))
    //                    {
    //                        EXPECT_EQ(expectedCountersInPass[counterIndex], pScheduledCountersInPass->at(counterIndex));
    //                        return;
    //                    }
    //                }
    //            }
    //
    //            EXPECT_EQ(expectedResultLocations.size(), countersToEnable.size());
    //
    //            std::map<unsigned int, GPA_CounterResultLocation>* pCounterResultLocation = nullptr;
    //
    //            for (unsigned int i = 0; i < countersToEnable.size(); ++i)
    //            {
    //                pCounterResultLocation = pCounterScheduler->GetCounterResultLocations(countersToEnable[i]);
    //                EXPECT_NE((void*)nullptr, pCounterResultLocation);
    //
    //                if (nullptr != pCounterResultLocation)
    //                {
    //                    const auto expectedResultiter = expectedResultLocations.find(countersToEnable[i]);
    //
    //                    if (expectedResultiter == expectedResultLocations.end())
    //                    {
    //                        // Counter not found in expected results
    //                        ADD_FAILURE();
    //                    }
    //
    //                    const std::map<unsigned int, GPA_CounterResultLocation> expectedResultLocation = expectedResultiter->second;
    //
    //                    EXPECT_EQ(expectedResultLocation.size(), pCounterResultLocation->size());
    //
    //                    if (expectedResultLocation.size() == pCounterResultLocation->size())
    //                    {
    //                        for (auto hardwareCounterIter = expectedResultLocation.begin(); hardwareCounterIter != expectedResultLocation.end();
    //                             hardwareCounterIter++)
    //                        {
    //                            unsigned int expectedOffset = hardwareCounterIter->second.m_offset;
    //                            unsigned int expectedPass   = hardwareCounterIter->second.m_pass;
    //
    //                            auto locationIter = pCounterResultLocation->find(hardwareCounterIter->first);
    //
    //                            if (pCounterResultLocation->end() != locationIter)
    //                            {
    //                                EXPECT_EQ(expectedOffset, locationIter->second.m_offset) << "Unexpected result offset for counter " << countersToEnable[i];
    //                                EXPECT_EQ(expectedPass, locationIter->second.m_pass) << "Unexpected result pass for counter " << countersToEnable[i];
    //                            }
    //                            else
    //                            {
    //                                // The locationIter should always be valid; if the code got here, that means a counter was not in the expected place
    //                                ADD_FAILURE();
    //                            }
    //                        }
    //                    }
    //                }
    //            }
    //
    //            // disable the counters
    //            pCounterScheduler->DisableAllCounters();
    //        }
    //    }
    //
    UnloadLib(libHandle);
}

//static void ExplainCounters(GPA_API_Type                 api,
//                            uint32_t                     deviceId,
//                            gpa_uint8                    generateAsicSpecificCounters,
//                            const std::vector<uint32_t>& countersToEnable,
//                            std::stringstream*           pOutputStream)
//{
//    LibHandle libHandle = LoadLib(countersLibName);
//    ASSERT_NE((LibHandle) nullptr, libHandle);
//    UNREFERENCED_PARAMETER(api);
//    UNREFERENCED_PARAMETER(deviceId);
//    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);git
//    UNREFERENCED_PARAMETER(countersToEnable);
//    UNREFERENCED_PARAMETER(pOutputStream);
//
//    //    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetEntryPoint(libHandle, "GPA_GetAvailableCounters");
////
////    if (nullptr != GPA_GetAvailableCounters_fn)
////    {
////        IGPACounterAccessor*  pCounterAccessor  = nullptr;
////        IGPACounterScheduler* pCounterScheduler = nullptr;
////
////        // Get all the counters (based on API and the deviceID), an accessor, and a scheduler
////        GPA_Status status = GPA_GetAvailableCounters_fn(
////            api, AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, GPA_OPENCONTEXT_DEFAULT_BIT, generateAsicSpecificCounters, &pCounterAccessor, &pCounterScheduler);
////
////        EXPECT_EQ(GPA_STATUS_OK, status);
////        EXPECT_NE((IGPACounterAccessor*)nullptr, pCounterAccessor);
////        EXPECT_NE((IGPACounterScheduler*)nullptr, pCounterScheduler);
////
////        if (nullptr != pCounterScheduler)
////        {
////            pCounterScheduler->DisableAllCounters();
////
////            for (unsigned int i = 0; i < countersToEnable.size(); ++i)
////            {
////                *pOutputStream << "Enabling public counter id: " << countersToEnable[i] << "\n";
////
////                GPA_Status enabled = pCounterScheduler->EnableCounter(countersToEnable[i]);
////                EXPECT_EQ(GPA_STATUS_OK, enabled);
////            }
////
////            gpa_uint32 requiredPasses = 0;
////
////            GPA_Status passCountStatus = pCounterScheduler->GetNumRequiredPasses(&requiredPasses);
////            EXPECT_EQ(GPA_STATUS_OK, passCountStatus);
////
////            *pOutputStream << "Expected number of passes: " << requiredPasses << "\n\n";
////
////            // make sure each pass has the expected set of hw counters
////            for (unsigned int passIndex = 0; passIndex < requiredPasses; passIndex++)
////            {
////                std::vector<gpa_uint32>* pScheduledCountersInPass = pCounterScheduler->GetCountersForPass(passIndex);
////
////                *pOutputStream << "// Pass: " << passIndex << "  Counters: " << pScheduledCountersInPass->size() << "\n";
////
////                *pOutputStream << "std::vector<uint32_t> expectedCountersPass" << passIndex << " =\n{\n    ";
////
////                // make sure all the counters match what we expect
////                for (unsigned int counterIndex = 0; counterIndex < pScheduledCountersInPass->size(); counterIndex++)
////                {
////                    if (counterIndex)
////                    {
////                        *pOutputStream << ", ";
////
////                        if (!(counterIndex % 10))
////                        {
////                            *pOutputStream << "\n    ";
////                        }
////                    }
////
////                    *pOutputStream << pScheduledCountersInPass->at(counterIndex);
////                }
////
////                *pOutputStream << "\n};\n\n";
////            }
////
////            *pOutputStream << "std::vector< std::vector<uint32_t> > expectedHwCountersPerPass =\n{\n";
////
////            for (unsigned int passIndex = 0; passIndex < requiredPasses; passIndex++)
////            {
////                *pOutputStream << "    expectedCountersPass" << passIndex << ",\n";
////            }
////
////            *pOutputStream << "};\n\n";
////
////            std::map<unsigned int, GPA_CounterResultLocation>* pCounterResultLocation = nullptr;
////
////            *pOutputStream << "\n// Result locations (Pass, Offset)\n\n";
////
////            for (unsigned int i = 0; i < countersToEnable.size(); ++i)
////            {
////                *pOutputStream << "// Pass: " << i << "  Counters: " << countersToEnable[i] << "\n";
////
////                *pOutputStream << "std::map<uint32_t, GPA_CounterResultLocation> expectedLocations" << i << "\n{\n";
////
////                pCounterResultLocation = pCounterScheduler->GetCounterResultLocations(countersToEnable[i]);
////                EXPECT_NE((void*)nullptr, pCounterResultLocation);
////
////                if (nullptr != pCounterResultLocation)
////                {
////                    for (auto hardwareCounterIter = pCounterResultLocation->begin(); hardwareCounterIter != pCounterResultLocation->end();
////                         hardwareCounterIter++)
////                    {
////                        unsigned int expectedOffset = hardwareCounterIter->second.m_offset;
////                        unsigned int expectedPass   = hardwareCounterIter->second.m_pass;
////
////                        *pOutputStream << "    MakeExpectedCounterLocationEntry(" << expectedPass << ", " << expectedOffset << ")\n";
////
////                        auto locationIter = pCounterResultLocation->find(hardwareCounterIter->first);
////
////                        if (pCounterResultLocation->end() != locationIter)
////                        {
////                            EXPECT_EQ(expectedOffset, locationIter->second.m_offset) << "Unexpected result offset for counter " << countersToEnable[i];
////                            EXPECT_EQ(expectedPass, locationIter->second.m_pass) << "Unexpected result pass for counter " << countersToEnable[i];
////                        }
////                        else
////                        {
////                            // The locationIter should always be valid; if the code got here, that means a counter was not in the expected place
////                            ADD_FAILURE();
////                        }
////                    }
////                }
////
////                *pOutputStream << "};\n\n";
////            }
////
////            *pOutputStream << "std::map< uint32_t, std::map<uint32_t, GPA_CounterResultLocation> > expectedResultLocations = \n{\n";
////
////            for (unsigned int i = 0; i < countersToEnable.size(); ++i)
////            {
////                *pOutputStream << "    expectedLocations" << i << ",\n";
////            }
////
////            *pOutputStream << "};\n\n";
////
////            // disable the counters
////            pCounterScheduler->DisableAllCounters();
////
////            *pOutputStream << "\n";
////        }
////    }
////
//    UnloadLib(libHandle);
//}

//void ExplainCountersInPassAndResultLocations(GPA_API_Type                 api,
//                                             uint32_t                     deviceId,
//                                             gpa_uint8                    generateAsicSpecificCounters,
//                                             const std::vector<uint32_t>& countersToEnable,
//                                             std::stringstream*           pOutputStream)
//{
//    *pOutputStream << "Total number of counters:" << countersToEnable.size() << "\n\n";
//
//    if (countersToEnable.empty())
//    {
//        return;
//    }
//
//    if (countersToEnable.size() > 1)
//    {
//        for (size_t i = 0; i < countersToEnable.size(); ++i)
//        {
//            *pOutputStream << "*** Explaining counter " << (i + 1) << " of " << countersToEnable.size() << " ***\n";
//
//            ExplainCounters(api, deviceId, generateAsicSpecificCounters, std::vector<uint32_t>{countersToEnable[i]}, pOutputStream);
//        }
//    }
//
//    *pOutputStream << "*** Explaining combined counters ***\n";
//    ExplainCounters(api, deviceId, generateAsicSpecificCounters, countersToEnable, pOutputStream);
//}

void VerifyCounterCalculation(GPA_API_Type                          api,
                              unsigned int                          deviceId,
                              gpa_uint8                             generateAsicSpecificCounters,
                              char*                                 counterName,
                              const std::vector<const gpa_uint64*>& sampleResults,
                              gpa_float64                           expectedResult)
{
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle) nullptr, libHandle);
    UNREFERENCED_PARAMETER(api);
    UNREFERENCED_PARAMETER(deviceId);
    UNREFERENCED_PARAMETER(generateAsicSpecificCounters);
    UNREFERENCED_PARAMETER(counterName);
    UNREFERENCED_PARAMETER(sampleResults);
    UNREFERENCED_PARAMETER(expectedResult);
    //    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetEntryPoint(libHandle, "GPA_GetAvailableCounters");
    //
    //    if (nullptr != GPA_GetAvailableCounters_fn)
    //    {
    //        IGPACounterAccessor*  pCounterAccessor  = nullptr;
    //        IGPACounterScheduler* pCounterScheduler = nullptr;
    //        GPA_Status            status            = GPA_GetAvailableCounters_fn(
    //            api, AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, GPA_OPENCONTEXT_DEFAULT_BIT, generateAsicSpecificCounters, &pCounterAccessor, &pCounterScheduler);
    //        EXPECT_EQ(GPA_STATUS_OK, status);
    //        EXPECT_NE((IGPACounterAccessor*)nullptr, pCounterAccessor);
    //        EXPECT_NE((IGPACounterScheduler*)nullptr, pCounterScheduler);
    //
    //        if (nullptr != pCounterScheduler)
    //        {
    //            std::vector<GPA_Data_Type> internalCounterTypes;
    //            gpa_float64                result = 0;
    //            GPA_HWInfo                 hwInfo;  ///< TODO ? Find this from the scheduler
    //
    //            size_t numResults = sampleResults.size();
    //
    //            for (size_t i = 0; i < numResults; i++)
    //            {
    //                internalCounterTypes.push_back(GPA_DATA_TYPE_UINT64);
    //            }
    //
    //            gpa_uint32 numCounters = pCounterAccessor->GetNumCounters();
    //
    //            gpa_uint32 counterIndex = gpa_uint32(-1);
    //
    //            for (gpa_uint32 i = 0; i < numCounters; i++)
    //            {
    //                if (strcmp(pCounterAccessor->GetCounterName(i), counterName) == 0)
    //                {
    //                    counterIndex = i;
    //                    break;
    //                }
    //            }
    //
    //            status = pCounterAccessor->ComputePublicCounterValue(counterIndex, sampleResults, internalCounterTypes, &result, &hwInfo);
    //            EXPECT_EQ(GPA_STATUS_OK, status);
    //
    //            EXPECT_EQ(expectedResult, result);
    //
    //            // disable the counters
    //            pCounterScheduler->DisableAllCounters();
    //        }
    //    }
    //
    UnloadLib(libHandle);
}
