//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA Pass Object Implementation
//==============================================================================

#include "GPAPass.h"
#include "GPACommandList.h"
#include "GPAHardwareCounters.h"

GPAPass::GPAPass(IGPASession* pGpaSession,
                 PassIndex passIndex,
                 GPACounterSource counterSource,
                 IGPACounterScheduler* pCounterScheduler,
                 const IGPACounterAccessor* pCounterAccessor):
    m_pGpaSession(pGpaSession),
    m_uiPassIndex(passIndex),
    m_counterSource(counterSource),
    m_isResultCollected(false),
    m_isTimingPass(false),
    m_pCounterScheduler(pCounterScheduler),
    m_pCounterAccessor(pCounterAccessor),
    m_commandListCounter(0u),
    m_isAllSampleValidInPass(false),
    m_gpuTimeTopToBottomPresent(false),
    m_gpuTimeTopToBottomOffset(0),
    m_gpuTimeBottomToBottomPresent(false),
    m_gpuTimeBottomToBottomOffset(0),
    m_gpuTimestampTopPresent(false),
    m_gpuTimestampTopOffset(0),
    m_gpuTimestampPreBottomPresent(false),
    m_gpuTimestampPreBottomOffset(0),
    m_gpuTimestampPostBottomPresent(false),
    m_gpuTimestampPostBottomOffset(0)
{
    m_pCounterList = m_pCounterScheduler->GetCountersForPass(passIndex);

    const GPA_HardwareCounters* pHardwareCounters = m_pCounterAccessor->GetHardwareCounters();

    if (!m_pCounterList->empty())
    {
        if (m_pCounterList->at(0) == pHardwareCounters->m_gpuTimeBottomToBottomCounterIndex ||
            m_pCounterList->at(0) == pHardwareCounters->m_gpuTimeTopToBottomCounterIndex)
        {
            m_isTimingPass = true;
            PopulateTimingCounterInfo();
        }
    }
}

GPAPass::~GPAPass()
{
    m_gpaCmdListMutex.lock();

    for (auto it = m_gpaCmdList.begin();
         it != m_gpaCmdList.end(); ++it)
    {
        delete(*it);
    }

    m_gpaCmdList.clear();
    m_gpaCmdListMutex.unlock();

    std::lock_guard<std::mutex> lock(m_samplesMapMutex);

    for (auto samplePair : m_samplesMap)
    {
        GPASample* pSample = samplePair.second;
        delete pSample;
    }

    m_samplesMap.clear();
}

GPACounterSource GPAPass::GetCounterSource() const
{
    return m_counterSource;
}

GPASample* GPAPass::GetSampleById(ClientSampleId sampleId) const
{
    std::lock_guard<std::mutex> lock(m_samplesMapMutex);

    GPASample* pRetVal = nullptr;

    if (m_samplesMap.find(sampleId) != m_samplesMap.end())
    {
        pRetVal = m_samplesMap.at(sampleId);
    }

    return pRetVal;
}


GPASample* GPAPass::CreateAndBeginSample(ClientSampleId clientSampleId, IGPACommandList* pCmdList)
{
    std::lock_guard<std::mutex> lock(m_samplesMapMutex);

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
            m_samplesMap.insert(std::pair<ClientSampleId, GPASample*>(clientSampleId, pSample));

            if (!pCmdList->BeginSample(clientSampleId, pSample))
            {
                GPA_LogError("Unable to begin sample in pass.");
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
    std::lock_guard<std::mutex> lock(m_samplesMapMutex);

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
    GPASample* pParentSample = GetSampleById(srcSampleId);
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
                // TODO: Can these two be merged into the same entrypoint?
                // ie, if we link a continuing sample, isn't it by default continued by client?
                // is there a way that WE (GPA) would continue it on our own?
                // Mark the parent sample as getting continuing by client
                pParentSample->SetAsContinuedByClient();
                // Link the sample to the parent sample
                pParentSample->LinkContinuingSample(pNewSample);
                success = true;
            }
        }
        else
        {
            GPA_LogError("Unable to continue sample: Either the specified command list has already been closed or the previous sample has not been closed.");
        }
    }
    else
    {
        GPA_LogError("Unable to continue sample: The specified command list must be secondary command list and it must be different than the parent sample's command list.");
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
    std::lock_guard<std::mutex> lock(m_samplesMapMutex);

    return static_cast<SampleCount>(m_samplesMap.size());
}

