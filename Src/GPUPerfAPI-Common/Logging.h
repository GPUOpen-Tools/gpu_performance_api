//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Logging utility
//==============================================================================

#ifndef GPA_LOGGING_H_
#define GPA_LOGGING_H_

#ifdef _WIN32
    #include <windows.h>
#endif

#ifdef _LINUX
    #include <pthread.h>
    #include <string.h>

    #define EnterCriticalSection pthread_mutex_lock
    #define LeaveCriticalSection pthread_mutex_unlock
    #include <stdarg.h>
    #include <stdio.h>

#endif

#include <string>
using std::string;

#include "GPUPerfAPITypes.h"
#include "GPUPerfAPIFunctionTypes.h"

#if 1 // enable trace functions ?
    #undef TRACE_FUNCTION
    /// macro for tracing function calls
    #define TRACE_FUNCTION(func) ScopeTrace _tempScopeTraceObject(#func)
    #ifdef AMDT_INTERNAL
        #undef TRACE_PRIVATE_FUNCTION
        #define TRACE_PRIVATE_FUNCTION(func) ScopeTrace _tempScopeTraceObject(#func)
    #else // public build
        #undef TRACE_PRIVATE_FUNCTION
        /// macro for tracing private function calls
        #define TRACE_PRIVATE_FUNCTION(func)
    #endif // AMDT_INTERNAL / public build
#else // disable trace functions
    #undef TRACE_FUNCTION
    #define TRACE_FUNCTION(func)
    #undef TRACE_PRIVATE_FUNCTION
    #define TRACE_PRIVATE_FUNCTION(func)
#endif // trace functions

/// Passes log messages of various types to a user-supplied callback function
/// if the user has elected to receive messages of that particular type.
class GPALogger
{
public:

    /// Default constructor
    GPALogger();

    /// Destructor
    virtual ~GPALogger();

    /// Sets the type of message the user would like to be informed of and a pointer to the callback function.
    /// \param loggingType the type of messages to pass on to the callback function
    /// \param loggingCallback a pointer to the callback function
    void SetLoggingCallback(GPA_Logging_Type loggingType, GPA_LoggingCallbackPtrType loggingCallback);

    /// Passes the supplied message to the callback function if the user has accepted that type of message.
    /// \param logType the type of message being supplied
    /// \param pMessage the message to pass along
    void Log(GPA_Logging_Type logType, const char* pMessage);

    /// Logs an error message.
    /// \param pMessage the message to pass along
    inline void LogError(const char* pMessage)
    {
        Log(GPA_LOGGING_ERROR, pMessage);
    }

    /// Logs an informational message.
    /// \param pMessage the message to pass along
    inline void LogMessage(const char* pMessage)
    {
        Log(GPA_LOGGING_MESSAGE, pMessage);
    }

    /// Logs a trace message.
    /// \param pMessage the message to pass along
    inline void LogTrace(const char* pMessage)
    {
        Log(GPA_LOGGING_TRACE, pMessage);
    }

    /// Logs a formatted message in internal builds; does nothing in release.
    /// \param pMsgFmt the message to format and pass along
    void LogDebugMessage(const char* pMsgFmt, ...)
    {
        // if the supplied message type is among those that the user wants be notified of,
        // then pass the message along.
        if (GPA_LOGGING_DEBUG_MESSAGE & m_loggingType)
        {
            EnterCriticalSection(&m_hLock);

            // Format string
            char buffer[1024 * 50];
            va_list arglist;
            va_start(arglist, pMsgFmt);
#ifdef WIN32
            vsprintf_s(buffer, pMsgFmt, arglist);
#else
            vsprintf(buffer, pMsgFmt, arglist);
#endif
            va_end(arglist);

            Log(GPA_LOGGING_DEBUG_MESSAGE, buffer);

            LeaveCriticalSection(&m_hLock);
        }
    }

    /// Logs a formatted error message in debug builds; does nothing in release.
    /// \param pMsgFmt the message to format and pass along
    void LogDebugError(const char* pMsgFmt, ...)
    {
        // if the supplied message type is among those that the user wants be notified of,
        // then pass the message along.
        if (GPA_LOGGING_DEBUG_ERROR & m_loggingType)
        {
            EnterCriticalSection(&m_hLock);

            // Format string
            char buffer[1024 * 50];
            va_list arglist;
            va_start(arglist, pMsgFmt);
#ifdef WIN32
            vsprintf_s(buffer, pMsgFmt, arglist);
#else
            vsprintf(buffer, pMsgFmt, arglist);
#endif
            va_end(arglist);

            Log(GPA_LOGGING_DEBUG_ERROR, buffer);

            LeaveCriticalSection(&m_hLock);
        }
    }


