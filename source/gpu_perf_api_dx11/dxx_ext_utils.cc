//==============================================================================
// Copyright (c) 2014-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DXX Utility functions
//==============================================================================

#include "gpu_perf_api_dx11/dxx_ext_utils.h"

#include "gpu_perf_api_common/gpa_common_defs.h"

/// Generate a single int from a DX extension version struct.
#define GENERATE_DXX_EXT_VERSION(major, minor) ((major << 16) + minor)

bool dxx_ext_utils::IsMultiGpuPerfExtSupported(IAmdDxExt* dxx_ext)
{
    static const unsigned int kDxExtVersion8P1 = GENERATE_DXX_EXT_VERSION(8, 1);
    AmdDxExtVersion           ext_version;
    HRESULT                   hr             = dxx_ext->GetVersion(&ext_version);
    unsigned int              dx_ext_version = GENERATE_DXX_EXT_VERSION(ext_version.majorVersion, ext_version.minorVersion);
    return (SUCCEEDED(hr) && (kDxExtVersion8P1 < dx_ext_version));
}
