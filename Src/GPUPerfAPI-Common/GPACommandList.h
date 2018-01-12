//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GPA Command List Declarations
//==============================================================================

#ifndef _GPA_COMMAND_LIST_H_
#define _GPA_COMMAND_LIST_H_

// GPA Common
#include "IGPACommandList.h"
#include "GPASample.h"

/// Class for GPA Command List
class GPACommandList : public IGPACommandList
{
public:

    /// Constructor
    GPACommandList() = delete;

    /// Constructor
    /// \param[in] pGpaSession GPA session pointer
    /// \param[in] pGpaPass pass object pointer
    GPACommandList(IGPASession* pGpaSession, GPAPass* pGpaPass);

    /// Destructor
    virtual ~GPACommandList() = default;

    /// \copydoc IGPACommandList::GetParentSession()
    IGPASession* GetParentSession() const override;

    /// \copydoc IGPACommandList::Begin()
    bool Begin() override;

    /// \copydoc IGPACommandList::End()
    bool End() override;

    /// \copydoc IGPACommandList::IsCommandListRunning()
    bool IsCommandListRunning() const override;

    /// \copydoc IGPACommandList::GetPass()
    GPAPass* GetPass() const override;

    /// \copydoc IGPACommandList::GetSampleCount()
    gpa_uint32 GetSampleCount() const override;

    /// \copydoc IGPACommandList::BeginSample()
    bool BeginSample(ClientSampleId clientSampleIndex,
                     GPASample* pSample,
                     const std::vector<CounterIndex>* pCounterList) override;

    /// \copydoc IGPACommandList::GetLastSample()
    GPASample* GetLastSample() const override;

    /// \copydoc IGPACommandList::CloseLastSample()
    bool CloseLastSample(bool closingByClient) override;

    /// \copydoc IGPACommandList::IsLastSampleClosed()
    bool IsLastSampleClosed() const override;

    /// \copydoc IGPACommandList::IsComplete()
    bool IsComplete() const override;

    /// \copydoc IGPACommandList::GetCmdType()
    GPA_Command_List_Type GetCmdType() const override;

    /// \copydoc IGPAInterfaceTrait::ObjectType()
    GPAObjectType ObjectType() const override;

private:

    IGPASession*            m_pGpaSession;                 ///< GPA session
    GPAPass*                m_pGpaPass;                    ///< GPA Pass
    GPASample*              m_pLastSample;                 ///< the current open sample on this command list
    bool                    m_isCmdRunning;                ///< flag indicating if the command list is running or not
};

#endif // _GPA_COMMAND_LIST_H_
