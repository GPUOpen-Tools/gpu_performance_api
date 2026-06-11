//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Logging utility.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_LOGGING_H_
#define GPU_PERF_API_COMMON_LOGGING_H_

#include <array>
#include <cassert>
#include <source_location>
#include <string>
#include <sstream>
#include <mutex>
#include <map>
#include <thread>
#include <fstream>
#include <format>
#include <string_view>
#include <optional>

#include "gpu_performance_api/gpu_perf_api_function_types.h"
#include "gpu_performance_api/gpu_perf_api_types.h"
#include "gpu_perf_api_common/utility.h"

/// @brief Macro for tracing function calls using a scope-bound object.
///
/// When GPA_ENABLE_TRACING is enabled, this macro creates a ScopeTrace object
/// that automatically logs function entry in its constructor and function exit
/// in its destructor. The function name is captured via std::source_location.
#ifdef GPA_TRACE_FUNCTION
#undef GPA_TRACE_FUNCTION
#endif

#define GPA_ENABLE_TRACING 1  ///< Macro to determine if tracing is enabled.

#if GPA_ENABLE_TRACING
#define GPA_TRACE_FUNCTION() ScopeTrace temp_scope_trace_object{}
#else
#define GPA_TRACE_FUNCTION()
#endif

/// @brief Internal GPA logger function.
///
/// Logs messages to an internal log file for debugging purposes.
/// This is used as the default internal logger and is called in addition
/// to the user-supplied callback when internal logging is enabled.
///
/// @param [in] log_type Logging type.
/// @param [in] log_msg Logging message.
extern void GpaInternalLogger(GpaLoggingType log_type, const char* log_msg);

#define GPA_INTERNAL_LOG(...)                                                                                                                                  \
    do                                                                                                                                                         \
    {                                                                                                                                                          \
        std::stringstream log_additional_message;                                                                                                              \
        log_additional_message << "ThreadId: " << std::this_thread::get_id() << " " << std::source_location::current().function_name() << ": " << __VA_ARGS__; \
        GpaInternalLogger(kGpaLoggingInternal, log_additional_message.str().c_str());                                                                          \
    } while (0)

/// @brief Thread-safe singleton logger that passes log messages of various types
/// to a user-supplied callback function.
///
/// Messages are only forwarded if the user has elected to receive messages of
/// that particular type via SetLoggingCallback. All logging methods use
/// std::format for compile-time format string validation and type-safe formatting.
class GpaLogger
{
public:
    /// @brief Deleted copy constructor to enforce singleton pattern.
    GpaLogger(const GpaLogger&) = delete;

    /// @brief Deleted move constructor to enforce singleton pattern.
    GpaLogger(GpaLogger&&) = delete;

    /// @brief Deleted copy assignment operator to enforce singleton pattern.
    void operator=(const GpaLogger&) = delete;

    /// @brief Deleted move assignment operator to enforce singleton pattern.
    void operator=(GpaLogger&&) = delete;

    /// @brief Returns the singleton instance of the GpaLogger.
    ///
    /// Uses a function-local static variable for thread-safe lazy initialization.
    /// The instance is never explicitly destroyed; it lives until program termination.
    ///
    /// @return Reference to the singleton GpaLogger instance.
    [[nodiscard]] static GpaLogger& Instance()
    {
        static GpaLogger logger;
        return logger;
    }

    /// @brief Sets the type of message the user would like to be informed of and a pointer to the callback function.
    ///        SetLoggingCallback must not be called concurrently with logging!
    ///        Otherwise ShouldLog will not be thread safe. This is a tradeoff to allow for more
    ///        efficient logging when the callback is set, since we won't need to acquire a lock
    ///        in ShouldLog to check if the callback is set or not.
    ///
    /// @param [in] logging_type The type of messages to pass on to the callback function.
    /// @param [in] logging_callback A pointer to the callback function.
    void SetLoggingCallback(GpaLoggingType logging_type, GpaLoggingCallbackPtrType logging_callback);

    /// @brief Logs a formatted error message with compile-time format string validation.
    ///
    /// @param [in] fmt The format string.
    /// @param [in] args The format arguments.
    template <class... Args>
    void LogError(std::format_string<Args...> fmt, Args&&... args)
    {
        constexpr GpaLoggingType kLogType = kGpaLoggingError;
        if (ShouldLog(kLogType)) [[unlikely]]
        {
            Log(kLogType, fmt, std::forward<Args>(args)...);
        }
    }

