//==============================================================================
// Copyright (c) 2010-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for DX11 GFX11_GFX1103.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx11_gfx1103.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_gfx11_gfx1103.h"

namespace dx11_gfx11_gfx1103
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GpaDerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!counter_gfx11_gfx1103::MatchAsic(asic_type))
    {
        return false;
    }

    counter_gfx11_gfx1103::OverrideBlockInstanceCounters(asic_type);

    return true;
}

}  // namespace dx11_gfx11_gfx1103

