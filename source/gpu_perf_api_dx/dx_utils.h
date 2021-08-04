//==============================================================================
// Copyright (c) 2015-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Common DX utility function declarations
//==============================================================================

#ifndef _GPA_DX_DX_UTILS_H_
#define _GPA_DX_DX_UTILS_H_

#include <DXGI.h>

#include "gpu_performance_api/gpu_perf_api_types.h"
#include "logging.h"

/// Get the adapter description for the given device
/// @return kGpaStatusOk if adapter description access succeeded, GPA_STATUS_ERROR_* if access failed
/// @param [in] device The device
/// @param [out] adapter_desc The adapter description
GpaStatus DxGetAdapterDesc(IUnknown* device, DXGI_ADAPTER_DESC& adapter_desc);

/// Get the first monitor attached to the given device
/// @return Handle to the monitor, nullptr on error
/// @param [in] device The device
HMONITOR DxGetDeviceMonitor(IUnknown* device);

#endif  // _GPA_DX_DX_UTILS_H_
