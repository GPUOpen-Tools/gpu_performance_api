//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions for CL GFX9 _gfx909
//==============================================================================

#include "gpa_counter.h"
#include "public_counter_definitions_cl_gfx9_gfx909.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "gpa_hw_counter_gfx9_gfx909.h"

namespace clgfx9gfx909
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GPA_DerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!countergfx9gfx909::MatchAsic(asic_type))
    {
        return false;
    }

    countergfx9gfx909::OverrideBlockInstanceCounters(asic_type);

    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9428);
        internalCounters.push_back(9710);
        internalCounters.push_back(9992);
        internalCounters.push_back(10274);
        internalCounters.push_back(10556);
        internalCounters.push_back(10838);
        internalCounters.push_back(11120);
        internalCounters.push_back(11402);
        internalCounters.push_back(11684);
        internalCounters.push_back(11966);
        internalCounters.push_back(12248);
        internalCounters.push_back(12530);
        internalCounters.push_back(12812);
        internalCounters.push_back(13094);
        internalCounters.push_back(13376);
        internalCounters.push_back(13658);
        internalCounters.push_back(9429);
        internalCounters.push_back(9711);
        internalCounters.push_back(9993);
        internalCounters.push_back(10275);
        internalCounters.push_back(10557);
        internalCounters.push_back(10839);
        internalCounters.push_back(11121);
        internalCounters.push_back(11403);
        internalCounters.push_back(11685);
        internalCounters.push_back(11967);
        internalCounters.push_back(12249);
        internalCounters.push_back(12531);
        internalCounters.push_back(12813);
        internalCounters.push_back(13095);
        internalCounters.push_back(13377);
        internalCounters.push_back(13659);

        c.UpdateAsicSpecificDerivedCounter("FetchSize", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(64),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+,(1024),/");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9416);
        internalCounters.push_back(9698);
        internalCounters.push_back(9980);
        internalCounters.push_back(10262);
        internalCounters.push_back(10544);
        internalCounters.push_back(10826);
        internalCounters.push_back(11108);
        internalCounters.push_back(11390);
        internalCounters.push_back(11672);
        internalCounters.push_back(11954);
        internalCounters.push_back(12236);
        internalCounters.push_back(12518);
        internalCounters.push_back(12800);
        internalCounters.push_back(13082);
        internalCounters.push_back(13364);
        internalCounters.push_back(13646);
        internalCounters.push_back(9417);
        internalCounters.push_back(9699);
        internalCounters.push_back(9981);
        internalCounters.push_back(10263);
        internalCounters.push_back(10545);
        internalCounters.push_back(10827);
        internalCounters.push_back(11109);
        internalCounters.push_back(11391);
        internalCounters.push_back(11673);
        internalCounters.push_back(11955);
        internalCounters.push_back(12237);
        internalCounters.push_back(12519);
        internalCounters.push_back(12801);
        internalCounters.push_back(13083);
        internalCounters.push_back(13365);
        internalCounters.push_back(13647);

        c.UpdateAsicSpecificDerivedCounter("WriteSize", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+,(1024),/");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9407);
        internalCounters.push_back(9689);
        internalCounters.push_back(9971);
        internalCounters.push_back(10253);
        internalCounters.push_back(10535);
        internalCounters.push_back(10817);
        internalCounters.push_back(11099);
        internalCounters.push_back(11381);
        internalCounters.push_back(11663);
        internalCounters.push_back(11945);
        internalCounters.push_back(12227);
        internalCounters.push_back(12509);
        internalCounters.push_back(12791);
        internalCounters.push_back(13073);
        internalCounters.push_back(13355);
        internalCounters.push_back(13637);
        internalCounters.push_back(9409);
        internalCounters.push_back(9691);
        internalCounters.push_back(9973);
        internalCounters.push_back(10255);
        internalCounters.push_back(10537);
        internalCounters.push_back(10819);
        internalCounters.push_back(11101);
        internalCounters.push_back(11383);
        internalCounters.push_back(11665);
        internalCounters.push_back(11947);
        internalCounters.push_back(12229);
        internalCounters.push_back(12511);
        internalCounters.push_back(12793);
        internalCounters.push_back(13075);
        internalCounters.push_back(13357);
        internalCounters.push_back(13639);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHit", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(9420);
        internalCounters.push_back(9702);
        internalCounters.push_back(9984);
        internalCounters.push_back(10266);
        internalCounters.push_back(10548);
        internalCounters.push_back(10830);
        internalCounters.push_back(11112);
        internalCounters.push_back(11394);
        internalCounters.push_back(11676);
        internalCounters.push_back(11958);
        internalCounters.push_back(12240);
        internalCounters.push_back(12522);
        internalCounters.push_back(12804);
        internalCounters.push_back(13086);
        internalCounters.push_back(13368);
        internalCounters.push_back(13650);
        internalCounters.push_back(1799);

        c.UpdateAsicSpecificDerivedCounter("WriteUnitStalled", internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max,16,/,(100),*");
    }
    return true;
}

}  // namespace clgfx9gfx909

