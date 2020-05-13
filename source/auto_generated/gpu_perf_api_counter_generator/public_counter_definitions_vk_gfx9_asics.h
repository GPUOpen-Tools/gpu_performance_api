//==============================================================================
// Copyright (c) 2010-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Public Counter Definitions ASIC file for VKGFX9
//==============================================================================

#ifndef _PUBLIC_COUNTER_DEFINITIONS_VKGFX9_ASICS_H_
#define _PUBLIC_COUNTER_DEFINITIONS_VKGFX9_ASICS_H_

//*** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "gpa_derived_counter.h"

#include "public_counter_definitions_vk_gfx9_gfx906.h"
#include "public_counter_definitions_vk_gfx9_gfx909.h"
#include "public_counter_definitions_vk_gfx9_placeholder4.h"

namespace vkgfx9asics
{
    /// Updates default GPU generation derived counters with ASIC specific derived counters if available.
    /// \param desired_generation Hardware generation currently in use.
    /// \param asic_type The ASIC type that is currently in use.
    /// \param c Returned set of derived counters, if available.
    /// \return True if the ASIC matched one available, and c was updated.
    inline void UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desired_generation, GDT_HW_ASIC_TYPE asic_type, GPA_DerivedCounters& c)
    {
        if (vkgfx9gfx906::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (vkgfx9gfx909::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }

        if (vkgfx9placeholder4::UpdatePublicAsicSpecificCounters(desired_generation, asic_type, c))
        {
            return;
        }
    }

}  // namespace vkgfx9asics

#endif  // _PUBLIC__COUNTER_DEFINITIONS_VKGFX9_ASICS_H_
