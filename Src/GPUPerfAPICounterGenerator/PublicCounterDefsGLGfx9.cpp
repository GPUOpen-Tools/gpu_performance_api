//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for GLGFX9
//==============================================================================

#include "GPAInternalCounter.h"
#include "PublicCounterDefsGLGfx9.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersGLGfx9(GPA_DerivedCounters& c)
{
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16606);

        c.DefineDerivedCounter("GPUTime", "Timing", "Time this API command took to execute on the GPU in nanoseconds from the time the previous command reached the bottom of the pipeline (BOP) to the time this command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "0,TS_FREQ,/,(1000000000),*", "cbd338f2-de6c-7b14-92ad-ba724ca2e501");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3098);
        internalCounters.push_back(3096);

        c.DefineDerivedCounter("GPUBusy", "Timing", "The percentage of time GPU was busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,(100),*,(100),min", "bef38bf3-1167-0844-81f0-67d2d28ddbc5");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("GPUBusyCycles", "Timing", "Number of GPU cycles that the GPU was busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0", "1e84970d-7014-2b8d-d61e-388b5f782691");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16393);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("TessellatorBusy", "Timing", "The percentage of time the tessellation engine is busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*", "36af6c72-dcfb-8102-4fd4-ce8ddc573365");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16393);

        c.DefineDerivedCounter("TessellatorBusyCycles", "Timing", "Number of GPU cycles that the tessellation engine is busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_PRIM_PIPES,/", "60289dcb-7b33-46e7-26d1-8a2121605543");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3994);
        internalCounters.push_back(4003);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("VSBusy", "Timing", "The percentage of time the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "94caad5e-867c-6c09-cf3a-d05b51df8f3b");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3994);
        internalCounters.push_back(4003);

        c.DefineDerivedCounter("VSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero", "a2086d4e-274b-48a8-3e08-a4ab76ac15dd");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16606);
        internalCounters.push_back(3994);
        internalCounters.push_back(4003);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("VSTime", "Timing", "Time vertex shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "d6ce819e-69af-a241-d07a-5dd8d146e436");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4025);
        internalCounters.push_back(4031);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("HSBusy", "Timing", "The percentage of time the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "16f30a0b-4cbf-eccd-b13f-ab68dd254d32");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4025);
        internalCounters.push_back(4031);

        c.DefineDerivedCounter("HSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero", "753e76ef-8ef8-3f13-b511-4bd9f3589fdb");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16606);
        internalCounters.push_back(4025);
        internalCounters.push_back(4031);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("HSTime", "Timing", "Time hull shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "8386a863-dd34-1526-f703-0f0c7b241bc4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4013);
        internalCounters.push_back(4016);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("GSBusy", "Timing", "The percentage of time the ShaderUnit has geometry shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "876f36d8-d046-833f-7832-673cbffd0a45");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4013);
        internalCounters.push_back(4016);

        c.DefineDerivedCounter("GSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has geometry shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero", "48203b6b-8983-c067-d63e-05da8be5111b");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16606);
        internalCounters.push_back(4013);
        internalCounters.push_back(4016);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("GSTime", "Timing", "Time geometry shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "c73e715f-59af-76e8-9e22-097b94c066c4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4047);
        internalCounters.push_back(4052);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("PSBusy", "Timing", "The percentage of time the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "7e772beb-d82c-bd9a-aed0-fe504d416ce5");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4047);
        internalCounters.push_back(4052);

        c.DefineDerivedCounter("PSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero", "b58bea04-ce8e-2984-80f4-8aba7d4c817b");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16606);
        internalCounters.push_back(4047);
        internalCounters.push_back(4052);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("PSTime", "Timing", "Time pixel shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "edca7694-7416-e8a6-0c5a-63a5ad5f3d74");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4035);
        internalCounters.push_back(4039);
        internalCounters.push_back(4041);
        internalCounters.push_back(4045);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("CSBusy", "Timing", "The percentage of time the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,max,4,/,(100),*,(100),min", "493fdd90-8d2b-a055-5e4e-2d29c3396b8c");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4035);
        internalCounters.push_back(4039);
        internalCounters.push_back(4041);
        internalCounters.push_back(4045);

        c.DefineDerivedCounter("CSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,max", "39bcf1b8-f6b2-4c37-f9af-0a2bb59512f9");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16606);
        internalCounters.push_back(4035);
        internalCounters.push_back(4039);
        internalCounters.push_back(4041);
        internalCounters.push_back(4045);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("CSTime", "Timing", "Time compute shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,2,ifnotzero,(0),3,4,ifnotzero,max,5,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "dbc24916-ecb2-7eef-8d63-7afadaaab6bc");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16288);
        internalCounters.push_back(16269);
        internalCounters.push_back(16364);

        c.DefineDerivedCounter("VSVerticesIn", "VertexShader", "The number of vertices processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero", "810a04c8-2ff4-081d-766d-bfa2bd4ad916");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5337);
        internalCounters.push_back(5315);

        c.DefineDerivedCounter("VSVALUInstCount", "VertexShader", "Average number of vector ALU instructions executed in the VS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "8ec604e4-63f5-e6b5-4558-c38f0b26d4b1");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5341);
        internalCounters.push_back(5315);

        c.DefineDerivedCounter("VSSALUInstCount", "VertexShader", "Average number of scalar ALU instructions executed in the VS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "e3da0383-7322-7f65-8cf2-3ce641578e54");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5382);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("VSVALUBusy", "VertexShader", "The percentage of GPUTime vector ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "8b3572f7-fda0-eddf-6c93-2ab145b8754b");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5382);

        c.DefineDerivedCounter("VSVALUBusyCycles", "VertexShader", "Number of GPU cycles where vector ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0", "0af1686e-6d77-2f6e-2862-7bb8e869a776");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5395);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("VSSALUBusy", "VertexShader", "The percentage of GPUTime scalar ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*", "3bc8730c-e3bc-e2f0-7d24-36974064c25a");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5395);

        c.DefineDerivedCounter("VSSALUBusyCycles", "VertexShader", "Number of GPU cycles where scalar ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "357ac7cd-2e1c-dcb0-77f6-37527237f35b");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16373);

        c.DefineDerivedCounter("HSPatches", "HullShader", "The number of patches processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "d1bbd27d-d591-4509-df52-d329fb73a98f");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6459);
        internalCounters.push_back(6437);

        c.DefineDerivedCounter("HSVALUInstCount", "HullShader", "Average number of vector ALU instructions executed in the HS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "786673bf-d58f-9895-3a37-9d6efb5e5804");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6463);
        internalCounters.push_back(6437);

        c.DefineDerivedCounter("HSSALUInstCount", "HullShader", "Average number of scalar ALU instructions executed in the HS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "1af675c4-cb0b-c4c5-c131-2796750f683e");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6504);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("HSVALUBusy", "HullShader", "The percentage of GPUTime vector ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "7880d192-8015-0311-d43e-fb0b7a4df179");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6504);

        c.DefineDerivedCounter("HSVALUBusyCycles", "HullShader", "Number of GPU cycles vector where ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,/", "3afb94e4-e937-5730-0cc9-41d3113ba012");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6517);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("HSSALUBusy", "HullShader", "The percentage of GPUTime scalar ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*", "34748a4b-9148-0b06-b7b9-5700d6631bde");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6517);

        c.DefineDerivedCounter("HSSALUBusyCycles", "HullShader", "Number of GPU cycles where scalar ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "9bceabf7-3f01-2fd9-7b1d-8fe46c729efc");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16277);

        c.DefineDerivedCounter("GSPrimsIn", "GeometryShader", "The number of primitives passed into the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "20c29866-509a-aaab-2697-6b2c38f79953");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16288);
        internalCounters.push_back(16269);

        c.DefineDerivedCounter("GSVerticesOut", "GeometryShader", "The number of vertices output by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,ifnotzero", "775b9736-319a-bd8a-48c9-68db9c91d978");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4963);
        internalCounters.push_back(4941);

        c.DefineDerivedCounter("GSVALUInstCount", "GeometryShader", "Average number of vector ALU instructions executed in the GS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "21b12bfa-b8cd-2e71-a2d5-f9e9f1d65d61");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4967);
        internalCounters.push_back(4941);

        c.DefineDerivedCounter("GSSALUInstCount", "GeometryShader", "Average number of scalar ALU instructions executed in the GS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "a8562594-d335-ca43-61bf-03b72d2b98a5");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5008);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("GSVALUBusy", "GeometryShader", "The percentage of GPUTime vector ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "228a4818-1e56-cebb-0720-3b2cdc057a6f");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5008);

        c.DefineDerivedCounter("GSVALUBusyCycles", "GeometryShader", "Number of GPU cycles where vector ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,/", "be217edd-226f-bd97-9a48-46e2809b1933");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5021);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("GSSALUBusy", "GeometryShader", "The percentage of GPUTime scalar ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*", "f28ce300-800e-9822-39e4-f48528bdb935");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5021);

        c.DefineDerivedCounter("GSSALUBusyCycles", "GeometryShader", "Number of GPU cycles where scalar ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "b3eace7c-3bc4-0107-887f-923851dc8ea7");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3255);
        internalCounters.push_back(3259);
        internalCounters.push_back(3211);
        internalCounters.push_back(3223);
        internalCounters.push_back(3212);
        internalCounters.push_back(3224);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("PrimitiveAssemblyBusy", "Timing", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max,6,/,(100),*,(100),min", "fe08f347-91cb-01b6-02e4-d79f7cb89a93");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3255);
        internalCounters.push_back(3259);
        internalCounters.push_back(3211);
        internalCounters.push_back(3223);
        internalCounters.push_back(3212);
        internalCounters.push_back(3224);

        c.DefineDerivedCounter("PrimitiveAssemblyBusyCycles", "Timing", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max", "b75bc709-9c04-bf6c-b3f2-511b66e70ed0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3158);

        c.DefineDerivedCounter("PrimitivesIn", "PrimitiveAssembly", "The number of primitives received by the hardware. This includes primitives generated by tessellation.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "a515b80d-75c3-c7d2-0d2f-d7766b4759a6");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3164);
        internalCounters.push_back(3204);
        internalCounters.push_back(3205);
        internalCounters.push_back(3206);
        internalCounters.push_back(3207);

        c.DefineDerivedCounter("CulledPrims", "PrimitiveAssembly", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+,4,+", "589bdf55-9192-280a-41c3-584bc94f2562");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3171);

        c.DefineDerivedCounter("ClippedPrims", "PrimitiveAssembly", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "5ef6f9d5-155e-5baa-163f-8359d9ea9bbf");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3259);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("PAStalledOnRasterizer", "PrimitiveAssembly", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*", "6f9f416b-53c1-0457-f88c-7b6ba8973974");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3259);

        c.DefineDerivedCounter("PAStalledOnRasterizerCycles", "PrimitiveAssembly", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_PRIM_PIPES,/", "7a8c492a-c566-9328-6805-760dbff5c0f2");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7193);
        internalCounters.push_back(7198);
        internalCounters.push_back(7203);
        internalCounters.push_back(7208);

        c.DefineDerivedCounter("PSPixelsOut", "PixelShader", "Pixels exported from shader to color buffers. Does not include killed or alpha tested pixels", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "edd35449-8cba-daa2-06f8-8f0eb2bd42c8");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7195);
        internalCounters.push_back(7200);
        internalCounters.push_back(7205);
        internalCounters.push_back(7210);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("PSExportStalls", "PixelShader", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "d438414c-9ff5-d60a-1468-92040ce387c7");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7195);
        internalCounters.push_back(7200);
        internalCounters.push_back(7205);
        internalCounters.push_back(7210);

        c.DefineDerivedCounter("PSExportStallsCycles", "PixelShader", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "477bf668-a6d3-bd1b-823e-3aff43b2beb4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5711);
        internalCounters.push_back(5689);

        c.DefineDerivedCounter("PSVALUInstCount", "PixelShader", "Average number of vector ALU instructions executed in the PS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "eb74389e-435c-4137-ecf1-39eb5bc1cbfe");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5715);
        internalCounters.push_back(5689);

        c.DefineDerivedCounter("PSSALUInstCount", "PixelShader", "Average number of scalar ALU instructions executed in the PS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "e6a06580-8a82-96d6-976c-acc121fc5516");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5756);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("PSVALUBusy", "PixelShader", "The percentage of GPUTime vector ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "6ce6fef7-8e33-10b4-f351-af755e177e85");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5756);

        c.DefineDerivedCounter("PSVALUBusyCycles", "PixelShader", "Number of GPU cycles where vector ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,/", "1e276f86-cd2a-72e7-fc9d-004f666f2981");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5769);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("PSSALUBusy", "PixelShader", "The percentage of GPUTime scalar ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*", "2ff9f34f-e94b-af4d-18c2-5fbbf6d1727a");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5769);

        c.DefineDerivedCounter("PSSALUBusyCycles", "PixelShader", "Number of GPU cycles where scalar ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "29808906-f128-b078-fc79-820a4b3b3b8d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4036);
        internalCounters.push_back(4042);

        c.DefineDerivedCounter("CSThreadGroups", "ComputeShader", "Total number of thread groups.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+", "8ce3fc80-56b2-97f9-8e70-2e8c747cea68");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6811);

        c.DefineDerivedCounter("CSWavefronts", "ComputeShader", "The total number of wavefronts used for the CS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "42379c6e-369b-c237-8b25-cdb9cdc65c4d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6821);

        c.DefineDerivedCounter("CSThreads", "ComputeShader", "The number of CS threads processed by the hardware.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "7a648013-6eac-2665-ac36-13c6f4ac9c26");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6833);
        internalCounters.push_back(6811);

        c.DefineDerivedCounter("CSVALUInsts", "ComputeShader", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "376cb1cc-5a40-9d1d-404c-f1736c0c5084");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6892);
        internalCounters.push_back(6878);

        c.DefineDerivedCounter("CSVALUUtilization", "ComputeShader", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,(64),*,/,(100),*,1,ifnotzero,(100),min", "4476879e-cdc0-d602-b24e-9b4a8d38438f");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6837);
        internalCounters.push_back(6811);

        c.DefineDerivedCounter("CSSALUInsts", "ComputeShader", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "eb211144-8136-ff86-e8bf-4d0493a904cb");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6835);
        internalCounters.push_back(7490);
        internalCounters.push_back(7609);
        internalCounters.push_back(7728);
        internalCounters.push_back(7847);
        internalCounters.push_back(7966);
        internalCounters.push_back(8085);
        internalCounters.push_back(8204);
        internalCounters.push_back(8323);
        internalCounters.push_back(8442);
        internalCounters.push_back(8561);
        internalCounters.push_back(8680);
        internalCounters.push_back(8799);
        internalCounters.push_back(8918);
        internalCounters.push_back(9037);
        internalCounters.push_back(9156);
        internalCounters.push_back(9275);
        internalCounters.push_back(6811);

        c.DefineDerivedCounter("CSVFetchInsts", "ComputeShader", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/,17,ifnotzero", "3e2829c0-6215-783b-c271-6d57ff2c520e");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6838);
        internalCounters.push_back(6811);

        c.DefineDerivedCounter("CSSFetchInsts", "ComputeShader", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "da09171c-6a0a-584f-fddc-dc5062d63a3e");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6834);
        internalCounters.push_back(7491);
        internalCounters.push_back(7610);
        internalCounters.push_back(7729);
        internalCounters.push_back(7848);
        internalCounters.push_back(7967);
        internalCounters.push_back(8086);
        internalCounters.push_back(8205);
        internalCounters.push_back(8324);
        internalCounters.push_back(8443);
        internalCounters.push_back(8562);
        internalCounters.push_back(8681);
        internalCounters.push_back(8800);
        internalCounters.push_back(8919);
        internalCounters.push_back(9038);
        internalCounters.push_back(9157);
        internalCounters.push_back(9276);
        internalCounters.push_back(6811);

        c.DefineDerivedCounter("CSVWriteInsts", "ComputeShader", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/,17,ifnotzero", "43438c22-e910-b377-b767-b32902e0df0d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6839);
        internalCounters.push_back(6840);
        internalCounters.push_back(6811);

        c.DefineDerivedCounter("CSFlatVMemInsts", "ComputeShader", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,-,2,/,2,ifnotzero", "2570b477-13e3-f5b6-e6ff-7159373bc74d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6878);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("CSVALUBusy", "ComputeShader", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*", "f1e64815-f6a8-c277-d4f9-d054b443e205");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6878);

        c.DefineDerivedCounter("CSVALUBusyCycles", "ComputeShader", "Number of GPU cycles where vector ALU instructions are processed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,/", "2d0d5852-2658-eb73-68d2-f23f7118c9c3");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6891);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("CSSALUBusy", "ComputeShader", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*", "3fc35f4e-9882-94e3-6f5f-4e81cd97082a");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6891);

        c.DefineDerivedCounter("CSSALUBusyCycles", "ComputeShader", "Number of GPU cycles where scalar ALU instructions are processed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "de58f8fc-8ed4-a799-648d-62ded7b1c4c4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7404);
        internalCounters.push_back(7523);
        internalCounters.push_back(7642);
        internalCounters.push_back(7761);
        internalCounters.push_back(7880);
        internalCounters.push_back(7999);
        internalCounters.push_back(8118);
        internalCounters.push_back(8237);
        internalCounters.push_back(8356);
        internalCounters.push_back(8475);
        internalCounters.push_back(8594);
        internalCounters.push_back(8713);
        internalCounters.push_back(8832);
        internalCounters.push_back(8951);
        internalCounters.push_back(9070);
        internalCounters.push_back(9189);
        internalCounters.push_back(3098);
        internalCounters.push_back(4036);
        internalCounters.push_back(4042);

        c.DefineDerivedCounter("CSMemUnitBusy", "ComputeShader", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*,17,18,+,ifnotzero", "42ab96e1-0a24-96c8-c4ff-098fa267d78e");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7404);
        internalCounters.push_back(7523);
        internalCounters.push_back(7642);
        internalCounters.push_back(7761);
        internalCounters.push_back(7880);
        internalCounters.push_back(7999);
        internalCounters.push_back(8118);
        internalCounters.push_back(8237);
        internalCounters.push_back(8356);
        internalCounters.push_back(8475);
        internalCounters.push_back(8594);
        internalCounters.push_back(8713);
        internalCounters.push_back(8832);
        internalCounters.push_back(8951);
        internalCounters.push_back(9070);
        internalCounters.push_back(9189);

        c.DefineDerivedCounter("CSMemUnitBusyCycles", "ComputeShader", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ENGINES,/", "39d5687f-c727-7c0c-af82-bb711d3897ed");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14793);
        internalCounters.push_back(14878);
        internalCounters.push_back(14963);
        internalCounters.push_back(15048);
        internalCounters.push_back(15133);
        internalCounters.push_back(15218);
        internalCounters.push_back(15303);
        internalCounters.push_back(15388);
        internalCounters.push_back(15473);
        internalCounters.push_back(15558);
        internalCounters.push_back(15643);
        internalCounters.push_back(15728);
        internalCounters.push_back(15813);
        internalCounters.push_back(15898);
        internalCounters.push_back(15983);
        internalCounters.push_back(16068);
        internalCounters.push_back(3098);
        internalCounters.push_back(4036);
        internalCounters.push_back(4042);

        c.DefineDerivedCounter("CSMemUnitStalled", "ComputeShader", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*,17,18,+,ifnotzero", "f18e8679-1511-d533-d9ee-4365197f7d0c");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14793);
        internalCounters.push_back(14878);
        internalCounters.push_back(14963);
        internalCounters.push_back(15048);
        internalCounters.push_back(15133);
        internalCounters.push_back(15218);
        internalCounters.push_back(15303);
        internalCounters.push_back(15388);
        internalCounters.push_back(15473);
        internalCounters.push_back(15558);
        internalCounters.push_back(15643);
        internalCounters.push_back(15728);
        internalCounters.push_back(15813);
        internalCounters.push_back(15898);
        internalCounters.push_back(15983);
        internalCounters.push_back(16068);

        c.DefineDerivedCounter("CSMemUnitStalledCycles", "ComputeShader", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ENGINES,/", "51991c84-ed2b-bf31-c4ab-8f8e9eb8f29f");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14847);
        internalCounters.push_back(14932);
        internalCounters.push_back(15017);
        internalCounters.push_back(15102);
        internalCounters.push_back(15187);
        internalCounters.push_back(15272);
        internalCounters.push_back(15357);
        internalCounters.push_back(15442);
        internalCounters.push_back(15527);
        internalCounters.push_back(15612);
        internalCounters.push_back(15697);
        internalCounters.push_back(15782);
        internalCounters.push_back(15867);
        internalCounters.push_back(15952);
        internalCounters.push_back(16037);
        internalCounters.push_back(16122);
        internalCounters.push_back(14856);
        internalCounters.push_back(14941);
        internalCounters.push_back(15026);
        internalCounters.push_back(15111);
        internalCounters.push_back(15196);
        internalCounters.push_back(15281);
        internalCounters.push_back(15366);
        internalCounters.push_back(15451);
        internalCounters.push_back(15536);
        internalCounters.push_back(15621);
        internalCounters.push_back(15706);
        internalCounters.push_back(15791);
        internalCounters.push_back(15876);
        internalCounters.push_back(15961);
        internalCounters.push_back(16046);
        internalCounters.push_back(16131);
        internalCounters.push_back(14857);
        internalCounters.push_back(14942);
        internalCounters.push_back(15027);
        internalCounters.push_back(15112);
        internalCounters.push_back(15197);
        internalCounters.push_back(15282);
        internalCounters.push_back(15367);
        internalCounters.push_back(15452);
        internalCounters.push_back(15537);
        internalCounters.push_back(15622);
        internalCounters.push_back(15707);
        internalCounters.push_back(15792);
        internalCounters.push_back(15877);
        internalCounters.push_back(15962);
        internalCounters.push_back(16047);
        internalCounters.push_back(16132);
        internalCounters.push_back(14858);
        internalCounters.push_back(14943);
        internalCounters.push_back(15028);
        internalCounters.push_back(15113);
        internalCounters.push_back(15198);
        internalCounters.push_back(15283);
        internalCounters.push_back(15368);
        internalCounters.push_back(15453);
        internalCounters.push_back(15538);
        internalCounters.push_back(15623);
        internalCounters.push_back(15708);
        internalCounters.push_back(15793);
        internalCounters.push_back(15878);
        internalCounters.push_back(15963);
        internalCounters.push_back(16048);
        internalCounters.push_back(16133);
        internalCounters.push_back(14859);
        internalCounters.push_back(14944);
        internalCounters.push_back(15029);
        internalCounters.push_back(15114);
        internalCounters.push_back(15199);
        internalCounters.push_back(15284);
        internalCounters.push_back(15369);
        internalCounters.push_back(15454);
        internalCounters.push_back(15539);
        internalCounters.push_back(15624);
        internalCounters.push_back(15709);
        internalCounters.push_back(15794);
        internalCounters.push_back(15879);
        internalCounters.push_back(15964);
        internalCounters.push_back(16049);
        internalCounters.push_back(16134);

        c.DefineDerivedCounter("L1CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum64,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "6deaf002-3cac-2d2d-7b89-566c7a52b08e");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14847);
        internalCounters.push_back(14932);
        internalCounters.push_back(15017);
        internalCounters.push_back(15102);
        internalCounters.push_back(15187);
        internalCounters.push_back(15272);
        internalCounters.push_back(15357);
        internalCounters.push_back(15442);
        internalCounters.push_back(15527);
        internalCounters.push_back(15612);
        internalCounters.push_back(15697);
        internalCounters.push_back(15782);
        internalCounters.push_back(15867);
        internalCounters.push_back(15952);
        internalCounters.push_back(16037);
        internalCounters.push_back(16122);
        internalCounters.push_back(14856);
        internalCounters.push_back(14941);
        internalCounters.push_back(15026);
        internalCounters.push_back(15111);
        internalCounters.push_back(15196);
        internalCounters.push_back(15281);
        internalCounters.push_back(15366);
        internalCounters.push_back(15451);
        internalCounters.push_back(15536);
        internalCounters.push_back(15621);
        internalCounters.push_back(15706);
        internalCounters.push_back(15791);
        internalCounters.push_back(15876);
        internalCounters.push_back(15961);
        internalCounters.push_back(16046);
        internalCounters.push_back(16131);
        internalCounters.push_back(14857);
        internalCounters.push_back(14942);
        internalCounters.push_back(15027);
        internalCounters.push_back(15112);
        internalCounters.push_back(15197);
        internalCounters.push_back(15282);
        internalCounters.push_back(15367);
        internalCounters.push_back(15452);
        internalCounters.push_back(15537);
        internalCounters.push_back(15622);
        internalCounters.push_back(15707);
        internalCounters.push_back(15792);
        internalCounters.push_back(15877);
        internalCounters.push_back(15962);
        internalCounters.push_back(16047);
        internalCounters.push_back(16132);
        internalCounters.push_back(14858);
        internalCounters.push_back(14943);
        internalCounters.push_back(15028);
        internalCounters.push_back(15113);
        internalCounters.push_back(15198);
        internalCounters.push_back(15283);
        internalCounters.push_back(15368);
        internalCounters.push_back(15453);
        internalCounters.push_back(15538);
        internalCounters.push_back(15623);
        internalCounters.push_back(15708);
        internalCounters.push_back(15793);
        internalCounters.push_back(15878);
        internalCounters.push_back(15963);
        internalCounters.push_back(16048);
        internalCounters.push_back(16133);
        internalCounters.push_back(14859);
        internalCounters.push_back(14944);
        internalCounters.push_back(15029);
        internalCounters.push_back(15114);
        internalCounters.push_back(15199);
        internalCounters.push_back(15284);
        internalCounters.push_back(15369);
        internalCounters.push_back(15454);
        internalCounters.push_back(15539);
        internalCounters.push_back(15624);
        internalCounters.push_back(15709);
        internalCounters.push_back(15794);
        internalCounters.push_back(15879);
        internalCounters.push_back(15964);
        internalCounters.push_back(16049);
        internalCounters.push_back(16134);

        c.DefineDerivedCounter("L1CacheHitCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that hit the data in L1 cache.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum64,-", "279c8bff-ec6a-f9bf-96d7-5e8000f77891");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14856);
        internalCounters.push_back(14941);
        internalCounters.push_back(15026);
        internalCounters.push_back(15111);
        internalCounters.push_back(15196);
        internalCounters.push_back(15281);
        internalCounters.push_back(15366);
        internalCounters.push_back(15451);
        internalCounters.push_back(15536);
        internalCounters.push_back(15621);
        internalCounters.push_back(15706);
        internalCounters.push_back(15791);
        internalCounters.push_back(15876);
        internalCounters.push_back(15961);
        internalCounters.push_back(16046);
        internalCounters.push_back(16131);
        internalCounters.push_back(14857);
        internalCounters.push_back(14942);
        internalCounters.push_back(15027);
        internalCounters.push_back(15112);
        internalCounters.push_back(15197);
        internalCounters.push_back(15282);
        internalCounters.push_back(15367);
        internalCounters.push_back(15452);
        internalCounters.push_back(15537);
        internalCounters.push_back(15622);
        internalCounters.push_back(15707);
        internalCounters.push_back(15792);
        internalCounters.push_back(15877);
        internalCounters.push_back(15962);
        internalCounters.push_back(16047);
        internalCounters.push_back(16132);
        internalCounters.push_back(14858);
        internalCounters.push_back(14943);
        internalCounters.push_back(15028);
        internalCounters.push_back(15113);
        internalCounters.push_back(15198);
        internalCounters.push_back(15283);
        internalCounters.push_back(15368);
        internalCounters.push_back(15453);
        internalCounters.push_back(15538);
        internalCounters.push_back(15623);
        internalCounters.push_back(15708);
        internalCounters.push_back(15793);
        internalCounters.push_back(15878);
        internalCounters.push_back(15963);
        internalCounters.push_back(16048);
        internalCounters.push_back(16133);
        internalCounters.push_back(14859);
        internalCounters.push_back(14944);
        internalCounters.push_back(15029);
        internalCounters.push_back(15114);
        internalCounters.push_back(15199);
        internalCounters.push_back(15284);
        internalCounters.push_back(15369);
        internalCounters.push_back(15454);
        internalCounters.push_back(15539);
        internalCounters.push_back(15624);
        internalCounters.push_back(15709);
        internalCounters.push_back(15794);
        internalCounters.push_back(15879);
        internalCounters.push_back(15964);
        internalCounters.push_back(16049);
        internalCounters.push_back(16134);

        c.DefineDerivedCounter("L1CacheMissCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that miss the data in L1 cache.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64", "6e4ee364-41d7-476d-361d-f47b266c15db");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9396);
        internalCounters.push_back(9678);
        internalCounters.push_back(9960);
        internalCounters.push_back(10242);
        internalCounters.push_back(10524);
        internalCounters.push_back(10806);
        internalCounters.push_back(11088);
        internalCounters.push_back(11370);
        internalCounters.push_back(11652);
        internalCounters.push_back(11934);
        internalCounters.push_back(12216);
        internalCounters.push_back(12498);
        internalCounters.push_back(12780);
        internalCounters.push_back(13062);
        internalCounters.push_back(13344);
        internalCounters.push_back(13626);

        c.DefineDerivedCounter("CSWriteUnitStalledCycles", "ComputeShader", "Number of GPU cycles the write unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "be164c60-5e48-acac-9622-29616d09aa9a");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6842);
        internalCounters.push_back(6811);

        c.DefineDerivedCounter("CSGDSInsts", "ComputeShader", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "2a867f3e-4a37-ad16-55d1-f03d74707819");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6841);
        internalCounters.push_back(6840);
        internalCounters.push_back(6811);

        c.DefineDerivedCounter("CSLDSInsts", "ComputeShader", "The average number of LDS read/write instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,-,2,/,2,ifnotzero", "61b0b351-7e06-ef8e-a8e0-7a9e3200a836");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6840);
        internalCounters.push_back(6811);

        c.DefineDerivedCounter("CSFlatLDSInsts", "ComputeShader", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "99672cda-de2b-014c-482e-cf73b90068d5");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4252);
        internalCounters.push_back(4193);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("CSALUStalledByLDS", "ComputeShader", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,/,2,/,NUM_SHADER_ENGINES,/,(100),*,1,ifnotzero", "6dc4f1c2-bad0-c9ff-156e-883b319a752a");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4252);

        c.DefineDerivedCounter("CSALUStalledByLDSCycles", "ComputeShader", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_SHADER_ENGINES,/", "8f3d5f25-2159-0374-fafe-e26a7799b6c8");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6900);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("CSLDSBankConflict", "ComputeShader", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*", "1065ee10-2e41-ea41-1eb3-b61b491752f4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6900);

        c.DefineDerivedCounter("CSLDSBankConflictCycles", "ComputeShader", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_SIMDS,/", "1fd1adf3-c51e-94fd-083e-c482a0a0809e");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7404);
        internalCounters.push_back(7523);
        internalCounters.push_back(7642);
        internalCounters.push_back(7761);
        internalCounters.push_back(7880);
        internalCounters.push_back(7999);
        internalCounters.push_back(8118);
        internalCounters.push_back(8237);
        internalCounters.push_back(8356);
        internalCounters.push_back(8475);
        internalCounters.push_back(8594);
        internalCounters.push_back(8713);
        internalCounters.push_back(8832);
        internalCounters.push_back(8951);
        internalCounters.push_back(9070);
        internalCounters.push_back(9189);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("TexUnitBusy", "Timing", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "36afb8d9-42fc-aafe-66c5-449542153b2c");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7404);
        internalCounters.push_back(7523);
        internalCounters.push_back(7642);
        internalCounters.push_back(7761);
        internalCounters.push_back(7880);
        internalCounters.push_back(7999);
        internalCounters.push_back(8118);
        internalCounters.push_back(8237);
        internalCounters.push_back(8356);
        internalCounters.push_back(8475);
        internalCounters.push_back(8594);
        internalCounters.push_back(8713);
        internalCounters.push_back(8832);
        internalCounters.push_back(8951);
        internalCounters.push_back(9070);
        internalCounters.push_back(9189);

        c.DefineDerivedCounter("TexUnitBusyCycles", "Timing", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ENGINES,/", "c68761f2-248c-4f39-6528-c308b1c0807c");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7458);
        internalCounters.push_back(7577);
        internalCounters.push_back(7696);
        internalCounters.push_back(7815);
        internalCounters.push_back(7934);
        internalCounters.push_back(8053);
        internalCounters.push_back(8172);
        internalCounters.push_back(8291);
        internalCounters.push_back(8410);
        internalCounters.push_back(8529);
        internalCounters.push_back(8648);
        internalCounters.push_back(8767);
        internalCounters.push_back(8886);
        internalCounters.push_back(9005);
        internalCounters.push_back(9124);
        internalCounters.push_back(9243);
        internalCounters.push_back(7457);
        internalCounters.push_back(7576);
        internalCounters.push_back(7695);
        internalCounters.push_back(7814);
        internalCounters.push_back(7933);
        internalCounters.push_back(8052);
        internalCounters.push_back(8171);
        internalCounters.push_back(8290);
        internalCounters.push_back(8409);
        internalCounters.push_back(8528);
        internalCounters.push_back(8647);
        internalCounters.push_back(8766);
        internalCounters.push_back(8885);
        internalCounters.push_back(9004);
        internalCounters.push_back(9123);
        internalCounters.push_back(9242);

        c.DefineDerivedCounter("TexTriFilteringPct", "TextureUnit", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,+,/,(100),*", "1affc3c8-b917-5c81-622b-7004527208ae");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7458);
        internalCounters.push_back(7577);
        internalCounters.push_back(7696);
        internalCounters.push_back(7815);
        internalCounters.push_back(7934);
        internalCounters.push_back(8053);
        internalCounters.push_back(8172);
        internalCounters.push_back(8291);
        internalCounters.push_back(8410);
        internalCounters.push_back(8529);
        internalCounters.push_back(8648);
        internalCounters.push_back(8767);
        internalCounters.push_back(8886);
        internalCounters.push_back(9005);
        internalCounters.push_back(9124);
        internalCounters.push_back(9243);

        c.DefineDerivedCounter("TexTriFilteringCount", "TextureUnit", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "5785b3a1-a513-18db-4b1c-bdeef75bb2b6");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7457);
        internalCounters.push_back(7576);
        internalCounters.push_back(7695);
        internalCounters.push_back(7814);
        internalCounters.push_back(7933);
        internalCounters.push_back(8052);
        internalCounters.push_back(8171);
        internalCounters.push_back(8290);
        internalCounters.push_back(8409);
        internalCounters.push_back(8528);
        internalCounters.push_back(8647);
        internalCounters.push_back(8766);
        internalCounters.push_back(8885);
        internalCounters.push_back(9004);
        internalCounters.push_back(9123);
        internalCounters.push_back(9242);

        c.DefineDerivedCounter("NoTexTriFilteringCount", "TextureUnit", "Count of pixels that did not receive trilinear filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "179da29a-81af-c06e-ce8c-a0a731ea030d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7460);
        internalCounters.push_back(7579);
        internalCounters.push_back(7698);
        internalCounters.push_back(7817);
        internalCounters.push_back(7936);
        internalCounters.push_back(8055);
        internalCounters.push_back(8174);
        internalCounters.push_back(8293);
        internalCounters.push_back(8412);
        internalCounters.push_back(8531);
        internalCounters.push_back(8650);
        internalCounters.push_back(8769);
        internalCounters.push_back(8888);
        internalCounters.push_back(9007);
        internalCounters.push_back(9126);
        internalCounters.push_back(9245);
        internalCounters.push_back(7459);
        internalCounters.push_back(7578);
        internalCounters.push_back(7697);
        internalCounters.push_back(7816);
        internalCounters.push_back(7935);
        internalCounters.push_back(8054);
        internalCounters.push_back(8173);
        internalCounters.push_back(8292);
        internalCounters.push_back(8411);
        internalCounters.push_back(8530);
        internalCounters.push_back(8649);
        internalCounters.push_back(8768);
        internalCounters.push_back(8887);
        internalCounters.push_back(9006);
        internalCounters.push_back(9125);
        internalCounters.push_back(9244);

        c.DefineDerivedCounter("TexVolFilteringPct", "TextureUnit", "Percentage of pixels that received volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,+,/,(100),*", "b5ff6bed-3178-aee4-42dd-c74391c02a2d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7460);
        internalCounters.push_back(7579);
        internalCounters.push_back(7698);
        internalCounters.push_back(7817);
        internalCounters.push_back(7936);
        internalCounters.push_back(8055);
        internalCounters.push_back(8174);
        internalCounters.push_back(8293);
        internalCounters.push_back(8412);
        internalCounters.push_back(8531);
        internalCounters.push_back(8650);
        internalCounters.push_back(8769);
        internalCounters.push_back(8888);
        internalCounters.push_back(9007);
        internalCounters.push_back(9126);
        internalCounters.push_back(9245);

        c.DefineDerivedCounter("TexVolFilteringCount", "TextureUnit", "Count of pixels that received volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "4bddc587-d589-8128-e18c-762eab2c871f");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7459);
        internalCounters.push_back(7578);
        internalCounters.push_back(7697);
        internalCounters.push_back(7816);
        internalCounters.push_back(7935);
        internalCounters.push_back(8054);
        internalCounters.push_back(8173);
        internalCounters.push_back(8292);
        internalCounters.push_back(8411);
        internalCounters.push_back(8530);
        internalCounters.push_back(8649);
        internalCounters.push_back(8768);
        internalCounters.push_back(8887);
        internalCounters.push_back(9006);
        internalCounters.push_back(9125);
        internalCounters.push_back(9244);

        c.DefineDerivedCounter("NoTexVolFilteringCount", "TextureUnit", "Count of pixels that did not receive volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "9fe1a854-17c6-9d26-b2b9-80610cd5827d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7478);
        internalCounters.push_back(7597);
        internalCounters.push_back(7716);
        internalCounters.push_back(7835);
        internalCounters.push_back(7954);
        internalCounters.push_back(8073);
        internalCounters.push_back(8192);
        internalCounters.push_back(8311);
        internalCounters.push_back(8430);
        internalCounters.push_back(8549);
        internalCounters.push_back(8668);
        internalCounters.push_back(8787);
        internalCounters.push_back(8906);
        internalCounters.push_back(9025);
        internalCounters.push_back(9144);
        internalCounters.push_back(9263);
        internalCounters.push_back(7479);
        internalCounters.push_back(7598);
        internalCounters.push_back(7717);
        internalCounters.push_back(7836);
        internalCounters.push_back(7955);
        internalCounters.push_back(8074);
        internalCounters.push_back(8193);
        internalCounters.push_back(8312);
        internalCounters.push_back(8431);
        internalCounters.push_back(8550);
        internalCounters.push_back(8669);
        internalCounters.push_back(8788);
        internalCounters.push_back(8907);
        internalCounters.push_back(9026);
        internalCounters.push_back(9145);
        internalCounters.push_back(9264);
        internalCounters.push_back(7480);
        internalCounters.push_back(7599);
        internalCounters.push_back(7718);
        internalCounters.push_back(7837);
        internalCounters.push_back(7956);
        internalCounters.push_back(8075);
        internalCounters.push_back(8194);
        internalCounters.push_back(8313);
        internalCounters.push_back(8432);
        internalCounters.push_back(8551);
        internalCounters.push_back(8670);
        internalCounters.push_back(8789);
        internalCounters.push_back(8908);
        internalCounters.push_back(9027);
        internalCounters.push_back(9146);
        internalCounters.push_back(9265);
        internalCounters.push_back(7481);
        internalCounters.push_back(7600);
        internalCounters.push_back(7719);
        internalCounters.push_back(7838);
        internalCounters.push_back(7957);
        internalCounters.push_back(8076);
        internalCounters.push_back(8195);
        internalCounters.push_back(8314);
        internalCounters.push_back(8433);
        internalCounters.push_back(8552);
        internalCounters.push_back(8671);
        internalCounters.push_back(8790);
        internalCounters.push_back(8909);
        internalCounters.push_back(9028);
        internalCounters.push_back(9147);
        internalCounters.push_back(9266);
        internalCounters.push_back(7482);
        internalCounters.push_back(7601);
        internalCounters.push_back(7720);
        internalCounters.push_back(7839);
        internalCounters.push_back(7958);
        internalCounters.push_back(8077);
        internalCounters.push_back(8196);
        internalCounters.push_back(8315);
        internalCounters.push_back(8434);
        internalCounters.push_back(8553);
        internalCounters.push_back(8672);
        internalCounters.push_back(8791);
        internalCounters.push_back(8910);
        internalCounters.push_back(9029);
        internalCounters.push_back(9148);
        internalCounters.push_back(9267);
        internalCounters.push_back(7483);
        internalCounters.push_back(7602);
        internalCounters.push_back(7721);
        internalCounters.push_back(7840);
        internalCounters.push_back(7959);
        internalCounters.push_back(8078);
        internalCounters.push_back(8197);
        internalCounters.push_back(8316);
        internalCounters.push_back(8435);
        internalCounters.push_back(8554);
        internalCounters.push_back(8673);
        internalCounters.push_back(8792);
        internalCounters.push_back(8911);
        internalCounters.push_back(9030);
        internalCounters.push_back(9149);
        internalCounters.push_back(9268);
        internalCounters.push_back(7484);
        internalCounters.push_back(7603);
        internalCounters.push_back(7722);
        internalCounters.push_back(7841);
        internalCounters.push_back(7960);
        internalCounters.push_back(8079);
        internalCounters.push_back(8198);
        internalCounters.push_back(8317);
        internalCounters.push_back(8436);
        internalCounters.push_back(8555);
        internalCounters.push_back(8674);
        internalCounters.push_back(8793);
        internalCounters.push_back(8912);
        internalCounters.push_back(9031);
        internalCounters.push_back(9150);
        internalCounters.push_back(9269);
        internalCounters.push_back(7485);
        internalCounters.push_back(7604);
        internalCounters.push_back(7723);
        internalCounters.push_back(7842);
        internalCounters.push_back(7961);
        internalCounters.push_back(8080);
        internalCounters.push_back(8199);
        internalCounters.push_back(8318);
        internalCounters.push_back(8437);
        internalCounters.push_back(8556);
        internalCounters.push_back(8675);
        internalCounters.push_back(8794);
        internalCounters.push_back(8913);
        internalCounters.push_back(9032);
        internalCounters.push_back(9151);
        internalCounters.push_back(9270);
        internalCounters.push_back(7486);
        internalCounters.push_back(7605);
        internalCounters.push_back(7724);
        internalCounters.push_back(7843);
        internalCounters.push_back(7962);
        internalCounters.push_back(8081);
        internalCounters.push_back(8200);
        internalCounters.push_back(8319);
        internalCounters.push_back(8438);
        internalCounters.push_back(8557);
        internalCounters.push_back(8676);
        internalCounters.push_back(8795);
        internalCounters.push_back(8914);
        internalCounters.push_back(9033);
        internalCounters.push_back(9152);
        internalCounters.push_back(9271);

        c.DefineDerivedCounter("TexAveAnisotropy", "TextureUnit", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(2),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,*,+,(4),32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,*,+,(6),48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,*,+,(8),64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,*,+,(10),80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,*,+,(12),96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,*,+,(14),112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,*,+,(16),128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,*,+,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,+,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,+,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,+,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,+,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,+,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,+,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,+,/", "7ca2a2b9-a4eb-ce23-d163-59147e672396");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1928);
        internalCounters.push_back(2256);
        internalCounters.push_back(2584);
        internalCounters.push_back(2912);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("DepthStencilTestBusy", "Timing", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "6834fb52-42e8-bb50-fd48-ec2f2904e7e0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1928);
        internalCounters.push_back(2256);
        internalCounters.push_back(2584);
        internalCounters.push_back(2912);

        c.DefineDerivedCounter("DepthStencilTestBusyCount", "Timing", "Number of GPU cycles spent performing depth and stencil tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "e02860fa-c7bd-90ea-2149-69b4e98a636c");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1799);
        internalCounters.push_back(2127);
        internalCounters.push_back(2455);
        internalCounters.push_back(2783);
        internalCounters.push_back(1788);
        internalCounters.push_back(2116);
        internalCounters.push_back(2444);
        internalCounters.push_back(2772);

        c.DefineDerivedCounter("HiZTilesAccepted", "DepthAndStencil", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*", "56176f45-d7ff-813d-4f05-3b2f046067e7");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1799);
        internalCounters.push_back(2127);
        internalCounters.push_back(2455);
        internalCounters.push_back(2783);

        c.DefineDerivedCounter("HiZTilesAcceptedCount", "DepthAndStencil", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "95d4e3f6-b2f0-f26e-8423-aacdfaf79ea3");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1788);
        internalCounters.push_back(2116);
        internalCounters.push_back(2444);
        internalCounters.push_back(2772);

        c.DefineDerivedCounter("HiZTilesRejectedCount", "DepthAndStencil", "Count of tiles not accepted by HiZ.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "156ba142-7eeb-aa6e-a00a-f8aea4e41e0b");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1788);
        internalCounters.push_back(2116);
        internalCounters.push_back(2444);
        internalCounters.push_back(2772);
        internalCounters.push_back(1812);
        internalCounters.push_back(2140);
        internalCounters.push_back(2468);
        internalCounters.push_back(2796);

        c.DefineDerivedCounter("PreZTilesDetailCulled", "DepthAndStencil", "Percentage of tiles rejected because the associated prim had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "4,5,6,7,sum4,0,1,2,3,sum4,/,(100),*", "cad7f54d-a044-7574-c472-6f2065cbeeac");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1812);
        internalCounters.push_back(2140);
        internalCounters.push_back(2468);
        internalCounters.push_back(2796);

        c.DefineDerivedCounter("PreZTilesDetailCulledCount", "DepthAndStencil", "Count of tiles rejected because the associated primitive had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "49262c8a-b1e6-90dd-f096-0fc4921715e9");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1788);
        internalCounters.push_back(2116);
        internalCounters.push_back(2444);
        internalCounters.push_back(2772);

        c.DefineDerivedCounter("PreZTilesDetailSurvivingCount", "DepthAndStencil", "Count of tiles surviving because the associated primitive had contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "f803eaa4-bbed-bd39-775f-a64df92e2c08");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3660);
        internalCounters.push_back(3661);
        internalCounters.push_back(3662);
        internalCounters.push_back(3663);
        internalCounters.push_back(3736);
        internalCounters.push_back(3737);
        internalCounters.push_back(3738);
        internalCounters.push_back(3739);

        c.DefineDerivedCounter("HiZQuadsCulled", "DepthAndStencil", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-,0,1,+,2,+,3,+,/,(100),*", "fa0e319b-5573-6d34-5bab-904769925036");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3660);
        internalCounters.push_back(3661);
        internalCounters.push_back(3662);
        internalCounters.push_back(3663);
        internalCounters.push_back(3736);
        internalCounters.push_back(3737);
        internalCounters.push_back(3738);
        internalCounters.push_back(3739);

        c.DefineDerivedCounter("HiZQuadsCulledCount", "DepthAndStencil", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-", "73b0b39d-6df2-3e24-0b5c-7cb0ac8b6f39");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3736);
        internalCounters.push_back(3737);
        internalCounters.push_back(3738);
        internalCounters.push_back(3739);

        c.DefineDerivedCounter("HiZQuadsAcceptedCount", "DepthAndStencil", "Count of quads that did continue on in the pipeline after HiZ.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+", "59049ad9-42b5-c7cb-3616-6a8f6a8e4894");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3660);
        internalCounters.push_back(3661);
        internalCounters.push_back(3662);
        internalCounters.push_back(3663);
        internalCounters.push_back(3760);
        internalCounters.push_back(3736);
        internalCounters.push_back(3737);
        internalCounters.push_back(3738);
        internalCounters.push_back(3739);

        c.DefineDerivedCounter("PreZQuadsCulled", "DepthAndStencil", "Percentage of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "5,6,+,7,+,8,+,4,-,0,1,+,2,+,3,+,/,(100),*", "4e77547b-ec55-5663-f034-af59be66d77d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3660);
        internalCounters.push_back(3661);
        internalCounters.push_back(3662);
        internalCounters.push_back(3663);
        internalCounters.push_back(3760);
        internalCounters.push_back(3736);
        internalCounters.push_back(3737);
        internalCounters.push_back(3738);
        internalCounters.push_back(3739);

        c.DefineDerivedCounter("PreZQuadsCulledCount", "DepthAndStencil", "Count of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+,4,-,5,-,6,-,7,-,8,-", "1bf169e6-9304-834e-df5f-0c44d7890a08");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3760);
        internalCounters.push_back(3736);
        internalCounters.push_back(3737);
        internalCounters.push_back(3738);
        internalCounters.push_back(3739);

        c.DefineDerivedCounter("PreZQuadsSurvivingCount", "DepthAndStencil", "Count of quads surviving detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "1,2,+,3,+,4,+,0,-", "50e25e51-3713-89cb-7f92-559cde5e5532");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3760);
        internalCounters.push_back(3660);
        internalCounters.push_back(3661);
        internalCounters.push_back(3662);
        internalCounters.push_back(3663);

        c.DefineDerivedCounter("PostZQuads", "DepthAndStencil", "Percentage of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,+,3,+,4,+,/,(100),*", "58f0d34b-eeb8-e8db-abce-cb72584144be");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3760);

        c.DefineDerivedCounter("PostZQuadCount", "DepthAndStencil", "Count of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "08404526-ce35-939b-34c8-a7a35a0ff4d6");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1961);
        internalCounters.push_back(2289);
        internalCounters.push_back(2617);
        internalCounters.push_back(2945);

        c.DefineDerivedCounter("PreZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z before shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "3bfe6c4d-7422-ca03-7ea5-e67ff1a00136");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1963);
        internalCounters.push_back(2291);
        internalCounters.push_back(2619);
        internalCounters.push_back(2947);

        c.DefineDerivedCounter("PreZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z before shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "df7f705e-5162-d3b5-da8b-63466cf9c4e5");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1962);
        internalCounters.push_back(2290);
        internalCounters.push_back(2618);
        internalCounters.push_back(2946);

        c.DefineDerivedCounter("PreZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z before shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "4484e950-f7a4-3800-bc74-78dd297f017e");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1958);
        internalCounters.push_back(2286);
        internalCounters.push_back(2614);
        internalCounters.push_back(2942);

        c.DefineDerivedCounter("PostZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z after shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "4995d5d6-2330-b986-508b-fae24856f44c");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1960);
        internalCounters.push_back(2288);
        internalCounters.push_back(2616);
        internalCounters.push_back(2944);

        c.DefineDerivedCounter("PostZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z after shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "ae558af4-f4be-3dd4-7316-b2c4dcf0def8");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1959);
        internalCounters.push_back(2287);
        internalCounters.push_back(2615);
        internalCounters.push_back(2943);

        c.DefineDerivedCounter("PostZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z after shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "b3684c94-814a-c695-c85d-a5b6ab798b35");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1830);
        internalCounters.push_back(2158);
        internalCounters.push_back(2486);
        internalCounters.push_back(2814);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("ZUnitStalled", "DepthAndStencil", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "5e86c3ad-1726-3157-1d01-7ed188bf854d");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1830);
        internalCounters.push_back(2158);
        internalCounters.push_back(2486);
        internalCounters.push_back(2814);

        c.DefineDerivedCounter("ZUnitStalledCycles", "DepthAndStencil", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "4351fa7f-6737-2c3e-3ffb-b3addbdceedd");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1832);
        internalCounters.push_back(2160);
        internalCounters.push_back(2488);
        internalCounters.push_back(2816);
        internalCounters.push_back(1839);
        internalCounters.push_back(2167);
        internalCounters.push_back(2495);
        internalCounters.push_back(2823);

        c.DefineDerivedCounter("DBMemRead", "DepthAndStencil", "Number of bytes read from the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,sum4,(256),*,4,5,6,7,sum4,(32),*,+", "dcdb4ee7-bd50-00f7-c028-9e5f4ce888c0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1844);
        internalCounters.push_back(2172);
        internalCounters.push_back(2500);
        internalCounters.push_back(2828);
        internalCounters.push_back(1847);
        internalCounters.push_back(2175);
        internalCounters.push_back(2503);
        internalCounters.push_back(2831);

        c.DefineDerivedCounter("DBMemWritten", "DepthAndStencil", "Number of bytes written to the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,sum4,(32),*,4,5,6,7,sum4,(32),*,+", "de5717f8-8a49-ee44-4645-10de51b37dcf");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(128);
        internalCounters.push_back(566);
        internalCounters.push_back(1004);
        internalCounters.push_back(1442);

        c.DefineDerivedCounter("CBMemRead", "ColorBuffer", "Number of bytes read from the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,sum4,(32),*", "84b531d8-a1f8-7f49-7c27-7bc97801f1e6");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(259);
        internalCounters.push_back(697);
        internalCounters.push_back(1135);
        internalCounters.push_back(1573);
        internalCounters.push_back(126);
        internalCounters.push_back(564);
        internalCounters.push_back(1002);
        internalCounters.push_back(1440);
        internalCounters.push_back(127);
        internalCounters.push_back(565);
        internalCounters.push_back(1003);
        internalCounters.push_back(1441);
        internalCounters.push_back(128);
        internalCounters.push_back(566);
        internalCounters.push_back(1004);
        internalCounters.push_back(1442);

        c.DefineDerivedCounter("CBColorAndMaskRead", "ColorBuffer", "Total number of bytes read from the color and mask buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "da41660e-eb6f-32ec-8a64-b32ca17bd7eb");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(118);
        internalCounters.push_back(556);
        internalCounters.push_back(994);
        internalCounters.push_back(1432);

        c.DefineDerivedCounter("CBMemWritten", "ColorBuffer", "Number of bytes written to the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,sum4,(32),*", "550f8ff8-60b6-a6bf-87d0-25ac9e87de70");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(257);
        internalCounters.push_back(695);
        internalCounters.push_back(1133);
        internalCounters.push_back(1571);
        internalCounters.push_back(116);
        internalCounters.push_back(554);
        internalCounters.push_back(992);
        internalCounters.push_back(1430);
        internalCounters.push_back(117);
        internalCounters.push_back(555);
        internalCounters.push_back(993);
        internalCounters.push_back(1431);
        internalCounters.push_back(118);
        internalCounters.push_back(556);
        internalCounters.push_back(994);
        internalCounters.push_back(1432);

        c.DefineDerivedCounter("CBColorAndMaskWritten", "ColorBuffer", "Total number of bytes written to the color and mask buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "29a04b69-8f5f-b770-a0f2-3453e2c99e49");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(162);
        internalCounters.push_back(600);
        internalCounters.push_back(1038);
        internalCounters.push_back(1476);
        internalCounters.push_back(7);
        internalCounters.push_back(445);
        internalCounters.push_back(883);
        internalCounters.push_back(1321);

        c.DefineDerivedCounter("CBSlowPixelPct", "ColorBuffer", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*,(100),min", "5775943f-0313-7e52-9638-b24a449197bc");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(162);
        internalCounters.push_back(600);
        internalCounters.push_back(1038);
        internalCounters.push_back(1476);

        c.DefineDerivedCounter("CBSlowPixelCount", "ColorBuffer", "Number of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "47eacbb0-28c8-22b4-5c69-c00d5813bb1c");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9404);
        internalCounters.push_back(9686);
        internalCounters.push_back(9968);
        internalCounters.push_back(10250);
        internalCounters.push_back(10532);
        internalCounters.push_back(10814);
        internalCounters.push_back(11096);
        internalCounters.push_back(11378);
        internalCounters.push_back(11660);
        internalCounters.push_back(11942);
        internalCounters.push_back(12224);
        internalCounters.push_back(12506);
        internalCounters.push_back(12788);
        internalCounters.push_back(13070);
        internalCounters.push_back(13352);
        internalCounters.push_back(13634);
        internalCounters.push_back(9405);
        internalCounters.push_back(9687);
        internalCounters.push_back(9969);
        internalCounters.push_back(10251);
        internalCounters.push_back(10533);
        internalCounters.push_back(10815);
        internalCounters.push_back(11097);
        internalCounters.push_back(11379);
        internalCounters.push_back(11661);
        internalCounters.push_back(11943);
        internalCounters.push_back(12225);
        internalCounters.push_back(12507);
        internalCounters.push_back(12789);
        internalCounters.push_back(13071);
        internalCounters.push_back(13353);
        internalCounters.push_back(13635);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total bytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(64),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+", "664bb3ef-6eca-86b1-1e2d-30cb897b5fa9");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9392);
        internalCounters.push_back(9674);
        internalCounters.push_back(9956);
        internalCounters.push_back(10238);
        internalCounters.push_back(10520);
        internalCounters.push_back(10802);
        internalCounters.push_back(11084);
        internalCounters.push_back(11366);
        internalCounters.push_back(11648);
        internalCounters.push_back(11930);
        internalCounters.push_back(12212);
        internalCounters.push_back(12494);
        internalCounters.push_back(12776);
        internalCounters.push_back(13058);
        internalCounters.push_back(13340);
        internalCounters.push_back(13622);
        internalCounters.push_back(9393);
        internalCounters.push_back(9675);
        internalCounters.push_back(9957);
        internalCounters.push_back(10239);
        internalCounters.push_back(10521);
        internalCounters.push_back(10803);
        internalCounters.push_back(11085);
        internalCounters.push_back(11367);
        internalCounters.push_back(11649);
        internalCounters.push_back(11931);
        internalCounters.push_back(12213);
        internalCounters.push_back(12495);
        internalCounters.push_back(12777);
        internalCounters.push_back(13059);
        internalCounters.push_back(13341);
        internalCounters.push_back(13623);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total bytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+", "f96f2c16-b1b4-4ec4-229c-fc82e6f80a82");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9383);
        internalCounters.push_back(9665);
        internalCounters.push_back(9947);
        internalCounters.push_back(10229);
        internalCounters.push_back(10511);
        internalCounters.push_back(10793);
        internalCounters.push_back(11075);
        internalCounters.push_back(11357);
        internalCounters.push_back(11639);
        internalCounters.push_back(11921);
        internalCounters.push_back(12203);
        internalCounters.push_back(12485);
        internalCounters.push_back(12767);
        internalCounters.push_back(13049);
        internalCounters.push_back(13331);
        internalCounters.push_back(13613);
        internalCounters.push_back(9385);
        internalCounters.push_back(9667);
        internalCounters.push_back(9949);
        internalCounters.push_back(10231);
        internalCounters.push_back(10513);
        internalCounters.push_back(10795);
        internalCounters.push_back(11077);
        internalCounters.push_back(11359);
        internalCounters.push_back(11641);
        internalCounters.push_back(11923);
        internalCounters.push_back(12205);
        internalCounters.push_back(12487);
        internalCounters.push_back(12769);
        internalCounters.push_back(13051);
        internalCounters.push_back(13333);
        internalCounters.push_back(13615);

        c.DefineDerivedCounter("L2CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the L2 cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "d78fdf66-104f-8372-02c1-91d07d7dc62e");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9383);
        internalCounters.push_back(9665);
        internalCounters.push_back(9947);
        internalCounters.push_back(10229);
        internalCounters.push_back(10511);
        internalCounters.push_back(10793);
        internalCounters.push_back(11075);
        internalCounters.push_back(11357);
        internalCounters.push_back(11639);
        internalCounters.push_back(11921);
        internalCounters.push_back(12203);
        internalCounters.push_back(12485);
        internalCounters.push_back(12767);
        internalCounters.push_back(13049);
        internalCounters.push_back(13331);
        internalCounters.push_back(13613);
        internalCounters.push_back(9385);
        internalCounters.push_back(9667);
        internalCounters.push_back(9949);
        internalCounters.push_back(10231);
        internalCounters.push_back(10513);
        internalCounters.push_back(10795);
        internalCounters.push_back(11077);
        internalCounters.push_back(11359);
        internalCounters.push_back(11641);
        internalCounters.push_back(11923);
        internalCounters.push_back(12205);
        internalCounters.push_back(12487);
        internalCounters.push_back(12769);
        internalCounters.push_back(13051);
        internalCounters.push_back(13333);
        internalCounters.push_back(13615);

        c.DefineDerivedCounter("L2CacheMiss", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that miss the L2 cache. Value range: 0% (optimal) to 100% (all miss).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "4cd70885-41b3-25cd-92db-c76a0decc634");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9383);
        internalCounters.push_back(9665);
        internalCounters.push_back(9947);
        internalCounters.push_back(10229);
        internalCounters.push_back(10511);
        internalCounters.push_back(10793);
        internalCounters.push_back(11075);
        internalCounters.push_back(11357);
        internalCounters.push_back(11639);
        internalCounters.push_back(11921);
        internalCounters.push_back(12203);
        internalCounters.push_back(12485);
        internalCounters.push_back(12767);
        internalCounters.push_back(13049);
        internalCounters.push_back(13331);
        internalCounters.push_back(13613);

        c.DefineDerivedCounter("L2CacheHitCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that hit the L2 cache.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "d0bce171-560c-1895-66b3-bc56abccb077");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9385);
        internalCounters.push_back(9667);
        internalCounters.push_back(9949);
        internalCounters.push_back(10231);
        internalCounters.push_back(10513);
        internalCounters.push_back(10795);
        internalCounters.push_back(11077);
        internalCounters.push_back(11359);
        internalCounters.push_back(11641);
        internalCounters.push_back(11923);
        internalCounters.push_back(12205);
        internalCounters.push_back(12487);
        internalCounters.push_back(12769);
        internalCounters.push_back(13051);
        internalCounters.push_back(13333);
        internalCounters.push_back(13615);

        c.DefineDerivedCounter("L2CacheMissCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that miss the L2 cache.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "f2ab3a1a-ead6-9893-961b-88ba2a758807");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7404);
        internalCounters.push_back(7523);
        internalCounters.push_back(7642);
        internalCounters.push_back(7761);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,max4,4,/,NUM_SHADER_ENGINES,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14793);
        internalCounters.push_back(14878);
        internalCounters.push_back(14963);
        internalCounters.push_back(15048);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,max4,4,/,NUM_SHADER_ENGINES,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9396);
        internalCounters.push_back(9678);
        internalCounters.push_back(9960);
        internalCounters.push_back(10242);
        internalCounters.push_back(10524);
        internalCounters.push_back(10806);
        internalCounters.push_back(11088);
        internalCounters.push_back(11370);
        internalCounters.push_back(11652);
        internalCounters.push_back(11934);
        internalCounters.push_back(12216);
        internalCounters.push_back(12498);
        internalCounters.push_back(12780);
        internalCounters.push_back(13062);
        internalCounters.push_back(13344);
        internalCounters.push_back(13626);
        internalCounters.push_back(3098);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
}

