//==============================================================================
// Copyright (c) 2016-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for CL counter generation.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_CL_GPA_COUNTER_GENERATOR_CL_H_
#define GPU_PERF_API_COUNTER_GENERATOR_CL_GPA_COUNTER_GENERATOR_CL_H_

#include "gpu_perf_api_counter_generator/gpa_counter_generator_base.h"

/// @brief The OpenCL-specific counter generator.
class GpaCounterGeneratorCl : public GpaCounterGeneratorBase
{
public:
    /// @brief Constructor.
    GpaCounterGeneratorCl();

protected:
    /// @copydoc GpaCounterGeneratorBase::GeneratePublicCounters()
    GpaStatus GeneratePublicCounters(GDT_HW_GENERATION   desired_generation,
                                     GDT_HW_ASIC_TYPE    asic_type,
                                     GpaUInt8            generate_asic_specific_counters,
                                     GpaDerivedCounters* public_counters) override;

    /// @copydoc GpaCounterGeneratorBase::GenerateHardwareCounters()
    GpaStatus GenerateHardwareCounters(GDT_HW_GENERATION    desired_generation,
                                       GDT_HW_ASIC_TYPE     asic_type,
                                       GpaUInt8             generate_asic_specific_counters,
                                       GpaHardwareCounters* hardware_counters) override;

    /// @copydoc GpaCounterGeneratorBase::GenerateHardwareExposedCounters()
    GpaStatus GenerateHardwareExposedCounters(GDT_HW_GENERATION    desired_generation,
                                              GDT_HW_ASIC_TYPE     asic_type,
                                              GpaUInt8             generate_asic_specific_counters,
                                              GpaHardwareCounters* hardware_counters) override;

private:
    /// @brief Function to map from GPA block index to the OCL driver's block index for a particular hw generation.
    ///
    /// @param [in] desired_generation The hardware generation.
    /// @param [in] block_index GPA's block index.
    ///
    /// @return The OCL driver's block index.
    int GetDriverGroupId(GDT_HW_GENERATION desired_generation, int block_index) const;

    /// @brief Generates internal counters.
    ///
    /// @param [in] hardware_counters The hardware counters to generate.
    /// @param [in] generation The generation for which counters need to be generated.
    ///
    /// @return True on success.
    bool GenerateInternalCounters(GpaHardwareCounters* hardware_counters, GDT_HW_GENERATION generation) const;
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_CL_GPA_COUNTER_GENERATOR_CL_H_
