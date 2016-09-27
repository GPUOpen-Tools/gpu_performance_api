//==============================================================================
// Copyright (c) 2010-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  PublicCounterDefinitions for GLGFX8
//==============================================================================

#include "PublicCounterDefsGLGfx8.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicCountersGLGfx8(GPA_PublicCounters& p)
{
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(15124);

        p.DefinePublicCounter("GPUTime", "#Timing#Time this API call took to execute on the GPU in milliseconds. Does not include time that draw calls are processed in parallel.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_API_DYNAMIC, internalCounters, "0,TS_FREQ,/,(1000),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2633);
        internalCounters.push_back(2631);

        p.DefinePublicCounter("GPUBusy", "#Timing#The percentage of time GPU was busy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14904);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("TessellatorBusy", "#Timing#The percentage of time the tessellation engine is busy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*");
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

        p.DefinePublicCounter("VSBusy", "#Timing#The percentage of time the ShaderUnit has vertex shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,1,5,ifnotzero,2,6,ifnotzero,7,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(15124);
        internalCounters.push_back(3231);
        internalCounters.push_back(3256);
        internalCounters.push_back(3278);
        internalCounters.push_back(3300);
        internalCounters.push_back(3240);
        internalCounters.push_back(3262);
        internalCounters.push_back(3284);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("VSTime", "#Timing#Time vertex shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,5,ifnotzero,2,6,ifnotzero,3,7,ifnotzero,8,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3268);
        internalCounters.push_back(3274);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("HSBusy", "#Timing#The percentage of time the ShaderUnit has hull shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(15124);
        internalCounters.push_back(3268);
        internalCounters.push_back(3274);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("HSTime", "#Timing#Time hull shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3231);
        internalCounters.push_back(3256);
        internalCounters.push_back(3300);
        internalCounters.push_back(3262);
        internalCounters.push_back(3284);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("DSBusy", "#Timing#The percentage of time the ShaderUnit has domain shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,5,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(15124);
        internalCounters.push_back(3231);
        internalCounters.push_back(3256);
        internalCounters.push_back(3300);
        internalCounters.push_back(3262);
        internalCounters.push_back(3284);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("DSTime", "#Timing#Time domain shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,4,ifnotzero,5,ifnotzero,6,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3247);
        internalCounters.push_back(3250);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("GSBusy", "#Timing#The percentage of time the ShaderUnit has geometry shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(15124);
        internalCounters.push_back(3247);
        internalCounters.push_back(3250);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("GSTime", "#Timing#Time geometry shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3300);
        internalCounters.push_back(3305);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("PSBusy", "#Timing#The percentage of time the ShaderUnit has pixel shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(15124);
        internalCounters.push_back(3300);
        internalCounters.push_back(3305);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("PSTime", "#Timing#Time pixel shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3288);
        internalCounters.push_back(3292);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("CSBusy", "#Timing#The percentage of time the ShaderUnit has compute shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(15124);
        internalCounters.push_back(3288);
        internalCounters.push_back(3292);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("CSTime", "#Timing#Time compute shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14800);
        internalCounters.push_back(14781);
        internalCounters.push_back(14876);

        p.DefinePublicCounter("VSVerticesIn", "#VertexShader#The number of vertices processed by the VS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero");
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

        p.DefinePublicCounter("VSVALUInstCount", "#VertexShader#Average number of vector ALU instructions executed in the VS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/,2,3,/,4,ifnotzero,5,6,/,7,ifnotzero");
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

        p.DefinePublicCounter("VSSALUInstCount", "#VertexShader#Average number of scalar ALU instructions executed in the VS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/,2,3,/,4,ifnotzero,5,6,/,7,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4405);
        internalCounters.push_back(3807);
        internalCounters.push_back(3740);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("VSVALUBusy", "#VertexShader#The percentage of GPUTime vector ALU instructions are being processed by the VS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,ifnotzero,(4),*,NUM_SIMDS,/,3,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4410);
        internalCounters.push_back(3812);
        internalCounters.push_back(3740);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("VSSALUBusy", "#VertexShader#The percentage of GPUTime scalar ALU instructions are being processed by the VS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,ifnotzero,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,3,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14885);

        p.DefinePublicCounter("HSPatches", "#HullShader#The number of patches processed by the HS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5247);
        internalCounters.push_back(5225);

        p.DefinePublicCounter("HSVALUInstCount", "#HullShader#Average number of vector ALU instructions executed in the HS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5251);
        internalCounters.push_back(5225);

        p.DefinePublicCounter("HSSALUInstCount", "#HullShader#Average number of scalar ALU instructions executed in the HS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5302);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("HSVALUBusy", "#HullShader#The percentage of GPUTime vector ALU instructions are being processed by the HS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5307);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("HSSALUBusy", "#HullShader#The percentage of GPUTime scalar ALU instructions are being processed by the HS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14800);
        internalCounters.push_back(14781);
        internalCounters.push_back(14876);

        p.DefinePublicCounter("DSVerticesIn", "#DomainShader#The number of vertices processed by the DS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,1,ifnotzero,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4350);
        internalCounters.push_back(4328);
        internalCounters.push_back(3752);
        internalCounters.push_back(3730);
        internalCounters.push_back(3740);
        internalCounters.push_back(4936);

        p.DefinePublicCounter("DSVALUInstCount", "#DomainShader#Average number of vector ALU instructions executed in the DS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,2,3,/,4,ifnotzero,5,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4354);
        internalCounters.push_back(4328);
        internalCounters.push_back(3756);
        internalCounters.push_back(3730);
        internalCounters.push_back(3740);
        internalCounters.push_back(4936);

        p.DefinePublicCounter("DSSALUInstCount", "#DomainShader#Average number of scalar ALU instructions executed in the DS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,2,3,/,4,ifnotzero,5,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4405);
        internalCounters.push_back(3807);
        internalCounters.push_back(2633);
        internalCounters.push_back(3740);
        internalCounters.push_back(4936);

        p.DefinePublicCounter("DSVALUBusy", "#DomainShader#The percentage of GPUTime vector ALU instructions are being processed by the DS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,(4),*,NUM_SIMDS,/,2,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4410);
        internalCounters.push_back(3812);
        internalCounters.push_back(2633);
        internalCounters.push_back(3740);
        internalCounters.push_back(4936);

        p.DefinePublicCounter("DSSALUBusy", "#DomainShader#The percentage of GPUTime scalar ALU instructions are being processed by the DS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,2,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14789);

        p.DefinePublicCounter("GSPrimsIn", "#GeometryShader#The number of primitives passed into the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14800);
        internalCounters.push_back(14781);

        p.DefinePublicCounter("GSVerticesOut", "#GeometryShader#The number of vertices output by the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4051);
        internalCounters.push_back(4029);

        p.DefinePublicCounter("GSVALUInstCount", "#GeometryShader#Average number of vector ALU instructions executed in the GS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4055);
        internalCounters.push_back(4029);

        p.DefinePublicCounter("GSSALUInstCount", "#GeometryShader#Average number of scalar ALU instructions executed in the GS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4106);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("GSVALUBusy", "#GeometryShader#The percentage of GPUTime vector ALU instructions are being processed by the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4111);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("GSSALUBusy", "#GeometryShader#The percentage of GPUTime scalar ALU instructions are being processed by the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*");
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

        p.DefinePublicCounter("PrimitiveAssemblyBusy", "#Timing#The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max,6,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2688);

        p.DefinePublicCounter("PrimitivesIn", "#PrimitiveAssembly#The number of primitives received by the hardware. This includes primitives generated by tessellation.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2694);
        internalCounters.push_back(2734);
        internalCounters.push_back(2735);
        internalCounters.push_back(2736);
        internalCounters.push_back(2737);

        p.DefinePublicCounter("CulledPrims", "#PrimitiveAssembly#The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,2,+,3,+,4,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2701);

        p.DefinePublicCounter("ClippedPrims", "#PrimitiveAssembly#The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2789);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("PAStalledOnRasterizer", "#PrimitiveAssembly#Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5831);
        internalCounters.push_back(5836);
        internalCounters.push_back(5841);
        internalCounters.push_back(5846);

        p.DefinePublicCounter("PSPixelsOut", "#PixelShader#Pixels exported from shader to colour buffers. Does not include killed or alpha tested pixels; if there are multiple rendertargets, each rendertarget receives one export, so this will be 2 for 1 pixel written to two RTs.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5833);
        internalCounters.push_back(5838);
        internalCounters.push_back(5843);
        internalCounters.push_back(5848);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("PSExportStalls", "#PixelShader#Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the colour buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4649);
        internalCounters.push_back(4627);

        p.DefinePublicCounter("PSVALUInstCount", "#PixelShader#Average number of vector ALU instructions executed in the PS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4653);
        internalCounters.push_back(4627);

        p.DefinePublicCounter("PSSALUInstCount", "#PixelShader#Average number of scalar ALU instructions executed in the PS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4704);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("PSVALUBusy", "#PixelShader#The percentage of GPUTime vector ALU instructions are being processed by the PS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4709);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("PSSALUBusy", "#PixelShader#The percentage of GPUTime scalar ALU instructions are being processed by the PS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3289);

        p.DefinePublicCounter("CSThreadGroups", "#ComputeShader#Total number of thread groups.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5524);

        p.DefinePublicCounter("CSWavefronts", "#ComputeShader#The total number of wavefronts used for the CS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5534);

        p.DefinePublicCounter("CSThreads", "#ComputeShader#The number of CS threads processed by the hardware.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5546);
        internalCounters.push_back(5524);

        p.DefinePublicCounter("CSVALUInsts", "#ComputeShader#The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5609);
        internalCounters.push_back(5601);

        p.DefinePublicCounter("CSVALUUtilization", "#ComputeShader#The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,(64),*,/,(100),*,1,ifnotzero,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5550);
        internalCounters.push_back(5524);

        p.DefinePublicCounter("CSSALUInsts", "#ComputeShader#The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,1,ifnotzero");
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

        p.DefinePublicCounter("CSVFetchInsts", "#ComputeShader#The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/,17,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5551);
        internalCounters.push_back(5524);

        p.DefinePublicCounter("CSSFetchInsts", "#ComputeShader#The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,1,ifnotzero");
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

        p.DefinePublicCounter("CSVWriteInsts", "#ComputeShader#The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,sum16,-,17,/,17,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5554);
        internalCounters.push_back(5553);
        internalCounters.push_back(5524);

        p.DefinePublicCounter("CSFlatVMemInsts", "#ComputeShader#The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,-,2,/,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5601);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("CSVALUBusy", "#ComputeShader#The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5606);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("CSSALUBusy", "#ComputeShader#The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*");
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

        p.DefinePublicCounter("CSMemUnitBusy", "#ComputeShader#The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*,17,ifnotzero");
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

        p.DefinePublicCounter("CSMemUnitStalled", "#ComputeShader#The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*,17,ifnotzero");
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
        internalCounters.push_back(3289);

        p.DefinePublicCounter("CSFetchSize", "#ComputeShader#The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,(1024),/,16,ifnotzero");
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
        internalCounters.push_back(3289);

        p.DefinePublicCounter("CSWriteSize", "#ComputeShader#The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,(1024),/,16,ifnotzero");
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
        internalCounters.push_back(3289);

        p.DefinePublicCounter("CSCacheHit", "#ComputeShader#The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*,32,ifnotzero");
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
        internalCounters.push_back(3289);

        p.DefinePublicCounter("CSWriteUnitStalled", "#ComputeShader#The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5555);
        internalCounters.push_back(5524);

        p.DefinePublicCounter("CSGDSInsts", "#ComputeShader#The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5554);
        internalCounters.push_back(5552);
        internalCounters.push_back(5524);

        p.DefinePublicCounter("CSLDSInsts", "#ComputeShader#The average number of LDS read/write instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,-,2,/,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5553);
        internalCounters.push_back(5524);

        p.DefinePublicCounter("CSFlatLDSInsts", "#ComputeShader#The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3488);
        internalCounters.push_back(3431);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("CSALUStalledByLDS", "#ComputeShader#The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,2,/,NUM_SHADER_ENGINES,/,(100),*,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5617);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("CSLDSBankConflict", "#ComputeShader#The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*");
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

        p.DefinePublicCounter("TexUnitBusy", "#Timing#The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*");
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

        p.DefinePublicCounter("TexTriFilteringPct", "#TextureUnit#Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,+,/,(100),*");
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

        p.DefinePublicCounter("TexVolFilteringPct", "#TextureUnit#Percentage of pixels that received volume filtering.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,+,/,(100),*");
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

        p.DefinePublicCounter("TexAveAnisotropy", "#TextureUnit#The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(2),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,*,+,(4),32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,*,+,(6),48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,*,+,(8),64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,*,+,(10),80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,*,+,(12),96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,*,+,(14),112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,*,+,(16),128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,*,+,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,+,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,+,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,+,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,+,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,+,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,+,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,+,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1747);
        internalCounters.push_back(2004);
        internalCounters.push_back(2261);
        internalCounters.push_back(2518);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("DepthStencilTestBusy", "#Timing#Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*");
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

        p.DefinePublicCounter("HiZTilesAccepted", "#DepthAndStencil#Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*");
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

        p.DefinePublicCounter("PreZTilesDetailCulled", "#DepthAndStencil#Percentage of tiles rejected because the associated prim had no contributing area.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "4,5,6,7,sum4,0,1,2,3,sum4,/,(100),*");
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

        p.DefinePublicCounter("HiZQuadsCulled", "#DepthAndStencil#Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-,0,1,+,2,+,3,+,/,(100),*");
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

        p.DefinePublicCounter("PreZQuadsCulled", "#DepthAndStencil#Percentage of quads rejected based on the detailZ and earlyZ tests.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "5,6,+,7,+,8,+,4,-,0,1,+,2,+,3,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3096);
        internalCounters.push_back(2996);
        internalCounters.push_back(2997);
        internalCounters.push_back(2998);
        internalCounters.push_back(2999);

        p.DefinePublicCounter("PostZQuads", "#DepthAndStencil#Percentage of quads for which the pixel shader will run and may be postZ tested.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,+,3,+,4,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1780);
        internalCounters.push_back(2037);
        internalCounters.push_back(2294);
        internalCounters.push_back(2551);

        p.DefinePublicCounter("PreZSamplesPassing", "#DepthAndStencil#Number of samples tested for Z before shading and passed.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1782);
        internalCounters.push_back(2039);
        internalCounters.push_back(2296);
        internalCounters.push_back(2553);

        p.DefinePublicCounter("PreZSamplesFailingS", "#DepthAndStencil#Number of samples tested for Z before shading and failed stencil test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1781);
        internalCounters.push_back(2038);
        internalCounters.push_back(2295);
        internalCounters.push_back(2552);

        p.DefinePublicCounter("PreZSamplesFailingZ", "#DepthAndStencil#Number of samples tested for Z before shading and failed Z test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1777);
        internalCounters.push_back(2034);
        internalCounters.push_back(2291);
        internalCounters.push_back(2548);

        p.DefinePublicCounter("PostZSamplesPassing", "#DepthAndStencil#Number of samples tested for Z after shading and passed.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1779);
        internalCounters.push_back(2036);
        internalCounters.push_back(2293);
        internalCounters.push_back(2550);

        p.DefinePublicCounter("PostZSamplesFailingS", "#DepthAndStencil#Number of samples tested for Z after shading and failed stencil test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1778);
        internalCounters.push_back(2035);
        internalCounters.push_back(2292);
        internalCounters.push_back(2549);

        p.DefinePublicCounter("PostZSamplesFailingZ", "#DepthAndStencil#Number of samples tested for Z after shading and failed Z test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1649);
        internalCounters.push_back(1906);
        internalCounters.push_back(2163);
        internalCounters.push_back(2420);
        internalCounters.push_back(2633);

        p.DefinePublicCounter("ZUnitStalled", "#DepthAndStencil#The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(128);
        internalCounters.push_back(524);
        internalCounters.push_back(920);
        internalCounters.push_back(1316);

        p.DefinePublicCounter("CBMemRead", "#ColorBuffer#Number of bytes read from the color buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(32),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(118);
        internalCounters.push_back(514);
        internalCounters.push_back(910);
        internalCounters.push_back(1306);

        p.DefinePublicCounter("CBMemWritten", "#ColorBuffer#Number of bytes written to the color buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(32),*");
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

        p.DefinePublicCounter("CBSlowPixelPct", "#ColorBuffer#Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*,(100),min");
    }
}

