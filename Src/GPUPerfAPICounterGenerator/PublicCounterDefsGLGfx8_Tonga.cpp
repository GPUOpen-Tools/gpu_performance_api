//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for GLGFX8_TONGA
//==============================================================================

#include "PublicCounterDefsGLGfx8_Tonga.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPAInternalCountersGfx8_Tonga.h"

namespace GLGfx8_Tonga
{

bool UpdateAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_DerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(c); // Unreferenced if there are no ASIC specific block instance registers

    if (!CounterGfx8_Tonga::MatchAsic(asicType))
    {
        return false;
    }

    CounterGfx8_Tonga::OverrideBlockInstanceCounters(asicType);

    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14905);
        internalCounters.push_back(2633);

        c.UpdateAsicSpecificDerivedCounter("TessellatorBusy", internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14905);

        c.UpdateAsicSpecificDerivedCounter("TessellatorBusyCycles", internalCounters, "0,NUM_PRIM_PIPES,/");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14800);
        internalCounters.push_back(14781);
        internalCounters.push_back(14876);

        c.UpdateAsicSpecificDerivedCounter("VSVerticesIn", internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14885);

        c.UpdateAsicSpecificDerivedCounter("HSPatches", internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14800);
        internalCounters.push_back(14781);
        internalCounters.push_back(14876);

        c.UpdateAsicSpecificDerivedCounter("DSVerticesIn", internalCounters, "(0),0,1,1,ifnotzero,2,ifnotzero");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14789);

        c.UpdateAsicSpecificDerivedCounter("GSPrimsIn", internalCounters, "0");
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14800);
        internalCounters.push_back(14781);

        c.UpdateAsicSpecificDerivedCounter("GSVerticesOut", internalCounters, "(0),0,1,ifnotzero");
    }
    return true;

}

} // GLGfx8_Tonga

