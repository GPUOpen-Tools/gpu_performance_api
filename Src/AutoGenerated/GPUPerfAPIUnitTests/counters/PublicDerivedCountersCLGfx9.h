//==============================================================================
// Copyright (c) 2015-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for CLGFX9 for testing
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef _GPA_TESTS_COUNTERS_PUBLIC_CLGFX9_
#define _GPA_TESTS_COUNTERS_PUBLIC_CLGFX9_

#include "GPACounterDesc.h"

/// Macros for CLGfx9 Public counter index
#define WavefrontsPublicCLGfx9 0
#define VALUInstsPublicCLGfx9 1
#define SALUInstsPublicCLGfx9 2
#define VFetchInstsPublicCLGfx9 3
#define SFetchInstsPublicCLGfx9 4
#define VWriteInstsPublicCLGfx9 5
#define FlatVMemInstsPublicCLGfx9 6
#define LDSInstsPublicCLGfx9 7
#define FlatLDSInstsPublicCLGfx9 8
#define GDSInstsPublicCLGfx9 9
#define VALUUtilizationPublicCLGfx9 10
#define VALUBusyPublicCLGfx9 11
#define SALUBusyPublicCLGfx9 12
#define FetchSizePublicCLGfx9 13
#define WriteSizePublicCLGfx9 14
#define L1CacheHitPublicCLGfx9 15
#define L2CacheHitPublicCLGfx9 16
#define MemUnitBusyPublicCLGfx9 17
#define MemUnitStalledPublicCLGfx9 18
#define WriteUnitStalledPublicCLGfx9 19
#define LDSBankConflictPublicCLGfx9 20

/// Number of public counters for CLGfx9
const size_t CLGFX9_PUBLIC_COUNTER_COUNT = 21;

/// Array of public counters for CLGfx9
extern const GPACounterDesc CLGFX9_PUBLIC_COUNTERS[CLGFX9_PUBLIC_COUNTER_COUNT];

#endif  // _GPA_TESTS_COUNTERS_PUBLIC_CLGFX9_
