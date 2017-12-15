//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Internal class to support profiling GPA calls themselves
//==============================================================================

//#define ENABLE_PROFILING
#ifdef ENABLE_PROFILING

#include "GPAProfiler.h"

#include "assert.h"

#include <iostream>
#include <fstream>


using namespace std;


static DWORD getCPUFreq()
{
    DWORD BufSize = sizeof(DWORD);
    DWORD dwMHz;
    HKEY hKey;

    // open the key where the proc speed is hidden:
    long lError = RegOpenKeyExA(HKEY_LOCAL_MACHINE,
                                "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
                                0,
                                KEY_READ,
                                &hKey);

    assert(lError == ERROR_SUCCESS);
    UNREFERENCED_PARAMETER(lError);

    // query the key;
    RegQueryValueExA(hKey, "~MHz", nullptr, nullptr, (LPBYTE) &dwMHz, &BufSize);

    RegCloseKey(hKey);

    return dwMHz;
}


static __int64 GetRDTSCTicksPerSecond()
{
    // use this to control how much time is spent measuring the high freq clock.
    // Measure for 1 / scaling seconds.
    // Higher numbers mean less time spent measuring but larger potential error range.
    const __int64 scaling = 4;

    // variables for the clock-cycles:
    __int64 cyclesStart = 0, cyclesStop = 0;

    // variables for the High-Res Preformance Counter:
    unsigned __int64 nCtr = 0, nFreq = 0, nCtrStop = 0;

    // retrieve performance-counter frequency per second:
    if (!QueryPerformanceFrequency((LARGE_INTEGER*) &nFreq)) { return 0; }

    // retrieve the current value of the performance counter:
    QueryPerformanceCounter((LARGE_INTEGER*) &nCtrStop);

    // add the frequency to the counter-value:
    nCtrStop += nFreq / scaling;

    cyclesStart = __rdtsc();

    do
    {
        // retrieve the value of the performance counter
        // until 1 sec has gone by:
        QueryPerformanceCounter((LARGE_INTEGER*) &nCtr);
    }
    while (nCtr < nCtrStop);

    cyclesStop = __rdtsc();

    return (cyclesStop - cyclesStart) * scaling;
}


// Constructor uses init to determine tick rate on this computer
Profiler::Profiler()
{
    m_RDTSCTicksPerSecond = 0;
    Init();
}

// determine tick rate on this computer
// also SetThreadAffinityMask to ensure accurate timings since running on same core always
bool Profiler::Init()
{
    Reset();

    SetThreadAffinityMask(GetCurrentThread(), 1);

    m_RDTSCTicksPerSecond = GetRDTSCTicksPerSecond();
    DWORD freq = getCPUFreq();

    DWORD freqCompare = DWORD(m_RDTSCTicksPerSecond / 1000000);

    if (freqCompare != freq)
    {
        return false;
    }

    return true;
}

void Profiler::Reset()
{
    m_startedTimestamps.clear();
    m_totalTimeBelowParent.clear();
    m_functionMap.clear();

    m_totalTime = 0;
    m_timingErrors = 0;
    m_active = false;
}


void Profiler::Start()
{
    Reset();
    m_active = true;
    m_startTime = __rdtsc();
}


void Profiler::Stop()
{
    m_stopTime = __rdtsc();
    m_active = false;
}


bool Profiler::EnterFunction(const char* pFunctionName)
{
    UNREFERENCED_PARAMETER(pFunctionName);

    __int64 startTimestamp = __rdtsc();

    // ignore any profiling calls when not active
    if (!Active())
    {
        return true;
    }

    // add enter timestamp to stack
    m_startedTimestamps.push_back(startTimestamp);
    // start time below total at 0
    m_totalTimeBelowParent.push_back(0);

    return true;
}


