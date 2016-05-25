//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX11 Counter Data Request
//==============================================================================

#include <assert.h>

#include "DX11CounterDataRequest.h"
#include "DX11SoftwareCounterDataRequestManager.h"
#include "DX11_PerfExperimentDataRequestHandler.h"
#include "D3D11SoftwareCounterDataRequest.h"

#include "..\GPUPerfAPI-Common\Logging.h"

/// setup block limits to ensure we only enable counters on available blocks
struct BlockLimits
{
    unsigned int m_blockID; ///< Block Id corresponding to that of the internal counters
    size_t m_limit;         ///< Limit on the number of blocks of the specified type
};

DX11CounterDataRequest::DX11CounterDataRequest() :
    m_pCounterDataRequest(nullptr)
{
    TRACE_PRIVATE_FUNCTION(DX11CounterDataRequest::CONSTRUCTOR);
}

DX11CounterDataRequest::~DX11CounterDataRequest()
{
    TRACE_PRIVATE_FUNCTION(DX11CounterDataRequest::DESTRUCTOR);

    assert(nullptr != m_pCounterDataRequest);

    if (nullptr != m_pCounterDataRequest)
    {
        delete m_pCounterDataRequest;
    }
}

void DX11CounterDataRequest::ReleaseCounters()
{
    TRACE_PRIVATE_FUNCTION(DX11CounterDataRequest::ReleaseCounters);

    assert(nullptr != m_pCounterDataRequest);

    m_pCounterDataRequest->ReleaseCounters();
}

bool DX11CounterDataRequest::CollectResults(GPA_CounterResults& resultStorage)
{
    TRACE_PRIVATE_FUNCTION(DX11CounterDataRequest::CollectResults);

    assert(nullptr != m_pCounterDataRequest);

    bool resultsCollected = m_pCounterDataRequest->CollectResults(resultStorage, m_activeCounters, m_sampleID);

    if (resultsCollected)
    {
        m_activeCounters = 0;
    }

    return resultsCollected;
}

void DX11CounterDataRequest::Reset(gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters)
{
    TRACE_PRIVATE_FUNCTION(DX11CounterDataRequest::Reset);

    assert(nullptr != m_pCounterDataRequest);

    m_pCounterDataRequest->Reset(selectionID, pCounters);
}

bool DX11CounterDataRequest::BeginRequest(GPA_ContextState* pContextState, gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters)
{
    TRACE_PRIVATE_FUNCTION(DX11CounterDataRequest::Begin);

    // Get the HW and SW counters
    GPA_HardwareCounters* pHwCounters = pContextState->m_pCounterAccessor->GetHardwareCounters();
    GPA_SoftwareCounters* pSwCounters = pContextState->m_pCounterAccessor->GetSoftwareCounters();

    // If this request contains software counters, make a software counter data request, otherwise make a hardware data request depending on the API to use
    // NOTE: This assumes that hardware and software counters will not be scheduled in the same pass.
    GPACounterGroupAccessor accessor(pHwCounters->m_pGroups,
                                     pHwCounters->m_groupCount,
                                     pHwCounters->m_pAdditionalGroups,
                                     pHwCounters->m_additionalGroupCount,
                                     pSwCounters->m_pGroups,
                                     pSwCounters->m_groupCount);

    // Use the counter type of the first scheduled counter to determine which data request type to create.
    accessor.SetCounterIndex((*pCounters)[0]);

    if (accessor.IsSWCounter())
    {
        GDT_HW_GENERATION gen = GDT_HW_GENERATION_NONE;

        if (getCurrentContext()->m_hwInfo.GetHWGeneration(gen) == true)
        {
            m_pCounterDataRequest = DX11SoftwareCounterDataRequestManager::Instance()->GetCounterDataRequest(gen, this);
        }

        if (nullptr == m_pCounterDataRequest)
        {
            // Create a SW counter
            m_pCounterDataRequest = new(std::nothrow) D3D11SoftwareCounterDataRequest(this);
        }
    }
    else if (accessor.IsHWCounter())
    {
        DX11_PerfExperimentDataRequestHandler* pPtr = new(std::nothrow) DX11_PerfExperimentDataRequestHandler(this);
        pPtr->Initialize(getCurrentContext()->m_pContext);
        m_pCounterDataRequest = pPtr;
    }
    else
    {
        GPA_LogError("Could not determine whether index is for a hardware or software counter.");
        return false;
    }

    assert(nullptr != m_pCounterDataRequest);

    // Begin the request
    bool requestStarted = m_pCounterDataRequest->BeginRequest(pContextState, selectionID, pCounters);

    if (requestStarted)
    {
        m_activeCounters = pCounters->size();
    }

    return requestStarted;
}

bool DX11CounterDataRequest::EndRequest()
{
    TRACE_PRIVATE_FUNCTION(DX11CounterDataRequest::End);

    assert(nullptr != m_pCounterDataRequest);

    return m_pCounterDataRequest->EndRequest();
}
