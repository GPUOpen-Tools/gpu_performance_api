//==============================================================================
// Copyright (c) 2015-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX12 utility functions declaration
//==============================================================================

#ifndef GPU_PERF_API_DX12_DX12_UTILS_H_
#define GPU_PERF_API_DX12_DX12_UTILS_H_

#include <dxgi.h>
#include <D3D12.h>

#include "gpu_performance_api/gpu_perf_api_types.h"

namespace dx12_utils
{
    /// @brief Gets the adapter description for the specified device
    ///
    /// @param device The input device
    /// @param [out] adapter_desc The adapter description
    ///
    /// @return GpaStatus type indicating success.
    /// @retval kGpaStatusOk on success.
    /// @retval kGpaStatusErrorFailed on failure.
    GpaStatus Dx12GetAdapterDesc(IUnknown* device, DXGI_ADAPTER_DESC& adapter_desc);

    /// @brief Checks if the interface pointer is a graphics command list or not.
    ///
    /// @param [in] cmd Interface pointer.
    /// @param [out] cmd_type Type of the command list if interface pointer is DX12 command list.
    ///
    /// @return true if interface pointer is D3D12 graphics command list.
    bool IsD3D12CommandList(void* cmd, D3D12_COMMAND_LIST_TYPE* cmd_type = nullptr);

    /// @brief Check whether the DX12 command list and GPA command list are of same type or not.
    ///
    /// @param [in] dx12_cmd_type the DX12 command list type to compare.
    /// @param [in] gpa_cmd_type the GPA command list type to compare.
    ///
    /// @return The success status.
    /// @retval True if DX12 cmd is bundle and GPA cmd is secondary OR if DX12 cmd type is not bundle AND GPA cmd type is primary.
    /// @retval False otherwise.
    bool IsSameCmdType(const D3D12_COMMAND_LIST_TYPE* dx12_cmd_type, const GpaCommandListType* gpa_cmd_type);

    /// @brief Checks whether the interface pointer is DirectX 12 device or not. If it is, it returns the ID3D12Device device pointer.
    /// Function increments the reference of the ID3D12Device pointer.
    ///
    /// @param [in] interface_pointer DirectX 12 interface pointer.
    /// @param [out] d3d12_device DirectX 12 device pointer.
    ///
    /// @return True if interface pointer is device otherwise false.
    bool GetD3D12Device(IUnknown* interface_pointer, ID3D12Device** d3d12_device);

    /// @brief Checks whether or not the device supports the minimum DirectX 12 feature level
    ///
    /// @param [in] d3d12_device device pointer.
    ///
    /// @return The success status.
    /// @retval True if device is supports minimal level of DirectX 12,
    /// @retval False otherwise.
    bool IsFeatureLevelSupported(ID3D12Device* d3d12_device);

    /// @brief Get the time stamp frequency of DirectX 12 device.
    ///
    /// @param [in] d3d12_device Device pointer.
    /// @param [out] timestamp_frequency The timestamp frequency.
    ///
    /// @return True if timestamp frequency access succeeded, otherwise false.
    bool GetTimestampFrequency(ID3D12Device* d3d12_device, UINT64& timestamp_frequency);
}  // namespace dx12_utils

#endif  // GPU_PERF_API_DX12_DX12_UTILS_H_
