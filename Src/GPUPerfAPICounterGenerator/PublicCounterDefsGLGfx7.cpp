//==============================================================================
// Copyright (c) 2010-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  PublicCounterDefinitions for GLGFX7
//==============================================================================

#include "PublicCounterDefsGLGfx7.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicCountersGLGfx7(GPA_PublicCounters& p)
{
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11279);

        p.DefinePublicCounter("GPUTime", "Timing", "Time this API call took to execute on the GPU in milliseconds. Does not include time that draw calls are processed in parallel.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_API_DYNAMIC, internalCounters, "0,TS_FREQ,/,(1000),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1951);
        internalCounters.push_back(1949);

        p.DefinePublicCounter("GPUBusy", "Timing", "The percentage of time GPU was busy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1951);

        p.DefinePublicCounter("GPUBusyCycles", "Timing", "Number of GPU cycles that the GPU was busy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11118);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("TessellatorBusy", "Timing", "The percentage of time the tessellation engine is busy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11118);

        p.DefinePublicCounter("TessellatorBusyCycles", "Timing", "Number of GPU cycles that the tessellation engine is busy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,NUM_PRIM_PIPES,/");
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

        p.DefinePublicCounter("VSBusy", "Timing", "The percentage of time the ShaderUnit has vertex shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,1,5,ifnotzero,2,6,ifnotzero,7,/,(100),*,(100),min");
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

        p.DefinePublicCounter("VSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has vertex shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,1,5,ifnotzero,2,6,ifnotzero");
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

        p.DefinePublicCounter("VSTime", "Timing", "Time vertex shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,5,ifnotzero,2,6,ifnotzero,3,7,ifnotzero,8,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2584);
        internalCounters.push_back(2590);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("HSBusy", "Timing", "The percentage of time the ShaderUnit has hull shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2584);
        internalCounters.push_back(2590);

        p.DefinePublicCounter("HSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has hull shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11279);
        internalCounters.push_back(2584);
        internalCounters.push_back(2590);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("HSTime", "Timing", "Time hull shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2547);
        internalCounters.push_back(2572);
        internalCounters.push_back(2616);
        internalCounters.push_back(2578);
        internalCounters.push_back(2600);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("DSBusy", "Timing", "The percentage of time the ShaderUnit has domain shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,5,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2547);
        internalCounters.push_back(2572);
        internalCounters.push_back(2616);
        internalCounters.push_back(2578);
        internalCounters.push_back(2600);

        p.DefinePublicCounter("DSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has domain shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero");
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

        p.DefinePublicCounter("DSTime", "Timing", "Time domain shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,4,ifnotzero,5,ifnotzero,6,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2563);
        internalCounters.push_back(2566);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("GSBusy", "Timing", "The percentage of time the ShaderUnit has geometry shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2563);
        internalCounters.push_back(2566);

        p.DefinePublicCounter("GSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has geometry shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11279);
        internalCounters.push_back(2563);
        internalCounters.push_back(2566);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("GSTime", "Timing", "Time geometry shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2616);
        internalCounters.push_back(2621);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("PSBusy", "Timing", "The percentage of time the ShaderUnit has pixel shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2616);
        internalCounters.push_back(2621);

        p.DefinePublicCounter("PSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has pixel shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11279);
        internalCounters.push_back(2616);
        internalCounters.push_back(2621);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("PSTime", "Timing", "Time pixel shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2604);
        internalCounters.push_back(2608);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("CSBusy", "Timing", "The percentage of time the ShaderUnit has compute shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2604);
        internalCounters.push_back(2608);

        p.DefinePublicCounter("CSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has compute shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11279);
        internalCounters.push_back(2604);
        internalCounters.push_back(2608);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("CSTime", "Timing", "Time compute shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11013);
        internalCounters.push_back(10994);
        internalCounters.push_back(11089);

        p.DefinePublicCounter("VSVerticesIn", "VertexShader", "The number of vertices processed by the VS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero");
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

        p.DefinePublicCounter("VSVALUInstCount", "VertexShader", "Average number of vector ALU instructions executed in the VS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/,2,3,/,4,ifnotzero,5,6,/,7,ifnotzero");
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

        p.DefinePublicCounter("VSSALUInstCount", "VertexShader", "Average number of scalar ALU instructions executed in the VS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/,2,3,/,4,ifnotzero,5,6,/,7,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3569);
        internalCounters.push_back(3065);
        internalCounters.push_back(2998);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("VSVALUBusy", "VertexShader", "The percentage of GPUTime vector ALU instructions are being processed by the VS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,ifnotzero,(4),*,NUM_SIMDS,/,3,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3569);
        internalCounters.push_back(3065);
        internalCounters.push_back(2998);

        p.DefinePublicCounter("VSVALUBusyCycles", "VertexShader", "Number of GPU cycles where vector ALU instructions are being processed by the VS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,ifnotzero,(4),*,NUM_SIMDS,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3574);
        internalCounters.push_back(3070);
        internalCounters.push_back(2998);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("VSSALUBusy", "VertexShader", "The percentage of GPUTime scalar ALU instructions are being processed by the VS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,ifnotzero,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,3,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3574);
        internalCounters.push_back(3070);
        internalCounters.push_back(2998);

        p.DefinePublicCounter("VSSALUBusyCycles", "VertexShader", "Number of GPU cycles where scalar ALU instructions are being processed by the VS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,ifnotzero,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11098);

        p.DefinePublicCounter("HSPatches", "HullShader", "The number of patches processed by the HS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4270);
        internalCounters.push_back(4248);

        p.DefinePublicCounter("HSVALUInstCount", "HullShader", "Average number of vector ALU instructions executed in the HS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4274);
        internalCounters.push_back(4248);

        p.DefinePublicCounter("HSSALUInstCount", "HullShader", "Average number of scalar ALU instructions executed in the HS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4325);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("HSVALUBusy", "HullShader", "The percentage of GPUTime vector ALU instructions are being processed by the HS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4325);

        p.DefinePublicCounter("HSVALUBusyCycles", "HullShader", "Number of GPU cycles vector where ALU instructions are being processed by the HS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4330);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("HSSALUBusy", "HullShader", "The percentage of GPUTime scalar ALU instructions are being processed by the HS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4330);

        p.DefinePublicCounter("HSSALUBusyCycles", "HullShader", "Number of GPU cycles where scalar ALU instructions are being processed by the HS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11013);
        internalCounters.push_back(10994);
        internalCounters.push_back(11089);

        p.DefinePublicCounter("DSVerticesIn", "DomainShader", "The number of vertices processed by the DS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,1,ifnotzero,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3514);
        internalCounters.push_back(3492);
        internalCounters.push_back(3010);
        internalCounters.push_back(2988);
        internalCounters.push_back(2998);
        internalCounters.push_back(4006);

        p.DefinePublicCounter("DSVALUInstCount", "DomainShader", "Average number of vector ALU instructions executed in the DS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,2,3,/,4,ifnotzero,5,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3518);
        internalCounters.push_back(3492);
        internalCounters.push_back(3014);
        internalCounters.push_back(2988);
        internalCounters.push_back(2998);
        internalCounters.push_back(4006);

        p.DefinePublicCounter("DSSALUInstCount", "DomainShader", "Average number of scalar ALU instructions executed in the DS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,2,3,/,4,ifnotzero,5,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3569);
        internalCounters.push_back(3065);
        internalCounters.push_back(1951);
        internalCounters.push_back(2998);
        internalCounters.push_back(4006);

        p.DefinePublicCounter("DSVALUBusy", "DomainShader", "The percentage of GPUTime vector ALU instructions are being processed by the DS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,(4),*,NUM_SIMDS,/,2,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3569);
        internalCounters.push_back(3065);
        internalCounters.push_back(1951);
        internalCounters.push_back(2998);
        internalCounters.push_back(4006);

        p.DefinePublicCounter("DSVALUBusyCycles", "DomainShader", "Number of GPU cycles where vector ALU instructions are being processed by the DS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,(4),*,NUM_SIMDS,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3574);
        internalCounters.push_back(3070);
        internalCounters.push_back(1951);
        internalCounters.push_back(2998);
        internalCounters.push_back(4006);

        p.DefinePublicCounter("DSSALUBusy", "DomainShader", "The percentage of GPUTime scalar ALU instructions are being processed by the DS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,2,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3574);
        internalCounters.push_back(3070);
        internalCounters.push_back(1951);
        internalCounters.push_back(2998);
        internalCounters.push_back(4006);

        p.DefinePublicCounter("DSSALUBusyCycles", "DomainShader", "Number of GPU cycles where scalar ALU instructions are being processed by the DS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11002);

        p.DefinePublicCounter("GSPrimsIn", "GeometryShader", "The number of primitives passed into the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11013);
        internalCounters.push_back(10994);

        p.DefinePublicCounter("GSVerticesOut", "GeometryShader", "The number of vertices output by the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3262);
        internalCounters.push_back(3240);

        p.DefinePublicCounter("GSVALUInstCount", "GeometryShader", "Average number of vector ALU instructions executed in the GS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3266);
        internalCounters.push_back(3240);

        p.DefinePublicCounter("GSSALUInstCount", "GeometryShader", "Average number of scalar ALU instructions executed in the GS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3317);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("GSVALUBusy", "GeometryShader", "The percentage of GPUTime vector ALU instructions are being processed by the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3317);

        p.DefinePublicCounter("GSVALUBusyCycles", "GeometryShader", "Number of GPU cycles where vector ALU instructions are being processed by the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3322);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("GSSALUBusy", "GeometryShader", "The percentage of GPUTime scalar ALU instructions are being processed by the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3322);

        p.DefinePublicCounter("GSSALUBusyCycles", "GeometryShader", "Number of GPU cycles where scalar ALU instructions are being processed by the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/");
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

        p.DefinePublicCounter("PrimitiveAssemblyBusy", "Timing", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max,6,/,(100),*,(100),min");
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

        p.DefinePublicCounter("PrimitiveAssemblyBusyCycles", "Timing", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2006);

        p.DefinePublicCounter("PrimitivesIn", "PrimitiveAssembly", "The number of primitives received by the hardware. This includes primitives generated by tessellation.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2012);
        internalCounters.push_back(2052);
        internalCounters.push_back(2053);
        internalCounters.push_back(2054);
        internalCounters.push_back(2055);

        p.DefinePublicCounter("CulledPrims", "PrimitiveAssembly", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,2,+,3,+,4,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2019);

        p.DefinePublicCounter("ClippedPrims", "PrimitiveAssembly", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2107);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("PAStalledOnRasterizer", "PrimitiveAssembly", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2107);

        p.DefinePublicCounter("PAStalledOnRasterizerCycles", "PrimitiveAssembly", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,NUM_PRIM_PIPES,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4760);
        internalCounters.push_back(4765);
        internalCounters.push_back(4770);
        internalCounters.push_back(4775);

        p.DefinePublicCounter("PSPixelsOut", "PixelShader", "Pixels exported from shader to colour buffers. Does not include killed or alpha tested pixels; if there are multiple rendertargets, each rendertarget receives one export, so this will be 2 for 1 pixel written to two RTs.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4762);
        internalCounters.push_back(4767);
        internalCounters.push_back(4772);
        internalCounters.push_back(4777);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("PSExportStalls", "PixelShader", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the colour buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4762);
        internalCounters.push_back(4767);
        internalCounters.push_back(4772);
        internalCounters.push_back(4777);

        p.DefinePublicCounter("PSExportStallsCycles", "PixelShader", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the colour buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3766);
        internalCounters.push_back(3744);

        p.DefinePublicCounter("PSVALUInstCount", "PixelShader", "Average number of vector ALU instructions executed in the PS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3770);
        internalCounters.push_back(3744);

        p.DefinePublicCounter("PSSALUInstCount", "PixelShader", "Average number of scalar ALU instructions executed in the PS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3821);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("PSVALUBusy", "PixelShader", "The percentage of GPUTime vector ALU instructions are being processed by the PS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3821);

        p.DefinePublicCounter("PSVALUBusyCycles", "PixelShader", "Number of GPU cycles where vector ALU instructions are being processed by the PS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3826);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("PSSALUBusy", "PixelShader", "The percentage of GPUTime scalar ALU instructions are being processed by the PS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3826);

        p.DefinePublicCounter("PSSALUBusyCycles", "PixelShader", "Number of GPU cycles where scalar ALU instructions are being processed by the PS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2605);

        p.DefinePublicCounter("CSThreadGroups", "ComputeShader", "Total number of thread groups.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4500);

        p.DefinePublicCounter("CSWavefronts", "ComputeShader", "The total number of wavefronts used for the CS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4510);

        p.DefinePublicCounter("CSThreads", "ComputeShader", "The number of CS threads processed by the hardware.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4522);
        internalCounters.push_back(4500);

        p.DefinePublicCounter("CSVALUInsts", "ComputeShader", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4585);
        internalCounters.push_back(4577);

        p.DefinePublicCounter("CSVALUUtilization", "ComputeShader", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,(64),*,/,(100),*,1,ifnotzero,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4526);
        internalCounters.push_back(4500);

        p.DefinePublicCounter("CSSALUInsts", "ComputeShader", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4524);
        internalCounters.push_back(4500);

        p.DefinePublicCounter("CSVFetchInsts", "ComputeShader", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4527);
        internalCounters.push_back(4500);

        p.DefinePublicCounter("CSSFetchInsts", "ComputeShader", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4523);
        internalCounters.push_back(4500);

        p.DefinePublicCounter("CSVWriteInsts", "ComputeShader", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4528);
        internalCounters.push_back(4529);
        internalCounters.push_back(4500);

        p.DefinePublicCounter("CSFlatVMemInsts", "ComputeShader", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,-,2,/,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4577);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("CSVALUBusy", "ComputeShader", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4577);

        p.DefinePublicCounter("CSVALUBusyCycles", "ComputeShader", "Number of GPU cycles where vector ALU instructions are processed.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4582);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("CSSALUBusy", "ComputeShader", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4582);

        p.DefinePublicCounter("CSSALUBusyCycles", "ComputeShader", "Number of GPU cycles where scalar ALU instructions are processed.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/");
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

        p.DefinePublicCounter("CSMemUnitBusy", "ComputeShader", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,/,NUM_SHADER_ENGINES,/,(100),*,12,ifnotzero");
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

        p.DefinePublicCounter("CSMemUnitBusyCycles", "ComputeShader", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,NUM_SHADER_ENGINES,/");
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

        p.DefinePublicCounter("CSMemUnitStalled", "ComputeShader", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,/,NUM_SHADER_ENGINES,/,(100),*,12,ifnotzero");
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

        p.DefinePublicCounter("CSMemUnitStalledCycles", "ComputeShader", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max");
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

        p.DefinePublicCounter("CSFetchSize", "ComputeShader", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,(1024),/,16,ifnotzero");
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

        p.DefinePublicCounter("CSWriteSize", "ComputeShader", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,(1024),/,16,ifnotzero");
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

        p.DefinePublicCounter("CSCacheHit", "ComputeShader", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*,32,ifnotzero");
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

        p.DefinePublicCounter("CSCacheHitCount", "ComputeShader", "Count of fetch, write, atomic, and other instructions that hit the data cache.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
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

        p.DefinePublicCounter("CSCacheMissCount", "ComputeShader", "Count of fetch, write, atomic, and other instructions that miss the data cache.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
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

        p.DefinePublicCounter("CSWriteUnitStalled", "ComputeShader", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,ifnotzero");
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

        p.DefinePublicCounter("CSWriteUnitStalledCycles", "ComputeShader", "Number of GPU cycles the write unit is stalled.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4531);
        internalCounters.push_back(4500);

        p.DefinePublicCounter("CSGDSInsts", "ComputeShader", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4530);
        internalCounters.push_back(4528);
        internalCounters.push_back(4500);

        p.DefinePublicCounter("CSLDSInsts", "ComputeShader", "The average number of LDS read/write instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,-,2,/,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4529);
        internalCounters.push_back(4500);

        p.DefinePublicCounter("CSFlatLDSInsts", "ComputeShader", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2793);
        internalCounters.push_back(2736);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("CSALUStalledByLDS", "ComputeShader", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,2,/,NUM_SHADER_ENGINES,/,(100),*,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2793);

        p.DefinePublicCounter("CSALUStalledByLDSCycles", "ComputeShader", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,NUM_SHADER_ENGINES,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4593);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("CSLDSBankConflict", "ComputeShader", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4593);

        p.DefinePublicCounter("CSLDSBankConflictCycles", "ComputeShader", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,NUM_SIMDS,/");
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

        p.DefinePublicCounter("TexUnitBusy", "Timing", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,/,NUM_SHADER_ENGINES,/,(100),*");
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

        p.DefinePublicCounter("TexUnitBusyCycles", "Timing", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max");
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

        p.DefinePublicCounter("TexTriFilteringPct", "TextureUnit", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,sum11,11,12,13,14,15,16,17,18,19,20,21,sum11,0,1,2,3,4,5,6,7,8,9,10,sum11,+,/,(100),*");
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

        p.DefinePublicCounter("TexTriFilteringCount", "TextureUnit", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,sum11");
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

        p.DefinePublicCounter("NoTexTriFilteringCount", "TextureUnit", "Count of pixels that did not receive trilinear filtering.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,sum11");
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

        p.DefinePublicCounter("TexVolFilteringPct", "TextureUnit", "Percentage of pixels that received volume filtering.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,sum11,11,12,13,14,15,16,17,18,19,20,21,sum11,0,1,2,3,4,5,6,7,8,9,10,sum11,+,/,(100),*");
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

        p.DefinePublicCounter("TexVolFilteringCount", "TextureUnit", "Count of pixels that received volume filtering.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,sum11");
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

        p.DefinePublicCounter("NoTexVolFilteringCount", "TextureUnit", "Count of pixels that did not receive volume filtering.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,sum11");
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

        p.DefinePublicCounter("TexAveAnisotropy", "TextureUnit", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,sum11,(2),11,12,13,14,15,16,17,18,19,20,21,sum11,*,+,(4),22,23,24,25,26,27,28,29,30,31,32,sum11,*,+,(6),33,34,35,36,37,38,39,40,41,42,43,sum11,*,+,(8),44,45,46,47,48,49,50,51,52,53,54,sum11,*,+,(10),55,56,57,58,59,60,61,62,63,64,65,sum11,*,+,(12),66,67,68,69,70,71,72,73,74,75,76,sum11,*,+,(14),77,78,79,80,81,82,83,84,85,86,87,sum11,*,+,(16),88,89,90,91,92,93,94,95,96,97,98,sum11,*,+,0,1,2,3,4,5,6,7,8,9,10,sum11,11,12,13,14,15,16,17,18,19,20,21,sum11,+,22,23,24,25,26,27,28,29,30,31,32,sum11,+,33,34,35,36,37,38,39,40,41,42,43,sum11,+,44,45,46,47,48,49,50,51,52,53,54,sum11,+,55,56,57,58,59,60,61,62,63,64,65,sum11,+,66,67,68,69,70,71,72,73,74,75,76,sum11,+,77,78,79,80,81,82,83,84,85,86,87,sum11,+,88,89,90,91,92,93,94,95,96,97,98,sum11,+,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1065);
        internalCounters.push_back(1322);
        internalCounters.push_back(1579);
        internalCounters.push_back(1836);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("DepthStencilTestBusy", "Timing", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1065);
        internalCounters.push_back(1322);
        internalCounters.push_back(1579);
        internalCounters.push_back(1836);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("DepthStencilTestBusyCount", "Timing", "Number of GPU cycles spent performing depth and stencil tests.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/");
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

        p.DefinePublicCounter("HiZTilesAccepted", "DepthAndStencil", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(936);
        internalCounters.push_back(1193);
        internalCounters.push_back(1450);
        internalCounters.push_back(1707);

        p.DefinePublicCounter("HiZTilesAcceptedCount", "DepthAndStencil", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(925);
        internalCounters.push_back(1182);
        internalCounters.push_back(1439);
        internalCounters.push_back(1696);

        p.DefinePublicCounter("HiZTilesRejectedCount", "DepthAndStencil", "Count of tiles not accepted by HiZ.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
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

        p.DefinePublicCounter("PreZTilesDetailCulled", "DepthAndStencil", "Percentage of tiles rejected because the associated prim had no contributing area.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "4,5,6,7,sum4,0,1,2,3,sum4,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(949);
        internalCounters.push_back(1206);
        internalCounters.push_back(1463);
        internalCounters.push_back(1720);

        p.DefinePublicCounter("PreZTilesDetailCulledCount", "DepthAndStencil", "Count of tiles rejected because the associated primitive had no contributing area.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(925);
        internalCounters.push_back(1182);
        internalCounters.push_back(1439);
        internalCounters.push_back(1696);

        p.DefinePublicCounter("PreZTilesDetailSurvivingCount", "DepthAndStencil", "Count of tiles surviving because the associated primitive had contributing area.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
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

        p.DefinePublicCounter("HiZQuadsCulled", "DepthAndStencil", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-,0,1,+,2,+,3,+,/,(100),*");
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

        p.DefinePublicCounter("HiZQuadsCulledCount", "DepthAndStencil", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2390);
        internalCounters.push_back(2391);
        internalCounters.push_back(2392);
        internalCounters.push_back(2393);

        p.DefinePublicCounter("HiZQuadsAcceptedCount", "DepthAndStencil", "Count of quads that did continue on in the pipeline after HiZ.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,2,+,3,+");
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

        p.DefinePublicCounter("PreZQuadsCulled", "DepthAndStencil", "Percentage of quads rejected based on the detailZ and earlyZ tests.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "5,6,+,7,+,8,+,4,-,0,1,+,2,+,3,+,/,(100),*");
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

        p.DefinePublicCounter("PreZQuadsCulledCount", "DepthAndStencil", "Count of quads rejected based on the detailZ and earlyZ tests.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,2,+,3,+,4,-,5,-,6,-,7,-,8,-");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2414);
        internalCounters.push_back(2390);
        internalCounters.push_back(2391);
        internalCounters.push_back(2392);
        internalCounters.push_back(2393);

        p.DefinePublicCounter("PreZQuadsSurvivingCount", "DepthAndStencil", "Count of quads surviving detailZ and earlyZ tests.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "1,2,+,3,+,4,+,0,-");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2414);
        internalCounters.push_back(2314);
        internalCounters.push_back(2315);
        internalCounters.push_back(2316);
        internalCounters.push_back(2317);

        p.DefinePublicCounter("PostZQuads", "DepthAndStencil", "Percentage of quads for which the pixel shader will run and may be postZ tested.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,+,3,+,4,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2414);

        p.DefinePublicCounter("PostZQuadCount", "DepthAndStencil", "Count of quads for which the pixel shader will run and may be postZ tested.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1098);
        internalCounters.push_back(1355);
        internalCounters.push_back(1612);
        internalCounters.push_back(1869);

        p.DefinePublicCounter("PreZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z before shading and passed.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1100);
        internalCounters.push_back(1357);
        internalCounters.push_back(1614);
        internalCounters.push_back(1871);

        p.DefinePublicCounter("PreZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z before shading and failed stencil test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1099);
        internalCounters.push_back(1356);
        internalCounters.push_back(1613);
        internalCounters.push_back(1870);

        p.DefinePublicCounter("PreZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z before shading and failed Z test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1095);
        internalCounters.push_back(1352);
        internalCounters.push_back(1609);
        internalCounters.push_back(1866);

        p.DefinePublicCounter("PostZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z after shading and passed.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1097);
        internalCounters.push_back(1354);
        internalCounters.push_back(1611);
        internalCounters.push_back(1868);

        p.DefinePublicCounter("PostZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z after shading and failed stencil test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1096);
        internalCounters.push_back(1353);
        internalCounters.push_back(1610);
        internalCounters.push_back(1867);

        p.DefinePublicCounter("PostZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z after shading and failed Z test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(967);
        internalCounters.push_back(1224);
        internalCounters.push_back(1481);
        internalCounters.push_back(1738);
        internalCounters.push_back(1951);

        p.DefinePublicCounter("ZUnitStalled", "DepthAndStencil", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(967);
        internalCounters.push_back(1224);
        internalCounters.push_back(1481);
        internalCounters.push_back(1738);

        p.DefinePublicCounter("ZUnitStalledCycles", "DepthAndStencil", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/");
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

        p.DefinePublicCounter("DBMemRead", "DepthAndStencil", "Number of bytes read from the depth buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(256),*,4,5,6,7,sum4,(32),*,+");
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

        p.DefinePublicCounter("DBMemWritten", "DepthAndStencil", "Number of bytes written to the depth buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(256),*,4,5,6,7,sum4,(32),*,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(127);
        internalCounters.push_back(353);
        internalCounters.push_back(579);
        internalCounters.push_back(805);

        p.DefinePublicCounter("CBMemRead", "ColorBuffer", "Number of bytes read from the color buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(32),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(117);
        internalCounters.push_back(343);
        internalCounters.push_back(569);
        internalCounters.push_back(795);

        p.DefinePublicCounter("CBMemWritten", "ColorBuffer", "Number of bytes written to the color buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(32),*");
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

        p.DefinePublicCounter("CBSlowPixelPct", "ColorBuffer", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(161);
        internalCounters.push_back(387);
        internalCounters.push_back(613);
        internalCounters.push_back(839);

        p.DefinePublicCounter("CBSlowPixelCount", "ColorBuffer", "Number of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
}

