//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Interface representing the GPA context.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_CONTEXT_INTERFACE_H_
#define GPU_PERF_API_COMMON_GPA_CONTEXT_INTERFACE_H_

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_counter_generator/gpa_counter_accessor_interface.h"
#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_interface.h"

#include "gpu_perf_api_common/gpa_hw_info.h"
#include "gpu_perf_api_common/gpa_interface_trait_interface.h"

class IGpaSession;

/// @brief Device clock mode enum used to decode usage of GPA_OpenContext mode flag.
enum class DeviceClockMode : uint32_t
{
    kDefault,        ///< Device clocks and other power settings are restored to default.
    kMinimumEngine,  ///< Engine clock is set to the lowest available level. Memory clock is set to thermal and power sustainable level.
    kMinimumMemory,  ///< Memory clock is set to the lowest available level. Engine clock is set to thermal and power sustainable level.
    kPeak,           ///< Clocks set to maximum when possible. Fan set to maximum. Note: Under power and thermal constraints device will clock down.
    kProfiling,  ///< Scale down from peak ratio. Clocks are set to a constant amount which is known to be power and thermal sustainable. The engine/memory clock ratio will be kept the same as much as possible.
};

/// @brief Interface for GPA Context Object.
class IGpaContext : public IGpaInterfaceTrait
{
public:
    /// @brief Virtual Destructor.
    virtual ~IGpaContext() = default;

    /// @brief Creates a session Container.
    ///
    /// @param sample_type The sample type that will be created for this session.
    ///
    /// @return GPA_Session Id object.
    virtual GpaSessionId CreateSession(GpaSessionSampleType sample_type) = 0;

    /// @brief Deletes a session and its associated counter data.
    ///
    /// @param [in] session_id Pointer to previously created session object.
    ///
    /// @return True if operation is successful otherwise false.
    virtual bool DeleteSession(GpaSessionId session_id) = 0;

    /// @brief Returns the maximum number of sessions possible in the context.
    ///
    /// @return Maximum number of possible sessions.
    virtual GpaUInt32 GetMaxGpaSessions() const = 0;

    /// @brief Returns the count of created sessions in the context.
    ///
    /// @return Number of sessions created in the context.
    virtual GpaUInt32 GetSessionCount() const = 0;

    /// @brief Checks whether the session current exist or not.
    ///
    /// @param [in] session_id Pointer to GPA Session id object.
    ///
    /// @return True if session exist otherwise false.
    virtual bool DoesSessionExist(GpaSessionId session_id) const = 0;

    /// @brief Gets a mask of the sample types supported by this context.
    ///
    /// @param [out] sample_types The value that will be set to the the mask of the sample types supported by this context. This will be a combination of GPA_Context_Sample_Type_Bits.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus GetSupportedSampleTypes(GpaContextSampleTypeFlags* sample_types) const = 0;

    /// @brief Gets the number of available counters in the context.
    ///
    /// @param [out] counter_count Number of counters.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus GetNumCounters(GpaUInt32* counter_count) const = 0;

    /// @brief Gets the name of a counter.
    ///
    /// @param [in] index Index of the counter.
    /// @param [out] counter_name Name of the counter.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus GetCounterName(GpaUInt32 index, const char** counter_name) const = 0;

    /// @brief Gets the name of the group that a specific counter belongs to.
    ///
    /// @param [in] index Index of the counter.
    /// @param [out] counter_group Name of the group.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus GetCounterGroup(GpaUInt32 index, const char** counter_group) const = 0;

    /// @brief Gets the description of a counter.
    ///
    /// @param [in] index Index of the counter.
    /// @param [out] counter_description Description of the counter.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus GetCounterDescription(GpaUInt32 index, const char** counter_description) const = 0;

    /// @brief Gets the data type of a counter.
    ///
    /// @param [in] index Index of the counter.
    /// @param [out] counter_data_type Data type of the counter.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus GetCounterDataType(GpaUInt32 index, GpaDataType* counter_data_type) const = 0;

    /// @brief Gets the usage type of a counter.
    ///
    /// @param [in] index Index of the counter.
    /// @param [out] counter_usage_type Counter usage type.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus GetCounterUsageType(GpaUInt32 index, GpaUsageType* counter_usage_type) const = 0;

    /// @brief Gets the UUID of the specified counter.
    ///
    /// @param [in] index Index of the counter.
    /// @param [out] counter_uuid The value which will hold the counter UUID upon successful execution.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus GetCounterUuid(GpaUInt32 index, GpaUuid* counter_uuid) const = 0;

