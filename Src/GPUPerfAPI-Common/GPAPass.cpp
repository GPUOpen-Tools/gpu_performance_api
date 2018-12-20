//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA Pass Object Implementation
//==============================================================================

#include "GPAPass.h"
#include "GPACommandList.h"
#include "GPAHardwareCounters.h"
#include "GPAContextCounterMediator.h"

GPAPass::GPAPass(IGPASession* pGpaSession,
                 PassIndex passIndex,
                 GPACounterSource counterSource,
                 CounterList* pPassCounters):
    m_pGpaSession(pGpaSession),
    m_uiPassIndex(passIndex),
    m_counterSource(counterSource),
    m_isResultCollected(false),
    m_isResultReady(false),
    m_isTimingPass(false),
    m_gpaInternalSampleCounter(0u),
    m_commandListCounter(0u),
    m_isAllSampleValidInPass(false),
    m_isPassComplete(false)
{
    m_pCounterList = pPassCounters;

    if (nullptr != m_pCounterList && !m_pCounterList->empty())
    {
        const GPA_HardwareCounters* pHardwareCounters =
            GPAContextCounterMediator::Instance()->GetCounterAccessor(GetGpaSession()->GetParentContext())->GetHardwareCounters();

        if (pHardwareCounters->IsTimeCounterIndex(m_pCounterList->at(0)))
        {
            m_isTimingPass = true;
        }
    }
}

GPAPass::~GPAPass()
{
    m_gpaCmdListMutex.lock();

    for (auto it = m_gpaCmdList.begin(); it != m_gpaCmdList.end(); ++it)
    {
        delete(*it);
    }

    m_gpaCmdList.clear();
    m_gpaCmdListMutex.unlock();

    std::lock_guard<std::mutex> lock(m_samplesUnorderedMapMutex);

    for (auto samplePair : m_samplesUnorderedMap)
    {
        GPASample* pSample = samplePair.second;
        delete pSample;
    }

    m_samplesUnorderedMap.clear();
}

GPACounterSource GPAPass::GetCounterSource() const
{
    return m_counterSource;
}

GPASample* GPAPass::GetSampleById(ClientSampleId sampleId) const
{
    std::lock_guard<std::mutex> lock(m_samplesUnorderedMapMutex);

    return GetSampleById_NotThreadSafe(sampleId);
}

GPASample* GPAPass::GetSampleById_NotThreadSafe(ClientSampleId sampleId) const
{
    GPASample* pRetVal = nullptr;

    if (m_samplesUnorderedMap.find(sampleId) != m_samplesUnorderedMap.end())
    {
        pRetVal = m_samplesUnorderedMap.at(sampleId);
    }

    return pRetVal;
}

GPASample* GPAPass::CreateAndBeginSample(ClientSampleId clientSampleId, IGPACommandList* pCmdList)
{
    std::lock_guard<std::mutex> lock(m_samplesUnorderedMapMutex);

    GPASample* pSample = nullptr;

    if (!DoesSampleExist_NotThreadSafe(clientSampleId))
    {
        if (GPACounterSource::HARDWARE == m_counterSource)
        {
            pSample = CreateAPISpecificSample(pCmdList, GpaSampleType::Hardware, clientSampleId);
        }
        else if (GPACounterSource::SOFTWARE == m_counterSource)
        {
            pSample = CreateAPISpecificSample(pCmdList, GpaSampleType::Software, clientSampleId);
        }

        if (nullptr != pSample)
        {
            if (!pCmdList->BeginSample(clientSampleId, pSample))
            {
                GPA_LogError("Unable to begin sample in pass.");
                delete pSample;
                pSample = nullptr;
            }
            else
            {
                m_samplesUnorderedMap.insert(std::pair<ClientSampleId, GPASample*>(clientSampleId, pSample));
            }
        }
        else
        {
            GPA_LogError("Unable to create sample.");
        }
    }
    else
    {
        GPA_LogError("Sample Id already exists.");
    }

    return pSample;
}

