//==============================================================================
// Copyright (c) 2010-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for GL GFX8_CARRIZO.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_gl_gfx8_carrizo.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_gfx8_carrizo.h"

namespace gl_gfx8_carrizo
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GpaDerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!counter_gfx8_carrizo::MatchAsic(asic_type))
    {
        return false;
    }

    counter_gfx8_carrizo::OverrideBlockInstanceCounters(asic_type);

    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14904);
        internal_counters.push_back(2633);

        c.UpdateAsicSpecificDerivedCounter("TessellatorBusy", internal_counters, "0,NUM_PRIM_PIPES,/,1,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14904);

        c.UpdateAsicSpecificDerivedCounter("TessellatorBusyCycles", internal_counters, "0,NUM_PRIM_PIPES,/");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14800);
        internal_counters.push_back(14781);
        internal_counters.push_back(14876);

        c.UpdateAsicSpecificDerivedCounter("VSVerticesIn", internal_counters, "0,1,1,ifnotzero,2,2,ifnotzero");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14885);

        c.UpdateAsicSpecificDerivedCounter("HSPatches", internal_counters, "0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14800);
        internal_counters.push_back(14781);
        internal_counters.push_back(14876);

        c.UpdateAsicSpecificDerivedCounter("DSVerticesIn", internal_counters, "(0),0,1,1,ifnotzero,2,ifnotzero");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14789);

        c.UpdateAsicSpecificDerivedCounter("GSPrimsIn", internal_counters, "0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14800);
        internal_counters.push_back(14781);

        c.UpdateAsicSpecificDerivedCounter("GSVerticesOut", internal_counters, "(0),0,1,ifnotzero");
    }
    return true;
}

}  // namespace gl_gfx8_carrizo

