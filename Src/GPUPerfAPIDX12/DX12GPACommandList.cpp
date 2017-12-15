//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief DX12 GPA Command List Implementation
//==============================================================================

#include <cassert>

#include "DX12GPACommandList.h"
#include "GPACommonDefs.h"
#include "DX12Utils.h"
#include "DX12GPASession.h"
#include "DX12GPAContext.h"
#include "Logging.h"
#include "DX12GPAPass.h"


DX12GPASession* DX12GPACommandList::GetSession() const
{
    return m_pDX12GpaSession;
}

DX12GPACommandList::DX12GPACommandList(DX12GPASession* pDX12Gpasession,
                               GPAPass* passObject,
                               void* pCmd,
                               GPA_Command_List_Type cmdType)
{
    m_pCmdList = reinterpret_cast<ID3D12GraphicsCommandList*>(pCmd);
    unsigned int refCount = m_pCmdList->AddRef();
    UNREFERENCED_PARAMETER(refCount);
    m_gpaCommandListType = cmdType;
    m_pDX12GpaSession = pDX12Gpasession;
    m_commandListState = CommandListState::UNDEFINED;
    m_pDX12GpaPass = reinterpret_cast<DX12GPAPass*>(passObject);
    m_cmdSampleStatus = CmdSampleStatus::SAMPLE_END;
    m_pAmdExtSession = nullptr;
    m_currentDriverSampleId = NULL;
    m_isCommandListOpen = false;
    m_isNonGPAResourceReleased = false;
    m_lastOpenedClientSampleId = 0u;
}

DX12GPACommandList::~DX12GPACommandList()
{
    ReleaseNonGPAResources();
}

IGPASession* DX12GPACommandList::GetParentSession() const
{
    return m_pDX12GpaSession;
}

bool DX12GPACommandList::Begin()
{
    if (CommandListState::UNDEFINED == m_commandListState)
    {
        // TODO: Merge http://git.amd.com:8080/#/c/106405/ - workaround for driver bug
        // where if no sample is added on a command list, driver check for data never to return true.

        /*if (S_OK == GetAmdExtSession()->Begin(m_pCmdList))
        {*/
        m_commandListState = CommandListState::SAMPLE_RECORDING_BEGIN;
        return true;
        //}

        /* GPA_LogDebugError("AMD extension is unable to begin the command list.");
         return false;*/
    }

    GPA_LogError("CommandList already started.");
    return false;
}

bool DX12GPACommandList::End()
{
    bool isSucceed = false;

    if (CommandListState::UNDEFINED == m_commandListState)
    {
        GPA_LogDebugError("Command list is not yet opened for sampling.");
    }
    else if (CommandListState::SAMPLE_RECORDING_END == m_commandListState)
    {
        GPA_LogError("Command List already ended.");
    }
    else if (CommandListState::SAMPLE_RECORDING_BEGIN == m_commandListState)
    {
        // Close any outstanding opened sample and mark it as candidate for continuation
        if (CmdSampleStatus::SAMPLE_END != m_cmdSampleStatus)
        {
            CloseLastSample(false);
        }

        // TODO: Merge http://git.amd.com:8080/#/c/106405/ - workaround for driver bug
        // where if no sample is added on a command list, driver check for data never to return true.
        if (m_isCommandListOpen)
        {
            HRESULT status = m_pAmdExtSession->End(m_pCmdList);
            if (S_OK == status)
            {
                m_commandListState = CommandListState::SAMPLE_RECORDING_END;
                isSucceed = true;
                m_isCommandListOpen = false;
            }
        }
        else
        {
            GPA_LogDebugError("AMD extension is unable to end the command list.");
        }
    }

    return isSucceed;
}

bool DX12GPACommandList::IsCommandListRunning() const
{
    return m_commandListState == CommandListState::SAMPLE_RECORDING_BEGIN;
}

GPAPass* DX12GPACommandList::GetPass() const
{
    return m_pDX12GpaPass;
}

