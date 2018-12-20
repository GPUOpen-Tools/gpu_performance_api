//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for CLGFX9
//==============================================================================

#include "GPAInternalCounter.h"
#include "PublicCounterDefsCLGfx9.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersCLGfx9(GPA_DerivedCounters& c)
{
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("Wavefronts", "General", "Total wavefronts.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "e8999836-489d-80a6-8e94-2c3ea191fd58");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4215);
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4219);
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4217);
        internalCounters.push_back(7490);
        internalCounters.push_back(7609);
        internalCounters.push_back(7728);
        internalCounters.push_back(7847);
        internalCounters.push_back(7966);
        internalCounters.push_back(8085);
        internalCounters.push_back(8204);
        internalCounters.push_back(8323);
        internalCounters.push_back(8442);
        internalCounters.push_back(8561);
        internalCounters.push_back(8680);
        internalCounters.push_back(8799);
        internalCounters.push_back(8918);
        internalCounters.push_back(9037);
        internalCounters.push_back(9156);
        internalCounters.push_back(9275);
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/", "85970f8f-0b2c-6431-9e52-7999236e6e8a");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4220);
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4216);
        internalCounters.push_back(7491);
        internalCounters.push_back(7610);
        internalCounters.push_back(7729);
        internalCounters.push_back(7848);
        internalCounters.push_back(7967);
        internalCounters.push_back(8086);
        internalCounters.push_back(8205);
        internalCounters.push_back(8324);
        internalCounters.push_back(8443);
        internalCounters.push_back(8562);
        internalCounters.push_back(8681);
        internalCounters.push_back(8800);
        internalCounters.push_back(8919);
        internalCounters.push_back(9038);
        internalCounters.push_back(9157);
        internalCounters.push_back(9276);
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/", "d8154a17-224d-704e-73d2-bb5d150f3196");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4221);
        internalCounters.push_back(4222);
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("FlatVMemInsts", "General", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,-,2,/", "05e4a953-c59a-e722-872b-e4bc7526bcee");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4223);
        internalCounters.push_back(4222);
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control). Excludes FLAT instructions that read from or write to LDS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,-,2,/", "be9bbead-f82a-a2c6-8333-1a5c4ce5ee98");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4222);
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("FlatLDSInsts", "LocalMemory", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "0f7d8f58-1750-a36f-d03e-85a2d9cd6e08");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4224);
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4274);
        internalCounters.push_back(4260);

        c.DefineDerivedCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,(64),*,/,(100),*,(100),min", "ffea5f90-624f-67dd-4ca6-74911f4c85d3");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4260);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4273);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9404);
        internalCounters.push_back(9686);
        internalCounters.push_back(9968);
        internalCounters.push_back(10250);
        internalCounters.push_back(10532);
        internalCounters.push_back(10814);
        internalCounters.push_back(11096);
        internalCounters.push_back(11378);
        internalCounters.push_back(11660);
        internalCounters.push_back(11942);
        internalCounters.push_back(12224);
        internalCounters.push_back(12506);
        internalCounters.push_back(12788);
        internalCounters.push_back(13070);
        internalCounters.push_back(13352);
        internalCounters.push_back(13634);
        internalCounters.push_back(9405);
        internalCounters.push_back(9687);
        internalCounters.push_back(9969);
        internalCounters.push_back(10251);
        internalCounters.push_back(10533);
        internalCounters.push_back(10815);
        internalCounters.push_back(11097);
        internalCounters.push_back(11379);
        internalCounters.push_back(11661);
        internalCounters.push_back(11943);
        internalCounters.push_back(12225);
        internalCounters.push_back(12507);
        internalCounters.push_back(12789);
        internalCounters.push_back(13071);
        internalCounters.push_back(13353);
        internalCounters.push_back(13635);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(64),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9392);
        internalCounters.push_back(9674);
        internalCounters.push_back(9956);
        internalCounters.push_back(10238);
        internalCounters.push_back(10520);
        internalCounters.push_back(10802);
        internalCounters.push_back(11084);
        internalCounters.push_back(11366);
        internalCounters.push_back(11648);
        internalCounters.push_back(11930);
        internalCounters.push_back(12212);
        internalCounters.push_back(12494);
        internalCounters.push_back(12776);
        internalCounters.push_back(13058);
        internalCounters.push_back(13340);
        internalCounters.push_back(13622);
        internalCounters.push_back(9393);
        internalCounters.push_back(9675);
        internalCounters.push_back(9957);
        internalCounters.push_back(10239);
        internalCounters.push_back(10521);
        internalCounters.push_back(10803);
        internalCounters.push_back(11085);
        internalCounters.push_back(11367);
        internalCounters.push_back(11649);
        internalCounters.push_back(11931);
        internalCounters.push_back(12213);
        internalCounters.push_back(12495);
        internalCounters.push_back(12777);
        internalCounters.push_back(13059);
        internalCounters.push_back(13341);
        internalCounters.push_back(13623);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+,(1024),/", "e09d95da-2772-f7cb-51f5-4fad27bb998b");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14847);
        internalCounters.push_back(14932);
        internalCounters.push_back(15017);
        internalCounters.push_back(15102);
        internalCounters.push_back(15187);
        internalCounters.push_back(15272);
        internalCounters.push_back(15357);
        internalCounters.push_back(15442);
        internalCounters.push_back(15527);
        internalCounters.push_back(15612);
        internalCounters.push_back(15697);
        internalCounters.push_back(15782);
        internalCounters.push_back(15867);
        internalCounters.push_back(15952);
        internalCounters.push_back(16037);
        internalCounters.push_back(16122);
        internalCounters.push_back(14856);
        internalCounters.push_back(14941);
        internalCounters.push_back(15026);
        internalCounters.push_back(15111);
        internalCounters.push_back(15196);
        internalCounters.push_back(15281);
        internalCounters.push_back(15366);
        internalCounters.push_back(15451);
        internalCounters.push_back(15536);
        internalCounters.push_back(15621);
        internalCounters.push_back(15706);
        internalCounters.push_back(15791);
        internalCounters.push_back(15876);
        internalCounters.push_back(15961);
        internalCounters.push_back(16046);
        internalCounters.push_back(16131);
        internalCounters.push_back(14857);
        internalCounters.push_back(14942);
        internalCounters.push_back(15027);
        internalCounters.push_back(15112);
        internalCounters.push_back(15197);
        internalCounters.push_back(15282);
        internalCounters.push_back(15367);
        internalCounters.push_back(15452);
        internalCounters.push_back(15537);
        internalCounters.push_back(15622);
        internalCounters.push_back(15707);
        internalCounters.push_back(15792);
        internalCounters.push_back(15877);
        internalCounters.push_back(15962);
        internalCounters.push_back(16047);
        internalCounters.push_back(16132);
        internalCounters.push_back(14858);
        internalCounters.push_back(14943);
        internalCounters.push_back(15028);
        internalCounters.push_back(15113);
        internalCounters.push_back(15198);
        internalCounters.push_back(15283);
        internalCounters.push_back(15368);
        internalCounters.push_back(15453);
        internalCounters.push_back(15538);
        internalCounters.push_back(15623);
        internalCounters.push_back(15708);
        internalCounters.push_back(15793);
        internalCounters.push_back(15878);
        internalCounters.push_back(15963);
        internalCounters.push_back(16048);
        internalCounters.push_back(16133);
        internalCounters.push_back(14859);
        internalCounters.push_back(14944);
        internalCounters.push_back(15029);
        internalCounters.push_back(15114);
        internalCounters.push_back(15199);
        internalCounters.push_back(15284);
        internalCounters.push_back(15369);
        internalCounters.push_back(15454);
        internalCounters.push_back(15539);
        internalCounters.push_back(15624);
        internalCounters.push_back(15709);
        internalCounters.push_back(15794);
        internalCounters.push_back(15879);
        internalCounters.push_back(15964);
        internalCounters.push_back(16049);
        internalCounters.push_back(16134);

        c.DefineDerivedCounter("L1CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum64,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "6deaf002-3cac-2d2d-7b89-566c7a52b08e");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9383);
        internalCounters.push_back(9665);
        internalCounters.push_back(9947);
        internalCounters.push_back(10229);
        internalCounters.push_back(10511);
        internalCounters.push_back(10793);
        internalCounters.push_back(11075);
        internalCounters.push_back(11357);
        internalCounters.push_back(11639);
        internalCounters.push_back(11921);
        internalCounters.push_back(12203);
        internalCounters.push_back(12485);
        internalCounters.push_back(12767);
        internalCounters.push_back(13049);
        internalCounters.push_back(13331);
        internalCounters.push_back(13613);
        internalCounters.push_back(9385);
        internalCounters.push_back(9667);
        internalCounters.push_back(9949);
        internalCounters.push_back(10231);
        internalCounters.push_back(10513);
        internalCounters.push_back(10795);
        internalCounters.push_back(11077);
        internalCounters.push_back(11359);
        internalCounters.push_back(11641);
        internalCounters.push_back(11923);
        internalCounters.push_back(12205);
        internalCounters.push_back(12487);
        internalCounters.push_back(12769);
        internalCounters.push_back(13051);
        internalCounters.push_back(13333);
        internalCounters.push_back(13615);

        c.DefineDerivedCounter("L2CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L2 cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "7507935e-ed29-f169-ee27-9b0fa9b88f3c");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7404);
        internalCounters.push_back(7523);
        internalCounters.push_back(7642);
        internalCounters.push_back(7761);
        internalCounters.push_back(7880);
        internalCounters.push_back(7999);
        internalCounters.push_back(8118);
        internalCounters.push_back(8237);
        internalCounters.push_back(8356);
        internalCounters.push_back(8475);
        internalCounters.push_back(8594);
        internalCounters.push_back(8713);
        internalCounters.push_back(8832);
        internalCounters.push_back(8951);
        internalCounters.push_back(9070);
        internalCounters.push_back(9189);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14793);
        internalCounters.push_back(14878);
        internalCounters.push_back(14963);
        internalCounters.push_back(15048);
        internalCounters.push_back(15133);
        internalCounters.push_back(15218);
        internalCounters.push_back(15303);
        internalCounters.push_back(15388);
        internalCounters.push_back(15473);
        internalCounters.push_back(15558);
        internalCounters.push_back(15643);
        internalCounters.push_back(15728);
        internalCounters.push_back(15813);
        internalCounters.push_back(15898);
        internalCounters.push_back(15983);
        internalCounters.push_back(16068);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9396);
        internalCounters.push_back(9678);
        internalCounters.push_back(9960);
        internalCounters.push_back(10242);
        internalCounters.push_back(10524);
        internalCounters.push_back(10806);
        internalCounters.push_back(11088);
        internalCounters.push_back(11370);
        internalCounters.push_back(11652);
        internalCounters.push_back(11934);
        internalCounters.push_back(12216);
        internalCounters.push_back(12498);
        internalCounters.push_back(12780);
        internalCounters.push_back(13062);
        internalCounters.push_back(13344);
        internalCounters.push_back(13626);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4282);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6");
    }
}

