//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions for GL GFX8 _fiji
//==============================================================================

#include "gpa_counter.h"
#include "public_counter_definitions_gl_gfx8_fiji.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "gpa_hw_counter_gfx8_fiji.h"

namespace gl_gfx8_fiji
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GPA_DerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!counter_gfx8_fiji::MatchAsic(asic_type))
    {
        return false;
    }

    counter_gfx8_fiji::OverrideBlockInstanceCounters(asic_type);

    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14904);
        internalCounters.push_back(2633);

        c.UpdateAsicSpecificDerivedCounter("TessellatorBusy", internalCounters, "0,NUM_PRIM_PIPES,/,1,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14904);

        c.UpdateAsicSpecificDerivedCounter("TessellatorBusyCycles", internalCounters, "0,NUM_PRIM_PIPES,/");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14800);
        internalCounters.push_back(14781);
        internalCounters.push_back(14876);

        c.UpdateAsicSpecificDerivedCounter("VSVerticesIn", internalCounters, "0,1,1,ifnotzero,2,2,ifnotzero");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14885);

        c.UpdateAsicSpecificDerivedCounter("HSPatches", internalCounters, "0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14800);
        internalCounters.push_back(14781);
        internalCounters.push_back(14876);

        c.UpdateAsicSpecificDerivedCounter("DSVerticesIn", internalCounters, "(0),0,1,1,ifnotzero,2,ifnotzero");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14789);

        c.UpdateAsicSpecificDerivedCounter("GSPrimsIn", internalCounters, "0");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(14800);
        internalCounters.push_back(14781);

        c.UpdateAsicSpecificDerivedCounter("GSVerticesOut", internalCounters, "(0),0,1,ifnotzero");
    }
    return true;
}

}  // namespace gl_gfx8_fiji

