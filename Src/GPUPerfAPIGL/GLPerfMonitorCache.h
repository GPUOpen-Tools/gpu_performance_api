//==============================================================================
// Copyright (c) 2014-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage caching (reusing) perf monitors for identical counter sets
//==============================================================================

#ifndef _GL_PERFMONITOR_CACHE_H_
#define _GL_PERFMONITOR_CACHE_H_

#include <TSingleton.h>

#include "GPUPerfAPIGL.h"

class GLCounterDataRequest;  ///< forward declaration

/// Class to manage caching (reusing) perf monitors for identical counter sets
class GLPerfMonitorCache : public TSingleton<GLPerfMonitorCache>
{
public:
    /// Gets a perf monitor to be used for the specified counters. Increments the cache's ref count on the monitor
    /// \param[in] pCounterIndices list of counter indices which need a perf monitor
    /// \param[in] pCounterDataRequest the GLCounterDataRequest requesting a perf monitor.
    /// \param[out] monitor the perf monitor
    /// \param[out] pPreviousCounterDataRequest If the perf monitor already exists, then pPreviousCounterDataRequest is set to most recent instance that used this perf monitor
    /// \return true if the perf monitor is newly created, false if it already existed
    bool GetMonitorForCounters(const vector<gpa_uint32>* pCounterIndices, GLCounterDataRequest* pCounterDataRequest, GLuint& monitor, GLCounterDataRequest*& pPreviousCounterDataRequest);

    /// Enables the specified counter in the monitor
    /// \param monitor the monitor to use to enable counters
    /// \param uiGroupId the group id of the counter to enable
    /// \param uiCounterIndex the counter index of the counter to enable
    void EnableCounterInMonitor(GLuint monitor, gpa_uint32 uiGroupId, gpa_uint64 uiCounterIndex);

    /// Called to indicate that a perf monitor is no longer used. Decrements the cache's ref count on the monitor-- when the ref count reaches zero, the montitor is destroyed and removed from the cache
    /// \param monitor the monitor that is no longer used
    void DoneMonitor(GLuint monitor);

private:

    /// struct to reference a hw counter
    struct GLHardwareCounter
    {
        gpa_uint32 m_groupId;      ///< the group id of the counter
        gpa_uint64 m_counterIndex; ///< the index of the counter within the group
    };

    /// struct to cache perf monitors
    struct MonitorInfo
    {
        vector<gpa_uint32>        m_counterIndices;  ///< list of counter indices associated with a perf monitor
        GLCounterDataRequest*     m_prevDataRequest; ///< the most recent data request object associated with a perf monitor
        unsigned int              m_refCount;        ///< the number of data requests using a perf monitor
        vector<GLHardwareCounter> m_hwCounters;      ///< list of hardware counters enabled in a perf monitor
    };

    /// Map from a perf monitor to a MonitorInfo instance
    typedef std::map<GLuint, MonitorInfo> MonitorInfoMap;

    MonitorInfoMap m_monitorInfoMap; ///< Map from a perf monitor to a MonitorInfo instance
};

#endif // _GL_PERFMONITOR_CACHE_H_