bool GPAPass::ContinueSample(ClientSampleId srcSampleId, IGPACommandList* pPrimaryGpaCmdList)
{
    std::lock_guard<std::mutex> lock(m_samplesUnorderedMapMutex);

    // 1. Validate that sample already exists in the pass
    // 2. Create a new sample on the cmd
    // 3. Link the new GPA Sample to the old GPA Sample
    // 4. Update the sample map

    // In continuing a sample, we need to check only that the srcSampleId exists (it may not be closed at this point)
    // and primary command list is not same as that of that of the srcSampleId
    // Rather closing the sample over here, we will let the sample close upon closing the command list
    // In this way, we need not to synchronize the samples on different command list (in multi-thread application they might be on different thread)
    // We will mark the parent sample as to be continued by the client

    bool success = false;
    GPASample* pParentSample = GetSampleById_NotThreadSafe(srcSampleId);

    if (nullptr != pParentSample)
    {
        IGPACommandList* pParentSampleCmdList = pParentSample->GetCmdList();

        // Validate that both command list are different and passed command list is not secondary
        if (nullptr != pParentSampleCmdList &&
            nullptr != pPrimaryGpaCmdList &&
            GPA_COMMAND_LIST_SECONDARY != pPrimaryGpaCmdList->GetCmdType() &&
            pPrimaryGpaCmdList != pParentSampleCmdList)
        {
            if (nullptr != pParentSample &&
                pPrimaryGpaCmdList->IsCommandListRunning() &&
                pPrimaryGpaCmdList->IsLastSampleClosed())
            {
                GpaSampleType sampleType = (GPACounterSource::HARDWARE == GetCounterSource()) ? GpaSampleType::Hardware : GpaSampleType::Software;
                // We don't need to add this sample to the sample map as it will be linked to the parent sample
                GPASample* pNewSample = CreateAPISpecificSample(
                                            pPrimaryGpaCmdList,
                                            sampleType,
                                            srcSampleId);

                if (nullptr != pNewSample)
                {
                    if (!pPrimaryGpaCmdList->BeginSample(srcSampleId, pNewSample))
                    {
                        GPA_LogError("Unable to begin continued sample in pass.");
                        delete pNewSample;
                        pNewSample = nullptr;
                    }
                    else
                    {
                        pParentSample->SetAsContinuedByClient();
                        // Link the sample to the parent sample
                        pParentSample->LinkContinuingSample(pNewSample);

                        success = true;
                    }
                }
            }
            else
            {
                GPA_LogError("Unable to continue sample: Either the specified command list has already been closed or the previous sample has not been closed.");
            }
        }
        else
        {
            GPA_LogError("Unable to continue sample: The specified command list must be a secondary command list and it must be different than the parent sample's command list.");
        }
    }
    else
    {
        GPA_LogError("Unable to continue sample: The specified sample id was not found in this pass.");
    }

    return success;
}

IGPACommandList* GPAPass::CreateCommandList(void* pCmd, GPA_Command_List_Type cmdType)
{
    IGPACommandList* pRetCmdList = CreateAPISpecificCommandList(pCmd, m_commandListCounter, cmdType);
    m_commandListCounter++;

    if (nullptr != pRetCmdList)
    {
        AddCommandList(pRetCmdList);
    }

    return pRetCmdList;
}

SampleCount GPAPass::GetSampleCount() const
{
    std::lock_guard<std::mutex> lock(m_samplesUnorderedMapMutex);
    return static_cast<SampleCount>(m_samplesUnorderedMap.size());
}

bool GPAPass::GetSampleIdByIndex(SampleIndex sampleIndex, ClientSampleId& clientSampleId) const
{
    std::lock_guard<std::mutex> lock(m_samplesUnorderedMapMutex);
    bool found = m_clientGpaSamplesMap.find(sampleIndex) != m_clientGpaSamplesMap.end();

    if (found)
    {
        clientSampleId = m_clientGpaSamplesMap.at(sampleIndex);
    }

    return found;
}

