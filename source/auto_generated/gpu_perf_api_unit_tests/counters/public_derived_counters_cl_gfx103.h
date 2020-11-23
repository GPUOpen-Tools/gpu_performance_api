//==============================================================================
// Copyright (c) 2015-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for CLGFX103 for testing
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef _GPA_TESTS_COUNTERS_PUBLIC_CLGFX103_
#define _GPA_TESTS_COUNTERS_PUBLIC_CLGFX103_

#include "gpa_counter_desc.h"

/// Macros for CLGfx103 Public counter index
#define WavefrontsPublicCLGfx103 0
#define VALUInstsPublicCLGfx103 1
#define SALUInstsPublicCLGfx103 2
#define VFetchInstsPublicCLGfx103 3
#define SFetchInstsPublicCLGfx103 4
#define VWriteInstsPublicCLGfx103 5
#define LDSInstsPublicCLGfx103 6
#define GDSInstsPublicCLGfx103 7
#define VALUUtilizationPublicCLGfx103 8
#define VALUBusyPublicCLGfx103 9
#define SALUBusyPublicCLGfx103 10
#define FetchSizePublicCLGfx103 11
#define WriteSizePublicCLGfx103 12
#define L0CacheHitPublicCLGfx103 13
#define L1CacheHitPublicCLGfx103 14
#define L2CacheHitPublicCLGfx103 15
#define MemUnitBusyPublicCLGfx103 16
#define MemUnitStalledPublicCLGfx103 17
#define WriteUnitStalledPublicCLGfx103 18
#define LDSBankConflictPublicCLGfx103 19

/// Number of public counters for CLGfx103
const size_t CLGFX103_PUBLIC_COUNTER_COUNT = 20;

/// Array of public counters for CLGfx103
extern const GPACounterDesc CLGFX103_PUBLIC_COUNTERS[CLGFX103_PUBLIC_COUNTER_COUNT];

#endif  // _GPA_TESTS_COUNTERS_PUBLIC_CLGFX103_
