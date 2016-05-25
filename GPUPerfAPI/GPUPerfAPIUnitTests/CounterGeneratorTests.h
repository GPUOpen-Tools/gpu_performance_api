//==============================================================================
// Copyright (c) 2012-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Helper functions for Counter Generator Unit Tests
//==============================================================================

#include <gtest/gtest.h>
#include "GPACounterGenerator.h"
#include "GPUPerfAPICounters.h"
#include "GPAHwInfo.h"
#ifdef _WIN32
    #include <windows.h>
#endif

typedef decltype(GPA_GetAvailableCounters)* GPA_GetAvailableCountersProc;
typedef decltype(GPA_GetAvailableCountersByGeneration)* GPA_GetAvailableCountersByGenerationProc;

static const unsigned int gDevIdUnknown = 0xFFFFFFFF; //< bogus device id
static const unsigned int gDevIdSI = 0x6798;
static const unsigned int gDevIdCI = 0x6650;
static const unsigned int gDevIdVI = 0x6900;

void VerifyNotImplemented(GPA_API_Type api, unsigned int deviceId);
void VerifyNotImplemented(GPA_API_Type api, GPA_HW_GENERATION generation);

void VerifyHardwareNotSupported(GPA_API_Type api, unsigned int deviceId);
void VerifyHardwareNotSupported(GPA_API_Type api, GPA_HW_GENERATION generation);

void VerifyCounterNames(GPA_API_Type api, unsigned int deviceId, std::vector<const char*> expectedNames);
void VerifyCounterNames(GPA_API_Type api, GPA_HW_GENERATION generation, std::vector<const char*> expectedNames);

void VerifyPassCount(GPA_API_Type api, unsigned int deviceId, std::vector<unsigned int> countersToEnable, unsigned int expectedNumPasses);

/// \param api The API being used in the test
/// \param deviceID The hardware being used
/// \param countersToEnable The list of exposed counters being tested
/// \param expectedHwCountersPerPass A list of counters in each pass (list of lists)
/// \param expectedResultLocations A list of maps for the result locations
void VerifyCountersInPass(GPA_API_Type api,
                          unsigned int deviceId,
                          std::vector<unsigned int> countersToEnable,
                          std::vector< std::vector<unsigned int> >& expectedHwCountersPerPass,
                          std::map< unsigned int, std::map<unsigned int, GPA_CounterResultLocation> >& expectedResultLocations);

void VerifyCounterCalculation(GPA_API_Type api, unsigned int deviceId, char* counterName, std::vector<char*>& sampleResults, gpa_float64 expectedResult);
