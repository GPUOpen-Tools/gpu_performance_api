//==============================================================================
// Copyright (c) 2015-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for CLGFX6 for testing
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef _GPA_TESTS_COUNTERS_PUBLIC_CLGFX6_
#define _GPA_TESTS_COUNTERS_PUBLIC_CLGFX6_

#include "GPACounterDesc.h"

/// Macros for CLGfx6 Public counter index
#define WavefrontsPublicCLGfx6 0
#define VALUInstsPublicCLGfx6 1
#define SALUInstsPublicCLGfx6 2
#define VFetchInstsPublicCLGfx6 3
#define SFetchInstsPublicCLGfx6 4
#define VWriteInstsPublicCLGfx6 5
#define LDSInstsPublicCLGfx6 6
#define GDSInstsPublicCLGfx6 7
#define VALUUtilizationPublicCLGfx6 8
#define VALUBusyPublicCLGfx6 9
#define SALUBusyPublicCLGfx6 10
#define FetchSizePublicCLGfx6 11
#define WriteSizePublicCLGfx6 12
#define CacheHitPublicCLGfx6 13
#define MemUnitBusyPublicCLGfx6 14
#define MemUnitStalledPublicCLGfx6 15
#define WriteUnitStalledPublicCLGfx6 16
#define LDSBankConflictPublicCLGfx6 17

/// Number of public counters for CLGfx6
static const size_t CLGFX6_PUBLIC_COUNTER_COUNT = 18;

/// Array of public counters for CLGfx6
extern const GPACounterDesc CLGFX6_PUBLIC_COUNTERS[CLGFX6_PUBLIC_COUNTER_COUNT];

#endif // _GPA_TESTS_COUNTERS_PUBLIC_CLGFX6_
