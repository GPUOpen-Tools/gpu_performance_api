//==============================================================================
// Copyright (c) 2014-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DXX Utility functions
//==============================================================================


#ifndef _GPUPERFAPI_DXXEXTUTILS_H_
#define _GPUPERFAPI_DXXEXTUTILS_H_

#include <Windows.h>
#include <d3d11.h>

#include "AmdDxExtApi.h"

/// Test if MGPU performance extension is supported
/// \param[in] pDxxExt DXX extension
/// \return True if MGPU performance extension is supported, false if not
bool IsMgpuPerfExtSupported(IAmdDxExt* pDxxExt);

#endif // _GPUPERFAPI_DXXEXTUTILS_H_
