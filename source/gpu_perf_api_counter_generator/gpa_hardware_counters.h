//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Maintains a set of hardware counters.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_HARDWARE_COUNTERS_H_
#define GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_HARDWARE_COUNTERS_H_

#ifdef AMDT_INTERNAL
#include <unordered_map>
#endif

#include <sstream>

#include "gpa_counter.h"
#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpa_split_counters_interfaces.h"
#include "gpa_counter_scheduler_interface.h"

/// @brief Struct to describe a hardware counter
struct GpaHardwareCounterDescExt
{
    GpaUInt32               group_index;        ///< Index of group containing this counter.
    GpaUInt32               group_id_driver;    ///< Group ID according to the driver.
    GpaUInt32               counter_id_driver;  ///< Counter ID according to the driver.
    GpaHardwareCounterDesc* hardware_counters;  ///< The internal counter.
};

/// @brief Maintains a set of hardware counters.
class GpaHardwareCounters
{
public:
    /// @brief Enum of all available hardware blocks.
    enum GpaInternalHardwareBlock
    {
        kGpaInternalHwBlockCpf = 0,                            ///< The Gpa hardware block is CPF.
        kGpaInternalHwBlockIa,                                 ///< The Gpa hardware block is IA.
        kGpaInternalHwBlockVgt,                                ///< The Gpa hardware block is VGT.
        kGpaInternalHwBlockPa,                                 ///< The Gpa hardware block is PA.
        kGpaInternalHwBlockSc,                                 ///< The Gpa hardware block is SC.
        kGpaInternalHwBlockSpi,                                ///< The Gpa hardware block is SPI.
        kGpaInternalHwBlockSq,                                 ///< The Gpa hardware block is SQ.
        kGpaInternalHwBlockSx,                                 ///< The Gpa hardware block is SX.
        kGpaInternalHwBlockTa,                                 ///< The Gpa hardware block is TA.
        kGpaInternalHwBlockTd,                                 ///< The Gpa hardware block is TD.
        kGpaInternalHwBlockTcp,                                ///< The Gpa hardware block is TCP.
        kGpaInternalHwBlockTcc,                                ///< The Gpa hardware block is TCC.
        kGpaInternalHwBlockTca,                                ///< The Gpa hardware block is TCA.
        kGpaInternalHwBlockDb,                                 ///< The Gpa hardware block is DB.
        kGpaInternalHwBlockCb,                                 ///< The Gpa hardware block is CB.
        kGpaInternalHwBlockGds,                                ///< The Gpa hardware block is GDS.
        kGpaInternalHwBlockSrbm,                               ///< The Gpa hardware block is SRBM.
        kGpaInternalHwBlockGrbm,                               ///< The Gpa hardware block is GRBM.
        kGpaInternalHwBlockGrbmse,                             ///< The Gpa hardware block is GRBMSE.
        kGpaInternalHwBlockRlc,                                ///< The Gpa hardware block is RLC.
        kGpaInternalHwBlockDma,                                ///< The Gpa hardware block is DMA.
        kGpaInternalHwBlockMc,                                 ///< The Gpa hardware block is MC.
        kGpaInternalHwBlockCpg,                                ///< The Gpa hardware block is CPG.
        kGpaInternalHwBlockCpc,                                ///< The Gpa hardware block is CPC.
        kGpaInternalHwBlockWd,                                 ///< The Gpa hardware block is WD.
        kGpaInternalHwBlockTcs,                                ///< The Gpa hardware block is TCS.
        kGpaInternalHwBlockAtc,                                ///< The Gpa hardware block is ATC.
        kGpaInternalHwBlockAtcl2,                              ///< The Gpa hardware block is ATCL2.
        kGpaInternalHwBlockMcvml2,                             ///< The Gpa hardware block is MCVML2.
        kGpaInternalHwBlockEa,                                 ///< The Gpa hardware block is EA.
        kGpaInternalHwBlockRpb,                                ///< The Gpa hardware block is RPB.
        kGpaInternalHwBlockRmi,                                ///< The Gpa hardware block is RMI.
        kGpaInternalHwBlockUmcch,                              ///< The Gpa hardware block is UMCCH.
        kGpaInternalHwBlockGe,                                 ///< The Gpa hardware block is GE.
        kGpaInternalHwBlockGl1A,                               ///< The Gpa hardware block is GL1A.
        kGpaInternalHwBlockGl1C,                               ///< The Gpa hardware block is GL1C.
        kGpaInternalHwBlockGl1Cg,                              ///< The Gpa hardware block is GL1CG.
        kGpaInternalHwBlockGl2A,                               ///< The Gpa hardware block is GL2A.
        kGpaInternalHwBlockGl2C,                               ///< The Gpa hardware block is GL2C.
        kGpaInternalHwBlockCha,                                ///< The Gpa hardware block is CHA.
        kGpaInternalHwBlockChc,                                ///< The Gpa hardware block is CHC.
        kGpaInternalHwBlockChcg,                               ///< The Gpa hardware block is CHCG.
        kGpaInternalHwBlockGus,                                ///< The Gpa hardware block is GUS.
        kGpaInternalHwBlockGcr,                                ///< The Gpa hardware block is GCR.
        kGpaInternalHwBlockPh,                                 ///< The Gpa hardware block is PH.
        kGpaInternalHwBlockUtcl1,                              ///< The Gpa hardware block is UTCL1.
        kGpaInternalHwBlockGedist,                             ///< The Gpa hardware block is GEDIST.
        kGpaInternalHwBlockGese,                               ///< The Gpa hardware block is GESE.
        kGpaInternalHwBlockDfmall,                             ///< The Gpa hardware block is DFMALL.
        kGpaInternalHwBlockSqFirst,                            ///< The Gpa hardware block is SQ.
        kGpaInternalHwBlockSqPs = kGpaInternalHwBlockSqFirst,  ///< The Gpa hardware block is SQ_PS.
        kGpaInternalHwBlockSqVs,                               ///< The Gpa hardware block is SQ_VS.
        kGpaInternalHwBlockSqGs,                               ///< The Gpa hardware block is SQ_GS.
        kGpaInternalHwBlockSqEs,                               ///< The Gpa hardware block is SQ_ES.
        kGpaInternalHwBlockSqHs,                               ///< The Gpa hardware block is SQ_HS.
        kGpaInternalHwBlockSqLs,                               ///< The Gpa hardware block is SQ_LS.
        kGpaInternalHwBlockSqCs,                               ///< The Gpa hardware block is SQ_CS.
        kGpaInternalHwBlockCount,                              ///< Count.
    };

