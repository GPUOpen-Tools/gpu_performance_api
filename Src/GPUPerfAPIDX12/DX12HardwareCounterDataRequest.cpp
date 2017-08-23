//==============================================================================
// Copyright (c) 2016-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage a single sample of HW counters
//==============================================================================

#include "DX12HardwareCounterDataRequest.h"

DX12HardwareCounterDataRequest::DX12HardwareCounterDataRequest() :
    m_pContextState(nullptr),
    m_numCounters(0),
    m_sampleIndex(0),
    m_commandList(nullptr),
    m_isTimingRequest(false)
{
}

DX12HardwareCounterDataRequest::~DX12HardwareCounterDataRequest()
{
    m_commandList = nullptr;
}

bool DX12HardwareCounterDataRequest::CollectResults(GPA_CounterResults& resultStorage)
{
    bool result = false;
    IAmdExtGpaSession* pGpaSession = nullptr;

    if (m_pContextState->GetGpaSessionForCommandList(m_commandList, &pGpaSession))
    {
        result = pGpaSession->IsReady();

        if (result)
        {
            size_t expectedResultsSize;

            if (m_isTimingRequest)
            {
                expectedResultsSize = 2 * sizeof(gpa_uint64); // timing requests have two timestamps
            }
            else
            {
                expectedResultsSize = m_numCounters * sizeof(gpa_uint64);
            }

            size_t reportedSize = 0;

            pGpaSession->GetResults(m_sampleIndex, &reportedSize, nullptr);

            result = false;

            if (m_isTimingRequest)
            {
                if (reportedSize == expectedResultsSize)
                {
                    gpa_uint64 timestamps[2] = {};

                    result = S_OK == pGpaSession->GetResults(m_sampleIndex, &reportedSize, timestamps);

                    if (result)
                    {
                        gpa_uint64 difference = timestamps[1] - timestamps[0];

#ifdef DEBUG_TIMING_COUNTER_RESULTS
                        std::stringstream ss;
                        std::string cmdlistType;
                        switch (m_commandList->GetType())
                        {
                        case D3D12_COMMAND_LIST_TYPE_DIRECT:
                            cmdlistType = "D3D12_COMMAND_LIST_TYPE_DIRECT";
                            break;
                        case D3D12_COMMAND_LIST_TYPE_BUNDLE:
                            cmdlistType = "D3D12_COMMAND_LIST_TYPE_BUNDLE";
                            break;
                        case D3D12_COMMAND_LIST_TYPE_COMPUTE:
                            cmdlistType = "D3D12_COMMAND_LIST_TYPE_COMPUTE";
                            break;
                        case D3D12_COMMAND_LIST_TYPE_COPY:
                            cmdlistType = "D3D12_COMMAND_LIST_TYPE_COPY";
                            break;
                        default:
                            cmdlistType = "UNKNOWN";
                            break;
                        }

                        ss << "SampleId: " << m_sampleID << " SampleIndex: " << m_sampleIndex << " CmdList: " << std::hex << m_commandList.GetInterfacePtr() << "(" << cmdlistType << ")" << std::dec << " TS0: " << timestamps[0] << " TS1: " << timestamps[1] << " duration: " << difference;
                        GPA_LogDebugCounterDefs(ss.str().c_str());
#endif

                        resultStorage.m_pResultBuffer[0] = difference;
                    }
                }
            }
            else
            {
                if (m_skippedCounterIndexes.empty())
                {
                    // all counters are valid -- just read the results from GpaSession
                    if (reportedSize == expectedResultsSize)
                    {
                        result = S_OK == pGpaSession->GetResults(m_sampleIndex, &reportedSize, resultStorage.m_pResultBuffer);
                    }
                }
                else
                {
                    // some counters are invalid for the current hardware -- we need to use zero for those and
                    // and the GpaSession results for the valid counters
                    size_t numUint64Results = reportedSize / sizeof(gpa_uint64);
                    gpa_uint64* pCounterResults = new(std::nothrow) gpa_uint64[numUint64Results];

                    if (nullptr == pCounterResults)
                    {
                        GPA_LogError("Unable to allocate memory for counter results.");
                    }
                    else
                    {
                        result = S_OK == pGpaSession->GetResults(m_sampleIndex, &reportedSize, pCounterResults);

                        if (result)
                        {
                            int skippedCounters = 0;

                            for (size_t i = 0; i < m_numCounters; i++)
                            {
                                if (!m_skippedCounterIndexes.empty() && m_skippedCounterIndexes.front() == i)
                                {
                                    m_skippedCounterIndexes.pop_front();
                                    resultStorage.m_pResultBuffer[i] = 0;
                                    skippedCounters++;
                                }
                                else
                                {
                                    resultStorage.m_pResultBuffer[i] = pCounterResults[i - skippedCounters];
                                }
                            }
                        }

                        delete[] pCounterResults;
                    }
                }
            }

            if (!result)
            {
                GPA_LogError("Unable to get hw sample results.");
            }
        }
    }

    return result;
}

