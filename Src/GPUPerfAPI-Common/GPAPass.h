//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA Pass Object Header
//==============================================================================

#ifndef _GPA_PASS_H_
#define _GPA_PASS_H_

// std
#include <vector>
#include <unordered_map>
#include <set>
#include <memory>
#include <atomic>

#include "IGPACounterScheduler.h"
#include "GPASample.h"
#include "GPAContext.h"

using PassIndex = unsigned int;                                       ///< type alias for pass index
using SampleCount = unsigned int;                                     ///< type alias for sample count
using CounterCount = unsigned int;                                    ///< type alias for counter count
using CounterIndex = unsigned int;                                    ///< type alias for counter index
using SamplesMap = std::unordered_map<ClientSampleId, GPASample*>;    ///< type alias for map of client sample id and GPASample Object
using GpaInternalSampleCounter = std::atomic<unsigned int>;           ///< type alias for GPA internal sample counter
using ClientGpaSamplesMap = std::map<unsigned int, unsigned int>;     ///< type alias for map of internal sample id and client sample id
using CounterList = std::vector<CounterIndex>;                        ///< type alias for counter list
using SkippedCounters = std::set<CounterIndex>;                       ///< type alias for list of skipped counters
using SampleIndex = unsigned int;                                     ///< type alias for sample indexes
using GPACommandLists = std::vector<IGPACommandList*>;                ///< type alias for list of GPA command lists
using CommandListCounter = unsigned int;                              ///< type alias for command list counter
using CommandListId = unsigned int;                                   ///< type alias for command list Id

/// Class for GPA pass
class GPAPass
{
public:

    /// Constructor
    /// \param[in] pGpaSession GPA session object pointer
    /// \param[in] passIndex pass index
    /// \param[in] counterSource counter source
    /// \param[in] pCounterScheduler counter scheduler
    /// \param[in] pCounterAccessor counter accessor
    GPAPass(IGPASession* pGpaSession,
            PassIndex passIndex,
            GPACounterSource counterSource,
            IGPACounterScheduler* pCounterScheduler,
            const IGPACounterAccessor* pCounterAccessor);

    /// Delete default constructor
    GPAPass() = delete;

    /// Destructor
    /// Deletes the samples.
    virtual ~GPAPass();

    /// Returns the GPA session
    /// \return GPA session
    IGPASession* GetGpaSession() const;

    /// Returns the counter source of the pass
    /// \return counter source of the pass
    GPACounterSource GetCounterSource() const;

    /// Returns the sample by its client sample Id
    /// \param[in] sampleId Id of the sample
    /// \return GPA Sample object
    GPASample* GetSampleById(ClientSampleId sampleId) const;

    /// Add the sample to the pass
    /// \param[in] clientSampleId index of the sample
    /// \param[in] pCmdList GPA sample object
    /// \return A pointer to the created sample; nullptr if creation failed or clientSampleId already exists.
    GPASample* CreateAndBeginSample(ClientSampleId clientSampleId, IGPACommandList* pCmdList);

    /// Ends a sample created by the CreateAPISpecificSample
    /// \param[in] pCmdList GPA sample object
    /// \return true if operation is successful otherwise false
    virtual bool EndSample(IGPACommandList* pCmdList) = 0;

    /// Creates a new sample on the supplied command list and links with the old sample
    /// \param[in] srcSampleId continuing sample
    /// \param[in] pPrimaryGpaCmdList GPA command list pointer to the primary command list
    /// \return true if operation is successful otherwise false
    virtual bool ContinueSample(ClientSampleId srcSampleId, IGPACommandList* pPrimaryGpaCmdList);

    /// Creates a command list
    /// \param[in] pCmd command list
    /// \param[in] cmdType type of the command list
    /// \return the Command list that was created or null if an error occurred
    virtual IGPACommandList* CreateCommandList(void* pCmd, GPA_Command_List_Type cmdType);

    /// Returns the number of samples in the pass
    /// \return sample count
    SampleCount GetSampleCount() const;

    /// Get the sample id by index
    /// \param[in] sampleIndex index of the sample
    /// \param[out] clientSampleId client sample id
    /// \return true if sample found otherwise false
    bool GetSampleIdByIndex(SampleIndex sampleIndex, ClientSampleId& clientSampleId) const;

    /// Returns the number of counters in the pass
    /// \return sample count
    CounterCount GetEnabledCounterCount() const;

    /// Returns the number of counters skipped in the pass
    /// \return sample count
    CounterCount GetSkippedCounterCount() const;

    /// Returns the index of the pass object
    /// \return index of the pass object
    PassIndex GetIndex() const;

    /// Indicates whether the pass is timing pass or not
    /// \return true if pass is timing otherwise false
    bool IsTimingPass() const;

    /// Should query any available sample results from the driver and store them in local memory.
    /// By default, this is implemented to ask each individual sample to update its own results
    /// if they are available, but may be overridden if more optimal solutions exist.
    /// \return true if the results from all samples on the pass
    /// are now available and cached locally; false if none or only some results are updated.
    virtual bool UpdateResults();

