//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for counter scheduling for DX12.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_dx12.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

#include "gpu_perf_api_common/gpa_hw_support.h"

GpaCounterSchedulerDx12::GpaCounterSchedulerDx12(GpaSessionSampleType sample_type)
    : GpaCounterSchedulerBase(sample_type)
{
    for (const device_info::HwGeneration gen : kSupportedGenerations)
    {
        CounterGeneratorSchedulerManager::Instance().RegisterCounterScheduler(kGpaApiDirectx12, gen, this);
    }
}
