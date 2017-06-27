//==============================================================================
// Copyright (c) 2014-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage caching (reusing) perf monitors for identical counter sets
//==============================================================================

#include <ADLUtil.h>

#include "Logging.h"
#include "GLPerfMonitorCache.h"

bool GLPerfMonitorCache::GetMonitorForCounters(const vector<gpa_uint32>* pCounterIndices, GLCounterDataRequest* pCounterDataRequest, GLuint& monitor, GLCounterDataRequest*& pPreviousCounterDataRequest)
{
    bool bFound = false;
    MonitorInfo monitorInfo;

    for (MonitorInfoMap::reverse_iterator iter = m_monitorInfoMap.rbegin(); iter != m_monitorInfoMap.rend() && !bFound; ++iter)
    {
        monitorInfo = iter->second;

        if (monitorInfo.m_counterIndices == *pCounterIndices)
        {
            bFound = true;
            pPreviousCounterDataRequest = monitorInfo.m_prevDataRequest;
            monitorInfo.m_prevDataRequest = pCounterDataRequest;
            monitor = iter->first;
        }
    }

    if (!bFound)
    {
        _oglGenPerfMonitorsAMD(1, &monitor);

        monitorInfo.m_counterIndices = *pCounterIndices;
        monitorInfo.m_prevDataRequest = pCounterDataRequest;
        monitorInfo.m_refCount = 0;
        pPreviousCounterDataRequest = nullptr;
        GPA_LogDebugMessage("Created Monitor: %u.", monitor);
    }

    monitorInfo.m_refCount++;
    m_monitorInfoMap[monitor] = monitorInfo;

    return !bFound;
}

void GLPerfMonitorCache::EnableCounterInMonitor(GLuint monitor, gpa_uint32 uiGroupId, gpa_uint64 uiCounterIndex)
{
    MonitorInfoMap::iterator iter = m_monitorInfoMap.find(monitor);
    assert(m_monitorInfoMap.end() != iter);

    if (m_monitorInfoMap.end() != iter)
    {
        _oglSelectPerfMonitorCountersAMD(monitor, GL_TRUE, uiGroupId, 1, (GLuint*)&uiCounterIndex);
        GPA_LogDebugMessage("Enabled counter: group %u, counter %u.", uiGroupId, uiCounterIndex);
#ifdef DEBUG_GL_ERRORS
        CheckForGLErrors("Error detected after glSelectPerfMonitorCountersAMD(..).");
#endif
        GLHardwareCounter hwCounter;
        hwCounter.m_groupId = uiGroupId;
        hwCounter.m_counterIndex = uiCounterIndex;
        iter->second.m_hwCounters.push_back(hwCounter);
    }
}

void GLPerfMonitorCache::DoneMonitor(GLuint monitor)
{
    MonitorInfoMap::iterator iter = m_monitorInfoMap.find(monitor);

    if (m_monitorInfoMap.end() != iter)
    {
        MonitorInfo* monitorInfo = &iter->second;
        monitorInfo->m_refCount--;

        if (monitorInfo->m_refCount == 0)
        {
            for (vector<GLHardwareCounter>::iterator hwcIter = monitorInfo->m_hwCounters.begin(); hwcIter != monitorInfo->m_hwCounters.end(); ++hwcIter)
            {
                _oglSelectPerfMonitorCountersAMD(monitor, GL_FALSE, hwcIter->m_groupId, 1, (GLuint*)&hwcIter->m_counterIndex);
                GPA_LogDebugMessage("Disabled counter: group %u, counter %u.", hwcIter->m_groupId, hwcIter->m_counterIndex);
#ifdef DEBUG_GL_ERRORS
                CheckForGLErrors("Error detected after glSelectPerfMonitorCountersAMD(..).");
#endif
            }

            m_monitorInfoMap.erase(monitor);
            GPA_LogDebugMessage("Deleting Monitor: %u.", monitor);
            bool deletePerfMonitor = true;
#if defined(_LINUX) && defined(X86)
            unsigned int majorVer;
            unsigned int minorVer;
            unsigned int subMinorVer;

            if (AMDTADLUtils::Instance()->GetDriverVersion(majorVer, minorVer, subMinorVer) && 15 > majorVer)
            {
                // Workaround a driver issue by not deleting the perf monitor.
                // The 32-bit Linux driver will crash when glDeletePerfMonitor
                // is called.  This is a HUGE hack and introduces an intentional
                // memory leak.
                // The driver EPR is # 410865, and it was fixed starting with 15.10
                deletePerfMonitor = false;
            }

#endif

            if (deletePerfMonitor)
            {
                _oglDeletePerfMonitorsAMD(1, &monitor);
            }

#ifdef DEBUG_GL_ERRORS
            CheckForGLErrors("Error detected after glDeletePerfMonitorsAMD(..).");
#endif
        }
    }
}
