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

#include "../GPUPerfAPICounterGenerator/GPAInternalCounter.h"
#include "../GPUPerfAPICounterGenerator/GPACounterGeneratorBase.h"
#include "../GPUPerfAPICounterGenerator/GPAICounterScheduler.h"

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

    ///// called by BeginSampling when a newSession is allocated
    ///// this session could be brand new, or an existing session which needs to be recycled
    ///// m_requests should not contain any objects upon return
    ///// m_expiredRequests is used to store expired requests by default
    ///// an alternative implementation could be to just delete the expired requests,
    ///// and always allocate new
    //virtual void RecycleCurrentSession();

    /// Finds the specified session if it is available.
    /// \param sessionID The ID of the session to find.
    /// \return The specified session if available, otherwise nullptr if not found.
    virtual GPA_SessionRequests* FindSession(gpa_uint32 sessionID);

    /// The current API-specific context.
    /// It is public to allow access by DLL entry point functions which would usually be part of the class.
    void* m_pContext;

    // session vars
    gpa_uint32 m_sessionID;    ///< The ID of the current session allocated
    gpa_uint32 m_currentPass;  ///< The current pass number within the session

    gpa_uint32 m_currentSample; ///< The current sample Id
    bool m_samplingStarted;    ///< Indicates whether or not sampling has started and not ended.
    bool m_sampleStarted;      ///< Indicates whether or not a sample is started and not ended.
    gpa_uint32 m_selectionID;  ///< The ID of the current counter selection

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
};

#endif //_GPA_CONTEXT_STATE_H_
