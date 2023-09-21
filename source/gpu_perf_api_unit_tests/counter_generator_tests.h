//==============================================================================
// Copyright (c) 2012-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Helper functions for Counter Generator Unit Tests.
//==============================================================================

#ifndef GPU_PERF_API_UNIT_TESTS_COUNTER_GENERATOR_TESTS_H_
#define GPU_PERF_API_UNIT_TESTS_COUNTER_GENERATOR_TESTS_H_

#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

#include <gtest/gtest.h>

#include "gpu_performance_api/gpu_perf_api.h"
#include "gpu_performance_api/gpu_perf_api_counters.h"
#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_common/gpa_hw_info.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator.h"

#include "gpu_perf_api_unit_tests/counters/gpa_counter_desc.h"

static const unsigned int kDevIdUnknown      = 0xFFFFFFFF;  ///< bogus device id.
static const unsigned int kDevIdSI           = 0x6798;      ///< 7970 Series.
static const unsigned int kDevIdCI           = 0x6649;      ///< FirePro W5100.
static const unsigned int kDevIdCIHawaii     = 0x67A0;      ///< HAWAII XTGL.
static const unsigned int kDevIdVI           = 0x6900;      ///< R7 M260.
static const unsigned int kDevIdGfx8         = 0x67DF;      ///< Gfx8.
static const unsigned int kDevIdGfx9         = 0x6863;      ///< Gfx9.
static const unsigned int kDevIdMi250X       = 0x740C;      ///< GFX9_0_A (MI250X).
static const unsigned int kDevIdMi210        = 0x740F;      ///< GFX9_0_A (MI210).
static const unsigned int kDevIdGfx10        = 0x7310;      ///< Gfx10.
static const unsigned int kDevIdGfx10_3      = 0x73A0;      ///< Gfx10_3.
static const unsigned int kDevIdGfx11        = 0x744C;      ///< Gfx11.
static const unsigned int kDevIdGfx11_0_3    = 0x15BF;      ///< Gfx11_0_3.
static const unsigned int kDevIdGfx11_0_3B   = 0x15C8;      ///< Gfx11_0_3B.
static const unsigned int kDevIdUnsupported1 = 0x1506;      ///< An unsupported device id.
static const unsigned int kDevIdUnsupported2 = 0x164e;      ///< An unsupported device id.

/// Name of the counter library.
extern const char* kCountersLibName;

/// @brief Load the library.
///
/// @param [in] lib_name The name of the library to load.
///
/// @return The handle to the loaded library.
LibHandle LoadLib(const char* lib_name);

/// @brief Unload the library.
///
/// @param [in] lib_handle The handle of the library to unload.
void UnloadLib(LibHandle lib_handle);

/// @brief Get an entrypoint within a library.
///
/// @param [in] lib_handle The handle of the loaded library.
/// @param [in] entry_point_name The name of the entrypoint.
///
/// @return Function pointer to the loaded entrypoint.
void* GetEntryPoint(LibHandle lib_handle, const char* entrypoint_name);

/// Verifies the internal counter count.
///
/// @param [in] api The API being used in the test.
/// @param [in] generation The hardware generation being used.
/// @param [in] generation_asic_specific_counters Flag indicating whether to use ASIC specific counters, if available.
/// @param [in] public_counters Public descriptions of the counter.
void VerifyDerivedCounterCount(const GpaApiType                  api,
                               const GpaHwGeneration             generation,
                               const GpaUInt8                    generate_asic_specific_counters,
                               const std::vector<GpaCounterDesc> counter_descriptions);

void VerifyNotImplemented(GpaApiType api, unsigned int device_id, GpaUInt8 generation_asic_specific_counters);

void VerifyNotImplemented(GpaApiType api, GpaHwGeneration generation, GpaUInt8 genrate_asic_specific_counters);

void VerifyHardwareNotSupported(GpaApiType api, unsigned int device_id, GpaUInt8 generate_asic_specific_counters);

void VerifyHardwareNotSupported(GpaApiType api, GpaHwGeneration generation, GpaUInt8 generate_asic_specific_counters);

