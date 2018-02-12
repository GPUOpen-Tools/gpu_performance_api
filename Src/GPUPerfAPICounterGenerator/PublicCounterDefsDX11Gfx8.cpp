//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for DX11GFX8
//==============================================================================

#include "PublicCounterDefsDX11Gfx8.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

void AutoDefinePublicCountersDX11Gfx8(GPA_PublicCounters& p)
{
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(51132);

        p.DefinePublicCounter("GPUTime", "Timing", "Time this API call took to execute on the GPU in milliseconds. Does not include time that draw calls are processed in parallel.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "0,TS_FREQ,/,(1000),*", "00bfa9cd-5512-48e8-7055-7b592113b8cb" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10620);
        internalCounters.push_back(10618);

        p.DefinePublicCounter("GPUBusy", "Timing", "The percentage of time GPU was busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,/,(100),*,(100),min", "bef38bf3-1167-0844-81f0-67d2d28ddbc5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10620);

        p.DefinePublicCounter("GPUBusyCycles", "Timing", "Number of GPU cycles that the GPU was busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0", "1e84970d-7014-2b8d-d61e-388b5f782691" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(49502);
        internalCounters.push_back(49649);
        internalCounters.push_back(49796);
        internalCounters.push_back(49943);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("TessellatorBusy", "Timing", "The percentage of time the tessellation engine is busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,/,(100),*", "36af6c72-dcfb-8102-4fd4-ce8ddc573365" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(49502);
        internalCounters.push_back(49649);
        internalCounters.push_back(49796);
        internalCounters.push_back(49943);

        p.DefinePublicCounter("TessellatorBusyCycles", "Timing", "Number of GPU cycles that the tessellation engine is busy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max", "60289dcb-7b33-46e7-26d1-8a2121605543" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13056);
        internalCounters.push_back(13253);
        internalCounters.push_back(13450);
        internalCounters.push_back(13647);
        internalCounters.push_back(13081);
        internalCounters.push_back(13278);
        internalCounters.push_back(13475);
        internalCounters.push_back(13672);
        internalCounters.push_back(13103);
        internalCounters.push_back(13300);
        internalCounters.push_back(13497);
        internalCounters.push_back(13694);
        internalCounters.push_back(13125);
        internalCounters.push_back(13322);
        internalCounters.push_back(13519);
        internalCounters.push_back(13716);
        internalCounters.push_back(13065);
        internalCounters.push_back(13262);
        internalCounters.push_back(13459);
        internalCounters.push_back(13656);
        internalCounters.push_back(13087);
        internalCounters.push_back(13284);
        internalCounters.push_back(13481);
        internalCounters.push_back(13678);
        internalCounters.push_back(13109);
        internalCounters.push_back(13306);
        internalCounters.push_back(13503);
        internalCounters.push_back(13700);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("VSBusy", "Timing", "The percentage of time the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,16,ifnotzero,4,20,ifnotzero,8,24,ifnotzero,(0),1,17,ifnotzero,5,21,ifnotzero,9,25,ifnotzero,max,(0),2,18,ifnotzero,6,22,ifnotzero,10,26,ifnotzero,max,(0),3,19,ifnotzero,7,23,ifnotzero,11,27,ifnotzero,max,28,/,(100),*,(100),min", "94caad5e-867c-6c09-cf3a-d05b51df8f3b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13056);
        internalCounters.push_back(13253);
        internalCounters.push_back(13450);
        internalCounters.push_back(13647);
        internalCounters.push_back(13081);
        internalCounters.push_back(13278);
        internalCounters.push_back(13475);
        internalCounters.push_back(13672);
        internalCounters.push_back(13103);
        internalCounters.push_back(13300);
        internalCounters.push_back(13497);
        internalCounters.push_back(13694);
        internalCounters.push_back(13125);
        internalCounters.push_back(13322);
        internalCounters.push_back(13519);
        internalCounters.push_back(13716);
        internalCounters.push_back(13065);
        internalCounters.push_back(13262);
        internalCounters.push_back(13459);
        internalCounters.push_back(13656);
        internalCounters.push_back(13087);
        internalCounters.push_back(13284);
        internalCounters.push_back(13481);
        internalCounters.push_back(13678);
        internalCounters.push_back(13109);
        internalCounters.push_back(13306);
        internalCounters.push_back(13503);
        internalCounters.push_back(13700);

        p.DefinePublicCounter("VSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has vertex shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,16,ifnotzero,4,20,ifnotzero,8,24,ifnotzero,(0),1,17,ifnotzero,5,21,ifnotzero,9,25,ifnotzero,max,(0),2,18,ifnotzero,6,22,ifnotzero,10,26,ifnotzero,max,(0),3,19,ifnotzero,7,23,ifnotzero,11,27,ifnotzero,max", "a2086d4e-274b-48a8-3e08-a4ab76ac15dd" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(51132);
        internalCounters.push_back(13056);
        internalCounters.push_back(13253);
        internalCounters.push_back(13450);
        internalCounters.push_back(13647);
        internalCounters.push_back(13081);
        internalCounters.push_back(13278);
        internalCounters.push_back(13475);
        internalCounters.push_back(13672);
        internalCounters.push_back(13103);
        internalCounters.push_back(13300);
        internalCounters.push_back(13497);
        internalCounters.push_back(13694);
        internalCounters.push_back(13125);
        internalCounters.push_back(13322);
        internalCounters.push_back(13519);
        internalCounters.push_back(13716);
        internalCounters.push_back(13065);
        internalCounters.push_back(13262);
        internalCounters.push_back(13459);
        internalCounters.push_back(13656);
        internalCounters.push_back(13087);
        internalCounters.push_back(13284);
        internalCounters.push_back(13481);
        internalCounters.push_back(13678);
        internalCounters.push_back(13109);
        internalCounters.push_back(13306);
        internalCounters.push_back(13503);
        internalCounters.push_back(13700);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("VSTime", "Timing", "Time vertex shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "(0),1,17,ifnotzero,5,21,ifnotzero,9,25,ifnotzero,(0),2,18,ifnotzero,6,22,ifnotzero,10,26,ifnotzero,max,(0),3,19,ifnotzero,7,23,ifnotzero,11,27,ifnotzero,max,(0),4,20,ifnotzero,8,24,ifnotzero,12,28,ifnotzero,max,29,/,(1),min,0,TS_FREQ,/,(1000),*,*", "fee660c7-8e01-4dc5-e5d0-fcb61c17fb2c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13093);
        internalCounters.push_back(13290);
        internalCounters.push_back(13487);
        internalCounters.push_back(13684);
        internalCounters.push_back(13099);
        internalCounters.push_back(13296);
        internalCounters.push_back(13493);
        internalCounters.push_back(13690);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("HSBusy", "Timing", "The percentage of time the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,8,/,(100),*,(100),min", "16f30a0b-4cbf-eccd-b13f-ab68dd254d32" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13093);
        internalCounters.push_back(13290);
        internalCounters.push_back(13487);
        internalCounters.push_back(13684);
        internalCounters.push_back(13099);
        internalCounters.push_back(13296);
        internalCounters.push_back(13493);
        internalCounters.push_back(13690);

        p.DefinePublicCounter("HSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has hull shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max", "753e76ef-8ef8-3f13-b511-4bd9f3589fdb" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(51132);
        internalCounters.push_back(13093);
        internalCounters.push_back(13290);
        internalCounters.push_back(13487);
        internalCounters.push_back(13684);
        internalCounters.push_back(13099);
        internalCounters.push_back(13296);
        internalCounters.push_back(13493);
        internalCounters.push_back(13690);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("HSTime", "Timing", "Time hull shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "(0),1,5,ifnotzero,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,(0),4,8,ifnotzero,max,9,/,(1),min,0,TS_FREQ,/,(1000),*,*", "8792e9f1-fb39-b92a-b230-f33df4c8a0de" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13056);
        internalCounters.push_back(13253);
        internalCounters.push_back(13450);
        internalCounters.push_back(13647);
        internalCounters.push_back(13081);
        internalCounters.push_back(13278);
        internalCounters.push_back(13475);
        internalCounters.push_back(13672);
        internalCounters.push_back(13125);
        internalCounters.push_back(13322);
        internalCounters.push_back(13519);
        internalCounters.push_back(13716);
        internalCounters.push_back(13087);
        internalCounters.push_back(13284);
        internalCounters.push_back(13481);
        internalCounters.push_back(13678);
        internalCounters.push_back(13109);
        internalCounters.push_back(13306);
        internalCounters.push_back(13503);
        internalCounters.push_back(13700);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("DSBusy", "Timing", "The percentage of time the ShaderUnit has domain shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,4,12,ifnotzero,16,ifnotzero,(0),1,5,13,ifnotzero,17,ifnotzero,max,(0),2,6,14,ifnotzero,18,ifnotzero,max,(0),3,7,15,ifnotzero,19,ifnotzero,max,20,/,(100),*,(100),min", "0c626e8a-9b82-b6d4-d9a3-578509316301" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13056);
        internalCounters.push_back(13253);
        internalCounters.push_back(13450);
        internalCounters.push_back(13647);
        internalCounters.push_back(13081);
        internalCounters.push_back(13278);
        internalCounters.push_back(13475);
        internalCounters.push_back(13672);
        internalCounters.push_back(13125);
        internalCounters.push_back(13322);
        internalCounters.push_back(13519);
        internalCounters.push_back(13716);
        internalCounters.push_back(13087);
        internalCounters.push_back(13284);
        internalCounters.push_back(13481);
        internalCounters.push_back(13678);
        internalCounters.push_back(13109);
        internalCounters.push_back(13306);
        internalCounters.push_back(13503);
        internalCounters.push_back(13700);

        p.DefinePublicCounter("DSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has domain shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,4,12,ifnotzero,16,ifnotzero,(0),1,5,13,ifnotzero,17,ifnotzero,max,(0),2,6,14,ifnotzero,18,ifnotzero,max,(0),3,7,15,ifnotzero,19,ifnotzero,max", "2f3f7561-0549-2232-536d-129ffc5f7703" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(51132);
        internalCounters.push_back(13056);
        internalCounters.push_back(13253);
        internalCounters.push_back(13450);
        internalCounters.push_back(13647);
        internalCounters.push_back(13081);
        internalCounters.push_back(13278);
        internalCounters.push_back(13475);
        internalCounters.push_back(13672);
        internalCounters.push_back(13125);
        internalCounters.push_back(13322);
        internalCounters.push_back(13519);
        internalCounters.push_back(13716);
        internalCounters.push_back(13087);
        internalCounters.push_back(13284);
        internalCounters.push_back(13481);
        internalCounters.push_back(13678);
        internalCounters.push_back(13109);
        internalCounters.push_back(13306);
        internalCounters.push_back(13503);
        internalCounters.push_back(13700);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("DSTime", "Timing", "Time domain shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "(0),1,5,13,ifnotzero,17,ifnotzero,(0),2,6,14,ifnotzero,18,ifnotzero,max,(0),3,7,15,ifnotzero,19,ifnotzero,max,(0),4,8,16,ifnotzero,20,ifnotzero,max,21,/,(1),min,0,TS_FREQ,/,(1000),*,*", "f050e495-f511-ecc9-9c46-c96516bddeb2" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13072);
        internalCounters.push_back(13269);
        internalCounters.push_back(13466);
        internalCounters.push_back(13663);
        internalCounters.push_back(13075);
        internalCounters.push_back(13272);
        internalCounters.push_back(13469);
        internalCounters.push_back(13666);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("GSBusy", "Timing", "The percentage of time the ShaderUnit has geometry shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,8,/,(100),*,(100),min", "876f36d8-d046-833f-7832-673cbffd0a45" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13072);
        internalCounters.push_back(13269);
        internalCounters.push_back(13466);
        internalCounters.push_back(13663);
        internalCounters.push_back(13075);
        internalCounters.push_back(13272);
        internalCounters.push_back(13469);
        internalCounters.push_back(13666);

        p.DefinePublicCounter("GSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has geometry shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max", "48203b6b-8983-c067-d63e-05da8be5111b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(51132);
        internalCounters.push_back(13072);
        internalCounters.push_back(13269);
        internalCounters.push_back(13466);
        internalCounters.push_back(13663);
        internalCounters.push_back(13075);
        internalCounters.push_back(13272);
        internalCounters.push_back(13469);
        internalCounters.push_back(13666);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("GSTime", "Timing", "Time geometry shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "(0),1,5,ifnotzero,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,(0),4,8,ifnotzero,max,9,/,(1),min,0,TS_FREQ,/,(1000),*,*", "86d56794-f391-b601-9388-851b646d346c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13125);
        internalCounters.push_back(13322);
        internalCounters.push_back(13519);
        internalCounters.push_back(13716);
        internalCounters.push_back(13130);
        internalCounters.push_back(13327);
        internalCounters.push_back(13524);
        internalCounters.push_back(13721);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("PSBusy", "Timing", "The percentage of time the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,8,/,(100),*", "7e772beb-d82c-bd9a-aed0-fe504d416ce5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13125);
        internalCounters.push_back(13322);
        internalCounters.push_back(13519);
        internalCounters.push_back(13716);
        internalCounters.push_back(13130);
        internalCounters.push_back(13327);
        internalCounters.push_back(13524);
        internalCounters.push_back(13721);

        p.DefinePublicCounter("PSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has pixel shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,4,ifnotzero,(0),1,5,ifnotzero,max,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max", "b58bea04-ce8e-2984-80f4-8aba7d4c817b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(51132);
        internalCounters.push_back(13125);
        internalCounters.push_back(13322);
        internalCounters.push_back(13519);
        internalCounters.push_back(13716);
        internalCounters.push_back(13130);
        internalCounters.push_back(13327);
        internalCounters.push_back(13524);
        internalCounters.push_back(13721);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("PSTime", "Timing", "Time pixel shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "(0),1,5,ifnotzero,(0),2,6,ifnotzero,max,(0),3,7,ifnotzero,max,(0),4,8,ifnotzero,max,9,/,0,TS_FREQ,/,(1000),*,*", "f564ee00-ffcf-f7f6-fcbf-f200205cd0cc" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13113);
        internalCounters.push_back(13310);
        internalCounters.push_back(13507);
        internalCounters.push_back(13704);
        internalCounters.push_back(13117);
        internalCounters.push_back(13314);
        internalCounters.push_back(13511);
        internalCounters.push_back(13708);
        internalCounters.push_back(13119);
        internalCounters.push_back(13316);
        internalCounters.push_back(13513);
        internalCounters.push_back(13710);
        internalCounters.push_back(13123);
        internalCounters.push_back(13320);
        internalCounters.push_back(13517);
        internalCounters.push_back(13714);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("CSBusy", "Timing", "The percentage of time the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,comparemax4,8,9,10,11,12,13,14,15,comparemax4,max,16,/,(100),*,(100),min", "493fdd90-8d2b-a055-5e4e-2d29c3396b8c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13113);
        internalCounters.push_back(13310);
        internalCounters.push_back(13507);
        internalCounters.push_back(13704);
        internalCounters.push_back(13117);
        internalCounters.push_back(13314);
        internalCounters.push_back(13511);
        internalCounters.push_back(13708);
        internalCounters.push_back(13119);
        internalCounters.push_back(13316);
        internalCounters.push_back(13513);
        internalCounters.push_back(13710);
        internalCounters.push_back(13123);
        internalCounters.push_back(13320);
        internalCounters.push_back(13517);
        internalCounters.push_back(13714);

        p.DefinePublicCounter("CSBusyCycles", "Timing", "Number of GPU cycles that the ShaderUnit has compute shader work to do.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,comparemax4,8,9,10,11,12,13,14,15,comparemax4,max", "39bcf1b8-f6b2-4c37-f9af-0a2bb59512f9" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(51132);
        internalCounters.push_back(13113);
        internalCounters.push_back(13310);
        internalCounters.push_back(13507);
        internalCounters.push_back(13704);
        internalCounters.push_back(13117);
        internalCounters.push_back(13314);
        internalCounters.push_back(13511);
        internalCounters.push_back(13708);
        internalCounters.push_back(13119);
        internalCounters.push_back(13316);
        internalCounters.push_back(13513);
        internalCounters.push_back(13710);
        internalCounters.push_back(13123);
        internalCounters.push_back(13320);
        internalCounters.push_back(13517);
        internalCounters.push_back(13714);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("CSTime", "Timing", "Time compute shaders are busy in milliseconds.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS, internalCounters, "1,2,3,4,5,6,7,8,comparemax4,9,10,11,12,13,14,15,16,comparemax4,max,17,/,(1),min,0,TS_FREQ,/,(1000),*,*", "5177faaf-f59d-ee23-6e36-0ea087dca9dc" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(49398);
        internalCounters.push_back(49545);
        internalCounters.push_back(49692);
        internalCounters.push_back(49839);
        internalCounters.push_back(49379);
        internalCounters.push_back(49526);
        internalCounters.push_back(49673);
        internalCounters.push_back(49820);
        internalCounters.push_back(49474);
        internalCounters.push_back(49621);
        internalCounters.push_back(49768);
        internalCounters.push_back(49915);

        p.DefinePublicCounter("VSVerticesIn", "VertexShader", "The number of vertices processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,4,5,6,7,sum4,ifnotzero,8,9,10,11,sum4,8,9,10,11,sum4,ifnotzero", "810a04c8-2ff4-081d-766d-bfa2bd4ad916" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(17457);
        internalCounters.push_back(17756);
        internalCounters.push_back(18055);
        internalCounters.push_back(18354);
        internalCounters.push_back(17435);
        internalCounters.push_back(17734);
        internalCounters.push_back(18033);
        internalCounters.push_back(18332);
        internalCounters.push_back(15065);
        internalCounters.push_back(15364);
        internalCounters.push_back(15663);
        internalCounters.push_back(15962);
        internalCounters.push_back(15043);
        internalCounters.push_back(15342);
        internalCounters.push_back(15641);
        internalCounters.push_back(15940);
        internalCounters.push_back(15053);
        internalCounters.push_back(15352);
        internalCounters.push_back(15651);
        internalCounters.push_back(15950);
        internalCounters.push_back(19849);
        internalCounters.push_back(20148);
        internalCounters.push_back(20447);
        internalCounters.push_back(20746);
        internalCounters.push_back(19827);
        internalCounters.push_back(20126);
        internalCounters.push_back(20425);
        internalCounters.push_back(20724);
        internalCounters.push_back(19837);
        internalCounters.push_back(20136);
        internalCounters.push_back(20435);
        internalCounters.push_back(20734);

        p.DefinePublicCounter("VSVALUInstCount", "VertexShader", "Average number of vector ALU instructions executed in the VS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,12,13,14,15,sum4,/,16,17,18,19,sum4,ifnotzero,20,21,22,23,sum4,24,25,26,27,sum4,/,28,29,30,31,sum4,ifnotzero", "8ec604e4-63f5-e6b5-4558-c38f0b26d4b1" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(17461);
        internalCounters.push_back(17760);
        internalCounters.push_back(18059);
        internalCounters.push_back(18358);
        internalCounters.push_back(17435);
        internalCounters.push_back(17734);
        internalCounters.push_back(18033);
        internalCounters.push_back(18332);
        internalCounters.push_back(15069);
        internalCounters.push_back(15368);
        internalCounters.push_back(15667);
        internalCounters.push_back(15966);
        internalCounters.push_back(15043);
        internalCounters.push_back(15342);
        internalCounters.push_back(15641);
        internalCounters.push_back(15940);
        internalCounters.push_back(15053);
        internalCounters.push_back(15352);
        internalCounters.push_back(15651);
        internalCounters.push_back(15950);
        internalCounters.push_back(19853);
        internalCounters.push_back(20152);
        internalCounters.push_back(20451);
        internalCounters.push_back(20750);
        internalCounters.push_back(19827);
        internalCounters.push_back(20126);
        internalCounters.push_back(20425);
        internalCounters.push_back(20724);
        internalCounters.push_back(19837);
        internalCounters.push_back(20136);
        internalCounters.push_back(20435);
        internalCounters.push_back(20734);

        p.DefinePublicCounter("VSSALUInstCount", "VertexShader", "Average number of scalar ALU instructions executed in the VS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,12,13,14,15,sum4,/,16,17,18,19,sum4,ifnotzero,20,21,22,23,sum4,24,25,26,27,sum4,/,28,29,30,31,sum4,ifnotzero", "e3da0383-7322-7f65-8cf2-3ce641578e54" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(17512);
        internalCounters.push_back(17811);
        internalCounters.push_back(18110);
        internalCounters.push_back(18409);
        internalCounters.push_back(15120);
        internalCounters.push_back(15419);
        internalCounters.push_back(15718);
        internalCounters.push_back(16017);
        internalCounters.push_back(15053);
        internalCounters.push_back(15352);
        internalCounters.push_back(15651);
        internalCounters.push_back(15950);
        internalCounters.push_back(10620);
        internalCounters.push_back(19904);
        internalCounters.push_back(20203);
        internalCounters.push_back(20502);
        internalCounters.push_back(20801);
        internalCounters.push_back(19837);
        internalCounters.push_back(20136);
        internalCounters.push_back(20435);
        internalCounters.push_back(20734);

        p.DefinePublicCounter("VSVALUBusy", "VertexShader", "The percentage of GPUTime vector ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,ifnotzero,13,14,15,16,sum4,17,18,19,20,sum4,ifnotzero,(4),*,NUM_SIMDS,/,12,/,(100),*", "8b3572f7-fda0-eddf-6c93-2ab145b8754b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(17512);
        internalCounters.push_back(17811);
        internalCounters.push_back(18110);
        internalCounters.push_back(18409);
        internalCounters.push_back(15120);
        internalCounters.push_back(15419);
        internalCounters.push_back(15718);
        internalCounters.push_back(16017);
        internalCounters.push_back(15053);
        internalCounters.push_back(15352);
        internalCounters.push_back(15651);
        internalCounters.push_back(15950);
        internalCounters.push_back(19904);
        internalCounters.push_back(20203);
        internalCounters.push_back(20502);
        internalCounters.push_back(20801);
        internalCounters.push_back(19837);
        internalCounters.push_back(20136);
        internalCounters.push_back(20435);
        internalCounters.push_back(20734);

        p.DefinePublicCounter("VSVALUBusyCycles", "VertexShader", "Number of GPU cycles where vector ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,ifnotzero,12,13,14,15,sum4,16,17,18,19,sum4,ifnotzero,(4),*,NUM_SIMDS,/", "0af1686e-6d77-2f6e-2862-7bb8e869a776" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(17517);
        internalCounters.push_back(17816);
        internalCounters.push_back(18115);
        internalCounters.push_back(18414);
        internalCounters.push_back(15125);
        internalCounters.push_back(15424);
        internalCounters.push_back(15723);
        internalCounters.push_back(16022);
        internalCounters.push_back(15053);
        internalCounters.push_back(15352);
        internalCounters.push_back(15651);
        internalCounters.push_back(15950);
        internalCounters.push_back(10620);
        internalCounters.push_back(19909);
        internalCounters.push_back(20208);
        internalCounters.push_back(20507);
        internalCounters.push_back(20806);
        internalCounters.push_back(19837);
        internalCounters.push_back(20136);
        internalCounters.push_back(20435);
        internalCounters.push_back(20734);

        p.DefinePublicCounter("VSSALUBusy", "VertexShader", "The percentage of GPUTime scalar ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,ifnotzero,13,14,15,16,sum4,17,18,19,20,sum4,ifnotzero,(4),*,NUM_SIMDS,/,12,/,(100),*", "3bc8730c-e3bc-e2f0-7d24-36974064c25a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(17517);
        internalCounters.push_back(17816);
        internalCounters.push_back(18115);
        internalCounters.push_back(18414);
        internalCounters.push_back(15125);
        internalCounters.push_back(15424);
        internalCounters.push_back(15723);
        internalCounters.push_back(16022);
        internalCounters.push_back(15053);
        internalCounters.push_back(15352);
        internalCounters.push_back(15651);
        internalCounters.push_back(15950);
        internalCounters.push_back(19909);
        internalCounters.push_back(20208);
        internalCounters.push_back(20507);
        internalCounters.push_back(20806);
        internalCounters.push_back(19837);
        internalCounters.push_back(20136);
        internalCounters.push_back(20435);
        internalCounters.push_back(20734);

        p.DefinePublicCounter("VSSALUBusyCycles", "VertexShader", "Number of GPU cycles where scalar ALU instructions are being processed by the VS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,ifnotzero,12,13,14,15,sum4,16,17,18,19,sum4,ifnotzero,(4),*,NUM_SIMDS,/", "357ac7cd-2e1c-dcb0-77f6-37527237f35b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(49483);
        internalCounters.push_back(49630);
        internalCounters.push_back(49777);
        internalCounters.push_back(49924);

        p.DefinePublicCounter("HSPatches", "HullShader", "The number of patches processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "d1bbd27d-d591-4509-df52-d329fb73a98f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(21045);
        internalCounters.push_back(21344);
        internalCounters.push_back(21643);
        internalCounters.push_back(21942);
        internalCounters.push_back(21023);
        internalCounters.push_back(21322);
        internalCounters.push_back(21621);
        internalCounters.push_back(21920);

        p.DefinePublicCounter("HSVALUInstCount", "HullShader", "Average number of vector ALU instructions executed in the HS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/", "786673bf-d58f-9895-3a37-9d6efb5e5804" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(21049);
        internalCounters.push_back(21348);
        internalCounters.push_back(21647);
        internalCounters.push_back(21946);
        internalCounters.push_back(21023);
        internalCounters.push_back(21322);
        internalCounters.push_back(21621);
        internalCounters.push_back(21920);

        p.DefinePublicCounter("HSSALUInstCount", "HullShader", "Average number of scalar ALU instructions executed in the HS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/", "1af675c4-cb0b-c4c5-c131-2796750f683e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(21100);
        internalCounters.push_back(21399);
        internalCounters.push_back(21698);
        internalCounters.push_back(21997);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("HSVALUBusy", "HullShader", "The percentage of GPUTime vector ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/,4,/,(100),*", "7880d192-8015-0311-d43e-fb0b7a4df179" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(21100);
        internalCounters.push_back(21399);
        internalCounters.push_back(21698);
        internalCounters.push_back(21997);

        p.DefinePublicCounter("HSVALUBusyCycles", "HullShader", "Number of GPU cycles vector where ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/", "3afb94e4-e937-5730-0cc9-41d3113ba012" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(21105);
        internalCounters.push_back(21404);
        internalCounters.push_back(21703);
        internalCounters.push_back(22002);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("HSSALUBusy", "HullShader", "The percentage of GPUTime scalar ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/,4,/,(100),*", "34748a4b-9148-0b06-b7b9-5700d6631bde" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(21105);
        internalCounters.push_back(21404);
        internalCounters.push_back(21703);
        internalCounters.push_back(22002);

        p.DefinePublicCounter("HSSALUBusyCycles", "HullShader", "Number of GPU cycles where scalar ALU instructions are being processed by the HS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/", "9bceabf7-3f01-2fd9-7b1d-8fe46c729efc" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(49398);
        internalCounters.push_back(49545);
        internalCounters.push_back(49692);
        internalCounters.push_back(49839);
        internalCounters.push_back(49379);
        internalCounters.push_back(49526);
        internalCounters.push_back(49673);
        internalCounters.push_back(49820);
        internalCounters.push_back(49474);
        internalCounters.push_back(49621);
        internalCounters.push_back(49768);
        internalCounters.push_back(49915);

        p.DefinePublicCounter("DSVerticesIn", "DomainShader", "The number of vertices processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,4,5,6,7,sum4,ifnotzero,8,9,10,11,sum4,ifnotzero", "b88d9d05-2418-e639-4e3d-3a5815855f8d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(17457);
        internalCounters.push_back(17756);
        internalCounters.push_back(18055);
        internalCounters.push_back(18354);
        internalCounters.push_back(17435);
        internalCounters.push_back(17734);
        internalCounters.push_back(18033);
        internalCounters.push_back(18332);
        internalCounters.push_back(15065);
        internalCounters.push_back(15364);
        internalCounters.push_back(15663);
        internalCounters.push_back(15962);
        internalCounters.push_back(15043);
        internalCounters.push_back(15342);
        internalCounters.push_back(15641);
        internalCounters.push_back(15940);
        internalCounters.push_back(15053);
        internalCounters.push_back(15352);
        internalCounters.push_back(15651);
        internalCounters.push_back(15950);
        internalCounters.push_back(19837);
        internalCounters.push_back(20136);
        internalCounters.push_back(20435);
        internalCounters.push_back(20734);

        p.DefinePublicCounter("DSVALUInstCount", "DomainShader", "Average number of vector ALU instructions executed in the DS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,12,13,14,15,sum4,/,16,17,18,19,sum4,ifnotzero,20,21,22,23,sum4,ifnotzero", "03a3e949-82f9-be4d-7228-5eb5ad80915a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(17461);
        internalCounters.push_back(17760);
        internalCounters.push_back(18059);
        internalCounters.push_back(18358);
        internalCounters.push_back(17435);
        internalCounters.push_back(17734);
        internalCounters.push_back(18033);
        internalCounters.push_back(18332);
        internalCounters.push_back(15069);
        internalCounters.push_back(15368);
        internalCounters.push_back(15667);
        internalCounters.push_back(15966);
        internalCounters.push_back(15043);
        internalCounters.push_back(15342);
        internalCounters.push_back(15641);
        internalCounters.push_back(15940);
        internalCounters.push_back(15053);
        internalCounters.push_back(15352);
        internalCounters.push_back(15651);
        internalCounters.push_back(15950);
        internalCounters.push_back(19837);
        internalCounters.push_back(20136);
        internalCounters.push_back(20435);
        internalCounters.push_back(20734);

        p.DefinePublicCounter("DSSALUInstCount", "DomainShader", "Average number of scalar ALU instructions executed in the DS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,sum4,12,13,14,15,sum4,/,16,17,18,19,sum4,ifnotzero,20,21,22,23,sum4,ifnotzero", "73daa728-483e-95d0-5b40-504719aadc1c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(17512);
        internalCounters.push_back(17811);
        internalCounters.push_back(18110);
        internalCounters.push_back(18409);
        internalCounters.push_back(15120);
        internalCounters.push_back(15419);
        internalCounters.push_back(15718);
        internalCounters.push_back(16017);
        internalCounters.push_back(10620);
        internalCounters.push_back(15053);
        internalCounters.push_back(15352);
        internalCounters.push_back(15651);
        internalCounters.push_back(15950);
        internalCounters.push_back(19837);
        internalCounters.push_back(20136);
        internalCounters.push_back(20435);
        internalCounters.push_back(20734);

        p.DefinePublicCounter("DSVALUBusy", "DomainShader", "The percentage of GPUTime vector ALU instructions are being processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,9,10,11,12,sum4,ifnotzero,13,14,15,16,sum4,ifnotzero,(4),*,NUM_SIMDS,/,8,/,(100),*", "ddc0dd0c-0c73-b831-a410-cfea8b9713d9" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(17512);
        internalCounters.push_back(17811);
        internalCounters.push_back(18110);
        internalCounters.push_back(18409);
        internalCounters.push_back(15120);
        internalCounters.push_back(15419);
        internalCounters.push_back(15718);
        internalCounters.push_back(16017);
        internalCounters.push_back(15053);
        internalCounters.push_back(15352);
        internalCounters.push_back(15651);
        internalCounters.push_back(15950);
        internalCounters.push_back(19837);
        internalCounters.push_back(20136);
        internalCounters.push_back(20435);
        internalCounters.push_back(20734);

        p.DefinePublicCounter("DSVALUBusyCycles", "DomainShader", "Number of GPU cycles where vector ALU instructions are being processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,ifnotzero,12,13,14,15,sum4,ifnotzero,(4),*,NUM_SIMDS,/", "1e280912-81ee-a684-823b-94c468d8ebda" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(17517);
        internalCounters.push_back(17816);
        internalCounters.push_back(18115);
        internalCounters.push_back(18414);
        internalCounters.push_back(15125);
        internalCounters.push_back(15424);
        internalCounters.push_back(15723);
        internalCounters.push_back(16022);
        internalCounters.push_back(10620);
        internalCounters.push_back(15053);
        internalCounters.push_back(15352);
        internalCounters.push_back(15651);
        internalCounters.push_back(15950);
        internalCounters.push_back(19837);
        internalCounters.push_back(20136);
        internalCounters.push_back(20435);
        internalCounters.push_back(20734);

        p.DefinePublicCounter("DSSALUBusy", "DomainShader", "The percentage of GPUTime scalar ALU instructions are being processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,9,10,11,12,sum4,ifnotzero,13,14,15,16,sum4,ifnotzero,(4),*,NUM_SIMDS,/,8,/,(100),*", "b639f64c-24af-348f-6439-43c701b4fc07" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(17517);
        internalCounters.push_back(17816);
        internalCounters.push_back(18115);
        internalCounters.push_back(18414);
        internalCounters.push_back(15125);
        internalCounters.push_back(15424);
        internalCounters.push_back(15723);
        internalCounters.push_back(16022);
        internalCounters.push_back(15053);
        internalCounters.push_back(15352);
        internalCounters.push_back(15651);
        internalCounters.push_back(15950);
        internalCounters.push_back(19837);
        internalCounters.push_back(20136);
        internalCounters.push_back(20435);
        internalCounters.push_back(20734);

        p.DefinePublicCounter("DSSALUBusyCycles", "DomainShader", "Number of GPU cycles where scalar ALU instructions are being processed by the DS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,ifnotzero,12,13,14,15,sum4,ifnotzero,(4),*,NUM_SIMDS,/", "b5bf8a0c-e682-1aa6-23d7-c6c6784ffa5c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(49387);
        internalCounters.push_back(49534);
        internalCounters.push_back(49681);
        internalCounters.push_back(49828);

        p.DefinePublicCounter("GSPrimsIn", "GeometryShader", "The number of primitives passed into the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "20c29866-509a-aaab-2697-6b2c38f79953" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(49398);
        internalCounters.push_back(49545);
        internalCounters.push_back(49692);
        internalCounters.push_back(49839);
        internalCounters.push_back(49379);
        internalCounters.push_back(49526);
        internalCounters.push_back(49673);
        internalCounters.push_back(49820);

        p.DefinePublicCounter("GSVerticesOut", "GeometryShader", "The number of vertices output by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,ifnotzero", "775b9736-319a-bd8a-48c9-68db9c91d978" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16261);
        internalCounters.push_back(16560);
        internalCounters.push_back(16859);
        internalCounters.push_back(17158);
        internalCounters.push_back(16239);
        internalCounters.push_back(16538);
        internalCounters.push_back(16837);
        internalCounters.push_back(17136);

        p.DefinePublicCounter("GSVALUInstCount", "GeometryShader", "Average number of vector ALU instructions executed in the GS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/", "21b12bfa-b8cd-2e71-a2d5-f9e9f1d65d61" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16265);
        internalCounters.push_back(16564);
        internalCounters.push_back(16863);
        internalCounters.push_back(17162);
        internalCounters.push_back(16239);
        internalCounters.push_back(16538);
        internalCounters.push_back(16837);
        internalCounters.push_back(17136);

        p.DefinePublicCounter("GSSALUInstCount", "GeometryShader", "Average number of scalar ALU instructions executed in the GS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/", "a8562594-d335-ca43-61bf-03b72d2b98a5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16316);
        internalCounters.push_back(16615);
        internalCounters.push_back(16914);
        internalCounters.push_back(17213);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("GSVALUBusy", "GeometryShader", "The percentage of GPUTime vector ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/,4,/,(100),*", "228a4818-1e56-cebb-0720-3b2cdc057a6f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16316);
        internalCounters.push_back(16615);
        internalCounters.push_back(16914);
        internalCounters.push_back(17213);

        p.DefinePublicCounter("GSVALUBusyCycles", "GeometryShader", "Number of GPU cycles where vector ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/", "be217edd-226f-bd97-9a48-46e2809b1933" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16321);
        internalCounters.push_back(16620);
        internalCounters.push_back(16919);
        internalCounters.push_back(17218);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("GSSALUBusy", "GeometryShader", "The percentage of GPUTime scalar ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,4,/,(100),*", "f28ce300-800e-9822-39e4-f48528bdb935" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(16321);
        internalCounters.push_back(16620);
        internalCounters.push_back(16919);
        internalCounters.push_back(17218);

        p.DefinePublicCounter("GSSALUBusyCycles", "GeometryShader", "Number of GPU cycles where scalar ALU instructions are being processed by the GS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "b3eace7c-3bc4-0107-887f-923851dc8ea7" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10824);
        internalCounters.push_back(10977);
        internalCounters.push_back(11130);
        internalCounters.push_back(11283);
        internalCounters.push_back(10828);
        internalCounters.push_back(10981);
        internalCounters.push_back(11134);
        internalCounters.push_back(11287);
        internalCounters.push_back(10780);
        internalCounters.push_back(10933);
        internalCounters.push_back(11086);
        internalCounters.push_back(11239);
        internalCounters.push_back(10792);
        internalCounters.push_back(10945);
        internalCounters.push_back(11098);
        internalCounters.push_back(11251);
        internalCounters.push_back(10781);
        internalCounters.push_back(10934);
        internalCounters.push_back(11087);
        internalCounters.push_back(11240);
        internalCounters.push_back(10793);
        internalCounters.push_back(10946);
        internalCounters.push_back(11099);
        internalCounters.push_back(11252);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("PrimitiveAssemblyBusy", "Timing", "The percentage of GPUTime that primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max,24,/,(100),*,(100),min", "54ac5640-c4d7-95e2-20e0-6a9fdfc07333" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10824);
        internalCounters.push_back(10977);
        internalCounters.push_back(11130);
        internalCounters.push_back(11283);
        internalCounters.push_back(10828);
        internalCounters.push_back(10981);
        internalCounters.push_back(11134);
        internalCounters.push_back(11287);
        internalCounters.push_back(10780);
        internalCounters.push_back(10933);
        internalCounters.push_back(11086);
        internalCounters.push_back(11239);
        internalCounters.push_back(10792);
        internalCounters.push_back(10945);
        internalCounters.push_back(11098);
        internalCounters.push_back(11251);
        internalCounters.push_back(10781);
        internalCounters.push_back(10934);
        internalCounters.push_back(11087);
        internalCounters.push_back(11240);
        internalCounters.push_back(10793);
        internalCounters.push_back(10946);
        internalCounters.push_back(11099);
        internalCounters.push_back(11252);

        p.DefinePublicCounter("PrimitiveAssemblyBusyCycles", "Timing", "Number of GPU cycles the primitive assembly (clipping and culling) is busy. High values may be caused by having many small primitives; mid to low values may indicate pixel shader or output buffer bottleneck.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,4,-,8,12,+,16,+,20,(2),*,+,SU_CLOCKS_PRIM,*,-,1,5,-,9,13,+,17,+,21,(2),*,+,SU_CLOCKS_PRIM,*,-,max,2,6,-,10,14,+,18,+,22,(2),*,+,SU_CLOCKS_PRIM,*,-,max,3,7,-,11,15,+,19,+,23,(2),*,+,SU_CLOCKS_PRIM,*,-,max,(0),max", "99777f2d-9626-c78a-a97c-c4505eba1e5f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10727);
        internalCounters.push_back(10880);
        internalCounters.push_back(11033);
        internalCounters.push_back(11186);

        p.DefinePublicCounter("PrimitivesIn", "PrimitiveAssembly", "The number of primitives received by the hardware. This includes primitives generated by tessellation.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "a515b80d-75c3-c7d2-0d2f-d7766b4759a6" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10733);
        internalCounters.push_back(10886);
        internalCounters.push_back(11039);
        internalCounters.push_back(11192);
        internalCounters.push_back(10773);
        internalCounters.push_back(10926);
        internalCounters.push_back(11079);
        internalCounters.push_back(11232);
        internalCounters.push_back(10774);
        internalCounters.push_back(10927);
        internalCounters.push_back(11080);
        internalCounters.push_back(11233);
        internalCounters.push_back(10775);
        internalCounters.push_back(10928);
        internalCounters.push_back(11081);
        internalCounters.push_back(11234);
        internalCounters.push_back(10776);
        internalCounters.push_back(10929);
        internalCounters.push_back(11082);
        internalCounters.push_back(11235);

        p.DefinePublicCounter("CulledPrims", "PrimitiveAssembly", "The number of culled primitives. Typical reasons include scissor, the primitive having zero area, and back or front face culling.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,+,2,+,3,+,4,+,5,+,6,+,7,+,8,+,9,+,10,+,11,+,12,+,13,+,14,+,15,+,16,+,17,+,18,+,19,+", "589bdf55-9192-280a-41c3-584bc94f2562" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10740);
        internalCounters.push_back(10893);
        internalCounters.push_back(11046);
        internalCounters.push_back(11199);

        p.DefinePublicCounter("ClippedPrims", "PrimitiveAssembly", "The number of primitives that required one or more clipping operations due to intersecting the view volume or user clip planes.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "5ef6f9d5-155e-5baa-163f-8359d9ea9bbf" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10828);
        internalCounters.push_back(10981);
        internalCounters.push_back(11134);
        internalCounters.push_back(11287);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("PAStalledOnRasterizer", "PrimitiveAssembly", "Percentage of GPUTime that primitive assembly waits for rasterization to be ready to accept data. This roughly indicates for what percentage of time the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,/,(100),*", "6f9f416b-53c1-0457-f88c-7b6ba8973974" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(10828);
        internalCounters.push_back(10981);
        internalCounters.push_back(11134);
        internalCounters.push_back(11287);

        p.DefinePublicCounter("PAStalledOnRasterizerCycles", "PrimitiveAssembly", "Number of GPU cycles the primitive assembly waits for rasterization to be ready to accept data. Indicates the number of GPU cycles the pipeline is bottlenecked by pixel operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max", "7a8c492a-c566-9328-6805-760dbff5c0f2" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12931);
        internalCounters.push_back(12965);
        internalCounters.push_back(12999);
        internalCounters.push_back(13033);
        internalCounters.push_back(12936);
        internalCounters.push_back(12970);
        internalCounters.push_back(13004);
        internalCounters.push_back(13038);
        internalCounters.push_back(12941);
        internalCounters.push_back(12975);
        internalCounters.push_back(13009);
        internalCounters.push_back(13043);
        internalCounters.push_back(12946);
        internalCounters.push_back(12980);
        internalCounters.push_back(13014);
        internalCounters.push_back(13048);

        p.DefinePublicCounter("PSPixelsOut", "PixelShader", "Pixels exported from shader to colour buffers. Does not include killed or alpha tested pixels; if there are multiple rendertargets, each rendertarget receives one export, so this will be 2 for 1 pixel written to two RTs.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,8,9,10,11,sum4,12,13,14,15,sum4,sum4", "181f5ca1-ec90-61a3-fd73-d8e3722af9e9" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12933);
        internalCounters.push_back(12967);
        internalCounters.push_back(13001);
        internalCounters.push_back(13035);
        internalCounters.push_back(12938);
        internalCounters.push_back(12972);
        internalCounters.push_back(13006);
        internalCounters.push_back(13040);
        internalCounters.push_back(12943);
        internalCounters.push_back(12977);
        internalCounters.push_back(13011);
        internalCounters.push_back(13045);
        internalCounters.push_back(12948);
        internalCounters.push_back(12982);
        internalCounters.push_back(13016);
        internalCounters.push_back(13050);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("PSExportStalls", "PixelShader", "Pixel shader output stalls. Percentage of GPUBusy. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the colour buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max,16,/,(100),*", "996ce2b4-55ce-25c1-afb7-575bd9b4ce90" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(12933);
        internalCounters.push_back(12967);
        internalCounters.push_back(13001);
        internalCounters.push_back(13035);
        internalCounters.push_back(12938);
        internalCounters.push_back(12972);
        internalCounters.push_back(13006);
        internalCounters.push_back(13040);
        internalCounters.push_back(12943);
        internalCounters.push_back(12977);
        internalCounters.push_back(13011);
        internalCounters.push_back(13045);
        internalCounters.push_back(12948);
        internalCounters.push_back(12982);
        internalCounters.push_back(13016);
        internalCounters.push_back(13050);

        p.DefinePublicCounter("PSExportStallsCycles", "PixelShader", "Number of GPU cycles the pixel shader output stalls. Should be zero for PS or further upstream limited cases; if not zero, indicates a bottleneck in late Z testing or in the colour buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max", "5e58e8ae-1854-e662-b460-a4a31f7fb493" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(18653);
        internalCounters.push_back(18952);
        internalCounters.push_back(19251);
        internalCounters.push_back(19550);
        internalCounters.push_back(18631);
        internalCounters.push_back(18930);
        internalCounters.push_back(19229);
        internalCounters.push_back(19528);

        p.DefinePublicCounter("PSVALUInstCount", "PixelShader", "Average number of vector ALU instructions executed in the PS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/", "eb74389e-435c-4137-ecf1-39eb5bc1cbfe" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(18657);
        internalCounters.push_back(18956);
        internalCounters.push_back(19255);
        internalCounters.push_back(19554);
        internalCounters.push_back(18631);
        internalCounters.push_back(18930);
        internalCounters.push_back(19229);
        internalCounters.push_back(19528);

        p.DefinePublicCounter("PSSALUInstCount", "PixelShader", "Average number of scalar ALU instructions executed in the PS. Affected by flow control.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,/", "e6a06580-8a82-96d6-976c-acc121fc5516" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(18708);
        internalCounters.push_back(19007);
        internalCounters.push_back(19306);
        internalCounters.push_back(19605);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("PSVALUBusy", "PixelShader", "The percentage of GPUTime vector ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/,4,/,(100),*", "6ce6fef7-8e33-10b4-f351-af755e177e85" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(18708);
        internalCounters.push_back(19007);
        internalCounters.push_back(19306);
        internalCounters.push_back(19605);

        p.DefinePublicCounter("PSVALUBusyCycles", "PixelShader", "Number of GPU cycles where vector ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/", "1e276f86-cd2a-72e7-fc9d-004f666f2981" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(18713);
        internalCounters.push_back(19012);
        internalCounters.push_back(19311);
        internalCounters.push_back(19610);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("PSSALUBusy", "PixelShader", "The percentage of GPUTime scalar ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,4,/,(100),*", "2ff9f34f-e94b-af4d-18c2-5fbbf6d1727a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(18713);
        internalCounters.push_back(19012);
        internalCounters.push_back(19311);
        internalCounters.push_back(19610);

        p.DefinePublicCounter("PSSALUBusyCycles", "PixelShader", "Number of GPU cycles where scalar ALU instructions are being processed by the PS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "29808906-f128-b078-fc79-820a4b3b3b8d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13114);
        internalCounters.push_back(13311);
        internalCounters.push_back(13508);
        internalCounters.push_back(13705);
        internalCounters.push_back(13120);
        internalCounters.push_back(13317);
        internalCounters.push_back(13514);
        internalCounters.push_back(13711);

        p.DefinePublicCounter("CSThreadGroups", "ComputeShader", "Total number of thread groups.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,sum8", "8ce3fc80-56b2-97f9-8e70-2e8c747cea68" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13117);
        internalCounters.push_back(13314);
        internalCounters.push_back(13511);
        internalCounters.push_back(13708);
        internalCounters.push_back(13123);
        internalCounters.push_back(13320);
        internalCounters.push_back(13517);
        internalCounters.push_back(13714);

        p.DefinePublicCounter("CSWavefronts", "ComputeShader", "The total number of wavefronts used for the CS.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,sum8", "42379c6e-369b-c237-8b25-cdb9cdc65c4d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(13114);
        internalCounters.push_back(13311);
        internalCounters.push_back(13508);
        internalCounters.push_back(13705);
        internalCounters.push_back(13120);
        internalCounters.push_back(13317);
        internalCounters.push_back(13514);
        internalCounters.push_back(13711);
        internalCounters.push_back(13857);
        internalCounters.push_back(14156);
        internalCounters.push_back(14455);
        internalCounters.push_back(14754);

        p.DefinePublicCounter("CSThreads", "ComputeShader", "The number of CS threads processed by the hardware.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,4,5,6,7,sum8,8,9,10,11,sum4,ifnotzero", "7a648013-6eac-2665-ac36-13c6f4ac9c26" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(22241);
        internalCounters.push_back(22540);
        internalCounters.push_back(22839);
        internalCounters.push_back(23138);
        internalCounters.push_back(22219);
        internalCounters.push_back(22518);
        internalCounters.push_back(22817);
        internalCounters.push_back(23116);
        internalCounters.push_back(13114);
        internalCounters.push_back(13311);
        internalCounters.push_back(13508);
        internalCounters.push_back(13705);
        internalCounters.push_back(13120);
        internalCounters.push_back(13317);
        internalCounters.push_back(13514);
        internalCounters.push_back(13711);

        p.DefinePublicCounter("CSVALUInsts", "ComputeShader", "The average number of vector ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,12,13,14,15,sum8,ifnotzero", "376cb1cc-5a40-9d1d-404c-f1736c0c5084" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(22304);
        internalCounters.push_back(22603);
        internalCounters.push_back(22902);
        internalCounters.push_back(23201);
        internalCounters.push_back(22296);
        internalCounters.push_back(22595);
        internalCounters.push_back(22894);
        internalCounters.push_back(23193);
        internalCounters.push_back(13114);
        internalCounters.push_back(13311);
        internalCounters.push_back(13508);
        internalCounters.push_back(13705);
        internalCounters.push_back(13120);
        internalCounters.push_back(13317);
        internalCounters.push_back(13514);
        internalCounters.push_back(13711);

        p.DefinePublicCounter("CSVALUUtilization", "ComputeShader", "The percentage of active vector ALU threads in a wave. A lower number can mean either more thread divergence in a wave or that the work-group size is not a multiple of 64. Value range: 0% (bad), 100% (ideal - no thread divergence).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,(64),*,/,(100),*,8,9,10,11,12,13,14,15,sum8,ifnotzero,(100),min", "4476879e-cdc0-d602-b24e-9b4a8d38438f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(22245);
        internalCounters.push_back(22544);
        internalCounters.push_back(22843);
        internalCounters.push_back(23142);
        internalCounters.push_back(22219);
        internalCounters.push_back(22518);
        internalCounters.push_back(22817);
        internalCounters.push_back(23116);
        internalCounters.push_back(13114);
        internalCounters.push_back(13311);
        internalCounters.push_back(13508);
        internalCounters.push_back(13705);
        internalCounters.push_back(13120);
        internalCounters.push_back(13317);
        internalCounters.push_back(13514);
        internalCounters.push_back(13711);

        p.DefinePublicCounter("CSSALUInsts", "ComputeShader", "The average number of scalar ALU instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,12,13,14,15,sum8,ifnotzero", "eb211144-8136-ff86-e8bf-4d0493a904cb" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(22243);
        internalCounters.push_back(22542);
        internalCounters.push_back(22841);
        internalCounters.push_back(23140);
        internalCounters.push_back(23512);
        internalCounters.push_back(23631);
        internalCounters.push_back(23750);
        internalCounters.push_back(23869);
        internalCounters.push_back(23988);
        internalCounters.push_back(24107);
        internalCounters.push_back(24226);
        internalCounters.push_back(24345);
        internalCounters.push_back(24464);
        internalCounters.push_back(24583);
        internalCounters.push_back(24702);
        internalCounters.push_back(24821);
        internalCounters.push_back(24940);
        internalCounters.push_back(25059);
        internalCounters.push_back(25178);
        internalCounters.push_back(25297);
        internalCounters.push_back(25416);
        internalCounters.push_back(25535);
        internalCounters.push_back(25654);
        internalCounters.push_back(25773);
        internalCounters.push_back(25892);
        internalCounters.push_back(26011);
        internalCounters.push_back(26130);
        internalCounters.push_back(26249);
        internalCounters.push_back(26368);
        internalCounters.push_back(26487);
        internalCounters.push_back(26606);
        internalCounters.push_back(26725);
        internalCounters.push_back(26844);
        internalCounters.push_back(26963);
        internalCounters.push_back(27082);
        internalCounters.push_back(27201);
        internalCounters.push_back(27320);
        internalCounters.push_back(27439);
        internalCounters.push_back(27558);
        internalCounters.push_back(27677);
        internalCounters.push_back(27796);
        internalCounters.push_back(27915);
        internalCounters.push_back(28034);
        internalCounters.push_back(28153);
        internalCounters.push_back(28272);
        internalCounters.push_back(28391);
        internalCounters.push_back(28510);
        internalCounters.push_back(28629);
        internalCounters.push_back(28748);
        internalCounters.push_back(28867);
        internalCounters.push_back(28986);
        internalCounters.push_back(29105);
        internalCounters.push_back(29224);
        internalCounters.push_back(29343);
        internalCounters.push_back(29462);
        internalCounters.push_back(29581);
        internalCounters.push_back(29700);
        internalCounters.push_back(29819);
        internalCounters.push_back(29938);
        internalCounters.push_back(30057);
        internalCounters.push_back(30176);
        internalCounters.push_back(30295);
        internalCounters.push_back(30414);
        internalCounters.push_back(30533);
        internalCounters.push_back(30652);
        internalCounters.push_back(30771);
        internalCounters.push_back(30890);
        internalCounters.push_back(31009);
        internalCounters.push_back(22219);
        internalCounters.push_back(22518);
        internalCounters.push_back(22817);
        internalCounters.push_back(23116);
        internalCounters.push_back(13114);
        internalCounters.push_back(13311);
        internalCounters.push_back(13508);
        internalCounters.push_back(13705);
        internalCounters.push_back(13120);
        internalCounters.push_back(13317);
        internalCounters.push_back(13514);
        internalCounters.push_back(13711);

        p.DefinePublicCounter("CSVFetchInsts", "ComputeShader", "The average number of vector fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,sum64,-,68,69,70,71,sum4,/,72,73,74,75,76,77,78,79,sum8,ifnotzero", "3e2829c0-6215-783b-c271-6d57ff2c520e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(22246);
        internalCounters.push_back(22545);
        internalCounters.push_back(22844);
        internalCounters.push_back(23143);
        internalCounters.push_back(22219);
        internalCounters.push_back(22518);
        internalCounters.push_back(22817);
        internalCounters.push_back(23116);
        internalCounters.push_back(13114);
        internalCounters.push_back(13311);
        internalCounters.push_back(13508);
        internalCounters.push_back(13705);
        internalCounters.push_back(13120);
        internalCounters.push_back(13317);
        internalCounters.push_back(13514);
        internalCounters.push_back(13711);

        p.DefinePublicCounter("CSSFetchInsts", "ComputeShader", "The average number of scalar fetch instructions from the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,12,13,14,15,sum8,ifnotzero", "da09171c-6a0a-584f-fddc-dc5062d63a3e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(22242);
        internalCounters.push_back(22541);
        internalCounters.push_back(22840);
        internalCounters.push_back(23139);
        internalCounters.push_back(23513);
        internalCounters.push_back(23632);
        internalCounters.push_back(23751);
        internalCounters.push_back(23870);
        internalCounters.push_back(23989);
        internalCounters.push_back(24108);
        internalCounters.push_back(24227);
        internalCounters.push_back(24346);
        internalCounters.push_back(24465);
        internalCounters.push_back(24584);
        internalCounters.push_back(24703);
        internalCounters.push_back(24822);
        internalCounters.push_back(24941);
        internalCounters.push_back(25060);
        internalCounters.push_back(25179);
        internalCounters.push_back(25298);
        internalCounters.push_back(25417);
        internalCounters.push_back(25536);
        internalCounters.push_back(25655);
        internalCounters.push_back(25774);
        internalCounters.push_back(25893);
        internalCounters.push_back(26012);
        internalCounters.push_back(26131);
        internalCounters.push_back(26250);
        internalCounters.push_back(26369);
        internalCounters.push_back(26488);
        internalCounters.push_back(26607);
        internalCounters.push_back(26726);
        internalCounters.push_back(26845);
        internalCounters.push_back(26964);
        internalCounters.push_back(27083);
        internalCounters.push_back(27202);
        internalCounters.push_back(27321);
        internalCounters.push_back(27440);
        internalCounters.push_back(27559);
        internalCounters.push_back(27678);
        internalCounters.push_back(27797);
        internalCounters.push_back(27916);
        internalCounters.push_back(28035);
        internalCounters.push_back(28154);
        internalCounters.push_back(28273);
        internalCounters.push_back(28392);
        internalCounters.push_back(28511);
        internalCounters.push_back(28630);
        internalCounters.push_back(28749);
        internalCounters.push_back(28868);
        internalCounters.push_back(28987);
        internalCounters.push_back(29106);
        internalCounters.push_back(29225);
        internalCounters.push_back(29344);
        internalCounters.push_back(29463);
        internalCounters.push_back(29582);
        internalCounters.push_back(29701);
        internalCounters.push_back(29820);
        internalCounters.push_back(29939);
        internalCounters.push_back(30058);
        internalCounters.push_back(30177);
        internalCounters.push_back(30296);
        internalCounters.push_back(30415);
        internalCounters.push_back(30534);
        internalCounters.push_back(30653);
        internalCounters.push_back(30772);
        internalCounters.push_back(30891);
        internalCounters.push_back(31010);
        internalCounters.push_back(22219);
        internalCounters.push_back(22518);
        internalCounters.push_back(22817);
        internalCounters.push_back(23116);
        internalCounters.push_back(13114);
        internalCounters.push_back(13311);
        internalCounters.push_back(13508);
        internalCounters.push_back(13705);
        internalCounters.push_back(13120);
        internalCounters.push_back(13317);
        internalCounters.push_back(13514);
        internalCounters.push_back(13711);

        p.DefinePublicCounter("CSVWriteInsts", "ComputeShader", "The average number of vector write instructions to the video memory executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,sum64,-,68,69,70,71,sum4,/,72,73,74,75,76,77,78,79,sum8,ifnotzero", "43438c22-e910-b377-b767-b32902e0df0d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(22247);
        internalCounters.push_back(22546);
        internalCounters.push_back(22845);
        internalCounters.push_back(23144);
        internalCounters.push_back(22248);
        internalCounters.push_back(22547);
        internalCounters.push_back(22846);
        internalCounters.push_back(23145);
        internalCounters.push_back(22219);
        internalCounters.push_back(22518);
        internalCounters.push_back(22817);
        internalCounters.push_back(23116);
        internalCounters.push_back(13114);
        internalCounters.push_back(13311);
        internalCounters.push_back(13508);
        internalCounters.push_back(13705);
        internalCounters.push_back(13120);
        internalCounters.push_back(13317);
        internalCounters.push_back(13514);
        internalCounters.push_back(13711);

        p.DefinePublicCounter("CSFlatVMemInsts", "ComputeShader", "The average number of FLAT instructions that read from or write to the video memory executed per work item (affected by flow control). Includes FLAT instructions that read from or write to scratch.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,-,8,9,10,11,sum4,/,12,13,14,15,16,17,18,19,sum8,ifnotzero", "2570b477-13e3-f5b6-e6ff-7159373bc74d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(22296);
        internalCounters.push_back(22595);
        internalCounters.push_back(22894);
        internalCounters.push_back(23193);
        internalCounters.push_back(10620);
        internalCounters.push_back(13114);
        internalCounters.push_back(13311);
        internalCounters.push_back(13508);
        internalCounters.push_back(13705);
        internalCounters.push_back(13120);
        internalCounters.push_back(13317);
        internalCounters.push_back(13514);
        internalCounters.push_back(13711);

        p.DefinePublicCounter("CSVALUBusy", "ComputeShader", "The percentage of GPUTime vector ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,sum4,(4),*,NUM_SIMDS,/,4,/,(100),*,5,6,7,8,9,10,11,12,sum8,ifnotzero", "f1e64815-f6a8-c277-d4f9-d054b443e205" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(22296);
        internalCounters.push_back(22595);
        internalCounters.push_back(22894);
        internalCounters.push_back(23193);

        p.DefinePublicCounter("CSVALUBusyCycles", "ComputeShader", "Number of GPU cycles where vector ALU instructions are processed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,/", "2d0d5852-2658-eb73-68d2-f23f7118c9c3" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(22301);
        internalCounters.push_back(22600);
        internalCounters.push_back(22899);
        internalCounters.push_back(23198);
        internalCounters.push_back(10620);
        internalCounters.push_back(13114);
        internalCounters.push_back(13311);
        internalCounters.push_back(13508);
        internalCounters.push_back(13705);
        internalCounters.push_back(13120);
        internalCounters.push_back(13317);
        internalCounters.push_back(13514);
        internalCounters.push_back(13711);

        p.DefinePublicCounter("CSSALUBusy", "ComputeShader", "The percentage of GPUTime scalar ALU instructions are processed. Value range: 0% (bad) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,sum4,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/,4,/,(100),*,5,6,7,8,9,10,11,12,sum8,ifnotzero", "3fc35f4e-9882-94e3-6f5f-4e81cd97082a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(22301);
        internalCounters.push_back(22600);
        internalCounters.push_back(22899);
        internalCounters.push_back(23198);

        p.DefinePublicCounter("CSSALUBusyCycles", "ComputeShader", "Number of GPU cycles where scalar ALU instructions are processed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,sum4,(4),*,NUM_SIMDS,NUM_SHADER_ENGINES,/,/", "de58f8fc-8ed4-a799-648d-62ded7b1c4c4" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(23426);
        internalCounters.push_back(23545);
        internalCounters.push_back(23664);
        internalCounters.push_back(23783);
        internalCounters.push_back(23902);
        internalCounters.push_back(24021);
        internalCounters.push_back(24140);
        internalCounters.push_back(24259);
        internalCounters.push_back(24378);
        internalCounters.push_back(24497);
        internalCounters.push_back(24616);
        internalCounters.push_back(24735);
        internalCounters.push_back(24854);
        internalCounters.push_back(24973);
        internalCounters.push_back(25092);
        internalCounters.push_back(25211);
        internalCounters.push_back(25330);
        internalCounters.push_back(25449);
        internalCounters.push_back(25568);
        internalCounters.push_back(25687);
        internalCounters.push_back(25806);
        internalCounters.push_back(25925);
        internalCounters.push_back(26044);
        internalCounters.push_back(26163);
        internalCounters.push_back(26282);
        internalCounters.push_back(26401);
        internalCounters.push_back(26520);
        internalCounters.push_back(26639);
        internalCounters.push_back(26758);
        internalCounters.push_back(26877);
        internalCounters.push_back(26996);
        internalCounters.push_back(27115);
        internalCounters.push_back(27234);
        internalCounters.push_back(27353);
        internalCounters.push_back(27472);
        internalCounters.push_back(27591);
        internalCounters.push_back(27710);
        internalCounters.push_back(27829);
        internalCounters.push_back(27948);
        internalCounters.push_back(28067);
        internalCounters.push_back(28186);
        internalCounters.push_back(28305);
        internalCounters.push_back(28424);
        internalCounters.push_back(28543);
        internalCounters.push_back(28662);
        internalCounters.push_back(28781);
        internalCounters.push_back(28900);
        internalCounters.push_back(29019);
        internalCounters.push_back(29138);
        internalCounters.push_back(29257);
        internalCounters.push_back(29376);
        internalCounters.push_back(29495);
        internalCounters.push_back(29614);
        internalCounters.push_back(29733);
        internalCounters.push_back(29852);
        internalCounters.push_back(29971);
        internalCounters.push_back(30090);
        internalCounters.push_back(30209);
        internalCounters.push_back(30328);
        internalCounters.push_back(30447);
        internalCounters.push_back(30566);
        internalCounters.push_back(30685);
        internalCounters.push_back(30804);
        internalCounters.push_back(30923);
        internalCounters.push_back(10620);
        internalCounters.push_back(13114);
        internalCounters.push_back(13311);
        internalCounters.push_back(13508);
        internalCounters.push_back(13705);
        internalCounters.push_back(13120);
        internalCounters.push_back(13317);
        internalCounters.push_back(13514);
        internalCounters.push_back(13711);

        p.DefinePublicCounter("CSMemUnitBusy", "ComputeShader", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,max64,64,/,(100),*,65,66,67,68,69,70,71,72,sum8,ifnotzero", "42ab96e1-0a24-96c8-c4ff-098fa267d78e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(23426);
        internalCounters.push_back(23545);
        internalCounters.push_back(23664);
        internalCounters.push_back(23783);
        internalCounters.push_back(23902);
        internalCounters.push_back(24021);
        internalCounters.push_back(24140);
        internalCounters.push_back(24259);
        internalCounters.push_back(24378);
        internalCounters.push_back(24497);
        internalCounters.push_back(24616);
        internalCounters.push_back(24735);
        internalCounters.push_back(24854);
        internalCounters.push_back(24973);
        internalCounters.push_back(25092);
        internalCounters.push_back(25211);
        internalCounters.push_back(25330);
        internalCounters.push_back(25449);
        internalCounters.push_back(25568);
        internalCounters.push_back(25687);
        internalCounters.push_back(25806);
        internalCounters.push_back(25925);
        internalCounters.push_back(26044);
        internalCounters.push_back(26163);
        internalCounters.push_back(26282);
        internalCounters.push_back(26401);
        internalCounters.push_back(26520);
        internalCounters.push_back(26639);
        internalCounters.push_back(26758);
        internalCounters.push_back(26877);
        internalCounters.push_back(26996);
        internalCounters.push_back(27115);
        internalCounters.push_back(27234);
        internalCounters.push_back(27353);
        internalCounters.push_back(27472);
        internalCounters.push_back(27591);
        internalCounters.push_back(27710);
        internalCounters.push_back(27829);
        internalCounters.push_back(27948);
        internalCounters.push_back(28067);
        internalCounters.push_back(28186);
        internalCounters.push_back(28305);
        internalCounters.push_back(28424);
        internalCounters.push_back(28543);
        internalCounters.push_back(28662);
        internalCounters.push_back(28781);
        internalCounters.push_back(28900);
        internalCounters.push_back(29019);
        internalCounters.push_back(29138);
        internalCounters.push_back(29257);
        internalCounters.push_back(29376);
        internalCounters.push_back(29495);
        internalCounters.push_back(29614);
        internalCounters.push_back(29733);
        internalCounters.push_back(29852);
        internalCounters.push_back(29971);
        internalCounters.push_back(30090);
        internalCounters.push_back(30209);
        internalCounters.push_back(30328);
        internalCounters.push_back(30447);
        internalCounters.push_back(30566);
        internalCounters.push_back(30685);
        internalCounters.push_back(30804);
        internalCounters.push_back(30923);

        p.DefinePublicCounter("CSMemUnitBusyCycles", "ComputeShader", "Number of GPU cycles the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,max64", "39d5687f-c727-7c0c-af82-bb711d3897ed" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(34550);
        internalCounters.push_back(34730);
        internalCounters.push_back(34910);
        internalCounters.push_back(35090);
        internalCounters.push_back(35270);
        internalCounters.push_back(35450);
        internalCounters.push_back(35630);
        internalCounters.push_back(35810);
        internalCounters.push_back(35990);
        internalCounters.push_back(36170);
        internalCounters.push_back(36350);
        internalCounters.push_back(36530);
        internalCounters.push_back(36710);
        internalCounters.push_back(36890);
        internalCounters.push_back(37070);
        internalCounters.push_back(37250);
        internalCounters.push_back(37430);
        internalCounters.push_back(37610);
        internalCounters.push_back(37790);
        internalCounters.push_back(37970);
        internalCounters.push_back(38150);
        internalCounters.push_back(38330);
        internalCounters.push_back(38510);
        internalCounters.push_back(38690);
        internalCounters.push_back(38870);
        internalCounters.push_back(39050);
        internalCounters.push_back(39230);
        internalCounters.push_back(39410);
        internalCounters.push_back(39590);
        internalCounters.push_back(39770);
        internalCounters.push_back(39950);
        internalCounters.push_back(40130);
        internalCounters.push_back(40310);
        internalCounters.push_back(40490);
        internalCounters.push_back(40670);
        internalCounters.push_back(40850);
        internalCounters.push_back(41030);
        internalCounters.push_back(41210);
        internalCounters.push_back(41390);
        internalCounters.push_back(41570);
        internalCounters.push_back(41750);
        internalCounters.push_back(41930);
        internalCounters.push_back(42110);
        internalCounters.push_back(42290);
        internalCounters.push_back(42470);
        internalCounters.push_back(42650);
        internalCounters.push_back(42830);
        internalCounters.push_back(43010);
        internalCounters.push_back(43190);
        internalCounters.push_back(43370);
        internalCounters.push_back(43550);
        internalCounters.push_back(43730);
        internalCounters.push_back(43910);
        internalCounters.push_back(44090);
        internalCounters.push_back(44270);
        internalCounters.push_back(44450);
        internalCounters.push_back(44630);
        internalCounters.push_back(44810);
        internalCounters.push_back(44990);
        internalCounters.push_back(45170);
        internalCounters.push_back(45350);
        internalCounters.push_back(45530);
        internalCounters.push_back(45710);
        internalCounters.push_back(45890);
        internalCounters.push_back(10620);
        internalCounters.push_back(13114);
        internalCounters.push_back(13311);
        internalCounters.push_back(13508);
        internalCounters.push_back(13705);
        internalCounters.push_back(13120);
        internalCounters.push_back(13317);
        internalCounters.push_back(13514);
        internalCounters.push_back(13711);

        p.DefinePublicCounter("CSMemUnitStalled", "ComputeShader", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,max64,64,/,(100),*,65,66,67,68,69,70,71,72,sum8,ifnotzero", "f18e8679-1511-d533-d9ee-4365197f7d0c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(34550);
        internalCounters.push_back(34730);
        internalCounters.push_back(34910);
        internalCounters.push_back(35090);
        internalCounters.push_back(35270);
        internalCounters.push_back(35450);
        internalCounters.push_back(35630);
        internalCounters.push_back(35810);
        internalCounters.push_back(35990);
        internalCounters.push_back(36170);
        internalCounters.push_back(36350);
        internalCounters.push_back(36530);
        internalCounters.push_back(36710);
        internalCounters.push_back(36890);
        internalCounters.push_back(37070);
        internalCounters.push_back(37250);
        internalCounters.push_back(37430);
        internalCounters.push_back(37610);
        internalCounters.push_back(37790);
        internalCounters.push_back(37970);
        internalCounters.push_back(38150);
        internalCounters.push_back(38330);
        internalCounters.push_back(38510);
        internalCounters.push_back(38690);
        internalCounters.push_back(38870);
        internalCounters.push_back(39050);
        internalCounters.push_back(39230);
        internalCounters.push_back(39410);
        internalCounters.push_back(39590);
        internalCounters.push_back(39770);
        internalCounters.push_back(39950);
        internalCounters.push_back(40130);
        internalCounters.push_back(40310);
        internalCounters.push_back(40490);
        internalCounters.push_back(40670);
        internalCounters.push_back(40850);
        internalCounters.push_back(41030);
        internalCounters.push_back(41210);
        internalCounters.push_back(41390);
        internalCounters.push_back(41570);
        internalCounters.push_back(41750);
        internalCounters.push_back(41930);
        internalCounters.push_back(42110);
        internalCounters.push_back(42290);
        internalCounters.push_back(42470);
        internalCounters.push_back(42650);
        internalCounters.push_back(42830);
        internalCounters.push_back(43010);
        internalCounters.push_back(43190);
        internalCounters.push_back(43370);
        internalCounters.push_back(43550);
        internalCounters.push_back(43730);
        internalCounters.push_back(43910);
        internalCounters.push_back(44090);
        internalCounters.push_back(44270);
        internalCounters.push_back(44450);
        internalCounters.push_back(44630);
        internalCounters.push_back(44810);
        internalCounters.push_back(44990);
        internalCounters.push_back(45170);
        internalCounters.push_back(45350);
        internalCounters.push_back(45530);
        internalCounters.push_back(45710);
        internalCounters.push_back(45890);

        p.DefinePublicCounter("CSMemUnitStalledCycles", "ComputeShader", "Number of GPU cycles the memory unit is stalled. Try reducing the number or size of fetches and writes if possible.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,max64", "51991c84-ed2b-bf31-c4ab-8f8e9eb8f29f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(46095);
        internalCounters.push_back(46287);
        internalCounters.push_back(46479);
        internalCounters.push_back(46671);
        internalCounters.push_back(46863);
        internalCounters.push_back(47055);
        internalCounters.push_back(47247);
        internalCounters.push_back(47439);
        internalCounters.push_back(47631);
        internalCounters.push_back(47823);
        internalCounters.push_back(48015);
        internalCounters.push_back(48207);
        internalCounters.push_back(48399);
        internalCounters.push_back(48591);
        internalCounters.push_back(48783);
        internalCounters.push_back(48975);

        p.DefinePublicCounter("CSWriteUnitStalledCycles", "ComputeShader", "Number of GPU cycles the write unit is stalled.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "be164c60-5e48-acac-9622-29616d09aa9a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(22250);
        internalCounters.push_back(22549);
        internalCounters.push_back(22848);
        internalCounters.push_back(23147);
        internalCounters.push_back(22219);
        internalCounters.push_back(22518);
        internalCounters.push_back(22817);
        internalCounters.push_back(23116);
        internalCounters.push_back(13114);
        internalCounters.push_back(13311);
        internalCounters.push_back(13508);
        internalCounters.push_back(13705);
        internalCounters.push_back(13120);
        internalCounters.push_back(13317);
        internalCounters.push_back(13514);
        internalCounters.push_back(13711);

        p.DefinePublicCounter("CSGDSInsts", "ComputeShader", "The average number of GDS read or GDS write instructions executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,12,13,14,15,sum8,ifnotzero", "2a867f3e-4a37-ad16-55d1-f03d74707819" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(22249);
        internalCounters.push_back(22548);
        internalCounters.push_back(22847);
        internalCounters.push_back(23146);
        internalCounters.push_back(22247);
        internalCounters.push_back(22546);
        internalCounters.push_back(22845);
        internalCounters.push_back(23144);
        internalCounters.push_back(22219);
        internalCounters.push_back(22518);
        internalCounters.push_back(22817);
        internalCounters.push_back(23116);
        internalCounters.push_back(13114);
        internalCounters.push_back(13311);
        internalCounters.push_back(13508);
        internalCounters.push_back(13705);
        internalCounters.push_back(13120);
        internalCounters.push_back(13317);
        internalCounters.push_back(13514);
        internalCounters.push_back(13711);

        p.DefinePublicCounter("CSLDSInsts", "ComputeShader", "The average number of LDS read/write instructions executed per work-item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,-,8,9,10,11,sum4,/,12,13,14,15,16,17,18,19,sum8,ifnotzero", "61b0b351-7e06-ef8e-a8e0-7a9e3200a836" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(22248);
        internalCounters.push_back(22547);
        internalCounters.push_back(22846);
        internalCounters.push_back(23145);
        internalCounters.push_back(22219);
        internalCounters.push_back(22518);
        internalCounters.push_back(22817);
        internalCounters.push_back(23116);
        internalCounters.push_back(13114);
        internalCounters.push_back(13311);
        internalCounters.push_back(13508);
        internalCounters.push_back(13705);
        internalCounters.push_back(13120);
        internalCounters.push_back(13317);
        internalCounters.push_back(13514);
        internalCounters.push_back(13711);

        p.DefinePublicCounter("CSFlatLDSInsts", "ComputeShader", "The average number of FLAT instructions that read from or write to LDS executed per work item (affected by flow control).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,9,10,11,12,13,14,15,sum8,ifnotzero", "99672cda-de2b-014c-482e-cf73b90068d5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(22276);
        internalCounters.push_back(22575);
        internalCounters.push_back(22874);
        internalCounters.push_back(23173);
        internalCounters.push_back(22219);
        internalCounters.push_back(22518);
        internalCounters.push_back(22817);
        internalCounters.push_back(23116);
        internalCounters.push_back(10620);
        internalCounters.push_back(13114);
        internalCounters.push_back(13311);
        internalCounters.push_back(13508);
        internalCounters.push_back(13705);
        internalCounters.push_back(13120);
        internalCounters.push_back(13317);
        internalCounters.push_back(13514);
        internalCounters.push_back(13711);

        p.DefinePublicCounter("CSALUStalledByLDS", "ComputeShader", "The percentage of GPUTime ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,/,8,/,NUM_SHADER_ENGINES,/,(100),*,9,10,11,12,13,14,15,16,sum8,ifnotzero", "6dc4f1c2-bad0-c9ff-156e-883b319a752a" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(22276);
        internalCounters.push_back(22575);
        internalCounters.push_back(22874);
        internalCounters.push_back(23173);

        p.DefinePublicCounter("CSALUStalledByLDSCycles", "ComputeShader", "Number of GPU cycles the ALU units are stalled by the LDS input queue being full or the output queue being not ready. If there are LDS bank conflicts, reduce them. Otherwise, try reducing the number of LDS accesses if possible.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,sum4,NUM_SHADER_ENGINES,/", "8f3d5f25-2159-0374-fafe-e26a7799b6c8" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(22312);
        internalCounters.push_back(22611);
        internalCounters.push_back(22910);
        internalCounters.push_back(23209);
        internalCounters.push_back(10620);
        internalCounters.push_back(13114);
        internalCounters.push_back(13311);
        internalCounters.push_back(13508);
        internalCounters.push_back(13705);
        internalCounters.push_back(13120);
        internalCounters.push_back(13317);
        internalCounters.push_back(13514);
        internalCounters.push_back(13711);

        p.DefinePublicCounter("CSLDSBankConflict", "ComputeShader", "The percentage of GPUTime LDS is stalled by bank conflicts. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "(0),0,1,2,3,sum4,4,/,NUM_SIMDS,/,(100),*,5,6,7,8,9,10,11,12,sum8,ifnotzero", "1065ee10-2e41-ea41-1eb3-b61b491752f4" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(22312);
        internalCounters.push_back(22611);
        internalCounters.push_back(22910);
        internalCounters.push_back(23209);

        p.DefinePublicCounter("CSLDSBankConflictCycles", "ComputeShader", "Number of GPU cycles the LDS is stalled by bank conflicts. Value range: 0 (optimal) to GPUBusyCycles (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,sum4,NUM_SIMDS,/", "1fd1adf3-c51e-94fd-083e-c482a0a0809e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(23426);
        internalCounters.push_back(23545);
        internalCounters.push_back(23664);
        internalCounters.push_back(23783);
        internalCounters.push_back(23902);
        internalCounters.push_back(24021);
        internalCounters.push_back(24140);
        internalCounters.push_back(24259);
        internalCounters.push_back(24378);
        internalCounters.push_back(24497);
        internalCounters.push_back(24616);
        internalCounters.push_back(24735);
        internalCounters.push_back(24854);
        internalCounters.push_back(24973);
        internalCounters.push_back(25092);
        internalCounters.push_back(25211);
        internalCounters.push_back(25330);
        internalCounters.push_back(25449);
        internalCounters.push_back(25568);
        internalCounters.push_back(25687);
        internalCounters.push_back(25806);
        internalCounters.push_back(25925);
        internalCounters.push_back(26044);
        internalCounters.push_back(26163);
        internalCounters.push_back(26282);
        internalCounters.push_back(26401);
        internalCounters.push_back(26520);
        internalCounters.push_back(26639);
        internalCounters.push_back(26758);
        internalCounters.push_back(26877);
        internalCounters.push_back(26996);
        internalCounters.push_back(27115);
        internalCounters.push_back(27234);
        internalCounters.push_back(27353);
        internalCounters.push_back(27472);
        internalCounters.push_back(27591);
        internalCounters.push_back(27710);
        internalCounters.push_back(27829);
        internalCounters.push_back(27948);
        internalCounters.push_back(28067);
        internalCounters.push_back(28186);
        internalCounters.push_back(28305);
        internalCounters.push_back(28424);
        internalCounters.push_back(28543);
        internalCounters.push_back(28662);
        internalCounters.push_back(28781);
        internalCounters.push_back(28900);
        internalCounters.push_back(29019);
        internalCounters.push_back(29138);
        internalCounters.push_back(29257);
        internalCounters.push_back(29376);
        internalCounters.push_back(29495);
        internalCounters.push_back(29614);
        internalCounters.push_back(29733);
        internalCounters.push_back(29852);
        internalCounters.push_back(29971);
        internalCounters.push_back(30090);
        internalCounters.push_back(30209);
        internalCounters.push_back(30328);
        internalCounters.push_back(30447);
        internalCounters.push_back(30566);
        internalCounters.push_back(30685);
        internalCounters.push_back(30804);
        internalCounters.push_back(30923);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("TexUnitBusy", "Timing", "The percentage of GPUTime the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,max64,64,/,(100),*", "36afb8d9-42fc-aafe-66c5-449542153b2c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(23426);
        internalCounters.push_back(23545);
        internalCounters.push_back(23664);
        internalCounters.push_back(23783);
        internalCounters.push_back(23902);
        internalCounters.push_back(24021);
        internalCounters.push_back(24140);
        internalCounters.push_back(24259);
        internalCounters.push_back(24378);
        internalCounters.push_back(24497);
        internalCounters.push_back(24616);
        internalCounters.push_back(24735);
        internalCounters.push_back(24854);
        internalCounters.push_back(24973);
        internalCounters.push_back(25092);
        internalCounters.push_back(25211);
        internalCounters.push_back(25330);
        internalCounters.push_back(25449);
        internalCounters.push_back(25568);
        internalCounters.push_back(25687);
        internalCounters.push_back(25806);
        internalCounters.push_back(25925);
        internalCounters.push_back(26044);
        internalCounters.push_back(26163);
        internalCounters.push_back(26282);
        internalCounters.push_back(26401);
        internalCounters.push_back(26520);
        internalCounters.push_back(26639);
        internalCounters.push_back(26758);
        internalCounters.push_back(26877);
        internalCounters.push_back(26996);
        internalCounters.push_back(27115);
        internalCounters.push_back(27234);
        internalCounters.push_back(27353);
        internalCounters.push_back(27472);
        internalCounters.push_back(27591);
        internalCounters.push_back(27710);
        internalCounters.push_back(27829);
        internalCounters.push_back(27948);
        internalCounters.push_back(28067);
        internalCounters.push_back(28186);
        internalCounters.push_back(28305);
        internalCounters.push_back(28424);
        internalCounters.push_back(28543);
        internalCounters.push_back(28662);
        internalCounters.push_back(28781);
        internalCounters.push_back(28900);
        internalCounters.push_back(29019);
        internalCounters.push_back(29138);
        internalCounters.push_back(29257);
        internalCounters.push_back(29376);
        internalCounters.push_back(29495);
        internalCounters.push_back(29614);
        internalCounters.push_back(29733);
        internalCounters.push_back(29852);
        internalCounters.push_back(29971);
        internalCounters.push_back(30090);
        internalCounters.push_back(30209);
        internalCounters.push_back(30328);
        internalCounters.push_back(30447);
        internalCounters.push_back(30566);
        internalCounters.push_back(30685);
        internalCounters.push_back(30804);
        internalCounters.push_back(30923);

        p.DefinePublicCounter("TexUnitBusyCycles", "Timing", "Number of GPU cycles the texture unit is active. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,max64", "c68761f2-248c-4f39-6528-c308b1c0807c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(23480);
        internalCounters.push_back(23599);
        internalCounters.push_back(23718);
        internalCounters.push_back(23837);
        internalCounters.push_back(23956);
        internalCounters.push_back(24075);
        internalCounters.push_back(24194);
        internalCounters.push_back(24313);
        internalCounters.push_back(24432);
        internalCounters.push_back(24551);
        internalCounters.push_back(24670);
        internalCounters.push_back(24789);
        internalCounters.push_back(24908);
        internalCounters.push_back(25027);
        internalCounters.push_back(25146);
        internalCounters.push_back(25265);
        internalCounters.push_back(25384);
        internalCounters.push_back(25503);
        internalCounters.push_back(25622);
        internalCounters.push_back(25741);
        internalCounters.push_back(25860);
        internalCounters.push_back(25979);
        internalCounters.push_back(26098);
        internalCounters.push_back(26217);
        internalCounters.push_back(26336);
        internalCounters.push_back(26455);
        internalCounters.push_back(26574);
        internalCounters.push_back(26693);
        internalCounters.push_back(26812);
        internalCounters.push_back(26931);
        internalCounters.push_back(27050);
        internalCounters.push_back(27169);
        internalCounters.push_back(27288);
        internalCounters.push_back(27407);
        internalCounters.push_back(27526);
        internalCounters.push_back(27645);
        internalCounters.push_back(27764);
        internalCounters.push_back(27883);
        internalCounters.push_back(28002);
        internalCounters.push_back(28121);
        internalCounters.push_back(28240);
        internalCounters.push_back(28359);
        internalCounters.push_back(28478);
        internalCounters.push_back(28597);
        internalCounters.push_back(28716);
        internalCounters.push_back(28835);
        internalCounters.push_back(28954);
        internalCounters.push_back(29073);
        internalCounters.push_back(29192);
        internalCounters.push_back(29311);
        internalCounters.push_back(29430);
        internalCounters.push_back(29549);
        internalCounters.push_back(29668);
        internalCounters.push_back(29787);
        internalCounters.push_back(29906);
        internalCounters.push_back(30025);
        internalCounters.push_back(30144);
        internalCounters.push_back(30263);
        internalCounters.push_back(30382);
        internalCounters.push_back(30501);
        internalCounters.push_back(30620);
        internalCounters.push_back(30739);
        internalCounters.push_back(30858);
        internalCounters.push_back(30977);
        internalCounters.push_back(23479);
        internalCounters.push_back(23598);
        internalCounters.push_back(23717);
        internalCounters.push_back(23836);
        internalCounters.push_back(23955);
        internalCounters.push_back(24074);
        internalCounters.push_back(24193);
        internalCounters.push_back(24312);
        internalCounters.push_back(24431);
        internalCounters.push_back(24550);
        internalCounters.push_back(24669);
        internalCounters.push_back(24788);
        internalCounters.push_back(24907);
        internalCounters.push_back(25026);
        internalCounters.push_back(25145);
        internalCounters.push_back(25264);
        internalCounters.push_back(25383);
        internalCounters.push_back(25502);
        internalCounters.push_back(25621);
        internalCounters.push_back(25740);
        internalCounters.push_back(25859);
        internalCounters.push_back(25978);
        internalCounters.push_back(26097);
        internalCounters.push_back(26216);
        internalCounters.push_back(26335);
        internalCounters.push_back(26454);
        internalCounters.push_back(26573);
        internalCounters.push_back(26692);
        internalCounters.push_back(26811);
        internalCounters.push_back(26930);
        internalCounters.push_back(27049);
        internalCounters.push_back(27168);
        internalCounters.push_back(27287);
        internalCounters.push_back(27406);
        internalCounters.push_back(27525);
        internalCounters.push_back(27644);
        internalCounters.push_back(27763);
        internalCounters.push_back(27882);
        internalCounters.push_back(28001);
        internalCounters.push_back(28120);
        internalCounters.push_back(28239);
        internalCounters.push_back(28358);
        internalCounters.push_back(28477);
        internalCounters.push_back(28596);
        internalCounters.push_back(28715);
        internalCounters.push_back(28834);
        internalCounters.push_back(28953);
        internalCounters.push_back(29072);
        internalCounters.push_back(29191);
        internalCounters.push_back(29310);
        internalCounters.push_back(29429);
        internalCounters.push_back(29548);
        internalCounters.push_back(29667);
        internalCounters.push_back(29786);
        internalCounters.push_back(29905);
        internalCounters.push_back(30024);
        internalCounters.push_back(30143);
        internalCounters.push_back(30262);
        internalCounters.push_back(30381);
        internalCounters.push_back(30500);
        internalCounters.push_back(30619);
        internalCounters.push_back(30738);
        internalCounters.push_back(30857);
        internalCounters.push_back(30976);

        p.DefinePublicCounter("TexTriFilteringPct", "TextureUnit", "Percentage of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum64,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,+,/,(100),*", "1affc3c8-b917-5c81-622b-7004527208ae" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(23480);
        internalCounters.push_back(23599);
        internalCounters.push_back(23718);
        internalCounters.push_back(23837);
        internalCounters.push_back(23956);
        internalCounters.push_back(24075);
        internalCounters.push_back(24194);
        internalCounters.push_back(24313);
        internalCounters.push_back(24432);
        internalCounters.push_back(24551);
        internalCounters.push_back(24670);
        internalCounters.push_back(24789);
        internalCounters.push_back(24908);
        internalCounters.push_back(25027);
        internalCounters.push_back(25146);
        internalCounters.push_back(25265);
        internalCounters.push_back(25384);
        internalCounters.push_back(25503);
        internalCounters.push_back(25622);
        internalCounters.push_back(25741);
        internalCounters.push_back(25860);
        internalCounters.push_back(25979);
        internalCounters.push_back(26098);
        internalCounters.push_back(26217);
        internalCounters.push_back(26336);
        internalCounters.push_back(26455);
        internalCounters.push_back(26574);
        internalCounters.push_back(26693);
        internalCounters.push_back(26812);
        internalCounters.push_back(26931);
        internalCounters.push_back(27050);
        internalCounters.push_back(27169);
        internalCounters.push_back(27288);
        internalCounters.push_back(27407);
        internalCounters.push_back(27526);
        internalCounters.push_back(27645);
        internalCounters.push_back(27764);
        internalCounters.push_back(27883);
        internalCounters.push_back(28002);
        internalCounters.push_back(28121);
        internalCounters.push_back(28240);
        internalCounters.push_back(28359);
        internalCounters.push_back(28478);
        internalCounters.push_back(28597);
        internalCounters.push_back(28716);
        internalCounters.push_back(28835);
        internalCounters.push_back(28954);
        internalCounters.push_back(29073);
        internalCounters.push_back(29192);
        internalCounters.push_back(29311);
        internalCounters.push_back(29430);
        internalCounters.push_back(29549);
        internalCounters.push_back(29668);
        internalCounters.push_back(29787);
        internalCounters.push_back(29906);
        internalCounters.push_back(30025);
        internalCounters.push_back(30144);
        internalCounters.push_back(30263);
        internalCounters.push_back(30382);
        internalCounters.push_back(30501);
        internalCounters.push_back(30620);
        internalCounters.push_back(30739);
        internalCounters.push_back(30858);
        internalCounters.push_back(30977);

        p.DefinePublicCounter("TexTriFilteringCount", "TextureUnit", "Count of pixels that received trilinear filtering. Note that not all pixels for which trilinear filtering is enabled will receive it (e.g. if the texture is magnified).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64", "5785b3a1-a513-18db-4b1c-bdeef75bb2b6" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(23479);
        internalCounters.push_back(23598);
        internalCounters.push_back(23717);
        internalCounters.push_back(23836);
        internalCounters.push_back(23955);
        internalCounters.push_back(24074);
        internalCounters.push_back(24193);
        internalCounters.push_back(24312);
        internalCounters.push_back(24431);
        internalCounters.push_back(24550);
        internalCounters.push_back(24669);
        internalCounters.push_back(24788);
        internalCounters.push_back(24907);
        internalCounters.push_back(25026);
        internalCounters.push_back(25145);
        internalCounters.push_back(25264);
        internalCounters.push_back(25383);
        internalCounters.push_back(25502);
        internalCounters.push_back(25621);
        internalCounters.push_back(25740);
        internalCounters.push_back(25859);
        internalCounters.push_back(25978);
        internalCounters.push_back(26097);
        internalCounters.push_back(26216);
        internalCounters.push_back(26335);
        internalCounters.push_back(26454);
        internalCounters.push_back(26573);
        internalCounters.push_back(26692);
        internalCounters.push_back(26811);
        internalCounters.push_back(26930);
        internalCounters.push_back(27049);
        internalCounters.push_back(27168);
        internalCounters.push_back(27287);
        internalCounters.push_back(27406);
        internalCounters.push_back(27525);
        internalCounters.push_back(27644);
        internalCounters.push_back(27763);
        internalCounters.push_back(27882);
        internalCounters.push_back(28001);
        internalCounters.push_back(28120);
        internalCounters.push_back(28239);
        internalCounters.push_back(28358);
        internalCounters.push_back(28477);
        internalCounters.push_back(28596);
        internalCounters.push_back(28715);
        internalCounters.push_back(28834);
        internalCounters.push_back(28953);
        internalCounters.push_back(29072);
        internalCounters.push_back(29191);
        internalCounters.push_back(29310);
        internalCounters.push_back(29429);
        internalCounters.push_back(29548);
        internalCounters.push_back(29667);
        internalCounters.push_back(29786);
        internalCounters.push_back(29905);
        internalCounters.push_back(30024);
        internalCounters.push_back(30143);
        internalCounters.push_back(30262);
        internalCounters.push_back(30381);
        internalCounters.push_back(30500);
        internalCounters.push_back(30619);
        internalCounters.push_back(30738);
        internalCounters.push_back(30857);
        internalCounters.push_back(30976);

        p.DefinePublicCounter("NoTexTriFilteringCount", "TextureUnit", "Count of pixels that did not receive trilinear filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64", "179da29a-81af-c06e-ce8c-a0a731ea030d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(23482);
        internalCounters.push_back(23601);
        internalCounters.push_back(23720);
        internalCounters.push_back(23839);
        internalCounters.push_back(23958);
        internalCounters.push_back(24077);
        internalCounters.push_back(24196);
        internalCounters.push_back(24315);
        internalCounters.push_back(24434);
        internalCounters.push_back(24553);
        internalCounters.push_back(24672);
        internalCounters.push_back(24791);
        internalCounters.push_back(24910);
        internalCounters.push_back(25029);
        internalCounters.push_back(25148);
        internalCounters.push_back(25267);
        internalCounters.push_back(25386);
        internalCounters.push_back(25505);
        internalCounters.push_back(25624);
        internalCounters.push_back(25743);
        internalCounters.push_back(25862);
        internalCounters.push_back(25981);
        internalCounters.push_back(26100);
        internalCounters.push_back(26219);
        internalCounters.push_back(26338);
        internalCounters.push_back(26457);
        internalCounters.push_back(26576);
        internalCounters.push_back(26695);
        internalCounters.push_back(26814);
        internalCounters.push_back(26933);
        internalCounters.push_back(27052);
        internalCounters.push_back(27171);
        internalCounters.push_back(27290);
        internalCounters.push_back(27409);
        internalCounters.push_back(27528);
        internalCounters.push_back(27647);
        internalCounters.push_back(27766);
        internalCounters.push_back(27885);
        internalCounters.push_back(28004);
        internalCounters.push_back(28123);
        internalCounters.push_back(28242);
        internalCounters.push_back(28361);
        internalCounters.push_back(28480);
        internalCounters.push_back(28599);
        internalCounters.push_back(28718);
        internalCounters.push_back(28837);
        internalCounters.push_back(28956);
        internalCounters.push_back(29075);
        internalCounters.push_back(29194);
        internalCounters.push_back(29313);
        internalCounters.push_back(29432);
        internalCounters.push_back(29551);
        internalCounters.push_back(29670);
        internalCounters.push_back(29789);
        internalCounters.push_back(29908);
        internalCounters.push_back(30027);
        internalCounters.push_back(30146);
        internalCounters.push_back(30265);
        internalCounters.push_back(30384);
        internalCounters.push_back(30503);
        internalCounters.push_back(30622);
        internalCounters.push_back(30741);
        internalCounters.push_back(30860);
        internalCounters.push_back(30979);
        internalCounters.push_back(23481);
        internalCounters.push_back(23600);
        internalCounters.push_back(23719);
        internalCounters.push_back(23838);
        internalCounters.push_back(23957);
        internalCounters.push_back(24076);
        internalCounters.push_back(24195);
        internalCounters.push_back(24314);
        internalCounters.push_back(24433);
        internalCounters.push_back(24552);
        internalCounters.push_back(24671);
        internalCounters.push_back(24790);
        internalCounters.push_back(24909);
        internalCounters.push_back(25028);
        internalCounters.push_back(25147);
        internalCounters.push_back(25266);
        internalCounters.push_back(25385);
        internalCounters.push_back(25504);
        internalCounters.push_back(25623);
        internalCounters.push_back(25742);
        internalCounters.push_back(25861);
        internalCounters.push_back(25980);
        internalCounters.push_back(26099);
        internalCounters.push_back(26218);
        internalCounters.push_back(26337);
        internalCounters.push_back(26456);
        internalCounters.push_back(26575);
        internalCounters.push_back(26694);
        internalCounters.push_back(26813);
        internalCounters.push_back(26932);
        internalCounters.push_back(27051);
        internalCounters.push_back(27170);
        internalCounters.push_back(27289);
        internalCounters.push_back(27408);
        internalCounters.push_back(27527);
        internalCounters.push_back(27646);
        internalCounters.push_back(27765);
        internalCounters.push_back(27884);
        internalCounters.push_back(28003);
        internalCounters.push_back(28122);
        internalCounters.push_back(28241);
        internalCounters.push_back(28360);
        internalCounters.push_back(28479);
        internalCounters.push_back(28598);
        internalCounters.push_back(28717);
        internalCounters.push_back(28836);
        internalCounters.push_back(28955);
        internalCounters.push_back(29074);
        internalCounters.push_back(29193);
        internalCounters.push_back(29312);
        internalCounters.push_back(29431);
        internalCounters.push_back(29550);
        internalCounters.push_back(29669);
        internalCounters.push_back(29788);
        internalCounters.push_back(29907);
        internalCounters.push_back(30026);
        internalCounters.push_back(30145);
        internalCounters.push_back(30264);
        internalCounters.push_back(30383);
        internalCounters.push_back(30502);
        internalCounters.push_back(30621);
        internalCounters.push_back(30740);
        internalCounters.push_back(30859);
        internalCounters.push_back(30978);

        p.DefinePublicCounter("TexVolFilteringPct", "TextureUnit", "Percentage of pixels that received volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum64,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,+,/,(100),*", "b5ff6bed-3178-aee4-42dd-c74391c02a2d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(23482);
        internalCounters.push_back(23601);
        internalCounters.push_back(23720);
        internalCounters.push_back(23839);
        internalCounters.push_back(23958);
        internalCounters.push_back(24077);
        internalCounters.push_back(24196);
        internalCounters.push_back(24315);
        internalCounters.push_back(24434);
        internalCounters.push_back(24553);
        internalCounters.push_back(24672);
        internalCounters.push_back(24791);
        internalCounters.push_back(24910);
        internalCounters.push_back(25029);
        internalCounters.push_back(25148);
        internalCounters.push_back(25267);
        internalCounters.push_back(25386);
        internalCounters.push_back(25505);
        internalCounters.push_back(25624);
        internalCounters.push_back(25743);
        internalCounters.push_back(25862);
        internalCounters.push_back(25981);
        internalCounters.push_back(26100);
        internalCounters.push_back(26219);
        internalCounters.push_back(26338);
        internalCounters.push_back(26457);
        internalCounters.push_back(26576);
        internalCounters.push_back(26695);
        internalCounters.push_back(26814);
        internalCounters.push_back(26933);
        internalCounters.push_back(27052);
        internalCounters.push_back(27171);
        internalCounters.push_back(27290);
        internalCounters.push_back(27409);
        internalCounters.push_back(27528);
        internalCounters.push_back(27647);
        internalCounters.push_back(27766);
        internalCounters.push_back(27885);
        internalCounters.push_back(28004);
        internalCounters.push_back(28123);
        internalCounters.push_back(28242);
        internalCounters.push_back(28361);
        internalCounters.push_back(28480);
        internalCounters.push_back(28599);
        internalCounters.push_back(28718);
        internalCounters.push_back(28837);
        internalCounters.push_back(28956);
        internalCounters.push_back(29075);
        internalCounters.push_back(29194);
        internalCounters.push_back(29313);
        internalCounters.push_back(29432);
        internalCounters.push_back(29551);
        internalCounters.push_back(29670);
        internalCounters.push_back(29789);
        internalCounters.push_back(29908);
        internalCounters.push_back(30027);
        internalCounters.push_back(30146);
        internalCounters.push_back(30265);
        internalCounters.push_back(30384);
        internalCounters.push_back(30503);
        internalCounters.push_back(30622);
        internalCounters.push_back(30741);
        internalCounters.push_back(30860);
        internalCounters.push_back(30979);

        p.DefinePublicCounter("TexVolFilteringCount", "TextureUnit", "Count of pixels that received volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64", "4bddc587-d589-8128-e18c-762eab2c871f" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(23481);
        internalCounters.push_back(23600);
        internalCounters.push_back(23719);
        internalCounters.push_back(23838);
        internalCounters.push_back(23957);
        internalCounters.push_back(24076);
        internalCounters.push_back(24195);
        internalCounters.push_back(24314);
        internalCounters.push_back(24433);
        internalCounters.push_back(24552);
        internalCounters.push_back(24671);
        internalCounters.push_back(24790);
        internalCounters.push_back(24909);
        internalCounters.push_back(25028);
        internalCounters.push_back(25147);
        internalCounters.push_back(25266);
        internalCounters.push_back(25385);
        internalCounters.push_back(25504);
        internalCounters.push_back(25623);
        internalCounters.push_back(25742);
        internalCounters.push_back(25861);
        internalCounters.push_back(25980);
        internalCounters.push_back(26099);
        internalCounters.push_back(26218);
        internalCounters.push_back(26337);
        internalCounters.push_back(26456);
        internalCounters.push_back(26575);
        internalCounters.push_back(26694);
        internalCounters.push_back(26813);
        internalCounters.push_back(26932);
        internalCounters.push_back(27051);
        internalCounters.push_back(27170);
        internalCounters.push_back(27289);
        internalCounters.push_back(27408);
        internalCounters.push_back(27527);
        internalCounters.push_back(27646);
        internalCounters.push_back(27765);
        internalCounters.push_back(27884);
        internalCounters.push_back(28003);
        internalCounters.push_back(28122);
        internalCounters.push_back(28241);
        internalCounters.push_back(28360);
        internalCounters.push_back(28479);
        internalCounters.push_back(28598);
        internalCounters.push_back(28717);
        internalCounters.push_back(28836);
        internalCounters.push_back(28955);
        internalCounters.push_back(29074);
        internalCounters.push_back(29193);
        internalCounters.push_back(29312);
        internalCounters.push_back(29431);
        internalCounters.push_back(29550);
        internalCounters.push_back(29669);
        internalCounters.push_back(29788);
        internalCounters.push_back(29907);
        internalCounters.push_back(30026);
        internalCounters.push_back(30145);
        internalCounters.push_back(30264);
        internalCounters.push_back(30383);
        internalCounters.push_back(30502);
        internalCounters.push_back(30621);
        internalCounters.push_back(30740);
        internalCounters.push_back(30859);
        internalCounters.push_back(30978);

        p.DefinePublicCounter("NoTexVolFilteringCount", "TextureUnit", "Count of pixels that did not receive volume filtering.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64", "9fe1a854-17c6-9d26-b2b9-80610cd5827d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(23500);
        internalCounters.push_back(23619);
        internalCounters.push_back(23738);
        internalCounters.push_back(23857);
        internalCounters.push_back(23976);
        internalCounters.push_back(24095);
        internalCounters.push_back(24214);
        internalCounters.push_back(24333);
        internalCounters.push_back(24452);
        internalCounters.push_back(24571);
        internalCounters.push_back(24690);
        internalCounters.push_back(24809);
        internalCounters.push_back(24928);
        internalCounters.push_back(25047);
        internalCounters.push_back(25166);
        internalCounters.push_back(25285);
        internalCounters.push_back(25404);
        internalCounters.push_back(25523);
        internalCounters.push_back(25642);
        internalCounters.push_back(25761);
        internalCounters.push_back(25880);
        internalCounters.push_back(25999);
        internalCounters.push_back(26118);
        internalCounters.push_back(26237);
        internalCounters.push_back(26356);
        internalCounters.push_back(26475);
        internalCounters.push_back(26594);
        internalCounters.push_back(26713);
        internalCounters.push_back(26832);
        internalCounters.push_back(26951);
        internalCounters.push_back(27070);
        internalCounters.push_back(27189);
        internalCounters.push_back(27308);
        internalCounters.push_back(27427);
        internalCounters.push_back(27546);
        internalCounters.push_back(27665);
        internalCounters.push_back(27784);
        internalCounters.push_back(27903);
        internalCounters.push_back(28022);
        internalCounters.push_back(28141);
        internalCounters.push_back(28260);
        internalCounters.push_back(28379);
        internalCounters.push_back(28498);
        internalCounters.push_back(28617);
        internalCounters.push_back(28736);
        internalCounters.push_back(28855);
        internalCounters.push_back(28974);
        internalCounters.push_back(29093);
        internalCounters.push_back(29212);
        internalCounters.push_back(29331);
        internalCounters.push_back(29450);
        internalCounters.push_back(29569);
        internalCounters.push_back(29688);
        internalCounters.push_back(29807);
        internalCounters.push_back(29926);
        internalCounters.push_back(30045);
        internalCounters.push_back(30164);
        internalCounters.push_back(30283);
        internalCounters.push_back(30402);
        internalCounters.push_back(30521);
        internalCounters.push_back(30640);
        internalCounters.push_back(30759);
        internalCounters.push_back(30878);
        internalCounters.push_back(30997);
        internalCounters.push_back(23501);
        internalCounters.push_back(23620);
        internalCounters.push_back(23739);
        internalCounters.push_back(23858);
        internalCounters.push_back(23977);
        internalCounters.push_back(24096);
        internalCounters.push_back(24215);
        internalCounters.push_back(24334);
        internalCounters.push_back(24453);
        internalCounters.push_back(24572);
        internalCounters.push_back(24691);
        internalCounters.push_back(24810);
        internalCounters.push_back(24929);
        internalCounters.push_back(25048);
        internalCounters.push_back(25167);
        internalCounters.push_back(25286);
        internalCounters.push_back(25405);
        internalCounters.push_back(25524);
        internalCounters.push_back(25643);
        internalCounters.push_back(25762);
        internalCounters.push_back(25881);
        internalCounters.push_back(26000);
        internalCounters.push_back(26119);
        internalCounters.push_back(26238);
        internalCounters.push_back(26357);
        internalCounters.push_back(26476);
        internalCounters.push_back(26595);
        internalCounters.push_back(26714);
        internalCounters.push_back(26833);
        internalCounters.push_back(26952);
        internalCounters.push_back(27071);
        internalCounters.push_back(27190);
        internalCounters.push_back(27309);
        internalCounters.push_back(27428);
        internalCounters.push_back(27547);
        internalCounters.push_back(27666);
        internalCounters.push_back(27785);
        internalCounters.push_back(27904);
        internalCounters.push_back(28023);
        internalCounters.push_back(28142);
        internalCounters.push_back(28261);
        internalCounters.push_back(28380);
        internalCounters.push_back(28499);
        internalCounters.push_back(28618);
        internalCounters.push_back(28737);
        internalCounters.push_back(28856);
        internalCounters.push_back(28975);
        internalCounters.push_back(29094);
        internalCounters.push_back(29213);
        internalCounters.push_back(29332);
        internalCounters.push_back(29451);
        internalCounters.push_back(29570);
        internalCounters.push_back(29689);
        internalCounters.push_back(29808);
        internalCounters.push_back(29927);
        internalCounters.push_back(30046);
        internalCounters.push_back(30165);
        internalCounters.push_back(30284);
        internalCounters.push_back(30403);
        internalCounters.push_back(30522);
        internalCounters.push_back(30641);
        internalCounters.push_back(30760);
        internalCounters.push_back(30879);
        internalCounters.push_back(30998);
        internalCounters.push_back(23502);
        internalCounters.push_back(23621);
        internalCounters.push_back(23740);
        internalCounters.push_back(23859);
        internalCounters.push_back(23978);
        internalCounters.push_back(24097);
        internalCounters.push_back(24216);
        internalCounters.push_back(24335);
        internalCounters.push_back(24454);
        internalCounters.push_back(24573);
        internalCounters.push_back(24692);
        internalCounters.push_back(24811);
        internalCounters.push_back(24930);
        internalCounters.push_back(25049);
        internalCounters.push_back(25168);
        internalCounters.push_back(25287);
        internalCounters.push_back(25406);
        internalCounters.push_back(25525);
        internalCounters.push_back(25644);
        internalCounters.push_back(25763);
        internalCounters.push_back(25882);
        internalCounters.push_back(26001);
        internalCounters.push_back(26120);
        internalCounters.push_back(26239);
        internalCounters.push_back(26358);
        internalCounters.push_back(26477);
        internalCounters.push_back(26596);
        internalCounters.push_back(26715);
        internalCounters.push_back(26834);
        internalCounters.push_back(26953);
        internalCounters.push_back(27072);
        internalCounters.push_back(27191);
        internalCounters.push_back(27310);
        internalCounters.push_back(27429);
        internalCounters.push_back(27548);
        internalCounters.push_back(27667);
        internalCounters.push_back(27786);
        internalCounters.push_back(27905);
        internalCounters.push_back(28024);
        internalCounters.push_back(28143);
        internalCounters.push_back(28262);
        internalCounters.push_back(28381);
        internalCounters.push_back(28500);
        internalCounters.push_back(28619);
        internalCounters.push_back(28738);
        internalCounters.push_back(28857);
        internalCounters.push_back(28976);
        internalCounters.push_back(29095);
        internalCounters.push_back(29214);
        internalCounters.push_back(29333);
        internalCounters.push_back(29452);
        internalCounters.push_back(29571);
        internalCounters.push_back(29690);
        internalCounters.push_back(29809);
        internalCounters.push_back(29928);
        internalCounters.push_back(30047);
        internalCounters.push_back(30166);
        internalCounters.push_back(30285);
        internalCounters.push_back(30404);
        internalCounters.push_back(30523);
        internalCounters.push_back(30642);
        internalCounters.push_back(30761);
        internalCounters.push_back(30880);
        internalCounters.push_back(30999);
        internalCounters.push_back(23503);
        internalCounters.push_back(23622);
        internalCounters.push_back(23741);
        internalCounters.push_back(23860);
        internalCounters.push_back(23979);
        internalCounters.push_back(24098);
        internalCounters.push_back(24217);
        internalCounters.push_back(24336);
        internalCounters.push_back(24455);
        internalCounters.push_back(24574);
        internalCounters.push_back(24693);
        internalCounters.push_back(24812);
        internalCounters.push_back(24931);
        internalCounters.push_back(25050);
        internalCounters.push_back(25169);
        internalCounters.push_back(25288);
        internalCounters.push_back(25407);
        internalCounters.push_back(25526);
        internalCounters.push_back(25645);
        internalCounters.push_back(25764);
        internalCounters.push_back(25883);
        internalCounters.push_back(26002);
        internalCounters.push_back(26121);
        internalCounters.push_back(26240);
        internalCounters.push_back(26359);
        internalCounters.push_back(26478);
        internalCounters.push_back(26597);
        internalCounters.push_back(26716);
        internalCounters.push_back(26835);
        internalCounters.push_back(26954);
        internalCounters.push_back(27073);
        internalCounters.push_back(27192);
        internalCounters.push_back(27311);
        internalCounters.push_back(27430);
        internalCounters.push_back(27549);
        internalCounters.push_back(27668);
        internalCounters.push_back(27787);
        internalCounters.push_back(27906);
        internalCounters.push_back(28025);
        internalCounters.push_back(28144);
        internalCounters.push_back(28263);
        internalCounters.push_back(28382);
        internalCounters.push_back(28501);
        internalCounters.push_back(28620);
        internalCounters.push_back(28739);
        internalCounters.push_back(28858);
        internalCounters.push_back(28977);
        internalCounters.push_back(29096);
        internalCounters.push_back(29215);
        internalCounters.push_back(29334);
        internalCounters.push_back(29453);
        internalCounters.push_back(29572);
        internalCounters.push_back(29691);
        internalCounters.push_back(29810);
        internalCounters.push_back(29929);
        internalCounters.push_back(30048);
        internalCounters.push_back(30167);
        internalCounters.push_back(30286);
        internalCounters.push_back(30405);
        internalCounters.push_back(30524);
        internalCounters.push_back(30643);
        internalCounters.push_back(30762);
        internalCounters.push_back(30881);
        internalCounters.push_back(31000);
        internalCounters.push_back(23504);
        internalCounters.push_back(23623);
        internalCounters.push_back(23742);
        internalCounters.push_back(23861);
        internalCounters.push_back(23980);
        internalCounters.push_back(24099);
        internalCounters.push_back(24218);
        internalCounters.push_back(24337);
        internalCounters.push_back(24456);
        internalCounters.push_back(24575);
        internalCounters.push_back(24694);
        internalCounters.push_back(24813);
        internalCounters.push_back(24932);
        internalCounters.push_back(25051);
        internalCounters.push_back(25170);
        internalCounters.push_back(25289);
        internalCounters.push_back(25408);
        internalCounters.push_back(25527);
        internalCounters.push_back(25646);
        internalCounters.push_back(25765);
        internalCounters.push_back(25884);
        internalCounters.push_back(26003);
        internalCounters.push_back(26122);
        internalCounters.push_back(26241);
        internalCounters.push_back(26360);
        internalCounters.push_back(26479);
        internalCounters.push_back(26598);
        internalCounters.push_back(26717);
        internalCounters.push_back(26836);
        internalCounters.push_back(26955);
        internalCounters.push_back(27074);
        internalCounters.push_back(27193);
        internalCounters.push_back(27312);
        internalCounters.push_back(27431);
        internalCounters.push_back(27550);
        internalCounters.push_back(27669);
        internalCounters.push_back(27788);
        internalCounters.push_back(27907);
        internalCounters.push_back(28026);
        internalCounters.push_back(28145);
        internalCounters.push_back(28264);
        internalCounters.push_back(28383);
        internalCounters.push_back(28502);
        internalCounters.push_back(28621);
        internalCounters.push_back(28740);
        internalCounters.push_back(28859);
        internalCounters.push_back(28978);
        internalCounters.push_back(29097);
        internalCounters.push_back(29216);
        internalCounters.push_back(29335);
        internalCounters.push_back(29454);
        internalCounters.push_back(29573);
        internalCounters.push_back(29692);
        internalCounters.push_back(29811);
        internalCounters.push_back(29930);
        internalCounters.push_back(30049);
        internalCounters.push_back(30168);
        internalCounters.push_back(30287);
        internalCounters.push_back(30406);
        internalCounters.push_back(30525);
        internalCounters.push_back(30644);
        internalCounters.push_back(30763);
        internalCounters.push_back(30882);
        internalCounters.push_back(31001);
        internalCounters.push_back(23505);
        internalCounters.push_back(23624);
        internalCounters.push_back(23743);
        internalCounters.push_back(23862);
        internalCounters.push_back(23981);
        internalCounters.push_back(24100);
        internalCounters.push_back(24219);
        internalCounters.push_back(24338);
        internalCounters.push_back(24457);
        internalCounters.push_back(24576);
        internalCounters.push_back(24695);
        internalCounters.push_back(24814);
        internalCounters.push_back(24933);
        internalCounters.push_back(25052);
        internalCounters.push_back(25171);
        internalCounters.push_back(25290);
        internalCounters.push_back(25409);
        internalCounters.push_back(25528);
        internalCounters.push_back(25647);
        internalCounters.push_back(25766);
        internalCounters.push_back(25885);
        internalCounters.push_back(26004);
        internalCounters.push_back(26123);
        internalCounters.push_back(26242);
        internalCounters.push_back(26361);
        internalCounters.push_back(26480);
        internalCounters.push_back(26599);
        internalCounters.push_back(26718);
        internalCounters.push_back(26837);
        internalCounters.push_back(26956);
        internalCounters.push_back(27075);
        internalCounters.push_back(27194);
        internalCounters.push_back(27313);
        internalCounters.push_back(27432);
        internalCounters.push_back(27551);
        internalCounters.push_back(27670);
        internalCounters.push_back(27789);
        internalCounters.push_back(27908);
        internalCounters.push_back(28027);
        internalCounters.push_back(28146);
        internalCounters.push_back(28265);
        internalCounters.push_back(28384);
        internalCounters.push_back(28503);
        internalCounters.push_back(28622);
        internalCounters.push_back(28741);
        internalCounters.push_back(28860);
        internalCounters.push_back(28979);
        internalCounters.push_back(29098);
        internalCounters.push_back(29217);
        internalCounters.push_back(29336);
        internalCounters.push_back(29455);
        internalCounters.push_back(29574);
        internalCounters.push_back(29693);
        internalCounters.push_back(29812);
        internalCounters.push_back(29931);
        internalCounters.push_back(30050);
        internalCounters.push_back(30169);
        internalCounters.push_back(30288);
        internalCounters.push_back(30407);
        internalCounters.push_back(30526);
        internalCounters.push_back(30645);
        internalCounters.push_back(30764);
        internalCounters.push_back(30883);
        internalCounters.push_back(31002);
        internalCounters.push_back(23506);
        internalCounters.push_back(23625);
        internalCounters.push_back(23744);
        internalCounters.push_back(23863);
        internalCounters.push_back(23982);
        internalCounters.push_back(24101);
        internalCounters.push_back(24220);
        internalCounters.push_back(24339);
        internalCounters.push_back(24458);
        internalCounters.push_back(24577);
        internalCounters.push_back(24696);
        internalCounters.push_back(24815);
        internalCounters.push_back(24934);
        internalCounters.push_back(25053);
        internalCounters.push_back(25172);
        internalCounters.push_back(25291);
        internalCounters.push_back(25410);
        internalCounters.push_back(25529);
        internalCounters.push_back(25648);
        internalCounters.push_back(25767);
        internalCounters.push_back(25886);
        internalCounters.push_back(26005);
        internalCounters.push_back(26124);
        internalCounters.push_back(26243);
        internalCounters.push_back(26362);
        internalCounters.push_back(26481);
        internalCounters.push_back(26600);
        internalCounters.push_back(26719);
        internalCounters.push_back(26838);
        internalCounters.push_back(26957);
        internalCounters.push_back(27076);
        internalCounters.push_back(27195);
        internalCounters.push_back(27314);
        internalCounters.push_back(27433);
        internalCounters.push_back(27552);
        internalCounters.push_back(27671);
        internalCounters.push_back(27790);
        internalCounters.push_back(27909);
        internalCounters.push_back(28028);
        internalCounters.push_back(28147);
        internalCounters.push_back(28266);
        internalCounters.push_back(28385);
        internalCounters.push_back(28504);
        internalCounters.push_back(28623);
        internalCounters.push_back(28742);
        internalCounters.push_back(28861);
        internalCounters.push_back(28980);
        internalCounters.push_back(29099);
        internalCounters.push_back(29218);
        internalCounters.push_back(29337);
        internalCounters.push_back(29456);
        internalCounters.push_back(29575);
        internalCounters.push_back(29694);
        internalCounters.push_back(29813);
        internalCounters.push_back(29932);
        internalCounters.push_back(30051);
        internalCounters.push_back(30170);
        internalCounters.push_back(30289);
        internalCounters.push_back(30408);
        internalCounters.push_back(30527);
        internalCounters.push_back(30646);
        internalCounters.push_back(30765);
        internalCounters.push_back(30884);
        internalCounters.push_back(31003);
        internalCounters.push_back(23507);
        internalCounters.push_back(23626);
        internalCounters.push_back(23745);
        internalCounters.push_back(23864);
        internalCounters.push_back(23983);
        internalCounters.push_back(24102);
        internalCounters.push_back(24221);
        internalCounters.push_back(24340);
        internalCounters.push_back(24459);
        internalCounters.push_back(24578);
        internalCounters.push_back(24697);
        internalCounters.push_back(24816);
        internalCounters.push_back(24935);
        internalCounters.push_back(25054);
        internalCounters.push_back(25173);
        internalCounters.push_back(25292);
        internalCounters.push_back(25411);
        internalCounters.push_back(25530);
        internalCounters.push_back(25649);
        internalCounters.push_back(25768);
        internalCounters.push_back(25887);
        internalCounters.push_back(26006);
        internalCounters.push_back(26125);
        internalCounters.push_back(26244);
        internalCounters.push_back(26363);
        internalCounters.push_back(26482);
        internalCounters.push_back(26601);
        internalCounters.push_back(26720);
        internalCounters.push_back(26839);
        internalCounters.push_back(26958);
        internalCounters.push_back(27077);
        internalCounters.push_back(27196);
        internalCounters.push_back(27315);
        internalCounters.push_back(27434);
        internalCounters.push_back(27553);
        internalCounters.push_back(27672);
        internalCounters.push_back(27791);
        internalCounters.push_back(27910);
        internalCounters.push_back(28029);
        internalCounters.push_back(28148);
        internalCounters.push_back(28267);
        internalCounters.push_back(28386);
        internalCounters.push_back(28505);
        internalCounters.push_back(28624);
        internalCounters.push_back(28743);
        internalCounters.push_back(28862);
        internalCounters.push_back(28981);
        internalCounters.push_back(29100);
        internalCounters.push_back(29219);
        internalCounters.push_back(29338);
        internalCounters.push_back(29457);
        internalCounters.push_back(29576);
        internalCounters.push_back(29695);
        internalCounters.push_back(29814);
        internalCounters.push_back(29933);
        internalCounters.push_back(30052);
        internalCounters.push_back(30171);
        internalCounters.push_back(30290);
        internalCounters.push_back(30409);
        internalCounters.push_back(30528);
        internalCounters.push_back(30647);
        internalCounters.push_back(30766);
        internalCounters.push_back(30885);
        internalCounters.push_back(31004);
        internalCounters.push_back(23508);
        internalCounters.push_back(23627);
        internalCounters.push_back(23746);
        internalCounters.push_back(23865);
        internalCounters.push_back(23984);
        internalCounters.push_back(24103);
        internalCounters.push_back(24222);
        internalCounters.push_back(24341);
        internalCounters.push_back(24460);
        internalCounters.push_back(24579);
        internalCounters.push_back(24698);
        internalCounters.push_back(24817);
        internalCounters.push_back(24936);
        internalCounters.push_back(25055);
        internalCounters.push_back(25174);
        internalCounters.push_back(25293);
        internalCounters.push_back(25412);
        internalCounters.push_back(25531);
        internalCounters.push_back(25650);
        internalCounters.push_back(25769);
        internalCounters.push_back(25888);
        internalCounters.push_back(26007);
        internalCounters.push_back(26126);
        internalCounters.push_back(26245);
        internalCounters.push_back(26364);
        internalCounters.push_back(26483);
        internalCounters.push_back(26602);
        internalCounters.push_back(26721);
        internalCounters.push_back(26840);
        internalCounters.push_back(26959);
        internalCounters.push_back(27078);
        internalCounters.push_back(27197);
        internalCounters.push_back(27316);
        internalCounters.push_back(27435);
        internalCounters.push_back(27554);
        internalCounters.push_back(27673);
        internalCounters.push_back(27792);
        internalCounters.push_back(27911);
        internalCounters.push_back(28030);
        internalCounters.push_back(28149);
        internalCounters.push_back(28268);
        internalCounters.push_back(28387);
        internalCounters.push_back(28506);
        internalCounters.push_back(28625);
        internalCounters.push_back(28744);
        internalCounters.push_back(28863);
        internalCounters.push_back(28982);
        internalCounters.push_back(29101);
        internalCounters.push_back(29220);
        internalCounters.push_back(29339);
        internalCounters.push_back(29458);
        internalCounters.push_back(29577);
        internalCounters.push_back(29696);
        internalCounters.push_back(29815);
        internalCounters.push_back(29934);
        internalCounters.push_back(30053);
        internalCounters.push_back(30172);
        internalCounters.push_back(30291);
        internalCounters.push_back(30410);
        internalCounters.push_back(30529);
        internalCounters.push_back(30648);
        internalCounters.push_back(30767);
        internalCounters.push_back(30886);
        internalCounters.push_back(31005);

        p.DefinePublicCounter("TexAveAnisotropy", "TextureUnit", "The average degree of anisotropy applied. A number between 1 and 16. The anisotropic filtering algorithm only applies samples where they are required (e.g. there will be no extra anisotropic samples if the view vector is perpendicular to the surface) so this can be much lower than the requested anisotropy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(2),64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum64,*,+,(4),128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,sum64,*,+,(6),192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,sum64,*,+,(8),256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,sum64,*,+,(10),320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,sum64,*,+,(12),384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,433,434,435,436,437,438,439,440,441,442,443,444,445,446,447,sum64,*,+,(14),448,449,450,451,452,453,454,455,456,457,458,459,460,461,462,463,464,465,466,467,468,469,470,471,472,473,474,475,476,477,478,479,480,481,482,483,484,485,486,487,488,489,490,491,492,493,494,495,496,497,498,499,500,501,502,503,504,505,506,507,508,509,510,511,sum64,*,+,(16),512,513,514,515,516,517,518,519,520,521,522,523,524,525,526,527,528,529,530,531,532,533,534,535,536,537,538,539,540,541,542,543,544,545,546,547,548,549,550,551,552,553,554,555,556,557,558,559,560,561,562,563,564,565,566,567,568,569,570,571,572,573,574,575,sum64,*,+,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,sum64,+,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,sum64,+,192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,sum64,+,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289,290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,sum64,+,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374,375,376,377,378,379,380,381,382,383,sum64,+,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,433,434,435,436,437,438,439,440,441,442,443,444,445,446,447,sum64,+,448,449,450,451,452,453,454,455,456,457,458,459,460,461,462,463,464,465,466,467,468,469,470,471,472,473,474,475,476,477,478,479,480,481,482,483,484,485,486,487,488,489,490,491,492,493,494,495,496,497,498,499,500,501,502,503,504,505,506,507,508,509,510,511,sum64,+,512,513,514,515,516,517,518,519,520,521,522,523,524,525,526,527,528,529,530,531,532,533,534,535,536,537,538,539,540,541,542,543,544,545,546,547,548,549,550,551,552,553,554,555,556,557,558,559,560,561,562,563,564,565,566,567,568,569,570,571,572,573,574,575,sum64,+,/", "7ca2a2b9-a4eb-ce23-d163-59147e672396" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6650);
        internalCounters.push_back(6907);
        internalCounters.push_back(7164);
        internalCounters.push_back(7421);
        internalCounters.push_back(7678);
        internalCounters.push_back(7935);
        internalCounters.push_back(8192);
        internalCounters.push_back(8449);
        internalCounters.push_back(8706);
        internalCounters.push_back(8963);
        internalCounters.push_back(9220);
        internalCounters.push_back(9477);
        internalCounters.push_back(9734);
        internalCounters.push_back(9991);
        internalCounters.push_back(10248);
        internalCounters.push_back(10505);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("DepthStencilTestBusy", "Timing", "Percentage of time GPU spent performing depth and stencil tests relative to GPUBusy.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "6834fb52-42e8-bb50-fd48-ec2f2904e7e0" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6650);
        internalCounters.push_back(6907);
        internalCounters.push_back(7164);
        internalCounters.push_back(7421);
        internalCounters.push_back(7678);
        internalCounters.push_back(7935);
        internalCounters.push_back(8192);
        internalCounters.push_back(8449);
        internalCounters.push_back(8706);
        internalCounters.push_back(8963);
        internalCounters.push_back(9220);
        internalCounters.push_back(9477);
        internalCounters.push_back(9734);
        internalCounters.push_back(9991);
        internalCounters.push_back(10248);
        internalCounters.push_back(10505);

        p.DefinePublicCounter("DepthStencilTestBusyCount", "Timing", "Number of GPU cycles spent performing depth and stencil tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "e02860fa-c7bd-90ea-2149-69b4e98a636c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6521);
        internalCounters.push_back(6778);
        internalCounters.push_back(7035);
        internalCounters.push_back(7292);
        internalCounters.push_back(7549);
        internalCounters.push_back(7806);
        internalCounters.push_back(8063);
        internalCounters.push_back(8320);
        internalCounters.push_back(8577);
        internalCounters.push_back(8834);
        internalCounters.push_back(9091);
        internalCounters.push_back(9348);
        internalCounters.push_back(9605);
        internalCounters.push_back(9862);
        internalCounters.push_back(10119);
        internalCounters.push_back(10376);
        internalCounters.push_back(6510);
        internalCounters.push_back(6767);
        internalCounters.push_back(7024);
        internalCounters.push_back(7281);
        internalCounters.push_back(7538);
        internalCounters.push_back(7795);
        internalCounters.push_back(8052);
        internalCounters.push_back(8309);
        internalCounters.push_back(8566);
        internalCounters.push_back(8823);
        internalCounters.push_back(9080);
        internalCounters.push_back(9337);
        internalCounters.push_back(9594);
        internalCounters.push_back(9851);
        internalCounters.push_back(10108);
        internalCounters.push_back(10365);

        p.DefinePublicCounter("HiZTilesAccepted", "DepthAndStencil", "Percentage of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*", "56176f45-d7ff-813d-4f05-3b2f046067e7" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6510);
        internalCounters.push_back(6767);
        internalCounters.push_back(7024);
        internalCounters.push_back(7281);
        internalCounters.push_back(7538);
        internalCounters.push_back(7795);
        internalCounters.push_back(8052);
        internalCounters.push_back(8309);
        internalCounters.push_back(8566);
        internalCounters.push_back(8823);
        internalCounters.push_back(9080);
        internalCounters.push_back(9337);
        internalCounters.push_back(9594);
        internalCounters.push_back(9851);
        internalCounters.push_back(10108);
        internalCounters.push_back(10365);

        p.DefinePublicCounter("HiZTilesAcceptedCount", "DepthAndStencil", "Count of tiles accepted by HiZ and will be rendered to the depth or color buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "95d4e3f6-b2f0-f26e-8423-aacdfaf79ea3" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6521);
        internalCounters.push_back(6778);
        internalCounters.push_back(7035);
        internalCounters.push_back(7292);
        internalCounters.push_back(7549);
        internalCounters.push_back(7806);
        internalCounters.push_back(8063);
        internalCounters.push_back(8320);
        internalCounters.push_back(8577);
        internalCounters.push_back(8834);
        internalCounters.push_back(9091);
        internalCounters.push_back(9348);
        internalCounters.push_back(9605);
        internalCounters.push_back(9862);
        internalCounters.push_back(10119);
        internalCounters.push_back(10376);

        p.DefinePublicCounter("HiZTilesRejectedCount", "DepthAndStencil", "Count of tiles not accepted by HiZ.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "156ba142-7eeb-aa6e-a00a-f8aea4e41e0b" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6510);
        internalCounters.push_back(6767);
        internalCounters.push_back(7024);
        internalCounters.push_back(7281);
        internalCounters.push_back(7538);
        internalCounters.push_back(7795);
        internalCounters.push_back(8052);
        internalCounters.push_back(8309);
        internalCounters.push_back(8566);
        internalCounters.push_back(8823);
        internalCounters.push_back(9080);
        internalCounters.push_back(9337);
        internalCounters.push_back(9594);
        internalCounters.push_back(9851);
        internalCounters.push_back(10108);
        internalCounters.push_back(10365);
        internalCounters.push_back(6534);
        internalCounters.push_back(6791);
        internalCounters.push_back(7048);
        internalCounters.push_back(7305);
        internalCounters.push_back(7562);
        internalCounters.push_back(7819);
        internalCounters.push_back(8076);
        internalCounters.push_back(8333);
        internalCounters.push_back(8590);
        internalCounters.push_back(8847);
        internalCounters.push_back(9104);
        internalCounters.push_back(9361);
        internalCounters.push_back(9618);
        internalCounters.push_back(9875);
        internalCounters.push_back(10132);
        internalCounters.push_back(10389);

        p.DefinePublicCounter("PreZTilesDetailCulled", "DepthAndStencil", "Percentage of tiles rejected because the associated prim had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*", "cad7f54d-a044-7574-c472-6f2065cbeeac" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6534);
        internalCounters.push_back(6791);
        internalCounters.push_back(7048);
        internalCounters.push_back(7305);
        internalCounters.push_back(7562);
        internalCounters.push_back(7819);
        internalCounters.push_back(8076);
        internalCounters.push_back(8333);
        internalCounters.push_back(8590);
        internalCounters.push_back(8847);
        internalCounters.push_back(9104);
        internalCounters.push_back(9361);
        internalCounters.push_back(9618);
        internalCounters.push_back(9875);
        internalCounters.push_back(10132);
        internalCounters.push_back(10389);

        p.DefinePublicCounter("PreZTilesDetailCulledCount", "DepthAndStencil", "Count of tiles rejected because the associated primitive had no contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "49262c8a-b1e6-90dd-f096-0fc4921715e9" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6510);
        internalCounters.push_back(6767);
        internalCounters.push_back(7024);
        internalCounters.push_back(7281);
        internalCounters.push_back(7538);
        internalCounters.push_back(7795);
        internalCounters.push_back(8052);
        internalCounters.push_back(8309);
        internalCounters.push_back(8566);
        internalCounters.push_back(8823);
        internalCounters.push_back(9080);
        internalCounters.push_back(9337);
        internalCounters.push_back(9594);
        internalCounters.push_back(9851);
        internalCounters.push_back(10108);
        internalCounters.push_back(10365);

        p.DefinePublicCounter("PreZTilesDetailSurvivingCount", "DepthAndStencil", "Count of tiles surviving because the associated primitive had contributing area.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "f803eaa4-bbed-bd39-775f-a64df92e2c08" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11494);
        internalCounters.push_back(11891);
        internalCounters.push_back(12288);
        internalCounters.push_back(12685);
        internalCounters.push_back(11495);
        internalCounters.push_back(11892);
        internalCounters.push_back(12289);
        internalCounters.push_back(12686);
        internalCounters.push_back(11496);
        internalCounters.push_back(11893);
        internalCounters.push_back(12290);
        internalCounters.push_back(12687);
        internalCounters.push_back(11497);
        internalCounters.push_back(11894);
        internalCounters.push_back(12291);
        internalCounters.push_back(12688);
        internalCounters.push_back(11570);
        internalCounters.push_back(11967);
        internalCounters.push_back(12364);
        internalCounters.push_back(12761);
        internalCounters.push_back(11571);
        internalCounters.push_back(11968);
        internalCounters.push_back(12365);
        internalCounters.push_back(12762);
        internalCounters.push_back(11572);
        internalCounters.push_back(11969);
        internalCounters.push_back(12366);
        internalCounters.push_back(12763);
        internalCounters.push_back(11573);
        internalCounters.push_back(11970);
        internalCounters.push_back(12367);
        internalCounters.push_back(12764);

        p.DefinePublicCounter("HiZQuadsCulled", "DepthAndStencil", "Percentage of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*", "fa0e319b-5573-6d34-5bab-904769925036" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11570);
        internalCounters.push_back(11967);
        internalCounters.push_back(12364);
        internalCounters.push_back(12761);
        internalCounters.push_back(11571);
        internalCounters.push_back(11968);
        internalCounters.push_back(12365);
        internalCounters.push_back(12762);
        internalCounters.push_back(11572);
        internalCounters.push_back(11969);
        internalCounters.push_back(12366);
        internalCounters.push_back(12763);
        internalCounters.push_back(11573);
        internalCounters.push_back(11970);
        internalCounters.push_back(12367);
        internalCounters.push_back(12764);

        p.DefinePublicCounter("HiZQuadsCulledCount", "DepthAndStencil", "Count of quads that did not have to continue on in the pipeline after HiZ. They may be written directly to the depth buffer, or culled completely. Consistently low values here may suggest that the Z-range is not being fully utilized.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "73b0b39d-6df2-3e24-0b5c-7cb0ac8b6f39" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11494);
        internalCounters.push_back(11891);
        internalCounters.push_back(12288);
        internalCounters.push_back(12685);
        internalCounters.push_back(11495);
        internalCounters.push_back(11892);
        internalCounters.push_back(12289);
        internalCounters.push_back(12686);
        internalCounters.push_back(11496);
        internalCounters.push_back(11893);
        internalCounters.push_back(12290);
        internalCounters.push_back(12687);
        internalCounters.push_back(11497);
        internalCounters.push_back(11894);
        internalCounters.push_back(12291);
        internalCounters.push_back(12688);
        internalCounters.push_back(11570);
        internalCounters.push_back(11967);
        internalCounters.push_back(12364);
        internalCounters.push_back(12761);
        internalCounters.push_back(11571);
        internalCounters.push_back(11968);
        internalCounters.push_back(12365);
        internalCounters.push_back(12762);
        internalCounters.push_back(11572);
        internalCounters.push_back(11969);
        internalCounters.push_back(12366);
        internalCounters.push_back(12763);
        internalCounters.push_back(11573);
        internalCounters.push_back(11970);
        internalCounters.push_back(12367);
        internalCounters.push_back(12764);

        p.DefinePublicCounter("HiZQuadsSurvivingCount", "DepthAndStencil", "Count of quads that survive in the pipeline after HiZ.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(0),max", "5a2cd556-acb9-c81e-92bc-7ceef6012b42" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11494);
        internalCounters.push_back(11891);
        internalCounters.push_back(12288);
        internalCounters.push_back(12685);
        internalCounters.push_back(11495);
        internalCounters.push_back(11892);
        internalCounters.push_back(12289);
        internalCounters.push_back(12686);
        internalCounters.push_back(11496);
        internalCounters.push_back(11893);
        internalCounters.push_back(12290);
        internalCounters.push_back(12687);
        internalCounters.push_back(11497);
        internalCounters.push_back(11894);
        internalCounters.push_back(12291);
        internalCounters.push_back(12688);
        internalCounters.push_back(11594);
        internalCounters.push_back(11991);
        internalCounters.push_back(12388);
        internalCounters.push_back(12785);
        internalCounters.push_back(11570);
        internalCounters.push_back(11967);
        internalCounters.push_back(12364);
        internalCounters.push_back(12761);
        internalCounters.push_back(11571);
        internalCounters.push_back(11968);
        internalCounters.push_back(12365);
        internalCounters.push_back(12762);
        internalCounters.push_back(11572);
        internalCounters.push_back(11969);
        internalCounters.push_back(12366);
        internalCounters.push_back(12763);
        internalCounters.push_back(11573);
        internalCounters.push_back(11970);
        internalCounters.push_back(12367);
        internalCounters.push_back(12764);

        p.DefinePublicCounter("PreZQuadsCulled", "DepthAndStencil", "Percentage of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,sum16,16,17,18,19,sum4,-,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,/,(100),*", "4e77547b-ec55-5663-f034-af59be66d77d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11594);
        internalCounters.push_back(11991);
        internalCounters.push_back(12388);
        internalCounters.push_back(12785);
        internalCounters.push_back(11570);
        internalCounters.push_back(11967);
        internalCounters.push_back(12364);
        internalCounters.push_back(12761);
        internalCounters.push_back(11571);
        internalCounters.push_back(11968);
        internalCounters.push_back(12365);
        internalCounters.push_back(12762);
        internalCounters.push_back(11572);
        internalCounters.push_back(11969);
        internalCounters.push_back(12366);
        internalCounters.push_back(12763);
        internalCounters.push_back(11573);
        internalCounters.push_back(11970);
        internalCounters.push_back(12367);
        internalCounters.push_back(12764);

        p.DefinePublicCounter("PreZQuadsCulledCount", "DepthAndStencil", "Count of quads rejected based on the detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,sum4,+", "1bf169e6-9304-834e-df5f-0c44d7890a08" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11494);
        internalCounters.push_back(11891);
        internalCounters.push_back(12288);
        internalCounters.push_back(12685);
        internalCounters.push_back(11495);
        internalCounters.push_back(11892);
        internalCounters.push_back(12289);
        internalCounters.push_back(12686);
        internalCounters.push_back(11496);
        internalCounters.push_back(11893);
        internalCounters.push_back(12290);
        internalCounters.push_back(12687);
        internalCounters.push_back(11497);
        internalCounters.push_back(11894);
        internalCounters.push_back(12291);
        internalCounters.push_back(12688);
        internalCounters.push_back(11570);
        internalCounters.push_back(11967);
        internalCounters.push_back(12364);
        internalCounters.push_back(12761);
        internalCounters.push_back(11571);
        internalCounters.push_back(11968);
        internalCounters.push_back(12365);
        internalCounters.push_back(12762);
        internalCounters.push_back(11572);
        internalCounters.push_back(11969);
        internalCounters.push_back(12366);
        internalCounters.push_back(12763);
        internalCounters.push_back(11573);
        internalCounters.push_back(11970);
        internalCounters.push_back(12367);
        internalCounters.push_back(12764);

        p.DefinePublicCounter("PreZQuadsSurvivingCount", "DepthAndStencil", "Count of quads surviving detailZ and earlyZ tests.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(0),max", "50e25e51-3713-89cb-7f92-559cde5e5532" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11594);
        internalCounters.push_back(11991);
        internalCounters.push_back(12388);
        internalCounters.push_back(12785);
        internalCounters.push_back(11494);
        internalCounters.push_back(11891);
        internalCounters.push_back(12288);
        internalCounters.push_back(12685);
        internalCounters.push_back(11495);
        internalCounters.push_back(11892);
        internalCounters.push_back(12289);
        internalCounters.push_back(12686);
        internalCounters.push_back(11496);
        internalCounters.push_back(11893);
        internalCounters.push_back(12290);
        internalCounters.push_back(12687);
        internalCounters.push_back(11497);
        internalCounters.push_back(11894);
        internalCounters.push_back(12291);
        internalCounters.push_back(12688);

        p.DefinePublicCounter("PostZQuads", "DepthAndStencil", "Percentage of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,sum4,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,sum16,/,(100),*", "58f0d34b-eeb8-e8db-abce-cb72584144be" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(11594);
        internalCounters.push_back(11991);
        internalCounters.push_back(12388);
        internalCounters.push_back(12785);

        p.DefinePublicCounter("PostZQuadCount", "DepthAndStencil", "Count of quads for which the pixel shader will run and may be postZ tested.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,sum4", "08404526-ce35-939b-34c8-a7a35a0ff4d6" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6683);
        internalCounters.push_back(6940);
        internalCounters.push_back(7197);
        internalCounters.push_back(7454);
        internalCounters.push_back(7711);
        internalCounters.push_back(7968);
        internalCounters.push_back(8225);
        internalCounters.push_back(8482);
        internalCounters.push_back(8739);
        internalCounters.push_back(8996);
        internalCounters.push_back(9253);
        internalCounters.push_back(9510);
        internalCounters.push_back(9767);
        internalCounters.push_back(10024);
        internalCounters.push_back(10281);
        internalCounters.push_back(10538);

        p.DefinePublicCounter("PreZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z before shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "3bfe6c4d-7422-ca03-7ea5-e67ff1a00136" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6685);
        internalCounters.push_back(6942);
        internalCounters.push_back(7199);
        internalCounters.push_back(7456);
        internalCounters.push_back(7713);
        internalCounters.push_back(7970);
        internalCounters.push_back(8227);
        internalCounters.push_back(8484);
        internalCounters.push_back(8741);
        internalCounters.push_back(8998);
        internalCounters.push_back(9255);
        internalCounters.push_back(9512);
        internalCounters.push_back(9769);
        internalCounters.push_back(10026);
        internalCounters.push_back(10283);
        internalCounters.push_back(10540);

        p.DefinePublicCounter("PreZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z before shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "df7f705e-5162-d3b5-da8b-63466cf9c4e5" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6684);
        internalCounters.push_back(6941);
        internalCounters.push_back(7198);
        internalCounters.push_back(7455);
        internalCounters.push_back(7712);
        internalCounters.push_back(7969);
        internalCounters.push_back(8226);
        internalCounters.push_back(8483);
        internalCounters.push_back(8740);
        internalCounters.push_back(8997);
        internalCounters.push_back(9254);
        internalCounters.push_back(9511);
        internalCounters.push_back(9768);
        internalCounters.push_back(10025);
        internalCounters.push_back(10282);
        internalCounters.push_back(10539);

        p.DefinePublicCounter("PreZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z before shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "4484e950-f7a4-3800-bc74-78dd297f017e" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6680);
        internalCounters.push_back(6937);
        internalCounters.push_back(7194);
        internalCounters.push_back(7451);
        internalCounters.push_back(7708);
        internalCounters.push_back(7965);
        internalCounters.push_back(8222);
        internalCounters.push_back(8479);
        internalCounters.push_back(8736);
        internalCounters.push_back(8993);
        internalCounters.push_back(9250);
        internalCounters.push_back(9507);
        internalCounters.push_back(9764);
        internalCounters.push_back(10021);
        internalCounters.push_back(10278);
        internalCounters.push_back(10535);

        p.DefinePublicCounter("PostZSamplesPassing", "DepthAndStencil", "Number of samples tested for Z after shading and passed.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "4995d5d6-2330-b986-508b-fae24856f44c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6682);
        internalCounters.push_back(6939);
        internalCounters.push_back(7196);
        internalCounters.push_back(7453);
        internalCounters.push_back(7710);
        internalCounters.push_back(7967);
        internalCounters.push_back(8224);
        internalCounters.push_back(8481);
        internalCounters.push_back(8738);
        internalCounters.push_back(8995);
        internalCounters.push_back(9252);
        internalCounters.push_back(9509);
        internalCounters.push_back(9766);
        internalCounters.push_back(10023);
        internalCounters.push_back(10280);
        internalCounters.push_back(10537);

        p.DefinePublicCounter("PostZSamplesFailingS", "DepthAndStencil", "Number of samples tested for Z after shading and failed stencil test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "ae558af4-f4be-3dd4-7316-b2c4dcf0def8" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6681);
        internalCounters.push_back(6938);
        internalCounters.push_back(7195);
        internalCounters.push_back(7452);
        internalCounters.push_back(7709);
        internalCounters.push_back(7966);
        internalCounters.push_back(8223);
        internalCounters.push_back(8480);
        internalCounters.push_back(8737);
        internalCounters.push_back(8994);
        internalCounters.push_back(9251);
        internalCounters.push_back(9508);
        internalCounters.push_back(9765);
        internalCounters.push_back(10022);
        internalCounters.push_back(10279);
        internalCounters.push_back(10536);

        p.DefinePublicCounter("PostZSamplesFailingZ", "DepthAndStencil", "Number of samples tested for Z after shading and failed Z test.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "b3684c94-814a-c695-c85d-a5b6ab798b35" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6552);
        internalCounters.push_back(6809);
        internalCounters.push_back(7066);
        internalCounters.push_back(7323);
        internalCounters.push_back(7580);
        internalCounters.push_back(7837);
        internalCounters.push_back(8094);
        internalCounters.push_back(8351);
        internalCounters.push_back(8608);
        internalCounters.push_back(8865);
        internalCounters.push_back(9122);
        internalCounters.push_back(9379);
        internalCounters.push_back(9636);
        internalCounters.push_back(9893);
        internalCounters.push_back(10150);
        internalCounters.push_back(10407);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("ZUnitStalled", "DepthAndStencil", "The percentage of GPUTime the depth buffer spends waiting for the color buffer to be ready to accept data. High figures here indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "5e86c3ad-1726-3157-1d01-7ed188bf854d" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6552);
        internalCounters.push_back(6809);
        internalCounters.push_back(7066);
        internalCounters.push_back(7323);
        internalCounters.push_back(7580);
        internalCounters.push_back(7837);
        internalCounters.push_back(8094);
        internalCounters.push_back(8351);
        internalCounters.push_back(8608);
        internalCounters.push_back(8865);
        internalCounters.push_back(9122);
        internalCounters.push_back(9379);
        internalCounters.push_back(9636);
        internalCounters.push_back(9893);
        internalCounters.push_back(10150);
        internalCounters.push_back(10407);

        p.DefinePublicCounter("ZUnitStalledCycles", "DepthAndStencil", "Number of GPU cycles the depth buffer spends waiting for the color buffer to be ready to accept data. Larger numbers indicate a bottleneck in color buffer operations.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_CYCLES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16", "4351fa7f-6737-2c3e-3ffb-b3addbdceedd" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6554);
        internalCounters.push_back(6811);
        internalCounters.push_back(7068);
        internalCounters.push_back(7325);
        internalCounters.push_back(7582);
        internalCounters.push_back(7839);
        internalCounters.push_back(8096);
        internalCounters.push_back(8353);
        internalCounters.push_back(8610);
        internalCounters.push_back(8867);
        internalCounters.push_back(9124);
        internalCounters.push_back(9381);
        internalCounters.push_back(9638);
        internalCounters.push_back(9895);
        internalCounters.push_back(10152);
        internalCounters.push_back(10409);
        internalCounters.push_back(6561);
        internalCounters.push_back(6818);
        internalCounters.push_back(7075);
        internalCounters.push_back(7332);
        internalCounters.push_back(7589);
        internalCounters.push_back(7846);
        internalCounters.push_back(8103);
        internalCounters.push_back(8360);
        internalCounters.push_back(8617);
        internalCounters.push_back(8874);
        internalCounters.push_back(9131);
        internalCounters.push_back(9388);
        internalCounters.push_back(9645);
        internalCounters.push_back(9902);
        internalCounters.push_back(10159);
        internalCounters.push_back(10416);

        p.DefinePublicCounter("DBMemRead", "DepthAndStencil", "Number of bytes read from the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(256),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+", "dcdb4ee7-bd50-00f7-c028-9e5f4ce888c0" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(6566);
        internalCounters.push_back(6823);
        internalCounters.push_back(7080);
        internalCounters.push_back(7337);
        internalCounters.push_back(7594);
        internalCounters.push_back(7851);
        internalCounters.push_back(8108);
        internalCounters.push_back(8365);
        internalCounters.push_back(8622);
        internalCounters.push_back(8879);
        internalCounters.push_back(9136);
        internalCounters.push_back(9393);
        internalCounters.push_back(9650);
        internalCounters.push_back(9907);
        internalCounters.push_back(10164);
        internalCounters.push_back(10421);
        internalCounters.push_back(6569);
        internalCounters.push_back(6826);
        internalCounters.push_back(7083);
        internalCounters.push_back(7340);
        internalCounters.push_back(7597);
        internalCounters.push_back(7854);
        internalCounters.push_back(8111);
        internalCounters.push_back(8368);
        internalCounters.push_back(8625);
        internalCounters.push_back(8882);
        internalCounters.push_back(9139);
        internalCounters.push_back(9396);
        internalCounters.push_back(9653);
        internalCounters.push_back(9910);
        internalCounters.push_back(10167);
        internalCounters.push_back(10424);

        p.DefinePublicCounter("DBMemWritten", "DepthAndStencil", "Number of bytes written to the depth buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+", "de5717f8-8a49-ee44-4645-10de51b37dcf" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(298);
        internalCounters.push_back(694);
        internalCounters.push_back(1090);
        internalCounters.push_back(1486);
        internalCounters.push_back(1882);
        internalCounters.push_back(2278);
        internalCounters.push_back(2674);
        internalCounters.push_back(3070);
        internalCounters.push_back(3466);
        internalCounters.push_back(3862);
        internalCounters.push_back(4258);
        internalCounters.push_back(4654);
        internalCounters.push_back(5050);
        internalCounters.push_back(5446);
        internalCounters.push_back(5842);
        internalCounters.push_back(6238);

        p.DefinePublicCounter("CBMemRead", "ColorBuffer", "Number of bytes read from the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "84b531d8-a1f8-7f49-7c27-7bc97801f1e6" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(429);
        internalCounters.push_back(825);
        internalCounters.push_back(1221);
        internalCounters.push_back(1617);
        internalCounters.push_back(2013);
        internalCounters.push_back(2409);
        internalCounters.push_back(2805);
        internalCounters.push_back(3201);
        internalCounters.push_back(3597);
        internalCounters.push_back(3993);
        internalCounters.push_back(4389);
        internalCounters.push_back(4785);
        internalCounters.push_back(5181);
        internalCounters.push_back(5577);
        internalCounters.push_back(5973);
        internalCounters.push_back(6369);
        internalCounters.push_back(296);
        internalCounters.push_back(692);
        internalCounters.push_back(1088);
        internalCounters.push_back(1484);
        internalCounters.push_back(1880);
        internalCounters.push_back(2276);
        internalCounters.push_back(2672);
        internalCounters.push_back(3068);
        internalCounters.push_back(3464);
        internalCounters.push_back(3860);
        internalCounters.push_back(4256);
        internalCounters.push_back(4652);
        internalCounters.push_back(5048);
        internalCounters.push_back(5444);
        internalCounters.push_back(5840);
        internalCounters.push_back(6236);
        internalCounters.push_back(297);
        internalCounters.push_back(693);
        internalCounters.push_back(1089);
        internalCounters.push_back(1485);
        internalCounters.push_back(1881);
        internalCounters.push_back(2277);
        internalCounters.push_back(2673);
        internalCounters.push_back(3069);
        internalCounters.push_back(3465);
        internalCounters.push_back(3861);
        internalCounters.push_back(4257);
        internalCounters.push_back(4653);
        internalCounters.push_back(5049);
        internalCounters.push_back(5445);
        internalCounters.push_back(5841);
        internalCounters.push_back(6237);
        internalCounters.push_back(298);
        internalCounters.push_back(694);
        internalCounters.push_back(1090);
        internalCounters.push_back(1486);
        internalCounters.push_back(1882);
        internalCounters.push_back(2278);
        internalCounters.push_back(2674);
        internalCounters.push_back(3070);
        internalCounters.push_back(3466);
        internalCounters.push_back(3862);
        internalCounters.push_back(4258);
        internalCounters.push_back(4654);
        internalCounters.push_back(5050);
        internalCounters.push_back(5446);
        internalCounters.push_back(5842);
        internalCounters.push_back(6238);

        p.DefinePublicCounter("CBColorAndMaskRead", "ColorBuffer", "Total number of bytes read from the color and mask buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*", "da41660e-eb6f-32ec-8a64-b32ca17bd7eb" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(288);
        internalCounters.push_back(684);
        internalCounters.push_back(1080);
        internalCounters.push_back(1476);
        internalCounters.push_back(1872);
        internalCounters.push_back(2268);
        internalCounters.push_back(2664);
        internalCounters.push_back(3060);
        internalCounters.push_back(3456);
        internalCounters.push_back(3852);
        internalCounters.push_back(4248);
        internalCounters.push_back(4644);
        internalCounters.push_back(5040);
        internalCounters.push_back(5436);
        internalCounters.push_back(5832);
        internalCounters.push_back(6228);

        p.DefinePublicCounter("CBMemWritten", "ColorBuffer", "Number of bytes written to the color buffer.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "550f8ff8-60b6-a6bf-87d0-25ac9e87de70" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(427);
        internalCounters.push_back(823);
        internalCounters.push_back(1219);
        internalCounters.push_back(1615);
        internalCounters.push_back(2011);
        internalCounters.push_back(2407);
        internalCounters.push_back(2803);
        internalCounters.push_back(3199);
        internalCounters.push_back(3595);
        internalCounters.push_back(3991);
        internalCounters.push_back(4387);
        internalCounters.push_back(4783);
        internalCounters.push_back(5179);
        internalCounters.push_back(5575);
        internalCounters.push_back(5971);
        internalCounters.push_back(6367);
        internalCounters.push_back(286);
        internalCounters.push_back(682);
        internalCounters.push_back(1078);
        internalCounters.push_back(1474);
        internalCounters.push_back(1870);
        internalCounters.push_back(2266);
        internalCounters.push_back(2662);
        internalCounters.push_back(3058);
        internalCounters.push_back(3454);
        internalCounters.push_back(3850);
        internalCounters.push_back(4246);
        internalCounters.push_back(4642);
        internalCounters.push_back(5038);
        internalCounters.push_back(5434);
        internalCounters.push_back(5830);
        internalCounters.push_back(6226);
        internalCounters.push_back(287);
        internalCounters.push_back(683);
        internalCounters.push_back(1079);
        internalCounters.push_back(1475);
        internalCounters.push_back(1871);
        internalCounters.push_back(2267);
        internalCounters.push_back(2663);
        internalCounters.push_back(3059);
        internalCounters.push_back(3455);
        internalCounters.push_back(3851);
        internalCounters.push_back(4247);
        internalCounters.push_back(4643);
        internalCounters.push_back(5039);
        internalCounters.push_back(5435);
        internalCounters.push_back(5831);
        internalCounters.push_back(6227);
        internalCounters.push_back(288);
        internalCounters.push_back(684);
        internalCounters.push_back(1080);
        internalCounters.push_back(1476);
        internalCounters.push_back(1872);
        internalCounters.push_back(2268);
        internalCounters.push_back(2664);
        internalCounters.push_back(3060);
        internalCounters.push_back(3456);
        internalCounters.push_back(3852);
        internalCounters.push_back(4248);
        internalCounters.push_back(4644);
        internalCounters.push_back(5040);
        internalCounters.push_back(5436);
        internalCounters.push_back(5832);
        internalCounters.push_back(6228);

        p.DefinePublicCounter("CBColorAndMaskWritten", "ColorBuffer", "Total number of bytes written to the color and mask buffers.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_BYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,sum64,(32),*", "29a04b69-8f5f-b770-a0f2-3453e2c99e49" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(332);
        internalCounters.push_back(728);
        internalCounters.push_back(1124);
        internalCounters.push_back(1520);
        internalCounters.push_back(1916);
        internalCounters.push_back(2312);
        internalCounters.push_back(2708);
        internalCounters.push_back(3104);
        internalCounters.push_back(3500);
        internalCounters.push_back(3896);
        internalCounters.push_back(4292);
        internalCounters.push_back(4688);
        internalCounters.push_back(5084);
        internalCounters.push_back(5480);
        internalCounters.push_back(5876);
        internalCounters.push_back(6272);
        internalCounters.push_back(177);
        internalCounters.push_back(573);
        internalCounters.push_back(969);
        internalCounters.push_back(1365);
        internalCounters.push_back(1761);
        internalCounters.push_back(2157);
        internalCounters.push_back(2553);
        internalCounters.push_back(2949);
        internalCounters.push_back(3345);
        internalCounters.push_back(3741);
        internalCounters.push_back(4137);
        internalCounters.push_back(4533);
        internalCounters.push_back(4929);
        internalCounters.push_back(5325);
        internalCounters.push_back(5721);
        internalCounters.push_back(6117);

        p.DefinePublicCounter("CBSlowPixelPct", "ColorBuffer", "Percentage of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,/,(100),*,(100),min", "5775943f-0313-7e52-9638-b24a449197bc" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(332);
        internalCounters.push_back(728);
        internalCounters.push_back(1124);
        internalCounters.push_back(1520);
        internalCounters.push_back(1916);
        internalCounters.push_back(2312);
        internalCounters.push_back(2708);
        internalCounters.push_back(3104);
        internalCounters.push_back(3500);
        internalCounters.push_back(3896);
        internalCounters.push_back(4292);
        internalCounters.push_back(4688);
        internalCounters.push_back(5084);
        internalCounters.push_back(5480);
        internalCounters.push_back(5876);
        internalCounters.push_back(6272);

        p.DefinePublicCounter("CBSlowPixelCount", "ColorBuffer", "Number of pixels written to the color buffer using a half-rate or quarter-rate format.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "47eacbb0-28c8-22b4-5c69-c00d5813bb1c" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(46102);
        internalCounters.push_back(46294);
        internalCounters.push_back(46486);
        internalCounters.push_back(46678);
        internalCounters.push_back(46870);
        internalCounters.push_back(47062);
        internalCounters.push_back(47254);
        internalCounters.push_back(47446);
        internalCounters.push_back(47638);
        internalCounters.push_back(47830);
        internalCounters.push_back(48022);
        internalCounters.push_back(48214);
        internalCounters.push_back(48406);
        internalCounters.push_back(48598);
        internalCounters.push_back(48790);
        internalCounters.push_back(48982);

        p.DefinePublicCounter("FetchSize", "GlobalMemory", "The total bytes fetched from the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "664bb3ef-6eca-86b1-1e2d-30cb897b5fa9" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(46093);
        internalCounters.push_back(46285);
        internalCounters.push_back(46477);
        internalCounters.push_back(46669);
        internalCounters.push_back(46861);
        internalCounters.push_back(47053);
        internalCounters.push_back(47245);
        internalCounters.push_back(47437);
        internalCounters.push_back(47629);
        internalCounters.push_back(47821);
        internalCounters.push_back(48013);
        internalCounters.push_back(48205);
        internalCounters.push_back(48397);
        internalCounters.push_back(48589);
        internalCounters.push_back(48781);
        internalCounters.push_back(48973);

        p.DefinePublicCounter("WriteSize", "GlobalMemory", "The total bytes written to the video memory. This is measured with all extra fetches and any cache or memory effects taken into account.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_KILOBYTES, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,(32),*", "f96f2c16-b1b4-4ec4-229c-fc82e6f80a82" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(46085);
        internalCounters.push_back(46277);
        internalCounters.push_back(46469);
        internalCounters.push_back(46661);
        internalCounters.push_back(46853);
        internalCounters.push_back(47045);
        internalCounters.push_back(47237);
        internalCounters.push_back(47429);
        internalCounters.push_back(47621);
        internalCounters.push_back(47813);
        internalCounters.push_back(48005);
        internalCounters.push_back(48197);
        internalCounters.push_back(48389);
        internalCounters.push_back(48581);
        internalCounters.push_back(48773);
        internalCounters.push_back(48965);
        internalCounters.push_back(46086);
        internalCounters.push_back(46278);
        internalCounters.push_back(46470);
        internalCounters.push_back(46662);
        internalCounters.push_back(46854);
        internalCounters.push_back(47046);
        internalCounters.push_back(47238);
        internalCounters.push_back(47430);
        internalCounters.push_back(47622);
        internalCounters.push_back(47814);
        internalCounters.push_back(48006);
        internalCounters.push_back(48198);
        internalCounters.push_back(48390);
        internalCounters.push_back(48582);
        internalCounters.push_back(48774);
        internalCounters.push_back(48966);

        p.DefinePublicCounter("CacheHit", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that hit the data cache. Value range: 0% (no hit) to 100% (optimal).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "dfbeebab-f7c1-1211-e502-4aae361e2ad7" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(46085);
        internalCounters.push_back(46277);
        internalCounters.push_back(46469);
        internalCounters.push_back(46661);
        internalCounters.push_back(46853);
        internalCounters.push_back(47045);
        internalCounters.push_back(47237);
        internalCounters.push_back(47429);
        internalCounters.push_back(47621);
        internalCounters.push_back(47813);
        internalCounters.push_back(48005);
        internalCounters.push_back(48197);
        internalCounters.push_back(48389);
        internalCounters.push_back(48581);
        internalCounters.push_back(48773);
        internalCounters.push_back(48965);
        internalCounters.push_back(46086);
        internalCounters.push_back(46278);
        internalCounters.push_back(46470);
        internalCounters.push_back(46662);
        internalCounters.push_back(46854);
        internalCounters.push_back(47046);
        internalCounters.push_back(47238);
        internalCounters.push_back(47430);
        internalCounters.push_back(47622);
        internalCounters.push_back(47814);
        internalCounters.push_back(48006);
        internalCounters.push_back(48198);
        internalCounters.push_back(48390);
        internalCounters.push_back(48582);
        internalCounters.push_back(48774);
        internalCounters.push_back(48966);

        p.DefinePublicCounter("CacheMiss", "GlobalMemory", "The percentage of fetch, write, atomic, and other instructions that miss the data cache. Value range: 0% (optimal) to 100% (all miss).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*", "aebc0a53-7f87-60bd-4c4b-2b956846ef83" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(46085);
        internalCounters.push_back(46277);
        internalCounters.push_back(46469);
        internalCounters.push_back(46661);
        internalCounters.push_back(46853);
        internalCounters.push_back(47045);
        internalCounters.push_back(47237);
        internalCounters.push_back(47429);
        internalCounters.push_back(47621);
        internalCounters.push_back(47813);
        internalCounters.push_back(48005);
        internalCounters.push_back(48197);
        internalCounters.push_back(48389);
        internalCounters.push_back(48581);
        internalCounters.push_back(48773);
        internalCounters.push_back(48965);

        p.DefinePublicCounter("CacheHitCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that hit the data cache.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "43437652-1024-9737-2eb0-0899c0c1feae" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(46086);
        internalCounters.push_back(46278);
        internalCounters.push_back(46470);
        internalCounters.push_back(46662);
        internalCounters.push_back(46854);
        internalCounters.push_back(47046);
        internalCounters.push_back(47238);
        internalCounters.push_back(47430);
        internalCounters.push_back(47622);
        internalCounters.push_back(47814);
        internalCounters.push_back(48006);
        internalCounters.push_back(48198);
        internalCounters.push_back(48390);
        internalCounters.push_back(48582);
        internalCounters.push_back(48774);
        internalCounters.push_back(48966);

        p.DefinePublicCounter("CacheMissCount", "GlobalMemory", "Count of fetch, write, atomic, and other instructions that miss the data cache.", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_ITEMS, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16", "d0f8a812-f41b-644f-09d1-14ee03ea3671" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(23426);
        internalCounters.push_back(23545);
        internalCounters.push_back(23664);
        internalCounters.push_back(23783);
        internalCounters.push_back(23902);
        internalCounters.push_back(24021);
        internalCounters.push_back(24140);
        internalCounters.push_back(24259);
        internalCounters.push_back(24378);
        internalCounters.push_back(24497);
        internalCounters.push_back(24616);
        internalCounters.push_back(24735);
        internalCounters.push_back(24854);
        internalCounters.push_back(24973);
        internalCounters.push_back(25092);
        internalCounters.push_back(25211);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("MemUnitBusy", "GlobalMemory", "The percentage of GPUTime the memory unit is active. The result includes the stall time (MemUnitStalled). This is measured with all extra fetches and writes and any cache or memory effects taken into account. Value range: 0% to 100% (fetch-bound).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "a1efa380-4a72-e066-e06a-2ab71a488521" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(34550);
        internalCounters.push_back(34730);
        internalCounters.push_back(34910);
        internalCounters.push_back(35090);
        internalCounters.push_back(35270);
        internalCounters.push_back(35450);
        internalCounters.push_back(35630);
        internalCounters.push_back(35810);
        internalCounters.push_back(35990);
        internalCounters.push_back(36170);
        internalCounters.push_back(36350);
        internalCounters.push_back(36530);
        internalCounters.push_back(36710);
        internalCounters.push_back(36890);
        internalCounters.push_back(37070);
        internalCounters.push_back(37250);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("MemUnitStalled", "GlobalMemory", "The percentage of GPUTime the memory unit is stalled. Try reducing the number or size of fetches and writes if possible. Value range: 0% (optimal) to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,NUM_SHADER_ENGINES,/,(100),*", "465ba54f-d250-1453-790a-731b10d230b1" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(46095);
        internalCounters.push_back(46287);
        internalCounters.push_back(46479);
        internalCounters.push_back(46671);
        internalCounters.push_back(46863);
        internalCounters.push_back(47055);
        internalCounters.push_back(47247);
        internalCounters.push_back(47439);
        internalCounters.push_back(47631);
        internalCounters.push_back(47823);
        internalCounters.push_back(48015);
        internalCounters.push_back(48207);
        internalCounters.push_back(48399);
        internalCounters.push_back(48591);
        internalCounters.push_back(48783);
        internalCounters.push_back(48975);
        internalCounters.push_back(10620);

        p.DefinePublicCounter("WriteUnitStalled", "GlobalMemory", "The percentage of GPUTime the Write unit is stalled. Value range: 0% to 100% (bad).", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_PERCENTAGE, internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*", "594ad3ce-d1ec-10fc-7d59-25738e397d72" );
    }
}

