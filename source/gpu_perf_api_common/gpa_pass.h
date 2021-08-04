//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GPA Pass Object Header.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_PASS_H_
#define GPU_PERF_API_COMMON_GPA_PASS_H_

#include <atomic>
#include <memory>
#include <set>
#include <unordered_map>
#include <vector>

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_interface.h"

#include "gpu_perf_api_common/gpa_context.h"
#include "gpu_perf_api_common/gpa_sample.h"

using PassIndex                = unsigned int;                                    ///< Type alias for pass index.
using SampleCount              = unsigned int;                                    ///< Type alias for sample count.
using CounterCount             = unsigned int;                                    ///< Type alias for counter count.
using CounterIndex             = unsigned int;                                    ///< Type alias for counter index.
using SamplesMap               = std::unordered_map<ClientSampleId, GpaSample*>;  ///< Type alias for map of client sample id and GPA sample object.
using GpaInternalSampleCounter = std::atomic<unsigned int>;                       ///< Type alias for GPA internal sample counter.
using ClientGpaSamplesMap      = std::map<unsigned int, unsigned int>;            ///< Type alias for map of internal sample id and client sample id.
using CounterList              = std::vector<CounterIndex>;                       ///< Type alias for counter list.
using SkippedCounters          = std::set<CounterIndex>;                          ///< Type alias for list of skipped counters.
using SampleIndex              = unsigned int;                                    ///< Type alias for sample indexes.
using GpaCommandLists          = std::vector<IGpaCommandList*>;                   ///< Type alias for list of GPA command lists.
using CommandListCounter       = unsigned int;                                    ///< Type alias for command list counter.
using CommandListId            = unsigned int;                                    ///< Type alias for command list Id.

