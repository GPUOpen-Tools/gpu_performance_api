//==============================================================================
// Copyright (c) 2015-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief PublicCounterDefinitions for CL GFX10 for testing.
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef GPA_AUTO_GEN_UNIT_TESTS_COUNTERS_PUBLIC_CL_GFX10
#define GPA_AUTO_GEN_UNIT_TESTS_COUNTERS_PUBLIC_CL_GFX10

#include "gpu_perf_api_unit_tests/counters/gpa_counter_desc.h"

/// Macros for CLGfx10 Public counter index
#define WAVEFRONTS_PUBLIC_CL_GFX10 0
#define VALUINSTS_PUBLIC_CL_GFX10 1
#define SALUINSTS_PUBLIC_CL_GFX10 2
#define VFETCHINSTS_PUBLIC_CL_GFX10 3
#define SFETCHINSTS_PUBLIC_CL_GFX10 4
#define VWRITEINSTS_PUBLIC_CL_GFX10 5
#define LDSINSTS_PUBLIC_CL_GFX10 6
#define GDSINSTS_PUBLIC_CL_GFX10 7
#define VALUUTILIZATION_PUBLIC_CL_GFX10 8
#define VALUBUSY_PUBLIC_CL_GFX10 9
#define SALUBUSY_PUBLIC_CL_GFX10 10
#define FETCHSIZE_PUBLIC_CL_GFX10 11
#define WRITESIZE_PUBLIC_CL_GFX10 12
#define L0CACHEHIT_PUBLIC_CL_GFX10 13
#define L1CACHEHIT_PUBLIC_CL_GFX10 14
#define L2CACHEHIT_PUBLIC_CL_GFX10 15
#define MEMUNITBUSY_PUBLIC_CL_GFX10 16
#define MEMUNITSTALLED_PUBLIC_CL_GFX10 17
#define WRITEUNITSTALLED_PUBLIC_CL_GFX10 18
#define LDSBANKCONFLICT_PUBLIC_CL_GFX10 19

/// Number of public counters for CL GFX10 
const size_t kClGfx10PublicCounterCount = 20;

/// Array of public counters for CL GFX10 
extern const GpaCounterDesc kClGfx10PublicCounters[kClGfx10PublicCounterCount];

#endif  // GPA_AUTO_GEN_UNIT_TESTS_COUNTERS_PUBLIC_CL_GFX10