bool Profiler::LeaveFunction(const char* pFunctionName)
{
    __int64 endTimestamp = __rdtsc();

    // ignore any profiling calls when not active
    if (!Active())
    {
        return true;
    }

    // ensure that enter function was called prior to this leave
    assert(m_startedTimestamps.size() > 0);

    if (m_startedTimestamps.size() == 0)
    {
        return false;
    }

    // pop the start time for the function
    __int64 startTimestamp = m_startedTimestamps.back();
    m_startedTimestamps.pop_back();

    // look up the function info for this function
    FunctionInfo& fi = m_functionMap[std::string(pFunctionName)];

    // inc call count
    fi.calls++;

    // compute delta between entering and leaving the function
    __int64 deltaForThisInvocation = endTimestamp - startTimestamp;

    if (deltaForThisInvocation < 0)
    {
        // problem timing
        deltaForThisInvocation = 0;
        m_timingErrors++;
        //try and fix
        SetThreadAffinityMask(GetCurrentThread(), 1);
    }

    // inc total time spent in profiled code
    fi.totalTime += deltaForThisInvocation;

    // retrieve the time below total, which will have been updated by any functions below this one
    fi.timeBelow += m_totalTimeBelowParent.back();
    m_totalTimeBelowParent.pop_back();

    // now contribute to parent of this function if there was one
    if (m_totalTimeBelowParent.size() > 0)
    {
        // we are below a parent function, so add the time of this function to the time below total
        m_totalTimeBelowParent[m_totalTimeBelowParent.size() - 1] += deltaForThisInvocation;
    }
    else
    {
        // we are now evaluating a top level function call, add it's total time to the total time for profiling
        m_totalTime += deltaForThisInvocation;
    }


    return true;
}


FunctionInfo& Profiler::GetFunctionInfo(const char* pFunctionName)
{
    FunctionInfo& fi = m_functionMap[std::string(pFunctionName)];
    return fi;
}


void Profiler::outputTime(std::stringstream& ss, __int64 time)
{
    double t = (double)time / (double)m_RDTSCTicksPerSecond;
    ss << t;
    ss << "(";
    ss << time;
    ss << ")";

}


// create a string containing a report of all profiling
std::string Profiler::GenerateReport()
{
    // if profiling, stop
    if (Active())
    {
        Stop();
    }

    //   std::string str;
    std::stringstream str;
    str << "Time profiling = ";
    outputTime(str, m_stopTime - m_startTime);
    str << std::endl;

    str << "Total time in functions = ";
    outputTime(str, m_totalTime);
    str << std::endl;

    str << "% time in functions = ";
    double pctOfTotal = (double)m_totalTime * 100.0 / (double)(m_stopTime - m_startTime);
    str << pctOfTotal;
    str << std::endl;

    str << "Timing errors = ";
    str << m_timingErrors;
    str << std::endl;
    str << std::endl;

    str << "Function, # of calls, in % of total time, total % of total time, total time, time per call, total time in, time in per call";
    str << std::endl;

    for (std::map<std::string, FunctionInfo>::const_iterator it = m_functionMap.begin(); it != m_functionMap.end(); it++)
    {
        //      str << "Function ";
#if 0
        str << it->first;
        str << ":[";
        str << it->second.calls;
        str << "] tot: ";
        outputTime(str, it->second.totalTime);
        str << ", in: ";
        outputTime(str, it->second.totalTime - it->second.timeBelow);
        str << ", %: ";
        double pct = ((double)(it->second.totalTime - it->second.timeBelow) / (double)m_totalTime) * 100.0;
        str << pct;
        str << endl;
#endif
        str << it->first;
        str << ", ";
        str << it->second.calls;
        str << ", ";
        double pct = ((double)(it->second.totalTime - it->second.timeBelow) / (double)m_totalTime) * 100.0;
        str << pct;
        str << ", ";
        double pctTotal = ((double)it->second.totalTime / (double)m_totalTime) * 100.0;
        str << pctTotal;
        str << ", ";
        outputTime(str, it->second.totalTime);
        str << ", ";
        outputTime(str, it->second.totalTime / it->second.calls);
        str << ", ";
        outputTime(str, it->second.totalTime - it->second.timeBelow);
        str << ", ";
        outputTime(str, (it->second.totalTime - it->second.timeBelow) / it->second.calls);
        str << ", ";
        str << endl;
    }

    return str.str();
}


// generate a profiling report and write it to disk using the specified filename.
void Profiler::WriteReport(std::string filename)
{
    string s = GenerateReport();
    ofstream file(filename.c_str(), ios::out);

    if (file.is_open())
    {
        file << s;
        file.close();
    }
}


Profiler gProfilerSingleton;

#else
// !ENABLE_PROFILING

#endif   // ENABLE_PROFILING
