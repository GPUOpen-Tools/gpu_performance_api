//==============================================================================
// Copyright (c) 2010-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for CL GFX103.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_cl_gfx103.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersClGfx103(GpaDerivedCounters& c)
{
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5250);

        c.DefineDerivedCounter("Wavefronts", "General", "Total wavefronts.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "e8999836-489d-80a6-8e94-2c3ea191fd58");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5310);
        internal_counters.push_back(5250);

        c.DefineDerivedCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5306);
        internal_counters.push_back(5250);

        c.DefineDerivedCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5315);
        internal_counters.push_back(5250);

        c.DefineDerivedCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "85970f8f-0b2c-6431-9e52-7999236e6e8a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5307);
        internal_counters.push_back(5250);

        c.DefineDerivedCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5316);
        internal_counters.push_back(5250);

        c.DefineDerivedCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "d8154a17-224d-704e-73d2-bb5d150f3196");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5305);
        internal_counters.push_back(5250);

        c.DefineDerivedCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "852ccd67-d2eb-d238-567a-0d1f7bf5f34f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5301);
        internal_counters.push_back(5250);

        c.DefineDerivedCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "c63fc276-151e-3b88-6edb-a0c92507aadb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5328);
        internal_counters.push_back(5363);
        internal_counters.push_back(5251);

        c.DefineDerivedCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,(64),(32),2,ifnotzero,*,/,(100),*,(100),min", "435fc505-4d15-095e-79f1-80346bcd0a24");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5363);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_SIMDS,/,1,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5306);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(20550);
        internal_counters.push_back(20804);
        internal_counters.push_back(21058);
        internal_counters.push_back(21312);
        internal_counters.push_back(21566);
        internal_counters.push_back(21820);
        internal_counters.push_back(22074);
        internal_counters.push_back(22328);
        internal_counters.push_back(22582);
        internal_counters.push_back(22836);
        internal_counters.push_back(23090);
        internal_counters.push_back(23344);
        internal_counters.push_back(23598);
        internal_counters.push_back(23852);
        internal_counters.push_back(24106);
        internal_counters.push_back(24360);
        internal_counters.push_back(24614);
        internal_counters.push_back(24868);
        internal_counters.push_back(25122);
        internal_counters.push_back(25376);
        internal_counters.push_back(25630);
        internal_counters.push_back(25884);
        internal_counters.push_back(26138);
        internal_counters.push_back(26392);
        internal_counters.push_back(20551);
        internal_counters.push_back(20805);
        internal_counters.push_back(21059);
        internal_counters.push_back(21313);
        internal_counters.push_back(21567);
        internal_counters.push_back(21821);
        internal_counters.push_back(22075);
        internal_counters.push_back(22329);
        internal_counters.push_back(22583);
        internal_counters.push_back(22837);
        internal_counters.push_back(23091);
        internal_counters.push_back(23345);
        internal_counters.push_back(23599);
        internal_counters.push_back(23853);
        internal_counters.push_back(24107);
        internal_counters.push_back(24361);
        internal_counters.push_back(24615);
        internal_counters.push_back(24869);
        internal_counters.push_back(25123);
        internal_counters.push_back(25377);
        internal_counters.push_back(25631);
        internal_counters.push_back(25885);
        internal_counters.push_back(26139);
        internal_counters.push_back(26393);
        internal_counters.push_back(20552);
        internal_counters.push_back(20806);
        internal_counters.push_back(21060);
        internal_counters.push_back(21314);
        internal_counters.push_back(21568);
        internal_counters.push_back(21822);
        internal_counters.push_back(22076);
        internal_counters.push_back(22330);
        internal_counters.push_back(22584);
        internal_counters.push_back(22838);
        internal_counters.push_back(23092);
        internal_counters.push_back(23346);
        internal_counters.push_back(23600);
        internal_counters.push_back(23854);
        internal_counters.push_back(24108);
        internal_counters.push_back(24362);
        internal_counters.push_back(24616);
        internal_counters.push_back(24870);
        internal_counters.push_back(25124);
        internal_counters.push_back(25378);
        internal_counters.push_back(25632);
        internal_counters.push_back(25886);
        internal_counters.push_back(26140);
        internal_counters.push_back(26394);
        internal_counters.push_back(20553);
        internal_counters.push_back(20807);
        internal_counters.push_back(21061);
        internal_counters.push_back(21315);
        internal_counters.push_back(21569);
        internal_counters.push_back(21823);
        internal_counters.push_back(22077);
        internal_counters.push_back(22331);
        internal_counters.push_back(22585);
        internal_counters.push_back(22839);
        internal_counters.push_back(23093);
        internal_counters.push_back(23347);
        internal_counters.push_back(23601);
        internal_counters.push_back(23855);
        internal_counters.push_back(24109);
        internal_counters.push_back(24363);
        internal_counters.push_back(24617);
        internal_counters.push_back(24871);
        internal_counters.push_back(25125);
        internal_counters.push_back(25379);
        internal_counters.push_back(25633);
        internal_counters.push_back(25887);
        internal_counters.push_back(26141);
        internal_counters.push_back(26395);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeKilobytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24,(32),*,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum24,(64),*,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,sum24,(96),*,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum24,(128),*,sum4,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(20534);
        internal_counters.push_back(20788);
        internal_counters.push_back(21042);
        internal_counters.push_back(21296);
        internal_counters.push_back(21550);
        internal_counters.push_back(21804);
        internal_counters.push_back(22058);
        internal_counters.push_back(22312);
        internal_counters.push_back(22566);
        internal_counters.push_back(22820);
        internal_counters.push_back(23074);
        internal_counters.push_back(23328);
        internal_counters.push_back(23582);
        internal_counters.push_back(23836);
        internal_counters.push_back(24090);
        internal_counters.push_back(24344);
        internal_counters.push_back(24598);
        internal_counters.push_back(24852);
        internal_counters.push_back(25106);
        internal_counters.push_back(25360);
        internal_counters.push_back(25614);
        internal_counters.push_back(25868);
        internal_counters.push_back(26122);
        internal_counters.push_back(26376);
        internal_counters.push_back(20536);
        internal_counters.push_back(20790);
        internal_counters.push_back(21044);
        internal_counters.push_back(21298);
        internal_counters.push_back(21552);
        internal_counters.push_back(21806);
        internal_counters.push_back(22060);
        internal_counters.push_back(22314);
        internal_counters.push_back(22568);
        internal_counters.push_back(22822);
        internal_counters.push_back(23076);
        internal_counters.push_back(23330);
        internal_counters.push_back(23584);
        internal_counters.push_back(23838);
        internal_counters.push_back(24092);
        internal_counters.push_back(24346);
        internal_counters.push_back(24600);
        internal_counters.push_back(24854);
        internal_counters.push_back(25108);
        internal_counters.push_back(25362);
        internal_counters.push_back(25616);
        internal_counters.push_back(25870);
        internal_counters.push_back(26124);
        internal_counters.push_back(26378);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeKilobytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum24,-,(32),*,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum24,(64),*,+,(1024),/", "e09d95da-2772-f7cb-51f5-4fad27bb998b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16424);
        internal_counters.push_back(16485);
        internal_counters.push_back(16546);
        internal_counters.push_back(16607);
        internal_counters.push_back(16668);
        internal_counters.push_back(16729);
        internal_counters.push_back(16790);
        internal_counters.push_back(16851);
        internal_counters.push_back(16912);
        internal_counters.push_back(16973);
        internal_counters.push_back(17034);
        internal_counters.push_back(17095);
        internal_counters.push_back(17156);
        internal_counters.push_back(17217);
        internal_counters.push_back(17278);
        internal_counters.push_back(17339);
        internal_counters.push_back(16433);
        internal_counters.push_back(16494);
        internal_counters.push_back(16555);
        internal_counters.push_back(16616);
        internal_counters.push_back(16677);
        internal_counters.push_back(16738);
        internal_counters.push_back(16799);
        internal_counters.push_back(16860);
        internal_counters.push_back(16921);
        internal_counters.push_back(16982);
        internal_counters.push_back(17043);
        internal_counters.push_back(17104);
        internal_counters.push_back(17165);
        internal_counters.push_back(17226);
        internal_counters.push_back(17287);
        internal_counters.push_back(17348);

        c.DefineDerivedCounter("L0CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L0 cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "be1e0578-82b8-ad7f-ba3f-3afce150937a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(19866);
        internal_counters.push_back(19870);

        c.DefineDerivedCounter("L1CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Writes and atomics always miss this cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),1,0,/,-,(100),*,0,ifnotzero", "b10c589c-f7a5-b8f2-46c2-e0aed4a84105");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(20454);
        internal_counters.push_back(20708);
        internal_counters.push_back(20962);
        internal_counters.push_back(21216);
        internal_counters.push_back(21470);
        internal_counters.push_back(21724);
        internal_counters.push_back(21978);
        internal_counters.push_back(22232);
        internal_counters.push_back(22486);
        internal_counters.push_back(22740);
        internal_counters.push_back(22994);
        internal_counters.push_back(23248);
        internal_counters.push_back(23502);
        internal_counters.push_back(23756);
        internal_counters.push_back(24010);
        internal_counters.push_back(24264);
        internal_counters.push_back(24518);
        internal_counters.push_back(24772);
        internal_counters.push_back(25026);
        internal_counters.push_back(25280);
        internal_counters.push_back(25534);
        internal_counters.push_back(25788);
        internal_counters.push_back(26042);
        internal_counters.push_back(26296);
        internal_counters.push_back(20494);
        internal_counters.push_back(20748);
        internal_counters.push_back(21002);
        internal_counters.push_back(21256);
        internal_counters.push_back(21510);
        internal_counters.push_back(21764);
        internal_counters.push_back(22018);
        internal_counters.push_back(22272);
        internal_counters.push_back(22526);
        internal_counters.push_back(22780);
        internal_counters.push_back(23034);
        internal_counters.push_back(23288);
        internal_counters.push_back(23542);
        internal_counters.push_back(23796);
        internal_counters.push_back(24050);
        internal_counters.push_back(24304);
        internal_counters.push_back(24558);
        internal_counters.push_back(24812);
        internal_counters.push_back(25066);
        internal_counters.push_back(25320);
        internal_counters.push_back(25574);
        internal_counters.push_back(25828);
        internal_counters.push_back(26082);
        internal_counters.push_back(26336);

        c.DefineDerivedCounter("L2CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L2 cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24,ifnotzero", "7507935e-ed29-f169-ee27-9b0fa9b88f3c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9582);
        internal_counters.push_back(9818);
        internal_counters.push_back(10054);
        internal_counters.push_back(10290);
        internal_counters.push_back(10526);
        internal_counters.push_back(10762);
        internal_counters.push_back(10998);
        internal_counters.push_back(11234);
        internal_counters.push_back(11470);
        internal_counters.push_back(11706);
        internal_counters.push_back(11942);
        internal_counters.push_back(12178);
        internal_counters.push_back(12414);
        internal_counters.push_back(12650);
        internal_counters.push_back(12886);
        internal_counters.push_back(13122);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16451);
        internal_counters.push_back(16512);
        internal_counters.push_back(16573);
        internal_counters.push_back(16634);
        internal_counters.push_back(16695);
        internal_counters.push_back(16756);
        internal_counters.push_back(16817);
        internal_counters.push_back(16878);
        internal_counters.push_back(16939);
        internal_counters.push_back(17000);
        internal_counters.push_back(17061);
        internal_counters.push_back(17122);
        internal_counters.push_back(17183);
        internal_counters.push_back(17244);
        internal_counters.push_back(17305);
        internal_counters.push_back(17366);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(20539);
        internal_counters.push_back(20793);
        internal_counters.push_back(21047);
        internal_counters.push_back(21301);
        internal_counters.push_back(21555);
        internal_counters.push_back(21809);
        internal_counters.push_back(22063);
        internal_counters.push_back(22317);
        internal_counters.push_back(22571);
        internal_counters.push_back(22825);
        internal_counters.push_back(23079);
        internal_counters.push_back(23333);
        internal_counters.push_back(23587);
        internal_counters.push_back(23841);
        internal_counters.push_back(24095);
        internal_counters.push_back(24349);
        internal_counters.push_back(24603);
        internal_counters.push_back(24857);
        internal_counters.push_back(25111);
        internal_counters.push_back(25365);
        internal_counters.push_back(25619);
        internal_counters.push_back(25873);
        internal_counters.push_back(26127);
        internal_counters.push_back(26381);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,max24,24,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5531);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6");
    }
}

