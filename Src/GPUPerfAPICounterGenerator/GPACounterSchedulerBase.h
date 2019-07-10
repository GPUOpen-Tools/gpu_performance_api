//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Base Class for counter scheduling
//==============================================================================

#ifndef _GPA_COUNTER_SCHEDULER_BASE_H_
#define _GPA_COUNTER_SCHEDULER_BASE_H_

#include "IGPACounterScheduler.h"
#include "GPASplitCounterFactory.h"

/// Base Class for counter scheduling
class GPA_CounterSchedulerBase : public IGPACounterScheduler
{
public:
    /// Constructor
    GPA_CounterSchedulerBase();

    /// Destructor
    ~GPA_CounterSchedulerBase() = default;

    /// \copydoc IGPACounterScheduler::Reset()
    void Reset() override;

    /// \copydoc IGPACounterScheduler::SetCounterAccessor()
    GPA_Status SetCounterAccessor(IGPACounterAccessor* pCounterAccessor, gpa_uint32 vendorId, gpa_uint32 deviceId, gpa_uint32 revisionId) override;

    /// \copydoc IGPACounterScheduler::GetNumEnabledCounters()
    gpa_uint32 GetNumEnabledCounters() const override;

    /// \copydoc IGPACounterScheduler::EnableCounter()
    GPA_Status EnableCounter(gpa_uint32 index) override;

    /// \copydoc IGPACounterScheduler::DisableCounter()
    GPA_Status DisableCounter(gpa_uint32 index) override;

    /// \copydoc IGPACounterScheduler::DisableAllCounters()
    void DisableAllCounters() override;

    /// \copydoc IGPACounterScheduler::GetEnabledIndex()
    GPA_Status GetEnabledIndex(gpa_uint32 enabledIndex, gpa_uint32* pCounterAtIndex) const override;

    /// \copydoc IGPACounterScheduler::IsCounterEnabled()
    GPA_Status IsCounterEnabled(gpa_uint32 counterIndex) const override;

    /// \copydoc IGPACounterScheduler::GetNumRequiredPasses()
    GPA_Status GetNumRequiredPasses(gpa_uint32* pNumRequiredPassesOut) override;

    /// \copydoc IGPACounterScheduler::GetCounterSelectionChanged()
    bool GetCounterSelectionChanged() const override;

    /// \copydoc IGPACounterScheduler::BeginProfile()
    GPA_Status BeginProfile() override;

    /// \copydoc IGPACounterScheduler::BeginPass()
    void BeginPass() override;

    /// \copydoc IGPACounterScheduler::GetCountersForPass()
    std::vector<unsigned int>* GetCountersForPass(gpa_uint32 passIndex) override;

    /// \copydoc IGPACounterScheduler::EndPass()
    void EndPass() override;

    /// \copydoc IGPACounterScheduler::EndProfile()
    GPA_Status EndProfile() override;

    /// \copydoc IGPACounterScheduler::GetCounterResultLocations()
    CounterResultLocationMap* GetCounterResultLocations(unsigned int publicCounterIndex) override;

    /// \copydoc IGPACounterScheduler::SetDrawCallCounts()
    void SetDrawCallCounts(int iCounts) override;

protected:
    /// Gets the preferred counter splitting algorithm
    /// \return the preferred counter splitting algorithm
    virtual GPACounterSplitterAlgorithm GetPreferredSplittingAlgorithm() const = 0;

    /// Helper function to disable a counter
    /// \param index the index of the counter to disable
    /// \return GPA_STATUS_OK on success
    virtual GPA_Status DoDisableCounter(gpa_uint32 index);

    /// Helper function to get the number of software counters
    /// \return the number of software counters
    virtual gpa_uint32 DoGetNumSoftwareCounters() const;

    /// Helper function called when beginning a profile
    /// \return GPA_STATUS_OK on success
    virtual GPA_Status DoBeginProfile();

    /// Helper function called when ending a profile
    /// \return GPA_STATUS_OK on success
    virtual GPA_Status DoEndProfile();

    /// Helper function called when beginning a pass
    virtual void DoBeginPass();

    /// Helper function called when ending a pass
    virtual void DoEndPass();

    /// Helper function called when setting draw call counts
    /// \param iCount draw call count per frame
    virtual void DoSetDrawCallCounts(int iCount);

    /// A map between a public counter index and the set of hardware counters that compose the public counter.
    /// For each hardware counter, there is a map from the hardware counter to the counter result location (pass and offset) for that specific counter.
    /// Multiple public counters may be enabled which require the same hardware counter, but the hardware counter may be profiled in multiple passes so
    /// that the public counters will be consistent. This complex set of maps allows us to find the correct pass and offset for the instance of a
    /// hardware counter that is required for a specific public counter.
    std::map<DerivedCounterIndex, CounterResultLocationMap> m_counterResultLocationMap;

    /// The counter accessor used by the scheduler
    IGPACounterAccessor* m_pCounterAccessor;

    /// The vendor id used by the scheduler
    gpa_uint32 m_vendorId;

    /// The device id used by the scheduler
    gpa_uint32 m_deviceId;

    /// The revision id used by the scheduler
    gpa_uint32 m_revisionId;

    /// This must be maintained in parallel with m_enabledPublicCounterBits - both are views of the list of active counters
    /// m_enabledPublicIndices as a list of indices, m_enabledPublicCounterBits as a random access bool array.
    std::vector<gpa_uint32> m_enabledPublicIndices;

    /// This must be maintained in parallel with m_enabledPublicIndices - both are views of the list of active counters
    /// m_enabledPublicCounterBits was added for performance reasons.
    std::vector<bool> m_enabledPublicCounterBits;

    /// Records whether or not the counter selection changed since GPA_BeginSampling was last called.
    bool m_counterSelectionChanged;

    /// List of passes, which are identified by a list of counter indices which are in that pass.
    /// Populated when GetNumRequiredPasses is called.
    GPACounterPassList m_passPartitions;

    /// As the profile is happening, this tracks the current pass.
    unsigned int m_passIndex;
};

#endif  //_GPA_COUNTER_GENERATOR_BASE_H_
