//==============================================================================
// Copyright (c) 2012-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief An interface for scheduling counters in terms of enabling, disabling, and
///        obtaining the number of necessary passes.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_COUNTER_SCHEDULER_INTERFACE_H_
#define GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_COUNTER_SCHEDULER_INTERFACE_H_

#include <vector>
#include <map>

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_counter_generator/gpa_counter_accessor_interface.h"

using HardwareCounterIndex              = unsigned int;                                               ///< Type alias for internal hardware counter.
using DerivedCounterIndex               = unsigned int;                                               ///< Type alias for derived counter.
using HardwareCounterResultLocationPair = std::pair<HardwareCounterIndex, GpaCounterResultLocation>;  ///< Type alias to help find counter results.
using CounterResultLocationMap          = std::map<HardwareCounterIndex, GpaCounterResultLocation>;   ///< Type alias for map of Counter Result Locations.

/// @brief An interface for enabling and disabling counters and getting the resulting number of necessary passes.
class IGpaCounterScheduler
{
public:
    /// @brief Virtual destructor.
    virtual ~IGpaCounterScheduler() = default;

    /// @brief Reset the counter scheduler.
    virtual void Reset() = 0;

    /// @brief Set the counter accessor that should be used when scheduling counters.
    ///
    /// @param [in] counter_accessor The counter accessor.
    /// @param [in] vendor_id The vendor id of the GPU hardware.
    /// @param [in] device_id The device id of the GPU hardware.
    /// @param [in] revision_id The revision id of the GPU hardware.
    ///
    /// @return kGpaStatusErrorNullPointer If counter_accessor is nullptr otherwise kGpaStatusOk.
    virtual GpaStatus SetCounterAccessor(IGpaCounterAccessor* counter_accessor, GpaUInt32 vendor_id, GpaUInt32 device_id, GpaUInt32 revision_id) = 0;

    /// @brief Enables a counter.
    ///
    /// @param [in] index The index of a counter to enable.
    ///
    /// @return kGpaStatusOk on success.
    virtual GpaStatus EnableCounter(GpaUInt32 index) = 0;

    /// @brief Disables a counter.
    ///
    /// @param [in] index The index of a counter to disable.
    ///
    /// @return kGpaStatusOk on success.
    virtual GpaStatus DisableCounter(GpaUInt32 index) = 0;

    /// @brief Disables all counters.
    virtual void DisableAllCounters() = 0;

    /// @brief Get the number of enabled counters.
    ///
    /// @return The number of enabled counters.
    virtual GpaUInt32 GetNumEnabledCounters() const = 0;

    /// @brief Gets the counter index of the specified enabled counter.
    ///
    /// @param [in] enabled_index The enabled counter whose counter index is needed.
    /// @param [out] counter_at_index The counter index of the specified enabled counter.
    ///
    /// @return kGpaStatusOk on success.
    virtual GpaStatus GetEnabledIndex(GpaUInt32 enabled_index, GpaUInt32* counter_at_index) const = 0;

    /// @brief Checks if the specified counter is enabled.
    ///
    /// @param [in] counter_index The index of the counter to check.
    ///
    /// @return kGpaStatusOk if the counter is enabled.
    virtual GpaStatus IsCounterEnabled(GpaUInt32 counter_index) const = 0;

    /// @brief Obtains the number of passes required to collect the enabled counters.
    ///
    /// @param [in,out] num_required_passes_out Will contain the number of passes needed to collect the set of enabled counters.
    ///
    /// @return kGpaStatusOk on success.
    virtual GpaStatus GetNumRequiredPasses(GpaUInt32* num_required_passes_out) = 0;

    /// @brief Get a flag indicating if the counter selection has changed.
    ///
    /// @return true if the counter selection has changed, false otherwise.
    virtual bool GetCounterSelectionChanged() const = 0;

    /// @brief Begin profiling -- sets pass index to zero.
    ///
    /// @return kGpaStatusOk on success.
    virtual GpaStatus BeginProfile() = 0;

    /// @brief Begin a pass -- increments the pass index.
    virtual void BeginPass() = 0;

    /// @brief Gets the counters for the specified pass.
    ///
    /// @param [in] pass_index The pass whose counters are needed.
    ///
    /// @return A list of counters for the specified pass.
    virtual std::vector<unsigned int>* GetCountersForPass(GpaUInt32 pass_index) = 0;

    /// @brief End a pass.
    virtual void EndPass() = 0;

    /// @brief End profiling.
    ///
    /// @return kGpaStatusOk on success.
    virtual GpaStatus EndProfile() = 0;

    /// @brief Gets the counter result locations for the specified public counter.
    ///
    /// @param [in] public_counter_index The counter index whose result locations are needed.
    ///
    /// @return A map of counter result locations.
    virtual CounterResultLocationMap* GetCounterResultLocations(unsigned int public_counter_index) = 0;

    /// @brief Set draw call counts (internal support).
    ///
    /// @param [in] internal_draw_counts The count of draw calls.
    virtual void SetDrawCallCounts(int internal_draw_counts) = 0;

    /// Gets the scheduler sample type.
    ///
    /// @return The sample type.
    virtual GpaSessionSampleType GetSampleType() const = 0;
};

#endif
