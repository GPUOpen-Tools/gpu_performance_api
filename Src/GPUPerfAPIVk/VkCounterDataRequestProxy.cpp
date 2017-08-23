//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  VkCounterDataRequestProxy implementation
//==============================================================================

#include "VkCounterDataRequestProxy.h"

#include <GPAContextState.h>
#include <GPAHardwareCounters.h>
#include <GPASoftwareCounters.h>

#include "VkHardwareCounterDataRequest.h"
#include "VkSoftwareCounterDataRequest.h"

VkCounterDataRequestProxy::VkCounterDataRequestProxy()
    :
    VkDataRequest(),
    m_pDataRequest(nullptr)
{
}

VkCounterDataRequestProxy::~VkCounterDataRequestProxy()
{
    delete m_pDataRequest;
    m_pDataRequest = nullptr;
}

bool VkCounterDataRequestProxy::CollectResults(GPA_CounterResults& resultStorage)
{
    bool result = (nullptr != m_pDataRequest);

    if (result)
    {
        result = m_pDataRequest->CollectResults(resultStorage);
    }

    return result;
}

bool VkCounterDataRequestProxy::BeginRequest(
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
        m_pDataRequest = new(std::nothrow) VkSoftwareCounterDataRequest;
    }
    else if (counterAccessor.IsHWCounter())
    {
        GPA_ContextStateVk* pContext = static_cast<GPA_ContextStateVk*>(pContextState);
        m_pDataRequest = new(std::nothrow) VkHardwareCounterDataRequest(pContext->GetVkDevice());
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
            m_activeCounters = m_pDataRequest->GetActiveCountersCount();
        }
    }

    return result;
}

bool VkCounterDataRequestProxy::EndRequest()
{
    bool result = (nullptr != m_pDataRequest);

    if (result)
    {
        result = m_pDataRequest->EndRequest();
    }

    return result;
}

void VkCounterDataRequestProxy::ReleaseCounters()
{
    if (nullptr != m_pDataRequest)
    {
        m_pDataRequest->ReleaseCounters();
    }
}
