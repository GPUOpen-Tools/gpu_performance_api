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
#pragma warning(push)
#pragma warning(disable : 4201)
#include <AmdExtGpaInterfaceApi.h>
#pragma warning(pop)

// GPA Common
#include "GPACommandList.h"
#include "GPASample.h"
#include "DX12GPAPass.h"
#include "GPACommonDefs.h"

class DX12GPASession;  // forward declaration

using SampleResultSize = gpa_uint64;  ///< type alias for size of sample result
using SampleResult     = gpa_uint64;  ///< type alias for sample result

/// Class for DX12 GPA Command List
class GPA_NOT_THREAD_SAFE_OBJECT DX12GPACommandList : public GPACommandList
{
public:
    using BundleResultAmdExtSession = IAmdExtGpaSession*;  ///< type alias for bundle result session
    using SecondaryDx12Cmd          = DX12GPACommandList;  ///< type alias for secondary dx12 command list

    /// Constructor
    /// \param[in] pDX12GpaSession dx12 GPA session
    /// \param[in] pDX12GpaPass pass object pointer
    /// \param[in] pCmd command list pointer
    /// \param[in] commandListId command list id
    /// \param[in] cmdType command list type
    DX12GPACommandList(DX12GPASession* pDX12GpaSession, GPAPass* pDX12GpaPass, void* pCmd, CommandListId commandListId, GPA_Command_List_Type cmdType);

    /// Delete default constructor
    DX12GPACommandList() = delete;

    /// Destructor
    ~DX12GPACommandList();

    /// \copydoc IGPACommandList::IsResultReady()
    bool IsResultReady() const override;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

    /// Get the ID3D12GraphicsCommandList
    /// \return ID3D12GraphicsCommandList pointer
    ID3D12GraphicsCommandList* GetCmdList() const;

    /// Copies the bundle session result from the primary command list
    /// \param[in] clientSampleIds client sample id
    /// \param[in] pDx12SecondaryCmd DirectX 12 GPA secondary command list object pointer
    /// \param[out] originalClientSampleIds list of original client sample ids created on secondary command list
    /// \return true upon successful operation otherwise false
    bool CopyBundleSamples(std::vector<ClientSampleId>  clientSampleIds,
                           SecondaryDx12Cmd*            pDx12SecondaryCmd,
                           std::vector<ClientSampleId>& originalClientSampleIds);

    /// Returns the command list GPA extension session
    /// \return DirectX 12 AMD GPA extension session
    IAmdExtGpaSession* GetAmdExtSession() const;

    /// Returns the bundle result GPA extension session for the given sample id
    /// \param[in] clientSampleId client sample id
    /// \return DirectX 12 AMD GPA extension session
    IAmdExtGpaSession* GetBundleResultAmdExtSession(ClientSampleId clientSampleId) const;

    /// Release the graphics command list
    void ReleaseNonGPAResources();

private:
    /// \copydoc GPACommandList::BeginCommandListRequest()
    bool BeginCommandListRequest() override final;

    /// \copydoc GPACommandList::EndCommandListRequest()
    bool EndCommandListRequest() override final;

    /// \copydoc GPACommandList::BeginSampleRequest()
    bool BeginSampleRequest(ClientSampleId clientSampleId, GPASample* pGpaSample) override final;

    /// \copydoc GPACommandList::CloseLastSampleRequest()
    bool CloseLastSampleRequest() override final;

    /// Creates a hardware sample
    /// \param[in] clientSampleId client sample id
    /// \param[out] pDriverSampleId pointer to write the driver generated sample id
    /// \return true upon successful operation otherwise false
    bool OpenHwSample(ClientSampleId clientSampleId, DriverSampleId* pDriverSampleId) const;

    /// Creates a hardware sample
    /// \param[in] clientSampleId client sample id
    /// \param[out] pDriverSampleId pointer to write the driver generated sample id
    /// \return true upon successful operation otherwise false
    bool OpenSwSample(ClientSampleId clientSampleId, DriverSampleId* pDriverSampleId = nullptr) const;

    /// Closes the previously opened hardware sample
    /// \return true upon successful operation otherwise false
    bool CloseHwSample() const;

    /// Closes the previously opened software sample
    /// \return true upon successful operation otherwise false
    bool CloseSwSample();

    using BundleSamplesOnPrimaryCmd = std::unordered_set<ClientSampleId>;  ///< type alias for set of client sample id for bundle samples
    using BundleResultAmdExtSessionBundleSamplesOnPrimaryCmdPair =
        std::pair<BundleResultAmdExtSession, BundleSamplesOnPrimaryCmd>;  ///< type alias for pair of bundle result session and set of bundle samples
    using BundleResultAmdExtSessionBundleSamplesOnPrimaryCmdMap =
        std::map<BundleResultAmdExtSession, BundleSamplesOnPrimaryCmd>;  ///< type alias for map of bundle result session and set of bundle samples

    std::mutex                 m_dx12CmdListMutex;  ///< Mutex for DX12 Cmd List object
    ID3D12GraphicsCommandList* m_pCmdList;          ///< Command List

    IAmdExtGpaSession* m_pAmdExtSession;  ///< Amd Ext Gpa session
    BundleResultAmdExtSessionBundleSamplesOnPrimaryCmdMap
         m_secondarySampleAmdExtSessionMap;  ///< Map of bundle result session and client sample id - usage only applicable if the cmd is primary
    bool m_isCommandListOpenInDriver;        ///< Flag indicating if the command list has been started in the driver (i.e. if it is in a recording state)
    bool m_isNonGPAResourceReleased;         ///< flag indicating ID3DGraphicsCommand list has been released or not
    bool m_hasAnyHardwareCounters;           ///< flag indicating if there are any non-skipped hardware counters in this request
    bool m_usePre1850Config;                 ///< flag indicating whether to use pre-18.50 configuration
};

#endif  // _DX12_GPA_COMMAND_LIST_H_