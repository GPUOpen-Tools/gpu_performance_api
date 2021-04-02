//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for DX11 counter generation for non-AMD hardware (used simply to register the generator).
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_DX11_GPA_COUNTER_GENERATOR_DX11_NON_AMD_H_
#define GPU_PERF_API_COUNTER_GENERATOR_DX11_GPA_COUNTER_GENERATOR_DX11_NON_AMD_H_

#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx11_base.h"

/// @brief Class for DX11 counter generation for non-AMD hardware (used simply to register the generator).
class GpaCounterGeneratorDx11NonAmd : public GpaCounterGeneratorDx11Base
{
public:
    /// @brief Constructor.
    GpaCounterGeneratorDx11NonAmd();
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_DX11_GPA_COUNTER_GENERATOR_DX11_NON_AMD_H_
