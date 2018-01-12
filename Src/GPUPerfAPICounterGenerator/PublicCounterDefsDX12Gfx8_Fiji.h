//==============================================================================
// Copyright (c) 2010-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  PublicCounterDefinitions for DX12GFX8_FIJI
//==============================================================================

#ifndef _PUBLIC_COUNTER_DEFS_DX12GFX8_FIJI_H_
#define _PUBLIC_COUNTER_DEFS_DX12GFX8_FIJI_H_

//*** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPAPublicCounters.h"

namespace DX12Gfx8_Fiji
{

/// Updates default GPU generation public counters with ASIC specific public counters if available.
/// \param desiredGeneration Hardware generation currently in use.
/// \param asicType The ASIC type that is currently in use.
/// \param p public counters instance.
/// \return True if the ASIC matched one available, and pPublicCounters was updated.
extern bool UpdateAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_PublicCounters& p);

} //DX12Gfx8_Fiji

#endif // _PUBLIC_COUNTER_DEFS_DX12GFX8_FIJI_H_
