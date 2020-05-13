//==============================================================================
// Copyright (c) 2006-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Utility routines for retrieving ASIC information
//==============================================================================

#ifndef _ASIC_INFO_H_
#define _ASIC_INFO_H_

#include <map>
#include <TSingleton.h>
#include "DeviceInfo.h"

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

    /// Asic Id specific information
    typedef struct _AsicIdInfo
    {
        ASICType         asic_type;          ///< asic hardware generation
        GDT_HW_ASIC_TYPE gdt_asic_type;      ///< GDT hardware asic type
        uint32_t         default_device_id;  ///< default device id
        bool             is_apu;             ///< flag indicating the asic is APU or not
    } AsicIdInfo;

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

    class AsicInfoManager : public TSingleton<AsicInfoManager>
    {
        friend class TSingleton<AsicInfoManager>;

    public:

        ///Destructor
        ~AsicInfoManager();

        /// Get the asic info from the driver using GPIN counter
        /// \param[out] asicInfo AsicInfo struct populated by GPIN group
        /// \return false if unable to query GPIN counters, true otherwise
        bool GetAsicInfoFromDriver(ASICInfo& asicInfo);

        /// Returns the fallback Asic info based on asic id
        /// \param[in] asic_id asic id
        /// \param[out] gdt_hw_asic_type gdt hardware asic type based on asic id
        /// \param[out] default_device_id device id based on asic id
        /// \return true if the ASIC information could be identified, false if not.
        bool GetFallbackAsicInfo(const AsicID& asic_id, GDT_HW_ASIC_TYPE& gdt_hw_asic_type, uint32_t& default_device_id);

    private:

        /// Constructor
        AsicInfoManager();

        /// Initializes the asic info
        void InitializeAsicInfo();

        /// Get the corresponding ASIC type for the specified ASIC ID
        /// \param asic_id the ASIC ID whose type is needed
        /// \return the ASIC type of the specified ASIC ID
        ASICType GetASICTypeFromAsicID(AsicID asic_id);

        std::map<AsicID, AsicIdInfo> asic_id_info_map_;          ///< map containing info of driver defined asic Ids
        bool                         is_asic_info_initialized_;  ///< flag indicating asic info is initialized or not
    };

}  // namespace oglUtils

#endif  // _ASIC_INFO_H_
