//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
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
    ///
    /// @param [in] sample_type The type of samples for which to generate counters.
    GpaCounterGeneratorVk(GpaSessionSampleType sample_type);

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
    virtual GpaStatus GeneratePublicCounters(device_info::HwGeneration desired_generation,
                                             device_info::AsicType     asic_type,
                                             GpaDerivedCounters*       public_counters) override;

    /// @copydoc GpaCounterGeneratorBase::GenerateHardwareCounters()
    virtual GpaStatus GenerateHardwareCounters(device_info::HwGeneration desired_generation,
                                               device_info::AsicType     asic_type,
                                               GpaHardwareCounters*      hardware_counters) override;

    /// @copydoc GpaCounterGeneratorBase::GenerateHardwareExposedCounters()
    GpaStatus GenerateHardwareExposedCounters(device_info::HwGeneration desired_generation,
                                              device_info::AsicType     asic_type,
                                              GpaHardwareCounters*      hardware_counters) override;

private:
    /// @brief Delete default constructor.
    GpaCounterGeneratorVk() = delete;

    /// @brief Generates internal counters.
    ///
    /// @param [in] hardware_counters The hardware counters to generate.
    /// @param [in] generation The generation for which counters need to be generated.
    ///
    /// @return True on success.
    static bool GenerateInternalCounters(GpaHardwareCounters* hardware_counters, device_info::HwGeneration generation);
};

#endif
