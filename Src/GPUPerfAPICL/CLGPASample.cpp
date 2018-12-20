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
#include "CLGPAPass.h"
#include "GPAContextCounterMediator.h"

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

    CounterCount counterCount = GetPass()->GetEnabledCounterCount();

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
                    GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = m_clCounterBlocks[blockID]->GetResult(counterID);
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

bool CLGPASample::BeginRequest()
{
    bool success = true;

    if (nullptr != m_pCLGpaContext)
    {
        CounterCount counterCount = GetPass()->GetEnabledCounterCount();

        m_pClCounters = new(std::nothrow) CLCounter[counterCount];

        if (nullptr == m_pClCounters)
        {
            GPA_LogError("Unable to allocate memory for CL counters.");
            return false;
        }

        IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(m_pCLGpaContext);
        const GPA_HardwareCounters* pHardwareCounters = pCounterAccessor->GetHardwareCounters();

        bool populateCounterInfoStatus = true;
        unsigned int counterGroupSize = 0u;

        auto PopulateCLPerFCounterInfo = [&](GroupCountersPair groupCountersPair) -> bool
        {
            bool counterStatus = true;

            gpa_uint32 maxCountersEnabled = static_cast<gpa_uint32>(pHardwareCounters->m_pGroups[groupCountersPair.first].m_maxActiveCounters);
            clPerfCounterBlock* clBlock = nullptr;

            clBlock = new(std::nothrow) clPerfCounterBlock(m_pCLGpaContext->GetCLDeviceId(), groupCountersPair.first, maxCountersEnabled, groupCountersPair.second);

            if (nullptr == clBlock)
            {
                GPA_LogError("Unable to allocate memory for CL counter blocks.");
                counterStatus = false;
            }
            else
            {
                m_clCounterBlocks.push_back(clBlock);

                // store the opencl counters into an array so we can use one call of clEnqueueBeginPerfCounterAMD for all of them
                cl_perfcounter_amd* pClCounters = clBlock->GetCounterArray(0);

                for (gpa_uint32 i = 0; i < clBlock->GetCounterCount(); ++i)
                {
                    m_clCounterList.push_back(pClCounters[i]);
                }
            }

            populateCounterInfoStatus &= counterStatus;
            counterGroupSize++;
            return counterStatus;
        };

        CLGPAPass* pClGpaPass = reinterpret_cast<CLGPAPass*>(GetPass());

        // loop through the requested counters and create and enable them
        pClGpaPass->IterateCLCounterMap(PopulateCLPerFCounterInfo);

        assert(m_clCounterBlocks.size() == counterGroupSize);

        if (CL_SUCCESS != my_clEnqueueBeginPerfCounterAMD(m_pCLGpaContext->GetCLCommandQueue(),
                                                          static_cast<cl_uint>(m_clCounterList.size()),
                                                          &m_clCounterList[0],
                                                          0, 0, 0))
        {
            //Reset(selectionID, pCounters);
            return false;
        }

        unsigned int counterCountIter = 0;

        auto AddClCounterToSample = [&](const CounterIndex& counterIndex)->bool
        {
            const GPA_HardwareCounterDescExt* pCounter = pCounterAccessor->GetHardwareCounterExt(counterIndex);

            // GPA_LogDebugMessage( "ENABLED COUNTER: %x.", m_pCounters[i] );
            m_pClCounters[counterCountIter].m_counterID = counterIndex;
            m_pClCounters[counterCountIter].m_counterGroup = pCounter->m_groupIdDriver;
            m_pClCounters[counterCountIter].m_counterIndex = static_cast<gpa_uint32>(pCounter->m_pHardwareCounter->m_counterIndexInGroup);
            counterCountIter++;
            return true;
        };

        pClGpaPass->IterateEnabledCounterList(AddClCounterToSample);

    }
    else
    {
        GPA_LogError("CL Context is not initialized.");
        success = false;
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
