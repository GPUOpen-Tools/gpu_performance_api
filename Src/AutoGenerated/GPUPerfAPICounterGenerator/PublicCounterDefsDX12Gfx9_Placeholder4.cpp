//==============================================================================
// Copyright (c) 2010-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for DX12GFX9_PLACEHOLDER4
//==============================================================================

#include "GPACounter.h"
#include "PublicCounterDefsDX12Gfx9_Placeholder4.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPAHWCounterGfx9_Placeholder4.h"

namespace DX12Gfx9_Placeholder4
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_DerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!CounterGfx9_Placeholder4::MatchAsic(asicType))
    {
        return false;
    }

    CounterGfx9_Placeholder4::OverrideBlockInstanceCounters(asicType);

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
        internalCounters.push_back(51871);
        internalCounters.push_back(51954);
        internalCounters.push_back(52037);
        internalCounters.push_back(52120);
        internalCounters.push_back(52203);
        internalCounters.push_back(52286);
        internalCounters.push_back(52369);
        internalCounters.push_back(52452);
        internalCounters.push_back(52535);
        internalCounters.push_back(52618);
        internalCounters.push_back(52701);
        internalCounters.push_back(52784);
        internalCounters.push_back(52867);
        internalCounters.push_back(52950);
        internalCounters.push_back(53033);
        internalCounters.push_back(53116);

        c.UpdateAsicSpecificDerivedCounter("LocalVidMemBytes", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(51873);
        internalCounters.push_back(51956);
        internalCounters.push_back(52039);
        internalCounters.push_back(52122);
        internalCounters.push_back(52205);
        internalCounters.push_back(52288);
        internalCounters.push_back(52371);
        internalCounters.push_back(52454);
        internalCounters.push_back(52537);
        internalCounters.push_back(52620);
        internalCounters.push_back(52703);
        internalCounters.push_back(52786);
        internalCounters.push_back(52869);
        internalCounters.push_back(52952);
        internalCounters.push_back(53035);
        internalCounters.push_back(53118);

        c.UpdateAsicSpecificDerivedCounter("PcieBytes", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    return true;
}

}  // namespace DX12Gfx9_Placeholder4

