//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Logging utility
//==============================================================================

#include "Logging.h"
#include <assert.h>
#include "Utility.h"

#ifdef _WIN32
#pragma comment(lib, "Winmm.lib")
#endif

GPATracer gTracerSingleton;
GPALogger g_loggerSingleton;

void GPAInternalLogger(GPA_Logging_Type logType, const char* pLogMsg)
{
    if (GPA_LOGGING_INTERNAL == logType)
    {
        if (g_loggerSingleton.m_internalLoggingFileStream.is_open())
        {
            g_loggerSingleton.m_internalLoggingFileStream << "GPA Internal Logging: " << pLogMsg << std::endl;
        }
    }
}

GPATracer::GPATracer()
{
#ifdef AMDT_INTERNAL
    // in internal builds, we want all the tracing to be displayed
    m_topLevelOnly = false;
#else
    // in public builds, the end-user should only see the functions they call
    m_topLevelOnly = true;
#endif  // AMDT_INTERNAL
}

void GPATracer::EnterFunction(const char* pFunctionName)
{
    std::thread::id currentThreadId;
    auto            tabCounter = GetTabCounter(&currentThreadId);

    if ((!tabCounter->second && m_topLevelOnly) || !m_topLevelOnly)
    {
        std::stringstream message;

        for (int32_t tempLogTab = 0; tempLogTab < tabCounter->second; tempLogTab++)
        {
            message << "   ";
        }

        message << "Thread " << currentThreadId << " ";
        message << "Enter: ";
        message << pFunctionName;
        message << ".";

#ifdef AMDT_INTERNAL
        GPA_LogDebugTrace(message.str().c_str());

        if (tabCounter->second == 0)
        {
            // if this is the top level, also pass it to the normal LogTrace
            GPA_LogTrace(message.str().c_str());
        }

#else
        GPA_LogTrace(message.str().c_str());
#endif  // AMDT_INTERNAL
    }

    ++tabCounter->second;
}

void GPATracer::LeaveFunction(const char* pFunctionName)
{
    std::thread::id currentThreadId;
    auto            tabCounter = GetTabCounter(&currentThreadId);

    if (tabCounter->second > 0)
    {
        --tabCounter->second;
    }

    if ((!tabCounter->second && m_topLevelOnly) || !m_topLevelOnly)
    {
        std::stringstream message;

        for (int32_t tempLogTab = 0; tempLogTab < tabCounter->second; tempLogTab++)
        {
            message << "   ";
        }

        message << "Thread " << currentThreadId << " ";
        message << "Leave: ";
        message << pFunctionName;
        message << ".";

#ifdef AMDT_INTERNAL
        GPA_LogDebugTrace(message.str().c_str());

        if (tabCounter->second == 0)
        {
            // if this is the top level, also pass it to the normal LogTrace
            GPA_LogTrace(message.str().c_str());
        }

#else
        GPA_LogTrace(message.str().c_str());
#endif  // AMDT_INTERNAL
    }
}

void GPATracer::OutputFunctionData(const char* pData)
{
    std::thread::id currentThreadId;
    auto            tabCounter = GetTabCounter(&currentThreadId);

    if (((tabCounter->second) == 1 && m_topLevelOnly) || !m_topLevelOnly)
    {
        std::stringstream message;

        for (int32_t tempLogTab = 0; tempLogTab < tabCounter->second; tempLogTab++)
        {
            message << "   ";
        }

        message << "Thread " << currentThreadId << " ";
        message << pData;
        message << ".";

#ifdef AMDT_INTERNAL
        GPA_LogDebugTrace(message.str().c_str());

        if (tabCounter->second == 0)
        {
            // if this is the top level, also pass it to the normal LogTrace
            GPA_LogTrace(message.str().c_str());
        }

#else
        GPA_LogTrace(message.str().c_str());
#endif  // AMDT_INTERNAL
    }
}

std::map<std::thread::id, int32_t>::iterator GPATracer::GetTabCounter(std::thread::id* pCurrentThreadId)
{
    std::lock_guard<std::mutex> lock(m_tracerMutex);

    *pCurrentThreadId = std::this_thread::get_id();

    std::map<std::thread::id, int32_t>::iterator ret = m_threadTabCountMap.find(*pCurrentThreadId);

    if (ret == m_threadTabCountMap.end())
    {
        m_threadTabCountMap[*pCurrentThreadId] = 0;
        ret                                    = m_threadTabCountMap.find(*pCurrentThreadId);
    }

#ifdef _DEBUG
    // Validate tab value
    const int32_t MAX_TAB_COUNT = 1024;
    assert(ret->second >= 0 && ret->second < MAX_TAB_COUNT);
#endif

    return ret;
}

ScopeTrace::ScopeTrace(const char* pTraceFunction)
{
    if (g_loggerSingleton.IsTracingEnabled())
    {
        gTracerSingleton.EnterFunction(pTraceFunction);
        m_traceFunction = pTraceFunction;
    }
}

ScopeTrace::~ScopeTrace()
{
    if (g_loggerSingleton.IsTracingEnabled())
    {
        gTracerSingleton.LeaveFunction(m_traceFunction.c_str());
    }
}

GPALogger::GPALogger()
    : m_loggingType(GPA_LOGGING_NONE)
    , m_loggingCallback(nullptr)
    , m_enableInternalLogging(false)
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

#ifdef _DEBUG
    std::string currentModulePath;
    GPAUtil::GetCurrentModulePath(currentModulePath);
    m_internalLogFileName = currentModulePath + "GPA-Internal-Log.txt";
    std::remove(m_internalLogFileName.c_str());
    m_internalLoggingFileStream.open(m_internalLogFileName.c_str(), std::ios_base::out | std::ios_base::app);
#endif
}

void GPALogger::SetLoggingCallback(GPA_Logging_Type loggingType, GPA_LoggingCallbackPtrType loggingCallback)
{
    if (nullptr == loggingCallback)
    {
        m_loggingCallback = nullptr;
        m_loggingType     = GPA_LOGGING_NONE;
    }
    else
    {
        m_loggingCallback = loggingCallback;
        m_loggingType     = loggingType;
    }
}

void GPALogger::Log(GPA_Logging_Type logType, const char* pMessage)
{
    EnterCriticalSection(&m_hLock);

    // if the supplied message type is among those that the user wants be notified of,
    // then pass the message along.
    if ((logType & m_loggingType) && nullptr != m_loggingCallback)
    {
        m_loggingCallback(logType, pMessage);

        if (m_enableInternalLogging)
        {
            m_gpaInternalLogger(logType, pMessage);
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
