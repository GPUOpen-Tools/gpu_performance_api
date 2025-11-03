//==============================================================================
// Copyright (c) 2017-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for VK Base counter generation.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_VK_GPA_COUNTER_GENERATOR_VK_BASE_H_
#define GPU_PERF_API_COUNTER_GENERATOR_VK_GPA_COUNTER_GENERATOR_VK_BASE_H_

#include "gpu_perf_api_counter_generator/gpa_counter_generator_base.h"

/// @brief The VK-specific counter generator.
class GpaCounterGeneratorVkBase : public GpaCounterGeneratorBase
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] sample_type The type of samples for which to generate counters.
    GpaCounterGeneratorVkBase(GpaSessionSampleType sample_type);

    /// @brief Virtual destructor.
    virtual ~GpaCounterGeneratorVkBase() = default;

protected:
    /// @copydoc GpaCounterGeneratorBase::GeneratePublicCounters()
    virtual GpaStatus GeneratePublicCounters(GDT_HW_GENERATION   desired_generation,
                                             GDT_HW_ASIC_TYPE    asic_type,
                                             GpaDerivedCounters* public_counters) override;

    /// @copydoc GpaCounterGeneratorBase::GenerateHardwareCounters()
    virtual GpaStatus GenerateHardwareCounters(GDT_HW_GENERATION    desired_generation,
                                               GDT_HW_ASIC_TYPE     asic_type,
                                               GpaHardwareCounters* hardware_counters) override;

private:
    /// @brief Delete default constructor.
    GpaCounterGeneratorVkBase() = delete;

    /// @brief Copy constructor - private override to prevent usage.
    GpaCounterGeneratorVkBase(const GpaCounterGeneratorVkBase&) = delete;

    /// @brief Move constructor - private override to prevent usage.
    GpaCounterGeneratorVkBase(GpaCounterGeneratorVkBase&&) = delete;

    /// @brief Copy operator - private override to prevent usage.
    ///
    /// @return Reference to object.
    GpaCounterGeneratorVkBase& operator=(const GpaCounterGeneratorVkBase&) = delete;

    /// @brief Move operator - private override to prevent usage.
    ///
    /// @return Reference to object.
    GpaCounterGeneratorVkBase& operator=(GpaCounterGeneratorVkBase&&) = delete;
};

#endif
