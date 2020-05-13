//==============================================================================
// Copyright (c) 2017-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Class for DX12 counter generation for non-AMD hardware (used simply to register the generator)
//==============================================================================

#ifndef _GPA_COUNTER_GENERATOR_DX12_NON_AMD_H_
#define _GPA_COUNTER_GENERATOR_DX12_NON_AMD_H_

#include "gpa_counter_generator_dx12.h"

/// DX12 Counter Generator on non-AMD generation devices
class GPA_CounterGeneratorDX12NonAMD : public GPA_CounterGeneratorDX12Base
{
public:
    /// Constructor
    GPA_CounterGeneratorDX12NonAMD();
};

#endif  // _GPA_COUNTER_GENERATOR_DX12_NON_AMD_H_
