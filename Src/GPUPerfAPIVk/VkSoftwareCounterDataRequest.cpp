//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  VkSoftwareCounterDataRequest implementation
//==============================================================================

#include "VkSoftwareCounterDataRequest.h"

VkSoftwareCounterDataRequest::VkSoftwareCounterDataRequest()
    :
    VkDataRequest(),
    m_pContextState(nullptr),
    m_activeCountersList(),
    m_activeQueries(0),
    m_commandList(),
    m_swSampleId(ms_unitializedSampleId)
{
}

VkSoftwareCounterDataRequest::~VkSoftwareCounterDataRequest()
{
    m_pContextState = nullptr;
    m_activeCountersList.clear();
    m_activeQueries = 0;
    m_swSampleId = ms_unitializedSampleId;
}

bool VkSoftwareCounterDataRequest::CollectResults(GPA_CounterResults& resultStorage)
{
    bool result = true;

    if (nullptr == m_pContextState || ms_unitializedSampleId == m_swSampleId)
    {
        result = false;
    }
    else
    {
        GpaVkSoftwareQueryResults queryResults;
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
                    case GPA_VK_QUERY_TYPE_OCCLUSION:
                        resultStorage.m_pResultBuffer[ci] = queryResults.occlusion;
                        break;

                    case GPA_VK_QUERY_TYPE_OCCLUSION_BINARY:
                        resultStorage.m_pResultBuffer[ci] = queryResults.occlusionBinary;
                        break;

                    case GPA_VK_QUERY_TYPE_TIMESTAMP:
                        result = GetTimestampQueryCounterResult(
                                     queryResults,
                                     m_activeCountersList[ci].m_index,
                                     resultStorage.m_pResultBuffer[ci]);
                        break;

                    case GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS:
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

bool VkSoftwareCounterDataRequest::BeginRequest(
    GPA_ContextState* pContextState,
    void* pSampleList,
    gpa_uint32 selectionId,
    const vector<gpa_uint32>* pCounters)
{
    UNREFERENCED_PARAMETER(selectionId);
    UNREFERENCED_PARAMETER(pSampleList);
    bool result = true;

    if ((nullptr == pContextState) || (nullptr == pCounters) || (nullptr != m_pContextState) || (nullptr == pSampleList))
    {
        result = false;
    }
    else
    {
        m_pContextState = static_cast<GPA_ContextStateVk*>(pContextState);
        GPA_SoftwareCounters* pSwCounters =
            m_pContextState->m_pCounterAccessor->GetSoftwareCounters();
        const size_t counterCount = pCounters->size();
        m_activeCountersList.resize(counterCount);

        gpa_uint32 hardwareCountersCount = m_pContextState->m_pCounterAccessor->GetHardwareCounters()->GetNumCounters();

        for (size_t ci = 0; result && (ci < counterCount) ; ++ci)
        {
            gpa_uint32 swCounterIndex = (*pCounters)[ci];
            m_activeCountersList[ci].m_index =
                s_pSwCounterManager->GetSwCounterPubIndex(swCounterIndex);

            // software counter indices are after the hardware counter
            gpa_uint32 counterIdDriver = pSwCounters->m_counters[swCounterIndex - hardwareCountersCount].m_counterIdDriver;
            m_activeCountersList[ci].m_queryType = static_cast<GPA_VK_SW_QUERY_TYPE>(counterIdDriver);
            result = (counterIdDriver < sizeof(m_activeQueries));

            if (result)
            {
                m_activeQueries |= (0x1 << counterIdDriver);
            }
        }

        if (result)
        {
            m_commandList = static_cast<VkCommandBuffer>(pSampleList);

            unsigned int activeQueries = m_activeQueries;
            bool beginQuery = (0 != activeQueries);
            result = m_pContextState->BeginSwSample(m_commandList, m_swSampleId);

            if (result)
            {
                while (beginQuery)
                {
                    GPA_VK_SW_QUERY_TYPE queryType;
#ifdef _WIN32
                    _BitScanForward(reinterpret_cast<unsigned long*>(&queryType), activeQueries);
#else
                    queryType = static_cast<GPA_VK_SW_QUERY_TYPE>(__builtin_clz(activeQueries)); // TODO: verify that this works
#endif
                    m_pContextState->BeginSwQuery(m_commandList, m_swSampleId, queryType);
                    activeQueries &= ~(0x1 << static_cast<unsigned int>(queryType));
                    beginQuery = (0 != activeQueries);
                }

                SetActiveCountersCount(counterCount);
            }
        }
    }

    return result;
}

bool VkSoftwareCounterDataRequest::EndRequest()
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
            GPA_VK_SW_QUERY_TYPE queryType;
#ifdef _WIN32
            _BitScanForward(reinterpret_cast<unsigned long*>(&queryType), activeQueries);
#else
            queryType = static_cast<GPA_VK_SW_QUERY_TYPE>(__builtin_clz(activeQueries)); //TODO: verify that this works
#endif
            m_pContextState->EndSwQuery(m_commandList, m_swSampleId, queryType);
            activeQueries &= ~(0x1 << static_cast<unsigned int>(queryType));
            endQuery = (0 != activeQueries);
        }

        m_pContextState->EndSwSample(m_commandList, m_swSampleId);
    }

    return result;
}

