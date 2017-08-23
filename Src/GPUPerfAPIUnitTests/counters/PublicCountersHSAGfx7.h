//==============================================================================
// Copyright (c) 2015-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  PublicCounterDefinitions for HSAGFX7 for testing
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef _GPA_TESTS_COUNTERS_HSAGFX7_
#define _GPA_TESTS_COUNTERS_HSAGFX7_

#include "GPACounterDesc.h"

/// Macros for HSAGfx7 Public counter index
#define WavefrontsHSAGfx7 0
#define VALUInstsHSAGfx7 1
#define SALUInstsHSAGfx7 2
#define VFetchInstsHSAGfx7 3
#define SFetchInstsHSAGfx7 4
#define VWriteInstsHSAGfx7 5
#define FlatVMemInstsHSAGfx7 6
#define LDSInstsHSAGfx7 7
#define FlatLDSInstsHSAGfx7 8
#define GDSInstsHSAGfx7 9
#define VALUUtilizationHSAGfx7 10
#define VALUBusyHSAGfx7 11
#define SALUBusyHSAGfx7 12
#define FetchSizeHSAGfx7 13
#define WriteSizeHSAGfx7 14
#define CacheHitHSAGfx7 15
#define MemUnitBusyHSAGfx7 16
#define MemUnitStalledHSAGfx7 17
#define WriteUnitStalledHSAGfx7 18
#define LDSBankConflictHSAGfx7 19

/// Number of public counters for HSAGfx7
static const size_t HSAGFX7_PUBLIC_COUNTER_COUNT = 20;

/// Array of public counters for HSAGfx7
extern const GPACounterDesc HSAGFX7_PUBLIC_COUNTERS[HSAGFX7_PUBLIC_COUNTER_COUNT];

#endif // _GPA_TESTS_COUNTERS_HSAGFX7_
