//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA_ContextStateDX12 implementation
//==============================================================================

#include "GPAContextStateDX12.h"

#include <cassert>

GPA_ContextStateDX12::GPA_ContextStateDX12()
    :
    m_device(),
    m_commandList(),
    m_commandListQueries(),
    m_mutex()
{
} // end of GPA_ContextStateDX12::GPA_ContextStateDX12

GPA_ContextStateDX12::~GPA_ContextStateDX12()
{
    Cleanup();
} // end of GPA_ContextStateDX12::~GPA_ContextStateDX12

void GPA_ContextStateDX12::Cleanup()
{
    if (nullptr != m_commandList)
    {
        m_commandList.Release();
    }

    if (nullptr != m_device)
    {
        m_device.Release();
    }
} // end of GPA_ContextStateDX12::Cleanup


bool GPA_ContextStateDX12::SetCommandList(ID3D12GraphicsCommandListPtr pCommandList)
{
    AMDTScopeLock scopeLock(m_mutex);
    bool result = true;

    if (nullptr == pCommandList)
    {
        m_commandList.Release();
        result = false;
    }
    else
    {
        if (m_commandList != pCommandList)
        {
            if (nullptr != m_commandList)
            {
                m_commandList.Release();
            }

            m_commandList = pCommandList;

            HRESULT hr = m_commandList->GetDevice(__uuidof(ID3D12Device), (void**)&m_device);

            result = S_OK == hr;
        }
    }

    return result;
} // end of GPA_ContextStateDX12::SetCommandList

GPA_Status GPA_ContextStateDX12::GetTimestampFrequency(UINT64& timestampFrequency)
{
    GPA_Status result = GPA_STATUS_ERROR_FAILED;

    result = SetStablePowerState(TRUE);

    if (GPA_STATUS_OK == result)
    {
        ID3D12CommandQueue* pQueue = nullptr;
        D3D12_COMMAND_QUEUE_DESC queueDesc;
        ZeroMemory(&queueDesc, sizeof(queueDesc));
        queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        HRESULT hr = m_device->CreateCommandQueue(&queueDesc, __uuidof(ID3D12CommandQueue), (PVOID*)&pQueue);

        if (S_OK != hr || nullptr == pQueue)
        {
            result = GPA_STATUS_ERROR_FAILED;
        }
        else
        {
            UINT64 frequencey = 0;
            hr = pQueue->GetTimestampFrequency(&frequencey);

            if (S_OK != hr)
            {
                result = GPA_STATUS_ERROR_FAILED;
            }
            else
            {
                timestampFrequency = frequencey;
            }

            pQueue->Release();
        }

        result = SetStablePowerState(FALSE);
    }

    return result;
} // end of GPA_ContextStateDX12::GetTimestampFrequency

GPA_Status GPA_ContextStateDX12::BeginSession()
{
    return SetStablePowerState(TRUE);
} // end of GPA_ContextStateDX12::BeginSession

GPA_Status GPA_ContextStateDX12::EndSession()
{
    return SetStablePowerState(FALSE);
} // end of GPA_ContextStateDX12::EndSession

bool GPA_ContextStateDX12::BeginSwSample(
    ID3D12GraphicsCommandListPtr& commandList, gpa_uint32& swSampleId)
{
    bool result = (nullptr != m_commandList.GetInterfacePtr());
    CommandListQueriesType::iterator cmdListQueriesIter = m_commandListQueries.end();

    if (result)
    {
        cmdListQueriesIter = m_commandListQueries.find(m_commandList.GetInterfacePtr());

        if (m_commandListQueries.end() == cmdListQueriesIter)
        {
            DX12CommandListSwQueries cmdListSwQueries;
            result = cmdListSwQueries.Initialize(m_device, m_commandList);

            if (result)
            {
                std::pair<CommandListQueriesType::iterator, bool> insertResult =
                    m_commandListQueries.insert(CommandListQueriesType::value_type(
                                                    m_commandList.GetInterfacePtr(), std::move(cmdListSwQueries)));
                result = insertResult.second;

                if (result)
                {
                    cmdListQueriesIter = insertResult.first;
                }
            }
        }
    }

    if (result)
    {
        result = cmdListQueriesIter->second.BeginSwSample(swSampleId);
        commandList = m_commandList;
    }

    return result;
} // end of GPA_ContextStateDX12::BeginSwSample

