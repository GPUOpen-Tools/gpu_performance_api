//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief A base-class implementation of the GPA Session interface
//==============================================================================

#ifndef _GPA_SESSION_H_
#define _GPA_SESSION_H_

#include "IGPASession.h"
#include "IGPACounterScheduler.h"
#include "GPAPass.h"

using PassInfo = std::vector<GPAPass*>; ///< type alias for pass index and its corresponding pass

const uint32_t GPA_TIMEOUT_INFINITE = static_cast<uint32_t>(-1); ///< Timeout constant indicating "infinite", or no, timeout

/// Base class implementation for the IGPASession
class GPASession : public IGPASession
{
public:
    /// Constructor
    /// \param[in] pParentContext The context Id on which this session is created
    /// \param[in] sampleType The type of samples that will be created on this session
    GPASession(IGPAContext* pParentContext,
               GPA_Session_Sample_Type sampleType);

    /// Delete default constructor
    GPASession() = delete;

    /// Destructor
    virtual ~GPASession();

    /// \copydoc IGPAInterfaceTrait::ObjectType()
    GPAObjectType ObjectType() const override;

    /// \copydoc IGPASession::GetParentContext()
    IGPAContext* GetParentContext() const override;

    /// \copydoc IGPASession::GetState()
    GPASessionState GetState() const override;

    /// \copydoc IGPASession::EnableCounter()
    GPA_Status EnableCounter(gpa_uint32 index) override;

    /// \copydoc IGPASession::DisableCounter()
    GPA_Status DisableCounter(gpa_uint32 index) override;

    /// \copydoc IGPASession::DisableAllCounters()
    GPA_Status DisableAllCounters() override;

    /// \copydoc IGPASession::GetNumEnabledCounters()
    GPA_Status GetNumEnabledCounters(gpa_uint32* pCount) const override;

    /// \copydoc IGPASession::GetEnabledIndex()
    GPA_Status GetEnabledIndex(gpa_uint32 enabledNumber,
                               gpa_uint32* pEnabledCounterIndex) const override;

    /// \copydoc IGPASession::IsCounterEnabled()
    GPA_Status IsCounterEnabled(gpa_uint32 counterIndex) const override;

    /// \copydoc IGPASession::GetNumRequiredPasses()
    GPA_Status GetNumRequiredPasses(gpa_uint32* pNumPasses) override;

    /// \copydoc IGPASession::Begin()
    GPA_Status Begin() override;

    /// \copydoc IGPASession::End()
    GPA_Status End() override;

    /// \copydoc IGPASession::CreateCommandList()
    GPA_CommandListId CreateCommandList(gpa_uint32 passIndex,
                                        void* pCmd,
                                        GPA_Command_List_Type cmdType) override;

    /// \copydoc IGPASession::GetSampleCount()
    gpa_uint32 GetSampleCount() const override;

    /// \copydoc IGPASession::GetSampleIdByIndex()
    bool GetSampleIdByIndex(SampleIndex sampleIndex, ClientSampleId& clientSampleId) const override;

    /// \copydoc IGPASession::DoesCommandListExist()
    bool DoesCommandListExist(gpa_uint32 passIndex,
                              GPA_CommandListId pCommandListId) const override;

    /// \copydoc IGPASession::DoesSampleExist()
    bool DoesSampleExist(gpa_uint32 sampleId) const override;

    /// \copydoc IGPASession::BeginSample()
    bool BeginSample(ClientSampleId sampleId,
                     GPA_CommandListId commandListId) override;

    /// \copydoc IGPASession::EndSample()
    bool EndSample(GPA_CommandListId commandListId) override;

    /// \copydoc IGPASession::ContinueSampleOnCommandList()
    GPA_Status ContinueSampleOnCommandList(gpa_uint32 srcSampleId,
                                           GPA_CommandListId primaryCommandListId) override;

    /// \copydoc IGPASession::CopySecondarySamples()
    GPA_Status CopySecondarySamples(GPA_CommandListId secondaryCmdListId,
                                    GPA_CommandListId primaryCmdListId,
                                    gpa_uint32 numSamples,
                                    gpa_uint32* pNewSampleIds) override;

    /// \copydoc IGPASession::UpdateResults()
    bool UpdateResults() override;

    /// \copydoc IGPASession::UpdateResults(gpa_uint32)
    bool UpdateResults(gpa_uint32 passIndex) override;

    /// \copydoc IGPASession::IsSessionRunning()
    bool IsSessionRunning() const override;

    /// \copydoc IGPASession::IsPassComplete()
    GPA_Status IsPassComplete(gpa_uint32 passIndex) const override;

    /// \copydoc IGPASession::IsResultReady()
    bool IsResultReady() const override;

    /// \copydoc IGPASession::GetSampleResultSizeInBytes()
    size_t GetSampleResultSizeInBytes(gpa_uint32 sampleId) const override;

