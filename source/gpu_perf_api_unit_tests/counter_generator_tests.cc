//==============================================================================
// Copyright (c) 2012-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Helper functions for Counter Generator Unit Tests
//==============================================================================

#include <map>
#include <algorithm>

#include "counter_generator_tests.h"
#include "gpu_perf_api_types.h"
#include "gpa_hw_info.h"
#include "gpa_split_counters_interfaces.h"

#ifdef _WIN32
const char* countersLibName = "GPUPerfAPICounters" AMDT_PLATFORM_SUFFIX AMDT_DEBUG_SUFFIX AMDT_BUILD_SUFFIX ".dll";
#else
const char* countersLibName = "libGPUPerfAPICounters" AMDT_PLATFORM_SUFFIX AMDT_DEBUG_SUFFIX AMDT_BUILD_SUFFIX ".so";
#endif

#define LOAD_AND_VERIFY_COUNTER_LIB(lib_handle, fn_table)                                                              \
    *lib_handle = LoadLib(countersLibName);                                                                            \
    ASSERT_NE((LibHandle) nullptr, *lib_handle);                                                                       \
                                                                                                                       \
    GpaCounterLib_GetFuncTablePtrType get_func_table_ptr =                                                             \
        reinterpret_cast<GpaCounterLib_GetFuncTablePtrType>(GetEntryPoint(*lib_handle, "GpaCounterLib_GetFuncTable")); \
    ASSERT_NE((GpaCounterLib_GetFuncTablePtrType) nullptr, get_func_table_ptr);                                        \
                                                                                                                       \
    GPA_Status gpa_status = get_func_table_ptr(fn_table);                                                              \
    EXPECT_EQ(GPA_STATUS_OK, gpa_status)

LibHandle LoadLib(const char* pLibName)
{
    LibHandle retVal = nullptr;
#ifdef _WIN32
    // raise an error if the library is already loaded
    retVal = GetModuleHandleA(pLibName);
    EXPECT_TRUE(retVal == nullptr);
    retVal = LoadLibraryA(pLibName);
#else
    // raise an error if the library is already loaded
    retVal = dlopen(pLibName, RTLD_NOLOAD);
    EXPECT_TRUE(retVal == nullptr);
    retVal    = dlopen(pLibName, RTLD_NOW);
#endif
    EXPECT_TRUE(retVal != nullptr);
    return retVal;
}

static std::map<GPA_Hw_Generation, unsigned int> generation_device_map = {{GPA_HW_GENERATION_NONE, 0},
                                                                          {GPA_HW_GENERATION_NVIDIA, 0},
                                                                          {GPA_HW_GENERATION_INTEL, 0},
                                                                          {GPA_HW_GENERATION_GFX6, gDevIdSI},
                                                                          {GPA_HW_GENERATION_GFX7, gDevIdCI},
                                                                          {GPA_HW_GENERATION_GFX8, gDevIdGfx8},
                                                                          {GPA_HW_GENERATION_GFX9, gDevIdGfx9},
                                                                          {GPA_HW_GENERATION_GFX10, gDevIdGfx10},
                                                                          {GPA_HW_GENERATION_GFX103, gDevIdGfx10_3}};

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

void VerifyDerivedCounterCount(const GPA_API_Type                api,
                               GPA_Hw_Generation                 generation,
                               const gpa_uint8                   generate_asic_specific_counters,
                               const std::vector<GPACounterDesc> counter_descriptions)
{
    LibHandle                     lib_handle                    = nullptr;
    const GpaCounterInfo*         counter_info                  = nullptr;
    GPA_Status                    status                        = GPA_STATUS_OK;
    GpaCounterLibFuncTable        fn_table                      = {};
    GPA_CounterContext            counter_context               = {};
    GpaCounterParam               counter_parameters            = {};
    gpa_uint32                    counter_index                 = 0;
    GpaCounterContextHardwareInfo counter_context_hardware_info = {AMD_VENDOR_ID, generation_device_map[generation], REVISION_ID_ANY, nullptr, 0};

    LOAD_AND_VERIFY_COUNTER_LIB(&lib_handle, &fn_table);

    status = fn_table.GpaCounterLib_OpenCounterContext(
        api, counter_context_hardware_info, GPA_OPENCONTEXT_DEFAULT_BIT, generate_asic_specific_counters, &counter_context);
    EXPECT_EQ(GPA_STATUS_OK, status);

    // Verify the internal counter count
    counter_parameters.is_derived_counter = true;
    for (const auto& counter_desc : counter_descriptions)
    {
        // Set counter parameters
        counter_parameters.derived_counter_name = counter_desc.m_pName;
        status                                  = fn_table.GpaCounterLib_GetCounterIndex(counter_context, &counter_parameters, &counter_index);
        EXPECT_EQ(GPA_STATUS_OK, status);

        // Get counter information
        status = fn_table.GpaCounterLib_GetCounterInfo(counter_context, counter_index, &counter_info);
        EXPECT_EQ(GPA_STATUS_OK, status);

        EXPECT_EQ(counter_info->gpa_derived_counter->gpa_hw_counter_count, counter_desc.m_internalCounterCount);
    }

    UnloadLib(lib_handle);
}