void GPA_ContextStateDX12::EndSwSample(
    ID3D12GraphicsCommandListPtr& commandList, const gpa_uint32 swSampleId)
{
    CommandListQueriesType::iterator cmdListIter =
        m_commandListQueries.find(commandList.GetInterfacePtr());
#ifdef _DEBUG
    assert(m_commandListQueries.end() != cmdListIter);
#endif // _DEBUG

    if ((m_commandListQueries.end() != cmdListIter))
    {
        cmdListIter->second.EndSwSample(swSampleId);
    }
} // end of GPA_ContextStateDX12::EndSwSample

void GPA_ContextStateDX12::ReleaseSwSample(
    ID3D12GraphicsCommandListPtr& commandList, const gpa_uint32 swSampleId)
{
    CommandListQueriesType::iterator cmdListIter =
        m_commandListQueries.find(commandList.GetInterfacePtr());
#ifdef _DEBUG
    assert(m_commandListQueries.end() != cmdListIter);
#endif // _DEBUG

    if (m_commandListQueries.end() != cmdListIter)
    {
        cmdListIter->second.ReleaseSwSample(swSampleId);
    }
} // end of GPA_ContextStateDX12::ReleaseSwSample

void GPA_ContextStateDX12::BeginSwQuery(
    ID3D12GraphicsCommandListPtr& commandList,
    const gpa_uint32 swSampleId,
    const D3D12_QUERY_TYPE queryType)
{
    CommandListQueriesType::iterator cmdListIter =
        m_commandListQueries.find(commandList.GetInterfacePtr());
#ifdef _DEBUG
    assert(m_commandListQueries.end() != cmdListIter);
#endif // _DEBUG

    if (m_commandListQueries.end() != cmdListIter)
    {
        cmdListIter->second.BeginSwQuery(swSampleId, queryType);
    }
} // end of GPA_ContextStateDX12::BeginSwQuery

void GPA_ContextStateDX12::EndSwQuery(
    ID3D12GraphicsCommandListPtr& commandList,
    const gpa_uint32 swSampleId,
    const D3D12_QUERY_TYPE queryType)
{
    CommandListQueriesType::iterator cmdListIter =
        m_commandListQueries.find(commandList.GetInterfacePtr());
#ifdef _DEBUG
    assert(m_commandListQueries.end() != cmdListIter);
#endif // _DEBUG

    if (m_commandListQueries.end() != cmdListIter)
    {
        cmdListIter->second.EndSwQuery(swSampleId, queryType);
    }
} // end of GPA_ContextStateDX12::EndSwQuery

bool GPA_ContextStateDX12::GetSwSampleResults(
    ID3D12GraphicsCommandListPtr& commandList,
    const gpa_uint32 swSampleId,
    DX12SoftwareCountersResults& queryResults)
{
    CommandListQueriesType::iterator cmdListIter =
        m_commandListQueries.find(commandList.GetInterfacePtr());
    bool result = (m_commandListQueries.end() != cmdListIter);

    if (result)
    {
        result = cmdListIter->second.GetSwSampleResults(swSampleId, queryResults);
    }

    return result;
} // end of GPA_ContextStateDX12::GetSwSampleResults

inline GPA_Status GPA_ContextStateDX12::SetStablePowerState(BOOL state)
{
    GPA_Status result = GPA_STATUS_OK;
    HRESULT hr = m_device->SetStablePowerState(state);

    if (S_OK != hr)
    {
        result = GPA_STATUS_ERROR_FAILED;
    }

    return result;
} // end of GPA_ContextStateDX12::SetStablePowerState

