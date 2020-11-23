//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions for DX11 GFX10 
//==============================================================================

#include "gpa_counter.h"
#include "public_counter_definitions_dx11_gfx10.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersDX11_Gfx10(GPA_DerivedCounters& c)
{
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(58892);

        c.DefineDerivedCounter("GPUTime", "Timing", "Time this API command took to execute on the GPU in nanoseconds from the time the previous command reached the bottom of the pipeline (BOP) to the time this command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "0,TS_FREQ,/,(1000000000),*", "cbd338f2-de6c-7b14-92ad-ba724ca2e501");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(24);
        internalCounters.push_back(0);

        c.DefineDerivedCounter("GPUBusy", "Timing", "The percentage of time the GPU command processor was busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,(100),*,(100),min", "b1ba5363-1abc-fe66-2fdd-1fe6ee8989a0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(24);

        c.DefineDerivedCounter("GPUBusyCycles", "Timing", "Number of GPU cycles that the GPU command processor was busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0", "451cb045-23af-ac44-4603-d5832fa041d9");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(20116);
        internalCounters.push_back(20445);
        internalCounters.push_back(20128);
        internalCounters.push_back(20457);
        internalCounters.push_back(19809);
        internalCounters.push_back(20138);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("VSBusy", "Timing", "The percentage of time the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,2,2,ifnotzero,4,4,ifnotzero,1,3,3,ifnotzero,5,5,ifnotzero,max,6,/,(100),*,(100),min", "94caad5e-867c-6c09-cf3a-d05b51df8f3b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(20116);
        internalCounters.push_back(20445);
        internalCounters.push_back(20128);
        internalCounters.push_back(20457);
        internalCounters.push_back(19809);
        internalCounters.push_back(20138);

        c.DefineDerivedCounter("VSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,2,2,ifnotzero,4,4,ifnotzero,1,3,3,ifnotzero,5,5,ifnotzero,max", "a2086d4e-274b-48a8-3e08-a4ab76ac15dd");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(58892);
        internalCounters.push_back(20116);
        internalCounters.push_back(20445);
        internalCounters.push_back(20128);
        internalCounters.push_back(20457);
        internalCounters.push_back(19809);
        internalCounters.push_back(20138);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("VSTime", "Timing", "Time vertex shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "1,3,3,ifnotzero,5,5,ifnotzero,2,4,4,ifnotzero,6,6,ifnotzero,max,7,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "d6ce819e-69af-a241-d07a-5dd8d146e436");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(19842);
        internalCounters.push_back(20171);
        internalCounters.push_back(19849);
        internalCounters.push_back(20178);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("HSBusy", "Timing", "The percentage of time the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,2,ifnotzero,(0),1,3,ifnotzero,max,4,/,(100),*,(100),min", "16f30a0b-4cbf-eccd-b13f-ab68dd254d32");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(19842);
        internalCounters.push_back(20171);
        internalCounters.push_back(19849);
        internalCounters.push_back(20178);

        c.DefineDerivedCounter("HSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,2,ifnotzero,(0),1,3,ifnotzero,max", "753e76ef-8ef8-3f13-b511-4bd9f3589fdb");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(58892);
        internalCounters.push_back(19842);
        internalCounters.push_back(20171);
        internalCounters.push_back(19849);
        internalCounters.push_back(20178);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("HSTime", "Timing", "Time hull shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,3,ifnotzero,(0),2,4,ifnotzero,max,5,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "8386a863-dd34-1526-f703-0f0c7b241bc4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(19809);
        internalCounters.push_back(20138);
        internalCounters.push_back(20116);
        internalCounters.push_back(20445);
        internalCounters.push_back(20122);
        internalCounters.push_back(20451);
        internalCounters.push_back(20134);
        internalCounters.push_back(20463);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("DSBusy", "Timing", "The percentage of time the ShaderUnit has domain shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,2,4,ifnotzero,6,ifnotzero,(0),1,3,5,ifnotzero,7,ifnotzero,max,8,/,(100),*,(100),min", "0c626e8a-9b82-b6d4-d9a3-578509316301");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(19809);
        internalCounters.push_back(20138);
        internalCounters.push_back(20116);
        internalCounters.push_back(20445);
        internalCounters.push_back(20122);
        internalCounters.push_back(20451);
        internalCounters.push_back(20134);
        internalCounters.push_back(20463);

        c.DefineDerivedCounter("DSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has domain shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,2,4,ifnotzero,6,ifnotzero,(0),1,3,5,ifnotzero,7,ifnotzero,max", "2f3f7561-0549-2232-536d-129ffc5f7703");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(58892);
        internalCounters.push_back(19809);
        internalCounters.push_back(20138);
        internalCounters.push_back(20116);
        internalCounters.push_back(20445);
        internalCounters.push_back(20122);
        internalCounters.push_back(20451);
        internalCounters.push_back(20134);
        internalCounters.push_back(20463);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("DSTime", "Timing", "Time domain shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,3,5,ifnotzero,7,ifnotzero,(0),2,4,6,ifnotzero,8,ifnotzero,max,9,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "bfe28947-c727-8a9f-aa59-c218e58bfba5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(19868);
        internalCounters.push_back(20197);
        internalCounters.push_back(19888);
        internalCounters.push_back(20217);
        internalCounters.push_back(19869);
        internalCounters.push_back(20198);
        internalCounters.push_back(19889);
        internalCounters.push_back(20218);
        internalCounters.push_back(19870);
        internalCounters.push_back(20199);
        internalCounters.push_back(19890);
        internalCounters.push_back(20219);
        internalCounters.push_back(19871);
        internalCounters.push_back(20200);
        internalCounters.push_back(19891);
        internalCounters.push_back(20220);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("PSBusy", "Timing", "The percentage of time the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,2,ifnotzero,(0),1,3,ifnotzero,max,(0),4,6,ifnotzero,(0),5,7,ifnotzero,max,(0),8,10,ifnotzero,(0),9,11,ifnotzero,max,(0),12,14,ifnotzero,(0),13,15,ifnotzero,max,max4,16,/,(100),*,(100),min", "7e772beb-d82c-bd9a-aed0-fe504d416ce5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(19868);
        internalCounters.push_back(20197);
        internalCounters.push_back(19888);
        internalCounters.push_back(20217);
        internalCounters.push_back(19869);
        internalCounters.push_back(20198);
        internalCounters.push_back(19889);
        internalCounters.push_back(20218);
        internalCounters.push_back(19870);
        internalCounters.push_back(20199);
        internalCounters.push_back(19890);
        internalCounters.push_back(20219);
        internalCounters.push_back(19871);
        internalCounters.push_back(20200);
        internalCounters.push_back(19891);
        internalCounters.push_back(20220);

        c.DefineDerivedCounter("PSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,2,ifnotzero,(0),1,3,ifnotzero,max,(0),4,6,ifnotzero,(0),5,7,ifnotzero,max,(0),8,10,ifnotzero,(0),9,11,ifnotzero,max,(0),12,14,ifnotzero,(0),13,15,ifnotzero,max,max4", "b58bea04-ce8e-2984-80f4-8aba7d4c817b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(58892);
        internalCounters.push_back(19868);
        internalCounters.push_back(20197);
        internalCounters.push_back(19888);
        internalCounters.push_back(20217);
        internalCounters.push_back(19869);
        internalCounters.push_back(20198);
        internalCounters.push_back(19889);
        internalCounters.push_back(20218);
        internalCounters.push_back(19870);
        internalCounters.push_back(20199);
        internalCounters.push_back(19890);
        internalCounters.push_back(20219);
        internalCounters.push_back(19871);
        internalCounters.push_back(20200);
        internalCounters.push_back(19891);
        internalCounters.push_back(20220);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("PSTime", "Timing", "Time pixel shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,3,ifnotzero,(0),2,4,ifnotzero,max,(0),5,7,ifnotzero,(0),6,8,ifnotzero,max,(0),9,11,ifnotzero,(0),10,12,ifnotzero,max,(0),13,15,ifnotzero,(0),14,16,ifnotzero,max,max4,17,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "edca7694-7416-e8a6-0c5a-63a5ad5f3d74");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(19853);
        internalCounters.push_back(20182);
        internalCounters.push_back(19857);
        internalCounters.push_back(20186);
        internalCounters.push_back(19859);
        internalCounters.push_back(20188);
        internalCounters.push_back(19863);
        internalCounters.push_back(20192);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("CSBusy", "Timing", "The percentage of time the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,comparemax2,4,5,6,7,comparemax2,max,8,/,(100),*,(100),min", "493fdd90-8d2b-a055-5e4e-2d29c3396b8c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(19853);
        internalCounters.push_back(20182);
        internalCounters.push_back(19857);
        internalCounters.push_back(20186);
        internalCounters.push_back(19859);
        internalCounters.push_back(20188);
        internalCounters.push_back(19863);
        internalCounters.push_back(20192);

        c.DefineDerivedCounter("CSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,comparemax2,4,5,6,7,comparemax2,max", "39bcf1b8-f6b2-4c37-f9af-0a2bb59512f9");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(58892);
        internalCounters.push_back(19853);
        internalCounters.push_back(20182);
        internalCounters.push_back(19857);
        internalCounters.push_back(20186);
        internalCounters.push_back(19859);
        internalCounters.push_back(20188);
        internalCounters.push_back(19863);
        internalCounters.push_back(20192);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("CSTime", "Timing", "Time compute shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "1,2,3,4,comparemax2,5,6,7,8,comparemax2,max,9,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "dbc24916-ecb2-7eef-8d63-7afadaaab6bc");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(49667);
        internalCounters.push_back(49689);
        internalCounters.push_back(49731);

        c.DefineDerivedCounter("VSVerticesIn", "VertexShader", "The number of vertices processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero", "810a04c8-2ff4-081d-766d-bfa2bd4ad916");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(21554);
        internalCounters.push_back(22066);
        internalCounters.push_back(21494);
        internalCounters.push_back(22006);
        internalCounters.push_back(25650);
        internalCounters.push_back(26162);
        internalCounters.push_back(25590);
        internalCounters.push_back(26102);
        internalCounters.push_back(23602);
        internalCounters.push_back(24114);
        internalCounters.push_back(23542);
        internalCounters.push_back(24054);

        c.DefineDerivedCounter("VSVALUInstCount", "VertexShader", "Average number of vector ALU instructions executed in the VS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,sum2,6,7,sum2,/,6,7,sum2,ifnotzero,8,9,sum2,10,11,sum2,/,10,11,sum2,ifnotzero", "8ec604e4-63f5-e6b5-4558-c38f0b26d4b1");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(21554);
        internalCounters.push_back(22066);
        internalCounters.push_back(21494);
        internalCounters.push_back(22006);
        internalCounters.push_back(25650);
        internalCounters.push_back(26162);
        internalCounters.push_back(25590);
        internalCounters.push_back(26102);
        internalCounters.push_back(23602);
        internalCounters.push_back(24114);
        internalCounters.push_back(23542);
        internalCounters.push_back(24054);

        c.DefineDerivedCounter("VSSALUInstCount", "VertexShader", "Average number of scalar ALU instructions executed in the VS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,sum2,6,7,sum2,/,6,7,sum2,ifnotzero,8,9,sum2,10,11,sum2,/,10,11,sum2,ifnotzero", "e3da0383-7322-7f65-8cf2-3ce641578e54");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(21607);
        internalCounters.push_back(22119);
        internalCounters.push_back(25703);
        internalCounters.push_back(26215);
        internalCounters.push_back(23655);
        internalCounters.push_back(24167);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("VSVALUBusy", "VertexShader", "The percentage of GPUTime vector ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,sum2,2,3,sum2,2,3,sum2,ifnotzero,4,5,sum2,4,5,sum2,ifnotzero,NUM_SIMDS,/,6,/,(100),*", "8b3572f7-fda0-eddf-6c93-2ab145b8754b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(21607);
        internalCounters.push_back(22119);
        internalCounters.push_back(25703);
        internalCounters.push_back(26215);
        internalCounters.push_back(23655);
        internalCounters.push_back(24167);

        c.DefineDerivedCounter("VSVALUBusyCycles", "VertexShader", "Number of GPU cycles where vector ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,sum2,2,3,sum2,2,3,sum2,ifnotzero,4,5,sum2,4,5,sum2,ifnotzero", "0af1686e-6d77-2f6e-2862-7bb8e869a776");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(21550);
        internalCounters.push_back(22062);
        internalCounters.push_back(25646);
        internalCounters.push_back(26158);
        internalCounters.push_back(23598);
        internalCounters.push_back(24110);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("VSSALUBusy", "VertexShader", "The percentage of GPUTime scalar ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,sum2,2,3,sum2,2,3,sum2,ifnotzero,4,5,sum2,4,5,sum2,ifnotzero,NUM_CUS,/,6,/,(100),*", "3bc8730c-e3bc-e2f0-7d24-36974064c25a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(21550);
        internalCounters.push_back(22062);
        internalCounters.push_back(25646);
        internalCounters.push_back(26158);
        internalCounters.push_back(23598);
        internalCounters.push_back(24110);

        c.DefineDerivedCounter("VSSALUBusyCycles", "VertexShader", "Number of GPU cycles where scalar ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,sum2,2,3,sum2,2,3,sum2,ifnotzero,4,5,sum2,4,5,sum2,ifnotzero,NUM_CUS,/", "357ac7cd-2e1c-dcb0-77f6-37527237f35b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(49683);

        c.DefineDerivedCounter("HSPatches", "HullShader", "The number of patches processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "d1bbd27d-d591-4509-df52-d329fb73a98f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(26674);
        internalCounters.push_back(27186);
        internalCounters.push_back(26614);
        internalCounters.push_back(27126);

        c.DefineDerivedCounter("HSVALUInstCount", "HullShader", "Average number of vector ALU instructions executed in the HS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,sum2,2,3,sum2,/", "786673bf-d58f-9895-3a37-9d6efb5e5804");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(26670);
        internalCounters.push_back(27182);
        internalCounters.push_back(26614);
        internalCounters.push_back(27126);

        c.DefineDerivedCounter("HSSALUInstCount", "HullShader", "Average number of scalar ALU instructions executed in the HS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,sum2,2,3,sum2,/", "1af675c4-cb0b-c4c5-c131-2796750f683e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(26727);
        internalCounters.push_back(27239);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("HSVALUBusy", "HullShader", "The percentage of GPUTime vector ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,sum2,NUM_SIMDS,/,2,/,(100),*", "7880d192-8015-0311-d43e-fb0b7a4df179");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(26727);
        internalCounters.push_back(27239);

        c.DefineDerivedCounter("HSVALUBusyCycles", "HullShader", "Number of GPU cycles vector where ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,sum2,NUM_SIMDS,/", "3afb94e4-e937-5730-0cc9-41d3113ba012");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(26670);
        internalCounters.push_back(27182);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("HSSALUBusy", "HullShader", "The percentage of GPUTime scalar ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,sum2,NUM_CUS,/,2,/,(100),*", "34748a4b-9148-0b06-b7b9-5700d6631bde");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(26670);
        internalCounters.push_back(27182);

        c.DefineDerivedCounter("HSSALUBusyCycles", "HullShader", "Number of GPU cycles where scalar ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,sum2,NUM_CUS,/", "9bceabf7-3f01-2fd9-7b1d-8fe46c729efc");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(49731);
        internalCounters.push_back(49667);
        internalCounters.push_back(49689);

        c.DefineDerivedCounter("DSVerticesIn", "DomainShader", "The number of vertices processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,1,ifnotzero,2,ifnotzero", "b88d9d05-2418-e639-4e3d-3a5815855f8d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(23602);
        internalCounters.push_back(24114);
        internalCounters.push_back(23542);
        internalCounters.push_back(24054);
        internalCounters.push_back(21554);
        internalCounters.push_back(22066);
        internalCounters.push_back(21494);
        internalCounters.push_back(22006);
        internalCounters.push_back(21498);
        internalCounters.push_back(22010);
        internalCounters.push_back(25594);
        internalCounters.push_back(26106);

        c.DefineDerivedCounter("DSVALUInstCount", "DomainShader", "Average number of vector ALU instructions executed in the DS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,sum2,2,3,sum2,/,4,5,sum2,6,7,sum2,/,8,9,sum2,ifnotzero,10,11,sum2,ifnotzero", "03a3e949-82f9-be4d-7228-5eb5ad80915a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(23598);
        internalCounters.push_back(24110);
        internalCounters.push_back(23542);
        internalCounters.push_back(24054);
        internalCounters.push_back(21550);
        internalCounters.push_back(22062);
        internalCounters.push_back(21494);
        internalCounters.push_back(22006);
        internalCounters.push_back(21498);
        internalCounters.push_back(22010);
        internalCounters.push_back(25594);
        internalCounters.push_back(26106);

        c.DefineDerivedCounter("DSSALUInstCount", "DomainShader", "Average number of scalar ALU instructions executed in the DS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,sum2,2,3,sum2,/,4,5,sum2,6,7,sum2,/,8,9,sum2,ifnotzero,10,11,sum2,ifnotzero", "73daa728-483e-95d0-5b40-504719aadc1c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13533);
        internalCounters.push_back(13799);
        internalCounters.push_back(14065);
        internalCounters.push_back(14331);
        internalCounters.push_back(13537);
        internalCounters.push_back(13803);
        internalCounters.push_back(14069);
        internalCounters.push_back(14335);
        internalCounters.push_back(13489);
        internalCounters.push_back(13755);
        internalCounters.push_back(14021);
        internalCounters.push_back(14287);
        internalCounters.push_back(13501);
        internalCounters.push_back(13767);
        internalCounters.push_back(14033);
        internalCounters.push_back(14299);
        internalCounters.push_back(13490);
        internalCounters.push_back(13756);
        internalCounters.push_back(14022);
        internalCounters.push_back(14288);
        internalCounters.push_back(13502);
        internalCounters.push_back(13768);
        internalCounters.push_back(14034);
        internalCounters.push_back(14300);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("PrimitiveAssemblyBusy", "Timing", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max,24,/,(100),*,(100),min", "54ac5640-c4d7-95e2-20e0-6a9fdfc07333");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13533);
        internalCounters.push_back(13799);
        internalCounters.push_back(14065);
        internalCounters.push_back(14331);
        internalCounters.push_back(13537);
        internalCounters.push_back(13803);
        internalCounters.push_back(14069);
        internalCounters.push_back(14335);
        internalCounters.push_back(13489);
        internalCounters.push_back(13755);
        internalCounters.push_back(14021);
        internalCounters.push_back(14287);
        internalCounters.push_back(13501);
        internalCounters.push_back(13767);
        internalCounters.push_back(14033);
        internalCounters.push_back(14299);
        internalCounters.push_back(13490);
        internalCounters.push_back(13756);
        internalCounters.push_back(14022);
        internalCounters.push_back(14288);
        internalCounters.push_back(13502);
        internalCounters.push_back(13768);
        internalCounters.push_back(14034);
        internalCounters.push_back(14300);

        c.DefineDerivedCounter("PrimitiveAssemblyBusyCycles", "Timing", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max", "99777f2d-9626-c78a-a97c-c4505eba1e5f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13436);
        internalCounters.push_back(13702);
        internalCounters.push_back(13968);
        internalCounters.push_back(14234);

        c.DefineDerivedCounter("PrimitivesIn", "PrimitiveAssembly", "The number of primitives received by the hardware. This includes primitives generated by tessellation.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "a515b80d-75c3-c7d2-0d2f-d7766b4759a6");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13442);
        internalCounters.push_back(13708);
        internalCounters.push_back(13974);
        internalCounters.push_back(14240);
        internalCounters.push_back(13482);
        internalCounters.push_back(13748);
        internalCounters.push_back(14014);
        internalCounters.push_back(14280);
        internalCounters.push_back(13483);
        internalCounters.push_back(13749);
        internalCounters.push_back(14015);
        internalCounters.push_back(14281);
        internalCounters.push_back(13484);
        internalCounters.push_back(13750);
        internalCounters.push_back(14016);
        internalCounters.push_back(14282);
        internalCounters.push_back(13485);
        internalCounters.push_back(13751);
        internalCounters.push_back(14017);
        internalCounters.push_back(14283);

        c.DefineDerivedCounter("CulledPrims", "PrimitiveAssembly", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+,4,+,5,+,6,+,7,+,8,+,9,+,10,+,11,+,12,+,13,+,14,+,15,+,16,+,17,+,18,+,19,+", "589bdf55-9192-280a-41c3-584bc94f2562");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13449);
        internalCounters.push_back(13715);
        internalCounters.push_back(13981);
        internalCounters.push_back(14247);

        c.DefineDerivedCounter("ClippedPrims", "PrimitiveAssembly", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "5ef6f9d5-155e-5baa-163f-8359d9ea9bbf");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13537);
        internalCounters.push_back(13803);
        internalCounters.push_back(14069);
        internalCounters.push_back(14335);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("PAStalledOnRasterizer", "PrimitiveAssembly", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,/,(100),*", "6f9f416b-53c1-0457-f88c-7b6ba8973974");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13537);
        internalCounters.push_back(13803);
        internalCounters.push_back(14069);
        internalCounters.push_back(14335);

        c.DefineDerivedCounter("PAStalledOnRasterizerCycles", "PrimitiveAssembly", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max", "7a8c492a-c566-9328-6805-760dbff5c0f2");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18920);
        internalCounters.push_back(19145);
        internalCounters.push_back(19370);
        internalCounters.push_back(19595);
        internalCounters.push_back(18925);
        internalCounters.push_back(19150);
        internalCounters.push_back(19375);
        internalCounters.push_back(19600);
        internalCounters.push_back(18930);
        internalCounters.push_back(19155);
        internalCounters.push_back(19380);
        internalCounters.push_back(19605);
        internalCounters.push_back(18935);
        internalCounters.push_back(19160);
        internalCounters.push_back(19385);
        internalCounters.push_back(19610);

        c.DefineDerivedCounter("PSPixelsOut", "PixelShader", "Pixels exported from shader to color buffers. Does not include killed or alpha tested pixels; if there are multiple render targets, each render target receives one export, so this will be 2 for 1 pixel written to two RTs.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "24cba16c-baa6-6ecd-95ad-92ecb1338da1");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18922);
        internalCounters.push_back(19147);
        internalCounters.push_back(19372);
        internalCounters.push_back(19597);
        internalCounters.push_back(18927);
        internalCounters.push_back(19152);
        internalCounters.push_back(19377);
        internalCounters.push_back(19602);
        internalCounters.push_back(18932);
        internalCounters.push_back(19157);
        internalCounters.push_back(19382);
        internalCounters.push_back(19607);
        internalCounters.push_back(18937);
        internalCounters.push_back(19162);
        internalCounters.push_back(19387);
        internalCounters.push_back(19612);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("PSExportStalls", "PixelShader", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "9b4f466c-ff97-22bb-557d-84d3c4c51895");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(18922);
        internalCounters.push_back(19147);
        internalCounters.push_back(19372);
        internalCounters.push_back(19597);
        internalCounters.push_back(18927);
        internalCounters.push_back(19152);
        internalCounters.push_back(19377);
        internalCounters.push_back(19602);
        internalCounters.push_back(18932);
        internalCounters.push_back(19157);
        internalCounters.push_back(19382);
        internalCounters.push_back(19607);
        internalCounters.push_back(18937);
        internalCounters.push_back(19162);
        internalCounters.push_back(19387);
        internalCounters.push_back(19612);

        c.DefineDerivedCounter("PSExportStallsCycles", "PixelShader", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "47c72aad-64e6-0864-d533-d8e0bc27c156");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(24626);
        internalCounters.push_back(25138);
        internalCounters.push_back(24566);
        internalCounters.push_back(25078);

        c.DefineDerivedCounter("PSVALUInstCount", "PixelShader", "Average number of vector ALU instructions executed in the PS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,sum2,2,3,sum2,/", "eb74389e-435c-4137-ecf1-39eb5bc1cbfe");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(24622);
        internalCounters.push_back(25134);
        internalCounters.push_back(24566);
        internalCounters.push_back(25078);

        c.DefineDerivedCounter("PSSALUInstCount", "PixelShader", "Average number of scalar ALU instructions executed in the PS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,sum2,2,3,sum2,/", "e6a06580-8a82-96d6-976c-acc121fc5516");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(24679);
        internalCounters.push_back(25191);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("PSVALUBusy", "PixelShader", "The percentage of GPUTime vector ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,sum2,NUM_SIMDS,/,2,/,(100),*", "6ce6fef7-8e33-10b4-f351-af755e177e85");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(24679);
        internalCounters.push_back(25191);

        c.DefineDerivedCounter("PSVALUBusyCycles", "PixelShader", "Number of GPU cycles where vector ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,sum2,NUM_SIMDS,/", "1e276f86-cd2a-72e7-fc9d-004f666f2981");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(24622);
        internalCounters.push_back(25134);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("PSSALUBusy", "PixelShader", "The percentage of GPUTime scalar ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,sum2,NUM_CUS,/,2,/,(100),*", "2ff9f34f-e94b-af4d-18c2-5fbbf6d1727a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(24622);
        internalCounters.push_back(25134);

        c.DefineDerivedCounter("PSSALUBusyCycles", "PixelShader", "Number of GPU cycles where scalar ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,sum2,NUM_CUS,/", "29808906-f128-b078-fc79-820a4b3b3b8d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSThreadGroups", "ComputeShader", "Total number of thread groups.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "8ce3fc80-56b2-97f9-8e70-2e8c747cea68");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(19857);
        internalCounters.push_back(20186);
        internalCounters.push_back(19863);
        internalCounters.push_back(20192);

        c.DefineDerivedCounter("CSWavefronts", "ComputeShader", "The total number of wavefronts used for the CS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "42379c6e-369b-c237-8b25-cdb9cdc65c4d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);
        internalCounters.push_back(27642);
        internalCounters.push_back(28154);

        c.DefineDerivedCounter("CSThreads", "ComputeShader", "The number of CS threads processed by the hardware.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,sum4,4,5,sum2,ifnotzero", "7a648013-6eac-2665-ac36-13c6f4ac9c26");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(27698);
        internalCounters.push_back(28210);
        internalCounters.push_back(27638);
        internalCounters.push_back(28150);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSVALUInsts", "ComputeShader", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,sum2,2,3,sum2,/,4,5,6,7,sum4,ifnotzero", "376cb1cc-5a40-9d1d-404c-f1736c0c5084");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(27716);
        internalCounters.push_back(28228);
        internalCounters.push_back(27751);
        internalCounters.push_back(28263);
        internalCounters.push_back(27639);
        internalCounters.push_back(28151);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSVALUUtilization", "ComputeShader", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(0),0,1,sum2,2,3,sum2,(64),(32),4,5,sum2,ifnotzero,*,/,(100),*,2,3,sum2,ifnotzero,(100),min,6,7,8,9,sum4,ifnotzero", "ae943d2a-76e1-bb68-e1e2-0e06c9031611");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(27694);
        internalCounters.push_back(28206);
        internalCounters.push_back(27638);
        internalCounters.push_back(28150);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSSALUInsts", "ComputeShader", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero", "eb211144-8136-ff86-e8bf-4d0493a904cb");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(27703);
        internalCounters.push_back(28215);
        internalCounters.push_back(27638);
        internalCounters.push_back(28150);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSVFetchInsts", "ComputeShader", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero", "3e2829c0-6215-783b-c271-6d57ff2c520e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(27695);
        internalCounters.push_back(28207);
        internalCounters.push_back(27638);
        internalCounters.push_back(28150);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSSFetchInsts", "ComputeShader", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero", "da09171c-6a0a-584f-fddc-dc5062d63a3e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(27704);
        internalCounters.push_back(28216);
        internalCounters.push_back(27638);
        internalCounters.push_back(28150);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSVWriteInsts", "ComputeShader", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero", "43438c22-e910-b377-b767-b32902e0df0d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(27751);
        internalCounters.push_back(28263);
        internalCounters.push_back(24);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSVALUBusy", "ComputeShader", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,sum2,NUM_SIMDS,/,2,/,(100),*,3,4,5,6,sum4,ifnotzero", "f1e64815-f6a8-c277-d4f9-d054b443e205");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(27751);
        internalCounters.push_back(28263);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSVALUBusyCycles", "ComputeShader", "Number of GPU cycles where vector ALU instructions are processed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,sum2,NUM_SIMDS,/,2,3,4,5,sum4,ifnotzero", "2d0d5852-2658-eb73-68d2-f23f7118c9c3");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(27694);
        internalCounters.push_back(28206);
        internalCounters.push_back(24);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSSALUBusy", "ComputeShader", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,sum2,NUM_CUS,/,2,/,(100),*,3,4,5,6,sum4,ifnotzero", "3fc35f4e-9882-94e3-6f5f-4e81cd97082a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(27694);
        internalCounters.push_back(28206);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSSALUBusyCycles", "ComputeShader", "Number of GPU cycles where scalar ALU instructions are processed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,sum2,NUM_CUS,/,2,3,4,5,sum4,ifnotzero", "de58f8fc-8ed4-a799-648d-62ded7b1c4c4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(28673);
        internalCounters.push_back(28899);
        internalCounters.push_back(29125);
        internalCounters.push_back(29351);
        internalCounters.push_back(29577);
        internalCounters.push_back(29803);
        internalCounters.push_back(30029);
        internalCounters.push_back(30255);
        internalCounters.push_back(30481);
        internalCounters.push_back(30707);
        internalCounters.push_back(30933);
        internalCounters.push_back(31159);
        internalCounters.push_back(31385);
        internalCounters.push_back(31611);
        internalCounters.push_back(31837);
        internalCounters.push_back(32063);
        internalCounters.push_back(32289);
        internalCounters.push_back(32515);
        internalCounters.push_back(32741);
        internalCounters.push_back(32967);
        internalCounters.push_back(33193);
        internalCounters.push_back(33419);
        internalCounters.push_back(33645);
        internalCounters.push_back(33871);
        internalCounters.push_back(34097);
        internalCounters.push_back(34323);
        internalCounters.push_back(34549);
        internalCounters.push_back(34775);
        internalCounters.push_back(35001);
        internalCounters.push_back(35227);
        internalCounters.push_back(35453);
        internalCounters.push_back(35679);
        internalCounters.push_back(35905);
        internalCounters.push_back(36131);
        internalCounters.push_back(36357);
        internalCounters.push_back(36583);
        internalCounters.push_back(36809);
        internalCounters.push_back(37035);
        internalCounters.push_back(37261);
        internalCounters.push_back(37487);
        internalCounters.push_back(24);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSMemUnitBusy", "ComputeShader", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,/,(100),*,41,42,43,44,sum4,ifnotzero", "42ab96e1-0a24-96c8-c4ff-098fa267d78e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(28673);
        internalCounters.push_back(28899);
        internalCounters.push_back(29125);
        internalCounters.push_back(29351);
        internalCounters.push_back(29577);
        internalCounters.push_back(29803);
        internalCounters.push_back(30029);
        internalCounters.push_back(30255);
        internalCounters.push_back(30481);
        internalCounters.push_back(30707);
        internalCounters.push_back(30933);
        internalCounters.push_back(31159);
        internalCounters.push_back(31385);
        internalCounters.push_back(31611);
        internalCounters.push_back(31837);
        internalCounters.push_back(32063);
        internalCounters.push_back(32289);
        internalCounters.push_back(32515);
        internalCounters.push_back(32741);
        internalCounters.push_back(32967);
        internalCounters.push_back(33193);
        internalCounters.push_back(33419);
        internalCounters.push_back(33645);
        internalCounters.push_back(33871);
        internalCounters.push_back(34097);
        internalCounters.push_back(34323);
        internalCounters.push_back(34549);
        internalCounters.push_back(34775);
        internalCounters.push_back(35001);
        internalCounters.push_back(35227);
        internalCounters.push_back(35453);
        internalCounters.push_back(35679);
        internalCounters.push_back(35905);
        internalCounters.push_back(36131);
        internalCounters.push_back(36357);
        internalCounters.push_back(36583);
        internalCounters.push_back(36809);
        internalCounters.push_back(37035);
        internalCounters.push_back(37261);
        internalCounters.push_back(37487);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSMemUnitBusyCycles", "ComputeShader", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,41,42,43,sum4,ifnotzero", "39d5687f-c727-7c0c-af82-bb711d3897ed");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(40174);
        internalCounters.push_back(40251);
        internalCounters.push_back(40328);
        internalCounters.push_back(40405);
        internalCounters.push_back(40482);
        internalCounters.push_back(40559);
        internalCounters.push_back(40636);
        internalCounters.push_back(40713);
        internalCounters.push_back(40790);
        internalCounters.push_back(40867);
        internalCounters.push_back(40944);
        internalCounters.push_back(41021);
        internalCounters.push_back(41098);
        internalCounters.push_back(41175);
        internalCounters.push_back(41252);
        internalCounters.push_back(41329);
        internalCounters.push_back(41406);
        internalCounters.push_back(41483);
        internalCounters.push_back(41560);
        internalCounters.push_back(41637);
        internalCounters.push_back(41714);
        internalCounters.push_back(41791);
        internalCounters.push_back(41868);
        internalCounters.push_back(41945);
        internalCounters.push_back(42022);
        internalCounters.push_back(42099);
        internalCounters.push_back(42176);
        internalCounters.push_back(42253);
        internalCounters.push_back(42330);
        internalCounters.push_back(42407);
        internalCounters.push_back(42484);
        internalCounters.push_back(42561);
        internalCounters.push_back(42638);
        internalCounters.push_back(42715);
        internalCounters.push_back(42792);
        internalCounters.push_back(42869);
        internalCounters.push_back(42946);
        internalCounters.push_back(43023);
        internalCounters.push_back(43100);
        internalCounters.push_back(43177);
        internalCounters.push_back(24);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSMemUnitStalled", "ComputeShader", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,/,(100),*,41,42,43,44,sum4,ifnotzero", "f18e8679-1511-d533-d9ee-4365197f7d0c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(40174);
        internalCounters.push_back(40251);
        internalCounters.push_back(40328);
        internalCounters.push_back(40405);
        internalCounters.push_back(40482);
        internalCounters.push_back(40559);
        internalCounters.push_back(40636);
        internalCounters.push_back(40713);
        internalCounters.push_back(40790);
        internalCounters.push_back(40867);
        internalCounters.push_back(40944);
        internalCounters.push_back(41021);
        internalCounters.push_back(41098);
        internalCounters.push_back(41175);
        internalCounters.push_back(41252);
        internalCounters.push_back(41329);
        internalCounters.push_back(41406);
        internalCounters.push_back(41483);
        internalCounters.push_back(41560);
        internalCounters.push_back(41637);
        internalCounters.push_back(41714);
        internalCounters.push_back(41791);
        internalCounters.push_back(41868);
        internalCounters.push_back(41945);
        internalCounters.push_back(42022);
        internalCounters.push_back(42099);
        internalCounters.push_back(42176);
        internalCounters.push_back(42253);
        internalCounters.push_back(42330);
        internalCounters.push_back(42407);
        internalCounters.push_back(42484);
        internalCounters.push_back(42561);
        internalCounters.push_back(42638);
        internalCounters.push_back(42715);
        internalCounters.push_back(42792);
        internalCounters.push_back(42869);
        internalCounters.push_back(42946);
        internalCounters.push_back(43023);
        internalCounters.push_back(43100);
        internalCounters.push_back(43177);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSMemUnitStalledCycles", "ComputeShader", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,41,42,43,sum4,ifnotzero", "51991c84-ed2b-bf31-c4ab-8f8e9eb8f29f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52134);
        internalCounters.push_back(52369);
        internalCounters.push_back(52604);
        internalCounters.push_back(52839);
        internalCounters.push_back(53074);
        internalCounters.push_back(53309);
        internalCounters.push_back(53544);
        internalCounters.push_back(53779);
        internalCounters.push_back(54014);
        internalCounters.push_back(54249);
        internalCounters.push_back(54484);
        internalCounters.push_back(54719);
        internalCounters.push_back(54954);
        internalCounters.push_back(55189);
        internalCounters.push_back(55424);
        internalCounters.push_back(55659);
        internalCounters.push_back(24);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSWriteUnitStalled", "ComputeShader", "The percentage of GPUTime the write unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,18,19,20,sum4,ifnotzero", "55118f7a-8f92-726f-78c6-407f689a2eb4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52134);
        internalCounters.push_back(52369);
        internalCounters.push_back(52604);
        internalCounters.push_back(52839);
        internalCounters.push_back(53074);
        internalCounters.push_back(53309);
        internalCounters.push_back(53544);
        internalCounters.push_back(53779);
        internalCounters.push_back(54014);
        internalCounters.push_back(54249);
        internalCounters.push_back(54484);
        internalCounters.push_back(54719);
        internalCounters.push_back(54954);
        internalCounters.push_back(55189);
        internalCounters.push_back(55424);
        internalCounters.push_back(55659);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSWriteUnitStalledCycles", "ComputeShader", "Number of GPU cycles the write unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,17,18,19,sum4,ifnotzero", "be164c60-5e48-acac-9622-29616d09aa9a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(27689);
        internalCounters.push_back(28201);
        internalCounters.push_back(27638);
        internalCounters.push_back(28150);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSGDSInsts", "ComputeShader", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero", "2a867f3e-4a37-ad16-55d1-f03d74707819");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(27693);
        internalCounters.push_back(28205);
        internalCounters.push_back(27638);
        internalCounters.push_back(28150);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSLDSInsts", "ComputeShader", "The average number of LDS read/write instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero", "61b0b351-7e06-ef8e-a8e0-7a9e3200a836");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(27665);
        internalCounters.push_back(28177);
        internalCounters.push_back(27638);
        internalCounters.push_back(28150);
        internalCounters.push_back(24);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSALUStalledByLDS", "ComputeShader", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(0),0,1,sum2,2,3,sum2,/,4,/,NUM_SHADER_ENGINES,/,(100),*,2,3,sum2,ifnotzero,5,6,7,8,sum4,ifnotzero", "6dc4f1c2-bad0-c9ff-156e-883b319a752a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(27665);
        internalCounters.push_back(28177);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSALUStalledByLDSCycles", "ComputeShader", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,sum2,NUM_SHADER_ENGINES,/,2,3,4,5,sum4,ifnotzero", "8f3d5f25-2159-0374-fafe-e26a7799b6c8");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(27919);
        internalCounters.push_back(28431);
        internalCounters.push_back(24);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSLDSBankConflict", "ComputeShader", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,sum2,2,/,NUM_SIMDS,/,(100),*,3,4,5,6,sum4,ifnotzero", "1065ee10-2e41-ea41-1eb3-b61b491752f4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(27919);
        internalCounters.push_back(28431);
        internalCounters.push_back(19854);
        internalCounters.push_back(20183);
        internalCounters.push_back(19860);
        internalCounters.push_back(20189);

        c.DefineDerivedCounter("CSLDSBankConflictCycles", "ComputeShader", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,sum2,NUM_SIMDS,/,2,3,4,5,sum4,ifnotzero", "1fd1adf3-c51e-94fd-083e-c482a0a0809e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(28673);
        internalCounters.push_back(28899);
        internalCounters.push_back(29125);
        internalCounters.push_back(29351);
        internalCounters.push_back(29577);
        internalCounters.push_back(29803);
        internalCounters.push_back(30029);
        internalCounters.push_back(30255);
        internalCounters.push_back(30481);
        internalCounters.push_back(30707);
        internalCounters.push_back(30933);
        internalCounters.push_back(31159);
        internalCounters.push_back(31385);
        internalCounters.push_back(31611);
        internalCounters.push_back(31837);
        internalCounters.push_back(32063);
        internalCounters.push_back(32289);
        internalCounters.push_back(32515);
        internalCounters.push_back(32741);
        internalCounters.push_back(32967);
        internalCounters.push_back(33193);
        internalCounters.push_back(33419);
        internalCounters.push_back(33645);
        internalCounters.push_back(33871);
        internalCounters.push_back(34097);
        internalCounters.push_back(34323);
        internalCounters.push_back(34549);
        internalCounters.push_back(34775);
        internalCounters.push_back(35001);
        internalCounters.push_back(35227);
        internalCounters.push_back(35453);
        internalCounters.push_back(35679);
        internalCounters.push_back(35905);
        internalCounters.push_back(36131);
        internalCounters.push_back(36357);
        internalCounters.push_back(36583);
        internalCounters.push_back(36809);
        internalCounters.push_back(37035);
        internalCounters.push_back(37261);
        internalCounters.push_back(37487);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("TexUnitBusy", "Timing", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,/,(100),*", "36afb8d9-42fc-aafe-66c5-449542153b2c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(28673);
        internalCounters.push_back(28899);
        internalCounters.push_back(29125);
        internalCounters.push_back(29351);
        internalCounters.push_back(29577);
        internalCounters.push_back(29803);
        internalCounters.push_back(30029);
        internalCounters.push_back(30255);
        internalCounters.push_back(30481);
        internalCounters.push_back(30707);
        internalCounters.push_back(30933);
        internalCounters.push_back(31159);
        internalCounters.push_back(31385);
        internalCounters.push_back(31611);
        internalCounters.push_back(31837);
        internalCounters.push_back(32063);
        internalCounters.push_back(32289);
        internalCounters.push_back(32515);
        internalCounters.push_back(32741);
        internalCounters.push_back(32967);
        internalCounters.push_back(33193);
        internalCounters.push_back(33419);
        internalCounters.push_back(33645);
        internalCounters.push_back(33871);
        internalCounters.push_back(34097);
        internalCounters.push_back(34323);
        internalCounters.push_back(34549);
        internalCounters.push_back(34775);
        internalCounters.push_back(35001);
        internalCounters.push_back(35227);
        internalCounters.push_back(35453);
        internalCounters.push_back(35679);
        internalCounters.push_back(35905);
        internalCounters.push_back(36131);
        internalCounters.push_back(36357);
        internalCounters.push_back(36583);
        internalCounters.push_back(36809);
        internalCounters.push_back(37035);
        internalCounters.push_back(37261);
        internalCounters.push_back(37487);

        c.DefineDerivedCounter("TexUnitBusyCycles", "Timing", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40", "c68761f2-248c-4f39-6528-c308b1c0807c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(28727);
        internalCounters.push_back(28953);
        internalCounters.push_back(29179);
        internalCounters.push_back(29405);
        internalCounters.push_back(29631);
        internalCounters.push_back(29857);
        internalCounters.push_back(30083);
        internalCounters.push_back(30309);
        internalCounters.push_back(30535);
        internalCounters.push_back(30761);
        internalCounters.push_back(30987);
        internalCounters.push_back(31213);
        internalCounters.push_back(31439);
        internalCounters.push_back(31665);
        internalCounters.push_back(31891);
        internalCounters.push_back(32117);
        internalCounters.push_back(32343);
        internalCounters.push_back(32569);
        internalCounters.push_back(32795);
        internalCounters.push_back(33021);
        internalCounters.push_back(33247);
        internalCounters.push_back(33473);
        internalCounters.push_back(33699);
        internalCounters.push_back(33925);
        internalCounters.push_back(34151);
        internalCounters.push_back(34377);
        internalCounters.push_back(34603);
        internalCounters.push_back(34829);
        internalCounters.push_back(35055);
        internalCounters.push_back(35281);
        internalCounters.push_back(35507);
        internalCounters.push_back(35733);
        internalCounters.push_back(35959);
        internalCounters.push_back(36185);
        internalCounters.push_back(36411);
        internalCounters.push_back(36637);
        internalCounters.push_back(36863);
        internalCounters.push_back(37089);
        internalCounters.push_back(37315);
        internalCounters.push_back(37541);
        internalCounters.push_back(28726);
        internalCounters.push_back(28952);
        internalCounters.push_back(29178);
        internalCounters.push_back(29404);
        internalCounters.push_back(29630);
        internalCounters.push_back(29856);
        internalCounters.push_back(30082);
        internalCounters.push_back(30308);
        internalCounters.push_back(30534);
        internalCounters.push_back(30760);
        internalCounters.push_back(30986);
        internalCounters.push_back(31212);
        internalCounters.push_back(31438);
        internalCounters.push_back(31664);
        internalCounters.push_back(31890);
        internalCounters.push_back(32116);
        internalCounters.push_back(32342);
        internalCounters.push_back(32568);
        internalCounters.push_back(32794);
        internalCounters.push_back(33020);
        internalCounters.push_back(33246);
        internalCounters.push_back(33472);
        internalCounters.push_back(33698);
        internalCounters.push_back(33924);
        internalCounters.push_back(34150);
        internalCounters.push_back(34376);
        internalCounters.push_back(34602);
        internalCounters.push_back(34828);
        internalCounters.push_back(35054);
        internalCounters.push_back(35280);
        internalCounters.push_back(35506);
        internalCounters.push_back(35732);
        internalCounters.push_back(35958);
        internalCounters.push_back(36184);
        internalCounters.push_back(36410);
        internalCounters.push_back(36636);
        internalCounters.push_back(36862);
        internalCounters.push_back(37088);
        internalCounters.push_back(37314);
        internalCounters.push_back(37540);

        c.DefineDerivedCounter("TexTriFilteringPct", "TextureUnit", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,+,/,(100),*", "1affc3c8-b917-5c81-622b-7004527208ae");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(28727);
        internalCounters.push_back(28953);
        internalCounters.push_back(29179);
        internalCounters.push_back(29405);
        internalCounters.push_back(29631);
        internalCounters.push_back(29857);
        internalCounters.push_back(30083);
        internalCounters.push_back(30309);
        internalCounters.push_back(30535);
        internalCounters.push_back(30761);
        internalCounters.push_back(30987);
        internalCounters.push_back(31213);
        internalCounters.push_back(31439);
        internalCounters.push_back(31665);
        internalCounters.push_back(31891);
        internalCounters.push_back(32117);
        internalCounters.push_back(32343);
        internalCounters.push_back(32569);
        internalCounters.push_back(32795);
        internalCounters.push_back(33021);
        internalCounters.push_back(33247);
        internalCounters.push_back(33473);
        internalCounters.push_back(33699);
        internalCounters.push_back(33925);
        internalCounters.push_back(34151);
        internalCounters.push_back(34377);
        internalCounters.push_back(34603);
        internalCounters.push_back(34829);
        internalCounters.push_back(35055);
        internalCounters.push_back(35281);
        internalCounters.push_back(35507);
        internalCounters.push_back(35733);
        internalCounters.push_back(35959);
        internalCounters.push_back(36185);
        internalCounters.push_back(36411);
        internalCounters.push_back(36637);
        internalCounters.push_back(36863);
        internalCounters.push_back(37089);
        internalCounters.push_back(37315);
        internalCounters.push_back(37541);

        c.DefineDerivedCounter("TexTriFilteringCount", "TextureUnit", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40", "5785b3a1-a513-18db-4b1c-bdeef75bb2b6");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(28726);
        internalCounters.push_back(28952);
        internalCounters.push_back(29178);
        internalCounters.push_back(29404);
        internalCounters.push_back(29630);
        internalCounters.push_back(29856);
        internalCounters.push_back(30082);
        internalCounters.push_back(30308);
        internalCounters.push_back(30534);
        internalCounters.push_back(30760);
        internalCounters.push_back(30986);
        internalCounters.push_back(31212);
        internalCounters.push_back(31438);
        internalCounters.push_back(31664);
        internalCounters.push_back(31890);
        internalCounters.push_back(32116);
        internalCounters.push_back(32342);
        internalCounters.push_back(32568);
        internalCounters.push_back(32794);
        internalCounters.push_back(33020);
        internalCounters.push_back(33246);
        internalCounters.push_back(33472);
        internalCounters.push_back(33698);
        internalCounters.push_back(33924);
        internalCounters.push_back(34150);
        internalCounters.push_back(34376);
        internalCounters.push_back(34602);
        internalCounters.push_back(34828);
        internalCounters.push_back(35054);
        internalCounters.push_back(35280);
        internalCounters.push_back(35506);
        internalCounters.push_back(35732);
        internalCounters.push_back(35958);
        internalCounters.push_back(36184);
        internalCounters.push_back(36410);
        internalCounters.push_back(36636);
        internalCounters.push_back(36862);
        internalCounters.push_back(37088);
        internalCounters.push_back(37314);
        internalCounters.push_back(37540);

        c.DefineDerivedCounter("NoTexTriFilteringCount", "TextureUnit", "Count of pixels that did not receive trilinear filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40", "179da29a-81af-c06e-ce8c-a0a731ea030d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(28729);
        internalCounters.push_back(28955);
        internalCounters.push_back(29181);
        internalCounters.push_back(29407);
        internalCounters.push_back(29633);
        internalCounters.push_back(29859);
        internalCounters.push_back(30085);
        internalCounters.push_back(30311);
        internalCounters.push_back(30537);
        internalCounters.push_back(30763);
        internalCounters.push_back(30989);
        internalCounters.push_back(31215);
        internalCounters.push_back(31441);
        internalCounters.push_back(31667);
        internalCounters.push_back(31893);
        internalCounters.push_back(32119);
        internalCounters.push_back(32345);
        internalCounters.push_back(32571);
        internalCounters.push_back(32797);
        internalCounters.push_back(33023);
        internalCounters.push_back(33249);
        internalCounters.push_back(33475);
        internalCounters.push_back(33701);
        internalCounters.push_back(33927);
        internalCounters.push_back(34153);
        internalCounters.push_back(34379);
        internalCounters.push_back(34605);
        internalCounters.push_back(34831);
        internalCounters.push_back(35057);
        internalCounters.push_back(35283);
        internalCounters.push_back(35509);
        internalCounters.push_back(35735);
        internalCounters.push_back(35961);
        internalCounters.push_back(36187);
        internalCounters.push_back(36413);
        internalCounters.push_back(36639);
        internalCounters.push_back(36865);
        internalCounters.push_back(37091);
        internalCounters.push_back(37317);
        internalCounters.push_back(37543);
        internalCounters.push_back(28728);
        internalCounters.push_back(28954);
        internalCounters.push_back(29180);
        internalCounters.push_back(29406);
        internalCounters.push_back(29632);
        internalCounters.push_back(29858);
        internalCounters.push_back(30084);
        internalCounters.push_back(30310);
        internalCounters.push_back(30536);
        internalCounters.push_back(30762);
        internalCounters.push_back(30988);
        internalCounters.push_back(31214);
        internalCounters.push_back(31440);
        internalCounters.push_back(31666);
        internalCounters.push_back(31892);
        internalCounters.push_back(32118);
        internalCounters.push_back(32344);
        internalCounters.push_back(32570);
        internalCounters.push_back(32796);
        internalCounters.push_back(33022);
        internalCounters.push_back(33248);
        internalCounters.push_back(33474);
        internalCounters.push_back(33700);
        internalCounters.push_back(33926);
        internalCounters.push_back(34152);
        internalCounters.push_back(34378);
        internalCounters.push_back(34604);
        internalCounters.push_back(34830);
        internalCounters.push_back(35056);
        internalCounters.push_back(35282);
        internalCounters.push_back(35508);
        internalCounters.push_back(35734);
        internalCounters.push_back(35960);
        internalCounters.push_back(36186);
        internalCounters.push_back(36412);
        internalCounters.push_back(36638);
        internalCounters.push_back(36864);
        internalCounters.push_back(37090);
        internalCounters.push_back(37316);
        internalCounters.push_back(37542);

        c.DefineDerivedCounter("TexVolFilteringPct", "TextureUnit", "Percentage of pixels that received volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,+,/,(100),*", "b5ff6bed-3178-aee4-42dd-c74391c02a2d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(28729);
        internalCounters.push_back(28955);
        internalCounters.push_back(29181);
        internalCounters.push_back(29407);
        internalCounters.push_back(29633);
        internalCounters.push_back(29859);
        internalCounters.push_back(30085);
        internalCounters.push_back(30311);
        internalCounters.push_back(30537);
        internalCounters.push_back(30763);
        internalCounters.push_back(30989);
        internalCounters.push_back(31215);
        internalCounters.push_back(31441);
        internalCounters.push_back(31667);
        internalCounters.push_back(31893);
        internalCounters.push_back(32119);
        internalCounters.push_back(32345);
        internalCounters.push_back(32571);
        internalCounters.push_back(32797);
        internalCounters.push_back(33023);
        internalCounters.push_back(33249);
        internalCounters.push_back(33475);
        internalCounters.push_back(33701);
        internalCounters.push_back(33927);
        internalCounters.push_back(34153);
        internalCounters.push_back(34379);
        internalCounters.push_back(34605);
        internalCounters.push_back(34831);
        internalCounters.push_back(35057);
        internalCounters.push_back(35283);
        internalCounters.push_back(35509);
        internalCounters.push_back(35735);
        internalCounters.push_back(35961);
        internalCounters.push_back(36187);
        internalCounters.push_back(36413);
        internalCounters.push_back(36639);
        internalCounters.push_back(36865);
        internalCounters.push_back(37091);
        internalCounters.push_back(37317);
        internalCounters.push_back(37543);

        c.DefineDerivedCounter("TexVolFilteringCount", "TextureUnit", "Count of pixels that received volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40", "4bddc587-d589-8128-e18c-762eab2c871f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(28728);
        internalCounters.push_back(28954);
        internalCounters.push_back(29180);
        internalCounters.push_back(29406);
        internalCounters.push_back(29632);
        internalCounters.push_back(29858);
        internalCounters.push_back(30084);
        internalCounters.push_back(30310);
        internalCounters.push_back(30536);
        internalCounters.push_back(30762);
        internalCounters.push_back(30988);
        internalCounters.push_back(31214);
        internalCounters.push_back(31440);
        internalCounters.push_back(31666);
        internalCounters.push_back(31892);
        internalCounters.push_back(32118);
        internalCounters.push_back(32344);
        internalCounters.push_back(32570);
        internalCounters.push_back(32796);
        internalCounters.push_back(33022);
        internalCounters.push_back(33248);
        internalCounters.push_back(33474);
        internalCounters.push_back(33700);
        internalCounters.push_back(33926);
        internalCounters.push_back(34152);
        internalCounters.push_back(34378);
        internalCounters.push_back(34604);
        internalCounters.push_back(34830);
        internalCounters.push_back(35056);
        internalCounters.push_back(35282);
        internalCounters.push_back(35508);
        internalCounters.push_back(35734);
        internalCounters.push_back(35960);
        internalCounters.push_back(36186);
        internalCounters.push_back(36412);
        internalCounters.push_back(36638);
        internalCounters.push_back(36864);
        internalCounters.push_back(37090);
        internalCounters.push_back(37316);
        internalCounters.push_back(37542);

        c.DefineDerivedCounter("NoTexVolFilteringCount", "TextureUnit", "Count of pixels that did not receive volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40", "9fe1a854-17c6-9d26-b2b9-80610cd5827d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(28747);
        internalCounters.push_back(28973);
        internalCounters.push_back(29199);
        internalCounters.push_back(29425);
        internalCounters.push_back(29651);
        internalCounters.push_back(29877);
        internalCounters.push_back(30103);
        internalCounters.push_back(30329);
        internalCounters.push_back(30555);
        internalCounters.push_back(30781);
        internalCounters.push_back(31007);
        internalCounters.push_back(31233);
        internalCounters.push_back(31459);
        internalCounters.push_back(31685);
        internalCounters.push_back(31911);
        internalCounters.push_back(32137);
        internalCounters.push_back(32363);
        internalCounters.push_back(32589);
        internalCounters.push_back(32815);
        internalCounters.push_back(33041);
        internalCounters.push_back(33267);
        internalCounters.push_back(33493);
        internalCounters.push_back(33719);
        internalCounters.push_back(33945);
        internalCounters.push_back(34171);
        internalCounters.push_back(34397);
        internalCounters.push_back(34623);
        internalCounters.push_back(34849);
        internalCounters.push_back(35075);
        internalCounters.push_back(35301);
        internalCounters.push_back(35527);
        internalCounters.push_back(35753);
        internalCounters.push_back(35979);
        internalCounters.push_back(36205);
        internalCounters.push_back(36431);
        internalCounters.push_back(36657);
        internalCounters.push_back(36883);
        internalCounters.push_back(37109);
        internalCounters.push_back(37335);
        internalCounters.push_back(37561);
        internalCounters.push_back(28748);
        internalCounters.push_back(28974);
        internalCounters.push_back(29200);
        internalCounters.push_back(29426);
        internalCounters.push_back(29652);
        internalCounters.push_back(29878);
        internalCounters.push_back(30104);
        internalCounters.push_back(30330);
        internalCounters.push_back(30556);
        internalCounters.push_back(30782);
        internalCounters.push_back(31008);
        internalCounters.push_back(31234);
        internalCounters.push_back(31460);
        internalCounters.push_back(31686);
        internalCounters.push_back(31912);
        internalCounters.push_back(32138);
        internalCounters.push_back(32364);
        internalCounters.push_back(32590);
        internalCounters.push_back(32816);
        internalCounters.push_back(33042);
        internalCounters.push_back(33268);
        internalCounters.push_back(33494);
        internalCounters.push_back(33720);
        internalCounters.push_back(33946);
        internalCounters.push_back(34172);
        internalCounters.push_back(34398);
        internalCounters.push_back(34624);
        internalCounters.push_back(34850);
        internalCounters.push_back(35076);
        internalCounters.push_back(35302);
        internalCounters.push_back(35528);
        internalCounters.push_back(35754);
        internalCounters.push_back(35980);
        internalCounters.push_back(36206);
        internalCounters.push_back(36432);
        internalCounters.push_back(36658);
        internalCounters.push_back(36884);
        internalCounters.push_back(37110);
        internalCounters.push_back(37336);
        internalCounters.push_back(37562);
        internalCounters.push_back(28749);
        internalCounters.push_back(28975);
        internalCounters.push_back(29201);
        internalCounters.push_back(29427);
        internalCounters.push_back(29653);
        internalCounters.push_back(29879);
        internalCounters.push_back(30105);
        internalCounters.push_back(30331);
        internalCounters.push_back(30557);
        internalCounters.push_back(30783);
        internalCounters.push_back(31009);
        internalCounters.push_back(31235);
        internalCounters.push_back(31461);
        internalCounters.push_back(31687);
        internalCounters.push_back(31913);
        internalCounters.push_back(32139);
        internalCounters.push_back(32365);
        internalCounters.push_back(32591);
        internalCounters.push_back(32817);
        internalCounters.push_back(33043);
        internalCounters.push_back(33269);
        internalCounters.push_back(33495);
        internalCounters.push_back(33721);
        internalCounters.push_back(33947);
        internalCounters.push_back(34173);
        internalCounters.push_back(34399);
        internalCounters.push_back(34625);
        internalCounters.push_back(34851);
        internalCounters.push_back(35077);
        internalCounters.push_back(35303);
        internalCounters.push_back(35529);
        internalCounters.push_back(35755);
        internalCounters.push_back(35981);
        internalCounters.push_back(36207);
        internalCounters.push_back(36433);
        internalCounters.push_back(36659);
        internalCounters.push_back(36885);
        internalCounters.push_back(37111);
        internalCounters.push_back(37337);
        internalCounters.push_back(37563);
        internalCounters.push_back(28750);
        internalCounters.push_back(28976);
        internalCounters.push_back(29202);
        internalCounters.push_back(29428);
        internalCounters.push_back(29654);
        internalCounters.push_back(29880);
        internalCounters.push_back(30106);
        internalCounters.push_back(30332);
        internalCounters.push_back(30558);
        internalCounters.push_back(30784);
        internalCounters.push_back(31010);
        internalCounters.push_back(31236);
        internalCounters.push_back(31462);
        internalCounters.push_back(31688);
        internalCounters.push_back(31914);
        internalCounters.push_back(32140);
        internalCounters.push_back(32366);
        internalCounters.push_back(32592);
        internalCounters.push_back(32818);
        internalCounters.push_back(33044);
        internalCounters.push_back(33270);
        internalCounters.push_back(33496);
        internalCounters.push_back(33722);
        internalCounters.push_back(33948);
        internalCounters.push_back(34174);
        internalCounters.push_back(34400);
        internalCounters.push_back(34626);
        internalCounters.push_back(34852);
        internalCounters.push_back(35078);
        internalCounters.push_back(35304);
        internalCounters.push_back(35530);
        internalCounters.push_back(35756);
        internalCounters.push_back(35982);
        internalCounters.push_back(36208);
        internalCounters.push_back(36434);
        internalCounters.push_back(36660);
        internalCounters.push_back(36886);
        internalCounters.push_back(37112);
        internalCounters.push_back(37338);
        internalCounters.push_back(37564);
        internalCounters.push_back(28751);
        internalCounters.push_back(28977);
        internalCounters.push_back(29203);
        internalCounters.push_back(29429);
        internalCounters.push_back(29655);
        internalCounters.push_back(29881);
        internalCounters.push_back(30107);
        internalCounters.push_back(30333);
        internalCounters.push_back(30559);
        internalCounters.push_back(30785);
        internalCounters.push_back(31011);
        internalCounters.push_back(31237);
        internalCounters.push_back(31463);
        internalCounters.push_back(31689);
        internalCounters.push_back(31915);
        internalCounters.push_back(32141);
        internalCounters.push_back(32367);
        internalCounters.push_back(32593);
        internalCounters.push_back(32819);
        internalCounters.push_back(33045);
        internalCounters.push_back(33271);
        internalCounters.push_back(33497);
        internalCounters.push_back(33723);
        internalCounters.push_back(33949);
        internalCounters.push_back(34175);
        internalCounters.push_back(34401);
        internalCounters.push_back(34627);
        internalCounters.push_back(34853);
        internalCounters.push_back(35079);
        internalCounters.push_back(35305);
        internalCounters.push_back(35531);
        internalCounters.push_back(35757);
        internalCounters.push_back(35983);
        internalCounters.push_back(36209);
        internalCounters.push_back(36435);
        internalCounters.push_back(36661);
        internalCounters.push_back(36887);
        internalCounters.push_back(37113);
        internalCounters.push_back(37339);
        internalCounters.push_back(37565);
        internalCounters.push_back(28752);
        internalCounters.push_back(28978);
        internalCounters.push_back(29204);
        internalCounters.push_back(29430);
        internalCounters.push_back(29656);
        internalCounters.push_back(29882);
        internalCounters.push_back(30108);
        internalCounters.push_back(30334);
        internalCounters.push_back(30560);
        internalCounters.push_back(30786);
        internalCounters.push_back(31012);
        internalCounters.push_back(31238);
        internalCounters.push_back(31464);
        internalCounters.push_back(31690);
        internalCounters.push_back(31916);
        internalCounters.push_back(32142);
        internalCounters.push_back(32368);
        internalCounters.push_back(32594);
        internalCounters.push_back(32820);
        internalCounters.push_back(33046);
        internalCounters.push_back(33272);
        internalCounters.push_back(33498);
        internalCounters.push_back(33724);
        internalCounters.push_back(33950);
        internalCounters.push_back(34176);
        internalCounters.push_back(34402);
        internalCounters.push_back(34628);
        internalCounters.push_back(34854);
        internalCounters.push_back(35080);
        internalCounters.push_back(35306);
        internalCounters.push_back(35532);
        internalCounters.push_back(35758);
        internalCounters.push_back(35984);
        internalCounters.push_back(36210);
        internalCounters.push_back(36436);
        internalCounters.push_back(36662);
        internalCounters.push_back(36888);
        internalCounters.push_back(37114);
        internalCounters.push_back(37340);
        internalCounters.push_back(37566);
        internalCounters.push_back(28753);
        internalCounters.push_back(28979);
        internalCounters.push_back(29205);
        internalCounters.push_back(29431);
        internalCounters.push_back(29657);
        internalCounters.push_back(29883);
        internalCounters.push_back(30109);
        internalCounters.push_back(30335);
        internalCounters.push_back(30561);
        internalCounters.push_back(30787);
        internalCounters.push_back(31013);
        internalCounters.push_back(31239);
        internalCounters.push_back(31465);
        internalCounters.push_back(31691);
        internalCounters.push_back(31917);
        internalCounters.push_back(32143);
        internalCounters.push_back(32369);
        internalCounters.push_back(32595);
        internalCounters.push_back(32821);
        internalCounters.push_back(33047);
        internalCounters.push_back(33273);
        internalCounters.push_back(33499);
        internalCounters.push_back(33725);
        internalCounters.push_back(33951);
        internalCounters.push_back(34177);
        internalCounters.push_back(34403);
        internalCounters.push_back(34629);
        internalCounters.push_back(34855);
        internalCounters.push_back(35081);
        internalCounters.push_back(35307);
        internalCounters.push_back(35533);
        internalCounters.push_back(35759);
        internalCounters.push_back(35985);
        internalCounters.push_back(36211);
        internalCounters.push_back(36437);
        internalCounters.push_back(36663);
        internalCounters.push_back(36889);
        internalCounters.push_back(37115);
        internalCounters.push_back(37341);
        internalCounters.push_back(37567);
        internalCounters.push_back(28754);
        internalCounters.push_back(28980);
        internalCounters.push_back(29206);
        internalCounters.push_back(29432);
        internalCounters.push_back(29658);
        internalCounters.push_back(29884);
        internalCounters.push_back(30110);
        internalCounters.push_back(30336);
        internalCounters.push_back(30562);
        internalCounters.push_back(30788);
        internalCounters.push_back(31014);
        internalCounters.push_back(31240);
        internalCounters.push_back(31466);
        internalCounters.push_back(31692);
        internalCounters.push_back(31918);
        internalCounters.push_back(32144);
        internalCounters.push_back(32370);
        internalCounters.push_back(32596);
        internalCounters.push_back(32822);
        internalCounters.push_back(33048);
        internalCounters.push_back(33274);
        internalCounters.push_back(33500);
        internalCounters.push_back(33726);
        internalCounters.push_back(33952);
        internalCounters.push_back(34178);
        internalCounters.push_back(34404);
        internalCounters.push_back(34630);
        internalCounters.push_back(34856);
        internalCounters.push_back(35082);
        internalCounters.push_back(35308);
        internalCounters.push_back(35534);
        internalCounters.push_back(35760);
        internalCounters.push_back(35986);
        internalCounters.push_back(36212);
        internalCounters.push_back(36438);
        internalCounters.push_back(36664);
        internalCounters.push_back(36890);
        internalCounters.push_back(37116);
        internalCounters.push_back(37342);
        internalCounters.push_back(37568);
        internalCounters.push_back(28755);
        internalCounters.push_back(28981);
        internalCounters.push_back(29207);
        internalCounters.push_back(29433);
        internalCounters.push_back(29659);
        internalCounters.push_back(29885);
        internalCounters.push_back(30111);
        internalCounters.push_back(30337);
        internalCounters.push_back(30563);
        internalCounters.push_back(30789);
        internalCounters.push_back(31015);
        internalCounters.push_back(31241);
        internalCounters.push_back(31467);
        internalCounters.push_back(31693);
        internalCounters.push_back(31919);
        internalCounters.push_back(32145);
        internalCounters.push_back(32371);
        internalCounters.push_back(32597);
        internalCounters.push_back(32823);
        internalCounters.push_back(33049);
        internalCounters.push_back(33275);
        internalCounters.push_back(33501);
        internalCounters.push_back(33727);
        internalCounters.push_back(33953);
        internalCounters.push_back(34179);
        internalCounters.push_back(34405);
        internalCounters.push_back(34631);
        internalCounters.push_back(34857);
        internalCounters.push_back(35083);
        internalCounters.push_back(35309);
        internalCounters.push_back(35535);
        internalCounters.push_back(35761);
        internalCounters.push_back(35987);
        internalCounters.push_back(36213);
        internalCounters.push_back(36439);
        internalCounters.push_back(36665);
        internalCounters.push_back(36891);
        internalCounters.push_back(37117);
        internalCounters.push_back(37343);
        internalCounters.push_back(37569);

        c.DefineDerivedCounter("TexAveAnisotropy", "TextureUnit", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,(2),40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,*,+,(4),80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,sum40,*,+,(6),120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,sum40,*,+,(8),160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,sum40,*,+,(10),200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,sum40,*,+,(12),240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,sum40,*,+,(14),280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,sum40,*,+,(16),320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,sum40,*,+,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,+,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,sum40,+,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,sum40,+,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,sum40,+,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,sum40,+,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,sum40,+,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,sum40,+,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,sum40,+,/", "7ca2a2b9-a4eb-ce23-d163-59147e672396");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7560);
        internalCounters.push_back(7930);
        internalCounters.push_back(8300);
        internalCounters.push_back(8670);
        internalCounters.push_back(9040);
        internalCounters.push_back(9410);
        internalCounters.push_back(9780);
        internalCounters.push_back(10150);
        internalCounters.push_back(10520);
        internalCounters.push_back(10890);
        internalCounters.push_back(11260);
        internalCounters.push_back(11630);
        internalCounters.push_back(12000);
        internalCounters.push_back(12370);
        internalCounters.push_back(12740);
        internalCounters.push_back(13110);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("DepthStencilTestBusy", "Timing", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "6834fb52-42e8-bb50-fd48-ec2f2904e7e0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7560);
        internalCounters.push_back(7930);
        internalCounters.push_back(8300);
        internalCounters.push_back(8670);
        internalCounters.push_back(9040);
        internalCounters.push_back(9410);
        internalCounters.push_back(9780);
        internalCounters.push_back(10150);
        internalCounters.push_back(10520);
        internalCounters.push_back(10890);
        internalCounters.push_back(11260);
        internalCounters.push_back(11630);
        internalCounters.push_back(12000);
        internalCounters.push_back(12370);
        internalCounters.push_back(12740);
        internalCounters.push_back(13110);

        c.DefineDerivedCounter("DepthStencilTestBusyCount", "Timing", "Number of GPU cycles spent performing depth and stencil tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "e02860fa-c7bd-90ea-2149-69b4e98a636c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7431);
        internalCounters.push_back(7801);
        internalCounters.push_back(8171);
        internalCounters.push_back(8541);
        internalCounters.push_back(8911);
        internalCounters.push_back(9281);
        internalCounters.push_back(9651);
        internalCounters.push_back(10021);
        internalCounters.push_back(10391);
        internalCounters.push_back(10761);
        internalCounters.push_back(11131);
        internalCounters.push_back(11501);
        internalCounters.push_back(11871);
        internalCounters.push_back(12241);
        internalCounters.push_back(12611);
        internalCounters.push_back(12981);
        internalCounters.push_back(7420);
        internalCounters.push_back(7790);
        internalCounters.push_back(8160);
        internalCounters.push_back(8530);
        internalCounters.push_back(8900);
        internalCounters.push_back(9270);
        internalCounters.push_back(9640);
        internalCounters.push_back(10010);
        internalCounters.push_back(10380);
        internalCounters.push_back(10750);
        internalCounters.push_back(11120);
        internalCounters.push_back(11490);
        internalCounters.push_back(11860);
        internalCounters.push_back(12230);
        internalCounters.push_back(12600);
        internalCounters.push_back(12970);

        c.DefineDerivedCounter("HiZTilesAccepted", "DepthAndStencil", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*", "56176f45-d7ff-813d-4f05-3b2f046067e7");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7431);
        internalCounters.push_back(7801);
        internalCounters.push_back(8171);
        internalCounters.push_back(8541);
        internalCounters.push_back(8911);
        internalCounters.push_back(9281);
        internalCounters.push_back(9651);
        internalCounters.push_back(10021);
        internalCounters.push_back(10391);
        internalCounters.push_back(10761);
        internalCounters.push_back(11131);
        internalCounters.push_back(11501);
        internalCounters.push_back(11871);
        internalCounters.push_back(12241);
        internalCounters.push_back(12611);
        internalCounters.push_back(12981);

        c.DefineDerivedCounter("HiZTilesAcceptedCount", "DepthAndStencil", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "95d4e3f6-b2f0-f26e-8423-aacdfaf79ea3");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7420);
        internalCounters.push_back(7790);
        internalCounters.push_back(8160);
        internalCounters.push_back(8530);
        internalCounters.push_back(8900);
        internalCounters.push_back(9270);
        internalCounters.push_back(9640);
        internalCounters.push_back(10010);
        internalCounters.push_back(10380);
        internalCounters.push_back(10750);
        internalCounters.push_back(11120);
        internalCounters.push_back(11490);
        internalCounters.push_back(11860);
        internalCounters.push_back(12230);
        internalCounters.push_back(12600);
        internalCounters.push_back(12970);

        c.DefineDerivedCounter("HiZTilesRejectedCount", "DepthAndStencil", "Count of tiles not accepted by HiZ.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "156ba142-7eeb-aa6e-a00a-f8aea4e41e0b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7420);
        internalCounters.push_back(7790);
        internalCounters.push_back(8160);
        internalCounters.push_back(8530);
        internalCounters.push_back(8900);
        internalCounters.push_back(9270);
        internalCounters.push_back(9640);
        internalCounters.push_back(10010);
        internalCounters.push_back(10380);
        internalCounters.push_back(10750);
        internalCounters.push_back(11120);
        internalCounters.push_back(11490);
        internalCounters.push_back(11860);
        internalCounters.push_back(12230);
        internalCounters.push_back(12600);
        internalCounters.push_back(12970);
        internalCounters.push_back(7444);
        internalCounters.push_back(7814);
        internalCounters.push_back(8184);
        internalCounters.push_back(8554);
        internalCounters.push_back(8924);
        internalCounters.push_back(9294);
        internalCounters.push_back(9664);
        internalCounters.push_back(10034);
        internalCounters.push_back(10404);
        internalCounters.push_back(10774);
        internalCounters.push_back(11144);
        internalCounters.push_back(11514);
        internalCounters.push_back(11884);
        internalCounters.push_back(12254);
        internalCounters.push_back(12624);
        internalCounters.push_back(12994);

        c.DefineDerivedCounter("PreZTilesDetailCulled", "DepthAndStencil", "Percentage of tiles rejected because the associated prim had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*", "cad7f54d-a044-7574-c472-6f2065cbeeac");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7444);
        internalCounters.push_back(7814);
        internalCounters.push_back(8184);
        internalCounters.push_back(8554);
        internalCounters.push_back(8924);
        internalCounters.push_back(9294);
        internalCounters.push_back(9664);
        internalCounters.push_back(10034);
        internalCounters.push_back(10404);
        internalCounters.push_back(10774);
        internalCounters.push_back(11144);
        internalCounters.push_back(11514);
        internalCounters.push_back(11884);
        internalCounters.push_back(12254);
        internalCounters.push_back(12624);
        internalCounters.push_back(12994);

        c.DefineDerivedCounter("PreZTilesDetailCulledCount", "DepthAndStencil", "Count of tiles rejected because the associated primitive had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "49262c8a-b1e6-90dd-f096-0fc4921715e9");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7420);
        internalCounters.push_back(7790);
        internalCounters.push_back(8160);
        internalCounters.push_back(8530);
        internalCounters.push_back(8900);
        internalCounters.push_back(9270);
        internalCounters.push_back(9640);
        internalCounters.push_back(10010);
        internalCounters.push_back(10380);
        internalCounters.push_back(10750);
        internalCounters.push_back(11120);
        internalCounters.push_back(11490);
        internalCounters.push_back(11860);
        internalCounters.push_back(12230);
        internalCounters.push_back(12600);
        internalCounters.push_back(12970);

        c.DefineDerivedCounter("PreZTilesDetailSurvivingCount", "DepthAndStencil", "Count of tiles surviving because the associated primitive had contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "f803eaa4-bbed-bd39-775f-a64df92e2c08");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14651);
        internalCounters.push_back(15203);
        internalCounters.push_back(15755);
        internalCounters.push_back(16307);
        internalCounters.push_back(16859);
        internalCounters.push_back(17411);
        internalCounters.push_back(17963);
        internalCounters.push_back(18515);
        internalCounters.push_back(14652);
        internalCounters.push_back(15204);
        internalCounters.push_back(15756);
        internalCounters.push_back(16308);
        internalCounters.push_back(16860);
        internalCounters.push_back(17412);
        internalCounters.push_back(17964);
        internalCounters.push_back(18516);
        internalCounters.push_back(14653);
        internalCounters.push_back(15205);
        internalCounters.push_back(15757);
        internalCounters.push_back(16309);
        internalCounters.push_back(16861);
        internalCounters.push_back(17413);
        internalCounters.push_back(17965);
        internalCounters.push_back(18517);
        internalCounters.push_back(14654);
        internalCounters.push_back(15206);
        internalCounters.push_back(15758);
        internalCounters.push_back(16310);
        internalCounters.push_back(16862);
        internalCounters.push_back(17414);
        internalCounters.push_back(17966);
        internalCounters.push_back(18518);
        internalCounters.push_back(14727);
        internalCounters.push_back(15279);
        internalCounters.push_back(15831);
        internalCounters.push_back(16383);
        internalCounters.push_back(16935);
        internalCounters.push_back(17487);
        internalCounters.push_back(18039);
        internalCounters.push_back(18591);
        internalCounters.push_back(14728);
        internalCounters.push_back(15280);
        internalCounters.push_back(15832);
        internalCounters.push_back(16384);
        internalCounters.push_back(16936);
        internalCounters.push_back(17488);
        internalCounters.push_back(18040);
        internalCounters.push_back(18592);
        internalCounters.push_back(14729);
        internalCounters.push_back(15281);
        internalCounters.push_back(15833);
        internalCounters.push_back(16385);
        internalCounters.push_back(16937);
        internalCounters.push_back(17489);
        internalCounters.push_back(18041);
        internalCounters.push_back(18593);
        internalCounters.push_back(14730);
        internalCounters.push_back(15282);
        internalCounters.push_back(15834);
        internalCounters.push_back(16386);
        internalCounters.push_back(16938);
        internalCounters.push_back(17490);
        internalCounters.push_back(18042);
        internalCounters.push_back(18594);

        c.DefineDerivedCounter("HiZQuadsCulled", "DepthAndStencil", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum32,-,(0),max,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,/,(100),*", "fa0e319b-5573-6d34-5bab-904769925036");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14651);
        internalCounters.push_back(15203);
        internalCounters.push_back(15755);
        internalCounters.push_back(16307);
        internalCounters.push_back(16859);
        internalCounters.push_back(17411);
        internalCounters.push_back(17963);
        internalCounters.push_back(18515);
        internalCounters.push_back(14652);
        internalCounters.push_back(15204);
        internalCounters.push_back(15756);
        internalCounters.push_back(16308);
        internalCounters.push_back(16860);
        internalCounters.push_back(17412);
        internalCounters.push_back(17964);
        internalCounters.push_back(18516);
        internalCounters.push_back(14653);
        internalCounters.push_back(15205);
        internalCounters.push_back(15757);
        internalCounters.push_back(16309);
        internalCounters.push_back(16861);
        internalCounters.push_back(17413);
        internalCounters.push_back(17965);
        internalCounters.push_back(18517);
        internalCounters.push_back(14654);
        internalCounters.push_back(15206);
        internalCounters.push_back(15758);
        internalCounters.push_back(16310);
        internalCounters.push_back(16862);
        internalCounters.push_back(17414);
        internalCounters.push_back(17966);
        internalCounters.push_back(18518);
        internalCounters.push_back(14727);
        internalCounters.push_back(15279);
        internalCounters.push_back(15831);
        internalCounters.push_back(16383);
        internalCounters.push_back(16935);
        internalCounters.push_back(17487);
        internalCounters.push_back(18039);
        internalCounters.push_back(18591);
        internalCounters.push_back(14728);
        internalCounters.push_back(15280);
        internalCounters.push_back(15832);
        internalCounters.push_back(16384);
        internalCounters.push_back(16936);
        internalCounters.push_back(17488);
        internalCounters.push_back(18040);
        internalCounters.push_back(18592);
        internalCounters.push_back(14729);
        internalCounters.push_back(15281);
        internalCounters.push_back(15833);
        internalCounters.push_back(16385);
        internalCounters.push_back(16937);
        internalCounters.push_back(17489);
        internalCounters.push_back(18041);
        internalCounters.push_back(18593);
        internalCounters.push_back(14730);
        internalCounters.push_back(15282);
        internalCounters.push_back(15834);
        internalCounters.push_back(16386);
        internalCounters.push_back(16938);
        internalCounters.push_back(17490);
        internalCounters.push_back(18042);
        internalCounters.push_back(18594);

        c.DefineDerivedCounter("HiZQuadsCulledCount", "DepthAndStencil", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum32,-,(0),max", "73b0b39d-6df2-3e24-0b5c-7cb0ac8b6f39");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14727);
        internalCounters.push_back(15279);
        internalCounters.push_back(15831);
        internalCounters.push_back(16383);
        internalCounters.push_back(16935);
        internalCounters.push_back(17487);
        internalCounters.push_back(18039);
        internalCounters.push_back(18591);
        internalCounters.push_back(14728);
        internalCounters.push_back(15280);
        internalCounters.push_back(15832);
        internalCounters.push_back(16384);
        internalCounters.push_back(16936);
        internalCounters.push_back(17488);
        internalCounters.push_back(18040);
        internalCounters.push_back(18592);
        internalCounters.push_back(14729);
        internalCounters.push_back(15281);
        internalCounters.push_back(15833);
        internalCounters.push_back(16385);
        internalCounters.push_back(16937);
        internalCounters.push_back(17489);
        internalCounters.push_back(18041);
        internalCounters.push_back(18593);
        internalCounters.push_back(14730);
        internalCounters.push_back(15282);
        internalCounters.push_back(15834);
        internalCounters.push_back(16386);
        internalCounters.push_back(16938);
        internalCounters.push_back(17490);
        internalCounters.push_back(18042);
        internalCounters.push_back(18594);

        c.DefineDerivedCounter("HiZQuadsAcceptedCount", "DepthAndStencil", "Count of quads that did continue on in the pipeline after HiZ.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32", "59049ad9-42b5-c7cb-3616-6a8f6a8e4894");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14651);
        internalCounters.push_back(15203);
        internalCounters.push_back(15755);
        internalCounters.push_back(16307);
        internalCounters.push_back(16859);
        internalCounters.push_back(17411);
        internalCounters.push_back(17963);
        internalCounters.push_back(18515);
        internalCounters.push_back(14652);
        internalCounters.push_back(15204);
        internalCounters.push_back(15756);
        internalCounters.push_back(16308);
        internalCounters.push_back(16860);
        internalCounters.push_back(17412);
        internalCounters.push_back(17964);
        internalCounters.push_back(18516);
        internalCounters.push_back(14653);
        internalCounters.push_back(15205);
        internalCounters.push_back(15757);
        internalCounters.push_back(16309);
        internalCounters.push_back(16861);
        internalCounters.push_back(17413);
        internalCounters.push_back(17965);
        internalCounters.push_back(18517);
        internalCounters.push_back(14654);
        internalCounters.push_back(15206);
        internalCounters.push_back(15758);
        internalCounters.push_back(16310);
        internalCounters.push_back(16862);
        internalCounters.push_back(17414);
        internalCounters.push_back(17966);
        internalCounters.push_back(18518);
        internalCounters.push_back(14751);
        internalCounters.push_back(15303);
        internalCounters.push_back(15855);
        internalCounters.push_back(16407);
        internalCounters.push_back(16959);
        internalCounters.push_back(17511);
        internalCounters.push_back(18063);
        internalCounters.push_back(18615);
        internalCounters.push_back(14727);
        internalCounters.push_back(15279);
        internalCounters.push_back(15831);
        internalCounters.push_back(16383);
        internalCounters.push_back(16935);
        internalCounters.push_back(17487);
        internalCounters.push_back(18039);
        internalCounters.push_back(18591);
        internalCounters.push_back(14728);
        internalCounters.push_back(15280);
        internalCounters.push_back(15832);
        internalCounters.push_back(16384);
        internalCounters.push_back(16936);
        internalCounters.push_back(17488);
        internalCounters.push_back(18040);
        internalCounters.push_back(18592);
        internalCounters.push_back(14729);
        internalCounters.push_back(15281);
        internalCounters.push_back(15833);
        internalCounters.push_back(16385);
        internalCounters.push_back(16937);
        internalCounters.push_back(17489);
        internalCounters.push_back(18041);
        internalCounters.push_back(18593);
        internalCounters.push_back(14730);
        internalCounters.push_back(15282);
        internalCounters.push_back(15834);
        internalCounters.push_back(16386);
        internalCounters.push_back(16938);
        internalCounters.push_back(17490);
        internalCounters.push_back(18042);
        internalCounters.push_back(18594);

        c.DefineDerivedCounter("PreZQuadsCulled", "DepthAndStencil", "Percentage of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,sum32,32,33,34,35,36,37,38,39,sum8,-,(0),max,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,/,(100),*", "4e77547b-ec55-5663-f034-af59be66d77d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14651);
        internalCounters.push_back(15203);
        internalCounters.push_back(15755);
        internalCounters.push_back(16307);
        internalCounters.push_back(16859);
        internalCounters.push_back(17411);
        internalCounters.push_back(17963);
        internalCounters.push_back(18515);
        internalCounters.push_back(14652);
        internalCounters.push_back(15204);
        internalCounters.push_back(15756);
        internalCounters.push_back(16308);
        internalCounters.push_back(16860);
        internalCounters.push_back(17412);
        internalCounters.push_back(17964);
        internalCounters.push_back(18516);
        internalCounters.push_back(14653);
        internalCounters.push_back(15205);
        internalCounters.push_back(15757);
        internalCounters.push_back(16309);
        internalCounters.push_back(16861);
        internalCounters.push_back(17413);
        internalCounters.push_back(17965);
        internalCounters.push_back(18517);
        internalCounters.push_back(14654);
        internalCounters.push_back(15206);
        internalCounters.push_back(15758);
        internalCounters.push_back(16310);
        internalCounters.push_back(16862);
        internalCounters.push_back(17414);
        internalCounters.push_back(17966);
        internalCounters.push_back(18518);
        internalCounters.push_back(14751);
        internalCounters.push_back(15303);
        internalCounters.push_back(15855);
        internalCounters.push_back(16407);
        internalCounters.push_back(16959);
        internalCounters.push_back(17511);
        internalCounters.push_back(18063);
        internalCounters.push_back(18615);
        internalCounters.push_back(14727);
        internalCounters.push_back(15279);
        internalCounters.push_back(15831);
        internalCounters.push_back(16383);
        internalCounters.push_back(16935);
        internalCounters.push_back(17487);
        internalCounters.push_back(18039);
        internalCounters.push_back(18591);
        internalCounters.push_back(14728);
        internalCounters.push_back(15280);
        internalCounters.push_back(15832);
        internalCounters.push_back(16384);
        internalCounters.push_back(16936);
        internalCounters.push_back(17488);
        internalCounters.push_back(18040);
        internalCounters.push_back(18592);
        internalCounters.push_back(14729);
        internalCounters.push_back(15281);
        internalCounters.push_back(15833);
        internalCounters.push_back(16385);
        internalCounters.push_back(16937);
        internalCounters.push_back(17489);
        internalCounters.push_back(18041);
        internalCounters.push_back(18593);
        internalCounters.push_back(14730);
        internalCounters.push_back(15282);
        internalCounters.push_back(15834);
        internalCounters.push_back(16386);
        internalCounters.push_back(16938);
        internalCounters.push_back(17490);
        internalCounters.push_back(18042);
        internalCounters.push_back(18594);

        c.DefineDerivedCounter("PreZQuadsCulledCount", "DepthAndStencil", "Count of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,32,33,34,35,36,37,38,39,sum8,-,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,sum32,-,(0),max", "1bf169e6-9304-834e-df5f-0c44d7890a08");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14751);
        internalCounters.push_back(15303);
        internalCounters.push_back(15855);
        internalCounters.push_back(16407);
        internalCounters.push_back(16959);
        internalCounters.push_back(17511);
        internalCounters.push_back(18063);
        internalCounters.push_back(18615);
        internalCounters.push_back(14727);
        internalCounters.push_back(15279);
        internalCounters.push_back(15831);
        internalCounters.push_back(16383);
        internalCounters.push_back(16935);
        internalCounters.push_back(17487);
        internalCounters.push_back(18039);
        internalCounters.push_back(18591);
        internalCounters.push_back(14728);
        internalCounters.push_back(15280);
        internalCounters.push_back(15832);
        internalCounters.push_back(16384);
        internalCounters.push_back(16936);
        internalCounters.push_back(17488);
        internalCounters.push_back(18040);
        internalCounters.push_back(18592);
        internalCounters.push_back(14729);
        internalCounters.push_back(15281);
        internalCounters.push_back(15833);
        internalCounters.push_back(16385);
        internalCounters.push_back(16937);
        internalCounters.push_back(17489);
        internalCounters.push_back(18041);
        internalCounters.push_back(18593);
        internalCounters.push_back(14730);
        internalCounters.push_back(15282);
        internalCounters.push_back(15834);
        internalCounters.push_back(16386);
        internalCounters.push_back(16938);
        internalCounters.push_back(17490);
        internalCounters.push_back(18042);
        internalCounters.push_back(18594);

        c.DefineDerivedCounter("PreZQuadsSurvivingCount", "DepthAndStencil", "Count of quads surviving detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum32,0,1,2,3,4,5,6,7,sum8,-,(0),max", "50e25e51-3713-89cb-7f92-559cde5e5532");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14751);
        internalCounters.push_back(15303);
        internalCounters.push_back(15855);
        internalCounters.push_back(16407);
        internalCounters.push_back(16959);
        internalCounters.push_back(17511);
        internalCounters.push_back(18063);
        internalCounters.push_back(18615);
        internalCounters.push_back(14651);
        internalCounters.push_back(15203);
        internalCounters.push_back(15755);
        internalCounters.push_back(16307);
        internalCounters.push_back(16859);
        internalCounters.push_back(17411);
        internalCounters.push_back(17963);
        internalCounters.push_back(18515);
        internalCounters.push_back(14652);
        internalCounters.push_back(15204);
        internalCounters.push_back(15756);
        internalCounters.push_back(16308);
        internalCounters.push_back(16860);
        internalCounters.push_back(17412);
        internalCounters.push_back(17964);
        internalCounters.push_back(18516);
        internalCounters.push_back(14653);
        internalCounters.push_back(15205);
        internalCounters.push_back(15757);
        internalCounters.push_back(16309);
        internalCounters.push_back(16861);
        internalCounters.push_back(17413);
        internalCounters.push_back(17965);
        internalCounters.push_back(18517);
        internalCounters.push_back(14654);
        internalCounters.push_back(15206);
        internalCounters.push_back(15758);
        internalCounters.push_back(16310);
        internalCounters.push_back(16862);
        internalCounters.push_back(17414);
        internalCounters.push_back(17966);
        internalCounters.push_back(18518);

        c.DefineDerivedCounter("PostZQuads", "DepthAndStencil", "Percentage of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum32,/,(100),*", "58f0d34b-eeb8-e8db-abce-cb72584144be");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14751);
        internalCounters.push_back(15303);
        internalCounters.push_back(15855);
        internalCounters.push_back(16407);
        internalCounters.push_back(16959);
        internalCounters.push_back(17511);
        internalCounters.push_back(18063);
        internalCounters.push_back(18615);

        c.DefineDerivedCounter("PostZQuadCount", "DepthAndStencil", "Count of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,sum8", "08404526-ce35-939b-34c8-a7a35a0ff4d6");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7593);
        internalCounters.push_back(7963);
        internalCounters.push_back(8333);
        internalCounters.push_back(8703);
        internalCounters.push_back(9073);
        internalCounters.push_back(9443);
        internalCounters.push_back(9813);
        internalCounters.push_back(10183);
        internalCounters.push_back(10553);
        internalCounters.push_back(10923);
        internalCounters.push_back(11293);
        internalCounters.push_back(11663);
        internalCounters.push_back(12033);
        internalCounters.push_back(12403);
        internalCounters.push_back(12773);
        internalCounters.push_back(13143);

        c.DefineDerivedCounter("PreZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z before shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "3bfe6c4d-7422-ca03-7ea5-e67ff1a00136");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7595);
        internalCounters.push_back(7965);
        internalCounters.push_back(8335);
        internalCounters.push_back(8705);
        internalCounters.push_back(9075);
        internalCounters.push_back(9445);
        internalCounters.push_back(9815);
        internalCounters.push_back(10185);
        internalCounters.push_back(10555);
        internalCounters.push_back(10925);
        internalCounters.push_back(11295);
        internalCounters.push_back(11665);
        internalCounters.push_back(12035);
        internalCounters.push_back(12405);
        internalCounters.push_back(12775);
        internalCounters.push_back(13145);

        c.DefineDerivedCounter("PreZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z before shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "df7f705e-5162-d3b5-da8b-63466cf9c4e5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7594);
        internalCounters.push_back(7964);
        internalCounters.push_back(8334);
        internalCounters.push_back(8704);
        internalCounters.push_back(9074);
        internalCounters.push_back(9444);
        internalCounters.push_back(9814);
        internalCounters.push_back(10184);
        internalCounters.push_back(10554);
        internalCounters.push_back(10924);
        internalCounters.push_back(11294);
        internalCounters.push_back(11664);
        internalCounters.push_back(12034);
        internalCounters.push_back(12404);
        internalCounters.push_back(12774);
        internalCounters.push_back(13144);

        c.DefineDerivedCounter("PreZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z before shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "4484e950-f7a4-3800-bc74-78dd297f017e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7590);
        internalCounters.push_back(7960);
        internalCounters.push_back(8330);
        internalCounters.push_back(8700);
        internalCounters.push_back(9070);
        internalCounters.push_back(9440);
        internalCounters.push_back(9810);
        internalCounters.push_back(10180);
        internalCounters.push_back(10550);
        internalCounters.push_back(10920);
        internalCounters.push_back(11290);
        internalCounters.push_back(11660);
        internalCounters.push_back(12030);
        internalCounters.push_back(12400);
        internalCounters.push_back(12770);
        internalCounters.push_back(13140);

        c.DefineDerivedCounter("PostZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z after shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "4995d5d6-2330-b986-508b-fae24856f44c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7592);
        internalCounters.push_back(7962);
        internalCounters.push_back(8332);
        internalCounters.push_back(8702);
        internalCounters.push_back(9072);
        internalCounters.push_back(9442);
        internalCounters.push_back(9812);
        internalCounters.push_back(10182);
        internalCounters.push_back(10552);
        internalCounters.push_back(10922);
        internalCounters.push_back(11292);
        internalCounters.push_back(11662);
        internalCounters.push_back(12032);
        internalCounters.push_back(12402);
        internalCounters.push_back(12772);
        internalCounters.push_back(13142);

        c.DefineDerivedCounter("PostZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z after shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "ae558af4-f4be-3dd4-7316-b2c4dcf0def8");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7591);
        internalCounters.push_back(7961);
        internalCounters.push_back(8331);
        internalCounters.push_back(8701);
        internalCounters.push_back(9071);
        internalCounters.push_back(9441);
        internalCounters.push_back(9811);
        internalCounters.push_back(10181);
        internalCounters.push_back(10551);
        internalCounters.push_back(10921);
        internalCounters.push_back(11291);
        internalCounters.push_back(11661);
        internalCounters.push_back(12031);
        internalCounters.push_back(12401);
        internalCounters.push_back(12771);
        internalCounters.push_back(13141);

        c.DefineDerivedCounter("PostZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z after shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "b3684c94-814a-c695-c85d-a5b6ab798b35");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7462);
        internalCounters.push_back(7832);
        internalCounters.push_back(8202);
        internalCounters.push_back(8572);
        internalCounters.push_back(8942);
        internalCounters.push_back(9312);
        internalCounters.push_back(9682);
        internalCounters.push_back(10052);
        internalCounters.push_back(10422);
        internalCounters.push_back(10792);
        internalCounters.push_back(11162);
        internalCounters.push_back(11532);
        internalCounters.push_back(11902);
        internalCounters.push_back(12272);
        internalCounters.push_back(12642);
        internalCounters.push_back(13012);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("ZUnitStalled", "DepthAndStencil", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "5e86c3ad-1726-3157-1d01-7ed188bf854d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7462);
        internalCounters.push_back(7832);
        internalCounters.push_back(8202);
        internalCounters.push_back(8572);
        internalCounters.push_back(8942);
        internalCounters.push_back(9312);
        internalCounters.push_back(9682);
        internalCounters.push_back(10052);
        internalCounters.push_back(10422);
        internalCounters.push_back(10792);
        internalCounters.push_back(11162);
        internalCounters.push_back(11532);
        internalCounters.push_back(11902);
        internalCounters.push_back(12272);
        internalCounters.push_back(12642);
        internalCounters.push_back(13012);

        c.DefineDerivedCounter("ZUnitStalledCycles", "DepthAndStencil", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "4351fa7f-6737-2c3e-3ffb-b3addbdceedd");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7464);
        internalCounters.push_back(7834);
        internalCounters.push_back(8204);
        internalCounters.push_back(8574);
        internalCounters.push_back(8944);
        internalCounters.push_back(9314);
        internalCounters.push_back(9684);
        internalCounters.push_back(10054);
        internalCounters.push_back(10424);
        internalCounters.push_back(10794);
        internalCounters.push_back(11164);
        internalCounters.push_back(11534);
        internalCounters.push_back(11904);
        internalCounters.push_back(12274);
        internalCounters.push_back(12644);
        internalCounters.push_back(13014);
        internalCounters.push_back(7471);
        internalCounters.push_back(7841);
        internalCounters.push_back(8211);
        internalCounters.push_back(8581);
        internalCounters.push_back(8951);
        internalCounters.push_back(9321);
        internalCounters.push_back(9691);
        internalCounters.push_back(10061);
        internalCounters.push_back(10431);
        internalCounters.push_back(10801);
        internalCounters.push_back(11171);
        internalCounters.push_back(11541);
        internalCounters.push_back(11911);
        internalCounters.push_back(12281);
        internalCounters.push_back(12651);
        internalCounters.push_back(13021);

        c.DefineDerivedCounter("DBMemRead", "DepthAndStencil", "Number of bytes read from the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(256),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+", "dcdb4ee7-bd50-00f7-c028-9e5f4ce888c0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7476);
        internalCounters.push_back(7846);
        internalCounters.push_back(8216);
        internalCounters.push_back(8586);
        internalCounters.push_back(8956);
        internalCounters.push_back(9326);
        internalCounters.push_back(9696);
        internalCounters.push_back(10066);
        internalCounters.push_back(10436);
        internalCounters.push_back(10806);
        internalCounters.push_back(11176);
        internalCounters.push_back(11546);
        internalCounters.push_back(11916);
        internalCounters.push_back(12286);
        internalCounters.push_back(12656);
        internalCounters.push_back(13026);
        internalCounters.push_back(7479);
        internalCounters.push_back(7849);
        internalCounters.push_back(8219);
        internalCounters.push_back(8589);
        internalCounters.push_back(8959);
        internalCounters.push_back(9329);
        internalCounters.push_back(9699);
        internalCounters.push_back(10069);
        internalCounters.push_back(10439);
        internalCounters.push_back(10809);
        internalCounters.push_back(11179);
        internalCounters.push_back(11549);
        internalCounters.push_back(11919);
        internalCounters.push_back(12289);
        internalCounters.push_back(12659);
        internalCounters.push_back(13029);

        c.DefineDerivedCounter("DBMemWritten", "DepthAndStencil", "Number of bytes written to the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+", "de5717f8-8a49-ee44-4645-10de51b37dcf");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(168);
        internalCounters.push_back(629);
        internalCounters.push_back(1090);
        internalCounters.push_back(1551);
        internalCounters.push_back(2012);
        internalCounters.push_back(2473);
        internalCounters.push_back(2934);
        internalCounters.push_back(3395);
        internalCounters.push_back(3856);
        internalCounters.push_back(4317);
        internalCounters.push_back(4778);
        internalCounters.push_back(5239);
        internalCounters.push_back(5700);
        internalCounters.push_back(6161);
        internalCounters.push_back(6622);
        internalCounters.push_back(7083);

        c.DefineDerivedCounter("CBMemRead", "ColorBuffer", "Number of bytes read from the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "84b531d8-a1f8-7f49-7c27-7bc97801f1e6");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(299);
        internalCounters.push_back(760);
        internalCounters.push_back(1221);
        internalCounters.push_back(1682);
        internalCounters.push_back(2143);
        internalCounters.push_back(2604);
        internalCounters.push_back(3065);
        internalCounters.push_back(3526);
        internalCounters.push_back(3987);
        internalCounters.push_back(4448);
        internalCounters.push_back(4909);
        internalCounters.push_back(5370);
        internalCounters.push_back(5831);
        internalCounters.push_back(6292);
        internalCounters.push_back(6753);
        internalCounters.push_back(7214);
        internalCounters.push_back(166);
        internalCounters.push_back(627);
        internalCounters.push_back(1088);
        internalCounters.push_back(1549);
        internalCounters.push_back(2010);
        internalCounters.push_back(2471);
        internalCounters.push_back(2932);
        internalCounters.push_back(3393);
        internalCounters.push_back(3854);
        internalCounters.push_back(4315);
        internalCounters.push_back(4776);
        internalCounters.push_back(5237);
        internalCounters.push_back(5698);
        internalCounters.push_back(6159);
        internalCounters.push_back(6620);
        internalCounters.push_back(7081);
        internalCounters.push_back(167);
        internalCounters.push_back(628);
        internalCounters.push_back(1089);
        internalCounters.push_back(1550);
        internalCounters.push_back(2011);
        internalCounters.push_back(2472);
        internalCounters.push_back(2933);
        internalCounters.push_back(3394);
        internalCounters.push_back(3855);
        internalCounters.push_back(4316);
        internalCounters.push_back(4777);
        internalCounters.push_back(5238);
        internalCounters.push_back(5699);
        internalCounters.push_back(6160);
        internalCounters.push_back(6621);
        internalCounters.push_back(7082);
        internalCounters.push_back(168);
        internalCounters.push_back(629);
        internalCounters.push_back(1090);
        internalCounters.push_back(1551);
        internalCounters.push_back(2012);
        internalCounters.push_back(2473);
        internalCounters.push_back(2934);
        internalCounters.push_back(3395);
        internalCounters.push_back(3856);
        internalCounters.push_back(4317);
        internalCounters.push_back(4778);
        internalCounters.push_back(5239);
        internalCounters.push_back(5700);
        internalCounters.push_back(6161);
        internalCounters.push_back(6622);
        internalCounters.push_back(7083);

        c.DefineDerivedCounter("CBColorAndMaskRead", "ColorBuffer", "Total number of bytes read from the color and mask buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*", "da41660e-eb6f-32ec-8a64-b32ca17bd7eb");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(158);
        internalCounters.push_back(619);
        internalCounters.push_back(1080);
        internalCounters.push_back(1541);
        internalCounters.push_back(2002);
        internalCounters.push_back(2463);
        internalCounters.push_back(2924);
        internalCounters.push_back(3385);
        internalCounters.push_back(3846);
        internalCounters.push_back(4307);
        internalCounters.push_back(4768);
        internalCounters.push_back(5229);
        internalCounters.push_back(5690);
        internalCounters.push_back(6151);
        internalCounters.push_back(6612);
        internalCounters.push_back(7073);

        c.DefineDerivedCounter("CBMemWritten", "ColorBuffer", "Number of bytes written to the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "550f8ff8-60b6-a6bf-87d0-25ac9e87de70");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(297);
        internalCounters.push_back(758);
        internalCounters.push_back(1219);
        internalCounters.push_back(1680);
        internalCounters.push_back(2141);
        internalCounters.push_back(2602);
        internalCounters.push_back(3063);
        internalCounters.push_back(3524);
        internalCounters.push_back(3985);
        internalCounters.push_back(4446);
        internalCounters.push_back(4907);
        internalCounters.push_back(5368);
        internalCounters.push_back(5829);
        internalCounters.push_back(6290);
        internalCounters.push_back(6751);
        internalCounters.push_back(7212);
        internalCounters.push_back(156);
        internalCounters.push_back(617);
        internalCounters.push_back(1078);
        internalCounters.push_back(1539);
        internalCounters.push_back(2000);
        internalCounters.push_back(2461);
        internalCounters.push_back(2922);
        internalCounters.push_back(3383);
        internalCounters.push_back(3844);
        internalCounters.push_back(4305);
        internalCounters.push_back(4766);
        internalCounters.push_back(5227);
        internalCounters.push_back(5688);
        internalCounters.push_back(6149);
        internalCounters.push_back(6610);
        internalCounters.push_back(7071);
        internalCounters.push_back(157);
        internalCounters.push_back(618);
        internalCounters.push_back(1079);
        internalCounters.push_back(1540);
        internalCounters.push_back(2001);
        internalCounters.push_back(2462);
        internalCounters.push_back(2923);
        internalCounters.push_back(3384);
        internalCounters.push_back(3845);
        internalCounters.push_back(4306);
        internalCounters.push_back(4767);
        internalCounters.push_back(5228);
        internalCounters.push_back(5689);
        internalCounters.push_back(6150);
        internalCounters.push_back(6611);
        internalCounters.push_back(7072);
        internalCounters.push_back(158);
        internalCounters.push_back(619);
        internalCounters.push_back(1080);
        internalCounters.push_back(1541);
        internalCounters.push_back(2002);
        internalCounters.push_back(2463);
        internalCounters.push_back(2924);
        internalCounters.push_back(3385);
        internalCounters.push_back(3846);
        internalCounters.push_back(4307);
        internalCounters.push_back(4768);
        internalCounters.push_back(5229);
        internalCounters.push_back(5690);
        internalCounters.push_back(6151);
        internalCounters.push_back(6612);
        internalCounters.push_back(7073);

        c.DefineDerivedCounter("CBColorAndMaskWritten", "ColorBuffer", "Total number of bytes written to the color and mask buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*", "29a04b69-8f5f-b770-a0f2-3453e2c99e49");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(202);
        internalCounters.push_back(663);
        internalCounters.push_back(1124);
        internalCounters.push_back(1585);
        internalCounters.push_back(2046);
        internalCounters.push_back(2507);
        internalCounters.push_back(2968);
        internalCounters.push_back(3429);
        internalCounters.push_back(3890);
        internalCounters.push_back(4351);
        internalCounters.push_back(4812);
        internalCounters.push_back(5273);
        internalCounters.push_back(5734);
        internalCounters.push_back(6195);
        internalCounters.push_back(6656);
        internalCounters.push_back(7117);
        internalCounters.push_back(47);
        internalCounters.push_back(508);
        internalCounters.push_back(969);
        internalCounters.push_back(1430);
        internalCounters.push_back(1891);
        internalCounters.push_back(2352);
        internalCounters.push_back(2813);
        internalCounters.push_back(3274);
        internalCounters.push_back(3735);
        internalCounters.push_back(4196);
        internalCounters.push_back(4657);
        internalCounters.push_back(5118);
        internalCounters.push_back(5579);
        internalCounters.push_back(6040);
        internalCounters.push_back(6501);
        internalCounters.push_back(6962);

        c.DefineDerivedCounter("CBSlowPixelPct", "ColorBuffer", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*,(100),min", "5775943f-0313-7e52-9638-b24a449197bc");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(202);
        internalCounters.push_back(663);
        internalCounters.push_back(1124);
        internalCounters.push_back(1585);
        internalCounters.push_back(2046);
        internalCounters.push_back(2507);
        internalCounters.push_back(2968);
        internalCounters.push_back(3429);
        internalCounters.push_back(3890);
        internalCounters.push_back(4351);
        internalCounters.push_back(4812);
        internalCounters.push_back(5273);
        internalCounters.push_back(5734);
        internalCounters.push_back(6195);
        internalCounters.push_back(6656);
        internalCounters.push_back(7117);

        c.DefineDerivedCounter("CBSlowPixelCount", "ColorBuffer", "Number of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "47eacbb0-28c8-22b4-5c69-c00d5813bb1c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(40147);
        internalCounters.push_back(40224);
        internalCounters.push_back(40301);
        internalCounters.push_back(40378);
        internalCounters.push_back(40455);
        internalCounters.push_back(40532);
        internalCounters.push_back(40609);
        internalCounters.push_back(40686);
        internalCounters.push_back(40763);
        internalCounters.push_back(40840);
        internalCounters.push_back(40917);
        internalCounters.push_back(40994);
        internalCounters.push_back(41071);
        internalCounters.push_back(41148);
        internalCounters.push_back(41225);
        internalCounters.push_back(41302);
        internalCounters.push_back(41379);
        internalCounters.push_back(41456);
        internalCounters.push_back(41533);
        internalCounters.push_back(41610);
        internalCounters.push_back(41687);
        internalCounters.push_back(41764);
        internalCounters.push_back(41841);
        internalCounters.push_back(41918);
        internalCounters.push_back(41995);
        internalCounters.push_back(42072);
        internalCounters.push_back(42149);
        internalCounters.push_back(42226);
        internalCounters.push_back(42303);
        internalCounters.push_back(42380);
        internalCounters.push_back(42457);
        internalCounters.push_back(42534);
        internalCounters.push_back(42611);
        internalCounters.push_back(42688);
        internalCounters.push_back(42765);
        internalCounters.push_back(42842);
        internalCounters.push_back(42919);
        internalCounters.push_back(42996);
        internalCounters.push_back(43073);
        internalCounters.push_back(43150);
        internalCounters.push_back(40156);
        internalCounters.push_back(40233);
        internalCounters.push_back(40310);
        internalCounters.push_back(40387);
        internalCounters.push_back(40464);
        internalCounters.push_back(40541);
        internalCounters.push_back(40618);
        internalCounters.push_back(40695);
        internalCounters.push_back(40772);
        internalCounters.push_back(40849);
        internalCounters.push_back(40926);
        internalCounters.push_back(41003);
        internalCounters.push_back(41080);
        internalCounters.push_back(41157);
        internalCounters.push_back(41234);
        internalCounters.push_back(41311);
        internalCounters.push_back(41388);
        internalCounters.push_back(41465);
        internalCounters.push_back(41542);
        internalCounters.push_back(41619);
        internalCounters.push_back(41696);
        internalCounters.push_back(41773);
        internalCounters.push_back(41850);
        internalCounters.push_back(41927);
        internalCounters.push_back(42004);
        internalCounters.push_back(42081);
        internalCounters.push_back(42158);
        internalCounters.push_back(42235);
        internalCounters.push_back(42312);
        internalCounters.push_back(42389);
        internalCounters.push_back(42466);
        internalCounters.push_back(42543);
        internalCounters.push_back(42620);
        internalCounters.push_back(42697);
        internalCounters.push_back(42774);
        internalCounters.push_back(42851);
        internalCounters.push_back(42928);
        internalCounters.push_back(43005);
        internalCounters.push_back(43082);
        internalCounters.push_back(43159);

        c.DefineDerivedCounter("L0CacheHit", "MemoryCache", "The percentage of read requests that hit the data in the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,ifnotzero", "286c786e-9a42-3371-9dea-dd54e6e612e9");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(40147);
        internalCounters.push_back(40224);
        internalCounters.push_back(40301);
        internalCounters.push_back(40378);
        internalCounters.push_back(40455);
        internalCounters.push_back(40532);
        internalCounters.push_back(40609);
        internalCounters.push_back(40686);
        internalCounters.push_back(40763);
        internalCounters.push_back(40840);
        internalCounters.push_back(40917);
        internalCounters.push_back(40994);
        internalCounters.push_back(41071);
        internalCounters.push_back(41148);
        internalCounters.push_back(41225);
        internalCounters.push_back(41302);
        internalCounters.push_back(41379);
        internalCounters.push_back(41456);
        internalCounters.push_back(41533);
        internalCounters.push_back(41610);
        internalCounters.push_back(41687);
        internalCounters.push_back(41764);
        internalCounters.push_back(41841);
        internalCounters.push_back(41918);
        internalCounters.push_back(41995);
        internalCounters.push_back(42072);
        internalCounters.push_back(42149);
        internalCounters.push_back(42226);
        internalCounters.push_back(42303);
        internalCounters.push_back(42380);
        internalCounters.push_back(42457);
        internalCounters.push_back(42534);
        internalCounters.push_back(42611);
        internalCounters.push_back(42688);
        internalCounters.push_back(42765);
        internalCounters.push_back(42842);
        internalCounters.push_back(42919);
        internalCounters.push_back(42996);
        internalCounters.push_back(43073);
        internalCounters.push_back(43150);

        c.DefineDerivedCounter("L0CacheRequestCount", "MemoryCache", "The number of read requests made to the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40", "74983cae-ee57-2e1b-d990-5128fef84e1f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(40147);
        internalCounters.push_back(40224);
        internalCounters.push_back(40301);
        internalCounters.push_back(40378);
        internalCounters.push_back(40455);
        internalCounters.push_back(40532);
        internalCounters.push_back(40609);
        internalCounters.push_back(40686);
        internalCounters.push_back(40763);
        internalCounters.push_back(40840);
        internalCounters.push_back(40917);
        internalCounters.push_back(40994);
        internalCounters.push_back(41071);
        internalCounters.push_back(41148);
        internalCounters.push_back(41225);
        internalCounters.push_back(41302);
        internalCounters.push_back(41379);
        internalCounters.push_back(41456);
        internalCounters.push_back(41533);
        internalCounters.push_back(41610);
        internalCounters.push_back(41687);
        internalCounters.push_back(41764);
        internalCounters.push_back(41841);
        internalCounters.push_back(41918);
        internalCounters.push_back(41995);
        internalCounters.push_back(42072);
        internalCounters.push_back(42149);
        internalCounters.push_back(42226);
        internalCounters.push_back(42303);
        internalCounters.push_back(42380);
        internalCounters.push_back(42457);
        internalCounters.push_back(42534);
        internalCounters.push_back(42611);
        internalCounters.push_back(42688);
        internalCounters.push_back(42765);
        internalCounters.push_back(42842);
        internalCounters.push_back(42919);
        internalCounters.push_back(42996);
        internalCounters.push_back(43073);
        internalCounters.push_back(43150);
        internalCounters.push_back(40156);
        internalCounters.push_back(40233);
        internalCounters.push_back(40310);
        internalCounters.push_back(40387);
        internalCounters.push_back(40464);
        internalCounters.push_back(40541);
        internalCounters.push_back(40618);
        internalCounters.push_back(40695);
        internalCounters.push_back(40772);
        internalCounters.push_back(40849);
        internalCounters.push_back(40926);
        internalCounters.push_back(41003);
        internalCounters.push_back(41080);
        internalCounters.push_back(41157);
        internalCounters.push_back(41234);
        internalCounters.push_back(41311);
        internalCounters.push_back(41388);
        internalCounters.push_back(41465);
        internalCounters.push_back(41542);
        internalCounters.push_back(41619);
        internalCounters.push_back(41696);
        internalCounters.push_back(41773);
        internalCounters.push_back(41850);
        internalCounters.push_back(41927);
        internalCounters.push_back(42004);
        internalCounters.push_back(42081);
        internalCounters.push_back(42158);
        internalCounters.push_back(42235);
        internalCounters.push_back(42312);
        internalCounters.push_back(42389);
        internalCounters.push_back(42466);
        internalCounters.push_back(42543);
        internalCounters.push_back(42620);
        internalCounters.push_back(42697);
        internalCounters.push_back(42774);
        internalCounters.push_back(42851);
        internalCounters.push_back(42928);
        internalCounters.push_back(43005);
        internalCounters.push_back(43082);
        internalCounters.push_back(43159);

        c.DefineDerivedCounter("L0CacheHitCount", "MemoryCache", "The number of read requests which result in a cache hit from the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,-", "c0de7338-069b-c5ba-ead3-c65e030cd2ac");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(40156);
        internalCounters.push_back(40233);
        internalCounters.push_back(40310);
        internalCounters.push_back(40387);
        internalCounters.push_back(40464);
        internalCounters.push_back(40541);
        internalCounters.push_back(40618);
        internalCounters.push_back(40695);
        internalCounters.push_back(40772);
        internalCounters.push_back(40849);
        internalCounters.push_back(40926);
        internalCounters.push_back(41003);
        internalCounters.push_back(41080);
        internalCounters.push_back(41157);
        internalCounters.push_back(41234);
        internalCounters.push_back(41311);
        internalCounters.push_back(41388);
        internalCounters.push_back(41465);
        internalCounters.push_back(41542);
        internalCounters.push_back(41619);
        internalCounters.push_back(41696);
        internalCounters.push_back(41773);
        internalCounters.push_back(41850);
        internalCounters.push_back(41927);
        internalCounters.push_back(42004);
        internalCounters.push_back(42081);
        internalCounters.push_back(42158);
        internalCounters.push_back(42235);
        internalCounters.push_back(42312);
        internalCounters.push_back(42389);
        internalCounters.push_back(42466);
        internalCounters.push_back(42543);
        internalCounters.push_back(42620);
        internalCounters.push_back(42697);
        internalCounters.push_back(42774);
        internalCounters.push_back(42851);
        internalCounters.push_back(42928);
        internalCounters.push_back(43005);
        internalCounters.push_back(43082);
        internalCounters.push_back(43159);

        c.DefineDerivedCounter("L0CacheMissCount", "MemoryCache", "The number of read requests which result in a cache miss from the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40", "a2f08766-ea1b-6eae-6eaf-faa04125d3e6");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(50073);
        internalCounters.push_back(50137);
        internalCounters.push_back(50201);
        internalCounters.push_back(50265);
        internalCounters.push_back(50329);
        internalCounters.push_back(50393);
        internalCounters.push_back(50457);
        internalCounters.push_back(50521);
        internalCounters.push_back(50585);
        internalCounters.push_back(50649);
        internalCounters.push_back(50713);
        internalCounters.push_back(50777);
        internalCounters.push_back(50841);
        internalCounters.push_back(50905);
        internalCounters.push_back(50969);
        internalCounters.push_back(51033);
        internalCounters.push_back(50077);
        internalCounters.push_back(50141);
        internalCounters.push_back(50205);
        internalCounters.push_back(50269);
        internalCounters.push_back(50333);
        internalCounters.push_back(50397);
        internalCounters.push_back(50461);
        internalCounters.push_back(50525);
        internalCounters.push_back(50589);
        internalCounters.push_back(50653);
        internalCounters.push_back(50717);
        internalCounters.push_back(50781);
        internalCounters.push_back(50845);
        internalCounters.push_back(50909);
        internalCounters.push_back(50973);
        internalCounters.push_back(51037);

        c.DefineDerivedCounter("L1CacheHit", "MemoryCache", "The percentage of read or write requests that hit the data in the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "5a34915a-24b8-8baf-2bf8-5878e7894ae3");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(50073);
        internalCounters.push_back(50137);
        internalCounters.push_back(50201);
        internalCounters.push_back(50265);
        internalCounters.push_back(50329);
        internalCounters.push_back(50393);
        internalCounters.push_back(50457);
        internalCounters.push_back(50521);
        internalCounters.push_back(50585);
        internalCounters.push_back(50649);
        internalCounters.push_back(50713);
        internalCounters.push_back(50777);
        internalCounters.push_back(50841);
        internalCounters.push_back(50905);
        internalCounters.push_back(50969);
        internalCounters.push_back(51033);

        c.DefineDerivedCounter("L1CacheRequestCount", "MemoryCache", "The number of read or write requests made to the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "29c76c67-4611-205d-0b88-d08668df03c5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(50073);
        internalCounters.push_back(50137);
        internalCounters.push_back(50201);
        internalCounters.push_back(50265);
        internalCounters.push_back(50329);
        internalCounters.push_back(50393);
        internalCounters.push_back(50457);
        internalCounters.push_back(50521);
        internalCounters.push_back(50585);
        internalCounters.push_back(50649);
        internalCounters.push_back(50713);
        internalCounters.push_back(50777);
        internalCounters.push_back(50841);
        internalCounters.push_back(50905);
        internalCounters.push_back(50969);
        internalCounters.push_back(51033);
        internalCounters.push_back(50077);
        internalCounters.push_back(50141);
        internalCounters.push_back(50205);
        internalCounters.push_back(50269);
        internalCounters.push_back(50333);
        internalCounters.push_back(50397);
        internalCounters.push_back(50461);
        internalCounters.push_back(50525);
        internalCounters.push_back(50589);
        internalCounters.push_back(50653);
        internalCounters.push_back(50717);
        internalCounters.push_back(50781);
        internalCounters.push_back(50845);
        internalCounters.push_back(50909);
        internalCounters.push_back(50973);
        internalCounters.push_back(51037);

        c.DefineDerivedCounter("L1CacheHitCount", "MemoryCache", "The number of read or write requests which result in a cache hit from the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-", "1ae150c3-f2d0-82c6-a51b-a77fd8d5fc33");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(50077);
        internalCounters.push_back(50141);
        internalCounters.push_back(50205);
        internalCounters.push_back(50269);
        internalCounters.push_back(50333);
        internalCounters.push_back(50397);
        internalCounters.push_back(50461);
        internalCounters.push_back(50525);
        internalCounters.push_back(50589);
        internalCounters.push_back(50653);
        internalCounters.push_back(50717);
        internalCounters.push_back(50781);
        internalCounters.push_back(50845);
        internalCounters.push_back(50909);
        internalCounters.push_back(50973);
        internalCounters.push_back(51037);

        c.DefineDerivedCounter("L1CacheMissCount", "MemoryCache", "The number of read or write requests which result in a cache miss from the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "71bfec6d-257b-849d-e212-cdf5c1b1de65");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52058);
        internalCounters.push_back(52293);
        internalCounters.push_back(52528);
        internalCounters.push_back(52763);
        internalCounters.push_back(52998);
        internalCounters.push_back(53233);
        internalCounters.push_back(53468);
        internalCounters.push_back(53703);
        internalCounters.push_back(53938);
        internalCounters.push_back(54173);
        internalCounters.push_back(54408);
        internalCounters.push_back(54643);
        internalCounters.push_back(54878);
        internalCounters.push_back(55113);
        internalCounters.push_back(55348);
        internalCounters.push_back(55583);
        internalCounters.push_back(52090);
        internalCounters.push_back(52325);
        internalCounters.push_back(52560);
        internalCounters.push_back(52795);
        internalCounters.push_back(53030);
        internalCounters.push_back(53265);
        internalCounters.push_back(53500);
        internalCounters.push_back(53735);
        internalCounters.push_back(53970);
        internalCounters.push_back(54205);
        internalCounters.push_back(54440);
        internalCounters.push_back(54675);
        internalCounters.push_back(54910);
        internalCounters.push_back(55145);
        internalCounters.push_back(55380);
        internalCounters.push_back(55615);

        c.DefineDerivedCounter("L2CacheHit", "MemoryCache", "The percentage of read or write requests that hit the data in the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "47694e4d-6ce6-f387-080d-b1f3d00b73ac");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52090);
        internalCounters.push_back(52325);
        internalCounters.push_back(52560);
        internalCounters.push_back(52795);
        internalCounters.push_back(53030);
        internalCounters.push_back(53265);
        internalCounters.push_back(53500);
        internalCounters.push_back(53735);
        internalCounters.push_back(53970);
        internalCounters.push_back(54205);
        internalCounters.push_back(54440);
        internalCounters.push_back(54675);
        internalCounters.push_back(54910);
        internalCounters.push_back(55145);
        internalCounters.push_back(55380);
        internalCounters.push_back(55615);
        internalCounters.push_back(52058);
        internalCounters.push_back(52293);
        internalCounters.push_back(52528);
        internalCounters.push_back(52763);
        internalCounters.push_back(52998);
        internalCounters.push_back(53233);
        internalCounters.push_back(53468);
        internalCounters.push_back(53703);
        internalCounters.push_back(53938);
        internalCounters.push_back(54173);
        internalCounters.push_back(54408);
        internalCounters.push_back(54643);
        internalCounters.push_back(54878);
        internalCounters.push_back(55113);
        internalCounters.push_back(55348);
        internalCounters.push_back(55583);

        c.DefineDerivedCounter("L2CacheMiss", "MemoryCache", "The percentage of read or write requests that miss the data in the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size. Value range: 0% (optimal) to 100% (all miss).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*", "8aee5458-a58e-11b6-5131-7f19ed070117");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52058);
        internalCounters.push_back(52293);
        internalCounters.push_back(52528);
        internalCounters.push_back(52763);
        internalCounters.push_back(52998);
        internalCounters.push_back(53233);
        internalCounters.push_back(53468);
        internalCounters.push_back(53703);
        internalCounters.push_back(53938);
        internalCounters.push_back(54173);
        internalCounters.push_back(54408);
        internalCounters.push_back(54643);
        internalCounters.push_back(54878);
        internalCounters.push_back(55113);
        internalCounters.push_back(55348);
        internalCounters.push_back(55583);

        c.DefineDerivedCounter("L2CacheRequestCount", "MemoryCache", "The number of read or write requests made to the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "21e9219c-e725-0d96-06b1-b21698b736b2");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52058);
        internalCounters.push_back(52293);
        internalCounters.push_back(52528);
        internalCounters.push_back(52763);
        internalCounters.push_back(52998);
        internalCounters.push_back(53233);
        internalCounters.push_back(53468);
        internalCounters.push_back(53703);
        internalCounters.push_back(53938);
        internalCounters.push_back(54173);
        internalCounters.push_back(54408);
        internalCounters.push_back(54643);
        internalCounters.push_back(54878);
        internalCounters.push_back(55113);
        internalCounters.push_back(55348);
        internalCounters.push_back(55583);
        internalCounters.push_back(52090);
        internalCounters.push_back(52325);
        internalCounters.push_back(52560);
        internalCounters.push_back(52795);
        internalCounters.push_back(53030);
        internalCounters.push_back(53265);
        internalCounters.push_back(53500);
        internalCounters.push_back(53735);
        internalCounters.push_back(53970);
        internalCounters.push_back(54205);
        internalCounters.push_back(54440);
        internalCounters.push_back(54675);
        internalCounters.push_back(54910);
        internalCounters.push_back(55145);
        internalCounters.push_back(55380);
        internalCounters.push_back(55615);

        c.DefineDerivedCounter("L2CacheHitCount", "MemoryCache", "The number of read or write requests which result in a cache hit from the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-", "29ddcb92-d3dd-951b-1b23-efe52e4eeee4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52090);
        internalCounters.push_back(52325);
        internalCounters.push_back(52560);
        internalCounters.push_back(52795);
        internalCounters.push_back(53030);
        internalCounters.push_back(53265);
        internalCounters.push_back(53500);
        internalCounters.push_back(53735);
        internalCounters.push_back(53970);
        internalCounters.push_back(54205);
        internalCounters.push_back(54440);
        internalCounters.push_back(54675);
        internalCounters.push_back(54910);
        internalCounters.push_back(55145);
        internalCounters.push_back(55380);
        internalCounters.push_back(55615);

        c.DefineDerivedCounter("L2CacheMissCount", "MemoryCache", "The number of read or write requests which result in a cache miss from the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "376eec7b-ab25-9012-06b5-63291a17fd47");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52144);
        internalCounters.push_back(52379);
        internalCounters.push_back(52614);
        internalCounters.push_back(52849);
        internalCounters.push_back(53084);
        internalCounters.push_back(53319);
        internalCounters.push_back(53554);
        internalCounters.push_back(53789);
        internalCounters.push_back(54024);
        internalCounters.push_back(54259);
        internalCounters.push_back(54494);
        internalCounters.push_back(54729);
        internalCounters.push_back(54964);
        internalCounters.push_back(55199);
        internalCounters.push_back(55434);
        internalCounters.push_back(55669);
        internalCounters.push_back(52145);
        internalCounters.push_back(52380);
        internalCounters.push_back(52615);
        internalCounters.push_back(52850);
        internalCounters.push_back(53085);
        internalCounters.push_back(53320);
        internalCounters.push_back(53555);
        internalCounters.push_back(53790);
        internalCounters.push_back(54025);
        internalCounters.push_back(54260);
        internalCounters.push_back(54495);
        internalCounters.push_back(54730);
        internalCounters.push_back(54965);
        internalCounters.push_back(55200);
        internalCounters.push_back(55435);
        internalCounters.push_back(55670);
        internalCounters.push_back(52146);
        internalCounters.push_back(52381);
        internalCounters.push_back(52616);
        internalCounters.push_back(52851);
        internalCounters.push_back(53086);
        internalCounters.push_back(53321);
        internalCounters.push_back(53556);
        internalCounters.push_back(53791);
        internalCounters.push_back(54026);
        internalCounters.push_back(54261);
        internalCounters.push_back(54496);
        internalCounters.push_back(54731);
        internalCounters.push_back(54966);
        internalCounters.push_back(55201);
        internalCounters.push_back(55436);
        internalCounters.push_back(55671);
        internalCounters.push_back(52147);
        internalCounters.push_back(52382);
        internalCounters.push_back(52617);
        internalCounters.push_back(52852);
        internalCounters.push_back(53087);
        internalCounters.push_back(53322);
        internalCounters.push_back(53557);
        internalCounters.push_back(53792);
        internalCounters.push_back(54027);
        internalCounters.push_back(54262);
        internalCounters.push_back(54497);
        internalCounters.push_back(54732);
        internalCounters.push_back(54967);
        internalCounters.push_back(55202);
        internalCounters.push_back(55437);
        internalCounters.push_back(55672);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total bytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,(96),*,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,(128),*,sum4", "664bb3ef-6eca-86b1-1e2d-30cb897b5fa9");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52130);
        internalCounters.push_back(52365);
        internalCounters.push_back(52600);
        internalCounters.push_back(52835);
        internalCounters.push_back(53070);
        internalCounters.push_back(53305);
        internalCounters.push_back(53540);
        internalCounters.push_back(53775);
        internalCounters.push_back(54010);
        internalCounters.push_back(54245);
        internalCounters.push_back(54480);
        internalCounters.push_back(54715);
        internalCounters.push_back(54950);
        internalCounters.push_back(55185);
        internalCounters.push_back(55420);
        internalCounters.push_back(55655);
        internalCounters.push_back(52131);
        internalCounters.push_back(52366);
        internalCounters.push_back(52601);
        internalCounters.push_back(52836);
        internalCounters.push_back(53071);
        internalCounters.push_back(53306);
        internalCounters.push_back(53541);
        internalCounters.push_back(53776);
        internalCounters.push_back(54011);
        internalCounters.push_back(54246);
        internalCounters.push_back(54481);
        internalCounters.push_back(54716);
        internalCounters.push_back(54951);
        internalCounters.push_back(55186);
        internalCounters.push_back(55421);
        internalCounters.push_back(55656);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total bytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+", "f96f2c16-b1b4-4ec4-229c-fc82e6f80a82");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(28673);
        internalCounters.push_back(28899);
        internalCounters.push_back(29125);
        internalCounters.push_back(29351);
        internalCounters.push_back(29577);
        internalCounters.push_back(29803);
        internalCounters.push_back(30029);
        internalCounters.push_back(30255);
        internalCounters.push_back(30481);
        internalCounters.push_back(30707);
        internalCounters.push_back(30933);
        internalCounters.push_back(31159);
        internalCounters.push_back(31385);
        internalCounters.push_back(31611);
        internalCounters.push_back(31837);
        internalCounters.push_back(32063);
        internalCounters.push_back(32289);
        internalCounters.push_back(32515);
        internalCounters.push_back(32741);
        internalCounters.push_back(32967);
        internalCounters.push_back(33193);
        internalCounters.push_back(33419);
        internalCounters.push_back(33645);
        internalCounters.push_back(33871);
        internalCounters.push_back(34097);
        internalCounters.push_back(34323);
        internalCounters.push_back(34549);
        internalCounters.push_back(34775);
        internalCounters.push_back(35001);
        internalCounters.push_back(35227);
        internalCounters.push_back(35453);
        internalCounters.push_back(35679);
        internalCounters.push_back(35905);
        internalCounters.push_back(36131);
        internalCounters.push_back(36357);
        internalCounters.push_back(36583);
        internalCounters.push_back(36809);
        internalCounters.push_back(37035);
        internalCounters.push_back(37261);
        internalCounters.push_back(37487);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(28673);
        internalCounters.push_back(28899);
        internalCounters.push_back(29125);
        internalCounters.push_back(29351);
        internalCounters.push_back(29577);
        internalCounters.push_back(29803);
        internalCounters.push_back(30029);
        internalCounters.push_back(30255);
        internalCounters.push_back(30481);
        internalCounters.push_back(30707);
        internalCounters.push_back(30933);
        internalCounters.push_back(31159);
        internalCounters.push_back(31385);
        internalCounters.push_back(31611);
        internalCounters.push_back(31837);
        internalCounters.push_back(32063);
        internalCounters.push_back(32289);
        internalCounters.push_back(32515);
        internalCounters.push_back(32741);
        internalCounters.push_back(32967);
        internalCounters.push_back(33193);
        internalCounters.push_back(33419);
        internalCounters.push_back(33645);
        internalCounters.push_back(33871);
        internalCounters.push_back(34097);
        internalCounters.push_back(34323);
        internalCounters.push_back(34549);
        internalCounters.push_back(34775);
        internalCounters.push_back(35001);
        internalCounters.push_back(35227);
        internalCounters.push_back(35453);
        internalCounters.push_back(35679);
        internalCounters.push_back(35905);
        internalCounters.push_back(36131);
        internalCounters.push_back(36357);
        internalCounters.push_back(36583);
        internalCounters.push_back(36809);
        internalCounters.push_back(37035);
        internalCounters.push_back(37261);
        internalCounters.push_back(37487);

        c.DefineDerivedCounter("MemUnitBusyCycles", "GlobalMemory", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalledCycles). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40", "168f077c-4797-b2f5-717f-105c725266c8");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(40174);
        internalCounters.push_back(40251);
        internalCounters.push_back(40328);
        internalCounters.push_back(40405);
        internalCounters.push_back(40482);
        internalCounters.push_back(40559);
        internalCounters.push_back(40636);
        internalCounters.push_back(40713);
        internalCounters.push_back(40790);
        internalCounters.push_back(40867);
        internalCounters.push_back(40944);
        internalCounters.push_back(41021);
        internalCounters.push_back(41098);
        internalCounters.push_back(41175);
        internalCounters.push_back(41252);
        internalCounters.push_back(41329);
        internalCounters.push_back(41406);
        internalCounters.push_back(41483);
        internalCounters.push_back(41560);
        internalCounters.push_back(41637);
        internalCounters.push_back(41714);
        internalCounters.push_back(41791);
        internalCounters.push_back(41868);
        internalCounters.push_back(41945);
        internalCounters.push_back(42022);
        internalCounters.push_back(42099);
        internalCounters.push_back(42176);
        internalCounters.push_back(42253);
        internalCounters.push_back(42330);
        internalCounters.push_back(42407);
        internalCounters.push_back(42484);
        internalCounters.push_back(42561);
        internalCounters.push_back(42638);
        internalCounters.push_back(42715);
        internalCounters.push_back(42792);
        internalCounters.push_back(42869);
        internalCounters.push_back(42946);
        internalCounters.push_back(43023);
        internalCounters.push_back(43100);
        internalCounters.push_back(43177);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(40174);
        internalCounters.push_back(40251);
        internalCounters.push_back(40328);
        internalCounters.push_back(40405);
        internalCounters.push_back(40482);
        internalCounters.push_back(40559);
        internalCounters.push_back(40636);
        internalCounters.push_back(40713);
        internalCounters.push_back(40790);
        internalCounters.push_back(40867);
        internalCounters.push_back(40944);
        internalCounters.push_back(41021);
        internalCounters.push_back(41098);
        internalCounters.push_back(41175);
        internalCounters.push_back(41252);
        internalCounters.push_back(41329);
        internalCounters.push_back(41406);
        internalCounters.push_back(41483);
        internalCounters.push_back(41560);
        internalCounters.push_back(41637);
        internalCounters.push_back(41714);
        internalCounters.push_back(41791);
        internalCounters.push_back(41868);
        internalCounters.push_back(41945);
        internalCounters.push_back(42022);
        internalCounters.push_back(42099);
        internalCounters.push_back(42176);
        internalCounters.push_back(42253);
        internalCounters.push_back(42330);
        internalCounters.push_back(42407);
        internalCounters.push_back(42484);
        internalCounters.push_back(42561);
        internalCounters.push_back(42638);
        internalCounters.push_back(42715);
        internalCounters.push_back(42792);
        internalCounters.push_back(42869);
        internalCounters.push_back(42946);
        internalCounters.push_back(43023);
        internalCounters.push_back(43100);
        internalCounters.push_back(43177);

        c.DefineDerivedCounter("MemUnitStalledCycles", "GlobalMemory", "Number of GPU cycles the memory unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40", "2745659a-0e40-bace-3b9b-86a54f8e4623");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52134);
        internalCounters.push_back(52369);
        internalCounters.push_back(52604);
        internalCounters.push_back(52839);
        internalCounters.push_back(53074);
        internalCounters.push_back(53309);
        internalCounters.push_back(53544);
        internalCounters.push_back(53779);
        internalCounters.push_back(54014);
        internalCounters.push_back(54249);
        internalCounters.push_back(54484);
        internalCounters.push_back(54719);
        internalCounters.push_back(54954);
        internalCounters.push_back(55189);
        internalCounters.push_back(55424);
        internalCounters.push_back(55659);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52134);
        internalCounters.push_back(52369);
        internalCounters.push_back(52604);
        internalCounters.push_back(52839);
        internalCounters.push_back(53074);
        internalCounters.push_back(53309);
        internalCounters.push_back(53544);
        internalCounters.push_back(53779);
        internalCounters.push_back(54014);
        internalCounters.push_back(54249);
        internalCounters.push_back(54484);
        internalCounters.push_back(54719);
        internalCounters.push_back(54954);
        internalCounters.push_back(55189);
        internalCounters.push_back(55424);
        internalCounters.push_back(55659);

        c.DefineDerivedCounter("WriteUnitStalledCycles", "GlobalMemory", "Number of GPU cycles the Write unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "ede3305e-abd4-d6bf-6b00-ffc57a29fce3");
    }
}

