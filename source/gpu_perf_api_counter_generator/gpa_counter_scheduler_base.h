//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Base Class for counter scheduling.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_COUNTER_SCHEDULER_BASE_H_
#define GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_COUNTER_SCHEDULER_BASE_H_

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_interface.h"
#include "gpu_perf_api_counter_generator/gpa_split_counter_factory.h"

/// @brief Base Class for counter scheduling.
class GpaCounterSchedulerBase : public IGpaCounterScheduler
{
public:
    /// @brief Constructor.
    GpaCounterSchedulerBase();

    /// @brief Destructor.
    ~GpaCounterSchedulerBase() = default;

    /// @copydoc IGpaCounterScheduler::Reset()
    void Reset() override;

    /// @copydoc IGpaCounterScheduler::SetCounterAccessor()
    GpaStatus SetCounterAccessor(IGpaCounterAccessor* counter_accessor, GpaUInt32 vendor_id, GpaUInt32 device_id, GpaUInt32 revision_id) override;

    /// @copydoc IGpaCounterScheduler::GetNumEnabledCounters()
    GpaUInt32 GetNumEnabledCounters() const override;

    /// @copydoc IGpaCounterScheduler::EnableCounter()
    GpaStatus EnableCounter(GpaUInt32 index) override;

    /// @copydoc IGpaCounterScheduler::DisableCounter()
    GpaStatus DisableCounter(GpaUInt32 index) override;

    /// @copydoc IGpaCounterScheduler::DisableAllCounters()
    void DisableAllCounters() override;

    /// @copydoc IGpaCounterScheduler::GetEnabledIndex()
    GpaStatus GetEnabledIndex(GpaUInt32 enabled_index, GpaUInt32* counter_at_index) const override;

    /// @copydoc IGpaCounterScheduler::IsCounterEnabled()
    GpaStatus IsCounterEnabled(GpaUInt32 counter_index) const override;

    /// @copydoc IGpaCounterScheduler::GetNumRequiredPasses()
    GpaStatus GetNumRequiredPasses(GpaUInt32* num_required_passes_out) override;

    /// @copydoc IGpaCounterScheduler::GetCounterSelectionChanged()
    bool GetCounterSelectionChanged() const override;

    /// @copydoc IGpaCounterScheduler::BeginProfile()
    GpaStatus BeginProfile() override;

    /// @copydoc IGpaCounterScheduler::BeginPass()
    void BeginPass() override;

    /// @copydoc IGpaCounterScheduler::GetCountersForPass()
    std::vector<unsigned int>* GetCountersForPass(GpaUInt32 pass_index) override;

    /// @copydoc IGpaCounterScheduler::EndPass()
    void EndPass() override;

    /// @copydoc IGpaCounterScheduler::EndProfile()
    GpaStatus EndProfile() override;

    /// @copydoc IGpaCounterScheduler::GetCounterResultLocations()
    CounterResultLocationMap* GetCounterResultLocations(unsigned int public_counter_index) override;

    /// @copydoc IGpaCounterScheduler::SetDrawCallCounts()
    void SetDrawCallCounts(int internal_counts) override;

protected:
    /// @brief Gets the preferred counter splitting algorithm.
    ///
    /// @return the preferred counter splitting algorithm.
    virtual GpaCounterSplitterAlgorithm GetPreferredSplittingAlgorithm() const = 0;

    /// @brief Helper function to disable a counter.
    ///
    /// @param [in] index The index of the counter to disable.
    ///
    /// @return kGpaStatusOk on success.
    virtual GpaStatus DoDisableCounter(GpaUInt32 index);

    /// @brief Helper function to get the number of software counters.
    ///
    /// @return The number of software counters.
    virtual GpaUInt32 DoGetNumSoftwareCounters() const;

    /// @brief Helper function called when beginning a profile.
    ///
    /// @return kGpaStatusOk on success.
    virtual GpaStatus DoBeginProfile();

    /// @brief Helper function called when ending a profile.
    ///
    /// @return kGpaStatusOk on success.
    virtual GpaStatus DoEndProfile();

    /// @brief Helper function called when beginning a pass.
    virtual void DoBeginPass();

    /// @brief Helper function called when ending a pass.
    virtual void DoEndPass();

    /// @brief Helper function called when setting draw call counts.
    ///
    /// @param [in] internal_count Draw call count per frame.
    virtual void DoSetDrawCallCounts(int internal_count);

    /// @brief A map between a public counter index and the set of hardware counters that compose the public counter.
    ///
    /// For each hardware counter, there is a map from the hardware counter to the counter result location (pass and offset) for that specific counter.
    /// Multiple public counters may be enabled which require the same hardware counter, but the hardware counter may be profiled in multiple passes so
    /// that the public counters will be consistent. This complex set of maps allows us to find the correct pass and offset for the instance of a
    /// hardware counter that is required for a specific public counter.
    std::map<DerivedCounterIndex, CounterResultLocationMap> counter_result_location_map_;

    /// The counter accessor used by the scheduler.
    IGpaCounterAccessor* counter_accessor_;

    /// The vendor id used by the scheduler.
    GpaUInt32 vendor_id_;

    /// The device id used by the scheduler.
    GpaUInt32 device_id_;

    /// The revision id used by the scheduler.
    GpaUInt32 revision_id_;

    /// This must be maintained in parallel with enabled_public_counter_bits_ - both are views of the list of active counters
    /// enabled_public_indices_ as a list of indices, enabled_public_counter_bits_ as a random access bool array.
    std::vector<GpaUInt32> enabled_public_indices_;

    /// This must be maintained in parallel with enabled_public_indices_ - both are views of the list of active counters
    /// enabled_public_counter_bits_ was added for performance reasons.
    std::vector<bool> enabled_public_counter_bits_;

    /// Records whether or not the counter selection changed since GPA_BeginSampling was last called.
    bool counter_selection_changed_;

    /// List of passes, which are identified by a list of counter indices which are in that pass.
    /// Populated when GetNumRequiredPasses is called.
    GpaCounterPassList pass_partitions_;

    /// As the profile is happening, this tracks the current pass.
    unsigned int pass_index_;
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_COUNTER_SCHEDULER_BASE_H_
