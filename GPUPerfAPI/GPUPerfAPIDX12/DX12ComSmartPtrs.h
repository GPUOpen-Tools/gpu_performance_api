//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12 Com smart pointers declarations
//==============================================================================

#ifndef _DX12_COM_SMART_PTRS_H_
#define _DX12_COM_SMART_PTRS_H_

#include <Windows.h>
#include <D3D12.h>
#include <comdef.h>

_COM_SMARTPTR_TYPEDEF(ID3D12Device, __uuidof(ID3D12Device));                           ///< typedef for a COM smart pointer wrapper for ID3D12Device
_COM_SMARTPTR_TYPEDEF(ID3D12GraphicsCommandList, __uuidof(ID3D12GraphicsCommandList)); ///< typedef for a COM smart pointer wrapper for ID3D12GraphicsCommandList
_COM_SMARTPTR_TYPEDEF(ID3D12QueryHeap, __uuidof(ID3D12QueryHeap));                     ///< typedef for a COM smart pointer wrapper for ID3D12QueryHeap
_COM_SMARTPTR_TYPEDEF(ID3D12Heap, __uuidof(ID3D12Heap));                               ///< typedef for a COM smart pointer wrapper for ID3D12Heap
_COM_SMARTPTR_TYPEDEF(ID3D12Resource, __uuidof(ID3D12Resource));                       ///< typedef for a COM smart pointer wrapper for ID3D12Resource

#endif // _DX12_COM_SMART_PTRS_H_

