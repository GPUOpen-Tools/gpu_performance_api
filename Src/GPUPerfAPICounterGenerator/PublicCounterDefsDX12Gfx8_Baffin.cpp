//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for DX12GFX8_BAFFIN
//==============================================================================

#include "PublicCounterDefsDX12Gfx8_Baffin.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPAInternalCountersGfx8_Baffin.h"

namespace DX12Gfx8_Baffin
{

bool UpdateAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_PublicCounters& p)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(p); // Unreferenced if there are no ASIC specific block instance registers

    if (!CounterGfx8_Baffin::MatchAsic(asicType))
    {
        return false;
    }

    CounterGfx8_Baffin::OverrideBlockInstanceCounters(asicType);

    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(192);
        internalCounters.push_back(339);
        internalCounters.push_back(486);
        internalCounters.push_back(633);
        internalCounters.push_back(49743);

        p.UpdateAsicSpecificPublicCounter("TessellatorBusy", internalCounters, "0,1,max,2,max,3,max,4,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(192);
        internalCounters.push_back(339);
        internalCounters.push_back(486);
        internalCounters.push_back(633);

        p.UpdateAsicSpecificPublicCounter("TessellatorBusyCycles", internalCounters, "0,1,max,2,max,3,max");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(87);
        internalCounters.push_back(234);
        internalCounters.push_back(381);
        internalCounters.push_back(528);
        internalCounters.push_back(68);
        internalCounters.push_back(215);
        internalCounters.push_back(362);
        internalCounters.push_back(509);
        internalCounters.push_back(163);
        internalCounters.push_back(310);
        internalCounters.push_back(457);
        internalCounters.push_back(604);

        p.UpdateAsicSpecificPublicCounter("VSVerticesIn", internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,4,5,6,7,sum4,ifnotzero,8,9,10,11,sum4,8,9,10,11,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(172);
        internalCounters.push_back(319);
        internalCounters.push_back(466);
        internalCounters.push_back(613);

        p.UpdateAsicSpecificPublicCounter("HSPatches", internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(87);
        internalCounters.push_back(234);
        internalCounters.push_back(381);
        internalCounters.push_back(528);
        internalCounters.push_back(68);
        internalCounters.push_back(215);
        internalCounters.push_back(362);
        internalCounters.push_back(509);
        internalCounters.push_back(163);
        internalCounters.push_back(310);
        internalCounters.push_back(457);
        internalCounters.push_back(604);

        p.UpdateAsicSpecificPublicCounter("DSVerticesIn", internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,4,5,6,7,sum4,ifnotzero,8,9,10,11,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(76);
        internalCounters.push_back(223);
        internalCounters.push_back(370);
        internalCounters.push_back(517);

        p.UpdateAsicSpecificPublicCounter("GSPrimsIn", internalCounters, "0,1,2,3,sum4");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(87);
        internalCounters.push_back(234);
        internalCounters.push_back(381);
        internalCounters.push_back(528);
        internalCounters.push_back(68);
        internalCounters.push_back(215);
        internalCounters.push_back(362);
        internalCounters.push_back(509);

        p.UpdateAsicSpecificPublicCounter("GSVerticesOut", internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,ifnotzero");
    }
    return true;

}

} // DX12Gfx8_Baffin

