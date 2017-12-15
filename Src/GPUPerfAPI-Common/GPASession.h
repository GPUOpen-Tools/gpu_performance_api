//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief A base-class implementation of the GPA Session interface
//==============================================================================

#ifndef _GPA_SESSION_H_
#define _GPA_SESSION_H_

#include "IGPASession.h"
#include "IGPACounterScheduler.h"
#include "GPAPass.h"

using SampleIndex = unsigned int;                   ///< type alias for sample indexes
using PassInfo = std::vector<GPAPass*>;             ///< type alias for pass index and its corresponding pass

/// Base class implementation for the IGPASession
class GPASession : public IGPASession
{
public:
    /// Deleted default constructor
    GPASession() = delete;

    /// Constructor
    /// \param[in] pParentContext The context Id on which this session is created
    /// \param[in] pCounterScheduler The counter scheduler that should be used by this session
    GPASession(
        IGPAContext* pParentContext,
        IGPACounterScheduler* pCounterScheduler);

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
    GPA_Status GetEnabledIndex(gpa_uint32 enabledNumber, gpa_uint32* pEnabledCounterIndex) const override;

    /// \copydoc IGPASession::IsCounterEnabled()
    GPA_Status IsCounterEnabled(gpa_uint32 counterIndex) const override;

    /// \copydoc IGPASession::GetNumRequiredPasses()
    GPA_Status GetNumRequiredPasses(gpa_uint32* pNumPasses) override;

    /// \copydoc IGPASession::Begin()
    bool Begin() override;

    /// \copydoc IGPASession::End()
    bool End() override;

    /// \copydoc IGPASession::CreateCommandList()
    GPA_CommandListId CreateCommandList(gpa_uint32 passIndex, void* pCmd, GPA_Command_List_Type cmdType) override;

    /// \copydoc IGPASession::GetSampleCount()
    gpa_uint32 GetSampleCount() const override;

    /// \copydoc IGPASession::DoesCommandListExist()
    bool DoesCommandListExist(gpa_uint32 passIndex, GPA_CommandListId pCommandListId) const override;

    /// \copydoc IGPASession::ContinueSampleOnCommandList()
    GPA_Status ContinueSampleOnCommandList(gpa_uint32 srcSampleId, GPA_CommandListId primaryCommandListId) override;

    /// \copydoc IGPASession::CopySecondarySamples()
    GPA_Status CopySecondarySamples(GPA_CommandListId secondaryCmdListId, GPA_CommandListId primaryCmdListId, gpa_uint32 numSamples, gpa_uint32* pNewSampleIds) override;

    /// \copydoc IGPASession::UpdateResults()
    bool UpdateResults() override;

    /// \copydoc IGPASession::UpdateResults()
    bool UpdateResults(gpa_uint32 passIndex) override;

    /// \copydoc IGPASession::IsSessionRunning()
    bool IsSessionRunning() const override;

    /// \copydoc IGPASession::IsComplete()
    bool IsComplete() const override;

    /// \copydoc IGPASession::GetPerSampleResultSizeInBytes()
    gpa_uint32 GetPerSampleResultSizeInBytes() const override;

    /// \copydoc IGPASession::GetSampleResult()
    GPA_Status GetSampleResult(gpa_uint32 sampleId, gpa_uint64 sampleResultSizeInBytes, void* pCounterSampleResults) override;

    /// \copydoc IGPASession::BeginSample()
    bool BeginSample(ClientSampleId sampleId, GPA_CommandListId commandListId) override;

    /// \copydoc IGPASession::EndSample()
    bool EndSample(GPA_CommandListId commandListId) override;

protected:

    /// Checks whether the multiple passes in the session have same number of samples
    /// \return true if number of samples in each are same
    bool CheckWhetherPassesAreConsistent() const;

    /// Creates the API specific pass
    /// \param[in] passIndex index of the pass
    /// \return API specific pass objec pointer
    virtual GPAPass* CreateAPIPass(PassIndex passIndex) = 0;

    /// Returns the Counter scheduler
    /// \return counter scheduler
    IGPACounterScheduler* GetCounterScheduler() const;

private:

    /// Waits for all data requests to be complete (blocking).
    virtual void Flush();

    mutable std::mutex                  m_gpaSessionMutex;                         ///< Mutex gpa session
    mutable GPASessionState             m_state;                                   ///< The state of the session
    IGPACounterScheduler*               m_pCounterScheduler;                       ///< The counter scheduler that this session will use to schedule counters.
    IGPAContext*                        m_pParentContext;                          ///< The context on which this session was created
    PassInfo                            m_passes;                                  ///< List of pass objects in the session
    unsigned int                        m_sessionID;                               ///< The session ID of this session.
    PassIndex                           m_maxPassIndex;                            ///< maximum pass index reported for creating command list

};

#endif // _GPA_SESSION_H_
