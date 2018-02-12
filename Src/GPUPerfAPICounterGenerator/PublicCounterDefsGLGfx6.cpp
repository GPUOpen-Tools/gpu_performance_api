//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for GLGFX6
//==============================================================================

#include "PublicCounterDefsGLGfx6.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicCountersGLGfx6(GPA_PublicCounters& p)
{
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8883);

        p.DefinePublicCounter("GPUTime", "Timing", "Time this API call took to execute on the GPU in milliseconds. Does not include time that draw calls are processed in parallel.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "0,TS_FREQ,/,(1000),*", "00bfa9cd-5512-48e8-7055-7b592113b8cb" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(976);
        internalCounters.push_back(974);

        p.DefinePublicCounter("GPUBusy", "Timing", "The percentage of time GPU was busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,(100),*,(100),min", "bef38bf3-1167-0844-81f0-67d2d28ddbc5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8775);
        internalCounters.push_back(976);

        p.DefinePublicCounter("TessellatorBusy", "Timing", "The percentage of time the tessellation engine is busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*", "36af6c72-dcfb-8102-4fd4-ce8ddc573365" );
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

        p.DefinePublicCounter("VSBusy", "Timing", "The percentage of time the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,4,ifnotzero,1,5,ifnotzero,2,6,ifnotzero,7,/,(100),*,(100),min", "94caad5e-867c-6c09-cf3a-d05b51df8f3b" );
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

        p.DefinePublicCounter("VSTime", "Timing", "Time vertex shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "(0),1,5,ifnotzero,2,6,ifnotzero,3,7,ifnotzero,8,/,(1),min,0,TS_FREQ,/,(1000),*,*", "fee660c7-8e01-4dc5-e5d0-fcb61c17fb2c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1474);
        internalCounters.push_back(1480);
        internalCounters.push_back(976);

        p.DefinePublicCounter("HSBusy", "Timing", "The percentage of time the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "16f30a0b-4cbf-eccd-b13f-ab68dd254d32" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8883);
        internalCounters.push_back(1474);
        internalCounters.push_back(1480);
        internalCounters.push_back(976);

        p.DefinePublicCounter("HSTime", "Timing", "Time hull shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*", "8792e9f1-fb39-b92a-b230-f33df4c8a0de" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1447);
        internalCounters.push_back(1465);
        internalCounters.push_back(1513);
        internalCounters.push_back(1471);
        internalCounters.push_back(1489);
        internalCounters.push_back(976);

        p.DefinePublicCounter("DSBusy", "Timing", "The percentage of time the ShaderUnit has domain shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,3,ifnotzero,4,ifnotzero,5,/,(100),*,(100),min", "0c626e8a-9b82-b6d4-d9a3-578509316301" );
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

        p.DefinePublicCounter("DSTime", "Timing", "Time domain shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "(0),1,2,4,ifnotzero,5,ifnotzero,6,/,(1),min,0,TS_FREQ,/,(1000),*,*", "f050e495-f511-ecc9-9c46-c96516bddeb2" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1459);
        internalCounters.push_back(1462);
        internalCounters.push_back(976);

        p.DefinePublicCounter("GSBusy", "Timing", "The percentage of time the ShaderUnit has geometry shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "876f36d8-d046-833f-7832-673cbffd0a45" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8883);
        internalCounters.push_back(1459);
        internalCounters.push_back(1462);
        internalCounters.push_back(976);

        p.DefinePublicCounter("GSTime", "Timing", "Time geometry shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*", "86d56794-f391-b601-9388-851b646d346c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1513);
        internalCounters.push_back(1520);
        internalCounters.push_back(976);

        p.DefinePublicCounter("PSBusy", "Timing", "The percentage of time the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "7e772beb-d82c-bd9a-aed0-fe504d416ce5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8883);
        internalCounters.push_back(1513);
        internalCounters.push_back(1520);
        internalCounters.push_back(976);

        p.DefinePublicCounter("PSTime", "Timing", "Time pixel shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*", "f564ee00-ffcf-f7f6-fcbf-f200205cd0cc" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1492);
        internalCounters.push_back(1497);
        internalCounters.push_back(976);

        p.DefinePublicCounter("CSBusy", "Timing", "The percentage of time the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "493fdd90-8d2b-a055-5e4e-2d29c3396b8c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8883);
        internalCounters.push_back(1492);
        internalCounters.push_back(1497);
        internalCounters.push_back(976);

        p.DefinePublicCounter("CSTime", "Timing", "Time compute shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000),*,*", "5177faaf-f59d-ee23-6e36-0ea087dca9dc" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8670);
        internalCounters.push_back(8651);
        internalCounters.push_back(8746);

        p.DefinePublicCounter("VSVerticesIn", "VertexShader", "The number of vertices processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero", "810a04c8-2ff4-081d-766d-bfa2bd4ad916" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8755);

        p.DefinePublicCounter("HSPatches", "HullShader", "The number of patches processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "d1bbd27d-d591-4509-df52-d329fb73a98f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8670);
        internalCounters.push_back(8651);
        internalCounters.push_back(8746);

        p.DefinePublicCounter("DSVerticesIn", "DomainShader", "The number of vertices processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,1,ifnotzero,2,ifnotzero", "b88d9d05-2418-e639-4e3d-3a5815855f8d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8659);

        p.DefinePublicCounter("GSPrimsIn", "GeometryShader", "The number of primitives passed into the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "20c29866-509a-aaab-2697-6b2c38f79953" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8670);
        internalCounters.push_back(8651);

        p.DefinePublicCounter("GSVerticesOut", "GeometryShader", "The number of vertices output by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,ifnotzero", "775b9736-319a-bd8a-48c9-68db9c91d978" );
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

        p.DefinePublicCounter("PrimitiveAssemblyBusy", "Timing", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max,6,/,(100),*,(100),min", "54ac5640-c4d7-95e2-20e0-6a9fdfc07333" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1026);

        p.DefinePublicCounter("PrimitivesIn", "PrimitiveAssembly", "The number of primitives received by the hardware. This includes primitives generated by tessellation.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "a515b80d-75c3-c7d2-0d2f-d7766b4759a6" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1032);
        internalCounters.push_back(1072);
        internalCounters.push_back(1073);
        internalCounters.push_back(1074);
        internalCounters.push_back(1075);

        p.DefinePublicCounter("CulledPrims", "PrimitiveAssembly", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+,4,+", "589bdf55-9192-280a-41c3-584bc94f2562" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1039);

        p.DefinePublicCounter("ClippedPrims", "PrimitiveAssembly", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "5ef6f9d5-155e-5baa-163f-8359d9ea9bbf" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1127);
        internalCounters.push_back(976);

        p.DefinePublicCounter("PAStalledOnRasterizer", "PrimitiveAssembly", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*", "6f9f416b-53c1-0457-f88c-7b6ba8973974" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4839);
        internalCounters.push_back(4844);
        internalCounters.push_back(4849);
        internalCounters.push_back(4854);

        p.DefinePublicCounter("PSPixelsOut", "PixelShader", "Pixels exported from shader to colour buffers. Does not include killed or alpha tested pixels; if there are multiple rendertargets, each rendertarget receives one export, so this will be 2 for 1 pixel written to two RTs.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "181f5ca1-ec90-61a3-fd73-d8e3722af9e9" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(4841);
        internalCounters.push_back(4846);
        internalCounters.push_back(4851);
        internalCounters.push_back(4856);
        internalCounters.push_back(976);

        p.DefinePublicCounter("PSExportStalls", "PixelShader", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the colour buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "996ce2b4-55ce-25c1-afb7-575bd9b4ce90" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSThreadGroups", "ComputeShader", "Total number of thread groups.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "8ce3fc80-56b2-97f9-8e70-2e8c747cea68" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1497);

        p.DefinePublicCounter("CSWavefronts", "ComputeShader", "The total number of wavefronts used for the CS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "42379c6e-369b-c237-8b25-cdb9cdc65c4d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1494);
        internalCounters.push_back(1644);

        p.DefinePublicCounter("CSThreads", "ComputeShader", "The number of CS threads processed by the hardware.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),1,0,ifnotzero", "7a648013-6eac-2665-ac36-13c6f4ac9c26" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1649);
        internalCounters.push_back(1639);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSVALUInsts", "ComputeShader", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,2,ifnotzero", "376cb1cc-5a40-9d1d-404c-f1736c0c5084" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1693);
        internalCounters.push_back(1685);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSVALUUtilization", "ComputeShader", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,(64),*,/,(100),*,2,ifnotzero,(100),min", "4476879e-cdc0-d602-b24e-9b4a8d38438f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1653);
        internalCounters.push_back(1639);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSSALUInsts", "ComputeShader", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,2,ifnotzero", "eb211144-8136-ff86-e8bf-4d0493a904cb" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1651);
        internalCounters.push_back(1639);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSVFetchInsts", "ComputeShader", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,2,ifnotzero", "3e2829c0-6215-783b-c271-6d57ff2c520e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1654);
        internalCounters.push_back(1639);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSSFetchInsts", "ComputeShader", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,2,ifnotzero", "da09171c-6a0a-584f-fddc-dc5062d63a3e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1650);
        internalCounters.push_back(1639);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSVWriteInsts", "ComputeShader", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,2,ifnotzero", "43438c22-e910-b377-b767-b32902e0df0d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1685);
        internalCounters.push_back(976);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSVALUBusy", "ComputeShader", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,(4),*,NUM_SIMDS,/,1,/,(100),*,2,ifnotzero", "f1e64815-f6a8-c277-d4f9-d054b443e205" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1690);
        internalCounters.push_back(976);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSSALUBusy", "ComputeShader", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,1,/,(100),*,2,ifnotzero", "3fc35f4e-9882-94e3-6f5f-4e81cd97082a" );
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

        p.DefinePublicCounter("CSMemUnitBusy", "ComputeShader", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,/,NUM_SHADER_ENGINES,/,(100),*,9,ifnotzero", "42ab96e1-0a24-96c8-c4ff-098fa267d78e" );
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

        p.DefinePublicCounter("CSMemUnitStalled", "ComputeShader", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,/,NUM_SHADER_ENGINES,/,(100),*,9,ifnotzero", "f18e8679-1511-d533-d9ee-4365197f7d0c" );
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

        p.DefinePublicCounter("CSFetchSize", "ComputeShader", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,sum12,(32),*,(1024),/,12,ifnotzero", "03cdb7e9-2bc3-15c1-811f-2106f3449295" );
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

        p.DefinePublicCounter("CSWriteSize", "ComputeShader", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,sum12,(32),*,(1024),/,12,ifnotzero", "3ec1ce55-d621-b7a5-5b8d-2909cf2dbe7d" );
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

        p.DefinePublicCounter("CSCacheHit", "ComputeShader", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,sum12,0,1,2,3,4,5,6,7,8,9,10,11,sum12,12,13,14,15,16,17,18,19,20,21,22,23,sum12,+,/,(100),*,24,ifnotzero", "50fdbc38-d099-5957-5f75-dfe5341b2187" );
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

        p.DefinePublicCounter("CSWriteUnitStalled", "ComputeShader", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,/,(100),*,13,ifnotzero", "3e0e1bdc-f66c-eddd-af3d-f8e9e8f45fd8" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1656);
        internalCounters.push_back(1639);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSGDSInsts", "ComputeShader", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,2,ifnotzero", "2a867f3e-4a37-ad16-55d1-f03d74707819" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1655);
        internalCounters.push_back(1639);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSLDSInsts", "ComputeShader", "The average number of LDS read/write instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,2,ifnotzero", "61b0b351-7e06-ef8e-a8e0-7a9e3200a836" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1674);
        internalCounters.push_back(1639);
        internalCounters.push_back(976);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSALUStalledByLDS", "ComputeShader", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,/,2,/,NUM_SHADER_ENGINES,/,(100),*,3,ifnotzero", "6dc4f1c2-bad0-c9ff-156e-883b319a752a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1697);
        internalCounters.push_back(976);
        internalCounters.push_back(1494);

        p.DefinePublicCounter("CSLDSBankConflict", "ComputeShader", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,/,NUM_SIMDS,/,(100),*,2,ifnotzero", "1065ee10-2e41-ea41-1eb3-b61b491752f4" );
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

        p.DefinePublicCounter("TexUnitBusy", "Timing", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,/,NUM_SHADER_ENGINES,/,(100),*", "36afb8d9-42fc-aafe-66c5-449542153b2c" );
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

        p.DefinePublicCounter("TexTriFilteringPct", "TextureUnit", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,sum8,0,1,2,3,4,5,6,7,sum8,+,/,(100),*", "1affc3c8-b917-5c81-622b-7004527208ae" );
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

        p.DefinePublicCounter("TexVolFilteringPct", "TextureUnit", "Percentage of pixels that received volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,sum8,0,1,2,3,4,5,6,7,sum8,+,/,(100),*", "b5ff6bed-3178-aee4-42dd-c74391c02a2d" );
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

        p.DefinePublicCounter("TexAveAnisotropy", "TextureUnit", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,sum8,(2),8,9,10,11,12,13,14,15,sum8,*,+,(4),16,17,18,19,20,21,22,23,sum8,*,+,(6),24,25,26,27,28,29,30,31,sum8,*,+,(8),32,33,34,35,36,37,38,39,sum8,*,+,(10),40,41,42,43,44,45,46,47,sum8,*,+,(12),48,49,50,51,52,53,54,55,sum8,*,+,(14),56,57,58,59,60,61,62,63,sum8,*,+,(16),64,65,66,67,68,69,70,71,sum8,*,+,0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,sum8,+,16,17,18,19,20,21,22,23,sum8,+,24,25,26,27,28,29,30,31,sum8,+,32,33,34,35,36,37,38,39,sum8,+,40,41,42,43,44,45,46,47,sum8,+,48,49,50,51,52,53,54,55,sum8,+,56,57,58,59,60,61,62,63,sum8,+,64,65,66,67,68,69,70,71,sum8,+,/", "7ca2a2b9-a4eb-ce23-d163-59147e672396" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(621);
        internalCounters.push_back(870);
        internalCounters.push_back(976);

        p.DefinePublicCounter("DepthStencilTestBusy", "Timing", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,/,NUM_SHADER_ENGINES,/,(100),*", "6834fb52-42e8-bb50-fd48-ec2f2904e7e0" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(491);
        internalCounters.push_back(740);
        internalCounters.push_back(480);
        internalCounters.push_back(729);

        p.DefinePublicCounter("HiZTilesAccepted", "DepthAndStencil", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,+,2,3,+,/,(100),*", "56176f45-d7ff-813d-4f05-3b2f046067e7" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(480);
        internalCounters.push_back(729);
        internalCounters.push_back(504);
        internalCounters.push_back(753);

        p.DefinePublicCounter("PreZTilesDetailCulled", "DepthAndStencil", "Percentage of tiles rejected because the associated prim had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "2,3,+,0,1,+,/,(100),*", "cad7f54d-a044-7574-c472-6f2065cbeeac" );
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

        p.DefinePublicCounter("HiZQuadsCulled", "DepthAndStencil", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-,0,1,+,2,+,3,+,/,(100),*", "fa0e319b-5573-6d34-5bab-904769925036" );
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

        p.DefinePublicCounter("PreZQuadsCulled", "DepthAndStencil", "Percentage of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "5,6,+,7,+,8,+,4,-,0,1,+,2,+,3,+,/,(100),*", "4e77547b-ec55-5663-f034-af59be66d77d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1417);
        internalCounters.push_back(1317);
        internalCounters.push_back(1318);
        internalCounters.push_back(1319);
        internalCounters.push_back(1320);

        p.DefinePublicCounter("PostZQuads", "DepthAndStencil", "Percentage of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,+,3,+,4,+,/,(100),*", "58f0d34b-eeb8-e8db-abce-cb72584144be" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(656);
        internalCounters.push_back(905);

        p.DefinePublicCounter("PreZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z before shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+", "3bfe6c4d-7422-ca03-7ea5-e67ff1a00136" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(658);
        internalCounters.push_back(907);

        p.DefinePublicCounter("PreZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z before shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+", "df7f705e-5162-d3b5-da8b-63466cf9c4e5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(657);
        internalCounters.push_back(906);

        p.DefinePublicCounter("PreZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z before shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+", "4484e950-f7a4-3800-bc74-78dd297f017e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(653);
        internalCounters.push_back(902);

        p.DefinePublicCounter("PostZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z after shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+", "4995d5d6-2330-b986-508b-fae24856f44c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(655);
        internalCounters.push_back(904);

        p.DefinePublicCounter("PostZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z after shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+", "ae558af4-f4be-3dd4-7316-b2c4dcf0def8" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(654);
        internalCounters.push_back(903);

        p.DefinePublicCounter("PostZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z after shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+", "b3684c94-814a-c695-c85d-a5b6ab798b35" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(523);
        internalCounters.push_back(772);
        internalCounters.push_back(976);

        p.DefinePublicCounter("ZUnitStalled", "DepthAndStencil", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,/,NUM_SHADER_ENGINES,/,(100),*", "5e86c3ad-1726-3157-1d01-7ed188bf854d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(525);
        internalCounters.push_back(774);
        internalCounters.push_back(532);
        internalCounters.push_back(781);

        p.DefinePublicCounter("DBMemRead", "DepthAndStencil", "Number of bytes read from the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,+,(256),*,2,3,+,(32),*,+", "dcdb4ee7-bd50-00f7-c028-9e5f4ce888c0" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(537);
        internalCounters.push_back(786);
        internalCounters.push_back(540);
        internalCounters.push_back(789);

        p.DefinePublicCounter("DBMemWritten", "DepthAndStencil", "Number of bytes written to the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,+,(32),*,2,3,+,(32),*,+", "de5717f8-8a49-ee44-4645-10de51b37dcf" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(127);
        internalCounters.push_back(342);

        p.DefinePublicCounter("CBMemRead", "ColorBuffer", "Number of bytes read from the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,+,(32),*", "84b531d8-a1f8-7f49-7c27-7bc97801f1e6" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(117);
        internalCounters.push_back(332);

        p.DefinePublicCounter("CBMemWritten", "ColorBuffer", "Number of bytes written to the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,+,(32),*", "550f8ff8-60b6-a6bf-87d0-25ac9e87de70" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(161);
        internalCounters.push_back(376);
        internalCounters.push_back(7);
        internalCounters.push_back(222);

        p.DefinePublicCounter("CBSlowPixelPct", "ColorBuffer", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,+,2,3,+,/,(100),*,(100),min", "5775943f-0313-7e52-9638-b24a449197bc" );
    }
}

