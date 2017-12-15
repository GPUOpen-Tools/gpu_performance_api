//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  D3D11 Software counter data request
//==============================================================================

#include <assert.h>
#include "D3D11SoftwareCounterDataRequest.h"
#include "..\GPUPerfAPI-Common\Logging.h"
#include "..\GPUPerfAPICounterGenerator\GPASwCounterManager.h"

D3D11SoftwareCounterDataRequest::D3D11SoftwareCounterDataRequest(GPA_DataRequest* pParentCounter):
    m_parentCounter(pParentCounter)
{
    TRACE_PRIVATE_FUNCTION(D3D11SoftwareCounterDataRequest::CONSTRUCTOR);
    m_D3d11QueryData.m_timeStampFirst  = 0;
    m_D3d11QueryData.m_timeStampSecond = 0;
    m_numAMDCounters = getCurrentContext()->m_pCounterAccessor->GetNumAMDCounters();
    m_numSwCounters = SwCounterManager::Instance()->GetNumSwCounters();
}

D3D11SoftwareCounterDataRequest::~D3D11SoftwareCounterDataRequest()
{
    TRACE_PRIVATE_FUNCTION(D3D11SoftwareCounterDataRequest::DESTRUCTOR);

    m_device             = nullptr;
    m_D3DContext         = nullptr;
    m_pEnabledSwCounters = nullptr;
}

void D3D11SoftwareCounterDataRequest::ReleaseCounters()
{
}

bool D3D11SoftwareCounterDataRequest::IsSWGPUTimeCounterActive()
{
    gpa_uint32 index = SwCounterManager::Instance()->GetSwGPUTimeCounterIndex();

    for (size_t i = 0; i < m_activeSWCountersVec.size(); i++)
    {
        if (index == m_activeSWCountersVec[i])
        {
            return true;
        }
    }

    return false;
}

bool D3D11SoftwareCounterDataRequest::IsSWCounterActive()
{
    return (m_activeSWCountersVec.size() > 0);
}

