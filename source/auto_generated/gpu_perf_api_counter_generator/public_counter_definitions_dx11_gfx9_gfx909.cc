//==============================================================================
// Copyright (c) 2010-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for DX11 GFX9_GFX909.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx9_gfx909.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_gfx9_gfx909.h"

namespace dx11_gfx9_gfx909
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GpaDerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!counter_gfx9_gfx909::MatchAsic(asic_type))
    {
        return false;
    }

    counter_gfx9_gfx909::OverrideBlockInstanceCounters(asic_type);

    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12501);
        internal_counters.push_back(12852);
        internal_counters.push_back(13203);
        internal_counters.push_back(13554);
        internal_counters.push_back(50929);
        internal_counters.push_back(51077);
        internal_counters.push_back(51225);
        internal_counters.push_back(51373);
        internal_counters.push_back(16735);
        internal_counters.push_back(16931);
        internal_counters.push_back(17127);
        internal_counters.push_back(17323);

        c.UpdateAsicSpecificDerivedCounter("VsGsPrimsIn", internal_counters, "0,1,2,3,sum4,4,5,6,7,sum4,4,5,6,7,sum4,ifnotzero,(0),8,9,10,11,sum4,ifnotzero");
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
        internal_counters.push_back(46186);
        internal_counters.push_back(46468);
        internal_counters.push_back(46750);
        internal_counters.push_back(47032);
        internal_counters.push_back(47314);
        internal_counters.push_back(47596);
        internal_counters.push_back(47878);
        internal_counters.push_back(48160);
        internal_counters.push_back(48442);
        internal_counters.push_back(48724);
        internal_counters.push_back(49006);
        internal_counters.push_back(49288);
        internal_counters.push_back(49570);
        internal_counters.push_back(49852);
        internal_counters.push_back(50134);
        internal_counters.push_back(50416);
        internal_counters.push_back(23);
        internal_counters.push_back(16740);
        internal_counters.push_back(16936);
        internal_counters.push_back(17132);
        internal_counters.push_back(17328);
        internal_counters.push_back(16746);
        internal_counters.push_back(16942);
        internal_counters.push_back(17138);
        internal_counters.push_back(17334);

        c.UpdateAsicSpecificDerivedCounter("CSWriteUnitStalled", internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,18,19,20,21,22,23,24,sum8,ifnotzero");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(46186);
        internal_counters.push_back(46468);
        internal_counters.push_back(46750);
        internal_counters.push_back(47032);
        internal_counters.push_back(47314);
        internal_counters.push_back(47596);
        internal_counters.push_back(47878);
        internal_counters.push_back(48160);
        internal_counters.push_back(48442);
        internal_counters.push_back(48724);
        internal_counters.push_back(49006);
        internal_counters.push_back(49288);
        internal_counters.push_back(49570);
        internal_counters.push_back(49852);
        internal_counters.push_back(50134);
        internal_counters.push_back(50416);
        internal_counters.push_back(16740);
        internal_counters.push_back(16936);
        internal_counters.push_back(17132);
        internal_counters.push_back(17328);
        internal_counters.push_back(16746);
        internal_counters.push_back(16942);
        internal_counters.push_back(17138);
        internal_counters.push_back(17334);

        c.UpdateAsicSpecificDerivedCounter("CSWriteUnitStalledCycles", internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,17,18,19,20,21,22,23,sum8,ifnotzero");
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
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(160);
        internal_counters.push_back(604);
        internal_counters.push_back(1048);
        internal_counters.push_back(1492);
        internal_counters.push_back(1936);
        internal_counters.push_back(2380);
        internal_counters.push_back(2824);
        internal_counters.push_back(3268);
        internal_counters.push_back(3712);
        internal_counters.push_back(4156);
        internal_counters.push_back(4600);
        internal_counters.push_back(5044);
        internal_counters.push_back(5488);
        internal_counters.push_back(5932);
        internal_counters.push_back(6376);
        internal_counters.push_back(6820);

        c.UpdateAsicSpecificDerivedCounter("CBMemRead", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(291);
        internal_counters.push_back(735);
        internal_counters.push_back(1179);
        internal_counters.push_back(1623);
        internal_counters.push_back(2067);
        internal_counters.push_back(2511);
        internal_counters.push_back(2955);
        internal_counters.push_back(3399);
        internal_counters.push_back(3843);
        internal_counters.push_back(4287);
        internal_counters.push_back(4731);
        internal_counters.push_back(5175);
        internal_counters.push_back(5619);
        internal_counters.push_back(6063);
        internal_counters.push_back(6507);
        internal_counters.push_back(6951);
        internal_counters.push_back(158);
        internal_counters.push_back(602);
        internal_counters.push_back(1046);
        internal_counters.push_back(1490);
        internal_counters.push_back(1934);
        internal_counters.push_back(2378);
        internal_counters.push_back(2822);
        internal_counters.push_back(3266);
        internal_counters.push_back(3710);
        internal_counters.push_back(4154);
        internal_counters.push_back(4598);
        internal_counters.push_back(5042);
        internal_counters.push_back(5486);
        internal_counters.push_back(5930);
        internal_counters.push_back(6374);
        internal_counters.push_back(6818);
        internal_counters.push_back(159);
        internal_counters.push_back(603);
        internal_counters.push_back(1047);
        internal_counters.push_back(1491);
        internal_counters.push_back(1935);
        internal_counters.push_back(2379);
        internal_counters.push_back(2823);
        internal_counters.push_back(3267);
        internal_counters.push_back(3711);
        internal_counters.push_back(4155);
        internal_counters.push_back(4599);
        internal_counters.push_back(5043);
        internal_counters.push_back(5487);
        internal_counters.push_back(5931);
        internal_counters.push_back(6375);
        internal_counters.push_back(6819);
        internal_counters.push_back(160);
        internal_counters.push_back(604);
        internal_counters.push_back(1048);
        internal_counters.push_back(1492);
        internal_counters.push_back(1936);
        internal_counters.push_back(2380);
        internal_counters.push_back(2824);
        internal_counters.push_back(3268);
        internal_counters.push_back(3712);
        internal_counters.push_back(4156);
        internal_counters.push_back(4600);
        internal_counters.push_back(5044);
        internal_counters.push_back(5488);
        internal_counters.push_back(5932);
        internal_counters.push_back(6376);
        internal_counters.push_back(6820);

        c.UpdateAsicSpecificDerivedCounter("CBColorAndMaskRead", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(150);
        internal_counters.push_back(594);
        internal_counters.push_back(1038);
        internal_counters.push_back(1482);
        internal_counters.push_back(1926);
        internal_counters.push_back(2370);
        internal_counters.push_back(2814);
        internal_counters.push_back(3258);
        internal_counters.push_back(3702);
        internal_counters.push_back(4146);
        internal_counters.push_back(4590);
        internal_counters.push_back(5034);
        internal_counters.push_back(5478);
        internal_counters.push_back(5922);
        internal_counters.push_back(6366);
        internal_counters.push_back(6810);

        c.UpdateAsicSpecificDerivedCounter("CBMemWritten", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(289);
        internal_counters.push_back(733);
        internal_counters.push_back(1177);
        internal_counters.push_back(1621);
        internal_counters.push_back(2065);
        internal_counters.push_back(2509);
        internal_counters.push_back(2953);
        internal_counters.push_back(3397);
        internal_counters.push_back(3841);
        internal_counters.push_back(4285);
        internal_counters.push_back(4729);
        internal_counters.push_back(5173);
        internal_counters.push_back(5617);
        internal_counters.push_back(6061);
        internal_counters.push_back(6505);
        internal_counters.push_back(6949);
        internal_counters.push_back(148);
        internal_counters.push_back(592);
        internal_counters.push_back(1036);
        internal_counters.push_back(1480);
        internal_counters.push_back(1924);
        internal_counters.push_back(2368);
        internal_counters.push_back(2812);
        internal_counters.push_back(3256);
        internal_counters.push_back(3700);
        internal_counters.push_back(4144);
        internal_counters.push_back(4588);
        internal_counters.push_back(5032);
        internal_counters.push_back(5476);
        internal_counters.push_back(5920);
        internal_counters.push_back(6364);
        internal_counters.push_back(6808);
        internal_counters.push_back(149);
        internal_counters.push_back(593);
        internal_counters.push_back(1037);
        internal_counters.push_back(1481);
        internal_counters.push_back(1925);
        internal_counters.push_back(2369);
        internal_counters.push_back(2813);
        internal_counters.push_back(3257);
        internal_counters.push_back(3701);
        internal_counters.push_back(4145);
        internal_counters.push_back(4589);
        internal_counters.push_back(5033);
        internal_counters.push_back(5477);
        internal_counters.push_back(5921);
        internal_counters.push_back(6365);
        internal_counters.push_back(6809);
        internal_counters.push_back(150);
        internal_counters.push_back(594);
        internal_counters.push_back(1038);
        internal_counters.push_back(1482);
        internal_counters.push_back(1926);
        internal_counters.push_back(2370);
        internal_counters.push_back(2814);
        internal_counters.push_back(3258);
        internal_counters.push_back(3702);
        internal_counters.push_back(4146);
        internal_counters.push_back(4590);
        internal_counters.push_back(5034);
        internal_counters.push_back(5478);
        internal_counters.push_back(5922);
        internal_counters.push_back(6366);
        internal_counters.push_back(6810);

        c.UpdateAsicSpecificDerivedCounter("CBColorAndMaskWritten", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(194);
        internal_counters.push_back(638);
        internal_counters.push_back(1082);
        internal_counters.push_back(1526);
        internal_counters.push_back(1970);
        internal_counters.push_back(2414);
        internal_counters.push_back(2858);
        internal_counters.push_back(3302);
        internal_counters.push_back(3746);
        internal_counters.push_back(4190);
        internal_counters.push_back(4634);
        internal_counters.push_back(5078);
        internal_counters.push_back(5522);
        internal_counters.push_back(5966);
        internal_counters.push_back(6410);
        internal_counters.push_back(6854);
        internal_counters.push_back(39);
        internal_counters.push_back(483);
        internal_counters.push_back(927);
        internal_counters.push_back(1371);
        internal_counters.push_back(1815);
        internal_counters.push_back(2259);
        internal_counters.push_back(2703);
        internal_counters.push_back(3147);
        internal_counters.push_back(3591);
        internal_counters.push_back(4035);
        internal_counters.push_back(4479);
        internal_counters.push_back(4923);
        internal_counters.push_back(5367);
        internal_counters.push_back(5811);
        internal_counters.push_back(6255);
        internal_counters.push_back(6699);

        c.UpdateAsicSpecificDerivedCounter("CBSlowPixelPct", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*,(100),min");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(194);
        internal_counters.push_back(638);
        internal_counters.push_back(1082);
        internal_counters.push_back(1526);
        internal_counters.push_back(1970);
        internal_counters.push_back(2414);
        internal_counters.push_back(2858);
        internal_counters.push_back(3302);
        internal_counters.push_back(3746);
        internal_counters.push_back(4190);
        internal_counters.push_back(4634);
        internal_counters.push_back(5078);
        internal_counters.push_back(5522);
        internal_counters.push_back(5966);
        internal_counters.push_back(6410);
        internal_counters.push_back(6854);

        c.UpdateAsicSpecificDerivedCounter("CBSlowPixelCount", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(46194);
        internal_counters.push_back(46476);
        internal_counters.push_back(46758);
        internal_counters.push_back(47040);
        internal_counters.push_back(47322);
        internal_counters.push_back(47604);
        internal_counters.push_back(47886);
        internal_counters.push_back(48168);
        internal_counters.push_back(48450);
        internal_counters.push_back(48732);
        internal_counters.push_back(49014);
        internal_counters.push_back(49296);
        internal_counters.push_back(49578);
        internal_counters.push_back(49860);
        internal_counters.push_back(50142);
        internal_counters.push_back(50424);
        internal_counters.push_back(46195);
        internal_counters.push_back(46477);
        internal_counters.push_back(46759);
        internal_counters.push_back(47041);
        internal_counters.push_back(47323);
        internal_counters.push_back(47605);
        internal_counters.push_back(47887);
        internal_counters.push_back(48169);
        internal_counters.push_back(48451);
        internal_counters.push_back(48733);
        internal_counters.push_back(49015);
        internal_counters.push_back(49297);
        internal_counters.push_back(49579);
        internal_counters.push_back(49861);
        internal_counters.push_back(50143);
        internal_counters.push_back(50425);

        c.UpdateAsicSpecificDerivedCounter("FetchSize", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(64),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(46182);
        internal_counters.push_back(46464);
        internal_counters.push_back(46746);
        internal_counters.push_back(47028);
        internal_counters.push_back(47310);
        internal_counters.push_back(47592);
        internal_counters.push_back(47874);
        internal_counters.push_back(48156);
        internal_counters.push_back(48438);
        internal_counters.push_back(48720);
        internal_counters.push_back(49002);
        internal_counters.push_back(49284);
        internal_counters.push_back(49566);
        internal_counters.push_back(49848);
        internal_counters.push_back(50130);
        internal_counters.push_back(50412);
        internal_counters.push_back(46183);
        internal_counters.push_back(46465);
        internal_counters.push_back(46747);
        internal_counters.push_back(47029);
        internal_counters.push_back(47311);
        internal_counters.push_back(47593);
        internal_counters.push_back(47875);
        internal_counters.push_back(48157);
        internal_counters.push_back(48439);
        internal_counters.push_back(48721);
        internal_counters.push_back(49003);
        internal_counters.push_back(49285);
        internal_counters.push_back(49567);
        internal_counters.push_back(49849);
        internal_counters.push_back(50131);
        internal_counters.push_back(50413);

        c.UpdateAsicSpecificDerivedCounter("WriteSize", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(46173);
        internal_counters.push_back(46455);
        internal_counters.push_back(46737);
        internal_counters.push_back(47019);
        internal_counters.push_back(47301);
        internal_counters.push_back(47583);
        internal_counters.push_back(47865);
        internal_counters.push_back(48147);
        internal_counters.push_back(48429);
        internal_counters.push_back(48711);
        internal_counters.push_back(48993);
        internal_counters.push_back(49275);
        internal_counters.push_back(49557);
        internal_counters.push_back(49839);
        internal_counters.push_back(50121);
        internal_counters.push_back(50403);
        internal_counters.push_back(46175);
        internal_counters.push_back(46457);
        internal_counters.push_back(46739);
        internal_counters.push_back(47021);
        internal_counters.push_back(47303);
        internal_counters.push_back(47585);
        internal_counters.push_back(47867);
        internal_counters.push_back(48149);
        internal_counters.push_back(48431);
        internal_counters.push_back(48713);
        internal_counters.push_back(48995);
        internal_counters.push_back(49277);
        internal_counters.push_back(49559);
        internal_counters.push_back(49841);
        internal_counters.push_back(50123);
        internal_counters.push_back(50405);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHit", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(46173);
        internal_counters.push_back(46455);
        internal_counters.push_back(46737);
        internal_counters.push_back(47019);
        internal_counters.push_back(47301);
        internal_counters.push_back(47583);
        internal_counters.push_back(47865);
        internal_counters.push_back(48147);
        internal_counters.push_back(48429);
        internal_counters.push_back(48711);
        internal_counters.push_back(48993);
        internal_counters.push_back(49275);
        internal_counters.push_back(49557);
        internal_counters.push_back(49839);
        internal_counters.push_back(50121);
        internal_counters.push_back(50403);
        internal_counters.push_back(46175);
        internal_counters.push_back(46457);
        internal_counters.push_back(46739);
        internal_counters.push_back(47021);
        internal_counters.push_back(47303);
        internal_counters.push_back(47585);
        internal_counters.push_back(47867);
        internal_counters.push_back(48149);
        internal_counters.push_back(48431);
        internal_counters.push_back(48713);
        internal_counters.push_back(48995);
        internal_counters.push_back(49277);
        internal_counters.push_back(49559);
        internal_counters.push_back(49841);
        internal_counters.push_back(50123);
        internal_counters.push_back(50405);

        c.UpdateAsicSpecificDerivedCounter("L2CacheMiss", internal_counters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(46173);
        internal_counters.push_back(46455);
        internal_counters.push_back(46737);
        internal_counters.push_back(47019);
        internal_counters.push_back(47301);
        internal_counters.push_back(47583);
        internal_counters.push_back(47865);
        internal_counters.push_back(48147);
        internal_counters.push_back(48429);
        internal_counters.push_back(48711);
        internal_counters.push_back(48993);
        internal_counters.push_back(49275);
        internal_counters.push_back(49557);
        internal_counters.push_back(49839);
        internal_counters.push_back(50121);
        internal_counters.push_back(50403);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHitCount", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(46175);
        internal_counters.push_back(46457);
        internal_counters.push_back(46739);
        internal_counters.push_back(47021);
        internal_counters.push_back(47303);
        internal_counters.push_back(47585);
        internal_counters.push_back(47867);
        internal_counters.push_back(48149);
        internal_counters.push_back(48431);
        internal_counters.push_back(48713);
        internal_counters.push_back(48995);
        internal_counters.push_back(49277);
        internal_counters.push_back(49559);
        internal_counters.push_back(49841);
        internal_counters.push_back(50123);
        internal_counters.push_back(50405);

        c.UpdateAsicSpecificDerivedCounter("L2CacheMissCount", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(46186);
        internal_counters.push_back(46468);
        internal_counters.push_back(46750);
        internal_counters.push_back(47032);
        internal_counters.push_back(47314);
        internal_counters.push_back(47596);
        internal_counters.push_back(47878);
        internal_counters.push_back(48160);
        internal_counters.push_back(48442);
        internal_counters.push_back(48724);
        internal_counters.push_back(49006);
        internal_counters.push_back(49288);
        internal_counters.push_back(49570);
        internal_counters.push_back(49852);
        internal_counters.push_back(50134);
        internal_counters.push_back(50416);
        internal_counters.push_back(23);

        c.UpdateAsicSpecificDerivedCounter("WriteUnitStalled", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(46186);
        internal_counters.push_back(46468);
        internal_counters.push_back(46750);
        internal_counters.push_back(47032);
        internal_counters.push_back(47314);
        internal_counters.push_back(47596);
        internal_counters.push_back(47878);
        internal_counters.push_back(48160);
        internal_counters.push_back(48442);
        internal_counters.push_back(48724);
        internal_counters.push_back(49006);
        internal_counters.push_back(49288);
        internal_counters.push_back(49570);
        internal_counters.push_back(49852);
        internal_counters.push_back(50134);
        internal_counters.push_back(50416);

        c.UpdateAsicSpecificDerivedCounter("WriteUnitStalledCycles", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16");
    }
    return true;
}

}  // namespace dx11_gfx9_gfx909