    /// Logs a formatted error message in debug builds; does nothing in release.
    /// \param pMsgFmt the message to format and pass along
    void LogDebugTrace(const char* pMsgFmt, ...)
    {

        // if the supplied message type is among those that the user wants be notified of,
        // then pass the message along.
        if (GPA_LOGGING_DEBUG_TRACE & m_loggingType)
        {
            EnterCriticalSection(&m_hLock);

            // Format string
            char buffer[1024 * 50];
            va_list arglist;
            va_start(arglist, pMsgFmt);
#ifdef WIN32
            vsprintf_s(buffer, pMsgFmt, arglist);
#else
            vsprintf(buffer, pMsgFmt, arglist);
#endif
            va_end(arglist);

            Log(GPA_LOGGING_DEBUG_TRACE, buffer);

            LeaveCriticalSection(&m_hLock);
        }
    }

    /// Logs a formatted message in internal builds; does nothing in public builds.
    /// \param pMsgFmt the message to format and pass along
    void LogDebugCounterDefs(const char* pMsgFmt, ...)
    {
        // if the supplied message type is among those that the user wants be notified of,
        // then pass the message along.
        if (GPA_LOGGING_DEBUG_COUNTERDEFS & m_loggingType)
        {
            EnterCriticalSection(&m_hLock);

            // Format string
            char buffer[1024 * 50];
            va_list arglist;
            va_start(arglist, pMsgFmt);
#ifdef WIN32
            vsprintf_s(buffer, pMsgFmt, arglist);
#else
            vsprintf(buffer, pMsgFmt, arglist);
#endif
            va_end(arglist);

            Log(GPA_LOGGING_DEBUG_COUNTERDEFS, buffer);

            LeaveCriticalSection(&m_hLock);
        }
    }

protected:

    /// User selected logging type that defines what messages they want to be notified of
    GPA_Logging_Type m_loggingType;

    /// User-supplied callback function
    GPA_LoggingCallbackPtrType m_loggingCallback;

#ifdef _WIN32
    CRITICAL_SECTION m_hLock;  ///< lock for thread-safe access
#endif

#ifdef _LINUX
    pthread_mutex_t m_hLock;   ///< lock for thread-safe access
#endif
};

/// Singleton instance of the GPALogger class
extern GPALogger g_loggerSingleton;

// define C-style functions for simplified logging
/// macro for logging
#define GPA_Log g_loggerSingleton.Log
/// macro for logging of errors
#define GPA_LogError g_loggerSingleton.LogError
/// macro for logging of messages
#define GPA_LogMessage g_loggerSingleton.LogMessage
/// macro for logging of trace items
#define GPA_LogTrace g_loggerSingleton.LogTrace

/// macro for debug logging of messages
#define GPA_LogDebugMessage g_loggerSingleton.LogDebugMessage
/// macro for debug logging of errors
#define GPA_LogDebugError g_loggerSingleton.LogDebugError
/// macro for debug logging of trace items
#define GPA_LogDebugTrace g_loggerSingleton.LogDebugTrace
/// macro for debug logging of counter defs
#define GPA_LogDebugCounterDefs g_loggerSingleton.LogDebugCounterDefs

/// Utility class for tracing the start and end of functions.
class GPATracer
{
public:

    /// Default constructor
    GPATracer();

    /// Destructor
    ~GPATracer() {}

    /// Should be called when a function is entered.
    /// \param pFunctionName the function that is being entered
    void EnterFunction(const char* pFunctionName);

    /// Should be called when a function is exited.
    /// \param pFunctionName the function that is being left
    void LeaveFunction(const char* pFunctionName);

protected:

    /// Indicates whether to only show the top level of functions (true), or also show nested function calls (false).
    bool m_topLevelOnly;

    /// Stores the number of tabs to indent nested function calls.
    unsigned int m_logTab;
};

/// Singleton instance of the GPATracer class
extern GPATracer gTracerSingleton;

/// Allows for easy tracing of exiting a function.
/// Calls GPATracer::EnterFunction in the constructor
/// and GPATracer::LeaveFunction in the destructor.
class ScopeTrace
{
public:
    /// Constructor which calls GPATracer::EnterFunction.
    /// \param pTraceFunction the function which is being traced.
    ScopeTrace(const char* pTraceFunction);

    /// Destructor which calls GPATracer::LeaveFunction.
    ~ScopeTrace();

protected:

    /// Stores the function being traced.
    const char* m_pTraceFunction;
};

#endif //GPA_LOGGING_H_
