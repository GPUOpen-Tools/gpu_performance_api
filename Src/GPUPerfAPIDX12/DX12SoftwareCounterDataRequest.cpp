//==============================================================================
// Copyright (c) 2015-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12SoftwareCounterDataRequest implementation
//==============================================================================

#include "DX12SoftwareCounterDataRequest.h"

DX12SoftwareCounterDataRequest::DX12SoftwareCounterDataRequest()
    :
    DX12DataRequest(),
    m_pContextState(nullptr),
    m_activeCountersList(),
    m_activeQueries(0),
    m_commandList(),
    m_swSampleId(ms_unitializedSampleId)
{
}

DX12SoftwareCounterDataRequest::~DX12SoftwareCounterDataRequest()
{
    m_pContextState = nullptr;
    m_activeCountersList.clear();
    m_activeQueries = 0;
    m_commandList.Release();
    m_swSampleId = ms_unitializedSampleId;
}

bool DX12SoftwareCounterDataRequest::CollectResults(GPASampleResult& resultStorage)
{
    bool result = true;

    if (nullptr == m_pContextState || ms_unitializedSampleId == m_swSampleId)
    {
        result = false;
    }
    else
    {
        DX12SoftwareCountersResults queryResults;
        memset(&queryResults, 0, sizeof(queryResults));
        result = m_pContextState->GetSwSampleResults(m_commandList, m_swSampleId, queryResults);

        if (result)
        {
            resultStorage.m_numResults = m_activeCountersList.size();
            const size_t counterCount = m_activeCountersList.size();
            result = (counterCount == resultStorage.m_numResults);

            for (size_t ci = 0 ; result && (counterCount > ci) ; ++ci)
            {
                switch (m_activeCountersList[ci].m_queryType)
                {
                    case D3D12_QUERY_TYPE_OCCLUSION:
                        resultStorage.m_pResultBuffer[ci] = queryResults.occlusion;
                        break;

                    case D3D12_QUERY_TYPE_BINARY_OCCLUSION:
                        resultStorage.m_pResultBuffer[ci] = queryResults.binaryOcclusion;
                        break;

                    case D3D12_QUERY_TYPE_TIMESTAMP:
                        result = GetTimestampQueryCounterResult(
                                     queryResults,
                                     m_activeCountersList[ci].m_index,
                                     resultStorage.m_pResultBuffer[ci]);
                        break;

                    case D3D12_QUERY_TYPE_PIPELINE_STATISTICS:
                        result = GetPipelineQueryCounterResult(
                                     queryResults,
                                     m_activeCountersList[ci].m_index,
                                     resultStorage.m_pResultBuffer[ci]);
                        break;

                    default:
                        result = false;
                        break;
                }
            }

            m_pContextState->ReleaseSwSample(m_commandList, m_swSampleId);
        }
    }

    return result;
}

bool DX12SoftwareCounterDataRequest::BeginRequest(
    GPA_ContextState* pContextState,
    void* pSampleList,
    const vector<gpa_uint32>* pCounters)
{
    bool result = true;

    if ((nullptr == pContextState) || (nullptr == pCounters) || (nullptr != m_pContextState))
    {
        result = false;
    }
    else
    {
        m_pContextState = static_cast<GPA_ContextStateDX12*>(pContextState);
        GPA_SoftwareCounters* pSwCounters =
            m_pContextState->m_pCounterAccessor->GetSoftwareCounters();
        const size_t counterCount = pCounters->size();
        m_activeCountersList.resize(counterCount);

        gpa_uint32 hardWareCountersCount = m_pContextState->m_pCounterAccessor->GetHardwareCounters()->GetNumCounters();

        for (size_t ci = 0; result && (ci < counterCount) ; ++ci)
        {
            gpa_uint32 swCounterIndex = (*pCounters)[ci];
            m_activeCountersList[ci].m_index =
                SwCounterManager::Instance()->GetSwCounterPubIndex(swCounterIndex);

            // software counter indices are after the hardware counter
            gpa_uint32 counterIdDriver = pSwCounters->m_counters[swCounterIndex - hardWareCountersCount].m_counterIdDriver;
            m_activeCountersList[ci].m_queryType = static_cast<D3D12_QUERY_TYPE>(counterIdDriver);
            result = (counterIdDriver < sizeof(m_activeQueries));

            if (result)
            {
                m_activeQueries |= (0x1 << counterIdDriver);
            }
        }

        if (result)
        {
            IUnknown* pUnknown = static_cast<IUnknown*>(pSampleList);

            ID3D12GraphicsCommandList* pCommandList;
            HRESULT hr = pUnknown->QueryInterface(__uuidof(ID3D12GraphicsCommandList), reinterpret_cast<void**>(&pCommandList));
            result = S_OK == hr;

            if (result)
            {
                m_commandList = pCommandList;

                unsigned int activeQueries = m_activeQueries;
                bool beginQuery = (0 != activeQueries);
                result = m_pContextState->BeginSwSample(m_commandList, m_swSampleId);

                if (result)
                {
                    while (beginQuery)
                    {
                        D3D12_QUERY_TYPE queryType;
                        _BitScanForward(reinterpret_cast<unsigned long*>(&queryType), activeQueries);
                        m_pContextState->BeginSwQuery(m_commandList, m_swSampleId, queryType);
                        activeQueries &= ~(0x1 << static_cast<unsigned int>(queryType));
                        beginQuery = (0 != activeQueries);
                    }

                    SetNumActiveCounters(counterCount);
                }
            }
        }
    }

    return result;
}

