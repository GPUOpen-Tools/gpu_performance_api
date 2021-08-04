//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief A base-class implementation of the GPA Session interface.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_SESSION_H_
#define GPU_PERF_API_COMMON_GPA_SESSION_H_

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_interface.h"

#include "gpu_perf_api_common/gpa_pass.h"
#include "gpu_perf_api_common/gpa_session_interface.h"

using PassInfo = std::vector<GpaPass*>;  ///< Type alias for pass index and its corresponding pass.

/// Timeout constant indicating "infinite", or no, timeout.
const uint32_t kGpaTimeoutInfinite = static_cast<uint32_t>(-1);

/// @brief Base class implementation for the IGpaSession.
class GpaSession : public IGpaSession
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] parent_context The context Id on which this session is created.
    /// @param [in] sample_type The type of samples that will be created on this session.
    GpaSession(IGpaContext* parent_context, GpaSessionSampleType sample_type);

    /// @brief Delete default constructor.
    GpaSession() = delete;

    /// @brief Virtual Destructor.
    virtual ~GpaSession();

    /// @copydoc IGpaInterfaceTrait::ObjectType()
    GpaObjectType ObjectType() const override;

    /// @copydoc IGpaSession::GetParentContext()
    IGpaContext* GetParentContext() const override;

    /// @copydoc IGpaSession::GetState()
    GpaSessionState GetState() const override;

    /// @copydoc IGpaSession::EnableCounter()
    GpaStatus EnableCounter(GpaUInt32 index) override;

    /// @copydoc IGpaSession::DisableCounter()
    GpaStatus DisableCounter(GpaUInt32 index) override;

    /// @copydoc IGpaSession::DisableAllCounters()
    GpaStatus DisableAllCounters() override;

    /// @copydoc IGpaSession::GetNumEnabledCounters()
    GpaStatus GetNumEnabledCounters(GpaUInt32* counter_count) const override;

    /// @copydoc IGpaSession::GetEnabledIndex()
    GpaStatus GetEnabledIndex(GpaUInt32 enabled_number, GpaUInt32* enabled_counter_index) const override;

    /// @copydoc IGpaSession::IsCounterEnabled()
    GpaStatus IsCounterEnabled(GpaUInt32 counter_index) const override;

    /// @copydoc IGpaSession::GetNumRequiredPasses()
    GpaStatus GetNumRequiredPasses(GpaUInt32* num_passes) override;

    /// @copydoc IGpaSession::Begin()
    GpaStatus Begin() override;

    /// @copydoc IGpaSession::End()
    GpaStatus End() override;

    /// @copydoc IGpaSession::CreateCommandList()
    GpaCommandListId CreateCommandList(GpaUInt32 pass_index, void* cmd_list, GpaCommandListType cmd_type) override;

    /// @copydoc IGpaSession::GetSampleCount()
    GpaUInt32 GetSampleCount() const override;

    /// @copydoc IGpaSession::GetSampleIdByIndex()
    bool GetSampleIdByIndex(SampleIndex sample_index, ClientSampleId& client_sample_id) const override;

    /// @copydoc IGpaSession::DoesCommandListExist()
    bool DoesCommandListExist(GpaUInt32 pass_index, GpaCommandListId gpa_command_list_id) const override;

    /// @copydoc IGpaSession::DoesSampleExist()
    bool DoesSampleExist(GpaUInt32 sample_id) const override;

    /// @copydoc IGpaSession::BeginSample()
    bool BeginSample(ClientSampleId sample_id, GpaCommandListId command_list_id) override;

    /// @copydoc IGpaSession::EndSample()
    bool EndSample(GpaCommandListId command_list_id) override;

    /// @copydoc IGpaSession::ContinueSampleOnCommandList()
    GpaStatus ContinueSampleOnCommandList(GpaUInt32 src_sample_id, GpaCommandListId primary_command_list_id) override;

    /// @copydoc IGpaSession::CopySecondarySamples()
    GpaStatus CopySecondarySamples(GpaCommandListId secondary_cmd_list_id,
                                   GpaCommandListId primary_cmd_list_id,
                                   GpaUInt32        num_samples,
                                   GpaUInt32*       new_sample_ids) override;

    /// @copydoc IGpaSession::UpdateResults()
    bool UpdateResults() override;

    /// @copydoc IGpaSession::UpdateResults(GpaUInt32)
    bool UpdateResults(GpaUInt32 pass_index) override;

    /// @copydoc IGpaSession::IsSessionRunning()
    bool IsSessionRunning() const override;

    /// @copydoc IGpaSession::IsPassComplete()
    GpaStatus IsPassComplete(GpaUInt32 pass_index) const override;

    /// @copydoc IGpaSession::IsResultReady()
    bool IsResultReady() const override;

    /// @copydoc IGpaSession::GetSampleResultSizeInBytes()
    size_t GetSampleResultSizeInBytes(GpaUInt32 sample_id) const override;

    /// @copydoc IGpaSession::GetSampleResult()
    GpaStatus GetSampleResult(GpaUInt32 sample_id, size_t sample_result_size_in_bytes, void* counter_sample_results) override;

    /// @copydoc IGpaSession::GetSampleType()
    GpaSessionSampleType GetSampleType() const override;

    /// @copydoc IGpaSession::GetSpmInterval()
    GpaUInt32 GetSpmInterval() const override;

    /// @copydoc IGpaSession::SetSpmInterval()
    void SetSpmInterval(GpaUInt32 interval) override;

    /// @copydoc IGpaSession::GetSpmMemoryLimit()
    GpaUInt64 GetSpmMemoryLimit() const override;

    /// @copydoc IGpaSession::SetSpmMemoryLimit()
    void SetSpmMemoryLimit(GpaUInt64 memory_limit) override;

    /// @copydoc IGpaSession::GetSqttInstructionMask()
    GpaSqttInstructionFlags GetSqttInstructionMask() const override;

    /// @copydoc IGpaSession::SetSqttInstructionMask()
    void SetSqttInstructionMask(GpaSqttInstructionFlags sqtt_instruction_mask) override;

    /// @copydoc IGpaSession::GetSqttComputeUnitId()
    GpaUInt32 GetSqttComputeUnitId() const override;

    /// @copydoc IGpaSession::SetSqttComputeUnitId()
    void SetSqttComputeUnitId(GpaUInt32 sqtt_compute_unit_id) override;

    /// @copydoc IGpaSession::GetSqttMemoryLimit()
    GpaUInt64 GetSqttMemoryLimit() const override;

    /// @copydoc IGpaSession::SetSqttMemoryLimit()
    void SetSqttMemoryLimit(GpaUInt64 memory_limit) override;

    /// @copydoc IGpaSession::GetCountersForPass()
    CounterList* GetCountersForPass(PassIndex pass_index) override;

