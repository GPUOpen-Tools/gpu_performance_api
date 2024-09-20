//==============================================================================
// Copyright (c) 2010-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for CL GFX11.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_cl_gfx11.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersClGfx11(GpaDerivedCounters& c)
{
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4908);

        c.DefineDerivedCounter("Wavefronts", "General", "Total wavefronts.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "e8999836-489d-80a6-8e94-2c3ea191fd58");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24344);
        internal_counters.push_back(24286);

        c.DefineDerivedCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24340);
        internal_counters.push_back(24286);

        c.DefineDerivedCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24348);
        internal_counters.push_back(24286);

        c.DefineDerivedCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "85970f8f-0b2c-6431-9e52-7999236e6e8a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24341);
        internal_counters.push_back(24286);

        c.DefineDerivedCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24349);
        internal_counters.push_back(24286);

        c.DefineDerivedCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "d8154a17-224d-704e-73d2-bb5d150f3196");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24339);
        internal_counters.push_back(24286);

        c.DefineDerivedCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "852ccd67-d2eb-d238-567a-0d1f7bf5f34f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24336);
        internal_counters.push_back(24286);

        c.DefineDerivedCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24362);
        internal_counters.push_back(24385);
        internal_counters.push_back(24287);

        c.DefineDerivedCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,(64),(32),2,ifnotzero,*,/,(100),*,(100),min", "435fc505-4d15-095e-79f1-80346bcd0a24");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24385);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24340);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16616);
        internal_counters.push_back(16875);
        internal_counters.push_back(17134);
        internal_counters.push_back(17393);
        internal_counters.push_back(17652);
        internal_counters.push_back(17911);
        internal_counters.push_back(18170);
        internal_counters.push_back(18429);
        internal_counters.push_back(18688);
        internal_counters.push_back(18947);
        internal_counters.push_back(19206);
        internal_counters.push_back(19465);
        internal_counters.push_back(19724);
        internal_counters.push_back(19983);
        internal_counters.push_back(20242);
        internal_counters.push_back(20501);
        internal_counters.push_back(16617);
        internal_counters.push_back(16876);
        internal_counters.push_back(17135);
        internal_counters.push_back(17394);
        internal_counters.push_back(17653);
        internal_counters.push_back(17912);
        internal_counters.push_back(18171);
        internal_counters.push_back(18430);
        internal_counters.push_back(18689);
        internal_counters.push_back(18948);
        internal_counters.push_back(19207);
        internal_counters.push_back(19466);
        internal_counters.push_back(19725);
        internal_counters.push_back(19984);
        internal_counters.push_back(20243);
        internal_counters.push_back(20502);
        internal_counters.push_back(16618);
        internal_counters.push_back(16877);
        internal_counters.push_back(17136);
        internal_counters.push_back(17395);
        internal_counters.push_back(17654);
        internal_counters.push_back(17913);
        internal_counters.push_back(18172);
        internal_counters.push_back(18431);
        internal_counters.push_back(18690);
        internal_counters.push_back(18949);
        internal_counters.push_back(19208);
        internal_counters.push_back(19467);
        internal_counters.push_back(19726);
        internal_counters.push_back(19985);
        internal_counters.push_back(20244);
        internal_counters.push_back(20503);
        internal_counters.push_back(16619);
        internal_counters.push_back(16878);
        internal_counters.push_back(17137);
        internal_counters.push_back(17396);
        internal_counters.push_back(17655);
        internal_counters.push_back(17914);
        internal_counters.push_back(18173);
        internal_counters.push_back(18432);
        internal_counters.push_back(18691);
        internal_counters.push_back(18950);
        internal_counters.push_back(19209);
        internal_counters.push_back(19468);
        internal_counters.push_back(19727);
        internal_counters.push_back(19986);
        internal_counters.push_back(20245);
        internal_counters.push_back(20504);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeKilobytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,(96),*,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,(128),*,sum4,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16600);
        internal_counters.push_back(16859);
        internal_counters.push_back(17118);
        internal_counters.push_back(17377);
        internal_counters.push_back(17636);
        internal_counters.push_back(17895);
        internal_counters.push_back(18154);
        internal_counters.push_back(18413);
        internal_counters.push_back(18672);
        internal_counters.push_back(18931);
        internal_counters.push_back(19190);
        internal_counters.push_back(19449);
        internal_counters.push_back(19708);
        internal_counters.push_back(19967);
        internal_counters.push_back(20226);
        internal_counters.push_back(20485);
        internal_counters.push_back(16602);
        internal_counters.push_back(16861);
        internal_counters.push_back(17120);
        internal_counters.push_back(17379);
        internal_counters.push_back(17638);
        internal_counters.push_back(17897);
        internal_counters.push_back(18156);
        internal_counters.push_back(18415);
        internal_counters.push_back(18674);
        internal_counters.push_back(18933);
        internal_counters.push_back(19192);
        internal_counters.push_back(19451);
        internal_counters.push_back(19710);
        internal_counters.push_back(19969);
        internal_counters.push_back(20228);
        internal_counters.push_back(20487);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeKilobytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+,(1024),/", "e09d95da-2772-f7cb-51f5-4fad27bb998b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12379);
        internal_counters.push_back(12458);
        internal_counters.push_back(12537);
        internal_counters.push_back(12616);
        internal_counters.push_back(12695);
        internal_counters.push_back(12774);
        internal_counters.push_back(12853);
        internal_counters.push_back(12932);
        internal_counters.push_back(13011);
        internal_counters.push_back(13090);
        internal_counters.push_back(13169);
        internal_counters.push_back(13248);
        internal_counters.push_back(13327);
        internal_counters.push_back(13406);
        internal_counters.push_back(13485);
        internal_counters.push_back(13564);
        internal_counters.push_back(12387);
        internal_counters.push_back(12466);
        internal_counters.push_back(12545);
        internal_counters.push_back(12624);
        internal_counters.push_back(12703);
        internal_counters.push_back(12782);
        internal_counters.push_back(12861);
        internal_counters.push_back(12940);
        internal_counters.push_back(13019);
        internal_counters.push_back(13098);
        internal_counters.push_back(13177);
        internal_counters.push_back(13256);
        internal_counters.push_back(13335);
        internal_counters.push_back(13414);
        internal_counters.push_back(13493);
        internal_counters.push_back(13572);

        c.DefineDerivedCounter("L0CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L0 cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "be1e0578-82b8-ad7f-ba3f-3afce150937a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16011);
        internal_counters.push_back(16015);

        c.DefineDerivedCounter("L1CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Writes and atomics always miss this cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),1,0,/,-,(100),*,0,ifnotzero", "b10c589c-f7a5-b8f2-46c2-e0aed4a84105");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16520);
        internal_counters.push_back(16779);
        internal_counters.push_back(17038);
        internal_counters.push_back(17297);
        internal_counters.push_back(17556);
        internal_counters.push_back(17815);
        internal_counters.push_back(18074);
        internal_counters.push_back(18333);
        internal_counters.push_back(18592);
        internal_counters.push_back(18851);
        internal_counters.push_back(19110);
        internal_counters.push_back(19369);
        internal_counters.push_back(19628);
        internal_counters.push_back(19887);
        internal_counters.push_back(20146);
        internal_counters.push_back(20405);
        internal_counters.push_back(16560);
        internal_counters.push_back(16819);
        internal_counters.push_back(17078);
        internal_counters.push_back(17337);
        internal_counters.push_back(17596);
        internal_counters.push_back(17855);
        internal_counters.push_back(18114);
        internal_counters.push_back(18373);
        internal_counters.push_back(18632);
        internal_counters.push_back(18891);
        internal_counters.push_back(19150);
        internal_counters.push_back(19409);
        internal_counters.push_back(19668);
        internal_counters.push_back(19927);
        internal_counters.push_back(20186);
        internal_counters.push_back(20445);

        c.DefineDerivedCounter("L2CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L2 cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "7507935e-ed29-f169-ee27-9b0fa9b88f3c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5281);
        internal_counters.push_back(5517);
        internal_counters.push_back(5753);
        internal_counters.push_back(5989);
        internal_counters.push_back(6225);
        internal_counters.push_back(6461);
        internal_counters.push_back(6697);
        internal_counters.push_back(6933);
        internal_counters.push_back(7169);
        internal_counters.push_back(7405);
        internal_counters.push_back(7641);
        internal_counters.push_back(7877);
        internal_counters.push_back(8113);
        internal_counters.push_back(8349);
        internal_counters.push_back(8585);
        internal_counters.push_back(8821);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12409);
        internal_counters.push_back(12488);
        internal_counters.push_back(12567);
        internal_counters.push_back(12646);
        internal_counters.push_back(12725);
        internal_counters.push_back(12804);
        internal_counters.push_back(12883);
        internal_counters.push_back(12962);
        internal_counters.push_back(13041);
        internal_counters.push_back(13120);
        internal_counters.push_back(13199);
        internal_counters.push_back(13278);
        internal_counters.push_back(13357);
        internal_counters.push_back(13436);
        internal_counters.push_back(13515);
        internal_counters.push_back(13594);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16605);
        internal_counters.push_back(16864);
        internal_counters.push_back(17123);
        internal_counters.push_back(17382);
        internal_counters.push_back(17641);
        internal_counters.push_back(17900);
        internal_counters.push_back(18159);
        internal_counters.push_back(18418);
        internal_counters.push_back(18677);
        internal_counters.push_back(18936);
        internal_counters.push_back(19195);
        internal_counters.push_back(19454);
        internal_counters.push_back(19713);
        internal_counters.push_back(19972);
        internal_counters.push_back(20231);
        internal_counters.push_back(20490);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24538);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6");
    }
}

