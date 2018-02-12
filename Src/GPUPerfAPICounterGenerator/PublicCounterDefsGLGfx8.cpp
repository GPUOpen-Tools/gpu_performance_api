//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for GLGFX8
//==============================================================================

#include "PublicCounterDefsGLGfx8.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicCountersGLGfx8(GPA_PublicCounters& p)
{
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(15125);

        p.DefinePublicCounter("GPUTime", "Timing", "Time this API call took to execute on the GPU in milliseconds. Does not include time that draw calls are processed in parallel.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "0,TS_FREQ,/,(1000),*", "00bfa9cd-5512-48e8-7055-7b592113b8cb" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2633);
        internalCounters.push_back(2631);

        p.DefinePublicCounter("GPUBusy", "Timing", "The percentage of time GPU was busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,(100),*,(100),min", "bef38bf3-1167-0844-81f0-67d2d28ddbc5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2633);

        p.DefinePublicCounter("GPUBusyCycles", "Timing", "Number of GPU cycles that the GPU was busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0", "1e84970d-7014-2b8d-d61e-388b5f782691" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14904);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("TessellatorBusy", "Timing", "The percentage of time the tessellation engine is busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*", "36af6c72-dcfb-8102-4fd4-ce8ddc573365" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14904);

        p.DefinePublicCounter("TessellatorBusyCycles", "Timing", "Number of GPU cycles that the tessellation engine is busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_PRIM_PIPES,/", "60289dcb-7b33-46e7-26d1-8a2121605543" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3231);
        internalCounters.push_back(3256);
        internalCounters.push_back(3278);
        internalCounters.push_back(3300);
        internalCounters.push_back(3240);
        internalCounters.push_back(3262);
        internalCounters.push_back(3284);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("VSBusy", "Timing", "The percentage of time the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,4,ifnotzero,1,5,ifnotzero,2,6,ifnotzero,7,/,(100),*,(100),min", "94caad5e-867c-6c09-cf3a-d05b51df8f3b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3231);
        internalCounters.push_back(3256);
        internalCounters.push_back(3278);
        internalCounters.push_back(3300);
        internalCounters.push_back(3240);
        internalCounters.push_back(3262);
        internalCounters.push_back(3284);

        p.DefinePublicCounter("VSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,4,ifnotzero,1,5,ifnotzero,2,6,ifnotzero", "a2086d4e-274b-48a8-3e08-a4ab76ac15dd" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(15125);
        internalCounters.push_back(3231);
        internalCounters.push_back(3256);
        internalCounters.push_back(3278);
        internalCounters.push_back(3300);
        internalCounters.push_back(3240);
        internalCounters.push_back(3262);
        internalCounters.push_back(3284);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("VSTime", "Timing", "Time vertex shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "(0),1,5,ifnotzero,2,6,ifnotzero,3,7,ifnotzero,8,/,(1),min,0,TS_FREQ,/,(1000),*,*", "fee660c7-8e01-4dc5-e5d0-fcb61c17fb2c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3268);
        internalCounters.push_back(3274);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("HSBusy", "Timing", "The percentage of time the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "16f30a0b-4cbf-eccd-b13f-ab68dd254d32" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3268);
        internalCounters.push_back(3274);

        p.DefinePublicCounter("HSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero", "753e76ef-8ef8-3f13-b511-4bd9f3589fdb" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(15125);
        internalCounters.push_back(3268);
        internalCounters.push_back(3274);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("HSTime", "Timing", "Time hull shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*", "8792e9f1-fb39-b92a-b230-f33df4c8a0de" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3231);
        internalCounters.push_back(3256);
        internalCounters.push_back(3300);
        internalCounters.push_back(3262);
        internalCounters.push_back(3284);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("DSBusy", "Timing", "The percentage of time the ShaderUnit has domain shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,5,/,(100),*,(100),min", "0c626e8a-9b82-b6d4-d9a3-578509316301" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3231);
        internalCounters.push_back(3256);
        internalCounters.push_back(3300);
        internalCounters.push_back(3262);
        internalCounters.push_back(3284);

        p.DefinePublicCounter("DSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has domain shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero", "2f3f7561-0549-2232-536d-129ffc5f7703" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(15125);
        internalCounters.push_back(3231);
        internalCounters.push_back(3256);
        internalCounters.push_back(3300);
        internalCounters.push_back(3262);
        internalCounters.push_back(3284);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("DSTime", "Timing", "Time domain shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "(0),1,2,4,ifnotzero,5,ifnotzero,6,/,(1),min,0,TS_FREQ,/,(1000),*,*", "f050e495-f511-ecc9-9c46-c96516bddeb2" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3247);
        internalCounters.push_back(3250);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("GSBusy", "Timing", "The percentage of time the ShaderUnit has geometry shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "876f36d8-d046-833f-7832-673cbffd0a45" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3247);
        internalCounters.push_back(3250);

        p.DefinePublicCounter("GSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has geometry shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero", "48203b6b-8983-c067-d63e-05da8be5111b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(15125);
        internalCounters.push_back(3247);
        internalCounters.push_back(3250);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("GSTime", "Timing", "Time geometry shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*", "86d56794-f391-b601-9388-851b646d346c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3300);
        internalCounters.push_back(3305);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("PSBusy", "Timing", "The percentage of time the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "7e772beb-d82c-bd9a-aed0-fe504d416ce5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3300);
        internalCounters.push_back(3305);

        p.DefinePublicCounter("PSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero", "b58bea04-ce8e-2984-80f4-8aba7d4c817b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(15125);
        internalCounters.push_back(3300);
        internalCounters.push_back(3305);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("PSTime", "Timing", "Time pixel shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*", "f564ee00-ffcf-f7f6-fcbf-f200205cd0cc" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3288);
        internalCounters.push_back(3292);
        internalCounters.push_back(3294);
        internalCounters.push_back(3298);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("CSBusy", "Timing", "The percentage of time the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,max,4,/,(100),*,(100),min", "493fdd90-8d2b-a055-5e4e-2d29c3396b8c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3288);
        internalCounters.push_back(3292);
        internalCounters.push_back(3294);
        internalCounters.push_back(3298);

        p.DefinePublicCounter("CSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,max", "39bcf1b8-f6b2-4c37-f9af-0a2bb59512f9" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(15125);
        internalCounters.push_back(3288);
        internalCounters.push_back(3292);
        internalCounters.push_back(3294);
        internalCounters.push_back(3298);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("CSTime", "Timing", "Time compute shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "(0),1,2,ifnotzero,(0),3,4,ifnotzero,max,5,/,(1),min,0,TS_FREQ,/,(1000),*,*", "5177faaf-f59d-ee23-6e36-0ea087dca9dc" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14800);
        internalCounters.push_back(14781);
        internalCounters.push_back(14876);

        p.DefinePublicCounter("VSVerticesIn", "VertexShader", "The number of vertices processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero", "810a04c8-2ff4-081d-766d-bfa2bd4ad916" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4350);
        internalCounters.push_back(4328);
        internalCounters.push_back(3752);
        internalCounters.push_back(3730);
        internalCounters.push_back(3740);
        internalCounters.push_back(4948);
        internalCounters.push_back(4926);
        internalCounters.push_back(4936);

        p.DefinePublicCounter("VSVALUInstCount", "VertexShader", "Average number of vector ALU instructions executed in the VS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/,2,3,/,4,ifnotzero,5,6,/,7,ifnotzero", "8ec604e4-63f5-e6b5-4558-c38f0b26d4b1" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4354);
        internalCounters.push_back(4328);
        internalCounters.push_back(3756);
        internalCounters.push_back(3730);
        internalCounters.push_back(3740);
        internalCounters.push_back(4952);
        internalCounters.push_back(4926);
        internalCounters.push_back(4936);

        p.DefinePublicCounter("VSSALUInstCount", "VertexShader", "Average number of scalar ALU instructions executed in the VS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/,2,3,/,4,ifnotzero,5,6,/,7,ifnotzero", "e3da0383-7322-7f65-8cf2-3ce641578e54" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4405);
        internalCounters.push_back(3807);
        internalCounters.push_back(3740);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("VSVALUBusy", "VertexShader", "The percentage of GPUTime vector ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,ifnotzero,(4),*,NUM_SIMDS,/,3,/,(100),*", "8b3572f7-fda0-eddf-6c93-2ab145b8754b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4405);
        internalCounters.push_back(3807);
        internalCounters.push_back(3740);

        p.DefinePublicCounter("VSVALUBusyCycles", "VertexShader", "Number of GPU cycles where vector ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,ifnotzero,(4),*,NUM_SIMDS,/", "0af1686e-6d77-2f6e-2862-7bb8e869a776" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4410);
        internalCounters.push_back(3812);
        internalCounters.push_back(3740);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("VSSALUBusy", "VertexShader", "The percentage of GPUTime scalar ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,ifnotzero,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,3,/,(100),*", "3bc8730c-e3bc-e2f0-7d24-36974064c25a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4410);
        internalCounters.push_back(3812);
        internalCounters.push_back(3740);

        p.DefinePublicCounter("VSSALUBusyCycles", "VertexShader", "Number of GPU cycles where scalar ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,ifnotzero,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "357ac7cd-2e1c-dcb0-77f6-37527237f35b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14885);

        p.DefinePublicCounter("HSPatches", "HullShader", "The number of patches processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "d1bbd27d-d591-4509-df52-d329fb73a98f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5247);
        internalCounters.push_back(5225);

        p.DefinePublicCounter("HSVALUInstCount", "HullShader", "Average number of vector ALU instructions executed in the HS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "786673bf-d58f-9895-3a37-9d6efb5e5804" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5251);
        internalCounters.push_back(5225);

        p.DefinePublicCounter("HSSALUInstCount", "HullShader", "Average number of scalar ALU instructions executed in the HS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "1af675c4-cb0b-c4c5-c131-2796750f683e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5302);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("HSVALUBusy", "HullShader", "The percentage of GPUTime vector ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "7880d192-8015-0311-d43e-fb0b7a4df179" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5302);

        p.DefinePublicCounter("HSVALUBusyCycles", "HullShader", "Number of GPU cycles vector where ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,/", "3afb94e4-e937-5730-0cc9-41d3113ba012" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5307);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("HSSALUBusy", "HullShader", "The percentage of GPUTime scalar ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*", "34748a4b-9148-0b06-b7b9-5700d6631bde" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5307);

        p.DefinePublicCounter("HSSALUBusyCycles", "HullShader", "Number of GPU cycles where scalar ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "9bceabf7-3f01-2fd9-7b1d-8fe46c729efc" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14800);
        internalCounters.push_back(14781);
        internalCounters.push_back(14876);

        p.DefinePublicCounter("DSVerticesIn", "DomainShader", "The number of vertices processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,1,ifnotzero,2,ifnotzero", "b88d9d05-2418-e639-4e3d-3a5815855f8d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4350);
        internalCounters.push_back(4328);
        internalCounters.push_back(3752);
        internalCounters.push_back(3730);
        internalCounters.push_back(3740);
        internalCounters.push_back(4936);

        p.DefinePublicCounter("DSVALUInstCount", "DomainShader", "Average number of vector ALU instructions executed in the DS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,2,3,/,4,ifnotzero,5,ifnotzero", "03a3e949-82f9-be4d-7228-5eb5ad80915a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4354);
        internalCounters.push_back(4328);
        internalCounters.push_back(3756);
        internalCounters.push_back(3730);
        internalCounters.push_back(3740);
        internalCounters.push_back(4936);

        p.DefinePublicCounter("DSSALUInstCount", "DomainShader", "Average number of scalar ALU instructions executed in the DS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,2,3,/,4,ifnotzero,5,ifnotzero", "73daa728-483e-95d0-5b40-504719aadc1c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4405);
        internalCounters.push_back(3807);
        internalCounters.push_back(2633);
        internalCounters.push_back(3740);
        internalCounters.push_back(4936);

        p.DefinePublicCounter("DSVALUBusy", "DomainShader", "The percentage of GPUTime vector ALU instructions are being processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,(4),*,NUM_SIMDS,/,2,/,(100),*", "ddc0dd0c-0c73-b831-a410-cfea8b9713d9" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4405);
        internalCounters.push_back(3807);
        internalCounters.push_back(3740);
        internalCounters.push_back(4936);

        p.DefinePublicCounter("DSVALUBusyCycles", "DomainShader", "Number of GPU cycles where vector ALU instructions are being processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,ifnotzero,3,ifnotzero,(4),*,NUM_SIMDS,/", "1e280912-81ee-a684-823b-94c468d8ebda" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4410);
        internalCounters.push_back(3812);
        internalCounters.push_back(2633);
        internalCounters.push_back(3740);
        internalCounters.push_back(4936);

        p.DefinePublicCounter("DSSALUBusy", "DomainShader", "The percentage of GPUTime scalar ALU instructions are being processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,2,/,(100),*", "b639f64c-24af-348f-6439-43c701b4fc07" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4410);
        internalCounters.push_back(3812);
        internalCounters.push_back(3740);
        internalCounters.push_back(4936);

        p.DefinePublicCounter("DSSALUBusyCycles", "DomainShader", "Number of GPU cycles where scalar ALU instructions are being processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,ifnotzero,3,ifnotzero,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "b5bf8a0c-e682-1aa6-23d7-c6c6784ffa5c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14789);

        p.DefinePublicCounter("GSPrimsIn", "GeometryShader", "The number of primitives passed into the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "20c29866-509a-aaab-2697-6b2c38f79953" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14800);
        internalCounters.push_back(14781);

        p.DefinePublicCounter("GSVerticesOut", "GeometryShader", "The number of vertices output by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,ifnotzero", "775b9736-319a-bd8a-48c9-68db9c91d978" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4051);
        internalCounters.push_back(4029);

        p.DefinePublicCounter("GSVALUInstCount", "GeometryShader", "Average number of vector ALU instructions executed in the GS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "21b12bfa-b8cd-2e71-a2d5-f9e9f1d65d61" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4055);
        internalCounters.push_back(4029);

        p.DefinePublicCounter("GSSALUInstCount", "GeometryShader", "Average number of scalar ALU instructions executed in the GS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "a8562594-d335-ca43-61bf-03b72d2b98a5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4106);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("GSVALUBusy", "GeometryShader", "The percentage of GPUTime vector ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "228a4818-1e56-cebb-0720-3b2cdc057a6f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4106);

        p.DefinePublicCounter("GSVALUBusyCycles", "GeometryShader", "Number of GPU cycles where vector ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,/", "be217edd-226f-bd97-9a48-46e2809b1933" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4111);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("GSSALUBusy", "GeometryShader", "The percentage of GPUTime scalar ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*", "f28ce300-800e-9822-39e4-f48528bdb935" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4111);

        p.DefinePublicCounter("GSSALUBusyCycles", "GeometryShader", "Number of GPU cycles where scalar ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "b3eace7c-3bc4-0107-887f-923851dc8ea7" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2785);
        internalCounters.push_back(2789);
        internalCounters.push_back(2741);
        internalCounters.push_back(2753);
        internalCounters.push_back(2742);
        internalCounters.push_back(2754);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("PrimitiveAssemblyBusy", "Timing", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max,6,/,(100),*,(100),min", "54ac5640-c4d7-95e2-20e0-6a9fdfc07333" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2785);
        internalCounters.push_back(2789);
        internalCounters.push_back(2741);
        internalCounters.push_back(2753);
        internalCounters.push_back(2742);
        internalCounters.push_back(2754);

        p.DefinePublicCounter("PrimitiveAssemblyBusyCycles", "Timing", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max", "99777f2d-9626-c78a-a97c-c4505eba1e5f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2688);

        p.DefinePublicCounter("PrimitivesIn", "PrimitiveAssembly", "The number of primitives received by the hardware. This includes primitives generated by tessellation.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "a515b80d-75c3-c7d2-0d2f-d7766b4759a6" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2694);
        internalCounters.push_back(2734);
        internalCounters.push_back(2735);
        internalCounters.push_back(2736);
        internalCounters.push_back(2737);

        p.DefinePublicCounter("CulledPrims", "PrimitiveAssembly", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+,4,+", "589bdf55-9192-280a-41c3-584bc94f2562" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2701);

        p.DefinePublicCounter("ClippedPrims", "PrimitiveAssembly", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "5ef6f9d5-155e-5baa-163f-8359d9ea9bbf" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2789);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("PAStalledOnRasterizer", "PrimitiveAssembly", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*", "6f9f416b-53c1-0457-f88c-7b6ba8973974" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2789);

        p.DefinePublicCounter("PAStalledOnRasterizerCycles", "PrimitiveAssembly", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_PRIM_PIPES,/", "7a8c492a-c566-9328-6805-760dbff5c0f2" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5831);
        internalCounters.push_back(5836);
        internalCounters.push_back(5841);
        internalCounters.push_back(5846);

        p.DefinePublicCounter("PSPixelsOut", "PixelShader", "Pixels exported from shader to colour buffers. Does not include killed or alpha tested pixels; if there are multiple rendertargets, each rendertarget receives one export, so this will be 2 for 1 pixel written to two RTs.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "181f5ca1-ec90-61a3-fd73-d8e3722af9e9" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5833);
        internalCounters.push_back(5838);
        internalCounters.push_back(5843);
        internalCounters.push_back(5848);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("PSExportStalls", "PixelShader", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the colour buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "996ce2b4-55ce-25c1-afb7-575bd9b4ce90" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5833);
        internalCounters.push_back(5838);
        internalCounters.push_back(5843);
        internalCounters.push_back(5848);

        p.DefinePublicCounter("PSExportStallsCycles", "PixelShader", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the colour buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "5e58e8ae-1854-e662-b460-a4a31f7fb493" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4649);
        internalCounters.push_back(4627);

        p.DefinePublicCounter("PSVALUInstCount", "PixelShader", "Average number of vector ALU instructions executed in the PS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "eb74389e-435c-4137-ecf1-39eb5bc1cbfe" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4653);
        internalCounters.push_back(4627);

        p.DefinePublicCounter("PSSALUInstCount", "PixelShader", "Average number of scalar ALU instructions executed in the PS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "e6a06580-8a82-96d6-976c-acc121fc5516" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4704);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("PSVALUBusy", "PixelShader", "The percentage of GPUTime vector ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "6ce6fef7-8e33-10b4-f351-af755e177e85" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4704);

        p.DefinePublicCounter("PSVALUBusyCycles", "PixelShader", "Number of GPU cycles where vector ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,/", "1e276f86-cd2a-72e7-fc9d-004f666f2981" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4709);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("PSSALUBusy", "PixelShader", "The percentage of GPUTime scalar ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*", "2ff9f34f-e94b-af4d-18c2-5fbbf6d1727a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4709);

        p.DefinePublicCounter("PSSALUBusyCycles", "PixelShader", "Number of GPU cycles where scalar ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "29808906-f128-b078-fc79-820a4b3b3b8d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3289);
        internalCounters.push_back(3295);

        p.DefinePublicCounter("CSThreadGroups", "ComputeShader", "Total number of thread groups.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+", "8ce3fc80-56b2-97f9-8e70-2e8c747cea68" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5524);

        p.DefinePublicCounter("CSWavefronts", "ComputeShader", "The total number of wavefronts used for the CS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "42379c6e-369b-c237-8b25-cdb9cdc65c4d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5534);

        p.DefinePublicCounter("CSThreads", "ComputeShader", "The number of CS threads processed by the hardware.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "7a648013-6eac-2665-ac36-13c6f4ac9c26" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5546);
        internalCounters.push_back(5524);

        p.DefinePublicCounter("CSVALUInsts", "ComputeShader", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "376cb1cc-5a40-9d1d-404c-f1736c0c5084" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5609);
        internalCounters.push_back(5601);

        p.DefinePublicCounter("CSVALUUtilization", "ComputeShader", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,(64),*,/,(100),*,1,ifnotzero,(100),min", "4476879e-cdc0-d602-b24e-9b4a8d38438f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5550);
        internalCounters.push_back(5524);

        p.DefinePublicCounter("CSSALUInsts", "ComputeShader", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "eb211144-8136-ff86-e8bf-4d0493a904cb" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5548);
        internalCounters.push_back(5954);
        internalCounters.push_back(6073);
        internalCounters.push_back(6192);
        internalCounters.push_back(6311);
        internalCounters.push_back(6430);
        internalCounters.push_back(6549);
        internalCounters.push_back(6668);
        internalCounters.push_back(6787);
        internalCounters.push_back(6906);
        internalCounters.push_back(7025);
        internalCounters.push_back(7144);
        internalCounters.push_back(7263);
        internalCounters.push_back(7382);
        internalCounters.push_back(7501);
        internalCounters.push_back(7620);
        internalCounters.push_back(7739);
        internalCounters.push_back(5524);

        p.DefinePublicCounter("CSVFetchInsts", "ComputeShader", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/,17,ifnotzero", "3e2829c0-6215-783b-c271-6d57ff2c520e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5551);
        internalCounters.push_back(5524);

        p.DefinePublicCounter("CSSFetchInsts", "ComputeShader", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "da09171c-6a0a-584f-fddc-dc5062d63a3e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5547);
        internalCounters.push_back(5955);
        internalCounters.push_back(6074);
        internalCounters.push_back(6193);
        internalCounters.push_back(6312);
        internalCounters.push_back(6431);
        internalCounters.push_back(6550);
        internalCounters.push_back(6669);
        internalCounters.push_back(6788);
        internalCounters.push_back(6907);
        internalCounters.push_back(7026);
        internalCounters.push_back(7145);
        internalCounters.push_back(7264);
        internalCounters.push_back(7383);
        internalCounters.push_back(7502);
        internalCounters.push_back(7621);
        internalCounters.push_back(7740);
        internalCounters.push_back(5524);

        p.DefinePublicCounter("CSVWriteInsts", "ComputeShader", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/,17,ifnotzero", "43438c22-e910-b377-b767-b32902e0df0d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5552);
        internalCounters.push_back(5553);
        internalCounters.push_back(5524);

        p.DefinePublicCounter("CSFlatVMemInsts", "ComputeShader", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,-,2,/,2,ifnotzero", "2570b477-13e3-f5b6-e6ff-7159373bc74d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5601);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("CSVALUBusy", "ComputeShader", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "f1e64815-f6a8-c277-d4f9-d054b443e205" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5601);

        p.DefinePublicCounter("CSVALUBusyCycles", "ComputeShader", "Number of GPU cycles where vector ALU instructions are processed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,/", "2d0d5852-2658-eb73-68d2-f23f7118c9c3" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5606);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("CSSALUBusy", "ComputeShader", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*", "3fc35f4e-9882-94e3-6f5f-4e81cd97082a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5606);

        p.DefinePublicCounter("CSSALUBusyCycles", "ComputeShader", "Number of GPU cycles where scalar ALU instructions are processed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "de58f8fc-8ed4-a799-648d-62ded7b1c4c4" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5868);
        internalCounters.push_back(5987);
        internalCounters.push_back(6106);
        internalCounters.push_back(6225);
        internalCounters.push_back(6344);
        internalCounters.push_back(6463);
        internalCounters.push_back(6582);
        internalCounters.push_back(6701);
        internalCounters.push_back(6820);
        internalCounters.push_back(6939);
        internalCounters.push_back(7058);
        internalCounters.push_back(7177);
        internalCounters.push_back(7296);
        internalCounters.push_back(7415);
        internalCounters.push_back(7534);
        internalCounters.push_back(7653);
        internalCounters.push_back(2633);
        internalCounters.push_back(3289);
        internalCounters.push_back(3295);

        p.DefinePublicCounter("CSMemUnitBusy", "ComputeShader", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*,17,18,+,ifnotzero", "42ab96e1-0a24-96c8-c4ff-098fa267d78e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5868);
        internalCounters.push_back(5987);
        internalCounters.push_back(6106);
        internalCounters.push_back(6225);
        internalCounters.push_back(6344);
        internalCounters.push_back(6463);
        internalCounters.push_back(6582);
        internalCounters.push_back(6701);
        internalCounters.push_back(6820);
        internalCounters.push_back(6939);
        internalCounters.push_back(7058);
        internalCounters.push_back(7177);
        internalCounters.push_back(7296);
        internalCounters.push_back(7415);
        internalCounters.push_back(7534);
        internalCounters.push_back(7653);

        p.DefinePublicCounter("CSMemUnitBusyCycles", "ComputeShader", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ENGINES,/", "39d5687f-c727-7c0c-af82-bb711d3897ed" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11782);
        internalCounters.push_back(11962);
        internalCounters.push_back(12142);
        internalCounters.push_back(12322);
        internalCounters.push_back(12502);
        internalCounters.push_back(12682);
        internalCounters.push_back(12862);
        internalCounters.push_back(13042);
        internalCounters.push_back(13222);
        internalCounters.push_back(13402);
        internalCounters.push_back(13582);
        internalCounters.push_back(13762);
        internalCounters.push_back(13942);
        internalCounters.push_back(14122);
        internalCounters.push_back(14302);
        internalCounters.push_back(14482);
        internalCounters.push_back(2633);
        internalCounters.push_back(3289);
        internalCounters.push_back(3295);

        p.DefinePublicCounter("CSMemUnitStalled", "ComputeShader", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*,17,18,+,ifnotzero", "f18e8679-1511-d533-d9ee-4365197f7d0c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11782);
        internalCounters.push_back(11962);
        internalCounters.push_back(12142);
        internalCounters.push_back(12322);
        internalCounters.push_back(12502);
        internalCounters.push_back(12682);
        internalCounters.push_back(12862);
        internalCounters.push_back(13042);
        internalCounters.push_back(13222);
        internalCounters.push_back(13402);
        internalCounters.push_back(13582);
        internalCounters.push_back(13762);
        internalCounters.push_back(13942);
        internalCounters.push_back(14122);
        internalCounters.push_back(14302);
        internalCounters.push_back(14482);

        p.DefinePublicCounter("CSMemUnitStalledCycles", "ComputeShader", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ENGINES,/", "51991c84-ed2b-bf31-c4ab-8f8e9eb8f29f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7855);
        internalCounters.push_back(8047);
        internalCounters.push_back(8239);
        internalCounters.push_back(8431);
        internalCounters.push_back(8623);
        internalCounters.push_back(8815);
        internalCounters.push_back(9007);
        internalCounters.push_back(9199);
        internalCounters.push_back(9391);
        internalCounters.push_back(9583);
        internalCounters.push_back(9775);
        internalCounters.push_back(9967);
        internalCounters.push_back(10159);
        internalCounters.push_back(10351);
        internalCounters.push_back(10543);
        internalCounters.push_back(10735);

        p.DefinePublicCounter("CSWriteUnitStalledCycles", "ComputeShader", "Number of GPU cycles the write unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "be164c60-5e48-acac-9622-29616d09aa9a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5555);
        internalCounters.push_back(5524);

        p.DefinePublicCounter("CSGDSInsts", "ComputeShader", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "2a867f3e-4a37-ad16-55d1-f03d74707819" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5554);
        internalCounters.push_back(5552);
        internalCounters.push_back(5524);

        p.DefinePublicCounter("CSLDSInsts", "ComputeShader", "The average number of LDS read/write instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,-,2,/,2,ifnotzero", "61b0b351-7e06-ef8e-a8e0-7a9e3200a836" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5553);
        internalCounters.push_back(5524);

        p.DefinePublicCounter("CSFlatLDSInsts", "ComputeShader", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "99672cda-de2b-014c-482e-cf73b90068d5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3488);
        internalCounters.push_back(3431);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("CSALUStalledByLDS", "ComputeShader", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,/,2,/,NUM_SHADER_ENGINES,/,(100),*,1,ifnotzero", "6dc4f1c2-bad0-c9ff-156e-883b319a752a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3488);

        p.DefinePublicCounter("CSALUStalledByLDSCycles", "ComputeShader", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_SHADER_ENGINES,/", "8f3d5f25-2159-0374-fafe-e26a7799b6c8" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5617);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("CSLDSBankConflict", "ComputeShader", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*", "1065ee10-2e41-ea41-1eb3-b61b491752f4" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5617);

        p.DefinePublicCounter("CSLDSBankConflictCycles", "ComputeShader", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_SIMDS,/", "1fd1adf3-c51e-94fd-083e-c482a0a0809e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5868);
        internalCounters.push_back(5987);
        internalCounters.push_back(6106);
        internalCounters.push_back(6225);
        internalCounters.push_back(6344);
        internalCounters.push_back(6463);
        internalCounters.push_back(6582);
        internalCounters.push_back(6701);
        internalCounters.push_back(6820);
        internalCounters.push_back(6939);
        internalCounters.push_back(7058);
        internalCounters.push_back(7177);
        internalCounters.push_back(7296);
        internalCounters.push_back(7415);
        internalCounters.push_back(7534);
        internalCounters.push_back(7653);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("TexUnitBusy", "Timing", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "36afb8d9-42fc-aafe-66c5-449542153b2c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5868);
        internalCounters.push_back(5987);
        internalCounters.push_back(6106);
        internalCounters.push_back(6225);
        internalCounters.push_back(6344);
        internalCounters.push_back(6463);
        internalCounters.push_back(6582);
        internalCounters.push_back(6701);
        internalCounters.push_back(6820);
        internalCounters.push_back(6939);
        internalCounters.push_back(7058);
        internalCounters.push_back(7177);
        internalCounters.push_back(7296);
        internalCounters.push_back(7415);
        internalCounters.push_back(7534);
        internalCounters.push_back(7653);

        p.DefinePublicCounter("TexUnitBusyCycles", "Timing", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ENGINES,/", "c68761f2-248c-4f39-6528-c308b1c0807c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5922);
        internalCounters.push_back(6041);
        internalCounters.push_back(6160);
        internalCounters.push_back(6279);
        internalCounters.push_back(6398);
        internalCounters.push_back(6517);
        internalCounters.push_back(6636);
        internalCounters.push_back(6755);
        internalCounters.push_back(6874);
        internalCounters.push_back(6993);
        internalCounters.push_back(7112);
        internalCounters.push_back(7231);
        internalCounters.push_back(7350);
        internalCounters.push_back(7469);
        internalCounters.push_back(7588);
        internalCounters.push_back(7707);
        internalCounters.push_back(5921);
        internalCounters.push_back(6040);
        internalCounters.push_back(6159);
        internalCounters.push_back(6278);
        internalCounters.push_back(6397);
        internalCounters.push_back(6516);
        internalCounters.push_back(6635);
        internalCounters.push_back(6754);
        internalCounters.push_back(6873);
        internalCounters.push_back(6992);
        internalCounters.push_back(7111);
        internalCounters.push_back(7230);
        internalCounters.push_back(7349);
        internalCounters.push_back(7468);
        internalCounters.push_back(7587);
        internalCounters.push_back(7706);

        p.DefinePublicCounter("TexTriFilteringPct", "TextureUnit", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,+,/,(100),*", "1affc3c8-b917-5c81-622b-7004527208ae" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5922);
        internalCounters.push_back(6041);
        internalCounters.push_back(6160);
        internalCounters.push_back(6279);
        internalCounters.push_back(6398);
        internalCounters.push_back(6517);
        internalCounters.push_back(6636);
        internalCounters.push_back(6755);
        internalCounters.push_back(6874);
        internalCounters.push_back(6993);
        internalCounters.push_back(7112);
        internalCounters.push_back(7231);
        internalCounters.push_back(7350);
        internalCounters.push_back(7469);
        internalCounters.push_back(7588);
        internalCounters.push_back(7707);

        p.DefinePublicCounter("TexTriFilteringCount", "TextureUnit", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "5785b3a1-a513-18db-4b1c-bdeef75bb2b6" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5921);
        internalCounters.push_back(6040);
        internalCounters.push_back(6159);
        internalCounters.push_back(6278);
        internalCounters.push_back(6397);
        internalCounters.push_back(6516);
        internalCounters.push_back(6635);
        internalCounters.push_back(6754);
        internalCounters.push_back(6873);
        internalCounters.push_back(6992);
        internalCounters.push_back(7111);
        internalCounters.push_back(7230);
        internalCounters.push_back(7349);
        internalCounters.push_back(7468);
        internalCounters.push_back(7587);
        internalCounters.push_back(7706);

        p.DefinePublicCounter("NoTexTriFilteringCount", "TextureUnit", "Count of pixels that did not receive trilinear filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "179da29a-81af-c06e-ce8c-a0a731ea030d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5924);
        internalCounters.push_back(6043);
        internalCounters.push_back(6162);
        internalCounters.push_back(6281);
        internalCounters.push_back(6400);
        internalCounters.push_back(6519);
        internalCounters.push_back(6638);
        internalCounters.push_back(6757);
        internalCounters.push_back(6876);
        internalCounters.push_back(6995);
        internalCounters.push_back(7114);
        internalCounters.push_back(7233);
        internalCounters.push_back(7352);
        internalCounters.push_back(7471);
        internalCounters.push_back(7590);
        internalCounters.push_back(7709);
        internalCounters.push_back(5923);
        internalCounters.push_back(6042);
        internalCounters.push_back(6161);
        internalCounters.push_back(6280);
        internalCounters.push_back(6399);
        internalCounters.push_back(6518);
        internalCounters.push_back(6637);
        internalCounters.push_back(6756);
        internalCounters.push_back(6875);
        internalCounters.push_back(6994);
        internalCounters.push_back(7113);
        internalCounters.push_back(7232);
        internalCounters.push_back(7351);
        internalCounters.push_back(7470);
        internalCounters.push_back(7589);
        internalCounters.push_back(7708);

        p.DefinePublicCounter("TexVolFilteringPct", "TextureUnit", "Percentage of pixels that received volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,+,/,(100),*", "b5ff6bed-3178-aee4-42dd-c74391c02a2d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5924);
        internalCounters.push_back(6043);
        internalCounters.push_back(6162);
        internalCounters.push_back(6281);
        internalCounters.push_back(6400);
        internalCounters.push_back(6519);
        internalCounters.push_back(6638);
        internalCounters.push_back(6757);
        internalCounters.push_back(6876);
        internalCounters.push_back(6995);
        internalCounters.push_back(7114);
        internalCounters.push_back(7233);
        internalCounters.push_back(7352);
        internalCounters.push_back(7471);
        internalCounters.push_back(7590);
        internalCounters.push_back(7709);

        p.DefinePublicCounter("TexVolFilteringCount", "TextureUnit", "Count of pixels that received volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "4bddc587-d589-8128-e18c-762eab2c871f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5923);
        internalCounters.push_back(6042);
        internalCounters.push_back(6161);
        internalCounters.push_back(6280);
        internalCounters.push_back(6399);
        internalCounters.push_back(6518);
        internalCounters.push_back(6637);
        internalCounters.push_back(6756);
        internalCounters.push_back(6875);
        internalCounters.push_back(6994);
        internalCounters.push_back(7113);
        internalCounters.push_back(7232);
        internalCounters.push_back(7351);
        internalCounters.push_back(7470);
        internalCounters.push_back(7589);
        internalCounters.push_back(7708);

        p.DefinePublicCounter("NoTexVolFilteringCount", "TextureUnit", "Count of pixels that did not receive volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "9fe1a854-17c6-9d26-b2b9-80610cd5827d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5942);
        internalCounters.push_back(6061);
        internalCounters.push_back(6180);
        internalCounters.push_back(6299);
        internalCounters.push_back(6418);
        internalCounters.push_back(6537);
        internalCounters.push_back(6656);
        internalCounters.push_back(6775);
        internalCounters.push_back(6894);
        internalCounters.push_back(7013);
        internalCounters.push_back(7132);
        internalCounters.push_back(7251);
        internalCounters.push_back(7370);
        internalCounters.push_back(7489);
        internalCounters.push_back(7608);
        internalCounters.push_back(7727);
        internalCounters.push_back(5943);
        internalCounters.push_back(6062);
        internalCounters.push_back(6181);
        internalCounters.push_back(6300);
        internalCounters.push_back(6419);
        internalCounters.push_back(6538);
        internalCounters.push_back(6657);
        internalCounters.push_back(6776);
        internalCounters.push_back(6895);
        internalCounters.push_back(7014);
        internalCounters.push_back(7133);
        internalCounters.push_back(7252);
        internalCounters.push_back(7371);
        internalCounters.push_back(7490);
        internalCounters.push_back(7609);
        internalCounters.push_back(7728);
        internalCounters.push_back(5944);
        internalCounters.push_back(6063);
        internalCounters.push_back(6182);
        internalCounters.push_back(6301);
        internalCounters.push_back(6420);
        internalCounters.push_back(6539);
        internalCounters.push_back(6658);
        internalCounters.push_back(6777);
        internalCounters.push_back(6896);
        internalCounters.push_back(7015);
        internalCounters.push_back(7134);
        internalCounters.push_back(7253);
        internalCounters.push_back(7372);
        internalCounters.push_back(7491);
        internalCounters.push_back(7610);
        internalCounters.push_back(7729);
        internalCounters.push_back(5945);
        internalCounters.push_back(6064);
        internalCounters.push_back(6183);
        internalCounters.push_back(6302);
        internalCounters.push_back(6421);
        internalCounters.push_back(6540);
        internalCounters.push_back(6659);
        internalCounters.push_back(6778);
        internalCounters.push_back(6897);
        internalCounters.push_back(7016);
        internalCounters.push_back(7135);
        internalCounters.push_back(7254);
        internalCounters.push_back(7373);
        internalCounters.push_back(7492);
        internalCounters.push_back(7611);
        internalCounters.push_back(7730);
        internalCounters.push_back(5946);
        internalCounters.push_back(6065);
        internalCounters.push_back(6184);
        internalCounters.push_back(6303);
        internalCounters.push_back(6422);
        internalCounters.push_back(6541);
        internalCounters.push_back(6660);
        internalCounters.push_back(6779);
        internalCounters.push_back(6898);
        internalCounters.push_back(7017);
        internalCounters.push_back(7136);
        internalCounters.push_back(7255);
        internalCounters.push_back(7374);
        internalCounters.push_back(7493);
        internalCounters.push_back(7612);
        internalCounters.push_back(7731);
        internalCounters.push_back(5947);
        internalCounters.push_back(6066);
        internalCounters.push_back(6185);
        internalCounters.push_back(6304);
        internalCounters.push_back(6423);
        internalCounters.push_back(6542);
        internalCounters.push_back(6661);
        internalCounters.push_back(6780);
        internalCounters.push_back(6899);
        internalCounters.push_back(7018);
        internalCounters.push_back(7137);
        internalCounters.push_back(7256);
        internalCounters.push_back(7375);
        internalCounters.push_back(7494);
        internalCounters.push_back(7613);
        internalCounters.push_back(7732);
        internalCounters.push_back(5948);
        internalCounters.push_back(6067);
        internalCounters.push_back(6186);
        internalCounters.push_back(6305);
        internalCounters.push_back(6424);
        internalCounters.push_back(6543);
        internalCounters.push_back(6662);
        internalCounters.push_back(6781);
        internalCounters.push_back(6900);
        internalCounters.push_back(7019);
        internalCounters.push_back(7138);
        internalCounters.push_back(7257);
        internalCounters.push_back(7376);
        internalCounters.push_back(7495);
        internalCounters.push_back(7614);
        internalCounters.push_back(7733);
        internalCounters.push_back(5949);
        internalCounters.push_back(6068);
        internalCounters.push_back(6187);
        internalCounters.push_back(6306);
        internalCounters.push_back(6425);
        internalCounters.push_back(6544);
        internalCounters.push_back(6663);
        internalCounters.push_back(6782);
        internalCounters.push_back(6901);
        internalCounters.push_back(7020);
        internalCounters.push_back(7139);
        internalCounters.push_back(7258);
        internalCounters.push_back(7377);
        internalCounters.push_back(7496);
        internalCounters.push_back(7615);
        internalCounters.push_back(7734);
        internalCounters.push_back(5950);
        internalCounters.push_back(6069);
        internalCounters.push_back(6188);
        internalCounters.push_back(6307);
        internalCounters.push_back(6426);
        internalCounters.push_back(6545);
        internalCounters.push_back(6664);
        internalCounters.push_back(6783);
        internalCounters.push_back(6902);
        internalCounters.push_back(7021);
        internalCounters.push_back(7140);
        internalCounters.push_back(7259);
        internalCounters.push_back(7378);
        internalCounters.push_back(7497);
        internalCounters.push_back(7616);
        internalCounters.push_back(7735);

        p.DefinePublicCounter("TexAveAnisotropy", "TextureUnit", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(2),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,*,+,(4),32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,*,+,(6),48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,*,+,(8),64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,*,+,(10),80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,*,+,(12),96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,*,+,(14),112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,*,+,(16),128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,*,+,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,+,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,+,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,+,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,+,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,+,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,+,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,+,/", "7ca2a2b9-a4eb-ce23-d163-59147e672396" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1747);
        internalCounters.push_back(2004);
        internalCounters.push_back(2261);
        internalCounters.push_back(2518);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("DepthStencilTestBusy", "Timing", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "6834fb52-42e8-bb50-fd48-ec2f2904e7e0" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1747);
        internalCounters.push_back(2004);
        internalCounters.push_back(2261);
        internalCounters.push_back(2518);

        p.DefinePublicCounter("DepthStencilTestBusyCount", "Timing", "Number of GPU cycles spent performing depth and stencil tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "e02860fa-c7bd-90ea-2149-69b4e98a636c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1618);
        internalCounters.push_back(1875);
        internalCounters.push_back(2132);
        internalCounters.push_back(2389);
        internalCounters.push_back(1607);
        internalCounters.push_back(1864);
        internalCounters.push_back(2121);
        internalCounters.push_back(2378);

        p.DefinePublicCounter("HiZTilesAccepted", "DepthAndStencil", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*", "56176f45-d7ff-813d-4f05-3b2f046067e7" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1607);
        internalCounters.push_back(1864);
        internalCounters.push_back(2121);
        internalCounters.push_back(2378);

        p.DefinePublicCounter("HiZTilesAcceptedCount", "DepthAndStencil", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "95d4e3f6-b2f0-f26e-8423-aacdfaf79ea3" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1618);
        internalCounters.push_back(1875);
        internalCounters.push_back(2132);
        internalCounters.push_back(2389);

        p.DefinePublicCounter("HiZTilesRejectedCount", "DepthAndStencil", "Count of tiles not accepted by HiZ.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "156ba142-7eeb-aa6e-a00a-f8aea4e41e0b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1607);
        internalCounters.push_back(1864);
        internalCounters.push_back(2121);
        internalCounters.push_back(2378);
        internalCounters.push_back(1631);
        internalCounters.push_back(1888);
        internalCounters.push_back(2145);
        internalCounters.push_back(2402);

        p.DefinePublicCounter("PreZTilesDetailCulled", "DepthAndStencil", "Percentage of tiles rejected because the associated prim had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "4,5,6,7,sum4,0,1,2,3,sum4,/,(100),*", "cad7f54d-a044-7574-c472-6f2065cbeeac" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1631);
        internalCounters.push_back(1888);
        internalCounters.push_back(2145);
        internalCounters.push_back(2402);

        p.DefinePublicCounter("PreZTilesDetailCulledCount", "DepthAndStencil", "Count of tiles rejected because the associated primitive had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "49262c8a-b1e6-90dd-f096-0fc4921715e9" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1607);
        internalCounters.push_back(1864);
        internalCounters.push_back(2121);
        internalCounters.push_back(2378);

        p.DefinePublicCounter("PreZTilesDetailSurvivingCount", "DepthAndStencil", "Count of tiles surviving because the associated primitive had contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "f803eaa4-bbed-bd39-775f-a64df92e2c08" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2996);
        internalCounters.push_back(2997);
        internalCounters.push_back(2998);
        internalCounters.push_back(2999);
        internalCounters.push_back(3072);
        internalCounters.push_back(3073);
        internalCounters.push_back(3074);
        internalCounters.push_back(3075);

        p.DefinePublicCounter("HiZQuadsCulled", "DepthAndStencil", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-,0,1,+,2,+,3,+,/,(100),*", "fa0e319b-5573-6d34-5bab-904769925036" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3072);
        internalCounters.push_back(3073);
        internalCounters.push_back(3074);
        internalCounters.push_back(3075);

        p.DefinePublicCounter("HiZQuadsCulledCount", "DepthAndStencil", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+", "73b0b39d-6df2-3e24-0b5c-7cb0ac8b6f39" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2996);
        internalCounters.push_back(2997);
        internalCounters.push_back(2998);
        internalCounters.push_back(2999);
        internalCounters.push_back(3072);
        internalCounters.push_back(3073);
        internalCounters.push_back(3074);
        internalCounters.push_back(3075);

        p.DefinePublicCounter("HiZQuadsSurvivingCount", "DepthAndStencil", "Count of quads that survive in the pipeline after HiZ.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+,4,-,5,-,6,-,7,-", "5a2cd556-acb9-c81e-92bc-7ceef6012b42" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2996);
        internalCounters.push_back(2997);
        internalCounters.push_back(2998);
        internalCounters.push_back(2999);
        internalCounters.push_back(3096);
        internalCounters.push_back(3072);
        internalCounters.push_back(3073);
        internalCounters.push_back(3074);
        internalCounters.push_back(3075);

        p.DefinePublicCounter("PreZQuadsCulled", "DepthAndStencil", "Percentage of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "5,6,+,7,+,8,+,4,-,0,1,+,2,+,3,+,/,(100),*", "4e77547b-ec55-5663-f034-af59be66d77d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3096);
        internalCounters.push_back(3072);
        internalCounters.push_back(3073);
        internalCounters.push_back(3074);
        internalCounters.push_back(3075);

        p.DefinePublicCounter("PreZQuadsCulledCount", "DepthAndStencil", "Count of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+,4,+", "1bf169e6-9304-834e-df5f-0c44d7890a08" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2996);
        internalCounters.push_back(2997);
        internalCounters.push_back(2998);
        internalCounters.push_back(2999);
        internalCounters.push_back(3096);
        internalCounters.push_back(3072);
        internalCounters.push_back(3073);
        internalCounters.push_back(3074);
        internalCounters.push_back(3075);

        p.DefinePublicCounter("PreZQuadsSurvivingCount", "DepthAndStencil", "Count of quads surviving detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+,4,-,5,-,6,-,7,-,8,-,(0),max", "50e25e51-3713-89cb-7f92-559cde5e5532" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3096);
        internalCounters.push_back(2996);
        internalCounters.push_back(2997);
        internalCounters.push_back(2998);
        internalCounters.push_back(2999);

        p.DefinePublicCounter("PostZQuads", "DepthAndStencil", "Percentage of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,+,3,+,4,+,/,(100),*", "58f0d34b-eeb8-e8db-abce-cb72584144be" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3096);

        p.DefinePublicCounter("PostZQuadCount", "DepthAndStencil", "Count of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "08404526-ce35-939b-34c8-a7a35a0ff4d6" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1780);
        internalCounters.push_back(2037);
        internalCounters.push_back(2294);
        internalCounters.push_back(2551);

        p.DefinePublicCounter("PreZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z before shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "3bfe6c4d-7422-ca03-7ea5-e67ff1a00136" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1782);
        internalCounters.push_back(2039);
        internalCounters.push_back(2296);
        internalCounters.push_back(2553);

        p.DefinePublicCounter("PreZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z before shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "df7f705e-5162-d3b5-da8b-63466cf9c4e5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1781);
        internalCounters.push_back(2038);
        internalCounters.push_back(2295);
        internalCounters.push_back(2552);

        p.DefinePublicCounter("PreZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z before shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "4484e950-f7a4-3800-bc74-78dd297f017e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1777);
        internalCounters.push_back(2034);
        internalCounters.push_back(2291);
        internalCounters.push_back(2548);

        p.DefinePublicCounter("PostZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z after shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "4995d5d6-2330-b986-508b-fae24856f44c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1779);
        internalCounters.push_back(2036);
        internalCounters.push_back(2293);
        internalCounters.push_back(2550);

        p.DefinePublicCounter("PostZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z after shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "ae558af4-f4be-3dd4-7316-b2c4dcf0def8" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1778);
        internalCounters.push_back(2035);
        internalCounters.push_back(2292);
        internalCounters.push_back(2549);

        p.DefinePublicCounter("PostZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z after shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "b3684c94-814a-c695-c85d-a5b6ab798b35" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1649);
        internalCounters.push_back(1906);
        internalCounters.push_back(2163);
        internalCounters.push_back(2420);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("ZUnitStalled", "DepthAndStencil", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "5e86c3ad-1726-3157-1d01-7ed188bf854d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1649);
        internalCounters.push_back(1906);
        internalCounters.push_back(2163);
        internalCounters.push_back(2420);

        p.DefinePublicCounter("ZUnitStalledCycles", "DepthAndStencil", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "4351fa7f-6737-2c3e-3ffb-b3addbdceedd" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1651);
        internalCounters.push_back(1908);
        internalCounters.push_back(2165);
        internalCounters.push_back(2422);
        internalCounters.push_back(1658);
        internalCounters.push_back(1915);
        internalCounters.push_back(2172);
        internalCounters.push_back(2429);

        p.DefinePublicCounter("DBMemRead", "DepthAndStencil", "Number of bytes read from the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,sum4,(256),*,4,5,6,7,sum4,(32),*,+", "dcdb4ee7-bd50-00f7-c028-9e5f4ce888c0" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1663);
        internalCounters.push_back(1920);
        internalCounters.push_back(2177);
        internalCounters.push_back(2434);
        internalCounters.push_back(1666);
        internalCounters.push_back(1923);
        internalCounters.push_back(2180);
        internalCounters.push_back(2437);

        p.DefinePublicCounter("DBMemWritten", "DepthAndStencil", "Number of bytes written to the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,sum4,(32),*,4,5,6,7,sum4,(32),*,+", "de5717f8-8a49-ee44-4645-10de51b37dcf" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(128);
        internalCounters.push_back(524);
        internalCounters.push_back(920);
        internalCounters.push_back(1316);

        p.DefinePublicCounter("CBMemRead", "ColorBuffer", "Number of bytes read from the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,sum4,(32),*", "84b531d8-a1f8-7f49-7c27-7bc97801f1e6" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(259);
        internalCounters.push_back(655);
        internalCounters.push_back(1051);
        internalCounters.push_back(1447);
        internalCounters.push_back(126);
        internalCounters.push_back(522);
        internalCounters.push_back(918);
        internalCounters.push_back(1314);
        internalCounters.push_back(127);
        internalCounters.push_back(523);
        internalCounters.push_back(919);
        internalCounters.push_back(1315);
        internalCounters.push_back(128);
        internalCounters.push_back(524);
        internalCounters.push_back(920);
        internalCounters.push_back(1316);

        p.DefinePublicCounter("CBColorAndMaskRead", "ColorBuffer", "Total number of bytes read from the color and mask buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "da41660e-eb6f-32ec-8a64-b32ca17bd7eb" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(118);
        internalCounters.push_back(514);
        internalCounters.push_back(910);
        internalCounters.push_back(1306);

        p.DefinePublicCounter("CBMemWritten", "ColorBuffer", "Number of bytes written to the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,sum4,(32),*", "550f8ff8-60b6-a6bf-87d0-25ac9e87de70" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(257);
        internalCounters.push_back(653);
        internalCounters.push_back(1049);
        internalCounters.push_back(1445);
        internalCounters.push_back(116);
        internalCounters.push_back(512);
        internalCounters.push_back(908);
        internalCounters.push_back(1304);
        internalCounters.push_back(117);
        internalCounters.push_back(513);
        internalCounters.push_back(909);
        internalCounters.push_back(1305);
        internalCounters.push_back(118);
        internalCounters.push_back(514);
        internalCounters.push_back(910);
        internalCounters.push_back(1306);

        p.DefinePublicCounter("CBColorAndMaskWritten", "ColorBuffer", "Total number of bytes written to the color and mask buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "29a04b69-8f5f-b770-a0f2-3453e2c99e49" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(162);
        internalCounters.push_back(558);
        internalCounters.push_back(954);
        internalCounters.push_back(1350);
        internalCounters.push_back(7);
        internalCounters.push_back(403);
        internalCounters.push_back(799);
        internalCounters.push_back(1195);

        p.DefinePublicCounter("CBSlowPixelPct", "ColorBuffer", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*,(100),min", "5775943f-0313-7e52-9638-b24a449197bc" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(162);
        internalCounters.push_back(558);
        internalCounters.push_back(954);
        internalCounters.push_back(1350);

        p.DefinePublicCounter("CBSlowPixelCount", "ColorBuffer", "Number of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "47eacbb0-28c8-22b4-5c69-c00d5813bb1c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7862);
        internalCounters.push_back(8054);
        internalCounters.push_back(8246);
        internalCounters.push_back(8438);
        internalCounters.push_back(8630);
        internalCounters.push_back(8822);
        internalCounters.push_back(9014);
        internalCounters.push_back(9206);
        internalCounters.push_back(9398);
        internalCounters.push_back(9590);
        internalCounters.push_back(9782);
        internalCounters.push_back(9974);
        internalCounters.push_back(10166);
        internalCounters.push_back(10358);
        internalCounters.push_back(10550);
        internalCounters.push_back(10742);

        p.DefinePublicCounter("FetchSize", "GlobalMemory", "The total bytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "664bb3ef-6eca-86b1-1e2d-30cb897b5fa9" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7853);
        internalCounters.push_back(8045);
        internalCounters.push_back(8237);
        internalCounters.push_back(8429);
        internalCounters.push_back(8621);
        internalCounters.push_back(8813);
        internalCounters.push_back(9005);
        internalCounters.push_back(9197);
        internalCounters.push_back(9389);
        internalCounters.push_back(9581);
        internalCounters.push_back(9773);
        internalCounters.push_back(9965);
        internalCounters.push_back(10157);
        internalCounters.push_back(10349);
        internalCounters.push_back(10541);
        internalCounters.push_back(10733);

        p.DefinePublicCounter("WriteSize", "GlobalMemory", "The total bytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "f96f2c16-b1b4-4ec4-229c-fc82e6f80a82" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7845);
        internalCounters.push_back(8037);
        internalCounters.push_back(8229);
        internalCounters.push_back(8421);
        internalCounters.push_back(8613);
        internalCounters.push_back(8805);
        internalCounters.push_back(8997);
        internalCounters.push_back(9189);
        internalCounters.push_back(9381);
        internalCounters.push_back(9573);
        internalCounters.push_back(9765);
        internalCounters.push_back(9957);
        internalCounters.push_back(10149);
        internalCounters.push_back(10341);
        internalCounters.push_back(10533);
        internalCounters.push_back(10725);
        internalCounters.push_back(7846);
        internalCounters.push_back(8038);
        internalCounters.push_back(8230);
        internalCounters.push_back(8422);
        internalCounters.push_back(8614);
        internalCounters.push_back(8806);
        internalCounters.push_back(8998);
        internalCounters.push_back(9190);
        internalCounters.push_back(9382);
        internalCounters.push_back(9574);
        internalCounters.push_back(9766);
        internalCounters.push_back(9958);
        internalCounters.push_back(10150);
        internalCounters.push_back(10342);
        internalCounters.push_back(10534);
        internalCounters.push_back(10726);

        p.DefinePublicCounter("CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "dfbeebab-f7c1-1211-e502-4aae361e2ad7" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7845);
        internalCounters.push_back(8037);
        internalCounters.push_back(8229);
        internalCounters.push_back(8421);
        internalCounters.push_back(8613);
        internalCounters.push_back(8805);
        internalCounters.push_back(8997);
        internalCounters.push_back(9189);
        internalCounters.push_back(9381);
        internalCounters.push_back(9573);
        internalCounters.push_back(9765);
        internalCounters.push_back(9957);
        internalCounters.push_back(10149);
        internalCounters.push_back(10341);
        internalCounters.push_back(10533);
        internalCounters.push_back(10725);
        internalCounters.push_back(7846);
        internalCounters.push_back(8038);
        internalCounters.push_back(8230);
        internalCounters.push_back(8422);
        internalCounters.push_back(8614);
        internalCounters.push_back(8806);
        internalCounters.push_back(8998);
        internalCounters.push_back(9190);
        internalCounters.push_back(9382);
        internalCounters.push_back(9574);
        internalCounters.push_back(9766);
        internalCounters.push_back(9958);
        internalCounters.push_back(10150);
        internalCounters.push_back(10342);
        internalCounters.push_back(10534);
        internalCounters.push_back(10726);

        p.DefinePublicCounter("CacheMiss", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that miss the data cache. Value range: 0% (optimal) to 100% (all miss).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "aebc0a53-7f87-60bd-4c4b-2b956846ef83" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7845);
        internalCounters.push_back(8037);
        internalCounters.push_back(8229);
        internalCounters.push_back(8421);
        internalCounters.push_back(8613);
        internalCounters.push_back(8805);
        internalCounters.push_back(8997);
        internalCounters.push_back(9189);
        internalCounters.push_back(9381);
        internalCounters.push_back(9573);
        internalCounters.push_back(9765);
        internalCounters.push_back(9957);
        internalCounters.push_back(10149);
        internalCounters.push_back(10341);
        internalCounters.push_back(10533);
        internalCounters.push_back(10725);

        p.DefinePublicCounter("CacheHitCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that hit the data cache.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "43437652-1024-9737-2eb0-0899c0c1feae" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7846);
        internalCounters.push_back(8038);
        internalCounters.push_back(8230);
        internalCounters.push_back(8422);
        internalCounters.push_back(8614);
        internalCounters.push_back(8806);
        internalCounters.push_back(8998);
        internalCounters.push_back(9190);
        internalCounters.push_back(9382);
        internalCounters.push_back(9574);
        internalCounters.push_back(9766);
        internalCounters.push_back(9958);
        internalCounters.push_back(10150);
        internalCounters.push_back(10342);
        internalCounters.push_back(10534);
        internalCounters.push_back(10726);

        p.DefinePublicCounter("CacheMissCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that miss the data cache.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "d0f8a812-f41b-644f-09d1-14ee03ea3671" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5868);
        internalCounters.push_back(5987);
        internalCounters.push_back(6106);
        internalCounters.push_back(6225);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,max4,4,/,NUM_SHADER_ENGINES,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11782);
        internalCounters.push_back(11962);
        internalCounters.push_back(12142);
        internalCounters.push_back(12322);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,max4,4,/,NUM_SHADER_ENGINES,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7855);
        internalCounters.push_back(8047);
        internalCounters.push_back(8239);
        internalCounters.push_back(8431);
        internalCounters.push_back(8623);
        internalCounters.push_back(8815);
        internalCounters.push_back(9007);
        internalCounters.push_back(9199);
        internalCounters.push_back(9391);
        internalCounters.push_back(9583);
        internalCounters.push_back(9775);
        internalCounters.push_back(9967);
        internalCounters.push_back(10159);
        internalCounters.push_back(10351);
        internalCounters.push_back(10543);
        internalCounters.push_back(10735);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72" );
    }
}

