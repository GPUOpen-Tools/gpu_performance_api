//==============================================================================
// Copyright (c) 2011-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX11 version of GPUPerfAPI
//==============================================================================


#ifndef _GPUPERFAPI_DX11_H_
#define _GPUPERFAPI_DX11_H_

#include "..\GPUPerfAPI-Common\GPUPerfAPI.h"

#include <d3d11.h>
#include "GPAContextStateDX11.h"

/// Gets the current DX11 ContextState
/// \return the DX11-specific context state
GPA_ContextStateDX11* getCurrentContext();

#endif // _GPUPERFAPI_DX11_H_
