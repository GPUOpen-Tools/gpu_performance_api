//==============================================================================
// Copyright (c) 2006-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Utility routines for retrieving ASIC information
//==============================================================================

#ifndef _ASIC_INFO_H_
#define _ASIC_INFO_H_

namespace oglUtils
{
    /// ASIC type enum
    typedef enum
    {
        ASIC_Gfx6,    ///< GFX6 Family
        ASIC_Gfx7,    ///< GFX7 Family
        ASIC_Gfx8,    ///< GFX8 Family
        ASIC_Gfx9,    ///< GFX9 Family
        ASIC_Gfx10,   ///< GFX10 Family
        ASIC_UNKNOWN  ///< unknown asic family
    } ASICType;

    /// !!! From /stg/ugl/drivers/ugl/src/gl/gs/include/atiasics.h !!!
    ///   NOTE: THIS MUST BE UPDATED FOR NEW ASICS
    /// Asic identifier enum
    typedef enum AsicIDEnum
    {
        ASIC_ID_TAHITI_P,                 ///< ATIASICID for TAHITI (GFX6)
        ASIC_ID_PITCAIRN_PM,              ///< ATIASICID for PITCAIRN (GFX6)
        ASIC_ID_CAPEVERDE_M,              ///< ATIASICID for CAPEVERDE (GFX6)
        ASIC_ID_OLAND_M,                  ///< ATIASICID for OLAND (GFX6)
        ASIC_ID_HAINAN_M,                 ///< ATIASICID for HAINAN (GFX6)
        ASIC_ID_BONAIRE_M,                ///< ATIASICID for BONAIRE (GFX7)
        ASIC_ID_SPECTRE,                  ///< ATIASICID for KAVERI (GFX7 Fusion KV1)
        ASIC_ID_SPOOKY,                   ///< ATIASICID for KAVERI (GFX7 Fusion KV2)
        ASIC_ID_KALINDI,                  ///< ATIASICID for KABINI (GFX7 Fusion KB)
        ASIC_ID_HAWAII_P,                 ///< ATIASICID for HAWAII (GFX7)
        ASIC_ID_ICELAND_M,                ///< ATIASICID for ICELAND (GFX8)
        ASIC_ID_TONGA_P,                  ///< ATIASICID for TONGA (GFX8)
        ASIC_ID_GODAVARI,                 ///< ATIASICID for MULLINS (GFX8 Fusion (Mullins))
        ASIC_ID_CARRIZO,                  ///< ATIASICID for Carrizo (GFX8 Fusion)
        ASIC_ID_NOLAN,                    ///< ATIASICID for Nolan (GFX8.1 APU)
        ASIC_ID_STONEY,                   ///< ATIASICID for Stoney (GFX8.1 APU, almost the same as Nolan)
        ASIC_ID_AMUR,                     ///< ATIASICID for Amur (GFX8.1 APU)
        ASIC_ID_FIJI_P,                   ///< ATIASICID for Fiji (GFX8)
        ASIC_ID_ELLESMERE,                ///< ATIASICID for Ellesmere (GFX8)
        ASIC_ID_BAFFIN,                   ///< ATIASICID for Baffin (GFX8)
        ASIC_ID_LEXA,                     ///< ATIASICID for Lexa (GFX8)
        ASIC_ID_VEGAM,                    ///< ATIASICID for VegaM (GFX8)
        ASIC_ID_GFX900,                   ///< ATIASICID for GFX900
        ASIC_ID_GFX902,                   ///< ATIASICID for GFX902 (APU)
        ASIC_ID_PLACEHOLDER,              ///< ATIASICID for placeholder APU
        ASIC_ID_PLACEHOLDER1,             ///< ATIASICID for placeholder GFX9
        ASIC_ID_GFX906,                   ///< ATIASICID for GFX906
        ASIC_ID_PLACEHOLDER2,             ///< ATIASICID for placeholder APU
        ASIC_ID_PLACEHOLDER3,             ///< ATIASICID for placeholder APU
        ASIC_ID_GFX1010,                  ///< ATIASICID for GFX1010
        ASIC_ID_GFX1010LITE,              ///< ATIASICID for GFX1010Lite
        ASIC_ID_PLACEHOLDER4,             ///< ATIASICID for placeholder GFX10
        ASIC_ID_PLACEHOLDER5,             ///< ATIASICID for placeholder GFX10
        ASIC_ID_GFX1012,                  ///< ATIASICID for GFX1012
        ASIC_ID_PLACEHOLDER6,             ///< ATIASICID for placeholder GFX10
        ASIC_ID_PLACEHOLDER7,             ///< ATIASICID for placeholder GFX10
        ASIC_ID_UNKNOWN,                  ///< Unknown Asic
        AsicId_First = ASIC_ID_TAHITI_P,  ///< First place holder
        AsicId_LAST  = ASIC_ID_UNKNOWN    ///< Last place holder
    } AsicID;

    /// Asic-specific information
    typedef struct _ASICInfo
    {
        static const unsigned int s_UNASSIGNED_ASIC_INFO = static_cast<unsigned int>(-1);  ///< value indicating that ASICInfo member is unassigned

        int          m_driverVersion = INT_MAX;                 ///< The driver version extracted from GL_VERSION
        ASICType     m_asicType      = ASIC_UNKNOWN;            ///< The Asic family
        AsicID       m_asicID        = ASIC_ID_UNKNOWN;         ///< The specific Asic ID
        unsigned int m_deviceId      = s_UNASSIGNED_ASIC_INFO;  ///< The PCIE device id
        unsigned int m_deviceRev     = s_UNASSIGNED_ASIC_INFO;  ///< The PCIE revision id
        unsigned int m_numSIMD       = s_UNASSIGNED_ASIC_INFO;  ///< The number of SIMD units
        unsigned int m_numSE         = s_UNASSIGNED_ASIC_INFO;  ///< The number of shader engines
        unsigned int m_numSA         = s_UNASSIGNED_ASIC_INFO;  ///< The number of shader arrays
        unsigned int m_numCU         = s_UNASSIGNED_ASIC_INFO;  ///< The number of compute units
        unsigned int m_numRB         = s_UNASSIGNED_ASIC_INFO;  ///< The number of render backends (CB / DB)
        unsigned int m_numSPI        = s_UNASSIGNED_ASIC_INFO;  ///< The number of shader processor interpolators
    } ASICInfo;

    /// Get the ASIC information
    /// \param[out] asicInfo The structure to fill out with the current ASIC information
    /// \return True if the ASIC information could be identified, false if not.
    bool GetASICInfo(ASICInfo& asicInfo);
}  // namespace oglUtils

#endif  // _ASIC_INFO_H_
