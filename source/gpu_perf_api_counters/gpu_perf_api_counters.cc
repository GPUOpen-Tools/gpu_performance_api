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

#include <cstring>
#include <vector>

#include "gpu_performance_api/gpu_perf_api_counters.h"
#include "gpa_hardware_counters.h"
#include "gpa_counter_context_handler.h"
#include "gpa_version.h"
#include "gpa_hw_support.h"
#include "gpa_array_view.hpp"

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

namespace
{
    // Get the HW counter data via the appropriate SPM data offset
    GpaStatus GetHardwareCounterData(const GpaSpmData&     spm_data,
                                     const GpaCounterInfo& counter_info,
                                     const GpaUInt32       timestamp_index,
                                     const GpaUInt32       spm_counter_data_size_in_bytes,
                                     GpaFloat64*           result)
    {
        assert(!counter_info.is_derived_counter);

        GpaHwCounter* gpa_hw_counter = counter_info.gpa_hw_counter;

        size_t hw_offset = timestamp_index;

        bool invalid_hw_counter = true;

        for (uint32_t i = 0; i < spm_data.number_of_spm_counter_info; ++i)
        {
            GpaSpmCounterInfo const& spm_counter_info = spm_data.spm_counter_info[i];

            if (static_cast<uint32_t>(gpa_hw_counter->gpa_hw_block) != spm_counter_info.gpu_block_id)
            {
                continue;
            }
            if (gpa_hw_counter->gpa_hw_block_event_id != spm_counter_info.event_index)
            {
                continue;
            }
            if (gpa_hw_counter->gpa_hw_block_instance != spm_counter_info.gpu_block_instance)
            {
                continue;
            }

            invalid_hw_counter = false;

            // The offset should be a multiple of the timestamp.
            if (spm_counter_info.data_offset % spm_data.number_of_timestamps != 0)
            {
                return kGpaStatusErrorInvalidParameter;
            }

            // Then get the appropriate spm data offset.
            hw_offset += spm_counter_info.data_offset;
            break;
        }

        if (invalid_hw_counter)
        {
            // The hardware counter the user queried for doesn't exist in the spm counter array.
            return kGpaStatusErrorInvalidParameter;
        }

        if (spm_counter_data_size_in_bytes == 2)
        {
            const GpaUInt16* counter_data = spm_data.counter_data_16bit;
            *result                       = counter_data[hw_offset];
        }
        else
        {
            const auto* counter_data = reinterpret_cast<const GpaUInt32*>(spm_data.counter_data_16bit);
            *result                  = counter_data[hw_offset];
        }

        return kGpaStatusOk;
    }

    // Data needed to implement WaveOccupancyPct described below.
    struct WaveOccupancyPctWorkaroundData
    {
        int64_t  level_waves_rolling_sum;      ///< Keeps track of the total waves
        uint64_t max_waves_total;              ///< Used to calculate the percentage
        uint64_t max_waves_per_shader_engine;  ///< Used to quickly determine if a wave value is negative
    };