bool GPAPass::IsAllSampleValidInPass() const
{
    if (!m_isAllSampleValidInPass)
    {
        bool success = true;
        std::lock_guard<std::mutex> lockSamples(m_samplesUnorderedMapMutex);

        for (auto sampleIter = m_samplesUnorderedMap.cbegin(); sampleIter != m_samplesUnorderedMap.cend(); ++sampleIter)
        {
            success &= sampleIter->second->IsSampleValid();
        }

        if (success)
        {
            m_isAllSampleValidInPass = true;
        }
    }

    return m_isAllSampleValidInPass;
}

CounterCount GPAPass::GetEnabledCounterCount() const
{
    return static_cast<unsigned int>(m_usedCounterListForPass.size());
}

CounterCount GPAPass::GetSkippedCounterCount() const
{
    return static_cast<unsigned int>(m_skippedCounterList.size());
}

PassIndex GPAPass::GetIndex() const
{
    return m_uiPassIndex;
}

bool GPAPass::IsTimingPass() const
{
    return m_isTimingPass;
}

bool GPAPass::UpdateResults()
{
    std::lock_guard<std::mutex> lock(m_samplesUnorderedMapMutex);

    if (!m_isResultCollected)
    {
        bool tmpAllResultsCollected = true;

        for (auto sampleIter = m_samplesUnorderedMap.begin(); sampleIter != m_samplesUnorderedMap.end(); ++sampleIter)
        {
            tmpAllResultsCollected &= sampleIter->second->UpdateResults();
        }

        m_isResultCollected = tmpAllResultsCollected;
    }

    return m_isResultCollected;
}

GPA_Status GPAPass::IsComplete() const
{
    GPA_Status retStatus = GPA_STATUS_OK;

    std::lock_guard<std::mutex> lockCmdList(m_gpaCmdListMutex);

    if (!m_isPassComplete)
    {
        bool completed = true;

        for (auto cmdIter = m_gpaCmdList.cbegin(); cmdIter != m_gpaCmdList.cend() && completed; ++cmdIter)
        {
            completed = !(*cmdIter)->IsCommandListRunning();
        }

        if (!completed)
        {
            retStatus = GPA_STATUS_ERROR_COMMAND_LIST_NOT_ENDED;
        }
        else
        {
            completed = IsAllSampleValidInPass();

            if (!completed)
            {
                retStatus = GPA_STATUS_ERROR_SAMPLE_NOT_ENDED;
            }
            else
            {
                m_isPassComplete = true;
            }
        }
    }

    return retStatus;
}

bool GPAPass::IsResultReady() const
{
    std::lock_guard<std::mutex> lockCmdList(m_gpaCmdListMutex);
    bool isReady = m_isResultReady;

    if (!isReady)
    {
        isReady = true;


        for (auto cmdIter = m_gpaCmdList.cbegin(); cmdIter != m_gpaCmdList.cend() && isReady; ++cmdIter)
        {
            isReady &= (*cmdIter)->IsResultReady();
        }

        if (isReady)
        {
            m_isResultReady = true;
        }
    }

    return isReady;
}

bool GPAPass::IsResultCollected() const
{
    return m_isResultCollected;
}

