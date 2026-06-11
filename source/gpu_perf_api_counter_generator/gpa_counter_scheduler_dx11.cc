//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Base class to handle the scheduling of the D3D Query counters.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_dx11.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

#include "gpu_perf_api_common/gpa_hw_support.h"

GpaCounterSchedulerDx11::GpaCounterSchedulerDx11(GpaSessionSampleType sample_type)
    : GpaCounterSchedulerBase(sample_type)
{
    for (const device_info::HwGeneration gen : kSupportedGenerations)
    {
        CounterGeneratorSchedulerManager::Instance().RegisterCounterScheduler(kGpaApiDirectx11, gen, this);
    }
}

GpaStatus GpaCounterSchedulerDx11::EnableCounter(GpaUInt32 index)
{
    return GpaCounterSchedulerBase::EnableCounter(index);
}

GpaStatus GpaCounterSchedulerDx11::DoDisableCounter(GpaUInt32 index)
{
    return GpaCounterSchedulerBase::DoDisableCounter(index);
}

void GpaCounterSchedulerDx11::DisableAllCounters()
{
    GpaCounterSchedulerBase::DisableAllCounters();
}
