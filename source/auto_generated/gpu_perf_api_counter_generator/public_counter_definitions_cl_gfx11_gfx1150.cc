//==============================================================================
// Copyright (c) 2010-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for CL GFX11_GFX1150.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_cl_gfx11_gfx1150.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_gfx11_gfx1150.h"

namespace cl_gfx11_gfx1150
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GpaDerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!counter_gfx11_gfx1150::MatchAsic(asic_type))
    {
        return false;
    }

    counter_gfx11_gfx1150::OverrideBlockInstanceCounters(asic_type);

    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12379);
        internal_counters.push_back(12458);
        internal_counters.push_back(12537);
        internal_counters.push_back(12616);
        internal_counters.push_back(12695);
        internal_counters.push_back(12774);
        internal_counters.push_back(12853);
        internal_counters.push_back(12932);
        internal_counters.push_back(13011);
        internal_counters.push_back(13090);
        internal_counters.push_back(13169);
        internal_counters.push_back(13248);
        internal_counters.push_back(13327);
        internal_counters.push_back(13406);
        internal_counters.push_back(13485);
        internal_counters.push_back(13564);
        internal_counters.push_back(12387);
        internal_counters.push_back(12466);
        internal_counters.push_back(12545);
        internal_counters.push_back(12624);
        internal_counters.push_back(12703);
        internal_counters.push_back(12782);
        internal_counters.push_back(12861);
        internal_counters.push_back(12940);
        internal_counters.push_back(13019);
        internal_counters.push_back(13098);
        internal_counters.push_back(13177);
        internal_counters.push_back(13256);
        internal_counters.push_back(13335);
        internal_counters.push_back(13414);
        internal_counters.push_back(13493);
        internal_counters.push_back(13572);

        c.UpdateAsicSpecificDerivedCounter("L0CacheHit", internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12409);
        internal_counters.push_back(12488);
        internal_counters.push_back(12567);
        internal_counters.push_back(12646);
        internal_counters.push_back(12725);
        internal_counters.push_back(12804);
        internal_counters.push_back(12883);
        internal_counters.push_back(12962);
        internal_counters.push_back(13041);
        internal_counters.push_back(13120);
        internal_counters.push_back(13199);
        internal_counters.push_back(13278);
        internal_counters.push_back(13357);
        internal_counters.push_back(13436);
        internal_counters.push_back(13515);
        internal_counters.push_back(13594);
        internal_counters.push_back(1280);

        c.UpdateAsicSpecificDerivedCounter("MemUnitStalled", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*");
    }
    return true;
}

}  // namespace cl_gfx11_gfx1150

