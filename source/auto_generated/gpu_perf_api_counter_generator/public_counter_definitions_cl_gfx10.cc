//==============================================================================
// Copyright (c) 2010-2022 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for CL GFX10.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_cl_gfx10.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersClGfx10(GpaDerivedCounters& c)
{
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5133);

        c.DefineDerivedCounter("Wavefronts", "General", "Total wavefronts.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "e8999836-489d-80a6-8e94-2c3ea191fd58");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5193);
        internal_counters.push_back(5133);

        c.DefineDerivedCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5189);
        internal_counters.push_back(5133);

        c.DefineDerivedCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5198);
        internal_counters.push_back(5133);

        c.DefineDerivedCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "85970f8f-0b2c-6431-9e52-7999236e6e8a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5190);
        internal_counters.push_back(5133);

        c.DefineDerivedCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5199);
        internal_counters.push_back(5133);

        c.DefineDerivedCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "d8154a17-224d-704e-73d2-bb5d150f3196");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5188);
        internal_counters.push_back(5133);

        c.DefineDerivedCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "852ccd67-d2eb-d238-567a-0d1f7bf5f34f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5184);
        internal_counters.push_back(5133);

        c.DefineDerivedCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5211);
        internal_counters.push_back(5246);
        internal_counters.push_back(5134);

        c.DefineDerivedCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,(64),(32),2,ifnotzero,*,/,(100),*,(100),min", "435fc505-4d15-095e-79f1-80346bcd0a24");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5246);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5189);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(18606);
        internal_counters.push_back(18841);
        internal_counters.push_back(19076);
        internal_counters.push_back(19311);
        internal_counters.push_back(19546);
        internal_counters.push_back(19781);
        internal_counters.push_back(20016);
        internal_counters.push_back(20251);
        internal_counters.push_back(20486);
        internal_counters.push_back(20721);
        internal_counters.push_back(20956);
        internal_counters.push_back(21191);
        internal_counters.push_back(21426);
        internal_counters.push_back(21661);
        internal_counters.push_back(21896);
        internal_counters.push_back(22131);
        internal_counters.push_back(18607);
        internal_counters.push_back(18842);
        internal_counters.push_back(19077);
        internal_counters.push_back(19312);
        internal_counters.push_back(19547);
        internal_counters.push_back(19782);
        internal_counters.push_back(20017);
        internal_counters.push_back(20252);
        internal_counters.push_back(20487);
        internal_counters.push_back(20722);
        internal_counters.push_back(20957);
        internal_counters.push_back(21192);
        internal_counters.push_back(21427);
        internal_counters.push_back(21662);
        internal_counters.push_back(21897);
        internal_counters.push_back(22132);
        internal_counters.push_back(18608);
        internal_counters.push_back(18843);
        internal_counters.push_back(19078);
        internal_counters.push_back(19313);
        internal_counters.push_back(19548);
        internal_counters.push_back(19783);
        internal_counters.push_back(20018);
        internal_counters.push_back(20253);
        internal_counters.push_back(20488);
        internal_counters.push_back(20723);
        internal_counters.push_back(20958);
        internal_counters.push_back(21193);
        internal_counters.push_back(21428);
        internal_counters.push_back(21663);
        internal_counters.push_back(21898);
        internal_counters.push_back(22133);
        internal_counters.push_back(18609);
        internal_counters.push_back(18844);
        internal_counters.push_back(19079);
        internal_counters.push_back(19314);
        internal_counters.push_back(19549);
        internal_counters.push_back(19784);
        internal_counters.push_back(20019);
        internal_counters.push_back(20254);
        internal_counters.push_back(20489);
        internal_counters.push_back(20724);
        internal_counters.push_back(20959);
        internal_counters.push_back(21194);
        internal_counters.push_back(21429);
        internal_counters.push_back(21664);
        internal_counters.push_back(21899);
        internal_counters.push_back(22134);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeKilobytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,(96),*,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,(128),*,sum4,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(18592);
        internal_counters.push_back(18827);
        internal_counters.push_back(19062);
        internal_counters.push_back(19297);
        internal_counters.push_back(19532);
        internal_counters.push_back(19767);
        internal_counters.push_back(20002);
        internal_counters.push_back(20237);
        internal_counters.push_back(20472);
        internal_counters.push_back(20707);
        internal_counters.push_back(20942);
        internal_counters.push_back(21177);
        internal_counters.push_back(21412);
        internal_counters.push_back(21647);
        internal_counters.push_back(21882);
        internal_counters.push_back(22117);
        internal_counters.push_back(18593);
        internal_counters.push_back(18828);
        internal_counters.push_back(19063);
        internal_counters.push_back(19298);
        internal_counters.push_back(19533);
        internal_counters.push_back(19768);
        internal_counters.push_back(20003);
        internal_counters.push_back(20238);
        internal_counters.push_back(20473);
        internal_counters.push_back(20708);
        internal_counters.push_back(20943);
        internal_counters.push_back(21178);
        internal_counters.push_back(21413);
        internal_counters.push_back(21648);
        internal_counters.push_back(21883);
        internal_counters.push_back(22118);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeKilobytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+,(1024),/", "e09d95da-2772-f7cb-51f5-4fad27bb998b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14051);
        internal_counters.push_back(14128);
        internal_counters.push_back(14205);
        internal_counters.push_back(14282);
        internal_counters.push_back(14359);
        internal_counters.push_back(14436);
        internal_counters.push_back(14513);
        internal_counters.push_back(14590);
        internal_counters.push_back(14667);
        internal_counters.push_back(14744);
        internal_counters.push_back(14821);
        internal_counters.push_back(14898);
        internal_counters.push_back(14975);
        internal_counters.push_back(15052);
        internal_counters.push_back(15129);
        internal_counters.push_back(15206);
        internal_counters.push_back(14060);
        internal_counters.push_back(14137);
        internal_counters.push_back(14214);
        internal_counters.push_back(14291);
        internal_counters.push_back(14368);
        internal_counters.push_back(14445);
        internal_counters.push_back(14522);
        internal_counters.push_back(14599);
        internal_counters.push_back(14676);
        internal_counters.push_back(14753);
        internal_counters.push_back(14830);
        internal_counters.push_back(14907);
        internal_counters.push_back(14984);
        internal_counters.push_back(15061);
        internal_counters.push_back(15138);
        internal_counters.push_back(15215);

        c.DefineDerivedCounter("L0CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L0 cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "be1e0578-82b8-ad7f-ba3f-3afce150937a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(17951);
        internal_counters.push_back(17955);

        c.DefineDerivedCounter("L1CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Writes and atomics always miss this cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),1,0,/,-,(100),*,0,ifnotzero", "b10c589c-f7a5-b8f2-46c2-e0aed4a84105");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(18520);
        internal_counters.push_back(18755);
        internal_counters.push_back(18990);
        internal_counters.push_back(19225);
        internal_counters.push_back(19460);
        internal_counters.push_back(19695);
        internal_counters.push_back(19930);
        internal_counters.push_back(20165);
        internal_counters.push_back(20400);
        internal_counters.push_back(20635);
        internal_counters.push_back(20870);
        internal_counters.push_back(21105);
        internal_counters.push_back(21340);
        internal_counters.push_back(21575);
        internal_counters.push_back(21810);
        internal_counters.push_back(22045);
        internal_counters.push_back(18552);
        internal_counters.push_back(18787);
        internal_counters.push_back(19022);
        internal_counters.push_back(19257);
        internal_counters.push_back(19492);
        internal_counters.push_back(19727);
        internal_counters.push_back(19962);
        internal_counters.push_back(20197);
        internal_counters.push_back(20432);
        internal_counters.push_back(20667);
        internal_counters.push_back(20902);
        internal_counters.push_back(21137);
        internal_counters.push_back(21372);
        internal_counters.push_back(21607);
        internal_counters.push_back(21842);
        internal_counters.push_back(22077);

        c.DefineDerivedCounter("L2CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L2 cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "7507935e-ed29-f169-ee27-9b0fa9b88f3c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9465);
        internal_counters.push_back(9691);
        internal_counters.push_back(9917);
        internal_counters.push_back(10143);
        internal_counters.push_back(10369);
        internal_counters.push_back(10595);
        internal_counters.push_back(10821);
        internal_counters.push_back(11047);
        internal_counters.push_back(11273);
        internal_counters.push_back(11499);
        internal_counters.push_back(11725);
        internal_counters.push_back(11951);
        internal_counters.push_back(12177);
        internal_counters.push_back(12403);
        internal_counters.push_back(12629);
        internal_counters.push_back(12855);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14078);
        internal_counters.push_back(14155);
        internal_counters.push_back(14232);
        internal_counters.push_back(14309);
        internal_counters.push_back(14386);
        internal_counters.push_back(14463);
        internal_counters.push_back(14540);
        internal_counters.push_back(14617);
        internal_counters.push_back(14694);
        internal_counters.push_back(14771);
        internal_counters.push_back(14848);
        internal_counters.push_back(14925);
        internal_counters.push_back(15002);
        internal_counters.push_back(15079);
        internal_counters.push_back(15156);
        internal_counters.push_back(15233);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(18596);
        internal_counters.push_back(18831);
        internal_counters.push_back(19066);
        internal_counters.push_back(19301);
        internal_counters.push_back(19536);
        internal_counters.push_back(19771);
        internal_counters.push_back(20006);
        internal_counters.push_back(20241);
        internal_counters.push_back(20476);
        internal_counters.push_back(20711);
        internal_counters.push_back(20946);
        internal_counters.push_back(21181);
        internal_counters.push_back(21416);
        internal_counters.push_back(21651);
        internal_counters.push_back(21886);
        internal_counters.push_back(22121);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5414);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6");
    }
}

