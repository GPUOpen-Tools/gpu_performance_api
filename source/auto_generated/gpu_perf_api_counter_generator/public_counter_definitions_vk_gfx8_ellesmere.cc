//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions for VK GFX8 _ellesmere
//==============================================================================

#include "gpa_counter.h"
#include "public_counter_definitions_vk_gfx8_ellesmere.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "gpa_hw_counter_gfx8_ellesmere.h"

namespace vkgfx8ellesmere
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GPA_DerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!countergfx8ellesmere::MatchAsic(asic_type))
    {
        return false;
    }

    countergfx8ellesmere::OverrideBlockInstanceCounters(asic_type);

    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(192);
        internalCounters.push_back(339);
        internalCounters.push_back(486);
        internalCounters.push_back(633);
        internalCounters.push_back(49743);

        c.UpdateAsicSpecificDerivedCounter("TessellatorBusy", internalCounters, "0,1,max,2,max,3,max,4,/,(100),*");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(192);
        internalCounters.push_back(339);
        internalCounters.push_back(486);
        internalCounters.push_back(633);

        c.UpdateAsicSpecificDerivedCounter("TessellatorBusyCycles", internalCounters, "0,1,max,2,max,3,max");
    }
    {
        vector<gpa_uint32> internalCounters;
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

        c.UpdateAsicSpecificDerivedCounter("VSVerticesIn", internalCounters, "0,1,2,3,sum4,4,5,6,7,sum4,4,5,6,7,sum4,ifnotzero,8,9,10,11,sum4,8,9,10,11,sum4,ifnotzero");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(172);
        internalCounters.push_back(319);
        internalCounters.push_back(466);
        internalCounters.push_back(613);

        c.UpdateAsicSpecificDerivedCounter("HSPatches", internalCounters, "0,1,2,3,sum4");
    }
    {
        vector<gpa_uint32> internalCounters;
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

        c.UpdateAsicSpecificDerivedCounter("DSVerticesIn", internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,4,5,6,7,sum4,ifnotzero,8,9,10,11,sum4,ifnotzero");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(76);
        internalCounters.push_back(223);
        internalCounters.push_back(370);
        internalCounters.push_back(517);

        c.UpdateAsicSpecificDerivedCounter("GSPrimsIn", internalCounters, "0,1,2,3,sum4");
    }
    {
        vector<gpa_uint32> internalCounters;
        internalCounters.push_back(87);
        internalCounters.push_back(234);
        internalCounters.push_back(381);
        internalCounters.push_back(528);
        internalCounters.push_back(68);
        internalCounters.push_back(215);
        internalCounters.push_back(362);
        internalCounters.push_back(509);

        c.UpdateAsicSpecificDerivedCounter("GSVerticesOut", internalCounters, "(0),0,1,2,3,sum4,4,5,6,7,sum4,ifnotzero");
    }
    return true;
}

}  // namespace vkgfx8ellesmere

