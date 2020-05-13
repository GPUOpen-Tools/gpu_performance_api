//==============================================================================
// Copyright (c) 2015-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage the resources used for Vk SW queries
//==============================================================================
#include <string.h>

#include "logging.h"
#include "vk_command_list_sw_query_group.h"
#include "vk_entry_points.h"

const VkQueryType VkCommandListSWQueryGroup::ms_queryTypes[] = {VK_QUERY_TYPE_OCCLUSION,
                                                                VK_QUERY_TYPE_OCCLUSION,
                                                                VK_QUERY_TYPE_TIMESTAMP,
                                                                VK_QUERY_TYPE_PIPELINE_STATISTICS};

VkCommandListSWQueryGroup::VkCommandListSWQueryGroup()
    : m_maxSamples(0)
    , m_activeSampleCount(0)
    , m_device(VK_NULL_HANDLE)
    , m_commandBuffer(VK_NULL_HANDLE)
    , m_pQueriesResults(nullptr)
{
    for (size_t qi = 0; GPA_VK_QUERY_TYPE_COUNT > qi; ++qi)
    {
        m_queryPools[qi] = VK_NULL_HANDLE;
    }
}

VkCommandListSWQueryGroup::VkCommandListSWQueryGroup(VkCommandListSWQueryGroup&& other)
    : m_maxSamples(other.m_maxSamples)
    , m_activeSampleCount(other.m_activeSampleCount)
    , m_commandBuffer(other.m_commandBuffer)
    , m_pQueriesResults(other.m_pQueriesResults)
{
    for (size_t qi = 0; GPA_VK_QUERY_TYPE_COUNT > qi; ++qi)
    {
        m_queryPools[qi] = other.m_queryPools[qi];
    }

    other.m_pQueriesResults = nullptr;
}

VkCommandListSWQueryGroup::~VkCommandListSWQueryGroup()
{
    Cleanup();
}

VkCommandListSWQueryGroup& VkCommandListSWQueryGroup::operator=(VkCommandListSWQueryGroup&& other)
{
    m_maxSamples        = other.m_maxSamples;
    m_activeSampleCount = other.m_activeSampleCount;
    m_commandBuffer     = other.m_commandBuffer;
    m_device            = other.m_device;

    for (size_t qi = 0; (GPA_VK_QUERY_TYPE_COUNT > qi); ++qi)
    {
        m_queryPools[qi] = other.m_queryPools[qi];
    }

    m_pQueriesResults       = other.m_pQueriesResults;
    other.m_pQueriesResults = nullptr;

    return (*this);
}

bool VkCommandListSWQueryGroup::Initialize(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandBuffer commandBuffer, size_t groupSize)
{
    bool result  = true;
    m_maxSamples = groupSize;

    for (size_t qi = 0; (GPA_VK_QUERY_TYPE_COUNT > qi) && result; ++qi)
    {
        if (VK_NULL_HANDLE == m_queryPools[qi])
        {
            VkBool32 bCreateQueryPool = VK_TRUE;

            if (ms_queryTypes[qi] == VK_QUERY_TYPE_PIPELINE_STATISTICS)
            {
                VkPhysicalDeviceFeatures features;
                _vkGetPhysicalDeviceFeatures(physicalDevice, &features);
                bCreateQueryPool = features.pipelineStatisticsQuery;
            }

            if (bCreateQueryPool == VK_TRUE)
            {
                result &= CreateSwQueryPool(device, (GPA_VK_SW_QUERY_TYPE)qi);

                if (result)
                {
                    // Reset the query pool so that it can be used
                    _vkCmdResetQueryPool(commandBuffer, m_queryPools[qi], 0, (uint32_t)m_maxSamples);
                }
            }
        }
    }

    if (result)
    {
        m_device        = device;
        m_commandBuffer = commandBuffer;

        m_activeSampleQueries.clear();
    }
    else
    {
        Cleanup();
    }

    return result;
}

void VkCommandListSWQueryGroup::Cleanup()
{
    if (nullptr != m_pQueriesResults)
    {
        delete[] m_pQueriesResults;
        m_pQueriesResults = nullptr;
    }

    m_activeSampleQueries.clear();

    if (VK_NULL_HANDLE != m_device)
    {
        VkResult waitResult = _vkDeviceWaitIdle(m_device);

        if (waitResult == VK_SUCCESS)
        {
            for (size_t qti = 0; qti < GPA_VK_QUERY_TYPE_COUNT; ++qti)
            {
                if (VK_NULL_HANDLE != m_queryPools[qti])
                {
                    _vkDestroyQueryPool(m_device, m_queryPools[qti], nullptr);
                }
            }
        }
    }
}