    /// @brief Gets the supported sample types of the specified counter.
    ///
    /// @param [in] index Index of the counter.
    /// @param [out] counter_sample_type The value which will hold the counter's supported sample type upon successful execution.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus GetCounterSampleType(GpaUInt32 index, GpaCounterSampleType* counter_sample_type) const = 0;

    /// @brief Gets the index of a counter by its name.
    ///
    /// @param [in] counter_name Name of the counter.
    /// @param [out] counter_index Index of the counter.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus GetCounterIndex(const char* counter_name, GpaUInt32* counter_index) const = 0;

    /// @brief Uses the exposed counter index to look up which source the counter comes from and the relative (local)
    /// counter index into that source of counters.
    ///
    /// @param [in] exposed_counter_index The counter index of which to get the source and local index.
    /// @param [out] counter_source Pointer to a variable that will hold the counter's source. Cannot be NULL.
    /// @param [out] source_local_index Pointer to a variable that will hold the counters index relative to that source. Cannot be NULL.
    ///
    /// @return True if the exposedCounterIndex is in the valid range; false otherwise.
    virtual bool GetCounterSourceLocalIndex(GpaUInt32 exposed_counter_index, GpaCounterSource* counter_source, GpaUInt32* source_local_index) const = 0;

    /// @brief Check to see if public counters should be exposed.
    ///
    /// @return True if public counters should be exposed; false otherwise.
    virtual bool ArePublicCountersExposed() const = 0;

    /// @brief Check to see if software counters should be exposed.
    ///
    /// @return True if software counters should be exposed; false otherwise.
    virtual bool AreHardwareCountersExposed() const = 0;

    /// @brief Check to see if hardware counters should be exposed.
    ///
    /// @return True if hardware counters should be exposed; false otherwise.
    virtual bool AreSoftwareCountersExposed() const = 0;

    /// @brief Gets the source (origin) of the specified internal counter (ie, either hardware or software).
    ///
    /// @param internal_counter_index The index of the counter to find, must be in range of 0 to (NumHwCounters + NumSwCounters).
    ///
    /// @retval Unknown If the counterIndex is invalid.
    /// @retval Public If the counter is defined by GPA.
    /// @retval Hardware If the counter comes from our internal extension.
    /// @retval Software If the counter comes from an API-level entry point (ie, queries).
    virtual GpaCounterSource GetCounterSource(GpaUInt32 internal_counter_index) const = 0;

    /// @brief Sets a flag to invalidate and flush the L2 cache around the next counter sample.
    ///
    /// @param [in] should_invalidate_and_flush_l2_cache Flag indicating to enable invalidation and flushing of the L2 cache.
    virtual void SetInvalidateAndFlushL2Cache(bool should_invalidate_and_flush_l2_cache) = 0;

    /// @brief Returns the status of the flag indicating the invalidation and flushing of L2 cache.
    ///
    /// @return Flag indicating the invalidation and flushing of L2 cache.
    virtual bool IsInvalidateAndFlushL2CacheEnabled() const = 0;

    /// @brief Returns the hardware info.
    ///
    /// @return Pointer to the context hardware info.
    virtual const GpaHwInfo* GetHwInfo() const = 0;

    /// @brief Checks whether the context is open or not.
    ///
    /// @return True if context is open otherwise false.
    virtual bool IsOpen() const = 0;

    /// @brief Gets device clock mode behavior.
    ///
    /// @return DeviceClockMode enum indicating clock mode behavior.
    virtual DeviceClockMode GetDeviceClockMode() const = 0;

    /// @brief Opens the counter for the context.
    ///
    /// @return True if successfully opens the counter otherwise false.
    virtual bool OpenCounters() = 0;

    /// @brief Begins the session on current context.
    ///
    /// @param [in] gpa_session Pointer to previously created session object.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus BeginSession(IGpaSession* gpa_session) = 0;

    /// @brief Ends the session on current context.
    ///
    /// @param [in] gpa_session Pointer to previously created session object.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus EndSession(IGpaSession* gpa_session) = 0;

    /// @brief Returns the active session for the context.
    ///
    /// @return Active session if any session is active otherwise nullptr.
    virtual const IGpaSession* GetActiveSession() const = 0;

    /// @brief Enable/disable the stable power state, using the stable clock mode specified when opening the context.
    ///
    /// @param [in] use_profiling_clocks True to use GPU clocks for profiling, false to use default clock mode.
    ///
    /// @return kGpaStatusOk on success.
    virtual GpaStatus SetStableClocks(bool use_profiling_clocks) = 0;
};

#endif  // GPU_PERF_API_COMMON_GPA_CONTEXT_INTERFACE_H_