void VerifyNotImplemented(GPA_API_Type api, unsigned int deviceId, gpa_uint8 generateAsicSpecificCounters)
{
    LibHandle              libHandle                  = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    LOAD_AND_VERIFY_COUNTER_LIB(&libHandle, &gpa_counter_lib_func_table);

    GPA_CounterContext            gpa_counter_context           = nullptr;
    GpaCounterContextHardwareInfo counter_context_hardware_info = {AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, nullptr, 0};
    gpa_status                                                  = gpa_counter_lib_func_table.GpaCounterLib_OpenCounterContext(
        api, counter_context_hardware_info, GPA_OPENCONTEXT_DEFAULT_BIT, generateAsicSpecificCounters, &gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED, gpa_status);

    gpa_status = gpa_counter_lib_func_table.GpaCounterLib_CloseCounterContext(gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_OPEN, gpa_status);

    UnloadLib(libHandle);
}

void VerifyNotImplemented(GPA_API_Type api, GPA_Hw_Generation generation, gpa_uint8 generateAsicSpecificCounters)
{
    LibHandle              libHandle                  = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    LOAD_AND_VERIFY_COUNTER_LIB(&libHandle, &gpa_counter_lib_func_table);

    GPA_CounterContext            gpa_counter_context           = nullptr;
    GpaCounterContextHardwareInfo counter_context_hardware_info = {AMD_VENDOR_ID, generation_device_map[generation], REVISION_ID_ANY, nullptr, 0};
    gpa_status                                                  = gpa_counter_lib_func_table.GpaCounterLib_OpenCounterContext(
        api, counter_context_hardware_info, GPA_OPENCONTEXT_DEFAULT_BIT, generateAsicSpecificCounters, &gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED, gpa_status);

    gpa_status = gpa_counter_lib_func_table.GpaCounterLib_CloseCounterContext(gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_ERROR_CONTEXT_NOT_OPEN, gpa_status);

    UnloadLib(libHandle);
}

void VerifyHardwareNotSupported(GPA_API_Type api, unsigned int deviceId, gpa_uint8 generateAsicSpecificCounters)
{
    LibHandle              libHandle                  = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    LOAD_AND_VERIFY_COUNTER_LIB(&libHandle, &gpa_counter_lib_func_table);

    GPA_CounterContext            gpa_counter_context           = nullptr;
    GpaCounterContextHardwareInfo counter_context_hardware_info = {AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, nullptr, 0};
    gpa_status                                                  = gpa_counter_lib_func_table.GpaCounterLib_OpenCounterContext(
        api, counter_context_hardware_info, GPA_OPENCONTEXT_DEFAULT_BIT, generateAsicSpecificCounters, &gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED, gpa_status);

    gpa_status = gpa_counter_lib_func_table.GpaCounterLib_CloseCounterContext(gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, gpa_status);

    UnloadLib(libHandle);
}

void VerifyHardwareNotSupported(GPA_API_Type api, GPA_Hw_Generation generation, gpa_uint8 generateAsicSpecificCounters)
{
    LibHandle              libHandle                  = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    LOAD_AND_VERIFY_COUNTER_LIB(&libHandle, &gpa_counter_lib_func_table);

    GPA_CounterContext            gpa_counter_context           = nullptr;
    GpaCounterContextHardwareInfo counter_context_hardware_info = {AMD_VENDOR_ID, generation_device_map[generation], REVISION_ID_ANY, nullptr, 0};
    gpa_status                                                  = gpa_counter_lib_func_table.GpaCounterLib_OpenCounterContext(
        api, counter_context_hardware_info, GPA_OPENCONTEXT_DEFAULT_BIT, generateAsicSpecificCounters, &gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED, gpa_status);

    gpa_status = gpa_counter_lib_func_table.GpaCounterLib_CloseCounterContext(gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_ERROR_NULL_POINTER, gpa_status);

    UnloadLib(libHandle);
}

