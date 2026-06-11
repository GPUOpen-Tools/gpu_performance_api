//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
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
    /// @brief Default constructor not allowed.
    GpaCounterGeneratorDx12() = delete;

    /// @brief Generates internal counters.
    ///
    /// @param [in] hardware_counters The hardware counters to generate.
    /// @param [in] generation The generation for which counters need to be generated.
    ///
    /// @return True on success.
    static bool GenerateInternalCounters(GpaHardwareCounters* hardware_counters, device_info::HwGeneration generation);
};

#endif
