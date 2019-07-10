//==============================================================================
// Copyright (c) 2010-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for HSAGFX8_FIJI
//==============================================================================

#include "GPACounter.h"
#include "PublicCounterDefsHSAGfx8_Fiji.h"

// *** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPAHWCounterGfx8_Fiji.h"

namespace HSAGfx8_Fiji
{
bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_DerivedCounters& c)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(c);  // Unreferenced if there are no ASIC specific block instance registers

    if (!CounterGfx8_Fiji::MatchAsic(asicType))
    {
        return false;
    }

    CounterGfx8_Fiji::OverrideBlockInstanceCounters(asicType);

    return true;
}

}  // namespace HSAGfx8_Fiji

