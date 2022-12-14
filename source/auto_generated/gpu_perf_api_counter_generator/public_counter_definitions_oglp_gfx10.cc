//==============================================================================
// Copyright (c) 2010-2022 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for OGLP GFX10.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter.h"
#include "auto_generated/gpu_perf_api_counter_generator/public_counter_definitions_oglp_gfx10.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicDerivedCountersOglpGfx10(GpaDerivedCounters& c)
{
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(59898);

        c.DefineDerivedCounter("GPUTime", "Timing", "Time this API command took to execute on the GPU in nanoseconds from the time the previous command reached the bottom of the pipeline (BOP) to the time this command reaches the bottom of the pipeline (BOP). Does not include time that draw calls are processed in parallel.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "0,TS_FREQ,/,(1000000000),*", "cbd338f2-de6c-7b14-92ad-ba724ca2e501");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24);
        internal_counters.push_back(0);

        c.DefineDerivedCounter("GPUBusy", "Timing", "The percentage of time the GPU command processor was busy.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,/,(100),*,(100),min", "b1ba5363-1abc-fe66-2fdd-1fe6ee8989a0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(24);

        c.DefineDerivedCounter("GPUBusyCycles", "Timing", "Number of GPU cycles that the GPU command processor was busy.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0", "451cb045-23af-ac44-4603-d5832fa041d9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5521);
        internal_counters.push_back(5850);
        internal_counters.push_back(5538);
        internal_counters.push_back(5867);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("VsGsBusy", "Timing", "The percentage of time the ShaderUnit has VS or GS work to do in a VS-[GS-]PS pipeline.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,max4,(0),4,5,sum2,ifnotzero,6,/,(100),*,(100),min", "969c41c7-eb0b-9706-a7a1-98f27c3af56b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5521);
        internal_counters.push_back(5850);
        internal_counters.push_back(5538);
        internal_counters.push_back(5867);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);

        c.DefineDerivedCounter("VsGsBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has VS or GS work to do in a VS-[GS-]PS pipeline.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,max4,(0),4,5,sum2,ifnotzero", "a8420bb7-6bd8-930a-9088-d73b9c039851");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(59898);
        internal_counters.push_back(5521);
        internal_counters.push_back(5850);
        internal_counters.push_back(5538);
        internal_counters.push_back(5867);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("VsGsTime", "Timing", "Time VS or GS are busy in nanoseconds in a VS-[GS-]PS pipeline.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "1,2,3,4,max4,(0),5,6,sum2,ifnotzero,7,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "3ce33b11-210d-b3de-9b6c-b9f3cd04beff");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5554);
        internal_counters.push_back(5883);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PreTessellationBusy", "Timing", "The percentage of time the ShaderUnit has VS and HS work to do in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,max2,2,3,sum2,ifnotzero,4,/,(100),*,(100),min", "346c7430-4666-7065-b5b7-1cb8cbb1c01c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5554);
        internal_counters.push_back(5883);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);

        c.DefineDerivedCounter("PreTessellationBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has VS and HS work to do in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,max2,2,3,sum2,ifnotzero", "dac68e38-0e3a-9364-2674-308e63bee2d2");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(59898);
        internal_counters.push_back(5554);
        internal_counters.push_back(5883);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PreTessellationTime", "Timing", "Time VS and HS are busy in nanoseconds in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,max2,3,4,sum2,ifnotzero,5,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "d5e6c54c-5ffb-b173-6118-bece61f0281c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5521);
        internal_counters.push_back(5850);
        internal_counters.push_back(5538);
        internal_counters.push_back(5867);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PostTessellationBusy", "Timing", "The percentage of time the ShaderUnit has DS or GS work to do in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,2,3,max4,4,5,sum2,ifnotzero,6,/,(100),*,(100),min", "1a275c68-9340-f358-71c6-a2648390381d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5521);
        internal_counters.push_back(5850);
        internal_counters.push_back(5538);
        internal_counters.push_back(5867);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);

        c.DefineDerivedCounter("PostTessellationBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has DS or GS work to do in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,3,max4,4,5,sum2,ifnotzero", "a5ed943b-13ef-942b-56fb-6d519eeb7337");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(59898);
        internal_counters.push_back(5521);
        internal_counters.push_back(5850);
        internal_counters.push_back(5538);
        internal_counters.push_back(5867);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PostTessellationTime", "Timing", "Time DS or GS are busy in nanoseconds in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,2,3,4,max4,5,6,sum2,ifnotzero,7,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "9f8dfa40-faee-2014-3467-2630a7d95c1e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5580);
        internal_counters.push_back(5909);
        internal_counters.push_back(5600);
        internal_counters.push_back(5929);
        internal_counters.push_back(5581);
        internal_counters.push_back(5910);
        internal_counters.push_back(5601);
        internal_counters.push_back(5930);
        internal_counters.push_back(5582);
        internal_counters.push_back(5911);
        internal_counters.push_back(5602);
        internal_counters.push_back(5931);
        internal_counters.push_back(5583);
        internal_counters.push_back(5912);
        internal_counters.push_back(5603);
        internal_counters.push_back(5932);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PSBusy", "Timing", "The percentage of time the ShaderUnit has pixel shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,2,ifnotzero,(0),1,3,ifnotzero,max,(0),4,6,ifnotzero,(0),5,7,ifnotzero,max,(0),8,10,ifnotzero,(0),9,11,ifnotzero,max,(0),12,14,ifnotzero,(0),13,15,ifnotzero,max,max4,16,/,(100),*,(100),min", "7e772beb-d82c-bd9a-aed0-fe504d416ce5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5580);
        internal_counters.push_back(5909);
        internal_counters.push_back(5600);
        internal_counters.push_back(5929);
        internal_counters.push_back(5581);
        internal_counters.push_back(5910);
        internal_counters.push_back(5601);
        internal_counters.push_back(5930);
        internal_counters.push_back(5582);
        internal_counters.push_back(5911);
        internal_counters.push_back(5602);
        internal_counters.push_back(5931);
        internal_counters.push_back(5583);
        internal_counters.push_back(5912);
        internal_counters.push_back(5603);
        internal_counters.push_back(5932);

        c.DefineDerivedCounter("PSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has pixel shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,2,ifnotzero,(0),1,3,ifnotzero,max,(0),4,6,ifnotzero,(0),5,7,ifnotzero,max,(0),8,10,ifnotzero,(0),9,11,ifnotzero,max,(0),12,14,ifnotzero,(0),13,15,ifnotzero,max,max4", "b58bea04-ce8e-2984-80f4-8aba7d4c817b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(59898);
        internal_counters.push_back(5580);
        internal_counters.push_back(5909);
        internal_counters.push_back(5600);
        internal_counters.push_back(5929);
        internal_counters.push_back(5581);
        internal_counters.push_back(5910);
        internal_counters.push_back(5601);
        internal_counters.push_back(5930);
        internal_counters.push_back(5582);
        internal_counters.push_back(5911);
        internal_counters.push_back(5602);
        internal_counters.push_back(5931);
        internal_counters.push_back(5583);
        internal_counters.push_back(5912);
        internal_counters.push_back(5603);
        internal_counters.push_back(5932);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PSTime", "Timing", "Time pixel shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "(0),1,3,ifnotzero,(0),2,4,ifnotzero,max,(0),5,7,ifnotzero,(0),6,8,ifnotzero,max,(0),9,11,ifnotzero,(0),10,12,ifnotzero,max,(0),13,15,ifnotzero,(0),14,16,ifnotzero,max,max4,17,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "edca7694-7416-e8a6-0c5a-63a5ad5f3d74");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5565);
        internal_counters.push_back(5894);
        internal_counters.push_back(5569);
        internal_counters.push_back(5898);
        internal_counters.push_back(5571);
        internal_counters.push_back(5900);
        internal_counters.push_back(5575);
        internal_counters.push_back(5904);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("CSBusy", "Timing", "The percentage of time the ShaderUnit has compute shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,comparemax2,4,5,6,7,comparemax2,max,8,/,(100),*,(100),min", "493fdd90-8d2b-a055-5e4e-2d29c3396b8c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5565);
        internal_counters.push_back(5894);
        internal_counters.push_back(5569);
        internal_counters.push_back(5898);
        internal_counters.push_back(5571);
        internal_counters.push_back(5900);
        internal_counters.push_back(5575);
        internal_counters.push_back(5904);

        c.DefineDerivedCounter("CSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has compute shader work to do.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,comparemax2,4,5,6,7,comparemax2,max", "39bcf1b8-f6b2-4c37-f9af-0a2bb59512f9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(59898);
        internal_counters.push_back(5565);
        internal_counters.push_back(5894);
        internal_counters.push_back(5569);
        internal_counters.push_back(5898);
        internal_counters.push_back(5571);
        internal_counters.push_back(5900);
        internal_counters.push_back(5575);
        internal_counters.push_back(5904);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("CSTime", "Timing", "Time compute shaders are busy in nanoseconds.", kGpaDataTypeFloat64, kGpaUsageTypeNanoseconds, internal_counters, "1,2,3,4,comparemax2,5,6,7,8,comparemax2,max,9,/,(1),min,0,TS_FREQ,/,(1000000000),*,*", "dbc24916-ecb2-7eef-8d63-7afadaaab6bc");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9314);
        internal_counters.push_back(9826);
        internal_counters.push_back(9254);
        internal_counters.push_back(9766);
        internal_counters.push_back(8290);
        internal_counters.push_back(8802);
        internal_counters.push_back(8230);
        internal_counters.push_back(8742);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);

        c.DefineDerivedCounter("VsGsVALUInstCount", "VertexGeometry", "Average number of vector ALU instructions executed for the VS and GS in a VS-[GS-]PS pipeline. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,sum2,6,7,sum2,/,6,7,sum2,ifnotzero,(0),8,9,sum2,ifnotzero", "9f5e6407-3b8c-e0a8-9987-a59586b45ea8");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9310);
        internal_counters.push_back(9822);
        internal_counters.push_back(9254);
        internal_counters.push_back(9766);
        internal_counters.push_back(8286);
        internal_counters.push_back(8798);
        internal_counters.push_back(8230);
        internal_counters.push_back(8742);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);

        c.DefineDerivedCounter("VsGsSALUInstCount", "VertexGeometry", "Average number of scalar ALU instructions executed for the VS and GS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,sum2,6,7,sum2,/,6,7,sum2,ifnotzero,(0),8,9,sum2,ifnotzero", "67fe9696-8428-cf74-09d9-9133ea0f148c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9367);
        internal_counters.push_back(9879);
        internal_counters.push_back(8343);
        internal_counters.push_back(8855);
        internal_counters.push_back(24);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);

        c.DefineDerivedCounter("VsGsVALUBusy", "VertexGeometry", "The percentage of GPUTime vector ALU instructions are being processed for the VS and GS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,sum2,2,3,sum2,+,NUM_SIMDS,/,4,/,(100),*,(0),5,6,sum2,ifnotzero", "0e98794e-d570-20a5-671c-b65c3991d358");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9367);
        internal_counters.push_back(9879);
        internal_counters.push_back(8343);
        internal_counters.push_back(8855);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);

        c.DefineDerivedCounter("VsGsVALUBusyCycles", "VertexGeometry", "Number of GPU cycles where vector ALU instructions are being processed for the VS and GS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,sum2,2,3,sum2,+,NUM_SIMDS,/,(0),4,5,sum2,ifnotzero", "3558535c-e727-e459-4484-bcb683fcac2f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9310);
        internal_counters.push_back(9822);
        internal_counters.push_back(8286);
        internal_counters.push_back(8798);
        internal_counters.push_back(24);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);

        c.DefineDerivedCounter("VsGsSALUBusy", "VertexGeometry", "The percentage of GPUTime scalar ALU instructions are being processed for the VS and GS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,sum2,2,3,sum2,+,NUM_CUS,/,4,/,(100),*,(0),5,6,sum2,ifnotzero", "49521e07-5a41-0c17-38d9-450718dcb5ab");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(9310);
        internal_counters.push_back(9822);
        internal_counters.push_back(8286);
        internal_counters.push_back(8798);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);

        c.DefineDerivedCounter("VsGsSALUBusyCycles", "VertexGeometry", "Number of GPU cycles where scalar ALU instructions are being processed for the VS and GS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,sum2,2,3,sum2,+,NUM_CUS,/,(0),4,5,sum2,ifnotzero", "c4f78496-7f24-cb3d-3108-e9e8c761cf07");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12386);
        internal_counters.push_back(12898);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);

        c.DefineDerivedCounter("PreTessVALUInstCount", "PreTessellation", "Average number of vector ALU instructions executed for the VS and HS in a pipeline that uses tessellation. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero", "a6894a29-4213-27d4-e186-b9ca6112e3f3");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12382);
        internal_counters.push_back(12894);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);

        c.DefineDerivedCounter("PreTessSALUInstCount", "PreTessellation", "Average number of scalar ALU instructions executed for the VS and HS in a pipeline that uses tessellation. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero", "c6d06968-3557-fb5d-7a28-5eda098190db");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12439);
        internal_counters.push_back(12951);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PreTessVALUBusy", "PreTessellation", "The percentage of GPUTime vector ALU instructions are being processed for the VS and HS in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,sum2,NUM_SIMDS,/,4,/,(100),*,2,3,sum2,ifnotzero", "72627e0a-da7e-899a-738c-69e8ba96bf42");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12439);
        internal_counters.push_back(12951);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);

        c.DefineDerivedCounter("PreTessVALUBusyCycles", "PreTessellation", "Number of GPU cycles vector where ALU instructions are being processed for the VS and HS in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,sum2,NUM_SIMDS,/,2,3,sum2,ifnotzero", "2d750b51-a75e-380b-1b42-40d59f4fbdb6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12382);
        internal_counters.push_back(12894);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PreTessSALUBusy", "PreTessellation", "The percentage of GPUTime scalar ALU instructions are being processed for the VS and HS in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,sum2,NUM_CUS,/,4,/,(100),*,2,3,sum2,ifnotzero", "74e778bb-ce25-32cd-caa6-810eb44c95fa");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(12382);
        internal_counters.push_back(12894);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);

        c.DefineDerivedCounter("PreTessSALUBusyCycles", "PreTessellation", "Number of GPU cycles where scalar ALU instructions are being processed for the VS and HS in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,sum2,NUM_CUS,/,2,3,sum2,ifnotzero", "8aa4a036-313f-f4b0-a820-ff0a6e71b1a2");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8290);
        internal_counters.push_back(8802);
        internal_counters.push_back(8230);
        internal_counters.push_back(8742);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);

        c.DefineDerivedCounter("PostTessVALUInstCount", "PostTessellation", "Average number of vector ALU instructions executed for the DS and GS in a pipeline that uses tessellation. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,sum2,2,3,sum2,/,4,5,sum2,ifnotzero", "718b7237-1371-4c85-3ad1-f12af258ba08");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8286);
        internal_counters.push_back(8798);
        internal_counters.push_back(8230);
        internal_counters.push_back(8742);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);

        c.DefineDerivedCounter("PostTessSALUInstCount", "PostTessellation", "Average number of scalar ALU instructions executed for the DS and GS in a pipeline that uses tessellation. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,sum2,2,3,sum2,/,4,5,sum2,ifnotzero", "546cecd8-53d4-c7b7-3b2e-f5b2db6c8282");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8343);
        internal_counters.push_back(8855);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PostTessVALUBusy", "PostTessellation", "The percentage of GPUTime vector ALU instructions are being processed for the DS and GS in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,sum2,NUM_SIMDS,/,4,/,(100),*,2,3,sum2,ifnotzero", "068d1738-da17-7b6d-9d88-4013a8b27bf8");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8343);
        internal_counters.push_back(8855);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);

        c.DefineDerivedCounter("PostTessVALUBusyCycles", "PostTessellation", "Number of GPU cycles vector where ALU instructions are being processed for the DS and GS in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,sum2,NUM_SIMDS,/,2,3,sum2,ifnotzero", "29951e35-e415-22e9-ea59-03955faa8973");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8286);
        internal_counters.push_back(8798);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PostTessSALUBusy", "PostTessellation", "The percentage of GPUTime scalar ALU instructions are being processed for the DS and GS in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,sum2,NUM_CUS,/,4,/,(100),*,2,3,sum2,ifnotzero", "776fb8e3-1541-75e5-8a4c-28d43d39662b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(8286);
        internal_counters.push_back(8798);
        internal_counters.push_back(5561);
        internal_counters.push_back(5890);

        c.DefineDerivedCounter("PostTessSALUBusyCycles", "PostTessellation", "Number of GPU cycles where scalar ALU instructions are being processed for the DS and GS in a pipeline that uses tessellation.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,sum2,NUM_CUS,/,2,3,sum2,ifnotzero", "fce0317e-c679-a310-fd96-85bbb4a8b79d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(145);
        internal_counters.push_back(411);
        internal_counters.push_back(677);
        internal_counters.push_back(943);
        internal_counters.push_back(149);
        internal_counters.push_back(415);
        internal_counters.push_back(681);
        internal_counters.push_back(947);
        internal_counters.push_back(101);
        internal_counters.push_back(367);
        internal_counters.push_back(633);
        internal_counters.push_back(899);
        internal_counters.push_back(113);
        internal_counters.push_back(379);
        internal_counters.push_back(645);
        internal_counters.push_back(911);
        internal_counters.push_back(102);
        internal_counters.push_back(368);
        internal_counters.push_back(634);
        internal_counters.push_back(900);
        internal_counters.push_back(114);
        internal_counters.push_back(380);
        internal_counters.push_back(646);
        internal_counters.push_back(912);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PrimitiveAssemblyBusy", "Timing", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max,24,/,(100),*,(100),min", "54ac5640-c4d7-95e2-20e0-6a9fdfc07333");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(145);
        internal_counters.push_back(411);
        internal_counters.push_back(677);
        internal_counters.push_back(943);
        internal_counters.push_back(149);
        internal_counters.push_back(415);
        internal_counters.push_back(681);
        internal_counters.push_back(947);
        internal_counters.push_back(101);
        internal_counters.push_back(367);
        internal_counters.push_back(633);
        internal_counters.push_back(899);
        internal_counters.push_back(113);
        internal_counters.push_back(379);
        internal_counters.push_back(645);
        internal_counters.push_back(911);
        internal_counters.push_back(102);
        internal_counters.push_back(368);
        internal_counters.push_back(634);
        internal_counters.push_back(900);
        internal_counters.push_back(114);
        internal_counters.push_back(380);
        internal_counters.push_back(646);
        internal_counters.push_back(912);

        c.DefineDerivedCounter("PrimitiveAssemblyBusyCycles", "Timing", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max", "99777f2d-9626-c78a-a97c-c4505eba1e5f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(54);
        internal_counters.push_back(320);
        internal_counters.push_back(586);
        internal_counters.push_back(852);
        internal_counters.push_back(94);
        internal_counters.push_back(360);
        internal_counters.push_back(626);
        internal_counters.push_back(892);
        internal_counters.push_back(95);
        internal_counters.push_back(361);
        internal_counters.push_back(627);
        internal_counters.push_back(893);
        internal_counters.push_back(96);
        internal_counters.push_back(362);
        internal_counters.push_back(628);
        internal_counters.push_back(894);
        internal_counters.push_back(97);
        internal_counters.push_back(363);
        internal_counters.push_back(629);
        internal_counters.push_back(895);

        c.DefineDerivedCounter("CulledPrims", "PrimitiveAssembly", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,+,2,+,3,+,4,+,5,+,6,+,7,+,8,+,9,+,10,+,11,+,12,+,13,+,14,+,15,+,16,+,17,+,18,+,19,+", "589bdf55-9192-280a-41c3-584bc94f2562");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(61);
        internal_counters.push_back(327);
        internal_counters.push_back(593);
        internal_counters.push_back(859);

        c.DefineDerivedCounter("ClippedPrims", "PrimitiveAssembly", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "5ef6f9d5-155e-5baa-163f-8359d9ea9bbf");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(149);
        internal_counters.push_back(415);
        internal_counters.push_back(681);
        internal_counters.push_back(947);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PAStalledOnRasterizer", "PrimitiveAssembly", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,max,2,max,3,max,4,/,(100),*", "6f9f416b-53c1-0457-f88c-7b6ba8973974");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(149);
        internal_counters.push_back(415);
        internal_counters.push_back(681);
        internal_counters.push_back(947);

        c.DefineDerivedCounter("PAStalledOnRasterizerCycles", "PrimitiveAssembly", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,max,2,max,3,max", "7a8c492a-c566-9328-6805-760dbff5c0f2");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14382);
        internal_counters.push_back(14607);
        internal_counters.push_back(14832);
        internal_counters.push_back(15057);
        internal_counters.push_back(14387);
        internal_counters.push_back(14612);
        internal_counters.push_back(14837);
        internal_counters.push_back(15062);
        internal_counters.push_back(14392);
        internal_counters.push_back(14617);
        internal_counters.push_back(14842);
        internal_counters.push_back(15067);
        internal_counters.push_back(14397);
        internal_counters.push_back(14622);
        internal_counters.push_back(14847);
        internal_counters.push_back(15072);

        c.DefineDerivedCounter("PSPixelsOut", "PixelShader", "Pixels exported from shader to color buffers. Does not include killed or alpha tested pixels; if there are multiple render targets, each render target receives one export, so this will be 2 for 1 pixel written to two RTs.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "24cba16c-baa6-6ecd-95ad-92ecb1338da1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14384);
        internal_counters.push_back(14609);
        internal_counters.push_back(14834);
        internal_counters.push_back(15059);
        internal_counters.push_back(14389);
        internal_counters.push_back(14614);
        internal_counters.push_back(14839);
        internal_counters.push_back(15064);
        internal_counters.push_back(14394);
        internal_counters.push_back(14619);
        internal_counters.push_back(14844);
        internal_counters.push_back(15069);
        internal_counters.push_back(14399);
        internal_counters.push_back(14624);
        internal_counters.push_back(14849);
        internal_counters.push_back(15074);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PSExportStalls", "PixelShader", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "9b4f466c-ff97-22bb-557d-84d3c4c51895");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(14384);
        internal_counters.push_back(14609);
        internal_counters.push_back(14834);
        internal_counters.push_back(15059);
        internal_counters.push_back(14389);
        internal_counters.push_back(14614);
        internal_counters.push_back(14839);
        internal_counters.push_back(15064);
        internal_counters.push_back(14394);
        internal_counters.push_back(14619);
        internal_counters.push_back(14844);
        internal_counters.push_back(15069);
        internal_counters.push_back(14399);
        internal_counters.push_back(14624);
        internal_counters.push_back(14849);
        internal_counters.push_back(15074);

        c.DefineDerivedCounter("PSExportStallsCycles", "PixelShader", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "47c72aad-64e6-0864-d533-d8e0bc27c156");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(10338);
        internal_counters.push_back(10850);
        internal_counters.push_back(10278);
        internal_counters.push_back(10790);

        c.DefineDerivedCounter("PSVALUInstCount", "PixelShader", "Average number of vector ALU instructions executed in the PS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,sum2,2,3,sum2,/", "eb74389e-435c-4137-ecf1-39eb5bc1cbfe");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(10334);
        internal_counters.push_back(10846);
        internal_counters.push_back(10278);
        internal_counters.push_back(10790);

        c.DefineDerivedCounter("PSSALUInstCount", "PixelShader", "Average number of scalar ALU instructions executed in the PS. Affected by flow control.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,sum2,2,3,sum2,/", "e6a06580-8a82-96d6-976c-acc121fc5516");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(10391);
        internal_counters.push_back(10903);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PSVALUBusy", "PixelShader", "The percentage of GPUTime vector ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,sum2,NUM_SIMDS,/,2,/,(100),*", "6ce6fef7-8e33-10b4-f351-af755e177e85");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(10391);
        internal_counters.push_back(10903);

        c.DefineDerivedCounter("PSVALUBusyCycles", "PixelShader", "Number of GPU cycles where vector ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,sum2,NUM_SIMDS,/", "1e276f86-cd2a-72e7-fc9d-004f666f2981");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(10334);
        internal_counters.push_back(10846);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("PSSALUBusy", "PixelShader", "The percentage of GPUTime scalar ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,sum2,NUM_CUS,/,2,/,(100),*", "2ff9f34f-e94b-af4d-18c2-5fbbf6d1727a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(10334);
        internal_counters.push_back(10846);

        c.DefineDerivedCounter("PSSALUBusyCycles", "PixelShader", "Number of GPU cycles where scalar ALU instructions are being processed by the PS.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,sum2,NUM_CUS,/", "29808906-f128-b078-fc79-820a4b3b3b8d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSThreadGroups", "ComputeShader", "Total number of thread groups.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "8ce3fc80-56b2-97f9-8e70-2e8c747cea68");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(5569);
        internal_counters.push_back(5898);
        internal_counters.push_back(5575);
        internal_counters.push_back(5904);

        c.DefineDerivedCounter("CSWavefronts", "ComputeShader", "The total number of wavefronts used for the CS.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,sum4", "42379c6e-369b-c237-8b25-cdb9cdc65c4d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13354);
        internal_counters.push_back(13866);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSThreads", "ComputeShader", "The number of CS threads processed by the hardware.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,sum2,2,3,4,5,sum4,ifnotzero", "7a648013-6eac-2665-ac36-13c6f4ac9c26");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13354);
        internal_counters.push_back(13866);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSThreadGroupSize", "ComputeShader", "The number of CS threads within each thread group.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,sum2,2,3,4,5,sum4,/,2,3,4,5,sum4,ifnotzero", "8c65008a-9957-7ca6-4199-f6fe940420f6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13410);
        internal_counters.push_back(13922);
        internal_counters.push_back(13350);
        internal_counters.push_back(13862);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSVALUInsts", "ComputeShader", "The average number of vector ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),0,1,sum2,2,3,sum2,/,4,5,6,7,sum4,ifnotzero", "376cb1cc-5a40-9d1d-404c-f1736c0c5084");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13428);
        internal_counters.push_back(13940);
        internal_counters.push_back(13463);
        internal_counters.push_back(13975);
        internal_counters.push_back(13351);
        internal_counters.push_back(13863);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSVALUUtilization", "ComputeShader", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of the wave size. Value range: 0% (bad), 100% (ideal - no thread divergence).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(0),0,1,sum2,2,3,sum2,(64),(32),4,5,sum2,ifnotzero,*,/,(100),*,2,3,sum2,ifnotzero,(100),min,6,7,8,9,sum4,ifnotzero", "ae943d2a-76e1-bb68-e1e2-0e06c9031611");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13406);
        internal_counters.push_back(13918);
        internal_counters.push_back(13350);
        internal_counters.push_back(13862);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSSALUInsts", "ComputeShader", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero", "eb211144-8136-ff86-e8bf-4d0493a904cb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13415);
        internal_counters.push_back(13927);
        internal_counters.push_back(13350);
        internal_counters.push_back(13862);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSVFetchInsts", "ComputeShader", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero", "3e2829c0-6215-783b-c271-6d57ff2c520e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13407);
        internal_counters.push_back(13919);
        internal_counters.push_back(13350);
        internal_counters.push_back(13862);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSSFetchInsts", "ComputeShader", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero", "da09171c-6a0a-584f-fddc-dc5062d63a3e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13416);
        internal_counters.push_back(13928);
        internal_counters.push_back(13350);
        internal_counters.push_back(13862);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSVWriteInsts", "ComputeShader", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero", "43438c22-e910-b377-b767-b32902e0df0d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13463);
        internal_counters.push_back(13975);
        internal_counters.push_back(24);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSVALUBusy", "ComputeShader", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,sum2,NUM_SIMDS,/,2,/,(100),*,3,4,5,6,sum4,ifnotzero", "f1e64815-f6a8-c277-d4f9-d054b443e205");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13463);
        internal_counters.push_back(13975);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSVALUBusyCycles", "ComputeShader", "Number of GPU cycles where vector ALU instructions are processed.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,sum2,NUM_SIMDS,/,2,3,4,5,sum4,ifnotzero", "2d0d5852-2658-eb73-68d2-f23f7118c9c3");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13406);
        internal_counters.push_back(13918);
        internal_counters.push_back(24);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSSALUBusy", "ComputeShader", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,sum2,NUM_CUS,/,2,/,(100),*,3,4,5,6,sum4,ifnotzero", "3fc35f4e-9882-94e3-6f5f-4e81cd97082a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13406);
        internal_counters.push_back(13918);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSSALUBusyCycles", "ComputeShader", "Number of GPU cycles where scalar ALU instructions are processed.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,sum2,NUM_CUS,/,2,3,4,5,sum4,ifnotzero", "de58f8fc-8ed4-a799-648d-62ded7b1c4c4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15285);
        internal_counters.push_back(15511);
        internal_counters.push_back(15737);
        internal_counters.push_back(15963);
        internal_counters.push_back(16189);
        internal_counters.push_back(16415);
        internal_counters.push_back(16641);
        internal_counters.push_back(16867);
        internal_counters.push_back(17093);
        internal_counters.push_back(17319);
        internal_counters.push_back(17545);
        internal_counters.push_back(17771);
        internal_counters.push_back(17997);
        internal_counters.push_back(18223);
        internal_counters.push_back(18449);
        internal_counters.push_back(18675);
        internal_counters.push_back(18901);
        internal_counters.push_back(19127);
        internal_counters.push_back(19353);
        internal_counters.push_back(19579);
        internal_counters.push_back(19805);
        internal_counters.push_back(20031);
        internal_counters.push_back(20257);
        internal_counters.push_back(20483);
        internal_counters.push_back(20709);
        internal_counters.push_back(20935);
        internal_counters.push_back(21161);
        internal_counters.push_back(21387);
        internal_counters.push_back(21613);
        internal_counters.push_back(21839);
        internal_counters.push_back(22065);
        internal_counters.push_back(22291);
        internal_counters.push_back(22517);
        internal_counters.push_back(22743);
        internal_counters.push_back(22969);
        internal_counters.push_back(23195);
        internal_counters.push_back(23421);
        internal_counters.push_back(23647);
        internal_counters.push_back(23873);
        internal_counters.push_back(24099);
        internal_counters.push_back(24);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSMemUnitBusy", "ComputeShader", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,/,(100),*,41,42,43,44,sum4,ifnotzero", "42ab96e1-0a24-96c8-c4ff-098fa267d78e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15285);
        internal_counters.push_back(15511);
        internal_counters.push_back(15737);
        internal_counters.push_back(15963);
        internal_counters.push_back(16189);
        internal_counters.push_back(16415);
        internal_counters.push_back(16641);
        internal_counters.push_back(16867);
        internal_counters.push_back(17093);
        internal_counters.push_back(17319);
        internal_counters.push_back(17545);
        internal_counters.push_back(17771);
        internal_counters.push_back(17997);
        internal_counters.push_back(18223);
        internal_counters.push_back(18449);
        internal_counters.push_back(18675);
        internal_counters.push_back(18901);
        internal_counters.push_back(19127);
        internal_counters.push_back(19353);
        internal_counters.push_back(19579);
        internal_counters.push_back(19805);
        internal_counters.push_back(20031);
        internal_counters.push_back(20257);
        internal_counters.push_back(20483);
        internal_counters.push_back(20709);
        internal_counters.push_back(20935);
        internal_counters.push_back(21161);
        internal_counters.push_back(21387);
        internal_counters.push_back(21613);
        internal_counters.push_back(21839);
        internal_counters.push_back(22065);
        internal_counters.push_back(22291);
        internal_counters.push_back(22517);
        internal_counters.push_back(22743);
        internal_counters.push_back(22969);
        internal_counters.push_back(23195);
        internal_counters.push_back(23421);
        internal_counters.push_back(23647);
        internal_counters.push_back(23873);
        internal_counters.push_back(24099);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSMemUnitBusyCycles", "ComputeShader", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,41,42,43,sum4,ifnotzero", "39d5687f-c727-7c0c-af82-bb711d3897ed");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(26786);
        internal_counters.push_back(26863);
        internal_counters.push_back(26940);
        internal_counters.push_back(27017);
        internal_counters.push_back(27094);
        internal_counters.push_back(27171);
        internal_counters.push_back(27248);
        internal_counters.push_back(27325);
        internal_counters.push_back(27402);
        internal_counters.push_back(27479);
        internal_counters.push_back(27556);
        internal_counters.push_back(27633);
        internal_counters.push_back(27710);
        internal_counters.push_back(27787);
        internal_counters.push_back(27864);
        internal_counters.push_back(27941);
        internal_counters.push_back(28018);
        internal_counters.push_back(28095);
        internal_counters.push_back(28172);
        internal_counters.push_back(28249);
        internal_counters.push_back(28326);
        internal_counters.push_back(28403);
        internal_counters.push_back(28480);
        internal_counters.push_back(28557);
        internal_counters.push_back(28634);
        internal_counters.push_back(28711);
        internal_counters.push_back(28788);
        internal_counters.push_back(28865);
        internal_counters.push_back(28942);
        internal_counters.push_back(29019);
        internal_counters.push_back(29096);
        internal_counters.push_back(29173);
        internal_counters.push_back(29250);
        internal_counters.push_back(29327);
        internal_counters.push_back(29404);
        internal_counters.push_back(29481);
        internal_counters.push_back(29558);
        internal_counters.push_back(29635);
        internal_counters.push_back(29712);
        internal_counters.push_back(29789);
        internal_counters.push_back(24);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSMemUnitStalled", "ComputeShader", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,/,(100),*,41,42,43,44,sum4,ifnotzero", "f18e8679-1511-d533-d9ee-4365197f7d0c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(26786);
        internal_counters.push_back(26863);
        internal_counters.push_back(26940);
        internal_counters.push_back(27017);
        internal_counters.push_back(27094);
        internal_counters.push_back(27171);
        internal_counters.push_back(27248);
        internal_counters.push_back(27325);
        internal_counters.push_back(27402);
        internal_counters.push_back(27479);
        internal_counters.push_back(27556);
        internal_counters.push_back(27633);
        internal_counters.push_back(27710);
        internal_counters.push_back(27787);
        internal_counters.push_back(27864);
        internal_counters.push_back(27941);
        internal_counters.push_back(28018);
        internal_counters.push_back(28095);
        internal_counters.push_back(28172);
        internal_counters.push_back(28249);
        internal_counters.push_back(28326);
        internal_counters.push_back(28403);
        internal_counters.push_back(28480);
        internal_counters.push_back(28557);
        internal_counters.push_back(28634);
        internal_counters.push_back(28711);
        internal_counters.push_back(28788);
        internal_counters.push_back(28865);
        internal_counters.push_back(28942);
        internal_counters.push_back(29019);
        internal_counters.push_back(29096);
        internal_counters.push_back(29173);
        internal_counters.push_back(29250);
        internal_counters.push_back(29327);
        internal_counters.push_back(29404);
        internal_counters.push_back(29481);
        internal_counters.push_back(29558);
        internal_counters.push_back(29635);
        internal_counters.push_back(29712);
        internal_counters.push_back(29789);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSMemUnitStalledCycles", "ComputeShader", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,41,42,43,sum4,ifnotzero", "51991c84-ed2b-bf31-c4ab-8f8e9eb8f29f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52822);
        internal_counters.push_back(53057);
        internal_counters.push_back(53292);
        internal_counters.push_back(53527);
        internal_counters.push_back(53762);
        internal_counters.push_back(53997);
        internal_counters.push_back(54232);
        internal_counters.push_back(54467);
        internal_counters.push_back(54702);
        internal_counters.push_back(54937);
        internal_counters.push_back(55172);
        internal_counters.push_back(55407);
        internal_counters.push_back(55642);
        internal_counters.push_back(55877);
        internal_counters.push_back(56112);
        internal_counters.push_back(56347);
        internal_counters.push_back(24);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSWriteUnitStalled", "ComputeShader", "The percentage of GPUTime the write unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,18,19,20,sum4,ifnotzero", "55118f7a-8f92-726f-78c6-407f689a2eb4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52822);
        internal_counters.push_back(53057);
        internal_counters.push_back(53292);
        internal_counters.push_back(53527);
        internal_counters.push_back(53762);
        internal_counters.push_back(53997);
        internal_counters.push_back(54232);
        internal_counters.push_back(54467);
        internal_counters.push_back(54702);
        internal_counters.push_back(54937);
        internal_counters.push_back(55172);
        internal_counters.push_back(55407);
        internal_counters.push_back(55642);
        internal_counters.push_back(55877);
        internal_counters.push_back(56112);
        internal_counters.push_back(56347);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSWriteUnitStalledCycles", "ComputeShader", "Number of GPU cycles the write unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,17,18,19,sum4,ifnotzero", "be164c60-5e48-acac-9622-29616d09aa9a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13401);
        internal_counters.push_back(13913);
        internal_counters.push_back(13350);
        internal_counters.push_back(13862);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSGDSInsts", "ComputeShader", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero", "2a867f3e-4a37-ad16-55d1-f03d74707819");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13405);
        internal_counters.push_back(13917);
        internal_counters.push_back(13350);
        internal_counters.push_back(13862);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSLDSInsts", "ComputeShader", "The average number of LDS read/write instructions executed per work-item (affected by flow control).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "(0),(0),0,1,sum2,2,3,sum2,/,2,3,sum2,ifnotzero,4,5,6,7,sum4,ifnotzero", "61b0b351-7e06-ef8e-a8e0-7a9e3200a836");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13377);
        internal_counters.push_back(13889);
        internal_counters.push_back(13350);
        internal_counters.push_back(13862);
        internal_counters.push_back(24);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSALUStalledByLDS", "ComputeShader", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(0),0,1,sum2,2,3,sum2,/,4,/,NUM_SHADER_ENGINES,/,(100),*,2,3,sum2,ifnotzero,5,6,7,8,sum4,ifnotzero", "6dc4f1c2-bad0-c9ff-156e-883b319a752a");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13377);
        internal_counters.push_back(13889);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSALUStalledByLDSCycles", "ComputeShader", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,sum2,NUM_SHADER_ENGINES,/,2,3,4,5,sum4,ifnotzero", "8f3d5f25-2159-0374-fafe-e26a7799b6c8");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13631);
        internal_counters.push_back(14143);
        internal_counters.push_back(24);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSLDSBankConflict", "ComputeShader", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),0,1,sum2,2,/,NUM_SIMDS,/,(100),*,3,4,5,6,sum4,ifnotzero", "1065ee10-2e41-ea41-1eb3-b61b491752f4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(13631);
        internal_counters.push_back(14143);
        internal_counters.push_back(5566);
        internal_counters.push_back(5895);
        internal_counters.push_back(5572);
        internal_counters.push_back(5901);

        c.DefineDerivedCounter("CSLDSBankConflictCycles", "ComputeShader", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad).", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "(0),0,1,sum2,NUM_SIMDS,/,2,3,4,5,sum4,ifnotzero", "1fd1adf3-c51e-94fd-083e-c482a0a0809e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15285);
        internal_counters.push_back(15511);
        internal_counters.push_back(15737);
        internal_counters.push_back(15963);
        internal_counters.push_back(16189);
        internal_counters.push_back(16415);
        internal_counters.push_back(16641);
        internal_counters.push_back(16867);
        internal_counters.push_back(17093);
        internal_counters.push_back(17319);
        internal_counters.push_back(17545);
        internal_counters.push_back(17771);
        internal_counters.push_back(17997);
        internal_counters.push_back(18223);
        internal_counters.push_back(18449);
        internal_counters.push_back(18675);
        internal_counters.push_back(18901);
        internal_counters.push_back(19127);
        internal_counters.push_back(19353);
        internal_counters.push_back(19579);
        internal_counters.push_back(19805);
        internal_counters.push_back(20031);
        internal_counters.push_back(20257);
        internal_counters.push_back(20483);
        internal_counters.push_back(20709);
        internal_counters.push_back(20935);
        internal_counters.push_back(21161);
        internal_counters.push_back(21387);
        internal_counters.push_back(21613);
        internal_counters.push_back(21839);
        internal_counters.push_back(22065);
        internal_counters.push_back(22291);
        internal_counters.push_back(22517);
        internal_counters.push_back(22743);
        internal_counters.push_back(22969);
        internal_counters.push_back(23195);
        internal_counters.push_back(23421);
        internal_counters.push_back(23647);
        internal_counters.push_back(23873);
        internal_counters.push_back(24099);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("TexUnitBusy", "Timing", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,/,(100),*", "36afb8d9-42fc-aafe-66c5-449542153b2c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15285);
        internal_counters.push_back(15511);
        internal_counters.push_back(15737);
        internal_counters.push_back(15963);
        internal_counters.push_back(16189);
        internal_counters.push_back(16415);
        internal_counters.push_back(16641);
        internal_counters.push_back(16867);
        internal_counters.push_back(17093);
        internal_counters.push_back(17319);
        internal_counters.push_back(17545);
        internal_counters.push_back(17771);
        internal_counters.push_back(17997);
        internal_counters.push_back(18223);
        internal_counters.push_back(18449);
        internal_counters.push_back(18675);
        internal_counters.push_back(18901);
        internal_counters.push_back(19127);
        internal_counters.push_back(19353);
        internal_counters.push_back(19579);
        internal_counters.push_back(19805);
        internal_counters.push_back(20031);
        internal_counters.push_back(20257);
        internal_counters.push_back(20483);
        internal_counters.push_back(20709);
        internal_counters.push_back(20935);
        internal_counters.push_back(21161);
        internal_counters.push_back(21387);
        internal_counters.push_back(21613);
        internal_counters.push_back(21839);
        internal_counters.push_back(22065);
        internal_counters.push_back(22291);
        internal_counters.push_back(22517);
        internal_counters.push_back(22743);
        internal_counters.push_back(22969);
        internal_counters.push_back(23195);
        internal_counters.push_back(23421);
        internal_counters.push_back(23647);
        internal_counters.push_back(23873);
        internal_counters.push_back(24099);

        c.DefineDerivedCounter("TexUnitBusyCycles", "Timing", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40", "c68761f2-248c-4f39-6528-c308b1c0807c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15339);
        internal_counters.push_back(15565);
        internal_counters.push_back(15791);
        internal_counters.push_back(16017);
        internal_counters.push_back(16243);
        internal_counters.push_back(16469);
        internal_counters.push_back(16695);
        internal_counters.push_back(16921);
        internal_counters.push_back(17147);
        internal_counters.push_back(17373);
        internal_counters.push_back(17599);
        internal_counters.push_back(17825);
        internal_counters.push_back(18051);
        internal_counters.push_back(18277);
        internal_counters.push_back(18503);
        internal_counters.push_back(18729);
        internal_counters.push_back(18955);
        internal_counters.push_back(19181);
        internal_counters.push_back(19407);
        internal_counters.push_back(19633);
        internal_counters.push_back(19859);
        internal_counters.push_back(20085);
        internal_counters.push_back(20311);
        internal_counters.push_back(20537);
        internal_counters.push_back(20763);
        internal_counters.push_back(20989);
        internal_counters.push_back(21215);
        internal_counters.push_back(21441);
        internal_counters.push_back(21667);
        internal_counters.push_back(21893);
        internal_counters.push_back(22119);
        internal_counters.push_back(22345);
        internal_counters.push_back(22571);
        internal_counters.push_back(22797);
        internal_counters.push_back(23023);
        internal_counters.push_back(23249);
        internal_counters.push_back(23475);
        internal_counters.push_back(23701);
        internal_counters.push_back(23927);
        internal_counters.push_back(24153);
        internal_counters.push_back(15338);
        internal_counters.push_back(15564);
        internal_counters.push_back(15790);
        internal_counters.push_back(16016);
        internal_counters.push_back(16242);
        internal_counters.push_back(16468);
        internal_counters.push_back(16694);
        internal_counters.push_back(16920);
        internal_counters.push_back(17146);
        internal_counters.push_back(17372);
        internal_counters.push_back(17598);
        internal_counters.push_back(17824);
        internal_counters.push_back(18050);
        internal_counters.push_back(18276);
        internal_counters.push_back(18502);
        internal_counters.push_back(18728);
        internal_counters.push_back(18954);
        internal_counters.push_back(19180);
        internal_counters.push_back(19406);
        internal_counters.push_back(19632);
        internal_counters.push_back(19858);
        internal_counters.push_back(20084);
        internal_counters.push_back(20310);
        internal_counters.push_back(20536);
        internal_counters.push_back(20762);
        internal_counters.push_back(20988);
        internal_counters.push_back(21214);
        internal_counters.push_back(21440);
        internal_counters.push_back(21666);
        internal_counters.push_back(21892);
        internal_counters.push_back(22118);
        internal_counters.push_back(22344);
        internal_counters.push_back(22570);
        internal_counters.push_back(22796);
        internal_counters.push_back(23022);
        internal_counters.push_back(23248);
        internal_counters.push_back(23474);
        internal_counters.push_back(23700);
        internal_counters.push_back(23926);
        internal_counters.push_back(24152);

        c.DefineDerivedCounter("TexTriFilteringPct", "TextureUnit", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,+,/,(100),*", "1affc3c8-b917-5c81-622b-7004527208ae");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15339);
        internal_counters.push_back(15565);
        internal_counters.push_back(15791);
        internal_counters.push_back(16017);
        internal_counters.push_back(16243);
        internal_counters.push_back(16469);
        internal_counters.push_back(16695);
        internal_counters.push_back(16921);
        internal_counters.push_back(17147);
        internal_counters.push_back(17373);
        internal_counters.push_back(17599);
        internal_counters.push_back(17825);
        internal_counters.push_back(18051);
        internal_counters.push_back(18277);
        internal_counters.push_back(18503);
        internal_counters.push_back(18729);
        internal_counters.push_back(18955);
        internal_counters.push_back(19181);
        internal_counters.push_back(19407);
        internal_counters.push_back(19633);
        internal_counters.push_back(19859);
        internal_counters.push_back(20085);
        internal_counters.push_back(20311);
        internal_counters.push_back(20537);
        internal_counters.push_back(20763);
        internal_counters.push_back(20989);
        internal_counters.push_back(21215);
        internal_counters.push_back(21441);
        internal_counters.push_back(21667);
        internal_counters.push_back(21893);
        internal_counters.push_back(22119);
        internal_counters.push_back(22345);
        internal_counters.push_back(22571);
        internal_counters.push_back(22797);
        internal_counters.push_back(23023);
        internal_counters.push_back(23249);
        internal_counters.push_back(23475);
        internal_counters.push_back(23701);
        internal_counters.push_back(23927);
        internal_counters.push_back(24153);

        c.DefineDerivedCounter("TexTriFilteringCount", "TextureUnit", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40", "5785b3a1-a513-18db-4b1c-bdeef75bb2b6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15338);
        internal_counters.push_back(15564);
        internal_counters.push_back(15790);
        internal_counters.push_back(16016);
        internal_counters.push_back(16242);
        internal_counters.push_back(16468);
        internal_counters.push_back(16694);
        internal_counters.push_back(16920);
        internal_counters.push_back(17146);
        internal_counters.push_back(17372);
        internal_counters.push_back(17598);
        internal_counters.push_back(17824);
        internal_counters.push_back(18050);
        internal_counters.push_back(18276);
        internal_counters.push_back(18502);
        internal_counters.push_back(18728);
        internal_counters.push_back(18954);
        internal_counters.push_back(19180);
        internal_counters.push_back(19406);
        internal_counters.push_back(19632);
        internal_counters.push_back(19858);
        internal_counters.push_back(20084);
        internal_counters.push_back(20310);
        internal_counters.push_back(20536);
        internal_counters.push_back(20762);
        internal_counters.push_back(20988);
        internal_counters.push_back(21214);
        internal_counters.push_back(21440);
        internal_counters.push_back(21666);
        internal_counters.push_back(21892);
        internal_counters.push_back(22118);
        internal_counters.push_back(22344);
        internal_counters.push_back(22570);
        internal_counters.push_back(22796);
        internal_counters.push_back(23022);
        internal_counters.push_back(23248);
        internal_counters.push_back(23474);
        internal_counters.push_back(23700);
        internal_counters.push_back(23926);
        internal_counters.push_back(24152);

        c.DefineDerivedCounter("NoTexTriFilteringCount", "TextureUnit", "Count of pixels that did not receive trilinear filtering.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40", "179da29a-81af-c06e-ce8c-a0a731ea030d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15341);
        internal_counters.push_back(15567);
        internal_counters.push_back(15793);
        internal_counters.push_back(16019);
        internal_counters.push_back(16245);
        internal_counters.push_back(16471);
        internal_counters.push_back(16697);
        internal_counters.push_back(16923);
        internal_counters.push_back(17149);
        internal_counters.push_back(17375);
        internal_counters.push_back(17601);
        internal_counters.push_back(17827);
        internal_counters.push_back(18053);
        internal_counters.push_back(18279);
        internal_counters.push_back(18505);
        internal_counters.push_back(18731);
        internal_counters.push_back(18957);
        internal_counters.push_back(19183);
        internal_counters.push_back(19409);
        internal_counters.push_back(19635);
        internal_counters.push_back(19861);
        internal_counters.push_back(20087);
        internal_counters.push_back(20313);
        internal_counters.push_back(20539);
        internal_counters.push_back(20765);
        internal_counters.push_back(20991);
        internal_counters.push_back(21217);
        internal_counters.push_back(21443);
        internal_counters.push_back(21669);
        internal_counters.push_back(21895);
        internal_counters.push_back(22121);
        internal_counters.push_back(22347);
        internal_counters.push_back(22573);
        internal_counters.push_back(22799);
        internal_counters.push_back(23025);
        internal_counters.push_back(23251);
        internal_counters.push_back(23477);
        internal_counters.push_back(23703);
        internal_counters.push_back(23929);
        internal_counters.push_back(24155);
        internal_counters.push_back(15340);
        internal_counters.push_back(15566);
        internal_counters.push_back(15792);
        internal_counters.push_back(16018);
        internal_counters.push_back(16244);
        internal_counters.push_back(16470);
        internal_counters.push_back(16696);
        internal_counters.push_back(16922);
        internal_counters.push_back(17148);
        internal_counters.push_back(17374);
        internal_counters.push_back(17600);
        internal_counters.push_back(17826);
        internal_counters.push_back(18052);
        internal_counters.push_back(18278);
        internal_counters.push_back(18504);
        internal_counters.push_back(18730);
        internal_counters.push_back(18956);
        internal_counters.push_back(19182);
        internal_counters.push_back(19408);
        internal_counters.push_back(19634);
        internal_counters.push_back(19860);
        internal_counters.push_back(20086);
        internal_counters.push_back(20312);
        internal_counters.push_back(20538);
        internal_counters.push_back(20764);
        internal_counters.push_back(20990);
        internal_counters.push_back(21216);
        internal_counters.push_back(21442);
        internal_counters.push_back(21668);
        internal_counters.push_back(21894);
        internal_counters.push_back(22120);
        internal_counters.push_back(22346);
        internal_counters.push_back(22572);
        internal_counters.push_back(22798);
        internal_counters.push_back(23024);
        internal_counters.push_back(23250);
        internal_counters.push_back(23476);
        internal_counters.push_back(23702);
        internal_counters.push_back(23928);
        internal_counters.push_back(24154);

        c.DefineDerivedCounter("TexVolFilteringPct", "TextureUnit", "Percentage of pixels that received volume filtering.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,+,/,(100),*", "b5ff6bed-3178-aee4-42dd-c74391c02a2d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15341);
        internal_counters.push_back(15567);
        internal_counters.push_back(15793);
        internal_counters.push_back(16019);
        internal_counters.push_back(16245);
        internal_counters.push_back(16471);
        internal_counters.push_back(16697);
        internal_counters.push_back(16923);
        internal_counters.push_back(17149);
        internal_counters.push_back(17375);
        internal_counters.push_back(17601);
        internal_counters.push_back(17827);
        internal_counters.push_back(18053);
        internal_counters.push_back(18279);
        internal_counters.push_back(18505);
        internal_counters.push_back(18731);
        internal_counters.push_back(18957);
        internal_counters.push_back(19183);
        internal_counters.push_back(19409);
        internal_counters.push_back(19635);
        internal_counters.push_back(19861);
        internal_counters.push_back(20087);
        internal_counters.push_back(20313);
        internal_counters.push_back(20539);
        internal_counters.push_back(20765);
        internal_counters.push_back(20991);
        internal_counters.push_back(21217);
        internal_counters.push_back(21443);
        internal_counters.push_back(21669);
        internal_counters.push_back(21895);
        internal_counters.push_back(22121);
        internal_counters.push_back(22347);
        internal_counters.push_back(22573);
        internal_counters.push_back(22799);
        internal_counters.push_back(23025);
        internal_counters.push_back(23251);
        internal_counters.push_back(23477);
        internal_counters.push_back(23703);
        internal_counters.push_back(23929);
        internal_counters.push_back(24155);

        c.DefineDerivedCounter("TexVolFilteringCount", "TextureUnit", "Count of pixels that received volume filtering.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40", "4bddc587-d589-8128-e18c-762eab2c871f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15340);
        internal_counters.push_back(15566);
        internal_counters.push_back(15792);
        internal_counters.push_back(16018);
        internal_counters.push_back(16244);
        internal_counters.push_back(16470);
        internal_counters.push_back(16696);
        internal_counters.push_back(16922);
        internal_counters.push_back(17148);
        internal_counters.push_back(17374);
        internal_counters.push_back(17600);
        internal_counters.push_back(17826);
        internal_counters.push_back(18052);
        internal_counters.push_back(18278);
        internal_counters.push_back(18504);
        internal_counters.push_back(18730);
        internal_counters.push_back(18956);
        internal_counters.push_back(19182);
        internal_counters.push_back(19408);
        internal_counters.push_back(19634);
        internal_counters.push_back(19860);
        internal_counters.push_back(20086);
        internal_counters.push_back(20312);
        internal_counters.push_back(20538);
        internal_counters.push_back(20764);
        internal_counters.push_back(20990);
        internal_counters.push_back(21216);
        internal_counters.push_back(21442);
        internal_counters.push_back(21668);
        internal_counters.push_back(21894);
        internal_counters.push_back(22120);
        internal_counters.push_back(22346);
        internal_counters.push_back(22572);
        internal_counters.push_back(22798);
        internal_counters.push_back(23024);
        internal_counters.push_back(23250);
        internal_counters.push_back(23476);
        internal_counters.push_back(23702);
        internal_counters.push_back(23928);
        internal_counters.push_back(24154);

        c.DefineDerivedCounter("NoTexVolFilteringCount", "TextureUnit", "Count of pixels that did not receive volume filtering.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40", "9fe1a854-17c6-9d26-b2b9-80610cd5827d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15359);
        internal_counters.push_back(15585);
        internal_counters.push_back(15811);
        internal_counters.push_back(16037);
        internal_counters.push_back(16263);
        internal_counters.push_back(16489);
        internal_counters.push_back(16715);
        internal_counters.push_back(16941);
        internal_counters.push_back(17167);
        internal_counters.push_back(17393);
        internal_counters.push_back(17619);
        internal_counters.push_back(17845);
        internal_counters.push_back(18071);
        internal_counters.push_back(18297);
        internal_counters.push_back(18523);
        internal_counters.push_back(18749);
        internal_counters.push_back(18975);
        internal_counters.push_back(19201);
        internal_counters.push_back(19427);
        internal_counters.push_back(19653);
        internal_counters.push_back(19879);
        internal_counters.push_back(20105);
        internal_counters.push_back(20331);
        internal_counters.push_back(20557);
        internal_counters.push_back(20783);
        internal_counters.push_back(21009);
        internal_counters.push_back(21235);
        internal_counters.push_back(21461);
        internal_counters.push_back(21687);
        internal_counters.push_back(21913);
        internal_counters.push_back(22139);
        internal_counters.push_back(22365);
        internal_counters.push_back(22591);
        internal_counters.push_back(22817);
        internal_counters.push_back(23043);
        internal_counters.push_back(23269);
        internal_counters.push_back(23495);
        internal_counters.push_back(23721);
        internal_counters.push_back(23947);
        internal_counters.push_back(24173);
        internal_counters.push_back(15360);
        internal_counters.push_back(15586);
        internal_counters.push_back(15812);
        internal_counters.push_back(16038);
        internal_counters.push_back(16264);
        internal_counters.push_back(16490);
        internal_counters.push_back(16716);
        internal_counters.push_back(16942);
        internal_counters.push_back(17168);
        internal_counters.push_back(17394);
        internal_counters.push_back(17620);
        internal_counters.push_back(17846);
        internal_counters.push_back(18072);
        internal_counters.push_back(18298);
        internal_counters.push_back(18524);
        internal_counters.push_back(18750);
        internal_counters.push_back(18976);
        internal_counters.push_back(19202);
        internal_counters.push_back(19428);
        internal_counters.push_back(19654);
        internal_counters.push_back(19880);
        internal_counters.push_back(20106);
        internal_counters.push_back(20332);
        internal_counters.push_back(20558);
        internal_counters.push_back(20784);
        internal_counters.push_back(21010);
        internal_counters.push_back(21236);
        internal_counters.push_back(21462);
        internal_counters.push_back(21688);
        internal_counters.push_back(21914);
        internal_counters.push_back(22140);
        internal_counters.push_back(22366);
        internal_counters.push_back(22592);
        internal_counters.push_back(22818);
        internal_counters.push_back(23044);
        internal_counters.push_back(23270);
        internal_counters.push_back(23496);
        internal_counters.push_back(23722);
        internal_counters.push_back(23948);
        internal_counters.push_back(24174);
        internal_counters.push_back(15361);
        internal_counters.push_back(15587);
        internal_counters.push_back(15813);
        internal_counters.push_back(16039);
        internal_counters.push_back(16265);
        internal_counters.push_back(16491);
        internal_counters.push_back(16717);
        internal_counters.push_back(16943);
        internal_counters.push_back(17169);
        internal_counters.push_back(17395);
        internal_counters.push_back(17621);
        internal_counters.push_back(17847);
        internal_counters.push_back(18073);
        internal_counters.push_back(18299);
        internal_counters.push_back(18525);
        internal_counters.push_back(18751);
        internal_counters.push_back(18977);
        internal_counters.push_back(19203);
        internal_counters.push_back(19429);
        internal_counters.push_back(19655);
        internal_counters.push_back(19881);
        internal_counters.push_back(20107);
        internal_counters.push_back(20333);
        internal_counters.push_back(20559);
        internal_counters.push_back(20785);
        internal_counters.push_back(21011);
        internal_counters.push_back(21237);
        internal_counters.push_back(21463);
        internal_counters.push_back(21689);
        internal_counters.push_back(21915);
        internal_counters.push_back(22141);
        internal_counters.push_back(22367);
        internal_counters.push_back(22593);
        internal_counters.push_back(22819);
        internal_counters.push_back(23045);
        internal_counters.push_back(23271);
        internal_counters.push_back(23497);
        internal_counters.push_back(23723);
        internal_counters.push_back(23949);
        internal_counters.push_back(24175);
        internal_counters.push_back(15362);
        internal_counters.push_back(15588);
        internal_counters.push_back(15814);
        internal_counters.push_back(16040);
        internal_counters.push_back(16266);
        internal_counters.push_back(16492);
        internal_counters.push_back(16718);
        internal_counters.push_back(16944);
        internal_counters.push_back(17170);
        internal_counters.push_back(17396);
        internal_counters.push_back(17622);
        internal_counters.push_back(17848);
        internal_counters.push_back(18074);
        internal_counters.push_back(18300);
        internal_counters.push_back(18526);
        internal_counters.push_back(18752);
        internal_counters.push_back(18978);
        internal_counters.push_back(19204);
        internal_counters.push_back(19430);
        internal_counters.push_back(19656);
        internal_counters.push_back(19882);
        internal_counters.push_back(20108);
        internal_counters.push_back(20334);
        internal_counters.push_back(20560);
        internal_counters.push_back(20786);
        internal_counters.push_back(21012);
        internal_counters.push_back(21238);
        internal_counters.push_back(21464);
        internal_counters.push_back(21690);
        internal_counters.push_back(21916);
        internal_counters.push_back(22142);
        internal_counters.push_back(22368);
        internal_counters.push_back(22594);
        internal_counters.push_back(22820);
        internal_counters.push_back(23046);
        internal_counters.push_back(23272);
        internal_counters.push_back(23498);
        internal_counters.push_back(23724);
        internal_counters.push_back(23950);
        internal_counters.push_back(24176);
        internal_counters.push_back(15363);
        internal_counters.push_back(15589);
        internal_counters.push_back(15815);
        internal_counters.push_back(16041);
        internal_counters.push_back(16267);
        internal_counters.push_back(16493);
        internal_counters.push_back(16719);
        internal_counters.push_back(16945);
        internal_counters.push_back(17171);
        internal_counters.push_back(17397);
        internal_counters.push_back(17623);
        internal_counters.push_back(17849);
        internal_counters.push_back(18075);
        internal_counters.push_back(18301);
        internal_counters.push_back(18527);
        internal_counters.push_back(18753);
        internal_counters.push_back(18979);
        internal_counters.push_back(19205);
        internal_counters.push_back(19431);
        internal_counters.push_back(19657);
        internal_counters.push_back(19883);
        internal_counters.push_back(20109);
        internal_counters.push_back(20335);
        internal_counters.push_back(20561);
        internal_counters.push_back(20787);
        internal_counters.push_back(21013);
        internal_counters.push_back(21239);
        internal_counters.push_back(21465);
        internal_counters.push_back(21691);
        internal_counters.push_back(21917);
        internal_counters.push_back(22143);
        internal_counters.push_back(22369);
        internal_counters.push_back(22595);
        internal_counters.push_back(22821);
        internal_counters.push_back(23047);
        internal_counters.push_back(23273);
        internal_counters.push_back(23499);
        internal_counters.push_back(23725);
        internal_counters.push_back(23951);
        internal_counters.push_back(24177);
        internal_counters.push_back(15364);
        internal_counters.push_back(15590);
        internal_counters.push_back(15816);
        internal_counters.push_back(16042);
        internal_counters.push_back(16268);
        internal_counters.push_back(16494);
        internal_counters.push_back(16720);
        internal_counters.push_back(16946);
        internal_counters.push_back(17172);
        internal_counters.push_back(17398);
        internal_counters.push_back(17624);
        internal_counters.push_back(17850);
        internal_counters.push_back(18076);
        internal_counters.push_back(18302);
        internal_counters.push_back(18528);
        internal_counters.push_back(18754);
        internal_counters.push_back(18980);
        internal_counters.push_back(19206);
        internal_counters.push_back(19432);
        internal_counters.push_back(19658);
        internal_counters.push_back(19884);
        internal_counters.push_back(20110);
        internal_counters.push_back(20336);
        internal_counters.push_back(20562);
        internal_counters.push_back(20788);
        internal_counters.push_back(21014);
        internal_counters.push_back(21240);
        internal_counters.push_back(21466);
        internal_counters.push_back(21692);
        internal_counters.push_back(21918);
        internal_counters.push_back(22144);
        internal_counters.push_back(22370);
        internal_counters.push_back(22596);
        internal_counters.push_back(22822);
        internal_counters.push_back(23048);
        internal_counters.push_back(23274);
        internal_counters.push_back(23500);
        internal_counters.push_back(23726);
        internal_counters.push_back(23952);
        internal_counters.push_back(24178);
        internal_counters.push_back(15365);
        internal_counters.push_back(15591);
        internal_counters.push_back(15817);
        internal_counters.push_back(16043);
        internal_counters.push_back(16269);
        internal_counters.push_back(16495);
        internal_counters.push_back(16721);
        internal_counters.push_back(16947);
        internal_counters.push_back(17173);
        internal_counters.push_back(17399);
        internal_counters.push_back(17625);
        internal_counters.push_back(17851);
        internal_counters.push_back(18077);
        internal_counters.push_back(18303);
        internal_counters.push_back(18529);
        internal_counters.push_back(18755);
        internal_counters.push_back(18981);
        internal_counters.push_back(19207);
        internal_counters.push_back(19433);
        internal_counters.push_back(19659);
        internal_counters.push_back(19885);
        internal_counters.push_back(20111);
        internal_counters.push_back(20337);
        internal_counters.push_back(20563);
        internal_counters.push_back(20789);
        internal_counters.push_back(21015);
        internal_counters.push_back(21241);
        internal_counters.push_back(21467);
        internal_counters.push_back(21693);
        internal_counters.push_back(21919);
        internal_counters.push_back(22145);
        internal_counters.push_back(22371);
        internal_counters.push_back(22597);
        internal_counters.push_back(22823);
        internal_counters.push_back(23049);
        internal_counters.push_back(23275);
        internal_counters.push_back(23501);
        internal_counters.push_back(23727);
        internal_counters.push_back(23953);
        internal_counters.push_back(24179);
        internal_counters.push_back(15366);
        internal_counters.push_back(15592);
        internal_counters.push_back(15818);
        internal_counters.push_back(16044);
        internal_counters.push_back(16270);
        internal_counters.push_back(16496);
        internal_counters.push_back(16722);
        internal_counters.push_back(16948);
        internal_counters.push_back(17174);
        internal_counters.push_back(17400);
        internal_counters.push_back(17626);
        internal_counters.push_back(17852);
        internal_counters.push_back(18078);
        internal_counters.push_back(18304);
        internal_counters.push_back(18530);
        internal_counters.push_back(18756);
        internal_counters.push_back(18982);
        internal_counters.push_back(19208);
        internal_counters.push_back(19434);
        internal_counters.push_back(19660);
        internal_counters.push_back(19886);
        internal_counters.push_back(20112);
        internal_counters.push_back(20338);
        internal_counters.push_back(20564);
        internal_counters.push_back(20790);
        internal_counters.push_back(21016);
        internal_counters.push_back(21242);
        internal_counters.push_back(21468);
        internal_counters.push_back(21694);
        internal_counters.push_back(21920);
        internal_counters.push_back(22146);
        internal_counters.push_back(22372);
        internal_counters.push_back(22598);
        internal_counters.push_back(22824);
        internal_counters.push_back(23050);
        internal_counters.push_back(23276);
        internal_counters.push_back(23502);
        internal_counters.push_back(23728);
        internal_counters.push_back(23954);
        internal_counters.push_back(24180);
        internal_counters.push_back(15367);
        internal_counters.push_back(15593);
        internal_counters.push_back(15819);
        internal_counters.push_back(16045);
        internal_counters.push_back(16271);
        internal_counters.push_back(16497);
        internal_counters.push_back(16723);
        internal_counters.push_back(16949);
        internal_counters.push_back(17175);
        internal_counters.push_back(17401);
        internal_counters.push_back(17627);
        internal_counters.push_back(17853);
        internal_counters.push_back(18079);
        internal_counters.push_back(18305);
        internal_counters.push_back(18531);
        internal_counters.push_back(18757);
        internal_counters.push_back(18983);
        internal_counters.push_back(19209);
        internal_counters.push_back(19435);
        internal_counters.push_back(19661);
        internal_counters.push_back(19887);
        internal_counters.push_back(20113);
        internal_counters.push_back(20339);
        internal_counters.push_back(20565);
        internal_counters.push_back(20791);
        internal_counters.push_back(21017);
        internal_counters.push_back(21243);
        internal_counters.push_back(21469);
        internal_counters.push_back(21695);
        internal_counters.push_back(21921);
        internal_counters.push_back(22147);
        internal_counters.push_back(22373);
        internal_counters.push_back(22599);
        internal_counters.push_back(22825);
        internal_counters.push_back(23051);
        internal_counters.push_back(23277);
        internal_counters.push_back(23503);
        internal_counters.push_back(23729);
        internal_counters.push_back(23955);
        internal_counters.push_back(24181);

        c.DefineDerivedCounter("TexAveAnisotropy", "TextureUnit", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,(2),40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,*,+,(4),80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,sum40,*,+,(6),120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,sum40,*,+,(8),160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,sum40,*,+,(10),200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,sum40,*,+,(12),240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,sum40,*,+,(14),280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,sum40,*,+,(16),320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,sum40,*,+,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,+,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,sum40,+,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,sum40,+,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,sum40,+,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,sum40,+,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,sum40,+,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,sum40,+,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,sum40,+,/", "7ca2a2b9-a4eb-ce23-d163-59147e672396");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(29974);
        internal_counters.push_back(30344);
        internal_counters.push_back(30714);
        internal_counters.push_back(31084);
        internal_counters.push_back(31454);
        internal_counters.push_back(31824);
        internal_counters.push_back(32194);
        internal_counters.push_back(32564);
        internal_counters.push_back(32934);
        internal_counters.push_back(33304);
        internal_counters.push_back(33674);
        internal_counters.push_back(34044);
        internal_counters.push_back(34414);
        internal_counters.push_back(34784);
        internal_counters.push_back(35154);
        internal_counters.push_back(35524);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("DepthStencilTestBusy", "Timing", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "6834fb52-42e8-bb50-fd48-ec2f2904e7e0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(29974);
        internal_counters.push_back(30344);
        internal_counters.push_back(30714);
        internal_counters.push_back(31084);
        internal_counters.push_back(31454);
        internal_counters.push_back(31824);
        internal_counters.push_back(32194);
        internal_counters.push_back(32564);
        internal_counters.push_back(32934);
        internal_counters.push_back(33304);
        internal_counters.push_back(33674);
        internal_counters.push_back(34044);
        internal_counters.push_back(34414);
        internal_counters.push_back(34784);
        internal_counters.push_back(35154);
        internal_counters.push_back(35524);

        c.DefineDerivedCounter("DepthStencilTestBusyCycles", "Timing", "Number of GPU cycles spent performing depth and stencil tests.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "07ad48f0-49d8-87e7-1ef5-1e24ff2cef49");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(29845);
        internal_counters.push_back(30215);
        internal_counters.push_back(30585);
        internal_counters.push_back(30955);
        internal_counters.push_back(31325);
        internal_counters.push_back(31695);
        internal_counters.push_back(32065);
        internal_counters.push_back(32435);
        internal_counters.push_back(32805);
        internal_counters.push_back(33175);
        internal_counters.push_back(33545);
        internal_counters.push_back(33915);
        internal_counters.push_back(34285);
        internal_counters.push_back(34655);
        internal_counters.push_back(35025);
        internal_counters.push_back(35395);
        internal_counters.push_back(29834);
        internal_counters.push_back(30204);
        internal_counters.push_back(30574);
        internal_counters.push_back(30944);
        internal_counters.push_back(31314);
        internal_counters.push_back(31684);
        internal_counters.push_back(32054);
        internal_counters.push_back(32424);
        internal_counters.push_back(32794);
        internal_counters.push_back(33164);
        internal_counters.push_back(33534);
        internal_counters.push_back(33904);
        internal_counters.push_back(34274);
        internal_counters.push_back(34644);
        internal_counters.push_back(35014);
        internal_counters.push_back(35384);

        c.DefineDerivedCounter("HiZTilesAccepted", "DepthAndStencil", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,-,(0),max,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*", "56176f45-d7ff-813d-4f05-3b2f046067e7");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(29834);
        internal_counters.push_back(30204);
        internal_counters.push_back(30574);
        internal_counters.push_back(30944);
        internal_counters.push_back(31314);
        internal_counters.push_back(31684);
        internal_counters.push_back(32054);
        internal_counters.push_back(32424);
        internal_counters.push_back(32794);
        internal_counters.push_back(33164);
        internal_counters.push_back(33534);
        internal_counters.push_back(33904);
        internal_counters.push_back(34274);
        internal_counters.push_back(34644);
        internal_counters.push_back(35014);
        internal_counters.push_back(35384);
        internal_counters.push_back(29845);
        internal_counters.push_back(30215);
        internal_counters.push_back(30585);
        internal_counters.push_back(30955);
        internal_counters.push_back(31325);
        internal_counters.push_back(31695);
        internal_counters.push_back(32065);
        internal_counters.push_back(32435);
        internal_counters.push_back(32805);
        internal_counters.push_back(33175);
        internal_counters.push_back(33545);
        internal_counters.push_back(33915);
        internal_counters.push_back(34285);
        internal_counters.push_back(34655);
        internal_counters.push_back(35025);
        internal_counters.push_back(35395);

        c.DefineDerivedCounter("HiZTilesAcceptedCount", "DepthAndStencil", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(0),max", "95d4e3f6-b2f0-f26e-8423-aacdfaf79ea3");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(29845);
        internal_counters.push_back(30215);
        internal_counters.push_back(30585);
        internal_counters.push_back(30955);
        internal_counters.push_back(31325);
        internal_counters.push_back(31695);
        internal_counters.push_back(32065);
        internal_counters.push_back(32435);
        internal_counters.push_back(32805);
        internal_counters.push_back(33175);
        internal_counters.push_back(33545);
        internal_counters.push_back(33915);
        internal_counters.push_back(34285);
        internal_counters.push_back(34655);
        internal_counters.push_back(35025);
        internal_counters.push_back(35395);

        c.DefineDerivedCounter("HiZTilesRejectedCount", "DepthAndStencil", "Count of tiles not accepted by HiZ.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "156ba142-7eeb-aa6e-a00a-f8aea4e41e0b");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(29834);
        internal_counters.push_back(30204);
        internal_counters.push_back(30574);
        internal_counters.push_back(30944);
        internal_counters.push_back(31314);
        internal_counters.push_back(31684);
        internal_counters.push_back(32054);
        internal_counters.push_back(32424);
        internal_counters.push_back(32794);
        internal_counters.push_back(33164);
        internal_counters.push_back(33534);
        internal_counters.push_back(33904);
        internal_counters.push_back(34274);
        internal_counters.push_back(34644);
        internal_counters.push_back(35014);
        internal_counters.push_back(35384);
        internal_counters.push_back(29858);
        internal_counters.push_back(30228);
        internal_counters.push_back(30598);
        internal_counters.push_back(30968);
        internal_counters.push_back(31338);
        internal_counters.push_back(31708);
        internal_counters.push_back(32078);
        internal_counters.push_back(32448);
        internal_counters.push_back(32818);
        internal_counters.push_back(33188);
        internal_counters.push_back(33558);
        internal_counters.push_back(33928);
        internal_counters.push_back(34298);
        internal_counters.push_back(34668);
        internal_counters.push_back(35038);
        internal_counters.push_back(35408);

        c.DefineDerivedCounter("PreZTilesDetailCulled", "DepthAndStencil", "Percentage of tiles rejected because the associated prim had no contributing area.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*", "cad7f54d-a044-7574-c472-6f2065cbeeac");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(29858);
        internal_counters.push_back(30228);
        internal_counters.push_back(30598);
        internal_counters.push_back(30968);
        internal_counters.push_back(31338);
        internal_counters.push_back(31708);
        internal_counters.push_back(32078);
        internal_counters.push_back(32448);
        internal_counters.push_back(32818);
        internal_counters.push_back(33188);
        internal_counters.push_back(33558);
        internal_counters.push_back(33928);
        internal_counters.push_back(34298);
        internal_counters.push_back(34668);
        internal_counters.push_back(35038);
        internal_counters.push_back(35408);

        c.DefineDerivedCounter("PreZTilesDetailCulledCount", "DepthAndStencil", "Count of tiles rejected because the associated primitive had no contributing area.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "49262c8a-b1e6-90dd-f096-0fc4921715e9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(29834);
        internal_counters.push_back(30204);
        internal_counters.push_back(30574);
        internal_counters.push_back(30944);
        internal_counters.push_back(31314);
        internal_counters.push_back(31684);
        internal_counters.push_back(32054);
        internal_counters.push_back(32424);
        internal_counters.push_back(32794);
        internal_counters.push_back(33164);
        internal_counters.push_back(33534);
        internal_counters.push_back(33904);
        internal_counters.push_back(34274);
        internal_counters.push_back(34644);
        internal_counters.push_back(35014);
        internal_counters.push_back(35384);

        c.DefineDerivedCounter("PreZTilesDetailSurvivingCount", "DepthAndStencil", "Count of tiles surviving because the associated primitive had contributing area.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "f803eaa4-bbed-bd39-775f-a64df92e2c08");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1263);
        internal_counters.push_back(1815);
        internal_counters.push_back(2367);
        internal_counters.push_back(2919);
        internal_counters.push_back(3471);
        internal_counters.push_back(4023);
        internal_counters.push_back(4575);
        internal_counters.push_back(5127);
        internal_counters.push_back(1264);
        internal_counters.push_back(1816);
        internal_counters.push_back(2368);
        internal_counters.push_back(2920);
        internal_counters.push_back(3472);
        internal_counters.push_back(4024);
        internal_counters.push_back(4576);
        internal_counters.push_back(5128);
        internal_counters.push_back(1265);
        internal_counters.push_back(1817);
        internal_counters.push_back(2369);
        internal_counters.push_back(2921);
        internal_counters.push_back(3473);
        internal_counters.push_back(4025);
        internal_counters.push_back(4577);
        internal_counters.push_back(5129);
        internal_counters.push_back(1266);
        internal_counters.push_back(1818);
        internal_counters.push_back(2370);
        internal_counters.push_back(2922);
        internal_counters.push_back(3474);
        internal_counters.push_back(4026);
        internal_counters.push_back(4578);
        internal_counters.push_back(5130);
        internal_counters.push_back(1339);
        internal_counters.push_back(1891);
        internal_counters.push_back(2443);
        internal_counters.push_back(2995);
        internal_counters.push_back(3547);
        internal_counters.push_back(4099);
        internal_counters.push_back(4651);
        internal_counters.push_back(5203);
        internal_counters.push_back(1340);
        internal_counters.push_back(1892);
        internal_counters.push_back(2444);
        internal_counters.push_back(2996);
        internal_counters.push_back(3548);
        internal_counters.push_back(4100);
        internal_counters.push_back(4652);
        internal_counters.push_back(5204);
        internal_counters.push_back(1341);
        internal_counters.push_back(1893);
        internal_counters.push_back(2445);
        internal_counters.push_back(2997);
        internal_counters.push_back(3549);
        internal_counters.push_back(4101);
        internal_counters.push_back(4653);
        internal_counters.push_back(5205);
        internal_counters.push_back(1342);
        internal_counters.push_back(1894);
        internal_counters.push_back(2446);
        internal_counters.push_back(2998);
        internal_counters.push_back(3550);
        internal_counters.push_back(4102);
        internal_counters.push_back(4654);
        internal_counters.push_back(5206);

        c.DefineDerivedCounter("HiZQuadsCulled", "DepthAndStencil", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum32,-,(0),max,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,/,(100),*", "fa0e319b-5573-6d34-5bab-904769925036");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1263);
        internal_counters.push_back(1815);
        internal_counters.push_back(2367);
        internal_counters.push_back(2919);
        internal_counters.push_back(3471);
        internal_counters.push_back(4023);
        internal_counters.push_back(4575);
        internal_counters.push_back(5127);
        internal_counters.push_back(1264);
        internal_counters.push_back(1816);
        internal_counters.push_back(2368);
        internal_counters.push_back(2920);
        internal_counters.push_back(3472);
        internal_counters.push_back(4024);
        internal_counters.push_back(4576);
        internal_counters.push_back(5128);
        internal_counters.push_back(1265);
        internal_counters.push_back(1817);
        internal_counters.push_back(2369);
        internal_counters.push_back(2921);
        internal_counters.push_back(3473);
        internal_counters.push_back(4025);
        internal_counters.push_back(4577);
        internal_counters.push_back(5129);
        internal_counters.push_back(1266);
        internal_counters.push_back(1818);
        internal_counters.push_back(2370);
        internal_counters.push_back(2922);
        internal_counters.push_back(3474);
        internal_counters.push_back(4026);
        internal_counters.push_back(4578);
        internal_counters.push_back(5130);
        internal_counters.push_back(1339);
        internal_counters.push_back(1891);
        internal_counters.push_back(2443);
        internal_counters.push_back(2995);
        internal_counters.push_back(3547);
        internal_counters.push_back(4099);
        internal_counters.push_back(4651);
        internal_counters.push_back(5203);
        internal_counters.push_back(1340);
        internal_counters.push_back(1892);
        internal_counters.push_back(2444);
        internal_counters.push_back(2996);
        internal_counters.push_back(3548);
        internal_counters.push_back(4100);
        internal_counters.push_back(4652);
        internal_counters.push_back(5204);
        internal_counters.push_back(1341);
        internal_counters.push_back(1893);
        internal_counters.push_back(2445);
        internal_counters.push_back(2997);
        internal_counters.push_back(3549);
        internal_counters.push_back(4101);
        internal_counters.push_back(4653);
        internal_counters.push_back(5205);
        internal_counters.push_back(1342);
        internal_counters.push_back(1894);
        internal_counters.push_back(2446);
        internal_counters.push_back(2998);
        internal_counters.push_back(3550);
        internal_counters.push_back(4102);
        internal_counters.push_back(4654);
        internal_counters.push_back(5206);

        c.DefineDerivedCounter("HiZQuadsCulledCount", "DepthAndStencil", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum32,-,(0),max", "73b0b39d-6df2-3e24-0b5c-7cb0ac8b6f39");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1339);
        internal_counters.push_back(1891);
        internal_counters.push_back(2443);
        internal_counters.push_back(2995);
        internal_counters.push_back(3547);
        internal_counters.push_back(4099);
        internal_counters.push_back(4651);
        internal_counters.push_back(5203);
        internal_counters.push_back(1340);
        internal_counters.push_back(1892);
        internal_counters.push_back(2444);
        internal_counters.push_back(2996);
        internal_counters.push_back(3548);
        internal_counters.push_back(4100);
        internal_counters.push_back(4652);
        internal_counters.push_back(5204);
        internal_counters.push_back(1341);
        internal_counters.push_back(1893);
        internal_counters.push_back(2445);
        internal_counters.push_back(2997);
        internal_counters.push_back(3549);
        internal_counters.push_back(4101);
        internal_counters.push_back(4653);
        internal_counters.push_back(5205);
        internal_counters.push_back(1342);
        internal_counters.push_back(1894);
        internal_counters.push_back(2446);
        internal_counters.push_back(2998);
        internal_counters.push_back(3550);
        internal_counters.push_back(4102);
        internal_counters.push_back(4654);
        internal_counters.push_back(5206);

        c.DefineDerivedCounter("HiZQuadsAcceptedCount", "DepthAndStencil", "Count of quads that did continue on in the pipeline after HiZ.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32", "59049ad9-42b5-c7cb-3616-6a8f6a8e4894");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1339);
        internal_counters.push_back(1891);
        internal_counters.push_back(2443);
        internal_counters.push_back(2995);
        internal_counters.push_back(3547);
        internal_counters.push_back(4099);
        internal_counters.push_back(4651);
        internal_counters.push_back(5203);
        internal_counters.push_back(1340);
        internal_counters.push_back(1892);
        internal_counters.push_back(2444);
        internal_counters.push_back(2996);
        internal_counters.push_back(3548);
        internal_counters.push_back(4100);
        internal_counters.push_back(4652);
        internal_counters.push_back(5204);
        internal_counters.push_back(1341);
        internal_counters.push_back(1893);
        internal_counters.push_back(2445);
        internal_counters.push_back(2997);
        internal_counters.push_back(3549);
        internal_counters.push_back(4101);
        internal_counters.push_back(4653);
        internal_counters.push_back(5205);
        internal_counters.push_back(1342);
        internal_counters.push_back(1894);
        internal_counters.push_back(2446);
        internal_counters.push_back(2998);
        internal_counters.push_back(3550);
        internal_counters.push_back(4102);
        internal_counters.push_back(4654);
        internal_counters.push_back(5206);
        internal_counters.push_back(1363);
        internal_counters.push_back(1915);
        internal_counters.push_back(2467);
        internal_counters.push_back(3019);
        internal_counters.push_back(3571);
        internal_counters.push_back(4123);
        internal_counters.push_back(4675);
        internal_counters.push_back(5227);
        internal_counters.push_back(1263);
        internal_counters.push_back(1815);
        internal_counters.push_back(2367);
        internal_counters.push_back(2919);
        internal_counters.push_back(3471);
        internal_counters.push_back(4023);
        internal_counters.push_back(4575);
        internal_counters.push_back(5127);
        internal_counters.push_back(1264);
        internal_counters.push_back(1816);
        internal_counters.push_back(2368);
        internal_counters.push_back(2920);
        internal_counters.push_back(3472);
        internal_counters.push_back(4024);
        internal_counters.push_back(4576);
        internal_counters.push_back(5128);
        internal_counters.push_back(1265);
        internal_counters.push_back(1817);
        internal_counters.push_back(2369);
        internal_counters.push_back(2921);
        internal_counters.push_back(3473);
        internal_counters.push_back(4025);
        internal_counters.push_back(4577);
        internal_counters.push_back(5129);
        internal_counters.push_back(1266);
        internal_counters.push_back(1818);
        internal_counters.push_back(2370);
        internal_counters.push_back(2922);
        internal_counters.push_back(3474);
        internal_counters.push_back(4026);
        internal_counters.push_back(4578);
        internal_counters.push_back(5130);

        c.DefineDerivedCounter("PreZQuadsCulled", "DepthAndStencil", "Percentage of quads rejected based on the detailZ and earlyZ tests.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,32,33,34,35,36,37,38,39,sum8,-,(0),max,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,sum32,/,(100),*", "4e77547b-ec55-5663-f034-af59be66d77d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1339);
        internal_counters.push_back(1891);
        internal_counters.push_back(2443);
        internal_counters.push_back(2995);
        internal_counters.push_back(3547);
        internal_counters.push_back(4099);
        internal_counters.push_back(4651);
        internal_counters.push_back(5203);
        internal_counters.push_back(1340);
        internal_counters.push_back(1892);
        internal_counters.push_back(2444);
        internal_counters.push_back(2996);
        internal_counters.push_back(3548);
        internal_counters.push_back(4100);
        internal_counters.push_back(4652);
        internal_counters.push_back(5204);
        internal_counters.push_back(1341);
        internal_counters.push_back(1893);
        internal_counters.push_back(2445);
        internal_counters.push_back(2997);
        internal_counters.push_back(3549);
        internal_counters.push_back(4101);
        internal_counters.push_back(4653);
        internal_counters.push_back(5205);
        internal_counters.push_back(1342);
        internal_counters.push_back(1894);
        internal_counters.push_back(2446);
        internal_counters.push_back(2998);
        internal_counters.push_back(3550);
        internal_counters.push_back(4102);
        internal_counters.push_back(4654);
        internal_counters.push_back(5206);
        internal_counters.push_back(1363);
        internal_counters.push_back(1915);
        internal_counters.push_back(2467);
        internal_counters.push_back(3019);
        internal_counters.push_back(3571);
        internal_counters.push_back(4123);
        internal_counters.push_back(4675);
        internal_counters.push_back(5227);

        c.DefineDerivedCounter("PreZQuadsCulledCount", "DepthAndStencil", "Count of quads rejected based on the detailZ and earlyZ tests.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum32,32,33,34,35,36,37,38,39,sum8,-,(0),max", "1bf169e6-9304-834e-df5f-0c44d7890a08");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1363);
        internal_counters.push_back(1915);
        internal_counters.push_back(2467);
        internal_counters.push_back(3019);
        internal_counters.push_back(3571);
        internal_counters.push_back(4123);
        internal_counters.push_back(4675);
        internal_counters.push_back(5227);

        c.DefineDerivedCounter("PreZQuadsSurvivingCount", "DepthAndStencil", "Count of quads surviving detailZ and earlyZ tests.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,sum8", "50e25e51-3713-89cb-7f92-559cde5e5532");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1363);
        internal_counters.push_back(1915);
        internal_counters.push_back(2467);
        internal_counters.push_back(3019);
        internal_counters.push_back(3571);
        internal_counters.push_back(4123);
        internal_counters.push_back(4675);
        internal_counters.push_back(5227);
        internal_counters.push_back(1263);
        internal_counters.push_back(1815);
        internal_counters.push_back(2367);
        internal_counters.push_back(2919);
        internal_counters.push_back(3471);
        internal_counters.push_back(4023);
        internal_counters.push_back(4575);
        internal_counters.push_back(5127);
        internal_counters.push_back(1264);
        internal_counters.push_back(1816);
        internal_counters.push_back(2368);
        internal_counters.push_back(2920);
        internal_counters.push_back(3472);
        internal_counters.push_back(4024);
        internal_counters.push_back(4576);
        internal_counters.push_back(5128);
        internal_counters.push_back(1265);
        internal_counters.push_back(1817);
        internal_counters.push_back(2369);
        internal_counters.push_back(2921);
        internal_counters.push_back(3473);
        internal_counters.push_back(4025);
        internal_counters.push_back(4577);
        internal_counters.push_back(5129);
        internal_counters.push_back(1266);
        internal_counters.push_back(1818);
        internal_counters.push_back(2370);
        internal_counters.push_back(2922);
        internal_counters.push_back(3474);
        internal_counters.push_back(4026);
        internal_counters.push_back(4578);
        internal_counters.push_back(5130);

        c.DefineDerivedCounter("PostZQuads", "DepthAndStencil", "Percentage of quads for which the pixel shader will run and may be postZ tested.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,sum8,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum32,/,(100),*", "58f0d34b-eeb8-e8db-abce-cb72584144be");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(1363);
        internal_counters.push_back(1915);
        internal_counters.push_back(2467);
        internal_counters.push_back(3019);
        internal_counters.push_back(3571);
        internal_counters.push_back(4123);
        internal_counters.push_back(4675);
        internal_counters.push_back(5227);

        c.DefineDerivedCounter("PostZQuadCount", "DepthAndStencil", "Count of quads for which the pixel shader will run and may be postZ tested.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,sum8", "08404526-ce35-939b-34c8-a7a35a0ff4d6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(30007);
        internal_counters.push_back(30377);
        internal_counters.push_back(30747);
        internal_counters.push_back(31117);
        internal_counters.push_back(31487);
        internal_counters.push_back(31857);
        internal_counters.push_back(32227);
        internal_counters.push_back(32597);
        internal_counters.push_back(32967);
        internal_counters.push_back(33337);
        internal_counters.push_back(33707);
        internal_counters.push_back(34077);
        internal_counters.push_back(34447);
        internal_counters.push_back(34817);
        internal_counters.push_back(35187);
        internal_counters.push_back(35557);

        c.DefineDerivedCounter("PreZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z before shading and passed.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "3bfe6c4d-7422-ca03-7ea5-e67ff1a00136");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(30009);
        internal_counters.push_back(30379);
        internal_counters.push_back(30749);
        internal_counters.push_back(31119);
        internal_counters.push_back(31489);
        internal_counters.push_back(31859);
        internal_counters.push_back(32229);
        internal_counters.push_back(32599);
        internal_counters.push_back(32969);
        internal_counters.push_back(33339);
        internal_counters.push_back(33709);
        internal_counters.push_back(34079);
        internal_counters.push_back(34449);
        internal_counters.push_back(34819);
        internal_counters.push_back(35189);
        internal_counters.push_back(35559);

        c.DefineDerivedCounter("PreZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z before shading and failed stencil test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "df7f705e-5162-d3b5-da8b-63466cf9c4e5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(30008);
        internal_counters.push_back(30378);
        internal_counters.push_back(30748);
        internal_counters.push_back(31118);
        internal_counters.push_back(31488);
        internal_counters.push_back(31858);
        internal_counters.push_back(32228);
        internal_counters.push_back(32598);
        internal_counters.push_back(32968);
        internal_counters.push_back(33338);
        internal_counters.push_back(33708);
        internal_counters.push_back(34078);
        internal_counters.push_back(34448);
        internal_counters.push_back(34818);
        internal_counters.push_back(35188);
        internal_counters.push_back(35558);

        c.DefineDerivedCounter("PreZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z before shading and failed Z test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "4484e950-f7a4-3800-bc74-78dd297f017e");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(30004);
        internal_counters.push_back(30374);
        internal_counters.push_back(30744);
        internal_counters.push_back(31114);
        internal_counters.push_back(31484);
        internal_counters.push_back(31854);
        internal_counters.push_back(32224);
        internal_counters.push_back(32594);
        internal_counters.push_back(32964);
        internal_counters.push_back(33334);
        internal_counters.push_back(33704);
        internal_counters.push_back(34074);
        internal_counters.push_back(34444);
        internal_counters.push_back(34814);
        internal_counters.push_back(35184);
        internal_counters.push_back(35554);

        c.DefineDerivedCounter("PostZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z after shading and passed.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "4995d5d6-2330-b986-508b-fae24856f44c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(30006);
        internal_counters.push_back(30376);
        internal_counters.push_back(30746);
        internal_counters.push_back(31116);
        internal_counters.push_back(31486);
        internal_counters.push_back(31856);
        internal_counters.push_back(32226);
        internal_counters.push_back(32596);
        internal_counters.push_back(32966);
        internal_counters.push_back(33336);
        internal_counters.push_back(33706);
        internal_counters.push_back(34076);
        internal_counters.push_back(34446);
        internal_counters.push_back(34816);
        internal_counters.push_back(35186);
        internal_counters.push_back(35556);

        c.DefineDerivedCounter("PostZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z after shading and failed stencil test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "ae558af4-f4be-3dd4-7316-b2c4dcf0def8");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(30005);
        internal_counters.push_back(30375);
        internal_counters.push_back(30745);
        internal_counters.push_back(31115);
        internal_counters.push_back(31485);
        internal_counters.push_back(31855);
        internal_counters.push_back(32225);
        internal_counters.push_back(32595);
        internal_counters.push_back(32965);
        internal_counters.push_back(33335);
        internal_counters.push_back(33705);
        internal_counters.push_back(34075);
        internal_counters.push_back(34445);
        internal_counters.push_back(34815);
        internal_counters.push_back(35185);
        internal_counters.push_back(35555);

        c.DefineDerivedCounter("PostZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z after shading and failed Z test.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "b3684c94-814a-c695-c85d-a5b6ab798b35");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(29876);
        internal_counters.push_back(30246);
        internal_counters.push_back(30616);
        internal_counters.push_back(30986);
        internal_counters.push_back(31356);
        internal_counters.push_back(31726);
        internal_counters.push_back(32096);
        internal_counters.push_back(32466);
        internal_counters.push_back(32836);
        internal_counters.push_back(33206);
        internal_counters.push_back(33576);
        internal_counters.push_back(33946);
        internal_counters.push_back(34316);
        internal_counters.push_back(34686);
        internal_counters.push_back(35056);
        internal_counters.push_back(35426);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("ZUnitStalled", "DepthAndStencil", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "5e86c3ad-1726-3157-1d01-7ed188bf854d");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(29876);
        internal_counters.push_back(30246);
        internal_counters.push_back(30616);
        internal_counters.push_back(30986);
        internal_counters.push_back(31356);
        internal_counters.push_back(31726);
        internal_counters.push_back(32096);
        internal_counters.push_back(32466);
        internal_counters.push_back(32836);
        internal_counters.push_back(33206);
        internal_counters.push_back(33576);
        internal_counters.push_back(33946);
        internal_counters.push_back(34316);
        internal_counters.push_back(34686);
        internal_counters.push_back(35056);
        internal_counters.push_back(35426);

        c.DefineDerivedCounter("ZUnitStalledCycles", "DepthAndStencil", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "4351fa7f-6737-2c3e-3ffb-b3addbdceedd");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(29878);
        internal_counters.push_back(30248);
        internal_counters.push_back(30618);
        internal_counters.push_back(30988);
        internal_counters.push_back(31358);
        internal_counters.push_back(31728);
        internal_counters.push_back(32098);
        internal_counters.push_back(32468);
        internal_counters.push_back(32838);
        internal_counters.push_back(33208);
        internal_counters.push_back(33578);
        internal_counters.push_back(33948);
        internal_counters.push_back(34318);
        internal_counters.push_back(34688);
        internal_counters.push_back(35058);
        internal_counters.push_back(35428);
        internal_counters.push_back(29885);
        internal_counters.push_back(30255);
        internal_counters.push_back(30625);
        internal_counters.push_back(30995);
        internal_counters.push_back(31365);
        internal_counters.push_back(31735);
        internal_counters.push_back(32105);
        internal_counters.push_back(32475);
        internal_counters.push_back(32845);
        internal_counters.push_back(33215);
        internal_counters.push_back(33585);
        internal_counters.push_back(33955);
        internal_counters.push_back(34325);
        internal_counters.push_back(34695);
        internal_counters.push_back(35065);
        internal_counters.push_back(35435);

        c.DefineDerivedCounter("DBMemRead", "DepthAndStencil", "Number of bytes read from the depth buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(256),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+", "dcdb4ee7-bd50-00f7-c028-9e5f4ce888c0");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(29890);
        internal_counters.push_back(30260);
        internal_counters.push_back(30630);
        internal_counters.push_back(31000);
        internal_counters.push_back(31370);
        internal_counters.push_back(31740);
        internal_counters.push_back(32110);
        internal_counters.push_back(32480);
        internal_counters.push_back(32850);
        internal_counters.push_back(33220);
        internal_counters.push_back(33590);
        internal_counters.push_back(33960);
        internal_counters.push_back(34330);
        internal_counters.push_back(34700);
        internal_counters.push_back(35070);
        internal_counters.push_back(35440);
        internal_counters.push_back(29893);
        internal_counters.push_back(30263);
        internal_counters.push_back(30633);
        internal_counters.push_back(31003);
        internal_counters.push_back(31373);
        internal_counters.push_back(31743);
        internal_counters.push_back(32113);
        internal_counters.push_back(32483);
        internal_counters.push_back(32853);
        internal_counters.push_back(33223);
        internal_counters.push_back(33593);
        internal_counters.push_back(33963);
        internal_counters.push_back(34333);
        internal_counters.push_back(34703);
        internal_counters.push_back(35073);
        internal_counters.push_back(35443);

        c.DefineDerivedCounter("DBMemWritten", "DepthAndStencil", "Number of bytes written to the depth buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+", "de5717f8-8a49-ee44-4645-10de51b37dcf");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(35878);
        internal_counters.push_back(36339);
        internal_counters.push_back(36800);
        internal_counters.push_back(37261);
        internal_counters.push_back(37722);
        internal_counters.push_back(38183);
        internal_counters.push_back(38644);
        internal_counters.push_back(39105);
        internal_counters.push_back(39566);
        internal_counters.push_back(40027);
        internal_counters.push_back(40488);
        internal_counters.push_back(40949);
        internal_counters.push_back(41410);
        internal_counters.push_back(41871);
        internal_counters.push_back(42332);
        internal_counters.push_back(42793);

        c.DefineDerivedCounter("CBMemRead", "ColorBuffer", "Number of bytes read from the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "84b531d8-a1f8-7f49-7c27-7bc97801f1e6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(36009);
        internal_counters.push_back(36470);
        internal_counters.push_back(36931);
        internal_counters.push_back(37392);
        internal_counters.push_back(37853);
        internal_counters.push_back(38314);
        internal_counters.push_back(38775);
        internal_counters.push_back(39236);
        internal_counters.push_back(39697);
        internal_counters.push_back(40158);
        internal_counters.push_back(40619);
        internal_counters.push_back(41080);
        internal_counters.push_back(41541);
        internal_counters.push_back(42002);
        internal_counters.push_back(42463);
        internal_counters.push_back(42924);
        internal_counters.push_back(35876);
        internal_counters.push_back(36337);
        internal_counters.push_back(36798);
        internal_counters.push_back(37259);
        internal_counters.push_back(37720);
        internal_counters.push_back(38181);
        internal_counters.push_back(38642);
        internal_counters.push_back(39103);
        internal_counters.push_back(39564);
        internal_counters.push_back(40025);
        internal_counters.push_back(40486);
        internal_counters.push_back(40947);
        internal_counters.push_back(41408);
        internal_counters.push_back(41869);
        internal_counters.push_back(42330);
        internal_counters.push_back(42791);
        internal_counters.push_back(35877);
        internal_counters.push_back(36338);
        internal_counters.push_back(36799);
        internal_counters.push_back(37260);
        internal_counters.push_back(37721);
        internal_counters.push_back(38182);
        internal_counters.push_back(38643);
        internal_counters.push_back(39104);
        internal_counters.push_back(39565);
        internal_counters.push_back(40026);
        internal_counters.push_back(40487);
        internal_counters.push_back(40948);
        internal_counters.push_back(41409);
        internal_counters.push_back(41870);
        internal_counters.push_back(42331);
        internal_counters.push_back(42792);
        internal_counters.push_back(35878);
        internal_counters.push_back(36339);
        internal_counters.push_back(36800);
        internal_counters.push_back(37261);
        internal_counters.push_back(37722);
        internal_counters.push_back(38183);
        internal_counters.push_back(38644);
        internal_counters.push_back(39105);
        internal_counters.push_back(39566);
        internal_counters.push_back(40027);
        internal_counters.push_back(40488);
        internal_counters.push_back(40949);
        internal_counters.push_back(41410);
        internal_counters.push_back(41871);
        internal_counters.push_back(42332);
        internal_counters.push_back(42793);

        c.DefineDerivedCounter("CBColorAndMaskRead", "ColorBuffer", "Total number of bytes read from the color and mask buffers.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*", "da41660e-eb6f-32ec-8a64-b32ca17bd7eb");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(35868);
        internal_counters.push_back(36329);
        internal_counters.push_back(36790);
        internal_counters.push_back(37251);
        internal_counters.push_back(37712);
        internal_counters.push_back(38173);
        internal_counters.push_back(38634);
        internal_counters.push_back(39095);
        internal_counters.push_back(39556);
        internal_counters.push_back(40017);
        internal_counters.push_back(40478);
        internal_counters.push_back(40939);
        internal_counters.push_back(41400);
        internal_counters.push_back(41861);
        internal_counters.push_back(42322);
        internal_counters.push_back(42783);

        c.DefineDerivedCounter("CBMemWritten", "ColorBuffer", "Number of bytes written to the color buffer.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "550f8ff8-60b6-a6bf-87d0-25ac9e87de70");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(36007);
        internal_counters.push_back(36468);
        internal_counters.push_back(36929);
        internal_counters.push_back(37390);
        internal_counters.push_back(37851);
        internal_counters.push_back(38312);
        internal_counters.push_back(38773);
        internal_counters.push_back(39234);
        internal_counters.push_back(39695);
        internal_counters.push_back(40156);
        internal_counters.push_back(40617);
        internal_counters.push_back(41078);
        internal_counters.push_back(41539);
        internal_counters.push_back(42000);
        internal_counters.push_back(42461);
        internal_counters.push_back(42922);
        internal_counters.push_back(35866);
        internal_counters.push_back(36327);
        internal_counters.push_back(36788);
        internal_counters.push_back(37249);
        internal_counters.push_back(37710);
        internal_counters.push_back(38171);
        internal_counters.push_back(38632);
        internal_counters.push_back(39093);
        internal_counters.push_back(39554);
        internal_counters.push_back(40015);
        internal_counters.push_back(40476);
        internal_counters.push_back(40937);
        internal_counters.push_back(41398);
        internal_counters.push_back(41859);
        internal_counters.push_back(42320);
        internal_counters.push_back(42781);
        internal_counters.push_back(35867);
        internal_counters.push_back(36328);
        internal_counters.push_back(36789);
        internal_counters.push_back(37250);
        internal_counters.push_back(37711);
        internal_counters.push_back(38172);
        internal_counters.push_back(38633);
        internal_counters.push_back(39094);
        internal_counters.push_back(39555);
        internal_counters.push_back(40016);
        internal_counters.push_back(40477);
        internal_counters.push_back(40938);
        internal_counters.push_back(41399);
        internal_counters.push_back(41860);
        internal_counters.push_back(42321);
        internal_counters.push_back(42782);
        internal_counters.push_back(35868);
        internal_counters.push_back(36329);
        internal_counters.push_back(36790);
        internal_counters.push_back(37251);
        internal_counters.push_back(37712);
        internal_counters.push_back(38173);
        internal_counters.push_back(38634);
        internal_counters.push_back(39095);
        internal_counters.push_back(39556);
        internal_counters.push_back(40017);
        internal_counters.push_back(40478);
        internal_counters.push_back(40939);
        internal_counters.push_back(41400);
        internal_counters.push_back(41861);
        internal_counters.push_back(42322);
        internal_counters.push_back(42783);

        c.DefineDerivedCounter("CBColorAndMaskWritten", "ColorBuffer", "Total number of bytes written to the color and mask buffers.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*", "29a04b69-8f5f-b770-a0f2-3453e2c99e49");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(35912);
        internal_counters.push_back(36373);
        internal_counters.push_back(36834);
        internal_counters.push_back(37295);
        internal_counters.push_back(37756);
        internal_counters.push_back(38217);
        internal_counters.push_back(38678);
        internal_counters.push_back(39139);
        internal_counters.push_back(39600);
        internal_counters.push_back(40061);
        internal_counters.push_back(40522);
        internal_counters.push_back(40983);
        internal_counters.push_back(41444);
        internal_counters.push_back(41905);
        internal_counters.push_back(42366);
        internal_counters.push_back(42827);
        internal_counters.push_back(35757);
        internal_counters.push_back(36218);
        internal_counters.push_back(36679);
        internal_counters.push_back(37140);
        internal_counters.push_back(37601);
        internal_counters.push_back(38062);
        internal_counters.push_back(38523);
        internal_counters.push_back(38984);
        internal_counters.push_back(39445);
        internal_counters.push_back(39906);
        internal_counters.push_back(40367);
        internal_counters.push_back(40828);
        internal_counters.push_back(41289);
        internal_counters.push_back(41750);
        internal_counters.push_back(42211);
        internal_counters.push_back(42672);

        c.DefineDerivedCounter("CBSlowPixelPct", "ColorBuffer", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*,(100),min", "5775943f-0313-7e52-9638-b24a449197bc");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(35912);
        internal_counters.push_back(36373);
        internal_counters.push_back(36834);
        internal_counters.push_back(37295);
        internal_counters.push_back(37756);
        internal_counters.push_back(38217);
        internal_counters.push_back(38678);
        internal_counters.push_back(39139);
        internal_counters.push_back(39600);
        internal_counters.push_back(40061);
        internal_counters.push_back(40522);
        internal_counters.push_back(40983);
        internal_counters.push_back(41444);
        internal_counters.push_back(41905);
        internal_counters.push_back(42366);
        internal_counters.push_back(42827);

        c.DefineDerivedCounter("CBSlowPixelCount", "ColorBuffer", "Number of pixels written to the color buffer using a half-rate or quarter-rate format.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "47eacbb0-28c8-22b4-5c69-c00d5813bb1c");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(26759);
        internal_counters.push_back(26836);
        internal_counters.push_back(26913);
        internal_counters.push_back(26990);
        internal_counters.push_back(27067);
        internal_counters.push_back(27144);
        internal_counters.push_back(27221);
        internal_counters.push_back(27298);
        internal_counters.push_back(27375);
        internal_counters.push_back(27452);
        internal_counters.push_back(27529);
        internal_counters.push_back(27606);
        internal_counters.push_back(27683);
        internal_counters.push_back(27760);
        internal_counters.push_back(27837);
        internal_counters.push_back(27914);
        internal_counters.push_back(27991);
        internal_counters.push_back(28068);
        internal_counters.push_back(28145);
        internal_counters.push_back(28222);
        internal_counters.push_back(28299);
        internal_counters.push_back(28376);
        internal_counters.push_back(28453);
        internal_counters.push_back(28530);
        internal_counters.push_back(28607);
        internal_counters.push_back(28684);
        internal_counters.push_back(28761);
        internal_counters.push_back(28838);
        internal_counters.push_back(28915);
        internal_counters.push_back(28992);
        internal_counters.push_back(29069);
        internal_counters.push_back(29146);
        internal_counters.push_back(29223);
        internal_counters.push_back(29300);
        internal_counters.push_back(29377);
        internal_counters.push_back(29454);
        internal_counters.push_back(29531);
        internal_counters.push_back(29608);
        internal_counters.push_back(29685);
        internal_counters.push_back(29762);
        internal_counters.push_back(26768);
        internal_counters.push_back(26845);
        internal_counters.push_back(26922);
        internal_counters.push_back(26999);
        internal_counters.push_back(27076);
        internal_counters.push_back(27153);
        internal_counters.push_back(27230);
        internal_counters.push_back(27307);
        internal_counters.push_back(27384);
        internal_counters.push_back(27461);
        internal_counters.push_back(27538);
        internal_counters.push_back(27615);
        internal_counters.push_back(27692);
        internal_counters.push_back(27769);
        internal_counters.push_back(27846);
        internal_counters.push_back(27923);
        internal_counters.push_back(28000);
        internal_counters.push_back(28077);
        internal_counters.push_back(28154);
        internal_counters.push_back(28231);
        internal_counters.push_back(28308);
        internal_counters.push_back(28385);
        internal_counters.push_back(28462);
        internal_counters.push_back(28539);
        internal_counters.push_back(28616);
        internal_counters.push_back(28693);
        internal_counters.push_back(28770);
        internal_counters.push_back(28847);
        internal_counters.push_back(28924);
        internal_counters.push_back(29001);
        internal_counters.push_back(29078);
        internal_counters.push_back(29155);
        internal_counters.push_back(29232);
        internal_counters.push_back(29309);
        internal_counters.push_back(29386);
        internal_counters.push_back(29463);
        internal_counters.push_back(29540);
        internal_counters.push_back(29617);
        internal_counters.push_back(29694);
        internal_counters.push_back(29771);

        c.DefineDerivedCounter("L0CacheHit", "MemoryCache", "The percentage of read requests that hit the data in the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,ifnotzero", "286c786e-9a42-3371-9dea-dd54e6e612e9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(26759);
        internal_counters.push_back(26836);
        internal_counters.push_back(26913);
        internal_counters.push_back(26990);
        internal_counters.push_back(27067);
        internal_counters.push_back(27144);
        internal_counters.push_back(27221);
        internal_counters.push_back(27298);
        internal_counters.push_back(27375);
        internal_counters.push_back(27452);
        internal_counters.push_back(27529);
        internal_counters.push_back(27606);
        internal_counters.push_back(27683);
        internal_counters.push_back(27760);
        internal_counters.push_back(27837);
        internal_counters.push_back(27914);
        internal_counters.push_back(27991);
        internal_counters.push_back(28068);
        internal_counters.push_back(28145);
        internal_counters.push_back(28222);
        internal_counters.push_back(28299);
        internal_counters.push_back(28376);
        internal_counters.push_back(28453);
        internal_counters.push_back(28530);
        internal_counters.push_back(28607);
        internal_counters.push_back(28684);
        internal_counters.push_back(28761);
        internal_counters.push_back(28838);
        internal_counters.push_back(28915);
        internal_counters.push_back(28992);
        internal_counters.push_back(29069);
        internal_counters.push_back(29146);
        internal_counters.push_back(29223);
        internal_counters.push_back(29300);
        internal_counters.push_back(29377);
        internal_counters.push_back(29454);
        internal_counters.push_back(29531);
        internal_counters.push_back(29608);
        internal_counters.push_back(29685);
        internal_counters.push_back(29762);

        c.DefineDerivedCounter("L0CacheRequestCount", "MemoryCache", "The number of read requests made to the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40", "74983cae-ee57-2e1b-d990-5128fef84e1f");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(26759);
        internal_counters.push_back(26836);
        internal_counters.push_back(26913);
        internal_counters.push_back(26990);
        internal_counters.push_back(27067);
        internal_counters.push_back(27144);
        internal_counters.push_back(27221);
        internal_counters.push_back(27298);
        internal_counters.push_back(27375);
        internal_counters.push_back(27452);
        internal_counters.push_back(27529);
        internal_counters.push_back(27606);
        internal_counters.push_back(27683);
        internal_counters.push_back(27760);
        internal_counters.push_back(27837);
        internal_counters.push_back(27914);
        internal_counters.push_back(27991);
        internal_counters.push_back(28068);
        internal_counters.push_back(28145);
        internal_counters.push_back(28222);
        internal_counters.push_back(28299);
        internal_counters.push_back(28376);
        internal_counters.push_back(28453);
        internal_counters.push_back(28530);
        internal_counters.push_back(28607);
        internal_counters.push_back(28684);
        internal_counters.push_back(28761);
        internal_counters.push_back(28838);
        internal_counters.push_back(28915);
        internal_counters.push_back(28992);
        internal_counters.push_back(29069);
        internal_counters.push_back(29146);
        internal_counters.push_back(29223);
        internal_counters.push_back(29300);
        internal_counters.push_back(29377);
        internal_counters.push_back(29454);
        internal_counters.push_back(29531);
        internal_counters.push_back(29608);
        internal_counters.push_back(29685);
        internal_counters.push_back(29762);
        internal_counters.push_back(26768);
        internal_counters.push_back(26845);
        internal_counters.push_back(26922);
        internal_counters.push_back(26999);
        internal_counters.push_back(27076);
        internal_counters.push_back(27153);
        internal_counters.push_back(27230);
        internal_counters.push_back(27307);
        internal_counters.push_back(27384);
        internal_counters.push_back(27461);
        internal_counters.push_back(27538);
        internal_counters.push_back(27615);
        internal_counters.push_back(27692);
        internal_counters.push_back(27769);
        internal_counters.push_back(27846);
        internal_counters.push_back(27923);
        internal_counters.push_back(28000);
        internal_counters.push_back(28077);
        internal_counters.push_back(28154);
        internal_counters.push_back(28231);
        internal_counters.push_back(28308);
        internal_counters.push_back(28385);
        internal_counters.push_back(28462);
        internal_counters.push_back(28539);
        internal_counters.push_back(28616);
        internal_counters.push_back(28693);
        internal_counters.push_back(28770);
        internal_counters.push_back(28847);
        internal_counters.push_back(28924);
        internal_counters.push_back(29001);
        internal_counters.push_back(29078);
        internal_counters.push_back(29155);
        internal_counters.push_back(29232);
        internal_counters.push_back(29309);
        internal_counters.push_back(29386);
        internal_counters.push_back(29463);
        internal_counters.push_back(29540);
        internal_counters.push_back(29617);
        internal_counters.push_back(29694);
        internal_counters.push_back(29771);

        c.DefineDerivedCounter("L0CacheHitCount", "MemoryCache", "The number of read requests which result in a cache hit from the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,sum40,-", "c0de7338-069b-c5ba-ead3-c65e030cd2ac");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(26768);
        internal_counters.push_back(26845);
        internal_counters.push_back(26922);
        internal_counters.push_back(26999);
        internal_counters.push_back(27076);
        internal_counters.push_back(27153);
        internal_counters.push_back(27230);
        internal_counters.push_back(27307);
        internal_counters.push_back(27384);
        internal_counters.push_back(27461);
        internal_counters.push_back(27538);
        internal_counters.push_back(27615);
        internal_counters.push_back(27692);
        internal_counters.push_back(27769);
        internal_counters.push_back(27846);
        internal_counters.push_back(27923);
        internal_counters.push_back(28000);
        internal_counters.push_back(28077);
        internal_counters.push_back(28154);
        internal_counters.push_back(28231);
        internal_counters.push_back(28308);
        internal_counters.push_back(28385);
        internal_counters.push_back(28462);
        internal_counters.push_back(28539);
        internal_counters.push_back(28616);
        internal_counters.push_back(28693);
        internal_counters.push_back(28770);
        internal_counters.push_back(28847);
        internal_counters.push_back(28924);
        internal_counters.push_back(29001);
        internal_counters.push_back(29078);
        internal_counters.push_back(29155);
        internal_counters.push_back(29232);
        internal_counters.push_back(29309);
        internal_counters.push_back(29386);
        internal_counters.push_back(29463);
        internal_counters.push_back(29540);
        internal_counters.push_back(29617);
        internal_counters.push_back(29694);
        internal_counters.push_back(29771);

        c.DefineDerivedCounter("L0CacheMissCount", "MemoryCache", "The number of read requests which result in a cache miss from the L0 cache. The L0 cache contains vector data, which is data that may vary in each thread across the wavefront. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,sum40", "a2f08766-ea1b-6eae-6eaf-faa04125d3e6");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(50761);
        internal_counters.push_back(50825);
        internal_counters.push_back(50889);
        internal_counters.push_back(50953);
        internal_counters.push_back(51017);
        internal_counters.push_back(51081);
        internal_counters.push_back(51145);
        internal_counters.push_back(51209);
        internal_counters.push_back(51273);
        internal_counters.push_back(51337);
        internal_counters.push_back(51401);
        internal_counters.push_back(51465);
        internal_counters.push_back(51529);
        internal_counters.push_back(51593);
        internal_counters.push_back(51657);
        internal_counters.push_back(51721);
        internal_counters.push_back(50765);
        internal_counters.push_back(50829);
        internal_counters.push_back(50893);
        internal_counters.push_back(50957);
        internal_counters.push_back(51021);
        internal_counters.push_back(51085);
        internal_counters.push_back(51149);
        internal_counters.push_back(51213);
        internal_counters.push_back(51277);
        internal_counters.push_back(51341);
        internal_counters.push_back(51405);
        internal_counters.push_back(51469);
        internal_counters.push_back(51533);
        internal_counters.push_back(51597);
        internal_counters.push_back(51661);
        internal_counters.push_back(51725);

        c.DefineDerivedCounter("L1CacheHit", "MemoryCache", "The percentage of read or write requests that hit the data in the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "5a34915a-24b8-8baf-2bf8-5878e7894ae3");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(50761);
        internal_counters.push_back(50825);
        internal_counters.push_back(50889);
        internal_counters.push_back(50953);
        internal_counters.push_back(51017);
        internal_counters.push_back(51081);
        internal_counters.push_back(51145);
        internal_counters.push_back(51209);
        internal_counters.push_back(51273);
        internal_counters.push_back(51337);
        internal_counters.push_back(51401);
        internal_counters.push_back(51465);
        internal_counters.push_back(51529);
        internal_counters.push_back(51593);
        internal_counters.push_back(51657);
        internal_counters.push_back(51721);

        c.DefineDerivedCounter("L1CacheRequestCount", "MemoryCache", "The number of read or write requests made to the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "29c76c67-4611-205d-0b88-d08668df03c5");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(50761);
        internal_counters.push_back(50825);
        internal_counters.push_back(50889);
        internal_counters.push_back(50953);
        internal_counters.push_back(51017);
        internal_counters.push_back(51081);
        internal_counters.push_back(51145);
        internal_counters.push_back(51209);
        internal_counters.push_back(51273);
        internal_counters.push_back(51337);
        internal_counters.push_back(51401);
        internal_counters.push_back(51465);
        internal_counters.push_back(51529);
        internal_counters.push_back(51593);
        internal_counters.push_back(51657);
        internal_counters.push_back(51721);
        internal_counters.push_back(50765);
        internal_counters.push_back(50829);
        internal_counters.push_back(50893);
        internal_counters.push_back(50957);
        internal_counters.push_back(51021);
        internal_counters.push_back(51085);
        internal_counters.push_back(51149);
        internal_counters.push_back(51213);
        internal_counters.push_back(51277);
        internal_counters.push_back(51341);
        internal_counters.push_back(51405);
        internal_counters.push_back(51469);
        internal_counters.push_back(51533);
        internal_counters.push_back(51597);
        internal_counters.push_back(51661);
        internal_counters.push_back(51725);

        c.DefineDerivedCounter("L1CacheHitCount", "MemoryCache", "The number of read or write requests which result in a cache hit from the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-", "1ae150c3-f2d0-82c6-a51b-a77fd8d5fc33");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(50765);
        internal_counters.push_back(50829);
        internal_counters.push_back(50893);
        internal_counters.push_back(50957);
        internal_counters.push_back(51021);
        internal_counters.push_back(51085);
        internal_counters.push_back(51149);
        internal_counters.push_back(51213);
        internal_counters.push_back(51277);
        internal_counters.push_back(51341);
        internal_counters.push_back(51405);
        internal_counters.push_back(51469);
        internal_counters.push_back(51533);
        internal_counters.push_back(51597);
        internal_counters.push_back(51661);
        internal_counters.push_back(51725);

        c.DefineDerivedCounter("L1CacheMissCount", "MemoryCache", "The number of read or write requests which result in a cache miss from the L1 cache. The L1 cache is shared across all WGPs in a single shader engine. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "71bfec6d-257b-849d-e212-cdf5c1b1de65");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52746);
        internal_counters.push_back(52981);
        internal_counters.push_back(53216);
        internal_counters.push_back(53451);
        internal_counters.push_back(53686);
        internal_counters.push_back(53921);
        internal_counters.push_back(54156);
        internal_counters.push_back(54391);
        internal_counters.push_back(54626);
        internal_counters.push_back(54861);
        internal_counters.push_back(55096);
        internal_counters.push_back(55331);
        internal_counters.push_back(55566);
        internal_counters.push_back(55801);
        internal_counters.push_back(56036);
        internal_counters.push_back(56271);
        internal_counters.push_back(52778);
        internal_counters.push_back(53013);
        internal_counters.push_back(53248);
        internal_counters.push_back(53483);
        internal_counters.push_back(53718);
        internal_counters.push_back(53953);
        internal_counters.push_back(54188);
        internal_counters.push_back(54423);
        internal_counters.push_back(54658);
        internal_counters.push_back(54893);
        internal_counters.push_back(55128);
        internal_counters.push_back(55363);
        internal_counters.push_back(55598);
        internal_counters.push_back(55833);
        internal_counters.push_back(56068);
        internal_counters.push_back(56303);

        c.DefineDerivedCounter("L2CacheHit", "MemoryCache", "The percentage of read or write requests that hit the data in the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size. Value range: 0% (no hit) to 100% (optimal).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "(0),(1),16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,-,(100),*,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,ifnotzero", "47694e4d-6ce6-f387-080d-b1f3d00b73ac");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52778);
        internal_counters.push_back(53013);
        internal_counters.push_back(53248);
        internal_counters.push_back(53483);
        internal_counters.push_back(53718);
        internal_counters.push_back(53953);
        internal_counters.push_back(54188);
        internal_counters.push_back(54423);
        internal_counters.push_back(54658);
        internal_counters.push_back(54893);
        internal_counters.push_back(55128);
        internal_counters.push_back(55363);
        internal_counters.push_back(55598);
        internal_counters.push_back(55833);
        internal_counters.push_back(56068);
        internal_counters.push_back(56303);
        internal_counters.push_back(52746);
        internal_counters.push_back(52981);
        internal_counters.push_back(53216);
        internal_counters.push_back(53451);
        internal_counters.push_back(53686);
        internal_counters.push_back(53921);
        internal_counters.push_back(54156);
        internal_counters.push_back(54391);
        internal_counters.push_back(54626);
        internal_counters.push_back(54861);
        internal_counters.push_back(55096);
        internal_counters.push_back(55331);
        internal_counters.push_back(55566);
        internal_counters.push_back(55801);
        internal_counters.push_back(56036);
        internal_counters.push_back(56271);

        c.DefineDerivedCounter("L2CacheMiss", "MemoryCache", "The percentage of read or write requests that miss the data in the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size. Value range: 0% (optimal) to 100% (all miss).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*", "8aee5458-a58e-11b6-5131-7f19ed070117");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52746);
        internal_counters.push_back(52981);
        internal_counters.push_back(53216);
        internal_counters.push_back(53451);
        internal_counters.push_back(53686);
        internal_counters.push_back(53921);
        internal_counters.push_back(54156);
        internal_counters.push_back(54391);
        internal_counters.push_back(54626);
        internal_counters.push_back(54861);
        internal_counters.push_back(55096);
        internal_counters.push_back(55331);
        internal_counters.push_back(55566);
        internal_counters.push_back(55801);
        internal_counters.push_back(56036);
        internal_counters.push_back(56271);

        c.DefineDerivedCounter("L2CacheRequestCount", "MemoryCache", "The number of read or write requests made to the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "21e9219c-e725-0d96-06b1-b21698b736b2");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52746);
        internal_counters.push_back(52981);
        internal_counters.push_back(53216);
        internal_counters.push_back(53451);
        internal_counters.push_back(53686);
        internal_counters.push_back(53921);
        internal_counters.push_back(54156);
        internal_counters.push_back(54391);
        internal_counters.push_back(54626);
        internal_counters.push_back(54861);
        internal_counters.push_back(55096);
        internal_counters.push_back(55331);
        internal_counters.push_back(55566);
        internal_counters.push_back(55801);
        internal_counters.push_back(56036);
        internal_counters.push_back(56271);
        internal_counters.push_back(52778);
        internal_counters.push_back(53013);
        internal_counters.push_back(53248);
        internal_counters.push_back(53483);
        internal_counters.push_back(53718);
        internal_counters.push_back(53953);
        internal_counters.push_back(54188);
        internal_counters.push_back(54423);
        internal_counters.push_back(54658);
        internal_counters.push_back(54893);
        internal_counters.push_back(55128);
        internal_counters.push_back(55363);
        internal_counters.push_back(55598);
        internal_counters.push_back(55833);
        internal_counters.push_back(56068);
        internal_counters.push_back(56303);

        c.DefineDerivedCounter("L2CacheHitCount", "MemoryCache", "The number of read or write requests which result in a cache hit from the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-", "29ddcb92-d3dd-951b-1b23-efe52e4eeee4");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52778);
        internal_counters.push_back(53013);
        internal_counters.push_back(53248);
        internal_counters.push_back(53483);
        internal_counters.push_back(53718);
        internal_counters.push_back(53953);
        internal_counters.push_back(54188);
        internal_counters.push_back(54423);
        internal_counters.push_back(54658);
        internal_counters.push_back(54893);
        internal_counters.push_back(55128);
        internal_counters.push_back(55363);
        internal_counters.push_back(55598);
        internal_counters.push_back(55833);
        internal_counters.push_back(56068);
        internal_counters.push_back(56303);

        c.DefineDerivedCounter("L2CacheMissCount", "MemoryCache", "The number of read or write requests which result in a cache miss from the L2 cache. The L2 cache is shared by many blocks across the GPU, including the Command Processor, Geometry Engine, all WGPs, all Render Backends, and others. Each request is 128 bytes in size.", kGpaDataTypeFloat64, kGpaUsageTypeItems, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "376eec7b-ab25-9012-06b5-63291a17fd47");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52832);
        internal_counters.push_back(53067);
        internal_counters.push_back(53302);
        internal_counters.push_back(53537);
        internal_counters.push_back(53772);
        internal_counters.push_back(54007);
        internal_counters.push_back(54242);
        internal_counters.push_back(54477);
        internal_counters.push_back(54712);
        internal_counters.push_back(54947);
        internal_counters.push_back(55182);
        internal_counters.push_back(55417);
        internal_counters.push_back(55652);
        internal_counters.push_back(55887);
        internal_counters.push_back(56122);
        internal_counters.push_back(56357);
        internal_counters.push_back(52833);
        internal_counters.push_back(53068);
        internal_counters.push_back(53303);
        internal_counters.push_back(53538);
        internal_counters.push_back(53773);
        internal_counters.push_back(54008);
        internal_counters.push_back(54243);
        internal_counters.push_back(54478);
        internal_counters.push_back(54713);
        internal_counters.push_back(54948);
        internal_counters.push_back(55183);
        internal_counters.push_back(55418);
        internal_counters.push_back(55653);
        internal_counters.push_back(55888);
        internal_counters.push_back(56123);
        internal_counters.push_back(56358);
        internal_counters.push_back(52834);
        internal_counters.push_back(53069);
        internal_counters.push_back(53304);
        internal_counters.push_back(53539);
        internal_counters.push_back(53774);
        internal_counters.push_back(54009);
        internal_counters.push_back(54244);
        internal_counters.push_back(54479);
        internal_counters.push_back(54714);
        internal_counters.push_back(54949);
        internal_counters.push_back(55184);
        internal_counters.push_back(55419);
        internal_counters.push_back(55654);
        internal_counters.push_back(55889);
        internal_counters.push_back(56124);
        internal_counters.push_back(56359);
        internal_counters.push_back(52835);
        internal_counters.push_back(53070);
        internal_counters.push_back(53305);
        internal_counters.push_back(53540);
        internal_counters.push_back(53775);
        internal_counters.push_back(54010);
        internal_counters.push_back(54245);
        internal_counters.push_back(54480);
        internal_counters.push_back(54715);
        internal_counters.push_back(54950);
        internal_counters.push_back(55185);
        internal_counters.push_back(55420);
        internal_counters.push_back(55655);
        internal_counters.push_back(55890);
        internal_counters.push_back(56125);
        internal_counters.push_back(56360);

        c.DefineDerivedCounter("FetchSize", "GlobalMemory", "The total bytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,sum16,(96),*,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum16,(128),*,sum4", "664bb3ef-6eca-86b1-1e2d-30cb897b5fa9");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52818);
        internal_counters.push_back(53053);
        internal_counters.push_back(53288);
        internal_counters.push_back(53523);
        internal_counters.push_back(53758);
        internal_counters.push_back(53993);
        internal_counters.push_back(54228);
        internal_counters.push_back(54463);
        internal_counters.push_back(54698);
        internal_counters.push_back(54933);
        internal_counters.push_back(55168);
        internal_counters.push_back(55403);
        internal_counters.push_back(55638);
        internal_counters.push_back(55873);
        internal_counters.push_back(56108);
        internal_counters.push_back(56343);
        internal_counters.push_back(52819);
        internal_counters.push_back(53054);
        internal_counters.push_back(53289);
        internal_counters.push_back(53524);
        internal_counters.push_back(53759);
        internal_counters.push_back(53994);
        internal_counters.push_back(54229);
        internal_counters.push_back(54464);
        internal_counters.push_back(54699);
        internal_counters.push_back(54934);
        internal_counters.push_back(55169);
        internal_counters.push_back(55404);
        internal_counters.push_back(55639);
        internal_counters.push_back(55874);
        internal_counters.push_back(56109);
        internal_counters.push_back(56344);

        c.DefineDerivedCounter("WriteSize", "GlobalMemory", "The total bytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeBytes, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+", "f96f2c16-b1b4-4ec4-229c-fc82e6f80a82");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15285);
        internal_counters.push_back(15511);
        internal_counters.push_back(15737);
        internal_counters.push_back(15963);
        internal_counters.push_back(16189);
        internal_counters.push_back(16415);
        internal_counters.push_back(16641);
        internal_counters.push_back(16867);
        internal_counters.push_back(17093);
        internal_counters.push_back(17319);
        internal_counters.push_back(17545);
        internal_counters.push_back(17771);
        internal_counters.push_back(17997);
        internal_counters.push_back(18223);
        internal_counters.push_back(18449);
        internal_counters.push_back(18675);
        internal_counters.push_back(18901);
        internal_counters.push_back(19127);
        internal_counters.push_back(19353);
        internal_counters.push_back(19579);
        internal_counters.push_back(19805);
        internal_counters.push_back(20031);
        internal_counters.push_back(20257);
        internal_counters.push_back(20483);
        internal_counters.push_back(20709);
        internal_counters.push_back(20935);
        internal_counters.push_back(21161);
        internal_counters.push_back(21387);
        internal_counters.push_back(21613);
        internal_counters.push_back(21839);
        internal_counters.push_back(22065);
        internal_counters.push_back(22291);
        internal_counters.push_back(22517);
        internal_counters.push_back(22743);
        internal_counters.push_back(22969);
        internal_counters.push_back(23195);
        internal_counters.push_back(23421);
        internal_counters.push_back(23647);
        internal_counters.push_back(23873);
        internal_counters.push_back(24099);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(15285);
        internal_counters.push_back(15511);
        internal_counters.push_back(15737);
        internal_counters.push_back(15963);
        internal_counters.push_back(16189);
        internal_counters.push_back(16415);
        internal_counters.push_back(16641);
        internal_counters.push_back(16867);
        internal_counters.push_back(17093);
        internal_counters.push_back(17319);
        internal_counters.push_back(17545);
        internal_counters.push_back(17771);
        internal_counters.push_back(17997);
        internal_counters.push_back(18223);
        internal_counters.push_back(18449);
        internal_counters.push_back(18675);
        internal_counters.push_back(18901);
        internal_counters.push_back(19127);
        internal_counters.push_back(19353);
        internal_counters.push_back(19579);
        internal_counters.push_back(19805);
        internal_counters.push_back(20031);
        internal_counters.push_back(20257);
        internal_counters.push_back(20483);
        internal_counters.push_back(20709);
        internal_counters.push_back(20935);
        internal_counters.push_back(21161);
        internal_counters.push_back(21387);
        internal_counters.push_back(21613);
        internal_counters.push_back(21839);
        internal_counters.push_back(22065);
        internal_counters.push_back(22291);
        internal_counters.push_back(22517);
        internal_counters.push_back(22743);
        internal_counters.push_back(22969);
        internal_counters.push_back(23195);
        internal_counters.push_back(23421);
        internal_counters.push_back(23647);
        internal_counters.push_back(23873);
        internal_counters.push_back(24099);

        c.DefineDerivedCounter("MemUnitBusyCycles", "GlobalMemory", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalledCycles). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40", "168f077c-4797-b2f5-717f-105c725266c8");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(26786);
        internal_counters.push_back(26863);
        internal_counters.push_back(26940);
        internal_counters.push_back(27017);
        internal_counters.push_back(27094);
        internal_counters.push_back(27171);
        internal_counters.push_back(27248);
        internal_counters.push_back(27325);
        internal_counters.push_back(27402);
        internal_counters.push_back(27479);
        internal_counters.push_back(27556);
        internal_counters.push_back(27633);
        internal_counters.push_back(27710);
        internal_counters.push_back(27787);
        internal_counters.push_back(27864);
        internal_counters.push_back(27941);
        internal_counters.push_back(28018);
        internal_counters.push_back(28095);
        internal_counters.push_back(28172);
        internal_counters.push_back(28249);
        internal_counters.push_back(28326);
        internal_counters.push_back(28403);
        internal_counters.push_back(28480);
        internal_counters.push_back(28557);
        internal_counters.push_back(28634);
        internal_counters.push_back(28711);
        internal_counters.push_back(28788);
        internal_counters.push_back(28865);
        internal_counters.push_back(28942);
        internal_counters.push_back(29019);
        internal_counters.push_back(29096);
        internal_counters.push_back(29173);
        internal_counters.push_back(29250);
        internal_counters.push_back(29327);
        internal_counters.push_back(29404);
        internal_counters.push_back(29481);
        internal_counters.push_back(29558);
        internal_counters.push_back(29635);
        internal_counters.push_back(29712);
        internal_counters.push_back(29789);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40,40,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(26786);
        internal_counters.push_back(26863);
        internal_counters.push_back(26940);
        internal_counters.push_back(27017);
        internal_counters.push_back(27094);
        internal_counters.push_back(27171);
        internal_counters.push_back(27248);
        internal_counters.push_back(27325);
        internal_counters.push_back(27402);
        internal_counters.push_back(27479);
        internal_counters.push_back(27556);
        internal_counters.push_back(27633);
        internal_counters.push_back(27710);
        internal_counters.push_back(27787);
        internal_counters.push_back(27864);
        internal_counters.push_back(27941);
        internal_counters.push_back(28018);
        internal_counters.push_back(28095);
        internal_counters.push_back(28172);
        internal_counters.push_back(28249);
        internal_counters.push_back(28326);
        internal_counters.push_back(28403);
        internal_counters.push_back(28480);
        internal_counters.push_back(28557);
        internal_counters.push_back(28634);
        internal_counters.push_back(28711);
        internal_counters.push_back(28788);
        internal_counters.push_back(28865);
        internal_counters.push_back(28942);
        internal_counters.push_back(29019);
        internal_counters.push_back(29096);
        internal_counters.push_back(29173);
        internal_counters.push_back(29250);
        internal_counters.push_back(29327);
        internal_counters.push_back(29404);
        internal_counters.push_back(29481);
        internal_counters.push_back(29558);
        internal_counters.push_back(29635);
        internal_counters.push_back(29712);
        internal_counters.push_back(29789);

        c.DefineDerivedCounter("MemUnitStalledCycles", "GlobalMemory", "Number of GPU cycles the memory unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,max40", "2745659a-0e40-bace-3b9b-86a54f8e4623");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52822);
        internal_counters.push_back(53057);
        internal_counters.push_back(53292);
        internal_counters.push_back(53527);
        internal_counters.push_back(53762);
        internal_counters.push_back(53997);
        internal_counters.push_back(54232);
        internal_counters.push_back(54467);
        internal_counters.push_back(54702);
        internal_counters.push_back(54937);
        internal_counters.push_back(55172);
        internal_counters.push_back(55407);
        internal_counters.push_back(55642);
        internal_counters.push_back(55877);
        internal_counters.push_back(56112);
        internal_counters.push_back(56347);
        internal_counters.push_back(24);

        c.DefineDerivedCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", kGpaDataTypeFloat64, kGpaUsageTypePercentage, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72");
    }
    {
        vector<GpaUInt32> internal_counters;
        internal_counters.push_back(52822);
        internal_counters.push_back(53057);
        internal_counters.push_back(53292);
        internal_counters.push_back(53527);
        internal_counters.push_back(53762);
        internal_counters.push_back(53997);
        internal_counters.push_back(54232);
        internal_counters.push_back(54467);
        internal_counters.push_back(54702);
        internal_counters.push_back(54937);
        internal_counters.push_back(55172);
        internal_counters.push_back(55407);
        internal_counters.push_back(55642);
        internal_counters.push_back(55877);
        internal_counters.push_back(56112);
        internal_counters.push_back(56347);

        c.DefineDerivedCounter("WriteUnitStalledCycles", "GlobalMemory", "Number of GPU cycles the Write unit is stalled.", kGpaDataTypeFloat64, kGpaUsageTypeCycles, internal_counters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "ede3305e-abd4-d6bf-6b00-ffc57a29fce3");
    }
}

