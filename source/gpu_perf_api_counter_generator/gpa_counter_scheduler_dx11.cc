//==============================================================================
// Copyright (c) 2016-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Base class to handle the scheduling of the D3D Query counters
//==============================================================================

#include "gpa_sw_counter_manager.h"

#include "gpa_counter_scheduler_dx11.h"
#include "gpa_counter_generator_scheduler_manager.h"

GPA_CounterSchedulerDX11::GPA_CounterSchedulerDX11()
{
    CounterGeneratorSchedulerManager::Instance()->RegisterCounterScheduler(GPA_API_DIRECTX_11, GDT_HW_GENERATION_NVIDIA, this, false);

    for (int gen = GDT_HW_GENERATION_INTEL; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterScheduler(GPA_API_DIRECTX_11, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GPA_Status GPA_CounterSchedulerDX11::EnableCounter(gpa_uint32 index)
{
    GPA_Status status = GPA_CounterSchedulerBase::EnableCounter(index);

#if defined(WIN32)
    gpa_uint32 totalCounters = m_pCounterAccessor->GetNumCounters();

    if (NVIDIA_VENDOR_ID == m_vendorId)
    {
        if (index < SwCounterManager::Instance()->GetNumSwCounters())  //SW counter
        {
            SwCounterManager::Instance()->EnableSwCounter(index);
        }
    }
    else  //for AMD SW D3D counters are added at the end
    {
        if ((index >= totalCounters - SwCounterManager::Instance()->GetNumSwCounters()) && index < totalCounters)
        {
            SwCounterManager::Instance()->EnableSwCounter(index);
        }
    }

#endif  // WIN32

    return status;
}

GPA_Status GPA_CounterSchedulerDX11::DoDisableCounter(gpa_uint32 index)
{
    GPA_Status status = GPA_CounterSchedulerBase::DoDisableCounter(index);

    if (GPA_STATUS_OK == status)
    {
#if defined(WIN32)

        if (NVIDIA_VENDOR_ID == m_vendorId)
        {
            if (index < SwCounterManager::Instance()->GetNumSwCounters())  //SW counter
            {
                SwCounterManager::Instance()->DisableSwCounter(index);
            }
        }
        else  //for AMD SW D3D counters are added at the end (for Intel, they are first and last)
        {
            gpa_uint32 totalCounters = m_pCounterAccessor->GetNumCounters();

            if ((index >= totalCounters - SwCounterManager::Instance()->GetNumSwCounters()) && index < totalCounters)
            {
                SwCounterManager::Instance()->DisableSwCounter(index);
            }
        }

#endif  // WIN32
    }

    return status;
}

void GPA_CounterSchedulerDX11::DisableAllCounters()
{
    GPA_CounterSchedulerBase::DisableAllCounters();

    SwCounterManager::Instance()->ClearEnabledSwCounters();
}

GPACounterSplitterAlgorithm GPA_CounterSchedulerDX11::GetPreferredSplittingAlgorithm() const
{
    return CONSOLIDATED;
}
