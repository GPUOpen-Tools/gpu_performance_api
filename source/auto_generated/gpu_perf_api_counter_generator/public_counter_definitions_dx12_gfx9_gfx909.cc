//==============================================================================
// Copyright (c) 2010-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for DX12 GFX9_GFX909.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx12_gfx9_gfx909.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "auto_generated/gpu_perf_api_counter_generator/gpa_hw_counter_gfx9_gfx909.h"

namespace dx12_gfx9_gfx909
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
        internal_counters.push_back(696);
        internal_counters.push_back(1047);
        internal_counters.push_back(1398);
        internal_counters.push_back(1749);
        internal_counters.push_back(105);
        internal_counters.push_back(253);
        internal_counters.push_back(401);
        internal_counters.push_back(549);
        internal_counters.push_back(4098);
        internal_counters.push_back(4294);
        internal_counters.push_back(4490);
        internal_counters.push_back(4686);

        c.UpdateAsicSpecificDerivedCounter("VsGsPrimsIn", internal_counters, "0,1,2,3,sum4,4,5,6,7,sum4,4,5,6,7,sum4,ifnotzero,(0),8,9,10,11,sum4,ifnotzero");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(793);
        internal_counters.push_back(1144);
        internal_counters.push_back(1495);
        internal_counters.push_back(1846);
        internal_counters.push_back(797);
        internal_counters.push_back(1148);
        internal_counters.push_back(1499);
        internal_counters.push_back(1850);
        internal_counters.push_back(749);
        internal_counters.push_back(1100);
        internal_counters.push_back(1451);
        internal_counters.push_back(1802);
        internal_counters.push_back(761);
        internal_counters.push_back(1112);
        internal_counters.push_back(1463);
        internal_counters.push_back(1814);
        internal_counters.push_back(750);
        internal_counters.push_back(1101);
        internal_counters.push_back(1452);
        internal_counters.push_back(1803);
        internal_counters.push_back(762);
        internal_counters.push_back(1113);
        internal_counters.push_back(1464);
        internal_counters.push_back(1815);
        internal_counters.push_back(23);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusy", internal_counters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max,24,/,(100),*,(100),min");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(793);
        internal_counters.push_back(1144);
        internal_counters.push_back(1495);
        internal_counters.push_back(1846);
        internal_counters.push_back(797);
        internal_counters.push_back(1148);
        internal_counters.push_back(1499);
        internal_counters.push_back(1850);
        internal_counters.push_back(749);
        internal_counters.push_back(1100);
        internal_counters.push_back(1451);
        internal_counters.push_back(1802);
        internal_counters.push_back(761);
        internal_counters.push_back(1112);
        internal_counters.push_back(1463);
        internal_counters.push_back(1814);
        internal_counters.push_back(750);
        internal_counters.push_back(1101);
        internal_counters.push_back(1452);
        internal_counters.push_back(1803);
        internal_counters.push_back(762);
        internal_counters.push_back(1113);
        internal_counters.push_back(1464);
        internal_counters.push_back(1815);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusyCycles", internal_counters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(696);
        internal_counters.push_back(1047);
        internal_counters.push_back(1398);
        internal_counters.push_back(1749);

        c.UpdateAsicSpecificDerivedCounter("PrimitivesIn", internal_counters, "0,1,2,3,sum4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(702);
        internal_counters.push_back(1053);
        internal_counters.push_back(1404);
        internal_counters.push_back(1755);
        internal_counters.push_back(742);
        internal_counters.push_back(1093);
        internal_counters.push_back(1444);
        internal_counters.push_back(1795);
        internal_counters.push_back(743);
        internal_counters.push_back(1094);
        internal_counters.push_back(1445);
        internal_counters.push_back(1796);
        internal_counters.push_back(744);
        internal_counters.push_back(1095);
        internal_counters.push_back(1446);
        internal_counters.push_back(1797);
        internal_counters.push_back(745);
        internal_counters.push_back(1096);
        internal_counters.push_back(1447);
        internal_counters.push_back(1798);

        c.UpdateAsicSpecificDerivedCounter("CulledPrims", internal_counters, "0,1,+,2,+,3,+,4,+,5,+,6,+,7,+,8,+,9,+,10,+,11,+,12,+,13,+,14,+,15,+,16,+,17,+,18,+,19,+");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(709);
        internal_counters.push_back(1060);
        internal_counters.push_back(1411);
        internal_counters.push_back(1762);

        c.UpdateAsicSpecificDerivedCounter("ClippedPrims", internal_counters, "0,1,2,3,sum4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(797);
        internal_counters.push_back(1148);
        internal_counters.push_back(1499);
        internal_counters.push_back(1850);
        internal_counters.push_back(23);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizer", internal_counters, "0,1,max,2,max,3,max,4,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(797);
        internal_counters.push_back(1148);
        internal_counters.push_back(1499);
        internal_counters.push_back(1850);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizerCycles", internal_counters, "0,1,max,2,max,3,max");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(34381);
        internal_counters.push_back(34663);
        internal_counters.push_back(34945);
        internal_counters.push_back(35227);
        internal_counters.push_back(35509);
        internal_counters.push_back(35791);
        internal_counters.push_back(36073);
        internal_counters.push_back(36355);
        internal_counters.push_back(36637);
        internal_counters.push_back(36919);
        internal_counters.push_back(37201);
        internal_counters.push_back(37483);
        internal_counters.push_back(37765);
        internal_counters.push_back(38047);
        internal_counters.push_back(38329);
        internal_counters.push_back(38611);
        internal_counters.push_back(23);
        internal_counters.push_back(4103);
        internal_counters.push_back(4299);
        internal_counters.push_back(4495);
        internal_counters.push_back(4691);
        internal_counters.push_back(4109);
        internal_counters.push_back(4305);
        internal_counters.push_back(4501);
        internal_counters.push_back(4697);

        c.UpdateAsicSpecificDerivedCounter("CSWriteUnitStalled", internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,18,19,20,21,22,23,24,sum8,ifnotzero");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(34381);
        internal_counters.push_back(34663);
        internal_counters.push_back(34945);
        internal_counters.push_back(35227);
        internal_counters.push_back(35509);
        internal_counters.push_back(35791);
        internal_counters.push_back(36073);
        internal_counters.push_back(36355);
        internal_counters.push_back(36637);
        internal_counters.push_back(36919);
        internal_counters.push_back(37201);
        internal_counters.push_back(37483);
        internal_counters.push_back(37765);
        internal_counters.push_back(38047);
        internal_counters.push_back(38329);
        internal_counters.push_back(38611);
        internal_counters.push_back(4103);
        internal_counters.push_back(4299);
        internal_counters.push_back(4495);
        internal_counters.push_back(4691);
        internal_counters.push_back(4109);
        internal_counters.push_back(4305);
        internal_counters.push_back(4501);
        internal_counters.push_back(4697);

        c.UpdateAsicSpecificDerivedCounter("CSWriteUnitStalledCycles", internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,17,18,19,20,21,22,23,sum8,ifnotzero");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2251);
        internal_counters.push_back(2743);
        internal_counters.push_back(3235);
        internal_counters.push_back(3727);
        internal_counters.push_back(2252);
        internal_counters.push_back(2744);
        internal_counters.push_back(3236);
        internal_counters.push_back(3728);
        internal_counters.push_back(2253);
        internal_counters.push_back(2745);
        internal_counters.push_back(3237);
        internal_counters.push_back(3729);
        internal_counters.push_back(2254);
        internal_counters.push_back(2746);
        internal_counters.push_back(3238);
        internal_counters.push_back(3730);
        internal_counters.push_back(2327);
        internal_counters.push_back(2819);
        internal_counters.push_back(3311);
        internal_counters.push_back(3803);
        internal_counters.push_back(2328);
        internal_counters.push_back(2820);
        internal_counters.push_back(3312);
        internal_counters.push_back(3804);
        internal_counters.push_back(2329);
        internal_counters.push_back(2821);
        internal_counters.push_back(3313);
        internal_counters.push_back(3805);
        internal_counters.push_back(2330);
        internal_counters.push_back(2822);
        internal_counters.push_back(3314);
        internal_counters.push_back(3806);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulled", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(0),max,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2251);
        internal_counters.push_back(2743);
        internal_counters.push_back(3235);
        internal_counters.push_back(3727);
        internal_counters.push_back(2252);
        internal_counters.push_back(2744);
        internal_counters.push_back(3236);
        internal_counters.push_back(3728);
        internal_counters.push_back(2253);
        internal_counters.push_back(2745);
        internal_counters.push_back(3237);
        internal_counters.push_back(3729);
        internal_counters.push_back(2254);
        internal_counters.push_back(2746);
        internal_counters.push_back(3238);
        internal_counters.push_back(3730);
        internal_counters.push_back(2327);
        internal_counters.push_back(2819);
        internal_counters.push_back(3311);
        internal_counters.push_back(3803);
        internal_counters.push_back(2328);
        internal_counters.push_back(2820);
        internal_counters.push_back(3312);
        internal_counters.push_back(3804);
        internal_counters.push_back(2329);
        internal_counters.push_back(2821);
        internal_counters.push_back(3313);
        internal_counters.push_back(3805);
        internal_counters.push_back(2330);
        internal_counters.push_back(2822);
        internal_counters.push_back(3314);
        internal_counters.push_back(3806);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulledCount", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(0),max");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2327);
        internal_counters.push_back(2819);
        internal_counters.push_back(3311);
        internal_counters.push_back(3803);
        internal_counters.push_back(2328);
        internal_counters.push_back(2820);
        internal_counters.push_back(3312);
        internal_counters.push_back(3804);
        internal_counters.push_back(2329);
        internal_counters.push_back(2821);
        internal_counters.push_back(3313);
        internal_counters.push_back(3805);
        internal_counters.push_back(2330);
        internal_counters.push_back(2822);
        internal_counters.push_back(3314);
        internal_counters.push_back(3806);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsAcceptedCount", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2327);
        internal_counters.push_back(2819);
        internal_counters.push_back(3311);
        internal_counters.push_back(3803);
        internal_counters.push_back(2328);
        internal_counters.push_back(2820);
        internal_counters.push_back(3312);
        internal_counters.push_back(3804);
        internal_counters.push_back(2329);
        internal_counters.push_back(2821);
        internal_counters.push_back(3313);
        internal_counters.push_back(3805);
        internal_counters.push_back(2330);
        internal_counters.push_back(2822);
        internal_counters.push_back(3314);
        internal_counters.push_back(3806);
        internal_counters.push_back(2351);
        internal_counters.push_back(2843);
        internal_counters.push_back(3335);
        internal_counters.push_back(3827);
        internal_counters.push_back(2251);
        internal_counters.push_back(2743);
        internal_counters.push_back(3235);
        internal_counters.push_back(3727);
        internal_counters.push_back(2252);
        internal_counters.push_back(2744);
        internal_counters.push_back(3236);
        internal_counters.push_back(3728);
        internal_counters.push_back(2253);
        internal_counters.push_back(2745);
        internal_counters.push_back(3237);
        internal_counters.push_back(3729);
        internal_counters.push_back(2254);
        internal_counters.push_back(2746);
        internal_counters.push_back(3238);
        internal_counters.push_back(3730);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulled", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,sum4,-,(0),max,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,sum16,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2327);
        internal_counters.push_back(2819);
        internal_counters.push_back(3311);
        internal_counters.push_back(3803);
        internal_counters.push_back(2328);
        internal_counters.push_back(2820);
        internal_counters.push_back(3312);
        internal_counters.push_back(3804);
        internal_counters.push_back(2329);
        internal_counters.push_back(2821);
        internal_counters.push_back(3313);
        internal_counters.push_back(3805);
        internal_counters.push_back(2330);
        internal_counters.push_back(2822);
        internal_counters.push_back(3314);
        internal_counters.push_back(3806);
        internal_counters.push_back(2351);
        internal_counters.push_back(2843);
        internal_counters.push_back(3335);
        internal_counters.push_back(3827);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulledCount", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,sum4,-,(0),max");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2351);
        internal_counters.push_back(2843);
        internal_counters.push_back(3335);
        internal_counters.push_back(3827);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsSurvivingCount", internal_counters, "0,1,2,3,sum4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2351);
        internal_counters.push_back(2843);
        internal_counters.push_back(3335);
        internal_counters.push_back(3827);
        internal_counters.push_back(2251);
        internal_counters.push_back(2743);
        internal_counters.push_back(3235);
        internal_counters.push_back(3727);
        internal_counters.push_back(2252);
        internal_counters.push_back(2744);
        internal_counters.push_back(3236);
        internal_counters.push_back(3728);
        internal_counters.push_back(2253);
        internal_counters.push_back(2745);
        internal_counters.push_back(3237);
        internal_counters.push_back(3729);
        internal_counters.push_back(2254);
        internal_counters.push_back(2746);
        internal_counters.push_back(3238);
        internal_counters.push_back(3730);

        c.UpdateAsicSpecificDerivedCounter("PostZQuads", internal_counters, "0,1,2,3,sum4,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,sum16,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2351);
        internal_counters.push_back(2843);
        internal_counters.push_back(3335);
        internal_counters.push_back(3827);

        c.UpdateAsicSpecificDerivedCounter("PostZQuadCount", internal_counters, "0,1,2,3,sum4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(44306);
        internal_counters.push_back(44750);
        internal_counters.push_back(45194);
        internal_counters.push_back(45638);
        internal_counters.push_back(46082);
        internal_counters.push_back(46526);
        internal_counters.push_back(46970);
        internal_counters.push_back(47414);
        internal_counters.push_back(47858);
        internal_counters.push_back(48302);
        internal_counters.push_back(48746);
        internal_counters.push_back(49190);
        internal_counters.push_back(49634);
        internal_counters.push_back(50078);
        internal_counters.push_back(50522);
        internal_counters.push_back(50966);

        c.UpdateAsicSpecificDerivedCounter("CBMemRead", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(44437);
        internal_counters.push_back(44881);
        internal_counters.push_back(45325);
        internal_counters.push_back(45769);
        internal_counters.push_back(46213);
        internal_counters.push_back(46657);
        internal_counters.push_back(47101);
        internal_counters.push_back(47545);
        internal_counters.push_back(47989);
        internal_counters.push_back(48433);
        internal_counters.push_back(48877);
        internal_counters.push_back(49321);
        internal_counters.push_back(49765);
        internal_counters.push_back(50209);
        internal_counters.push_back(50653);
        internal_counters.push_back(51097);
        internal_counters.push_back(44304);
        internal_counters.push_back(44748);
        internal_counters.push_back(45192);
        internal_counters.push_back(45636);
        internal_counters.push_back(46080);
        internal_counters.push_back(46524);
        internal_counters.push_back(46968);
        internal_counters.push_back(47412);
        internal_counters.push_back(47856);
        internal_counters.push_back(48300);
        internal_counters.push_back(48744);
        internal_counters.push_back(49188);
        internal_counters.push_back(49632);
        internal_counters.push_back(50076);
        internal_counters.push_back(50520);
        internal_counters.push_back(50964);
        internal_counters.push_back(44305);
        internal_counters.push_back(44749);
        internal_counters.push_back(45193);
        internal_counters.push_back(45637);
        internal_counters.push_back(46081);
        internal_counters.push_back(46525);
        internal_counters.push_back(46969);
        internal_counters.push_back(47413);
        internal_counters.push_back(47857);
        internal_counters.push_back(48301);
        internal_counters.push_back(48745);
        internal_counters.push_back(49189);
        internal_counters.push_back(49633);
        internal_counters.push_back(50077);
        internal_counters.push_back(50521);
        internal_counters.push_back(50965);
        internal_counters.push_back(44306);
        internal_counters.push_back(44750);
        internal_counters.push_back(45194);
        internal_counters.push_back(45638);
        internal_counters.push_back(46082);
        internal_counters.push_back(46526);
        internal_counters.push_back(46970);
        internal_counters.push_back(47414);
        internal_counters.push_back(47858);
        internal_counters.push_back(48302);
        internal_counters.push_back(48746);
        internal_counters.push_back(49190);
        internal_counters.push_back(49634);
        internal_counters.push_back(50078);
        internal_counters.push_back(50522);
        internal_counters.push_back(50966);

        c.UpdateAsicSpecificDerivedCounter("CBColorAndMaskRead", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(44296);
        internal_counters.push_back(44740);
        internal_counters.push_back(45184);
        internal_counters.push_back(45628);
        internal_counters.push_back(46072);
        internal_counters.push_back(46516);
        internal_counters.push_back(46960);
        internal_counters.push_back(47404);
        internal_counters.push_back(47848);
        internal_counters.push_back(48292);
        internal_counters.push_back(48736);
        internal_counters.push_back(49180);
        internal_counters.push_back(49624);
        internal_counters.push_back(50068);
        internal_counters.push_back(50512);
        internal_counters.push_back(50956);

        c.UpdateAsicSpecificDerivedCounter("CBMemWritten", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(44435);
        internal_counters.push_back(44879);
        internal_counters.push_back(45323);
        internal_counters.push_back(45767);
        internal_counters.push_back(46211);
        internal_counters.push_back(46655);
        internal_counters.push_back(47099);
        internal_counters.push_back(47543);
        internal_counters.push_back(47987);
        internal_counters.push_back(48431);
        internal_counters.push_back(48875);
        internal_counters.push_back(49319);
        internal_counters.push_back(49763);
        internal_counters.push_back(50207);
        internal_counters.push_back(50651);
        internal_counters.push_back(51095);
        internal_counters.push_back(44294);
        internal_counters.push_back(44738);
        internal_counters.push_back(45182);
        internal_counters.push_back(45626);
        internal_counters.push_back(46070);
        internal_counters.push_back(46514);
        internal_counters.push_back(46958);
        internal_counters.push_back(47402);
        internal_counters.push_back(47846);
        internal_counters.push_back(48290);
        internal_counters.push_back(48734);
        internal_counters.push_back(49178);
        internal_counters.push_back(49622);
        internal_counters.push_back(50066);
        internal_counters.push_back(50510);
        internal_counters.push_back(50954);
        internal_counters.push_back(44295);
        internal_counters.push_back(44739);
        internal_counters.push_back(45183);
        internal_counters.push_back(45627);
        internal_counters.push_back(46071);
        internal_counters.push_back(46515);
        internal_counters.push_back(46959);
        internal_counters.push_back(47403);
        internal_counters.push_back(47847);
        internal_counters.push_back(48291);
        internal_counters.push_back(48735);
        internal_counters.push_back(49179);
        internal_counters.push_back(49623);
        internal_counters.push_back(50067);
        internal_counters.push_back(50511);
        internal_counters.push_back(50955);
        internal_counters.push_back(44296);
        internal_counters.push_back(44740);
        internal_counters.push_back(45184);
        internal_counters.push_back(45628);
        internal_counters.push_back(46072);
        internal_counters.push_back(46516);
        internal_counters.push_back(46960);
        internal_counters.push_back(47404);
        internal_counters.push_back(47848);
        internal_counters.push_back(48292);
        internal_counters.push_back(48736);
        internal_counters.push_back(49180);
        internal_counters.push_back(49624);
        internal_counters.push_back(50068);
        internal_counters.push_back(50512);
        internal_counters.push_back(50956);

        c.UpdateAsicSpecificDerivedCounter("CBColorAndMaskWritten", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(44340);
        internal_counters.push_back(44784);
        internal_counters.push_back(45228);
        internal_counters.push_back(45672);
        internal_counters.push_back(46116);
        internal_counters.push_back(46560);
        internal_counters.push_back(47004);
        internal_counters.push_back(47448);
        internal_counters.push_back(47892);
        internal_counters.push_back(48336);
        internal_counters.push_back(48780);
        internal_counters.push_back(49224);
        internal_counters.push_back(49668);
        internal_counters.push_back(50112);
        internal_counters.push_back(50556);
        internal_counters.push_back(51000);
        internal_counters.push_back(44185);
        internal_counters.push_back(44629);
        internal_counters.push_back(45073);
        internal_counters.push_back(45517);
        internal_counters.push_back(45961);
        internal_counters.push_back(46405);
        internal_counters.push_back(46849);
        internal_counters.push_back(47293);
        internal_counters.push_back(47737);
        internal_counters.push_back(48181);
        internal_counters.push_back(48625);
        internal_counters.push_back(49069);
        internal_counters.push_back(49513);
        internal_counters.push_back(49957);
        internal_counters.push_back(50401);
        internal_counters.push_back(50845);

        c.UpdateAsicSpecificDerivedCounter("CBSlowPixelPct", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*,(100),min");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(44340);
        internal_counters.push_back(44784);
        internal_counters.push_back(45228);
        internal_counters.push_back(45672);
        internal_counters.push_back(46116);
        internal_counters.push_back(46560);
        internal_counters.push_back(47004);
        internal_counters.push_back(47448);
        internal_counters.push_back(47892);
        internal_counters.push_back(48336);
        internal_counters.push_back(48780);
        internal_counters.push_back(49224);
        internal_counters.push_back(49668);
        internal_counters.push_back(50112);
        internal_counters.push_back(50556);
        internal_counters.push_back(51000);

        c.UpdateAsicSpecificDerivedCounter("CBSlowPixelCount", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(34389);
        internal_counters.push_back(34671);
        internal_counters.push_back(34953);
        internal_counters.push_back(35235);
        internal_counters.push_back(35517);
        internal_counters.push_back(35799);
        internal_counters.push_back(36081);
        internal_counters.push_back(36363);
        internal_counters.push_back(36645);
        internal_counters.push_back(36927);
        internal_counters.push_back(37209);
        internal_counters.push_back(37491);
        internal_counters.push_back(37773);
        internal_counters.push_back(38055);
        internal_counters.push_back(38337);
        internal_counters.push_back(38619);
        internal_counters.push_back(34390);
        internal_counters.push_back(34672);
        internal_counters.push_back(34954);
        internal_counters.push_back(35236);
        internal_counters.push_back(35518);
        internal_counters.push_back(35800);
        internal_counters.push_back(36082);
        internal_counters.push_back(36364);
        internal_counters.push_back(36646);
        internal_counters.push_back(36928);
        internal_counters.push_back(37210);
        internal_counters.push_back(37492);
        internal_counters.push_back(37774);
        internal_counters.push_back(38056);
        internal_counters.push_back(38338);
        internal_counters.push_back(38620);

        c.UpdateAsicSpecificDerivedCounter("FetchSize", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(64),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(34377);
        internal_counters.push_back(34659);
        internal_counters.push_back(34941);
        internal_counters.push_back(35223);
        internal_counters.push_back(35505);
        internal_counters.push_back(35787);
        internal_counters.push_back(36069);
        internal_counters.push_back(36351);
        internal_counters.push_back(36633);
        internal_counters.push_back(36915);
        internal_counters.push_back(37197);
        internal_counters.push_back(37479);
        internal_counters.push_back(37761);
        internal_counters.push_back(38043);
        internal_counters.push_back(38325);
        internal_counters.push_back(38607);
        internal_counters.push_back(34378);
        internal_counters.push_back(34660);
        internal_counters.push_back(34942);
        internal_counters.push_back(35224);
        internal_counters.push_back(35506);
        internal_counters.push_back(35788);
        internal_counters.push_back(36070);
        internal_counters.push_back(36352);
        internal_counters.push_back(36634);
        internal_counters.push_back(36916);
        internal_counters.push_back(37198);
        internal_counters.push_back(37480);
        internal_counters.push_back(37762);
        internal_counters.push_back(38044);
        internal_counters.push_back(38326);
        internal_counters.push_back(38608);

        c.UpdateAsicSpecificDerivedCounter("WriteSize", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(34368);
        internal_counters.push_back(34650);
        internal_counters.push_back(34932);
        internal_counters.push_back(35214);
        internal_counters.push_back(35496);
        internal_counters.push_back(35778);
        internal_counters.push_back(36060);
        internal_counters.push_back(36342);
        internal_counters.push_back(36624);
        internal_counters.push_back(36906);
        internal_counters.push_back(37188);
        internal_counters.push_back(37470);
        internal_counters.push_back(37752);
        internal_counters.push_back(38034);
        internal_counters.push_back(38316);
        internal_counters.push_back(38598);
        internal_counters.push_back(34370);
        internal_counters.push_back(34652);
        internal_counters.push_back(34934);
        internal_counters.push_back(35216);
        internal_counters.push_back(35498);
        internal_counters.push_back(35780);
        internal_counters.push_back(36062);
        internal_counters.push_back(36344);
        internal_counters.push_back(36626);
        internal_counters.push_back(36908);
        internal_counters.push_back(37190);
        internal_counters.push_back(37472);
        internal_counters.push_back(37754);
        internal_counters.push_back(38036);
        internal_counters.push_back(38318);
        internal_counters.push_back(38600);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHit", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(34368);
        internal_counters.push_back(34650);
        internal_counters.push_back(34932);
        internal_counters.push_back(35214);
        internal_counters.push_back(35496);
        internal_counters.push_back(35778);
        internal_counters.push_back(36060);
        internal_counters.push_back(36342);
        internal_counters.push_back(36624);
        internal_counters.push_back(36906);
        internal_counters.push_back(37188);
        internal_counters.push_back(37470);
        internal_counters.push_back(37752);
        internal_counters.push_back(38034);
        internal_counters.push_back(38316);
        internal_counters.push_back(38598);
        internal_counters.push_back(34370);
        internal_counters.push_back(34652);
        internal_counters.push_back(34934);
        internal_counters.push_back(35216);
        internal_counters.push_back(35498);
        internal_counters.push_back(35780);
        internal_counters.push_back(36062);
        internal_counters.push_back(36344);
        internal_counters.push_back(36626);
        internal_counters.push_back(36908);
        internal_counters.push_back(37190);
        internal_counters.push_back(37472);
        internal_counters.push_back(37754);
        internal_counters.push_back(38036);
        internal_counters.push_back(38318);
        internal_counters.push_back(38600);

        c.UpdateAsicSpecificDerivedCounter("L2CacheMiss", internal_counters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(34368);
        internal_counters.push_back(34650);
        internal_counters.push_back(34932);
        internal_counters.push_back(35214);
        internal_counters.push_back(35496);
        internal_counters.push_back(35778);
        internal_counters.push_back(36060);
        internal_counters.push_back(36342);
        internal_counters.push_back(36624);
        internal_counters.push_back(36906);
        internal_counters.push_back(37188);
        internal_counters.push_back(37470);
        internal_counters.push_back(37752);
        internal_counters.push_back(38034);
        internal_counters.push_back(38316);
        internal_counters.push_back(38598);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHitCount", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(34370);
        internal_counters.push_back(34652);
        internal_counters.push_back(34934);
        internal_counters.push_back(35216);
        internal_counters.push_back(35498);
        internal_counters.push_back(35780);
        internal_counters.push_back(36062);
        internal_counters.push_back(36344);
        internal_counters.push_back(36626);
        internal_counters.push_back(36908);
        internal_counters.push_back(37190);
        internal_counters.push_back(37472);
        internal_counters.push_back(37754);
        internal_counters.push_back(38036);
        internal_counters.push_back(38318);
        internal_counters.push_back(38600);

        c.UpdateAsicSpecificDerivedCounter("L2CacheMissCount", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(34381);
        internal_counters.push_back(34663);
        internal_counters.push_back(34945);
        internal_counters.push_back(35227);
        internal_counters.push_back(35509);
        internal_counters.push_back(35791);
        internal_counters.push_back(36073);
        internal_counters.push_back(36355);
        internal_counters.push_back(36637);
        internal_counters.push_back(36919);
        internal_counters.push_back(37201);
        internal_counters.push_back(37483);
        internal_counters.push_back(37765);
        internal_counters.push_back(38047);
        internal_counters.push_back(38329);
        internal_counters.push_back(38611);
        internal_counters.push_back(23);

        c.UpdateAsicSpecificDerivedCounter("WriteUnitStalled", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(34381);
        internal_counters.push_back(34663);
        internal_counters.push_back(34945);
        internal_counters.push_back(35227);
        internal_counters.push_back(35509);
        internal_counters.push_back(35791);
        internal_counters.push_back(36073);
        internal_counters.push_back(36355);
        internal_counters.push_back(36637);
        internal_counters.push_back(36919);
        internal_counters.push_back(37201);
        internal_counters.push_back(37483);
        internal_counters.push_back(37765);
        internal_counters.push_back(38047);
        internal_counters.push_back(38329);
        internal_counters.push_back(38611);

        c.UpdateAsicSpecificDerivedCounter("WriteUnitStalledCycles", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(51967);
        internal_counters.push_back(52050);
        internal_counters.push_back(52133);
        internal_counters.push_back(52216);
        internal_counters.push_back(52299);
        internal_counters.push_back(52382);
        internal_counters.push_back(52465);
        internal_counters.push_back(52548);
        internal_counters.push_back(52631);
        internal_counters.push_back(52714);
        internal_counters.push_back(52797);
        internal_counters.push_back(52880);
        internal_counters.push_back(52963);
        internal_counters.push_back(53046);
        internal_counters.push_back(53129);
        internal_counters.push_back(53212);

        c.UpdateAsicSpecificDerivedCounter("LocalVidMemBytes", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(51969);
        internal_counters.push_back(52052);
        internal_counters.push_back(52135);
        internal_counters.push_back(52218);
        internal_counters.push_back(52301);
        internal_counters.push_back(52384);
        internal_counters.push_back(52467);
        internal_counters.push_back(52550);
        internal_counters.push_back(52633);
        internal_counters.push_back(52716);
        internal_counters.push_back(52799);
        internal_counters.push_back(52882);
        internal_counters.push_back(52965);
        internal_counters.push_back(53048);
        internal_counters.push_back(53131);
        internal_counters.push_back(53214);

        c.UpdateAsicSpecificDerivedCounter("PcieBytes", internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    return true;
}

}  // namespace dx12_gfx9_gfx909

