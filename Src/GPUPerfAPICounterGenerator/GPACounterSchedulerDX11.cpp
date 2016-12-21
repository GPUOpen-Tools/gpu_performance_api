//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Base class to handle the scheduling of the D3D Query counters
//==============================================================================

#include "GPASwCounterManager.h"

#include "GPACounterSchedulerDX11.h"
#include "GPACounterGeneratorSchedulerManager.h"

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
        if (index < s_pSwCounterManager->GetNumSwCounters()) //SW counter
        {
            s_pSwCounterManager->EnableSwCounter(index);
        }
    }
    else  //for AMD SW D3D counters are added at the end
    {
        if ((index >= totalCounters - s_pSwCounterManager->GetNumSwCounters()) && index < totalCounters)
        {
            s_pSwCounterManager->EnableSwCounter(index);
        }
    }

#endif // WIN32

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
            if (index < s_pSwCounterManager->GetNumSwCounters()) //SW counter
            {
                s_pSwCounterManager->DisableSwCounter(index);
            }
        }
        else  //for AMD SW D3D counters are added at the end (for Intel, they are first and last)
        {
            gpa_uint32 totalCounters = m_pCounterAccessor->GetNumCounters();

            if ((index >= totalCounters - s_pSwCounterManager->GetNumSwCounters()) && index < totalCounters)
            {
                s_pSwCounterManager->DisableSwCounter(index);
            }
        }

#endif // WIN32
    }

    return status;
}

void GPA_CounterSchedulerDX11::DisableAllCounters()
{
    GPA_CounterSchedulerBase::DisableAllCounters();

    s_pSwCounterManager->ClearEnabledSwCounters();
}

GPACounterSplitterAlgorithm GPA_CounterSchedulerDX11::GetPreferredSplittingAlgorithm()
{
    return CONSOLIDATED;
}
