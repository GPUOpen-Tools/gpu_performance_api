//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Base Class for counter scheduling
//==============================================================================

#ifndef _GPA_COUNTER_SCHEDULER_BASE_H_
#define _GPA_COUNTER_SCHEDULER_BASE_H_

#include "GPAICounterScheduler.h"
#include "GPASplitCounterFactory.h"

/// Base Class for counter scheduling
class GPA_CounterSchedulerBase : public GPA_ICounterScheduler
{
public:
    /// Constructor
    GPA_CounterSchedulerBase();

    /// Destructor
    ~GPA_CounterSchedulerBase();

    // Implementation of GPA_ICounterScheduler

    /// Reset the counter scheduler
    void Reset();

    /// Set the counter accessor that should be used when scheduling counters
    /// \param pCounterAccessor The counter accessor
    /// \param vendorId The vendor id
    /// \param deviceId The device id
    /// \param revisionId The revision id
    /// \return GPA_STATUS_ERROR_NULL_POINTER If pCounterAccessor is nullptr
    /// \return GPA_STATUS_OK
    GPA_Status SetCounterAccessor(GPA_ICounterAccessor* pCounterAccessor, gpa_uint32 vendorId, gpa_uint32 deviceId, gpa_uint32 revisionId);

    /// Get the number of enabled counters
    /// \return the number of enabled counters
    gpa_uint32 GetNumEnabledCounters();

    /// Enables a counter
    /// \param index The index of a counter to enable
    /// \return GPA_STATUS_OK on success
    GPA_Status EnableCounter(gpa_uint32 index);

    /// Disables a counter
    /// \param index The index of a counter to disable
    /// \return GPA_STATUS_OK on success
    GPA_Status DisableCounter(gpa_uint32 index);

    /// Disables all counters
    void DisableAllCounters();

    /// Gets the counter index of the specified enabled counter
    /// \param enabledIndex the enabled counter whose counter index is needed
    /// \param[out] pCounterAtIndex the counter index of the specified enabled counter
    /// \return GPA_STATUS_OK on success
    GPA_Status GetEnabledIndex(gpa_uint32 enabledIndex, gpa_uint32* pCounterAtIndex);

    /// Checks if the specified counter is enabled
    /// \param counterIndex the index of the counter to check
    /// \return GPA_STATUS_OK if the counter is enabled
    GPA_Status IsCounterEnabled(gpa_uint32 counterIndex);

    /// Obtains the number of passes required to collect the enabled counters
    /// \param[inout] pNumRequiredPassesOut Will contain the number of passes needed to collect the set of enabled counters
    /// \return GPA_STATUS_OK on success
    GPA_Status GetNumRequiredPasses(gpa_uint32* pNumRequiredPassesOut);

    /// Get a flag indicating if the counter selection has changed
    /// \return true if the counter selection has changed, false otherwise
    bool GetCounterSelectionChanged();

    /// Begin profiling -- sets pass index to zero
    /// \return GPA_STATUS_OK on success
    GPA_Status BeginProfile();

    /// Begin a pass -- increments the pass index
    void BeginPass();

    /// Gets the counters for the specified pass
    /// \param passIndex the pass whose counters are needed
    /// \return a list of counters for the specified pass
    std::vector<unsigned int>* GetCountersForPass(gpa_uint32 passIndex);

    /// End a pass (empty implementation)
    void EndPass();

    /// End profiling
    /// \return GPA_STATUS_OK on success
    GPA_Status EndProfile();

    /// Gets the counter result locations for the specified public counter
    /// \param publicCounterIndex the counter index whose result locations are needed
    /// \return a map of counter result locations
    CounterResultLocationMap* GetCounterResultLocations(unsigned int publicCounterIndex);

    /// Set draw call counts (internal support)
    /// \param iCounts the count of draw calls
    void SetDrawCallCounts(const int iCounts);

    // end Implementation of GPA_ICounterScheduler

protected:

    /// Gets the preferred counter splitting algorithm
    /// \return the preferred counter splitting algorithm
    virtual GPACounterSplitterAlgorithm GetPreferredSplittingAlgorithm() = 0;

    /// Helper function to disable a counter
    /// \param index the index of the counter to disable
    /// \return GPA_STATUS_OK on success
    virtual GPA_Status DoDisableCounter(gpa_uint32 index);

    /// Helper function to get the number of software counters
    /// \return the number of software counters
    virtual gpa_uint32 DoGetNumSoftwareCounters();

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
    virtual void DoSetDrawCallCounts(const int iCount);

    /// A map between a public counter index and the set of hardware counters that compose the public counter.
    /// For each hardware counter, there is a map from the hardware counter to the counter result location (pass and offset) for that specific counter.
    /// Multiple public counters may be enabled which require the same hardware counter, but the hardware counter may be profiled in multiple passes so
    /// that the public counters will be consistent. This complex set of maps allows us to find the correct pass and offset for the instance of a
    /// hardware counter that is required for a specific public counter.
    std::map< unsigned int, CounterResultLocationMap> m_counterResultLocationMap;

    /// The counter accessor used by the scheduler
    GPA_ICounterAccessor* m_pCounterAccessor;

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

#endif //_GPA_COUNTER_GENERATOR_BASE_H_
