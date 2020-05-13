//==============================================================================
// Copyright (c) 2012-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Implements a library that allows access to the available counters
///         in GPUPerfAPI without creating a GPA Context.
//==============================================================================

/// macro to export public API functions
#ifdef _LINUX
#define GPU_PERF_API_COUNTERS_DECL extern "C" __attribute__((visibility("default")))
#else
#define GPU_PERF_API_COUNTERS_DECL extern "C" __declspec(dllexport)
#endif

#include <string.h>
#include <vector>
#include "gpu_perf_api_counters.h"
#include "gpa_counter_context.h"
#include "gpa_version.h"

GpaCounterContextManager* GpaCounterContextManager::gpa_counter_context_manager_ = nullptr;

GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetVersion(gpa_uint32* major_version,
                                                               gpa_uint32* minor_version,
                                                               gpa_uint32* build_number,
                                                               gpa_uint32* update_version)
{
    if (nullptr == major_version || nullptr == minor_version || nullptr == build_number || nullptr == update_version)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    *major_version  = GPA_MAJOR_VERSION;
    *minor_version  = GPA_MINOR_VERSION;
    *build_number   = GPA_BUILD_NUMBER;
    *update_version = GPA_UPDATE_VERSION;

    return GPA_STATUS_OK;
}

GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetFuncTable(void* gpa_counter_lib_function_table)
{
    if (nullptr == gpa_counter_lib_function_table)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    GpaCounterLibFuncTable* counter_lib_func_table = reinterpret_cast<GpaCounterLibFuncTable*>(gpa_counter_lib_function_table);

    bool       major_version_match = GPA_COUNTER_LIB_FUNC_TABLE_MAJOR_VERSION == counter_lib_func_table->gpa_counter_lib_major_version;
    gpa_uint32 user_minor_version  = counter_lib_func_table->gpa_counter_lib_minor_version;

    if (!major_version_match)
    {
        return GPA_STATUS_ERROR_LIB_LOAD_MAJOR_VERSION_MISMATCH;
    }

    if (user_minor_version > GPA_COUNTER_LIB_FUNC_TABLE_MINOR_VERSION)
    {
        return GPA_STATUS_ERROR_LIB_LOAD_MINOR_VERSION_MISMATCH;
    }

    GpaCounterLibFuncTable lib_func_table;
#define GPA_COUNTER_LIB_INIT_FUNC(func) lib_func_table.func = func;
    GPA_COUNTER_LIB_FUNC(GPA_COUNTER_LIB_INIT_FUNC)

    memcpy(counter_lib_func_table, &lib_func_table, user_minor_version);
    return GPA_STATUS_OK;
}

GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_OpenCounterContext(GPA_API_Type         api,
                                                                       gpa_uint32           vendor_id,
                                                                       gpa_uint32           device_id,
                                                                       gpa_uint32           revision_id,
                                                                       GPA_OpenContextFlags context_flags,
                                                                       gpa_uint8            generate_asic_specific_counters,
                                                                       GPA_CounterContext*  gpa_virtual_context)
{
    if (nullptr == gpa_virtual_context)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    // Gpa no longer supports software counters
    const GPA_OpenContextFlags context_flags_temp = context_flags | GPA_OPENCONTEXT_HIDE_SOFTWARE_COUNTERS_BIT;

    return GpaCounterContextManager::Instance()->OpenCounterContext(
        api, vendor_id, device_id, revision_id, context_flags_temp, generate_asic_specific_counters, gpa_virtual_context);
}

GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_CloseCounterContext(const GPA_CounterContext gpa_virtual_context)
{
    if (nullptr == gpa_virtual_context)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
    }

    return GpaCounterContextManager::Instance()->CloseCounterContext(gpa_virtual_context);
}

GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetNumCounters(const GPA_CounterContext gpa_virtual_context, gpa_uint32* counter_count)
{
    if (nullptr == gpa_virtual_context)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
    }

    const IGPACounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        *counter_count = counter_accessor->GetNumCounters();
        return GPA_STATUS_OK;
    }

    return GPA_STATUS_ERROR_FAILED;
}

GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetCounterName(const GPA_CounterContext gpa_virtual_context,
                                                                   gpa_uint32               gpa_counter_index,
                                                                   const char**             gpa_counter_name)
{
    if (nullptr == gpa_virtual_context)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
    }

    const IGPACounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        *gpa_counter_name = counter_accessor->GetCounterName(gpa_counter_index);

        if (nullptr != (*gpa_counter_name))
        {
            return GPA_STATUS_OK;
        }

        return GPA_STATUS_ERROR_COUNTER_NOT_FOUND;
    }

    return GPA_STATUS_ERROR_FAILED;
}

GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetCounterIndex(const GPA_CounterContext gpa_virtual_context,
                                                                    const GpaCounterParam*   gpa_counter_info,
                                                                    gpa_uint32*              gpa_counter_index)
{
    if (nullptr == gpa_virtual_context ||
        nullptr == gpa_counter_info)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
    }

    const IGPACounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        bool counter_found = false;
        if (gpa_counter_info->is_derived_counter)
        {
            counter_found = counter_accessor->GetCounterIndex(gpa_counter_info->derived_counter_name, gpa_counter_index);
        }
        else
        {
            counter_found = counter_accessor->GetCounterIndex(gpa_counter_info->gpa_hw_counter.gpa_hw_block,
                                                              gpa_counter_info->gpa_hw_counter.gpa_hw_block_instance,
                                                              gpa_counter_info->gpa_hw_counter.gpa_hw_block_event_id,
                                                              gpa_counter_info->gpa_hw_counter.gpa_shader_mask,
                                                              gpa_counter_index);
        }

        if (counter_found)
        {
            return GPA_STATUS_OK;
        }

        return GPA_STATUS_ERROR_COUNTER_NOT_FOUND;
    }

    return GPA_STATUS_ERROR_FAILED;
}

GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetCounterGroup(const GPA_CounterContext gpa_virtual_context,
                                                                    gpa_uint32               gpa_counter_index,
                                                                    const char**             gpa_counter_group)
{
    if (nullptr == gpa_virtual_context)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
    }

    const IGPACounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        *gpa_counter_group = counter_accessor->GetCounterGroup(gpa_counter_index);
        return GPA_STATUS_OK;
    }

    return GPA_STATUS_ERROR_FAILED;
}

GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetCounterDescription(const GPA_CounterContext gpa_virtual_context,
                                                                          gpa_uint32               gpa_counter_index,
                                                                          const char**             gpa_counter_description)
{
    if (nullptr == gpa_virtual_context)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
    }

    const IGPACounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        *gpa_counter_description = counter_accessor->GetCounterDescription(gpa_counter_index);
        return GPA_STATUS_OK;
    }

    return GPA_STATUS_ERROR_FAILED;
}

GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetCounterDataType(const GPA_CounterContext gpa_virtual_context,
                                                                       gpa_uint32               gpa_counter_index,
                                                                       GPA_Data_Type*           gpa_counter_data_type)
{
    if (nullptr == gpa_virtual_context)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
    }

    const IGPACounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        *gpa_counter_data_type = counter_accessor->GetCounterDataType(gpa_counter_index);
        return GPA_STATUS_OK;
    }

    return GPA_STATUS_ERROR_FAILED;
}

GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetCounterUsageType(const GPA_CounterContext gpa_virtual_context,
                                                                        gpa_uint32               gpa_counter_index,
                                                                        GPA_Usage_Type*          gpa_counter_usage_type)
{
    if (nullptr == gpa_virtual_context)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
    }

    const IGPACounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        *gpa_counter_usage_type = counter_accessor->GetCounterUsageType(gpa_counter_index);
        return GPA_STATUS_OK;
    }

    return GPA_STATUS_ERROR_FAILED;
}

GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetCounterUuid(const GPA_CounterContext gpa_virtual_context,
                                                                   gpa_uint32               gpa_counter_index,
                                                                   GPA_UUID*                gpa_counter_uuid)
{
    if (nullptr == gpa_virtual_context)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
    }

    const IGPACounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        *gpa_counter_uuid = counter_accessor->GetCounterUuid(gpa_counter_index);
        return GPA_STATUS_OK;
    }

    return GPA_STATUS_ERROR_FAILED;
}

GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetCounterSampleType(const GPA_CounterContext gpa_virtual_context,
                                                                         gpa_uint32               gpa_counter_index,
                                                                         GPA_Counter_Sample_Type* gpa_counter_sample_type)
{
    if (nullptr == gpa_virtual_context)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
    }

    const IGPACounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        *gpa_counter_sample_type = counter_accessor->GetCounterSampleType(gpa_counter_index);
        return GPA_STATUS_OK;
    }

    return GPA_STATUS_ERROR_FAILED;
}

GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetDerivedCounterInfo(const GPA_CounterContext      gpa_virtual_context,
                                                                          gpa_uint32                    gpa_derived_counter_index,
                                                                          const GpaDerivedCounterInfo** gpa_derived_counter_info)
{
    if (nullptr == gpa_virtual_context || nullptr == gpa_derived_counter_info)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
    }

    const IGPACounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        GpaDerivedCounterInfo* gpa_derived_counter_info_temp = counter_accessor->GetDerivedCounterInfo(gpa_derived_counter_index);

        if (nullptr != gpa_derived_counter_info_temp)
        {
            *gpa_derived_counter_info = gpa_derived_counter_info_temp;
            return GPA_STATUS_OK;
        }
    }

    return GPA_STATUS_ERROR_FAILED;
}

GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_ComputeDerivedCounterResult(const GPA_CounterContext gpa_virtual_context,
                                                                                gpa_uint32               gpa_derived_counter_index,
                                                                                const gpa_uint64*        gpa_hw_counter_result,
                                                                                gpa_uint32               gpa_hw_counter_result_count,
                                                                                gpa_float64*             gpa_derived_counter_result)
{
    if (nullptr == gpa_virtual_context || nullptr == gpa_derived_counter_result || nullptr == gpa_hw_counter_result)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }
    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
    }

    const IGPACounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        const gpa_uint32 public_counter_count = counter_accessor->GetNumPublicCounters();

        if (gpa_derived_counter_index >= public_counter_count)
        {
            return GPA_STATUS_ERROR_FAILED;
        }

        if (gpa_hw_counter_result_count != counter_accessor->GetInternalCountersRequired(gpa_derived_counter_index).size())
        {
            return GPA_STATUS_ERROR_FAILED;
        }

        std::vector<const gpa_uint64*> hardware_counter_result;
        std::vector<GPA_Data_Type>     hardware_counter_result_data_type;
        for (gpa_uint32 i = 0; i < gpa_hw_counter_result_count; i++)
        {
            hardware_counter_result.push_back(&gpa_hw_counter_result[i]);
            hardware_counter_result_data_type.push_back(GPA_DATA_TYPE_UINT64);
        }

        const GPA_HWInfo* gpa_virtual_context_hw_info = (*gpa_virtual_context)->GetHardwareInfo();
        const GPA_Status  gpa_status                  = counter_accessor->ComputePublicCounterValue(
            gpa_derived_counter_index, hardware_counter_result, hardware_counter_result_data_type, gpa_derived_counter_result, gpa_virtual_context_hw_info);

        return gpa_status;
    }

    return GPA_STATUS_ERROR_FAILED;
}

GPU_PERF_API_COUNTERS_DECL GPA_Status GpaCounterLib_GetPassCount(const GPA_CounterContext gpa_virtual_context,
                                                                 const gpa_uint32*        gpa_counter_indices,
                                                                 gpa_uint32               gpa_counter_count,
                                                                 gpa_uint32*              number_of_pass_req)
{
    if (nullptr == gpa_virtual_context || nullptr == gpa_counter_indices)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (0 == gpa_counter_count)
    {
        return GPA_STATUS_ERROR_INVALID_PARAMETER;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return GPA_STATUS_ERROR_CONTEXT_NOT_OPEN;
    }

    IGPACounterScheduler* counter_scheduler = GpaCounterContextManager::Instance()->GetCounterScheduler(gpa_virtual_context);
    counter_scheduler->DisableAllCounters();

    gpa_uint32 counter_index             = 0u;
    bool       enabled_counters          = true;
    GPA_Status counter_scheduling_status = GPA_STATUS_OK;

    for (gpa_uint32 counter_index_iter = 0u; counter_index_iter < gpa_counter_count; ++counter_index_iter)
    {
        counter_index             = gpa_counter_indices[counter_index_iter];
        counter_scheduling_status = counter_scheduler->EnableCounter(counter_index);
        enabled_counters &= GPA_STATUS_OK == counter_scheduling_status;
    }

    if (enabled_counters)
    {
        counter_scheduling_status = counter_scheduler->GetNumRequiredPasses(number_of_pass_req);
        counter_scheduler->DisableAllCounters();
    }

    return counter_scheduling_status;
}
