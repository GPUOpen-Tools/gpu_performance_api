//==============================================================================
// Copyright (c) 2017-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Vulkan counter generation for non-AMD hardware (used simply to register the generator).
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator_vk_non_amd.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

GpaCounterGeneratorVkNonAmd::GpaCounterGeneratorVkNonAmd()
{
    GpaCounterGeneratorBase::SetAllowedCounters(false, false);

    // Allow future registrations to override this default one.
    CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(kGpaApiVulkan, GDT_HW_GENERATION_INTEL, this, false);

    // Allow future registrations to override this default one.
    CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(kGpaApiVulkan, GDT_HW_GENERATION_NVIDIA, this, false);
}
