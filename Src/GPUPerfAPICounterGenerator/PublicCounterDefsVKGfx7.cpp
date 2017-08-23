//==============================================================================
// Copyright (c) 2010-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  PublicCounterDefinitions for VKGFX7
//==============================================================================

#include "PublicCounterDefsVKGfx7.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicCountersVKGfx7(GPA_PublicCounters& p)
{
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(36722);

        p.DefinePublicCounter("GPUTime", "Timing", "Time this API call took to execute on the GPU in milliseconds. Does not include time that draw calls are processed in parallel.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_API_DYNAMIC, internalCounters, "0,TS_FREQ,/,(1000),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(36073);
        internalCounters.push_back(36071);

        p.DefinePublicCounter("GPUBusy", "Timing", "The percentage of time GPU was busy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(36073);

        p.DefinePublicCounter("GPUBusyCycles", "Timing", "Number of GPU cycles that the GPU was busy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(186);
        internalCounters.push_back(326);
        internalCounters.push_back(466);
        internalCounters.push_back(606);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("TessellatorBusy", "Timing", "The percentage of time the tessellation engine is busy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(186);
        internalCounters.push_back(326);
        internalCounters.push_back(466);
        internalCounters.push_back(606);

        p.DefinePublicCounter("TessellatorBusyCycles", "Timing", "Number of GPU cycles that the tessellation engine is busy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2814);
        internalCounters.push_back(3000);
        internalCounters.push_back(3186);
        internalCounters.push_back(3372);
        internalCounters.push_back(2839);
        internalCounters.push_back(3025);
        internalCounters.push_back(3211);
        internalCounters.push_back(3397);
        internalCounters.push_back(2861);
        internalCounters.push_back(3047);
        internalCounters.push_back(3233);
        internalCounters.push_back(3419);
        internalCounters.push_back(2883);
        internalCounters.push_back(3069);
        internalCounters.push_back(3255);
        internalCounters.push_back(3441);
        internalCounters.push_back(2823);
        internalCounters.push_back(3009);
        internalCounters.push_back(3195);
        internalCounters.push_back(3381);
        internalCounters.push_back(2845);
        internalCounters.push_back(3031);
        internalCounters.push_back(3217);
        internalCounters.push_back(3403);
        internalCounters.push_back(2867);
        internalCounters.push_back(3053);
        internalCounters.push_back(3239);
        internalCounters.push_back(3425);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("VSBusy", "Timing", "The percentage of time the ShaderUnit has vertex shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,16,ifnotzero,4,20,ifnotzero,8,24,ifnotzero,(0),1,17,ifnotzero,5,21,ifnotzero,9,25,ifnotzero,max,(0),2,18,ifnotzero,6,22,ifnotzero,10,26,ifnotzero,max,(0),3,19,ifnotzero,7,23,ifnotzero,11,27,ifnotzero,max,28,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2814);
        internalCounters.push_back(3000);
        internalCounters.push_back(3186);
        internalCounters.push_back(3372);
        internalCounters.push_back(2839);
        internalCounters.push_back(3025);
        internalCounters.push_back(3211);
        internalCounters.push_back(3397);
        internalCounters.push_back(2861);
        internalCounters.push_back(3047);
        internalCounters.push_back(3233);
        internalCounters.push_back(3419);
        internalCounters.push_back(2883);
        internalCounters.push_back(3069);
        internalCounters.push_back(3255);
        internalCounters.push_back(3441);
        internalCounters.push_back(2823);
        internalCounters.push_back(3009);
        internalCounters.push_back(3195);
        internalCounters.push_back(3381);
        internalCounters.push_back(2845);
        internalCounters.push_back(3031);
        internalCounters.push_back(3217);
        internalCounters.push_back(3403);
        internalCounters.push_back(2867);
        internalCounters.push_back(3053);
        internalCounters.push_back(3239);
        internalCounters.push_back(3425);

        p.DefinePublicCounter("VSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has vertex shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,16,ifnotzero,4,20,ifnotzero,8,24,ifnotzero,(0),1,17,ifnotzero,5,21,ifnotzero,9,25,ifnotzero,max,(0),2,18,ifnotzero,6,22,ifnotzero,10,26,ifnotzero,max,(0),3,19,ifnotzero,7,23,ifnotzero,11,27,ifnotzero,max");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(36722);
        internalCounters.push_back(2814);
        internalCounters.push_back(3000);
        internalCounters.push_back(3186);
        internalCounters.push_back(3372);
        internalCounters.push_back(2839);
        internalCounters.push_back(3025);
        internalCounters.push_back(3211);
        internalCounters.push_back(3397);
        internalCounters.push_back(2861);
        internalCounters.push_back(3047);
        internalCounters.push_back(3233);
        internalCounters.push_back(3419);
        internalCounters.push_back(2883);
        internalCounters.push_back(3069);
        internalCounters.push_back(3255);
        internalCounters.push_back(3441);
        internalCounters.push_back(2823);
        internalCounters.push_back(3009);
        internalCounters.push_back(3195);
        internalCounters.push_back(3381);
        internalCounters.push_back(2845);
        internalCounters.push_back(3031);
        internalCounters.push_back(3217);
        internalCounters.push_back(3403);
        internalCounters.push_back(2867);
        internalCounters.push_back(3053);
        internalCounters.push_back(3239);
        internalCounters.push_back(3425);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("VSTime", "Timing", "Time vertex shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,17,ifnotzero,5,21,ifnotzero,9,25,ifnotzero,(0),2,18,ifnotzero,6,22,ifnotzero,10,26,ifnotzero,max,(0),3,19,ifnotzero,7,23,ifnotzero,11,27,ifnotzero,max,(0),4,20,ifnotzero,8,24,ifnotzero,12,28,ifnotzero,max,29,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2851);
        internalCounters.push_back(3037);
        internalCounters.push_back(3223);
        internalCounters.push_back(3409);
        internalCounters.push_back(2857);
        internalCounters.push_back(3043);
        internalCounters.push_back(3229);
        internalCounters.push_back(3415);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("HSBusy", "Timing", "The percentage of time the ShaderUnit has hull shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,8,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2851);
        internalCounters.push_back(3037);
        internalCounters.push_back(3223);
        internalCounters.push_back(3409);
        internalCounters.push_back(2857);
        internalCounters.push_back(3043);
        internalCounters.push_back(3229);
        internalCounters.push_back(3415);

        p.DefinePublicCounter("HSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has hull shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(36722);
        internalCounters.push_back(2851);
        internalCounters.push_back(3037);
        internalCounters.push_back(3223);
        internalCounters.push_back(3409);
        internalCounters.push_back(2857);
        internalCounters.push_back(3043);
        internalCounters.push_back(3229);
        internalCounters.push_back(3415);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("HSTime", "Timing", "Time hull shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,5,ifnotzero,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,(0),4,8,ifnotzero,max,9,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2814);
        internalCounters.push_back(3000);
        internalCounters.push_back(3186);
        internalCounters.push_back(3372);
        internalCounters.push_back(2839);
        internalCounters.push_back(3025);
        internalCounters.push_back(3211);
        internalCounters.push_back(3397);
        internalCounters.push_back(2883);
        internalCounters.push_back(3069);
        internalCounters.push_back(3255);
        internalCounters.push_back(3441);
        internalCounters.push_back(2845);
        internalCounters.push_back(3031);
        internalCounters.push_back(3217);
        internalCounters.push_back(3403);
        internalCounters.push_back(2867);
        internalCounters.push_back(3053);
        internalCounters.push_back(3239);
        internalCounters.push_back(3425);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("DSBusy", "Timing", "The percentage of time the ShaderUnit has domain shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,12,ifnotzero,16,ifnotzero,(0),1,5,13,ifnotzero,17,ifnotzero,max,(0),2,6,14,ifnotzero,18,ifnotzero,max,(0),3,7,15,ifnotzero,19,ifnotzero,max,20,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2814);
        internalCounters.push_back(3000);
        internalCounters.push_back(3186);
        internalCounters.push_back(3372);
        internalCounters.push_back(2839);
        internalCounters.push_back(3025);
        internalCounters.push_back(3211);
        internalCounters.push_back(3397);
        internalCounters.push_back(2883);
        internalCounters.push_back(3069);
        internalCounters.push_back(3255);
        internalCounters.push_back(3441);
        internalCounters.push_back(2845);
        internalCounters.push_back(3031);
        internalCounters.push_back(3217);
        internalCounters.push_back(3403);
        internalCounters.push_back(2867);
        internalCounters.push_back(3053);
        internalCounters.push_back(3239);
        internalCounters.push_back(3425);

        p.DefinePublicCounter("DSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has domain shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,12,ifnotzero,16,ifnotzero,(0),1,5,13,ifnotzero,17,ifnotzero,max,(0),2,6,14,ifnotzero,18,ifnotzero,max,(0),3,7,15,ifnotzero,19,ifnotzero,max");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(36722);
        internalCounters.push_back(2814);
        internalCounters.push_back(3000);
        internalCounters.push_back(3186);
        internalCounters.push_back(3372);
        internalCounters.push_back(2839);
        internalCounters.push_back(3025);
        internalCounters.push_back(3211);
        internalCounters.push_back(3397);
        internalCounters.push_back(2883);
        internalCounters.push_back(3069);
        internalCounters.push_back(3255);
        internalCounters.push_back(3441);
        internalCounters.push_back(2845);
        internalCounters.push_back(3031);
        internalCounters.push_back(3217);
        internalCounters.push_back(3403);
        internalCounters.push_back(2867);
        internalCounters.push_back(3053);
        internalCounters.push_back(3239);
        internalCounters.push_back(3425);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("DSTime", "Timing", "Time domain shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,5,13,ifnotzero,17,ifnotzero,(0),2,6,14,ifnotzero,18,ifnotzero,max,(0),3,7,15,ifnotzero,19,ifnotzero,max,(0),4,8,16,ifnotzero,20,ifnotzero,max,21,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2830);
        internalCounters.push_back(3016);
        internalCounters.push_back(3202);
        internalCounters.push_back(3388);
        internalCounters.push_back(2833);
        internalCounters.push_back(3019);
        internalCounters.push_back(3205);
        internalCounters.push_back(3391);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("GSBusy", "Timing", "The percentage of time the ShaderUnit has geometry shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,8,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2830);
        internalCounters.push_back(3016);
        internalCounters.push_back(3202);
        internalCounters.push_back(3388);
        internalCounters.push_back(2833);
        internalCounters.push_back(3019);
        internalCounters.push_back(3205);
        internalCounters.push_back(3391);

        p.DefinePublicCounter("GSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has geometry shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(36722);
        internalCounters.push_back(2830);
        internalCounters.push_back(3016);
        internalCounters.push_back(3202);
        internalCounters.push_back(3388);
        internalCounters.push_back(2833);
        internalCounters.push_back(3019);
        internalCounters.push_back(3205);
        internalCounters.push_back(3391);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("GSTime", "Timing", "Time geometry shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,5,ifnotzero,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,(0),4,8,ifnotzero,max,9,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2883);
        internalCounters.push_back(3069);
        internalCounters.push_back(3255);
        internalCounters.push_back(3441);
        internalCounters.push_back(2888);
        internalCounters.push_back(3074);
        internalCounters.push_back(3260);
        internalCounters.push_back(3446);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("PSBusy", "Timing", "The percentage of time the ShaderUnit has pixel shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,8,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2883);
        internalCounters.push_back(3069);
        internalCounters.push_back(3255);
        internalCounters.push_back(3441);
        internalCounters.push_back(2888);
        internalCounters.push_back(3074);
        internalCounters.push_back(3260);
        internalCounters.push_back(3446);

        p.DefinePublicCounter("PSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has pixel shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(36722);
        internalCounters.push_back(2883);
        internalCounters.push_back(3069);
        internalCounters.push_back(3255);
        internalCounters.push_back(3441);
        internalCounters.push_back(2888);
        internalCounters.push_back(3074);
        internalCounters.push_back(3260);
        internalCounters.push_back(3446);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("PSTime", "Timing", "Time pixel shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,5,ifnotzero,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,(0),4,8,ifnotzero,max,9,/,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2871);
        internalCounters.push_back(3057);
        internalCounters.push_back(3243);
        internalCounters.push_back(3429);
        internalCounters.push_back(2875);
        internalCounters.push_back(3061);
        internalCounters.push_back(3247);
        internalCounters.push_back(3433);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("CSBusy", "Timing", "The percentage of time the ShaderUnit has compute shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,8,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2871);
        internalCounters.push_back(3057);
        internalCounters.push_back(3243);
        internalCounters.push_back(3429);
        internalCounters.push_back(2875);
        internalCounters.push_back(3061);
        internalCounters.push_back(3247);
        internalCounters.push_back(3433);

        p.DefinePublicCounter("CSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has compute shader work to do.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(36722);
        internalCounters.push_back(2871);
        internalCounters.push_back(3057);
        internalCounters.push_back(3243);
        internalCounters.push_back(3429);
        internalCounters.push_back(2875);
        internalCounters.push_back(3061);
        internalCounters.push_back(3247);
        internalCounters.push_back(3433);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("CSTime", "Timing", "Time compute shaders are busy in milliseconds.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,5,ifnotzero,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,(0),4,8,ifnotzero,max,9,/,(1),min,0,TS_FREQ,/,(1000),*,*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(81);
        internalCounters.push_back(221);
        internalCounters.push_back(361);
        internalCounters.push_back(501);
        internalCounters.push_back(62);
        internalCounters.push_back(202);
        internalCounters.push_back(342);
        internalCounters.push_back(482);
        internalCounters.push_back(157);
        internalCounters.push_back(297);
        internalCounters.push_back(437);
        internalCounters.push_back(577);

        p.DefinePublicCounter("VSVerticesIn", "VertexShader", "The number of vertices processed by the VS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,4,5,6,7,sum4,ifnotzero,8,9,10,11,sum4,8,9,10,11,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6607);
        internalCounters.push_back(6859);
        internalCounters.push_back(7111);
        internalCounters.push_back(7363);
        internalCounters.push_back(6585);
        internalCounters.push_back(6837);
        internalCounters.push_back(7089);
        internalCounters.push_back(7341);
        internalCounters.push_back(4591);
        internalCounters.push_back(4843);
        internalCounters.push_back(5095);
        internalCounters.push_back(5347);
        internalCounters.push_back(4569);
        internalCounters.push_back(4821);
        internalCounters.push_back(5073);
        internalCounters.push_back(5325);
        internalCounters.push_back(4579);
        internalCounters.push_back(4831);
        internalCounters.push_back(5083);
        internalCounters.push_back(5335);
        internalCounters.push_back(8623);
        internalCounters.push_back(8875);
        internalCounters.push_back(9127);
        internalCounters.push_back(9379);
        internalCounters.push_back(8601);
        internalCounters.push_back(8853);
        internalCounters.push_back(9105);
        internalCounters.push_back(9357);
        internalCounters.push_back(8611);
        internalCounters.push_back(8863);
        internalCounters.push_back(9115);
        internalCounters.push_back(9367);

        p.DefinePublicCounter("VSVALUInstCount", "VertexShader", "Average number of vector ALU instructions executed in the VS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,12,13,14,15,sum4,/,16,17,18,19,sum4,ifnotzero,20,21,22,23,sum4,24,25,26,27,sum4,/,28,29,30,31,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6611);
        internalCounters.push_back(6863);
        internalCounters.push_back(7115);
        internalCounters.push_back(7367);
        internalCounters.push_back(6585);
        internalCounters.push_back(6837);
        internalCounters.push_back(7089);
        internalCounters.push_back(7341);
        internalCounters.push_back(4595);
        internalCounters.push_back(4847);
        internalCounters.push_back(5099);
        internalCounters.push_back(5351);
        internalCounters.push_back(4569);
        internalCounters.push_back(4821);
        internalCounters.push_back(5073);
        internalCounters.push_back(5325);
        internalCounters.push_back(4579);
        internalCounters.push_back(4831);
        internalCounters.push_back(5083);
        internalCounters.push_back(5335);
        internalCounters.push_back(8627);
        internalCounters.push_back(8879);
        internalCounters.push_back(9131);
        internalCounters.push_back(9383);
        internalCounters.push_back(8601);
        internalCounters.push_back(8853);
        internalCounters.push_back(9105);
        internalCounters.push_back(9357);
        internalCounters.push_back(8611);
        internalCounters.push_back(8863);
        internalCounters.push_back(9115);
        internalCounters.push_back(9367);

        p.DefinePublicCounter("VSSALUInstCount", "VertexShader", "Average number of scalar ALU instructions executed in the VS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,12,13,14,15,sum4,/,16,17,18,19,sum4,ifnotzero,20,21,22,23,sum4,24,25,26,27,sum4,/,28,29,30,31,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6662);
        internalCounters.push_back(6914);
        internalCounters.push_back(7166);
        internalCounters.push_back(7418);
        internalCounters.push_back(4646);
        internalCounters.push_back(4898);
        internalCounters.push_back(5150);
        internalCounters.push_back(5402);
        internalCounters.push_back(4579);
        internalCounters.push_back(4831);
        internalCounters.push_back(5083);
        internalCounters.push_back(5335);
        internalCounters.push_back(36073);
        internalCounters.push_back(8678);
        internalCounters.push_back(8930);
        internalCounters.push_back(9182);
        internalCounters.push_back(9434);
        internalCounters.push_back(8611);
        internalCounters.push_back(8863);
        internalCounters.push_back(9115);
        internalCounters.push_back(9367);

        p.DefinePublicCounter("VSVALUBusy", "VertexShader", "The percentage of GPUTime vector ALU instructions are being processed by the VS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,ifnotzero,13,14,15,16,sum4,17,18,19,20,sum4,ifnotzero,(4),*,NUM_SIMDS,/,12,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6662);
        internalCounters.push_back(6914);
        internalCounters.push_back(7166);
        internalCounters.push_back(7418);
        internalCounters.push_back(4646);
        internalCounters.push_back(4898);
        internalCounters.push_back(5150);
        internalCounters.push_back(5402);
        internalCounters.push_back(4579);
        internalCounters.push_back(4831);
        internalCounters.push_back(5083);
        internalCounters.push_back(5335);
        internalCounters.push_back(36073);
        internalCounters.push_back(8678);
        internalCounters.push_back(8930);
        internalCounters.push_back(9182);
        internalCounters.push_back(9434);
        internalCounters.push_back(8611);
        internalCounters.push_back(8863);
        internalCounters.push_back(9115);
        internalCounters.push_back(9367);

        p.DefinePublicCounter("VSVALUBusyCycles", "VertexShader", "Number of GPU cycles where vector ALU instructions are being processed by the VS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,ifnotzero,13,14,15,16,sum4,17,18,19,20,sum4,ifnotzero,(4),*,NUM_SIMDS,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6667);
        internalCounters.push_back(6919);
        internalCounters.push_back(7171);
        internalCounters.push_back(7423);
        internalCounters.push_back(4651);
        internalCounters.push_back(4903);
        internalCounters.push_back(5155);
        internalCounters.push_back(5407);
        internalCounters.push_back(4579);
        internalCounters.push_back(4831);
        internalCounters.push_back(5083);
        internalCounters.push_back(5335);
        internalCounters.push_back(36073);
        internalCounters.push_back(8683);
        internalCounters.push_back(8935);
        internalCounters.push_back(9187);
        internalCounters.push_back(9439);
        internalCounters.push_back(8611);
        internalCounters.push_back(8863);
        internalCounters.push_back(9115);
        internalCounters.push_back(9367);

        p.DefinePublicCounter("VSSALUBusy", "VertexShader", "The percentage of GPUTime scalar ALU instructions are being processed by the VS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,ifnotzero,13,14,15,16,sum4,17,18,19,20,sum4,ifnotzero,(4),*,NUM_SIMDS,/,12,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6667);
        internalCounters.push_back(6919);
        internalCounters.push_back(7171);
        internalCounters.push_back(7423);
        internalCounters.push_back(4651);
        internalCounters.push_back(4903);
        internalCounters.push_back(5155);
        internalCounters.push_back(5407);
        internalCounters.push_back(4579);
        internalCounters.push_back(4831);
        internalCounters.push_back(5083);
        internalCounters.push_back(5335);
        internalCounters.push_back(36073);
        internalCounters.push_back(8683);
        internalCounters.push_back(8935);
        internalCounters.push_back(9187);
        internalCounters.push_back(9439);
        internalCounters.push_back(8611);
        internalCounters.push_back(8863);
        internalCounters.push_back(9115);
        internalCounters.push_back(9367);

        p.DefinePublicCounter("VSSALUBusyCycles", "VertexShader", "Number of GPU cycles where scalar ALU instructions are being processed by the VS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,ifnotzero,13,14,15,16,sum4,17,18,19,20,sum4,ifnotzero,(4),*,NUM_SIMDS,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(166);
        internalCounters.push_back(306);
        internalCounters.push_back(446);
        internalCounters.push_back(586);

        p.DefinePublicCounter("HSPatches", "HullShader", "The number of patches processed by the HS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9631);
        internalCounters.push_back(9883);
        internalCounters.push_back(10135);
        internalCounters.push_back(10387);
        internalCounters.push_back(9609);
        internalCounters.push_back(9861);
        internalCounters.push_back(10113);
        internalCounters.push_back(10365);

        p.DefinePublicCounter("HSVALUInstCount", "HullShader", "Average number of vector ALU instructions executed in the HS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9635);
        internalCounters.push_back(9887);
        internalCounters.push_back(10139);
        internalCounters.push_back(10391);
        internalCounters.push_back(9609);
        internalCounters.push_back(9861);
        internalCounters.push_back(10113);
        internalCounters.push_back(10365);

        p.DefinePublicCounter("HSSALUInstCount", "HullShader", "Average number of scalar ALU instructions executed in the HS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9686);
        internalCounters.push_back(9938);
        internalCounters.push_back(10190);
        internalCounters.push_back(10442);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("HSVALUBusy", "HullShader", "The percentage of GPUTime vector ALU instructions are being processed by the HS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/,4,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9686);
        internalCounters.push_back(9938);
        internalCounters.push_back(10190);
        internalCounters.push_back(10442);

        p.DefinePublicCounter("HSVALUBusyCycles", "HullShader", "Number of GPU cycles vector where ALU instructions are being processed by the HS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9691);
        internalCounters.push_back(9943);
        internalCounters.push_back(10195);
        internalCounters.push_back(10447);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("HSSALUBusy", "HullShader", "The percentage of GPUTime scalar ALU instructions are being processed by the HS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/,4,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9691);
        internalCounters.push_back(9943);
        internalCounters.push_back(10195);
        internalCounters.push_back(10447);

        p.DefinePublicCounter("HSSALUBusyCycles", "HullShader", "Number of GPU cycles where scalar ALU instructions are being processed by the HS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(81);
        internalCounters.push_back(221);
        internalCounters.push_back(361);
        internalCounters.push_back(501);
        internalCounters.push_back(62);
        internalCounters.push_back(202);
        internalCounters.push_back(342);
        internalCounters.push_back(482);
        internalCounters.push_back(157);
        internalCounters.push_back(297);
        internalCounters.push_back(437);
        internalCounters.push_back(577);

        p.DefinePublicCounter("DSVerticesIn", "DomainShader", "The number of vertices processed by the DS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,4,5,6,7,sum4,ifnotzero,8,9,10,11,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6607);
        internalCounters.push_back(6859);
        internalCounters.push_back(7111);
        internalCounters.push_back(7363);
        internalCounters.push_back(6585);
        internalCounters.push_back(6837);
        internalCounters.push_back(7089);
        internalCounters.push_back(7341);
        internalCounters.push_back(4591);
        internalCounters.push_back(4843);
        internalCounters.push_back(5095);
        internalCounters.push_back(5347);
        internalCounters.push_back(4569);
        internalCounters.push_back(4821);
        internalCounters.push_back(5073);
        internalCounters.push_back(5325);
        internalCounters.push_back(4579);
        internalCounters.push_back(4831);
        internalCounters.push_back(5083);
        internalCounters.push_back(5335);
        internalCounters.push_back(8611);
        internalCounters.push_back(8863);
        internalCounters.push_back(9115);
        internalCounters.push_back(9367);

        p.DefinePublicCounter("DSVALUInstCount", "DomainShader", "Average number of vector ALU instructions executed in the DS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,12,13,14,15,sum4,/,16,17,18,19,sum4,ifnotzero,20,21,22,23,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6611);
        internalCounters.push_back(6863);
        internalCounters.push_back(7115);
        internalCounters.push_back(7367);
        internalCounters.push_back(6585);
        internalCounters.push_back(6837);
        internalCounters.push_back(7089);
        internalCounters.push_back(7341);
        internalCounters.push_back(4595);
        internalCounters.push_back(4847);
        internalCounters.push_back(5099);
        internalCounters.push_back(5351);
        internalCounters.push_back(4569);
        internalCounters.push_back(4821);
        internalCounters.push_back(5073);
        internalCounters.push_back(5325);
        internalCounters.push_back(4579);
        internalCounters.push_back(4831);
        internalCounters.push_back(5083);
        internalCounters.push_back(5335);
        internalCounters.push_back(8611);
        internalCounters.push_back(8863);
        internalCounters.push_back(9115);
        internalCounters.push_back(9367);

        p.DefinePublicCounter("DSSALUInstCount", "DomainShader", "Average number of scalar ALU instructions executed in the DS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,12,13,14,15,sum4,/,16,17,18,19,sum4,ifnotzero,20,21,22,23,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6662);
        internalCounters.push_back(6914);
        internalCounters.push_back(7166);
        internalCounters.push_back(7418);
        internalCounters.push_back(4646);
        internalCounters.push_back(4898);
        internalCounters.push_back(5150);
        internalCounters.push_back(5402);
        internalCounters.push_back(36073);
        internalCounters.push_back(4579);
        internalCounters.push_back(4831);
        internalCounters.push_back(5083);
        internalCounters.push_back(5335);
        internalCounters.push_back(8611);
        internalCounters.push_back(8863);
        internalCounters.push_back(9115);
        internalCounters.push_back(9367);

        p.DefinePublicCounter("DSVALUBusy", "DomainShader", "The percentage of GPUTime vector ALU instructions are being processed by the DS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,9,10,11,12,sum4,ifnotzero,13,14,15,16,sum4,ifnotzero,(4),*,NUM_SIMDS,/,8,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6662);
        internalCounters.push_back(6914);
        internalCounters.push_back(7166);
        internalCounters.push_back(7418);
        internalCounters.push_back(4646);
        internalCounters.push_back(4898);
        internalCounters.push_back(5150);
        internalCounters.push_back(5402);
        internalCounters.push_back(36073);
        internalCounters.push_back(4579);
        internalCounters.push_back(4831);
        internalCounters.push_back(5083);
        internalCounters.push_back(5335);
        internalCounters.push_back(8611);
        internalCounters.push_back(8863);
        internalCounters.push_back(9115);
        internalCounters.push_back(9367);

        p.DefinePublicCounter("DSVALUBusyCycles", "DomainShader", "Number of GPU cycles where vector ALU instructions are being processed by the DS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,9,10,11,12,sum4,ifnotzero,13,14,15,16,sum4,ifnotzero,(4),*,NUM_SIMDS,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6667);
        internalCounters.push_back(6919);
        internalCounters.push_back(7171);
        internalCounters.push_back(7423);
        internalCounters.push_back(4651);
        internalCounters.push_back(4903);
        internalCounters.push_back(5155);
        internalCounters.push_back(5407);
        internalCounters.push_back(36073);
        internalCounters.push_back(4579);
        internalCounters.push_back(4831);
        internalCounters.push_back(5083);
        internalCounters.push_back(5335);
        internalCounters.push_back(8611);
        internalCounters.push_back(8863);
        internalCounters.push_back(9115);
        internalCounters.push_back(9367);

        p.DefinePublicCounter("DSSALUBusy", "DomainShader", "The percentage of GPUTime scalar ALU instructions are being processed by the DS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,9,10,11,12,sum4,ifnotzero,13,14,15,16,sum4,ifnotzero,(4),*,NUM_SIMDS,/,8,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6667);
        internalCounters.push_back(6919);
        internalCounters.push_back(7171);
        internalCounters.push_back(7423);
        internalCounters.push_back(4651);
        internalCounters.push_back(4903);
        internalCounters.push_back(5155);
        internalCounters.push_back(5407);
        internalCounters.push_back(36073);
        internalCounters.push_back(4579);
        internalCounters.push_back(4831);
        internalCounters.push_back(5083);
        internalCounters.push_back(5335);
        internalCounters.push_back(8611);
        internalCounters.push_back(8863);
        internalCounters.push_back(9115);
        internalCounters.push_back(9367);

        p.DefinePublicCounter("DSSALUBusyCycles", "DomainShader", "Number of GPU cycles where scalar ALU instructions are being processed by the DS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,9,10,11,12,sum4,ifnotzero,13,14,15,16,sum4,ifnotzero,(4),*,NUM_SIMDS,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(70);
        internalCounters.push_back(210);
        internalCounters.push_back(350);
        internalCounters.push_back(490);

        p.DefinePublicCounter("GSPrimsIn", "GeometryShader", "The number of primitives passed into the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(81);
        internalCounters.push_back(221);
        internalCounters.push_back(361);
        internalCounters.push_back(501);
        internalCounters.push_back(62);
        internalCounters.push_back(202);
        internalCounters.push_back(342);
        internalCounters.push_back(482);

        p.DefinePublicCounter("GSVerticesOut", "GeometryShader", "The number of vertices output by the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5599);
        internalCounters.push_back(5851);
        internalCounters.push_back(6103);
        internalCounters.push_back(6355);
        internalCounters.push_back(5577);
        internalCounters.push_back(5829);
        internalCounters.push_back(6081);
        internalCounters.push_back(6333);

        p.DefinePublicCounter("GSVALUInstCount", "GeometryShader", "Average number of vector ALU instructions executed in the GS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5603);
        internalCounters.push_back(5855);
        internalCounters.push_back(6107);
        internalCounters.push_back(6359);
        internalCounters.push_back(5577);
        internalCounters.push_back(5829);
        internalCounters.push_back(6081);
        internalCounters.push_back(6333);

        p.DefinePublicCounter("GSSALUInstCount", "GeometryShader", "Average number of scalar ALU instructions executed in the GS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5654);
        internalCounters.push_back(5906);
        internalCounters.push_back(6158);
        internalCounters.push_back(6410);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("GSVALUBusy", "GeometryShader", "The percentage of GPUTime vector ALU instructions are being processed by the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/,4,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5654);
        internalCounters.push_back(5906);
        internalCounters.push_back(6158);
        internalCounters.push_back(6410);

        p.DefinePublicCounter("GSVALUBusyCycles", "GeometryShader", "Number of GPU cycles where vector ALU instructions are being processed by the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5659);
        internalCounters.push_back(5911);
        internalCounters.push_back(6163);
        internalCounters.push_back(6415);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("GSSALUBusy", "GeometryShader", "The percentage of GPUTime scalar ALU instructions are being processed by the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,4,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(5659);
        internalCounters.push_back(5911);
        internalCounters.push_back(6163);
        internalCounters.push_back(6415);

        p.DefinePublicCounter("GSSALUBusyCycles", "GeometryShader", "Number of GPU cycles where scalar ALU instructions are being processed by the GS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(726);
        internalCounters.push_back(879);
        internalCounters.push_back(1032);
        internalCounters.push_back(1185);
        internalCounters.push_back(730);
        internalCounters.push_back(883);
        internalCounters.push_back(1036);
        internalCounters.push_back(1189);
        internalCounters.push_back(682);
        internalCounters.push_back(835);
        internalCounters.push_back(988);
        internalCounters.push_back(1141);
        internalCounters.push_back(694);
        internalCounters.push_back(847);
        internalCounters.push_back(1000);
        internalCounters.push_back(1153);
        internalCounters.push_back(683);
        internalCounters.push_back(836);
        internalCounters.push_back(989);
        internalCounters.push_back(1142);
        internalCounters.push_back(695);
        internalCounters.push_back(848);
        internalCounters.push_back(1001);
        internalCounters.push_back(1154);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("PrimitiveAssemblyBusy", "Timing", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max,24,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(726);
        internalCounters.push_back(879);
        internalCounters.push_back(1032);
        internalCounters.push_back(1185);
        internalCounters.push_back(730);
        internalCounters.push_back(883);
        internalCounters.push_back(1036);
        internalCounters.push_back(1189);
        internalCounters.push_back(682);
        internalCounters.push_back(835);
        internalCounters.push_back(988);
        internalCounters.push_back(1141);
        internalCounters.push_back(694);
        internalCounters.push_back(847);
        internalCounters.push_back(1000);
        internalCounters.push_back(1153);
        internalCounters.push_back(683);
        internalCounters.push_back(836);
        internalCounters.push_back(989);
        internalCounters.push_back(1142);
        internalCounters.push_back(695);
        internalCounters.push_back(848);
        internalCounters.push_back(1001);
        internalCounters.push_back(1154);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("PrimitiveAssemblyBusyCycles", "Timing", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(629);
        internalCounters.push_back(782);
        internalCounters.push_back(935);
        internalCounters.push_back(1088);

        p.DefinePublicCounter("PrimitivesIn", "PrimitiveAssembly", "The number of primitives received by the hardware. This includes primitives generated by tessellation.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(635);
        internalCounters.push_back(788);
        internalCounters.push_back(941);
        internalCounters.push_back(1094);
        internalCounters.push_back(675);
        internalCounters.push_back(828);
        internalCounters.push_back(981);
        internalCounters.push_back(1134);
        internalCounters.push_back(676);
        internalCounters.push_back(829);
        internalCounters.push_back(982);
        internalCounters.push_back(1135);
        internalCounters.push_back(677);
        internalCounters.push_back(830);
        internalCounters.push_back(983);
        internalCounters.push_back(1136);
        internalCounters.push_back(678);
        internalCounters.push_back(831);
        internalCounters.push_back(984);
        internalCounters.push_back(1137);

        p.DefinePublicCounter("CulledPrims", "PrimitiveAssembly", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,2,+,3,+,4,+,5,+,6,+,7,+,8,+,9,+,10,+,11,+,12,+,13,+,14,+,15,+,16,+,17,+,18,+,19,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(642);
        internalCounters.push_back(795);
        internalCounters.push_back(948);
        internalCounters.push_back(1101);

        p.DefinePublicCounter("ClippedPrims", "PrimitiveAssembly", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(730);
        internalCounters.push_back(883);
        internalCounters.push_back(1036);
        internalCounters.push_back(1189);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("PAStalledOnRasterizer", "PrimitiveAssembly", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(730);
        internalCounters.push_back(883);
        internalCounters.push_back(1036);
        internalCounters.push_back(1189);

        p.DefinePublicCounter("PAStalledOnRasterizerCycles", "PrimitiveAssembly", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11633);
        internalCounters.push_back(11665);
        internalCounters.push_back(11697);
        internalCounters.push_back(11729);
        internalCounters.push_back(11638);
        internalCounters.push_back(11670);
        internalCounters.push_back(11702);
        internalCounters.push_back(11734);
        internalCounters.push_back(11643);
        internalCounters.push_back(11675);
        internalCounters.push_back(11707);
        internalCounters.push_back(11739);
        internalCounters.push_back(11648);
        internalCounters.push_back(11680);
        internalCounters.push_back(11712);
        internalCounters.push_back(11744);

        p.DefinePublicCounter("PSPixelsOut", "PixelShader", "Pixels exported from shader to colour buffers. Does not include killed or alpha tested pixels; if there are multiple rendertargets, each rendertarget receives one export, so this will be 2 for 1 pixel written to two RTs.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,12,13,14,15,sum4,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11635);
        internalCounters.push_back(11667);
        internalCounters.push_back(11699);
        internalCounters.push_back(11731);
        internalCounters.push_back(11640);
        internalCounters.push_back(11672);
        internalCounters.push_back(11704);
        internalCounters.push_back(11736);
        internalCounters.push_back(11645);
        internalCounters.push_back(11677);
        internalCounters.push_back(11709);
        internalCounters.push_back(11741);
        internalCounters.push_back(11650);
        internalCounters.push_back(11682);
        internalCounters.push_back(11714);
        internalCounters.push_back(11746);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("PSExportStalls", "PixelShader", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the colour buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max,16,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11635);
        internalCounters.push_back(11667);
        internalCounters.push_back(11699);
        internalCounters.push_back(11731);
        internalCounters.push_back(11640);
        internalCounters.push_back(11672);
        internalCounters.push_back(11704);
        internalCounters.push_back(11736);
        internalCounters.push_back(11645);
        internalCounters.push_back(11677);
        internalCounters.push_back(11709);
        internalCounters.push_back(11741);
        internalCounters.push_back(11650);
        internalCounters.push_back(11682);
        internalCounters.push_back(11714);
        internalCounters.push_back(11746);

        p.DefinePublicCounter("PSExportStallsCycles", "PixelShader", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the colour buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7615);
        internalCounters.push_back(7867);
        internalCounters.push_back(8119);
        internalCounters.push_back(8371);
        internalCounters.push_back(7593);
        internalCounters.push_back(7845);
        internalCounters.push_back(8097);
        internalCounters.push_back(8349);

        p.DefinePublicCounter("PSVALUInstCount", "PixelShader", "Average number of vector ALU instructions executed in the PS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7619);
        internalCounters.push_back(7871);
        internalCounters.push_back(8123);
        internalCounters.push_back(8375);
        internalCounters.push_back(7593);
        internalCounters.push_back(7845);
        internalCounters.push_back(8097);
        internalCounters.push_back(8349);

        p.DefinePublicCounter("PSSALUInstCount", "PixelShader", "Average number of scalar ALU instructions executed in the PS. Affected by flow control.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7670);
        internalCounters.push_back(7922);
        internalCounters.push_back(8174);
        internalCounters.push_back(8426);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("PSVALUBusy", "PixelShader", "The percentage of GPUTime vector ALU instructions are being processed by the PS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/,4,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7670);
        internalCounters.push_back(7922);
        internalCounters.push_back(8174);
        internalCounters.push_back(8426);

        p.DefinePublicCounter("PSVALUBusyCycles", "PixelShader", "Number of GPU cycles where vector ALU instructions are being processed by the PS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7675);
        internalCounters.push_back(7927);
        internalCounters.push_back(8179);
        internalCounters.push_back(8431);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("PSSALUBusy", "PixelShader", "The percentage of GPUTime scalar ALU instructions are being processed by the PS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,4,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7675);
        internalCounters.push_back(7927);
        internalCounters.push_back(8179);
        internalCounters.push_back(8431);

        p.DefinePublicCounter("PSSALUBusyCycles", "PixelShader", "Number of GPU cycles where scalar ALU instructions are being processed by the PS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSThreadGroups", "ComputeShader", "Total number of thread groups.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2875);
        internalCounters.push_back(3061);
        internalCounters.push_back(3247);
        internalCounters.push_back(3433);

        p.DefinePublicCounter("CSWavefronts", "ComputeShader", "The total number of wavefronts used for the CS.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);
        internalCounters.push_back(3571);
        internalCounters.push_back(3823);
        internalCounters.push_back(4075);
        internalCounters.push_back(4327);

        p.DefinePublicCounter("CSThreads", "ComputeShader", "The number of CS threads processed by the hardware.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),4,5,6,7,sum4,0,1,2,3,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10639);
        internalCounters.push_back(10891);
        internalCounters.push_back(11143);
        internalCounters.push_back(11395);
        internalCounters.push_back(10617);
        internalCounters.push_back(10869);
        internalCounters.push_back(11121);
        internalCounters.push_back(11373);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSVALUInsts", "ComputeShader", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10702);
        internalCounters.push_back(10954);
        internalCounters.push_back(11206);
        internalCounters.push_back(11458);
        internalCounters.push_back(10694);
        internalCounters.push_back(10946);
        internalCounters.push_back(11198);
        internalCounters.push_back(11450);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSVALUUtilization", "ComputeShader", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,(64),*,/,(100),*,8,9,10,11,sum4,ifnotzero,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10643);
        internalCounters.push_back(10895);
        internalCounters.push_back(11147);
        internalCounters.push_back(11399);
        internalCounters.push_back(10617);
        internalCounters.push_back(10869);
        internalCounters.push_back(11121);
        internalCounters.push_back(11373);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSSALUInsts", "ComputeShader", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10641);
        internalCounters.push_back(10893);
        internalCounters.push_back(11145);
        internalCounters.push_back(11397);
        internalCounters.push_back(10617);
        internalCounters.push_back(10869);
        internalCounters.push_back(11121);
        internalCounters.push_back(11373);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSVFetchInsts", "ComputeShader", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10644);
        internalCounters.push_back(10896);
        internalCounters.push_back(11148);
        internalCounters.push_back(11400);
        internalCounters.push_back(10617);
        internalCounters.push_back(10869);
        internalCounters.push_back(11121);
        internalCounters.push_back(11373);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSSFetchInsts", "ComputeShader", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10640);
        internalCounters.push_back(10892);
        internalCounters.push_back(11144);
        internalCounters.push_back(11396);
        internalCounters.push_back(10617);
        internalCounters.push_back(10869);
        internalCounters.push_back(11121);
        internalCounters.push_back(11373);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSVWriteInsts", "ComputeShader", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10645);
        internalCounters.push_back(10897);
        internalCounters.push_back(11149);
        internalCounters.push_back(11401);
        internalCounters.push_back(10646);
        internalCounters.push_back(10898);
        internalCounters.push_back(11150);
        internalCounters.push_back(11402);
        internalCounters.push_back(10617);
        internalCounters.push_back(10869);
        internalCounters.push_back(11121);
        internalCounters.push_back(11373);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSFlatVMemInsts", "ComputeShader", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,-,8,9,10,11,sum4,/,12,13,14,15,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10694);
        internalCounters.push_back(10946);
        internalCounters.push_back(11198);
        internalCounters.push_back(11450);
        internalCounters.push_back(36073);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSVALUBusy", "ComputeShader", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,(4),*,NUM_SIMDS,/,4,/,(100),*,5,6,7,8,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10694);
        internalCounters.push_back(10946);
        internalCounters.push_back(11198);
        internalCounters.push_back(11450);
        internalCounters.push_back(36073);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSVALUBusyCycles", "ComputeShader", "Number of GPU cycles where vector ALU instructions are processed.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10699);
        internalCounters.push_back(10951);
        internalCounters.push_back(11203);
        internalCounters.push_back(11455);
        internalCounters.push_back(36073);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSSALUBusy", "ComputeShader", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,4,/,(100),*,5,6,7,8,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10699);
        internalCounters.push_back(10951);
        internalCounters.push_back(11203);
        internalCounters.push_back(11455);
        internalCounters.push_back(36073);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSSALUBusyCycles", "ComputeShader", "Number of GPU cycles where scalar ALU instructions are processed.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11749);
        internalCounters.push_back(11860);
        internalCounters.push_back(11971);
        internalCounters.push_back(12082);
        internalCounters.push_back(12193);
        internalCounters.push_back(12304);
        internalCounters.push_back(12415);
        internalCounters.push_back(12526);
        internalCounters.push_back(12637);
        internalCounters.push_back(12748);
        internalCounters.push_back(12859);
        internalCounters.push_back(12970);
        internalCounters.push_back(13081);
        internalCounters.push_back(13192);
        internalCounters.push_back(13303);
        internalCounters.push_back(13414);
        internalCounters.push_back(13525);
        internalCounters.push_back(13636);
        internalCounters.push_back(13747);
        internalCounters.push_back(13858);
        internalCounters.push_back(13969);
        internalCounters.push_back(14080);
        internalCounters.push_back(14191);
        internalCounters.push_back(14302);
        internalCounters.push_back(14413);
        internalCounters.push_back(14524);
        internalCounters.push_back(14635);
        internalCounters.push_back(14746);
        internalCounters.push_back(14857);
        internalCounters.push_back(14968);
        internalCounters.push_back(15079);
        internalCounters.push_back(15190);
        internalCounters.push_back(15301);
        internalCounters.push_back(15412);
        internalCounters.push_back(15523);
        internalCounters.push_back(15634);
        internalCounters.push_back(15745);
        internalCounters.push_back(15856);
        internalCounters.push_back(15967);
        internalCounters.push_back(16078);
        internalCounters.push_back(16189);
        internalCounters.push_back(16300);
        internalCounters.push_back(16411);
        internalCounters.push_back(16522);
        internalCounters.push_back(36073);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSMemUnitBusy", "ComputeShader", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,max44,44,/,(100),*,45,46,47,48,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11749);
        internalCounters.push_back(11860);
        internalCounters.push_back(11971);
        internalCounters.push_back(12082);
        internalCounters.push_back(12193);
        internalCounters.push_back(12304);
        internalCounters.push_back(12415);
        internalCounters.push_back(12526);
        internalCounters.push_back(12637);
        internalCounters.push_back(12748);
        internalCounters.push_back(12859);
        internalCounters.push_back(12970);
        internalCounters.push_back(13081);
        internalCounters.push_back(13192);
        internalCounters.push_back(13303);
        internalCounters.push_back(13414);
        internalCounters.push_back(13525);
        internalCounters.push_back(13636);
        internalCounters.push_back(13747);
        internalCounters.push_back(13858);
        internalCounters.push_back(13969);
        internalCounters.push_back(14080);
        internalCounters.push_back(14191);
        internalCounters.push_back(14302);
        internalCounters.push_back(14413);
        internalCounters.push_back(14524);
        internalCounters.push_back(14635);
        internalCounters.push_back(14746);
        internalCounters.push_back(14857);
        internalCounters.push_back(14968);
        internalCounters.push_back(15079);
        internalCounters.push_back(15190);
        internalCounters.push_back(15301);
        internalCounters.push_back(15412);
        internalCounters.push_back(15523);
        internalCounters.push_back(15634);
        internalCounters.push_back(15745);
        internalCounters.push_back(15856);
        internalCounters.push_back(15967);
        internalCounters.push_back(16078);
        internalCounters.push_back(16189);
        internalCounters.push_back(16300);
        internalCounters.push_back(16411);
        internalCounters.push_back(16522);

        p.DefinePublicCounter("CSMemUnitBusyCycles", "ComputeShader", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,max44");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(18792);
        internalCounters.push_back(18946);
        internalCounters.push_back(19100);
        internalCounters.push_back(19254);
        internalCounters.push_back(19408);
        internalCounters.push_back(19562);
        internalCounters.push_back(19716);
        internalCounters.push_back(19870);
        internalCounters.push_back(20024);
        internalCounters.push_back(20178);
        internalCounters.push_back(20332);
        internalCounters.push_back(20486);
        internalCounters.push_back(20640);
        internalCounters.push_back(20794);
        internalCounters.push_back(20948);
        internalCounters.push_back(21102);
        internalCounters.push_back(21256);
        internalCounters.push_back(21410);
        internalCounters.push_back(21564);
        internalCounters.push_back(21718);
        internalCounters.push_back(21872);
        internalCounters.push_back(22026);
        internalCounters.push_back(22180);
        internalCounters.push_back(22334);
        internalCounters.push_back(22488);
        internalCounters.push_back(22642);
        internalCounters.push_back(22796);
        internalCounters.push_back(22950);
        internalCounters.push_back(23104);
        internalCounters.push_back(23258);
        internalCounters.push_back(23412);
        internalCounters.push_back(23566);
        internalCounters.push_back(23720);
        internalCounters.push_back(23874);
        internalCounters.push_back(24028);
        internalCounters.push_back(24182);
        internalCounters.push_back(24336);
        internalCounters.push_back(24490);
        internalCounters.push_back(24644);
        internalCounters.push_back(24798);
        internalCounters.push_back(24952);
        internalCounters.push_back(25106);
        internalCounters.push_back(25260);
        internalCounters.push_back(25414);
        internalCounters.push_back(36073);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSMemUnitStalled", "ComputeShader", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,max44,44,/,(100),*,45,46,47,48,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(18792);
        internalCounters.push_back(18946);
        internalCounters.push_back(19100);
        internalCounters.push_back(19254);
        internalCounters.push_back(19408);
        internalCounters.push_back(19562);
        internalCounters.push_back(19716);
        internalCounters.push_back(19870);
        internalCounters.push_back(20024);
        internalCounters.push_back(20178);
        internalCounters.push_back(20332);
        internalCounters.push_back(20486);
        internalCounters.push_back(20640);
        internalCounters.push_back(20794);
        internalCounters.push_back(20948);
        internalCounters.push_back(21102);
        internalCounters.push_back(21256);
        internalCounters.push_back(21410);
        internalCounters.push_back(21564);
        internalCounters.push_back(21718);
        internalCounters.push_back(21872);
        internalCounters.push_back(22026);
        internalCounters.push_back(22180);
        internalCounters.push_back(22334);
        internalCounters.push_back(22488);
        internalCounters.push_back(22642);
        internalCounters.push_back(22796);
        internalCounters.push_back(22950);
        internalCounters.push_back(23104);
        internalCounters.push_back(23258);
        internalCounters.push_back(23412);
        internalCounters.push_back(23566);
        internalCounters.push_back(23720);
        internalCounters.push_back(23874);
        internalCounters.push_back(24028);
        internalCounters.push_back(24182);
        internalCounters.push_back(24336);
        internalCounters.push_back(24490);
        internalCounters.push_back(24644);
        internalCounters.push_back(24798);
        internalCounters.push_back(24952);
        internalCounters.push_back(25106);
        internalCounters.push_back(25260);
        internalCounters.push_back(25414);

        p.DefinePublicCounter("CSMemUnitStalledCycles", "ComputeShader", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,max44");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(25589);
        internalCounters.push_back(25749);
        internalCounters.push_back(25909);
        internalCounters.push_back(26069);
        internalCounters.push_back(26229);
        internalCounters.push_back(26389);
        internalCounters.push_back(26549);
        internalCounters.push_back(26709);
        internalCounters.push_back(26869);
        internalCounters.push_back(27029);
        internalCounters.push_back(27189);
        internalCounters.push_back(27349);
        internalCounters.push_back(27509);
        internalCounters.push_back(27669);
        internalCounters.push_back(27829);
        internalCounters.push_back(27989);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSFetchSize", "ComputeShader", "The total kilobytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,(1024),/,16,17,18,19,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(25583);
        internalCounters.push_back(25743);
        internalCounters.push_back(25903);
        internalCounters.push_back(26063);
        internalCounters.push_back(26223);
        internalCounters.push_back(26383);
        internalCounters.push_back(26543);
        internalCounters.push_back(26703);
        internalCounters.push_back(26863);
        internalCounters.push_back(27023);
        internalCounters.push_back(27183);
        internalCounters.push_back(27343);
        internalCounters.push_back(27503);
        internalCounters.push_back(27663);
        internalCounters.push_back(27823);
        internalCounters.push_back(27983);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSWriteSize", "ComputeShader", "The total kilobytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,(1024),/,16,17,18,19,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(25575);
        internalCounters.push_back(25735);
        internalCounters.push_back(25895);
        internalCounters.push_back(26055);
        internalCounters.push_back(26215);
        internalCounters.push_back(26375);
        internalCounters.push_back(26535);
        internalCounters.push_back(26695);
        internalCounters.push_back(26855);
        internalCounters.push_back(27015);
        internalCounters.push_back(27175);
        internalCounters.push_back(27335);
        internalCounters.push_back(27495);
        internalCounters.push_back(27655);
        internalCounters.push_back(27815);
        internalCounters.push_back(27975);
        internalCounters.push_back(25576);
        internalCounters.push_back(25736);
        internalCounters.push_back(25896);
        internalCounters.push_back(26056);
        internalCounters.push_back(26216);
        internalCounters.push_back(26376);
        internalCounters.push_back(26536);
        internalCounters.push_back(26696);
        internalCounters.push_back(26856);
        internalCounters.push_back(27016);
        internalCounters.push_back(27176);
        internalCounters.push_back(27336);
        internalCounters.push_back(27496);
        internalCounters.push_back(27656);
        internalCounters.push_back(27816);
        internalCounters.push_back(27976);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSCacheHit", "ComputeShader", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*,32,33,34,35,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(25575);
        internalCounters.push_back(25735);
        internalCounters.push_back(25895);
        internalCounters.push_back(26055);
        internalCounters.push_back(26215);
        internalCounters.push_back(26375);
        internalCounters.push_back(26535);
        internalCounters.push_back(26695);
        internalCounters.push_back(26855);
        internalCounters.push_back(27015);
        internalCounters.push_back(27175);
        internalCounters.push_back(27335);
        internalCounters.push_back(27495);
        internalCounters.push_back(27655);
        internalCounters.push_back(27815);
        internalCounters.push_back(27975);

        p.DefinePublicCounter("CSCacheHitCount", "ComputeShader", "Count of fetch, write, atomic, and other instructions that hit the data cache.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(25576);
        internalCounters.push_back(25736);
        internalCounters.push_back(25896);
        internalCounters.push_back(26056);
        internalCounters.push_back(26216);
        internalCounters.push_back(26376);
        internalCounters.push_back(26536);
        internalCounters.push_back(26696);
        internalCounters.push_back(26856);
        internalCounters.push_back(27016);
        internalCounters.push_back(27176);
        internalCounters.push_back(27336);
        internalCounters.push_back(27496);
        internalCounters.push_back(27656);
        internalCounters.push_back(27816);
        internalCounters.push_back(27976);

        p.DefinePublicCounter("CSCacheMissCount", "ComputeShader", "Count of fetch, write, atomic, and other instructions that miss the data cache.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(25584);
        internalCounters.push_back(25744);
        internalCounters.push_back(25904);
        internalCounters.push_back(26064);
        internalCounters.push_back(26224);
        internalCounters.push_back(26384);
        internalCounters.push_back(26544);
        internalCounters.push_back(26704);
        internalCounters.push_back(26864);
        internalCounters.push_back(27024);
        internalCounters.push_back(27184);
        internalCounters.push_back(27344);
        internalCounters.push_back(27504);
        internalCounters.push_back(27664);
        internalCounters.push_back(27824);
        internalCounters.push_back(27984);
        internalCounters.push_back(36073);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSWriteUnitStalled", "ComputeShader", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,18,19,20,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(25584);
        internalCounters.push_back(25744);
        internalCounters.push_back(25904);
        internalCounters.push_back(26064);
        internalCounters.push_back(26224);
        internalCounters.push_back(26384);
        internalCounters.push_back(26544);
        internalCounters.push_back(26704);
        internalCounters.push_back(26864);
        internalCounters.push_back(27024);
        internalCounters.push_back(27184);
        internalCounters.push_back(27344);
        internalCounters.push_back(27504);
        internalCounters.push_back(27664);
        internalCounters.push_back(27824);
        internalCounters.push_back(27984);

        p.DefinePublicCounter("CSWriteUnitStalledCycles", "ComputeShader", "Number of GPU cycles the write unit is stalled.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10648);
        internalCounters.push_back(10900);
        internalCounters.push_back(11152);
        internalCounters.push_back(11404);
        internalCounters.push_back(10617);
        internalCounters.push_back(10869);
        internalCounters.push_back(11121);
        internalCounters.push_back(11373);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSGDSInsts", "ComputeShader", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10647);
        internalCounters.push_back(10899);
        internalCounters.push_back(11151);
        internalCounters.push_back(11403);
        internalCounters.push_back(10645);
        internalCounters.push_back(10897);
        internalCounters.push_back(11149);
        internalCounters.push_back(11401);
        internalCounters.push_back(10617);
        internalCounters.push_back(10869);
        internalCounters.push_back(11121);
        internalCounters.push_back(11373);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSLDSInsts", "ComputeShader", "The average number of LDS read/write instructions executed per work-item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,-,8,9,10,11,sum4,/,12,13,14,15,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10646);
        internalCounters.push_back(10898);
        internalCounters.push_back(11150);
        internalCounters.push_back(11402);
        internalCounters.push_back(10617);
        internalCounters.push_back(10869);
        internalCounters.push_back(11121);
        internalCounters.push_back(11373);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSFlatLDSInsts", "ComputeShader", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10674);
        internalCounters.push_back(10926);
        internalCounters.push_back(11178);
        internalCounters.push_back(11430);
        internalCounters.push_back(10617);
        internalCounters.push_back(10869);
        internalCounters.push_back(11121);
        internalCounters.push_back(11373);
        internalCounters.push_back(36073);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSALUStalledByLDS", "ComputeShader", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,/,NUM_SHADER_ENGINES,/,(100),*,8,9,10,11,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10674);
        internalCounters.push_back(10926);
        internalCounters.push_back(11178);
        internalCounters.push_back(11430);

        p.DefinePublicCounter("CSALUStalledByLDSCycles", "ComputeShader", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,NUM_SHADER_ENGINES,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10710);
        internalCounters.push_back(10962);
        internalCounters.push_back(11214);
        internalCounters.push_back(11466);
        internalCounters.push_back(36073);
        internalCounters.push_back(2872);
        internalCounters.push_back(3058);
        internalCounters.push_back(3244);
        internalCounters.push_back(3430);

        p.DefinePublicCounter("CSLDSBankConflict", "ComputeShader", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,/,NUM_SIMDS,/,(100),*,5,6,7,8,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10710);
        internalCounters.push_back(10962);
        internalCounters.push_back(11214);
        internalCounters.push_back(11466);

        p.DefinePublicCounter("CSLDSBankConflictCycles", "ComputeShader", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,NUM_SIMDS,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11749);
        internalCounters.push_back(11860);
        internalCounters.push_back(11971);
        internalCounters.push_back(12082);
        internalCounters.push_back(12193);
        internalCounters.push_back(12304);
        internalCounters.push_back(12415);
        internalCounters.push_back(12526);
        internalCounters.push_back(12637);
        internalCounters.push_back(12748);
        internalCounters.push_back(12859);
        internalCounters.push_back(12970);
        internalCounters.push_back(13081);
        internalCounters.push_back(13192);
        internalCounters.push_back(13303);
        internalCounters.push_back(13414);
        internalCounters.push_back(13525);
        internalCounters.push_back(13636);
        internalCounters.push_back(13747);
        internalCounters.push_back(13858);
        internalCounters.push_back(13969);
        internalCounters.push_back(14080);
        internalCounters.push_back(14191);
        internalCounters.push_back(14302);
        internalCounters.push_back(14413);
        internalCounters.push_back(14524);
        internalCounters.push_back(14635);
        internalCounters.push_back(14746);
        internalCounters.push_back(14857);
        internalCounters.push_back(14968);
        internalCounters.push_back(15079);
        internalCounters.push_back(15190);
        internalCounters.push_back(15301);
        internalCounters.push_back(15412);
        internalCounters.push_back(15523);
        internalCounters.push_back(15634);
        internalCounters.push_back(15745);
        internalCounters.push_back(15856);
        internalCounters.push_back(15967);
        internalCounters.push_back(16078);
        internalCounters.push_back(16189);
        internalCounters.push_back(16300);
        internalCounters.push_back(16411);
        internalCounters.push_back(16522);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("TexUnitBusy", "Timing", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,max44,44,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11749);
        internalCounters.push_back(11860);
        internalCounters.push_back(11971);
        internalCounters.push_back(12082);
        internalCounters.push_back(12193);
        internalCounters.push_back(12304);
        internalCounters.push_back(12415);
        internalCounters.push_back(12526);
        internalCounters.push_back(12637);
        internalCounters.push_back(12748);
        internalCounters.push_back(12859);
        internalCounters.push_back(12970);
        internalCounters.push_back(13081);
        internalCounters.push_back(13192);
        internalCounters.push_back(13303);
        internalCounters.push_back(13414);
        internalCounters.push_back(13525);
        internalCounters.push_back(13636);
        internalCounters.push_back(13747);
        internalCounters.push_back(13858);
        internalCounters.push_back(13969);
        internalCounters.push_back(14080);
        internalCounters.push_back(14191);
        internalCounters.push_back(14302);
        internalCounters.push_back(14413);
        internalCounters.push_back(14524);
        internalCounters.push_back(14635);
        internalCounters.push_back(14746);
        internalCounters.push_back(14857);
        internalCounters.push_back(14968);
        internalCounters.push_back(15079);
        internalCounters.push_back(15190);
        internalCounters.push_back(15301);
        internalCounters.push_back(15412);
        internalCounters.push_back(15523);
        internalCounters.push_back(15634);
        internalCounters.push_back(15745);
        internalCounters.push_back(15856);
        internalCounters.push_back(15967);
        internalCounters.push_back(16078);
        internalCounters.push_back(16189);
        internalCounters.push_back(16300);
        internalCounters.push_back(16411);
        internalCounters.push_back(16522);

        p.DefinePublicCounter("TexUnitBusyCycles", "Timing", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,max44");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11818);
        internalCounters.push_back(11929);
        internalCounters.push_back(12040);
        internalCounters.push_back(12151);
        internalCounters.push_back(12262);
        internalCounters.push_back(12373);
        internalCounters.push_back(12484);
        internalCounters.push_back(12595);
        internalCounters.push_back(12706);
        internalCounters.push_back(12817);
        internalCounters.push_back(12928);
        internalCounters.push_back(13039);
        internalCounters.push_back(13150);
        internalCounters.push_back(13261);
        internalCounters.push_back(13372);
        internalCounters.push_back(13483);
        internalCounters.push_back(13594);
        internalCounters.push_back(13705);
        internalCounters.push_back(13816);
        internalCounters.push_back(13927);
        internalCounters.push_back(14038);
        internalCounters.push_back(14149);
        internalCounters.push_back(14260);
        internalCounters.push_back(14371);
        internalCounters.push_back(14482);
        internalCounters.push_back(14593);
        internalCounters.push_back(14704);
        internalCounters.push_back(14815);
        internalCounters.push_back(14926);
        internalCounters.push_back(15037);
        internalCounters.push_back(15148);
        internalCounters.push_back(15259);
        internalCounters.push_back(15370);
        internalCounters.push_back(15481);
        internalCounters.push_back(15592);
        internalCounters.push_back(15703);
        internalCounters.push_back(15814);
        internalCounters.push_back(15925);
        internalCounters.push_back(16036);
        internalCounters.push_back(16147);
        internalCounters.push_back(16258);
        internalCounters.push_back(16369);
        internalCounters.push_back(16480);
        internalCounters.push_back(16591);
        internalCounters.push_back(11817);
        internalCounters.push_back(11928);
        internalCounters.push_back(12039);
        internalCounters.push_back(12150);
        internalCounters.push_back(12261);
        internalCounters.push_back(12372);
        internalCounters.push_back(12483);
        internalCounters.push_back(12594);
        internalCounters.push_back(12705);
        internalCounters.push_back(12816);
        internalCounters.push_back(12927);
        internalCounters.push_back(13038);
        internalCounters.push_back(13149);
        internalCounters.push_back(13260);
        internalCounters.push_back(13371);
        internalCounters.push_back(13482);
        internalCounters.push_back(13593);
        internalCounters.push_back(13704);
        internalCounters.push_back(13815);
        internalCounters.push_back(13926);
        internalCounters.push_back(14037);
        internalCounters.push_back(14148);
        internalCounters.push_back(14259);
        internalCounters.push_back(14370);
        internalCounters.push_back(14481);
        internalCounters.push_back(14592);
        internalCounters.push_back(14703);
        internalCounters.push_back(14814);
        internalCounters.push_back(14925);
        internalCounters.push_back(15036);
        internalCounters.push_back(15147);
        internalCounters.push_back(15258);
        internalCounters.push_back(15369);
        internalCounters.push_back(15480);
        internalCounters.push_back(15591);
        internalCounters.push_back(15702);
        internalCounters.push_back(15813);
        internalCounters.push_back(15924);
        internalCounters.push_back(16035);
        internalCounters.push_back(16146);
        internalCounters.push_back(16257);
        internalCounters.push_back(16368);
        internalCounters.push_back(16479);
        internalCounters.push_back(16590);

        p.DefinePublicCounter("TexTriFilteringPct", "TextureUnit", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,sum44,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,sum44,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,sum44,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11818);
        internalCounters.push_back(11929);
        internalCounters.push_back(12040);
        internalCounters.push_back(12151);
        internalCounters.push_back(12262);
        internalCounters.push_back(12373);
        internalCounters.push_back(12484);
        internalCounters.push_back(12595);
        internalCounters.push_back(12706);
        internalCounters.push_back(12817);
        internalCounters.push_back(12928);
        internalCounters.push_back(13039);
        internalCounters.push_back(13150);
        internalCounters.push_back(13261);
        internalCounters.push_back(13372);
        internalCounters.push_back(13483);
        internalCounters.push_back(13594);
        internalCounters.push_back(13705);
        internalCounters.push_back(13816);
        internalCounters.push_back(13927);
        internalCounters.push_back(14038);
        internalCounters.push_back(14149);
        internalCounters.push_back(14260);
        internalCounters.push_back(14371);
        internalCounters.push_back(14482);
        internalCounters.push_back(14593);
        internalCounters.push_back(14704);
        internalCounters.push_back(14815);
        internalCounters.push_back(14926);
        internalCounters.push_back(15037);
        internalCounters.push_back(15148);
        internalCounters.push_back(15259);
        internalCounters.push_back(15370);
        internalCounters.push_back(15481);
        internalCounters.push_back(15592);
        internalCounters.push_back(15703);
        internalCounters.push_back(15814);
        internalCounters.push_back(15925);
        internalCounters.push_back(16036);
        internalCounters.push_back(16147);
        internalCounters.push_back(16258);
        internalCounters.push_back(16369);
        internalCounters.push_back(16480);
        internalCounters.push_back(16591);

        p.DefinePublicCounter("TexTriFilteringCount", "TextureUnit", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,sum44");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11817);
        internalCounters.push_back(11928);
        internalCounters.push_back(12039);
        internalCounters.push_back(12150);
        internalCounters.push_back(12261);
        internalCounters.push_back(12372);
        internalCounters.push_back(12483);
        internalCounters.push_back(12594);
        internalCounters.push_back(12705);
        internalCounters.push_back(12816);
        internalCounters.push_back(12927);
        internalCounters.push_back(13038);
        internalCounters.push_back(13149);
        internalCounters.push_back(13260);
        internalCounters.push_back(13371);
        internalCounters.push_back(13482);
        internalCounters.push_back(13593);
        internalCounters.push_back(13704);
        internalCounters.push_back(13815);
        internalCounters.push_back(13926);
        internalCounters.push_back(14037);
        internalCounters.push_back(14148);
        internalCounters.push_back(14259);
        internalCounters.push_back(14370);
        internalCounters.push_back(14481);
        internalCounters.push_back(14592);
        internalCounters.push_back(14703);
        internalCounters.push_back(14814);
        internalCounters.push_back(14925);
        internalCounters.push_back(15036);
        internalCounters.push_back(15147);
        internalCounters.push_back(15258);
        internalCounters.push_back(15369);
        internalCounters.push_back(15480);
        internalCounters.push_back(15591);
        internalCounters.push_back(15702);
        internalCounters.push_back(15813);
        internalCounters.push_back(15924);
        internalCounters.push_back(16035);
        internalCounters.push_back(16146);
        internalCounters.push_back(16257);
        internalCounters.push_back(16368);
        internalCounters.push_back(16479);
        internalCounters.push_back(16590);

        p.DefinePublicCounter("NoTexTriFilteringCount", "TextureUnit", "Count of pixels that did not receive trilinear filtering.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,sum44");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11820);
        internalCounters.push_back(11931);
        internalCounters.push_back(12042);
        internalCounters.push_back(12153);
        internalCounters.push_back(12264);
        internalCounters.push_back(12375);
        internalCounters.push_back(12486);
        internalCounters.push_back(12597);
        internalCounters.push_back(12708);
        internalCounters.push_back(12819);
        internalCounters.push_back(12930);
        internalCounters.push_back(13041);
        internalCounters.push_back(13152);
        internalCounters.push_back(13263);
        internalCounters.push_back(13374);
        internalCounters.push_back(13485);
        internalCounters.push_back(13596);
        internalCounters.push_back(13707);
        internalCounters.push_back(13818);
        internalCounters.push_back(13929);
        internalCounters.push_back(14040);
        internalCounters.push_back(14151);
        internalCounters.push_back(14262);
        internalCounters.push_back(14373);
        internalCounters.push_back(14484);
        internalCounters.push_back(14595);
        internalCounters.push_back(14706);
        internalCounters.push_back(14817);
        internalCounters.push_back(14928);
        internalCounters.push_back(15039);
        internalCounters.push_back(15150);
        internalCounters.push_back(15261);
        internalCounters.push_back(15372);
        internalCounters.push_back(15483);
        internalCounters.push_back(15594);
        internalCounters.push_back(15705);
        internalCounters.push_back(15816);
        internalCounters.push_back(15927);
        internalCounters.push_back(16038);
        internalCounters.push_back(16149);
        internalCounters.push_back(16260);
        internalCounters.push_back(16371);
        internalCounters.push_back(16482);
        internalCounters.push_back(16593);
        internalCounters.push_back(11819);
        internalCounters.push_back(11930);
        internalCounters.push_back(12041);
        internalCounters.push_back(12152);
        internalCounters.push_back(12263);
        internalCounters.push_back(12374);
        internalCounters.push_back(12485);
        internalCounters.push_back(12596);
        internalCounters.push_back(12707);
        internalCounters.push_back(12818);
        internalCounters.push_back(12929);
        internalCounters.push_back(13040);
        internalCounters.push_back(13151);
        internalCounters.push_back(13262);
        internalCounters.push_back(13373);
        internalCounters.push_back(13484);
        internalCounters.push_back(13595);
        internalCounters.push_back(13706);
        internalCounters.push_back(13817);
        internalCounters.push_back(13928);
        internalCounters.push_back(14039);
        internalCounters.push_back(14150);
        internalCounters.push_back(14261);
        internalCounters.push_back(14372);
        internalCounters.push_back(14483);
        internalCounters.push_back(14594);
        internalCounters.push_back(14705);
        internalCounters.push_back(14816);
        internalCounters.push_back(14927);
        internalCounters.push_back(15038);
        internalCounters.push_back(15149);
        internalCounters.push_back(15260);
        internalCounters.push_back(15371);
        internalCounters.push_back(15482);
        internalCounters.push_back(15593);
        internalCounters.push_back(15704);
        internalCounters.push_back(15815);
        internalCounters.push_back(15926);
        internalCounters.push_back(16037);
        internalCounters.push_back(16148);
        internalCounters.push_back(16259);
        internalCounters.push_back(16370);
        internalCounters.push_back(16481);
        internalCounters.push_back(16592);

        p.DefinePublicCounter("TexVolFilteringPct", "TextureUnit", "Percentage of pixels that received volume filtering.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,sum44,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,sum44,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,sum44,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11820);
        internalCounters.push_back(11931);
        internalCounters.push_back(12042);
        internalCounters.push_back(12153);
        internalCounters.push_back(12264);
        internalCounters.push_back(12375);
        internalCounters.push_back(12486);
        internalCounters.push_back(12597);
        internalCounters.push_back(12708);
        internalCounters.push_back(12819);
        internalCounters.push_back(12930);
        internalCounters.push_back(13041);
        internalCounters.push_back(13152);
        internalCounters.push_back(13263);
        internalCounters.push_back(13374);
        internalCounters.push_back(13485);
        internalCounters.push_back(13596);
        internalCounters.push_back(13707);
        internalCounters.push_back(13818);
        internalCounters.push_back(13929);
        internalCounters.push_back(14040);
        internalCounters.push_back(14151);
        internalCounters.push_back(14262);
        internalCounters.push_back(14373);
        internalCounters.push_back(14484);
        internalCounters.push_back(14595);
        internalCounters.push_back(14706);
        internalCounters.push_back(14817);
        internalCounters.push_back(14928);
        internalCounters.push_back(15039);
        internalCounters.push_back(15150);
        internalCounters.push_back(15261);
        internalCounters.push_back(15372);
        internalCounters.push_back(15483);
        internalCounters.push_back(15594);
        internalCounters.push_back(15705);
        internalCounters.push_back(15816);
        internalCounters.push_back(15927);
        internalCounters.push_back(16038);
        internalCounters.push_back(16149);
        internalCounters.push_back(16260);
        internalCounters.push_back(16371);
        internalCounters.push_back(16482);
        internalCounters.push_back(16593);

        p.DefinePublicCounter("TexVolFilteringCount", "TextureUnit", "Count of pixels that received volume filtering.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,sum44");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11819);
        internalCounters.push_back(11930);
        internalCounters.push_back(12041);
        internalCounters.push_back(12152);
        internalCounters.push_back(12263);
        internalCounters.push_back(12374);
        internalCounters.push_back(12485);
        internalCounters.push_back(12596);
        internalCounters.push_back(12707);
        internalCounters.push_back(12818);
        internalCounters.push_back(12929);
        internalCounters.push_back(13040);
        internalCounters.push_back(13151);
        internalCounters.push_back(13262);
        internalCounters.push_back(13373);
        internalCounters.push_back(13484);
        internalCounters.push_back(13595);
        internalCounters.push_back(13706);
        internalCounters.push_back(13817);
        internalCounters.push_back(13928);
        internalCounters.push_back(14039);
        internalCounters.push_back(14150);
        internalCounters.push_back(14261);
        internalCounters.push_back(14372);
        internalCounters.push_back(14483);
        internalCounters.push_back(14594);
        internalCounters.push_back(14705);
        internalCounters.push_back(14816);
        internalCounters.push_back(14927);
        internalCounters.push_back(15038);
        internalCounters.push_back(15149);
        internalCounters.push_back(15260);
        internalCounters.push_back(15371);
        internalCounters.push_back(15482);
        internalCounters.push_back(15593);
        internalCounters.push_back(15704);
        internalCounters.push_back(15815);
        internalCounters.push_back(15926);
        internalCounters.push_back(16037);
        internalCounters.push_back(16148);
        internalCounters.push_back(16259);
        internalCounters.push_back(16370);
        internalCounters.push_back(16481);
        internalCounters.push_back(16592);

        p.DefinePublicCounter("NoTexVolFilteringCount", "TextureUnit", "Count of pixels that did not receive volume filtering.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,sum44");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11838);
        internalCounters.push_back(11949);
        internalCounters.push_back(12060);
        internalCounters.push_back(12171);
        internalCounters.push_back(12282);
        internalCounters.push_back(12393);
        internalCounters.push_back(12504);
        internalCounters.push_back(12615);
        internalCounters.push_back(12726);
        internalCounters.push_back(12837);
        internalCounters.push_back(12948);
        internalCounters.push_back(13059);
        internalCounters.push_back(13170);
        internalCounters.push_back(13281);
        internalCounters.push_back(13392);
        internalCounters.push_back(13503);
        internalCounters.push_back(13614);
        internalCounters.push_back(13725);
        internalCounters.push_back(13836);
        internalCounters.push_back(13947);
        internalCounters.push_back(14058);
        internalCounters.push_back(14169);
        internalCounters.push_back(14280);
        internalCounters.push_back(14391);
        internalCounters.push_back(14502);
        internalCounters.push_back(14613);
        internalCounters.push_back(14724);
        internalCounters.push_back(14835);
        internalCounters.push_back(14946);
        internalCounters.push_back(15057);
        internalCounters.push_back(15168);
        internalCounters.push_back(15279);
        internalCounters.push_back(15390);
        internalCounters.push_back(15501);
        internalCounters.push_back(15612);
        internalCounters.push_back(15723);
        internalCounters.push_back(15834);
        internalCounters.push_back(15945);
        internalCounters.push_back(16056);
        internalCounters.push_back(16167);
        internalCounters.push_back(16278);
        internalCounters.push_back(16389);
        internalCounters.push_back(16500);
        internalCounters.push_back(16611);
        internalCounters.push_back(11839);
        internalCounters.push_back(11950);
        internalCounters.push_back(12061);
        internalCounters.push_back(12172);
        internalCounters.push_back(12283);
        internalCounters.push_back(12394);
        internalCounters.push_back(12505);
        internalCounters.push_back(12616);
        internalCounters.push_back(12727);
        internalCounters.push_back(12838);
        internalCounters.push_back(12949);
        internalCounters.push_back(13060);
        internalCounters.push_back(13171);
        internalCounters.push_back(13282);
        internalCounters.push_back(13393);
        internalCounters.push_back(13504);
        internalCounters.push_back(13615);
        internalCounters.push_back(13726);
        internalCounters.push_back(13837);
        internalCounters.push_back(13948);
        internalCounters.push_back(14059);
        internalCounters.push_back(14170);
        internalCounters.push_back(14281);
        internalCounters.push_back(14392);
        internalCounters.push_back(14503);
        internalCounters.push_back(14614);
        internalCounters.push_back(14725);
        internalCounters.push_back(14836);
        internalCounters.push_back(14947);
        internalCounters.push_back(15058);
        internalCounters.push_back(15169);
        internalCounters.push_back(15280);
        internalCounters.push_back(15391);
        internalCounters.push_back(15502);
        internalCounters.push_back(15613);
        internalCounters.push_back(15724);
        internalCounters.push_back(15835);
        internalCounters.push_back(15946);
        internalCounters.push_back(16057);
        internalCounters.push_back(16168);
        internalCounters.push_back(16279);
        internalCounters.push_back(16390);
        internalCounters.push_back(16501);
        internalCounters.push_back(16612);
        internalCounters.push_back(11840);
        internalCounters.push_back(11951);
        internalCounters.push_back(12062);
        internalCounters.push_back(12173);
        internalCounters.push_back(12284);
        internalCounters.push_back(12395);
        internalCounters.push_back(12506);
        internalCounters.push_back(12617);
        internalCounters.push_back(12728);
        internalCounters.push_back(12839);
        internalCounters.push_back(12950);
        internalCounters.push_back(13061);
        internalCounters.push_back(13172);
        internalCounters.push_back(13283);
        internalCounters.push_back(13394);
        internalCounters.push_back(13505);
        internalCounters.push_back(13616);
        internalCounters.push_back(13727);
        internalCounters.push_back(13838);
        internalCounters.push_back(13949);
        internalCounters.push_back(14060);
        internalCounters.push_back(14171);
        internalCounters.push_back(14282);
        internalCounters.push_back(14393);
        internalCounters.push_back(14504);
        internalCounters.push_back(14615);
        internalCounters.push_back(14726);
        internalCounters.push_back(14837);
        internalCounters.push_back(14948);
        internalCounters.push_back(15059);
        internalCounters.push_back(15170);
        internalCounters.push_back(15281);
        internalCounters.push_back(15392);
        internalCounters.push_back(15503);
        internalCounters.push_back(15614);
        internalCounters.push_back(15725);
        internalCounters.push_back(15836);
        internalCounters.push_back(15947);
        internalCounters.push_back(16058);
        internalCounters.push_back(16169);
        internalCounters.push_back(16280);
        internalCounters.push_back(16391);
        internalCounters.push_back(16502);
        internalCounters.push_back(16613);
        internalCounters.push_back(11841);
        internalCounters.push_back(11952);
        internalCounters.push_back(12063);
        internalCounters.push_back(12174);
        internalCounters.push_back(12285);
        internalCounters.push_back(12396);
        internalCounters.push_back(12507);
        internalCounters.push_back(12618);
        internalCounters.push_back(12729);
        internalCounters.push_back(12840);
        internalCounters.push_back(12951);
        internalCounters.push_back(13062);
        internalCounters.push_back(13173);
        internalCounters.push_back(13284);
        internalCounters.push_back(13395);
        internalCounters.push_back(13506);
        internalCounters.push_back(13617);
        internalCounters.push_back(13728);
        internalCounters.push_back(13839);
        internalCounters.push_back(13950);
        internalCounters.push_back(14061);
        internalCounters.push_back(14172);
        internalCounters.push_back(14283);
        internalCounters.push_back(14394);
        internalCounters.push_back(14505);
        internalCounters.push_back(14616);
        internalCounters.push_back(14727);
        internalCounters.push_back(14838);
        internalCounters.push_back(14949);
        internalCounters.push_back(15060);
        internalCounters.push_back(15171);
        internalCounters.push_back(15282);
        internalCounters.push_back(15393);
        internalCounters.push_back(15504);
        internalCounters.push_back(15615);
        internalCounters.push_back(15726);
        internalCounters.push_back(15837);
        internalCounters.push_back(15948);
        internalCounters.push_back(16059);
        internalCounters.push_back(16170);
        internalCounters.push_back(16281);
        internalCounters.push_back(16392);
        internalCounters.push_back(16503);
        internalCounters.push_back(16614);
        internalCounters.push_back(11842);
        internalCounters.push_back(11953);
        internalCounters.push_back(12064);
        internalCounters.push_back(12175);
        internalCounters.push_back(12286);
        internalCounters.push_back(12397);
        internalCounters.push_back(12508);
        internalCounters.push_back(12619);
        internalCounters.push_back(12730);
        internalCounters.push_back(12841);
        internalCounters.push_back(12952);
        internalCounters.push_back(13063);
        internalCounters.push_back(13174);
        internalCounters.push_back(13285);
        internalCounters.push_back(13396);
        internalCounters.push_back(13507);
        internalCounters.push_back(13618);
        internalCounters.push_back(13729);
        internalCounters.push_back(13840);
        internalCounters.push_back(13951);
        internalCounters.push_back(14062);
        internalCounters.push_back(14173);
        internalCounters.push_back(14284);
        internalCounters.push_back(14395);
        internalCounters.push_back(14506);
        internalCounters.push_back(14617);
        internalCounters.push_back(14728);
        internalCounters.push_back(14839);
        internalCounters.push_back(14950);
        internalCounters.push_back(15061);
        internalCounters.push_back(15172);
        internalCounters.push_back(15283);
        internalCounters.push_back(15394);
        internalCounters.push_back(15505);
        internalCounters.push_back(15616);
        internalCounters.push_back(15727);
        internalCounters.push_back(15838);
        internalCounters.push_back(15949);
        internalCounters.push_back(16060);
        internalCounters.push_back(16171);
        internalCounters.push_back(16282);
        internalCounters.push_back(16393);
        internalCounters.push_back(16504);
        internalCounters.push_back(16615);
        internalCounters.push_back(11843);
        internalCounters.push_back(11954);
        internalCounters.push_back(12065);
        internalCounters.push_back(12176);
        internalCounters.push_back(12287);
        internalCounters.push_back(12398);
        internalCounters.push_back(12509);
        internalCounters.push_back(12620);
        internalCounters.push_back(12731);
        internalCounters.push_back(12842);
        internalCounters.push_back(12953);
        internalCounters.push_back(13064);
        internalCounters.push_back(13175);
        internalCounters.push_back(13286);
        internalCounters.push_back(13397);
        internalCounters.push_back(13508);
        internalCounters.push_back(13619);
        internalCounters.push_back(13730);
        internalCounters.push_back(13841);
        internalCounters.push_back(13952);
        internalCounters.push_back(14063);
        internalCounters.push_back(14174);
        internalCounters.push_back(14285);
        internalCounters.push_back(14396);
        internalCounters.push_back(14507);
        internalCounters.push_back(14618);
        internalCounters.push_back(14729);
        internalCounters.push_back(14840);
        internalCounters.push_back(14951);
        internalCounters.push_back(15062);
        internalCounters.push_back(15173);
        internalCounters.push_back(15284);
        internalCounters.push_back(15395);
        internalCounters.push_back(15506);
        internalCounters.push_back(15617);
        internalCounters.push_back(15728);
        internalCounters.push_back(15839);
        internalCounters.push_back(15950);
        internalCounters.push_back(16061);
        internalCounters.push_back(16172);
        internalCounters.push_back(16283);
        internalCounters.push_back(16394);
        internalCounters.push_back(16505);
        internalCounters.push_back(16616);
        internalCounters.push_back(11844);
        internalCounters.push_back(11955);
        internalCounters.push_back(12066);
        internalCounters.push_back(12177);
        internalCounters.push_back(12288);
        internalCounters.push_back(12399);
        internalCounters.push_back(12510);
        internalCounters.push_back(12621);
        internalCounters.push_back(12732);
        internalCounters.push_back(12843);
        internalCounters.push_back(12954);
        internalCounters.push_back(13065);
        internalCounters.push_back(13176);
        internalCounters.push_back(13287);
        internalCounters.push_back(13398);
        internalCounters.push_back(13509);
        internalCounters.push_back(13620);
        internalCounters.push_back(13731);
        internalCounters.push_back(13842);
        internalCounters.push_back(13953);
        internalCounters.push_back(14064);
        internalCounters.push_back(14175);
        internalCounters.push_back(14286);
        internalCounters.push_back(14397);
        internalCounters.push_back(14508);
        internalCounters.push_back(14619);
        internalCounters.push_back(14730);
        internalCounters.push_back(14841);
        internalCounters.push_back(14952);
        internalCounters.push_back(15063);
        internalCounters.push_back(15174);
        internalCounters.push_back(15285);
        internalCounters.push_back(15396);
        internalCounters.push_back(15507);
        internalCounters.push_back(15618);
        internalCounters.push_back(15729);
        internalCounters.push_back(15840);
        internalCounters.push_back(15951);
        internalCounters.push_back(16062);
        internalCounters.push_back(16173);
        internalCounters.push_back(16284);
        internalCounters.push_back(16395);
        internalCounters.push_back(16506);
        internalCounters.push_back(16617);
        internalCounters.push_back(11845);
        internalCounters.push_back(11956);
        internalCounters.push_back(12067);
        internalCounters.push_back(12178);
        internalCounters.push_back(12289);
        internalCounters.push_back(12400);
        internalCounters.push_back(12511);
        internalCounters.push_back(12622);
        internalCounters.push_back(12733);
        internalCounters.push_back(12844);
        internalCounters.push_back(12955);
        internalCounters.push_back(13066);
        internalCounters.push_back(13177);
        internalCounters.push_back(13288);
        internalCounters.push_back(13399);
        internalCounters.push_back(13510);
        internalCounters.push_back(13621);
        internalCounters.push_back(13732);
        internalCounters.push_back(13843);
        internalCounters.push_back(13954);
        internalCounters.push_back(14065);
        internalCounters.push_back(14176);
        internalCounters.push_back(14287);
        internalCounters.push_back(14398);
        internalCounters.push_back(14509);
        internalCounters.push_back(14620);
        internalCounters.push_back(14731);
        internalCounters.push_back(14842);
        internalCounters.push_back(14953);
        internalCounters.push_back(15064);
        internalCounters.push_back(15175);
        internalCounters.push_back(15286);
        internalCounters.push_back(15397);
        internalCounters.push_back(15508);
        internalCounters.push_back(15619);
        internalCounters.push_back(15730);
        internalCounters.push_back(15841);
        internalCounters.push_back(15952);
        internalCounters.push_back(16063);
        internalCounters.push_back(16174);
        internalCounters.push_back(16285);
        internalCounters.push_back(16396);
        internalCounters.push_back(16507);
        internalCounters.push_back(16618);
        internalCounters.push_back(11846);
        internalCounters.push_back(11957);
        internalCounters.push_back(12068);
        internalCounters.push_back(12179);
        internalCounters.push_back(12290);
        internalCounters.push_back(12401);
        internalCounters.push_back(12512);
        internalCounters.push_back(12623);
        internalCounters.push_back(12734);
        internalCounters.push_back(12845);
        internalCounters.push_back(12956);
        internalCounters.push_back(13067);
        internalCounters.push_back(13178);
        internalCounters.push_back(13289);
        internalCounters.push_back(13400);
        internalCounters.push_back(13511);
        internalCounters.push_back(13622);
        internalCounters.push_back(13733);
        internalCounters.push_back(13844);
        internalCounters.push_back(13955);
        internalCounters.push_back(14066);
        internalCounters.push_back(14177);
        internalCounters.push_back(14288);
        internalCounters.push_back(14399);
        internalCounters.push_back(14510);
        internalCounters.push_back(14621);
        internalCounters.push_back(14732);
        internalCounters.push_back(14843);
        internalCounters.push_back(14954);
        internalCounters.push_back(15065);
        internalCounters.push_back(15176);
        internalCounters.push_back(15287);
        internalCounters.push_back(15398);
        internalCounters.push_back(15509);
        internalCounters.push_back(15620);
        internalCounters.push_back(15731);
        internalCounters.push_back(15842);
        internalCounters.push_back(15953);
        internalCounters.push_back(16064);
        internalCounters.push_back(16175);
        internalCounters.push_back(16286);
        internalCounters.push_back(16397);
        internalCounters.push_back(16508);
        internalCounters.push_back(16619);

        p.DefinePublicCounter("TexAveAnisotropy", "TextureUnit", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,sum44,(2),44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,sum44,*,+,(4),88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,sum44,*,+,(6),132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,sum44,*,+,(8),176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,sum44,*,+,(10),220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,sum44,*,+,(12),264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,sum44,*,+,(14),308,309,310,311,312,313,314,315,316,317,318,319,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,sum44,*,+,(16),352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,384,385,386,387,388,389,390,391,392,393,394,395,sum44,*,+,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,sum44,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,sum44,+,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,sum44,+,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,sum44,+,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,sum44,+,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,sum44,+,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,sum44,+,308,309,310,311,312,313,314,315,316,317,318,319,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,sum44,+,352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,384,385,386,387,388,389,390,391,392,393,394,395,sum44,+,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(28347);
        internalCounters.push_back(28604);
        internalCounters.push_back(28861);
        internalCounters.push_back(29118);
        internalCounters.push_back(29375);
        internalCounters.push_back(29632);
        internalCounters.push_back(29889);
        internalCounters.push_back(30146);
        internalCounters.push_back(30403);
        internalCounters.push_back(30660);
        internalCounters.push_back(30917);
        internalCounters.push_back(31174);
        internalCounters.push_back(31431);
        internalCounters.push_back(31688);
        internalCounters.push_back(31945);
        internalCounters.push_back(32202);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("DepthStencilTestBusy", "Timing", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(28347);
        internalCounters.push_back(28604);
        internalCounters.push_back(28861);
        internalCounters.push_back(29118);
        internalCounters.push_back(29375);
        internalCounters.push_back(29632);
        internalCounters.push_back(29889);
        internalCounters.push_back(30146);
        internalCounters.push_back(30403);
        internalCounters.push_back(30660);
        internalCounters.push_back(30917);
        internalCounters.push_back(31174);
        internalCounters.push_back(31431);
        internalCounters.push_back(31688);
        internalCounters.push_back(31945);
        internalCounters.push_back(32202);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("DepthStencilTestBusyCount", "Timing", "Number of GPU cycles spent performing depth and stencil tests.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(28218);
        internalCounters.push_back(28475);
        internalCounters.push_back(28732);
        internalCounters.push_back(28989);
        internalCounters.push_back(29246);
        internalCounters.push_back(29503);
        internalCounters.push_back(29760);
        internalCounters.push_back(30017);
        internalCounters.push_back(30274);
        internalCounters.push_back(30531);
        internalCounters.push_back(30788);
        internalCounters.push_back(31045);
        internalCounters.push_back(31302);
        internalCounters.push_back(31559);
        internalCounters.push_back(31816);
        internalCounters.push_back(32073);
        internalCounters.push_back(28207);
        internalCounters.push_back(28464);
        internalCounters.push_back(28721);
        internalCounters.push_back(28978);
        internalCounters.push_back(29235);
        internalCounters.push_back(29492);
        internalCounters.push_back(29749);
        internalCounters.push_back(30006);
        internalCounters.push_back(30263);
        internalCounters.push_back(30520);
        internalCounters.push_back(30777);
        internalCounters.push_back(31034);
        internalCounters.push_back(31291);
        internalCounters.push_back(31548);
        internalCounters.push_back(31805);
        internalCounters.push_back(32062);

        p.DefinePublicCounter("HiZTilesAccepted", "DepthAndStencil", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(28218);
        internalCounters.push_back(28475);
        internalCounters.push_back(28732);
        internalCounters.push_back(28989);
        internalCounters.push_back(29246);
        internalCounters.push_back(29503);
        internalCounters.push_back(29760);
        internalCounters.push_back(30017);
        internalCounters.push_back(30274);
        internalCounters.push_back(30531);
        internalCounters.push_back(30788);
        internalCounters.push_back(31045);
        internalCounters.push_back(31302);
        internalCounters.push_back(31559);
        internalCounters.push_back(31816);
        internalCounters.push_back(32073);

        p.DefinePublicCounter("HiZTilesAcceptedCount", "DepthAndStencil", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(28207);
        internalCounters.push_back(28464);
        internalCounters.push_back(28721);
        internalCounters.push_back(28978);
        internalCounters.push_back(29235);
        internalCounters.push_back(29492);
        internalCounters.push_back(29749);
        internalCounters.push_back(30006);
        internalCounters.push_back(30263);
        internalCounters.push_back(30520);
        internalCounters.push_back(30777);
        internalCounters.push_back(31034);
        internalCounters.push_back(31291);
        internalCounters.push_back(31548);
        internalCounters.push_back(31805);
        internalCounters.push_back(32062);

        p.DefinePublicCounter("HiZTilesRejectedCount", "DepthAndStencil", "Count of tiles not accepted by HiZ.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(28207);
        internalCounters.push_back(28464);
        internalCounters.push_back(28721);
        internalCounters.push_back(28978);
        internalCounters.push_back(29235);
        internalCounters.push_back(29492);
        internalCounters.push_back(29749);
        internalCounters.push_back(30006);
        internalCounters.push_back(30263);
        internalCounters.push_back(30520);
        internalCounters.push_back(30777);
        internalCounters.push_back(31034);
        internalCounters.push_back(31291);
        internalCounters.push_back(31548);
        internalCounters.push_back(31805);
        internalCounters.push_back(32062);
        internalCounters.push_back(28231);
        internalCounters.push_back(28488);
        internalCounters.push_back(28745);
        internalCounters.push_back(29002);
        internalCounters.push_back(29259);
        internalCounters.push_back(29516);
        internalCounters.push_back(29773);
        internalCounters.push_back(30030);
        internalCounters.push_back(30287);
        internalCounters.push_back(30544);
        internalCounters.push_back(30801);
        internalCounters.push_back(31058);
        internalCounters.push_back(31315);
        internalCounters.push_back(31572);
        internalCounters.push_back(31829);
        internalCounters.push_back(32086);

        p.DefinePublicCounter("PreZTilesDetailCulled", "DepthAndStencil", "Percentage of tiles rejected because the associated prim had no contributing area.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(28231);
        internalCounters.push_back(28488);
        internalCounters.push_back(28745);
        internalCounters.push_back(29002);
        internalCounters.push_back(29259);
        internalCounters.push_back(29516);
        internalCounters.push_back(29773);
        internalCounters.push_back(30030);
        internalCounters.push_back(30287);
        internalCounters.push_back(30544);
        internalCounters.push_back(30801);
        internalCounters.push_back(31058);
        internalCounters.push_back(31315);
        internalCounters.push_back(31572);
        internalCounters.push_back(31829);
        internalCounters.push_back(32086);

        p.DefinePublicCounter("PreZTilesDetailCulledCount", "DepthAndStencil", "Count of tiles rejected because the associated primitive had no contributing area.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(28207);
        internalCounters.push_back(28464);
        internalCounters.push_back(28721);
        internalCounters.push_back(28978);
        internalCounters.push_back(29235);
        internalCounters.push_back(29492);
        internalCounters.push_back(29749);
        internalCounters.push_back(30006);
        internalCounters.push_back(30263);
        internalCounters.push_back(30520);
        internalCounters.push_back(30777);
        internalCounters.push_back(31034);
        internalCounters.push_back(31291);
        internalCounters.push_back(31548);
        internalCounters.push_back(31805);
        internalCounters.push_back(32062);

        p.DefinePublicCounter("PreZTilesDetailSurvivingCount", "DepthAndStencil", "Count of tiles surviving because the associated primitive had contributing area.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1396);
        internalCounters.push_back(1791);
        internalCounters.push_back(2186);
        internalCounters.push_back(2581);
        internalCounters.push_back(1397);
        internalCounters.push_back(1792);
        internalCounters.push_back(2187);
        internalCounters.push_back(2582);
        internalCounters.push_back(1398);
        internalCounters.push_back(1793);
        internalCounters.push_back(2188);
        internalCounters.push_back(2583);
        internalCounters.push_back(1399);
        internalCounters.push_back(1794);
        internalCounters.push_back(2189);
        internalCounters.push_back(2584);
        internalCounters.push_back(1472);
        internalCounters.push_back(1867);
        internalCounters.push_back(2262);
        internalCounters.push_back(2657);
        internalCounters.push_back(1473);
        internalCounters.push_back(1868);
        internalCounters.push_back(2263);
        internalCounters.push_back(2658);
        internalCounters.push_back(1474);
        internalCounters.push_back(1869);
        internalCounters.push_back(2264);
        internalCounters.push_back(2659);
        internalCounters.push_back(1475);
        internalCounters.push_back(1870);
        internalCounters.push_back(2265);
        internalCounters.push_back(2660);

        p.DefinePublicCounter("HiZQuadsCulled", "DepthAndStencil", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1396);
        internalCounters.push_back(1791);
        internalCounters.push_back(2186);
        internalCounters.push_back(2581);
        internalCounters.push_back(1397);
        internalCounters.push_back(1792);
        internalCounters.push_back(2187);
        internalCounters.push_back(2582);
        internalCounters.push_back(1398);
        internalCounters.push_back(1793);
        internalCounters.push_back(2188);
        internalCounters.push_back(2583);
        internalCounters.push_back(1399);
        internalCounters.push_back(1794);
        internalCounters.push_back(2189);
        internalCounters.push_back(2584);
        internalCounters.push_back(1472);
        internalCounters.push_back(1867);
        internalCounters.push_back(2262);
        internalCounters.push_back(2657);
        internalCounters.push_back(1473);
        internalCounters.push_back(1868);
        internalCounters.push_back(2263);
        internalCounters.push_back(2658);
        internalCounters.push_back(1474);
        internalCounters.push_back(1869);
        internalCounters.push_back(2264);
        internalCounters.push_back(2659);
        internalCounters.push_back(1475);
        internalCounters.push_back(1870);
        internalCounters.push_back(2265);
        internalCounters.push_back(2660);

        p.DefinePublicCounter("HiZQuadsCulledCount", "DepthAndStencil", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1472);
        internalCounters.push_back(1867);
        internalCounters.push_back(2262);
        internalCounters.push_back(2657);
        internalCounters.push_back(1473);
        internalCounters.push_back(1868);
        internalCounters.push_back(2263);
        internalCounters.push_back(2658);
        internalCounters.push_back(1474);
        internalCounters.push_back(1869);
        internalCounters.push_back(2264);
        internalCounters.push_back(2659);
        internalCounters.push_back(1475);
        internalCounters.push_back(1870);
        internalCounters.push_back(2265);
        internalCounters.push_back(2660);

        p.DefinePublicCounter("HiZQuadsAcceptedCount", "DepthAndStencil", "Count of quads that did continue on in the pipeline after HiZ.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1396);
        internalCounters.push_back(1791);
        internalCounters.push_back(2186);
        internalCounters.push_back(2581);
        internalCounters.push_back(1397);
        internalCounters.push_back(1792);
        internalCounters.push_back(2187);
        internalCounters.push_back(2582);
        internalCounters.push_back(1398);
        internalCounters.push_back(1793);
        internalCounters.push_back(2188);
        internalCounters.push_back(2583);
        internalCounters.push_back(1399);
        internalCounters.push_back(1794);
        internalCounters.push_back(2189);
        internalCounters.push_back(2584);
        internalCounters.push_back(1496);
        internalCounters.push_back(1891);
        internalCounters.push_back(2286);
        internalCounters.push_back(2681);
        internalCounters.push_back(1472);
        internalCounters.push_back(1867);
        internalCounters.push_back(2262);
        internalCounters.push_back(2657);
        internalCounters.push_back(1473);
        internalCounters.push_back(1868);
        internalCounters.push_back(2263);
        internalCounters.push_back(2658);
        internalCounters.push_back(1474);
        internalCounters.push_back(1869);
        internalCounters.push_back(2264);
        internalCounters.push_back(2659);
        internalCounters.push_back(1475);
        internalCounters.push_back(1870);
        internalCounters.push_back(2265);
        internalCounters.push_back(2660);

        p.DefinePublicCounter("PreZQuadsCulled", "DepthAndStencil", "Percentage of quads rejected based on the detailZ and earlyZ tests.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,sum16,16,17,18,19,sum4,-,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1396);
        internalCounters.push_back(1791);
        internalCounters.push_back(2186);
        internalCounters.push_back(2581);
        internalCounters.push_back(1397);
        internalCounters.push_back(1792);
        internalCounters.push_back(2187);
        internalCounters.push_back(2582);
        internalCounters.push_back(1398);
        internalCounters.push_back(1793);
        internalCounters.push_back(2188);
        internalCounters.push_back(2583);
        internalCounters.push_back(1399);
        internalCounters.push_back(1794);
        internalCounters.push_back(2189);
        internalCounters.push_back(2584);
        internalCounters.push_back(1496);
        internalCounters.push_back(1891);
        internalCounters.push_back(2286);
        internalCounters.push_back(2681);
        internalCounters.push_back(1472);
        internalCounters.push_back(1867);
        internalCounters.push_back(2262);
        internalCounters.push_back(2657);
        internalCounters.push_back(1473);
        internalCounters.push_back(1868);
        internalCounters.push_back(2263);
        internalCounters.push_back(2658);
        internalCounters.push_back(1474);
        internalCounters.push_back(1869);
        internalCounters.push_back(2264);
        internalCounters.push_back(2659);
        internalCounters.push_back(1475);
        internalCounters.push_back(1870);
        internalCounters.push_back(2265);
        internalCounters.push_back(2660);

        p.DefinePublicCounter("PreZQuadsCulledCount", "DepthAndStencil", "Count of quads rejected based on the detailZ and earlyZ tests.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,sum4,-,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,sum16,-");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1496);
        internalCounters.push_back(1891);
        internalCounters.push_back(2286);
        internalCounters.push_back(2681);
        internalCounters.push_back(1472);
        internalCounters.push_back(1867);
        internalCounters.push_back(2262);
        internalCounters.push_back(2657);
        internalCounters.push_back(1473);
        internalCounters.push_back(1868);
        internalCounters.push_back(2263);
        internalCounters.push_back(2658);
        internalCounters.push_back(1474);
        internalCounters.push_back(1869);
        internalCounters.push_back(2264);
        internalCounters.push_back(2659);
        internalCounters.push_back(1475);
        internalCounters.push_back(1870);
        internalCounters.push_back(2265);
        internalCounters.push_back(2660);

        p.DefinePublicCounter("PreZQuadsSurvivingCount", "DepthAndStencil", "Count of quads surviving detailZ and earlyZ tests.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,sum16,0,1,2,3,sum4,-");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1496);
        internalCounters.push_back(1891);
        internalCounters.push_back(2286);
        internalCounters.push_back(2681);
        internalCounters.push_back(1396);
        internalCounters.push_back(1791);
        internalCounters.push_back(2186);
        internalCounters.push_back(2581);
        internalCounters.push_back(1397);
        internalCounters.push_back(1792);
        internalCounters.push_back(2187);
        internalCounters.push_back(2582);
        internalCounters.push_back(1398);
        internalCounters.push_back(1793);
        internalCounters.push_back(2188);
        internalCounters.push_back(2583);
        internalCounters.push_back(1399);
        internalCounters.push_back(1794);
        internalCounters.push_back(2189);
        internalCounters.push_back(2584);

        p.DefinePublicCounter("PostZQuads", "DepthAndStencil", "Percentage of quads for which the pixel shader will run and may be postZ tested.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,sum16,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1496);
        internalCounters.push_back(1891);
        internalCounters.push_back(2286);
        internalCounters.push_back(2681);

        p.DefinePublicCounter("PostZQuadCount", "DepthAndStencil", "Count of quads for which the pixel shader will run and may be postZ tested.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(28380);
        internalCounters.push_back(28637);
        internalCounters.push_back(28894);
        internalCounters.push_back(29151);
        internalCounters.push_back(29408);
        internalCounters.push_back(29665);
        internalCounters.push_back(29922);
        internalCounters.push_back(30179);
        internalCounters.push_back(30436);
        internalCounters.push_back(30693);
        internalCounters.push_back(30950);
        internalCounters.push_back(31207);
        internalCounters.push_back(31464);
        internalCounters.push_back(31721);
        internalCounters.push_back(31978);
        internalCounters.push_back(32235);

        p.DefinePublicCounter("PreZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z before shading and passed.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(28382);
        internalCounters.push_back(28639);
        internalCounters.push_back(28896);
        internalCounters.push_back(29153);
        internalCounters.push_back(29410);
        internalCounters.push_back(29667);
        internalCounters.push_back(29924);
        internalCounters.push_back(30181);
        internalCounters.push_back(30438);
        internalCounters.push_back(30695);
        internalCounters.push_back(30952);
        internalCounters.push_back(31209);
        internalCounters.push_back(31466);
        internalCounters.push_back(31723);
        internalCounters.push_back(31980);
        internalCounters.push_back(32237);

        p.DefinePublicCounter("PreZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z before shading and failed stencil test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(28381);
        internalCounters.push_back(28638);
        internalCounters.push_back(28895);
        internalCounters.push_back(29152);
        internalCounters.push_back(29409);
        internalCounters.push_back(29666);
        internalCounters.push_back(29923);
        internalCounters.push_back(30180);
        internalCounters.push_back(30437);
        internalCounters.push_back(30694);
        internalCounters.push_back(30951);
        internalCounters.push_back(31208);
        internalCounters.push_back(31465);
        internalCounters.push_back(31722);
        internalCounters.push_back(31979);
        internalCounters.push_back(32236);

        p.DefinePublicCounter("PreZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z before shading and failed Z test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(28377);
        internalCounters.push_back(28634);
        internalCounters.push_back(28891);
        internalCounters.push_back(29148);
        internalCounters.push_back(29405);
        internalCounters.push_back(29662);
        internalCounters.push_back(29919);
        internalCounters.push_back(30176);
        internalCounters.push_back(30433);
        internalCounters.push_back(30690);
        internalCounters.push_back(30947);
        internalCounters.push_back(31204);
        internalCounters.push_back(31461);
        internalCounters.push_back(31718);
        internalCounters.push_back(31975);
        internalCounters.push_back(32232);

        p.DefinePublicCounter("PostZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z after shading and passed.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(28379);
        internalCounters.push_back(28636);
        internalCounters.push_back(28893);
        internalCounters.push_back(29150);
        internalCounters.push_back(29407);
        internalCounters.push_back(29664);
        internalCounters.push_back(29921);
        internalCounters.push_back(30178);
        internalCounters.push_back(30435);
        internalCounters.push_back(30692);
        internalCounters.push_back(30949);
        internalCounters.push_back(31206);
        internalCounters.push_back(31463);
        internalCounters.push_back(31720);
        internalCounters.push_back(31977);
        internalCounters.push_back(32234);

        p.DefinePublicCounter("PostZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z after shading and failed stencil test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(28378);
        internalCounters.push_back(28635);
        internalCounters.push_back(28892);
        internalCounters.push_back(29149);
        internalCounters.push_back(29406);
        internalCounters.push_back(29663);
        internalCounters.push_back(29920);
        internalCounters.push_back(30177);
        internalCounters.push_back(30434);
        internalCounters.push_back(30691);
        internalCounters.push_back(30948);
        internalCounters.push_back(31205);
        internalCounters.push_back(31462);
        internalCounters.push_back(31719);
        internalCounters.push_back(31976);
        internalCounters.push_back(32233);

        p.DefinePublicCounter("PostZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z after shading and failed Z test.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(28249);
        internalCounters.push_back(28506);
        internalCounters.push_back(28763);
        internalCounters.push_back(29020);
        internalCounters.push_back(29277);
        internalCounters.push_back(29534);
        internalCounters.push_back(29791);
        internalCounters.push_back(30048);
        internalCounters.push_back(30305);
        internalCounters.push_back(30562);
        internalCounters.push_back(30819);
        internalCounters.push_back(31076);
        internalCounters.push_back(31333);
        internalCounters.push_back(31590);
        internalCounters.push_back(31847);
        internalCounters.push_back(32104);
        internalCounters.push_back(36073);

        p.DefinePublicCounter("ZUnitStalled", "DepthAndStencil", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(28249);
        internalCounters.push_back(28506);
        internalCounters.push_back(28763);
        internalCounters.push_back(29020);
        internalCounters.push_back(29277);
        internalCounters.push_back(29534);
        internalCounters.push_back(29791);
        internalCounters.push_back(30048);
        internalCounters.push_back(30305);
        internalCounters.push_back(30562);
        internalCounters.push_back(30819);
        internalCounters.push_back(31076);
        internalCounters.push_back(31333);
        internalCounters.push_back(31590);
        internalCounters.push_back(31847);
        internalCounters.push_back(32104);

        p.DefinePublicCounter("ZUnitStalledCycles", "DepthAndStencil", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(28251);
        internalCounters.push_back(28508);
        internalCounters.push_back(28765);
        internalCounters.push_back(29022);
        internalCounters.push_back(29279);
        internalCounters.push_back(29536);
        internalCounters.push_back(29793);
        internalCounters.push_back(30050);
        internalCounters.push_back(30307);
        internalCounters.push_back(30564);
        internalCounters.push_back(30821);
        internalCounters.push_back(31078);
        internalCounters.push_back(31335);
        internalCounters.push_back(31592);
        internalCounters.push_back(31849);
        internalCounters.push_back(32106);
        internalCounters.push_back(28258);
        internalCounters.push_back(28515);
        internalCounters.push_back(28772);
        internalCounters.push_back(29029);
        internalCounters.push_back(29286);
        internalCounters.push_back(29543);
        internalCounters.push_back(29800);
        internalCounters.push_back(30057);
        internalCounters.push_back(30314);
        internalCounters.push_back(30571);
        internalCounters.push_back(30828);
        internalCounters.push_back(31085);
        internalCounters.push_back(31342);
        internalCounters.push_back(31599);
        internalCounters.push_back(31856);
        internalCounters.push_back(32113);

        p.DefinePublicCounter("DBMemRead", "DepthAndStencil", "Number of bytes read from the depth buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(256),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(28263);
        internalCounters.push_back(28520);
        internalCounters.push_back(28777);
        internalCounters.push_back(29034);
        internalCounters.push_back(29291);
        internalCounters.push_back(29548);
        internalCounters.push_back(29805);
        internalCounters.push_back(30062);
        internalCounters.push_back(30319);
        internalCounters.push_back(30576);
        internalCounters.push_back(30833);
        internalCounters.push_back(31090);
        internalCounters.push_back(31347);
        internalCounters.push_back(31604);
        internalCounters.push_back(31861);
        internalCounters.push_back(32118);
        internalCounters.push_back(28266);
        internalCounters.push_back(28523);
        internalCounters.push_back(28780);
        internalCounters.push_back(29037);
        internalCounters.push_back(29294);
        internalCounters.push_back(29551);
        internalCounters.push_back(29808);
        internalCounters.push_back(30065);
        internalCounters.push_back(30322);
        internalCounters.push_back(30579);
        internalCounters.push_back(30836);
        internalCounters.push_back(31093);
        internalCounters.push_back(31350);
        internalCounters.push_back(31607);
        internalCounters.push_back(31864);
        internalCounters.push_back(32121);

        p.DefinePublicCounter("DBMemWritten", "DepthAndStencil", "Number of bytes written to the depth buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(256),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(32442);
        internalCounters.push_back(32668);
        internalCounters.push_back(32894);
        internalCounters.push_back(33120);
        internalCounters.push_back(33346);
        internalCounters.push_back(33572);
        internalCounters.push_back(33798);
        internalCounters.push_back(34024);
        internalCounters.push_back(34250);
        internalCounters.push_back(34476);
        internalCounters.push_back(34702);
        internalCounters.push_back(34928);
        internalCounters.push_back(35154);
        internalCounters.push_back(35380);
        internalCounters.push_back(35606);
        internalCounters.push_back(35832);

        p.DefinePublicCounter("CBMemRead", "ColorBuffer", "Number of bytes read from the color buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(32432);
        internalCounters.push_back(32658);
        internalCounters.push_back(32884);
        internalCounters.push_back(33110);
        internalCounters.push_back(33336);
        internalCounters.push_back(33562);
        internalCounters.push_back(33788);
        internalCounters.push_back(34014);
        internalCounters.push_back(34240);
        internalCounters.push_back(34466);
        internalCounters.push_back(34692);
        internalCounters.push_back(34918);
        internalCounters.push_back(35144);
        internalCounters.push_back(35370);
        internalCounters.push_back(35596);
        internalCounters.push_back(35822);

        p.DefinePublicCounter("CBMemWritten", "ColorBuffer", "Number of bytes written to the color buffer.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(32476);
        internalCounters.push_back(32702);
        internalCounters.push_back(32928);
        internalCounters.push_back(33154);
        internalCounters.push_back(33380);
        internalCounters.push_back(33606);
        internalCounters.push_back(33832);
        internalCounters.push_back(34058);
        internalCounters.push_back(34284);
        internalCounters.push_back(34510);
        internalCounters.push_back(34736);
        internalCounters.push_back(34962);
        internalCounters.push_back(35188);
        internalCounters.push_back(35414);
        internalCounters.push_back(35640);
        internalCounters.push_back(35866);
        internalCounters.push_back(32322);
        internalCounters.push_back(32548);
        internalCounters.push_back(32774);
        internalCounters.push_back(33000);
        internalCounters.push_back(33226);
        internalCounters.push_back(33452);
        internalCounters.push_back(33678);
        internalCounters.push_back(33904);
        internalCounters.push_back(34130);
        internalCounters.push_back(34356);
        internalCounters.push_back(34582);
        internalCounters.push_back(34808);
        internalCounters.push_back(35034);
        internalCounters.push_back(35260);
        internalCounters.push_back(35486);
        internalCounters.push_back(35712);

        p.DefinePublicCounter("CBSlowPixelPct", "ColorBuffer", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(32476);
        internalCounters.push_back(32702);
        internalCounters.push_back(32928);
        internalCounters.push_back(33154);
        internalCounters.push_back(33380);
        internalCounters.push_back(33606);
        internalCounters.push_back(33832);
        internalCounters.push_back(34058);
        internalCounters.push_back(34284);
        internalCounters.push_back(34510);
        internalCounters.push_back(34736);
        internalCounters.push_back(34962);
        internalCounters.push_back(35188);
        internalCounters.push_back(35414);
        internalCounters.push_back(35640);
        internalCounters.push_back(35866);

        p.DefinePublicCounter("CBSlowPixelCount", "ColorBuffer", "Number of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
}