    /// Should confirm that results have been returned from all samples on this pass.
    /// By default, this is implemented to ask each individual sample if it is complete,
    /// but may be overridden if more optimal solutions exist (ie, in DX12 and Vulkan).
    /// \return GPA_STATUS_OK on successful execution
    virtual GPA_Status IsComplete() const;

    /// Should confirm that results are ready to be collected in this pass.
    /// By default, this is implemented to ask each individual command list
    /// if it is complete and ready to retreive the results,
    /// but may be overridden if more optimal solutions exist (ie, in DX12 and Vulkan).
    /// \return true if result is ready otherwise false
    virtual bool IsResultReady() const;

    /// Should confirm that results have been returned from all samples on this pass.
    /// By default, this is implemented to ask each individual sample if it is complete,
    /// but may be overridden if more optimal solutions exist (ie, in DX12 and Vulkan).
    /// \return true if result is collected otherwise false
    virtual bool IsResultCollected() const;

    /// Gets the result for a specific counter within a specific sample.
    /// \param[in] clientSampleId The Sample to get the result from.
    /// \param[in] internalCounterIndex internal counter index
    /// \return The 64-bit counter value.
    virtual gpa_uint64 GetResult(ClientSampleId clientSampleId, CounterIndex internalCounterIndex) const;

    /// Checks to see if the supplied command list exists on this pass.
    /// \param pGpaCommandList The IGPACommandList to search for.
    /// \return True if the command list exists; False otherwise
    bool DoesCommandListExist(IGPACommandList* pGpaCommandList) const;

    /// Checks to see if the supplied ClientSampleId has been opened on this pass.
    /// \param clientSampleId A user-supplied sampleId
    /// \return True if the sample has been opened; False otherwise
    bool DoesSampleExist(ClientSampleId clientSampleId) const;

    /// Returns the command lists for the pass
    /// \return command lists for the pass
    const GPACommandLists& GetCmdList() const;

    /// Adds the counter to the enabled counter set for the pass.
    /// Certain counters can't be enabled in the API specific driver due to unavailability of certain blocks
    /// This function keeps track to add only counter set which can be enabled in the driver
    /// \param[in] counterIndex index of the counter
    void EnableCounterForPass(const CounterIndex& counterIndex);

    /// Adds the counter to the skipped counter set for the pass.
    /// Certain counters can't be enabled in the API specific driver due to unavailability of certain blocks
    /// This function keeps track to add only counterset which can be enabled in the driver
    /// \param[in] counterIndex index of the counter
    void DisableCounterForPass(const CounterIndex& counterIndex);

    /// Adds all counters to enabled counter set for the pass
    void EnableAllCountersForPass();

    /// Adds all counters to disable counter set for the pass
    void DisableAllCountersForPass();

    /// Returns the number of the counters enabled in the driver
    /// \return number of counters
    CounterCount GetNumEnabledCountersForPass() const;

    /// Returns the index of the EOP to TOP timing counter
    /// \return index of the EOP to EOP timing counter
    gpa_uint32 GetBottomToBottomTimingCounterIndex() const;

    /// Returns the index of the TOP to TOP timing counter
    /// \return index of the TOP to EOP timing counter
    gpa_uint32 GetTopToBottomTimingCounterIndex() const;

    /// Iterate over all the counter in the pass
    /// \param[in] function function to be executed for each object in the list - function may return false to terminate iteration
    void IteratePassCounterList(std::function<bool(const CounterIndex& counterIndex)> function) const;

    /// Iterate over all the counter in the pass
    /// \param[in] function function to be executed for each object in the list - function may return false to terminate iteration
    void IterateEnabledCounterList(std::function<bool(const CounterIndex& counterIndex)> function) const;

    /// Iterate over all the counter in the pass
    /// \param[in] function function to be executed for each object in the list - function may return false to terminate iteration
    void IterateSkippedCounterList(std::function<bool(const CounterIndex& counterIndex)> function) const;

    /// Get the counter index in the list of the counters passed to the driver for sample creation
    /// \param[in] counterIndexInPass index of the counter in the pass
    /// \param[out] pInternalCounterIndex internal counter index from the counter generator
    /// \return true if counter index is found otherwise false
    bool GetCounterByIndexInPass(CounterIndex counterIndexInPass, CounterIndex* pInternalCounterIndex) const;

protected:

    /// Checks to see if the supplied ClientSampleId has been opened on this pass.
    /// Does NOT lock the mutex, expects the calling method to do that.
    /// \param clientSampleId A user-supplied sampleId
    /// \return True if the sample has been opened; False otherwise
    bool DoesSampleExist_NotThreadSafe(ClientSampleId clientSampleId) const;

    /// Returns the sample by its client sample Id.
    /// Does NOT lock the mutex, expects the calling method to do that.
    /// \param[in] sampleId Id of the sample
    /// \return GPA Sample object
    GPASample* GetSampleById_NotThreadSafe(ClientSampleId sampleId) const;

