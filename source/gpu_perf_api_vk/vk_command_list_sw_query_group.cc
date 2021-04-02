//==============================================================================
// Copyright (c) 2015-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Class to manage the resources used for Vk SW queries
//==============================================================================

#include "gpu_perf_api_vk/vk_command_list_sw_query_group.h"

#include <string.h>

#include "gpu_perf_api_common/logging.h"

#include "gpu_perf_api_vk/vk_entry_points.h"

const VkQueryType VkCommandListSWQueryGroup::kQueryTypes[] = {VK_QUERY_TYPE_OCCLUSION,
                                                              VK_QUERY_TYPE_OCCLUSION,
                                                              VK_QUERY_TYPE_TIMESTAMP,
                                                              VK_QUERY_TYPE_PIPELINE_STATISTICS};

VkCommandListSWQueryGroup::VkCommandListSWQueryGroup()
    : max_samples_(0)
    , active_sample_count_(0)
    , device_(VK_NULL_HANDLE)
    , command_buffer_(VK_NULL_HANDLE)
    , queries_results_(nullptr)
{
    for (size_t query_index = 0; kGpaVkQueryTypeCount > query_index; ++query_index)
    {
        query_pools_[query_index] = VK_NULL_HANDLE;
    }
}

VkCommandListSWQueryGroup::VkCommandListSWQueryGroup(VkCommandListSWQueryGroup&& other)
    : max_samples_(other.max_samples_)
    , active_sample_count_(other.active_sample_count_)
    , command_buffer_(other.command_buffer_)
    , queries_results_(other.queries_results_)
{
    for (size_t query_index = 0; kGpaVkQueryTypeCount > query_index; ++query_index)
    {
        query_pools_[query_index] = other.query_pools_[query_index];
    }

    other.queries_results_ = nullptr;
}

VkCommandListSWQueryGroup::~VkCommandListSWQueryGroup()
{
    Cleanup();
}

VkCommandListSWQueryGroup& VkCommandListSWQueryGroup::operator=(VkCommandListSWQueryGroup&& other)
{
    max_samples_         = other.max_samples_;
    active_sample_count_ = other.active_sample_count_;
    command_buffer_      = other.command_buffer_;
    device_              = other.device_;

    for (size_t query_index = 0; (kGpaVkQueryTypeCount > query_index); ++query_index)
    {
        query_pools_[query_index] = other.query_pools_[query_index];
    }

    queries_results_       = other.queries_results_;
    other.queries_results_ = nullptr;

    return (*this);
}

bool VkCommandListSWQueryGroup::Initialize(VkPhysicalDevice physical_device, VkDevice device, VkCommandBuffer command_buffer, size_t grouop_size)
{
    bool result  = true;
    max_samples_ = grouop_size;

    for (size_t query_index = 0; (kGpaVkQueryTypeCount > query_index) && result; ++query_index)
    {
        if (VK_NULL_HANDLE == query_pools_[query_index])
        {
            VkBool32 create_query_pool = VK_TRUE;

            if (kQueryTypes[query_index] == VK_QUERY_TYPE_PIPELINE_STATISTICS)
            {
                VkPhysicalDeviceFeatures features;
                _vkGetPhysicalDeviceFeatures(physical_device, &features);
                create_query_pool = features.pipelineStatisticsQuery;
            }

            if (create_query_pool == VK_TRUE)
            {
                result &= CreateSwQueryPool(device, (GpaVkSwQueryType)query_index);

                if (result)
                {
                    // Reset the query pool so that it can be used.
                    _vkCmdResetQueryPool(command_buffer, query_pools_[query_index], 0, (uint32_t)max_samples_);
                }
            }
        }
    }

    if (result)
    {
        device_         = device;
        command_buffer_ = command_buffer;

        active_sample_queries_.clear();
    }
    else
    {
        Cleanup();
    }

    return result;
}

void VkCommandListSWQueryGroup::Cleanup()
{
    if (nullptr != queries_results_)
    {
        delete[] queries_results_;
        queries_results_ = nullptr;
    }

    active_sample_queries_.clear();

    if (VK_NULL_HANDLE != device_)
    {
        VkResult wait_result = _vkDeviceWaitIdle(device_);

        if (wait_result == VK_SUCCESS)
        {
            for (size_t query_index = 0; query_index < kGpaVkQueryTypeCount; ++query_index)
            {
                if (VK_NULL_HANDLE != query_pools_[query_index])
                {
                    _vkDestroyQueryPool(device_, query_pools_[query_index], nullptr);
                }
            }
        }
    }
}