    // WaveOccupancyPct on GFX10 and GFX10.3 is based on SQ*_PERF_SEL_LEVEL_WAVES which requires setting the next hardware counter to ACCUM_PREV to get the desired result.
    // We elected not to utilize ACCUM_PREV because GPA can not guarantee that the ACCUM_PREV event would definitively be enabled on the immediately proceeding hardware register as the LEVEL_WAVES events.
    //
    // This is not the case for GFX11+ where we use SQWGP*_SQ_PERF_SEL_LEVEL_WAVES. Where the counter is not being reset.
    //
    // Currently the equation for WaveOccupanyPct adds up each HW counter value.
    // Then divides by the maximum number of waves. Then multiples by 100 to get a percentage.
    //
    // The main problem is the HW counters can be negative values on GFX10 and GFX10.3 as a result we have to workaround this
    // Since our current codebase doesn't handle negative hardware counter values.
    //
    // We could fixup the hardware counters by maintaining a separate array to keep track of the rolling sum for each HW
    // counter. But that ends up being more expensive/difficult to read. Instead keeping 1 rolling sum is much cheaper.
    //
    // NOTE: There is a slight bug with this approach. Because this function implements the entire calculation for WaveOccupancyPct;
    // it doesn't re-update the array of SQ_PERF_PERF_SEL_LEVEL_WAVES counter results to be correct. As such, if that event was being
    // shared by multiple counters that were enabled in this pass, it would not correctly update the values for that other counter equation.
    // We currently don't have other equations that use that currently. Also since Gfx10 and Gfx10.3 since they have gone into maintenance mode
    // the equations for those 2 HW generations is unlikely to change.
    GpaFloat64 ComputeWaveOccupancyWorkaround(WaveOccupancyPctWorkaroundData* wave_occupancy_workaround,
                                              const GpaUInt32                 spm_counter_data_size_in_bytes,
                                              const gpa_array_view<GpaUInt64> hardware_counter_data)
    {
        const uint64_t max_waves_per_shader_engine = wave_occupancy_workaround->max_waves_per_shader_engine;

        for (const GpaUInt64& raw_level_value : hardware_counter_data)
        {
            if (raw_level_value <= max_waves_per_shader_engine)
            {
                // This is a positive value.
                wave_occupancy_workaround->level_waves_rolling_sum += raw_level_value;
            }
            else if (spm_counter_data_size_in_bytes == 2)
            {
                // This is a negative 16-bit value.
                wave_occupancy_workaround->level_waves_rolling_sum += static_cast<int16_t>(raw_level_value);
            }
            else
            {
                // This is a negative 32-bit value.
                wave_occupancy_workaround->level_waves_rolling_sum += static_cast<int32_t>(raw_level_value);
            }
        }

        // The rolling sum should always be greater than zero, but it can go negative due to race conditions on the hardware or if the SPM buffer wraps.
        if (wave_occupancy_workaround->level_waves_rolling_sum < 0)
        {
            wave_occupancy_workaround->level_waves_rolling_sum = 0;
        }

        const auto max_waves_total = static_cast<double>(wave_occupancy_workaround->max_waves_total);

        GpaFloat64 result = static_cast<double>(wave_occupancy_workaround->level_waves_rolling_sum) / max_waves_total;
        result *= 100.0;
        return result;
    }
}  // namespace

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

    bool      major_version_match = GPA_COUNTER_LIB_FUNC_TABLE_MAJOR_VERSION == counter_lib_func_table->gpa_counter_lib_major_version;
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

