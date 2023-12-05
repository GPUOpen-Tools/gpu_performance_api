//==============================================================================
// Copyright (c) 2016-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Logging utility.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_LOGGING_H_
#define GPU_PERF_API_COMMON_LOGGING_H_

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

#include "TSingleton.h"

#include "gpu_performance_api/gpu_perf_api_function_types.h"
#include "gpu_performance_api/gpu_perf_api_types.h"

#define ENABLE_TRACING 1  ///< Macro to determine if tracing is enabled.

#if ENABLE_TRACING
#undef TRACE_FUNCTION
/// Macro for tracing function calls.
#define TRACE_FUNCTION(func) ScopeTrace temp_scope_trace_object(#func)  ///< Macro used for tracing functions.
#undef TRACE_PRIVATE_FUNCTION
#undef TRACE_PRIVATE_FUNCTION_WITH_ARGS
/// Macro for tracing private function calls.
#define TRACE_PRIVATE_FUNCTION(func)                 ///< Macro used for tracing private functions.
#define TRACE_PRIVATE_FUNCTION_WITH_ARGS(func, ...)  ///< Macro used for tracing private function with parameters.
#else                                                // disable trace functions.
#undef TRACE_FUNCTION
#define TRACE_FUNCTION(func)  ///< Macro used for tracing functions.
#undef TRACE_PRIVATE_FUNCTION
#define TRACE_PRIVATE_FUNCTION(func)                 ///< Macro used for tracing private functions.
#define TRACE_PRIVATE_FUNCTION_WITH_ARGS(func, ...)  ///< Macro used for tracing private function with parameters.
#endif                                               // trace functions.

#ifdef __GNUC__
#define GPA_ATTRIBUTE_PRINTF(msg, args) __attribute__((format(printf, msg, args)))
#else
#define GPA_ATTRIBUTE_PRINTF(msg, args)
#endif  // !__GNUC__

/// @brief Internal GPA logger function.
///
/// @param [in] log_type Logging type.
/// @param [in] log_msg Logging message.
extern void GpaInternalLogger(GpaLoggingType log_type, const char* log_msg);

#define GPA_INTERNAL_LOG(func, ...)                                                                              \
    std::stringstream log_additional_message;                                                                    \
    log_additional_message << "ThreadId: " << std::this_thread::get_id() << " " << #func << ": " << __VA_ARGS__; \
    GpaInternalLogger(kGpaLoggingInternal, log_additional_message.str().c_str());

/// @brief Passes log messages of various types to a user-supplied callback function
/// if the user has elected to receive messages of that particular type.
class GpaLogger : public TSingleton<GpaLogger>
{
public:
    /// @brief Sets the type of message the user would like to be informed of and a pointer to the callback function.
    ///
    /// @param [in] logging_type The type of messages to pass on to the callback function.
    /// @param [in] logging_callback A pointer to the callback function.
    void SetLoggingCallback(GpaLoggingType logging_type, GpaLoggingCallbackPtrType logging_callback);

    /// @brief Passes the supplied message to the callback function if the user has accepted that type of message.
    ///
    /// @param [in] log_type The type of message being supplied.
    /// @param [in] log_message The message to pass along.
    void Log(GpaLoggingType log_type, const char* log_message);

    /// @brief Passes the supplied formatted message to the callback function if the user has accepted that type of message.
    ///
    /// @param [in] type The type of message being supplied.
    /// @param [in] msg_fmt The message to format.
    /// @param [in] args Variable arguments supplied for the message.
    void Logfv(GpaLoggingType type, const char* msg_fmt, va_list args)
    {
        // If the supplied message type is among those that the user wants be notified of,
        // then pass the message along.
        if (type & logging_type_)
        {
            EnterCriticalSection(&lock_handle);

            // Format string.
            char    buffer[1024 * 5];
            buffer[0] = '\0';
#ifdef WIN32
            vsnprintf_s(buffer, sizeof(buffer), msg_fmt, args);
#else
            vsnprintf(buffer, sizeof(buffer), msg_fmt, args);
#endif
            Log(type, buffer);

            LeaveCriticalSection(&lock_handle);
        }
    }

