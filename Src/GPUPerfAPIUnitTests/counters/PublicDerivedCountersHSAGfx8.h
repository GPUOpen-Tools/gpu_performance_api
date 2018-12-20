//==============================================================================
// Copyright (c) 2015-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for HSAGFX8 for testing
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef _GPA_TESTS_COUNTERS_PUBLIC_HSAGFX8_
#define _GPA_TESTS_COUNTERS_PUBLIC_HSAGFX8_

#include "GPACounterDesc.h"

/// Macros for HSAGfx8 Public counter index
#define WavefrontsPublicHSAGfx8 0
#define VALUInstsPublicHSAGfx8 1
#define SALUInstsPublicHSAGfx8 2
#define VFetchInstsPublicHSAGfx8 3
#define SFetchInstsPublicHSAGfx8 4
#define VWriteInstsPublicHSAGfx8 5
#define FlatVMemInstsPublicHSAGfx8 6
#define LDSInstsPublicHSAGfx8 7
#define FlatLDSInstsPublicHSAGfx8 8
#define GDSInstsPublicHSAGfx8 9
#define VALUUtilizationPublicHSAGfx8 10
#define VALUBusyPublicHSAGfx8 11
#define SALUBusyPublicHSAGfx8 12
#define FetchSizePublicHSAGfx8 13
#define WriteSizePublicHSAGfx8 14
#define CacheHitPublicHSAGfx8 15
#define MemUnitBusyPublicHSAGfx8 16
#define MemUnitStalledPublicHSAGfx8 17
#define WriteUnitStalledPublicHSAGfx8 18
#define LDSBankConflictPublicHSAGfx8 19

/// Number of public counters for HSAGfx8
static const size_t HSAGFX8_PUBLIC_COUNTER_COUNT = 20;

/// Array of public counters for HSAGfx8
extern const GPACounterDesc HSAGFX8_PUBLIC_COUNTERS[HSAGFX8_PUBLIC_COUNTER_COUNT];

#endif // _GPA_TESTS_COUNTERS_PUBLIC_HSAGFX8_
