//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions for CL GFX103 
//==============================================================================

#include "gpa_counter.h"
#include "public_counter_definitions_cl_gfx103.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersCL_Gfx103(GPA_DerivedCounters& c)
{
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5282);

        c.DefineDerivedCounter("Wavefronts", "General", "Total wavefronts.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "e8999836-489d-80a6-8e94-2c3ea191fd58");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5342);
        internalCounters.push_back(5282);

        c.DefineDerivedCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5338);
        internalCounters.push_back(5282);

        c.DefineDerivedCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5347);
        internalCounters.push_back(5282);

        c.DefineDerivedCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "85970f8f-0b2c-6431-9e52-7999236e6e8a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5339);
        internalCounters.push_back(5282);

        c.DefineDerivedCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5348);
        internalCounters.push_back(5282);

        c.DefineDerivedCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "d8154a17-224d-704e-73d2-bb5d150f3196");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5337);
        internalCounters.push_back(5282);

        c.DefineDerivedCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "852ccd67-d2eb-d238-567a-0d1f7bf5f34f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5333);
        internalCounters.push_back(5282);

        c.DefineDerivedCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5360);
        internalCounters.push_back(5395);
        internalCounters.push_back(5283);

        c.DefineDerivedCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,(64),(32),2,ifnotzero,*,/,(100),*,(100),min", "435fc505-4d15-095e-79f1-80346bcd0a24");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5395);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5338);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_CUS,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(20851);
        internalCounters.push_back(21105);
        internalCounters.push_back(21359);
        internalCounters.push_back(21613);
        internalCounters.push_back(21867);
        internalCounters.push_back(22121);
        internalCounters.push_back(22375);
        internalCounters.push_back(22629);
        internalCounters.push_back(22883);
        internalCounters.push_back(23137);
        internalCounters.push_back(23391);
        internalCounters.push_back(23645);
        internalCounters.push_back(23899);
        internalCounters.push_back(24153);
        internalCounters.push_back(24407);
        internalCounters.push_back(24661);
        internalCounters.push_back(24915);
        internalCounters.push_back(25169);
        internalCounters.push_back(25423);
        internalCounters.push_back(25677);
        internalCounters.push_back(25931);
        internalCounters.push_back(26185);
        internalCounters.push_back(26439);
        internalCounters.push_back(26693);
        internalCounters.push_back(20852);
        internalCounters.push_back(21106);
        internalCounters.push_back(21360);
        internalCounters.push_back(21614);
        internalCounters.push_back(21868);
        internalCounters.push_back(22122);
        internalCounters.push_back(22376);
        internalCounters.push_back(22630);
        internalCounters.push_back(22884);
        internalCounters.push_back(23138);
        internalCounters.push_back(23392);
        internalCounters.push_back(23646);
        internalCounters.push_back(23900);
        internalCounters.push_back(24154);
        internalCounters.push_back(24408);
        internalCounters.push_back(24662);
        internalCounters.push_back(24916);
        internalCounters.push_back(25170);
        internalCounters.push_back(25424);
        internalCounters.push_back(25678);
        internalCounters.push_back(25932);
        internalCounters.push_back(26186);
        internalCounters.push_back(26440);
        internalCounters.push_back(26694);
        internalCounters.push_back(20853);
        internalCounters.push_back(21107);
        internalCounters.push_back(21361);
        internalCounters.push_back(21615);
        internalCounters.push_back(21869);
        internalCounters.push_back(22123);
        internalCounters.push_back(22377);
        internalCounters.push_back(22631);
        internalCounters.push_back(22885);
        internalCounters.push_back(23139);
        internalCounters.push_back(23393);
        internalCounters.push_back(23647);
        internalCounters.push_back(23901);
        internalCounters.push_back(24155);
        internalCounters.push_back(24409);
        internalCounters.push_back(24663);
        internalCounters.push_back(24917);
        internalCounters.push_back(25171);
        internalCounters.push_back(25425);
        internalCounters.push_back(25679);
        internalCounters.push_back(25933);
        internalCounters.push_back(26187);
        internalCounters.push_back(26441);
        internalCounters.push_back(26695);
        internalCounters.push_back(20854);
        internalCounters.push_back(21108);
        internalCounters.push_back(21362);
        internalCounters.push_back(21616);
        internalCounters.push_back(21870);
        internalCounters.push_back(22124);
        internalCounters.push_back(22378);
        internalCounters.push_back(22632);
        internalCounters.push_back(22886);
        internalCounters.push_back(23140);
        internalCounters.push_back(23394);
        internalCounters.push_back(23648);
        internalCounters.push_back(23902);
        internalCounters.push_back(24156);
        internalCounters.push_back(24410);
        internalCounters.push_back(24664);
        internalCounters.push_back(24918);
        internalCounters.push_back(25172);
        internalCounters.push_back(25426);
        internalCounters.push_back(25680);
        internalCounters.push_back(25934);
        internalCounters.push_back(26188);
        internalCounters.push_back(26442);
        internalCounters.push_back(26696);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24,(32),*,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum24,(64),*,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,sum24,(96),*,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum24,(128),*,sum4,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(20835);
        internalCounters.push_back(21089);
        internalCounters.push_back(21343);
        internalCounters.push_back(21597);
        internalCounters.push_back(21851);
        internalCounters.push_back(22105);
        internalCounters.push_back(22359);
        internalCounters.push_back(22613);
        internalCounters.push_back(22867);
        internalCounters.push_back(23121);
        internalCounters.push_back(23375);
        internalCounters.push_back(23629);
        internalCounters.push_back(23883);
        internalCounters.push_back(24137);
        internalCounters.push_back(24391);
        internalCounters.push_back(24645);
        internalCounters.push_back(24899);
        internalCounters.push_back(25153);
        internalCounters.push_back(25407);
        internalCounters.push_back(25661);
        internalCounters.push_back(25915);
        internalCounters.push_back(26169);
        internalCounters.push_back(26423);
        internalCounters.push_back(26677);
        internalCounters.push_back(20837);
        internalCounters.push_back(21091);
        internalCounters.push_back(21345);
        internalCounters.push_back(21599);
        internalCounters.push_back(21853);
        internalCounters.push_back(22107);
        internalCounters.push_back(22361);
        internalCounters.push_back(22615);
        internalCounters.push_back(22869);
        internalCounters.push_back(23123);
        internalCounters.push_back(23377);
        internalCounters.push_back(23631);
        internalCounters.push_back(23885);
        internalCounters.push_back(24139);
        internalCounters.push_back(24393);
        internalCounters.push_back(24647);
        internalCounters.push_back(24901);
        internalCounters.push_back(25155);
        internalCounters.push_back(25409);
        internalCounters.push_back(25663);
        internalCounters.push_back(25917);
        internalCounters.push_back(26171);
        internalCounters.push_back(26425);
        internalCounters.push_back(26679);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum24,-,(32),*,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum24,(64),*,+,(1024),/", "e09d95da-2772-f7cb-51f5-4fad27bb998b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16456);
        internalCounters.push_back(16533);
        internalCounters.push_back(16610);
        internalCounters.push_back(16687);
        internalCounters.push_back(16764);
        internalCounters.push_back(16841);
        internalCounters.push_back(16918);
        internalCounters.push_back(16995);
        internalCounters.push_back(17072);
        internalCounters.push_back(17149);
        internalCounters.push_back(17226);
        internalCounters.push_back(17303);
        internalCounters.push_back(17380);
        internalCounters.push_back(17457);
        internalCounters.push_back(17534);
        internalCounters.push_back(17611);
        internalCounters.push_back(16465);
        internalCounters.push_back(16542);
        internalCounters.push_back(16619);
        internalCounters.push_back(16696);
        internalCounters.push_back(16773);
        internalCounters.push_back(16850);
        internalCounters.push_back(16927);
        internalCounters.push_back(17004);
        internalCounters.push_back(17081);
        internalCounters.push_back(17158);
        internalCounters.push_back(17235);
        internalCounters.push_back(17312);
        internalCounters.push_back(17389);
        internalCounters.push_back(17466);
        internalCounters.push_back(17543);
        internalCounters.push_back(17620);

        c.DefineDerivedCounter("L0CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L0 cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "be1e0578-82b8-ad7f-ba3f-3afce150937a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(20167);
        internalCounters.push_back(20171);

        c.DefineDerivedCounter("L1CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Writes and atomics always miss this cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),1,0,/,-,(100),*,0,ifnotzero", "b10c589c-f7a5-b8f2-46c2-e0aed4a84105");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(20755);
        internalCounters.push_back(21009);
        internalCounters.push_back(21263);
        internalCounters.push_back(21517);
        internalCounters.push_back(21771);
        internalCounters.push_back(22025);
        internalCounters.push_back(22279);
        internalCounters.push_back(22533);
        internalCounters.push_back(22787);
        internalCounters.push_back(23041);
        internalCounters.push_back(23295);
        internalCounters.push_back(23549);
        internalCounters.push_back(23803);
        internalCounters.push_back(24057);
        internalCounters.push_back(24311);
        internalCounters.push_back(24565);
        internalCounters.push_back(24819);
        internalCounters.push_back(25073);
        internalCounters.push_back(25327);
        internalCounters.push_back(25581);
        internalCounters.push_back(25835);
        internalCounters.push_back(26089);
        internalCounters.push_back(26343);
        internalCounters.push_back(26597);
        internalCounters.push_back(20795);
        internalCounters.push_back(21049);
        internalCounters.push_back(21303);
        internalCounters.push_back(21557);
        internalCounters.push_back(21811);
        internalCounters.push_back(22065);
        internalCounters.push_back(22319);
        internalCounters.push_back(22573);
        internalCounters.push_back(22827);
        internalCounters.push_back(23081);
        internalCounters.push_back(23335);
        internalCounters.push_back(23589);
        internalCounters.push_back(23843);
        internalCounters.push_back(24097);
        internalCounters.push_back(24351);
        internalCounters.push_back(24605);
        internalCounters.push_back(24859);
        internalCounters.push_back(25113);
        internalCounters.push_back(25367);
        internalCounters.push_back(25621);
        internalCounters.push_back(25875);
        internalCounters.push_back(26129);
        internalCounters.push_back(26383);
        internalCounters.push_back(26637);

        c.DefineDerivedCounter("L2CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L2 cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24,ifnotzero", "7507935e-ed29-f169-ee27-9b0fa9b88f3c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9614);
        internalCounters.push_back(9850);
        internalCounters.push_back(10086);
        internalCounters.push_back(10322);
        internalCounters.push_back(10558);
        internalCounters.push_back(10794);
        internalCounters.push_back(11030);
        internalCounters.push_back(11266);
        internalCounters.push_back(11502);
        internalCounters.push_back(11738);
        internalCounters.push_back(11974);
        internalCounters.push_back(12210);
        internalCounters.push_back(12446);
        internalCounters.push_back(12682);
        internalCounters.push_back(12918);
        internalCounters.push_back(13154);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16483);
        internalCounters.push_back(16560);
        internalCounters.push_back(16637);
        internalCounters.push_back(16714);
        internalCounters.push_back(16791);
        internalCounters.push_back(16868);
        internalCounters.push_back(16945);
        internalCounters.push_back(17022);
        internalCounters.push_back(17099);
        internalCounters.push_back(17176);
        internalCounters.push_back(17253);
        internalCounters.push_back(17330);
        internalCounters.push_back(17407);
        internalCounters.push_back(17484);
        internalCounters.push_back(17561);
        internalCounters.push_back(17638);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(20840);
        internalCounters.push_back(21094);
        internalCounters.push_back(21348);
        internalCounters.push_back(21602);
        internalCounters.push_back(21856);
        internalCounters.push_back(22110);
        internalCounters.push_back(22364);
        internalCounters.push_back(22618);
        internalCounters.push_back(22872);
        internalCounters.push_back(23126);
        internalCounters.push_back(23380);
        internalCounters.push_back(23634);
        internalCounters.push_back(23888);
        internalCounters.push_back(24142);
        internalCounters.push_back(24396);
        internalCounters.push_back(24650);
        internalCounters.push_back(24904);
        internalCounters.push_back(25158);
        internalCounters.push_back(25412);
        internalCounters.push_back(25666);
        internalCounters.push_back(25920);
        internalCounters.push_back(26174);
        internalCounters.push_back(26428);
        internalCounters.push_back(26682);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,max24,24,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5563);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6");
    }
}