    /// @brief Initializes an instance of the GPA_HardwareCounters class.
    GpaHardwareCounters()
    {
        if (kHardwareBlockString.empty())
        {
            static_assert(kGpaHwBlockCpf == static_cast<GpaHwBlock>(kGpaInternalHwBlockCpf), "Mismatched block");
            static_assert(kGpaHwBlockIa == static_cast<GpaHwBlock>(kGpaInternalHwBlockIa), "Mismatched block");
            static_assert(kGpaHwBlockVgt == static_cast<GpaHwBlock>(kGpaInternalHwBlockVgt), "Mismatched block");
            static_assert(kGpaHwBlockPa == static_cast<GpaHwBlock>(kGpaInternalHwBlockPa), "Mismatched block");
            static_assert(kGpaHwBlockSc == static_cast<GpaHwBlock>(kGpaInternalHwBlockSc), "Mismatched block");
            static_assert(kGpaHwBlockSpi == static_cast<GpaHwBlock>(kGpaInternalHwBlockSpi), "Mismatched block");
            static_assert(kGpaHwBlockSq == static_cast<GpaHwBlock>(kGpaInternalHwBlockSq), "Mismatched block");
            static_assert(kGpaHwBlockSx == static_cast<GpaHwBlock>(kGpaInternalHwBlockSx), "Mismatched block");
            static_assert(kGpaHwBlockTa == static_cast<GpaHwBlock>(kGpaInternalHwBlockTa), "Mismatched block");
            static_assert(kGpaHwBlockTd == static_cast<GpaHwBlock>(kGpaInternalHwBlockTd), "Mismatched block");
            static_assert(kGpaHwBlockTcp == static_cast<GpaHwBlock>(kGpaInternalHwBlockTcp), "Mismatched block");
            static_assert(kGpaHwBlockTcc == static_cast<GpaHwBlock>(kGpaInternalHwBlockTcc), "Mismatched block");
            static_assert(kGpaHwBlockTca == static_cast<GpaHwBlock>(kGpaInternalHwBlockTca), "Mismatched block");
            static_assert(kGpaHwBlockDb == static_cast<GpaHwBlock>(kGpaInternalHwBlockDb), "Mismatched block");
            static_assert(kGpaHwBlockCb == static_cast<GpaHwBlock>(kGpaInternalHwBlockCb), "Mismatched block");
            static_assert(kGpaHwBlockGds == static_cast<GpaHwBlock>(kGpaInternalHwBlockGds), "Mismatched block");
            static_assert(kGpaHwBlockSrbm == static_cast<GpaHwBlock>(kGpaInternalHwBlockSrbm), "Mismatched block");
            static_assert(kGpaHwBlockGrbm == static_cast<GpaHwBlock>(kGpaInternalHwBlockGrbm), "Mismatched block");
            static_assert(kGpaHwBlockGrbmse == static_cast<GpaHwBlock>(kGpaInternalHwBlockGrbmse), "Mismatched block");
            static_assert(kGpaHwBlockRlc == static_cast<GpaHwBlock>(kGpaInternalHwBlockRlc), "Mismatched block");
            static_assert(kGpaHwBlockDma == static_cast<GpaHwBlock>(kGpaInternalHwBlockDma), "Mismatched block");
            static_assert(kGpaHwBlockMc == static_cast<GpaHwBlock>(kGpaInternalHwBlockMc), "Mismatched block");
            static_assert(kGpaHwBlockCpg == static_cast<GpaHwBlock>(kGpaInternalHwBlockCpg), "Mismatched block");
            static_assert(kGpaHwBlockCpc == static_cast<GpaHwBlock>(kGpaInternalHwBlockCpc), "Mismatched block");
            static_assert(kGpaHwBlockWd == static_cast<GpaHwBlock>(kGpaInternalHwBlockWd), "Mismatched block");
            static_assert(kGpaHwBlockTcs == static_cast<GpaHwBlock>(kGpaInternalHwBlockTcs), "Mismatched block");
            static_assert(kGpaHwBlockAtc == static_cast<GpaHwBlock>(kGpaInternalHwBlockAtc), "Mismatched block");
            static_assert(kGpaHwBlockAtcl2 == static_cast<GpaHwBlock>(kGpaInternalHwBlockAtcl2), "Mismatched block");
            static_assert(kGpaHwBlockMcvml2 == static_cast<GpaHwBlock>(kGpaInternalHwBlockMcvml2), "Mismatched block");
            static_assert(kGpaHwBlockEa == static_cast<GpaHwBlock>(kGpaInternalHwBlockEa), "Mismatched block");
            static_assert(kGpaHwBlockRpb == static_cast<GpaHwBlock>(kGpaInternalHwBlockRpb), "Mismatched block");
            static_assert(kGpaHwBlockRmi == static_cast<GpaHwBlock>(kGpaInternalHwBlockRmi), "Mismatched block");
            static_assert(kGpaHwBlockUmcch == static_cast<GpaHwBlock>(kGpaInternalHwBlockUmcch), "Mismatched block");
            static_assert(kGpaHwBlockGe == static_cast<GpaHwBlock>(kGpaInternalHwBlockGe), "Mismatched block");
            static_assert(kGpaHwBlockGl1A == static_cast<GpaHwBlock>(kGpaInternalHwBlockGl1A), "Mismatched block");
            static_assert(kGpaHwBlockGl1C == static_cast<GpaHwBlock>(kGpaInternalHwBlockGl1C), "Mismatched block");
            static_assert(kGpaHwBlockGl1Cg == static_cast<GpaHwBlock>(kGpaInternalHwBlockGl1Cg), "Mismatched block");
            static_assert(kGpaHwBlockGl2A == static_cast<GpaHwBlock>(kGpaInternalHwBlockGl2A), "Mismatched block");
            static_assert(kGpaHwBlockGl2C == static_cast<GpaHwBlock>(kGpaInternalHwBlockGl2C), "Mismatched block");
            static_assert(kGpaHwBlockCha == static_cast<GpaHwBlock>(kGpaInternalHwBlockCha), "Mismatched block");
            static_assert(kGpaHwBlockChc == static_cast<GpaHwBlock>(kGpaInternalHwBlockChc), "Mismatched block");
            static_assert(kGpaHwBlockChcg == static_cast<GpaHwBlock>(kGpaInternalHwBlockChcg), "Mismatched block");
            static_assert(kGpaHwBlockGus == static_cast<GpaHwBlock>(kGpaInternalHwBlockGus), "Mismatched block");
            static_assert(kGpaHwBlockGcr == static_cast<GpaHwBlock>(kGpaInternalHwBlockGcr), "Mismatched block");
            static_assert(kGpaHwBlockPh == static_cast<GpaHwBlock>(kGpaInternalHwBlockPh), "Mismatched block");
            static_assert(kGpaHwBlockUtcl1 == static_cast<GpaHwBlock>(kGpaInternalHwBlockUtcl1), "Mismatched block");
            static_assert(kGpaHwBlockGedist == static_cast<GpaHwBlock>(kGpaInternalHwBlockGedist), "Mismatched block");
            static_assert(kGpaHwBlockGese == static_cast<GpaHwBlock>(kGpaInternalHwBlockGese), "Mismatched block");
            static_assert(kGpaHwBlockDfmall == static_cast<GpaHwBlock>(kGpaInternalHwBlockDfmall), "Mismatched block");
            static_assert(kGpaHwBlockCount == static_cast<GpaHwBlock>(kGpaInternalHwBlockSqFirst), "Mismatched block");

            kHardwareBlockString = {GPA_ENUM_STRING_VAL(kGpaInternalHwBlockCpf, "CPF"),       GPA_ENUM_STRING_VAL(kGpaInternalHwBlockIa, "IA"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockVgt, "VGT"),       GPA_ENUM_STRING_VAL(kGpaInternalHwBlockPa, "PA_SU"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockSc, "PA_SC"),      GPA_ENUM_STRING_VAL(kGpaInternalHwBlockSpi, "SPI"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockSq, "SQ"),         GPA_ENUM_STRING_VAL(kGpaInternalHwBlockSx, "SX"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockTa, "TA"),         GPA_ENUM_STRING_VAL(kGpaInternalHwBlockTd, "TD"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockTcp, "TCP"),       GPA_ENUM_STRING_VAL(kGpaInternalHwBlockTcc, "TCC"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockTca, "TCA"),       GPA_ENUM_STRING_VAL(kGpaInternalHwBlockDb, "DB"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockCb, "CB"),         GPA_ENUM_STRING_VAL(kGpaInternalHwBlockGds, "GDS"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockSrbm, "SRBM"),     GPA_ENUM_STRING_VAL(kGpaInternalHwBlockGrbm, "GRBM"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockGrbmse, "GRBMSE"), GPA_ENUM_STRING_VAL(kGpaInternalHwBlockRlc, "RLC"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockDma, "DMA"),       GPA_ENUM_STRING_VAL(kGpaInternalHwBlockMc, "MC"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockCpg, "CPG"),       GPA_ENUM_STRING_VAL(kGpaInternalHwBlockCpc, "CPC"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockWd, "WD"),         GPA_ENUM_STRING_VAL(kGpaInternalHwBlockTcs, "TCS"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockAtc, "ATC"),       GPA_ENUM_STRING_VAL(kGpaInternalHwBlockAtcl2, "ATCL2"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockMcvml2, "MCVML2"), GPA_ENUM_STRING_VAL(kGpaInternalHwBlockEa, "GCEA"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockRpb, "RPB"),       GPA_ENUM_STRING_VAL(kGpaInternalHwBlockRmi, "RMI"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockUmcch, "UMC"),     GPA_ENUM_STRING_VAL(kGpaInternalHwBlockGe, "GE"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockGl1A, "GL1A"),     GPA_ENUM_STRING_VAL(kGpaInternalHwBlockGl1C, "GL1C"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockGl1Cg, "GL1CG"),   GPA_ENUM_STRING_VAL(kGpaInternalHwBlockGl2A, "GL2A"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockGl2C, "GL2C"),     GPA_ENUM_STRING_VAL(kGpaInternalHwBlockCha, "CHA"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockChc, "CHC"),       GPA_ENUM_STRING_VAL(kGpaInternalHwBlockChcg, "CHCG"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockGus, "GUS"),       GPA_ENUM_STRING_VAL(kGpaInternalHwBlockGcr, "GCR"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockPh, "PA_PH"),      GPA_ENUM_STRING_VAL(kGpaInternalHwBlockUtcl1, "UTCL1"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockGedist, "GEDIST"), GPA_ENUM_STRING_VAL(kGpaInternalHwBlockGese, "GESE"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockDfmall, "DFMALL"), GPA_ENUM_STRING_VAL(kGpaInternalHwBlockSqPs, "SQ_PS"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockSqVs, "SQ_VS"),    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockSqGs, "SQ_GS"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockSqEs, "SQ_ES"),    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockSqHs, "SQ_HS"),
                                    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockSqLs, "SQ_LS"),    GPA_ENUM_STRING_VAL(kGpaInternalHwBlockSqCs, "SQ_CS")};
        }

        Clear();
    }

    /// @brief Virtual destructor.
    virtual ~GpaHardwareCounters()
    {
        for (auto it = counter_info_map_.begin(); it != counter_info_map_.end(); ++it)
        {
            delete it->second;
        }

        counter_info_map_.clear();
    }

    /// @brief Clears all counter data.
    void Clear()
    {
        current_group_used_counts_.clear();
        hardware_counters_.clear();
        counter_groups_array_                             = nullptr;
        hardware_exposed_counters_                        = nullptr;
        internal_counter_groups_                          = nullptr;
        group_count_                                      = 0;
        additional_groups_                                = nullptr;
        additional_group_count_                           = 0;
        sq_counter_groups_                                = nullptr;
        sq_group_count_                                   = 0;
        gpu_time_bottom_to_bottom_duration_counter_index_ = static_cast<unsigned int>(-1);
        gpu_time_bottom_to_bottom_start_counter_index_    = static_cast<unsigned int>(-1);
        gpu_time_bottom_to_bottom_end_counter_index_      = static_cast<unsigned int>(-1);
        gpu_time_top_to_bottom_duration_counter_index_    = static_cast<unsigned int>(-1);
        gpu_time_top_to_bottom_start_counter_index_       = static_cast<unsigned int>(-1);
        gpu_time_top_to_bottom_end_counter_index_         = static_cast<unsigned int>(-1);
        counters_generated_                               = false;
        isolated_groups_                                  = nullptr;
        isolated_group_count_                             = 0;

        hardware_exposed_counters_            = nullptr;
        hardware_exposed_counter_groups_      = nullptr;
        hardware_exposed_counter_group_count_ = 0;
        hardware_exposed_counters_list_.clear();
        hardware_exposed_counter_internal_indices_list_.clear();
        hardware_exposed_counters_generated_ = false;
        counter_info_map_.clear();
    }

    /// @brief Obtains the number of hardware counters.
    ///
    /// @return The number of hardware counters.
    GpaUInt32 GetNumCounters() const
    {
        return static_cast<GpaUInt32>(hardware_counters_.size());
    }

    /// @brief Obtains the number of hardware exposed counters.
    ///
    /// @return The number of hardware exposed counters.
    GpaUInt32 GetNumHardwareExposedCounters() const
    {
        return static_cast<GpaUInt32>(hardware_exposed_counters_list_.size());
    }

    /// @brief Obtains the index of the counter.
    ///
    /// @param [in] gpa_hardware_block Gpa hardware block.
    /// @param [in] block_instance Block instance.
    /// @param [in] block_event_id Event id in the block.
    /// @param [in] sq_shader_mask SQ shader mask.
    /// @param [out] counter_index Index of the counter.
    ///
    /// @return True if counter is found otherwise false.
    bool GetIndex(const GpaHwBlock&    gpa_hardware_block,
                  const GpaUInt32&     block_instance,
                  const GpaUInt32&     block_event_id,
                  const GpaShaderMask& sq_shader_mask,
                  GpaUInt32*           counter_index) const
    {
        auto update_hardware_info_in_cache = [&](GpaInternalHardwareBlock gpa_internal_hardware_block) -> bool {
            if (gpa_hw_block_hardware_block_group_cache_.empty())
            {
                gpa_hw_block_hardware_block_group_cache_.resize(GpaInternalHardwareBlock::kGpaInternalHwBlockCount);
            }

            if (block_instance_counters_index_cache_.empty())
            {
                block_instance_counters_index_cache_.resize(GpaInternalHardwareBlock::kGpaInternalHwBlockCount);
            }
            else if (GpaInternalHardwareBlock::kGpaInternalHwBlockCount > gpa_internal_hardware_block)
            {
                assert(gpa_hw_block_hardware_block_group_cache_.size() > static_cast<size_t>(gpa_internal_hardware_block));
                if (!block_instance_counters_index_cache_[gpa_internal_hardware_block].empty())
                {
                    // We've already found this block.
                    return true;
                }
            }

            bool      found_block    = false;
            GpaUInt32 group_iter     = 0u;
            GpaUInt32 counter_offset = 0u;

            std::string hardware_block_string = kHardwareBlockString[gpa_internal_hardware_block];
            std::string current_block_string;

            while (!found_block && group_iter < group_count_)
            {
                current_block_string.clear();
                current_block_string = std::string(internal_counter_groups_[group_iter].name);

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
                        counter_offset += internal_counter_groups_[group_iter].num_counters;
                        ++instance_iter;
                        ++group_iter;
                        current_block_string.clear();
                        current_block_string = std::string(internal_counter_groups_[group_iter].name);

                        if (hardware_block_string.find("SQ") != std::string::npos || hardware_block_string.find("GL1C") != std::string::npos)
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

                counter_offset += internal_counter_groups_[group_iter].num_counters;
                ++group_iter;
            }

            return found_block;
        };

        bool valid_counter_query = false;

        GpaInternalHardwareBlock gpa_internal_hardware_block_mapped;

        if (kGpaHwBlockSq == gpa_hardware_block)
        {
            GpaInternalHardwareBlock sq_internal_block = static_cast<GpaInternalHardwareBlock>(kGpaHwBlockSq);

            switch (sq_shader_mask)
            {
            case kGpaShaderMaskCs:
                sq_internal_block = kGpaInternalHwBlockSqCs;
                break;
            case kGpaShaderMaskPs:
                sq_internal_block = kGpaInternalHwBlockSqPs;
                break;
            case kGpaShaderMaskVs:
                sq_internal_block = kGpaInternalHwBlockSqVs;
                break;
            case kGpaShaderMaskGs:
                sq_internal_block = kGpaInternalHwBlockSqGs;
                break;
            case kGpaShaderMaskEs:
                sq_internal_block = kGpaInternalHwBlockSqEs;
                break;
            case kGpaShaderMaskHs:
                sq_internal_block = kGpaInternalHwBlockSqHs;
                break;
            case kGpaShaderMaskLs:
                sq_internal_block = kGpaInternalHwBlockSqLs;
                break;
            case kGpaShaderMaskAll:
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
                        bool valid_event             = block_event_id < internal_counter_groups_[hardware_internal_group].num_counters;

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

    /// @brief Gets the name of the specified counter.
    ///
    /// @param [in] index The index of the counter whose name is needed.
    ///
    /// @return The name of the specified counter.
    const char* GetCounterName(GpaUInt32 index) const
    {
#ifdef AMDT_INTERNAL
        if (0 < alternate_name_map_.count(index))
        {
            return alternate_name_map_.at(index).c_str();
        }
#endif
        return hardware_counters_[index].hardware_counters->name;
    }

    /// @brief Gets the name of the specified hardware exposed counter.
    ///
    /// @param [in] index The index of the counter whose name is needed.
    ///
    /// @return The name of the specified counter.
    const char* GetHardwareExposedCounterName(GpaUInt32 index) const
    {
        return GetCounterName(GetHardwareExposedCounterInternalIndex(index));
    }

    bool GetHardwareExposedCounterIndex(const GpaUInt32& internal_hardware_index, GpaUInt32& exposed_counter_index) const
    {
        auto found = std::find(
            hardware_exposed_counter_internal_indices_list_.cbegin(), hardware_exposed_counter_internal_indices_list_.cend(), internal_hardware_index);

        if (found != hardware_exposed_counter_internal_indices_list_.end())
        {
            exposed_counter_index = static_cast<GpaUInt32>(found - hardware_exposed_counter_internal_indices_list_.cbegin());
            return true;
        }

        return false;
    }

    /// @brief Gets the group (hw block) of the specified counter.
    ///
    /// @param [in] index The index of the counter whose group is needed.
    ///
    /// @return The group name of the specified counter.
    const char* GetCounterGroup(GpaUInt32 index) const
    {
        if (hardware_counters_[index].group_index < group_count_)
        {
            return internal_counter_groups_[hardware_counters_[index].group_index].name;
        }
        else
        {
            GpaUInt32 additional_group_index = hardware_counters_[index].group_index - group_count_;

            if (additional_group_index < additional_group_count_)
            {
                return additional_groups_[additional_group_index].name;
            }
        }

        return nullptr;
    }

    void GetHardwareBlock(const GpaUInt32& group, GpaHwBlock& gpa_hw_block, GpaShaderMask& gpa_shader_mask) const
    {
        std::string group_name(internal_counter_groups_[group].name);

        GpaInternalHardwareBlock internal_hw_block = kGpaInternalHwBlockCount;
        bool                     found             = false;

        // Iterate backwards so that "SQ_PS" won't match "SQ". By iterating backwards, "SQ_PS" will always find SQ_PS"
        // before "SQ".
        for (auto block_iter = kHardwareBlockString.rbegin(); block_iter != kHardwareBlockString.rend(); ++block_iter)
        {
            if (group_name.find(*block_iter) != std::string::npos)
            {
                internal_hw_block = static_cast<GpaInternalHardwareBlock>(kHardwareBlockString.rend() - block_iter - 1);
                found             = true;
                break;
            }
        }

        if (found)
        {
            if (internal_hw_block >= kGpaInternalHwBlockSqFirst)
            {
                static_assert((kGpaInternalHwBlockSqPs - kGpaHwBlockCount) == kGpaShaderMaskPs, "");
                static_assert((kGpaInternalHwBlockSqVs - kGpaHwBlockCount) == kGpaShaderMaskVs, "");
                static_assert((kGpaInternalHwBlockSqGs - kGpaHwBlockCount) == kGpaShaderMaskGs, "");
                static_assert((kGpaInternalHwBlockSqEs - kGpaHwBlockCount) == kGpaShaderMaskEs, "");
                static_assert((kGpaInternalHwBlockSqHs - kGpaHwBlockCount) == kGpaShaderMaskHs, "");
                static_assert((kGpaInternalHwBlockSqLs - kGpaHwBlockCount) == kGpaShaderMaskLs, "");
                static_assert((kGpaInternalHwBlockSqCs - kGpaHwBlockCount) == kGpaShaderMaskCs, "");

                gpa_hw_block    = kGpaHwBlockSq;
                gpa_shader_mask = static_cast<GpaShaderMask>(internal_hw_block - kGpaInternalHwBlockSqFirst);
            }
            else
            {
                gpa_hw_block    = static_cast<GpaHwBlock>(internal_hw_block);
                gpa_shader_mask = kGpaShaderMaskAll;
            }
        }
    }

    /// @brief Gets the group (hw block) of the specified counter.
    ///
    /// @param [in] index The index of the counter whose group is needed.
    ///
    /// @return The group name of the specified counter.
    const char* GetHardwareExposedCounterGroup(GpaUInt32 index) const
    {
        return GetCounterGroup(GetHardwareExposedCounterInternalIndex(index));
    }

    /// @brief Get hardware information for this specified counter.
    ///
    /// @param [in] counter_index The index of the counter to get info for.
    /// @param [out] gpa_hw_counter The hardware counter info.
    ///
    /// @return True if the counter index is valid; false otherwise.
    bool GetHardwareInfo(const GpaUInt32& counter_index, GpaHwCounter& gpa_hw_counter) const
    {
        if (counter_index == gpu_time_bottom_to_bottom_duration_counter_index_)
        {
            gpa_hw_counter.is_timing_block                    = true;
            gpa_hw_counter.gpu_time_bottom_to_bottom_duration = gpu_time_bottom_to_bottom_duration_counter_index_;
            counter_hardware_info_map_.insert(std::pair<CounterIndex, GpaHwCounter>(counter_index, gpa_hw_counter));
            return true;
        }
        if (counter_index == gpu_time_bottom_to_bottom_start_counter_index_)
        {
            gpa_hw_counter.is_timing_block                 = true;
            gpa_hw_counter.gpu_time_bottom_to_bottom_start = gpu_time_bottom_to_bottom_start_counter_index_;
            counter_hardware_info_map_.insert(std::pair<CounterIndex, GpaHwCounter>(counter_index, gpa_hw_counter));
            return true;
        }

        if (counter_index == gpu_time_bottom_to_bottom_end_counter_index_)
        {
            gpa_hw_counter.is_timing_block               = true;
            gpa_hw_counter.gpu_time_bottom_to_bottom_end = gpu_time_bottom_to_bottom_end_counter_index_;
            counter_hardware_info_map_.insert(std::pair<CounterIndex, GpaHwCounter>(counter_index, gpa_hw_counter));
            return true;
        }

        if (counter_index == gpu_time_top_to_bottom_duration_counter_index_)
        {
            gpa_hw_counter.is_timing_block                 = true;
            gpa_hw_counter.gpu_time_top_to_bottom_duration = gpu_time_top_to_bottom_duration_counter_index_;
            counter_hardware_info_map_.insert(std::pair<CounterIndex, GpaHwCounter>(counter_index, gpa_hw_counter));
            return true;
        }

        if (counter_index == gpu_time_top_to_bottom_start_counter_index_)
        {
            gpa_hw_counter.is_timing_block              = true;
            gpa_hw_counter.gpu_time_top_to_bottom_start = gpu_time_top_to_bottom_start_counter_index_;
            counter_hardware_info_map_.insert(std::pair<CounterIndex, GpaHwCounter>(counter_index, gpa_hw_counter));
            return true;
        }

        if (counter_index == gpu_time_top_to_bottom_end_counter_index_)
        {
            gpa_hw_counter.is_timing_block            = true;
            gpa_hw_counter.gpu_time_top_to_bottom_end = gpu_time_top_to_bottom_end_counter_index_;
            counter_hardware_info_map_.insert(std::pair<CounterIndex, GpaHwCounter>(counter_index, gpa_hw_counter));
            return true;
        }

        if (counter_index <= hardware_counters_.size())
        {
            const auto counter_hardware_info = counter_hardware_info_map_.find(counter_index);

            if (counter_hardware_info != counter_hardware_info_map_.end())
            {
                gpa_hw_counter = counter_hardware_info->second;
                return true;
            }

            bool      found_counter      = false;
            GpaUInt32 counter_group      = 0u;
            GpaUInt32 counter_index_iter = 0u;

            do
            {
                const GpaUInt32 temp_counter_index = counter_index_iter + internal_counter_groups_[counter_group].num_counters;
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
                gpa_hw_counter.is_timing_block       = false;
                gpa_hw_counter.gpa_hw_block_event_id = counter_index - counter_index_iter;
                gpa_hw_counter.gpa_hw_block_instance = internal_counter_groups_[counter_group].block_instance;
                GetHardwareBlock(counter_group, gpa_hw_counter.gpa_hw_block, gpa_hw_counter.gpa_shader_mask);
                counter_hardware_info_map_.insert(std::pair<CounterIndex, GpaHwCounter>(counter_index, gpa_hw_counter));
                return true;
            }
        }

        return false;
    }

    /// @brief Gets the description of the specified counter.
    ///
    /// @param [in] index The index of the counter whose description is needed.
    ///
    /// @return The description of the specified counter.
    const char* GetCounterDescription(GpaUInt32 index) const
    {
        return hardware_counters_[index].hardware_counters->description;
    }

    /// @brief Gets the description of the specified counter.
    ///
    /// @param [in] index The index of the counter whose description is needed.
    ///
    /// @return The description of the specified counter.
    const char* GetHardwareExposedCounterDescription(GpaUInt32 index) const
    {
        return GetCounterDescription(GetHardwareExposedCounterInternalIndex(index));
    }

    /// @brief Gets a counter's UUID.
    ///
    /// @param [in] index The index of the requested counter.
    ///
    /// @return The counter's UUID.
    GpaUuid GetCounterUuid(GpaUInt32 index) const
    {
        return ::GetCounterUuid(GetCounterName(index), GetCounterDescription(index));
    }

    /// @brief Gets a counter's UUID.
    ///
    /// @param [in] index The index of the requested counter.
    ///
    /// @return The counter's UUID.
    GpaUuid GetHardwareExposedCounterUuid(GpaUInt32 index) const
    {
        return ::GetCounterUuid(GetHardwareExposedCounterName(index), GetHardwareExposedCounterDescription(index));
    }

    /// @brief Returns the internal index of hardware exposed counter in hardware counter list.
    ///
    /// @param [in] exposed_counter_index The exposed counter index.
    ///
    /// @return Index in hardware counter list.
    GpaUInt32 GetHardwareExposedCounterInternalIndex(GpaUInt32 exposed_counter_index) const
    {
        return hardware_exposed_counter_internal_indices_list_[exposed_counter_index];
    }

    /// @brief Returns the counter info of the hardware exposed counter.
    ///
    /// @param [in] exposed_counter_index The exposed counter index.
    ///
    /// @return Counter info.
    GpaCounterInfo* GetCounterInfo(GpaUInt32 exposed_counter_index) const
    {
        auto            counter_info     = counter_info_map_.find(exposed_counter_index);
        GpaCounterInfo* gpa_counter_info = nullptr;

        if (counter_info == counter_info_map_.end())
        {
            gpa_counter_info = new (std::nothrow) GpaCounterInfo();

            if (nullptr != gpa_counter_info)
            {
                gpa_counter_info->is_derived_counter = false;
                GpaHwCounter hw_counter;
                GetHardwareInfo(exposed_counter_index, hw_counter);
                gpa_counter_info->gpa_hw_counter         = &counter_hardware_info_map_[exposed_counter_index];
                counter_info_map_[exposed_counter_index] = gpa_counter_info;
            }
        }
        else
        {
            gpa_counter_info = counter_info->second;
        }

        return gpa_counter_info;
    }

    /// @brief Return the number of padded counters in the group.
    ///
    /// @param [in] group_index Counter group index.
    ///
    /// @return The number of padded counter for the queried groupIndex if found otherwise zero.
    GpaUInt32 GetPaddedCounterCount(const GpaUInt32& group_index) const
    {
        for (auto group_iter = 0u; group_iter < padded_counter_count_; ++group_iter)
        {
            if (padded_counters_[group_iter].group_index == group_index)
            {
                return static_cast<GpaUInt32>(padded_counters_[group_iter].padded_counter_list.size());
            }
        }

        return 0;
    }

    /// @brief Gets a counter's supported sample type.
    ///
    /// @param [in] index The index of the requested counter.
    ///
    /// @return The counter's supported sample type.
    GpaCounterSampleType GetCounterSampleType(GpaUInt32 index) const
    {
        // TODO: Hard coding to discrete-only counters for now.
        //       Uncomment the below line and remove the following two lines when we have a mechanism
        //       for hardware counters to specify which sample types they support.
        //return pass_counter_list[index].hardware_counters->supported_sample_types_;

        UNREFERENCED_PARAMETER(index);
        return kGpaCounterSampleTypeDiscrete;
    }

    /// @brief Gets a counter's supported sample type.
    ///
    /// @param [in] index The index of the requested counter.
    ///
    /// @return The counter's supported sample type.
    GpaCounterSampleType GetHardwareExposedCounterSampleType(GpaUInt32 index) const
    {
        // TODO: Hard coding to discrete-only counters for now.
        //       Uncomment the below line and remove the following two lines when we have a mechanism
        //       for hardware counters to specify which sample types they support.
        //return pass_counter_list[index].hardware_counters->supported_sample_types_;

        UNREFERENCED_PARAMETER(index);
        return kGpaCounterSampleTypeDiscrete;
    }

    /// @brief Determines whether the indicated block id is a timestamp block id.
    ///
    /// @param [in] block_id The block id to check.
    ///
    /// @return True if the block id is a timestamp block id.
    bool IsTimestampBlockId(unsigned int block_id) const
    {
        return timestamp_block_ids_.find(block_id) != timestamp_block_ids_.end();
    }

    /// Determines whether the indicated counter index is a timestamp counter.
    ///
    /// @param [in] counter_index The counter index to check.
    ///
    /// @return True if the counter index is a timestamp counter.
    bool IsTimeCounterIndex(unsigned int counter_index) const
    {
        return time_counter_indices_.find(counter_index) != time_counter_indices_.end();
    }

    /// @brief Finds and returns the hardware timing counter with the minimum index in the set.
    ///
    /// @return The hardware timing counter with the minimum index in the set.
    unsigned int GetFirstHardwareTimeCounterIndex() const
    {
        auto iter = std::min_element(time_counter_indices_.begin(), time_counter_indices_.end());
        return *iter;
    }

    /// @brief Determines whether the indicated counter index is a bottom of pipe counter index.
    ///
    /// @param [in] counter_index The counter index to check.
    ///
    /// @return True if the counter index is a bottom of pipe counter.
    bool IsBottomOfPipeCounterIndex(unsigned int counter_index) const
    {
        return counter_index == gpu_time_bottom_to_bottom_duration_counter_index_ || counter_index == gpu_time_bottom_to_bottom_start_counter_index_ ||
               counter_index == gpu_time_bottom_to_bottom_end_counter_index_;
    }

    /// @brief Determines whether the indicated counter index is a top of pipe counter index.
    ///
    /// @param [in] counter_index The counter index to check.
    ///
    /// @return True if the counter index is a top of pipe counter.
    bool IsTopOfPipeCounterIndex(unsigned int counter_index) const
    {
        return counter_index == gpu_time_top_to_bottom_duration_counter_index_ || counter_index == gpu_time_top_to_bottom_start_counter_index_ ||
               counter_index == gpu_time_top_to_bottom_end_counter_index_;
    }

    GpaHardwareCounterDesc** counter_groups_array_;                  ///< List of counter groups as defined by the list of internal counters in each group.
    GpaCounterGroupDesc*     internal_counter_groups_;               ///< List of internal counter groups.
    GpaCounterGroupDesc*     additional_groups_;                     ///< List of internal counter groups exposed by the driver, but not known by GPA.
    unsigned int             group_count_;                           ///< The number of internal counter groups.
    unsigned int             additional_group_count_;                ///< The number of internal counter groups exposed by the driver, but not known by GPA.
    GpaSqCounterGroupDesc*   sq_counter_groups_;                     ///< List of GpaSqCounterGroupDesc.
    unsigned int             sq_group_count_;                        ///< The number of internal SQ counter groups.
    std::set<unsigned int>   timestamp_block_ids_;                   ///< Set of timestamp block id's.
    std::set<unsigned int>   time_counter_indices_;                  ///< Set of timestamp counter indices.
    unsigned int gpu_time_bottom_to_bottom_duration_counter_index_;  ///< The index of the GPUTime Bottom-to-Bottom duration counter (-1 if it doesn't exist).
    unsigned int gpu_time_bottom_to_bottom_start_counter_index_;     ///< The index of the GPUTime Bottom-to-Bottom start counter (-1 if it doesn't exist).
    unsigned int gpu_time_bottom_to_bottom_end_counter_index_;       ///< The index of the GPUTime Bottom-to-Bottom end counter (-1 if it doesn't exist).
    unsigned int gpu_time_top_to_bottom_duration_counter_index_;     ///< The index of the GPUTime Top-to-Bottom duration counter (-1 if it doesn't exist).
    unsigned int gpu_time_top_to_bottom_start_counter_index_;        ///< The index of the GPUTime Top-to-Bottom start counter (-1 if it doesn't exist).
    unsigned int gpu_time_top_to_bottom_end_counter_index_;          ///< The index of the GPUTime Top-to-Bottom end counter (-1 if it doesn't exist).
    bool         counters_generated_;                                ///< Indicates that the internal counters have been generated.
    const uint32_t*                        isolated_groups_;         ///< List of groups that are isolated from SQ groups.
    uint32_t                               isolated_group_count_;    ///< The number of isolated groups.
    std::vector<GpaHardwareCounterDescExt> hardware_counters_;       ///< Vector of hardware counters.
    std::vector<int>                       current_group_used_counts_;  ///< List of the number of counters which have been enabled in each group.

    using BlockCounterIndexOffset = GpaUInt32;
    using BlockInstance           = GpaUInt32;
    mutable std::vector<std::vector<BlockCounterIndexOffset>> block_instance_counters_index_cache_;  ///< Cache of counter offset for the hardware blocks.
    mutable std::vector<GpaUInt32> gpa_hw_block_hardware_block_group_cache_;  ///< Cache of the gpa hardware block and internal hardware block.

    using CounterIndex = GpaUInt32;
    mutable std::map<CounterIndex, GpaHwCounter> counter_hardware_info_map_;  ///< Cache of the counter index and hardware info.

    /// Hardware exposed counters.
    GpaHardwareCounterDesc**
                                        hardware_exposed_counters_;  ///< List of counter groups as defined by the list of hardware exposed counters counters in each group.
    GpaCounterGroupExposedCounterDesc*  hardware_exposed_counter_groups_;                 ///< List of hardware exposed counter groups.
    unsigned int                        hardware_exposed_counter_group_count_;            ///< The number of hardware exposed counter groups.
    std::vector<GpaHardwareCounterDesc> hardware_exposed_counters_list_;                  ///< Vector of hardware exposed counters.
    std::vector<GpaUInt32>              hardware_exposed_counter_internal_indices_list_;  ///< Internal hardware index for the hardware exposed counter.
    bool                                hardware_exposed_counters_generated_;             ///< Indicates that the hardware exposed counters have been generated.
    GpaPaddedCounterDesc*               padded_counters_;                                 ///< List of GPA padded counters by groups.
    unsigned int                        padded_counter_count_;                            ///< Count of GPA padded counter by group.
    static std::vector<std::string>     kHardwareBlockString;                             ///< Internal hardware block string map.
    mutable std::map<CounterIndex, GpaCounterInfo*> counter_info_map_;                    ///< Map from counter index to counter info.

#ifdef AMDT_INTERNAL
    /// A map from counter index to the alternate name for that counter.
    std::unordered_map<GpaUInt32, std::string> alternate_name_map_;

    /// @brief Allow hardware counters to be given an alternate name when they are enabled using the "block:instance:event:alt_name" syntax.
    ///
    /// @param [in] index The index of a counter.
    /// @param [in] counter_name The alternate counter name to be used for the hardware counter.
    ///
    /// @return True upon success otherwise false.
    bool SetCounterName(const GpaUInt32& index, const char* counter_name)
    {
        alternate_name_map_[index] = std::string(counter_name);
        return true;
    }
#endif
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_HARDWARE_COUNTERS_H_
