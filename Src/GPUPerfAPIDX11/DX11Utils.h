//==============================================================================
// Copyright (c) 2015-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX11 utility function declaration
//==============================================================================

#ifndef _DX11_UTILS_H_
#define _DX11_UTILS_H_

#include "DX11Include.h"

namespace DX11Utils
{
/// Checks whether the interface pointer is DirectX 11 device or not. If it is, it returns the ID3D11Device device pointer.
/// Function increments the reference of the ID3D11Device pointer
/// \param[in] pInterfacePointer DirectX 11 interface pointer
/// \param[out] ppD3D11Device DirectX 11 device pointer
/// \return true if interface pointer is device otherwise false
bool GetD3D11Device(IUnknown* pInterfacePointer, ID3D11Device** ppD3D11Device);

/// Checks whether or not the device supports the minimum DirectX 11 feature level
/// \param[in] pD3D11Device device pointer
/// \return true if device is supports minimal level of DirectX 11 otherwise false
bool IsFeatureLevelSupported(ID3D11Device* pD3D11Device);

/// Get the time stamp frequencey of DirectX 11 device
/// \param[in] pD3D11Device device pointer
/// \param[out] timestampFrequency The timestamp frequencey
/// \return true if timestamp frequencey access succeeded, otherwise false
bool GetTimestampFrequency(ID3D11Device* pD3D11Device, UINT64& timestampFrequency);
}

#endif // _DX11_UTILS_H_

