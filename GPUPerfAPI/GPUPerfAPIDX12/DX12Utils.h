//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12 utility functions declaration
//==============================================================================

#ifndef _GPA_DX12_DX_UTILS_H
#define _GPA_DX12_DX_UTILS_H

#include <dxgi.h>

#include "GPUPerfAPITypes.h"
#include "Logging.h"

/// Gets the adapter description for the specified device
/// \param pDevice the input device
/// \param[out] adapterDesc the adapter description
/// \return GPA_STATUS_OK on success
GPA_Status DX12GetAdapterDesc(IUnknown* pDevice, DXGI_ADAPTER_DESC& adapterDesc);

#endif // _GPA_DX12_DX_UTILS_H
