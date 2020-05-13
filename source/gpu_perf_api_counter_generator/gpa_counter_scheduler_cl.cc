//==============================================================================
// Copyright (c) 2016-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for counter scheduling for CL
//==============================================================================

#include "gpa_counter_scheduler_cl.h"
#include "gpa_counter_generator_scheduler_manager.h"


GPA_CounterSchedulerCL::GPA_CounterSchedulerCL()
{
    for (int gen = GDT_HW_GENERATION_FIRST_AMD; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterScheduler(GPA_API_OPENCL, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GPACounterSplitterAlgorithm GPA_CounterSchedulerCL::GetPreferredSplittingAlgorithm() const
{
    return CONSOLIDATED;
}
