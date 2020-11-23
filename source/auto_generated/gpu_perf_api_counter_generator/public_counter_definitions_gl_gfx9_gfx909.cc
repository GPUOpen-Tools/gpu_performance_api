//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions for GL GFX9 _gfx909
//==============================================================================

#include "gpa_counter.h"
#include "public_counter_definitions_gl_gfx9_gfx909.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "gpa_hw_counter_gfx9_gfx909.h"

namespace gl_gfx9_gfx909
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
        internalCounters.push_back(3279);
        internalCounters.push_back(3283);
        internalCounters.push_back(3235);
        internalCounters.push_back(3247);
        internalCounters.push_back(3236);
        internalCounters.push_back(3248);
        internalCounters.push_back(1799);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusy", internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max,6,/,(100),*,(100),min");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3279);
        internalCounters.push_back(3283);
        internalCounters.push_back(3235);
        internalCounters.push_back(3247);
        internalCounters.push_back(3236);
        internalCounters.push_back(3248);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusyCycles", internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3182);

        c.UpdateAsicSpecificDerivedCounter("PrimitivesIn", internalCounters, "0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3188);
        internalCounters.push_back(3228);
        internalCounters.push_back(3229);
        internalCounters.push_back(3230);
        internalCounters.push_back(3231);

        c.UpdateAsicSpecificDerivedCounter("CulledPrims", internalCounters, "0,1,+,2,+,3,+,4,+");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3195);

        c.UpdateAsicSpecificDerivedCounter("ClippedPrims", internalCounters, "0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3283);
        internalCounters.push_back(1799);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizer", internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3283);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizerCycles", internalCounters, "0,NUM_PRIM_PIPES,/");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9420);
        internalCounters.push_back(9702);
        internalCounters.push_back(9984);
        internalCounters.push_back(10266);
        internalCounters.push_back(10548);
        internalCounters.push_back(10830);
        internalCounters.push_back(11112);
        internalCounters.push_back(11394);
        internalCounters.push_back(11676);
        internalCounters.push_back(11958);
        internalCounters.push_back(12240);
        internalCounters.push_back(12522);
        internalCounters.push_back(12804);
        internalCounters.push_back(13086);
        internalCounters.push_back(13368);
        internalCounters.push_back(13650);
        internalCounters.push_back(1799);
        internalCounters.push_back(4060);
        internalCounters.push_back(4066);

        c.UpdateAsicSpecificDerivedCounter("CSWriteUnitStalled", internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,18,+,ifnotzero");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9420);
        internalCounters.push_back(9702);
        internalCounters.push_back(9984);
        internalCounters.push_back(10266);
        internalCounters.push_back(10548);
        internalCounters.push_back(10830);
        internalCounters.push_back(11112);
        internalCounters.push_back(11394);
        internalCounters.push_back(11676);
        internalCounters.push_back(11958);
        internalCounters.push_back(12240);
        internalCounters.push_back(12522);
        internalCounters.push_back(12804);
        internalCounters.push_back(13086);
        internalCounters.push_back(13368);
        internalCounters.push_back(13650);
        internalCounters.push_back(4060);
        internalCounters.push_back(4066);

        c.UpdateAsicSpecificDerivedCounter("CSWriteUnitStalledCycles", internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,17,+,ifnotzero");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3684);
        internalCounters.push_back(3685);
        internalCounters.push_back(3686);
        internalCounters.push_back(3687);
        internalCounters.push_back(3760);
        internalCounters.push_back(3761);
        internalCounters.push_back(3762);
        internalCounters.push_back(3763);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulled", internalCounters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-,(0),max,0,1,+,2,+,3,+,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3684);
        internalCounters.push_back(3685);
        internalCounters.push_back(3686);
        internalCounters.push_back(3687);
        internalCounters.push_back(3760);
        internalCounters.push_back(3761);
        internalCounters.push_back(3762);
        internalCounters.push_back(3763);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulledCount", internalCounters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3760);
        internalCounters.push_back(3761);
        internalCounters.push_back(3762);
        internalCounters.push_back(3763);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsAcceptedCount", internalCounters, "0,1,+,2,+,3,+");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3684);
        internalCounters.push_back(3685);
        internalCounters.push_back(3686);
        internalCounters.push_back(3687);
        internalCounters.push_back(3784);
        internalCounters.push_back(3760);
        internalCounters.push_back(3761);
        internalCounters.push_back(3762);
        internalCounters.push_back(3763);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulled", internalCounters, "5,6,+,7,+,8,+,4,-,(0),max,0,1,+,2,+,3,+,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3684);
        internalCounters.push_back(3685);
        internalCounters.push_back(3686);
        internalCounters.push_back(3687);
        internalCounters.push_back(3784);
        internalCounters.push_back(3760);
        internalCounters.push_back(3761);
        internalCounters.push_back(3762);
        internalCounters.push_back(3763);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulledCount", internalCounters, "0,1,+,2,+,3,+,4,-,5,-,6,-,7,-,8,-,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3784);
        internalCounters.push_back(3760);
        internalCounters.push_back(3761);
        internalCounters.push_back(3762);
        internalCounters.push_back(3763);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsSurvivingCount", internalCounters, "1,2,+,3,+,4,+,0,-,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3784);
        internalCounters.push_back(3684);
        internalCounters.push_back(3685);
        internalCounters.push_back(3686);
        internalCounters.push_back(3687);

        c.UpdateAsicSpecificDerivedCounter("PostZQuads", internalCounters, "0,1,2,+,3,+,4,+,/,(100),*,(100),min");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3784);

        c.UpdateAsicSpecificDerivedCounter("PostZQuadCount", internalCounters, "0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(128);
        internalCounters.push_back(572);
        internalCounters.push_back(1016);
        internalCounters.push_back(1460);

        c.UpdateAsicSpecificDerivedCounter("CBMemRead", internalCounters, "0,1,2,3,sum4,(32),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(259);
        internalCounters.push_back(703);
        internalCounters.push_back(1147);
        internalCounters.push_back(1591);
        internalCounters.push_back(126);
        internalCounters.push_back(570);
        internalCounters.push_back(1014);
        internalCounters.push_back(1458);
        internalCounters.push_back(127);
        internalCounters.push_back(571);
        internalCounters.push_back(1015);
        internalCounters.push_back(1459);
        internalCounters.push_back(128);
        internalCounters.push_back(572);
        internalCounters.push_back(1016);
        internalCounters.push_back(1460);

        c.UpdateAsicSpecificDerivedCounter("CBColorAndMaskRead", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(118);
        internalCounters.push_back(562);
        internalCounters.push_back(1006);
        internalCounters.push_back(1450);

        c.UpdateAsicSpecificDerivedCounter("CBMemWritten", internalCounters, "0,1,2,3,sum4,(32),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(257);
        internalCounters.push_back(701);
        internalCounters.push_back(1145);
        internalCounters.push_back(1589);
        internalCounters.push_back(116);
        internalCounters.push_back(560);
        internalCounters.push_back(1004);
        internalCounters.push_back(1448);
        internalCounters.push_back(117);
        internalCounters.push_back(561);
        internalCounters.push_back(1005);
        internalCounters.push_back(1449);
        internalCounters.push_back(118);
        internalCounters.push_back(562);
        internalCounters.push_back(1006);
        internalCounters.push_back(1450);

        c.UpdateAsicSpecificDerivedCounter("CBColorAndMaskWritten", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(162);
        internalCounters.push_back(606);
        internalCounters.push_back(1050);
        internalCounters.push_back(1494);
        internalCounters.push_back(7);
        internalCounters.push_back(451);
        internalCounters.push_back(895);
        internalCounters.push_back(1339);

        c.UpdateAsicSpecificDerivedCounter("CBSlowPixelPct", internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*,(100),min");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(162);
        internalCounters.push_back(606);
        internalCounters.push_back(1050);
        internalCounters.push_back(1494);

        c.UpdateAsicSpecificDerivedCounter("CBSlowPixelCount", internalCounters, "0,1,2,3,sum4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9428);
        internalCounters.push_back(9710);
        internalCounters.push_back(9992);
        internalCounters.push_back(10274);
        internalCounters.push_back(10556);
        internalCounters.push_back(10838);
        internalCounters.push_back(11120);
        internalCounters.push_back(11402);
        internalCounters.push_back(11684);
        internalCounters.push_back(11966);
        internalCounters.push_back(12248);
        internalCounters.push_back(12530);
        internalCounters.push_back(12812);
        internalCounters.push_back(13094);
        internalCounters.push_back(13376);
        internalCounters.push_back(13658);
        internalCounters.push_back(9429);
        internalCounters.push_back(9711);
        internalCounters.push_back(9993);
        internalCounters.push_back(10275);
        internalCounters.push_back(10557);
        internalCounters.push_back(10839);
        internalCounters.push_back(11121);
        internalCounters.push_back(11403);
        internalCounters.push_back(11685);
        internalCounters.push_back(11967);
        internalCounters.push_back(12249);
        internalCounters.push_back(12531);
        internalCounters.push_back(12813);
        internalCounters.push_back(13095);
        internalCounters.push_back(13377);
        internalCounters.push_back(13659);

        c.UpdateAsicSpecificDerivedCounter("FetchSize", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(64),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9416);
        internalCounters.push_back(9698);
        internalCounters.push_back(9980);
        internalCounters.push_back(10262);
        internalCounters.push_back(10544);
        internalCounters.push_back(10826);
        internalCounters.push_back(11108);
        internalCounters.push_back(11390);
        internalCounters.push_back(11672);
        internalCounters.push_back(11954);
        internalCounters.push_back(12236);
        internalCounters.push_back(12518);
        internalCounters.push_back(12800);
        internalCounters.push_back(13082);
        internalCounters.push_back(13364);
        internalCounters.push_back(13646);
        internalCounters.push_back(9417);
        internalCounters.push_back(9699);
        internalCounters.push_back(9981);
        internalCounters.push_back(10263);
        internalCounters.push_back(10545);
        internalCounters.push_back(10827);
        internalCounters.push_back(11109);
        internalCounters.push_back(11391);
        internalCounters.push_back(11673);
        internalCounters.push_back(11955);
        internalCounters.push_back(12237);
        internalCounters.push_back(12519);
        internalCounters.push_back(12801);
        internalCounters.push_back(13083);
        internalCounters.push_back(13365);
        internalCounters.push_back(13647);

        c.UpdateAsicSpecificDerivedCounter("WriteSize", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9407);
        internalCounters.push_back(9689);
        internalCounters.push_back(9971);
        internalCounters.push_back(10253);
        internalCounters.push_back(10535);
        internalCounters.push_back(10817);
        internalCounters.push_back(11099);
        internalCounters.push_back(11381);
        internalCounters.push_back(11663);
        internalCounters.push_back(11945);
        internalCounters.push_back(12227);
        internalCounters.push_back(12509);
        internalCounters.push_back(12791);
        internalCounters.push_back(13073);
        internalCounters.push_back(13355);
        internalCounters.push_back(13637);
        internalCounters.push_back(9409);
        internalCounters.push_back(9691);
        internalCounters.push_back(9973);
        internalCounters.push_back(10255);
        internalCounters.push_back(10537);
        internalCounters.push_back(10819);
        internalCounters.push_back(11101);
        internalCounters.push_back(11383);
        internalCounters.push_back(11665);
        internalCounters.push_back(11947);
        internalCounters.push_back(12229);
        internalCounters.push_back(12511);
        internalCounters.push_back(12793);
        internalCounters.push_back(13075);
        internalCounters.push_back(13357);
        internalCounters.push_back(13639);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHit", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9407);
        internalCounters.push_back(9689);
        internalCounters.push_back(9971);
        internalCounters.push_back(10253);
        internalCounters.push_back(10535);
        internalCounters.push_back(10817);
        internalCounters.push_back(11099);
        internalCounters.push_back(11381);
        internalCounters.push_back(11663);
        internalCounters.push_back(11945);
        internalCounters.push_back(12227);
        internalCounters.push_back(12509);
        internalCounters.push_back(12791);
        internalCounters.push_back(13073);
        internalCounters.push_back(13355);
        internalCounters.push_back(13637);
        internalCounters.push_back(9409);
        internalCounters.push_back(9691);
        internalCounters.push_back(9973);
        internalCounters.push_back(10255);
        internalCounters.push_back(10537);
        internalCounters.push_back(10819);
        internalCounters.push_back(11101);
        internalCounters.push_back(11383);
        internalCounters.push_back(11665);
        internalCounters.push_back(11947);
        internalCounters.push_back(12229);
        internalCounters.push_back(12511);
        internalCounters.push_back(12793);
        internalCounters.push_back(13075);
        internalCounters.push_back(13357);
        internalCounters.push_back(13639);

        c.UpdateAsicSpecificDerivedCounter("L2CacheMiss", internalCounters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9407);
        internalCounters.push_back(9689);
        internalCounters.push_back(9971);
        internalCounters.push_back(10253);
        internalCounters.push_back(10535);
        internalCounters.push_back(10817);
        internalCounters.push_back(11099);
        internalCounters.push_back(11381);
        internalCounters.push_back(11663);
        internalCounters.push_back(11945);
        internalCounters.push_back(12227);
        internalCounters.push_back(12509);
        internalCounters.push_back(12791);
        internalCounters.push_back(13073);
        internalCounters.push_back(13355);
        internalCounters.push_back(13637);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHitCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9409);
        internalCounters.push_back(9691);
        internalCounters.push_back(9973);
        internalCounters.push_back(10255);
        internalCounters.push_back(10537);
        internalCounters.push_back(10819);
        internalCounters.push_back(11101);
        internalCounters.push_back(11383);
        internalCounters.push_back(11665);
        internalCounters.push_back(11947);
        internalCounters.push_back(12229);
        internalCounters.push_back(12511);
        internalCounters.push_back(12793);
        internalCounters.push_back(13075);
        internalCounters.push_back(13357);
        internalCounters.push_back(13639);

        c.UpdateAsicSpecificDerivedCounter("L2CacheMissCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9420);
        internalCounters.push_back(9702);
        internalCounters.push_back(9984);
        internalCounters.push_back(10266);
        internalCounters.push_back(10548);
        internalCounters.push_back(10830);
        internalCounters.push_back(11112);
        internalCounters.push_back(11394);
        internalCounters.push_back(11676);
        internalCounters.push_back(11958);
        internalCounters.push_back(12240);
        internalCounters.push_back(12522);
        internalCounters.push_back(12804);
        internalCounters.push_back(13086);
        internalCounters.push_back(13368);
        internalCounters.push_back(13650);
        internalCounters.push_back(1799);

        c.UpdateAsicSpecificDerivedCounter("WriteUnitStalled", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9420);
        internalCounters.push_back(9702);
        internalCounters.push_back(9984);
        internalCounters.push_back(10266);
        internalCounters.push_back(10548);
        internalCounters.push_back(10830);
        internalCounters.push_back(11112);
        internalCounters.push_back(11394);
        internalCounters.push_back(11676);
        internalCounters.push_back(11958);
        internalCounters.push_back(12240);
        internalCounters.push_back(12522);
        internalCounters.push_back(12804);
        internalCounters.push_back(13086);
        internalCounters.push_back(13368);
        internalCounters.push_back(13650);

        c.UpdateAsicSpecificDerivedCounter("WriteUnitStalledCycles", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16");
    }
    return true;
}

}  // namespace gl_gfx9_gfx909