    /// @brief Logs a formatted message with compile-time format string validation.
    ///
    /// @param [in] fmt The format string.
    /// @param [in] args The format arguments.
    template <class... Args>
    void LogMessage(std::format_string<Args...> fmt, Args&&... args)
    {
        constexpr GpaLoggingType kLogType = kGpaLoggingMessage;
        if (ShouldLog(kLogType)) [[unlikely]]
        {
            Log(kLogType, fmt, std::forward<Args>(args)...);
        }
    }

    /// @brief Logs a formatted trace message with compile-time format string validation.
    ///
    /// @param [in] fmt The format string.
    /// @param [in] args The format arguments.
    template <class... Args>
    void LogTrace(std::format_string<Args...> fmt, Args&&... args)
    {
        constexpr GpaLoggingType kLogType = kGpaLoggingTrace;
        if (ShouldLog(kLogType)) [[unlikely]]
        {
            Log(kLogType, fmt, std::forward<Args>(args)...);
        }
    }

    /// @brief Logs a formatted debug message with compile-time format string validation.
    ///
    /// @param [in] fmt The format string.
    /// @param [in] args The format arguments.
    template <class... Args>
    void LogDebugMessage(std::format_string<Args...> fmt, Args&&... args)
    {
        constexpr GpaLoggingType kLogType = kGpaLoggingDebugMessage;
        if (ShouldLog(kLogType)) [[unlikely]]
        {
            Log(kLogType, fmt, std::forward<Args>(args)...);
        }
    }

    /// @brief Logs a formatted debug error message with compile-time format string validation.
    ///
    /// @param [in] fmt The format string.
    /// @param [in] args The format arguments.
    template <class... Args>
    void LogDebugError(std::format_string<Args...> fmt, Args&&... args)
    {
        constexpr GpaLoggingType kLogType = kGpaLoggingDebugError;
        if (ShouldLog(kLogType)) [[unlikely]]
        {
            Log(kLogType, fmt, std::forward<Args>(args)...);
        }
    }

    /// @brief Logs a formatted debug trace message with compile-time format string validation.
    ///
    /// @param [in] fmt The format string.
    /// @param [in] args The format arguments.
    template <class... Args>
    void LogDebugTrace(std::format_string<Args...> fmt, Args&&... args)
    {
        constexpr GpaLoggingType kLogType = kGpaLoggingDebugTrace;
        if (ShouldLog(kLogType)) [[unlikely]]
        {
            Log(kLogType, fmt, std::forward<Args>(args)...);
        }
    }

    /// @brief Logs a formatted debug counter definition message with compile-time format string validation.
    ///
    /// @param [in] fmt The format string.
    /// @param [in] args The format arguments.
    template <class... Args>
    void LogDebugCounterDefs(std::format_string<Args...> fmt, Args&&... args)
    {
        constexpr GpaLoggingType kLogType = kGpaLoggingDebugCounterDefinitions;
        if (ShouldLog(kLogType)) [[unlikely]]
        {
            Log(kLogType, fmt, std::forward<Args>(args)...);
        }
    }

    /// @brief Checks whether the tracing is enabled or not.
    ///
    /// @return True if either tracing or debug tracing is enabled otherwise false.
    [[nodiscard]] bool IsTracingEnabled() const
    {
        return ShouldLog(kGpaLoggingTrace) || ShouldLog(kGpaLoggingDebugTrace);
    }

#ifdef _DEBUG
    /// Internal logging file stream.
    std::fstream internal_logging_file_stream_;

    /// Internal logging file.
    std::string internal_log_file_name_;
#endif

protected:
    /// User selected logging type that defines what messages they want to be notified of.
    GpaLoggingType logging_type_ = kGpaLoggingNone;

    /// User-supplied callback function.
    GpaLoggingCallbackPtrType logging_callback_ = nullptr;

    /// Internal logger of GPA for debugging purposes.
    GpaLoggingCallbackPtrType gpa_internal_logger_ = GpaInternalLogger;

    /// Lock for thread-safe access.
    std::recursive_mutex lock_handle_;

private:
    /// @brief Must be called before Log to check if the log type is enabled and a callback is set.
    /// @param log_type Logging type to check.
    /// @return Whether the message should be logged or not.
    [[nodiscard]] bool ShouldLog(GpaLoggingType log_type) const noexcept
    {
        // Assume that most of the time, the log type won't be enabled, so check that first to avoid acquiring a lock unnecessarily.
        if ((log_type & logging_type_) == 0) [[likely]]
        {
            return false;
        }
        return (logging_callback_ != nullptr);
    }

