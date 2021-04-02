//==============================================================================
// Copyright (c) 2015-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  VkCommandListSwQueries declaration
//==============================================================================
#include "gpu_perf_api_vk/vk_command_list_sw_queries.h"

#include "gpu_perf_api_common/logging.h"

VkCommandListSwQueries::VkCommandListSwQueries()
    : physical_device_(VK_NULL_HANDLE)
    , command_buffer_(VK_NULL_HANDLE)
    , device_(VK_NULL_HANDLE)
{
}

VkCommandListSwQueries::VkCommandListSwQueries(VkCommandListSwQueries&& other)
{
    command_buffer_  = other.command_buffer_;
    physical_device_ = other.physical_device_;
    device_          = other.device_;

    query_group_ = std::move(other.query_group_);
}

VkCommandListSwQueries::~VkCommandListSwQueries()
{
}

VkCommandListSwQueries& VkCommandListSwQueries::operator=(VkCommandListSwQueries&& other)
{
    command_buffer_ = other.command_buffer_;

    device_ = other.device_;

    query_group_ = std::move(other.query_group_);

    return (*this);
}

bool VkCommandListSwQueries::Initialize(VkPhysicalDevice pysical_device, VkDevice device, VkCommandBuffer command_buffer)
{
    physical_device_ = pysical_device;
    device_          = device;
    command_buffer_  = command_buffer;

    bool created = query_group_.Initialize(physical_device_, device_, command_buffer_, kResultGroupSize);
    return created;
}

bool VkCommandListSwQueries::BeginSwSample(GpaUInt32& sample_id)
{
    bool ret_val = true;

    sample_id = query_group_.GetSampleCount();

    query_group_.BeginSwSample();

    return ret_val;
}

void VkCommandListSwQueries::EndSwSample(const GpaUInt32 sample_id)
{
    const GpaUInt32 sample_index = sample_id % kResultGroupSize;

    query_group_.EndSwSample(sample_index);
}

void VkCommandListSwQueries::ReleaseSwSample(const GpaUInt32 sample_id)
{
    const GpaUInt32 sample_index = sample_id % kResultGroupSize;

    query_group_.ReleaseSwSample(sample_index);
}

void VkCommandListSwQueries::BeginSwQuery(const GpaUInt32 sample_id, const GpaVkSwQueryType query_type)
{
    const GpaUInt32 sample_index = sample_id % kResultGroupSize;

    query_group_.BeginSwQuery(sample_index, query_type);
}

void VkCommandListSwQueries::EndSwQuery(const GpaUInt32 sample_id, const GpaVkSwQueryType query_type)
{
    const GpaUInt32 sample_index = sample_id % kResultGroupSize;

    query_group_.EndSwQuery(sample_index, query_type);
}

bool VkCommandListSwQueries::GetSwSampleResults(const GpaUInt32 sample_id, GpaVkSoftwareQueryResults& query_restuls)
{
    const GpaUInt32 sample_index = sample_id % kResultGroupSize;

    return query_group_.GetSwSampleResults(sample_index, query_restuls);
}