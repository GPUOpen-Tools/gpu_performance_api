//==============================================================================
// Copyright (c) 2015-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  VkGPASoftwareSample implementation
//==============================================================================

#include "VkGPASoftwareSample.h"
#include "VkGPAContext.h"
#include "VkGPACommandList.h"
#include "GPASoftwareCounters.h"
#include "GPAHardwareCounters.h"
#include "VkGPAPass.h"
#include "GPAContextCounterMediator.h"

VkGPASoftwareSample::VkGPASoftwareSample(GPAPass* pPass,
                                         IGPACommandList* pCmdList,
                                         unsigned int sampleId)
    :
    VkGPASample(pPass, pCmdList, GpaSampleType::Software, sampleId),
    m_pContextState(nullptr),
    m_activeCountersList(),
    m_activeQueries(0),
    m_commandList(m_pVkGpaCmdList->GetVkCommandBuffer()),
    m_swSampleId(ms_unitializedSampleId),
    m_pSwQueries(nullptr)
{
}

VkGPASoftwareSample::~VkGPASoftwareSample()
{
    m_pContextState = nullptr;
    m_activeCountersList.clear();
    m_activeQueries = 0;
    m_swSampleId = ms_unitializedSampleId;
}

void VkGPASoftwareSample::AssignQueries(VkCommandListSwQueries* pSwQueries)
{
    m_pSwQueries = pSwQueries;
}

bool VkGPASoftwareSample::BeginRequest()
{
    bool result = true;

    if ((nullptr != m_pContextState) || (nullptr == m_pVkGpaCmdList))
    {
        result = false;
    }
    else
    {
        VkGPAPass* pVkGpaPass = reinterpret_cast<VkGPAPass*>(GetPass());
        m_pContextState = reinterpret_cast<VkGPAContext*>(pVkGpaPass->GetGpaSession()->GetParentContext());
        const size_t counterCount = pVkGpaPass->GetEnabledCounterCount();

        const IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(m_pContextState);
        const GPA_SoftwareCounters* pSwCounters = pCounterAccessor->GetSoftwareCounters();
        const GPA_HardwareCounters* pHwCounters = pCounterAccessor->GetHardwareCounters();
        m_activeCountersList.resize(counterCount);

        gpa_uint32 hardwareCountersCount = pHwCounters->GetNumCounters();

        unsigned int counterIter = 0u;
        bool bCounterInfoCollected = true;

        auto PopulateSoftwareCounterInfo = [&](const CounterIndex & counterIndex) -> bool
        {
            bool bIsCounterEnabled = true;
            gpa_uint32 swCounterIndex = counterIndex;
            m_activeCountersList[counterIter].m_index =
            SwCounterManager::Instance()->GetSwCounterPubIndex(swCounterIndex);

            // software counter indices are after the hardware counter
            gpa_uint32 counterIdDriver = pSwCounters->m_counters[swCounterIndex - hardwareCountersCount].m_counterIdDriver;
            m_activeCountersList[counterIter].m_queryType = static_cast<GPA_VK_SW_QUERY_TYPE>(counterIdDriver);
            bIsCounterEnabled = (counterIdDriver < sizeof(m_activeQueries));

            if (bIsCounterEnabled)
            {
                m_activeQueries |= (0x1 << counterIdDriver);
            }

            counterIter++;
            bCounterInfoCollected &= bIsCounterEnabled;
            return bIsCounterEnabled;
        };

        pVkGpaPass->IterateEnabledCounterList(PopulateSoftwareCounterInfo);
        result = bCounterInfoCollected;

        if (result)
        {
            unsigned int activeQueries = m_activeQueries;
            bool beginQuery = (0 != activeQueries);
            result = m_pSwQueries->BeginSwSample(m_swSampleId);

            if (result)
            {
                while (beginQuery)
                {
                    GPA_VK_SW_QUERY_TYPE queryType;
#ifdef _WIN32
                    _BitScanForward(reinterpret_cast<unsigned long*>(&queryType), activeQueries);
#else
                    queryType = static_cast<GPA_VK_SW_QUERY_TYPE>(__builtin_clz(activeQueries)); // TODO: verify that this works
#endif
                    m_pSwQueries->BeginSwQuery(m_swSampleId, queryType);
                    activeQueries &= ~(0x1 << static_cast<unsigned int>(queryType));
                    beginQuery = (0 != activeQueries);
                }
            }
        }
    }

    return result;
}

bool VkGPASoftwareSample::EndRequest()
{
    bool result = true;

    if (nullptr == m_pContextState)
    {
        result = false;
    }
    else
    {
        unsigned int activeQueries = m_activeQueries;
        bool endQuery = (0 != activeQueries);

        while (endQuery)
        {
            GPA_VK_SW_QUERY_TYPE queryType;
#ifdef _WIN32
            _BitScanForward(reinterpret_cast<unsigned long*>(&queryType), activeQueries);
#else
            queryType = static_cast<GPA_VK_SW_QUERY_TYPE>(__builtin_clz(activeQueries)); //TODO: verify that this works
#endif
            m_pSwQueries->EndSwQuery(m_swSampleId, queryType);
            activeQueries &= ~(0x1 << static_cast<unsigned int>(queryType));
            endQuery = (0 != activeQueries);
        }

        m_pSwQueries->EndSwSample(m_swSampleId);
    }

    return result;
}

