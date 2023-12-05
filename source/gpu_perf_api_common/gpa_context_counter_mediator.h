//==============================================================================
// Copyright (c) 2018-2023 Advanced Micro Devices, Inc. All rights reserved.
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
    /// @param [in] gpa_context GPA context.
    /// @param [in] flags Flags used to initialize the context. Should be a combination of GPA_OpenContext_Bits.
    GpaStatus GenerateCounters(const IGpaContext* gpa_context, GpaOpenContextFlags flags);

    /// @brief Checks whether the counter scheduling is supported or not for the given context.
    ///
    /// @param [in] gpa_context GPA context.
    ///
    /// @return True upon successful execution.
    bool IsCounterSchedulingSupported(const IGpaContext* gpa_context) const;

    /// @brief Returns the counter accessor for the given context.
    ///
    /// @param [in] gpa_context GPA context.
    ///
    /// @return Pointer to the counter accessor.
    IGpaCounterAccessor* GetCounterAccessor(const IGpaContext* gpa_context) const;

    /// @brief Schedules the given set of counters for the given context.
    ///
    /// @param [in] gpa_context GPA context.
    /// @param [in] gpa_session GPA session.
    /// @param [in] counter_set Set of counter.
    ///
    /// @return kGpaStatusOk upon successful operation.
    GpaStatus ScheduleCounters(const IGpaContext* gpa_context, const IGpaSession* gpa_session, const std::vector<GpaUInt32>& counter_set);

    /// @brief Unchedules the given set of counters for the given context.
    ///
    /// @param [in] gpa_context GPA context.
    /// @param [in] gpa_session GPA session.
    /// @param [in] counter_set Set of counter.
    ///
    /// @return kGpaStatusOk upon successful operation.
    GpaStatus UnscheduleCounters(const IGpaContext* gpa_context, const IGpaSession* gpa_session, const std::vector<GpaUInt32>& counter_set);

    /// @brief Schedules and returns the number of pass required for the given set of counters.
    ///
    /// @param [in] gpa_context GPA context.
    /// @param [out] pass_required Required number of pass.
    /// @param [in] counter_set Set of counters.
    ///
    /// @return kGpaStatusOk upon successful operation.
    GpaStatus GetRequiredPassCount(const IGpaContext* gpa_context, const std::vector<GpaUInt32>& counter_set, unsigned int& pass_required);

    /// @brief Returns the counter result location for the given public counter index.
    ///
    /// @param [in] gpa_context GPA Context.
    /// @param [in] public_counter_index Index of the public counter.
    ///
    /// @return address to result location map otherwise nullptr.
    CounterResultLocationMap* GetCounterResultLocations(const IGpaContext* gpa_context, const unsigned int& public_counter_index);

    /// @brief Releases the context from the mediator.
    ///
    /// @param [in] gpa_context GPA Context.
    void RemoveContext(IGpaContext* gpa_context);

    /// @brief Gets the counter in the given pass for the scheduled counters in the context.
    ///
    /// @param [in] gpa_context GPA Context.
    /// @param [in] pass_index Index of the pass.
    ///
    /// @return The list of the counters.
    CounterList* GetCounterForPass(IGpaContext* gpa_context, PassIndex pass_index);

private:
    /// @brief Private Constructor.
    GpaContextCounterMediator() = default;

    /// @brief Checks whether the given context info exists or not.
    ///
    /// @param [in] gpa_context GPA context.
    ///
    /// @return True if context info exist otherwise false.
    bool DoesContextExist(const IGpaContext* gpa_context) const;

    static GpaContextCounterMediator* kCounterManager;  ///< Static instance of the counter manager.

    /// @brief Container to associate a counter accessor with a counter scheduler.
    struct GpaContextStatus
    {
        IGpaCounterScheduler* counter_scheduler;  ///< Counter scheduler.
        IGpaCounterAccessor*  counter_accessor;   ///< Counter accessor.
    };

    using GpaCtxStatusInfoPair = std::pair<const IGpaContext*, GpaContextStatus>;  ///< Type alias for GPA context and its status info pair.
    using GpaCtxStatusInfoMap = std::map<const IGpaContext*, GpaContextStatus>;   ///< Type alias for GPA context and its status info map.

    GpaCtxStatusInfoMap context_info_map_;        ///< Map of context and its info.
    mutable std::mutex  context_info_map_mutex_;  ///< Mutex for context info map.
};

#endif  // GPU_PERF_API_COMMON_GPA_CONTEXT_COUNTER_MEDIATOR_H_
