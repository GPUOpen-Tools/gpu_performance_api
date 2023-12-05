//==============================================================================
// Copyright (c) 2017-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for VK counter generation.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATION_VK_GPA_COUNTER_GENERATOR_VK_H_
#define GPU_PERF_API_COUNTER_GENERATION_VK_GPA_COUNTER_GENERATOR_VK_H_

#include "gpu_perf_api_counter_generator/gpa_counter_generator_vk_base.h"

/// @brief The VK-specific counter generator.
class GpaCounterGeneratorVk : public GpaCounterGeneratorVkBase
{
public:
    /// @brief Construct a GPA VK counter generator.
    GpaCounterGeneratorVk();

    /// @brief Destroy this GPA VK counter generator.
    virtual ~GpaCounterGeneratorVk() = default;

    /// @brief Copy constructor - private override to prevent usage.
    GpaCounterGeneratorVk(const GpaCounterGeneratorVk&) = delete;

    /// @brief Move constructor - private override to prevent usage.
    GpaCounterGeneratorVk(GpaCounterGeneratorVk&&) = delete;

    /// @brief Copy operator - private override to prevent usage.
    ///
    /// @return Reference to object.
    GpaCounterGeneratorVk& operator=(const GpaCounterGeneratorVk&) = delete;

    /// @brief Move operator - private override to prevent usage.
    ///
    /// @return Reference to object.
    GpaCounterGeneratorVk& operator=(GpaCounterGeneratorVk&&) = delete;

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
    /// @brief Checks if the given hw generation represents an AMD GPU.
    ///
    /// @param [in] generation The hardware generation to check.
    ///
    /// @return True if the hardware generation represents and AMD GPU.
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
    static GpaUInt32 CalculateBlockIdVk(GDT_HW_GENERATION generation, GpaCounterGroupDesc* group);

    /// @brief Generates internal counters.
    ///
    /// @param [in] hardware_counters The hardware counters to generate.
    /// @param [in] generation The generation for which counters need to be generated.
    ///
    /// @return True on success.
    static bool GenerateInternalCounters(GpaHardwareCounters* hardware_counters, GDT_HW_GENERATION generation);
};

#endif  // GPU_PERF_API_COUNTER_GENERATION_VK_GPA_COUNTER_GENERATOR_VK_H_