gpa_uint32 DX12GPACommandList::GetSampleCount() const
{
    return static_cast<gpa_uint32>(m_clientSampleIdGPASampleObjectMap.size());
}

bool DX12GPACommandList::BeginSample(ClientSampleId clientSampleIndex, GPASample* pSample, const std::vector<CounterIndex>* pCounterList)
{
    bool succeeded = false;

    if (CommandListState::SAMPLE_RECORDING_BEGIN != m_commandListState)
    {
        GPA_LogError("Command list must be in recording state to start/end a sample.");
    }
    else if (CmdSampleStatus::SAMPLE_END != m_cmdSampleStatus)
    {
        GPA_LogError("Previous sample must be ended before starting a new one.");
    }
    else if (DoesSampleExist(clientSampleIndex))
    {
        GPA_LogError("Sample Id already exists.");
    }
    m_cmdSampleStatus = CmdSampleStatus::SAMPLE_BEGIN;

    DriverSampleId driverSampleId = 0;

    if (GPACounterSource::HARDWARE == m_pDX12GpaPass->GetCounterSource())
    {
        if (OpenHwSample(clientSampleIndex, &driverSampleId))
        {
            succeeded = pSample->Begin(this->m_pDX12GpaSession->GetParentContext(), pCounterList);
        }
    }
    else if (GPACounterSource::SOFTWARE == m_pDX12GpaPass->GetCounterSource())
    {
        if (OpenSwSample(clientSampleIndex, &driverSampleId))
        {
            succeeded = pSample->Begin(this->m_pDX12GpaSession->GetParentContext(), pCounterList);
        }
    }

    if (succeeded)
    {
        pSample->SetDriverSampleId(driverSampleId);
        m_lastOpenedClientSampleId = clientSampleIndex;
        m_currentDriverSampleId = driverSampleId;
    }
    else
    {
        GPA_LogError("Unable to begin sample in command list.");
    }

    return succeeded;
}

GPASample* DX12GPACommandList::GetLastSample() const
{
    GPASample* pRetSample = nullptr;

    if (DoesSampleExist(m_lastOpenedClientSampleId))
    {
        pRetSample = m_clientSampleIdGPASampleObjectMap.at(m_lastOpenedClientSampleId);
    }

    return pRetSample;
}

bool DX12GPACommandList::CloseLastSample(bool closingByClient)
{
    bool succeeded = false;

    if (CommandListState::SAMPLE_RECORDING_BEGIN != m_commandListState)
    {
        GPA_LogError("Command list must be in recording state to start/end a sample.");
    }
    else if (CmdSampleStatus::SAMPLE_BEGIN != m_cmdSampleStatus)
    {
        GPA_LogError("Sample must be started before ending one.");
    }
    else if (!DoesSampleExist(m_lastOpenedClientSampleId))
    {
        GPA_LogError("Sample has not been added to the list.");
    }
    else
    {
        if (closingByClient)
        {
            m_clientSampleIdGPASampleObjectMap[m_lastOpenedClientSampleId]->SetAsClosedByClient();
        }

        if (GPACounterSource::HARDWARE == m_pDX12GpaPass->GetCounterSource())
        {
            CloseHwSample();
        }
        else if (GPACounterSource::SOFTWARE == m_pDX12GpaPass->GetCounterSource())
        {
            CloseSwSample();
        }

        m_cmdSampleStatus = CmdSampleStatus::SAMPLE_END;
        succeeded = true;
    }

    return succeeded;
}

bool DX12GPACommandList::IsLastSampleClosed() const
{
    return CmdSampleStatus::SAMPLE_END == m_cmdSampleStatus;
}

bool DX12GPACommandList::IsComplete() const
{
    bool isComplete = true;

    isComplete = m_pAmdExtSession->IsReady();

    for(auto bundleIter = m_secondarySampleAmdExtSessionMap.cbegin();
        bundleIter != m_secondarySampleAmdExtSessionMap.cend();
        ++bundleIter)
    {
        isComplete &= bundleIter->first->IsReady();
    }

    return isComplete;
}

