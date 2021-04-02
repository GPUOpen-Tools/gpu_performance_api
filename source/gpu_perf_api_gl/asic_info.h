//==============================================================================
// Copyright (c) 2006-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Utility routines for retrieving ASIC information
//==============================================================================

#ifndef GPU_PERF_API_GL_ASIC_INFO_H_
#define GPU_PERF_API_GL_ASIC_INFO_H_

#include "limits.h"

#include <map>

#include "TSingleton.h"
#include "DeviceInfo.h"

namespace ogl_utils
{
    /// @brief ASIC type enumeration.
    typedef enum
    {
        kAsicGfx6,    ///< GFX6 Family.
        kAsicGfx7,    ///< GFX7 Family.
        kAsicGfx8,    ///< GFX8 Family.
        kAsicGfx9,    ///< GFX9 Family.
        kAsicGfx10,   ///< GFX10 Family.
        kAsicGfx103,  ///< GFX103 Family.
        kAsicUnknown  ///< Unknown ASIC Family.
    } AsicType;

    /// @brief ASIC identifier enumeration.
    ///
    /// From /stg/ugl/drivers/ugl/src/gl/gs/include/atiasics.h
    /// NOTE: THIS MUST BE UPDATED FOR NEW ASICs
    typedef enum AsicIdEnum
    {
        kAsicIdTahitiP,                 ///< ATI ASIC Id for TAHITI (GFX6).
        kAsicIdPitcairnPm,              ///< ATI ASIC Id for PITCAIRN (GFX6).
        kAsicIdCapeverdeM,              ///< ATI ASIC Id for CAPEVERDE (GFX6).
        kAsicIdOlandM,                  ///< ATI ASIC Id for OLAND (GFX6).
        kAsicIdHainanM,                 ///< ATI ASIC Id for HAINAN (GFX6).
        kAsicIdBonaireM,                ///< ATI ASIC Id for BONAIRE (GFX7).
        kAsicIdSpectre,                 ///< ATI ASIC Id for Spectre (GFX7 Fusion KV1).
        kAsicIdSpooky,                  ///< ATI ASIC Id for Spooky (GFX7 Fusion KV2).
        kAsicIdKalindi,                 ///< ATI ASIC Id for Kalindi (GFX7 Fusion KB).
        kAsicIdHawaiiP,                 ///< ATI ASIC Id for HAWAII (GFX7).
        kAsicIdIcelandM,                ///< ATI ASIC Id for ICELAND (GFX8).
        kAsicIdTongaP,                  ///< ATI ASIC Id for TONGA (GFX8).
        kAsicIdGodavari,                ///< ATI ASIC Id for MULLINS (GFX8 Fusion (Mullins)).
        kAsicIdCarrizo,                 ///< ATI ASIC Id for Carrizo (GFX8 Fusion).
        kAsicIdNolan,                   ///< ATI ASIC Id for Nolan (GFX8.1 APU).
        kAsicIdStoney,                  ///< ATI ASIC Id for Stoney (GFX8.1 APU, almost the same as Nolan).
        kAsicIdAmur,                    ///< ATI ASIC Id for Amur (GFX8.1 APU).
        kAsicIdFijiP,                   ///< ATI ASIC Id for Fiji (GFX8).
        kAsicIdEllesmere,               ///< ATI ASIC Id for Ellesmere (GFX8).
        kAsicIdBaffin,                  ///< ATI ASIC Id for Baffin (GFX8).
        kAsicIdLexa,                    ///< ATI ASIC Id for Lexa (GFX8).
        kAsicIdVegaM,                   ///< ATI ASIC Id for VegaM (GFX8).
        kAsicIdGfx900,                  ///< ATI ASIC Id for GFX900.
        kAsicIdGfx902,                  ///< ATI ASIC Id for GFX902 (APU).
        kAsicIdPlaceholder,             ///< ATI ASIC Id for placeholder APU.
        kAsicIdPlaceholder1,            ///< ATI ASIC Id for placeholder GFX9.
        kAsicIdGfx906,                  ///< ATI ASIC Id for GFX906.
        kAsicIdPlaceholder2,            ///< ATI ASIC Id for placeholder APU.
        kAsicIdPlaceholder3,            ///< ATI ASIC Id for placeholder APU.
        kAsicIdGfx1010,                 ///< ATI ASIC Id for GFX1010.
        kAsicIdGfx1010Lite,             ///< ATI ASIC Id for GFX1010Lite.
        kAsicIdPlaceholder4,            ///< ATI ASIC Id for placeholder GFX10.
        kAsicIdPlaceholder5,            ///< ATI ASIC Id for placeholder GFX10.
        kAsicIdGfx1012,                 ///< ATI ASIC Id for GFX1012.
        kAsicIdGfx1030,                 ///< ATI ASIC Id for GFX10.3.
        kAsicIdGfx1030Lite,             ///< ATI ASIC Id for GFX10.3 Lite.
        kAsicIdPlaceholder6,            ///< ATI ASIC Id for placeholder GFX10.3.
        kAsicIdPlaceholder7,            ///< ATI ASIC Id for placeholder GFX10.3.
        kAsicIdPlaceholder8,            ///< ATI ASIC Id for placeholder GFX10.3.
        kAsicIdPlaceholder9,            ///< ATI ASIC Id for placeholder GFX10.3
        kAsicIdPlaceholder10,           ///< ATI ASIC Id for placeholder GFX10.3.
        kAsicIdUnknown,                 ///< Unknown ASIC
        kAsicIdFirst = kAsicIdTahitiP,  ///< First place holder.
        kAsicIdLast  = kAsicIdUnknown   ///< Last place holder.
    } AsicId;