gpa_uint64 D3D11SoftwareCounterDataRequest::GetSWD3DCounterData(gpa_uint32 index)
{
    gpa_uint64 result = 0;

    if (!SwCounterManager::Instance()->SwCounterEnabled())
    {
        return result;
    }

    if (nullptr == m_D3DContext)
    {
        GPA_LogError("m_D3DContext is NULL.");
        return result;
    }

    //adjust index for SW D3D counters
    if (index >= m_numAMDCounters)
    {
        index -= m_numAMDCounters;
    }

    if (index >= SwCounterManager::Instance()->GetNumSwCounters())
    {
        GPA_LogError("D3D11SoftwareCounterDataRequest::GetSWD3DCounterData(): index out of range.");
        return result;
    }

    D3DCOUNTERS counterIndex = static_cast<D3DCOUNTERS>(index);

    if (!IsSWGPUTimeCounterActive())
    {
        //pipelineStatsQuery
        while (S_FALSE == m_D3DContext->GetData(m_D3d11Query.m_pipelineStatsQuery, nullptr, 0, 0))
        {
            Sleep(0);
        }

        HRESULT hResult = S_OK;

        hResult = m_D3DContext->GetData(m_D3d11Query.m_pipelineStatsQuery, &m_D3d11QueryData.m_pipelineStats, sizeof(m_D3d11QueryData.m_pipelineStats), 0);

        if (hResult != S_OK)
        {
            GPA_LogError("D3d11 pipelineStatsQuery GetData failed.");
        }

        //occlusionQuery
        while (S_FALSE == m_D3DContext->GetData(m_D3d11Query.m_occlusionQuery, nullptr, 0, 0))
        {
            Sleep(0);
        }

        hResult = m_D3DContext->GetData(m_D3d11Query.m_occlusionQuery, &m_D3d11QueryData.m_samplesPassed, sizeof(m_D3d11QueryData.m_samplesPassed), 0);

        if (hResult != S_OK)
        {
            GPA_LogError("D3d11 occlusionQuery GetData failed.");
        }

        //occlusionPredQuery
        while (S_FALSE == m_D3DContext->GetData(m_D3d11Query.m_occlusionPredQuery, nullptr, 0, 0))
        {
            Sleep(0);
        }

        hResult = m_D3DContext->GetData(m_D3d11Query.m_occlusionPredQuery, &m_D3d11QueryData.m_anySamplePassed, sizeof(m_D3d11QueryData.m_anySamplePassed), 0);

        if (hResult != S_OK)
        {
            GPA_LogError("D3d11 occlusionPredQuery GetData failed.");
        }

        //soStatsQuery
        while (S_FALSE == m_D3DContext->GetData(m_D3d11Query.m_soStatsQuery, nullptr, 0, 0))
        {
            Sleep(0);
        }

        hResult = m_D3DContext->GetData(m_D3d11Query.m_soStatsQuery, &m_D3d11QueryData.m_soStats, sizeof(m_D3d11QueryData.m_soStats), 0);

        if (hResult != S_OK)
        {
            GPA_LogError("D3d11 soStatsQuery GetData failed.");
        }

        //soOverflowPredQuery
        while (S_FALSE == m_D3DContext->GetData(m_D3d11Query.m_soOverflowPredQuery, nullptr, 0, 0))
        {
            Sleep(0);
        }

        hResult = m_D3DContext->GetData(m_D3d11Query.m_soOverflowPredQuery, &m_D3d11QueryData.m_soOverFlow, sizeof(m_D3d11QueryData.m_soOverFlow), 0);

        if (hResult != S_OK)
        {
            GPA_LogError("D3d11 soOverflowPredQuery GetData failed.");
        }

        //soStatsS0Query
        while (S_FALSE == m_D3DContext->GetData(m_D3d11Query.m_soStatsS0Query, nullptr, 0, 0))
        {
            Sleep(0);
        }

        hResult = m_D3DContext->GetData(m_D3d11Query.m_soStatsS0Query, &m_D3d11QueryData.m_soStatsS0, sizeof(m_D3d11QueryData.m_soStatsS0), 0);

        if (hResult != S_OK)
        {
            GPA_LogError("D3d11 soStatsS0Query GetData failed.");
        }

        //soOverflowPredS0Query
        while (S_FALSE == m_D3DContext->GetData(m_D3d11Query.m_soOverflowPredS0Query, nullptr, 0, 0))
        {
            Sleep(0);
        }

        hResult = m_D3DContext->GetData(m_D3d11Query.m_soOverflowPredS0Query, &m_D3d11QueryData.m_soS0OverFlow, sizeof(m_D3d11QueryData.m_soS0OverFlow), 0);

        if (hResult != S_OK)
        {
            GPA_LogError("D3d11 soOverflowPredS0Query GetData failed.");
        }

        //soStatsS1Query
        while (S_FALSE == m_D3DContext->GetData(m_D3d11Query.m_soStatsS1Query, nullptr, 0, 0))
        {
            Sleep(0);
        }

        hResult = m_D3DContext->GetData(m_D3d11Query.m_soStatsS1Query, &m_D3d11QueryData.m_soStatsS1, sizeof(m_D3d11QueryData.m_soStatsS1), 0);

        if (hResult != S_OK)
        {
            GPA_LogError("D3d11 soStatsS1Query GetData failed.");
        }

        //soOverflowPredS1Query
        while (S_FALSE == m_D3DContext->GetData(m_D3d11Query.m_soOverflowPredS1Query, nullptr, 0, 0))
        {
            Sleep(0);
        }

        hResult = m_D3DContext->GetData(m_D3d11Query.m_soOverflowPredS1Query, &m_D3d11QueryData.m_soS1OverFlow, sizeof(m_D3d11QueryData.m_soS1OverFlow), 0);

        if (hResult != S_OK)
        {
            GPA_LogError("D3d11 soOverflowPredS1Query GetData failed.");
        }

        //soStatsS2Query
        while (S_FALSE == m_D3DContext->GetData(m_D3d11Query.m_soStatsS2Query, nullptr, 0, 0))
        {
            Sleep(0);
        }

        hResult = m_D3DContext->GetData(m_D3d11Query.m_soStatsS2Query, &m_D3d11QueryData.m_soStatsS2, sizeof(m_D3d11QueryData.m_soStatsS2), 0);

        if (hResult != S_OK)
        {
            GPA_LogError("D3d11 soStatsS2Query GetData failed.");
        }

        //soOverflowPredS2Query
        while (S_FALSE == m_D3DContext->GetData(m_D3d11Query.m_soOverflowPredS2Query, nullptr, 0, 0))
        {
            Sleep(0);
        }

        hResult = m_D3DContext->GetData(m_D3d11Query.m_soOverflowPredS2Query, &m_D3d11QueryData.m_soS2OverFlow, sizeof(m_D3d11QueryData.m_soS2OverFlow), 0);

        if (hResult != S_OK)
        {
            GPA_LogError("D3d11 soOverflowPredS2Query GetData failed.");
        }

        //soStatsS3Query
        while (S_FALSE == m_D3DContext->GetData(m_D3d11Query.m_soStatsS3Query, nullptr, 0, 0))
        {
            Sleep(0);
        }

        hResult = m_D3DContext->GetData(m_D3d11Query.m_soStatsS3Query, &m_D3d11QueryData.m_soStatsS3, sizeof(m_D3d11QueryData.m_soStatsS3), 0);

        if (hResult != S_OK)
        {
            GPA_LogError("D3d11 soStatsS3Query GetData failed.");
        }

        //soOverflowPredS3Query
        while (S_FALSE == m_D3DContext->GetData(m_D3d11Query.m_soOverflowPredS3Query, nullptr, 0, 0))
        {
            Sleep(0);
        }

        hResult = m_D3DContext->GetData(m_D3d11Query.m_soOverflowPredS3Query, &m_D3d11QueryData.m_soS3OverFlow, sizeof(m_D3d11QueryData.m_soS3OverFlow), 0);

        if (hResult != S_OK)
        {
            GPA_LogError("D3d11 soOverflowPredS3Query GetData failed.");
        }

    }

    switch (counterIndex)
    {
        case D3DCOUNTERS::GPUTIME:
            result = GetGPUTime();
            break;

        case D3DCOUNTERS::OCCLUSION:
            result = m_D3d11QueryData.m_samplesPassed;
            break;

        case D3DCOUNTERS::IAVERTICES:
            result = m_D3d11QueryData.m_pipelineStats.IAVertices;
            break;

        case D3DCOUNTERS::IAPRIMITIVES:
            result = m_D3d11QueryData.m_pipelineStats.IAPrimitives;
            break;

        case D3DCOUNTERS::VSINVOCATIONS:
            result = m_D3d11QueryData.m_pipelineStats.VSInvocations;
            break;

        case D3DCOUNTERS::GSINVOCATIONS:
            result = m_D3d11QueryData.m_pipelineStats.GSInvocations;
            break;

        case D3DCOUNTERS::GSPRIMITIVES:
            result = m_D3d11QueryData.m_pipelineStats.GSPrimitives;
            break;

        case D3DCOUNTERS::CINVOCATIONS:
            result = m_D3d11QueryData.m_pipelineStats.CInvocations;
            break;

        case D3DCOUNTERS::CPRIMITIVES:
            result = m_D3d11QueryData.m_pipelineStats.CPrimitives;
            break;

        case D3DCOUNTERS::PSINVOCATIONS:
            result = m_D3d11QueryData.m_pipelineStats.PSInvocations;
            break;

        case D3DCOUNTERS::HSINVOCATIONS:
            result = m_D3d11QueryData.m_pipelineStats.HSInvocations;
            break;

        case D3DCOUNTERS::DSINVOCATIONS:
            result = m_D3d11QueryData.m_pipelineStats.DSInvocations;
            break;

        case D3DCOUNTERS::CSINVOCATIONS:
            result = m_D3d11QueryData.m_pipelineStats.CSInvocations;
            break;

        case D3DCOUNTERS::OCCLUSIONPREDICATE:
            result = (gpa_uint64) m_D3d11QueryData.m_anySamplePassed;
            break;

        case D3DCOUNTERS::SOPRIMSWRITTEN:
            result = m_D3d11QueryData.m_soStats.NumPrimitivesWritten;
            break;

        case D3DCOUNTERS::SOPRIMSSTORAGENEED:
            result = m_D3d11QueryData.m_soStats.PrimitivesStorageNeeded;
            break;

        case D3DCOUNTERS::SOOVERFLOWPRED:
            result = (gpa_uint64) m_D3d11QueryData.m_soOverFlow;
            break;

        case D3DCOUNTERS::PRIMSWRITTEN_S0:
            result = m_D3d11QueryData.m_soStatsS0.NumPrimitivesWritten;
            break;

        case D3DCOUNTERS::PRIMSSTORAGENEED_S0:
            result = m_D3d11QueryData.m_soStatsS0.PrimitivesStorageNeeded;
            break;

        case D3DCOUNTERS::OVERFLOWPRED_S0:
            result = (gpa_uint64) m_D3d11QueryData.m_soOverFlow;
            break;

        case D3DCOUNTERS::PRIMSWRITTEN_S1:
            result = m_D3d11QueryData.m_soStatsS1.NumPrimitivesWritten;
            break;

        case D3DCOUNTERS::PRIMSSTORAGENEED_S1:
            result = m_D3d11QueryData.m_soStatsS1.PrimitivesStorageNeeded;
            break;

        case D3DCOUNTERS::OVERFLOWPRED_S1:
            result = (gpa_uint64) m_D3d11QueryData.m_soS1OverFlow;
            break;

        case D3DCOUNTERS::PRIMSWRITTEN_S2:
            result = m_D3d11QueryData.m_soStatsS2.NumPrimitivesWritten;
            break;

        case D3DCOUNTERS::PRIMSSTORAGENEED_S2:
            result = m_D3d11QueryData.m_soStatsS2.PrimitivesStorageNeeded;
            break;

        case D3DCOUNTERS::OVERFLOWPRED_S2:
            result = (gpa_uint64) m_D3d11QueryData.m_soS2OverFlow;
            break;

        case D3DCOUNTERS::PRIMSWRITTEN_S3:
            result = m_D3d11QueryData.m_soStatsS3.NumPrimitivesWritten;
            break;

        case D3DCOUNTERS::PRIMSSTORAGENEED_S3:
            result = m_D3d11QueryData.m_soStatsS3.PrimitivesStorageNeeded;
            break;

        case D3DCOUNTERS::OVERFLOWPRED_S3:
            result = (gpa_uint64) m_D3d11QueryData.m_soS3OverFlow;
            break;

        default:
            result = 0;
            break;
    }

    return result;
}

