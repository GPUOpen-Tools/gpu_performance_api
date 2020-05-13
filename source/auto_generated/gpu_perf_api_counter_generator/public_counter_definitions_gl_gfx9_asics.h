//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions ASIC file for GLGFX9
//==============================================================================

#ifndef _PUBLIC_COUNTER_DEFINITIONS_GLGFX9_ASICS_H_
#define _PUBLIC_COUNTER_DEFINITIONS_GLGFX9_ASICS_H_

//*** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "gpa_derived_counter.h"

#include "public_counter_definitions_gl_gfx9_gfx906.h"
#include "public_counter_definitions_gl_gfx9_gfx909.h"
#include "public_counter_definitions_gl_gfx9_placeholder4.h"

namespace glgfx9asics
{
    /// Updates default GPU generation derived counters with ASIC specific derived counters if available.
    /// \param desired_generation Hardware generation currently in use.
    /// \param asic_type The ASIC type that is currently in use.
    /// \param c Returned set of derived counters, if available.
    /// \return True if the ASIC matched one available, and c was updated.
    inline void UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GPA_DerivedCounters& c)
    {
        if (glgfx9gfx906::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (glgfx9gfx909::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (glgfx9placeholder4::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }
    }

}  // namespace glgfx9asics

#endif  // _PUBLIC__COUNTER_DEFINITIONS_GLGFX9_ASICS_H_
