//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  CL counter definitions for GFX8
//==============================================================================

// This file is autogenerated by the ConvertHWEnums project

#ifndef _GPA_HW_COUNTER_CL_GFX8_H_
#define _GPA_HW_COUNTER_CL_GFX8_H_

// clang-format off

#include <set>

struct GPA_HardwareCounterDesc;
struct GPA_CounterGroupDesc;
struct GPA_SQCounterGroupDesc;

namespace counter_cl_gfx8
{
    extern GPA_HardwareCounterDesc*           cl_counter_group_array_gfx8[]; ///< Array of hardware counter groups for cl for gfx8 family
    extern GPA_HardwareCounterDesc*           cl_exposed_counters_group_array_gfx8[]; ///< Array of hardware exposed counter groups for cl for gfx8 family
    extern GPA_CounterGroupDesc               hw_cl_groups_gfx8[]; ///< Array of counter groups for cl for gfx8 family
    extern GPA_CounterGroupExposedCounterDesc hw_cl_exposed_counters_by_group_gfx8[]; ///< Array of exposed counter groups for cl for gfx8 family
    extern GPA_PaddedCounterDesc              cl_padded_counter_by_group_gfx8[]; ///< Array of reserved counter for cl for gfx8 family
    extern GPA_SQCounterGroupDesc             hw_cl_sq_groups_gfx8[]; ///< Array of SQ groups for cl for gfx8 family
    extern unsigned int                       hw_cl_sq_isolated_groups_gfx8[]; ///< Array of counter groups isolated from SQ counter groups for cl for gfx8 family
    extern const std::set<unsigned int>       hw_cl_timestamp_block_ids_gfx8; ///< Timestamp block id's for cl for gfx8 family
    extern const std::set<unsigned int>       hw_cl_time_counter_indices_gfx8; ///< Timestamp counter indices for cl for gfx8 family
    extern const unsigned int                 hw_cl_group_count_gfx8; ///< Hardware Group Count for cl for gfx8 family
    extern const unsigned int                 hw_cl_exposed_counters_group_count_gfx8; ///< Whitelist hardware counter Group Count for cl for gfx8 family
    extern const unsigned int                 cl_padded_counter_group_count_gfx8; ///< reserved counter group count for cl for gfx8 family
    extern const unsigned int                 hw_cl_sq_group_count_gfx8; ///< Hardware SQ Group Count for cl for gfx8 family
    extern const unsigned int                 hw_cl_sq_isolated_group_count_gfx8; ///< Hardware Isolated Group Count for cl for gfx8 family

/// If the requested ASIC type is supported, then the global GPU generation block instance counters are updated.
/// \param asic_type The ASIC type that is currently in use.
/// \return True if the ASIC is matched by this file and block instances are updated, otherwise false.
inline bool OverrideMaxBlockEvents(GDT_HW_ASIC_TYPE asic_type)
{
    UNREFERENCED_PARAMETER(asic_type);


    return true;
}
} //  namespace counter_cl_gfx8

// clang-format on

#endif  // _GPA_HW_COUNTER_CL_GFX8_H_
