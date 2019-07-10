//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GPA Context Counter Mediator Header
//==============================================================================

#ifndef _GPA_CONTEXT_COUNTER_MEDIATOR_H_
#define _GPA_CONTEXT_COUNTER_MEDIATOR_H_

#include <vector>

#include "IGPAContext.h"
#include "IGPASession.h"
#include "GPAPass.h"
#include "IGPACounterScheduler.h"

/// GPAContextCounterMediator class
class GPAContextCounterMediator
{
public:
    /// Returns the instance of the counter manager
    /// \return instance of the GPAContextCounterMediator
    static GPAContextCounterMediator* Instance();

    /// Deletes the static instance of the counter manager
    static void DeleteInstance();

    /// Destructor
    ~GPAContextCounterMediator();

    /// Generates the counter for the given context
    /// \param[in] pGpaContext GPA context
    /// \param[in] flags Flags used to initialize the context. Should be a combination of GPA_OpenContext_Bits
    /// \param[in] generateAsicSpecificCounters Flag that indicates whether the counters should be ASIC specific, if available.
    GPA_Status GenerateCounters(const IGPAContext* pGpaContext, GPA_OpenContextFlags flags, gpa_uint8 generateAsicSpecificCounters);

    /// Checks whether the counter scheduling is supported or not for the given context
    /// \param[in] pGpaContext GPA context
    /// \return true upon successful execution
    bool IsCounterSchedulingSupported(const IGPAContext* pGpaContext) const;

    /// Returns the counter accessor for the given context
    /// \param[in] pGpaContext GPA context
    /// \return GPA_STATUS_OK upon successful operation
    IGPACounterAccessor* GetCounterAccessor(const IGPAContext* pGpaContext) const;

    /// Schedules the given set of counters for the given context
    /// \param[in] pGpaContext GPA context
    /// \param[in] pGpaSession GPA session
    /// \param[in] counterSet set of counter
    /// \return GPA_STATUS_OK upon successful operation
    GPA_Status ScheduleCounters(const IGPAContext* pGpaContext, const IGPASession* pGpaSession, const std::vector<gpa_uint32>& counterSet);

    /// Unschedules the given set of counters for the given context
    /// \param[in] pGpaContext GPA context
    /// \param[in] pGpaSession GPA session
    /// \param[in] counterSet set of counter
    /// \return GPA_STATUS_OK upon successful operation
    GPA_Status UnscheduleCounters(const IGPAContext* pGpaContext, const IGPASession* pGpaSession, const std::vector<gpa_uint32>& counterSet);

    /// Schedules and returns the number of pass required for the given set of counters
    /// \param[in] pGpaContext GPA context
    /// \param[out] passRequired required number of pass
    /// \param[in] counterSet set of counter
    /// \return GPA_STATUS_OK upon successful operation
    GPA_Status GetRequiredPassCount(const IGPAContext* pGpaContext, const std::vector<gpa_uint32>& counterSet, unsigned int& passRequired);

    /// Returns the counter result location for the given public counter index
    /// \param[in] pGpaContext GPA Context
    /// \param[in] publicCounterIndex index of the public counter
    /// \return address to result location map otherwise nullptr
    CounterResultLocationMap* GetCounterResultLocations(const IGPAContext* pGpaContext, const unsigned int& publicCounterIndex);

    /// Releases the context from the mediator
    /// \param[in] pGpaContext GPA Context
    void RemoveContext(IGPAContext* pGpaContext);

    /// Gets the counter in the given pass for the scheduled counters in the context
    /// \param[in] pGpaContext GPA Context
    /// \param[in] passIndex index of the pass
    /// \return list of the counters
    CounterList* GetCounterForPass(IGPAContext* pGpaContext, PassIndex passIndex);

private:
    /// Constructor
    GPAContextCounterMediator() = default;

    /// Checks whether the given context info exists or not
    /// \param[in] pGpaContext GPA context
    /// \return true if context info exist otherwise false
    bool DoesContextExist(const IGPAContext* pGpaContext) const;

    static GPAContextCounterMediator* ms_pCounterManager;  ///< static instance of the counter manager

    struct GPAContextStatus
    {
        IGPACounterScheduler* m_pCounterScheduler;  ///< counter scheduler
        IGPACounterAccessor*  m_pCounterAccessor;   ///< counter accessor
    };

    using GpaCtxStatusInfoPair = std::pair<const IGPAContext*, GPAContextStatus>;  ///< type alias for GPA context and its status info pair
    using GpaCtxStatusInfoMap  = std::map<const IGPAContext*, GPAContextStatus>;   ///< type alias for GPA context and its status info map

    GpaCtxStatusInfoMap m_contextInfoMap;       ///< map of context and its info
    mutable std::mutex  m_contextInfoMapMutex;  ///< mutex for context info map
};

#endif  // _GPA_CONTEXT_COUNTER_MEDIATOR_H_