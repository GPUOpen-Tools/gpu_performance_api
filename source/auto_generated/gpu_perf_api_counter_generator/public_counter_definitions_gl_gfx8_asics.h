//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions ASIC file for GL_GFX8
//==============================================================================

#ifndef _PUBLIC_COUNTER_DEFINITIONS_GL_GFX8_ASICS_H_
#define _PUBLIC_COUNTER_DEFINITIONS_GL_GFX8_ASICS_H_

//*** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "gpa_derived_counter.h"

#include "gpa_hw_counter_gl_gfx8.h"

#include "public_counter_definitions_gl_gfx8_baffin.h"
#include "public_counter_definitions_gl_gfx8_carrizo.h"
#include "public_counter_definitions_gl_gfx8_ellesmere.h"
#include "public_counter_definitions_gl_gfx8_fiji.h"
#include "public_counter_definitions_gl_gfx8_iceland.h"
#include "public_counter_definitions_gl_gfx8_tonga.h"

namespace gl_gfx8_asics
{
    /// Updates default GPU generation derived counters with ASIC specific derived counters if available.
    /// \param desired_generation Hardware generation currently in use.
    /// \param asic_type The ASIC type that is currently in use.
    /// \param c Returned set of derived counters, if available.
    /// \return True if the ASIC matched one available, and c was updated.
    inline void UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GPA_DerivedCounters& c)
    {
        // Override max block events first so we could chain these if we want
        counter_gl_gfx8::OverrideMaxBlockEvents(asic_type);

        if (gl_gfx8_baffin::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (gl_gfx8_carrizo::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (gl_gfx8_ellesmere::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (gl_gfx8_fiji::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (gl_gfx8_iceland::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (gl_gfx8_tonga::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

    }

}  // namespace gl_gfx8asics

#endif  // _PUBLIC__COUNTER_DEFINITIONS_GL_GFX8_ASICS_H_
