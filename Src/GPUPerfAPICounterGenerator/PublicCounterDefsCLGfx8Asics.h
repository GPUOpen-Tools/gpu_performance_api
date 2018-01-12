//==============================================================================
// Copyright (c) 2010-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  PublicCounterDefinitions ASIC file for CLGFX8
//==============================================================================

#ifndef _PUBLIC_COUNTER_DEFS_CLGFX8_ASICS_H_
#define _PUBLIC_COUNTER_DEFS_CLGFX8_ASICS_H_

//*** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPAPublicCounters.h"

#include "PublicCounterDefsCLGfx8_Baffin.h"
#include "PublicCounterDefsCLGfx8_Carrizo.h"
#include "PublicCounterDefsCLGfx8_Ellesmere.h"
#include "PublicCounterDefsCLGfx8_Fiji.h"
#include "PublicCounterDefsCLGfx8_Iceland.h"
#include "PublicCounterDefsCLGfx8_Tonga.h"

namespace CLGfx8Asics
{

/// Updates default GPU generation public counters with ASIC specific public counters if available.
/// \param desiredGeneration Hardware generation currently in use.
/// \param asicType The ASIC type that is currently in use.
/// \param publicCounters Returned set of public counters, if available.
/// \return True if the ASIC matched one available, and publicCounters was updated.
inline void UpdateAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_PublicCounters& publicCounters)
{

    if (CLGfx8_Baffin::UpdateAsicSpecificCounters(desiredGeneration, asicType, publicCounters))
    {
        return;
    }

    if (CLGfx8_Carrizo::UpdateAsicSpecificCounters(desiredGeneration, asicType, publicCounters))
    {
        return;
    }

    if (CLGfx8_Ellesmere::UpdateAsicSpecificCounters(desiredGeneration, asicType, publicCounters))
    {
        return;
    }

    if (CLGfx8_Fiji::UpdateAsicSpecificCounters(desiredGeneration, asicType, publicCounters))
    {
        return;
    }

    if (CLGfx8_Iceland::UpdateAsicSpecificCounters(desiredGeneration, asicType, publicCounters))
    {
        return;
    }

    if (CLGfx8_Tonga::UpdateAsicSpecificCounters(desiredGeneration, asicType, publicCounters))
    {
        return;
    }

}

} // CLGfx8Asics

#endif // _PUBLIC_COUNTER_DEFS_CLGFX8_ASICS_H_
