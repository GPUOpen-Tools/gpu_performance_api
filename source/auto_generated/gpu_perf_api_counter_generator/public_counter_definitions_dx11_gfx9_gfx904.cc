//==============================================================================
// Copyright (c) 2010-2022 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for DX11 GFX9_GFX904.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx9_gfx904.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_gfx9_gfx904.h"

namespace dx11_gfx9_gfx904
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
        internal_counters.push_back(12598);
        internal_counters.push_back(12949);
        internal_counters.push_back(13300);
        internal_counters.push_back(13651);
        internal_counters.push_back(12602);
        internal_counters.push_back(12953);
        internal_counters.push_back(13304);
        internal_counters.push_back(13655);
        internal_counters.push_back(12554);
        internal_counters.push_back(12905);
        internal_counters.push_back(13256);
        internal_counters.push_back(13607);
        internal_counters.push_back(12566);
        internal_counters.push_back(12917);
        internal_counters.push_back(13268);
        internal_counters.push_back(13619);
        internal_counters.push_back(12555);
        internal_counters.push_back(12906);
        internal_counters.push_back(13257);
        internal_counters.push_back(13608);
        internal_counters.push_back(12567);
        internal_counters.push_back(12918);
        internal_counters.push_back(13269);
        internal_counters.push_back(13620);
        internal_counters.push_back(23);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusy", internal_counters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max,24,/,(100),*,(100),min");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12598);
        internal_counters.push_back(12949);
        internal_counters.push_back(13300);
        internal_counters.push_back(13651);
        internal_counters.push_back(12602);
        internal_counters.push_back(12953);
        internal_counters.push_back(13304);
        internal_counters.push_back(13655);
        internal_counters.push_back(12554);
        internal_counters.push_back(12905);
        internal_counters.push_back(13256);
        internal_counters.push_back(13607);
        internal_counters.push_back(12566);
        internal_counters.push_back(12917);
        internal_counters.push_back(13268);
        internal_counters.push_back(13619);
        internal_counters.push_back(12555);
        internal_counters.push_back(12906);
        internal_counters.push_back(13257);
        internal_counters.push_back(13608);
        internal_counters.push_back(12567);
        internal_counters.push_back(12918);
        internal_counters.push_back(13269);
        internal_counters.push_back(13620);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusyCycles", internal_counters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12501);
        internal_counters.push_back(12852);
        internal_counters.push_back(13203);
        internal_counters.push_back(13554);

        c.UpdateAsicSpecificDerivedCounter("PrimitivesIn", internal_counters, "0,1,2,3,sum4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12507);
        internal_counters.push_back(12858);
        internal_counters.push_back(13209);
        internal_counters.push_back(13560);
        internal_counters.push_back(12547);
        internal_counters.push_back(12898);
        internal_counters.push_back(13249);
        internal_counters.push_back(13600);
        internal_counters.push_back(12548);
        internal_counters.push_back(12899);
        internal_counters.push_back(13250);
        internal_counters.push_back(13601);
        internal_counters.push_back(12549);
        internal_counters.push_back(12900);
        internal_counters.push_back(13251);
        internal_counters.push_back(13602);
        internal_counters.push_back(12550);
        internal_counters.push_back(12901);
        internal_counters.push_back(13252);
        internal_counters.push_back(13603);

        c.UpdateAsicSpecificDerivedCounter("CulledPrims", internal_counters, "0,1,+,2,+,3,+,4,+,5,+,6,+,7,+,8,+,9,+,10,+,11,+,12,+,13,+,14,+,15,+,16,+,17,+,18,+,19,+");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12514);
        internal_counters.push_back(12865);
        internal_counters.push_back(13216);
        internal_counters.push_back(13567);

        c.UpdateAsicSpecificDerivedCounter("ClippedPrims", internal_counters, "0,1,2,3,sum4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12602);
        internal_counters.push_back(12953);
        internal_counters.push_back(13304);
        internal_counters.push_back(13655);
        internal_counters.push_back(23);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizer", internal_counters, "0,1,max,2,max,3,max,4,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12602);
        internal_counters.push_back(12953);
        internal_counters.push_back(13304);
        internal_counters.push_back(13655);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizerCycles", internal_counters, "0,1,max,2,max,3,max");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14056);
        internal_counters.push_back(14548);
        internal_counters.push_back(15040);
        internal_counters.push_back(15532);
        internal_counters.push_back(14057);
        internal_counters.push_back(14549);
        internal_counters.push_back(15041);
        internal_counters.push_back(15533);
        internal_counters.push_back(14058);
        internal_counters.push_back(14550);
        internal_counters.push_back(15042);
        internal_counters.push_back(15534);
        internal_counters.push_back(14059);
        internal_counters.push_back(14551);
        internal_counters.push_back(15043);
        internal_counters.push_back(15535);
        internal_counters.push_back(14132);
        internal_counters.push_back(14624);
        internal_counters.push_back(15116);
        internal_counters.push_back(15608);
        internal_counters.push_back(14133);
        internal_counters.push_back(14625);
        internal_counters.push_back(15117);
        internal_counters.push_back(15609);
        internal_counters.push_back(14134);
        internal_counters.push_back(14626);
        internal_counters.push_back(15118);
        internal_counters.push_back(15610);
        internal_counters.push_back(14135);
        internal_counters.push_back(14627);
        internal_counters.push_back(15119);
        internal_counters.push_back(15611);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulled", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(0),max,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14056);
        internal_counters.push_back(14548);
        internal_counters.push_back(15040);
        internal_counters.push_back(15532);
        internal_counters.push_back(14057);
        internal_counters.push_back(14549);
        internal_counters.push_back(15041);
        internal_counters.push_back(15533);
        internal_counters.push_back(14058);
        internal_counters.push_back(14550);
        internal_counters.push_back(15042);
        internal_counters.push_back(15534);
        internal_counters.push_back(14059);
        internal_counters.push_back(14551);
        internal_counters.push_back(15043);
        internal_counters.push_back(15535);
        internal_counters.push_back(14132);
        internal_counters.push_back(14624);
        internal_counters.push_back(15116);
        internal_counters.push_back(15608);
        internal_counters.push_back(14133);
        internal_counters.push_back(14625);
        internal_counters.push_back(15117);
        internal_counters.push_back(15609);
        internal_counters.push_back(14134);
        internal_counters.push_back(14626);
        internal_counters.push_back(15118);
        internal_counters.push_back(15610);
        internal_counters.push_back(14135);
        internal_counters.push_back(14627);
        internal_counters.push_back(15119);
        internal_counters.push_back(15611);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulledCount", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(0),max");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14132);
        internal_counters.push_back(14624);
        internal_counters.push_back(15116);
        internal_counters.push_back(15608);
        internal_counters.push_back(14133);
        internal_counters.push_back(14625);
        internal_counters.push_back(15117);
        internal_counters.push_back(15609);
        internal_counters.push_back(14134);
        internal_counters.push_back(14626);
        internal_counters.push_back(15118);
        internal_counters.push_back(15610);
        internal_counters.push_back(14135);
        internal_counters.push_back(14627);
        internal_counters.push_back(15119);
        internal_counters.push_back(15611);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsAcceptedCount", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14132);
        internal_counters.push_back(14624);
        internal_counters.push_back(15116);
        internal_counters.push_back(15608);
        internal_counters.push_back(14133);
        internal_counters.push_back(14625);
        internal_counters.push_back(15117);
        internal_counters.push_back(15609);
        internal_counters.push_back(14134);
        internal_counters.push_back(14626);
        internal_counters.push_back(15118);
        internal_counters.push_back(15610);
        internal_counters.push_back(14135);
        internal_counters.push_back(14627);
        internal_counters.push_back(15119);
        internal_counters.push_back(15611);
        internal_counters.push_back(14156);
        internal_counters.push_back(14648);
        internal_counters.push_back(15140);
        internal_counters.push_back(15632);
        internal_counters.push_back(14056);
        internal_counters.push_back(14548);
        internal_counters.push_back(15040);
        internal_counters.push_back(15532);
        internal_counters.push_back(14057);
        internal_counters.push_back(14549);
        internal_counters.push_back(15041);
        internal_counters.push_back(15533);
        internal_counters.push_back(14058);
        internal_counters.push_back(14550);
        internal_counters.push_back(15042);
        internal_counters.push_back(15534);
        internal_counters.push_back(14059);
        internal_counters.push_back(14551);
        internal_counters.push_back(15043);
        internal_counters.push_back(15535);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulled", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,sum4,-,(0),max,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,sum16,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14132);
        internal_counters.push_back(14624);
        internal_counters.push_back(15116);
        internal_counters.push_back(15608);
        internal_counters.push_back(14133);
        internal_counters.push_back(14625);
        internal_counters.push_back(15117);
        internal_counters.push_back(15609);
        internal_counters.push_back(14134);
        internal_counters.push_back(14626);
        internal_counters.push_back(15118);
        internal_counters.push_back(15610);
        internal_counters.push_back(14135);
        internal_counters.push_back(14627);
        internal_counters.push_back(15119);
        internal_counters.push_back(15611);
        internal_counters.push_back(14156);
        internal_counters.push_back(14648);
        internal_counters.push_back(15140);
        internal_counters.push_back(15632);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulledCount", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,sum4,-,(0),max");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14156);
        internal_counters.push_back(14648);
        internal_counters.push_back(15140);
        internal_counters.push_back(15632);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsSurvivingCount", internal_counters, "0,1,2,3,sum4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14156);
        internal_counters.push_back(14648);
        internal_counters.push_back(15140);
        internal_counters.push_back(15632);
        internal_counters.push_back(14056);
        internal_counters.push_back(14548);
        internal_counters.push_back(15040);
        internal_counters.push_back(15532);
        internal_counters.push_back(14057);
        internal_counters.push_back(14549);
        internal_counters.push_back(15041);
        internal_counters.push_back(15533);
        internal_counters.push_back(14058);
        internal_counters.push_back(14550);
        internal_counters.push_back(15042);
        internal_counters.push_back(15534);
        internal_counters.push_back(14059);
        internal_counters.push_back(14551);
        internal_counters.push_back(15043);
        internal_counters.push_back(15535);

        c.UpdateAsicSpecificDerivedCounter("PostZQuads", internal_counters, "0,1,2,3,sum4,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,sum16,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14156);
        internal_counters.push_back(14648);
        internal_counters.push_back(15140);
        internal_counters.push_back(15632);

        c.UpdateAsicSpecificDerivedCounter("PostZQuadCount", internal_counters, "0,1,2,3,sum4");
    }
    return true;
}

}  // namespace dx11_gfx9_gfx904

