//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage the resources used for DX12 SW queries
//==============================================================================

#include "DX12CommandListSWQueryGroup.h"

const D3D12_QUERY_TYPE DX12CommandListSWQueryGroup::ms_queryTypes[] =
{
    D3D12_QUERY_TYPE_OCCLUSION,
    D3D12_QUERY_TYPE_BINARY_OCCLUSION,
    D3D12_QUERY_TYPE_TIMESTAMP,
    D3D12_QUERY_TYPE_PIPELINE_STATISTICS,
};


DX12CommandListSWQueryGroup::DX12CommandListSWQueryGroup()
    :
    m_maxSamples(0),
    m_sampleCount(0),
    m_commandList(),
    m_queriesResultsResource(),
    m_pQueriesResults(),
    m_queriesSessionIdsResource()
{
}

DX12CommandListSWQueryGroup::DX12CommandListSWQueryGroup(DX12CommandListSWQueryGroup&& other)
    :
    m_maxSamples(other.m_maxSamples),
    m_sampleCount(other.m_sampleCount),
    m_commandList(other.m_commandList),
    m_queriesResultsResource(other.m_queriesResultsResource),
    m_pQueriesResults(other.m_pQueriesResults),
    m_queriesSessionIdsResource(other.m_queriesSessionIdsResource)
{
    other.m_commandList.Release();

    for (size_t qi = 0; (ms_queryTypeCount > qi); ++qi)
    {
        m_queries[qi] = other.m_queries[qi];
        other.m_queries[qi].Release();
    }

    other.m_queriesResultsResource.Release();
    other.m_pQueriesResults = nullptr;
    other.m_queriesSessionIdsResource.Release();
} // end of DX12CommandListSWQueryGroup::DX12CommandListSWQueryGroup

DX12CommandListSWQueryGroup::~DX12CommandListSWQueryGroup()
{
    Cleanup();
} // end of DX12CommandListSWQueryGroup::~DX12CommandListSWQueryGroup

DX12CommandListSWQueryGroup& DX12CommandListSWQueryGroup::operator=(DX12CommandListSWQueryGroup&& other)
{
    m_maxSamples = other.m_maxSamples;
    m_sampleCount = other.m_sampleCount;

    m_commandList = other.m_commandList;
    other.m_commandList.Release();

    for (size_t qi = 0; (ms_queryTypeCount > qi); ++qi)
    {
        m_queries[qi] = other.m_queries[qi];
        other.m_queries[qi].Release();
    }

    m_queriesResultsResource = other.m_queriesResultsResource;
    other.m_queriesResultsResource.Release();
    m_pQueriesResults = other.m_pQueriesResults;
    other.m_pQueriesResults = nullptr;
    m_queriesSessionIdsResource = other.m_queriesSessionIdsResource;
    other.m_queriesSessionIdsResource.Release();
    return (*this);
} // end of DX12CommandListSWQueryGroup::operator=

bool DX12CommandListSWQueryGroup::Initialize(ID3D12DevicePtr& device, ID3D12GraphicsCommandListPtr& commandList, size_t groupSize)
{
    bool result = true;
    m_maxSamples = groupSize;

    if (nullptr == m_queriesResultsResource)
    {

        result = CreateSwQueriesResultsResources(device);

        if (nullptr == m_queriesSessionIdsResource)
        {
            result = CreateQueriesIdsResource(device);

            for (size_t qi = 0; (ms_queryTypeCount > qi) && result; ++qi)
            {
                if (nullptr == m_queries[qi])
                {
                    result = CreateSwQueryHeap(device, static_cast<D3D12_QUERY_TYPE>(qi));

                    if (result)
                    {
                        m_commandList = commandList;
                    }
                }
            }
        }
    }

    if (!result)
    {
        Cleanup();
    }

    return result;
} // end of DX12CommandListSWQueryGroup::Initialize

void DX12CommandListSWQueryGroup::Cleanup()
{
    if (nullptr != m_queriesSessionIdsResource)
    {
        m_queriesSessionIdsResource.Release();
    }

    if (nullptr != m_queriesResultsResource)
    {
        m_pQueriesResults = nullptr;
        m_queriesResultsResource->Unmap(0, nullptr);
        m_queriesResultsResource.Release();
    }

    for (size_t qti = 0; ms_queryTypeCount > qti; ++qti)
    {
        if (nullptr != m_queries[qti])
        {
            m_queries[qti].Release();
        }
    }

    if (nullptr != m_commandList)
    {
        m_commandList.Release();
    }
} // end of DX12CommandListSWQueryGroup::Cleanup

gpa_uint32 DX12CommandListSWQueryGroup::GetSampleCount() const
{
    return m_sampleCount;
}

void DX12CommandListSWQueryGroup::BeginSwSample()
{
    m_sampleCount++;
} // end of DX12CommandListSWQueryGroup::BeginSwSample