GpaUInt32 VkCommandListSWQueryGroup::GetSampleCount() const
{
    return active_sample_count_;
}

void VkCommandListSWQueryGroup::BeginSwSample()
{
    active_sample_count_++;
}

void VkCommandListSWQueryGroup::EndSwSample(const GpaUInt32 sample_index)
{
    UNREFERENCED_PARAMETER(sample_index);
}

void VkCommandListSWQueryGroup::ReleaseSwSample(const GpaUInt32 sample_index)
{
    UNREFERENCED_PARAMETER(sample_index);
    memset(&(queries_results_[sample_index]), 0, sizeof(queries_results_[sample_index]));
    active_sample_count_--;
}

void VkCommandListSWQueryGroup::BeginSwQuery(const GpaUInt32 sample_index, const GpaVkSwQueryType query_type)
{
    if (kGpaVkQueryTypeTimestamp == query_type)
    {
        _vkCmdWriteTimestamp(command_buffer_, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, query_pools_[query_type], 2 * sample_index);
    }
    else
    {
        VkQueryControlFlags flags = 0;

        if (kGpaVkQueryTypeOcclusion == query_type)
        {
            flags = VK_QUERY_CONTROL_PRECISE_BIT;
        }

        _vkCmdBeginQuery(command_buffer_, query_pools_[query_type], sample_index, flags);
    }

    active_sample_queries_[sample_index][query_type] = true;
}

void VkCommandListSWQueryGroup::EndSwQuery(const GpaUInt32 sample_index, const GpaVkSwQueryType query_type)
{
    if (kGpaVkQueryTypeTimestamp == query_type)
    {
        _vkCmdWriteTimestamp(command_buffer_, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, query_pools_[query_type], 2 * sample_index + 1);
    }
    else
    {
        _vkCmdEndQuery(command_buffer_, query_pools_[query_type], sample_index);
    }
}

bool VkCommandListSWQueryGroup::GetSwSampleResults(const GpaUInt32 sample_index, GpaVkSoftwareQueryResults& queryResults)
{
    uint64_t* result_available_addresses[kGpaVkQueryTypeCount] = {&(queries_results_[sample_index].occlusionAvailable),
                                                                  &(queries_results_[sample_index].occlusionBinaryAvailable),
                                                                  &(queries_results_[2 * sample_index].timestampEndAvailable),
                                                                  &(queries_results_[sample_index].pipelineStatsAvailable)};

    uint64_t* result_addresses[kGpaVkQueryTypeCount] = {&(queries_results_[sample_index].occlusion),
                                                        &(queries_results_[sample_index].occlusionBinary),
                                                        &(queries_results_[2 * sample_index].timestampBegin),
                                                        &(queries_results_[sample_index].inputAssemblyVertices)};

    // Initially all results are available.
    bool all_results_available = true;

    for (size_t query_type_index = 0; kGpaVkQueryTypeCount > query_type_index; ++query_type_index)
    {
        if (active_sample_queries_[sample_index][query_type_index] == true)
        {
            VkQueryPool query_pool = query_pools_[query_type_index];

            if (VK_NULL_HANDLE != query_pool)
            {
                // First, get a copy of the query results.
                uint64_t* result_address = result_addresses[query_type_index];
                size_t    result_size    = kGpaVkSoftwareResultSizes[query_type_index];
                size_t    result_stride  = kGpaVkSoftwareResultStrides[query_type_index];

                uint32_t query_index = sample_index;
                uint32_t num_queries = 1;

                if (query_type_index == kGpaVkQueryTypeTimestamp)
                {
                    // Timestamp has 2 queries (begin and end).
                    query_index = 2 * sample_index;
                    num_queries = 2;
                }

                // Get the results back.
                // NOTE: because we may loop over this multiple times, it is possible
                // that the query results get updated each time we get them.
                VkResult results = _vkGetQueryPoolResults(device_,
                                                          query_pool,
                                                          query_index,
                                                          num_queries,
                                                          result_size,
                                                          result_address,
                                                          result_stride,
                                                          VK_QUERY_RESULT_64_BIT | VK_QUERY_RESULT_WITH_AVAILABILITY_BIT);

                all_results_available = (results == VK_SUCCESS);

                if (all_results_available)
                {
                    // Second, Check if the query results availability bit indicated that it was available.
                    uint64_t* results_available_address = result_available_addresses[query_type_index];
                    GpaUInt64 result_available          = *results_available_address;

                    if (result_available == 0)
                    {
                        all_results_available = false;
                    }
                    else
                    {
                        // Result is available, which matches initial assumption.
                        // CAVEAT: There's currently a bug in the availibility bit for PIPELINE_STATISTICS that
                        // it will report available even though all results are 0. So if we encounter this
                        // situation, report that results are actually NOT available.
                        if (query_type_index == kGpaVkQueryTypePipelineStatistics && queries_results_[sample_index].inputAssemblyVertices == 0 &&
                            queries_results_[sample_index].inputAssemblyPrimitives == 0 && queries_results_[sample_index].vertexShaderInvocations == 0 &&
                            queries_results_[sample_index].geometryShaderInvocations == 0 && queries_results_[sample_index].geometryShaderPrimitives == 0 &&
                            queries_results_[sample_index].clippingInvocations == 0 && queries_results_[sample_index].clippingPrimitives == 0 &&
                            queries_results_[sample_index].fragmentShaderInvocations == 0 &&
                            queries_results_[sample_index].tessellationControlShaderPatches == 0 &&
                            queries_results_[sample_index].tessellationEvaluationShaderInvocations == 0 &&
                            queries_results_[sample_index].computeShaderInvocations == 0)
                        {
                            // CAVEAT: There's currently a bug in the availibility bit that it will report available
                            // even though all results are 0. So if we encounter this situation, report that results
                            // are actually NOT available.
                            all_results_available = false;
                        }
                    }
                }
            }
        }
    }

    if (all_results_available)
    {
        queryResults = queries_results_[sample_index];
    }

    return all_results_available;
}