gpa_uint64 D3D11SoftwareCounterDataRequest::GetGPUTime()
{
    gpa_uint64 result = 0;

    if (IsSWGPUTimeCounterActive())
    {

        HRESULT hr = S_FALSE;

        do
        {
            hr = m_D3DContext->GetData(m_D3d11Query.m_timeStampDisjointQuery, &m_D3d11QueryData.m_disjointData, sizeof(D3D11_QUERY_DATA_TIMESTAMP_DISJOINT), 0);
        }
        while (S_FALSE == hr);

        assert(hr == S_OK);

        do
        {
            hr = m_D3DContext->GetData(m_D3d11Query.m_timeStampFirstQuery, &m_D3d11QueryData.m_timeStampFirst, sizeof(UINT64), 0);
        }
        while (S_FALSE == hr);

        assert(hr == S_OK);

        do
        {
            hr = m_D3DContext->GetData(m_D3d11Query.m_timeStampSecondQuery, &m_D3d11QueryData.m_timeStampSecond, sizeof(UINT64), 0);
        }
        while (S_FALSE == hr);

        assert(hr == S_OK);

        result = m_D3d11QueryData.m_timeStampSecond - m_D3d11QueryData.m_timeStampFirst;

    }

    return result;
}

bool D3D11SoftwareCounterDataRequest::CollectResults(GPASampleResult& resultStorage, size_t numActiveCounters, gpa_uint32 sampleId)
{
    TRACE_PRIVATE_FUNCTION(D3D11SoftwareCounterDataRequest::CollectResults);

    UNREFERENCED_PARAMETER(sampleId);

    //Collect SW D3D counter results
    if (SwCounterManager::Instance()->SwCounterEnabled())
    {
        resultStorage.m_numResults = numActiveCounters;

        for (size_t i = 0; i < m_activeSWCountersVec.size(); i++)
        {
            resultStorage.m_pResultBuffer[i] = GetSWD3DCounterData(m_activeSWCountersVec[i]);
        }
    }

    return true;
}

