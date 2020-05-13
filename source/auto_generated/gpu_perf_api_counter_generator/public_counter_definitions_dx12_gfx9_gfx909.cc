//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions for DX12 GFX9 _gfx909
//==============================================================================

#include "gpa_counter.h"
#include "public_counter_definitions_dx12_gfx9_gfx909.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "gpa_hw_counter_gfx9_gfx909.h"

namespace dx12gfx9gfx909
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GPA_DerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!countergfx9gfx909::MatchAsic(asic_type))
    {
        return false;
    }

    countergfx9gfx909::OverrideBlockInstanceCounters(asic_type);

    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(793);
        internalCounters.push_back(1144);
        internalCounters.push_back(1495);
        internalCounters.push_back(1846);
        internalCounters.push_back(797);
        internalCounters.push_back(1148);
        internalCounters.push_back(1499);
        internalCounters.push_back(1850);
        internalCounters.push_back(749);
        internalCounters.push_back(1100);
        internalCounters.push_back(1451);
        internalCounters.push_back(1802);
        internalCounters.push_back(761);
        internalCounters.push_back(1112);
        internalCounters.push_back(1463);
        internalCounters.push_back(1814);
        internalCounters.push_back(750);
        internalCounters.push_back(1101);
        internalCounters.push_back(1452);
        internalCounters.push_back(1803);
        internalCounters.push_back(762);
        internalCounters.push_back(1113);
        internalCounters.push_back(1464);
        internalCounters.push_back(1815);
        internalCounters.push_back(23);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusy", internalCounters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max,24,/,(100),*,(100),min");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(793);
        internalCounters.push_back(1144);
        internalCounters.push_back(1495);
        internalCounters.push_back(1846);
        internalCounters.push_back(797);
        internalCounters.push_back(1148);
        internalCounters.push_back(1499);
        internalCounters.push_back(1850);
        internalCounters.push_back(749);
        internalCounters.push_back(1100);
        internalCounters.push_back(1451);
        internalCounters.push_back(1802);
        internalCounters.push_back(761);
        internalCounters.push_back(1112);
        internalCounters.push_back(1463);
        internalCounters.push_back(1814);
        internalCounters.push_back(750);
        internalCounters.push_back(1101);
        internalCounters.push_back(1452);
        internalCounters.push_back(1803);
        internalCounters.push_back(762);
        internalCounters.push_back(1113);
        internalCounters.push_back(1464);
        internalCounters.push_back(1815);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusyCycles", internalCounters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(696);
        internalCounters.push_back(1047);
        internalCounters.push_back(1398);
        internalCounters.push_back(1749);

        c.UpdateAsicSpecificDerivedCounter("PrimitivesIn", internalCounters, "0,1,2,3,sum4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(702);
        internalCounters.push_back(1053);
        internalCounters.push_back(1404);
        internalCounters.push_back(1755);
        internalCounters.push_back(742);
        internalCounters.push_back(1093);
        internalCounters.push_back(1444);
        internalCounters.push_back(1795);
        internalCounters.push_back(743);
        internalCounters.push_back(1094);
        internalCounters.push_back(1445);
        internalCounters.push_back(1796);
        internalCounters.push_back(744);
        internalCounters.push_back(1095);
        internalCounters.push_back(1446);
        internalCounters.push_back(1797);
        internalCounters.push_back(745);
        internalCounters.push_back(1096);
        internalCounters.push_back(1447);
        internalCounters.push_back(1798);

        c.UpdateAsicSpecificDerivedCounter("CulledPrims", internalCounters, "0,1,+,2,+,3,+,4,+,5,+,6,+,7,+,8,+,9,+,10,+,11,+,12,+,13,+,14,+,15,+,16,+,17,+,18,+,19,+");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(709);
        internalCounters.push_back(1060);
        internalCounters.push_back(1411);
        internalCounters.push_back(1762);

        c.UpdateAsicSpecificDerivedCounter("ClippedPrims", internalCounters, "0,1,2,3,sum4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(797);
        internalCounters.push_back(1148);
        internalCounters.push_back(1499);
        internalCounters.push_back(1850);
        internalCounters.push_back(23);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizer", internalCounters, "0,1,max,2,max,3,max,4,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(797);
        internalCounters.push_back(1148);
        internalCounters.push_back(1499);
        internalCounters.push_back(1850);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizerCycles", internalCounters, "0,1,max,2,max,3,max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(34381);
        internalCounters.push_back(34663);
        internalCounters.push_back(34945);
        internalCounters.push_back(35227);
        internalCounters.push_back(35509);
        internalCounters.push_back(35791);
        internalCounters.push_back(36073);
        internalCounters.push_back(36355);
        internalCounters.push_back(36637);
        internalCounters.push_back(36919);
        internalCounters.push_back(37201);
        internalCounters.push_back(37483);
        internalCounters.push_back(37765);
        internalCounters.push_back(38047);
        internalCounters.push_back(38329);
        internalCounters.push_back(38611);
        internalCounters.push_back(23);
        internalCounters.push_back(4103);
        internalCounters.push_back(4299);
        internalCounters.push_back(4495);
        internalCounters.push_back(4691);
        internalCounters.push_back(4109);
        internalCounters.push_back(4305);
        internalCounters.push_back(4501);
        internalCounters.push_back(4697);

        c.UpdateAsicSpecificDerivedCounter("CSWriteUnitStalled", internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,18,19,20,21,22,23,24,sum8,ifnotzero");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(34381);
        internalCounters.push_back(34663);
        internalCounters.push_back(34945);
        internalCounters.push_back(35227);
        internalCounters.push_back(35509);
        internalCounters.push_back(35791);
        internalCounters.push_back(36073);
        internalCounters.push_back(36355);
        internalCounters.push_back(36637);
        internalCounters.push_back(36919);
        internalCounters.push_back(37201);
        internalCounters.push_back(37483);
        internalCounters.push_back(37765);
        internalCounters.push_back(38047);
        internalCounters.push_back(38329);
        internalCounters.push_back(38611);
        internalCounters.push_back(4103);
        internalCounters.push_back(4299);
        internalCounters.push_back(4495);
        internalCounters.push_back(4691);
        internalCounters.push_back(4109);
        internalCounters.push_back(4305);
        internalCounters.push_back(4501);
        internalCounters.push_back(4697);

        c.UpdateAsicSpecificDerivedCounter("CSWriteUnitStalledCycles", internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,17,18,19,20,21,22,23,sum8,ifnotzero");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2251);
        internalCounters.push_back(2743);
        internalCounters.push_back(3235);
        internalCounters.push_back(3727);
        internalCounters.push_back(2252);
        internalCounters.push_back(2744);
        internalCounters.push_back(3236);
        internalCounters.push_back(3728);
        internalCounters.push_back(2253);
        internalCounters.push_back(2745);
        internalCounters.push_back(3237);
        internalCounters.push_back(3729);
        internalCounters.push_back(2254);
        internalCounters.push_back(2746);
        internalCounters.push_back(3238);
        internalCounters.push_back(3730);
        internalCounters.push_back(2327);
        internalCounters.push_back(2819);
        internalCounters.push_back(3311);
        internalCounters.push_back(3803);
        internalCounters.push_back(2328);
        internalCounters.push_back(2820);
        internalCounters.push_back(3312);
        internalCounters.push_back(3804);
        internalCounters.push_back(2329);
        internalCounters.push_back(2821);
        internalCounters.push_back(3313);
        internalCounters.push_back(3805);
        internalCounters.push_back(2330);
        internalCounters.push_back(2822);
        internalCounters.push_back(3314);
        internalCounters.push_back(3806);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulled", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(0),max,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2251);
        internalCounters.push_back(2743);
        internalCounters.push_back(3235);
        internalCounters.push_back(3727);
        internalCounters.push_back(2252);
        internalCounters.push_back(2744);
        internalCounters.push_back(3236);
        internalCounters.push_back(3728);
        internalCounters.push_back(2253);
        internalCounters.push_back(2745);
        internalCounters.push_back(3237);
        internalCounters.push_back(3729);
        internalCounters.push_back(2254);
        internalCounters.push_back(2746);
        internalCounters.push_back(3238);
        internalCounters.push_back(3730);
        internalCounters.push_back(2327);
        internalCounters.push_back(2819);
        internalCounters.push_back(3311);
        internalCounters.push_back(3803);
        internalCounters.push_back(2328);
        internalCounters.push_back(2820);
        internalCounters.push_back(3312);
        internalCounters.push_back(3804);
        internalCounters.push_back(2329);
        internalCounters.push_back(2821);
        internalCounters.push_back(3313);
        internalCounters.push_back(3805);
        internalCounters.push_back(2330);
        internalCounters.push_back(2822);
        internalCounters.push_back(3314);
        internalCounters.push_back(3806);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulledCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2327);
        internalCounters.push_back(2819);
        internalCounters.push_back(3311);
        internalCounters.push_back(3803);
        internalCounters.push_back(2328);
        internalCounters.push_back(2820);
        internalCounters.push_back(3312);
        internalCounters.push_back(3804);
        internalCounters.push_back(2329);
        internalCounters.push_back(2821);
        internalCounters.push_back(3313);
        internalCounters.push_back(3805);
        internalCounters.push_back(2330);
        internalCounters.push_back(2822);
        internalCounters.push_back(3314);
        internalCounters.push_back(3806);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsAcceptedCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2251);
        internalCounters.push_back(2743);
        internalCounters.push_back(3235);
        internalCounters.push_back(3727);
        internalCounters.push_back(2252);
        internalCounters.push_back(2744);
        internalCounters.push_back(3236);
        internalCounters.push_back(3728);
        internalCounters.push_back(2253);
        internalCounters.push_back(2745);
        internalCounters.push_back(3237);
        internalCounters.push_back(3729);
        internalCounters.push_back(2254);
        internalCounters.push_back(2746);
        internalCounters.push_back(3238);
        internalCounters.push_back(3730);
        internalCounters.push_back(2351);
        internalCounters.push_back(2843);
        internalCounters.push_back(3335);
        internalCounters.push_back(3827);
        internalCounters.push_back(2327);
        internalCounters.push_back(2819);
        internalCounters.push_back(3311);
        internalCounters.push_back(3803);
        internalCounters.push_back(2328);
        internalCounters.push_back(2820);
        internalCounters.push_back(3312);
        internalCounters.push_back(3804);
        internalCounters.push_back(2329);
        internalCounters.push_back(2821);
        internalCounters.push_back(3313);
        internalCounters.push_back(3805);
        internalCounters.push_back(2330);
        internalCounters.push_back(2822);
        internalCounters.push_back(3314);
        internalCounters.push_back(3806);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulled", internalCounters, "20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,sum16,16,17,18,19,sum4,-,(0),max,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2251);
        internalCounters.push_back(2743);
        internalCounters.push_back(3235);
        internalCounters.push_back(3727);
        internalCounters.push_back(2252);
        internalCounters.push_back(2744);
        internalCounters.push_back(3236);
        internalCounters.push_back(3728);
        internalCounters.push_back(2253);
        internalCounters.push_back(2745);
        internalCounters.push_back(3237);
        internalCounters.push_back(3729);
        internalCounters.push_back(2254);
        internalCounters.push_back(2746);
        internalCounters.push_back(3238);
        internalCounters.push_back(3730);
        internalCounters.push_back(2351);
        internalCounters.push_back(2843);
        internalCounters.push_back(3335);
        internalCounters.push_back(3827);
        internalCounters.push_back(2327);
        internalCounters.push_back(2819);
        internalCounters.push_back(3311);
        internalCounters.push_back(3803);
        internalCounters.push_back(2328);
        internalCounters.push_back(2820);
        internalCounters.push_back(3312);
        internalCounters.push_back(3804);
        internalCounters.push_back(2329);
        internalCounters.push_back(2821);
        internalCounters.push_back(3313);
        internalCounters.push_back(3805);
        internalCounters.push_back(2330);
        internalCounters.push_back(2822);
        internalCounters.push_back(3314);
        internalCounters.push_back(3806);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulledCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,sum4,-,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,sum16,-,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2351);
        internalCounters.push_back(2843);
        internalCounters.push_back(3335);
        internalCounters.push_back(3827);
        internalCounters.push_back(2327);
        internalCounters.push_back(2819);
        internalCounters.push_back(3311);
        internalCounters.push_back(3803);
        internalCounters.push_back(2328);
        internalCounters.push_back(2820);
        internalCounters.push_back(3312);
        internalCounters.push_back(3804);
        internalCounters.push_back(2329);
        internalCounters.push_back(2821);
        internalCounters.push_back(3313);
        internalCounters.push_back(3805);
        internalCounters.push_back(2330);
        internalCounters.push_back(2822);
        internalCounters.push_back(3314);
        internalCounters.push_back(3806);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsSurvivingCount", internalCounters, "4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,sum16,0,1,2,3,sum4,-,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2351);
        internalCounters.push_back(2843);
        internalCounters.push_back(3335);
        internalCounters.push_back(3827);
        internalCounters.push_back(2251);
        internalCounters.push_back(2743);
        internalCounters.push_back(3235);
        internalCounters.push_back(3727);
        internalCounters.push_back(2252);
        internalCounters.push_back(2744);
        internalCounters.push_back(3236);
        internalCounters.push_back(3728);
        internalCounters.push_back(2253);
        internalCounters.push_back(2745);
        internalCounters.push_back(3237);
        internalCounters.push_back(3729);
        internalCounters.push_back(2254);
        internalCounters.push_back(2746);
        internalCounters.push_back(3238);
        internalCounters.push_back(3730);

        c.UpdateAsicSpecificDerivedCounter("PostZQuads", internalCounters, "0,1,2,3,sum4,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,sum16,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2351);
        internalCounters.push_back(2843);
        internalCounters.push_back(3335);
        internalCounters.push_back(3827);

        c.UpdateAsicSpecificDerivedCounter("PostZQuadCount", internalCounters, "0,1,2,3,sum4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(44306);
        internalCounters.push_back(44750);
        internalCounters.push_back(45194);
        internalCounters.push_back(45638);
        internalCounters.push_back(46082);
        internalCounters.push_back(46526);
        internalCounters.push_back(46970);
        internalCounters.push_back(47414);
        internalCounters.push_back(47858);
        internalCounters.push_back(48302);
        internalCounters.push_back(48746);
        internalCounters.push_back(49190);
        internalCounters.push_back(49634);
        internalCounters.push_back(50078);
        internalCounters.push_back(50522);
        internalCounters.push_back(50966);

        c.UpdateAsicSpecificDerivedCounter("CBMemRead", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(44437);
        internalCounters.push_back(44881);
        internalCounters.push_back(45325);
        internalCounters.push_back(45769);
        internalCounters.push_back(46213);
        internalCounters.push_back(46657);
        internalCounters.push_back(47101);
        internalCounters.push_back(47545);
        internalCounters.push_back(47989);
        internalCounters.push_back(48433);
        internalCounters.push_back(48877);
        internalCounters.push_back(49321);
        internalCounters.push_back(49765);
        internalCounters.push_back(50209);
        internalCounters.push_back(50653);
        internalCounters.push_back(51097);
        internalCounters.push_back(44304);
        internalCounters.push_back(44748);
        internalCounters.push_back(45192);
        internalCounters.push_back(45636);
        internalCounters.push_back(46080);
        internalCounters.push_back(46524);
        internalCounters.push_back(46968);
        internalCounters.push_back(47412);
        internalCounters.push_back(47856);
        internalCounters.push_back(48300);
        internalCounters.push_back(48744);
        internalCounters.push_back(49188);
        internalCounters.push_back(49632);
        internalCounters.push_back(50076);
        internalCounters.push_back(50520);
        internalCounters.push_back(50964);
        internalCounters.push_back(44305);
        internalCounters.push_back(44749);
        internalCounters.push_back(45193);
        internalCounters.push_back(45637);
        internalCounters.push_back(46081);
        internalCounters.push_back(46525);
        internalCounters.push_back(46969);
        internalCounters.push_back(47413);
        internalCounters.push_back(47857);
        internalCounters.push_back(48301);
        internalCounters.push_back(48745);
        internalCounters.push_back(49189);
        internalCounters.push_back(49633);
        internalCounters.push_back(50077);
        internalCounters.push_back(50521);
        internalCounters.push_back(50965);
        internalCounters.push_back(44306);
        internalCounters.push_back(44750);
        internalCounters.push_back(45194);
        internalCounters.push_back(45638);
        internalCounters.push_back(46082);
        internalCounters.push_back(46526);
        internalCounters.push_back(46970);
        internalCounters.push_back(47414);
        internalCounters.push_back(47858);
        internalCounters.push_back(48302);
        internalCounters.push_back(48746);
        internalCounters.push_back(49190);
        internalCounters.push_back(49634);
        internalCounters.push_back(50078);
        internalCounters.push_back(50522);
        internalCounters.push_back(50966);

        c.UpdateAsicSpecificDerivedCounter("CBColorAndMaskRead", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(44296);
        internalCounters.push_back(44740);
        internalCounters.push_back(45184);
        internalCounters.push_back(45628);
        internalCounters.push_back(46072);
        internalCounters.push_back(46516);
        internalCounters.push_back(46960);
        internalCounters.push_back(47404);
        internalCounters.push_back(47848);
        internalCounters.push_back(48292);
        internalCounters.push_back(48736);
        internalCounters.push_back(49180);
        internalCounters.push_back(49624);
        internalCounters.push_back(50068);
        internalCounters.push_back(50512);
        internalCounters.push_back(50956);

        c.UpdateAsicSpecificDerivedCounter("CBMemWritten", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(44435);
        internalCounters.push_back(44879);
        internalCounters.push_back(45323);
        internalCounters.push_back(45767);
        internalCounters.push_back(46211);
        internalCounters.push_back(46655);
        internalCounters.push_back(47099);
        internalCounters.push_back(47543);
        internalCounters.push_back(47987);
        internalCounters.push_back(48431);
        internalCounters.push_back(48875);
        internalCounters.push_back(49319);
        internalCounters.push_back(49763);
        internalCounters.push_back(50207);
        internalCounters.push_back(50651);
        internalCounters.push_back(51095);
        internalCounters.push_back(44294);
        internalCounters.push_back(44738);
        internalCounters.push_back(45182);
        internalCounters.push_back(45626);
        internalCounters.push_back(46070);
        internalCounters.push_back(46514);
        internalCounters.push_back(46958);
        internalCounters.push_back(47402);
        internalCounters.push_back(47846);
        internalCounters.push_back(48290);
        internalCounters.push_back(48734);
        internalCounters.push_back(49178);
        internalCounters.push_back(49622);
        internalCounters.push_back(50066);
        internalCounters.push_back(50510);
        internalCounters.push_back(50954);
        internalCounters.push_back(44295);
        internalCounters.push_back(44739);
        internalCounters.push_back(45183);
        internalCounters.push_back(45627);
        internalCounters.push_back(46071);
        internalCounters.push_back(46515);
        internalCounters.push_back(46959);
        internalCounters.push_back(47403);
        internalCounters.push_back(47847);
        internalCounters.push_back(48291);
        internalCounters.push_back(48735);
        internalCounters.push_back(49179);
        internalCounters.push_back(49623);
        internalCounters.push_back(50067);
        internalCounters.push_back(50511);
        internalCounters.push_back(50955);
        internalCounters.push_back(44296);
        internalCounters.push_back(44740);
        internalCounters.push_back(45184);
        internalCounters.push_back(45628);
        internalCounters.push_back(46072);
        internalCounters.push_back(46516);
        internalCounters.push_back(46960);
        internalCounters.push_back(47404);
        internalCounters.push_back(47848);
        internalCounters.push_back(48292);
        internalCounters.push_back(48736);
        internalCounters.push_back(49180);
        internalCounters.push_back(49624);
        internalCounters.push_back(50068);
        internalCounters.push_back(50512);
        internalCounters.push_back(50956);

        c.UpdateAsicSpecificDerivedCounter("CBColorAndMaskWritten", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(44340);
        internalCounters.push_back(44784);
        internalCounters.push_back(45228);
        internalCounters.push_back(45672);
        internalCounters.push_back(46116);
        internalCounters.push_back(46560);
        internalCounters.push_back(47004);
        internalCounters.push_back(47448);
        internalCounters.push_back(47892);
        internalCounters.push_back(48336);
        internalCounters.push_back(48780);
        internalCounters.push_back(49224);
        internalCounters.push_back(49668);
        internalCounters.push_back(50112);
        internalCounters.push_back(50556);
        internalCounters.push_back(51000);
        internalCounters.push_back(44185);
        internalCounters.push_back(44629);
        internalCounters.push_back(45073);
        internalCounters.push_back(45517);
        internalCounters.push_back(45961);
        internalCounters.push_back(46405);
        internalCounters.push_back(46849);
        internalCounters.push_back(47293);
        internalCounters.push_back(47737);
        internalCounters.push_back(48181);
        internalCounters.push_back(48625);
        internalCounters.push_back(49069);
        internalCounters.push_back(49513);
        internalCounters.push_back(49957);
        internalCounters.push_back(50401);
        internalCounters.push_back(50845);

        c.UpdateAsicSpecificDerivedCounter("CBSlowPixelPct", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*,(100),min");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(44340);
        internalCounters.push_back(44784);
        internalCounters.push_back(45228);
        internalCounters.push_back(45672);
        internalCounters.push_back(46116);
        internalCounters.push_back(46560);
        internalCounters.push_back(47004);
        internalCounters.push_back(47448);
        internalCounters.push_back(47892);
        internalCounters.push_back(48336);
        internalCounters.push_back(48780);
        internalCounters.push_back(49224);
        internalCounters.push_back(49668);
        internalCounters.push_back(50112);
        internalCounters.push_back(50556);
        internalCounters.push_back(51000);

        c.UpdateAsicSpecificDerivedCounter("CBSlowPixelCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(34389);
        internalCounters.push_back(34671);
        internalCounters.push_back(34953);
        internalCounters.push_back(35235);
        internalCounters.push_back(35517);
        internalCounters.push_back(35799);
        internalCounters.push_back(36081);
        internalCounters.push_back(36363);
        internalCounters.push_back(36645);
        internalCounters.push_back(36927);
        internalCounters.push_back(37209);
        internalCounters.push_back(37491);
        internalCounters.push_back(37773);
        internalCounters.push_back(38055);
        internalCounters.push_back(38337);
        internalCounters.push_back(38619);
        internalCounters.push_back(34390);
        internalCounters.push_back(34672);
        internalCounters.push_back(34954);
        internalCounters.push_back(35236);
        internalCounters.push_back(35518);
        internalCounters.push_back(35800);
        internalCounters.push_back(36082);
        internalCounters.push_back(36364);
        internalCounters.push_back(36646);
        internalCounters.push_back(36928);
        internalCounters.push_back(37210);
        internalCounters.push_back(37492);
        internalCounters.push_back(37774);
        internalCounters.push_back(38056);
        internalCounters.push_back(38338);
        internalCounters.push_back(38620);

        c.UpdateAsicSpecificDerivedCounter("FetchSize", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(64),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(34377);
        internalCounters.push_back(34659);
        internalCounters.push_back(34941);
        internalCounters.push_back(35223);
        internalCounters.push_back(35505);
        internalCounters.push_back(35787);
        internalCounters.push_back(36069);
        internalCounters.push_back(36351);
        internalCounters.push_back(36633);
        internalCounters.push_back(36915);
        internalCounters.push_back(37197);
        internalCounters.push_back(37479);
        internalCounters.push_back(37761);
        internalCounters.push_back(38043);
        internalCounters.push_back(38325);
        internalCounters.push_back(38607);
        internalCounters.push_back(34378);
        internalCounters.push_back(34660);
        internalCounters.push_back(34942);
        internalCounters.push_back(35224);
        internalCounters.push_back(35506);
        internalCounters.push_back(35788);
        internalCounters.push_back(36070);
        internalCounters.push_back(36352);
        internalCounters.push_back(36634);
        internalCounters.push_back(36916);
        internalCounters.push_back(37198);
        internalCounters.push_back(37480);
        internalCounters.push_back(37762);
        internalCounters.push_back(38044);
        internalCounters.push_back(38326);
        internalCounters.push_back(38608);

        c.UpdateAsicSpecificDerivedCounter("WriteSize", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(34368);
        internalCounters.push_back(34650);
        internalCounters.push_back(34932);
        internalCounters.push_back(35214);
        internalCounters.push_back(35496);
        internalCounters.push_back(35778);
        internalCounters.push_back(36060);
        internalCounters.push_back(36342);
        internalCounters.push_back(36624);
        internalCounters.push_back(36906);
        internalCounters.push_back(37188);
        internalCounters.push_back(37470);
        internalCounters.push_back(37752);
        internalCounters.push_back(38034);
        internalCounters.push_back(38316);
        internalCounters.push_back(38598);
        internalCounters.push_back(34370);
        internalCounters.push_back(34652);
        internalCounters.push_back(34934);
        internalCounters.push_back(35216);
        internalCounters.push_back(35498);
        internalCounters.push_back(35780);
        internalCounters.push_back(36062);
        internalCounters.push_back(36344);
        internalCounters.push_back(36626);
        internalCounters.push_back(36908);
        internalCounters.push_back(37190);
        internalCounters.push_back(37472);
        internalCounters.push_back(37754);
        internalCounters.push_back(38036);
        internalCounters.push_back(38318);
        internalCounters.push_back(38600);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHit", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(34368);
        internalCounters.push_back(34650);
        internalCounters.push_back(34932);
        internalCounters.push_back(35214);
        internalCounters.push_back(35496);
        internalCounters.push_back(35778);
        internalCounters.push_back(36060);
        internalCounters.push_back(36342);
        internalCounters.push_back(36624);
        internalCounters.push_back(36906);
        internalCounters.push_back(37188);
        internalCounters.push_back(37470);
        internalCounters.push_back(37752);
        internalCounters.push_back(38034);
        internalCounters.push_back(38316);
        internalCounters.push_back(38598);
        internalCounters.push_back(34370);
        internalCounters.push_back(34652);
        internalCounters.push_back(34934);
        internalCounters.push_back(35216);
        internalCounters.push_back(35498);
        internalCounters.push_back(35780);
        internalCounters.push_back(36062);
        internalCounters.push_back(36344);
        internalCounters.push_back(36626);
        internalCounters.push_back(36908);
        internalCounters.push_back(37190);
        internalCounters.push_back(37472);
        internalCounters.push_back(37754);
        internalCounters.push_back(38036);
        internalCounters.push_back(38318);
        internalCounters.push_back(38600);

        c.UpdateAsicSpecificDerivedCounter("L2CacheMiss", internalCounters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(34368);
        internalCounters.push_back(34650);
        internalCounters.push_back(34932);
        internalCounters.push_back(35214);
        internalCounters.push_back(35496);
        internalCounters.push_back(35778);
        internalCounters.push_back(36060);
        internalCounters.push_back(36342);
        internalCounters.push_back(36624);
        internalCounters.push_back(36906);
        internalCounters.push_back(37188);
        internalCounters.push_back(37470);
        internalCounters.push_back(37752);
        internalCounters.push_back(38034);
        internalCounters.push_back(38316);
        internalCounters.push_back(38598);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHitCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(34370);
        internalCounters.push_back(34652);
        internalCounters.push_back(34934);
        internalCounters.push_back(35216);
        internalCounters.push_back(35498);
        internalCounters.push_back(35780);
        internalCounters.push_back(36062);
        internalCounters.push_back(36344);
        internalCounters.push_back(36626);
        internalCounters.push_back(36908);
        internalCounters.push_back(37190);
        internalCounters.push_back(37472);
        internalCounters.push_back(37754);
        internalCounters.push_back(38036);
        internalCounters.push_back(38318);
        internalCounters.push_back(38600);

        c.UpdateAsicSpecificDerivedCounter("L2CacheMissCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(34381);
        internalCounters.push_back(34663);
        internalCounters.push_back(34945);
        internalCounters.push_back(35227);
        internalCounters.push_back(35509);
        internalCounters.push_back(35791);
        internalCounters.push_back(36073);
        internalCounters.push_back(36355);
        internalCounters.push_back(36637);
        internalCounters.push_back(36919);
        internalCounters.push_back(37201);
        internalCounters.push_back(37483);
        internalCounters.push_back(37765);
        internalCounters.push_back(38047);
        internalCounters.push_back(38329);
        internalCounters.push_back(38611);
        internalCounters.push_back(23);

        c.UpdateAsicSpecificDerivedCounter("WriteUnitStalled", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(34381);
        internalCounters.push_back(34663);
        internalCounters.push_back(34945);
        internalCounters.push_back(35227);
        internalCounters.push_back(35509);
        internalCounters.push_back(35791);
        internalCounters.push_back(36073);
        internalCounters.push_back(36355);
        internalCounters.push_back(36637);
        internalCounters.push_back(36919);
        internalCounters.push_back(37201);
        internalCounters.push_back(37483);
        internalCounters.push_back(37765);
        internalCounters.push_back(38047);
        internalCounters.push_back(38329);
        internalCounters.push_back(38611);

        c.UpdateAsicSpecificDerivedCounter("WriteUnitStalledCycles", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(51967);
        internalCounters.push_back(52050);
        internalCounters.push_back(52133);
        internalCounters.push_back(52216);
        internalCounters.push_back(52299);
        internalCounters.push_back(52382);
        internalCounters.push_back(52465);
        internalCounters.push_back(52548);
        internalCounters.push_back(52631);
        internalCounters.push_back(52714);
        internalCounters.push_back(52797);
        internalCounters.push_back(52880);
        internalCounters.push_back(52963);
        internalCounters.push_back(53046);
        internalCounters.push_back(53129);
        internalCounters.push_back(53212);

        c.UpdateAsicSpecificDerivedCounter("LocalVidMemBytes", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(51969);
        internalCounters.push_back(52052);
        internalCounters.push_back(52135);
        internalCounters.push_back(52218);
        internalCounters.push_back(52301);
        internalCounters.push_back(52384);
        internalCounters.push_back(52467);
        internalCounters.push_back(52550);
        internalCounters.push_back(52633);
        internalCounters.push_back(52716);
        internalCounters.push_back(52799);
        internalCounters.push_back(52882);
        internalCounters.push_back(52965);
        internalCounters.push_back(53048);
        internalCounters.push_back(53131);
        internalCounters.push_back(53214);

        c.UpdateAsicSpecificDerivedCounter("PcieBytes", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    return true;
}

}  // namespace dx12gfx9gfx909

