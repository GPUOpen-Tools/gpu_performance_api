//==============================================================================
// Copyright (c) 2010-2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief PublicCounterDefinitions ASIC file for GLGFX9
//==============================================================================

#ifndef _PUBLIC_COUNTER_DEFS_GLGFX9_ASICS_H_
#define _PUBLIC_COUNTER_DEFS_GLGFX9_ASICS_H_

//*** Note, this is an auto-generated file. Do not edit. Execute PublicCounterCompiler to rebuild.

#include "GPADerivedCounters.h"

#include "PublicCounterDefsGLGfx9_Gfx906.h"
#include "PublicCounterDefsGLGfx9_Placeholder4.h"

namespace GLGfx9Asics
{
    /// Updates default GPU generation derived counters with ASIC specific derived counters if available.
    /// \param desiredGeneration Hardware generation currently in use.
    /// \param asicType The ASIC type that is currently in use.
    /// \param c Returned set of derived counters, if available.
    /// \return True if the ASIC matched one available, and c was updated.
    inline void UpdatePublicAsicSpecificCounters(GDT_HW_GENERATION desiredGeneration, GDT_HW_ASIC_TYPE asicType, GPA_DerivedCounters& c)
    {
        if (GLGfx9_Gfx906::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, c))
        {
            return;
        }

        if (GLGfx9_Placeholder4::UpdatePublicAsicSpecificCounters(desiredGeneration, asicType, c))
        {
            return;
        }
    }

}  // namespace GLGfx9Asics

#endif  // _PUBLIC_COUNTER_DEFS_GLGFX9_ASICS_H_
