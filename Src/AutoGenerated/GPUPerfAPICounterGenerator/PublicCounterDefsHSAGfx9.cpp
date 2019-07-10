//==============================================================================
// Copyright (c) 2010-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for HSAGFX9
//==============================================================================

#include "GPACounter.h"
#include "PublicCounterDefsHSAGfx9.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersHSAGfx9(GPA_DerivedCounters& c)
{
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(442);

        c.DefineDerivedCounter("Wavefronts", "General", "Total wavefronts.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "e8999836-489d-80a6-8e94-2c3ea191fd58");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(464);
        internalCounters.push_back(442);

        c.DefineDerivedCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(468);
        internalCounters.push_back(442);

        c.DefineDerivedCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(466);
        internalCounters.push_back(1495);
        internalCounters.push_back(1614);
        internalCounters.push_back(1733);
        internalCounters.push_back(1852);
        internalCounters.push_back(1971);
        internalCounters.push_back(2090);
        internalCounters.push_back(2209);
        internalCounters.push_back(2328);
        internalCounters.push_back(2447);
        internalCounters.push_back(2566);
        internalCounters.push_back(2685);
        internalCounters.push_back(2804);
        internalCounters.push_back(2923);
        internalCounters.push_back(3042);
        internalCounters.push_back(3161);
        internalCounters.push_back(3280);
        internalCounters.push_back(442);

        c.DefineDerivedCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/", "85970f8f-0b2c-6431-9e52-7999236e6e8a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(469);
        internalCounters.push_back(442);

        c.DefineDerivedCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(465);
        internalCounters.push_back(1496);
        internalCounters.push_back(1615);
        internalCounters.push_back(1734);
        internalCounters.push_back(1853);
        internalCounters.push_back(1972);
        internalCounters.push_back(2091);
        internalCounters.push_back(2210);
        internalCounters.push_back(2329);
        internalCounters.push_back(2448);
        internalCounters.push_back(2567);
        internalCounters.push_back(2686);
        internalCounters.push_back(2805);
        internalCounters.push_back(2924);
        internalCounters.push_back(3043);
        internalCounters.push_back(3162);
        internalCounters.push_back(3281);
        internalCounters.push_back(442);

        c.DefineDerivedCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/", "d8154a17-224d-704e-73d2-bb5d150f3196");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(470);
        internalCounters.push_back(471);
        internalCounters.push_back(442);

        c.DefineDerivedCounter("FlatVMemInsts", "General", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,-,2,/", "05e4a953-c59a-e722-872b-e4bc7526bcee");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(472);
        internalCounters.push_back(471);
        internalCounters.push_back(442);

        c.DefineDerivedCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control). Excludes FLAT instructions that read from or write to LDS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,-,2,/", "be9bbead-f82a-a2c6-8333-1a5c4ce5ee98");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(471);
        internalCounters.push_back(442);

        c.DefineDerivedCounter("FlatLDSInsts", "LocalMemory", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "0f7d8f58-1750-a36f-d03e-85a2d9cd6e08");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(473);
        internalCounters.push_back(442);

        c.DefineDerivedCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(523);
        internalCounters.push_back(509);

        c.DefineDerivedCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,(64),*,/,(100),*,(100),min", "ffea5f90-624f-67dd-4ca6-74911f4c85d3");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(509);
        internalCounters.push_back(58);

        c.DefineDerivedCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(522);
        internalCounters.push_back(58);

        c.DefineDerivedCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_CUS,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3409);
        internalCounters.push_back(3691);
        internalCounters.push_back(3973);
        internalCounters.push_back(4255);
        internalCounters.push_back(4537);
        internalCounters.push_back(4819);
        internalCounters.push_back(5101);
        internalCounters.push_back(5383);
        internalCounters.push_back(5665);
        internalCounters.push_back(5947);
        internalCounters.push_back(6229);
        internalCounters.push_back(6511);
        internalCounters.push_back(6793);
        internalCounters.push_back(7075);
        internalCounters.push_back(7357);
        internalCounters.push_back(7639);
        internalCounters.push_back(3410);
        internalCounters.push_back(3692);
        internalCounters.push_back(3974);
        internalCounters.push_back(4256);
        internalCounters.push_back(4538);
        internalCounters.push_back(4820);
        internalCounters.push_back(5102);
        internalCounters.push_back(5384);
        internalCounters.push_back(5666);
        internalCounters.push_back(5948);
        internalCounters.push_back(6230);
        internalCounters.push_back(6512);
        internalCounters.push_back(6794);
        internalCounters.push_back(7076);
        internalCounters.push_back(7358);
        internalCounters.push_back(7640);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(64),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3397);
        internalCounters.push_back(3679);
        internalCounters.push_back(3961);
        internalCounters.push_back(4243);
        internalCounters.push_back(4525);
        internalCounters.push_back(4807);
        internalCounters.push_back(5089);
        internalCounters.push_back(5371);
        internalCounters.push_back(5653);
        internalCounters.push_back(5935);
        internalCounters.push_back(6217);
        internalCounters.push_back(6499);
        internalCounters.push_back(6781);
        internalCounters.push_back(7063);
        internalCounters.push_back(7345);
        internalCounters.push_back(7627);
        internalCounters.push_back(3398);
        internalCounters.push_back(3680);
        internalCounters.push_back(3962);
        internalCounters.push_back(4244);
        internalCounters.push_back(4526);
        internalCounters.push_back(4808);
        internalCounters.push_back(5090);
        internalCounters.push_back(5372);
        internalCounters.push_back(5654);
        internalCounters.push_back(5936);
        internalCounters.push_back(6218);
        internalCounters.push_back(6500);
        internalCounters.push_back(6782);
        internalCounters.push_back(7064);
        internalCounters.push_back(7346);
        internalCounters.push_back(7628);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+,(1024),/", "e09d95da-2772-f7cb-51f5-4fad27bb998b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3388);
        internalCounters.push_back(3670);
        internalCounters.push_back(3952);
        internalCounters.push_back(4234);
        internalCounters.push_back(4516);
        internalCounters.push_back(4798);
        internalCounters.push_back(5080);
        internalCounters.push_back(5362);
        internalCounters.push_back(5644);
        internalCounters.push_back(5926);
        internalCounters.push_back(6208);
        internalCounters.push_back(6490);
        internalCounters.push_back(6772);
        internalCounters.push_back(7054);
        internalCounters.push_back(7336);
        internalCounters.push_back(7618);
        internalCounters.push_back(3390);
        internalCounters.push_back(3672);
        internalCounters.push_back(3954);
        internalCounters.push_back(4236);
        internalCounters.push_back(4518);
        internalCounters.push_back(4800);
        internalCounters.push_back(5082);
        internalCounters.push_back(5364);
        internalCounters.push_back(5646);
        internalCounters.push_back(5928);
        internalCounters.push_back(6210);
        internalCounters.push_back(6492);
        internalCounters.push_back(6774);
        internalCounters.push_back(7056);
        internalCounters.push_back(7338);
        internalCounters.push_back(7620);

        c.DefineDerivedCounter("L2CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L2 cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "7507935e-ed29-f169-ee27-9b0fa9b88f3c");
    }
    {
        vector<gpa_uint32> internalCounters;
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
        internalCounters.push_back(3075);
        internalCounters.push_back(3194);
        internalCounters.push_back(58);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7886);
        internalCounters.push_back(7971);
        internalCounters.push_back(8056);
        internalCounters.push_back(8141);
        internalCounters.push_back(8226);
        internalCounters.push_back(8311);
        internalCounters.push_back(8396);
        internalCounters.push_back(8481);
        internalCounters.push_back(8566);
        internalCounters.push_back(8651);
        internalCounters.push_back(8736);
        internalCounters.push_back(8821);
        internalCounters.push_back(8906);
        internalCounters.push_back(8991);
        internalCounters.push_back(9076);
        internalCounters.push_back(9161);
        internalCounters.push_back(58);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3401);
        internalCounters.push_back(3683);
        internalCounters.push_back(3965);
        internalCounters.push_back(4247);
        internalCounters.push_back(4529);
        internalCounters.push_back(4811);
        internalCounters.push_back(5093);
        internalCounters.push_back(5375);
        internalCounters.push_back(5657);
        internalCounters.push_back(5939);
        internalCounters.push_back(6221);
        internalCounters.push_back(6503);
        internalCounters.push_back(6785);
        internalCounters.push_back(7067);
        internalCounters.push_back(7349);
        internalCounters.push_back(7631);
        internalCounters.push_back(58);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(531);
        internalCounters.push_back(58);

        c.DefineDerivedCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6");
    }
}

