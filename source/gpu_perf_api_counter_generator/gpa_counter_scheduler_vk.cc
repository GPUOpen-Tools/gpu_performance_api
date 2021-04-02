//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for counter scheduling for VK.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_vk.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

GpaCounterSchedulerVk::GpaCounterSchedulerVk()
{
    for (int gen = GDT_HW_GENERATION_NVIDIA; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterScheduler(kGpaApiVulkan, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GpaCounterSplitterAlgorithm GpaCounterSchedulerVk::GetPreferredSplittingAlgorithm() const
{
    return kConsolidated;
}