void DX12CommandListSWQueryGroup::EndSwSample(const gpa_uint32 swSampleId)
{
    UINT64 queryResultsReadySrcOffset = (swSampleId * sizeof(UINT64));
    UINT64 queryResultsReadyDstOffset = ((swSampleId * sizeof(DX12SoftwareCountersResults))
                                         + DX12SoftwareCountersResults::QueryReadyEventOffset);

    m_commandList->CopyBufferRegion(
        m_queriesResultsResource,
        queryResultsReadyDstOffset,
        m_queriesSessionIdsResource,
        queryResultsReadySrcOffset,
        sizeof(UINT64));
} // end of DX12CommandListSWQueryGroup::EndSwSample

void DX12CommandListSWQueryGroup::ReleaseSwSample(const gpa_uint32 swSampleId)
{
    memset(&(m_pQueriesResults[swSampleId]), 0, sizeof(m_pQueriesResults[swSampleId]));
    m_sampleCount--; // TODO: note this only makes sense if you don't release some samples while others are still active -- if you do this, then the indeces get messed up and you need to use something akin to m_freeQueryIds
} // end of DX12CommandListSWQueryGroup::ReleaseSwSample

void DX12CommandListSWQueryGroup::BeginSwQuery(
    const gpa_uint32 swSampleId, const D3D12_QUERY_TYPE queryType)
{
    if (D3D12_QUERY_TYPE_TIMESTAMP != queryType)
    {
        m_commandList->BeginQuery(m_queries[queryType], queryType, swSampleId);
    }
    else
    {
        m_commandList->EndQuery(m_queries[queryType], queryType, swSampleId);
        UINT64 queryResultOffset = swSampleId * sizeof(DX12SoftwareCountersResults)
                                   + DX12SoftwareCountersResults::TimestampBeginOffset;
        m_commandList->ResolveQueryData(
            m_queries[queryType],
            queryType,
            swSampleId,
            1,
            m_queriesResultsResource,
            queryResultOffset);
    }
} // end of DX12CommandListSWQueryGroup::BeginSwQuery

void DX12CommandListSWQueryGroup::EndSwQuery(
    const gpa_uint32 swSampleId, const D3D12_QUERY_TYPE queryType)
{
    m_commandList->EndQuery(m_queries[queryType], queryType, swSampleId);
    static const UINT64 resultOffsets[] =
    {
        DX12SoftwareCountersResults::OcclusionOffset,
        DX12SoftwareCountersResults::BinaryOcclusionOffset,
        DX12SoftwareCountersResults::TimestampEndOffset,
        DX12SoftwareCountersResults::PipelineStatisticsOffset,
    };
    UINT64 queryResultOffset = swSampleId * sizeof(DX12SoftwareCountersResults)
                               + resultOffsets[queryType];
    m_commandList->ResolveQueryData(
        m_queries[queryType],
        queryType,
        swSampleId,
        1,
        m_queriesResultsResource,
        queryResultOffset);
} // end of DX12CommandListSWQueryGroup::EndSwQuery

bool DX12CommandListSWQueryGroup::GetSwSampleResults(
    const gpa_uint32 swSampleId, DX12SoftwareCountersResults& queryResults)
{
    bool result = (
                      GetQueryId(swSampleId) == m_pQueriesResults[swSampleId].queryReadyEvent);

    if (result)
    {
        queryResults = m_pQueriesResults[swSampleId];
    }

    return result;
} // end of DX12CommandListSWQueryGroup::GetSwSampleResults

bool DX12CommandListSWQueryGroup::CreateSwQueryHeap(ID3D12DevicePtr& device, const D3D12_QUERY_TYPE queryType)
{
    bool result = true;
    D3D12_QUERY_HEAP_DESC queryHeapDesc;
    memset(&queryHeapDesc, 0, sizeof(queryHeapDesc));

    switch (queryType)
    {
        case D3D12_QUERY_TYPE_OCCLUSION:
            queryHeapDesc.Type = D3D12_QUERY_HEAP_TYPE_OCCLUSION;
            break;

        case D3D12_QUERY_TYPE_BINARY_OCCLUSION:
            queryHeapDesc.Type = D3D12_QUERY_HEAP_TYPE_OCCLUSION;
            break;

        case D3D12_QUERY_TYPE_TIMESTAMP:
            queryHeapDesc.Type = D3D12_QUERY_HEAP_TYPE_TIMESTAMP;
            break;

        case D3D12_QUERY_TYPE_PIPELINE_STATISTICS:
            queryHeapDesc.Type = D3D12_QUERY_HEAP_TYPE_PIPELINE_STATISTICS;
            break;
    }

    queryHeapDesc.Count = (UINT)m_maxSamples /* * 2 */;
    ID3D12QueryHeap* pQueryHeap = nullptr;
    result = (S_OK == device->CreateQueryHeap(
                  &queryHeapDesc, __uuidof(ID3D12QueryHeap), reinterpret_cast<void**>(&pQueryHeap)));

    if (result)
    {
        pQueryHeap->SetName(L"GPUPerfAPIDX12 Query Heap");
        m_queries[queryType] = pQueryHeap;
        pQueryHeap->Release();
    }

    return result;
} // end of DX12CommandListSWQueryGroup::CreateSwQueryHeap