/// @brief Class for GPA pass.
class GpaPass
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] gpa_session GPA session object pointer.
    /// @param [in] pass_index Pass index.
    /// @param [in] counter_source Counter source.
    /// @param [in] pass_counters Counter list for the pass.
    GpaPass(IGpaSession* gpa_session, PassIndex pass_index, GpaCounterSource counter_source, CounterList* pass_counters);

    /// @brief Delete default constructor.
    GpaPass() = delete;

    /// @brief Virtual destructor.
    ///
    /// Deletes the samples.
    virtual ~GpaPass();

    /// @brief Returns the GPA session.
    ///
    /// @return GPA session.
    IGpaSession* GetGpaSession() const;

    /// @brief Returns the counter source of the pass.
    ///
    /// @return Counter source of the pass.
    GpaCounterSource GetCounterSource() const;

    /// @brief Returns the sample by its client sample Id.
    ///
    /// @param [in] sample_id Id of the sample.
    ///
    /// @return GPA Sample object.
    GpaSample* GetSampleById(ClientSampleId sample_id) const;

    /// @brief Add the sample to the pass.
    ///
    /// @param [in] client_sample_id Index of the sample.
    /// @param [in] gpa_cmd_list GPA sample object.
    ///
    /// @return A pointer to the created sample; nullptr if creation failed or client_sample_id already exists.
    GpaSample* CreateAndBeginSample(ClientSampleId client_sample_id, IGpaCommandList* gpa_cmd_list);

    /// @brief Ends a sample created by the CreateAPISpecificSample.
    ///
    /// @param [in] gpa_cmd_list GPA sample object.
    ///
    /// @return True if operation is successful otherwise false.
    virtual bool EndSample(IGpaCommandList* gpa_cmd_list) = 0;

    /// @brief Creates a new sample on the supplied command list and links with the old sample.
    ///
    /// @param [in] src_sample_id Continuing sample.
    /// @param [in] primary_gpa_cmd_list GPA command list pointer to the primary command list.
    ///
    /// @return True if operation is successful otherwise false.
    virtual bool ContinueSample(ClientSampleId src_sample_id, IGpaCommandList* primary_gpa_cmd_list);

    /// @brief Creates a command list.
    ///
    /// @param [in] cmd_list Command list.
    /// @param [in] cmd_type Type of the command list.
    ///
    /// @return The Command list that was created or null if an error occurred.
    virtual IGpaCommandList* CreateCommandList(void* cmd_list, GpaCommandListType cmd_type);

    /// @brief Returns the number of samples in the pass.
    ///
    /// @return sample count.
    SampleCount GetSampleCount() const;

    /// @brief Get the sample id by index.
    ///
    /// @param [in] sample_index Index of the sample.
    /// @param [out] client_sample_id Client sample id.
    ///
    /// @return True if sample found otherwise false.
    bool GetSampleIdByIndex(SampleIndex sample_index, ClientSampleId& client_sample_id) const;

    /// @brief Returns the number of counters in the pass.
    ///
    /// @return Sample count.
    CounterCount GetEnabledCounterCount() const;

    /// @brief Returns the number of counters skipped in the pass.
    ///
    /// @return Sample count.
    CounterCount GetSkippedCounterCount() const;

    /// @brief Returns the index of the pass object.
    ///
    /// @return Index of the pass object.
    PassIndex GetIndex() const;

    /// @brief Indicates whether the pass is timing pass or not.
    ///
    /// @return True if pass is timing otherwise false.
    bool IsTimingPass() const;

    /// @brief Should query any available sample results from the driver and store them in local memory.
    ///
    /// By default, this is implemented to ask each individual sample to update its own results
    /// if they are available, but may be overridden if more optimal solutions exist.
    ///
    /// @retval true If the results from all samples on the pass are now available and cached locally.
    /// @retval false If none or only some results are updated.
    virtual bool UpdateResults();

    /// @brief Should confirm that results have been returned from all samples on this pass.
    ///
    /// By default, this is implemented to ask each individual sample if it is complete,
    /// but may be overridden if more optimal solutions exist (i.e., in DX12 and Vulkan).
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus IsComplete() const;

    /// @brief Should confirm that results are ready to be collected in this pass.
    ///
    /// By default, this is implemented to ask each individual command list.
    /// if it is complete and ready to retrieve the results,
    /// but may be overridden if more optimal solutions exist (i.e., in DX12 and Vulkan).
    ///
    /// @return True if result is ready otherwise false.
    virtual bool IsResultReady() const;

    /// @brief Should confirm that results have been returned from all samples on this pass.
    ///
    /// By default, this is implemented to ask each individual sample if it is complete,
    /// but may be overridden if more optimal solutions exist (i.e., in DX12 and Vulkan).
    ///
    /// @return True if result is collected otherwise false.
    virtual bool IsResultCollected() const;

    /// @brief Gets the result for a specific counter within a specific sample.
    ///
    /// @param [in] client_sample_id The Sample to get the result from.
    /// @param [in] internal_counter_index Internal counter index.
    /// @param [out] result_buffer The 64-bit counter value.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus GetResult(ClientSampleId client_sample_id, CounterIndex internal_counter_index, GpaUInt64* result_buffer) const;

    /// @brief Checks to see if the supplied command list exists on this pass.
    ///
    /// @param [in] gpa_cmd_list The IGpaCommandList to search for.
    ///
    /// @return True if the command list exists; False otherwise.
    bool DoesCommandListExist(IGpaCommandList* gpa_cmd_list) const;

    /// @brief Checks to see if the supplied ClientSampleId has been opened on this pass.
    ///
    /// @param client_sample_id A user-supplied sample id.
    ///
    /// @return True if the sample has been opened; False otherwise.
    bool DoesSampleExist(ClientSampleId client_sample_id) const;

    /// @brief Returns the command lists for the pass.
    ///
    /// @return Command lists for the pass.
    const GpaCommandLists& GetCmdList() const;

    /// @brief Adds the counter to the enabled counter set for the pass.
    ///
    /// Certain counters can't be enabled in the API specific driver due to unavailability of certain blocks.
    /// This function keeps track to add only counter set which can be enabled in the driver.
    ///
    /// @param [in] counter_index Index of the counter.
    void EnableCounterForPass(const CounterIndex& counter_index);

    /// @brief Adds the counter to the skipped counter set for the pass.
    ///
    /// Certain counters can't be enabled in the API specific driver due to unavailability of certain blocks.
    /// This function keeps track to add only counter set which can be enabled in the driver.
    ///
    /// @param [in] counter_index Index of the counter.
    void DisableCounterForPass(const CounterIndex& counter_index);

    /// @brief Adds all counters to enabled counter set for the pass.
    void EnableAllCountersForPass();

    /// @brief Adds all counters to disable counter set for the pass.
    void DisableAllCountersForPass();

    /// @brief Returns the number of the counters enabled in the driver.
    ///
    /// @return Number of counters.
    CounterCount GetNumEnabledCountersForPass() const;

    /// @brief Returns the index of the Bottom-Of-Pipe (BOP) to BOP timing counter.
    ///
    /// @return Index of the BOP to BOP timing counter.
    GpaUInt32 GetBottomToBottomTimingDurationCounterIndex() const;

    /// @brief Returns the index of the Top-Of-Pipe (TOP) to Bottom-Of-Pipe (BOP) timing counter.
    ///
    /// @return Index of the TOP to BOP timing counter.
    GpaUInt32 GetTopToBottomTimingDurationCounterIndex() const;

    /// @brief Iterate over all the counter in the pass.
    ///
    /// @param [in] function Function to be executed for each object in the list - function may return false to terminate iteration.
    void IteratePassCounterList(std::function<bool(const CounterIndex& counter_index)> function) const;

    /// @brief Iterate over all the counter in the pass.
    ///
    /// @param [in] function Function to be executed for each object in the list - function may return false to terminate iteration.
    void IterateEnabledCounterList(std::function<bool(const CounterIndex& counter_index)> function) const;

    /// @brief Iterate over all the counter in the pass.
    ///
    /// @param [in] function Function to be executed for each object in the list - function may return false to terminate iteration.
    void IterateSkippedCounterList(std::function<bool(const CounterIndex& counter_index)> function) const;

    /// @brief Get the counter index in the list of the counters passed to the driver for sample creation.
    ///
    /// @param [in] counter_index_in_pass Index of the counter in the pass.
    /// @param [out] internal_counter_index Internal counter index from the counter generator.
    ///
    /// @return True if counter index is found otherwise false.
    bool GetCounterByIndexInPass(CounterIndex counter_index_in_pass, CounterIndex* internal_counter_index) const;

    /// @brief Returns the counter accessor for the pass' session context.
    ///
    /// @return counter accessor.
    const IGpaCounterAccessor* GetSessionContextCounterAccessor() const;

