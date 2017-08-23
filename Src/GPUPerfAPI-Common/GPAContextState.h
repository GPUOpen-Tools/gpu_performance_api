//==============================================================================
// Copyright (c) 2011-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage GPA Context state
//==============================================================================

#ifndef _GPA_CONTEXT_STATE_H_
#define _GPA_CONTEXT_STATE_H_

#include <vector>
#include "GPADataRequest.h"
#include "GPASessionRequests.h"
#include "CircularBuffer.h"
#include "GPAHWInfo.h"

#include "GPAInternalCounter.h"
#include "GPACounterGeneratorBase.h"
#include "GPAICounterScheduler.h"

/// Device clock mode enum used to decode usage of GPA_OpenContext mode flag
enum class DeviceClockMode : uint32_t
{
    Default,        ///< Device clocks and other power settings are restored to default.
    MinimumEngine,  ///< Engine clock is set to the lowest available level. Memory clock is set to
                    ///  thermal and power sustainable level.
    MinimumMemory,  ///< Memory clock is set to the lowest available level. Engine clock is set to
                    ///  thermal and power sustainable level.
    Peak,           ///< Clocks set to maximum when possible. Fan set to maximum. Note: Under power
                    ///  and thermal constraints device will clock down.
    Profiling,      ///< Scale down from peak ratio. Clocks are set to a constant amount which is
                    ///  known to be power and thermal sustainable. The engine/memory clock ratio
                    ///  will be kept the same as much as possible.
};

/// Creates a new data request.
/// \return A pointer to a new data request.
GPA_DataRequest* GPA_IMP_CreateDataRequest();

/// Stores state for each context including which counters are enabled,
/// which pass we are on, etc.
class GPA_ContextState
{
public:
    /// Initializes an instance of the GPA_ContextState class.
    GPA_ContextState();

    /// Virtual Destructor
    virtual ~GPA_ContextState();

    /// Initialize the context
    virtual void Init();

    /// Get a data request for the specified pass number.
    /// Default implementation recycles expired requests.
    /// \param passNumber The pass number for which to get a data request.
    /// \return A data request object that can be used for the specified pass.
    virtual GPA_DataRequest* GetDataRequest(gpa_uint32 passNumber);

    /// Finds the specified session if it is available.
    /// \param sessionID The ID of the session to find.
    /// \return The specified session if available, otherwise nullptr if not found.
    virtual GPA_SessionRequests* FindSession(gpa_uint32 sessionID);

    /// Set Context Flags
    /// \param flags The supplied flags to set.
    inline void SetFlags(GPA_OpenContextFlags flags)
    {
        m_flags = flags;
    }
    
    /// Check to see if public counters should be exposed.
    /// \return true if public counters should be exposed; false otherwise.
    inline bool ExposePublicCounters()
    {
        return (m_flags & GPA_OPENCONTEXT_HIDE_PUBLIC_COUNTERS_BIT) == 0;
    }

    /// Check to see if software counters should be exposed.
    /// \return true if software counters should be exposed; false otherwise.
    inline bool ExposeSoftwareCounters()
    {
        return (m_flags & GPA_OPENCONTEXT_HIDE_SOFTWARE_COUNTERS_BIT) == 0;
    }

    /// Check to see if hardware counters should be exposed.
    /// \return true if hardware counters should be exposed; false otherwise.
    inline bool ExposeHardwareCounters()
    {
        return (m_flags & GPA_OPENCONTEXT_HIDE_HARDWARE_COUNTERS_BIT) == 0;
    }

    /// Flag to invalidate and flush the L2 cache around the next counter sample
    inline void SetInvalidateAndFlushL2Cache(bool b)
    {
        m_invalidateAndFlushL2Cache = b;
    }

    inline bool GetInvalidateAndFlushL2Cache() const
    {
        return m_invalidateAndFlushL2Cache;
    }

    /// Gets device clock mode behavior
    /// \return DeviceClockMode enum indicating clock mode behavior
    inline DeviceClockMode GetDeviceClockMode() const
    {
        if (m_flags & GPA_OPENCONTEXT_CLOCK_MODE_NONE_BIT)
        {
            return DeviceClockMode::Default;
        }

        if (m_flags & GPA_OPENCONTEXT_CLOCK_MODE_PEAK_BIT)
        {
            return DeviceClockMode::Peak;
        }

        if (m_flags & GPA_OPENCONTEXT_CLOCK_MODE_MIN_MEMORY_BIT)
        {
            return DeviceClockMode::MinimumMemory;
        }

        if (m_flags & GPA_OPENCONTEXT_CLOCK_MODE_MIN_ENGINE_BIT)
        {
            return DeviceClockMode::MinimumEngine;
        }

        return DeviceClockMode::Profiling;
    }

    /// The current API-specific context.
    /// It is public to allow access by DLL entry point functions which would usually be part of the class.
    void* m_pContext;

    // session vars
    gpa_uint32 m_sessionID;         ///< The ID of the current session allocated
    gpa_uint32 m_currentPass;       ///< The current pass number within the session
    GPA_OpenContextFlags m_flags;   ///< The flags that were supplied to open the context

    gpa_uint32 m_currentSample; ///< The current sample Id
    bool m_samplingStarted;     ///< Indicates whether or not sampling has started and not ended.
    bool m_sampleStarted;       ///< Indicates whether or not a sample is started and not ended.
    gpa_uint32 m_selectionID;   ///< The ID of the current counter selection

    // pass vars
    bool m_passStarted;                 ///< Indicates that a pass was started and not ended
    gpa_uint32 m_sampleCount;           ///< number of samples performed in the current pass
    gpa_uint32 m_firstPassSampleCount;  ///< number of samples performed in the first pass, for error checking

    /// max simultaneous sessions
    gpa_uint32 m_maxSessions;

    CircularBuffer<GPA_SessionRequests> m_profileSessions; ///< The available set of data requests. size is m_maxSessions
    GPA_SessionRequests* m_pCurrentSessionRequests;        ///< Pointer to an element in m_profileSessions, which is the current session

    /// structure that stores hardware information
    GPA_HWInfo m_hwInfo;

    /// Counter scheduler
    GPA_ICounterScheduler* m_pCounterScheduler;

    /// Counter accessor
    GPA_CounterGeneratorBase* m_pCounterAccessor;

    /// Flag to invalidate and flush the L2 cache around the next counter sample
    bool m_invalidateAndFlushL2Cache;
};

#endif //_GPA_CONTEXT_STATE_H_
