//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief DX12 counter generation for non-AMD hardware (used simply to register the generator).
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx12_non_amd.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

GpaCounterGeneratorDx12NonAmd::GpaCounterGeneratorDx12NonAmd()
{
    // Enable only sw counters.
    GpaCounterGeneratorBase::SetAllowedCounters(false, false, true);

    // Allow future registrations to override this default one.
    CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(kGpaApiDirectx12, GDT_HW_GENERATION_INTEL, this, false);

    // Allow future registrations to override this default one.
    CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(kGpaApiDirectx12, GDT_HW_GENERATION_NVIDIA, this, false);
}
