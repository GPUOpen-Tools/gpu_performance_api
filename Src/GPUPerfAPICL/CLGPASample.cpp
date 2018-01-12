//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  CL GPA Sample Implementation
//==============================================================================

#include "CLGPAContext.h"
#include "GPAHardwareCounters.h"
#include "GPAPass.h"
#include "CLGPASample.h"
#include "CLPerfCounterBlock.h"
#include "CLPerfCounterAMDExtension.h"

CLGPASample::CLGPASample(GPAPass* pPass,
                         IGPACommandList* pCmdList,
                         GpaSampleType sampleType,
                         ClientSampleId sampleId) :
    GPASample(pPass, pCmdList, sampleType, sampleId),
    m_pClCounters(nullptr),
    m_clEvent(nullptr),
    m_dataReadyCount(0)
{
    if (nullptr != pPass)
    {
        IGPASession* pGpaSession = pPass->GetGpaSession();

        if (nullptr != pGpaSession)
        {
            m_pCLGpaContext = reinterpret_cast<CLGPAContext*>(pGpaSession->GetParentContext());
        }
    }
}

CLGPASample::~CLGPASample()
{
    ReleaseBlockCounters();
    DeleteCounterBlocks();
    delete[] m_pClCounters;
}

bool CLGPASample::UpdateResults()
{
    bool isComplete = false;

    CounterCount counterCount = GetPass()->GetCounterCount();

    if (nullptr != m_clEvent)
    {
        // Get the data from opencl interface
        for (gpa_uint32 i = 0; i < m_clCounterBlocks.size(); ++i)
        {
            m_clCounterBlocks[i]->CollectData(&m_clEvent);
        }

        // get and set the result to m_pCounters
        for (gpa_uint32 i = 0; i < counterCount; ++i)
        {
            if (!m_pClCounters[i].m_isCounterResultReady)
            {
                gpa_uint32 groupID = m_pClCounters[i].m_counterGroup;
                gpa_uint32 counterID = m_pClCounters[i].m_counterIndex;

                // find the corresponding block with uGroupID
                gpa_uint32 blockID = 0;

                if (!FindBlockID(blockID, groupID))
                {
                    // can't find the corresponding block with the group id
                    // something must be wrong in the block initialization/creation
                    return false;
                }

                if (m_clCounterBlocks[blockID]->IsComplete())
                {
                    GetSampleResultLocation()->m_pResultBuffer[i] = m_clCounterBlocks[blockID]->GetResult(counterID);
                    m_pClCounters[i].m_isCounterResultReady = true;
                    m_dataReadyCount++;
                }
            }
        }
    }
    else
    {
        // clEnqueueEndPerfCounterAMD() hasn't been called successfully
    }

    isComplete = m_dataReadyCount == counterCount;

    if (isComplete)
    {
        MarkAsCompleted();
    }

    return isComplete;
}