    /// @brief ASIC Id specific information
    typedef struct _AsicIdInfo
    {
        AsicType         asic_type;          ///< ASIC hardware generation.
        GDT_HW_ASIC_TYPE gdt_asic_type;      ///< GDT hardware ASIC type.
        uint32_t         default_device_id;  ///< default device id.
        bool             is_apu;             ///< Flag indicating the ASIC is APU or not.
    } AsicIdInfo;

    /// @brief ASIC specific information.
    typedef struct _ASICInfo
    {
        static const unsigned int unassigned_asic_info = static_cast<unsigned int>(-1);  ///< value indicating that ASICInfo member is unassigned

        int          driver_version = INT_MAX;               ///< The driver version extracted from GL_VERSION.
        AsicType     asic_type      = kAsicUnknown;          ///< The ASIC family.
        AsicId       asic_id        = kAsicIdUnknown;        ///< The specific ASIC ID.
        unsigned int device_id      = unassigned_asic_info;  ///< The PCIE device id.
        unsigned int device_rev     = unassigned_asic_info;  ///< The PCIE revision id.
        unsigned int num_simd       = unassigned_asic_info;  ///< The number of SIMD units.
        unsigned int num_se         = unassigned_asic_info;  ///< The number of shader engines.
        unsigned int num_sa         = unassigned_asic_info;  ///< The number of shader arrays.
        unsigned int num_cu         = unassigned_asic_info;  ///< The number of compute units.
        unsigned int num_rb         = unassigned_asic_info;  ///< The number of render back-ends (CB / DB).
        unsigned int num_spi        = unassigned_asic_info;  ///< The number of shader processor interpolators.
    } AsicInfo;

    class AsicInfoManager : public TSingleton<AsicInfoManager>
    {
        friend class TSingleton<AsicInfoManager>;

    public:
        /// @brief Get the ASIC info from the driver using GPIN counter.
        ///
        /// @param [out] asic_info AsicInfo struct populated by GPIN group.
        ///
        /// @return Success status on querying GPIN counters.
        /// @retval True on success.
        /// @retval False on failure.
        bool GetAsicInfoFromDriver(AsicInfo& asic_info);

        /// @brief Returns the fall-back ASIC info based on ASIC id.
        ///
        /// @param [in] asic_id ASIC id.
        /// @param [out] gdt_hw_asic_type GDT hardware ASIC type based on ASIC id.
        /// @param [out] default_device_id Device id based on ASIC id.
        ///
        /// @return Success status on identifying ASIC information.
        /// @retval True on success.
        /// @retval False on failure.
        bool GetFallbackAsicInfo(const AsicId& asic_id, GDT_HW_ASIC_TYPE& gdt_hw_asic_type, uint32_t& default_device_id);

    private:
        /// @brief Constructor.
        AsicInfoManager();

        /// @brief Destructor.
        ~AsicInfoManager();

        /// @brief Initializes the ASIC info.
        void InitializeAsicInfo();

        /// @brief Singleton; don't allow copies.
        AsicInfoManager(const AsicInfoManager&) = delete;

        /// @brief Singleton; don't allow assignment.
        void operator=(const AsicInfoManager&) = delete;

        /// @brief Get the corresponding ASIC type for the specified ASIC ID.
        ///
        /// @param asic_id The ASIC ID whose type is needed.
        ///
        /// @return The ASIC type of the specified ASIC ID.
        AsicType GetAsicTypeFromAsicId(AsicId asic_id);

        std::map<AsicId, AsicIdInfo> asic_id_info_map_;          ///< Map containing info of driver defined ASIC Ids.
        bool                         is_asic_info_initialized_;  ///< Flag indicating ASIC info is initialized or not.
    };

}  // namespace ogl_utils

#endif  // GPU_PERF_API_GL_ASIC_INFO_H_
