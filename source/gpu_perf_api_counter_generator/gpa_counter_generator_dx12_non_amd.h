//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for DX12 counter generation for non-AMD hardware (used simply to register the generator).
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_GPA_COUNTER_GENERATOR_DX12_NON_AMD_H_
#define GPU_PERF_API_COUNTER_GENERATOR_GPA_COUNTER_GENERATOR_DX12_NON_AMD_H_

#include "gpu_perf_api_counter_generator/gpa_counter_generator_dx12.h"

/// @brief DX12 Counter Generator on non-AMD generation devices.
class GpaCounterGeneratorDx12NonAmd : public GpaCounterGeneratorDx12Base
{
public:
    /// @brief Constructor.
    GpaCounterGeneratorDx12NonAmd();
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_GPA_COUNTER_GENERATOR_DX12_NON_AMD_H_
