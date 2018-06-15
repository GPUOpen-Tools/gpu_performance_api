//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief DX12 GPA Command List Implementation
//==============================================================================

#include "DX12GPACommandList.h"
#include "GPACommonDefs.h"
#include "DX12Utils.h"
#include "DX12GPASession.h"
#include "DX12GPAContext.h"
#include "Logging.h"
#include "DX12GPAPass.h"

static const UINT32 S_INVALID_SAMPLE_INDEX = static_cast<UINT32>(-1); ///< Invalid sample index

DX12GPACommandList::DX12GPACommandList(DX12GPASession* pDX12GpaSession,
                                       GPAPass* pDX12GpaPass,
                                       void* pCmd,
                                       CommandListId commandListId,
                                       GPA_Command_List_Type cmdType):
    GPACommandList(pDX12GpaSession, pDX12GpaPass, commandListId, cmdType)
{
    m_pCmdList = reinterpret_cast<ID3D12GraphicsCommandList*>(pCmd);
    unsigned int refCount = m_pCmdList->AddRef();
    UNREFERENCED_PARAMETER(refCount);
    m_pAmdExtSession = nullptr;
    m_isCommandListOpenInDriver = false;
    m_isNonGPAResourceReleased = false;

    // Hardware counters are requested from the client even though it is not available in the driver
    m_hasAnyHardwareCounters = pDX12GpaPass->GetEnabledCounterCount() > 0;
}

DX12GPACommandList::~DX12GPACommandList()
{
    ReleaseNonGPAResources();
}

bool DX12GPACommandList::BeginCommandListRequest()
{
    std::lock_guard<std::mutex> lock(m_dx12CmdListMutex);
    bool success = false;

    if (!m_isCommandListOpenInDriver)
    {
        if (nullptr == m_pAmdExtSession)
        {
            DX12GPASession* pDx12GpaSession = reinterpret_cast<DX12GPASession*>(GetParentSession());
            m_pAmdExtSession = pDx12GpaSession->GetAmdExtInterface()->CreateGpaSession();
            m_pAmdExtSession->AddRef(); // Holding a reference is not required here, but we are doing so in order to work around an issue in older drivers
        }

        HRESULT extensionOpResult = m_pAmdExtSession->Begin(m_pCmdList);
        success = S_OK == extensionOpResult;

        if (!success)
        {
            GPA_LogError("The driver extension is unable to begin the command list.");
        }
        else
        {
            m_isCommandListOpenInDriver = true;
        }
    }
    else
    {
        GPA_LogError("The command list has already been started.");
    }

    return success;
}

bool DX12GPACommandList::EndCommandListRequest()
{
    std::lock_guard<std::mutex> lock(m_dx12CmdListMutex);
    bool success = false;

    if (m_isCommandListOpenInDriver)
    {
        HRESULT status = m_pAmdExtSession->End(m_pCmdList);

        if (S_OK == status)
        {
            success = true;
            m_isCommandListOpenInDriver = false;
        }
        else
        {
            GPA_LogError("The driver extension is unable to end the command list. This can occur if GPA_EndCommandList is called after the command list has been closed.");
        }
    }
    else
    {
        GPA_LogError("The command list has not been started.");
    }

    return success;
}

bool DX12GPACommandList::BeginSampleRequest(ClientSampleId clientSampleId, GPASample* pGpaSample)
{
    bool success = false;

    DriverSampleId driverSampleId = 0;
    GPACounterSource counterSource = GetPass()->GetCounterSource();

    if (GPACounterSource::HARDWARE == counterSource)
    {
        if (OpenHwSample(clientSampleId, &driverSampleId))
        {
            success = true;
        }
    }
    else if (GPACounterSource::SOFTWARE == counterSource)
    {
        if (OpenSwSample(clientSampleId, &driverSampleId))
        {
            success = true;
        }
    }

    if (success)
    {
        pGpaSample->SetDriverSampleId(driverSampleId);
    }
    else
    {
        GPA_LogError("Unable to begin sample in command list.");
    }

    return success;
}

bool DX12GPACommandList::CloseLastSampleRequest()
{
    GPACounterSource counterSource = GetPass()->GetCounterSource();

    if (GPACounterSource::HARDWARE == counterSource)
    {
        CloseHwSample();
    }
    else if (GPACounterSource::SOFTWARE == counterSource)
    {
        CloseSwSample();
    }

    return true;
}

bool DX12GPACommandList::IsResultReady() const
{
    bool isResultReady = true;

    isResultReady = m_pAmdExtSession->IsReady();

    for (auto bundleIter = m_secondarySampleAmdExtSessionMap.cbegin();
         bundleIter != m_secondarySampleAmdExtSessionMap.cend();
         ++bundleIter)
    {
        isResultReady &= bundleIter->first->IsReady();
    }

    return isResultReady;
}

