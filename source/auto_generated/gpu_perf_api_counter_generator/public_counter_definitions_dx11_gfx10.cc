//==============================================================================
// Copyright (c) 2010-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for DX11 GFX10.
//==============================================================================

// clang-format off
#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_dx11_gfx10.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersDx11Gfx10(GpaDerivedCounters& c)
{
    { // Index:0
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(58892);

        c.DefineDerivedCounter("GPUTime",
                               "Timing",
                               "Time this API command took to execute on the GPU in nanoseconds from the time the previous command reached the bottom of the pipeline (BOP) to the time this command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeNanoseconds,
                               true,
                               false,
                               internal_counters,
                               "0,TS_FREQ,/,(1000000000),*",
                               "cbd338f2-de6c-7b14-92ad-ba724ca2e501");
    }
    { // Index:1
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24);
        internal_counters.push_back(0);

        c.DefineDerivedCounter("GPUBusy",
                               "Timing",
                               "The percentage of time the GPU command processor was busy.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,/,(100),*,(100),min",
                               "b1ba5363-1abc-fe66-2fdd-1fe6ee8989a0");
    }
    { // Index:2
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24);

        c.DefineDerivedCounter("GPUBusyCycles",
                               "Timing",
                               "Number of GPU cycles that the GPU command processor was busy.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "0",
                               "451cb045-23af-ac44-4603-d5832fa041d9");
    }
    { // Index:3
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(49703);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("TessellatorBusy",
                               "Timing",
                               "The percentage of time the tessellation engine is busy.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,/,(100),*",
                               "36af6c72-dcfb-8102-4fd4-ce8ddc573365");
    }
    { // Index:4
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(49703);

        c.DefineDerivedCounter("TessellatorBusyCycles",
                               "Timing",
                               "Number of GPU cycles that the tessellation engine is busy.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "0",
                               "60289dcb-7b33-46e7-26d1-8a2121605543");
    }
    { // Index:5
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(19809);
        internal_counters.push_back(20138);
        internal_counters.push_back(19826);
        internal_counters.push_back(20155);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("VsGsBusy",
                               "Timing",
                               "The percentage of time the ShaderUnit has VS or GS work to do in a VS-[GS-]PS pipeline.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,max4,(0),4,5,sum2,ifnotzero,6,/,(100),*,(100),min",
                               "969c41c7-eb0b-9706-a7a1-98f27c3af56b");
    }
    { // Index:6
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(19809);
        internal_counters.push_back(20138);
        internal_counters.push_back(19826);
        internal_counters.push_back(20155);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);

        c.DefineDerivedCounter("VsGsBusyCycles",
                               "Timing",
                               "Number of GPU cycles that the ShaderUnit has VS or GS work to do in a VS-[GS-]PS pipeline.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,max4,(0),4,5,sum2,ifnotzero",
                               "a8420bb7-6bd8-930a-9088-d73b9c039851");
    }
    { // Index:7
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(58892);
        internal_counters.push_back(19809);
        internal_counters.push_back(20138);
        internal_counters.push_back(19826);
        internal_counters.push_back(20155);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("VsGsTime",
                               "Timing",
                               "Time VS or GS are busy in nanoseconds in a VS-[GS-]PS pipeline.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeNanoseconds,
                               true,
                               false,
                               internal_counters,
                               "1,2,3,4,max4,(0),5,6,sum2,ifnotzero,7,/,(1),min,0,TS_FREQ,/,(1000000000),*,*",
                               "3ce33b11-210d-b3de-9b6c-b9f3cd04beff");
    }
    { // Index:8
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(19842);
        internal_counters.push_back(20171);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PreTessellationBusy",
                               "Timing",
                               "The percentage of time the ShaderUnit has VS and HS work to do in a pipeline that uses tessellation.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,max2,2,3,sum2,ifnotzero,4,/,(100),*,(100),min",
                               "346c7430-4666-7065-b5b7-1cb8cbb1c01c");
    }
    { // Index:9
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(19842);
        internal_counters.push_back(20171);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);

        c.DefineDerivedCounter("PreTessellationBusyCycles",
                               "Timing",
                               "Number of GPU cycles that the ShaderUnit has VS and HS work to do in a pipeline that uses tessellation.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,max2,2,3,sum2,ifnotzero",
                               "dac68e38-0e3a-9364-2674-308e63bee2d2");
    }
    { // Index:10
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(58892);
        internal_counters.push_back(19842);
        internal_counters.push_back(20171);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PreTessellationTime",
                               "Timing",
                               "Time VS and HS are busy in nanoseconds in a pipeline that uses tessellation.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeNanoseconds,
                               true,
                               false,
                               internal_counters,
                               "(0),1,2,max2,3,4,sum2,ifnotzero,5,/,(1),min,0,TS_FREQ,/,(1000000000),*,*",
                               "d5e6c54c-5ffb-b173-6118-bece61f0281c");
    }
    { // Index:11
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(19809);
        internal_counters.push_back(20138);
        internal_counters.push_back(19826);
        internal_counters.push_back(20155);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PostTessellationBusy",
                               "Timing",
                               "The percentage of time the ShaderUnit has DS or GS work to do in a pipeline that uses tessellation.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,2,3,max4,4,5,sum2,ifnotzero,6,/,(100),*,(100),min",
                               "1a275c68-9340-f358-71c6-a2648390381d");
    }
    { // Index:12
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(19809);
        internal_counters.push_back(20138);
        internal_counters.push_back(19826);
        internal_counters.push_back(20155);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);

        c.DefineDerivedCounter("PostTessellationBusyCycles",
                               "Timing",
                               "Number of GPU cycles that the ShaderUnit has DS or GS work to do in a pipeline that uses tessellation.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,2,3,max4,4,5,sum2,ifnotzero",
                               "a5ed943b-13ef-942b-56fb-6d519eeb7337");
    }
    { // Index:13
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(58892);
        internal_counters.push_back(19809);
        internal_counters.push_back(20138);
        internal_counters.push_back(19826);
        internal_counters.push_back(20155);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PostTessellationTime",
                               "Timing",
                               "Time DS or GS are busy in nanoseconds in a pipeline that uses tessellation.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeNanoseconds,
                               true,
                               false,
                               internal_counters,
                               "(0),1,2,3,4,max4,5,6,sum2,ifnotzero,7,/,(1),min,0,TS_FREQ,/,(1000000000),*,*",
                               "9f8dfa40-faee-2014-3467-2630a7d95c1e");
    }
    { // Index:14
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(19868);
        internal_counters.push_back(20197);
        internal_counters.push_back(19888);
        internal_counters.push_back(20217);
        internal_counters.push_back(19869);
        internal_counters.push_back(20198);
        internal_counters.push_back(19889);
        internal_counters.push_back(20218);
        internal_counters.push_back(19870);
        internal_counters.push_back(20199);
        internal_counters.push_back(19890);
        internal_counters.push_back(20219);
        internal_counters.push_back(19871);
        internal_counters.push_back(20200);
        internal_counters.push_back(19891);
        internal_counters.push_back(20220);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PSBusy",
                               "Timing",
                               "The percentage of time the ShaderUnit has pixel shader work to do.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "(0),0,2,ifnotzero,(0),1,3,ifnotzero,max,(0),4,6,ifnotzero,(0),5,7,ifnotzero,max,(0),8,10,ifnotzero,(0),9,11,ifnotzero,max,(0),12,14,ifnotzero,(0),13,15,ifnotzero,max,max4,16,/,(100),*,(100),min",
                               "7e772beb-d82c-bd9a-aed0-fe504d416ce5");
    }
    { // Index:15
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(19868);
        internal_counters.push_back(20197);
        internal_counters.push_back(19888);
        internal_counters.push_back(20217);
        internal_counters.push_back(19869);
        internal_counters.push_back(20198);
        internal_counters.push_back(19889);
        internal_counters.push_back(20218);
        internal_counters.push_back(19870);
        internal_counters.push_back(20199);
        internal_counters.push_back(19890);
        internal_counters.push_back(20219);
        internal_counters.push_back(19871);
        internal_counters.push_back(20200);
        internal_counters.push_back(19891);
        internal_counters.push_back(20220);

        c.DefineDerivedCounter("PSBusyCycles",
                               "Timing",
                               "Number of GPU cycles that the ShaderUnit has pixel shader work to do.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "(0),0,2,ifnotzero,(0),1,3,ifnotzero,max,(0),4,6,ifnotzero,(0),5,7,ifnotzero,max,(0),8,10,ifnotzero,(0),9,11,ifnotzero,max,(0),12,14,ifnotzero,(0),13,15,ifnotzero,max,max4",
                               "b58bea04-ce8e-2984-80f4-8aba7d4c817b");
    }
    { // Index:16
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(58892);
        internal_counters.push_back(19868);
        internal_counters.push_back(20197);
        internal_counters.push_back(19888);
        internal_counters.push_back(20217);
        internal_counters.push_back(19869);
        internal_counters.push_back(20198);
        internal_counters.push_back(19889);
        internal_counters.push_back(20218);
        internal_counters.push_back(19870);
        internal_counters.push_back(20199);
        internal_counters.push_back(19890);
        internal_counters.push_back(20219);
        internal_counters.push_back(19871);
        internal_counters.push_back(20200);
        internal_counters.push_back(19891);
        internal_counters.push_back(20220);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PSTime",
                               "Timing",
                               "Time pixel shaders are busy in nanoseconds.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeNanoseconds,
                               true,
                               false,
                               internal_counters,
                               "(0),1,3,ifnotzero,(0),2,4,ifnotzero,max,(0),5,7,ifnotzero,(0),6,8,ifnotzero,max,(0),9,11,ifnotzero,(0),10,12,ifnotzero,max,(0),13,15,ifnotzero,(0),14,16,ifnotzero,max,max4,17,/,(1),min,0,TS_FREQ,/,(1000000000),*,*",
                               "edca7694-7416-e8a6-0c5a-63a5ad5f3d74");
    }
    { // Index:17
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(19853);
        internal_counters.push_back(20182);
        internal_counters.push_back(19857);
        internal_counters.push_back(20186);
        internal_counters.push_back(19859);
        internal_counters.push_back(20188);
        internal_counters.push_back(19863);
        internal_counters.push_back(20192);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("CSBusy",
                               "Timing",
                               "The percentage of time the ShaderUnit has compute shader work to do.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,comparemax2,4,5,6,7,comparemax2,max,8,/,(100),*,(100),min",
                               "493fdd90-8d2b-a055-5e4e-2d29c3396b8c");
    }
    { // Index:18
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(19853);
        internal_counters.push_back(20182);
        internal_counters.push_back(19857);
        internal_counters.push_back(20186);
        internal_counters.push_back(19859);
        internal_counters.push_back(20188);
        internal_counters.push_back(19863);
        internal_counters.push_back(20192);

        c.DefineDerivedCounter("CSBusyCycles",
                               "Timing",
                               "Number of GPU cycles that the ShaderUnit has compute shader work to do.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,comparemax2,4,5,6,7,comparemax2,max",
                               "39bcf1b8-f6b2-4c37-f9af-0a2bb59512f9");
    }
    { // Index:19
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(58892);
        internal_counters.push_back(19853);
        internal_counters.push_back(20182);
        internal_counters.push_back(19857);
        internal_counters.push_back(20186);
        internal_counters.push_back(19859);
        internal_counters.push_back(20188);
        internal_counters.push_back(19863);
        internal_counters.push_back(20192);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("CSTime",
                               "Timing",
                               "Time compute shaders are busy in nanoseconds.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeNanoseconds,
                               true,
                               false,
                               internal_counters,
                               "1,2,3,4,comparemax2,5,6,7,8,comparemax2,max,9,/,(1),min,0,TS_FREQ,/,(1000000000),*,*",
                               "dbc24916-ecb2-7eef-8d63-7afadaaab6bc");
    }
    { // Index:20
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(49731);
        internal_counters.push_back(49667);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);

        c.DefineDerivedCounter("GSVerticesOut",
                               "VertexGeometry",
                               "The number of vertices output by the GS.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,ifnotzero,(0),2,3,sum2,ifnotzero",
                               "775b9736-319a-bd8a-48c9-68db9c91d978");
    }
    { // Index:21
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(49683);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);

        c.DefineDerivedCounter("PreTessVerticesIn",
                               "PreTessellation",
                               "The number of vertices processed by the VS and HS when using tessellation.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,2,sum2,ifnotzero",
                               "b0d4c894-2fd0-6f4f-0b07-d5369769ef2d");
    }
    { // Index:22
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(26674);
        internal_counters.push_back(27186);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);

        c.DefineDerivedCounter("PreTessVALUInstCount",
                               "PreTessellation",
                               "Average number of vector ALU instructions executed for the VS and HS in a pipeline that uses tessellation. Affected by flow control.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero",
                               "a6894a29-4213-27d4-e186-b9ca6112e3f3");
    }
    { // Index:23
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(26670);
        internal_counters.push_back(27182);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);

        c.DefineDerivedCounter("PreTessSALUInstCount",
                               "PreTessellation",
                               "Average number of scalar ALU instructions executed for the VS and HS in a pipeline that uses tessellation. Affected by flow control.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero",
                               "c6d06968-3557-fb5d-7a28-5eda098190db");
    }
    { // Index:24
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(26727);
        internal_counters.push_back(27239);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PreTessVALUBusy",
                               "PreTessellation",
                               "The percentage of GPUTime vector ALU instructions are being processed for the VS and HS in a pipeline that uses tessellation.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,NUM_SIMDS,/,4,/,(100),*,2,3,sum2,ifnotzero",
                               "72627e0a-da7e-899a-738c-69e8ba96bf42");
    }
    { // Index:25
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(26727);
        internal_counters.push_back(27239);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);

        c.DefineDerivedCounter("PreTessVALUBusyCycles",
                               "PreTessellation",
                               "Number of GPU cycles vector where ALU instructions are being processed for the VS and HS in a pipeline that uses tessellation.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,NUM_SIMDS,/,2,3,sum2,ifnotzero",
                               "2d750b51-a75e-380b-1b42-40d59f4fbdb6");
    }
    { // Index:26
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(26670);
        internal_counters.push_back(27182);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PreTessSALUBusy",
                               "PreTessellation",
                               "The percentage of GPUTime scalar ALU instructions are being processed for the VS and HS in a pipeline that uses tessellation.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,NUM_CUS,/,4,/,(100),*,2,3,sum2,ifnotzero",
                               "74e778bb-ce25-32cd-caa6-810eb44c95fa");
    }
    { // Index:27
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(26670);
        internal_counters.push_back(27182);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);

        c.DefineDerivedCounter("PreTessSALUBusyCycles",
                               "PreTessellation",
                               "Number of GPU cycles where scalar ALU instructions are being processed for the VS and HS in a pipeline that uses tessellation.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,NUM_CUS,/,2,3,sum2,ifnotzero",
                               "8aa4a036-313f-f4b0-a820-ff0a6e71b1a2");
    }
    { // Index:28
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(49677);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);

        c.DefineDerivedCounter("PostTessPrimsOut",
                               "PostTessellation",
                               "The number of primitives output by the DS and GS when using tessellation.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,2,sum2,ifnotzero",
                               "d38dabe8-1f13-ea34-d3c1-eb5783b737f1");
    }
    { // Index:29
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(22578);
        internal_counters.push_back(23090);
        internal_counters.push_back(22518);
        internal_counters.push_back(23030);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);

        c.DefineDerivedCounter("PostTessVALUInstCount",
                               "PostTessellation",
                               "Average number of vector ALU instructions executed for the DS and GS in a pipeline that uses tessellation. Affected by flow control.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,2,3,sum2,/,4,5,sum2,ifnotzero",
                               "718b7237-1371-4c85-3ad1-f12af258ba08");
    }
    { // Index:30
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(22574);
        internal_counters.push_back(23086);
        internal_counters.push_back(22518);
        internal_counters.push_back(23030);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);

        c.DefineDerivedCounter("PostTessSALUInstCount",
                               "PostTessellation",
                               "Average number of scalar ALU instructions executed for the DS and GS in a pipeline that uses tessellation. Affected by flow control.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,2,3,sum2,/,4,5,sum2,ifnotzero",
                               "546cecd8-53d4-c7b7-3b2e-f5b2db6c8282");
    }
    { // Index:31
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(22631);
        internal_counters.push_back(23143);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PostTessVALUBusy",
                               "PostTessellation",
                               "The percentage of GPUTime vector ALU instructions are being processed for the DS and GS in a pipeline that uses tessellation.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,NUM_SIMDS,/,4,/,(100),*,2,3,sum2,ifnotzero",
                               "068d1738-da17-7b6d-9d88-4013a8b27bf8");
    }
    { // Index:32
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(22631);
        internal_counters.push_back(23143);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);

        c.DefineDerivedCounter("PostTessVALUBusyCycles",
                               "PostTessellation",
                               "Number of GPU cycles vector where ALU instructions are being processed for the DS and GS in a pipeline that uses tessellation.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,NUM_SIMDS,/,2,3,sum2,ifnotzero",
                               "29951e35-e415-22e9-ea59-03955faa8973");
    }
    { // Index:33
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(22574);
        internal_counters.push_back(23086);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PostTessSALUBusy",
                               "PostTessellation",
                               "The percentage of GPUTime scalar ALU instructions are being processed for the DS and GS in a pipeline that uses tessellation.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,NUM_CUS,/,4,/,(100),*,2,3,sum2,ifnotzero",
                               "776fb8e3-1541-75e5-8a4c-28d43d39662b");
    }
    { // Index:34
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(22574);
        internal_counters.push_back(23086);
        internal_counters.push_back(19849);
        internal_counters.push_back(20178);

        c.DefineDerivedCounter("PostTessSALUBusyCycles",
                               "PostTessellation",
                               "Number of GPU cycles where scalar ALU instructions are being processed for the DS and GS in a pipeline that uses tessellation.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,NUM_CUS,/,2,3,sum2,ifnotzero",
                               "fce0317e-c679-a310-fd96-85bbb4a8b79d");
    }
    { // Index:35
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13533);
        internal_counters.push_back(13799);
        internal_counters.push_back(14065);
        internal_counters.push_back(14331);
        internal_counters.push_back(13537);
        internal_counters.push_back(13803);
        internal_counters.push_back(14069);
        internal_counters.push_back(14335);
        internal_counters.push_back(13489);
        internal_counters.push_back(13755);
        internal_counters.push_back(14021);
        internal_counters.push_back(14287);
        internal_counters.push_back(13501);
        internal_counters.push_back(13767);
        internal_counters.push_back(14033);
        internal_counters.push_back(14299);
        internal_counters.push_back(13490);
        internal_counters.push_back(13756);
        internal_counters.push_back(14022);
        internal_counters.push_back(14288);
        internal_counters.push_back(13502);
        internal_counters.push_back(13768);
        internal_counters.push_back(14034);
        internal_counters.push_back(14300);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PrimitiveAssemblyBusy",
                               "Timing",
                               "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max,24,/,(100),*,(100),min",
                               "54ac5640-c4d7-95e2-20e0-6a9fdfc07333");
    }
    { // Index:36
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13533);
        internal_counters.push_back(13799);
        internal_counters.push_back(14065);
        internal_counters.push_back(14331);
        internal_counters.push_back(13537);
        internal_counters.push_back(13803);
        internal_counters.push_back(14069);
        internal_counters.push_back(14335);
        internal_counters.push_back(13489);
        internal_counters.push_back(13755);
        internal_counters.push_back(14021);
        internal_counters.push_back(14287);
        internal_counters.push_back(13501);
        internal_counters.push_back(13767);
        internal_counters.push_back(14033);
        internal_counters.push_back(14299);
        internal_counters.push_back(13490);
        internal_counters.push_back(13756);
        internal_counters.push_back(14022);
        internal_counters.push_back(14288);
        internal_counters.push_back(13502);
        internal_counters.push_back(13768);
        internal_counters.push_back(14034);
        internal_counters.push_back(14300);

        c.DefineDerivedCounter("PrimitiveAssemblyBusyCycles",
                               "Timing",
                               "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max",
                               "99777f2d-9626-c78a-a97c-c4505eba1e5f");
    }
    { // Index:37
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13436);
        internal_counters.push_back(13702);
        internal_counters.push_back(13968);
        internal_counters.push_back(14234);

        c.DefineDerivedCounter("PrimitivesIn",
                               "PrimitiveAssembly",
                               "The number of primitives received by the hardware. This includes primitives generated by tessellation.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,sum4",
                               "a515b80d-75c3-c7d2-0d2f-d7766b4759a6");
    }
    { // Index:38
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13442);
        internal_counters.push_back(13708);
        internal_counters.push_back(13974);
        internal_counters.push_back(14240);
        internal_counters.push_back(13482);
        internal_counters.push_back(13748);
        internal_counters.push_back(14014);
        internal_counters.push_back(14280);
        internal_counters.push_back(13483);
        internal_counters.push_back(13749);
        internal_counters.push_back(14015);
        internal_counters.push_back(14281);
        internal_counters.push_back(13484);
        internal_counters.push_back(13750);
        internal_counters.push_back(14016);
        internal_counters.push_back(14282);
        internal_counters.push_back(13485);
        internal_counters.push_back(13751);
        internal_counters.push_back(14017);
        internal_counters.push_back(14283);

        c.DefineDerivedCounter("CulledPrims",
                               "PrimitiveAssembly",
                               "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,+,2,+,3,+,4,+,5,+,6,+,7,+,8,+,9,+,10,+,11,+,12,+,13,+,14,+,15,+,16,+,17,+,18,+,19,+",
                               "589bdf55-9192-280a-41c3-584bc94f2562");
    }
    { // Index:39
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13449);
        internal_counters.push_back(13715);
        internal_counters.push_back(13981);
        internal_counters.push_back(14247);

        c.DefineDerivedCounter("ClippedPrims",
                               "PrimitiveAssembly",
                               "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,sum4",
                               "5ef6f9d5-155e-5baa-163f-8359d9ea9bbf");
    }
    { // Index:40
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13537);
        internal_counters.push_back(13803);
        internal_counters.push_back(14069);
        internal_counters.push_back(14335);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PAStalledOnRasterizer",
                               "PrimitiveAssembly",
                               "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,max,2,max,3,max,4,/,(100),*",
                               "6f9f416b-53c1-0457-f88c-7b6ba8973974");
    }
    { // Index:41
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13537);
        internal_counters.push_back(13803);
        internal_counters.push_back(14069);
        internal_counters.push_back(14335);

        c.DefineDerivedCounter("PAStalledOnRasterizerCycles",
                               "PrimitiveAssembly",
                               "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "0,1,max,2,max,3,max",
                               "7a8c492a-c566-9328-6805-760dbff5c0f2");
    }
    { // Index:42
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(18920);
        internal_counters.push_back(19145);
        internal_counters.push_back(19370);
        internal_counters.push_back(19595);
        internal_counters.push_back(18925);
        internal_counters.push_back(19150);
        internal_counters.push_back(19375);
        internal_counters.push_back(19600);
        internal_counters.push_back(18930);
        internal_counters.push_back(19155);
        internal_counters.push_back(19380);
        internal_counters.push_back(19605);
        internal_counters.push_back(18935);
        internal_counters.push_back(19160);
        internal_counters.push_back(19385);
        internal_counters.push_back(19610);

        c.DefineDerivedCounter("PSPixelsOut",
                               "PixelShader",
                               "Pixels exported from shader to color buffers. Does not include killed or alpha tested pixels; if there are multiple render targets, each render target receives one export, so this will be 2 for 1 pixel written to two RTs.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16",
                               "24cba16c-baa6-6ecd-95ad-92ecb1338da1");
    }
    { // Index:43
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(18922);
        internal_counters.push_back(19147);
        internal_counters.push_back(19372);
        internal_counters.push_back(19597);
        internal_counters.push_back(18927);
        internal_counters.push_back(19152);
        internal_counters.push_back(19377);
        internal_counters.push_back(19602);
        internal_counters.push_back(18932);
        internal_counters.push_back(19157);
        internal_counters.push_back(19382);
        internal_counters.push_back(19607);
        internal_counters.push_back(18937);
        internal_counters.push_back(19162);
        internal_counters.push_back(19387);
        internal_counters.push_back(19612);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PSExportStalls",
                               "PixelShader",
                               "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*",
                               "9b4f466c-ff97-22bb-557d-84d3c4c51895");
    }
    { // Index:44
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(18922);
        internal_counters.push_back(19147);
        internal_counters.push_back(19372);
        internal_counters.push_back(19597);
        internal_counters.push_back(18927);
        internal_counters.push_back(19152);
        internal_counters.push_back(19377);
        internal_counters.push_back(19602);
        internal_counters.push_back(18932);
        internal_counters.push_back(19157);
        internal_counters.push_back(19382);
        internal_counters.push_back(19607);
        internal_counters.push_back(18937);
        internal_counters.push_back(19162);
        internal_counters.push_back(19387);
        internal_counters.push_back(19612);

        c.DefineDerivedCounter("PSExportStallsCycles",
                               "PixelShader",
                               "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16",
                               "47c72aad-64e6-0864-d533-d8e0bc27c156");
    }
    { // Index:45
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSThreadGroupsLaunched",
                               "ComputeShader",
                               "Total number of thread groups launched.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,sum4",
                               "e1e2f302-868a-1d2e-ca81-9901bbc8b58f");
    }
    { // Index:46
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(19857);
        internal_counters.push_back(20186);
        internal_counters.push_back(19863);
        internal_counters.push_back(20192);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSWavefrontsLaunched",
                               "ComputeShader",
                               "The total number of wavefronts launched for the CS.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,2,3,sum4,4,5,6,7,sum4,ifnotzero",
                               "00c49129-6ae5-f6a0-1753-4738cbe17938");
    }
    { // Index:47
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(27642);
        internal_counters.push_back(28154);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSThreadsLaunched",
                               "ComputeShader",
                               "The number of CS threads launched and processed by the hardware.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,2,3,4,5,sum4,ifnotzero",
                               "cbbbf1ba-d164-1c90-9df0-6120c1660fb1");
    }
    { // Index:48
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(27642);
        internal_counters.push_back(28154);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSThreadGroupSize",
                               "ComputeShader",
                               "The number of CS threads within each thread group.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,2,3,4,5,sum4,/,2,3,4,5,sum4,ifnotzero",
                               "8c65008a-9957-7ca6-4199-f6fe940420f6");
    }
    { // Index:49
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(27698);
        internal_counters.push_back(28210);
        internal_counters.push_back(27638);
        internal_counters.push_back(28150);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSVALUInsts",
                               "ComputeShader",
                               "The average number of vector ALU instructions executed per work-item (affected by flow control).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,2,3,sum2,/,4,5,6,7,sum4,ifnotzero",
                               "376cb1cc-5a40-9d1d-404c-f1736c0c5084");
    }
    { // Index:50
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(27716);
        internal_counters.push_back(28228);
        internal_counters.push_back(27751);
        internal_counters.push_back(28263);
        internal_counters.push_back(27639);
        internal_counters.push_back(28151);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSVALUUtilization",
                               "ComputeShader",
                               "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "(0),(0),0,1,sum2,2,3,sum2,(64),(32),4,5,sum2,ifnotzero,*,/,(100),*,2,3,sum2,ifnotzero,(100),min,6,7,8,9,sum4,ifnotzero",
                               "ae943d2a-76e1-bb68-e1e2-0e06c9031611");
    }
    { // Index:51
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(27694);
        internal_counters.push_back(28206);
        internal_counters.push_back(27638);
        internal_counters.push_back(28150);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSSALUInsts",
                               "ComputeShader",
                               "The average number of scalar ALU instructions executed per work-item (affected by flow control).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero",
                               "eb211144-8136-ff86-e8bf-4d0493a904cb");
    }
    { // Index:52
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(27703);
        internal_counters.push_back(28215);
        internal_counters.push_back(27638);
        internal_counters.push_back(28150);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSVFetchInsts",
                               "ComputeShader",
                               "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero",
                               "3e2829c0-6215-783b-c271-6d57ff2c520e");
    }
    { // Index:53
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(27695);
        internal_counters.push_back(28207);
        internal_counters.push_back(27638);
        internal_counters.push_back(28150);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSSFetchInsts",
                               "ComputeShader",
                               "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero",
                               "da09171c-6a0a-584f-fddc-dc5062d63a3e");
    }
    { // Index:54
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(27704);
        internal_counters.push_back(28216);
        internal_counters.push_back(27638);
        internal_counters.push_back(28150);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSVWriteInsts",
                               "ComputeShader",
                               "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero",
                               "43438c22-e910-b377-b767-b32902e0df0d");
    }
    { // Index:55
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(27751);
        internal_counters.push_back(28263);
        internal_counters.push_back(24);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSVALUBusy",
                               "ComputeShader",
                               "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,NUM_SIMDS,/,2,/,(100),*,3,4,5,6,sum4,ifnotzero",
                               "f1e64815-f6a8-c277-d4f9-d054b443e205");
    }
    { // Index:56
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(27751);
        internal_counters.push_back(28263);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSVALUBusyCycles",
                               "ComputeShader",
                               "Number of GPU cycles where vector ALU instructions are processed.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,NUM_SIMDS,/,2,3,4,5,sum4,ifnotzero",
                               "2d0d5852-2658-eb73-68d2-f23f7118c9c3");
    }
    { // Index:57
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(27694);
        internal_counters.push_back(28206);
        internal_counters.push_back(24);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSSALUBusy",
                               "ComputeShader",
                               "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,NUM_SIMDS,/,2,/,(100),*,3,4,5,6,sum4,ifnotzero",
                               "3fc35f4e-9882-94e3-6f5f-4e81cd97082a");
    }
    { // Index:58
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(27694);
        internal_counters.push_back(28206);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSSALUBusyCycles",
                               "ComputeShader",
                               "Number of GPU cycles where scalar ALU instructions are processed.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,NUM_SIMDS,/,2,3,4,5,sum4,ifnotzero",
                               "de58f8fc-8ed4-a799-648d-62ded7b1c4c4");
    }
    { // Index:59
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(27689);
        internal_counters.push_back(28201);
        internal_counters.push_back(27638);
        internal_counters.push_back(28150);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSGDSInsts",
                               "ComputeShader",
                               "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero",
                               "2a867f3e-4a37-ad16-55d1-f03d74707819");
    }
    { // Index:60
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(27693);
        internal_counters.push_back(28205);
        internal_counters.push_back(27638);
        internal_counters.push_back(28150);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSLDSInsts",
                               "ComputeShader",
                               "The average number of LDS read/write instructions executed per work-item (affected by flow control).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero",
                               "61b0b351-7e06-ef8e-a8e0-7a9e3200a836");
    }
    { // Index:61
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(27665);
        internal_counters.push_back(28177);
        internal_counters.push_back(27638);
        internal_counters.push_back(28150);
        internal_counters.push_back(24);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSALUStalledByLDS",
                               "ComputeShader",
                               "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,2,3,sum2,/,4,/,(100),*,5,6,7,8,sum4,ifnotzero",
                               "6dc4f1c2-bad0-c9ff-156e-883b319a752a");
    }
    { // Index:62
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(27665);
        internal_counters.push_back(28177);
        internal_counters.push_back(27638);
        internal_counters.push_back(28150);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSALUStalledByLDSCycles",
                               "ComputeShader",
                               "Number of GPU cycles each wavefronts' ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,2,3,sum2,/,4,5,6,7,sum4,ifnotzero",
                               "1d9b1104-b732-bb38-6812-876fdd9737ad");
    }
    { // Index:63
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(27919);
        internal_counters.push_back(28431);
        internal_counters.push_back(24);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSLDSBankConflict",
                               "ComputeShader",
                               "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,NUM_SIMDS,/,2,/,(100),*,3,4,5,6,sum4,ifnotzero",
                               "1065ee10-2e41-ea41-1eb3-b61b491752f4");
    }
    { // Index:64
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(27919);
        internal_counters.push_back(28431);
        internal_counters.push_back(19854);
        internal_counters.push_back(20183);
        internal_counters.push_back(19860);
        internal_counters.push_back(20189);

        c.DefineDerivedCounter("CSLDSBankConflictCycles",
                               "ComputeShader",
                               "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "(0),0,1,sum2,NUM_SIMDS,/,2,3,4,5,sum4,ifnotzero",
                               "1fd1adf3-c51e-94fd-083e-c482a0a0809e");
    }
    { // Index:65
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(28673);
        internal_counters.push_back(28899);
        internal_counters.push_back(29125);
        internal_counters.push_back(29351);
        internal_counters.push_back(29577);
        internal_counters.push_back(29803);
        internal_counters.push_back(30029);
        internal_counters.push_back(30255);
        internal_counters.push_back(30481);
        internal_counters.push_back(30707);
        internal_counters.push_back(30933);
        internal_counters.push_back(31159);
        internal_counters.push_back(31385);
        internal_counters.push_back(31611);
        internal_counters.push_back(31837);
        internal_counters.push_back(32063);
        internal_counters.push_back(32289);
        internal_counters.push_back(32515);
        internal_counters.push_back(32741);
        internal_counters.push_back(32967);
        internal_counters.push_back(33193);
        internal_counters.push_back(33419);
        internal_counters.push_back(33645);
        internal_counters.push_back(33871);
        internal_counters.push_back(34097);
        internal_counters.push_back(34323);
        internal_counters.push_back(34549);
        internal_counters.push_back(34775);
        internal_counters.push_back(35001);
        internal_counters.push_back(35227);
        internal_counters.push_back(35453);
        internal_counters.push_back(35679);
        internal_counters.push_back(35905);
        internal_counters.push_back(36131);
        internal_counters.push_back(36357);
        internal_counters.push_back(36583);
        internal_counters.push_back(36809);
        internal_counters.push_back(37035);
        internal_counters.push_back(37261);
        internal_counters.push_back(37487);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("TexUnitBusy",
                               "Timing",
                               "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,/,(100),*",
                               "36afb8d9-42fc-aafe-66c5-449542153b2c");
    }
    { // Index:66
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(28673);
        internal_counters.push_back(28899);
        internal_counters.push_back(29125);
        internal_counters.push_back(29351);
        internal_counters.push_back(29577);
        internal_counters.push_back(29803);
        internal_counters.push_back(30029);
        internal_counters.push_back(30255);
        internal_counters.push_back(30481);
        internal_counters.push_back(30707);
        internal_counters.push_back(30933);
        internal_counters.push_back(31159);
        internal_counters.push_back(31385);
        internal_counters.push_back(31611);
        internal_counters.push_back(31837);
        internal_counters.push_back(32063);
        internal_counters.push_back(32289);
        internal_counters.push_back(32515);
        internal_counters.push_back(32741);
        internal_counters.push_back(32967);
        internal_counters.push_back(33193);
        internal_counters.push_back(33419);
        internal_counters.push_back(33645);
        internal_counters.push_back(33871);
        internal_counters.push_back(34097);
        internal_counters.push_back(34323);
        internal_counters.push_back(34549);
        internal_counters.push_back(34775);
        internal_counters.push_back(35001);
        internal_counters.push_back(35227);
        internal_counters.push_back(35453);
        internal_counters.push_back(35679);
        internal_counters.push_back(35905);
        internal_counters.push_back(36131);
        internal_counters.push_back(36357);
        internal_counters.push_back(36583);
        internal_counters.push_back(36809);
        internal_counters.push_back(37035);
        internal_counters.push_back(37261);
        internal_counters.push_back(37487);

        c.DefineDerivedCounter("TexUnitBusyCycles",
                               "Timing",
                               "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40",
                               "c68761f2-248c-4f39-6528-c308b1c0807c");
    }
    { // Index:67
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(28727);
        internal_counters.push_back(28953);
        internal_counters.push_back(29179);
        internal_counters.push_back(29405);
        internal_counters.push_back(29631);
        internal_counters.push_back(29857);
        internal_counters.push_back(30083);
        internal_counters.push_back(30309);
        internal_counters.push_back(30535);
        internal_counters.push_back(30761);
        internal_counters.push_back(30987);
        internal_counters.push_back(31213);
        internal_counters.push_back(31439);
        internal_counters.push_back(31665);
        internal_counters.push_back(31891);
        internal_counters.push_back(32117);
        internal_counters.push_back(32343);
        internal_counters.push_back(32569);
        internal_counters.push_back(32795);
        internal_counters.push_back(33021);
        internal_counters.push_back(33247);
        internal_counters.push_back(33473);
        internal_counters.push_back(33699);
        internal_counters.push_back(33925);
        internal_counters.push_back(34151);
        internal_counters.push_back(34377);
        internal_counters.push_back(34603);
        internal_counters.push_back(34829);
        internal_counters.push_back(35055);
        internal_counters.push_back(35281);
        internal_counters.push_back(35507);
        internal_counters.push_back(35733);
        internal_counters.push_back(35959);
        internal_counters.push_back(36185);
        internal_counters.push_back(36411);
        internal_counters.push_back(36637);
        internal_counters.push_back(36863);
        internal_counters.push_back(37089);
        internal_counters.push_back(37315);
        internal_counters.push_back(37541);
        internal_counters.push_back(28726);
        internal_counters.push_back(28952);
        internal_counters.push_back(29178);
        internal_counters.push_back(29404);
        internal_counters.push_back(29630);
        internal_counters.push_back(29856);
        internal_counters.push_back(30082);
        internal_counters.push_back(30308);
        internal_counters.push_back(30534);
        internal_counters.push_back(30760);
        internal_counters.push_back(30986);
        internal_counters.push_back(31212);
        internal_counters.push_back(31438);
        internal_counters.push_back(31664);
        internal_counters.push_back(31890);
        internal_counters.push_back(32116);
        internal_counters.push_back(32342);
        internal_counters.push_back(32568);
        internal_counters.push_back(32794);
        internal_counters.push_back(33020);
        internal_counters.push_back(33246);
        internal_counters.push_back(33472);
        internal_counters.push_back(33698);
        internal_counters.push_back(33924);
        internal_counters.push_back(34150);
        internal_counters.push_back(34376);
        internal_counters.push_back(34602);
        internal_counters.push_back(34828);
        internal_counters.push_back(35054);
        internal_counters.push_back(35280);
        internal_counters.push_back(35506);
        internal_counters.push_back(35732);
        internal_counters.push_back(35958);
        internal_counters.push_back(36184);
        internal_counters.push_back(36410);
        internal_counters.push_back(36636);
        internal_counters.push_back(36862);
        internal_counters.push_back(37088);
        internal_counters.push_back(37314);
        internal_counters.push_back(37540);

        c.DefineDerivedCounter("TexTriFilteringPct",
                               "TextureUnit",
                               "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,+,/,(100),*",
                               "1affc3c8-b917-5c81-622b-7004527208ae");
    }
    { // Index:68
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(28727);
        internal_counters.push_back(28953);
        internal_counters.push_back(29179);
        internal_counters.push_back(29405);
        internal_counters.push_back(29631);
        internal_counters.push_back(29857);
        internal_counters.push_back(30083);
        internal_counters.push_back(30309);
        internal_counters.push_back(30535);
        internal_counters.push_back(30761);
        internal_counters.push_back(30987);
        internal_counters.push_back(31213);
        internal_counters.push_back(31439);
        internal_counters.push_back(31665);
        internal_counters.push_back(31891);
        internal_counters.push_back(32117);
        internal_counters.push_back(32343);
        internal_counters.push_back(32569);
        internal_counters.push_back(32795);
        internal_counters.push_back(33021);
        internal_counters.push_back(33247);
        internal_counters.push_back(33473);
        internal_counters.push_back(33699);
        internal_counters.push_back(33925);
        internal_counters.push_back(34151);
        internal_counters.push_back(34377);
        internal_counters.push_back(34603);
        internal_counters.push_back(34829);
        internal_counters.push_back(35055);
        internal_counters.push_back(35281);
        internal_counters.push_back(35507);
        internal_counters.push_back(35733);
        internal_counters.push_back(35959);
        internal_counters.push_back(36185);
        internal_counters.push_back(36411);
        internal_counters.push_back(36637);
        internal_counters.push_back(36863);
        internal_counters.push_back(37089);
        internal_counters.push_back(37315);
        internal_counters.push_back(37541);

        c.DefineDerivedCounter("TexTriFilteringCount",
                               "TextureUnit",
                               "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40",
                               "5785b3a1-a513-18db-4b1c-bdeef75bb2b6");
    }
    { // Index:69
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(28726);
        internal_counters.push_back(28952);
        internal_counters.push_back(29178);
        internal_counters.push_back(29404);
        internal_counters.push_back(29630);
        internal_counters.push_back(29856);
        internal_counters.push_back(30082);
        internal_counters.push_back(30308);
        internal_counters.push_back(30534);
        internal_counters.push_back(30760);
        internal_counters.push_back(30986);
        internal_counters.push_back(31212);
        internal_counters.push_back(31438);
        internal_counters.push_back(31664);
        internal_counters.push_back(31890);
        internal_counters.push_back(32116);
        internal_counters.push_back(32342);
        internal_counters.push_back(32568);
        internal_counters.push_back(32794);
        internal_counters.push_back(33020);
        internal_counters.push_back(33246);
        internal_counters.push_back(33472);
        internal_counters.push_back(33698);
        internal_counters.push_back(33924);
        internal_counters.push_back(34150);
        internal_counters.push_back(34376);
        internal_counters.push_back(34602);
        internal_counters.push_back(34828);
        internal_counters.push_back(35054);
        internal_counters.push_back(35280);
        internal_counters.push_back(35506);
        internal_counters.push_back(35732);
        internal_counters.push_back(35958);
        internal_counters.push_back(36184);
        internal_counters.push_back(36410);
        internal_counters.push_back(36636);
        internal_counters.push_back(36862);
        internal_counters.push_back(37088);
        internal_counters.push_back(37314);
        internal_counters.push_back(37540);

        c.DefineDerivedCounter("NoTexTriFilteringCount",
                               "TextureUnit",
                               "Count of pixels that did not receive trilinear filtering.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40",
                               "179da29a-81af-c06e-ce8c-a0a731ea030d");
    }
    { // Index:70
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(28729);
        internal_counters.push_back(28955);
        internal_counters.push_back(29181);
        internal_counters.push_back(29407);
        internal_counters.push_back(29633);
        internal_counters.push_back(29859);
        internal_counters.push_back(30085);
        internal_counters.push_back(30311);
        internal_counters.push_back(30537);
        internal_counters.push_back(30763);
        internal_counters.push_back(30989);
        internal_counters.push_back(31215);
        internal_counters.push_back(31441);
        internal_counters.push_back(31667);
        internal_counters.push_back(31893);
        internal_counters.push_back(32119);
        internal_counters.push_back(32345);
        internal_counters.push_back(32571);
        internal_counters.push_back(32797);
        internal_counters.push_back(33023);
        internal_counters.push_back(33249);
        internal_counters.push_back(33475);
        internal_counters.push_back(33701);
        internal_counters.push_back(33927);
        internal_counters.push_back(34153);
        internal_counters.push_back(34379);
        internal_counters.push_back(34605);
        internal_counters.push_back(34831);
        internal_counters.push_back(35057);
        internal_counters.push_back(35283);
        internal_counters.push_back(35509);
        internal_counters.push_back(35735);
        internal_counters.push_back(35961);
        internal_counters.push_back(36187);
        internal_counters.push_back(36413);
        internal_counters.push_back(36639);
        internal_counters.push_back(36865);
        internal_counters.push_back(37091);
        internal_counters.push_back(37317);
        internal_counters.push_back(37543);
        internal_counters.push_back(28728);
        internal_counters.push_back(28954);
        internal_counters.push_back(29180);
        internal_counters.push_back(29406);
        internal_counters.push_back(29632);
        internal_counters.push_back(29858);
        internal_counters.push_back(30084);
        internal_counters.push_back(30310);
        internal_counters.push_back(30536);
        internal_counters.push_back(30762);
        internal_counters.push_back(30988);
        internal_counters.push_back(31214);
        internal_counters.push_back(31440);
        internal_counters.push_back(31666);
        internal_counters.push_back(31892);
        internal_counters.push_back(32118);
        internal_counters.push_back(32344);
        internal_counters.push_back(32570);
        internal_counters.push_back(32796);
        internal_counters.push_back(33022);
        internal_counters.push_back(33248);
        internal_counters.push_back(33474);
        internal_counters.push_back(33700);
        internal_counters.push_back(33926);
        internal_counters.push_back(34152);
        internal_counters.push_back(34378);
        internal_counters.push_back(34604);
        internal_counters.push_back(34830);
        internal_counters.push_back(35056);
        internal_counters.push_back(35282);
        internal_counters.push_back(35508);
        internal_counters.push_back(35734);
        internal_counters.push_back(35960);
        internal_counters.push_back(36186);
        internal_counters.push_back(36412);
        internal_counters.push_back(36638);
        internal_counters.push_back(36864);
        internal_counters.push_back(37090);
        internal_counters.push_back(37316);
        internal_counters.push_back(37542);

        c.DefineDerivedCounter("TexVolFilteringPct",
                               "TextureUnit",
                               "Percentage of pixels that received volume filtering.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,+,/,(100),*",
                               "b5ff6bed-3178-aee4-42dd-c74391c02a2d");
    }
    { // Index:71
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(28729);
        internal_counters.push_back(28955);
        internal_counters.push_back(29181);
        internal_counters.push_back(29407);
        internal_counters.push_back(29633);
        internal_counters.push_back(29859);
        internal_counters.push_back(30085);
        internal_counters.push_back(30311);
        internal_counters.push_back(30537);
        internal_counters.push_back(30763);
        internal_counters.push_back(30989);
        internal_counters.push_back(31215);
        internal_counters.push_back(31441);
        internal_counters.push_back(31667);
        internal_counters.push_back(31893);
        internal_counters.push_back(32119);
        internal_counters.push_back(32345);
        internal_counters.push_back(32571);
        internal_counters.push_back(32797);
        internal_counters.push_back(33023);
        internal_counters.push_back(33249);
        internal_counters.push_back(33475);
        internal_counters.push_back(33701);
        internal_counters.push_back(33927);
        internal_counters.push_back(34153);
        internal_counters.push_back(34379);
        internal_counters.push_back(34605);
        internal_counters.push_back(34831);
        internal_counters.push_back(35057);
        internal_counters.push_back(35283);
        internal_counters.push_back(35509);
        internal_counters.push_back(35735);
        internal_counters.push_back(35961);
        internal_counters.push_back(36187);
        internal_counters.push_back(36413);
        internal_counters.push_back(36639);
        internal_counters.push_back(36865);
        internal_counters.push_back(37091);
        internal_counters.push_back(37317);
        internal_counters.push_back(37543);

        c.DefineDerivedCounter("TexVolFilteringCount",
                               "TextureUnit",
                               "Count of pixels that received volume filtering.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40",
                               "4bddc587-d589-8128-e18c-762eab2c871f");
    }
    { // Index:72
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(28728);
        internal_counters.push_back(28954);
        internal_counters.push_back(29180);
        internal_counters.push_back(29406);
        internal_counters.push_back(29632);
        internal_counters.push_back(29858);
        internal_counters.push_back(30084);
        internal_counters.push_back(30310);
        internal_counters.push_back(30536);
        internal_counters.push_back(30762);
        internal_counters.push_back(30988);
        internal_counters.push_back(31214);
        internal_counters.push_back(31440);
        internal_counters.push_back(31666);
        internal_counters.push_back(31892);
        internal_counters.push_back(32118);
        internal_counters.push_back(32344);
        internal_counters.push_back(32570);
        internal_counters.push_back(32796);
        internal_counters.push_back(33022);
        internal_counters.push_back(33248);
        internal_counters.push_back(33474);
        internal_counters.push_back(33700);
        internal_counters.push_back(33926);
        internal_counters.push_back(34152);
        internal_counters.push_back(34378);
        internal_counters.push_back(34604);
        internal_counters.push_back(34830);
        internal_counters.push_back(35056);
        internal_counters.push_back(35282);
        internal_counters.push_back(35508);
        internal_counters.push_back(35734);
        internal_counters.push_back(35960);
        internal_counters.push_back(36186);
        internal_counters.push_back(36412);
        internal_counters.push_back(36638);
        internal_counters.push_back(36864);
        internal_counters.push_back(37090);
        internal_counters.push_back(37316);
        internal_counters.push_back(37542);

        c.DefineDerivedCounter("NoTexVolFilteringCount",
                               "TextureUnit",
                               "Count of pixels that did not receive volume filtering.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40",
                               "9fe1a854-17c6-9d26-b2b9-80610cd5827d");
    }
    { // Index:73
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(28747);
        internal_counters.push_back(28973);
        internal_counters.push_back(29199);
        internal_counters.push_back(29425);
        internal_counters.push_back(29651);
        internal_counters.push_back(29877);
        internal_counters.push_back(30103);
        internal_counters.push_back(30329);
        internal_counters.push_back(30555);
        internal_counters.push_back(30781);
        internal_counters.push_back(31007);
        internal_counters.push_back(31233);
        internal_counters.push_back(31459);
        internal_counters.push_back(31685);
        internal_counters.push_back(31911);
        internal_counters.push_back(32137);
        internal_counters.push_back(32363);
        internal_counters.push_back(32589);
        internal_counters.push_back(32815);
        internal_counters.push_back(33041);
        internal_counters.push_back(33267);
        internal_counters.push_back(33493);
        internal_counters.push_back(33719);
        internal_counters.push_back(33945);
        internal_counters.push_back(34171);
        internal_counters.push_back(34397);
        internal_counters.push_back(34623);
        internal_counters.push_back(34849);
        internal_counters.push_back(35075);
        internal_counters.push_back(35301);
        internal_counters.push_back(35527);
        internal_counters.push_back(35753);
        internal_counters.push_back(35979);
        internal_counters.push_back(36205);
        internal_counters.push_back(36431);
        internal_counters.push_back(36657);
        internal_counters.push_back(36883);
        internal_counters.push_back(37109);
        internal_counters.push_back(37335);
        internal_counters.push_back(37561);
        internal_counters.push_back(28748);
        internal_counters.push_back(28974);
        internal_counters.push_back(29200);
        internal_counters.push_back(29426);
        internal_counters.push_back(29652);
        internal_counters.push_back(29878);
        internal_counters.push_back(30104);
        internal_counters.push_back(30330);
        internal_counters.push_back(30556);
        internal_counters.push_back(30782);
        internal_counters.push_back(31008);
        internal_counters.push_back(31234);
        internal_counters.push_back(31460);
        internal_counters.push_back(31686);
        internal_counters.push_back(31912);
        internal_counters.push_back(32138);
        internal_counters.push_back(32364);
        internal_counters.push_back(32590);
        internal_counters.push_back(32816);
        internal_counters.push_back(33042);
        internal_counters.push_back(33268);
        internal_counters.push_back(33494);
        internal_counters.push_back(33720);
        internal_counters.push_back(33946);
        internal_counters.push_back(34172);
        internal_counters.push_back(34398);
        internal_counters.push_back(34624);
        internal_counters.push_back(34850);
        internal_counters.push_back(35076);
        internal_counters.push_back(35302);
        internal_counters.push_back(35528);
        internal_counters.push_back(35754);
        internal_counters.push_back(35980);
        internal_counters.push_back(36206);
        internal_counters.push_back(36432);
        internal_counters.push_back(36658);
        internal_counters.push_back(36884);
        internal_counters.push_back(37110);
        internal_counters.push_back(37336);
        internal_counters.push_back(37562);
        internal_counters.push_back(28749);
        internal_counters.push_back(28975);
        internal_counters.push_back(29201);
        internal_counters.push_back(29427);
        internal_counters.push_back(29653);
        internal_counters.push_back(29879);
        internal_counters.push_back(30105);
        internal_counters.push_back(30331);
        internal_counters.push_back(30557);
        internal_counters.push_back(30783);
        internal_counters.push_back(31009);
        internal_counters.push_back(31235);
        internal_counters.push_back(31461);
        internal_counters.push_back(31687);
        internal_counters.push_back(31913);
        internal_counters.push_back(32139);
        internal_counters.push_back(32365);
        internal_counters.push_back(32591);
        internal_counters.push_back(32817);
        internal_counters.push_back(33043);
        internal_counters.push_back(33269);
        internal_counters.push_back(33495);
        internal_counters.push_back(33721);
        internal_counters.push_back(33947);
        internal_counters.push_back(34173);
        internal_counters.push_back(34399);
        internal_counters.push_back(34625);
        internal_counters.push_back(34851);
        internal_counters.push_back(35077);
        internal_counters.push_back(35303);
        internal_counters.push_back(35529);
        internal_counters.push_back(35755);
        internal_counters.push_back(35981);
        internal_counters.push_back(36207);
        internal_counters.push_back(36433);
        internal_counters.push_back(36659);
        internal_counters.push_back(36885);
        internal_counters.push_back(37111);
        internal_counters.push_back(37337);
        internal_counters.push_back(37563);
        internal_counters.push_back(28750);
        internal_counters.push_back(28976);
        internal_counters.push_back(29202);
        internal_counters.push_back(29428);
        internal_counters.push_back(29654);
        internal_counters.push_back(29880);
        internal_counters.push_back(30106);
        internal_counters.push_back(30332);
        internal_counters.push_back(30558);
        internal_counters.push_back(30784);
        internal_counters.push_back(31010);
        internal_counters.push_back(31236);
        internal_counters.push_back(31462);
        internal_counters.push_back(31688);
        internal_counters.push_back(31914);
        internal_counters.push_back(32140);
        internal_counters.push_back(32366);
        internal_counters.push_back(32592);
        internal_counters.push_back(32818);
        internal_counters.push_back(33044);
        internal_counters.push_back(33270);
        internal_counters.push_back(33496);
        internal_counters.push_back(33722);
        internal_counters.push_back(33948);
        internal_counters.push_back(34174);
        internal_counters.push_back(34400);
        internal_counters.push_back(34626);
        internal_counters.push_back(34852);
        internal_counters.push_back(35078);
        internal_counters.push_back(35304);
        internal_counters.push_back(35530);
        internal_counters.push_back(35756);
        internal_counters.push_back(35982);
        internal_counters.push_back(36208);
        internal_counters.push_back(36434);
        internal_counters.push_back(36660);
        internal_counters.push_back(36886);
        internal_counters.push_back(37112);
        internal_counters.push_back(37338);
        internal_counters.push_back(37564);
        internal_counters.push_back(28751);
        internal_counters.push_back(28977);
        internal_counters.push_back(29203);
        internal_counters.push_back(29429);
        internal_counters.push_back(29655);
        internal_counters.push_back(29881);
        internal_counters.push_back(30107);
        internal_counters.push_back(30333);
        internal_counters.push_back(30559);
        internal_counters.push_back(30785);
        internal_counters.push_back(31011);
        internal_counters.push_back(31237);
        internal_counters.push_back(31463);
        internal_counters.push_back(31689);
        internal_counters.push_back(31915);
        internal_counters.push_back(32141);
        internal_counters.push_back(32367);
        internal_counters.push_back(32593);
        internal_counters.push_back(32819);
        internal_counters.push_back(33045);
        internal_counters.push_back(33271);
        internal_counters.push_back(33497);
        internal_counters.push_back(33723);
        internal_counters.push_back(33949);
        internal_counters.push_back(34175);
        internal_counters.push_back(34401);
        internal_counters.push_back(34627);
        internal_counters.push_back(34853);
        internal_counters.push_back(35079);
        internal_counters.push_back(35305);
        internal_counters.push_back(35531);
        internal_counters.push_back(35757);
        internal_counters.push_back(35983);
        internal_counters.push_back(36209);
        internal_counters.push_back(36435);
        internal_counters.push_back(36661);
        internal_counters.push_back(36887);
        internal_counters.push_back(37113);
        internal_counters.push_back(37339);
        internal_counters.push_back(37565);
        internal_counters.push_back(28752);
        internal_counters.push_back(28978);
        internal_counters.push_back(29204);
        internal_counters.push_back(29430);
        internal_counters.push_back(29656);
        internal_counters.push_back(29882);
        internal_counters.push_back(30108);
        internal_counters.push_back(30334);
        internal_counters.push_back(30560);
        internal_counters.push_back(30786);
        internal_counters.push_back(31012);
        internal_counters.push_back(31238);
        internal_counters.push_back(31464);
        internal_counters.push_back(31690);
        internal_counters.push_back(31916);
        internal_counters.push_back(32142);
        internal_counters.push_back(32368);
        internal_counters.push_back(32594);
        internal_counters.push_back(32820);
        internal_counters.push_back(33046);
        internal_counters.push_back(33272);
        internal_counters.push_back(33498);
        internal_counters.push_back(33724);
        internal_counters.push_back(33950);
        internal_counters.push_back(34176);
        internal_counters.push_back(34402);
        internal_counters.push_back(34628);
        internal_counters.push_back(34854);
        internal_counters.push_back(35080);
        internal_counters.push_back(35306);
        internal_counters.push_back(35532);
        internal_counters.push_back(35758);
        internal_counters.push_back(35984);
        internal_counters.push_back(36210);
        internal_counters.push_back(36436);
        internal_counters.push_back(36662);
        internal_counters.push_back(36888);
        internal_counters.push_back(37114);
        internal_counters.push_back(37340);
        internal_counters.push_back(37566);
        internal_counters.push_back(28753);
        internal_counters.push_back(28979);
        internal_counters.push_back(29205);
        internal_counters.push_back(29431);
        internal_counters.push_back(29657);
        internal_counters.push_back(29883);
        internal_counters.push_back(30109);
        internal_counters.push_back(30335);
        internal_counters.push_back(30561);
        internal_counters.push_back(30787);
        internal_counters.push_back(31013);
        internal_counters.push_back(31239);
        internal_counters.push_back(31465);
        internal_counters.push_back(31691);
        internal_counters.push_back(31917);
        internal_counters.push_back(32143);
        internal_counters.push_back(32369);
        internal_counters.push_back(32595);
        internal_counters.push_back(32821);
        internal_counters.push_back(33047);
        internal_counters.push_back(33273);
        internal_counters.push_back(33499);
        internal_counters.push_back(33725);
        internal_counters.push_back(33951);
        internal_counters.push_back(34177);
        internal_counters.push_back(34403);
        internal_counters.push_back(34629);
        internal_counters.push_back(34855);
        internal_counters.push_back(35081);
        internal_counters.push_back(35307);
        internal_counters.push_back(35533);
        internal_counters.push_back(35759);
        internal_counters.push_back(35985);
        internal_counters.push_back(36211);
        internal_counters.push_back(36437);
        internal_counters.push_back(36663);
        internal_counters.push_back(36889);
        internal_counters.push_back(37115);
        internal_counters.push_back(37341);
        internal_counters.push_back(37567);
        internal_counters.push_back(28754);
        internal_counters.push_back(28980);
        internal_counters.push_back(29206);
        internal_counters.push_back(29432);
        internal_counters.push_back(29658);
        internal_counters.push_back(29884);
        internal_counters.push_back(30110);
        internal_counters.push_back(30336);
        internal_counters.push_back(30562);
        internal_counters.push_back(30788);
        internal_counters.push_back(31014);
        internal_counters.push_back(31240);
        internal_counters.push_back(31466);
        internal_counters.push_back(31692);
        internal_counters.push_back(31918);
        internal_counters.push_back(32144);
        internal_counters.push_back(32370);
        internal_counters.push_back(32596);
        internal_counters.push_back(32822);
        internal_counters.push_back(33048);
        internal_counters.push_back(33274);
        internal_counters.push_back(33500);
        internal_counters.push_back(33726);
        internal_counters.push_back(33952);
        internal_counters.push_back(34178);
        internal_counters.push_back(34404);
        internal_counters.push_back(34630);
        internal_counters.push_back(34856);
        internal_counters.push_back(35082);
        internal_counters.push_back(35308);
        internal_counters.push_back(35534);
        internal_counters.push_back(35760);
        internal_counters.push_back(35986);
        internal_counters.push_back(36212);
        internal_counters.push_back(36438);
        internal_counters.push_back(36664);
        internal_counters.push_back(36890);
        internal_counters.push_back(37116);
        internal_counters.push_back(37342);
        internal_counters.push_back(37568);
        internal_counters.push_back(28755);
        internal_counters.push_back(28981);
        internal_counters.push_back(29207);
        internal_counters.push_back(29433);
        internal_counters.push_back(29659);
        internal_counters.push_back(29885);
        internal_counters.push_back(30111);
        internal_counters.push_back(30337);
        internal_counters.push_back(30563);
        internal_counters.push_back(30789);
        internal_counters.push_back(31015);
        internal_counters.push_back(31241);
        internal_counters.push_back(31467);
        internal_counters.push_back(31693);
        internal_counters.push_back(31919);
        internal_counters.push_back(32145);
        internal_counters.push_back(32371);
        internal_counters.push_back(32597);
        internal_counters.push_back(32823);
        internal_counters.push_back(33049);
        internal_counters.push_back(33275);
        internal_counters.push_back(33501);
        internal_counters.push_back(33727);
        internal_counters.push_back(33953);
        internal_counters.push_back(34179);
        internal_counters.push_back(34405);
        internal_counters.push_back(34631);
        internal_counters.push_back(34857);
        internal_counters.push_back(35083);
        internal_counters.push_back(35309);
        internal_counters.push_back(35535);
        internal_counters.push_back(35761);
        internal_counters.push_back(35987);
        internal_counters.push_back(36213);
        internal_counters.push_back(36439);
        internal_counters.push_back(36665);
        internal_counters.push_back(36891);
        internal_counters.push_back(37117);
        internal_counters.push_back(37343);
        internal_counters.push_back(37569);

        c.DefineDerivedCounter("TexAveAnisotropy",
                               "TextureUnit",
                               "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,(2),40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,*,+,(4),80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,sum40,*,+,(6),120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,sum40,*,+,(8),160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,sum40,*,+,(10),200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,sum40,*,+,(12),240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,sum40,*,+,(14),280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,sum40,*,+,(16),320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,sum40,*,+,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,+,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,sum40,+,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,sum40,+,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,sum40,+,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,sum40,+,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,sum40,+,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,sum40,+,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,sum40,+,/",
                               "7ca2a2b9-a4eb-ce23-d163-59147e672396");
    }
    { // Index:74
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7560);
        internal_counters.push_back(7930);
        internal_counters.push_back(8300);
        internal_counters.push_back(8670);
        internal_counters.push_back(9040);
        internal_counters.push_back(9410);
        internal_counters.push_back(9780);
        internal_counters.push_back(10150);
        internal_counters.push_back(10520);
        internal_counters.push_back(10890);
        internal_counters.push_back(11260);
        internal_counters.push_back(11630);
        internal_counters.push_back(12000);
        internal_counters.push_back(12370);
        internal_counters.push_back(12740);
        internal_counters.push_back(13110);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("DepthStencilTestBusy",
                               "Timing",
                               "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*",
                               "6834fb52-42e8-bb50-fd48-ec2f2904e7e0");
    }
    { // Index:75
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7560);
        internal_counters.push_back(7930);
        internal_counters.push_back(8300);
        internal_counters.push_back(8670);
        internal_counters.push_back(9040);
        internal_counters.push_back(9410);
        internal_counters.push_back(9780);
        internal_counters.push_back(10150);
        internal_counters.push_back(10520);
        internal_counters.push_back(10890);
        internal_counters.push_back(11260);
        internal_counters.push_back(11630);
        internal_counters.push_back(12000);
        internal_counters.push_back(12370);
        internal_counters.push_back(12740);
        internal_counters.push_back(13110);

        c.DefineDerivedCounter("DepthStencilTestBusyCycles",
                               "Timing",
                               "Number of GPU cycles spent performing depth and stencil tests.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16",
                               "07ad48f0-49d8-87e7-1ef5-1e24ff2cef49");
    }
    { // Index:76
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7431);
        internal_counters.push_back(7801);
        internal_counters.push_back(8171);
        internal_counters.push_back(8541);
        internal_counters.push_back(8911);
        internal_counters.push_back(9281);
        internal_counters.push_back(9651);
        internal_counters.push_back(10021);
        internal_counters.push_back(10391);
        internal_counters.push_back(10761);
        internal_counters.push_back(11131);
        internal_counters.push_back(11501);
        internal_counters.push_back(11871);
        internal_counters.push_back(12241);
        internal_counters.push_back(12611);
        internal_counters.push_back(12981);
        internal_counters.push_back(7420);
        internal_counters.push_back(7790);
        internal_counters.push_back(8160);
        internal_counters.push_back(8530);
        internal_counters.push_back(8900);
        internal_counters.push_back(9270);
        internal_counters.push_back(9640);
        internal_counters.push_back(10010);
        internal_counters.push_back(10380);
        internal_counters.push_back(10750);
        internal_counters.push_back(11120);
        internal_counters.push_back(11490);
        internal_counters.push_back(11860);
        internal_counters.push_back(12230);
        internal_counters.push_back(12600);
        internal_counters.push_back(12970);

        c.DefineDerivedCounter("HiZTilesAccepted",
                               "DepthAndStencil",
                               "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,-,(0),max,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*",
                               "56176f45-d7ff-813d-4f05-3b2f046067e7");
    }
    { // Index:77
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7420);
        internal_counters.push_back(7790);
        internal_counters.push_back(8160);
        internal_counters.push_back(8530);
        internal_counters.push_back(8900);
        internal_counters.push_back(9270);
        internal_counters.push_back(9640);
        internal_counters.push_back(10010);
        internal_counters.push_back(10380);
        internal_counters.push_back(10750);
        internal_counters.push_back(11120);
        internal_counters.push_back(11490);
        internal_counters.push_back(11860);
        internal_counters.push_back(12230);
        internal_counters.push_back(12600);
        internal_counters.push_back(12970);
        internal_counters.push_back(7431);
        internal_counters.push_back(7801);
        internal_counters.push_back(8171);
        internal_counters.push_back(8541);
        internal_counters.push_back(8911);
        internal_counters.push_back(9281);
        internal_counters.push_back(9651);
        internal_counters.push_back(10021);
        internal_counters.push_back(10391);
        internal_counters.push_back(10761);
        internal_counters.push_back(11131);
        internal_counters.push_back(11501);
        internal_counters.push_back(11871);
        internal_counters.push_back(12241);
        internal_counters.push_back(12611);
        internal_counters.push_back(12981);

        c.DefineDerivedCounter("HiZTilesAcceptedCount",
                               "DepthAndStencil",
                               "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(0),max",
                               "95d4e3f6-b2f0-f26e-8423-aacdfaf79ea3");
    }
    { // Index:78
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7431);
        internal_counters.push_back(7801);
        internal_counters.push_back(8171);
        internal_counters.push_back(8541);
        internal_counters.push_back(8911);
        internal_counters.push_back(9281);
        internal_counters.push_back(9651);
        internal_counters.push_back(10021);
        internal_counters.push_back(10391);
        internal_counters.push_back(10761);
        internal_counters.push_back(11131);
        internal_counters.push_back(11501);
        internal_counters.push_back(11871);
        internal_counters.push_back(12241);
        internal_counters.push_back(12611);
        internal_counters.push_back(12981);

        c.DefineDerivedCounter("HiZTilesRejectedCount",
                               "DepthAndStencil",
                               "Count of tiles not accepted by HiZ.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16",
                               "156ba142-7eeb-aa6e-a00a-f8aea4e41e0b");
    }
    { // Index:79
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7420);
        internal_counters.push_back(7790);
        internal_counters.push_back(8160);
        internal_counters.push_back(8530);
        internal_counters.push_back(8900);
        internal_counters.push_back(9270);
        internal_counters.push_back(9640);
        internal_counters.push_back(10010);
        internal_counters.push_back(10380);
        internal_counters.push_back(10750);
        internal_counters.push_back(11120);
        internal_counters.push_back(11490);
        internal_counters.push_back(11860);
        internal_counters.push_back(12230);
        internal_counters.push_back(12600);
        internal_counters.push_back(12970);
        internal_counters.push_back(7444);
        internal_counters.push_back(7814);
        internal_counters.push_back(8184);
        internal_counters.push_back(8554);
        internal_counters.push_back(8924);
        internal_counters.push_back(9294);
        internal_counters.push_back(9664);
        internal_counters.push_back(10034);
        internal_counters.push_back(10404);
        internal_counters.push_back(10774);
        internal_counters.push_back(11144);
        internal_counters.push_back(11514);
        internal_counters.push_back(11884);
        internal_counters.push_back(12254);
        internal_counters.push_back(12624);
        internal_counters.push_back(12994);

        c.DefineDerivedCounter("PreZTilesDetailCulled",
                               "DepthAndStencil",
                               "Percentage of tiles rejected because the associated prim had no contributing area.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*",
                               "cad7f54d-a044-7574-c472-6f2065cbeeac");
    }
    { // Index:80
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7444);
        internal_counters.push_back(7814);
        internal_counters.push_back(8184);
        internal_counters.push_back(8554);
        internal_counters.push_back(8924);
        internal_counters.push_back(9294);
        internal_counters.push_back(9664);
        internal_counters.push_back(10034);
        internal_counters.push_back(10404);
        internal_counters.push_back(10774);
        internal_counters.push_back(11144);
        internal_counters.push_back(11514);
        internal_counters.push_back(11884);
        internal_counters.push_back(12254);
        internal_counters.push_back(12624);
        internal_counters.push_back(12994);

        c.DefineDerivedCounter("PreZTilesDetailCulledCount",
                               "DepthAndStencil",
                               "Count of tiles rejected because the associated primitive had no contributing area.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16",
                               "49262c8a-b1e6-90dd-f096-0fc4921715e9");
    }
    { // Index:81
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7420);
        internal_counters.push_back(7790);
        internal_counters.push_back(8160);
        internal_counters.push_back(8530);
        internal_counters.push_back(8900);
        internal_counters.push_back(9270);
        internal_counters.push_back(9640);
        internal_counters.push_back(10010);
        internal_counters.push_back(10380);
        internal_counters.push_back(10750);
        internal_counters.push_back(11120);
        internal_counters.push_back(11490);
        internal_counters.push_back(11860);
        internal_counters.push_back(12230);
        internal_counters.push_back(12600);
        internal_counters.push_back(12970);

        c.DefineDerivedCounter("PreZTilesDetailSurvivingCount",
                               "DepthAndStencil",
                               "Count of tiles surviving because the associated primitive had contributing area.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16",
                               "f803eaa4-bbed-bd39-775f-a64df92e2c08");
    }
    { // Index:82
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14651);
        internal_counters.push_back(15203);
        internal_counters.push_back(15755);
        internal_counters.push_back(16307);
        internal_counters.push_back(16859);
        internal_counters.push_back(17411);
        internal_counters.push_back(17963);
        internal_counters.push_back(18515);
        internal_counters.push_back(14652);
        internal_counters.push_back(15204);
        internal_counters.push_back(15756);
        internal_counters.push_back(16308);
        internal_counters.push_back(16860);
        internal_counters.push_back(17412);
        internal_counters.push_back(17964);
        internal_counters.push_back(18516);
        internal_counters.push_back(14653);
        internal_counters.push_back(15205);
        internal_counters.push_back(15757);
        internal_counters.push_back(16309);
        internal_counters.push_back(16861);
        internal_counters.push_back(17413);
        internal_counters.push_back(17965);
        internal_counters.push_back(18517);
        internal_counters.push_back(14654);
        internal_counters.push_back(15206);
        internal_counters.push_back(15758);
        internal_counters.push_back(16310);
        internal_counters.push_back(16862);
        internal_counters.push_back(17414);
        internal_counters.push_back(17966);
        internal_counters.push_back(18518);
        internal_counters.push_back(14727);
        internal_counters.push_back(15279);
        internal_counters.push_back(15831);
        internal_counters.push_back(16383);
        internal_counters.push_back(16935);
        internal_counters.push_back(17487);
        internal_counters.push_back(18039);
        internal_counters.push_back(18591);
        internal_counters.push_back(14728);
        internal_counters.push_back(15280);
        internal_counters.push_back(15832);
        internal_counters.push_back(16384);
        internal_counters.push_back(16936);
        internal_counters.push_back(17488);
        internal_counters.push_back(18040);
        internal_counters.push_back(18592);
        internal_counters.push_back(14729);
        internal_counters.push_back(15281);
        internal_counters.push_back(15833);
        internal_counters.push_back(16385);
        internal_counters.push_back(16937);
        internal_counters.push_back(17489);
        internal_counters.push_back(18041);
        internal_counters.push_back(18593);
        internal_counters.push_back(14730);
        internal_counters.push_back(15282);
        internal_counters.push_back(15834);
        internal_counters.push_back(16386);
        internal_counters.push_back(16938);
        internal_counters.push_back(17490);
        internal_counters.push_back(18042);
        internal_counters.push_back(18594);

        c.DefineDerivedCounter("HiZQuadsCulled",
                               "DepthAndStencil",
                               "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum32,-,(0),max,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,/,(100),*",
                               "fa0e319b-5573-6d34-5bab-904769925036");
    }
    { // Index:83
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14651);
        internal_counters.push_back(15203);
        internal_counters.push_back(15755);
        internal_counters.push_back(16307);
        internal_counters.push_back(16859);
        internal_counters.push_back(17411);
        internal_counters.push_back(17963);
        internal_counters.push_back(18515);
        internal_counters.push_back(14652);
        internal_counters.push_back(15204);
        internal_counters.push_back(15756);
        internal_counters.push_back(16308);
        internal_counters.push_back(16860);
        internal_counters.push_back(17412);
        internal_counters.push_back(17964);
        internal_counters.push_back(18516);
        internal_counters.push_back(14653);
        internal_counters.push_back(15205);
        internal_counters.push_back(15757);
        internal_counters.push_back(16309);
        internal_counters.push_back(16861);
        internal_counters.push_back(17413);
        internal_counters.push_back(17965);
        internal_counters.push_back(18517);
        internal_counters.push_back(14654);
        internal_counters.push_back(15206);
        internal_counters.push_back(15758);
        internal_counters.push_back(16310);
        internal_counters.push_back(16862);
        internal_counters.push_back(17414);
        internal_counters.push_back(17966);
        internal_counters.push_back(18518);
        internal_counters.push_back(14727);
        internal_counters.push_back(15279);
        internal_counters.push_back(15831);
        internal_counters.push_back(16383);
        internal_counters.push_back(16935);
        internal_counters.push_back(17487);
        internal_counters.push_back(18039);
        internal_counters.push_back(18591);
        internal_counters.push_back(14728);
        internal_counters.push_back(15280);
        internal_counters.push_back(15832);
        internal_counters.push_back(16384);
        internal_counters.push_back(16936);
        internal_counters.push_back(17488);
        internal_counters.push_back(18040);
        internal_counters.push_back(18592);
        internal_counters.push_back(14729);
        internal_counters.push_back(15281);
        internal_counters.push_back(15833);
        internal_counters.push_back(16385);
        internal_counters.push_back(16937);
        internal_counters.push_back(17489);
        internal_counters.push_back(18041);
        internal_counters.push_back(18593);
        internal_counters.push_back(14730);
        internal_counters.push_back(15282);
        internal_counters.push_back(15834);
        internal_counters.push_back(16386);
        internal_counters.push_back(16938);
        internal_counters.push_back(17490);
        internal_counters.push_back(18042);
        internal_counters.push_back(18594);

        c.DefineDerivedCounter("HiZQuadsCulledCount",
                               "DepthAndStencil",
                               "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum32,-,(0),max",
                               "73b0b39d-6df2-3e24-0b5c-7cb0ac8b6f39");
    }
    { // Index:84
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14727);
        internal_counters.push_back(15279);
        internal_counters.push_back(15831);
        internal_counters.push_back(16383);
        internal_counters.push_back(16935);
        internal_counters.push_back(17487);
        internal_counters.push_back(18039);
        internal_counters.push_back(18591);
        internal_counters.push_back(14728);
        internal_counters.push_back(15280);
        internal_counters.push_back(15832);
        internal_counters.push_back(16384);
        internal_counters.push_back(16936);
        internal_counters.push_back(17488);
        internal_counters.push_back(18040);
        internal_counters.push_back(18592);
        internal_counters.push_back(14729);
        internal_counters.push_back(15281);
        internal_counters.push_back(15833);
        internal_counters.push_back(16385);
        internal_counters.push_back(16937);
        internal_counters.push_back(17489);
        internal_counters.push_back(18041);
        internal_counters.push_back(18593);
        internal_counters.push_back(14730);
        internal_counters.push_back(15282);
        internal_counters.push_back(15834);
        internal_counters.push_back(16386);
        internal_counters.push_back(16938);
        internal_counters.push_back(17490);
        internal_counters.push_back(18042);
        internal_counters.push_back(18594);

        c.DefineDerivedCounter("HiZQuadsAcceptedCount",
                               "DepthAndStencil",
                               "Count of quads that did continue on in the pipeline after HiZ.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32",
                               "59049ad9-42b5-c7cb-3616-6a8f6a8e4894");
    }
    { // Index:85
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14727);
        internal_counters.push_back(15279);
        internal_counters.push_back(15831);
        internal_counters.push_back(16383);
        internal_counters.push_back(16935);
        internal_counters.push_back(17487);
        internal_counters.push_back(18039);
        internal_counters.push_back(18591);
        internal_counters.push_back(14728);
        internal_counters.push_back(15280);
        internal_counters.push_back(15832);
        internal_counters.push_back(16384);
        internal_counters.push_back(16936);
        internal_counters.push_back(17488);
        internal_counters.push_back(18040);
        internal_counters.push_back(18592);
        internal_counters.push_back(14729);
        internal_counters.push_back(15281);
        internal_counters.push_back(15833);
        internal_counters.push_back(16385);
        internal_counters.push_back(16937);
        internal_counters.push_back(17489);
        internal_counters.push_back(18041);
        internal_counters.push_back(18593);
        internal_counters.push_back(14730);
        internal_counters.push_back(15282);
        internal_counters.push_back(15834);
        internal_counters.push_back(16386);
        internal_counters.push_back(16938);
        internal_counters.push_back(17490);
        internal_counters.push_back(18042);
        internal_counters.push_back(18594);
        internal_counters.push_back(14751);
        internal_counters.push_back(15303);
        internal_counters.push_back(15855);
        internal_counters.push_back(16407);
        internal_counters.push_back(16959);
        internal_counters.push_back(17511);
        internal_counters.push_back(18063);
        internal_counters.push_back(18615);
        internal_counters.push_back(14651);
        internal_counters.push_back(15203);
        internal_counters.push_back(15755);
        internal_counters.push_back(16307);
        internal_counters.push_back(16859);
        internal_counters.push_back(17411);
        internal_counters.push_back(17963);
        internal_counters.push_back(18515);
        internal_counters.push_back(14652);
        internal_counters.push_back(15204);
        internal_counters.push_back(15756);
        internal_counters.push_back(16308);
        internal_counters.push_back(16860);
        internal_counters.push_back(17412);
        internal_counters.push_back(17964);
        internal_counters.push_back(18516);
        internal_counters.push_back(14653);
        internal_counters.push_back(15205);
        internal_counters.push_back(15757);
        internal_counters.push_back(16309);
        internal_counters.push_back(16861);
        internal_counters.push_back(17413);
        internal_counters.push_back(17965);
        internal_counters.push_back(18517);
        internal_counters.push_back(14654);
        internal_counters.push_back(15206);
        internal_counters.push_back(15758);
        internal_counters.push_back(16310);
        internal_counters.push_back(16862);
        internal_counters.push_back(17414);
        internal_counters.push_back(17966);
        internal_counters.push_back(18518);

        c.DefineDerivedCounter("PreZQuadsCulled",
                               "DepthAndStencil",
                               "Percentage of quads rejected based on the detailZ and earlyZ tests.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,32,33,34,35,36,37,38,39,sum8,-,(0),max,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,sum32,/,(100),*",
                               "4e77547b-ec55-5663-f034-af59be66d77d");
    }
    { // Index:86
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14727);
        internal_counters.push_back(15279);
        internal_counters.push_back(15831);
        internal_counters.push_back(16383);
        internal_counters.push_back(16935);
        internal_counters.push_back(17487);
        internal_counters.push_back(18039);
        internal_counters.push_back(18591);
        internal_counters.push_back(14728);
        internal_counters.push_back(15280);
        internal_counters.push_back(15832);
        internal_counters.push_back(16384);
        internal_counters.push_back(16936);
        internal_counters.push_back(17488);
        internal_counters.push_back(18040);
        internal_counters.push_back(18592);
        internal_counters.push_back(14729);
        internal_counters.push_back(15281);
        internal_counters.push_back(15833);
        internal_counters.push_back(16385);
        internal_counters.push_back(16937);
        internal_counters.push_back(17489);
        internal_counters.push_back(18041);
        internal_counters.push_back(18593);
        internal_counters.push_back(14730);
        internal_counters.push_back(15282);
        internal_counters.push_back(15834);
        internal_counters.push_back(16386);
        internal_counters.push_back(16938);
        internal_counters.push_back(17490);
        internal_counters.push_back(18042);
        internal_counters.push_back(18594);
        internal_counters.push_back(14751);
        internal_counters.push_back(15303);
        internal_counters.push_back(15855);
        internal_counters.push_back(16407);
        internal_counters.push_back(16959);
        internal_counters.push_back(17511);
        internal_counters.push_back(18063);
        internal_counters.push_back(18615);

        c.DefineDerivedCounter("PreZQuadsCulledCount",
                               "DepthAndStencil",
                               "Count of quads rejected based on the detailZ and earlyZ tests.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,32,33,34,35,36,37,38,39,sum8,-,(0),max",
                               "1bf169e6-9304-834e-df5f-0c44d7890a08");
    }
    { // Index:87
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14751);
        internal_counters.push_back(15303);
        internal_counters.push_back(15855);
        internal_counters.push_back(16407);
        internal_counters.push_back(16959);
        internal_counters.push_back(17511);
        internal_counters.push_back(18063);
        internal_counters.push_back(18615);

        c.DefineDerivedCounter("PreZQuadsSurvivingCount",
                               "DepthAndStencil",
                               "Count of quads surviving detailZ and earlyZ tests.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,sum8",
                               "50e25e51-3713-89cb-7f92-559cde5e5532");
    }
    { // Index:88
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14751);
        internal_counters.push_back(15303);
        internal_counters.push_back(15855);
        internal_counters.push_back(16407);
        internal_counters.push_back(16959);
        internal_counters.push_back(17511);
        internal_counters.push_back(18063);
        internal_counters.push_back(18615);
        internal_counters.push_back(14651);
        internal_counters.push_back(15203);
        internal_counters.push_back(15755);
        internal_counters.push_back(16307);
        internal_counters.push_back(16859);
        internal_counters.push_back(17411);
        internal_counters.push_back(17963);
        internal_counters.push_back(18515);
        internal_counters.push_back(14652);
        internal_counters.push_back(15204);
        internal_counters.push_back(15756);
        internal_counters.push_back(16308);
        internal_counters.push_back(16860);
        internal_counters.push_back(17412);
        internal_counters.push_back(17964);
        internal_counters.push_back(18516);
        internal_counters.push_back(14653);
        internal_counters.push_back(15205);
        internal_counters.push_back(15757);
        internal_counters.push_back(16309);
        internal_counters.push_back(16861);
        internal_counters.push_back(17413);
        internal_counters.push_back(17965);
        internal_counters.push_back(18517);
        internal_counters.push_back(14654);
        internal_counters.push_back(15206);
        internal_counters.push_back(15758);
        internal_counters.push_back(16310);
        internal_counters.push_back(16862);
        internal_counters.push_back(17414);
        internal_counters.push_back(17966);
        internal_counters.push_back(18518);

        c.DefineDerivedCounter("PostZQuads",
                               "DepthAndStencil",
                               "Percentage of quads for which the pixel shader will run and may be postZ tested.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum32,/,(100),*",
                               "58f0d34b-eeb8-e8db-abce-cb72584144be");
    }
    { // Index:89
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14751);
        internal_counters.push_back(15303);
        internal_counters.push_back(15855);
        internal_counters.push_back(16407);
        internal_counters.push_back(16959);
        internal_counters.push_back(17511);
        internal_counters.push_back(18063);
        internal_counters.push_back(18615);

        c.DefineDerivedCounter("PostZQuadCount",
                               "DepthAndStencil",
                               "Count of quads for which the pixel shader will run and may be postZ tested.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,sum8",
                               "08404526-ce35-939b-34c8-a7a35a0ff4d6");
    }
    { // Index:90
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7593);
        internal_counters.push_back(7963);
        internal_counters.push_back(8333);
        internal_counters.push_back(8703);
        internal_counters.push_back(9073);
        internal_counters.push_back(9443);
        internal_counters.push_back(9813);
        internal_counters.push_back(10183);
        internal_counters.push_back(10553);
        internal_counters.push_back(10923);
        internal_counters.push_back(11293);
        internal_counters.push_back(11663);
        internal_counters.push_back(12033);
        internal_counters.push_back(12403);
        internal_counters.push_back(12773);
        internal_counters.push_back(13143);

        c.DefineDerivedCounter("PreZSamplesPassing",
                               "DepthAndStencil",
                               "Number of samples tested for Z before shading and passed.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16",
                               "3bfe6c4d-7422-ca03-7ea5-e67ff1a00136");
    }
    { // Index:91
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7595);
        internal_counters.push_back(7965);
        internal_counters.push_back(8335);
        internal_counters.push_back(8705);
        internal_counters.push_back(9075);
        internal_counters.push_back(9445);
        internal_counters.push_back(9815);
        internal_counters.push_back(10185);
        internal_counters.push_back(10555);
        internal_counters.push_back(10925);
        internal_counters.push_back(11295);
        internal_counters.push_back(11665);
        internal_counters.push_back(12035);
        internal_counters.push_back(12405);
        internal_counters.push_back(12775);
        internal_counters.push_back(13145);

        c.DefineDerivedCounter("PreZSamplesFailingS",
                               "DepthAndStencil",
                               "Number of samples tested for Z before shading and failed stencil test.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16",
                               "df7f705e-5162-d3b5-da8b-63466cf9c4e5");
    }
    { // Index:92
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7594);
        internal_counters.push_back(7964);
        internal_counters.push_back(8334);
        internal_counters.push_back(8704);
        internal_counters.push_back(9074);
        internal_counters.push_back(9444);
        internal_counters.push_back(9814);
        internal_counters.push_back(10184);
        internal_counters.push_back(10554);
        internal_counters.push_back(10924);
        internal_counters.push_back(11294);
        internal_counters.push_back(11664);
        internal_counters.push_back(12034);
        internal_counters.push_back(12404);
        internal_counters.push_back(12774);
        internal_counters.push_back(13144);

        c.DefineDerivedCounter("PreZSamplesFailingZ",
                               "DepthAndStencil",
                               "Number of samples tested for Z before shading and failed Z test.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16",
                               "4484e950-f7a4-3800-bc74-78dd297f017e");
    }
    { // Index:93
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7590);
        internal_counters.push_back(7960);
        internal_counters.push_back(8330);
        internal_counters.push_back(8700);
        internal_counters.push_back(9070);
        internal_counters.push_back(9440);
        internal_counters.push_back(9810);
        internal_counters.push_back(10180);
        internal_counters.push_back(10550);
        internal_counters.push_back(10920);
        internal_counters.push_back(11290);
        internal_counters.push_back(11660);
        internal_counters.push_back(12030);
        internal_counters.push_back(12400);
        internal_counters.push_back(12770);
        internal_counters.push_back(13140);

        c.DefineDerivedCounter("PostZSamplesPassing",
                               "DepthAndStencil",
                               "Number of samples tested for Z after shading and passed.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16",
                               "4995d5d6-2330-b986-508b-fae24856f44c");
    }
    { // Index:94
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7592);
        internal_counters.push_back(7962);
        internal_counters.push_back(8332);
        internal_counters.push_back(8702);
        internal_counters.push_back(9072);
        internal_counters.push_back(9442);
        internal_counters.push_back(9812);
        internal_counters.push_back(10182);
        internal_counters.push_back(10552);
        internal_counters.push_back(10922);
        internal_counters.push_back(11292);
        internal_counters.push_back(11662);
        internal_counters.push_back(12032);
        internal_counters.push_back(12402);
        internal_counters.push_back(12772);
        internal_counters.push_back(13142);

        c.DefineDerivedCounter("PostZSamplesFailingS",
                               "DepthAndStencil",
                               "Number of samples tested for Z after shading and failed stencil test.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16",
                               "ae558af4-f4be-3dd4-7316-b2c4dcf0def8");
    }
    { // Index:95
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7591);
        internal_counters.push_back(7961);
        internal_counters.push_back(8331);
        internal_counters.push_back(8701);
        internal_counters.push_back(9071);
        internal_counters.push_back(9441);
        internal_counters.push_back(9811);
        internal_counters.push_back(10181);
        internal_counters.push_back(10551);
        internal_counters.push_back(10921);
        internal_counters.push_back(11291);
        internal_counters.push_back(11661);
        internal_counters.push_back(12031);
        internal_counters.push_back(12401);
        internal_counters.push_back(12771);
        internal_counters.push_back(13141);

        c.DefineDerivedCounter("PostZSamplesFailingZ",
                               "DepthAndStencil",
                               "Number of samples tested for Z after shading and failed Z test.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16",
                               "b3684c94-814a-c695-c85d-a5b6ab798b35");
    }
    { // Index:96
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7462);
        internal_counters.push_back(7832);
        internal_counters.push_back(8202);
        internal_counters.push_back(8572);
        internal_counters.push_back(8942);
        internal_counters.push_back(9312);
        internal_counters.push_back(9682);
        internal_counters.push_back(10052);
        internal_counters.push_back(10422);
        internal_counters.push_back(10792);
        internal_counters.push_back(11162);
        internal_counters.push_back(11532);
        internal_counters.push_back(11902);
        internal_counters.push_back(12272);
        internal_counters.push_back(12642);
        internal_counters.push_back(13012);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("ZUnitStalled",
                               "DepthAndStencil",
                               "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*",
                               "5e86c3ad-1726-3157-1d01-7ed188bf854d");
    }
    { // Index:97
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7462);
        internal_counters.push_back(7832);
        internal_counters.push_back(8202);
        internal_counters.push_back(8572);
        internal_counters.push_back(8942);
        internal_counters.push_back(9312);
        internal_counters.push_back(9682);
        internal_counters.push_back(10052);
        internal_counters.push_back(10422);
        internal_counters.push_back(10792);
        internal_counters.push_back(11162);
        internal_counters.push_back(11532);
        internal_counters.push_back(11902);
        internal_counters.push_back(12272);
        internal_counters.push_back(12642);
        internal_counters.push_back(13012);

        c.DefineDerivedCounter("ZUnitStalledCycles",
                               "DepthAndStencil",
                               "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16",
                               "4351fa7f-6737-2c3e-3ffb-b3addbdceedd");
    }
    { // Index:98
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7464);
        internal_counters.push_back(7834);
        internal_counters.push_back(8204);
        internal_counters.push_back(8574);
        internal_counters.push_back(8944);
        internal_counters.push_back(9314);
        internal_counters.push_back(9684);
        internal_counters.push_back(10054);
        internal_counters.push_back(10424);
        internal_counters.push_back(10794);
        internal_counters.push_back(11164);
        internal_counters.push_back(11534);
        internal_counters.push_back(11904);
        internal_counters.push_back(12274);
        internal_counters.push_back(12644);
        internal_counters.push_back(13014);
        internal_counters.push_back(7471);
        internal_counters.push_back(7841);
        internal_counters.push_back(8211);
        internal_counters.push_back(8581);
        internal_counters.push_back(8951);
        internal_counters.push_back(9321);
        internal_counters.push_back(9691);
        internal_counters.push_back(10061);
        internal_counters.push_back(10431);
        internal_counters.push_back(10801);
        internal_counters.push_back(11171);
        internal_counters.push_back(11541);
        internal_counters.push_back(11911);
        internal_counters.push_back(12281);
        internal_counters.push_back(12651);
        internal_counters.push_back(13021);

        c.DefineDerivedCounter("DBMemRead",
                               "DepthAndStencil",
                               "Number of bytes read from the depth buffer.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeBytes,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(256),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+",
                               "dcdb4ee7-bd50-00f7-c028-9e5f4ce888c0");
    }
    { // Index:99
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7476);
        internal_counters.push_back(7846);
        internal_counters.push_back(8216);
        internal_counters.push_back(8586);
        internal_counters.push_back(8956);
        internal_counters.push_back(9326);
        internal_counters.push_back(9696);
        internal_counters.push_back(10066);
        internal_counters.push_back(10436);
        internal_counters.push_back(10806);
        internal_counters.push_back(11176);
        internal_counters.push_back(11546);
        internal_counters.push_back(11916);
        internal_counters.push_back(12286);
        internal_counters.push_back(12656);
        internal_counters.push_back(13026);
        internal_counters.push_back(7479);
        internal_counters.push_back(7849);
        internal_counters.push_back(8219);
        internal_counters.push_back(8589);
        internal_counters.push_back(8959);
        internal_counters.push_back(9329);
        internal_counters.push_back(9699);
        internal_counters.push_back(10069);
        internal_counters.push_back(10439);
        internal_counters.push_back(10809);
        internal_counters.push_back(11179);
        internal_counters.push_back(11549);
        internal_counters.push_back(11919);
        internal_counters.push_back(12289);
        internal_counters.push_back(12659);
        internal_counters.push_back(13029);

        c.DefineDerivedCounter("DBMemWritten",
                               "DepthAndStencil",
                               "Number of bytes written to the depth buffer.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeBytes,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+",
                               "de5717f8-8a49-ee44-4645-10de51b37dcf");
    }
    { // Index:100
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(168);
        internal_counters.push_back(629);
        internal_counters.push_back(1090);
        internal_counters.push_back(1551);
        internal_counters.push_back(2012);
        internal_counters.push_back(2473);
        internal_counters.push_back(2934);
        internal_counters.push_back(3395);
        internal_counters.push_back(3856);
        internal_counters.push_back(4317);
        internal_counters.push_back(4778);
        internal_counters.push_back(5239);
        internal_counters.push_back(5700);
        internal_counters.push_back(6161);
        internal_counters.push_back(6622);
        internal_counters.push_back(7083);

        c.DefineDerivedCounter("CBMemRead",
                               "ColorBuffer",
                               "Number of bytes read from the color buffer.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeBytes,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*",
                               "84b531d8-a1f8-7f49-7c27-7bc97801f1e6");
    }
    { // Index:101
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(299);
        internal_counters.push_back(760);
        internal_counters.push_back(1221);
        internal_counters.push_back(1682);
        internal_counters.push_back(2143);
        internal_counters.push_back(2604);
        internal_counters.push_back(3065);
        internal_counters.push_back(3526);
        internal_counters.push_back(3987);
        internal_counters.push_back(4448);
        internal_counters.push_back(4909);
        internal_counters.push_back(5370);
        internal_counters.push_back(5831);
        internal_counters.push_back(6292);
        internal_counters.push_back(6753);
        internal_counters.push_back(7214);
        internal_counters.push_back(166);
        internal_counters.push_back(627);
        internal_counters.push_back(1088);
        internal_counters.push_back(1549);
        internal_counters.push_back(2010);
        internal_counters.push_back(2471);
        internal_counters.push_back(2932);
        internal_counters.push_back(3393);
        internal_counters.push_back(3854);
        internal_counters.push_back(4315);
        internal_counters.push_back(4776);
        internal_counters.push_back(5237);
        internal_counters.push_back(5698);
        internal_counters.push_back(6159);
        internal_counters.push_back(6620);
        internal_counters.push_back(7081);
        internal_counters.push_back(167);
        internal_counters.push_back(628);
        internal_counters.push_back(1089);
        internal_counters.push_back(1550);
        internal_counters.push_back(2011);
        internal_counters.push_back(2472);
        internal_counters.push_back(2933);
        internal_counters.push_back(3394);
        internal_counters.push_back(3855);
        internal_counters.push_back(4316);
        internal_counters.push_back(4777);
        internal_counters.push_back(5238);
        internal_counters.push_back(5699);
        internal_counters.push_back(6160);
        internal_counters.push_back(6621);
        internal_counters.push_back(7082);
        internal_counters.push_back(168);
        internal_counters.push_back(629);
        internal_counters.push_back(1090);
        internal_counters.push_back(1551);
        internal_counters.push_back(2012);
        internal_counters.push_back(2473);
        internal_counters.push_back(2934);
        internal_counters.push_back(3395);
        internal_counters.push_back(3856);
        internal_counters.push_back(4317);
        internal_counters.push_back(4778);
        internal_counters.push_back(5239);
        internal_counters.push_back(5700);
        internal_counters.push_back(6161);
        internal_counters.push_back(6622);
        internal_counters.push_back(7083);

        c.DefineDerivedCounter("CBColorAndMaskRead",
                               "ColorBuffer",
                               "Total number of bytes read from the color and mask buffers.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeBytes,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*",
                               "da41660e-eb6f-32ec-8a64-b32ca17bd7eb");
    }
    { // Index:102
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(158);
        internal_counters.push_back(619);
        internal_counters.push_back(1080);
        internal_counters.push_back(1541);
        internal_counters.push_back(2002);
        internal_counters.push_back(2463);
        internal_counters.push_back(2924);
        internal_counters.push_back(3385);
        internal_counters.push_back(3846);
        internal_counters.push_back(4307);
        internal_counters.push_back(4768);
        internal_counters.push_back(5229);
        internal_counters.push_back(5690);
        internal_counters.push_back(6151);
        internal_counters.push_back(6612);
        internal_counters.push_back(7073);

        c.DefineDerivedCounter("CBMemWritten",
                               "ColorBuffer",
                               "Number of bytes written to the color buffer.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeBytes,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*",
                               "550f8ff8-60b6-a6bf-87d0-25ac9e87de70");
    }
    { // Index:103
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(297);
        internal_counters.push_back(758);
        internal_counters.push_back(1219);
        internal_counters.push_back(1680);
        internal_counters.push_back(2141);
        internal_counters.push_back(2602);
        internal_counters.push_back(3063);
        internal_counters.push_back(3524);
        internal_counters.push_back(3985);
        internal_counters.push_back(4446);
        internal_counters.push_back(4907);
        internal_counters.push_back(5368);
        internal_counters.push_back(5829);
        internal_counters.push_back(6290);
        internal_counters.push_back(6751);
        internal_counters.push_back(7212);
        internal_counters.push_back(156);
        internal_counters.push_back(617);
        internal_counters.push_back(1078);
        internal_counters.push_back(1539);
        internal_counters.push_back(2000);
        internal_counters.push_back(2461);
        internal_counters.push_back(2922);
        internal_counters.push_back(3383);
        internal_counters.push_back(3844);
        internal_counters.push_back(4305);
        internal_counters.push_back(4766);
        internal_counters.push_back(5227);
        internal_counters.push_back(5688);
        internal_counters.push_back(6149);
        internal_counters.push_back(6610);
        internal_counters.push_back(7071);
        internal_counters.push_back(157);
        internal_counters.push_back(618);
        internal_counters.push_back(1079);
        internal_counters.push_back(1540);
        internal_counters.push_back(2001);
        internal_counters.push_back(2462);
        internal_counters.push_back(2923);
        internal_counters.push_back(3384);
        internal_counters.push_back(3845);
        internal_counters.push_back(4306);
        internal_counters.push_back(4767);
        internal_counters.push_back(5228);
        internal_counters.push_back(5689);
        internal_counters.push_back(6150);
        internal_counters.push_back(6611);
        internal_counters.push_back(7072);
        internal_counters.push_back(158);
        internal_counters.push_back(619);
        internal_counters.push_back(1080);
        internal_counters.push_back(1541);
        internal_counters.push_back(2002);
        internal_counters.push_back(2463);
        internal_counters.push_back(2924);
        internal_counters.push_back(3385);
        internal_counters.push_back(3846);
        internal_counters.push_back(4307);
        internal_counters.push_back(4768);
        internal_counters.push_back(5229);
        internal_counters.push_back(5690);
        internal_counters.push_back(6151);
        internal_counters.push_back(6612);
        internal_counters.push_back(7073);

        c.DefineDerivedCounter("CBColorAndMaskWritten",
                               "ColorBuffer",
                               "Total number of bytes written to the color and mask buffers.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeBytes,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*",
                               "29a04b69-8f5f-b770-a0f2-3453e2c99e49");
    }
    { // Index:104
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(202);
        internal_counters.push_back(663);
        internal_counters.push_back(1124);
        internal_counters.push_back(1585);
        internal_counters.push_back(2046);
        internal_counters.push_back(2507);
        internal_counters.push_back(2968);
        internal_counters.push_back(3429);
        internal_counters.push_back(3890);
        internal_counters.push_back(4351);
        internal_counters.push_back(4812);
        internal_counters.push_back(5273);
        internal_counters.push_back(5734);
        internal_counters.push_back(6195);
        internal_counters.push_back(6656);
        internal_counters.push_back(7117);
        internal_counters.push_back(47);
        internal_counters.push_back(508);
        internal_counters.push_back(969);
        internal_counters.push_back(1430);
        internal_counters.push_back(1891);
        internal_counters.push_back(2352);
        internal_counters.push_back(2813);
        internal_counters.push_back(3274);
        internal_counters.push_back(3735);
        internal_counters.push_back(4196);
        internal_counters.push_back(4657);
        internal_counters.push_back(5118);
        internal_counters.push_back(5579);
        internal_counters.push_back(6040);
        internal_counters.push_back(6501);
        internal_counters.push_back(6962);

        c.DefineDerivedCounter("CBSlowPixelPct",
                               "ColorBuffer",
                               "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*,(100),min",
                               "5775943f-0313-7e52-9638-b24a449197bc");
    }
    { // Index:105
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(202);
        internal_counters.push_back(663);
        internal_counters.push_back(1124);
        internal_counters.push_back(1585);
        internal_counters.push_back(2046);
        internal_counters.push_back(2507);
        internal_counters.push_back(2968);
        internal_counters.push_back(3429);
        internal_counters.push_back(3890);
        internal_counters.push_back(4351);
        internal_counters.push_back(4812);
        internal_counters.push_back(5273);
        internal_counters.push_back(5734);
        internal_counters.push_back(6195);
        internal_counters.push_back(6656);
        internal_counters.push_back(7117);

        c.DefineDerivedCounter("CBSlowPixelCount",
                               "ColorBuffer",
                               "Number of pixels written to the color buffer using a half-rate or quarter-rate format.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16",
                               "47eacbb0-28c8-22b4-5c69-c00d5813bb1c");
    }
    { // Index:106
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(40147);
        internal_counters.push_back(40224);
        internal_counters.push_back(40301);
        internal_counters.push_back(40378);
        internal_counters.push_back(40455);
        internal_counters.push_back(40532);
        internal_counters.push_back(40609);
        internal_counters.push_back(40686);
        internal_counters.push_back(40763);
        internal_counters.push_back(40840);
        internal_counters.push_back(40917);
        internal_counters.push_back(40994);
        internal_counters.push_back(41071);
        internal_counters.push_back(41148);
        internal_counters.push_back(41225);
        internal_counters.push_back(41302);
        internal_counters.push_back(41379);
        internal_counters.push_back(41456);
        internal_counters.push_back(41533);
        internal_counters.push_back(41610);
        internal_counters.push_back(41687);
        internal_counters.push_back(41764);
        internal_counters.push_back(41841);
        internal_counters.push_back(41918);
        internal_counters.push_back(41995);
        internal_counters.push_back(42072);
        internal_counters.push_back(42149);
        internal_counters.push_back(42226);
        internal_counters.push_back(42303);
        internal_counters.push_back(42380);
        internal_counters.push_back(42457);
        internal_counters.push_back(42534);
        internal_counters.push_back(42611);
        internal_counters.push_back(42688);
        internal_counters.push_back(42765);
        internal_counters.push_back(42842);
        internal_counters.push_back(42919);
        internal_counters.push_back(42996);
        internal_counters.push_back(43073);
        internal_counters.push_back(43150);
        internal_counters.push_back(40156);
        internal_counters.push_back(40233);
        internal_counters.push_back(40310);
        internal_counters.push_back(40387);
        internal_counters.push_back(40464);
        internal_counters.push_back(40541);
        internal_counters.push_back(40618);
        internal_counters.push_back(40695);
        internal_counters.push_back(40772);
        internal_counters.push_back(40849);
        internal_counters.push_back(40926);
        internal_counters.push_back(41003);
        internal_counters.push_back(41080);
        internal_counters.push_back(41157);
        internal_counters.push_back(41234);
        internal_counters.push_back(41311);
        internal_counters.push_back(41388);
        internal_counters.push_back(41465);
        internal_counters.push_back(41542);
        internal_counters.push_back(41619);
        internal_counters.push_back(41696);
        internal_counters.push_back(41773);
        internal_counters.push_back(41850);
        internal_counters.push_back(41927);
        internal_counters.push_back(42004);
        internal_counters.push_back(42081);
        internal_counters.push_back(42158);
        internal_counters.push_back(42235);
        internal_counters.push_back(42312);
        internal_counters.push_back(42389);
        internal_counters.push_back(42466);
        internal_counters.push_back(42543);
        internal_counters.push_back(42620);
        internal_counters.push_back(42697);
        internal_counters.push_back(42774);
        internal_counters.push_back(42851);
        internal_counters.push_back(42928);
        internal_counters.push_back(43005);
        internal_counters.push_back(43082);
        internal_counters.push_back(43159);

        c.DefineDerivedCounter("L0CacheHit",
                               "MemoryCache",
                               "The percentage of read requests that hit the data in the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "(0),(1),40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,ifnotzero",
                               "286c786e-9a42-3371-9dea-dd54e6e612e9");
    }
    { // Index:107
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(40147);
        internal_counters.push_back(40224);
        internal_counters.push_back(40301);
        internal_counters.push_back(40378);
        internal_counters.push_back(40455);
        internal_counters.push_back(40532);
        internal_counters.push_back(40609);
        internal_counters.push_back(40686);
        internal_counters.push_back(40763);
        internal_counters.push_back(40840);
        internal_counters.push_back(40917);
        internal_counters.push_back(40994);
        internal_counters.push_back(41071);
        internal_counters.push_back(41148);
        internal_counters.push_back(41225);
        internal_counters.push_back(41302);
        internal_counters.push_back(41379);
        internal_counters.push_back(41456);
        internal_counters.push_back(41533);
        internal_counters.push_back(41610);
        internal_counters.push_back(41687);
        internal_counters.push_back(41764);
        internal_counters.push_back(41841);
        internal_counters.push_back(41918);
        internal_counters.push_back(41995);
        internal_counters.push_back(42072);
        internal_counters.push_back(42149);
        internal_counters.push_back(42226);
        internal_counters.push_back(42303);
        internal_counters.push_back(42380);
        internal_counters.push_back(42457);
        internal_counters.push_back(42534);
        internal_counters.push_back(42611);
        internal_counters.push_back(42688);
        internal_counters.push_back(42765);
        internal_counters.push_back(42842);
        internal_counters.push_back(42919);
        internal_counters.push_back(42996);
        internal_counters.push_back(43073);
        internal_counters.push_back(43150);

        c.DefineDerivedCounter("L0CacheRequestCount",
                               "MemoryCache",
                               "The number of read requests made to the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40",
                               "74983cae-ee57-2e1b-d990-5128fef84e1f");
    }
    { // Index:108
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(40147);
        internal_counters.push_back(40224);
        internal_counters.push_back(40301);
        internal_counters.push_back(40378);
        internal_counters.push_back(40455);
        internal_counters.push_back(40532);
        internal_counters.push_back(40609);
        internal_counters.push_back(40686);
        internal_counters.push_back(40763);
        internal_counters.push_back(40840);
        internal_counters.push_back(40917);
        internal_counters.push_back(40994);
        internal_counters.push_back(41071);
        internal_counters.push_back(41148);
        internal_counters.push_back(41225);
        internal_counters.push_back(41302);
        internal_counters.push_back(41379);
        internal_counters.push_back(41456);
        internal_counters.push_back(41533);
        internal_counters.push_back(41610);
        internal_counters.push_back(41687);
        internal_counters.push_back(41764);
        internal_counters.push_back(41841);
        internal_counters.push_back(41918);
        internal_counters.push_back(41995);
        internal_counters.push_back(42072);
        internal_counters.push_back(42149);
        internal_counters.push_back(42226);
        internal_counters.push_back(42303);
        internal_counters.push_back(42380);
        internal_counters.push_back(42457);
        internal_counters.push_back(42534);
        internal_counters.push_back(42611);
        internal_counters.push_back(42688);
        internal_counters.push_back(42765);
        internal_counters.push_back(42842);
        internal_counters.push_back(42919);
        internal_counters.push_back(42996);
        internal_counters.push_back(43073);
        internal_counters.push_back(43150);
        internal_counters.push_back(40156);
        internal_counters.push_back(40233);
        internal_counters.push_back(40310);
        internal_counters.push_back(40387);
        internal_counters.push_back(40464);
        internal_counters.push_back(40541);
        internal_counters.push_back(40618);
        internal_counters.push_back(40695);
        internal_counters.push_back(40772);
        internal_counters.push_back(40849);
        internal_counters.push_back(40926);
        internal_counters.push_back(41003);
        internal_counters.push_back(41080);
        internal_counters.push_back(41157);
        internal_counters.push_back(41234);
        internal_counters.push_back(41311);
        internal_counters.push_back(41388);
        internal_counters.push_back(41465);
        internal_counters.push_back(41542);
        internal_counters.push_back(41619);
        internal_counters.push_back(41696);
        internal_counters.push_back(41773);
        internal_counters.push_back(41850);
        internal_counters.push_back(41927);
        internal_counters.push_back(42004);
        internal_counters.push_back(42081);
        internal_counters.push_back(42158);
        internal_counters.push_back(42235);
        internal_counters.push_back(42312);
        internal_counters.push_back(42389);
        internal_counters.push_back(42466);
        internal_counters.push_back(42543);
        internal_counters.push_back(42620);
        internal_counters.push_back(42697);
        internal_counters.push_back(42774);
        internal_counters.push_back(42851);
        internal_counters.push_back(42928);
        internal_counters.push_back(43005);
        internal_counters.push_back(43082);
        internal_counters.push_back(43159);

        c.DefineDerivedCounter("L0CacheHitCount",
                               "MemoryCache",
                               "The number of read requests which result in a cache hit from the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,-",
                               "c0de7338-069b-c5ba-ead3-c65e030cd2ac");
    }
    { // Index:109
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(40156);
        internal_counters.push_back(40233);
        internal_counters.push_back(40310);
        internal_counters.push_back(40387);
        internal_counters.push_back(40464);
        internal_counters.push_back(40541);
        internal_counters.push_back(40618);
        internal_counters.push_back(40695);
        internal_counters.push_back(40772);
        internal_counters.push_back(40849);
        internal_counters.push_back(40926);
        internal_counters.push_back(41003);
        internal_counters.push_back(41080);
        internal_counters.push_back(41157);
        internal_counters.push_back(41234);
        internal_counters.push_back(41311);
        internal_counters.push_back(41388);
        internal_counters.push_back(41465);
        internal_counters.push_back(41542);
        internal_counters.push_back(41619);
        internal_counters.push_back(41696);
        internal_counters.push_back(41773);
        internal_counters.push_back(41850);
        internal_counters.push_back(41927);
        internal_counters.push_back(42004);
        internal_counters.push_back(42081);
        internal_counters.push_back(42158);
        internal_counters.push_back(42235);
        internal_counters.push_back(42312);
        internal_counters.push_back(42389);
        internal_counters.push_back(42466);
        internal_counters.push_back(42543);
        internal_counters.push_back(42620);
        internal_counters.push_back(42697);
        internal_counters.push_back(42774);
        internal_counters.push_back(42851);
        internal_counters.push_back(42928);
        internal_counters.push_back(43005);
        internal_counters.push_back(43082);
        internal_counters.push_back(43159);

        c.DefineDerivedCounter("L0CacheMissCount",
                               "MemoryCache",
                               "The number of read requests which result in a cache miss from the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40",
                               "a2f08766-ea1b-6eae-6eaf-faa04125d3e6");
    }
    { // Index:110
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(50073);
        internal_counters.push_back(50137);
        internal_counters.push_back(50201);
        internal_counters.push_back(50265);
        internal_counters.push_back(50329);
        internal_counters.push_back(50393);
        internal_counters.push_back(50457);
        internal_counters.push_back(50521);
        internal_counters.push_back(50585);
        internal_counters.push_back(50649);
        internal_counters.push_back(50713);
        internal_counters.push_back(50777);
        internal_counters.push_back(50841);
        internal_counters.push_back(50905);
        internal_counters.push_back(50969);
        internal_counters.push_back(51033);
        internal_counters.push_back(50077);
        internal_counters.push_back(50141);
        internal_counters.push_back(50205);
        internal_counters.push_back(50269);
        internal_counters.push_back(50333);
        internal_counters.push_back(50397);
        internal_counters.push_back(50461);
        internal_counters.push_back(50525);
        internal_counters.push_back(50589);
        internal_counters.push_back(50653);
        internal_counters.push_back(50717);
        internal_counters.push_back(50781);
        internal_counters.push_back(50845);
        internal_counters.push_back(50909);
        internal_counters.push_back(50973);
        internal_counters.push_back(51037);

        c.DefineDerivedCounter("L1CacheHit",
                               "MemoryCache",
                               "The percentage of read or write requests that hit the data in the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero",
                               "5a34915a-24b8-8baf-2bf8-5878e7894ae3");
    }
    { // Index:111
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(50073);
        internal_counters.push_back(50137);
        internal_counters.push_back(50201);
        internal_counters.push_back(50265);
        internal_counters.push_back(50329);
        internal_counters.push_back(50393);
        internal_counters.push_back(50457);
        internal_counters.push_back(50521);
        internal_counters.push_back(50585);
        internal_counters.push_back(50649);
        internal_counters.push_back(50713);
        internal_counters.push_back(50777);
        internal_counters.push_back(50841);
        internal_counters.push_back(50905);
        internal_counters.push_back(50969);
        internal_counters.push_back(51033);

        c.DefineDerivedCounter("L1CacheRequestCount",
                               "MemoryCache",
                               "The number of read or write requests made to the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16",
                               "29c76c67-4611-205d-0b88-d08668df03c5");
    }
    { // Index:112
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(50073);
        internal_counters.push_back(50137);
        internal_counters.push_back(50201);
        internal_counters.push_back(50265);
        internal_counters.push_back(50329);
        internal_counters.push_back(50393);
        internal_counters.push_back(50457);
        internal_counters.push_back(50521);
        internal_counters.push_back(50585);
        internal_counters.push_back(50649);
        internal_counters.push_back(50713);
        internal_counters.push_back(50777);
        internal_counters.push_back(50841);
        internal_counters.push_back(50905);
        internal_counters.push_back(50969);
        internal_counters.push_back(51033);
        internal_counters.push_back(50077);
        internal_counters.push_back(50141);
        internal_counters.push_back(50205);
        internal_counters.push_back(50269);
        internal_counters.push_back(50333);
        internal_counters.push_back(50397);
        internal_counters.push_back(50461);
        internal_counters.push_back(50525);
        internal_counters.push_back(50589);
        internal_counters.push_back(50653);
        internal_counters.push_back(50717);
        internal_counters.push_back(50781);
        internal_counters.push_back(50845);
        internal_counters.push_back(50909);
        internal_counters.push_back(50973);
        internal_counters.push_back(51037);

        c.DefineDerivedCounter("L1CacheHitCount",
                               "MemoryCache",
                               "The number of read or write requests which result in a cache hit from the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-",
                               "1ae150c3-f2d0-82c6-a51b-a77fd8d5fc33");
    }
    { // Index:113
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(50077);
        internal_counters.push_back(50141);
        internal_counters.push_back(50205);
        internal_counters.push_back(50269);
        internal_counters.push_back(50333);
        internal_counters.push_back(50397);
        internal_counters.push_back(50461);
        internal_counters.push_back(50525);
        internal_counters.push_back(50589);
        internal_counters.push_back(50653);
        internal_counters.push_back(50717);
        internal_counters.push_back(50781);
        internal_counters.push_back(50845);
        internal_counters.push_back(50909);
        internal_counters.push_back(50973);
        internal_counters.push_back(51037);

        c.DefineDerivedCounter("L1CacheMissCount",
                               "MemoryCache",
                               "The number of read or write requests which result in a cache miss from the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16",
                               "71bfec6d-257b-849d-e212-cdf5c1b1de65");
    }
    { // Index:114
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52058);
        internal_counters.push_back(52293);
        internal_counters.push_back(52528);
        internal_counters.push_back(52763);
        internal_counters.push_back(52998);
        internal_counters.push_back(53233);
        internal_counters.push_back(53468);
        internal_counters.push_back(53703);
        internal_counters.push_back(53938);
        internal_counters.push_back(54173);
        internal_counters.push_back(54408);
        internal_counters.push_back(54643);
        internal_counters.push_back(54878);
        internal_counters.push_back(55113);
        internal_counters.push_back(55348);
        internal_counters.push_back(55583);
        internal_counters.push_back(52090);
        internal_counters.push_back(52325);
        internal_counters.push_back(52560);
        internal_counters.push_back(52795);
        internal_counters.push_back(53030);
        internal_counters.push_back(53265);
        internal_counters.push_back(53500);
        internal_counters.push_back(53735);
        internal_counters.push_back(53970);
        internal_counters.push_back(54205);
        internal_counters.push_back(54440);
        internal_counters.push_back(54675);
        internal_counters.push_back(54910);
        internal_counters.push_back(55145);
        internal_counters.push_back(55380);
        internal_counters.push_back(55615);

        c.DefineDerivedCounter("L2CacheHit",
                               "MemoryCache",
                               "The percentage of read or write requests that hit the data in the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero",
                               "47694e4d-6ce6-f387-080d-b1f3d00b73ac");
    }
    { // Index:115
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52090);
        internal_counters.push_back(52325);
        internal_counters.push_back(52560);
        internal_counters.push_back(52795);
        internal_counters.push_back(53030);
        internal_counters.push_back(53265);
        internal_counters.push_back(53500);
        internal_counters.push_back(53735);
        internal_counters.push_back(53970);
        internal_counters.push_back(54205);
        internal_counters.push_back(54440);
        internal_counters.push_back(54675);
        internal_counters.push_back(54910);
        internal_counters.push_back(55145);
        internal_counters.push_back(55380);
        internal_counters.push_back(55615);
        internal_counters.push_back(52058);
        internal_counters.push_back(52293);
        internal_counters.push_back(52528);
        internal_counters.push_back(52763);
        internal_counters.push_back(52998);
        internal_counters.push_back(53233);
        internal_counters.push_back(53468);
        internal_counters.push_back(53703);
        internal_counters.push_back(53938);
        internal_counters.push_back(54173);
        internal_counters.push_back(54408);
        internal_counters.push_back(54643);
        internal_counters.push_back(54878);
        internal_counters.push_back(55113);
        internal_counters.push_back(55348);
        internal_counters.push_back(55583);

        c.DefineDerivedCounter("L2CacheMiss",
                               "MemoryCache",
                               "The percentage of read or write requests that miss the data in the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size. Value range: 0% (optimal) to 100% (all miss).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*",
                               "8aee5458-a58e-11b6-5131-7f19ed070117");
    }
    { // Index:116
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52058);
        internal_counters.push_back(52293);
        internal_counters.push_back(52528);
        internal_counters.push_back(52763);
        internal_counters.push_back(52998);
        internal_counters.push_back(53233);
        internal_counters.push_back(53468);
        internal_counters.push_back(53703);
        internal_counters.push_back(53938);
        internal_counters.push_back(54173);
        internal_counters.push_back(54408);
        internal_counters.push_back(54643);
        internal_counters.push_back(54878);
        internal_counters.push_back(55113);
        internal_counters.push_back(55348);
        internal_counters.push_back(55583);

        c.DefineDerivedCounter("L2CacheRequestCount",
                               "MemoryCache",
                               "The number of read or write requests made to the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16",
                               "21e9219c-e725-0d96-06b1-b21698b736b2");
    }
    { // Index:117
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52058);
        internal_counters.push_back(52293);
        internal_counters.push_back(52528);
        internal_counters.push_back(52763);
        internal_counters.push_back(52998);
        internal_counters.push_back(53233);
        internal_counters.push_back(53468);
        internal_counters.push_back(53703);
        internal_counters.push_back(53938);
        internal_counters.push_back(54173);
        internal_counters.push_back(54408);
        internal_counters.push_back(54643);
        internal_counters.push_back(54878);
        internal_counters.push_back(55113);
        internal_counters.push_back(55348);
        internal_counters.push_back(55583);
        internal_counters.push_back(52090);
        internal_counters.push_back(52325);
        internal_counters.push_back(52560);
        internal_counters.push_back(52795);
        internal_counters.push_back(53030);
        internal_counters.push_back(53265);
        internal_counters.push_back(53500);
        internal_counters.push_back(53735);
        internal_counters.push_back(53970);
        internal_counters.push_back(54205);
        internal_counters.push_back(54440);
        internal_counters.push_back(54675);
        internal_counters.push_back(54910);
        internal_counters.push_back(55145);
        internal_counters.push_back(55380);
        internal_counters.push_back(55615);

        c.DefineDerivedCounter("L2CacheHitCount",
                               "MemoryCache",
                               "The number of read or write requests which result in a cache hit from the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-",
                               "29ddcb92-d3dd-951b-1b23-efe52e4eeee4");
    }
    { // Index:118
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52090);
        internal_counters.push_back(52325);
        internal_counters.push_back(52560);
        internal_counters.push_back(52795);
        internal_counters.push_back(53030);
        internal_counters.push_back(53265);
        internal_counters.push_back(53500);
        internal_counters.push_back(53735);
        internal_counters.push_back(53970);
        internal_counters.push_back(54205);
        internal_counters.push_back(54440);
        internal_counters.push_back(54675);
        internal_counters.push_back(54910);
        internal_counters.push_back(55145);
        internal_counters.push_back(55380);
        internal_counters.push_back(55615);

        c.DefineDerivedCounter("L2CacheMissCount",
                               "MemoryCache",
                               "The number of read or write requests which result in a cache miss from the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16",
                               "376eec7b-ab25-9012-06b5-63291a17fd47");
    }
    { // Index:119
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(40182);
        internal_counters.push_back(40259);
        internal_counters.push_back(40336);
        internal_counters.push_back(40413);
        internal_counters.push_back(40490);
        internal_counters.push_back(40567);
        internal_counters.push_back(40644);
        internal_counters.push_back(40721);
        internal_counters.push_back(40798);
        internal_counters.push_back(40875);
        internal_counters.push_back(40952);
        internal_counters.push_back(41029);
        internal_counters.push_back(41106);
        internal_counters.push_back(41183);
        internal_counters.push_back(41260);
        internal_counters.push_back(41337);
        internal_counters.push_back(41414);
        internal_counters.push_back(41491);
        internal_counters.push_back(41568);
        internal_counters.push_back(41645);
        internal_counters.push_back(41722);
        internal_counters.push_back(41799);
        internal_counters.push_back(41876);
        internal_counters.push_back(41953);
        internal_counters.push_back(42030);
        internal_counters.push_back(42107);
        internal_counters.push_back(42184);
        internal_counters.push_back(42261);
        internal_counters.push_back(42338);
        internal_counters.push_back(42415);
        internal_counters.push_back(42492);
        internal_counters.push_back(42569);
        internal_counters.push_back(42646);
        internal_counters.push_back(42723);
        internal_counters.push_back(42800);
        internal_counters.push_back(42877);
        internal_counters.push_back(42954);
        internal_counters.push_back(43031);
        internal_counters.push_back(43108);
        internal_counters.push_back(43185);

        c.DefineDerivedCounter("L0TagConflictReadStalledCycles",
                               "MemoryCache",
                               "The number of cycles read operations from the L0 cache are stalled due to tag conflicts.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40",
                               "e2412737-e2bf-c791-5f2f-64abd4ba47cf");
    }
    { // Index:120
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(40183);
        internal_counters.push_back(40260);
        internal_counters.push_back(40337);
        internal_counters.push_back(40414);
        internal_counters.push_back(40491);
        internal_counters.push_back(40568);
        internal_counters.push_back(40645);
        internal_counters.push_back(40722);
        internal_counters.push_back(40799);
        internal_counters.push_back(40876);
        internal_counters.push_back(40953);
        internal_counters.push_back(41030);
        internal_counters.push_back(41107);
        internal_counters.push_back(41184);
        internal_counters.push_back(41261);
        internal_counters.push_back(41338);
        internal_counters.push_back(41415);
        internal_counters.push_back(41492);
        internal_counters.push_back(41569);
        internal_counters.push_back(41646);
        internal_counters.push_back(41723);
        internal_counters.push_back(41800);
        internal_counters.push_back(41877);
        internal_counters.push_back(41954);
        internal_counters.push_back(42031);
        internal_counters.push_back(42108);
        internal_counters.push_back(42185);
        internal_counters.push_back(42262);
        internal_counters.push_back(42339);
        internal_counters.push_back(42416);
        internal_counters.push_back(42493);
        internal_counters.push_back(42570);
        internal_counters.push_back(42647);
        internal_counters.push_back(42724);
        internal_counters.push_back(42801);
        internal_counters.push_back(42878);
        internal_counters.push_back(42955);
        internal_counters.push_back(43032);
        internal_counters.push_back(43109);
        internal_counters.push_back(43186);

        c.DefineDerivedCounter("L0TagConflictWriteStalledCycles",
                               "MemoryCache",
                               "The number of cycles write operations to the L0 cache are stalled due to tag conflicts.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40",
                               "0c2571f3-f084-f351-99ba-0d9e23b47e8e");
    }
    { // Index:121
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(40184);
        internal_counters.push_back(40261);
        internal_counters.push_back(40338);
        internal_counters.push_back(40415);
        internal_counters.push_back(40492);
        internal_counters.push_back(40569);
        internal_counters.push_back(40646);
        internal_counters.push_back(40723);
        internal_counters.push_back(40800);
        internal_counters.push_back(40877);
        internal_counters.push_back(40954);
        internal_counters.push_back(41031);
        internal_counters.push_back(41108);
        internal_counters.push_back(41185);
        internal_counters.push_back(41262);
        internal_counters.push_back(41339);
        internal_counters.push_back(41416);
        internal_counters.push_back(41493);
        internal_counters.push_back(41570);
        internal_counters.push_back(41647);
        internal_counters.push_back(41724);
        internal_counters.push_back(41801);
        internal_counters.push_back(41878);
        internal_counters.push_back(41955);
        internal_counters.push_back(42032);
        internal_counters.push_back(42109);
        internal_counters.push_back(42186);
        internal_counters.push_back(42263);
        internal_counters.push_back(42340);
        internal_counters.push_back(42417);
        internal_counters.push_back(42494);
        internal_counters.push_back(42571);
        internal_counters.push_back(42648);
        internal_counters.push_back(42725);
        internal_counters.push_back(42802);
        internal_counters.push_back(42879);
        internal_counters.push_back(42956);
        internal_counters.push_back(43033);
        internal_counters.push_back(43110);
        internal_counters.push_back(43187);

        c.DefineDerivedCounter("L0TagConflictAtomicStalledCycles",
                               "MemoryCache",
                               "The number of cycles atomic operations on the L0 cache are stalled due to tag conflicts.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeItems,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40",
                               "f13f8563-4151-1533-f42f-0f9c08a20210");
    }
    { // Index:122
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52144);
        internal_counters.push_back(52379);
        internal_counters.push_back(52614);
        internal_counters.push_back(52849);
        internal_counters.push_back(53084);
        internal_counters.push_back(53319);
        internal_counters.push_back(53554);
        internal_counters.push_back(53789);
        internal_counters.push_back(54024);
        internal_counters.push_back(54259);
        internal_counters.push_back(54494);
        internal_counters.push_back(54729);
        internal_counters.push_back(54964);
        internal_counters.push_back(55199);
        internal_counters.push_back(55434);
        internal_counters.push_back(55669);
        internal_counters.push_back(52145);
        internal_counters.push_back(52380);
        internal_counters.push_back(52615);
        internal_counters.push_back(52850);
        internal_counters.push_back(53085);
        internal_counters.push_back(53320);
        internal_counters.push_back(53555);
        internal_counters.push_back(53790);
        internal_counters.push_back(54025);
        internal_counters.push_back(54260);
        internal_counters.push_back(54495);
        internal_counters.push_back(54730);
        internal_counters.push_back(54965);
        internal_counters.push_back(55200);
        internal_counters.push_back(55435);
        internal_counters.push_back(55670);
        internal_counters.push_back(52146);
        internal_counters.push_back(52381);
        internal_counters.push_back(52616);
        internal_counters.push_back(52851);
        internal_counters.push_back(53086);
        internal_counters.push_back(53321);
        internal_counters.push_back(53556);
        internal_counters.push_back(53791);
        internal_counters.push_back(54026);
        internal_counters.push_back(54261);
        internal_counters.push_back(54496);
        internal_counters.push_back(54731);
        internal_counters.push_back(54966);
        internal_counters.push_back(55201);
        internal_counters.push_back(55436);
        internal_counters.push_back(55671);
        internal_counters.push_back(52147);
        internal_counters.push_back(52382);
        internal_counters.push_back(52617);
        internal_counters.push_back(52852);
        internal_counters.push_back(53087);
        internal_counters.push_back(53322);
        internal_counters.push_back(53557);
        internal_counters.push_back(53792);
        internal_counters.push_back(54027);
        internal_counters.push_back(54262);
        internal_counters.push_back(54497);
        internal_counters.push_back(54732);
        internal_counters.push_back(54967);
        internal_counters.push_back(55202);
        internal_counters.push_back(55437);
        internal_counters.push_back(55672);

        c.DefineDerivedCounter("FetchSize",
                               "GlobalMemory",
                               "The total bytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeBytes,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,(96),*,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,(128),*,sum4",
                               "664bb3ef-6eca-86b1-1e2d-30cb897b5fa9");
    }
    { // Index:123
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52130);
        internal_counters.push_back(52365);
        internal_counters.push_back(52600);
        internal_counters.push_back(52835);
        internal_counters.push_back(53070);
        internal_counters.push_back(53305);
        internal_counters.push_back(53540);
        internal_counters.push_back(53775);
        internal_counters.push_back(54010);
        internal_counters.push_back(54245);
        internal_counters.push_back(54480);
        internal_counters.push_back(54715);
        internal_counters.push_back(54950);
        internal_counters.push_back(55185);
        internal_counters.push_back(55420);
        internal_counters.push_back(55655);
        internal_counters.push_back(52131);
        internal_counters.push_back(52366);
        internal_counters.push_back(52601);
        internal_counters.push_back(52836);
        internal_counters.push_back(53071);
        internal_counters.push_back(53306);
        internal_counters.push_back(53541);
        internal_counters.push_back(53776);
        internal_counters.push_back(54011);
        internal_counters.push_back(54246);
        internal_counters.push_back(54481);
        internal_counters.push_back(54716);
        internal_counters.push_back(54951);
        internal_counters.push_back(55186);
        internal_counters.push_back(55421);
        internal_counters.push_back(55656);

        c.DefineDerivedCounter("WriteSize",
                               "GlobalMemory",
                               "The total bytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeBytes,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+",
                               "f96f2c16-b1b4-4ec4-229c-fc82e6f80a82");
    }
    { // Index:124
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(28673);
        internal_counters.push_back(28899);
        internal_counters.push_back(29125);
        internal_counters.push_back(29351);
        internal_counters.push_back(29577);
        internal_counters.push_back(29803);
        internal_counters.push_back(30029);
        internal_counters.push_back(30255);
        internal_counters.push_back(30481);
        internal_counters.push_back(30707);
        internal_counters.push_back(30933);
        internal_counters.push_back(31159);
        internal_counters.push_back(31385);
        internal_counters.push_back(31611);
        internal_counters.push_back(31837);
        internal_counters.push_back(32063);
        internal_counters.push_back(32289);
        internal_counters.push_back(32515);
        internal_counters.push_back(32741);
        internal_counters.push_back(32967);
        internal_counters.push_back(33193);
        internal_counters.push_back(33419);
        internal_counters.push_back(33645);
        internal_counters.push_back(33871);
        internal_counters.push_back(34097);
        internal_counters.push_back(34323);
        internal_counters.push_back(34549);
        internal_counters.push_back(34775);
        internal_counters.push_back(35001);
        internal_counters.push_back(35227);
        internal_counters.push_back(35453);
        internal_counters.push_back(35679);
        internal_counters.push_back(35905);
        internal_counters.push_back(36131);
        internal_counters.push_back(36357);
        internal_counters.push_back(36583);
        internal_counters.push_back(36809);
        internal_counters.push_back(37035);
        internal_counters.push_back(37261);
        internal_counters.push_back(37487);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("MemUnitBusy",
                               "GlobalMemory",
                               "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,/,(100),*",
                               "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    { // Index:125
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(28673);
        internal_counters.push_back(28899);
        internal_counters.push_back(29125);
        internal_counters.push_back(29351);
        internal_counters.push_back(29577);
        internal_counters.push_back(29803);
        internal_counters.push_back(30029);
        internal_counters.push_back(30255);
        internal_counters.push_back(30481);
        internal_counters.push_back(30707);
        internal_counters.push_back(30933);
        internal_counters.push_back(31159);
        internal_counters.push_back(31385);
        internal_counters.push_back(31611);
        internal_counters.push_back(31837);
        internal_counters.push_back(32063);
        internal_counters.push_back(32289);
        internal_counters.push_back(32515);
        internal_counters.push_back(32741);
        internal_counters.push_back(32967);
        internal_counters.push_back(33193);
        internal_counters.push_back(33419);
        internal_counters.push_back(33645);
        internal_counters.push_back(33871);
        internal_counters.push_back(34097);
        internal_counters.push_back(34323);
        internal_counters.push_back(34549);
        internal_counters.push_back(34775);
        internal_counters.push_back(35001);
        internal_counters.push_back(35227);
        internal_counters.push_back(35453);
        internal_counters.push_back(35679);
        internal_counters.push_back(35905);
        internal_counters.push_back(36131);
        internal_counters.push_back(36357);
        internal_counters.push_back(36583);
        internal_counters.push_back(36809);
        internal_counters.push_back(37035);
        internal_counters.push_back(37261);
        internal_counters.push_back(37487);

        c.DefineDerivedCounter("MemUnitBusyCycles",
                               "GlobalMemory",
                               "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalledCycles). This is measured with all extra fetches and writes and any cache or memory effects taken into account.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40",
                               "168f077c-4797-b2f5-717f-105c725266c8");
    }
    { // Index:126
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(40174);
        internal_counters.push_back(40251);
        internal_counters.push_back(40328);
        internal_counters.push_back(40405);
        internal_counters.push_back(40482);
        internal_counters.push_back(40559);
        internal_counters.push_back(40636);
        internal_counters.push_back(40713);
        internal_counters.push_back(40790);
        internal_counters.push_back(40867);
        internal_counters.push_back(40944);
        internal_counters.push_back(41021);
        internal_counters.push_back(41098);
        internal_counters.push_back(41175);
        internal_counters.push_back(41252);
        internal_counters.push_back(41329);
        internal_counters.push_back(41406);
        internal_counters.push_back(41483);
        internal_counters.push_back(41560);
        internal_counters.push_back(41637);
        internal_counters.push_back(41714);
        internal_counters.push_back(41791);
        internal_counters.push_back(41868);
        internal_counters.push_back(41945);
        internal_counters.push_back(42022);
        internal_counters.push_back(42099);
        internal_counters.push_back(42176);
        internal_counters.push_back(42253);
        internal_counters.push_back(42330);
        internal_counters.push_back(42407);
        internal_counters.push_back(42484);
        internal_counters.push_back(42561);
        internal_counters.push_back(42638);
        internal_counters.push_back(42715);
        internal_counters.push_back(42792);
        internal_counters.push_back(42869);
        internal_counters.push_back(42946);
        internal_counters.push_back(43023);
        internal_counters.push_back(43100);
        internal_counters.push_back(43177);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("MemUnitStalled",
                               "GlobalMemory",
                               "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,/,(100),*",
                               "465ba54f-d250-1453-790a-731b10d230b1");
    }
    { // Index:127
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(40174);
        internal_counters.push_back(40251);
        internal_counters.push_back(40328);
        internal_counters.push_back(40405);
        internal_counters.push_back(40482);
        internal_counters.push_back(40559);
        internal_counters.push_back(40636);
        internal_counters.push_back(40713);
        internal_counters.push_back(40790);
        internal_counters.push_back(40867);
        internal_counters.push_back(40944);
        internal_counters.push_back(41021);
        internal_counters.push_back(41098);
        internal_counters.push_back(41175);
        internal_counters.push_back(41252);
        internal_counters.push_back(41329);
        internal_counters.push_back(41406);
        internal_counters.push_back(41483);
        internal_counters.push_back(41560);
        internal_counters.push_back(41637);
        internal_counters.push_back(41714);
        internal_counters.push_back(41791);
        internal_counters.push_back(41868);
        internal_counters.push_back(41945);
        internal_counters.push_back(42022);
        internal_counters.push_back(42099);
        internal_counters.push_back(42176);
        internal_counters.push_back(42253);
        internal_counters.push_back(42330);
        internal_counters.push_back(42407);
        internal_counters.push_back(42484);
        internal_counters.push_back(42561);
        internal_counters.push_back(42638);
        internal_counters.push_back(42715);
        internal_counters.push_back(42792);
        internal_counters.push_back(42869);
        internal_counters.push_back(42946);
        internal_counters.push_back(43023);
        internal_counters.push_back(43100);
        internal_counters.push_back(43177);

        c.DefineDerivedCounter("MemUnitStalledCycles",
                               "GlobalMemory",
                               "Number of GPU cycles the memory unit is stalled.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40",
                               "2745659a-0e40-bace-3b9b-86a54f8e4623");
    }
    { // Index:128
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52134);
        internal_counters.push_back(52369);
        internal_counters.push_back(52604);
        internal_counters.push_back(52839);
        internal_counters.push_back(53074);
        internal_counters.push_back(53309);
        internal_counters.push_back(53544);
        internal_counters.push_back(53779);
        internal_counters.push_back(54014);
        internal_counters.push_back(54249);
        internal_counters.push_back(54484);
        internal_counters.push_back(54719);
        internal_counters.push_back(54954);
        internal_counters.push_back(55189);
        internal_counters.push_back(55424);
        internal_counters.push_back(55659);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("WriteUnitStalled",
                               "GlobalMemory",
                               "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypePercentage,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*",
                               "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    { // Index:129
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52134);
        internal_counters.push_back(52369);
        internal_counters.push_back(52604);
        internal_counters.push_back(52839);
        internal_counters.push_back(53074);
        internal_counters.push_back(53309);
        internal_counters.push_back(53544);
        internal_counters.push_back(53779);
        internal_counters.push_back(54014);
        internal_counters.push_back(54249);
        internal_counters.push_back(54484);
        internal_counters.push_back(54719);
        internal_counters.push_back(54954);
        internal_counters.push_back(55189);
        internal_counters.push_back(55424);
        internal_counters.push_back(55659);

        c.DefineDerivedCounter("WriteUnitStalledCycles",
                               "GlobalMemory",
                               "Number of GPU cycles the Write unit is stalled.",
                               kGpaDataTypeFloat64,
                               kGpaUsageTypeCycles,
                               true,
                               false,
                               internal_counters,
                               "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16",
                               "ede3305e-abd4-d6bf-6b00-ffc57a29fce3");
    }
}

// clang-format on