    /// \copydoc IGPASession::GetSampleResult()
    GPA_Status GetSampleResult(gpa_uint32 sampleId,
                               size_t sampleResultSizeInBytes,
                               void* pCounterSampleResults) override;

    /// \copydoc IGPASession::GetSampleType()
    GPA_Session_Sample_Type GetSampleType() const override;

    /// \copydoc IGPASession::GetSPMInterval()
    gpa_uint32 GetSPMInterval() const override;

    /// \copydoc IGPASession::SetSPMInterval()
    void SetSPMInterval(gpa_uint32 interval) override;

    /// \copydoc IGPASession::GetSPMMemoryLimit()
    gpa_uint64 GetSPMMemoryLimit() const override;

    /// \copydoc IGPASession::SetSPMMemoryLimit()
    void SetSPMMemoryLimit(gpa_uint64 memoryLimit) override;

    /// \copydoc IGPASession::GetSQTTInstructionMask()
    GPA_SQTTInstructionFlags GetSQTTInstructionMask() const override;

    /// \copydoc IGPASession::SetSQTTInstructionMask()
    void SetSQTTInstructionMask(GPA_SQTTInstructionFlags sqttInstructionMask) override;

    /// \copydoc IGPASession::GetSQTTComputeUnitId()
    gpa_uint32 GetSQTTComputeUnitId() const override;

    /// \copydoc IGPASession::SetSQTTComputeUnitId()
    void SetSQTTComputeUnitId(gpa_uint32 sqttComputeUnitId) override;

    /// \copydoc IGPASession::GetSQTTMemoryLimit()
    gpa_uint64 GetSQTTMemoryLimit() const override;

    /// \copydoc IGPASession::SetSQTTMemoryLimit()
    void SetSQTTMemoryLimit(gpa_uint64 memoryLimit) override;

    /// \copydoc IGPASession::GetCountersForPass()
    CounterList* GetCountersForPass(PassIndex passIndex) override;

protected:

    /// Checks whether the multiple passes in the session have same number of samples
    /// \return true if number of samples in each are same
    bool CheckWhetherPassesAreFinishedAndConsistent() const;

    /// Creates the API specific pass
    /// \param[in] passIndex index of the pass
    /// \return API specific pass objec pointer
    virtual GPAPass* CreateAPIPass(PassIndex passIndex) = 0;

private:

    /// Waits for all data requests to be complete (blocking).
    /// \param timeout the amount of time (in milliseconds) to wait before giving up
    /// \return true if all data requests are complete, false if a timeout occurred
    virtual bool Flush(uint32_t timeout = GPA_TIMEOUT_INFINITE);

    /// Gathers the counter result locations
    /// \return true upon successful copying otherwise false
    bool GatherCounterResultLocations();

    using SessionCounters = std::vector<gpa_uint32>; ///< type alias for counters in the session
    using CounterResultLocationPair = std::pair<DerivedCounterIndex, CounterResultLocationMap>; ///< type alias for counter and its reult location pair
    using CounterResultLocations = std::map<DerivedCounterIndex, CounterResultLocationMap>; ///< type alias for counter and its reult location map
    using PassCountersPair = std::pair<PassIndex, CounterList>; ///< type alias for pass and its counters pair
    using PassCountersMap = std::map<PassIndex, CounterList>; ///< type alias for pass and its counters map

    mutable std::mutex          m_gpaSessionMutex;        ///< Mutex GPA session
    mutable GPASessionState     m_state;                  ///< The state of the session
    IGPAContext*                m_pParentContext;         ///< The context on which this session was created
    PassInfo                    m_passes;                 ///< List of pass objects in the session
    PassIndex                   m_maxPassIndex;           ///< maximum pass index reported for creating command list
    GPA_Session_Sample_Type     m_sampleType;             ///< the sample type suported by the session
    gpa_uint32                  m_spmInterval;            ///< the interval (in clock cycles) at which to sample SPM counters
    gpa_uint64                  m_spmMemoryLimit;         ///< the maximum amount of GPU memory (in bytes) to use for SPM data
    GPA_SQTTInstructionFlags    m_sqttInstructionMask;    ///< mask of instructions included in the SQTT data
    gpa_uint32                  m_sqttComputeUnitId;      ///< id of the compute unit which should generate the insruction level data
    gpa_uint64                  m_sqttMemoryLimit;        ///< the maximum amount of GPU memory (in bytes) to use for SQTT data
    SessionCounters             m_sessionCounters;        ///< list of counters enabled in the session
    std::mutex                  m_sessionCountersMutex;   ///< mutex for enabled counter list
    gpa_uint32                  m_passRequired;           ///< cached number of passes
    bool                        m_counterSetChanged;      ///< flag indicating the counter selection has changed or not for the pass
    CounterResultLocations      m_counterResultLocations; ///< counter result location for the scheduled counter in the session
    PassCountersMap             m_passCountersMap;        ///< map for the pass and its counters
};

#endif // _GPA_SESSION_H_
