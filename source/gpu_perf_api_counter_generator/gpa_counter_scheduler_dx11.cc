//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Base class to handle the scheduling of the D3D Query counters.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_dx11.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"
#include "gpu_perf_api_counter_generator/gpa_sw_counter_manager.h"

GpaCounterSchedulerDx11::GpaCounterSchedulerDx11()
{
    CounterGeneratorSchedulerManager::Instance()->RegisterCounterScheduler(kGpaApiDirectx11, GDT_HW_GENERATION_NVIDIA, this, false);

    for (int gen = GDT_HW_GENERATION_INTEL; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterScheduler(kGpaApiDirectx11, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GpaStatus GpaCounterSchedulerDx11::EnableCounter(GpaUInt32 index)
{
    GpaStatus status = GpaCounterSchedulerBase::EnableCounter(index);

#if defined(WIN32)
    GpaUInt32 total_counters = counter_accessor_->GetNumCounters();

    if (kNvidiaVendorId == vendor_id_)
    {
        // Nvidia D3D SW counters are added at the beginning of the list, so if the index is less than the
        // number of SW counters, the index must be pointing to a SW counter.
        if (index < SwCounterManager::Instance()->GetNumSwCounters())
        {
            SwCounterManager::Instance()->EnableSwCounter(index);
        }
    }
    else
    {
        // AMD and Intel D3D SW counters are added at the end of the list, so if the index is near the end of the
        // total number of counters (within # SW counters), the index must be pointing to a SW counter.
        if ((index >= total_counters - SwCounterManager::Instance()->GetNumSwCounters()) && index < total_counters)
        {
            SwCounterManager::Instance()->EnableSwCounter(index);
        }
    }

#endif  // WIN32

    return status;
}

GpaStatus GpaCounterSchedulerDx11::DoDisableCounter(GpaUInt32 index)
{
    GpaStatus status = GpaCounterSchedulerBase::DoDisableCounter(index);

    if (kGpaStatusOk == status)
    {
#if defined(WIN32)

        if (kNvidiaVendorId == vendor_id_)
        {
            // Nvidia D3D SW counters are added at the beginning of the list, so if the index is less than the
            // number of SW counters, the index must be pointing to a SW counter.
            if (index < SwCounterManager::Instance()->GetNumSwCounters())
            {
                SwCounterManager::Instance()->DisableSwCounter(index);
            }
        }
        else
        {
            // AMD and Intel D3D SW counters are added at the end of the list, so if the index is near the end of the
            // total number of counters (within # SW counters), the index must be pointing to a SW counter.
            GpaUInt32 total_counters = counter_accessor_->GetNumCounters();

            if ((index >= total_counters - SwCounterManager::Instance()->GetNumSwCounters()) && index < total_counters)
            {
                SwCounterManager::Instance()->DisableSwCounter(index);
            }
        }

#endif  // WIN32
    }

    return status;
}

void GpaCounterSchedulerDx11::DisableAllCounters()
{
    GpaCounterSchedulerBase::DisableAllCounters();

    SwCounterManager::Instance()->ClearEnabledSwCounters();
}

GpaCounterSplitterAlgorithm GpaCounterSchedulerDx11::GetPreferredSplittingAlgorithm() const
{
    return kConsolidated;
}
