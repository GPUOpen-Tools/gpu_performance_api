//==============================================================================
// Copyright (c) 2015-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX11 utility function declaration
//==============================================================================

#ifndef GPU_PERF_API_DX11_DX11_UTILS_H_
#define GPU_PERF_API_DX11_DX11_UTILS_H_

#include "gpu_perf_api_dx11/dx11_include.h"

namespace dx11_utils
{
    /// @brief Checks whether the interface pointer is DirectX 11 device or not.
    //
    /// Function increments the reference of the ID3D11Device pointer
    ///
    /// @param [in] interface_pointer DirectX 11 interface pointer.
    /// @param [out] d3d11_device DirectX 11 device pointer.
    ///
    /// @return Boolean value indicating if the pointer is a DX11 device.
    /// @retval True if interface pointer is a DX11 device.
    /// @retval False otherwise.
    bool GetD3D11Device(IUnknown* interface_pointer, ID3D11Device** d3d11_device);

    /// @brief Checks whether or not the device supports the minimum DirectX 11 feature level.
    ///
    ///  @param [in] d3d11_device Device pointer.
    ///
    /// @return Boolean value indicating if the device supports DX11.
    /// @retval True if device is supports minimal level of DirectX 11.
    /// @retval False otherwise.
    bool IsFeatureLevelSupported(ID3D11Device* d3d11_device);

    /// @brief Get the time stamp frequency of DirectX 11 device.
    ///
    /// @param [in] d3d11_device device pointer
    /// @param [out] timestamp_frequency The time-stamp frequency
    ///
    /// @return Boolean value indicating the time-stamp frequency access success.
    /// @retval True if time-stamp frequency access succeeded.
    /// @retval False otherwise.
    bool GetTimestampFrequency(ID3D11Device* d3d11_device, UINT64& timestamp_frequency);
}  // namespace dx11_utils

#endif  // GPU_PERF_API_DX11_DX11_UTILS_H_
