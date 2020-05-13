//==============================================================================
// Copyright (c) 2016-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Maintains a set of hardware counters
//==============================================================================

#ifndef _GPA_HARDWARE_COUNTERS_H_
#define _GPA_HARDWARE_COUNTERS_H_

#ifdef AMDT_INTERNAL
#include <unordered_map>
#endif

#include <sstream>
#include "gpa_counter.h"
#include "gpa_common_defs.h"
#include "gpa_split_counters_interfaces.h"
#include "gpa_counter_scheduler_interface.h"

/// Struct to describe a hardware counter
struct GPA_HardwareCounterDescExt
{
    gpa_uint32               m_groupIndex;        ///< index of group containing this counter
    gpa_uint32               m_groupIdDriver;     ///< group ID according to the driver
    gpa_uint32               m_counterIdDriver;   ///< counter ID according to the driver
    GPA_HardwareCounterDesc* m_pHardwareCounter;  ///< the internal counter
};

/// Maintains a set of hardware counters
class GPA_HardwareCounters
{
public:
    enum GpaInternalHardwareBlock
    {
        GPA_INTERNAL_HW_BLOCK_CPF = 0,                                 ///< The Gpa hardware block is CPF
        GPA_INTERNAL_HW_BLOCK_IA,                                      ///< The Gpa hardware block is IA
        GPA_INTERNAL_HW_BLOCK_VGT,                                     ///< The Gpa hardware block is VGT
        GPA_INTERNAL_HW_BLOCK_PA,                                      ///< The Gpa hardware block is PA
        GPA_INTERNAL_HW_BLOCK_SC,                                      ///< The Gpa hardware block is SC
        GPA_INTERNAL_HW_BLOCK_SPI,                                     ///< The Gpa hardware block is SPI
        GPA_INTERNAL_HW_BLOCK_SQ,                                      ///< The Gpa hardware block is SQ
        GPA_INTERNAL_HW_BLOCK_SX,                                      ///< The Gpa hardware block is SX
        GPA_INTERNAL_HW_BLOCK_TA,                                      ///< The Gpa hardware block is TA
        GPA_INTERNAL_HW_BLOCK_TD,                                      ///< The Gpa hardware block is TD
        GPA_INTERNAL_HW_BLOCK_TCP,                                     ///< The Gpa hardware block is TCP
        GPA_INTERNAL_HW_BLOCK_TCC,                                     ///< The Gpa hardware block is TCC
        GPA_INTERNAL_HW_BLOCK_TCA,                                     ///< The Gpa hardware block is TCA
        GPA_INTERNAL_HW_BLOCK_DB,                                      ///< The Gpa hardware block is DB
        GPA_INTERNAL_HW_BLOCK_CB,                                      ///< The Gpa hardware block is CB
        GPA_INTERNAL_HW_BLOCK_GDS,                                     ///< The Gpa hardware block is GDS
        GPA_INTERNAL_HW_BLOCK_SRBM,                                    ///< The Gpa hardware block is SRBM
        GPA_INTERNAL_HW_BLOCK_GRBM,                                    ///< The Gpa hardware block is GRBM
        GPA_INTERNAL_HW_BLOCK_GRBMSE,                                  ///< The Gpa hardware block is GRBMSE
        GPA_INTERNAL_HW_BLOCK_RLC,                                     ///< The Gpa hardware block is RLC
        GPA_INTERNAL_HW_BLOCK_DMA,                                     ///< The Gpa hardware block is DMA
        GPA_INTERNAL_HW_BLOCK_MC,                                      ///< The Gpa hardware block is MC
        GPA_INTERNAL_HW_BLOCK_CPG,                                     ///< The Gpa hardware block is CPG
        GPA_INTERNAL_HW_BLOCK_CPC,                                     ///< The Gpa hardware block is CPC
        GPA_INTERNAL_HW_BLOCK_WD,                                      ///< The Gpa hardware block is WD
        GPA_INTERNAL_HW_BLOCK_TCS,                                     ///< The Gpa hardware block is TCS
        GPA_INTERNAL_HW_BLOCK_ATC,                                     ///< The Gpa hardware block is ATC
        GPA_INTERNAL_HW_BLOCK_ATCL2,                                   ///< The Gpa hardware block is ATCL2
        GPA_INTERNAL_HW_BLOCK_MCVML2,                                  ///< The Gpa hardware block is MCVML2
        GPA_INTERNAL_HW_BLOCK_EA,                                      ///< The Gpa hardware block is EA
        GPA_INTERNAL_HW_BLOCK_RPB,                                     ///< The Gpa hardware block is RPB
        GPA_INTERNAL_HW_BLOCK_RMI,                                     ///< The Gpa hardware block is RMI
        GPA_INTERNAL_HW_BLOCK_UMCCH,                                   ///< The Gpa hardware block is UMCCH
        GPA_INTERNAL_HW_BLOCK_GE,                                      ///< The Gpa hardware block is GE
        GPA_INTERNAL_HW_BLOCK_GL1A,                                    ///< The Gpa hardware block is GL1A
        GPA_INTERNAL_HW_BLOCK_GL1C,                                    ///< The Gpa hardware block is GL1C
        GPA_INTERNAL_HW_BLOCK_GL1CG,                                   ///< The Gpa hardware block is GL1CG
        GPA_INTERNAL_HW_BLOCK_GL2A,                                    ///< The Gpa hardware block is GL2A
        GPA_INTERNAL_HW_BLOCK_GL2C,                                    ///< The Gpa hardware block is GL2C
        GPA_INTERNAL_HW_BLOCK_CHA,                                     ///< The Gpa hardware block is CHA
        GPA_INTERNAL_HW_BLOCK_CHC,                                     ///< The Gpa hardware block is CHC
        GPA_INTERNAL_HW_BLOCK_CHCG,                                    ///< The Gpa hardware block is CHCG
        GPA_INTERNAL_HW_BLOCK_GUS,                                     ///< The Gpa hardware block is GUS
        GPA_INTERNAL_HW_BLOCK_GCR,                                     ///< The Gpa hardware block is GCR
        GPA_INTERNAL_HW_BLOCK_PH,                                      ///< The Gpa hardware block is PH
        GPA_INTERNAL_HW_BLOCK_UTCL1,                                   ///< The Gpa hardware block is UTCL1
        GPA_INTERNAL_HQ_BLOCK_SQ_FIRST,                                ///< The Gpa hardware block is SQ
        GPA_INTERNAL_HW_BLOCK_SQ_PS = GPA_INTERNAL_HQ_BLOCK_SQ_FIRST,  ///< The Gpa hardware block is SQ_PS
        GPA_INTERNAL_HW_BLOCK_SQ_VS,                                   ///< The Gpa hardware block is SQ_VS
        GPA_INTERNAL_HW_BLOCK_SQ_GS,                                   ///< The Gpa hardware block is SQ_GS
        GPA_INTERNAL_HW_BLOCK_SQ_ES,                                   ///< The Gpa hardware block is SQ_ES
        GPA_INTERNAL_HW_BLOCK_SQ_HS,                                   ///< The Gpa hardware block is SQ_HS
        GPA_INTERNAL_HW_BLOCK_SQ_LS,                                   ///< The Gpa hardware block is SQ_LS
        GPA_INTERNAL_HW_BLOCK_SQ_CS,                                   ///< The Gpa hardware block is SQ_CS
        GPA_INTERNAL_HW_BLOCK_COUNT,                                   ///< Count
    };

