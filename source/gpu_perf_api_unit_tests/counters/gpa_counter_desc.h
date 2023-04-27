//==============================================================================
// Copyright (c) 2014-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GpaCounterDesc declaration.
//==============================================================================

#ifndef GPA_PERF_API_UNIT_TESTS_COUNTERS_GPA_COUNTER_DESCRIPTION_H_
#define GPA_PERF_API_UNIT_TESTS_COUNTERS_GPA_COUNTER_DESCRIPTION_H_

#include <cstddef>

#include "gpu_performance_api/gpu_perf_api_types.h"

/// @brief GPA public counter description
struct GpaCounterDesc
{
    const char*  name;                   ///< Counter name.
    const char*  group;                  ///< Counter group name.
    const char*  description;            ///< Counter description.
    const char*  equation;               ///< Counter equation.
    GpaUInt32    num_hardware_counters;  ///< Number of hardware counters required.
    GpaDataType  data_type;              ///< Counter type.
    GpaUsageType usage_type;             ///< Counter usage.
    GpaUuid      uuid;                   ///< Counter UUID.
};

#endif  // GPA_PERF_API_UNIT_TESTS_COUNTERS_GPA_COUNTER_DESCRIPTION_H_
