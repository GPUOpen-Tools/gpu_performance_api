//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Base class for counter generation.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_COUNTER_GENERATOR_BASE_H_
#define GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_COUNTER_GENERATOR_BASE_H_

#include <unordered_map>

#include "gpu_perf_api_counter_generator/gpa_counter_accessor_interface.h"
#include "gpu_perf_api_counter_generator/gpa_hardware_counters.h"
#include "gpu_perf_api_counter_generator/gpa_software_counters.h"

/// @brief Base class for counter generation.
class GpaCounterGeneratorBase : public IGpaCounterAccessor
{
public:
    /// @brief Constructor.
    GpaCounterGeneratorBase();

    /// @brief Virtual destructor.
    virtual ~GpaCounterGeneratorBase() = default;

    /// @copydoc IGpaCounterAccessor::SetAllowedCounters()
    void SetAllowedCounters(bool allow_public_counters, bool allow_hardware_counters, bool allow_software_counters) override;

    /// @copydoc IGpaCounterAccessor::GetNumCounters()
    GpaUInt32 GetNumCounters() const override;

    /// @copydoc IGpaCounterAccessor::GetCounterName()
    const char* GetCounterName(GpaUInt32 index) const override;

    /// @copydoc IGpaCounterAccessor::GetCounterGroup()
    const char* GetCounterGroup(GpaUInt32 index) const override;

    /// @copydoc IGpaCounterAccessor::GetCounterDescription()
    const char* GetCounterDescription(GpaUInt32 index) const override;

    /// @copydoc IGpaCounterAccessor::GetCounterDataType()
    GpaDataType GetCounterDataType(GpaUInt32 index) const override;

    /// @copydoc IGpaCounterAccessor::GetCounterUsageType()
    GpaUsageType GetCounterUsageType(GpaUInt32 index) const override;

    /// @copydoc IGpaCounterAccessor::GetCounterUuid()
    GpaUuid GetCounterUuid(GpaUInt32 index) const override;

    /// @copydoc IGpaCounterAccessor::GetCounterSampleType()
    GpaCounterSampleType GetCounterSampleType(GpaUInt32 index) const override;

    /// @copydoc IGpaCounterAccessor::GetPublicCounter()
    const GpaDerivedCounterInfoClass* GetPublicCounter(GpaUInt32 index) const override;

    /// @copydoc IGpaCounterAccessor::GetHardwareCounterExt()
    const GpaHardwareCounterDescExt* GetHardwareCounterExt(GpaUInt32 index) const override;

    /// @copydoc IGpaCounterAccessor::GetNumPublicCounters()
    GpaUInt32 GetNumPublicCounters() const override;

    /// @copydoc IGpaCounterAccessor::GetInternalCountersRequired()
    std::vector<GpaUInt32> GetInternalCountersRequired(GpaUInt32 index) const override;

    /// @copydoc IGpaCounterAccessor::ComputePublicCounterValue()
    GpaStatus ComputePublicCounterValue(GpaUInt32                            counter_index,
                                        const std::vector<const GpaUInt64*>& results,
                                        std::vector<GpaDataType>&            internal_counter_types,
                                        void*                                result,
                                        const GpaHwInfo*                     hardware_info) const override;

    /// @copydoc IGpaCounterAccessor::GetCounterSourceInfo()
    GpaCounterSourceInfo GetCounterSourceInfo(GpaUInt32 global_index) const override;

    /// @copydoc IGpaCounterAccessor::GetCounterIndex()
    bool GetCounterIndex(const char* counter_name, GpaUInt32* counter_index) const override;

    /// @copydoc IGpaCounterAccessor::GetCounterIndex()
    bool GetCounterIndex(const GpaHwBlock&    gpa_hardware_block,
                         const GpaUInt32&     block_instance,
                         const GpaUInt32&     block_event_id,
                         const GpaShaderMask& gpa_shader_mask,
                         GpaUInt32*           counter_index) const override;

    /// @copydoc IGpaCounterAccessor::GetPublicInterfaceCounterIndex()
    bool GetPublicInterfaceCounterIndex(const GpaUInt32& hardware_counter_index, GpaUInt32* public_interface_counter_index) const override;

    /// @copydoc IGpaCounterAccessor::GetHardwareCounters()
    const GpaHardwareCounters* GetHardwareCounters() const override;

    /// @copydoc IGpaCounterAccessor::GetSoftwareCounters()
    const GpaSoftwareCounters* GetSoftwareCounters() const override;

    /// @copydoc IGpaCounterAccessor::GetCounterInfo()
    GpaCounterInfo* GetCounterInfo(const GpaUInt32& derived_counter_index) const override;

