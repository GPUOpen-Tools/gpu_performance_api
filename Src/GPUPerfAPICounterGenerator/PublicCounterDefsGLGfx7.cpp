//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for GLGFX7
//==============================================================================

#include "GPAInternalCounter.h"
#include "PublicCounterDefsGLGfx7.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersGLGfx7(GPA_DerivedCounters& c)
{
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11279);

        c.DefineDerivedCounter("GPUTime", "Timing", "Time this API command took to execute on the GPU in nanoseconds from the time the previous command reached the bottom of the pipeline (BOP) to the time this command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "0,TS_FREQ,/,(1000000000),*", "cbd338f2-de6c-7b14-92ad-ba724ca2e501");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1951);
        internalCounters.push_back(1949);

        c.DefineDerivedCounter("GPUBusy", "Timing", "The percentage of time GPU was busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,(100),*,(100),min", "bef38bf3-1167-0844-81f0-67d2d28ddbc5");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("GPUBusyCycles", "Timing", "Number of GPU cycles that the GPU was busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0", "1e84970d-7014-2b8d-d61e-388b5f782691");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11118);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("TessellatorBusy", "Timing", "The percentage of time the tessellation engine is busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*", "36af6c72-dcfb-8102-4fd4-ce8ddc573365");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11118);

        c.DefineDerivedCounter("TessellatorBusyCycles", "Timing", "Number of GPU cycles that the tessellation engine is busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_PRIM_PIPES,/", "60289dcb-7b33-46e7-26d1-8a2121605543");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2547);
        internalCounters.push_back(2572);
        internalCounters.push_back(2594);
        internalCounters.push_back(2616);
        internalCounters.push_back(2556);
        internalCounters.push_back(2578);
        internalCounters.push_back(2600);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("VSBusy", "Timing", "The percentage of time the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,4,ifnotzero,1,5,ifnotzero,2,6,ifnotzero,7,/,(100),*,(100),min", "94caad5e-867c-6c09-cf3a-d05b51df8f3b");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2547);
        internalCounters.push_back(2572);
        internalCounters.push_back(2594);
        internalCounters.push_back(2616);
        internalCounters.push_back(2556);
        internalCounters.push_back(2578);
        internalCounters.push_back(2600);

        c.DefineDerivedCounter("VSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,4,ifnotzero,1,5,ifnotzero,2,6,ifnotzero", "a2086d4e-274b-48a8-3e08-a4ab76ac15dd");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11279);
        internalCounters.push_back(2547);
        internalCounters.push_back(2572);
        internalCounters.push_back(2594);
        internalCounters.push_back(2616);
        internalCounters.push_back(2556);
        internalCounters.push_back(2578);
        internalCounters.push_back(2600);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("VSTime", "Timing", "Time vertex shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,5,ifnotzero,2,6,ifnotzero,3,7,ifnotzero,8,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "d6ce819e-69af-a241-d07a-5dd8d146e436");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2584);
        internalCounters.push_back(2590);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("HSBusy", "Timing", "The percentage of time the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "16f30a0b-4cbf-eccd-b13f-ab68dd254d32");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2584);
        internalCounters.push_back(2590);

        c.DefineDerivedCounter("HSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero", "753e76ef-8ef8-3f13-b511-4bd9f3589fdb");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11279);
        internalCounters.push_back(2584);
        internalCounters.push_back(2590);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("HSTime", "Timing", "Time hull shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "8386a863-dd34-1526-f703-0f0c7b241bc4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2547);
        internalCounters.push_back(2572);
        internalCounters.push_back(2616);
        internalCounters.push_back(2578);
        internalCounters.push_back(2600);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("DSBusy", "Timing", "The percentage of time the ShaderUnit has domain shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,5,/,(100),*,(100),min", "0c626e8a-9b82-b6d4-d9a3-578509316301");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2547);
        internalCounters.push_back(2572);
        internalCounters.push_back(2616);
        internalCounters.push_back(2578);
        internalCounters.push_back(2600);

        c.DefineDerivedCounter("DSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has domain shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero", "2f3f7561-0549-2232-536d-129ffc5f7703");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11279);
        internalCounters.push_back(2547);
        internalCounters.push_back(2572);
        internalCounters.push_back(2616);
        internalCounters.push_back(2578);
        internalCounters.push_back(2600);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("DSTime", "Timing", "Time domain shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,2,4,ifnotzero,5,ifnotzero,6,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "bfe28947-c727-8a9f-aa59-c218e58bfba5");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2563);
        internalCounters.push_back(2566);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("GSBusy", "Timing", "The percentage of time the ShaderUnit has geometry shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "876f36d8-d046-833f-7832-673cbffd0a45");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2563);
        internalCounters.push_back(2566);

        c.DefineDerivedCounter("GSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has geometry shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero", "48203b6b-8983-c067-d63e-05da8be5111b");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11279);
        internalCounters.push_back(2563);
        internalCounters.push_back(2566);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("GSTime", "Timing", "Time geometry shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "c73e715f-59af-76e8-9e22-097b94c066c4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2616);
        internalCounters.push_back(2621);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("PSBusy", "Timing", "The percentage of time the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "7e772beb-d82c-bd9a-aed0-fe504d416ce5");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2616);
        internalCounters.push_back(2621);

        c.DefineDerivedCounter("PSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero", "b58bea04-ce8e-2984-80f4-8aba7d4c817b");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11279);
        internalCounters.push_back(2616);
        internalCounters.push_back(2621);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("PSTime", "Timing", "Time pixel shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "edca7694-7416-e8a6-0c5a-63a5ad5f3d74");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2604);
        internalCounters.push_back(2608);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("CSBusy", "Timing", "The percentage of time the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "493fdd90-8d2b-a055-5e4e-2d29c3396b8c");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2604);
        internalCounters.push_back(2608);

        c.DefineDerivedCounter("CSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero", "39bcf1b8-f6b2-4c37-f9af-0a2bb59512f9");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11279);
        internalCounters.push_back(2604);
        internalCounters.push_back(2608);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("CSTime", "Timing", "Time compute shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "dbc24916-ecb2-7eef-8d63-7afadaaab6bc");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11013);
        internalCounters.push_back(10994);
        internalCounters.push_back(11089);

        c.DefineDerivedCounter("VSVerticesIn", "VertexShader", "The number of vertices processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero", "810a04c8-2ff4-081d-766d-bfa2bd4ad916");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3514);
        internalCounters.push_back(3492);
        internalCounters.push_back(3010);
        internalCounters.push_back(2988);
        internalCounters.push_back(2998);
        internalCounters.push_back(4018);
        internalCounters.push_back(3996);
        internalCounters.push_back(4006);

        c.DefineDerivedCounter("VSVALUInstCount", "VertexShader", "Average number of vector ALU instructions executed in the VS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/,2,3,/,4,ifnotzero,5,6,/,7,ifnotzero", "8ec604e4-63f5-e6b5-4558-c38f0b26d4b1");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3518);
        internalCounters.push_back(3492);
        internalCounters.push_back(3014);
        internalCounters.push_back(2988);
        internalCounters.push_back(2998);
        internalCounters.push_back(4022);
        internalCounters.push_back(3996);
        internalCounters.push_back(4006);

        c.DefineDerivedCounter("VSSALUInstCount", "VertexShader", "Average number of scalar ALU instructions executed in the VS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/,2,3,/,4,ifnotzero,5,6,/,7,ifnotzero", "e3da0383-7322-7f65-8cf2-3ce641578e54");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3569);
        internalCounters.push_back(3065);
        internalCounters.push_back(2998);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("VSVALUBusy", "VertexShader", "The percentage of GPUTime vector ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,ifnotzero,(4),*,NUM_SIMDS,/,3,/,(100),*", "8b3572f7-fda0-eddf-6c93-2ab145b8754b");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3569);
        internalCounters.push_back(3065);
        internalCounters.push_back(2998);

        c.DefineDerivedCounter("VSVALUBusyCycles", "VertexShader", "Number of GPU cycles where vector ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,ifnotzero,(4),*,NUM_SIMDS,/", "0af1686e-6d77-2f6e-2862-7bb8e869a776");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3574);
        internalCounters.push_back(3070);
        internalCounters.push_back(2998);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("VSSALUBusy", "VertexShader", "The percentage of GPUTime scalar ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,ifnotzero,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,3,/,(100),*", "3bc8730c-e3bc-e2f0-7d24-36974064c25a");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3574);
        internalCounters.push_back(3070);
        internalCounters.push_back(2998);

        c.DefineDerivedCounter("VSSALUBusyCycles", "VertexShader", "Number of GPU cycles where scalar ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,ifnotzero,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "357ac7cd-2e1c-dcb0-77f6-37527237f35b");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11098);

        c.DefineDerivedCounter("HSPatches", "HullShader", "The number of patches processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "d1bbd27d-d591-4509-df52-d329fb73a98f");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4270);
        internalCounters.push_back(4248);

        c.DefineDerivedCounter("HSVALUInstCount", "HullShader", "Average number of vector ALU instructions executed in the HS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "786673bf-d58f-9895-3a37-9d6efb5e5804");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4274);
        internalCounters.push_back(4248);

        c.DefineDerivedCounter("HSSALUInstCount", "HullShader", "Average number of scalar ALU instructions executed in the HS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "1af675c4-cb0b-c4c5-c131-2796750f683e");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4325);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("HSVALUBusy", "HullShader", "The percentage of GPUTime vector ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "7880d192-8015-0311-d43e-fb0b7a4df179");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4325);

        c.DefineDerivedCounter("HSVALUBusyCycles", "HullShader", "Number of GPU cycles vector where ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,/", "3afb94e4-e937-5730-0cc9-41d3113ba012");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4330);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("HSSALUBusy", "HullShader", "The percentage of GPUTime scalar ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*", "34748a4b-9148-0b06-b7b9-5700d6631bde");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4330);

        c.DefineDerivedCounter("HSSALUBusyCycles", "HullShader", "Number of GPU cycles where scalar ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "9bceabf7-3f01-2fd9-7b1d-8fe46c729efc");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11013);
        internalCounters.push_back(10994);
        internalCounters.push_back(11089);

        c.DefineDerivedCounter("DSVerticesIn", "DomainShader", "The number of vertices processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,1,ifnotzero,2,ifnotzero", "b88d9d05-2418-e639-4e3d-3a5815855f8d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3514);
        internalCounters.push_back(3492);
        internalCounters.push_back(3010);
        internalCounters.push_back(2988);
        internalCounters.push_back(2998);
        internalCounters.push_back(4006);

        c.DefineDerivedCounter("DSVALUInstCount", "DomainShader", "Average number of vector ALU instructions executed in the DS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,2,3,/,4,ifnotzero,5,ifnotzero", "03a3e949-82f9-be4d-7228-5eb5ad80915a");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3518);
        internalCounters.push_back(3492);
        internalCounters.push_back(3014);
        internalCounters.push_back(2988);
        internalCounters.push_back(2998);
        internalCounters.push_back(4006);

        c.DefineDerivedCounter("DSSALUInstCount", "DomainShader", "Average number of scalar ALU instructions executed in the DS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,2,3,/,4,ifnotzero,5,ifnotzero", "73daa728-483e-95d0-5b40-504719aadc1c");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3569);
        internalCounters.push_back(3065);
        internalCounters.push_back(1951);
        internalCounters.push_back(2998);
        internalCounters.push_back(4006);

        c.DefineDerivedCounter("DSVALUBusy", "DomainShader", "The percentage of GPUTime vector ALU instructions are being processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,(4),*,NUM_SIMDS,/,2,/,(100),*", "ddc0dd0c-0c73-b831-a410-cfea8b9713d9");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3569);
        internalCounters.push_back(3065);
        internalCounters.push_back(2998);
        internalCounters.push_back(4006);

        c.DefineDerivedCounter("DSVALUBusyCycles", "DomainShader", "Number of GPU cycles where vector ALU instructions are being processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,ifnotzero,3,ifnotzero,(4),*,NUM_SIMDS,/", "1e280912-81ee-a684-823b-94c468d8ebda");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3574);
        internalCounters.push_back(3070);
        internalCounters.push_back(1951);
        internalCounters.push_back(2998);
        internalCounters.push_back(4006);

        c.DefineDerivedCounter("DSSALUBusy", "DomainShader", "The percentage of GPUTime scalar ALU instructions are being processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,2,/,(100),*", "b639f64c-24af-348f-6439-43c701b4fc07");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3574);
        internalCounters.push_back(3070);
        internalCounters.push_back(2998);
        internalCounters.push_back(4006);

        c.DefineDerivedCounter("DSSALUBusyCycles", "DomainShader", "Number of GPU cycles where scalar ALU instructions are being processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,ifnotzero,3,ifnotzero,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "b5bf8a0c-e682-1aa6-23d7-c6c6784ffa5c");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11002);

        c.DefineDerivedCounter("GSPrimsIn", "GeometryShader", "The number of primitives passed into the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "20c29866-509a-aaab-2697-6b2c38f79953");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11013);
        internalCounters.push_back(10994);

        c.DefineDerivedCounter("GSVerticesOut", "GeometryShader", "The number of vertices output by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,ifnotzero", "775b9736-319a-bd8a-48c9-68db9c91d978");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3262);
        internalCounters.push_back(3240);

        c.DefineDerivedCounter("GSVALUInstCount", "GeometryShader", "Average number of vector ALU instructions executed in the GS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "21b12bfa-b8cd-2e71-a2d5-f9e9f1d65d61");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3266);
        internalCounters.push_back(3240);

        c.DefineDerivedCounter("GSSALUInstCount", "GeometryShader", "Average number of scalar ALU instructions executed in the GS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "a8562594-d335-ca43-61bf-03b72d2b98a5");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3317);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("GSVALUBusy", "GeometryShader", "The percentage of GPUTime vector ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "228a4818-1e56-cebb-0720-3b2cdc057a6f");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3317);

        c.DefineDerivedCounter("GSVALUBusyCycles", "GeometryShader", "Number of GPU cycles where vector ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,/", "be217edd-226f-bd97-9a48-46e2809b1933");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3322);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("GSSALUBusy", "GeometryShader", "The percentage of GPUTime scalar ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*", "f28ce300-800e-9822-39e4-f48528bdb935");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3322);

        c.DefineDerivedCounter("GSSALUBusyCycles", "GeometryShader", "Number of GPU cycles where scalar ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "b3eace7c-3bc4-0107-887f-923851dc8ea7");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2103);
        internalCounters.push_back(2107);
        internalCounters.push_back(2059);
        internalCounters.push_back(2071);
        internalCounters.push_back(2060);
        internalCounters.push_back(2072);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("PrimitiveAssemblyBusy", "Timing", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max,6,/,(100),*,(100),min", "fe08f347-91cb-01b6-02e4-d79f7cb89a93");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2103);
        internalCounters.push_back(2107);
        internalCounters.push_back(2059);
        internalCounters.push_back(2071);
        internalCounters.push_back(2060);
        internalCounters.push_back(2072);

        c.DefineDerivedCounter("PrimitiveAssemblyBusyCycles", "Timing", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max", "b75bc709-9c04-bf6c-b3f2-511b66e70ed0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2006);

        c.DefineDerivedCounter("PrimitivesIn", "PrimitiveAssembly", "The number of primitives received by the hardware. This includes primitives generated by tessellation.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "a515b80d-75c3-c7d2-0d2f-d7766b4759a6");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2012);
        internalCounters.push_back(2052);
        internalCounters.push_back(2053);
        internalCounters.push_back(2054);
        internalCounters.push_back(2055);

        c.DefineDerivedCounter("CulledPrims", "PrimitiveAssembly", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+,4,+", "589bdf55-9192-280a-41c3-584bc94f2562");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2019);

        c.DefineDerivedCounter("ClippedPrims", "PrimitiveAssembly", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "5ef6f9d5-155e-5baa-163f-8359d9ea9bbf");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2107);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("PAStalledOnRasterizer", "PrimitiveAssembly", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*", "6f9f416b-53c1-0457-f88c-7b6ba8973974");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2107);

        c.DefineDerivedCounter("PAStalledOnRasterizerCycles", "PrimitiveAssembly", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_PRIM_PIPES,/", "7a8c492a-c566-9328-6805-760dbff5c0f2");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4760);
        internalCounters.push_back(4765);
        internalCounters.push_back(4770);
        internalCounters.push_back(4775);

        c.DefineDerivedCounter("PSPixelsOut", "PixelShader", "Pixels exported from shader to color buffers. Does not include killed or alpha tested pixels", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "edd35449-8cba-daa2-06f8-8f0eb2bd42c8");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4762);
        internalCounters.push_back(4767);
        internalCounters.push_back(4772);
        internalCounters.push_back(4777);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("PSExportStalls", "PixelShader", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "d438414c-9ff5-d60a-1468-92040ce387c7");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4762);
        internalCounters.push_back(4767);
        internalCounters.push_back(4772);
        internalCounters.push_back(4777);

        c.DefineDerivedCounter("PSExportStallsCycles", "PixelShader", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "477bf668-a6d3-bd1b-823e-3aff43b2beb4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3766);
        internalCounters.push_back(3744);

        c.DefineDerivedCounter("PSVALUInstCount", "PixelShader", "Average number of vector ALU instructions executed in the PS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "eb74389e-435c-4137-ecf1-39eb5bc1cbfe");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3770);
        internalCounters.push_back(3744);

        c.DefineDerivedCounter("PSSALUInstCount", "PixelShader", "Average number of scalar ALU instructions executed in the PS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "e6a06580-8a82-96d6-976c-acc121fc5516");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3821);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("PSVALUBusy", "PixelShader", "The percentage of GPUTime vector ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "6ce6fef7-8e33-10b4-f351-af755e177e85");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3821);

        c.DefineDerivedCounter("PSVALUBusyCycles", "PixelShader", "Number of GPU cycles where vector ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,/", "1e276f86-cd2a-72e7-fc9d-004f666f2981");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3826);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("PSSALUBusy", "PixelShader", "The percentage of GPUTime scalar ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*", "2ff9f34f-e94b-af4d-18c2-5fbbf6d1727a");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3826);

        c.DefineDerivedCounter("PSSALUBusyCycles", "PixelShader", "Number of GPU cycles where scalar ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "29808906-f128-b078-fc79-820a4b3b3b8d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2605);

        c.DefineDerivedCounter("CSThreadGroups", "ComputeShader", "Total number of thread groups.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "8ce3fc80-56b2-97f9-8e70-2e8c747cea68");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4500);

        c.DefineDerivedCounter("CSWavefronts", "ComputeShader", "The total number of wavefronts used for the CS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "42379c6e-369b-c237-8b25-cdb9cdc65c4d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4510);

        c.DefineDerivedCounter("CSThreads", "ComputeShader", "The number of CS threads processed by the hardware.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "7a648013-6eac-2665-ac36-13c6f4ac9c26");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4522);
        internalCounters.push_back(4500);

        c.DefineDerivedCounter("CSVALUInsts", "ComputeShader", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "376cb1cc-5a40-9d1d-404c-f1736c0c5084");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4585);
        internalCounters.push_back(4577);

        c.DefineDerivedCounter("CSVALUUtilization", "ComputeShader", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,(64),*,/,(100),*,1,ifnotzero,(100),min", "4476879e-cdc0-d602-b24e-9b4a8d38438f");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4526);
        internalCounters.push_back(4500);

        c.DefineDerivedCounter("CSSALUInsts", "ComputeShader", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "eb211144-8136-ff86-e8bf-4d0493a904cb");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4524);
        internalCounters.push_back(4500);

        c.DefineDerivedCounter("CSVFetchInsts", "ComputeShader", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "3e2829c0-6215-783b-c271-6d57ff2c520e");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4527);
        internalCounters.push_back(4500);

        c.DefineDerivedCounter("CSSFetchInsts", "ComputeShader", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "da09171c-6a0a-584f-fddc-dc5062d63a3e");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4523);
        internalCounters.push_back(4500);

        c.DefineDerivedCounter("CSVWriteInsts", "ComputeShader", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "43438c22-e910-b377-b767-b32902e0df0d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4528);
        internalCounters.push_back(4529);
        internalCounters.push_back(4500);

        c.DefineDerivedCounter("CSFlatVMemInsts", "ComputeShader", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,-,2,/,2,ifnotzero", "2570b477-13e3-f5b6-e6ff-7159373bc74d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4577);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("CSVALUBusy", "ComputeShader", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "f1e64815-f6a8-c277-d4f9-d054b443e205");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4577);

        c.DefineDerivedCounter("CSVALUBusyCycles", "ComputeShader", "Number of GPU cycles where vector ALU instructions are processed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,/", "2d0d5852-2658-eb73-68d2-f23f7118c9c3");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4582);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("CSSALUBusy", "ComputeShader", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*", "3fc35f4e-9882-94e3-6f5f-4e81cd97082a");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4582);

        c.DefineDerivedCounter("CSSALUBusyCycles", "ComputeShader", "Number of GPU cycles where scalar ALU instructions are processed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "de58f8fc-8ed4-a799-648d-62ded7b1c4c4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4780);
        internalCounters.push_back(4891);
        internalCounters.push_back(5002);
        internalCounters.push_back(5113);
        internalCounters.push_back(5224);
        internalCounters.push_back(5335);
        internalCounters.push_back(5446);
        internalCounters.push_back(5557);
        internalCounters.push_back(5668);
        internalCounters.push_back(5779);
        internalCounters.push_back(5890);
        internalCounters.push_back(1951);
        internalCounters.push_back(2605);

        c.DefineDerivedCounter("CSMemUnitBusy", "ComputeShader", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,/,NUM_SHADER_ENGINES,/,(100),*,12,ifnotzero", "42ab96e1-0a24-96c8-c4ff-098fa267d78e");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4780);
        internalCounters.push_back(4891);
        internalCounters.push_back(5002);
        internalCounters.push_back(5113);
        internalCounters.push_back(5224);
        internalCounters.push_back(5335);
        internalCounters.push_back(5446);
        internalCounters.push_back(5557);
        internalCounters.push_back(5668);
        internalCounters.push_back(5779);
        internalCounters.push_back(5890);

        c.DefineDerivedCounter("CSMemUnitBusyCycles", "ComputeShader", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,NUM_SHADER_ENGINES,/", "39d5687f-c727-7c0c-af82-bb711d3897ed");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9181);
        internalCounters.push_back(9335);
        internalCounters.push_back(9489);
        internalCounters.push_back(9643);
        internalCounters.push_back(9797);
        internalCounters.push_back(9951);
        internalCounters.push_back(10105);
        internalCounters.push_back(10259);
        internalCounters.push_back(10413);
        internalCounters.push_back(10567);
        internalCounters.push_back(10721);
        internalCounters.push_back(1951);
        internalCounters.push_back(2605);

        c.DefineDerivedCounter("CSMemUnitStalled", "ComputeShader", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,/,NUM_SHADER_ENGINES,/,(100),*,12,ifnotzero", "f18e8679-1511-d533-d9ee-4365197f7d0c");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9181);
        internalCounters.push_back(9335);
        internalCounters.push_back(9489);
        internalCounters.push_back(9643);
        internalCounters.push_back(9797);
        internalCounters.push_back(9951);
        internalCounters.push_back(10105);
        internalCounters.push_back(10259);
        internalCounters.push_back(10413);
        internalCounters.push_back(10567);
        internalCounters.push_back(10721);

        c.DefineDerivedCounter("CSMemUnitStalledCycles", "ComputeShader", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max", "51991c84-ed2b-bf31-c4ab-8f8e9eb8f29f");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6103);
        internalCounters.push_back(6263);
        internalCounters.push_back(6423);
        internalCounters.push_back(6583);
        internalCounters.push_back(6743);
        internalCounters.push_back(6903);
        internalCounters.push_back(7063);
        internalCounters.push_back(7223);
        internalCounters.push_back(7383);
        internalCounters.push_back(7543);
        internalCounters.push_back(7703);
        internalCounters.push_back(7863);
        internalCounters.push_back(8023);
        internalCounters.push_back(8183);
        internalCounters.push_back(8343);
        internalCounters.push_back(8503);
        internalCounters.push_back(2605);

        c.DefineDerivedCounter("CSFetchSize", "ComputeShader", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,(1024),/,16,ifnotzero", "03cdb7e9-2bc3-15c1-811f-2106f3449295");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6097);
        internalCounters.push_back(6257);
        internalCounters.push_back(6417);
        internalCounters.push_back(6577);
        internalCounters.push_back(6737);
        internalCounters.push_back(6897);
        internalCounters.push_back(7057);
        internalCounters.push_back(7217);
        internalCounters.push_back(7377);
        internalCounters.push_back(7537);
        internalCounters.push_back(7697);
        internalCounters.push_back(7857);
        internalCounters.push_back(8017);
        internalCounters.push_back(8177);
        internalCounters.push_back(8337);
        internalCounters.push_back(8497);
        internalCounters.push_back(2605);

        c.DefineDerivedCounter("CSWriteSize", "ComputeShader", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,(1024),/,16,ifnotzero", "3ec1ce55-d621-b7a5-5b8d-2909cf2dbe7d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6089);
        internalCounters.push_back(6249);
        internalCounters.push_back(6409);
        internalCounters.push_back(6569);
        internalCounters.push_back(6729);
        internalCounters.push_back(6889);
        internalCounters.push_back(7049);
        internalCounters.push_back(7209);
        internalCounters.push_back(7369);
        internalCounters.push_back(7529);
        internalCounters.push_back(7689);
        internalCounters.push_back(7849);
        internalCounters.push_back(8009);
        internalCounters.push_back(8169);
        internalCounters.push_back(8329);
        internalCounters.push_back(8489);
        internalCounters.push_back(6090);
        internalCounters.push_back(6250);
        internalCounters.push_back(6410);
        internalCounters.push_back(6570);
        internalCounters.push_back(6730);
        internalCounters.push_back(6890);
        internalCounters.push_back(7050);
        internalCounters.push_back(7210);
        internalCounters.push_back(7370);
        internalCounters.push_back(7530);
        internalCounters.push_back(7690);
        internalCounters.push_back(7850);
        internalCounters.push_back(8010);
        internalCounters.push_back(8170);
        internalCounters.push_back(8330);
        internalCounters.push_back(8490);
        internalCounters.push_back(2605);

        c.DefineDerivedCounter("CSCacheHit", "ComputeShader", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*,32,ifnotzero", "50fdbc38-d099-5957-5f75-dfe5341b2187");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6089);
        internalCounters.push_back(6249);
        internalCounters.push_back(6409);
        internalCounters.push_back(6569);
        internalCounters.push_back(6729);
        internalCounters.push_back(6889);
        internalCounters.push_back(7049);
        internalCounters.push_back(7209);
        internalCounters.push_back(7369);
        internalCounters.push_back(7529);
        internalCounters.push_back(7689);
        internalCounters.push_back(7849);
        internalCounters.push_back(8009);
        internalCounters.push_back(8169);
        internalCounters.push_back(8329);
        internalCounters.push_back(8489);

        c.DefineDerivedCounter("CSCacheHitCount", "ComputeShader", "Count of fetch, write, atomic, and other instructions that hit the data cache.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "bee6ef8f-13fc-1b98-7bb9-c28a357dc3be");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6090);
        internalCounters.push_back(6250);
        internalCounters.push_back(6410);
        internalCounters.push_back(6570);
        internalCounters.push_back(6730);
        internalCounters.push_back(6890);
        internalCounters.push_back(7050);
        internalCounters.push_back(7210);
        internalCounters.push_back(7370);
        internalCounters.push_back(7530);
        internalCounters.push_back(7690);
        internalCounters.push_back(7850);
        internalCounters.push_back(8010);
        internalCounters.push_back(8170);
        internalCounters.push_back(8330);
        internalCounters.push_back(8490);

        c.DefineDerivedCounter("CSCacheMissCount", "ComputeShader", "Count of fetch, write, atomic, and other instructions that miss the data cache.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "c38cd67e-6557-c53b-9fd3-934bf3d7a196");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6098);
        internalCounters.push_back(6258);
        internalCounters.push_back(6418);
        internalCounters.push_back(6578);
        internalCounters.push_back(6738);
        internalCounters.push_back(6898);
        internalCounters.push_back(7058);
        internalCounters.push_back(7218);
        internalCounters.push_back(7378);
        internalCounters.push_back(7538);
        internalCounters.push_back(7698);
        internalCounters.push_back(7858);
        internalCounters.push_back(8018);
        internalCounters.push_back(8178);
        internalCounters.push_back(8338);
        internalCounters.push_back(8498);
        internalCounters.push_back(1951);
        internalCounters.push_back(2605);

        c.DefineDerivedCounter("CSWriteUnitStalled", "ComputeShader", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,ifnotzero", "3e0e1bdc-f66c-eddd-af3d-f8e9e8f45fd8");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6098);
        internalCounters.push_back(6258);
        internalCounters.push_back(6418);
        internalCounters.push_back(6578);
        internalCounters.push_back(6738);
        internalCounters.push_back(6898);
        internalCounters.push_back(7058);
        internalCounters.push_back(7218);
        internalCounters.push_back(7378);
        internalCounters.push_back(7538);
        internalCounters.push_back(7698);
        internalCounters.push_back(7858);
        internalCounters.push_back(8018);
        internalCounters.push_back(8178);
        internalCounters.push_back(8338);
        internalCounters.push_back(8498);

        c.DefineDerivedCounter("CSWriteUnitStalledCycles", "ComputeShader", "Number of GPU cycles the write unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "be164c60-5e48-acac-9622-29616d09aa9a");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4531);
        internalCounters.push_back(4500);

        c.DefineDerivedCounter("CSGDSInsts", "ComputeShader", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "2a867f3e-4a37-ad16-55d1-f03d74707819");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4530);
        internalCounters.push_back(4528);
        internalCounters.push_back(4500);

        c.DefineDerivedCounter("CSLDSInsts", "ComputeShader", "The average number of LDS read/write instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,-,2,/,2,ifnotzero", "61b0b351-7e06-ef8e-a8e0-7a9e3200a836");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4529);
        internalCounters.push_back(4500);

        c.DefineDerivedCounter("CSFlatLDSInsts", "ComputeShader", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "99672cda-de2b-014c-482e-cf73b90068d5");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2793);
        internalCounters.push_back(2736);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("CSALUStalledByLDS", "ComputeShader", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,/,2,/,NUM_SHADER_ENGINES,/,(100),*,1,ifnotzero", "6dc4f1c2-bad0-c9ff-156e-883b319a752a");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2793);

        c.DefineDerivedCounter("CSALUStalledByLDSCycles", "ComputeShader", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_SHADER_ENGINES,/", "8f3d5f25-2159-0374-fafe-e26a7799b6c8");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4593);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("CSLDSBankConflict", "ComputeShader", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*", "1065ee10-2e41-ea41-1eb3-b61b491752f4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4593);

        c.DefineDerivedCounter("CSLDSBankConflictCycles", "ComputeShader", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_SIMDS,/", "1fd1adf3-c51e-94fd-083e-c482a0a0809e");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4780);
        internalCounters.push_back(4891);
        internalCounters.push_back(5002);
        internalCounters.push_back(5113);
        internalCounters.push_back(5224);
        internalCounters.push_back(5335);
        internalCounters.push_back(5446);
        internalCounters.push_back(5557);
        internalCounters.push_back(5668);
        internalCounters.push_back(5779);
        internalCounters.push_back(5890);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("TexUnitBusy", "Timing", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,/,NUM_SHADER_ENGINES,/,(100),*", "36afb8d9-42fc-aafe-66c5-449542153b2c");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4780);
        internalCounters.push_back(4891);
        internalCounters.push_back(5002);
        internalCounters.push_back(5113);
        internalCounters.push_back(5224);
        internalCounters.push_back(5335);
        internalCounters.push_back(5446);
        internalCounters.push_back(5557);
        internalCounters.push_back(5668);
        internalCounters.push_back(5779);
        internalCounters.push_back(5890);

        c.DefineDerivedCounter("TexUnitBusyCycles", "Timing", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max", "c68761f2-248c-4f39-6528-c308b1c0807c");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4849);
        internalCounters.push_back(4960);
        internalCounters.push_back(5071);
        internalCounters.push_back(5182);
        internalCounters.push_back(5293);
        internalCounters.push_back(5404);
        internalCounters.push_back(5515);
        internalCounters.push_back(5626);
        internalCounters.push_back(5737);
        internalCounters.push_back(5848);
        internalCounters.push_back(5959);
        internalCounters.push_back(4848);
        internalCounters.push_back(4959);
        internalCounters.push_back(5070);
        internalCounters.push_back(5181);
        internalCounters.push_back(5292);
        internalCounters.push_back(5403);
        internalCounters.push_back(5514);
        internalCounters.push_back(5625);
        internalCounters.push_back(5736);
        internalCounters.push_back(5847);
        internalCounters.push_back(5958);

        c.DefineDerivedCounter("TexTriFilteringPct", "TextureUnit", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,sum11,11,12,13,14,15,16,17,18,19,20,21,sum11,0,1,2,3,4,5,6,7,8,9,10,sum11,+,/,(100),*", "1affc3c8-b917-5c81-622b-7004527208ae");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4849);
        internalCounters.push_back(4960);
        internalCounters.push_back(5071);
        internalCounters.push_back(5182);
        internalCounters.push_back(5293);
        internalCounters.push_back(5404);
        internalCounters.push_back(5515);
        internalCounters.push_back(5626);
        internalCounters.push_back(5737);
        internalCounters.push_back(5848);
        internalCounters.push_back(5959);

        c.DefineDerivedCounter("TexTriFilteringCount", "TextureUnit", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,sum11", "5785b3a1-a513-18db-4b1c-bdeef75bb2b6");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4848);
        internalCounters.push_back(4959);
        internalCounters.push_back(5070);
        internalCounters.push_back(5181);
        internalCounters.push_back(5292);
        internalCounters.push_back(5403);
        internalCounters.push_back(5514);
        internalCounters.push_back(5625);
        internalCounters.push_back(5736);
        internalCounters.push_back(5847);
        internalCounters.push_back(5958);

        c.DefineDerivedCounter("NoTexTriFilteringCount", "TextureUnit", "Count of pixels that did not receive trilinear filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,sum11", "179da29a-81af-c06e-ce8c-a0a731ea030d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4851);
        internalCounters.push_back(4962);
        internalCounters.push_back(5073);
        internalCounters.push_back(5184);
        internalCounters.push_back(5295);
        internalCounters.push_back(5406);
        internalCounters.push_back(5517);
        internalCounters.push_back(5628);
        internalCounters.push_back(5739);
        internalCounters.push_back(5850);
        internalCounters.push_back(5961);
        internalCounters.push_back(4850);
        internalCounters.push_back(4961);
        internalCounters.push_back(5072);
        internalCounters.push_back(5183);
        internalCounters.push_back(5294);
        internalCounters.push_back(5405);
        internalCounters.push_back(5516);
        internalCounters.push_back(5627);
        internalCounters.push_back(5738);
        internalCounters.push_back(5849);
        internalCounters.push_back(5960);

        c.DefineDerivedCounter("TexVolFilteringPct", "TextureUnit", "Percentage of pixels that received volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,sum11,11,12,13,14,15,16,17,18,19,20,21,sum11,0,1,2,3,4,5,6,7,8,9,10,sum11,+,/,(100),*", "b5ff6bed-3178-aee4-42dd-c74391c02a2d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4851);
        internalCounters.push_back(4962);
        internalCounters.push_back(5073);
        internalCounters.push_back(5184);
        internalCounters.push_back(5295);
        internalCounters.push_back(5406);
        internalCounters.push_back(5517);
        internalCounters.push_back(5628);
        internalCounters.push_back(5739);
        internalCounters.push_back(5850);
        internalCounters.push_back(5961);

        c.DefineDerivedCounter("TexVolFilteringCount", "TextureUnit", "Count of pixels that received volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,sum11", "4bddc587-d589-8128-e18c-762eab2c871f");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4850);
        internalCounters.push_back(4961);
        internalCounters.push_back(5072);
        internalCounters.push_back(5183);
        internalCounters.push_back(5294);
        internalCounters.push_back(5405);
        internalCounters.push_back(5516);
        internalCounters.push_back(5627);
        internalCounters.push_back(5738);
        internalCounters.push_back(5849);
        internalCounters.push_back(5960);

        c.DefineDerivedCounter("NoTexVolFilteringCount", "TextureUnit", "Count of pixels that did not receive volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,sum11", "9fe1a854-17c6-9d26-b2b9-80610cd5827d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4869);
        internalCounters.push_back(4980);
        internalCounters.push_back(5091);
        internalCounters.push_back(5202);
        internalCounters.push_back(5313);
        internalCounters.push_back(5424);
        internalCounters.push_back(5535);
        internalCounters.push_back(5646);
        internalCounters.push_back(5757);
        internalCounters.push_back(5868);
        internalCounters.push_back(5979);
        internalCounters.push_back(4870);
        internalCounters.push_back(4981);
        internalCounters.push_back(5092);
        internalCounters.push_back(5203);
        internalCounters.push_back(5314);
        internalCounters.push_back(5425);
        internalCounters.push_back(5536);
        internalCounters.push_back(5647);
        internalCounters.push_back(5758);
        internalCounters.push_back(5869);
        internalCounters.push_back(5980);
        internalCounters.push_back(4871);
        internalCounters.push_back(4982);
        internalCounters.push_back(5093);
        internalCounters.push_back(5204);
        internalCounters.push_back(5315);
        internalCounters.push_back(5426);
        internalCounters.push_back(5537);
        internalCounters.push_back(5648);
        internalCounters.push_back(5759);
        internalCounters.push_back(5870);
        internalCounters.push_back(5981);
        internalCounters.push_back(4872);
        internalCounters.push_back(4983);
        internalCounters.push_back(5094);
        internalCounters.push_back(5205);
        internalCounters.push_back(5316);
        internalCounters.push_back(5427);
        internalCounters.push_back(5538);
        internalCounters.push_back(5649);
        internalCounters.push_back(5760);
        internalCounters.push_back(5871);
        internalCounters.push_back(5982);
        internalCounters.push_back(4873);
        internalCounters.push_back(4984);
        internalCounters.push_back(5095);
        internalCounters.push_back(5206);
        internalCounters.push_back(5317);
        internalCounters.push_back(5428);
        internalCounters.push_back(5539);
        internalCounters.push_back(5650);
        internalCounters.push_back(5761);
        internalCounters.push_back(5872);
        internalCounters.push_back(5983);
        internalCounters.push_back(4874);
        internalCounters.push_back(4985);
        internalCounters.push_back(5096);
        internalCounters.push_back(5207);
        internalCounters.push_back(5318);
        internalCounters.push_back(5429);
        internalCounters.push_back(5540);
        internalCounters.push_back(5651);
        internalCounters.push_back(5762);
        internalCounters.push_back(5873);
        internalCounters.push_back(5984);
        internalCounters.push_back(4875);
        internalCounters.push_back(4986);
        internalCounters.push_back(5097);
        internalCounters.push_back(5208);
        internalCounters.push_back(5319);
        internalCounters.push_back(5430);
        internalCounters.push_back(5541);
        internalCounters.push_back(5652);
        internalCounters.push_back(5763);
        internalCounters.push_back(5874);
        internalCounters.push_back(5985);
        internalCounters.push_back(4876);
        internalCounters.push_back(4987);
        internalCounters.push_back(5098);
        internalCounters.push_back(5209);
        internalCounters.push_back(5320);
        internalCounters.push_back(5431);
        internalCounters.push_back(5542);
        internalCounters.push_back(5653);
        internalCounters.push_back(5764);
        internalCounters.push_back(5875);
        internalCounters.push_back(5986);
        internalCounters.push_back(4877);
        internalCounters.push_back(4988);
        internalCounters.push_back(5099);
        internalCounters.push_back(5210);
        internalCounters.push_back(5321);
        internalCounters.push_back(5432);
        internalCounters.push_back(5543);
        internalCounters.push_back(5654);
        internalCounters.push_back(5765);
        internalCounters.push_back(5876);
        internalCounters.push_back(5987);

        c.DefineDerivedCounter("TexAveAnisotropy", "TextureUnit", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,sum11,(2),11,12,13,14,15,16,17,18,19,20,21,sum11,*,+,(4),22,23,24,25,26,27,28,29,30,31,32,sum11,*,+,(6),33,34,35,36,37,38,39,40,41,42,43,sum11,*,+,(8),44,45,46,47,48,49,50,51,52,53,54,sum11,*,+,(10),55,56,57,58,59,60,61,62,63,64,65,sum11,*,+,(12),66,67,68,69,70,71,72,73,74,75,76,sum11,*,+,(14),77,78,79,80,81,82,83,84,85,86,87,sum11,*,+,(16),88,89,90,91,92,93,94,95,96,97,98,sum11,*,+,0,1,2,3,4,5,6,7,8,9,10,sum11,11,12,13,14,15,16,17,18,19,20,21,sum11,+,22,23,24,25,26,27,28,29,30,31,32,sum11,+,33,34,35,36,37,38,39,40,41,42,43,sum11,+,44,45,46,47,48,49,50,51,52,53,54,sum11,+,55,56,57,58,59,60,61,62,63,64,65,sum11,+,66,67,68,69,70,71,72,73,74,75,76,sum11,+,77,78,79,80,81,82,83,84,85,86,87,sum11,+,88,89,90,91,92,93,94,95,96,97,98,sum11,+,/", "7ca2a2b9-a4eb-ce23-d163-59147e672396");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1065);
        internalCounters.push_back(1322);
        internalCounters.push_back(1579);
        internalCounters.push_back(1836);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("DepthStencilTestBusy", "Timing", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "6834fb52-42e8-bb50-fd48-ec2f2904e7e0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1065);
        internalCounters.push_back(1322);
        internalCounters.push_back(1579);
        internalCounters.push_back(1836);

        c.DefineDerivedCounter("DepthStencilTestBusyCount", "Timing", "Number of GPU cycles spent performing depth and stencil tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "e02860fa-c7bd-90ea-2149-69b4e98a636c");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(936);
        internalCounters.push_back(1193);
        internalCounters.push_back(1450);
        internalCounters.push_back(1707);
        internalCounters.push_back(925);
        internalCounters.push_back(1182);
        internalCounters.push_back(1439);
        internalCounters.push_back(1696);

        c.DefineDerivedCounter("HiZTilesAccepted", "DepthAndStencil", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*", "56176f45-d7ff-813d-4f05-3b2f046067e7");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(936);
        internalCounters.push_back(1193);
        internalCounters.push_back(1450);
        internalCounters.push_back(1707);

        c.DefineDerivedCounter("HiZTilesAcceptedCount", "DepthAndStencil", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "95d4e3f6-b2f0-f26e-8423-aacdfaf79ea3");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(925);
        internalCounters.push_back(1182);
        internalCounters.push_back(1439);
        internalCounters.push_back(1696);

        c.DefineDerivedCounter("HiZTilesRejectedCount", "DepthAndStencil", "Count of tiles not accepted by HiZ.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "156ba142-7eeb-aa6e-a00a-f8aea4e41e0b");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(925);
        internalCounters.push_back(1182);
        internalCounters.push_back(1439);
        internalCounters.push_back(1696);
        internalCounters.push_back(949);
        internalCounters.push_back(1206);
        internalCounters.push_back(1463);
        internalCounters.push_back(1720);

        c.DefineDerivedCounter("PreZTilesDetailCulled", "DepthAndStencil", "Percentage of tiles rejected because the associated prim had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "4,5,6,7,sum4,0,1,2,3,sum4,/,(100),*", "cad7f54d-a044-7574-c472-6f2065cbeeac");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(949);
        internalCounters.push_back(1206);
        internalCounters.push_back(1463);
        internalCounters.push_back(1720);

        c.DefineDerivedCounter("PreZTilesDetailCulledCount", "DepthAndStencil", "Count of tiles rejected because the associated primitive had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "49262c8a-b1e6-90dd-f096-0fc4921715e9");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(925);
        internalCounters.push_back(1182);
        internalCounters.push_back(1439);
        internalCounters.push_back(1696);

        c.DefineDerivedCounter("PreZTilesDetailSurvivingCount", "DepthAndStencil", "Count of tiles surviving because the associated primitive had contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "f803eaa4-bbed-bd39-775f-a64df92e2c08");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2314);
        internalCounters.push_back(2315);
        internalCounters.push_back(2316);
        internalCounters.push_back(2317);
        internalCounters.push_back(2390);
        internalCounters.push_back(2391);
        internalCounters.push_back(2392);
        internalCounters.push_back(2393);

        c.DefineDerivedCounter("HiZQuadsCulled", "DepthAndStencil", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-,0,1,+,2,+,3,+,/,(100),*", "fa0e319b-5573-6d34-5bab-904769925036");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2314);
        internalCounters.push_back(2315);
        internalCounters.push_back(2316);
        internalCounters.push_back(2317);
        internalCounters.push_back(2390);
        internalCounters.push_back(2391);
        internalCounters.push_back(2392);
        internalCounters.push_back(2393);

        c.DefineDerivedCounter("HiZQuadsCulledCount", "DepthAndStencil", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-", "73b0b39d-6df2-3e24-0b5c-7cb0ac8b6f39");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2390);
        internalCounters.push_back(2391);
        internalCounters.push_back(2392);
        internalCounters.push_back(2393);

        c.DefineDerivedCounter("HiZQuadsAcceptedCount", "DepthAndStencil", "Count of quads that did continue on in the pipeline after HiZ.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+", "59049ad9-42b5-c7cb-3616-6a8f6a8e4894");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2314);
        internalCounters.push_back(2315);
        internalCounters.push_back(2316);
        internalCounters.push_back(2317);
        internalCounters.push_back(2414);
        internalCounters.push_back(2390);
        internalCounters.push_back(2391);
        internalCounters.push_back(2392);
        internalCounters.push_back(2393);

        c.DefineDerivedCounter("PreZQuadsCulled", "DepthAndStencil", "Percentage of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "5,6,+,7,+,8,+,4,-,0,1,+,2,+,3,+,/,(100),*", "4e77547b-ec55-5663-f034-af59be66d77d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2314);
        internalCounters.push_back(2315);
        internalCounters.push_back(2316);
        internalCounters.push_back(2317);
        internalCounters.push_back(2414);
        internalCounters.push_back(2390);
        internalCounters.push_back(2391);
        internalCounters.push_back(2392);
        internalCounters.push_back(2393);

        c.DefineDerivedCounter("PreZQuadsCulledCount", "DepthAndStencil", "Count of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+,4,-,5,-,6,-,7,-,8,-", "1bf169e6-9304-834e-df5f-0c44d7890a08");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2414);
        internalCounters.push_back(2390);
        internalCounters.push_back(2391);
        internalCounters.push_back(2392);
        internalCounters.push_back(2393);

        c.DefineDerivedCounter("PreZQuadsSurvivingCount", "DepthAndStencil", "Count of quads surviving detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "1,2,+,3,+,4,+,0,-", "50e25e51-3713-89cb-7f92-559cde5e5532");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2414);
        internalCounters.push_back(2314);
        internalCounters.push_back(2315);
        internalCounters.push_back(2316);
        internalCounters.push_back(2317);

        c.DefineDerivedCounter("PostZQuads", "DepthAndStencil", "Percentage of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,+,3,+,4,+,/,(100),*", "58f0d34b-eeb8-e8db-abce-cb72584144be");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2414);

        c.DefineDerivedCounter("PostZQuadCount", "DepthAndStencil", "Count of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "08404526-ce35-939b-34c8-a7a35a0ff4d6");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1098);
        internalCounters.push_back(1355);
        internalCounters.push_back(1612);
        internalCounters.push_back(1869);

        c.DefineDerivedCounter("PreZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z before shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "3bfe6c4d-7422-ca03-7ea5-e67ff1a00136");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1100);
        internalCounters.push_back(1357);
        internalCounters.push_back(1614);
        internalCounters.push_back(1871);

        c.DefineDerivedCounter("PreZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z before shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "df7f705e-5162-d3b5-da8b-63466cf9c4e5");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1099);
        internalCounters.push_back(1356);
        internalCounters.push_back(1613);
        internalCounters.push_back(1870);

        c.DefineDerivedCounter("PreZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z before shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "4484e950-f7a4-3800-bc74-78dd297f017e");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1095);
        internalCounters.push_back(1352);
        internalCounters.push_back(1609);
        internalCounters.push_back(1866);

        c.DefineDerivedCounter("PostZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z after shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "4995d5d6-2330-b986-508b-fae24856f44c");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1097);
        internalCounters.push_back(1354);
        internalCounters.push_back(1611);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("PostZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z after shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "ae558af4-f4be-3dd4-7316-b2c4dcf0def8");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1096);
        internalCounters.push_back(1353);
        internalCounters.push_back(1610);
        internalCounters.push_back(1867);

        c.DefineDerivedCounter("PostZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z after shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "b3684c94-814a-c695-c85d-a5b6ab798b35");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(967);
        internalCounters.push_back(1224);
        internalCounters.push_back(1481);
        internalCounters.push_back(1738);
        internalCounters.push_back(1951);

        c.DefineDerivedCounter("ZUnitStalled", "DepthAndStencil", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "5e86c3ad-1726-3157-1d01-7ed188bf854d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(967);
        internalCounters.push_back(1224);
        internalCounters.push_back(1481);
        internalCounters.push_back(1738);

        c.DefineDerivedCounter("ZUnitStalledCycles", "DepthAndStencil", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "4351fa7f-6737-2c3e-3ffb-b3addbdceedd");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(969);
        internalCounters.push_back(1226);
        internalCounters.push_back(1483);
        internalCounters.push_back(1740);
        internalCounters.push_back(976);
        internalCounters.push_back(1233);
        internalCounters.push_back(1490);
        internalCounters.push_back(1747);

        c.DefineDerivedCounter("DBMemRead", "DepthAndStencil", "Number of bytes read from the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,sum4,(256),*,4,5,6,7,sum4,(32),*,+", "dcdb4ee7-bd50-00f7-c028-9e5f4ce888c0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(981);
        internalCounters.push_back(1238);
        internalCounters.push_back(1495);
        internalCounters.push_back(1752);
        internalCounters.push_back(984);
        internalCounters.push_back(1241);
        internalCounters.push_back(1498);
        internalCounters.push_back(1755);

        c.DefineDerivedCounter("DBMemWritten", "DepthAndStencil", "Number of bytes written to the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,sum4,(32),*,4,5,6,7,sum4,(32),*,+", "de5717f8-8a49-ee44-4645-10de51b37dcf");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(127);
        internalCounters.push_back(353);
        internalCounters.push_back(579);
        internalCounters.push_back(805);

        c.DefineDerivedCounter("CBMemRead", "ColorBuffer", "Number of bytes read from the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,sum4,(32),*", "84b531d8-a1f8-7f49-7c27-7bc97801f1e6");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(117);
        internalCounters.push_back(343);
        internalCounters.push_back(569);
        internalCounters.push_back(795);

        c.DefineDerivedCounter("CBMemWritten", "ColorBuffer", "Number of bytes written to the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,sum4,(32),*", "550f8ff8-60b6-a6bf-87d0-25ac9e87de70");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(161);
        internalCounters.push_back(387);
        internalCounters.push_back(613);
        internalCounters.push_back(839);
        internalCounters.push_back(7);
        internalCounters.push_back(233);
        internalCounters.push_back(459);
        internalCounters.push_back(685);

        c.DefineDerivedCounter("CBSlowPixelPct", "ColorBuffer", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*,(100),min", "5775943f-0313-7e52-9638-b24a449197bc");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(161);
        internalCounters.push_back(387);
        internalCounters.push_back(613);
        internalCounters.push_back(839);

        c.DefineDerivedCounter("CBSlowPixelCount", "ColorBuffer", "Number of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "47eacbb0-28c8-22b4-5c69-c00d5813bb1c");
    }
}

