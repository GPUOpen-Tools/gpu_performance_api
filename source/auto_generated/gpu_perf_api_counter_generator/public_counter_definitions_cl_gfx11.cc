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
        internal_counters.push_back(24076);
        internal_counters.push_back(4872);

        c.DefineDerivedCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24072);
        internal_counters.push_back(4872);

        c.DefineDerivedCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24080);
        internal_counters.push_back(4872);

        c.DefineDerivedCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "85970f8f-0b2c-6431-9e52-7999236e6e8a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24073);
        internal_counters.push_back(4872);

        c.DefineDerivedCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24081);
        internal_counters.push_back(4872);

        c.DefineDerivedCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "d8154a17-224d-704e-73d2-bb5d150f3196");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24071);
        internal_counters.push_back(4872);

        c.DefineDerivedCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "852ccd67-d2eb-d238-567a-0d1f7bf5f34f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24068);
        internal_counters.push_back(4872);

        c.DefineDerivedCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24094);
        internal_counters.push_back(24117);
        internal_counters.push_back(4873);

        c.DefineDerivedCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,(64),(32),2,ifnotzero,*,/,(100),*,(100),min", "435fc505-4d15-095e-79f1-80346bcd0a24");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24117);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24072);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16348);
        internal_counters.push_back(16607);
        internal_counters.push_back(16866);
        internal_counters.push_back(17125);
        internal_counters.push_back(17384);
        internal_counters.push_back(17643);
        internal_counters.push_back(17902);
        internal_counters.push_back(18161);
        internal_counters.push_back(18420);
        internal_counters.push_back(18679);
        internal_counters.push_back(18938);
        internal_counters.push_back(19197);
        internal_counters.push_back(19456);
        internal_counters.push_back(19715);
        internal_counters.push_back(19974);
        internal_counters.push_back(20233);
        internal_counters.push_back(16349);
        internal_counters.push_back(16608);
        internal_counters.push_back(16867);
        internal_counters.push_back(17126);
        internal_counters.push_back(17385);
        internal_counters.push_back(17644);
        internal_counters.push_back(17903);
        internal_counters.push_back(18162);
        internal_counters.push_back(18421);
        internal_counters.push_back(18680);
        internal_counters.push_back(18939);
        internal_counters.push_back(19198);
        internal_counters.push_back(19457);
        internal_counters.push_back(19716);
        internal_counters.push_back(19975);
        internal_counters.push_back(20234);
        internal_counters.push_back(16350);
        internal_counters.push_back(16609);
        internal_counters.push_back(16868);
        internal_counters.push_back(17127);
        internal_counters.push_back(17386);
        internal_counters.push_back(17645);
        internal_counters.push_back(17904);
        internal_counters.push_back(18163);
        internal_counters.push_back(18422);
        internal_counters.push_back(18681);
        internal_counters.push_back(18940);
        internal_counters.push_back(19199);
        internal_counters.push_back(19458);
        internal_counters.push_back(19717);
        internal_counters.push_back(19976);
        internal_counters.push_back(20235);
        internal_counters.push_back(16351);
        internal_counters.push_back(16610);
        internal_counters.push_back(16869);
        internal_counters.push_back(17128);
        internal_counters.push_back(17387);
        internal_counters.push_back(17646);
        internal_counters.push_back(17905);
        internal_counters.push_back(18164);
        internal_counters.push_back(18423);
        internal_counters.push_back(18682);
        internal_counters.push_back(18941);
        internal_counters.push_back(19200);
        internal_counters.push_back(19459);
        internal_counters.push_back(19718);
        internal_counters.push_back(19977);
        internal_counters.push_back(20236);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeKilobytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,(96),*,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,(128),*,sum4,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16332);
        internal_counters.push_back(16591);
        internal_counters.push_back(16850);
        internal_counters.push_back(17109);
        internal_counters.push_back(17368);
        internal_counters.push_back(17627);
        internal_counters.push_back(17886);
        internal_counters.push_back(18145);
        internal_counters.push_back(18404);
        internal_counters.push_back(18663);
        internal_counters.push_back(18922);
        internal_counters.push_back(19181);
        internal_counters.push_back(19440);
        internal_counters.push_back(19699);
        internal_counters.push_back(19958);
        internal_counters.push_back(20217);
        internal_counters.push_back(16334);
        internal_counters.push_back(16593);
        internal_counters.push_back(16852);
        internal_counters.push_back(17111);
        internal_counters.push_back(17370);
        internal_counters.push_back(17629);
        internal_counters.push_back(17888);
        internal_counters.push_back(18147);
        internal_counters.push_back(18406);
        internal_counters.push_back(18665);
        internal_counters.push_back(18924);
        internal_counters.push_back(19183);
        internal_counters.push_back(19442);
        internal_counters.push_back(19701);
        internal_counters.push_back(19960);
        internal_counters.push_back(20219);

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
        internal_counters.push_back(15743);
        internal_counters.push_back(15747);

        c.DefineDerivedCounter("L1CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Writes and atomics always miss this cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),1,0,/,-,(100),*,0,ifnotzero", "b10c589c-f7a5-b8f2-46c2-e0aed4a84105");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16252);
        internal_counters.push_back(16511);
        internal_counters.push_back(16770);
        internal_counters.push_back(17029);
        internal_counters.push_back(17288);
        internal_counters.push_back(17547);
        internal_counters.push_back(17806);
        internal_counters.push_back(18065);
        internal_counters.push_back(18324);
        internal_counters.push_back(18583);
        internal_counters.push_back(18842);
        internal_counters.push_back(19101);
        internal_counters.push_back(19360);
        internal_counters.push_back(19619);
        internal_counters.push_back(19878);
        internal_counters.push_back(20137);
        internal_counters.push_back(16292);
        internal_counters.push_back(16551);
        internal_counters.push_back(16810);
        internal_counters.push_back(17069);
        internal_counters.push_back(17328);
        internal_counters.push_back(17587);
        internal_counters.push_back(17846);
        internal_counters.push_back(18105);
        internal_counters.push_back(18364);
        internal_counters.push_back(18623);
        internal_counters.push_back(18882);
        internal_counters.push_back(19141);
        internal_counters.push_back(19400);
        internal_counters.push_back(19659);
        internal_counters.push_back(19918);
        internal_counters.push_back(20177);

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
        internal_counters.push_back(16337);
        internal_counters.push_back(16596);
        internal_counters.push_back(16855);
        internal_counters.push_back(17114);
        internal_counters.push_back(17373);
        internal_counters.push_back(17632);
        internal_counters.push_back(17891);
        internal_counters.push_back(18150);
        internal_counters.push_back(18409);
        internal_counters.push_back(18668);
        internal_counters.push_back(18927);
        internal_counters.push_back(19186);
        internal_counters.push_back(19445);
        internal_counters.push_back(19704);
        internal_counters.push_back(19963);
        internal_counters.push_back(20222);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24270);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6");
    }
}

