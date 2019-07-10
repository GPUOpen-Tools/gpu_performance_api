//==============================================================================
// Copyright (c) 2010-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for CLGFX8_CARRIZO
//==============================================================================

#include "GPACounter.h"
#include "PublicCounterDefsCLGfx8_Carrizo.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPAHWCounterGfx8_Carrizo.h"

namespace CLGfx8_Carrizo
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_DerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!CounterGfx8_Carrizo::MatchAsic(asicType))
    {
        return false;
    }

    CounterGfx8_Carrizo::OverrideBlockInstanceCounters(asicType);

    return true;
}

}  // namespace CLGfx8_Carrizo