GPA_Status GPAPass::GetResult(ClientSampleId clientSampleId, CounterIndex internalCounterIndex, gpa_uint64* pResultBuffer) const
{
    *pResultBuffer = 0;

    std::lock_guard<std::mutex> lock(m_samplesUnorderedMapMutex);

    GPA_Status status = GPA_STATUS_OK;
    SamplesMap::const_iterator sampleIter = m_samplesUnorderedMap.find(clientSampleId);

    if (sampleIter == m_samplesUnorderedMap.cend())
    {
        GPA_LogError("Invalid SampleId supplied while getting pass results.");
        status = GPA_STATUS_ERROR_INVALID_PARAMETER;
    }
    else
    {
        CounterIndex counterIndexWithinSample;

        if (GetCounterIndexInPass(internalCounterIndex, &counterIndexWithinSample))
        {
            if (!sampleIter->second->GetResult(counterIndexWithinSample, pResultBuffer))
            {
                GPA_LogError("Failed to get counter result within pass.");
                status = GPA_STATUS_ERROR_FAILED;
            }
        }
        else if (m_skippedCounterList.find(internalCounterIndex) == m_skippedCounterList.end())
        {
            // we didn't skip the counter, so we wrongly think it was in this pass.
            GPA_LogError("Failed to find internal counter index within pass counters.");
            status = GPA_STATUS_ERROR_INVALID_PARAMETER;
        }
    }

    return status;
}

bool GPAPass::DoesSampleExist(ClientSampleId clientSampleId) const
{
    std::lock_guard<std::mutex> lock(m_samplesUnorderedMapMutex);
    return DoesSampleExist_NotThreadSafe(clientSampleId);
}

bool GPAPass::DoesSampleExist_NotThreadSafe(ClientSampleId clientSampleId) const
{
    bool exists = false;

    if (m_samplesUnorderedMap.find(clientSampleId) != m_samplesUnorderedMap.end())
    {
        exists = true;
    }

    return exists;
}

bool GPAPass::DoesCommandListExist(IGPACommandList* pGpaCommandList) const
{
    bool exists = false;

    std::lock_guard<std::mutex> lock(m_gpaCmdListMutex);

    for (auto cIter = m_gpaCmdList.cbegin(); !exists && cIter != m_gpaCmdList.cend(); ++cIter)
    {
        if (*cIter == pGpaCommandList)
        {
            exists = true;
        }
    }

    return exists;
}

const GPACommandLists& GPAPass::GetCmdList() const
{
    return m_gpaCmdList;
}

void GPAPass::EnableCounterForPass(const CounterIndex& counterIndex)
{
    std::lock_guard<std::mutex> lockPass(m_counterListMutex);
    m_usedCounterListForPass.push_back(counterIndex);
}

void GPAPass::DisableCounterForPass(const CounterIndex& counterIndex)
{
    std::lock_guard<std::mutex> lockPass(m_counterListMutex);
    m_skippedCounterList.insert(counterIndex);
}

void GPAPass::EnableAllCountersForPass()
{
    std::lock_guard<std::mutex> lockPass(m_counterListMutex);
    m_usedCounterListForPass = *m_pCounterList;
    m_skippedCounterList.empty();
}

void GPAPass::DisableAllCountersForPass()
{
    std::lock_guard<std::mutex> lockPass(m_counterListMutex);
    m_skippedCounterList.clear();
    m_skippedCounterList.insert(m_pCounterList->begin(), m_pCounterList->end());
    m_usedCounterListForPass.empty();
}

CounterCount GPAPass::GetNumEnabledCountersForPass() const
{
    std::lock_guard<std::mutex> lockPass(m_counterListMutex);
    return static_cast<CounterCount>(m_pCounterList->size() - m_skippedCounterList.size());
}

bool GPAPass::GetCounterIndexInPass(CounterIndex internalCounterIndex, CounterIndex* pCounterIndexInPassList) const
{
    bool found = false;
    if (!m_usedCounterListForPass.empty())
    {
        CounterList::const_iterator iter = std::find(m_usedCounterListForPass.begin(), m_usedCounterListForPass.end(), internalCounterIndex);

        if (m_usedCounterListForPass.end() != iter)
        {
            *pCounterIndexInPassList = static_cast<CounterIndex>(iter - m_usedCounterListForPass.begin());
            found = true;
        }
    }

    return found;
}