    /// @brief Generate the counters for the specified generation.
    ///
    /// @param [in] desired_generation The generation whose counters are needed.
    /// @param [in] asic_type The ASIC type whose counters are needed.
    /// @param [in] generate_asic_specific_counters Flag that indicates whether the counters should be ASIC specific, if available.
    ///
    /// @return kGpaStatusOk on success.
    GpaStatus GenerateCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GpaUInt8 generate_asic_specific_counters);

    /// @copydoc IGpaCounterAccessor::ComputeSwCounterValue().
    void ComputeSwCounterValue(GpaUInt32 software_counter_index, GpaUInt64 value, void* result, const GpaHwInfo* hardware_info) const override;

    /// @brief Get the number of supported AMD counters.
    ///
    /// @return number of supported AMD counters.
    GpaUInt32 GetNumAmdCounters() const;

    /// @brief Generate the public counters for the specified hardware generation.
    ///
    /// @param [in] desired_generation The generation whose counters are needed.
    /// @param [in] asic_type The ASIC whose counters are needed.
    /// @param [in] generate_asic_specific_counters Flag that indicates whether the counters should be ASIC specific, if available.
    /// @param [out] public_counters The generated counters.
    ///
    /// @return kGpaStatusOk on success.
    virtual GpaStatus GeneratePublicCounters(GDT_HW_GENERATION   desired_generation,
                                             GDT_HW_ASIC_TYPE    asic_type,
                                             GpaUInt8            generate_asic_specific_counters,
                                             GpaDerivedCounters* public_counters) = 0;

    /// @brief Generate the hardware counters for the specified hardware generation.
    ///
    /// @param [in] desired_generation The generation whose counters are needed.
    /// @param [in] asic_type The ASIC whose counters are needed.
    /// @param [in] generate_asic_specific_counters Flag that indicates whether the counters should be ASIC specific, if available.
    /// @param [out] hardware_counters The generated counters.
    ///
    /// @return kGpaStatusOk on success.
    virtual GpaStatus GenerateHardwareCounters(GDT_HW_GENERATION    desired_generation,
                                               GDT_HW_ASIC_TYPE     asic_type,
                                               GpaUInt8             generate_asic_specific_counters,
                                               GpaHardwareCounters* hardware_counters) = 0;

    /// @brief Generate the software counters for the specified hardware generation.
    ///
    /// @param [in] desired_generation The generation whose counters are needed.
    /// @param [in] asic_type The ASIC whose counters are needed.
    /// @param [in] generate_asic_specific_counters Flag that indicates whether the counters should be ASIC specific, if available.
    /// @param [out] software_counters The generated counters.
    ///
    /// @return kGpaStatusOk on success.
    virtual GpaStatus GenerateSoftwareCounters(GDT_HW_GENERATION    desired_generation,
                                               GDT_HW_ASIC_TYPE     asic_type,
                                               GpaUInt8             generate_asic_specific_counters,
                                               GpaSoftwareCounters* software_counters) = 0;

    /// @brief Generate the hardware exposed counters for the specified hardware generation
    ///
    /// @param [in] desired_generation The generation whose counters are needed
    /// @param [in] asic_type The ASIC whose counters are needed
    /// @param [in] generate_asic_specific_counters Flag that indicates whether the counters should be ASIC specific, if available.
    /// @param [out] hardware_counters The generated counters
    ///
    /// @return kGpaStatusOk on success
    virtual GpaStatus GenerateHardwareExposedCounters(GDT_HW_GENERATION    desired_generation,
                                                      GDT_HW_ASIC_TYPE     asic_type,
                                                      GpaUInt8             generate_asic_specific_counters,
                                                      GpaHardwareCounters* hardware_counters);

    /// @brief Maps the hardware counter and hardware exposed counter.
    ///
    /// @param [in] hardware_counters The generated counters.
    ///
    /// @return true upon success otherwise false.
    virtual bool MapHardwareExposedCounter(GpaHardwareCounters* hardware_counters);

    GpaDerivedCounters  public_counters_;    ///< The generated public counters.
    GpaHardwareCounters hardware_counters_;  ///< The generated hardware counters.
    GpaSoftwareCounters software_counters_;  ///< The generated software counters.

private:
#ifdef AMDT_INTERNAL
    /// @brief Allow hardware counters to be given an alternate name when they are enabled using the "block:instance:event:alt_name" syntax.
    ///
    /// @param [in] index The index of a counter, must be between 0 and the value returned from GetNumPublicCounters().
    /// @param [in] counter_name The alternate counter name to be used for the hardware counter.
    ///
    /// @return true upon success otherwise false.
    bool SetCounterName(GpaUInt32 index, const char* counter_name);

    /// @brief Entry point to load internal counters.
    ///
    /// @param [in] desired_generation The generation whose counters are needed.
    /// @param [in] asic_type The ASIC whose counters are needed.
    /// @param [in] generate_asic_specific_counters Flag that indicates whether the counters should be ASIC specific, if available.
    /// @param [out] public_counters The generated counters.
    ///
    /// @return kGpaStatusOk on success.
    virtual GpaStatus GenerateInternalDerivedCounters(GDT_HW_GENERATION   desired_generation,
                                                      GDT_HW_ASIC_TYPE    asic_type,
                                                      GpaUInt8            generate_asic_specific_counters,
                                                      GpaDerivedCounters* public_counters);
#endif

    bool do_allow_public_counters_;            ///< Flag indicating whether or not public counters are allowed.
    bool do_allow_hardware_counters_;          ///< Flag indicating whether or not hardware counters are allowed.
    bool do_allow_software_counters_;          ///< Flag indicating whether or not software counters are allowed.
    bool do_allow_hardware_exposed_counters_;  ///< Flag indicating whether or not whitelist counters are allowed.

    /// Typedef for an unordered_map from counter name to index.
    typedef std::unordered_map<std::string, GpaUInt32> CounterNameIndexMap;

    /// Const indicating that a counter was not found.
    static const GpaUInt32 kCounterNotFound = static_cast<GpaUInt32>(-1);

    /// Cache of counter indexes, so we don't have to look up a counter more than once (it can be expensive).
    mutable CounterNameIndexMap counter_index_cache_;
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_GPA_COUNTER_GENERATOR_BASE_H_
