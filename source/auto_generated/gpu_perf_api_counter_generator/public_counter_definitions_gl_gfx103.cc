//==============================================================================
// Copyright (c) 2010-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for GL GFX103.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_gl_gfx103.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersGlGfx103(GpaDerivedCounters& c)
{
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(25620);

        c.DefineDerivedCounter("GPUTime", "Timing", "Time this API command took to execute on the GPU in nanoseconds from the time the previous command reached the bottom of the pipeline (BOP) to the time this command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "0,TS_FREQ,/,(1000000000),*", "cbd338f2-de6c-7b14-92ad-ba724ca2e501");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1836);
        internal_counters.push_back(1812);

        c.DefineDerivedCounter("GPUBusy", "Timing", "The percentage of time the GPU command processor was busy.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,/,(100),*,(100),min", "b1ba5363-1abc-fe66-2fdd-1fe6ee8989a0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("GPUBusyCycles", "Timing", "Number of GPU cycles that the GPU command processor was busy.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0", "451cb045-23af-ac44-4603-d5832fa041d9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(25455);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("TessellatorBusy", "Timing", "The percentage of time the tessellation engine is busy.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,/,(100),*", "36af6c72-dcfb-8102-4fd4-ce8ddc573365");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(25455);

        c.DefineDerivedCounter("TessellatorBusyCycles", "Timing", "Number of GPU cycles that the tessellation engine is busy.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0", "60289dcb-7b33-46e7-26d1-8a2121605543");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4915);
        internal_counters.push_back(4932);
        internal_counters.push_back(4955);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("VsGsBusy", "Timing", "The percentage of time the ShaderUnit has VS or GS work to do in a VS-[GS-]PS pipeline.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,max,NUM_SHADER_ENGINES,/,(0),2,ifnotzero,3,/,(100),*,(100),min", "969c41c7-eb0b-9706-a7a1-98f27c3af56b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4915);
        internal_counters.push_back(4932);
        internal_counters.push_back(4955);

        c.DefineDerivedCounter("VsGsBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has VS or GS work to do in a VS-[GS-]PS pipeline.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,max,NUM_SHADER_ENGINES,/,(0),2,ifnotzero", "a8420bb7-6bd8-930a-9088-d73b9c039851");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(25620);
        internal_counters.push_back(4915);
        internal_counters.push_back(4932);
        internal_counters.push_back(4955);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("VsGsTime", "Timing", "Time VS or GS are busy in nanoseconds in a VS-[GS-]PS pipeline.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "1,2,max,NUM_SHADER_ENGINES,/,(0),3,ifnotzero,4,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "3ce33b11-210d-b3de-9b6c-b9f3cd04beff");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4948);
        internal_counters.push_back(4955);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("PreTessellationBusy", "Timing", "The percentage of time the ShaderUnit has VS and HS work to do in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,NUM_SHADER_ENGINES,/,1,ifnotzero,2,/,(100),*,(100),min", "346c7430-4666-7065-b5b7-1cb8cbb1c01c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4948);
        internal_counters.push_back(4955);

        c.DefineDerivedCounter("PreTessellationBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has VS and HS work to do in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,NUM_SHADER_ENGINES,/,1,ifnotzero", "dac68e38-0e3a-9364-2674-308e63bee2d2");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(25620);
        internal_counters.push_back(4948);
        internal_counters.push_back(4955);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("PreTessellationTime", "Timing", "Time VS and HS are busy in nanoseconds in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,NUM_SHADER_ENGINES,/,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "d5e6c54c-5ffb-b173-6118-bece61f0281c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4915);
        internal_counters.push_back(4932);
        internal_counters.push_back(4955);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("PostTessellationBusy", "Timing", "The percentage of time the ShaderUnit has DS or GS work to do in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,max,NUM_SHADER_ENGINES,/,2,ifnotzero,3,/,(100),*,(100),min", "1a275c68-9340-f358-71c6-a2648390381d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4915);
        internal_counters.push_back(4932);
        internal_counters.push_back(4955);

        c.DefineDerivedCounter("PostTessellationBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has DS or GS work to do in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,max,NUM_SHADER_ENGINES,/,2,ifnotzero", "a5ed943b-13ef-942b-56fb-6d519eeb7337");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(25620);
        internal_counters.push_back(4915);
        internal_counters.push_back(4932);
        internal_counters.push_back(4955);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("PostTessellationTime", "Timing", "Time DS or GS are busy in nanoseconds in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,max,NUM_SHADER_ENGINES,/,3,ifnotzero,4,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "9f8dfa40-faee-2014-3467-2630a7d95c1e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4974);
        internal_counters.push_back(4994);
        internal_counters.push_back(4975);
        internal_counters.push_back(4995);
        internal_counters.push_back(4976);
        internal_counters.push_back(4996);
        internal_counters.push_back(4977);
        internal_counters.push_back(4997);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("PSBusy", "Timing", "The percentage of time the ShaderUnit has pixel shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,(0),4,5,ifnotzero,(0),6,7,ifnotzero,max4,8,/,(100),*,(100),min", "7e772beb-d82c-bd9a-aed0-fe504d416ce5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4974);
        internal_counters.push_back(4994);
        internal_counters.push_back(4975);
        internal_counters.push_back(4995);
        internal_counters.push_back(4976);
        internal_counters.push_back(4996);
        internal_counters.push_back(4977);
        internal_counters.push_back(4997);

        c.DefineDerivedCounter("PSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has pixel shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,(0),4,5,ifnotzero,(0),6,7,ifnotzero,max4", "b58bea04-ce8e-2984-80f4-8aba7d4c817b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(25620);
        internal_counters.push_back(4974);
        internal_counters.push_back(4994);
        internal_counters.push_back(4975);
        internal_counters.push_back(4995);
        internal_counters.push_back(4976);
        internal_counters.push_back(4996);
        internal_counters.push_back(4977);
        internal_counters.push_back(4997);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("PSTime", "Timing", "Time pixel shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,ifnotzero,(0),3,4,ifnotzero,(0),5,6,ifnotzero,(0),7,8,ifnotzero,max4,9,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "edca7694-7416-e8a6-0c5a-63a5ad5f3d74");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4959);
        internal_counters.push_back(4963);
        internal_counters.push_back(4965);
        internal_counters.push_back(4969);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("CSBusy", "Timing", "The percentage of time the ShaderUnit has compute shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,max,4,/,(100),*,(100),min", "493fdd90-8d2b-a055-5e4e-2d29c3396b8c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4959);
        internal_counters.push_back(4963);
        internal_counters.push_back(4965);
        internal_counters.push_back(4969);

        c.DefineDerivedCounter("CSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has compute shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,max", "39bcf1b8-f6b2-4c37-f9af-0a2bb59512f9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(25620);
        internal_counters.push_back(4959);
        internal_counters.push_back(4963);
        internal_counters.push_back(4965);
        internal_counters.push_back(4969);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("CSTime", "Timing", "Time compute shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,ifnotzero,(0),3,4,ifnotzero,max,5,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "dbc24916-ecb2-7eef-8d63-7afadaaab6bc");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(25549);
        internal_counters.push_back(4955);

        c.DefineDerivedCounter("VsGsVerticesIn", "VertexGeometry", "The number of unique vertices processed by the VS and GS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,(0),1,ifnotzero", "17d0c775-3ed5-affb-d5ac-5391a198a4aa");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(25556);
        internal_counters.push_back(4955);

        c.DefineDerivedCounter("VsGsPrimsIn", "VertexGeometry", "The number of primitives passed into the VS and GS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,(0),1,ifnotzero", "1bbdf2ec-cca3-4d9a-a243-94f4aec5409b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(25587);
        internal_counters.push_back(4955);

        c.DefineDerivedCounter("GSVerticesOut", "VertexGeometry", "The number of vertices output by the GS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,(0),1,ifnotzero", "775b9736-319a-bd8a-48c9-68db9c91d978");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(25562);
        internal_counters.push_back(4955);

        c.DefineDerivedCounter("PreTessVerticesIn", "PreTessellation", "The number of vertices processed by the VS and HS when using tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,ifnotzero", "b0d4c894-2fd0-6f4f-0b07-d5369769ef2d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(25480);
        internal_counters.push_back(4955);

        c.DefineDerivedCounter("PostTessPrimsOut", "PostTessellation", "The number of primitives output by the DS and GS when using tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,ifnotzero", "d38dabe8-1f13-ea34-d3c1-eb5783b737f1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3587);
        internal_counters.push_back(3591);
        internal_counters.push_back(3543);
        internal_counters.push_back(3555);
        internal_counters.push_back(3544);
        internal_counters.push_back(3556);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("PrimitiveAssemblyBusy", "Timing", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max,6,/,(100),*,(100),min", "54ac5640-c4d7-95e2-20e0-6a9fdfc07333");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3587);
        internal_counters.push_back(3591);
        internal_counters.push_back(3543);
        internal_counters.push_back(3555);
        internal_counters.push_back(3544);
        internal_counters.push_back(3556);

        c.DefineDerivedCounter("PrimitiveAssemblyBusyCycles", "Timing", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max", "99777f2d-9626-c78a-a97c-c4505eba1e5f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3490);

        c.DefineDerivedCounter("PrimitivesIn", "PrimitiveAssembly", "The number of primitives received by the hardware. This includes primitives generated by tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "a515b80d-75c3-c7d2-0d2f-d7766b4759a6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3496);
        internal_counters.push_back(3536);
        internal_counters.push_back(3537);
        internal_counters.push_back(3538);
        internal_counters.push_back(3539);

        c.DefineDerivedCounter("CulledPrims", "PrimitiveAssembly", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,+,2,+,3,+,4,+", "589bdf55-9192-280a-41c3-584bc94f2562");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3503);

        c.DefineDerivedCounter("ClippedPrims", "PrimitiveAssembly", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "5ef6f9d5-155e-5baa-163f-8359d9ea9bbf");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3591);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("PAStalledOnRasterizer", "PrimitiveAssembly", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_PRIM_PIPES,/,1,/,(100),*", "6f9f416b-53c1-0457-f88c-7b6ba8973974");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3591);

        c.DefineDerivedCounter("PAStalledOnRasterizerCycles", "PrimitiveAssembly", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_PRIM_PIPES,/", "7a8c492a-c566-9328-6805-760dbff5c0f2");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9354);
        internal_counters.push_back(9359);
        internal_counters.push_back(9364);
        internal_counters.push_back(9369);

        c.DefineDerivedCounter("PSPixelsOut", "PixelShader", "Pixels exported from shader to color buffers. Does not include killed or alpha tested pixels; if there are multiple render targets, each render target receives one export, so this will be 2 for 1 pixel written to two RTs.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "24cba16c-baa6-6ecd-95ad-92ecb1338da1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9356);
        internal_counters.push_back(9361);
        internal_counters.push_back(9366);
        internal_counters.push_back(9371);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("PSExportStalls", "PixelShader", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,max4,4,/,NUM_SHADER_ARRAYS,/,(100),*", "9b4f466c-ff97-22bb-557d-84d3c4c51895");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9356);
        internal_counters.push_back(9361);
        internal_counters.push_back(9366);
        internal_counters.push_back(9371);

        c.DefineDerivedCounter("PSExportStallsCycles", "PixelShader", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,max,2,max,3,max,NUM_SHADER_ARRAYS,/", "47c72aad-64e6-0864-d533-d8e0bc27c156");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4960);
        internal_counters.push_back(4966);

        c.DefineDerivedCounter("CSThreadGroups", "ComputeShader", "Total number of thread groups.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,+", "8ce3fc80-56b2-97f9-8e70-2e8c747cea68");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8834);

        c.DefineDerivedCounter("CSWavefronts", "ComputeShader", "The total number of wavefronts used for the CS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "42379c6e-369b-c237-8b25-cdb9cdc65c4d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8838);

        c.DefineDerivedCounter("CSThreads", "ComputeShader", "The number of CS threads processed by the hardware.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "7a648013-6eac-2665-ac36-13c6f4ac9c26");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8838);
        internal_counters.push_back(4960);
        internal_counters.push_back(4966);

        c.DefineDerivedCounter("CSThreadGroupSize", "ComputeShader", "The number of CS threads within each thread group.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,2,+,/,1,2,+,ifnotzero", "8c65008a-9957-7ca6-4199-f6fe940420f6");
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
        internal_counters.push_back(4960);
        internal_counters.push_back(4966);

        c.DefineDerivedCounter("CSMemUnitBusy", "ComputeShader", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*,17,18,+,ifnotzero", "42ab96e1-0a24-96c8-c4ff-098fa267d78e");
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
        internal_counters.push_back(4960);
        internal_counters.push_back(4966);

        c.DefineDerivedCounter("CSMemUnitBusyCycles", "ComputeShader", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ARRAYS,/,16,17,+,ifnotzero", "39d5687f-c727-7c0c-af82-bb711d3897ed");
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
        internal_counters.push_back(4960);
        internal_counters.push_back(4966);

        c.DefineDerivedCounter("CSMemUnitStalled", "ComputeShader", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*,17,18,+,ifnotzero", "f18e8679-1511-d533-d9ee-4365197f7d0c");
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
        internal_counters.push_back(4960);
        internal_counters.push_back(4966);

        c.DefineDerivedCounter("CSMemUnitStalledCycles", "ComputeShader", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ARRAYS,/,16,17,+,ifnotzero", "51991c84-ed2b-bf31-c4ab-8f8e9eb8f29f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(18240);
        internal_counters.push_back(18494);
        internal_counters.push_back(18748);
        internal_counters.push_back(19002);
        internal_counters.push_back(19256);
        internal_counters.push_back(19510);
        internal_counters.push_back(19764);
        internal_counters.push_back(20018);
        internal_counters.push_back(20272);
        internal_counters.push_back(20526);
        internal_counters.push_back(20780);
        internal_counters.push_back(21034);
        internal_counters.push_back(21288);
        internal_counters.push_back(21542);
        internal_counters.push_back(21796);
        internal_counters.push_back(22050);
        internal_counters.push_back(1836);
        internal_counters.push_back(4960);
        internal_counters.push_back(4966);

        c.DefineDerivedCounter("CSWriteUnitStalled", "ComputeShader", "The percentage of GPUTime the write unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,18,+,ifnotzero", "55118f7a-8f92-726f-78c6-407f689a2eb4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(18240);
        internal_counters.push_back(18494);
        internal_counters.push_back(18748);
        internal_counters.push_back(19002);
        internal_counters.push_back(19256);
        internal_counters.push_back(19510);
        internal_counters.push_back(19764);
        internal_counters.push_back(20018);
        internal_counters.push_back(20272);
        internal_counters.push_back(20526);
        internal_counters.push_back(20780);
        internal_counters.push_back(21034);
        internal_counters.push_back(21288);
        internal_counters.push_back(21542);
        internal_counters.push_back(21796);
        internal_counters.push_back(22050);
        internal_counters.push_back(4960);
        internal_counters.push_back(4966);

        c.DefineDerivedCounter("CSWriteUnitStalledCycles", "ComputeShader", "Number of GPU cycles the write unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,17,+,ifnotzero", "be164c60-5e48-acac-9622-29616d09aa9a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8885);
        internal_counters.push_back(8834);

        c.DefineDerivedCounter("CSGDSInsts", "ComputeShader", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "2a867f3e-4a37-ad16-55d1-f03d74707819");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8889);
        internal_counters.push_back(8834);

        c.DefineDerivedCounter("CSLDSInsts", "ComputeShader", "The average number of LDS read/write instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "61b0b351-7e06-ef8e-a8e0-7a9e3200a836");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8861);
        internal_counters.push_back(8834);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("CSALUStalledByLDS", "ComputeShader", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,/,2,/,NUM_SHADER_ENGINES,/,(100),*,1,ifnotzero", "6dc4f1c2-bad0-c9ff-156e-883b319a752a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8861);

        c.DefineDerivedCounter("CSALUStalledByLDSCycles", "ComputeShader", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_SHADER_ENGINES,/", "8f3d5f25-2159-0374-fafe-e26a7799b6c8");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9115);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("CSLDSBankConflict", "ComputeShader", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,/,NUM_SIMDS,/,(100),*", "1065ee10-2e41-ea41-1eb3-b61b491752f4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9115);

        c.DefineDerivedCounter("CSLDSBankConflictCycles", "ComputeShader", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad).", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_SIMDS,/", "1fd1adf3-c51e-94fd-083e-c482a0a0809e");
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

        c.DefineDerivedCounter("TexUnitBusy", "Timing", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "36afb8d9-42fc-aafe-66c5-449542153b2c");
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

        c.DefineDerivedCounter("TexUnitBusyCycles", "Timing", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ARRAYS,/", "c68761f2-248c-4f39-6528-c308b1c0807c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9636);
        internal_counters.push_back(9872);
        internal_counters.push_back(10108);
        internal_counters.push_back(10344);
        internal_counters.push_back(10580);
        internal_counters.push_back(10816);
        internal_counters.push_back(11052);
        internal_counters.push_back(11288);
        internal_counters.push_back(11524);
        internal_counters.push_back(11760);
        internal_counters.push_back(11996);
        internal_counters.push_back(12232);
        internal_counters.push_back(12468);
        internal_counters.push_back(12704);
        internal_counters.push_back(12940);
        internal_counters.push_back(13176);
        internal_counters.push_back(9635);
        internal_counters.push_back(9871);
        internal_counters.push_back(10107);
        internal_counters.push_back(10343);
        internal_counters.push_back(10579);
        internal_counters.push_back(10815);
        internal_counters.push_back(11051);
        internal_counters.push_back(11287);
        internal_counters.push_back(11523);
        internal_counters.push_back(11759);
        internal_counters.push_back(11995);
        internal_counters.push_back(12231);
        internal_counters.push_back(12467);
        internal_counters.push_back(12703);
        internal_counters.push_back(12939);
        internal_counters.push_back(13175);

        c.DefineDerivedCounter("TexTriFilteringPct", "TextureUnit", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,+,/,(100),*", "1affc3c8-b917-5c81-622b-7004527208ae");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9636);
        internal_counters.push_back(9872);
        internal_counters.push_back(10108);
        internal_counters.push_back(10344);
        internal_counters.push_back(10580);
        internal_counters.push_back(10816);
        internal_counters.push_back(11052);
        internal_counters.push_back(11288);
        internal_counters.push_back(11524);
        internal_counters.push_back(11760);
        internal_counters.push_back(11996);
        internal_counters.push_back(12232);
        internal_counters.push_back(12468);
        internal_counters.push_back(12704);
        internal_counters.push_back(12940);
        internal_counters.push_back(13176);

        c.DefineDerivedCounter("TexTriFilteringCount", "TextureUnit", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(4),*", "5785b3a1-a513-18db-4b1c-bdeef75bb2b6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9635);
        internal_counters.push_back(9871);
        internal_counters.push_back(10107);
        internal_counters.push_back(10343);
        internal_counters.push_back(10579);
        internal_counters.push_back(10815);
        internal_counters.push_back(11051);
        internal_counters.push_back(11287);
        internal_counters.push_back(11523);
        internal_counters.push_back(11759);
        internal_counters.push_back(11995);
        internal_counters.push_back(12231);
        internal_counters.push_back(12467);
        internal_counters.push_back(12703);
        internal_counters.push_back(12939);
        internal_counters.push_back(13175);

        c.DefineDerivedCounter("NoTexTriFilteringCount", "TextureUnit", "Count of pixels that did not receive trilinear filtering.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(4),*", "179da29a-81af-c06e-ce8c-a0a731ea030d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9638);
        internal_counters.push_back(9874);
        internal_counters.push_back(10110);
        internal_counters.push_back(10346);
        internal_counters.push_back(10582);
        internal_counters.push_back(10818);
        internal_counters.push_back(11054);
        internal_counters.push_back(11290);
        internal_counters.push_back(11526);
        internal_counters.push_back(11762);
        internal_counters.push_back(11998);
        internal_counters.push_back(12234);
        internal_counters.push_back(12470);
        internal_counters.push_back(12706);
        internal_counters.push_back(12942);
        internal_counters.push_back(13178);
        internal_counters.push_back(9637);
        internal_counters.push_back(9873);
        internal_counters.push_back(10109);
        internal_counters.push_back(10345);
        internal_counters.push_back(10581);
        internal_counters.push_back(10817);
        internal_counters.push_back(11053);
        internal_counters.push_back(11289);
        internal_counters.push_back(11525);
        internal_counters.push_back(11761);
        internal_counters.push_back(11997);
        internal_counters.push_back(12233);
        internal_counters.push_back(12469);
        internal_counters.push_back(12705);
        internal_counters.push_back(12941);
        internal_counters.push_back(13177);

        c.DefineDerivedCounter("TexVolFilteringPct", "TextureUnit", "Percentage of pixels that received volume filtering.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,+,/,(100),*", "b5ff6bed-3178-aee4-42dd-c74391c02a2d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9638);
        internal_counters.push_back(9874);
        internal_counters.push_back(10110);
        internal_counters.push_back(10346);
        internal_counters.push_back(10582);
        internal_counters.push_back(10818);
        internal_counters.push_back(11054);
        internal_counters.push_back(11290);
        internal_counters.push_back(11526);
        internal_counters.push_back(11762);
        internal_counters.push_back(11998);
        internal_counters.push_back(12234);
        internal_counters.push_back(12470);
        internal_counters.push_back(12706);
        internal_counters.push_back(12942);
        internal_counters.push_back(13178);

        c.DefineDerivedCounter("TexVolFilteringCount", "TextureUnit", "Count of pixels that received volume filtering.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(4),*", "4bddc587-d589-8128-e18c-762eab2c871f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9637);
        internal_counters.push_back(9873);
        internal_counters.push_back(10109);
        internal_counters.push_back(10345);
        internal_counters.push_back(10581);
        internal_counters.push_back(10817);
        internal_counters.push_back(11053);
        internal_counters.push_back(11289);
        internal_counters.push_back(11525);
        internal_counters.push_back(11761);
        internal_counters.push_back(11997);
        internal_counters.push_back(12233);
        internal_counters.push_back(12469);
        internal_counters.push_back(12705);
        internal_counters.push_back(12941);
        internal_counters.push_back(13177);

        c.DefineDerivedCounter("NoTexVolFilteringCount", "TextureUnit", "Count of pixels that did not receive volume filtering.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(4),*", "9fe1a854-17c6-9d26-b2b9-80610cd5827d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9656);
        internal_counters.push_back(9892);
        internal_counters.push_back(10128);
        internal_counters.push_back(10364);
        internal_counters.push_back(10600);
        internal_counters.push_back(10836);
        internal_counters.push_back(11072);
        internal_counters.push_back(11308);
        internal_counters.push_back(11544);
        internal_counters.push_back(11780);
        internal_counters.push_back(12016);
        internal_counters.push_back(12252);
        internal_counters.push_back(12488);
        internal_counters.push_back(12724);
        internal_counters.push_back(12960);
        internal_counters.push_back(13196);
        internal_counters.push_back(9657);
        internal_counters.push_back(9893);
        internal_counters.push_back(10129);
        internal_counters.push_back(10365);
        internal_counters.push_back(10601);
        internal_counters.push_back(10837);
        internal_counters.push_back(11073);
        internal_counters.push_back(11309);
        internal_counters.push_back(11545);
        internal_counters.push_back(11781);
        internal_counters.push_back(12017);
        internal_counters.push_back(12253);
        internal_counters.push_back(12489);
        internal_counters.push_back(12725);
        internal_counters.push_back(12961);
        internal_counters.push_back(13197);
        internal_counters.push_back(9658);
        internal_counters.push_back(9894);
        internal_counters.push_back(10130);
        internal_counters.push_back(10366);
        internal_counters.push_back(10602);
        internal_counters.push_back(10838);
        internal_counters.push_back(11074);
        internal_counters.push_back(11310);
        internal_counters.push_back(11546);
        internal_counters.push_back(11782);
        internal_counters.push_back(12018);
        internal_counters.push_back(12254);
        internal_counters.push_back(12490);
        internal_counters.push_back(12726);
        internal_counters.push_back(12962);
        internal_counters.push_back(13198);
        internal_counters.push_back(9659);
        internal_counters.push_back(9895);
        internal_counters.push_back(10131);
        internal_counters.push_back(10367);
        internal_counters.push_back(10603);
        internal_counters.push_back(10839);
        internal_counters.push_back(11075);
        internal_counters.push_back(11311);
        internal_counters.push_back(11547);
        internal_counters.push_back(11783);
        internal_counters.push_back(12019);
        internal_counters.push_back(12255);
        internal_counters.push_back(12491);
        internal_counters.push_back(12727);
        internal_counters.push_back(12963);
        internal_counters.push_back(13199);
        internal_counters.push_back(9660);
        internal_counters.push_back(9896);
        internal_counters.push_back(10132);
        internal_counters.push_back(10368);
        internal_counters.push_back(10604);
        internal_counters.push_back(10840);
        internal_counters.push_back(11076);
        internal_counters.push_back(11312);
        internal_counters.push_back(11548);
        internal_counters.push_back(11784);
        internal_counters.push_back(12020);
        internal_counters.push_back(12256);
        internal_counters.push_back(12492);
        internal_counters.push_back(12728);
        internal_counters.push_back(12964);
        internal_counters.push_back(13200);
        internal_counters.push_back(9661);
        internal_counters.push_back(9897);
        internal_counters.push_back(10133);
        internal_counters.push_back(10369);
        internal_counters.push_back(10605);
        internal_counters.push_back(10841);
        internal_counters.push_back(11077);
        internal_counters.push_back(11313);
        internal_counters.push_back(11549);
        internal_counters.push_back(11785);
        internal_counters.push_back(12021);
        internal_counters.push_back(12257);
        internal_counters.push_back(12493);
        internal_counters.push_back(12729);
        internal_counters.push_back(12965);
        internal_counters.push_back(13201);
        internal_counters.push_back(9662);
        internal_counters.push_back(9898);
        internal_counters.push_back(10134);
        internal_counters.push_back(10370);
        internal_counters.push_back(10606);
        internal_counters.push_back(10842);
        internal_counters.push_back(11078);
        internal_counters.push_back(11314);
        internal_counters.push_back(11550);
        internal_counters.push_back(11786);
        internal_counters.push_back(12022);
        internal_counters.push_back(12258);
        internal_counters.push_back(12494);
        internal_counters.push_back(12730);
        internal_counters.push_back(12966);
        internal_counters.push_back(13202);
        internal_counters.push_back(9663);
        internal_counters.push_back(9899);
        internal_counters.push_back(10135);
        internal_counters.push_back(10371);
        internal_counters.push_back(10607);
        internal_counters.push_back(10843);
        internal_counters.push_back(11079);
        internal_counters.push_back(11315);
        internal_counters.push_back(11551);
        internal_counters.push_back(11787);
        internal_counters.push_back(12023);
        internal_counters.push_back(12259);
        internal_counters.push_back(12495);
        internal_counters.push_back(12731);
        internal_counters.push_back(12967);
        internal_counters.push_back(13203);
        internal_counters.push_back(9664);
        internal_counters.push_back(9900);
        internal_counters.push_back(10136);
        internal_counters.push_back(10372);
        internal_counters.push_back(10608);
        internal_counters.push_back(10844);
        internal_counters.push_back(11080);
        internal_counters.push_back(11316);
        internal_counters.push_back(11552);
        internal_counters.push_back(11788);
        internal_counters.push_back(12024);
        internal_counters.push_back(12260);
        internal_counters.push_back(12496);
        internal_counters.push_back(12732);
        internal_counters.push_back(12968);
        internal_counters.push_back(13204);

        c.DefineDerivedCounter("TexAveAnisotropy", "TextureUnit", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(2),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,*,+,(4),32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,*,+,(6),48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,*,+,(8),64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,*,+,(10),80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,*,+,(12),96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,*,+,(14),112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,*,+,(16),128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,*,+,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,+,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,+,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,+,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,+,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,+,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,+,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,+,/", "7ca2a2b9-a4eb-ce23-d163-59147e672396");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1996);
        internal_counters.push_back(2387);
        internal_counters.push_back(2778);
        internal_counters.push_back(3169);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("DepthStencilTestBusy", "Timing", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "6834fb52-42e8-bb50-fd48-ec2f2904e7e0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1996);
        internal_counters.push_back(2387);
        internal_counters.push_back(2778);
        internal_counters.push_back(3169);

        c.DefineDerivedCounter("DepthStencilTestBusyCycles", "Timing", "Number of GPU cycles spent performing depth and stencil tests.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "07ad48f0-49d8-87e7-1ef5-1e24ff2cef49");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1867);
        internal_counters.push_back(2258);
        internal_counters.push_back(2649);
        internal_counters.push_back(3040);
        internal_counters.push_back(1856);
        internal_counters.push_back(2247);
        internal_counters.push_back(2638);
        internal_counters.push_back(3029);

        c.DefineDerivedCounter("HiZTilesAccepted", "DepthAndStencil", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "4,5,6,7,sum4,0,1,2,3,sum4,-,(0),max,4,5,6,7,sum4,/,(100),*", "56176f45-d7ff-813d-4f05-3b2f046067e7");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1856);
        internal_counters.push_back(2247);
        internal_counters.push_back(2638);
        internal_counters.push_back(3029);
        internal_counters.push_back(1867);
        internal_counters.push_back(2258);
        internal_counters.push_back(2649);
        internal_counters.push_back(3040);

        c.DefineDerivedCounter("HiZTilesAcceptedCount", "DepthAndStencil", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4,4,5,6,7,sum4,-,(0),max", "95d4e3f6-b2f0-f26e-8423-aacdfaf79ea3");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1867);
        internal_counters.push_back(2258);
        internal_counters.push_back(2649);
        internal_counters.push_back(3040);

        c.DefineDerivedCounter("HiZTilesRejectedCount", "DepthAndStencil", "Count of tiles not accepted by HiZ.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "156ba142-7eeb-aa6e-a00a-f8aea4e41e0b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1856);
        internal_counters.push_back(2247);
        internal_counters.push_back(2638);
        internal_counters.push_back(3029);
        internal_counters.push_back(1880);
        internal_counters.push_back(2271);
        internal_counters.push_back(2662);
        internal_counters.push_back(3053);

        c.DefineDerivedCounter("PreZTilesDetailCulled", "DepthAndStencil", "Percentage of tiles rejected because the associated prim had no contributing area.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "4,5,6,7,sum4,0,1,2,3,sum4,/,(100),*", "cad7f54d-a044-7574-c472-6f2065cbeeac");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1880);
        internal_counters.push_back(2271);
        internal_counters.push_back(2662);
        internal_counters.push_back(3053);

        c.DefineDerivedCounter("PreZTilesDetailCulledCount", "DepthAndStencil", "Count of tiles rejected because the associated primitive had no contributing area.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "49262c8a-b1e6-90dd-f096-0fc4921715e9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1856);
        internal_counters.push_back(2247);
        internal_counters.push_back(2638);
        internal_counters.push_back(3029);

        c.DefineDerivedCounter("PreZTilesDetailSurvivingCount", "DepthAndStencil", "Count of tiles surviving because the associated primitive had contributing area.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "f803eaa4-bbed-bd39-775f-a64df92e2c08");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3917);
        internal_counters.push_back(4495);
        internal_counters.push_back(3918);
        internal_counters.push_back(4496);
        internal_counters.push_back(3919);
        internal_counters.push_back(4497);
        internal_counters.push_back(3920);
        internal_counters.push_back(4498);
        internal_counters.push_back(3993);
        internal_counters.push_back(4571);
        internal_counters.push_back(3994);
        internal_counters.push_back(4572);
        internal_counters.push_back(3995);
        internal_counters.push_back(4573);
        internal_counters.push_back(3996);
        internal_counters.push_back(4574);

        c.DefineDerivedCounter("HiZQuadsCulled", "DepthAndStencil", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,sum8,-,(0),max,0,1,2,3,4,5,6,7,sum8,/,(100),*", "fa0e319b-5573-6d34-5bab-904769925036");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3917);
        internal_counters.push_back(4495);
        internal_counters.push_back(3918);
        internal_counters.push_back(4496);
        internal_counters.push_back(3919);
        internal_counters.push_back(4497);
        internal_counters.push_back(3920);
        internal_counters.push_back(4498);
        internal_counters.push_back(3993);
        internal_counters.push_back(4571);
        internal_counters.push_back(3994);
        internal_counters.push_back(4572);
        internal_counters.push_back(3995);
        internal_counters.push_back(4573);
        internal_counters.push_back(3996);
        internal_counters.push_back(4574);

        c.DefineDerivedCounter("HiZQuadsCulledCount", "DepthAndStencil", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,sum8,-,(0),max", "73b0b39d-6df2-3e24-0b5c-7cb0ac8b6f39");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3993);
        internal_counters.push_back(4571);
        internal_counters.push_back(3994);
        internal_counters.push_back(4572);
        internal_counters.push_back(3995);
        internal_counters.push_back(4573);
        internal_counters.push_back(3996);
        internal_counters.push_back(4574);

        c.DefineDerivedCounter("HiZQuadsAcceptedCount", "DepthAndStencil", "Count of quads that did continue on in the pipeline after HiZ.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,sum8", "59049ad9-42b5-c7cb-3616-6a8f6a8e4894");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3993);
        internal_counters.push_back(4571);
        internal_counters.push_back(3994);
        internal_counters.push_back(4572);
        internal_counters.push_back(3995);
        internal_counters.push_back(4573);
        internal_counters.push_back(3996);
        internal_counters.push_back(4574);
        internal_counters.push_back(4017);
        internal_counters.push_back(4595);
        internal_counters.push_back(3917);
        internal_counters.push_back(4495);
        internal_counters.push_back(3918);
        internal_counters.push_back(4496);
        internal_counters.push_back(3919);
        internal_counters.push_back(4497);
        internal_counters.push_back(3920);
        internal_counters.push_back(4498);

        c.DefineDerivedCounter("PreZQuadsCulled", "DepthAndStencil", "Percentage of quads rejected based on the detailZ and earlyZ tests.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,9,+,-,(0),max,10,11,12,13,14,15,16,17,sum8,/,(100),*", "4e77547b-ec55-5663-f034-af59be66d77d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3993);
        internal_counters.push_back(4571);
        internal_counters.push_back(3994);
        internal_counters.push_back(4572);
        internal_counters.push_back(3995);
        internal_counters.push_back(4573);
        internal_counters.push_back(3996);
        internal_counters.push_back(4574);
        internal_counters.push_back(4017);
        internal_counters.push_back(4595);

        c.DefineDerivedCounter("PreZQuadsCulledCount", "DepthAndStencil", "Count of quads rejected based on the detailZ and earlyZ tests.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,9,sum2,-,(0),max", "1bf169e6-9304-834e-df5f-0c44d7890a08");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4017);
        internal_counters.push_back(4595);

        c.DefineDerivedCounter("PreZQuadsSurvivingCount", "DepthAndStencil", "Count of quads surviving detailZ and earlyZ tests.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,sum2", "50e25e51-3713-89cb-7f92-559cde5e5532");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4017);
        internal_counters.push_back(4595);
        internal_counters.push_back(3917);
        internal_counters.push_back(4495);
        internal_counters.push_back(3918);
        internal_counters.push_back(4496);
        internal_counters.push_back(3919);
        internal_counters.push_back(4497);
        internal_counters.push_back(3920);
        internal_counters.push_back(4498);

        c.DefineDerivedCounter("PostZQuads", "DepthAndStencil", "Percentage of quads for which the pixel shader will run and may be postZ tested.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,+,2,3,4,5,6,7,8,9,sum8,/,(100),*,(100),min", "58f0d34b-eeb8-e8db-abce-cb72584144be");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4017);
        internal_counters.push_back(4595);

        c.DefineDerivedCounter("PostZQuadCount", "DepthAndStencil", "Count of quads for which the pixel shader will run and may be postZ tested.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,+", "08404526-ce35-939b-34c8-a7a35a0ff4d6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2029);
        internal_counters.push_back(2420);
        internal_counters.push_back(2811);
        internal_counters.push_back(3202);

        c.DefineDerivedCounter("PreZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z before shading and passed.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "3bfe6c4d-7422-ca03-7ea5-e67ff1a00136");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2031);
        internal_counters.push_back(2422);
        internal_counters.push_back(2813);
        internal_counters.push_back(3204);

        c.DefineDerivedCounter("PreZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z before shading and failed stencil test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "df7f705e-5162-d3b5-da8b-63466cf9c4e5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2030);
        internal_counters.push_back(2421);
        internal_counters.push_back(2812);
        internal_counters.push_back(3203);

        c.DefineDerivedCounter("PreZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z before shading and failed Z test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "4484e950-f7a4-3800-bc74-78dd297f017e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2026);
        internal_counters.push_back(2417);
        internal_counters.push_back(2808);
        internal_counters.push_back(3199);

        c.DefineDerivedCounter("PostZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z after shading and passed.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "4995d5d6-2330-b986-508b-fae24856f44c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2028);
        internal_counters.push_back(2419);
        internal_counters.push_back(2810);
        internal_counters.push_back(3201);

        c.DefineDerivedCounter("PostZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z after shading and failed stencil test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "ae558af4-f4be-3dd4-7316-b2c4dcf0def8");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2027);
        internal_counters.push_back(2418);
        internal_counters.push_back(2809);
        internal_counters.push_back(3200);

        c.DefineDerivedCounter("PostZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z after shading and failed Z test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "b3684c94-814a-c695-c85d-a5b6ab798b35");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1898);
        internal_counters.push_back(2289);
        internal_counters.push_back(2680);
        internal_counters.push_back(3071);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("ZUnitStalled", "DepthAndStencil", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "5e86c3ad-1726-3157-1d01-7ed188bf854d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1898);
        internal_counters.push_back(2289);
        internal_counters.push_back(2680);
        internal_counters.push_back(3071);

        c.DefineDerivedCounter("ZUnitStalledCycles", "DepthAndStencil", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "4351fa7f-6737-2c3e-3ffb-b3addbdceedd");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1900);
        internal_counters.push_back(2291);
        internal_counters.push_back(2682);
        internal_counters.push_back(3073);
        internal_counters.push_back(1907);
        internal_counters.push_back(2298);
        internal_counters.push_back(2689);
        internal_counters.push_back(3080);

        c.DefineDerivedCounter("DBMemRead", "DepthAndStencil", "Number of bytes read from the depth buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,sum4,(256),*,4,5,6,7,sum4,(32),*,+", "dcdb4ee7-bd50-00f7-c028-9e5f4ce888c0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1912);
        internal_counters.push_back(2303);
        internal_counters.push_back(2694);
        internal_counters.push_back(3085);
        internal_counters.push_back(1915);
        internal_counters.push_back(2306);
        internal_counters.push_back(2697);
        internal_counters.push_back(3088);

        c.DefineDerivedCounter("DBMemWritten", "DepthAndStencil", "Number of bytes written to the depth buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,sum4,(32),*,4,5,6,7,sum4,(32),*,+", "de5717f8-8a49-ee44-4645-10de51b37dcf");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(128);
        internal_counters.push_back(581);
        internal_counters.push_back(1034);
        internal_counters.push_back(1487);

        c.DefineDerivedCounter("CBMemRead", "ColorBuffer", "Number of bytes read from the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,sum4,(32),*", "84b531d8-a1f8-7f49-7c27-7bc97801f1e6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(259);
        internal_counters.push_back(712);
        internal_counters.push_back(1165);
        internal_counters.push_back(1618);
        internal_counters.push_back(126);
        internal_counters.push_back(579);
        internal_counters.push_back(1032);
        internal_counters.push_back(1485);
        internal_counters.push_back(127);
        internal_counters.push_back(580);
        internal_counters.push_back(1033);
        internal_counters.push_back(1486);
        internal_counters.push_back(128);
        internal_counters.push_back(581);
        internal_counters.push_back(1034);
        internal_counters.push_back(1487);

        c.DefineDerivedCounter("CBColorAndMaskRead", "ColorBuffer", "Total number of bytes read from the color and mask buffers.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "da41660e-eb6f-32ec-8a64-b32ca17bd7eb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(118);
        internal_counters.push_back(571);
        internal_counters.push_back(1024);
        internal_counters.push_back(1477);

        c.DefineDerivedCounter("CBMemWritten", "ColorBuffer", "Number of bytes written to the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,sum4,(32),*", "550f8ff8-60b6-a6bf-87d0-25ac9e87de70");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(257);
        internal_counters.push_back(710);
        internal_counters.push_back(1163);
        internal_counters.push_back(1616);
        internal_counters.push_back(116);
        internal_counters.push_back(569);
        internal_counters.push_back(1022);
        internal_counters.push_back(1475);
        internal_counters.push_back(117);
        internal_counters.push_back(570);
        internal_counters.push_back(1023);
        internal_counters.push_back(1476);
        internal_counters.push_back(118);
        internal_counters.push_back(571);
        internal_counters.push_back(1024);
        internal_counters.push_back(1477);

        c.DefineDerivedCounter("CBColorAndMaskWritten", "ColorBuffer", "Total number of bytes written to the color and mask buffers.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "29a04b69-8f5f-b770-a0f2-3453e2c99e49");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(162);
        internal_counters.push_back(615);
        internal_counters.push_back(1068);
        internal_counters.push_back(1521);
        internal_counters.push_back(7);
        internal_counters.push_back(460);
        internal_counters.push_back(913);
        internal_counters.push_back(1366);

        c.DefineDerivedCounter("CBSlowPixelPct", "ColorBuffer", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*,(100),min", "5775943f-0313-7e52-9638-b24a449197bc");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(162);
        internal_counters.push_back(615);
        internal_counters.push_back(1068);
        internal_counters.push_back(1521);

        c.DefineDerivedCounter("CBSlowPixelCount", "ColorBuffer", "Number of pixels written to the color buffer using a half-rate or quarter-rate format.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "47eacbb0-28c8-22b4-5c69-c00d5813bb1c");
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

        c.DefineDerivedCounter("L0CacheHit", "MemoryCache", "The percentage of read requests that hit the data in the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "286c786e-9a42-3371-9dea-dd54e6e612e9");
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

        c.DefineDerivedCounter("L0CacheRequestCount", "MemoryCache", "The number of read requests made to the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "74983cae-ee57-2e1b-d990-5128fef84e1f");
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

        c.DefineDerivedCounter("L0CacheHitCount", "MemoryCache", "The number of read requests which result in a cache hit from the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-", "c0de7338-069b-c5ba-ead3-c65e030cd2ac");
    }
    {
        vector<GpaUInt32> internal_counters;
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

        c.DefineDerivedCounter("L0CacheMissCount", "MemoryCache", "The number of read requests which result in a cache miss from the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "a2f08766-ea1b-6eae-6eaf-faa04125d3e6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(17719);
        internal_counters.push_back(17723);

        c.DefineDerivedCounter("L1CacheHit", "MemoryCache", "The percentage of read or write requests that hit the data in the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),1,0,/,-,(100),*,0,ifnotzero", "5a34915a-24b8-8baf-2bf8-5878e7894ae3");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(17719);

        c.DefineDerivedCounter("L1CacheRequestCount", "MemoryCache", "The number of read or write requests made to the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "29c76c67-4611-205d-0b88-d08668df03c5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(17719);
        internal_counters.push_back(17723);

        c.DefineDerivedCounter("L1CacheHitCount", "MemoryCache", "The number of read or write requests which result in a cache hit from the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,-", "1ae150c3-f2d0-82c6-a51b-a77fd8d5fc33");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(17723);

        c.DefineDerivedCounter("L1CacheMissCount", "MemoryCache", "The number of read or write requests which result in a cache miss from the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "71bfec6d-257b-849d-e212-cdf5c1b1de65");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(18155);
        internal_counters.push_back(18409);
        internal_counters.push_back(18663);
        internal_counters.push_back(18917);
        internal_counters.push_back(19171);
        internal_counters.push_back(19425);
        internal_counters.push_back(19679);
        internal_counters.push_back(19933);
        internal_counters.push_back(20187);
        internal_counters.push_back(20441);
        internal_counters.push_back(20695);
        internal_counters.push_back(20949);
        internal_counters.push_back(21203);
        internal_counters.push_back(21457);
        internal_counters.push_back(21711);
        internal_counters.push_back(21965);
        internal_counters.push_back(18195);
        internal_counters.push_back(18449);
        internal_counters.push_back(18703);
        internal_counters.push_back(18957);
        internal_counters.push_back(19211);
        internal_counters.push_back(19465);
        internal_counters.push_back(19719);
        internal_counters.push_back(19973);
        internal_counters.push_back(20227);
        internal_counters.push_back(20481);
        internal_counters.push_back(20735);
        internal_counters.push_back(20989);
        internal_counters.push_back(21243);
        internal_counters.push_back(21497);
        internal_counters.push_back(21751);
        internal_counters.push_back(22005);

        c.DefineDerivedCounter("L2CacheHit", "MemoryCache", "The percentage of read or write requests that hit the data in the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "47694e4d-6ce6-f387-080d-b1f3d00b73ac");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(18195);
        internal_counters.push_back(18449);
        internal_counters.push_back(18703);
        internal_counters.push_back(18957);
        internal_counters.push_back(19211);
        internal_counters.push_back(19465);
        internal_counters.push_back(19719);
        internal_counters.push_back(19973);
        internal_counters.push_back(20227);
        internal_counters.push_back(20481);
        internal_counters.push_back(20735);
        internal_counters.push_back(20989);
        internal_counters.push_back(21243);
        internal_counters.push_back(21497);
        internal_counters.push_back(21751);
        internal_counters.push_back(22005);
        internal_counters.push_back(18155);
        internal_counters.push_back(18409);
        internal_counters.push_back(18663);
        internal_counters.push_back(18917);
        internal_counters.push_back(19171);
        internal_counters.push_back(19425);
        internal_counters.push_back(19679);
        internal_counters.push_back(19933);
        internal_counters.push_back(20187);
        internal_counters.push_back(20441);
        internal_counters.push_back(20695);
        internal_counters.push_back(20949);
        internal_counters.push_back(21203);
        internal_counters.push_back(21457);
        internal_counters.push_back(21711);
        internal_counters.push_back(21965);

        c.DefineDerivedCounter("L2CacheMiss", "MemoryCache", "The percentage of read or write requests that miss the data in the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size. Value range: 0% (optimal) to 100% (all miss).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*", "8aee5458-a58e-11b6-5131-7f19ed070117");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(18155);
        internal_counters.push_back(18409);
        internal_counters.push_back(18663);
        internal_counters.push_back(18917);
        internal_counters.push_back(19171);
        internal_counters.push_back(19425);
        internal_counters.push_back(19679);
        internal_counters.push_back(19933);
        internal_counters.push_back(20187);
        internal_counters.push_back(20441);
        internal_counters.push_back(20695);
        internal_counters.push_back(20949);
        internal_counters.push_back(21203);
        internal_counters.push_back(21457);
        internal_counters.push_back(21711);
        internal_counters.push_back(21965);

        c.DefineDerivedCounter("L2CacheRequestCount", "MemoryCache", "The number of read or write requests made to the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "21e9219c-e725-0d96-06b1-b21698b736b2");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(18155);
        internal_counters.push_back(18409);
        internal_counters.push_back(18663);
        internal_counters.push_back(18917);
        internal_counters.push_back(19171);
        internal_counters.push_back(19425);
        internal_counters.push_back(19679);
        internal_counters.push_back(19933);
        internal_counters.push_back(20187);
        internal_counters.push_back(20441);
        internal_counters.push_back(20695);
        internal_counters.push_back(20949);
        internal_counters.push_back(21203);
        internal_counters.push_back(21457);
        internal_counters.push_back(21711);
        internal_counters.push_back(21965);
        internal_counters.push_back(18195);
        internal_counters.push_back(18449);
        internal_counters.push_back(18703);
        internal_counters.push_back(18957);
        internal_counters.push_back(19211);
        internal_counters.push_back(19465);
        internal_counters.push_back(19719);
        internal_counters.push_back(19973);
        internal_counters.push_back(20227);
        internal_counters.push_back(20481);
        internal_counters.push_back(20735);
        internal_counters.push_back(20989);
        internal_counters.push_back(21243);
        internal_counters.push_back(21497);
        internal_counters.push_back(21751);
        internal_counters.push_back(22005);

        c.DefineDerivedCounter("L2CacheHitCount", "MemoryCache", "The number of read or write requests which result in a cache hit from the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-", "29ddcb92-d3dd-951b-1b23-efe52e4eeee4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(18195);
        internal_counters.push_back(18449);
        internal_counters.push_back(18703);
        internal_counters.push_back(18957);
        internal_counters.push_back(19211);
        internal_counters.push_back(19465);
        internal_counters.push_back(19719);
        internal_counters.push_back(19973);
        internal_counters.push_back(20227);
        internal_counters.push_back(20481);
        internal_counters.push_back(20735);
        internal_counters.push_back(20989);
        internal_counters.push_back(21243);
        internal_counters.push_back(21497);
        internal_counters.push_back(21751);
        internal_counters.push_back(22005);

        c.DefineDerivedCounter("L2CacheMissCount", "MemoryCache", "The number of read or write requests which result in a cache miss from the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "376eec7b-ab25-9012-06b5-63291a17fd47");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16458);
        internal_counters.push_back(16519);
        internal_counters.push_back(16580);
        internal_counters.push_back(16641);
        internal_counters.push_back(16702);
        internal_counters.push_back(16763);
        internal_counters.push_back(16824);
        internal_counters.push_back(16885);
        internal_counters.push_back(16946);
        internal_counters.push_back(17007);
        internal_counters.push_back(17068);
        internal_counters.push_back(17129);
        internal_counters.push_back(17190);
        internal_counters.push_back(17251);
        internal_counters.push_back(17312);
        internal_counters.push_back(17373);

        c.DefineDerivedCounter("L0TagConflictReadStalledCycles", "MemoryCache", "The number of cycles read operations from the L0 cache are stalled due to tag conflicts.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "e2412737-e2bf-c791-5f2f-64abd4ba47cf");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16459);
        internal_counters.push_back(16520);
        internal_counters.push_back(16581);
        internal_counters.push_back(16642);
        internal_counters.push_back(16703);
        internal_counters.push_back(16764);
        internal_counters.push_back(16825);
        internal_counters.push_back(16886);
        internal_counters.push_back(16947);
        internal_counters.push_back(17008);
        internal_counters.push_back(17069);
        internal_counters.push_back(17130);
        internal_counters.push_back(17191);
        internal_counters.push_back(17252);
        internal_counters.push_back(17313);
        internal_counters.push_back(17374);

        c.DefineDerivedCounter("L0TagConflictWriteStalledCycles", "MemoryCache", "The number of cycles write operations to the L0 cache are stalled due to tag conflicts.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "0c2571f3-f084-f351-99ba-0d9e23b47e8e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(16460);
        internal_counters.push_back(16521);
        internal_counters.push_back(16582);
        internal_counters.push_back(16643);
        internal_counters.push_back(16704);
        internal_counters.push_back(16765);
        internal_counters.push_back(16826);
        internal_counters.push_back(16887);
        internal_counters.push_back(16948);
        internal_counters.push_back(17009);
        internal_counters.push_back(17070);
        internal_counters.push_back(17131);
        internal_counters.push_back(17192);
        internal_counters.push_back(17253);
        internal_counters.push_back(17314);
        internal_counters.push_back(17375);

        c.DefineDerivedCounter("L0TagConflictAtomicStalledCycles", "MemoryCache", "The number of cycles atomic operations on the L0 cache are stalled due to tag conflicts.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "f13f8563-4151-1533-f42f-0f9c08a20210");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(18251);
        internal_counters.push_back(18505);
        internal_counters.push_back(18759);
        internal_counters.push_back(19013);
        internal_counters.push_back(19267);
        internal_counters.push_back(19521);
        internal_counters.push_back(19775);
        internal_counters.push_back(20029);
        internal_counters.push_back(20283);
        internal_counters.push_back(20537);
        internal_counters.push_back(20791);
        internal_counters.push_back(21045);
        internal_counters.push_back(21299);
        internal_counters.push_back(21553);
        internal_counters.push_back(21807);
        internal_counters.push_back(22061);
        internal_counters.push_back(18252);
        internal_counters.push_back(18506);
        internal_counters.push_back(18760);
        internal_counters.push_back(19014);
        internal_counters.push_back(19268);
        internal_counters.push_back(19522);
        internal_counters.push_back(19776);
        internal_counters.push_back(20030);
        internal_counters.push_back(20284);
        internal_counters.push_back(20538);
        internal_counters.push_back(20792);
        internal_counters.push_back(21046);
        internal_counters.push_back(21300);
        internal_counters.push_back(21554);
        internal_counters.push_back(21808);
        internal_counters.push_back(22062);
        internal_counters.push_back(18253);
        internal_counters.push_back(18507);
        internal_counters.push_back(18761);
        internal_counters.push_back(19015);
        internal_counters.push_back(19269);
        internal_counters.push_back(19523);
        internal_counters.push_back(19777);
        internal_counters.push_back(20031);
        internal_counters.push_back(20285);
        internal_counters.push_back(20539);
        internal_counters.push_back(20793);
        internal_counters.push_back(21047);
        internal_counters.push_back(21301);
        internal_counters.push_back(21555);
        internal_counters.push_back(21809);
        internal_counters.push_back(22063);
        internal_counters.push_back(18254);
        internal_counters.push_back(18508);
        internal_counters.push_back(18762);
        internal_counters.push_back(19016);
        internal_counters.push_back(19270);
        internal_counters.push_back(19524);
        internal_counters.push_back(19778);
        internal_counters.push_back(20032);
        internal_counters.push_back(20286);
        internal_counters.push_back(20540);
        internal_counters.push_back(20794);
        internal_counters.push_back(21048);
        internal_counters.push_back(21302);
        internal_counters.push_back(21556);
        internal_counters.push_back(21810);
        internal_counters.push_back(22064);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total bytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,(96),*,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,(128),*,sum4", "664bb3ef-6eca-86b1-1e2d-30cb897b5fa9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(18235);
        internal_counters.push_back(18489);
        internal_counters.push_back(18743);
        internal_counters.push_back(18997);
        internal_counters.push_back(19251);
        internal_counters.push_back(19505);
        internal_counters.push_back(19759);
        internal_counters.push_back(20013);
        internal_counters.push_back(20267);
        internal_counters.push_back(20521);
        internal_counters.push_back(20775);
        internal_counters.push_back(21029);
        internal_counters.push_back(21283);
        internal_counters.push_back(21537);
        internal_counters.push_back(21791);
        internal_counters.push_back(22045);
        internal_counters.push_back(18237);
        internal_counters.push_back(18491);
        internal_counters.push_back(18745);
        internal_counters.push_back(18999);
        internal_counters.push_back(19253);
        internal_counters.push_back(19507);
        internal_counters.push_back(19761);
        internal_counters.push_back(20015);
        internal_counters.push_back(20269);
        internal_counters.push_back(20523);
        internal_counters.push_back(20777);
        internal_counters.push_back(21031);
        internal_counters.push_back(21285);
        internal_counters.push_back(21539);
        internal_counters.push_back(21793);
        internal_counters.push_back(22047);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total bytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+", "f96f2c16-b1b4-4ec4-229c-fc82e6f80a82");
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

        c.DefineDerivedCounter("MemUnitBusyCycles", "GlobalMemory", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalledCycles). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ARRAYS,/", "168f077c-4797-b2f5-717f-105c725266c8");
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

        c.DefineDerivedCounter("MemUnitStalledCycles", "GlobalMemory", "Number of GPU cycles the memory unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,max10", "2745659a-0e40-bace-3b9b-86a54f8e4623");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(18240);
        internal_counters.push_back(18494);
        internal_counters.push_back(18748);
        internal_counters.push_back(19002);
        internal_counters.push_back(19256);
        internal_counters.push_back(19510);
        internal_counters.push_back(19764);
        internal_counters.push_back(20018);
        internal_counters.push_back(20272);
        internal_counters.push_back(20526);
        internal_counters.push_back(20780);
        internal_counters.push_back(21034);
        internal_counters.push_back(21288);
        internal_counters.push_back(21542);
        internal_counters.push_back(21796);
        internal_counters.push_back(22050);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(18240);
        internal_counters.push_back(18494);
        internal_counters.push_back(18748);
        internal_counters.push_back(19002);
        internal_counters.push_back(19256);
        internal_counters.push_back(19510);
        internal_counters.push_back(19764);
        internal_counters.push_back(20018);
        internal_counters.push_back(20272);
        internal_counters.push_back(20526);
        internal_counters.push_back(20780);
        internal_counters.push_back(21034);
        internal_counters.push_back(21288);
        internal_counters.push_back(21542);
        internal_counters.push_back(21796);
        internal_counters.push_back(22050);

        c.DefineDerivedCounter("WriteUnitStalledCycles", "GlobalMemory", "Number of GPU cycles the Write unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "ede3305e-abd4-d6bf-6b00-ffc57a29fce3");
    }
}

