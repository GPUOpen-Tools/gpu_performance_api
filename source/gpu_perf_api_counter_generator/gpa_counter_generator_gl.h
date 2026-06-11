//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for GL counter generation.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_GL_GPA_COUNTER_GENERATOR_GL_H_
#define GPU_PERF_API_COUNTER_GENERATOR_GL_GPA_COUNTER_GENERATOR_GL_H_

#include <memory>

#include "gpu_perf_api_counter_generator/gpa_counter_generator_base.h"

/// @brief The OpenGL-specific counter generator.
class GpaCounterGeneratorGl : public GpaCounterGeneratorBase
{
public:
    /// @brief Constructor.
    explicit GpaCounterGeneratorGl(GpaSessionSampleType sample_type);

    /// @brief Virtual destructor.
    virtual ~GpaCounterGeneratorGl();

protected:
    /// @copydoc GpaCounterGeneratorBase::GeneratePublicCounters()
    GpaStatus GeneratePublicCounters(device_info::HwGeneration desired_generation,
                                     device_info::AsicType     asic_type,
                                     GpaDerivedCounters*       public_counters) override;

    /// @copydoc GpaCounterGeneratorBase::GenerateHardwareCounters()
    GpaStatus GenerateHardwareCounters(device_info::HwGeneration desired_generation,
                                       device_info::AsicType     asic_type,
                                       GpaHardwareCounters*      hardware_counters) override;

    /// @copydoc GpaCounterGeneratorBase::GenerateHardwareExposedCounters()
    GpaStatus GenerateHardwareExposedCounters(device_info::HwGeneration desired_generation,
                                              device_info::AsicType     asic_type,
                                              GpaHardwareCounters*      hardware_counters) override;

private:
    /// @brief Delete default constructor.
    GpaCounterGeneratorGl() = delete;

    /// @brief Helper function to generate the driver-supplied counters.
    ///
    /// @param [in] hardware_counters The list of hardware counters to augment with the driver-supplied counters.
    /// @param [in] global_counter_index The global index of the current counter added to the hardware counters list.
    ///
    /// @return True on success, false on failure.
    bool GenerateDriverSuppliedInternalCounters(GpaHardwareCounters* hardware_counters, unsigned int global_counter_index);

    /// @brief Helper function to generate the internal counters.
    ///
    /// @param [in] hardware_counters The list of hardware counters to augment with the driver-supplied counters.
    /// @param [in] generation the hardware generation whose internal counters are needed.
    ///
    /// @return True on success, false on failure.
    GpaStatus GenerateInternalCounters(GpaHardwareCounters* hardware_counters, device_info::HwGeneration generation);

    /// @brief Helper function to cleanup and release memory.
    void Cleanup();

    std::vector<GpaCounterGroupDesc>               driver_supplied_groups_;        ///< Driver-supplied counter groups.
    unsigned int                                   driver_supplied_groups_count_;  ///< Number of driver-supplied counter groups.
    std::map<GpaUInt32, GpaHardwareCounterDescExt> driver_supplied_counters_;      ///< List of driver-supplied counters.

    // The following vectors are used to track and free allocated memory.
    std::vector<std::unique_ptr<GpaHardwareCounterDesc>> hardware_counter_descs_;  ///< Allocated GpaHardwareCounterDescs.
    std::vector<std::unique_ptr<char[]>>                 counter_buffers_;         ///< Allocated driver supplied counter buffers.
};

#endif