GPA_Command_List_Type DX12GPACommandList::GetCmdType() const
{
    return m_gpaCommandListType;
}

GPA_API_Type DX12GPACommandList::GetAPIType() const
{
    return GPA_API_DIRECTX_12;
}

GPAObjectType DX12GPACommandList::ObjectType() const
{
    return GPAObjectType::GPA_OBJECT_TYPE_COMMAND_LIST;
}

DX12GPASample* DX12GPACommandList::GetSample(ClientSampleId clientSampleId) const
{
    DX12GPASample* pRetDx12GpaSample = nullptr;

    ClientSampleIdGPASampleObjectMap::const_iterator iter = m_clientSampleIdGPASampleObjectMap.find(clientSampleId);

    if(iter != m_clientSampleIdGPASampleObjectMap.end())
    {
        pRetDx12GpaSample = iter->second;
    }

    return pRetDx12GpaSample;
}

ID3D12GraphicsCommandList* DX12GPACommandList::GetCmdList() const
{
    return m_pCmdList;
}

bool DX12GPACommandList::CopyBundleSamples(std::vector<ClientSampleId> clientSampleIds,
                                           SecondaryDx12Cmd* pDx12SecondaryCmd,
                                           std::vector<ClientSampleId>& originalClientSampleIds)
{
    bool success = false;

    if (this->m_gpaCommandListType == GPA_COMMAND_LIST_PRIMARY &&
        nullptr == GetBundleResultAmdExtSession(clientSampleIds.at(0)))     ///< This should always return nullptr because you've already confirmed that the new clientSampleIds are unique. Therefore this code could be removed.
    {
        IAmdExtGpaSession* pCopyAmdExtGpaSession = m_pDX12GpaSession->GetAmdExtInterface()->CopyGpaSession(
            pDx12SecondaryCmd->GetAmdExtSession());

        HRESULT status = S_OK;

        // TODO: Merge http://git.amd.com:8080/#/c/106405/ - workaround for driver bug
        // where if no sample is added on a command list, driver check for data never to return true.
        if (!m_isCommandListOpen)
        {
            if (nullptr == m_pAmdExtSession)
            {
                m_pAmdExtSession = m_pDX12GpaSession->GetAmdExtInterface()->CreateGpaSession();
                m_pAmdExtSession->AddRef();
            }

            status = m_pAmdExtSession->Begin(m_pCmdList);

            if (S_OK == status)
            {
                m_isCommandListOpen = true;
            }
        }

        pCopyAmdExtGpaSession->CopyResults(m_pCmdList);
        BundleSamplesOnPrimaryCmd bundleSamplesOnPrimaryCmd(clientSampleIds.begin(), clientSampleIds.end());
        m_secondarySampleAmdExtSessionMap.insert(
            BundleResultAmdExtSessionBundleSamplesOnPrimaryCmdPair(
                pCopyAmdExtGpaSession, bundleSamplesOnPrimaryCmd));
        // holding a reference
        pCopyAmdExtGpaSession->AddRef();

        for(auto constIter = pDx12SecondaryCmd->m_clientSampleIdGPASampleObjectMap.cbegin();
              constIter != pDx12SecondaryCmd->m_clientSampleIdGPASampleObjectMap.cend(); ++constIter)
        {
            originalClientSampleIds.push_back(constIter->first);
        }

        success = true;
    }
    else
    {
        GPA_LogError("Unable to copy bundle samples. Copying is only supported on primary command lists for samples that do not already exist.");
    }

    return success;
}

IAmdExtGpaSession* DX12GPACommandList::GetAmdExtSession() const
{
    return m_pAmdExtSession;
}

