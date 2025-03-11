//==============================================================================
// Copyright (c) 2017-2022 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief DX11 include file.
//==============================================================================

#ifndef GPU_PERF_API_DX11_DX11_INCLUDE_H_
#define GPU_PERF_API_DX11_DX11_INCLUDE_H_

#include <d3d11.h>
#include <d3dcommon.h>

#include "AmdDxExtASICInfo.h"
#include "AmdDxExtASICInfoApi.h"
#include "AmdDxExtPerfProfileApi.h"

#include "gpu_perf_api_common/gpa_common_defs.h"

#define PE_BLOCK_ID_MAX PE_BLOCK_MAX_GFX12  ///< Macro for count of DX11 block id; needs an update every generation.

#endif  // GPU_PERF_API_DX11_DX11_INCLUDE_H_