GPU_PERF_API_COUNTERS_DECL GpaStatus
GpaCounterLibOpenCounterContext(GpaApiType           api,
                                GpaSessionSampleType sample_type,
                                // NOTE: GpaCounterContextHardwareInfo is being passed by value. This should be passed via const*.
                                GpaCounterContextHardwareInfo gpa_counter_context_hardware_info,
                                GpaOpenContextFlags           context_flags,
                                GpaCounterContext*            gpa_virtual_context)
{
    if (nullptr == gpa_virtual_context)
    {
        return kGpaStatusErrorNullPointer;
    }

    const bool hide_derived_counters     = (context_flags & kGpaOpenContextHideDerivedCountersBit) != 0;
    const bool disable_hardware_counters = (context_flags & kGpaOpenContextEnableHardwareCountersBit) == 0;

    // If we are disabling all types of counters then return an error since no counters will be generated.
    if (hide_derived_counters && disable_hardware_counters)
    {
        return kGpaStatusErrorInvalidParameter;
    }

    // Opening a counter context is only meaningful for generating counters offline. Sqtt doesn't have counters to generate.
    //
    // Furthermore, it is wasteful to have the user create 2 different contexts for getting discrete/spm counter information.
    if (sample_type == kGpaSessionSampleTypeSqtt)
    {
        return kGpaStatusErrorInvalidParameter;
    }

    // We have to pass an invalid driver. Since we can't break ABI.
    constexpr GpaDriverInfo kDriverInfo = {};
    static_assert(kDriverInfo.driver_type == kIgnoreDriver);

    return GpaCounterContextManager::Instance()->OpenCounterContext(
        api, sample_type, gpa_counter_context_hardware_info, context_flags, gpa_virtual_context, kDriverInfo);
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
    if (gpa_hw_counter_result_count == 0)
    {
        return kGpaStatusErrorInvalidParameter;
    }
    if (nullptr == gpa_virtual_context || nullptr == gpa_derived_counter_result || nullptr == gpa_hw_counter_result)
    {
        return kGpaStatusErrorNullPointer;
    }
    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }

    const IGpaCounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);
    if (counter_accessor == nullptr)
    {
        return kGpaStatusErrorFailed;
    }

    const GpaUInt32 public_counter_count = counter_accessor->GetNumPublicCounters();

    // User created context with GpaOpenContextHidePublicCountersBit or they passed in a completely invalid index.
    if (public_counter_count == 0 || gpa_derived_counter_index >= public_counter_count)
    {
        return kGpaStatusErrorFailed;
    }

    // The above checks guarantee it's safe to index the variant like this. Since we now know the user passed
    // in a valid derived counter index.
    constexpr auto                  kCounterSourcePublic = static_cast<uint32_t>(GpaCounterSource::kPublic);
    const gpa_array_view<GpaUInt32> required_hardware_counters =
        std::get<kCounterSourcePublic>(counter_accessor->GetInternalCountersRequired(gpa_derived_counter_index));

    if (gpa_hw_counter_result_count != required_hardware_counters.size())
    {
        return kGpaStatusErrorFailed;
    }

    const gpa_array_view<GpaUInt64> hardware_counter_result(gpa_hw_counter_result, gpa_hw_counter_result_count);
    const GpaHwInfo&                gpa_virtual_context_hw_info = (*gpa_virtual_context)->GetHardwareInfo();
    const GpaStatus                 gpa_status                  = counter_accessor->ComputePublicCounterValue(
        gpa_derived_counter_index, hardware_counter_result, gpa_derived_counter_result, gpa_virtual_context_hw_info);

    return gpa_status;
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

    if (nullptr == counter_scheduler)
    {
        return kGpaStatusErrorFailed;
    }

    counter_scheduler->DisableAllCounters();

    GpaUInt32 counter_index             = 0u;
    bool      enabled_counters          = true;
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
    bool      enabled_counters          = true;
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

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterLibGetSupportedSampleTypes(const GpaApiType                  api,
                                                                          const GpaSupportedSampleTypeInfo* info,
                                                                          GpaContextSampleTypeFlags*        supported_sample_types)
{
    if (api < kGpaApiDirectx11 || api > kGpaApiVulkan)
    {
        return kGpaStatusErrorApiNotSupported;
    }
    if (info == nullptr || supported_sample_types == nullptr)
    {
        return kGpaStatusErrorNullPointer;
    }
    if (info->vendor_id != kAmdVendorId)
    {
        return kGpaStatusErrorHardwareNotSupported;
    }
    if (info->driver_info.driver_type > kAmdProprietaryDriver)
    {
        return kGpaStatusErrorInvalidParameter;
    }
    *supported_sample_types = CalculateSupportedSampleTypes(info->device_id, info->revision_id, api, info->driver_info);
    if (*supported_sample_types == 0)
    {
        return kGpaStatusErrorHardwareNotSupported;
    }

    return kGpaStatusOk;
}

