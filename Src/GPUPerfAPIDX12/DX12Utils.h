//==============================================================================
// Copyright (c) 2015-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12 utility functions declaration
//==============================================================================

#ifndef _DX12_UTILS_H_
#define _DX12_UTILS_H_

#include <dxgi.h>
#include <D3D12.h>

// GPA Common
#include "GPUPerfAPITypes.h"


namespace DX12Utils
{
/// Gets the adapter description for the specified device
/// \param pDevice the input device
/// \param[out] adapterDesc the adapter description
/// \return GPA_STATUS_OK on success
GPA_Status DX12GetAdapterDesc(IUnknown* pDevice, DXGI_ADAPTER_DESC& adapterDesc);

/// Checks if the interface pointer is a graphics command list or not
/// \param[in] pCmd interface pointer
/// \param[out] cmdType type of the command list if interface pointer is DX12 command list
/// \return true if interface pointer is D3D12 graphics command list
bool IsD3D12CommandList(void* pCmd, D3D12_COMMAND_LIST_TYPE* cmdType = nullptr);

/// Check whether the DX12 command list and GPA command list are of same type or not
/// \param[in] pDX12CmdType the DX12 command list type to compare
/// \param[in] pGpaCmdType the GPA command list type to compare
/// \return true if DX12 cmd is bundle and GPA cmd is secondary OR
/// if DX12 cmd type is not bundle and GPA cmd type is primary otherwise false
bool IsSameCmdType(const D3D12_COMMAND_LIST_TYPE* pDX12CmdType, const GPA_Command_List_Type* pGpaCmdType);

/// Checks whether the interface pointer is DirectX 12 device or not. If it is, it returns the ID3D12Device device pointer.
/// Function increments the reference of the ID3D12Device pointer
/// \param[in] pInterfacePointer DirectX 12 interface pointer
/// \param[out] ppD3D12Device DirectX 12 device pointer
/// \return true if interface pointer is device otherwise false
bool GetD3D12Device(IUnknown* pInterfacePointer, ID3D12Device** ppD3D12Device);

/// Checks whether or not the device supports the minimum DirectX 12 feature level
/// \param[in] pD3D12Device device pointer
/// \return true if device is supports minimal level of DirectX 12 otherwise false
bool IsFeatureLevelSupported(ID3D12Device* pD3D12Device);

/// Get the time stamp frequencey of DirectX 12 device
/// \param[in] pD3D12Device device pointer
/// \param[out] timestampFrequency The timestamp frequencey
/// \return true if timestamp frequencey access succeeded, otherwise false
bool GetTimestampFrequency(ID3D12Device* pD3D12Device, UINT64& timestampFrequency);
}

#endif // _DX12_UTILS_H
