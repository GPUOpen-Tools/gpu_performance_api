//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for CLGFX8_TONGA
//==============================================================================

#include "PublicCounterDefsCLGfx8_Tonga.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPAInternalCountersGfx8_Tonga.h"

namespace CLGfx8_Tonga
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

    return true;

}

} // CLGfx8_Tonga