gpa_uint32 VkCommandListSWQueryGroup::GetSampleCount() const
{
    return m_activeSampleCount;
}

void VkCommandListSWQueryGroup::BeginSwSample()
{
    m_activeSampleCount++;
}

void VkCommandListSWQueryGroup::EndSwSample(const gpa_uint32 swSampleIndex)
{
    UNREFERENCED_PARAMETER(swSampleIndex);
}

void VkCommandListSWQueryGroup::ReleaseSwSample(const gpa_uint32 swSampleIndex)
{
    UNREFERENCED_PARAMETER(swSampleIndex);
    memset(&(m_pQueriesResults[swSampleIndex]), 0, sizeof(m_pQueriesResults[swSampleIndex]));
    m_activeSampleCount--;
}

void VkCommandListSWQueryGroup::BeginSwQuery(const gpa_uint32 swSampleIndex, const GPA_VK_SW_QUERY_TYPE queryType)
{
    if (GPA_VK_QUERY_TYPE_TIMESTAMP == queryType)
    {
        _vkCmdWriteTimestamp(m_commandBuffer, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, m_queryPools[queryType], 2 * swSampleIndex);
    }
    else
    {
        VkQueryControlFlags flags = 0;

        if (GPA_VK_QUERY_TYPE_OCCLUSION == queryType)
        {
            flags = VK_QUERY_CONTROL_PRECISE_BIT;
        }

        _vkCmdBeginQuery(m_commandBuffer, m_queryPools[queryType], swSampleIndex, flags);
    }

    m_activeSampleQueries[swSampleIndex][queryType] = true;
}

void VkCommandListSWQueryGroup::EndSwQuery(const gpa_uint32 swSampleIndex, const GPA_VK_SW_QUERY_TYPE queryType)
{
    if (GPA_VK_QUERY_TYPE_TIMESTAMP == queryType)
    {
        _vkCmdWriteTimestamp(m_commandBuffer, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, m_queryPools[queryType], 2 * swSampleIndex + 1);
    }
    else
    {
        _vkCmdEndQuery(m_commandBuffer, m_queryPools[queryType], swSampleIndex);
    }
}

bool VkCommandListSWQueryGroup::GetSwSampleResults(const gpa_uint32 swSampleIndex, GpaVkSoftwareQueryResults& queryResults)
{
    uint64_t* pResultAvailableAddresses[GPA_VK_QUERY_TYPE_COUNT] = {&(m_pQueriesResults[swSampleIndex].occlusionAvailable),
                                                                    &(m_pQueriesResults[swSampleIndex].occlusionBinaryAvailable),
                                                                    &(m_pQueriesResults[2 * swSampleIndex].timestampEndAvailable),
                                                                    &(m_pQueriesResults[swSampleIndex].pipelineStatsAvailable)};

    uint64_t* pResultAddresses[GPA_VK_QUERY_TYPE_COUNT] = {&(m_pQueriesResults[swSampleIndex].occlusion),
                                                           &(m_pQueriesResults[swSampleIndex].occlusionBinary),
                                                           &(m_pQueriesResults[2 * swSampleIndex].timestampBegin),
                                                           &(m_pQueriesResults[swSampleIndex].inputAssemblyVertices)};

    // Initially all results are available.
    bool allResultsAvailable = true;

    for (size_t qti = 0; GPA_VK_QUERY_TYPE_COUNT > qti; ++qti)
    {
        if (m_activeSampleQueries[swSampleIndex][qti] == true)
        {
            VkQueryPool queryPool = m_queryPools[qti];

            if (VK_NULL_HANDLE != queryPool)
            {
                // First, get a copy of the query results.
                uint64_t* pResultAddress = pResultAddresses[qti];
                size_t    resultSize     = ms_gpaVkSoftwareResultSizes[qti];
                size_t    resultStride   = ms_gpaVkSoftwareResultStrides[qti];

                uint32_t queryIndex = swSampleIndex;
                uint32_t numQueries = 1;

                if (qti == GPA_VK_QUERY_TYPE_TIMESTAMP)
                {
                    // timestamp has 2 queries (begin and end)
                    queryIndex = 2 * swSampleIndex;
                    numQueries = 2;
                }

                // get the results back
                // NOTE: because we may loop over this multiple times, it is possible
                // that the query results get updated each time we get them.
                VkResult qpResults = _vkGetQueryPoolResults(m_device,
                                                            queryPool,
                                                            queryIndex,
                                                            numQueries,
                                                            resultSize,
                                                            pResultAddress,
                                                            resultStride,
                                                            VK_QUERY_RESULT_64_BIT | VK_QUERY_RESULT_WITH_AVAILABILITY_BIT);

                allResultsAvailable = (qpResults == VK_SUCCESS);

                if (allResultsAvailable)
                {
                    // Second, Check if the query results availability bit indicated that it was available.
                    uint64_t*  pResultAvailableAddress = pResultAvailableAddresses[qti];
                    gpa_uint64 resultAvailable         = *pResultAvailableAddress;

                    if (resultAvailable == 0)
                    {
                        allResultsAvailable = false;
                    }
                    else
                    {
                        // Result is available, which matches initial assumption.

                        // CAVEAT: There's currently a bug in the availibility bit for PIPELINE_STATISTICS that
                        // it will report available even though all results are 0. So if we encounter this
                        // situation, report that results are actually NOT available.
                        if (qti == GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS && m_pQueriesResults[swSampleIndex].inputAssemblyVertices == 0 &&
                            m_pQueriesResults[swSampleIndex].inputAssemblyPrimitives == 0 && m_pQueriesResults[swSampleIndex].vertexShaderInvocations == 0 &&
                            m_pQueriesResults[swSampleIndex].geometryShaderInvocations == 0 && m_pQueriesResults[swSampleIndex].geometryShaderPrimitives == 0 &&
                            m_pQueriesResults[swSampleIndex].clippingInvocations == 0 && m_pQueriesResults[swSampleIndex].clippingPrimitives == 0 &&
                            m_pQueriesResults[swSampleIndex].fragmentShaderInvocations == 0 &&
                            m_pQueriesResults[swSampleIndex].tessellationControlShaderPatches == 0 &&
                            m_pQueriesResults[swSampleIndex].tessellationEvaluationShaderInvocations == 0 &&
                            m_pQueriesResults[swSampleIndex].computeShaderInvocations == 0)
                        {
                            // CAVEAT: There's currently a bug in the availibility bit that it will report available
                            // even though all results are 0. So if we encounter this situation, report that results
                            // are actually NOT available.
                            allResultsAvailable = false;
                        }
                    }
                }
            }
        }
    }  // end for each query type

    if (allResultsAvailable)
    {
        queryResults = m_pQueriesResults[swSampleIndex];
    }

    return allResultsAvailable;
}