    /// @brief Passes the supplied formatted message to the callback function if the user has accepted that type of message.
    ///
    /// @param [in] type The type of message being supplied.
    /// @param [in] msg_fmt The message to format.
    void Logf(GpaLoggingType type, const char* msg_fmt, ...) GPA_ATTRIBUTE_PRINTF(3, 4)
    {
        va_list args;
        va_start(args, msg_fmt);
        Logfv(type, msg_fmt, args);
        va_end(args);
    }

    /// @brief Logs an error message.
    ///
    /// @param [in] msg_fmt The message to format and pass along.
    inline void LogError(const char* msg_fmt, ...) GPA_ATTRIBUTE_PRINTF(2, 3)
    {
        va_list args;
        va_start(args, msg_fmt);
        Logfv(kGpaLoggingError, msg_fmt, args);
        va_end(args);
    }

    /// @brief Logs an informational message.
    ///
    /// @param [in] msg_fmt The message to format and pass along.
    inline void LogMessage(const char* msg_fmt, ...) GPA_ATTRIBUTE_PRINTF(2, 3)
    {
        va_list args;
        va_start(args, msg_fmt);
        Logfv(kGpaLoggingMessage, msg_fmt, args);
        va_end(args);
    }

    /// @brief Logs a trace message.
    ///
    /// @param [in] msg_fmt The message to format and pass along.
    inline void LogTrace(const char* msg_fmt, ...) GPA_ATTRIBUTE_PRINTF(2, 3)
    {
        va_list args;
        va_start(args, msg_fmt);
        Logfv(kGpaLoggingTrace, msg_fmt, args);
        va_end(args);
    }

    /// @brief Logs a formatted message in internal builds; does nothing in release.
    ///
    /// @param [in] msg_fmt The message to format and pass along.
    void LogDebugMessage(const char* msg_fmt, ...) GPA_ATTRIBUTE_PRINTF(2, 3)
    {
        va_list args;
        va_start(args, msg_fmt);
        Logfv(kGpaLoggingDebugMessage, msg_fmt, args);
        va_end(args);
    }

    /// @brief Logs a formatted error message in debug builds; does nothing in release.
    ///
    /// @param [in] msg_fmt The message to format and pass along.
    void LogDebugError(const char* msg_fmt, ...) GPA_ATTRIBUTE_PRINTF(2, 3)
    {
        va_list args;
        va_start(args, msg_fmt);
        Logfv(kGpaLoggingDebugError, msg_fmt, args);
        va_end(args);
    }

    /// @brief Logs a formatted error message in debug builds; does nothing in release.
    ///
    /// @param [in] msg_fmt The message to format and pass along.
    void LogDebugTrace(const char* msg_fmt, ...) GPA_ATTRIBUTE_PRINTF(2, 3)
    {
        va_list args;
        va_start(args, msg_fmt);
        Logfv(kGpaLoggingDebugTrace, msg_fmt, args);
        va_end(args);
    }

    /// @brief Logs a formatted message in internal builds; does nothing in public builds.
    ///
    /// @param [in] msg_fmt The message to format and pass along.
    void LogDebugCounterDefs(const char* msg_fmt, ...) GPA_ATTRIBUTE_PRINTF(2, 3)
    {
        va_list args;
        va_start(args, msg_fmt);
        Logfv(kGpaLoggingDebugCounterDefinitions, msg_fmt, args);
        va_end(args);
    }

    /// @brief Checks whether the tracing is enabled or not.
    ///
    /// @return True if either tracing or debug tracing is enabled otherwise false.
    bool IsTracingEnabled() const
    {
        if (nullptr != logging_callback_)
        {
            return logging_type_ & kGpaLoggingTrace || logging_type_ & kGpaLoggingDebugTrace;
        }

        return false;
    }

    /// Internal logging file stream.
    std::fstream internal_logging_file_stream_;

    /// Internal logging file.
    std::string internal_log_file_name_;

protected:
    /// User selected logging type that defines what messages they want to be notified of.
    GpaLoggingType logging_type_;

    /// User-supplied callback function.
    GpaLoggingCallbackPtrType logging_callback_;