void VerifyCounterNames(GpaApiType               api,
                        unsigned int             device_id,
                        GpaUInt8                 generate_asic_specific_counters,
                        std::vector<const char*> expected_names,
                        std::vector<const char*> expected_hardware_names);

void VerifyCounterNames(GpaApiType               api,
                        GpaHwGeneration          generation,
                        GpaUInt8                 generate_asic_specific_counters,
                        std::vector<const char*> expected_names,
                        std::vector<const char*> expected_hardware_names);

void VerifyOpenCounterContext(GpaApiType api, GpaHwGeneration generation);

void VerifyCounterLibInterface(GpaApiType                         api,
                               unsigned int                       device_id,
                               unsigned int                       revision_id,
                               GpaUInt8                           asic_specific,
                               std::vector<GpaDerivedCounterInfo> expected_derived_counter_list = std::vector<GpaDerivedCounterInfo>());

void VerifyCounterByPassCounterLibEntry(GpaApiType api, unsigned device_id, unsigned revision_id, GpaUInt8 asic_specific);

void VerifyPassCount(GpaApiType                       api,
                     unsigned int                     device_id,
                     GpaUInt8                         generate_asic_specific_counters,
                     const std::vector<unsigned int>& counters_to_enable,
                     unsigned int                     expected_num_passes);

/// @brief Verifies the number of passes, the counters in each pass, and the output result locations.
///
/// @param [in] api The API being used in the test.
/// @param [in] device_id The hardware being used.
/// @param [in] generation_asic_specific_counters Flag indicating whether to use ASIC specific counters, if available.
/// @param [in] counters_to_enable The list of exposed counters being tested.
/// @param [in] expected_hw_counters_per_pass A list of counters in each pass (list of lists).
/// @param [in] expected_result_location A list of maps for the result locations.
void VerifyCountersInPass(GpaApiType                                                                      api,
                          unsigned int                                                                    device_id,
                          GpaUInt8                                                                        generate_asic_specific_counters,
                          const std::vector<unsigned int>&                                                counters_to_enable,
                          const std::vector<std::vector<unsigned int>>&                                   expected_hw_counters_per_pass,
                          const std::map<unsigned int, std::map<unsigned int, GpaCounterResultLocation>>& expected_result_location);

/// @brief Verifies the counter calculation.
///
/// @param [in] api The API being used in the test
/// @param [in] device_id The hardware being used
/// @param [in] generation_asic_specific_counters Flag indicating whether to use ASIC specific counters, if available.
/// @param [in] counter_name Name of the counter
/// @param [in] sample_results List of sample results
/// @param [in] expected_result Expected result
void VerifyCounterCalculation(GpaApiType                           api,
                              unsigned int                         device_id,
                              GpaUInt8                             generate_asic_specific_counters,
                              char*                                counter_name,
                              const std::vector<const GpaUInt64*>& sample_results,
                              GpaFloat64                           expected_result);

/// @brief Verifies the counter calculation.
///
/// @param [in] public_counters Public descriptions of the counter
void VerifyCounterFormula(std::vector<GpaCounterDesc> public_counters);

/// @brief Returns a string describing the hardware counters and passes for each public counter, and the scheduling of the
/// combined counters, passes, and result locations.
///
/// @param [in] api The API being used in the test.
/// @param [in] device_id The hardware being used.
/// @param [in] generation_asic_specific_counters Flag indicating whether to use ASIC specific counters, if available.
/// @param [in] counters_to_enable The list of exposed counters being tested.
/// @param [in,out] output_stream Output string stream describing the counters in each pass and the result locations.
void ExplainCountersInPassAndResultLocations(GpaApiType                   api,
                                             uint32_t                     device_id,
                                             GpaUInt8                     generate_asic_specific_counters,
                                             const std::vector<uint32_t>& counters_to_enable,
                                             std::stringstream*           output_stream);

#endif  // GPU_PERF_API_UNIT_TESTS_COUNTER_GENERATOR_TESTS_H_
