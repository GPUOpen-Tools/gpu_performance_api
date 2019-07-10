//==============================================================================
// Copyright (c) 2010-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for HSAGFX8
//==============================================================================

#include "GPACounter.h"
#include "PublicCounterDefsHSAGfx8.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersHSAGfx8(GPA_DerivedCounters& c)
{
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(414);

        c.DefineDerivedCounter("Wavefronts", "General", "Total wavefronts.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "e8999836-489d-80a6-8e94-2c3ea191fd58");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(436);
        internalCounters.push_back(414);

        c.DefineDerivedCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(440);
        internalCounters.push_back(414);

        c.DefineDerivedCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(438);
        internalCounters.push_back(1170);
        internalCounters.push_back(1289);
        internalCounters.push_back(1408);
        internalCounters.push_back(1527);
        internalCounters.push_back(1646);
        internalCounters.push_back(1765);
        internalCounters.push_back(1884);
        internalCounters.push_back(2003);
        internalCounters.push_back(2122);
        internalCounters.push_back(2241);
        internalCounters.push_back(2360);
        internalCounters.push_back(2479);
        internalCounters.push_back(2598);
        internalCounters.push_back(2717);
        internalCounters.push_back(2836);
        internalCounters.push_back(2955);
        internalCounters.push_back(414);

        c.DefineDerivedCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/", "85970f8f-0b2c-6431-9e52-7999236e6e8a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(441);
        internalCounters.push_back(414);

        c.DefineDerivedCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(437);
        internalCounters.push_back(1171);
        internalCounters.push_back(1290);
        internalCounters.push_back(1409);
        internalCounters.push_back(1528);
        internalCounters.push_back(1647);
        internalCounters.push_back(1766);
        internalCounters.push_back(1885);
        internalCounters.push_back(2004);
        internalCounters.push_back(2123);
        internalCounters.push_back(2242);
        internalCounters.push_back(2361);
        internalCounters.push_back(2480);
        internalCounters.push_back(2599);
        internalCounters.push_back(2718);
        internalCounters.push_back(2837);
        internalCounters.push_back(2956);
        internalCounters.push_back(414);

        c.DefineDerivedCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/", "d8154a17-224d-704e-73d2-bb5d150f3196");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(442);
        internalCounters.push_back(443);
        internalCounters.push_back(414);

        c.DefineDerivedCounter("FlatVMemInsts", "General", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,-,2,/", "05e4a953-c59a-e722-872b-e4bc7526bcee");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(444);
        internalCounters.push_back(442);
        internalCounters.push_back(414);

        c.DefineDerivedCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control). Excludes FLAT instructions that read from or write to LDS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,-,2,/", "be9bbead-f82a-a2c6-8333-1a5c4ce5ee98");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(443);
        internalCounters.push_back(414);

        c.DefineDerivedCounter("FlatLDSInsts", "LocalMemory", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "0f7d8f58-1750-a36f-d03e-85a2d9cd6e08");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(445);
        internalCounters.push_back(414);

        c.DefineDerivedCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(499);
        internalCounters.push_back(491);

        c.DefineDerivedCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,(64),*,/,(100),*,(100),min", "ffea5f90-624f-67dd-4ca6-74911f4c85d3");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(491);
        internalCounters.push_back(166);

        c.DefineDerivedCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(496);
        internalCounters.push_back(166);

        c.DefineDerivedCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_CUS,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3078);
        internalCounters.push_back(3270);
        internalCounters.push_back(3462);
        internalCounters.push_back(3654);
        internalCounters.push_back(3846);
        internalCounters.push_back(4038);
        internalCounters.push_back(4230);
        internalCounters.push_back(4422);
        internalCounters.push_back(4614);
        internalCounters.push_back(4806);
        internalCounters.push_back(4998);
        internalCounters.push_back(5190);
        internalCounters.push_back(5382);
        internalCounters.push_back(5574);
        internalCounters.push_back(5766);
        internalCounters.push_back(5958);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3069);
        internalCounters.push_back(3261);
        internalCounters.push_back(3453);
        internalCounters.push_back(3645);
        internalCounters.push_back(3837);
        internalCounters.push_back(4029);
        internalCounters.push_back(4221);
        internalCounters.push_back(4413);
        internalCounters.push_back(4605);
        internalCounters.push_back(4797);
        internalCounters.push_back(4989);
        internalCounters.push_back(5181);
        internalCounters.push_back(5373);
        internalCounters.push_back(5565);
        internalCounters.push_back(5757);
        internalCounters.push_back(5949);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,(1024),/", "e09d95da-2772-f7cb-51f5-4fad27bb998b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3061);
        internalCounters.push_back(3253);
        internalCounters.push_back(3445);
        internalCounters.push_back(3637);
        internalCounters.push_back(3829);
        internalCounters.push_back(4021);
        internalCounters.push_back(4213);
        internalCounters.push_back(4405);
        internalCounters.push_back(4597);
        internalCounters.push_back(4789);
        internalCounters.push_back(4981);
        internalCounters.push_back(5173);
        internalCounters.push_back(5365);
        internalCounters.push_back(5557);
        internalCounters.push_back(5749);
        internalCounters.push_back(5941);
        internalCounters.push_back(3062);
        internalCounters.push_back(3254);
        internalCounters.push_back(3446);
        internalCounters.push_back(3638);
        internalCounters.push_back(3830);
        internalCounters.push_back(4022);
        internalCounters.push_back(4214);
        internalCounters.push_back(4406);
        internalCounters.push_back(4598);
        internalCounters.push_back(4790);
        internalCounters.push_back(4982);
        internalCounters.push_back(5174);
        internalCounters.push_back(5366);
        internalCounters.push_back(5558);
        internalCounters.push_back(5750);
        internalCounters.push_back(5942);

        c.DefineDerivedCounter("CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "dfbeebab-f7c1-1211-e502-4aae361e2ad7");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1084);
        internalCounters.push_back(1203);
        internalCounters.push_back(1322);
        internalCounters.push_back(1441);
        internalCounters.push_back(1560);
        internalCounters.push_back(1679);
        internalCounters.push_back(1798);
        internalCounters.push_back(1917);
        internalCounters.push_back(2036);
        internalCounters.push_back(2155);
        internalCounters.push_back(2274);
        internalCounters.push_back(2393);
        internalCounters.push_back(2512);
        internalCounters.push_back(2631);
        internalCounters.push_back(2750);
        internalCounters.push_back(2869);
        internalCounters.push_back(166);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(6118);
        internalCounters.push_back(6298);
        internalCounters.push_back(6478);
        internalCounters.push_back(6658);
        internalCounters.push_back(6838);
        internalCounters.push_back(7018);
        internalCounters.push_back(7198);
        internalCounters.push_back(7378);
        internalCounters.push_back(7558);
        internalCounters.push_back(7738);
        internalCounters.push_back(7918);
        internalCounters.push_back(8098);
        internalCounters.push_back(8278);
        internalCounters.push_back(8458);
        internalCounters.push_back(8638);
        internalCounters.push_back(8818);
        internalCounters.push_back(166);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3071);
        internalCounters.push_back(3263);
        internalCounters.push_back(3455);
        internalCounters.push_back(3647);
        internalCounters.push_back(3839);
        internalCounters.push_back(4031);
        internalCounters.push_back(4223);
        internalCounters.push_back(4415);
        internalCounters.push_back(4607);
        internalCounters.push_back(4799);
        internalCounters.push_back(4991);
        internalCounters.push_back(5183);
        internalCounters.push_back(5375);
        internalCounters.push_back(5567);
        internalCounters.push_back(5759);
        internalCounters.push_back(5951);
        internalCounters.push_back(166);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(507);
        internalCounters.push_back(166);

        c.DefineDerivedCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6");
    }
}

