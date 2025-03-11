//==============================================================================
// Copyright (c) 2017-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for VK counter generation.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator_vk_base.h"

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

GpaCounterGeneratorVkBase::GpaCounterGeneratorVkBase(GpaSessionSampleType sample_type)
    : GpaCounterGeneratorBase(sample_type)
{
}

GpaStatus GpaCounterGeneratorVkBase::GeneratePublicCounters(GDT_HW_GENERATION   desired_generation,
                                                            GDT_HW_ASIC_TYPE    asic_type,
                                                            GpaDerivedCounters* public_counters)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(public_counters);
    return kGpaStatusOk;
}

GpaStatus GpaCounterGeneratorVkBase::GenerateHardwareCounters(GDT_HW_GENERATION    desired_generation,
                                                              GDT_HW_ASIC_TYPE     asic_type,
                                                              GpaHardwareCounters* hardware_counters)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(hardware_counters);
    return kGpaStatusOk;
}