bool VkCommandListSWQueryGroup::CreateSwQueryPool(VkDevice device, const GpaVkSwQueryType query_type)
{
    bool                  result = true;
    VkQueryPoolCreateInfo query_pool_description;
    memset(&query_pool_description, 0, sizeof(query_pool_description));
    query_pool_description.sType      = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
    query_pool_description.queryType  = kQueryTypes[query_type];
    query_pool_description.flags      = 0;
    query_pool_description.queryCount = (uint32_t)max_samples_;

    if (query_type == kGpaVkQueryTypePipelineStatistics)
    {
        query_pool_description.pipelineStatistics =
            VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_VERTICES_BIT | VK_QUERY_PIPELINE_STATISTIC_INPUT_ASSEMBLY_PRIMITIVES_BIT |
            VK_QUERY_PIPELINE_STATISTIC_VERTEX_SHADER_INVOCATIONS_BIT | VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_INVOCATIONS_BIT |
            VK_QUERY_PIPELINE_STATISTIC_GEOMETRY_SHADER_PRIMITIVES_BIT | VK_QUERY_PIPELINE_STATISTIC_CLIPPING_INVOCATIONS_BIT |
            VK_QUERY_PIPELINE_STATISTIC_CLIPPING_PRIMITIVES_BIT | VK_QUERY_PIPELINE_STATISTIC_FRAGMENT_SHADER_INVOCATIONS_BIT |
            VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_CONTROL_SHADER_PATCHES_BIT | VK_QUERY_PIPELINE_STATISTIC_TESSELLATION_EVALUATION_SHADER_INVOCATIONS_BIT |
            VK_QUERY_PIPELINE_STATISTIC_COMPUTE_SHADER_INVOCATIONS_BIT;
    }

    if (query_type == kGpaVkQueryTypeTimestamp)
    {
        // We keep track of both begin and end timestamps, so we need 2x as many queries.
        query_pool_description.queryCount *= 2;
    }

    if (result)
    {
        VkQueryPool query_pool = VK_NULL_HANDLE;
        result                 = (VK_SUCCESS == _vkCreateQueryPool(device, &query_pool_description, nullptr, &query_pool));

        if (result)
        {
            query_pools_[query_type] = query_pool;

            queries_results_ = new (std::nothrow) GpaVkSoftwareQueryResults[max_samples_];
            result           = (nullptr != queries_results_);

            if (result)
            {
                memset(queries_results_, 0, sizeof(GpaVkSoftwareQueryResults) * max_samples_);
            }
        }
        else
        {
            query_pools_[query_type] = VK_NULL_HANDLE;
            result                   = false;
        }
    }

    return result;
}