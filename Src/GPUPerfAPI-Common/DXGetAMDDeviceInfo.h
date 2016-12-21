//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Defines entry points in GPUPerfAPIDXGetAMDDeviceInfo dll
//==============================================================================

#ifndef _DX_GET_AMD_DEVICE_INFO_H_
#define _DX_GET_AMD_DEVICE_INFO_H_

#include <windows.h>
#include "GPUPerfAPI.h"

/// Get the vendor id and device id of the GPU associated with the monitor
/// \param[in] hMonitor the monitor whose device is needed
/// \param[out] vendorId the vendor id of the device associated with hMonitor
/// \param[out] deviceId the vendor id of the device associated with hMonitor
/// \return bool if an AMD device is associated with hMonitor
GPALIB_DECL bool DXGetAMDDeviceInfo(HMONITOR hMonitor, int& vendorId, int& deviceId);

#endif // _DX_GET_AMD_DEVICE_INFO_H_