    /// Initializes an instance of the GPA_HardwareCounters class.
    GPA_HardwareCounters()
    {
        if (hardware_block_string_.empty())
        {
            static_assert(GPA_HW_BLOCK_CPF == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_CPF), "Mismatched block");
            static_assert(GPA_HW_BLOCK_IA == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_IA), "Mismatched block");
            static_assert(GPA_HW_BLOCK_VGT == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_VGT), "Mismatched block");
            static_assert(GPA_HW_BLOCK_PA == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_PA), "Mismatched block");
            static_assert(GPA_HW_BLOCK_SC == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_SC), "Mismatched block");
            static_assert(GPA_HW_BLOCK_SPI == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_SPI), "Mismatched block");
            static_assert(GPA_HW_BLOCK_SQ == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_SQ), "Mismatched block");
            static_assert(GPA_HW_BLOCK_SX == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_SX), "Mismatched block");
            static_assert(GPA_HW_BLOCK_TA == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_TA), "Mismatched block");
            static_assert(GPA_HW_BLOCK_TD == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_TD), "Mismatched block");
            static_assert(GPA_HW_BLOCK_TCP == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_TCP), "Mismatched block");
            static_assert(GPA_HW_BLOCK_TCC == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_TCC), "Mismatched block");
            static_assert(GPA_HW_BLOCK_TCA == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_TCA), "Mismatched block");
            static_assert(GPA_HW_BLOCK_DB == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_DB), "Mismatched block");
            static_assert(GPA_HW_BLOCK_CB == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_CB), "Mismatched block");
            static_assert(GPA_HW_BLOCK_GDS == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_GDS), "Mismatched block");
            static_assert(GPA_HW_BLOCK_SRBM == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_SRBM), "Mismatched block");
            static_assert(GPA_HW_BLOCK_GRBM == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_GRBM), "Mismatched block");
            static_assert(GPA_HW_BLOCK_GRBMSE == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_GRBMSE), "Mismatched block");
            static_assert(GPA_HW_BLOCK_RLC == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_RLC), "Mismatched block");
            static_assert(GPA_HW_BLOCK_DMA == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_DMA), "Mismatched block");
            static_assert(GPA_HW_BLOCK_MC == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_MC), "Mismatched block");
            static_assert(GPA_HW_BLOCK_CPG == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_CPG), "Mismatched block");
            static_assert(GPA_HW_BLOCK_CPC == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_CPC), "Mismatched block");
            static_assert(GPA_HW_BLOCK_WD == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_WD), "Mismatched block");
            static_assert(GPA_HW_BLOCK_TCS == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_TCS), "Mismatched block");
            static_assert(GPA_HW_BLOCK_ATC == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_ATC), "Mismatched block");
            static_assert(GPA_HW_BLOCK_ATCL2 == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_ATCL2), "Mismatched block");
            static_assert(GPA_HW_BLOCK_MCVML2 == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_MCVML2), "Mismatched block");
            static_assert(GPA_HW_BLOCK_EA == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_EA), "Mismatched block");
            static_assert(GPA_HW_BLOCK_RPB == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_RPB), "Mismatched block");
            static_assert(GPA_HW_BLOCK_RMI == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_RMI), "Mismatched block");
            static_assert(GPA_HW_BLOCK_UMCCH == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_UMCCH), "Mismatched block");
            static_assert(GPA_HW_BLOCK_GE == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_GE), "Mismatched block");
            static_assert(GPA_HW_BLOCK_GL1A == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_GL1A), "Mismatched block");
            static_assert(GPA_HW_BLOCK_GL1C == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_GL1C), "Mismatched block");
            static_assert(GPA_HW_BLOCK_GL1CG == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_GL1CG), "Mismatched block");
            static_assert(GPA_HW_BLOCK_GL2A == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_GL2A), "Mismatched block");
            static_assert(GPA_HW_BLOCK_GL2C == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_GL2C), "Mismatched block");
            static_assert(GPA_HW_BLOCK_CHA == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_CHA), "Mismatched block");
            static_assert(GPA_HW_BLOCK_CHC == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_CHC), "Mismatched block");
            static_assert(GPA_HW_BLOCK_CHCG == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_CHCG), "Mismatched block");
            static_assert(GPA_HW_BLOCK_GUS == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_GUS), "Mismatched block");
            static_assert(GPA_HW_BLOCK_GCR == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_GCR), "Mismatched block");
            static_assert(GPA_HW_BLOCK_PH == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_PH), "Mismatched block");
            static_assert(GPA_HW_BLOCK_UTCL1 == static_cast<GpaHwBlock>(GPA_INTERNAL_HW_BLOCK_UTCL1), "Mismatched block");
            static_assert(GPA_HW_BLOCK_COUNT == static_cast<GpaHwBlock>(GPA_INTERNAL_HQ_BLOCK_SQ_FIRST), "Mismatched block");

            hardware_block_string_ = {GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_CPF, "CPF"),       GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_IA, "IA"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_VGT, "VGT"),       GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_PA, "PA_SU"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_SC, "PA_SC"),      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_SPI, "SPI"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_SQ, "SQ"),         GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_SX, "SX"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_TA, "TA"),         GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_TD, "TD"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_TCP, "TCP"),       GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_TCC, "TCC"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_TCA, "TCA"),       GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_DB, "DB"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_CB, "CB"),         GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_GDS, "GDS"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_SRBM, "SRBM"),     GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_GRBM, "GRBM"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_GRBMSE, "GRBMSE"), GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_RLC, "RLC"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_DMA, "DMA"),       GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_MC, "MC"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_CPG, "CPG"),       GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_CPC, "CPC"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_WD, "WD"),         GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_TCS, "TCS"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_ATC, "ATC"),       GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_ATCL2, "ATCL2"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_MCVML2, "MCVML2"), GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_EA, "GCEA"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_RPB, "RPB"),       GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_RMI, "RMI"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_UMCCH, "UMC"),     GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_GE, "GE"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_GL1A, "GL1A"),     GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_GL1C, "GL1C"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_GL1CG, "GL1CG"),   GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_GL2A, "GL2A"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_GL2C, "GL2C"),     GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_CHA, "CHA"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_CHC, "CHC"),       GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_CHCG, "CHCG"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_GUS, "GUS"),       GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_GCR, "GCR"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_PH, "PA_PH"),      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_UTCL1, "UTCL1"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_SQ_PS, "SQ_PS"),   GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_SQ_VS, "SQ_VS"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_SQ_GS, "SQ_GS"),   GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_SQ_ES, "SQ_ES"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_SQ_HS, "SQ_HS"),   GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_SQ_LS, "SQ_LS"),
                                      GPA_ENUM_STRING_VAL(GPA_INTERNAL_HW_BLOCK_SQ_CS, "SQ_CS")};
        }

        Clear();
    }

    /// Destructor
    virtual ~GPA_HardwareCounters() = default;

    /// Clears all counter data
    void Clear()
    {
        m_currentGroupUsedCounts.clear();
        m_counters.clear();
        m_ppCounterGroupArray                       = nullptr;
        m_ppHardwareExposedCounter                  = nullptr;
        m_pGroups                                   = nullptr;
        m_groupCount                                = 0;
        m_pAdditionalGroups                         = nullptr;
        m_additionalGroupCount                      = 0;
        m_pSQCounterGroups                          = nullptr;
        m_sqGroupCount                              = 0;
        m_gpuTimeBottomToBottomDurationCounterIndex = static_cast<unsigned int>(-1);
        m_gpuTimeBottomToBottomStartCounterIndex    = static_cast<unsigned int>(-1);
        m_gpuTimeBottomToBottomEndCounterIndex      = static_cast<unsigned int>(-1);
        m_gpuTimeTopToBottomDurationCounterIndex    = static_cast<unsigned int>(-1);
        m_gpuTimeTopToBottomStartCounterIndex       = static_cast<unsigned int>(-1);
        m_gpuTimeTopToBottomEndCounterIndex         = static_cast<unsigned int>(-1);
        m_countersGenerated                         = false;
        m_pIsolatedGroups                           = nullptr;
        m_isolatedGroupCount                        = 0;

        m_ppHardwareExposedCounter         = nullptr;
        m_pHardwareExposedCounterGroups    = nullptr;
        m_hardwareExposedCounterGroupCount = 0;
        m_hardwareExposedCounters.clear();
        m_hardwareExposedCounterInternalIndices.clear();
        m_hardwareExposedCountersGenerated = false;
    }

    /// Obtains the number of hardware counters
    /// \return the number of hardware counters
    gpa_uint32 GetNumCounters() const
    {
        return static_cast<gpa_uint32>(m_counters.size());
    }

    /// Obtains the number of hardware exposed counters
    /// \return the number of hardware exposed counters
    gpa_uint32 GetNumHardwareExposedCounters() const
    {
        return static_cast<gpa_uint32>(m_hardwareExposedCounters.size());
    }

    /// Obtains the index of the counter
    /// \param[in] gpa_hardware_block Gpa hardware block
    /// \param[in] block_instance block instance
    /// \param[in] block_event_id event id in the block
    /// \param[in] sq_shader_mask SQ shader mask
    /// \param[out] counter_index index of the counter
    /// \return true if counter is found otherwise false
    bool GetIndex(const GpaHwBlock&    gpa_hardware_block,
                  const gpa_uint32&    block_instance,
                  const gpa_uint32&    block_event_id,
                  const GpaShaderMask& sq_shader_mask,
                  gpa_uint32*          counter_index) const
    {
        auto update_hardware_info_in_cache = [&](GpaInternalHardwareBlock gpa_internal_hardware_block) -> bool {

            if (gpa_hw_block_hardware_block_group_cache_.empty())
            {
                gpa_hw_block_hardware_block_group_cache_.resize(GpaInternalHardwareBlock::GPA_INTERNAL_HW_BLOCK_COUNT);
            }

            if (block_instance_counters_index_cache_.empty())
            {
                block_instance_counters_index_cache_.resize(GpaInternalHardwareBlock::GPA_INTERNAL_HW_BLOCK_COUNT);
            }
            else if (GpaInternalHardwareBlock::GPA_INTERNAL_HW_BLOCK_COUNT > gpa_internal_hardware_block)
            {
                assert(gpa_hw_block_hardware_block_group_cache_.size() > static_cast<size_t>(gpa_internal_hardware_block));
                if (!block_instance_counters_index_cache_[gpa_internal_hardware_block].empty())
                {
                    // we've already found this block
                    return true;
                }
            }

            bool       found_block    = false;
            gpa_uint32 group_iter     = 0u;
            gpa_uint32 counter_offset = 0u;

            std::string hardware_block_string = hardware_block_string_[gpa_internal_hardware_block];
            std::string current_block_string;

            while (!found_block && group_iter < m_groupCount)
            {
                current_block_string.clear();
                current_block_string = std::string(m_pGroups[group_iter].m_pName);

                if (current_block_string.find(hardware_block_string) != std::string::npos)
                {
                    found_block                                                       = true;
                    auto                                 instance_iter                = 0u;
                    auto                                 group_id_with_first_instance = group_iter;
                    std::vector<BlockCounterIndexOffset> block_instance_counter_offsets;
                    bool                                 updated_all_instance = false;
                    do
                    {
                        block_instance_counter_offsets.push_back(counter_offset);
                        counter_offset += m_pGroups[group_iter].m_numCounters;
                        ++instance_iter;
                        ++group_iter;
                        current_block_string.clear();
                        current_block_string = std::string(m_pGroups[group_iter].m_pName);

                        if (hardware_block_string.find("SQ") != std::string::npos ||
                            hardware_block_string.find("GL1C") != std::string::npos)
                        {
                            std::stringstream hardware_block_str_with_instance;
                            hardware_block_str_with_instance << hardware_block_string.c_str() << instance_iter;

                            if (hardware_block_str_with_instance.str().find(current_block_string) == std::string::npos)
                            {
                                updated_all_instance = true;
                            }
                        }
                        else if (current_block_string.find(hardware_block_string) == std::string::npos)
                        {
                            updated_all_instance = true;
                        }

                    } while (!updated_all_instance);

                    block_instance_counters_index_cache_[gpa_internal_hardware_block]     = block_instance_counter_offsets;
                    gpa_hw_block_hardware_block_group_cache_[gpa_internal_hardware_block] = group_id_with_first_instance;
                }

                counter_offset += m_pGroups[group_iter].m_numCounters;
                ++group_iter;
            }

            return found_block;
        };

        bool valid_counter_query = false;

        GpaInternalHardwareBlock gpa_internal_hardware_block_mapped;

        if (GPA_HW_BLOCK_SQ == gpa_hardware_block)
        {
            GpaInternalHardwareBlock sq_internal_block = static_cast<GpaInternalHardwareBlock>(GPA_HW_BLOCK_SQ);

            switch (sq_shader_mask)
            {
            case GPA_SHADER_MASK_CS:
                sq_internal_block = GPA_INTERNAL_HW_BLOCK_SQ_CS;
                break;
            case GPA_SHADER_MASK_PS:
                sq_internal_block = GPA_INTERNAL_HW_BLOCK_SQ_PS;
                break;
            case GPA_SHADER_MASK_VS:
                sq_internal_block = GPA_INTERNAL_HW_BLOCK_SQ_VS;
                break;
            case GPA_SHADER_MASK_GS:
                sq_internal_block = GPA_INTERNAL_HW_BLOCK_SQ_GS;
                break;
            case GPA_SHADER_MASK_ES:
                sq_internal_block = GPA_INTERNAL_HW_BLOCK_SQ_ES;
                break;
            case GPA_SHADER_MASK_HS:
                sq_internal_block = GPA_INTERNAL_HW_BLOCK_SQ_HS;
                break;
            case GPA_SHADER_MASK_LS:
                sq_internal_block = GPA_INTERNAL_HW_BLOCK_SQ_LS;
                break;
            case GPA_SHADER_MASK_ALL:
                break;
            default:;
            }

            gpa_internal_hardware_block_mapped = sq_internal_block;
        }
        else
        {
            gpa_internal_hardware_block_mapped = static_cast<GpaInternalHardwareBlock>(gpa_hardware_block);
        }

        if (update_hardware_info_in_cache(gpa_internal_hardware_block_mapped))
        {
            if (gpa_internal_hardware_block_mapped < static_cast<GpaInternalHardwareBlock>(block_instance_counters_index_cache_.size()) &&
                gpa_internal_hardware_block_mapped < static_cast<GpaInternalHardwareBlock>(gpa_hw_block_hardware_block_group_cache_.size()))
            {
                auto block_offset = block_instance_counters_index_cache_[gpa_internal_hardware_block_mapped];
                if (!block_offset.empty())
                {
                    bool valid_instance = block_instance < block_offset.size();
                    if (valid_instance)
                    {
                        auto hardware_internal_group = gpa_hw_block_hardware_block_group_cache_[gpa_internal_hardware_block_mapped];
                        bool valid_event             = block_event_id < m_pGroups[hardware_internal_group].m_numCounters;

                        if (valid_event)
                        {
                            *counter_index      = block_offset[block_instance] + block_event_id;
                            valid_counter_query = true;
                        }
                    }
                }
            }
        }

        return valid_counter_query;
    }

    /// Gets the name of the specified counter
    /// \param index the index of the counter whose name is needed
    /// \return the name of the specified counter
    const char* GetCounterName(gpa_uint32 index) const
    {
#ifdef AMDT_INTERNAL
        if (0 < m_alternateNameMap.count(index))
        {
            return m_alternateNameMap.at(index).c_str();
        }
#endif
        return m_counters[index].m_pHardwareCounter->m_pName;
    }

    /// Gets the name of the specified hardware exposed counter
    /// \param index the index of the counter whose name is needed
    /// \return the name of the specified counter
    const char* GetHardwareExposedCounterName(gpa_uint32 index) const
    {
        return GetCounterName(GetHardwareExposedCounterInternalIndex(index));
    }

    bool GetHardwareExposedCounterIndex(const gpa_uint32& internal_hardware_index, gpa_uint32& exposed_counter_index) const
    {
        auto found = std::find(m_hardwareExposedCounterInternalIndices.cbegin(), m_hardwareExposedCounterInternalIndices.cend(), internal_hardware_index);

        if (found != m_hardwareExposedCounterInternalIndices.end())
        {
            exposed_counter_index = static_cast<gpa_uint32>(found - m_hardwareExposedCounterInternalIndices.cbegin());
            return true;
        }

        return false;
    }

    /// Gets the group (hw block) of the specified counter
    /// \param index the index of the counter whose group is needed
    /// \return the group name of the specified counter
    const char* GetCounterGroup(gpa_uint32 index) const
    {
        if (m_counters[index].m_groupIndex < m_groupCount)
        {
            return m_pGroups[m_counters[index].m_groupIndex].m_pName;
        }
        else
        {
            gpa_uint32 additionalGroupIndex = m_counters[index].m_groupIndex - m_groupCount;

            if (additionalGroupIndex < m_additionalGroupCount)
            {
                return m_pAdditionalGroups[additionalGroupIndex].m_pName;
            }
        }

        return nullptr;
    }

    void GetHardwareBlock(const gpa_uint32& group, GpaHwBlock& gpa_hw_block, GpaShaderMask& gpa_shader_mask) const
    {
        std::string group_name(m_pGroups[group].m_pName);

        GpaInternalHardwareBlock internal_hw_block = GPA_INTERNAL_HW_BLOCK_COUNT;
        bool                     found             = false;

        for (auto block_iter = hardware_block_string_.cbegin(); block_iter != hardware_block_string_.cend(); ++block_iter)
        {
            if (group_name.find(*block_iter) != std::string::npos)
            {
                internal_hw_block = static_cast<GpaInternalHardwareBlock>(block_iter - hardware_block_string_.cbegin());
                found             = true;
                break;
            }
        }

        if (found)
        {
            if (internal_hw_block >= GPA_INTERNAL_HQ_BLOCK_SQ_FIRST)
            {
                static_assert((GPA_INTERNAL_HW_BLOCK_SQ_PS - GPA_HW_BLOCK_COUNT) == GPA_SHADER_MASK_PS, "");
                static_assert((GPA_INTERNAL_HW_BLOCK_SQ_VS - GPA_HW_BLOCK_COUNT) == GPA_SHADER_MASK_VS, "");
                static_assert((GPA_INTERNAL_HW_BLOCK_SQ_GS - GPA_HW_BLOCK_COUNT) == GPA_SHADER_MASK_GS, "");
                static_assert((GPA_INTERNAL_HW_BLOCK_SQ_ES - GPA_HW_BLOCK_COUNT) == GPA_SHADER_MASK_ES, "");
                static_assert((GPA_INTERNAL_HW_BLOCK_SQ_HS - GPA_HW_BLOCK_COUNT) == GPA_SHADER_MASK_HS, "");
                static_assert((GPA_INTERNAL_HW_BLOCK_SQ_LS - GPA_HW_BLOCK_COUNT) == GPA_SHADER_MASK_LS, "");
                static_assert((GPA_INTERNAL_HW_BLOCK_SQ_CS - GPA_HW_BLOCK_COUNT) == GPA_SHADER_MASK_CS, "");

                gpa_hw_block    = GPA_HW_BLOCK_SQ;
                gpa_shader_mask = static_cast<GpaShaderMask>(internal_hw_block - GPA_INTERNAL_HQ_BLOCK_SQ_FIRST);
            }
            else
            {
                gpa_hw_block = static_cast<GpaHwBlock>(internal_hw_block);
            }
        }
    }

    /// Gets the group (hw block) of the specified counter
    /// \param index the index of the counter whose group is needed
    /// \return the group name of the specified counter
    const char* GetHardwareExposedCounterGroup(gpa_uint32 index) const
    {
        return GetCounterGroup(GetHardwareExposedCounterInternalIndex(index));
    }

    bool GetHardwareInfo(const gpa_uint32& counter_index, GpaHwCounter& gpa_hw_counter) const
    {
        if (counter_index <= m_counters.size())
        {
            auto counter_hardware_info = counter_hardware_info_map_.find(counter_index);

            if (counter_hardware_info != counter_hardware_info_map_.end())
            {
                gpa_hw_counter = counter_hardware_info->second;
                return true;
            }
            else
            {
                bool       found_counter      = false;
                gpa_uint32 counter_group      = 0u;
                gpa_uint32 counter_index_iter = 0u;

                do
                {
                    gpa_uint32 temp_counter_index = counter_index_iter + m_pGroups[counter_group].m_numCounters;
                    if (counter_index < temp_counter_index)
                    {
                        found_counter = true;
                    }
                    else
                    {
                        ++counter_group;
                        counter_index_iter = temp_counter_index;
                    }
                } while (!found_counter);

                if (found_counter)
                {
                    gpa_hw_counter.gpa_hw_block_event_id = counter_index - counter_index_iter;
                    gpa_hw_counter.gpa_hw_block_instance = m_pGroups[counter_group].m_blockInstance;
                    GetHardwareBlock(counter_group, gpa_hw_counter.gpa_hw_block, gpa_hw_counter.gpa_shader_mask);
                    counter_hardware_info_map_.insert(std::pair<CounterIndex, GpaHwCounter>(counter_index, gpa_hw_counter));
                    return true;
                }
            }
        }

        return false;
    }

    /// Gets the description of the specified counter
    /// \param index the index of the counter whose description is needed
    /// \return the description of the specified counter
    const char* GetCounterDescription(gpa_uint32 index) const
    {
        return m_counters[index].m_pHardwareCounter->m_pDescription;
    }

    /// Gets the description of the specified counter
    /// \param index the index of the counter whose description is needed
    /// \return the description of the specified counter
    const char* GetHardwareExposedCounterDescription(gpa_uint32 index) const
    {
        return GetCounterDescription(GetHardwareExposedCounterInternalIndex(index));
    }

    /// Gets a counter's UUID
    /// \param index the index of the requested counter
    /// \return the counter's UUID
    GPA_UUID GetCounterUuid(gpa_uint32 index) const
    {
        return ::GetCounterUuid(GetCounterName(index), GetCounterDescription(index));
    }

    /// Gets a counter's UUID
    /// \param index the index of the requested counter
    /// \return the counter's UUID
    GPA_UUID GetHardwareExposedCounterUuid(gpa_uint32 index) const
    {
        return ::GetCounterUuid(GetHardwareExposedCounterName(index), GetHardwareExposedCounterDescription(index));
    }

    /// Returns the internal index of hardware exposed counter in hardware counter list
    /// \param[in] exposedCounterIndex exposed counter index
    /// \return index in hardware counter list
    gpa_uint32 GetHardwareExposedCounterInternalIndex(gpa_uint32 exposedCounterIndex) const
    {
        return m_hardwareExposedCounterInternalIndices[exposedCounterIndex];
    }

    /// Return the number of padded counters in the group
    /// \param[in] groupIndex counter group index
    /// \return returns the number of padded counter for the queried groupIndex if found otherwise zero
    gpa_uint32 GetPaddedCounterCount(const gpa_uint32& groupIndex) const
    {
        for (auto groupIter = 0u; groupIter < m_paddedCounterCount; ++groupIter)
        {
            if (m_pPaddedCounters[groupIter].m_groupIndex == groupIndex)
            {
                return static_cast<gpa_uint32>(m_pPaddedCounters[groupIter].m_paddedCounterList.size());
            }
        }

        return 0;
    }

    /// Gets a counter's supported sample type
    /// \param index the index of the requested counter
    /// \return the counter's supported sample type
    GPA_Counter_Sample_Type GetCounterSampleType(gpa_uint32 index) const
    {
        // TODO: Hard coding to discrete-only counters for now.
        //       Uncomment the below line and remove the following two lines when we have a mechanism
        //       for hardware counters to specify which sample types they support.
        //return m_counters[index].m_pHardwareCounter->m_supportedSampleTypes;

        UNREFERENCED_PARAMETER(index);
        return GPA_COUNTER_SAMPLE_TYPE_DISCRETE;
    }

    /// Gets a counter's supported sample type
    /// \param index the index of the requested counter
    /// \return the counter's supported sample type
    GPA_Counter_Sample_Type GetHardwareExposedCounterSampleType(gpa_uint32 index) const
    {
        // TODO: Hard coding to discrete-only counters for now.
        //       Uncomment the below line and remove the following two lines when we have a mechanism
        //       for hardware counters to specify which sample types they support.
        //return m_counters[index].m_pHardwareCounter->m_supportedSampleTypes;

        UNREFERENCED_PARAMETER(index);
        return GPA_COUNTER_SAMPLE_TYPE_DISCRETE;
    }

    /// Determines whether the indicated block id is a timestamp block id
    /// \param blockId The block id to check
    /// \return True if the block id is a timestamp block id
    bool IsTimestampBlockId(unsigned int blockId) const
    {
        return m_timestampBlockIds.find(blockId) != m_timestampBlockIds.end();
    }

    /// Determines whether the indicated counter index is a timestamp counter
    /// \param counterIndex The counter index to check
    /// \return True if the counter index is a timestamp counter
    bool IsTimeCounterIndex(unsigned int counterIndex) const
    {
        return m_timeCounterIndices.find(counterIndex) != m_timeCounterIndices.end();
    }

    /// Finds and returns the hardware timing counter with the minimum index in the set
    /// \return The hardware timing counter with the minimum index in the set
    unsigned int GetFirstHardwareTimeCounterIndex() const
    {
        auto iter = std::min_element(m_timeCounterIndices.begin(), m_timeCounterIndices.end());
        return *iter;
    }

    /// Determines whether the indicated counter index is a bottom of pipe counter index
    /// \param counterIndex The counter index to check
    /// \return True if the counter index is a bottom of pipe counter
    bool IsBottomOfPipeCounterIndex(unsigned int counterIndex) const
    {
        return counterIndex == m_gpuTimeBottomToBottomDurationCounterIndex || counterIndex == m_gpuTimeBottomToBottomStartCounterIndex ||
               counterIndex == m_gpuTimeBottomToBottomEndCounterIndex;
    }

    /// Determines whether the indicated counter index is a top of pipe counter index
    /// \param counterIndex The counter index to check
    /// \return True if the counter index is a top of pipe counter
    bool IsTopOfPipeCounterIndex(unsigned int counterIndex) const
    {
        return counterIndex == m_gpuTimeTopToBottomDurationCounterIndex || counterIndex == m_gpuTimeTopToBottomStartCounterIndex ||
               counterIndex == m_gpuTimeTopToBottomEndCounterIndex;
    }

    GPA_HardwareCounterDesc** m_ppCounterGroupArray;                   ///< List of counter groups as defined by the list of internal counters in each group.
    GPA_CounterGroupDesc*     m_pGroups;                               ///< List of internal counter groups
    GPA_CounterGroupDesc*     m_pAdditionalGroups;                     ///< List of internal counter groups exposed by the driver, but not known by GPA
    unsigned int              m_groupCount;                            ///< The number of internal counter groups
    unsigned int              m_additionalGroupCount;                  ///< The number of internal counter groups exposed by the driver, but not known by GPA
    GPA_SQCounterGroupDesc*   m_pSQCounterGroups;                      ///< List of SQCounterGroupDesc
    unsigned int              m_sqGroupCount;                          ///< The number of internal SQ counter groups
    std::set<unsigned int>    m_timestampBlockIds;                     ///< Set of timestamp block id's
    std::set<unsigned int>    m_timeCounterIndices;                    ///< Set of timestamp counter indices
    unsigned int    m_gpuTimeBottomToBottomDurationCounterIndex;       ///< the index of the GPUTime Bottom-to-Bottom duration counter (-1 if it doesn't exist)
    unsigned int    m_gpuTimeBottomToBottomStartCounterIndex;          ///< the index of the GPUTime Bottom-to-Bottom start counter (-1 if it doesn't exist)
    unsigned int    m_gpuTimeBottomToBottomEndCounterIndex;            ///< the index of the GPUTime Bottom-to-Bottom end counter (-1 if it doesn't exist)
    unsigned int    m_gpuTimeTopToBottomDurationCounterIndex;          ///< the index of the GPUTime Top-to-Bottom duration counter (-1 if it doesn't exist)
    unsigned int    m_gpuTimeTopToBottomStartCounterIndex;             ///< the index of the GPUTime Top-to-Bottom start counter (-1 if it doesn't exist)
    unsigned int    m_gpuTimeTopToBottomEndCounterIndex;               ///< the index of the GPUTime Top-to-Bottom end counter (-1 if it doesn't exist)
    bool            m_countersGenerated;                               ///< indicates that the internal counters have been generated
    const uint32_t* m_pIsolatedGroups;                                 ///< List of groups that are isolated from SQ groups
    uint32_t        m_isolatedGroupCount;                              ///< The number of isolated groups
    std::vector<GPA_HardwareCounterDescExt> m_counters;                ///< vector of hardware counters
    std::vector<int>                        m_currentGroupUsedCounts;  ///< List of the number of counters which have been enabled in each group

    using BlockCounterIndexOffset = gpa_uint32;
    using BlockInstance           = gpa_uint32;
    mutable std::vector<std::vector<BlockCounterIndexOffset>> block_instance_counters_index_cache_;  ///< cache of counter offset for the hardware blocks
    mutable std::vector<gpa_uint32> gpa_hw_block_hardware_block_group_cache_;  ///< cache of the gpa hardware block and internal hardware block

    using CounterIndex = gpa_uint32;
    mutable std::map<CounterIndex, GpaHwCounter> counter_hardware_info_map_;  ///< cache of the counter index and hardware info

    /// Hardware exposed counters
    GPA_HardwareCounterDesc**
                                         m_ppHardwareExposedCounter;  ///< List of counter groups as defined by the list of hardware exposed counters counters in each group.
    GPA_CounterGroupExposedCounterDesc*  m_pHardwareExposedCounterGroups;          ///< List of hardware exposed counter groups
    unsigned int                         m_hardwareExposedCounterGroupCount;       ///< The number of hardware exposed counter groups
    std::vector<GPA_HardwareCounterDesc> m_hardwareExposedCounters;                ///< vector of hardware exposed counters
    std::vector<gpa_uint32>              m_hardwareExposedCounterInternalIndices;  ///< internal hardware index for the hardware exposed counter
    bool                                 m_hardwareExposedCountersGenerated;       ///< indicates that the hardware exposed counters have been generated
    GPA_PaddedCounterDesc*               m_pPaddedCounters;                        ///< List of GPA padded counters by groups
    unsigned int                         m_paddedCounterCount;                     ///< Count of GPA padded counter by group
    static std::vector<std::string>      hardware_block_string_;                   ///< internal hardware block string map

#ifdef AMDT_INTERNAL
    std::unordered_map<gpa_uint32, std::string> m_alternateNameMap;  ///< a map from counter index to the alternate name for that counter

    /// Allow hardware counters to be given an alternate name when they are enabled using the "block:instance:event:alt_name" syntax
    /// \param index The index of a counter
    /// \param pCounterName the alternate counter name to be used for the hardware counter
    /// \return true upon success otherwise false
    bool SetCounterName(gpa_uint32 index, const char* pCounterName)
    {
        m_alternateNameMap[index] = std::string(pCounterName);
        return true;
    }
#endif
};

#endif  //_GPA_HARDWARE_COUNTERS_H_
