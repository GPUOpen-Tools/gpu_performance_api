//==============================================================================
// Copyright (c) 2015-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for CLGFX10 for testing
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef _GPA_TESTS_COUNTERS_PUBLIC_CLGFX10_
#define _GPA_TESTS_COUNTERS_PUBLIC_CLGFX10_

#include "GPACounterDesc.h"

/// Macros for CLGfx10 Public counter index
#define WavefrontsPublicCLGfx10 0
#define VALUInstsPublicCLGfx10 1
#define SALUInstsPublicCLGfx10 2
#define VFetchInstsPublicCLGfx10 3
#define SFetchInstsPublicCLGfx10 4
#define VWriteInstsPublicCLGfx10 5
#define LDSInstsPublicCLGfx10 6
#define GDSInstsPublicCLGfx10 7
#define VALUUtilizationPublicCLGfx10 8
#define VALUBusyPublicCLGfx10 9
#define SALUBusyPublicCLGfx10 10
#define FetchSizePublicCLGfx10 11
#define WriteSizePublicCLGfx10 12
#define L0CacheHitPublicCLGfx10 13
#define L1CacheHitPublicCLGfx10 14
#define L2CacheHitPublicCLGfx10 15
#define MemUnitBusyPublicCLGfx10 16
#define MemUnitStalledPublicCLGfx10 17
#define WriteUnitStalledPublicCLGfx10 18
#define LDSBankConflictPublicCLGfx10 19

/// Number of public counters for CLGfx10
const size_t CLGFX10_PUBLIC_COUNTER_COUNT = 20;

/// Array of public counters for CLGfx10
extern const GPACounterDesc CLGFX10_PUBLIC_COUNTERS[CLGFX10_PUBLIC_COUNTER_COUNT];

#endif  // _GPA_TESTS_COUNTERS_PUBLIC_CLGFX10_
