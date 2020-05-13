//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions for CL GFX9 
//==============================================================================

#include "gpa_counter.h"
#include "public_counter_definitions_cl_gfx9.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersCLGfx9(GPA_DerivedCounters& c)
{
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4217);

        c.DefineDerivedCounter("Wavefronts", "General", "Total wavefronts.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "e8999836-489d-80a6-8e94-2c3ea191fd58");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4239);
        internalCounters.push_back(4217);

        c.DefineDerivedCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4243);
        internalCounters.push_back(4217);

        c.DefineDerivedCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4241);
        internalCounters.push_back(7514);
        internalCounters.push_back(7633);
        internalCounters.push_back(7752);
        internalCounters.push_back(7871);
        internalCounters.push_back(7990);
        internalCounters.push_back(8109);
        internalCounters.push_back(8228);
        internalCounters.push_back(8347);
        internalCounters.push_back(8466);
        internalCounters.push_back(8585);
        internalCounters.push_back(8704);
        internalCounters.push_back(8823);
        internalCounters.push_back(8942);
        internalCounters.push_back(9061);
        internalCounters.push_back(9180);
        internalCounters.push_back(9299);
        internalCounters.push_back(4217);

        c.DefineDerivedCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/", "85970f8f-0b2c-6431-9e52-7999236e6e8a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4244);
        internalCounters.push_back(4217);

        c.DefineDerivedCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4240);
        internalCounters.push_back(7515);
        internalCounters.push_back(7634);
        internalCounters.push_back(7753);
        internalCounters.push_back(7872);
        internalCounters.push_back(7991);
        internalCounters.push_back(8110);
        internalCounters.push_back(8229);
        internalCounters.push_back(8348);
        internalCounters.push_back(8467);
        internalCounters.push_back(8586);
        internalCounters.push_back(8705);
        internalCounters.push_back(8824);
        internalCounters.push_back(8943);
        internalCounters.push_back(9062);
        internalCounters.push_back(9181);
        internalCounters.push_back(9300);
        internalCounters.push_back(4217);

        c.DefineDerivedCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/", "d8154a17-224d-704e-73d2-bb5d150f3196");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4245);
        internalCounters.push_back(4246);
        internalCounters.push_back(4217);

        c.DefineDerivedCounter("FlatVMemInsts", "General", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,-,2,/", "05e4a953-c59a-e722-872b-e4bc7526bcee");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4247);
        internalCounters.push_back(4246);
        internalCounters.push_back(4217);

        c.DefineDerivedCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control). Excludes FLAT instructions that read from or write to LDS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,-,2,/", "be9bbead-f82a-a2c6-8333-1a5c4ce5ee98");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4246);
        internalCounters.push_back(4217);

        c.DefineDerivedCounter("FlatLDSInsts", "LocalMemory", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "0f7d8f58-1750-a36f-d03e-85a2d9cd6e08");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4248);
        internalCounters.push_back(4217);

        c.DefineDerivedCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4298);
        internalCounters.push_back(4284);

        c.DefineDerivedCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,(64),*,/,(100),*,(100),min", "ffea5f90-624f-67dd-4ca6-74911f4c85d3");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4284);
        internalCounters.push_back(1799);

        c.DefineDerivedCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4297);
        internalCounters.push_back(1799);

        c.DefineDerivedCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_CUS,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d");
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

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(64),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33");
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

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+,(1024),/", "e09d95da-2772-f7cb-51f5-4fad27bb998b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14871);
        internalCounters.push_back(14956);
        internalCounters.push_back(15041);
        internalCounters.push_back(15126);
        internalCounters.push_back(15211);
        internalCounters.push_back(15296);
        internalCounters.push_back(15381);
        internalCounters.push_back(15466);
        internalCounters.push_back(15551);
        internalCounters.push_back(15636);
        internalCounters.push_back(15721);
        internalCounters.push_back(15806);
        internalCounters.push_back(15891);
        internalCounters.push_back(15976);
        internalCounters.push_back(16061);
        internalCounters.push_back(16146);
        internalCounters.push_back(14880);
        internalCounters.push_back(14965);
        internalCounters.push_back(15050);
        internalCounters.push_back(15135);
        internalCounters.push_back(15220);
        internalCounters.push_back(15305);
        internalCounters.push_back(15390);
        internalCounters.push_back(15475);
        internalCounters.push_back(15560);
        internalCounters.push_back(15645);
        internalCounters.push_back(15730);
        internalCounters.push_back(15815);
        internalCounters.push_back(15900);
        internalCounters.push_back(15985);
        internalCounters.push_back(16070);
        internalCounters.push_back(16155);
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
        internalCounters.push_back(15731);
        internalCounters.push_back(15816);
        internalCounters.push_back(15901);
        internalCounters.push_back(15986);
        internalCounters.push_back(16071);
        internalCounters.push_back(16156);
        internalCounters.push_back(14882);
        internalCounters.push_back(14967);
        internalCounters.push_back(15052);
        internalCounters.push_back(15137);
        internalCounters.push_back(15222);
        internalCounters.push_back(15307);
        internalCounters.push_back(15392);
        internalCounters.push_back(15477);
        internalCounters.push_back(15562);
        internalCounters.push_back(15647);
        internalCounters.push_back(15732);
        internalCounters.push_back(15817);
        internalCounters.push_back(15902);
        internalCounters.push_back(15987);
        internalCounters.push_back(16072);
        internalCounters.push_back(16157);
        internalCounters.push_back(14883);
        internalCounters.push_back(14968);
        internalCounters.push_back(15053);
        internalCounters.push_back(15138);
        internalCounters.push_back(15223);
        internalCounters.push_back(15308);
        internalCounters.push_back(15393);
        internalCounters.push_back(15478);
        internalCounters.push_back(15563);
        internalCounters.push_back(15648);
        internalCounters.push_back(15733);
        internalCounters.push_back(15818);
        internalCounters.push_back(15903);
        internalCounters.push_back(15988);
        internalCounters.push_back(16073);
        internalCounters.push_back(16158);

        c.DefineDerivedCounter("L1CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum64,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "6deaf002-3cac-2d2d-7b89-566c7a52b08e");
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

        c.DefineDerivedCounter("L2CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L2 cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "7507935e-ed29-f169-ee27-9b0fa9b88f3c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7428);
        internalCounters.push_back(7547);
        internalCounters.push_back(7666);
        internalCounters.push_back(7785);
        internalCounters.push_back(7904);
        internalCounters.push_back(8023);
        internalCounters.push_back(8142);
        internalCounters.push_back(8261);
        internalCounters.push_back(8380);
        internalCounters.push_back(8499);
        internalCounters.push_back(8618);
        internalCounters.push_back(8737);
        internalCounters.push_back(8856);
        internalCounters.push_back(8975);
        internalCounters.push_back(9094);
        internalCounters.push_back(9213);
        internalCounters.push_back(1799);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14817);
        internalCounters.push_back(14902);
        internalCounters.push_back(14987);
        internalCounters.push_back(15072);
        internalCounters.push_back(15157);
        internalCounters.push_back(15242);
        internalCounters.push_back(15327);
        internalCounters.push_back(15412);
        internalCounters.push_back(15497);
        internalCounters.push_back(15582);
        internalCounters.push_back(15667);
        internalCounters.push_back(15752);
        internalCounters.push_back(15837);
        internalCounters.push_back(15922);
        internalCounters.push_back(16007);
        internalCounters.push_back(16092);
        internalCounters.push_back(1799);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
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

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4306);
        internalCounters.push_back(1799);

        c.DefineDerivedCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6");
    }
}