bool D3D11SoftwareCounterDataRequest::BeginRequest(GPA_ContextState* pContextState, gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters)
{
    TRACE_PRIVATE_FUNCTION(D3D11SoftwareCounterDataRequest::BeginRequest);

    m_activeSWCountersVec.clear();
    Reset(selectionID, pCounters);

    m_pEnabledSwCounters = SwCounterManager::Instance()->GetEnabledSwCounters();

    m_device = static_cast<ID3D11Device*>(pContextState->m_pContext);

    if (nullptr == m_device)
    {
        GPA_LogError("D3D11SoftwareCounterDataRequest::BeginRequest(): m_device is NULL.");
        return false;
    }

    m_device->GetImmediateContext(&m_D3DContext);

    if (nullptr == m_D3DContext)
    {
        GPA_LogError("D3D11SoftwareCounterDataRequest::BeginRequest(): m_D3DContext is NULL.");
        return false;
    }

    //Only create SW D3D11 counter queries if one or more D3D11 counter(s) enabled
    if (SwCounterManager::Instance()->SwCounterEnabled())
    {
        HRESULT hr = E_FAIL;
        D3D11_QUERY_DESC desc;
        desc.MiscFlags = 0;

        if (IsSWGPUTimeCounterActive())
        {
            desc.Query = D3D11_QUERY_TIMESTAMP;
            hr = m_device->CreateQuery(&desc, &m_D3d11Query.m_timeStampFirstQuery);

            if (S_OK != hr)
            {
                GPA_LogError("CreateQuery(timeStampFirstQuery) failed.");
                return false;
            }

            hr = m_device->CreateQuery(&desc, &m_D3d11Query.m_timeStampSecondQuery);

            if (S_OK != hr)
            {
                GPA_LogError("CreateQuery(m_TimeStampSecondQuery) failed.");
                return false;
            }

            desc.Query = D3D11_QUERY_TIMESTAMP_DISJOINT;
            hr = m_device->CreateQuery(&desc, &m_D3d11Query.m_timeStampDisjointQuery);

            if (S_OK != hr)
            {
                GPA_LogError("CreateQuery(timeStampDisjointQuery) failed.");
                return false;
            }

            // Submit the disjoint query
            m_D3DContext->Begin(m_D3d11Query.m_timeStampDisjointQuery);
            // End the first time stamp query
            m_D3DContext->End(m_D3d11Query.m_timeStampFirstQuery);
        }
        else if (IsSWCounterActive())  //other SW counter active in current pass
        {
            desc.Query = D3D11_QUERY_OCCLUSION;
            hr = m_device->CreateQuery(&desc, &m_D3d11Query.m_occlusionQuery);

            if (S_OK != hr)
            {
                GPA_LogError("CreateQuery(occlusionQuery) failed.");
                return false;
            }

            desc.Query = D3D11_QUERY_PIPELINE_STATISTICS;
            hr = m_device->CreateQuery(&desc, &m_D3d11Query.m_pipelineStatsQuery);

            if (S_OK != hr)
            {
                GPA_LogError("CreateQuery(pipelineStatsQuery) failed.");
                return false;
            }

            desc.Query = D3D11_QUERY_OCCLUSION_PREDICATE;
            hr = m_device->CreateQuery(&desc, &m_D3d11Query.m_occlusionPredQuery);

            if (S_OK != hr)
            {
                GPA_LogError("CreateQuery(occlusionPredQuery) failed.");
                return false;
            }

            desc.Query = D3D11_QUERY_SO_STATISTICS;
            hr = m_device->CreateQuery(&desc, &m_D3d11Query.m_soStatsQuery);

            if (S_OK != hr)
            {
                GPA_LogError("CreateQuery(soStatsQuery) failed.");
                return false;
            }

            desc.Query = D3D11_QUERY_SO_OVERFLOW_PREDICATE;
            hr = m_device->CreateQuery(&desc, &m_D3d11Query.m_soOverflowPredQuery);

            if (S_OK != hr)
            {
                GPA_LogError("CreateQuery(soOverflowPredQuery) failed.");
                return false;
            }

            desc.Query = D3D11_QUERY_SO_STATISTICS_STREAM0;
            hr = m_device->CreateQuery(&desc, &m_D3d11Query.m_soStatsS0Query);

            if (S_OK != hr)
            {
                GPA_LogError("CreateQuery(soStatsS0Query) failed.");
                return false;
            }

            desc.Query = D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM0;
            hr = m_device->CreateQuery(&desc, &m_D3d11Query.m_soOverflowPredS0Query);

            if (S_OK != hr)
            {
                GPA_LogError("CreateQuery(soOverflowPredS0Query) failed.");
                return false;
            }

            desc.Query = D3D11_QUERY_SO_STATISTICS_STREAM1;
            hr = m_device->CreateQuery(&desc, &m_D3d11Query.m_soStatsS1Query);

            if (S_OK != hr)
            {
                GPA_LogError("CreateQuery(soStatsS1Query) failed.");
                return false;
            }

            desc.Query = D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM1;
            hr = m_device->CreateQuery(&desc, &m_D3d11Query.m_soOverflowPredS1Query);

            if (S_OK != hr)
            {
                GPA_LogError("CreateQuery(soOverflowPredS1Query) failed.");
                return false;
            }

            desc.Query = D3D11_QUERY_SO_STATISTICS_STREAM2;
            hr = m_device->CreateQuery(&desc, &m_D3d11Query.m_soStatsS2Query);

            if (S_OK != hr)
            {
                GPA_LogError("CreateQuery(soStatsS2Query) failed.");
                return false;
            }

            desc.Query = D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM2;
            hr = m_device->CreateQuery(&desc, &m_D3d11Query.m_soOverflowPredS2Query);

            if (S_OK != hr)
            {
                GPA_LogError("CreateQuery(soOverflowPredS2Query) failed.");
                return false;
            }

            desc.Query = D3D11_QUERY_SO_STATISTICS_STREAM3;
            hr = m_device->CreateQuery(&desc, &m_D3d11Query.m_soStatsS3Query);

            if (S_OK != hr)
            {
                GPA_LogError("CreateQuery(soStatsS3Query) failed.");
                return false;
            }

            desc.Query = D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM3;
            hr = m_device->CreateQuery(&desc, &m_D3d11Query.m_soOverflowPredS3Query);

            if (S_OK != hr)
            {
                GPA_LogError("CreateQuery(soOverflowPredS3Query) failed.");
                return false;
            }

            // Begin other queries
            m_D3DContext->Begin(m_D3d11Query.m_pipelineStatsQuery);
            m_D3DContext->Begin(m_D3d11Query.m_occlusionQuery);
            m_D3DContext->Begin(m_D3d11Query.m_occlusionPredQuery);
            m_D3DContext->Begin(m_D3d11Query.m_soStatsQuery);
            m_D3DContext->Begin(m_D3d11Query.m_soOverflowPredQuery);
            m_D3DContext->Begin(m_D3d11Query.m_soStatsS0Query);
            m_D3DContext->Begin(m_D3d11Query.m_soOverflowPredS0Query);
            m_D3DContext->Begin(m_D3d11Query.m_soStatsS1Query);
            m_D3DContext->Begin(m_D3d11Query.m_soOverflowPredS1Query);
            m_D3DContext->Begin(m_D3d11Query.m_soStatsS2Query);
            m_D3DContext->Begin(m_D3d11Query.m_soOverflowPredS2Query);
            m_D3DContext->Begin(m_D3d11Query.m_soStatsS3Query);
            m_D3DContext->Begin(m_D3d11Query.m_soOverflowPredS3Query);
        }
    }

    return true;
}

