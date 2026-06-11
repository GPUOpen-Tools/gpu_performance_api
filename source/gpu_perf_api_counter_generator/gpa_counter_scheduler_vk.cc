//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for counter scheduling for VK.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_vk.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

#include "gpu_perf_api_common/gpa_hw_support.h"

GpaCounterSchedulerVk::GpaCounterSchedulerVk(GpaSessionSampleType sample_type)
    : GpaCounterSchedulerBase(sample_type)
{
    for (const device_info::HwGeneration gen : kSupportedGenerations)
    {
        CounterGeneratorSchedulerManager::Instance().RegisterCounterScheduler(kGpaApiVulkan, gen, this);
    }
}
