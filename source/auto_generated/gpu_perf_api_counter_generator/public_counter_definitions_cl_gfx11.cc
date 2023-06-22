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
        internal_counters.push_back(4872);

        c.DefineDerivedCounter("Wavefronts", "General", "Total wavefronts.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "e8999836-489d-80a6-8e94-2c3ea191fd58");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24068);
        internal_counters.push_back(4872);

        c.DefineDerivedCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24064);
        internal_counters.push_back(4872);

        c.DefineDerivedCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24072);
        internal_counters.push_back(4872);

        c.DefineDerivedCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "85970f8f-0b2c-6431-9e52-7999236e6e8a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24065);
        internal_counters.push_back(4872);

        c.DefineDerivedCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24073);
        internal_counters.push_back(4872);

        c.DefineDerivedCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "d8154a17-224d-704e-73d2-bb5d150f3196");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24063);
        internal_counters.push_back(4872);

        c.DefineDerivedCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "852ccd67-d2eb-d238-567a-0d1f7bf5f34f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24060);
        internal_counters.push_back(4872);

        c.DefineDerivedCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24086);
        internal_counters.push_back(24109);
        internal_counters.push_back(4873);

        c.DefineDerivedCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,(64),(32),2,ifnotzero,*,/,(100),*,(100),min", "435fc505-4d15-095e-79f1-80346bcd0a24");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24109);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24064);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16340);
        internal_counters.push_back(16599);
        internal_counters.push_back(16858);
        internal_counters.push_back(17117);
        internal_counters.push_back(17376);
        internal_counters.push_back(17635);
        internal_counters.push_back(17894);
        internal_counters.push_back(18153);
        internal_counters.push_back(18412);
        internal_counters.push_back(18671);
        internal_counters.push_back(18930);
        internal_counters.push_back(19189);
        internal_counters.push_back(19448);
        internal_counters.push_back(19707);
        internal_counters.push_back(19966);
        internal_counters.push_back(20225);
        internal_counters.push_back(16341);
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
        internal_counters.push_back(16342);
        internal_counters.push_back(16601);
        internal_counters.push_back(16860);
        internal_counters.push_back(17119);
        internal_counters.push_back(17378);
        internal_counters.push_back(17637);
        internal_counters.push_back(17896);
        internal_counters.push_back(18155);
        internal_counters.push_back(18414);
        internal_counters.push_back(18673);
        internal_counters.push_back(18932);
        internal_counters.push_back(19191);
        internal_counters.push_back(19450);
        internal_counters.push_back(19709);
        internal_counters.push_back(19968);
        internal_counters.push_back(20227);
        internal_counters.push_back(16343);
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

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeKilobytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,(96),*,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,(128),*,sum4,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16324);
        internal_counters.push_back(16583);
        internal_counters.push_back(16842);
        internal_counters.push_back(17101);
        internal_counters.push_back(17360);
        internal_counters.push_back(17619);
        internal_counters.push_back(17878);
        internal_counters.push_back(18137);
        internal_counters.push_back(18396);
        internal_counters.push_back(18655);
        internal_counters.push_back(18914);
        internal_counters.push_back(19173);
        internal_counters.push_back(19432);
        internal_counters.push_back(19691);
        internal_counters.push_back(19950);
        internal_counters.push_back(20209);
        internal_counters.push_back(16326);
        internal_counters.push_back(16585);
        internal_counters.push_back(16844);
        internal_counters.push_back(17103);
        internal_counters.push_back(17362);
        internal_counters.push_back(17621);
        internal_counters.push_back(17880);
        internal_counters.push_back(18139);
        internal_counters.push_back(18398);
        internal_counters.push_back(18657);
        internal_counters.push_back(18916);
        internal_counters.push_back(19175);
        internal_counters.push_back(19434);
        internal_counters.push_back(19693);
        internal_counters.push_back(19952);
        internal_counters.push_back(20211);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeKilobytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+,(1024),/", "e09d95da-2772-f7cb-51f5-4fad27bb998b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12167);
        internal_counters.push_back(12245);
        internal_counters.push_back(12323);
        internal_counters.push_back(12401);
        internal_counters.push_back(12479);
        internal_counters.push_back(12557);
        internal_counters.push_back(12635);
        internal_counters.push_back(12713);
        internal_counters.push_back(12791);
        internal_counters.push_back(12869);
        internal_counters.push_back(12947);
        internal_counters.push_back(13025);
        internal_counters.push_back(13103);
        internal_counters.push_back(13181);
        internal_counters.push_back(13259);
        internal_counters.push_back(13337);
        internal_counters.push_back(12175);
        internal_counters.push_back(12253);
        internal_counters.push_back(12331);
        internal_counters.push_back(12409);
        internal_counters.push_back(12487);
        internal_counters.push_back(12565);
        internal_counters.push_back(12643);
        internal_counters.push_back(12721);
        internal_counters.push_back(12799);
        internal_counters.push_back(12877);
        internal_counters.push_back(12955);
        internal_counters.push_back(13033);
        internal_counters.push_back(13111);
        internal_counters.push_back(13189);
        internal_counters.push_back(13267);
        internal_counters.push_back(13345);

        c.DefineDerivedCounter("L0CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L0 cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "be1e0578-82b8-ad7f-ba3f-3afce150937a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15735);
        internal_counters.push_back(15739);

        c.DefineDerivedCounter("L1CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Writes and atomics always miss this cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),1,0,/,-,(100),*,0,ifnotzero", "b10c589c-f7a5-b8f2-46c2-e0aed4a84105");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16244);
        internal_counters.push_back(16503);
        internal_counters.push_back(16762);
        internal_counters.push_back(17021);
        internal_counters.push_back(17280);
        internal_counters.push_back(17539);
        internal_counters.push_back(17798);
        internal_counters.push_back(18057);
        internal_counters.push_back(18316);
        internal_counters.push_back(18575);
        internal_counters.push_back(18834);
        internal_counters.push_back(19093);
        internal_counters.push_back(19352);
        internal_counters.push_back(19611);
        internal_counters.push_back(19870);
        internal_counters.push_back(20129);
        internal_counters.push_back(16284);
        internal_counters.push_back(16543);
        internal_counters.push_back(16802);
        internal_counters.push_back(17061);
        internal_counters.push_back(17320);
        internal_counters.push_back(17579);
        internal_counters.push_back(17838);
        internal_counters.push_back(18097);
        internal_counters.push_back(18356);
        internal_counters.push_back(18615);
        internal_counters.push_back(18874);
        internal_counters.push_back(19133);
        internal_counters.push_back(19392);
        internal_counters.push_back(19651);
        internal_counters.push_back(19910);
        internal_counters.push_back(20169);

        c.DefineDerivedCounter("L2CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L2 cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "7507935e-ed29-f169-ee27-9b0fa9b88f3c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5245);
        internal_counters.push_back(5481);
        internal_counters.push_back(5717);
        internal_counters.push_back(5953);
        internal_counters.push_back(6189);
        internal_counters.push_back(6425);
        internal_counters.push_back(6661);
        internal_counters.push_back(6897);
        internal_counters.push_back(7133);
        internal_counters.push_back(7369);
        internal_counters.push_back(7605);
        internal_counters.push_back(7841);
        internal_counters.push_back(8077);
        internal_counters.push_back(8313);
        internal_counters.push_back(8549);
        internal_counters.push_back(8785);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12197);
        internal_counters.push_back(12275);
        internal_counters.push_back(12353);
        internal_counters.push_back(12431);
        internal_counters.push_back(12509);
        internal_counters.push_back(12587);
        internal_counters.push_back(12665);
        internal_counters.push_back(12743);
        internal_counters.push_back(12821);
        internal_counters.push_back(12899);
        internal_counters.push_back(12977);
        internal_counters.push_back(13055);
        internal_counters.push_back(13133);
        internal_counters.push_back(13211);
        internal_counters.push_back(13289);
        internal_counters.push_back(13367);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16329);
        internal_counters.push_back(16588);
        internal_counters.push_back(16847);
        internal_counters.push_back(17106);
        internal_counters.push_back(17365);
        internal_counters.push_back(17624);
        internal_counters.push_back(17883);
        internal_counters.push_back(18142);
        internal_counters.push_back(18401);
        internal_counters.push_back(18660);
        internal_counters.push_back(18919);
        internal_counters.push_back(19178);
        internal_counters.push_back(19437);
        internal_counters.push_back(19696);
        internal_counters.push_back(19955);
        internal_counters.push_back(20214);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24262);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6");
    }
}