protected:
    /// @brief Checks whether the multiple passes in the session have same number of samples.
    ///
    /// @return True if number of samples in each are same.
    bool CheckWhetherPassesAreFinishedAndConsistent() const;

    /// @brief Creates the API specific pass.
    ///
    /// @param [in] pass_index Index of the pass.
    ///
    /// @return API specific pass object pointer.
    virtual GpaPass* CreateApiPass(PassIndex pass_index) = 0;

private:
    /// @brief Waits for all data requests to be complete (blocking).
    ///
    /// @param [in] timeout The amount of time (in milliseconds) to wait before giving up.
    ///
    /// @return True if all data requests are complete, false if a timeout occurred.
    virtual bool Flush(uint32_t timeout = kGpaTimeoutInfinite);

    /// @brief Gathers the counter result locations.
    ///
    /// @return True upon successful copying otherwise false.
    bool GatherCounterResultLocations();

    using SessionCounters           = std::vector<GpaUInt32>;                                    ///< Type alias for counters in the session.
    using CounterResultLocationPair = std::pair<DerivedCounterIndex, CounterResultLocationMap>;  ///< Type alias for counter and its result location pair.
    using CounterResultLocations    = std::map<DerivedCounterIndex, CounterResultLocationMap>;   ///< Type alias for counter and its result location map.
    using PassCountersPair          = std::pair<PassIndex, CounterList>;                         ///< Type alias for pass and its counters pair.
    using PassCountersMap           = std::map<PassIndex, CounterList>;                          ///< Type alias for pass and its counters map.

    mutable std::mutex      gpa_session_mutex_;         ///< Mutex GPA session.
    mutable GpaSessionState gpa_session_state_;         ///< The state of the session.
    IGpaContext*            parent_context_;            ///< The context on which this session was created.
    PassInfo                passes_;                    ///< List of pass objects in the session.
    PassIndex               max_pass_index_;            ///< Maximum pass index reported for creating command list.
    GpaSessionSampleType    sample_type_;               ///< The sample type supported by the session.
    GpaUInt32               spm_interval_;              ///< The interval (in clock cycles) at which to sample SPM counters.
    GpaUInt64               spm_memory_limit_;          ///< The maximum amount of GPU memory (in bytes) to use for SPM data.
    GpaSqttInstructionFlags sqtt_instruction_mask_;     ///< Mask of instructions included in the SQTT data.
    GpaUInt32               sqtt_compute_unit_id_;      ///< Id of the compute unit which should generate the instruction level data.
    GpaUInt64               sqtt_memory_limit_;         ///< The maximum amount of GPU memory (in bytes) to use for SQTT data.
    SessionCounters         session_counters_;          ///< List of counters enabled in the session.
    std::mutex              session_counters_mutex_;    ///< Mutex for enabled counter list.
    GpaUInt32               pass_required_;             ///< Cached number of passes.
    bool                    counter_set_changed_;       ///< Flag indicating the counter selection has changed or not for the pass.
    CounterResultLocations  counter_result_locations_;  ///< Counter result location for the scheduled counter in the session.
    PassCountersMap         pass_counters_map_;         ///< Map for the pass and its counters.
};

#endif  // GPU_PERF_API_COMMON_GPA_SESSION_H_
