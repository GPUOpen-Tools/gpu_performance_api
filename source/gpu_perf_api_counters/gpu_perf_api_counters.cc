//==============================================================================
// Copyright (c) 2012-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Implements a library that allows access to the available counters
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

#include "gpu_performance_api/gpu_perf_api_counters.h"
#include "gpa_hardware_counters.h"
#include "gpa_counter_context_handler.h"
#include "gpa_version.h"

GpaCounterContextManager* GpaCounterContextManager::gpa_counter_context_manager_ = nullptr;

#ifdef _WIN32
BOOL WINAPI DllMain(HINSTANCE, DWORD reason, LPVOID)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;

    case DLL_PROCESS_DETACH:
        GpaCounterContextManager::DeleteInstance();
        break;
    }
    return TRUE;
}
#endif

#ifdef __linux__
void __attribute__((destructor)) dll_fini(void)
{
    // Perform any necessary cleanup.
    GpaCounterContextManager::DeleteInstance();
}
#endif

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterLibGetVersion(GpaUInt32* major_version,
                                                             GpaUInt32* minor_version,
                                                             GpaUInt32* build_number,
                                                             GpaUInt32* update_version)
{
    if (nullptr == major_version || nullptr == minor_version || nullptr == build_number || nullptr == update_version)
    {
        return kGpaStatusErrorNullPointer;
    }

    *major_version  = GPA_MAJOR_VERSION;
    *minor_version  = GPA_MINOR_VERSION;
    *build_number   = GPA_BUILD_NUMBER;
    *update_version = GPA_UPDATE_VERSION;

    return kGpaStatusOk;
}

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterLibGetFuncTable(void* gpa_counter_lib_function_table)
{
    if (nullptr == gpa_counter_lib_function_table)
    {
        return kGpaStatusErrorNullPointer;
    }

    GpaCounterLibFuncTable* counter_lib_func_table = reinterpret_cast<GpaCounterLibFuncTable*>(gpa_counter_lib_function_table);

    bool       major_version_match = GPA_COUNTER_LIB_FUNC_TABLE_MAJOR_VERSION == counter_lib_func_table->gpa_counter_lib_major_version;
    GpaUInt32 user_minor_version  = counter_lib_func_table->gpa_counter_lib_minor_version;

    if (!major_version_match)
    {
        return kGpaStatusErrorLibLoadMajorVersionMismatch;
    }

    if (user_minor_version > GPA_COUNTER_LIB_FUNC_TABLE_MINOR_VERSION)
    {
        return kGpaStatusErrorLibLoadMinorVersionMismatch;
    }

    GpaCounterLibFuncTable lib_func_table;
#define GPA_COUNTER_LIB_INIT_FUNC(func) lib_func_table.func = func;
    GPA_COUNTER_LIB_FUNC(GPA_COUNTER_LIB_INIT_FUNC)

    memcpy(counter_lib_func_table, &lib_func_table, user_minor_version);
    return kGpaStatusOk;
}

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterLibOpenCounterContext(GpaApiType                    api,
                                                                     GpaSessionSampleType          sample_type,
                                                                     GpaCounterContextHardwareInfo gpa_counter_context_hardware_info,
                                                                     GpaOpenContextFlags           context_flags,
                                                                     GpaCounterContext*            gpa_virtual_context)
{
    if (nullptr == gpa_virtual_context)
    {
        return kGpaStatusErrorNullPointer;
    }

    if ((context_flags & kGpaOpenContextHideDerivedCountersBit) && !(context_flags & kGpaOpenContextEnableHardwareCountersBit))
    {
        return kGpaStatusErrorInvalidParameter;
    }

    return GpaCounterContextManager::Instance()->OpenCounterContext(
        api,
        sample_type,
        gpa_counter_context_hardware_info, context_flags, gpa_virtual_context);
}

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterLibCloseCounterContext(const GpaCounterContext gpa_virtual_context)
{
    if (nullptr == gpa_virtual_context)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    GpaStatus close_status = GpaCounterContextManager::Instance()->CloseCounterContext(gpa_virtual_context);

    GpaCounterContextManager::DeleteInstanceIfZero();

    return close_status;
}

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterLibGetNumCounters(const GpaCounterContext gpa_virtual_context, GpaUInt32* counter_count)
{
    if (nullptr == gpa_virtual_context)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    const IGpaCounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        *counter_count = counter_accessor->GetNumCounters();
        return kGpaStatusOk;
    }

    return kGpaStatusErrorFailed;
}

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterLibGetCounterName(const GpaCounterContext gpa_virtual_context,
                                                                 GpaUInt32               gpa_counter_index,
                                                                 const char**            gpa_counter_name)
{
    if (nullptr == gpa_virtual_context)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    const IGpaCounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        *gpa_counter_name = counter_accessor->GetCounterName(gpa_counter_index);

        if (nullptr != (*gpa_counter_name))
        {
            return kGpaStatusOk;
        }

        return kGpaStatusErrorCounterNotFound;
    }

    return kGpaStatusErrorFailed;
}

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterLibGetCounterIndex(const GpaCounterContext gpa_virtual_context,
                                                                  const GpaCounterParam*  gpa_counter_info,
                                                                  GpaUInt32*              gpa_counter_index)
{
    if (nullptr == gpa_virtual_context || nullptr == gpa_counter_info)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (gpa_counter_info->is_derived_counter && gpa_counter_info->derived_counter_name == nullptr)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    const IGpaCounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

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
            return kGpaStatusOk;
        }

        return kGpaStatusErrorCounterNotFound;
    }

    return kGpaStatusErrorFailed;
}

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterLibGetCounterGroup(const GpaCounterContext gpa_virtual_context,
                                                                  GpaUInt32               gpa_counter_index,
                                                                  const char**            gpa_counter_group)
{
    if (nullptr == gpa_virtual_context)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    const IGpaCounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        *gpa_counter_group = counter_accessor->GetCounterGroup(gpa_counter_index);
        return kGpaStatusOk;
    }

    return kGpaStatusErrorFailed;
}

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterLibGetCounterDescription(const GpaCounterContext gpa_virtual_context,
                                                                        GpaUInt32               gpa_counter_index,
                                                                        const char**            gpa_counter_description)
{
    if (nullptr == gpa_virtual_context)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    const IGpaCounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        *gpa_counter_description = counter_accessor->GetCounterDescription(gpa_counter_index);
        return kGpaStatusOk;
    }

    return kGpaStatusErrorFailed;
}

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterLibGetCounterDataType(const GpaCounterContext gpa_virtual_context,
                                                                     GpaUInt32               gpa_counter_index,
                                                                     GpaDataType*            gpa_counter_data_type)
{
    if (nullptr == gpa_virtual_context)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    const IGpaCounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        *gpa_counter_data_type = counter_accessor->GetCounterDataType(gpa_counter_index);
        return kGpaStatusOk;
    }

    return kGpaStatusErrorFailed;
}

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterLibGetCounterUsageType(const GpaCounterContext gpa_virtual_context,
                                                                      GpaUInt32               gpa_counter_index,
                                                                      GpaUsageType*           gpa_counter_usage_type)
{
    if (nullptr == gpa_virtual_context)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    const IGpaCounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        *gpa_counter_usage_type = counter_accessor->GetCounterUsageType(gpa_counter_index);
        return kGpaStatusOk;
    }

    return kGpaStatusErrorFailed;
}

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterLibGetCounterUuid(const GpaCounterContext gpa_virtual_context,
                                                                 GpaUInt32               gpa_counter_index,
                                                                 GpaUuid*                gpa_counter_uuid)
{
    if (nullptr == gpa_virtual_context)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    const IGpaCounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        *gpa_counter_uuid = counter_accessor->GetCounterUuid(gpa_counter_index);
        return kGpaStatusOk;
    }

    return kGpaStatusErrorFailed;
}

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterLibGetCounterSampleType(const GpaCounterContext gpa_virtual_context,
                                                                       GpaUInt32               gpa_counter_index,
                                                                       GpaCounterSampleType*   gpa_counter_sample_type)
{
    if (nullptr == gpa_virtual_context)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    const IGpaCounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        *gpa_counter_sample_type = counter_accessor->GetCounterSampleType(gpa_counter_index);
        return kGpaStatusOk;
    }

    return kGpaStatusErrorFailed;
}

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterLibGetCounterInfo(const GpaCounterContext gpa_virtual_context,
                                                                 GpaUInt32               gpa_counter_index,
                                                                 const GpaCounterInfo**  gpa_counter_info)
{
    if (nullptr == gpa_virtual_context || nullptr == gpa_counter_info)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    const IGpaCounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        GpaCounterInfo* gpa_counter_info_temp = counter_accessor->GetCounterInfo(gpa_counter_index);

        if (nullptr != gpa_counter_info_temp)
        {
            *gpa_counter_info = gpa_counter_info_temp;
            return kGpaStatusOk;
        }
    }

    return kGpaStatusErrorFailed;
}

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterLibComputeDerivedCounterResult(const GpaCounterContext gpa_virtual_context,
                                                                              GpaUInt32               gpa_derived_counter_index,
                                                                              const GpaUInt64*        gpa_hw_counter_result,
                                                                              GpaUInt32               gpa_hw_counter_result_count,
                                                                              GpaFloat64*             gpa_derived_counter_result)
{
    if (nullptr == gpa_virtual_context || nullptr == gpa_derived_counter_result || nullptr == gpa_hw_counter_result)
    {
        return kGpaStatusErrorNullPointer;
    }
    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    const IGpaCounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr != counter_accessor)
    {
        const GpaUInt32 public_counter_count = counter_accessor->GetNumPublicCounters();

        if (gpa_derived_counter_index >= public_counter_count)
        {
            return kGpaStatusErrorFailed;
        }

        if (gpa_hw_counter_result_count != counter_accessor->GetInternalCountersRequired(gpa_derived_counter_index).size())
        {
            return kGpaStatusErrorFailed;
        }

        std::vector<const GpaUInt64*> hardware_counter_result;
        std::vector<GpaDataType>     hardware_counter_result_data_type;
        for (GpaUInt32 i = 0; i < gpa_hw_counter_result_count; i++)
        {
            hardware_counter_result.push_back(&gpa_hw_counter_result[i]);
            hardware_counter_result_data_type.push_back(kGpaDataTypeUint64);
        }

        const GpaHwInfo* gpa_virtual_context_hw_info = (*gpa_virtual_context)->GetHardwareInfo();
        const GpaStatus  gpa_status                  = counter_accessor->ComputePublicCounterValue(
            gpa_derived_counter_index, hardware_counter_result, hardware_counter_result_data_type, gpa_derived_counter_result, gpa_virtual_context_hw_info);

        return gpa_status;
    }

    return kGpaStatusErrorFailed;
}

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterLibGetPassCount(const GpaCounterContext gpa_virtual_context,
                                                               const GpaUInt32*        gpa_counter_indices,
                                                               GpaUInt32               gpa_counter_count,
                                                               GpaUInt32*              number_of_pass_req)
{
    if (nullptr == gpa_virtual_context || nullptr == gpa_counter_indices)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (0 == gpa_counter_count)
    {
        return kGpaStatusErrorInvalidParameter;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    IGpaCounterScheduler* counter_scheduler = GpaCounterContextManager::Instance()->GetCounterScheduler(gpa_virtual_context);
    counter_scheduler->DisableAllCounters();

    GpaUInt32 counter_index             = 0u;
    bool       enabled_counters          = true;
    GpaStatus counter_scheduling_status = kGpaStatusOk;

    for (GpaUInt32 counter_index_iter = 0u; counter_index_iter < gpa_counter_count; ++counter_index_iter)
    {
        counter_index             = gpa_counter_indices[counter_index_iter];
        counter_scheduling_status = counter_scheduler->EnableCounter(counter_index);
        enabled_counters &= kGpaStatusOk == counter_scheduling_status;
    }

    if (enabled_counters)
    {
        counter_scheduling_status = counter_scheduler->GetNumRequiredPasses(number_of_pass_req);
        counter_scheduler->DisableAllCounters();
    }

    return counter_scheduling_status;
}

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterLibGetCountersByPass(const GpaCounterContext gpa_virtual_context,
                                                                    GpaUInt32               gpa_counter_count,
                                                                    const GpaUInt32*        gpa_counter_indices,
                                                                    GpaUInt32*              pass_count,
                                                                    GpaUInt32*              counter_by_pass_list,
                                                                    GpaPassCounter*         gpa_pass_counters)
{
    if (nullptr == gpa_virtual_context || nullptr == gpa_counter_indices || nullptr == pass_count)
    {
        return kGpaStatusErrorNullPointer;
    }

    if (0 == gpa_counter_count)
    {
        return kGpaStatusErrorInvalidParameter;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    const IGpaCounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);

    if (nullptr == counter_accessor)
    {
        return kGpaStatusErrorFailed;
    }

    IGpaCounterScheduler* counter_scheduler = GpaCounterContextManager::Instance()->GetCounterScheduler(gpa_virtual_context);

    if (nullptr == counter_scheduler)
    {
        return kGpaStatusErrorFailed;
    }

    counter_scheduler->DisableAllCounters();

    GpaUInt32 counter_index             = 0u;
    bool       enabled_counters          = true;
    GpaStatus counter_scheduling_status = kGpaStatusOk;

    for (GpaUInt32 counter_index_iter = 0u; counter_index_iter < gpa_counter_count; ++counter_index_iter)
    {
        counter_index             = gpa_counter_indices[counter_index_iter];
        counter_scheduling_status = counter_scheduler->EnableCounter(counter_index);
        enabled_counters &= kGpaStatusOk == counter_scheduling_status;
    }

    if (enabled_counters)
    {
        GpaUInt32 number_of_pass_req;
        counter_scheduling_status = counter_scheduler->GetNumRequiredPasses(&number_of_pass_req);

        if (nullptr == counter_by_pass_list)
        {
            *pass_count = number_of_pass_req;
        }
        else
        {
            if (nullptr == gpa_pass_counters)
            {
                std::vector<unsigned int> counter_in_pass;
                for (unsigned int i = 0; i < *pass_count; i++)
                {
                    counter_in_pass         = *counter_scheduler->GetCountersForPass(i);
                    counter_by_pass_list[i] = static_cast<GpaUInt32>(counter_in_pass.size());
                    counter_in_pass.clear();
                }
            }
        }

        if (nullptr != gpa_pass_counters)
        {
            std::vector<GpaUInt32> pass_counter_vec;
            for (unsigned int i = 0; i < *pass_count; i++)
            {
                GpaPassCounter* pass_counter = &gpa_pass_counters[i];
                pass_counter_vec             = *counter_scheduler->GetCountersForPass(pass_counter->pass_index);

                if (!pass_counter_vec.empty() && nullptr != pass_counter->counter_indices)
                {
                    GpaUInt32 public_interface_counter_index;

                    for (size_t j = 0; j < (pass_counter_vec.size() < pass_counter->counter_count ? pass_counter_vec.size() : pass_counter->counter_count); j++)
                    {
                        counter_accessor->GetPublicInterfaceCounterIndex(pass_counter_vec.at(j), &public_interface_counter_index);
                        pass_counter->counter_indices[j] = public_interface_counter_index;
                    }
                }

                pass_counter_vec.clear();
            }
        }

        counter_scheduler->DisableAllCounters();
    }

    return kGpaStatusOk;
}
