//==============================================================================
// Copyright (c) 2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Array of testing values for parameterized testing.
//==============================================================================
#include <array>

#include <gtest/gtest.h>

#include "gpu_performance_api/gpu_perf_api_types.h"

inline testing::internal::ParamGenerator<GpaApiType> GetApiParametersList()
{
    constexpr std::array kApiList = {
#if DX11
        kGpaApiDirectx11,
#endif
#if DX12
        kGpaApiDirectx12,
#endif
#if VK
        kGpaApiVulkan,
#endif
#if GL
        kGpaApiOpengl,
#endif
    };
    return ::testing::ValuesIn(kApiList);
}
