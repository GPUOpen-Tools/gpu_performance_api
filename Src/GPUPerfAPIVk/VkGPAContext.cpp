//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA VK Context Definition
//==============================================================================

#include "VkGPAContext.h"

#include <map>
#include <mutex>
#include <assert.h>
#include <DeviceInfoUtils.h>

#include "VkGPASession.h"
#include "GPUPerfAPI-VK.h"
#include "VkEntrypoints.h"
#include "GPACounterGenerator.h"
#include "GPACounterGeneratorBase.h"
#include "GPAUniqueObject.h"
#include "VkUtils.h"

VkGPAContext::VkGPAContext(const GPA_vkContextOpenInfo* openInfo,
    GPA_HWInfo& hwInfo,
    GPA_OpenContextFlags flags)
    : GPAContext(hwInfo, flags)
{
    m_physicalDevice = openInfo->physicalDevice;
    m_device = openInfo->device;

    m_amdDeviceProperties = {};
}

VkGPAContext::~VkGPAContext()
{
    VkUtils::ReleasePhysicalDeviceGpaPropertiesAMD(&m_amdDeviceProperties);

    std::lock_guard<std::mutex> lockSessionList(m_sessionListMutex);

    for (auto sessionIter = m_gpaSessionList.begin(); sessionIter != m_gpaSessionList.end(); ++sessionIter)
    {
        DeleteVkGpaSession(reinterpret_cast<VkGPASession*>(*sessionIter));
    }

    m_gpaSessionList.clear();
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
        result = SetStableClocks(true);

        if (GPA_STATUS_OK == result && OpenCounters())
        {
            SetAsOpened(true);
        }
        else
        {
            result = GPA_STATUS_ERROR_FAILED;

            GPA_LogError("Driver was unable to set stable clocks for profiling.");
#ifdef __linux__
            GPA_LogMessage("In Linux, make sure to run your application with root privileges.");
#endif //__linux__

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

        VkResult clockResult = _vkSetGpaDeviceClockModeAMD(m_device, &clockMode);
        result = (clockResult == VK_SUCCESS) ? GPA_STATUS_OK : GPA_STATUS_ERROR_DRIVER_NOT_SUPPORTED;

        if (clockResult != VK_SUCCESS)
        {
            GPA_LogError("Failed to set ClockMode for profiling.");
        }
    }

    return result;
}

GPA_SessionId VkGPAContext::CreateSession()
{
    GPA_SessionId sessionId = nullptr;

    VkGPASession* pSession = new (std::nothrow) VkGPASession(this);

    if (nullptr != pSession)
    {
        std::lock_guard<std::mutex> lockSessionList(m_sessionListMutex);
        m_gpaSessionList.push_back(pSession);
        sessionId = reinterpret_cast<GPA_SessionId>(GPAUniqueObjectManager::Instance()->CreateObject(pSession));
    }

    return sessionId;
}

bool VkGPAContext::DeleteSession(GPA_SessionId sessionId)
{
    bool isDeleted = false;

    std::lock_guard<std::mutex> lockSessionList(m_sessionListMutex);

    VkGPASession* pVkSession = reinterpret_cast<VkGPASession*>(sessionId->Object());
    isDeleted = DeleteVkGpaSession(pVkSession);

    return isDeleted;
}

bool VkGPAContext::DeleteVkGpaSession(VkGPASession* pVkGpaSession)
{
    if (nullptr != pVkGpaSession)
    {
        m_gpaSessionList.remove(pVkGpaSession);
        GPAUniqueObjectManager::Instance()->DeleteObject(pVkGpaSession);
        delete pVkGpaSession;
    }

    return true;
}

gpa_uint32 VkGPAContext::GetMaxGPASessions() const
{
    // there is no maximum number of sessions
    return 0;
}

bool VkGPAContext::DoesSessionExist(GPA_SessionId sessionId) const
{
    std::lock_guard<std::mutex> lockSessionList(m_sessionListMutex);
    GPASessionList::const_iterator search = m_gpaSessionList.cbegin();
    while (search != m_gpaSessionList.end() && *search != reinterpret_cast<VkGPASession*>(sessionId))
    {
        ++search;
    }
    return (search != m_gpaSessionList.end());
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
        instanceCount = static_cast<gpa_uint32>(m_amdDeviceProperties.pPerfBlocks[static_cast<size_t>(block)].instanceCount);
    }

    return instanceCount;
}

gpa_uint32 VkGPAContext::GetMaxEventIdCount(VkGpaPerfBlockAMD block) const
{
    gpa_uint32 maxEventId = 0;

    if (block < VK_GPA_PERF_BLOCK_RANGE_SIZE_AMD)
    {
        maxEventId = static_cast<gpa_uint32>(m_amdDeviceProperties.pPerfBlocks[static_cast<size_t>(block)].maxEventID);
    }

    return maxEventId;
}
