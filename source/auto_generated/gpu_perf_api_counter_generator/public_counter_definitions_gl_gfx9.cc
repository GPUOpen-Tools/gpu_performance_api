//==============================================================================
// Copyright (c) 2010-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for GL GFX9.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_gl_gfx9.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersGlGfx9(GpaDerivedCounters& c)
{
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16630);

        c.DefineDerivedCounter("GPUTime", "Timing", "Time this API command took to execute on the GPU in nanoseconds from the time the previous command reached the bottom of the pipeline (BOP) to the time this command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "0,TS_FREQ,/,(1000000000),*", "cbd338f2-de6c-7b14-92ad-ba724ca2e501");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1799);
        internal_counters.push_back(1776);

        c.DefineDerivedCounter("GPUBusy", "Timing", "The percentage of time the GPU command processor was busy.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,/,(100),*,(100),min", "b1ba5363-1abc-fe66-2fdd-1fe6ee8989a0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("GPUBusyCycles", "Timing", "Number of GPU cycles that the GPU command processor was busy.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0", "451cb045-23af-ac44-4603-d5832fa041d9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16417);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("TessellatorBusy", "Timing", "The percentage of time the tessellation engine is busy.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_PRIM_PIPES,/,1,/,(100),*", "36af6c72-dcfb-8102-4fd4-ce8ddc573365");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16417);

        c.DefineDerivedCounter("TessellatorBusyCycles", "Timing", "Number of GPU cycles that the tessellation engine is busy.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_PRIM_PIPES,/", "60289dcb-7b33-46e7-26d1-8a2121605543");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4018);
        internal_counters.push_back(4027);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("VSBusy", "Timing", "The percentage of time the ShaderUnit has vertex shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "94caad5e-867c-6c09-cf3a-d05b51df8f3b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4018);
        internal_counters.push_back(4027);

        c.DefineDerivedCounter("VSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has vertex shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,ifnotzero", "a2086d4e-274b-48a8-3e08-a4ab76ac15dd");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16630);
        internal_counters.push_back(4018);
        internal_counters.push_back(4027);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("VSTime", "Timing", "Time vertex shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "d6ce819e-69af-a241-d07a-5dd8d146e436");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4049);
        internal_counters.push_back(4055);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("HSBusy", "Timing", "The percentage of time the ShaderUnit has hull shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "16f30a0b-4cbf-eccd-b13f-ab68dd254d32");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4049);
        internal_counters.push_back(4055);

        c.DefineDerivedCounter("HSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has hull shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,ifnotzero", "753e76ef-8ef8-3f13-b511-4bd9f3589fdb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16630);
        internal_counters.push_back(4049);
        internal_counters.push_back(4055);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("HSTime", "Timing", "Time hull shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "8386a863-dd34-1526-f703-0f0c7b241bc4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4037);
        internal_counters.push_back(4040);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("GSBusy", "Timing", "The percentage of time the ShaderUnit has geometry shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "876f36d8-d046-833f-7832-673cbffd0a45");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4037);
        internal_counters.push_back(4040);

        c.DefineDerivedCounter("GSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has geometry shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,ifnotzero", "48203b6b-8983-c067-d63e-05da8be5111b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16630);
        internal_counters.push_back(4037);
        internal_counters.push_back(4040);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("GSTime", "Timing", "Time geometry shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "c73e715f-59af-76e8-9e22-097b94c066c4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4071);
        internal_counters.push_back(4076);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("PSBusy", "Timing", "The percentage of time the ShaderUnit has pixel shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "7e772beb-d82c-bd9a-aed0-fe504d416ce5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4071);
        internal_counters.push_back(4076);

        c.DefineDerivedCounter("PSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has pixel shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,ifnotzero", "b58bea04-ce8e-2984-80f4-8aba7d4c817b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16630);
        internal_counters.push_back(4071);
        internal_counters.push_back(4076);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("PSTime", "Timing", "Time pixel shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "edca7694-7416-e8a6-0c5a-63a5ad5f3d74");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4059);
        internal_counters.push_back(4063);
        internal_counters.push_back(4065);
        internal_counters.push_back(4069);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("CSBusy", "Timing", "The percentage of time the ShaderUnit has compute shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,max,4,/,(100),*,(100),min", "493fdd90-8d2b-a055-5e4e-2d29c3396b8c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4059);
        internal_counters.push_back(4063);
        internal_counters.push_back(4065);
        internal_counters.push_back(4069);

        c.DefineDerivedCounter("CSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has compute shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,max", "39bcf1b8-f6b2-4c37-f9af-0a2bb59512f9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16630);
        internal_counters.push_back(4059);
        internal_counters.push_back(4063);
        internal_counters.push_back(4065);
        internal_counters.push_back(4069);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("CSTime", "Timing", "Time compute shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,ifnotzero,(0),3,4,ifnotzero,max,5,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "dbc24916-ecb2-7eef-8d63-7afadaaab6bc");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16312);
        internal_counters.push_back(16293);
        internal_counters.push_back(16388);

        c.DefineDerivedCounter("VSVerticesIn", "VertexShader", "The number of vertices processed by the VS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,1,ifnotzero,2,2,ifnotzero", "810a04c8-2ff4-081d-766d-bfa2bd4ad916");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5361);
        internal_counters.push_back(5339);

        c.DefineDerivedCounter("VSVALUInstCount", "VertexShader", "Average number of vector ALU instructions executed in the VS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "8ec604e4-63f5-e6b5-4558-c38f0b26d4b1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5365);
        internal_counters.push_back(5339);

        c.DefineDerivedCounter("VSSALUInstCount", "VertexShader", "Average number of scalar ALU instructions executed in the VS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "e3da0383-7322-7f65-8cf2-3ce641578e54");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5406);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("VSVALUBusy", "VertexShader", "The percentage of GPUTime vector ALU instructions are being processed by the VS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "8b3572f7-fda0-eddf-6c93-2ab145b8754b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5406);

        c.DefineDerivedCounter("VSVALUBusyCycles", "VertexShader", "Number of GPU cycles where vector ALU instructions are being processed by the VS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,(4),*,NUM_SIMDS,/", "0af1686e-6d77-2f6e-2862-7bb8e869a776");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5419);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("VSSALUBusy", "VertexShader", "The percentage of GPUTime scalar ALU instructions are being processed by the VS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "3bc8730c-e3bc-e2f0-7d24-36974064c25a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5419);

        c.DefineDerivedCounter("VSSALUBusyCycles", "VertexShader", "Number of GPU cycles where scalar ALU instructions are being processed by the VS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_CUS,/", "357ac7cd-2e1c-dcb0-77f6-37527237f35b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16397);

        c.DefineDerivedCounter("HSPatches", "HullShader", "The number of patches processed by the HS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "d1bbd27d-d591-4509-df52-d329fb73a98f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6483);
        internal_counters.push_back(6461);

        c.DefineDerivedCounter("HSVALUInstCount", "HullShader", "Average number of vector ALU instructions executed in the HS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "786673bf-d58f-9895-3a37-9d6efb5e5804");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6487);
        internal_counters.push_back(6461);

        c.DefineDerivedCounter("HSSALUInstCount", "HullShader", "Average number of scalar ALU instructions executed in the HS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "1af675c4-cb0b-c4c5-c131-2796750f683e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6528);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("HSVALUBusy", "HullShader", "The percentage of GPUTime vector ALU instructions are being processed by the HS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "7880d192-8015-0311-d43e-fb0b7a4df179");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6528);

        c.DefineDerivedCounter("HSVALUBusyCycles", "HullShader", "Number of GPU cycles vector where ALU instructions are being processed by the HS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,(4),*,NUM_SIMDS,/", "3afb94e4-e937-5730-0cc9-41d3113ba012");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6541);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("HSSALUBusy", "HullShader", "The percentage of GPUTime scalar ALU instructions are being processed by the HS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "34748a4b-9148-0b06-b7b9-5700d6631bde");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6541);

        c.DefineDerivedCounter("HSSALUBusyCycles", "HullShader", "Number of GPU cycles where scalar ALU instructions are being processed by the HS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_CUS,/", "9bceabf7-3f01-2fd9-7b1d-8fe46c729efc");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16301);

        c.DefineDerivedCounter("GSPrimsIn", "GeometryShader", "The number of primitives passed into the GS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "20c29866-509a-aaab-2697-6b2c38f79953");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16312);
        internal_counters.push_back(16293);

        c.DefineDerivedCounter("GSVerticesOut", "GeometryShader", "The number of vertices output by the GS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,ifnotzero", "775b9736-319a-bd8a-48c9-68db9c91d978");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4987);
        internal_counters.push_back(4965);

        c.DefineDerivedCounter("GSVALUInstCount", "GeometryShader", "Average number of vector ALU instructions executed in the GS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "21b12bfa-b8cd-2e71-a2d5-f9e9f1d65d61");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4991);
        internal_counters.push_back(4965);

        c.DefineDerivedCounter("GSSALUInstCount", "GeometryShader", "Average number of scalar ALU instructions executed in the GS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "a8562594-d335-ca43-61bf-03b72d2b98a5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5032);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("GSVALUBusy", "GeometryShader", "The percentage of GPUTime vector ALU instructions are being processed by the GS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "228a4818-1e56-cebb-0720-3b2cdc057a6f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5032);

        c.DefineDerivedCounter("GSVALUBusyCycles", "GeometryShader", "Number of GPU cycles where vector ALU instructions are being processed by the GS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,(4),*,NUM_SIMDS,/", "be217edd-226f-bd97-9a48-46e2809b1933");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5045);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("GSSALUBusy", "GeometryShader", "The percentage of GPUTime scalar ALU instructions are being processed by the GS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "f28ce300-800e-9822-39e4-f48528bdb935");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5045);

        c.DefineDerivedCounter("GSSALUBusyCycles", "GeometryShader", "Number of GPU cycles where scalar ALU instructions are being processed by the GS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_CUS,/", "b3eace7c-3bc4-0107-887f-923851dc8ea7");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3279);
        internal_counters.push_back(3283);
        internal_counters.push_back(3235);
        internal_counters.push_back(3247);
        internal_counters.push_back(3236);
        internal_counters.push_back(3248);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("PrimitiveAssemblyBusy", "Timing", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max,6,/,(100),*,(100),min", "54ac5640-c4d7-95e2-20e0-6a9fdfc07333");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3279);
        internal_counters.push_back(3283);
        internal_counters.push_back(3235);
        internal_counters.push_back(3247);
        internal_counters.push_back(3236);
        internal_counters.push_back(3248);

        c.DefineDerivedCounter("PrimitiveAssemblyBusyCycles", "Timing", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max", "99777f2d-9626-c78a-a97c-c4505eba1e5f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3182);

        c.DefineDerivedCounter("PrimitivesIn", "PrimitiveAssembly", "The number of primitives received by the hardware. This includes primitives generated by tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "a515b80d-75c3-c7d2-0d2f-d7766b4759a6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3188);
        internal_counters.push_back(3228);
        internal_counters.push_back(3229);
        internal_counters.push_back(3230);
        internal_counters.push_back(3231);

        c.DefineDerivedCounter("CulledPrims", "PrimitiveAssembly", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,+,2,+,3,+,4,+", "589bdf55-9192-280a-41c3-584bc94f2562");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3195);

        c.DefineDerivedCounter("ClippedPrims", "PrimitiveAssembly", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "5ef6f9d5-155e-5baa-163f-8359d9ea9bbf");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3283);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("PAStalledOnRasterizer", "PrimitiveAssembly", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_PRIM_PIPES,/,1,/,(100),*", "6f9f416b-53c1-0457-f88c-7b6ba8973974");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3283);

        c.DefineDerivedCounter("PAStalledOnRasterizerCycles", "PrimitiveAssembly", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_PRIM_PIPES,/", "7a8c492a-c566-9328-6805-760dbff5c0f2");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7217);
        internal_counters.push_back(7222);
        internal_counters.push_back(7227);
        internal_counters.push_back(7232);

        c.DefineDerivedCounter("PSPixelsOut", "PixelShader", "Pixels exported from shader to color buffers. Does not include killed or alpha tested pixels; if there are multiple render targets, each render target receives one export, so this will be 2 for 1 pixel written to two RTs.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "24cba16c-baa6-6ecd-95ad-92ecb1338da1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7219);
        internal_counters.push_back(7224);
        internal_counters.push_back(7229);
        internal_counters.push_back(7234);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("PSExportStalls", "PixelShader", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "9b4f466c-ff97-22bb-557d-84d3c4c51895");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7219);
        internal_counters.push_back(7224);
        internal_counters.push_back(7229);
        internal_counters.push_back(7234);

        c.DefineDerivedCounter("PSExportStallsCycles", "PixelShader", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "47c72aad-64e6-0864-d533-d8e0bc27c156");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5735);
        internal_counters.push_back(5713);

        c.DefineDerivedCounter("PSVALUInstCount", "PixelShader", "Average number of vector ALU instructions executed in the PS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "eb74389e-435c-4137-ecf1-39eb5bc1cbfe");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5739);
        internal_counters.push_back(5713);

        c.DefineDerivedCounter("PSSALUInstCount", "PixelShader", "Average number of scalar ALU instructions executed in the PS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "e6a06580-8a82-96d6-976c-acc121fc5516");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5780);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("PSVALUBusy", "PixelShader", "The percentage of GPUTime vector ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "6ce6fef7-8e33-10b4-f351-af755e177e85");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5780);

        c.DefineDerivedCounter("PSVALUBusyCycles", "PixelShader", "Number of GPU cycles where vector ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,(4),*,NUM_SIMDS,/", "1e276f86-cd2a-72e7-fc9d-004f666f2981");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5793);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("PSSALUBusy", "PixelShader", "The percentage of GPUTime scalar ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "2ff9f34f-e94b-af4d-18c2-5fbbf6d1727a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5793);

        c.DefineDerivedCounter("PSSALUBusyCycles", "PixelShader", "Number of GPU cycles where scalar ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_CUS,/", "29808906-f128-b078-fc79-820a4b3b3b8d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4060);
        internal_counters.push_back(4066);

        c.DefineDerivedCounter("CSThreadGroups", "ComputeShader", "Total number of thread groups.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,+", "8ce3fc80-56b2-97f9-8e70-2e8c747cea68");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6835);

        c.DefineDerivedCounter("CSWavefronts", "ComputeShader", "The total number of wavefronts used for the CS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "42379c6e-369b-c237-8b25-cdb9cdc65c4d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6845);

        c.DefineDerivedCounter("CSThreads", "ComputeShader", "The number of CS threads processed by the hardware.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "7a648013-6eac-2665-ac36-13c6f4ac9c26");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6857);
        internal_counters.push_back(6835);

        c.DefineDerivedCounter("CSVALUInsts", "ComputeShader", "The average number of vector ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "376cb1cc-5a40-9d1d-404c-f1736c0c5084");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6916);
        internal_counters.push_back(6902);

        c.DefineDerivedCounter("CSVALUUtilization", "ComputeShader", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,(64),*,/,(100),*,1,ifnotzero,(100),min", "4476879e-cdc0-d602-b24e-9b4a8d38438f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6861);
        internal_counters.push_back(6835);

        c.DefineDerivedCounter("CSSALUInsts", "ComputeShader", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "eb211144-8136-ff86-e8bf-4d0493a904cb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6859);
        internal_counters.push_back(7514);
        internal_counters.push_back(7633);
        internal_counters.push_back(7752);
        internal_counters.push_back(7871);
        internal_counters.push_back(7990);
        internal_counters.push_back(8109);
        internal_counters.push_back(8228);
        internal_counters.push_back(8347);
        internal_counters.push_back(8466);
        internal_counters.push_back(8585);
        internal_counters.push_back(8704);
        internal_counters.push_back(8823);
        internal_counters.push_back(8942);
        internal_counters.push_back(9061);
        internal_counters.push_back(9180);
        internal_counters.push_back(9299);
        internal_counters.push_back(6835);

        c.DefineDerivedCounter("CSVFetchInsts", "ComputeShader", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/,17,ifnotzero", "3e2829c0-6215-783b-c271-6d57ff2c520e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6862);
        internal_counters.push_back(6835);

        c.DefineDerivedCounter("CSSFetchInsts", "ComputeShader", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "da09171c-6a0a-584f-fddc-dc5062d63a3e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6858);
        internal_counters.push_back(7515);
        internal_counters.push_back(7634);
        internal_counters.push_back(7753);
        internal_counters.push_back(7872);
        internal_counters.push_back(7991);
        internal_counters.push_back(8110);
        internal_counters.push_back(8229);
        internal_counters.push_back(8348);
        internal_counters.push_back(8467);
        internal_counters.push_back(8586);
        internal_counters.push_back(8705);
        internal_counters.push_back(8824);
        internal_counters.push_back(8943);
        internal_counters.push_back(9062);
        internal_counters.push_back(9181);
        internal_counters.push_back(9300);
        internal_counters.push_back(6835);

        c.DefineDerivedCounter("CSVWriteInsts", "ComputeShader", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/,17,ifnotzero", "43438c22-e910-b377-b767-b32902e0df0d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6863);
        internal_counters.push_back(6864);
        internal_counters.push_back(6835);

        c.DefineDerivedCounter("CSFlatVMemInsts", "ComputeShader", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,-,2,/,2,ifnotzero", "2570b477-13e3-f5b6-e6ff-7159373bc74d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6902);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("CSVALUBusy", "ComputeShader", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "f1e64815-f6a8-c277-d4f9-d054b443e205");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6902);

        c.DefineDerivedCounter("CSVALUBusyCycles", "ComputeShader", "Number of GPU cycles where vector ALU instructions are processed.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,(4),*,NUM_SIMDS,/", "2d0d5852-2658-eb73-68d2-f23f7118c9c3");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6915);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("CSSALUBusy", "ComputeShader", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "3fc35f4e-9882-94e3-6f5f-4e81cd97082a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6915);

        c.DefineDerivedCounter("CSSALUBusyCycles", "ComputeShader", "Number of GPU cycles where scalar ALU instructions are processed.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_CUS,/", "de58f8fc-8ed4-a799-648d-62ded7b1c4c4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7428);
        internal_counters.push_back(7547);
        internal_counters.push_back(7666);
        internal_counters.push_back(7785);
        internal_counters.push_back(7904);
        internal_counters.push_back(8023);
        internal_counters.push_back(8142);
        internal_counters.push_back(8261);
        internal_counters.push_back(8380);
        internal_counters.push_back(8499);
        internal_counters.push_back(8618);
        internal_counters.push_back(8737);
        internal_counters.push_back(8856);
        internal_counters.push_back(8975);
        internal_counters.push_back(9094);
        internal_counters.push_back(9213);
        internal_counters.push_back(1799);
        internal_counters.push_back(4060);
        internal_counters.push_back(4066);

        c.DefineDerivedCounter("CSMemUnitBusy", "ComputeShader", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*,17,18,+,ifnotzero", "42ab96e1-0a24-96c8-c4ff-098fa267d78e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7428);
        internal_counters.push_back(7547);
        internal_counters.push_back(7666);
        internal_counters.push_back(7785);
        internal_counters.push_back(7904);
        internal_counters.push_back(8023);
        internal_counters.push_back(8142);
        internal_counters.push_back(8261);
        internal_counters.push_back(8380);
        internal_counters.push_back(8499);
        internal_counters.push_back(8618);
        internal_counters.push_back(8737);
        internal_counters.push_back(8856);
        internal_counters.push_back(8975);
        internal_counters.push_back(9094);
        internal_counters.push_back(9213);
        internal_counters.push_back(4060);
        internal_counters.push_back(4066);

        c.DefineDerivedCounter("CSMemUnitBusyCycles", "ComputeShader", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ENGINES,/,16,17,+,ifnotzero", "39d5687f-c727-7c0c-af82-bb711d3897ed");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14817);
        internal_counters.push_back(14902);
        internal_counters.push_back(14987);
        internal_counters.push_back(15072);
        internal_counters.push_back(15157);
        internal_counters.push_back(15242);
        internal_counters.push_back(15327);
        internal_counters.push_back(15412);
        internal_counters.push_back(15497);
        internal_counters.push_back(15582);
        internal_counters.push_back(15667);
        internal_counters.push_back(15752);
        internal_counters.push_back(15837);
        internal_counters.push_back(15922);
        internal_counters.push_back(16007);
        internal_counters.push_back(16092);
        internal_counters.push_back(1799);
        internal_counters.push_back(4060);
        internal_counters.push_back(4066);

        c.DefineDerivedCounter("CSMemUnitStalled", "ComputeShader", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*,17,18,+,ifnotzero", "f18e8679-1511-d533-d9ee-4365197f7d0c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14817);
        internal_counters.push_back(14902);
        internal_counters.push_back(14987);
        internal_counters.push_back(15072);
        internal_counters.push_back(15157);
        internal_counters.push_back(15242);
        internal_counters.push_back(15327);
        internal_counters.push_back(15412);
        internal_counters.push_back(15497);
        internal_counters.push_back(15582);
        internal_counters.push_back(15667);
        internal_counters.push_back(15752);
        internal_counters.push_back(15837);
        internal_counters.push_back(15922);
        internal_counters.push_back(16007);
        internal_counters.push_back(16092);
        internal_counters.push_back(4060);
        internal_counters.push_back(4066);

        c.DefineDerivedCounter("CSMemUnitStalledCycles", "ComputeShader", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ENGINES,/,16,17,+,ifnotzero", "51991c84-ed2b-bf31-c4ab-8f8e9eb8f29f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9420);
        internal_counters.push_back(9702);
        internal_counters.push_back(9984);
        internal_counters.push_back(10266);
        internal_counters.push_back(10548);
        internal_counters.push_back(10830);
        internal_counters.push_back(11112);
        internal_counters.push_back(11394);
        internal_counters.push_back(11676);
        internal_counters.push_back(11958);
        internal_counters.push_back(12240);
        internal_counters.push_back(12522);
        internal_counters.push_back(12804);
        internal_counters.push_back(13086);
        internal_counters.push_back(13368);
        internal_counters.push_back(13650);
        internal_counters.push_back(1799);
        internal_counters.push_back(4060);
        internal_counters.push_back(4066);

        c.DefineDerivedCounter("CSWriteUnitStalled", "ComputeShader", "The percentage of GPUTime the write unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,18,+,ifnotzero", "55118f7a-8f92-726f-78c6-407f689a2eb4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9420);
        internal_counters.push_back(9702);
        internal_counters.push_back(9984);
        internal_counters.push_back(10266);
        internal_counters.push_back(10548);
        internal_counters.push_back(10830);
        internal_counters.push_back(11112);
        internal_counters.push_back(11394);
        internal_counters.push_back(11676);
        internal_counters.push_back(11958);
        internal_counters.push_back(12240);
        internal_counters.push_back(12522);
        internal_counters.push_back(12804);
        internal_counters.push_back(13086);
        internal_counters.push_back(13368);
        internal_counters.push_back(13650);
        internal_counters.push_back(4060);
        internal_counters.push_back(4066);

        c.DefineDerivedCounter("CSWriteUnitStalledCycles", "ComputeShader", "Number of GPU cycles the write unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,17,+,ifnotzero", "be164c60-5e48-acac-9622-29616d09aa9a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6866);
        internal_counters.push_back(6835);

        c.DefineDerivedCounter("CSGDSInsts", "ComputeShader", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "2a867f3e-4a37-ad16-55d1-f03d74707819");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6865);
        internal_counters.push_back(6864);
        internal_counters.push_back(6835);

        c.DefineDerivedCounter("CSLDSInsts", "ComputeShader", "The average number of LDS read/write instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,-,2,/,2,ifnotzero", "61b0b351-7e06-ef8e-a8e0-7a9e3200a836");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6864);
        internal_counters.push_back(6835);

        c.DefineDerivedCounter("CSFlatLDSInsts", "ComputeShader", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "99672cda-de2b-014c-482e-cf73b90068d5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4276);
        internal_counters.push_back(4217);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("CSALUStalledByLDS", "ComputeShader", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,/,2,/,NUM_SHADER_ENGINES,/,(100),*,1,ifnotzero", "6dc4f1c2-bad0-c9ff-156e-883b319a752a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4276);

        c.DefineDerivedCounter("CSALUStalledByLDSCycles", "ComputeShader", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_SHADER_ENGINES,/", "8f3d5f25-2159-0374-fafe-e26a7799b6c8");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6924);
        internal_counters.push_back(1799);
        internal_counters.push_back(4060);
        internal_counters.push_back(4066);

        c.DefineDerivedCounter("CSLDSBankConflict", "ComputeShader", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,/,NUM_SIMDS,/,(100),*,2,3,+,ifnotzero", "1065ee10-2e41-ea41-1eb3-b61b491752f4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6924);

        c.DefineDerivedCounter("CSLDSBankConflictCycles", "ComputeShader", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad).", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_SIMDS,/", "1fd1adf3-c51e-94fd-083e-c482a0a0809e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7428);
        internal_counters.push_back(7547);
        internal_counters.push_back(7666);
        internal_counters.push_back(7785);
        internal_counters.push_back(7904);
        internal_counters.push_back(8023);
        internal_counters.push_back(8142);
        internal_counters.push_back(8261);
        internal_counters.push_back(8380);
        internal_counters.push_back(8499);
        internal_counters.push_back(8618);
        internal_counters.push_back(8737);
        internal_counters.push_back(8856);
        internal_counters.push_back(8975);
        internal_counters.push_back(9094);
        internal_counters.push_back(9213);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("TexUnitBusy", "Timing", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "36afb8d9-42fc-aafe-66c5-449542153b2c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7428);
        internal_counters.push_back(7547);
        internal_counters.push_back(7666);
        internal_counters.push_back(7785);
        internal_counters.push_back(7904);
        internal_counters.push_back(8023);
        internal_counters.push_back(8142);
        internal_counters.push_back(8261);
        internal_counters.push_back(8380);
        internal_counters.push_back(8499);
        internal_counters.push_back(8618);
        internal_counters.push_back(8737);
        internal_counters.push_back(8856);
        internal_counters.push_back(8975);
        internal_counters.push_back(9094);
        internal_counters.push_back(9213);

        c.DefineDerivedCounter("TexUnitBusyCycles", "Timing", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ENGINES,/", "c68761f2-248c-4f39-6528-c308b1c0807c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7482);
        internal_counters.push_back(7601);
        internal_counters.push_back(7720);
        internal_counters.push_back(7839);
        internal_counters.push_back(7958);
        internal_counters.push_back(8077);
        internal_counters.push_back(8196);
        internal_counters.push_back(8315);
        internal_counters.push_back(8434);
        internal_counters.push_back(8553);
        internal_counters.push_back(8672);
        internal_counters.push_back(8791);
        internal_counters.push_back(8910);
        internal_counters.push_back(9029);
        internal_counters.push_back(9148);
        internal_counters.push_back(9267);
        internal_counters.push_back(7481);
        internal_counters.push_back(7600);
        internal_counters.push_back(7719);
        internal_counters.push_back(7838);
        internal_counters.push_back(7957);
        internal_counters.push_back(8076);
        internal_counters.push_back(8195);
        internal_counters.push_back(8314);
        internal_counters.push_back(8433);
        internal_counters.push_back(8552);
        internal_counters.push_back(8671);
        internal_counters.push_back(8790);
        internal_counters.push_back(8909);
        internal_counters.push_back(9028);
        internal_counters.push_back(9147);
        internal_counters.push_back(9266);

        c.DefineDerivedCounter("TexTriFilteringPct", "TextureUnit", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,+,/,(100),*", "1affc3c8-b917-5c81-622b-7004527208ae");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7482);
        internal_counters.push_back(7601);
        internal_counters.push_back(7720);
        internal_counters.push_back(7839);
        internal_counters.push_back(7958);
        internal_counters.push_back(8077);
        internal_counters.push_back(8196);
        internal_counters.push_back(8315);
        internal_counters.push_back(8434);
        internal_counters.push_back(8553);
        internal_counters.push_back(8672);
        internal_counters.push_back(8791);
        internal_counters.push_back(8910);
        internal_counters.push_back(9029);
        internal_counters.push_back(9148);
        internal_counters.push_back(9267);

        c.DefineDerivedCounter("TexTriFilteringCount", "TextureUnit", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "5785b3a1-a513-18db-4b1c-bdeef75bb2b6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7481);
        internal_counters.push_back(7600);
        internal_counters.push_back(7719);
        internal_counters.push_back(7838);
        internal_counters.push_back(7957);
        internal_counters.push_back(8076);
        internal_counters.push_back(8195);
        internal_counters.push_back(8314);
        internal_counters.push_back(8433);
        internal_counters.push_back(8552);
        internal_counters.push_back(8671);
        internal_counters.push_back(8790);
        internal_counters.push_back(8909);
        internal_counters.push_back(9028);
        internal_counters.push_back(9147);
        internal_counters.push_back(9266);

        c.DefineDerivedCounter("NoTexTriFilteringCount", "TextureUnit", "Count of pixels that did not receive trilinear filtering.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "179da29a-81af-c06e-ce8c-a0a731ea030d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7484);
        internal_counters.push_back(7603);
        internal_counters.push_back(7722);
        internal_counters.push_back(7841);
        internal_counters.push_back(7960);
        internal_counters.push_back(8079);
        internal_counters.push_back(8198);
        internal_counters.push_back(8317);
        internal_counters.push_back(8436);
        internal_counters.push_back(8555);
        internal_counters.push_back(8674);
        internal_counters.push_back(8793);
        internal_counters.push_back(8912);
        internal_counters.push_back(9031);
        internal_counters.push_back(9150);
        internal_counters.push_back(9269);
        internal_counters.push_back(7483);
        internal_counters.push_back(7602);
        internal_counters.push_back(7721);
        internal_counters.push_back(7840);
        internal_counters.push_back(7959);
        internal_counters.push_back(8078);
        internal_counters.push_back(8197);
        internal_counters.push_back(8316);
        internal_counters.push_back(8435);
        internal_counters.push_back(8554);
        internal_counters.push_back(8673);
        internal_counters.push_back(8792);
        internal_counters.push_back(8911);
        internal_counters.push_back(9030);
        internal_counters.push_back(9149);
        internal_counters.push_back(9268);

        c.DefineDerivedCounter("TexVolFilteringPct", "TextureUnit", "Percentage of pixels that received volume filtering.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,+,/,(100),*", "b5ff6bed-3178-aee4-42dd-c74391c02a2d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7484);
        internal_counters.push_back(7603);
        internal_counters.push_back(7722);
        internal_counters.push_back(7841);
        internal_counters.push_back(7960);
        internal_counters.push_back(8079);
        internal_counters.push_back(8198);
        internal_counters.push_back(8317);
        internal_counters.push_back(8436);
        internal_counters.push_back(8555);
        internal_counters.push_back(8674);
        internal_counters.push_back(8793);
        internal_counters.push_back(8912);
        internal_counters.push_back(9031);
        internal_counters.push_back(9150);
        internal_counters.push_back(9269);

        c.DefineDerivedCounter("TexVolFilteringCount", "TextureUnit", "Count of pixels that received volume filtering.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "4bddc587-d589-8128-e18c-762eab2c871f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7483);
        internal_counters.push_back(7602);
        internal_counters.push_back(7721);
        internal_counters.push_back(7840);
        internal_counters.push_back(7959);
        internal_counters.push_back(8078);
        internal_counters.push_back(8197);
        internal_counters.push_back(8316);
        internal_counters.push_back(8435);
        internal_counters.push_back(8554);
        internal_counters.push_back(8673);
        internal_counters.push_back(8792);
        internal_counters.push_back(8911);
        internal_counters.push_back(9030);
        internal_counters.push_back(9149);
        internal_counters.push_back(9268);

        c.DefineDerivedCounter("NoTexVolFilteringCount", "TextureUnit", "Count of pixels that did not receive volume filtering.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "9fe1a854-17c6-9d26-b2b9-80610cd5827d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7502);
        internal_counters.push_back(7621);
        internal_counters.push_back(7740);
        internal_counters.push_back(7859);
        internal_counters.push_back(7978);
        internal_counters.push_back(8097);
        internal_counters.push_back(8216);
        internal_counters.push_back(8335);
        internal_counters.push_back(8454);
        internal_counters.push_back(8573);
        internal_counters.push_back(8692);
        internal_counters.push_back(8811);
        internal_counters.push_back(8930);
        internal_counters.push_back(9049);
        internal_counters.push_back(9168);
        internal_counters.push_back(9287);
        internal_counters.push_back(7503);
        internal_counters.push_back(7622);
        internal_counters.push_back(7741);
        internal_counters.push_back(7860);
        internal_counters.push_back(7979);
        internal_counters.push_back(8098);
        internal_counters.push_back(8217);
        internal_counters.push_back(8336);
        internal_counters.push_back(8455);
        internal_counters.push_back(8574);
        internal_counters.push_back(8693);
        internal_counters.push_back(8812);
        internal_counters.push_back(8931);
        internal_counters.push_back(9050);
        internal_counters.push_back(9169);
        internal_counters.push_back(9288);
        internal_counters.push_back(7504);
        internal_counters.push_back(7623);
        internal_counters.push_back(7742);
        internal_counters.push_back(7861);
        internal_counters.push_back(7980);
        internal_counters.push_back(8099);
        internal_counters.push_back(8218);
        internal_counters.push_back(8337);
        internal_counters.push_back(8456);
        internal_counters.push_back(8575);
        internal_counters.push_back(8694);
        internal_counters.push_back(8813);
        internal_counters.push_back(8932);
        internal_counters.push_back(9051);
        internal_counters.push_back(9170);
        internal_counters.push_back(9289);
        internal_counters.push_back(7505);
        internal_counters.push_back(7624);
        internal_counters.push_back(7743);
        internal_counters.push_back(7862);
        internal_counters.push_back(7981);
        internal_counters.push_back(8100);
        internal_counters.push_back(8219);
        internal_counters.push_back(8338);
        internal_counters.push_back(8457);
        internal_counters.push_back(8576);
        internal_counters.push_back(8695);
        internal_counters.push_back(8814);
        internal_counters.push_back(8933);
        internal_counters.push_back(9052);
        internal_counters.push_back(9171);
        internal_counters.push_back(9290);
        internal_counters.push_back(7506);
        internal_counters.push_back(7625);
        internal_counters.push_back(7744);
        internal_counters.push_back(7863);
        internal_counters.push_back(7982);
        internal_counters.push_back(8101);
        internal_counters.push_back(8220);
        internal_counters.push_back(8339);
        internal_counters.push_back(8458);
        internal_counters.push_back(8577);
        internal_counters.push_back(8696);
        internal_counters.push_back(8815);
        internal_counters.push_back(8934);
        internal_counters.push_back(9053);
        internal_counters.push_back(9172);
        internal_counters.push_back(9291);
        internal_counters.push_back(7507);
        internal_counters.push_back(7626);
        internal_counters.push_back(7745);
        internal_counters.push_back(7864);
        internal_counters.push_back(7983);
        internal_counters.push_back(8102);
        internal_counters.push_back(8221);
        internal_counters.push_back(8340);
        internal_counters.push_back(8459);
        internal_counters.push_back(8578);
        internal_counters.push_back(8697);
        internal_counters.push_back(8816);
        internal_counters.push_back(8935);
        internal_counters.push_back(9054);
        internal_counters.push_back(9173);
        internal_counters.push_back(9292);
        internal_counters.push_back(7508);
        internal_counters.push_back(7627);
        internal_counters.push_back(7746);
        internal_counters.push_back(7865);
        internal_counters.push_back(7984);
        internal_counters.push_back(8103);
        internal_counters.push_back(8222);
        internal_counters.push_back(8341);
        internal_counters.push_back(8460);
        internal_counters.push_back(8579);
        internal_counters.push_back(8698);
        internal_counters.push_back(8817);
        internal_counters.push_back(8936);
        internal_counters.push_back(9055);
        internal_counters.push_back(9174);
        internal_counters.push_back(9293);
        internal_counters.push_back(7509);
        internal_counters.push_back(7628);
        internal_counters.push_back(7747);
        internal_counters.push_back(7866);
        internal_counters.push_back(7985);
        internal_counters.push_back(8104);
        internal_counters.push_back(8223);
        internal_counters.push_back(8342);
        internal_counters.push_back(8461);
        internal_counters.push_back(8580);
        internal_counters.push_back(8699);
        internal_counters.push_back(8818);
        internal_counters.push_back(8937);
        internal_counters.push_back(9056);
        internal_counters.push_back(9175);
        internal_counters.push_back(9294);
        internal_counters.push_back(7510);
        internal_counters.push_back(7629);
        internal_counters.push_back(7748);
        internal_counters.push_back(7867);
        internal_counters.push_back(7986);
        internal_counters.push_back(8105);
        internal_counters.push_back(8224);
        internal_counters.push_back(8343);
        internal_counters.push_back(8462);
        internal_counters.push_back(8581);
        internal_counters.push_back(8700);
        internal_counters.push_back(8819);
        internal_counters.push_back(8938);
        internal_counters.push_back(9057);
        internal_counters.push_back(9176);
        internal_counters.push_back(9295);

        c.DefineDerivedCounter("TexAveAnisotropy", "TextureUnit", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(2),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,*,+,(4),32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,*,+,(6),48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,*,+,(8),64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,*,+,(10),80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,*,+,(12),96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,*,+,(14),112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,*,+,(16),128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,*,+,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,+,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,+,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,+,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,+,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,+,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,+,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,+,/", "7ca2a2b9-a4eb-ce23-d163-59147e672396");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1952);
        internal_counters.push_back(2280);
        internal_counters.push_back(2608);
        internal_counters.push_back(2936);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("DepthStencilTestBusy", "Timing", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "6834fb52-42e8-bb50-fd48-ec2f2904e7e0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1952);
        internal_counters.push_back(2280);
        internal_counters.push_back(2608);
        internal_counters.push_back(2936);

        c.DefineDerivedCounter("DepthStencilTestBusyCount", "Timing", "Number of GPU cycles spent performing depth and stencil tests.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "e02860fa-c7bd-90ea-2149-69b4e98a636c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1823);
        internal_counters.push_back(2151);
        internal_counters.push_back(2479);
        internal_counters.push_back(2807);
        internal_counters.push_back(1812);
        internal_counters.push_back(2140);
        internal_counters.push_back(2468);
        internal_counters.push_back(2796);

        c.DefineDerivedCounter("HiZTilesAccepted", "DepthAndStencil", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*", "56176f45-d7ff-813d-4f05-3b2f046067e7");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1823);
        internal_counters.push_back(2151);
        internal_counters.push_back(2479);
        internal_counters.push_back(2807);

        c.DefineDerivedCounter("HiZTilesAcceptedCount", "DepthAndStencil", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "95d4e3f6-b2f0-f26e-8423-aacdfaf79ea3");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1812);
        internal_counters.push_back(2140);
        internal_counters.push_back(2468);
        internal_counters.push_back(2796);

        c.DefineDerivedCounter("HiZTilesRejectedCount", "DepthAndStencil", "Count of tiles not accepted by HiZ.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "156ba142-7eeb-aa6e-a00a-f8aea4e41e0b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1812);
        internal_counters.push_back(2140);
        internal_counters.push_back(2468);
        internal_counters.push_back(2796);
        internal_counters.push_back(1836);
        internal_counters.push_back(2164);
        internal_counters.push_back(2492);
        internal_counters.push_back(2820);

        c.DefineDerivedCounter("PreZTilesDetailCulled", "DepthAndStencil", "Percentage of tiles rejected because the associated prim had no contributing area.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "4,5,6,7,sum4,0,1,2,3,sum4,/,(100),*", "cad7f54d-a044-7574-c472-6f2065cbeeac");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1836);
        internal_counters.push_back(2164);
        internal_counters.push_back(2492);
        internal_counters.push_back(2820);

        c.DefineDerivedCounter("PreZTilesDetailCulledCount", "DepthAndStencil", "Count of tiles rejected because the associated primitive had no contributing area.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "49262c8a-b1e6-90dd-f096-0fc4921715e9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1812);
        internal_counters.push_back(2140);
        internal_counters.push_back(2468);
        internal_counters.push_back(2796);

        c.DefineDerivedCounter("PreZTilesDetailSurvivingCount", "DepthAndStencil", "Count of tiles surviving because the associated primitive had contributing area.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "f803eaa4-bbed-bd39-775f-a64df92e2c08");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3684);
        internal_counters.push_back(3685);
        internal_counters.push_back(3686);
        internal_counters.push_back(3687);
        internal_counters.push_back(3760);
        internal_counters.push_back(3761);
        internal_counters.push_back(3762);
        internal_counters.push_back(3763);

        c.DefineDerivedCounter("HiZQuadsCulled", "DepthAndStencil", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-,(0),max,0,1,+,2,+,3,+,/,(100),*", "fa0e319b-5573-6d34-5bab-904769925036");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3684);
        internal_counters.push_back(3685);
        internal_counters.push_back(3686);
        internal_counters.push_back(3687);
        internal_counters.push_back(3760);
        internal_counters.push_back(3761);
        internal_counters.push_back(3762);
        internal_counters.push_back(3763);

        c.DefineDerivedCounter("HiZQuadsCulledCount", "DepthAndStencil", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-,(0),max", "73b0b39d-6df2-3e24-0b5c-7cb0ac8b6f39");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3760);
        internal_counters.push_back(3761);
        internal_counters.push_back(3762);
        internal_counters.push_back(3763);

        c.DefineDerivedCounter("HiZQuadsAcceptedCount", "DepthAndStencil", "Count of quads that did continue on in the pipeline after HiZ.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,+,2,+,3,+", "59049ad9-42b5-c7cb-3616-6a8f6a8e4894");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3684);
        internal_counters.push_back(3685);
        internal_counters.push_back(3686);
        internal_counters.push_back(3687);
        internal_counters.push_back(3784);
        internal_counters.push_back(3760);
        internal_counters.push_back(3761);
        internal_counters.push_back(3762);
        internal_counters.push_back(3763);

        c.DefineDerivedCounter("PreZQuadsCulled", "DepthAndStencil", "Percentage of quads rejected based on the detailZ and earlyZ tests.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "5,6,+,7,+,8,+,4,-,(0),max,0,1,+,2,+,3,+,/,(100),*", "4e77547b-ec55-5663-f034-af59be66d77d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3684);
        internal_counters.push_back(3685);
        internal_counters.push_back(3686);
        internal_counters.push_back(3687);
        internal_counters.push_back(3784);
        internal_counters.push_back(3760);
        internal_counters.push_back(3761);
        internal_counters.push_back(3762);
        internal_counters.push_back(3763);

        c.DefineDerivedCounter("PreZQuadsCulledCount", "DepthAndStencil", "Count of quads rejected based on the detailZ and earlyZ tests.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,+,2,+,3,+,4,-,5,-,6,-,7,-,8,-,(0),max", "1bf169e6-9304-834e-df5f-0c44d7890a08");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3784);
        internal_counters.push_back(3760);
        internal_counters.push_back(3761);
        internal_counters.push_back(3762);
        internal_counters.push_back(3763);

        c.DefineDerivedCounter("PreZQuadsSurvivingCount", "DepthAndStencil", "Count of quads surviving detailZ and earlyZ tests.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "1,2,+,3,+,4,+,0,-,(0),max", "50e25e51-3713-89cb-7f92-559cde5e5532");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3784);
        internal_counters.push_back(3684);
        internal_counters.push_back(3685);
        internal_counters.push_back(3686);
        internal_counters.push_back(3687);

        c.DefineDerivedCounter("PostZQuads", "DepthAndStencil", "Percentage of quads for which the pixel shader will run and may be postZ tested.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,+,3,+,4,+,/,(100),*,(100),min", "58f0d34b-eeb8-e8db-abce-cb72584144be");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3784);

        c.DefineDerivedCounter("PostZQuadCount", "DepthAndStencil", "Count of quads for which the pixel shader will run and may be postZ tested.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "08404526-ce35-939b-34c8-a7a35a0ff4d6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1985);
        internal_counters.push_back(2313);
        internal_counters.push_back(2641);
        internal_counters.push_back(2969);

        c.DefineDerivedCounter("PreZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z before shading and passed.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "3bfe6c4d-7422-ca03-7ea5-e67ff1a00136");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1987);
        internal_counters.push_back(2315);
        internal_counters.push_back(2643);
        internal_counters.push_back(2971);

        c.DefineDerivedCounter("PreZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z before shading and failed stencil test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "df7f705e-5162-d3b5-da8b-63466cf9c4e5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1986);
        internal_counters.push_back(2314);
        internal_counters.push_back(2642);
        internal_counters.push_back(2970);

        c.DefineDerivedCounter("PreZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z before shading and failed Z test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "4484e950-f7a4-3800-bc74-78dd297f017e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1982);
        internal_counters.push_back(2310);
        internal_counters.push_back(2638);
        internal_counters.push_back(2966);

        c.DefineDerivedCounter("PostZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z after shading and passed.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "4995d5d6-2330-b986-508b-fae24856f44c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1984);
        internal_counters.push_back(2312);
        internal_counters.push_back(2640);
        internal_counters.push_back(2968);

        c.DefineDerivedCounter("PostZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z after shading and failed stencil test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "ae558af4-f4be-3dd4-7316-b2c4dcf0def8");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1983);
        internal_counters.push_back(2311);
        internal_counters.push_back(2639);
        internal_counters.push_back(2967);

        c.DefineDerivedCounter("PostZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z after shading and failed Z test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "b3684c94-814a-c695-c85d-a5b6ab798b35");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1854);
        internal_counters.push_back(2182);
        internal_counters.push_back(2510);
        internal_counters.push_back(2838);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("ZUnitStalled", "DepthAndStencil", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "5e86c3ad-1726-3157-1d01-7ed188bf854d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1854);
        internal_counters.push_back(2182);
        internal_counters.push_back(2510);
        internal_counters.push_back(2838);

        c.DefineDerivedCounter("ZUnitStalledCycles", "DepthAndStencil", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "4351fa7f-6737-2c3e-3ffb-b3addbdceedd");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1856);
        internal_counters.push_back(2184);
        internal_counters.push_back(2512);
        internal_counters.push_back(2840);
        internal_counters.push_back(1863);
        internal_counters.push_back(2191);
        internal_counters.push_back(2519);
        internal_counters.push_back(2847);

        c.DefineDerivedCounter("DBMemRead", "DepthAndStencil", "Number of bytes read from the depth buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,sum4,(256),*,4,5,6,7,sum4,(32),*,+", "dcdb4ee7-bd50-00f7-c028-9e5f4ce888c0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1868);
        internal_counters.push_back(2196);
        internal_counters.push_back(2524);
        internal_counters.push_back(2852);
        internal_counters.push_back(1871);
        internal_counters.push_back(2199);
        internal_counters.push_back(2527);
        internal_counters.push_back(2855);

        c.DefineDerivedCounter("DBMemWritten", "DepthAndStencil", "Number of bytes written to the depth buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,sum4,(32),*,4,5,6,7,sum4,(32),*,+", "de5717f8-8a49-ee44-4645-10de51b37dcf");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(128);
        internal_counters.push_back(572);
        internal_counters.push_back(1016);
        internal_counters.push_back(1460);

        c.DefineDerivedCounter("CBMemRead", "ColorBuffer", "Number of bytes read from the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,sum4,(32),*", "84b531d8-a1f8-7f49-7c27-7bc97801f1e6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(259);
        internal_counters.push_back(703);
        internal_counters.push_back(1147);
        internal_counters.push_back(1591);
        internal_counters.push_back(126);
        internal_counters.push_back(570);
        internal_counters.push_back(1014);
        internal_counters.push_back(1458);
        internal_counters.push_back(127);
        internal_counters.push_back(571);
        internal_counters.push_back(1015);
        internal_counters.push_back(1459);
        internal_counters.push_back(128);
        internal_counters.push_back(572);
        internal_counters.push_back(1016);
        internal_counters.push_back(1460);

        c.DefineDerivedCounter("CBColorAndMaskRead", "ColorBuffer", "Total number of bytes read from the color and mask buffers.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "da41660e-eb6f-32ec-8a64-b32ca17bd7eb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(118);
        internal_counters.push_back(562);
        internal_counters.push_back(1006);
        internal_counters.push_back(1450);

        c.DefineDerivedCounter("CBMemWritten", "ColorBuffer", "Number of bytes written to the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,sum4,(32),*", "550f8ff8-60b6-a6bf-87d0-25ac9e87de70");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(257);
        internal_counters.push_back(701);
        internal_counters.push_back(1145);
        internal_counters.push_back(1589);
        internal_counters.push_back(116);
        internal_counters.push_back(560);
        internal_counters.push_back(1004);
        internal_counters.push_back(1448);
        internal_counters.push_back(117);
        internal_counters.push_back(561);
        internal_counters.push_back(1005);
        internal_counters.push_back(1449);
        internal_counters.push_back(118);
        internal_counters.push_back(562);
        internal_counters.push_back(1006);
        internal_counters.push_back(1450);

        c.DefineDerivedCounter("CBColorAndMaskWritten", "ColorBuffer", "Total number of bytes written to the color and mask buffers.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "29a04b69-8f5f-b770-a0f2-3453e2c99e49");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(162);
        internal_counters.push_back(606);
        internal_counters.push_back(1050);
        internal_counters.push_back(1494);
        internal_counters.push_back(7);
        internal_counters.push_back(451);
        internal_counters.push_back(895);
        internal_counters.push_back(1339);

        c.DefineDerivedCounter("CBSlowPixelPct", "ColorBuffer", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*,(100),min", "5775943f-0313-7e52-9638-b24a449197bc");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(162);
        internal_counters.push_back(606);
        internal_counters.push_back(1050);
        internal_counters.push_back(1494);

        c.DefineDerivedCounter("CBSlowPixelCount", "ColorBuffer", "Number of pixels written to the color buffer using a half-rate or quarter-rate format.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "47eacbb0-28c8-22b4-5c69-c00d5813bb1c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9428);
        internal_counters.push_back(9710);
        internal_counters.push_back(9992);
        internal_counters.push_back(10274);
        internal_counters.push_back(10556);
        internal_counters.push_back(10838);
        internal_counters.push_back(11120);
        internal_counters.push_back(11402);
        internal_counters.push_back(11684);
        internal_counters.push_back(11966);
        internal_counters.push_back(12248);
        internal_counters.push_back(12530);
        internal_counters.push_back(12812);
        internal_counters.push_back(13094);
        internal_counters.push_back(13376);
        internal_counters.push_back(13658);
        internal_counters.push_back(9429);
        internal_counters.push_back(9711);
        internal_counters.push_back(9993);
        internal_counters.push_back(10275);
        internal_counters.push_back(10557);
        internal_counters.push_back(10839);
        internal_counters.push_back(11121);
        internal_counters.push_back(11403);
        internal_counters.push_back(11685);
        internal_counters.push_back(11967);
        internal_counters.push_back(12249);
        internal_counters.push_back(12531);
        internal_counters.push_back(12813);
        internal_counters.push_back(13095);
        internal_counters.push_back(13377);
        internal_counters.push_back(13659);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total bytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(64),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+", "664bb3ef-6eca-86b1-1e2d-30cb897b5fa9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9416);
        internal_counters.push_back(9698);
        internal_counters.push_back(9980);
        internal_counters.push_back(10262);
        internal_counters.push_back(10544);
        internal_counters.push_back(10826);
        internal_counters.push_back(11108);
        internal_counters.push_back(11390);
        internal_counters.push_back(11672);
        internal_counters.push_back(11954);
        internal_counters.push_back(12236);
        internal_counters.push_back(12518);
        internal_counters.push_back(12800);
        internal_counters.push_back(13082);
        internal_counters.push_back(13364);
        internal_counters.push_back(13646);
        internal_counters.push_back(9417);
        internal_counters.push_back(9699);
        internal_counters.push_back(9981);
        internal_counters.push_back(10263);
        internal_counters.push_back(10545);
        internal_counters.push_back(10827);
        internal_counters.push_back(11109);
        internal_counters.push_back(11391);
        internal_counters.push_back(11673);
        internal_counters.push_back(11955);
        internal_counters.push_back(12237);
        internal_counters.push_back(12519);
        internal_counters.push_back(12801);
        internal_counters.push_back(13083);
        internal_counters.push_back(13365);
        internal_counters.push_back(13647);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total bytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+", "f96f2c16-b1b4-4ec4-229c-fc82e6f80a82");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14871);
        internal_counters.push_back(14956);
        internal_counters.push_back(15041);
        internal_counters.push_back(15126);
        internal_counters.push_back(15211);
        internal_counters.push_back(15296);
        internal_counters.push_back(15381);
        internal_counters.push_back(15466);
        internal_counters.push_back(15551);
        internal_counters.push_back(15636);
        internal_counters.push_back(15721);
        internal_counters.push_back(15806);
        internal_counters.push_back(15891);
        internal_counters.push_back(15976);
        internal_counters.push_back(16061);
        internal_counters.push_back(16146);
        internal_counters.push_back(14880);
        internal_counters.push_back(14965);
        internal_counters.push_back(15050);
        internal_counters.push_back(15135);
        internal_counters.push_back(15220);
        internal_counters.push_back(15305);
        internal_counters.push_back(15390);
        internal_counters.push_back(15475);
        internal_counters.push_back(15560);
        internal_counters.push_back(15645);
        internal_counters.push_back(15730);
        internal_counters.push_back(15815);
        internal_counters.push_back(15900);
        internal_counters.push_back(15985);
        internal_counters.push_back(16070);
        internal_counters.push_back(16155);
        internal_counters.push_back(14881);
        internal_counters.push_back(14966);
        internal_counters.push_back(15051);
        internal_counters.push_back(15136);
        internal_counters.push_back(15221);
        internal_counters.push_back(15306);
        internal_counters.push_back(15391);
        internal_counters.push_back(15476);
        internal_counters.push_back(15561);
        internal_counters.push_back(15646);
        internal_counters.push_back(15731);
        internal_counters.push_back(15816);
        internal_counters.push_back(15901);
        internal_counters.push_back(15986);
        internal_counters.push_back(16071);
        internal_counters.push_back(16156);
        internal_counters.push_back(14882);
        internal_counters.push_back(14967);
        internal_counters.push_back(15052);
        internal_counters.push_back(15137);
        internal_counters.push_back(15222);
        internal_counters.push_back(15307);
        internal_counters.push_back(15392);
        internal_counters.push_back(15477);
        internal_counters.push_back(15562);
        internal_counters.push_back(15647);
        internal_counters.push_back(15732);
        internal_counters.push_back(15817);
        internal_counters.push_back(15902);
        internal_counters.push_back(15987);
        internal_counters.push_back(16072);
        internal_counters.push_back(16157);
        internal_counters.push_back(14883);
        internal_counters.push_back(14968);
        internal_counters.push_back(15053);
        internal_counters.push_back(15138);
        internal_counters.push_back(15223);
        internal_counters.push_back(15308);
        internal_counters.push_back(15393);
        internal_counters.push_back(15478);
        internal_counters.push_back(15563);
        internal_counters.push_back(15648);
        internal_counters.push_back(15733);
        internal_counters.push_back(15818);
        internal_counters.push_back(15903);
        internal_counters.push_back(15988);
        internal_counters.push_back(16073);
        internal_counters.push_back(16158);

        c.DefineDerivedCounter("L1CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum64,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "6deaf002-3cac-2d2d-7b89-566c7a52b08e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14871);
        internal_counters.push_back(14956);
        internal_counters.push_back(15041);
        internal_counters.push_back(15126);
        internal_counters.push_back(15211);
        internal_counters.push_back(15296);
        internal_counters.push_back(15381);
        internal_counters.push_back(15466);
        internal_counters.push_back(15551);
        internal_counters.push_back(15636);
        internal_counters.push_back(15721);
        internal_counters.push_back(15806);
        internal_counters.push_back(15891);
        internal_counters.push_back(15976);
        internal_counters.push_back(16061);
        internal_counters.push_back(16146);
        internal_counters.push_back(14880);
        internal_counters.push_back(14965);
        internal_counters.push_back(15050);
        internal_counters.push_back(15135);
        internal_counters.push_back(15220);
        internal_counters.push_back(15305);
        internal_counters.push_back(15390);
        internal_counters.push_back(15475);
        internal_counters.push_back(15560);
        internal_counters.push_back(15645);
        internal_counters.push_back(15730);
        internal_counters.push_back(15815);
        internal_counters.push_back(15900);
        internal_counters.push_back(15985);
        internal_counters.push_back(16070);
        internal_counters.push_back(16155);
        internal_counters.push_back(14881);
        internal_counters.push_back(14966);
        internal_counters.push_back(15051);
        internal_counters.push_back(15136);
        internal_counters.push_back(15221);
        internal_counters.push_back(15306);
        internal_counters.push_back(15391);
        internal_counters.push_back(15476);
        internal_counters.push_back(15561);
        internal_counters.push_back(15646);
        internal_counters.push_back(15731);
        internal_counters.push_back(15816);
        internal_counters.push_back(15901);
        internal_counters.push_back(15986);
        internal_counters.push_back(16071);
        internal_counters.push_back(16156);
        internal_counters.push_back(14882);
        internal_counters.push_back(14967);
        internal_counters.push_back(15052);
        internal_counters.push_back(15137);
        internal_counters.push_back(15222);
        internal_counters.push_back(15307);
        internal_counters.push_back(15392);
        internal_counters.push_back(15477);
        internal_counters.push_back(15562);
        internal_counters.push_back(15647);
        internal_counters.push_back(15732);
        internal_counters.push_back(15817);
        internal_counters.push_back(15902);
        internal_counters.push_back(15987);
        internal_counters.push_back(16072);
        internal_counters.push_back(16157);
        internal_counters.push_back(14883);
        internal_counters.push_back(14968);
        internal_counters.push_back(15053);
        internal_counters.push_back(15138);
        internal_counters.push_back(15223);
        internal_counters.push_back(15308);
        internal_counters.push_back(15393);
        internal_counters.push_back(15478);
        internal_counters.push_back(15563);
        internal_counters.push_back(15648);
        internal_counters.push_back(15733);
        internal_counters.push_back(15818);
        internal_counters.push_back(15903);
        internal_counters.push_back(15988);
        internal_counters.push_back(16073);
        internal_counters.push_back(16158);

        c.DefineDerivedCounter("L1CacheHitCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that hit the data in L1 cache.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum64,-", "279c8bff-ec6a-f9bf-96d7-5e8000f77891");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14880);
        internal_counters.push_back(14965);
        internal_counters.push_back(15050);
        internal_counters.push_back(15135);
        internal_counters.push_back(15220);
        internal_counters.push_back(15305);
        internal_counters.push_back(15390);
        internal_counters.push_back(15475);
        internal_counters.push_back(15560);
        internal_counters.push_back(15645);
        internal_counters.push_back(15730);
        internal_counters.push_back(15815);
        internal_counters.push_back(15900);
        internal_counters.push_back(15985);
        internal_counters.push_back(16070);
        internal_counters.push_back(16155);
        internal_counters.push_back(14881);
        internal_counters.push_back(14966);
        internal_counters.push_back(15051);
        internal_counters.push_back(15136);
        internal_counters.push_back(15221);
        internal_counters.push_back(15306);
        internal_counters.push_back(15391);
        internal_counters.push_back(15476);
        internal_counters.push_back(15561);
        internal_counters.push_back(15646);
        internal_counters.push_back(15731);
        internal_counters.push_back(15816);
        internal_counters.push_back(15901);
        internal_counters.push_back(15986);
        internal_counters.push_back(16071);
        internal_counters.push_back(16156);
        internal_counters.push_back(14882);
        internal_counters.push_back(14967);
        internal_counters.push_back(15052);
        internal_counters.push_back(15137);
        internal_counters.push_back(15222);
        internal_counters.push_back(15307);
        internal_counters.push_back(15392);
        internal_counters.push_back(15477);
        internal_counters.push_back(15562);
        internal_counters.push_back(15647);
        internal_counters.push_back(15732);
        internal_counters.push_back(15817);
        internal_counters.push_back(15902);
        internal_counters.push_back(15987);
        internal_counters.push_back(16072);
        internal_counters.push_back(16157);
        internal_counters.push_back(14883);
        internal_counters.push_back(14968);
        internal_counters.push_back(15053);
        internal_counters.push_back(15138);
        internal_counters.push_back(15223);
        internal_counters.push_back(15308);
        internal_counters.push_back(15393);
        internal_counters.push_back(15478);
        internal_counters.push_back(15563);
        internal_counters.push_back(15648);
        internal_counters.push_back(15733);
        internal_counters.push_back(15818);
        internal_counters.push_back(15903);
        internal_counters.push_back(15988);
        internal_counters.push_back(16073);
        internal_counters.push_back(16158);

        c.DefineDerivedCounter("L1CacheMissCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that miss the data in L1 cache.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64", "6e4ee364-41d7-476d-361d-f47b266c15db");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9407);
        internal_counters.push_back(9689);
        internal_counters.push_back(9971);
        internal_counters.push_back(10253);
        internal_counters.push_back(10535);
        internal_counters.push_back(10817);
        internal_counters.push_back(11099);
        internal_counters.push_back(11381);
        internal_counters.push_back(11663);
        internal_counters.push_back(11945);
        internal_counters.push_back(12227);
        internal_counters.push_back(12509);
        internal_counters.push_back(12791);
        internal_counters.push_back(13073);
        internal_counters.push_back(13355);
        internal_counters.push_back(13637);
        internal_counters.push_back(9409);
        internal_counters.push_back(9691);
        internal_counters.push_back(9973);
        internal_counters.push_back(10255);
        internal_counters.push_back(10537);
        internal_counters.push_back(10819);
        internal_counters.push_back(11101);
        internal_counters.push_back(11383);
        internal_counters.push_back(11665);
        internal_counters.push_back(11947);
        internal_counters.push_back(12229);
        internal_counters.push_back(12511);
        internal_counters.push_back(12793);
        internal_counters.push_back(13075);
        internal_counters.push_back(13357);
        internal_counters.push_back(13639);

        c.DefineDerivedCounter("L2CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the L2 cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "d78fdf66-104f-8372-02c1-91d07d7dc62e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9407);
        internal_counters.push_back(9689);
        internal_counters.push_back(9971);
        internal_counters.push_back(10253);
        internal_counters.push_back(10535);
        internal_counters.push_back(10817);
        internal_counters.push_back(11099);
        internal_counters.push_back(11381);
        internal_counters.push_back(11663);
        internal_counters.push_back(11945);
        internal_counters.push_back(12227);
        internal_counters.push_back(12509);
        internal_counters.push_back(12791);
        internal_counters.push_back(13073);
        internal_counters.push_back(13355);
        internal_counters.push_back(13637);
        internal_counters.push_back(9409);
        internal_counters.push_back(9691);
        internal_counters.push_back(9973);
        internal_counters.push_back(10255);
        internal_counters.push_back(10537);
        internal_counters.push_back(10819);
        internal_counters.push_back(11101);
        internal_counters.push_back(11383);
        internal_counters.push_back(11665);
        internal_counters.push_back(11947);
        internal_counters.push_back(12229);
        internal_counters.push_back(12511);
        internal_counters.push_back(12793);
        internal_counters.push_back(13075);
        internal_counters.push_back(13357);
        internal_counters.push_back(13639);

        c.DefineDerivedCounter("L2CacheMiss", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that miss the L2 cache. Value range: 0% (optimal) to 100% (all miss).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "4cd70885-41b3-25cd-92db-c76a0decc634");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9407);
        internal_counters.push_back(9689);
        internal_counters.push_back(9971);
        internal_counters.push_back(10253);
        internal_counters.push_back(10535);
        internal_counters.push_back(10817);
        internal_counters.push_back(11099);
        internal_counters.push_back(11381);
        internal_counters.push_back(11663);
        internal_counters.push_back(11945);
        internal_counters.push_back(12227);
        internal_counters.push_back(12509);
        internal_counters.push_back(12791);
        internal_counters.push_back(13073);
        internal_counters.push_back(13355);
        internal_counters.push_back(13637);

        c.DefineDerivedCounter("L2CacheHitCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that hit the L2 cache.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "d0bce171-560c-1895-66b3-bc56abccb077");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9409);
        internal_counters.push_back(9691);
        internal_counters.push_back(9973);
        internal_counters.push_back(10255);
        internal_counters.push_back(10537);
        internal_counters.push_back(10819);
        internal_counters.push_back(11101);
        internal_counters.push_back(11383);
        internal_counters.push_back(11665);
        internal_counters.push_back(11947);
        internal_counters.push_back(12229);
        internal_counters.push_back(12511);
        internal_counters.push_back(12793);
        internal_counters.push_back(13075);
        internal_counters.push_back(13357);
        internal_counters.push_back(13639);

        c.DefineDerivedCounter("L2CacheMissCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that miss the L2 cache.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "f2ab3a1a-ead6-9893-961b-88ba2a758807");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7428);
        internal_counters.push_back(7547);
        internal_counters.push_back(7666);
        internal_counters.push_back(7785);
        internal_counters.push_back(7904);
        internal_counters.push_back(8023);
        internal_counters.push_back(8142);
        internal_counters.push_back(8261);
        internal_counters.push_back(8380);
        internal_counters.push_back(8499);
        internal_counters.push_back(8618);
        internal_counters.push_back(8737);
        internal_counters.push_back(8856);
        internal_counters.push_back(8975);
        internal_counters.push_back(9094);
        internal_counters.push_back(9213);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7428);
        internal_counters.push_back(7547);
        internal_counters.push_back(7666);
        internal_counters.push_back(7785);
        internal_counters.push_back(7904);
        internal_counters.push_back(8023);
        internal_counters.push_back(8142);
        internal_counters.push_back(8261);
        internal_counters.push_back(8380);
        internal_counters.push_back(8499);
        internal_counters.push_back(8618);
        internal_counters.push_back(8737);
        internal_counters.push_back(8856);
        internal_counters.push_back(8975);
        internal_counters.push_back(9094);
        internal_counters.push_back(9213);

        c.DefineDerivedCounter("MemUnitBusyCycles", "GlobalMemory", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalledCycles). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "168f077c-4797-b2f5-717f-105c725266c8");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14817);
        internal_counters.push_back(14902);
        internal_counters.push_back(14987);
        internal_counters.push_back(15072);
        internal_counters.push_back(15157);
        internal_counters.push_back(15242);
        internal_counters.push_back(15327);
        internal_counters.push_back(15412);
        internal_counters.push_back(15497);
        internal_counters.push_back(15582);
        internal_counters.push_back(15667);
        internal_counters.push_back(15752);
        internal_counters.push_back(15837);
        internal_counters.push_back(15922);
        internal_counters.push_back(16007);
        internal_counters.push_back(16092);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14817);
        internal_counters.push_back(14902);
        internal_counters.push_back(14987);
        internal_counters.push_back(15072);
        internal_counters.push_back(15157);
        internal_counters.push_back(15242);
        internal_counters.push_back(15327);
        internal_counters.push_back(15412);
        internal_counters.push_back(15497);
        internal_counters.push_back(15582);
        internal_counters.push_back(15667);
        internal_counters.push_back(15752);
        internal_counters.push_back(15837);
        internal_counters.push_back(15922);
        internal_counters.push_back(16007);
        internal_counters.push_back(16092);

        c.DefineDerivedCounter("MemUnitStalledCycles", "GlobalMemory", "Number of GPU cycles the memory unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "2745659a-0e40-bace-3b9b-86a54f8e4623");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9420);
        internal_counters.push_back(9702);
        internal_counters.push_back(9984);
        internal_counters.push_back(10266);
        internal_counters.push_back(10548);
        internal_counters.push_back(10830);
        internal_counters.push_back(11112);
        internal_counters.push_back(11394);
        internal_counters.push_back(11676);
        internal_counters.push_back(11958);
        internal_counters.push_back(12240);
        internal_counters.push_back(12522);
        internal_counters.push_back(12804);
        internal_counters.push_back(13086);
        internal_counters.push_back(13368);
        internal_counters.push_back(13650);
        internal_counters.push_back(1799);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9420);
        internal_counters.push_back(9702);
        internal_counters.push_back(9984);
        internal_counters.push_back(10266);
        internal_counters.push_back(10548);
        internal_counters.push_back(10830);
        internal_counters.push_back(11112);
        internal_counters.push_back(11394);
        internal_counters.push_back(11676);
        internal_counters.push_back(11958);
        internal_counters.push_back(12240);
        internal_counters.push_back(12522);
        internal_counters.push_back(12804);
        internal_counters.push_back(13086);
        internal_counters.push_back(13368);
        internal_counters.push_back(13650);

        c.DefineDerivedCounter("WriteUnitStalledCycles", "GlobalMemory", "Number of GPU cycles the Write unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "ede3305e-abd4-d6bf-6b00-ffc57a29fce3");
    }
}