bool DX12HardwareCounterDataRequest::BeginRequest(GPA_ContextState* pContextState,
                                                  void* pSampleList,
                                                  gpa_uint32 selectionId,
                                                  const vector<gpa_uint32>* pCounters)
{
    UNREFERENCED_PARAMETER(selectionId);

    bool result = true;

    m_pContextState = reinterpret_cast<GPA_ContextStateDX12*>(pContextState);

    AmdExtGpaSampleConfig gpaSampleConfig = { };

    std::vector<AmdExtPerfCounterId> counterIds;

    GPA_HardwareCounters* pHardwareCounters = m_pContextState->m_pCounterAccessor->GetHardwareCounters();

    m_numCounters = static_cast<gpa_uint32>(pCounters->size());

    if (m_numCounters > 0)
    {
        if ((*pCounters)[0] == pHardwareCounters->m_gpuTimeBottomToBottomCounterIndex ||
            (*pCounters)[0] == pHardwareCounters->m_gpuTimeTopToBottomCounterIndex)
        {
            m_isTimingRequest = true;

            gpaSampleConfig.type = AmdExtGpaSampleType::Timing;

            if ((*pCounters)[0] == pHardwareCounters->m_gpuTimeBottomToBottomCounterIndex)
            {
                gpaSampleConfig.timing.preSample = AmdExtHwPipePoint::HwPipeBottom;
            }
            else if ((*pCounters)[0] == pHardwareCounters->m_gpuTimeTopToBottomCounterIndex)
            {
                gpaSampleConfig.timing.preSample = AmdExtHwPipePoint::HwPipeTop;
            }

            gpaSampleConfig.timing.postSample = AmdExtHwPipePoint::HwPipeBottom;
        }
        else
        {
            AmdExtPerfExperimentShaderFlags maskValue = PerfShaderMaskAll;

            gpaSampleConfig.type = AmdExtGpaSampleType::Cumulative;
            gpaSampleConfig.flags.u32All = 0;

            m_skippedCounterIndexes.clear();

            // add all desired counters
            for (size_t i = 0; i < pCounters->size(); i++)
            {
                GPA_HardwareCounterDescExt* pCounter = &pHardwareCounters->m_counters[(*pCounters)[i]];
                AmdExtGpuBlock block = static_cast<AmdExtGpuBlock>(pCounter->m_groupIdDriver);
                UINT32 instance = static_cast<UINT32>(pHardwareCounters->m_pGroups[pCounter->m_groupIndex].m_blockInstance);
                UINT32 eventId = static_cast<UINT32>(pCounter->m_pHardwareCounter->m_counterIndexInGroup);

                if (m_pContextState->GetInstanceCount(block) <= instance)
                {
                    m_skippedCounterIndexes.push_back(i);
                    continue;
                }

                if (m_pContextState->GetMaxEventIdCount(block) <= eventId)
                {
                    m_skippedCounterIndexes.push_back(i);
                    continue;
                }

                // Validate requested counter vs number of actual hardware counters and group index
                uint32_t groupIndex = pCounter->m_groupIndex;

                uint32_t counters = 0;

                if (groupIndex < pHardwareCounters->m_groupCount)
                {
                    counters = pHardwareCounters->m_pGroups[groupIndex].m_numCounters;
                }
                else
                {
                    counters = pHardwareCounters->m_pAdditionalGroups[groupIndex - pHardwareCounters->m_groupCount].m_numCounters;
                }

                if (pCounter->m_pHardwareCounter->m_counterIndexInGroup > counters)
                {
                    assert(pCounter->m_pHardwareCounter->m_counterIndexInGroup <= counters);
                    m_skippedCounterIndexes.push_back(i);
                    continue;
                }

                if (groupIndex > (pHardwareCounters->m_groupCount + pHardwareCounters->m_additionalGroupCount))
                {
                    assert(groupIndex <= (pHardwareCounters->m_groupCount + pHardwareCounters->m_additionalGroupCount));
                    m_skippedCounterIndexes.push_back(i);
                    continue;
                }

                // Add counter to valid vector
                AmdExtPerfCounterId thisCounter;
                thisCounter.block = block;
                thisCounter.instance = instance;
                thisCounter.eventId = eventId;

                counterIds.push_back(thisCounter);

                // if dealing with an SQ counter, check if the the stage mask needs to be set
                if (pCounter->m_groupIndex >= pHardwareCounters->m_pSQCounterGroups[0].m_groupIndex && pCounter->m_groupIndex <= pHardwareCounters->m_pSQCounterGroups[pHardwareCounters->m_sqGroupCount - 1].m_groupIndex)
                {
                    GPA_SQShaderStage stage = SQ_ALL;

                    for (unsigned int j = 0; j < pHardwareCounters->m_sqGroupCount - 1; j++)
                    {
                        if (pHardwareCounters->m_pSQCounterGroups[j].m_groupIndex == pCounter->m_groupIndex)
                        {
                            stage = pHardwareCounters->m_pSQCounterGroups[j].m_stage;
                            break;
                        }
                    }

                    if (stage == SQ_ES)
                    {
                        maskValue = PerfShaderMaskEs;
                    }
                    else if (stage == SQ_GS)
                    {
                        maskValue = PerfShaderMaskGs;
                    }
                    else if (stage == SQ_VS)
                    {
                        maskValue = PerfShaderMaskVs;
                    }
                    else if (stage == SQ_PS)
                    {
                        maskValue = PerfShaderMaskPs;
                    }
                    else if (stage == SQ_LS)
                    {
                        maskValue = PerfShaderMaskLs;
                    }
                    else if (stage == SQ_HS)
                    {
                        maskValue = PerfShaderMaskHs;
                    }
                    else if (stage == SQ_CS)
                    {
                        maskValue = PerfShaderMaskCs;
                    }
                }
            }

            gpaSampleConfig.perfCounters.numCounters = m_numCounters - static_cast<UINT32>(m_skippedCounterIndexes.size());
            gpaSampleConfig.perfCounters.pIds = counterIds.data();
            gpaSampleConfig.perfCounters.spmTraceSampleInterval = 0;
            gpaSampleConfig.perfCounters.gpuMemoryLimit = 0;

            // set shader mask
            gpaSampleConfig.flags.sqShaderMask = 1;
            gpaSampleConfig.sqShaderMask = maskValue;
        }

        // Insert L2 cache invalidate and flush around counter sample
        if (pContextState->GetInvalidateAndFlushL2Cache())
        {
            gpaSampleConfig.flags.cacheFlushOnCounterCollection = true;
            pContextState->SetInvalidateAndFlushL2Cache(false);
        }
    }

    IUnknown* pUnknown = static_cast<IUnknown*>(pSampleList);

    HRESULT hr = pUnknown->QueryInterface(__uuidof(ID3D12GraphicsCommandList), reinterpret_cast<void**>(&m_commandList.GetInterfacePtr()));
    result = S_OK == hr;

    if (result)
    {
        IAmdExtGpaSession* pGpaSession = nullptr;

        if (m_pContextState->GetGpaSessionForCommandList(m_commandList, &pGpaSession))
        {
            m_sampleIndex = pGpaSession->BeginSample(m_commandList, gpaSampleConfig);

            SetActiveCountersCount(m_numCounters);
        }
        else
        {
            result = false;
        }
    }
    else
    {
        GPA_LogError("Unable to begin request due to invalid sample list.");
    }

    return result;
}

bool DX12HardwareCounterDataRequest::EndRequest()
{
    IAmdExtGpaSession* pGpaSession = nullptr;
    bool result = m_pContextState->GetGpaSessionForCommandList(m_commandList, &pGpaSession);

    if (result)
    {
        pGpaSession->EndSample(m_commandList, m_sampleIndex);
    }

    return result;
}

void DX12HardwareCounterDataRequest::ReleaseCounters()
{
}
