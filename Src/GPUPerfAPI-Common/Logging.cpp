//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Logging utility
//==============================================================================

#include "Logging.h"

#ifdef _WIN32
    #pragma comment( lib, "Winmm.lib" )
#endif

static const char MUTEX_NAME[]     = "GPALoggerMutex"; ///< mutex name

GPATracer gTracerSingleton;
GPALogger g_loggerSingleton;

GPATracer::GPATracer()
{
    m_logTab = 0;

#ifdef AMDT_INTERNAL
    // in internal builds, we want all the tracing to be displayed
    m_topLevelOnly = false;
#else
    // in public builds, the end-user should only see the functions they call
    m_topLevelOnly = true;
#endif // AMDT_INTERNAL
}


void GPATracer::EnterFunction(const char* pFunctionName)
{
    if ((!m_logTab && m_topLevelOnly) || !m_topLevelOnly)
    {
        std::string message;

        for (unsigned int tempLogTab = 0; tempLogTab < m_logTab; tempLogTab++)
        {
            message += "   ";
        }

        message += "Entering: ";
        message += pFunctionName;
        message += ".";

#ifdef AMDT_INTERNAL
        GPA_LogDebugTrace(message.c_str());

        if (m_logTab == 0)
        {
            // if this is the top level, also pass it to the normal LogTrace
            GPA_LogTrace(message.c_str());
        }

#else
        GPA_LogTrace(message.c_str());
#endif // AMDT_INTERNAL
    }

    m_logTab++;
}


void GPATracer::LeaveFunction(const char* pFunctionName)
{
    m_logTab--;

    if ((!m_logTab && m_topLevelOnly) || !m_topLevelOnly)
    {
        std::string message;

        for (unsigned int tempLogTab = 0; tempLogTab < m_logTab; tempLogTab++)
        {
            message += "   ";
        }

        message += "Leaving: ";
        message += pFunctionName;
        message += ".";

#ifdef AMDT_INTERNAL
        GPA_LogDebugTrace(message.c_str());

        if (m_logTab == 0)
        {
            // if this is the top level, also pass it to the normal LogTrace
            GPA_LogTrace(message.c_str());
        }

#else
        GPA_LogTrace(message.c_str());
#endif // AMDT_INTERNAL
    }
}


ScopeTrace::ScopeTrace(const char* pTraceFunction)
{
    gTracerSingleton.EnterFunction(pTraceFunction);
    m_pTraceFunction = pTraceFunction;
}

ScopeTrace::~ScopeTrace()
{
    gTracerSingleton.LeaveFunction(m_pTraceFunction);
}



GPALogger::GPALogger():
    m_loggingType(GPA_LOGGING_NONE),
    m_loggingCallback(nullptr)
{
#ifdef _WIN32
    InitializeCriticalSection(&m_hLock);
#endif

#ifdef _LINUX
    pthread_mutexattr_t mutexattr;
    pthread_mutexattr_init(&mutexattr);
    // Set the mutex as a recursive mutex
    pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE_NP);

    // create the mutex with the attributes set
    pthread_mutex_init(&m_hLock, &mutexattr);

    //After initializing the mutex, the thread attribute can be destroyed
    pthread_mutexattr_destroy(&mutexattr);
#endif
}

void GPALogger::SetLoggingCallback(GPA_Logging_Type loggingType, GPA_LoggingCallbackPtrType loggingCallback)
{
    if (nullptr == loggingCallback)
    {
        m_loggingCallback = nullptr;
        m_loggingType = GPA_LOGGING_NONE;
    }
    else
    {
        m_loggingCallback = loggingCallback;
        m_loggingType = loggingType;
    }
}

void GPALogger::Log(GPA_Logging_Type logType, const char* pMessage)
{
    EnterCriticalSection(&m_hLock);

    // if the supplied message type is among those that the user wants be notified of,
    // then pass the message along.
    if ((logType & m_loggingType) &&
        nullptr != m_loggingCallback)
    {
        m_loggingCallback(logType, pMessage);
    }

    LeaveCriticalSection(&m_hLock);
}

GPALogger::~GPALogger()
{
#ifdef _WIN32
    DeleteCriticalSection(&m_hLock);
#else
    pthread_mutex_destroy(&m_hLock);
#endif
}
