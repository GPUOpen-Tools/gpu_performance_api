//==============================================================================
// Copyright (c) 2010-2021 Advanced Micro Devices, Inc. All rights reserved.
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
        internal_counters.push_back(5222);
        internal_counters.push_back(5234);
        internal_counters.push_back(4915);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("VSBusy", "Timing", "The percentage of time the ShaderUnit has vertex shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,1,ifnotzero,2,2,ifnotzero,3,/,(100),*,(100),min", "94caad5e-867c-6c09-cf3a-d05b51df8f3b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5222);
        internal_counters.push_back(5234);
        internal_counters.push_back(4915);

        c.DefineDerivedCounter("VSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has vertex shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,1,ifnotzero,2,2,ifnotzero", "a2086d4e-274b-48a8-3e08-a4ab76ac15dd");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(25620);
        internal_counters.push_back(5222);
        internal_counters.push_back(5234);
        internal_counters.push_back(4915);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("VSTime", "Timing", "Time vertex shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "1,2,2,ifnotzero,3,3,ifnotzero,4,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "d6ce819e-69af-a241-d07a-5dd8d146e436");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4948);
        internal_counters.push_back(4955);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("HSBusy", "Timing", "The percentage of time the ShaderUnit has hull shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "16f30a0b-4cbf-eccd-b13f-ab68dd254d32");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4948);
        internal_counters.push_back(4955);

        c.DefineDerivedCounter("HSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has hull shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,ifnotzero", "753e76ef-8ef8-3f13-b511-4bd9f3589fdb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(25620);
        internal_counters.push_back(4948);
        internal_counters.push_back(4955);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("HSTime", "Timing", "Time hull shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "8386a863-dd34-1526-f703-0f0c7b241bc4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4915);
        internal_counters.push_back(5222);
        internal_counters.push_back(5228);
        internal_counters.push_back(5240);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("DSBusy", "Timing", "The percentage of time the ShaderUnit has domain shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,2,ifnotzero,3,ifnotzero,4,/,(100),*,(100),min", "0c626e8a-9b82-b6d4-d9a3-578509316301");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4915);
        internal_counters.push_back(5222);
        internal_counters.push_back(5228);
        internal_counters.push_back(5240);

        c.DefineDerivedCounter("DSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has domain shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,ifnotzero,3,ifnotzero", "2f3f7561-0549-2232-536d-129ffc5f7703");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(25620);
        internal_counters.push_back(4915);
        internal_counters.push_back(5222);
        internal_counters.push_back(5228);
        internal_counters.push_back(5240);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("DSTime", "Timing", "Time domain shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,3,ifnotzero,4,ifnotzero,5,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "bfe28947-c727-8a9f-aa59-c218e58bfba5");
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
        internal_counters.push_back(25568);
        internal_counters.push_back(25587);

        c.DefineDerivedCounter("VSVerticesIn", "VertexShader", "The number of vertices processed by the VS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,1,ifnotzero,2,2,ifnotzero", "810a04c8-2ff4-081d-766d-bfa2bd4ad916");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5822);
        internal_counters.push_back(5762);
        internal_counters.push_back(7870);
        internal_counters.push_back(7810);
        internal_counters.push_back(6846);
        internal_counters.push_back(6786);

        c.DefineDerivedCounter("VSVALUInstCount", "VertexShader", "Average number of vector ALU instructions executed in the VS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero,2,3,/,3,ifnotzero,4,5,/,5,ifnotzero", "8ec604e4-63f5-e6b5-4558-c38f0b26d4b1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5818);
        internal_counters.push_back(5762);
        internal_counters.push_back(7866);
        internal_counters.push_back(7810);
        internal_counters.push_back(6842);
        internal_counters.push_back(6786);

        c.DefineDerivedCounter("VSSALUInstCount", "VertexShader", "Average number of scalar ALU instructions executed in the VS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero,2,3,/,3,ifnotzero,4,5,/,5,ifnotzero", "e3da0383-7322-7f65-8cf2-3ce641578e54");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5875);
        internal_counters.push_back(7923);
        internal_counters.push_back(6899);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("VSVALUBusy", "VertexShader", "The percentage of GPUTime vector ALU instructions are being processed by the VS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,1,ifnotzero,2,2,ifnotzero,NUM_SIMDS,/,3,/,(100),*", "8b3572f7-fda0-eddf-6c93-2ab145b8754b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5875);
        internal_counters.push_back(7923);
        internal_counters.push_back(6899);

        c.DefineDerivedCounter("VSVALUBusyCycles", "VertexShader", "Number of GPU cycles where vector ALU instructions are being processed by the VS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,1,ifnotzero,2,2,ifnotzero", "0af1686e-6d77-2f6e-2862-7bb8e869a776");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5818);
        internal_counters.push_back(7866);
        internal_counters.push_back(6842);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("VSSALUBusy", "VertexShader", "The percentage of GPUTime scalar ALU instructions are being processed by the VS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,1,ifnotzero,2,2,ifnotzero,NUM_CUS,/,3,/,(100),*", "3bc8730c-e3bc-e2f0-7d24-36974064c25a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5818);
        internal_counters.push_back(7866);
        internal_counters.push_back(6842);

        c.DefineDerivedCounter("VSSALUBusyCycles", "VertexShader", "Number of GPU cycles where scalar ALU instructions are being processed by the VS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,1,ifnotzero,2,2,ifnotzero,NUM_CUS,/", "357ac7cd-2e1c-dcb0-77f6-37527237f35b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(25562);

        c.DefineDerivedCounter("HSPatches", "HullShader", "The number of patches processed by the HS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "d1bbd27d-d591-4509-df52-d329fb73a98f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8382);
        internal_counters.push_back(8322);

        c.DefineDerivedCounter("HSVALUInstCount", "HullShader", "Average number of vector ALU instructions executed in the HS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "786673bf-d58f-9895-3a37-9d6efb5e5804");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8378);
        internal_counters.push_back(8322);

        c.DefineDerivedCounter("HSSALUInstCount", "HullShader", "Average number of scalar ALU instructions executed in the HS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "1af675c4-cb0b-c4c5-c131-2796750f683e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8435);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("HSVALUBusy", "HullShader", "The percentage of GPUTime vector ALU instructions are being processed by the HS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_SIMDS,/,1,/,(100),*", "7880d192-8015-0311-d43e-fb0b7a4df179");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8435);

        c.DefineDerivedCounter("HSVALUBusyCycles", "HullShader", "Number of GPU cycles vector where ALU instructions are being processed by the HS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_SIMDS,/", "3afb94e4-e937-5730-0cc9-41d3113ba012");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8378);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("HSSALUBusy", "HullShader", "The percentage of GPUTime scalar ALU instructions are being processed by the HS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "34748a4b-9148-0b06-b7b9-5700d6631bde");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8378);

        c.DefineDerivedCounter("HSSALUBusyCycles", "HullShader", "Number of GPU cycles where scalar ALU instructions are being processed by the HS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_CUS,/", "9bceabf7-3f01-2fd9-7b1d-8fe46c729efc");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(25549);
        internal_counters.push_back(25568);
        internal_counters.push_back(25587);

        c.DefineDerivedCounter("DSVerticesIn", "DomainShader", "The number of vertices processed by the DS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,1,ifnotzero,2,2,ifnotzero", "b88d9d05-2418-e639-4e3d-3a5815855f8d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6846);
        internal_counters.push_back(6786);
        internal_counters.push_back(5822);
        internal_counters.push_back(5762);
        internal_counters.push_back(5766);
        internal_counters.push_back(7814);

        c.DefineDerivedCounter("DSVALUInstCount", "DomainShader", "Average number of vector ALU instructions executed in the DS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,2,3,/,4,ifnotzero,5,ifnotzero", "03a3e949-82f9-be4d-7228-5eb5ad80915a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(6842);
        internal_counters.push_back(6786);
        internal_counters.push_back(5818);
        internal_counters.push_back(5762);
        internal_counters.push_back(5766);
        internal_counters.push_back(7814);

        c.DefineDerivedCounter("DSSALUInstCount", "DomainShader", "Average number of scalar ALU instructions executed in the DS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,2,3,/,4,ifnotzero,5,ifnotzero", "73daa728-483e-95d0-5b40-504719aadc1c");
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

        c.DefineDerivedCounter("PSExportStalls", "PixelShader", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,max4,4,/,NUM_SHADER_ENGINES,/,(100),*", "9b4f466c-ff97-22bb-557d-84d3c4c51895");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9356);
        internal_counters.push_back(9361);
        internal_counters.push_back(9366);
        internal_counters.push_back(9371);

        c.DefineDerivedCounter("PSExportStallsCycles", "PixelShader", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "47c72aad-64e6-0864-d533-d8e0bc27c156");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7358);
        internal_counters.push_back(7298);

        c.DefineDerivedCounter("PSVALUInstCount", "PixelShader", "Average number of vector ALU instructions executed in the PS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "eb74389e-435c-4137-ecf1-39eb5bc1cbfe");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7354);
        internal_counters.push_back(7298);

        c.DefineDerivedCounter("PSSALUInstCount", "PixelShader", "Average number of scalar ALU instructions executed in the PS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "e6a06580-8a82-96d6-976c-acc121fc5516");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7411);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("PSVALUBusy", "PixelShader", "The percentage of GPUTime vector ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_SIMDS,/,1,/,(100),*", "6ce6fef7-8e33-10b4-f351-af755e177e85");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7411);

        c.DefineDerivedCounter("PSVALUBusyCycles", "PixelShader", "Number of GPU cycles where vector ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_SIMDS,/", "1e276f86-cd2a-72e7-fc9d-004f666f2981");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7354);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("PSSALUBusy", "PixelShader", "The percentage of GPUTime scalar ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "2ff9f34f-e94b-af4d-18c2-5fbbf6d1727a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7354);

        c.DefineDerivedCounter("PSSALUBusyCycles", "PixelShader", "Number of GPU cycles where scalar ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_CUS,/", "29808906-f128-b078-fc79-820a4b3b3b8d");
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
        internal_counters.push_back(8894);
        internal_counters.push_back(8834);

        c.DefineDerivedCounter("CSVALUInsts", "ComputeShader", "The average number of vector ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "376cb1cc-5a40-9d1d-404c-f1736c0c5084");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8912);
        internal_counters.push_back(8947);
        internal_counters.push_back(5251);

        c.DefineDerivedCounter("CSVALUUtilization", "ComputeShader", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,(64),(32),2,ifnotzero,*,/,(100),*,1,ifnotzero,(100),min", "ae943d2a-76e1-bb68-e1e2-0e06c9031611");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8890);
        internal_counters.push_back(8834);

        c.DefineDerivedCounter("CSSALUInsts", "ComputeShader", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "eb211144-8136-ff86-e8bf-4d0493a904cb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8899);
        internal_counters.push_back(8834);

        c.DefineDerivedCounter("CSVFetchInsts", "ComputeShader", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "3e2829c0-6215-783b-c271-6d57ff2c520e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8891);
        internal_counters.push_back(8834);

        c.DefineDerivedCounter("CSSFetchInsts", "ComputeShader", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "da09171c-6a0a-584f-fddc-dc5062d63a3e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8900);
        internal_counters.push_back(8834);

        c.DefineDerivedCounter("CSVWriteInsts", "ComputeShader", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "43438c22-e910-b377-b767-b32902e0df0d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8947);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("CSVALUBusy", "ComputeShader", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_SIMDS,/,1,/,(100),*", "f1e64815-f6a8-c277-d4f9-d054b443e205");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8947);

        c.DefineDerivedCounter("CSVALUBusyCycles", "ComputeShader", "Number of GPU cycles where vector ALU instructions are processed.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_SIMDS,/", "2d0d5852-2658-eb73-68d2-f23f7118c9c3");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8890);
        internal_counters.push_back(1836);

        c.DefineDerivedCounter("CSSALUBusy", "ComputeShader", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "3fc35f4e-9882-94e3-6f5f-4e81cd97082a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8890);

        c.DefineDerivedCounter("CSSALUBusyCycles", "ComputeShader", "Number of GPU cycles where scalar ALU instructions are processed.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_CUS,/", "de58f8fc-8ed4-a799-648d-62ded7b1c4c4");
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

        c.DefineDerivedCounter("DepthStencilTestBusyCount", "Timing", "Number of GPU cycles spent performing depth and stencil tests.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "e02860fa-c7bd-90ea-2149-69b4e98a636c");
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

        c.DefineDerivedCounter("HiZTilesAccepted", "DepthAndStencil", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*", "56176f45-d7ff-813d-4f05-3b2f046067e7");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1867);
        internal_counters.push_back(2258);
        internal_counters.push_back(2649);
        internal_counters.push_back(3040);

        c.DefineDerivedCounter("HiZTilesAcceptedCount", "DepthAndStencil", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "95d4e3f6-b2f0-f26e-8423-aacdfaf79ea3");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1856);
        internal_counters.push_back(2247);
        internal_counters.push_back(2638);
        internal_counters.push_back(3029);

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
        internal_counters.push_back(3917);
        internal_counters.push_back(4495);
        internal_counters.push_back(3918);
        internal_counters.push_back(4496);
        internal_counters.push_back(3919);
        internal_counters.push_back(4497);
        internal_counters.push_back(3920);
        internal_counters.push_back(4498);
        internal_counters.push_back(4017);
        internal_counters.push_back(4595);
        internal_counters.push_back(3993);
        internal_counters.push_back(4571);
        internal_counters.push_back(3994);
        internal_counters.push_back(4572);
        internal_counters.push_back(3995);
        internal_counters.push_back(4573);
        internal_counters.push_back(3996);
        internal_counters.push_back(4574);

        c.DefineDerivedCounter("PreZQuadsCulled", "DepthAndStencil", "Percentage of quads rejected based on the detailZ and earlyZ tests.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "10,11,12,13,14,15,16,17,sum8,8,9,+,-,(0),max,0,1,2,3,4,5,6,7,sum8,/,(100),*", "4e77547b-ec55-5663-f034-af59be66d77d");
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
        internal_counters.push_back(4017);
        internal_counters.push_back(4595);
        internal_counters.push_back(3993);
        internal_counters.push_back(4571);
        internal_counters.push_back(3994);
        internal_counters.push_back(4572);
        internal_counters.push_back(3995);
        internal_counters.push_back(4573);
        internal_counters.push_back(3996);
        internal_counters.push_back(4574);

        c.DefineDerivedCounter("PreZQuadsCulledCount", "DepthAndStencil", "Count of quads rejected based on the detailZ and earlyZ tests.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,9,+,-,10,11,12,13,14,15,16,17,sum8,-,(0),max", "1bf169e6-9304-834e-df5f-0c44d7890a08");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4017);
        internal_counters.push_back(4595);
        internal_counters.push_back(3993);
        internal_counters.push_back(4571);
        internal_counters.push_back(3994);
        internal_counters.push_back(4572);
        internal_counters.push_back(3995);
        internal_counters.push_back(4573);
        internal_counters.push_back(3996);
        internal_counters.push_back(4574);

        c.DefineDerivedCounter("PreZQuadsSurvivingCount", "DepthAndStencil", "Count of quads surviving detailZ and earlyZ tests.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "2,3,4,5,6,7,8,9,sum8,0,1,+,-,(0),max", "50e25e51-3713-89cb-7f92-559cde5e5532");
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

        c.DefineDerivedCounter("MemUnitBusyCycles", "GlobalMemory", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalledCycles). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "168f077c-4797-b2f5-717f-105c725266c8");
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

