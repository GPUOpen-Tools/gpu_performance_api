//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief DX12 GPA Command List Declarations
//==============================================================================

#ifndef _DX12_GPA_COMMAND_LIST_H_
#define _DX12_GPA_COMMAND_LIST_H_

// std
#include <map>
#include <unordered_set>

// DirectX 12
#include <d3d12.h>

// AMD Extension
#pragma warning (push)
#pragma warning (disable: 4201)
#include <AmdExtGpaInterfaceApi.h>
#pragma warning (pop)

// GPA Common
#include "IGPACommandList.h"
#include "GPASample.h"
#include "DX12GPAPass.h"
#include "DX12GPASample.h"
#include "GPACommonDefs.h"

class DX12GPASession;   // forward declaration

using ClientSampleIdGPASampleObjectPair = std::pair<ClientSampleId, DX12GPASample*>;    ///< type alias for pair of client sample id and dx12gpasample object pointer
using ClientSampleIdGPASampleObjectMap = std::map<ClientSampleId, DX12GPASample*>;      ///< type alias for map of client sample id and dx12gpasample object pointer
using SampleResultSize = gpa_uint64;                                                    ///< type alias for size of sample result
using SampleResult = gpa_uint64;                                                        ///< type alias for sample result

/// Class for DX12 GPA Command List
class GPA_NOT_THREAD_SAFE_OBJECT DX12GPACommandList : public IGPACommandList
{
public:

    using BundleResultAmdExtSession = IAmdExtGpaSession*;           ///< type alias for bundle result session
    using SecondaryDx12Cmd = DX12GPACommandList;                        ///< type alias for secondary dx12 command list

    /// Returns the associated session
    /// \return DX12 GPA Session Object
    DX12GPASession* GetSession() const;

    /// Constructor
    DX12GPACommandList() = delete;

    /// Constructor
    /// \param[in] pDX12GpaSession dx12 GPA session
    /// \param[in] pPass pass object pointer
    /// \param[in] pCmd command list pointer
    /// \param[in] cmdType commnad list type
    DX12GPACommandList(DX12GPASession* pDX12GpaSession,
                       GPAPass* pPass,
                       void* pCmd,
                       GPA_Command_List_Type cmdType);

    /// Destructor
    ~DX12GPACommandList();

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
    virtual bool BeginSample(ClientSampleId clientSampleIndex, GPASample* pSample, const std::vector<CounterIndex>* pCounterList) override;

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

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

    /// \copydoc IGPAInterfaceTrait::ObjectType()
    GPAObjectType ObjectType() const override;

    /// Returns the sample with given client sample id if it exists otherwise nullptr
    /// \param[in] clientSampleId client sample id
    /// \return dx12 gpa sample if found otherwise nullptr
    DX12GPASample* GetSample(ClientSampleId clientSampleId) const;

    /// Get the ID3D12GraphicsCommandList
    /// \return ID3D12GraphicsCommandList pointer
    ID3D12GraphicsCommandList* GetCmdList() const;

    /// Copies the bundle session result from the primary command list
    /// \param[in] clientSampleIds client sample id
    /// \param[in] pDx12SecondaryCmd DirectX 12 GPA secondary command list object pointer
    /// \param[out] originalClientSampleIds list of original client sample ids created on secondary command list
    /// \return true upon successful operation otherwise false
    bool CopyBundleSamples(std::vector<ClientSampleId> clientSampleIds,
                           SecondaryDx12Cmd* pDx12SecondaryCmd,
                           std::vector<ClientSampleId>& originalClientSampleIds);

    /// Returns the command list GPA extension session
    /// \return DirectX 12 AMD GPA extension session
    IAmdExtGpaSession* GetAmdExtSession() const;

    /// Returns the bundle result GPA extension session for the given sample id
    /// \param[in] clientSampleId client sample id
    /// \return DirectX 12 AMD GPA extension session
    IAmdExtGpaSession* GetBundleResultAmdExtSession(ClientSampleId clientSampleId) const;

    /// Checks to see if the supplied ClientSampleId has been opened on this command list.
    /// \param clientSampleId A user-supplied sampleId
    /// \return True if the sample has been opened; False otherwise
    bool DoesSampleExist(ClientSampleId clientSampleId) const;

