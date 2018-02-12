//==============================================================================
// Copyright (c) 2015-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for CLGFX6 for testing
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef _GPA_TESTS_COUNTERS_CLGFX6_
#define _GPA_TESTS_COUNTERS_CLGFX6_

#include "GPACounterDesc.h"

/// Macros for CLGfx6 Public counter index
#define WavefrontsCLGfx6 0
#define VALUInstsCLGfx6 1
#define SALUInstsCLGfx6 2
#define VFetchInstsCLGfx6 3
#define SFetchInstsCLGfx6 4
#define VWriteInstsCLGfx6 5
#define LDSInstsCLGfx6 6
#define GDSInstsCLGfx6 7
#define VALUUtilizationCLGfx6 8
#define VALUBusyCLGfx6 9
#define SALUBusyCLGfx6 10
#define FetchSizeCLGfx6 11
#define WriteSizeCLGfx6 12
#define CacheHitCLGfx6 13
#define MemUnitBusyCLGfx6 14
#define MemUnitStalledCLGfx6 15
#define WriteUnitStalledCLGfx6 16
#define LDSBankConflictCLGfx6 17

/// Number of public counters for CLGfx6
static const size_t CLGFX6_PUBLIC_COUNTER_COUNT = 18;

/// Array of public counters for CLGfx6
extern const GPACounterDesc CLGFX6_PUBLIC_COUNTERS[CLGFX6_PUBLIC_COUNTER_COUNT];

#endif // _GPA_TESTS_COUNTERS_CLGFX6_
