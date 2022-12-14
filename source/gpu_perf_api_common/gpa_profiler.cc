//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Internal class to support profiling GPA calls themselves.
//==============================================================================

#ifdef ENABLE_PROFILING

#include "gpu_perf_api_common/gpa_profiler.h"

#include <assert.h>

#include <iostream>
#include <fstream>

using namespace std;

static DWORD GetCpuFreq()
{
    DWORD buf_size = sizeof(DWORD);
    DWORD freq_mhz;
    HKEY  key_handle;

    // Open the key where the proc speed is hidden.
    long l_error = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &key_handle);

    assert(l_error == ERROR_SUCCESS);
    UNREFERENCED_PARAMETER(l_error);

    // Query the key.
    RegQueryValueExA(key_handle, "~MHz", nullptr, nullptr, (LPBYTE)&freq_mhz, &buf_size);

    RegCloseKey(key_handle);

    return freq_mhz;
}

static __int64 GetRdtscTicksPerSecond()
{
    // Use this to control how much time is spent measuring the high freq clock.
    // Measure for 1 / scaling seconds.
    // Higher numbers mean less time spent measuring but larger potential error range.
    const __int64 scaling = 4;

    // Variables for the clock-cycles.
    __int64 cycles_start = 0, cycles_stop = 0;

    // Variables for the High-Res Performance Counter.
    unsigned __int64 ctr_start = 0, freq = 0, ctr_stop = 0;

    // Retrieve performance-counter frequency per second.
    if (!QueryPerformanceFrequency((LARGE_INTEGER*)&freq))
    {
        return 0;
    }

    // Retrieve the current value of the performance counter.
    QueryPerformanceCounter((LARGE_INTEGER*)&ctr_stop);

    // Add the frequency to the counter-value.
    ctr_stop += freq / scaling;

    cycles_start = __rdtsc();

    do
    {
        // Retrieve the value of the performance counter
        // until 1 sec has gone by.
        QueryPerformanceCounter((LARGE_INTEGER*)&ctr_start);
    } while (ctr_start < ctr_stop);

    cycles_stop = __rdtsc();

    return (cycles_stop - cycles_start) * scaling;
}

Profiler::Profiler()
{
    // Constructor uses init to determine tick rate on this computer.
    rdtsc_ticks_per_second_ = 0;
    Init();
}

bool Profiler::Init()
{
    // Determine tick rate on this computer.
    // Also SetThreadAffinityMask to ensure accurate timings since running on same core always.
    Reset();

    SetThreadAffinityMask(GetCurrentThread(), 1);

    rdtsc_ticks_per_second_ = GetRdtscTicksPerSecond();
    DWORD freq              = GetCpuFreq();

    DWORD freq_compare = DWORD(rdtsc_ticks_per_second_ / 1000000);

    if (freq_compare != freq)
    {
        return false;
    }

    return true;
}

void Profiler::Reset()
{
    started_timestamps_.clear();
    total_time_below_parent_.clear();
    function_map_.clear();

    total_time_    = 0;
    timing_errors_ = 0;
    is_active_     = false;
}

void Profiler::Start()
{
    Reset();
    is_active_  = true;
    start_time_ = __rdtsc();
}

void Profiler::Stop()
{
    stop_time_ = __rdtsc();
    is_active_ = false;
}

bool Profiler::EnterFunction(const char* function_name)
{
    UNREFERENCED_PARAMETER(function_name);

    __int64 start_timestamp = __rdtsc();

    // Ignore any profiling calls when not active.
    if (!Active())
    {
        return true;
    }

    // Add enter timestamp to stack.
    started_timestamps_.push_back(start_timestamp);
    // Start time below total at 0.
    total_time_below_parent_.push_back(0);

    return true;
}

