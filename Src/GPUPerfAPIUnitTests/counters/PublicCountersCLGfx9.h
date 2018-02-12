//==============================================================================
// Copyright (c) 2015-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for CLGFX9 for testing
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef _GPA_TESTS_COUNTERS_CLGFX9_
#define _GPA_TESTS_COUNTERS_CLGFX9_

#include "GPACounterDesc.h"

/// Macros for CLGfx9 Public counter index
#define WavefrontsCLGfx9 0
#define VALUInstsCLGfx9 1
#define SALUInstsCLGfx9 2
#define VFetchInstsCLGfx9 3
#define SFetchInstsCLGfx9 4
#define VWriteInstsCLGfx9 5
#define FlatVMemInstsCLGfx9 6
#define LDSInstsCLGfx9 7
#define FlatLDSInstsCLGfx9 8
#define GDSInstsCLGfx9 9
#define VALUUtilizationCLGfx9 10
#define VALUBusyCLGfx9 11
#define SALUBusyCLGfx9 12
#define FetchSizeCLGfx9 13
#define WriteSizeCLGfx9 14
#define L1CacheHitCLGfx9 15
#define L2CacheHitCLGfx9 16
#define MemUnitBusyCLGfx9 17
#define MemUnitStalledCLGfx9 18
#define WriteUnitStalledCLGfx9 19
#define LDSBankConflictCLGfx9 20

/// Number of public counters for CLGfx9
static const size_t CLGFX9_PUBLIC_COUNTER_COUNT = 21;

/// Array of public counters for CLGfx9
extern const GPACounterDesc CLGFX9_PUBLIC_COUNTERS[CLGFX9_PUBLIC_COUNTER_COUNT];

#endif // _GPA_TESTS_COUNTERS_CLGFX9_
