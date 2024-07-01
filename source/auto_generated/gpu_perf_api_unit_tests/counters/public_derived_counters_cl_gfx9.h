//==============================================================================
// Copyright (c) 2015-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief PublicCounterDefinitions for CL GFX9 for testing.
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef GPA_AUTO_GEN_UNIT_TESTS_COUNTERS_PUBLIC_CL_GFX9
#define GPA_AUTO_GEN_UNIT_TESTS_COUNTERS_PUBLIC_CL_GFX9

#include "gpu_perf_api_unit_tests/counters/gpa_counter_desc.h"

/// Macros for CLGfx9 Public counter index
#define WAVEFRONTS_PUBLIC_CL_GFX9 0
#define VALUINSTS_PUBLIC_CL_GFX9 1
#define SALUINSTS_PUBLIC_CL_GFX9 2
#define VFETCHINSTS_PUBLIC_CL_GFX9 3
#define SFETCHINSTS_PUBLIC_CL_GFX9 4
#define VWRITEINSTS_PUBLIC_CL_GFX9 5
#define FLATVMEMINSTS_PUBLIC_CL_GFX9 6
#define LDSINSTS_PUBLIC_CL_GFX9 7
#define FLATLDSINSTS_PUBLIC_CL_GFX9 8
#define GDSINSTS_PUBLIC_CL_GFX9 9
#define VALUUTILIZATION_PUBLIC_CL_GFX9 10
#define VALUBUSY_PUBLIC_CL_GFX9 11
#define SALUBUSY_PUBLIC_CL_GFX9 12
#define FETCHSIZE_PUBLIC_CL_GFX9 13
#define WRITESIZE_PUBLIC_CL_GFX9 14
#define L1CACHEHIT_PUBLIC_CL_GFX9 15
#define L2CACHEHIT_PUBLIC_CL_GFX9 16
#define MEMUNITBUSY_PUBLIC_CL_GFX9 17
#define MEMUNITSTALLED_PUBLIC_CL_GFX9 18
#define WRITEUNITSTALLED_PUBLIC_CL_GFX9 19
#define LDSBANKCONFLICT_PUBLIC_CL_GFX9 20

/// Number of public counters for CL GFX9 
const size_t kClGfx9PublicCounterCount = 21;

/// Array of public counters for CL GFX9 
extern const GpaCounterDesc kClGfx9PublicCounters[kClGfx9PublicCounterCount];

#endif  // GPA_AUTO_GEN_UNIT_TESTS_COUNTERS_PUBLIC_CL_GFX9
