//==============================================================================
// Copyright (c) 2011-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class to manage GPA Context state
//==============================================================================

#include "GPAContextState.h"

GPA_ContextState::GPA_ContextState()
{
    Init();
}

GPA_ContextState::~GPA_ContextState()
{
}

void GPA_ContextState::Init()
{
    m_sessionID = 0;
    m_flags = 0;
    m_currentPass = 0;
    m_currentSample = 0;
    m_samplingStarted = false;
    m_sampleStarted = false;
    m_selectionID = 0;
    m_passStarted = false;
    m_sampleCount = 0;
    m_firstPassSampleCount = 0;
    m_maxSessions = 0;
    m_pCurrentSessionRequests = nullptr;
    m_pCounterScheduler = nullptr;
    m_pCounterAccessor = nullptr;
    m_invalidateAndFlushL2Cache = false;
}

GPASample* GPA_ContextState::GetDataRequest(gpa_uint32 passNumber)
{
    UNREFERENCED_PARAMETER(passNumber);
    return nullptr;
    //return GPA_IMP_CreateDataRequest();
}

IGPASession* GPA_ContextState::FindSession(gpa_uint32 sessionID)
{
    for (gpa_uint32 i = 0; i < m_profileSessions.getCount(); i++)
    {
        // search from oldest to newest
        IGPASession* checkSession = m_profileSessions.getRelative(i);

        if (checkSession.m_sessionID == sessionID)
        {
            return (&checkSession);
        }
    }

    return nullptr;
}

