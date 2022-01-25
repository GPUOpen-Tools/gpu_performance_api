//==============================================================================
// Copyright (c) 2010-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for GL GFX9_GFX909.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_gl_gfx9_gfx909.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_gfx9_gfx909.h"

namespace gl_gfx9_gfx909
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
        internal_counters.push_back(9420);
        internal_counters.push_back(9702);
        internal_counters.push_back(9984);
        internal_counters.push_back(10266);
        internal_counters.push_back(10548);
        internal_counters.push_back(10830);
        internal_counters.push_back(11112);
        internal_counters.push_back(11394);
        internal_counters.push_back(11676);
        internal_counters.push_back(11958);
        internal_counters.push_back(12240);
        internal_counters.push_back(12522);
        internal_counters.push_back(12804);
        internal_counters.push_back(13086);
        internal_counters.push_back(13368);
        internal_counters.push_back(13650);
        internal_counters.push_back(1799);
        internal_counters.push_back(4060);
        internal_counters.push_back(4066);

        c.UpdateAsicSpecificDerivedCounter("CSWriteUnitStalled", internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,18,+,ifnotzero");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9420);
        internal_counters.push_back(9702);
        internal_counters.push_back(9984);
        internal_counters.push_back(10266);
        internal_counters.push_back(10548);
        internal_counters.push_back(10830);
        internal_counters.push_back(11112);
        internal_counters.push_back(11394);
        internal_counters.push_back(11676);
        internal_counters.push_back(11958);
        internal_counters.push_back(12240);
        internal_counters.push_back(12522);
        internal_counters.push_back(12804);
        internal_counters.push_back(13086);
        internal_counters.push_back(13368);
        internal_counters.push_back(13650);
        internal_counters.push_back(4060);
        internal_counters.push_back(4066);

        c.UpdateAsicSpecificDerivedCounter("CSWriteUnitStalledCycles", internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,17,+,ifnotzero");
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
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(128);
        internal_counters.push_back(572);
        internal_counters.push_back(1016);
        internal_counters.push_back(1460);

        c.UpdateAsicSpecificDerivedCounter("CBMemRead", internal_counters, "0,1,2,3,sum4,(32),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(259);
        internal_counters.push_back(703);
        internal_counters.push_back(1147);
        internal_counters.push_back(1591);
        internal_counters.push_back(126);
        internal_counters.push_back(570);
        internal_counters.push_back(1014);
        internal_counters.push_back(1458);
        internal_counters.push_back(127);
        internal_counters.push_back(571);
        internal_counters.push_back(1015);
        internal_counters.push_back(1459);
        internal_counters.push_back(128);
        internal_counters.push_back(572);
        internal_counters.push_back(1016);
        internal_counters.push_back(1460);

        c.UpdateAsicSpecificDerivedCounter("CBColorAndMaskRead", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(118);
        internal_counters.push_back(562);
        internal_counters.push_back(1006);
        internal_counters.push_back(1450);

        c.UpdateAsicSpecificDerivedCounter("CBMemWritten", internal_counters, "0,1,2,3,sum4,(32),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(257);
        internal_counters.push_back(701);
        internal_counters.push_back(1145);
        internal_counters.push_back(1589);
        internal_counters.push_back(116);
        internal_counters.push_back(560);
        internal_counters.push_back(1004);
        internal_counters.push_back(1448);
        internal_counters.push_back(117);
        internal_counters.push_back(561);
        internal_counters.push_back(1005);
        internal_counters.push_back(1449);
        internal_counters.push_back(118);
        internal_counters.push_back(562);
        internal_counters.push_back(1006);
        internal_counters.push_back(1450);

        c.UpdateAsicSpecificDerivedCounter("CBColorAndMaskWritten", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(162);
        internal_counters.push_back(606);
        internal_counters.push_back(1050);
        internal_counters.push_back(1494);
        internal_counters.push_back(7);
        internal_counters.push_back(451);
        internal_counters.push_back(895);
        internal_counters.push_back(1339);

        c.UpdateAsicSpecificDerivedCounter("CBSlowPixelPct", internal_counters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*,(100),min");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(162);
        internal_counters.push_back(606);
        internal_counters.push_back(1050);
        internal_counters.push_back(1494);

        c.UpdateAsicSpecificDerivedCounter("CBSlowPixelCount", internal_counters, "0,1,2,3,sum4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9428);
        internal_counters.push_back(9710);
        internal_counters.push_back(9992);
        internal_counters.push_back(10274);
        internal_counters.push_back(10556);
        internal_counters.push_back(10838);
        internal_counters.push_back(11120);
        internal_counters.push_back(11402);
        internal_counters.push_back(11684);
        internal_counters.push_back(11966);
        internal_counters.push_back(12248);
        internal_counters.push_back(12530);
        internal_counters.push_back(12812);
        internal_counters.push_back(13094);
        internal_counters.push_back(13376);
        internal_counters.push_back(13658);
        internal_counters.push_back(9429);
        internal_counters.push_back(9711);
        internal_counters.push_back(9993);
        internal_counters.push_back(10275);
        internal_counters.push_back(10557);
        internal_counters.push_back(10839);
        internal_counters.push_back(11121);
        internal_counters.push_back(11403);
        internal_counters.push_back(11685);
        internal_counters.push_back(11967);
        internal_counters.push_back(12249);
        internal_counters.push_back(12531);
        internal_counters.push_back(12813);
        internal_counters.push_back(13095);
        internal_counters.push_back(13377);
        internal_counters.push_back(13659);

        c.UpdateAsicSpecificDerivedCounter("FetchSize", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(64),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9416);
        internal_counters.push_back(9698);
        internal_counters.push_back(9980);
        internal_counters.push_back(10262);
        internal_counters.push_back(10544);
        internal_counters.push_back(10826);
        internal_counters.push_back(11108);
        internal_counters.push_back(11390);
        internal_counters.push_back(11672);
        internal_counters.push_back(11954);
        internal_counters.push_back(12236);
        internal_counters.push_back(12518);
        internal_counters.push_back(12800);
        internal_counters.push_back(13082);
        internal_counters.push_back(13364);
        internal_counters.push_back(13646);
        internal_counters.push_back(9417);
        internal_counters.push_back(9699);
        internal_counters.push_back(9981);
        internal_counters.push_back(10263);
        internal_counters.push_back(10545);
        internal_counters.push_back(10827);
        internal_counters.push_back(11109);
        internal_counters.push_back(11391);
        internal_counters.push_back(11673);
        internal_counters.push_back(11955);
        internal_counters.push_back(12237);
        internal_counters.push_back(12519);
        internal_counters.push_back(12801);
        internal_counters.push_back(13083);
        internal_counters.push_back(13365);
        internal_counters.push_back(13647);

        c.UpdateAsicSpecificDerivedCounter("WriteSize", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9407);
        internal_counters.push_back(9689);
        internal_counters.push_back(9971);
        internal_counters.push_back(10253);
        internal_counters.push_back(10535);
        internal_counters.push_back(10817);
        internal_counters.push_back(11099);
        internal_counters.push_back(11381);
        internal_counters.push_back(11663);
        internal_counters.push_back(11945);
        internal_counters.push_back(12227);
        internal_counters.push_back(12509);
        internal_counters.push_back(12791);
        internal_counters.push_back(13073);
        internal_counters.push_back(13355);
        internal_counters.push_back(13637);
        internal_counters.push_back(9409);
        internal_counters.push_back(9691);
        internal_counters.push_back(9973);
        internal_counters.push_back(10255);
        internal_counters.push_back(10537);
        internal_counters.push_back(10819);
        internal_counters.push_back(11101);
        internal_counters.push_back(11383);
        internal_counters.push_back(11665);
        internal_counters.push_back(11947);
        internal_counters.push_back(12229);
        internal_counters.push_back(12511);
        internal_counters.push_back(12793);
        internal_counters.push_back(13075);
        internal_counters.push_back(13357);
        internal_counters.push_back(13639);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHit", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9407);
        internal_counters.push_back(9689);
        internal_counters.push_back(9971);
        internal_counters.push_back(10253);
        internal_counters.push_back(10535);
        internal_counters.push_back(10817);
        internal_counters.push_back(11099);
        internal_counters.push_back(11381);
        internal_counters.push_back(11663);
        internal_counters.push_back(11945);
        internal_counters.push_back(12227);
        internal_counters.push_back(12509);
        internal_counters.push_back(12791);
        internal_counters.push_back(13073);
        internal_counters.push_back(13355);
        internal_counters.push_back(13637);
        internal_counters.push_back(9409);
        internal_counters.push_back(9691);
        internal_counters.push_back(9973);
        internal_counters.push_back(10255);
        internal_counters.push_back(10537);
        internal_counters.push_back(10819);
        internal_counters.push_back(11101);
        internal_counters.push_back(11383);
        internal_counters.push_back(11665);
        internal_counters.push_back(11947);
        internal_counters.push_back(12229);
        internal_counters.push_back(12511);
        internal_counters.push_back(12793);
        internal_counters.push_back(13075);
        internal_counters.push_back(13357);
        internal_counters.push_back(13639);

        c.UpdateAsicSpecificDerivedCounter("L2CacheMiss", internal_counters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9407);
        internal_counters.push_back(9689);
        internal_counters.push_back(9971);
        internal_counters.push_back(10253);
        internal_counters.push_back(10535);
        internal_counters.push_back(10817);
        internal_counters.push_back(11099);
        internal_counters.push_back(11381);
        internal_counters.push_back(11663);
        internal_counters.push_back(11945);
        internal_counters.push_back(12227);
        internal_counters.push_back(12509);
        internal_counters.push_back(12791);
        internal_counters.push_back(13073);
        internal_counters.push_back(13355);
        internal_counters.push_back(13637);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHitCount", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9409);
        internal_counters.push_back(9691);
        internal_counters.push_back(9973);
        internal_counters.push_back(10255);
        internal_counters.push_back(10537);
        internal_counters.push_back(10819);
        internal_counters.push_back(11101);
        internal_counters.push_back(11383);
        internal_counters.push_back(11665);
        internal_counters.push_back(11947);
        internal_counters.push_back(12229);
        internal_counters.push_back(12511);
        internal_counters.push_back(12793);
        internal_counters.push_back(13075);
        internal_counters.push_back(13357);
        internal_counters.push_back(13639);

        c.UpdateAsicSpecificDerivedCounter("L2CacheMissCount", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9420);
        internal_counters.push_back(9702);
        internal_counters.push_back(9984);
        internal_counters.push_back(10266);
        internal_counters.push_back(10548);
        internal_counters.push_back(10830);
        internal_counters.push_back(11112);
        internal_counters.push_back(11394);
        internal_counters.push_back(11676);
        internal_counters.push_back(11958);
        internal_counters.push_back(12240);
        internal_counters.push_back(12522);
        internal_counters.push_back(12804);
        internal_counters.push_back(13086);
        internal_counters.push_back(13368);
        internal_counters.push_back(13650);
        internal_counters.push_back(1799);

        c.UpdateAsicSpecificDerivedCounter("WriteUnitStalled", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9420);
        internal_counters.push_back(9702);
        internal_counters.push_back(9984);
        internal_counters.push_back(10266);
        internal_counters.push_back(10548);
        internal_counters.push_back(10830);
        internal_counters.push_back(11112);
        internal_counters.push_back(11394);
        internal_counters.push_back(11676);
        internal_counters.push_back(11958);
        internal_counters.push_back(12240);
        internal_counters.push_back(12522);
        internal_counters.push_back(12804);
        internal_counters.push_back(13086);
        internal_counters.push_back(13368);
        internal_counters.push_back(13650);

        c.UpdateAsicSpecificDerivedCounter("WriteUnitStalledCycles", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16");
    }
    return true;
}

}  // namespace gl_gfx9_gfx909