bool CLGPASample::BeginRequest(IGPAContext* pContextState, const std::vector<gpa_uint32>* pCounters)
{
    bool success = true;
    UNREFERENCED_PARAMETER(pCounters);

    if (nullptr != pContextState &&
        nullptr == m_pCLGpaContext)
    {
        m_pCLGpaContext = reinterpret_cast<CLGPAContext*>(pContextState);
    }

    if (nullptr != m_pCLGpaContext)
    {
        CounterCount counterCount = GetPass()->GetCounterCount();

        m_pClCounters = new(std::nothrow) CLCounter[counterCount];

        if (nullptr == m_pClCounters)
        {
            GPA_LogError("Unable to allocate memory for CL counters.");
            return false;
        }

        const GPA_HardwareCounters* pHardwareCounters = m_pCLGpaContext->GetCounterAccessor()->GetHardwareCounters();

        gpa_uint32 groupCount = static_cast<gpa_uint32>(pHardwareCounters->m_groupCount);
        UNREFERENCED_PARAMETER(groupCount);

        std::map< gpa_uint32, vector<cl_ulong> > groupCounters;

        for (size_t i = 0; i < pCounters->size(); i++)
        {
            const GPA_HardwareCounterDescExt* pCounter = m_pCLGpaContext->GetCounterAccessor()->GetHardwareCounterExt((*pCounters)[i]);

            gpa_uint32 groupIndex = pCounter->m_groupIdDriver;
            assert(groupIndex <= groupCount);

            gpa_uint64 numCounters = pHardwareCounters->m_pGroups[groupIndex].m_numCounters;
            UNREFERENCED_PARAMETER(numCounters);
            assert(pCounter->m_pHardwareCounter->m_counterIndexInGroup <= numCounters);

            groupCounters[groupIndex].push_back(pCounter->m_pHardwareCounter->m_counterIndexInGroup);
        }

        // loop through the requested counters and create and enable them
        for (std::map< gpa_uint32, vector<cl_ulong> >::iterator it = groupCounters.begin();
            it != groupCounters.end();
            ++it)
        {
            gpa_uint32 maxCountersEnabled = static_cast<gpa_uint32>(pHardwareCounters->m_pGroups[it->first].m_maxActiveCounters);
            clPerfCounterBlock* clBlock = nullptr;

            clBlock = new(std::nothrow) clPerfCounterBlock(m_pCLGpaContext->GetCLDeviceId(),
                                                           it->first,
                                                           maxCountersEnabled,
                                                           it->second);

            if (nullptr == clBlock)
            {
                GPA_LogError("Unable to allocate memory for CL counter blocks.");
                return false;
            }

            m_clCounterBlocks.push_back(clBlock);

            // store the opencl counters into an array so we can use one call of clEnqueueBeginPerfCounterAMD for all of them
            cl_perfcounter_amd* pClCounters = clBlock->GetCounterArray(0);

            for (gpa_uint32 i = 0; i < clBlock->GetCounterCount(); ++i)
            {
                m_clCounterList.push_back(pClCounters[i]);
            }
        }

        assert(m_clCounterBlocks.size() == groupCounters.size());

        if (CL_SUCCESS != my_clEnqueueBeginPerfCounterAMD(m_pCLGpaContext->GetCLCommandQueue(),
                                                          static_cast<cl_uint>(m_clCounterList.size()),
                                                          &m_clCounterList[0],
                                                          0, 0, 0))
        {
            //Reset(selectionID, pCounters);
            return false;
        }

        for (gpa_uint32 i = 0; i < counterCount; ++i)
        {
            const GPA_HardwareCounterDescExt* pCounter = m_pCLGpaContext->GetCounterAccessor()->GetHardwareCounterExt((*pCounters)[i]);

            // GPA_LogDebugMessage( "ENABLED COUNTER: %x.", m_pCounters[i] );

            m_pClCounters[i].m_counterID = (*pCounters)[i];
            m_pClCounters[i].m_counterGroup = pCounter->m_groupIdDriver;
            m_pClCounters[i].m_counterIndex = static_cast<gpa_uint32>(pCounter->m_pHardwareCounter->m_counterIndexInGroup);
        }
    }

    return success;
}

bool CLGPASample::EndRequest()
{
    bool success = (CL_SUCCESS == my_clEnqueueEndPerfCounterAMD(m_pCLGpaContext->GetCLCommandQueue(),
                                                                static_cast<cl_uint>(m_clCounterList.size()),
                                                                &m_clCounterList[0],
                                                                0, 0, &m_clEvent));

    return success;
}

void CLGPASample::ReleaseCounters()
{
    ReleaseBlockCounters();
}

bool CLGPASample::FindBlockID(gpa_uint32& blockID, gpa_uint32 groupID)
{
    for (gpa_uint32 i = 0; i < m_clCounterBlocks.size(); ++i)
    {
        if (groupID == m_clCounterBlocks[i]->GetBlockID())
        {
            blockID = i;
            return true;
        }
    }

    return false;
}

void CLGPASample::DeleteCounterBlocks()
{
    if (!m_clCounterBlocks.empty())
    {
        for (gpa_uint32 i = 0; i < m_clCounterBlocks.size(); ++i)
        {
            delete m_clCounterBlocks[i];
        }
    }

    m_clCounterBlocks.clear();
}

void CLGPASample::ReleaseBlockCounters()
{
    for (gpa_uint32 i = 0; i < m_clCounterBlocks.size(); ++i)
    {
        m_clCounterBlocks[i]->ReleaseCounters();
    }
}
