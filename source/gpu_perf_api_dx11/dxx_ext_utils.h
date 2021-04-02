//==============================================================================
// Copyright (c) 2014-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DXX Utility functions
//==============================================================================

#ifndef GPU_PERF_API_DX11_DXX_EXT_UTILS_H_
#define GPU_PERF_API_DX11_DXX_EXT_UTILS_H_

#include "gpu_perf_api_dx11/dx11_include.h"

namespace dxx_ext_utils
{
    /// @brief Test if multi GPU performance extension is supported.
    ///
    /// @param [in] dxx_ext DXX extension.
    ///
    /// @return Boolean value indicating if multi GPU performance extension is supported.
    /// @retval True if Multi-GPU performance extension is supported.
    /// @retval False otherwise.
    bool IsMultiGpuPerfExtSupported(IAmdDxExt* dxx_ext);
}  // namespace dxx_ext_utils

#endif  // GPU_PERF_API_DX11_DXX_EXT_UTILS_H_
