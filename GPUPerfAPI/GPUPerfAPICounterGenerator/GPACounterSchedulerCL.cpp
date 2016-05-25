//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for counter scheduling for CL
//==============================================================================

#include "GPACounterSchedulerCL.h"
#include "GPACounterGeneratorSchedulerManager.h"

GPA_CounterSchedulerCL::GPA_CounterSchedulerCL()
{
    for (int gen = GDT_HW_GENERATION_FIRST_AMD; gen < GDT_HW_GENERATION_LAST; gen = gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterScheduler(GPA_API_OPENCL, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GPACounterSplitterAlgorithm GPA_CounterSchedulerCL::GetPreferredSplittingAlgorithm()
{
    return CONSOLIDATED;
}