GPA_API_Type DX12GPACommandList::GetAPIType() const
{
    return GPA_API_DIRECTX_12;
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

    if (GPA_COMMAND_LIST_PRIMARY == GetCmdType() &&
        nullptr == GetBundleResultAmdExtSession(clientSampleIds.at(0)))     ///TODO: This should always return nullptr because you've already confirmed that the new clientSampleIds are unique. Therefore this code could be removed.
    {
        DX12GPASession* pDx12GpaSession = reinterpret_cast<DX12GPASession*>(GetParentSession());
        IAmdExtGpaSession* pCopyAmdExtGpaSession = pDx12GpaSession->GetAmdExtInterface()->CopyGpaSession(
                                                       pDx12SecondaryCmd->GetAmdExtSession());

        pCopyAmdExtGpaSession->CopyResults(m_pCmdList);
        BundleSamplesOnPrimaryCmd bundleSamplesOnPrimaryCmd(clientSampleIds.begin(), clientSampleIds.end());
        m_secondarySampleAmdExtSessionMap.insert(
            BundleResultAmdExtSessionBundleSamplesOnPrimaryCmdPair(
                pCopyAmdExtGpaSession, bundleSamplesOnPrimaryCmd));
        pCopyAmdExtGpaSession->AddRef(); // Holding a reference is not required here, but we are doing so in order to work around an issue in older drivers

        auto insertOriginalClientSampleId = [&](ClientSampleIdGpaSamplePair clientSampleIdGpaSamplePair)->bool
        {
            originalClientSampleIds.push_back(clientSampleIdGpaSamplePair.first);
            return true;
        };

        pDx12SecondaryCmd->IterateSampleUnorderedMap(insertOriginalClientSampleId);

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


bool DX12GPACommandList::OpenHwSample(ClientSampleId clientSampleId, DriverSampleId* pDriverSampleId) const
{

    UNREFERENCED_PARAMETER(clientSampleId);
    bool success = false;

    if (nullptr != pDriverSampleId)
    {
        if (m_isCommandListOpenInDriver)
        {
            success = true;

            if (m_hasAnyHardwareCounters)
            {
                *pDriverSampleId = m_pAmdExtSession->BeginSample(m_pCmdList, reinterpret_cast<DX12GPAPass*>(GetPass())->GetAmdExtSampleConfig());

                if (*pDriverSampleId == S_INVALID_SAMPLE_INDEX)
                {
                    success = false;
                    GPA_LogError("Unable to begin request due to invalid sample index.");
                }
                else
                {
                    success = true;
                }
            }
        }
    }

    return success;
}

bool DX12GPACommandList::CloseHwSample() const
{
    bool success = false;

    if (m_isCommandListOpenInDriver &&
        nullptr != GetLastSample())
    {
        if (m_hasAnyHardwareCounters)
        {
            m_pAmdExtSession->EndSample(m_pCmdList, GetLastSample()->GetDriverSampleId());
        }

        success = true;
    }

    return success;
}

bool DX12GPACommandList::OpenSwSample(ClientSampleId clientSampleId, DriverSampleId* pDriverSampleId) const
{
    // TODO: Come back when we are implementing software counters
    GPA_STUB_FUNCTION;
    UNREFERENCED_PARAMETER(clientSampleId);
    UNREFERENCED_PARAMETER(pDriverSampleId);
    return true;
}

bool DX12GPACommandList::CloseSwSample()
{
    // TODO: Come back when we are implementing software counters
    GPA_STUB_FUNCTION;
    return true;
}

void DX12GPACommandList::ReleaseNonGPAResources()
{
    if (!m_isNonGPAResourceReleased)
    {
        unsigned int refCount = m_pCmdList->Release();
        UNREFERENCED_PARAMETER(refCount);
        m_pCmdList = nullptr;
        m_isNonGPAResourceReleased = true;

        /*
         * We won't rely on Release() to delete extension session objects because of an issue in older drivers,
         * rather we will use DestroyGpaSession to delete the session object
         */

        DX12GPASession* pDx12GpaSession = reinterpret_cast<DX12GPASession*>(GetParentSession());
        pDx12GpaSession->GetAmdExtInterface()->DestroyGpaSession(m_pAmdExtSession);
        m_pAmdExtSession = nullptr;

        for (auto iter = m_secondarySampleAmdExtSessionMap.begin();
             iter != m_secondarySampleAmdExtSessionMap.end(); ++iter)
        {
            pDx12GpaSession->GetAmdExtInterface()->DestroyGpaSession(iter->first);
        }

        m_secondarySampleAmdExtSessionMap.clear();
    }
}
