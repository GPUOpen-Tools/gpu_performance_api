//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions for CL GFX10 
//==============================================================================

#include "gpa_counter.h"
#include "public_counter_definitions_cl_gfx10.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersCLGfx10(GPA_DerivedCounters& c)
{
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5133);

        c.DefineDerivedCounter("Wavefronts", "General", "Total wavefronts.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "e8999836-489d-80a6-8e94-2c3ea191fd58");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5193);
        internalCounters.push_back(5133);

        c.DefineDerivedCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5189);
        internalCounters.push_back(5133);

        c.DefineDerivedCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5198);
        internalCounters.push_back(5133);

        c.DefineDerivedCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "85970f8f-0b2c-6431-9e52-7999236e6e8a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5190);
        internalCounters.push_back(5133);

        c.DefineDerivedCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5199);
        internalCounters.push_back(5133);

        c.DefineDerivedCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "d8154a17-224d-704e-73d2-bb5d150f3196");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5188);
        internalCounters.push_back(5133);

        c.DefineDerivedCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "852ccd67-d2eb-d238-567a-0d1f7bf5f34f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5184);
        internalCounters.push_back(5133);

        c.DefineDerivedCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5211);
        internalCounters.push_back(5246);
        internalCounters.push_back(5134);

        c.DefineDerivedCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,(64),(32),2,ifnotzero,*,/,(100),*,(100),min", "435fc505-4d15-095e-79f1-80346bcd0a24");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5246);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5189);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_CUS,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18606);
        internalCounters.push_back(18841);
        internalCounters.push_back(19076);
        internalCounters.push_back(19311);
        internalCounters.push_back(19546);
        internalCounters.push_back(19781);
        internalCounters.push_back(20016);
        internalCounters.push_back(20251);
        internalCounters.push_back(20486);
        internalCounters.push_back(20721);
        internalCounters.push_back(20956);
        internalCounters.push_back(21191);
        internalCounters.push_back(21426);
        internalCounters.push_back(21661);
        internalCounters.push_back(21896);
        internalCounters.push_back(22131);
        internalCounters.push_back(22366);
        internalCounters.push_back(22601);
        internalCounters.push_back(22836);
        internalCounters.push_back(23071);
        internalCounters.push_back(23306);
        internalCounters.push_back(23541);
        internalCounters.push_back(23776);
        internalCounters.push_back(24011);
        internalCounters.push_back(18607);
        internalCounters.push_back(18842);
        internalCounters.push_back(19077);
        internalCounters.push_back(19312);
        internalCounters.push_back(19547);
        internalCounters.push_back(19782);
        internalCounters.push_back(20017);
        internalCounters.push_back(20252);
        internalCounters.push_back(20487);
        internalCounters.push_back(20722);
        internalCounters.push_back(20957);
        internalCounters.push_back(21192);
        internalCounters.push_back(21427);
        internalCounters.push_back(21662);
        internalCounters.push_back(21897);
        internalCounters.push_back(22132);
        internalCounters.push_back(22367);
        internalCounters.push_back(22602);
        internalCounters.push_back(22837);
        internalCounters.push_back(23072);
        internalCounters.push_back(23307);
        internalCounters.push_back(23542);
        internalCounters.push_back(23777);
        internalCounters.push_back(24012);
        internalCounters.push_back(18608);
        internalCounters.push_back(18843);
        internalCounters.push_back(19078);
        internalCounters.push_back(19313);
        internalCounters.push_back(19548);
        internalCounters.push_back(19783);
        internalCounters.push_back(20018);
        internalCounters.push_back(20253);
        internalCounters.push_back(20488);
        internalCounters.push_back(20723);
        internalCounters.push_back(20958);
        internalCounters.push_back(21193);
        internalCounters.push_back(21428);
        internalCounters.push_back(21663);
        internalCounters.push_back(21898);
        internalCounters.push_back(22133);
        internalCounters.push_back(22368);
        internalCounters.push_back(22603);
        internalCounters.push_back(22838);
        internalCounters.push_back(23073);
        internalCounters.push_back(23308);
        internalCounters.push_back(23543);
        internalCounters.push_back(23778);
        internalCounters.push_back(24013);
        internalCounters.push_back(18609);
        internalCounters.push_back(18844);
        internalCounters.push_back(19079);
        internalCounters.push_back(19314);
        internalCounters.push_back(19549);
        internalCounters.push_back(19784);
        internalCounters.push_back(20019);
        internalCounters.push_back(20254);
        internalCounters.push_back(20489);
        internalCounters.push_back(20724);
        internalCounters.push_back(20959);
        internalCounters.push_back(21194);
        internalCounters.push_back(21429);
        internalCounters.push_back(21664);
        internalCounters.push_back(21899);
        internalCounters.push_back(22134);
        internalCounters.push_back(22369);
        internalCounters.push_back(22604);
        internalCounters.push_back(22839);
        internalCounters.push_back(23074);
        internalCounters.push_back(23309);
        internalCounters.push_back(23544);
        internalCounters.push_back(23779);
        internalCounters.push_back(24014);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24,(32),*,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum24,(64),*,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,sum24,(96),*,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum24,(128),*,sum4,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18592);
        internalCounters.push_back(18827);
        internalCounters.push_back(19062);
        internalCounters.push_back(19297);
        internalCounters.push_back(19532);
        internalCounters.push_back(19767);
        internalCounters.push_back(20002);
        internalCounters.push_back(20237);
        internalCounters.push_back(20472);
        internalCounters.push_back(20707);
        internalCounters.push_back(20942);
        internalCounters.push_back(21177);
        internalCounters.push_back(21412);
        internalCounters.push_back(21647);
        internalCounters.push_back(21882);
        internalCounters.push_back(22117);
        internalCounters.push_back(22352);
        internalCounters.push_back(22587);
        internalCounters.push_back(22822);
        internalCounters.push_back(23057);
        internalCounters.push_back(23292);
        internalCounters.push_back(23527);
        internalCounters.push_back(23762);
        internalCounters.push_back(23997);
        internalCounters.push_back(18593);
        internalCounters.push_back(18828);
        internalCounters.push_back(19063);
        internalCounters.push_back(19298);
        internalCounters.push_back(19533);
        internalCounters.push_back(19768);
        internalCounters.push_back(20003);
        internalCounters.push_back(20238);
        internalCounters.push_back(20473);
        internalCounters.push_back(20708);
        internalCounters.push_back(20943);
        internalCounters.push_back(21178);
        internalCounters.push_back(21413);
        internalCounters.push_back(21648);
        internalCounters.push_back(21883);
        internalCounters.push_back(22118);
        internalCounters.push_back(22353);
        internalCounters.push_back(22588);
        internalCounters.push_back(22823);
        internalCounters.push_back(23058);
        internalCounters.push_back(23293);
        internalCounters.push_back(23528);
        internalCounters.push_back(23763);
        internalCounters.push_back(23998);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum24,-,(32),*,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum24,(64),*,+,(1024),/", "e09d95da-2772-f7cb-51f5-4fad27bb998b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14051);
        internalCounters.push_back(14128);
        internalCounters.push_back(14205);
        internalCounters.push_back(14282);
        internalCounters.push_back(14359);
        internalCounters.push_back(14436);
        internalCounters.push_back(14513);
        internalCounters.push_back(14590);
        internalCounters.push_back(14667);
        internalCounters.push_back(14744);
        internalCounters.push_back(14821);
        internalCounters.push_back(14898);
        internalCounters.push_back(14975);
        internalCounters.push_back(15052);
        internalCounters.push_back(15129);
        internalCounters.push_back(15206);
        internalCounters.push_back(14060);
        internalCounters.push_back(14137);
        internalCounters.push_back(14214);
        internalCounters.push_back(14291);
        internalCounters.push_back(14368);
        internalCounters.push_back(14445);
        internalCounters.push_back(14522);
        internalCounters.push_back(14599);
        internalCounters.push_back(14676);
        internalCounters.push_back(14753);
        internalCounters.push_back(14830);
        internalCounters.push_back(14907);
        internalCounters.push_back(14984);
        internalCounters.push_back(15061);
        internalCounters.push_back(15138);
        internalCounters.push_back(15215);

        c.DefineDerivedCounter("L0CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L0 cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "be1e0578-82b8-ad7f-ba3f-3afce150937a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(17951);
        internalCounters.push_back(17955);

        c.DefineDerivedCounter("L1CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Writes and atomics always miss this cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),1,0,/,-,(100),*,0,ifnotzero", "b10c589c-f7a5-b8f2-46c2-e0aed4a84105");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18520);
        internalCounters.push_back(18755);
        internalCounters.push_back(18990);
        internalCounters.push_back(19225);
        internalCounters.push_back(19460);
        internalCounters.push_back(19695);
        internalCounters.push_back(19930);
        internalCounters.push_back(20165);
        internalCounters.push_back(20400);
        internalCounters.push_back(20635);
        internalCounters.push_back(20870);
        internalCounters.push_back(21105);
        internalCounters.push_back(21340);
        internalCounters.push_back(21575);
        internalCounters.push_back(21810);
        internalCounters.push_back(22045);
        internalCounters.push_back(22280);
        internalCounters.push_back(22515);
        internalCounters.push_back(22750);
        internalCounters.push_back(22985);
        internalCounters.push_back(23220);
        internalCounters.push_back(23455);
        internalCounters.push_back(23690);
        internalCounters.push_back(23925);
        internalCounters.push_back(18552);
        internalCounters.push_back(18787);
        internalCounters.push_back(19022);
        internalCounters.push_back(19257);
        internalCounters.push_back(19492);
        internalCounters.push_back(19727);
        internalCounters.push_back(19962);
        internalCounters.push_back(20197);
        internalCounters.push_back(20432);
        internalCounters.push_back(20667);
        internalCounters.push_back(20902);
        internalCounters.push_back(21137);
        internalCounters.push_back(21372);
        internalCounters.push_back(21607);
        internalCounters.push_back(21842);
        internalCounters.push_back(22077);
        internalCounters.push_back(22312);
        internalCounters.push_back(22547);
        internalCounters.push_back(22782);
        internalCounters.push_back(23017);
        internalCounters.push_back(23252);
        internalCounters.push_back(23487);
        internalCounters.push_back(23722);
        internalCounters.push_back(23957);

        c.DefineDerivedCounter("L2CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L2 cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24,ifnotzero", "7507935e-ed29-f169-ee27-9b0fa9b88f3c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9465);
        internalCounters.push_back(9691);
        internalCounters.push_back(9917);
        internalCounters.push_back(10143);
        internalCounters.push_back(10369);
        internalCounters.push_back(10595);
        internalCounters.push_back(10821);
        internalCounters.push_back(11047);
        internalCounters.push_back(11273);
        internalCounters.push_back(11499);
        internalCounters.push_back(11725);
        internalCounters.push_back(11951);
        internalCounters.push_back(12177);
        internalCounters.push_back(12403);
        internalCounters.push_back(12629);
        internalCounters.push_back(12855);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14078);
        internalCounters.push_back(14155);
        internalCounters.push_back(14232);
        internalCounters.push_back(14309);
        internalCounters.push_back(14386);
        internalCounters.push_back(14463);
        internalCounters.push_back(14540);
        internalCounters.push_back(14617);
        internalCounters.push_back(14694);
        internalCounters.push_back(14771);
        internalCounters.push_back(14848);
        internalCounters.push_back(14925);
        internalCounters.push_back(15002);
        internalCounters.push_back(15079);
        internalCounters.push_back(15156);
        internalCounters.push_back(15233);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18596);
        internalCounters.push_back(18831);
        internalCounters.push_back(19066);
        internalCounters.push_back(19301);
        internalCounters.push_back(19536);
        internalCounters.push_back(19771);
        internalCounters.push_back(20006);
        internalCounters.push_back(20241);
        internalCounters.push_back(20476);
        internalCounters.push_back(20711);
        internalCounters.push_back(20946);
        internalCounters.push_back(21181);
        internalCounters.push_back(21416);
        internalCounters.push_back(21651);
        internalCounters.push_back(21886);
        internalCounters.push_back(22121);
        internalCounters.push_back(22356);
        internalCounters.push_back(22591);
        internalCounters.push_back(22826);
        internalCounters.push_back(23061);
        internalCounters.push_back(23296);
        internalCounters.push_back(23531);
        internalCounters.push_back(23766);
        internalCounters.push_back(24001);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,max24,24,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5414);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6");
    }
}

