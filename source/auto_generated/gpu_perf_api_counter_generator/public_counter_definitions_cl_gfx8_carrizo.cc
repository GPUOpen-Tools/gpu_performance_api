//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions for CL GFX8 _carrizo
//==============================================================================

#include "gpa_counter.h"
#include "public_counter_definitions_cl_gfx8_carrizo.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "gpa_hw_counter_gfx8_carrizo.h"

namespace cl_gfx8_carrizo
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GPA_DerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desired_generation);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!counter_gfx8_carrizo::MatchAsic(asic_type))
    {
        return false;
    }

    counter_gfx8_carrizo::OverrideBlockInstanceCounters(asic_type);

    return true;
}

}  // namespace cl_gfx8_carrizo

