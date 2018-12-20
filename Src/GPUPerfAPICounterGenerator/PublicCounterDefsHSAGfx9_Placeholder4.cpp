//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for HSAGFX9_PLACEHOLDER4
//==============================================================================

#include "GPAInternalCounter.h"
#include "PublicCounterDefsHSAGfx9_Placeholder4.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPAInternalCountersGfx9_Placeholder4.h"

namespace HSAGfx9_Placeholder4
{

bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_DerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(c); // Unreferenced if there are no ASIC specific block instance registers

    if (!CounterGfx9_Placeholder4::MatchAsic(asicType))
    {
        return false;
    }

    CounterGfx9_Placeholder4::OverrideBlockInstanceCounters(asicType);

    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(3388);
        internalCounters.push_back(3670);
        internalCounters.push_back(3952);
        internalCounters.push_back(4234);
        internalCounters.push_back(4516);
        internalCounters.push_back(4798);
        internalCounters.push_back(5080);
        internalCounters.push_back(5362);
        internalCounters.push_back(5644);
        internalCounters.push_back(5926);
        internalCounters.push_back(6208);
        internalCounters.push_back(6490);
        internalCounters.push_back(6772);
        internalCounters.push_back(7054);
        internalCounters.push_back(7336);
        internalCounters.push_back(7618);
        internalCounters.push_back(3390);
        internalCounters.push_back(3672);
        internalCounters.push_back(3954);
        internalCounters.push_back(4236);
        internalCounters.push_back(4518);
        internalCounters.push_back(4800);
        internalCounters.push_back(5082);
        internalCounters.push_back(5364);
        internalCounters.push_back(5646);
        internalCounters.push_back(5928);
        internalCounters.push_back(6210);
        internalCounters.push_back(6492);
        internalCounters.push_back(6774);
        internalCounters.push_back(7056);
        internalCounters.push_back(7338);
        internalCounters.push_back(7620);

        c.UpdateAsicSpecificDerivedCounter("L2CacheHit", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,+,/,(100),*");
    }
    return true;

}

} // HSAGfx9_Placeholder4

