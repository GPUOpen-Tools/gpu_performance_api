//==============================================================================
// Copyright (c) 2015-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for CLGFX8 for testing
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef _GPA_TESTS_COUNTERS_PUBLIC_CLGFX8_
#define _GPA_TESTS_COUNTERS_PUBLIC_CLGFX8_

#include "gpa_counter_desc.h"

/// Macros for CLGfx8 Public counter index
#define WavefrontsPublicCLGfx8 0
#define VALUInstsPublicCLGfx8 1
#define SALUInstsPublicCLGfx8 2
#define VFetchInstsPublicCLGfx8 3
#define SFetchInstsPublicCLGfx8 4
#define VWriteInstsPublicCLGfx8 5
#define FlatVMemInstsPublicCLGfx8 6
#define LDSInstsPublicCLGfx8 7
#define FlatLDSInstsPublicCLGfx8 8
#define GDSInstsPublicCLGfx8 9
#define VALUUtilizationPublicCLGfx8 10
#define VALUBusyPublicCLGfx8 11
#define SALUBusyPublicCLGfx8 12
#define FetchSizePublicCLGfx8 13
#define WriteSizePublicCLGfx8 14
#define CacheHitPublicCLGfx8 15
#define MemUnitBusyPublicCLGfx8 16
#define MemUnitStalledPublicCLGfx8 17
#define WriteUnitStalledPublicCLGfx8 18
#define LDSBankConflictPublicCLGfx8 19

/// Number of public counters for CLGfx8
const size_t CLGFX8_PUBLIC_COUNTER_COUNT = 20;

/// Array of public counters for CLGfx8
extern const GPACounterDesc CLGFX8_PUBLIC_COUNTERS[CLGFX8_PUBLIC_COUNTER_COUNT];

#endif  // _GPA_TESTS_COUNTERS_PUBLIC_CLGFX8_
