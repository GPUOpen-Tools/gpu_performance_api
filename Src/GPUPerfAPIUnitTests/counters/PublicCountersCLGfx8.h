//==============================================================================
// Copyright (c) 2015-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  PublicCounterDefinitions for CLGFX8 for testing
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef _GPA_TESTS_COUNTERS_CLGFX8_
#define _GPA_TESTS_COUNTERS_CLGFX8_

#include "GPACounterDesc.h"

/// Macros for CLGfx8 Public counter index
#define WavefrontsCLGfx8 0
#define VALUInstsCLGfx8 1
#define SALUInstsCLGfx8 2
#define VFetchInstsCLGfx8 3
#define SFetchInstsCLGfx8 4
#define VWriteInstsCLGfx8 5
#define FlatVMemInstsCLGfx8 6
#define LDSInstsCLGfx8 7
#define FlatLDSInstsCLGfx8 8
#define GDSInstsCLGfx8 9
#define VALUUtilizationCLGfx8 10
#define VALUBusyCLGfx8 11
#define SALUBusyCLGfx8 12
#define FetchSizeCLGfx8 13
#define WriteSizeCLGfx8 14
#define CacheHitCLGfx8 15
#define MemUnitBusyCLGfx8 16
#define MemUnitStalledCLGfx8 17
#define WriteUnitStalledCLGfx8 18
#define LDSBankConflictCLGfx8 19

/// Number of public counters for CLGfx8
static const size_t CLGFX8_PUBLIC_COUNTER_COUNT = 20;

/// Array of public counters for CLGfx8
extern const GPACounterDesc CLGFX8_PUBLIC_COUNTERS[CLGFX8_PUBLIC_COUNTER_COUNT];

#endif // _GPA_TESTS_COUNTERS_CLGFX8_
