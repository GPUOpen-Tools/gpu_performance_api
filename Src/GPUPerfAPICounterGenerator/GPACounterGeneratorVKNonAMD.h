//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Class for Vulkan counter generation for non-AMD hardware (used simply to register the generator)
//==============================================================================

#ifndef _GPA_COUNTER_GENERATOR_VK_NON_AMD_H_
#define _GPA_COUNTER_GENERATOR_VK_NON_AMD_H_

#include "GPACounterGeneratorVKBase.h"

/// Vulkan Counter Generator on non-AMD generation devices
class GPA_CounterGeneratorVKNonAMD : public GPA_CounterGeneratorVKBase
{
public:
    /// Constructor
    GPA_CounterGeneratorVKNonAMD();
};

#endif  // _GPA_COUNTER_GENERATOR_VK_NON_AMD_H_
