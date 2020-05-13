//==============================================================================
// Copyright (c) 2016-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Class for DX11 counter generation for non-AMD hardware (used simply to register the generator)
//==============================================================================

#ifndef _GPA_COUNTER_GENERATOR_DX11_NON_AMD_H_
#define _GPA_COUNTER_GENERATOR_DX11_NON_AMD_H_

#include "gpa_counter_generator_dx11_base.h"

/// Class for DX11 counter generation for non-AMD hardware (used simply to register the generator)
class GPA_CounterGeneratorDX11NonAMD : public GPA_CounterGeneratorDX11Base
{
public:
    /// Constructor
    GPA_CounterGeneratorDX11NonAMD();
};

#endif  // _GPA_COUNTER_GENERATOR_DX11_NON_AMD_H_