bool GPAPass::IsAllSampleValidInPass() const
{
    if (!m_isAllSampleValidInPass)
    {
        bool success = true;
        std::lock_guard<std::mutex> lockSamples(m_samplesMapMutex);

        for (auto sampleIter = m_samplesMap.cbegin(); sampleIter != m_samplesMap.cend(); ++sampleIter)
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
    std::lock_guard<std::mutex> lock(m_samplesMapMutex);

    if (!m_isResultCollected)
    {
        bool tmpAllResultsCollected = true;

        for (auto sampleIter = m_samplesMap.begin(); sampleIter != m_samplesMap.end(); ++sampleIter)
        {
            tmpAllResultsCollected &= sampleIter->second->UpdateResults();
        }

        m_isResultCollected = tmpAllResultsCollected;
    }

    return m_isResultCollected;
}

bool GPAPass::IsComplete() const
{
    std::lock_guard<std::mutex> lock(m_samplesMapMutex);

    bool completed = true;

    for (auto sampleIter = m_samplesMap.cbegin(); sampleIter != m_samplesMap.cend(); ++sampleIter)
    {
        completed &= sampleIter->second->IsComplete();
    }

    return completed;
}

gpa_uint64 GPAPass::GetResult(ClientSampleId clientSampleId, CounterIndex internalCounterIndex) const
{
    std::lock_guard<std::mutex> lock(m_samplesMapMutex);

    gpa_uint64 result = 0u;

    SamplesMap::const_iterator sampleIter = m_samplesMap.find(clientSampleId);

    if (sampleIter == m_samplesMap.cend())
    {
        GPA_LogError("Invalid SampleId supplied while getting pass results.");
    }
    else
    {
        CounterIndex counterIndexWithinSample;

        if (GetCounterIndexInPass(internalCounterIndex, counterIndexWithinSample))
        {
            if (!sampleIter->second->GetResult(counterIndexWithinSample, &result))
            {
                GPA_LogError("Failed to get counter result within pass.");
            }
        }
        else if (m_skippedCounterList.find(internalCounterIndex) == m_skippedCounterList.end())
        {
            // we didn't skip the counter, so we wrongly think it was in this pass.
            GPA_LogError("Failed to find internal counter index within pass counters.");
        }
    }

    return result;
}

bool GPAPass::DoesSampleExist(ClientSampleId clientSampleId) const
{
    std::lock_guard<std::mutex> lock(m_samplesMapMutex);
    return DoesSampleExist_NotThreadSafe(clientSampleId);
}

bool GPAPass::DoesSampleExist_NotThreadSafe(ClientSampleId clientSampleId) const
{
    bool exists = false;

    if (m_samplesMap.find(clientSampleId) != m_samplesMap.end())
    {
        exists = true;
    }

    return exists;
}

bool GPAPass::DoesCommandListExist(IGPACommandList* pGpaCommandList) const
{
    bool exists = false;

    std::lock_guard<std::mutex> lock(m_gpaCmdListMutex);

    for (GPACommandLists::const_iterator cIter = m_gpaCmdList.cbegin();
         !exists &&
         cIter != m_gpaCmdList.cend(); ++cIter)
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

bool GPAPass::IsTimeStamp(gpa_uint32 activeCounterOffset) const
{
    bool isTimestamp = false;

    if ((m_gpuTimeBottomToBottomPresent && activeCounterOffset == m_gpuTimeBottomToBottomOffset) ||
        (m_gpuTimeTopToBottomPresent && activeCounterOffset == m_gpuTimeTopToBottomOffset) ||
        (m_gpuTimestampTopPresent && activeCounterOffset == m_gpuTimestampTopOffset) ||
        (m_gpuTimestampPreBottomPresent && activeCounterOffset == m_gpuTimestampPreBottomOffset) ||
        (m_gpuTimestampPostBottomPresent && activeCounterOffset == m_gpuTimestampPostBottomOffset))
    {
        isTimestamp = true;
    }

    return isTimestamp;
}

bool GPAPass::GPUTimeTopToBottomPresent() const
{
    return m_gpuTimeTopToBottomPresent;
}

bool GPAPass::GPUTimeBottomToBottomPresent() const
{
    return m_gpuTimeBottomToBottomPresent;
}

bool GPAPass::GPUTimestampTopPresent() const
{
    return m_gpuTimestampTopPresent;
}

bool GPAPass::GPUTimestampPreBottomPresent() const
{
    return m_gpuTimestampPreBottomPresent;
}

bool GPAPass::GPUTimestampPostBottomPresent() const
{
    return m_gpuTimestampPostBottomPresent;
}

gpa_uint32 GPAPass::GPUTimeBottomToBottomOffset() const
{
    return m_gpuTimeBottomToBottomOffset;
}

gpa_uint32 GPAPass::GPUTimeTopToBottomOffset() const
{
    return m_gpuTimeTopToBottomOffset;
}

gpa_uint32 GPAPass::GPUTimestampTopOffset() const
{
    return m_gpuTimestampTopOffset;
}

gpa_uint32 GPAPass::GPUTimestampPreBottomOffset() const
{
    return m_gpuTimestampPreBottomOffset;
}

gpa_uint32 GPAPass::GPUTimestampPostBottomOffset() const
{
    return m_gpuTimestampPostBottomOffset;
}

bool GPAPass::GetCounterIndexInPass(CounterIndex internalCounterIndex, CounterIndex& counterIndexInPassList) const
{
    bool found = false;

    if (!m_usedCounterListForPass.empty())
    {
        CounterList::const_iterator iter = std::find(m_usedCounterListForPass.begin(), m_usedCounterListForPass.end(), internalCounterIndex);

        if (m_usedCounterListForPass.end() != iter)
        {
            counterIndexInPassList = static_cast<CounterIndex>(iter - m_usedCounterListForPass.begin());
            found = true;
        }
    }

    return found;
}

bool GPAPass::GetCounterByIndexInPass(CounterIndex counterIndexInPass, CounterIndex& internalCounterIndex) const
{
    bool found = counterIndexInPass < m_usedCounterListForPass.size();

    if (found)
    {
        internalCounterIndex = m_usedCounterListForPass[counterIndexInPass];
    }

    return found;
}

bool GPAPass::IsResultsCollectedFromDriver() const
{
    return m_isResultCollected;
}

const IGPACounterAccessor* GPAPass::GetCounterAccessor() const
{
    return m_pCounterAccessor;
}

const IGPACounterScheduler* GPAPass::GetCounterScheduler() const
{
    return m_pCounterScheduler;
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
    m_samplesMapMutex.lock();
    m_samplesMap.insert(std::pair<ClientSampleId, GPASample*>(sampleId, pGPASample));
    m_samplesMapMutex.unlock();
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

void GPAPass::PopulateTimingCounterInfo()
{
    const GPA_HardwareCounters* pHardwareCounters = m_pCounterAccessor->GetHardwareCounters();

    m_gpuTimeTopToBottomPresent = false;
    m_gpuTimeBottomToBottomPresent = false;
    m_gpuTimestampTopPresent = false;
    m_gpuTimestampPreBottomPresent = false;
    m_gpuTimestampPostBottomPresent = false;

    for (gpa_uint32 i = 0; i < static_cast<gpa_uint32>(m_pCounterList->size()); i++)
    {
        if ((*m_pCounterList)[i] == pHardwareCounters->m_gpuTimeTopToBottomCounterIndex)
        {
            m_gpuTimeTopToBottomPresent = true;
            m_gpuTimeTopToBottomOffset = i;
        }
        else if ((*m_pCounterList)[i] == pHardwareCounters->m_gpuTimeBottomToBottomCounterIndex)
        {
            m_gpuTimeBottomToBottomPresent = true;
            m_gpuTimeBottomToBottomOffset = i;
        }
        else if ((*m_pCounterList)[i] == pHardwareCounters->m_gpuTimestampTopCounterIndex)
        {
            m_gpuTimestampTopPresent = true;
            m_gpuTimestampTopOffset = i;
        }
        else if ((*m_pCounterList)[i] == pHardwareCounters->m_gpuTimestampPreBottomCounterIndex)
        {
            m_gpuTimestampPreBottomPresent = true;
            m_gpuTimestampPreBottomOffset = i;
        }
        else if ((*m_pCounterList)[i] == pHardwareCounters->m_gpuTimestampPostBottomCounterIndex)
        {
            m_gpuTimestampPostBottomPresent = true;
            m_gpuTimestampPostBottomOffset = i;
        }
    }
}

IGPASession* GPAPass::GetGpaSession() const
{
    return m_pGpaSession;
}
