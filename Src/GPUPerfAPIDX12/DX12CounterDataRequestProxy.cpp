//==============================================================================
// Copyright (c) 2015-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12CounterDataRequestProxy implementation
//==============================================================================

#include "DX12CounterDataRequestProxy.h"

#include <GPAContextState.h>
#include <GPAHardwareCounters.h>
#include <GPASoftwareCounters.h>

#include "DX12HardwareCounterDataRequest.h"
#include "DX12SoftwareCounterDataRequest.h"

DX12CounterDataRequestProxy::DX12CounterDataRequestProxy()
    :
    DX12DataRequest(),
    m_pDataRequest(nullptr)
{
}

DX12CounterDataRequestProxy::~DX12CounterDataRequestProxy()
{
    delete m_pDataRequest;
    m_pDataRequest = nullptr;
}

bool DX12CounterDataRequestProxy::CollectResults(GPASampleCounterResults& resultStorage)
{
    bool result = (nullptr != m_pDataRequest);

    if (result)
    {
        result = m_pDataRequest->CollectResults(resultStorage);
    }

    return result;
}

bool DX12CounterDataRequestProxy::BeginRequest(
    GPA_ContextState* pContextState,
    void* pSampleList,
    gpa_uint32 selectionID,
    const vector<gpa_uint32>* pCounters)
{
    bool result = true;
    GPA_HardwareCounters* pHwCounters = pContextState->m_pCounterAccessor->GetHardwareCounters();
    GPA_SoftwareCounters* pSwCounters = pContextState->m_pCounterAccessor->GetSoftwareCounters();
    GPACounterGroupAccessor counterAccessor(
        pHwCounters->m_pGroups,
        pHwCounters->m_groupCount,
        pHwCounters->m_pAdditionalGroups,
        pHwCounters->m_additionalGroupCount,
        pSwCounters->m_pGroups,
        pSwCounters->m_groupCount);
    counterAccessor.SetCounterIndex((*pCounters)[0]); // First counter sets which request to create

    if (counterAccessor.IsSWCounter())
    {
        m_pDataRequest = new(std::nothrow) DX12SoftwareCounterDataRequest;
    }
    else if (counterAccessor.IsHWCounter())
    {
        m_pDataRequest = new(std::nothrow) DX12HardwareCounterDataRequest;
    }
    else
    {
        GPA_LogError("Unknown Counter type.");
        result = false;
    }

    if (nullptr == m_pDataRequest)
    {
        result = false;
    }
    else
    {
        result = m_pDataRequest->BeginRequest(pContextState, pSampleList, selectionID, pCounters);

        if (result)
        {
            m_activeCounters = m_pDataRequest->NumActiveCounters();
        }
    }

    return result;
}

bool DX12CounterDataRequestProxy::EndRequest()
{
    bool result = (nullptr != m_pDataRequest);

    if (result)
    {
        result = m_pDataRequest->EndRequest();
    }

    return result;
}

void DX12CounterDataRequestProxy::ReleaseCounters()
{
    if (nullptr != m_pDataRequest)
    {
        m_pDataRequest->ReleaseCounters();
    }
}
