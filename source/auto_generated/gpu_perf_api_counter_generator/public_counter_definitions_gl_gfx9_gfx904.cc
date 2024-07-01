//==============================================================================
// Copyright (c) 2010-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for GL GFX9_GFX904.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_gl_gfx9_gfx904.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_gfx9_gfx904.h"

namespace gl_gfx9_gfx904
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GpaDerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!counter_gfx9_gfx904::MatchAsic(asic_type))
    {
        return false;
    }

    counter_gfx9_gfx904::OverrideBlockInstanceCounters(asic_type);

    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3182);
        internal_counters.push_back(16301);
        internal_counters.push_back(4055);

        c.UpdateAsicSpecificDerivedCounter("VsGsPrimsIn", internal_counters, "0,1,1,ifnotzero,(0),2,ifnotzero");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3279);
        internal_counters.push_back(3283);
        internal_counters.push_back(3235);
        internal_counters.push_back(3247);
        internal_counters.push_back(3236);
        internal_counters.push_back(3248);
        internal_counters.push_back(1799);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusy", internal_counters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max,6,/,(100),*,(100),min");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3279);
        internal_counters.push_back(3283);
        internal_counters.push_back(3235);
        internal_counters.push_back(3247);
        internal_counters.push_back(3236);
        internal_counters.push_back(3248);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusyCycles", internal_counters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3182);

        c.UpdateAsicSpecificDerivedCounter("PrimitivesIn", internal_counters, "0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3188);
        internal_counters.push_back(3228);
        internal_counters.push_back(3229);
        internal_counters.push_back(3230);
        internal_counters.push_back(3231);

        c.UpdateAsicSpecificDerivedCounter("CulledPrims", internal_counters, "0,1,+,2,+,3,+,4,+");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3195);

        c.UpdateAsicSpecificDerivedCounter("ClippedPrims", internal_counters, "0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3283);
        internal_counters.push_back(1799);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizer", internal_counters, "0,NUM_PRIM_PIPES,/,1,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3283);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizerCycles", internal_counters, "0,NUM_PRIM_PIPES,/");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3684);
        internal_counters.push_back(3685);
        internal_counters.push_back(3686);
        internal_counters.push_back(3687);
        internal_counters.push_back(3760);
        internal_counters.push_back(3761);
        internal_counters.push_back(3762);
        internal_counters.push_back(3763);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulled", internal_counters, "0,1,2,3,sum4,4,5,6,7,sum4,-,(0),max,0,1,2,3,sum4,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3684);
        internal_counters.push_back(3685);
        internal_counters.push_back(3686);
        internal_counters.push_back(3687);
        internal_counters.push_back(3760);
        internal_counters.push_back(3761);
        internal_counters.push_back(3762);
        internal_counters.push_back(3763);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulledCount", internal_counters, "0,1,2,3,sum4,4,5,6,7,sum4,-,(0),max");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3760);
        internal_counters.push_back(3761);
        internal_counters.push_back(3762);
        internal_counters.push_back(3763);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsAcceptedCount", internal_counters, "0,1,2,3,sum4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3760);
        internal_counters.push_back(3761);
        internal_counters.push_back(3762);
        internal_counters.push_back(3763);
        internal_counters.push_back(3784);
        internal_counters.push_back(3684);
        internal_counters.push_back(3685);
        internal_counters.push_back(3686);
        internal_counters.push_back(3687);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulled", internal_counters, "0,1,2,3,sum4,4,-,(0),max,5,6,7,8,sum4,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3760);
        internal_counters.push_back(3761);
        internal_counters.push_back(3762);
        internal_counters.push_back(3763);
        internal_counters.push_back(3784);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulledCount", internal_counters, "0,1,2,3,sum4,4,-,(0),max");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3784);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsSurvivingCount", internal_counters, "0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3784);
        internal_counters.push_back(3684);
        internal_counters.push_back(3685);
        internal_counters.push_back(3686);
        internal_counters.push_back(3687);

        c.UpdateAsicSpecificDerivedCounter("PostZQuads", internal_counters, "0,1,2,3,4,sum4,/,(100),*,(100),min");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3784);

        c.UpdateAsicSpecificDerivedCounter("PostZQuadCount", internal_counters, "0");
    }
    return true;
}

}  // namespace gl_gfx9_gfx904

