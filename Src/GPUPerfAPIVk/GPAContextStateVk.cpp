//==============================================================================
// Copyright (c) 2015-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA_ContextStateVk implementation
//==============================================================================

#include "GPAContextStateVk.h"

#include <cassert>

GPA_ContextStateVk::GPA_ContextStateVk()
    :
    m_commandBufferQueries(),
    m_mutex(),
    m_physicalDevice(VK_NULL_HANDLE),
    m_device(VK_NULL_HANDLE),
    m_clockMode(VK_GPA_DEVICE_CLOCK_MODE_DEFAULT_AMD)
{
}

GPA_ContextStateVk::~GPA_ContextStateVk()
{
    Cleanup();
}

void GPA_ContextStateVk::Cleanup()
{
    if (VK_NULL_HANDLE != m_physicalDevice)
    {
        if (GPA_STATUS_OK != SetStableClocks(false))
        {
            GPA_LogError("Unable to restore GPU clocks.");
        }

        m_physicalDevice = VK_NULL_HANDLE;
    }
}

GPA_Status GPA_ContextStateVk::SetVkPhysicalDevice(VkPhysicalDevice physicalDevice)
{
    // only allow it to be set once. It should not be changed once it is set.
    GPA_Status result = GPA_STATUS_ERROR_FAILED;

    if (physicalDevice == m_physicalDevice)
    {
        result = GPA_STATUS_OK;
    }
    else
    {
        m_physicalDevice = physicalDevice;
    }

    return result;
}

void GPA_ContextStateVk::SetVkDevice(VkDevice device)
{
    if (device != m_device)
    {
        m_device = device;
    }
}

VkDevice GPA_ContextStateVk::GetVkDevice()
{
    return m_device;
}

GPA_Status GPA_ContextStateVk::GetTimestampFrequency(gpa_uint64& timestampFrequency)
{
    GPA_Status result = GPA_STATUS_OK;

    VkPhysicalDeviceProperties properties;
    _vkGetPhysicalDeviceProperties(m_physicalDevice, &properties);

    // get Time stamp frequency
    float timestampPeriod = properties.limits.timestampPeriod;

    // TODO: decide if/how this should come into play
    //bool computeAndGraphics = properties.limits.timestampComputeAndGraphics;

    // TODO: confirm this is accurate
    timestampFrequency = static_cast<gpa_uint64>(timestampPeriod);

    return result;
}

GPA_Status GPA_ContextStateVk::BeginCommandBuffer(void* pCommandList)
{
    GPA_Status retVal = GPA_STATUS_OK;

    VkCommandBuffer commandBuffer = static_cast<VkCommandBuffer>(pCommandList);
    if (m_commandBufferQueries.end() == m_commandBufferQueries.find(commandBuffer))
    {
        // Need to add this command buffer to the map
        bool isInitialized = m_commandBufferQueries[commandBuffer].Initialize(m_physicalDevice, m_device, commandBuffer);
        assert(isInitialized);
        if (!isInitialized)
        {
            retVal = GPA_STATUS_ERROR_FAILED;
        }
    }

    VkGpaSessionAMD gpaSession = VK_NULL_HANDLE;

    if (m_commandBufferGpaSession.end() == m_commandBufferGpaSession.find(commandBuffer))
    {
        VkGpaSessionCreateInfoAMD createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_GPA_SESSION_CREATE_INFO_AMD;
        createInfo.pNext = NULL;
        createInfo.secondaryCopySource = VK_NULL_HANDLE;

        VkResult createResult = _vkCreateGpaSessionAMD(this->m_device, &createInfo, NULL, &gpaSession);
        retVal = (createResult == VK_SUCCESS) ? GPA_STATUS_OK : GPA_STATUS_ERROR_FAILED;
    }
    else
    {
        gpaSession = m_commandBufferGpaSession[commandBuffer];

        GPA_SessionRequests* pSessionRequests = FindSession(m_sessionID);

        if (nullptr == pSessionRequests)
        {
            GPA_LogError("Unable to find session requests.");
            return GPA_STATUS_ERROR_NULL_POINTER;
        }

        // attempt to collect any outstanding results before resetting the Gpa Session
        if (pSessionRequests->IsComplete())
        {
            VkResult resetResult = _vkResetGpaSessionAMD(m_device, gpaSession);

            if (resetResult != VK_SUCCESS)
            {
                GPA_LogError("Unable to reset GPA session.");
                retVal = GPA_STATUS_ERROR_FAILED;
            }
        }
        else
        {
            GPA_LogError("Attempt to restart a command list while its previous results have not been collected.");
            retVal = GPA_STATUS_ERROR_FAILED;
        }
    }

    if (VK_NULL_HANDLE == gpaSession)
    {
        GPA_LogError("Unable to create GPA session.");
        retVal = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        m_commandBufferGpaSession[commandBuffer] = gpaSession;

        VkResult beginResult = _vkCmdBeginGpaSessionAMD(commandBuffer, gpaSession);

        if (beginResult != VK_SUCCESS)
        {
            GPA_LogError("Unable to open command list for sampling.");
            retVal = GPA_STATUS_ERROR_FAILED;
        }
    }

    return retVal;
}

