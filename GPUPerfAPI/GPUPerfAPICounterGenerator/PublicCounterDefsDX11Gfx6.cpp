//==============================================================================
// Copyright (c) 2010-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  PublicCounterDefinitions for DX11GFX6
//==============================================================================

#include "PublicCounterDefsDX11Gfx6.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicCountersDX11Gfx6(GPA_PublicCounters& p)
{
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16886);

        p.DefinePublicCounter("GPUTime", "#Timing#Time this API call took to execute on the GPU in milliseconds. Does not include time that draw calls are processed in parallel.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_API_DYNAMIC, internalCounters, "0,TS_FREQ,/,(1000),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3892);
        internalCounters.push_back(3890);

        p.DefinePublicCounter("GPUBusy", "#Timing#The percentage of time GPU was busy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16466);
        internalCounters.push_back(16606);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("TessellatorBusy", "#Timing#The percentage of time the tessellation engine is busy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4993);
        internalCounters.push_back(5182);
        internalCounters.push_back(5011);
        internalCounters.push_back(5200);
        internalCounters.push_back(5029);
        internalCounters.push_back(5218);
        internalCounters.push_back(5059);
        internalCounters.push_back(5248);
        internalCounters.push_back(5002);
        internalCounters.push_back(5191);
        internalCounters.push_back(5017);
        internalCounters.push_back(5206);
        internalCounters.push_back(5035);
        internalCounters.push_back(5224);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("VSBusy", "#Timing#The percentage of time the ShaderUnit has vertex shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,8,ifnotzero,2,10,ifnotzero,4,12,ifnotzero,(0),1,9,ifnotzero,3,11,ifnotzero,5,13,ifnotzero,max,14,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16886);
        internalCounters.push_back(4993);
        internalCounters.push_back(5182);
        internalCounters.push_back(5011);
        internalCounters.push_back(5200);
        internalCounters.push_back(5029);
        internalCounters.push_back(5218);
        internalCounters.push_back(5059);
        internalCounters.push_back(5248);
        internalCounters.push_back(5002);
        internalCounters.push_back(5191);
        internalCounters.push_back(5017);
        internalCounters.push_back(5206);
        internalCounters.push_back(5035);
        internalCounters.push_back(5224);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("VSTime", "#Timing#Time vertex shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,9,ifnotzero,3,11,ifnotzero,5,13,ifnotzero,(0),2,10,ifnotzero,4,12,ifnotzero,6,14,ifnotzero,max,15,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5020);
        internalCounters.push_back(5209);
        internalCounters.push_back(5026);
        internalCounters.push_back(5215);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("HSBusy", "#Timing#The percentage of time the ShaderUnit has hull shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,2,ifnotzero,(0),1,3,ifnotzero,max,4,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16886);
        internalCounters.push_back(5020);
        internalCounters.push_back(5209);
        internalCounters.push_back(5026);
        internalCounters.push_back(5215);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("HSTime", "#Timing#Time hull shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,3,ifnotzero,(0),2,4,ifnotzero,max,5,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4993);
        internalCounters.push_back(5182);
        internalCounters.push_back(5011);
        internalCounters.push_back(5200);
        internalCounters.push_back(5059);
        internalCounters.push_back(5248);
        internalCounters.push_back(5017);
        internalCounters.push_back(5206);
        internalCounters.push_back(5035);
        internalCounters.push_back(5224);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("DSBusy", "#Timing#The percentage of time the ShaderUnit has domain shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,2,6,ifnotzero,8,ifnotzero,(0),1,3,7,ifnotzero,9,ifnotzero,max,10,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16886);
        internalCounters.push_back(4993);
        internalCounters.push_back(5182);
        internalCounters.push_back(5011);
        internalCounters.push_back(5200);
        internalCounters.push_back(5059);
        internalCounters.push_back(5248);
        internalCounters.push_back(5017);
        internalCounters.push_back(5206);
        internalCounters.push_back(5035);
        internalCounters.push_back(5224);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("DSTime", "#Timing#Time domain shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,3,7,ifnotzero,9,ifnotzero,(0),2,4,8,ifnotzero,10,ifnotzero,max,11,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5005);
        internalCounters.push_back(5194);
        internalCounters.push_back(5008);
        internalCounters.push_back(5197);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("GSBusy", "#Timing#The percentage of time the ShaderUnit has geometry shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,2,ifnotzero,(0),1,3,ifnotzero,max,4,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16886);
        internalCounters.push_back(5005);
        internalCounters.push_back(5194);
        internalCounters.push_back(5008);
        internalCounters.push_back(5197);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("GSTime", "#Timing#Time geometry shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,3,ifnotzero,(0),2,4,ifnotzero,max,5,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5059);
        internalCounters.push_back(5248);
        internalCounters.push_back(5066);
        internalCounters.push_back(5255);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("PSBusy", "#Timing#The percentage of time the ShaderUnit has pixel shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,2,ifnotzero,(0),1,3,ifnotzero,max,4,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16886);
        internalCounters.push_back(5059);
        internalCounters.push_back(5248);
        internalCounters.push_back(5066);
        internalCounters.push_back(5255);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("PSTime", "#Timing#Time pixel shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,3,ifnotzero,(0),2,4,ifnotzero,max,5,/,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5038);
        internalCounters.push_back(5227);
        internalCounters.push_back(5043);
        internalCounters.push_back(5232);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("CSBusy", "#Timing#The percentage of time the ShaderUnit has compute shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,2,ifnotzero,(0),1,3,ifnotzero,max,4,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16886);
        internalCounters.push_back(5038);
        internalCounters.push_back(5227);
        internalCounters.push_back(5043);
        internalCounters.push_back(5232);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("CSTime", "#Timing#Time compute shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,3,ifnotzero,(0),2,4,ifnotzero,max,5,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16361);
        internalCounters.push_back(16501);
        internalCounters.push_back(16342);
        internalCounters.push_back(16482);
        internalCounters.push_back(16437);
        internalCounters.push_back(16577);

        p.DefinePublicCounter("VSVerticesIn", "#VertexShader#The number of vertices processed by the VS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,2,3,+,2,3,+,ifnotzero,4,5,+,4,5,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16446);
        internalCounters.push_back(16586);

        p.DefinePublicCounter("HSPatches", "#HullShader#The number of patches processed by the HS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16361);
        internalCounters.push_back(16501);
        internalCounters.push_back(16342);
        internalCounters.push_back(16482);
        internalCounters.push_back(16437);
        internalCounters.push_back(16577);

        p.DefinePublicCounter("DSVerticesIn", "#DomainShader#The number of vertices processed by the DS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,+,2,3,+,2,3,+,ifnotzero,4,5,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16350);
        internalCounters.push_back(16490);

        p.DefinePublicCounter("GSPrimsIn", "#GeometryShader#The number of primitives passed into the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16361);
        internalCounters.push_back(16501);
        internalCounters.push_back(16342);
        internalCounters.push_back(16482);

        p.DefinePublicCounter("GSVerticesOut", "#GeometryShader#The number of vertices output by the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,+,2,3,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4113);
        internalCounters.push_back(4249);
        internalCounters.push_back(4117);
        internalCounters.push_back(4253);
        internalCounters.push_back(4069);
        internalCounters.push_back(4205);
        internalCounters.push_back(4081);
        internalCounters.push_back(4217);
        internalCounters.push_back(4070);
        internalCounters.push_back(4206);
        internalCounters.push_back(4082);
        internalCounters.push_back(4218);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("PrimitiveAssemblyBusy", "#Timing#The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,2,-,4,6,+,8,+,10,(2),*,+,SU_CLOCKS_PRIM,*,-,1,3,-,5,7,+,9,+,11,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max,12,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4016);
        internalCounters.push_back(4152);

        p.DefinePublicCounter("PrimitivesIn", "#PrimitiveAssembly#The number of primitives received by the hardware. This includes primitives generated by tessellation.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4022);
        internalCounters.push_back(4158);
        internalCounters.push_back(4062);
        internalCounters.push_back(4198);
        internalCounters.push_back(4063);
        internalCounters.push_back(4199);
        internalCounters.push_back(4064);
        internalCounters.push_back(4200);
        internalCounters.push_back(4065);
        internalCounters.push_back(4201);

        p.DefinePublicCounter("CulledPrims", "#PrimitiveAssembly#The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,2,+,3,+,4,+,5,+,6,+,7,+,8,+,9,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4029);
        internalCounters.push_back(4165);

        p.DefinePublicCounter("ClippedPrims", "#PrimitiveAssembly#The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4117);
        internalCounters.push_back(4253);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("PAStalledOnRasterizer", "#PrimitiveAssembly#Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4876);
        internalCounters.push_back(4908);
        internalCounters.push_back(4940);
        internalCounters.push_back(4972);
        internalCounters.push_back(4881);
        internalCounters.push_back(4913);
        internalCounters.push_back(4945);
        internalCounters.push_back(4977);
        internalCounters.push_back(4886);
        internalCounters.push_back(4918);
        internalCounters.push_back(4950);
        internalCounters.push_back(4982);
        internalCounters.push_back(4891);
        internalCounters.push_back(4923);
        internalCounters.push_back(4955);
        internalCounters.push_back(4987);

        p.DefinePublicCounter("PSPixelsOut", "#PixelShader#Pixels exported from shader to colour buffers. Does not include killed or alpha tested pixels; if there are multiple rendertargets, each rendertarget receives one export, so this will be 2 for 1 pixel written to two RTs.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,12,13,14,15,sum4,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4878);
        internalCounters.push_back(4910);
        internalCounters.push_back(4942);
        internalCounters.push_back(4974);
        internalCounters.push_back(4883);
        internalCounters.push_back(4915);
        internalCounters.push_back(4947);
        internalCounters.push_back(4979);
        internalCounters.push_back(4888);
        internalCounters.push_back(4920);
        internalCounters.push_back(4952);
        internalCounters.push_back(4984);
        internalCounters.push_back(4893);
        internalCounters.push_back(4925);
        internalCounters.push_back(4957);
        internalCounters.push_back(4989);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("PSExportStalls", "#PixelShader#Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the colour buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max,16,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSThreadGroups", "#ComputeShader#Total number of thread groups.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5043);
        internalCounters.push_back(5232);

        p.DefinePublicCounter("CSWavefronts", "#ComputeShader#The total number of wavefronts used for the CS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);
        internalCounters.push_back(5379);
        internalCounters.push_back(5778);

        p.DefinePublicCounter("CSThreads", "#ComputeShader#The number of CS threads processed by the hardware.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),2,3,+,0,1,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5384);
        internalCounters.push_back(5783);
        internalCounters.push_back(5374);
        internalCounters.push_back(5773);
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSVALUInsts", "#ComputeShader#The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,+,2,3,+,/,4,5,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5428);
        internalCounters.push_back(5827);
        internalCounters.push_back(5420);
        internalCounters.push_back(5819);
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSVALUUtilization", "#ComputeShader#The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,+,2,3,+,(64),*,/,(100),*,4,5,+,ifnotzero,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5388);
        internalCounters.push_back(5787);
        internalCounters.push_back(5374);
        internalCounters.push_back(5773);
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSSALUInsts", "#ComputeShader#The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,+,2,3,+,/,4,5,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5386);
        internalCounters.push_back(5785);
        internalCounters.push_back(5374);
        internalCounters.push_back(5773);
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSVFetchInsts", "#ComputeShader#The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,+,2,3,+,/,4,5,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5389);
        internalCounters.push_back(5788);
        internalCounters.push_back(5374);
        internalCounters.push_back(5773);
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSSFetchInsts", "#ComputeShader#The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,+,2,3,+,/,4,5,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5385);
        internalCounters.push_back(5784);
        internalCounters.push_back(5374);
        internalCounters.push_back(5773);
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSVWriteInsts", "#ComputeShader#The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,+,2,3,+,/,4,5,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5420);
        internalCounters.push_back(5819);
        internalCounters.push_back(3892);
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSVALUBusy", "#ComputeShader#The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,+,(4),*,NUM_SIMDS,/,2,/,(100),*,3,4,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5425);
        internalCounters.push_back(5824);
        internalCounters.push_back(3892);
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSSALUBusy", "#ComputeShader#The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,+,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,2,/,(100),*,3,4,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6168);
        internalCounters.push_back(6274);
        internalCounters.push_back(6380);
        internalCounters.push_back(6486);
        internalCounters.push_back(6592);
        internalCounters.push_back(6698);
        internalCounters.push_back(6804);
        internalCounters.push_back(6910);
        internalCounters.push_back(7016);
        internalCounters.push_back(7122);
        internalCounters.push_back(7228);
        internalCounters.push_back(7334);
        internalCounters.push_back(7440);
        internalCounters.push_back(7546);
        internalCounters.push_back(7652);
        internalCounters.push_back(7758);
        internalCounters.push_back(7864);
        internalCounters.push_back(7970);
        internalCounters.push_back(8076);
        internalCounters.push_back(8182);
        internalCounters.push_back(8288);
        internalCounters.push_back(8394);
        internalCounters.push_back(8500);
        internalCounters.push_back(8606);
        internalCounters.push_back(8712);
        internalCounters.push_back(8818);
        internalCounters.push_back(8924);
        internalCounters.push_back(9030);
        internalCounters.push_back(9136);
        internalCounters.push_back(9242);
        internalCounters.push_back(9348);
        internalCounters.push_back(9454);
        internalCounters.push_back(3892);
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSMemUnitBusy", "#ComputeShader#The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,max32,32,/,(100),*,33,34,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11131);
        internalCounters.push_back(11241);
        internalCounters.push_back(11351);
        internalCounters.push_back(11461);
        internalCounters.push_back(11571);
        internalCounters.push_back(11681);
        internalCounters.push_back(11791);
        internalCounters.push_back(11901);
        internalCounters.push_back(12011);
        internalCounters.push_back(12121);
        internalCounters.push_back(12231);
        internalCounters.push_back(12341);
        internalCounters.push_back(12451);
        internalCounters.push_back(12561);
        internalCounters.push_back(12671);
        internalCounters.push_back(12781);
        internalCounters.push_back(12891);
        internalCounters.push_back(13001);
        internalCounters.push_back(13111);
        internalCounters.push_back(13221);
        internalCounters.push_back(13331);
        internalCounters.push_back(13441);
        internalCounters.push_back(13551);
        internalCounters.push_back(13661);
        internalCounters.push_back(13771);
        internalCounters.push_back(13881);
        internalCounters.push_back(13991);
        internalCounters.push_back(14101);
        internalCounters.push_back(14211);
        internalCounters.push_back(14321);
        internalCounters.push_back(14431);
        internalCounters.push_back(14541);
        internalCounters.push_back(3892);
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSMemUnitStalled", "#ComputeShader#The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,max32,32,/,(100),*,33,34,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14672);
        internalCounters.push_back(14800);
        internalCounters.push_back(14928);
        internalCounters.push_back(15056);
        internalCounters.push_back(15184);
        internalCounters.push_back(15312);
        internalCounters.push_back(15440);
        internalCounters.push_back(15568);
        internalCounters.push_back(15696);
        internalCounters.push_back(15824);
        internalCounters.push_back(15952);
        internalCounters.push_back(16080);
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSFetchSize", "#ComputeShader#The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,sum12,(32),*,(1024),/,12,13,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14666);
        internalCounters.push_back(14794);
        internalCounters.push_back(14922);
        internalCounters.push_back(15050);
        internalCounters.push_back(15178);
        internalCounters.push_back(15306);
        internalCounters.push_back(15434);
        internalCounters.push_back(15562);
        internalCounters.push_back(15690);
        internalCounters.push_back(15818);
        internalCounters.push_back(15946);
        internalCounters.push_back(16074);
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSWriteSize", "#ComputeShader#The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,sum12,(32),*,(1024),/,12,13,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14658);
        internalCounters.push_back(14786);
        internalCounters.push_back(14914);
        internalCounters.push_back(15042);
        internalCounters.push_back(15170);
        internalCounters.push_back(15298);
        internalCounters.push_back(15426);
        internalCounters.push_back(15554);
        internalCounters.push_back(15682);
        internalCounters.push_back(15810);
        internalCounters.push_back(15938);
        internalCounters.push_back(16066);
        internalCounters.push_back(14659);
        internalCounters.push_back(14787);
        internalCounters.push_back(14915);
        internalCounters.push_back(15043);
        internalCounters.push_back(15171);
        internalCounters.push_back(15299);
        internalCounters.push_back(15427);
        internalCounters.push_back(15555);
        internalCounters.push_back(15683);
        internalCounters.push_back(15811);
        internalCounters.push_back(15939);
        internalCounters.push_back(16067);
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSCacheHit", "#ComputeShader#The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,sum12,0,1,2,3,4,5,6,7,8,9,10,11,sum12,12,13,14,15,16,17,18,19,20,21,22,23,sum12,+,/,(100),*,24,25,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14667);
        internalCounters.push_back(14795);
        internalCounters.push_back(14923);
        internalCounters.push_back(15051);
        internalCounters.push_back(15179);
        internalCounters.push_back(15307);
        internalCounters.push_back(15435);
        internalCounters.push_back(15563);
        internalCounters.push_back(15691);
        internalCounters.push_back(15819);
        internalCounters.push_back(15947);
        internalCounters.push_back(16075);
        internalCounters.push_back(3892);
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSWriteUnitStalled", "#ComputeShader#The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,max,2,max,3,max,4,max,5,max,7,max,8,max,9,max,10,max,11,max,12,/,(100),*,13,14,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5391);
        internalCounters.push_back(5790);
        internalCounters.push_back(5374);
        internalCounters.push_back(5773);
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSGDSInsts", "#ComputeShader#The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,+,2,3,+,/,4,5,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5390);
        internalCounters.push_back(5789);
        internalCounters.push_back(5374);
        internalCounters.push_back(5773);
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSLDSInsts", "#ComputeShader#The average number of LDS read/write instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,+,2,3,+,/,4,5,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5409);
        internalCounters.push_back(5808);
        internalCounters.push_back(5374);
        internalCounters.push_back(5773);
        internalCounters.push_back(3892);
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSALUStalledByLDS", "#ComputeShader#The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,+,2,3,+,/,4,/,NUM_SHADER_ENGINES,/,(100),*,5,6,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5432);
        internalCounters.push_back(5831);
        internalCounters.push_back(3892);
        internalCounters.push_back(5040);
        internalCounters.push_back(5229);

        p.DefinePublicCounter("CSLDSBankConflict", "#ComputeShader#The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,+,2,/,NUM_SIMDS,/,(100),*,3,4,+,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6168);
        internalCounters.push_back(6274);
        internalCounters.push_back(6380);
        internalCounters.push_back(6486);
        internalCounters.push_back(6592);
        internalCounters.push_back(6698);
        internalCounters.push_back(6804);
        internalCounters.push_back(6910);
        internalCounters.push_back(7016);
        internalCounters.push_back(7122);
        internalCounters.push_back(7228);
        internalCounters.push_back(7334);
        internalCounters.push_back(7440);
        internalCounters.push_back(7546);
        internalCounters.push_back(7652);
        internalCounters.push_back(7758);
        internalCounters.push_back(7864);
        internalCounters.push_back(7970);
        internalCounters.push_back(8076);
        internalCounters.push_back(8182);
        internalCounters.push_back(8288);
        internalCounters.push_back(8394);
        internalCounters.push_back(8500);
        internalCounters.push_back(8606);
        internalCounters.push_back(8712);
        internalCounters.push_back(8818);
        internalCounters.push_back(8924);
        internalCounters.push_back(9030);
        internalCounters.push_back(9136);
        internalCounters.push_back(9242);
        internalCounters.push_back(9348);
        internalCounters.push_back(9454);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("TexUnitBusy", "#Timing#The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max,16,max,17,max,18,max,19,max,20,max,21,max,22,max,23,max,24,max,25,max,26,max,27,max,28,max,29,max,30,max,31,max,32,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6237);
        internalCounters.push_back(6343);
        internalCounters.push_back(6449);
        internalCounters.push_back(6555);
        internalCounters.push_back(6661);
        internalCounters.push_back(6767);
        internalCounters.push_back(6873);
        internalCounters.push_back(6979);
        internalCounters.push_back(7085);
        internalCounters.push_back(7191);
        internalCounters.push_back(7297);
        internalCounters.push_back(7403);
        internalCounters.push_back(7509);
        internalCounters.push_back(7615);
        internalCounters.push_back(7721);
        internalCounters.push_back(7827);
        internalCounters.push_back(7933);
        internalCounters.push_back(8039);
        internalCounters.push_back(8145);
        internalCounters.push_back(8251);
        internalCounters.push_back(8357);
        internalCounters.push_back(8463);
        internalCounters.push_back(8569);
        internalCounters.push_back(8675);
        internalCounters.push_back(8781);
        internalCounters.push_back(8887);
        internalCounters.push_back(8993);
        internalCounters.push_back(9099);
        internalCounters.push_back(9205);
        internalCounters.push_back(9311);
        internalCounters.push_back(9417);
        internalCounters.push_back(9523);
        internalCounters.push_back(6236);
        internalCounters.push_back(6342);
        internalCounters.push_back(6448);
        internalCounters.push_back(6554);
        internalCounters.push_back(6660);
        internalCounters.push_back(6766);
        internalCounters.push_back(6872);
        internalCounters.push_back(6978);
        internalCounters.push_back(7084);
        internalCounters.push_back(7190);
        internalCounters.push_back(7296);
        internalCounters.push_back(7402);
        internalCounters.push_back(7508);
        internalCounters.push_back(7614);
        internalCounters.push_back(7720);
        internalCounters.push_back(7826);
        internalCounters.push_back(7932);
        internalCounters.push_back(8038);
        internalCounters.push_back(8144);
        internalCounters.push_back(8250);
        internalCounters.push_back(8356);
        internalCounters.push_back(8462);
        internalCounters.push_back(8568);
        internalCounters.push_back(8674);
        internalCounters.push_back(8780);
        internalCounters.push_back(8886);
        internalCounters.push_back(8992);
        internalCounters.push_back(9098);
        internalCounters.push_back(9204);
        internalCounters.push_back(9310);
        internalCounters.push_back(9416);
        internalCounters.push_back(9522);

        p.DefinePublicCounter("TexTriFilteringPct", "#TextureUnit#Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum32,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6239);
        internalCounters.push_back(6345);
        internalCounters.push_back(6451);
        internalCounters.push_back(6557);
        internalCounters.push_back(6663);
        internalCounters.push_back(6769);
        internalCounters.push_back(6875);
        internalCounters.push_back(6981);
        internalCounters.push_back(7087);
        internalCounters.push_back(7193);
        internalCounters.push_back(7299);
        internalCounters.push_back(7405);
        internalCounters.push_back(7511);
        internalCounters.push_back(7617);
        internalCounters.push_back(7723);
        internalCounters.push_back(7829);
        internalCounters.push_back(7935);
        internalCounters.push_back(8041);
        internalCounters.push_back(8147);
        internalCounters.push_back(8253);
        internalCounters.push_back(8359);
        internalCounters.push_back(8465);
        internalCounters.push_back(8571);
        internalCounters.push_back(8677);
        internalCounters.push_back(8783);
        internalCounters.push_back(8889);
        internalCounters.push_back(8995);
        internalCounters.push_back(9101);
        internalCounters.push_back(9207);
        internalCounters.push_back(9313);
        internalCounters.push_back(9419);
        internalCounters.push_back(9525);
        internalCounters.push_back(6238);
        internalCounters.push_back(6344);
        internalCounters.push_back(6450);
        internalCounters.push_back(6556);
        internalCounters.push_back(6662);
        internalCounters.push_back(6768);
        internalCounters.push_back(6874);
        internalCounters.push_back(6980);
        internalCounters.push_back(7086);
        internalCounters.push_back(7192);
        internalCounters.push_back(7298);
        internalCounters.push_back(7404);
        internalCounters.push_back(7510);
        internalCounters.push_back(7616);
        internalCounters.push_back(7722);
        internalCounters.push_back(7828);
        internalCounters.push_back(7934);
        internalCounters.push_back(8040);
        internalCounters.push_back(8146);
        internalCounters.push_back(8252);
        internalCounters.push_back(8358);
        internalCounters.push_back(8464);
        internalCounters.push_back(8570);
        internalCounters.push_back(8676);
        internalCounters.push_back(8782);
        internalCounters.push_back(8888);
        internalCounters.push_back(8994);
        internalCounters.push_back(9100);
        internalCounters.push_back(9206);
        internalCounters.push_back(9312);
        internalCounters.push_back(9418);
        internalCounters.push_back(9524);

        p.DefinePublicCounter("TexVolFilteringPct", "#TextureUnit#Percentage of pixels that received volume filtering.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum32,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6257);
        internalCounters.push_back(6363);
        internalCounters.push_back(6469);
        internalCounters.push_back(6575);
        internalCounters.push_back(6681);
        internalCounters.push_back(6787);
        internalCounters.push_back(6893);
        internalCounters.push_back(6999);
        internalCounters.push_back(7105);
        internalCounters.push_back(7211);
        internalCounters.push_back(7317);
        internalCounters.push_back(7423);
        internalCounters.push_back(7529);
        internalCounters.push_back(7635);
        internalCounters.push_back(7741);
        internalCounters.push_back(7847);
        internalCounters.push_back(7953);
        internalCounters.push_back(8059);
        internalCounters.push_back(8165);
        internalCounters.push_back(8271);
        internalCounters.push_back(8377);
        internalCounters.push_back(8483);
        internalCounters.push_back(8589);
        internalCounters.push_back(8695);
        internalCounters.push_back(8801);
        internalCounters.push_back(8907);
        internalCounters.push_back(9013);
        internalCounters.push_back(9119);
        internalCounters.push_back(9225);
        internalCounters.push_back(9331);
        internalCounters.push_back(9437);
        internalCounters.push_back(9543);
        internalCounters.push_back(6258);
        internalCounters.push_back(6364);
        internalCounters.push_back(6470);
        internalCounters.push_back(6576);
        internalCounters.push_back(6682);
        internalCounters.push_back(6788);
        internalCounters.push_back(6894);
        internalCounters.push_back(7000);
        internalCounters.push_back(7106);
        internalCounters.push_back(7212);
        internalCounters.push_back(7318);
        internalCounters.push_back(7424);
        internalCounters.push_back(7530);
        internalCounters.push_back(7636);
        internalCounters.push_back(7742);
        internalCounters.push_back(7848);
        internalCounters.push_back(7954);
        internalCounters.push_back(8060);
        internalCounters.push_back(8166);
        internalCounters.push_back(8272);
        internalCounters.push_back(8378);
        internalCounters.push_back(8484);
        internalCounters.push_back(8590);
        internalCounters.push_back(8696);
        internalCounters.push_back(8802);
        internalCounters.push_back(8908);
        internalCounters.push_back(9014);
        internalCounters.push_back(9120);
        internalCounters.push_back(9226);
        internalCounters.push_back(9332);
        internalCounters.push_back(9438);
        internalCounters.push_back(9544);
        internalCounters.push_back(6259);
        internalCounters.push_back(6365);
        internalCounters.push_back(6471);
        internalCounters.push_back(6577);
        internalCounters.push_back(6683);
        internalCounters.push_back(6789);
        internalCounters.push_back(6895);
        internalCounters.push_back(7001);
        internalCounters.push_back(7107);
        internalCounters.push_back(7213);
        internalCounters.push_back(7319);
        internalCounters.push_back(7425);
        internalCounters.push_back(7531);
        internalCounters.push_back(7637);
        internalCounters.push_back(7743);
        internalCounters.push_back(7849);
        internalCounters.push_back(7955);
        internalCounters.push_back(8061);
        internalCounters.push_back(8167);
        internalCounters.push_back(8273);
        internalCounters.push_back(8379);
        internalCounters.push_back(8485);
        internalCounters.push_back(8591);
        internalCounters.push_back(8697);
        internalCounters.push_back(8803);
        internalCounters.push_back(8909);
        internalCounters.push_back(9015);
        internalCounters.push_back(9121);
        internalCounters.push_back(9227);
        internalCounters.push_back(9333);
        internalCounters.push_back(9439);
        internalCounters.push_back(9545);
        internalCounters.push_back(6260);
        internalCounters.push_back(6366);
        internalCounters.push_back(6472);
        internalCounters.push_back(6578);
        internalCounters.push_back(6684);
        internalCounters.push_back(6790);
        internalCounters.push_back(6896);
        internalCounters.push_back(7002);
        internalCounters.push_back(7108);
        internalCounters.push_back(7214);
        internalCounters.push_back(7320);
        internalCounters.push_back(7426);
        internalCounters.push_back(7532);
        internalCounters.push_back(7638);
        internalCounters.push_back(7744);
        internalCounters.push_back(7850);
        internalCounters.push_back(7956);
        internalCounters.push_back(8062);
        internalCounters.push_back(8168);
        internalCounters.push_back(8274);
        internalCounters.push_back(8380);
        internalCounters.push_back(8486);
        internalCounters.push_back(8592);
        internalCounters.push_back(8698);
        internalCounters.push_back(8804);
        internalCounters.push_back(8910);
        internalCounters.push_back(9016);
        internalCounters.push_back(9122);
        internalCounters.push_back(9228);
        internalCounters.push_back(9334);
        internalCounters.push_back(9440);
        internalCounters.push_back(9546);
        internalCounters.push_back(6261);
        internalCounters.push_back(6367);
        internalCounters.push_back(6473);
        internalCounters.push_back(6579);
        internalCounters.push_back(6685);
        internalCounters.push_back(6791);
        internalCounters.push_back(6897);
        internalCounters.push_back(7003);
        internalCounters.push_back(7109);
        internalCounters.push_back(7215);
        internalCounters.push_back(7321);
        internalCounters.push_back(7427);
        internalCounters.push_back(7533);
        internalCounters.push_back(7639);
        internalCounters.push_back(7745);
        internalCounters.push_back(7851);
        internalCounters.push_back(7957);
        internalCounters.push_back(8063);
        internalCounters.push_back(8169);
        internalCounters.push_back(8275);
        internalCounters.push_back(8381);
        internalCounters.push_back(8487);
        internalCounters.push_back(8593);
        internalCounters.push_back(8699);
        internalCounters.push_back(8805);
        internalCounters.push_back(8911);
        internalCounters.push_back(9017);
        internalCounters.push_back(9123);
        internalCounters.push_back(9229);
        internalCounters.push_back(9335);
        internalCounters.push_back(9441);
        internalCounters.push_back(9547);
        internalCounters.push_back(6262);
        internalCounters.push_back(6368);
        internalCounters.push_back(6474);
        internalCounters.push_back(6580);
        internalCounters.push_back(6686);
        internalCounters.push_back(6792);
        internalCounters.push_back(6898);
        internalCounters.push_back(7004);
        internalCounters.push_back(7110);
        internalCounters.push_back(7216);
        internalCounters.push_back(7322);
        internalCounters.push_back(7428);
        internalCounters.push_back(7534);
        internalCounters.push_back(7640);
        internalCounters.push_back(7746);
        internalCounters.push_back(7852);
        internalCounters.push_back(7958);
        internalCounters.push_back(8064);
        internalCounters.push_back(8170);
        internalCounters.push_back(8276);
        internalCounters.push_back(8382);
        internalCounters.push_back(8488);
        internalCounters.push_back(8594);
        internalCounters.push_back(8700);
        internalCounters.push_back(8806);
        internalCounters.push_back(8912);
        internalCounters.push_back(9018);
        internalCounters.push_back(9124);
        internalCounters.push_back(9230);
        internalCounters.push_back(9336);
        internalCounters.push_back(9442);
        internalCounters.push_back(9548);
        internalCounters.push_back(6263);
        internalCounters.push_back(6369);
        internalCounters.push_back(6475);
        internalCounters.push_back(6581);
        internalCounters.push_back(6687);
        internalCounters.push_back(6793);
        internalCounters.push_back(6899);
        internalCounters.push_back(7005);
        internalCounters.push_back(7111);
        internalCounters.push_back(7217);
        internalCounters.push_back(7323);
        internalCounters.push_back(7429);
        internalCounters.push_back(7535);
        internalCounters.push_back(7641);
        internalCounters.push_back(7747);
        internalCounters.push_back(7853);
        internalCounters.push_back(7959);
        internalCounters.push_back(8065);
        internalCounters.push_back(8171);
        internalCounters.push_back(8277);
        internalCounters.push_back(8383);
        internalCounters.push_back(8489);
        internalCounters.push_back(8595);
        internalCounters.push_back(8701);
        internalCounters.push_back(8807);
        internalCounters.push_back(8913);
        internalCounters.push_back(9019);
        internalCounters.push_back(9125);
        internalCounters.push_back(9231);
        internalCounters.push_back(9337);
        internalCounters.push_back(9443);
        internalCounters.push_back(9549);
        internalCounters.push_back(6264);
        internalCounters.push_back(6370);
        internalCounters.push_back(6476);
        internalCounters.push_back(6582);
        internalCounters.push_back(6688);
        internalCounters.push_back(6794);
        internalCounters.push_back(6900);
        internalCounters.push_back(7006);
        internalCounters.push_back(7112);
        internalCounters.push_back(7218);
        internalCounters.push_back(7324);
        internalCounters.push_back(7430);
        internalCounters.push_back(7536);
        internalCounters.push_back(7642);
        internalCounters.push_back(7748);
        internalCounters.push_back(7854);
        internalCounters.push_back(7960);
        internalCounters.push_back(8066);
        internalCounters.push_back(8172);
        internalCounters.push_back(8278);
        internalCounters.push_back(8384);
        internalCounters.push_back(8490);
        internalCounters.push_back(8596);
        internalCounters.push_back(8702);
        internalCounters.push_back(8808);
        internalCounters.push_back(8914);
        internalCounters.push_back(9020);
        internalCounters.push_back(9126);
        internalCounters.push_back(9232);
        internalCounters.push_back(9338);
        internalCounters.push_back(9444);
        internalCounters.push_back(9550);
        internalCounters.push_back(6265);
        internalCounters.push_back(6371);
        internalCounters.push_back(6477);
        internalCounters.push_back(6583);
        internalCounters.push_back(6689);
        internalCounters.push_back(6795);
        internalCounters.push_back(6901);
        internalCounters.push_back(7007);
        internalCounters.push_back(7113);
        internalCounters.push_back(7219);
        internalCounters.push_back(7325);
        internalCounters.push_back(7431);
        internalCounters.push_back(7537);
        internalCounters.push_back(7643);
        internalCounters.push_back(7749);
        internalCounters.push_back(7855);
        internalCounters.push_back(7961);
        internalCounters.push_back(8067);
        internalCounters.push_back(8173);
        internalCounters.push_back(8279);
        internalCounters.push_back(8385);
        internalCounters.push_back(8491);
        internalCounters.push_back(8597);
        internalCounters.push_back(8703);
        internalCounters.push_back(8809);
        internalCounters.push_back(8915);
        internalCounters.push_back(9021);
        internalCounters.push_back(9127);
        internalCounters.push_back(9233);
        internalCounters.push_back(9339);
        internalCounters.push_back(9445);
        internalCounters.push_back(9551);

        p.DefinePublicCounter("TexAveAnisotropy", "#TextureUnit#The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,(2),32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum32,*,+,(4),64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum32,*,+,(6),96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum32,*,+,(8),128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,sum32,*,+,(10),160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,sum32,*,+,(12),192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,sum32,*,+,(14),224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,sum32,*,+,(16),256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,sum32,*,+,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum32,+,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum32,+,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum32,+,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,sum32,+,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,sum32,+,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,sum32,+,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,sum32,+,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,sum32,+,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2043);
        internalCounters.push_back(2292);
        internalCounters.push_back(2541);
        internalCounters.push_back(2790);
        internalCounters.push_back(3039);
        internalCounters.push_back(3288);
        internalCounters.push_back(3537);
        internalCounters.push_back(3786);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("DepthStencilTestBusy", "#Timing#Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1913);
        internalCounters.push_back(2162);
        internalCounters.push_back(2411);
        internalCounters.push_back(2660);
        internalCounters.push_back(2909);
        internalCounters.push_back(3158);
        internalCounters.push_back(3407);
        internalCounters.push_back(3656);
        internalCounters.push_back(1902);
        internalCounters.push_back(2151);
        internalCounters.push_back(2400);
        internalCounters.push_back(2649);
        internalCounters.push_back(2898);
        internalCounters.push_back(3147);
        internalCounters.push_back(3396);
        internalCounters.push_back(3645);

        p.DefinePublicCounter("HiZTilesAccepted", "#DepthAndStencil#Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,sum8,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1902);
        internalCounters.push_back(2151);
        internalCounters.push_back(2400);
        internalCounters.push_back(2649);
        internalCounters.push_back(2898);
        internalCounters.push_back(3147);
        internalCounters.push_back(3396);
        internalCounters.push_back(3645);
        internalCounters.push_back(1926);
        internalCounters.push_back(2175);
        internalCounters.push_back(2424);
        internalCounters.push_back(2673);
        internalCounters.push_back(2922);
        internalCounters.push_back(3171);
        internalCounters.push_back(3420);
        internalCounters.push_back(3669);

        p.DefinePublicCounter("PreZTilesDetailCulled", "#DepthAndStencil#Percentage of tiles rejected because the associated prim had no contributing area.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "8,9,10,11,12,13,14,15,sum8,0,1,2,3,4,5,6,7,sum8,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4443);
        internalCounters.push_back(4735);
        internalCounters.push_back(4444);
        internalCounters.push_back(4736);
        internalCounters.push_back(4445);
        internalCounters.push_back(4737);
        internalCounters.push_back(4446);
        internalCounters.push_back(4738);
        internalCounters.push_back(4519);
        internalCounters.push_back(4811);
        internalCounters.push_back(4520);
        internalCounters.push_back(4812);
        internalCounters.push_back(4521);
        internalCounters.push_back(4813);
        internalCounters.push_back(4522);
        internalCounters.push_back(4814);

        p.DefinePublicCounter("HiZQuadsCulled", "#DepthAndStencil#Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,sum8,-,0,1,2,3,4,5,6,7,sum8,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4443);
        internalCounters.push_back(4735);
        internalCounters.push_back(4444);
        internalCounters.push_back(4736);
        internalCounters.push_back(4445);
        internalCounters.push_back(4737);
        internalCounters.push_back(4446);
        internalCounters.push_back(4738);
        internalCounters.push_back(4543);
        internalCounters.push_back(4835);
        internalCounters.push_back(4519);
        internalCounters.push_back(4811);
        internalCounters.push_back(4520);
        internalCounters.push_back(4812);
        internalCounters.push_back(4521);
        internalCounters.push_back(4813);
        internalCounters.push_back(4522);
        internalCounters.push_back(4814);

        p.DefinePublicCounter("PreZQuadsCulled", "#DepthAndStencil#Percentage of quads rejected based on the detailZ and earlyZ tests.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "10,11,12,13,14,15,16,17,sum8,8,9,+,-,0,1,2,3,4,5,6,7,sum8,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4543);
        internalCounters.push_back(4835);
        internalCounters.push_back(4443);
        internalCounters.push_back(4735);
        internalCounters.push_back(4444);
        internalCounters.push_back(4736);
        internalCounters.push_back(4445);
        internalCounters.push_back(4737);
        internalCounters.push_back(4446);
        internalCounters.push_back(4738);

        p.DefinePublicCounter("PostZQuads", "#DepthAndStencil#Percentage of quads for which the pixel shader will run and may be postZ tested.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,2,3,4,5,6,7,8,9,sum8,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2078);
        internalCounters.push_back(2327);
        internalCounters.push_back(2576);
        internalCounters.push_back(2825);
        internalCounters.push_back(3074);
        internalCounters.push_back(3323);
        internalCounters.push_back(3572);
        internalCounters.push_back(3821);

        p.DefinePublicCounter("PreZSamplesPassing", "#DepthAndStencil#Number of samples tested for Z before shading and passed.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,sum8");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2080);
        internalCounters.push_back(2329);
        internalCounters.push_back(2578);
        internalCounters.push_back(2827);
        internalCounters.push_back(3076);
        internalCounters.push_back(3325);
        internalCounters.push_back(3574);
        internalCounters.push_back(3823);

        p.DefinePublicCounter("PreZSamplesFailingS", "#DepthAndStencil#Number of samples tested for Z before shading and failed stencil test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,sum8");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2079);
        internalCounters.push_back(2328);
        internalCounters.push_back(2577);
        internalCounters.push_back(2826);
        internalCounters.push_back(3075);
        internalCounters.push_back(3324);
        internalCounters.push_back(3573);
        internalCounters.push_back(3822);

        p.DefinePublicCounter("PreZSamplesFailingZ", "#DepthAndStencil#Number of samples tested for Z before shading and failed Z test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,sum8");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2075);
        internalCounters.push_back(2324);
        internalCounters.push_back(2573);
        internalCounters.push_back(2822);
        internalCounters.push_back(3071);
        internalCounters.push_back(3320);
        internalCounters.push_back(3569);
        internalCounters.push_back(3818);

        p.DefinePublicCounter("PostZSamplesPassing", "#DepthAndStencil#Number of samples tested for Z after shading and passed.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,sum8");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2077);
        internalCounters.push_back(2326);
        internalCounters.push_back(2575);
        internalCounters.push_back(2824);
        internalCounters.push_back(3073);
        internalCounters.push_back(3322);
        internalCounters.push_back(3571);
        internalCounters.push_back(3820);

        p.DefinePublicCounter("PostZSamplesFailingS", "#DepthAndStencil#Number of samples tested for Z after shading and failed stencil test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,sum8");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2076);
        internalCounters.push_back(2325);
        internalCounters.push_back(2574);
        internalCounters.push_back(2823);
        internalCounters.push_back(3072);
        internalCounters.push_back(3321);
        internalCounters.push_back(3570);
        internalCounters.push_back(3819);

        p.DefinePublicCounter("PostZSamplesFailingZ", "#DepthAndStencil#Number of samples tested for Z after shading and failed Z test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,sum8");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1945);
        internalCounters.push_back(2194);
        internalCounters.push_back(2443);
        internalCounters.push_back(2692);
        internalCounters.push_back(2941);
        internalCounters.push_back(3190);
        internalCounters.push_back(3439);
        internalCounters.push_back(3688);
        internalCounters.push_back(3892);

        p.DefinePublicCounter("ZUnitStalled", "#DepthAndStencil#The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(305);
        internalCounters.push_back(520);
        internalCounters.push_back(735);
        internalCounters.push_back(950);
        internalCounters.push_back(1165);
        internalCounters.push_back(1380);
        internalCounters.push_back(1595);
        internalCounters.push_back(1810);

        p.DefinePublicCounter("CBMemRead", "#ColorBuffer#Number of bytes read from the color buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,sum8,(32),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(295);
        internalCounters.push_back(510);
        internalCounters.push_back(725);
        internalCounters.push_back(940);
        internalCounters.push_back(1155);
        internalCounters.push_back(1370);
        internalCounters.push_back(1585);
        internalCounters.push_back(1800);

        p.DefinePublicCounter("CBMemWritten", "#ColorBuffer#Number of bytes written to the color buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,sum8,(32),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(339);
        internalCounters.push_back(554);
        internalCounters.push_back(769);
        internalCounters.push_back(984);
        internalCounters.push_back(1199);
        internalCounters.push_back(1414);
        internalCounters.push_back(1629);
        internalCounters.push_back(1844);
        internalCounters.push_back(185);
        internalCounters.push_back(400);
        internalCounters.push_back(615);
        internalCounters.push_back(830);
        internalCounters.push_back(1045);
        internalCounters.push_back(1260);
        internalCounters.push_back(1475);
        internalCounters.push_back(1690);

        p.DefinePublicCounter("CBSlowPixelPct", "#ColorBuffer#Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,sum8,/,(100),*,(100),min");
    }
}

