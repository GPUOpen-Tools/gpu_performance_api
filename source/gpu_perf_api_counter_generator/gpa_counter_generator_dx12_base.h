//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for common DX12 counter generation.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_DX12_GPA_COUNTER_GENERATOR_DX12_BASE_H_
#define GPU_PERF_API_COUNTER_GENERATOR_DX12_GPA_COUNTER_GENERATOR_DX12_BASE_H_

#include "gpu_perf_api_counter_generator/gpa_counter_generator_base.h"

/// @brief The DX12 common counter generator.
class GpaCounterGeneratorDx12Base : public GpaCounterGeneratorBase
{
public:
    /// @brief Constructor.
    explicit GpaCounterGeneratorDx12Base(GpaSessionSampleType sample_type)
        : GpaCounterGeneratorBase(sample_type)
    {
    }

    /// @brief Virtual Destructor.
    virtual ~GpaCounterGeneratorDx12Base() = default;

protected:
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
    GpaCounterGeneratorDx12Base() = delete;

    /// @brief Copy constructor - private override to prevent usage.
    GpaCounterGeneratorDx12Base(const GpaCounterGeneratorDx12Base&) = delete;

    /// @brief Move constructor - private override to prevent usage.
    GpaCounterGeneratorDx12Base(GpaCounterGeneratorDx12Base&&) = delete;

    /// @brief Copy operator - private override to prevent usage.
    ///
    /// @return reference to object.
    GpaCounterGeneratorDx12Base& operator=(const GpaCounterGeneratorDx12Base&) = delete;

    /// @brief Move operator - private override to prevent usage.
    ///
    /// @return reference to object.
    GpaCounterGeneratorDx12Base& operator=(GpaCounterGeneratorDx12Base&&) = delete;
};

#endif
