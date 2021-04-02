//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Get internal derived counters -- stub for open source build.
//==============================================================================

#ifdef AMDT_INTERNAL

#include "gpu_perf_api_counter_generator/gpa_derived_counter.h"

GPA_Status GpaGetInternalDerivedCounters(GpaApiType, GpaHwGeneration, const GpaCounterDesc**, size_t*)
{
    return kGpaStatusErrorFailed;
}

#endif