bool D3D11SoftwareCounterDataRequest::EndRequest()
{
    TRACE_PRIVATE_FUNCTION(D3D11SoftwareCounterDataRequest::EndRequest);

    if (SwCounterManager::Instance()->SwCounterEnabled())
    {
        if (IsSWGPUTimeCounterActive())
        {
            m_D3DContext->End(m_D3d11Query.m_timeStampSecondQuery);
            m_D3DContext->End(m_D3d11Query.m_timeStampDisjointQuery);
        }
        else if (IsSWCounterActive())
        {
            m_D3DContext->End(m_D3d11Query.m_pipelineStatsQuery);
            m_D3DContext->End(m_D3d11Query.m_occlusionQuery);
            m_D3DContext->End(m_D3d11Query.m_occlusionPredQuery);
            m_D3DContext->End(m_D3d11Query.m_soStatsQuery);
            m_D3DContext->End(m_D3d11Query.m_soOverflowPredQuery);
            m_D3DContext->End(m_D3d11Query.m_soStatsS0Query);
            m_D3DContext->End(m_D3d11Query.m_soOverflowPredS0Query);
            m_D3DContext->End(m_D3d11Query.m_soStatsS1Query);
            m_D3DContext->End(m_D3d11Query.m_soOverflowPredS1Query);
            m_D3DContext->End(m_D3d11Query.m_soStatsS2Query);
            m_D3DContext->End(m_D3d11Query.m_soOverflowPredS2Query);
            m_D3DContext->End(m_D3d11Query.m_soStatsS3Query);
            m_D3DContext->End(m_D3d11Query.m_soOverflowPredS3Query);
        }
    }

    return true;
}

void D3D11SoftwareCounterDataRequest::Reset(gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters)
{
    UNREFERENCED_PARAMETER(selectionID);

    // reset object
    const gpa_uint32 newActiveCounters = static_cast<gpa_uint32>(pCounters->size());

    m_parentCounter->SetCounterSelectionID(selectionID);
    m_parentCounter->SetNumActiveCounters(newActiveCounters);

    for (gpa_uint32 ui = 0; ui < newActiveCounters; ui++)
    {
        gpa_uint32 counter = SwCounterManager::Instance()->GetSwCounterPubIndex(pCounters->at(ui));

        gpa_uint32 numAmdSwCounters = m_numAMDCounters + m_numSwCounters;

        if (counter < numAmdSwCounters)
        {
            m_activeSWCountersVec.push_back(counter);  //SW public counter index
        }
    }
}
