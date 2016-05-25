//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12CommandListSwQueries declaration
//==============================================================================

#include "Logging.h"
#include "DX12CommandListSwQueries.h"

DX12CommandListSwQueries::DX12CommandListSwQueries()
    :
    m_commandList(0),
    m_device(0)
{
} // end of DX12CommandListSwQueries::DX12CommandListSwQueries

DX12CommandListSwQueries::DX12CommandListSwQueries(DX12CommandListSwQueries&& other)
    :
    m_queryGroups(std::move(other.m_queryGroups))
{
    m_commandList = other.m_commandList;
    other.m_commandList.Release();

    m_device = other.m_device;
    other.m_device.Release();

    for (auto iterator = m_queryGroups.begin(); iterator != m_queryGroups.end(); ++iterator)
    {
        delete(*iterator);
    }

    m_queryGroups.clear();

    m_queryGroups = std::move(other.m_queryGroups);

} // end of DX12CommandListSwQueries::DX12CommandListSwQueries

DX12CommandListSwQueries::~DX12CommandListSwQueries()
{
    for (auto iterator = m_queryGroups.begin(); iterator != m_queryGroups.end(); ++iterator)
    {
        delete(*iterator);
    }

    m_queryGroups.clear();

    if (nullptr != m_commandList)
    {
        m_commandList.Release();
    }

    if (nullptr != m_device)
    {
        m_device.Release();
    }

} // end of DX12CommandListSwQueries::~DX12CommandListSwQueries

DX12CommandListSwQueries& DX12CommandListSwQueries::operator=(DX12CommandListSwQueries&& other)
{
    m_commandList = other.m_commandList;
    other.m_commandList.Release();

    m_device = other.m_device;
    other.m_device.Release();

    for (auto iterator = m_queryGroups.begin(); iterator != m_queryGroups.end(); ++iterator)
    {
        delete(*iterator);
    }

    m_queryGroups.clear();

    m_queryGroups = std::move(other.m_queryGroups);

    return (*this);
} // end of DX12CommandListSwQueries::operator=

bool DX12CommandListSwQueries::Initialize(
    ID3D12DevicePtr& device, ID3D12GraphicsCommandListPtr& commandList)
{
    m_device = device;
    m_commandList = commandList;

    return true;
} // end of DX12CommandListSwQueries::Initialize

bool DX12CommandListSwQueries::BeginSwSample(gpa_uint32& swSampleId)
{
    bool retVal = true;

    gpa_uint32 curGroupSampleCount = 0;

    if ((0 < m_queryGroups.size()))
    {
        curGroupSampleCount = m_queryGroups.back()->GetSampleCount();
    }

    gpa_uint32 sampleIndex = curGroupSampleCount % ms_resultGroupSize;

    if (sampleIndex == 0)
    {
        if (!CreateNewQueryGroup())
        {
            retVal = false;
        }
        else
        {
            curGroupSampleCount = 0;
        }
    }

    if (retVal)
    {
        DX12CommandListSWQueryGroup* pQueryGroup = m_queryGroups.back();
        pQueryGroup->BeginSwSample();


        gpa_uint32 nextSampleId = (gpa_uint32)(m_queryGroups.size() - 1) * ms_resultGroupSize;
        nextSampleId += curGroupSampleCount;
        swSampleId = nextSampleId;
    }

    return retVal;
} // end of DX12CommandListSwQueries::BeginSwSample


void DX12CommandListSwQueries::EndSwSample(const gpa_uint32 swSampleId)
{
    const gpa_uint32 groupIndex = swSampleId / ms_resultGroupSize;
    const gpa_uint32 sampleIndex = swSampleId % ms_resultGroupSize;

    DX12CommandListSWQueryGroup* pQueryGroup = m_queryGroups[groupIndex];

    pQueryGroup->EndSwSample(sampleIndex);
} // end of DX12CommandListSwQueries::EndSwSample

void DX12CommandListSwQueries::ReleaseSwSample(const gpa_uint32 swSampleId)
{
    const gpa_uint32 groupIndex = swSampleId / ms_resultGroupSize;
    const gpa_uint32 sampleIndex = swSampleId % ms_resultGroupSize;

    DX12CommandListSWQueryGroup* pQueryGroup = m_queryGroups[groupIndex];
    pQueryGroup->ReleaseSwSample(sampleIndex);
} // end of DX12CommandListSwQueries::ReleaseSwSample


void DX12CommandListSwQueries::BeginSwQuery(
    const gpa_uint32 swSampleId, const D3D12_QUERY_TYPE queryType)
{
    const gpa_uint32 groupIndex = swSampleId / ms_resultGroupSize;
    const gpa_uint32 sampleIndex = swSampleId % ms_resultGroupSize;

    DX12CommandListSWQueryGroup* pQueryGroup = m_queryGroups[groupIndex];

    pQueryGroup->BeginSwQuery(sampleIndex, queryType);
} // end of DX12CommandListSwQueries::BeginSwQuery

void DX12CommandListSwQueries::EndSwQuery(
    const gpa_uint32 swSampleId, const D3D12_QUERY_TYPE queryType)
{
    const gpa_uint32 groupIndex = swSampleId / ms_resultGroupSize;
    const gpa_uint32 sampleIndex = swSampleId % ms_resultGroupSize;

    DX12CommandListSWQueryGroup* pQueryGroup = m_queryGroups[groupIndex];

    pQueryGroup->EndSwQuery(sampleIndex, queryType);
} // end of DX12CommandListSwQueries::EndSwQuery

bool DX12CommandListSwQueries::GetSwSampleResults(
    const gpa_uint32 swSampleId, DX12SoftwareCountersResults& queryResults)
{
    const gpa_uint32 groupIndex = swSampleId / ms_resultGroupSize;
    const gpa_uint32 sampleIndex = swSampleId % ms_resultGroupSize;

    DX12CommandListSWQueryGroup* pQueryGroup = m_queryGroups[groupIndex];

    return pQueryGroup->GetSwSampleResults(sampleIndex, queryResults);
} // end of DX12CommandListSwQueries::GetSwSampleResults

bool DX12CommandListSwQueries::CreateNewQueryGroup()
{
    bool retVal = false;

    DX12CommandListSWQueryGroup* queryGroup = new(std::nothrow) DX12CommandListSWQueryGroup();

    if (nullptr == queryGroup)
    {
        GPA_LogError("Unable to allocate memory for software queries");
    }
    else
    {
        retVal = queryGroup->Initialize(m_device, m_commandList, ms_resultGroupSize);

        if (retVal)
        {
            m_queryGroups.push_back(queryGroup);
        }
        else
        {
            delete queryGroup;
        }
    }

    return retVal;
} // end of DX12CommandListSwQueries::CreateNewQueryGroup

