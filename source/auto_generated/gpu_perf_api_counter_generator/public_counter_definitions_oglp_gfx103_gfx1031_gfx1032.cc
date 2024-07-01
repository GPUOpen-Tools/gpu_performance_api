//==============================================================================
// Copyright (c) 2010-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for OGLP GFX103_GFX1031_GFX1032.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx103_gfx1031_gfx1032.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_gfx103_gfx1031_gfx1032.h"

namespace oglp_gfx103_gfx1031_gfx1032
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GpaDerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!counter_gfx103_gfx1031_gfx1032::MatchAsic(asic_type))
    {
        return false;
    }

    counter_gfx103_gfx1031_gfx1032::OverrideBlockInstanceCounters(asic_type);

    return true;
}

}  // namespace oglp_gfx103_gfx1031_gfx1032

