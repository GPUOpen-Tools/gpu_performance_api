//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for Vulkan counter generation for non-AMD hardware (used simply to register the generator).
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_VK_GPA_COUNTER_GENERATOR_VK_NON_AMD_H_
#define GPU_PERF_API_COUNTER_GENERATOR_VK_GPA_COUNTER_GENERATOR_VK_NON_AMD_H_

#include "gpu_perf_api_counter_generator/gpa_counter_generator_vk_base.h"

/// @brief Vulkan Counter Generator on non-AMD generation devices.
class GpaCounterGeneratorVkNonAmd : public GpaCounterGeneratorVkBase
{
public:
    /// @brief Constructor.
    GpaCounterGeneratorVkNonAmd();
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_VK_GPA_COUNTER_GENERATOR_VK_NON_AMD_H_
