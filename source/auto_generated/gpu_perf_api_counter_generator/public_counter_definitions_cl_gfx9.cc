//==============================================================================
// Copyright (c) 2010-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for CL GFX9.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_cl_gfx9.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersClGfx9(GpaDerivedCounters& c)
{
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4217);

        c.DefineDerivedCounter("Wavefronts", "General", "Total wavefronts.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "e8999836-489d-80a6-8e94-2c3ea191fd58");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4239);
        internal_counters.push_back(4217);

        c.DefineDerivedCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4243);
        internal_counters.push_back(4217);

        c.DefineDerivedCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4241);
        internal_counters.push_back(7514);
        internal_counters.push_back(7633);
        internal_counters.push_back(7752);
        internal_counters.push_back(7871);
        internal_counters.push_back(7990);
        internal_counters.push_back(8109);
        internal_counters.push_back(8228);
        internal_counters.push_back(8347);
        internal_counters.push_back(8466);
        internal_counters.push_back(8585);
        internal_counters.push_back(8704);
        internal_counters.push_back(8823);
        internal_counters.push_back(8942);
        internal_counters.push_back(9061);
        internal_counters.push_back(9180);
        internal_counters.push_back(9299);
        internal_counters.push_back(4217);

        c.DefineDerivedCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/", "85970f8f-0b2c-6431-9e52-7999236e6e8a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4244);
        internal_counters.push_back(4217);

        c.DefineDerivedCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4240);
        internal_counters.push_back(7515);
        internal_counters.push_back(7634);
        internal_counters.push_back(7753);
        internal_counters.push_back(7872);
        internal_counters.push_back(7991);
        internal_counters.push_back(8110);
        internal_counters.push_back(8229);
        internal_counters.push_back(8348);
        internal_counters.push_back(8467);
        internal_counters.push_back(8586);
        internal_counters.push_back(8705);
        internal_counters.push_back(8824);
        internal_counters.push_back(8943);
        internal_counters.push_back(9062);
        internal_counters.push_back(9181);
        internal_counters.push_back(9300);
        internal_counters.push_back(4217);

        c.DefineDerivedCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/", "d8154a17-224d-704e-73d2-bb5d150f3196");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4245);
        internal_counters.push_back(4246);
        internal_counters.push_back(4217);

        c.DefineDerivedCounter("FlatVMemInsts", "General", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,-,2,/", "05e4a953-c59a-e722-872b-e4bc7526bcee");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4247);
        internal_counters.push_back(4246);
        internal_counters.push_back(4217);

        c.DefineDerivedCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control). Excludes FLAT instructions that read from or write to LDS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,-,2,/", "be9bbead-f82a-a2c6-8333-1a5c4ce5ee98");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4246);
        internal_counters.push_back(4217);

        c.DefineDerivedCounter("FlatLDSInsts", "LocalMemory", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "0f7d8f58-1750-a36f-d03e-85a2d9cd6e08");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4248);
        internal_counters.push_back(4217);

        c.DefineDerivedCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4298);
        internal_counters.push_back(4284);

        c.DefineDerivedCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,(64),*,/,(100),*,(100),min", "ffea5f90-624f-67dd-4ca6-74911f4c85d3");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4284);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4297);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d");
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

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeKilobytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(64),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33");
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

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeKilobytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+,(1024),/", "e09d95da-2772-f7cb-51f5-4fad27bb998b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14871);
        internal_counters.push_back(14956);
        internal_counters.push_back(15041);
        internal_counters.push_back(15126);
        internal_counters.push_back(15211);
        internal_counters.push_back(15296);
        internal_counters.push_back(15381);
        internal_counters.push_back(15466);
        internal_counters.push_back(15551);
        internal_counters.push_back(15636);
        internal_counters.push_back(15721);
        internal_counters.push_back(15806);
        internal_counters.push_back(15891);
        internal_counters.push_back(15976);
        internal_counters.push_back(16061);
        internal_counters.push_back(16146);
        internal_counters.push_back(14880);
        internal_counters.push_back(14965);
        internal_counters.push_back(15050);
        internal_counters.push_back(15135);
        internal_counters.push_back(15220);
        internal_counters.push_back(15305);
        internal_counters.push_back(15390);
        internal_counters.push_back(15475);
        internal_counters.push_back(15560);
        internal_counters.push_back(15645);
        internal_counters.push_back(15730);
        internal_counters.push_back(15815);
        internal_counters.push_back(15900);
        internal_counters.push_back(15985);
        internal_counters.push_back(16070);
        internal_counters.push_back(16155);
        internal_counters.push_back(14881);
        internal_counters.push_back(14966);
        internal_counters.push_back(15051);
        internal_counters.push_back(15136);
        internal_counters.push_back(15221);
        internal_counters.push_back(15306);
        internal_counters.push_back(15391);
        internal_counters.push_back(15476);
        internal_counters.push_back(15561);
        internal_counters.push_back(15646);
        internal_counters.push_back(15731);
        internal_counters.push_back(15816);
        internal_counters.push_back(15901);
        internal_counters.push_back(15986);
        internal_counters.push_back(16071);
        internal_counters.push_back(16156);
        internal_counters.push_back(14882);
        internal_counters.push_back(14967);
        internal_counters.push_back(15052);
        internal_counters.push_back(15137);
        internal_counters.push_back(15222);
        internal_counters.push_back(15307);
        internal_counters.push_back(15392);
        internal_counters.push_back(15477);
        internal_counters.push_back(15562);
        internal_counters.push_back(15647);
        internal_counters.push_back(15732);
        internal_counters.push_back(15817);
        internal_counters.push_back(15902);
        internal_counters.push_back(15987);
        internal_counters.push_back(16072);
        internal_counters.push_back(16157);
        internal_counters.push_back(14883);
        internal_counters.push_back(14968);
        internal_counters.push_back(15053);
        internal_counters.push_back(15138);
        internal_counters.push_back(15223);
        internal_counters.push_back(15308);
        internal_counters.push_back(15393);
        internal_counters.push_back(15478);
        internal_counters.push_back(15563);
        internal_counters.push_back(15648);
        internal_counters.push_back(15733);
        internal_counters.push_back(15818);
        internal_counters.push_back(15903);
        internal_counters.push_back(15988);
        internal_counters.push_back(16073);
        internal_counters.push_back(16158);

        c.DefineDerivedCounter("L1CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum64,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "6deaf002-3cac-2d2d-7b89-566c7a52b08e");
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

        c.DefineDerivedCounter("L2CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L2 cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "7507935e-ed29-f169-ee27-9b0fa9b88f3c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7428);
        internal_counters.push_back(7547);
        internal_counters.push_back(7666);
        internal_counters.push_back(7785);
        internal_counters.push_back(7904);
        internal_counters.push_back(8023);
        internal_counters.push_back(8142);
        internal_counters.push_back(8261);
        internal_counters.push_back(8380);
        internal_counters.push_back(8499);
        internal_counters.push_back(8618);
        internal_counters.push_back(8737);
        internal_counters.push_back(8856);
        internal_counters.push_back(8975);
        internal_counters.push_back(9094);
        internal_counters.push_back(9213);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14817);
        internal_counters.push_back(14902);
        internal_counters.push_back(14987);
        internal_counters.push_back(15072);
        internal_counters.push_back(15157);
        internal_counters.push_back(15242);
        internal_counters.push_back(15327);
        internal_counters.push_back(15412);
        internal_counters.push_back(15497);
        internal_counters.push_back(15582);
        internal_counters.push_back(15667);
        internal_counters.push_back(15752);
        internal_counters.push_back(15837);
        internal_counters.push_back(15922);
        internal_counters.push_back(16007);
        internal_counters.push_back(16092);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
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

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4306);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6");
    }
}

