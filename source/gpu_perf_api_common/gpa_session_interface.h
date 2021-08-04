//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Interface representing the GPA Session.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_SESSION_INTERFACE_H_
#define GPU_PERF_API_COMMON_GPA_SESSION_INTERFACE_H_

#include <vector>

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_common/gpa_interface_trait_interface.h"

class IGpaContext;

/// @brief Enum for GPA Session limit.
enum GpaSessionLimit : uint8_t
{
    kGpaSessionNoLimit = 0  ///< GPA session no limit enum value.
};

/// @brief Enum to track the state of a GPASession.
enum GpaSessionState : uint8_t
{
    kGpaSessionStateNotStarted = 0,       ///< Session has been created, but not yet started. This is when counters can be enabled and disabled.
    kGpaSessionStateStarted,              ///< Session has been started, but not yet ended.
    kGpaSessionStateEndedPendingResults,  ///< Session has been ended, and is pending results.
    kGpaSessionStateResultCollected,      ///< Session's results are available.
};

/// @brief Interface for the GPA Session Object.
class IGpaSession : public IGpaInterfaceTrait
{
public:
    /// @brief Virtual Destructor.
    virtual ~IGpaSession() = default;

    /// @brief Gets the context which created this session.
    ///
    /// @return The parent context.
    virtual IGpaContext* GetParentContext() const = 0;

    /// @brief Get the current state of the session.
    ///
    /// @return The state of the session.
    virtual GpaSessionState GetState() const = 0;

    /// @brief Enables a counter by its index.
    ///
    /// @param [in] counter_index Index of the counter.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus EnableCounter(GpaUInt32 counter_index) = 0;

    /// @brief Disables a counter by its index.
    ///
    /// @param [in] counter_index Index of the counter.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus DisableCounter(GpaUInt32 counter_index) = 0;

    /// @brief Disables all the enabled counters.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus DisableAllCounters() = 0;

    /// @brief Returns the number of enabled counter.
    ///
    /// @param [out] counter_count Number of enabled counters.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus GetNumEnabledCounters(GpaUInt32* counter_count) const = 0;

    /// @brief Get the counter index for an enabled counter.
    ///
    /// @param [in] enabled_number The number of the enabled counter to get the counter index for. Must lie between 0 and (GPA_GetNumEnabledCounters result - 1).
    /// @param [out] enabled_counter_index The value that will contain the index of the counter.
    ///
    /// @return The GPA result status of the operation. kGpaStatusOk is returned if the operation is successful.
    virtual GpaStatus GetEnabledIndex(GpaUInt32 enabled_number, GpaUInt32* enabled_counter_index) const = 0;

    /// @brief Checks whether a counter is enabled or not.
    ///
    /// @param [in] counter_index Index of the counter.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus IsCounterEnabled(GpaUInt32 counter_index) const = 0;

    /// @brief Returns the number of required passes for enabled counter.
    ///
    /// @param [out] num_passes Number of required passes.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus GetNumRequiredPasses(GpaUInt32* num_passes) = 0;

    /// @brief Begins a session.
    ///
    /// @return kGpaStatusOk if session started successfully otherwise an error code.
    virtual GpaStatus Begin() = 0;

    /// @brief Ends a session.
    ///
    /// @return kGpaStatusOk if session ended successfully otherwise an error code.
    virtual GpaStatus End() = 0;

    /// @brief Creates a command list for sampling.
    ///
    /// @param [in] pass_index Index of the pass.
    /// @param [in] cmd_list Command list.
    /// @param [in] cmd_type Type of command List.
    ///
    /// @return unique command list id object.
    virtual GpaCommandListId CreateCommandList(GpaUInt32 pass_index, void* cmd_list, GpaCommandListType cmd_type) = 0;