    /// @brief Logs a formatted message with compile-time format string validation.
    ///
    /// @param [in] log_type The type of message being supplied.
    /// @param [in] fmt The format string.
    /// @param [in] args The format arguments.
    template <class... Args>
    void Log(GpaLoggingType log_type, std::format_string<Args...> fmt, Args&&... args)
    {
        // Users must call ShouldLog before calling Log to ensure the log type is enabled and a callback is set.
        // This assert serves as a safeguard to prevent misuse of the Log function.
        assert(ShouldLog(log_type));

        const std::scoped_lock<std::recursive_mutex> lock(lock_handle_);

        // Use a small stack buffer to avoid heap allocation for short messages.
        constexpr std::size_t              kStackBufferSize = 512;
        std::array<char, kStackBufferSize> stack_buffer     = {};

        auto result = std::format_to_n(stack_buffer.data(), stack_buffer.size() - 1, fmt, std::forward<Args>(args)...);

        // Set to true to enable internal logging in addition to user callback.
        constexpr bool kEnableInternalLogging = false;

        // 99.9% of the time, the message will fit in the stack buffer.
        if (result.size < static_cast<std::ptrdiff_t>(stack_buffer.size())) [[likely]]
        {
            *result.out = '\0';
            logging_callback_(log_type, stack_buffer.data());

            if constexpr (kEnableInternalLogging)
            {
                gpa_internal_logger_(log_type, stack_buffer.data());
            }
        }
        else [[unlikely]]
        {
            // Fallback for large messages — format once directly into a string.
            const std::string formatted_message = std::format(fmt, std::forward<Args>(args)...);
            logging_callback_(log_type, formatted_message.c_str());

            if constexpr (kEnableInternalLogging)
            {
                gpa_internal_logger_(log_type, formatted_message.c_str());
            }
        }
    }

#ifdef _DEBUG
    GpaLogger()
    {
        // NOTE: If multiple processes are running GPA at the same time,
        // they will overwrite each other's internal log file.
        // This is not a concern since internal logging is only enabled in debug builds,
        // which are not expected to be used by end-users or run concurrently.
        if (std::string current_module_path; gpa_util::GetCurrentModulePath(current_module_path))
        {
            internal_log_file_name_ = current_module_path + "GPA-Internal-Log.txt";
            // Open the file stream for internal logging.
            // Use truncation to ensure a new log file is created each time.
            constexpr auto kMode = std::ios_base::out | std::ios_base::trunc;
            internal_logging_file_stream_.open(internal_log_file_name_.c_str(), kMode);
        }
    }
#else
    /// @brief Default constructor.
    GpaLogger() = default;
#endif

    /// @brief Destructor.
    ~GpaLogger() = default;
};

/// @brief Utility class for tracing the start and end of functions.
class GpaTracer
{
public:
    /// @brief Gets the instance of the GpaTracer.
    ///
    /// @return The instance of the GpaTracer.
    [[nodiscard]] static GpaTracer* Instance()
    {
        static GpaTracer tracer;  ///< GPA Tracer instance.
        return &tracer;
    }

    /// @brief Don't allow singleton copies.
    GpaTracer(const GpaTracer&) = delete;
    GpaTracer(GpaTracer&&)      = delete;

    /// @brief Don't allow singleton assignment elsewhere.
    void operator=(const GpaTracer&) = delete;
    void operator=(GpaTracer&&)      = delete;

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
    /// @brief Default constructor.
    GpaTracer() = default;

    /// @brief Returns the pointer to the tab counter.
    ///
    /// @param [out] current_thread_id Thread id of the caller.
    ///
    /// @return Pointer to the tab counter.
    [[nodiscard]] std::map<std::thread::id, int32_t>::iterator GetTabCounter(std::thread::id* current_thread_id);

    /// Indicates whether to only show the top level of functions (true), or also show nested function calls (false).
    bool top_level_only_ = true;

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
    /// @param [in] location The source location of the function being traced.
    ScopeTrace(const std::source_location location = std::source_location::current());

    ScopeTrace(const ScopeTrace&)            = delete;
    ScopeTrace(ScopeTrace&&)                 = delete;
    ScopeTrace& operator=(const ScopeTrace&) = delete;
    ScopeTrace& operator=(ScopeTrace&&)      = delete;

    /// @brief Destructor which calls GPATracer::LeaveFunction.
    ~ScopeTrace();

protected:
    /// Stores the function being traced.
    const char* function_name_ = nullptr;
};

#endif
