//==============================================================================
// Copyright (c) 2010-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for HSAGFX9_PLACEHOLDER4
//==============================================================================

#include "GPACounter.h"
#include "PublicCounterDefsHSAGfx9_Placeholder4.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPAHWCounterGfx9_Placeholder4.h"

namespace HSAGfx9_Placeholder4
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_DerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!CounterGfx9_Placeholder4::MatchAsic(asicType))
    {
        return false;
    }

    CounterGfx9_Placeholder4::OverrideBlockInstanceCounters(asicType);

    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3409);
        internalCounters.push_back(3691);
        internalCounters.push_back(3973);
        internalCounters.push_back(4255);
        internalCounters.push_back(4537);
        internalCounters.push_back(4819);
        internalCounters.push_back(5101);
        internalCounters.push_back(5383);
        internalCounters.push_back(5665);
        internalCounters.push_back(5947);
        internalCounters.push_back(6229);
        internalCounters.push_back(6511);
        internalCounters.push_back(6793);
        internalCounters.push_back(7075);
        internalCounters.push_back(7357);
        internalCounters.push_back(7639);
        internalCounters.push_back(3410);
        internalCounters.push_back(3692);
        internalCounters.push_back(3974);
        internalCounters.push_back(4256);
        internalCounters.push_back(4538);
        internalCounters.push_back(4820);
        internalCounters.push_back(5102);
        internalCounters.push_back(5384);
        internalCounters.push_back(5666);
        internalCounters.push_back(5948);
        internalCounters.push_back(6230);
        internalCounters.push_back(6512);
        internalCounters.push_back(6794);
        internalCounters.push_back(7076);
        internalCounters.push_back(7358);
        internalCounters.push_back(7640);

        c.UpdateAsicSpecificDerivedCounter("FetchSize", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(64),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(32),*,+,(1024),/");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3397);
        internalCounters.push_back(3679);
        internalCounters.push_back(3961);
        internalCounters.push_back(4243);
        internalCounters.push_back(4525);
        internalCounters.push_back(4807);
        internalCounters.push_back(5089);
        internalCounters.push_back(5371);
        internalCounters.push_back(5653);
        internalCounters.push_back(5935);
        internalCounters.push_back(6217);
        internalCounters.push_back(6499);
        internalCounters.push_back(6781);
        internalCounters.push_back(7063);
        internalCounters.push_back(7345);
        internalCounters.push_back(7627);
        internalCounters.push_back(3398);
        internalCounters.push_back(3680);
        internalCounters.push_back(3962);
        internalCounters.push_back(4244);
        internalCounters.push_back(4526);
        internalCounters.push_back(4808);
        internalCounters.push_back(5090);
        internalCounters.push_back(5372);
        internalCounters.push_back(5654);
        internalCounters.push_back(5936);
        internalCounters.push_back(6218);
        internalCounters.push_back(6500);
        internalCounters.push_back(6782);
        internalCounters.push_back(7064);
        internalCounters.push_back(7346);
        internalCounters.push_back(7628);

        c.UpdateAsicSpecificDerivedCounter("WriteSize", internalCounters, "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,sum16,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,-,(32),*,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,sum16,(64),*,+,(1024),/");
    }
    {
        vector<gpa_uint32> internalCounters;
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
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(3401);
        internalCounters.push_back(3683);
        internalCounters.push_back(3965);
        internalCounters.push_back(4247);
        internalCounters.push_back(4529);
        internalCounters.push_back(4811);
        internalCounters.push_back(5093);
        internalCounters.push_back(5375);
        internalCounters.push_back(5657);
        internalCounters.push_back(5939);
        internalCounters.push_back(6221);
        internalCounters.push_back(6503);
        internalCounters.push_back(6785);
        internalCounters.push_back(7067);
        internalCounters.push_back(7349);
        internalCounters.push_back(7631);
        internalCounters.push_back(58);

        c.UpdateAsicSpecificDerivedCounter("WriteUnitStalled", internalCounters, "0,1,max,2,max,3,max,4,max,5,max,6,max,7,max,8,max,9,max,10,max,11,max,12,max,13,max,14,max,15,max,16,/,(100),*");
    }
    return true;
}

}  // namespace HSAGfx9_Placeholder4

