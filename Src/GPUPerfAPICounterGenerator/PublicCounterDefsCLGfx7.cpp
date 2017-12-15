//==============================================================================
// Copyright (c) 2010-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  PublicCounterDefinitions for CLGFX7
//==============================================================================

#include "PublicCounterDefsCLGfx7.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicCountersCLGfx7(GPA_PublicCounters& p)
{
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2736);

        p.DefinePublicCounter("Wavefronts", "General", "Total wavefronts.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0", "e8999836-489d-80a6-8e94-2c3ea191fd58" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2758);
        internalCounters.push_back(2736);

        p.DefinePublicCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2762);
        internalCounters.push_back(2736);

        p.DefinePublicCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2760);
        internalCounters.push_back(2736);

        p.DefinePublicCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/", "d45b0277-03fa-9480-eada-4871ec89c504" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2763);
        internalCounters.push_back(2736);

        p.DefinePublicCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2759);
        internalCounters.push_back(2736);

        p.DefinePublicCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/", "d33f2e7c-3198-cf69-2432-d2a32f385d46" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2764);
        internalCounters.push_back(2765);
        internalCounters.push_back(2736);

        p.DefinePublicCounter("FlatVMemInsts", "General", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,-,2,/", "05e4a953-c59a-e722-872b-e4bc7526bcee" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2766);
        internalCounters.push_back(2764);
        internalCounters.push_back(2736);

        p.DefinePublicCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control).  Excludes FLAT instructions that read from or write to LDS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,-,2,/", "d38c615e-1ae5-cfc1-cd3b-c5bcbde4ff3c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2765);
        internalCounters.push_back(2736);

        p.DefinePublicCounter("FlatLDSInsts", "LocalMemory", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/", "0f7d8f58-1750-a36f-d03e-85a2d9cd6e08" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2767);
        internalCounters.push_back(2736);

        p.DefinePublicCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2821);
        internalCounters.push_back(2813);

        p.DefinePublicCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,(64),*,/,(100),*,(100),min", "ffea5f90-624f-67dd-4ca6-74911f4c85d3" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2813);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2818);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6103);
        internalCounters.push_back(6263);
        internalCounters.push_back(6423);
        internalCounters.push_back(6583);
        internalCounters.push_back(6743);
        internalCounters.push_back(6903);
        internalCounters.push_back(7063);
        internalCounters.push_back(7223);
        internalCounters.push_back(7383);
        internalCounters.push_back(7543);
        internalCounters.push_back(7703);
        internalCounters.push_back(7863);
        internalCounters.push_back(8023);
        internalCounters.push_back(8183);
        internalCounters.push_back(8343);
        internalCounters.push_back(8503);

        p.DefinePublicCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6097);
        internalCounters.push_back(6257);
        internalCounters.push_back(6417);
        internalCounters.push_back(6577);
        internalCounters.push_back(6737);
        internalCounters.push_back(6897);
        internalCounters.push_back(7057);
        internalCounters.push_back(7217);
        internalCounters.push_back(7377);
        internalCounters.push_back(7537);
        internalCounters.push_back(7697);
        internalCounters.push_back(7857);
        internalCounters.push_back(8017);
        internalCounters.push_back(8177);
        internalCounters.push_back(8337);
        internalCounters.push_back(8497);

        p.DefinePublicCounter("WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,(1024),/", "e09d95da-2772-f7cb-51f5-4fad27bb998b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6089);
        internalCounters.push_back(6249);
        internalCounters.push_back(6409);
        internalCounters.push_back(6569);
        internalCounters.push_back(6729);
        internalCounters.push_back(6889);
        internalCounters.push_back(7049);
        internalCounters.push_back(7209);
        internalCounters.push_back(7369);
        internalCounters.push_back(7529);
        internalCounters.push_back(7689);
        internalCounters.push_back(7849);
        internalCounters.push_back(8009);
        internalCounters.push_back(8169);
        internalCounters.push_back(8329);
        internalCounters.push_back(8489);
        internalCounters.push_back(6090);
        internalCounters.push_back(6250);
        internalCounters.push_back(6410);
        internalCounters.push_back(6570);
        internalCounters.push_back(6730);
        internalCounters.push_back(6890);
        internalCounters.push_back(7050);
        internalCounters.push_back(7210);
        internalCounters.push_back(7370);
        internalCounters.push_back(7530);
        internalCounters.push_back(7690);
        internalCounters.push_back(7850);
        internalCounters.push_back(8010);
        internalCounters.push_back(8170);
        internalCounters.push_back(8330);
        internalCounters.push_back(8490);

        p.DefinePublicCounter("CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "dfbeebab-f7c1-1211-e502-4aae361e2ad7" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4780);
        internalCounters.push_back(4891);
        internalCounters.push_back(5002);
        internalCounters.push_back(5113);
        internalCounters.push_back(5224);
        internalCounters.push_back(5335);
        internalCounters.push_back(5446);
        internalCounters.push_back(5557);
        internalCounters.push_back(5668);
        internalCounters.push_back(5779);
        internalCounters.push_back(5890);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,/,NUM_SHADER_ENGINES,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9181);
        internalCounters.push_back(9335);
        internalCounters.push_back(9489);
        internalCounters.push_back(9643);
        internalCounters.push_back(9797);
        internalCounters.push_back(9951);
        internalCounters.push_back(10105);
        internalCounters.push_back(10259);
        internalCounters.push_back(10413);
        internalCounters.push_back(10567);
        internalCounters.push_back(10721);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,/,NUM_SHADER_ENGINES,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6098);
        internalCounters.push_back(6258);
        internalCounters.push_back(6418);
        internalCounters.push_back(6578);
        internalCounters.push_back(6738);
        internalCounters.push_back(6898);
        internalCounters.push_back(7058);
        internalCounters.push_back(7218);
        internalCounters.push_back(7378);
        internalCounters.push_back(7538);
        internalCounters.push_back(7698);
        internalCounters.push_back(7858);
        internalCounters.push_back(8018);
        internalCounters.push_back(8178);
        internalCounters.push_back(8338);
        internalCounters.push_back(8498);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2829);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6" );
    }
}

