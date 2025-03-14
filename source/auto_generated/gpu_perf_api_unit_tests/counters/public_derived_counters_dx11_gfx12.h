//==============================================================================
// Copyright (c) 2015-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief PublicCounterDefinitions for DX11 GFX12 for testing.
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#ifndef GPA_AUTO_GEN_UNIT_TESTS_COUNTERS_PUBLIC_DX11_GFX12
#define GPA_AUTO_GEN_UNIT_TESTS_COUNTERS_PUBLIC_DX11_GFX12

#include "gpu_perf_api_unit_tests/counters/gpa_counter_desc.h"

/// Macros for DX11Gfx12 Public counter index
// clang-format off
#define DISCRETE_GPUTIME_PUBLIC_DX11_GFX12 0
#define DISCRETE_GPUBUSY_PUBLIC_DX11_GFX12 1
#define DISCRETE_GPUBUSYCYCLES_PUBLIC_DX11_GFX12 2
#define DISCRETE_TESSELLATORBUSY_PUBLIC_DX11_GFX12 3
#define DISCRETE_TESSELLATORBUSYCYCLES_PUBLIC_DX11_GFX12 4
#define DISCRETE_VSGSBUSY_PUBLIC_DX11_GFX12 5
#define DISCRETE_VSGSBUSYCYCLES_PUBLIC_DX11_GFX12 6
#define DISCRETE_VSGSTIME_PUBLIC_DX11_GFX12 7
#define DISCRETE_PRETESSELLATIONBUSY_PUBLIC_DX11_GFX12 8
#define DISCRETE_PRETESSELLATIONBUSYCYCLES_PUBLIC_DX11_GFX12 9
#define DISCRETE_PRETESSELLATIONTIME_PUBLIC_DX11_GFX12 10
#define DISCRETE_POSTTESSELLATIONBUSY_PUBLIC_DX11_GFX12 11
#define DISCRETE_POSTTESSELLATIONBUSYCYCLES_PUBLIC_DX11_GFX12 12
#define DISCRETE_POSTTESSELLATIONTIME_PUBLIC_DX11_GFX12 13
#define DISCRETE_PSBUSY_PUBLIC_DX11_GFX12 14
#define DISCRETE_PSBUSYCYCLES_PUBLIC_DX11_GFX12 15
#define DISCRETE_PSTIME_PUBLIC_DX11_GFX12 16
#define DISCRETE_CSBUSY_PUBLIC_DX11_GFX12 17
#define DISCRETE_CSBUSYCYCLES_PUBLIC_DX11_GFX12 18
#define DISCRETE_CSTIME_PUBLIC_DX11_GFX12 19
#define DISCRETE_VSGSVERTICESIN_PUBLIC_DX11_GFX12 20
#define DISCRETE_VSGSPRIMSIN_PUBLIC_DX11_GFX12 21
#define DISCRETE_PRETESSVERTICESIN_PUBLIC_DX11_GFX12 22
#define DISCRETE_POSTTESSPRIMSOUT_PUBLIC_DX11_GFX12 23
#define DISCRETE_PRIMITIVEASSEMBLYBUSY_PUBLIC_DX11_GFX12 24
#define DISCRETE_PRIMITIVEASSEMBLYBUSYCYCLES_PUBLIC_DX11_GFX12 25
#define DISCRETE_PRIMITIVESIN_PUBLIC_DX11_GFX12 26
#define DISCRETE_CULLEDPRIMS_PUBLIC_DX11_GFX12 27
#define DISCRETE_CLIPPEDPRIMS_PUBLIC_DX11_GFX12 28
#define DISCRETE_PASTALLEDONRASTERIZER_PUBLIC_DX11_GFX12 29
#define DISCRETE_PASTALLEDONRASTERIZERCYCLES_PUBLIC_DX11_GFX12 30
#define DISCRETE_PSPIXELSOUT_PUBLIC_DX11_GFX12 31
#define DISCRETE_PSEXPORTSTALLS_PUBLIC_DX11_GFX12 32
#define DISCRETE_PSEXPORTSTALLSCYCLES_PUBLIC_DX11_GFX12 33
#define DISCRETE_CSTHREADGROUPSLAUNCHED_PUBLIC_DX11_GFX12 34
#define DISCRETE_CSWAVEFRONTSLAUNCHED_PUBLIC_DX11_GFX12 35
#define DISCRETE_CSTHREADSLAUNCHED_PUBLIC_DX11_GFX12 36
#define DISCRETE_CSTHREADGROUPSIZE_PUBLIC_DX11_GFX12 37
#define DISCRETE_CSLDSBANKCONFLICT_PUBLIC_DX11_GFX12 38
#define DISCRETE_CSLDSBANKCONFLICTCYCLES_PUBLIC_DX11_GFX12 39
#define DISCRETE_TEXUNITBUSY_PUBLIC_DX11_GFX12 40
#define DISCRETE_TEXUNITBUSYCYCLES_PUBLIC_DX11_GFX12 41
#define DISCRETE_TEXTRIFILTERINGPCT_PUBLIC_DX11_GFX12 42
#define DISCRETE_TEXTRIFILTERINGCOUNT_PUBLIC_DX11_GFX12 43
#define DISCRETE_NOTEXTRIFILTERINGCOUNT_PUBLIC_DX11_GFX12 44
#define DISCRETE_TEXVOLFILTERINGPCT_PUBLIC_DX11_GFX12 45
#define DISCRETE_TEXVOLFILTERINGCOUNT_PUBLIC_DX11_GFX12 46
#define DISCRETE_NOTEXVOLFILTERINGCOUNT_PUBLIC_DX11_GFX12 47
#define DISCRETE_TEXAVEANISOTROPY_PUBLIC_DX11_GFX12 48
#define DISCRETE_DEPTHSTENCILTESTBUSY_PUBLIC_DX11_GFX12 49
#define DISCRETE_DEPTHSTENCILTESTBUSYCYCLES_PUBLIC_DX11_GFX12 50
#define DISCRETE_HIZQUADSCULLED_PUBLIC_DX11_GFX12 51
#define DISCRETE_HIZQUADSCULLEDCOUNT_PUBLIC_DX11_GFX12 52
#define DISCRETE_HIZQUADSACCEPTEDCOUNT_PUBLIC_DX11_GFX12 53
#define DISCRETE_PREZQUADSCULLED_PUBLIC_DX11_GFX12 54
#define DISCRETE_PREZQUADSCULLEDCOUNT_PUBLIC_DX11_GFX12 55
#define DISCRETE_PREZQUADSSURVIVINGCOUNT_PUBLIC_DX11_GFX12 56
#define DISCRETE_POSTZQUADS_PUBLIC_DX11_GFX12 57
#define DISCRETE_POSTZQUADCOUNT_PUBLIC_DX11_GFX12 58
#define DISCRETE_PREZSAMPLESPASSING_PUBLIC_DX11_GFX12 59
#define DISCRETE_PREZSAMPLESFAILINGS_PUBLIC_DX11_GFX12 60
#define DISCRETE_PREZSAMPLESFAILINGZ_PUBLIC_DX11_GFX12 61
#define DISCRETE_POSTZSAMPLESPASSING_PUBLIC_DX11_GFX12 62
#define DISCRETE_POSTZSAMPLESFAILINGS_PUBLIC_DX11_GFX12 63
#define DISCRETE_POSTZSAMPLESFAILINGZ_PUBLIC_DX11_GFX12 64
#define DISCRETE_ZUNITSTALLED_PUBLIC_DX11_GFX12 65
#define DISCRETE_ZUNITSTALLEDCYCLES_PUBLIC_DX11_GFX12 66
#define DISCRETE_CBMEMREAD_PUBLIC_DX11_GFX12 67
#define DISCRETE_CBMEMWRITTEN_PUBLIC_DX11_GFX12 68
#define DISCRETE_L0CACHEHIT_PUBLIC_DX11_GFX12 69
#define DISCRETE_L0CACHEREQUESTCOUNT_PUBLIC_DX11_GFX12 70
#define DISCRETE_L0CACHEHITCOUNT_PUBLIC_DX11_GFX12 71
#define DISCRETE_L0CACHEMISSCOUNT_PUBLIC_DX11_GFX12 72
#define DISCRETE_L2CACHEHIT_PUBLIC_DX11_GFX12 73
#define DISCRETE_L2CACHEMISS_PUBLIC_DX11_GFX12 74
#define DISCRETE_L2CACHEREQUESTCOUNT_PUBLIC_DX11_GFX12 75
#define DISCRETE_L2CACHEHITCOUNT_PUBLIC_DX11_GFX12 76
#define DISCRETE_L2CACHEMISSCOUNT_PUBLIC_DX11_GFX12 77
#define DISCRETE_L0TAGCONFLICTREADSTALLEDCYCLES_PUBLIC_DX11_GFX12 78
#define DISCRETE_L0TAGCONFLICTWRITESTALLEDCYCLES_PUBLIC_DX11_GFX12 79
#define DISCRETE_L0TAGCONFLICTATOMICSTALLEDCYCLES_PUBLIC_DX11_GFX12 80
#define DISCRETE_FETCHSIZE_PUBLIC_DX11_GFX12 81
#define DISCRETE_WRITESIZE_PUBLIC_DX11_GFX12 82
#define DISCRETE_MEMUNITBUSY_PUBLIC_DX11_GFX12 83
#define DISCRETE_MEMUNITBUSYCYCLES_PUBLIC_DX11_GFX12 84
#define DISCRETE_MEMUNITSTALLED_PUBLIC_DX11_GFX12 85
#define DISCRETE_MEMUNITSTALLEDCYCLES_PUBLIC_DX11_GFX12 86
#define DISCRETE_WRITEUNITSTALLED_PUBLIC_DX11_GFX12 87
#define DISCRETE_WRITEUNITSTALLEDCYCLES_PUBLIC_DX11_GFX12 88

/// Number of public counters for DX11 GFX12 
const size_t kDx11Gfx12PublicCounterCount = 89;

/// Array of public counters for DX11 GFX12 
extern const GpaCounterDesc kDx11Gfx12PublicCounters[kDx11Gfx12PublicCounterCount];

// clang-format on
#endif  // GPA_AUTO_GEN_UNIT_TESTS_COUNTERS_PUBLIC_DX11_GFX12
