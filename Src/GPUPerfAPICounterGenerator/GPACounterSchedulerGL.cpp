//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Class for counter scheduling for GL
//==============================================================================

#include "GPACounterSchedulerGL.h"
#include "GPACounterGeneratorSchedulerManager.h"

GPA_CounterSchedulerGL::GPA_CounterSchedulerGL()
{
    // TODO: need to make some changes to support GPUTime counter on non-AMD in public build
    for (int gen = GDT_HW_GENERATION_FIRST_AMD; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterScheduler(GPA_API_OPENGL, static_cast<GDT_HW_GENERATION>(gen), this);
    }

    // AMD only for GLES (for now) -- will allow non-AMD once GPUTime is supported in public builds
    for (int gen = GDT_HW_GENERATION_FIRST_AMD; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterScheduler(GPA_API_OPENGLES, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GPACounterSplitterAlgorithm GPA_CounterSchedulerGL::GetPreferredSplittingAlgorithm()
{
    return CONSOLIDATED;
}