    /// Internal logger of GPA for debugging purposes.
    GpaLoggingCallbackPtrType gpa_internal_logger_ = GpaInternalLogger;

    /// Mutex for internal logging flag.
    std::mutex internal_logging_mutex_;

    /// Internal logging flag.
    bool enable_internal_logging_;

#ifdef _WIN32
    CRITICAL_SECTION lock_handle;  ///< Lock for thread-safe access.
#endif

#ifdef _LINUX
    pthread_mutex_t lock_handle;  ///< Lock for thread-safe access.
#endif
private:
    friend TSingleton<GpaLogger>;

    /// @brief Default constructor.
    GpaLogger();

    /// @brief Virtual destructor.
    virtual ~GpaLogger();

    /// @brief Don't allow the singleton to be copies.
    GpaLogger(const GpaLogger&) = delete;

    /// @brief Don't allow the singleton to be assigned.
    void operator=(const GpaLogger&) = delete;
};

// define C-style functions for simplified logging.
/// Macro for logging.
#define GPA_LOG GpaLogger::Instance()->Log
/// Macro for logging of errors.
#define GPA_LOG_ERROR GpaLogger::Instance()->LogError
/// Macro for logging of messages.
#define GPA_LOG_MESSAGE GpaLogger::Instance()->LogMessage
/// Macro for logging of trace items.
#define GPA_LOG_TRACE GpaLogger::Instance()->LogTrace

/// Macro for debug logging of messages.
#define GPA_LOG_DEBUG_MESSAGE GpaLogger::Instance()->LogDebugMessage
/// Macro for debug logging of errors.
#define GPA_LOG_DEBUG_ERROR GpaLogger::Instance()->LogDebugError
/// Macro for debug logging of trace items.
#define GPA_LOG_DEBUG_TRACE GpaLogger::Instance()->LogDebugTrace
/// Macro for debug logging of counter definitions.
#define GPA_LOG_DEBUG_COUNTER_DEFS GpaLogger::Instance()->LogDebugCounterDefs

/// @brief Utility class for tracing the start and end of functions.
class GpaTracer : public TSingleton<GpaTracer>
{
public:
    /// @brief Should be called when a function is entered.
    ///
    /// @param [in] function_name The function that is being entered.
    void EnterFunction(const char* function_name);

    /// @brief Should be called when a function is exited.
    ///
    /// @param [in] function_name The function that is being left.
    void LeaveFunction(const char* function_name);

    /// @brief Called if a function has additional data to output.
    ///
    /// Information is tabbed under the function.
    ///
    /// @param [in] data The additional data to output.
    void OutputFunctionData(const char* data);

private:
    friend TSingleton<GpaTracer>;

    /// @brief Default constructor.
    GpaTracer();

    /// @brief Don't allow singleton copies.
    GpaTracer(const GpaTracer&) = delete;

    /// @brief Don't allow singleton assignment elsewhere.
    void operator=(const GpaTracer&) = delete;

    /// @brief Returns the pointer to the tab counter.
    ///
    /// @param [out] current_thread_id Thread id of the caller.
    ///
    /// @return Pointer to the tab counter.
    std::map<std::thread::id, int32_t>::iterator GetTabCounter(std::thread::id* current_thread_id);

    /// Indicates whether to only show the top level of functions (true), or also show nested function calls (false).
    bool top_level_only_;

    /// Mutex for the thread and tab counter map.
    std::mutex tracer_mutex_;

    /// Map of the thread and its associated tab counter.
    std::map<std::thread::id, int32_t> thread_tab_count_map_;
};

/// @brief Allows for easy tracing of exiting a function.
///
/// Calls GPATracer::EnterFunction in the constructor and GpaTracer::LeaveFunction in the destructor.
class ScopeTrace
{
public:
    /// @brief Constructor which calls GPATracer::EnterFunction.
    ///
    /// @param [in] trace_function The function which is being traced.
    ScopeTrace(const char* trace_function);

    /// @brief Destructor which calls GPATracer::LeaveFunction.
    ~ScopeTrace();

protected:
    /// Stores the function being traced.
    std::string trace_function_;
};

#endif  // GPU_PERF_API_COMMON_LOGGING_H_
