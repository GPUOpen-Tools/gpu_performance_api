//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Base class for DX11 counter generation -- add D3D11 Query counters which are supported on all hardware.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_DX11_GPA_COUNTER_GENERATOR_DX11_BASE_H_
#define GPU_PERF_API_COUNTER_GENERATOR_DX11_GPA_COUNTER_GENERATOR_DX11_BASE_H_

#include "gpu_perf_api_counter_generator/gpa_counter_generator_base.h"

/// @brief Base class for DX11 counter generation -- add D3D11 Query counters which are supported on all hardware.
class GpaCounterGeneratorDx11Base : public GpaCounterGeneratorBase
{
public:
    /// @brief Constructor.
    GpaCounterGeneratorDx11Base();

    /// @copydoc GpaCounterGeneratorBase::GeneratePublicCounters()
    virtual GpaStatus GeneratePublicCounters(GDT_HW_GENERATION   desired_generation,
                                             GDT_HW_ASIC_TYPE    asic_type,
                                             GpaUInt8            generate_asic_specific_counters,
                                             GpaDerivedCounters* public_counters) override;

    /// @copydoc GpaCounterGeneratorBase::GenerateHardwareCounters()
    virtual GpaStatus GenerateHardwareCounters(GDT_HW_GENERATION    desired_generation,
                                               GDT_HW_ASIC_TYPE     asic_type,
                                               GpaUInt8             generate_asic_specific_counters,
                                               GpaHardwareCounters* hardware_counters) override;

    /// @copydoc GpaCounterGeneratorBase::GenerateSoftwareCounters()
    virtual GpaStatus GenerateSoftwareCounters(GDT_HW_GENERATION    desired_generation,
                                               GDT_HW_ASIC_TYPE     asic_type,
                                               GpaUInt8             generate_asic_specific_counters,
                                               GpaSoftwareCounters* software_counters) override;

    /// @copydoc IGpaCounterAccessor::ComputeSwCounterValue()
    void ComputeSwCounterValue(GpaUInt32 software_counter_index, GpaUInt64 value, void* result, const GpaHwInfo* hw_info) const override;

    /// @brief Get the D3D11_QUERY enum value based on our own software counter index.
    ///
    /// @param [in] index Our SW counter index.
    ///
    /// @return A D3D11_QUERY enum value.
    GpaUInt32 GetD3D11Enum(GpaUInt32 index) const;

    /// @brief Add D3D software counters.
    ///
    /// @param [in] desired_generation The desired GDT_HW_GENERATION.
    void GenerateD3DSoftwareCounters(GDT_HW_GENERATION desired_generation);

    /// @brief Helper function to indicates whether the specified HW generation represents an AMD GPU.
    ///
    /// @param [in] generation The hw generation to check.
    ///
    /// @return True if the specified HW generation represents an AMD GPU.
    static bool IsAmdGpu(GDT_HW_GENERATION generation);

private:
    GpaCounterGroupDesc d3d_counter_group_ = {0, "D3D11", 0, 0, 0};  ///< Description for D3D11 counter group.
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_DX11_GPA_COUNTER_GENERATOR_DX11_BASE_H_
