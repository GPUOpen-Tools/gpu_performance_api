//==============================================================================
// Copyright (c) 2010-2023 Advanced Micro Devices, Inc. All rights reserved.
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
        internal_counters.push_back(4868);

        c.DefineDerivedCounter("Wavefronts", "General", "Total wavefronts.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "e8999836-489d-80a6-8e94-2c3ea191fd58");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24112);
        internal_counters.push_back(4868);

        c.DefineDerivedCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24108);
        internal_counters.push_back(4868);

        c.DefineDerivedCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24116);
        internal_counters.push_back(4868);

        c.DefineDerivedCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "85970f8f-0b2c-6431-9e52-7999236e6e8a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24109);
        internal_counters.push_back(4868);

        c.DefineDerivedCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24117);
        internal_counters.push_back(4868);

        c.DefineDerivedCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "d8154a17-224d-704e-73d2-bb5d150f3196");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24107);
        internal_counters.push_back(4868);

        c.DefineDerivedCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "852ccd67-d2eb-d238-567a-0d1f7bf5f34f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24104);
        internal_counters.push_back(4868);

        c.DefineDerivedCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24130);
        internal_counters.push_back(24153);
        internal_counters.push_back(4869);

        c.DefineDerivedCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,(64),(32),2,ifnotzero,*,/,(100),*,(100),min", "435fc505-4d15-095e-79f1-80346bcd0a24");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24153);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24108);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16384);
        internal_counters.push_back(16643);
        internal_counters.push_back(16902);
        internal_counters.push_back(17161);
        internal_counters.push_back(17420);
        internal_counters.push_back(17679);
        internal_counters.push_back(17938);
        internal_counters.push_back(18197);
        internal_counters.push_back(18456);
        internal_counters.push_back(18715);
        internal_counters.push_back(18974);
        internal_counters.push_back(19233);
        internal_counters.push_back(19492);
        internal_counters.push_back(19751);
        internal_counters.push_back(20010);
        internal_counters.push_back(20269);
        internal_counters.push_back(16385);
        internal_counters.push_back(16644);
        internal_counters.push_back(16903);
        internal_counters.push_back(17162);
        internal_counters.push_back(17421);
        internal_counters.push_back(17680);
        internal_counters.push_back(17939);
        internal_counters.push_back(18198);
        internal_counters.push_back(18457);
        internal_counters.push_back(18716);
        internal_counters.push_back(18975);
        internal_counters.push_back(19234);
        internal_counters.push_back(19493);
        internal_counters.push_back(19752);
        internal_counters.push_back(20011);
        internal_counters.push_back(20270);
        internal_counters.push_back(16386);
        internal_counters.push_back(16645);
        internal_counters.push_back(16904);
        internal_counters.push_back(17163);
        internal_counters.push_back(17422);
        internal_counters.push_back(17681);
        internal_counters.push_back(17940);
        internal_counters.push_back(18199);
        internal_counters.push_back(18458);
        internal_counters.push_back(18717);
        internal_counters.push_back(18976);
        internal_counters.push_back(19235);
        internal_counters.push_back(19494);
        internal_counters.push_back(19753);
        internal_counters.push_back(20012);
        internal_counters.push_back(20271);
        internal_counters.push_back(16387);
        internal_counters.push_back(16646);
        internal_counters.push_back(16905);
        internal_counters.push_back(17164);
        internal_counters.push_back(17423);
        internal_counters.push_back(17682);
        internal_counters.push_back(17941);
        internal_counters.push_back(18200);
        internal_counters.push_back(18459);
        internal_counters.push_back(18718);
        internal_counters.push_back(18977);
        internal_counters.push_back(19236);
        internal_counters.push_back(19495);
        internal_counters.push_back(19754);
        internal_counters.push_back(20013);
        internal_counters.push_back(20272);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeKilobytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,(96),*,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,(128),*,sum4,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16368);
        internal_counters.push_back(16627);
        internal_counters.push_back(16886);
        internal_counters.push_back(17145);
        internal_counters.push_back(17404);
        internal_counters.push_back(17663);
        internal_counters.push_back(17922);
        internal_counters.push_back(18181);
        internal_counters.push_back(18440);
        internal_counters.push_back(18699);
        internal_counters.push_back(18958);
        internal_counters.push_back(19217);
        internal_counters.push_back(19476);
        internal_counters.push_back(19735);
        internal_counters.push_back(19994);
        internal_counters.push_back(20253);
        internal_counters.push_back(16370);
        internal_counters.push_back(16629);
        internal_counters.push_back(16888);
        internal_counters.push_back(17147);
        internal_counters.push_back(17406);
        internal_counters.push_back(17665);
        internal_counters.push_back(17924);
        internal_counters.push_back(18183);
        internal_counters.push_back(18442);
        internal_counters.push_back(18701);
        internal_counters.push_back(18960);
        internal_counters.push_back(19219);
        internal_counters.push_back(19478);
        internal_counters.push_back(19737);
        internal_counters.push_back(19996);
        internal_counters.push_back(20255);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeKilobytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+,(1024),/", "e09d95da-2772-f7cb-51f5-4fad27bb998b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12163);
        internal_counters.push_back(12241);
        internal_counters.push_back(12319);
        internal_counters.push_back(12397);
        internal_counters.push_back(12475);
        internal_counters.push_back(12553);
        internal_counters.push_back(12631);
        internal_counters.push_back(12709);
        internal_counters.push_back(12787);
        internal_counters.push_back(12865);
        internal_counters.push_back(12943);
        internal_counters.push_back(13021);
        internal_counters.push_back(13099);
        internal_counters.push_back(13177);
        internal_counters.push_back(13255);
        internal_counters.push_back(13333);
        internal_counters.push_back(12171);
        internal_counters.push_back(12249);
        internal_counters.push_back(12327);
        internal_counters.push_back(12405);
        internal_counters.push_back(12483);
        internal_counters.push_back(12561);
        internal_counters.push_back(12639);
        internal_counters.push_back(12717);
        internal_counters.push_back(12795);
        internal_counters.push_back(12873);
        internal_counters.push_back(12951);
        internal_counters.push_back(13029);
        internal_counters.push_back(13107);
        internal_counters.push_back(13185);
        internal_counters.push_back(13263);
        internal_counters.push_back(13341);

        c.DefineDerivedCounter("L0CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L0 cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "be1e0578-82b8-ad7f-ba3f-3afce150937a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15779);
        internal_counters.push_back(15783);

        c.DefineDerivedCounter("L1CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Writes and atomics always miss this cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),1,0,/,-,(100),*,0,ifnotzero", "b10c589c-f7a5-b8f2-46c2-e0aed4a84105");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16288);
        internal_counters.push_back(16547);
        internal_counters.push_back(16806);
        internal_counters.push_back(17065);
        internal_counters.push_back(17324);
        internal_counters.push_back(17583);
        internal_counters.push_back(17842);
        internal_counters.push_back(18101);
        internal_counters.push_back(18360);
        internal_counters.push_back(18619);
        internal_counters.push_back(18878);
        internal_counters.push_back(19137);
        internal_counters.push_back(19396);
        internal_counters.push_back(19655);
        internal_counters.push_back(19914);
        internal_counters.push_back(20173);
        internal_counters.push_back(16328);
        internal_counters.push_back(16587);
        internal_counters.push_back(16846);
        internal_counters.push_back(17105);
        internal_counters.push_back(17364);
        internal_counters.push_back(17623);
        internal_counters.push_back(17882);
        internal_counters.push_back(18141);
        internal_counters.push_back(18400);
        internal_counters.push_back(18659);
        internal_counters.push_back(18918);
        internal_counters.push_back(19177);
        internal_counters.push_back(19436);
        internal_counters.push_back(19695);
        internal_counters.push_back(19954);
        internal_counters.push_back(20213);

        c.DefineDerivedCounter("L2CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L2 cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "7507935e-ed29-f169-ee27-9b0fa9b88f3c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5241);
        internal_counters.push_back(5477);
        internal_counters.push_back(5713);
        internal_counters.push_back(5949);
        internal_counters.push_back(6185);
        internal_counters.push_back(6421);
        internal_counters.push_back(6657);
        internal_counters.push_back(6893);
        internal_counters.push_back(7129);
        internal_counters.push_back(7365);
        internal_counters.push_back(7601);
        internal_counters.push_back(7837);
        internal_counters.push_back(8073);
        internal_counters.push_back(8309);
        internal_counters.push_back(8545);
        internal_counters.push_back(8781);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12193);
        internal_counters.push_back(12271);
        internal_counters.push_back(12349);
        internal_counters.push_back(12427);
        internal_counters.push_back(12505);
        internal_counters.push_back(12583);
        internal_counters.push_back(12661);
        internal_counters.push_back(12739);
        internal_counters.push_back(12817);
        internal_counters.push_back(12895);
        internal_counters.push_back(12973);
        internal_counters.push_back(13051);
        internal_counters.push_back(13129);
        internal_counters.push_back(13207);
        internal_counters.push_back(13285);
        internal_counters.push_back(13363);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16373);
        internal_counters.push_back(16632);
        internal_counters.push_back(16891);
        internal_counters.push_back(17150);
        internal_counters.push_back(17409);
        internal_counters.push_back(17668);
        internal_counters.push_back(17927);
        internal_counters.push_back(18186);
        internal_counters.push_back(18445);
        internal_counters.push_back(18704);
        internal_counters.push_back(18963);
        internal_counters.push_back(19222);
        internal_counters.push_back(19481);
        internal_counters.push_back(19740);
        internal_counters.push_back(19999);
        internal_counters.push_back(20258);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24306);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6");
    }
}

