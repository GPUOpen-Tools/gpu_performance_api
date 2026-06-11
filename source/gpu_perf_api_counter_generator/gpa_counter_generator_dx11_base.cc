//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Base class for DX11 counter generation -- add D3D11 Query counters which are supported on all hardware.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx11_base.h"

#ifdef EXTRA_COUNTER_INFO
#include <sstream>
#endif

#include <d3d11.h>

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_common/logging.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

GpaCounterGeneratorDx11Base::GpaCounterGeneratorDx11Base(GpaSessionSampleType sampleType)
    : GpaCounterGeneratorBase(sampleType)
{
}

GpaStatus GpaCounterGeneratorDx11Base::GeneratePublicCounters(device_info::HwGeneration desired_generation,
                                                              device_info::AsicType     asic_type,
                                                              GpaDerivedCounters*       public_counters)
{
    // Do nothing in base class.
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(public_counters);
    return kGpaStatusOk;
}

GpaStatus GpaCounterGeneratorDx11Base::GenerateHardwareCounters(device_info::HwGeneration desired_generation,
                                                                device_info::AsicType     asic_type,
                                                                GpaHardwareCounters*      hardware_counters)
{
    // Do nothing in base class.
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(asic_type);
    UNREFERENCED_PARAMETER(hardware_counters);
    return kGpaStatusOk;
}
