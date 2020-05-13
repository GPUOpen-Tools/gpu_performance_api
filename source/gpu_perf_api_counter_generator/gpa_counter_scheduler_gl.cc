//==============================================================================
// Copyright (c) 2016-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Class for counter scheduling for GL
//==============================================================================

#include "gpa_counter_scheduler_gl.h"
#include "gpa_counter_generator_scheduler_manager.h"

GPA_CounterSchedulerGL::GPA_CounterSchedulerGL()
{
    // TODO: need to make some changes to support GPUTime counter on non-AMD in public build
    for (int gen = GDT_HW_GENERATION_FIRST_AMD; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterScheduler(GPA_API_OPENGL, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GPACounterSplitterAlgorithm GPA_CounterSchedulerGL::GetPreferredSplittingAlgorithm() const
{
    return CONSOLIDATED;
}
