//==============================================================================
// Copyright (c) 2010-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  PublicCounterDefinitions for GLGFX8_FIJI
//==============================================================================

#include "PublicCounterDefsGLGfx8_Fiji.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPAInternalCountersGfx8_Fiji.h"

namespace GLGfx8_Fiji
{

bool UpdateAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_PublicCounters& p)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(p); // Unreferenced if there are no ASIC specific block instance registers

    if (!CounterGfx8_Fiji::MatchAsic(asicType))
    {
         return false;
    }

    CounterGfx8_Fiji::OverrideBlockInstanceCounters(asicType);

    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14904);
        internalCounters.push_back(2633);

        p.UpdateAsicSpecificPublicCounter("TessellatorBusy", internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14904);

        p.UpdateAsicSpecificPublicCounter("TessellatorBusyCycles", internalCounters, "0,NUM_PRIM_PIPES,/" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14800);
        internalCounters.push_back(14781);
        internalCounters.push_back(14876);

        p.UpdateAsicSpecificPublicCounter("VSVerticesIn", internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14885);

        p.UpdateAsicSpecificPublicCounter("HSPatches", internalCounters, "0" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14800);
        internalCounters.push_back(14781);
        internalCounters.push_back(14876);

        p.UpdateAsicSpecificPublicCounter("DSVerticesIn", internalCounters, "(0),0,1,1,ifnotzero,2,ifnotzero" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14789);

        p.UpdateAsicSpecificPublicCounter("GSPrimsIn", internalCounters, "0" );
    }
    {
        vector< gpa_uint32 > internalCounters;
        internalCounters.push_back(14800);
        internalCounters.push_back(14781);

        p.UpdateAsicSpecificPublicCounter("GSVerticesOut", internalCounters, "(0),0,1,ifnotzero" );
    }
    return true;

}

} // GLGfx8_Fiji

