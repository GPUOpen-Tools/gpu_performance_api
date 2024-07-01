//==============================================================================
// Copyright (c) 2006-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Utility routines for retrieving ASIC information.
//==============================================================================

#ifndef GPU_PERF_API_GL_ASIC_INFO_H_
#define GPU_PERF_API_GL_ASIC_INFO_H_

#include "limits.h"

#include <map>

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
        kAsicGfx11,   ///< GFX11 Family.
        kAsicUnknown  ///< Unknown ASIC Family.
    } AsicGeneration;

    static const char* kAsicGenerationStrings[] = {"Gfx6", "Gfx7", "Gfx8", "Gfx9", "Gfx10", "Gfx103", "Gfx11", "Unknown"};
    static_assert(sizeof(kAsicGenerationStrings) / sizeof(char*) == (kAsicUnknown + 1), "kAsicGenerationStrings does not have enough entries.");

    /// @brief ASIC identifier enumeration from the UGL driver.
    ///
    /// From /stg/ugl/drivers/ugl/src/gl/gs/include/atiasics.h
    /// NOTE: There are not expected to be additional updates after Placeholder11.
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
        kAsicIdPlaceholder,             ///< ATI ASIC Id for placeholder.
        kAsicIdGfx904,                  ///< ATI ASIC Id for GFX904.
        kAsicIdGfx906,                  ///< ATI ASIC Id for GFX906.
        kAsicIdGfx90C,                  ///< ATI ASIC Id for GFX90C (APU).
        kAsicIdPlaceholder3,            ///< ATI ASIC Id for placeholder APU.
        kAsicIdGfx1010,                 ///< ATI ASIC Id for GFX1010.
        kAsicIdGfx1010Lite,             ///< ATI ASIC Id for GFX1010Lite.
        kAsicIdGfx1011,                 ///< ATI ASIC Id for GFX1011.
        kAsicIdGfx1011Lite,             ///< ATI ASIC Id for GFX1011Lite.
        kAsicIdGfx1012,                 ///< ATI ASIC Id for GFX1012.
        kAsicIdGfx1030,                 ///< ATI ASIC Id for GFX103.
        kAsicIdGfx1030Lite,             ///< ATI ASIC Id for GFX103 Lite.
        kAsicIdPlaceholder6,            ///< ATI ASIC Id for placeholder6.
        kAsicIdGfx1031,                 ///< ATI ASIC Id for GFX1031.
        kAsicIdGfx1032,                 ///< ATI ASIC Id for GFX1032.
        kAsicIdGfx1034,                 ///< ATI ASIC Id for GFX1034.
        kAsicIdGfx1035,                 ///< ATI ASIC Id for GFX1035.
        kAsicIdPlaceholder10,           ///< ATI ASIC Id for placeholder10.
        kAsicIdPlaceholder11,           ///< ATI ASIC Id for placeholder11.
        kAsicIdUnknown,                 ///< Unknown ASIC.
        kAsicIdFirst = kAsicIdTahitiP,  ///< First place holder.
        kAsicIdLast  = kAsicIdUnknown   ///< Last place holder.
    } AsicId;


    // All entries in the device_info GDT_HW_ASIC_TYPE enum should be represented in the AsicRevisionEnum below.
    static_assert(GDT_LAST == 50, "GDT_HW_ASIC_TYPE enum has changed, make sure to add necessary entry for AsicRevision below.");

    /// @brief AsicRevision enumeration from PAL.
    ///
    /// The open source version can be found here: https://github.com/GPUOpen-Drivers/pal/blob/dev/inc/core/palLib.h
    typedef enum AsicRevisionEnum
    {
        kUnknown = 0x00,

        kTahiti    = 0x01,
        kPitcairn  = 0x02,
        kCapeverde = 0x03,
        kOland     = 0x04,
        kHainan    = 0x05,

        kBonaire   = 0x06,
        kHawaii    = 0x07,
        kHawaiiPro = 0x08,

        kKalindi  = 0x0A,
        kGodavari = 0x0B,
        kSpectre  = 0x0C,
        kSpooky   = 0x0D,

        kCarrizo = 0x0E,
        kBristol = 0x0F,
        kStoney  = 0x10,

        kIceland  = 0x11,
        kTonga    = 0x12,
        kTongaPro = kTonga,
        kFiji     = 0x13,

        kPolaris10 = 0x14,
        kPolaris11 = 0x15,
        kPolaris12 = 0x16,
        kPolaris22 = 0x17,

        kVega10 = 0x18,
        kVega12 = 0x19,
        kVega20 = 0x1A,
        kRaven  = 0x1B,
        kRaven2 = 0x1C,
        kRenoir = 0x1D,

        kNavi10       = 0x1F,
        kNavi12       = 0x21,
        kNavi12Lite   = 0x22,
        kNavi14       = 0x23,
        kNavi21       = 0x24,
        kNavi22       = 0x25,
        kNavi23       = 0x26,
        kNavi24       = 0x27,
        kNavi21Lite   = 0x28,
        kGfx1033      = 0x29,
        kPlaceholder6 = 0x2A,
        kNavi14Lite   = 0x2B,
        kGfx1100      = 0x2C,
        kGfx1101      = 0x2D,
        kGfx1102      = 0x2E,
        kGfx1035      = 0x2F,
        kGfx1150      = 0x33,
        kGfx1103      = 0x35,
        kGfx1103B     = 0x38,
        kGfx1103HP1   = 0x39,
        kGfx1103HP2   = 0x3A,
        kAsicRevisionLast
    } AsicRevision;

    /// @brief ASIC Id specific information
    typedef struct _AsicIdInfo
    {
        AsicGeneration   asic_generation;    ///< ASIC hardware generation.
        GDT_HW_ASIC_TYPE gdt_asic_type;      ///< GDT hardware ASIC type.
        uint32_t         default_device_id;  ///< Default device id.
        bool             is_apu;             ///< Flag indicating the ASIC is APU or not.
    } AsicIdInfo;

    /// @brief ASIC specific information.
    typedef struct _ASICInfo
    {
        static const unsigned int unassigned_asic_info = static_cast<unsigned int>(-1);  ///< Value indicating that ASICInfo member is unassigned.

        int            driver_version  = INT_MAX;               ///< The driver version extracted from GL_VERSION.
        AsicGeneration asic_generation = kAsicUnknown;          ///< The ASIC family.
        AsicRevision   asic_revision   = kUnknown;              ///< The specific Asic Revision.
        unsigned int   device_id       = unassigned_asic_info;  ///< The PCIE device id.
        unsigned int   device_rev      = unassigned_asic_info;  ///< The PCIE revision id.
        unsigned int   num_simd        = unassigned_asic_info;  ///< The number of SIMD units.
        unsigned int   num_se          = unassigned_asic_info;  ///< The number of shader engines.
        unsigned int   num_sa_per_se   = unassigned_asic_info;  ///< The number of shader arrays per shader engine.
        unsigned int   num_cu          = unassigned_asic_info;  ///< The number of compute units.
        unsigned int   num_rb          = unassigned_asic_info;  ///< The number of render back-ends (CB / DB).
        unsigned int   num_spi         = unassigned_asic_info;  ///< The number of shader processor interpolators.
    } AsicInfo;

    /// @brief Get the ASIC info from the driver using GPIN counter.
    ///
    /// @param [out] asic_info AsicInfo struct populated by GPIN group.
    ///
    /// @return Success status on querying GPIN counters.
    /// @retval True on success.
    /// @retval False on failure.
    bool GetAsicInfoFromDriver(AsicInfo& asic_info);

    /// @brief Returns the fall-back ASIC info based on ASIC revision.
    ///
    /// @param [in] asic_revision ASIC Revision.
    /// @param [out] gdt_hw_asic_type GDT hardware ASIC type based on ASIC revision.
    /// @param [out] default_device_id Device ID based on ASIC revision.
    ///
    /// @return Success status on identifying ASIC information.
    /// @retval True on success.
    /// @retval False on failure.
    bool GetFallbackAsicInfo(const AsicRevision& asic_revision, GDT_HW_ASIC_TYPE& gdt_hw_asic_type, uint32_t& default_device_id);

    /// @brief Get the corresponding ASIC type for the specified ASIC revision.
    ///
    /// @param asic_revision The ASIC Revision whose type is needed.
    ///
    /// @return The ASIC type of the specified ASIC revision.
    AsicGeneration GetAsicTypeFromAsicRevision(AsicRevision asic_revision);

    /// @brief Get the corresponding AsicRevision for the specified AsicId.
    ///
    /// @param asic_id The ASIC Id whose revision is needed.
    ///
    /// @return The ASIC type of the specified ASIC ID.
    AsicRevision GetAsicRevisionFromAsicId(AsicId asic_id);

    /// @brief Gets the hardcoded asic info for a specified AsicRevision.
    ///
    /// @param asic_revision The ASIC Revision to lookup.
    ///
    /// @return A valid AsicIdInfo struct if the AsicRevision is found; otherwise the asic_type member will be kAsicUnknown.
    AsicIdInfo GetAsicInfoForAsicRevision(AsicRevision asic_revision);

}  // namespace ogl_utils

#endif  // GPU_PERF_API_GL_ASIC_INFO_H_
