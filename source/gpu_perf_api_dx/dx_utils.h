//==============================================================================
// Copyright (c) 2015-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Common DX utility function declarations
//==============================================================================

#ifndef _GPA_DX_DX_UTILS_H_
#define _GPA_DX_DX_UTILS_H_

#include <DXGI.h>

#include "gpu_perf_api_types.h"
#include "logging.h"

/// Get the adapter description for the given device
/// \return GPA_STATUS_OK if adapter description access succeeded, GPA_STATUS_ERROR_* if access failed
/// \param[in] pDevice The device
/// \param[out] adapterDesc The adapter description
GPA_Status DXGetAdapterDesc(IUnknown* pDevice, DXGI_ADAPTER_DESC& adapterDesc);

/// Get the first monitor attached to the given device
/// \return Handle to the monitor, nullptr on error
/// \param[in] pDevice The device
HMONITOR DXGetDeviceMonitor(IUnknown* pDevice);

#endif  // _GPA_DX_DX_UTILS_H_
