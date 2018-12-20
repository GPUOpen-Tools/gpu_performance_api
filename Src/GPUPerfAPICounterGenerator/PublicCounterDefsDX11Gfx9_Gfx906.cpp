//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for DX11GFX9_GFX906
//==============================================================================

#include "GPAInternalCounter.h"
#include "PublicCounterDefsDX11Gfx9_Gfx906.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPAInternalCountersGfx9_Gfx906.h"

namespace DX11Gfx9_Gfx906
{

bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_DerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(c); // Unreferenced if there are no ASIC specific block instance registers

    if (!CounterGfx9_Gfx906::MatchAsic(asicType))
    {
        return false;
    }

    CounterGfx9_Gfx906::OverrideBlockInstanceCounters(asicType);

    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12696);
        internalCounters.push_back(13047);
        internalCounters.push_back(13398);
        internalCounters.push_back(13749);
        internalCounters.push_back(12700);
        internalCounters.push_back(13051);
        internalCounters.push_back(13402);
        internalCounters.push_back(13753);
        internalCounters.push_back(12652);
        internalCounters.push_back(13003);
        internalCounters.push_back(13354);
        internalCounters.push_back(13705);
        internalCounters.push_back(12664);
        internalCounters.push_back(13015);
        internalCounters.push_back(13366);
        internalCounters.push_back(13717);
        internalCounters.push_back(12653);
        internalCounters.push_back(13004);
        internalCounters.push_back(13355);
        internalCounters.push_back(13706);
        internalCounters.push_back(12665);
        internalCounters.push_back(13016);
        internalCounters.push_back(13367);
        internalCounters.push_back(13718);
        internalCounters.push_back(12484);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusy", internalCounters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max,24,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12696);
        internalCounters.push_back(13047);
        internalCounters.push_back(13398);
        internalCounters.push_back(13749);
        internalCounters.push_back(12700);
        internalCounters.push_back(13051);
        internalCounters.push_back(13402);
        internalCounters.push_back(13753);
        internalCounters.push_back(12652);
        internalCounters.push_back(13003);
        internalCounters.push_back(13354);
        internalCounters.push_back(13705);
        internalCounters.push_back(12664);
        internalCounters.push_back(13015);
        internalCounters.push_back(13366);
        internalCounters.push_back(13717);
        internalCounters.push_back(12653);
        internalCounters.push_back(13004);
        internalCounters.push_back(13355);
        internalCounters.push_back(13706);
        internalCounters.push_back(12665);
        internalCounters.push_back(13016);
        internalCounters.push_back(13367);
        internalCounters.push_back(13718);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusyCycles", internalCounters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12599);
        internalCounters.push_back(12950);
        internalCounters.push_back(13301);
        internalCounters.push_back(13652);

        c.UpdateAsicSpecificDerivedCounter("PrimitivesIn", internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12605);
        internalCounters.push_back(12956);
        internalCounters.push_back(13307);
        internalCounters.push_back(13658);
        internalCounters.push_back(12645);
        internalCounters.push_back(12996);
        internalCounters.push_back(13347);
        internalCounters.push_back(13698);
        internalCounters.push_back(12646);
        internalCounters.push_back(12997);
        internalCounters.push_back(13348);
        internalCounters.push_back(13699);
        internalCounters.push_back(12647);
        internalCounters.push_back(12998);
        internalCounters.push_back(13349);
        internalCounters.push_back(13700);
        internalCounters.push_back(12648);
        internalCounters.push_back(12999);
        internalCounters.push_back(13350);
        internalCounters.push_back(13701);

        c.UpdateAsicSpecificDerivedCounter("CulledPrims", internalCounters, "0,1,+,2,+,3,+,4,+,5,+,6,+,7,+,8,+,9,+,10,+,11,+,12,+,13,+,14,+,15,+,16,+,17,+,18,+,19,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12612);
        internalCounters.push_back(12963);
        internalCounters.push_back(13314);
        internalCounters.push_back(13665);

        c.UpdateAsicSpecificDerivedCounter("ClippedPrims", internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12700);
        internalCounters.push_back(13051);
        internalCounters.push_back(13402);
        internalCounters.push_back(13753);
        internalCounters.push_back(12484);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizer", internalCounters, "0,1,max,2,max,3,max,4,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12700);
        internalCounters.push_back(13051);
        internalCounters.push_back(13402);
        internalCounters.push_back(13753);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizerCycles", internalCounters, "0,1,max,2,max,3,max");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14154);
        internalCounters.push_back(14646);
        internalCounters.push_back(15138);
        internalCounters.push_back(15630);
        internalCounters.push_back(14155);
        internalCounters.push_back(14647);
        internalCounters.push_back(15139);
        internalCounters.push_back(15631);
        internalCounters.push_back(14156);
        internalCounters.push_back(14648);
        internalCounters.push_back(15140);
        internalCounters.push_back(15632);
        internalCounters.push_back(14157);
        internalCounters.push_back(14649);
        internalCounters.push_back(15141);
        internalCounters.push_back(15633);
        internalCounters.push_back(14230);
        internalCounters.push_back(14722);
        internalCounters.push_back(15214);
        internalCounters.push_back(15706);
        internalCounters.push_back(14231);
        internalCounters.push_back(14723);
        internalCounters.push_back(15215);
        internalCounters.push_back(15707);
        internalCounters.push_back(14232);
        internalCounters.push_back(14724);
        internalCounters.push_back(15216);
        internalCounters.push_back(15708);
        internalCounters.push_back(14233);
        internalCounters.push_back(14725);
        internalCounters.push_back(15217);
        internalCounters.push_back(15709);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulled", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14154);
        internalCounters.push_back(14646);
        internalCounters.push_back(15138);
        internalCounters.push_back(15630);
        internalCounters.push_back(14155);
        internalCounters.push_back(14647);
        internalCounters.push_back(15139);
        internalCounters.push_back(15631);
        internalCounters.push_back(14156);
        internalCounters.push_back(14648);
        internalCounters.push_back(15140);
        internalCounters.push_back(15632);
        internalCounters.push_back(14157);
        internalCounters.push_back(14649);
        internalCounters.push_back(15141);
        internalCounters.push_back(15633);
        internalCounters.push_back(14230);
        internalCounters.push_back(14722);
        internalCounters.push_back(15214);
        internalCounters.push_back(15706);
        internalCounters.push_back(14231);
        internalCounters.push_back(14723);
        internalCounters.push_back(15215);
        internalCounters.push_back(15707);
        internalCounters.push_back(14232);
        internalCounters.push_back(14724);
        internalCounters.push_back(15216);
        internalCounters.push_back(15708);
        internalCounters.push_back(14233);
        internalCounters.push_back(14725);
        internalCounters.push_back(15217);
        internalCounters.push_back(15709);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulledCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14230);
        internalCounters.push_back(14722);
        internalCounters.push_back(15214);
        internalCounters.push_back(15706);
        internalCounters.push_back(14231);
        internalCounters.push_back(14723);
        internalCounters.push_back(15215);
        internalCounters.push_back(15707);
        internalCounters.push_back(14232);
        internalCounters.push_back(14724);
        internalCounters.push_back(15216);
        internalCounters.push_back(15708);
        internalCounters.push_back(14233);
        internalCounters.push_back(14725);
        internalCounters.push_back(15217);
        internalCounters.push_back(15709);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsAcceptedCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14154);
        internalCounters.push_back(14646);
        internalCounters.push_back(15138);
        internalCounters.push_back(15630);
        internalCounters.push_back(14155);
        internalCounters.push_back(14647);
        internalCounters.push_back(15139);
        internalCounters.push_back(15631);
        internalCounters.push_back(14156);
        internalCounters.push_back(14648);
        internalCounters.push_back(15140);
        internalCounters.push_back(15632);
        internalCounters.push_back(14157);
        internalCounters.push_back(14649);
        internalCounters.push_back(15141);
        internalCounters.push_back(15633);
        internalCounters.push_back(14254);
        internalCounters.push_back(14746);
        internalCounters.push_back(15238);
        internalCounters.push_back(15730);
        internalCounters.push_back(14230);
        internalCounters.push_back(14722);
        internalCounters.push_back(15214);
        internalCounters.push_back(15706);
        internalCounters.push_back(14231);
        internalCounters.push_back(14723);
        internalCounters.push_back(15215);
        internalCounters.push_back(15707);
        internalCounters.push_back(14232);
        internalCounters.push_back(14724);
        internalCounters.push_back(15216);
        internalCounters.push_back(15708);
        internalCounters.push_back(14233);
        internalCounters.push_back(14725);
        internalCounters.push_back(15217);
        internalCounters.push_back(15709);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulled", internalCounters, "20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,sum16,16,17,18,19,sum4,-,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14154);
        internalCounters.push_back(14646);
        internalCounters.push_back(15138);
        internalCounters.push_back(15630);
        internalCounters.push_back(14155);
        internalCounters.push_back(14647);
        internalCounters.push_back(15139);
        internalCounters.push_back(15631);
        internalCounters.push_back(14156);
        internalCounters.push_back(14648);
        internalCounters.push_back(15140);
        internalCounters.push_back(15632);
        internalCounters.push_back(14157);
        internalCounters.push_back(14649);
        internalCounters.push_back(15141);
        internalCounters.push_back(15633);
        internalCounters.push_back(14254);
        internalCounters.push_back(14746);
        internalCounters.push_back(15238);
        internalCounters.push_back(15730);
        internalCounters.push_back(14230);
        internalCounters.push_back(14722);
        internalCounters.push_back(15214);
        internalCounters.push_back(15706);
        internalCounters.push_back(14231);
        internalCounters.push_back(14723);
        internalCounters.push_back(15215);
        internalCounters.push_back(15707);
        internalCounters.push_back(14232);
        internalCounters.push_back(14724);
        internalCounters.push_back(15216);
        internalCounters.push_back(15708);
        internalCounters.push_back(14233);
        internalCounters.push_back(14725);
        internalCounters.push_back(15217);
        internalCounters.push_back(15709);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulledCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,sum4,-,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,sum16,-");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14254);
        internalCounters.push_back(14746);
        internalCounters.push_back(15238);
        internalCounters.push_back(15730);
        internalCounters.push_back(14230);
        internalCounters.push_back(14722);
        internalCounters.push_back(15214);
        internalCounters.push_back(15706);
        internalCounters.push_back(14231);
        internalCounters.push_back(14723);
        internalCounters.push_back(15215);
        internalCounters.push_back(15707);
        internalCounters.push_back(14232);
        internalCounters.push_back(14724);
        internalCounters.push_back(15216);
        internalCounters.push_back(15708);
        internalCounters.push_back(14233);
        internalCounters.push_back(14725);
        internalCounters.push_back(15217);
        internalCounters.push_back(15709);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsSurvivingCount", internalCounters, "4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,sum16,0,1,2,3,sum4,-");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14254);
        internalCounters.push_back(14746);
        internalCounters.push_back(15238);
        internalCounters.push_back(15730);
        internalCounters.push_back(14154);
        internalCounters.push_back(14646);
        internalCounters.push_back(15138);
        internalCounters.push_back(15630);
        internalCounters.push_back(14155);
        internalCounters.push_back(14647);
        internalCounters.push_back(15139);
        internalCounters.push_back(15631);
        internalCounters.push_back(14156);
        internalCounters.push_back(14648);
        internalCounters.push_back(15140);
        internalCounters.push_back(15632);
        internalCounters.push_back(14157);
        internalCounters.push_back(14649);
        internalCounters.push_back(15141);
        internalCounters.push_back(15633);

        c.UpdateAsicSpecificDerivedCounter("PostZQuads", internalCounters, "0,1,2,3,sum4,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,sum16,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14254);
        internalCounters.push_back(14746);
        internalCounters.push_back(15238);
        internalCounters.push_back(15730);

        c.UpdateAsicSpecificDerivedCounter("PostZQuadCount", internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(46271);
        internalCounters.push_back(46553);
        internalCounters.push_back(46835);
        internalCounters.push_back(47117);
        internalCounters.push_back(47399);
        internalCounters.push_back(47681);
        internalCounters.push_back(47963);
        internalCounters.push_back(48245);
        internalCounters.push_back(48527);
        internalCounters.push_back(48809);
        internalCounters.push_back(49091);
        internalCounters.push_back(49373);
        internalCounters.push_back(49655);
        internalCounters.push_back(49937);
        internalCounters.push_back(50219);
        internalCounters.push_back(50501);
        internalCounters.push_back(46273);
        internalCounters.push_back(46555);
        internalCounters.push_back(46837);
        internalCounters.push_back(47119);
        internalCounters.push_back(47401);
        internalCounters.push_back(47683);
        internalCounters.push_back(47965);
        internalCounters.push_back(48247);
        internalCounters.push_back(48529);
        internalCounters.push_back(48811);
        internalCounters.push_back(49093);
        internalCounters.push_back(49375);
        internalCounters.push_back(49657);
        internalCounters.push_back(49939);
        internalCounters.push_back(50221);
        internalCounters.push_back(50503);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHit", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(46271);
        internalCounters.push_back(46553);
        internalCounters.push_back(46835);
        internalCounters.push_back(47117);
        internalCounters.push_back(47399);
        internalCounters.push_back(47681);
        internalCounters.push_back(47963);
        internalCounters.push_back(48245);
        internalCounters.push_back(48527);
        internalCounters.push_back(48809);
        internalCounters.push_back(49091);
        internalCounters.push_back(49373);
        internalCounters.push_back(49655);
        internalCounters.push_back(49937);
        internalCounters.push_back(50219);
        internalCounters.push_back(50501);
        internalCounters.push_back(46273);
        internalCounters.push_back(46555);
        internalCounters.push_back(46837);
        internalCounters.push_back(47119);
        internalCounters.push_back(47401);
        internalCounters.push_back(47683);
        internalCounters.push_back(47965);
        internalCounters.push_back(48247);
        internalCounters.push_back(48529);
        internalCounters.push_back(48811);
        internalCounters.push_back(49093);
        internalCounters.push_back(49375);
        internalCounters.push_back(49657);
        internalCounters.push_back(49939);
        internalCounters.push_back(50221);
        internalCounters.push_back(50503);

        c.UpdateAsicSpecificDerivedCounter("L2CacheMiss", internalCounters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(46271);
        internalCounters.push_back(46553);
        internalCounters.push_back(46835);
        internalCounters.push_back(47117);
        internalCounters.push_back(47399);
        internalCounters.push_back(47681);
        internalCounters.push_back(47963);
        internalCounters.push_back(48245);
        internalCounters.push_back(48527);
        internalCounters.push_back(48809);
        internalCounters.push_back(49091);
        internalCounters.push_back(49373);
        internalCounters.push_back(49655);
        internalCounters.push_back(49937);
        internalCounters.push_back(50219);
        internalCounters.push_back(50501);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHitCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(46273);
        internalCounters.push_back(46555);
        internalCounters.push_back(46837);
        internalCounters.push_back(47119);
        internalCounters.push_back(47401);
        internalCounters.push_back(47683);
        internalCounters.push_back(47965);
        internalCounters.push_back(48247);
        internalCounters.push_back(48529);
        internalCounters.push_back(48811);
        internalCounters.push_back(49093);
        internalCounters.push_back(49375);
        internalCounters.push_back(49657);
        internalCounters.push_back(49939);
        internalCounters.push_back(50221);
        internalCounters.push_back(50503);

        c.UpdateAsicSpecificDerivedCounter("L2CacheMissCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    return true;

}

} // DX11Gfx9_Gfx906

