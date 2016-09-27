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
}

GPA_DataRequest* GPA_ContextState::GetDataRequest(gpa_uint32 passNumber)
{
    UNREFERENCED_PARAMETER(passNumber);
    //if ( m_expiredRequests.m_requests.size() > passNumber )
    //{
    //   // try and reuse an expired request
    //   std::map<gpa_uint32, GPA_DataRequest*>* pExpiredPassRequests = &(m_expiredRequests.m_requests[passNumber]);
    //   if (pExpiredPassRequests->size() > 0)
    //   {
    //      GPA_DataRequest* expiredRequest = pExpiredPassRequests->begin()->second;
    //      pExpiredPassRequests->erase(pExpiredPassRequests->begin()->first);
    //      return expiredRequest;
    //   }

    //   // otherwise search thru all passes and take the first found
    //   for (std::vector<std::map<gpa_uint32, GPA_DataRequest*> >::iterator requestIter = m_expiredRequests.m_requests.begin(); requestIter != m_expiredRequests.m_requests.end(); ++requestIter)
    //   {
    //      if ( requestIter->size() > 0 )
    //      {
    //         GPA_DataRequest* expiredRequest = requestIter->begin()->second;
    //         requestIter->erase(requestIter->begin()->first);
    //         return expiredRequest;
    //      }
    //   }
    //}

    // none available, need to create a new request
    return GPA_IMP_CreateDataRequest();
}


//// called by BeginSession when a newSession is allocated
//// this session could be brand new, or an existing session which needs to be recycled
//// m_requests should not contain any objects upon return
//// m_expiredRequests is used to store expired requests by default
//// an alternative implementation could be to just delete the expired requests,
//// and always allocate new
//void GPA_ContextState::RecycleCurrentSession()
//{
//   // assumes from this point all requests in the currentSession have been expired
//   // remove old requests from session and put them in the context expired requests list
//   gpa_uint32 numPasses = ( gpa_uint32 )m_currentSessionRequests->m_requests.size();
//
//   // make sure expired request vec has enough passes
//   if ( m_expiredRequests.m_requests.size() < numPasses )
//   {
//      m_expiredRequests.m_requests.resize( numPasses );
//   }
//
//   std::map<gpa_uint32, GPA_DataRequest*>* pActivePassRequests = nullptr;
//   std::map<gpa_uint32, GPA_DataRequest*>* pExpiredPassRequests = nullptr;
//   for ( gpa_uint32 i = 0 ; i < numPasses ; i++ )
//   {
//      pActivePassRequests = &(m_currentSessionRequests->m_requests[i]);
//      pExpiredPassRequests = &(m_expiredRequests.m_requests[i]);
//      for (std::map<gpa_uint32, GPA_DataRequest*>::iterator activeRequestIter = pActivePassRequests->begin(); activeRequestIter != pActivePassRequests->end(); ++activeRequestIter)
//      {
//         pExpiredPassRequests->insert(pExpiredPassRequests->begin(), *activeRequestIter);
//      }
//   }
//
//   // clear the request structure
//   m_currentSessionRequests->m_requests.clear();
//}

GPA_SessionRequests* GPA_ContextState::FindSession(gpa_uint32 sessionID)
{
    for (gpa_uint32 i = 0; i < m_profileSessions.getCount(); i++)
    {
        // search from oldest to newest
        GPA_SessionRequests& checkSession = m_profileSessions.getRelative(i);

        if (checkSession.m_sessionID == sessionID)
        {
            return (&checkSession);
        }
    }

    return nullptr;
}

