/* Copyright (C) 2017-2026 Advanced Micro Devices, Inc. All rights reserved. */

/**
***************************************************************************************************
* @file  AmdDxExtASICInfo.h
*
* @brief
*    AMD D3D ASIC Info Extension API include file.
***************************************************************************************************
*/

#ifndef _AMDDXEXTASICINFO_H_
#define _AMDDXEXTASICINFO_H_

const unsigned int AmdDxASICInfoMaxGPUCount      = 8;   ///< Maximum GPU Count

/**
***************************************************************************************************
* @brief
*    AmdDxASICInfoChipFamily - Enumerates chip family.
*
***************************************************************************************************
*/
enum AmdDxASICInfoChipFamily
{
    AmdDxChipFamily_Unknown,
    AmdDxChipFamily_GFX6,
    AmdDxChipFamily_GFX7,
    AmdDxChipFamily_GFX8,
    AmdDxChipFamily_GFX9,
    AmdDxChipFamily_GFX10,
    AmdDxChipFamily_GFX11
};

/**
***************************************************************************************************
* @brief
*    AmdDxASICInfoFlags - Structure for ASIC info flags.
*
***************************************************************************************************
*/
union AmdDxASICInfoFlags
{
    struct
    {
        UINT isApu                  :  1;   ///< indicates the ASIC is APU
        UINT reBarEnabled           :  1;   ///< indicates Resize Bar is enabled        (Version 3.1 and above).
        UINT cpuHostApertureEnabled :  1;   ///< indicates CPU host Aperture is enabled (Version 3.1 and above).
        UINT reserved               : 29;
    };
    UINT value;
};

/**
***************************************************************************************************
* @brief
*    AmdDxExtASICInfoHWInfo - Structure for video graphics hardware info.
*
***************************************************************************************************
*/
struct AmdDxASICInfoHWInfo
{
    AmdDxASICInfoChipFamily chipFamily;           ///< Chip family
    UINT                    chipID;               ///< Chip ID
    UINT                    revisionID;           ///< Revision ID
    UINT64                  gpuCounterFrequency;  ///< GPU counter frequency
    UINT64                  coreClockInHz;        ///< Core clock in Hz
    UINT64                  memClockInHz;         ///< Memory clock in Hz
    UINT64                  videoMemSize;         ///< Size of video memory
    UINT                    numShaderEngines;     ///< Total shader engine
    UINT                    numShaderArraysPerSE; ///< Number of shader arrays per shader engine
    UINT                    totalCU;              ///< Total compute unit
    UINT                    numSimdsPerCU;        ///< Number of SIMDs per CU
    UINT                    asicName;             ///< ASIC name enumeration (internal driver-defined)
    UINT                    waveSlotsPerSimd;     ///< Number of wave slots per SIMD
    UINT                    ldsSizePerCU;         ///< LDS size per CU (version 2.1 and above)
    UINT                    numVGPRsPerSIMD;      ///< Number of VGPRs per SIMD (version 2.1 and above)
    UINT                    vgprAllocGranularity; ///< granularity of VGPRs (version 2.1 and above)
    AmdDxASICInfoFlags      flags;                ///< ASIC info flags (version 2.2 and above)
    UINT                    mallSizeInBytes;      ///< Size of total MALL (L3) cache in bytes.
    UINT64                  cpuVisibleVidMemSize; ///< Size of CPU visble VideoMem Size (version 3.1 and above).
    UINT                    reserved[502];        ///< Reserved for further extensions
};

/**
***************************************************************************************************
* @brief
*    AmdDxASICInfo struct - Structure filled by driver to provide video graphics harware and
*    driver info.
*
***************************************************************************************************
*/
struct AmdDxASICInfo
{
    AmdDxASICInfoHWInfo     hwInfo[AmdDxASICInfoMaxGPUCount];  ///< Hardware specific information
    UINT        gpuCount;                                      ///< Number of active GPUs
    UINT        reserved[512];                                 ///< Reserved for further extensions
};

/**
***************************************************************************************************
* @brief
*    AmdDxASICInfoParam struct - Structure filled by the application to pass current extension
*    version and pointer to AmdDxASICInfo structure object.
*
***************************************************************************************************
*/
struct AmdDxASICInfoParam
{
    AmdDxASICInfo*  pASICInfo;                  ///< Pointer to the info object
};

#endif
