//==============================================================================
// Copyright (c) 2016-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Logging utility
//==============================================================================

#ifndef GPA_LOGGING_H_
#define GPA_LOGGING_H_

#ifdef _WIN32
#include <Windows.h>
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
#include <sstream>
#include <mutex>
#include <map>
#include <thread>
#include <fstream>

#include "gpu_perf_api_types.h"
#include "gpu_perf_api_function_types.h"

#define ENABLE_TRACING 1  ///< Macro to determine if tracing is enabled

#if ENABLE_TRACING
#undef TRACE_FUNCTION
/// macro for tracing function calls
#define TRACE_FUNCTION(func) ScopeTrace _tempScopeTraceObject(#func)  ///< Macro used for tracing functions
#ifdef AMDT_INTERNAL
#undef TRACE_PRIVATE_FUNCTION
#undef TRACE_PRIVATE_FUNCTION_WITH_ARGS
/// macro for tracing private function calls
#define TRACE_PRIVATE_FUNCTION(func) ScopeTrace _tempScopeTraceObject(#func)  ///< Macro used for tracing private functions
#define TRACE_PRIVATE_FUNCTION_WITH_ARGS(func, ...)           \
    TRACE_PRIVATE_FUNCTION(func);                             \
    {                                                         \
        std::ostringstream o;                                 \
        o << ##__VA_ARGS__;                                   \
        gTracerSingleton.OutputFunctionData(o.str().c_str()); \
    }  ///< Macro used for tracing private function with parameters
#else  // public build
#undef TRACE_PRIVATE_FUNCTION
#undef TRACE_PRIVATE_FUNCTION_WITH_ARGS
/// macro for tracing private function calls
#define TRACE_PRIVATE_FUNCTION(func)                 ///< Macro used for tracing private functions
#define TRACE_PRIVATE_FUNCTION_WITH_ARGS(func, ...)  ///< Macro used for tracing private function with parameters
#endif                                               // AMDT_INTERNAL / public build
#else                                                // disable trace functions
#undef TRACE_FUNCTION
#define TRACE_FUNCTION(func)  ///< Macro used for tracing functions
#undef TRACE_PRIVATE_FUNCTION
#define TRACE_PRIVATE_FUNCTION(func)                 ///< Macro used for tracing private functions
#define TRACE_PRIVATE_FUNCTION_WITH_ARGS(func, ...)  ///< Macro used for tracing private function with parameters
#endif                                               // trace functions

/// Internal GPA logger function
/// \param[in] logType logging type
/// \param[in] pLogMsg logging message
extern void GPAInternalLogger(GPA_Logging_Type logType, const char* pLogMsg);

#define GPA_INTERNAL_LOG(func, ...)                                                                            \
    std::stringstream logAdditionalMessage;                                                                    \
    logAdditionalMessage << "ThreadId: " << std::this_thread::get_id() << " " << #func << ": " << __VA_ARGS__; \
    GPAInternalLogger(GPA_LOGGING_INTERNAL, logAdditionalMessage.str().c_str());

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
            char    buffer[1024 * 50];
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
            char    buffer[1024 * 50];
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
            char    buffer[1024 * 50];
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
            char    buffer[1024 * 50];
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

    /// Checks whether the tracing is enabled or not
    /// \return true if either tracing or debug tracing is enabled otherwise false
    bool IsTracingEnabled() const
    {
        if (nullptr != m_loggingCallback)
        {
            return m_loggingType & GPA_LOGGING_TRACE || m_loggingType & GPA_LOGGING_DEBUG_TRACE;
        }

        return false;
    }

    /// Internal logging file stream
    std::fstream m_internalLoggingFileStream;

    /// Internal logging file
    std::string m_internalLogFileName;

protected:
    /// User selected logging type that defines what messages they want to be notified of
    GPA_Logging_Type m_loggingType;

    /// User-supplied callback function
    GPA_LoggingCallbackPtrType m_loggingCallback;

    /// Internal logger of GPA for debugging purposes
    GPA_LoggingCallbackPtrType m_gpaInternalLogger = GPAInternalLogger;

    /// Mutex for internal logging flag
    std::mutex m_internalLoggingMutex;

    /// Internal logging flag
    bool m_enableInternalLogging;

#ifdef _WIN32
    CRITICAL_SECTION m_hLock;  ///< lock for thread-safe access
#endif

#ifdef _LINUX
    pthread_mutex_t m_hLock;  ///< lock for thread-safe access
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

    /// Should be called when a function is entered.
    /// \param pFunctionName the function that is being entered
    void EnterFunction(const char* pFunctionName);

    /// Should be called when a function is exited.
    /// \param pFunctionName the function that is being left
    void LeaveFunction(const char* pFunctionName);

    /// Called if a function has additional data to output
    /// Information is tabbed under the function
    /// \param pData the additional data to output
    void OutputFunctionData(const char* pData);

private:
    /// Returns the pointer to the tab counter
    /// \param[out] pCurrentThreadId thread id of the caller
    /// \return pointer to the tab counter
    std::map<std::thread::id, int32_t>::iterator GetTabCounter(std::thread::id* pCurrentThreadId);

    /// Indicates whether to only show the top level of functions (true), or also show nested function calls (false).
    bool m_topLevelOnly;

    /// Mutex for the thread and tab counter map
    std::mutex m_tracerMutex;

    /// Map of the thread and its associated tab counter
    std::map<std::thread::id, int32_t> m_threadTabCountMap;
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
    std::string m_traceFunction;
};

#endif  //GPA_LOGGING_H_
