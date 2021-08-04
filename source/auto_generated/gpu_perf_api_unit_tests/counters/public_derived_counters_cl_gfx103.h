//==============================================================================
// Copyright (c) 2015-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief PublicCounterDefinitions for CL GFX103 for testing.
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef GPA_AUTO_GEN_UNIT_TESTS_COUNTERS_PUBLIC_CL_GFX103
#define GPA_AUTO_GEN_UNIT_TESTS_COUNTERS_PUBLIC_CL_GFX103

#include "gpu_perf_api_unit_tests/counters/gpa_counter_desc.h"

/// Macros for CLGfx103 Public counter index
#define WAVEFRONTS_PUBLIC_CL_GFX103 0
#define VALUINSTS_PUBLIC_CL_GFX103 1
#define SALUINSTS_PUBLIC_CL_GFX103 2
#define VFETCHINSTS_PUBLIC_CL_GFX103 3
#define SFETCHINSTS_PUBLIC_CL_GFX103 4
#define VWRITEINSTS_PUBLIC_CL_GFX103 5
#define LDSINSTS_PUBLIC_CL_GFX103 6
#define GDSINSTS_PUBLIC_CL_GFX103 7
#define VALUUTILIZATION_PUBLIC_CL_GFX103 8
#define VALUBUSY_PUBLIC_CL_GFX103 9
#define SALUBUSY_PUBLIC_CL_GFX103 10
#define FETCHSIZE_PUBLIC_CL_GFX103 11
#define WRITESIZE_PUBLIC_CL_GFX103 12
#define L0CACHEHIT_PUBLIC_CL_GFX103 13
#define L1CACHEHIT_PUBLIC_CL_GFX103 14
#define L2CACHEHIT_PUBLIC_CL_GFX103 15
#define MEMUNITBUSY_PUBLIC_CL_GFX103 16
#define MEMUNITSTALLED_PUBLIC_CL_GFX103 17
#define WRITEUNITSTALLED_PUBLIC_CL_GFX103 18
#define LDSBANKCONFLICT_PUBLIC_CL_GFX103 19

/// Number of public counters for CL GFX103 
const size_t kClGfx103PublicCounterCount = 20;

/// Array of public counters for CL GFX103 
extern const GpaCounterDesc kClGfx103PublicCounters[kClGfx103PublicCounterCount];

#endif  // GPA_AUTO_GEN_UNIT_TESTS_COUNTERS_PUBLIC_CL_GFX103
