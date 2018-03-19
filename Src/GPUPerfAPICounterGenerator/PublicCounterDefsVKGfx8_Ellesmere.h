//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for VKGFX8_ELLESMERE
//==============================================================================

#ifndef _PUBLIC_COUNTER_DEFS_VKGFX8_ELLESMERE_H_
#define _PUBLIC_COUNTER_DEFS_VKGFX8_ELLESMERE_H_

//*** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPAPublicCounters.h"

namespace VKGfx8_Ellesmere
{

/// Updates default GPU generation public counters with ASIC specific public counters if available.
/// \param desiredGeneration Hardware generation currently in use.
/// \param asicType The ASIC type that is currently in use.
/// \param p public counters instance.
/// \return True if the ASIC matched one available, and pPublicCounters was updated.
extern bool UpdateAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_PublicCounters& p);

} //VKGfx8_Ellesmere

#endif // _PUBLIC_COUNTER_DEFS_VKGFX8_ELLESMERE_H_
