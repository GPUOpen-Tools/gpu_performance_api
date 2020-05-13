//==============================================================================
// Copyright (c) 2016-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Class for counter scheduling for DX12
//==============================================================================

#include "gpa_counter_scheduler_dx12.h"
#include "gpa_counter_generator_scheduler_manager.h"

GPA_CounterSchedulerDX12::GPA_CounterSchedulerDX12()
{
    for (int gen = GDT_HW_GENERATION_NVIDIA; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterScheduler(GPA_API_DIRECTX_12, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GPACounterSplitterAlgorithm GPA_CounterSchedulerDX12::GetPreferredSplittingAlgorithm() const
{
    return CONSOLIDATED;
}
