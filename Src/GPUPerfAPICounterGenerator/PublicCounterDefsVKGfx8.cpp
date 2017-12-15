//==============================================================================
// Copyright (c) 2010-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  PublicCounterDefinitions for VKGFX8
//==============================================================================

#include "PublicCounterDefsVKGfx8.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicCountersVKGfx8(GPA_PublicCounters& p)
{
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(51127);

        p.DefinePublicCounter("GPUTime", "Timing", "Time this API call took to execute on the GPU in milliseconds. Does not include time that draw calls are processed in parallel.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_API_DYNAMIC, internalCounters, "0,TS_FREQ,/,(1000),*", "00bfa9cd-5512-48e8-7055-7b592113b8cb" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(49739);
        internalCounters.push_back(49737);

        p.DefinePublicCounter("GPUBusy", "Timing", "The percentage of time GPU was busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,/,(100),*,(100),min", "bef38bf3-1167-0844-81f0-67d2d28ddbc5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(49739);

        p.DefinePublicCounter("GPUBusyCycles", "Timing", "Number of GPU cycles that the GPU was busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0", "1e84970d-7014-2b8d-d61e-388b5f782691" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(191);
        internalCounters.push_back(337);
        internalCounters.push_back(483);
        internalCounters.push_back(629);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("TessellatorBusy", "Timing", "The percentage of time the tessellation engine is busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,/,(100),*", "36af6c72-dcfb-8102-4fd4-ce8ddc573365" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(191);
        internalCounters.push_back(337);
        internalCounters.push_back(483);
        internalCounters.push_back(629);

        p.DefinePublicCounter("TessellatorBusyCycles", "Timing", "Number of GPU cycles that the tessellation engine is busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max", "60289dcb-7b33-46e7-26d1-8a2121605543" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2852);
        internalCounters.push_back(3049);
        internalCounters.push_back(3246);
        internalCounters.push_back(3443);
        internalCounters.push_back(2877);
        internalCounters.push_back(3074);
        internalCounters.push_back(3271);
        internalCounters.push_back(3468);
        internalCounters.push_back(2899);
        internalCounters.push_back(3096);
        internalCounters.push_back(3293);
        internalCounters.push_back(3490);
        internalCounters.push_back(2921);
        internalCounters.push_back(3118);
        internalCounters.push_back(3315);
        internalCounters.push_back(3512);
        internalCounters.push_back(2861);
        internalCounters.push_back(3058);
        internalCounters.push_back(3255);
        internalCounters.push_back(3452);
        internalCounters.push_back(2883);
        internalCounters.push_back(3080);
        internalCounters.push_back(3277);
        internalCounters.push_back(3474);
        internalCounters.push_back(2905);
        internalCounters.push_back(3102);
        internalCounters.push_back(3299);
        internalCounters.push_back(3496);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("VSBusy", "Timing", "The percentage of time the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,16,ifnotzero,4,20,ifnotzero,8,24,ifnotzero,(0),1,17,ifnotzero,5,21,ifnotzero,9,25,ifnotzero,max,(0),2,18,ifnotzero,6,22,ifnotzero,10,26,ifnotzero,max,(0),3,19,ifnotzero,7,23,ifnotzero,11,27,ifnotzero,max,28,/,(100),*,(100),min", "94caad5e-867c-6c09-cf3a-d05b51df8f3b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2852);
        internalCounters.push_back(3049);
        internalCounters.push_back(3246);
        internalCounters.push_back(3443);
        internalCounters.push_back(2877);
        internalCounters.push_back(3074);
        internalCounters.push_back(3271);
        internalCounters.push_back(3468);
        internalCounters.push_back(2899);
        internalCounters.push_back(3096);
        internalCounters.push_back(3293);
        internalCounters.push_back(3490);
        internalCounters.push_back(2921);
        internalCounters.push_back(3118);
        internalCounters.push_back(3315);
        internalCounters.push_back(3512);
        internalCounters.push_back(2861);
        internalCounters.push_back(3058);
        internalCounters.push_back(3255);
        internalCounters.push_back(3452);
        internalCounters.push_back(2883);
        internalCounters.push_back(3080);
        internalCounters.push_back(3277);
        internalCounters.push_back(3474);
        internalCounters.push_back(2905);
        internalCounters.push_back(3102);
        internalCounters.push_back(3299);
        internalCounters.push_back(3496);

        p.DefinePublicCounter("VSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,16,ifnotzero,4,20,ifnotzero,8,24,ifnotzero,(0),1,17,ifnotzero,5,21,ifnotzero,9,25,ifnotzero,max,(0),2,18,ifnotzero,6,22,ifnotzero,10,26,ifnotzero,max,(0),3,19,ifnotzero,7,23,ifnotzero,11,27,ifnotzero,max", "a2086d4e-274b-48a8-3e08-a4ab76ac15dd" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(51127);
        internalCounters.push_back(2852);
        internalCounters.push_back(3049);
        internalCounters.push_back(3246);
        internalCounters.push_back(3443);
        internalCounters.push_back(2877);
        internalCounters.push_back(3074);
        internalCounters.push_back(3271);
        internalCounters.push_back(3468);
        internalCounters.push_back(2899);
        internalCounters.push_back(3096);
        internalCounters.push_back(3293);
        internalCounters.push_back(3490);
        internalCounters.push_back(2921);
        internalCounters.push_back(3118);
        internalCounters.push_back(3315);
        internalCounters.push_back(3512);
        internalCounters.push_back(2861);
        internalCounters.push_back(3058);
        internalCounters.push_back(3255);
        internalCounters.push_back(3452);
        internalCounters.push_back(2883);
        internalCounters.push_back(3080);
        internalCounters.push_back(3277);
        internalCounters.push_back(3474);
        internalCounters.push_back(2905);
        internalCounters.push_back(3102);
        internalCounters.push_back(3299);
        internalCounters.push_back(3496);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("VSTime", "Timing", "Time vertex shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,17,ifnotzero,5,21,ifnotzero,9,25,ifnotzero,(0),2,18,ifnotzero,6,22,ifnotzero,10,26,ifnotzero,max,(0),3,19,ifnotzero,7,23,ifnotzero,11,27,ifnotzero,max,(0),4,20,ifnotzero,8,24,ifnotzero,12,28,ifnotzero,max,29,/,(1),min,0,TS_FREQ,/,(1000),*,*", "fee660c7-8e01-4dc5-e5d0-fcb61c17fb2c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2889);
        internalCounters.push_back(3086);
        internalCounters.push_back(3283);
        internalCounters.push_back(3480);
        internalCounters.push_back(2895);
        internalCounters.push_back(3092);
        internalCounters.push_back(3289);
        internalCounters.push_back(3486);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("HSBusy", "Timing", "The percentage of time the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,8,/,(100),*,(100),min", "16f30a0b-4cbf-eccd-b13f-ab68dd254d32" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2889);
        internalCounters.push_back(3086);
        internalCounters.push_back(3283);
        internalCounters.push_back(3480);
        internalCounters.push_back(2895);
        internalCounters.push_back(3092);
        internalCounters.push_back(3289);
        internalCounters.push_back(3486);

        p.DefinePublicCounter("HSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max", "753e76ef-8ef8-3f13-b511-4bd9f3589fdb" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(51127);
        internalCounters.push_back(2889);
        internalCounters.push_back(3086);
        internalCounters.push_back(3283);
        internalCounters.push_back(3480);
        internalCounters.push_back(2895);
        internalCounters.push_back(3092);
        internalCounters.push_back(3289);
        internalCounters.push_back(3486);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("HSTime", "Timing", "Time hull shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,5,ifnotzero,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,(0),4,8,ifnotzero,max,9,/,(1),min,0,TS_FREQ,/,(1000),*,*", "8792e9f1-fb39-b92a-b230-f33df4c8a0de" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2852);
        internalCounters.push_back(3049);
        internalCounters.push_back(3246);
        internalCounters.push_back(3443);
        internalCounters.push_back(2877);
        internalCounters.push_back(3074);
        internalCounters.push_back(3271);
        internalCounters.push_back(3468);
        internalCounters.push_back(2921);
        internalCounters.push_back(3118);
        internalCounters.push_back(3315);
        internalCounters.push_back(3512);
        internalCounters.push_back(2883);
        internalCounters.push_back(3080);
        internalCounters.push_back(3277);
        internalCounters.push_back(3474);
        internalCounters.push_back(2905);
        internalCounters.push_back(3102);
        internalCounters.push_back(3299);
        internalCounters.push_back(3496);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("DSBusy", "Timing", "The percentage of time the ShaderUnit has domain shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,12,ifnotzero,16,ifnotzero,(0),1,5,13,ifnotzero,17,ifnotzero,max,(0),2,6,14,ifnotzero,18,ifnotzero,max,(0),3,7,15,ifnotzero,19,ifnotzero,max,20,/,(100),*,(100),min", "0c626e8a-9b82-b6d4-d9a3-578509316301" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2852);
        internalCounters.push_back(3049);
        internalCounters.push_back(3246);
        internalCounters.push_back(3443);
        internalCounters.push_back(2877);
        internalCounters.push_back(3074);
        internalCounters.push_back(3271);
        internalCounters.push_back(3468);
        internalCounters.push_back(2921);
        internalCounters.push_back(3118);
        internalCounters.push_back(3315);
        internalCounters.push_back(3512);
        internalCounters.push_back(2883);
        internalCounters.push_back(3080);
        internalCounters.push_back(3277);
        internalCounters.push_back(3474);
        internalCounters.push_back(2905);
        internalCounters.push_back(3102);
        internalCounters.push_back(3299);
        internalCounters.push_back(3496);

        p.DefinePublicCounter("DSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has domain shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,12,ifnotzero,16,ifnotzero,(0),1,5,13,ifnotzero,17,ifnotzero,max,(0),2,6,14,ifnotzero,18,ifnotzero,max,(0),3,7,15,ifnotzero,19,ifnotzero,max", "2f3f7561-0549-2232-536d-129ffc5f7703" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(51127);
        internalCounters.push_back(2852);
        internalCounters.push_back(3049);
        internalCounters.push_back(3246);
        internalCounters.push_back(3443);
        internalCounters.push_back(2877);
        internalCounters.push_back(3074);
        internalCounters.push_back(3271);
        internalCounters.push_back(3468);
        internalCounters.push_back(2921);
        internalCounters.push_back(3118);
        internalCounters.push_back(3315);
        internalCounters.push_back(3512);
        internalCounters.push_back(2883);
        internalCounters.push_back(3080);
        internalCounters.push_back(3277);
        internalCounters.push_back(3474);
        internalCounters.push_back(2905);
        internalCounters.push_back(3102);
        internalCounters.push_back(3299);
        internalCounters.push_back(3496);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("DSTime", "Timing", "Time domain shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,5,13,ifnotzero,17,ifnotzero,(0),2,6,14,ifnotzero,18,ifnotzero,max,(0),3,7,15,ifnotzero,19,ifnotzero,max,(0),4,8,16,ifnotzero,20,ifnotzero,max,21,/,(1),min,0,TS_FREQ,/,(1000),*,*", "f050e495-f511-ecc9-9c46-c96516bddeb2" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2868);
        internalCounters.push_back(3065);
        internalCounters.push_back(3262);
        internalCounters.push_back(3459);
        internalCounters.push_back(2871);
        internalCounters.push_back(3068);
        internalCounters.push_back(3265);
        internalCounters.push_back(3462);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("GSBusy", "Timing", "The percentage of time the ShaderUnit has geometry shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,8,/,(100),*,(100),min", "876f36d8-d046-833f-7832-673cbffd0a45" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2868);
        internalCounters.push_back(3065);
        internalCounters.push_back(3262);
        internalCounters.push_back(3459);
        internalCounters.push_back(2871);
        internalCounters.push_back(3068);
        internalCounters.push_back(3265);
        internalCounters.push_back(3462);

        p.DefinePublicCounter("GSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has geometry shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max", "48203b6b-8983-c067-d63e-05da8be5111b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(51127);
        internalCounters.push_back(2868);
        internalCounters.push_back(3065);
        internalCounters.push_back(3262);
        internalCounters.push_back(3459);
        internalCounters.push_back(2871);
        internalCounters.push_back(3068);
        internalCounters.push_back(3265);
        internalCounters.push_back(3462);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("GSTime", "Timing", "Time geometry shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,5,ifnotzero,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,(0),4,8,ifnotzero,max,9,/,(1),min,0,TS_FREQ,/,(1000),*,*", "86d56794-f391-b601-9388-851b646d346c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2921);
        internalCounters.push_back(3118);
        internalCounters.push_back(3315);
        internalCounters.push_back(3512);
        internalCounters.push_back(2926);
        internalCounters.push_back(3123);
        internalCounters.push_back(3320);
        internalCounters.push_back(3517);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("PSBusy", "Timing", "The percentage of time the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,8,/,(100),*", "7e772beb-d82c-bd9a-aed0-fe504d416ce5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2921);
        internalCounters.push_back(3118);
        internalCounters.push_back(3315);
        internalCounters.push_back(3512);
        internalCounters.push_back(2926);
        internalCounters.push_back(3123);
        internalCounters.push_back(3320);
        internalCounters.push_back(3517);

        p.DefinePublicCounter("PSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max", "b58bea04-ce8e-2984-80f4-8aba7d4c817b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(51127);
        internalCounters.push_back(2921);
        internalCounters.push_back(3118);
        internalCounters.push_back(3315);
        internalCounters.push_back(3512);
        internalCounters.push_back(2926);
        internalCounters.push_back(3123);
        internalCounters.push_back(3320);
        internalCounters.push_back(3517);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("PSTime", "Timing", "Time pixel shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,5,ifnotzero,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,(0),4,8,ifnotzero,max,9,/,0,TS_FREQ,/,(1000),*,*", "f564ee00-ffcf-f7f6-fcbf-f200205cd0cc" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2909);
        internalCounters.push_back(3106);
        internalCounters.push_back(3303);
        internalCounters.push_back(3500);
        internalCounters.push_back(2913);
        internalCounters.push_back(3110);
        internalCounters.push_back(3307);
        internalCounters.push_back(3504);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("CSBusy", "Timing", "The percentage of time the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,8,/,(100),*,(100),min", "493fdd90-8d2b-a055-5e4e-2d29c3396b8c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2909);
        internalCounters.push_back(3106);
        internalCounters.push_back(3303);
        internalCounters.push_back(3500);
        internalCounters.push_back(2913);
        internalCounters.push_back(3110);
        internalCounters.push_back(3307);
        internalCounters.push_back(3504);

        p.DefinePublicCounter("CSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max", "39bcf1b8-f6b2-4c37-f9af-0a2bb59512f9" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(51127);
        internalCounters.push_back(2909);
        internalCounters.push_back(3106);
        internalCounters.push_back(3303);
        internalCounters.push_back(3500);
        internalCounters.push_back(2913);
        internalCounters.push_back(3110);
        internalCounters.push_back(3307);
        internalCounters.push_back(3504);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("CSTime", "Timing", "Time compute shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),1,5,ifnotzero,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,(0),4,8,ifnotzero,max,9,/,(1),min,0,TS_FREQ,/,(1000),*,*", "5177faaf-f59d-ee23-6e36-0ea087dca9dc" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(87);
        internalCounters.push_back(233);
        internalCounters.push_back(379);
        internalCounters.push_back(525);
        internalCounters.push_back(68);
        internalCounters.push_back(214);
        internalCounters.push_back(360);
        internalCounters.push_back(506);
        internalCounters.push_back(163);
        internalCounters.push_back(309);
        internalCounters.push_back(455);
        internalCounters.push_back(601);

        p.DefinePublicCounter("VSVerticesIn", "VertexShader", "The number of vertices processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,4,5,6,7,sum4,ifnotzero,8,9,10,11,sum4,8,9,10,11,sum4,ifnotzero", "810a04c8-2ff4-081d-766d-bfa2bd4ad916" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7253);
        internalCounters.push_back(7552);
        internalCounters.push_back(7851);
        internalCounters.push_back(8150);
        internalCounters.push_back(7231);
        internalCounters.push_back(7530);
        internalCounters.push_back(7829);
        internalCounters.push_back(8128);
        internalCounters.push_back(4861);
        internalCounters.push_back(5160);
        internalCounters.push_back(5459);
        internalCounters.push_back(5758);
        internalCounters.push_back(4839);
        internalCounters.push_back(5138);
        internalCounters.push_back(5437);
        internalCounters.push_back(5736);
        internalCounters.push_back(4849);
        internalCounters.push_back(5148);
        internalCounters.push_back(5447);
        internalCounters.push_back(5746);
        internalCounters.push_back(9645);
        internalCounters.push_back(9944);
        internalCounters.push_back(10243);
        internalCounters.push_back(10542);
        internalCounters.push_back(9623);
        internalCounters.push_back(9922);
        internalCounters.push_back(10221);
        internalCounters.push_back(10520);
        internalCounters.push_back(9633);
        internalCounters.push_back(9932);
        internalCounters.push_back(10231);
        internalCounters.push_back(10530);

        p.DefinePublicCounter("VSVALUInstCount", "VertexShader", "Average number of vector ALU instructions executed in the VS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,12,13,14,15,sum4,/,16,17,18,19,sum4,ifnotzero,20,21,22,23,sum4,24,25,26,27,sum4,/,28,29,30,31,sum4,ifnotzero", "8ec604e4-63f5-e6b5-4558-c38f0b26d4b1" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7257);
        internalCounters.push_back(7556);
        internalCounters.push_back(7855);
        internalCounters.push_back(8154);
        internalCounters.push_back(7231);
        internalCounters.push_back(7530);
        internalCounters.push_back(7829);
        internalCounters.push_back(8128);
        internalCounters.push_back(4865);
        internalCounters.push_back(5164);
        internalCounters.push_back(5463);
        internalCounters.push_back(5762);
        internalCounters.push_back(4839);
        internalCounters.push_back(5138);
        internalCounters.push_back(5437);
        internalCounters.push_back(5736);
        internalCounters.push_back(4849);
        internalCounters.push_back(5148);
        internalCounters.push_back(5447);
        internalCounters.push_back(5746);
        internalCounters.push_back(9649);
        internalCounters.push_back(9948);
        internalCounters.push_back(10247);
        internalCounters.push_back(10546);
        internalCounters.push_back(9623);
        internalCounters.push_back(9922);
        internalCounters.push_back(10221);
        internalCounters.push_back(10520);
        internalCounters.push_back(9633);
        internalCounters.push_back(9932);
        internalCounters.push_back(10231);
        internalCounters.push_back(10530);

        p.DefinePublicCounter("VSSALUInstCount", "VertexShader", "Average number of scalar ALU instructions executed in the VS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,12,13,14,15,sum4,/,16,17,18,19,sum4,ifnotzero,20,21,22,23,sum4,24,25,26,27,sum4,/,28,29,30,31,sum4,ifnotzero", "e3da0383-7322-7f65-8cf2-3ce641578e54" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7308);
        internalCounters.push_back(7607);
        internalCounters.push_back(7906);
        internalCounters.push_back(8205);
        internalCounters.push_back(4916);
        internalCounters.push_back(5215);
        internalCounters.push_back(5514);
        internalCounters.push_back(5813);
        internalCounters.push_back(4849);
        internalCounters.push_back(5148);
        internalCounters.push_back(5447);
        internalCounters.push_back(5746);
        internalCounters.push_back(49739);
        internalCounters.push_back(9700);
        internalCounters.push_back(9999);
        internalCounters.push_back(10298);
        internalCounters.push_back(10597);
        internalCounters.push_back(9633);
        internalCounters.push_back(9932);
        internalCounters.push_back(10231);
        internalCounters.push_back(10530);

        p.DefinePublicCounter("VSVALUBusy", "VertexShader", "The percentage of GPUTime vector ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,ifnotzero,13,14,15,16,sum4,17,18,19,20,sum4,ifnotzero,(4),*,NUM_SIMDS,/,12,/,(100),*", "8b3572f7-fda0-eddf-6c93-2ab145b8754b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7308);
        internalCounters.push_back(7607);
        internalCounters.push_back(7906);
        internalCounters.push_back(8205);
        internalCounters.push_back(4916);
        internalCounters.push_back(5215);
        internalCounters.push_back(5514);
        internalCounters.push_back(5813);
        internalCounters.push_back(4849);
        internalCounters.push_back(5148);
        internalCounters.push_back(5447);
        internalCounters.push_back(5746);
        internalCounters.push_back(9700);
        internalCounters.push_back(9999);
        internalCounters.push_back(10298);
        internalCounters.push_back(10597);
        internalCounters.push_back(9633);
        internalCounters.push_back(9932);
        internalCounters.push_back(10231);
        internalCounters.push_back(10530);

        p.DefinePublicCounter("VSVALUBusyCycles", "VertexShader", "Number of GPU cycles where vector ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,ifnotzero,12,13,14,15,sum4,16,17,18,19,sum4,ifnotzero,(4),*,NUM_SIMDS,/", "0af1686e-6d77-2f6e-2862-7bb8e869a776" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7313);
        internalCounters.push_back(7612);
        internalCounters.push_back(7911);
        internalCounters.push_back(8210);
        internalCounters.push_back(4921);
        internalCounters.push_back(5220);
        internalCounters.push_back(5519);
        internalCounters.push_back(5818);
        internalCounters.push_back(4849);
        internalCounters.push_back(5148);
        internalCounters.push_back(5447);
        internalCounters.push_back(5746);
        internalCounters.push_back(49739);
        internalCounters.push_back(9705);
        internalCounters.push_back(10004);
        internalCounters.push_back(10303);
        internalCounters.push_back(10602);
        internalCounters.push_back(9633);
        internalCounters.push_back(9932);
        internalCounters.push_back(10231);
        internalCounters.push_back(10530);

        p.DefinePublicCounter("VSSALUBusy", "VertexShader", "The percentage of GPUTime scalar ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,ifnotzero,13,14,15,16,sum4,17,18,19,20,sum4,ifnotzero,(4),*,NUM_SIMDS,/,12,/,(100),*", "3bc8730c-e3bc-e2f0-7d24-36974064c25a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7313);
        internalCounters.push_back(7612);
        internalCounters.push_back(7911);
        internalCounters.push_back(8210);
        internalCounters.push_back(4921);
        internalCounters.push_back(5220);
        internalCounters.push_back(5519);
        internalCounters.push_back(5818);
        internalCounters.push_back(4849);
        internalCounters.push_back(5148);
        internalCounters.push_back(5447);
        internalCounters.push_back(5746);
        internalCounters.push_back(9705);
        internalCounters.push_back(10004);
        internalCounters.push_back(10303);
        internalCounters.push_back(10602);
        internalCounters.push_back(9633);
        internalCounters.push_back(9932);
        internalCounters.push_back(10231);
        internalCounters.push_back(10530);

        p.DefinePublicCounter("VSSALUBusyCycles", "VertexShader", "Number of GPU cycles where scalar ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,ifnotzero,12,13,14,15,sum4,16,17,18,19,sum4,ifnotzero,(4),*,NUM_SIMDS,/", "357ac7cd-2e1c-dcb0-77f6-37527237f35b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(172);
        internalCounters.push_back(318);
        internalCounters.push_back(464);
        internalCounters.push_back(610);

        p.DefinePublicCounter("HSPatches", "HullShader", "The number of patches processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4", "d1bbd27d-d591-4509-df52-d329fb73a98f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10841);
        internalCounters.push_back(11140);
        internalCounters.push_back(11439);
        internalCounters.push_back(11738);
        internalCounters.push_back(10819);
        internalCounters.push_back(11118);
        internalCounters.push_back(11417);
        internalCounters.push_back(11716);

        p.DefinePublicCounter("HSVALUInstCount", "HullShader", "Average number of vector ALU instructions executed in the HS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/", "786673bf-d58f-9895-3a37-9d6efb5e5804" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10845);
        internalCounters.push_back(11144);
        internalCounters.push_back(11443);
        internalCounters.push_back(11742);
        internalCounters.push_back(10819);
        internalCounters.push_back(11118);
        internalCounters.push_back(11417);
        internalCounters.push_back(11716);

        p.DefinePublicCounter("HSSALUInstCount", "HullShader", "Average number of scalar ALU instructions executed in the HS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/", "1af675c4-cb0b-c4c5-c131-2796750f683e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10896);
        internalCounters.push_back(11195);
        internalCounters.push_back(11494);
        internalCounters.push_back(11793);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("HSVALUBusy", "HullShader", "The percentage of GPUTime vector ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/,4,/,(100),*", "7880d192-8015-0311-d43e-fb0b7a4df179" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10896);
        internalCounters.push_back(11195);
        internalCounters.push_back(11494);
        internalCounters.push_back(11793);

        p.DefinePublicCounter("HSVALUBusyCycles", "HullShader", "Number of GPU cycles vector where ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/", "3afb94e4-e937-5730-0cc9-41d3113ba012" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10901);
        internalCounters.push_back(11200);
        internalCounters.push_back(11499);
        internalCounters.push_back(11798);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("HSSALUBusy", "HullShader", "The percentage of GPUTime scalar ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/,4,/,(100),*", "34748a4b-9148-0b06-b7b9-5700d6631bde" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10901);
        internalCounters.push_back(11200);
        internalCounters.push_back(11499);
        internalCounters.push_back(11798);

        p.DefinePublicCounter("HSSALUBusyCycles", "HullShader", "Number of GPU cycles where scalar ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/", "9bceabf7-3f01-2fd9-7b1d-8fe46c729efc" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(87);
        internalCounters.push_back(233);
        internalCounters.push_back(379);
        internalCounters.push_back(525);
        internalCounters.push_back(68);
        internalCounters.push_back(214);
        internalCounters.push_back(360);
        internalCounters.push_back(506);
        internalCounters.push_back(163);
        internalCounters.push_back(309);
        internalCounters.push_back(455);
        internalCounters.push_back(601);

        p.DefinePublicCounter("DSVerticesIn", "DomainShader", "The number of vertices processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,4,5,6,7,sum4,ifnotzero,8,9,10,11,sum4,ifnotzero", "b88d9d05-2418-e639-4e3d-3a5815855f8d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7253);
        internalCounters.push_back(7552);
        internalCounters.push_back(7851);
        internalCounters.push_back(8150);
        internalCounters.push_back(7231);
        internalCounters.push_back(7530);
        internalCounters.push_back(7829);
        internalCounters.push_back(8128);
        internalCounters.push_back(4861);
        internalCounters.push_back(5160);
        internalCounters.push_back(5459);
        internalCounters.push_back(5758);
        internalCounters.push_back(4839);
        internalCounters.push_back(5138);
        internalCounters.push_back(5437);
        internalCounters.push_back(5736);
        internalCounters.push_back(4849);
        internalCounters.push_back(5148);
        internalCounters.push_back(5447);
        internalCounters.push_back(5746);
        internalCounters.push_back(9633);
        internalCounters.push_back(9932);
        internalCounters.push_back(10231);
        internalCounters.push_back(10530);

        p.DefinePublicCounter("DSVALUInstCount", "DomainShader", "Average number of vector ALU instructions executed in the DS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,12,13,14,15,sum4,/,16,17,18,19,sum4,ifnotzero,20,21,22,23,sum4,ifnotzero", "03a3e949-82f9-be4d-7228-5eb5ad80915a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7257);
        internalCounters.push_back(7556);
        internalCounters.push_back(7855);
        internalCounters.push_back(8154);
        internalCounters.push_back(7231);
        internalCounters.push_back(7530);
        internalCounters.push_back(7829);
        internalCounters.push_back(8128);
        internalCounters.push_back(4865);
        internalCounters.push_back(5164);
        internalCounters.push_back(5463);
        internalCounters.push_back(5762);
        internalCounters.push_back(4839);
        internalCounters.push_back(5138);
        internalCounters.push_back(5437);
        internalCounters.push_back(5736);
        internalCounters.push_back(4849);
        internalCounters.push_back(5148);
        internalCounters.push_back(5447);
        internalCounters.push_back(5746);
        internalCounters.push_back(9633);
        internalCounters.push_back(9932);
        internalCounters.push_back(10231);
        internalCounters.push_back(10530);

        p.DefinePublicCounter("DSSALUInstCount", "DomainShader", "Average number of scalar ALU instructions executed in the DS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,12,13,14,15,sum4,/,16,17,18,19,sum4,ifnotzero,20,21,22,23,sum4,ifnotzero", "73daa728-483e-95d0-5b40-504719aadc1c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7308);
        internalCounters.push_back(7607);
        internalCounters.push_back(7906);
        internalCounters.push_back(8205);
        internalCounters.push_back(4916);
        internalCounters.push_back(5215);
        internalCounters.push_back(5514);
        internalCounters.push_back(5813);
        internalCounters.push_back(49739);
        internalCounters.push_back(4849);
        internalCounters.push_back(5148);
        internalCounters.push_back(5447);
        internalCounters.push_back(5746);
        internalCounters.push_back(9633);
        internalCounters.push_back(9932);
        internalCounters.push_back(10231);
        internalCounters.push_back(10530);

        p.DefinePublicCounter("DSVALUBusy", "DomainShader", "The percentage of GPUTime vector ALU instructions are being processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,9,10,11,12,sum4,ifnotzero,13,14,15,16,sum4,ifnotzero,(4),*,NUM_SIMDS,/,8,/,(100),*", "ddc0dd0c-0c73-b831-a410-cfea8b9713d9" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7308);
        internalCounters.push_back(7607);
        internalCounters.push_back(7906);
        internalCounters.push_back(8205);
        internalCounters.push_back(4916);
        internalCounters.push_back(5215);
        internalCounters.push_back(5514);
        internalCounters.push_back(5813);
        internalCounters.push_back(4849);
        internalCounters.push_back(5148);
        internalCounters.push_back(5447);
        internalCounters.push_back(5746);
        internalCounters.push_back(9633);
        internalCounters.push_back(9932);
        internalCounters.push_back(10231);
        internalCounters.push_back(10530);

        p.DefinePublicCounter("DSVALUBusyCycles", "DomainShader", "Number of GPU cycles where vector ALU instructions are being processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,ifnotzero,12,13,14,15,sum4,ifnotzero,(4),*,NUM_SIMDS,/", "1e280912-81ee-a684-823b-94c468d8ebda" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7313);
        internalCounters.push_back(7612);
        internalCounters.push_back(7911);
        internalCounters.push_back(8210);
        internalCounters.push_back(4921);
        internalCounters.push_back(5220);
        internalCounters.push_back(5519);
        internalCounters.push_back(5818);
        internalCounters.push_back(49739);
        internalCounters.push_back(4849);
        internalCounters.push_back(5148);
        internalCounters.push_back(5447);
        internalCounters.push_back(5746);
        internalCounters.push_back(9633);
        internalCounters.push_back(9932);
        internalCounters.push_back(10231);
        internalCounters.push_back(10530);

        p.DefinePublicCounter("DSSALUBusy", "DomainShader", "The percentage of GPUTime scalar ALU instructions are being processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,9,10,11,12,sum4,ifnotzero,13,14,15,16,sum4,ifnotzero,(4),*,NUM_SIMDS,/,8,/,(100),*", "b639f64c-24af-348f-6439-43c701b4fc07" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(7313);
        internalCounters.push_back(7612);
        internalCounters.push_back(7911);
        internalCounters.push_back(8210);
        internalCounters.push_back(4921);
        internalCounters.push_back(5220);
        internalCounters.push_back(5519);
        internalCounters.push_back(5818);
        internalCounters.push_back(4849);
        internalCounters.push_back(5148);
        internalCounters.push_back(5447);
        internalCounters.push_back(5746);
        internalCounters.push_back(9633);
        internalCounters.push_back(9932);
        internalCounters.push_back(10231);
        internalCounters.push_back(10530);

        p.DefinePublicCounter("DSSALUBusyCycles", "DomainShader", "Number of GPU cycles where scalar ALU instructions are being processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,ifnotzero,12,13,14,15,sum4,ifnotzero,(4),*,NUM_SIMDS,/", "b5bf8a0c-e682-1aa6-23d7-c6c6784ffa5c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(76);
        internalCounters.push_back(222);
        internalCounters.push_back(368);
        internalCounters.push_back(514);

        p.DefinePublicCounter("GSPrimsIn", "GeometryShader", "The number of primitives passed into the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4", "20c29866-509a-aaab-2697-6b2c38f79953" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(87);
        internalCounters.push_back(233);
        internalCounters.push_back(379);
        internalCounters.push_back(525);
        internalCounters.push_back(68);
        internalCounters.push_back(214);
        internalCounters.push_back(360);
        internalCounters.push_back(506);

        p.DefinePublicCounter("GSVerticesOut", "GeometryShader", "The number of vertices output by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,ifnotzero", "775b9736-319a-bd8a-48c9-68db9c91d978" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6057);
        internalCounters.push_back(6356);
        internalCounters.push_back(6655);
        internalCounters.push_back(6954);
        internalCounters.push_back(6035);
        internalCounters.push_back(6334);
        internalCounters.push_back(6633);
        internalCounters.push_back(6932);

        p.DefinePublicCounter("GSVALUInstCount", "GeometryShader", "Average number of vector ALU instructions executed in the GS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/", "21b12bfa-b8cd-2e71-a2d5-f9e9f1d65d61" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6061);
        internalCounters.push_back(6360);
        internalCounters.push_back(6659);
        internalCounters.push_back(6958);
        internalCounters.push_back(6035);
        internalCounters.push_back(6334);
        internalCounters.push_back(6633);
        internalCounters.push_back(6932);

        p.DefinePublicCounter("GSSALUInstCount", "GeometryShader", "Average number of scalar ALU instructions executed in the GS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/", "a8562594-d335-ca43-61bf-03b72d2b98a5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6112);
        internalCounters.push_back(6411);
        internalCounters.push_back(6710);
        internalCounters.push_back(7009);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("GSVALUBusy", "GeometryShader", "The percentage of GPUTime vector ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/,4,/,(100),*", "228a4818-1e56-cebb-0720-3b2cdc057a6f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6112);
        internalCounters.push_back(6411);
        internalCounters.push_back(6710);
        internalCounters.push_back(7009);

        p.DefinePublicCounter("GSVALUBusyCycles", "GeometryShader", "Number of GPU cycles where vector ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/", "be217edd-226f-bd97-9a48-46e2809b1933" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6117);
        internalCounters.push_back(6416);
        internalCounters.push_back(6715);
        internalCounters.push_back(7014);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("GSSALUBusy", "GeometryShader", "The percentage of GPUTime scalar ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,4,/,(100),*", "f28ce300-800e-9822-39e4-f48528bdb935" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6117);
        internalCounters.push_back(6416);
        internalCounters.push_back(6715);
        internalCounters.push_back(7014);

        p.DefinePublicCounter("GSSALUBusyCycles", "GeometryShader", "Number of GPU cycles where scalar ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "b3eace7c-3bc4-0107-887f-923851dc8ea7" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(756);
        internalCounters.push_back(909);
        internalCounters.push_back(1062);
        internalCounters.push_back(1215);
        internalCounters.push_back(760);
        internalCounters.push_back(913);
        internalCounters.push_back(1066);
        internalCounters.push_back(1219);
        internalCounters.push_back(712);
        internalCounters.push_back(865);
        internalCounters.push_back(1018);
        internalCounters.push_back(1171);
        internalCounters.push_back(724);
        internalCounters.push_back(877);
        internalCounters.push_back(1030);
        internalCounters.push_back(1183);
        internalCounters.push_back(713);
        internalCounters.push_back(866);
        internalCounters.push_back(1019);
        internalCounters.push_back(1172);
        internalCounters.push_back(725);
        internalCounters.push_back(878);
        internalCounters.push_back(1031);
        internalCounters.push_back(1184);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("PrimitiveAssemblyBusy", "Timing", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max,24,/,(100),*,(100),min", "54ac5640-c4d7-95e2-20e0-6a9fdfc07333" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(756);
        internalCounters.push_back(909);
        internalCounters.push_back(1062);
        internalCounters.push_back(1215);
        internalCounters.push_back(760);
        internalCounters.push_back(913);
        internalCounters.push_back(1066);
        internalCounters.push_back(1219);
        internalCounters.push_back(712);
        internalCounters.push_back(865);
        internalCounters.push_back(1018);
        internalCounters.push_back(1171);
        internalCounters.push_back(724);
        internalCounters.push_back(877);
        internalCounters.push_back(1030);
        internalCounters.push_back(1183);
        internalCounters.push_back(713);
        internalCounters.push_back(866);
        internalCounters.push_back(1019);
        internalCounters.push_back(1172);
        internalCounters.push_back(725);
        internalCounters.push_back(878);
        internalCounters.push_back(1031);
        internalCounters.push_back(1184);

        p.DefinePublicCounter("PrimitiveAssemblyBusyCycles", "Timing", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max", "99777f2d-9626-c78a-a97c-c4505eba1e5f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(659);
        internalCounters.push_back(812);
        internalCounters.push_back(965);
        internalCounters.push_back(1118);

        p.DefinePublicCounter("PrimitivesIn", "PrimitiveAssembly", "The number of primitives received by the hardware. This includes primitives generated by tessellation.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4", "a515b80d-75c3-c7d2-0d2f-d7766b4759a6" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(665);
        internalCounters.push_back(818);
        internalCounters.push_back(971);
        internalCounters.push_back(1124);
        internalCounters.push_back(705);
        internalCounters.push_back(858);
        internalCounters.push_back(1011);
        internalCounters.push_back(1164);
        internalCounters.push_back(706);
        internalCounters.push_back(859);
        internalCounters.push_back(1012);
        internalCounters.push_back(1165);
        internalCounters.push_back(707);
        internalCounters.push_back(860);
        internalCounters.push_back(1013);
        internalCounters.push_back(1166);
        internalCounters.push_back(708);
        internalCounters.push_back(861);
        internalCounters.push_back(1014);
        internalCounters.push_back(1167);

        p.DefinePublicCounter("CulledPrims", "PrimitiveAssembly", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,+,2,+,3,+,4,+,5,+,6,+,7,+,8,+,9,+,10,+,11,+,12,+,13,+,14,+,15,+,16,+,17,+,18,+,19,+", "589bdf55-9192-280a-41c3-584bc94f2562" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(672);
        internalCounters.push_back(825);
        internalCounters.push_back(978);
        internalCounters.push_back(1131);

        p.DefinePublicCounter("ClippedPrims", "PrimitiveAssembly", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4", "5ef6f9d5-155e-5baa-163f-8359d9ea9bbf" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(760);
        internalCounters.push_back(913);
        internalCounters.push_back(1066);
        internalCounters.push_back(1219);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("PAStalledOnRasterizer", "PrimitiveAssembly", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,/,(100),*", "6f9f416b-53c1-0457-f88c-7b6ba8973974" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(760);
        internalCounters.push_back(913);
        internalCounters.push_back(1066);
        internalCounters.push_back(1219);

        p.DefinePublicCounter("PAStalledOnRasterizerCycles", "PrimitiveAssembly", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max", "7a8c492a-c566-9328-6805-760dbff5c0f2" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13219);
        internalCounters.push_back(13253);
        internalCounters.push_back(13287);
        internalCounters.push_back(13321);
        internalCounters.push_back(13224);
        internalCounters.push_back(13258);
        internalCounters.push_back(13292);
        internalCounters.push_back(13326);
        internalCounters.push_back(13229);
        internalCounters.push_back(13263);
        internalCounters.push_back(13297);
        internalCounters.push_back(13331);
        internalCounters.push_back(13234);
        internalCounters.push_back(13268);
        internalCounters.push_back(13302);
        internalCounters.push_back(13336);

        p.DefinePublicCounter("PSPixelsOut", "PixelShader", "Pixels exported from shader to colour buffers. Does not include killed or alpha tested pixels; if there are multiple rendertargets, each rendertarget receives one export, so this will be 2 for 1 pixel written to two RTs.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,12,13,14,15,sum4,sum4", "181f5ca1-ec90-61a3-fd73-d8e3722af9e9" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13221);
        internalCounters.push_back(13255);
        internalCounters.push_back(13289);
        internalCounters.push_back(13323);
        internalCounters.push_back(13226);
        internalCounters.push_back(13260);
        internalCounters.push_back(13294);
        internalCounters.push_back(13328);
        internalCounters.push_back(13231);
        internalCounters.push_back(13265);
        internalCounters.push_back(13299);
        internalCounters.push_back(13333);
        internalCounters.push_back(13236);
        internalCounters.push_back(13270);
        internalCounters.push_back(13304);
        internalCounters.push_back(13338);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("PSExportStalls", "PixelShader", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the colour buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max,16,/,(100),*", "996ce2b4-55ce-25c1-afb7-575bd9b4ce90" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13221);
        internalCounters.push_back(13255);
        internalCounters.push_back(13289);
        internalCounters.push_back(13323);
        internalCounters.push_back(13226);
        internalCounters.push_back(13260);
        internalCounters.push_back(13294);
        internalCounters.push_back(13328);
        internalCounters.push_back(13231);
        internalCounters.push_back(13265);
        internalCounters.push_back(13299);
        internalCounters.push_back(13333);
        internalCounters.push_back(13236);
        internalCounters.push_back(13270);
        internalCounters.push_back(13304);
        internalCounters.push_back(13338);

        p.DefinePublicCounter("PSExportStallsCycles", "PixelShader", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the colour buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max", "5e58e8ae-1854-e662-b460-a4a31f7fb493" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8449);
        internalCounters.push_back(8748);
        internalCounters.push_back(9047);
        internalCounters.push_back(9346);
        internalCounters.push_back(8427);
        internalCounters.push_back(8726);
        internalCounters.push_back(9025);
        internalCounters.push_back(9324);

        p.DefinePublicCounter("PSVALUInstCount", "PixelShader", "Average number of vector ALU instructions executed in the PS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/", "eb74389e-435c-4137-ecf1-39eb5bc1cbfe" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8453);
        internalCounters.push_back(8752);
        internalCounters.push_back(9051);
        internalCounters.push_back(9350);
        internalCounters.push_back(8427);
        internalCounters.push_back(8726);
        internalCounters.push_back(9025);
        internalCounters.push_back(9324);

        p.DefinePublicCounter("PSSALUInstCount", "PixelShader", "Average number of scalar ALU instructions executed in the PS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/", "e6a06580-8a82-96d6-976c-acc121fc5516" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8504);
        internalCounters.push_back(8803);
        internalCounters.push_back(9102);
        internalCounters.push_back(9401);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("PSVALUBusy", "PixelShader", "The percentage of GPUTime vector ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/,4,/,(100),*", "6ce6fef7-8e33-10b4-f351-af755e177e85" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8504);
        internalCounters.push_back(8803);
        internalCounters.push_back(9102);
        internalCounters.push_back(9401);

        p.DefinePublicCounter("PSVALUBusyCycles", "PixelShader", "Number of GPU cycles where vector ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/", "1e276f86-cd2a-72e7-fc9d-004f666f2981" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8509);
        internalCounters.push_back(8808);
        internalCounters.push_back(9107);
        internalCounters.push_back(9406);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("PSSALUBusy", "PixelShader", "The percentage of GPUTime scalar ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,4,/,(100),*", "2ff9f34f-e94b-af4d-18c2-5fbbf6d1727a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(8509);
        internalCounters.push_back(8808);
        internalCounters.push_back(9107);
        internalCounters.push_back(9406);

        p.DefinePublicCounter("PSSALUBusyCycles", "PixelShader", "Number of GPU cycles where scalar ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "29808906-f128-b078-fc79-820a4b3b3b8d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2910);
        internalCounters.push_back(3107);
        internalCounters.push_back(3304);
        internalCounters.push_back(3501);

        p.DefinePublicCounter("CSThreadGroups", "ComputeShader", "Total number of thread groups.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4", "8ce3fc80-56b2-97f9-8e70-2e8c747cea68" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2913);
        internalCounters.push_back(3110);
        internalCounters.push_back(3307);
        internalCounters.push_back(3504);

        p.DefinePublicCounter("CSWavefronts", "ComputeShader", "The total number of wavefronts used for the CS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4", "42379c6e-369b-c237-8b25-cdb9cdc65c4d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(2910);
        internalCounters.push_back(3107);
        internalCounters.push_back(3304);
        internalCounters.push_back(3501);
        internalCounters.push_back(3653);
        internalCounters.push_back(3952);
        internalCounters.push_back(4251);
        internalCounters.push_back(4550);

        p.DefinePublicCounter("CSThreads", "ComputeShader", "The number of CS threads processed by the hardware.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),4,5,6,7,sum4,0,1,2,3,sum4,ifnotzero", "7a648013-6eac-2665-ac36-13c6f4ac9c26" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12037);
        internalCounters.push_back(12336);
        internalCounters.push_back(12635);
        internalCounters.push_back(12934);
        internalCounters.push_back(12015);
        internalCounters.push_back(12314);
        internalCounters.push_back(12613);
        internalCounters.push_back(12912);
        internalCounters.push_back(2910);
        internalCounters.push_back(3107);
        internalCounters.push_back(3304);
        internalCounters.push_back(3501);

        p.DefinePublicCounter("CSVALUInsts", "ComputeShader", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,ifnotzero", "376cb1cc-5a40-9d1d-404c-f1736c0c5084" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12100);
        internalCounters.push_back(12399);
        internalCounters.push_back(12698);
        internalCounters.push_back(12997);
        internalCounters.push_back(12092);
        internalCounters.push_back(12391);
        internalCounters.push_back(12690);
        internalCounters.push_back(12989);
        internalCounters.push_back(2910);
        internalCounters.push_back(3107);
        internalCounters.push_back(3304);
        internalCounters.push_back(3501);

        p.DefinePublicCounter("CSVALUUtilization", "ComputeShader", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,(64),*,/,(100),*,8,9,10,11,sum4,ifnotzero,(100),min", "4476879e-cdc0-d602-b24e-9b4a8d38438f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12041);
        internalCounters.push_back(12340);
        internalCounters.push_back(12639);
        internalCounters.push_back(12938);
        internalCounters.push_back(12015);
        internalCounters.push_back(12314);
        internalCounters.push_back(12613);
        internalCounters.push_back(12912);
        internalCounters.push_back(2910);
        internalCounters.push_back(3107);
        internalCounters.push_back(3304);
        internalCounters.push_back(3501);

        p.DefinePublicCounter("CSSALUInsts", "ComputeShader", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,ifnotzero", "eb211144-8136-ff86-e8bf-4d0493a904cb" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12039);
        internalCounters.push_back(12338);
        internalCounters.push_back(12637);
        internalCounters.push_back(12936);
        internalCounters.push_back(13444);
        internalCounters.push_back(13563);
        internalCounters.push_back(13682);
        internalCounters.push_back(13801);
        internalCounters.push_back(13920);
        internalCounters.push_back(14039);
        internalCounters.push_back(14158);
        internalCounters.push_back(14277);
        internalCounters.push_back(14396);
        internalCounters.push_back(14515);
        internalCounters.push_back(14634);
        internalCounters.push_back(14753);
        internalCounters.push_back(14872);
        internalCounters.push_back(14991);
        internalCounters.push_back(15110);
        internalCounters.push_back(15229);
        internalCounters.push_back(15348);
        internalCounters.push_back(15467);
        internalCounters.push_back(15586);
        internalCounters.push_back(15705);
        internalCounters.push_back(15824);
        internalCounters.push_back(15943);
        internalCounters.push_back(16062);
        internalCounters.push_back(16181);
        internalCounters.push_back(16300);
        internalCounters.push_back(16419);
        internalCounters.push_back(16538);
        internalCounters.push_back(16657);
        internalCounters.push_back(16776);
        internalCounters.push_back(16895);
        internalCounters.push_back(17014);
        internalCounters.push_back(17133);
        internalCounters.push_back(17252);
        internalCounters.push_back(17371);
        internalCounters.push_back(17490);
        internalCounters.push_back(17609);
        internalCounters.push_back(17728);
        internalCounters.push_back(17847);
        internalCounters.push_back(17966);
        internalCounters.push_back(18085);
        internalCounters.push_back(18204);
        internalCounters.push_back(18323);
        internalCounters.push_back(18442);
        internalCounters.push_back(18561);
        internalCounters.push_back(18680);
        internalCounters.push_back(18799);
        internalCounters.push_back(18918);
        internalCounters.push_back(19037);
        internalCounters.push_back(19156);
        internalCounters.push_back(19275);
        internalCounters.push_back(19394);
        internalCounters.push_back(19513);
        internalCounters.push_back(19632);
        internalCounters.push_back(19751);
        internalCounters.push_back(19870);
        internalCounters.push_back(19989);
        internalCounters.push_back(20108);
        internalCounters.push_back(20227);
        internalCounters.push_back(20346);
        internalCounters.push_back(20465);
        internalCounters.push_back(20584);
        internalCounters.push_back(20703);
        internalCounters.push_back(20822);
        internalCounters.push_back(20941);
        internalCounters.push_back(12015);
        internalCounters.push_back(12314);
        internalCounters.push_back(12613);
        internalCounters.push_back(12912);
        internalCounters.push_back(2910);
        internalCounters.push_back(3107);
        internalCounters.push_back(3304);
        internalCounters.push_back(3501);

        p.DefinePublicCounter("CSVFetchInsts", "ComputeShader", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,sum64,-,68,69,70,71,sum4,/,72,73,74,75,sum4,ifnotzero", "3e2829c0-6215-783b-c271-6d57ff2c520e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12042);
        internalCounters.push_back(12341);
        internalCounters.push_back(12640);
        internalCounters.push_back(12939);
        internalCounters.push_back(12015);
        internalCounters.push_back(12314);
        internalCounters.push_back(12613);
        internalCounters.push_back(12912);
        internalCounters.push_back(2910);
        internalCounters.push_back(3107);
        internalCounters.push_back(3304);
        internalCounters.push_back(3501);

        p.DefinePublicCounter("CSSFetchInsts", "ComputeShader", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,ifnotzero", "da09171c-6a0a-584f-fddc-dc5062d63a3e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12038);
        internalCounters.push_back(12337);
        internalCounters.push_back(12636);
        internalCounters.push_back(12935);
        internalCounters.push_back(13445);
        internalCounters.push_back(13564);
        internalCounters.push_back(13683);
        internalCounters.push_back(13802);
        internalCounters.push_back(13921);
        internalCounters.push_back(14040);
        internalCounters.push_back(14159);
        internalCounters.push_back(14278);
        internalCounters.push_back(14397);
        internalCounters.push_back(14516);
        internalCounters.push_back(14635);
        internalCounters.push_back(14754);
        internalCounters.push_back(14873);
        internalCounters.push_back(14992);
        internalCounters.push_back(15111);
        internalCounters.push_back(15230);
        internalCounters.push_back(15349);
        internalCounters.push_back(15468);
        internalCounters.push_back(15587);
        internalCounters.push_back(15706);
        internalCounters.push_back(15825);
        internalCounters.push_back(15944);
        internalCounters.push_back(16063);
        internalCounters.push_back(16182);
        internalCounters.push_back(16301);
        internalCounters.push_back(16420);
        internalCounters.push_back(16539);
        internalCounters.push_back(16658);
        internalCounters.push_back(16777);
        internalCounters.push_back(16896);
        internalCounters.push_back(17015);
        internalCounters.push_back(17134);
        internalCounters.push_back(17253);
        internalCounters.push_back(17372);
        internalCounters.push_back(17491);
        internalCounters.push_back(17610);
        internalCounters.push_back(17729);
        internalCounters.push_back(17848);
        internalCounters.push_back(17967);
        internalCounters.push_back(18086);
        internalCounters.push_back(18205);
        internalCounters.push_back(18324);
        internalCounters.push_back(18443);
        internalCounters.push_back(18562);
        internalCounters.push_back(18681);
        internalCounters.push_back(18800);
        internalCounters.push_back(18919);
        internalCounters.push_back(19038);
        internalCounters.push_back(19157);
        internalCounters.push_back(19276);
        internalCounters.push_back(19395);
        internalCounters.push_back(19514);
        internalCounters.push_back(19633);
        internalCounters.push_back(19752);
        internalCounters.push_back(19871);
        internalCounters.push_back(19990);
        internalCounters.push_back(20109);
        internalCounters.push_back(20228);
        internalCounters.push_back(20347);
        internalCounters.push_back(20466);
        internalCounters.push_back(20585);
        internalCounters.push_back(20704);
        internalCounters.push_back(20823);
        internalCounters.push_back(20942);
        internalCounters.push_back(12015);
        internalCounters.push_back(12314);
        internalCounters.push_back(12613);
        internalCounters.push_back(12912);
        internalCounters.push_back(2910);
        internalCounters.push_back(3107);
        internalCounters.push_back(3304);
        internalCounters.push_back(3501);

        p.DefinePublicCounter("CSVWriteInsts", "ComputeShader", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,sum64,-,68,69,70,71,sum4,/,72,73,74,75,sum4,ifnotzero", "43438c22-e910-b377-b767-b32902e0df0d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12043);
        internalCounters.push_back(12342);
        internalCounters.push_back(12641);
        internalCounters.push_back(12940);
        internalCounters.push_back(12044);
        internalCounters.push_back(12343);
        internalCounters.push_back(12642);
        internalCounters.push_back(12941);
        internalCounters.push_back(12015);
        internalCounters.push_back(12314);
        internalCounters.push_back(12613);
        internalCounters.push_back(12912);
        internalCounters.push_back(2910);
        internalCounters.push_back(3107);
        internalCounters.push_back(3304);
        internalCounters.push_back(3501);

        p.DefinePublicCounter("CSFlatVMemInsts", "ComputeShader", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,-,8,9,10,11,sum4,/,12,13,14,15,sum4,ifnotzero", "2570b477-13e3-f5b6-e6ff-7159373bc74d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12092);
        internalCounters.push_back(12391);
        internalCounters.push_back(12690);
        internalCounters.push_back(12989);
        internalCounters.push_back(49739);
        internalCounters.push_back(2910);
        internalCounters.push_back(3107);
        internalCounters.push_back(3304);
        internalCounters.push_back(3501);

        p.DefinePublicCounter("CSVALUBusy", "ComputeShader", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,(4),*,NUM_SIMDS,/,4,/,(100),*,5,6,7,8,sum4,ifnotzero", "f1e64815-f6a8-c277-d4f9-d054b443e205" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12092);
        internalCounters.push_back(12391);
        internalCounters.push_back(12690);
        internalCounters.push_back(12989);

        p.DefinePublicCounter("CSVALUBusyCycles", "ComputeShader", "Number of GPU cycles where vector ALU instructions are processed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/", "2d0d5852-2658-eb73-68d2-f23f7118c9c3" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12097);
        internalCounters.push_back(12396);
        internalCounters.push_back(12695);
        internalCounters.push_back(12994);
        internalCounters.push_back(49739);
        internalCounters.push_back(2910);
        internalCounters.push_back(3107);
        internalCounters.push_back(3304);
        internalCounters.push_back(3501);

        p.DefinePublicCounter("CSSALUBusy", "ComputeShader", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,4,/,(100),*,5,6,7,8,sum4,ifnotzero", "3fc35f4e-9882-94e3-6f5f-4e81cd97082a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12097);
        internalCounters.push_back(12396);
        internalCounters.push_back(12695);
        internalCounters.push_back(12994);

        p.DefinePublicCounter("CSSALUBusyCycles", "ComputeShader", "Number of GPU cycles where scalar ALU instructions are processed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "de58f8fc-8ed4-a799-648d-62ded7b1c4c4" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13358);
        internalCounters.push_back(13477);
        internalCounters.push_back(13596);
        internalCounters.push_back(13715);
        internalCounters.push_back(13834);
        internalCounters.push_back(13953);
        internalCounters.push_back(14072);
        internalCounters.push_back(14191);
        internalCounters.push_back(14310);
        internalCounters.push_back(14429);
        internalCounters.push_back(14548);
        internalCounters.push_back(14667);
        internalCounters.push_back(14786);
        internalCounters.push_back(14905);
        internalCounters.push_back(15024);
        internalCounters.push_back(15143);
        internalCounters.push_back(15262);
        internalCounters.push_back(15381);
        internalCounters.push_back(15500);
        internalCounters.push_back(15619);
        internalCounters.push_back(15738);
        internalCounters.push_back(15857);
        internalCounters.push_back(15976);
        internalCounters.push_back(16095);
        internalCounters.push_back(16214);
        internalCounters.push_back(16333);
        internalCounters.push_back(16452);
        internalCounters.push_back(16571);
        internalCounters.push_back(16690);
        internalCounters.push_back(16809);
        internalCounters.push_back(16928);
        internalCounters.push_back(17047);
        internalCounters.push_back(17166);
        internalCounters.push_back(17285);
        internalCounters.push_back(17404);
        internalCounters.push_back(17523);
        internalCounters.push_back(17642);
        internalCounters.push_back(17761);
        internalCounters.push_back(17880);
        internalCounters.push_back(17999);
        internalCounters.push_back(18118);
        internalCounters.push_back(18237);
        internalCounters.push_back(18356);
        internalCounters.push_back(18475);
        internalCounters.push_back(18594);
        internalCounters.push_back(18713);
        internalCounters.push_back(18832);
        internalCounters.push_back(18951);
        internalCounters.push_back(19070);
        internalCounters.push_back(19189);
        internalCounters.push_back(19308);
        internalCounters.push_back(19427);
        internalCounters.push_back(19546);
        internalCounters.push_back(19665);
        internalCounters.push_back(19784);
        internalCounters.push_back(19903);
        internalCounters.push_back(20022);
        internalCounters.push_back(20141);
        internalCounters.push_back(20260);
        internalCounters.push_back(20379);
        internalCounters.push_back(20498);
        internalCounters.push_back(20617);
        internalCounters.push_back(20736);
        internalCounters.push_back(20855);
        internalCounters.push_back(49739);
        internalCounters.push_back(2910);
        internalCounters.push_back(3107);
        internalCounters.push_back(3304);
        internalCounters.push_back(3501);

        p.DefinePublicCounter("CSMemUnitBusy", "ComputeShader", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,max64,64,/,(100),*,65,66,67,68,sum4,ifnotzero", "42ab96e1-0a24-96c8-c4ff-098fa267d78e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13358);
        internalCounters.push_back(13477);
        internalCounters.push_back(13596);
        internalCounters.push_back(13715);
        internalCounters.push_back(13834);
        internalCounters.push_back(13953);
        internalCounters.push_back(14072);
        internalCounters.push_back(14191);
        internalCounters.push_back(14310);
        internalCounters.push_back(14429);
        internalCounters.push_back(14548);
        internalCounters.push_back(14667);
        internalCounters.push_back(14786);
        internalCounters.push_back(14905);
        internalCounters.push_back(15024);
        internalCounters.push_back(15143);
        internalCounters.push_back(15262);
        internalCounters.push_back(15381);
        internalCounters.push_back(15500);
        internalCounters.push_back(15619);
        internalCounters.push_back(15738);
        internalCounters.push_back(15857);
        internalCounters.push_back(15976);
        internalCounters.push_back(16095);
        internalCounters.push_back(16214);
        internalCounters.push_back(16333);
        internalCounters.push_back(16452);
        internalCounters.push_back(16571);
        internalCounters.push_back(16690);
        internalCounters.push_back(16809);
        internalCounters.push_back(16928);
        internalCounters.push_back(17047);
        internalCounters.push_back(17166);
        internalCounters.push_back(17285);
        internalCounters.push_back(17404);
        internalCounters.push_back(17523);
        internalCounters.push_back(17642);
        internalCounters.push_back(17761);
        internalCounters.push_back(17880);
        internalCounters.push_back(17999);
        internalCounters.push_back(18118);
        internalCounters.push_back(18237);
        internalCounters.push_back(18356);
        internalCounters.push_back(18475);
        internalCounters.push_back(18594);
        internalCounters.push_back(18713);
        internalCounters.push_back(18832);
        internalCounters.push_back(18951);
        internalCounters.push_back(19070);
        internalCounters.push_back(19189);
        internalCounters.push_back(19308);
        internalCounters.push_back(19427);
        internalCounters.push_back(19546);
        internalCounters.push_back(19665);
        internalCounters.push_back(19784);
        internalCounters.push_back(19903);
        internalCounters.push_back(20022);
        internalCounters.push_back(20141);
        internalCounters.push_back(20260);
        internalCounters.push_back(20379);
        internalCounters.push_back(20498);
        internalCounters.push_back(20617);
        internalCounters.push_back(20736);
        internalCounters.push_back(20855);

        p.DefinePublicCounter("CSMemUnitBusyCycles", "ComputeShader", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,max64", "39d5687f-c727-7c0c-af82-bb711d3897ed" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(24482);
        internalCounters.push_back(24662);
        internalCounters.push_back(24842);
        internalCounters.push_back(25022);
        internalCounters.push_back(25202);
        internalCounters.push_back(25382);
        internalCounters.push_back(25562);
        internalCounters.push_back(25742);
        internalCounters.push_back(25922);
        internalCounters.push_back(26102);
        internalCounters.push_back(26282);
        internalCounters.push_back(26462);
        internalCounters.push_back(26642);
        internalCounters.push_back(26822);
        internalCounters.push_back(27002);
        internalCounters.push_back(27182);
        internalCounters.push_back(27362);
        internalCounters.push_back(27542);
        internalCounters.push_back(27722);
        internalCounters.push_back(27902);
        internalCounters.push_back(28082);
        internalCounters.push_back(28262);
        internalCounters.push_back(28442);
        internalCounters.push_back(28622);
        internalCounters.push_back(28802);
        internalCounters.push_back(28982);
        internalCounters.push_back(29162);
        internalCounters.push_back(29342);
        internalCounters.push_back(29522);
        internalCounters.push_back(29702);
        internalCounters.push_back(29882);
        internalCounters.push_back(30062);
        internalCounters.push_back(30242);
        internalCounters.push_back(30422);
        internalCounters.push_back(30602);
        internalCounters.push_back(30782);
        internalCounters.push_back(30962);
        internalCounters.push_back(31142);
        internalCounters.push_back(31322);
        internalCounters.push_back(31502);
        internalCounters.push_back(31682);
        internalCounters.push_back(31862);
        internalCounters.push_back(32042);
        internalCounters.push_back(32222);
        internalCounters.push_back(32402);
        internalCounters.push_back(32582);
        internalCounters.push_back(32762);
        internalCounters.push_back(32942);
        internalCounters.push_back(33122);
        internalCounters.push_back(33302);
        internalCounters.push_back(33482);
        internalCounters.push_back(33662);
        internalCounters.push_back(33842);
        internalCounters.push_back(34022);
        internalCounters.push_back(34202);
        internalCounters.push_back(34382);
        internalCounters.push_back(34562);
        internalCounters.push_back(34742);
        internalCounters.push_back(34922);
        internalCounters.push_back(35102);
        internalCounters.push_back(35282);
        internalCounters.push_back(35462);
        internalCounters.push_back(35642);
        internalCounters.push_back(35822);
        internalCounters.push_back(49739);
        internalCounters.push_back(2910);
        internalCounters.push_back(3107);
        internalCounters.push_back(3304);
        internalCounters.push_back(3501);

        p.DefinePublicCounter("CSMemUnitStalled", "ComputeShader", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,max64,64,/,(100),*,65,66,67,68,sum4,ifnotzero", "f18e8679-1511-d533-d9ee-4365197f7d0c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(24482);
        internalCounters.push_back(24662);
        internalCounters.push_back(24842);
        internalCounters.push_back(25022);
        internalCounters.push_back(25202);
        internalCounters.push_back(25382);
        internalCounters.push_back(25562);
        internalCounters.push_back(25742);
        internalCounters.push_back(25922);
        internalCounters.push_back(26102);
        internalCounters.push_back(26282);
        internalCounters.push_back(26462);
        internalCounters.push_back(26642);
        internalCounters.push_back(26822);
        internalCounters.push_back(27002);
        internalCounters.push_back(27182);
        internalCounters.push_back(27362);
        internalCounters.push_back(27542);
        internalCounters.push_back(27722);
        internalCounters.push_back(27902);
        internalCounters.push_back(28082);
        internalCounters.push_back(28262);
        internalCounters.push_back(28442);
        internalCounters.push_back(28622);
        internalCounters.push_back(28802);
        internalCounters.push_back(28982);
        internalCounters.push_back(29162);
        internalCounters.push_back(29342);
        internalCounters.push_back(29522);
        internalCounters.push_back(29702);
        internalCounters.push_back(29882);
        internalCounters.push_back(30062);
        internalCounters.push_back(30242);
        internalCounters.push_back(30422);
        internalCounters.push_back(30602);
        internalCounters.push_back(30782);
        internalCounters.push_back(30962);
        internalCounters.push_back(31142);
        internalCounters.push_back(31322);
        internalCounters.push_back(31502);
        internalCounters.push_back(31682);
        internalCounters.push_back(31862);
        internalCounters.push_back(32042);
        internalCounters.push_back(32222);
        internalCounters.push_back(32402);
        internalCounters.push_back(32582);
        internalCounters.push_back(32762);
        internalCounters.push_back(32942);
        internalCounters.push_back(33122);
        internalCounters.push_back(33302);
        internalCounters.push_back(33482);
        internalCounters.push_back(33662);
        internalCounters.push_back(33842);
        internalCounters.push_back(34022);
        internalCounters.push_back(34202);
        internalCounters.push_back(34382);
        internalCounters.push_back(34562);
        internalCounters.push_back(34742);
        internalCounters.push_back(34922);
        internalCounters.push_back(35102);
        internalCounters.push_back(35282);
        internalCounters.push_back(35462);
        internalCounters.push_back(35642);
        internalCounters.push_back(35822);

        p.DefinePublicCounter("CSMemUnitStalledCycles", "ComputeShader", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,max64", "51991c84-ed2b-bf31-c4ab-8f8e9eb8f29f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(36027);
        internalCounters.push_back(36219);
        internalCounters.push_back(36411);
        internalCounters.push_back(36603);
        internalCounters.push_back(36795);
        internalCounters.push_back(36987);
        internalCounters.push_back(37179);
        internalCounters.push_back(37371);
        internalCounters.push_back(37563);
        internalCounters.push_back(37755);
        internalCounters.push_back(37947);
        internalCounters.push_back(38139);
        internalCounters.push_back(38331);
        internalCounters.push_back(38523);
        internalCounters.push_back(38715);
        internalCounters.push_back(38907);

        p.DefinePublicCounter("CSWriteUnitStalledCycles", "ComputeShader", "Number of GPU cycles the write unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "be164c60-5e48-acac-9622-29616d09aa9a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12046);
        internalCounters.push_back(12345);
        internalCounters.push_back(12644);
        internalCounters.push_back(12943);
        internalCounters.push_back(12015);
        internalCounters.push_back(12314);
        internalCounters.push_back(12613);
        internalCounters.push_back(12912);
        internalCounters.push_back(2910);
        internalCounters.push_back(3107);
        internalCounters.push_back(3304);
        internalCounters.push_back(3501);

        p.DefinePublicCounter("CSGDSInsts", "ComputeShader", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,ifnotzero", "2a867f3e-4a37-ad16-55d1-f03d74707819" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12045);
        internalCounters.push_back(12344);
        internalCounters.push_back(12643);
        internalCounters.push_back(12942);
        internalCounters.push_back(12043);
        internalCounters.push_back(12342);
        internalCounters.push_back(12641);
        internalCounters.push_back(12940);
        internalCounters.push_back(12015);
        internalCounters.push_back(12314);
        internalCounters.push_back(12613);
        internalCounters.push_back(12912);
        internalCounters.push_back(2910);
        internalCounters.push_back(3107);
        internalCounters.push_back(3304);
        internalCounters.push_back(3501);

        p.DefinePublicCounter("CSLDSInsts", "ComputeShader", "The average number of LDS read/write instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,-,8,9,10,11,sum4,/,12,13,14,15,sum4,ifnotzero", "61b0b351-7e06-ef8e-a8e0-7a9e3200a836" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12044);
        internalCounters.push_back(12343);
        internalCounters.push_back(12642);
        internalCounters.push_back(12941);
        internalCounters.push_back(12015);
        internalCounters.push_back(12314);
        internalCounters.push_back(12613);
        internalCounters.push_back(12912);
        internalCounters.push_back(2910);
        internalCounters.push_back(3107);
        internalCounters.push_back(3304);
        internalCounters.push_back(3501);

        p.DefinePublicCounter("CSFlatLDSInsts", "ComputeShader", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,ifnotzero", "99672cda-de2b-014c-482e-cf73b90068d5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12072);
        internalCounters.push_back(12371);
        internalCounters.push_back(12670);
        internalCounters.push_back(12969);
        internalCounters.push_back(12015);
        internalCounters.push_back(12314);
        internalCounters.push_back(12613);
        internalCounters.push_back(12912);
        internalCounters.push_back(49739);
        internalCounters.push_back(2910);
        internalCounters.push_back(3107);
        internalCounters.push_back(3304);
        internalCounters.push_back(3501);

        p.DefinePublicCounter("CSALUStalledByLDS", "ComputeShader", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,/,NUM_SHADER_ENGINES,/,(100),*,9,10,11,12,sum4,ifnotzero", "6dc4f1c2-bad0-c9ff-156e-883b319a752a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12072);
        internalCounters.push_back(12371);
        internalCounters.push_back(12670);
        internalCounters.push_back(12969);

        p.DefinePublicCounter("CSALUStalledByLDSCycles", "ComputeShader", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,NUM_SHADER_ENGINES,/", "8f3d5f25-2159-0374-fafe-e26a7799b6c8" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12108);
        internalCounters.push_back(12407);
        internalCounters.push_back(12706);
        internalCounters.push_back(13005);
        internalCounters.push_back(49739);
        internalCounters.push_back(2910);
        internalCounters.push_back(3107);
        internalCounters.push_back(3304);
        internalCounters.push_back(3501);

        p.DefinePublicCounter("CSLDSBankConflict", "ComputeShader", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "(0),0,1,2,3,sum4,4,/,NUM_SIMDS,/,(100),*,5,6,7,8,sum4,ifnotzero", "1065ee10-2e41-ea41-1eb3-b61b491752f4" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12108);
        internalCounters.push_back(12407);
        internalCounters.push_back(12706);
        internalCounters.push_back(13005);

        p.DefinePublicCounter("CSLDSBankConflictCycles", "ComputeShader", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,NUM_SIMDS,/", "1fd1adf3-c51e-94fd-083e-c482a0a0809e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13358);
        internalCounters.push_back(13477);
        internalCounters.push_back(13596);
        internalCounters.push_back(13715);
        internalCounters.push_back(13834);
        internalCounters.push_back(13953);
        internalCounters.push_back(14072);
        internalCounters.push_back(14191);
        internalCounters.push_back(14310);
        internalCounters.push_back(14429);
        internalCounters.push_back(14548);
        internalCounters.push_back(14667);
        internalCounters.push_back(14786);
        internalCounters.push_back(14905);
        internalCounters.push_back(15024);
        internalCounters.push_back(15143);
        internalCounters.push_back(15262);
        internalCounters.push_back(15381);
        internalCounters.push_back(15500);
        internalCounters.push_back(15619);
        internalCounters.push_back(15738);
        internalCounters.push_back(15857);
        internalCounters.push_back(15976);
        internalCounters.push_back(16095);
        internalCounters.push_back(16214);
        internalCounters.push_back(16333);
        internalCounters.push_back(16452);
        internalCounters.push_back(16571);
        internalCounters.push_back(16690);
        internalCounters.push_back(16809);
        internalCounters.push_back(16928);
        internalCounters.push_back(17047);
        internalCounters.push_back(17166);
        internalCounters.push_back(17285);
        internalCounters.push_back(17404);
        internalCounters.push_back(17523);
        internalCounters.push_back(17642);
        internalCounters.push_back(17761);
        internalCounters.push_back(17880);
        internalCounters.push_back(17999);
        internalCounters.push_back(18118);
        internalCounters.push_back(18237);
        internalCounters.push_back(18356);
        internalCounters.push_back(18475);
        internalCounters.push_back(18594);
        internalCounters.push_back(18713);
        internalCounters.push_back(18832);
        internalCounters.push_back(18951);
        internalCounters.push_back(19070);
        internalCounters.push_back(19189);
        internalCounters.push_back(19308);
        internalCounters.push_back(19427);
        internalCounters.push_back(19546);
        internalCounters.push_back(19665);
        internalCounters.push_back(19784);
        internalCounters.push_back(19903);
        internalCounters.push_back(20022);
        internalCounters.push_back(20141);
        internalCounters.push_back(20260);
        internalCounters.push_back(20379);
        internalCounters.push_back(20498);
        internalCounters.push_back(20617);
        internalCounters.push_back(20736);
        internalCounters.push_back(20855);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("TexUnitBusy", "Timing", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,max64,64,/,(100),*", "36afb8d9-42fc-aafe-66c5-449542153b2c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13358);
        internalCounters.push_back(13477);
        internalCounters.push_back(13596);
        internalCounters.push_back(13715);
        internalCounters.push_back(13834);
        internalCounters.push_back(13953);
        internalCounters.push_back(14072);
        internalCounters.push_back(14191);
        internalCounters.push_back(14310);
        internalCounters.push_back(14429);
        internalCounters.push_back(14548);
        internalCounters.push_back(14667);
        internalCounters.push_back(14786);
        internalCounters.push_back(14905);
        internalCounters.push_back(15024);
        internalCounters.push_back(15143);
        internalCounters.push_back(15262);
        internalCounters.push_back(15381);
        internalCounters.push_back(15500);
        internalCounters.push_back(15619);
        internalCounters.push_back(15738);
        internalCounters.push_back(15857);
        internalCounters.push_back(15976);
        internalCounters.push_back(16095);
        internalCounters.push_back(16214);
        internalCounters.push_back(16333);
        internalCounters.push_back(16452);
        internalCounters.push_back(16571);
        internalCounters.push_back(16690);
        internalCounters.push_back(16809);
        internalCounters.push_back(16928);
        internalCounters.push_back(17047);
        internalCounters.push_back(17166);
        internalCounters.push_back(17285);
        internalCounters.push_back(17404);
        internalCounters.push_back(17523);
        internalCounters.push_back(17642);
        internalCounters.push_back(17761);
        internalCounters.push_back(17880);
        internalCounters.push_back(17999);
        internalCounters.push_back(18118);
        internalCounters.push_back(18237);
        internalCounters.push_back(18356);
        internalCounters.push_back(18475);
        internalCounters.push_back(18594);
        internalCounters.push_back(18713);
        internalCounters.push_back(18832);
        internalCounters.push_back(18951);
        internalCounters.push_back(19070);
        internalCounters.push_back(19189);
        internalCounters.push_back(19308);
        internalCounters.push_back(19427);
        internalCounters.push_back(19546);
        internalCounters.push_back(19665);
        internalCounters.push_back(19784);
        internalCounters.push_back(19903);
        internalCounters.push_back(20022);
        internalCounters.push_back(20141);
        internalCounters.push_back(20260);
        internalCounters.push_back(20379);
        internalCounters.push_back(20498);
        internalCounters.push_back(20617);
        internalCounters.push_back(20736);
        internalCounters.push_back(20855);

        p.DefinePublicCounter("TexUnitBusyCycles", "Timing", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,max64", "c68761f2-248c-4f39-6528-c308b1c0807c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13412);
        internalCounters.push_back(13531);
        internalCounters.push_back(13650);
        internalCounters.push_back(13769);
        internalCounters.push_back(13888);
        internalCounters.push_back(14007);
        internalCounters.push_back(14126);
        internalCounters.push_back(14245);
        internalCounters.push_back(14364);
        internalCounters.push_back(14483);
        internalCounters.push_back(14602);
        internalCounters.push_back(14721);
        internalCounters.push_back(14840);
        internalCounters.push_back(14959);
        internalCounters.push_back(15078);
        internalCounters.push_back(15197);
        internalCounters.push_back(15316);
        internalCounters.push_back(15435);
        internalCounters.push_back(15554);
        internalCounters.push_back(15673);
        internalCounters.push_back(15792);
        internalCounters.push_back(15911);
        internalCounters.push_back(16030);
        internalCounters.push_back(16149);
        internalCounters.push_back(16268);
        internalCounters.push_back(16387);
        internalCounters.push_back(16506);
        internalCounters.push_back(16625);
        internalCounters.push_back(16744);
        internalCounters.push_back(16863);
        internalCounters.push_back(16982);
        internalCounters.push_back(17101);
        internalCounters.push_back(17220);
        internalCounters.push_back(17339);
        internalCounters.push_back(17458);
        internalCounters.push_back(17577);
        internalCounters.push_back(17696);
        internalCounters.push_back(17815);
        internalCounters.push_back(17934);
        internalCounters.push_back(18053);
        internalCounters.push_back(18172);
        internalCounters.push_back(18291);
        internalCounters.push_back(18410);
        internalCounters.push_back(18529);
        internalCounters.push_back(18648);
        internalCounters.push_back(18767);
        internalCounters.push_back(18886);
        internalCounters.push_back(19005);
        internalCounters.push_back(19124);
        internalCounters.push_back(19243);
        internalCounters.push_back(19362);
        internalCounters.push_back(19481);
        internalCounters.push_back(19600);
        internalCounters.push_back(19719);
        internalCounters.push_back(19838);
        internalCounters.push_back(19957);
        internalCounters.push_back(20076);
        internalCounters.push_back(20195);
        internalCounters.push_back(20314);
        internalCounters.push_back(20433);
        internalCounters.push_back(20552);
        internalCounters.push_back(20671);
        internalCounters.push_back(20790);
        internalCounters.push_back(20909);
        internalCounters.push_back(13411);
        internalCounters.push_back(13530);
        internalCounters.push_back(13649);
        internalCounters.push_back(13768);
        internalCounters.push_back(13887);
        internalCounters.push_back(14006);
        internalCounters.push_back(14125);
        internalCounters.push_back(14244);
        internalCounters.push_back(14363);
        internalCounters.push_back(14482);
        internalCounters.push_back(14601);
        internalCounters.push_back(14720);
        internalCounters.push_back(14839);
        internalCounters.push_back(14958);
        internalCounters.push_back(15077);
        internalCounters.push_back(15196);
        internalCounters.push_back(15315);
        internalCounters.push_back(15434);
        internalCounters.push_back(15553);
        internalCounters.push_back(15672);
        internalCounters.push_back(15791);
        internalCounters.push_back(15910);
        internalCounters.push_back(16029);
        internalCounters.push_back(16148);
        internalCounters.push_back(16267);
        internalCounters.push_back(16386);
        internalCounters.push_back(16505);
        internalCounters.push_back(16624);
        internalCounters.push_back(16743);
        internalCounters.push_back(16862);
        internalCounters.push_back(16981);
        internalCounters.push_back(17100);
        internalCounters.push_back(17219);
        internalCounters.push_back(17338);
        internalCounters.push_back(17457);
        internalCounters.push_back(17576);
        internalCounters.push_back(17695);
        internalCounters.push_back(17814);
        internalCounters.push_back(17933);
        internalCounters.push_back(18052);
        internalCounters.push_back(18171);
        internalCounters.push_back(18290);
        internalCounters.push_back(18409);
        internalCounters.push_back(18528);
        internalCounters.push_back(18647);
        internalCounters.push_back(18766);
        internalCounters.push_back(18885);
        internalCounters.push_back(19004);
        internalCounters.push_back(19123);
        internalCounters.push_back(19242);
        internalCounters.push_back(19361);
        internalCounters.push_back(19480);
        internalCounters.push_back(19599);
        internalCounters.push_back(19718);
        internalCounters.push_back(19837);
        internalCounters.push_back(19956);
        internalCounters.push_back(20075);
        internalCounters.push_back(20194);
        internalCounters.push_back(20313);
        internalCounters.push_back(20432);
        internalCounters.push_back(20551);
        internalCounters.push_back(20670);
        internalCounters.push_back(20789);
        internalCounters.push_back(20908);

        p.DefinePublicCounter("TexTriFilteringPct", "TextureUnit", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum64,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,+,/,(100),*", "1affc3c8-b917-5c81-622b-7004527208ae" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13412);
        internalCounters.push_back(13531);
        internalCounters.push_back(13650);
        internalCounters.push_back(13769);
        internalCounters.push_back(13888);
        internalCounters.push_back(14007);
        internalCounters.push_back(14126);
        internalCounters.push_back(14245);
        internalCounters.push_back(14364);
        internalCounters.push_back(14483);
        internalCounters.push_back(14602);
        internalCounters.push_back(14721);
        internalCounters.push_back(14840);
        internalCounters.push_back(14959);
        internalCounters.push_back(15078);
        internalCounters.push_back(15197);
        internalCounters.push_back(15316);
        internalCounters.push_back(15435);
        internalCounters.push_back(15554);
        internalCounters.push_back(15673);
        internalCounters.push_back(15792);
        internalCounters.push_back(15911);
        internalCounters.push_back(16030);
        internalCounters.push_back(16149);
        internalCounters.push_back(16268);
        internalCounters.push_back(16387);
        internalCounters.push_back(16506);
        internalCounters.push_back(16625);
        internalCounters.push_back(16744);
        internalCounters.push_back(16863);
        internalCounters.push_back(16982);
        internalCounters.push_back(17101);
        internalCounters.push_back(17220);
        internalCounters.push_back(17339);
        internalCounters.push_back(17458);
        internalCounters.push_back(17577);
        internalCounters.push_back(17696);
        internalCounters.push_back(17815);
        internalCounters.push_back(17934);
        internalCounters.push_back(18053);
        internalCounters.push_back(18172);
        internalCounters.push_back(18291);
        internalCounters.push_back(18410);
        internalCounters.push_back(18529);
        internalCounters.push_back(18648);
        internalCounters.push_back(18767);
        internalCounters.push_back(18886);
        internalCounters.push_back(19005);
        internalCounters.push_back(19124);
        internalCounters.push_back(19243);
        internalCounters.push_back(19362);
        internalCounters.push_back(19481);
        internalCounters.push_back(19600);
        internalCounters.push_back(19719);
        internalCounters.push_back(19838);
        internalCounters.push_back(19957);
        internalCounters.push_back(20076);
        internalCounters.push_back(20195);
        internalCounters.push_back(20314);
        internalCounters.push_back(20433);
        internalCounters.push_back(20552);
        internalCounters.push_back(20671);
        internalCounters.push_back(20790);
        internalCounters.push_back(20909);

        p.DefinePublicCounter("TexTriFilteringCount", "TextureUnit", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64", "5785b3a1-a513-18db-4b1c-bdeef75bb2b6" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13411);
        internalCounters.push_back(13530);
        internalCounters.push_back(13649);
        internalCounters.push_back(13768);
        internalCounters.push_back(13887);
        internalCounters.push_back(14006);
        internalCounters.push_back(14125);
        internalCounters.push_back(14244);
        internalCounters.push_back(14363);
        internalCounters.push_back(14482);
        internalCounters.push_back(14601);
        internalCounters.push_back(14720);
        internalCounters.push_back(14839);
        internalCounters.push_back(14958);
        internalCounters.push_back(15077);
        internalCounters.push_back(15196);
        internalCounters.push_back(15315);
        internalCounters.push_back(15434);
        internalCounters.push_back(15553);
        internalCounters.push_back(15672);
        internalCounters.push_back(15791);
        internalCounters.push_back(15910);
        internalCounters.push_back(16029);
        internalCounters.push_back(16148);
        internalCounters.push_back(16267);
        internalCounters.push_back(16386);
        internalCounters.push_back(16505);
        internalCounters.push_back(16624);
        internalCounters.push_back(16743);
        internalCounters.push_back(16862);
        internalCounters.push_back(16981);
        internalCounters.push_back(17100);
        internalCounters.push_back(17219);
        internalCounters.push_back(17338);
        internalCounters.push_back(17457);
        internalCounters.push_back(17576);
        internalCounters.push_back(17695);
        internalCounters.push_back(17814);
        internalCounters.push_back(17933);
        internalCounters.push_back(18052);
        internalCounters.push_back(18171);
        internalCounters.push_back(18290);
        internalCounters.push_back(18409);
        internalCounters.push_back(18528);
        internalCounters.push_back(18647);
        internalCounters.push_back(18766);
        internalCounters.push_back(18885);
        internalCounters.push_back(19004);
        internalCounters.push_back(19123);
        internalCounters.push_back(19242);
        internalCounters.push_back(19361);
        internalCounters.push_back(19480);
        internalCounters.push_back(19599);
        internalCounters.push_back(19718);
        internalCounters.push_back(19837);
        internalCounters.push_back(19956);
        internalCounters.push_back(20075);
        internalCounters.push_back(20194);
        internalCounters.push_back(20313);
        internalCounters.push_back(20432);
        internalCounters.push_back(20551);
        internalCounters.push_back(20670);
        internalCounters.push_back(20789);
        internalCounters.push_back(20908);

        p.DefinePublicCounter("NoTexTriFilteringCount", "TextureUnit", "Count of pixels that did not receive trilinear filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64", "179da29a-81af-c06e-ce8c-a0a731ea030d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13414);
        internalCounters.push_back(13533);
        internalCounters.push_back(13652);
        internalCounters.push_back(13771);
        internalCounters.push_back(13890);
        internalCounters.push_back(14009);
        internalCounters.push_back(14128);
        internalCounters.push_back(14247);
        internalCounters.push_back(14366);
        internalCounters.push_back(14485);
        internalCounters.push_back(14604);
        internalCounters.push_back(14723);
        internalCounters.push_back(14842);
        internalCounters.push_back(14961);
        internalCounters.push_back(15080);
        internalCounters.push_back(15199);
        internalCounters.push_back(15318);
        internalCounters.push_back(15437);
        internalCounters.push_back(15556);
        internalCounters.push_back(15675);
        internalCounters.push_back(15794);
        internalCounters.push_back(15913);
        internalCounters.push_back(16032);
        internalCounters.push_back(16151);
        internalCounters.push_back(16270);
        internalCounters.push_back(16389);
        internalCounters.push_back(16508);
        internalCounters.push_back(16627);
        internalCounters.push_back(16746);
        internalCounters.push_back(16865);
        internalCounters.push_back(16984);
        internalCounters.push_back(17103);
        internalCounters.push_back(17222);
        internalCounters.push_back(17341);
        internalCounters.push_back(17460);
        internalCounters.push_back(17579);
        internalCounters.push_back(17698);
        internalCounters.push_back(17817);
        internalCounters.push_back(17936);
        internalCounters.push_back(18055);
        internalCounters.push_back(18174);
        internalCounters.push_back(18293);
        internalCounters.push_back(18412);
        internalCounters.push_back(18531);
        internalCounters.push_back(18650);
        internalCounters.push_back(18769);
        internalCounters.push_back(18888);
        internalCounters.push_back(19007);
        internalCounters.push_back(19126);
        internalCounters.push_back(19245);
        internalCounters.push_back(19364);
        internalCounters.push_back(19483);
        internalCounters.push_back(19602);
        internalCounters.push_back(19721);
        internalCounters.push_back(19840);
        internalCounters.push_back(19959);
        internalCounters.push_back(20078);
        internalCounters.push_back(20197);
        internalCounters.push_back(20316);
        internalCounters.push_back(20435);
        internalCounters.push_back(20554);
        internalCounters.push_back(20673);
        internalCounters.push_back(20792);
        internalCounters.push_back(20911);
        internalCounters.push_back(13413);
        internalCounters.push_back(13532);
        internalCounters.push_back(13651);
        internalCounters.push_back(13770);
        internalCounters.push_back(13889);
        internalCounters.push_back(14008);
        internalCounters.push_back(14127);
        internalCounters.push_back(14246);
        internalCounters.push_back(14365);
        internalCounters.push_back(14484);
        internalCounters.push_back(14603);
        internalCounters.push_back(14722);
        internalCounters.push_back(14841);
        internalCounters.push_back(14960);
        internalCounters.push_back(15079);
        internalCounters.push_back(15198);
        internalCounters.push_back(15317);
        internalCounters.push_back(15436);
        internalCounters.push_back(15555);
        internalCounters.push_back(15674);
        internalCounters.push_back(15793);
        internalCounters.push_back(15912);
        internalCounters.push_back(16031);
        internalCounters.push_back(16150);
        internalCounters.push_back(16269);
        internalCounters.push_back(16388);
        internalCounters.push_back(16507);
        internalCounters.push_back(16626);
        internalCounters.push_back(16745);
        internalCounters.push_back(16864);
        internalCounters.push_back(16983);
        internalCounters.push_back(17102);
        internalCounters.push_back(17221);
        internalCounters.push_back(17340);
        internalCounters.push_back(17459);
        internalCounters.push_back(17578);
        internalCounters.push_back(17697);
        internalCounters.push_back(17816);
        internalCounters.push_back(17935);
        internalCounters.push_back(18054);
        internalCounters.push_back(18173);
        internalCounters.push_back(18292);
        internalCounters.push_back(18411);
        internalCounters.push_back(18530);
        internalCounters.push_back(18649);
        internalCounters.push_back(18768);
        internalCounters.push_back(18887);
        internalCounters.push_back(19006);
        internalCounters.push_back(19125);
        internalCounters.push_back(19244);
        internalCounters.push_back(19363);
        internalCounters.push_back(19482);
        internalCounters.push_back(19601);
        internalCounters.push_back(19720);
        internalCounters.push_back(19839);
        internalCounters.push_back(19958);
        internalCounters.push_back(20077);
        internalCounters.push_back(20196);
        internalCounters.push_back(20315);
        internalCounters.push_back(20434);
        internalCounters.push_back(20553);
        internalCounters.push_back(20672);
        internalCounters.push_back(20791);
        internalCounters.push_back(20910);

        p.DefinePublicCounter("TexVolFilteringPct", "TextureUnit", "Percentage of pixels that received volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum64,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,+,/,(100),*", "b5ff6bed-3178-aee4-42dd-c74391c02a2d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13414);
        internalCounters.push_back(13533);
        internalCounters.push_back(13652);
        internalCounters.push_back(13771);
        internalCounters.push_back(13890);
        internalCounters.push_back(14009);
        internalCounters.push_back(14128);
        internalCounters.push_back(14247);
        internalCounters.push_back(14366);
        internalCounters.push_back(14485);
        internalCounters.push_back(14604);
        internalCounters.push_back(14723);
        internalCounters.push_back(14842);
        internalCounters.push_back(14961);
        internalCounters.push_back(15080);
        internalCounters.push_back(15199);
        internalCounters.push_back(15318);
        internalCounters.push_back(15437);
        internalCounters.push_back(15556);
        internalCounters.push_back(15675);
        internalCounters.push_back(15794);
        internalCounters.push_back(15913);
        internalCounters.push_back(16032);
        internalCounters.push_back(16151);
        internalCounters.push_back(16270);
        internalCounters.push_back(16389);
        internalCounters.push_back(16508);
        internalCounters.push_back(16627);
        internalCounters.push_back(16746);
        internalCounters.push_back(16865);
        internalCounters.push_back(16984);
        internalCounters.push_back(17103);
        internalCounters.push_back(17222);
        internalCounters.push_back(17341);
        internalCounters.push_back(17460);
        internalCounters.push_back(17579);
        internalCounters.push_back(17698);
        internalCounters.push_back(17817);
        internalCounters.push_back(17936);
        internalCounters.push_back(18055);
        internalCounters.push_back(18174);
        internalCounters.push_back(18293);
        internalCounters.push_back(18412);
        internalCounters.push_back(18531);
        internalCounters.push_back(18650);
        internalCounters.push_back(18769);
        internalCounters.push_back(18888);
        internalCounters.push_back(19007);
        internalCounters.push_back(19126);
        internalCounters.push_back(19245);
        internalCounters.push_back(19364);
        internalCounters.push_back(19483);
        internalCounters.push_back(19602);
        internalCounters.push_back(19721);
        internalCounters.push_back(19840);
        internalCounters.push_back(19959);
        internalCounters.push_back(20078);
        internalCounters.push_back(20197);
        internalCounters.push_back(20316);
        internalCounters.push_back(20435);
        internalCounters.push_back(20554);
        internalCounters.push_back(20673);
        internalCounters.push_back(20792);
        internalCounters.push_back(20911);

        p.DefinePublicCounter("TexVolFilteringCount", "TextureUnit", "Count of pixels that received volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64", "4bddc587-d589-8128-e18c-762eab2c871f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13413);
        internalCounters.push_back(13532);
        internalCounters.push_back(13651);
        internalCounters.push_back(13770);
        internalCounters.push_back(13889);
        internalCounters.push_back(14008);
        internalCounters.push_back(14127);
        internalCounters.push_back(14246);
        internalCounters.push_back(14365);
        internalCounters.push_back(14484);
        internalCounters.push_back(14603);
        internalCounters.push_back(14722);
        internalCounters.push_back(14841);
        internalCounters.push_back(14960);
        internalCounters.push_back(15079);
        internalCounters.push_back(15198);
        internalCounters.push_back(15317);
        internalCounters.push_back(15436);
        internalCounters.push_back(15555);
        internalCounters.push_back(15674);
        internalCounters.push_back(15793);
        internalCounters.push_back(15912);
        internalCounters.push_back(16031);
        internalCounters.push_back(16150);
        internalCounters.push_back(16269);
        internalCounters.push_back(16388);
        internalCounters.push_back(16507);
        internalCounters.push_back(16626);
        internalCounters.push_back(16745);
        internalCounters.push_back(16864);
        internalCounters.push_back(16983);
        internalCounters.push_back(17102);
        internalCounters.push_back(17221);
        internalCounters.push_back(17340);
        internalCounters.push_back(17459);
        internalCounters.push_back(17578);
        internalCounters.push_back(17697);
        internalCounters.push_back(17816);
        internalCounters.push_back(17935);
        internalCounters.push_back(18054);
        internalCounters.push_back(18173);
        internalCounters.push_back(18292);
        internalCounters.push_back(18411);
        internalCounters.push_back(18530);
        internalCounters.push_back(18649);
        internalCounters.push_back(18768);
        internalCounters.push_back(18887);
        internalCounters.push_back(19006);
        internalCounters.push_back(19125);
        internalCounters.push_back(19244);
        internalCounters.push_back(19363);
        internalCounters.push_back(19482);
        internalCounters.push_back(19601);
        internalCounters.push_back(19720);
        internalCounters.push_back(19839);
        internalCounters.push_back(19958);
        internalCounters.push_back(20077);
        internalCounters.push_back(20196);
        internalCounters.push_back(20315);
        internalCounters.push_back(20434);
        internalCounters.push_back(20553);
        internalCounters.push_back(20672);
        internalCounters.push_back(20791);
        internalCounters.push_back(20910);

        p.DefinePublicCounter("NoTexVolFilteringCount", "TextureUnit", "Count of pixels that did not receive volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64", "9fe1a854-17c6-9d26-b2b9-80610cd5827d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13432);
        internalCounters.push_back(13551);
        internalCounters.push_back(13670);
        internalCounters.push_back(13789);
        internalCounters.push_back(13908);
        internalCounters.push_back(14027);
        internalCounters.push_back(14146);
        internalCounters.push_back(14265);
        internalCounters.push_back(14384);
        internalCounters.push_back(14503);
        internalCounters.push_back(14622);
        internalCounters.push_back(14741);
        internalCounters.push_back(14860);
        internalCounters.push_back(14979);
        internalCounters.push_back(15098);
        internalCounters.push_back(15217);
        internalCounters.push_back(15336);
        internalCounters.push_back(15455);
        internalCounters.push_back(15574);
        internalCounters.push_back(15693);
        internalCounters.push_back(15812);
        internalCounters.push_back(15931);
        internalCounters.push_back(16050);
        internalCounters.push_back(16169);
        internalCounters.push_back(16288);
        internalCounters.push_back(16407);
        internalCounters.push_back(16526);
        internalCounters.push_back(16645);
        internalCounters.push_back(16764);
        internalCounters.push_back(16883);
        internalCounters.push_back(17002);
        internalCounters.push_back(17121);
        internalCounters.push_back(17240);
        internalCounters.push_back(17359);
        internalCounters.push_back(17478);
        internalCounters.push_back(17597);
        internalCounters.push_back(17716);
        internalCounters.push_back(17835);
        internalCounters.push_back(17954);
        internalCounters.push_back(18073);
        internalCounters.push_back(18192);
        internalCounters.push_back(18311);
        internalCounters.push_back(18430);
        internalCounters.push_back(18549);
        internalCounters.push_back(18668);
        internalCounters.push_back(18787);
        internalCounters.push_back(18906);
        internalCounters.push_back(19025);
        internalCounters.push_back(19144);
        internalCounters.push_back(19263);
        internalCounters.push_back(19382);
        internalCounters.push_back(19501);
        internalCounters.push_back(19620);
        internalCounters.push_back(19739);
        internalCounters.push_back(19858);
        internalCounters.push_back(19977);
        internalCounters.push_back(20096);
        internalCounters.push_back(20215);
        internalCounters.push_back(20334);
        internalCounters.push_back(20453);
        internalCounters.push_back(20572);
        internalCounters.push_back(20691);
        internalCounters.push_back(20810);
        internalCounters.push_back(20929);
        internalCounters.push_back(13433);
        internalCounters.push_back(13552);
        internalCounters.push_back(13671);
        internalCounters.push_back(13790);
        internalCounters.push_back(13909);
        internalCounters.push_back(14028);
        internalCounters.push_back(14147);
        internalCounters.push_back(14266);
        internalCounters.push_back(14385);
        internalCounters.push_back(14504);
        internalCounters.push_back(14623);
        internalCounters.push_back(14742);
        internalCounters.push_back(14861);
        internalCounters.push_back(14980);
        internalCounters.push_back(15099);
        internalCounters.push_back(15218);
        internalCounters.push_back(15337);
        internalCounters.push_back(15456);
        internalCounters.push_back(15575);
        internalCounters.push_back(15694);
        internalCounters.push_back(15813);
        internalCounters.push_back(15932);
        internalCounters.push_back(16051);
        internalCounters.push_back(16170);
        internalCounters.push_back(16289);
        internalCounters.push_back(16408);
        internalCounters.push_back(16527);
        internalCounters.push_back(16646);
        internalCounters.push_back(16765);
        internalCounters.push_back(16884);
        internalCounters.push_back(17003);
        internalCounters.push_back(17122);
        internalCounters.push_back(17241);
        internalCounters.push_back(17360);
        internalCounters.push_back(17479);
        internalCounters.push_back(17598);
        internalCounters.push_back(17717);
        internalCounters.push_back(17836);
        internalCounters.push_back(17955);
        internalCounters.push_back(18074);
        internalCounters.push_back(18193);
        internalCounters.push_back(18312);
        internalCounters.push_back(18431);
        internalCounters.push_back(18550);
        internalCounters.push_back(18669);
        internalCounters.push_back(18788);
        internalCounters.push_back(18907);
        internalCounters.push_back(19026);
        internalCounters.push_back(19145);
        internalCounters.push_back(19264);
        internalCounters.push_back(19383);
        internalCounters.push_back(19502);
        internalCounters.push_back(19621);
        internalCounters.push_back(19740);
        internalCounters.push_back(19859);
        internalCounters.push_back(19978);
        internalCounters.push_back(20097);
        internalCounters.push_back(20216);
        internalCounters.push_back(20335);
        internalCounters.push_back(20454);
        internalCounters.push_back(20573);
        internalCounters.push_back(20692);
        internalCounters.push_back(20811);
        internalCounters.push_back(20930);
        internalCounters.push_back(13434);
        internalCounters.push_back(13553);
        internalCounters.push_back(13672);
        internalCounters.push_back(13791);
        internalCounters.push_back(13910);
        internalCounters.push_back(14029);
        internalCounters.push_back(14148);
        internalCounters.push_back(14267);
        internalCounters.push_back(14386);
        internalCounters.push_back(14505);
        internalCounters.push_back(14624);
        internalCounters.push_back(14743);
        internalCounters.push_back(14862);
        internalCounters.push_back(14981);
        internalCounters.push_back(15100);
        internalCounters.push_back(15219);
        internalCounters.push_back(15338);
        internalCounters.push_back(15457);
        internalCounters.push_back(15576);
        internalCounters.push_back(15695);
        internalCounters.push_back(15814);
        internalCounters.push_back(15933);
        internalCounters.push_back(16052);
        internalCounters.push_back(16171);
        internalCounters.push_back(16290);
        internalCounters.push_back(16409);
        internalCounters.push_back(16528);
        internalCounters.push_back(16647);
        internalCounters.push_back(16766);
        internalCounters.push_back(16885);
        internalCounters.push_back(17004);
        internalCounters.push_back(17123);
        internalCounters.push_back(17242);
        internalCounters.push_back(17361);
        internalCounters.push_back(17480);
        internalCounters.push_back(17599);
        internalCounters.push_back(17718);
        internalCounters.push_back(17837);
        internalCounters.push_back(17956);
        internalCounters.push_back(18075);
        internalCounters.push_back(18194);
        internalCounters.push_back(18313);
        internalCounters.push_back(18432);
        internalCounters.push_back(18551);
        internalCounters.push_back(18670);
        internalCounters.push_back(18789);
        internalCounters.push_back(18908);
        internalCounters.push_back(19027);
        internalCounters.push_back(19146);
        internalCounters.push_back(19265);
        internalCounters.push_back(19384);
        internalCounters.push_back(19503);
        internalCounters.push_back(19622);
        internalCounters.push_back(19741);
        internalCounters.push_back(19860);
        internalCounters.push_back(19979);
        internalCounters.push_back(20098);
        internalCounters.push_back(20217);
        internalCounters.push_back(20336);
        internalCounters.push_back(20455);
        internalCounters.push_back(20574);
        internalCounters.push_back(20693);
        internalCounters.push_back(20812);
        internalCounters.push_back(20931);
        internalCounters.push_back(13435);
        internalCounters.push_back(13554);
        internalCounters.push_back(13673);
        internalCounters.push_back(13792);
        internalCounters.push_back(13911);
        internalCounters.push_back(14030);
        internalCounters.push_back(14149);
        internalCounters.push_back(14268);
        internalCounters.push_back(14387);
        internalCounters.push_back(14506);
        internalCounters.push_back(14625);
        internalCounters.push_back(14744);
        internalCounters.push_back(14863);
        internalCounters.push_back(14982);
        internalCounters.push_back(15101);
        internalCounters.push_back(15220);
        internalCounters.push_back(15339);
        internalCounters.push_back(15458);
        internalCounters.push_back(15577);
        internalCounters.push_back(15696);
        internalCounters.push_back(15815);
        internalCounters.push_back(15934);
        internalCounters.push_back(16053);
        internalCounters.push_back(16172);
        internalCounters.push_back(16291);
        internalCounters.push_back(16410);
        internalCounters.push_back(16529);
        internalCounters.push_back(16648);
        internalCounters.push_back(16767);
        internalCounters.push_back(16886);
        internalCounters.push_back(17005);
        internalCounters.push_back(17124);
        internalCounters.push_back(17243);
        internalCounters.push_back(17362);
        internalCounters.push_back(17481);
        internalCounters.push_back(17600);
        internalCounters.push_back(17719);
        internalCounters.push_back(17838);
        internalCounters.push_back(17957);
        internalCounters.push_back(18076);
        internalCounters.push_back(18195);
        internalCounters.push_back(18314);
        internalCounters.push_back(18433);
        internalCounters.push_back(18552);
        internalCounters.push_back(18671);
        internalCounters.push_back(18790);
        internalCounters.push_back(18909);
        internalCounters.push_back(19028);
        internalCounters.push_back(19147);
        internalCounters.push_back(19266);
        internalCounters.push_back(19385);
        internalCounters.push_back(19504);
        internalCounters.push_back(19623);
        internalCounters.push_back(19742);
        internalCounters.push_back(19861);
        internalCounters.push_back(19980);
        internalCounters.push_back(20099);
        internalCounters.push_back(20218);
        internalCounters.push_back(20337);
        internalCounters.push_back(20456);
        internalCounters.push_back(20575);
        internalCounters.push_back(20694);
        internalCounters.push_back(20813);
        internalCounters.push_back(20932);
        internalCounters.push_back(13436);
        internalCounters.push_back(13555);
        internalCounters.push_back(13674);
        internalCounters.push_back(13793);
        internalCounters.push_back(13912);
        internalCounters.push_back(14031);
        internalCounters.push_back(14150);
        internalCounters.push_back(14269);
        internalCounters.push_back(14388);
        internalCounters.push_back(14507);
        internalCounters.push_back(14626);
        internalCounters.push_back(14745);
        internalCounters.push_back(14864);
        internalCounters.push_back(14983);
        internalCounters.push_back(15102);
        internalCounters.push_back(15221);
        internalCounters.push_back(15340);
        internalCounters.push_back(15459);
        internalCounters.push_back(15578);
        internalCounters.push_back(15697);
        internalCounters.push_back(15816);
        internalCounters.push_back(15935);
        internalCounters.push_back(16054);
        internalCounters.push_back(16173);
        internalCounters.push_back(16292);
        internalCounters.push_back(16411);
        internalCounters.push_back(16530);
        internalCounters.push_back(16649);
        internalCounters.push_back(16768);
        internalCounters.push_back(16887);
        internalCounters.push_back(17006);
        internalCounters.push_back(17125);
        internalCounters.push_back(17244);
        internalCounters.push_back(17363);
        internalCounters.push_back(17482);
        internalCounters.push_back(17601);
        internalCounters.push_back(17720);
        internalCounters.push_back(17839);
        internalCounters.push_back(17958);
        internalCounters.push_back(18077);
        internalCounters.push_back(18196);
        internalCounters.push_back(18315);
        internalCounters.push_back(18434);
        internalCounters.push_back(18553);
        internalCounters.push_back(18672);
        internalCounters.push_back(18791);
        internalCounters.push_back(18910);
        internalCounters.push_back(19029);
        internalCounters.push_back(19148);
        internalCounters.push_back(19267);
        internalCounters.push_back(19386);
        internalCounters.push_back(19505);
        internalCounters.push_back(19624);
        internalCounters.push_back(19743);
        internalCounters.push_back(19862);
        internalCounters.push_back(19981);
        internalCounters.push_back(20100);
        internalCounters.push_back(20219);
        internalCounters.push_back(20338);
        internalCounters.push_back(20457);
        internalCounters.push_back(20576);
        internalCounters.push_back(20695);
        internalCounters.push_back(20814);
        internalCounters.push_back(20933);
        internalCounters.push_back(13437);
        internalCounters.push_back(13556);
        internalCounters.push_back(13675);
        internalCounters.push_back(13794);
        internalCounters.push_back(13913);
        internalCounters.push_back(14032);
        internalCounters.push_back(14151);
        internalCounters.push_back(14270);
        internalCounters.push_back(14389);
        internalCounters.push_back(14508);
        internalCounters.push_back(14627);
        internalCounters.push_back(14746);
        internalCounters.push_back(14865);
        internalCounters.push_back(14984);
        internalCounters.push_back(15103);
        internalCounters.push_back(15222);
        internalCounters.push_back(15341);
        internalCounters.push_back(15460);
        internalCounters.push_back(15579);
        internalCounters.push_back(15698);
        internalCounters.push_back(15817);
        internalCounters.push_back(15936);
        internalCounters.push_back(16055);
        internalCounters.push_back(16174);
        internalCounters.push_back(16293);
        internalCounters.push_back(16412);
        internalCounters.push_back(16531);
        internalCounters.push_back(16650);
        internalCounters.push_back(16769);
        internalCounters.push_back(16888);
        internalCounters.push_back(17007);
        internalCounters.push_back(17126);
        internalCounters.push_back(17245);
        internalCounters.push_back(17364);
        internalCounters.push_back(17483);
        internalCounters.push_back(17602);
        internalCounters.push_back(17721);
        internalCounters.push_back(17840);
        internalCounters.push_back(17959);
        internalCounters.push_back(18078);
        internalCounters.push_back(18197);
        internalCounters.push_back(18316);
        internalCounters.push_back(18435);
        internalCounters.push_back(18554);
        internalCounters.push_back(18673);
        internalCounters.push_back(18792);
        internalCounters.push_back(18911);
        internalCounters.push_back(19030);
        internalCounters.push_back(19149);
        internalCounters.push_back(19268);
        internalCounters.push_back(19387);
        internalCounters.push_back(19506);
        internalCounters.push_back(19625);
        internalCounters.push_back(19744);
        internalCounters.push_back(19863);
        internalCounters.push_back(19982);
        internalCounters.push_back(20101);
        internalCounters.push_back(20220);
        internalCounters.push_back(20339);
        internalCounters.push_back(20458);
        internalCounters.push_back(20577);
        internalCounters.push_back(20696);
        internalCounters.push_back(20815);
        internalCounters.push_back(20934);
        internalCounters.push_back(13438);
        internalCounters.push_back(13557);
        internalCounters.push_back(13676);
        internalCounters.push_back(13795);
        internalCounters.push_back(13914);
        internalCounters.push_back(14033);
        internalCounters.push_back(14152);
        internalCounters.push_back(14271);
        internalCounters.push_back(14390);
        internalCounters.push_back(14509);
        internalCounters.push_back(14628);
        internalCounters.push_back(14747);
        internalCounters.push_back(14866);
        internalCounters.push_back(14985);
        internalCounters.push_back(15104);
        internalCounters.push_back(15223);
        internalCounters.push_back(15342);
        internalCounters.push_back(15461);
        internalCounters.push_back(15580);
        internalCounters.push_back(15699);
        internalCounters.push_back(15818);
        internalCounters.push_back(15937);
        internalCounters.push_back(16056);
        internalCounters.push_back(16175);
        internalCounters.push_back(16294);
        internalCounters.push_back(16413);
        internalCounters.push_back(16532);
        internalCounters.push_back(16651);
        internalCounters.push_back(16770);
        internalCounters.push_back(16889);
        internalCounters.push_back(17008);
        internalCounters.push_back(17127);
        internalCounters.push_back(17246);
        internalCounters.push_back(17365);
        internalCounters.push_back(17484);
        internalCounters.push_back(17603);
        internalCounters.push_back(17722);
        internalCounters.push_back(17841);
        internalCounters.push_back(17960);
        internalCounters.push_back(18079);
        internalCounters.push_back(18198);
        internalCounters.push_back(18317);
        internalCounters.push_back(18436);
        internalCounters.push_back(18555);
        internalCounters.push_back(18674);
        internalCounters.push_back(18793);
        internalCounters.push_back(18912);
        internalCounters.push_back(19031);
        internalCounters.push_back(19150);
        internalCounters.push_back(19269);
        internalCounters.push_back(19388);
        internalCounters.push_back(19507);
        internalCounters.push_back(19626);
        internalCounters.push_back(19745);
        internalCounters.push_back(19864);
        internalCounters.push_back(19983);
        internalCounters.push_back(20102);
        internalCounters.push_back(20221);
        internalCounters.push_back(20340);
        internalCounters.push_back(20459);
        internalCounters.push_back(20578);
        internalCounters.push_back(20697);
        internalCounters.push_back(20816);
        internalCounters.push_back(20935);
        internalCounters.push_back(13439);
        internalCounters.push_back(13558);
        internalCounters.push_back(13677);
        internalCounters.push_back(13796);
        internalCounters.push_back(13915);
        internalCounters.push_back(14034);
        internalCounters.push_back(14153);
        internalCounters.push_back(14272);
        internalCounters.push_back(14391);
        internalCounters.push_back(14510);
        internalCounters.push_back(14629);
        internalCounters.push_back(14748);
        internalCounters.push_back(14867);
        internalCounters.push_back(14986);
        internalCounters.push_back(15105);
        internalCounters.push_back(15224);
        internalCounters.push_back(15343);
        internalCounters.push_back(15462);
        internalCounters.push_back(15581);
        internalCounters.push_back(15700);
        internalCounters.push_back(15819);
        internalCounters.push_back(15938);
        internalCounters.push_back(16057);
        internalCounters.push_back(16176);
        internalCounters.push_back(16295);
        internalCounters.push_back(16414);
        internalCounters.push_back(16533);
        internalCounters.push_back(16652);
        internalCounters.push_back(16771);
        internalCounters.push_back(16890);
        internalCounters.push_back(17009);
        internalCounters.push_back(17128);
        internalCounters.push_back(17247);
        internalCounters.push_back(17366);
        internalCounters.push_back(17485);
        internalCounters.push_back(17604);
        internalCounters.push_back(17723);
        internalCounters.push_back(17842);
        internalCounters.push_back(17961);
        internalCounters.push_back(18080);
        internalCounters.push_back(18199);
        internalCounters.push_back(18318);
        internalCounters.push_back(18437);
        internalCounters.push_back(18556);
        internalCounters.push_back(18675);
        internalCounters.push_back(18794);
        internalCounters.push_back(18913);
        internalCounters.push_back(19032);
        internalCounters.push_back(19151);
        internalCounters.push_back(19270);
        internalCounters.push_back(19389);
        internalCounters.push_back(19508);
        internalCounters.push_back(19627);
        internalCounters.push_back(19746);
        internalCounters.push_back(19865);
        internalCounters.push_back(19984);
        internalCounters.push_back(20103);
        internalCounters.push_back(20222);
        internalCounters.push_back(20341);
        internalCounters.push_back(20460);
        internalCounters.push_back(20579);
        internalCounters.push_back(20698);
        internalCounters.push_back(20817);
        internalCounters.push_back(20936);
        internalCounters.push_back(13440);
        internalCounters.push_back(13559);
        internalCounters.push_back(13678);
        internalCounters.push_back(13797);
        internalCounters.push_back(13916);
        internalCounters.push_back(14035);
        internalCounters.push_back(14154);
        internalCounters.push_back(14273);
        internalCounters.push_back(14392);
        internalCounters.push_back(14511);
        internalCounters.push_back(14630);
        internalCounters.push_back(14749);
        internalCounters.push_back(14868);
        internalCounters.push_back(14987);
        internalCounters.push_back(15106);
        internalCounters.push_back(15225);
        internalCounters.push_back(15344);
        internalCounters.push_back(15463);
        internalCounters.push_back(15582);
        internalCounters.push_back(15701);
        internalCounters.push_back(15820);
        internalCounters.push_back(15939);
        internalCounters.push_back(16058);
        internalCounters.push_back(16177);
        internalCounters.push_back(16296);
        internalCounters.push_back(16415);
        internalCounters.push_back(16534);
        internalCounters.push_back(16653);
        internalCounters.push_back(16772);
        internalCounters.push_back(16891);
        internalCounters.push_back(17010);
        internalCounters.push_back(17129);
        internalCounters.push_back(17248);
        internalCounters.push_back(17367);
        internalCounters.push_back(17486);
        internalCounters.push_back(17605);
        internalCounters.push_back(17724);
        internalCounters.push_back(17843);
        internalCounters.push_back(17962);
        internalCounters.push_back(18081);
        internalCounters.push_back(18200);
        internalCounters.push_back(18319);
        internalCounters.push_back(18438);
        internalCounters.push_back(18557);
        internalCounters.push_back(18676);
        internalCounters.push_back(18795);
        internalCounters.push_back(18914);
        internalCounters.push_back(19033);
        internalCounters.push_back(19152);
        internalCounters.push_back(19271);
        internalCounters.push_back(19390);
        internalCounters.push_back(19509);
        internalCounters.push_back(19628);
        internalCounters.push_back(19747);
        internalCounters.push_back(19866);
        internalCounters.push_back(19985);
        internalCounters.push_back(20104);
        internalCounters.push_back(20223);
        internalCounters.push_back(20342);
        internalCounters.push_back(20461);
        internalCounters.push_back(20580);
        internalCounters.push_back(20699);
        internalCounters.push_back(20818);
        internalCounters.push_back(20937);

        p.DefinePublicCounter("TexAveAnisotropy", "TextureUnit", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(2),64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum64,*,+,(4),128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,sum64,*,+,(6),192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,sum64,*,+,(8),256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,sum64,*,+,(10),320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,sum64,*,+,(12),384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,433,434,435,436,437,438,439,440,441,442,443,444,445,446,447,sum64,*,+,(14),448,449,450,451,452,453,454,455,456,457,458,459,460,461,462,463,464,465,466,467,468,469,470,471,472,473,474,475,476,477,478,479,480,481,482,483,484,485,486,487,488,489,490,491,492,493,494,495,496,497,498,499,500,501,502,503,504,505,506,507,508,509,510,511,sum64,*,+,(16),512,513,514,515,516,517,518,519,520,521,522,523,524,525,526,527,528,529,530,531,532,533,534,535,536,537,538,539,540,541,542,543,544,545,546,547,548,549,550,551,552,553,554,555,556,557,558,559,560,561,562,563,564,565,566,567,568,569,570,571,572,573,574,575,sum64,*,+,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum64,+,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,sum64,+,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,sum64,+,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,sum64,+,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,sum64,+,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,433,434,435,436,437,438,439,440,441,442,443,444,445,446,447,sum64,+,448,449,450,451,452,453,454,455,456,457,458,459,460,461,462,463,464,465,466,467,468,469,470,471,472,473,474,475,476,477,478,479,480,481,482,483,484,485,486,487,488,489,490,491,492,493,494,495,496,497,498,499,500,501,502,503,504,505,506,507,508,509,510,511,sum64,+,512,513,514,515,516,517,518,519,520,521,522,523,524,525,526,527,528,529,530,531,532,533,534,535,536,537,538,539,540,541,542,543,544,545,546,547,548,549,550,551,552,553,554,555,556,557,558,559,560,561,562,563,564,565,566,567,568,569,570,571,572,573,574,575,sum64,+,/", "7ca2a2b9-a4eb-ce23-d163-59147e672396" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(39285);
        internalCounters.push_back(39542);
        internalCounters.push_back(39799);
        internalCounters.push_back(40056);
        internalCounters.push_back(40313);
        internalCounters.push_back(40570);
        internalCounters.push_back(40827);
        internalCounters.push_back(41084);
        internalCounters.push_back(41341);
        internalCounters.push_back(41598);
        internalCounters.push_back(41855);
        internalCounters.push_back(42112);
        internalCounters.push_back(42369);
        internalCounters.push_back(42626);
        internalCounters.push_back(42883);
        internalCounters.push_back(43140);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("DepthStencilTestBusy", "Timing", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "6834fb52-42e8-bb50-fd48-ec2f2904e7e0" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(39285);
        internalCounters.push_back(39542);
        internalCounters.push_back(39799);
        internalCounters.push_back(40056);
        internalCounters.push_back(40313);
        internalCounters.push_back(40570);
        internalCounters.push_back(40827);
        internalCounters.push_back(41084);
        internalCounters.push_back(41341);
        internalCounters.push_back(41598);
        internalCounters.push_back(41855);
        internalCounters.push_back(42112);
        internalCounters.push_back(42369);
        internalCounters.push_back(42626);
        internalCounters.push_back(42883);
        internalCounters.push_back(43140);

        p.DefinePublicCounter("DepthStencilTestBusyCount", "Timing", "Number of GPU cycles spent performing depth and stencil tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "e02860fa-c7bd-90ea-2149-69b4e98a636c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(39156);
        internalCounters.push_back(39413);
        internalCounters.push_back(39670);
        internalCounters.push_back(39927);
        internalCounters.push_back(40184);
        internalCounters.push_back(40441);
        internalCounters.push_back(40698);
        internalCounters.push_back(40955);
        internalCounters.push_back(41212);
        internalCounters.push_back(41469);
        internalCounters.push_back(41726);
        internalCounters.push_back(41983);
        internalCounters.push_back(42240);
        internalCounters.push_back(42497);
        internalCounters.push_back(42754);
        internalCounters.push_back(43011);
        internalCounters.push_back(39145);
        internalCounters.push_back(39402);
        internalCounters.push_back(39659);
        internalCounters.push_back(39916);
        internalCounters.push_back(40173);
        internalCounters.push_back(40430);
        internalCounters.push_back(40687);
        internalCounters.push_back(40944);
        internalCounters.push_back(41201);
        internalCounters.push_back(41458);
        internalCounters.push_back(41715);
        internalCounters.push_back(41972);
        internalCounters.push_back(42229);
        internalCounters.push_back(42486);
        internalCounters.push_back(42743);
        internalCounters.push_back(43000);

        p.DefinePublicCounter("HiZTilesAccepted", "DepthAndStencil", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*", "56176f45-d7ff-813d-4f05-3b2f046067e7" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(39145);
        internalCounters.push_back(39402);
        internalCounters.push_back(39659);
        internalCounters.push_back(39916);
        internalCounters.push_back(40173);
        internalCounters.push_back(40430);
        internalCounters.push_back(40687);
        internalCounters.push_back(40944);
        internalCounters.push_back(41201);
        internalCounters.push_back(41458);
        internalCounters.push_back(41715);
        internalCounters.push_back(41972);
        internalCounters.push_back(42229);
        internalCounters.push_back(42486);
        internalCounters.push_back(42743);
        internalCounters.push_back(43000);

        p.DefinePublicCounter("HiZTilesAcceptedCount", "DepthAndStencil", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "95d4e3f6-b2f0-f26e-8423-aacdfaf79ea3" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(39156);
        internalCounters.push_back(39413);
        internalCounters.push_back(39670);
        internalCounters.push_back(39927);
        internalCounters.push_back(40184);
        internalCounters.push_back(40441);
        internalCounters.push_back(40698);
        internalCounters.push_back(40955);
        internalCounters.push_back(41212);
        internalCounters.push_back(41469);
        internalCounters.push_back(41726);
        internalCounters.push_back(41983);
        internalCounters.push_back(42240);
        internalCounters.push_back(42497);
        internalCounters.push_back(42754);
        internalCounters.push_back(43011);

        p.DefinePublicCounter("HiZTilesRejectedCount", "DepthAndStencil", "Count of tiles not accepted by HiZ.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "156ba142-7eeb-aa6e-a00a-f8aea4e41e0b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(39145);
        internalCounters.push_back(39402);
        internalCounters.push_back(39659);
        internalCounters.push_back(39916);
        internalCounters.push_back(40173);
        internalCounters.push_back(40430);
        internalCounters.push_back(40687);
        internalCounters.push_back(40944);
        internalCounters.push_back(41201);
        internalCounters.push_back(41458);
        internalCounters.push_back(41715);
        internalCounters.push_back(41972);
        internalCounters.push_back(42229);
        internalCounters.push_back(42486);
        internalCounters.push_back(42743);
        internalCounters.push_back(43000);
        internalCounters.push_back(39169);
        internalCounters.push_back(39426);
        internalCounters.push_back(39683);
        internalCounters.push_back(39940);
        internalCounters.push_back(40197);
        internalCounters.push_back(40454);
        internalCounters.push_back(40711);
        internalCounters.push_back(40968);
        internalCounters.push_back(41225);
        internalCounters.push_back(41482);
        internalCounters.push_back(41739);
        internalCounters.push_back(41996);
        internalCounters.push_back(42253);
        internalCounters.push_back(42510);
        internalCounters.push_back(42767);
        internalCounters.push_back(43024);

        p.DefinePublicCounter("PreZTilesDetailCulled", "DepthAndStencil", "Percentage of tiles rejected because the associated prim had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*", "cad7f54d-a044-7574-c472-6f2065cbeeac" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(39169);
        internalCounters.push_back(39426);
        internalCounters.push_back(39683);
        internalCounters.push_back(39940);
        internalCounters.push_back(40197);
        internalCounters.push_back(40454);
        internalCounters.push_back(40711);
        internalCounters.push_back(40968);
        internalCounters.push_back(41225);
        internalCounters.push_back(41482);
        internalCounters.push_back(41739);
        internalCounters.push_back(41996);
        internalCounters.push_back(42253);
        internalCounters.push_back(42510);
        internalCounters.push_back(42767);
        internalCounters.push_back(43024);

        p.DefinePublicCounter("PreZTilesDetailCulledCount", "DepthAndStencil", "Count of tiles rejected because the associated primitive had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "49262c8a-b1e6-90dd-f096-0fc4921715e9" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(39145);
        internalCounters.push_back(39402);
        internalCounters.push_back(39659);
        internalCounters.push_back(39916);
        internalCounters.push_back(40173);
        internalCounters.push_back(40430);
        internalCounters.push_back(40687);
        internalCounters.push_back(40944);
        internalCounters.push_back(41201);
        internalCounters.push_back(41458);
        internalCounters.push_back(41715);
        internalCounters.push_back(41972);
        internalCounters.push_back(42229);
        internalCounters.push_back(42486);
        internalCounters.push_back(42743);
        internalCounters.push_back(43000);

        p.DefinePublicCounter("PreZTilesDetailSurvivingCount", "DepthAndStencil", "Count of tiles surviving because the associated primitive had contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "f803eaa4-bbed-bd39-775f-a64df92e2c08" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1426);
        internalCounters.push_back(1823);
        internalCounters.push_back(2220);
        internalCounters.push_back(2617);
        internalCounters.push_back(1427);
        internalCounters.push_back(1824);
        internalCounters.push_back(2221);
        internalCounters.push_back(2618);
        internalCounters.push_back(1428);
        internalCounters.push_back(1825);
        internalCounters.push_back(2222);
        internalCounters.push_back(2619);
        internalCounters.push_back(1429);
        internalCounters.push_back(1826);
        internalCounters.push_back(2223);
        internalCounters.push_back(2620);
        internalCounters.push_back(1502);
        internalCounters.push_back(1899);
        internalCounters.push_back(2296);
        internalCounters.push_back(2693);
        internalCounters.push_back(1503);
        internalCounters.push_back(1900);
        internalCounters.push_back(2297);
        internalCounters.push_back(2694);
        internalCounters.push_back(1504);
        internalCounters.push_back(1901);
        internalCounters.push_back(2298);
        internalCounters.push_back(2695);
        internalCounters.push_back(1505);
        internalCounters.push_back(1902);
        internalCounters.push_back(2299);
        internalCounters.push_back(2696);

        p.DefinePublicCounter("HiZQuadsCulled", "DepthAndStencil", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*", "fa0e319b-5573-6d34-5bab-904769925036" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1502);
        internalCounters.push_back(1899);
        internalCounters.push_back(2296);
        internalCounters.push_back(2693);
        internalCounters.push_back(1503);
        internalCounters.push_back(1900);
        internalCounters.push_back(2297);
        internalCounters.push_back(2694);
        internalCounters.push_back(1504);
        internalCounters.push_back(1901);
        internalCounters.push_back(2298);
        internalCounters.push_back(2695);
        internalCounters.push_back(1505);
        internalCounters.push_back(1902);
        internalCounters.push_back(2299);
        internalCounters.push_back(2696);

        p.DefinePublicCounter("HiZQuadsCulledCount", "DepthAndStencil", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "73b0b39d-6df2-3e24-0b5c-7cb0ac8b6f39" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1426);
        internalCounters.push_back(1823);
        internalCounters.push_back(2220);
        internalCounters.push_back(2617);
        internalCounters.push_back(1427);
        internalCounters.push_back(1824);
        internalCounters.push_back(2221);
        internalCounters.push_back(2618);
        internalCounters.push_back(1428);
        internalCounters.push_back(1825);
        internalCounters.push_back(2222);
        internalCounters.push_back(2619);
        internalCounters.push_back(1429);
        internalCounters.push_back(1826);
        internalCounters.push_back(2223);
        internalCounters.push_back(2620);
        internalCounters.push_back(1502);
        internalCounters.push_back(1899);
        internalCounters.push_back(2296);
        internalCounters.push_back(2693);
        internalCounters.push_back(1503);
        internalCounters.push_back(1900);
        internalCounters.push_back(2297);
        internalCounters.push_back(2694);
        internalCounters.push_back(1504);
        internalCounters.push_back(1901);
        internalCounters.push_back(2298);
        internalCounters.push_back(2695);
        internalCounters.push_back(1505);
        internalCounters.push_back(1902);
        internalCounters.push_back(2299);
        internalCounters.push_back(2696);

        p.DefinePublicCounter("HiZQuadsSurvivingCount", "DepthAndStencil", "Count of quads that survive in the pipeline after HiZ.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(0),max", "5a2cd556-acb9-c81e-92bc-7ceef6012b42" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1426);
        internalCounters.push_back(1823);
        internalCounters.push_back(2220);
        internalCounters.push_back(2617);
        internalCounters.push_back(1427);
        internalCounters.push_back(1824);
        internalCounters.push_back(2221);
        internalCounters.push_back(2618);
        internalCounters.push_back(1428);
        internalCounters.push_back(1825);
        internalCounters.push_back(2222);
        internalCounters.push_back(2619);
        internalCounters.push_back(1429);
        internalCounters.push_back(1826);
        internalCounters.push_back(2223);
        internalCounters.push_back(2620);
        internalCounters.push_back(1526);
        internalCounters.push_back(1923);
        internalCounters.push_back(2320);
        internalCounters.push_back(2717);
        internalCounters.push_back(1502);
        internalCounters.push_back(1899);
        internalCounters.push_back(2296);
        internalCounters.push_back(2693);
        internalCounters.push_back(1503);
        internalCounters.push_back(1900);
        internalCounters.push_back(2297);
        internalCounters.push_back(2694);
        internalCounters.push_back(1504);
        internalCounters.push_back(1901);
        internalCounters.push_back(2298);
        internalCounters.push_back(2695);
        internalCounters.push_back(1505);
        internalCounters.push_back(1902);
        internalCounters.push_back(2299);
        internalCounters.push_back(2696);

        p.DefinePublicCounter("PreZQuadsCulled", "DepthAndStencil", "Percentage of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,sum16,16,17,18,19,sum4,-,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*", "4e77547b-ec55-5663-f034-af59be66d77d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1526);
        internalCounters.push_back(1923);
        internalCounters.push_back(2320);
        internalCounters.push_back(2717);
        internalCounters.push_back(1502);
        internalCounters.push_back(1899);
        internalCounters.push_back(2296);
        internalCounters.push_back(2693);
        internalCounters.push_back(1503);
        internalCounters.push_back(1900);
        internalCounters.push_back(2297);
        internalCounters.push_back(2694);
        internalCounters.push_back(1504);
        internalCounters.push_back(1901);
        internalCounters.push_back(2298);
        internalCounters.push_back(2695);
        internalCounters.push_back(1505);
        internalCounters.push_back(1902);
        internalCounters.push_back(2299);
        internalCounters.push_back(2696);

        p.DefinePublicCounter("PreZQuadsCulledCount", "DepthAndStencil", "Count of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,sum4,+", "1bf169e6-9304-834e-df5f-0c44d7890a08" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1426);
        internalCounters.push_back(1823);
        internalCounters.push_back(2220);
        internalCounters.push_back(2617);
        internalCounters.push_back(1427);
        internalCounters.push_back(1824);
        internalCounters.push_back(2221);
        internalCounters.push_back(2618);
        internalCounters.push_back(1428);
        internalCounters.push_back(1825);
        internalCounters.push_back(2222);
        internalCounters.push_back(2619);
        internalCounters.push_back(1429);
        internalCounters.push_back(1826);
        internalCounters.push_back(2223);
        internalCounters.push_back(2620);
        internalCounters.push_back(1502);
        internalCounters.push_back(1899);
        internalCounters.push_back(2296);
        internalCounters.push_back(2693);
        internalCounters.push_back(1503);
        internalCounters.push_back(1900);
        internalCounters.push_back(2297);
        internalCounters.push_back(2694);
        internalCounters.push_back(1504);
        internalCounters.push_back(1901);
        internalCounters.push_back(2298);
        internalCounters.push_back(2695);
        internalCounters.push_back(1505);
        internalCounters.push_back(1902);
        internalCounters.push_back(2299);
        internalCounters.push_back(2696);

        p.DefinePublicCounter("PreZQuadsSurvivingCount", "DepthAndStencil", "Count of quads surviving detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(0),max", "50e25e51-3713-89cb-7f92-559cde5e5532" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1526);
        internalCounters.push_back(1923);
        internalCounters.push_back(2320);
        internalCounters.push_back(2717);
        internalCounters.push_back(1426);
        internalCounters.push_back(1823);
        internalCounters.push_back(2220);
        internalCounters.push_back(2617);
        internalCounters.push_back(1427);
        internalCounters.push_back(1824);
        internalCounters.push_back(2221);
        internalCounters.push_back(2618);
        internalCounters.push_back(1428);
        internalCounters.push_back(1825);
        internalCounters.push_back(2222);
        internalCounters.push_back(2619);
        internalCounters.push_back(1429);
        internalCounters.push_back(1826);
        internalCounters.push_back(2223);
        internalCounters.push_back(2620);

        p.DefinePublicCounter("PostZQuads", "DepthAndStencil", "Percentage of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,sum16,/,(100),*", "58f0d34b-eeb8-e8db-abce-cb72584144be" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(1526);
        internalCounters.push_back(1923);
        internalCounters.push_back(2320);
        internalCounters.push_back(2717);

        p.DefinePublicCounter("PostZQuadCount", "DepthAndStencil", "Count of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,sum4", "08404526-ce35-939b-34c8-a7a35a0ff4d6" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(39318);
        internalCounters.push_back(39575);
        internalCounters.push_back(39832);
        internalCounters.push_back(40089);
        internalCounters.push_back(40346);
        internalCounters.push_back(40603);
        internalCounters.push_back(40860);
        internalCounters.push_back(41117);
        internalCounters.push_back(41374);
        internalCounters.push_back(41631);
        internalCounters.push_back(41888);
        internalCounters.push_back(42145);
        internalCounters.push_back(42402);
        internalCounters.push_back(42659);
        internalCounters.push_back(42916);
        internalCounters.push_back(43173);

        p.DefinePublicCounter("PreZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z before shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "3bfe6c4d-7422-ca03-7ea5-e67ff1a00136" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(39320);
        internalCounters.push_back(39577);
        internalCounters.push_back(39834);
        internalCounters.push_back(40091);
        internalCounters.push_back(40348);
        internalCounters.push_back(40605);
        internalCounters.push_back(40862);
        internalCounters.push_back(41119);
        internalCounters.push_back(41376);
        internalCounters.push_back(41633);
        internalCounters.push_back(41890);
        internalCounters.push_back(42147);
        internalCounters.push_back(42404);
        internalCounters.push_back(42661);
        internalCounters.push_back(42918);
        internalCounters.push_back(43175);

        p.DefinePublicCounter("PreZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z before shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "df7f705e-5162-d3b5-da8b-63466cf9c4e5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(39319);
        internalCounters.push_back(39576);
        internalCounters.push_back(39833);
        internalCounters.push_back(40090);
        internalCounters.push_back(40347);
        internalCounters.push_back(40604);
        internalCounters.push_back(40861);
        internalCounters.push_back(41118);
        internalCounters.push_back(41375);
        internalCounters.push_back(41632);
        internalCounters.push_back(41889);
        internalCounters.push_back(42146);
        internalCounters.push_back(42403);
        internalCounters.push_back(42660);
        internalCounters.push_back(42917);
        internalCounters.push_back(43174);

        p.DefinePublicCounter("PreZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z before shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "4484e950-f7a4-3800-bc74-78dd297f017e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(39315);
        internalCounters.push_back(39572);
        internalCounters.push_back(39829);
        internalCounters.push_back(40086);
        internalCounters.push_back(40343);
        internalCounters.push_back(40600);
        internalCounters.push_back(40857);
        internalCounters.push_back(41114);
        internalCounters.push_back(41371);
        internalCounters.push_back(41628);
        internalCounters.push_back(41885);
        internalCounters.push_back(42142);
        internalCounters.push_back(42399);
        internalCounters.push_back(42656);
        internalCounters.push_back(42913);
        internalCounters.push_back(43170);

        p.DefinePublicCounter("PostZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z after shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "4995d5d6-2330-b986-508b-fae24856f44c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(39317);
        internalCounters.push_back(39574);
        internalCounters.push_back(39831);
        internalCounters.push_back(40088);
        internalCounters.push_back(40345);
        internalCounters.push_back(40602);
        internalCounters.push_back(40859);
        internalCounters.push_back(41116);
        internalCounters.push_back(41373);
        internalCounters.push_back(41630);
        internalCounters.push_back(41887);
        internalCounters.push_back(42144);
        internalCounters.push_back(42401);
        internalCounters.push_back(42658);
        internalCounters.push_back(42915);
        internalCounters.push_back(43172);

        p.DefinePublicCounter("PostZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z after shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "ae558af4-f4be-3dd4-7316-b2c4dcf0def8" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(39316);
        internalCounters.push_back(39573);
        internalCounters.push_back(39830);
        internalCounters.push_back(40087);
        internalCounters.push_back(40344);
        internalCounters.push_back(40601);
        internalCounters.push_back(40858);
        internalCounters.push_back(41115);
        internalCounters.push_back(41372);
        internalCounters.push_back(41629);
        internalCounters.push_back(41886);
        internalCounters.push_back(42143);
        internalCounters.push_back(42400);
        internalCounters.push_back(42657);
        internalCounters.push_back(42914);
        internalCounters.push_back(43171);

        p.DefinePublicCounter("PostZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z after shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "b3684c94-814a-c695-c85d-a5b6ab798b35" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(39187);
        internalCounters.push_back(39444);
        internalCounters.push_back(39701);
        internalCounters.push_back(39958);
        internalCounters.push_back(40215);
        internalCounters.push_back(40472);
        internalCounters.push_back(40729);
        internalCounters.push_back(40986);
        internalCounters.push_back(41243);
        internalCounters.push_back(41500);
        internalCounters.push_back(41757);
        internalCounters.push_back(42014);
        internalCounters.push_back(42271);
        internalCounters.push_back(42528);
        internalCounters.push_back(42785);
        internalCounters.push_back(43042);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("ZUnitStalled", "DepthAndStencil", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "5e86c3ad-1726-3157-1d01-7ed188bf854d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(39187);
        internalCounters.push_back(39444);
        internalCounters.push_back(39701);
        internalCounters.push_back(39958);
        internalCounters.push_back(40215);
        internalCounters.push_back(40472);
        internalCounters.push_back(40729);
        internalCounters.push_back(40986);
        internalCounters.push_back(41243);
        internalCounters.push_back(41500);
        internalCounters.push_back(41757);
        internalCounters.push_back(42014);
        internalCounters.push_back(42271);
        internalCounters.push_back(42528);
        internalCounters.push_back(42785);
        internalCounters.push_back(43042);

        p.DefinePublicCounter("ZUnitStalledCycles", "DepthAndStencil", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "4351fa7f-6737-2c3e-3ffb-b3addbdceedd" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(39189);
        internalCounters.push_back(39446);
        internalCounters.push_back(39703);
        internalCounters.push_back(39960);
        internalCounters.push_back(40217);
        internalCounters.push_back(40474);
        internalCounters.push_back(40731);
        internalCounters.push_back(40988);
        internalCounters.push_back(41245);
        internalCounters.push_back(41502);
        internalCounters.push_back(41759);
        internalCounters.push_back(42016);
        internalCounters.push_back(42273);
        internalCounters.push_back(42530);
        internalCounters.push_back(42787);
        internalCounters.push_back(43044);
        internalCounters.push_back(39196);
        internalCounters.push_back(39453);
        internalCounters.push_back(39710);
        internalCounters.push_back(39967);
        internalCounters.push_back(40224);
        internalCounters.push_back(40481);
        internalCounters.push_back(40738);
        internalCounters.push_back(40995);
        internalCounters.push_back(41252);
        internalCounters.push_back(41509);
        internalCounters.push_back(41766);
        internalCounters.push_back(42023);
        internalCounters.push_back(42280);
        internalCounters.push_back(42537);
        internalCounters.push_back(42794);
        internalCounters.push_back(43051);

        p.DefinePublicCounter("DBMemRead", "DepthAndStencil", "Number of bytes read from the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(256),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+", "dcdb4ee7-bd50-00f7-c028-9e5f4ce888c0" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(39201);
        internalCounters.push_back(39458);
        internalCounters.push_back(39715);
        internalCounters.push_back(39972);
        internalCounters.push_back(40229);
        internalCounters.push_back(40486);
        internalCounters.push_back(40743);
        internalCounters.push_back(41000);
        internalCounters.push_back(41257);
        internalCounters.push_back(41514);
        internalCounters.push_back(41771);
        internalCounters.push_back(42028);
        internalCounters.push_back(42285);
        internalCounters.push_back(42542);
        internalCounters.push_back(42799);
        internalCounters.push_back(43056);
        internalCounters.push_back(39204);
        internalCounters.push_back(39461);
        internalCounters.push_back(39718);
        internalCounters.push_back(39975);
        internalCounters.push_back(40232);
        internalCounters.push_back(40489);
        internalCounters.push_back(40746);
        internalCounters.push_back(41003);
        internalCounters.push_back(41260);
        internalCounters.push_back(41517);
        internalCounters.push_back(41774);
        internalCounters.push_back(42031);
        internalCounters.push_back(42288);
        internalCounters.push_back(42545);
        internalCounters.push_back(42802);
        internalCounters.push_back(43059);

        p.DefinePublicCounter("DBMemWritten", "DepthAndStencil", "Number of bytes written to the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+", "de5717f8-8a49-ee44-4645-10de51b37dcf" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(43381);
        internalCounters.push_back(43777);
        internalCounters.push_back(44173);
        internalCounters.push_back(44569);
        internalCounters.push_back(44965);
        internalCounters.push_back(45361);
        internalCounters.push_back(45757);
        internalCounters.push_back(46153);
        internalCounters.push_back(46549);
        internalCounters.push_back(46945);
        internalCounters.push_back(47341);
        internalCounters.push_back(47737);
        internalCounters.push_back(48133);
        internalCounters.push_back(48529);
        internalCounters.push_back(48925);
        internalCounters.push_back(49321);

        p.DefinePublicCounter("CBMemRead", "ColorBuffer", "Number of bytes read from the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "84b531d8-a1f8-7f49-7c27-7bc97801f1e6" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(43512);
        internalCounters.push_back(43908);
        internalCounters.push_back(44304);
        internalCounters.push_back(44700);
        internalCounters.push_back(45096);
        internalCounters.push_back(45492);
        internalCounters.push_back(45888);
        internalCounters.push_back(46284);
        internalCounters.push_back(46680);
        internalCounters.push_back(47076);
        internalCounters.push_back(47472);
        internalCounters.push_back(47868);
        internalCounters.push_back(48264);
        internalCounters.push_back(48660);
        internalCounters.push_back(49056);
        internalCounters.push_back(49452);
        internalCounters.push_back(43379);
        internalCounters.push_back(43775);
        internalCounters.push_back(44171);
        internalCounters.push_back(44567);
        internalCounters.push_back(44963);
        internalCounters.push_back(45359);
        internalCounters.push_back(45755);
        internalCounters.push_back(46151);
        internalCounters.push_back(46547);
        internalCounters.push_back(46943);
        internalCounters.push_back(47339);
        internalCounters.push_back(47735);
        internalCounters.push_back(48131);
        internalCounters.push_back(48527);
        internalCounters.push_back(48923);
        internalCounters.push_back(49319);
        internalCounters.push_back(43380);
        internalCounters.push_back(43776);
        internalCounters.push_back(44172);
        internalCounters.push_back(44568);
        internalCounters.push_back(44964);
        internalCounters.push_back(45360);
        internalCounters.push_back(45756);
        internalCounters.push_back(46152);
        internalCounters.push_back(46548);
        internalCounters.push_back(46944);
        internalCounters.push_back(47340);
        internalCounters.push_back(47736);
        internalCounters.push_back(48132);
        internalCounters.push_back(48528);
        internalCounters.push_back(48924);
        internalCounters.push_back(49320);
        internalCounters.push_back(43381);
        internalCounters.push_back(43777);
        internalCounters.push_back(44173);
        internalCounters.push_back(44569);
        internalCounters.push_back(44965);
        internalCounters.push_back(45361);
        internalCounters.push_back(45757);
        internalCounters.push_back(46153);
        internalCounters.push_back(46549);
        internalCounters.push_back(46945);
        internalCounters.push_back(47341);
        internalCounters.push_back(47737);
        internalCounters.push_back(48133);
        internalCounters.push_back(48529);
        internalCounters.push_back(48925);
        internalCounters.push_back(49321);

        p.DefinePublicCounter("CBColorAndMaskRead", "ColorBuffer", "Total number of bytes read from the color and mask buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*", "da41660e-eb6f-32ec-8a64-b32ca17bd7eb" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(43371);
        internalCounters.push_back(43767);
        internalCounters.push_back(44163);
        internalCounters.push_back(44559);
        internalCounters.push_back(44955);
        internalCounters.push_back(45351);
        internalCounters.push_back(45747);
        internalCounters.push_back(46143);
        internalCounters.push_back(46539);
        internalCounters.push_back(46935);
        internalCounters.push_back(47331);
        internalCounters.push_back(47727);
        internalCounters.push_back(48123);
        internalCounters.push_back(48519);
        internalCounters.push_back(48915);
        internalCounters.push_back(49311);

        p.DefinePublicCounter("CBMemWritten", "ColorBuffer", "Number of bytes written to the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "550f8ff8-60b6-a6bf-87d0-25ac9e87de70" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(43510);
        internalCounters.push_back(43906);
        internalCounters.push_back(44302);
        internalCounters.push_back(44698);
        internalCounters.push_back(45094);
        internalCounters.push_back(45490);
        internalCounters.push_back(45886);
        internalCounters.push_back(46282);
        internalCounters.push_back(46678);
        internalCounters.push_back(47074);
        internalCounters.push_back(47470);
        internalCounters.push_back(47866);
        internalCounters.push_back(48262);
        internalCounters.push_back(48658);
        internalCounters.push_back(49054);
        internalCounters.push_back(49450);
        internalCounters.push_back(43369);
        internalCounters.push_back(43765);
        internalCounters.push_back(44161);
        internalCounters.push_back(44557);
        internalCounters.push_back(44953);
        internalCounters.push_back(45349);
        internalCounters.push_back(45745);
        internalCounters.push_back(46141);
        internalCounters.push_back(46537);
        internalCounters.push_back(46933);
        internalCounters.push_back(47329);
        internalCounters.push_back(47725);
        internalCounters.push_back(48121);
        internalCounters.push_back(48517);
        internalCounters.push_back(48913);
        internalCounters.push_back(49309);
        internalCounters.push_back(43370);
        internalCounters.push_back(43766);
        internalCounters.push_back(44162);
        internalCounters.push_back(44558);
        internalCounters.push_back(44954);
        internalCounters.push_back(45350);
        internalCounters.push_back(45746);
        internalCounters.push_back(46142);
        internalCounters.push_back(46538);
        internalCounters.push_back(46934);
        internalCounters.push_back(47330);
        internalCounters.push_back(47726);
        internalCounters.push_back(48122);
        internalCounters.push_back(48518);
        internalCounters.push_back(48914);
        internalCounters.push_back(49310);
        internalCounters.push_back(43371);
        internalCounters.push_back(43767);
        internalCounters.push_back(44163);
        internalCounters.push_back(44559);
        internalCounters.push_back(44955);
        internalCounters.push_back(45351);
        internalCounters.push_back(45747);
        internalCounters.push_back(46143);
        internalCounters.push_back(46539);
        internalCounters.push_back(46935);
        internalCounters.push_back(47331);
        internalCounters.push_back(47727);
        internalCounters.push_back(48123);
        internalCounters.push_back(48519);
        internalCounters.push_back(48915);
        internalCounters.push_back(49311);

        p.DefinePublicCounter("CBColorAndMaskWritten", "ColorBuffer", "Total number of bytes written to the color and mask buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*", "29a04b69-8f5f-b770-a0f2-3453e2c99e49" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(43415);
        internalCounters.push_back(43811);
        internalCounters.push_back(44207);
        internalCounters.push_back(44603);
        internalCounters.push_back(44999);
        internalCounters.push_back(45395);
        internalCounters.push_back(45791);
        internalCounters.push_back(46187);
        internalCounters.push_back(46583);
        internalCounters.push_back(46979);
        internalCounters.push_back(47375);
        internalCounters.push_back(47771);
        internalCounters.push_back(48167);
        internalCounters.push_back(48563);
        internalCounters.push_back(48959);
        internalCounters.push_back(49355);
        internalCounters.push_back(43260);
        internalCounters.push_back(43656);
        internalCounters.push_back(44052);
        internalCounters.push_back(44448);
        internalCounters.push_back(44844);
        internalCounters.push_back(45240);
        internalCounters.push_back(45636);
        internalCounters.push_back(46032);
        internalCounters.push_back(46428);
        internalCounters.push_back(46824);
        internalCounters.push_back(47220);
        internalCounters.push_back(47616);
        internalCounters.push_back(48012);
        internalCounters.push_back(48408);
        internalCounters.push_back(48804);
        internalCounters.push_back(49200);

        p.DefinePublicCounter("CBSlowPixelPct", "ColorBuffer", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*,(100),min", "5775943f-0313-7e52-9638-b24a449197bc" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(43415);
        internalCounters.push_back(43811);
        internalCounters.push_back(44207);
        internalCounters.push_back(44603);
        internalCounters.push_back(44999);
        internalCounters.push_back(45395);
        internalCounters.push_back(45791);
        internalCounters.push_back(46187);
        internalCounters.push_back(46583);
        internalCounters.push_back(46979);
        internalCounters.push_back(47375);
        internalCounters.push_back(47771);
        internalCounters.push_back(48167);
        internalCounters.push_back(48563);
        internalCounters.push_back(48959);
        internalCounters.push_back(49355);

        p.DefinePublicCounter("CBSlowPixelCount", "ColorBuffer", "Number of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "47eacbb0-28c8-22b4-5c69-c00d5813bb1c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(36034);
        internalCounters.push_back(36226);
        internalCounters.push_back(36418);
        internalCounters.push_back(36610);
        internalCounters.push_back(36802);
        internalCounters.push_back(36994);
        internalCounters.push_back(37186);
        internalCounters.push_back(37378);
        internalCounters.push_back(37570);
        internalCounters.push_back(37762);
        internalCounters.push_back(37954);
        internalCounters.push_back(38146);
        internalCounters.push_back(38338);
        internalCounters.push_back(38530);
        internalCounters.push_back(38722);
        internalCounters.push_back(38914);

        p.DefinePublicCounter("FetchSize", "GlobalMemory", "The total bytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "664bb3ef-6eca-86b1-1e2d-30cb897b5fa9" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(36025);
        internalCounters.push_back(36217);
        internalCounters.push_back(36409);
        internalCounters.push_back(36601);
        internalCounters.push_back(36793);
        internalCounters.push_back(36985);
        internalCounters.push_back(37177);
        internalCounters.push_back(37369);
        internalCounters.push_back(37561);
        internalCounters.push_back(37753);
        internalCounters.push_back(37945);
        internalCounters.push_back(38137);
        internalCounters.push_back(38329);
        internalCounters.push_back(38521);
        internalCounters.push_back(38713);
        internalCounters.push_back(38905);

        p.DefinePublicCounter("WriteSize", "GlobalMemory", "The total bytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "f96f2c16-b1b4-4ec4-229c-fc82e6f80a82" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(36017);
        internalCounters.push_back(36209);
        internalCounters.push_back(36401);
        internalCounters.push_back(36593);
        internalCounters.push_back(36785);
        internalCounters.push_back(36977);
        internalCounters.push_back(37169);
        internalCounters.push_back(37361);
        internalCounters.push_back(37553);
        internalCounters.push_back(37745);
        internalCounters.push_back(37937);
        internalCounters.push_back(38129);
        internalCounters.push_back(38321);
        internalCounters.push_back(38513);
        internalCounters.push_back(38705);
        internalCounters.push_back(38897);
        internalCounters.push_back(36018);
        internalCounters.push_back(36210);
        internalCounters.push_back(36402);
        internalCounters.push_back(36594);
        internalCounters.push_back(36786);
        internalCounters.push_back(36978);
        internalCounters.push_back(37170);
        internalCounters.push_back(37362);
        internalCounters.push_back(37554);
        internalCounters.push_back(37746);
        internalCounters.push_back(37938);
        internalCounters.push_back(38130);
        internalCounters.push_back(38322);
        internalCounters.push_back(38514);
        internalCounters.push_back(38706);
        internalCounters.push_back(38898);

        p.DefinePublicCounter("CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "dfbeebab-f7c1-1211-e502-4aae361e2ad7" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(36017);
        internalCounters.push_back(36209);
        internalCounters.push_back(36401);
        internalCounters.push_back(36593);
        internalCounters.push_back(36785);
        internalCounters.push_back(36977);
        internalCounters.push_back(37169);
        internalCounters.push_back(37361);
        internalCounters.push_back(37553);
        internalCounters.push_back(37745);
        internalCounters.push_back(37937);
        internalCounters.push_back(38129);
        internalCounters.push_back(38321);
        internalCounters.push_back(38513);
        internalCounters.push_back(38705);
        internalCounters.push_back(38897);
        internalCounters.push_back(36018);
        internalCounters.push_back(36210);
        internalCounters.push_back(36402);
        internalCounters.push_back(36594);
        internalCounters.push_back(36786);
        internalCounters.push_back(36978);
        internalCounters.push_back(37170);
        internalCounters.push_back(37362);
        internalCounters.push_back(37554);
        internalCounters.push_back(37746);
        internalCounters.push_back(37938);
        internalCounters.push_back(38130);
        internalCounters.push_back(38322);
        internalCounters.push_back(38514);
        internalCounters.push_back(38706);
        internalCounters.push_back(38898);

        p.DefinePublicCounter("CacheMiss", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that miss the data cache. Value range: 0% (optimal) to 100% (all miss).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "aebc0a53-7f87-60bd-4c4b-2b956846ef83" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(36017);
        internalCounters.push_back(36209);
        internalCounters.push_back(36401);
        internalCounters.push_back(36593);
        internalCounters.push_back(36785);
        internalCounters.push_back(36977);
        internalCounters.push_back(37169);
        internalCounters.push_back(37361);
        internalCounters.push_back(37553);
        internalCounters.push_back(37745);
        internalCounters.push_back(37937);
        internalCounters.push_back(38129);
        internalCounters.push_back(38321);
        internalCounters.push_back(38513);
        internalCounters.push_back(38705);
        internalCounters.push_back(38897);

        p.DefinePublicCounter("CacheHitCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that hit the data cache.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "43437652-1024-9737-2eb0-0899c0c1feae" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(36018);
        internalCounters.push_back(36210);
        internalCounters.push_back(36402);
        internalCounters.push_back(36594);
        internalCounters.push_back(36786);
        internalCounters.push_back(36978);
        internalCounters.push_back(37170);
        internalCounters.push_back(37362);
        internalCounters.push_back(37554);
        internalCounters.push_back(37746);
        internalCounters.push_back(37938);
        internalCounters.push_back(38130);
        internalCounters.push_back(38322);
        internalCounters.push_back(38514);
        internalCounters.push_back(38706);
        internalCounters.push_back(38898);

        p.DefinePublicCounter("CacheMissCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that miss the data cache.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "d0f8a812-f41b-644f-09d1-14ee03ea3671" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13358);
        internalCounters.push_back(13477);
        internalCounters.push_back(13596);
        internalCounters.push_back(13715);
        internalCounters.push_back(13834);
        internalCounters.push_back(13953);
        internalCounters.push_back(14072);
        internalCounters.push_back(14191);
        internalCounters.push_back(14310);
        internalCounters.push_back(14429);
        internalCounters.push_back(14548);
        internalCounters.push_back(14667);
        internalCounters.push_back(14786);
        internalCounters.push_back(14905);
        internalCounters.push_back(15024);
        internalCounters.push_back(15143);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(24482);
        internalCounters.push_back(24662);
        internalCounters.push_back(24842);
        internalCounters.push_back(25022);
        internalCounters.push_back(25202);
        internalCounters.push_back(25382);
        internalCounters.push_back(25562);
        internalCounters.push_back(25742);
        internalCounters.push_back(25922);
        internalCounters.push_back(26102);
        internalCounters.push_back(26282);
        internalCounters.push_back(26462);
        internalCounters.push_back(26642);
        internalCounters.push_back(26822);
        internalCounters.push_back(27002);
        internalCounters.push_back(27182);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(36027);
        internalCounters.push_back(36219);
        internalCounters.push_back(36411);
        internalCounters.push_back(36603);
        internalCounters.push_back(36795);
        internalCounters.push_back(36987);
        internalCounters.push_back(37179);
        internalCounters.push_back(37371);
        internalCounters.push_back(37563);
        internalCounters.push_back(37755);
        internalCounters.push_back(37947);
        internalCounters.push_back(38139);
        internalCounters.push_back(38331);
        internalCounters.push_back(38523);
        internalCounters.push_back(38715);
        internalCounters.push_back(38907);
        internalCounters.push_back(49739);

        p.DefinePublicCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, GPA_COUNTER_TYPE_DYNAMIC, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72" );
    }
}

