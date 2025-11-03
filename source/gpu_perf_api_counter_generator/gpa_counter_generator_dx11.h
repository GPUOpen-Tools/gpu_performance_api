//==============================================================================
// Copyright (c) 2016-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for DX11 counter generation for AMD HW.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_DX11_GPA_COUNTER_GENERATOR_DX11_H_
#define GPU_PERF_API_COUNTER_GENERATOR_DX11_GPA_COUNTER_GENERATOR_DX11_H_

#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx11_base.h"

/// @brief Class for DX11 counter generation for AMD HW.
class GpaCounterGeneratorDx11 : public GpaCounterGeneratorDx11Base
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] sample_type The type of samples for which to generate counters.
    GpaCounterGeneratorDx11(GpaSessionSampleType sample_type);

protected:
    /// @copydoc GpaCounterGeneratorBase::GeneratePublicCounters()
    GpaStatus GeneratePublicCounters(GDT_HW_GENERATION   desired_generation,
                                     GDT_HW_ASIC_TYPE    asic_type,
                                     GpaDerivedCounters* public_counters) override;

    /// @copydoc GpaCounterGeneratorBase::GenerateHardwareCounters()
    GpaStatus GenerateHardwareCounters(GDT_HW_GENERATION    desired_generation,
                                       GDT_HW_ASIC_TYPE     asic_type,
                                       GpaHardwareCounters* hardware_counters) override;

    /// @copydoc GpaCounterGeneratorBase::GenerateHardwareExposedCounters()
    GpaStatus GenerateHardwareExposedCounters(GDT_HW_GENERATION    desired_generation,
                                              GDT_HW_ASIC_TYPE     asic_type,
                                              GpaHardwareCounters* hardware_counters) override;

private:
    /// @brief Delete default constructor.
    GpaCounterGeneratorDx11() = delete;

    /// @brief Generates internal counters.
    ///
    /// @param [in] hardware_counters The hardware counters to generate.
    /// @param [in] generation The generation for which counters need to be generated.
    ///
    /// @return True on success.
    static bool GenerateInternalCounters(GpaHardwareCounters* hardware_counters, GDT_HW_GENERATION generation);
};

#endif
