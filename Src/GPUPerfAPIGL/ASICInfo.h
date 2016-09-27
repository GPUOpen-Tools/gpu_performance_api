//==============================================================================
// Copyright (c) 2006-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Utility routines for retreiving ASIC information
//==============================================================================


#ifndef _ASIC_INFO_H_
#define _ASIC_INFO_H_


//=========================================================================================================
/// \ingroup ASICInfo
/// \brief ASIC information structure
//=========================================================================================================
typedef enum
{
    ASIC_R6xx,     ///< R600 Family
    ASIC_R7xx,     ///< R700 Family
    ASIC_R8xx,     ///< R800 Family
    ASIC_R9xx,     ///< R900 Family
    ASIC_Gfx6,     ///< GFX6 Family
    ASIC_Gfx7,     ///< GFX7 Family
    ASIC_Gfx8,     ///< GFX8 Family
    ASIC_UNKNOWN   ///< unknown asic family
} ASICType;

/// !!! From maswp4p1.amd.com:1666/stg/ugl/drivers/ugl/src/gl/gs/include/atiasics.h !!!
///   NOTE: THIS MUST BE UPDATED FOR NEW ASICS
/// Asic identifier enumerant
typedef enum ATIAsicIDEnum
{
    ATIASIC_ID_R600,                    ///< ATIAsicID for R600   // < this is the first enum value in Cat 10.2 (aka GL driver version 9551)
    ATIASIC_ID_RV630,                   ///< ATIAsicID for RV630
    ATIASIC_ID_RV610,                   ///< ATIAsicID for RV610
    ATIASIC_ID_RS780,                   ///< ATIAsicID for RS780
    ATIASIC_ID_RV770,                   ///< ATIAsicID for RV770
    ATIASIC_ID_RV670,                   ///< ATIAsicID for RV670
    ATIASIC_ID_RV730,                   ///< ATIAsicID for RV730
    ATIASIC_ID_RV710,                   ///< ATIAsicID for RV710
    ATIASIC_ID_KONG,                    ///< ATIAsicID for RoadRunner
    ATIASIC_ID_R870,                    ///< ATIAsicID for R870
    ATIASIC_ID_R830,                    ///< ATIAsicID for R830
    ATIASIC_ID_RV740,                   ///< ATIAsicID for RV740
    ATIASIC_ID_REDWOOD,                 ///< ATIAsicID for REDWOOD
    ATIASIC_ID_CEDAR,                   ///< ATIAsicID for CEDAR
    ATIASIC_ID_SUPERSUMO,               ///< ATIASICID for SUPERSUMO
    ATIASIC_ID_SUMO,                    ///< ATIASICID for SUMO
    ATIASIC_ID_WRESTLER,                ///< ATIASICID for WRESTLER
    ATIASIC_ID_CAYMAN,                  ///< ATIAsicID for CAYMAN
    ATIASIC_ID_KAUAI,                   ///< ATIAsicID for KAUAI   this was removed in 14.50 (GL version 13252)
    ATIASIC_ID_BARTS,                   ///< ATIAsicID for BARTS (Evergreen derivative)
    ATIASIC_ID_TURKS,                   ///< ATIAsicID for TURKS (Evergreen derivative)
    ATIASIC_ID_CAICOS,                  ///< ATIAsicID for CAICOS(Evergreen derivative)
    ATIASIC_ID_TAHITI_P,                ///< ATIASICID for TAHITI (GFX6)
    ATIASIC_ID_PITCAIRN_PM,             ///< ATIASICID for PITCAIRN (GFX6)
    ATIASIC_ID_CAPEVERDE_M,             ///< ATIASICID for CAPEVERDE (GFX6)
    ATIASIC_ID_OLAND_M,                 ///< ATIASICID for OLAND (GFX6)
    ATIASIC_ID_HAINAN_M,                ///< ATIASICID for HAINAN (GFX6)
    ATIASIC_ID_DEVASTATOR,              ///< ATIASICID for TRINITY (GFX6 Fusion)
    ATIASIC_ID_SCRAPPER,                ///< ATIASICID for TRINITY (GFX6 Fusion)
    ATIASIC_ID_TIRAN_P,                 ///< ATIASICID for TIRAN (Sea Islands)   this was removed in 14.50  (GL version 13252)
    ATIASIC_ID_BONAIRE_M,               ///< ATIASICID for BONAIRE (GFX7)
    ATIASIC_ID_SPECTRE,                 ///< ATIASICID for KAVERI (GFX7 Fusion KV1)
    ATIASIC_ID_SPOOKY,                  ///< ATIASICID for KAVERI (GFX7 Fusion KV2)
    ATIASIC_ID_KALINDI,                 ///< ATIASICID for KABINI (GFX7 Fusion KB)
    ATIASIC_ID_HAWAII_P,                ///< ATIASICID for HAWAII (GFX7)
    ATIASIC_ID_MAUI_P,                  ///< ATIASICID for MAUI (Sea Islands)   this was removed in 14.50 (GL version 13252)
    ATIASIC_ID_ICELAND_M,               ///< ATIASICID for ICELAND (GFX8)
    ATIASIC_ID_TONGA_P,                 ///< ATIASICID for TONGA (GFX8)
    ATIASIC_ID_GODAVARI,                ///< ATIASICID for MULLINS (GFX8 Fusion (Mullins))
    ATIASIC_ID_CARRIZO,                 ///< ATIASICID for Carrizo (GFX8 Fusion)
    ATIASIC_ID_NOLAN,                   ///< ATIASICID for Nolan (GFX8.1 APU)
    ATIASIC_ID_STONEY,                  ///< ATIASICID for Stoney (GFX8.1 APU, almost the same as Nolan) this was added in 15.20 (GL version 13393)
    ATIASIC_ID_AMUR,                    ///< ATIASICID for Amur (GFX8.1 APU)
    ATIASIC_ID_BERMUDA_P,               ///< ATIASICID for Bermuda (Volcanic Islands)  this was removed in 15.20 (GL version 13393)
    ATIASIC_ID_FIJI_P,                  ///< ATIASICID for Fiji (GFX8)
    ATIASIC_ID_ELLESMERE,               ///< ATIASICID for Ellesmere (GFX8)
    ATIASIC_ID_BAFFIN,                  ///< ATIASICID for Baffin (GFX8)
    ATIASIC_ID_GREENLAND,               ///< ATIASICID for Greenland (GFX8)
    ATIASIC_ID_UNKNOWN,                 ///< Unknown Asic
    ATIAsicId_First = ATIASIC_ID_R600,  ///< First place holder
    ATIAsicId_LAST = ATIASIC_ID_UNKNOWN ///< Last place holder
} ATIAsicID;

/// Asic-specific information
typedef struct
{
    ASICType  eAsicType;        ///< The Asic family
    ATIAsicID eAsicRev;         ///< The specific Asic ID
    unsigned int nNumPipes;     ///< The number of Quad pipes (on older hardware)
    unsigned int nNumZPipes;    ///< The number of Depth/stencil pipes
    unsigned int nNumSIMD;      ///< The number of SIMD units
    unsigned int nNumQuadPipe;  ///< The number of Quad pipes
    unsigned int nNumRB;        ///< The number of render backends (CB / DB)
    unsigned int nNumSPI;       ///< The number of shader processor interpolators
} ASICInfo;

/// Get the ASIC information
/// \param[out] rASICInfo The structure to fill out with the current ASIC information
/// \return True if the ASIC information could be identified, false if not.
bool GetASICInfo(ASICInfo& rASICInfo);

#endif // _ASIC_INFO_H_
