//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions for CLGFX8_CARRIZO
//==============================================================================

#ifndef _PUBLIC_COUNTER_DEFINITIONS_CL_GFX8_CARRIZO_H_
#define _PUBLIC_COUNTER_DEFINITIONS_CL_GFX8_CARRIZO_H_

//*** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "gpa_derived_counter.h"

namespace clgfx8carrizo
{
    /// Updates default GPU generation Public derived counters with ASIC specific versions if available.
    /// \param desired_generation Hardware generation currently in use.
    /// \param asic_type The ASIC type that is currently in use.
    /// \param c Derived counters instance.
    /// \return True if the ASIC matched one available, and derivedCounters was updated.
    extern bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GPA_DerivedCounters& c);

}  // namespace clgfx8carrizo

#endif  // _PUBLIC_COUNTER_DEFINITIONS_CL_GFX8_CARRIZO_H_
