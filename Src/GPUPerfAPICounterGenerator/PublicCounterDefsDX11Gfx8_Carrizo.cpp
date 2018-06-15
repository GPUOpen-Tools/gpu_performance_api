//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for DX11GFX8_CARRIZO
//==============================================================================

#include "PublicCounterDefsDX11Gfx8_Carrizo.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPAInternalCountersGfx8_Carrizo.h"

namespace DX11Gfx8_Carrizo
{

bool UpdateAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_DerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(c); // Unreferenced if there are no ASIC specific block instance registers

    if (!CounterGfx8_Carrizo::MatchAsic(asicType))
    {
        return false;
    }

    CounterGfx8_Carrizo::OverrideBlockInstanceCounters(asicType);

    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(49502);
        internalCounters.push_back(49649);
        internalCounters.push_back(49796);
        internalCounters.push_back(49943);
        internalCounters.push_back(10620);

        c.UpdateAsicSpecificDerivedCounter("TessellatorBusy", internalCounters, "0,1,max,2,max,3,max,4,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(49502);
        internalCounters.push_back(49649);
        internalCounters.push_back(49796);
        internalCounters.push_back(49943);

        c.UpdateAsicSpecificDerivedCounter("TessellatorBusyCycles", internalCounters, "0,1,max,2,max,3,max");
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

        c.UpdateAsicSpecificDerivedCounter("VSVerticesIn", internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,4,5,6,7,sum4,ifnotzero,8,9,10,11,sum4,8,9,10,11,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(49483);
        internalCounters.push_back(49630);
        internalCounters.push_back(49777);
        internalCounters.push_back(49924);

        c.UpdateAsicSpecificDerivedCounter("HSPatches", internalCounters, "0,1,2,3,sum4");
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

        c.UpdateAsicSpecificDerivedCounter("DSVerticesIn", internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,4,5,6,7,sum4,ifnotzero,8,9,10,11,sum4,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(49387);
        internalCounters.push_back(49534);
        internalCounters.push_back(49681);
        internalCounters.push_back(49828);

        c.UpdateAsicSpecificDerivedCounter("GSPrimsIn", internalCounters, "0,1,2,3,sum4");
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

        c.UpdateAsicSpecificDerivedCounter("GSVerticesOut", internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,ifnotzero");
    }
    return true;

}

} // DX11Gfx8_Carrizo