GPA_Status GPA_ContextStateVk::EndCommandBuffer(void* pCommandBuffer)
{
    GPA_Status retVal = GPA_STATUS_OK;

    VkGpaSessionAMD gpaSession = VK_NULL_HANDLE;

    VkCommandBuffer commandBuffer = static_cast<VkCommandBuffer>(pCommandBuffer);

    if (m_commandBufferGpaSession.end() != m_commandBufferGpaSession.find(commandBuffer))
    {
        gpaSession = m_commandBufferGpaSession[commandBuffer];

        if (VK_NULL_HANDLE == gpaSession)
        {
            GPA_LogError("Make sure BeginCommandList is called before EndCommandList for this command list.");
            retVal = GPA_STATUS_ERROR_SAMPLING_NOT_STARTED;
        }
        else
        {
            VkResult ended = _vkCmdEndGpaSessionAMD(commandBuffer, gpaSession);

            if (ended != VK_SUCCESS)
            {
                GPA_LogError("Unable to end command buffer.");
                retVal = GPA_STATUS_ERROR_FAILED;
            }
        }
    }
    else
    {
        GPA_LogError("Command buffer not open for sampling.");
        retVal = GPA_STATUS_ERROR_SAMPLING_NOT_STARTED;
    }

    return retVal;
}

bool GPA_ContextStateVk::GetGpaSessionForCommandList(VkCommandBuffer commandBuffer, VkGpaSessionAMD* pGpaSession)
{
    bool retVal = false;

    if (nullptr != pGpaSession)
    {
        if (m_commandBufferGpaSession.end() != m_commandBufferGpaSession.find(commandBuffer))
        {
            *pGpaSession = m_commandBufferGpaSession[commandBuffer];
            retVal = true;
        }
        else
        {
            *pGpaSession = VK_NULL_HANDLE;
            GPA_LogError("Unable to get extension object for specified command buffer.");
        }
    }
    else
    {
        GPA_LogError("Null extension pointer.");
    }

    return retVal;
}

bool GPA_ContextStateVk::BeginSwSample(VkCommandBuffer commandBuffer, gpa_uint32& swSampleId)
{
    bool success = true;
    CommandBufferQueriesType::iterator cmdBufferQueriesIter = m_commandBufferQueries.find(commandBuffer);

    if (m_commandBufferQueries.end() == cmdBufferQueriesIter)
    {
        GPA_LogError("Sample started on invalid VkCommandBuffer.");
        success = false;
    }

    if (success)
    {
        success = cmdBufferQueriesIter->second.BeginSwSample(swSampleId);
    }

    return success;
}

void GPA_ContextStateVk::EndSwSample(VkCommandBuffer commandBuffer, const gpa_uint32 swSampleId)
{
    CommandBufferQueriesType::iterator cmdBufferIter = m_commandBufferQueries.find(commandBuffer);
#ifdef _DEBUG
    assert(m_commandBufferQueries.end() != cmdBufferIter);
#endif // _DEBUG

    if ((m_commandBufferQueries.end() != cmdBufferIter))
    {
        cmdBufferIter->second.EndSwSample(swSampleId);
    }
}

void GPA_ContextStateVk::ReleaseSwSample(VkCommandBuffer commandBuffer, const gpa_uint32 swSampleId)
{
    CommandBufferQueriesType::iterator cmdBufferIter = m_commandBufferQueries.find(commandBuffer);
#ifdef _DEBUG
    assert(m_commandBufferQueries.end() != cmdBufferIter);
#endif // _DEBUG

    if (m_commandBufferQueries.end() != cmdBufferIter)
    {
        cmdBufferIter->second.ReleaseSwSample(swSampleId);
    }
}

