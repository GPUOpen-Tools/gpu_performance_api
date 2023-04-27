//==============================================================================
// Copyright (c) 2010-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Public Counter Definitions for DX11 GFX9_GFX906.
//==============================================================================

#ifndef GPA_AUTO_GEN_COUNTER_GEN_PUBLIC_COUNTER_DEFINITIONS_DX11_GFX9_GFX906_H_
#define GPA_AUTO_GEN_COUNTER_GEN_PUBLIC_COUNTER_DEFINITIONS_DX11_GFX9_GFX906_H_

//*** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "gpa_derived_counter.h"

namespace dx11_gfx9_gfx906
{
    /// @brief Updates default GPU generation Public derived counters with ASIC specific versions if available.
    ///
    /// @param [in] desired_generation Hardware generation currently in use.
    /// @param [in] asic_type The ASIC type that is currently in use.
    /// @param [in] c Derived counters instance.
    ///
    /// @return True if the ASIC matched one available, and derivedCounters was updated.
    extern bool UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GpaDerivedCounters& c);

}  // namespace dx11_gfx9_gfx906

#endif  // GPA_AUTO_GEN_COUNTER_GEN_PUBLIC_COUNTER_DEFINITIONS_DX11_GFX9_GFX906_H_