protected:
    /// @brief Checks to see if the supplied ClientSampleId has been opened on this pass.
    ///
    /// Does NOT lock the mutex, expects the calling method to do that.
    ///
    /// @param [in] client_sample_id A user-supplied sample id.
    ///
    /// @return True if the sample has been opened; False otherwise.
    bool DoesSampleExistNotThreadSafe(ClientSampleId client_sample_id) const;

    /// @brief Returns the sample by its client sample Id.
    ///
    /// Does NOT lock the mutex, expects the calling method to do that.
    ///
    /// @param [in] client_sample_id Id of the sample.
    ///
    /// @return GPA Sample object.
    GpaSample* GetSampleByIdNotThreadSafe(ClientSampleId client_sample_id) const;

    /// @brief Create an API-specific GPASample of the supplied GpaSampleType.
    ///
    /// @param [in] gpa_cmd_list The commandList on which this sample is taking place.
    /// @param [in] sample_type Indicates whether the created sample should support Software or Hardware counters.
    /// @param [in] client_sample_id The client-supplied Id that will identify the created sample.
    ///
    /// @return A newly allocated API-specific GPASample object.
    virtual GpaSample* CreateApiSpecificSample(IGpaCommandList* gpa_cmd_list, GpaSampleType sample_type, ClientSampleId client_sample_id) = 0;

    /// @brief Creates a command list.
    ///
    /// @param [in] cmd_list Command list.
    /// @param [in] command_list_id Command list id.
    /// @param [in] cmd_type Type of the command list.
    ///
    /// @return The API-specific command list or null if an error occurred.
    virtual IGpaCommandList* CreateApiSpecificCommandList(void* cmd_list, CommandListId command_list_id, GpaCommandListType cmd_type) = 0;

    /// @brief Get the counter index in the list of the counters passed to the driver for sample creation.
    ///
    /// @param [in] internal_counter_index Internal counter index from the counter generator.
    /// @param [out] counter_indices_in_pass Index of the counter in the list of the counters passed to the driver for sample creation.
    ///
    /// @return True if the internal counter is passed to the driver for sampling otherwise false.
    bool GetCounterIndexInPass(CounterIndex internal_counter_index, CounterIndex* counter_indices_in_pass) const;

    /// @brief Returns the status of the result from the driver.
    ///
    /// @return True if the result from the driver is copied to GPA memory otherwise false.
    bool IsResultsCollectedFromDriver() const;

    /// @brief Lock the mutex to protect the GPACommandList vector.
    void LockCommandListMutex() const;

    /// @brief Unlock the mutex that protects the GPACommandList vector.
    void UnlockCommandListMutex() const;

    /// @brief Adds a client sample to the pass.
    ///
    /// @param [in] sample_id The id of the sample being added.
    /// @param [in] gpa_sample The sample being added.
    void AddClientSample(ClientSampleId sample_id, GpaSample* gpa_sample);

    const CounterList*                                    counter_list_;                  ///< List of counter in a pass.
    std::map<GpaUInt32, std::shared_ptr<GpaSampleResult>> counter_results_by_sample_id_;  ///< Maps a sample ID to a set of counter results.

