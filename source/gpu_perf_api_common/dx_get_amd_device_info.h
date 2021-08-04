//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Defines entry points in GPUPerfAPIDXGetAMDDeviceInfo dll.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_DX_GET_AMD_DEVICE_INFO_H_
#define GPU_PERF_API_COMMON_DX_GET_AMD_DEVICE_INFO_H_

#ifndef GPA_LIB_DECL
/// Macro for exporting an API function.
#ifdef __cplusplus
#define GPA_LIB_DECL extern "C" __declspec(dllimport)
#else
#define GPA_LIB_DECL __declspec(dllimport)
#endif
#endif

#include <windows.h>

/// @brief Get the vendor id and device id of the GPU associated with the monitor.
///
/// @param [in] monitor_handle The monitor whose device is needed.
/// @param [out] vendor_id The vendor id of the device associated with monitor_handle.
/// @param [out] device_id The device id of the device associated with monitor_handle.
///
/// @return True if an AMD device is associated with the monitor_handle.
GPA_LIB_DECL bool DxGetAmdDeviceInfo(HMONITOR monitor_handle, int& vendor_id, int& device_id);

#endif  // GPU_PERF_API_COMMON_DX_GET_AMD_DEVICE_INFO_H_
