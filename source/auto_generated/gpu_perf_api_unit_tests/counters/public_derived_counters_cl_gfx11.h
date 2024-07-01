//==============================================================================
// Copyright (c) 2015-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief PublicCounterDefinitions for CL GFX11 for testing.
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef GPA_AUTO_GEN_UNIT_TESTS_COUNTERS_PUBLIC_CL_GFX11
#define GPA_AUTO_GEN_UNIT_TESTS_COUNTERS_PUBLIC_CL_GFX11

#include "gpu_perf_api_unit_tests/counters/gpa_counter_desc.h"

/// Macros for CLGfx11 Public counter index
#define WAVEFRONTS_PUBLIC_CL_GFX11 0
#define VALUINSTS_PUBLIC_CL_GFX11 1
#define SALUINSTS_PUBLIC_CL_GFX11 2
#define VFETCHINSTS_PUBLIC_CL_GFX11 3
#define SFETCHINSTS_PUBLIC_CL_GFX11 4
#define VWRITEINSTS_PUBLIC_CL_GFX11 5
#define LDSINSTS_PUBLIC_CL_GFX11 6
#define GDSINSTS_PUBLIC_CL_GFX11 7
#define VALUUTILIZATION_PUBLIC_CL_GFX11 8
#define VALUBUSY_PUBLIC_CL_GFX11 9
#define SALUBUSY_PUBLIC_CL_GFX11 10
#define FETCHSIZE_PUBLIC_CL_GFX11 11
#define WRITESIZE_PUBLIC_CL_GFX11 12
#define L0CACHEHIT_PUBLIC_CL_GFX11 13
#define L1CACHEHIT_PUBLIC_CL_GFX11 14
#define L2CACHEHIT_PUBLIC_CL_GFX11 15
#define MEMUNITBUSY_PUBLIC_CL_GFX11 16
#define MEMUNITSTALLED_PUBLIC_CL_GFX11 17
#define WRITEUNITSTALLED_PUBLIC_CL_GFX11 18
#define LDSBANKCONFLICT_PUBLIC_CL_GFX11 19

/// Number of public counters for CL GFX11 
const size_t kClGfx11PublicCounterCount = 20;

/// Array of public counters for CL GFX11 
extern const GpaCounterDesc kClGfx11PublicCounters[kClGfx11PublicCounterCount];

#endif  // GPA_AUTO_GEN_UNIT_TESTS_COUNTERS_PUBLIC_CL_GFX11