GPU_PERF_API_COUNTERS_DECL GpaStatus GpaCounterlibComputeDerivedSpmCounterResults(const GpaCounterContext gpa_virtual_context,
                                                                                  const GpaSpmData*       spm_data,
                                                                                  const GpaUInt64         gpa_counter_indices_count,
                                                                                  const GpaUInt32*        gpa_counter_indices,
                                                                                  GpaFloat64*             gpa_counter_results)
{
    if (gpa_virtual_context == nullptr || spm_data == nullptr || gpa_counter_results == nullptr || gpa_counter_indices == nullptr)
    {
        return kGpaStatusErrorNullPointer;
    }
    if (spm_data->timestamps == nullptr || spm_data->counter_data_16bit == nullptr || spm_data->spm_counter_info == nullptr)
    {
        return kGpaStatusErrorNullPointer;
    }
    if (spm_data->number_of_timestamps == 0 || spm_data->number_of_spm_counter_info == 0 || spm_data->number_of_counter_data == 0 ||
        gpa_counter_indices_count == 0)
    {
        return kGpaStatusErrorInvalidParameter;
    }
    const GpaUInt32 spm_counter_data_size_in_bytes = spm_data->number_of_bytes_per_counter_data;
    if (spm_counter_data_size_in_bytes != 2 && spm_counter_data_size_in_bytes != 4)
    {
        return kGpaStatusErrorInvalidParameter;
    }
    if (spm_data->number_of_timestamps * spm_data->number_of_spm_counter_info != spm_data->number_of_counter_data)
    {
        return kGpaStatusErrorInvalidParameter;
    }

    if (!GpaCounterContextManager::Instance()->IsCounterContextOpen(gpa_virtual_context))
    {
        return kGpaStatusErrorContextNotOpen;
    }
    const IGpaCounterAccessor* counter_accessor = GpaCounterContextManager::Instance()->GetCounterAccessor(gpa_virtual_context);
    if (counter_accessor == nullptr)
    {
        return kGpaStatusErrorFailed;
    }

    // We don't utilize the timestamp information. It's not relevant for calculating the counter results.
    (void)spm_data->timestamps;

    const GpaHwInfo&            hw_info          = (*gpa_virtual_context)->GetHardwareInfo();
    GDT_HW_GENERATION           generation       = {};
    [[maybe_unused]] const bool found_generation = hw_info.GetHwGeneration(generation);

    // This should never happen. It means the counter lib context wasn't properly created.
    assert(found_generation);

    const bool                     is_older_than_gfx11            = (generation < GDT_HW_GENERATION_GFX11);
    WaveOccupancyPctWorkaroundData wave_occupancy_workaround_data = {};
    if (is_older_than_gfx11)
    {
        wave_occupancy_workaround_data.level_waves_rolling_sum     = 0;
        wave_occupancy_workaround_data.max_waves_total             = hw_info.GetMaxWaveSlots();
        wave_occupancy_workaround_data.max_waves_per_shader_engine = wave_occupancy_workaround_data.max_waves_total / hw_info.GetNumberShaderEngines();
    }

    using HardwareCounterDataOffsets = GpaUInt32;

    std::vector<HardwareCounterDataOffsets> offset_data;
    std::vector<GpaUInt64>                  hardware_counter_data;

    // GPA might be expecting more block instances than what is on the current hardware.
    // Use a dummy value to indicate this offset does not exist.
    constexpr uint32_t kDummyIndexForExtraGpaBlocks = UINT32_MAX;

    for (size_t i = 0; i < gpa_counter_indices_count; ++i)
    {
        const GpaUInt32 counter_index = *(gpa_counter_indices++);

        const GpaCounterInfo* counter_info = counter_accessor->GetCounterInfo(counter_index);

        // Unable to get counter information.
        if (counter_info == nullptr)
        {
            return kGpaStatusErrorCounterNotFound;
        }

        const bool is_derived                        = counter_info->is_derived_counter;
        bool       require_wave_occupancy_workaround = false;

        if (is_derived)
        {
            offset_data.clear();

            const GpaHwCounter* gpa_hardware_counters = counter_info->gpa_derived_counter->gpa_hw_counters;

            bool data_is_all_dummy_indices = true;

            const GpaUInt32 gpa_hw_counter_count = counter_info->gpa_derived_counter->gpa_hw_counter_count;

            // Technically we should be able to know at compile time the max amount of HW counters any derived
            // counter could contain. Reserving here is good enough though. The inner loop is where performance is critical.
            offset_data.reserve(gpa_hw_counter_count);
            hardware_counter_data.reserve(gpa_hw_counter_count);

            // Iterate through the hardware counters that make up the derived counter in order to collect the hardware offsets into the SPM data.
            for (size_t hc = 0; hc < gpa_hw_counter_count; ++hc)
            {
                const GpaHwCounter& current_counter = gpa_hardware_counters[hc];
                GpaSpmCounterInfo   to_search;
                to_search.gpu_block_id       = current_counter.gpa_hw_block;
                to_search.gpu_block_instance = current_counter.gpa_hw_block_instance;
                to_search.event_index        = current_counter.gpa_hw_block_event_id;

                GpaUInt32 offset = kDummyIndexForExtraGpaBlocks;

                for (uint64_t sc = 0; sc < spm_data->number_of_spm_counter_info; ++sc)
                {
                    GpaSpmCounterInfo const& spm_counter_info = spm_data->spm_counter_info[sc];

                    if (spm_counter_info.gpu_block_id == to_search.gpu_block_id && spm_counter_info.gpu_block_instance == to_search.gpu_block_instance &&
                        spm_counter_info.event_index == to_search.event_index)
                    {
                        data_is_all_dummy_indices = false;
                        offset                    = spm_counter_info.data_offset;

                        // The offset in the spm data should be a multiple based off the number of timestamps.
                        if (offset % spm_data->number_of_timestamps != 0)
                        {
                            return kGpaStatusErrorInvalidParameter;
                        }
                        break;
                    }
                }

                offset_data.push_back(offset);
            }

            // Something is wrong with the spm_counter_info data the user passed in.
            // Since all of the offset data is full of dummy values.
            if (data_is_all_dummy_indices)
            {
                return kGpaStatusErrorInvalidParameter;
            }

            assert(offset_data.size() == gpa_hw_counter_count);

            const char* derived_counter_name  = counter_accessor->GetCounterName(counter_index);
            require_wave_occupancy_workaround = is_older_than_gfx11 && (std::string_view(derived_counter_name) == "WaveOccupancyPct");
        }

        // Each counter has X amount of timestamps we need to calculate the result for.
        // It's important to optimize the contents of this inner loop.
        // The number of timestamps can be as much as 13,000 on a trivial test application.
        for (GpaUInt32 ts = 0; ts < spm_data->number_of_timestamps; ++ts)
        {
            GpaFloat64 result = 0.0;

            if (is_derived)
            {
                hardware_counter_data.clear();

                bool all_values_zero = true;

                for (const HardwareCounterDataOffsets& hardware_counter_offset : offset_data)
                {
                    // Provide a value of 0 for raw counters that are from block instances not present on this hardware.
                    if (hardware_counter_offset == kDummyIndexForExtraGpaBlocks)
                    {
                        hardware_counter_data.push_back(0);
                    }
                    else if (spm_counter_data_size_in_bytes == 2)
                    {
                        const GpaUInt16* counter_data = spm_data->counter_data_16bit;
                        GpaUInt16        value_u16    = counter_data[hardware_counter_offset + ts];
                        hardware_counter_data.push_back(value_u16);
                    }
                    else
                    {
                        const auto* counter_data = reinterpret_cast<const GpaUInt32*>(spm_data->counter_data_16bit);
                        GpaUInt32   value_32     = counter_data[hardware_counter_offset + ts];
                        hardware_counter_data.push_back(value_32);
                    }

                    if (hardware_counter_data.back() != 0)
                    {
                        all_values_zero = false;
                    }
                }

                assert(offset_data.size() == hardware_counter_data.size());

                // As an optimization, skip computing the derived counter value if all raw inputs are zero.
                if (all_values_zero)
                {
                    result = 0.0;
                }
                else  // We need to calculate the derived counter value
                {
                    const gpa_array_view<GpaUInt64> hw_counter_data(hardware_counter_data.data(), hardware_counter_data.size());

                    if (require_wave_occupancy_workaround)
                    {
                        result = ComputeWaveOccupancyWorkaround(&wave_occupancy_workaround_data, spm_counter_data_size_in_bytes, hw_counter_data);
                    }
                    else
                    {
                        const GpaStatus status = counter_accessor->ComputePublicCounterValue(counter_index, hw_counter_data, &result, hw_info);
                        if (status != kGpaStatusOk)
                        {
                            return status;
                        }
                    }
                }
            }
            else
            {
                const GpaStatus status = GetHardwareCounterData(*spm_data, *counter_info, ts, spm_counter_data_size_in_bytes, &result);
                if (status != kGpaStatusOk)
                {
                    return status;
                }
            }

            // Fill out the results for each timestamp for the current counter.
            *(gpa_counter_results++) = result;
        }
    }
    return kGpaStatusOk;
}