void VerifyCounterNames(GPA_API_Type api, unsigned int deviceId, gpa_uint8 generateAsicSpecificCounters, std::vector<const char*> expectedNames)
{
    LibHandle              libHandle                  = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    LOAD_AND_VERIFY_COUNTER_LIB(&libHandle, &gpa_counter_lib_func_table);

    GPA_CounterContext            gpa_counter_context           = nullptr;
    GpaCounterContextHardwareInfo counter_context_hardware_info = {AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, nullptr, 0};
    gpa_status                                                  = gpa_counter_lib_func_table.GpaCounterLib_OpenCounterContext(
        api, counter_context_hardware_info, GPA_OPENCONTEXT_DEFAULT_BIT, generateAsicSpecificCounters, &gpa_counter_context);
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
    assert(generation_device_map.size() == GDT_HW_GENERATION_LAST);
    VerifyCounterNames(api, generation_device_map[generation], generateAsicSpecificCounters, expectedNames);
}

void VerifyCounterLibInterface(GPA_API_Type                       api,
                               unsigned                           device_id,
                               unsigned                           revision_id,
                               gpa_uint8                          asic_specific,
                               std::vector<GpaDerivedCounterInfo> expected_derived_counter_list)
{
    UNREFERENCED_PARAMETER(expected_derived_counter_list);

    LibHandle              libHandle                  = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    LOAD_AND_VERIFY_COUNTER_LIB(&libHandle, &gpa_counter_lib_func_table);

    GPA_CounterContext gpa_counter_context = nullptr;

    {
        if (device_id == gDevIdGfx10_3)
        {
            GpaCounterContextHardwareInfo counter_context_hardware_info = {AMD_VENDOR_ID, device_id, revision_id, nullptr, 0};
            gpa_status                                                  = gpa_counter_lib_func_table.GpaCounterLib_OpenCounterContext(api,
                                                                                     counter_context_hardware_info,
                                                                                     GPA_OPENCONTEXT_DEFAULT_BIT | GPA_OPENCONTEXT_ENABLE_HARDWARE_COUNTERS_BIT,
                                                                                     asic_specific,
                                                                                     &gpa_counter_context);
            EXPECT_EQ(GPA_STATUS_OK, gpa_status);

            GpaCounterParam counter_param;
            gpa_uint32      index                              = 0;
            counter_param.is_derived_counter                   = false;
            counter_param.gpa_hw_counter.gpa_hw_block          = GPA_HW_BLOCK_GL2C;
            counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
            counter_param.gpa_hw_counter.gpa_hw_block_event_id = 43;
            //counter.gpa_hw_counter.gpa_shader_mask       = GPA_SHADER_MASK_ALL;

            gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param, &index);
            EXPECT_EQ(gpa_status, GPA_STATUS_OK);

            const char* temp_char = nullptr;
            gpa_status            = gpa_counter_lib_func_table.GpaCounterLib_GetCounterName(gpa_counter_context, index, &temp_char);
            EXPECT_EQ(gpa_status, GPA_STATUS_OK);

            gpa_status = gpa_counter_lib_func_table.GpaCounterLib_CloseCounterContext(gpa_counter_context);
            EXPECT_EQ(GPA_STATUS_OK, gpa_status);
            gpa_counter_context = nullptr;
        }
    }

    {
        GpaCounterContextHardwareInfo counter_context_hardware_info = {AMD_VENDOR_ID, device_id, revision_id, nullptr, 0};
        gpa_status                                                  = gpa_counter_lib_func_table.GpaCounterLib_OpenCounterContext(
            api, counter_context_hardware_info, GPA_OPENCONTEXT_DEFAULT_BIT, asic_specific, &gpa_counter_context);
        EXPECT_EQ(GPA_STATUS_OK, gpa_status);

        const GpaCounterInfo* temp_ptr = nullptr;
        gpa_status                     = gpa_counter_lib_func_table.GpaCounterLib_GetCounterInfo(gpa_counter_context, 8, &temp_ptr);

        if (GPA_API_DIRECTX_11 == api || GPA_API_OPENGL == api || GPA_API_DIRECTX_12 == api || GPA_API_DIRECTX_12 == api)
        {
            {
                // Graphics SQ-derived counters use a shader mask
                GpaCounterParam counter_param;
                counter_param.is_derived_counter   = true;
                counter_param.derived_counter_name = "VSVALUInstCount";
                gpa_uint32 counter_index           = 0;
                gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param, &counter_index);
                EXPECT_EQ(GPA_STATUS_OK, gpa_status);
                gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterInfo(gpa_counter_context, counter_index, &temp_ptr);
                EXPECT_EQ(GPA_STATUS_OK, gpa_status);
                EXPECT_TRUE(temp_ptr->is_derived_counter);
                for (gpa_uint32 i = 0; i < temp_ptr->gpa_derived_counter->gpa_hw_counter_count; i++)
                {
                    EXPECT_TRUE(GPA_SHADER_MASK_PS <= temp_ptr->gpa_derived_counter->gpa_hw_counters[i].gpa_shader_mask &&
                                GPA_SHADER_MASK_CS >= temp_ptr->gpa_derived_counter->gpa_hw_counters[i].gpa_shader_mask);
                }
            }

            {
                GpaCounterParam counter_param;
                counter_param.is_derived_counter   = true;
                counter_param.derived_counter_name = "VSTime";
                gpa_uint32 counter_index           = 0;
                gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param, &counter_index);
                EXPECT_EQ(GPA_STATUS_OK, gpa_status);
                gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterInfo(gpa_counter_context, counter_index, &temp_ptr);
                EXPECT_EQ(GPA_STATUS_OK, gpa_status);
                EXPECT_TRUE(temp_ptr->is_derived_counter);

                bool does_gpu_time_block_exist = false;
                for (gpa_uint32 i = 0; i < temp_ptr->gpa_derived_counter->gpa_hw_counter_count; i++)
                {
                    does_gpu_time_block_exist |= temp_ptr->gpa_derived_counter->gpa_hw_counters[i].is_timing_block;
                }

                EXPECT_TRUE(does_gpu_time_block_exist);
            }
        }
        else if (GPA_API_OPENCL == api)
        {
            // OpenCL SQ-derived counters do not use a shader mask
            GpaCounterParam counter_param;
            counter_param.is_derived_counter   = true;
            counter_param.derived_counter_name = "VALUInsts";
            gpa_uint32 counter_index           = 0;
            gpa_status                         = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param, &counter_index);
            EXPECT_EQ(GPA_STATUS_OK, gpa_status);
            gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterInfo(gpa_counter_context, counter_index, &temp_ptr);
            EXPECT_EQ(GPA_STATUS_OK, gpa_status);
            EXPECT_TRUE(temp_ptr->is_derived_counter);
            for (gpa_uint32 i = 0; i < temp_ptr->gpa_derived_counter->gpa_hw_counter_count; i++)
            {
                EXPECT_TRUE(GPA_SHADER_MASK_ALL == temp_ptr->gpa_derived_counter->gpa_hw_counters[i].gpa_shader_mask);
            }
        }

        gpa_status = gpa_counter_lib_func_table.GpaCounterLib_CloseCounterContext(gpa_counter_context);
        EXPECT_EQ(GPA_STATUS_OK, gpa_status);
        gpa_counter_context = nullptr;
    }

    {
        GpaCounterContextHardwareInfo counter_context_hardware_info = {AMD_VENDOR_ID, device_id, revision_id, nullptr, 0};
        gpa_status                                                  = gpa_counter_lib_func_table.GpaCounterLib_OpenCounterContext(api,
                                                                                 counter_context_hardware_info,
                                                                                 GPA_OPENCONTEXT_DEFAULT_BIT | GPA_OPENCONTEXT_ENABLE_HARDWARE_COUNTERS_BIT,
                                                                                 asic_specific,
                                                                                 &gpa_counter_context);
        EXPECT_EQ(GPA_STATUS_OK, gpa_status);

        {
            GpaCounterParam counter_param;
            counter_param.is_derived_counter = false;

            counter_param.gpa_hw_counter.gpa_hw_block          = GPA_HW_BLOCK_SQ;
            counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
            counter_param.gpa_hw_counter.gpa_hw_block_event_id = 4;
            counter_param.gpa_hw_counter.gpa_shader_mask       = GPA_SHADER_MASK_PS;

            gpa_uint32 index = 0;
            gpa_status       = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param, &index);
            EXPECT_EQ(GPA_STATUS_OK, gpa_status);

            const char* temp_char = nullptr;
            gpa_status            = gpa_counter_lib_func_table.GpaCounterLib_GetCounterName(gpa_counter_context, index, &temp_char);
            EXPECT_EQ(GPA_STATUS_OK, gpa_status);

            gpa_uint32      index2 = 0;
            GpaCounterParam counter_param2;
            counter_param2.is_derived_counter   = true;
            counter_param2.derived_counter_name = temp_char;
            gpa_status                          = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param2, &index2);
            if (index != index2)
            {
                std::cout << "Index1 " << index << " counter name " << temp_char << " doesn't match with " << index2 << "and gpa status is " << gpa_status
                          << std::endl;
            }
            EXPECT_EQ(index, index2);

            const GpaCounterInfo* temp_ptr = nullptr;
            gpa_counter_lib_func_table.GpaCounterLib_GetCounterInfo(gpa_counter_context, index2, &temp_ptr);
            EXPECT_FALSE(temp_ptr->is_derived_counter);
            EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block, counter_param.gpa_hw_counter.gpa_hw_block);
            EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block_instance, counter_param.gpa_hw_counter.gpa_hw_block_instance);
            EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block_event_id, counter_param.gpa_hw_counter.gpa_hw_block_event_id);
            EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_shader_mask, counter_param.gpa_hw_counter.gpa_shader_mask);
        }

        {
            GpaCounterParam counter_param;
            counter_param.is_derived_counter                   = false;
            counter_param.gpa_hw_counter.gpa_hw_block          = GPA_HW_BLOCK_SQ;
            counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
            counter_param.gpa_hw_counter.gpa_hw_block_event_id = 4;
            counter_param.gpa_hw_counter.gpa_shader_mask       = GPA_SHADER_MASK_ALL;

            gpa_uint32 index = 0u;
            gpa_status       = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param, &index);
            EXPECT_EQ(GPA_STATUS_OK, gpa_status);

            const char* temp_char = nullptr;
            gpa_status            = gpa_counter_lib_func_table.GpaCounterLib_GetCounterName(gpa_counter_context, index, &temp_char);
            EXPECT_EQ(GPA_STATUS_OK, gpa_status);

            gpa_uint32      index2 = 0u;
            GpaCounterParam counter_param2;
            counter_param2.is_derived_counter   = true;
            counter_param2.derived_counter_name = temp_char;
            const GpaCounterInfo* temp_ptr      = nullptr;
            gpa_status                          = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param2, &index2);
            EXPECT_EQ(index, index2);
            gpa_counter_lib_func_table.GpaCounterLib_GetCounterInfo(gpa_counter_context, index2, &temp_ptr);
            EXPECT_FALSE(temp_ptr->is_derived_counter);
            EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block, counter_param.gpa_hw_counter.gpa_hw_block);
            EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block_instance, counter_param.gpa_hw_counter.gpa_hw_block_instance);
            EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block_event_id, counter_param.gpa_hw_counter.gpa_hw_block_event_id);
            EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_shader_mask, counter_param.gpa_hw_counter.gpa_shader_mask);

            counter_param.gpa_hw_counter.gpa_hw_block          = GPA_HW_BLOCK_SQ;
            counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
            counter_param.gpa_hw_counter.gpa_hw_block_event_id = 4;
            counter_param.gpa_hw_counter.gpa_shader_mask       = GPA_SHADER_MASK_LS;

            gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param, &index);
            EXPECT_EQ(GPA_STATUS_OK, gpa_status);

            temp_char  = nullptr;
            gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterName(gpa_counter_context, index, &temp_char);
            EXPECT_EQ(GPA_STATUS_OK, gpa_status);

            counter_param2.derived_counter_name = temp_char;
            gpa_status                          = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param2, &index2);
            EXPECT_EQ(index, index2);
            gpa_counter_lib_func_table.GpaCounterLib_GetCounterInfo(gpa_counter_context, index2, &temp_ptr);
            EXPECT_FALSE(temp_ptr->is_derived_counter);
            EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block, counter_param.gpa_hw_counter.gpa_hw_block);
            EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block_instance, counter_param.gpa_hw_counter.gpa_hw_block_instance);
            EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block_event_id, counter_param.gpa_hw_counter.gpa_hw_block_event_id);
            EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_shader_mask, counter_param.gpa_hw_counter.gpa_shader_mask);
        }

        if (device_id == gDevIdGfx10)
        {
            GpaCounterParam counter_param;
            counter_param.is_derived_counter                   = false;
            counter_param.gpa_hw_counter.gpa_hw_block          = GPA_HW_BLOCK_GL1C;
            counter_param.gpa_hw_counter.gpa_hw_block_instance = 33;  // Instance not available
            counter_param.gpa_hw_counter.gpa_hw_block_event_id = 14;
            counter_param.gpa_hw_counter.gpa_shader_mask       = GPA_SHADER_MASK_LS;

            gpa_uint32 index = 0u;
            gpa_status       = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param, &index);
            EXPECT_EQ(gpa_status, GPA_STATUS_ERROR_COUNTER_NOT_FOUND);

            counter_param.gpa_hw_counter.gpa_hw_block          = GPA_HW_BLOCK_GL1C;
            counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
            counter_param.gpa_hw_counter.gpa_hw_block_event_id = 14;
            counter_param.gpa_hw_counter.gpa_shader_mask       = GPA_SHADER_MASK_LS;

            gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param, &index);
            EXPECT_EQ(gpa_status, GPA_STATUS_OK);

            const char* temp_char = nullptr;
            gpa_status            = gpa_counter_lib_func_table.GpaCounterLib_GetCounterName(gpa_counter_context, index, &temp_char);
            EXPECT_EQ(gpa_status, GPA_STATUS_OK);

            GpaCounterParam counter_param2;
            counter_param2.is_derived_counter   = true;
            counter_param2.derived_counter_name = temp_char;
            gpa_uint32 index2                   = 0u;
            gpa_status                          = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param2, &index2);
            EXPECT_EQ(index, index2);

            const GpaCounterInfo* temp_ptr = nullptr;
            gpa_counter_lib_func_table.GpaCounterLib_GetCounterInfo(gpa_counter_context, index2, &temp_ptr);
            EXPECT_FALSE(temp_ptr->is_derived_counter);
            EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block, counter_param.gpa_hw_counter.gpa_hw_block);
            EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block_instance, counter_param.gpa_hw_counter.gpa_hw_block_instance);
            EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_hw_block_event_id, counter_param.gpa_hw_counter.gpa_hw_block_event_id);
            EXPECT_EQ(temp_ptr->gpa_hw_counter->gpa_shader_mask,
                      GPA_SHADER_MASK_ALL);  // check for GPA_SHADER_MASK_ALL since the only the SQ block supports the shader mask
        }

        if (device_id == gDevIdGfx10_3)
        {
            GpaCounterParam counter_param;
            counter_param.is_derived_counter                   = false;
            counter_param.gpa_hw_counter.gpa_hw_block          = GPA_HW_BLOCK_GL2C;
            counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
            counter_param.gpa_hw_counter.gpa_hw_block_event_id = 43;
            //counter.gpa_hw_counter.gpa_shader_mask       = GPA_SHADER_MASK_ALL;

            gpa_uint32 index = 0u;
            gpa_status       = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param, &index);
            EXPECT_EQ(gpa_status, GPA_STATUS_OK);

            const char* temp_char = nullptr;
            gpa_status            = gpa_counter_lib_func_table.GpaCounterLib_GetCounterName(gpa_counter_context, index, &temp_char);
            EXPECT_EQ(gpa_status, GPA_STATUS_OK);
        }

        gpa_status = gpa_counter_lib_func_table.GpaCounterLib_CloseCounterContext(gpa_counter_context);
        EXPECT_EQ(GPA_STATUS_OK, gpa_status);
        gpa_counter_context = nullptr;
    }

    UnloadLib(libHandle);
    libHandle = nullptr;
}