    /// @brief Checks whether a command list exists in the specified pass.
    ///
    /// @param [in] pass_index The pass index in which to look for the command list.
    /// @param [in] gpa_command_list_id Unique command list id object.
    ///
    /// @return true if the command list exists in the session otherwise false.
    virtual bool DoesCommandListExist(GpaUInt32 pass_index, GpaCommandListId gpa_command_list_id) const = 0;

    /// @brief Checks whether a sample exists in the session.
    ///
    /// @param [in] sample_id The sample index to check.
    ///
    /// @return true if the sample exists in the session otherwise false.
    virtual bool DoesSampleExist(GpaUInt32 sample_id) const = 0;

    /// @brief Starts a sample on command list for the passed unique sample id.
    ///
    /// @param [in] sample_id User-supplied Id of the sample.
    /// @param [in] command_list_id The command_list_id on which the sample should be started.
    ///
    /// @return true if operation was successful otherwise false.
    virtual bool BeginSample(GpaUInt32 sample_id, GpaCommandListId command_list_id) = 0;

    /// @brief Ends the current sample on command list.
    ///
    /// @param [in] command_list_id The command list id on which the sample should be ended.
    ///
    /// @return true if operation was successful otherwise false.
    virtual bool EndSample(GpaCommandListId command_list_id) = 0;

    /// @brief Continue a primary command list sample to another primary command list.
    ///
    /// @param [in] src_sample_id Source sample id.
    /// @param [in] primary_command_list_id Primary command list id on which sample is continuing.
    ///
    /// @return The GPA result status of the operation. kGpaStatusOk is returned if the operation is successful.
    virtual GpaStatus ContinueSampleOnCommandList(GpaUInt32 src_sample_id, GpaCommandListId primary_command_list_id) = 0;

    /// @brief Copy secondary command list/buffer sample on primary command list/buffer.
    ///
    /// @param [in] secondary_cmd_list_id Secondary command list on secondary samples were created.
    /// @param [in] primary_cmd_list_id Primary command list/buffer in which new samples are getting copied.
    /// @param [in] num_samples Number of secondary samples.
    /// @param [in] new_sample_ids New sample ids on a primary command list.
    ///
    /// @return The GPA result status of the operation. kGpaStatusOk is returned if the operation is successful.
    virtual GpaStatus CopySecondarySamples(GpaCommandListId secondary_cmd_list_id,
                                            GpaCommandListId primary_cmd_list_id,
                                            GpaUInt32        num_samples,
                                            GpaUInt32*       new_sample_ids) = 0;

    /// @brief Returns the number of samples created in this session.
    ///
    /// @return Number of samples.
    virtual GpaUInt32 GetSampleCount() const = 0;

    /// @brief Get the sample id by index.
    ///
    /// @param [in] sample_index Index of the sample.
    /// @param [out] client_sample_id Client sample id.
    ///
    /// @return True if sample found otherwise false.
    virtual bool GetSampleIdByIndex(GpaUInt32 sample_index, GpaUInt32& client_sample_id) const = 0;

    /// @brief Checks for newly available sample results.
    ///
    /// @return True if the results from all samples are now available and cached locally;
    ///         false if none or only some results are updated.
    virtual bool UpdateResults() = 0;

    /// @brief Updates the specified pass' results cache if new results are available.
    ///
    /// @param [in] pass_index The specific pass to update.
    ///
    /// @return True if the results from all samples on the specified pass
    /// are now available and cached locally; false if none or only some results are updated.
    virtual bool UpdateResults(GpaUInt32 pass_index) = 0;

    /// @brief Checks whether or not the pass is complete for sampling.
    ///
    /// @param [in] pass_index The specific pass to update.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus IsPassComplete(GpaUInt32 pass_index) const = 0;

    /// @brief Checks whether the session is ready for querying counter results.
    ///
    /// Use IGpaSession::UpdateResults() periodically to make sure results are updated,
    /// which will trigger this call to return true.
    ///
    /// @return True if session is ready to be queried for counter data, false otherwise.
    virtual bool IsResultReady() const = 0;

