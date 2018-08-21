//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for HSAGFX9
//==============================================================================

#include "PublicCounterDefsHSAGfx9.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefineDerivedCountersHSAGfx9(GPA_DerivedCounters& c)
{
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("Wavefronts", "General", "Total wavefronts.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "e8999836-489d-80a6-8e94-2c3ea191fd58");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4215);
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4219);
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4217);
        internalCounters.push_back(6742);
        internalCounters.push_back(6861);
        internalCounters.push_back(6980);
        internalCounters.push_back(7099);
        internalCounters.push_back(7218);
        internalCounters.push_back(7337);
        internalCounters.push_back(7456);
        internalCounters.push_back(7575);
        internalCounters.push_back(7694);
        internalCounters.push_back(7813);
        internalCounters.push_back(7932);
        internalCounters.push_back(8051);
        internalCounters.push_back(8170);
        internalCounters.push_back(8289);
        internalCounters.push_back(8408);
        internalCounters.push_back(8527);
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/", "85970f8f-0b2c-6431-9e52-7999236e6e8a");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4220);
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4216);
        internalCounters.push_back(6743);
        internalCounters.push_back(6862);
        internalCounters.push_back(6981);
        internalCounters.push_back(7100);
        internalCounters.push_back(7219);
        internalCounters.push_back(7338);
        internalCounters.push_back(7457);
        internalCounters.push_back(7576);
        internalCounters.push_back(7695);
        internalCounters.push_back(7814);
        internalCounters.push_back(7933);
        internalCounters.push_back(8052);
        internalCounters.push_back(8171);
        internalCounters.push_back(8290);
        internalCounters.push_back(8409);
        internalCounters.push_back(8528);
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/", "d8154a17-224d-704e-73d2-bb5d150f3196");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4221);
        internalCounters.push_back(4222);
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("FlatVMemInsts", "General", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,-,2,/", "05e4a953-c59a-e722-872b-e4bc7526bcee");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4223);
        internalCounters.push_back(4222);
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control). Excludes FLAT instructions that read from or write to LDS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,-,2,/", "be9bbead-f82a-a2c6-8333-1a5c4ce5ee98");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4222);
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("FlatLDSInsts", "LocalMemory", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "0f7d8f58-1750-a36f-d03e-85a2d9cd6e08");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4224);
        internalCounters.push_back(4193);

        c.DefineDerivedCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4274);
        internalCounters.push_back(4260);

        c.DefineDerivedCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,(64),*,/,(100),*,(100),min", "ffea5f90-624f-67dd-4ca6-74911f4c85d3");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4260);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4273);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8656);
        internalCounters.push_back(8912);
        internalCounters.push_back(9168);
        internalCounters.push_back(9424);
        internalCounters.push_back(9680);
        internalCounters.push_back(9936);
        internalCounters.push_back(10192);
        internalCounters.push_back(10448);
        internalCounters.push_back(10704);
        internalCounters.push_back(10960);
        internalCounters.push_back(11216);
        internalCounters.push_back(11472);
        internalCounters.push_back(11728);
        internalCounters.push_back(11984);
        internalCounters.push_back(12240);
        internalCounters.push_back(12496);
        internalCounters.push_back(8657);
        internalCounters.push_back(8913);
        internalCounters.push_back(9169);
        internalCounters.push_back(9425);
        internalCounters.push_back(9681);
        internalCounters.push_back(9937);
        internalCounters.push_back(10193);
        internalCounters.push_back(10449);
        internalCounters.push_back(10705);
        internalCounters.push_back(10961);
        internalCounters.push_back(11217);
        internalCounters.push_back(11473);
        internalCounters.push_back(11729);
        internalCounters.push_back(11985);
        internalCounters.push_back(12241);
        internalCounters.push_back(12497);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(64),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8644);
        internalCounters.push_back(8900);
        internalCounters.push_back(9156);
        internalCounters.push_back(9412);
        internalCounters.push_back(9668);
        internalCounters.push_back(9924);
        internalCounters.push_back(10180);
        internalCounters.push_back(10436);
        internalCounters.push_back(10692);
        internalCounters.push_back(10948);
        internalCounters.push_back(11204);
        internalCounters.push_back(11460);
        internalCounters.push_back(11716);
        internalCounters.push_back(11972);
        internalCounters.push_back(12228);
        internalCounters.push_back(12484);
        internalCounters.push_back(8645);
        internalCounters.push_back(8901);
        internalCounters.push_back(9157);
        internalCounters.push_back(9413);
        internalCounters.push_back(9669);
        internalCounters.push_back(9925);
        internalCounters.push_back(10181);
        internalCounters.push_back(10437);
        internalCounters.push_back(10693);
        internalCounters.push_back(10949);
        internalCounters.push_back(11205);
        internalCounters.push_back(11461);
        internalCounters.push_back(11717);
        internalCounters.push_back(11973);
        internalCounters.push_back(12229);
        internalCounters.push_back(12485);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+,(1024),/", "e09d95da-2772-f7cb-51f5-4fad27bb998b");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8635);
        internalCounters.push_back(8891);
        internalCounters.push_back(9147);
        internalCounters.push_back(9403);
        internalCounters.push_back(9659);
        internalCounters.push_back(9915);
        internalCounters.push_back(10171);
        internalCounters.push_back(10427);
        internalCounters.push_back(10683);
        internalCounters.push_back(10939);
        internalCounters.push_back(11195);
        internalCounters.push_back(11451);
        internalCounters.push_back(11707);
        internalCounters.push_back(11963);
        internalCounters.push_back(12219);
        internalCounters.push_back(12475);
        internalCounters.push_back(8637);
        internalCounters.push_back(8893);
        internalCounters.push_back(9149);
        internalCounters.push_back(9405);
        internalCounters.push_back(9661);
        internalCounters.push_back(9917);
        internalCounters.push_back(10173);
        internalCounters.push_back(10429);
        internalCounters.push_back(10685);
        internalCounters.push_back(10941);
        internalCounters.push_back(11197);
        internalCounters.push_back(11453);
        internalCounters.push_back(11709);
        internalCounters.push_back(11965);
        internalCounters.push_back(12221);
        internalCounters.push_back(12477);

        c.DefineDerivedCounter("L2CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L2 cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "7507935e-ed29-f169-ee27-9b0fa9b88f3c");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6656);
        internalCounters.push_back(6775);
        internalCounters.push_back(6894);
        internalCounters.push_back(7013);
        internalCounters.push_back(7132);
        internalCounters.push_back(7251);
        internalCounters.push_back(7370);
        internalCounters.push_back(7489);
        internalCounters.push_back(7608);
        internalCounters.push_back(7727);
        internalCounters.push_back(7846);
        internalCounters.push_back(7965);
        internalCounters.push_back(8084);
        internalCounters.push_back(8203);
        internalCounters.push_back(8322);
        internalCounters.push_back(8441);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13629);
        internalCounters.push_back(13714);
        internalCounters.push_back(13799);
        internalCounters.push_back(13884);
        internalCounters.push_back(13969);
        internalCounters.push_back(14054);
        internalCounters.push_back(14139);
        internalCounters.push_back(14224);
        internalCounters.push_back(14309);
        internalCounters.push_back(14394);
        internalCounters.push_back(14479);
        internalCounters.push_back(14564);
        internalCounters.push_back(14649);
        internalCounters.push_back(14734);
        internalCounters.push_back(14819);
        internalCounters.push_back(14904);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8648);
        internalCounters.push_back(8904);
        internalCounters.push_back(9160);
        internalCounters.push_back(9416);
        internalCounters.push_back(9672);
        internalCounters.push_back(9928);
        internalCounters.push_back(10184);
        internalCounters.push_back(10440);
        internalCounters.push_back(10696);
        internalCounters.push_back(10952);
        internalCounters.push_back(11208);
        internalCounters.push_back(11464);
        internalCounters.push_back(11720);
        internalCounters.push_back(11976);
        internalCounters.push_back(12232);
        internalCounters.push_back(12488);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4282);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6");
    }
}

