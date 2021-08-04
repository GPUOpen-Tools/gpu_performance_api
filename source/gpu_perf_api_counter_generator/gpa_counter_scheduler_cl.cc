//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for counter scheduling for CL.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_cl.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

GpaCounterSchedulerCl::GpaCounterSchedulerCl()
{
    for (int gen = GDT_HW_GENERATION_FIRST_AMD; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterScheduler(kGpaApiOpencl, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GpaCounterSplitterAlgorithm GpaCounterSchedulerCl::GetPreferredSplittingAlgorithm() const
{
    return kConsolidated;
}
