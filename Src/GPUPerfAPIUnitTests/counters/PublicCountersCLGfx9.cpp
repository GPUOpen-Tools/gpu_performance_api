//==============================================================================
// Copyright (c) 2015-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for CLGfx9 for testing
//==============================================================================

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "PublicCountersCLGfx9.h"

const GPACounterDesc CLGFX9_PUBLIC_COUNTERS[CLGFX9_PUBLIC_COUNTER_COUNT] =
{
    {"Wavefronts", "General", "Total wavefronts.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, {0xe8999836,0x489d,0x80a6,{0x8e,0x94,0x2c,0x3e,0xa1,0x91,0xfd,0x58}}},
    {"VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, {0x17c27c10,0x3d5c,0x64c2,{0xe7,0xb4,0x4e,0xe1,0xab,0xdb,0xbb,0x46}}},
    {"SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, {0xe5693881,0x8d63,0x951d,{0x1f,0x4f,0xf9,0xe4,0xc8,0x42,0x36,0xf5}}},
    {"VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, {0x85970f8f,0x0b2c,0x6431,{0x9e,0x52,0x79,0x99,0x23,0x6e,0x6e,0x8a}}},
    {"SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, {0x7d9e4356,0xa8f5,0x04c7,{0xf7,0xa8,0xfe,0x68,0xdc,0x01,0xc4,0x41}}},
    {"VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, {0xd8154a17,0x224d,0x704e,{0x73,0xd2,0xbb,0x5d,0x15,0x0f,0x31,0x96}}},
    {"FlatVMemInsts", "General", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, {0x05e4a953,0xc59a,0xe722,{0x87,0x2b,0xe4,0xbc,0x75,0x26,0xbc,0xee}}},
    {"LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control).  Excludes FLAT instructions that read from or write to LDS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, {0xd38c615e,0x1ae5,0xcfc1,{0xcd,0x3b,0xc5,0xbc,0xbd,0xe4,0xff,0x3c}}},
    {"FlatLDSInsts", "LocalMemory", "The average number of FLAT instructions that read or write to LDS executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, {0x7b648dda,0x917a,0x5d05,{0x49,0xac,0x02,0x89,0x62,0x10,0x36,0x32}}},
    {"GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, {0xc63fc276,0x151e,0x3b88,{0x6e,0xdb,0xa0,0xc9,0x25,0x07,0xaa,0xdb}}},
    {"VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, {0xffea5f90,0x624f,0x67dd,{0x4c,0xa6,0x74,0x91,0x1f,0x4c,0x85,0xd3}}},
    {"VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, {0x51800108,0xe003,0x3c1f,{0xb9,0x2a,0xe2,0x24,0xaa,0xab,0x3c,0x1b}}},
    {"SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, {0xf1d53e7a,0x0182,0x42f8,{0x7d,0x2c,0x60,0x29,0xbf,0xf6,0xbc,0x2d}}},
    {"FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, {0xd91ac445,0xb44f,0xf821,{0x91,0x23,0x9d,0x82,0x9e,0x54,0x4c,0x33}}},
    {"WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, {0xe09d95da,0x2772,0xf7cb,{0x51,0xf5,0x4f,0xad,0x27,0xbb,0x99,0x8b}}},
    {"L1CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, {0x6deaf002,0x3cac,0x2d2d,{0x7b,0x89,0x56,0x6c,0x7a,0x52,0xb0,0x8e}}},
    {"L2CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L2 cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, {0x7507935e,0xed29,0xf169,{0xee,0x27,0x9b,0x0f,0xa9,0xb8,0x8f,0x3c}}},
    {"MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, {0xa1efa380,0x4a72,0xe066,{0xe0,0x6a,0x2a,0xb7,0x1a,0x48,0x85,0x21}}},
    {"MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, {0x465ba54f,0xd250,0x1453,{0x79,0x0a,0x73,0x1b,0x10,0xd2,0x30,0xb1}}},
    {"WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, {0x594ad3ce,0xd1ec,0x10fc,{0x7d,0x59,0x25,0x73,0x8e,0x39,0x7d,0x72}}},
    {"LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, {0xb3387100,0x3d5a,0x3235,{0xe6,0x12,0x58,0xb9,0x41,0x68,0x3e,0xb6}}},
};