void VerifyCounterByPassCounterLibEntry(GPA_API_Type api, unsigned device_id, unsigned revision_id, gpa_uint8 asic_specific)
{
    if (device_id == gDevIdVI)
    {
        return;
    }

    if (GPA_API_OPENCL == api)
    {
        return;
    }

    LibHandle              libHandle                  = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    LOAD_AND_VERIFY_COUNTER_LIB(&libHandle, &gpa_counter_lib_func_table);

    GPA_CounterContext gpa_counter_context = nullptr;

    auto GetPassCounters = [&](GPA_CounterContext gpa_counter_context,
                               gpa_uint32         counter_count,
                               gpa_uint32*        derived_counter_list) -> std::map<unsigned int, std::vector<unsigned int>> {
        std::map<unsigned int, std::vector<unsigned int>> pass_counter_map;
        gpa_uint32                                        pass_count;
        gpa_status =
            gpa_counter_lib_func_table.GpaCounterLib_GetCountersByPass(gpa_counter_context, counter_count, derived_counter_list, &pass_count, nullptr, nullptr);

        if (GPA_STATUS_OK == gpa_status)
        {
            if (pass_count > 0)
            {
                gpa_uint32* counter_list = new (std::nothrow) gpa_uint32[pass_count];

                if (nullptr != counter_list)
                {
                    gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCountersByPass(
                        gpa_counter_context, counter_count, derived_counter_list, &pass_count, counter_list, nullptr);

                    GpaPassCounter* pass_counters = new (std::nothrow) GpaPassCounter[pass_count];

                    if (nullptr != pass_counters)
                    {
                        for (unsigned int i = 0; i < pass_count; i++)
                        {
                            pass_counters[i].pass_index      = i;
                            pass_counters[i].counter_count   = counter_list[i];
                            pass_counters[i].counter_indices = new (std::nothrow) gpa_uint32[counter_list[i]];
                        }

                        gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCountersByPass(
                            gpa_counter_context, counter_count, derived_counter_list, &pass_count, nullptr, pass_counters);

                        if (GPA_STATUS_OK == gpa_status)
                        {
                            for (unsigned int i = 0; i < pass_count; i++)
                            {
                                std::vector<unsigned int> counter_list_vec;
                                counter_list_vec.resize(pass_counters[i].counter_count);
                                memcpy(counter_list_vec.data(), pass_counters[i].counter_indices, sizeof(gpa_uint32) * pass_counters[i].counter_count);
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

    GpaCounterContextHardwareInfo counter_context_hardware_info = {AMD_VENDOR_ID, device_id, revision_id, nullptr, 0};
    gpa_status                                                  = gpa_counter_lib_func_table.GpaCounterLib_OpenCounterContext(
        api, counter_context_hardware_info, GPA_OPENCONTEXT_DEFAULT_BIT | GPA_OPENCONTEXT_ENABLE_HARDWARE_COUNTERS_BIT, asic_specific, &gpa_counter_context);

    GpaCounterParam counter_param;

    counter_param.is_derived_counter   = true;
    counter_param.derived_counter_name = "GPUBusy";
    gpa_uint32 gpu_time_counter_index;
    gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param, &gpu_time_counter_index);

    counter_param.is_derived_counter   = true;
    counter_param.derived_counter_name = "GPUTime";
    gpa_uint32 gpu_busy_index;
    gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param, &gpu_busy_index);

    counter_param.is_derived_counter                   = false;
    counter_param.gpa_hw_counter.gpa_hw_block          = GPA_HW_BLOCK_SQ;
    counter_param.gpa_hw_counter.gpa_hw_block_instance = 0;
    counter_param.gpa_hw_counter.gpa_hw_block_event_id = 4;
    counter_param.gpa_hw_counter.gpa_shader_mask       = GPA_SHADER_MASK_PS;
    gpa_uint32 sq_counter_index;
    gpa_status = gpa_counter_lib_func_table.GpaCounterLib_GetCounterIndex(gpa_counter_context, &counter_param, &sq_counter_index);

    std::map<unsigned int, std::vector<std::string>> pass_counter_names = {
        {0, {"CPF_PERF_SEL_CPF_STAT_BUSY", "CPF_PERF_SEL_ALWAYS_COUNT", "SQ_PS0_PERF_SEL_WAVES"}}, {1, {"GPUTime_BOTTOM_TO_BOTTOM_DURATION"}}};

    if (GPA_STATUS_OK == gpa_status)
    {
        gpa_uint32                                        derived_counter_list[] = {gpu_time_counter_index, gpu_busy_index, sq_counter_index};
        std::map<unsigned int, std::vector<unsigned int>> pass_counter_map       = GetPassCounters(gpa_counter_context, 3, derived_counter_list);

        unsigned int pass_iter = 0;
        for (auto iter = pass_counter_map.cbegin(); iter != pass_counter_map.cend(); ++iter)
        {
            unsigned counter_index_iter = 0u;
            for (auto counter_iter = iter->second.cbegin(); counter_iter != iter->second.cend(); ++counter_iter)
            {
                const char* counter_name;
                gpa_counter_lib_func_table.GpaCounterLib_GetCounterName(gpa_counter_context, *counter_iter, &counter_name);
                EXPECT_STREQ(counter_name, pass_counter_names[pass_iter][counter_index_iter].c_str());
                counter_index_iter++;
            }
            pass_iter++;
        }
    }

    gpa_status = gpa_counter_lib_func_table.GpaCounterLib_CloseCounterContext(gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_OK, gpa_status);
    gpa_counter_context = nullptr;

    UnloadLib(libHandle);
    libHandle = nullptr;
}

void VerifyPassCount(GPA_API_Type                     api,
                     unsigned int                     deviceId,
                     gpa_uint8                        generateAsicSpecificCounters,
                     const std::vector<unsigned int>& countersToEnable,
                     unsigned int                     expectedNumPasses)
{
    LibHandle              libHandle                  = nullptr;
    GpaCounterLibFuncTable gpa_counter_lib_func_table = {};

    LOAD_AND_VERIFY_COUNTER_LIB(&libHandle, &gpa_counter_lib_func_table);

    GPA_CounterContext            gpa_counter_context           = nullptr;
    GpaCounterContextHardwareInfo counter_context_hardware_info = {AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, nullptr, 0};
    gpa_status                                                  = gpa_counter_lib_func_table.GpaCounterLib_OpenCounterContext(
        api, counter_context_hardware_info, GPA_OPENCONTEXT_DEFAULT_BIT, generateAsicSpecificCounters, &gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_OK, gpa_status);

    gpa_uint32 pass_count = 0u;
    gpa_status            = gpa_counter_lib_func_table.GpaCounterLib_GetPassCount(
        gpa_counter_context, countersToEnable.data(), static_cast<gpa_uint32>(countersToEnable.size()), &pass_count);
    EXPECT_EQ(expectedNumPasses, pass_count);

    gpa_status = gpa_counter_lib_func_table.GpaCounterLib_CloseCounterContext(gpa_counter_context);
    EXPECT_EQ(GPA_STATUS_OK, gpa_status);

    UnloadLib(libHandle);
}

void VerifyCountersInPass(GPA_API_Type                                                                     api,
                          unsigned int                                                                     deviceId,
                          gpa_uint8                                                                        generateAsicSpecificCounters,
                          const std::vector<unsigned int>&                                                 countersToEnable,
                          const std::vector<std::vector<unsigned int>>&                                    expectedHwCountersPerPass,
                          const std::map<unsigned int, std::map<unsigned int, GPA_CounterResultLocation>>& expectedResultLocations)
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

#include "gpa_derived_counter_evaluator.inc"

void VerifyCounterFormula(std::vector<GPACounterDesc> public_counters)
{
    GPA_HWInfo dummy_hardware_info;
    dummy_hardware_info.SetNumberShaderEngines(1);
    dummy_hardware_info.SetNumberShaderArrays(1);
    dummy_hardware_info.SetNumberSIMDs(1);
    dummy_hardware_info.SetSUClocksPrim(1);
    dummy_hardware_info.SetNumberPrimPipes(1);
    dummy_hardware_info.SetNumberCUs(1);
    dummy_hardware_info.SetTimeStampFrequency(1);

    for (std::vector<GPACounterDesc>::const_iterator it = public_counters.cbegin(); it != public_counters.cend(); ++it)
    {
        std::vector<const gpa_uint64*> results;
        gpa_uint64*                    result_mem = new (std::nothrow) gpa_uint64[it->m_internalCounterCount];

        if (nullptr != result_mem)
        {
            memset(result_mem, 1, sizeof(gpa_uint64) * it->m_internalCounterCount);
            results.reserve(it->m_internalCounterCount);

            for (gpa_uint32 i = 0; i < it->m_internalCounterCount; i++)
            {
                results.push_back(result_mem + i);
            }

            gpa_float64 final_result;
            GPA_Status  gpa_status = EvaluateExpression<gpa_float64, gpa_uint64>(it->m_pEqn, &final_result, results, it->m_type, &dummy_hardware_info);
            delete[] result_mem;
            EXPECT_EQ(GPA_STATUS_OK, gpa_status);
        }
    }
}