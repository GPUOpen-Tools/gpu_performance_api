//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Logging utility.
//==============================================================================

#include "gpu_perf_api_common/logging.h"

#include <assert.h>

#include "gpu_perf_api_common/utility.h"

#ifdef _WIN32
#pragma comment(lib, "Winmm.lib")
#endif

void GpaInternalLogger(GpaLoggingType log_type, const char* log_msg)
{
    if (kGpaLoggingInternal == log_type)
    {
        if (GpaLogger::Instance()->internal_logging_file_stream_.is_open())
        {
            GpaLogger::Instance()->internal_logging_file_stream_ << "GPA Internal Logging: " << log_msg << std::endl;
        }
    }
}

GpaTracer::GpaTracer()
{
#ifdef AMDT_INTERNAL
    // In internal builds, we want all the tracing to be displayed.
    top_level_only_ = false;
#else
    // In public builds, the end-user should only see the functions they call.
    top_level_only_ = true;
#endif  // AMDT_INTERNAL
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

#ifdef AMDT_INTERNAL
        GPA_LOG_DEBUG_TRACE(message.str().c_str());

        if (tab_counter->second == 0)
        {
            // If this is the top level, also pass it to the normal LogTrace.
            GPA_LOG_TRACE(message.str().c_str());
        }

#else
        GPA_LOG_TRACE(message.str().c_str());
#endif  // AMDT_INTERNAL
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

#ifdef AMDT_INTERNAL
        GPA_LOG_DEBUG_TRACE(message.str().c_str());

        if (tab_counter->second == 0)
        {
            // If this is the top level, also pass it to the normal LogTrace.
            GPA_LOG_TRACE(message.str().c_str());
        }

#else
        GPA_LOG_TRACE(message.str().c_str());
#endif  // AMDT_INTERNAL
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

#ifdef AMDT_INTERNAL
        GPA_LOG_DEBUG_TRACE(message.str().c_str());

        if (tab_counter->second == 0)
        {
            // If this is the top level, also pass it to the normal LogTrace.
            GPA_LOG_TRACE(message.str().c_str());
        }

#else
        GPA_LOG_TRACE(message.str().c_str());
#endif  // AMDT_INTERNAL
    }
}

std::map<std::thread::id, int32_t>::iterator GpaTracer::GetTabCounter(std::thread::id* current_thread_id)
{
    std::lock_guard<std::mutex> lock(tracer_mutex_);

    *current_thread_id = std::this_thread::get_id();

    std::map<std::thread::id, int32_t>::iterator ret = thread_tab_count_map_.find(*current_thread_id);

    if (ret == thread_tab_count_map_.end())
    {
        thread_tab_count_map_[*current_thread_id] = 0;
        ret                                       = thread_tab_count_map_.find(*current_thread_id);
    }

#ifdef _DEBUG
    // Validate tab value.
    const int32_t kMaxTabCount = 1024;
    assert(ret->second >= 0 && ret->second < kMaxTabCount);
#endif

    return ret;
}

ScopeTrace::ScopeTrace(const char* trace_function)
{
    if (GpaLogger::Instance()->IsTracingEnabled())
    {
        GpaTracer::Instance()->EnterFunction(trace_function);
        trace_function_ = trace_function;
    }
}

ScopeTrace::~ScopeTrace()
{
    if (GpaLogger::Instance()->IsTracingEnabled())
    {
        GpaTracer::Instance()->LeaveFunction(trace_function_.c_str());
    }
}

GpaLogger::GpaLogger()
    : logging_type_(kGpaLoggingNone)
    , logging_callback_(nullptr)
    , enable_internal_logging_(false)
{
#ifdef _WIN32
    InitializeCriticalSection(&lock_handle);
#endif

#ifdef _LINUX
    pthread_mutexattr_t mutex_attr;
    pthread_mutexattr_init(&mutex_attr);
    // Set the mutex as a recursive mutex.
#ifdef __APPLE__
    pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_RECURSIVE);
#else
    pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_RECURSIVE_NP);
#endif
    // Create the mutex with the attributes set.
    pthread_mutex_init(&lock_handle, &mutex_attr);

    // After initializing the mutex, the thread attribute can be destroyed.
    pthread_mutexattr_destroy(&mutex_attr);
#endif

#ifdef _DEBUG
    std::string current_module_path;
    gpa_util::GetCurrentModulePath(current_module_path);
    internal_log_file_name_ = current_module_path + "GPA-Internal-Log.txt";
    std::remove(internal_log_file_name_.c_str());
    internal_logging_file_stream_.open(internal_log_file_name_.c_str(), std::ios_base::out | std::ios_base::app);
#endif
}

void GpaLogger::SetLoggingCallback(GpaLoggingType logging_type, GpaLoggingCallbackPtrType logging_callback)
{
    if (nullptr == logging_callback)
    {
        logging_callback_ = nullptr;
        logging_type_     = kGpaLoggingNone;
    }
    else
    {
        logging_callback_ = logging_callback;
        logging_type_     = logging_type;
    }
}

void GpaLogger::Log(GpaLoggingType log_type, const char* log_message)
{
    EnterCriticalSection(&lock_handle);

    // If the supplied message type is among those that the user wants be notified of,
    // then pass the message along.
    if ((log_type & logging_type_) && nullptr != logging_callback_)
    {
        logging_callback_(log_type, log_message);

        if (enable_internal_logging_)
        {
            gpa_internal_logger_(log_type, log_message);
        }
    }

    LeaveCriticalSection(&lock_handle);
}

GpaLogger::~GpaLogger()
{
#ifdef _WIN32
    DeleteCriticalSection(&lock_handle);
#else
    pthread_mutex_destroy(&lock_handle);
#endif
}
