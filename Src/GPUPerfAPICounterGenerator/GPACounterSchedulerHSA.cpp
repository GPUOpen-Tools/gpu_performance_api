//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for counter scheduling for HSA
//==============================================================================

#include "GPACounterSchedulerHSA.h"
#include "GPACounterGeneratorSchedulerManager.h"

GPA_CounterSchedulerHSA::GPA_CounterSchedulerHSA()
{
    for (int gen = GDT_HW_GENERATION_VOLCANICISLAND; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterScheduler(GPA_API_ROCM, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GPACounterSplitterAlgorithm GPA_CounterSchedulerHSA::GetPreferredSplittingAlgorithm() const
{
    return CONSOLIDATED;
}
