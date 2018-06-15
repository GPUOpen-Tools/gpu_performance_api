//==============================================================================
// Copyright (c) 2010-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions for GLGFX8_ELLESMERE
//==============================================================================

#ifndef _PUBLIC_COUNTER_DEFS_GLGFX8_ELLESMERE_H_
#define _PUBLIC_COUNTER_DEFS_GLGFX8_ELLESMERE_H_

//*** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPADerivedCounters.h"

namespace GLGfx8_Ellesmere
{

/// Updates default GPU generation public counters with ASIC specific public counters if available.
/// \param desiredGeneration Hardware generation currently in use.
/// \param asicType The ASIC type that is currently in use.
/// \param p public counters instance.
/// \return True if the ASIC matched one available, and c was updated.
extern bool UpdateAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_DerivedCounters& p);

} //GLGfx8_Ellesmere

#endif // _PUBLIC_COUNTER_DEFS_GLGFX8_ELLESMERE_H_
