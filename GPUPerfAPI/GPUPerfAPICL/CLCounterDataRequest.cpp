//==============================================================================
// Copyright (c) 2009-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  The OpenCL Data request class
//==============================================================================

#include <assert.h>
#include <math.h>
#include <CL/cl.h>
#include <CL/internal/cl_profile_amd.h>
#include <map>
#include <vector>
#include "CLPerfCounterBlock.h"
#include "CLPerfCounterAMDExtension.h"

#include "CLCounterDataRequest.h"

#ifndef _LINUX
    #include "../GPUPerfAPI-Common/Logging.h"
#endif

CLCounterDataRequest::CLCounterDataRequest()
{
    TRACE_PRIVATE_FUNCTION(CLCounterDataRequest::CONSTRUCTOR);

    m_uCounterSelectionID = 0;
    m_counters            = nullptr;
    m_clEvent             = nullptr;
    m_uDataReadyCount     = 0;
}


CLCounterDataRequest::~CLCounterDataRequest()
{
    TRACE_PRIVATE_FUNCTION(CLCounterDataRequest::DESTRUCTOR);

    ReleaseCounters();

    DeleteCounterBlocks();
    delete[] m_counters;
}

void CLCounterDataRequest::DeleteCounterBlocks()
{
    TRACE_PRIVATE_FUNCTION(CLCounterDataRequest::DeleteCounterBlocks);

    if (!m_clCounterBlocks.empty())
    {
        for (gpa_uint32 i = 0; i < m_clCounterBlocks.size(); ++i)
        {
            delete m_clCounterBlocks[i];
        }
    }

    m_clCounterBlocks.clear();
}

void CLCounterDataRequest::ReleaseCounters()
{
    TRACE_PRIVATE_FUNCTION(CLCounterDataRequest::ReleaseCounters);

    for (gpa_uint32 i = 0; i < m_clCounterBlocks.size(); ++i)
    {
        m_clCounterBlocks[i]->ReleaseCounters();
    }
}

bool CLCounterDataRequest::FindBlockID(gpa_uint32& uBlockID, gpa_uint32 uGroupID)
{
    TRACE_PRIVATE_FUNCTION(CLCounterDataRequest::FindBlockID);

    for (gpa_uint32 i = 0; i < m_clCounterBlocks.size(); ++i)
    {
        if (uGroupID == m_clCounterBlocks[i]->GetBlockID())
        {
            uBlockID = i;
            return true;
        }
    }

    return false;
}

bool CLCounterDataRequest::CollectResults(GPA_CounterResults& resultStorage)
{
    TRACE_PRIVATE_FUNCTION(CLCounterDataRequest::CollectResults);

    if (nullptr == m_clEvent)
    {
        // clEnqueueEndPerfCounterAMD() hasn't been called succesfully
        return false;
    }

    // Get the data from opencl interface
    for (gpa_uint32 i = 0; i < m_clCounterBlocks.size(); ++i)
    {
        m_clCounterBlocks[i]->CollectData(&m_clEvent);
    }

    // get and set the result to m_counters
    for (gpa_uint32 i = 0; i < m_activeCounters; ++i)
    {
        if (!m_counters[i].bCounterResultReady)
        {
            gpa_uint32 uGroupID   = m_counters[i].uCounterGroup;
            gpa_uint32 uCounterID = m_counters[i].uCounterIndex;

            // find the corresponding block with uGroupID
            gpa_uint32 uBlockID = 0;

            if (!FindBlockID(uBlockID, uGroupID))
            {
                // can't find the corresponding block with the group id
                // something must be wrong in the block initialization/creation
                return false;
            }

            if (m_clCounterBlocks[uBlockID]->IsComplete())
            {
                resultStorage.m_pResultBuffer[i] = m_clCounterBlocks[uBlockID]->GetResult(uCounterID);

                m_counters[i].bCounterResultReady = true;
                m_uDataReadyCount++;
            }
        }
    }


    return m_uDataReadyCount == m_activeCounters;
}


void CLCounterDataRequest::Reset(gpa_uint32 uSelectionID, const vector<gpa_uint32>* pCounters)
{
    TRACE_PRIVATE_FUNCTION(CLCounterDataRequest::Reset);

    assert(!m_isRequestStarted);
    assert(!m_isRequestActive);

    // reset object
    const gpa_uint32 uNewActiveCounters = static_cast<gpa_uint32>(pCounters->size());

    GPA_HardwareCounters* pHardwareCounters = getCurrentContext()->m_pCounterAccessor->GetHardwareCounters();

    if (m_uCounterSelectionID != uSelectionID || m_activeCounters != uNewActiveCounters)
    {
        // release existing counters, cannot reuse
        ReleaseCounters();

        if (m_activeCounters != uNewActiveCounters)
        {
            // need to reallocate buffers
            delete[] m_counters;
            DeleteCounterBlocks();
            m_clCounterBlocks.reserve(pHardwareCounters->m_groupCount);

            m_counters = new(std::nothrow) CLCounter[uNewActiveCounters];

            if (nullptr == m_counters)
            {
                GPA_LogError("Unable to allocate memory for CL counters");
                return;
            }

            m_pclCounters.clear();
            m_pclCounters.reserve(pHardwareCounters->m_groupCount); // incorrect size but start with a reasonable number
        }

        m_uCounterSelectionID = uSelectionID;
        m_activeCounters     = uNewActiveCounters;
    }

    assert(nullptr != m_counters);
    assert(m_activeCounters == uNewActiveCounters);

    for (gpa_uint32 i = 0 ; i < m_activeCounters ; i++)
    {
        m_counters[i].bCounterResultReady = false;
    }

    m_uDataReadyCount = 0;
}


