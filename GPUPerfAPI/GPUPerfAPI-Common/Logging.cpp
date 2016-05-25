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

#ifdef GDT_INTERNAL
    // in internal builds, we want all the tracing to be displayed
    m_topLevelOnly = false;
#else
    // in public builds, the end-user should only see the functions they call
    m_topLevelOnly = true;
#endif // GDT_INTERNAL
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

#ifdef GDT_INTERNAL
        GPA_LogDebugTrace(message.c_str());

        if (m_logTab == 0)
        {
            // if this is the top level, also pass it to the normal LogTrace
            GPA_LogTrace(message.c_str());
        }

#else
        GPA_LogTrace(message.c_str());
#endif // GDT_INTERNAL
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

#ifdef GDT_INTERNAL
        GPA_LogDebugTrace(message.c_str());

        if (m_logTab == 0)
        {
            // if this is the top level, also pass it to the normal LogTrace
            GPA_LogTrace(message.c_str());
        }

#else
        GPA_LogTrace(message.c_str());
#endif // GDT_INTERNAL
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



GPALogger::GPALogger()
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

#ifdef GDT_INTERNAL
void GPALogger::SetLoggingDebugCallback(GPA_Log_Debug_Type loggingType, GPA_LoggingDebugCallbackPtrType loggingDebugCallback)
{
    if (nullptr == loggingDebugCallback)
    {
        m_loggingDebugCallback = nullptr;
        m_loggingDebugType = GPA_LOG_NONE;
    }
    else
    {
        m_loggingDebugCallback = loggingDebugCallback;
        m_loggingDebugType = loggingType;
    }
}
#endif // GDT_INTERNAL

void GPALogger::Log(GPA_Log_Debug_Type logType, const char* pMessage)
{
    EnterCriticalSection(&m_hLock);

#ifdef GDT_INTERNAL

    if (logType > GPA_LOG_ALL)
    {
        // this is in the debug message range,
        // so log it to the debug callback
        if ((logType & m_loggingDebugType) &&
            nullptr != m_loggingDebugCallback)
        {
            m_loggingDebugCallback(logType, pMessage);
        }

    }
    else
#endif // GDT_INTERNAL
    {
        // convert from private GPA_Log_Debug_type to public GPA_Logging_Type
        GPA_Logging_Type messageType = (GPA_Logging_Type)logType;

        // if the supplied message type is among those that the user wants be notified of,
        // then pass the message along.
        if ((messageType & m_loggingType) &&
            nullptr != m_loggingCallback)
        {
            m_loggingCallback(messageType, pMessage);
        }
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
