//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions ASIC file for DX11_GFX10
//==============================================================================

#ifndef _PUBLIC_COUNTER_DEFINITIONS_DX11_GFX10_ASICS_H_
#define _PUBLIC_COUNTER_DEFINITIONS_DX11_GFX10_ASICS_H_

//*** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "gpa_derived_counter.h"

#include "gpa_hw_counter_dx11_gfx10.h"

namespace dx11_gfx10_asics
{
    /// Updates default GPU generation derived counters with ASIC specific derived counters if available.
    /// \param desired_generation Hardware generation currently in use.
    /// \param asic_type The ASIC type that is currently in use.
    /// \param c Returned set of derived counters, if available.
    /// \return True if the ASIC matched one available, and c was updated.
    inline void UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GPA_DerivedCounters& c)
    {
        UNREFERENCED_PARAMETER(desired_generation);
        UNREFERENCED_PARAMETER(asic_type);
        UNREFERENCED_PARAMETER(c);
    }

}  // namespace dx11_gfx10asics

#endif  // _PUBLIC__COUNTER_DEFINITIONS_DX11_GFX10_ASICS_H_
