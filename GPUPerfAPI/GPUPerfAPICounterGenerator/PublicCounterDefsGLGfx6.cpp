//==============================================================================
// Copyright (c) 2010-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  PublicCounterDefinitions for GLGFX6
//==============================================================================

#include "PublicCounterDefsGLGfx6.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicCountersGLGfx6(GPA_PublicCounters& p)
{
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8883);

        p.DefinePublicCounter("GPUTime", "#Timing#Time this API call took to execute on the GPU in milliseconds. Does not include time that draw calls are processed in parallel.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_API_DYNAMIC, internalCounters, "0,TS_FREQ,/,(1000),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(976);
        internalCounters.push_back(974);

        p.DefinePublicCounter("GPUBusy", "#Timing#The percentage of time GPU was busy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8775);
        internalCounters.push_back(976);

        p.DefinePublicCounter("TessellatorBusy", "#Timing#The percentage of time the tessellation engine is busy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1447);
        internalCounters.push_back(1465);
        internalCounters.push_back(1483);
        internalCounters.push_back(1513);
        internalCounters.push_back(1456);
        internalCounters.push_back(1471);
        internalCounters.push_back(1489);
        internalCounters.push_back(976);

        p.DefinePublicCounter("VSBusy", "#Timing#The percentage of time the ShaderUnit has vertex shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,1,5,ifnotzero,2,6,ifnotzero,7,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8883);
        internalCounters.push_back(1447);
        internalCounters.push_back(1465);
        internalCounters.push_back(1483);
        internalCounters.push_back(1513);
        internalCounters.push_back(1456);
        internalCounters.push_back(1471);
        internalCounters.push_back(1489);
        internalCounters.push_back(976);

        p.DefinePublicCounter("VSTime", "#Timing#Time vertex shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,5,ifnotzero,2,6,ifnotzero,3,7,ifnotzero,8,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1474);
        internalCounters.push_back(1480);
        internalCounters.push_back(976);

        p.DefinePublicCounter("HSBusy", "#Timing#The percentage of time the ShaderUnit has hull shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8883);
        internalCounters.push_back(1474);
        internalCounters.push_back(1480);
        internalCounters.push_back(976);

        p.DefinePublicCounter("HSTime", "#Timing#Time hull shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1447);
        internalCounters.push_back(1465);
        internalCounters.push_back(1513);
        internalCounters.push_back(1471);
        internalCounters.push_back(1489);
        internalCounters.push_back(976);

        p.DefinePublicCounter("DSBusy", "#Timing#The percentage of time the ShaderUnit has domain shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,5,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8883);
        internalCounters.push_back(1447);
        internalCounters.push_back(1465);
        internalCounters.push_back(1513);
        internalCounters.push_back(1471);
        internalCounters.push_back(1489);
        internalCounters.push_back(976);

        p.DefinePublicCounter("DSTime", "#Timing#Time domain shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,4,ifnotzero,5,ifnotzero,6,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1459);
        internalCounters.push_back(1462);
        internalCounters.push_back(976);

        p.DefinePublicCounter("GSBusy", "#Timing#The percentage of time the ShaderUnit has geometry shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8883);
        internalCounters.push_back(1459);
        internalCounters.push_back(1462);
        internalCounters.push_back(976);

        p.DefinePublicCounter("GSTime", "#Timing#Time geometry shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1513);
        internalCounters.push_back(1520);
        internalCounters.push_back(976);

        p.DefinePublicCounter("PSBusy", "#Timing#The percentage of time the ShaderUnit has pixel shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8883);
        internalCounters.push_back(1513);
        internalCounters.push_back(1520);
        internalCounters.push_back(976);

        p.DefinePublicCounter("PSTime", "#Timing#Time pixel shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1492);
        internalCounters.push_back(1497);
        internalCounters.push_back(976);

        p.DefinePublicCounter("CSBusy", "#Timing#The percentage of time the ShaderUnit has compute shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8883);
        internalCounters.push_back(1492);
        internalCounters.push_back(1497);
        internalCounters.push_back(976);

        p.DefinePublicCounter("CSTime", "#Timing#Time compute shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8670);
        internalCounters.push_back(8651);
        internalCounters.push_back(8746);

        p.DefinePublicCounter("VSVerticesIn", "#VertexShader#The number of vertices processed by the VS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8755);

        p.DefinePublicCounter("HSPatches", "#HullShader#The number of patches processed by the HS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8670);
        internalCounters.push_back(8651);
        internalCounters.push_back(8746);

        p.DefinePublicCounter("DSVerticesIn", "#DomainShader#The number of vertices processed by the DS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,1,ifnotzero,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8659);

        p.DefinePublicCounter("GSPrimsIn", "#GeometryShader#The number of primitives passed into the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8670);
        internalCounters.push_back(8651);

        p.DefinePublicCounter("GSVerticesOut", "#GeometryShader#The number of vertices output by the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1123);
        internalCounters.push_back(1127);
        internalCounters.push_back(1079);
        internalCounters.push_back(1091);
        internalCounters.push_back(1080);
        internalCounters.push_back(1092);
        internalCounters.push_back(976);

        p.DefinePublicCounter("PrimitiveAssemblyBusy", "#Timing#The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max,6,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1026);

        p.DefinePublicCounter("PrimitivesIn", "#PrimitiveAssembly#The number of primitives received by the hardware. This includes primitives generated by tessellation.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1032);
        internalCounters.push_back(1072);
        internalCounters.push_back(1073);
        internalCounters.push_back(1074);
        internalCounters.push_back(1075);

        p.DefinePublicCounter("CulledPrims", "#PrimitiveAssembly#The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,2,+,3,+,4,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1039);

        p.DefinePublicCounter("ClippedPrims", "#PrimitiveAssembly#The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1127);
        internalCounters.push_back(976);

        p.DefinePublicCounter("PAStalledOnRasterizer", "#PrimitiveAssembly#Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4839);
        internalCounters.push_back(4844);
        internalCounters.push_back(4849);
        internalCounters.push_back(4854);

        p.DefinePublicCounter("PSPixelsOut", "#PixelShader#Pixels exported from shader to colour buffers. Does not include killed or alpha tested pixels; if there are multiple rendertargets, each rendertarget receives one export, so this will be 2 for 1 pixel written to two RTs.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4841);
        internalCounters.push_back(4846);
        internalCounters.push_back(4851);
        internalCounters.push_back(4856);
        internalCounters.push_back(976);

        p.DefinePublicCounter("PSExportStalls", "#PixelShader#Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the colour buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSThreadGroups", "#ComputeShader#Total number of thread groups.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1497);

        p.DefinePublicCounter("CSWavefronts", "#ComputeShader#The total number of wavefronts used for the CS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1494);
        internalCounters.push_back(1644);

        p.DefinePublicCounter("CSThreads", "#ComputeShader#The number of CS threads processed by the hardware.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,0,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1649);
        internalCounters.push_back(1639);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSVALUInsts", "#ComputeShader#The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1693);
        internalCounters.push_back(1685);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSVALUUtilization", "#ComputeShader#The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,(64),*,/,(100),*,2,ifnotzero,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1653);
        internalCounters.push_back(1639);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSSALUInsts", "#ComputeShader#The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1651);
        internalCounters.push_back(1639);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSVFetchInsts", "#ComputeShader#The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1654);
        internalCounters.push_back(1639);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSSFetchInsts", "#ComputeShader#The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1650);
        internalCounters.push_back(1639);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSVWriteInsts", "#ComputeShader#The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1685);
        internalCounters.push_back(976);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSVALUBusy", "#ComputeShader#The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,(4),*,NUM_SIMDS,/,1,/,(100),*,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1690);
        internalCounters.push_back(976);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSSALUBusy", "#ComputeShader#The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4859);
        internalCounters.push_back(4965);
        internalCounters.push_back(5071);
        internalCounters.push_back(5177);
        internalCounters.push_back(5283);
        internalCounters.push_back(5389);
        internalCounters.push_back(5495);
        internalCounters.push_back(5601);
        internalCounters.push_back(976);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSMemUnitBusy", "#ComputeShader#The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,/,NUM_SHADER_ENGINES,/,(100),*,9,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7708);
        internalCounters.push_back(7818);
        internalCounters.push_back(7928);
        internalCounters.push_back(8038);
        internalCounters.push_back(8148);
        internalCounters.push_back(8258);
        internalCounters.push_back(8368);
        internalCounters.push_back(8478);
        internalCounters.push_back(976);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSMemUnitStalled", "#ComputeShader#The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,/,NUM_SHADER_ENGINES,/,(100),*,9,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5801);
        internalCounters.push_back(5929);
        internalCounters.push_back(6057);
        internalCounters.push_back(6185);
        internalCounters.push_back(6313);
        internalCounters.push_back(6441);
        internalCounters.push_back(6569);
        internalCounters.push_back(6697);
        internalCounters.push_back(6825);
        internalCounters.push_back(6953);
        internalCounters.push_back(7081);
        internalCounters.push_back(7209);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSFetchSize", "#ComputeShader#The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,sum12,(32),*,(1024),/,12,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5795);
        internalCounters.push_back(5923);
        internalCounters.push_back(6051);
        internalCounters.push_back(6179);
        internalCounters.push_back(6307);
        internalCounters.push_back(6435);
        internalCounters.push_back(6563);
        internalCounters.push_back(6691);
        internalCounters.push_back(6819);
        internalCounters.push_back(6947);
        internalCounters.push_back(7075);
        internalCounters.push_back(7203);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSWriteSize", "#ComputeShader#The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,sum12,(32),*,(1024),/,12,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5787);
        internalCounters.push_back(5915);
        internalCounters.push_back(6043);
        internalCounters.push_back(6171);
        internalCounters.push_back(6299);
        internalCounters.push_back(6427);
        internalCounters.push_back(6555);
        internalCounters.push_back(6683);
        internalCounters.push_back(6811);
        internalCounters.push_back(6939);
        internalCounters.push_back(7067);
        internalCounters.push_back(7195);
        internalCounters.push_back(5788);
        internalCounters.push_back(5916);
        internalCounters.push_back(6044);
        internalCounters.push_back(6172);
        internalCounters.push_back(6300);
        internalCounters.push_back(6428);
        internalCounters.push_back(6556);
        internalCounters.push_back(6684);
        internalCounters.push_back(6812);
        internalCounters.push_back(6940);
        internalCounters.push_back(7068);
        internalCounters.push_back(7196);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSCacheHit", "#ComputeShader#The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,sum12,0,1,2,3,4,5,6,7,8,9,10,11,sum12,12,13,14,15,16,17,18,19,20,21,22,23,sum12,+,/,(100),*,24,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5796);
        internalCounters.push_back(5924);
        internalCounters.push_back(6052);
        internalCounters.push_back(6180);
        internalCounters.push_back(6308);
        internalCounters.push_back(6436);
        internalCounters.push_back(6564);
        internalCounters.push_back(6692);
        internalCounters.push_back(6820);
        internalCounters.push_back(6948);
        internalCounters.push_back(7076);
        internalCounters.push_back(7204);
        internalCounters.push_back(976);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSWriteUnitStalled", "#ComputeShader#The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,max,2,max,3,max,4,max,5,max,7,max,8,max,9,max,10,max,11,max,12,/,(100),*,13,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1656);
        internalCounters.push_back(1639);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSGDSInsts", "#ComputeShader#The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1655);
        internalCounters.push_back(1639);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSLDSInsts", "#ComputeShader#The average number of LDS read/write instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1674);
        internalCounters.push_back(1639);
        internalCounters.push_back(976);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSALUStalledByLDS", "#ComputeShader#The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,2,/,NUM_SHADER_ENGINES,/,(100),*,3,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1697);
        internalCounters.push_back(976);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSLDSBankConflict", "#ComputeShader#The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,/,NUM_SIMDS,/,(100),*,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4859);
        internalCounters.push_back(4965);
        internalCounters.push_back(5071);
        internalCounters.push_back(5177);
        internalCounters.push_back(5283);
        internalCounters.push_back(5389);
        internalCounters.push_back(5495);
        internalCounters.push_back(5601);
        internalCounters.push_back(976);

        p.DefinePublicCounter("TexUnitBusy", "#Timing#The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,/,NUM_SHADER_ENGINES,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4928);
        internalCounters.push_back(5034);
        internalCounters.push_back(5140);
        internalCounters.push_back(5246);
        internalCounters.push_back(5352);
        internalCounters.push_back(5458);
        internalCounters.push_back(5564);
        internalCounters.push_back(5670);
        internalCounters.push_back(4927);
        internalCounters.push_back(5033);
        internalCounters.push_back(5139);
        internalCounters.push_back(5245);
        internalCounters.push_back(5351);
        internalCounters.push_back(5457);
        internalCounters.push_back(5563);
        internalCounters.push_back(5669);

        p.DefinePublicCounter("TexTriFilteringPct", "#TextureUnit#Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,sum8,0,1,2,3,4,5,6,7,sum8,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4930);
        internalCounters.push_back(5036);
        internalCounters.push_back(5142);
        internalCounters.push_back(5248);
        internalCounters.push_back(5354);
        internalCounters.push_back(5460);
        internalCounters.push_back(5566);
        internalCounters.push_back(5672);
        internalCounters.push_back(4929);
        internalCounters.push_back(5035);
        internalCounters.push_back(5141);
        internalCounters.push_back(5247);
        internalCounters.push_back(5353);
        internalCounters.push_back(5459);
        internalCounters.push_back(5565);
        internalCounters.push_back(5671);

        p.DefinePublicCounter("TexVolFilteringPct", "#TextureUnit#Percentage of pixels that received volume filtering.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,sum8,0,1,2,3,4,5,6,7,sum8,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4948);
        internalCounters.push_back(5054);
        internalCounters.push_back(5160);
        internalCounters.push_back(5266);
        internalCounters.push_back(5372);
        internalCounters.push_back(5478);
        internalCounters.push_back(5584);
        internalCounters.push_back(5690);
        internalCounters.push_back(4949);
        internalCounters.push_back(5055);
        internalCounters.push_back(5161);
        internalCounters.push_back(5267);
        internalCounters.push_back(5373);
        internalCounters.push_back(5479);
        internalCounters.push_back(5585);
        internalCounters.push_back(5691);
        internalCounters.push_back(4950);
        internalCounters.push_back(5056);
        internalCounters.push_back(5162);
        internalCounters.push_back(5268);
        internalCounters.push_back(5374);
        internalCounters.push_back(5480);
        internalCounters.push_back(5586);
        internalCounters.push_back(5692);
        internalCounters.push_back(4951);
        internalCounters.push_back(5057);
        internalCounters.push_back(5163);
        internalCounters.push_back(5269);
        internalCounters.push_back(5375);
        internalCounters.push_back(5481);
        internalCounters.push_back(5587);
        internalCounters.push_back(5693);
        internalCounters.push_back(4952);
        internalCounters.push_back(5058);
        internalCounters.push_back(5164);
        internalCounters.push_back(5270);
        internalCounters.push_back(5376);
        internalCounters.push_back(5482);
        internalCounters.push_back(5588);
        internalCounters.push_back(5694);
        internalCounters.push_back(4953);
        internalCounters.push_back(5059);
        internalCounters.push_back(5165);
        internalCounters.push_back(5271);
        internalCounters.push_back(5377);
        internalCounters.push_back(5483);
        internalCounters.push_back(5589);
        internalCounters.push_back(5695);
        internalCounters.push_back(4954);
        internalCounters.push_back(5060);
        internalCounters.push_back(5166);
        internalCounters.push_back(5272);
        internalCounters.push_back(5378);
        internalCounters.push_back(5484);
        internalCounters.push_back(5590);
        internalCounters.push_back(5696);
        internalCounters.push_back(4955);
        internalCounters.push_back(5061);
        internalCounters.push_back(5167);
        internalCounters.push_back(5273);
        internalCounters.push_back(5379);
        internalCounters.push_back(5485);
        internalCounters.push_back(5591);
        internalCounters.push_back(5697);
        internalCounters.push_back(4956);
        internalCounters.push_back(5062);
        internalCounters.push_back(5168);
        internalCounters.push_back(5274);
        internalCounters.push_back(5380);
        internalCounters.push_back(5486);
        internalCounters.push_back(5592);
        internalCounters.push_back(5698);

        p.DefinePublicCounter("TexAveAnisotropy", "#TextureUnit#The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,sum8,(2),8,9,10,11,12,13,14,15,sum8,*,+,(4),16,17,18,19,20,21,22,23,sum8,*,+,(6),24,25,26,27,28,29,30,31,sum8,*,+,(8),32,33,34,35,36,37,38,39,sum8,*,+,(10),40,41,42,43,44,45,46,47,sum8,*,+,(12),48,49,50,51,52,53,54,55,sum8,*,+,(14),56,57,58,59,60,61,62,63,sum8,*,+,(16),64,65,66,67,68,69,70,71,sum8,*,+,0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,sum8,+,16,17,18,19,20,21,22,23,sum8,+,24,25,26,27,28,29,30,31,sum8,+,32,33,34,35,36,37,38,39,sum8,+,40,41,42,43,44,45,46,47,sum8,+,48,49,50,51,52,53,54,55,sum8,+,56,57,58,59,60,61,62,63,sum8,+,64,65,66,67,68,69,70,71,sum8,+,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(621);
        internalCounters.push_back(870);
        internalCounters.push_back(976);

        p.DefinePublicCounter("DepthStencilTestBusy", "#Timing#Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,/,NUM_SHADER_ENGINES,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(491);
        internalCounters.push_back(740);
        internalCounters.push_back(480);
        internalCounters.push_back(729);

        p.DefinePublicCounter("HiZTilesAccepted", "#DepthAndStencil#Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,2,3,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(480);
        internalCounters.push_back(729);
        internalCounters.push_back(504);
        internalCounters.push_back(753);

        p.DefinePublicCounter("PreZTilesDetailCulled", "#DepthAndStencil#Percentage of tiles rejected because the associated prim had no contributing area.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "2,3,+,0,1,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1317);
        internalCounters.push_back(1318);
        internalCounters.push_back(1319);
        internalCounters.push_back(1320);
        internalCounters.push_back(1393);
        internalCounters.push_back(1394);
        internalCounters.push_back(1395);
        internalCounters.push_back(1396);

        p.DefinePublicCounter("HiZQuadsCulled", "#DepthAndStencil#Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-,0,1,+,2,+,3,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1317);
        internalCounters.push_back(1318);
        internalCounters.push_back(1319);
        internalCounters.push_back(1320);
        internalCounters.push_back(1417);
        internalCounters.push_back(1393);
        internalCounters.push_back(1394);
        internalCounters.push_back(1395);
        internalCounters.push_back(1396);

        p.DefinePublicCounter("PreZQuadsCulled", "#DepthAndStencil#Percentage of quads rejected based on the detailZ and earlyZ tests.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "5,6,+,7,+,8,+,4,-,0,1,+,2,+,3,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1417);
        internalCounters.push_back(1317);
        internalCounters.push_back(1318);
        internalCounters.push_back(1319);
        internalCounters.push_back(1320);

        p.DefinePublicCounter("PostZQuads", "#DepthAndStencil#Percentage of quads for which the pixel shader will run and may be postZ tested.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,+,3,+,4,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(656);
        internalCounters.push_back(905);

        p.DefinePublicCounter("PreZSamplesPassing", "#DepthAndStencil#Number of samples tested for Z before shading and passed.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(658);
        internalCounters.push_back(907);

        p.DefinePublicCounter("PreZSamplesFailingS", "#DepthAndStencil#Number of samples tested for Z before shading and failed stencil test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(657);
        internalCounters.push_back(906);

        p.DefinePublicCounter("PreZSamplesFailingZ", "#DepthAndStencil#Number of samples tested for Z before shading and failed Z test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(653);
        internalCounters.push_back(902);

        p.DefinePublicCounter("PostZSamplesPassing", "#DepthAndStencil#Number of samples tested for Z after shading and passed.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(655);
        internalCounters.push_back(904);

        p.DefinePublicCounter("PostZSamplesFailingS", "#DepthAndStencil#Number of samples tested for Z after shading and failed stencil test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(654);
        internalCounters.push_back(903);

        p.DefinePublicCounter("PostZSamplesFailingZ", "#DepthAndStencil#Number of samples tested for Z after shading and failed Z test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(523);
        internalCounters.push_back(772);
        internalCounters.push_back(976);

        p.DefinePublicCounter("ZUnitStalled", "#DepthAndStencil#The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,/,NUM_SHADER_ENGINES,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(127);
        internalCounters.push_back(342);

        p.DefinePublicCounter("CBMemRead", "#ColorBuffer#Number of bytes read from the color buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,(32),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(117);
        internalCounters.push_back(332);

        p.DefinePublicCounter("CBMemWritten", "#ColorBuffer#Number of bytes written to the color buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,(32),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(161);
        internalCounters.push_back(376);
        internalCounters.push_back(7);
        internalCounters.push_back(222);

        p.DefinePublicCounter("CBSlowPixelPct", "#ColorBuffer#Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,2,3,+,/,(100),*,(100),min");
    }
}

