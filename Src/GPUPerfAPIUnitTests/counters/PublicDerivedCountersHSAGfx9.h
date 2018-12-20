//==============================================================================
// Copyright (c) 2015-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for HSAGFX9 for testing
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef _GPA_TESTS_COUNTERS_PUBLIC_HSAGFX9_
#define _GPA_TESTS_COUNTERS_PUBLIC_HSAGFX9_

#include "GPACounterDesc.h"

/// Macros for HSAGfx9 Public counter index
#define WavefrontsPublicHSAGfx9 0
#define VALUInstsPublicHSAGfx9 1
#define SALUInstsPublicHSAGfx9 2
#define VFetchInstsPublicHSAGfx9 3
#define SFetchInstsPublicHSAGfx9 4
#define VWriteInstsPublicHSAGfx9 5
#define FlatVMemInstsPublicHSAGfx9 6
#define LDSInstsPublicHSAGfx9 7
#define FlatLDSInstsPublicHSAGfx9 8
#define GDSInstsPublicHSAGfx9 9
#define VALUUtilizationPublicHSAGfx9 10
#define VALUBusyPublicHSAGfx9 11
#define SALUBusyPublicHSAGfx9 12
#define FetchSizePublicHSAGfx9 13
#define WriteSizePublicHSAGfx9 14
#define L2CacheHitPublicHSAGfx9 15
#define MemUnitBusyPublicHSAGfx9 16
#define MemUnitStalledPublicHSAGfx9 17
#define WriteUnitStalledPublicHSAGfx9 18
#define LDSBankConflictPublicHSAGfx9 19

/// Number of public counters for HSAGfx9
static const size_t HSAGFX9_PUBLIC_COUNTER_COUNT = 20;

/// Array of public counters for HSAGfx9
extern const GPACounterDesc HSAGFX9_PUBLIC_COUNTERS[HSAGFX9_PUBLIC_COUNTER_COUNT];

#endif // _GPA_TESTS_COUNTERS_PUBLIC_HSAGFX9_
