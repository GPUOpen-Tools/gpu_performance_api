//==============================================================================
// Copyright (c) 2010-2022 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for CL GFX11.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_cl_gfx11.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersClGfx11(GpaDerivedCounters& c)
{
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4868);

        c.DefineDerivedCounter("Wavefronts", "General", "Total wavefronts.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "e8999836-489d-80a6-8e94-2c3ea191fd58");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24779);
        internal_counters.push_back(25291);
        internal_counters.push_back(25803);
        internal_counters.push_back(26315);
        internal_counters.push_back(26827);
        internal_counters.push_back(27339);
        internal_counters.push_back(27851);
        internal_counters.push_back(28363);
        internal_counters.push_back(4868);

        c.DefineDerivedCounter("VALUInsts", "General", "The average number of vector ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,/", "17c27c10-3d5c-64c2-e7b4-4ee1abdbbb46");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24775);
        internal_counters.push_back(25287);
        internal_counters.push_back(25799);
        internal_counters.push_back(26311);
        internal_counters.push_back(26823);
        internal_counters.push_back(27335);
        internal_counters.push_back(27847);
        internal_counters.push_back(28359);
        internal_counters.push_back(4868);

        c.DefineDerivedCounter("SALUInsts", "General", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,/", "e5693881-8d63-951d-1f4f-f9e4c84236f5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24783);
        internal_counters.push_back(25295);
        internal_counters.push_back(25807);
        internal_counters.push_back(26319);
        internal_counters.push_back(26831);
        internal_counters.push_back(27343);
        internal_counters.push_back(27855);
        internal_counters.push_back(28367);
        internal_counters.push_back(4868);

        c.DefineDerivedCounter("VFetchInsts", "General", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that fetch from video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,/", "85970f8f-0b2c-6431-9e52-7999236e6e8a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24776);
        internal_counters.push_back(25288);
        internal_counters.push_back(25800);
        internal_counters.push_back(26312);
        internal_counters.push_back(26824);
        internal_counters.push_back(27336);
        internal_counters.push_back(27848);
        internal_counters.push_back(28360);
        internal_counters.push_back(4868);

        c.DefineDerivedCounter("SFetchInsts", "General", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,/", "7d9e4356-a8f5-04c7-f7a8-fe68dc01c441");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24784);
        internal_counters.push_back(25296);
        internal_counters.push_back(25808);
        internal_counters.push_back(26320);
        internal_counters.push_back(26832);
        internal_counters.push_back(27344);
        internal_counters.push_back(27856);
        internal_counters.push_back(28368);
        internal_counters.push_back(4868);

        c.DefineDerivedCounter("VWriteInsts", "General", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control). Excludes FLAT instructions that write to video memory.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,/", "d8154a17-224d-704e-73d2-bb5d150f3196");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24774);
        internal_counters.push_back(25286);
        internal_counters.push_back(25798);
        internal_counters.push_back(26310);
        internal_counters.push_back(26822);
        internal_counters.push_back(27334);
        internal_counters.push_back(27846);
        internal_counters.push_back(28358);
        internal_counters.push_back(4868);

        c.DefineDerivedCounter("LDSInsts", "LocalMemory", "The average number of LDS read or LDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,/", "852ccd67-d2eb-d238-567a-0d1f7bf5f34f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24771);
        internal_counters.push_back(25283);
        internal_counters.push_back(25795);
        internal_counters.push_back(26307);
        internal_counters.push_back(26819);
        internal_counters.push_back(27331);
        internal_counters.push_back(27843);
        internal_counters.push_back(28355);
        internal_counters.push_back(4868);

        c.DefineDerivedCounter("GDSInsts", "General", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,/", "c63fc276-151e-3b88-6edb-a0c92507aadb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24797);
        internal_counters.push_back(25309);
        internal_counters.push_back(25821);
        internal_counters.push_back(26333);
        internal_counters.push_back(26845);
        internal_counters.push_back(27357);
        internal_counters.push_back(27869);
        internal_counters.push_back(28381);
        internal_counters.push_back(24820);
        internal_counters.push_back(25332);
        internal_counters.push_back(25844);
        internal_counters.push_back(26356);
        internal_counters.push_back(26868);
        internal_counters.push_back(27380);
        internal_counters.push_back(27892);
        internal_counters.push_back(28404);
        internal_counters.push_back(4869);

        c.DefineDerivedCounter("VALUUtilization", "General", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,sum8,(64),(32),16,ifnotzero,*,/,(100),*,(100),min", "435fc505-4d15-095e-79f1-80346bcd0a24");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24820);
        internal_counters.push_back(25332);
        internal_counters.push_back(25844);
        internal_counters.push_back(26356);
        internal_counters.push_back(26868);
        internal_counters.push_back(27380);
        internal_counters.push_back(27892);
        internal_counters.push_back(28404);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("VALUBusy", "General", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,sum8,NUM_SIMDS,/,8,/,(100),*", "51800108-e003-3c1f-b92a-e224aaab3c1b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24775);
        internal_counters.push_back(25287);
        internal_counters.push_back(25799);
        internal_counters.push_back(26311);
        internal_counters.push_back(26823);
        internal_counters.push_back(27335);
        internal_counters.push_back(27847);
        internal_counters.push_back(28359);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("SALUBusy", "General", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,sum8,NUM_CUS,/,8,/,(100),*", "f1d53e7a-0182-42f8-7d2c-6029bff6bc2d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(17051);
        internal_counters.push_back(17310);
        internal_counters.push_back(17569);
        internal_counters.push_back(17828);
        internal_counters.push_back(18087);
        internal_counters.push_back(18346);
        internal_counters.push_back(18605);
        internal_counters.push_back(18864);
        internal_counters.push_back(19123);
        internal_counters.push_back(19382);
        internal_counters.push_back(19641);
        internal_counters.push_back(19900);
        internal_counters.push_back(20159);
        internal_counters.push_back(20418);
        internal_counters.push_back(20677);
        internal_counters.push_back(20936);
        internal_counters.push_back(17052);
        internal_counters.push_back(17311);
        internal_counters.push_back(17570);
        internal_counters.push_back(17829);
        internal_counters.push_back(18088);
        internal_counters.push_back(18347);
        internal_counters.push_back(18606);
        internal_counters.push_back(18865);
        internal_counters.push_back(19124);
        internal_counters.push_back(19383);
        internal_counters.push_back(19642);
        internal_counters.push_back(19901);
        internal_counters.push_back(20160);
        internal_counters.push_back(20419);
        internal_counters.push_back(20678);
        internal_counters.push_back(20937);
        internal_counters.push_back(17053);
        internal_counters.push_back(17312);
        internal_counters.push_back(17571);
        internal_counters.push_back(17830);
        internal_counters.push_back(18089);
        internal_counters.push_back(18348);
        internal_counters.push_back(18607);
        internal_counters.push_back(18866);
        internal_counters.push_back(19125);
        internal_counters.push_back(19384);
        internal_counters.push_back(19643);
        internal_counters.push_back(19902);
        internal_counters.push_back(20161);
        internal_counters.push_back(20420);
        internal_counters.push_back(20679);
        internal_counters.push_back(20938);
        internal_counters.push_back(17054);
        internal_counters.push_back(17313);
        internal_counters.push_back(17572);
        internal_counters.push_back(17831);
        internal_counters.push_back(18090);
        internal_counters.push_back(18349);
        internal_counters.push_back(18608);
        internal_counters.push_back(18867);
        internal_counters.push_back(19126);
        internal_counters.push_back(19385);
        internal_counters.push_back(19644);
        internal_counters.push_back(19903);
        internal_counters.push_back(20162);
        internal_counters.push_back(20421);
        internal_counters.push_back(20680);
        internal_counters.push_back(20939);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeKilobytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,(96),*,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,(128),*,sum4,(1024),/", "d91ac445-b44f-f821-9123-9d829e544c33");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(17035);
        internal_counters.push_back(17294);
        internal_counters.push_back(17553);
        internal_counters.push_back(17812);
        internal_counters.push_back(18071);
        internal_counters.push_back(18330);
        internal_counters.push_back(18589);
        internal_counters.push_back(18848);
        internal_counters.push_back(19107);
        internal_counters.push_back(19366);
        internal_counters.push_back(19625);
        internal_counters.push_back(19884);
        internal_counters.push_back(20143);
        internal_counters.push_back(20402);
        internal_counters.push_back(20661);
        internal_counters.push_back(20920);
        internal_counters.push_back(17037);
        internal_counters.push_back(17296);
        internal_counters.push_back(17555);
        internal_counters.push_back(17814);
        internal_counters.push_back(18073);
        internal_counters.push_back(18332);
        internal_counters.push_back(18591);
        internal_counters.push_back(18850);
        internal_counters.push_back(19109);
        internal_counters.push_back(19368);
        internal_counters.push_back(19627);
        internal_counters.push_back(19886);
        internal_counters.push_back(20145);
        internal_counters.push_back(20404);
        internal_counters.push_back(20663);
        internal_counters.push_back(20922);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeKilobytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+,(1024),/", "e09d95da-2772-f7cb-51f5-4fad27bb998b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12052);
        internal_counters.push_back(12130);
        internal_counters.push_back(12208);
        internal_counters.push_back(12286);
        internal_counters.push_back(12364);
        internal_counters.push_back(12442);
        internal_counters.push_back(12520);
        internal_counters.push_back(12598);
        internal_counters.push_back(12676);
        internal_counters.push_back(12754);
        internal_counters.push_back(12832);
        internal_counters.push_back(12910);
        internal_counters.push_back(12988);
        internal_counters.push_back(13066);
        internal_counters.push_back(13144);
        internal_counters.push_back(13222);
        internal_counters.push_back(12060);
        internal_counters.push_back(12138);
        internal_counters.push_back(12216);
        internal_counters.push_back(12294);
        internal_counters.push_back(12372);
        internal_counters.push_back(12450);
        internal_counters.push_back(12528);
        internal_counters.push_back(12606);
        internal_counters.push_back(12684);
        internal_counters.push_back(12762);
        internal_counters.push_back(12840);
        internal_counters.push_back(12918);
        internal_counters.push_back(12996);
        internal_counters.push_back(13074);
        internal_counters.push_back(13152);
        internal_counters.push_back(13230);

        c.DefineDerivedCounter("L0CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L0 cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "be1e0578-82b8-ad7f-ba3f-3afce150937a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16450);
        internal_counters.push_back(16454);

        c.DefineDerivedCounter("L1CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Writes and atomics always miss this cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),1,0,/,-,(100),*,0,ifnotzero", "b10c589c-f7a5-b8f2-46c2-e0aed4a84105");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16955);
        internal_counters.push_back(17214);
        internal_counters.push_back(17473);
        internal_counters.push_back(17732);
        internal_counters.push_back(17991);
        internal_counters.push_back(18250);
        internal_counters.push_back(18509);
        internal_counters.push_back(18768);
        internal_counters.push_back(19027);
        internal_counters.push_back(19286);
        internal_counters.push_back(19545);
        internal_counters.push_back(19804);
        internal_counters.push_back(20063);
        internal_counters.push_back(20322);
        internal_counters.push_back(20581);
        internal_counters.push_back(20840);
        internal_counters.push_back(16995);
        internal_counters.push_back(17254);
        internal_counters.push_back(17513);
        internal_counters.push_back(17772);
        internal_counters.push_back(18031);
        internal_counters.push_back(18290);
        internal_counters.push_back(18549);
        internal_counters.push_back(18808);
        internal_counters.push_back(19067);
        internal_counters.push_back(19326);
        internal_counters.push_back(19585);
        internal_counters.push_back(19844);
        internal_counters.push_back(20103);
        internal_counters.push_back(20362);
        internal_counters.push_back(20621);
        internal_counters.push_back(20880);

        c.DefineDerivedCounter("L2CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L2 cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "7507935e-ed29-f169-ee27-9b0fa9b88f3c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5130);
        internal_counters.push_back(5366);
        internal_counters.push_back(5602);
        internal_counters.push_back(5838);
        internal_counters.push_back(6074);
        internal_counters.push_back(6310);
        internal_counters.push_back(6546);
        internal_counters.push_back(6782);
        internal_counters.push_back(7018);
        internal_counters.push_back(7254);
        internal_counters.push_back(7490);
        internal_counters.push_back(7726);
        internal_counters.push_back(7962);
        internal_counters.push_back(8198);
        internal_counters.push_back(8434);
        internal_counters.push_back(8670);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12082);
        internal_counters.push_back(12160);
        internal_counters.push_back(12238);
        internal_counters.push_back(12316);
        internal_counters.push_back(12394);
        internal_counters.push_back(12472);
        internal_counters.push_back(12550);
        internal_counters.push_back(12628);
        internal_counters.push_back(12706);
        internal_counters.push_back(12784);
        internal_counters.push_back(12862);
        internal_counters.push_back(12940);
        internal_counters.push_back(13018);
        internal_counters.push_back(13096);
        internal_counters.push_back(13174);
        internal_counters.push_back(13252);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(17040);
        internal_counters.push_back(17299);
        internal_counters.push_back(17558);
        internal_counters.push_back(17817);
        internal_counters.push_back(18076);
        internal_counters.push_back(18335);
        internal_counters.push_back(18594);
        internal_counters.push_back(18853);
        internal_counters.push_back(19112);
        internal_counters.push_back(19371);
        internal_counters.push_back(19630);
        internal_counters.push_back(19889);
        internal_counters.push_back(20148);
        internal_counters.push_back(20407);
        internal_counters.push_back(20666);
        internal_counters.push_back(20925);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24973);
        internal_counters.push_back(25485);
        internal_counters.push_back(25997);
        internal_counters.push_back(26509);
        internal_counters.push_back(27021);
        internal_counters.push_back(27533);
        internal_counters.push_back(28045);
        internal_counters.push_back(28557);
        internal_counters.push_back(1280);

        c.DefineDerivedCounter("LDSBankConflict", "LocalMemory", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,/,NUM_SIMDS,/,(100),*", "b3387100-3d5a-3235-e612-58b941683eb6");
    }
}

