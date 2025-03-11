//==============================================================================
// Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA Context Counter Mediator Header.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_CONTEXT_COUNTER_MEDIATOR_H_
#define GPU_PERF_API_COMMON_GPA_CONTEXT_COUNTER_MEDIATOR_H_

#include <vector>

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_interface.h"

#include "gpu_perf_api_common/gpa_context_interface.h"
#include "gpu_perf_api_common/gpa_session_interface.h"
#include "gpu_perf_api_common/gpa_pass.h"

/// @brief GpaContextCounterMediator class.
class GpaContextCounterMediator
{
public:
    /// @brief Returns the instance of the counter manager.
    ///
    /// @return Instance of the GpaContextCounterMediator.
    static GpaContextCounterMediator* Instance();

    /// @brief Deletes the static instance of the counter manager.
    static void DeleteInstance();

    /// @brief Destructor.
    ~GpaContextCounterMediator();

    /// @brief Generates the counter for the given context.
    ///
    /// @param [in] gpa_session GPA session.
    /// @param [in] flags Flags used to initialize the context. Should be a combination of GpaOpenContextBits.
    GpaStatus GenerateCounters(const IGpaSession* gpa_session, GpaOpenContextFlags flags);

    /// @brief Checks whether the counter scheduling is supported or not for the given context.
    ///
    /// @param [in] gpa_session GPA Session.
    ///
    /// @return True upon successful execution.
    bool IsCounterSchedulingSupported(const IGpaSession* gpa_session) const;

    /// @brief Returns the counter accessor for the given context.
    ///
    /// @param [in] gpa_session GPA Session.
    ///
    /// @return Pointer to the counter accessor.
    IGpaCounterAccessor* GetCounterAccessor(const IGpaSession* gpa_session) const;

    /// @brief Schedules the given set of counters for the given context.
    ///
    /// @param [in] gpa_session GPA session.
    /// @param [in] counter_set Set of counter.
    ///
    /// @return kGpaStatusOk upon successful operation.
    GpaStatus ScheduleCounters(const IGpaSession* gpa_session, const std::vector<GpaUInt32>& counter_set);

    /// @brief Unchedules the given set of counters for the given context.
    ///
    /// @param [in] gpa_session GPA session.
    /// @param [in] counter_set Set of counter.
    ///
    /// @return kGpaStatusOk upon successful operation.
    GpaStatus UnscheduleCounters(const IGpaSession* gpa_session, const std::vector<GpaUInt32>& counter_set);

    /// @brief Schedules and returns the number of pass required for the given set of counters.
    ///
    /// @param [in] gpa_session GPA Session.
    /// @param [out] pass_required Required number of pass.
    /// @param [in] counter_set Set of counters.
    ///
    /// @return kGpaStatusOk upon successful operation.
    GpaStatus GetRequiredPassCount(const IGpaSession* gpa_session, const std::vector<GpaUInt32>& counter_set, unsigned int& pass_required);

    /// @brief Returns the counter result location for the given public counter index.
    ///
    /// @param [in] gpa_session GPA Session.
    /// @param [in] public_counter_index Index of the public counter.
    ///
    /// @return address to result location map otherwise nullptr.
    CounterResultLocationMap* GetCounterResultLocations(const IGpaSession* gpa_session, const unsigned int& public_counter_index);

    /// @brief Releases the context from the mediator.
    ///
    /// @param [in] gpa_session GPA Session.
    void RemoveContext(IGpaSession* gpa_session);

    /// @brief Gets the counter in the given pass for the scheduled counters in the context.
    ///
    /// @param [in] gpa_session GPA Session.
    /// @param [in] pass_index Index of the pass.
    ///
    /// @return The list of the counters.
    CounterList* GetCounterForPass(IGpaSession* gpa_session, PassIndex pass_index);

private:
    /// @brief Private Constructor.
    GpaContextCounterMediator() = default;

    /// @brief Checks whether the given session exists or not.
    ///
    /// @param [in] gpa_session GPA session.
    ///
    /// @return True if session exists otherwise false.
    bool DoesSessionExist(const IGpaSession* gpa_session) const;

    static GpaContextCounterMediator* kCounterManager;  ///< Static instance of the counter manager.

    /// @brief Container to associate a counter accessor with a counter scheduler.
    struct GpaContextStatus
    {
        IGpaCounterScheduler* counter_scheduler;  ///< Counter scheduler.
        IGpaCounterAccessor*  counter_accessor;   ///< Counter accessor.
    };

    using GpaCtxStatusInfoPair = std::pair<const IGpaSession*, GpaContextStatus>;  ///< Type alias for GPA session and its status info pair.
    using GpaCtxStatusInfoMap = std::map<const IGpaSession*, GpaContextStatus>;   ///< Type alias for GPA session and its status info map.

    GpaCtxStatusInfoMap session_info_map_;        ///< Map of sessions to corresponding info.
    mutable std::mutex  context_info_map_mutex_;  ///< Mutex for context info map.
};

#endif  // GPU_PERF_API_COMMON_GPA_CONTEXT_COUNTER_MEDIATOR_H_
