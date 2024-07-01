//==============================================================================
// Copyright (c) 2016-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Base class to handle the scheduling of the D3D Query counters.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_dx11.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

GpaCounterSchedulerDx11::GpaCounterSchedulerDx11()
{
    CounterGeneratorSchedulerManager::Instance()->RegisterCounterScheduler(kGpaApiDirectx11, GDT_HW_GENERATION_NVIDIA, this, false);

    for (int gen = GDT_HW_GENERATION_VOLCANICISLAND; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterScheduler(kGpaApiDirectx11, static_cast<GDT_HW_GENERATION>(gen), this);
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

GpaCounterSplitterAlgorithm GpaCounterSchedulerDx11::GetPreferredSplittingAlgorithm() const
{
    return kConsolidated;
}