void GPA_ContextStateVk::BeginSwQuery(
    VkCommandBuffer commandBuffer,
    const gpa_uint32 swSampleId,
    const GPA_VK_SW_QUERY_TYPE queryType)
{
    CommandBufferQueriesType::iterator cmdBufferIter = m_commandBufferQueries.find(commandBuffer);
#ifdef _DEBUG
    assert(m_commandBufferQueries.end() != cmdBufferIter);
#endif // _DEBUG

    if (m_commandBufferQueries.end() != cmdBufferIter)
    {
        cmdBufferIter->second.BeginSwQuery(swSampleId, queryType);
    }
}

void GPA_ContextStateVk::EndSwQuery(
    VkCommandBuffer commandBuffer,
    const gpa_uint32 swSampleId,
    const GPA_VK_SW_QUERY_TYPE queryType)
{
    CommandBufferQueriesType::iterator cmdBufferIter = m_commandBufferQueries.find(commandBuffer);
#ifdef _DEBUG
    assert(m_commandBufferQueries.end() != cmdBufferIter);
#endif // _DEBUG

    if (m_commandBufferQueries.end() != cmdBufferIter)
    {
        cmdBufferIter->second.EndSwQuery(swSampleId, queryType);
    }
}

bool GPA_ContextStateVk::GetSwSampleResults(
    VkCommandBuffer commandBuffer,
    const gpa_uint32 swSampleId,
    GpaVkSoftwareQueryResults& queryResults)
{
    CommandBufferQueriesType::iterator cmdBufferIter = m_commandBufferQueries.find(commandBuffer);
    bool result = (m_commandBufferQueries.end() != cmdBufferIter);

    if (result)
    {
        result = cmdBufferIter->second.GetSwSampleResults(swSampleId, queryResults);
    }

    return result;
}

GPA_Status GPA_ContextStateVk::SetStableClocks(bool useProfilingClocks)
{
    GPA_Status result = GPA_STATUS_OK;
    if (_vkSetGpaDeviceClockModeAMD == nullptr)
    {
        GPA_LogError("VK_AMD_gpa_interface extension is not available.");
        // VK_AMD_gpa_interface extension is not available
        result = GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED;
    }
    else
    {
        VkGpaDeviceClockModeInfoAMD clockMode = {};
        clockMode.sType = VK_STRUCTURE_TYPE_GPA_DEVICE_CLOCK_MODE_INFO_AMD;
        clockMode.clockMode = VK_GPA_DEVICE_CLOCK_MODE_DEFAULT_AMD;

        if (useProfilingClocks)
        {
            DeviceClockMode deviceClockMode = GetDeviceClockMode();

            switch (deviceClockMode)
            {
            case DeviceClockMode::Default:
                clockMode.clockMode = VK_GPA_DEVICE_CLOCK_MODE_DEFAULT_AMD;
                break;
            case DeviceClockMode::Profiling:
                clockMode.clockMode = VK_GPA_DEVICE_CLOCK_MODE_PROFILING_AMD;
                break;
            case DeviceClockMode::MinimumMemory:
                clockMode.clockMode = VK_GPA_DEVICE_CLOCK_MODE_MIN_MEMORY_AMD;
                break;
            case DeviceClockMode::MinimumEngine:
                clockMode.clockMode = VK_GPA_DEVICE_CLOCK_MODE_MIN_ENGINE_AMD;
                break;
            case DeviceClockMode::Peak:
                clockMode.clockMode = VK_GPA_DEVICE_CLOCK_MODE_PEAK_AMD;
                break;
            default:
                assert(0);
                clockMode.clockMode = VK_GPA_DEVICE_CLOCK_MODE_PROFILING_AMD;
                break;
            }
        }

        if (clockMode.clockMode != m_clockMode)
        {
            m_clockMode = clockMode.clockMode;
            VkResult clockResult = _vkSetGpaDeviceClockModeAMD(m_device, &clockMode);
            result = (clockResult == VK_SUCCESS) ? GPA_STATUS_OK : GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED;

            if (clockResult != VK_SUCCESS)
            {
                GPA_LogError("Failed to set ClockMode for profiling.");
            }
        }
    }
    return result;
}

