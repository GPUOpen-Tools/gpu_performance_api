//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA VK Context Definition
//==============================================================================

#include <mutex>
#include <assert.h>

#include "VkGPAContext.h"
#include <DeviceInfoUtils.h>
#include "VkGPASession.h"
#include "GPUPerfAPI-VK.h"
#include "VkEntrypoints.h"
#include "GPACounterGenerator.h"
#include "GPACounterGeneratorBase.h"
#include "GPAUniqueObject.h"
#include "VkUtils.h"

VkGPAContext::VkGPAContext(const GPA_vkContextOpenInfo* openInfo, GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags)
    : GPAContext(hwInfo, flags)
{
    m_physicalDevice = openInfo->physicalDevice;
    m_device         = openInfo->device;

    m_amdDeviceProperties = {};
    m_clockMode           = VK_GPA_DEVICE_CLOCK_MODE_DEFAULT_AMD;
}

VkGPAContext::~VkGPAContext()
{
    GPA_Status setStableClocksStatus = SetStableClocks(false);

    if (GPA_STATUS_OK != setStableClocksStatus)
    {
        GPA_LogError("Driver was unable to set stable clocks back to default.");
#ifdef __linux__
        GPA_LogMessage("In Linux, make sure to run your application with root privileges.");
#endif  //__linux__
    }

    VkUtils::ReleasePhysicalDeviceGpaPropertiesAMD(&m_amdDeviceProperties);

    auto deleteVkSession = [](IGPASession* pGpaSession) -> bool {
        if (nullptr != pGpaSession)
        {
            GPAUniqueObjectManager::Instance()->DeleteObject(pGpaSession);
            delete pGpaSession;
        }

        return true;
    };

    IterateGpaSessionList(deleteVkSession);
    ClearSessionList();
}

GPA_Status VkGPAContext::Open()
{
    GPA_Status result = GPA_STATUS_OK;

#ifdef _DEBUG
    VkUtils::DebugReportQueueFamilyTimestampBits(m_physicalDevice);
#endif

    if (VkUtils::GetPhysicalDeviceGpaPropertiesAMD(m_physicalDevice, &m_amdDeviceProperties))
    {
        // counters are supported, set stable clocks

        // we don't want a failure when setting stable clocks to result in a
        // fatal error returned from here. So we use a local status object
        // instead of modifying "result". We will still output log messages.
        GPA_Status setStableClocksStatus = SetStableClocks(true);

        if (GPA_STATUS_OK != setStableClocksStatus)
        {
            GPA_LogError("Driver was unable to set stable clocks for profiling.");
#ifdef __linux__
            GPA_LogMessage("In Linux, make sure to run your application with root privileges.");
#endif  //__linux__
        }

        if (OpenCounters())
        {
            SetAsOpened(true);
        }
        else
        {
            result = GPA_STATUS_ERROR_FAILED;

            VkUtils::ReleasePhysicalDeviceGpaPropertiesAMD(&m_amdDeviceProperties);
        }
    }
    else
    {
        GPA_LogError("Unable to obtain profiler functionality from the driver / hardware.");
        result = GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED;
    }

    return result;
}

GPA_Status VkGPAContext::SetStableClocks(bool useProfilingClocks)
{
    GPA_Status result = GPA_STATUS_OK;

    if (nullptr == _vkSetGpaDeviceClockModeAMD)
    {
        GPA_LogError("VK_AMD_gpa_interface extension is not available.");
        // VK_AMD_gpa_interface extension is not available
        result = GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED;
    }
    else
    {
        VkGpaDeviceClockModeInfoAMD clockMode = {};
        clockMode.sType                       = VK_STRUCTURE_TYPE_GPA_DEVICE_CLOCK_MODE_INFO_AMD;
        clockMode.clockMode                   = VK_GPA_DEVICE_CLOCK_MODE_DEFAULT_AMD;

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

        // TODO: DX12 locks a mutex here: std::lock_guard<std::mutex> lockAmdClock(m_gpaContextMutex);

        if (clockMode.clockMode != m_clockMode)
        {
            m_clockMode          = clockMode.clockMode;
            VkResult clockResult = _vkSetGpaDeviceClockModeAMD(m_device, &clockMode);
            result               = (clockResult == VK_SUCCESS) ? GPA_STATUS_OK : GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED;

            if (VK_SUCCESS != clockResult)
            {
                GPA_LogError("Failed to set ClockMode for profiling.");
            }
        }
    }

    return result;
}

GPA_SessionId VkGPAContext::CreateSession(GPA_Session_Sample_Type sampleType)
{
    GPA_SessionId sessionId = nullptr;

    VkGPASession* pSession = new (std::nothrow) VkGPASession(this, sampleType);

    if (nullptr != pSession)
    {
        AddGpaSession(pSession);
        sessionId = reinterpret_cast<GPA_SessionId>(GPAUniqueObjectManager::Instance()->CreateObject(pSession));
    }

    return sessionId;
}

bool VkGPAContext::DeleteSession(GPA_SessionId sessionId)
{
    bool isDeleted = false;

    std::lock_guard<std::mutex> lockSessionList(m_sessionListMutex);

    VkGPASession* pVkSession = reinterpret_cast<VkGPASession*>(sessionId->Object());
    isDeleted                = DeleteVkGpaSession(pVkSession);

    return isDeleted;
}

bool VkGPAContext::DeleteVkGpaSession(VkGPASession* pVkGpaSession)
{
    if (nullptr != pVkGpaSession)
    {
        RemoveGpaSession(pVkGpaSession);
        GPAUniqueObjectManager::Instance()->DeleteObject(pVkGpaSession);
        delete pVkGpaSession;
    }

    return true;
}

gpa_uint32 VkGPAContext::GetMaxGPASessions() const
{
    // there is no maximum number of sessions
    return GPA_SESSION_NO_LIMIT;
}

GPA_API_Type VkGPAContext::GetAPIType() const
{
    return GPA_API_VULKAN;
}

VkDevice VkGPAContext::GetVkDevice() const
{
    return m_device;
}

VkPhysicalDevice VkGPAContext::GetVkPhysicalDevice() const
{
    return m_physicalDevice;
}

gpa_uint32 VkGPAContext::GetInstanceCount(VkGpaPerfBlockAMD block) const
{
    gpa_uint32 instanceCount = 0;

    if (block < VK_GPA_PERF_BLOCK_RANGE_SIZE_AMD)
    {
        for (uint32_t i = 0; i < m_amdDeviceProperties.perfBlockCount; i++)
        {
            if (m_amdDeviceProperties.pPerfBlocks[i].blockType == block)
            {
                instanceCount = static_cast<gpa_uint32>(m_amdDeviceProperties.pPerfBlocks[i].instanceCount);
                break;
            }
        }
    }

    return instanceCount;
}

gpa_uint32 VkGPAContext::GetMaxEventIdCount(VkGpaPerfBlockAMD block) const
{
    gpa_uint32 maxEventId = 0;

    if (block < VK_GPA_PERF_BLOCK_RANGE_SIZE_AMD)
    {
        for (uint32_t i = 0; i < m_amdDeviceProperties.perfBlockCount; i++)
        {
            if (m_amdDeviceProperties.pPerfBlocks[i].blockType == block)
            {
                maxEventId = static_cast<gpa_uint32>(m_amdDeviceProperties.pPerfBlocks[i].maxEventID);
                break;
            }
        }
    }

    return maxEventId;
}