bool VkCommandListSWQueryGroup::CreateSwQueryPool(VkDevice device, const GPA_VK_SW_QUERY_TYPE queryType)
{
    bool                  result = true;
    VkQueryPoolCreateInfo queryPoolDesc;
    memset(&queryPoolDesc, 0, sizeof(queryPoolDesc));
    queryPoolDesc.sType      = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
    queryPoolDesc.queryType  = ms_queryTypes[queryType];
    queryPoolDesc.flags      = 0;
    queryPoolDesc.queryCount = (uint32_t)m_maxSamples;

    if (queryType == GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS)
    {
        queryPoolDesc.pipelineStatistics =
            VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_VERTICES_BIT | VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_PRIMITIVES_BIT |
            VK_QUERY_PIPELINE_STATISTIC_VERTEX_SHADER_INVOCATIONS_BIT | VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_INVOCATIONS_BIT |
            VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_PRIMITIVES_BIT | VK_QUERY_PIPELINE_STATISTIC_CLIPPING_INVOCATIONS_BIT |
            VK_QUERY_PIPELINE_STATISTIC_CLIPPING_PRIMITIVES_BIT | VK_QUERY_PIPELINE_STATISTIC_FRAGMENT_SHADER_INVOCATIONS_BIT |
            VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_CONTROL_SHADER_PATCHES_BIT | VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_EVALUATION_SHADER_INVOCATIONS_BIT |
            VK_QUERY_PIPELINE_STATISTIC_COMPUTE_SHADER_INVOCATIONS_BIT;
    }

    if (queryType == GPA_VK_QUERY_TYPE_TIMESTAMP)
    {
        // we keep track of both begin and end timestamps, so we need 2x as many queries
        queryPoolDesc.queryCount *= 2;
    }

    if (result)
    {
        VkQueryPool queryPool = VK_NULL_HANDLE;
        result                = (VK_SUCCESS == _vkCreateQueryPool(device, &queryPoolDesc, nullptr, &queryPool));

        if (result)
        {
            // TODO: Check for the debugging extension to be able to tag objects with names
            //pQueryPool->SetName(L"GPUPerfAPIVk QueryPool");
            m_queryPools[queryType] = queryPool;

            m_pQueriesResults = new (std::nothrow) GpaVkSoftwareQueryResults[m_maxSamples];
            result            = (nullptr != m_pQueriesResults);

            if (result)
            {
                memset(m_pQueriesResults, 0, sizeof(GpaVkSoftwareQueryResults) * m_maxSamples);
            }
        }
        else
        {
            m_queryPools[queryType] = VK_NULL_HANDLE;
            result                  = false;
        }
    }

    return result;
}
