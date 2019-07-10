//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GPA Command List Declarations
//==============================================================================

#ifndef _GPA_COMMAND_LIST_H_
#define _GPA_COMMAND_LIST_H_

#include <unordered_map>

// GPA Common
#include "IGPACommandList.h"
#include "GPASample.h"

using ClientSampleIdGpaSamplePair = std::pair<ClientSampleId, GPASample*>;  ///< type alias for pair of client sample id and GPA sample object pointer
using ClientSampleIdGpaSampleUnorderedMap =
    std::unordered_map<ClientSampleId, GPASample*>;  ///< type alias for map of client sample id and GPA sample object pointer

/// Class for GPA Command List
class GPACommandList : public IGPACommandList
{
public:
    /// Constructor
    /// \param[in] pGpaSession GPA session pointer
    /// \param[in] pGpaPass pass object pointer
    /// \param[in] commandListId command list id
    /// \param[in] commandListType GPA command list type
    GPACommandList(IGPASession* pGpaSession, GPAPass* pGpaPass, CommandListId commandListId, GPA_Command_List_Type commandListType = GPA_COMMAND_LIST_NONE);

    /// Delete default constructor
    GPACommandList() = delete;

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
    bool BeginSample(ClientSampleId clientSampleIndex, GPASample* pSample) override;

    /// \copydoc IGPACommandList::GetLastSample()
    GPASample* GetLastSample() const override;

    /// \copydoc IGPACommandList::GetSample()
    GPASample* GetSample(ClientSampleId clientSampleId) const override;

    /// \copydoc IGPACommandList::CloseLastSample()
    bool CloseLastSample(bool closingByClient) override;

    /// \copydoc IGPACommandList::IsLastSampleClosed()
    bool IsLastSampleClosed() const override;

    /// \copydoc IGPACommandList::IsResultReady()
    bool IsResultReady() const override;

    /// \copydoc IGPACommandList::GetCmdType()
    GPA_Command_List_Type GetCmdType() const override;

    /// \copydoc IGPAInterfaceTrait::ObjectType()
    GPAObjectType ObjectType() const override;

    /// Returns the command lsit id
    /// \return command list id
    CommandListId GetId() const;

    /// Iterate over all the samples in the command list
    /// \param[in] function function to be executed for each object in the list - function may return false to terminate iteration
    void IterateSampleUnorderedMap(std::function<bool(ClientSampleIdGpaSamplePair)> function) const;

private:
    /// Begin API specific command list
    /// \return true if successful otherwise false
    virtual bool BeginCommandListRequest() = 0;

    /// End API specific command list
    /// \return true if successful otherwise false
    virtual bool EndCommandListRequest() = 0;

    /// Begins the sample on the command list
    /// \param[in] clientSampleId index of the sample
    /// \param[in] pGpaSample The sample to start
    /// \return true if sample was successfully begun, false otherwise
    virtual bool BeginSampleRequest(ClientSampleId clientSampleId, GPASample* pGpaSample) = 0;

    /// Closes the most recent sample
    /// \return true if most recent sample was closed, false otherwise
    virtual bool CloseLastSampleRequest() = 0;

    /// Add the sample to the command list
    /// \param[in] clientSampleId sample id of the sample
    /// \param[in] pGpaSample The sample to start
    void AddSample(ClientSampleId clientSampleId, GPASample* pGpaSample);

    /// Enum for the state of command list
    enum class CommandListState
    {
        UNDEFINED,               ///< Undefined state
        SAMPLE_RECORDING_BEGIN,  ///< command list is ready to add samples
        SAMPLE_RECORDING_END,    ///< command List is closed for adding samples
    };

    mutable std::mutex                  m_cmdListMutex;                         ///< Mutex for command list object
    IGPASession*                        m_pGpaSession;                          ///< GPA session
    GPAPass*                            m_pGpaPass;                             ///< GPA Pass
    GPASample*                          m_pLastSample;                          ///< the current open sample on this command list
    CommandListState                    m_commandListState;                     ///< command list state
    ClientSampleIdGpaSampleUnorderedMap m_clientSampleIdGpaSampleUnorderedMap;  ///< Unordered Map of client sample id and GPA sample object
    GPA_Command_List_Type               m_commandListType;                      ///< GPA Command List type
    CommandListId                       m_commandListId;                        ///< command list id
};

#endif  // _GPA_COMMAND_LIST_H_
