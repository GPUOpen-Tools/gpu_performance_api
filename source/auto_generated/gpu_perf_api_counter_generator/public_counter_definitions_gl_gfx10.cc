//==============================================================================
// Copyright (c) 2010-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for GL GFX10.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_gl_gfx10.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersGlGfx10(GpaDerivedCounters& c)
{
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(23224);

        c.DefineDerivedCounter("GPUTime", "Timing", "Time this API command took to execute on the GPU in nanoseconds from the time the previous command reached the bottom of the pipeline (BOP) to the time this command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "0,TS_FREQ,/,(1000000000),*", "cbd338f2-de6c-7b14-92ad-ba724ca2e501");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1868);
        internal_counters.push_back(1844);

        c.DefineDerivedCounter("GPUBusy", "Timing", "The percentage of time the GPU command processor was busy.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,/,(100),*,(100),min", "b1ba5363-1abc-fe66-2fdd-1fe6ee8989a0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("GPUBusyCycles", "Timing", "Number of GPU cycles that the GPU command processor was busy.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0", "451cb045-23af-ac44-4603-d5832fa041d9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4801);
        internal_counters.push_back(4818);
        internal_counters.push_back(4841);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("VsGsBusy", "Timing", "The percentage of time the ShaderUnit has VS or GS work to do in a VS-[GS-]PS pipeline.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,max,NUM_SHADER_ENGINES,/,(0),2,ifnotzero,3,/,(100),*,(100),min", "969c41c7-eb0b-9706-a7a1-98f27c3af56b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4801);
        internal_counters.push_back(4818);
        internal_counters.push_back(4841);

        c.DefineDerivedCounter("VsGsBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has VS or GS work to do in a VS-[GS-]PS pipeline.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,max,NUM_SHADER_ENGINES,/,(0),2,ifnotzero", "a8420bb7-6bd8-930a-9088-d73b9c039851");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(23224);
        internal_counters.push_back(4801);
        internal_counters.push_back(4818);
        internal_counters.push_back(4841);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("VsGsTime", "Timing", "Time VS or GS are busy in nanoseconds in a VS-[GS-]PS pipeline.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "1,2,max,NUM_SHADER_ENGINES,/,(0),3,ifnotzero,4,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "3ce33b11-210d-b3de-9b6c-b9f3cd04beff");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4834);
        internal_counters.push_back(4841);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("PreTessellationBusy", "Timing", "The percentage of time the ShaderUnit has VS and HS work to do in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,NUM_SHADER_ENGINES,/,1,ifnotzero,2,/,(100),*,(100),min", "346c7430-4666-7065-b5b7-1cb8cbb1c01c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4834);
        internal_counters.push_back(4841);

        c.DefineDerivedCounter("PreTessellationBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has VS and HS work to do in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,NUM_SHADER_ENGINES,/,1,ifnotzero", "dac68e38-0e3a-9364-2674-308e63bee2d2");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(23224);
        internal_counters.push_back(4834);
        internal_counters.push_back(4841);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("PreTessellationTime", "Timing", "Time VS and HS are busy in nanoseconds in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,NUM_SHADER_ENGINES,/,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "d5e6c54c-5ffb-b173-6118-bece61f0281c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4801);
        internal_counters.push_back(4818);
        internal_counters.push_back(4841);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("PostTessellationBusy", "Timing", "The percentage of time the ShaderUnit has DS or GS work to do in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,max,NUM_SHADER_ENGINES,/,2,ifnotzero,3,/,(100),*,(100),min", "1a275c68-9340-f358-71c6-a2648390381d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4801);
        internal_counters.push_back(4818);
        internal_counters.push_back(4841);

        c.DefineDerivedCounter("PostTessellationBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has DS or GS work to do in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,max,NUM_SHADER_ENGINES,/,2,ifnotzero", "a5ed943b-13ef-942b-56fb-6d519eeb7337");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(23224);
        internal_counters.push_back(4801);
        internal_counters.push_back(4818);
        internal_counters.push_back(4841);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("PostTessellationTime", "Timing", "Time DS or GS are busy in nanoseconds in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,max,NUM_SHADER_ENGINES,/,3,ifnotzero,4,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "9f8dfa40-faee-2014-3467-2630a7d95c1e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4860);
        internal_counters.push_back(4880);
        internal_counters.push_back(4861);
        internal_counters.push_back(4881);
        internal_counters.push_back(4862);
        internal_counters.push_back(4882);
        internal_counters.push_back(4863);
        internal_counters.push_back(4883);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("PSBusy", "Timing", "The percentage of time the ShaderUnit has pixel shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,(0),4,5,ifnotzero,(0),6,7,ifnotzero,max4,NUM_SHADER_ENGINES,/,8,/,(100),*,(100),min", "7e772beb-d82c-bd9a-aed0-fe504d416ce5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4860);
        internal_counters.push_back(4880);
        internal_counters.push_back(4861);
        internal_counters.push_back(4881);
        internal_counters.push_back(4862);
        internal_counters.push_back(4882);
        internal_counters.push_back(4863);
        internal_counters.push_back(4883);

        c.DefineDerivedCounter("PSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has pixel shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,(0),4,5,ifnotzero,(0),6,7,ifnotzero,max4,NUM_SHADER_ENGINES,/", "b58bea04-ce8e-2984-80f4-8aba7d4c817b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(23224);
        internal_counters.push_back(4860);
        internal_counters.push_back(4880);
        internal_counters.push_back(4861);
        internal_counters.push_back(4881);
        internal_counters.push_back(4862);
        internal_counters.push_back(4882);
        internal_counters.push_back(4863);
        internal_counters.push_back(4883);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("PSTime", "Timing", "Time pixel shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,ifnotzero,(0),3,4,ifnotzero,(0),5,6,ifnotzero,(0),7,8,ifnotzero,max4,NUM_SHADER_ENGINES,/,9,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "edca7694-7416-e8a6-0c5a-63a5ad5f3d74");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4845);
        internal_counters.push_back(4849);
        internal_counters.push_back(4851);
        internal_counters.push_back(4855);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("CSBusy", "Timing", "The percentage of time the ShaderUnit has compute shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,max,NUM_SHADER_ENGINES,/,4,/,(100),*,(100),min", "493fdd90-8d2b-a055-5e4e-2d29c3396b8c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4845);
        internal_counters.push_back(4849);
        internal_counters.push_back(4851);
        internal_counters.push_back(4855);

        c.DefineDerivedCounter("CSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has compute shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,max,NUM_SHADER_ENGINES,/", "39bcf1b8-f6b2-4c37-f9af-0a2bb59512f9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(23224);
        internal_counters.push_back(4845);
        internal_counters.push_back(4849);
        internal_counters.push_back(4851);
        internal_counters.push_back(4855);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("CSTime", "Timing", "Time compute shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,ifnotzero,(0),3,4,ifnotzero,max,NUM_SHADER_ENGINES,/,5,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "dbc24916-ecb2-7eef-8d63-7afadaaab6bc");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6729);
        internal_counters.push_back(6669);
        internal_counters.push_back(6217);
        internal_counters.push_back(6157);
        internal_counters.push_back(4841);

        c.DefineDerivedCounter("VsGsVALUInstCount", "VertexGeometry", "Average number of vector ALU instructions executed for the VS and GS in a VS-[GS-]PS pipeline. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero,2,3,/,3,ifnotzero,(0),4,ifnotzero", "9f5e6407-3b8c-e0a8-9987-a59586b45ea8");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6725);
        internal_counters.push_back(6669);
        internal_counters.push_back(6213);
        internal_counters.push_back(6157);
        internal_counters.push_back(4841);

        c.DefineDerivedCounter("VsGsSALUInstCount", "VertexGeometry", "Average number of scalar ALU instructions executed for the VS and GS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero,2,3,/,3,ifnotzero,(0),4,ifnotzero", "67fe9696-8428-cf74-09d9-9133ea0f148c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6782);
        internal_counters.push_back(6270);
        internal_counters.push_back(1868);
        internal_counters.push_back(4841);

        c.DefineDerivedCounter("VsGsVALUBusy", "VertexGeometry", "The percentage of GPUTime vector ALU instructions are being processed for the VS and GS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,+,NUM_SIMDS,/,2,/,(100),*,(0),3,ifnotzero", "0e98794e-d570-20a5-671c-b65c3991d358");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6782);
        internal_counters.push_back(6270);
        internal_counters.push_back(4841);

        c.DefineDerivedCounter("VsGsVALUBusyCycles", "VertexGeometry", "Number of GPU cycles where vector ALU instructions are being processed for the VS and GS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,+,NUM_SIMDS,/,(0),2,ifnotzero", "3558535c-e727-e459-4484-bcb683fcac2f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6725);
        internal_counters.push_back(6213);
        internal_counters.push_back(1868);
        internal_counters.push_back(4841);

        c.DefineDerivedCounter("VsGsSALUBusy", "VertexGeometry", "The percentage of GPUTime scalar ALU instructions are being processed for the VS and GS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,+,NUM_CUS,/,2,/,(100),*,(0),3,ifnotzero", "49521e07-5a41-0c17-38d9-450718dcb5ab");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6725);
        internal_counters.push_back(6213);
        internal_counters.push_back(4841);

        c.DefineDerivedCounter("VsGsSALUBusyCycles", "VertexGeometry", "Number of GPU cycles where scalar ALU instructions are being processed for the VS and GS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,+,NUM_CUS,/,(0),2,ifnotzero", "c4f78496-7f24-cb3d-3108-e9e8c761cf07");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8265);
        internal_counters.push_back(8205);

        c.DefineDerivedCounter("PreTessVALUInstCount", "PreTessellation", "Average number of vector ALU instructions executed for the VS and HS in a pipeline that uses tessellation. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "a6894a29-4213-27d4-e186-b9ca6112e3f3");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8261);
        internal_counters.push_back(8205);

        c.DefineDerivedCounter("PreTessSALUInstCount", "PreTessellation", "Average number of scalar ALU instructions executed for the VS and HS in a pipeline that uses tessellation. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "c6d06968-3557-fb5d-7a28-5eda098190db");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8318);
        internal_counters.push_back(8205);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("PreTessVALUBusy", "PreTessellation", "The percentage of GPUTime vector ALU instructions are being processed for the VS and HS in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,NUM_SIMDS,/,2,/,(100),*,1,ifnotzero", "72627e0a-da7e-899a-738c-69e8ba96bf42");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8318);
        internal_counters.push_back(8205);

        c.DefineDerivedCounter("PreTessVALUBusyCycles", "PreTessellation", "Number of GPU cycles vector where ALU instructions are being processed for the VS and HS in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,NUM_SIMDS,/,1,ifnotzero", "2d750b51-a75e-380b-1b42-40d59f4fbdb6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8261);
        internal_counters.push_back(8205);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("PreTessSALUBusy", "PreTessellation", "The percentage of GPUTime scalar ALU instructions are being processed for the VS and HS in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,NUM_CUS,/,2,/,(100),*,1,ifnotzero", "74e778bb-ce25-32cd-caa6-810eb44c95fa");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8261);
        internal_counters.push_back(8205);

        c.DefineDerivedCounter("PreTessSALUBusyCycles", "PreTessellation", "Number of GPU cycles where scalar ALU instructions are being processed for the VS and HS in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,NUM_CUS,/,1,ifnotzero", "8aa4a036-313f-f4b0-a820-ff0a6e71b1a2");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6217);
        internal_counters.push_back(6157);

        c.DefineDerivedCounter("PostTessVALUInstCount", "PostTessellation", "Average number of vector ALU instructions executed for the DS and GS in a pipeline that uses tessellation. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "718b7237-1371-4c85-3ad1-f12af258ba08");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6213);
        internal_counters.push_back(6157);

        c.DefineDerivedCounter("PostTessSALUInstCount", "PostTessellation", "Average number of scalar ALU instructions executed for the DS and GS in a pipeline that uses tessellation. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "546cecd8-53d4-c7b7-3b2e-f5b2db6c8282");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6270);
        internal_counters.push_back(6157);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("PostTessVALUBusy", "PostTessellation", "The percentage of GPUTime vector ALU instructions are being processed for the DS and GS in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,NUM_SIMDS,/,2,/,(100),*,1,ifnotzero", "068d1738-da17-7b6d-9d88-4013a8b27bf8");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6270);
        internal_counters.push_back(6157);

        c.DefineDerivedCounter("PostTessVALUBusyCycles", "PostTessellation", "Number of GPU cycles vector where ALU instructions are being processed for the DS and GS in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,NUM_SIMDS,/,1,ifnotzero", "29951e35-e415-22e9-ea59-03955faa8973");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6213);
        internal_counters.push_back(6157);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("PostTessSALUBusy", "PostTessellation", "The percentage of GPUTime scalar ALU instructions are being processed for the DS and GS in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,NUM_CUS,/,2,/,(100),*,1,ifnotzero", "776fb8e3-1541-75e5-8a4c-28d43d39662b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6213);
        internal_counters.push_back(6157);

        c.DefineDerivedCounter("PostTessSALUBusyCycles", "PostTessellation", "Number of GPU cycles where scalar ALU instructions are being processed for the DS and GS in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,NUM_CUS,/,1,ifnotzero", "fce0317e-c679-a310-fd96-85bbb4a8b79d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3535);
        internal_counters.push_back(3539);
        internal_counters.push_back(3491);
        internal_counters.push_back(3503);
        internal_counters.push_back(3492);
        internal_counters.push_back(3504);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("PrimitiveAssemblyBusy", "Timing", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max,6,/,(100),*,(100),min", "54ac5640-c4d7-95e2-20e0-6a9fdfc07333");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3535);
        internal_counters.push_back(3539);
        internal_counters.push_back(3491);
        internal_counters.push_back(3503);
        internal_counters.push_back(3492);
        internal_counters.push_back(3504);

        c.DefineDerivedCounter("PrimitiveAssemblyBusyCycles", "Timing", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max", "99777f2d-9626-c78a-a97c-c4505eba1e5f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3444);
        internal_counters.push_back(3484);
        internal_counters.push_back(3485);
        internal_counters.push_back(3486);
        internal_counters.push_back(3487);

        c.DefineDerivedCounter("CulledPrims", "PrimitiveAssembly", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,+,2,+,3,+,4,+", "589bdf55-9192-280a-41c3-584bc94f2562");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3451);

        c.DefineDerivedCounter("ClippedPrims", "PrimitiveAssembly", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "5ef6f9d5-155e-5baa-163f-8359d9ea9bbf");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3539);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("PAStalledOnRasterizer", "PrimitiveAssembly", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_PRIM_PIPES,/,1,/,(100),*", "6f9f416b-53c1-0457-f88c-7b6ba8973974");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3539);

        c.DefineDerivedCounter("PAStalledOnRasterizerCycles", "PrimitiveAssembly", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_PRIM_PIPES,/", "7a8c492a-c566-9328-6805-760dbff5c0f2");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9237);
        internal_counters.push_back(9242);
        internal_counters.push_back(9247);
        internal_counters.push_back(9252);

        c.DefineDerivedCounter("PSPixelsOut", "PixelShader", "Pixels exported from shader to color buffers. Does not include killed or alpha tested pixels; if there are multiple render targets, each render target receives one export, so this will be 2 for 1 pixel written to two RTs.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "24cba16c-baa6-6ecd-95ad-92ecb1338da1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9239);
        internal_counters.push_back(9244);
        internal_counters.push_back(9249);
        internal_counters.push_back(9254);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("PSExportStalls", "PixelShader", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,max4,4,/,NUM_SHADER_ENGINES,/,(100),*", "9b4f466c-ff97-22bb-557d-84d3c4c51895");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9239);
        internal_counters.push_back(9244);
        internal_counters.push_back(9249);
        internal_counters.push_back(9254);

        c.DefineDerivedCounter("PSExportStallsCycles", "PixelShader", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "47c72aad-64e6-0864-d533-d8e0bc27c156");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7241);
        internal_counters.push_back(7181);

        c.DefineDerivedCounter("PSVALUInstCount", "PixelShader", "Average number of vector ALU instructions executed in the PS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "eb74389e-435c-4137-ecf1-39eb5bc1cbfe");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7237);
        internal_counters.push_back(7181);

        c.DefineDerivedCounter("PSSALUInstCount", "PixelShader", "Average number of scalar ALU instructions executed in the PS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "e6a06580-8a82-96d6-976c-acc121fc5516");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7294);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("PSVALUBusy", "PixelShader", "The percentage of GPUTime vector ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_SIMDS,/,1,/,(100),*", "6ce6fef7-8e33-10b4-f351-af755e177e85");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7294);

        c.DefineDerivedCounter("PSVALUBusyCycles", "PixelShader", "Number of GPU cycles where vector ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_SIMDS,/", "1e276f86-cd2a-72e7-fc9d-004f666f2981");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7237);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("PSSALUBusy", "PixelShader", "The percentage of GPUTime scalar ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "2ff9f34f-e94b-af4d-18c2-5fbbf6d1727a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7237);

        c.DefineDerivedCounter("PSSALUBusyCycles", "PixelShader", "Number of GPU cycles where scalar ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_CUS,/", "29808906-f128-b078-fc79-820a4b3b3b8d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4846);
        internal_counters.push_back(4852);

        c.DefineDerivedCounter("CSThreadGroups", "ComputeShader", "Total number of thread groups.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,+", "8ce3fc80-56b2-97f9-8e70-2e8c747cea68");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8717);

        c.DefineDerivedCounter("CSWavefronts", "ComputeShader", "The total number of wavefronts used for the CS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "42379c6e-369b-c237-8b25-cdb9cdc65c4d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8721);

        c.DefineDerivedCounter("CSThreads", "ComputeShader", "The number of CS threads processed by the hardware.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "7a648013-6eac-2665-ac36-13c6f4ac9c26");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8721);
        internal_counters.push_back(4846);
        internal_counters.push_back(4852);

        c.DefineDerivedCounter("CSThreadGroupSize", "ComputeShader", "The number of CS threads within each thread group.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,2,+,/,1,2,+,ifnotzero", "8c65008a-9957-7ca6-4199-f6fe940420f6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8777);
        internal_counters.push_back(8717);

        c.DefineDerivedCounter("CSVALUInsts", "ComputeShader", "The average number of vector ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "376cb1cc-5a40-9d1d-404c-f1736c0c5084");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8795);
        internal_counters.push_back(8830);
        internal_counters.push_back(5134);

        c.DefineDerivedCounter("CSVALUUtilization", "ComputeShader", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,(64),(32),2,ifnotzero,*,/,(100),*,1,ifnotzero,(100),min", "ae943d2a-76e1-bb68-e1e2-0e06c9031611");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8773);
        internal_counters.push_back(8717);

        c.DefineDerivedCounter("CSSALUInsts", "ComputeShader", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "eb211144-8136-ff86-e8bf-4d0493a904cb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8782);
        internal_counters.push_back(8717);

        c.DefineDerivedCounter("CSVFetchInsts", "ComputeShader", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "3e2829c0-6215-783b-c271-6d57ff2c520e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8774);
        internal_counters.push_back(8717);

        c.DefineDerivedCounter("CSSFetchInsts", "ComputeShader", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "da09171c-6a0a-584f-fddc-dc5062d63a3e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8783);
        internal_counters.push_back(8717);

        c.DefineDerivedCounter("CSVWriteInsts", "ComputeShader", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "43438c22-e910-b377-b767-b32902e0df0d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8830);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("CSVALUBusy", "ComputeShader", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_SIMDS,/,1,/,(100),*", "f1e64815-f6a8-c277-d4f9-d054b443e205");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8830);

        c.DefineDerivedCounter("CSVALUBusyCycles", "ComputeShader", "Number of GPU cycles where vector ALU instructions are processed.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_SIMDS,/", "2d0d5852-2658-eb73-68d2-f23f7118c9c3");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8773);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("CSSALUBusy", "ComputeShader", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "3fc35f4e-9882-94e3-6f5f-4e81cd97082a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8773);

        c.DefineDerivedCounter("CSSALUBusyCycles", "ComputeShader", "Number of GPU cycles where scalar ALU instructions are processed.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_CUS,/", "de58f8fc-8ed4-a799-648d-62ded7b1c4c4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9465);
        internal_counters.push_back(9691);
        internal_counters.push_back(9917);
        internal_counters.push_back(10143);
        internal_counters.push_back(10369);
        internal_counters.push_back(10595);
        internal_counters.push_back(10821);
        internal_counters.push_back(11047);
        internal_counters.push_back(11273);
        internal_counters.push_back(11499);
        internal_counters.push_back(11725);
        internal_counters.push_back(11951);
        internal_counters.push_back(12177);
        internal_counters.push_back(12403);
        internal_counters.push_back(12629);
        internal_counters.push_back(12855);
        internal_counters.push_back(1868);
        internal_counters.push_back(4846);
        internal_counters.push_back(4852);

        c.DefineDerivedCounter("CSMemUnitBusy", "ComputeShader", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*,17,18,+,ifnotzero", "42ab96e1-0a24-96c8-c4ff-098fa267d78e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9465);
        internal_counters.push_back(9691);
        internal_counters.push_back(9917);
        internal_counters.push_back(10143);
        internal_counters.push_back(10369);
        internal_counters.push_back(10595);
        internal_counters.push_back(10821);
        internal_counters.push_back(11047);
        internal_counters.push_back(11273);
        internal_counters.push_back(11499);
        internal_counters.push_back(11725);
        internal_counters.push_back(11951);
        internal_counters.push_back(12177);
        internal_counters.push_back(12403);
        internal_counters.push_back(12629);
        internal_counters.push_back(12855);
        internal_counters.push_back(4846);
        internal_counters.push_back(4852);

        c.DefineDerivedCounter("CSMemUnitBusyCycles", "ComputeShader", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ARRAYS,/,16,17,+,ifnotzero", "39d5687f-c727-7c0c-af82-bb711d3897ed");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14078);
        internal_counters.push_back(14155);
        internal_counters.push_back(14232);
        internal_counters.push_back(14309);
        internal_counters.push_back(14386);
        internal_counters.push_back(14463);
        internal_counters.push_back(14540);
        internal_counters.push_back(14617);
        internal_counters.push_back(14694);
        internal_counters.push_back(14771);
        internal_counters.push_back(14848);
        internal_counters.push_back(14925);
        internal_counters.push_back(15002);
        internal_counters.push_back(15079);
        internal_counters.push_back(15156);
        internal_counters.push_back(15233);
        internal_counters.push_back(1868);
        internal_counters.push_back(4846);
        internal_counters.push_back(4852);

        c.DefineDerivedCounter("CSMemUnitStalled", "ComputeShader", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*,17,18,+,ifnotzero", "f18e8679-1511-d533-d9ee-4365197f7d0c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14078);
        internal_counters.push_back(14155);
        internal_counters.push_back(14232);
        internal_counters.push_back(14309);
        internal_counters.push_back(14386);
        internal_counters.push_back(14463);
        internal_counters.push_back(14540);
        internal_counters.push_back(14617);
        internal_counters.push_back(14694);
        internal_counters.push_back(14771);
        internal_counters.push_back(14848);
        internal_counters.push_back(14925);
        internal_counters.push_back(15002);
        internal_counters.push_back(15079);
        internal_counters.push_back(15156);
        internal_counters.push_back(15233);
        internal_counters.push_back(4846);
        internal_counters.push_back(4852);

        c.DefineDerivedCounter("CSMemUnitStalledCycles", "ComputeShader", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ARRAYS,/,16,17,+,ifnotzero", "51991c84-ed2b-bf31-c4ab-8f8e9eb8f29f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16384);
        internal_counters.push_back(16619);
        internal_counters.push_back(16854);
        internal_counters.push_back(17089);
        internal_counters.push_back(17324);
        internal_counters.push_back(17559);
        internal_counters.push_back(17794);
        internal_counters.push_back(18029);
        internal_counters.push_back(18264);
        internal_counters.push_back(18499);
        internal_counters.push_back(18734);
        internal_counters.push_back(18969);
        internal_counters.push_back(19204);
        internal_counters.push_back(19439);
        internal_counters.push_back(19674);
        internal_counters.push_back(19909);
        internal_counters.push_back(1868);
        internal_counters.push_back(4846);
        internal_counters.push_back(4852);

        c.DefineDerivedCounter("CSWriteUnitStalled", "ComputeShader", "The percentage of GPUTime the write unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,18,+,ifnotzero", "55118f7a-8f92-726f-78c6-407f689a2eb4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16384);
        internal_counters.push_back(16619);
        internal_counters.push_back(16854);
        internal_counters.push_back(17089);
        internal_counters.push_back(17324);
        internal_counters.push_back(17559);
        internal_counters.push_back(17794);
        internal_counters.push_back(18029);
        internal_counters.push_back(18264);
        internal_counters.push_back(18499);
        internal_counters.push_back(18734);
        internal_counters.push_back(18969);
        internal_counters.push_back(19204);
        internal_counters.push_back(19439);
        internal_counters.push_back(19674);
        internal_counters.push_back(19909);
        internal_counters.push_back(4846);
        internal_counters.push_back(4852);

        c.DefineDerivedCounter("CSWriteUnitStalledCycles", "ComputeShader", "Number of GPU cycles the write unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,17,+,ifnotzero", "be164c60-5e48-acac-9622-29616d09aa9a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8768);
        internal_counters.push_back(8717);

        c.DefineDerivedCounter("CSGDSInsts", "ComputeShader", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "2a867f3e-4a37-ad16-55d1-f03d74707819");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8772);
        internal_counters.push_back(8717);

        c.DefineDerivedCounter("CSLDSInsts", "ComputeShader", "The average number of LDS read/write instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "61b0b351-7e06-ef8e-a8e0-7a9e3200a836");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8744);
        internal_counters.push_back(8717);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("CSALUStalledByLDS", "ComputeShader", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,/,2,/,NUM_SHADER_ENGINES,/,(100),*,1,ifnotzero", "6dc4f1c2-bad0-c9ff-156e-883b319a752a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8744);

        c.DefineDerivedCounter("CSALUStalledByLDSCycles", "ComputeShader", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_SHADER_ENGINES,/", "8f3d5f25-2159-0374-fafe-e26a7799b6c8");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8998);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("CSLDSBankConflict", "ComputeShader", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,/,NUM_SIMDS,/,(100),*", "1065ee10-2e41-ea41-1eb3-b61b491752f4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8998);

        c.DefineDerivedCounter("CSLDSBankConflictCycles", "ComputeShader", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad).", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_SIMDS,/", "1fd1adf3-c51e-94fd-083e-c482a0a0809e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9465);
        internal_counters.push_back(9691);
        internal_counters.push_back(9917);
        internal_counters.push_back(10143);
        internal_counters.push_back(10369);
        internal_counters.push_back(10595);
        internal_counters.push_back(10821);
        internal_counters.push_back(11047);
        internal_counters.push_back(11273);
        internal_counters.push_back(11499);
        internal_counters.push_back(11725);
        internal_counters.push_back(11951);
        internal_counters.push_back(12177);
        internal_counters.push_back(12403);
        internal_counters.push_back(12629);
        internal_counters.push_back(12855);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("TexUnitBusy", "Timing", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "36afb8d9-42fc-aafe-66c5-449542153b2c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9465);
        internal_counters.push_back(9691);
        internal_counters.push_back(9917);
        internal_counters.push_back(10143);
        internal_counters.push_back(10369);
        internal_counters.push_back(10595);
        internal_counters.push_back(10821);
        internal_counters.push_back(11047);
        internal_counters.push_back(11273);
        internal_counters.push_back(11499);
        internal_counters.push_back(11725);
        internal_counters.push_back(11951);
        internal_counters.push_back(12177);
        internal_counters.push_back(12403);
        internal_counters.push_back(12629);
        internal_counters.push_back(12855);

        c.DefineDerivedCounter("TexUnitBusyCycles", "Timing", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ARRAYS,/", "c68761f2-248c-4f39-6528-c308b1c0807c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9519);
        internal_counters.push_back(9745);
        internal_counters.push_back(9971);
        internal_counters.push_back(10197);
        internal_counters.push_back(10423);
        internal_counters.push_back(10649);
        internal_counters.push_back(10875);
        internal_counters.push_back(11101);
        internal_counters.push_back(11327);
        internal_counters.push_back(11553);
        internal_counters.push_back(11779);
        internal_counters.push_back(12005);
        internal_counters.push_back(12231);
        internal_counters.push_back(12457);
        internal_counters.push_back(12683);
        internal_counters.push_back(12909);
        internal_counters.push_back(9518);
        internal_counters.push_back(9744);
        internal_counters.push_back(9970);
        internal_counters.push_back(10196);
        internal_counters.push_back(10422);
        internal_counters.push_back(10648);
        internal_counters.push_back(10874);
        internal_counters.push_back(11100);
        internal_counters.push_back(11326);
        internal_counters.push_back(11552);
        internal_counters.push_back(11778);
        internal_counters.push_back(12004);
        internal_counters.push_back(12230);
        internal_counters.push_back(12456);
        internal_counters.push_back(12682);
        internal_counters.push_back(12908);

        c.DefineDerivedCounter("TexTriFilteringPct", "TextureUnit", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,+,/,(100),*", "1affc3c8-b917-5c81-622b-7004527208ae");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9519);
        internal_counters.push_back(9745);
        internal_counters.push_back(9971);
        internal_counters.push_back(10197);
        internal_counters.push_back(10423);
        internal_counters.push_back(10649);
        internal_counters.push_back(10875);
        internal_counters.push_back(11101);
        internal_counters.push_back(11327);
        internal_counters.push_back(11553);
        internal_counters.push_back(11779);
        internal_counters.push_back(12005);
        internal_counters.push_back(12231);
        internal_counters.push_back(12457);
        internal_counters.push_back(12683);
        internal_counters.push_back(12909);

        c.DefineDerivedCounter("TexTriFilteringCount", "TextureUnit", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "5785b3a1-a513-18db-4b1c-bdeef75bb2b6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9518);
        internal_counters.push_back(9744);
        internal_counters.push_back(9970);
        internal_counters.push_back(10196);
        internal_counters.push_back(10422);
        internal_counters.push_back(10648);
        internal_counters.push_back(10874);
        internal_counters.push_back(11100);
        internal_counters.push_back(11326);
        internal_counters.push_back(11552);
        internal_counters.push_back(11778);
        internal_counters.push_back(12004);
        internal_counters.push_back(12230);
        internal_counters.push_back(12456);
        internal_counters.push_back(12682);
        internal_counters.push_back(12908);

        c.DefineDerivedCounter("NoTexTriFilteringCount", "TextureUnit", "Count of pixels that did not receive trilinear filtering.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "179da29a-81af-c06e-ce8c-a0a731ea030d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9521);
        internal_counters.push_back(9747);
        internal_counters.push_back(9973);
        internal_counters.push_back(10199);
        internal_counters.push_back(10425);
        internal_counters.push_back(10651);
        internal_counters.push_back(10877);
        internal_counters.push_back(11103);
        internal_counters.push_back(11329);
        internal_counters.push_back(11555);
        internal_counters.push_back(11781);
        internal_counters.push_back(12007);
        internal_counters.push_back(12233);
        internal_counters.push_back(12459);
        internal_counters.push_back(12685);
        internal_counters.push_back(12911);
        internal_counters.push_back(9520);
        internal_counters.push_back(9746);
        internal_counters.push_back(9972);
        internal_counters.push_back(10198);
        internal_counters.push_back(10424);
        internal_counters.push_back(10650);
        internal_counters.push_back(10876);
        internal_counters.push_back(11102);
        internal_counters.push_back(11328);
        internal_counters.push_back(11554);
        internal_counters.push_back(11780);
        internal_counters.push_back(12006);
        internal_counters.push_back(12232);
        internal_counters.push_back(12458);
        internal_counters.push_back(12684);
        internal_counters.push_back(12910);

        c.DefineDerivedCounter("TexVolFilteringPct", "TextureUnit", "Percentage of pixels that received volume filtering.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,+,/,(100),*", "b5ff6bed-3178-aee4-42dd-c74391c02a2d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9521);
        internal_counters.push_back(9747);
        internal_counters.push_back(9973);
        internal_counters.push_back(10199);
        internal_counters.push_back(10425);
        internal_counters.push_back(10651);
        internal_counters.push_back(10877);
        internal_counters.push_back(11103);
        internal_counters.push_back(11329);
        internal_counters.push_back(11555);
        internal_counters.push_back(11781);
        internal_counters.push_back(12007);
        internal_counters.push_back(12233);
        internal_counters.push_back(12459);
        internal_counters.push_back(12685);
        internal_counters.push_back(12911);

        c.DefineDerivedCounter("TexVolFilteringCount", "TextureUnit", "Count of pixels that received volume filtering.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "4bddc587-d589-8128-e18c-762eab2c871f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9520);
        internal_counters.push_back(9746);
        internal_counters.push_back(9972);
        internal_counters.push_back(10198);
        internal_counters.push_back(10424);
        internal_counters.push_back(10650);
        internal_counters.push_back(10876);
        internal_counters.push_back(11102);
        internal_counters.push_back(11328);
        internal_counters.push_back(11554);
        internal_counters.push_back(11780);
        internal_counters.push_back(12006);
        internal_counters.push_back(12232);
        internal_counters.push_back(12458);
        internal_counters.push_back(12684);
        internal_counters.push_back(12910);

        c.DefineDerivedCounter("NoTexVolFilteringCount", "TextureUnit", "Count of pixels that did not receive volume filtering.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "9fe1a854-17c6-9d26-b2b9-80610cd5827d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9539);
        internal_counters.push_back(9765);
        internal_counters.push_back(9991);
        internal_counters.push_back(10217);
        internal_counters.push_back(10443);
        internal_counters.push_back(10669);
        internal_counters.push_back(10895);
        internal_counters.push_back(11121);
        internal_counters.push_back(11347);
        internal_counters.push_back(11573);
        internal_counters.push_back(11799);
        internal_counters.push_back(12025);
        internal_counters.push_back(12251);
        internal_counters.push_back(12477);
        internal_counters.push_back(12703);
        internal_counters.push_back(12929);
        internal_counters.push_back(9540);
        internal_counters.push_back(9766);
        internal_counters.push_back(9992);
        internal_counters.push_back(10218);
        internal_counters.push_back(10444);
        internal_counters.push_back(10670);
        internal_counters.push_back(10896);
        internal_counters.push_back(11122);
        internal_counters.push_back(11348);
        internal_counters.push_back(11574);
        internal_counters.push_back(11800);
        internal_counters.push_back(12026);
        internal_counters.push_back(12252);
        internal_counters.push_back(12478);
        internal_counters.push_back(12704);
        internal_counters.push_back(12930);
        internal_counters.push_back(9541);
        internal_counters.push_back(9767);
        internal_counters.push_back(9993);
        internal_counters.push_back(10219);
        internal_counters.push_back(10445);
        internal_counters.push_back(10671);
        internal_counters.push_back(10897);
        internal_counters.push_back(11123);
        internal_counters.push_back(11349);
        internal_counters.push_back(11575);
        internal_counters.push_back(11801);
        internal_counters.push_back(12027);
        internal_counters.push_back(12253);
        internal_counters.push_back(12479);
        internal_counters.push_back(12705);
        internal_counters.push_back(12931);
        internal_counters.push_back(9542);
        internal_counters.push_back(9768);
        internal_counters.push_back(9994);
        internal_counters.push_back(10220);
        internal_counters.push_back(10446);
        internal_counters.push_back(10672);
        internal_counters.push_back(10898);
        internal_counters.push_back(11124);
        internal_counters.push_back(11350);
        internal_counters.push_back(11576);
        internal_counters.push_back(11802);
        internal_counters.push_back(12028);
        internal_counters.push_back(12254);
        internal_counters.push_back(12480);
        internal_counters.push_back(12706);
        internal_counters.push_back(12932);
        internal_counters.push_back(9543);
        internal_counters.push_back(9769);
        internal_counters.push_back(9995);
        internal_counters.push_back(10221);
        internal_counters.push_back(10447);
        internal_counters.push_back(10673);
        internal_counters.push_back(10899);
        internal_counters.push_back(11125);
        internal_counters.push_back(11351);
        internal_counters.push_back(11577);
        internal_counters.push_back(11803);
        internal_counters.push_back(12029);
        internal_counters.push_back(12255);
        internal_counters.push_back(12481);
        internal_counters.push_back(12707);
        internal_counters.push_back(12933);
        internal_counters.push_back(9544);
        internal_counters.push_back(9770);
        internal_counters.push_back(9996);
        internal_counters.push_back(10222);
        internal_counters.push_back(10448);
        internal_counters.push_back(10674);
        internal_counters.push_back(10900);
        internal_counters.push_back(11126);
        internal_counters.push_back(11352);
        internal_counters.push_back(11578);
        internal_counters.push_back(11804);
        internal_counters.push_back(12030);
        internal_counters.push_back(12256);
        internal_counters.push_back(12482);
        internal_counters.push_back(12708);
        internal_counters.push_back(12934);
        internal_counters.push_back(9545);
        internal_counters.push_back(9771);
        internal_counters.push_back(9997);
        internal_counters.push_back(10223);
        internal_counters.push_back(10449);
        internal_counters.push_back(10675);
        internal_counters.push_back(10901);
        internal_counters.push_back(11127);
        internal_counters.push_back(11353);
        internal_counters.push_back(11579);
        internal_counters.push_back(11805);
        internal_counters.push_back(12031);
        internal_counters.push_back(12257);
        internal_counters.push_back(12483);
        internal_counters.push_back(12709);
        internal_counters.push_back(12935);
        internal_counters.push_back(9546);
        internal_counters.push_back(9772);
        internal_counters.push_back(9998);
        internal_counters.push_back(10224);
        internal_counters.push_back(10450);
        internal_counters.push_back(10676);
        internal_counters.push_back(10902);
        internal_counters.push_back(11128);
        internal_counters.push_back(11354);
        internal_counters.push_back(11580);
        internal_counters.push_back(11806);
        internal_counters.push_back(12032);
        internal_counters.push_back(12258);
        internal_counters.push_back(12484);
        internal_counters.push_back(12710);
        internal_counters.push_back(12936);
        internal_counters.push_back(9547);
        internal_counters.push_back(9773);
        internal_counters.push_back(9999);
        internal_counters.push_back(10225);
        internal_counters.push_back(10451);
        internal_counters.push_back(10677);
        internal_counters.push_back(10903);
        internal_counters.push_back(11129);
        internal_counters.push_back(11355);
        internal_counters.push_back(11581);
        internal_counters.push_back(11807);
        internal_counters.push_back(12033);
        internal_counters.push_back(12259);
        internal_counters.push_back(12485);
        internal_counters.push_back(12711);
        internal_counters.push_back(12937);

        c.DefineDerivedCounter("TexAveAnisotropy", "TextureUnit", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(2),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,*,+,(4),32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,*,+,(6),48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,*,+,(8),64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,*,+,(10),80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,*,+,(12),96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,*,+,(14),112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,*,+,(16),128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,*,+,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,+,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,+,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,+,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,+,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,+,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,+,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,+,/", "7ca2a2b9-a4eb-ce23-d163-59147e672396");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2028);
        internal_counters.push_back(2398);
        internal_counters.push_back(2768);
        internal_counters.push_back(3138);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("DepthStencilTestBusy", "Timing", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "6834fb52-42e8-bb50-fd48-ec2f2904e7e0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2028);
        internal_counters.push_back(2398);
        internal_counters.push_back(2768);
        internal_counters.push_back(3138);

        c.DefineDerivedCounter("DepthStencilTestBusyCount", "Timing", "Number of GPU cycles spent performing depth and stencil tests.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "e02860fa-c7bd-90ea-2149-69b4e98a636c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1899);
        internal_counters.push_back(2269);
        internal_counters.push_back(2639);
        internal_counters.push_back(3009);
        internal_counters.push_back(1888);
        internal_counters.push_back(2258);
        internal_counters.push_back(2628);
        internal_counters.push_back(2998);

        c.DefineDerivedCounter("HiZTilesAccepted", "DepthAndStencil", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "4,5,6,7,sum4,0,1,2,3,sum4,-,(0),max,4,5,6,7,sum4,/,(100),*", "56176f45-d7ff-813d-4f05-3b2f046067e7");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1888);
        internal_counters.push_back(2258);
        internal_counters.push_back(2628);
        internal_counters.push_back(2998);
        internal_counters.push_back(1899);
        internal_counters.push_back(2269);
        internal_counters.push_back(2639);
        internal_counters.push_back(3009);

        c.DefineDerivedCounter("HiZTilesAcceptedCount", "DepthAndStencil", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4,4,5,6,7,sum4,-,(0),max", "95d4e3f6-b2f0-f26e-8423-aacdfaf79ea3");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1899);
        internal_counters.push_back(2269);
        internal_counters.push_back(2639);
        internal_counters.push_back(3009);

        c.DefineDerivedCounter("HiZTilesRejectedCount", "DepthAndStencil", "Count of tiles not accepted by HiZ.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "156ba142-7eeb-aa6e-a00a-f8aea4e41e0b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1888);
        internal_counters.push_back(2258);
        internal_counters.push_back(2628);
        internal_counters.push_back(2998);
        internal_counters.push_back(1912);
        internal_counters.push_back(2282);
        internal_counters.push_back(2652);
        internal_counters.push_back(3022);

        c.DefineDerivedCounter("PreZTilesDetailCulled", "DepthAndStencil", "Percentage of tiles rejected because the associated prim had no contributing area.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "4,5,6,7,sum4,0,1,2,3,sum4,/,(100),*", "cad7f54d-a044-7574-c472-6f2065cbeeac");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1912);
        internal_counters.push_back(2282);
        internal_counters.push_back(2652);
        internal_counters.push_back(3022);

        c.DefineDerivedCounter("PreZTilesDetailCulledCount", "DepthAndStencil", "Count of tiles rejected because the associated primitive had no contributing area.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "49262c8a-b1e6-90dd-f096-0fc4921715e9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1888);
        internal_counters.push_back(2258);
        internal_counters.push_back(2628);
        internal_counters.push_back(2998);

        c.DefineDerivedCounter("PreZTilesDetailSurvivingCount", "DepthAndStencil", "Count of tiles surviving because the associated primitive had contributing area.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "f803eaa4-bbed-bd39-775f-a64df92e2c08");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3855);
        internal_counters.push_back(4407);
        internal_counters.push_back(3856);
        internal_counters.push_back(4408);
        internal_counters.push_back(3857);
        internal_counters.push_back(4409);
        internal_counters.push_back(3858);
        internal_counters.push_back(4410);
        internal_counters.push_back(3931);
        internal_counters.push_back(4483);
        internal_counters.push_back(3932);
        internal_counters.push_back(4484);
        internal_counters.push_back(3933);
        internal_counters.push_back(4485);
        internal_counters.push_back(3934);
        internal_counters.push_back(4486);

        c.DefineDerivedCounter("HiZQuadsCulled", "DepthAndStencil", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,sum8,-,(0),max,0,1,2,3,4,5,6,7,sum8,/,(100),*", "fa0e319b-5573-6d34-5bab-904769925036");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3855);
        internal_counters.push_back(4407);
        internal_counters.push_back(3856);
        internal_counters.push_back(4408);
        internal_counters.push_back(3857);
        internal_counters.push_back(4409);
        internal_counters.push_back(3858);
        internal_counters.push_back(4410);
        internal_counters.push_back(3931);
        internal_counters.push_back(4483);
        internal_counters.push_back(3932);
        internal_counters.push_back(4484);
        internal_counters.push_back(3933);
        internal_counters.push_back(4485);
        internal_counters.push_back(3934);
        internal_counters.push_back(4486);

        c.DefineDerivedCounter("HiZQuadsCulledCount", "DepthAndStencil", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,sum8,-,(0),max", "73b0b39d-6df2-3e24-0b5c-7cb0ac8b6f39");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3931);
        internal_counters.push_back(4483);
        internal_counters.push_back(3932);
        internal_counters.push_back(4484);
        internal_counters.push_back(3933);
        internal_counters.push_back(4485);
        internal_counters.push_back(3934);
        internal_counters.push_back(4486);

        c.DefineDerivedCounter("HiZQuadsAcceptedCount", "DepthAndStencil", "Count of quads that did continue on in the pipeline after HiZ.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,sum8", "59049ad9-42b5-c7cb-3616-6a8f6a8e4894");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3931);
        internal_counters.push_back(4483);
        internal_counters.push_back(3932);
        internal_counters.push_back(4484);
        internal_counters.push_back(3933);
        internal_counters.push_back(4485);
        internal_counters.push_back(3934);
        internal_counters.push_back(4486);
        internal_counters.push_back(3955);
        internal_counters.push_back(4507);
        internal_counters.push_back(3855);
        internal_counters.push_back(4407);
        internal_counters.push_back(3856);
        internal_counters.push_back(4408);
        internal_counters.push_back(3857);
        internal_counters.push_back(4409);
        internal_counters.push_back(3858);
        internal_counters.push_back(4410);

        c.DefineDerivedCounter("PreZQuadsCulled", "DepthAndStencil", "Percentage of quads rejected based on the detailZ and earlyZ tests.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,9,+,-,(0),max,10,11,12,13,14,15,16,17,sum8,/,(100),*", "4e77547b-ec55-5663-f034-af59be66d77d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3931);
        internal_counters.push_back(4483);
        internal_counters.push_back(3932);
        internal_counters.push_back(4484);
        internal_counters.push_back(3933);
        internal_counters.push_back(4485);
        internal_counters.push_back(3934);
        internal_counters.push_back(4486);
        internal_counters.push_back(3955);
        internal_counters.push_back(4507);

        c.DefineDerivedCounter("PreZQuadsCulledCount", "DepthAndStencil", "Count of quads rejected based on the detailZ and earlyZ tests.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,9,sum2,-,(0),max", "1bf169e6-9304-834e-df5f-0c44d7890a08");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3955);
        internal_counters.push_back(4507);

        c.DefineDerivedCounter("PreZQuadsSurvivingCount", "DepthAndStencil", "Count of quads surviving detailZ and earlyZ tests.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,sum2", "50e25e51-3713-89cb-7f92-559cde5e5532");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3955);
        internal_counters.push_back(4507);
        internal_counters.push_back(3855);
        internal_counters.push_back(4407);
        internal_counters.push_back(3856);
        internal_counters.push_back(4408);
        internal_counters.push_back(3857);
        internal_counters.push_back(4409);
        internal_counters.push_back(3858);
        internal_counters.push_back(4410);

        c.DefineDerivedCounter("PostZQuads", "DepthAndStencil", "Percentage of quads for which the pixel shader will run and may be postZ tested.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,+,2,3,4,5,6,7,8,9,sum8,/,(100),*,(100),min", "58f0d34b-eeb8-e8db-abce-cb72584144be");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3955);
        internal_counters.push_back(4507);

        c.DefineDerivedCounter("PostZQuadCount", "DepthAndStencil", "Count of quads for which the pixel shader will run and may be postZ tested.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,+", "08404526-ce35-939b-34c8-a7a35a0ff4d6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2061);
        internal_counters.push_back(2431);
        internal_counters.push_back(2801);
        internal_counters.push_back(3171);

        c.DefineDerivedCounter("PreZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z before shading and passed.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "3bfe6c4d-7422-ca03-7ea5-e67ff1a00136");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2063);
        internal_counters.push_back(2433);
        internal_counters.push_back(2803);
        internal_counters.push_back(3173);

        c.DefineDerivedCounter("PreZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z before shading and failed stencil test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "df7f705e-5162-d3b5-da8b-63466cf9c4e5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2062);
        internal_counters.push_back(2432);
        internal_counters.push_back(2802);
        internal_counters.push_back(3172);

        c.DefineDerivedCounter("PreZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z before shading and failed Z test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "4484e950-f7a4-3800-bc74-78dd297f017e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2058);
        internal_counters.push_back(2428);
        internal_counters.push_back(2798);
        internal_counters.push_back(3168);

        c.DefineDerivedCounter("PostZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z after shading and passed.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "4995d5d6-2330-b986-508b-fae24856f44c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2060);
        internal_counters.push_back(2430);
        internal_counters.push_back(2800);
        internal_counters.push_back(3170);

        c.DefineDerivedCounter("PostZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z after shading and failed stencil test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "ae558af4-f4be-3dd4-7316-b2c4dcf0def8");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2059);
        internal_counters.push_back(2429);
        internal_counters.push_back(2799);
        internal_counters.push_back(3169);

        c.DefineDerivedCounter("PostZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z after shading and failed Z test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "b3684c94-814a-c695-c85d-a5b6ab798b35");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1930);
        internal_counters.push_back(2300);
        internal_counters.push_back(2670);
        internal_counters.push_back(3040);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("ZUnitStalled", "DepthAndStencil", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "5e86c3ad-1726-3157-1d01-7ed188bf854d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1930);
        internal_counters.push_back(2300);
        internal_counters.push_back(2670);
        internal_counters.push_back(3040);

        c.DefineDerivedCounter("ZUnitStalledCycles", "DepthAndStencil", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "4351fa7f-6737-2c3e-3ffb-b3addbdceedd");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1932);
        internal_counters.push_back(2302);
        internal_counters.push_back(2672);
        internal_counters.push_back(3042);
        internal_counters.push_back(1939);
        internal_counters.push_back(2309);
        internal_counters.push_back(2679);
        internal_counters.push_back(3049);

        c.DefineDerivedCounter("DBMemRead", "DepthAndStencil", "Number of bytes read from the depth buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,sum4,(256),*,4,5,6,7,sum4,(32),*,+", "dcdb4ee7-bd50-00f7-c028-9e5f4ce888c0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1944);
        internal_counters.push_back(2314);
        internal_counters.push_back(2684);
        internal_counters.push_back(3054);
        internal_counters.push_back(1947);
        internal_counters.push_back(2317);
        internal_counters.push_back(2687);
        internal_counters.push_back(3057);

        c.DefineDerivedCounter("DBMemWritten", "DepthAndStencil", "Number of bytes written to the depth buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,sum4,(32),*,4,5,6,7,sum4,(32),*,+", "de5717f8-8a49-ee44-4645-10de51b37dcf");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(128);
        internal_counters.push_back(589);
        internal_counters.push_back(1050);
        internal_counters.push_back(1511);

        c.DefineDerivedCounter("CBMemRead", "ColorBuffer", "Number of bytes read from the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,sum4,(32),*", "84b531d8-a1f8-7f49-7c27-7bc97801f1e6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(259);
        internal_counters.push_back(720);
        internal_counters.push_back(1181);
        internal_counters.push_back(1642);
        internal_counters.push_back(126);
        internal_counters.push_back(587);
        internal_counters.push_back(1048);
        internal_counters.push_back(1509);
        internal_counters.push_back(127);
        internal_counters.push_back(588);
        internal_counters.push_back(1049);
        internal_counters.push_back(1510);
        internal_counters.push_back(128);
        internal_counters.push_back(589);
        internal_counters.push_back(1050);
        internal_counters.push_back(1511);

        c.DefineDerivedCounter("CBColorAndMaskRead", "ColorBuffer", "Total number of bytes read from the color and mask buffers.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "da41660e-eb6f-32ec-8a64-b32ca17bd7eb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(118);
        internal_counters.push_back(579);
        internal_counters.push_back(1040);
        internal_counters.push_back(1501);

        c.DefineDerivedCounter("CBMemWritten", "ColorBuffer", "Number of bytes written to the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,sum4,(32),*", "550f8ff8-60b6-a6bf-87d0-25ac9e87de70");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(257);
        internal_counters.push_back(718);
        internal_counters.push_back(1179);
        internal_counters.push_back(1640);
        internal_counters.push_back(116);
        internal_counters.push_back(577);
        internal_counters.push_back(1038);
        internal_counters.push_back(1499);
        internal_counters.push_back(117);
        internal_counters.push_back(578);
        internal_counters.push_back(1039);
        internal_counters.push_back(1500);
        internal_counters.push_back(118);
        internal_counters.push_back(579);
        internal_counters.push_back(1040);
        internal_counters.push_back(1501);

        c.DefineDerivedCounter("CBColorAndMaskWritten", "ColorBuffer", "Total number of bytes written to the color and mask buffers.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "29a04b69-8f5f-b770-a0f2-3453e2c99e49");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(162);
        internal_counters.push_back(623);
        internal_counters.push_back(1084);
        internal_counters.push_back(1545);
        internal_counters.push_back(7);
        internal_counters.push_back(468);
        internal_counters.push_back(929);
        internal_counters.push_back(1390);

        c.DefineDerivedCounter("CBSlowPixelPct", "ColorBuffer", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*,(100),min", "5775943f-0313-7e52-9638-b24a449197bc");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(162);
        internal_counters.push_back(623);
        internal_counters.push_back(1084);
        internal_counters.push_back(1545);

        c.DefineDerivedCounter("CBSlowPixelCount", "ColorBuffer", "Number of pixels written to the color buffer using a half-rate or quarter-rate format.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "47eacbb0-28c8-22b4-5c69-c00d5813bb1c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14051);
        internal_counters.push_back(14128);
        internal_counters.push_back(14205);
        internal_counters.push_back(14282);
        internal_counters.push_back(14359);
        internal_counters.push_back(14436);
        internal_counters.push_back(14513);
        internal_counters.push_back(14590);
        internal_counters.push_back(14667);
        internal_counters.push_back(14744);
        internal_counters.push_back(14821);
        internal_counters.push_back(14898);
        internal_counters.push_back(14975);
        internal_counters.push_back(15052);
        internal_counters.push_back(15129);
        internal_counters.push_back(15206);
        internal_counters.push_back(14060);
        internal_counters.push_back(14137);
        internal_counters.push_back(14214);
        internal_counters.push_back(14291);
        internal_counters.push_back(14368);
        internal_counters.push_back(14445);
        internal_counters.push_back(14522);
        internal_counters.push_back(14599);
        internal_counters.push_back(14676);
        internal_counters.push_back(14753);
        internal_counters.push_back(14830);
        internal_counters.push_back(14907);
        internal_counters.push_back(14984);
        internal_counters.push_back(15061);
        internal_counters.push_back(15138);
        internal_counters.push_back(15215);

        c.DefineDerivedCounter("L0CacheHit", "MemoryCache", "The percentage of read requests that hit the data in the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "286c786e-9a42-3371-9dea-dd54e6e612e9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14051);
        internal_counters.push_back(14128);
        internal_counters.push_back(14205);
        internal_counters.push_back(14282);
        internal_counters.push_back(14359);
        internal_counters.push_back(14436);
        internal_counters.push_back(14513);
        internal_counters.push_back(14590);
        internal_counters.push_back(14667);
        internal_counters.push_back(14744);
        internal_counters.push_back(14821);
        internal_counters.push_back(14898);
        internal_counters.push_back(14975);
        internal_counters.push_back(15052);
        internal_counters.push_back(15129);
        internal_counters.push_back(15206);

        c.DefineDerivedCounter("L0CacheRequestCount", "MemoryCache", "The number of read requests made to the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "74983cae-ee57-2e1b-d990-5128fef84e1f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14051);
        internal_counters.push_back(14128);
        internal_counters.push_back(14205);
        internal_counters.push_back(14282);
        internal_counters.push_back(14359);
        internal_counters.push_back(14436);
        internal_counters.push_back(14513);
        internal_counters.push_back(14590);
        internal_counters.push_back(14667);
        internal_counters.push_back(14744);
        internal_counters.push_back(14821);
        internal_counters.push_back(14898);
        internal_counters.push_back(14975);
        internal_counters.push_back(15052);
        internal_counters.push_back(15129);
        internal_counters.push_back(15206);
        internal_counters.push_back(14060);
        internal_counters.push_back(14137);
        internal_counters.push_back(14214);
        internal_counters.push_back(14291);
        internal_counters.push_back(14368);
        internal_counters.push_back(14445);
        internal_counters.push_back(14522);
        internal_counters.push_back(14599);
        internal_counters.push_back(14676);
        internal_counters.push_back(14753);
        internal_counters.push_back(14830);
        internal_counters.push_back(14907);
        internal_counters.push_back(14984);
        internal_counters.push_back(15061);
        internal_counters.push_back(15138);
        internal_counters.push_back(15215);

        c.DefineDerivedCounter("L0CacheHitCount", "MemoryCache", "The number of read requests which result in a cache hit from the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-", "c0de7338-069b-c5ba-ead3-c65e030cd2ac");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14060);
        internal_counters.push_back(14137);
        internal_counters.push_back(14214);
        internal_counters.push_back(14291);
        internal_counters.push_back(14368);
        internal_counters.push_back(14445);
        internal_counters.push_back(14522);
        internal_counters.push_back(14599);
        internal_counters.push_back(14676);
        internal_counters.push_back(14753);
        internal_counters.push_back(14830);
        internal_counters.push_back(14907);
        internal_counters.push_back(14984);
        internal_counters.push_back(15061);
        internal_counters.push_back(15138);
        internal_counters.push_back(15215);

        c.DefineDerivedCounter("L0CacheMissCount", "MemoryCache", "The number of read requests which result in a cache miss from the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "a2f08766-ea1b-6eae-6eaf-faa04125d3e6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15891);
        internal_counters.push_back(15895);

        c.DefineDerivedCounter("L1CacheHit", "MemoryCache", "The percentage of read or write requests that hit the data in the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),1,0,/,-,(100),*,0,ifnotzero", "5a34915a-24b8-8baf-2bf8-5878e7894ae3");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15891);

        c.DefineDerivedCounter("L1CacheRequestCount", "MemoryCache", "The number of read or write requests made to the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "29c76c67-4611-205d-0b88-d08668df03c5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15891);
        internal_counters.push_back(15895);

        c.DefineDerivedCounter("L1CacheHitCount", "MemoryCache", "The number of read or write requests which result in a cache hit from the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,-", "1ae150c3-f2d0-82c6-a51b-a77fd8d5fc33");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15895);

        c.DefineDerivedCounter("L1CacheMissCount", "MemoryCache", "The number of read or write requests which result in a cache miss from the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "71bfec6d-257b-849d-e212-cdf5c1b1de65");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16340);
        internal_counters.push_back(16575);
        internal_counters.push_back(16810);
        internal_counters.push_back(17045);
        internal_counters.push_back(17280);
        internal_counters.push_back(17515);
        internal_counters.push_back(17750);
        internal_counters.push_back(17985);
        internal_counters.push_back(18220);
        internal_counters.push_back(18455);
        internal_counters.push_back(18690);
        internal_counters.push_back(18925);
        internal_counters.push_back(19160);
        internal_counters.push_back(19395);
        internal_counters.push_back(19630);
        internal_counters.push_back(19865);
        internal_counters.push_back(16308);
        internal_counters.push_back(16543);
        internal_counters.push_back(16778);
        internal_counters.push_back(17013);
        internal_counters.push_back(17248);
        internal_counters.push_back(17483);
        internal_counters.push_back(17718);
        internal_counters.push_back(17953);
        internal_counters.push_back(18188);
        internal_counters.push_back(18423);
        internal_counters.push_back(18658);
        internal_counters.push_back(18893);
        internal_counters.push_back(19128);
        internal_counters.push_back(19363);
        internal_counters.push_back(19598);
        internal_counters.push_back(19833);

        c.DefineDerivedCounter("L2CacheMiss", "MemoryCache", "The percentage of read or write requests that miss the data in the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size. Value range: 0% (optimal) to 100% (all miss).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*", "8aee5458-a58e-11b6-5131-7f19ed070117");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16308);
        internal_counters.push_back(16543);
        internal_counters.push_back(16778);
        internal_counters.push_back(17013);
        internal_counters.push_back(17248);
        internal_counters.push_back(17483);
        internal_counters.push_back(17718);
        internal_counters.push_back(17953);
        internal_counters.push_back(18188);
        internal_counters.push_back(18423);
        internal_counters.push_back(18658);
        internal_counters.push_back(18893);
        internal_counters.push_back(19128);
        internal_counters.push_back(19363);
        internal_counters.push_back(19598);
        internal_counters.push_back(19833);

        c.DefineDerivedCounter("L2CacheRequestCount", "MemoryCache", "The number of read or write requests made to the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "21e9219c-e725-0d96-06b1-b21698b736b2");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16308);
        internal_counters.push_back(16543);
        internal_counters.push_back(16778);
        internal_counters.push_back(17013);
        internal_counters.push_back(17248);
        internal_counters.push_back(17483);
        internal_counters.push_back(17718);
        internal_counters.push_back(17953);
        internal_counters.push_back(18188);
        internal_counters.push_back(18423);
        internal_counters.push_back(18658);
        internal_counters.push_back(18893);
        internal_counters.push_back(19128);
        internal_counters.push_back(19363);
        internal_counters.push_back(19598);
        internal_counters.push_back(19833);
        internal_counters.push_back(16340);
        internal_counters.push_back(16575);
        internal_counters.push_back(16810);
        internal_counters.push_back(17045);
        internal_counters.push_back(17280);
        internal_counters.push_back(17515);
        internal_counters.push_back(17750);
        internal_counters.push_back(17985);
        internal_counters.push_back(18220);
        internal_counters.push_back(18455);
        internal_counters.push_back(18690);
        internal_counters.push_back(18925);
        internal_counters.push_back(19160);
        internal_counters.push_back(19395);
        internal_counters.push_back(19630);
        internal_counters.push_back(19865);

        c.DefineDerivedCounter("L2CacheHitCount", "MemoryCache", "The number of read or write requests which result in a cache hit from the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-", "29ddcb92-d3dd-951b-1b23-efe52e4eeee4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16340);
        internal_counters.push_back(16575);
        internal_counters.push_back(16810);
        internal_counters.push_back(17045);
        internal_counters.push_back(17280);
        internal_counters.push_back(17515);
        internal_counters.push_back(17750);
        internal_counters.push_back(17985);
        internal_counters.push_back(18220);
        internal_counters.push_back(18455);
        internal_counters.push_back(18690);
        internal_counters.push_back(18925);
        internal_counters.push_back(19160);
        internal_counters.push_back(19395);
        internal_counters.push_back(19630);
        internal_counters.push_back(19865);

        c.DefineDerivedCounter("L2CacheMissCount", "MemoryCache", "The number of read or write requests which result in a cache miss from the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "376eec7b-ab25-9012-06b5-63291a17fd47");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16394);
        internal_counters.push_back(16629);
        internal_counters.push_back(16864);
        internal_counters.push_back(17099);
        internal_counters.push_back(17334);
        internal_counters.push_back(17569);
        internal_counters.push_back(17804);
        internal_counters.push_back(18039);
        internal_counters.push_back(18274);
        internal_counters.push_back(18509);
        internal_counters.push_back(18744);
        internal_counters.push_back(18979);
        internal_counters.push_back(19214);
        internal_counters.push_back(19449);
        internal_counters.push_back(19684);
        internal_counters.push_back(19919);
        internal_counters.push_back(16395);
        internal_counters.push_back(16630);
        internal_counters.push_back(16865);
        internal_counters.push_back(17100);
        internal_counters.push_back(17335);
        internal_counters.push_back(17570);
        internal_counters.push_back(17805);
        internal_counters.push_back(18040);
        internal_counters.push_back(18275);
        internal_counters.push_back(18510);
        internal_counters.push_back(18745);
        internal_counters.push_back(18980);
        internal_counters.push_back(19215);
        internal_counters.push_back(19450);
        internal_counters.push_back(19685);
        internal_counters.push_back(19920);
        internal_counters.push_back(16396);
        internal_counters.push_back(16631);
        internal_counters.push_back(16866);
        internal_counters.push_back(17101);
        internal_counters.push_back(17336);
        internal_counters.push_back(17571);
        internal_counters.push_back(17806);
        internal_counters.push_back(18041);
        internal_counters.push_back(18276);
        internal_counters.push_back(18511);
        internal_counters.push_back(18746);
        internal_counters.push_back(18981);
        internal_counters.push_back(19216);
        internal_counters.push_back(19451);
        internal_counters.push_back(19686);
        internal_counters.push_back(19921);
        internal_counters.push_back(16397);
        internal_counters.push_back(16632);
        internal_counters.push_back(16867);
        internal_counters.push_back(17102);
        internal_counters.push_back(17337);
        internal_counters.push_back(17572);
        internal_counters.push_back(17807);
        internal_counters.push_back(18042);
        internal_counters.push_back(18277);
        internal_counters.push_back(18512);
        internal_counters.push_back(18747);
        internal_counters.push_back(18982);
        internal_counters.push_back(19217);
        internal_counters.push_back(19452);
        internal_counters.push_back(19687);
        internal_counters.push_back(19922);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total bytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,(96),*,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,(128),*,sum4", "664bb3ef-6eca-86b1-1e2d-30cb897b5fa9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16380);
        internal_counters.push_back(16615);
        internal_counters.push_back(16850);
        internal_counters.push_back(17085);
        internal_counters.push_back(17320);
        internal_counters.push_back(17555);
        internal_counters.push_back(17790);
        internal_counters.push_back(18025);
        internal_counters.push_back(18260);
        internal_counters.push_back(18495);
        internal_counters.push_back(18730);
        internal_counters.push_back(18965);
        internal_counters.push_back(19200);
        internal_counters.push_back(19435);
        internal_counters.push_back(19670);
        internal_counters.push_back(19905);
        internal_counters.push_back(16381);
        internal_counters.push_back(16616);
        internal_counters.push_back(16851);
        internal_counters.push_back(17086);
        internal_counters.push_back(17321);
        internal_counters.push_back(17556);
        internal_counters.push_back(17791);
        internal_counters.push_back(18026);
        internal_counters.push_back(18261);
        internal_counters.push_back(18496);
        internal_counters.push_back(18731);
        internal_counters.push_back(18966);
        internal_counters.push_back(19201);
        internal_counters.push_back(19436);
        internal_counters.push_back(19671);
        internal_counters.push_back(19906);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total bytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+", "f96f2c16-b1b4-4ec4-229c-fc82e6f80a82");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9465);
        internal_counters.push_back(9691);
        internal_counters.push_back(9917);
        internal_counters.push_back(10143);
        internal_counters.push_back(10369);
        internal_counters.push_back(10595);
        internal_counters.push_back(10821);
        internal_counters.push_back(11047);
        internal_counters.push_back(11273);
        internal_counters.push_back(11499);
        internal_counters.push_back(11725);
        internal_counters.push_back(11951);
        internal_counters.push_back(12177);
        internal_counters.push_back(12403);
        internal_counters.push_back(12629);
        internal_counters.push_back(12855);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9465);
        internal_counters.push_back(9691);
        internal_counters.push_back(9917);
        internal_counters.push_back(10143);
        internal_counters.push_back(10369);
        internal_counters.push_back(10595);
        internal_counters.push_back(10821);
        internal_counters.push_back(11047);
        internal_counters.push_back(11273);
        internal_counters.push_back(11499);
        internal_counters.push_back(11725);
        internal_counters.push_back(11951);
        internal_counters.push_back(12177);
        internal_counters.push_back(12403);
        internal_counters.push_back(12629);
        internal_counters.push_back(12855);

        c.DefineDerivedCounter("MemUnitBusyCycles", "GlobalMemory", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalledCycles). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "168f077c-4797-b2f5-717f-105c725266c8");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14078);
        internal_counters.push_back(14155);
        internal_counters.push_back(14232);
        internal_counters.push_back(14309);
        internal_counters.push_back(14386);
        internal_counters.push_back(14463);
        internal_counters.push_back(14540);
        internal_counters.push_back(14617);
        internal_counters.push_back(14694);
        internal_counters.push_back(14771);
        internal_counters.push_back(14848);
        internal_counters.push_back(14925);
        internal_counters.push_back(15002);
        internal_counters.push_back(15079);
        internal_counters.push_back(15156);
        internal_counters.push_back(15233);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14078);
        internal_counters.push_back(14155);
        internal_counters.push_back(14232);
        internal_counters.push_back(14309);
        internal_counters.push_back(14386);
        internal_counters.push_back(14463);
        internal_counters.push_back(14540);
        internal_counters.push_back(14617);
        internal_counters.push_back(14694);
        internal_counters.push_back(14771);

        c.DefineDerivedCounter("MemUnitStalledCycles", "GlobalMemory", "Number of GPU cycles the memory unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,max10", "2745659a-0e40-bace-3b9b-86a54f8e4623");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16384);
        internal_counters.push_back(16619);
        internal_counters.push_back(16854);
        internal_counters.push_back(17089);
        internal_counters.push_back(17324);
        internal_counters.push_back(17559);
        internal_counters.push_back(17794);
        internal_counters.push_back(18029);
        internal_counters.push_back(18264);
        internal_counters.push_back(18499);
        internal_counters.push_back(18734);
        internal_counters.push_back(18969);
        internal_counters.push_back(19204);
        internal_counters.push_back(19439);
        internal_counters.push_back(19674);
        internal_counters.push_back(19909);
        internal_counters.push_back(1868);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16384);
        internal_counters.push_back(16619);
        internal_counters.push_back(16854);
        internal_counters.push_back(17089);
        internal_counters.push_back(17324);
        internal_counters.push_back(17559);
        internal_counters.push_back(17794);
        internal_counters.push_back(18029);
        internal_counters.push_back(18264);
        internal_counters.push_back(18499);
        internal_counters.push_back(18734);
        internal_counters.push_back(18969);
        internal_counters.push_back(19204);
        internal_counters.push_back(19439);
        internal_counters.push_back(19674);
        internal_counters.push_back(19909);

        c.DefineDerivedCounter("WriteUnitStalledCycles", "GlobalMemory", "Number of GPU cycles the Write unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "ede3305e-abd4-d6bf-6b00-ffc57a29fce3");
    }
}

