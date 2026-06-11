//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Base class for DX11 counter generation.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_DX11_GPA_COUNTER_GENERATOR_DX11_BASE_H_
#define GPU_PERF_API_COUNTER_GENERATOR_DX11_GPA_COUNTER_GENERATOR_DX11_BASE_H_

#include "gpu_perf_api_counter_generator/gpa_counter_generator_base.h"

/// @brief Base class for DX11 counter generation -- add D3D11 Query counters which are supported on all hardware.
class GpaCounterGeneratorDx11Base : public GpaCounterGeneratorBase
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] sample_type The type of samples for which to generate counters.
    explicit GpaCounterGeneratorDx11Base(GpaSessionSampleType sample_type);

    /// @copydoc GpaCounterGeneratorBase::GeneratePublicCounters()
    virtual GpaStatus GeneratePublicCounters(device_info::HwGeneration desired_generation,
                                             device_info::AsicType     asic_type,
                                             GpaDerivedCounters*       public_counters) override;

    /// @copydoc GpaCounterGeneratorBase::GenerateHardwareCounters()
    virtual GpaStatus GenerateHardwareCounters(device_info::HwGeneration desired_generation,
                                               device_info::AsicType     asic_type,
                                               GpaHardwareCounters*      hardware_counters) override;

private:
    /// @brief Delete default constructor.
    GpaCounterGeneratorDx11Base() = delete;

    GpaCounterGroupDesc d3d_counter_group_ = {.group_index                  = 0,
                                              .name                         = "D3D11",
                                              .num_counters                 = 0,
                                              .max_active_discrete_counters = 0,
                                              .max_active_spm_counters      = 0};  ///< Description for D3D11 counter group.
};

#endif
