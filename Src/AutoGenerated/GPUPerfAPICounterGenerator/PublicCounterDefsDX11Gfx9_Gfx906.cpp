//==============================================================================
// Copyright (c) 2010-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for DX11GFX9_GFX906
//==============================================================================

#include "GPACounter.h"
#include "PublicCounterDefsDX11Gfx9_Gfx906.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPAHWCounterGfx9_Gfx906.h"

namespace DX11Gfx9_Gfx906
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_DerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!CounterGfx9_Gfx906::MatchAsic(asicType))
    {
        return false;
    }

    CounterGfx9_Gfx906::OverrideBlockInstanceCounters(asicType);

    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12502);
        internalCounters.push_back(12853);
        internalCounters.push_back(13204);
        internalCounters.push_back(13555);
        internalCounters.push_back(12506);
        internalCounters.push_back(12857);
        internalCounters.push_back(13208);
        internalCounters.push_back(13559);
        internalCounters.push_back(12458);
        internalCounters.push_back(12809);
        internalCounters.push_back(13160);
        internalCounters.push_back(13511);
        internalCounters.push_back(12470);
        internalCounters.push_back(12821);
        internalCounters.push_back(13172);
        internalCounters.push_back(13523);
        internalCounters.push_back(12459);
        internalCounters.push_back(12810);
        internalCounters.push_back(13161);
        internalCounters.push_back(13512);
        internalCounters.push_back(12471);
        internalCounters.push_back(12822);
        internalCounters.push_back(13173);
        internalCounters.push_back(13524);
        internalCounters.push_back(23);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusy", internalCounters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max,24,/,(100),*,(100),min");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12502);
        internalCounters.push_back(12853);
        internalCounters.push_back(13204);
        internalCounters.push_back(13555);
        internalCounters.push_back(12506);
        internalCounters.push_back(12857);
        internalCounters.push_back(13208);
        internalCounters.push_back(13559);
        internalCounters.push_back(12458);
        internalCounters.push_back(12809);
        internalCounters.push_back(13160);
        internalCounters.push_back(13511);
        internalCounters.push_back(12470);
        internalCounters.push_back(12821);
        internalCounters.push_back(13172);
        internalCounters.push_back(13523);
        internalCounters.push_back(12459);
        internalCounters.push_back(12810);
        internalCounters.push_back(13161);
        internalCounters.push_back(13512);
        internalCounters.push_back(12471);
        internalCounters.push_back(12822);
        internalCounters.push_back(13173);
        internalCounters.push_back(13524);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusyCycles", internalCounters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12405);
        internalCounters.push_back(12756);
        internalCounters.push_back(13107);
        internalCounters.push_back(13458);

        c.UpdateAsicSpecificDerivedCounter("PrimitivesIn", internalCounters, "0,1,2,3,sum4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12411);
        internalCounters.push_back(12762);
        internalCounters.push_back(13113);
        internalCounters.push_back(13464);
        internalCounters.push_back(12451);
        internalCounters.push_back(12802);
        internalCounters.push_back(13153);
        internalCounters.push_back(13504);
        internalCounters.push_back(12452);
        internalCounters.push_back(12803);
        internalCounters.push_back(13154);
        internalCounters.push_back(13505);
        internalCounters.push_back(12453);
        internalCounters.push_back(12804);
        internalCounters.push_back(13155);
        internalCounters.push_back(13506);
        internalCounters.push_back(12454);
        internalCounters.push_back(12805);
        internalCounters.push_back(13156);
        internalCounters.push_back(13507);

        c.UpdateAsicSpecificDerivedCounter("CulledPrims", internalCounters, "0,1,+,2,+,3,+,4,+,5,+,6,+,7,+,8,+,9,+,10,+,11,+,12,+,13,+,14,+,15,+,16,+,17,+,18,+,19,+");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12418);
        internalCounters.push_back(12769);
        internalCounters.push_back(13120);
        internalCounters.push_back(13471);

        c.UpdateAsicSpecificDerivedCounter("ClippedPrims", internalCounters, "0,1,2,3,sum4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12506);
        internalCounters.push_back(12857);
        internalCounters.push_back(13208);
        internalCounters.push_back(13559);
        internalCounters.push_back(23);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizer", internalCounters, "0,1,max,2,max,3,max,4,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12506);
        internalCounters.push_back(12857);
        internalCounters.push_back(13208);
        internalCounters.push_back(13559);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizerCycles", internalCounters, "0,1,max,2,max,3,max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46090);
        internalCounters.push_back(46372);
        internalCounters.push_back(46654);
        internalCounters.push_back(46936);
        internalCounters.push_back(47218);
        internalCounters.push_back(47500);
        internalCounters.push_back(47782);
        internalCounters.push_back(48064);
        internalCounters.push_back(48346);
        internalCounters.push_back(48628);
        internalCounters.push_back(48910);
        internalCounters.push_back(49192);
        internalCounters.push_back(49474);
        internalCounters.push_back(49756);
        internalCounters.push_back(50038);
        internalCounters.push_back(50320);
        internalCounters.push_back(23);
        internalCounters.push_back(16644);
        internalCounters.push_back(16840);
        internalCounters.push_back(17036);
        internalCounters.push_back(17232);
        internalCounters.push_back(16650);
        internalCounters.push_back(16846);
        internalCounters.push_back(17042);
        internalCounters.push_back(17238);

        c.UpdateAsicSpecificDerivedCounter("CSWriteUnitStalled", internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,18,19,20,21,22,23,24,sum8,ifnotzero");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46090);
        internalCounters.push_back(46372);
        internalCounters.push_back(46654);
        internalCounters.push_back(46936);
        internalCounters.push_back(47218);
        internalCounters.push_back(47500);
        internalCounters.push_back(47782);
        internalCounters.push_back(48064);
        internalCounters.push_back(48346);
        internalCounters.push_back(48628);
        internalCounters.push_back(48910);
        internalCounters.push_back(49192);
        internalCounters.push_back(49474);
        internalCounters.push_back(49756);
        internalCounters.push_back(50038);
        internalCounters.push_back(50320);
        internalCounters.push_back(16644);
        internalCounters.push_back(16840);
        internalCounters.push_back(17036);
        internalCounters.push_back(17232);
        internalCounters.push_back(16650);
        internalCounters.push_back(16846);
        internalCounters.push_back(17042);
        internalCounters.push_back(17238);

        c.UpdateAsicSpecificDerivedCounter("CSWriteUnitStalledCycles", internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,17,18,19,20,21,22,23,sum8,ifnotzero");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13960);
        internalCounters.push_back(14452);
        internalCounters.push_back(14944);
        internalCounters.push_back(15436);
        internalCounters.push_back(13961);
        internalCounters.push_back(14453);
        internalCounters.push_back(14945);
        internalCounters.push_back(15437);
        internalCounters.push_back(13962);
        internalCounters.push_back(14454);
        internalCounters.push_back(14946);
        internalCounters.push_back(15438);
        internalCounters.push_back(13963);
        internalCounters.push_back(14455);
        internalCounters.push_back(14947);
        internalCounters.push_back(15439);
        internalCounters.push_back(14036);
        internalCounters.push_back(14528);
        internalCounters.push_back(15020);
        internalCounters.push_back(15512);
        internalCounters.push_back(14037);
        internalCounters.push_back(14529);
        internalCounters.push_back(15021);
        internalCounters.push_back(15513);
        internalCounters.push_back(14038);
        internalCounters.push_back(14530);
        internalCounters.push_back(15022);
        internalCounters.push_back(15514);
        internalCounters.push_back(14039);
        internalCounters.push_back(14531);
        internalCounters.push_back(15023);
        internalCounters.push_back(15515);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulled", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(0),max,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13960);
        internalCounters.push_back(14452);
        internalCounters.push_back(14944);
        internalCounters.push_back(15436);
        internalCounters.push_back(13961);
        internalCounters.push_back(14453);
        internalCounters.push_back(14945);
        internalCounters.push_back(15437);
        internalCounters.push_back(13962);
        internalCounters.push_back(14454);
        internalCounters.push_back(14946);
        internalCounters.push_back(15438);
        internalCounters.push_back(13963);
        internalCounters.push_back(14455);
        internalCounters.push_back(14947);
        internalCounters.push_back(15439);
        internalCounters.push_back(14036);
        internalCounters.push_back(14528);
        internalCounters.push_back(15020);
        internalCounters.push_back(15512);
        internalCounters.push_back(14037);
        internalCounters.push_back(14529);
        internalCounters.push_back(15021);
        internalCounters.push_back(15513);
        internalCounters.push_back(14038);
        internalCounters.push_back(14530);
        internalCounters.push_back(15022);
        internalCounters.push_back(15514);
        internalCounters.push_back(14039);
        internalCounters.push_back(14531);
        internalCounters.push_back(15023);
        internalCounters.push_back(15515);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulledCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14036);
        internalCounters.push_back(14528);
        internalCounters.push_back(15020);
        internalCounters.push_back(15512);
        internalCounters.push_back(14037);
        internalCounters.push_back(14529);
        internalCounters.push_back(15021);
        internalCounters.push_back(15513);
        internalCounters.push_back(14038);
        internalCounters.push_back(14530);
        internalCounters.push_back(15022);
        internalCounters.push_back(15514);
        internalCounters.push_back(14039);
        internalCounters.push_back(14531);
        internalCounters.push_back(15023);
        internalCounters.push_back(15515);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsAcceptedCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13960);
        internalCounters.push_back(14452);
        internalCounters.push_back(14944);
        internalCounters.push_back(15436);
        internalCounters.push_back(13961);
        internalCounters.push_back(14453);
        internalCounters.push_back(14945);
        internalCounters.push_back(15437);
        internalCounters.push_back(13962);
        internalCounters.push_back(14454);
        internalCounters.push_back(14946);
        internalCounters.push_back(15438);
        internalCounters.push_back(13963);
        internalCounters.push_back(14455);
        internalCounters.push_back(14947);
        internalCounters.push_back(15439);
        internalCounters.push_back(14060);
        internalCounters.push_back(14552);
        internalCounters.push_back(15044);
        internalCounters.push_back(15536);
        internalCounters.push_back(14036);
        internalCounters.push_back(14528);
        internalCounters.push_back(15020);
        internalCounters.push_back(15512);
        internalCounters.push_back(14037);
        internalCounters.push_back(14529);
        internalCounters.push_back(15021);
        internalCounters.push_back(15513);
        internalCounters.push_back(14038);
        internalCounters.push_back(14530);
        internalCounters.push_back(15022);
        internalCounters.push_back(15514);
        internalCounters.push_back(14039);
        internalCounters.push_back(14531);
        internalCounters.push_back(15023);
        internalCounters.push_back(15515);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulled", internalCounters, "20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,sum16,16,17,18,19,sum4,-,(0),max,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13960);
        internalCounters.push_back(14452);
        internalCounters.push_back(14944);
        internalCounters.push_back(15436);
        internalCounters.push_back(13961);
        internalCounters.push_back(14453);
        internalCounters.push_back(14945);
        internalCounters.push_back(15437);
        internalCounters.push_back(13962);
        internalCounters.push_back(14454);
        internalCounters.push_back(14946);
        internalCounters.push_back(15438);
        internalCounters.push_back(13963);
        internalCounters.push_back(14455);
        internalCounters.push_back(14947);
        internalCounters.push_back(15439);
        internalCounters.push_back(14060);
        internalCounters.push_back(14552);
        internalCounters.push_back(15044);
        internalCounters.push_back(15536);
        internalCounters.push_back(14036);
        internalCounters.push_back(14528);
        internalCounters.push_back(15020);
        internalCounters.push_back(15512);
        internalCounters.push_back(14037);
        internalCounters.push_back(14529);
        internalCounters.push_back(15021);
        internalCounters.push_back(15513);
        internalCounters.push_back(14038);
        internalCounters.push_back(14530);
        internalCounters.push_back(15022);
        internalCounters.push_back(15514);
        internalCounters.push_back(14039);
        internalCounters.push_back(14531);
        internalCounters.push_back(15023);
        internalCounters.push_back(15515);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulledCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,sum4,-,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,sum16,-,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14060);
        internalCounters.push_back(14552);
        internalCounters.push_back(15044);
        internalCounters.push_back(15536);
        internalCounters.push_back(14036);
        internalCounters.push_back(14528);
        internalCounters.push_back(15020);
        internalCounters.push_back(15512);
        internalCounters.push_back(14037);
        internalCounters.push_back(14529);
        internalCounters.push_back(15021);
        internalCounters.push_back(15513);
        internalCounters.push_back(14038);
        internalCounters.push_back(14530);
        internalCounters.push_back(15022);
        internalCounters.push_back(15514);
        internalCounters.push_back(14039);
        internalCounters.push_back(14531);
        internalCounters.push_back(15023);
        internalCounters.push_back(15515);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsSurvivingCount", internalCounters, "4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,sum16,0,1,2,3,sum4,-,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14060);
        internalCounters.push_back(14552);
        internalCounters.push_back(15044);
        internalCounters.push_back(15536);
        internalCounters.push_back(13960);
        internalCounters.push_back(14452);
        internalCounters.push_back(14944);
        internalCounters.push_back(15436);
        internalCounters.push_back(13961);
        internalCounters.push_back(14453);
        internalCounters.push_back(14945);
        internalCounters.push_back(15437);
        internalCounters.push_back(13962);
        internalCounters.push_back(14454);
        internalCounters.push_back(14946);
        internalCounters.push_back(15438);
        internalCounters.push_back(13963);
        internalCounters.push_back(14455);
        internalCounters.push_back(14947);
        internalCounters.push_back(15439);

        c.UpdateAsicSpecificDerivedCounter("PostZQuads", internalCounters, "0,1,2,3,sum4,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,sum16,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14060);
        internalCounters.push_back(14552);
        internalCounters.push_back(15044);
        internalCounters.push_back(15536);

        c.UpdateAsicSpecificDerivedCounter("PostZQuadCount", internalCounters, "0,1,2,3,sum4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46098);
        internalCounters.push_back(46380);
        internalCounters.push_back(46662);
        internalCounters.push_back(46944);
        internalCounters.push_back(47226);
        internalCounters.push_back(47508);
        internalCounters.push_back(47790);
        internalCounters.push_back(48072);
        internalCounters.push_back(48354);
        internalCounters.push_back(48636);
        internalCounters.push_back(48918);
        internalCounters.push_back(49200);
        internalCounters.push_back(49482);
        internalCounters.push_back(49764);
        internalCounters.push_back(50046);
        internalCounters.push_back(50328);
        internalCounters.push_back(46099);
        internalCounters.push_back(46381);
        internalCounters.push_back(46663);
        internalCounters.push_back(46945);
        internalCounters.push_back(47227);
        internalCounters.push_back(47509);
        internalCounters.push_back(47791);
        internalCounters.push_back(48073);
        internalCounters.push_back(48355);
        internalCounters.push_back(48637);
        internalCounters.push_back(48919);
        internalCounters.push_back(49201);
        internalCounters.push_back(49483);
        internalCounters.push_back(49765);
        internalCounters.push_back(50047);
        internalCounters.push_back(50329);

        c.UpdateAsicSpecificDerivedCounter("FetchSize", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(64),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46086);
        internalCounters.push_back(46368);
        internalCounters.push_back(46650);
        internalCounters.push_back(46932);
        internalCounters.push_back(47214);
        internalCounters.push_back(47496);
        internalCounters.push_back(47778);
        internalCounters.push_back(48060);
        internalCounters.push_back(48342);
        internalCounters.push_back(48624);
        internalCounters.push_back(48906);
        internalCounters.push_back(49188);
        internalCounters.push_back(49470);
        internalCounters.push_back(49752);
        internalCounters.push_back(50034);
        internalCounters.push_back(50316);
        internalCounters.push_back(46087);
        internalCounters.push_back(46369);
        internalCounters.push_back(46651);
        internalCounters.push_back(46933);
        internalCounters.push_back(47215);
        internalCounters.push_back(47497);
        internalCounters.push_back(47779);
        internalCounters.push_back(48061);
        internalCounters.push_back(48343);
        internalCounters.push_back(48625);
        internalCounters.push_back(48907);
        internalCounters.push_back(49189);
        internalCounters.push_back(49471);
        internalCounters.push_back(49753);
        internalCounters.push_back(50035);
        internalCounters.push_back(50317);

        c.UpdateAsicSpecificDerivedCounter("WriteSize", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46077);
        internalCounters.push_back(46359);
        internalCounters.push_back(46641);
        internalCounters.push_back(46923);
        internalCounters.push_back(47205);
        internalCounters.push_back(47487);
        internalCounters.push_back(47769);
        internalCounters.push_back(48051);
        internalCounters.push_back(48333);
        internalCounters.push_back(48615);
        internalCounters.push_back(48897);
        internalCounters.push_back(49179);
        internalCounters.push_back(49461);
        internalCounters.push_back(49743);
        internalCounters.push_back(50025);
        internalCounters.push_back(50307);
        internalCounters.push_back(46079);
        internalCounters.push_back(46361);
        internalCounters.push_back(46643);
        internalCounters.push_back(46925);
        internalCounters.push_back(47207);
        internalCounters.push_back(47489);
        internalCounters.push_back(47771);
        internalCounters.push_back(48053);
        internalCounters.push_back(48335);
        internalCounters.push_back(48617);
        internalCounters.push_back(48899);
        internalCounters.push_back(49181);
        internalCounters.push_back(49463);
        internalCounters.push_back(49745);
        internalCounters.push_back(50027);
        internalCounters.push_back(50309);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHit", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46077);
        internalCounters.push_back(46359);
        internalCounters.push_back(46641);
        internalCounters.push_back(46923);
        internalCounters.push_back(47205);
        internalCounters.push_back(47487);
        internalCounters.push_back(47769);
        internalCounters.push_back(48051);
        internalCounters.push_back(48333);
        internalCounters.push_back(48615);
        internalCounters.push_back(48897);
        internalCounters.push_back(49179);
        internalCounters.push_back(49461);
        internalCounters.push_back(49743);
        internalCounters.push_back(50025);
        internalCounters.push_back(50307);
        internalCounters.push_back(46079);
        internalCounters.push_back(46361);
        internalCounters.push_back(46643);
        internalCounters.push_back(46925);
        internalCounters.push_back(47207);
        internalCounters.push_back(47489);
        internalCounters.push_back(47771);
        internalCounters.push_back(48053);
        internalCounters.push_back(48335);
        internalCounters.push_back(48617);
        internalCounters.push_back(48899);
        internalCounters.push_back(49181);
        internalCounters.push_back(49463);
        internalCounters.push_back(49745);
        internalCounters.push_back(50027);
        internalCounters.push_back(50309);

        c.UpdateAsicSpecificDerivedCounter("L2CacheMiss", internalCounters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46077);
        internalCounters.push_back(46359);
        internalCounters.push_back(46641);
        internalCounters.push_back(46923);
        internalCounters.push_back(47205);
        internalCounters.push_back(47487);
        internalCounters.push_back(47769);
        internalCounters.push_back(48051);
        internalCounters.push_back(48333);
        internalCounters.push_back(48615);
        internalCounters.push_back(48897);
        internalCounters.push_back(49179);
        internalCounters.push_back(49461);
        internalCounters.push_back(49743);
        internalCounters.push_back(50025);
        internalCounters.push_back(50307);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHitCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46079);
        internalCounters.push_back(46361);
        internalCounters.push_back(46643);
        internalCounters.push_back(46925);
        internalCounters.push_back(47207);
        internalCounters.push_back(47489);
        internalCounters.push_back(47771);
        internalCounters.push_back(48053);
        internalCounters.push_back(48335);
        internalCounters.push_back(48617);
        internalCounters.push_back(48899);
        internalCounters.push_back(49181);
        internalCounters.push_back(49463);
        internalCounters.push_back(49745);
        internalCounters.push_back(50027);
        internalCounters.push_back(50309);

        c.UpdateAsicSpecificDerivedCounter("L2CacheMissCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46090);
        internalCounters.push_back(46372);
        internalCounters.push_back(46654);
        internalCounters.push_back(46936);
        internalCounters.push_back(47218);
        internalCounters.push_back(47500);
        internalCounters.push_back(47782);
        internalCounters.push_back(48064);
        internalCounters.push_back(48346);
        internalCounters.push_back(48628);
        internalCounters.push_back(48910);
        internalCounters.push_back(49192);
        internalCounters.push_back(49474);
        internalCounters.push_back(49756);
        internalCounters.push_back(50038);
        internalCounters.push_back(50320);
        internalCounters.push_back(23);

        c.UpdateAsicSpecificDerivedCounter("WriteUnitStalled", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(46090);
        internalCounters.push_back(46372);
        internalCounters.push_back(46654);
        internalCounters.push_back(46936);
        internalCounters.push_back(47218);
        internalCounters.push_back(47500);
        internalCounters.push_back(47782);
        internalCounters.push_back(48064);
        internalCounters.push_back(48346);
        internalCounters.push_back(48628);
        internalCounters.push_back(48910);
        internalCounters.push_back(49192);
        internalCounters.push_back(49474);
        internalCounters.push_back(49756);
        internalCounters.push_back(50038);
        internalCounters.push_back(50320);

        c.UpdateAsicSpecificDerivedCounter("WriteUnitStalledCycles", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16");
    }
    return true;
}

}  // namespace DX11Gfx9_Gfx906

