//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions for GL GFX103 
//==============================================================================

#include "gpa_counter.h"
#include "public_counter_definitions_gl_gfx103.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersGL_Gfx103(GPA_DerivedCounters& c)
{
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(25927);

        c.DefineDerivedCounter("GPUTime", "Timing", "Time this API command took to execute on the GPU in nanoseconds from the time the previous command reached the bottom of the pipeline (BOP) to the time this command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "0,TS_FREQ,/,(1000000000),*", "cbd338f2-de6c-7b14-92ad-ba724ca2e501");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1868);
        internalCounters.push_back(1844);

        c.DefineDerivedCounter("GPUBusy", "Timing", "The percentage of time the GPU command processor was busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,(100),*,(100),min", "b1ba5363-1abc-fe66-2fdd-1fe6ee8989a0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("GPUBusyCycles", "Timing", "Number of GPU cycles that the GPU command processor was busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0", "451cb045-23af-ac44-4603-d5832fa041d9");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5254);
        internalCounters.push_back(5266);
        internalCounters.push_back(4947);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("VSBusy", "Timing", "The percentage of time the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero,3,/,(100),*,(100),min", "94caad5e-867c-6c09-cf3a-d05b51df8f3b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5254);
        internalCounters.push_back(5266);
        internalCounters.push_back(4947);

        c.DefineDerivedCounter("VSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero", "a2086d4e-274b-48a8-3e08-a4ab76ac15dd");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(25927);
        internalCounters.push_back(5254);
        internalCounters.push_back(5266);
        internalCounters.push_back(4947);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("VSTime", "Timing", "Time vertex shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "1,2,2,ifnotzero,3,3,ifnotzero,4,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "d6ce819e-69af-a241-d07a-5dd8d146e436");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4980);
        internalCounters.push_back(4987);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("HSBusy", "Timing", "The percentage of time the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "16f30a0b-4cbf-eccd-b13f-ab68dd254d32");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4980);
        internalCounters.push_back(4987);

        c.DefineDerivedCounter("HSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero", "753e76ef-8ef8-3f13-b511-4bd9f3589fdb");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(25927);
        internalCounters.push_back(4980);
        internalCounters.push_back(4987);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("HSTime", "Timing", "Time hull shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "8386a863-dd34-1526-f703-0f0c7b241bc4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4947);
        internalCounters.push_back(5254);
        internalCounters.push_back(5260);
        internalCounters.push_back(5272);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("DSBusy", "Timing", "The percentage of time the ShaderUnit has domain shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,ifnotzero,3,ifnotzero,4,/,(100),*,(100),min", "0c626e8a-9b82-b6d4-d9a3-578509316301");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4947);
        internalCounters.push_back(5254);
        internalCounters.push_back(5260);
        internalCounters.push_back(5272);

        c.DefineDerivedCounter("DSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has domain shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,ifnotzero,3,ifnotzero", "2f3f7561-0549-2232-536d-129ffc5f7703");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(25927);
        internalCounters.push_back(4947);
        internalCounters.push_back(5254);
        internalCounters.push_back(5260);
        internalCounters.push_back(5272);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("DSTime", "Timing", "Time domain shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,2,3,ifnotzero,4,ifnotzero,5,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "bfe28947-c727-8a9f-aa59-c218e58bfba5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5006);
        internalCounters.push_back(5026);
        internalCounters.push_back(5007);
        internalCounters.push_back(5027);
        internalCounters.push_back(5008);
        internalCounters.push_back(5028);
        internalCounters.push_back(5009);
        internalCounters.push_back(5029);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("PSBusy", "Timing", "The percentage of time the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,(0),4,5,ifnotzero,(0),6,7,ifnotzero,max4,8,/,(100),*,(100),min", "7e772beb-d82c-bd9a-aed0-fe504d416ce5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5006);
        internalCounters.push_back(5026);
        internalCounters.push_back(5007);
        internalCounters.push_back(5027);
        internalCounters.push_back(5008);
        internalCounters.push_back(5028);
        internalCounters.push_back(5009);
        internalCounters.push_back(5029);

        c.DefineDerivedCounter("PSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,(0),4,5,ifnotzero,(0),6,7,ifnotzero,max4", "b58bea04-ce8e-2984-80f4-8aba7d4c817b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(25927);
        internalCounters.push_back(5006);
        internalCounters.push_back(5026);
        internalCounters.push_back(5007);
        internalCounters.push_back(5027);
        internalCounters.push_back(5008);
        internalCounters.push_back(5028);
        internalCounters.push_back(5009);
        internalCounters.push_back(5029);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("PSTime", "Timing", "Time pixel shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,2,ifnotzero,(0),3,4,ifnotzero,(0),5,6,ifnotzero,(0),7,8,ifnotzero,max4,9,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "edca7694-7416-e8a6-0c5a-63a5ad5f3d74");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4991);
        internalCounters.push_back(4995);
        internalCounters.push_back(4997);
        internalCounters.push_back(5001);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("CSBusy", "Timing", "The percentage of time the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,max,4,/,(100),*,(100),min", "493fdd90-8d2b-a055-5e4e-2d29c3396b8c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4991);
        internalCounters.push_back(4995);
        internalCounters.push_back(4997);
        internalCounters.push_back(5001);

        c.DefineDerivedCounter("CSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,max", "39bcf1b8-f6b2-4c37-f9af-0a2bb59512f9");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(25927);
        internalCounters.push_back(4991);
        internalCounters.push_back(4995);
        internalCounters.push_back(4997);
        internalCounters.push_back(5001);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("CSTime", "Timing", "Time compute shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,2,ifnotzero,(0),3,4,ifnotzero,max,5,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "dbc24916-ecb2-7eef-8d63-7afadaaab6bc");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5854);
        internalCounters.push_back(5794);
        internalCounters.push_back(7902);
        internalCounters.push_back(7842);
        internalCounters.push_back(6878);
        internalCounters.push_back(6818);

        c.DefineDerivedCounter("VSVALUInstCount", "VertexShader", "Average number of vector ALU instructions executed in the VS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero,2,3,/,3,ifnotzero,4,5,/,5,ifnotzero", "8ec604e4-63f5-e6b5-4558-c38f0b26d4b1");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5850);
        internalCounters.push_back(5794);
        internalCounters.push_back(7898);
        internalCounters.push_back(7842);
        internalCounters.push_back(6874);
        internalCounters.push_back(6818);

        c.DefineDerivedCounter("VSSALUInstCount", "VertexShader", "Average number of scalar ALU instructions executed in the VS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero,2,3,/,3,ifnotzero,4,5,/,5,ifnotzero", "e3da0383-7322-7f65-8cf2-3ce641578e54");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5907);
        internalCounters.push_back(7955);
        internalCounters.push_back(6931);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("VSVALUBusy", "VertexShader", "The percentage of GPUTime vector ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero,NUM_SIMDS,/,3,/,(100),*", "8b3572f7-fda0-eddf-6c93-2ab145b8754b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5907);
        internalCounters.push_back(7955);
        internalCounters.push_back(6931);

        c.DefineDerivedCounter("VSVALUBusyCycles", "VertexShader", "Number of GPU cycles where vector ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero", "0af1686e-6d77-2f6e-2862-7bb8e869a776");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5850);
        internalCounters.push_back(7898);
        internalCounters.push_back(6874);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("VSSALUBusy", "VertexShader", "The percentage of GPUTime scalar ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero,NUM_CUS,/,3,/,(100),*", "3bc8730c-e3bc-e2f0-7d24-36974064c25a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5850);
        internalCounters.push_back(7898);
        internalCounters.push_back(6874);

        c.DefineDerivedCounter("VSSALUBusyCycles", "VertexShader", "Number of GPU cycles where scalar ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero,NUM_CUS,/", "357ac7cd-2e1c-dcb0-77f6-37527237f35b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8414);
        internalCounters.push_back(8354);

        c.DefineDerivedCounter("HSVALUInstCount", "HullShader", "Average number of vector ALU instructions executed in the HS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "786673bf-d58f-9895-3a37-9d6efb5e5804");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8410);
        internalCounters.push_back(8354);

        c.DefineDerivedCounter("HSSALUInstCount", "HullShader", "Average number of scalar ALU instructions executed in the HS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "1af675c4-cb0b-c4c5-c131-2796750f683e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8467);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("HSVALUBusy", "HullShader", "The percentage of GPUTime vector ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_SIMDS,/,1,/,(100),*", "7880d192-8015-0311-d43e-fb0b7a4df179");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8467);

        c.DefineDerivedCounter("HSVALUBusyCycles", "HullShader", "Number of GPU cycles vector where ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_SIMDS,/", "3afb94e4-e937-5730-0cc9-41d3113ba012");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8410);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("HSSALUBusy", "HullShader", "The percentage of GPUTime scalar ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_CUS,/,1,/,(100),*", "34748a4b-9148-0b06-b7b9-5700d6631bde");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8410);

        c.DefineDerivedCounter("HSSALUBusyCycles", "HullShader", "Number of GPU cycles where scalar ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_CUS,/", "9bceabf7-3f01-2fd9-7b1d-8fe46c729efc");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(6878);
        internalCounters.push_back(6818);
        internalCounters.push_back(5854);
        internalCounters.push_back(5794);
        internalCounters.push_back(5798);
        internalCounters.push_back(7846);

        c.DefineDerivedCounter("DSVALUInstCount", "DomainShader", "Average number of vector ALU instructions executed in the DS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,2,3,/,4,ifnotzero,5,ifnotzero", "03a3e949-82f9-be4d-7228-5eb5ad80915a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(6874);
        internalCounters.push_back(6818);
        internalCounters.push_back(5850);
        internalCounters.push_back(5794);
        internalCounters.push_back(5798);
        internalCounters.push_back(7846);

        c.DefineDerivedCounter("DSSALUInstCount", "DomainShader", "Average number of scalar ALU instructions executed in the DS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,2,3,/,4,ifnotzero,5,ifnotzero", "73daa728-483e-95d0-5b40-504719aadc1c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3619);
        internalCounters.push_back(3623);
        internalCounters.push_back(3575);
        internalCounters.push_back(3587);
        internalCounters.push_back(3576);
        internalCounters.push_back(3588);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("PrimitiveAssemblyBusy", "Timing", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max,6,/,(100),*,(100),min", "54ac5640-c4d7-95e2-20e0-6a9fdfc07333");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3619);
        internalCounters.push_back(3623);
        internalCounters.push_back(3575);
        internalCounters.push_back(3587);
        internalCounters.push_back(3576);
        internalCounters.push_back(3588);

        c.DefineDerivedCounter("PrimitiveAssemblyBusyCycles", "Timing", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max", "99777f2d-9626-c78a-a97c-c4505eba1e5f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3522);

        c.DefineDerivedCounter("PrimitivesIn", "PrimitiveAssembly", "The number of primitives received by the hardware. This includes primitives generated by tessellation.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "a515b80d-75c3-c7d2-0d2f-d7766b4759a6");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3528);
        internalCounters.push_back(3568);
        internalCounters.push_back(3569);
        internalCounters.push_back(3570);
        internalCounters.push_back(3571);

        c.DefineDerivedCounter("CulledPrims", "PrimitiveAssembly", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+,4,+", "589bdf55-9192-280a-41c3-584bc94f2562");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3535);

        c.DefineDerivedCounter("ClippedPrims", "PrimitiveAssembly", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "5ef6f9d5-155e-5baa-163f-8359d9ea9bbf");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3623);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("PAStalledOnRasterizer", "PrimitiveAssembly", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*", "6f9f416b-53c1-0457-f88c-7b6ba8973974");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3623);

        c.DefineDerivedCounter("PAStalledOnRasterizerCycles", "PrimitiveAssembly", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_PRIM_PIPES,/", "7a8c492a-c566-9328-6805-760dbff5c0f2");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9386);
        internalCounters.push_back(9391);
        internalCounters.push_back(9396);
        internalCounters.push_back(9401);

        c.DefineDerivedCounter("PSPixelsOut", "PixelShader", "Pixels exported from shader to color buffers. Does not include killed or alpha tested pixels; if there are multiple render targets, each render target receives one export, so this will be 2 for 1 pixel written to two RTs.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "24cba16c-baa6-6ecd-95ad-92ecb1338da1");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9388);
        internalCounters.push_back(9393);
        internalCounters.push_back(9398);
        internalCounters.push_back(9403);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("PSExportStalls", "PixelShader", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,max4,4,/,NUM_SHADER_ENGINES,/,(100),*", "9b4f466c-ff97-22bb-557d-84d3c4c51895");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9388);
        internalCounters.push_back(9393);
        internalCounters.push_back(9398);
        internalCounters.push_back(9403);

        c.DefineDerivedCounter("PSExportStallsCycles", "PixelShader", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "47c72aad-64e6-0864-d533-d8e0bc27c156");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7390);
        internalCounters.push_back(7330);

        c.DefineDerivedCounter("PSVALUInstCount", "PixelShader", "Average number of vector ALU instructions executed in the PS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "eb74389e-435c-4137-ecf1-39eb5bc1cbfe");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7386);
        internalCounters.push_back(7330);

        c.DefineDerivedCounter("PSSALUInstCount", "PixelShader", "Average number of scalar ALU instructions executed in the PS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "e6a06580-8a82-96d6-976c-acc121fc5516");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7443);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("PSVALUBusy", "PixelShader", "The percentage of GPUTime vector ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_SIMDS,/,1,/,(100),*", "6ce6fef7-8e33-10b4-f351-af755e177e85");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7443);

        c.DefineDerivedCounter("PSVALUBusyCycles", "PixelShader", "Number of GPU cycles where vector ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_SIMDS,/", "1e276f86-cd2a-72e7-fc9d-004f666f2981");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7386);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("PSSALUBusy", "PixelShader", "The percentage of GPUTime scalar ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_CUS,/,1,/,(100),*", "2ff9f34f-e94b-af4d-18c2-5fbbf6d1727a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7386);

        c.DefineDerivedCounter("PSSALUBusyCycles", "PixelShader", "Number of GPU cycles where scalar ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_CUS,/", "29808906-f128-b078-fc79-820a4b3b3b8d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4992);
        internalCounters.push_back(4998);

        c.DefineDerivedCounter("CSThreadGroups", "ComputeShader", "Total number of thread groups.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+", "8ce3fc80-56b2-97f9-8e70-2e8c747cea68");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8866);

        c.DefineDerivedCounter("CSWavefronts", "ComputeShader", "The total number of wavefronts used for the CS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "42379c6e-369b-c237-8b25-cdb9cdc65c4d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8870);

        c.DefineDerivedCounter("CSThreads", "ComputeShader", "The number of CS threads processed by the hardware.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "7a648013-6eac-2665-ac36-13c6f4ac9c26");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8926);
        internalCounters.push_back(8866);

        c.DefineDerivedCounter("CSVALUInsts", "ComputeShader", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "376cb1cc-5a40-9d1d-404c-f1736c0c5084");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8944);
        internalCounters.push_back(8979);
        internalCounters.push_back(5283);

        c.DefineDerivedCounter("CSVALUUtilization", "ComputeShader", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,(64),(32),2,ifnotzero,*,/,(100),*,1,ifnotzero,(100),min", "ae943d2a-76e1-bb68-e1e2-0e06c9031611");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8922);
        internalCounters.push_back(8866);

        c.DefineDerivedCounter("CSSALUInsts", "ComputeShader", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "eb211144-8136-ff86-e8bf-4d0493a904cb");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8931);
        internalCounters.push_back(8866);

        c.DefineDerivedCounter("CSVFetchInsts", "ComputeShader", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "3e2829c0-6215-783b-c271-6d57ff2c520e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8923);
        internalCounters.push_back(8866);

        c.DefineDerivedCounter("CSSFetchInsts", "ComputeShader", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "da09171c-6a0a-584f-fddc-dc5062d63a3e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8932);
        internalCounters.push_back(8866);

        c.DefineDerivedCounter("CSVWriteInsts", "ComputeShader", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "43438c22-e910-b377-b767-b32902e0df0d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8979);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("CSVALUBusy", "ComputeShader", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_SIMDS,/,1,/,(100),*", "f1e64815-f6a8-c277-d4f9-d054b443e205");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8979);

        c.DefineDerivedCounter("CSVALUBusyCycles", "ComputeShader", "Number of GPU cycles where vector ALU instructions are processed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_SIMDS,/", "2d0d5852-2658-eb73-68d2-f23f7118c9c3");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8922);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("CSSALUBusy", "ComputeShader", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_CUS,/,1,/,(100),*", "3fc35f4e-9882-94e3-6f5f-4e81cd97082a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8922);

        c.DefineDerivedCounter("CSSALUBusyCycles", "ComputeShader", "Number of GPU cycles where scalar ALU instructions are processed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_CUS,/", "de58f8fc-8ed4-a799-648d-62ded7b1c4c4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9614);
        internalCounters.push_back(9850);
        internalCounters.push_back(10086);
        internalCounters.push_back(10322);
        internalCounters.push_back(10558);
        internalCounters.push_back(10794);
        internalCounters.push_back(11030);
        internalCounters.push_back(11266);
        internalCounters.push_back(11502);
        internalCounters.push_back(11738);
        internalCounters.push_back(11974);
        internalCounters.push_back(12210);
        internalCounters.push_back(12446);
        internalCounters.push_back(12682);
        internalCounters.push_back(12918);
        internalCounters.push_back(13154);
        internalCounters.push_back(1868);
        internalCounters.push_back(4992);
        internalCounters.push_back(4998);

        c.DefineDerivedCounter("CSMemUnitBusy", "ComputeShader", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*,17,18,+,ifnotzero", "42ab96e1-0a24-96c8-c4ff-098fa267d78e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9614);
        internalCounters.push_back(9850);
        internalCounters.push_back(10086);
        internalCounters.push_back(10322);
        internalCounters.push_back(10558);
        internalCounters.push_back(10794);
        internalCounters.push_back(11030);
        internalCounters.push_back(11266);
        internalCounters.push_back(11502);
        internalCounters.push_back(11738);
        internalCounters.push_back(11974);
        internalCounters.push_back(12210);
        internalCounters.push_back(12446);
        internalCounters.push_back(12682);
        internalCounters.push_back(12918);
        internalCounters.push_back(13154);
        internalCounters.push_back(4992);
        internalCounters.push_back(4998);

        c.DefineDerivedCounter("CSMemUnitBusyCycles", "ComputeShader", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ARRAYS,/,16,17,+,ifnotzero", "39d5687f-c727-7c0c-af82-bb711d3897ed");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16483);
        internalCounters.push_back(16560);
        internalCounters.push_back(16637);
        internalCounters.push_back(16714);
        internalCounters.push_back(16791);
        internalCounters.push_back(16868);
        internalCounters.push_back(16945);
        internalCounters.push_back(17022);
        internalCounters.push_back(17099);
        internalCounters.push_back(17176);
        internalCounters.push_back(17253);
        internalCounters.push_back(17330);
        internalCounters.push_back(17407);
        internalCounters.push_back(17484);
        internalCounters.push_back(17561);
        internalCounters.push_back(17638);
        internalCounters.push_back(1868);
        internalCounters.push_back(4992);
        internalCounters.push_back(4998);

        c.DefineDerivedCounter("CSMemUnitStalled", "ComputeShader", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*,17,18,+,ifnotzero", "f18e8679-1511-d533-d9ee-4365197f7d0c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16483);
        internalCounters.push_back(16560);
        internalCounters.push_back(16637);
        internalCounters.push_back(16714);
        internalCounters.push_back(16791);
        internalCounters.push_back(16868);
        internalCounters.push_back(16945);
        internalCounters.push_back(17022);
        internalCounters.push_back(17099);
        internalCounters.push_back(17176);
        internalCounters.push_back(17253);
        internalCounters.push_back(17330);
        internalCounters.push_back(17407);
        internalCounters.push_back(17484);
        internalCounters.push_back(17561);
        internalCounters.push_back(17638);
        internalCounters.push_back(4992);
        internalCounters.push_back(4998);

        c.DefineDerivedCounter("CSMemUnitStalledCycles", "ComputeShader", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ARRAYS,/,16,17,+,ifnotzero", "51991c84-ed2b-bf31-c4ab-8f8e9eb8f29f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18542);
        internalCounters.push_back(18796);
        internalCounters.push_back(19050);
        internalCounters.push_back(19304);
        internalCounters.push_back(19558);
        internalCounters.push_back(19812);
        internalCounters.push_back(20066);
        internalCounters.push_back(20320);
        internalCounters.push_back(20574);
        internalCounters.push_back(20828);
        internalCounters.push_back(21082);
        internalCounters.push_back(21336);
        internalCounters.push_back(21590);
        internalCounters.push_back(21844);
        internalCounters.push_back(22098);
        internalCounters.push_back(22352);
        internalCounters.push_back(1868);
        internalCounters.push_back(4992);
        internalCounters.push_back(4998);

        c.DefineDerivedCounter("CSWriteUnitStalled", "ComputeShader", "The percentage of GPUTime the write unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,18,+,ifnotzero", "55118f7a-8f92-726f-78c6-407f689a2eb4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18542);
        internalCounters.push_back(18796);
        internalCounters.push_back(19050);
        internalCounters.push_back(19304);
        internalCounters.push_back(19558);
        internalCounters.push_back(19812);
        internalCounters.push_back(20066);
        internalCounters.push_back(20320);
        internalCounters.push_back(20574);
        internalCounters.push_back(20828);
        internalCounters.push_back(21082);
        internalCounters.push_back(21336);
        internalCounters.push_back(21590);
        internalCounters.push_back(21844);
        internalCounters.push_back(22098);
        internalCounters.push_back(22352);
        internalCounters.push_back(4992);
        internalCounters.push_back(4998);

        c.DefineDerivedCounter("CSWriteUnitStalledCycles", "ComputeShader", "Number of GPU cycles the write unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,17,+,ifnotzero", "be164c60-5e48-acac-9622-29616d09aa9a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8917);
        internalCounters.push_back(8866);

        c.DefineDerivedCounter("CSGDSInsts", "ComputeShader", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "2a867f3e-4a37-ad16-55d1-f03d74707819");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8921);
        internalCounters.push_back(8866);

        c.DefineDerivedCounter("CSLDSInsts", "ComputeShader", "The average number of LDS read/write instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "61b0b351-7e06-ef8e-a8e0-7a9e3200a836");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8893);
        internalCounters.push_back(8866);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("CSALUStalledByLDS", "ComputeShader", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,/,2,/,NUM_SHADER_ENGINES,/,(100),*,1,ifnotzero", "6dc4f1c2-bad0-c9ff-156e-883b319a752a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8893);

        c.DefineDerivedCounter("CSALUStalledByLDSCycles", "ComputeShader", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_SHADER_ENGINES,/", "8f3d5f25-2159-0374-fafe-e26a7799b6c8");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9147);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("CSLDSBankConflict", "ComputeShader", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*", "1065ee10-2e41-ea41-1eb3-b61b491752f4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9147);

        c.DefineDerivedCounter("CSLDSBankConflictCycles", "ComputeShader", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_SIMDS,/", "1fd1adf3-c51e-94fd-083e-c482a0a0809e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9614);
        internalCounters.push_back(9850);
        internalCounters.push_back(10086);
        internalCounters.push_back(10322);
        internalCounters.push_back(10558);
        internalCounters.push_back(10794);
        internalCounters.push_back(11030);
        internalCounters.push_back(11266);
        internalCounters.push_back(11502);
        internalCounters.push_back(11738);
        internalCounters.push_back(11974);
        internalCounters.push_back(12210);
        internalCounters.push_back(12446);
        internalCounters.push_back(12682);
        internalCounters.push_back(12918);
        internalCounters.push_back(13154);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("TexUnitBusy", "Timing", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "36afb8d9-42fc-aafe-66c5-449542153b2c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9614);
        internalCounters.push_back(9850);
        internalCounters.push_back(10086);
        internalCounters.push_back(10322);
        internalCounters.push_back(10558);
        internalCounters.push_back(10794);
        internalCounters.push_back(11030);
        internalCounters.push_back(11266);
        internalCounters.push_back(11502);
        internalCounters.push_back(11738);
        internalCounters.push_back(11974);
        internalCounters.push_back(12210);
        internalCounters.push_back(12446);
        internalCounters.push_back(12682);
        internalCounters.push_back(12918);
        internalCounters.push_back(13154);

        c.DefineDerivedCounter("TexUnitBusyCycles", "Timing", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ARRAYS,/", "c68761f2-248c-4f39-6528-c308b1c0807c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9688);
        internalCounters.push_back(9924);
        internalCounters.push_back(10160);
        internalCounters.push_back(10396);
        internalCounters.push_back(10632);
        internalCounters.push_back(10868);
        internalCounters.push_back(11104);
        internalCounters.push_back(11340);
        internalCounters.push_back(11576);
        internalCounters.push_back(11812);
        internalCounters.push_back(12048);
        internalCounters.push_back(12284);
        internalCounters.push_back(12520);
        internalCounters.push_back(12756);
        internalCounters.push_back(12992);
        internalCounters.push_back(13228);
        internalCounters.push_back(9689);
        internalCounters.push_back(9925);
        internalCounters.push_back(10161);
        internalCounters.push_back(10397);
        internalCounters.push_back(10633);
        internalCounters.push_back(10869);
        internalCounters.push_back(11105);
        internalCounters.push_back(11341);
        internalCounters.push_back(11577);
        internalCounters.push_back(11813);
        internalCounters.push_back(12049);
        internalCounters.push_back(12285);
        internalCounters.push_back(12521);
        internalCounters.push_back(12757);
        internalCounters.push_back(12993);
        internalCounters.push_back(13229);
        internalCounters.push_back(9690);
        internalCounters.push_back(9926);
        internalCounters.push_back(10162);
        internalCounters.push_back(10398);
        internalCounters.push_back(10634);
        internalCounters.push_back(10870);
        internalCounters.push_back(11106);
        internalCounters.push_back(11342);
        internalCounters.push_back(11578);
        internalCounters.push_back(11814);
        internalCounters.push_back(12050);
        internalCounters.push_back(12286);
        internalCounters.push_back(12522);
        internalCounters.push_back(12758);
        internalCounters.push_back(12994);
        internalCounters.push_back(13230);
        internalCounters.push_back(9691);
        internalCounters.push_back(9927);
        internalCounters.push_back(10163);
        internalCounters.push_back(10399);
        internalCounters.push_back(10635);
        internalCounters.push_back(10871);
        internalCounters.push_back(11107);
        internalCounters.push_back(11343);
        internalCounters.push_back(11579);
        internalCounters.push_back(11815);
        internalCounters.push_back(12051);
        internalCounters.push_back(12287);
        internalCounters.push_back(12523);
        internalCounters.push_back(12759);
        internalCounters.push_back(12995);
        internalCounters.push_back(13231);
        internalCounters.push_back(9692);
        internalCounters.push_back(9928);
        internalCounters.push_back(10164);
        internalCounters.push_back(10400);
        internalCounters.push_back(10636);
        internalCounters.push_back(10872);
        internalCounters.push_back(11108);
        internalCounters.push_back(11344);
        internalCounters.push_back(11580);
        internalCounters.push_back(11816);
        internalCounters.push_back(12052);
        internalCounters.push_back(12288);
        internalCounters.push_back(12524);
        internalCounters.push_back(12760);
        internalCounters.push_back(12996);
        internalCounters.push_back(13232);
        internalCounters.push_back(9693);
        internalCounters.push_back(9929);
        internalCounters.push_back(10165);
        internalCounters.push_back(10401);
        internalCounters.push_back(10637);
        internalCounters.push_back(10873);
        internalCounters.push_back(11109);
        internalCounters.push_back(11345);
        internalCounters.push_back(11581);
        internalCounters.push_back(11817);
        internalCounters.push_back(12053);
        internalCounters.push_back(12289);
        internalCounters.push_back(12525);
        internalCounters.push_back(12761);
        internalCounters.push_back(12997);
        internalCounters.push_back(13233);
        internalCounters.push_back(9694);
        internalCounters.push_back(9930);
        internalCounters.push_back(10166);
        internalCounters.push_back(10402);
        internalCounters.push_back(10638);
        internalCounters.push_back(10874);
        internalCounters.push_back(11110);
        internalCounters.push_back(11346);
        internalCounters.push_back(11582);
        internalCounters.push_back(11818);
        internalCounters.push_back(12054);
        internalCounters.push_back(12290);
        internalCounters.push_back(12526);
        internalCounters.push_back(12762);
        internalCounters.push_back(12998);
        internalCounters.push_back(13234);
        internalCounters.push_back(9695);
        internalCounters.push_back(9931);
        internalCounters.push_back(10167);
        internalCounters.push_back(10403);
        internalCounters.push_back(10639);
        internalCounters.push_back(10875);
        internalCounters.push_back(11111);
        internalCounters.push_back(11347);
        internalCounters.push_back(11583);
        internalCounters.push_back(11819);
        internalCounters.push_back(12055);
        internalCounters.push_back(12291);
        internalCounters.push_back(12527);
        internalCounters.push_back(12763);
        internalCounters.push_back(12999);
        internalCounters.push_back(13235);
        internalCounters.push_back(9696);
        internalCounters.push_back(9932);
        internalCounters.push_back(10168);
        internalCounters.push_back(10404);
        internalCounters.push_back(10640);
        internalCounters.push_back(10876);
        internalCounters.push_back(11112);
        internalCounters.push_back(11348);
        internalCounters.push_back(11584);
        internalCounters.push_back(11820);
        internalCounters.push_back(12056);
        internalCounters.push_back(12292);
        internalCounters.push_back(12528);
        internalCounters.push_back(12764);
        internalCounters.push_back(13000);
        internalCounters.push_back(13236);

        c.DefineDerivedCounter("TexAveAnisotropy", "TextureUnit", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(2),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,*,+,(4),32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,*,+,(6),48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,*,+,(8),64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,*,+,(10),80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,*,+,(12),96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,*,+,(14),112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,*,+,(16),128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,*,+,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,+,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,+,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,+,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,+,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,+,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,+,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,+,/", "7ca2a2b9-a4eb-ce23-d163-59147e672396");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2028);
        internalCounters.push_back(2419);
        internalCounters.push_back(2810);
        internalCounters.push_back(3201);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("DepthStencilTestBusy", "Timing", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "6834fb52-42e8-bb50-fd48-ec2f2904e7e0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2028);
        internalCounters.push_back(2419);
        internalCounters.push_back(2810);
        internalCounters.push_back(3201);

        c.DefineDerivedCounter("DepthStencilTestBusyCount", "Timing", "Number of GPU cycles spent performing depth and stencil tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "e02860fa-c7bd-90ea-2149-69b4e98a636c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1899);
        internalCounters.push_back(2290);
        internalCounters.push_back(2681);
        internalCounters.push_back(3072);
        internalCounters.push_back(1888);
        internalCounters.push_back(2279);
        internalCounters.push_back(2670);
        internalCounters.push_back(3061);

        c.DefineDerivedCounter("HiZTilesAccepted", "DepthAndStencil", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*", "56176f45-d7ff-813d-4f05-3b2f046067e7");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1899);
        internalCounters.push_back(2290);
        internalCounters.push_back(2681);
        internalCounters.push_back(3072);

        c.DefineDerivedCounter("HiZTilesAcceptedCount", "DepthAndStencil", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "95d4e3f6-b2f0-f26e-8423-aacdfaf79ea3");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1888);
        internalCounters.push_back(2279);
        internalCounters.push_back(2670);
        internalCounters.push_back(3061);

        c.DefineDerivedCounter("HiZTilesRejectedCount", "DepthAndStencil", "Count of tiles not accepted by HiZ.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "156ba142-7eeb-aa6e-a00a-f8aea4e41e0b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1888);
        internalCounters.push_back(2279);
        internalCounters.push_back(2670);
        internalCounters.push_back(3061);
        internalCounters.push_back(1912);
        internalCounters.push_back(2303);
        internalCounters.push_back(2694);
        internalCounters.push_back(3085);

        c.DefineDerivedCounter("PreZTilesDetailCulled", "DepthAndStencil", "Percentage of tiles rejected because the associated prim had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "4,5,6,7,sum4,0,1,2,3,sum4,/,(100),*", "cad7f54d-a044-7574-c472-6f2065cbeeac");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1912);
        internalCounters.push_back(2303);
        internalCounters.push_back(2694);
        internalCounters.push_back(3085);

        c.DefineDerivedCounter("PreZTilesDetailCulledCount", "DepthAndStencil", "Count of tiles rejected because the associated primitive had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "49262c8a-b1e6-90dd-f096-0fc4921715e9");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1888);
        internalCounters.push_back(2279);
        internalCounters.push_back(2670);
        internalCounters.push_back(3061);

        c.DefineDerivedCounter("PreZTilesDetailSurvivingCount", "DepthAndStencil", "Count of tiles surviving because the associated primitive had contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "f803eaa4-bbed-bd39-775f-a64df92e2c08");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3949);
        internalCounters.push_back(4527);
        internalCounters.push_back(3950);
        internalCounters.push_back(4528);
        internalCounters.push_back(3951);
        internalCounters.push_back(4529);
        internalCounters.push_back(3952);
        internalCounters.push_back(4530);
        internalCounters.push_back(4025);
        internalCounters.push_back(4603);
        internalCounters.push_back(4026);
        internalCounters.push_back(4604);
        internalCounters.push_back(4027);
        internalCounters.push_back(4605);
        internalCounters.push_back(4028);
        internalCounters.push_back(4606);

        c.DefineDerivedCounter("HiZQuadsCulled", "DepthAndStencil", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,sum8,-,(0),max,0,1,2,3,4,5,6,7,sum8,/,(100),*", "fa0e319b-5573-6d34-5bab-904769925036");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3949);
        internalCounters.push_back(4527);
        internalCounters.push_back(3950);
        internalCounters.push_back(4528);
        internalCounters.push_back(3951);
        internalCounters.push_back(4529);
        internalCounters.push_back(3952);
        internalCounters.push_back(4530);
        internalCounters.push_back(4025);
        internalCounters.push_back(4603);
        internalCounters.push_back(4026);
        internalCounters.push_back(4604);
        internalCounters.push_back(4027);
        internalCounters.push_back(4605);
        internalCounters.push_back(4028);
        internalCounters.push_back(4606);

        c.DefineDerivedCounter("HiZQuadsCulledCount", "DepthAndStencil", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,sum8,-,(0),max", "73b0b39d-6df2-3e24-0b5c-7cb0ac8b6f39");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4025);
        internalCounters.push_back(4603);
        internalCounters.push_back(4026);
        internalCounters.push_back(4604);
        internalCounters.push_back(4027);
        internalCounters.push_back(4605);
        internalCounters.push_back(4028);
        internalCounters.push_back(4606);

        c.DefineDerivedCounter("HiZQuadsAcceptedCount", "DepthAndStencil", "Count of quads that did continue on in the pipeline after HiZ.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,sum8", "59049ad9-42b5-c7cb-3616-6a8f6a8e4894");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3949);
        internalCounters.push_back(4527);
        internalCounters.push_back(3950);
        internalCounters.push_back(4528);
        internalCounters.push_back(3951);
        internalCounters.push_back(4529);
        internalCounters.push_back(3952);
        internalCounters.push_back(4530);
        internalCounters.push_back(4049);
        internalCounters.push_back(4627);
        internalCounters.push_back(4025);
        internalCounters.push_back(4603);
        internalCounters.push_back(4026);
        internalCounters.push_back(4604);
        internalCounters.push_back(4027);
        internalCounters.push_back(4605);
        internalCounters.push_back(4028);
        internalCounters.push_back(4606);

        c.DefineDerivedCounter("PreZQuadsCulled", "DepthAndStencil", "Percentage of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "10,11,12,13,14,15,16,17,sum8,8,9,+,-,(0),max,0,1,2,3,4,5,6,7,sum8,/,(100),*", "4e77547b-ec55-5663-f034-af59be66d77d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3949);
        internalCounters.push_back(4527);
        internalCounters.push_back(3950);
        internalCounters.push_back(4528);
        internalCounters.push_back(3951);
        internalCounters.push_back(4529);
        internalCounters.push_back(3952);
        internalCounters.push_back(4530);
        internalCounters.push_back(4049);
        internalCounters.push_back(4627);
        internalCounters.push_back(4025);
        internalCounters.push_back(4603);
        internalCounters.push_back(4026);
        internalCounters.push_back(4604);
        internalCounters.push_back(4027);
        internalCounters.push_back(4605);
        internalCounters.push_back(4028);
        internalCounters.push_back(4606);

        c.DefineDerivedCounter("PreZQuadsCulledCount", "DepthAndStencil", "Count of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,sum8,8,9,+,-,10,11,12,13,14,15,16,17,sum8,-,(0),max", "1bf169e6-9304-834e-df5f-0c44d7890a08");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4049);
        internalCounters.push_back(4627);
        internalCounters.push_back(4025);
        internalCounters.push_back(4603);
        internalCounters.push_back(4026);
        internalCounters.push_back(4604);
        internalCounters.push_back(4027);
        internalCounters.push_back(4605);
        internalCounters.push_back(4028);
        internalCounters.push_back(4606);

        c.DefineDerivedCounter("PreZQuadsSurvivingCount", "DepthAndStencil", "Count of quads surviving detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "2,3,4,5,6,7,8,9,sum8,0,1,+,-,(0),max", "50e25e51-3713-89cb-7f92-559cde5e5532");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4049);
        internalCounters.push_back(4627);
        internalCounters.push_back(3949);
        internalCounters.push_back(4527);
        internalCounters.push_back(3950);
        internalCounters.push_back(4528);
        internalCounters.push_back(3951);
        internalCounters.push_back(4529);
        internalCounters.push_back(3952);
        internalCounters.push_back(4530);

        c.DefineDerivedCounter("PostZQuads", "DepthAndStencil", "Percentage of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,+,2,3,4,5,6,7,8,9,sum8,/,(100),*,(100),min", "58f0d34b-eeb8-e8db-abce-cb72584144be");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4049);
        internalCounters.push_back(4627);

        c.DefineDerivedCounter("PostZQuadCount", "DepthAndStencil", "Count of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+", "08404526-ce35-939b-34c8-a7a35a0ff4d6");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2061);
        internalCounters.push_back(2452);
        internalCounters.push_back(2843);
        internalCounters.push_back(3234);

        c.DefineDerivedCounter("PreZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z before shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "3bfe6c4d-7422-ca03-7ea5-e67ff1a00136");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2063);
        internalCounters.push_back(2454);
        internalCounters.push_back(2845);
        internalCounters.push_back(3236);

        c.DefineDerivedCounter("PreZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z before shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "df7f705e-5162-d3b5-da8b-63466cf9c4e5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2062);
        internalCounters.push_back(2453);
        internalCounters.push_back(2844);
        internalCounters.push_back(3235);

        c.DefineDerivedCounter("PreZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z before shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "4484e950-f7a4-3800-bc74-78dd297f017e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2058);
        internalCounters.push_back(2449);
        internalCounters.push_back(2840);
        internalCounters.push_back(3231);

        c.DefineDerivedCounter("PostZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z after shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "4995d5d6-2330-b986-508b-fae24856f44c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2060);
        internalCounters.push_back(2451);
        internalCounters.push_back(2842);
        internalCounters.push_back(3233);

        c.DefineDerivedCounter("PostZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z after shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "ae558af4-f4be-3dd4-7316-b2c4dcf0def8");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2059);
        internalCounters.push_back(2450);
        internalCounters.push_back(2841);
        internalCounters.push_back(3232);

        c.DefineDerivedCounter("PostZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z after shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "b3684c94-814a-c695-c85d-a5b6ab798b35");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1930);
        internalCounters.push_back(2321);
        internalCounters.push_back(2712);
        internalCounters.push_back(3103);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("ZUnitStalled", "DepthAndStencil", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "5e86c3ad-1726-3157-1d01-7ed188bf854d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1930);
        internalCounters.push_back(2321);
        internalCounters.push_back(2712);
        internalCounters.push_back(3103);

        c.DefineDerivedCounter("ZUnitStalledCycles", "DepthAndStencil", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "4351fa7f-6737-2c3e-3ffb-b3addbdceedd");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1932);
        internalCounters.push_back(2323);
        internalCounters.push_back(2714);
        internalCounters.push_back(3105);
        internalCounters.push_back(1939);
        internalCounters.push_back(2330);
        internalCounters.push_back(2721);
        internalCounters.push_back(3112);

        c.DefineDerivedCounter("DBMemRead", "DepthAndStencil", "Number of bytes read from the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,sum4,(256),*,4,5,6,7,sum4,(32),*,+", "dcdb4ee7-bd50-00f7-c028-9e5f4ce888c0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1944);
        internalCounters.push_back(2335);
        internalCounters.push_back(2726);
        internalCounters.push_back(3117);
        internalCounters.push_back(1947);
        internalCounters.push_back(2338);
        internalCounters.push_back(2729);
        internalCounters.push_back(3120);

        c.DefineDerivedCounter("DBMemWritten", "DepthAndStencil", "Number of bytes written to the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,sum4,(32),*,4,5,6,7,sum4,(32),*,+", "de5717f8-8a49-ee44-4645-10de51b37dcf");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(128);
        internalCounters.push_back(589);
        internalCounters.push_back(1050);
        internalCounters.push_back(1511);

        c.DefineDerivedCounter("CBMemRead", "ColorBuffer", "Number of bytes read from the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,sum4,(32),*", "84b531d8-a1f8-7f49-7c27-7bc97801f1e6");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(259);
        internalCounters.push_back(720);
        internalCounters.push_back(1181);
        internalCounters.push_back(1642);
        internalCounters.push_back(126);
        internalCounters.push_back(587);
        internalCounters.push_back(1048);
        internalCounters.push_back(1509);
        internalCounters.push_back(127);
        internalCounters.push_back(588);
        internalCounters.push_back(1049);
        internalCounters.push_back(1510);
        internalCounters.push_back(128);
        internalCounters.push_back(589);
        internalCounters.push_back(1050);
        internalCounters.push_back(1511);

        c.DefineDerivedCounter("CBColorAndMaskRead", "ColorBuffer", "Total number of bytes read from the color and mask buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "da41660e-eb6f-32ec-8a64-b32ca17bd7eb");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(118);
        internalCounters.push_back(579);
        internalCounters.push_back(1040);
        internalCounters.push_back(1501);

        c.DefineDerivedCounter("CBMemWritten", "ColorBuffer", "Number of bytes written to the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,sum4,(32),*", "550f8ff8-60b6-a6bf-87d0-25ac9e87de70");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(257);
        internalCounters.push_back(718);
        internalCounters.push_back(1179);
        internalCounters.push_back(1640);
        internalCounters.push_back(116);
        internalCounters.push_back(577);
        internalCounters.push_back(1038);
        internalCounters.push_back(1499);
        internalCounters.push_back(117);
        internalCounters.push_back(578);
        internalCounters.push_back(1039);
        internalCounters.push_back(1500);
        internalCounters.push_back(118);
        internalCounters.push_back(579);
        internalCounters.push_back(1040);
        internalCounters.push_back(1501);

        c.DefineDerivedCounter("CBColorAndMaskWritten", "ColorBuffer", "Total number of bytes written to the color and mask buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "29a04b69-8f5f-b770-a0f2-3453e2c99e49");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(162);
        internalCounters.push_back(623);
        internalCounters.push_back(1084);
        internalCounters.push_back(1545);
        internalCounters.push_back(7);
        internalCounters.push_back(468);
        internalCounters.push_back(929);
        internalCounters.push_back(1390);

        c.DefineDerivedCounter("CBSlowPixelPct", "ColorBuffer", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*,(100),min", "5775943f-0313-7e52-9638-b24a449197bc");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(162);
        internalCounters.push_back(623);
        internalCounters.push_back(1084);
        internalCounters.push_back(1545);

        c.DefineDerivedCounter("CBSlowPixelCount", "ColorBuffer", "Number of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "47eacbb0-28c8-22b4-5c69-c00d5813bb1c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16456);
        internalCounters.push_back(16533);
        internalCounters.push_back(16610);
        internalCounters.push_back(16687);
        internalCounters.push_back(16764);
        internalCounters.push_back(16841);
        internalCounters.push_back(16918);
        internalCounters.push_back(16995);
        internalCounters.push_back(17072);
        internalCounters.push_back(17149);
        internalCounters.push_back(17226);
        internalCounters.push_back(17303);
        internalCounters.push_back(17380);
        internalCounters.push_back(17457);
        internalCounters.push_back(17534);
        internalCounters.push_back(17611);
        internalCounters.push_back(16465);
        internalCounters.push_back(16542);
        internalCounters.push_back(16619);
        internalCounters.push_back(16696);
        internalCounters.push_back(16773);
        internalCounters.push_back(16850);
        internalCounters.push_back(16927);
        internalCounters.push_back(17004);
        internalCounters.push_back(17081);
        internalCounters.push_back(17158);
        internalCounters.push_back(17235);
        internalCounters.push_back(17312);
        internalCounters.push_back(17389);
        internalCounters.push_back(17466);
        internalCounters.push_back(17543);
        internalCounters.push_back(17620);

        c.DefineDerivedCounter("L0CacheHit", "MemoryCache", "The percentage of read requests that hit the data in the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "286c786e-9a42-3371-9dea-dd54e6e612e9");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16456);
        internalCounters.push_back(16533);
        internalCounters.push_back(16610);
        internalCounters.push_back(16687);
        internalCounters.push_back(16764);
        internalCounters.push_back(16841);
        internalCounters.push_back(16918);
        internalCounters.push_back(16995);
        internalCounters.push_back(17072);
        internalCounters.push_back(17149);
        internalCounters.push_back(17226);
        internalCounters.push_back(17303);
        internalCounters.push_back(17380);
        internalCounters.push_back(17457);
        internalCounters.push_back(17534);
        internalCounters.push_back(17611);

        c.DefineDerivedCounter("L0CacheRequestCount", "MemoryCache", "The number of read requests made to the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "74983cae-ee57-2e1b-d990-5128fef84e1f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16456);
        internalCounters.push_back(16533);
        internalCounters.push_back(16610);
        internalCounters.push_back(16687);
        internalCounters.push_back(16764);
        internalCounters.push_back(16841);
        internalCounters.push_back(16918);
        internalCounters.push_back(16995);
        internalCounters.push_back(17072);
        internalCounters.push_back(17149);
        internalCounters.push_back(17226);
        internalCounters.push_back(17303);
        internalCounters.push_back(17380);
        internalCounters.push_back(17457);
        internalCounters.push_back(17534);
        internalCounters.push_back(17611);
        internalCounters.push_back(16465);
        internalCounters.push_back(16542);
        internalCounters.push_back(16619);
        internalCounters.push_back(16696);
        internalCounters.push_back(16773);
        internalCounters.push_back(16850);
        internalCounters.push_back(16927);
        internalCounters.push_back(17004);
        internalCounters.push_back(17081);
        internalCounters.push_back(17158);
        internalCounters.push_back(17235);
        internalCounters.push_back(17312);
        internalCounters.push_back(17389);
        internalCounters.push_back(17466);
        internalCounters.push_back(17543);
        internalCounters.push_back(17620);

        c.DefineDerivedCounter("L0CacheHitCount", "MemoryCache", "The number of read requests which result in a cache hit from the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-", "c0de7338-069b-c5ba-ead3-c65e030cd2ac");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16465);
        internalCounters.push_back(16542);
        internalCounters.push_back(16619);
        internalCounters.push_back(16696);
        internalCounters.push_back(16773);
        internalCounters.push_back(16850);
        internalCounters.push_back(16927);
        internalCounters.push_back(17004);
        internalCounters.push_back(17081);
        internalCounters.push_back(17158);
        internalCounters.push_back(17235);
        internalCounters.push_back(17312);
        internalCounters.push_back(17389);
        internalCounters.push_back(17466);
        internalCounters.push_back(17543);
        internalCounters.push_back(17620);

        c.DefineDerivedCounter("L0CacheMissCount", "MemoryCache", "The number of read requests which result in a cache miss from the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "a2f08766-ea1b-6eae-6eaf-faa04125d3e6");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18021);
        internalCounters.push_back(18025);

        c.DefineDerivedCounter("L1CacheHit", "MemoryCache", "The percentage of read or write requests that hit the data in the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),1,0,/,-,(100),*,0,ifnotzero", "5a34915a-24b8-8baf-2bf8-5878e7894ae3");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18021);

        c.DefineDerivedCounter("L1CacheRequestCount", "MemoryCache", "The number of read or write requests made to the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "29c76c67-4611-205d-0b88-d08668df03c5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18021);
        internalCounters.push_back(18025);

        c.DefineDerivedCounter("L1CacheHitCount", "MemoryCache", "The number of read or write requests which result in a cache hit from the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,-", "1ae150c3-f2d0-82c6-a51b-a77fd8d5fc33");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18025);

        c.DefineDerivedCounter("L1CacheMissCount", "MemoryCache", "The number of read or write requests which result in a cache miss from the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "71bfec6d-257b-849d-e212-cdf5c1b1de65");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18457);
        internalCounters.push_back(18711);
        internalCounters.push_back(18965);
        internalCounters.push_back(19219);
        internalCounters.push_back(19473);
        internalCounters.push_back(19727);
        internalCounters.push_back(19981);
        internalCounters.push_back(20235);
        internalCounters.push_back(20489);
        internalCounters.push_back(20743);
        internalCounters.push_back(20997);
        internalCounters.push_back(21251);
        internalCounters.push_back(21505);
        internalCounters.push_back(21759);
        internalCounters.push_back(22013);
        internalCounters.push_back(22267);
        internalCounters.push_back(18497);
        internalCounters.push_back(18751);
        internalCounters.push_back(19005);
        internalCounters.push_back(19259);
        internalCounters.push_back(19513);
        internalCounters.push_back(19767);
        internalCounters.push_back(20021);
        internalCounters.push_back(20275);
        internalCounters.push_back(20529);
        internalCounters.push_back(20783);
        internalCounters.push_back(21037);
        internalCounters.push_back(21291);
        internalCounters.push_back(21545);
        internalCounters.push_back(21799);
        internalCounters.push_back(22053);
        internalCounters.push_back(22307);

        c.DefineDerivedCounter("L2CacheHit", "MemoryCache", "The percentage of read or write requests that hit the data in the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "47694e4d-6ce6-f387-080d-b1f3d00b73ac");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18497);
        internalCounters.push_back(18751);
        internalCounters.push_back(19005);
        internalCounters.push_back(19259);
        internalCounters.push_back(19513);
        internalCounters.push_back(19767);
        internalCounters.push_back(20021);
        internalCounters.push_back(20275);
        internalCounters.push_back(20529);
        internalCounters.push_back(20783);
        internalCounters.push_back(21037);
        internalCounters.push_back(21291);
        internalCounters.push_back(21545);
        internalCounters.push_back(21799);
        internalCounters.push_back(22053);
        internalCounters.push_back(22307);
        internalCounters.push_back(18457);
        internalCounters.push_back(18711);
        internalCounters.push_back(18965);
        internalCounters.push_back(19219);
        internalCounters.push_back(19473);
        internalCounters.push_back(19727);
        internalCounters.push_back(19981);
        internalCounters.push_back(20235);
        internalCounters.push_back(20489);
        internalCounters.push_back(20743);
        internalCounters.push_back(20997);
        internalCounters.push_back(21251);
        internalCounters.push_back(21505);
        internalCounters.push_back(21759);
        internalCounters.push_back(22013);
        internalCounters.push_back(22267);

        c.DefineDerivedCounter("L2CacheMiss", "MemoryCache", "The percentage of read or write requests that miss the data in the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size. Value range: 0% (optimal) to 100% (all miss).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*", "8aee5458-a58e-11b6-5131-7f19ed070117");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18457);
        internalCounters.push_back(18711);
        internalCounters.push_back(18965);
        internalCounters.push_back(19219);
        internalCounters.push_back(19473);
        internalCounters.push_back(19727);
        internalCounters.push_back(19981);
        internalCounters.push_back(20235);
        internalCounters.push_back(20489);
        internalCounters.push_back(20743);
        internalCounters.push_back(20997);
        internalCounters.push_back(21251);
        internalCounters.push_back(21505);
        internalCounters.push_back(21759);
        internalCounters.push_back(22013);
        internalCounters.push_back(22267);

        c.DefineDerivedCounter("L2CacheRequestCount", "MemoryCache", "The number of read or write requests made to the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "21e9219c-e725-0d96-06b1-b21698b736b2");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18457);
        internalCounters.push_back(18711);
        internalCounters.push_back(18965);
        internalCounters.push_back(19219);
        internalCounters.push_back(19473);
        internalCounters.push_back(19727);
        internalCounters.push_back(19981);
        internalCounters.push_back(20235);
        internalCounters.push_back(20489);
        internalCounters.push_back(20743);
        internalCounters.push_back(20997);
        internalCounters.push_back(21251);
        internalCounters.push_back(21505);
        internalCounters.push_back(21759);
        internalCounters.push_back(22013);
        internalCounters.push_back(22267);
        internalCounters.push_back(18497);
        internalCounters.push_back(18751);
        internalCounters.push_back(19005);
        internalCounters.push_back(19259);
        internalCounters.push_back(19513);
        internalCounters.push_back(19767);
        internalCounters.push_back(20021);
        internalCounters.push_back(20275);
        internalCounters.push_back(20529);
        internalCounters.push_back(20783);
        internalCounters.push_back(21037);
        internalCounters.push_back(21291);
        internalCounters.push_back(21545);
        internalCounters.push_back(21799);
        internalCounters.push_back(22053);
        internalCounters.push_back(22307);

        c.DefineDerivedCounter("L2CacheHitCount", "MemoryCache", "The number of read or write requests which result in a cache hit from the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-", "29ddcb92-d3dd-951b-1b23-efe52e4eeee4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18497);
        internalCounters.push_back(18751);
        internalCounters.push_back(19005);
        internalCounters.push_back(19259);
        internalCounters.push_back(19513);
        internalCounters.push_back(19767);
        internalCounters.push_back(20021);
        internalCounters.push_back(20275);
        internalCounters.push_back(20529);
        internalCounters.push_back(20783);
        internalCounters.push_back(21037);
        internalCounters.push_back(21291);
        internalCounters.push_back(21545);
        internalCounters.push_back(21799);
        internalCounters.push_back(22053);
        internalCounters.push_back(22307);

        c.DefineDerivedCounter("L2CacheMissCount", "MemoryCache", "The number of read or write requests which result in a cache miss from the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "376eec7b-ab25-9012-06b5-63291a17fd47");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18553);
        internalCounters.push_back(18807);
        internalCounters.push_back(19061);
        internalCounters.push_back(19315);
        internalCounters.push_back(19569);
        internalCounters.push_back(19823);
        internalCounters.push_back(20077);
        internalCounters.push_back(20331);
        internalCounters.push_back(20585);
        internalCounters.push_back(20839);
        internalCounters.push_back(21093);
        internalCounters.push_back(21347);
        internalCounters.push_back(21601);
        internalCounters.push_back(21855);
        internalCounters.push_back(22109);
        internalCounters.push_back(22363);
        internalCounters.push_back(18554);
        internalCounters.push_back(18808);
        internalCounters.push_back(19062);
        internalCounters.push_back(19316);
        internalCounters.push_back(19570);
        internalCounters.push_back(19824);
        internalCounters.push_back(20078);
        internalCounters.push_back(20332);
        internalCounters.push_back(20586);
        internalCounters.push_back(20840);
        internalCounters.push_back(21094);
        internalCounters.push_back(21348);
        internalCounters.push_back(21602);
        internalCounters.push_back(21856);
        internalCounters.push_back(22110);
        internalCounters.push_back(22364);
        internalCounters.push_back(18555);
        internalCounters.push_back(18809);
        internalCounters.push_back(19063);
        internalCounters.push_back(19317);
        internalCounters.push_back(19571);
        internalCounters.push_back(19825);
        internalCounters.push_back(20079);
        internalCounters.push_back(20333);
        internalCounters.push_back(20587);
        internalCounters.push_back(20841);
        internalCounters.push_back(21095);
        internalCounters.push_back(21349);
        internalCounters.push_back(21603);
        internalCounters.push_back(21857);
        internalCounters.push_back(22111);
        internalCounters.push_back(22365);
        internalCounters.push_back(18556);
        internalCounters.push_back(18810);
        internalCounters.push_back(19064);
        internalCounters.push_back(19318);
        internalCounters.push_back(19572);
        internalCounters.push_back(19826);
        internalCounters.push_back(20080);
        internalCounters.push_back(20334);
        internalCounters.push_back(20588);
        internalCounters.push_back(20842);
        internalCounters.push_back(21096);
        internalCounters.push_back(21350);
        internalCounters.push_back(21604);
        internalCounters.push_back(21858);
        internalCounters.push_back(22112);
        internalCounters.push_back(22366);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total bytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,(96),*,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,(128),*,sum4", "664bb3ef-6eca-86b1-1e2d-30cb897b5fa9");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18537);
        internalCounters.push_back(18791);
        internalCounters.push_back(19045);
        internalCounters.push_back(19299);
        internalCounters.push_back(19553);
        internalCounters.push_back(19807);
        internalCounters.push_back(20061);
        internalCounters.push_back(20315);
        internalCounters.push_back(20569);
        internalCounters.push_back(20823);
        internalCounters.push_back(21077);
        internalCounters.push_back(21331);
        internalCounters.push_back(21585);
        internalCounters.push_back(21839);
        internalCounters.push_back(22093);
        internalCounters.push_back(22347);
        internalCounters.push_back(18539);
        internalCounters.push_back(18793);
        internalCounters.push_back(19047);
        internalCounters.push_back(19301);
        internalCounters.push_back(19555);
        internalCounters.push_back(19809);
        internalCounters.push_back(20063);
        internalCounters.push_back(20317);
        internalCounters.push_back(20571);
        internalCounters.push_back(20825);
        internalCounters.push_back(21079);
        internalCounters.push_back(21333);
        internalCounters.push_back(21587);
        internalCounters.push_back(21841);
        internalCounters.push_back(22095);
        internalCounters.push_back(22349);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total bytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+", "f96f2c16-b1b4-4ec4-229c-fc82e6f80a82");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9614);
        internalCounters.push_back(9850);
        internalCounters.push_back(10086);
        internalCounters.push_back(10322);
        internalCounters.push_back(10558);
        internalCounters.push_back(10794);
        internalCounters.push_back(11030);
        internalCounters.push_back(11266);
        internalCounters.push_back(11502);
        internalCounters.push_back(11738);
        internalCounters.push_back(11974);
        internalCounters.push_back(12210);
        internalCounters.push_back(12446);
        internalCounters.push_back(12682);
        internalCounters.push_back(12918);
        internalCounters.push_back(13154);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9614);
        internalCounters.push_back(9850);
        internalCounters.push_back(10086);
        internalCounters.push_back(10322);
        internalCounters.push_back(10558);
        internalCounters.push_back(10794);
        internalCounters.push_back(11030);
        internalCounters.push_back(11266);
        internalCounters.push_back(11502);
        internalCounters.push_back(11738);
        internalCounters.push_back(11974);
        internalCounters.push_back(12210);
        internalCounters.push_back(12446);
        internalCounters.push_back(12682);
        internalCounters.push_back(12918);
        internalCounters.push_back(13154);

        c.DefineDerivedCounter("MemUnitBusyCycles", "GlobalMemory", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalledCycles). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "168f077c-4797-b2f5-717f-105c725266c8");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16483);
        internalCounters.push_back(16560);
        internalCounters.push_back(16637);
        internalCounters.push_back(16714);
        internalCounters.push_back(16791);
        internalCounters.push_back(16868);
        internalCounters.push_back(16945);
        internalCounters.push_back(17022);
        internalCounters.push_back(17099);
        internalCounters.push_back(17176);
        internalCounters.push_back(17253);
        internalCounters.push_back(17330);
        internalCounters.push_back(17407);
        internalCounters.push_back(17484);
        internalCounters.push_back(17561);
        internalCounters.push_back(17638);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16483);
        internalCounters.push_back(16560);
        internalCounters.push_back(16637);
        internalCounters.push_back(16714);
        internalCounters.push_back(16791);
        internalCounters.push_back(16868);
        internalCounters.push_back(16945);
        internalCounters.push_back(17022);
        internalCounters.push_back(17099);
        internalCounters.push_back(17176);

        c.DefineDerivedCounter("MemUnitStalledCycles", "GlobalMemory", "Number of GPU cycles the memory unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,max10", "2745659a-0e40-bace-3b9b-86a54f8e4623");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18542);
        internalCounters.push_back(18796);
        internalCounters.push_back(19050);
        internalCounters.push_back(19304);
        internalCounters.push_back(19558);
        internalCounters.push_back(19812);
        internalCounters.push_back(20066);
        internalCounters.push_back(20320);
        internalCounters.push_back(20574);
        internalCounters.push_back(20828);
        internalCounters.push_back(21082);
        internalCounters.push_back(21336);
        internalCounters.push_back(21590);
        internalCounters.push_back(21844);
        internalCounters.push_back(22098);
        internalCounters.push_back(22352);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18542);
        internalCounters.push_back(18796);
        internalCounters.push_back(19050);
        internalCounters.push_back(19304);
        internalCounters.push_back(19558);
        internalCounters.push_back(19812);
        internalCounters.push_back(20066);
        internalCounters.push_back(20320);
        internalCounters.push_back(20574);
        internalCounters.push_back(20828);
        internalCounters.push_back(21082);
        internalCounters.push_back(21336);
        internalCounters.push_back(21590);
        internalCounters.push_back(21844);
        internalCounters.push_back(22098);
        internalCounters.push_back(22352);

        c.DefineDerivedCounter("WriteUnitStalledCycles", "GlobalMemory", "Number of GPU cycles the Write unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "ede3305e-abd4-d6bf-6b00-ffc57a29fce3");
    }
}

