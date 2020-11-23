//==============================================================================
// Copyright (c) 2012-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Helper functions for Counter Generator Unit Tests
//==============================================================================

#ifndef _COUNTER_GENERATOR_TEST_H_
#define _COUNTER_GENERATOR_TEST_H_

#include <gtest/gtest.h>

#include "gpu_perf_api.h"
#include "gpu_perf_api_types.h"
#include "gpa_counter_desc.h"
#include "gpa_counter_generator.h"
#include "gpu_perf_api_counters.h"
#include "gpa_hw_info.h"
#include "gpa_common_defs.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

static const unsigned int gDevIdUnknown  = 0xFFFFFFFF;  //< bogus device id
static const unsigned int gDevIdSI       = 0x6798;      //< 7970 Series
static const unsigned int gDevIdCI       = 0x6649;      //< FirePro W5100
static const unsigned int gDevIdCIHawaii = 0x67A0;      //< HAWAII XTGL
static const unsigned int gDevIdVI       = 0x6900;      //< R7 M260
static const unsigned int gDevIdGfx8     = 0x67DF;      //< Gfx8
static const unsigned int gDevIdGfx9     = 0x6863;      //< Gfx9
static const unsigned int gDevIdGfx10    = 0x7310;      //< Gfx10
static const unsigned int gDevIdGfx10_3  = 0x73A0;      //< Gfx10_3

extern const char* countersLibName;

LibHandle LoadLib(const char* pLibName);
void      UnloadLib(LibHandle libHandle);
void*     GetEntryPoint(LibHandle libHandle, const char* pEntrypointName);

/// Verifies the internal counter count
/// \param api The API being used in the test
/// \param generation The hardware generation being used
/// \param generateAsicSpecificCounters Flag indicating whether to use ASIC specific counters, if available.
/// \param public_counters Public descriptions of the counter
void VerifyDerivedCounterCount(const GPA_API_Type                api,
                               const GPA_Hw_Generation           generation,
                               const gpa_uint8                   generate_asic_specific_counters,
                               const std::vector<GPACounterDesc> counter_descriptions);

void VerifyNotImplemented(GPA_API_Type api, unsigned int deviceId, gpa_uint8 generateAsicSpecificCounters);
void VerifyNotImplemented(GPA_API_Type api, GPA_Hw_Generation generation, gpa_uint8 generateAsicSpecificCounters);

void VerifyHardwareNotSupported(GPA_API_Type api, unsigned int deviceId, gpa_uint8 generateAsicSpecificCounters);
void VerifyHardwareNotSupported(GPA_API_Type api, GPA_Hw_Generation generation, gpa_uint8 generateAsicSpecificCounters);

void VerifyCounterNames(GPA_API_Type api, unsigned int deviceId, gpa_uint8 generateAsicSpecificCounters, std::vector<const char*> expectedNames);
void VerifyCounterNames(GPA_API_Type api, GPA_Hw_Generation generation, gpa_uint8 generateAsicSpecificCounters, std::vector<const char*> expectedNames);

void VerifyCounterLibInterface(GPA_API_Type                       api,
                               unsigned int                       device_id,
                               unsigned int                       revision_id,
                               gpa_uint8                          asic_specific,
                               std::vector<GpaDerivedCounterInfo> expected_derived_counter_list = std::vector<GpaDerivedCounterInfo>());

void VerifyCounterByPassCounterLibEntry(GPA_API_Type api, unsigned device_id, unsigned revision_id, gpa_uint8 asic_specific);

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
void VerifyCountersInPass(GPA_API_Type                                                                     api,
                          unsigned int                                                                     deviceId,
                          gpa_uint8                                                                        generateAsicSpecificCounters,
                          const std::vector<unsigned int>&                                                 countersToEnable,
                          const std::vector<std::vector<unsigned int>>&                                    expectedHwCountersPerPass,
                          const std::map<unsigned int, std::map<unsigned int, GPA_CounterResultLocation>>& expectedResultLocations);

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

/// Verifies the counter calculation
/// \param public_counters Public descriptions of the counter
void VerifyCounterFormula(std::vector<GPACounterDesc> public_counters);

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