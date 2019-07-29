//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX11 Include file
//==============================================================================

#ifndef _DX11_INCLUDE_H_
#define _DX11_INCLUDE_H_

#include <d3d11.h>
#include <d3dcommon.h>
#include "GPACommonDefs.h"
#include "AmdDxExtASICInfo.h"
#include "AmdDxExtASICInfoApi.h"
#include "AmdDxExtPerfProfileApi.h"

#define PE_BLOCK_ID_MAX PE_BLOCK_MAX_GFX10  /// macro for count of DX11 block id, notably we need to update this with every next generation

#endif  // _DX11_INCLUDE_H_
