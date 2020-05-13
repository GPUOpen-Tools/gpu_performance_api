//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions ASIC file for DX11GFX8
//==============================================================================

#ifndef _PUBLIC_COUNTER_DEFINITIONS_DX11GFX8_ASICS_H_
#define _PUBLIC_COUNTER_DEFINITIONS_DX11GFX8_ASICS_H_

//*** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "gpa_derived_counter.h"

#include "public_counter_definitions_dx11_gfx8_baffin.h"
#include "public_counter_definitions_dx11_gfx8_carrizo.h"
#include "public_counter_definitions_dx11_gfx8_ellesmere.h"
#include "public_counter_definitions_dx11_gfx8_fiji.h"
#include "public_counter_definitions_dx11_gfx8_iceland.h"
#include "public_counter_definitions_dx11_gfx8_tonga.h"

namespace dx11gfx8asics
{
    /// Updates default GPU generation derived counters with ASIC specific derived counters if available.
    /// \param desired_generation Hardware generation currently in use.
    /// \param asic_type The ASIC type that is currently in use.
    /// \param c Returned set of derived counters, if available.
    /// \return True if the ASIC matched one available, and c was updated.
    inline void UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GPA_DerivedCounters& c)
    {
        if (dx11gfx8baffin::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (dx11gfx8carrizo::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (dx11gfx8ellesmere::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (dx11gfx8fiji::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (dx11gfx8iceland::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (dx11gfx8tonga::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }
    }

}  // namespace dx11gfx8asics

#endif  // _PUBLIC__COUNTER_DEFINITIONS_DX11GFX8_ASICS_H_