    /// Create an API-specific GPASample of the supplied GpaSampleType.
    /// \param[in] pCmdList The commandList on which this sample is taking place.
    /// \param[in] sampleType Indicates whether the created sample should support Software or Hardware counters.
    /// \param[in] sampleId The client-supplied Id that will identify the created sample.
    /// \return A newly allocated API-specific GPASample object.
    virtual GPASample* CreateAPISpecificSample(IGPACommandList* pCmdList,
                                               GpaSampleType sampleType,
                                               ClientSampleId sampleId) = 0;

    /// Creates a command list
    /// \param[in] pCmd command list
    /// \param[in] commandListId command list id
    /// \param[in] cmdType type of the command list
    /// \return the API-specific command list or null if an error occurred
    virtual IGPACommandList* CreateAPISpecificCommandList(void* pCmd,
                                                          CommandListId commandListId,
                                                          GPA_Command_List_Type cmdType) = 0;

    /// Get the counter index in the list of the counters passed to the driver for sample creation
    /// \param[in] internalCounterIndex internal counter index from the counter generator
    /// \param[out] counterIndexInPassList index of the counter in the list of the counters passed to the driver for sample creation
    /// \return true if the internal counter is passed to the driver for sampling otherwise false
    bool GetCounterIndexInPass(CounterIndex internalCounterIndex, CounterIndex& counterIndexInPassList) const;

    /// Returns the status of the result from the driver
    /// \return true if the result from the driver is copied to GPA memory otherwise false
    bool IsResultsCollectedFromDriver() const;

    /// Returns the counter accessor
    /// \return counter accessor
    const IGPACounterAccessor* GetCounterAccessor() const;

    /// Returns the counter scheduler
    /// \return counter scheduler
    const IGPACounterScheduler* GetCounterScheduler() const;

    /// Lock the mutex to protect the GPACommandList vector
    void LockCommandListMutex() const;

    /// Unlock the mutex that protects the GPACommandList vector
    void UnlockCommandListMutex() const;

    /// Adds a client sample to the pass
    /// \param[in] sampleId the id of the sample being added
    /// \param[in] pGPASample the sample being added
    void AddClientSample(ClientSampleId sampleId, GPASample* pGPASample);

    const CounterList*                                     m_pCounterList;          ///< list of counter in a pass
    std::map<gpa_uint32, std::shared_ptr<GPASampleResult>> m_results;               ///< Maps a sample ID to a set of counter results.

private:

    /// Add the GPA command list
    /// \param[in] pGPACommandList GPA command list
    void AddCommandList(IGPACommandList* pGPACommandList);

    /// Checks whether the all the samples are valid and ready to get the result
    /// \return true if pass is ready to collect the result
    bool IsAllSampleValidInPass() const;

    IGPASession*               m_pGpaSession;                   ///< session of the pass
    PassIndex                  m_uiPassIndex;                   ///< index of the pass
    GPACounterSource           m_counterSource;                 ///< counter source of the counters in the pass
    bool                       m_isResultCollected;             ///< flag indicating completion of the pass i.e. data has been collected from the driver
    mutable bool               m_isResultReady;                 ///< flag indicating whether or not results are ready to be collected
    bool                       m_isTimingPass;                  ///< flag indicating pass is timing pass
    IGPACounterScheduler*      m_pCounterScheduler;             ///< counter scheduler
    const IGPACounterAccessor* m_pCounterAccessor;              ///< accessor of the counter for the pass
    mutable std::mutex         m_counterListMutex;              ///< Mutex to protect the m_usedCounterListForPass member;
    CounterList                m_usedCounterListForPass;        ///< list of counters passed to driver for sample
    SkippedCounters            m_skippedCounterList;            ///< List of unsupported counters - these are counters whose blocks are not suported by the API specific driver
    mutable std::mutex         m_gpaCmdListMutex;               ///< Mutex to protect the gpaCmdList
    GPACommandLists            m_gpaCmdList;                    ///< list of api specific command Lists
    mutable std::mutex         m_samplesUnorderedMapMutex;      ///< Mutex to protect the samples map
    SamplesMap                 m_samplesUnorderedMap;           ///< client sample id and GPASample object unordered map
    ClientGpaSamplesMap        m_clientGpaSamplesMap;           ///< cleint sample id and internal sample id map
    GpaInternalSampleCounter   m_gpaInternalSampleCounter;      ///< atomic counter for internal sample counter
    CommandListCounter         m_commandListCounter;            ///< counter representing number of command list created in this pass - This will help in validation and uniquely identifying two different command list
    mutable bool               m_isAllSampleValidInPass;        ///< flag indicating all the sample in the pass is valid or not - for cache
    mutable bool               m_isPassComplete;                ///< flag indicating whether or not the command list and sample on them is complete
};

#endif  // _GPA_PASS_H_