bool Profiler::LeaveFunction(const char* function_name)
{
    __int64 end_timestamp = __rdtsc();

    // Ignore any profiling calls when not active.
    if (!Active())
    {
        return true;
    }

    // Ensure that enter function was called prior to this leave.
    assert(started_timestamps_.size() > 0);

    if (started_timestamps_.size() == 0)
    {
        return false;
    }

    // Pop the start time for the function.
    __int64 start_timestamp = started_timestamps_.back();
    started_timestamps_.pop_back();

    // Look up the function info for this function.
    FunctionInfo& fi = function_map_[std::string(function_name)];

    // Increment call count
    fi.calls++;

    // Compute delta between entering and leaving the function.
    __int64 delta_for_this_invocation = end_timestamp - start_timestamp;

    if (delta_for_this_invocation < 0)
    {
        // There is a problem with timing.
        delta_for_this_invocation = 0;
        timing_errors_++;
        // Try and fix.
        SetThreadAffinityMask(GetCurrentThread(), 1);
    }

    // Increment total time spent in profiled code.
    fi.total_time_ += delta_for_this_invocation;

    // Retrieve the time below total, which will have been updated by any functions below this one.
    fi.time_below_ += total_time_below_parent_.back();
    total_time_below_parent_.pop_back();

    // Now contribute to parent of this function if there was one.
    if (total_time_below_parent_.size() > 0)
    {
        // We are below a parent function, so add the time of this function to the time below total.
        total_time_below_parent_[total_time_below_parent_.size() - 1] += delta_for_this_invocation;
    }
    else
    {
        // We are now evaluating a top level function call, add it's total time to the total time for profiling.
        total_time_ += delta_for_this_invocation;
    }

    return true;
}

FunctionInfo& Profiler::GetFunctionInfo(const char* function_name)
{
    FunctionInfo& fi = function_map_[std::string(function_name)];
    return fi;
}

void Profiler::OutputTime(std::stringstream& ss, __int64 time) const
{
    double t = (double)time / (double)rdtsc_ticks_per_second_;
    ss << t;
    ss << "(";
    ss << time;
    ss << ")";
}

// Create a string containing a report of all profiling.
std::string Profiler::GenerateReport()
{
    // If profiling, stop.
    if (Active())
    {
        Stop();
    }

    std::stringstream str;
    str << "Time profiling = ";
    OutputTime(str, stop_time_ - start_time_);
    str << std::endl;

    str << "Total time in functions = ";
    OutputTime(str, total_time_);
    str << std::endl;

    str << "% time in functions = ";
    double percent_of_total = (double)total_time_ * 100.0 / (double)(stop_time_ - start_time_);
    str << percent_of_total;
    str << std::endl;

    str << "Timing errors = ";
    str << timing_errors_;
    str << std::endl;
    str << std::endl;

    str << "Function, # of calls, in % of total time, total % of total time, total time, time per call, total time in, time in per call";
    str << std::endl;

    for (std::map<std::string, FunctionInfo>::const_iterator it = function_map_.begin(); it != function_map_.end(); it++)
    {
        //      str << "Function ";
#if 0
        str << it->first;
        str << ":[";
        str << it->second.calls;
        str << "] tot: ";
        outputTime(str, it->second.total_time_);
        str << ", in: ";
        outputTime(str, it->second.total_time_ - it->second.time_below_);
        str << ", %: ";
        double pct = ((double)(it->second.total_time_ - it->second.time_below_) / (double)total_time_) * 100.0;
        str << pct;
        str << endl;
#endif
        str << it->first;
        str << ", ";
        str << it->second.calls;
        str << ", ";
        double pct = ((double)(it->second.total_time_ - it->second.time_below_) / (double)total_time_) * 100.0;
        str << pct;
        str << ", ";
        double percent_total = ((double)it->second.total_time_ / (double)total_time_) * 100.0;
        str << percent_total;
        str << ", ";
        OutputTime(str, it->second.total_time_);
        str << ", ";
        OutputTime(str, it->second.total_time_ / it->second.calls);
        str << ", ";
        OutputTime(str, it->second.total_time_ - it->second.time_below_);
        str << ", ";
        OutputTime(str, (it->second.total_time_ - it->second.time_below_) / it->second.calls);
        str << ", ";
        str << endl;
    }

    return str.str();
}

// Generate a profiling report and write it to disk using the specified file_name.
void Profiler::WriteReport(std::string file_name)
{
    string   s = GenerateReport();
    ofstream file(file_name.c_str(), ios::out);

    if (file.is_open())
    {
        file << s;
        file.close();
    }
}

Profiler profiler_singleton;

#else
// !ENABLE_PROFILING

#endif  // ENABLE_PROFILING