private:
    /// @brief Add the GPA command list.
    ///
    /// @param [in] gpa_command_list GPA command list.
    void AddCommandList(IGpaCommandList* gpa_command_list);

    /// @brief Checks whether the all the samples are valid and ready to get the result.
    ///
    /// @return True if pass is ready to collect the result.
    bool IsAllSampleValidInPass() const;

    IGpaSession*       gpa_session_;                 ///< Session of the pass.
    PassIndex          pass_index_;                  ///< Index of the pass.
    GpaCounterSource   counter_source_;              ///< Counter source of the counters in the pass.
    bool               is_result_collected_;         ///< Flag indicating completion of the pass i.e. data has been collected from the driver.
    mutable bool       is_result_ready_;             ///< Flag indicating whether or not results are ready to be collected.
    bool               is_timing_pass_;              ///< Flag indicating pass is timing pass.
    mutable std::mutex counter_list_mutex_;          ///< Mutex to protect the used_counter_list_for_pass_ member.
    CounterList        used_counter_list_for_pass_;  ///< List of counters passed to driver for sample.
    SkippedCounters    skipped_counter_list_;  ///< List of unsupported counters - these are counters whose blocks are not supported by the API specific driver.
    mutable std::mutex gpa_cmd_list_mutex_;    ///< Mutex to protect the gpaCmdList.
    GpaCommandLists    gpa_cmd_lists_;         ///< List of API specific command Lists.
    mutable std::mutex samples_unordered_map_mutex_;        ///< Mutex to protect the samples map.
    SamplesMap         samples_unordered_map_;              ///< Client sample id and GPASample object unordered map.
    ClientGpaSamplesMap      client_gpa_samples_map_;       ///< Client sample id and internal sample id map.
    GpaInternalSampleCounter gpa_internal_sample_counter_;  ///< Atomic counter for internal sample counter.

    /// Counter representing number of command list created in this pass - This will help in validation and uniquely identifying two different command list.
    CommandListCounter command_list_counter_;
    mutable bool       is_all_sample_valid_in_pass_;  ///< Flag indicating all the sample in the pass is valid or not - for cache.
    mutable bool       is_pass_complete_;             ///< Flag indicating whether or not the command list and sample on them is complete.
};

#endif  // GPU_PERF_API_COMMON_GPA_PASS_H_
