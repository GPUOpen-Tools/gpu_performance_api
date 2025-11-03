//==============================================================================
// Copyright (c) 2015-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for DX12 counter generation.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_DX12_GPA_COUNTER_GENERATOR_DX12_H_
#define GPU_PERF_API_COUNTER_GENERATOR_DX12_GPA_COUNTER_GENERATOR_DX12_H_

#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx12_base.h"

/// @brief The DX12-specific counter generator.
class GpaCounterGeneratorDx12 : public GpaCounterGeneratorDx12Base
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] sample_type The type of samples for which to generate counters.
    GpaCounterGeneratorDx12(GpaSessionSampleType sample_type);

    /// @brief Virtual destructor.
    virtual ~GpaCounterGeneratorDx12() = default;

    /// @brief Copy constructor - private override to prevent usage.
    GpaCounterGeneratorDx12(const GpaCounterGeneratorDx12Base&) = delete;

    /// @brief Move constructor - private override to prevent usage.
    GpaCounterGeneratorDx12(GpaCounterGeneratorDx12Base&&) = delete;

    /// @brief Copy operator - private override to prevent usage.
    ///
    /// @return Reference to object.
    GpaCounterGeneratorDx12& operator=(const GpaCounterGeneratorDx12&) = delete;

    /// @brief Move operator - private override to prevent usage.
    ///
    /// @return Reference to object.
    GpaCounterGeneratorDx12& operator=(GpaCounterGeneratorDx12&&) = delete;

protected:
    /// @copydoc GpaCounterGeneratorBase::GeneratePublicCounters()
    virtual GpaStatus GeneratePublicCounters(GDT_HW_GENERATION   desired_generation,
                                             GDT_HW_ASIC_TYPE    asic_type,
                                             GpaDerivedCounters* public_counters) override;

    /// @copydoc GpaCounterGeneratorBase::GenerateHardwareCounters()
    virtual GpaStatus GenerateHardwareCounters(GDT_HW_GENERATION    desired_generation,
                                               GDT_HW_ASIC_TYPE     asic_type,
                                               GpaHardwareCounters* hardware_counters) override;

    /// @copydoc GpaCounterGeneratorBase::GenerateHardwareExposedCounters()
    GpaStatus GenerateHardwareExposedCounters(GDT_HW_GENERATION    desired_generation,
                                              GDT_HW_ASIC_TYPE     asic_type,
                                              GpaHardwareCounters* hardware_counters) override;

private:
    /// @brief Default constructor not allowed.
    GpaCounterGeneratorDx12() = delete;

    /// @brief Helper function to indicates whether the specified HW generation represents an AMD GPU.
    ///
    /// @param [in] generation The hw generation to check.
    ///
    /// @return True if the specified HW generation represents an AMD GPU.
    static bool IsAmdGpu(GDT_HW_GENERATION generation);

    /// @brief Logic inside this function is based on the AmdExtGpuBlock enum in AmdExtGpaInterface in DXCP driver.
    ///
    /// The driver gives each block an ID, but ignores the instance. GPA treats each instance as a different
    /// block, so we need to translate.
    ///
    /// @param [in] generation The generation whose block id needs to be calculated.
    /// @param [in] group The group for which the block id needs to be calculated.
    ///
    /// @return The block id according to the driver.
    static GpaUInt32 CalculateBlockIdDx12(GDT_HW_GENERATION generation, const GpaCounterGroupDesc& group);

    /// @brief Generates internal counters.
    ///
    /// @param [in] hardware_counters The hardware counters to generate.
    /// @param [in] generation The generation for which counters need to be generated.
    ///
    /// @return True on success.
    static bool GenerateInternalCounters(GpaHardwareCounters* hardware_counters, GDT_HW_GENERATION generation);
};

#endif
