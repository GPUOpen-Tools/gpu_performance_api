//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Internal class to support profiling GPA calls themselves
//==============================================================================

#ifndef _GPA_PROFILER_H_
#define _GPA_PROFILER_H_

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
// GPA_BeginPass    9   0.628688    0.628688     0.00315014(8484159)     0.000350016(942684)     0.00315014(8484159)     0.000350016(942684)
// GPA_BeginSample  1647    0.440372    0.440372     0.00220656(5942836)     1.33964e-006(3608)  0.00220656(5942836)     1.33964e-006(3608)
// GPA_BeginSession 1   5.65964 5.68611  0.0284912(76734166)     0.0284912(76734166)     0.0283585(76376984)     0.0283585(76376984)


// Description of output:

// all numbers not in brackets are in seconds

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

//#define ENABLE_PROFILING
#include <mutex>

#ifdef ENABLE_PROFILING

#include "windows.h"

#include <vector>
#include <map>
#include <string>
#include <sstream>


// these macros refer to a singleton profiling object defined in GPAProfiler.cpp

/// macro to use a scope-bound object to profile a function
#define PROFILE_FUNCTION(func) ScopeProfile _tempScopeProfileObject(#func)

/// macro to begin profiling a section
#define BEGIN_PROFILE_SECTION(func) (gProfilerSingleton.EnterFunction(#func))

/// macro to end profiling a section
#define END_PROFILE_SECTION(func) (gProfilerSingleton.LeaveFunction(#func))

/// macro to start profiling
#define START_PROFILING() (gProfilerSingleton.Start())

/// macro to stop profiling
#define STOP_PROFILING() (gProfilerSingleton.Stop())

/// macro to check if profiling is active
#define IS_PROFILING() (gProfilerSingleton.Active())

/// macro to generate a profile report
#define GENERATE_PROFILE_REPORT() (gProfilerSingleton.GenerateReport())

/// macro to write a profile report
#define WRITE_PROFILE_REPORT(filename) (gProfilerSingleton.WriteReport(filename))

class FunctionInfo
{
public:
    unsigned int calls;
    __int64 totalTime;
    __int64 timeBelow;
};


class Profiler
{

public:
    Profiler();

    bool Init();

    void Start();
    void Stop();
    void Reset();

    bool Active()
    {
        return m_active;
    }

    bool EnterFunction(const char* pFunctionName);
    bool LeaveFunction(const char* pFunctionName);

    FunctionInfo& GetFunctionInfo(const char* pFunctionName);

    std::string GenerateReport();
    void WriteReport(std::string filename);

protected:
    void outputTime(std::stringstream& ss, __int64 time);

    __int64 m_RDTSCTicksPerSecond;
    std::vector<__int64> m_startedTimestamps;
    std::vector<__int64> m_totalTimeBelowParent;

    std::map<std::string, FunctionInfo> m_functionMap;

    __int64 m_totalTime;
    unsigned int m_timingErrors;

    bool m_active;
    __int64 m_startTime;
    __int64 m_stopTime;
};


extern Profiler gProfilerSingleton;


class ScopeProfile
{
public:
    ScopeProfile(const char* pFunctionName)
    {
        m_mutex.lock();
        m_pFunctionName = pFunctionName;
        gProfilerSingleton.EnterFunction(pFunctionName);
        m_mutex.unlock();
    }

    ~ScopeProfile()
    {
        gProfilerSingleton.LeaveFunction(m_pFunctionName);
    }

protected:
    const char* m_pFunctionName;
    std::mutex m_mutex;
};


#else

/// macro to use a scope-bound object to profile a function
#define PROFILE_FUNCTION(func)

/// macro to begin profiling a section
#define BEGIN_PROFILE_SECTION(func)

/// macro to end profiling a section
#define END_PROFILE_SECTION(func)

/// macro to start profiling
#define START_PROFILING()

/// macro to stop profiling
#define STOP_PROFILING()

/// macro to check if profiling is active
#define IS_PROFILING() (false)

/// macro to generate a profile report
#define GENERATE_PROFILE_REPORT()

/// macro to write a profile report
#define WRITE_PROFILE_REPORT(filename)

#endif

#endif // _GPA_PROFILER_H_
