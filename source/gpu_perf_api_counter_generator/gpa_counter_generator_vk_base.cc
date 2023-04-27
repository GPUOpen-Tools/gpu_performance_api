//==============================================================================
// Copyright (c) 2017-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for VK counter generation.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator_vk_base.h"

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

GpaStatus GpaCounterGeneratorVkBase::GeneratePublicCounters(GDT_HW_GENERATION   desired_generation,
                                                            GDT_HW_ASIC_TYPE    asic_type,
                                                            GpaUInt8            generate_asic_specific_counters,
                                                            GpaDerivedCounters* public_counters)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);
    UNREFERENCED_PARAMETER(public_counters);
    return kGpaStatusOk;
}

GpaStatus GpaCounterGeneratorVkBase::GenerateHardwareCounters(GDT_HW_GENERATION    desired_generation,
                                                              GDT_HW_ASIC_TYPE     asic_type,
                                                              GpaUInt8             generate_asic_specific_counters,
                                                              GpaHardwareCounters* hardware_counters)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(generate_asic_specific_counters);
    UNREFERENCED_PARAMETER(hardware_counters);
    return kGpaStatusOk;
}