bool GPAPass::GetCounterByIndexInPass(CounterIndex counterIndexInPass, CounterIndex* pInternalCounterIndex) const
{
    if (!pInternalCounterIndex)
    {
        assert(0);
        return false;
    }
    bool found = counterIndexInPass < m_usedCounterListForPass.size();

    *pInternalCounterIndex = static_cast<CounterIndex>(-1);
    if (found)
    {
        *pInternalCounterIndex = m_usedCounterListForPass[counterIndexInPass];
    }

    return found;
}

bool GPAPass::IsResultsCollectedFromDriver() const
{
    return m_isResultCollected;
}

const IGPACounterAccessor* GPAPass::GetSessionContextCounterAccessor() const
{
    return GPAContextCounterMediator::Instance()->GetCounterAccessor(GetGpaSession()->GetParentContext());
}

void GPAPass::AddCommandList(IGPACommandList* pGPACommandList)
{
    std::lock_guard<std::mutex> lockCmdList(m_gpaCmdListMutex);
    m_gpaCmdList.push_back(pGPACommandList);
}

void GPAPass::LockCommandListMutex() const
{
    m_gpaCmdListMutex.lock();
}

void GPAPass::UnlockCommandListMutex() const
{
    m_gpaCmdListMutex.unlock();
}

void GPAPass::AddClientSample(ClientSampleId sampleId, GPASample* pGPASample)
{
    m_samplesUnorderedMapMutex.lock();
    m_samplesUnorderedMap.insert(std::pair<ClientSampleId, GPASample*>(sampleId, pGPASample));
    unsigned int internalSampleId = m_gpaInternalSampleCounter.fetch_add(1);
    m_clientGpaSamplesMap.insert(std::pair<unsigned int, unsigned int>(internalSampleId, sampleId));
    m_samplesUnorderedMapMutex.unlock();
}

void GPAPass::IteratePassCounterList(std::function<bool(const CounterIndex& counterIndex)> function) const
{
    bool next = true;

    for (auto it = (*m_pCounterList).cbegin(); it != (*m_pCounterList).cend() && next; ++it)
    {
        next = function(*it);
    }
}

void GPAPass::IterateEnabledCounterList(std::function<bool(const CounterIndex& counterIndex)> function) const
{
    bool next = true;

    for (auto it = m_usedCounterListForPass.cbegin(); it != m_usedCounterListForPass.cend() && next; ++it)
    {
        next = function(*it);
    }
}

void GPAPass::IterateSkippedCounterList(std::function<bool(const CounterIndex& counterIndex)> function) const
{
    bool next = true;

    for (auto it = m_skippedCounterList.cbegin(); it != m_skippedCounterList.cend() && next; ++it)
    {
        next = function(*it);
    }
}

gpa_uint32 GPAPass::GetBottomToBottomTimingDurationCounterIndex() const
{
    const GPA_HardwareCounters* pHardwareCounters =
        GPAContextCounterMediator::Instance()->GetCounterAccessor(GetGpaSession()->GetParentContext())->GetHardwareCounters();

    for (gpa_uint32 i = 0; i < static_cast<gpa_uint32>(m_pCounterList->size()); i++)
    {
        if ((*m_pCounterList)[i] == pHardwareCounters->m_gpuTimeBottomToBottomDurationCounterIndex)
        {
            return i;
        }
    }

    return static_cast<gpa_uint32>(-1);
}

gpa_uint32 GPAPass::GetTopToBottomTimingDurationCounterIndex() const
{
    const GPA_HardwareCounters* pHardwareCounters =
        GPAContextCounterMediator::Instance()->GetCounterAccessor(GetGpaSession()->GetParentContext())->GetHardwareCounters();

    for (gpa_uint32 i = 0; i < static_cast<gpa_uint32>(m_pCounterList->size()); i++)
    {
        if ((*m_pCounterList)[i] == pHardwareCounters->m_gpuTimeTopToBottomDurationCounterIndex)
        {
            return i;
        }
    }

    return static_cast<gpa_uint32>(-1);
}

IGPASession* GPAPass::GetGpaSession() const
{
    return m_pGpaSession;
}
