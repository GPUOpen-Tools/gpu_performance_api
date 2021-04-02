//==============================================================================
// Copyright (c) 2010-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for GL GFX8.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_gl_gfx8.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersGlGfx8(GpaDerivedCounters& c)
{
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15125);

        c.DefineDerivedCounter("GPUTime", "Timing", "Time this API command took to execute on the GPU in nanoseconds from the time the previous command reached the bottom of the pipeline (BOP) to the time this command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "0,TS_FREQ,/,(1000000000),*", "cbd338f2-de6c-7b14-92ad-ba724ca2e501");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2633);
        internal_counters.push_back(2631);

        c.DefineDerivedCounter("GPUBusy", "Timing", "The percentage of time GPU was busy.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,/,(100),*,(100),min", "bef38bf3-1167-0844-81f0-67d2d28ddbc5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("GPUBusyCycles", "Timing", "Number of GPU cycles that the GPU was busy.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0", "1e84970d-7014-2b8d-d61e-388b5f782691");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14904);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("TessellatorBusy", "Timing", "The percentage of time the tessellation engine is busy.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_PRIM_PIPES,/,1,/,(100),*", "36af6c72-dcfb-8102-4fd4-ce8ddc573365");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14904);

        c.DefineDerivedCounter("TessellatorBusyCycles", "Timing", "Number of GPU cycles that the tessellation engine is busy.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_PRIM_PIPES,/", "60289dcb-7b33-46e7-26d1-8a2121605543");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3231);
        internal_counters.push_back(3256);
        internal_counters.push_back(3278);
        internal_counters.push_back(3300);
        internal_counters.push_back(3240);
        internal_counters.push_back(3262);
        internal_counters.push_back(3284);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("VSBusy", "Timing", "The percentage of time the ShaderUnit has vertex shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,4,ifnotzero,1,5,ifnotzero,2,6,ifnotzero,7,/,(100),*,(100),min", "94caad5e-867c-6c09-cf3a-d05b51df8f3b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3231);
        internal_counters.push_back(3256);
        internal_counters.push_back(3278);
        internal_counters.push_back(3300);
        internal_counters.push_back(3240);
        internal_counters.push_back(3262);
        internal_counters.push_back(3284);

        c.DefineDerivedCounter("VSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has vertex shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,4,ifnotzero,1,5,ifnotzero,2,6,ifnotzero", "a2086d4e-274b-48a8-3e08-a4ab76ac15dd");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15125);
        internal_counters.push_back(3231);
        internal_counters.push_back(3256);
        internal_counters.push_back(3278);
        internal_counters.push_back(3300);
        internal_counters.push_back(3240);
        internal_counters.push_back(3262);
        internal_counters.push_back(3284);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("VSTime", "Timing", "Time vertex shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,5,ifnotzero,2,6,ifnotzero,3,7,ifnotzero,8,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "d6ce819e-69af-a241-d07a-5dd8d146e436");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3268);
        internal_counters.push_back(3274);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("HSBusy", "Timing", "The percentage of time the ShaderUnit has hull shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "16f30a0b-4cbf-eccd-b13f-ab68dd254d32");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3268);
        internal_counters.push_back(3274);

        c.DefineDerivedCounter("HSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has hull shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,ifnotzero", "753e76ef-8ef8-3f13-b511-4bd9f3589fdb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15125);
        internal_counters.push_back(3268);
        internal_counters.push_back(3274);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("HSTime", "Timing", "Time hull shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "8386a863-dd34-1526-f703-0f0c7b241bc4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3231);
        internal_counters.push_back(3256);
        internal_counters.push_back(3300);
        internal_counters.push_back(3262);
        internal_counters.push_back(3284);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("DSBusy", "Timing", "The percentage of time the ShaderUnit has domain shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,3,ifnotzero,4,ifnotzero,5,/,(100),*,(100),min", "0c626e8a-9b82-b6d4-d9a3-578509316301");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3231);
        internal_counters.push_back(3256);
        internal_counters.push_back(3300);
        internal_counters.push_back(3262);
        internal_counters.push_back(3284);

        c.DefineDerivedCounter("DSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has domain shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,3,ifnotzero,4,ifnotzero", "2f3f7561-0549-2232-536d-129ffc5f7703");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15125);
        internal_counters.push_back(3231);
        internal_counters.push_back(3256);
        internal_counters.push_back(3300);
        internal_counters.push_back(3262);
        internal_counters.push_back(3284);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("DSTime", "Timing", "Time domain shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,4,ifnotzero,5,ifnotzero,6,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "bfe28947-c727-8a9f-aa59-c218e58bfba5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3247);
        internal_counters.push_back(3250);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("GSBusy", "Timing", "The percentage of time the ShaderUnit has geometry shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "876f36d8-d046-833f-7832-673cbffd0a45");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3247);
        internal_counters.push_back(3250);

        c.DefineDerivedCounter("GSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has geometry shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,ifnotzero", "48203b6b-8983-c067-d63e-05da8be5111b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15125);
        internal_counters.push_back(3247);
        internal_counters.push_back(3250);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("GSTime", "Timing", "Time geometry shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "c73e715f-59af-76e8-9e22-097b94c066c4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3300);
        internal_counters.push_back(3305);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("PSBusy", "Timing", "The percentage of time the ShaderUnit has pixel shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "7e772beb-d82c-bd9a-aed0-fe504d416ce5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3300);
        internal_counters.push_back(3305);

        c.DefineDerivedCounter("PSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has pixel shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,ifnotzero", "b58bea04-ce8e-2984-80f4-8aba7d4c817b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15125);
        internal_counters.push_back(3300);
        internal_counters.push_back(3305);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("PSTime", "Timing", "Time pixel shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "edca7694-7416-e8a6-0c5a-63a5ad5f3d74");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3288);
        internal_counters.push_back(3292);
        internal_counters.push_back(3294);
        internal_counters.push_back(3298);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("CSBusy", "Timing", "The percentage of time the ShaderUnit has compute shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,max,4,/,(100),*,(100),min", "493fdd90-8d2b-a055-5e4e-2d29c3396b8c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3288);
        internal_counters.push_back(3292);
        internal_counters.push_back(3294);
        internal_counters.push_back(3298);

        c.DefineDerivedCounter("CSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has compute shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,max", "39bcf1b8-f6b2-4c37-f9af-0a2bb59512f9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15125);
        internal_counters.push_back(3288);
        internal_counters.push_back(3292);
        internal_counters.push_back(3294);
        internal_counters.push_back(3298);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("CSTime", "Timing", "Time compute shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,ifnotzero,(0),3,4,ifnotzero,max,5,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "dbc24916-ecb2-7eef-8d63-7afadaaab6bc");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14800);
        internal_counters.push_back(14781);
        internal_counters.push_back(14876);

        c.DefineDerivedCounter("VSVerticesIn", "VertexShader", "The number of vertices processed by the VS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,1,ifnotzero,2,2,ifnotzero", "810a04c8-2ff4-081d-766d-bfa2bd4ad916");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4350);
        internal_counters.push_back(4328);
        internal_counters.push_back(3752);
        internal_counters.push_back(3730);
        internal_counters.push_back(3740);
        internal_counters.push_back(4948);
        internal_counters.push_back(4926);
        internal_counters.push_back(4936);

        c.DefineDerivedCounter("VSVALUInstCount", "VertexShader", "Average number of vector ALU instructions executed in the VS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/,2,3,/,4,ifnotzero,5,6,/,7,ifnotzero", "8ec604e4-63f5-e6b5-4558-c38f0b26d4b1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4354);
        internal_counters.push_back(4328);
        internal_counters.push_back(3756);
        internal_counters.push_back(3730);
        internal_counters.push_back(3740);
        internal_counters.push_back(4952);
        internal_counters.push_back(4926);
        internal_counters.push_back(4936);

        c.DefineDerivedCounter("VSSALUInstCount", "VertexShader", "Average number of scalar ALU instructions executed in the VS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/,2,3,/,4,ifnotzero,5,6,/,7,ifnotzero", "e3da0383-7322-7f65-8cf2-3ce641578e54");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4405);
        internal_counters.push_back(3807);
        internal_counters.push_back(3740);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("VSVALUBusy", "VertexShader", "The percentage of GPUTime vector ALU instructions are being processed by the VS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,ifnotzero,(4),*,NUM_SIMDS,/,3,/,(100),*", "8b3572f7-fda0-eddf-6c93-2ab145b8754b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4405);
        internal_counters.push_back(3807);
        internal_counters.push_back(3740);

        c.DefineDerivedCounter("VSVALUBusyCycles", "VertexShader", "Number of GPU cycles where vector ALU instructions are being processed by the VS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,ifnotzero,(4),*,NUM_SIMDS,/", "0af1686e-6d77-2f6e-2862-7bb8e869a776");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4410);
        internal_counters.push_back(3812);
        internal_counters.push_back(3740);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("VSSALUBusy", "VertexShader", "The percentage of GPUTime scalar ALU instructions are being processed by the VS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,ifnotzero,NUM_CUS,/,3,/,(100),*", "3bc8730c-e3bc-e2f0-7d24-36974064c25a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4410);
        internal_counters.push_back(3812);
        internal_counters.push_back(3740);

        c.DefineDerivedCounter("VSSALUBusyCycles", "VertexShader", "Number of GPU cycles where scalar ALU instructions are being processed by the VS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,ifnotzero,NUM_CUS,/", "357ac7cd-2e1c-dcb0-77f6-37527237f35b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14885);

        c.DefineDerivedCounter("HSPatches", "HullShader", "The number of patches processed by the HS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "d1bbd27d-d591-4509-df52-d329fb73a98f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5247);
        internal_counters.push_back(5225);

        c.DefineDerivedCounter("HSVALUInstCount", "HullShader", "Average number of vector ALU instructions executed in the HS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "786673bf-d58f-9895-3a37-9d6efb5e5804");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5251);
        internal_counters.push_back(5225);

        c.DefineDerivedCounter("HSSALUInstCount", "HullShader", "Average number of scalar ALU instructions executed in the HS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "1af675c4-cb0b-c4c5-c131-2796750f683e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5302);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("HSVALUBusy", "HullShader", "The percentage of GPUTime vector ALU instructions are being processed by the HS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "7880d192-8015-0311-d43e-fb0b7a4df179");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5302);

        c.DefineDerivedCounter("HSVALUBusyCycles", "HullShader", "Number of GPU cycles vector where ALU instructions are being processed by the HS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,(4),*,NUM_SIMDS,/", "3afb94e4-e937-5730-0cc9-41d3113ba012");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5307);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("HSSALUBusy", "HullShader", "The percentage of GPUTime scalar ALU instructions are being processed by the HS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "34748a4b-9148-0b06-b7b9-5700d6631bde");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5307);

        c.DefineDerivedCounter("HSSALUBusyCycles", "HullShader", "Number of GPU cycles where scalar ALU instructions are being processed by the HS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_CUS,/", "9bceabf7-3f01-2fd9-7b1d-8fe46c729efc");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14800);
        internal_counters.push_back(14781);
        internal_counters.push_back(14876);

        c.DefineDerivedCounter("DSVerticesIn", "DomainShader", "The number of vertices processed by the DS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,1,ifnotzero,2,ifnotzero", "b88d9d05-2418-e639-4e3d-3a5815855f8d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4350);
        internal_counters.push_back(4328);
        internal_counters.push_back(3752);
        internal_counters.push_back(3730);
        internal_counters.push_back(3740);
        internal_counters.push_back(4936);

        c.DefineDerivedCounter("DSVALUInstCount", "DomainShader", "Average number of vector ALU instructions executed in the DS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,2,3,/,4,ifnotzero,5,ifnotzero", "03a3e949-82f9-be4d-7228-5eb5ad80915a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4354);
        internal_counters.push_back(4328);
        internal_counters.push_back(3756);
        internal_counters.push_back(3730);
        internal_counters.push_back(3740);
        internal_counters.push_back(4936);

        c.DefineDerivedCounter("DSSALUInstCount", "DomainShader", "Average number of scalar ALU instructions executed in the DS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,2,3,/,4,ifnotzero,5,ifnotzero", "73daa728-483e-95d0-5b40-504719aadc1c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4405);
        internal_counters.push_back(3807);
        internal_counters.push_back(2633);
        internal_counters.push_back(3740);
        internal_counters.push_back(4936);

        c.DefineDerivedCounter("DSVALUBusy", "DomainShader", "The percentage of GPUTime vector ALU instructions are being processed by the DS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,3,ifnotzero,4,ifnotzero,(4),*,NUM_SIMDS,/,2,/,(100),*", "ddc0dd0c-0c73-b831-a410-cfea8b9713d9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4405);
        internal_counters.push_back(3807);
        internal_counters.push_back(3740);
        internal_counters.push_back(4936);

        c.DefineDerivedCounter("DSVALUBusyCycles", "DomainShader", "Number of GPU cycles where vector ALU instructions are being processed by the DS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,ifnotzero,3,ifnotzero,(4),*,NUM_SIMDS,/", "1e280912-81ee-a684-823b-94c468d8ebda");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4410);
        internal_counters.push_back(3812);
        internal_counters.push_back(2633);
        internal_counters.push_back(3740);
        internal_counters.push_back(4936);

        c.DefineDerivedCounter("DSSALUBusy", "DomainShader", "The percentage of GPUTime scalar ALU instructions are being processed by the DS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,3,ifnotzero,4,ifnotzero,NUM_CUS,/,2,/,(100),*", "b639f64c-24af-348f-6439-43c701b4fc07");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4410);
        internal_counters.push_back(3812);
        internal_counters.push_back(3740);
        internal_counters.push_back(4936);

        c.DefineDerivedCounter("DSSALUBusyCycles", "DomainShader", "Number of GPU cycles where scalar ALU instructions are being processed by the DS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,ifnotzero,3,ifnotzero,NUM_CUS,/", "b5bf8a0c-e682-1aa6-23d7-c6c6784ffa5c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14789);

        c.DefineDerivedCounter("GSPrimsIn", "GeometryShader", "The number of primitives passed into the GS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "20c29866-509a-aaab-2697-6b2c38f79953");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14800);
        internal_counters.push_back(14781);

        c.DefineDerivedCounter("GSVerticesOut", "GeometryShader", "The number of vertices output by the GS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,ifnotzero", "775b9736-319a-bd8a-48c9-68db9c91d978");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4051);
        internal_counters.push_back(4029);

        c.DefineDerivedCounter("GSVALUInstCount", "GeometryShader", "Average number of vector ALU instructions executed in the GS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "21b12bfa-b8cd-2e71-a2d5-f9e9f1d65d61");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4055);
        internal_counters.push_back(4029);

        c.DefineDerivedCounter("GSSALUInstCount", "GeometryShader", "Average number of scalar ALU instructions executed in the GS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "a8562594-d335-ca43-61bf-03b72d2b98a5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4106);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("GSVALUBusy", "GeometryShader", "The percentage of GPUTime vector ALU instructions are being processed by the GS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "228a4818-1e56-cebb-0720-3b2cdc057a6f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4106);

        c.DefineDerivedCounter("GSVALUBusyCycles", "GeometryShader", "Number of GPU cycles where vector ALU instructions are being processed by the GS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,(4),*,NUM_SIMDS,/", "be217edd-226f-bd97-9a48-46e2809b1933");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4111);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("GSSALUBusy", "GeometryShader", "The percentage of GPUTime scalar ALU instructions are being processed by the GS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "f28ce300-800e-9822-39e4-f48528bdb935");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4111);

        c.DefineDerivedCounter("GSSALUBusyCycles", "GeometryShader", "Number of GPU cycles where scalar ALU instructions are being processed by the GS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_CUS,/", "b3eace7c-3bc4-0107-887f-923851dc8ea7");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2785);
        internal_counters.push_back(2789);
        internal_counters.push_back(2741);
        internal_counters.push_back(2753);
        internal_counters.push_back(2742);
        internal_counters.push_back(2754);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("PrimitiveAssemblyBusy", "Timing", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max,6,/,(100),*,(100),min", "54ac5640-c4d7-95e2-20e0-6a9fdfc07333");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2785);
        internal_counters.push_back(2789);
        internal_counters.push_back(2741);
        internal_counters.push_back(2753);
        internal_counters.push_back(2742);
        internal_counters.push_back(2754);

        c.DefineDerivedCounter("PrimitiveAssemblyBusyCycles", "Timing", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max", "99777f2d-9626-c78a-a97c-c4505eba1e5f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2688);

        c.DefineDerivedCounter("PrimitivesIn", "PrimitiveAssembly", "The number of primitives received by the hardware. This includes primitives generated by tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "a515b80d-75c3-c7d2-0d2f-d7766b4759a6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2694);
        internal_counters.push_back(2734);
        internal_counters.push_back(2735);
        internal_counters.push_back(2736);
        internal_counters.push_back(2737);

        c.DefineDerivedCounter("CulledPrims", "PrimitiveAssembly", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,+,2,+,3,+,4,+", "589bdf55-9192-280a-41c3-584bc94f2562");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2701);

        c.DefineDerivedCounter("ClippedPrims", "PrimitiveAssembly", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "5ef6f9d5-155e-5baa-163f-8359d9ea9bbf");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2789);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("PAStalledOnRasterizer", "PrimitiveAssembly", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_PRIM_PIPES,/,1,/,(100),*", "6f9f416b-53c1-0457-f88c-7b6ba8973974");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2789);

        c.DefineDerivedCounter("PAStalledOnRasterizerCycles", "PrimitiveAssembly", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_PRIM_PIPES,/", "7a8c492a-c566-9328-6805-760dbff5c0f2");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5831);
        internal_counters.push_back(5836);
        internal_counters.push_back(5841);
        internal_counters.push_back(5846);

        c.DefineDerivedCounter("PSPixelsOut", "PixelShader", "Pixels exported from shader to color buffers. Does not include killed or alpha tested pixels; if there are multiple render targets, each render target receives one export, so this will be 2 for 1 pixel written to two RTs.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "24cba16c-baa6-6ecd-95ad-92ecb1338da1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5833);
        internal_counters.push_back(5838);
        internal_counters.push_back(5843);
        internal_counters.push_back(5848);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("PSExportStalls", "PixelShader", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "9b4f466c-ff97-22bb-557d-84d3c4c51895");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5833);
        internal_counters.push_back(5838);
        internal_counters.push_back(5843);
        internal_counters.push_back(5848);

        c.DefineDerivedCounter("PSExportStallsCycles", "PixelShader", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "47c72aad-64e6-0864-d533-d8e0bc27c156");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4649);
        internal_counters.push_back(4627);

        c.DefineDerivedCounter("PSVALUInstCount", "PixelShader", "Average number of vector ALU instructions executed in the PS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "eb74389e-435c-4137-ecf1-39eb5bc1cbfe");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4653);
        internal_counters.push_back(4627);

        c.DefineDerivedCounter("PSSALUInstCount", "PixelShader", "Average number of scalar ALU instructions executed in the PS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,/", "e6a06580-8a82-96d6-976c-acc121fc5516");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4704);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("PSVALUBusy", "PixelShader", "The percentage of GPUTime vector ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "6ce6fef7-8e33-10b4-f351-af755e177e85");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4704);

        c.DefineDerivedCounter("PSVALUBusyCycles", "PixelShader", "Number of GPU cycles where vector ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,(4),*,NUM_SIMDS,/", "1e276f86-cd2a-72e7-fc9d-004f666f2981");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4709);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("PSSALUBusy", "PixelShader", "The percentage of GPUTime scalar ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "2ff9f34f-e94b-af4d-18c2-5fbbf6d1727a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(4709);

        c.DefineDerivedCounter("PSSALUBusyCycles", "PixelShader", "Number of GPU cycles where scalar ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_CUS,/", "29808906-f128-b078-fc79-820a4b3b3b8d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3289);
        internal_counters.push_back(3295);

        c.DefineDerivedCounter("CSThreadGroups", "ComputeShader", "Total number of thread groups.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,+", "8ce3fc80-56b2-97f9-8e70-2e8c747cea68");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5524);

        c.DefineDerivedCounter("CSWavefronts", "ComputeShader", "The total number of wavefronts used for the CS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "42379c6e-369b-c237-8b25-cdb9cdc65c4d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5534);

        c.DefineDerivedCounter("CSThreads", "ComputeShader", "The number of CS threads processed by the hardware.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "7a648013-6eac-2665-ac36-13c6f4ac9c26");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5546);
        internal_counters.push_back(5524);

        c.DefineDerivedCounter("CSVALUInsts", "ComputeShader", "The average number of vector ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "376cb1cc-5a40-9d1d-404c-f1736c0c5084");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5609);
        internal_counters.push_back(5601);

        c.DefineDerivedCounter("CSVALUUtilization", "ComputeShader", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,(64),*,/,(100),*,1,ifnotzero,(100),min", "4476879e-cdc0-d602-b24e-9b4a8d38438f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5550);
        internal_counters.push_back(5524);

        c.DefineDerivedCounter("CSSALUInsts", "ComputeShader", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "eb211144-8136-ff86-e8bf-4d0493a904cb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5548);
        internal_counters.push_back(5954);
        internal_counters.push_back(6073);
        internal_counters.push_back(6192);
        internal_counters.push_back(6311);
        internal_counters.push_back(6430);
        internal_counters.push_back(6549);
        internal_counters.push_back(6668);
        internal_counters.push_back(6787);
        internal_counters.push_back(6906);
        internal_counters.push_back(7025);
        internal_counters.push_back(7144);
        internal_counters.push_back(7263);
        internal_counters.push_back(7382);
        internal_counters.push_back(7501);
        internal_counters.push_back(7620);
        internal_counters.push_back(7739);
        internal_counters.push_back(5524);

        c.DefineDerivedCounter("CSVFetchInsts", "ComputeShader", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/,17,ifnotzero", "3e2829c0-6215-783b-c271-6d57ff2c520e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5551);
        internal_counters.push_back(5524);

        c.DefineDerivedCounter("CSSFetchInsts", "ComputeShader", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "da09171c-6a0a-584f-fddc-dc5062d63a3e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5547);
        internal_counters.push_back(5955);
        internal_counters.push_back(6074);
        internal_counters.push_back(6193);
        internal_counters.push_back(6312);
        internal_counters.push_back(6431);
        internal_counters.push_back(6550);
        internal_counters.push_back(6669);
        internal_counters.push_back(6788);
        internal_counters.push_back(6907);
        internal_counters.push_back(7026);
        internal_counters.push_back(7145);
        internal_counters.push_back(7264);
        internal_counters.push_back(7383);
        internal_counters.push_back(7502);
        internal_counters.push_back(7621);
        internal_counters.push_back(7740);
        internal_counters.push_back(5524);

        c.DefineDerivedCounter("CSVWriteInsts", "ComputeShader", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/,17,ifnotzero", "43438c22-e910-b377-b767-b32902e0df0d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5552);
        internal_counters.push_back(5553);
        internal_counters.push_back(5524);

        c.DefineDerivedCounter("CSFlatVMemInsts", "ComputeShader", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,-,2,/,2,ifnotzero", "2570b477-13e3-f5b6-e6ff-7159373bc74d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5601);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("CSVALUBusy", "ComputeShader", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "f1e64815-f6a8-c277-d4f9-d054b443e205");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5601);

        c.DefineDerivedCounter("CSVALUBusyCycles", "ComputeShader", "Number of GPU cycles where vector ALU instructions are processed.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,(4),*,NUM_SIMDS,/", "2d0d5852-2658-eb73-68d2-f23f7118c9c3");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5606);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("CSSALUBusy", "ComputeShader", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,NUM_CUS,/,1,/,(100),*", "3fc35f4e-9882-94e3-6f5f-4e81cd97082a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5606);

        c.DefineDerivedCounter("CSSALUBusyCycles", "ComputeShader", "Number of GPU cycles where scalar ALU instructions are processed.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_CUS,/", "de58f8fc-8ed4-a799-648d-62ded7b1c4c4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5868);
        internal_counters.push_back(5987);
        internal_counters.push_back(6106);
        internal_counters.push_back(6225);
        internal_counters.push_back(6344);
        internal_counters.push_back(6463);
        internal_counters.push_back(6582);
        internal_counters.push_back(6701);
        internal_counters.push_back(6820);
        internal_counters.push_back(6939);
        internal_counters.push_back(7058);
        internal_counters.push_back(7177);
        internal_counters.push_back(7296);
        internal_counters.push_back(7415);
        internal_counters.push_back(7534);
        internal_counters.push_back(7653);
        internal_counters.push_back(2633);
        internal_counters.push_back(3289);
        internal_counters.push_back(3295);

        c.DefineDerivedCounter("CSMemUnitBusy", "ComputeShader", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*,17,18,+,ifnotzero", "42ab96e1-0a24-96c8-c4ff-098fa267d78e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5868);
        internal_counters.push_back(5987);
        internal_counters.push_back(6106);
        internal_counters.push_back(6225);
        internal_counters.push_back(6344);
        internal_counters.push_back(6463);
        internal_counters.push_back(6582);
        internal_counters.push_back(6701);
        internal_counters.push_back(6820);
        internal_counters.push_back(6939);
        internal_counters.push_back(7058);
        internal_counters.push_back(7177);
        internal_counters.push_back(7296);
        internal_counters.push_back(7415);
        internal_counters.push_back(7534);
        internal_counters.push_back(7653);
        internal_counters.push_back(3289);
        internal_counters.push_back(3295);

        c.DefineDerivedCounter("CSMemUnitBusyCycles", "ComputeShader", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ENGINES,/,16,17,+,ifnotzero", "39d5687f-c727-7c0c-af82-bb711d3897ed");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(11782);
        internal_counters.push_back(11962);
        internal_counters.push_back(12142);
        internal_counters.push_back(12322);
        internal_counters.push_back(12502);
        internal_counters.push_back(12682);
        internal_counters.push_back(12862);
        internal_counters.push_back(13042);
        internal_counters.push_back(13222);
        internal_counters.push_back(13402);
        internal_counters.push_back(13582);
        internal_counters.push_back(13762);
        internal_counters.push_back(13942);
        internal_counters.push_back(14122);
        internal_counters.push_back(14302);
        internal_counters.push_back(14482);
        internal_counters.push_back(2633);
        internal_counters.push_back(3289);
        internal_counters.push_back(3295);

        c.DefineDerivedCounter("CSMemUnitStalled", "ComputeShader", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*,17,18,+,ifnotzero", "f18e8679-1511-d533-d9ee-4365197f7d0c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(11782);
        internal_counters.push_back(11962);
        internal_counters.push_back(12142);
        internal_counters.push_back(12322);
        internal_counters.push_back(12502);
        internal_counters.push_back(12682);
        internal_counters.push_back(12862);
        internal_counters.push_back(13042);
        internal_counters.push_back(13222);
        internal_counters.push_back(13402);
        internal_counters.push_back(13582);
        internal_counters.push_back(13762);
        internal_counters.push_back(13942);
        internal_counters.push_back(14122);
        internal_counters.push_back(14302);
        internal_counters.push_back(14482);
        internal_counters.push_back(3289);
        internal_counters.push_back(3295);

        c.DefineDerivedCounter("CSMemUnitStalledCycles", "ComputeShader", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ENGINES,/,16,17,+,ifnotzero", "51991c84-ed2b-bf31-c4ab-8f8e9eb8f29f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7855);
        internal_counters.push_back(8047);
        internal_counters.push_back(8239);
        internal_counters.push_back(8431);
        internal_counters.push_back(8623);
        internal_counters.push_back(8815);
        internal_counters.push_back(9007);
        internal_counters.push_back(9199);
        internal_counters.push_back(9391);
        internal_counters.push_back(9583);
        internal_counters.push_back(9775);
        internal_counters.push_back(9967);
        internal_counters.push_back(10159);
        internal_counters.push_back(10351);
        internal_counters.push_back(10543);
        internal_counters.push_back(10735);
        internal_counters.push_back(2633);
        internal_counters.push_back(3289);
        internal_counters.push_back(3295);

        c.DefineDerivedCounter("CSWriteUnitStalled", "ComputeShader", "The percentage of GPUTime the write unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,18,+,ifnotzero", "55118f7a-8f92-726f-78c6-407f689a2eb4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7855);
        internal_counters.push_back(8047);
        internal_counters.push_back(8239);
        internal_counters.push_back(8431);
        internal_counters.push_back(8623);
        internal_counters.push_back(8815);
        internal_counters.push_back(9007);
        internal_counters.push_back(9199);
        internal_counters.push_back(9391);
        internal_counters.push_back(9583);
        internal_counters.push_back(9775);
        internal_counters.push_back(9967);
        internal_counters.push_back(10159);
        internal_counters.push_back(10351);
        internal_counters.push_back(10543);
        internal_counters.push_back(10735);
        internal_counters.push_back(3289);
        internal_counters.push_back(3295);

        c.DefineDerivedCounter("CSWriteUnitStalledCycles", "ComputeShader", "Number of GPU cycles the write unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,17,+,ifnotzero", "be164c60-5e48-acac-9622-29616d09aa9a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5555);
        internal_counters.push_back(5524);

        c.DefineDerivedCounter("CSGDSInsts", "ComputeShader", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "2a867f3e-4a37-ad16-55d1-f03d74707819");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5554);
        internal_counters.push_back(5552);
        internal_counters.push_back(5524);

        c.DefineDerivedCounter("CSLDSInsts", "ComputeShader", "The average number of LDS read/write instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,-,2,/,2,ifnotzero", "61b0b351-7e06-ef8e-a8e0-7a9e3200a836");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5553);
        internal_counters.push_back(5524);

        c.DefineDerivedCounter("CSFlatLDSInsts", "ComputeShader", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,/,1,ifnotzero", "99672cda-de2b-014c-482e-cf73b90068d5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3488);
        internal_counters.push_back(3431);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("CSALUStalledByLDS", "ComputeShader", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,/,2,/,NUM_SHADER_ENGINES,/,(100),*,1,ifnotzero", "6dc4f1c2-bad0-c9ff-156e-883b319a752a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3488);

        c.DefineDerivedCounter("CSALUStalledByLDSCycles", "ComputeShader", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_SHADER_ENGINES,/", "8f3d5f25-2159-0374-fafe-e26a7799b6c8");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5617);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("CSLDSBankConflict", "ComputeShader", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,/,NUM_SIMDS,/,(100),*", "1065ee10-2e41-ea41-1eb3-b61b491752f4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5617);

        c.DefineDerivedCounter("CSLDSBankConflictCycles", "ComputeShader", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad).", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,NUM_SIMDS,/", "1fd1adf3-c51e-94fd-083e-c482a0a0809e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5868);
        internal_counters.push_back(5987);
        internal_counters.push_back(6106);
        internal_counters.push_back(6225);
        internal_counters.push_back(6344);
        internal_counters.push_back(6463);
        internal_counters.push_back(6582);
        internal_counters.push_back(6701);
        internal_counters.push_back(6820);
        internal_counters.push_back(6939);
        internal_counters.push_back(7058);
        internal_counters.push_back(7177);
        internal_counters.push_back(7296);
        internal_counters.push_back(7415);
        internal_counters.push_back(7534);
        internal_counters.push_back(7653);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("TexUnitBusy", "Timing", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "36afb8d9-42fc-aafe-66c5-449542153b2c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5868);
        internal_counters.push_back(5987);
        internal_counters.push_back(6106);
        internal_counters.push_back(6225);
        internal_counters.push_back(6344);
        internal_counters.push_back(6463);
        internal_counters.push_back(6582);
        internal_counters.push_back(6701);
        internal_counters.push_back(6820);
        internal_counters.push_back(6939);
        internal_counters.push_back(7058);
        internal_counters.push_back(7177);
        internal_counters.push_back(7296);
        internal_counters.push_back(7415);
        internal_counters.push_back(7534);
        internal_counters.push_back(7653);

        c.DefineDerivedCounter("TexUnitBusyCycles", "Timing", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ENGINES,/", "c68761f2-248c-4f39-6528-c308b1c0807c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5922);
        internal_counters.push_back(6041);
        internal_counters.push_back(6160);
        internal_counters.push_back(6279);
        internal_counters.push_back(6398);
        internal_counters.push_back(6517);
        internal_counters.push_back(6636);
        internal_counters.push_back(6755);
        internal_counters.push_back(6874);
        internal_counters.push_back(6993);
        internal_counters.push_back(7112);
        internal_counters.push_back(7231);
        internal_counters.push_back(7350);
        internal_counters.push_back(7469);
        internal_counters.push_back(7588);
        internal_counters.push_back(7707);
        internal_counters.push_back(5921);
        internal_counters.push_back(6040);
        internal_counters.push_back(6159);
        internal_counters.push_back(6278);
        internal_counters.push_back(6397);
        internal_counters.push_back(6516);
        internal_counters.push_back(6635);
        internal_counters.push_back(6754);
        internal_counters.push_back(6873);
        internal_counters.push_back(6992);
        internal_counters.push_back(7111);
        internal_counters.push_back(7230);
        internal_counters.push_back(7349);
        internal_counters.push_back(7468);
        internal_counters.push_back(7587);
        internal_counters.push_back(7706);

        c.DefineDerivedCounter("TexTriFilteringPct", "TextureUnit", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,+,/,(100),*", "1affc3c8-b917-5c81-622b-7004527208ae");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5922);
        internal_counters.push_back(6041);
        internal_counters.push_back(6160);
        internal_counters.push_back(6279);
        internal_counters.push_back(6398);
        internal_counters.push_back(6517);
        internal_counters.push_back(6636);
        internal_counters.push_back(6755);
        internal_counters.push_back(6874);
        internal_counters.push_back(6993);
        internal_counters.push_back(7112);
        internal_counters.push_back(7231);
        internal_counters.push_back(7350);
        internal_counters.push_back(7469);
        internal_counters.push_back(7588);
        internal_counters.push_back(7707);

        c.DefineDerivedCounter("TexTriFilteringCount", "TextureUnit", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "5785b3a1-a513-18db-4b1c-bdeef75bb2b6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5921);
        internal_counters.push_back(6040);
        internal_counters.push_back(6159);
        internal_counters.push_back(6278);
        internal_counters.push_back(6397);
        internal_counters.push_back(6516);
        internal_counters.push_back(6635);
        internal_counters.push_back(6754);
        internal_counters.push_back(6873);
        internal_counters.push_back(6992);
        internal_counters.push_back(7111);
        internal_counters.push_back(7230);
        internal_counters.push_back(7349);
        internal_counters.push_back(7468);
        internal_counters.push_back(7587);
        internal_counters.push_back(7706);

        c.DefineDerivedCounter("NoTexTriFilteringCount", "TextureUnit", "Count of pixels that did not receive trilinear filtering.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "179da29a-81af-c06e-ce8c-a0a731ea030d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5924);
        internal_counters.push_back(6043);
        internal_counters.push_back(6162);
        internal_counters.push_back(6281);
        internal_counters.push_back(6400);
        internal_counters.push_back(6519);
        internal_counters.push_back(6638);
        internal_counters.push_back(6757);
        internal_counters.push_back(6876);
        internal_counters.push_back(6995);
        internal_counters.push_back(7114);
        internal_counters.push_back(7233);
        internal_counters.push_back(7352);
        internal_counters.push_back(7471);
        internal_counters.push_back(7590);
        internal_counters.push_back(7709);
        internal_counters.push_back(5923);
        internal_counters.push_back(6042);
        internal_counters.push_back(6161);
        internal_counters.push_back(6280);
        internal_counters.push_back(6399);
        internal_counters.push_back(6518);
        internal_counters.push_back(6637);
        internal_counters.push_back(6756);
        internal_counters.push_back(6875);
        internal_counters.push_back(6994);
        internal_counters.push_back(7113);
        internal_counters.push_back(7232);
        internal_counters.push_back(7351);
        internal_counters.push_back(7470);
        internal_counters.push_back(7589);
        internal_counters.push_back(7708);

        c.DefineDerivedCounter("TexVolFilteringPct", "TextureUnit", "Percentage of pixels that received volume filtering.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,+,/,(100),*", "b5ff6bed-3178-aee4-42dd-c74391c02a2d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5924);
        internal_counters.push_back(6043);
        internal_counters.push_back(6162);
        internal_counters.push_back(6281);
        internal_counters.push_back(6400);
        internal_counters.push_back(6519);
        internal_counters.push_back(6638);
        internal_counters.push_back(6757);
        internal_counters.push_back(6876);
        internal_counters.push_back(6995);
        internal_counters.push_back(7114);
        internal_counters.push_back(7233);
        internal_counters.push_back(7352);
        internal_counters.push_back(7471);
        internal_counters.push_back(7590);
        internal_counters.push_back(7709);

        c.DefineDerivedCounter("TexVolFilteringCount", "TextureUnit", "Count of pixels that received volume filtering.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "4bddc587-d589-8128-e18c-762eab2c871f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5923);
        internal_counters.push_back(6042);
        internal_counters.push_back(6161);
        internal_counters.push_back(6280);
        internal_counters.push_back(6399);
        internal_counters.push_back(6518);
        internal_counters.push_back(6637);
        internal_counters.push_back(6756);
        internal_counters.push_back(6875);
        internal_counters.push_back(6994);
        internal_counters.push_back(7113);
        internal_counters.push_back(7232);
        internal_counters.push_back(7351);
        internal_counters.push_back(7470);
        internal_counters.push_back(7589);
        internal_counters.push_back(7708);

        c.DefineDerivedCounter("NoTexVolFilteringCount", "TextureUnit", "Count of pixels that did not receive volume filtering.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "9fe1a854-17c6-9d26-b2b9-80610cd5827d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5942);
        internal_counters.push_back(6061);
        internal_counters.push_back(6180);
        internal_counters.push_back(6299);
        internal_counters.push_back(6418);
        internal_counters.push_back(6537);
        internal_counters.push_back(6656);
        internal_counters.push_back(6775);
        internal_counters.push_back(6894);
        internal_counters.push_back(7013);
        internal_counters.push_back(7132);
        internal_counters.push_back(7251);
        internal_counters.push_back(7370);
        internal_counters.push_back(7489);
        internal_counters.push_back(7608);
        internal_counters.push_back(7727);
        internal_counters.push_back(5943);
        internal_counters.push_back(6062);
        internal_counters.push_back(6181);
        internal_counters.push_back(6300);
        internal_counters.push_back(6419);
        internal_counters.push_back(6538);
        internal_counters.push_back(6657);
        internal_counters.push_back(6776);
        internal_counters.push_back(6895);
        internal_counters.push_back(7014);
        internal_counters.push_back(7133);
        internal_counters.push_back(7252);
        internal_counters.push_back(7371);
        internal_counters.push_back(7490);
        internal_counters.push_back(7609);
        internal_counters.push_back(7728);
        internal_counters.push_back(5944);
        internal_counters.push_back(6063);
        internal_counters.push_back(6182);
        internal_counters.push_back(6301);
        internal_counters.push_back(6420);
        internal_counters.push_back(6539);
        internal_counters.push_back(6658);
        internal_counters.push_back(6777);
        internal_counters.push_back(6896);
        internal_counters.push_back(7015);
        internal_counters.push_back(7134);
        internal_counters.push_back(7253);
        internal_counters.push_back(7372);
        internal_counters.push_back(7491);
        internal_counters.push_back(7610);
        internal_counters.push_back(7729);
        internal_counters.push_back(5945);
        internal_counters.push_back(6064);
        internal_counters.push_back(6183);
        internal_counters.push_back(6302);
        internal_counters.push_back(6421);
        internal_counters.push_back(6540);
        internal_counters.push_back(6659);
        internal_counters.push_back(6778);
        internal_counters.push_back(6897);
        internal_counters.push_back(7016);
        internal_counters.push_back(7135);
        internal_counters.push_back(7254);
        internal_counters.push_back(7373);
        internal_counters.push_back(7492);
        internal_counters.push_back(7611);
        internal_counters.push_back(7730);
        internal_counters.push_back(5946);
        internal_counters.push_back(6065);
        internal_counters.push_back(6184);
        internal_counters.push_back(6303);
        internal_counters.push_back(6422);
        internal_counters.push_back(6541);
        internal_counters.push_back(6660);
        internal_counters.push_back(6779);
        internal_counters.push_back(6898);
        internal_counters.push_back(7017);
        internal_counters.push_back(7136);
        internal_counters.push_back(7255);
        internal_counters.push_back(7374);
        internal_counters.push_back(7493);
        internal_counters.push_back(7612);
        internal_counters.push_back(7731);
        internal_counters.push_back(5947);
        internal_counters.push_back(6066);
        internal_counters.push_back(6185);
        internal_counters.push_back(6304);
        internal_counters.push_back(6423);
        internal_counters.push_back(6542);
        internal_counters.push_back(6661);
        internal_counters.push_back(6780);
        internal_counters.push_back(6899);
        internal_counters.push_back(7018);
        internal_counters.push_back(7137);
        internal_counters.push_back(7256);
        internal_counters.push_back(7375);
        internal_counters.push_back(7494);
        internal_counters.push_back(7613);
        internal_counters.push_back(7732);
        internal_counters.push_back(5948);
        internal_counters.push_back(6067);
        internal_counters.push_back(6186);
        internal_counters.push_back(6305);
        internal_counters.push_back(6424);
        internal_counters.push_back(6543);
        internal_counters.push_back(6662);
        internal_counters.push_back(6781);
        internal_counters.push_back(6900);
        internal_counters.push_back(7019);
        internal_counters.push_back(7138);
        internal_counters.push_back(7257);
        internal_counters.push_back(7376);
        internal_counters.push_back(7495);
        internal_counters.push_back(7614);
        internal_counters.push_back(7733);
        internal_counters.push_back(5949);
        internal_counters.push_back(6068);
        internal_counters.push_back(6187);
        internal_counters.push_back(6306);
        internal_counters.push_back(6425);
        internal_counters.push_back(6544);
        internal_counters.push_back(6663);
        internal_counters.push_back(6782);
        internal_counters.push_back(6901);
        internal_counters.push_back(7020);
        internal_counters.push_back(7139);
        internal_counters.push_back(7258);
        internal_counters.push_back(7377);
        internal_counters.push_back(7496);
        internal_counters.push_back(7615);
        internal_counters.push_back(7734);
        internal_counters.push_back(5950);
        internal_counters.push_back(6069);
        internal_counters.push_back(6188);
        internal_counters.push_back(6307);
        internal_counters.push_back(6426);
        internal_counters.push_back(6545);
        internal_counters.push_back(6664);
        internal_counters.push_back(6783);
        internal_counters.push_back(6902);
        internal_counters.push_back(7021);
        internal_counters.push_back(7140);
        internal_counters.push_back(7259);
        internal_counters.push_back(7378);
        internal_counters.push_back(7497);
        internal_counters.push_back(7616);
        internal_counters.push_back(7735);

        c.DefineDerivedCounter("TexAveAnisotropy", "TextureUnit", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(2),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,*,+,(4),32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,*,+,(6),48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,*,+,(8),64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,*,+,(10),80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,*,+,(12),96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,*,+,(14),112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,*,+,(16),128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,*,+,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,+,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,+,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,+,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,+,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,+,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,+,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,+,/", "7ca2a2b9-a4eb-ce23-d163-59147e672396");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1747);
        internal_counters.push_back(2004);
        internal_counters.push_back(2261);
        internal_counters.push_back(2518);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("DepthStencilTestBusy", "Timing", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "6834fb52-42e8-bb50-fd48-ec2f2904e7e0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1747);
        internal_counters.push_back(2004);
        internal_counters.push_back(2261);
        internal_counters.push_back(2518);

        c.DefineDerivedCounter("DepthStencilTestBusyCount", "Timing", "Number of GPU cycles spent performing depth and stencil tests.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "e02860fa-c7bd-90ea-2149-69b4e98a636c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1618);
        internal_counters.push_back(1875);
        internal_counters.push_back(2132);
        internal_counters.push_back(2389);
        internal_counters.push_back(1607);
        internal_counters.push_back(1864);
        internal_counters.push_back(2121);
        internal_counters.push_back(2378);

        c.DefineDerivedCounter("HiZTilesAccepted", "DepthAndStencil", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*", "56176f45-d7ff-813d-4f05-3b2f046067e7");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1607);
        internal_counters.push_back(1864);
        internal_counters.push_back(2121);
        internal_counters.push_back(2378);

        c.DefineDerivedCounter("HiZTilesAcceptedCount", "DepthAndStencil", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "95d4e3f6-b2f0-f26e-8423-aacdfaf79ea3");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1618);
        internal_counters.push_back(1875);
        internal_counters.push_back(2132);
        internal_counters.push_back(2389);

        c.DefineDerivedCounter("HiZTilesRejectedCount", "DepthAndStencil", "Count of tiles not accepted by HiZ.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "156ba142-7eeb-aa6e-a00a-f8aea4e41e0b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1607);
        internal_counters.push_back(1864);
        internal_counters.push_back(2121);
        internal_counters.push_back(2378);
        internal_counters.push_back(1631);
        internal_counters.push_back(1888);
        internal_counters.push_back(2145);
        internal_counters.push_back(2402);

        c.DefineDerivedCounter("PreZTilesDetailCulled", "DepthAndStencil", "Percentage of tiles rejected because the associated prim had no contributing area.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "4,5,6,7,sum4,0,1,2,3,sum4,/,(100),*", "cad7f54d-a044-7574-c472-6f2065cbeeac");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1631);
        internal_counters.push_back(1888);
        internal_counters.push_back(2145);
        internal_counters.push_back(2402);

        c.DefineDerivedCounter("PreZTilesDetailCulledCount", "DepthAndStencil", "Count of tiles rejected because the associated primitive had no contributing area.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "49262c8a-b1e6-90dd-f096-0fc4921715e9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1607);
        internal_counters.push_back(1864);
        internal_counters.push_back(2121);
        internal_counters.push_back(2378);

        c.DefineDerivedCounter("PreZTilesDetailSurvivingCount", "DepthAndStencil", "Count of tiles surviving because the associated primitive had contributing area.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "f803eaa4-bbed-bd39-775f-a64df92e2c08");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2996);
        internal_counters.push_back(2997);
        internal_counters.push_back(2998);
        internal_counters.push_back(2999);
        internal_counters.push_back(3072);
        internal_counters.push_back(3073);
        internal_counters.push_back(3074);
        internal_counters.push_back(3075);

        c.DefineDerivedCounter("HiZQuadsCulled", "DepthAndStencil", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-,(0),max,0,1,+,2,+,3,+,/,(100),*", "fa0e319b-5573-6d34-5bab-904769925036");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2996);
        internal_counters.push_back(2997);
        internal_counters.push_back(2998);
        internal_counters.push_back(2999);
        internal_counters.push_back(3072);
        internal_counters.push_back(3073);
        internal_counters.push_back(3074);
        internal_counters.push_back(3075);

        c.DefineDerivedCounter("HiZQuadsCulledCount", "DepthAndStencil", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,+,2,+,3,+,4,-,5,-,6,-,7,-,(0),max", "73b0b39d-6df2-3e24-0b5c-7cb0ac8b6f39");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3072);
        internal_counters.push_back(3073);
        internal_counters.push_back(3074);
        internal_counters.push_back(3075);

        c.DefineDerivedCounter("HiZQuadsAcceptedCount", "DepthAndStencil", "Count of quads that did continue on in the pipeline after HiZ.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,+,2,+,3,+", "59049ad9-42b5-c7cb-3616-6a8f6a8e4894");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2996);
        internal_counters.push_back(2997);
        internal_counters.push_back(2998);
        internal_counters.push_back(2999);
        internal_counters.push_back(3096);
        internal_counters.push_back(3072);
        internal_counters.push_back(3073);
        internal_counters.push_back(3074);
        internal_counters.push_back(3075);

        c.DefineDerivedCounter("PreZQuadsCulled", "DepthAndStencil", "Percentage of quads rejected based on the detailZ and earlyZ tests.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "5,6,+,7,+,8,+,4,-,(0),max,0,1,+,2,+,3,+,/,(100),*", "4e77547b-ec55-5663-f034-af59be66d77d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3096);
        internal_counters.push_back(3072);
        internal_counters.push_back(3073);
        internal_counters.push_back(3074);
        internal_counters.push_back(3075);

        c.DefineDerivedCounter("PreZQuadsCulledCount", "DepthAndStencil", "Count of quads rejected based on the detailZ and earlyZ tests.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,+,2,+,3,+,4,+", "1bf169e6-9304-834e-df5f-0c44d7890a08");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(2996);
        internal_counters.push_back(2997);
        internal_counters.push_back(2998);
        internal_counters.push_back(2999);
        internal_counters.push_back(3096);
        internal_counters.push_back(3072);
        internal_counters.push_back(3073);
        internal_counters.push_back(3074);
        internal_counters.push_back(3075);

        c.DefineDerivedCounter("PreZQuadsSurvivingCount", "DepthAndStencil", "Count of quads surviving detailZ and earlyZ tests.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,+,2,+,3,+,4,-,5,-,6,-,7,-,8,-,(0),max", "50e25e51-3713-89cb-7f92-559cde5e5532");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3096);
        internal_counters.push_back(2996);
        internal_counters.push_back(2997);
        internal_counters.push_back(2998);
        internal_counters.push_back(2999);

        c.DefineDerivedCounter("PostZQuads", "DepthAndStencil", "Percentage of quads for which the pixel shader will run and may be postZ tested.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,+,3,+,4,+,/,(100),*,(100),min", "58f0d34b-eeb8-e8db-abce-cb72584144be");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(3096);

        c.DefineDerivedCounter("PostZQuadCount", "DepthAndStencil", "Count of quads for which the pixel shader will run and may be postZ tested.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0", "08404526-ce35-939b-34c8-a7a35a0ff4d6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1780);
        internal_counters.push_back(2037);
        internal_counters.push_back(2294);
        internal_counters.push_back(2551);

        c.DefineDerivedCounter("PreZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z before shading and passed.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "3bfe6c4d-7422-ca03-7ea5-e67ff1a00136");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1782);
        internal_counters.push_back(2039);
        internal_counters.push_back(2296);
        internal_counters.push_back(2553);

        c.DefineDerivedCounter("PreZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z before shading and failed stencil test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "df7f705e-5162-d3b5-da8b-63466cf9c4e5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1781);
        internal_counters.push_back(2038);
        internal_counters.push_back(2295);
        internal_counters.push_back(2552);

        c.DefineDerivedCounter("PreZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z before shading and failed Z test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "4484e950-f7a4-3800-bc74-78dd297f017e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1777);
        internal_counters.push_back(2034);
        internal_counters.push_back(2291);
        internal_counters.push_back(2548);

        c.DefineDerivedCounter("PostZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z after shading and passed.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "4995d5d6-2330-b986-508b-fae24856f44c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1779);
        internal_counters.push_back(2036);
        internal_counters.push_back(2293);
        internal_counters.push_back(2550);

        c.DefineDerivedCounter("PostZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z after shading and failed stencil test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "ae558af4-f4be-3dd4-7316-b2c4dcf0def8");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1778);
        internal_counters.push_back(2035);
        internal_counters.push_back(2292);
        internal_counters.push_back(2549);

        c.DefineDerivedCounter("PostZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z after shading and failed Z test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "b3684c94-814a-c695-c85d-a5b6ab798b35");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1649);
        internal_counters.push_back(1906);
        internal_counters.push_back(2163);
        internal_counters.push_back(2420);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("ZUnitStalled", "DepthAndStencil", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "5e86c3ad-1726-3157-1d01-7ed188bf854d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1649);
        internal_counters.push_back(1906);
        internal_counters.push_back(2163);
        internal_counters.push_back(2420);

        c.DefineDerivedCounter("ZUnitStalledCycles", "DepthAndStencil", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "4351fa7f-6737-2c3e-3ffb-b3addbdceedd");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1651);
        internal_counters.push_back(1908);
        internal_counters.push_back(2165);
        internal_counters.push_back(2422);
        internal_counters.push_back(1658);
        internal_counters.push_back(1915);
        internal_counters.push_back(2172);
        internal_counters.push_back(2429);

        c.DefineDerivedCounter("DBMemRead", "DepthAndStencil", "Number of bytes read from the depth buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,sum4,(256),*,4,5,6,7,sum4,(32),*,+", "dcdb4ee7-bd50-00f7-c028-9e5f4ce888c0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1663);
        internal_counters.push_back(1920);
        internal_counters.push_back(2177);
        internal_counters.push_back(2434);
        internal_counters.push_back(1666);
        internal_counters.push_back(1923);
        internal_counters.push_back(2180);
        internal_counters.push_back(2437);

        c.DefineDerivedCounter("DBMemWritten", "DepthAndStencil", "Number of bytes written to the depth buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,sum4,(32),*,4,5,6,7,sum4,(32),*,+", "de5717f8-8a49-ee44-4645-10de51b37dcf");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(128);
        internal_counters.push_back(524);
        internal_counters.push_back(920);
        internal_counters.push_back(1316);

        c.DefineDerivedCounter("CBMemRead", "ColorBuffer", "Number of bytes read from the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,sum4,(32),*", "84b531d8-a1f8-7f49-7c27-7bc97801f1e6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(259);
        internal_counters.push_back(655);
        internal_counters.push_back(1051);
        internal_counters.push_back(1447);
        internal_counters.push_back(126);
        internal_counters.push_back(522);
        internal_counters.push_back(918);
        internal_counters.push_back(1314);
        internal_counters.push_back(127);
        internal_counters.push_back(523);
        internal_counters.push_back(919);
        internal_counters.push_back(1315);
        internal_counters.push_back(128);
        internal_counters.push_back(524);
        internal_counters.push_back(920);
        internal_counters.push_back(1316);

        c.DefineDerivedCounter("CBColorAndMaskRead", "ColorBuffer", "Total number of bytes read from the color and mask buffers.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "da41660e-eb6f-32ec-8a64-b32ca17bd7eb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(118);
        internal_counters.push_back(514);
        internal_counters.push_back(910);
        internal_counters.push_back(1306);

        c.DefineDerivedCounter("CBMemWritten", "ColorBuffer", "Number of bytes written to the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,sum4,(32),*", "550f8ff8-60b6-a6bf-87d0-25ac9e87de70");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(257);
        internal_counters.push_back(653);
        internal_counters.push_back(1049);
        internal_counters.push_back(1445);
        internal_counters.push_back(116);
        internal_counters.push_back(512);
        internal_counters.push_back(908);
        internal_counters.push_back(1304);
        internal_counters.push_back(117);
        internal_counters.push_back(513);
        internal_counters.push_back(909);
        internal_counters.push_back(1305);
        internal_counters.push_back(118);
        internal_counters.push_back(514);
        internal_counters.push_back(910);
        internal_counters.push_back(1306);

        c.DefineDerivedCounter("CBColorAndMaskWritten", "ColorBuffer", "Total number of bytes written to the color and mask buffers.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "29a04b69-8f5f-b770-a0f2-3453e2c99e49");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(162);
        internal_counters.push_back(558);
        internal_counters.push_back(954);
        internal_counters.push_back(1350);
        internal_counters.push_back(7);
        internal_counters.push_back(403);
        internal_counters.push_back(799);
        internal_counters.push_back(1195);

        c.DefineDerivedCounter("CBSlowPixelPct", "ColorBuffer", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*,(100),min", "5775943f-0313-7e52-9638-b24a449197bc");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(162);
        internal_counters.push_back(558);
        internal_counters.push_back(954);
        internal_counters.push_back(1350);

        c.DefineDerivedCounter("CBSlowPixelCount", "ColorBuffer", "Number of pixels written to the color buffer using a half-rate or quarter-rate format.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "47eacbb0-28c8-22b4-5c69-c00d5813bb1c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7862);
        internal_counters.push_back(8054);
        internal_counters.push_back(8246);
        internal_counters.push_back(8438);
        internal_counters.push_back(8630);
        internal_counters.push_back(8822);
        internal_counters.push_back(9014);
        internal_counters.push_back(9206);
        internal_counters.push_back(9398);
        internal_counters.push_back(9590);
        internal_counters.push_back(9782);
        internal_counters.push_back(9974);
        internal_counters.push_back(10166);
        internal_counters.push_back(10358);
        internal_counters.push_back(10550);
        internal_counters.push_back(10742);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total bytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "664bb3ef-6eca-86b1-1e2d-30cb897b5fa9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7853);
        internal_counters.push_back(8045);
        internal_counters.push_back(8237);
        internal_counters.push_back(8429);
        internal_counters.push_back(8621);
        internal_counters.push_back(8813);
        internal_counters.push_back(9005);
        internal_counters.push_back(9197);
        internal_counters.push_back(9389);
        internal_counters.push_back(9581);
        internal_counters.push_back(9773);
        internal_counters.push_back(9965);
        internal_counters.push_back(10157);
        internal_counters.push_back(10349);
        internal_counters.push_back(10541);
        internal_counters.push_back(10733);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total bytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "f96f2c16-b1b4-4ec4-229c-fc82e6f80a82");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7845);
        internal_counters.push_back(8037);
        internal_counters.push_back(8229);
        internal_counters.push_back(8421);
        internal_counters.push_back(8613);
        internal_counters.push_back(8805);
        internal_counters.push_back(8997);
        internal_counters.push_back(9189);
        internal_counters.push_back(9381);
        internal_counters.push_back(9573);
        internal_counters.push_back(9765);
        internal_counters.push_back(9957);
        internal_counters.push_back(10149);
        internal_counters.push_back(10341);
        internal_counters.push_back(10533);
        internal_counters.push_back(10725);
        internal_counters.push_back(7846);
        internal_counters.push_back(8038);
        internal_counters.push_back(8230);
        internal_counters.push_back(8422);
        internal_counters.push_back(8614);
        internal_counters.push_back(8806);
        internal_counters.push_back(8998);
        internal_counters.push_back(9190);
        internal_counters.push_back(9382);
        internal_counters.push_back(9574);
        internal_counters.push_back(9766);
        internal_counters.push_back(9958);
        internal_counters.push_back(10150);
        internal_counters.push_back(10342);
        internal_counters.push_back(10534);
        internal_counters.push_back(10726);

        c.DefineDerivedCounter("CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "dfbeebab-f7c1-1211-e502-4aae361e2ad7");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7845);
        internal_counters.push_back(8037);
        internal_counters.push_back(8229);
        internal_counters.push_back(8421);
        internal_counters.push_back(8613);
        internal_counters.push_back(8805);
        internal_counters.push_back(8997);
        internal_counters.push_back(9189);
        internal_counters.push_back(9381);
        internal_counters.push_back(9573);
        internal_counters.push_back(9765);
        internal_counters.push_back(9957);
        internal_counters.push_back(10149);
        internal_counters.push_back(10341);
        internal_counters.push_back(10533);
        internal_counters.push_back(10725);
        internal_counters.push_back(7846);
        internal_counters.push_back(8038);
        internal_counters.push_back(8230);
        internal_counters.push_back(8422);
        internal_counters.push_back(8614);
        internal_counters.push_back(8806);
        internal_counters.push_back(8998);
        internal_counters.push_back(9190);
        internal_counters.push_back(9382);
        internal_counters.push_back(9574);
        internal_counters.push_back(9766);
        internal_counters.push_back(9958);
        internal_counters.push_back(10150);
        internal_counters.push_back(10342);
        internal_counters.push_back(10534);
        internal_counters.push_back(10726);

        c.DefineDerivedCounter("CacheMiss", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that miss the data cache. Value range: 0% (optimal) to 100% (all miss).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "aebc0a53-7f87-60bd-4c4b-2b956846ef83");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7845);
        internal_counters.push_back(8037);
        internal_counters.push_back(8229);
        internal_counters.push_back(8421);
        internal_counters.push_back(8613);
        internal_counters.push_back(8805);
        internal_counters.push_back(8997);
        internal_counters.push_back(9189);
        internal_counters.push_back(9381);
        internal_counters.push_back(9573);
        internal_counters.push_back(9765);
        internal_counters.push_back(9957);
        internal_counters.push_back(10149);
        internal_counters.push_back(10341);
        internal_counters.push_back(10533);
        internal_counters.push_back(10725);

        c.DefineDerivedCounter("CacheHitCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that hit the data cache.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "43437652-1024-9737-2eb0-0899c0c1feae");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7846);
        internal_counters.push_back(8038);
        internal_counters.push_back(8230);
        internal_counters.push_back(8422);
        internal_counters.push_back(8614);
        internal_counters.push_back(8806);
        internal_counters.push_back(8998);
        internal_counters.push_back(9190);
        internal_counters.push_back(9382);
        internal_counters.push_back(9574);
        internal_counters.push_back(9766);
        internal_counters.push_back(9958);
        internal_counters.push_back(10150);
        internal_counters.push_back(10342);
        internal_counters.push_back(10534);
        internal_counters.push_back(10726);

        c.DefineDerivedCounter("CacheMissCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that miss the data cache.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "d0f8a812-f41b-644f-09d1-14ee03ea3671");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5868);
        internal_counters.push_back(5987);
        internal_counters.push_back(6106);
        internal_counters.push_back(6225);
        internal_counters.push_back(6344);
        internal_counters.push_back(6463);
        internal_counters.push_back(6582);
        internal_counters.push_back(6701);
        internal_counters.push_back(6820);
        internal_counters.push_back(6939);
        internal_counters.push_back(7058);
        internal_counters.push_back(7177);
        internal_counters.push_back(7296);
        internal_counters.push_back(7415);
        internal_counters.push_back(7534);
        internal_counters.push_back(7653);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5868);
        internal_counters.push_back(5987);
        internal_counters.push_back(6106);
        internal_counters.push_back(6225);
        internal_counters.push_back(6344);
        internal_counters.push_back(6463);
        internal_counters.push_back(6582);
        internal_counters.push_back(6701);
        internal_counters.push_back(6820);
        internal_counters.push_back(6939);
        internal_counters.push_back(7058);
        internal_counters.push_back(7177);
        internal_counters.push_back(7296);
        internal_counters.push_back(7415);
        internal_counters.push_back(7534);
        internal_counters.push_back(7653);

        c.DefineDerivedCounter("MemUnitBusyCycles", "GlobalMemory", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalledCycles). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "168f077c-4797-b2f5-717f-105c725266c8");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(11782);
        internal_counters.push_back(11962);
        internal_counters.push_back(12142);
        internal_counters.push_back(12322);
        internal_counters.push_back(12502);
        internal_counters.push_back(12682);
        internal_counters.push_back(12862);
        internal_counters.push_back(13042);
        internal_counters.push_back(13222);
        internal_counters.push_back(13402);
        internal_counters.push_back(13582);
        internal_counters.push_back(13762);
        internal_counters.push_back(13942);
        internal_counters.push_back(14122);
        internal_counters.push_back(14302);
        internal_counters.push_back(14482);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(11782);
        internal_counters.push_back(11962);
        internal_counters.push_back(12142);
        internal_counters.push_back(12322);
        internal_counters.push_back(12502);
        internal_counters.push_back(12682);
        internal_counters.push_back(12862);
        internal_counters.push_back(13042);
        internal_counters.push_back(13222);
        internal_counters.push_back(13402);
        internal_counters.push_back(13582);
        internal_counters.push_back(13762);
        internal_counters.push_back(13942);
        internal_counters.push_back(14122);
        internal_counters.push_back(14302);
        internal_counters.push_back(14482);

        c.DefineDerivedCounter("MemUnitStalledCycles", "GlobalMemory", "Number of GPU cycles the memory unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "2745659a-0e40-bace-3b9b-86a54f8e4623");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7855);
        internal_counters.push_back(8047);
        internal_counters.push_back(8239);
        internal_counters.push_back(8431);
        internal_counters.push_back(8623);
        internal_counters.push_back(8815);
        internal_counters.push_back(9007);
        internal_counters.push_back(9199);
        internal_counters.push_back(9391);
        internal_counters.push_back(9583);
        internal_counters.push_back(9775);
        internal_counters.push_back(9967);
        internal_counters.push_back(10159);
        internal_counters.push_back(10351);
        internal_counters.push_back(10543);
        internal_counters.push_back(10735);
        internal_counters.push_back(2633);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(7855);
        internal_counters.push_back(8047);
        internal_counters.push_back(8239);
        internal_counters.push_back(8431);
        internal_counters.push_back(8623);
        internal_counters.push_back(8815);
        internal_counters.push_back(9007);
        internal_counters.push_back(9199);
        internal_counters.push_back(9391);
        internal_counters.push_back(9583);
        internal_counters.push_back(9775);
        internal_counters.push_back(9967);
        internal_counters.push_back(10159);
        internal_counters.push_back(10351);
        internal_counters.push_back(10543);
        internal_counters.push_back(10735);

        c.DefineDerivedCounter("WriteUnitStalledCycles", "GlobalMemory", "Number of GPU cycles the Write unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "ede3305e-abd4-d6bf-6b00-ffc57a29fce3");
    }
}

