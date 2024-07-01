//==============================================================================
// Copyright (c) 2010-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for DX11 GFX8_BAFFIN.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx8_baffin.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_gfx8_baffin.h"

namespace dx11_gfx8_baffin
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GpaDerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!counter_gfx8_baffin::MatchAsic(asic_type))
    {
        return false;
    }

    counter_gfx8_baffin::OverrideBlockInstanceCounters(asic_type);

    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(49503);
        internal_counters.push_back(49650);
        internal_counters.push_back(49797);
        internal_counters.push_back(49944);
        internal_counters.push_back(10620);

        c.UpdateAsicSpecificDerivedCounter("TessellatorBusy", internal_counters, "0,1,max,2,max,3,max,4,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(49503);
        internal_counters.push_back(49650);
        internal_counters.push_back(49797);
        internal_counters.push_back(49944);

        c.UpdateAsicSpecificDerivedCounter("TessellatorBusyCycles", internal_counters, "0,1,max,2,max,3,max");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(49398);
        internal_counters.push_back(49545);
        internal_counters.push_back(49692);
        internal_counters.push_back(49839);
        internal_counters.push_back(49379);
        internal_counters.push_back(49526);
        internal_counters.push_back(49673);
        internal_counters.push_back(49820);
        internal_counters.push_back(49474);
        internal_counters.push_back(49621);
        internal_counters.push_back(49768);
        internal_counters.push_back(49915);

        c.UpdateAsicSpecificDerivedCounter("VSVerticesIn", internal_counters, "0,1,2,3,sum4,4,5,6,7,sum4,4,5,6,7,sum4,ifnotzero,8,9,10,11,sum4,8,9,10,11,sum4,ifnotzero");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(49483);
        internal_counters.push_back(49630);
        internal_counters.push_back(49777);
        internal_counters.push_back(49924);

        c.UpdateAsicSpecificDerivedCounter("HSPatches", internal_counters, "0,1,2,3,sum4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(49398);
        internal_counters.push_back(49545);
        internal_counters.push_back(49692);
        internal_counters.push_back(49839);
        internal_counters.push_back(49379);
        internal_counters.push_back(49526);
        internal_counters.push_back(49673);
        internal_counters.push_back(49820);
        internal_counters.push_back(49474);
        internal_counters.push_back(49621);
        internal_counters.push_back(49768);
        internal_counters.push_back(49915);

        c.UpdateAsicSpecificDerivedCounter("DSVerticesIn", internal_counters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,4,5,6,7,sum4,ifnotzero,8,9,10,11,sum4,ifnotzero");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(49387);
        internal_counters.push_back(49534);
        internal_counters.push_back(49681);
        internal_counters.push_back(49828);

        c.UpdateAsicSpecificDerivedCounter("GSPrimsIn", internal_counters, "0,1,2,3,sum4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(49398);
        internal_counters.push_back(49545);
        internal_counters.push_back(49692);
        internal_counters.push_back(49839);
        internal_counters.push_back(49379);
        internal_counters.push_back(49526);
        internal_counters.push_back(49673);
        internal_counters.push_back(49820);

        c.UpdateAsicSpecificDerivedCounter("GSVerticesOut", internal_counters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,ifnotzero");
    }
    return true;
}

}  // namespace dx11_gfx8_baffin

