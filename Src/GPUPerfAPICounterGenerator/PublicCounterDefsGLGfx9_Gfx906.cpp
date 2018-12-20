//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for GLGFX9_GFX906
//==============================================================================

#include "GPAInternalCounter.h"
#include "PublicCounterDefsGLGfx9_Gfx906.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPAInternalCountersGfx9_Gfx906.h"

namespace GLGfx9_Gfx906
{

bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_DerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(c); // Unreferenced if there are no ASIC specific block instance registers

    if (!CounterGfx9_Gfx906::MatchAsic(asicType))
    {
        return false;
    }

    CounterGfx9_Gfx906::OverrideBlockInstanceCounters(asicType);

    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3255);
        internalCounters.push_back(3259);
        internalCounters.push_back(3211);
        internalCounters.push_back(3223);
        internalCounters.push_back(3212);
        internalCounters.push_back(3224);
        internalCounters.push_back(3098);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusy", internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max,6,/,(100),*,(100),min");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3255);
        internalCounters.push_back(3259);
        internalCounters.push_back(3211);
        internalCounters.push_back(3223);
        internalCounters.push_back(3212);
        internalCounters.push_back(3224);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusyCycles", internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3158);

        c.UpdateAsicSpecificDerivedCounter("PrimitivesIn", internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3164);
        internalCounters.push_back(3204);
        internalCounters.push_back(3205);
        internalCounters.push_back(3206);
        internalCounters.push_back(3207);

        c.UpdateAsicSpecificDerivedCounter("CulledPrims", internalCounters, "0,1,+,2,+,3,+,4,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3171);

        c.UpdateAsicSpecificDerivedCounter("ClippedPrims", internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3259);
        internalCounters.push_back(3098);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizer", internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3259);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizerCycles", internalCounters, "0,NUM_PRIM_PIPES,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3660);
        internalCounters.push_back(3661);
        internalCounters.push_back(3662);
        internalCounters.push_back(3663);
        internalCounters.push_back(3736);
        internalCounters.push_back(3737);
        internalCounters.push_back(3738);
        internalCounters.push_back(3739);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulled", internalCounters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-,0,1,+,2,+,3,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3660);
        internalCounters.push_back(3661);
        internalCounters.push_back(3662);
        internalCounters.push_back(3663);
        internalCounters.push_back(3736);
        internalCounters.push_back(3737);
        internalCounters.push_back(3738);
        internalCounters.push_back(3739);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulledCount", internalCounters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3736);
        internalCounters.push_back(3737);
        internalCounters.push_back(3738);
        internalCounters.push_back(3739);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsAcceptedCount", internalCounters, "0,1,+,2,+,3,+");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3660);
        internalCounters.push_back(3661);
        internalCounters.push_back(3662);
        internalCounters.push_back(3663);
        internalCounters.push_back(3760);
        internalCounters.push_back(3736);
        internalCounters.push_back(3737);
        internalCounters.push_back(3738);
        internalCounters.push_back(3739);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulled", internalCounters, "5,6,+,7,+,8,+,4,-,0,1,+,2,+,3,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3660);
        internalCounters.push_back(3661);
        internalCounters.push_back(3662);
        internalCounters.push_back(3663);
        internalCounters.push_back(3760);
        internalCounters.push_back(3736);
        internalCounters.push_back(3737);
        internalCounters.push_back(3738);
        internalCounters.push_back(3739);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulledCount", internalCounters, "0,1,+,2,+,3,+,4,-,5,-,6,-,7,-,8,-");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3760);
        internalCounters.push_back(3736);
        internalCounters.push_back(3737);
        internalCounters.push_back(3738);
        internalCounters.push_back(3739);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsSurvivingCount", internalCounters, "1,2,+,3,+,4,+,0,-");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3760);
        internalCounters.push_back(3660);
        internalCounters.push_back(3661);
        internalCounters.push_back(3662);
        internalCounters.push_back(3663);

        c.UpdateAsicSpecificDerivedCounter("PostZQuads", internalCounters, "0,1,2,+,3,+,4,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3760);

        c.UpdateAsicSpecificDerivedCounter("PostZQuadCount", internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9383);
        internalCounters.push_back(9665);
        internalCounters.push_back(9947);
        internalCounters.push_back(10229);
        internalCounters.push_back(10511);
        internalCounters.push_back(10793);
        internalCounters.push_back(11075);
        internalCounters.push_back(11357);
        internalCounters.push_back(11639);
        internalCounters.push_back(11921);
        internalCounters.push_back(12203);
        internalCounters.push_back(12485);
        internalCounters.push_back(12767);
        internalCounters.push_back(13049);
        internalCounters.push_back(13331);
        internalCounters.push_back(13613);
        internalCounters.push_back(9385);
        internalCounters.push_back(9667);
        internalCounters.push_back(9949);
        internalCounters.push_back(10231);
        internalCounters.push_back(10513);
        internalCounters.push_back(10795);
        internalCounters.push_back(11077);
        internalCounters.push_back(11359);
        internalCounters.push_back(11641);
        internalCounters.push_back(11923);
        internalCounters.push_back(12205);
        internalCounters.push_back(12487);
        internalCounters.push_back(12769);
        internalCounters.push_back(13051);
        internalCounters.push_back(13333);
        internalCounters.push_back(13615);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHit", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9383);
        internalCounters.push_back(9665);
        internalCounters.push_back(9947);
        internalCounters.push_back(10229);
        internalCounters.push_back(10511);
        internalCounters.push_back(10793);
        internalCounters.push_back(11075);
        internalCounters.push_back(11357);
        internalCounters.push_back(11639);
        internalCounters.push_back(11921);
        internalCounters.push_back(12203);
        internalCounters.push_back(12485);
        internalCounters.push_back(12767);
        internalCounters.push_back(13049);
        internalCounters.push_back(13331);
        internalCounters.push_back(13613);
        internalCounters.push_back(9385);
        internalCounters.push_back(9667);
        internalCounters.push_back(9949);
        internalCounters.push_back(10231);
        internalCounters.push_back(10513);
        internalCounters.push_back(10795);
        internalCounters.push_back(11077);
        internalCounters.push_back(11359);
        internalCounters.push_back(11641);
        internalCounters.push_back(11923);
        internalCounters.push_back(12205);
        internalCounters.push_back(12487);
        internalCounters.push_back(12769);
        internalCounters.push_back(13051);
        internalCounters.push_back(13333);
        internalCounters.push_back(13615);

        c.UpdateAsicSpecificDerivedCounter("L2CacheMiss", internalCounters, "16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9383);
        internalCounters.push_back(9665);
        internalCounters.push_back(9947);
        internalCounters.push_back(10229);
        internalCounters.push_back(10511);
        internalCounters.push_back(10793);
        internalCounters.push_back(11075);
        internalCounters.push_back(11357);
        internalCounters.push_back(11639);
        internalCounters.push_back(11921);
        internalCounters.push_back(12203);
        internalCounters.push_back(12485);
        internalCounters.push_back(12767);
        internalCounters.push_back(13049);
        internalCounters.push_back(13331);
        internalCounters.push_back(13613);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHitCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(9385);
        internalCounters.push_back(9667);
        internalCounters.push_back(9949);
        internalCounters.push_back(10231);
        internalCounters.push_back(10513);
        internalCounters.push_back(10795);
        internalCounters.push_back(11077);
        internalCounters.push_back(11359);
        internalCounters.push_back(11641);
        internalCounters.push_back(11923);
        internalCounters.push_back(12205);
        internalCounters.push_back(12487);
        internalCounters.push_back(12769);
        internalCounters.push_back(13051);
        internalCounters.push_back(13333);
        internalCounters.push_back(13615);

        c.UpdateAsicSpecificDerivedCounter("L2CacheMissCount", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16");
    }
    return true;

}

} // GLGfx9_Gfx906

