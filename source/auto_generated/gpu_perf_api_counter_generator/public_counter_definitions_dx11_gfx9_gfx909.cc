//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions for DX11 GFX9 _gfx909
//==============================================================================

#include "gpa_counter.h"
#include "public_counter_definitions_dx11_gfx9_gfx909.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "gpa_hw_counter_gfx9_gfx909.h"

namespace dx11_gfx9_gfx909
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GPA_DerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!counter_gfx9_gfx909::MatchAsic(asic_type))
    {
        return false;
    }

    counter_gfx9_gfx909::OverrideBlockInstanceCounters(asic_type);

    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12598);
        internalCounters.push_back(12949);
        internalCounters.push_back(13300);
        internalCounters.push_back(13651);
        internalCounters.push_back(12602);
        internalCounters.push_back(12953);
        internalCounters.push_back(13304);
        internalCounters.push_back(13655);
        internalCounters.push_back(12554);
        internalCounters.push_back(12905);
        internalCounters.push_back(13256);
        internalCounters.push_back(13607);
        internalCounters.push_back(12566);
        internalCounters.push_back(12917);
        internalCounters.push_back(13268);
        internalCounters.push_back(13619);
        internalCounters.push_back(12555);
        internalCounters.push_back(12906);
        internalCounters.push_back(13257);
        internalCounters.push_back(13608);
        internalCounters.push_back(12567);
        internalCounters.push_back(12918);
        internalCounters.push_back(13269);
        internalCounters.push_back(13620);
        internalCounters.push_back(23);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusy", internalCounters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max,24,/,(100),*,(100),min");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12598);
        internalCounters.push_back(12949);
        internalCounters.push_back(13300);
        internalCounters.push_back(13651);
        internalCounters.push_back(12602);
        internalCounters.push_back(12953);
        internalCounters.push_back(13304);
        internalCounters.push_back(13655);
        internalCounters.push_back(12554);
        internalCounters.push_back(12905);
        internalCounters.push_back(13256);
        internalCounters.push_back(13607);
        internalCounters.push_back(12566);
        internalCounters.push_back(12917);
        internalCounters.push_back(13268);
        internalCounters.push_back(13619);
        internalCounters.push_back(12555);
        internalCounters.push_back(12906);
        internalCounters.push_back(13257);
        internalCounters.push_back(13608);
        internalCounters.push_back(12567);
        internalCounters.push_back(12918);
        internalCounters.push_back(13269);
        internalCounters.push_back(13620);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusyCycles", internalCounters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12501);
        internalCounters.push_back(12852);
        internalCounters.push_back(13203);
        internalCounters.push_back(13554);

        c.UpdateAsicSpecificDerivedCounter("PrimitivesIn", internalCounters, "0,1,2,3,sum4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12507);
        internalCounters.push_back(12858);
        internalCounters.push_back(13209);
        internalCounters.push_back(13560);
        internalCounters.push_back(12547);
        internalCounters.push_back(12898);
        internalCounters.push_back(13249);
        internalCounters.push_back(13600);
        internalCounters.push_back(12548);
        internalCounters.push_back(12899);
        internalCounters.push_back(13250);
        internalCounters.push_back(13601);
        internalCounters.push_back(12549);
        internalCounters.push_back(12900);
        internalCounters.push_back(13251);
        internalCounters.push_back(13602);
        internalCounters.push_back(12550);
        internalCounters.push_back(12901);
        internalCounters.push_back(13252);
        internalCounters.push_back(13603);

        c.UpdateAsicSpecificDerivedCounter("CulledPrims", internalCounters, "0,1,+,2,+,3,+,4,+,5,+,6,+,7,+,8,+,9,+,10,+,11,+,12,+,13,+,14,+,15,+,16,+,17,+,18,+,19,+");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12514);
        internalCounters.push_back(12865);
        internalCounters.push_back(13216);
        internalCounters.push_back(13567);

        c.UpdateAsicSpecificDerivedCounter("ClippedPrims", internalCounters, "0,1,2,3,sum4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12602);
        internalCounters.push_back(12953);
        internalCounters.push_back(13304);
        internalCounters.push_back(13655);
        internalCounters.push_back(23);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizer", internalCounters, "0,1,max,2,max,3,max,4,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12602);
        internalCounters.push_back(12953);
        internalCounters.push_back(13304);
        internalCounters.push_back(13655);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizerCycles", internalCounters, "0,1,max,2,max,3,max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46186);
        internalCounters.push_back(46468);
        internalCounters.push_back(46750);
        internalCounters.push_back(47032);
        internalCounters.push_back(47314);
        internalCounters.push_back(47596);
        internalCounters.push_back(47878);
        internalCounters.push_back(48160);
        internalCounters.push_back(48442);
        internalCounters.push_back(48724);
        internalCounters.push_back(49006);
        internalCounters.push_back(49288);
        internalCounters.push_back(49570);
        internalCounters.push_back(49852);
        internalCounters.push_back(50134);
        internalCounters.push_back(50416);
        internalCounters.push_back(23);
        internalCounters.push_back(16740);
        internalCounters.push_back(16936);
        internalCounters.push_back(17132);
        internalCounters.push_back(17328);
        internalCounters.push_back(16746);
        internalCounters.push_back(16942);
        internalCounters.push_back(17138);
        internalCounters.push_back(17334);

        c.UpdateAsicSpecificDerivedCounter("CSWriteUnitStalled", internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,18,19,20,21,22,23,24,sum8,ifnotzero");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46186);
        internalCounters.push_back(46468);
        internalCounters.push_back(46750);
        internalCounters.push_back(47032);
        internalCounters.push_back(47314);
        internalCounters.push_back(47596);
        internalCounters.push_back(47878);
        internalCounters.push_back(48160);
        internalCounters.push_back(48442);
        internalCounters.push_back(48724);
        internalCounters.push_back(49006);
        internalCounters.push_back(49288);
        internalCounters.push_back(49570);
        internalCounters.push_back(49852);
        internalCounters.push_back(50134);
        internalCounters.push_back(50416);
        internalCounters.push_back(16740);
        internalCounters.push_back(16936);
        internalCounters.push_back(17132);
        internalCounters.push_back(17328);
        internalCounters.push_back(16746);
        internalCounters.push_back(16942);
        internalCounters.push_back(17138);
        internalCounters.push_back(17334);

        c.UpdateAsicSpecificDerivedCounter("CSWriteUnitStalledCycles", internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,17,18,19,20,21,22,23,sum8,ifnotzero");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14056);
        internalCounters.push_back(14548);
        internalCounters.push_back(15040);
        internalCounters.push_back(15532);
        internalCounters.push_back(14057);
        internalCounters.push_back(14549);
        internalCounters.push_back(15041);
        internalCounters.push_back(15533);
        internalCounters.push_back(14058);
        internalCounters.push_back(14550);
        internalCounters.push_back(15042);
        internalCounters.push_back(15534);
        internalCounters.push_back(14059);
        internalCounters.push_back(14551);
        internalCounters.push_back(15043);
        internalCounters.push_back(15535);
        internalCounters.push_back(14132);
        internalCounters.push_back(14624);
        internalCounters.push_back(15116);
        internalCounters.push_back(15608);
        internalCounters.push_back(14133);
        internalCounters.push_back(14625);
        internalCounters.push_back(15117);
        internalCounters.push_back(15609);
        internalCounters.push_back(14134);
        internalCounters.push_back(14626);
        internalCounters.push_back(15118);
        internalCounters.push_back(15610);
        internalCounters.push_back(14135);
        internalCounters.push_back(14627);
        internalCounters.push_back(15119);
        internalCounters.push_back(15611);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulled", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(0),max,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14056);
        internalCounters.push_back(14548);
        internalCounters.push_back(15040);
        internalCounters.push_back(15532);
        internalCounters.push_back(14057);
        internalCounters.push_back(14549);
        internalCounters.push_back(15041);
        internalCounters.push_back(15533);
        internalCounters.push_back(14058);
        internalCounters.push_back(14550);
        internalCounters.push_back(15042);
        internalCounters.push_back(15534);
        internalCounters.push_back(14059);
        internalCounters.push_back(14551);
        internalCounters.push_back(15043);
        internalCounters.push_back(15535);
        internalCounters.push_back(14132);
        internalCounters.push_back(14624);
        internalCounters.push_back(15116);
        internalCounters.push_back(15608);
        internalCounters.push_back(14133);
        internalCounters.push_back(14625);
        internalCounters.push_back(15117);
        internalCounters.push_back(15609);
        internalCounters.push_back(14134);
        internalCounters.push_back(14626);
        internalCounters.push_back(15118);
        internalCounters.push_back(15610);
        internalCounters.push_back(14135);
        internalCounters.push_back(14627);
        internalCounters.push_back(15119);
        internalCounters.push_back(15611);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulledCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14132);
        internalCounters.push_back(14624);
        internalCounters.push_back(15116);
        internalCounters.push_back(15608);
        internalCounters.push_back(14133);
        internalCounters.push_back(14625);
        internalCounters.push_back(15117);
        internalCounters.push_back(15609);
        internalCounters.push_back(14134);
        internalCounters.push_back(14626);
        internalCounters.push_back(15118);
        internalCounters.push_back(15610);
        internalCounters.push_back(14135);
        internalCounters.push_back(14627);
        internalCounters.push_back(15119);
        internalCounters.push_back(15611);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsAcceptedCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14056);
        internalCounters.push_back(14548);
        internalCounters.push_back(15040);
        internalCounters.push_back(15532);
        internalCounters.push_back(14057);
        internalCounters.push_back(14549);
        internalCounters.push_back(15041);
        internalCounters.push_back(15533);
        internalCounters.push_back(14058);
        internalCounters.push_back(14550);
        internalCounters.push_back(15042);
        internalCounters.push_back(15534);
        internalCounters.push_back(14059);
        internalCounters.push_back(14551);
        internalCounters.push_back(15043);
        internalCounters.push_back(15535);
        internalCounters.push_back(14156);
        internalCounters.push_back(14648);
        internalCounters.push_back(15140);
        internalCounters.push_back(15632);
        internalCounters.push_back(14132);
        internalCounters.push_back(14624);
        internalCounters.push_back(15116);
        internalCounters.push_back(15608);
        internalCounters.push_back(14133);
        internalCounters.push_back(14625);
        internalCounters.push_back(15117);
        internalCounters.push_back(15609);
        internalCounters.push_back(14134);
        internalCounters.push_back(14626);
        internalCounters.push_back(15118);
        internalCounters.push_back(15610);
        internalCounters.push_back(14135);
        internalCounters.push_back(14627);
        internalCounters.push_back(15119);
        internalCounters.push_back(15611);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulled", internalCounters, "20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,sum16,16,17,18,19,sum4,-,(0),max,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14056);
        internalCounters.push_back(14548);
        internalCounters.push_back(15040);
        internalCounters.push_back(15532);
        internalCounters.push_back(14057);
        internalCounters.push_back(14549);
        internalCounters.push_back(15041);
        internalCounters.push_back(15533);
        internalCounters.push_back(14058);
        internalCounters.push_back(14550);
        internalCounters.push_back(15042);
        internalCounters.push_back(15534);
        internalCounters.push_back(14059);
        internalCounters.push_back(14551);
        internalCounters.push_back(15043);
        internalCounters.push_back(15535);
        internalCounters.push_back(14156);
        internalCounters.push_back(14648);
        internalCounters.push_back(15140);
        internalCounters.push_back(15632);
        internalCounters.push_back(14132);
        internalCounters.push_back(14624);
        internalCounters.push_back(15116);
        internalCounters.push_back(15608);
        internalCounters.push_back(14133);
        internalCounters.push_back(14625);
        internalCounters.push_back(15117);
        internalCounters.push_back(15609);
        internalCounters.push_back(14134);
        internalCounters.push_back(14626);
        internalCounters.push_back(15118);
        internalCounters.push_back(15610);
        internalCounters.push_back(14135);
        internalCounters.push_back(14627);
        internalCounters.push_back(15119);
        internalCounters.push_back(15611);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulledCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,sum4,-,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,sum16,-,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14156);
        internalCounters.push_back(14648);
        internalCounters.push_back(15140);
        internalCounters.push_back(15632);
        internalCounters.push_back(14132);
        internalCounters.push_back(14624);
        internalCounters.push_back(15116);
        internalCounters.push_back(15608);
        internalCounters.push_back(14133);
        internalCounters.push_back(14625);
        internalCounters.push_back(15117);
        internalCounters.push_back(15609);
        internalCounters.push_back(14134);
        internalCounters.push_back(14626);
        internalCounters.push_back(15118);
        internalCounters.push_back(15610);
        internalCounters.push_back(14135);
        internalCounters.push_back(14627);
        internalCounters.push_back(15119);
        internalCounters.push_back(15611);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsSurvivingCount", internalCounters, "4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,sum16,0,1,2,3,sum4,-,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14156);
        internalCounters.push_back(14648);
        internalCounters.push_back(15140);
        internalCounters.push_back(15632);
        internalCounters.push_back(14056);
        internalCounters.push_back(14548);
        internalCounters.push_back(15040);
        internalCounters.push_back(15532);
        internalCounters.push_back(14057);
        internalCounters.push_back(14549);
        internalCounters.push_back(15041);
        internalCounters.push_back(15533);
        internalCounters.push_back(14058);
        internalCounters.push_back(14550);
        internalCounters.push_back(15042);
        internalCounters.push_back(15534);
        internalCounters.push_back(14059);
        internalCounters.push_back(14551);
        internalCounters.push_back(15043);
        internalCounters.push_back(15535);

        c.UpdateAsicSpecificDerivedCounter("PostZQuads", internalCounters, "0,1,2,3,sum4,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,sum16,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14156);
        internalCounters.push_back(14648);
        internalCounters.push_back(15140);
        internalCounters.push_back(15632);

        c.UpdateAsicSpecificDerivedCounter("PostZQuadCount", internalCounters, "0,1,2,3,sum4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(160);
        internalCounters.push_back(604);
        internalCounters.push_back(1048);
        internalCounters.push_back(1492);
        internalCounters.push_back(1936);
        internalCounters.push_back(2380);
        internalCounters.push_back(2824);
        internalCounters.push_back(3268);
        internalCounters.push_back(3712);
        internalCounters.push_back(4156);
        internalCounters.push_back(4600);
        internalCounters.push_back(5044);
        internalCounters.push_back(5488);
        internalCounters.push_back(5932);
        internalCounters.push_back(6376);
        internalCounters.push_back(6820);

        c.UpdateAsicSpecificDerivedCounter("CBMemRead", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(291);
        internalCounters.push_back(735);
        internalCounters.push_back(1179);
        internalCounters.push_back(1623);
        internalCounters.push_back(2067);
        internalCounters.push_back(2511);
        internalCounters.push_back(2955);
        internalCounters.push_back(3399);
        internalCounters.push_back(3843);
        internalCounters.push_back(4287);
        internalCounters.push_back(4731);
        internalCounters.push_back(5175);
        internalCounters.push_back(5619);
        internalCounters.push_back(6063);
        internalCounters.push_back(6507);
        internalCounters.push_back(6951);
        internalCounters.push_back(158);
        internalCounters.push_back(602);
        internalCounters.push_back(1046);
        internalCounters.push_back(1490);
        internalCounters.push_back(1934);
        internalCounters.push_back(2378);
        internalCounters.push_back(2822);
        internalCounters.push_back(3266);
        internalCounters.push_back(3710);
        internalCounters.push_back(4154);
        internalCounters.push_back(4598);
        internalCounters.push_back(5042);
        internalCounters.push_back(5486);
        internalCounters.push_back(5930);
        internalCounters.push_back(6374);
        internalCounters.push_back(6818);
        internalCounters.push_back(159);
        internalCounters.push_back(603);
        internalCounters.push_back(1047);
        internalCounters.push_back(1491);
        internalCounters.push_back(1935);
        internalCounters.push_back(2379);
        internalCounters.push_back(2823);
        internalCounters.push_back(3267);
        internalCounters.push_back(3711);
        internalCounters.push_back(4155);
        internalCounters.push_back(4599);
        internalCounters.push_back(5043);
        internalCounters.push_back(5487);
        internalCounters.push_back(5931);
        internalCounters.push_back(6375);
        internalCounters.push_back(6819);
        internalCounters.push_back(160);
        internalCounters.push_back(604);
        internalCounters.push_back(1048);
        internalCounters.push_back(1492);
        internalCounters.push_back(1936);
        internalCounters.push_back(2380);
        internalCounters.push_back(2824);
        internalCounters.push_back(3268);
        internalCounters.push_back(3712);
        internalCounters.push_back(4156);
        internalCounters.push_back(4600);
        internalCounters.push_back(5044);
        internalCounters.push_back(5488);
        internalCounters.push_back(5932);
        internalCounters.push_back(6376);
        internalCounters.push_back(6820);

        c.UpdateAsicSpecificDerivedCounter("CBColorAndMaskRead", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(150);
        internalCounters.push_back(594);
        internalCounters.push_back(1038);
        internalCounters.push_back(1482);
        internalCounters.push_back(1926);
        internalCounters.push_back(2370);
        internalCounters.push_back(2814);
        internalCounters.push_back(3258);
        internalCounters.push_back(3702);
        internalCounters.push_back(4146);
        internalCounters.push_back(4590);
        internalCounters.push_back(5034);
        internalCounters.push_back(5478);
        internalCounters.push_back(5922);
        internalCounters.push_back(6366);
        internalCounters.push_back(6810);

        c.UpdateAsicSpecificDerivedCounter("CBMemWritten", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(289);
        internalCounters.push_back(733);
        internalCounters.push_back(1177);
        internalCounters.push_back(1621);
        internalCounters.push_back(2065);
        internalCounters.push_back(2509);
        internalCounters.push_back(2953);
        internalCounters.push_back(3397);
        internalCounters.push_back(3841);
        internalCounters.push_back(4285);
        internalCounters.push_back(4729);
        internalCounters.push_back(5173);
        internalCounters.push_back(5617);
        internalCounters.push_back(6061);
        internalCounters.push_back(6505);
        internalCounters.push_back(6949);
        internalCounters.push_back(148);
        internalCounters.push_back(592);
        internalCounters.push_back(1036);
        internalCounters.push_back(1480);
        internalCounters.push_back(1924);
        internalCounters.push_back(2368);
        internalCounters.push_back(2812);
        internalCounters.push_back(3256);
        internalCounters.push_back(3700);
        internalCounters.push_back(4144);
        internalCounters.push_back(4588);
        internalCounters.push_back(5032);
        internalCounters.push_back(5476);
        internalCounters.push_back(5920);
        internalCounters.push_back(6364);
        internalCounters.push_back(6808);
        internalCounters.push_back(149);
        internalCounters.push_back(593);
        internalCounters.push_back(1037);
        internalCounters.push_back(1481);
        internalCounters.push_back(1925);
        internalCounters.push_back(2369);
        internalCounters.push_back(2813);
        internalCounters.push_back(3257);
        internalCounters.push_back(3701);
        internalCounters.push_back(4145);
        internalCounters.push_back(4589);
        internalCounters.push_back(5033);
        internalCounters.push_back(5477);
        internalCounters.push_back(5921);
        internalCounters.push_back(6365);
        internalCounters.push_back(6809);
        internalCounters.push_back(150);
        internalCounters.push_back(594);
        internalCounters.push_back(1038);
        internalCounters.push_back(1482);
        internalCounters.push_back(1926);
        internalCounters.push_back(2370);
        internalCounters.push_back(2814);
        internalCounters.push_back(3258);
        internalCounters.push_back(3702);
        internalCounters.push_back(4146);
        internalCounters.push_back(4590);
        internalCounters.push_back(5034);
        internalCounters.push_back(5478);
        internalCounters.push_back(5922);
        internalCounters.push_back(6366);
        internalCounters.push_back(6810);

        c.UpdateAsicSpecificDerivedCounter("CBColorAndMaskWritten", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(194);
        internalCounters.push_back(638);
        internalCounters.push_back(1082);
        internalCounters.push_back(1526);
        internalCounters.push_back(1970);
        internalCounters.push_back(2414);
        internalCounters.push_back(2858);
        internalCounters.push_back(3302);
        internalCounters.push_back(3746);
        internalCounters.push_back(4190);
        internalCounters.push_back(4634);
        internalCounters.push_back(5078);
        internalCounters.push_back(5522);
        internalCounters.push_back(5966);
        internalCounters.push_back(6410);
        internalCounters.push_back(6854);
        internalCounters.push_back(39);
        internalCounters.push_back(483);
        internalCounters.push_back(927);
        internalCounters.push_back(1371);
        internalCounters.push_back(1815);
        internalCounters.push_back(2259);
        internalCounters.push_back(2703);
        internalCounters.push_back(3147);
        internalCounters.push_back(3591);
        internalCounters.push_back(4035);
        internalCounters.push_back(4479);
        internalCounters.push_back(4923);
        internalCounters.push_back(5367);
        internalCounters.push_back(5811);
        internalCounters.push_back(6255);
        internalCounters.push_back(6699);

        c.UpdateAsicSpecificDerivedCounter("CBSlowPixelPct", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*,(100),min");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(194);
        internalCounters.push_back(638);
        internalCounters.push_back(1082);
        internalCounters.push_back(1526);
        internalCounters.push_back(1970);
        internalCounters.push_back(2414);
        internalCounters.push_back(2858);
        internalCounters.push_back(3302);
        internalCounters.push_back(3746);
        internalCounters.push_back(4190);
        internalCounters.push_back(4634);
        internalCounters.push_back(5078);
        internalCounters.push_back(5522);
        internalCounters.push_back(5966);
        internalCounters.push_back(6410);
        internalCounters.push_back(6854);

        c.UpdateAsicSpecificDerivedCounter("CBSlowPixelCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46194);
        internalCounters.push_back(46476);
        internalCounters.push_back(46758);
        internalCounters.push_back(47040);
        internalCounters.push_back(47322);
        internalCounters.push_back(47604);
        internalCounters.push_back(47886);
        internalCounters.push_back(48168);
        internalCounters.push_back(48450);
        internalCounters.push_back(48732);
        internalCounters.push_back(49014);
        internalCounters.push_back(49296);
        internalCounters.push_back(49578);
        internalCounters.push_back(49860);
        internalCounters.push_back(50142);
        internalCounters.push_back(50424);
        internalCounters.push_back(46195);
        internalCounters.push_back(46477);
        internalCounters.push_back(46759);
        internalCounters.push_back(47041);
        internalCounters.push_back(47323);
        internalCounters.push_back(47605);
        internalCounters.push_back(47887);
        internalCounters.push_back(48169);
        internalCounters.push_back(48451);
        internalCounters.push_back(48733);
        internalCounters.push_back(49015);
        internalCounters.push_back(49297);
        internalCounters.push_back(49579);
        internalCounters.push_back(49861);
        internalCounters.push_back(50143);
        internalCounters.push_back(50425);

        c.UpdateAsicSpecificDerivedCounter("FetchSize", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(64),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46182);
        internalCounters.push_back(46464);
        internalCounters.push_back(46746);
        internalCounters.push_back(47028);
        internalCounters.push_back(47310);
        internalCounters.push_back(47592);
        internalCounters.push_back(47874);
        internalCounters.push_back(48156);
        internalCounters.push_back(48438);
        internalCounters.push_back(48720);
        internalCounters.push_back(49002);
        internalCounters.push_back(49284);
        internalCounters.push_back(49566);
        internalCounters.push_back(49848);
        internalCounters.push_back(50130);
        internalCounters.push_back(50412);
        internalCounters.push_back(46183);
        internalCounters.push_back(46465);
        internalCounters.push_back(46747);
        internalCounters.push_back(47029);
        internalCounters.push_back(47311);
        internalCounters.push_back(47593);
        internalCounters.push_back(47875);
        internalCounters.push_back(48157);
        internalCounters.push_back(48439);
        internalCounters.push_back(48721);
        internalCounters.push_back(49003);
        internalCounters.push_back(49285);
        internalCounters.push_back(49567);
        internalCounters.push_back(49849);
        internalCounters.push_back(50131);
        internalCounters.push_back(50413);

        c.UpdateAsicSpecificDerivedCounter("WriteSize", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46173);
        internalCounters.push_back(46455);
        internalCounters.push_back(46737);
        internalCounters.push_back(47019);
        internalCounters.push_back(47301);
        internalCounters.push_back(47583);
        internalCounters.push_back(47865);
        internalCounters.push_back(48147);
        internalCounters.push_back(48429);
        internalCounters.push_back(48711);
        internalCounters.push_back(48993);
        internalCounters.push_back(49275);
        internalCounters.push_back(49557);
        internalCounters.push_back(49839);
        internalCounters.push_back(50121);
        internalCounters.push_back(50403);
        internalCounters.push_back(46175);
        internalCounters.push_back(46457);
        internalCounters.push_back(46739);
        internalCounters.push_back(47021);
        internalCounters.push_back(47303);
        internalCounters.push_back(47585);
        internalCounters.push_back(47867);
        internalCounters.push_back(48149);
        internalCounters.push_back(48431);
        internalCounters.push_back(48713);
        internalCounters.push_back(48995);
        internalCounters.push_back(49277);
        internalCounters.push_back(49559);
        internalCounters.push_back(49841);
        internalCounters.push_back(50123);
        internalCounters.push_back(50405);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHit", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46173);
        internalCounters.push_back(46455);
        internalCounters.push_back(46737);
        internalCounters.push_back(47019);
        internalCounters.push_back(47301);
        internalCounters.push_back(47583);
        internalCounters.push_back(47865);
        internalCounters.push_back(48147);
        internalCounters.push_back(48429);
        internalCounters.push_back(48711);
        internalCounters.push_back(48993);
        internalCounters.push_back(49275);
        internalCounters.push_back(49557);
        internalCounters.push_back(49839);
        internalCounters.push_back(50121);
        internalCounters.push_back(50403);
        internalCounters.push_back(46175);
        internalCounters.push_back(46457);
        internalCounters.push_back(46739);
        internalCounters.push_back(47021);
        internalCounters.push_back(47303);
        internalCounters.push_back(47585);
        internalCounters.push_back(47867);
        internalCounters.push_back(48149);
        internalCounters.push_back(48431);
        internalCounters.push_back(48713);
        internalCounters.push_back(48995);
        internalCounters.push_back(49277);
        internalCounters.push_back(49559);
        internalCounters.push_back(49841);
        internalCounters.push_back(50123);
        internalCounters.push_back(50405);

        c.UpdateAsicSpecificDerivedCounter("L2CacheMiss", internalCounters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46173);
        internalCounters.push_back(46455);
        internalCounters.push_back(46737);
        internalCounters.push_back(47019);
        internalCounters.push_back(47301);
        internalCounters.push_back(47583);
        internalCounters.push_back(47865);
        internalCounters.push_back(48147);
        internalCounters.push_back(48429);
        internalCounters.push_back(48711);
        internalCounters.push_back(48993);
        internalCounters.push_back(49275);
        internalCounters.push_back(49557);
        internalCounters.push_back(49839);
        internalCounters.push_back(50121);
        internalCounters.push_back(50403);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHitCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46175);
        internalCounters.push_back(46457);
        internalCounters.push_back(46739);
        internalCounters.push_back(47021);
        internalCounters.push_back(47303);
        internalCounters.push_back(47585);
        internalCounters.push_back(47867);
        internalCounters.push_back(48149);
        internalCounters.push_back(48431);
        internalCounters.push_back(48713);
        internalCounters.push_back(48995);
        internalCounters.push_back(49277);
        internalCounters.push_back(49559);
        internalCounters.push_back(49841);
        internalCounters.push_back(50123);
        internalCounters.push_back(50405);

        c.UpdateAsicSpecificDerivedCounter("L2CacheMissCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46186);
        internalCounters.push_back(46468);
        internalCounters.push_back(46750);
        internalCounters.push_back(47032);
        internalCounters.push_back(47314);
        internalCounters.push_back(47596);
        internalCounters.push_back(47878);
        internalCounters.push_back(48160);
        internalCounters.push_back(48442);
        internalCounters.push_back(48724);
        internalCounters.push_back(49006);
        internalCounters.push_back(49288);
        internalCounters.push_back(49570);
        internalCounters.push_back(49852);
        internalCounters.push_back(50134);
        internalCounters.push_back(50416);
        internalCounters.push_back(23);

        c.UpdateAsicSpecificDerivedCounter("WriteUnitStalled", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46186);
        internalCounters.push_back(46468);
        internalCounters.push_back(46750);
        internalCounters.push_back(47032);
        internalCounters.push_back(47314);
        internalCounters.push_back(47596);
        internalCounters.push_back(47878);
        internalCounters.push_back(48160);
        internalCounters.push_back(48442);
        internalCounters.push_back(48724);
        internalCounters.push_back(49006);
        internalCounters.push_back(49288);
        internalCounters.push_back(49570);
        internalCounters.push_back(49852);
        internalCounters.push_back(50134);
        internalCounters.push_back(50416);

        c.UpdateAsicSpecificDerivedCounter("WriteUnitStalledCycles", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16");
    }
    return true;
}

}  // namespace dx11_gfx9_gfx909