void VkSoftwareCounterDataRequest::ReleaseCounters()
{
}

bool VkSoftwareCounterDataRequest::GetTimestampQueryCounterResult(
    const GpaVkSoftwareQueryResults& queryResults,
    const gpa_uint32 counterIndex,
    gpa_uint64& counterResult)
const
{
    bool result = true;
    const char* pCounterName = m_pContextState->m_pCounterAccessor->GetCounterName(counterIndex);

    if (0 == strcmp("VKGPUTime", pCounterName))
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

bool VkSoftwareCounterDataRequest::GetPipelineQueryCounterResult(
    const GpaVkSoftwareQueryResults& queryResults,
    const gpa_uint32 counterIndex,
    gpa_uint64& counterResult)
const
{
    bool result = true;
    const char* pCounterName = m_pContextState->m_pCounterAccessor->GetCounterName(counterIndex);

    if (0 == strcmp("IAVertices", pCounterName))
    {
        counterResult = queryResults.inputAssemblyVertices;
    }
    else if (0 == strcmp("IAPrimitives", pCounterName))
    {
        counterResult = queryResults.inputAssemblyPrimitives;
    }
    else if (0 == strcmp("VSInvocations", pCounterName))
    {
        counterResult = queryResults.vertexShaderInvocations;
    }
    else if (0 == strcmp("GSInvocations", pCounterName))
    {
        counterResult = queryResults.geometryShaderInvocations;
    }
    else if (0 == strcmp("GSPrimitives", pCounterName))
    {
        counterResult = queryResults.geometryShaderPrimitives;
    }
    else if (0 == strcmp("CInvocations", pCounterName))
    {
        counterResult = queryResults.clippingInvocations;
    }
    else if (0 == strcmp("CPrimitives", pCounterName))
    {
        counterResult = queryResults.clippingPrimitives;
    }
    else if (0 == strcmp("PSInvocations", pCounterName))
    {
        counterResult = queryResults.fragmentShaderInvocations;
    }
    else if (0 == strcmp("TCSInvocations", pCounterName))
    {
        counterResult = queryResults.tessellationControlShaderPatches;
    }
    else if (0 == strcmp("TESInvocations", pCounterName))
    {
        counterResult = queryResults.tessellationEvaluationShaderInvocations;
    }
    else if (0 == strcmp("CSInvocations", pCounterName))
    {
        counterResult = queryResults.computeShaderInvocations;
    }
    else
    {
        result = false;
    }

    return result;
}
