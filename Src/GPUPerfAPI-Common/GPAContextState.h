//==============================================================================
// Copyright (c) 2011-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage GPA Context state
//==============================================================================

#ifndef _GPA_CONTEXT_STATE_H_
#define _GPA_CONTEXT_STATE_H_

#include <vector>
#include "GPASample.h"
#include "IGPASession.h"
#include "CircularBuffer.h"
#include "GPAHWInfo.h"

#include "GPAInternalCounter.h"
#include "GPACounterGeneratorBase.h"
#include "IGPACounterScheduler.h"

/// Check to see if public counters should be exposed.
/// \param flags The supplied flags to check.
/// \return true if public counters should be exposed; false otherwise.
inline bool ExposePublicCounters(GPA_OpenContextFlags flags)
{
    return (flags & GPA_OPENCONTEXT_HIDE_PUBLIC_COUNTERS_BIT) == 0;
}

/// Check to see if software counters should be exposed.
/// \param flags The supplied flags to check.
/// \return true if software counters should be exposed; false otherwise.
inline bool ExposeSoftwareCounters(GPA_OpenContextFlags flags)
{
    return (flags & GPA_OPENCONTEXT_HIDE_SOFTWARE_COUNTERS_BIT) == 0;
}

/// Check to see if hardware counters should be exposed.
/// \param flags The supplied flags to check.
/// \return true if hardware counters should be exposed; false otherwise.
inline bool ExposeHardwareCounters(GPA_OpenContextFlags flags)
{
    return (flags & GPA_OPENCONTEXT_HIDE_HARDWARE_COUNTERS_BIT) == 0;
}

///// Creates a new data request.
///// \return A pointer to a new data request.
//GPA_DataRequest* GPA_IMP_CreateDataRequest();

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
    virtual GPASample* GetDataRequest(gpa_uint32 passNumber);

    /// Finds the specified session if it is available.
    /// \param sessionID The ID of the session to find.
    /// \return The specified session if available, otherwise nullptr if not found.
    virtual IGPASession* FindSession(gpa_uint32 sessionID);

    /// Set Context Flags
    /// \param flags The supplied flags to set.
    inline void SetFlags(GPA_OpenContextFlags flags)
    {
        m_flags = flags;
    }

    /// Check to see if public counters should be exposed.
    /// \return true if public counters should be exposed; false otherwise.
    inline bool ExposePublicCounters() const
    {
        return ::ExposePublicCounters(m_flags);
    }

    /// Check to see if software counters should be exposed.
    /// \return true if software counters should be exposed; false otherwise.
    inline bool ExposeSoftwareCounters() const
    {
        return ::ExposeSoftwareCounters(m_flags);
    }

    /// Check to see if hardware counters should be exposed.
    /// \return true if hardware counters should be exposed; false otherwise.
    inline bool ExposeHardwareCounters() const
    {
        return ::ExposeHardwareCounters(m_flags);
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

    CircularBuffer<IGPASession*> m_profileSessions; ///< The available set of data requests. size is m_maxSessions
    IGPASession* m_pCurrentSessionRequests;        ///< Pointer to an element in m_profileSessions, which is the current session


};

#endif //_GPA_CONTEXT_STATE_H_
