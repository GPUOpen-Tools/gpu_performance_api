//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Internal class to support profiling GPA calls themselves.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_PROFILER_H_
#define GPU_PERF_API_COMMON_GPA_PROFILER_H_

// To use, add this header and the GPAProfiler.cpp file to your project. Use the PROFILER_FUNCTION() macro
// giving the name of the function as a parameter at the very beginning of each function to include in profiling.
// Use START_PROFILING() to begin measurements, and STOP_PROFILING() to finish.
// Use WRITE_PROFILE_REPORT(filename) to write a text report to the specified filename. a csv extension is a good choice.
// Define ENABLE_PROFILING for all projects which reference the profiler.

// note: currently this is written to work for single-threaded apps without access to QueryPerformanceCounter.
// For multi-threaded apps with access to QPC, a QPC version of the timing code should be added.

// The results will look similar to the following:

// Time profiling = 0.762326(2053145454)
// Total time in functions = 0.501066(1349502989)
// % time in functions = 65.7286
// Timing errors = 0

// Function  # of calls  in % of total time  total % of total time   total time  time per call   total time in   time in per call
// GpaBeginPass    9   0.628688    0.628688     0.00315014(8484159)     0.000350016(942684)     0.00315014(8484159)     0.000350016(942684)
// GpaBeginSample  1647    0.440372    0.440372     0.00220656(5942836)     1.33964e-006(3608)  0.00220656(5942836)     1.33964e-006(3608)
// GPA_BeginSession 1   5.65964 5.68611  0.0284912(76734166)     0.0284912(76734166)     0.0283585(76376984)     0.0283585(76376984)

// Description of output:

// All numbers not in brackets are in seconds.

// Function: name of function profiled
// # of calls: number of times the function was called
// in % of total time: % of total time in profiled functions which was spent inside this function (not including any profiled
//                      functions called by it). This is usually the primary sort key since it gives the functions where the most
//                      time was spent.
// total % of total time: % of total time in profiled functions, which was spent in this function or any functions it called.
// total time: total time spend in the function (includes time spent in all functions it called).
// time per call: average time spent in the function each call. (includes time spent in all functions it called).
// total time in: total time spent within this function, not including time spent in profiled functions called by it.
// time in per call: average time spent within this function per call, not including time spent in profiled functions called by it.

#ifdef ENABLE_PROFILING

#include <windows.h>

#include <map>
#include <mutex>
#include <sstream>
#include <string>
#include <vector>

// These macros refer to a singleton profiling object defined in GPAProfiler.cpp

/// Macro to use a scope-bound object to profile a function.
#define PROFILE_FUNCTION(func) ScopeProfile temp_scope_profile_object(#func)

/// Macro to begin profiling a section.
#define BEGIN_PROFILE_SECTION(func) (profiler_singleton.EnterFunction(#func))

/// Macro to end profiling a section.
#define END_PROFILE_SECTION(func) (profiler_singleton.LeaveFunction(#func))

/// Macro to start profiling.
#define START_PROFILING() (profiler_singleton.Start())

/// Macro to stop profiling.
#define STOP_PROFILING() (profiler_singleton.Stop())

/// Macro to check if profiling is active.
#define IS_PROFILING() (profiler_singleton.Active())

/// Macro to generate a profile report.
#define GENERATE_PROFILE_REPORT() (profiler_singleton.GenerateReport())

/// Macro to write a profile report.
#define WRITE_PROFILE_REPORT(file_name) (profiler_singleton.WriteReport(file_name))

class FunctionInfo
{
public:
    unsigned int calls;
    __int64      total_time_;
    __int64      time_below_;
};

class Profiler
{
public:
    Profiler();

    bool Init();

    void Start();
    void Stop();
    void Reset();

    bool Active() const
    {
        return is_active_;
    }

    bool EnterFunction(const char* function_name);
    bool LeaveFunction(const char* function_name);

    FunctionInfo& GetFunctionInfo(const char* function_name);

    std::string GenerateReport();
    void        WriteReport(std::string file_name);

protected:
    void OutputTime(std::stringstream& ss, __int64 time) const;

    __int64              rdtsc_ticks_per_second_;
    std::vector<__int64> started_timestamps_;
    std::vector<__int64> total_time_below_parent_;

    std::map<std::string, FunctionInfo> function_map_;

    __int64      total_time_;
    unsigned int timing_errors_;

    bool    is_active_;
    __int64 start_time_;
    __int64 stop_time_;
};

extern Profiler profiler_singleton;

class ScopeProfile
{
public:
    ScopeProfile(const char* function_name)
    {
        gpa_profiler_mutex_.lock();
        function_name_ = function_name;
        profiler_singleton.EnterFunction(function_name);
        gpa_profiler_mutex_.unlock();
    }

    ~ScopeProfile()
    {
        profiler_singleton.LeaveFunction(function_name_);
    }

protected:
    const char* function_name_;
    std::mutex  gpa_profiler_mutex_;
};

#else

/// Macro to use a scope-bound object to profile a function.
#define PROFILE_FUNCTION(func)

/// Macro to begin profiling a section.
#define BEGIN_PROFILE_SECTION(func)

/// Macro to end profiling a section.
#define END_PROFILE_SECTION(func)

/// Macro to start profiling.
#define START_PROFILING()

/// Macro to stop profiling.
#define STOP_PROFILING()

/// Macro to check if profiling is active.
#define IS_PROFILING() (false)

/// Macro to generate a profile report.
#define GENERATE_PROFILE_REPORT()

/// Macro to write a profile report.
#define WRITE_PROFILE_REPORT(file_name)

#endif

#endif  // GPU_PERF_API_COMMON_GPA_PROFILER_H_
