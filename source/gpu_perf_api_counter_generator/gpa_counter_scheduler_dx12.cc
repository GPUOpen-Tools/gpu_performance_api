//==============================================================================
// Copyright (c) 2016-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for counter scheduling for DX12.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_dx12.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

GpaCounterSchedulerDx12::GpaCounterSchedulerDx12(GpaSessionSampleType sample_type)
    : GpaCounterSchedulerBase(sample_type)
{
    for (int gen = GDT_HW_GENERATION_GFX10; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterScheduler(kGpaApiDirectx12, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GpaCounterSplitterAlgorithm GpaCounterSchedulerDx12::GetPreferredSplittingAlgorithm() const
{
    return kConsolidated;
}
