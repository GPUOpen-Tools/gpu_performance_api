//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA Common Context class.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_CONTEXT_H_
#define GPU_PERF_API_COMMON_GPA_CONTEXT_H_

#include <list>
#include <mutex>
#include <functional>

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_common/gpa_context_interface.h"
#include "gpu_perf_api_common/gpa_session_interface.h"

/// @brief Type alias for list of IGpaSession objects.
using GpaSessionList = std::list<IGpaSession*>;

/// @brief Abstract GPAContext for common context code.
class GpaContext : public IGpaContext
{
public:
    /// @brief Delete default constructor.
    GpaContext() = delete;

    /// @brief Virtual Destructor.
    virtual ~GpaContext();

    /// @copydoc IGpaContext::GetSupportedSampleTypes()
    GpaStatus GetSupportedSampleTypes(GpaContextSampleTypeFlags* sample_types) const override;

    /// @copydoc IGpaContext::GetNumCounters()
    GpaStatus GetNumCounters(GpaUInt32* counter_count) const override;

    /// @copydoc IGpaContext::GetCounterName()
    GpaStatus GetCounterName(GpaUInt32 index, const char** counter_name) const override;

    /// @copydoc IGpaContext::GetCounterGroup()
    GpaStatus GetCounterGroup(GpaUInt32 index, const char** counter_group) const override;

    /// @copydoc IGpaContext::GetCounterDescription()
    GpaStatus GetCounterDescription(GpaUInt32 index, const char** counter_description) const override;

    /// @copydoc IGpaContext::GetCounterDataType()
    GpaStatus GetCounterDataType(GpaUInt32 index, GpaDataType* counter_data_type) const override;

    /// @copydoc IGpaContext::GetCounterUsageType()
    GpaStatus GetCounterUsageType(GpaUInt32 index, GpaUsageType* counter_usage_type) const override;

    /// @copydoc IGpaContext::GetCounterUuid()
    GpaStatus GetCounterUuid(GpaUInt32 index, GpaUuid* counter_uuid) const override;

    /// @copydoc IGpaContext::GetCounterSampleType()
    GpaStatus GetCounterSampleType(GpaUInt32 index, GpaCounterSampleType* counter_sample_type) const override;

    /// @copydoc IGpaContext::GetCounterIndex()
    GpaStatus GetCounterIndex(const char* pCounterName, GpaUInt32* counter_index) const override;

    /// @copydoc IGpaContext::GetCounterSourceLocalIndex()
    bool GetCounterSourceLocalIndex(GpaUInt32 exposed_counter_index, GpaCounterSource* counter_source, GpaUInt32* source_local_index) const override;

    /// @copydoc IGpaContext::ArePublicCountersExposed()
    bool ArePublicCountersExposed() const override;

    /// @copydoc IGpaContext::AreHardwareCountersExposed()
    bool AreHardwareCountersExposed() const override;

    /// @copydoc IGpaContext::AreSoftwareCountersExposed()
    bool AreSoftwareCountersExposed() const override;

    /// @copydoc IGpaContext::GetCounterSource()
    GpaCounterSource GetCounterSource(GpaUInt32 internal_counter_index) const override;

    /// @copydoc IGpaContext::SetInvalidateAndFlushL2Cache()
    void SetInvalidateAndFlushL2Cache(bool should_invalidate_and_flush_l2_cache) override;

    /// @copydoc IGpaContext::IsInvalidateAndFlushL2CacheEnabled()
    bool IsInvalidateAndFlushL2CacheEnabled() const override;

    /// @copydoc IGpaContext::GetHwInfo()
    const GpaHwInfo* GetHwInfo() const override;

    /// @copydoc IGpaContext::IsOpen()
    bool IsOpen() const override;

    /// @copydoc IGpaContext::GetDeviceClockMode()
    DeviceClockMode GetDeviceClockMode() const override;

    /// @copydoc IGpaContext::OpenCounters()
    bool OpenCounters() override;

    /// @copydoc IGpaInterfaceTrait::ObjectType()
    GpaObjectType ObjectType() const override;

    /// @copydoc IGpaContext::DoesSessionExist()
    bool DoesSessionExist(GpaSessionId gpa_session_id) const override;

    /// @copydoc IGpaContext::GetSessionCount()
    GpaUInt32 GetSessionCount() const override;

    /// @copydoc IGpaContext::BeginSession()
    GpaStatus BeginSession(IGpaSession* gpa_session) override;

    /// @copydoc IGpaContext::EndSession()
    GpaStatus EndSession(IGpaSession* gpa_session) override;

    /// @copydoc IGpaContext::GetActiveSession()
    const IGpaSession* GetActiveSession() const override;

protected:
    /// @brief Protected constructor.
    ///
    /// @param [in] hw_info The hardware info for the context.
    /// @param [in] flags Creation flags for context.
    GpaContext(GpaHwInfo& hw_info, GpaOpenContextFlags flags);

    /// @brief Marks the context to be opened.
    ///
    /// @param [in] open Flag indicating context to be marked open or closed.
    void SetAsOpened(bool open);

    /// @brief Returns whether the device is AMD device or not.
    ///
    /// @return true if context device is AMD device otherwise false.
    bool IsAmdDevice() const;

    /// @brief Adds the GPA session to the session list.
    ///
    /// @param [in] gpa_session GPA session object pointer.
    GPA_THREAD_SAFE_FUNCTION void AddGpaSession(IGpaSession* gpa_session);

    /// @brief Removes the GPA session from the session list.
    ///
    /// @param [in] gpa_session GPA session object pointer.
    GPA_THREAD_SAFE_FUNCTION void RemoveGpaSession(IGpaSession* gpa_session);

    /// @brief Iterate over GPA session list for the passed function.
    ///
    /// @param [in] function Function to be executed for each object in the list. The function may return false to terminate iteration.
    GPA_THREAD_SAFE_FUNCTION void IterateGpaSessionList(std::function<bool(IGpaSession* gpa_session)> function) const;

    /// @brief Clears the list of the GPA session.
    GPA_THREAD_SAFE_FUNCTION void ClearSessionList();

    /// @brief Returns the index of the GPA session if it exists.
    ///
    /// @param [in] gpa_session GPA session.
    /// @param [out] index Index of the the GPA session in the list.
    ///
    /// @return True if the index was found, false otherwise.
    bool GetIndex(IGpaSession* gpa_session, unsigned int* index = nullptr) const;

    GpaContextSampleTypeFlags supported_sample_types_;  ///< The supported sample types.

private:
    GpaOpenContextFlags  context_flags_;                          ///< Context flags.
    GpaHwInfo            hw_info_;                                ///< Hw info.
    bool                 invalidate_and_flush_l2_cache_enabled_;  ///< Flag indicating flush and invalidation of L2 cache is enabled or not.
    bool                 is_open_;                                ///< Flag indicating context is open or not.
    GpaSessionList       gpa_session_list_;                       ///< List of GPA sessions in the context.
    bool                 is_amd_device_;                          ///< Flag indicating whether the device is AMD or not.
    mutable std::mutex   gpa_session_list_mutex_;                 ///< Mutex for GPA session list.
    IGpaSession*         active_session_;                         ///< Gpa session to keep track of active session.
    mutable std::mutex   active_session_mutex_;                   ///< Mutex for the active session.
};

#endif  // GPU_PERF_API_COMMON_GPA_CONTEXT_H_
