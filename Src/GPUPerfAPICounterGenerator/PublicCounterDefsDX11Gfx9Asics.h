//==============================================================================
// Copyright (c) 2010-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  PublicCounterDefinitions ASIC file for DX11GFX9
//==============================================================================

#ifndef _PUBLIC_COUNTER_DEFS_DX11GFX9_ASICS_H_
#define _PUBLIC_COUNTER_DEFS_DX11GFX9_ASICS_H_

//*** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPAPublicCounters.h"


namespace DX11Gfx9Asics
{

/// Updates default GPU generation public counters with ASIC specific public counters if available.
/// \param desiredGeneration Hardware generation currently in use.
/// \param asicType The ASIC type that is currently in use.
/// \param publicCounters Returned set of public counters, if available.
/// \return True if the ASIC matched one available, and publicCounters was updated.
inline void UpdateAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_PublicCounters& publicCounters)
{
    UNREFERENCED_PARAMETER(desiredGeneration);
    UNREFERENCED_PARAMETER(asicType);
    UNREFERENCED_PARAMETER(publicCounters);
}

} // DX11Gfx9Asics

#endif // _PUBLIC_COUNTER_DEFS_DX11GFX9_ASICS_H_
