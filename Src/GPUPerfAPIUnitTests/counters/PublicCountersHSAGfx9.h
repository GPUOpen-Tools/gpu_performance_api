//==============================================================================
// Copyright (c) 2015-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  PublicCounterDefinitions for HSAGFX9 for testing
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef _GPA_TESTS_COUNTERS_HSAGFX9_
#define _GPA_TESTS_COUNTERS_HSAGFX9_

#include "GPACounterDesc.h"

/// Macros for HSAGfx9 Public counter index
#define WavefrontsHSAGfx9 0
#define VALUInstsHSAGfx9 1
#define SALUInstsHSAGfx9 2
#define VFetchInstsHSAGfx9 3
#define SFetchInstsHSAGfx9 4
#define VWriteInstsHSAGfx9 5
#define FlatVMemInstsHSAGfx9 6
#define LDSInstsHSAGfx9 7
#define FlatLDSInstsHSAGfx9 8
#define GDSInstsHSAGfx9 9
#define VALUUtilizationHSAGfx9 10
#define VALUBusyHSAGfx9 11
#define SALUBusyHSAGfx9 12
#define FetchSizeHSAGfx9 13
#define WriteSizeHSAGfx9 14
#define L2CacheHitHSAGfx9 15
#define MemUnitBusyHSAGfx9 16
#define MemUnitStalledHSAGfx9 17
#define WriteUnitStalledHSAGfx9 18
#define LDSBankConflictHSAGfx9 19

/// Number of public counters for HSAGfx9
static const size_t HSAGFX9_PUBLIC_COUNTER_COUNT = 20;

/// Array of public counters for HSAGfx9
extern const GPACounterDesc HSAGFX9_PUBLIC_COUNTERS[HSAGFX9_PUBLIC_COUNTER_COUNT];

#endif // _GPA_TESTS_COUNTERS_HSAGFX9_
