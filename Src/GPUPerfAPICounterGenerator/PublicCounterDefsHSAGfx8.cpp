//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for HSAGFX8
//==============================================================================

#include "PublicCounterDefsHSAGfx8.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicCountersHSAGfx8(GPA_PublicCounters& p)
{
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3431);

        p.DefinePublicCounter("Wavefronts", "General", "Total wavefronts.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "e8999836-489d-80a6-8e94-2c3ea191fd58");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3453);
        internalCounters.push_back(3431);

        p.DefinePublicCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3457);
        internalCounters.push_back(3431);

        p.DefinePublicCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3455);
        internalCounters.push_back(5954);
        internalCounters.push_back(6073);
        internalCounters.push_back(6192);
        internalCounters.push_back(6311);
        internalCounters.push_back(6430);
        internalCounters.push_back(6549);
        internalCounters.push_back(6668);
        internalCounters.push_back(6787);
        internalCounters.push_back(6906);
        internalCounters.push_back(7025);
        internalCounters.push_back(7144);
        internalCounters.push_back(7263);
        internalCounters.push_back(7382);
        internalCounters.push_back(7501);
        internalCounters.push_back(7620);
        internalCounters.push_back(7739);
        internalCounters.push_back(3431);

        p.DefinePublicCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/", "85970f8f-0b2c-6431-9e52-7999236e6e8a");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3458);
        internalCounters.push_back(3431);

        p.DefinePublicCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3454);
        internalCounters.push_back(5955);
        internalCounters.push_back(6074);
        internalCounters.push_back(6193);
        internalCounters.push_back(6312);
        internalCounters.push_back(6431);
        internalCounters.push_back(6550);
        internalCounters.push_back(6669);
        internalCounters.push_back(6788);
        internalCounters.push_back(6907);
        internalCounters.push_back(7026);
        internalCounters.push_back(7145);
        internalCounters.push_back(7264);
        internalCounters.push_back(7383);
        internalCounters.push_back(7502);
        internalCounters.push_back(7621);
        internalCounters.push_back(7740);
        internalCounters.push_back(3431);

        p.DefinePublicCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/", "d8154a17-224d-704e-73d2-bb5d150f3196");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3459);
        internalCounters.push_back(3460);
        internalCounters.push_back(3431);

        p.DefinePublicCounter("FlatVMemInsts", "General", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,-,2,/", "05e4a953-c59a-e722-872b-e4bc7526bcee");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3461);
        internalCounters.push_back(3459);
        internalCounters.push_back(3431);

        p.DefinePublicCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control). Excludes FLAT instructions that read from or write to LDS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,-,2,/", "be9bbead-f82a-a2c6-8333-1a5c4ce5ee98");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3460);
        internalCounters.push_back(3431);

        p.DefinePublicCounter("FlatLDSInsts", "LocalMemory", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "0f7d8f58-1750-a36f-d03e-85a2d9cd6e08");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3462);
        internalCounters.push_back(3431);

        p.DefinePublicCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3516);
        internalCounters.push_back(3508);

        p.DefinePublicCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,(64),*,/,(100),*,(100),min", "ffea5f90-624f-67dd-4ca6-74911f4c85d3");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3508);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3513);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7862);
        internalCounters.push_back(8054);
        internalCounters.push_back(8246);
        internalCounters.push_back(8438);
        internalCounters.push_back(8630);
        internalCounters.push_back(8822);
        internalCounters.push_back(9014);
        internalCounters.push_back(9206);
        internalCounters.push_back(9398);
        internalCounters.push_back(9590);
        internalCounters.push_back(9782);
        internalCounters.push_back(9974);
        internalCounters.push_back(10166);
        internalCounters.push_back(10358);
        internalCounters.push_back(10550);
        internalCounters.push_back(10742);

        p.DefinePublicCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7853);
        internalCounters.push_back(8045);
        internalCounters.push_back(8237);
        internalCounters.push_back(8429);
        internalCounters.push_back(8621);
        internalCounters.push_back(8813);
        internalCounters.push_back(9005);
        internalCounters.push_back(9197);
        internalCounters.push_back(9389);
        internalCounters.push_back(9581);
        internalCounters.push_back(9773);
        internalCounters.push_back(9965);
        internalCounters.push_back(10157);
        internalCounters.push_back(10349);
        internalCounters.push_back(10541);
        internalCounters.push_back(10733);

        p.DefinePublicCounter("WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,(1024),/", "e09d95da-2772-f7cb-51f5-4fad27bb998b");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7845);
        internalCounters.push_back(8037);
        internalCounters.push_back(8229);
        internalCounters.push_back(8421);
        internalCounters.push_back(8613);
        internalCounters.push_back(8805);
        internalCounters.push_back(8997);
        internalCounters.push_back(9189);
        internalCounters.push_back(9381);
        internalCounters.push_back(9573);
        internalCounters.push_back(9765);
        internalCounters.push_back(9957);
        internalCounters.push_back(10149);
        internalCounters.push_back(10341);
        internalCounters.push_back(10533);
        internalCounters.push_back(10725);
        internalCounters.push_back(7846);
        internalCounters.push_back(8038);
        internalCounters.push_back(8230);
        internalCounters.push_back(8422);
        internalCounters.push_back(8614);
        internalCounters.push_back(8806);
        internalCounters.push_back(8998);
        internalCounters.push_back(9190);
        internalCounters.push_back(9382);
        internalCounters.push_back(9574);
        internalCounters.push_back(9766);
        internalCounters.push_back(9958);
        internalCounters.push_back(10150);
        internalCounters.push_back(10342);
        internalCounters.push_back(10534);
        internalCounters.push_back(10726);

        p.DefinePublicCounter("CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "dfbeebab-f7c1-1211-e502-4aae361e2ad7");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5868);
        internalCounters.push_back(5987);
        internalCounters.push_back(6106);
        internalCounters.push_back(6225);
        internalCounters.push_back(6344);
        internalCounters.push_back(6463);
        internalCounters.push_back(6582);
        internalCounters.push_back(6701);
        internalCounters.push_back(6820);
        internalCounters.push_back(6939);
        internalCounters.push_back(7058);
        internalCounters.push_back(7177);
        internalCounters.push_back(7296);
        internalCounters.push_back(7415);
        internalCounters.push_back(7534);
        internalCounters.push_back(7653);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11782);
        internalCounters.push_back(11962);
        internalCounters.push_back(12142);
        internalCounters.push_back(12322);
        internalCounters.push_back(12502);
        internalCounters.push_back(12682);
        internalCounters.push_back(12862);
        internalCounters.push_back(13042);
        internalCounters.push_back(13222);
        internalCounters.push_back(13402);
        internalCounters.push_back(13582);
        internalCounters.push_back(13762);
        internalCounters.push_back(13942);
        internalCounters.push_back(14122);
        internalCounters.push_back(14302);
        internalCounters.push_back(14482);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7855);
        internalCounters.push_back(8047);
        internalCounters.push_back(8239);
        internalCounters.push_back(8431);
        internalCounters.push_back(8623);
        internalCounters.push_back(8815);
        internalCounters.push_back(9007);
        internalCounters.push_back(9199);
        internalCounters.push_back(9391);
        internalCounters.push_back(9583);
        internalCounters.push_back(9775);
        internalCounters.push_back(9967);
        internalCounters.push_back(10159);
        internalCounters.push_back(10351);
        internalCounters.push_back(10543);
        internalCounters.push_back(10735);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3524);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6");
    }
}

