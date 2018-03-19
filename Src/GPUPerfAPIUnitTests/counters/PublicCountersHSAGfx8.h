//==============================================================================
// Copyright (c) 2015-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for HSAGFX8 for testing
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef _GPA_TESTS_COUNTERS_HSAGFX8_
#define _GPA_TESTS_COUNTERS_HSAGFX8_

#include "GPACounterDesc.h"

/// Macros for HSAGfx8 Public counter index
#define WavefrontsHSAGfx8 0
#define VALUInstsHSAGfx8 1
#define SALUInstsHSAGfx8 2
#define VFetchInstsHSAGfx8 3
#define SFetchInstsHSAGfx8 4
#define VWriteInstsHSAGfx8 5
#define FlatVMemInstsHSAGfx8 6
#define LDSInstsHSAGfx8 7
#define FlatLDSInstsHSAGfx8 8
#define GDSInstsHSAGfx8 9
#define VALUUtilizationHSAGfx8 10
#define VALUBusyHSAGfx8 11
#define SALUBusyHSAGfx8 12
#define FetchSizeHSAGfx8 13
#define WriteSizeHSAGfx8 14
#define CacheHitHSAGfx8 15
#define MemUnitBusyHSAGfx8 16
#define MemUnitStalledHSAGfx8 17
#define WriteUnitStalledHSAGfx8 18
#define LDSBankConflictHSAGfx8 19

/// Number of public counters for HSAGfx8
static const size_t HSAGFX8_PUBLIC_COUNTER_COUNT = 20;

/// Array of public counters for HSAGfx8
extern const GPACounterDesc HSAGFX8_PUBLIC_COUNTERS[HSAGFX8_PUBLIC_COUNTER_COUNT];

#endif // _GPA_TESTS_COUNTERS_HSAGFX8_
