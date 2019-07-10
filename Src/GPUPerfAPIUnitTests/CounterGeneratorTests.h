//==============================================================================
// Copyright (c) 2012-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Helper functions for Counter Generator Unit Tests
//==============================================================================

#ifndef _COUNTER_GENERATOR_TEST_H_
#define _COUNTER_GENERATOR_TEST_H_

#include <gtest/gtest.h>
#include "GPUPerfAPI.h"
#include "GPACounterGenerator.h"
#include "GPUPerfAPICounters.h"
#include "GPAHWInfo.h"
#include "GPACommonDefs.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

typedef decltype(GPA_GetAvailableCounters)*             GPA_GetAvailableCountersProc;
typedef decltype(GPA_GetAvailableCountersByGeneration)* GPA_GetAvailableCountersByGenerationProc;

static const unsigned int gDevIdUnknown  = 0xFFFFFFFF;  //< bogus device id
static const unsigned int gDevIdSI       = 0x6798;      //< 7970 Series
static const unsigned int gDevIdCI       = 0x6649;      //< FirePro W5100
static const unsigned int gDevIdCIHawaii = 0x67A0;      //< HAWAII XTGL
static const unsigned int gDevIdVI       = 0x6900;      //< R7 M260
static const unsigned int gDevIdGfx8     = 0x67DF;      //< Gfx8
static const unsigned int gDevIdGfx9     = 0x6863;      //< Gfx9
static const unsigned int gDevIdGfx10    = 0x7310;      //< Gfx10

extern const char* countersLibName;

LibHandle LoadLib(const char* pLibName);
void      UnloadLib(LibHandle libHandle);
void*     GetEntryPoint(LibHandle libHandle, const char* pEntrypointName);

void VerifyNotImplemented(GPA_API_Type api, unsigned int deviceId, gpa_uint8 generateAsicSpecificCounters);
void VerifyNotImplemented(GPA_API_Type api, GPA_Hw_Generation generation, gpa_uint8 generateAsicSpecificCounters);

void VerifyHardwareNotSupported(GPA_API_Type api, unsigned int deviceId, gpa_uint8 generateAsicSpecificCounters);
void VerifyHardwareNotSupported(GPA_API_Type api, GPA_Hw_Generation generation, gpa_uint8 generateAsicSpecificCounters);

void VerifyCounterNames(GPA_API_Type api, unsigned int deviceId, gpa_uint8 generateAsicSpecificCounters, std::vector<const char*> expectedNames);
void VerifyCounterNames(GPA_API_Type api, GPA_Hw_Generation generation, gpa_uint8 generateAsicSpecificCounters, std::vector<const char*> expectedNames);

void VerifyPassCount(GPA_API_Type                     api,
                     unsigned int                     deviceId,
                     gpa_uint8                        generateAsicSpecificCounters,
                     const std::vector<unsigned int>& countersToEnable,
                     unsigned int                     expectedNumPasses);

/// Verifies the number of passes, the counters in each pass, and the output result locations
/// \param api The API being used in the test
/// \param deviceId The hardware being used
/// \param generateAsicSpecificCounters Flag indicating whether to use ASIC specific counters, if available.
/// \param countersToEnable The list of exposed counters being tested
/// \param expectedHwCountersPerPass A list of counters in each pass (list of lists)
/// \param expectedResultLocations A list of maps for the result locations
void VerifyCountersInPass(GPA_API_Type                                                                      api,
                          unsigned int                                                                      deviceId,
                          gpa_uint8                                                                         generateAsicSpecificCounters,
                          const std::vector<unsigned int>&                                                  countersToEnable,
                          const std::vector<std::vector<unsigned int> >&                                    expectedHwCountersPerPass,
                          const std::map<unsigned int, std::map<unsigned int, GPA_CounterResultLocation> >& expectedResultLocations);

/// Verifies the counter calculation
/// \param api The API being used in the test
/// \param deviceId The hardware being used
/// \param generateAsicSpecificCounters Flag indicating whether to use ASIC specific counters, if available.
/// \param counterName Name of the counter
/// \param sampleResults List of sample results
/// \param expectedResult Expected result
void VerifyCounterCalculation(GPA_API_Type                          api,
                              unsigned int                          deviceId,
                              gpa_uint8                             generateAsicSpecificCounters,
                              char*                                 counterName,
                              const std::vector<const gpa_uint64*>& sampleResults,
                              gpa_float64                           expectedResult);

/// Returns a string describing the hardware counters and passes for each public counter, and the scheduling of the
/// combined counters, passes, and result locations
/// \param api The API being used in the test
/// \param deviceId The hardware being used
/// \param generateAsicSpecificCounters Flag indicating whether to use ASIC specific counters, if available.
/// \param countersToEnable The list of exposed counters being tested
/// \param pOutputStream Output string stream describing the counters in each pass and the result locations
void ExplainCountersInPassAndResultLocations(GPA_API_Type                 api,
                                             uint32_t                     deviceId,
                                             gpa_uint8                    generateAsicSpecificCounters,
                                             const std::vector<uint32_t>& countersToEnable,
                                             std::stringstream*           pOutputStream);

#endif  // _COUNTER_GENERATOR_TEST_H_