//==============================================================================
// Copyright (c) 2010-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for GLGFX9_GFX906
//==============================================================================

#include "GPACounter.h"
#include "PublicCounterDefsGLGfx9_Gfx906.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPAHWCounterGfx9_Gfx906.h"

namespace GLGfx9_Gfx906
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_DerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!CounterGfx9_Gfx906::MatchAsic(asicType))
    {
        return false;
    }

    CounterGfx9_Gfx906::OverrideBlockInstanceCounters(asicType);

    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3255);
        internalCounters.push_back(3259);
        internalCounters.push_back(3211);
        internalCounters.push_back(3223);
        internalCounters.push_back(3212);
        internalCounters.push_back(3224);
        internalCounters.push_back(1775);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusy", internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max,6,/,(100),*,(100),min");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3255);
        internalCounters.push_back(3259);
        internalCounters.push_back(3211);
        internalCounters.push_back(3223);
        internalCounters.push_back(3212);
        internalCounters.push_back(3224);

        c.UpdateAsicSpecificDerivedCounter("PrimitiveAssemblyBusyCycles", internalCounters, "0,1,-,2,3,+,4,+,5,(2),*,+,SU_CLOCKS_PRIM,*,-,NUM_PRIM_PIPES,/,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3158);

        c.UpdateAsicSpecificDerivedCounter("PrimitivesIn", internalCounters, "0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3164);
        internalCounters.push_back(3204);
        internalCounters.push_back(3205);
        internalCounters.push_back(3206);
        internalCounters.push_back(3207);

        c.UpdateAsicSpecificDerivedCounter("CulledPrims", internalCounters, "0,1,+,2,+,3,+,4,+");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3171);

        c.UpdateAsicSpecificDerivedCounter("ClippedPrims", internalCounters, "0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3259);
        internalCounters.push_back(1775);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizer", internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3259);

        c.UpdateAsicSpecificDerivedCounter("PAStalledOnRasterizerCycles", internalCounters, "0,NUM_PRIM_PIPES,/");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9396);
        internalCounters.push_back(9678);
        internalCounters.push_back(9960);
        internalCounters.push_back(10242);
        internalCounters.push_back(10524);
        internalCounters.push_back(10806);
        internalCounters.push_back(11088);
        internalCounters.push_back(11370);
        internalCounters.push_back(11652);
        internalCounters.push_back(11934);
        internalCounters.push_back(12216);
        internalCounters.push_back(12498);
        internalCounters.push_back(12780);
        internalCounters.push_back(13062);
        internalCounters.push_back(13344);
        internalCounters.push_back(13626);
        internalCounters.push_back(1775);
        internalCounters.push_back(4036);
        internalCounters.push_back(4042);

        c.UpdateAsicSpecificDerivedCounter("CSWriteUnitStalled", internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*,17,18,+,ifnotzero");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9396);
        internalCounters.push_back(9678);
        internalCounters.push_back(9960);
        internalCounters.push_back(10242);
        internalCounters.push_back(10524);
        internalCounters.push_back(10806);
        internalCounters.push_back(11088);
        internalCounters.push_back(11370);
        internalCounters.push_back(11652);
        internalCounters.push_back(11934);
        internalCounters.push_back(12216);
        internalCounters.push_back(12498);
        internalCounters.push_back(12780);
        internalCounters.push_back(13062);
        internalCounters.push_back(13344);
        internalCounters.push_back(13626);
        internalCounters.push_back(4036);
        internalCounters.push_back(4042);

        c.UpdateAsicSpecificDerivedCounter("CSWriteUnitStalledCycles", internalCounters, "(0),0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,17,+,ifnotzero");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3660);
        internalCounters.push_back(3661);
        internalCounters.push_back(3662);
        internalCounters.push_back(3663);
        internalCounters.push_back(3736);
        internalCounters.push_back(3737);
        internalCounters.push_back(3738);
        internalCounters.push_back(3739);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulled", internalCounters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-,(0),max,0,1,+,2,+,3,+,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3660);
        internalCounters.push_back(3661);
        internalCounters.push_back(3662);
        internalCounters.push_back(3663);
        internalCounters.push_back(3736);
        internalCounters.push_back(3737);
        internalCounters.push_back(3738);
        internalCounters.push_back(3739);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsCulledCount", internalCounters, "0,1,+,2,+,3,+,4,5,+,6,+,7,+,-,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3736);
        internalCounters.push_back(3737);
        internalCounters.push_back(3738);
        internalCounters.push_back(3739);

        c.UpdateAsicSpecificDerivedCounter("HiZQuadsAcceptedCount", internalCounters, "0,1,+,2,+,3,+");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3660);
        internalCounters.push_back(3661);
        internalCounters.push_back(3662);
        internalCounters.push_back(3663);
        internalCounters.push_back(3760);
        internalCounters.push_back(3736);
        internalCounters.push_back(3737);
        internalCounters.push_back(3738);
        internalCounters.push_back(3739);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulled", internalCounters, "5,6,+,7,+,8,+,4,-,(0),max,0,1,+,2,+,3,+,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3660);
        internalCounters.push_back(3661);
        internalCounters.push_back(3662);
        internalCounters.push_back(3663);
        internalCounters.push_back(3760);
        internalCounters.push_back(3736);
        internalCounters.push_back(3737);
        internalCounters.push_back(3738);
        internalCounters.push_back(3739);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsCulledCount", internalCounters, "0,1,+,2,+,3,+,4,-,5,-,6,-,7,-,8,-,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3760);
        internalCounters.push_back(3736);
        internalCounters.push_back(3737);
        internalCounters.push_back(3738);
        internalCounters.push_back(3739);

        c.UpdateAsicSpecificDerivedCounter("PreZQuadsSurvivingCount", internalCounters, "1,2,+,3,+,4,+,0,-,(0),max");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3760);
        internalCounters.push_back(3660);
        internalCounters.push_back(3661);
        internalCounters.push_back(3662);
        internalCounters.push_back(3663);

        c.UpdateAsicSpecificDerivedCounter("PostZQuads", internalCounters, "0,1,2,+,3,+,4,+,/,(100),*,(100),min");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3760);

        c.UpdateAsicSpecificDerivedCounter("PostZQuadCount", internalCounters, "0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9404);
        internalCounters.push_back(9686);
        internalCounters.push_back(9968);
        internalCounters.push_back(10250);
        internalCounters.push_back(10532);
        internalCounters.push_back(10814);
        internalCounters.push_back(11096);
        internalCounters.push_back(11378);
        internalCounters.push_back(11660);
        internalCounters.push_back(11942);
        internalCounters.push_back(12224);
        internalCounters.push_back(12506);
        internalCounters.push_back(12788);
        internalCounters.push_back(13070);
        internalCounters.push_back(13352);
        internalCounters.push_back(13634);
        internalCounters.push_back(9405);
        internalCounters.push_back(9687);
        internalCounters.push_back(9969);
        internalCounters.push_back(10251);
        internalCounters.push_back(10533);
        internalCounters.push_back(10815);
        internalCounters.push_back(11097);
        internalCounters.push_back(11379);
        internalCounters.push_back(11661);
        internalCounters.push_back(11943);
        internalCounters.push_back(12225);
        internalCounters.push_back(12507);
        internalCounters.push_back(12789);
        internalCounters.push_back(13071);
        internalCounters.push_back(13353);
        internalCounters.push_back(13635);

        c.UpdateAsicSpecificDerivedCounter("FetchSize", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(64),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9392);
        internalCounters.push_back(9674);
        internalCounters.push_back(9956);
        internalCounters.push_back(10238);
        internalCounters.push_back(10520);
        internalCounters.push_back(10802);
        internalCounters.push_back(11084);
        internalCounters.push_back(11366);
        internalCounters.push_back(11648);
        internalCounters.push_back(11930);
        internalCounters.push_back(12212);
        internalCounters.push_back(12494);
        internalCounters.push_back(12776);
        internalCounters.push_back(13058);
        internalCounters.push_back(13340);
        internalCounters.push_back(13622);
        internalCounters.push_back(9393);
        internalCounters.push_back(9675);
        internalCounters.push_back(9957);
        internalCounters.push_back(10239);
        internalCounters.push_back(10521);
        internalCounters.push_back(10803);
        internalCounters.push_back(11085);
        internalCounters.push_back(11367);
        internalCounters.push_back(11649);
        internalCounters.push_back(11931);
        internalCounters.push_back(12213);
        internalCounters.push_back(12495);
        internalCounters.push_back(12777);
        internalCounters.push_back(13059);
        internalCounters.push_back(13341);
        internalCounters.push_back(13623);

        c.UpdateAsicSpecificDerivedCounter("WriteSize", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+");
    }
    {
        vector<gpa_uint32> internalCounters;
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
        vector<gpa_uint32> internalCounters;
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
        vector<gpa_uint32> internalCounters;
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
        vector<gpa_uint32> internalCounters;
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
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9396);
        internalCounters.push_back(9678);
        internalCounters.push_back(9960);
        internalCounters.push_back(10242);
        internalCounters.push_back(10524);
        internalCounters.push_back(10806);
        internalCounters.push_back(11088);
        internalCounters.push_back(11370);
        internalCounters.push_back(11652);
        internalCounters.push_back(11934);
        internalCounters.push_back(12216);
        internalCounters.push_back(12498);
        internalCounters.push_back(12780);
        internalCounters.push_back(13062);
        internalCounters.push_back(13344);
        internalCounters.push_back(13626);
        internalCounters.push_back(1775);

        c.UpdateAsicSpecificDerivedCounter("WriteUnitStalled", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16,16,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9396);
        internalCounters.push_back(9678);
        internalCounters.push_back(9960);
        internalCounters.push_back(10242);
        internalCounters.push_back(10524);
        internalCounters.push_back(10806);
        internalCounters.push_back(11088);
        internalCounters.push_back(11370);
        internalCounters.push_back(11652);
        internalCounters.push_back(11934);
        internalCounters.push_back(12216);
        internalCounters.push_back(12498);
        internalCounters.push_back(12780);
        internalCounters.push_back(13062);
        internalCounters.push_back(13344);
        internalCounters.push_back(13626);

        c.UpdateAsicSpecificDerivedCounter("WriteUnitStalledCycles", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,max16");
    }
    return true;
}

}  // namespace GLGfx9_Gfx906

