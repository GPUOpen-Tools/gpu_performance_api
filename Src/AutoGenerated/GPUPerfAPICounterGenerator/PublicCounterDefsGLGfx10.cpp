//==============================================================================
// Copyright (c) 2010-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for GLGFX10
//==============================================================================

#include "GPACounter.h"
#include "PublicCounterDefsGLGfx10.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersGLGfx10(GPA_DerivedCounters& c)
{
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(23040);

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
        internalCounters.push_back(5108);
        internalCounters.push_back(5120);
        internalCounters.push_back(4801);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("VSBusy", "Timing", "The percentage of time the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero,3,/,(100),*,(100),min", "94caad5e-867c-6c09-cf3a-d05b51df8f3b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5108);
        internalCounters.push_back(5120);
        internalCounters.push_back(4801);

        c.DefineDerivedCounter("VSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero", "a2086d4e-274b-48a8-3e08-a4ab76ac15dd");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(23040);
        internalCounters.push_back(5108);
        internalCounters.push_back(5120);
        internalCounters.push_back(4801);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("VSTime", "Timing", "Time vertex shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "1,2,2,ifnotzero,3,3,ifnotzero,4,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "d6ce819e-69af-a241-d07a-5dd8d146e436");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4834);
        internalCounters.push_back(4841);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("HSBusy", "Timing", "The percentage of time the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,2,/,(100),*,(100),min", "16f30a0b-4cbf-eccd-b13f-ab68dd254d32");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4834);
        internalCounters.push_back(4841);

        c.DefineDerivedCounter("HSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero", "753e76ef-8ef8-3f13-b511-4bd9f3589fdb");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(23040);
        internalCounters.push_back(4834);
        internalCounters.push_back(4841);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("HSTime", "Timing", "Time hull shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,2,ifnotzero,3,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "8386a863-dd34-1526-f703-0f0c7b241bc4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4801);
        internalCounters.push_back(5108);
        internalCounters.push_back(5114);
        internalCounters.push_back(5126);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("DSBusy", "Timing", "The percentage of time the ShaderUnit has domain shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,ifnotzero,3,ifnotzero,4,/,(100),*,(100),min", "0c626e8a-9b82-b6d4-d9a3-578509316301");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4801);
        internalCounters.push_back(5108);
        internalCounters.push_back(5114);
        internalCounters.push_back(5126);

        c.DefineDerivedCounter("DSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has domain shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,ifnotzero,3,ifnotzero", "2f3f7561-0549-2232-536d-129ffc5f7703");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(23040);
        internalCounters.push_back(4801);
        internalCounters.push_back(5108);
        internalCounters.push_back(5114);
        internalCounters.push_back(5126);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("DSTime", "Timing", "Time domain shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,2,3,ifnotzero,4,ifnotzero,5,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "bfe28947-c727-8a9f-aa59-c218e58bfba5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4860);
        internalCounters.push_back(4880);
        internalCounters.push_back(4861);
        internalCounters.push_back(4881);
        internalCounters.push_back(4862);
        internalCounters.push_back(4882);
        internalCounters.push_back(4863);
        internalCounters.push_back(4883);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("PSBusy", "Timing", "The percentage of time the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,(0),4,5,ifnotzero,(0),6,7,ifnotzero,max4,8,/,(100),*,(100),min", "7e772beb-d82c-bd9a-aed0-fe504d416ce5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4860);
        internalCounters.push_back(4880);
        internalCounters.push_back(4861);
        internalCounters.push_back(4881);
        internalCounters.push_back(4862);
        internalCounters.push_back(4882);
        internalCounters.push_back(4863);
        internalCounters.push_back(4883);

        c.DefineDerivedCounter("PSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,(0),4,5,ifnotzero,(0),6,7,ifnotzero,max4", "b58bea04-ce8e-2984-80f4-8aba7d4c817b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(23040);
        internalCounters.push_back(4860);
        internalCounters.push_back(4880);
        internalCounters.push_back(4861);
        internalCounters.push_back(4881);
        internalCounters.push_back(4862);
        internalCounters.push_back(4882);
        internalCounters.push_back(4863);
        internalCounters.push_back(4883);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("PSTime", "Timing", "Time pixel shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,2,ifnotzero,(0),3,4,ifnotzero,(0),5,6,ifnotzero,(0),7,8,ifnotzero,max4,9,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "edca7694-7416-e8a6-0c5a-63a5ad5f3d74");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4845);
        internalCounters.push_back(4849);
        internalCounters.push_back(4851);
        internalCounters.push_back(4855);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("CSBusy", "Timing", "The percentage of time the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,max,4,/,(100),*,(100),min", "493fdd90-8d2b-a055-5e4e-2d29c3396b8c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4845);
        internalCounters.push_back(4849);
        internalCounters.push_back(4851);
        internalCounters.push_back(4855);

        c.DefineDerivedCounter("CSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,ifnotzero,(0),2,3,ifnotzero,max", "39bcf1b8-f6b2-4c37-f9af-0a2bb59512f9");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(23040);
        internalCounters.push_back(4845);
        internalCounters.push_back(4849);
        internalCounters.push_back(4851);
        internalCounters.push_back(4855);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("CSTime", "Timing", "Time compute shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,2,ifnotzero,(0),3,4,ifnotzero,max,5,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "dbc24916-ecb2-7eef-8d63-7afadaaab6bc");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15737);
        internalCounters.push_back(15759);
        internalCounters.push_back(15801);

        c.DefineDerivedCounter("VSVerticesIn", "VertexShader", "The number of vertices processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero", "810a04c8-2ff4-081d-766d-bfa2bd4ad916");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5705);
        internalCounters.push_back(5645);
        internalCounters.push_back(7753);
        internalCounters.push_back(7693);
        internalCounters.push_back(6729);
        internalCounters.push_back(6669);

        c.DefineDerivedCounter("VSVALUInstCount", "VertexShader", "Average number of vector ALU instructions executed in the VS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero,2,3,/,3,ifnotzero,4,5,/,5,ifnotzero", "8ec604e4-63f5-e6b5-4558-c38f0b26d4b1");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5701);
        internalCounters.push_back(5645);
        internalCounters.push_back(7749);
        internalCounters.push_back(7693);
        internalCounters.push_back(6725);
        internalCounters.push_back(6669);

        c.DefineDerivedCounter("VSSALUInstCount", "VertexShader", "Average number of scalar ALU instructions executed in the VS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero,2,3,/,3,ifnotzero,4,5,/,5,ifnotzero", "e3da0383-7322-7f65-8cf2-3ce641578e54");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5758);
        internalCounters.push_back(7806);
        internalCounters.push_back(6782);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("VSVALUBusy", "VertexShader", "The percentage of GPUTime vector ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero,NUM_SIMDS,/,3,/,(100),*", "8b3572f7-fda0-eddf-6c93-2ab145b8754b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5758);
        internalCounters.push_back(7806);
        internalCounters.push_back(6782);

        c.DefineDerivedCounter("VSVALUBusyCycles", "VertexShader", "Number of GPU cycles where vector ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero", "0af1686e-6d77-2f6e-2862-7bb8e869a776");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5701);
        internalCounters.push_back(7749);
        internalCounters.push_back(6725);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("VSSALUBusy", "VertexShader", "The percentage of GPUTime scalar ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero,NUM_CUS,/,3,/,(100),*", "3bc8730c-e3bc-e2f0-7d24-36974064c25a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5701);
        internalCounters.push_back(7749);
        internalCounters.push_back(6725);

        c.DefineDerivedCounter("VSSALUBusyCycles", "VertexShader", "Number of GPU cycles where scalar ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero,NUM_CUS,/", "357ac7cd-2e1c-dcb0-77f6-37527237f35b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15753);

        c.DefineDerivedCounter("HSPatches", "HullShader", "The number of patches processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "d1bbd27d-d591-4509-df52-d329fb73a98f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8265);
        internalCounters.push_back(8205);

        c.DefineDerivedCounter("HSVALUInstCount", "HullShader", "Average number of vector ALU instructions executed in the HS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "786673bf-d58f-9895-3a37-9d6efb5e5804");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8261);
        internalCounters.push_back(8205);

        c.DefineDerivedCounter("HSSALUInstCount", "HullShader", "Average number of scalar ALU instructions executed in the HS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "1af675c4-cb0b-c4c5-c131-2796750f683e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8318);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("HSVALUBusy", "HullShader", "The percentage of GPUTime vector ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_SIMDS,/,1,/,(100),*", "7880d192-8015-0311-d43e-fb0b7a4df179");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8318);

        c.DefineDerivedCounter("HSVALUBusyCycles", "HullShader", "Number of GPU cycles vector where ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_SIMDS,/", "3afb94e4-e937-5730-0cc9-41d3113ba012");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8261);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("HSSALUBusy", "HullShader", "The percentage of GPUTime scalar ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_CUS,/,1,/,(100),*", "34748a4b-9148-0b06-b7b9-5700d6631bde");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8261);

        c.DefineDerivedCounter("HSSALUBusyCycles", "HullShader", "Number of GPU cycles where scalar ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_CUS,/", "9bceabf7-3f01-2fd9-7b1d-8fe46c729efc");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15801);
        internalCounters.push_back(15737);
        internalCounters.push_back(15759);

        c.DefineDerivedCounter("DSVerticesIn", "DomainShader", "The number of vertices processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,1,ifnotzero,2,ifnotzero", "b88d9d05-2418-e639-4e3d-3a5815855f8d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(6729);
        internalCounters.push_back(6669);
        internalCounters.push_back(5705);
        internalCounters.push_back(5645);
        internalCounters.push_back(5649);
        internalCounters.push_back(7697);

        c.DefineDerivedCounter("DSVALUInstCount", "DomainShader", "Average number of vector ALU instructions executed in the DS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,2,3,/,4,ifnotzero,5,ifnotzero", "03a3e949-82f9-be4d-7228-5eb5ad80915a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(6725);
        internalCounters.push_back(6669);
        internalCounters.push_back(5701);
        internalCounters.push_back(5645);
        internalCounters.push_back(5649);
        internalCounters.push_back(7697);

        c.DefineDerivedCounter("DSSALUInstCount", "DomainShader", "Average number of scalar ALU instructions executed in the DS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,2,3,/,4,ifnotzero,5,ifnotzero", "73daa728-483e-95d0-5b40-504719aadc1c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3535);
        internalCounters.push_back(3539);
        internalCounters.push_back(3491);
        internalCounters.push_back(3503);
        internalCounters.push_back(3492);
        internalCounters.push_back(3504);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("PrimitiveAssemblyBusy", "Timing", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max,6,/,(100),*,(100),min", "54ac5640-c4d7-95e2-20e0-6a9fdfc07333");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3535);
        internalCounters.push_back(3539);
        internalCounters.push_back(3491);
        internalCounters.push_back(3503);
        internalCounters.push_back(3492);
        internalCounters.push_back(3504);

        c.DefineDerivedCounter("PrimitiveAssemblyBusyCycles", "Timing", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max", "99777f2d-9626-c78a-a97c-c4505eba1e5f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3438);

        c.DefineDerivedCounter("PrimitivesIn", "PrimitiveAssembly", "The number of primitives received by the hardware. This includes primitives generated by tessellation.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "a515b80d-75c3-c7d2-0d2f-d7766b4759a6");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3444);
        internalCounters.push_back(3484);
        internalCounters.push_back(3485);
        internalCounters.push_back(3486);
        internalCounters.push_back(3487);

        c.DefineDerivedCounter("CulledPrims", "PrimitiveAssembly", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+,4,+", "589bdf55-9192-280a-41c3-584bc94f2562");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3451);

        c.DefineDerivedCounter("ClippedPrims", "PrimitiveAssembly", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "5ef6f9d5-155e-5baa-163f-8359d9ea9bbf");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3539);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("PAStalledOnRasterizer", "PrimitiveAssembly", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*", "6f9f416b-53c1-0457-f88c-7b6ba8973974");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3539);

        c.DefineDerivedCounter("PAStalledOnRasterizerCycles", "PrimitiveAssembly", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_PRIM_PIPES,/", "7a8c492a-c566-9328-6805-760dbff5c0f2");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9237);
        internalCounters.push_back(9242);
        internalCounters.push_back(9247);
        internalCounters.push_back(9252);

        c.DefineDerivedCounter("PSPixelsOut", "PixelShader", "Pixels exported from shader to color buffers. Does not include killed or alpha tested pixels; if there are multiple render targets, each render target receives one export, so this will be 2 for 1 pixel written to two RTs.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "24cba16c-baa6-6ecd-95ad-92ecb1338da1");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9239);
        internalCounters.push_back(9244);
        internalCounters.push_back(9249);
        internalCounters.push_back(9254);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("PSExportStalls", "PixelShader", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,max4,4,/,NUM_SHADER_ENGINES,/,(100),*", "9b4f466c-ff97-22bb-557d-84d3c4c51895");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9239);
        internalCounters.push_back(9244);
        internalCounters.push_back(9249);
        internalCounters.push_back(9254);

        c.DefineDerivedCounter("PSExportStallsCycles", "PixelShader", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "47c72aad-64e6-0864-d533-d8e0bc27c156");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7241);
        internalCounters.push_back(7181);

        c.DefineDerivedCounter("PSVALUInstCount", "PixelShader", "Average number of vector ALU instructions executed in the PS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "eb74389e-435c-4137-ecf1-39eb5bc1cbfe");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7237);
        internalCounters.push_back(7181);

        c.DefineDerivedCounter("PSSALUInstCount", "PixelShader", "Average number of scalar ALU instructions executed in the PS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,/", "e6a06580-8a82-96d6-976c-acc121fc5516");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7294);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("PSVALUBusy", "PixelShader", "The percentage of GPUTime vector ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_SIMDS,/,1,/,(100),*", "6ce6fef7-8e33-10b4-f351-af755e177e85");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7294);

        c.DefineDerivedCounter("PSVALUBusyCycles", "PixelShader", "Number of GPU cycles where vector ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_SIMDS,/", "1e276f86-cd2a-72e7-fc9d-004f666f2981");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7237);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("PSSALUBusy", "PixelShader", "The percentage of GPUTime scalar ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_CUS,/,1,/,(100),*", "2ff9f34f-e94b-af4d-18c2-5fbbf6d1727a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7237);

        c.DefineDerivedCounter("PSSALUBusyCycles", "PixelShader", "Number of GPU cycles where scalar ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_CUS,/", "29808906-f128-b078-fc79-820a4b3b3b8d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(4846);
        internalCounters.push_back(4852);

        c.DefineDerivedCounter("CSThreadGroups", "ComputeShader", "Total number of thread groups.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+", "8ce3fc80-56b2-97f9-8e70-2e8c747cea68");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8717);

        c.DefineDerivedCounter("CSWavefronts", "ComputeShader", "The total number of wavefronts used for the CS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "42379c6e-369b-c237-8b25-cdb9cdc65c4d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8721);

        c.DefineDerivedCounter("CSThreads", "ComputeShader", "The number of CS threads processed by the hardware.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "7a648013-6eac-2665-ac36-13c6f4ac9c26");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8777);
        internalCounters.push_back(8717);

        c.DefineDerivedCounter("CSVALUInsts", "ComputeShader", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "376cb1cc-5a40-9d1d-404c-f1736c0c5084");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8795);
        internalCounters.push_back(8830);
        internalCounters.push_back(5134);

        c.DefineDerivedCounter("CSVALUUtilization", "ComputeShader", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,(64),(32),2,ifnotzero,*,/,(100),*,1,ifnotzero,(100),min", "ae943d2a-76e1-bb68-e1e2-0e06c9031611");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8773);
        internalCounters.push_back(8717);

        c.DefineDerivedCounter("CSSALUInsts", "ComputeShader", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "eb211144-8136-ff86-e8bf-4d0493a904cb");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8782);
        internalCounters.push_back(8717);

        c.DefineDerivedCounter("CSVFetchInsts", "ComputeShader", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "3e2829c0-6215-783b-c271-6d57ff2c520e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8774);
        internalCounters.push_back(8717);

        c.DefineDerivedCounter("CSSFetchInsts", "ComputeShader", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "da09171c-6a0a-584f-fddc-dc5062d63a3e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8783);
        internalCounters.push_back(8717);

        c.DefineDerivedCounter("CSVWriteInsts", "ComputeShader", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "43438c22-e910-b377-b767-b32902e0df0d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8830);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("CSVALUBusy", "ComputeShader", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_SIMDS,/,1,/,(100),*", "f1e64815-f6a8-c277-d4f9-d054b443e205");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8830);

        c.DefineDerivedCounter("CSVALUBusyCycles", "ComputeShader", "Number of GPU cycles where vector ALU instructions are processed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_SIMDS,/", "2d0d5852-2658-eb73-68d2-f23f7118c9c3");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8773);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("CSSALUBusy", "ComputeShader", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,NUM_CUS,/,1,/,(100),*", "3fc35f4e-9882-94e3-6f5f-4e81cd97082a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8773);

        c.DefineDerivedCounter("CSSALUBusyCycles", "ComputeShader", "Number of GPU cycles where scalar ALU instructions are processed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_CUS,/", "de58f8fc-8ed4-a799-648d-62ded7b1c4c4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9465);
        internalCounters.push_back(9691);
        internalCounters.push_back(9917);
        internalCounters.push_back(10143);
        internalCounters.push_back(10369);
        internalCounters.push_back(10595);
        internalCounters.push_back(10821);
        internalCounters.push_back(11047);
        internalCounters.push_back(11273);
        internalCounters.push_back(11499);
        internalCounters.push_back(11725);
        internalCounters.push_back(11951);
        internalCounters.push_back(12177);
        internalCounters.push_back(12403);
        internalCounters.push_back(12629);
        internalCounters.push_back(12855);
        internalCounters.push_back(1868);
        internalCounters.push_back(4846);
        internalCounters.push_back(4852);

        c.DefineDerivedCounter("CSMemUnitBusy", "ComputeShader", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*,17,18,+,ifnotzero", "42ab96e1-0a24-96c8-c4ff-098fa267d78e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9465);
        internalCounters.push_back(9691);
        internalCounters.push_back(9917);
        internalCounters.push_back(10143);
        internalCounters.push_back(10369);
        internalCounters.push_back(10595);
        internalCounters.push_back(10821);
        internalCounters.push_back(11047);
        internalCounters.push_back(11273);
        internalCounters.push_back(11499);
        internalCounters.push_back(11725);
        internalCounters.push_back(11951);
        internalCounters.push_back(12177);
        internalCounters.push_back(12403);
        internalCounters.push_back(12629);
        internalCounters.push_back(12855);
        internalCounters.push_back(4846);
        internalCounters.push_back(4852);

        c.DefineDerivedCounter("CSMemUnitBusyCycles", "ComputeShader", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ARRAYS,/,16,17,+,ifnotzero", "39d5687f-c727-7c0c-af82-bb711d3897ed");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14078);
        internalCounters.push_back(14155);
        internalCounters.push_back(14232);
        internalCounters.push_back(14309);
        internalCounters.push_back(14386);
        internalCounters.push_back(14463);
        internalCounters.push_back(14540);
        internalCounters.push_back(14617);
        internalCounters.push_back(14694);
        internalCounters.push_back(14771);
        internalCounters.push_back(14848);
        internalCounters.push_back(14925);
        internalCounters.push_back(15002);
        internalCounters.push_back(15079);
        internalCounters.push_back(15156);
        internalCounters.push_back(15233);
        internalCounters.push_back(1868);
        internalCounters.push_back(4846);
        internalCounters.push_back(4852);

        c.DefineDerivedCounter("CSMemUnitStalled", "ComputeShader", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*,17,18,+,ifnotzero", "f18e8679-1511-d533-d9ee-4365197f7d0c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14078);
        internalCounters.push_back(14155);
        internalCounters.push_back(14232);
        internalCounters.push_back(14309);
        internalCounters.push_back(14386);
        internalCounters.push_back(14463);
        internalCounters.push_back(14540);
        internalCounters.push_back(14617);
        internalCounters.push_back(14694);
        internalCounters.push_back(14771);
        internalCounters.push_back(14848);
        internalCounters.push_back(14925);
        internalCounters.push_back(15002);
        internalCounters.push_back(15079);
        internalCounters.push_back(15156);
        internalCounters.push_back(15233);
        internalCounters.push_back(4846);
        internalCounters.push_back(4852);

        c.DefineDerivedCounter("CSMemUnitStalledCycles", "ComputeShader", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ARRAYS,/,16,17,+,ifnotzero", "51991c84-ed2b-bf31-c4ab-8f8e9eb8f29f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16384);
        internalCounters.push_back(16619);
        internalCounters.push_back(16854);
        internalCounters.push_back(17089);
        internalCounters.push_back(17324);
        internalCounters.push_back(17559);
        internalCounters.push_back(17794);
        internalCounters.push_back(18029);
        internalCounters.push_back(18264);
        internalCounters.push_back(18499);
        internalCounters.push_back(18734);
        internalCounters.push_back(18969);
        internalCounters.push_back(19204);
        internalCounters.push_back(19439);
        internalCounters.push_back(19674);
        internalCounters.push_back(19909);
        internalCounters.push_back(20144);
        internalCounters.push_back(20379);
        internalCounters.push_back(20614);
        internalCounters.push_back(20849);
        internalCounters.push_back(21084);
        internalCounters.push_back(21319);
        internalCounters.push_back(21554);
        internalCounters.push_back(21789);
        internalCounters.push_back(1868);
        internalCounters.push_back(4846);
        internalCounters.push_back(4852);

        c.DefineDerivedCounter("CSWriteUnitStalled", "ComputeShader", "The percentage of GPUTime the write unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,max24,24,/,(100),*,25,26,+,ifnotzero", "55118f7a-8f92-726f-78c6-407f689a2eb4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16384);
        internalCounters.push_back(16619);
        internalCounters.push_back(16854);
        internalCounters.push_back(17089);
        internalCounters.push_back(17324);
        internalCounters.push_back(17559);
        internalCounters.push_back(17794);
        internalCounters.push_back(18029);
        internalCounters.push_back(18264);
        internalCounters.push_back(18499);
        internalCounters.push_back(18734);
        internalCounters.push_back(18969);
        internalCounters.push_back(19204);
        internalCounters.push_back(19439);
        internalCounters.push_back(19674);
        internalCounters.push_back(19909);
        internalCounters.push_back(20144);
        internalCounters.push_back(20379);
        internalCounters.push_back(20614);
        internalCounters.push_back(20849);
        internalCounters.push_back(21084);
        internalCounters.push_back(21319);
        internalCounters.push_back(21554);
        internalCounters.push_back(21789);
        internalCounters.push_back(4846);
        internalCounters.push_back(4852);

        c.DefineDerivedCounter("CSWriteUnitStalledCycles", "ComputeShader", "Number of GPU cycles the write unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,max24,24,25,+,ifnotzero", "be164c60-5e48-acac-9622-29616d09aa9a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8768);
        internalCounters.push_back(8717);

        c.DefineDerivedCounter("CSGDSInsts", "ComputeShader", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "2a867f3e-4a37-ad16-55d1-f03d74707819");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8772);
        internalCounters.push_back(8717);

        c.DefineDerivedCounter("CSLDSInsts", "ComputeShader", "The average number of LDS read/write instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,/,1,ifnotzero", "61b0b351-7e06-ef8e-a8e0-7a9e3200a836");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8744);
        internalCounters.push_back(8717);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("CSALUStalledByLDS", "ComputeShader", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,/,2,/,NUM_SHADER_ENGINES,/,(100),*,1,ifnotzero", "6dc4f1c2-bad0-c9ff-156e-883b319a752a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8744);

        c.DefineDerivedCounter("CSALUStalledByLDSCycles", "ComputeShader", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_SHADER_ENGINES,/", "8f3d5f25-2159-0374-fafe-e26a7799b6c8");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8998);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("CSLDSBankConflict", "ComputeShader", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,NUM_SIMDS,/,(100),*", "1065ee10-2e41-ea41-1eb3-b61b491752f4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(8998);

        c.DefineDerivedCounter("CSLDSBankConflictCycles", "ComputeShader", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,NUM_SIMDS,/", "1fd1adf3-c51e-94fd-083e-c482a0a0809e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9465);
        internalCounters.push_back(9691);
        internalCounters.push_back(9917);
        internalCounters.push_back(10143);
        internalCounters.push_back(10369);
        internalCounters.push_back(10595);
        internalCounters.push_back(10821);
        internalCounters.push_back(11047);
        internalCounters.push_back(11273);
        internalCounters.push_back(11499);
        internalCounters.push_back(11725);
        internalCounters.push_back(11951);
        internalCounters.push_back(12177);
        internalCounters.push_back(12403);
        internalCounters.push_back(12629);
        internalCounters.push_back(12855);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("TexUnitBusy", "Timing", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "36afb8d9-42fc-aafe-66c5-449542153b2c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9465);
        internalCounters.push_back(9691);
        internalCounters.push_back(9917);
        internalCounters.push_back(10143);
        internalCounters.push_back(10369);
        internalCounters.push_back(10595);
        internalCounters.push_back(10821);
        internalCounters.push_back(11047);
        internalCounters.push_back(11273);
        internalCounters.push_back(11499);
        internalCounters.push_back(11725);
        internalCounters.push_back(11951);
        internalCounters.push_back(12177);
        internalCounters.push_back(12403);
        internalCounters.push_back(12629);
        internalCounters.push_back(12855);

        c.DefineDerivedCounter("TexUnitBusyCycles", "Timing", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,NUM_SHADER_ARRAYS,/", "c68761f2-248c-4f39-6528-c308b1c0807c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9519);
        internalCounters.push_back(9745);
        internalCounters.push_back(9971);
        internalCounters.push_back(10197);
        internalCounters.push_back(10423);
        internalCounters.push_back(10649);
        internalCounters.push_back(10875);
        internalCounters.push_back(11101);
        internalCounters.push_back(11327);
        internalCounters.push_back(11553);
        internalCounters.push_back(11779);
        internalCounters.push_back(12005);
        internalCounters.push_back(12231);
        internalCounters.push_back(12457);
        internalCounters.push_back(12683);
        internalCounters.push_back(12909);
        internalCounters.push_back(9518);
        internalCounters.push_back(9744);
        internalCounters.push_back(9970);
        internalCounters.push_back(10196);
        internalCounters.push_back(10422);
        internalCounters.push_back(10648);
        internalCounters.push_back(10874);
        internalCounters.push_back(11100);
        internalCounters.push_back(11326);
        internalCounters.push_back(11552);
        internalCounters.push_back(11778);
        internalCounters.push_back(12004);
        internalCounters.push_back(12230);
        internalCounters.push_back(12456);
        internalCounters.push_back(12682);
        internalCounters.push_back(12908);

        c.DefineDerivedCounter("TexTriFilteringPct", "TextureUnit", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,+,/,(100),*", "1affc3c8-b917-5c81-622b-7004527208ae");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9519);
        internalCounters.push_back(9745);
        internalCounters.push_back(9971);
        internalCounters.push_back(10197);
        internalCounters.push_back(10423);
        internalCounters.push_back(10649);
        internalCounters.push_back(10875);
        internalCounters.push_back(11101);
        internalCounters.push_back(11327);
        internalCounters.push_back(11553);
        internalCounters.push_back(11779);
        internalCounters.push_back(12005);
        internalCounters.push_back(12231);
        internalCounters.push_back(12457);
        internalCounters.push_back(12683);
        internalCounters.push_back(12909);

        c.DefineDerivedCounter("TexTriFilteringCount", "TextureUnit", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "5785b3a1-a513-18db-4b1c-bdeef75bb2b6");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9518);
        internalCounters.push_back(9744);
        internalCounters.push_back(9970);
        internalCounters.push_back(10196);
        internalCounters.push_back(10422);
        internalCounters.push_back(10648);
        internalCounters.push_back(10874);
        internalCounters.push_back(11100);
        internalCounters.push_back(11326);
        internalCounters.push_back(11552);
        internalCounters.push_back(11778);
        internalCounters.push_back(12004);
        internalCounters.push_back(12230);
        internalCounters.push_back(12456);
        internalCounters.push_back(12682);
        internalCounters.push_back(12908);

        c.DefineDerivedCounter("NoTexTriFilteringCount", "TextureUnit", "Count of pixels that did not receive trilinear filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "179da29a-81af-c06e-ce8c-a0a731ea030d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9521);
        internalCounters.push_back(9747);
        internalCounters.push_back(9973);
        internalCounters.push_back(10199);
        internalCounters.push_back(10425);
        internalCounters.push_back(10651);
        internalCounters.push_back(10877);
        internalCounters.push_back(11103);
        internalCounters.push_back(11329);
        internalCounters.push_back(11555);
        internalCounters.push_back(11781);
        internalCounters.push_back(12007);
        internalCounters.push_back(12233);
        internalCounters.push_back(12459);
        internalCounters.push_back(12685);
        internalCounters.push_back(12911);
        internalCounters.push_back(9520);
        internalCounters.push_back(9746);
        internalCounters.push_back(9972);
        internalCounters.push_back(10198);
        internalCounters.push_back(10424);
        internalCounters.push_back(10650);
        internalCounters.push_back(10876);
        internalCounters.push_back(11102);
        internalCounters.push_back(11328);
        internalCounters.push_back(11554);
        internalCounters.push_back(11780);
        internalCounters.push_back(12006);
        internalCounters.push_back(12232);
        internalCounters.push_back(12458);
        internalCounters.push_back(12684);
        internalCounters.push_back(12910);

        c.DefineDerivedCounter("TexVolFilteringPct", "TextureUnit", "Percentage of pixels that received volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,+,/,(100),*", "b5ff6bed-3178-aee4-42dd-c74391c02a2d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9521);
        internalCounters.push_back(9747);
        internalCounters.push_back(9973);
        internalCounters.push_back(10199);
        internalCounters.push_back(10425);
        internalCounters.push_back(10651);
        internalCounters.push_back(10877);
        internalCounters.push_back(11103);
        internalCounters.push_back(11329);
        internalCounters.push_back(11555);
        internalCounters.push_back(11781);
        internalCounters.push_back(12007);
        internalCounters.push_back(12233);
        internalCounters.push_back(12459);
        internalCounters.push_back(12685);
        internalCounters.push_back(12911);

        c.DefineDerivedCounter("TexVolFilteringCount", "TextureUnit", "Count of pixels that received volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "4bddc587-d589-8128-e18c-762eab2c871f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9520);
        internalCounters.push_back(9746);
        internalCounters.push_back(9972);
        internalCounters.push_back(10198);
        internalCounters.push_back(10424);
        internalCounters.push_back(10650);
        internalCounters.push_back(10876);
        internalCounters.push_back(11102);
        internalCounters.push_back(11328);
        internalCounters.push_back(11554);
        internalCounters.push_back(11780);
        internalCounters.push_back(12006);
        internalCounters.push_back(12232);
        internalCounters.push_back(12458);
        internalCounters.push_back(12684);
        internalCounters.push_back(12910);

        c.DefineDerivedCounter("NoTexVolFilteringCount", "TextureUnit", "Count of pixels that did not receive volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "9fe1a854-17c6-9d26-b2b9-80610cd5827d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9539);
        internalCounters.push_back(9765);
        internalCounters.push_back(9991);
        internalCounters.push_back(10217);
        internalCounters.push_back(10443);
        internalCounters.push_back(10669);
        internalCounters.push_back(10895);
        internalCounters.push_back(11121);
        internalCounters.push_back(11347);
        internalCounters.push_back(11573);
        internalCounters.push_back(11799);
        internalCounters.push_back(12025);
        internalCounters.push_back(12251);
        internalCounters.push_back(12477);
        internalCounters.push_back(12703);
        internalCounters.push_back(12929);
        internalCounters.push_back(9540);
        internalCounters.push_back(9766);
        internalCounters.push_back(9992);
        internalCounters.push_back(10218);
        internalCounters.push_back(10444);
        internalCounters.push_back(10670);
        internalCounters.push_back(10896);
        internalCounters.push_back(11122);
        internalCounters.push_back(11348);
        internalCounters.push_back(11574);
        internalCounters.push_back(11800);
        internalCounters.push_back(12026);
        internalCounters.push_back(12252);
        internalCounters.push_back(12478);
        internalCounters.push_back(12704);
        internalCounters.push_back(12930);
        internalCounters.push_back(9541);
        internalCounters.push_back(9767);
        internalCounters.push_back(9993);
        internalCounters.push_back(10219);
        internalCounters.push_back(10445);
        internalCounters.push_back(10671);
        internalCounters.push_back(10897);
        internalCounters.push_back(11123);
        internalCounters.push_back(11349);
        internalCounters.push_back(11575);
        internalCounters.push_back(11801);
        internalCounters.push_back(12027);
        internalCounters.push_back(12253);
        internalCounters.push_back(12479);
        internalCounters.push_back(12705);
        internalCounters.push_back(12931);
        internalCounters.push_back(9542);
        internalCounters.push_back(9768);
        internalCounters.push_back(9994);
        internalCounters.push_back(10220);
        internalCounters.push_back(10446);
        internalCounters.push_back(10672);
        internalCounters.push_back(10898);
        internalCounters.push_back(11124);
        internalCounters.push_back(11350);
        internalCounters.push_back(11576);
        internalCounters.push_back(11802);
        internalCounters.push_back(12028);
        internalCounters.push_back(12254);
        internalCounters.push_back(12480);
        internalCounters.push_back(12706);
        internalCounters.push_back(12932);
        internalCounters.push_back(9543);
        internalCounters.push_back(9769);
        internalCounters.push_back(9995);
        internalCounters.push_back(10221);
        internalCounters.push_back(10447);
        internalCounters.push_back(10673);
        internalCounters.push_back(10899);
        internalCounters.push_back(11125);
        internalCounters.push_back(11351);
        internalCounters.push_back(11577);
        internalCounters.push_back(11803);
        internalCounters.push_back(12029);
        internalCounters.push_back(12255);
        internalCounters.push_back(12481);
        internalCounters.push_back(12707);
        internalCounters.push_back(12933);
        internalCounters.push_back(9544);
        internalCounters.push_back(9770);
        internalCounters.push_back(9996);
        internalCounters.push_back(10222);
        internalCounters.push_back(10448);
        internalCounters.push_back(10674);
        internalCounters.push_back(10900);
        internalCounters.push_back(11126);
        internalCounters.push_back(11352);
        internalCounters.push_back(11578);
        internalCounters.push_back(11804);
        internalCounters.push_back(12030);
        internalCounters.push_back(12256);
        internalCounters.push_back(12482);
        internalCounters.push_back(12708);
        internalCounters.push_back(12934);
        internalCounters.push_back(9545);
        internalCounters.push_back(9771);
        internalCounters.push_back(9997);
        internalCounters.push_back(10223);
        internalCounters.push_back(10449);
        internalCounters.push_back(10675);
        internalCounters.push_back(10901);
        internalCounters.push_back(11127);
        internalCounters.push_back(11353);
        internalCounters.push_back(11579);
        internalCounters.push_back(11805);
        internalCounters.push_back(12031);
        internalCounters.push_back(12257);
        internalCounters.push_back(12483);
        internalCounters.push_back(12709);
        internalCounters.push_back(12935);
        internalCounters.push_back(9546);
        internalCounters.push_back(9772);
        internalCounters.push_back(9998);
        internalCounters.push_back(10224);
        internalCounters.push_back(10450);
        internalCounters.push_back(10676);
        internalCounters.push_back(10902);
        internalCounters.push_back(11128);
        internalCounters.push_back(11354);
        internalCounters.push_back(11580);
        internalCounters.push_back(11806);
        internalCounters.push_back(12032);
        internalCounters.push_back(12258);
        internalCounters.push_back(12484);
        internalCounters.push_back(12710);
        internalCounters.push_back(12936);
        internalCounters.push_back(9547);
        internalCounters.push_back(9773);
        internalCounters.push_back(9999);
        internalCounters.push_back(10225);
        internalCounters.push_back(10451);
        internalCounters.push_back(10677);
        internalCounters.push_back(10903);
        internalCounters.push_back(11129);
        internalCounters.push_back(11355);
        internalCounters.push_back(11581);
        internalCounters.push_back(11807);
        internalCounters.push_back(12033);
        internalCounters.push_back(12259);
        internalCounters.push_back(12485);
        internalCounters.push_back(12711);
        internalCounters.push_back(12937);

        c.DefineDerivedCounter("TexAveAnisotropy", "TextureUnit", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(2),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,*,+,(4),32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,*,+,(6),48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,*,+,(8),64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,*,+,(10),80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,*,+,(12),96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,*,+,(14),112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,*,+,(16),128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,*,+,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,+,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,+,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum16,+,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum16,+,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,sum16,+,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum16,+,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,sum16,+,/", "7ca2a2b9-a4eb-ce23-d163-59147e672396");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2028);
        internalCounters.push_back(2398);
        internalCounters.push_back(2768);
        internalCounters.push_back(3138);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("DepthStencilTestBusy", "Timing", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "6834fb52-42e8-bb50-fd48-ec2f2904e7e0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2028);
        internalCounters.push_back(2398);
        internalCounters.push_back(2768);
        internalCounters.push_back(3138);

        c.DefineDerivedCounter("DepthStencilTestBusyCount", "Timing", "Number of GPU cycles spent performing depth and stencil tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "e02860fa-c7bd-90ea-2149-69b4e98a636c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1899);
        internalCounters.push_back(2269);
        internalCounters.push_back(2639);
        internalCounters.push_back(3009);
        internalCounters.push_back(1888);
        internalCounters.push_back(2258);
        internalCounters.push_back(2628);
        internalCounters.push_back(2998);

        c.DefineDerivedCounter("HiZTilesAccepted", "DepthAndStencil", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,(100),*", "56176f45-d7ff-813d-4f05-3b2f046067e7");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1899);
        internalCounters.push_back(2269);
        internalCounters.push_back(2639);
        internalCounters.push_back(3009);

        c.DefineDerivedCounter("HiZTilesAcceptedCount", "DepthAndStencil", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "95d4e3f6-b2f0-f26e-8423-aacdfaf79ea3");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1888);
        internalCounters.push_back(2258);
        internalCounters.push_back(2628);
        internalCounters.push_back(2998);

        c.DefineDerivedCounter("HiZTilesRejectedCount", "DepthAndStencil", "Count of tiles not accepted by HiZ.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "156ba142-7eeb-aa6e-a00a-f8aea4e41e0b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1888);
        internalCounters.push_back(2258);
        internalCounters.push_back(2628);
        internalCounters.push_back(2998);
        internalCounters.push_back(1912);
        internalCounters.push_back(2282);
        internalCounters.push_back(2652);
        internalCounters.push_back(3022);

        c.DefineDerivedCounter("PreZTilesDetailCulled", "DepthAndStencil", "Percentage of tiles rejected because the associated prim had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "4,5,6,7,sum4,0,1,2,3,sum4,/,(100),*", "cad7f54d-a044-7574-c472-6f2065cbeeac");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1912);
        internalCounters.push_back(2282);
        internalCounters.push_back(2652);
        internalCounters.push_back(3022);

        c.DefineDerivedCounter("PreZTilesDetailCulledCount", "DepthAndStencil", "Count of tiles rejected because the associated primitive had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "49262c8a-b1e6-90dd-f096-0fc4921715e9");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1888);
        internalCounters.push_back(2258);
        internalCounters.push_back(2628);
        internalCounters.push_back(2998);

        c.DefineDerivedCounter("PreZTilesDetailSurvivingCount", "DepthAndStencil", "Count of tiles surviving because the associated primitive had contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "f803eaa4-bbed-bd39-775f-a64df92e2c08");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3855);
        internalCounters.push_back(4407);
        internalCounters.push_back(3856);
        internalCounters.push_back(4408);
        internalCounters.push_back(3857);
        internalCounters.push_back(4409);
        internalCounters.push_back(3858);
        internalCounters.push_back(4410);
        internalCounters.push_back(3931);
        internalCounters.push_back(4483);
        internalCounters.push_back(3932);
        internalCounters.push_back(4484);
        internalCounters.push_back(3933);
        internalCounters.push_back(4485);
        internalCounters.push_back(3934);
        internalCounters.push_back(4486);

        c.DefineDerivedCounter("HiZQuadsCulled", "DepthAndStencil", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,sum8,-,(0),max,0,1,2,3,4,5,6,7,sum8,/,(100),*", "fa0e319b-5573-6d34-5bab-904769925036");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3855);
        internalCounters.push_back(4407);
        internalCounters.push_back(3856);
        internalCounters.push_back(4408);
        internalCounters.push_back(3857);
        internalCounters.push_back(4409);
        internalCounters.push_back(3858);
        internalCounters.push_back(4410);
        internalCounters.push_back(3931);
        internalCounters.push_back(4483);
        internalCounters.push_back(3932);
        internalCounters.push_back(4484);
        internalCounters.push_back(3933);
        internalCounters.push_back(4485);
        internalCounters.push_back(3934);
        internalCounters.push_back(4486);

        c.DefineDerivedCounter("HiZQuadsCulledCount", "DepthAndStencil", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,sum8,-,(0),max", "73b0b39d-6df2-3e24-0b5c-7cb0ac8b6f39");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3931);
        internalCounters.push_back(4483);
        internalCounters.push_back(3932);
        internalCounters.push_back(4484);
        internalCounters.push_back(3933);
        internalCounters.push_back(4485);
        internalCounters.push_back(3934);
        internalCounters.push_back(4486);

        c.DefineDerivedCounter("HiZQuadsAcceptedCount", "DepthAndStencil", "Count of quads that did continue on in the pipeline after HiZ.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,sum8", "59049ad9-42b5-c7cb-3616-6a8f6a8e4894");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3855);
        internalCounters.push_back(4407);
        internalCounters.push_back(3856);
        internalCounters.push_back(4408);
        internalCounters.push_back(3857);
        internalCounters.push_back(4409);
        internalCounters.push_back(3858);
        internalCounters.push_back(4410);
        internalCounters.push_back(3955);
        internalCounters.push_back(4507);
        internalCounters.push_back(3931);
        internalCounters.push_back(4483);
        internalCounters.push_back(3932);
        internalCounters.push_back(4484);
        internalCounters.push_back(3933);
        internalCounters.push_back(4485);
        internalCounters.push_back(3934);
        internalCounters.push_back(4486);

        c.DefineDerivedCounter("PreZQuadsCulled", "DepthAndStencil", "Percentage of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "10,11,12,13,14,15,16,17,sum8,8,9,+,-,(0),max,0,1,2,3,4,5,6,7,sum8,/,(100),*", "4e77547b-ec55-5663-f034-af59be66d77d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3855);
        internalCounters.push_back(4407);
        internalCounters.push_back(3856);
        internalCounters.push_back(4408);
        internalCounters.push_back(3857);
        internalCounters.push_back(4409);
        internalCounters.push_back(3858);
        internalCounters.push_back(4410);
        internalCounters.push_back(3955);
        internalCounters.push_back(4507);
        internalCounters.push_back(3931);
        internalCounters.push_back(4483);
        internalCounters.push_back(3932);
        internalCounters.push_back(4484);
        internalCounters.push_back(3933);
        internalCounters.push_back(4485);
        internalCounters.push_back(3934);
        internalCounters.push_back(4486);

        c.DefineDerivedCounter("PreZQuadsCulledCount", "DepthAndStencil", "Count of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,sum8,8,9,+,-,10,11,12,13,14,15,16,17,sum8,-,(0),max", "1bf169e6-9304-834e-df5f-0c44d7890a08");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3955);
        internalCounters.push_back(4507);
        internalCounters.push_back(3931);
        internalCounters.push_back(4483);
        internalCounters.push_back(3932);
        internalCounters.push_back(4484);
        internalCounters.push_back(3933);
        internalCounters.push_back(4485);
        internalCounters.push_back(3934);
        internalCounters.push_back(4486);

        c.DefineDerivedCounter("PreZQuadsSurvivingCount", "DepthAndStencil", "Count of quads surviving detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "2,3,4,5,6,7,8,9,sum8,0,1,+,-,(0),max", "50e25e51-3713-89cb-7f92-559cde5e5532");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3955);
        internalCounters.push_back(4507);
        internalCounters.push_back(3855);
        internalCounters.push_back(4407);
        internalCounters.push_back(3856);
        internalCounters.push_back(4408);
        internalCounters.push_back(3857);
        internalCounters.push_back(4409);
        internalCounters.push_back(3858);
        internalCounters.push_back(4410);

        c.DefineDerivedCounter("PostZQuads", "DepthAndStencil", "Percentage of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,+,2,3,4,5,6,7,8,9,sum8,/,(100),*,(100),min", "58f0d34b-eeb8-e8db-abce-cb72584144be");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3955);
        internalCounters.push_back(4507);

        c.DefineDerivedCounter("PostZQuadCount", "DepthAndStencil", "Count of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+", "08404526-ce35-939b-34c8-a7a35a0ff4d6");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2061);
        internalCounters.push_back(2431);
        internalCounters.push_back(2801);
        internalCounters.push_back(3171);

        c.DefineDerivedCounter("PreZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z before shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "3bfe6c4d-7422-ca03-7ea5-e67ff1a00136");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2063);
        internalCounters.push_back(2433);
        internalCounters.push_back(2803);
        internalCounters.push_back(3173);

        c.DefineDerivedCounter("PreZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z before shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "df7f705e-5162-d3b5-da8b-63466cf9c4e5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2062);
        internalCounters.push_back(2432);
        internalCounters.push_back(2802);
        internalCounters.push_back(3172);

        c.DefineDerivedCounter("PreZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z before shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "4484e950-f7a4-3800-bc74-78dd297f017e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2058);
        internalCounters.push_back(2428);
        internalCounters.push_back(2798);
        internalCounters.push_back(3168);

        c.DefineDerivedCounter("PostZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z after shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "4995d5d6-2330-b986-508b-fae24856f44c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2060);
        internalCounters.push_back(2430);
        internalCounters.push_back(2800);
        internalCounters.push_back(3170);

        c.DefineDerivedCounter("PostZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z after shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "ae558af4-f4be-3dd4-7316-b2c4dcf0def8");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(2059);
        internalCounters.push_back(2429);
        internalCounters.push_back(2799);
        internalCounters.push_back(3169);

        c.DefineDerivedCounter("PostZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z after shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "b3684c94-814a-c695-c85d-a5b6ab798b35");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1930);
        internalCounters.push_back(2300);
        internalCounters.push_back(2670);
        internalCounters.push_back(3040);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("ZUnitStalled", "DepthAndStencil", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,/,NUM_SHADER_ENGINES,/,(100),*", "5e86c3ad-1726-3157-1d01-7ed188bf854d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1930);
        internalCounters.push_back(2300);
        internalCounters.push_back(2670);
        internalCounters.push_back(3040);

        c.DefineDerivedCounter("ZUnitStalledCycles", "DepthAndStencil", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,NUM_SHADER_ENGINES,/", "4351fa7f-6737-2c3e-3ffb-b3addbdceedd");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1932);
        internalCounters.push_back(2302);
        internalCounters.push_back(2672);
        internalCounters.push_back(3042);
        internalCounters.push_back(1939);
        internalCounters.push_back(2309);
        internalCounters.push_back(2679);
        internalCounters.push_back(3049);

        c.DefineDerivedCounter("DBMemRead", "DepthAndStencil", "Number of bytes read from the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,sum4,(256),*,4,5,6,7,sum4,(32),*,+", "dcdb4ee7-bd50-00f7-c028-9e5f4ce888c0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1944);
        internalCounters.push_back(2314);
        internalCounters.push_back(2684);
        internalCounters.push_back(3054);
        internalCounters.push_back(1947);
        internalCounters.push_back(2317);
        internalCounters.push_back(2687);
        internalCounters.push_back(3057);

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
        internalCounters.push_back(14051);
        internalCounters.push_back(14128);
        internalCounters.push_back(14205);
        internalCounters.push_back(14282);
        internalCounters.push_back(14359);
        internalCounters.push_back(14436);
        internalCounters.push_back(14513);
        internalCounters.push_back(14590);
        internalCounters.push_back(14667);
        internalCounters.push_back(14744);
        internalCounters.push_back(14821);
        internalCounters.push_back(14898);
        internalCounters.push_back(14975);
        internalCounters.push_back(15052);
        internalCounters.push_back(15129);
        internalCounters.push_back(15206);
        internalCounters.push_back(14060);
        internalCounters.push_back(14137);
        internalCounters.push_back(14214);
        internalCounters.push_back(14291);
        internalCounters.push_back(14368);
        internalCounters.push_back(14445);
        internalCounters.push_back(14522);
        internalCounters.push_back(14599);
        internalCounters.push_back(14676);
        internalCounters.push_back(14753);
        internalCounters.push_back(14830);
        internalCounters.push_back(14907);
        internalCounters.push_back(14984);
        internalCounters.push_back(15061);
        internalCounters.push_back(15138);
        internalCounters.push_back(15215);

        c.DefineDerivedCounter("L0CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L0 cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "be1e0578-82b8-ad7f-ba3f-3afce150937a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14051);
        internalCounters.push_back(14128);
        internalCounters.push_back(14205);
        internalCounters.push_back(14282);
        internalCounters.push_back(14359);
        internalCounters.push_back(14436);
        internalCounters.push_back(14513);
        internalCounters.push_back(14590);
        internalCounters.push_back(14667);
        internalCounters.push_back(14744);
        internalCounters.push_back(14821);
        internalCounters.push_back(14898);
        internalCounters.push_back(14975);
        internalCounters.push_back(15052);
        internalCounters.push_back(15129);
        internalCounters.push_back(15206);
        internalCounters.push_back(14060);
        internalCounters.push_back(14137);
        internalCounters.push_back(14214);
        internalCounters.push_back(14291);
        internalCounters.push_back(14368);
        internalCounters.push_back(14445);
        internalCounters.push_back(14522);
        internalCounters.push_back(14599);
        internalCounters.push_back(14676);
        internalCounters.push_back(14753);
        internalCounters.push_back(14830);
        internalCounters.push_back(14907);
        internalCounters.push_back(14984);
        internalCounters.push_back(15061);
        internalCounters.push_back(15138);
        internalCounters.push_back(15215);

        c.DefineDerivedCounter("L0CacheHitCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that hit the data in L0 cache.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-", "467f8740-98f0-2211-b8e2-3d60c40d9921");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14060);
        internalCounters.push_back(14137);
        internalCounters.push_back(14214);
        internalCounters.push_back(14291);
        internalCounters.push_back(14368);
        internalCounters.push_back(14445);
        internalCounters.push_back(14522);
        internalCounters.push_back(14599);
        internalCounters.push_back(14676);
        internalCounters.push_back(14753);
        internalCounters.push_back(14830);
        internalCounters.push_back(14907);
        internalCounters.push_back(14984);
        internalCounters.push_back(15061);
        internalCounters.push_back(15138);
        internalCounters.push_back(15215);

        c.DefineDerivedCounter("L0CacheMissCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that miss the data in L0 cache.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "db23a1fd-a359-64d4-7283-f6a02bd8db64");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15891);
        internalCounters.push_back(15895);

        c.DefineDerivedCounter("L1CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data in L1 cache. Writes and atomics always miss this cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),1,0,/,-,(100),*,0,ifnotzero", "b10c589c-f7a5-b8f2-46c2-e0aed4a84105");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15891);
        internalCounters.push_back(15895);

        c.DefineDerivedCounter("L1CacheHitCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that hit the data in L1 cache. Writes and atomics always miss this cache.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,-", "e58da8e8-3c2d-723d-9e95-97888210155b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15895);

        c.DefineDerivedCounter("L1CacheMissCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that miss the data in L1 cache. Writes and atomics always miss this cache.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "b9ee1c8c-9c9b-8b7e-6d9b-a7a94053a0ee");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16308);
        internalCounters.push_back(16543);
        internalCounters.push_back(16778);
        internalCounters.push_back(17013);
        internalCounters.push_back(17248);
        internalCounters.push_back(17483);
        internalCounters.push_back(17718);
        internalCounters.push_back(17953);
        internalCounters.push_back(18188);
        internalCounters.push_back(18423);
        internalCounters.push_back(18658);
        internalCounters.push_back(18893);
        internalCounters.push_back(19128);
        internalCounters.push_back(19363);
        internalCounters.push_back(19598);
        internalCounters.push_back(19833);
        internalCounters.push_back(20068);
        internalCounters.push_back(20303);
        internalCounters.push_back(20538);
        internalCounters.push_back(20773);
        internalCounters.push_back(21008);
        internalCounters.push_back(21243);
        internalCounters.push_back(21478);
        internalCounters.push_back(21713);
        internalCounters.push_back(16340);
        internalCounters.push_back(16575);
        internalCounters.push_back(16810);
        internalCounters.push_back(17045);
        internalCounters.push_back(17280);
        internalCounters.push_back(17515);
        internalCounters.push_back(17750);
        internalCounters.push_back(17985);
        internalCounters.push_back(18220);
        internalCounters.push_back(18455);
        internalCounters.push_back(18690);
        internalCounters.push_back(18925);
        internalCounters.push_back(19160);
        internalCounters.push_back(19395);
        internalCounters.push_back(19630);
        internalCounters.push_back(19865);
        internalCounters.push_back(20100);
        internalCounters.push_back(20335);
        internalCounters.push_back(20570);
        internalCounters.push_back(20805);
        internalCounters.push_back(21040);
        internalCounters.push_back(21275);
        internalCounters.push_back(21510);
        internalCounters.push_back(21745);

        c.DefineDerivedCounter("L2CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the L2 cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum24,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24,ifnotzero", "d78fdf66-104f-8372-02c1-91d07d7dc62e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16340);
        internalCounters.push_back(16575);
        internalCounters.push_back(16810);
        internalCounters.push_back(17045);
        internalCounters.push_back(17280);
        internalCounters.push_back(17515);
        internalCounters.push_back(17750);
        internalCounters.push_back(17985);
        internalCounters.push_back(18220);
        internalCounters.push_back(18455);
        internalCounters.push_back(18690);
        internalCounters.push_back(18925);
        internalCounters.push_back(19160);
        internalCounters.push_back(19395);
        internalCounters.push_back(19630);
        internalCounters.push_back(19865);
        internalCounters.push_back(20100);
        internalCounters.push_back(20335);
        internalCounters.push_back(20570);
        internalCounters.push_back(20805);
        internalCounters.push_back(21040);
        internalCounters.push_back(21275);
        internalCounters.push_back(21510);
        internalCounters.push_back(21745);
        internalCounters.push_back(16308);
        internalCounters.push_back(16543);
        internalCounters.push_back(16778);
        internalCounters.push_back(17013);
        internalCounters.push_back(17248);
        internalCounters.push_back(17483);
        internalCounters.push_back(17718);
        internalCounters.push_back(17953);
        internalCounters.push_back(18188);
        internalCounters.push_back(18423);
        internalCounters.push_back(18658);
        internalCounters.push_back(18893);
        internalCounters.push_back(19128);
        internalCounters.push_back(19363);
        internalCounters.push_back(19598);
        internalCounters.push_back(19833);
        internalCounters.push_back(20068);
        internalCounters.push_back(20303);
        internalCounters.push_back(20538);
        internalCounters.push_back(20773);
        internalCounters.push_back(21008);
        internalCounters.push_back(21243);
        internalCounters.push_back(21478);
        internalCounters.push_back(21713);

        c.DefineDerivedCounter("L2CacheMiss", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that miss the L2 cache. Value range: 0% (optimal) to 100% (all miss).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum24,/,(100),*", "4cd70885-41b3-25cd-92db-c76a0decc634");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16308);
        internalCounters.push_back(16543);
        internalCounters.push_back(16778);
        internalCounters.push_back(17013);
        internalCounters.push_back(17248);
        internalCounters.push_back(17483);
        internalCounters.push_back(17718);
        internalCounters.push_back(17953);
        internalCounters.push_back(18188);
        internalCounters.push_back(18423);
        internalCounters.push_back(18658);
        internalCounters.push_back(18893);
        internalCounters.push_back(19128);
        internalCounters.push_back(19363);
        internalCounters.push_back(19598);
        internalCounters.push_back(19833);
        internalCounters.push_back(20068);
        internalCounters.push_back(20303);
        internalCounters.push_back(20538);
        internalCounters.push_back(20773);
        internalCounters.push_back(21008);
        internalCounters.push_back(21243);
        internalCounters.push_back(21478);
        internalCounters.push_back(21713);
        internalCounters.push_back(16340);
        internalCounters.push_back(16575);
        internalCounters.push_back(16810);
        internalCounters.push_back(17045);
        internalCounters.push_back(17280);
        internalCounters.push_back(17515);
        internalCounters.push_back(17750);
        internalCounters.push_back(17985);
        internalCounters.push_back(18220);
        internalCounters.push_back(18455);
        internalCounters.push_back(18690);
        internalCounters.push_back(18925);
        internalCounters.push_back(19160);
        internalCounters.push_back(19395);
        internalCounters.push_back(19630);
        internalCounters.push_back(19865);
        internalCounters.push_back(20100);
        internalCounters.push_back(20335);
        internalCounters.push_back(20570);
        internalCounters.push_back(20805);
        internalCounters.push_back(21040);
        internalCounters.push_back(21275);
        internalCounters.push_back(21510);
        internalCounters.push_back(21745);

        c.DefineDerivedCounter("L2CacheHitCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that hit the L2 cache.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum24,-", "d0bce171-560c-1895-66b3-bc56abccb077");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16340);
        internalCounters.push_back(16575);
        internalCounters.push_back(16810);
        internalCounters.push_back(17045);
        internalCounters.push_back(17280);
        internalCounters.push_back(17515);
        internalCounters.push_back(17750);
        internalCounters.push_back(17985);
        internalCounters.push_back(18220);
        internalCounters.push_back(18455);
        internalCounters.push_back(18690);
        internalCounters.push_back(18925);
        internalCounters.push_back(19160);
        internalCounters.push_back(19395);
        internalCounters.push_back(19630);
        internalCounters.push_back(19865);
        internalCounters.push_back(20100);
        internalCounters.push_back(20335);
        internalCounters.push_back(20570);
        internalCounters.push_back(20805);
        internalCounters.push_back(21040);
        internalCounters.push_back(21275);
        internalCounters.push_back(21510);
        internalCounters.push_back(21745);

        c.DefineDerivedCounter("L2CacheMissCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that miss the L2 cache.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24", "f2ab3a1a-ead6-9893-961b-88ba2a758807");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16394);
        internalCounters.push_back(16629);
        internalCounters.push_back(16864);
        internalCounters.push_back(17099);
        internalCounters.push_back(17334);
        internalCounters.push_back(17569);
        internalCounters.push_back(17804);
        internalCounters.push_back(18039);
        internalCounters.push_back(18274);
        internalCounters.push_back(18509);
        internalCounters.push_back(18744);
        internalCounters.push_back(18979);
        internalCounters.push_back(19214);
        internalCounters.push_back(19449);
        internalCounters.push_back(19684);
        internalCounters.push_back(19919);
        internalCounters.push_back(20154);
        internalCounters.push_back(20389);
        internalCounters.push_back(20624);
        internalCounters.push_back(20859);
        internalCounters.push_back(21094);
        internalCounters.push_back(21329);
        internalCounters.push_back(21564);
        internalCounters.push_back(21799);
        internalCounters.push_back(16395);
        internalCounters.push_back(16630);
        internalCounters.push_back(16865);
        internalCounters.push_back(17100);
        internalCounters.push_back(17335);
        internalCounters.push_back(17570);
        internalCounters.push_back(17805);
        internalCounters.push_back(18040);
        internalCounters.push_back(18275);
        internalCounters.push_back(18510);
        internalCounters.push_back(18745);
        internalCounters.push_back(18980);
        internalCounters.push_back(19215);
        internalCounters.push_back(19450);
        internalCounters.push_back(19685);
        internalCounters.push_back(19920);
        internalCounters.push_back(20155);
        internalCounters.push_back(20390);
        internalCounters.push_back(20625);
        internalCounters.push_back(20860);
        internalCounters.push_back(21095);
        internalCounters.push_back(21330);
        internalCounters.push_back(21565);
        internalCounters.push_back(21800);
        internalCounters.push_back(16396);
        internalCounters.push_back(16631);
        internalCounters.push_back(16866);
        internalCounters.push_back(17101);
        internalCounters.push_back(17336);
        internalCounters.push_back(17571);
        internalCounters.push_back(17806);
        internalCounters.push_back(18041);
        internalCounters.push_back(18276);
        internalCounters.push_back(18511);
        internalCounters.push_back(18746);
        internalCounters.push_back(18981);
        internalCounters.push_back(19216);
        internalCounters.push_back(19451);
        internalCounters.push_back(19686);
        internalCounters.push_back(19921);
        internalCounters.push_back(20156);
        internalCounters.push_back(20391);
        internalCounters.push_back(20626);
        internalCounters.push_back(20861);
        internalCounters.push_back(21096);
        internalCounters.push_back(21331);
        internalCounters.push_back(21566);
        internalCounters.push_back(21801);
        internalCounters.push_back(16397);
        internalCounters.push_back(16632);
        internalCounters.push_back(16867);
        internalCounters.push_back(17102);
        internalCounters.push_back(17337);
        internalCounters.push_back(17572);
        internalCounters.push_back(17807);
        internalCounters.push_back(18042);
        internalCounters.push_back(18277);
        internalCounters.push_back(18512);
        internalCounters.push_back(18747);
        internalCounters.push_back(18982);
        internalCounters.push_back(19217);
        internalCounters.push_back(19452);
        internalCounters.push_back(19687);
        internalCounters.push_back(19922);
        internalCounters.push_back(20157);
        internalCounters.push_back(20392);
        internalCounters.push_back(20627);
        internalCounters.push_back(20862);
        internalCounters.push_back(21097);
        internalCounters.push_back(21332);
        internalCounters.push_back(21567);
        internalCounters.push_back(21802);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total bytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24,(32),*,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum24,(64),*,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,sum24,(96),*,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,sum24,(128),*,sum4", "664bb3ef-6eca-86b1-1e2d-30cb897b5fa9");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16380);
        internalCounters.push_back(16615);
        internalCounters.push_back(16850);
        internalCounters.push_back(17085);
        internalCounters.push_back(17320);
        internalCounters.push_back(17555);
        internalCounters.push_back(17790);
        internalCounters.push_back(18025);
        internalCounters.push_back(18260);
        internalCounters.push_back(18495);
        internalCounters.push_back(18730);
        internalCounters.push_back(18965);
        internalCounters.push_back(19200);
        internalCounters.push_back(19435);
        internalCounters.push_back(19670);
        internalCounters.push_back(19905);
        internalCounters.push_back(20140);
        internalCounters.push_back(20375);
        internalCounters.push_back(20610);
        internalCounters.push_back(20845);
        internalCounters.push_back(21080);
        internalCounters.push_back(21315);
        internalCounters.push_back(21550);
        internalCounters.push_back(21785);
        internalCounters.push_back(16381);
        internalCounters.push_back(16616);
        internalCounters.push_back(16851);
        internalCounters.push_back(17086);
        internalCounters.push_back(17321);
        internalCounters.push_back(17556);
        internalCounters.push_back(17791);
        internalCounters.push_back(18026);
        internalCounters.push_back(18261);
        internalCounters.push_back(18496);
        internalCounters.push_back(18731);
        internalCounters.push_back(18966);
        internalCounters.push_back(19201);
        internalCounters.push_back(19436);
        internalCounters.push_back(19671);
        internalCounters.push_back(19906);
        internalCounters.push_back(20141);
        internalCounters.push_back(20376);
        internalCounters.push_back(20611);
        internalCounters.push_back(20846);
        internalCounters.push_back(21081);
        internalCounters.push_back(21316);
        internalCounters.push_back(21551);
        internalCounters.push_back(21786);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total bytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,sum24,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum24,-,(32),*,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum24,(64),*,+", "f96f2c16-b1b4-4ec4-229c-fc82e6f80a82");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9465);
        internalCounters.push_back(9691);
        internalCounters.push_back(9917);
        internalCounters.push_back(10143);
        internalCounters.push_back(10369);
        internalCounters.push_back(10595);
        internalCounters.push_back(10821);
        internalCounters.push_back(11047);
        internalCounters.push_back(11273);
        internalCounters.push_back(11499);
        internalCounters.push_back(11725);
        internalCounters.push_back(11951);
        internalCounters.push_back(12177);
        internalCounters.push_back(12403);
        internalCounters.push_back(12629);
        internalCounters.push_back(12855);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9465);
        internalCounters.push_back(9691);
        internalCounters.push_back(9917);
        internalCounters.push_back(10143);
        internalCounters.push_back(10369);
        internalCounters.push_back(10595);
        internalCounters.push_back(10821);
        internalCounters.push_back(11047);
        internalCounters.push_back(11273);
        internalCounters.push_back(11499);
        internalCounters.push_back(11725);
        internalCounters.push_back(11951);
        internalCounters.push_back(12177);
        internalCounters.push_back(12403);
        internalCounters.push_back(12629);
        internalCounters.push_back(12855);

        c.DefineDerivedCounter("MemUnitBusyCycles", "GlobalMemory", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalledCycles). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "168f077c-4797-b2f5-717f-105c725266c8");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14078);
        internalCounters.push_back(14155);
        internalCounters.push_back(14232);
        internalCounters.push_back(14309);
        internalCounters.push_back(14386);
        internalCounters.push_back(14463);
        internalCounters.push_back(14540);
        internalCounters.push_back(14617);
        internalCounters.push_back(14694);
        internalCounters.push_back(14771);
        internalCounters.push_back(14848);
        internalCounters.push_back(14925);
        internalCounters.push_back(15002);
        internalCounters.push_back(15079);
        internalCounters.push_back(15156);
        internalCounters.push_back(15233);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ARRAYS,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14078);
        internalCounters.push_back(14155);
        internalCounters.push_back(14232);
        internalCounters.push_back(14309);
        internalCounters.push_back(14386);
        internalCounters.push_back(14463);
        internalCounters.push_back(14540);
        internalCounters.push_back(14617);
        internalCounters.push_back(14694);
        internalCounters.push_back(14771);

        c.DefineDerivedCounter("MemUnitStalledCycles", "GlobalMemory", "Number of GPU cycles the memory unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,max10", "2745659a-0e40-bace-3b9b-86a54f8e4623");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16384);
        internalCounters.push_back(16619);
        internalCounters.push_back(16854);
        internalCounters.push_back(17089);
        internalCounters.push_back(17324);
        internalCounters.push_back(17559);
        internalCounters.push_back(17794);
        internalCounters.push_back(18029);
        internalCounters.push_back(18264);
        internalCounters.push_back(18499);
        internalCounters.push_back(18734);
        internalCounters.push_back(18969);
        internalCounters.push_back(19204);
        internalCounters.push_back(19439);
        internalCounters.push_back(19674);
        internalCounters.push_back(19909);
        internalCounters.push_back(20144);
        internalCounters.push_back(20379);
        internalCounters.push_back(20614);
        internalCounters.push_back(20849);
        internalCounters.push_back(21084);
        internalCounters.push_back(21319);
        internalCounters.push_back(21554);
        internalCounters.push_back(21789);
        internalCounters.push_back(1868);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,max24,24,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(16384);
        internalCounters.push_back(16619);
        internalCounters.push_back(16854);
        internalCounters.push_back(17089);
        internalCounters.push_back(17324);
        internalCounters.push_back(17559);
        internalCounters.push_back(17794);
        internalCounters.push_back(18029);
        internalCounters.push_back(18264);
        internalCounters.push_back(18499);
        internalCounters.push_back(18734);
        internalCounters.push_back(18969);
        internalCounters.push_back(19204);
        internalCounters.push_back(19439);
        internalCounters.push_back(19674);
        internalCounters.push_back(19909);
        internalCounters.push_back(20144);
        internalCounters.push_back(20379);
        internalCounters.push_back(20614);
        internalCounters.push_back(20849);
        internalCounters.push_back(21084);
        internalCounters.push_back(21319);
        internalCounters.push_back(21554);
        internalCounters.push_back(21789);

        c.DefineDerivedCounter("WriteUnitStalledCycles", "GlobalMemory", "Number of GPU cycles the Write unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,max24", "ede3305e-abd4-d6bf-6b00-ffc57a29fce3");
    }
}

