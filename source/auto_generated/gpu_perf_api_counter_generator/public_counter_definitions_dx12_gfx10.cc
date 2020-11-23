//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions for DX12 GFX10 
//==============================================================================

#include "gpa_counter.h"
#include "public_counter_definitions_dx12_gfx10.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersDX12_Gfx10(GPA_DerivedCounters& c)
{
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(59893);

        c.DefineDerivedCounter("GPUTime", "Timing", "Time this API command took to execute on the GPU in nanoseconds from the time the previous command reached the bottom of the pipeline (BOP) to the time this command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "0,TS_FREQ,/,(1000000000),*", "cbd338f2-de6c-7b14-92ad-ba724ca2e501");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(59896);

        c.DefineDerivedCounter("ExecutionDuration", "Timing", "GPU command execution duration in nanoseconds, from the time the command enters the top of the pipeline (TOP) to the time the command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "0,TS_FREQ,/,(1000000000),*", "b2f08d0d-af13-cd66-d3b4-b290ad448e69");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(59897);

        c.DefineDerivedCounter("ExecutionStart", "Timing", "GPU command execution start time in nanoseconds. This is the time the command enters the top of the pipeline (TOP).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "0,TS_FREQ,/,(1000000000),*", "a368f79d-fcfe-2158-71c4-2f0c4eef5aa4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(59898);

        c.DefineDerivedCounter("ExecutionEnd", "Timing", "GPU command execution end time in nanoseconds. This is the time the command reaches the bottom of the pipeline (BOP).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "0,TS_FREQ,/,(1000000000),*", "0bce206a-0976-06a2-bf20-03fb351035a8");
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
        internalCounters.push_back(5828);
        internalCounters.push_back(6157);
        internalCounters.push_back(5840);
        internalCounters.push_back(6169);
        internalCounters.push_back(5521);
        internalCounters.push_back(5850);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("VSBusy", "Timing", "The percentage of time the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,2,2,ifnotzero,4,4,ifnotzero,1,3,3,ifnotzero,5,5,ifnotzero,max,6,/,(100),*,(100),min", "94caad5e-867c-6c09-cf3a-d05b51df8f3b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5828);
        internalCounters.push_back(6157);
        internalCounters.push_back(5840);
        internalCounters.push_back(6169);
        internalCounters.push_back(5521);
        internalCounters.push_back(5850);

        c.DefineDerivedCounter("VSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,2,2,ifnotzero,4,4,ifnotzero,1,3,3,ifnotzero,5,5,ifnotzero,max", "a2086d4e-274b-48a8-3e08-a4ab76ac15dd");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(59893);
        internalCounters.push_back(5828);
        internalCounters.push_back(6157);
        internalCounters.push_back(5840);
        internalCounters.push_back(6169);
        internalCounters.push_back(5521);
        internalCounters.push_back(5850);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("VSTime", "Timing", "Time vertex shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "1,3,3,ifnotzero,5,5,ifnotzero,2,4,4,ifnotzero,6,6,ifnotzero,max,7,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "d6ce819e-69af-a241-d07a-5dd8d146e436");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5554);
        internalCounters.push_back(5883);
        internalCounters.push_back(5561);
        internalCounters.push_back(5890);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("HSBusy", "Timing", "The percentage of time the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,2,ifnotzero,(0),1,3,ifnotzero,max,4,/,(100),*,(100),min", "16f30a0b-4cbf-eccd-b13f-ab68dd254d32");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5554);
        internalCounters.push_back(5883);
        internalCounters.push_back(5561);
        internalCounters.push_back(5890);

        c.DefineDerivedCounter("HSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,2,ifnotzero,(0),1,3,ifnotzero,max", "753e76ef-8ef8-3f13-b511-4bd9f3589fdb");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(59893);
        internalCounters.push_back(5554);
        internalCounters.push_back(5883);
        internalCounters.push_back(5561);
        internalCounters.push_back(5890);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("HSTime", "Timing", "Time hull shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,3,ifnotzero,(0),2,4,ifnotzero,max,5,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "8386a863-dd34-1526-f703-0f0c7b241bc4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5521);
        internalCounters.push_back(5850);
        internalCounters.push_back(5828);
        internalCounters.push_back(6157);
        internalCounters.push_back(5834);
        internalCounters.push_back(6163);
        internalCounters.push_back(5846);
        internalCounters.push_back(6175);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("DSBusy", "Timing", "The percentage of time the ShaderUnit has domain shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,2,4,ifnotzero,6,ifnotzero,(0),1,3,5,ifnotzero,7,ifnotzero,max,8,/,(100),*,(100),min", "0c626e8a-9b82-b6d4-d9a3-578509316301");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5521);
        internalCounters.push_back(5850);
        internalCounters.push_back(5828);
        internalCounters.push_back(6157);
        internalCounters.push_back(5834);
        internalCounters.push_back(6163);
        internalCounters.push_back(5846);
        internalCounters.push_back(6175);

        c.DefineDerivedCounter("DSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has domain shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,2,4,ifnotzero,6,ifnotzero,(0),1,3,5,ifnotzero,7,ifnotzero,max", "2f3f7561-0549-2232-536d-129ffc5f7703");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(59893);
        internalCounters.push_back(5521);
        internalCounters.push_back(5850);
        internalCounters.push_back(5828);
        internalCounters.push_back(6157);
        internalCounters.push_back(5834);
        internalCounters.push_back(6163);
        internalCounters.push_back(5846);
        internalCounters.push_back(6175);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("DSTime", "Timing", "Time domain shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,3,5,ifnotzero,7,ifnotzero,(0),2,4,6,ifnotzero,8,ifnotzero,max,9,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "bfe28947-c727-8a9f-aa59-c218e58bfba5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5580);
        internalCounters.push_back(5909);
        internalCounters.push_back(5600);
        internalCounters.push_back(5929);
        internalCounters.push_back(5581);
        internalCounters.push_back(5910);
        internalCounters.push_back(5601);
        internalCounters.push_back(5930);
        internalCounters.push_back(5582);
        internalCounters.push_back(5911);
        internalCounters.push_back(5602);
        internalCounters.push_back(5931);
        internalCounters.push_back(5583);
        internalCounters.push_back(5912);
        internalCounters.push_back(5603);
        internalCounters.push_back(5932);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("PSBusy", "Timing", "The percentage of time the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,2,ifnotzero,(0),1,3,ifnotzero,max,(0),4,6,ifnotzero,(0),5,7,ifnotzero,max,(0),8,10,ifnotzero,(0),9,11,ifnotzero,max,(0),12,14,ifnotzero,(0),13,15,ifnotzero,max,max4,16,/,(100),*,(100),min", "7e772beb-d82c-bd9a-aed0-fe504d416ce5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5580);
        internalCounters.push_back(5909);
        internalCounters.push_back(5600);
        internalCounters.push_back(5929);
        internalCounters.push_back(5581);
        internalCounters.push_back(5910);
        internalCounters.push_back(5601);
        internalCounters.push_back(5930);
        internalCounters.push_back(5582);
        internalCounters.push_back(5911);
        internalCounters.push_back(5602);
        internalCounters.push_back(5931);
        internalCounters.push_back(5583);
        internalCounters.push_back(5912);
        internalCounters.push_back(5603);
        internalCounters.push_back(5932);

        c.DefineDerivedCounter("PSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,2,ifnotzero,(0),1,3,ifnotzero,max,(0),4,6,ifnotzero,(0),5,7,ifnotzero,max,(0),8,10,ifnotzero,(0),9,11,ifnotzero,max,(0),12,14,ifnotzero,(0),13,15,ifnotzero,max,max4", "b58bea04-ce8e-2984-80f4-8aba7d4c817b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(59893);
        internalCounters.push_back(5580);
        internalCounters.push_back(5909);
        internalCounters.push_back(5600);
        internalCounters.push_back(5929);
        internalCounters.push_back(5581);
        internalCounters.push_back(5910);
        internalCounters.push_back(5601);
        internalCounters.push_back(5930);
        internalCounters.push_back(5582);
        internalCounters.push_back(5911);
        internalCounters.push_back(5602);
        internalCounters.push_back(5931);
        internalCounters.push_back(5583);
        internalCounters.push_back(5912);
        internalCounters.push_back(5603);
        internalCounters.push_back(5932);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("PSTime", "Timing", "Time pixel shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "(0),1,3,ifnotzero,(0),2,4,ifnotzero,max,(0),5,7,ifnotzero,(0),6,8,ifnotzero,max,(0),9,11,ifnotzero,(0),10,12,ifnotzero,max,(0),13,15,ifnotzero,(0),14,16,ifnotzero,max,max4,17,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "edca7694-7416-e8a6-0c5a-63a5ad5f3d74");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5565);
        internalCounters.push_back(5894);
        internalCounters.push_back(5569);
        internalCounters.push_back(5898);
        internalCounters.push_back(5571);
        internalCounters.push_back(5900);
        internalCounters.push_back(5575);
        internalCounters.push_back(5904);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("CSBusy", "Timing", "The percentage of time the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,comparemax2,4,5,6,7,comparemax2,max,8,/,(100),*,(100),min", "493fdd90-8d2b-a055-5e4e-2d29c3396b8c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5565);
        internalCounters.push_back(5894);
        internalCounters.push_back(5569);
        internalCounters.push_back(5898);
        internalCounters.push_back(5571);
        internalCounters.push_back(5900);
        internalCounters.push_back(5575);
        internalCounters.push_back(5904);

        c.DefineDerivedCounter("CSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,comparemax2,4,5,6,7,comparemax2,max", "39bcf1b8-f6b2-4c37-f9af-0a2bb59512f9");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(59893);
        internalCounters.push_back(5565);
        internalCounters.push_back(5894);
        internalCounters.push_back(5569);
        internalCounters.push_back(5898);
        internalCounters.push_back(5571);
        internalCounters.push_back(5900);
        internalCounters.push_back(5575);
        internalCounters.push_back(5904);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("CSTime", "Timing", "Time compute shaders are busy in nanoseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_NANOSECONDS, internalCounters, "1,2,3,4,comparemax2,5,6,7,8,comparemax2,max,9,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "dbc24916-ecb2-7eef-8d63-7afadaaab6bc");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(50355);
        internalCounters.push_back(50377);
        internalCounters.push_back(50419);

        c.DefineDerivedCounter("VSVerticesIn", "VertexShader", "The number of vertices processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero", "810a04c8-2ff4-081d-766d-bfa2bd4ad916");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7266);
        internalCounters.push_back(7778);
        internalCounters.push_back(7206);
        internalCounters.push_back(7718);
        internalCounters.push_back(11362);
        internalCounters.push_back(11874);
        internalCounters.push_back(11302);
        internalCounters.push_back(11814);
        internalCounters.push_back(9314);
        internalCounters.push_back(9826);
        internalCounters.push_back(9254);
        internalCounters.push_back(9766);

        c.DefineDerivedCounter("VSVALUInstCount", "VertexShader", "Average number of vector ALU instructions executed in the VS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,sum2,6,7,sum2,/,6,7,sum2,ifnotzero,8,9,sum2,10,11,sum2,/,10,11,sum2,ifnotzero", "8ec604e4-63f5-e6b5-4558-c38f0b26d4b1");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7266);
        internalCounters.push_back(7778);
        internalCounters.push_back(7206);
        internalCounters.push_back(7718);
        internalCounters.push_back(11362);
        internalCounters.push_back(11874);
        internalCounters.push_back(11302);
        internalCounters.push_back(11814);
        internalCounters.push_back(9314);
        internalCounters.push_back(9826);
        internalCounters.push_back(9254);
        internalCounters.push_back(9766);

        c.DefineDerivedCounter("VSSALUInstCount", "VertexShader", "Average number of scalar ALU instructions executed in the VS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,sum2,6,7,sum2,/,6,7,sum2,ifnotzero,8,9,sum2,10,11,sum2,/,10,11,sum2,ifnotzero", "e3da0383-7322-7f65-8cf2-3ce641578e54");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7319);
        internalCounters.push_back(7831);
        internalCounters.push_back(11415);
        internalCounters.push_back(11927);
        internalCounters.push_back(9367);
        internalCounters.push_back(9879);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("VSVALUBusy", "VertexShader", "The percentage of GPUTime vector ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,sum2,2,3,sum2,2,3,sum2,ifnotzero,4,5,sum2,4,5,sum2,ifnotzero,NUM_SIMDS,/,6,/,(100),*", "8b3572f7-fda0-eddf-6c93-2ab145b8754b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7319);
        internalCounters.push_back(7831);
        internalCounters.push_back(11415);
        internalCounters.push_back(11927);
        internalCounters.push_back(9367);
        internalCounters.push_back(9879);

        c.DefineDerivedCounter("VSVALUBusyCycles", "VertexShader", "Number of GPU cycles where vector ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,sum2,2,3,sum2,2,3,sum2,ifnotzero,4,5,sum2,4,5,sum2,ifnotzero", "0af1686e-6d77-2f6e-2862-7bb8e869a776");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7262);
        internalCounters.push_back(7774);
        internalCounters.push_back(11358);
        internalCounters.push_back(11870);
        internalCounters.push_back(9310);
        internalCounters.push_back(9822);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("VSSALUBusy", "VertexShader", "The percentage of GPUTime scalar ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,sum2,2,3,sum2,2,3,sum2,ifnotzero,4,5,sum2,4,5,sum2,ifnotzero,NUM_CUS,/,6,/,(100),*", "3bc8730c-e3bc-e2f0-7d24-36974064c25a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(7262);
        internalCounters.push_back(7774);
        internalCounters.push_back(11358);
        internalCounters.push_back(11870);
        internalCounters.push_back(9310);
        internalCounters.push_back(9822);

        c.DefineDerivedCounter("VSSALUBusyCycles", "VertexShader", "Number of GPU cycles where scalar ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,sum2,2,3,sum2,2,3,sum2,ifnotzero,4,5,sum2,4,5,sum2,ifnotzero,NUM_CUS,/", "357ac7cd-2e1c-dcb0-77f6-37527237f35b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(50371);

        c.DefineDerivedCounter("HSPatches", "HullShader", "The number of patches processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0", "d1bbd27d-d591-4509-df52-d329fb73a98f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12386);
        internalCounters.push_back(12898);
        internalCounters.push_back(12326);
        internalCounters.push_back(12838);

        c.DefineDerivedCounter("HSVALUInstCount", "HullShader", "Average number of vector ALU instructions executed in the HS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,sum2,2,3,sum2,/", "786673bf-d58f-9895-3a37-9d6efb5e5804");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12382);
        internalCounters.push_back(12894);
        internalCounters.push_back(12326);
        internalCounters.push_back(12838);

        c.DefineDerivedCounter("HSSALUInstCount", "HullShader", "Average number of scalar ALU instructions executed in the HS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,sum2,2,3,sum2,/", "1af675c4-cb0b-c4c5-c131-2796750f683e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12439);
        internalCounters.push_back(12951);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("HSVALUBusy", "HullShader", "The percentage of GPUTime vector ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,sum2,NUM_SIMDS,/,2,/,(100),*", "7880d192-8015-0311-d43e-fb0b7a4df179");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12439);
        internalCounters.push_back(12951);

        c.DefineDerivedCounter("HSVALUBusyCycles", "HullShader", "Number of GPU cycles vector where ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,sum2,NUM_SIMDS,/", "3afb94e4-e937-5730-0cc9-41d3113ba012");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12382);
        internalCounters.push_back(12894);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("HSSALUBusy", "HullShader", "The percentage of GPUTime scalar ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,sum2,NUM_CUS,/,2,/,(100),*", "34748a4b-9148-0b06-b7b9-5700d6631bde");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(12382);
        internalCounters.push_back(12894);

        c.DefineDerivedCounter("HSSALUBusyCycles", "HullShader", "Number of GPU cycles where scalar ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,sum2,NUM_CUS,/", "9bceabf7-3f01-2fd9-7b1d-8fe46c729efc");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(50419);
        internalCounters.push_back(50355);
        internalCounters.push_back(50377);

        c.DefineDerivedCounter("DSVerticesIn", "DomainShader", "The number of vertices processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,1,ifnotzero,2,ifnotzero", "b88d9d05-2418-e639-4e3d-3a5815855f8d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9314);
        internalCounters.push_back(9826);
        internalCounters.push_back(9254);
        internalCounters.push_back(9766);
        internalCounters.push_back(7266);
        internalCounters.push_back(7778);
        internalCounters.push_back(7206);
        internalCounters.push_back(7718);
        internalCounters.push_back(7210);
        internalCounters.push_back(7722);
        internalCounters.push_back(11306);
        internalCounters.push_back(11818);

        c.DefineDerivedCounter("DSVALUInstCount", "DomainShader", "Average number of vector ALU instructions executed in the DS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,sum2,2,3,sum2,/,4,5,sum2,6,7,sum2,/,8,9,sum2,ifnotzero,10,11,sum2,ifnotzero", "03a3e949-82f9-be4d-7228-5eb5ad80915a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9310);
        internalCounters.push_back(9822);
        internalCounters.push_back(9254);
        internalCounters.push_back(9766);
        internalCounters.push_back(7262);
        internalCounters.push_back(7774);
        internalCounters.push_back(7206);
        internalCounters.push_back(7718);
        internalCounters.push_back(7210);
        internalCounters.push_back(7722);
        internalCounters.push_back(11306);
        internalCounters.push_back(11818);

        c.DefineDerivedCounter("DSSALUInstCount", "DomainShader", "Average number of scalar ALU instructions executed in the DS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,sum2,2,3,sum2,/,4,5,sum2,6,7,sum2,/,8,9,sum2,ifnotzero,10,11,sum2,ifnotzero", "73daa728-483e-95d0-5b40-504719aadc1c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(145);
        internalCounters.push_back(411);
        internalCounters.push_back(677);
        internalCounters.push_back(943);
        internalCounters.push_back(149);
        internalCounters.push_back(415);
        internalCounters.push_back(681);
        internalCounters.push_back(947);
        internalCounters.push_back(101);
        internalCounters.push_back(367);
        internalCounters.push_back(633);
        internalCounters.push_back(899);
        internalCounters.push_back(113);
        internalCounters.push_back(379);
        internalCounters.push_back(645);
        internalCounters.push_back(911);
        internalCounters.push_back(102);
        internalCounters.push_back(368);
        internalCounters.push_back(634);
        internalCounters.push_back(900);
        internalCounters.push_back(114);
        internalCounters.push_back(380);
        internalCounters.push_back(646);
        internalCounters.push_back(912);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("PrimitiveAssemblyBusy", "Timing", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max,24,/,(100),*,(100),min", "54ac5640-c4d7-95e2-20e0-6a9fdfc07333");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(145);
        internalCounters.push_back(411);
        internalCounters.push_back(677);
        internalCounters.push_back(943);
        internalCounters.push_back(149);
        internalCounters.push_back(415);
        internalCounters.push_back(681);
        internalCounters.push_back(947);
        internalCounters.push_back(101);
        internalCounters.push_back(367);
        internalCounters.push_back(633);
        internalCounters.push_back(899);
        internalCounters.push_back(113);
        internalCounters.push_back(379);
        internalCounters.push_back(645);
        internalCounters.push_back(911);
        internalCounters.push_back(102);
        internalCounters.push_back(368);
        internalCounters.push_back(634);
        internalCounters.push_back(900);
        internalCounters.push_back(114);
        internalCounters.push_back(380);
        internalCounters.push_back(646);
        internalCounters.push_back(912);

        c.DefineDerivedCounter("PrimitiveAssemblyBusyCycles", "Timing", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max", "99777f2d-9626-c78a-a97c-c4505eba1e5f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(48);
        internalCounters.push_back(314);
        internalCounters.push_back(580);
        internalCounters.push_back(846);

        c.DefineDerivedCounter("PrimitivesIn", "PrimitiveAssembly", "The number of primitives received by the hardware. This includes primitives generated by tessellation.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "a515b80d-75c3-c7d2-0d2f-d7766b4759a6");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(54);
        internalCounters.push_back(320);
        internalCounters.push_back(586);
        internalCounters.push_back(852);
        internalCounters.push_back(94);
        internalCounters.push_back(360);
        internalCounters.push_back(626);
        internalCounters.push_back(892);
        internalCounters.push_back(95);
        internalCounters.push_back(361);
        internalCounters.push_back(627);
        internalCounters.push_back(893);
        internalCounters.push_back(96);
        internalCounters.push_back(362);
        internalCounters.push_back(628);
        internalCounters.push_back(894);
        internalCounters.push_back(97);
        internalCounters.push_back(363);
        internalCounters.push_back(629);
        internalCounters.push_back(895);

        c.DefineDerivedCounter("CulledPrims", "PrimitiveAssembly", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+,4,+,5,+,6,+,7,+,8,+,9,+,10,+,11,+,12,+,13,+,14,+,15,+,16,+,17,+,18,+,19,+", "589bdf55-9192-280a-41c3-584bc94f2562");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(61);
        internalCounters.push_back(327);
        internalCounters.push_back(593);
        internalCounters.push_back(859);

        c.DefineDerivedCounter("ClippedPrims", "PrimitiveAssembly", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "5ef6f9d5-155e-5baa-163f-8359d9ea9bbf");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(149);
        internalCounters.push_back(415);
        internalCounters.push_back(681);
        internalCounters.push_back(947);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("PAStalledOnRasterizer", "PrimitiveAssembly", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,/,(100),*", "6f9f416b-53c1-0457-f88c-7b6ba8973974");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(149);
        internalCounters.push_back(415);
        internalCounters.push_back(681);
        internalCounters.push_back(947);

        c.DefineDerivedCounter("PAStalledOnRasterizerCycles", "PrimitiveAssembly", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max", "7a8c492a-c566-9328-6805-760dbff5c0f2");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14382);
        internalCounters.push_back(14607);
        internalCounters.push_back(14832);
        internalCounters.push_back(15057);
        internalCounters.push_back(14387);
        internalCounters.push_back(14612);
        internalCounters.push_back(14837);
        internalCounters.push_back(15062);
        internalCounters.push_back(14392);
        internalCounters.push_back(14617);
        internalCounters.push_back(14842);
        internalCounters.push_back(15067);
        internalCounters.push_back(14397);
        internalCounters.push_back(14622);
        internalCounters.push_back(14847);
        internalCounters.push_back(15072);

        c.DefineDerivedCounter("PSPixelsOut", "PixelShader", "Pixels exported from shader to color buffers. Does not include killed or alpha tested pixels; if there are multiple render targets, each render target receives one export, so this will be 2 for 1 pixel written to two RTs.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "24cba16c-baa6-6ecd-95ad-92ecb1338da1");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14384);
        internalCounters.push_back(14609);
        internalCounters.push_back(14834);
        internalCounters.push_back(15059);
        internalCounters.push_back(14389);
        internalCounters.push_back(14614);
        internalCounters.push_back(14839);
        internalCounters.push_back(15064);
        internalCounters.push_back(14394);
        internalCounters.push_back(14619);
        internalCounters.push_back(14844);
        internalCounters.push_back(15069);
        internalCounters.push_back(14399);
        internalCounters.push_back(14624);
        internalCounters.push_back(14849);
        internalCounters.push_back(15074);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("PSExportStalls", "PixelShader", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "9b4f466c-ff97-22bb-557d-84d3c4c51895");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14384);
        internalCounters.push_back(14609);
        internalCounters.push_back(14834);
        internalCounters.push_back(15059);
        internalCounters.push_back(14389);
        internalCounters.push_back(14614);
        internalCounters.push_back(14839);
        internalCounters.push_back(15064);
        internalCounters.push_back(14394);
        internalCounters.push_back(14619);
        internalCounters.push_back(14844);
        internalCounters.push_back(15069);
        internalCounters.push_back(14399);
        internalCounters.push_back(14624);
        internalCounters.push_back(14849);
        internalCounters.push_back(15074);

        c.DefineDerivedCounter("PSExportStallsCycles", "PixelShader", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "47c72aad-64e6-0864-d533-d8e0bc27c156");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(10338);
        internalCounters.push_back(10850);
        internalCounters.push_back(10278);
        internalCounters.push_back(10790);

        c.DefineDerivedCounter("PSVALUInstCount", "PixelShader", "Average number of vector ALU instructions executed in the PS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,sum2,2,3,sum2,/", "eb74389e-435c-4137-ecf1-39eb5bc1cbfe");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(10334);
        internalCounters.push_back(10846);
        internalCounters.push_back(10278);
        internalCounters.push_back(10790);

        c.DefineDerivedCounter("PSSALUInstCount", "PixelShader", "Average number of scalar ALU instructions executed in the PS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,sum2,2,3,sum2,/", "e6a06580-8a82-96d6-976c-acc121fc5516");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(10391);
        internalCounters.push_back(10903);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("PSVALUBusy", "PixelShader", "The percentage of GPUTime vector ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,sum2,NUM_SIMDS,/,2,/,(100),*", "6ce6fef7-8e33-10b4-f351-af755e177e85");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(10391);
        internalCounters.push_back(10903);

        c.DefineDerivedCounter("PSVALUBusyCycles", "PixelShader", "Number of GPU cycles where vector ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,sum2,NUM_SIMDS,/", "1e276f86-cd2a-72e7-fc9d-004f666f2981");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(10334);
        internalCounters.push_back(10846);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("PSSALUBusy", "PixelShader", "The percentage of GPUTime scalar ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,sum2,NUM_CUS,/,2,/,(100),*", "2ff9f34f-e94b-af4d-18c2-5fbbf6d1727a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(10334);
        internalCounters.push_back(10846);

        c.DefineDerivedCounter("PSSALUBusyCycles", "PixelShader", "Number of GPU cycles where scalar ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,sum2,NUM_CUS,/", "29808906-f128-b078-fc79-820a4b3b3b8d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSThreadGroups", "ComputeShader", "Total number of thread groups.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "8ce3fc80-56b2-97f9-8e70-2e8c747cea68");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5569);
        internalCounters.push_back(5898);
        internalCounters.push_back(5575);
        internalCounters.push_back(5904);

        c.DefineDerivedCounter("CSWavefronts", "ComputeShader", "The total number of wavefronts used for the CS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "42379c6e-369b-c237-8b25-cdb9cdc65c4d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);
        internalCounters.push_back(13354);
        internalCounters.push_back(13866);

        c.DefineDerivedCounter("CSThreads", "ComputeShader", "The number of CS threads processed by the hardware.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,sum4,4,5,sum2,ifnotzero", "7a648013-6eac-2665-ac36-13c6f4ac9c26");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13410);
        internalCounters.push_back(13922);
        internalCounters.push_back(13350);
        internalCounters.push_back(13862);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSVALUInsts", "ComputeShader", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,sum2,2,3,sum2,/,4,5,6,7,sum4,ifnotzero", "376cb1cc-5a40-9d1d-404c-f1736c0c5084");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13428);
        internalCounters.push_back(13940);
        internalCounters.push_back(13463);
        internalCounters.push_back(13975);
        internalCounters.push_back(13351);
        internalCounters.push_back(13863);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSVALUUtilization", "ComputeShader", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(0),0,1,sum2,2,3,sum2,(64),(32),4,5,sum2,ifnotzero,*,/,(100),*,2,3,sum2,ifnotzero,(100),min,6,7,8,9,sum4,ifnotzero", "ae943d2a-76e1-bb68-e1e2-0e06c9031611");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13406);
        internalCounters.push_back(13918);
        internalCounters.push_back(13350);
        internalCounters.push_back(13862);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSSALUInsts", "ComputeShader", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero", "eb211144-8136-ff86-e8bf-4d0493a904cb");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13415);
        internalCounters.push_back(13927);
        internalCounters.push_back(13350);
        internalCounters.push_back(13862);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSVFetchInsts", "ComputeShader", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero", "3e2829c0-6215-783b-c271-6d57ff2c520e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13407);
        internalCounters.push_back(13919);
        internalCounters.push_back(13350);
        internalCounters.push_back(13862);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSSFetchInsts", "ComputeShader", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero", "da09171c-6a0a-584f-fddc-dc5062d63a3e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13416);
        internalCounters.push_back(13928);
        internalCounters.push_back(13350);
        internalCounters.push_back(13862);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSVWriteInsts", "ComputeShader", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero", "43438c22-e910-b377-b767-b32902e0df0d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13463);
        internalCounters.push_back(13975);
        internalCounters.push_back(24);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSVALUBusy", "ComputeShader", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,sum2,NUM_SIMDS,/,2,/,(100),*,3,4,5,6,sum4,ifnotzero", "f1e64815-f6a8-c277-d4f9-d054b443e205");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13463);
        internalCounters.push_back(13975);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSVALUBusyCycles", "ComputeShader", "Number of GPU cycles where vector ALU instructions are processed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,sum2,NUM_SIMDS,/,2,3,4,5,sum4,ifnotzero", "2d0d5852-2658-eb73-68d2-f23f7118c9c3");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13406);
        internalCounters.push_back(13918);
        internalCounters.push_back(24);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSSALUBusy", "ComputeShader", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,sum2,NUM_CUS,/,2,/,(100),*,3,4,5,6,sum4,ifnotzero", "3fc35f4e-9882-94e3-6f5f-4e81cd97082a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13406);
        internalCounters.push_back(13918);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSSALUBusyCycles", "ComputeShader", "Number of GPU cycles where scalar ALU instructions are processed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,sum2,NUM_CUS,/,2,3,4,5,sum4,ifnotzero", "de58f8fc-8ed4-a799-648d-62ded7b1c4c4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15285);
        internalCounters.push_back(15511);
        internalCounters.push_back(15737);
        internalCounters.push_back(15963);
        internalCounters.push_back(16189);
        internalCounters.push_back(16415);
        internalCounters.push_back(16641);
        internalCounters.push_back(16867);
        internalCounters.push_back(17093);
        internalCounters.push_back(17319);
        internalCounters.push_back(17545);
        internalCounters.push_back(17771);
        internalCounters.push_back(17997);
        internalCounters.push_back(18223);
        internalCounters.push_back(18449);
        internalCounters.push_back(18675);
        internalCounters.push_back(18901);
        internalCounters.push_back(19127);
        internalCounters.push_back(19353);
        internalCounters.push_back(19579);
        internalCounters.push_back(19805);
        internalCounters.push_back(20031);
        internalCounters.push_back(20257);
        internalCounters.push_back(20483);
        internalCounters.push_back(20709);
        internalCounters.push_back(20935);
        internalCounters.push_back(21161);
        internalCounters.push_back(21387);
        internalCounters.push_back(21613);
        internalCounters.push_back(21839);
        internalCounters.push_back(22065);
        internalCounters.push_back(22291);
        internalCounters.push_back(22517);
        internalCounters.push_back(22743);
        internalCounters.push_back(22969);
        internalCounters.push_back(23195);
        internalCounters.push_back(23421);
        internalCounters.push_back(23647);
        internalCounters.push_back(23873);
        internalCounters.push_back(24099);
        internalCounters.push_back(24);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSMemUnitBusy", "ComputeShader", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,/,(100),*,41,42,43,44,sum4,ifnotzero", "42ab96e1-0a24-96c8-c4ff-098fa267d78e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15285);
        internalCounters.push_back(15511);
        internalCounters.push_back(15737);
        internalCounters.push_back(15963);
        internalCounters.push_back(16189);
        internalCounters.push_back(16415);
        internalCounters.push_back(16641);
        internalCounters.push_back(16867);
        internalCounters.push_back(17093);
        internalCounters.push_back(17319);
        internalCounters.push_back(17545);
        internalCounters.push_back(17771);
        internalCounters.push_back(17997);
        internalCounters.push_back(18223);
        internalCounters.push_back(18449);
        internalCounters.push_back(18675);
        internalCounters.push_back(18901);
        internalCounters.push_back(19127);
        internalCounters.push_back(19353);
        internalCounters.push_back(19579);
        internalCounters.push_back(19805);
        internalCounters.push_back(20031);
        internalCounters.push_back(20257);
        internalCounters.push_back(20483);
        internalCounters.push_back(20709);
        internalCounters.push_back(20935);
        internalCounters.push_back(21161);
        internalCounters.push_back(21387);
        internalCounters.push_back(21613);
        internalCounters.push_back(21839);
        internalCounters.push_back(22065);
        internalCounters.push_back(22291);
        internalCounters.push_back(22517);
        internalCounters.push_back(22743);
        internalCounters.push_back(22969);
        internalCounters.push_back(23195);
        internalCounters.push_back(23421);
        internalCounters.push_back(23647);
        internalCounters.push_back(23873);
        internalCounters.push_back(24099);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSMemUnitBusyCycles", "ComputeShader", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,41,42,43,sum4,ifnotzero", "39d5687f-c727-7c0c-af82-bb711d3897ed");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(26786);
        internalCounters.push_back(26863);
        internalCounters.push_back(26940);
        internalCounters.push_back(27017);
        internalCounters.push_back(27094);
        internalCounters.push_back(27171);
        internalCounters.push_back(27248);
        internalCounters.push_back(27325);
        internalCounters.push_back(27402);
        internalCounters.push_back(27479);
        internalCounters.push_back(27556);
        internalCounters.push_back(27633);
        internalCounters.push_back(27710);
        internalCounters.push_back(27787);
        internalCounters.push_back(27864);
        internalCounters.push_back(27941);
        internalCounters.push_back(28018);
        internalCounters.push_back(28095);
        internalCounters.push_back(28172);
        internalCounters.push_back(28249);
        internalCounters.push_back(28326);
        internalCounters.push_back(28403);
        internalCounters.push_back(28480);
        internalCounters.push_back(28557);
        internalCounters.push_back(28634);
        internalCounters.push_back(28711);
        internalCounters.push_back(28788);
        internalCounters.push_back(28865);
        internalCounters.push_back(28942);
        internalCounters.push_back(29019);
        internalCounters.push_back(29096);
        internalCounters.push_back(29173);
        internalCounters.push_back(29250);
        internalCounters.push_back(29327);
        internalCounters.push_back(29404);
        internalCounters.push_back(29481);
        internalCounters.push_back(29558);
        internalCounters.push_back(29635);
        internalCounters.push_back(29712);
        internalCounters.push_back(29789);
        internalCounters.push_back(24);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSMemUnitStalled", "ComputeShader", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,/,(100),*,41,42,43,44,sum4,ifnotzero", "f18e8679-1511-d533-d9ee-4365197f7d0c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(26786);
        internalCounters.push_back(26863);
        internalCounters.push_back(26940);
        internalCounters.push_back(27017);
        internalCounters.push_back(27094);
        internalCounters.push_back(27171);
        internalCounters.push_back(27248);
        internalCounters.push_back(27325);
        internalCounters.push_back(27402);
        internalCounters.push_back(27479);
        internalCounters.push_back(27556);
        internalCounters.push_back(27633);
        internalCounters.push_back(27710);
        internalCounters.push_back(27787);
        internalCounters.push_back(27864);
        internalCounters.push_back(27941);
        internalCounters.push_back(28018);
        internalCounters.push_back(28095);
        internalCounters.push_back(28172);
        internalCounters.push_back(28249);
        internalCounters.push_back(28326);
        internalCounters.push_back(28403);
        internalCounters.push_back(28480);
        internalCounters.push_back(28557);
        internalCounters.push_back(28634);
        internalCounters.push_back(28711);
        internalCounters.push_back(28788);
        internalCounters.push_back(28865);
        internalCounters.push_back(28942);
        internalCounters.push_back(29019);
        internalCounters.push_back(29096);
        internalCounters.push_back(29173);
        internalCounters.push_back(29250);
        internalCounters.push_back(29327);
        internalCounters.push_back(29404);
        internalCounters.push_back(29481);
        internalCounters.push_back(29558);
        internalCounters.push_back(29635);
        internalCounters.push_back(29712);
        internalCounters.push_back(29789);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSMemUnitStalledCycles", "ComputeShader", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,41,42,43,sum4,ifnotzero", "51991c84-ed2b-bf31-c4ab-8f8e9eb8f29f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52822);
        internalCounters.push_back(53057);
        internalCounters.push_back(53292);
        internalCounters.push_back(53527);
        internalCounters.push_back(53762);
        internalCounters.push_back(53997);
        internalCounters.push_back(54232);
        internalCounters.push_back(54467);
        internalCounters.push_back(54702);
        internalCounters.push_back(54937);
        internalCounters.push_back(55172);
        internalCounters.push_back(55407);
        internalCounters.push_back(55642);
        internalCounters.push_back(55877);
        internalCounters.push_back(56112);
        internalCounters.push_back(56347);
        internalCounters.push_back(24);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSWriteUnitStalled", "ComputeShader", "The percentage of GPUTime the write unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,18,19,20,sum4,ifnotzero", "55118f7a-8f92-726f-78c6-407f689a2eb4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52822);
        internalCounters.push_back(53057);
        internalCounters.push_back(53292);
        internalCounters.push_back(53527);
        internalCounters.push_back(53762);
        internalCounters.push_back(53997);
        internalCounters.push_back(54232);
        internalCounters.push_back(54467);
        internalCounters.push_back(54702);
        internalCounters.push_back(54937);
        internalCounters.push_back(55172);
        internalCounters.push_back(55407);
        internalCounters.push_back(55642);
        internalCounters.push_back(55877);
        internalCounters.push_back(56112);
        internalCounters.push_back(56347);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSWriteUnitStalledCycles", "ComputeShader", "Number of GPU cycles the write unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,17,18,19,sum4,ifnotzero", "be164c60-5e48-acac-9622-29616d09aa9a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13401);
        internalCounters.push_back(13913);
        internalCounters.push_back(13350);
        internalCounters.push_back(13862);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSGDSInsts", "ComputeShader", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero", "2a867f3e-4a37-ad16-55d1-f03d74707819");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13405);
        internalCounters.push_back(13917);
        internalCounters.push_back(13350);
        internalCounters.push_back(13862);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSLDSInsts", "ComputeShader", "The average number of LDS read/write instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero", "61b0b351-7e06-ef8e-a8e0-7a9e3200a836");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13377);
        internalCounters.push_back(13889);
        internalCounters.push_back(13350);
        internalCounters.push_back(13862);
        internalCounters.push_back(24);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSALUStalledByLDS", "ComputeShader", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(0),0,1,sum2,2,3,sum2,/,4,/,NUM_SHADER_ENGINES,/,(100),*,2,3,sum2,ifnotzero,5,6,7,8,sum4,ifnotzero", "6dc4f1c2-bad0-c9ff-156e-883b319a752a");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13377);
        internalCounters.push_back(13889);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSALUStalledByLDSCycles", "ComputeShader", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,sum2,NUM_SHADER_ENGINES,/,2,3,4,5,sum4,ifnotzero", "8f3d5f25-2159-0374-fafe-e26a7799b6c8");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13631);
        internalCounters.push_back(14143);
        internalCounters.push_back(24);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSLDSBankConflict", "ComputeShader", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,sum2,2,/,NUM_SIMDS,/,(100),*,3,4,5,6,sum4,ifnotzero", "1065ee10-2e41-ea41-1eb3-b61b491752f4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(13631);
        internalCounters.push_back(14143);
        internalCounters.push_back(5566);
        internalCounters.push_back(5895);
        internalCounters.push_back(5572);
        internalCounters.push_back(5901);

        c.DefineDerivedCounter("CSLDSBankConflictCycles", "ComputeShader", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,sum2,NUM_SIMDS,/,2,3,4,5,sum4,ifnotzero", "1fd1adf3-c51e-94fd-083e-c482a0a0809e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15285);
        internalCounters.push_back(15511);
        internalCounters.push_back(15737);
        internalCounters.push_back(15963);
        internalCounters.push_back(16189);
        internalCounters.push_back(16415);
        internalCounters.push_back(16641);
        internalCounters.push_back(16867);
        internalCounters.push_back(17093);
        internalCounters.push_back(17319);
        internalCounters.push_back(17545);
        internalCounters.push_back(17771);
        internalCounters.push_back(17997);
        internalCounters.push_back(18223);
        internalCounters.push_back(18449);
        internalCounters.push_back(18675);
        internalCounters.push_back(18901);
        internalCounters.push_back(19127);
        internalCounters.push_back(19353);
        internalCounters.push_back(19579);
        internalCounters.push_back(19805);
        internalCounters.push_back(20031);
        internalCounters.push_back(20257);
        internalCounters.push_back(20483);
        internalCounters.push_back(20709);
        internalCounters.push_back(20935);
        internalCounters.push_back(21161);
        internalCounters.push_back(21387);
        internalCounters.push_back(21613);
        internalCounters.push_back(21839);
        internalCounters.push_back(22065);
        internalCounters.push_back(22291);
        internalCounters.push_back(22517);
        internalCounters.push_back(22743);
        internalCounters.push_back(22969);
        internalCounters.push_back(23195);
        internalCounters.push_back(23421);
        internalCounters.push_back(23647);
        internalCounters.push_back(23873);
        internalCounters.push_back(24099);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("TexUnitBusy", "Timing", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,/,(100),*", "36afb8d9-42fc-aafe-66c5-449542153b2c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15285);
        internalCounters.push_back(15511);
        internalCounters.push_back(15737);
        internalCounters.push_back(15963);
        internalCounters.push_back(16189);
        internalCounters.push_back(16415);
        internalCounters.push_back(16641);
        internalCounters.push_back(16867);
        internalCounters.push_back(17093);
        internalCounters.push_back(17319);
        internalCounters.push_back(17545);
        internalCounters.push_back(17771);
        internalCounters.push_back(17997);
        internalCounters.push_back(18223);
        internalCounters.push_back(18449);
        internalCounters.push_back(18675);
        internalCounters.push_back(18901);
        internalCounters.push_back(19127);
        internalCounters.push_back(19353);
        internalCounters.push_back(19579);
        internalCounters.push_back(19805);
        internalCounters.push_back(20031);
        internalCounters.push_back(20257);
        internalCounters.push_back(20483);
        internalCounters.push_back(20709);
        internalCounters.push_back(20935);
        internalCounters.push_back(21161);
        internalCounters.push_back(21387);
        internalCounters.push_back(21613);
        internalCounters.push_back(21839);
        internalCounters.push_back(22065);
        internalCounters.push_back(22291);
        internalCounters.push_back(22517);
        internalCounters.push_back(22743);
        internalCounters.push_back(22969);
        internalCounters.push_back(23195);
        internalCounters.push_back(23421);
        internalCounters.push_back(23647);
        internalCounters.push_back(23873);
        internalCounters.push_back(24099);

        c.DefineDerivedCounter("TexUnitBusyCycles", "Timing", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40", "c68761f2-248c-4f39-6528-c308b1c0807c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15339);
        internalCounters.push_back(15565);
        internalCounters.push_back(15791);
        internalCounters.push_back(16017);
        internalCounters.push_back(16243);
        internalCounters.push_back(16469);
        internalCounters.push_back(16695);
        internalCounters.push_back(16921);
        internalCounters.push_back(17147);
        internalCounters.push_back(17373);
        internalCounters.push_back(17599);
        internalCounters.push_back(17825);
        internalCounters.push_back(18051);
        internalCounters.push_back(18277);
        internalCounters.push_back(18503);
        internalCounters.push_back(18729);
        internalCounters.push_back(18955);
        internalCounters.push_back(19181);
        internalCounters.push_back(19407);
        internalCounters.push_back(19633);
        internalCounters.push_back(19859);
        internalCounters.push_back(20085);
        internalCounters.push_back(20311);
        internalCounters.push_back(20537);
        internalCounters.push_back(20763);
        internalCounters.push_back(20989);
        internalCounters.push_back(21215);
        internalCounters.push_back(21441);
        internalCounters.push_back(21667);
        internalCounters.push_back(21893);
        internalCounters.push_back(22119);
        internalCounters.push_back(22345);
        internalCounters.push_back(22571);
        internalCounters.push_back(22797);
        internalCounters.push_back(23023);
        internalCounters.push_back(23249);
        internalCounters.push_back(23475);
        internalCounters.push_back(23701);
        internalCounters.push_back(23927);
        internalCounters.push_back(24153);
        internalCounters.push_back(15338);
        internalCounters.push_back(15564);
        internalCounters.push_back(15790);
        internalCounters.push_back(16016);
        internalCounters.push_back(16242);
        internalCounters.push_back(16468);
        internalCounters.push_back(16694);
        internalCounters.push_back(16920);
        internalCounters.push_back(17146);
        internalCounters.push_back(17372);
        internalCounters.push_back(17598);
        internalCounters.push_back(17824);
        internalCounters.push_back(18050);
        internalCounters.push_back(18276);
        internalCounters.push_back(18502);
        internalCounters.push_back(18728);
        internalCounters.push_back(18954);
        internalCounters.push_back(19180);
        internalCounters.push_back(19406);
        internalCounters.push_back(19632);
        internalCounters.push_back(19858);
        internalCounters.push_back(20084);
        internalCounters.push_back(20310);
        internalCounters.push_back(20536);
        internalCounters.push_back(20762);
        internalCounters.push_back(20988);
        internalCounters.push_back(21214);
        internalCounters.push_back(21440);
        internalCounters.push_back(21666);
        internalCounters.push_back(21892);
        internalCounters.push_back(22118);
        internalCounters.push_back(22344);
        internalCounters.push_back(22570);
        internalCounters.push_back(22796);
        internalCounters.push_back(23022);
        internalCounters.push_back(23248);
        internalCounters.push_back(23474);
        internalCounters.push_back(23700);
        internalCounters.push_back(23926);
        internalCounters.push_back(24152);

        c.DefineDerivedCounter("TexTriFilteringPct", "TextureUnit", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,+,/,(100),*", "1affc3c8-b917-5c81-622b-7004527208ae");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15339);
        internalCounters.push_back(15565);
        internalCounters.push_back(15791);
        internalCounters.push_back(16017);
        internalCounters.push_back(16243);
        internalCounters.push_back(16469);
        internalCounters.push_back(16695);
        internalCounters.push_back(16921);
        internalCounters.push_back(17147);
        internalCounters.push_back(17373);
        internalCounters.push_back(17599);
        internalCounters.push_back(17825);
        internalCounters.push_back(18051);
        internalCounters.push_back(18277);
        internalCounters.push_back(18503);
        internalCounters.push_back(18729);
        internalCounters.push_back(18955);
        internalCounters.push_back(19181);
        internalCounters.push_back(19407);
        internalCounters.push_back(19633);
        internalCounters.push_back(19859);
        internalCounters.push_back(20085);
        internalCounters.push_back(20311);
        internalCounters.push_back(20537);
        internalCounters.push_back(20763);
        internalCounters.push_back(20989);
        internalCounters.push_back(21215);
        internalCounters.push_back(21441);
        internalCounters.push_back(21667);
        internalCounters.push_back(21893);
        internalCounters.push_back(22119);
        internalCounters.push_back(22345);
        internalCounters.push_back(22571);
        internalCounters.push_back(22797);
        internalCounters.push_back(23023);
        internalCounters.push_back(23249);
        internalCounters.push_back(23475);
        internalCounters.push_back(23701);
        internalCounters.push_back(23927);
        internalCounters.push_back(24153);

        c.DefineDerivedCounter("TexTriFilteringCount", "TextureUnit", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40", "5785b3a1-a513-18db-4b1c-bdeef75bb2b6");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15338);
        internalCounters.push_back(15564);
        internalCounters.push_back(15790);
        internalCounters.push_back(16016);
        internalCounters.push_back(16242);
        internalCounters.push_back(16468);
        internalCounters.push_back(16694);
        internalCounters.push_back(16920);
        internalCounters.push_back(17146);
        internalCounters.push_back(17372);
        internalCounters.push_back(17598);
        internalCounters.push_back(17824);
        internalCounters.push_back(18050);
        internalCounters.push_back(18276);
        internalCounters.push_back(18502);
        internalCounters.push_back(18728);
        internalCounters.push_back(18954);
        internalCounters.push_back(19180);
        internalCounters.push_back(19406);
        internalCounters.push_back(19632);
        internalCounters.push_back(19858);
        internalCounters.push_back(20084);
        internalCounters.push_back(20310);
        internalCounters.push_back(20536);
        internalCounters.push_back(20762);
        internalCounters.push_back(20988);
        internalCounters.push_back(21214);
        internalCounters.push_back(21440);
        internalCounters.push_back(21666);
        internalCounters.push_back(21892);
        internalCounters.push_back(22118);
        internalCounters.push_back(22344);
        internalCounters.push_back(22570);
        internalCounters.push_back(22796);
        internalCounters.push_back(23022);
        internalCounters.push_back(23248);
        internalCounters.push_back(23474);
        internalCounters.push_back(23700);
        internalCounters.push_back(23926);
        internalCounters.push_back(24152);

        c.DefineDerivedCounter("NoTexTriFilteringCount", "TextureUnit", "Count of pixels that did not receive trilinear filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40", "179da29a-81af-c06e-ce8c-a0a731ea030d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15341);
        internalCounters.push_back(15567);
        internalCounters.push_back(15793);
        internalCounters.push_back(16019);
        internalCounters.push_back(16245);
        internalCounters.push_back(16471);
        internalCounters.push_back(16697);
        internalCounters.push_back(16923);
        internalCounters.push_back(17149);
        internalCounters.push_back(17375);
        internalCounters.push_back(17601);
        internalCounters.push_back(17827);
        internalCounters.push_back(18053);
        internalCounters.push_back(18279);
        internalCounters.push_back(18505);
        internalCounters.push_back(18731);
        internalCounters.push_back(18957);
        internalCounters.push_back(19183);
        internalCounters.push_back(19409);
        internalCounters.push_back(19635);
        internalCounters.push_back(19861);
        internalCounters.push_back(20087);
        internalCounters.push_back(20313);
        internalCounters.push_back(20539);
        internalCounters.push_back(20765);
        internalCounters.push_back(20991);
        internalCounters.push_back(21217);
        internalCounters.push_back(21443);
        internalCounters.push_back(21669);
        internalCounters.push_back(21895);
        internalCounters.push_back(22121);
        internalCounters.push_back(22347);
        internalCounters.push_back(22573);
        internalCounters.push_back(22799);
        internalCounters.push_back(23025);
        internalCounters.push_back(23251);
        internalCounters.push_back(23477);
        internalCounters.push_back(23703);
        internalCounters.push_back(23929);
        internalCounters.push_back(24155);
        internalCounters.push_back(15340);
        internalCounters.push_back(15566);
        internalCounters.push_back(15792);
        internalCounters.push_back(16018);
        internalCounters.push_back(16244);
        internalCounters.push_back(16470);
        internalCounters.push_back(16696);
        internalCounters.push_back(16922);
        internalCounters.push_back(17148);
        internalCounters.push_back(17374);
        internalCounters.push_back(17600);
        internalCounters.push_back(17826);
        internalCounters.push_back(18052);
        internalCounters.push_back(18278);
        internalCounters.push_back(18504);
        internalCounters.push_back(18730);
        internalCounters.push_back(18956);
        internalCounters.push_back(19182);
        internalCounters.push_back(19408);
        internalCounters.push_back(19634);
        internalCounters.push_back(19860);
        internalCounters.push_back(20086);
        internalCounters.push_back(20312);
        internalCounters.push_back(20538);
        internalCounters.push_back(20764);
        internalCounters.push_back(20990);
        internalCounters.push_back(21216);
        internalCounters.push_back(21442);
        internalCounters.push_back(21668);
        internalCounters.push_back(21894);
        internalCounters.push_back(22120);
        internalCounters.push_back(22346);
        internalCounters.push_back(22572);
        internalCounters.push_back(22798);
        internalCounters.push_back(23024);
        internalCounters.push_back(23250);
        internalCounters.push_back(23476);
        internalCounters.push_back(23702);
        internalCounters.push_back(23928);
        internalCounters.push_back(24154);

        c.DefineDerivedCounter("TexVolFilteringPct", "TextureUnit", "Percentage of pixels that received volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,+,/,(100),*", "b5ff6bed-3178-aee4-42dd-c74391c02a2d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15341);
        internalCounters.push_back(15567);
        internalCounters.push_back(15793);
        internalCounters.push_back(16019);
        internalCounters.push_back(16245);
        internalCounters.push_back(16471);
        internalCounters.push_back(16697);
        internalCounters.push_back(16923);
        internalCounters.push_back(17149);
        internalCounters.push_back(17375);
        internalCounters.push_back(17601);
        internalCounters.push_back(17827);
        internalCounters.push_back(18053);
        internalCounters.push_back(18279);
        internalCounters.push_back(18505);
        internalCounters.push_back(18731);
        internalCounters.push_back(18957);
        internalCounters.push_back(19183);
        internalCounters.push_back(19409);
        internalCounters.push_back(19635);
        internalCounters.push_back(19861);
        internalCounters.push_back(20087);
        internalCounters.push_back(20313);
        internalCounters.push_back(20539);
        internalCounters.push_back(20765);
        internalCounters.push_back(20991);
        internalCounters.push_back(21217);
        internalCounters.push_back(21443);
        internalCounters.push_back(21669);
        internalCounters.push_back(21895);
        internalCounters.push_back(22121);
        internalCounters.push_back(22347);
        internalCounters.push_back(22573);
        internalCounters.push_back(22799);
        internalCounters.push_back(23025);
        internalCounters.push_back(23251);
        internalCounters.push_back(23477);
        internalCounters.push_back(23703);
        internalCounters.push_back(23929);
        internalCounters.push_back(24155);

        c.DefineDerivedCounter("TexVolFilteringCount", "TextureUnit", "Count of pixels that received volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40", "4bddc587-d589-8128-e18c-762eab2c871f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15340);
        internalCounters.push_back(15566);
        internalCounters.push_back(15792);
        internalCounters.push_back(16018);
        internalCounters.push_back(16244);
        internalCounters.push_back(16470);
        internalCounters.push_back(16696);
        internalCounters.push_back(16922);
        internalCounters.push_back(17148);
        internalCounters.push_back(17374);
        internalCounters.push_back(17600);
        internalCounters.push_back(17826);
        internalCounters.push_back(18052);
        internalCounters.push_back(18278);
        internalCounters.push_back(18504);
        internalCounters.push_back(18730);
        internalCounters.push_back(18956);
        internalCounters.push_back(19182);
        internalCounters.push_back(19408);
        internalCounters.push_back(19634);
        internalCounters.push_back(19860);
        internalCounters.push_back(20086);
        internalCounters.push_back(20312);
        internalCounters.push_back(20538);
        internalCounters.push_back(20764);
        internalCounters.push_back(20990);
        internalCounters.push_back(21216);
        internalCounters.push_back(21442);
        internalCounters.push_back(21668);
        internalCounters.push_back(21894);
        internalCounters.push_back(22120);
        internalCounters.push_back(22346);
        internalCounters.push_back(22572);
        internalCounters.push_back(22798);
        internalCounters.push_back(23024);
        internalCounters.push_back(23250);
        internalCounters.push_back(23476);
        internalCounters.push_back(23702);
        internalCounters.push_back(23928);
        internalCounters.push_back(24154);

        c.DefineDerivedCounter("NoTexVolFilteringCount", "TextureUnit", "Count of pixels that did not receive volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40", "9fe1a854-17c6-9d26-b2b9-80610cd5827d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15359);
        internalCounters.push_back(15585);
        internalCounters.push_back(15811);
        internalCounters.push_back(16037);
        internalCounters.push_back(16263);
        internalCounters.push_back(16489);
        internalCounters.push_back(16715);
        internalCounters.push_back(16941);
        internalCounters.push_back(17167);
        internalCounters.push_back(17393);
        internalCounters.push_back(17619);
        internalCounters.push_back(17845);
        internalCounters.push_back(18071);
        internalCounters.push_back(18297);
        internalCounters.push_back(18523);
        internalCounters.push_back(18749);
        internalCounters.push_back(18975);
        internalCounters.push_back(19201);
        internalCounters.push_back(19427);
        internalCounters.push_back(19653);
        internalCounters.push_back(19879);
        internalCounters.push_back(20105);
        internalCounters.push_back(20331);
        internalCounters.push_back(20557);
        internalCounters.push_back(20783);
        internalCounters.push_back(21009);
        internalCounters.push_back(21235);
        internalCounters.push_back(21461);
        internalCounters.push_back(21687);
        internalCounters.push_back(21913);
        internalCounters.push_back(22139);
        internalCounters.push_back(22365);
        internalCounters.push_back(22591);
        internalCounters.push_back(22817);
        internalCounters.push_back(23043);
        internalCounters.push_back(23269);
        internalCounters.push_back(23495);
        internalCounters.push_back(23721);
        internalCounters.push_back(23947);
        internalCounters.push_back(24173);
        internalCounters.push_back(15360);
        internalCounters.push_back(15586);
        internalCounters.push_back(15812);
        internalCounters.push_back(16038);
        internalCounters.push_back(16264);
        internalCounters.push_back(16490);
        internalCounters.push_back(16716);
        internalCounters.push_back(16942);
        internalCounters.push_back(17168);
        internalCounters.push_back(17394);
        internalCounters.push_back(17620);
        internalCounters.push_back(17846);
        internalCounters.push_back(18072);
        internalCounters.push_back(18298);
        internalCounters.push_back(18524);
        internalCounters.push_back(18750);
        internalCounters.push_back(18976);
        internalCounters.push_back(19202);
        internalCounters.push_back(19428);
        internalCounters.push_back(19654);
        internalCounters.push_back(19880);
        internalCounters.push_back(20106);
        internalCounters.push_back(20332);
        internalCounters.push_back(20558);
        internalCounters.push_back(20784);
        internalCounters.push_back(21010);
        internalCounters.push_back(21236);
        internalCounters.push_back(21462);
        internalCounters.push_back(21688);
        internalCounters.push_back(21914);
        internalCounters.push_back(22140);
        internalCounters.push_back(22366);
        internalCounters.push_back(22592);
        internalCounters.push_back(22818);
        internalCounters.push_back(23044);
        internalCounters.push_back(23270);
        internalCounters.push_back(23496);
        internalCounters.push_back(23722);
        internalCounters.push_back(23948);
        internalCounters.push_back(24174);
        internalCounters.push_back(15361);
        internalCounters.push_back(15587);
        internalCounters.push_back(15813);
        internalCounters.push_back(16039);
        internalCounters.push_back(16265);
        internalCounters.push_back(16491);
        internalCounters.push_back(16717);
        internalCounters.push_back(16943);
        internalCounters.push_back(17169);
        internalCounters.push_back(17395);
        internalCounters.push_back(17621);
        internalCounters.push_back(17847);
        internalCounters.push_back(18073);
        internalCounters.push_back(18299);
        internalCounters.push_back(18525);
        internalCounters.push_back(18751);
        internalCounters.push_back(18977);
        internalCounters.push_back(19203);
        internalCounters.push_back(19429);
        internalCounters.push_back(19655);
        internalCounters.push_back(19881);
        internalCounters.push_back(20107);
        internalCounters.push_back(20333);
        internalCounters.push_back(20559);
        internalCounters.push_back(20785);
        internalCounters.push_back(21011);
        internalCounters.push_back(21237);
        internalCounters.push_back(21463);
        internalCounters.push_back(21689);
        internalCounters.push_back(21915);
        internalCounters.push_back(22141);
        internalCounters.push_back(22367);
        internalCounters.push_back(22593);
        internalCounters.push_back(22819);
        internalCounters.push_back(23045);
        internalCounters.push_back(23271);
        internalCounters.push_back(23497);
        internalCounters.push_back(23723);
        internalCounters.push_back(23949);
        internalCounters.push_back(24175);
        internalCounters.push_back(15362);
        internalCounters.push_back(15588);
        internalCounters.push_back(15814);
        internalCounters.push_back(16040);
        internalCounters.push_back(16266);
        internalCounters.push_back(16492);
        internalCounters.push_back(16718);
        internalCounters.push_back(16944);
        internalCounters.push_back(17170);
        internalCounters.push_back(17396);
        internalCounters.push_back(17622);
        internalCounters.push_back(17848);
        internalCounters.push_back(18074);
        internalCounters.push_back(18300);
        internalCounters.push_back(18526);
        internalCounters.push_back(18752);
        internalCounters.push_back(18978);
        internalCounters.push_back(19204);
        internalCounters.push_back(19430);
        internalCounters.push_back(19656);
        internalCounters.push_back(19882);
        internalCounters.push_back(20108);
        internalCounters.push_back(20334);
        internalCounters.push_back(20560);
        internalCounters.push_back(20786);
        internalCounters.push_back(21012);
        internalCounters.push_back(21238);
        internalCounters.push_back(21464);
        internalCounters.push_back(21690);
        internalCounters.push_back(21916);
        internalCounters.push_back(22142);
        internalCounters.push_back(22368);
        internalCounters.push_back(22594);
        internalCounters.push_back(22820);
        internalCounters.push_back(23046);
        internalCounters.push_back(23272);
        internalCounters.push_back(23498);
        internalCounters.push_back(23724);
        internalCounters.push_back(23950);
        internalCounters.push_back(24176);
        internalCounters.push_back(15363);
        internalCounters.push_back(15589);
        internalCounters.push_back(15815);
        internalCounters.push_back(16041);
        internalCounters.push_back(16267);
        internalCounters.push_back(16493);
        internalCounters.push_back(16719);
        internalCounters.push_back(16945);
        internalCounters.push_back(17171);
        internalCounters.push_back(17397);
        internalCounters.push_back(17623);
        internalCounters.push_back(17849);
        internalCounters.push_back(18075);
        internalCounters.push_back(18301);
        internalCounters.push_back(18527);
        internalCounters.push_back(18753);
        internalCounters.push_back(18979);
        internalCounters.push_back(19205);
        internalCounters.push_back(19431);
        internalCounters.push_back(19657);
        internalCounters.push_back(19883);
        internalCounters.push_back(20109);
        internalCounters.push_back(20335);
        internalCounters.push_back(20561);
        internalCounters.push_back(20787);
        internalCounters.push_back(21013);
        internalCounters.push_back(21239);
        internalCounters.push_back(21465);
        internalCounters.push_back(21691);
        internalCounters.push_back(21917);
        internalCounters.push_back(22143);
        internalCounters.push_back(22369);
        internalCounters.push_back(22595);
        internalCounters.push_back(22821);
        internalCounters.push_back(23047);
        internalCounters.push_back(23273);
        internalCounters.push_back(23499);
        internalCounters.push_back(23725);
        internalCounters.push_back(23951);
        internalCounters.push_back(24177);
        internalCounters.push_back(15364);
        internalCounters.push_back(15590);
        internalCounters.push_back(15816);
        internalCounters.push_back(16042);
        internalCounters.push_back(16268);
        internalCounters.push_back(16494);
        internalCounters.push_back(16720);
        internalCounters.push_back(16946);
        internalCounters.push_back(17172);
        internalCounters.push_back(17398);
        internalCounters.push_back(17624);
        internalCounters.push_back(17850);
        internalCounters.push_back(18076);
        internalCounters.push_back(18302);
        internalCounters.push_back(18528);
        internalCounters.push_back(18754);
        internalCounters.push_back(18980);
        internalCounters.push_back(19206);
        internalCounters.push_back(19432);
        internalCounters.push_back(19658);
        internalCounters.push_back(19884);
        internalCounters.push_back(20110);
        internalCounters.push_back(20336);
        internalCounters.push_back(20562);
        internalCounters.push_back(20788);
        internalCounters.push_back(21014);
        internalCounters.push_back(21240);
        internalCounters.push_back(21466);
        internalCounters.push_back(21692);
        internalCounters.push_back(21918);
        internalCounters.push_back(22144);
        internalCounters.push_back(22370);
        internalCounters.push_back(22596);
        internalCounters.push_back(22822);
        internalCounters.push_back(23048);
        internalCounters.push_back(23274);
        internalCounters.push_back(23500);
        internalCounters.push_back(23726);
        internalCounters.push_back(23952);
        internalCounters.push_back(24178);
        internalCounters.push_back(15365);
        internalCounters.push_back(15591);
        internalCounters.push_back(15817);
        internalCounters.push_back(16043);
        internalCounters.push_back(16269);
        internalCounters.push_back(16495);
        internalCounters.push_back(16721);
        internalCounters.push_back(16947);
        internalCounters.push_back(17173);
        internalCounters.push_back(17399);
        internalCounters.push_back(17625);
        internalCounters.push_back(17851);
        internalCounters.push_back(18077);
        internalCounters.push_back(18303);
        internalCounters.push_back(18529);
        internalCounters.push_back(18755);
        internalCounters.push_back(18981);
        internalCounters.push_back(19207);
        internalCounters.push_back(19433);
        internalCounters.push_back(19659);
        internalCounters.push_back(19885);
        internalCounters.push_back(20111);
        internalCounters.push_back(20337);
        internalCounters.push_back(20563);
        internalCounters.push_back(20789);
        internalCounters.push_back(21015);
        internalCounters.push_back(21241);
        internalCounters.push_back(21467);
        internalCounters.push_back(21693);
        internalCounters.push_back(21919);
        internalCounters.push_back(22145);
        internalCounters.push_back(22371);
        internalCounters.push_back(22597);
        internalCounters.push_back(22823);
        internalCounters.push_back(23049);
        internalCounters.push_back(23275);
        internalCounters.push_back(23501);
        internalCounters.push_back(23727);
        internalCounters.push_back(23953);
        internalCounters.push_back(24179);
        internalCounters.push_back(15366);
        internalCounters.push_back(15592);
        internalCounters.push_back(15818);
        internalCounters.push_back(16044);
        internalCounters.push_back(16270);
        internalCounters.push_back(16496);
        internalCounters.push_back(16722);
        internalCounters.push_back(16948);
        internalCounters.push_back(17174);
        internalCounters.push_back(17400);
        internalCounters.push_back(17626);
        internalCounters.push_back(17852);
        internalCounters.push_back(18078);
        internalCounters.push_back(18304);
        internalCounters.push_back(18530);
        internalCounters.push_back(18756);
        internalCounters.push_back(18982);
        internalCounters.push_back(19208);
        internalCounters.push_back(19434);
        internalCounters.push_back(19660);
        internalCounters.push_back(19886);
        internalCounters.push_back(20112);
        internalCounters.push_back(20338);
        internalCounters.push_back(20564);
        internalCounters.push_back(20790);
        internalCounters.push_back(21016);
        internalCounters.push_back(21242);
        internalCounters.push_back(21468);
        internalCounters.push_back(21694);
        internalCounters.push_back(21920);
        internalCounters.push_back(22146);
        internalCounters.push_back(22372);
        internalCounters.push_back(22598);
        internalCounters.push_back(22824);
        internalCounters.push_back(23050);
        internalCounters.push_back(23276);
        internalCounters.push_back(23502);
        internalCounters.push_back(23728);
        internalCounters.push_back(23954);
        internalCounters.push_back(24180);
        internalCounters.push_back(15367);
        internalCounters.push_back(15593);
        internalCounters.push_back(15819);
        internalCounters.push_back(16045);
        internalCounters.push_back(16271);
        internalCounters.push_back(16497);
        internalCounters.push_back(16723);
        internalCounters.push_back(16949);
        internalCounters.push_back(17175);
        internalCounters.push_back(17401);
        internalCounters.push_back(17627);
        internalCounters.push_back(17853);
        internalCounters.push_back(18079);
        internalCounters.push_back(18305);
        internalCounters.push_back(18531);
        internalCounters.push_back(18757);
        internalCounters.push_back(18983);
        internalCounters.push_back(19209);
        internalCounters.push_back(19435);
        internalCounters.push_back(19661);
        internalCounters.push_back(19887);
        internalCounters.push_back(20113);
        internalCounters.push_back(20339);
        internalCounters.push_back(20565);
        internalCounters.push_back(20791);
        internalCounters.push_back(21017);
        internalCounters.push_back(21243);
        internalCounters.push_back(21469);
        internalCounters.push_back(21695);
        internalCounters.push_back(21921);
        internalCounters.push_back(22147);
        internalCounters.push_back(22373);
        internalCounters.push_back(22599);
        internalCounters.push_back(22825);
        internalCounters.push_back(23051);
        internalCounters.push_back(23277);
        internalCounters.push_back(23503);
        internalCounters.push_back(23729);
        internalCounters.push_back(23955);
        internalCounters.push_back(24181);

        c.DefineDerivedCounter("TexAveAnisotropy", "TextureUnit", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,(2),40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,*,+,(4),80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,sum40,*,+,(6),120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,sum40,*,+,(8),160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,sum40,*,+,(10),200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,sum40,*,+,(12),240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,sum40,*,+,(14),280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,sum40,*,+,(16),320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,sum40,*,+,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,+,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,sum40,+,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,sum40,+,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,sum40,+,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,sum40,+,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,sum40,+,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,sum40,+,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,sum40,+,/", "7ca2a2b9-a4eb-ce23-d163-59147e672396");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(29974);
        internalCounters.push_back(30344);
        internalCounters.push_back(30714);
        internalCounters.push_back(31084);
        internalCounters.push_back(31454);
        internalCounters.push_back(31824);
        internalCounters.push_back(32194);
        internalCounters.push_back(32564);
        internalCounters.push_back(32934);
        internalCounters.push_back(33304);
        internalCounters.push_back(33674);
        internalCounters.push_back(34044);
        internalCounters.push_back(34414);
        internalCounters.push_back(34784);
        internalCounters.push_back(35154);
        internalCounters.push_back(35524);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("DepthStencilTestBusy", "Timing", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "6834fb52-42e8-bb50-fd48-ec2f2904e7e0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(29974);
        internalCounters.push_back(30344);
        internalCounters.push_back(30714);
        internalCounters.push_back(31084);
        internalCounters.push_back(31454);
        internalCounters.push_back(31824);
        internalCounters.push_back(32194);
        internalCounters.push_back(32564);
        internalCounters.push_back(32934);
        internalCounters.push_back(33304);
        internalCounters.push_back(33674);
        internalCounters.push_back(34044);
        internalCounters.push_back(34414);
        internalCounters.push_back(34784);
        internalCounters.push_back(35154);
        internalCounters.push_back(35524);

        c.DefineDerivedCounter("DepthStencilTestBusyCount", "Timing", "Number of GPU cycles spent performing depth and stencil tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "e02860fa-c7bd-90ea-2149-69b4e98a636c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(29845);
        internalCounters.push_back(30215);
        internalCounters.push_back(30585);
        internalCounters.push_back(30955);
        internalCounters.push_back(31325);
        internalCounters.push_back(31695);
        internalCounters.push_back(32065);
        internalCounters.push_back(32435);
        internalCounters.push_back(32805);
        internalCounters.push_back(33175);
        internalCounters.push_back(33545);
        internalCounters.push_back(33915);
        internalCounters.push_back(34285);
        internalCounters.push_back(34655);
        internalCounters.push_back(35025);
        internalCounters.push_back(35395);
        internalCounters.push_back(29834);
        internalCounters.push_back(30204);
        internalCounters.push_back(30574);
        internalCounters.push_back(30944);
        internalCounters.push_back(31314);
        internalCounters.push_back(31684);
        internalCounters.push_back(32054);
        internalCounters.push_back(32424);
        internalCounters.push_back(32794);
        internalCounters.push_back(33164);
        internalCounters.push_back(33534);
        internalCounters.push_back(33904);
        internalCounters.push_back(34274);
        internalCounters.push_back(34644);
        internalCounters.push_back(35014);
        internalCounters.push_back(35384);

        c.DefineDerivedCounter("HiZTilesAccepted", "DepthAndStencil", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*", "56176f45-d7ff-813d-4f05-3b2f046067e7");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(29845);
        internalCounters.push_back(30215);
        internalCounters.push_back(30585);
        internalCounters.push_back(30955);
        internalCounters.push_back(31325);
        internalCounters.push_back(31695);
        internalCounters.push_back(32065);
        internalCounters.push_back(32435);
        internalCounters.push_back(32805);
        internalCounters.push_back(33175);
        internalCounters.push_back(33545);
        internalCounters.push_back(33915);
        internalCounters.push_back(34285);
        internalCounters.push_back(34655);
        internalCounters.push_back(35025);
        internalCounters.push_back(35395);

        c.DefineDerivedCounter("HiZTilesAcceptedCount", "DepthAndStencil", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "95d4e3f6-b2f0-f26e-8423-aacdfaf79ea3");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(29834);
        internalCounters.push_back(30204);
        internalCounters.push_back(30574);
        internalCounters.push_back(30944);
        internalCounters.push_back(31314);
        internalCounters.push_back(31684);
        internalCounters.push_back(32054);
        internalCounters.push_back(32424);
        internalCounters.push_back(32794);
        internalCounters.push_back(33164);
        internalCounters.push_back(33534);
        internalCounters.push_back(33904);
        internalCounters.push_back(34274);
        internalCounters.push_back(34644);
        internalCounters.push_back(35014);
        internalCounters.push_back(35384);

        c.DefineDerivedCounter("HiZTilesRejectedCount", "DepthAndStencil", "Count of tiles not accepted by HiZ.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "156ba142-7eeb-aa6e-a00a-f8aea4e41e0b");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(29834);
        internalCounters.push_back(30204);
        internalCounters.push_back(30574);
        internalCounters.push_back(30944);
        internalCounters.push_back(31314);
        internalCounters.push_back(31684);
        internalCounters.push_back(32054);
        internalCounters.push_back(32424);
        internalCounters.push_back(32794);
        internalCounters.push_back(33164);
        internalCounters.push_back(33534);
        internalCounters.push_back(33904);
        internalCounters.push_back(34274);
        internalCounters.push_back(34644);
        internalCounters.push_back(35014);
        internalCounters.push_back(35384);
        internalCounters.push_back(29858);
        internalCounters.push_back(30228);
        internalCounters.push_back(30598);
        internalCounters.push_back(30968);
        internalCounters.push_back(31338);
        internalCounters.push_back(31708);
        internalCounters.push_back(32078);
        internalCounters.push_back(32448);
        internalCounters.push_back(32818);
        internalCounters.push_back(33188);
        internalCounters.push_back(33558);
        internalCounters.push_back(33928);
        internalCounters.push_back(34298);
        internalCounters.push_back(34668);
        internalCounters.push_back(35038);
        internalCounters.push_back(35408);

        c.DefineDerivedCounter("PreZTilesDetailCulled", "DepthAndStencil", "Percentage of tiles rejected because the associated prim had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*", "cad7f54d-a044-7574-c472-6f2065cbeeac");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(29858);
        internalCounters.push_back(30228);
        internalCounters.push_back(30598);
        internalCounters.push_back(30968);
        internalCounters.push_back(31338);
        internalCounters.push_back(31708);
        internalCounters.push_back(32078);
        internalCounters.push_back(32448);
        internalCounters.push_back(32818);
        internalCounters.push_back(33188);
        internalCounters.push_back(33558);
        internalCounters.push_back(33928);
        internalCounters.push_back(34298);
        internalCounters.push_back(34668);
        internalCounters.push_back(35038);
        internalCounters.push_back(35408);

        c.DefineDerivedCounter("PreZTilesDetailCulledCount", "DepthAndStencil", "Count of tiles rejected because the associated primitive had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "49262c8a-b1e6-90dd-f096-0fc4921715e9");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(29834);
        internalCounters.push_back(30204);
        internalCounters.push_back(30574);
        internalCounters.push_back(30944);
        internalCounters.push_back(31314);
        internalCounters.push_back(31684);
        internalCounters.push_back(32054);
        internalCounters.push_back(32424);
        internalCounters.push_back(32794);
        internalCounters.push_back(33164);
        internalCounters.push_back(33534);
        internalCounters.push_back(33904);
        internalCounters.push_back(34274);
        internalCounters.push_back(34644);
        internalCounters.push_back(35014);
        internalCounters.push_back(35384);

        c.DefineDerivedCounter("PreZTilesDetailSurvivingCount", "DepthAndStencil", "Count of tiles surviving because the associated primitive had contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "f803eaa4-bbed-bd39-775f-a64df92e2c08");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1263);
        internalCounters.push_back(1815);
        internalCounters.push_back(2367);
        internalCounters.push_back(2919);
        internalCounters.push_back(3471);
        internalCounters.push_back(4023);
        internalCounters.push_back(4575);
        internalCounters.push_back(5127);
        internalCounters.push_back(1264);
        internalCounters.push_back(1816);
        internalCounters.push_back(2368);
        internalCounters.push_back(2920);
        internalCounters.push_back(3472);
        internalCounters.push_back(4024);
        internalCounters.push_back(4576);
        internalCounters.push_back(5128);
        internalCounters.push_back(1265);
        internalCounters.push_back(1817);
        internalCounters.push_back(2369);
        internalCounters.push_back(2921);
        internalCounters.push_back(3473);
        internalCounters.push_back(4025);
        internalCounters.push_back(4577);
        internalCounters.push_back(5129);
        internalCounters.push_back(1266);
        internalCounters.push_back(1818);
        internalCounters.push_back(2370);
        internalCounters.push_back(2922);
        internalCounters.push_back(3474);
        internalCounters.push_back(4026);
        internalCounters.push_back(4578);
        internalCounters.push_back(5130);
        internalCounters.push_back(1339);
        internalCounters.push_back(1891);
        internalCounters.push_back(2443);
        internalCounters.push_back(2995);
        internalCounters.push_back(3547);
        internalCounters.push_back(4099);
        internalCounters.push_back(4651);
        internalCounters.push_back(5203);
        internalCounters.push_back(1340);
        internalCounters.push_back(1892);
        internalCounters.push_back(2444);
        internalCounters.push_back(2996);
        internalCounters.push_back(3548);
        internalCounters.push_back(4100);
        internalCounters.push_back(4652);
        internalCounters.push_back(5204);
        internalCounters.push_back(1341);
        internalCounters.push_back(1893);
        internalCounters.push_back(2445);
        internalCounters.push_back(2997);
        internalCounters.push_back(3549);
        internalCounters.push_back(4101);
        internalCounters.push_back(4653);
        internalCounters.push_back(5205);
        internalCounters.push_back(1342);
        internalCounters.push_back(1894);
        internalCounters.push_back(2446);
        internalCounters.push_back(2998);
        internalCounters.push_back(3550);
        internalCounters.push_back(4102);
        internalCounters.push_back(4654);
        internalCounters.push_back(5206);

        c.DefineDerivedCounter("HiZQuadsCulled", "DepthAndStencil", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum32,-,(0),max,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,/,(100),*", "fa0e319b-5573-6d34-5bab-904769925036");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1263);
        internalCounters.push_back(1815);
        internalCounters.push_back(2367);
        internalCounters.push_back(2919);
        internalCounters.push_back(3471);
        internalCounters.push_back(4023);
        internalCounters.push_back(4575);
        internalCounters.push_back(5127);
        internalCounters.push_back(1264);
        internalCounters.push_back(1816);
        internalCounters.push_back(2368);
        internalCounters.push_back(2920);
        internalCounters.push_back(3472);
        internalCounters.push_back(4024);
        internalCounters.push_back(4576);
        internalCounters.push_back(5128);
        internalCounters.push_back(1265);
        internalCounters.push_back(1817);
        internalCounters.push_back(2369);
        internalCounters.push_back(2921);
        internalCounters.push_back(3473);
        internalCounters.push_back(4025);
        internalCounters.push_back(4577);
        internalCounters.push_back(5129);
        internalCounters.push_back(1266);
        internalCounters.push_back(1818);
        internalCounters.push_back(2370);
        internalCounters.push_back(2922);
        internalCounters.push_back(3474);
        internalCounters.push_back(4026);
        internalCounters.push_back(4578);
        internalCounters.push_back(5130);
        internalCounters.push_back(1339);
        internalCounters.push_back(1891);
        internalCounters.push_back(2443);
        internalCounters.push_back(2995);
        internalCounters.push_back(3547);
        internalCounters.push_back(4099);
        internalCounters.push_back(4651);
        internalCounters.push_back(5203);
        internalCounters.push_back(1340);
        internalCounters.push_back(1892);
        internalCounters.push_back(2444);
        internalCounters.push_back(2996);
        internalCounters.push_back(3548);
        internalCounters.push_back(4100);
        internalCounters.push_back(4652);
        internalCounters.push_back(5204);
        internalCounters.push_back(1341);
        internalCounters.push_back(1893);
        internalCounters.push_back(2445);
        internalCounters.push_back(2997);
        internalCounters.push_back(3549);
        internalCounters.push_back(4101);
        internalCounters.push_back(4653);
        internalCounters.push_back(5205);
        internalCounters.push_back(1342);
        internalCounters.push_back(1894);
        internalCounters.push_back(2446);
        internalCounters.push_back(2998);
        internalCounters.push_back(3550);
        internalCounters.push_back(4102);
        internalCounters.push_back(4654);
        internalCounters.push_back(5206);

        c.DefineDerivedCounter("HiZQuadsCulledCount", "DepthAndStencil", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum32,-,(0),max", "73b0b39d-6df2-3e24-0b5c-7cb0ac8b6f39");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1339);
        internalCounters.push_back(1891);
        internalCounters.push_back(2443);
        internalCounters.push_back(2995);
        internalCounters.push_back(3547);
        internalCounters.push_back(4099);
        internalCounters.push_back(4651);
        internalCounters.push_back(5203);
        internalCounters.push_back(1340);
        internalCounters.push_back(1892);
        internalCounters.push_back(2444);
        internalCounters.push_back(2996);
        internalCounters.push_back(3548);
        internalCounters.push_back(4100);
        internalCounters.push_back(4652);
        internalCounters.push_back(5204);
        internalCounters.push_back(1341);
        internalCounters.push_back(1893);
        internalCounters.push_back(2445);
        internalCounters.push_back(2997);
        internalCounters.push_back(3549);
        internalCounters.push_back(4101);
        internalCounters.push_back(4653);
        internalCounters.push_back(5205);
        internalCounters.push_back(1342);
        internalCounters.push_back(1894);
        internalCounters.push_back(2446);
        internalCounters.push_back(2998);
        internalCounters.push_back(3550);
        internalCounters.push_back(4102);
        internalCounters.push_back(4654);
        internalCounters.push_back(5206);

        c.DefineDerivedCounter("HiZQuadsAcceptedCount", "DepthAndStencil", "Count of quads that did continue on in the pipeline after HiZ.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32", "59049ad9-42b5-c7cb-3616-6a8f6a8e4894");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1263);
        internalCounters.push_back(1815);
        internalCounters.push_back(2367);
        internalCounters.push_back(2919);
        internalCounters.push_back(3471);
        internalCounters.push_back(4023);
        internalCounters.push_back(4575);
        internalCounters.push_back(5127);
        internalCounters.push_back(1264);
        internalCounters.push_back(1816);
        internalCounters.push_back(2368);
        internalCounters.push_back(2920);
        internalCounters.push_back(3472);
        internalCounters.push_back(4024);
        internalCounters.push_back(4576);
        internalCounters.push_back(5128);
        internalCounters.push_back(1265);
        internalCounters.push_back(1817);
        internalCounters.push_back(2369);
        internalCounters.push_back(2921);
        internalCounters.push_back(3473);
        internalCounters.push_back(4025);
        internalCounters.push_back(4577);
        internalCounters.push_back(5129);
        internalCounters.push_back(1266);
        internalCounters.push_back(1818);
        internalCounters.push_back(2370);
        internalCounters.push_back(2922);
        internalCounters.push_back(3474);
        internalCounters.push_back(4026);
        internalCounters.push_back(4578);
        internalCounters.push_back(5130);
        internalCounters.push_back(1363);
        internalCounters.push_back(1915);
        internalCounters.push_back(2467);
        internalCounters.push_back(3019);
        internalCounters.push_back(3571);
        internalCounters.push_back(4123);
        internalCounters.push_back(4675);
        internalCounters.push_back(5227);
        internalCounters.push_back(1339);
        internalCounters.push_back(1891);
        internalCounters.push_back(2443);
        internalCounters.push_back(2995);
        internalCounters.push_back(3547);
        internalCounters.push_back(4099);
        internalCounters.push_back(4651);
        internalCounters.push_back(5203);
        internalCounters.push_back(1340);
        internalCounters.push_back(1892);
        internalCounters.push_back(2444);
        internalCounters.push_back(2996);
        internalCounters.push_back(3548);
        internalCounters.push_back(4100);
        internalCounters.push_back(4652);
        internalCounters.push_back(5204);
        internalCounters.push_back(1341);
        internalCounters.push_back(1893);
        internalCounters.push_back(2445);
        internalCounters.push_back(2997);
        internalCounters.push_back(3549);
        internalCounters.push_back(4101);
        internalCounters.push_back(4653);
        internalCounters.push_back(5205);
        internalCounters.push_back(1342);
        internalCounters.push_back(1894);
        internalCounters.push_back(2446);
        internalCounters.push_back(2998);
        internalCounters.push_back(3550);
        internalCounters.push_back(4102);
        internalCounters.push_back(4654);
        internalCounters.push_back(5206);

        c.DefineDerivedCounter("PreZQuadsCulled", "DepthAndStencil", "Percentage of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,sum32,32,33,34,35,36,37,38,39,sum8,-,(0),max,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,/,(100),*", "4e77547b-ec55-5663-f034-af59be66d77d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1263);
        internalCounters.push_back(1815);
        internalCounters.push_back(2367);
        internalCounters.push_back(2919);
        internalCounters.push_back(3471);
        internalCounters.push_back(4023);
        internalCounters.push_back(4575);
        internalCounters.push_back(5127);
        internalCounters.push_back(1264);
        internalCounters.push_back(1816);
        internalCounters.push_back(2368);
        internalCounters.push_back(2920);
        internalCounters.push_back(3472);
        internalCounters.push_back(4024);
        internalCounters.push_back(4576);
        internalCounters.push_back(5128);
        internalCounters.push_back(1265);
        internalCounters.push_back(1817);
        internalCounters.push_back(2369);
        internalCounters.push_back(2921);
        internalCounters.push_back(3473);
        internalCounters.push_back(4025);
        internalCounters.push_back(4577);
        internalCounters.push_back(5129);
        internalCounters.push_back(1266);
        internalCounters.push_back(1818);
        internalCounters.push_back(2370);
        internalCounters.push_back(2922);
        internalCounters.push_back(3474);
        internalCounters.push_back(4026);
        internalCounters.push_back(4578);
        internalCounters.push_back(5130);
        internalCounters.push_back(1363);
        internalCounters.push_back(1915);
        internalCounters.push_back(2467);
        internalCounters.push_back(3019);
        internalCounters.push_back(3571);
        internalCounters.push_back(4123);
        internalCounters.push_back(4675);
        internalCounters.push_back(5227);
        internalCounters.push_back(1339);
        internalCounters.push_back(1891);
        internalCounters.push_back(2443);
        internalCounters.push_back(2995);
        internalCounters.push_back(3547);
        internalCounters.push_back(4099);
        internalCounters.push_back(4651);
        internalCounters.push_back(5203);
        internalCounters.push_back(1340);
        internalCounters.push_back(1892);
        internalCounters.push_back(2444);
        internalCounters.push_back(2996);
        internalCounters.push_back(3548);
        internalCounters.push_back(4100);
        internalCounters.push_back(4652);
        internalCounters.push_back(5204);
        internalCounters.push_back(1341);
        internalCounters.push_back(1893);
        internalCounters.push_back(2445);
        internalCounters.push_back(2997);
        internalCounters.push_back(3549);
        internalCounters.push_back(4101);
        internalCounters.push_back(4653);
        internalCounters.push_back(5205);
        internalCounters.push_back(1342);
        internalCounters.push_back(1894);
        internalCounters.push_back(2446);
        internalCounters.push_back(2998);
        internalCounters.push_back(3550);
        internalCounters.push_back(4102);
        internalCounters.push_back(4654);
        internalCounters.push_back(5206);

        c.DefineDerivedCounter("PreZQuadsCulledCount", "DepthAndStencil", "Count of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,32,33,34,35,36,37,38,39,sum8,-,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,sum32,-,(0),max", "1bf169e6-9304-834e-df5f-0c44d7890a08");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1363);
        internalCounters.push_back(1915);
        internalCounters.push_back(2467);
        internalCounters.push_back(3019);
        internalCounters.push_back(3571);
        internalCounters.push_back(4123);
        internalCounters.push_back(4675);
        internalCounters.push_back(5227);
        internalCounters.push_back(1339);
        internalCounters.push_back(1891);
        internalCounters.push_back(2443);
        internalCounters.push_back(2995);
        internalCounters.push_back(3547);
        internalCounters.push_back(4099);
        internalCounters.push_back(4651);
        internalCounters.push_back(5203);
        internalCounters.push_back(1340);
        internalCounters.push_back(1892);
        internalCounters.push_back(2444);
        internalCounters.push_back(2996);
        internalCounters.push_back(3548);
        internalCounters.push_back(4100);
        internalCounters.push_back(4652);
        internalCounters.push_back(5204);
        internalCounters.push_back(1341);
        internalCounters.push_back(1893);
        internalCounters.push_back(2445);
        internalCounters.push_back(2997);
        internalCounters.push_back(3549);
        internalCounters.push_back(4101);
        internalCounters.push_back(4653);
        internalCounters.push_back(5205);
        internalCounters.push_back(1342);
        internalCounters.push_back(1894);
        internalCounters.push_back(2446);
        internalCounters.push_back(2998);
        internalCounters.push_back(3550);
        internalCounters.push_back(4102);
        internalCounters.push_back(4654);
        internalCounters.push_back(5206);

        c.DefineDerivedCounter("PreZQuadsSurvivingCount", "DepthAndStencil", "Count of quads surviving detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum32,0,1,2,3,4,5,6,7,sum8,-,(0),max", "50e25e51-3713-89cb-7f92-559cde5e5532");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1363);
        internalCounters.push_back(1915);
        internalCounters.push_back(2467);
        internalCounters.push_back(3019);
        internalCounters.push_back(3571);
        internalCounters.push_back(4123);
        internalCounters.push_back(4675);
        internalCounters.push_back(5227);
        internalCounters.push_back(1263);
        internalCounters.push_back(1815);
        internalCounters.push_back(2367);
        internalCounters.push_back(2919);
        internalCounters.push_back(3471);
        internalCounters.push_back(4023);
        internalCounters.push_back(4575);
        internalCounters.push_back(5127);
        internalCounters.push_back(1264);
        internalCounters.push_back(1816);
        internalCounters.push_back(2368);
        internalCounters.push_back(2920);
        internalCounters.push_back(3472);
        internalCounters.push_back(4024);
        internalCounters.push_back(4576);
        internalCounters.push_back(5128);
        internalCounters.push_back(1265);
        internalCounters.push_back(1817);
        internalCounters.push_back(2369);
        internalCounters.push_back(2921);
        internalCounters.push_back(3473);
        internalCounters.push_back(4025);
        internalCounters.push_back(4577);
        internalCounters.push_back(5129);
        internalCounters.push_back(1266);
        internalCounters.push_back(1818);
        internalCounters.push_back(2370);
        internalCounters.push_back(2922);
        internalCounters.push_back(3474);
        internalCounters.push_back(4026);
        internalCounters.push_back(4578);
        internalCounters.push_back(5130);

        c.DefineDerivedCounter("PostZQuads", "DepthAndStencil", "Percentage of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum32,/,(100),*", "58f0d34b-eeb8-e8db-abce-cb72584144be");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(1363);
        internalCounters.push_back(1915);
        internalCounters.push_back(2467);
        internalCounters.push_back(3019);
        internalCounters.push_back(3571);
        internalCounters.push_back(4123);
        internalCounters.push_back(4675);
        internalCounters.push_back(5227);

        c.DefineDerivedCounter("PostZQuadCount", "DepthAndStencil", "Count of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,sum8", "08404526-ce35-939b-34c8-a7a35a0ff4d6");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(30007);
        internalCounters.push_back(30377);
        internalCounters.push_back(30747);
        internalCounters.push_back(31117);
        internalCounters.push_back(31487);
        internalCounters.push_back(31857);
        internalCounters.push_back(32227);
        internalCounters.push_back(32597);
        internalCounters.push_back(32967);
        internalCounters.push_back(33337);
        internalCounters.push_back(33707);
        internalCounters.push_back(34077);
        internalCounters.push_back(34447);
        internalCounters.push_back(34817);
        internalCounters.push_back(35187);
        internalCounters.push_back(35557);

        c.DefineDerivedCounter("PreZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z before shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "3bfe6c4d-7422-ca03-7ea5-e67ff1a00136");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(30009);
        internalCounters.push_back(30379);
        internalCounters.push_back(30749);
        internalCounters.push_back(31119);
        internalCounters.push_back(31489);
        internalCounters.push_back(31859);
        internalCounters.push_back(32229);
        internalCounters.push_back(32599);
        internalCounters.push_back(32969);
        internalCounters.push_back(33339);
        internalCounters.push_back(33709);
        internalCounters.push_back(34079);
        internalCounters.push_back(34449);
        internalCounters.push_back(34819);
        internalCounters.push_back(35189);
        internalCounters.push_back(35559);

        c.DefineDerivedCounter("PreZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z before shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "df7f705e-5162-d3b5-da8b-63466cf9c4e5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(30008);
        internalCounters.push_back(30378);
        internalCounters.push_back(30748);
        internalCounters.push_back(31118);
        internalCounters.push_back(31488);
        internalCounters.push_back(31858);
        internalCounters.push_back(32228);
        internalCounters.push_back(32598);
        internalCounters.push_back(32968);
        internalCounters.push_back(33338);
        internalCounters.push_back(33708);
        internalCounters.push_back(34078);
        internalCounters.push_back(34448);
        internalCounters.push_back(34818);
        internalCounters.push_back(35188);
        internalCounters.push_back(35558);

        c.DefineDerivedCounter("PreZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z before shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "4484e950-f7a4-3800-bc74-78dd297f017e");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(30004);
        internalCounters.push_back(30374);
        internalCounters.push_back(30744);
        internalCounters.push_back(31114);
        internalCounters.push_back(31484);
        internalCounters.push_back(31854);
        internalCounters.push_back(32224);
        internalCounters.push_back(32594);
        internalCounters.push_back(32964);
        internalCounters.push_back(33334);
        internalCounters.push_back(33704);
        internalCounters.push_back(34074);
        internalCounters.push_back(34444);
        internalCounters.push_back(34814);
        internalCounters.push_back(35184);
        internalCounters.push_back(35554);

        c.DefineDerivedCounter("PostZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z after shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "4995d5d6-2330-b986-508b-fae24856f44c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(30006);
        internalCounters.push_back(30376);
        internalCounters.push_back(30746);
        internalCounters.push_back(31116);
        internalCounters.push_back(31486);
        internalCounters.push_back(31856);
        internalCounters.push_back(32226);
        internalCounters.push_back(32596);
        internalCounters.push_back(32966);
        internalCounters.push_back(33336);
        internalCounters.push_back(33706);
        internalCounters.push_back(34076);
        internalCounters.push_back(34446);
        internalCounters.push_back(34816);
        internalCounters.push_back(35186);
        internalCounters.push_back(35556);

        c.DefineDerivedCounter("PostZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z after shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "ae558af4-f4be-3dd4-7316-b2c4dcf0def8");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(30005);
        internalCounters.push_back(30375);
        internalCounters.push_back(30745);
        internalCounters.push_back(31115);
        internalCounters.push_back(31485);
        internalCounters.push_back(31855);
        internalCounters.push_back(32225);
        internalCounters.push_back(32595);
        internalCounters.push_back(32965);
        internalCounters.push_back(33335);
        internalCounters.push_back(33705);
        internalCounters.push_back(34075);
        internalCounters.push_back(34445);
        internalCounters.push_back(34815);
        internalCounters.push_back(35185);
        internalCounters.push_back(35555);

        c.DefineDerivedCounter("PostZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z after shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "b3684c94-814a-c695-c85d-a5b6ab798b35");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(29876);
        internalCounters.push_back(30246);
        internalCounters.push_back(30616);
        internalCounters.push_back(30986);
        internalCounters.push_back(31356);
        internalCounters.push_back(31726);
        internalCounters.push_back(32096);
        internalCounters.push_back(32466);
        internalCounters.push_back(32836);
        internalCounters.push_back(33206);
        internalCounters.push_back(33576);
        internalCounters.push_back(33946);
        internalCounters.push_back(34316);
        internalCounters.push_back(34686);
        internalCounters.push_back(35056);
        internalCounters.push_back(35426);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("ZUnitStalled", "DepthAndStencil", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "5e86c3ad-1726-3157-1d01-7ed188bf854d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(29876);
        internalCounters.push_back(30246);
        internalCounters.push_back(30616);
        internalCounters.push_back(30986);
        internalCounters.push_back(31356);
        internalCounters.push_back(31726);
        internalCounters.push_back(32096);
        internalCounters.push_back(32466);
        internalCounters.push_back(32836);
        internalCounters.push_back(33206);
        internalCounters.push_back(33576);
        internalCounters.push_back(33946);
        internalCounters.push_back(34316);
        internalCounters.push_back(34686);
        internalCounters.push_back(35056);
        internalCounters.push_back(35426);

        c.DefineDerivedCounter("ZUnitStalledCycles", "DepthAndStencil", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "4351fa7f-6737-2c3e-3ffb-b3addbdceedd");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(29878);
        internalCounters.push_back(30248);
        internalCounters.push_back(30618);
        internalCounters.push_back(30988);
        internalCounters.push_back(31358);
        internalCounters.push_back(31728);
        internalCounters.push_back(32098);
        internalCounters.push_back(32468);
        internalCounters.push_back(32838);
        internalCounters.push_back(33208);
        internalCounters.push_back(33578);
        internalCounters.push_back(33948);
        internalCounters.push_back(34318);
        internalCounters.push_back(34688);
        internalCounters.push_back(35058);
        internalCounters.push_back(35428);
        internalCounters.push_back(29885);
        internalCounters.push_back(30255);
        internalCounters.push_back(30625);
        internalCounters.push_back(30995);
        internalCounters.push_back(31365);
        internalCounters.push_back(31735);
        internalCounters.push_back(32105);
        internalCounters.push_back(32475);
        internalCounters.push_back(32845);
        internalCounters.push_back(33215);
        internalCounters.push_back(33585);
        internalCounters.push_back(33955);
        internalCounters.push_back(34325);
        internalCounters.push_back(34695);
        internalCounters.push_back(35065);
        internalCounters.push_back(35435);

        c.DefineDerivedCounter("DBMemRead", "DepthAndStencil", "Number of bytes read from the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(256),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+", "dcdb4ee7-bd50-00f7-c028-9e5f4ce888c0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(29890);
        internalCounters.push_back(30260);
        internalCounters.push_back(30630);
        internalCounters.push_back(31000);
        internalCounters.push_back(31370);
        internalCounters.push_back(31740);
        internalCounters.push_back(32110);
        internalCounters.push_back(32480);
        internalCounters.push_back(32850);
        internalCounters.push_back(33220);
        internalCounters.push_back(33590);
        internalCounters.push_back(33960);
        internalCounters.push_back(34330);
        internalCounters.push_back(34700);
        internalCounters.push_back(35070);
        internalCounters.push_back(35440);
        internalCounters.push_back(29893);
        internalCounters.push_back(30263);
        internalCounters.push_back(30633);
        internalCounters.push_back(31003);
        internalCounters.push_back(31373);
        internalCounters.push_back(31743);
        internalCounters.push_back(32113);
        internalCounters.push_back(32483);
        internalCounters.push_back(32853);
        internalCounters.push_back(33223);
        internalCounters.push_back(33593);
        internalCounters.push_back(33963);
        internalCounters.push_back(34333);
        internalCounters.push_back(34703);
        internalCounters.push_back(35073);
        internalCounters.push_back(35443);

        c.DefineDerivedCounter("DBMemWritten", "DepthAndStencil", "Number of bytes written to the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+", "de5717f8-8a49-ee44-4645-10de51b37dcf");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(35878);
        internalCounters.push_back(36339);
        internalCounters.push_back(36800);
        internalCounters.push_back(37261);
        internalCounters.push_back(37722);
        internalCounters.push_back(38183);
        internalCounters.push_back(38644);
        internalCounters.push_back(39105);
        internalCounters.push_back(39566);
        internalCounters.push_back(40027);
        internalCounters.push_back(40488);
        internalCounters.push_back(40949);
        internalCounters.push_back(41410);
        internalCounters.push_back(41871);
        internalCounters.push_back(42332);
        internalCounters.push_back(42793);

        c.DefineDerivedCounter("CBMemRead", "ColorBuffer", "Number of bytes read from the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "84b531d8-a1f8-7f49-7c27-7bc97801f1e6");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(36009);
        internalCounters.push_back(36470);
        internalCounters.push_back(36931);
        internalCounters.push_back(37392);
        internalCounters.push_back(37853);
        internalCounters.push_back(38314);
        internalCounters.push_back(38775);
        internalCounters.push_back(39236);
        internalCounters.push_back(39697);
        internalCounters.push_back(40158);
        internalCounters.push_back(40619);
        internalCounters.push_back(41080);
        internalCounters.push_back(41541);
        internalCounters.push_back(42002);
        internalCounters.push_back(42463);
        internalCounters.push_back(42924);
        internalCounters.push_back(35876);
        internalCounters.push_back(36337);
        internalCounters.push_back(36798);
        internalCounters.push_back(37259);
        internalCounters.push_back(37720);
        internalCounters.push_back(38181);
        internalCounters.push_back(38642);
        internalCounters.push_back(39103);
        internalCounters.push_back(39564);
        internalCounters.push_back(40025);
        internalCounters.push_back(40486);
        internalCounters.push_back(40947);
        internalCounters.push_back(41408);
        internalCounters.push_back(41869);
        internalCounters.push_back(42330);
        internalCounters.push_back(42791);
        internalCounters.push_back(35877);
        internalCounters.push_back(36338);
        internalCounters.push_back(36799);
        internalCounters.push_back(37260);
        internalCounters.push_back(37721);
        internalCounters.push_back(38182);
        internalCounters.push_back(38643);
        internalCounters.push_back(39104);
        internalCounters.push_back(39565);
        internalCounters.push_back(40026);
        internalCounters.push_back(40487);
        internalCounters.push_back(40948);
        internalCounters.push_back(41409);
        internalCounters.push_back(41870);
        internalCounters.push_back(42331);
        internalCounters.push_back(42792);
        internalCounters.push_back(35878);
        internalCounters.push_back(36339);
        internalCounters.push_back(36800);
        internalCounters.push_back(37261);
        internalCounters.push_back(37722);
        internalCounters.push_back(38183);
        internalCounters.push_back(38644);
        internalCounters.push_back(39105);
        internalCounters.push_back(39566);
        internalCounters.push_back(40027);
        internalCounters.push_back(40488);
        internalCounters.push_back(40949);
        internalCounters.push_back(41410);
        internalCounters.push_back(41871);
        internalCounters.push_back(42332);
        internalCounters.push_back(42793);

        c.DefineDerivedCounter("CBColorAndMaskRead", "ColorBuffer", "Total number of bytes read from the color and mask buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*", "da41660e-eb6f-32ec-8a64-b32ca17bd7eb");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(35868);
        internalCounters.push_back(36329);
        internalCounters.push_back(36790);
        internalCounters.push_back(37251);
        internalCounters.push_back(37712);
        internalCounters.push_back(38173);
        internalCounters.push_back(38634);
        internalCounters.push_back(39095);
        internalCounters.push_back(39556);
        internalCounters.push_back(40017);
        internalCounters.push_back(40478);
        internalCounters.push_back(40939);
        internalCounters.push_back(41400);
        internalCounters.push_back(41861);
        internalCounters.push_back(42322);
        internalCounters.push_back(42783);

        c.DefineDerivedCounter("CBMemWritten", "ColorBuffer", "Number of bytes written to the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "550f8ff8-60b6-a6bf-87d0-25ac9e87de70");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(36007);
        internalCounters.push_back(36468);
        internalCounters.push_back(36929);
        internalCounters.push_back(37390);
        internalCounters.push_back(37851);
        internalCounters.push_back(38312);
        internalCounters.push_back(38773);
        internalCounters.push_back(39234);
        internalCounters.push_back(39695);
        internalCounters.push_back(40156);
        internalCounters.push_back(40617);
        internalCounters.push_back(41078);
        internalCounters.push_back(41539);
        internalCounters.push_back(42000);
        internalCounters.push_back(42461);
        internalCounters.push_back(42922);
        internalCounters.push_back(35866);
        internalCounters.push_back(36327);
        internalCounters.push_back(36788);
        internalCounters.push_back(37249);
        internalCounters.push_back(37710);
        internalCounters.push_back(38171);
        internalCounters.push_back(38632);
        internalCounters.push_back(39093);
        internalCounters.push_back(39554);
        internalCounters.push_back(40015);
        internalCounters.push_back(40476);
        internalCounters.push_back(40937);
        internalCounters.push_back(41398);
        internalCounters.push_back(41859);
        internalCounters.push_back(42320);
        internalCounters.push_back(42781);
        internalCounters.push_back(35867);
        internalCounters.push_back(36328);
        internalCounters.push_back(36789);
        internalCounters.push_back(37250);
        internalCounters.push_back(37711);
        internalCounters.push_back(38172);
        internalCounters.push_back(38633);
        internalCounters.push_back(39094);
        internalCounters.push_back(39555);
        internalCounters.push_back(40016);
        internalCounters.push_back(40477);
        internalCounters.push_back(40938);
        internalCounters.push_back(41399);
        internalCounters.push_back(41860);
        internalCounters.push_back(42321);
        internalCounters.push_back(42782);
        internalCounters.push_back(35868);
        internalCounters.push_back(36329);
        internalCounters.push_back(36790);
        internalCounters.push_back(37251);
        internalCounters.push_back(37712);
        internalCounters.push_back(38173);
        internalCounters.push_back(38634);
        internalCounters.push_back(39095);
        internalCounters.push_back(39556);
        internalCounters.push_back(40017);
        internalCounters.push_back(40478);
        internalCounters.push_back(40939);
        internalCounters.push_back(41400);
        internalCounters.push_back(41861);
        internalCounters.push_back(42322);
        internalCounters.push_back(42783);

        c.DefineDerivedCounter("CBColorAndMaskWritten", "ColorBuffer", "Total number of bytes written to the color and mask buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*", "29a04b69-8f5f-b770-a0f2-3453e2c99e49");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(35912);
        internalCounters.push_back(36373);
        internalCounters.push_back(36834);
        internalCounters.push_back(37295);
        internalCounters.push_back(37756);
        internalCounters.push_back(38217);
        internalCounters.push_back(38678);
        internalCounters.push_back(39139);
        internalCounters.push_back(39600);
        internalCounters.push_back(40061);
        internalCounters.push_back(40522);
        internalCounters.push_back(40983);
        internalCounters.push_back(41444);
        internalCounters.push_back(41905);
        internalCounters.push_back(42366);
        internalCounters.push_back(42827);
        internalCounters.push_back(35757);
        internalCounters.push_back(36218);
        internalCounters.push_back(36679);
        internalCounters.push_back(37140);
        internalCounters.push_back(37601);
        internalCounters.push_back(38062);
        internalCounters.push_back(38523);
        internalCounters.push_back(38984);
        internalCounters.push_back(39445);
        internalCounters.push_back(39906);
        internalCounters.push_back(40367);
        internalCounters.push_back(40828);
        internalCounters.push_back(41289);
        internalCounters.push_back(41750);
        internalCounters.push_back(42211);
        internalCounters.push_back(42672);

        c.DefineDerivedCounter("CBSlowPixelPct", "ColorBuffer", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*,(100),min", "5775943f-0313-7e52-9638-b24a449197bc");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(35912);
        internalCounters.push_back(36373);
        internalCounters.push_back(36834);
        internalCounters.push_back(37295);
        internalCounters.push_back(37756);
        internalCounters.push_back(38217);
        internalCounters.push_back(38678);
        internalCounters.push_back(39139);
        internalCounters.push_back(39600);
        internalCounters.push_back(40061);
        internalCounters.push_back(40522);
        internalCounters.push_back(40983);
        internalCounters.push_back(41444);
        internalCounters.push_back(41905);
        internalCounters.push_back(42366);
        internalCounters.push_back(42827);

        c.DefineDerivedCounter("CBSlowPixelCount", "ColorBuffer", "Number of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "47eacbb0-28c8-22b4-5c69-c00d5813bb1c");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(26759);
        internalCounters.push_back(26836);
        internalCounters.push_back(26913);
        internalCounters.push_back(26990);
        internalCounters.push_back(27067);
        internalCounters.push_back(27144);
        internalCounters.push_back(27221);
        internalCounters.push_back(27298);
        internalCounters.push_back(27375);
        internalCounters.push_back(27452);
        internalCounters.push_back(27529);
        internalCounters.push_back(27606);
        internalCounters.push_back(27683);
        internalCounters.push_back(27760);
        internalCounters.push_back(27837);
        internalCounters.push_back(27914);
        internalCounters.push_back(27991);
        internalCounters.push_back(28068);
        internalCounters.push_back(28145);
        internalCounters.push_back(28222);
        internalCounters.push_back(28299);
        internalCounters.push_back(28376);
        internalCounters.push_back(28453);
        internalCounters.push_back(28530);
        internalCounters.push_back(28607);
        internalCounters.push_back(28684);
        internalCounters.push_back(28761);
        internalCounters.push_back(28838);
        internalCounters.push_back(28915);
        internalCounters.push_back(28992);
        internalCounters.push_back(29069);
        internalCounters.push_back(29146);
        internalCounters.push_back(29223);
        internalCounters.push_back(29300);
        internalCounters.push_back(29377);
        internalCounters.push_back(29454);
        internalCounters.push_back(29531);
        internalCounters.push_back(29608);
        internalCounters.push_back(29685);
        internalCounters.push_back(29762);
        internalCounters.push_back(26768);
        internalCounters.push_back(26845);
        internalCounters.push_back(26922);
        internalCounters.push_back(26999);
        internalCounters.push_back(27076);
        internalCounters.push_back(27153);
        internalCounters.push_back(27230);
        internalCounters.push_back(27307);
        internalCounters.push_back(27384);
        internalCounters.push_back(27461);
        internalCounters.push_back(27538);
        internalCounters.push_back(27615);
        internalCounters.push_back(27692);
        internalCounters.push_back(27769);
        internalCounters.push_back(27846);
        internalCounters.push_back(27923);
        internalCounters.push_back(28000);
        internalCounters.push_back(28077);
        internalCounters.push_back(28154);
        internalCounters.push_back(28231);
        internalCounters.push_back(28308);
        internalCounters.push_back(28385);
        internalCounters.push_back(28462);
        internalCounters.push_back(28539);
        internalCounters.push_back(28616);
        internalCounters.push_back(28693);
        internalCounters.push_back(28770);
        internalCounters.push_back(28847);
        internalCounters.push_back(28924);
        internalCounters.push_back(29001);
        internalCounters.push_back(29078);
        internalCounters.push_back(29155);
        internalCounters.push_back(29232);
        internalCounters.push_back(29309);
        internalCounters.push_back(29386);
        internalCounters.push_back(29463);
        internalCounters.push_back(29540);
        internalCounters.push_back(29617);
        internalCounters.push_back(29694);
        internalCounters.push_back(29771);

        c.DefineDerivedCounter("L0CacheHit", "MemoryCache", "The percentage of read requests that hit the data in the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,ifnotzero", "286c786e-9a42-3371-9dea-dd54e6e612e9");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(26759);
        internalCounters.push_back(26836);
        internalCounters.push_back(26913);
        internalCounters.push_back(26990);
        internalCounters.push_back(27067);
        internalCounters.push_back(27144);
        internalCounters.push_back(27221);
        internalCounters.push_back(27298);
        internalCounters.push_back(27375);
        internalCounters.push_back(27452);
        internalCounters.push_back(27529);
        internalCounters.push_back(27606);
        internalCounters.push_back(27683);
        internalCounters.push_back(27760);
        internalCounters.push_back(27837);
        internalCounters.push_back(27914);
        internalCounters.push_back(27991);
        internalCounters.push_back(28068);
        internalCounters.push_back(28145);
        internalCounters.push_back(28222);
        internalCounters.push_back(28299);
        internalCounters.push_back(28376);
        internalCounters.push_back(28453);
        internalCounters.push_back(28530);
        internalCounters.push_back(28607);
        internalCounters.push_back(28684);
        internalCounters.push_back(28761);
        internalCounters.push_back(28838);
        internalCounters.push_back(28915);
        internalCounters.push_back(28992);
        internalCounters.push_back(29069);
        internalCounters.push_back(29146);
        internalCounters.push_back(29223);
        internalCounters.push_back(29300);
        internalCounters.push_back(29377);
        internalCounters.push_back(29454);
        internalCounters.push_back(29531);
        internalCounters.push_back(29608);
        internalCounters.push_back(29685);
        internalCounters.push_back(29762);

        c.DefineDerivedCounter("L0CacheRequestCount", "MemoryCache", "The number of read requests made to the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40", "74983cae-ee57-2e1b-d990-5128fef84e1f");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(26759);
        internalCounters.push_back(26836);
        internalCounters.push_back(26913);
        internalCounters.push_back(26990);
        internalCounters.push_back(27067);
        internalCounters.push_back(27144);
        internalCounters.push_back(27221);
        internalCounters.push_back(27298);
        internalCounters.push_back(27375);
        internalCounters.push_back(27452);
        internalCounters.push_back(27529);
        internalCounters.push_back(27606);
        internalCounters.push_back(27683);
        internalCounters.push_back(27760);
        internalCounters.push_back(27837);
        internalCounters.push_back(27914);
        internalCounters.push_back(27991);
        internalCounters.push_back(28068);
        internalCounters.push_back(28145);
        internalCounters.push_back(28222);
        internalCounters.push_back(28299);
        internalCounters.push_back(28376);
        internalCounters.push_back(28453);
        internalCounters.push_back(28530);
        internalCounters.push_back(28607);
        internalCounters.push_back(28684);
        internalCounters.push_back(28761);
        internalCounters.push_back(28838);
        internalCounters.push_back(28915);
        internalCounters.push_back(28992);
        internalCounters.push_back(29069);
        internalCounters.push_back(29146);
        internalCounters.push_back(29223);
        internalCounters.push_back(29300);
        internalCounters.push_back(29377);
        internalCounters.push_back(29454);
        internalCounters.push_back(29531);
        internalCounters.push_back(29608);
        internalCounters.push_back(29685);
        internalCounters.push_back(29762);
        internalCounters.push_back(26768);
        internalCounters.push_back(26845);
        internalCounters.push_back(26922);
        internalCounters.push_back(26999);
        internalCounters.push_back(27076);
        internalCounters.push_back(27153);
        internalCounters.push_back(27230);
        internalCounters.push_back(27307);
        internalCounters.push_back(27384);
        internalCounters.push_back(27461);
        internalCounters.push_back(27538);
        internalCounters.push_back(27615);
        internalCounters.push_back(27692);
        internalCounters.push_back(27769);
        internalCounters.push_back(27846);
        internalCounters.push_back(27923);
        internalCounters.push_back(28000);
        internalCounters.push_back(28077);
        internalCounters.push_back(28154);
        internalCounters.push_back(28231);
        internalCounters.push_back(28308);
        internalCounters.push_back(28385);
        internalCounters.push_back(28462);
        internalCounters.push_back(28539);
        internalCounters.push_back(28616);
        internalCounters.push_back(28693);
        internalCounters.push_back(28770);
        internalCounters.push_back(28847);
        internalCounters.push_back(28924);
        internalCounters.push_back(29001);
        internalCounters.push_back(29078);
        internalCounters.push_back(29155);
        internalCounters.push_back(29232);
        internalCounters.push_back(29309);
        internalCounters.push_back(29386);
        internalCounters.push_back(29463);
        internalCounters.push_back(29540);
        internalCounters.push_back(29617);
        internalCounters.push_back(29694);
        internalCounters.push_back(29771);

        c.DefineDerivedCounter("L0CacheHitCount", "MemoryCache", "The number of read requests which result in a cache hit from the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,-", "c0de7338-069b-c5ba-ead3-c65e030cd2ac");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(26768);
        internalCounters.push_back(26845);
        internalCounters.push_back(26922);
        internalCounters.push_back(26999);
        internalCounters.push_back(27076);
        internalCounters.push_back(27153);
        internalCounters.push_back(27230);
        internalCounters.push_back(27307);
        internalCounters.push_back(27384);
        internalCounters.push_back(27461);
        internalCounters.push_back(27538);
        internalCounters.push_back(27615);
        internalCounters.push_back(27692);
        internalCounters.push_back(27769);
        internalCounters.push_back(27846);
        internalCounters.push_back(27923);
        internalCounters.push_back(28000);
        internalCounters.push_back(28077);
        internalCounters.push_back(28154);
        internalCounters.push_back(28231);
        internalCounters.push_back(28308);
        internalCounters.push_back(28385);
        internalCounters.push_back(28462);
        internalCounters.push_back(28539);
        internalCounters.push_back(28616);
        internalCounters.push_back(28693);
        internalCounters.push_back(28770);
        internalCounters.push_back(28847);
        internalCounters.push_back(28924);
        internalCounters.push_back(29001);
        internalCounters.push_back(29078);
        internalCounters.push_back(29155);
        internalCounters.push_back(29232);
        internalCounters.push_back(29309);
        internalCounters.push_back(29386);
        internalCounters.push_back(29463);
        internalCounters.push_back(29540);
        internalCounters.push_back(29617);
        internalCounters.push_back(29694);
        internalCounters.push_back(29771);

        c.DefineDerivedCounter("L0CacheMissCount", "MemoryCache", "The number of read requests which result in a cache miss from the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40", "a2f08766-ea1b-6eae-6eaf-faa04125d3e6");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(6512);
        internalCounters.push_back(7024);
        internalCounters.push_back(6514);
        internalCounters.push_back(7026);

        c.DefineDerivedCounter("ScalarCacheHit", "MemoryCache", "The percentage of read requests made from executing shader code that hit the data in the Scalar cache. The Scalar cache contains data that does not vary in each thread across the wavefront. Each request is 64 bytes in size. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),2,3,sum2,0,1,sum2,/,-,(100),*,0,1,sum2,ifnotzero", "3346d2cf-b7e4-45b6-c0a0-350ce18159c0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(6512);
        internalCounters.push_back(7024);

        c.DefineDerivedCounter("ScalarCacheRequestCount", "MemoryCache", "The number of read requests made from executing shader code to the Scalar cache. The Scalar cache contains data that does not vary in each thread across the wavefront. Each request is 64 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,sum2", "b5ac4201-c4cd-caa5-6ca7-4bc9a3abee01");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(6512);
        internalCounters.push_back(7024);
        internalCounters.push_back(6514);
        internalCounters.push_back(7026);

        c.DefineDerivedCounter("ScalarCacheHitCount", "MemoryCache", "The number of read requests made from executing shader code which result in a cache hit from the Scalar cache. The Scalar cache contains data that does not vary in each thread across the wavefront. Each request is 64 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,sum2,2,3,sum2,-", "beebef4f-8f6c-9363-eda9-bb385ffec363");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(6514);
        internalCounters.push_back(7026);

        c.DefineDerivedCounter("ScalarCacheMissCount", "MemoryCache", "The number of read requests made from executing shader code which result in a cache miss from the Scalar cache. The Scalar cache contains data that does not vary in each thread across the wavefront. Each request is 64 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,sum2", "07f5afb2-75b2-4fc3-1a6a-579958f77dd3");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(6477);
        internalCounters.push_back(6989);
        internalCounters.push_back(6479);
        internalCounters.push_back(6991);

        c.DefineDerivedCounter("InstCacheHit", "MemoryCache", "The percentage of read requests made that hit the data in the Instruction cache. The Instruction cache supplies shader code to an executing shader. Each request is 64 bytes in size. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),2,3,sum2,0,1,sum2,/,-,(100),*,0,1,sum2,ifnotzero", "adf51399-597b-f017-8ec1-21817f92e91d");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(6477);
        internalCounters.push_back(6989);

        c.DefineDerivedCounter("InstCacheRequestCount", "MemoryCache", "The number of read requests made to the Instruction cache. The Instruction cache supplies shader code to an executing shader. Each request is 64 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,sum2", "8c92ca8c-7dcc-88a0-3037-9704aa4f64ac");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(6477);
        internalCounters.push_back(6989);
        internalCounters.push_back(6479);
        internalCounters.push_back(6991);

        c.DefineDerivedCounter("InstCacheHitCount", "MemoryCache", "The number of read requests which result in a cache hit from the Instruction cache. The Instruction cache supplies shader code to an executing shader. Each request is 64 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,sum2,2,3,sum2,-", "778be78f-cf83-9558-e967-868e997e6743");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(6479);
        internalCounters.push_back(6991);

        c.DefineDerivedCounter("InstCacheMissCount", "MemoryCache", "The number of read requests which result in a cache miss from the Instruction cache. The Instruction cache supplies shader code to an executing shader. Each request is 64 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,sum2", "351650dc-d349-dca8-2b78-b14a1479cf26");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(50761);
        internalCounters.push_back(50825);
        internalCounters.push_back(50889);
        internalCounters.push_back(50953);
        internalCounters.push_back(51017);
        internalCounters.push_back(51081);
        internalCounters.push_back(51145);
        internalCounters.push_back(51209);
        internalCounters.push_back(51273);
        internalCounters.push_back(51337);
        internalCounters.push_back(51401);
        internalCounters.push_back(51465);
        internalCounters.push_back(51529);
        internalCounters.push_back(51593);
        internalCounters.push_back(51657);
        internalCounters.push_back(51721);
        internalCounters.push_back(50765);
        internalCounters.push_back(50829);
        internalCounters.push_back(50893);
        internalCounters.push_back(50957);
        internalCounters.push_back(51021);
        internalCounters.push_back(51085);
        internalCounters.push_back(51149);
        internalCounters.push_back(51213);
        internalCounters.push_back(51277);
        internalCounters.push_back(51341);
        internalCounters.push_back(51405);
        internalCounters.push_back(51469);
        internalCounters.push_back(51533);
        internalCounters.push_back(51597);
        internalCounters.push_back(51661);
        internalCounters.push_back(51725);

        c.DefineDerivedCounter("L1CacheHit", "MemoryCache", "The percentage of read or write requests that hit the data in the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "5a34915a-24b8-8baf-2bf8-5878e7894ae3");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(50761);
        internalCounters.push_back(50825);
        internalCounters.push_back(50889);
        internalCounters.push_back(50953);
        internalCounters.push_back(51017);
        internalCounters.push_back(51081);
        internalCounters.push_back(51145);
        internalCounters.push_back(51209);
        internalCounters.push_back(51273);
        internalCounters.push_back(51337);
        internalCounters.push_back(51401);
        internalCounters.push_back(51465);
        internalCounters.push_back(51529);
        internalCounters.push_back(51593);
        internalCounters.push_back(51657);
        internalCounters.push_back(51721);

        c.DefineDerivedCounter("L1CacheRequestCount", "MemoryCache", "The number of read or write requests made to the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "29c76c67-4611-205d-0b88-d08668df03c5");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(50761);
        internalCounters.push_back(50825);
        internalCounters.push_back(50889);
        internalCounters.push_back(50953);
        internalCounters.push_back(51017);
        internalCounters.push_back(51081);
        internalCounters.push_back(51145);
        internalCounters.push_back(51209);
        internalCounters.push_back(51273);
        internalCounters.push_back(51337);
        internalCounters.push_back(51401);
        internalCounters.push_back(51465);
        internalCounters.push_back(51529);
        internalCounters.push_back(51593);
        internalCounters.push_back(51657);
        internalCounters.push_back(51721);
        internalCounters.push_back(50765);
        internalCounters.push_back(50829);
        internalCounters.push_back(50893);
        internalCounters.push_back(50957);
        internalCounters.push_back(51021);
        internalCounters.push_back(51085);
        internalCounters.push_back(51149);
        internalCounters.push_back(51213);
        internalCounters.push_back(51277);
        internalCounters.push_back(51341);
        internalCounters.push_back(51405);
        internalCounters.push_back(51469);
        internalCounters.push_back(51533);
        internalCounters.push_back(51597);
        internalCounters.push_back(51661);
        internalCounters.push_back(51725);

        c.DefineDerivedCounter("L1CacheHitCount", "MemoryCache", "The number of read or write requests which result in a cache hit from the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-", "1ae150c3-f2d0-82c6-a51b-a77fd8d5fc33");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(50765);
        internalCounters.push_back(50829);
        internalCounters.push_back(50893);
        internalCounters.push_back(50957);
        internalCounters.push_back(51021);
        internalCounters.push_back(51085);
        internalCounters.push_back(51149);
        internalCounters.push_back(51213);
        internalCounters.push_back(51277);
        internalCounters.push_back(51341);
        internalCounters.push_back(51405);
        internalCounters.push_back(51469);
        internalCounters.push_back(51533);
        internalCounters.push_back(51597);
        internalCounters.push_back(51661);
        internalCounters.push_back(51725);

        c.DefineDerivedCounter("L1CacheMissCount", "MemoryCache", "The number of read or write requests which result in a cache miss from the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "71bfec6d-257b-849d-e212-cdf5c1b1de65");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52746);
        internalCounters.push_back(52981);
        internalCounters.push_back(53216);
        internalCounters.push_back(53451);
        internalCounters.push_back(53686);
        internalCounters.push_back(53921);
        internalCounters.push_back(54156);
        internalCounters.push_back(54391);
        internalCounters.push_back(54626);
        internalCounters.push_back(54861);
        internalCounters.push_back(55096);
        internalCounters.push_back(55331);
        internalCounters.push_back(55566);
        internalCounters.push_back(55801);
        internalCounters.push_back(56036);
        internalCounters.push_back(56271);
        internalCounters.push_back(52778);
        internalCounters.push_back(53013);
        internalCounters.push_back(53248);
        internalCounters.push_back(53483);
        internalCounters.push_back(53718);
        internalCounters.push_back(53953);
        internalCounters.push_back(54188);
        internalCounters.push_back(54423);
        internalCounters.push_back(54658);
        internalCounters.push_back(54893);
        internalCounters.push_back(55128);
        internalCounters.push_back(55363);
        internalCounters.push_back(55598);
        internalCounters.push_back(55833);
        internalCounters.push_back(56068);
        internalCounters.push_back(56303);

        c.DefineDerivedCounter("L2CacheHit", "MemoryCache", "The percentage of read or write requests that hit the data in the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "47694e4d-6ce6-f387-080d-b1f3d00b73ac");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52778);
        internalCounters.push_back(53013);
        internalCounters.push_back(53248);
        internalCounters.push_back(53483);
        internalCounters.push_back(53718);
        internalCounters.push_back(53953);
        internalCounters.push_back(54188);
        internalCounters.push_back(54423);
        internalCounters.push_back(54658);
        internalCounters.push_back(54893);
        internalCounters.push_back(55128);
        internalCounters.push_back(55363);
        internalCounters.push_back(55598);
        internalCounters.push_back(55833);
        internalCounters.push_back(56068);
        internalCounters.push_back(56303);
        internalCounters.push_back(52746);
        internalCounters.push_back(52981);
        internalCounters.push_back(53216);
        internalCounters.push_back(53451);
        internalCounters.push_back(53686);
        internalCounters.push_back(53921);
        internalCounters.push_back(54156);
        internalCounters.push_back(54391);
        internalCounters.push_back(54626);
        internalCounters.push_back(54861);
        internalCounters.push_back(55096);
        internalCounters.push_back(55331);
        internalCounters.push_back(55566);
        internalCounters.push_back(55801);
        internalCounters.push_back(56036);
        internalCounters.push_back(56271);

        c.DefineDerivedCounter("L2CacheMiss", "MemoryCache", "The percentage of read or write requests that miss the data in the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size. Value range: 0% (optimal) to 100% (all miss).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*", "8aee5458-a58e-11b6-5131-7f19ed070117");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52746);
        internalCounters.push_back(52981);
        internalCounters.push_back(53216);
        internalCounters.push_back(53451);
        internalCounters.push_back(53686);
        internalCounters.push_back(53921);
        internalCounters.push_back(54156);
        internalCounters.push_back(54391);
        internalCounters.push_back(54626);
        internalCounters.push_back(54861);
        internalCounters.push_back(55096);
        internalCounters.push_back(55331);
        internalCounters.push_back(55566);
        internalCounters.push_back(55801);
        internalCounters.push_back(56036);
        internalCounters.push_back(56271);

        c.DefineDerivedCounter("L2CacheRequestCount", "MemoryCache", "The number of read or write requests made to the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "21e9219c-e725-0d96-06b1-b21698b736b2");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52746);
        internalCounters.push_back(52981);
        internalCounters.push_back(53216);
        internalCounters.push_back(53451);
        internalCounters.push_back(53686);
        internalCounters.push_back(53921);
        internalCounters.push_back(54156);
        internalCounters.push_back(54391);
        internalCounters.push_back(54626);
        internalCounters.push_back(54861);
        internalCounters.push_back(55096);
        internalCounters.push_back(55331);
        internalCounters.push_back(55566);
        internalCounters.push_back(55801);
        internalCounters.push_back(56036);
        internalCounters.push_back(56271);
        internalCounters.push_back(52778);
        internalCounters.push_back(53013);
        internalCounters.push_back(53248);
        internalCounters.push_back(53483);
        internalCounters.push_back(53718);
        internalCounters.push_back(53953);
        internalCounters.push_back(54188);
        internalCounters.push_back(54423);
        internalCounters.push_back(54658);
        internalCounters.push_back(54893);
        internalCounters.push_back(55128);
        internalCounters.push_back(55363);
        internalCounters.push_back(55598);
        internalCounters.push_back(55833);
        internalCounters.push_back(56068);
        internalCounters.push_back(56303);

        c.DefineDerivedCounter("L2CacheHitCount", "MemoryCache", "The number of read or write requests which result in a cache hit from the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-", "29ddcb92-d3dd-951b-1b23-efe52e4eeee4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52778);
        internalCounters.push_back(53013);
        internalCounters.push_back(53248);
        internalCounters.push_back(53483);
        internalCounters.push_back(53718);
        internalCounters.push_back(53953);
        internalCounters.push_back(54188);
        internalCounters.push_back(54423);
        internalCounters.push_back(54658);
        internalCounters.push_back(54893);
        internalCounters.push_back(55128);
        internalCounters.push_back(55363);
        internalCounters.push_back(55598);
        internalCounters.push_back(55833);
        internalCounters.push_back(56068);
        internalCounters.push_back(56303);

        c.DefineDerivedCounter("L2CacheMissCount", "MemoryCache", "The number of read or write requests which result in a cache miss from the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "376eec7b-ab25-9012-06b5-63291a17fd47");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52832);
        internalCounters.push_back(53067);
        internalCounters.push_back(53302);
        internalCounters.push_back(53537);
        internalCounters.push_back(53772);
        internalCounters.push_back(54007);
        internalCounters.push_back(54242);
        internalCounters.push_back(54477);
        internalCounters.push_back(54712);
        internalCounters.push_back(54947);
        internalCounters.push_back(55182);
        internalCounters.push_back(55417);
        internalCounters.push_back(55652);
        internalCounters.push_back(55887);
        internalCounters.push_back(56122);
        internalCounters.push_back(56357);
        internalCounters.push_back(52833);
        internalCounters.push_back(53068);
        internalCounters.push_back(53303);
        internalCounters.push_back(53538);
        internalCounters.push_back(53773);
        internalCounters.push_back(54008);
        internalCounters.push_back(54243);
        internalCounters.push_back(54478);
        internalCounters.push_back(54713);
        internalCounters.push_back(54948);
        internalCounters.push_back(55183);
        internalCounters.push_back(55418);
        internalCounters.push_back(55653);
        internalCounters.push_back(55888);
        internalCounters.push_back(56123);
        internalCounters.push_back(56358);
        internalCounters.push_back(52834);
        internalCounters.push_back(53069);
        internalCounters.push_back(53304);
        internalCounters.push_back(53539);
        internalCounters.push_back(53774);
        internalCounters.push_back(54009);
        internalCounters.push_back(54244);
        internalCounters.push_back(54479);
        internalCounters.push_back(54714);
        internalCounters.push_back(54949);
        internalCounters.push_back(55184);
        internalCounters.push_back(55419);
        internalCounters.push_back(55654);
        internalCounters.push_back(55889);
        internalCounters.push_back(56124);
        internalCounters.push_back(56359);
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
        internalCounters.push_back(55890);
        internalCounters.push_back(56125);
        internalCounters.push_back(56360);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total bytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,(96),*,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,(128),*,sum4", "664bb3ef-6eca-86b1-1e2d-30cb897b5fa9");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52818);
        internalCounters.push_back(53053);
        internalCounters.push_back(53288);
        internalCounters.push_back(53523);
        internalCounters.push_back(53758);
        internalCounters.push_back(53993);
        internalCounters.push_back(54228);
        internalCounters.push_back(54463);
        internalCounters.push_back(54698);
        internalCounters.push_back(54933);
        internalCounters.push_back(55168);
        internalCounters.push_back(55403);
        internalCounters.push_back(55638);
        internalCounters.push_back(55873);
        internalCounters.push_back(56108);
        internalCounters.push_back(56343);
        internalCounters.push_back(52819);
        internalCounters.push_back(53054);
        internalCounters.push_back(53289);
        internalCounters.push_back(53524);
        internalCounters.push_back(53759);
        internalCounters.push_back(53994);
        internalCounters.push_back(54229);
        internalCounters.push_back(54464);
        internalCounters.push_back(54699);
        internalCounters.push_back(54934);
        internalCounters.push_back(55169);
        internalCounters.push_back(55404);
        internalCounters.push_back(55639);
        internalCounters.push_back(55874);
        internalCounters.push_back(56109);
        internalCounters.push_back(56344);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total bytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+", "f96f2c16-b1b4-4ec4-229c-fc82e6f80a82");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15285);
        internalCounters.push_back(15511);
        internalCounters.push_back(15737);
        internalCounters.push_back(15963);
        internalCounters.push_back(16189);
        internalCounters.push_back(16415);
        internalCounters.push_back(16641);
        internalCounters.push_back(16867);
        internalCounters.push_back(17093);
        internalCounters.push_back(17319);
        internalCounters.push_back(17545);
        internalCounters.push_back(17771);
        internalCounters.push_back(17997);
        internalCounters.push_back(18223);
        internalCounters.push_back(18449);
        internalCounters.push_back(18675);
        internalCounters.push_back(18901);
        internalCounters.push_back(19127);
        internalCounters.push_back(19353);
        internalCounters.push_back(19579);
        internalCounters.push_back(19805);
        internalCounters.push_back(20031);
        internalCounters.push_back(20257);
        internalCounters.push_back(20483);
        internalCounters.push_back(20709);
        internalCounters.push_back(20935);
        internalCounters.push_back(21161);
        internalCounters.push_back(21387);
        internalCounters.push_back(21613);
        internalCounters.push_back(21839);
        internalCounters.push_back(22065);
        internalCounters.push_back(22291);
        internalCounters.push_back(22517);
        internalCounters.push_back(22743);
        internalCounters.push_back(22969);
        internalCounters.push_back(23195);
        internalCounters.push_back(23421);
        internalCounters.push_back(23647);
        internalCounters.push_back(23873);
        internalCounters.push_back(24099);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(15285);
        internalCounters.push_back(15511);
        internalCounters.push_back(15737);
        internalCounters.push_back(15963);
        internalCounters.push_back(16189);
        internalCounters.push_back(16415);
        internalCounters.push_back(16641);
        internalCounters.push_back(16867);
        internalCounters.push_back(17093);
        internalCounters.push_back(17319);
        internalCounters.push_back(17545);
        internalCounters.push_back(17771);
        internalCounters.push_back(17997);
        internalCounters.push_back(18223);
        internalCounters.push_back(18449);
        internalCounters.push_back(18675);
        internalCounters.push_back(18901);
        internalCounters.push_back(19127);
        internalCounters.push_back(19353);
        internalCounters.push_back(19579);
        internalCounters.push_back(19805);
        internalCounters.push_back(20031);
        internalCounters.push_back(20257);
        internalCounters.push_back(20483);
        internalCounters.push_back(20709);
        internalCounters.push_back(20935);
        internalCounters.push_back(21161);
        internalCounters.push_back(21387);
        internalCounters.push_back(21613);
        internalCounters.push_back(21839);
        internalCounters.push_back(22065);
        internalCounters.push_back(22291);
        internalCounters.push_back(22517);
        internalCounters.push_back(22743);
        internalCounters.push_back(22969);
        internalCounters.push_back(23195);
        internalCounters.push_back(23421);
        internalCounters.push_back(23647);
        internalCounters.push_back(23873);
        internalCounters.push_back(24099);

        c.DefineDerivedCounter("MemUnitBusyCycles", "GlobalMemory", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalledCycles). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40", "168f077c-4797-b2f5-717f-105c725266c8");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(26786);
        internalCounters.push_back(26863);
        internalCounters.push_back(26940);
        internalCounters.push_back(27017);
        internalCounters.push_back(27094);
        internalCounters.push_back(27171);
        internalCounters.push_back(27248);
        internalCounters.push_back(27325);
        internalCounters.push_back(27402);
        internalCounters.push_back(27479);
        internalCounters.push_back(27556);
        internalCounters.push_back(27633);
        internalCounters.push_back(27710);
        internalCounters.push_back(27787);
        internalCounters.push_back(27864);
        internalCounters.push_back(27941);
        internalCounters.push_back(28018);
        internalCounters.push_back(28095);
        internalCounters.push_back(28172);
        internalCounters.push_back(28249);
        internalCounters.push_back(28326);
        internalCounters.push_back(28403);
        internalCounters.push_back(28480);
        internalCounters.push_back(28557);
        internalCounters.push_back(28634);
        internalCounters.push_back(28711);
        internalCounters.push_back(28788);
        internalCounters.push_back(28865);
        internalCounters.push_back(28942);
        internalCounters.push_back(29019);
        internalCounters.push_back(29096);
        internalCounters.push_back(29173);
        internalCounters.push_back(29250);
        internalCounters.push_back(29327);
        internalCounters.push_back(29404);
        internalCounters.push_back(29481);
        internalCounters.push_back(29558);
        internalCounters.push_back(29635);
        internalCounters.push_back(29712);
        internalCounters.push_back(29789);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(26786);
        internalCounters.push_back(26863);
        internalCounters.push_back(26940);
        internalCounters.push_back(27017);
        internalCounters.push_back(27094);
        internalCounters.push_back(27171);
        internalCounters.push_back(27248);
        internalCounters.push_back(27325);
        internalCounters.push_back(27402);
        internalCounters.push_back(27479);
        internalCounters.push_back(27556);
        internalCounters.push_back(27633);
        internalCounters.push_back(27710);
        internalCounters.push_back(27787);
        internalCounters.push_back(27864);
        internalCounters.push_back(27941);
        internalCounters.push_back(28018);
        internalCounters.push_back(28095);
        internalCounters.push_back(28172);
        internalCounters.push_back(28249);
        internalCounters.push_back(28326);
        internalCounters.push_back(28403);
        internalCounters.push_back(28480);
        internalCounters.push_back(28557);
        internalCounters.push_back(28634);
        internalCounters.push_back(28711);
        internalCounters.push_back(28788);
        internalCounters.push_back(28865);
        internalCounters.push_back(28942);
        internalCounters.push_back(29019);
        internalCounters.push_back(29096);
        internalCounters.push_back(29173);
        internalCounters.push_back(29250);
        internalCounters.push_back(29327);
        internalCounters.push_back(29404);
        internalCounters.push_back(29481);
        internalCounters.push_back(29558);
        internalCounters.push_back(29635);
        internalCounters.push_back(29712);
        internalCounters.push_back(29789);

        c.DefineDerivedCounter("MemUnitStalledCycles", "GlobalMemory", "Number of GPU cycles the memory unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40", "2745659a-0e40-bace-3b9b-86a54f8e4623");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52822);
        internalCounters.push_back(53057);
        internalCounters.push_back(53292);
        internalCounters.push_back(53527);
        internalCounters.push_back(53762);
        internalCounters.push_back(53997);
        internalCounters.push_back(54232);
        internalCounters.push_back(54467);
        internalCounters.push_back(54702);
        internalCounters.push_back(54937);
        internalCounters.push_back(55172);
        internalCounters.push_back(55407);
        internalCounters.push_back(55642);
        internalCounters.push_back(55877);
        internalCounters.push_back(56112);
        internalCounters.push_back(56347);
        internalCounters.push_back(24);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(52822);
        internalCounters.push_back(53057);
        internalCounters.push_back(53292);
        internalCounters.push_back(53527);
        internalCounters.push_back(53762);
        internalCounters.push_back(53997);
        internalCounters.push_back(54232);
        internalCounters.push_back(54467);
        internalCounters.push_back(54702);
        internalCounters.push_back(54937);
        internalCounters.push_back(55172);
        internalCounters.push_back(55407);
        internalCounters.push_back(55642);
        internalCounters.push_back(55877);
        internalCounters.push_back(56112);
        internalCounters.push_back(56347);

        c.DefineDerivedCounter("WriteUnitStalledCycles", "GlobalMemory", "Number of GPU cycles the Write unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "ede3305e-abd4-d6bf-6b00-ffc57a29fce3");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(43784);
        internalCounters.push_back(43873);
        internalCounters.push_back(43962);
        internalCounters.push_back(44051);
        internalCounters.push_back(44140);
        internalCounters.push_back(44229);
        internalCounters.push_back(44318);
        internalCounters.push_back(44407);
        internalCounters.push_back(44496);
        internalCounters.push_back(44585);
        internalCounters.push_back(44674);
        internalCounters.push_back(44763);
        internalCounters.push_back(44852);
        internalCounters.push_back(44941);
        internalCounters.push_back(45030);
        internalCounters.push_back(45119);

        c.DefineDerivedCounter("LocalVidMemBytes", "GlobalMemory", "Number of bytes read from or written to local video memory", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "2a601145-56c1-625b-bedd-66d959c5ecc3");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(43786);
        internalCounters.push_back(43875);
        internalCounters.push_back(43964);
        internalCounters.push_back(44053);
        internalCounters.push_back(44142);
        internalCounters.push_back(44231);
        internalCounters.push_back(44320);
        internalCounters.push_back(44409);
        internalCounters.push_back(44498);
        internalCounters.push_back(44587);
        internalCounters.push_back(44676);
        internalCounters.push_back(44765);
        internalCounters.push_back(44854);
        internalCounters.push_back(44943);
        internalCounters.push_back(45032);
        internalCounters.push_back(45121);

        c.DefineDerivedCounter("PcieBytes", "GlobalMemory", "Number of bytes sent and received over the PCIe bus", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "4bbe92de-f79e-ed39-bfde-9e08390cdb21");
    }
}

