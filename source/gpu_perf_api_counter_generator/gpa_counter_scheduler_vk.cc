//==============================================================================
// Copyright (c) 2016-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Class for counter scheduling for VK
//==============================================================================

#include "gpa_counter_scheduler_vk.h"
#include "gpa_counter_generator_scheduler_manager.h"

GPA_CounterSchedulerVK::GPA_CounterSchedulerVK()
{
    for (int gen = GDT_HW_GENERATION_NVIDIA; gen < GDT_HW_GENERATION_LAST; gen++)
    {
        CounterGeneratorSchedulerManager::Instance()->RegisterCounterScheduler(GPA_API_VULKAN, static_cast<GDT_HW_GENERATION>(gen), this);
    }
}

GPACounterSplitterAlgorithm GPA_CounterSchedulerVK::GetPreferredSplittingAlgorithm() const
{
    return CONSOLIDATED;
}
