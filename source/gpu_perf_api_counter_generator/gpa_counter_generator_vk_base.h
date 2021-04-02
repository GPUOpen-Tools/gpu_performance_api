//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
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
    /// @brief Get the SW counter description for the given SW counter index.
    ///
    /// \param [in] sw_counter_index The SW counter index.
    /// \param [out] sw_counter_desc Software counter description.
    ///
    /// \return The SW counter description.
    static bool GetSwCounterDesc(const GpaUInt32 sw_counter_index, GpaSoftwareCounterDesc& sw_counter_desc);

    /// @brief Constructor.
    GpaCounterGeneratorVkBase() = default;

    /// @brief Virtual destructor.
    virtual ~GpaCounterGeneratorVkBase() = default;

protected:
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

    /// @copydoc GpaCounterGeneratorBase::ComputeSwCounterValue()
    virtual void ComputeSwCounterValue(GpaUInt32 sw_counter_index, GpaUInt64 value, void* result, const GpaHwInfo* hw_info) const override;

private:
    static const GpaSoftwareCounterDesc kVkSoftwareCounters[];     ///< VK SW counters list.
    static const size_t                 kVkSoftwareCountersCount;  ///< VK SW counter list size.

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

    /// @brief Generate VK API software counters.
    ///
    /// @return kGpaStatusOk if generating counters succeeded, false if it failed.
    GpaStatus GenerateVKSoftwareCounters();
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_VK_GPA_COUNTER_GENERATOR_VK_BASE_H_
