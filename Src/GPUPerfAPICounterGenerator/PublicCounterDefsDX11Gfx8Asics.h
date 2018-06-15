//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions ASIC file for DX11GFX8
//==============================================================================

#ifndef _PUBLIC_COUNTER_DEFS_DX11GFX8_ASICS_H_
#define _PUBLIC_COUNTER_DEFS_DX11GFX8_ASICS_H_

//*** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPADerivedCounters.h"

#include "PublicCounterDefsDX11Gfx8_Baffin.h"
#include "PublicCounterDefsDX11Gfx8_Carrizo.h"
#include "PublicCounterDefsDX11Gfx8_Ellesmere.h"
#include "PublicCounterDefsDX11Gfx8_Fiji.h"
#include "PublicCounterDefsDX11Gfx8_Iceland.h"
#include "PublicCounterDefsDX11Gfx8_Tonga.h"

namespace DX11Gfx8Asics
{

/// Updates default GPU generation derived counters with ASIC specific derived counters if available.
/// \param desiredGeneration Hardware generation currently in use.
/// \param asicType The ASIC type that is currently in use.
/// \param counters Returned set of derived counters, if available.
/// \return True if the ASIC matched one available, and counters was updated.
inline void UpdateAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_DerivedCounters& counters)
{

    if (DX11Gfx8_Baffin::UpdateAsicSpecificCounters(desiredGeneration, asicType, counters))
    {
        return;
    }

    if (DX11Gfx8_Carrizo::UpdateAsicSpecificCounters(desiredGeneration, asicType, counters))
    {
        return;
    }

    if (DX11Gfx8_Ellesmere::UpdateAsicSpecificCounters(desiredGeneration, asicType, counters))
    {
        return;
    }

    if (DX11Gfx8_Fiji::UpdateAsicSpecificCounters(desiredGeneration, asicType, counters))
    {
        return;
    }

    if (DX11Gfx8_Iceland::UpdateAsicSpecificCounters(desiredGeneration, asicType, counters))
    {
        return;
    }

    if (DX11Gfx8_Tonga::UpdateAsicSpecificCounters(desiredGeneration, asicType, counters))
    {
        return;
    }

}

} // DX11Gfx8Asics

#endif // _PUBLIC_COUNTER_DEFS_DX11GFX8_ASICS_H_