bool DX12CommandListSWQueryGroup::CreateSwQueriesResultsResources(ID3D12DevicePtr& device)
{
    static const size_t resultsBufferSize =
        sizeof(DX12SoftwareCountersResults) * m_maxSamples;
    D3D12_HEAP_PROPERTIES heapProperties;
    memset(&heapProperties, 0, sizeof(D3D12_HEAP_PROPERTIES));
    heapProperties.Type = D3D12_HEAP_TYPE_READBACK;
    heapProperties.CreationNodeMask = 1;
    heapProperties.VisibleNodeMask = 1;
    D3D12_RESOURCE_DESC resourceDesc;
    memset(&resourceDesc, 0, sizeof(D3D12_RESOURCE_DESC));
    resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    resourceDesc.Width = resultsBufferSize;
    resourceDesc.Height = 1;
    resourceDesc.DepthOrArraySize = 1;
    resourceDesc.MipLevels = 1;
    resourceDesc.SampleDesc.Count = 1;
    resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    ID3D12Resource* pResource = nullptr;
    bool result = (S_OK == device->CreateCommittedResource(
                       &heapProperties,
                       D3D12_HEAP_FLAG_NONE, // D3D12_HEAP_MISC_DENY_TEXTURES,
                       &resourceDesc,
                       D3D12_RESOURCE_STATE_COPY_DEST,
                       nullptr, // optimized clear value
                       __uuidof(ID3D12Resource),
                       reinterpret_cast<void**>(&pResource)));

    if (result)
    {
        pResource->SetName(L"GPUPerfAPIDX12 Query Results Buffer");
        D3D12_RANGE mapRange = { 0, resultsBufferSize };
        void* pData = nullptr;
        result = (S_OK == pResource->Map(0, &mapRange, &pData));

        if (result)
        {
            memset(pData, 0, resultsBufferSize);
            m_pQueriesResults = static_cast<DX12SoftwareCountersResults*>(pData);
            m_queriesResultsResource = pResource;
        }

        pResource->Release();
    }

    return result;
} // end of DX12CommandListSWQueryGroup::CreateSwQueriesResultsResources

bool DX12CommandListSWQueryGroup::CreateQueriesIdsResource(ID3D12DevicePtr& device)
{
    static const size_t sessionIdResourceSize = sizeof(UINT64) * m_maxSamples;
    D3D12_HEAP_PROPERTIES heapProperties;
    memset(&heapProperties, 0, sizeof(D3D12_HEAP_PROPERTIES));
    heapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
    heapProperties.CreationNodeMask = 1;
    heapProperties.VisibleNodeMask = 1;
    D3D12_RESOURCE_DESC resourceDesc;
    memset(&resourceDesc, 0, sizeof(D3D12_RESOURCE_DESC));
    resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    resourceDesc.Width = sessionIdResourceSize;
    resourceDesc.Height = 1;
    resourceDesc.DepthOrArraySize = 1;
    resourceDesc.MipLevels = 1;
    resourceDesc.SampleDesc.Count = 1;
    resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    ID3D12Resource* pResource = nullptr;
    bool result = (S_OK == device->CreateCommittedResource(
                       &heapProperties,
                       D3D12_HEAP_FLAG_NONE, // D3D12_HEAP_MISC_DENY_TEXTURES,
                       &resourceDesc,
                       D3D12_RESOURCE_STATE_GENERIC_READ,
                       nullptr, // optimized clear value
                       __uuidof(ID3D12Resource),
                       reinterpret_cast<void**>(&pResource)));

    if (result)
    {
        pResource->SetName(L"GPUPerfAPIDX12 Query Ids");
        D3D12_RANGE mapRange = { 0, sessionIdResourceSize };
        UINT64* pSessionIds = nullptr;
        result = (S_OK == pResource->Map(0, &mapRange, reinterpret_cast<void**>(&pSessionIds)));

        if (result)
        {
            for (size_t si = 0; m_maxSamples > si; ++si)
            {
                pSessionIds[si] = GetQueryId(si);
            }

            pResource->Unmap(0, nullptr);
            m_queriesSessionIdsResource = pResource;
        }

        pResource->Release();
    }

    return result;
} // end of DX12CommandListSWQueryGroup::CreateQueriesIdsResource

UINT64 DX12CommandListSWQueryGroup::GetQueryId(const UINT64 session)
{
    static const UINT64 sessionIdPrefix = 0x69AD3D12i64;
    return ((sessionIdPrefix << 32) + session);
} // end of DX12CommandListSWQueryGroup::GetQueryId
