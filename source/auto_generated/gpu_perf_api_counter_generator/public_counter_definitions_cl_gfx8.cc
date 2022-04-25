//==============================================================================
// Copyright (c) 2010-2022 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for CL GFX8.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_cl_gfx8.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersClGfx8(GpaDerivedCounters& c)
{
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3431);

        c.DefineDerivedCounter("Wavefronts", "General", "Total wavefronts.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "e8999836-489d-80a6-8e94-2c3ea191fd58");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3453);
        internal_counters.push_back(3431);

        c.DefineDerivedCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3457);
        internal_counters.push_back(3431);

        c.DefineDerivedCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3455);
        internal_counters.push_back(5954);
        internal_counters.push_back(6073);
        internal_counters.push_back(6192);
        internal_counters.push_back(6311);
        internal_counters.push_back(6430);
        internal_counters.push_back(6549);
        internal_counters.push_back(6668);
        internal_counters.push_back(6787);
        internal_counters.push_back(6906);
        internal_counters.push_back(7025);
        internal_counters.push_back(7144);
        internal_counters.push_back(7263);
        internal_counters.push_back(7382);
        internal_counters.push_back(7501);
        internal_counters.push_back(7620);
        internal_counters.push_back(7739);
        internal_counters.push_back(3431);

        c.DefineDerivedCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/", "85970f8f-0b2c-6431-9e52-7999236e6e8a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3458);
        internal_counters.push_back(3431);

        c.DefineDerivedCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3454);
        internal_counters.push_back(5955);
        internal_counters.push_back(6074);
        internal_counters.push_back(6193);
        internal_counters.push_back(6312);
        internal_counters.push_back(6431);
        internal_counters.push_back(6550);
        internal_counters.push_back(6669);
        internal_counters.push_back(6788);
        internal_counters.push_back(6907);
        internal_counters.push_back(7026);
        internal_counters.push_back(7145);
        internal_counters.push_back(7264);
        internal_counters.push_back(7383);
        internal_counters.push_back(7502);
        internal_counters.push_back(7621);
        internal_counters.push_back(7740);
        internal_counters.push_back(3431);

        c.DefineDerivedCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/", "d8154a17-224d-704e-73d2-bb5d150f3196");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3459);
        internal_counters.push_back(3460);
        internal_counters.push_back(3431);

        c.DefineDerivedCounter("FlatVMemInsts", "General", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,-,2,/", "05e4a953-c59a-e722-872b-e4bc7526bcee");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3461);
        internal_counters.push_back(3459);
        internal_counters.push_back(3431);

        c.DefineDerivedCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control). Excludes FLAT instructions that read from or write to LDS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,-,2,/", "be9bbead-f82a-a2c6-8333-1a5c4ce5ee98");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3460);
        internal_counters.push_back(3431);

        c.DefineDerivedCounter("FlatLDSInsts", "LocalMemory", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "0f7d8f58-1750-a36f-d03e-85a2d9cd6e08");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3462);
        internal_counters.push_back(3431);

        c.DefineDerivedCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3516);
        internal_counters.push_back(3508);

        c.DefineDerivedCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,(64),*,/,(100),*,(100),min", "ffea5f90-624f-67dd-4ca6-74911f4c85d3");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3508);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3513);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7862);
        internal_counters.push_back(8054);
        internal_counters.push_back(8246);
        internal_counters.push_back(8438);
        internal_counters.push_back(8630);
        internal_counters.push_back(8822);
        internal_counters.push_back(9014);
        internal_counters.push_back(9206);
        internal_counters.push_back(9398);
        internal_counters.push_back(9590);
        internal_counters.push_back(9782);
        internal_counters.push_back(9974);
        internal_counters.push_back(10166);
        internal_counters.push_back(10358);
        internal_counters.push_back(10550);
        internal_counters.push_back(10742);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeKilobytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7853);
        internal_counters.push_back(8045);
        internal_counters.push_back(8237);
        internal_counters.push_back(8429);
        internal_counters.push_back(8621);
        internal_counters.push_back(8813);
        internal_counters.push_back(9005);
        internal_counters.push_back(9197);
        internal_counters.push_back(9389);
        internal_counters.push_back(9581);
        internal_counters.push_back(9773);
        internal_counters.push_back(9965);
        internal_counters.push_back(10157);
        internal_counters.push_back(10349);
        internal_counters.push_back(10541);
        internal_counters.push_back(10733);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeKilobytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,(1024),/", "e09d95da-2772-f7cb-51f5-4fad27bb998b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7845);
        internal_counters.push_back(8037);
        internal_counters.push_back(8229);
        internal_counters.push_back(8421);
        internal_counters.push_back(8613);
        internal_counters.push_back(8805);
        internal_counters.push_back(8997);
        internal_counters.push_back(9189);
        internal_counters.push_back(9381);
        internal_counters.push_back(9573);
        internal_counters.push_back(9765);
        internal_counters.push_back(9957);
        internal_counters.push_back(10149);
        internal_counters.push_back(10341);
        internal_counters.push_back(10533);
        internal_counters.push_back(10725);
        internal_counters.push_back(7846);
        internal_counters.push_back(8038);
        internal_counters.push_back(8230);
        internal_counters.push_back(8422);
        internal_counters.push_back(8614);
        internal_counters.push_back(8806);
        internal_counters.push_back(8998);
        internal_counters.push_back(9190);
        internal_counters.push_back(9382);
        internal_counters.push_back(9574);
        internal_counters.push_back(9766);
        internal_counters.push_back(9958);
        internal_counters.push_back(10150);
        internal_counters.push_back(10342);
        internal_counters.push_back(10534);
        internal_counters.push_back(10726);

        c.DefineDerivedCounter("CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "dfbeebab-f7c1-1211-e502-4aae361e2ad7");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5868);
        internal_counters.push_back(5987);
        internal_counters.push_back(6106);
        internal_counters.push_back(6225);
        internal_counters.push_back(6344);
        internal_counters.push_back(6463);
        internal_counters.push_back(6582);
        internal_counters.push_back(6701);
        internal_counters.push_back(6820);
        internal_counters.push_back(6939);
        internal_counters.push_back(7058);
        internal_counters.push_back(7177);
        internal_counters.push_back(7296);
        internal_counters.push_back(7415);
        internal_counters.push_back(7534);
        internal_counters.push_back(7653);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(11782);
        internal_counters.push_back(11962);
        internal_counters.push_back(12142);
        internal_counters.push_back(12322);
        internal_counters.push_back(12502);
        internal_counters.push_back(12682);
        internal_counters.push_back(12862);
        internal_counters.push_back(13042);
        internal_counters.push_back(13222);
        internal_counters.push_back(13402);
        internal_counters.push_back(13582);
        internal_counters.push_back(13762);
        internal_counters.push_back(13942);
        internal_counters.push_back(14122);
        internal_counters.push_back(14302);
        internal_counters.push_back(14482);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7855);
        internal_counters.push_back(8047);
        internal_counters.push_back(8239);
        internal_counters.push_back(8431);
        internal_counters.push_back(8623);
        internal_counters.push_back(8815);
        internal_counters.push_back(9007);
        internal_counters.push_back(9199);
        internal_counters.push_back(9391);
        internal_counters.push_back(9583);
        internal_counters.push_back(9775);
        internal_counters.push_back(9967);
        internal_counters.push_back(10159);
        internal_counters.push_back(10351);
        internal_counters.push_back(10543);
        internal_counters.push_back(10735);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3524);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6");
    }
}

