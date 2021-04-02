//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for DX11 counter generation for non-AMD hardware (used simply to register the generator).
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx11_non_amd.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

GpaCounterGeneratorDx11NonAmd::GpaCounterGeneratorDx11NonAmd()
{
    // Enable sw counters.
    GpaCounterGeneratorBase::SetAllowedCounters(false, false, true);

    // Allow future registrations to override this default one.
    CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(kGpaApiDirectx11, GDT_HW_GENERATION_INTEL, this, false);

    // Allow future registrations to override this default one.
    CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(kGpaApiDirectx11, GDT_HW_GENERATION_NVIDIA, this, false);
}
