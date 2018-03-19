//==============================================================================
// Copyright (c) 2015-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for CLGFX7 for testing
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef _GPA_TESTS_COUNTERS_CLGFX7_
#define _GPA_TESTS_COUNTERS_CLGFX7_

#include "GPACounterDesc.h"

/// Macros for CLGfx7 Public counter index
#define WavefrontsCLGfx7 0
#define VALUInstsCLGfx7 1
#define SALUInstsCLGfx7 2
#define VFetchInstsCLGfx7 3
#define SFetchInstsCLGfx7 4
#define VWriteInstsCLGfx7 5
#define FlatVMemInstsCLGfx7 6
#define LDSInstsCLGfx7 7
#define FlatLDSInstsCLGfx7 8
#define GDSInstsCLGfx7 9
#define VALUUtilizationCLGfx7 10
#define VALUBusyCLGfx7 11
#define SALUBusyCLGfx7 12
#define FetchSizeCLGfx7 13
#define WriteSizeCLGfx7 14
#define CacheHitCLGfx7 15
#define MemUnitBusyCLGfx7 16
#define MemUnitStalledCLGfx7 17
#define WriteUnitStalledCLGfx7 18
#define LDSBankConflictCLGfx7 19

/// Number of public counters for CLGfx7
static const size_t CLGFX7_PUBLIC_COUNTER_COUNT = 20;

/// Array of public counters for CLGfx7
extern const GPACounterDesc CLGFX7_PUBLIC_COUNTERS[CLGFX7_PUBLIC_COUNTER_COUNT];

#endif // _GPA_TESTS_COUNTERS_CLGFX7_
