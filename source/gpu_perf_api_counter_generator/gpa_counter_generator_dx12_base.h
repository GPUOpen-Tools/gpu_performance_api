//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
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
    /// @brief Get the SW counter description for the given SW counter index.
    ///
    /// @param [in] sw_counter_index The SW counter index.
    /// @param [out] sw_counter_desc Software counter description.
    ///
    /// @return The SW counter description.
    static bool GetSwCounterDesc(const GpaUInt32 sw_counter_index, GpaSoftwareCounterDesc& sw_counter_desc);

    /// @brief Constructor.
    GpaCounterGeneratorDx12Base() = default;

    /// @brief Virtual Destructor.
    virtual ~GpaCounterGeneratorDx12Base() = default;

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

    /// @copydoc GpaCounterGeneratorBase::ComputeSWCounterValue()
    void ComputeSwCounterValue(GpaUInt32 software_counter_index, GpaUInt64 value, void* result, const GpaHwInfo* hw_info) const override;

private:
    static const GpaSoftwareCounterDesc kDx12SoftwareCounters[];     ///< DX12 SW counters list.
    static const size_t                 kDx12SoftwareCountersCount;  ///< DX12 SW counter list size.

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

    /// @brief Generate DX12 API software counters.
    ///
    /// @return kGpaStatusOk if generating counters succeeded, false if it failed.
    GpaStatus GenerateDX12SoftwareCounters() const;
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_DX12_GPA_COUNTER_GENERATOR_DX12_BASE_H_
