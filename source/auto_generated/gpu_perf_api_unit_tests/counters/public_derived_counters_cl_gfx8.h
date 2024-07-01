//==============================================================================
// Copyright (c) 2015-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief PublicCounterDefinitions for CL GFX8 for testing.
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef GPA_AUTO_GEN_UNIT_TESTS_COUNTERS_PUBLIC_CL_GFX8
#define GPA_AUTO_GEN_UNIT_TESTS_COUNTERS_PUBLIC_CL_GFX8

#include "gpu_perf_api_unit_tests/counters/gpa_counter_desc.h"

/// Macros for CLGfx8 Public counter index
#define WAVEFRONTS_PUBLIC_CL_GFX8 0
#define VALUINSTS_PUBLIC_CL_GFX8 1
#define SALUINSTS_PUBLIC_CL_GFX8 2
#define VFETCHINSTS_PUBLIC_CL_GFX8 3
#define SFETCHINSTS_PUBLIC_CL_GFX8 4
#define VWRITEINSTS_PUBLIC_CL_GFX8 5
#define FLATVMEMINSTS_PUBLIC_CL_GFX8 6
#define LDSINSTS_PUBLIC_CL_GFX8 7
#define FLATLDSINSTS_PUBLIC_CL_GFX8 8
#define GDSINSTS_PUBLIC_CL_GFX8 9
#define VALUUTILIZATION_PUBLIC_CL_GFX8 10
#define VALUBUSY_PUBLIC_CL_GFX8 11
#define SALUBUSY_PUBLIC_CL_GFX8 12
#define FETCHSIZE_PUBLIC_CL_GFX8 13
#define WRITESIZE_PUBLIC_CL_GFX8 14
#define CACHEHIT_PUBLIC_CL_GFX8 15
#define MEMUNITBUSY_PUBLIC_CL_GFX8 16
#define MEMUNITSTALLED_PUBLIC_CL_GFX8 17
#define WRITEUNITSTALLED_PUBLIC_CL_GFX8 18
#define LDSBANKCONFLICT_PUBLIC_CL_GFX8 19

/// Number of public counters for CL GFX8 
const size_t kClGfx8PublicCounterCount = 20;

/// Array of public counters for CL GFX8 
extern const GpaCounterDesc kClGfx8PublicCounters[kClGfx8PublicCounterCount];

#endif  // GPA_AUTO_GEN_UNIT_TESTS_COUNTERS_PUBLIC_CL_GFX8