    /// @brief Checks whether or not the session is running.
    ///
    /// @return True if session is started but not yet ended otherwise false.
    virtual bool IsSessionRunning() const = 0;

    /// @brief Returns the size of sample result in bytes.
    ///
    /// @param [in] sample_id The sample whose result size is needed.
    ///
    /// @return Size of the sample result in bytes.
    virtual size_t GetSampleResultSizeInBytes(GpaUInt32 sample_id) const = 0;

    /// @brief Get counter data of the sample.
    ///
    /// @param [in] sample_id The identifier of the sample to get the result for.
    /// @param [in] sample_result_size_in_bytes Size of sample in bytes.
    /// @param [out] counter_sample_results Address to which the counter data for the sample will be copied to.
    ///
    /// @return The GPA result status of the operation. kGpaStatusOk is returned if the operation is successful.
    virtual GpaStatus GetSampleResult(GpaUInt32 sample_id, size_t sample_result_size_in_bytes, void* counter_sample_results) = 0;

    /// @brief Gets the supported sample type for this session.
    ///
    /// @return The supported sample type for this session.
    virtual GpaSessionSampleType GetSampleType() const = 0;

    /// @brief Gets the SPM sampling interval (in clock cycles) for this session.
    ///
    /// @return The SPM sampling interval (in clock cycles) for this session.
    virtual GpaUInt32 GetSpmInterval() const = 0;

    /// @brief Sets the SPM sampling interval (in clock cycles) for this session.
    ///
    /// @param Interval the SPM sampling interval (in clock cycles) to set for this session.
    virtual void SetSpmInterval(GpaUInt32 interval) = 0;

    /// @brief Gets the SPM memory limit (in bytes) for this session.
    ///
    /// @return The SPM memory limit (in bytes) for this session.
    virtual GpaUInt64 GetSpmMemoryLimit() const = 0;

    /// @brief Sets the SPM memory limit (in bytes) for this session.
    ///
    /// @param [in] memory_limit The SPM memory limit (in bytes) to set for this session.
    virtual void SetSpmMemoryLimit(GpaUInt64 memory_limit) = 0;

    /// @brief Gets the mask of instruction types to be included in the SQTT data.
    ///
    /// @return The mask of instructions included in the SQTT data.
    virtual GpaSqttInstructionFlags GetSqttInstructionMask() const = 0;

    /// @brief Sets the mask of instruction types to be included in the SQTT data.
    ///
    /// @param [in] sqtt_instruction_mask The mask of instructions included in the SQTT data.
    virtual void SetSqttInstructionMask(GpaSqttInstructionFlags sqtt_instruction_mask) = 0;

    /// @brief Gets the id of the compute unit which should generate the instruction level data.
    ///
    /// @return The id of the compute unit which should generate the instruction level data.
    virtual GpaUInt32 GetSqttComputeUnitId() const = 0;

    /// @brief Sets the id of the compute unit which should generate the instruction level data.
    ///
    /// @param [in] sqtt_compute_unit_id The id of the compute unit which should generate the instruction level data.
    virtual void SetSqttComputeUnitId(GpaUInt32 sqtt_compute_unit_id) = 0;

    /// @brief Gets the SQTT memory limit (in bytes) for this session.
    ///
    /// @return The SQTT memory limit (in bytes) for this session.
    virtual GpaUInt64 GetSqttMemoryLimit() const = 0;

    /// @brief Sets the SQTT memory limit (in bytes) for this session.
    ///
    /// @param [in] memory_limit The SQTT memory limit (in bytes) to set for this session.
    virtual void SetSqttMemoryLimit(GpaUInt64 memory_limit) = 0;

    /// @brief Returns the counter list for the given pass in the session.
    ///
    /// @param [in] pass_index Index of the pass.
    ///
    /// @return Counter list for the given pass.
    virtual std::vector<unsigned int>* GetCountersForPass(unsigned int pass_index) = 0;
};

#endif  // GPU_PERF_API_COMMON_GPA_SESSION_INTERFACE_H_