bool DX12SoftwareCounterDataRequest::EndRequest()
{
    bool result = true;

    if (nullptr == m_pContextState)
    {
        result = false;
    }
    else
    {
        unsigned int activeQueries = m_activeQueries;
        bool endQuery = (0 != activeQueries);

        while (endQuery)
        {
            D3D12_QUERY_TYPE queryType;
            _BitScanForward(reinterpret_cast<unsigned long*>(&queryType), activeQueries);
            m_pContextState->EndSwQuery(m_commandList, m_swSampleId, queryType);
            activeQueries &= ~(0x1 << static_cast<unsigned int>(queryType));
            endQuery = (0 != activeQueries);
        }

        m_pContextState->EndSwSample(m_commandList, m_swSampleId);
    }

    return result;
}

void DX12SoftwareCounterDataRequest::ReleaseCounters()
{
}

bool DX12SoftwareCounterDataRequest::GetTimestampQueryCounterResult(
    const DX12SoftwareCountersResults& queryResults,
    const gpa_uint32 counterIndex,
    gpa_uint64& counterResult)
const
{
    bool result = true;
    const char* pCounterName = m_pContextState->m_pCounterAccessor->GetCounterName(counterIndex);

    if (0 == strcmp("D3DGPUTime", pCounterName))
    {
        counterResult = (queryResults.timestampEnd - queryResults.timestampBegin);
    }
    else if (0 == strcmp("PreBottomTimestamp", pCounterName))
    {
        counterResult = queryResults.timestampBegin;
    }
    else if (0 == strcmp("PostBottomTimestamp", pCounterName))
    {
        counterResult = queryResults.timestampEnd;
    }
    else
    {
        result = false;
    }

    return result;
}

bool DX12SoftwareCounterDataRequest::GetPipelineQueryCounterResult(
    const DX12SoftwareCountersResults& queryResults,
    const gpa_uint32 counterIndex,
    gpa_uint64& counterResult)
const
{
    bool result = true;
    const char* pCounterName = m_pContextState->m_pCounterAccessor->GetCounterName(counterIndex);

    if (0 == strcmp("IAVertices", pCounterName))
    {
        counterResult = queryResults.pipelineStatistics.IAVertices;
    }
    else if (0 == strcmp("IAPrimitives", pCounterName))
    {
        counterResult = queryResults.pipelineStatistics.IAPrimitives;
    }
    else if (0 == strcmp("VSInvocations", pCounterName))
    {
        counterResult = queryResults.pipelineStatistics.VSInvocations;
    }
    else if (0 == strcmp("GSInvocations", pCounterName))
    {
        counterResult = queryResults.pipelineStatistics.GSInvocations;
    }
    else if (0 == strcmp("GSPrimitives", pCounterName))
    {
        counterResult = queryResults.pipelineStatistics.GSPrimitives;
    }
    else if (0 == strcmp("CInvocations", pCounterName))
    {
        counterResult = queryResults.pipelineStatistics.CInvocations;
    }
    else if (0 == strcmp("CPrimitives", pCounterName))
    {
        counterResult = queryResults.pipelineStatistics.CPrimitives;
    }
    else if (0 == strcmp("PSInvocations", pCounterName))
    {
        counterResult = queryResults.pipelineStatistics.PSInvocations;
    }
    else if (0 == strcmp("HSInvocations", pCounterName))
    {
        counterResult = queryResults.pipelineStatistics.HSInvocations;
    }
    else if (0 == strcmp("DSInvocations", pCounterName))
    {
        counterResult = queryResults.pipelineStatistics.DSInvocations;
    }
    else if (0 == strcmp("CSInvocations", pCounterName))
    {
        counterResult = queryResults.pipelineStatistics.CSInvocations;
    }
    else
    {
        result = false;
    }

    return result;
}
