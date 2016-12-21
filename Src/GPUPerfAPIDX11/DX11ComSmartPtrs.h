//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX11 COM Smart pointers used by GPUPerfAPIDX11
//==============================================================================

#ifndef _DX11_COM_SMART_PTRS_H_
#define _DX11_COM_SMART_PTRS_H_

#include <Windows.h>
#include <d3d11.h>
#include <comdef.h>

_COM_SMARTPTR_TYPEDEF(ID3D11Device, __uuidof(ID3D11Device));               ///< COM Smart pointer to wrap ID3D11Device
_COM_SMARTPTR_TYPEDEF(ID3D11DeviceContext, __uuidof(ID3D11DeviceContext)); ///< COM Smart pointer to wrap ID3D11DeviceContext
_COM_SMARTPTR_TYPEDEF(ID3D11Query, __uuidof(ID3D11Query));                 ///< COM Smart pointer to wrap ID3D11Query
_COM_SMARTPTR_TYPEDEF(ID3D11Counter, __uuidof(ID3D11Counter));             ///< COM Smart pointer to wrap ID3D11Counter
_COM_SMARTPTR_TYPEDEF(IDXGIDevice1, __uuidof(IDXGIDevice1));               ///< COM Smart pointer to wrap IDXGIDevice1
_COM_SMARTPTR_TYPEDEF(IDXGIAdapter, __uuidof(IDXGIAdapter));               ///< COM Smart pointer to wrap IDXGIAdapter

#endif // _DX11_COM_SMART_PTRS_H_
