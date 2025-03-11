//==============================================================================
// Copyright (c) 2016-2024 Advanced Micro Devices, Inc. All rights reserved.
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
    GpaCounterGeneratorDx11Base(GpaSessionSampleType sample_type);

    /// @copydoc GpaCounterGeneratorBase::GeneratePublicCounters()
    virtual GpaStatus GeneratePublicCounters(GDT_HW_GENERATION   desired_generation,
                                             GDT_HW_ASIC_TYPE    asic_type,
                                             GpaDerivedCounters* public_counters) override;

    /// @copydoc GpaCounterGeneratorBase::GenerateHardwareCounters()
    virtual GpaStatus GenerateHardwareCounters(GDT_HW_GENERATION    desired_generation,
                                               GDT_HW_ASIC_TYPE     asic_type,
                                               GpaHardwareCounters* hardware_counters) override;

    /// @brief Helper function to indicates whether the specified HW generation represents an AMD GPU.
    ///
    /// @param [in] generation The hw generation to check.
    ///
    /// @return True if the specified HW generation represents an AMD GPU.
    static bool IsAmdGpu(GDT_HW_GENERATION generation);

private:
    /// @brief Delete default constructor.
    GpaCounterGeneratorDx11Base() = delete;

    GpaCounterGroupDesc d3d_counter_group_ = {0, "D3D11", 0, 0, 0};  ///< Description for D3D11 counter group.
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_DX11_GPA_COUNTER_GENERATOR_DX11_BASE_H_
