//==============================================================================
// Copyright (c) 2015-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for CLGFX7 for testing
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef _GPA_TESTS_COUNTERS_PUBLIC_CLGFX7_
#define _GPA_TESTS_COUNTERS_PUBLIC_CLGFX7_

#include "GPACounterDesc.h"

/// Macros for CLGfx7 Public counter index
#define WavefrontsPublicCLGfx7 0
#define VALUInstsPublicCLGfx7 1
#define SALUInstsPublicCLGfx7 2
#define VFetchInstsPublicCLGfx7 3
#define SFetchInstsPublicCLGfx7 4
#define VWriteInstsPublicCLGfx7 5
#define FlatVMemInstsPublicCLGfx7 6
#define LDSInstsPublicCLGfx7 7
#define FlatLDSInstsPublicCLGfx7 8
#define GDSInstsPublicCLGfx7 9
#define VALUUtilizationPublicCLGfx7 10
#define VALUBusyPublicCLGfx7 11
#define SALUBusyPublicCLGfx7 12
#define FetchSizePublicCLGfx7 13
#define WriteSizePublicCLGfx7 14
#define CacheHitPublicCLGfx7 15
#define MemUnitBusyPublicCLGfx7 16
#define MemUnitStalledPublicCLGfx7 17
#define WriteUnitStalledPublicCLGfx7 18
#define LDSBankConflictPublicCLGfx7 19

/// Number of public counters for CLGfx7
static const size_t CLGFX7_PUBLIC_COUNTER_COUNT = 20;

/// Array of public counters for CLGfx7
extern const GPACounterDesc CLGFX7_PUBLIC_COUNTERS[CLGFX7_PUBLIC_COUNTER_COUNT];

#endif // _GPA_TESTS_COUNTERS_PUBLIC_CLGFX7_
