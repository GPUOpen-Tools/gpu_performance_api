//==============================================================================
// Copyright (c) 2012-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPUPerfAPI Counter Generator function.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_COUNTER_GENERATOR_H_
#define GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_COUNTER_GENERATOR_H_

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_counter_generator/gpa_counter_accessor_interface.h"
#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_interface.h"

/// @brief Generates a counter accessor object that can be used to obtain the counters to expose.
///
/// Internal function. We don't want this exposed by the internal DLLs though, so it doesn't use GPALIB_DECL.
///
/// @param [in] desired_api The API to generate counters for.
/// @param [in] vendor_id The vendor id to generate counters for.
/// @param [in] device_id The device id to generate counters for.
/// @param [in] revision_id The revision id to generate counters for.
/// @param [in] flags Flags used to initialize the context. Should be a combination of GpaOpenContextBits.
/// @param [in] generate_asic_specific_counters Flag that indicates whether the counters should be ASIC specific, if available..
/// @param [in,out] counter_accessor_out Address of a counter accessor pointer which will be set to the necessary counter accessor.
/// @param [in,out] counter_scheduler_out Address of a counter scheduler pointer which will be set to the necessary counter scheduler.
///
/// @retval kGpaStatusErrorNullPointer If counter_accessor_out or counter_scheduler_out is nullptr.
/// @retval kGpaStatusErrorCounterNotFound If the desired API is not supported.
/// @retval kGpaStatusErrorNotEnabled If the desired API is not allowing any counters to be exposed.
/// @retval kGpaStatusErrorHardwareNotSupported If the desired generation is not supported.
/// @retval kGpaStatusOk If the desired API and generation are supported.
GpaStatus GenerateCounters(GpaApiType             desired_api,
                           GpaUInt32              vendor_id,
                           GpaUInt32              device_id,
                           GpaUInt32              revision_id,
                           GpaOpenContextFlags    flags,
                           GpaUInt8               generate_asic_specific_counters,
                           IGpaCounterAccessor**  counter_accessor_out,
                           IGpaCounterScheduler** counter_scheduler_out);

#endif  // GPU_PERF_API_COUNTER_GENERATOR_GPA_COUNTER_GENERATOR_H_
