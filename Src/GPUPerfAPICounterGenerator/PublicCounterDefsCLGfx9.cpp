//==============================================================================
// Copyright (c) 2010-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  PublicCounterDefinitions for CLGFX9
//==============================================================================

#include "PublicCounterDefsCLGfx9.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicCountersCLGfx9(GPA_PublicCounters& p)
{
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4133);

        p.DefinePublicCounter("Wavefronts", "#General#Total wavefronts.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4155);
        internalCounters.push_back(4133);

        p.DefinePublicCounter("VALUInsts", "#General#The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4159);
        internalCounters.push_back(4133);

        p.DefinePublicCounter("SALUInsts", "#General#The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4157);
        internalCounters.push_back(4812);
        internalCounters.push_back(4931);
        internalCounters.push_back(5050);
        internalCounters.push_back(5169);
        internalCounters.push_back(5288);
        internalCounters.push_back(5407);
        internalCounters.push_back(5526);
        internalCounters.push_back(5645);
        internalCounters.push_back(5764);
        internalCounters.push_back(5883);
        internalCounters.push_back(6002);
        internalCounters.push_back(6121);
        internalCounters.push_back(6240);
        internalCounters.push_back(6359);
        internalCounters.push_back(6478);
        internalCounters.push_back(6597);
        internalCounters.push_back(4133);

        p.DefinePublicCounter("VFetchInsts", "#General#The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4160);
        internalCounters.push_back(4133);

        p.DefinePublicCounter("SFetchInsts", "#General#The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4156);
        internalCounters.push_back(4813);
        internalCounters.push_back(4932);
        internalCounters.push_back(5051);
        internalCounters.push_back(5170);
        internalCounters.push_back(5289);
        internalCounters.push_back(5408);
        internalCounters.push_back(5527);
        internalCounters.push_back(5646);
        internalCounters.push_back(5765);
        internalCounters.push_back(5884);
        internalCounters.push_back(6003);
        internalCounters.push_back(6122);
        internalCounters.push_back(6241);
        internalCounters.push_back(6360);
        internalCounters.push_back(6479);
        internalCounters.push_back(6598);
        internalCounters.push_back(4133);

        p.DefinePublicCounter("VWriteInsts", "#General#The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4163);
        internalCounters.push_back(4162);
        internalCounters.push_back(4133);

        p.DefinePublicCounter("FlatVMemInsts", "#General#The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,-,2,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4163);
        internalCounters.push_back(4161);
        internalCounters.push_back(4133);

        p.DefinePublicCounter("LDSInsts", "#LocalMemory#The average number of LDS read or LDS write instructions executed per work item (affected by flow control).  Excludes FLAT instructions that read from or write to LDS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,-,2,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4162);
        internalCounters.push_back(4133);

        p.DefinePublicCounter("FlatLDSInsts", "#LocalMemory#The average number of FLAT instructions that read or write to LDS executed per work item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4164);
        internalCounters.push_back(4133);

        p.DefinePublicCounter("GDSInsts", "#General#The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4213);
        internalCounters.push_back(3098);

        p.DefinePublicCounter("SALUBusy", "#General#The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6705);
        internalCounters.push_back(6961);
        internalCounters.push_back(7217);
        internalCounters.push_back(7473);
        internalCounters.push_back(7729);
        internalCounters.push_back(7985);
        internalCounters.push_back(8241);
        internalCounters.push_back(8497);
        internalCounters.push_back(8753);
        internalCounters.push_back(9009);
        internalCounters.push_back(9265);
        internalCounters.push_back(9521);
        internalCounters.push_back(9777);
        internalCounters.push_back(10033);
        internalCounters.push_back(10289);
        internalCounters.push_back(10545);
        internalCounters.push_back(6707);
        internalCounters.push_back(6963);
        internalCounters.push_back(7219);
        internalCounters.push_back(7475);
        internalCounters.push_back(7731);
        internalCounters.push_back(7987);
        internalCounters.push_back(8243);
        internalCounters.push_back(8499);
        internalCounters.push_back(8755);
        internalCounters.push_back(9011);
        internalCounters.push_back(9267);
        internalCounters.push_back(9523);
        internalCounters.push_back(9779);
        internalCounters.push_back(10035);
        internalCounters.push_back(10291);
        internalCounters.push_back(10547);

        p.DefinePublicCounter("CacheHit", "#GlobalMemory#The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4726);
        internalCounters.push_back(4845);
        internalCounters.push_back(4964);
        internalCounters.push_back(5083);
        internalCounters.push_back(5202);
        internalCounters.push_back(5321);
        internalCounters.push_back(5440);
        internalCounters.push_back(5559);
        internalCounters.push_back(5678);
        internalCounters.push_back(5797);
        internalCounters.push_back(5916);
        internalCounters.push_back(6035);
        internalCounters.push_back(6154);
        internalCounters.push_back(6273);
        internalCounters.push_back(6392);
        internalCounters.push_back(6511);
        internalCounters.push_back(3098);

        p.DefinePublicCounter("MemUnitBusy", "#GlobalMemory#The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11699);
        internalCounters.push_back(11784);
        internalCounters.push_back(11869);
        internalCounters.push_back(11954);
        internalCounters.push_back(12039);
        internalCounters.push_back(12124);
        internalCounters.push_back(12209);
        internalCounters.push_back(12294);
        internalCounters.push_back(12379);
        internalCounters.push_back(12464);
        internalCounters.push_back(12549);
        internalCounters.push_back(12634);
        internalCounters.push_back(12719);
        internalCounters.push_back(12804);
        internalCounters.push_back(12889);
        internalCounters.push_back(12974);
        internalCounters.push_back(3098);

        p.DefinePublicCounter("MemUnitStalled", "#GlobalMemory#The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4222);
        internalCounters.push_back(3098);

        p.DefinePublicCounter("LDSBankConflict", "#LocalMemory#The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*");
    }
}