void VkGPASoftwareSample::ReleaseCounters()
{
}

bool VkGPASoftwareSample::GetTimestampQueryCounterResult(
    const GpaVkSoftwareQueryResults& queryResults,
    const gpa_uint32 counterIndex,
    gpa_uint64& counterResult)
const
{
    bool result = true;

    IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(m_pContextState);
    const char* pCounterName = pCounterAccessor->GetCounterName(counterIndex);

    if (0 == strcmp("VKGPUTime", pCounterName))
    {
        counterResult = (queryResults.timestampEnd - queryResults.timestampBegin);
    }
    else if (0 == strcmp("PreBottomTimestamp", pCounterName))
    {
        counterResult = queryResults.timestampBegin;
    }
    else if (0 == strcmp("PostBottomTimestamp", pCounterName))
    {
        counterResult = queryResults.timestampEnd;
    }
    else
    {
        result = false;
    }

    return result;
}

bool VkGPASoftwareSample::GetPipelineQueryCounterResult(
    const GpaVkSoftwareQueryResults& queryResults,
    const gpa_uint32 counterIndex,
    gpa_uint64& counterResult)
const
{
    bool result = true;
    const IGPACounterAccessor* pCounterAccessor = GPAContextCounterMediator::Instance()->GetCounterAccessor(m_pContextState);
    const char* pCounterName = pCounterAccessor->GetCounterName(counterIndex);

    if (0 == strcmp("IAVertices", pCounterName))
    {
        counterResult = queryResults.inputAssemblyVertices;
    }
    else if (0 == strcmp("IAPrimitives", pCounterName))
    {
        counterResult = queryResults.inputAssemblyPrimitives;
    }
    else if (0 == strcmp("VSInvocations", pCounterName))
    {
        counterResult = queryResults.vertexShaderInvocations;
    }
    else if (0 == strcmp("GSInvocations", pCounterName))
    {
        counterResult = queryResults.geometryShaderInvocations;
    }
    else if (0 == strcmp("GSPrimitives", pCounterName))
    {
        counterResult = queryResults.geometryShaderPrimitives;
    }
    else if (0 == strcmp("CInvocations", pCounterName))
    {
        counterResult = queryResults.clippingInvocations;
    }
    else if (0 == strcmp("CPrimitives", pCounterName))
    {
        counterResult = queryResults.clippingPrimitives;
    }
    else if (0 == strcmp("PSInvocations", pCounterName))
    {
        counterResult = queryResults.fragmentShaderInvocations;
    }
    else if (0 == strcmp("TCSInvocations", pCounterName))
    {
        counterResult = queryResults.tessellationControlShaderPatches;
    }
    else if (0 == strcmp("TESInvocations", pCounterName))
    {
        counterResult = queryResults.tessellationEvaluationShaderInvocations;
    }
    else if (0 == strcmp("CSInvocations", pCounterName))
    {
        counterResult = queryResults.computeShaderInvocations;
    }
    else
    {
        result = false;
    }

    return result;
}

bool VkGPASoftwareSample::UpdateResults()
{
    if (GPASampleState::RESULTS_COLLECTED == GetGpaSampleState())
    {
        return true;
    }

    bool isUpdated = false;

    if (IsSecondary())
    {
        MarkAsCompleted();
        isUpdated = true;
    }

    if (GPASampleState::PENDING_RESULTS == GetGpaSampleState() && !IsSecondary())
    {
        GpaVkSoftwareQueryResults queryResults = {};
        memset(&queryResults, 0, sizeof(queryResults));

        if (nullptr != m_pSwQueries)
        {
            if (m_pSwQueries->GetSwSampleResults(m_swSampleId, queryResults))
            {
                GetSampleResultLocation()->SetNumCounters(m_activeCountersList.size());
                const size_t counterCount = m_activeCountersList.size();
                isUpdated = (counterCount == GetSampleResultLocation()->GetNumCounters());

                for (size_t ci = 0; isUpdated && (counterCount > ci); ++ci)
                {
                    switch (m_activeCountersList[ci].m_queryType)
                    {
                        case GPA_VK_QUERY_TYPE_OCCLUSION:
                            GetSampleResultLocation()->GetResultBuffer()[ci] = queryResults.occlusion;
                            break;

                        case GPA_VK_QUERY_TYPE_OCCLUSION_BINARY:
                            GetSampleResultLocation()->GetResultBuffer()[ci] = queryResults.occlusionBinary;
                            break;

                        case GPA_VK_QUERY_TYPE_TIMESTAMP:
                            isUpdated = GetTimestampQueryCounterResult(
                                            queryResults,
                                            m_activeCountersList[ci].m_index,
                                            GetSampleResultLocation()->GetResultBuffer()[ci]);
                            break;

                        case GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS:
                            isUpdated = GetPipelineQueryCounterResult(
                                            queryResults,
                                            m_activeCountersList[ci].m_index,
                                            GetSampleResultLocation()->GetResultBuffer()[ci]);
                            break;

                        default:
                            isUpdated = false;
                            break;
                    }
                }

                m_pSwQueries->ReleaseSwSample(m_swSampleId);
            }
        }
    }

    if (isUpdated)
    {
        MarkAsCompleted();
    }

    return isUpdated;
}
