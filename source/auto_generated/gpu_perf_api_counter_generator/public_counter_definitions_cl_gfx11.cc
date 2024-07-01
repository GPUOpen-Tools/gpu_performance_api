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
        internal_counters.push_back(24304);
        internal_counters.push_back(4908);

        c.DefineDerivedCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24300);
        internal_counters.push_back(4908);

        c.DefineDerivedCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24308);
        internal_counters.push_back(4908);

        c.DefineDerivedCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "85970f8f-0b2c-6431-9e52-7999236e6e8a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24301);
        internal_counters.push_back(4908);

        c.DefineDerivedCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24309);
        internal_counters.push_back(4908);

        c.DefineDerivedCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "d8154a17-224d-704e-73d2-bb5d150f3196");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24299);
        internal_counters.push_back(4908);

        c.DefineDerivedCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "852ccd67-d2eb-d238-567a-0d1f7bf5f34f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24296);
        internal_counters.push_back(4908);

        c.DefineDerivedCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24322);
        internal_counters.push_back(24345);
        internal_counters.push_back(4909);

        c.DefineDerivedCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,(64),(32),2,ifnotzero,*,/,(100),*,(100),min", "435fc505-4d15-095e-79f1-80346bcd0a24");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24345);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24300);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16576);
        internal_counters.push_back(16835);
        internal_counters.push_back(17094);
        internal_counters.push_back(17353);
        internal_counters.push_back(17612);
        internal_counters.push_back(17871);
        internal_counters.push_back(18130);
        internal_counters.push_back(18389);
        internal_counters.push_back(18648);
        internal_counters.push_back(18907);
        internal_counters.push_back(19166);
        internal_counters.push_back(19425);
        internal_counters.push_back(19684);
        internal_counters.push_back(19943);
        internal_counters.push_back(20202);
        internal_counters.push_back(20461);
        internal_counters.push_back(16577);
        internal_counters.push_back(16836);
        internal_counters.push_back(17095);
        internal_counters.push_back(17354);
        internal_counters.push_back(17613);
        internal_counters.push_back(17872);
        internal_counters.push_back(18131);
        internal_counters.push_back(18390);
        internal_counters.push_back(18649);
        internal_counters.push_back(18908);
        internal_counters.push_back(19167);
        internal_counters.push_back(19426);
        internal_counters.push_back(19685);
        internal_counters.push_back(19944);
        internal_counters.push_back(20203);
        internal_counters.push_back(20462);
        internal_counters.push_back(16578);
        internal_counters.push_back(16837);
        internal_counters.push_back(17096);
        internal_counters.push_back(17355);
        internal_counters.push_back(17614);
        internal_counters.push_back(17873);
        internal_counters.push_back(18132);
        internal_counters.push_back(18391);
        internal_counters.push_back(18650);
        internal_counters.push_back(18909);
        internal_counters.push_back(19168);
        internal_counters.push_back(19427);
        internal_counters.push_back(19686);
        internal_counters.push_back(19945);
        internal_counters.push_back(20204);
        internal_counters.push_back(20463);
        internal_counters.push_back(16579);
        internal_counters.push_back(16838);
        internal_counters.push_back(17097);
        internal_counters.push_back(17356);
        internal_counters.push_back(17615);
        internal_counters.push_back(17874);
        internal_counters.push_back(18133);
        internal_counters.push_back(18392);
        internal_counters.push_back(18651);
        internal_counters.push_back(18910);
        internal_counters.push_back(19169);
        internal_counters.push_back(19428);
        internal_counters.push_back(19687);
        internal_counters.push_back(19946);
        internal_counters.push_back(20205);
        internal_counters.push_back(20464);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeKilobytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,(96),*,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,(128),*,sum4,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33");
    }
    {
        vector<GpaUInt32> internal_counters;
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
        internal_counters.push_back(16562);
        internal_counters.push_back(16821);
        internal_counters.push_back(17080);
        internal_counters.push_back(17339);
        internal_counters.push_back(17598);
        internal_counters.push_back(17857);
        internal_counters.push_back(18116);
        internal_counters.push_back(18375);
        internal_counters.push_back(18634);
        internal_counters.push_back(18893);
        internal_counters.push_back(19152);
        internal_counters.push_back(19411);
        internal_counters.push_back(19670);
        internal_counters.push_back(19929);
        internal_counters.push_back(20188);
        internal_counters.push_back(20447);

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
        internal_counters.push_back(15971);
        internal_counters.push_back(15975);

        c.DefineDerivedCounter("L1CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Writes and atomics always miss this cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),1,0,/,-,(100),*,0,ifnotzero", "b10c589c-f7a5-b8f2-46c2-e0aed4a84105");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16480);
        internal_counters.push_back(16739);
        internal_counters.push_back(16998);
        internal_counters.push_back(17257);
        internal_counters.push_back(17516);
        internal_counters.push_back(17775);
        internal_counters.push_back(18034);
        internal_counters.push_back(18293);
        internal_counters.push_back(18552);
        internal_counters.push_back(18811);
        internal_counters.push_back(19070);
        internal_counters.push_back(19329);
        internal_counters.push_back(19588);
        internal_counters.push_back(19847);
        internal_counters.push_back(20106);
        internal_counters.push_back(20365);
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
        internal_counters.push_back(16565);
        internal_counters.push_back(16824);
        internal_counters.push_back(17083);
        internal_counters.push_back(17342);
        internal_counters.push_back(17601);
        internal_counters.push_back(17860);
        internal_counters.push_back(18119);
        internal_counters.push_back(18378);
        internal_counters.push_back(18637);
        internal_counters.push_back(18896);
        internal_counters.push_back(19155);
        internal_counters.push_back(19414);
        internal_counters.push_back(19673);
        internal_counters.push_back(19932);
        internal_counters.push_back(20191);
        internal_counters.push_back(20450);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24498);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6");
    }
}

