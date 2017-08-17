//==============================================================================
// Copyright (c) 2010-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  PublicCounterDefinitions for CLGFX9
//==============================================================================

#include "PublicCounterDefsCLGfx9.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicCountersCLGfx9(GPA_PublicCounters& p)
{
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4133);

        p.DefinePublicCounter("Wavefronts", "#General#Total wavefronts.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4155);
        internalCounters.push_back(4133);

        p.DefinePublicCounter("VALUInsts", "#General#The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4159);
        internalCounters.push_back(4133);

        p.DefinePublicCounter("SALUInsts", "#General#The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4157);
        internalCounters.push_back(7430);
        internalCounters.push_back(7549);
        internalCounters.push_back(7668);
        internalCounters.push_back(7787);
        internalCounters.push_back(7906);
        internalCounters.push_back(8025);
        internalCounters.push_back(8144);
        internalCounters.push_back(8263);
        internalCounters.push_back(8382);
        internalCounters.push_back(8501);
        internalCounters.push_back(8620);
        internalCounters.push_back(8739);
        internalCounters.push_back(8858);
        internalCounters.push_back(8977);
        internalCounters.push_back(9096);
        internalCounters.push_back(9215);
        internalCounters.push_back(4133);

        p.DefinePublicCounter("VFetchInsts", "#General#The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4160);
        internalCounters.push_back(4133);

        p.DefinePublicCounter("SFetchInsts", "#General#The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4156);
        internalCounters.push_back(7431);
        internalCounters.push_back(7550);
        internalCounters.push_back(7669);
        internalCounters.push_back(7788);
        internalCounters.push_back(7907);
        internalCounters.push_back(8026);
        internalCounters.push_back(8145);
        internalCounters.push_back(8264);
        internalCounters.push_back(8383);
        internalCounters.push_back(8502);
        internalCounters.push_back(8621);
        internalCounters.push_back(8740);
        internalCounters.push_back(8859);
        internalCounters.push_back(8978);
        internalCounters.push_back(9097);
        internalCounters.push_back(9216);
        internalCounters.push_back(4133);

        p.DefinePublicCounter("VWriteInsts", "#General#The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4161);
        internalCounters.push_back(4162);
        internalCounters.push_back(4133);

        p.DefinePublicCounter("FlatVMemInsts", "#General#The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,-,2,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4163);
        internalCounters.push_back(4162);
        internalCounters.push_back(4133);

        p.DefinePublicCounter("LDSInsts", "#LocalMemory#The average number of LDS read or LDS write instructions executed per work item (affected by flow control).  Excludes FLAT instructions that read from or write to LDS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,-,2,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4162);
        internalCounters.push_back(4133);

        p.DefinePublicCounter("FlatLDSInsts", "#LocalMemory#The average number of FLAT instructions that read or write to LDS executed per work item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4164);
        internalCounters.push_back(4133);

        p.DefinePublicCounter("GDSInsts", "#General#The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4214);
        internalCounters.push_back(4200);

        p.DefinePublicCounter("VALUUtilization", "#General#The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,(64),*,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4200);
        internalCounters.push_back(3098);

        p.DefinePublicCounter("VALUBusy", "#General#The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4213);
        internalCounters.push_back(3098);

        p.DefinePublicCounter("SALUBusy", "#General#The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9344);
        internalCounters.push_back(9600);
        internalCounters.push_back(9856);
        internalCounters.push_back(10112);
        internalCounters.push_back(10368);
        internalCounters.push_back(10624);
        internalCounters.push_back(10880);
        internalCounters.push_back(11136);
        internalCounters.push_back(11392);
        internalCounters.push_back(11648);
        internalCounters.push_back(11904);
        internalCounters.push_back(12160);
        internalCounters.push_back(12416);
        internalCounters.push_back(12672);
        internalCounters.push_back(12928);
        internalCounters.push_back(13184);
        internalCounters.push_back(9345);
        internalCounters.push_back(9601);
        internalCounters.push_back(9857);
        internalCounters.push_back(10113);
        internalCounters.push_back(10369);
        internalCounters.push_back(10625);
        internalCounters.push_back(10881);
        internalCounters.push_back(11137);
        internalCounters.push_back(11393);
        internalCounters.push_back(11649);
        internalCounters.push_back(11905);
        internalCounters.push_back(12161);
        internalCounters.push_back(12417);
        internalCounters.push_back(12673);
        internalCounters.push_back(12929);
        internalCounters.push_back(13185);

        p.DefinePublicCounter("FetchSize", "#GlobalMemory#The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(64),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+,(1024),/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9332);
        internalCounters.push_back(9588);
        internalCounters.push_back(9844);
        internalCounters.push_back(10100);
        internalCounters.push_back(10356);
        internalCounters.push_back(10612);
        internalCounters.push_back(10868);
        internalCounters.push_back(11124);
        internalCounters.push_back(11380);
        internalCounters.push_back(11636);
        internalCounters.push_back(11892);
        internalCounters.push_back(12148);
        internalCounters.push_back(12404);
        internalCounters.push_back(12660);
        internalCounters.push_back(12916);
        internalCounters.push_back(13172);
        internalCounters.push_back(9333);
        internalCounters.push_back(9589);
        internalCounters.push_back(9845);
        internalCounters.push_back(10101);
        internalCounters.push_back(10357);
        internalCounters.push_back(10613);
        internalCounters.push_back(10869);
        internalCounters.push_back(11125);
        internalCounters.push_back(11381);
        internalCounters.push_back(11637);
        internalCounters.push_back(11893);
        internalCounters.push_back(12149);
        internalCounters.push_back(12405);
        internalCounters.push_back(12661);
        internalCounters.push_back(12917);
        internalCounters.push_back(13173);

        p.DefinePublicCounter("WriteSize", "#GlobalMemory#The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+,(1024),/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14371);
        internalCounters.push_back(14456);
        internalCounters.push_back(14541);
        internalCounters.push_back(14626);
        internalCounters.push_back(14711);
        internalCounters.push_back(14796);
        internalCounters.push_back(14881);
        internalCounters.push_back(14966);
        internalCounters.push_back(15051);
        internalCounters.push_back(15136);
        internalCounters.push_back(15221);
        internalCounters.push_back(15306);
        internalCounters.push_back(15391);
        internalCounters.push_back(15476);
        internalCounters.push_back(15561);
        internalCounters.push_back(15646);
        internalCounters.push_back(14380);
        internalCounters.push_back(14465);
        internalCounters.push_back(14550);
        internalCounters.push_back(14635);
        internalCounters.push_back(14720);
        internalCounters.push_back(14805);
        internalCounters.push_back(14890);
        internalCounters.push_back(14975);
        internalCounters.push_back(15060);
        internalCounters.push_back(15145);
        internalCounters.push_back(15230);
        internalCounters.push_back(15315);
        internalCounters.push_back(15400);
        internalCounters.push_back(15485);
        internalCounters.push_back(15570);
        internalCounters.push_back(15655);
        internalCounters.push_back(14381);
        internalCounters.push_back(14466);
        internalCounters.push_back(14551);
        internalCounters.push_back(14636);
        internalCounters.push_back(14721);
        internalCounters.push_back(14806);
        internalCounters.push_back(14891);
        internalCounters.push_back(14976);
        internalCounters.push_back(15061);
        internalCounters.push_back(15146);
        internalCounters.push_back(15231);
        internalCounters.push_back(15316);
        internalCounters.push_back(15401);
        internalCounters.push_back(15486);
        internalCounters.push_back(15571);
        internalCounters.push_back(15656);
        internalCounters.push_back(14382);
        internalCounters.push_back(14467);
        internalCounters.push_back(14552);
        internalCounters.push_back(14637);
        internalCounters.push_back(14722);
        internalCounters.push_back(14807);
        internalCounters.push_back(14892);
        internalCounters.push_back(14977);
        internalCounters.push_back(15062);
        internalCounters.push_back(15147);
        internalCounters.push_back(15232);
        internalCounters.push_back(15317);
        internalCounters.push_back(15402);
        internalCounters.push_back(15487);
        internalCounters.push_back(15572);
        internalCounters.push_back(15657);
        internalCounters.push_back(14383);
        internalCounters.push_back(14468);
        internalCounters.push_back(14553);
        internalCounters.push_back(14638);
        internalCounters.push_back(14723);
        internalCounters.push_back(14808);
        internalCounters.push_back(14893);
        internalCounters.push_back(14978);
        internalCounters.push_back(15063);
        internalCounters.push_back(15148);
        internalCounters.push_back(15233);
        internalCounters.push_back(15318);
        internalCounters.push_back(15403);
        internalCounters.push_back(15488);
        internalCounters.push_back(15573);
        internalCounters.push_back(15658);

        p.DefinePublicCounter("L1CacheHit", "#GlobalMemory#The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Value range: 0% (no hit) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum64,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9323);
        internalCounters.push_back(9579);
        internalCounters.push_back(9835);
        internalCounters.push_back(10091);
        internalCounters.push_back(10347);
        internalCounters.push_back(10603);
        internalCounters.push_back(10859);
        internalCounters.push_back(11115);
        internalCounters.push_back(11371);
        internalCounters.push_back(11627);
        internalCounters.push_back(11883);
        internalCounters.push_back(12139);
        internalCounters.push_back(12395);
        internalCounters.push_back(12651);
        internalCounters.push_back(12907);
        internalCounters.push_back(13163);
        internalCounters.push_back(9325);
        internalCounters.push_back(9581);
        internalCounters.push_back(9837);
        internalCounters.push_back(10093);
        internalCounters.push_back(10349);
        internalCounters.push_back(10605);
        internalCounters.push_back(10861);
        internalCounters.push_back(11117);
        internalCounters.push_back(11373);
        internalCounters.push_back(11629);
        internalCounters.push_back(11885);
        internalCounters.push_back(12141);
        internalCounters.push_back(12397);
        internalCounters.push_back(12653);
        internalCounters.push_back(12909);
        internalCounters.push_back(13165);

        p.DefinePublicCounter("L2CacheHit", "#GlobalMemory#The percentage of fetch, write, atomic, and other instructions that hit the data in L2 cache. Value range: 0% (no hit) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7344);
        internalCounters.push_back(7463);
        internalCounters.push_back(7582);
        internalCounters.push_back(7701);
        internalCounters.push_back(7820);
        internalCounters.push_back(7939);
        internalCounters.push_back(8058);
        internalCounters.push_back(8177);
        internalCounters.push_back(8296);
        internalCounters.push_back(8415);
        internalCounters.push_back(8534);
        internalCounters.push_back(8653);
        internalCounters.push_back(8772);
        internalCounters.push_back(8891);
        internalCounters.push_back(9010);
        internalCounters.push_back(9129);
        internalCounters.push_back(3098);

        p.DefinePublicCounter("MemUnitBusy", "#GlobalMemory#The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14317);
        internalCounters.push_back(14402);
        internalCounters.push_back(14487);
        internalCounters.push_back(14572);
        internalCounters.push_back(14657);
        internalCounters.push_back(14742);
        internalCounters.push_back(14827);
        internalCounters.push_back(14912);
        internalCounters.push_back(14997);
        internalCounters.push_back(15082);
        internalCounters.push_back(15167);
        internalCounters.push_back(15252);
        internalCounters.push_back(15337);
        internalCounters.push_back(15422);
        internalCounters.push_back(15507);
        internalCounters.push_back(15592);
        internalCounters.push_back(3098);

        p.DefinePublicCounter("MemUnitStalled", "#GlobalMemory#The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9336);
        internalCounters.push_back(9592);
        internalCounters.push_back(9848);
        internalCounters.push_back(10104);
        internalCounters.push_back(10360);
        internalCounters.push_back(10616);
        internalCounters.push_back(10872);
        internalCounters.push_back(11128);
        internalCounters.push_back(11384);
        internalCounters.push_back(11640);
        internalCounters.push_back(11896);
        internalCounters.push_back(12152);
        internalCounters.push_back(12408);
        internalCounters.push_back(12664);
        internalCounters.push_back(12920);
        internalCounters.push_back(13176);
        internalCounters.push_back(3098);

        p.DefinePublicCounter("WriteUnitStalled", "#GlobalMemory#The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max,16,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4222);
        internalCounters.push_back(3098);

        p.DefinePublicCounter("LDSBankConflict", "#LocalMemory#The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*");
    }
}

