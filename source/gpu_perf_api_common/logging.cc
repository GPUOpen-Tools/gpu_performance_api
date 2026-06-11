//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Logging utility.
//==============================================================================

#include "gpu_perf_api_common/logging.h"

#include <cassert>
#include <charconv>
#include <type_traits>

void GpaInternalLogger(GpaLoggingType log_type, const char* log_msg)
{
#ifdef _DEBUG
    if (kGpaLoggingInternal == log_type)
    {
        static std::mutex      internal_logging_mutex;
        const std::scoped_lock lock(internal_logging_mutex);
        if (GpaLogger::Instance().internal_logging_file_stream_.is_open())
        {
            GpaLogger::Instance().internal_logging_file_stream_ << "GPA Internal Logging: " << log_msg << '\n' << std::flush;
        }
    }
#else
    (void)log_type;
    (void)log_msg;
#endif
}

void GpaTracer::EnterFunction(const char* function_name)
{
    std::thread::id current_thread_id;
    auto            tab_counter = GetTabCounter(&current_thread_id);

    if ((!tab_counter->second && top_level_only_) || !top_level_only_)
    {
        std::stringstream message;

        for (int32_t temp_log_tab = 0; temp_log_tab < tab_counter->second; temp_log_tab++)
        {
            message << "   ";
        }

        message << "Thread " << current_thread_id << " ";
        message << "Enter: ";
        message << function_name;
        message << ".";

        GpaLogger::Instance().LogTrace("{}", message.str());
    }

    ++tab_counter->second;
}

void GpaTracer::LeaveFunction(const char* function_name)
{
    std::thread::id current_thread_id;
    auto            tab_counter = GetTabCounter(&current_thread_id);

    if (tab_counter->second > 0)
    {
        --tab_counter->second;
    }

    if ((!tab_counter->second && top_level_only_) || !top_level_only_)
    {
        std::stringstream message;

        for (int32_t temp_log_tab = 0; temp_log_tab < tab_counter->second; temp_log_tab++)
        {
            message << "   ";
        }

        message << "Thread " << current_thread_id << " ";
        message << "Leave: ";
        message << function_name;
        message << ".";

        GpaLogger::Instance().LogTrace("{}", message.str());
    }
}

void GpaTracer::OutputFunctionData(const char* data)
{
    std::thread::id current_thread_id;
    auto            tab_counter = GetTabCounter(&current_thread_id);

    if (((tab_counter->second) == 1 && top_level_only_) || !top_level_only_)
    {
        std::stringstream message;

        for (int32_t temp_log_tab = 0; temp_log_tab < tab_counter->second; temp_log_tab++)
        {
            message << "   ";
        }

        message << "Thread " << current_thread_id << " ";
        message << data;
        message << ".";

        GpaLogger::Instance().LogTrace("{}", message.str());
    }
}

std::map<std::thread::id, int32_t>::iterator GpaTracer::GetTabCounter(std::thread::id* current_thread_id)
{
    const std::scoped_lock<std::mutex> lock(tracer_mutex_);

    *current_thread_id = std::this_thread::get_id();

    std::map<std::thread::id, int32_t>::iterator ret = thread_tab_count_map_.find(*current_thread_id);

    if (ret == thread_tab_count_map_.end())
    {
        thread_tab_count_map_[*current_thread_id] = 0;
        ret                                       = thread_tab_count_map_.find(*current_thread_id);
    }

#ifdef _DEBUG
    // Validate tab value.
    constexpr int32_t kMaxTabCount = 1024;
    assert(ret->second >= 0 && ret->second < kMaxTabCount);
#endif

    return ret;
}

ScopeTrace::ScopeTrace(const std::source_location location)
    : function_name_(location.function_name())
{
    if (GpaLogger::Instance().IsTracingEnabled()) [[unlikely]]
    {
        GpaTracer::Instance()->EnterFunction(function_name_);
    }
}

ScopeTrace::~ScopeTrace()
{
    if (GpaLogger::Instance().IsTracingEnabled()) [[unlikely]]
    {
        GpaTracer::Instance()->LeaveFunction(function_name_);
    }
}

void GpaLogger::SetLoggingCallback(GpaLoggingType logging_type, GpaLoggingCallbackPtrType logging_callback)
{
    const std::scoped_lock<std::recursive_mutex> lock(lock_handle_);

    if (logging_callback == nullptr)
    {
        logging_callback_ = nullptr;
        logging_type_     = kGpaLoggingNone;
        return;
    }

    logging_callback_ = logging_callback;
    logging_type_     = logging_type;

    // See documentation/sphinx/source/gpa_env_variables.rst for details on this environment variable.
    const std::optional<std::string> level = gpa_util::GetEnv("GPA_OVERRIDE_LOG_LEVEL");
    if (!level.has_value())
    {
        return;
    }

    const std::string&                     str              = level.value();
    std::underlying_type_t<GpaLoggingType> parsed_log_level = 0;
    auto [ptr, ec]                                          = std::from_chars(str.data(), str.data() + str.size(), parsed_log_level);

    // Avoid junk: Values like "1junk" would currently be accepted as 1
    const bool invalid_str = ptr != str.data() + str.size();

    if (invalid_str || ec != std::errc{} || parsed_log_level > static_cast<std::underlying_type_t<GpaLoggingType>>(kGpaLoggingDebugAll))
    {
        GpaLogger::Instance().LogDebugError("Failed to parse log level from environment variable GPA_OVERRIDE_LOG_LEVEL: '{}'", str);
        return;
    }

    logging_type_ = static_cast<GpaLoggingType>(parsed_log_level);
}
