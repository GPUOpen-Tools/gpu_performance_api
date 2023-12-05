//==============================================================================
// Copyright (c) 2017-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Common DX12 counter generation.
//==============================================================================

#include <d3d12.h>

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx12_base.h"
#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

GpaStatus GpaCounterGeneratorDx12Base::GeneratePublicCounters(GDT_HW_GENERATION   desired_generation,
                                                              GDT_HW_ASIC_TYPE    asic_type,
                                                              GpaDerivedCounters* public_counters)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(public_counters);
    return kGpaStatusOk;
}

GpaStatus GpaCounterGeneratorDx12Base::GenerateHardwareCounters(GDT_HW_GENERATION    desired_generation,
                                                                GDT_HW_ASIC_TYPE     asic_type,
                                                                GpaHardwareCounters* hardware_counters)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(hardware_counters);
    return kGpaStatusOk;
}