bool CLCounterDataRequest::BeginRequest(GPA_ContextState* pContextState, gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters)
{
    TRACE_PRIVATE_FUNCTION(CLCounterDataRequest::Begin);

    UNREFERENCED_PARAMETER(pContextState);

    // reset object since may be reused
    Reset(selectionID, pCounters);

    GPA_HardwareCounters* pHardwareCounters = getCurrentContext()->m_pCounterAccessor->GetHardwareCounters();

    gpa_uint32 uGroups = (gpa_uint32)(pHardwareCounters->m_groupCount);
    uGroups;

    std::map< gpa_uint32, vector<cl_ulong> > groupCounters;

    // loop through requested counters and group them by their group id
    for (gpa_uint32 i = 0; i < m_activeCounters; ++i)
    {
        // need to Enable counters
        GPA_HardwareCounterDescExt* pCounter = getCurrentContext()->m_pCounterAccessor->GetHardwareCounterExt((*pCounters)[i]);

        gpa_uint32 uGroupIndex = pCounter->m_groupIndex;
        assert(uGroupIndex <= uGroups);

        gpa_uint64 uCounters = pHardwareCounters->m_pGroups[uGroupIndex].m_numCounters;
        uCounters;
        assert(pCounter->m_pHardwareCounter->m_counterIndexInGroup <= uCounters);

        groupCounters[uGroupIndex].push_back(pCounter->m_pHardwareCounter->m_counterIndexInGroup);
    }

    // loop through the requested counters and create and enable them
    for (std::map< gpa_uint32, vector<cl_ulong> >::iterator it = groupCounters.begin();
         it != groupCounters.end();
         ++it)
    {
        gpa_uint32 uMaxCountersEnabled = (gpa_uint32)pHardwareCounters->m_pGroups[it->first].m_maxActiveCounters;
        clPerfCounterBlock* cBlock = nullptr;

        cBlock = new(std::nothrow) clPerfCounterBlock(getCurrentContext()->m_clDevice,
                                                      it->first,
                                                      uMaxCountersEnabled,
                                                      it->second);

        if (nullptr == cBlock)
        {
            GPA_LogError("Unable to allocate memory for CL counter blocks");
            Reset(selectionID, pCounters);
            return false;
        }

        m_clCounterBlocks.push_back(cBlock);

        // store the opencl counters into an array so we can use one call of clEnqueueBeginPerfCounterAMD for all of them
        cl_perfcounter_amd* pclCounters = cBlock->GetCounterArray(0);

        for (gpa_uint32 i = 0; i < cBlock->GetCounterCount(); ++i)
        {
            m_pclCounters.push_back(pclCounters[i]);
        }
    }

    assert(m_clCounterBlocks.size() == groupCounters.size());

    if (CL_SUCCESS != my_clEnqueueBeginPerfCounterAMD((cl_command_queue) getCurrentContext()->m_pContext,
                                                      (cl_uint) m_pclCounters.size(),
                                                      &m_pclCounters[0],
                                                      0, 0, 0))
    {
        Reset(selectionID, pCounters);
        return false;
    }

    for (gpa_uint32 i = 0; i < m_activeCounters; ++i)
    {
        GPA_HardwareCounterDescExt* pCounter = getCurrentContext()->m_pCounterAccessor->GetHardwareCounterExt((*pCounters)[i]);

        // GPA_LogDebugMessage( "ENABLED COUNTER: %x", m_counters[i] );

        m_counters[i].uCounterID    = (*pCounters)[i];
        m_counters[i].uCounterGroup = pCounter->m_groupIdDriver;
        m_counters[i].uCounterIndex = (gpa_uint32)pCounter->m_pHardwareCounter->m_counterIndexInGroup;
    }

    return true;
}


bool CLCounterDataRequest::EndRequest()
{
    TRACE_PRIVATE_FUNCTION(CLCounterDataRequest::End);

    if (CL_SUCCESS != my_clEnqueueEndPerfCounterAMD((cl_command_queue) getCurrentContext()->m_pContext,
                                                    (cl_uint) m_pclCounters.size(),
                                                    &m_pclCounters[0],
                                                    0, 0, &m_clEvent))
    {
        return false;
    }

    return true;
}