IAmdExtGpaSession* DX12GPACommandList::GetBundleResultAmdExtSession(ClientSampleId clientSampleId) const
{
    bool sampleFound = false;
    IAmdExtGpaSession* pBundleResultExtSession = nullptr;

    for (auto iter = m_secondarySampleAmdExtSessionMap.cbegin();
         iter != m_secondarySampleAmdExtSessionMap.cend() && !sampleFound; ++iter)
    {
        if (iter->second.find(clientSampleId) != iter->second.end())
        {
            // Search the client sample id in each set
            pBundleResultExtSession = iter->first;
            sampleFound = true;
        }
    }

    return pBundleResultExtSession;
}


bool DX12GPACommandList::DoesSampleExist(ClientSampleId clientSampleId) const
{
    std::lock_guard<std::mutex> lock(m_cmdListMutex);
    bool exists = false;

    if (m_clientSampleIdGPASampleObjectMap.find(clientSampleId) != m_clientSampleIdGPASampleObjectMap.end())
    {
        exists = true;
    }

    return exists;
}


bool DX12GPACommandList::OpenHwSample(ClientSampleId clientSampleIndex, DriverSampleId* pDriverSampleIndex)
{
    UNREFERENCED_PARAMETER(clientSampleIndex);
    bool success = false;

    if (nullptr != pDriverSampleIndex)
    {
        HRESULT status = S_OK;

        std::lock_guard<std::mutex> lock(m_cmdListMutex);

        // TODO: Merge http://git.amd.com:8080/#/c/106405/ - workaround for driver bug
        // where if no sample is added on a command list, driver check for data never to return true.
        if (!m_isCommandListOpen)
        {
            if(nullptr == m_pAmdExtSession)
            {
                m_pAmdExtSession = m_pDX12GpaSession->GetAmdExtInterface()->CreateGpaSession();
                m_pAmdExtSession->AddRef();
            }

            status = m_pAmdExtSession->Begin(m_pCmdList);

            if (S_OK == status)
            {
                m_isCommandListOpen = true;
            }
        }

        if (S_OK == status)
        {
            *pDriverSampleIndex = m_pAmdExtSession->BeginSample(m_pCmdList, m_pDX12GpaPass->GetAmdExtSampleConfig());

        }

        success = true;
    }

    return success;
}

bool DX12GPACommandList::OpenSwSample(ClientSampleId clientSampleIndex, DriverSampleId* pDriverSampleIndex)
{
    // TODO: Come back when we are implementing software counters
    GPA_FUNCTION_NOT_IMPLEMENTED;
    UNREFERENCED_PARAMETER(clientSampleIndex);
    UNREFERENCED_PARAMETER(pDriverSampleIndex);
    return true;
}

void DX12GPACommandList::CloseHwSample() const
{
    m_pAmdExtSession->EndSample(m_pCmdList, m_currentDriverSampleId);
}

bool DX12GPACommandList::CloseSwSample()
{
    // TODO: Come back when we are implementing software counters
    GPA_FUNCTION_NOT_IMPLEMENTED;
    return true;
}


GPA_THREAD_SAFE_FUNCTION bool DX12GPACommandList::AddGpaSample(DX12GPASample* pdx12GpaSample)
{
    bool success = false;
    ClientSampleId clientSampleId = pdx12GpaSample->GetClientSampleId();
    if (!DoesSampleExist(clientSampleId) && nullptr != pdx12GpaSample)
    {
        std::lock_guard<std::mutex> lockCmdList(m_cmdListMutex);
        m_clientSampleIdGPASampleObjectMap.insert(
            ClientSampleIdGPASampleObjectPair(clientSampleId, pdx12GpaSample));
        success = true;
    }

    return success;
}

void DX12GPACommandList::ReleaseNonGPAResources()
{
    if (false == m_isNonGPAResourceReleased)
    {
        unsigned int refCount = m_pCmdList->Release();
        UNREFERENCED_PARAMETER(refCount);
        m_pCmdList = nullptr;
        m_isNonGPAResourceReleased = true;
        m_pAmdExtSession->Release();
        for(auto iter = m_secondarySampleAmdExtSessionMap.begin();
            iter != m_secondarySampleAmdExtSessionMap.end(); ++iter)
        {
            iter->first->Release();
        }
    }
}