    /// Release the graphics command list
    void ReleaseNonGPAResources();

    /// Adds the GPA Sample Object to the command list
    /// \param[in] pdx12GpaSample pointer to the Dx12 GPA Sample
    /// \return true if operation is successful otherwise false
    GPA_THREAD_SAFE_FUNCTION bool AddGpaSample(DX12GPASample* pdx12GpaSample);

private:

    /// Creates a hardware sample
    /// \param[in] clientSampleId client sample id
    /// \param[out] pDriverSampleId pointer to write the driver generated sample id
    /// \return true upon successful operation otherwise false
    bool OpenHwSample(ClientSampleId clientSampleId, DriverSampleId* pDriverSampleId);

    /// Creates a hardware sample
    /// \param[in] clientSampleId client sample id
    /// \param[out] pDriverSampleId pointer to write the driver generated sample id
    /// \return true upon successful operation otherwise false
    bool OpenSwSample(ClientSampleId clientSampleId, DriverSampleId* pDriverSampleId = nullptr);

    /// Closes the previously opened hardware sample
    void CloseHwSample() const;

    /// Closes the previously opened software sample
    bool CloseSwSample();

    /// Enums for the state of command list
    enum class CommandListState
    {
        UNDEFINED,                          ///< Undefined state
        SAMPLE_RECORDING_BEGIN,             ///< command list is ready to add samples
        SAMPLE_RECORDING_END,               ///< Command List is closed for adding samples
    };

    /// Enums for the state of the sample
    enum class CmdSampleStatus
    {
        SAMPLE_BEGIN,               ///< sample has started on a command list
        SAMPLE_END                  ///< sample has ended on a command list
    };

    using BundleSamplesOnPrimaryCmd = std::unordered_set<ClientSampleId>;                                                               ///< type alias for set of client sample id for bundle samples
    using BundleResultAmdExtSessionBundleSamplesOnPrimaryCmdPair = std::pair<BundleResultAmdExtSession, BundleSamplesOnPrimaryCmd>;     ///< type alias for pair of bundle result session and set of bundle samples
    using BundleResultAmdExtSessionBundleSamplesOnPrimaryCmdMap = std::map<BundleResultAmdExtSession, BundleSamplesOnPrimaryCmd>;       ///< type alias for map of bundle result session and set of bundle samples

    mutable std::mutex                                      m_cmdListMutex;                             ///< Mutex for DX12 Cmd List object
    ID3D12GraphicsCommandList*                              m_pCmdList;                                 ///< Command List
    GPA_Command_List_Type                                   m_gpaCommandListType;                       ///< GPA Command List type
    DX12GPAPass*                                            m_pDX12GpaPass;                             ///< GPA Pass Object
    DX12GPASession*                                         m_pDX12GpaSession;                          ///< DX12 GPA Session
    CommandListState                                        m_commandListState;                         ///< command list state
    CmdSampleStatus                                         m_cmdSampleStatus;                          ///< command list sample state
    DriverSampleId                                          m_currentDriverSampleId;                    ///< Current driver created sample index
    ClientSampleId                                          m_lastOpenedClientSampleId;                 ///< Current client created sample index
    IAmdExtGpaSession*                                      m_pAmdExtSession;                           ///< Amd Ext Gpa session
    BundleResultAmdExtSessionBundleSamplesOnPrimaryCmdMap   m_secondarySampleAmdExtSessionMap;          ///< Map of bundle result session and client sample id - usage only applicable if the cmd is primary
    ClientSampleIdGPASampleObjectMap                        m_clientSampleIdGPASampleObjectMap;         ///< Map of client sample id and Gpa sample object
    mutable bool                                            m_isCommandListOpen;                        ///< Flag indicating any sample has begun or not on the command list.
                                                                                                        ///  This is a workaround for merging http://git.amd.com:8080/#/c/106405/
    bool                                                    m_isNonGPAResourceReleased;                 ///< flag indicating ID3DGraphicsCommand list has been released or not
};

#endif // _DX12_GPA_COMMAND_LIST_H_