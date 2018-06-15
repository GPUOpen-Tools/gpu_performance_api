//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  VkCommandListSwQueries declaration
//==============================================================================

#include "Logging.h"
#include "VkCommandListSwQueries.h"

VkCommandListSwQueries::VkCommandListSwQueries()
    :
    m_physicalDevice(VK_NULL_HANDLE),
    m_commandBuffer(VK_NULL_HANDLE),
    m_device(VK_NULL_HANDLE)
{
}

VkCommandListSwQueries::VkCommandListSwQueries(VkCommandListSwQueries&& other)
{
    m_commandBuffer = other.m_commandBuffer;
    m_physicalDevice = other.m_physicalDevice;
    m_device = other.m_device;

    m_queryGroup = std::move(other.m_queryGroup);
}

VkCommandListSwQueries::~VkCommandListSwQueries()
{
}

VkCommandListSwQueries& VkCommandListSwQueries::operator=(VkCommandListSwQueries&& other)
{
    m_commandBuffer = other.m_commandBuffer;

    m_device = other.m_device;

    m_queryGroup = std::move(other.m_queryGroup);

    return (*this);
}

bool VkCommandListSwQueries::Initialize(VkPhysicalDevice physicalDevice, VkDevice device, VkCommandBuffer commandBuffer)
{
    m_physicalDevice = physicalDevice;
    m_device = device;
    m_commandBuffer = commandBuffer;

    bool created = m_queryGroup.Initialize(m_physicalDevice, m_device, m_commandBuffer, ms_resultGroupSize);
    return created;
}

bool VkCommandListSwQueries::BeginSwSample(gpa_uint32& swSampleId)
{
    bool retVal = true;

    swSampleId = m_queryGroup.GetSampleCount();

    m_queryGroup.BeginSwSample();

    return retVal;
}


void VkCommandListSwQueries::EndSwSample(const gpa_uint32 swSampleId)
{
    const gpa_uint32 sampleIndex = swSampleId % ms_resultGroupSize;

    m_queryGroup.EndSwSample(sampleIndex);
}

void VkCommandListSwQueries::ReleaseSwSample(const gpa_uint32 swSampleId)
{
    const gpa_uint32 sampleIndex = swSampleId % ms_resultGroupSize;

    m_queryGroup.ReleaseSwSample(sampleIndex);
}


void VkCommandListSwQueries::BeginSwQuery(
    const gpa_uint32 swSampleId, const GPA_VK_SW_QUERY_TYPE queryType)
{
    const gpa_uint32 sampleIndex = swSampleId % ms_resultGroupSize;

    m_queryGroup.BeginSwQuery(sampleIndex, queryType);
}

void VkCommandListSwQueries::EndSwQuery(
    const gpa_uint32 swSampleId, const GPA_VK_SW_QUERY_TYPE queryType)
{
    const gpa_uint32 sampleIndex = swSampleId % ms_resultGroupSize;

    m_queryGroup.EndSwQuery(sampleIndex, queryType);
}


bool VkCommandListSwQueries::GetSwSampleResults(
    const gpa_uint32 swSampleId, GpaVkSoftwareQueryResults& queryResults)
{
    const gpa_uint32 sampleIndex = swSampleId % ms_resultGroupSize;

    return m_queryGroup.GetSwSampleResults(sampleIndex, queryResults);
}

