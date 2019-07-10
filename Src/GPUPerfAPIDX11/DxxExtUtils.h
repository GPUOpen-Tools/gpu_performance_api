//==============================================================================
// Copyright (c) 2014-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DXX Utility functions
//==============================================================================

#ifndef _GPUPERFAPI_DXXEXTUTILS_H_
#define _GPUPERFAPI_DXXEXTUTILS_H_

#include "DX11Include.h"

namespace DxxExtUtils
{
    /// Test if MGPU performance extension is supported
    /// \param[in] pDxxExt DXX extension
    /// \return True if MGPU performance extension is supported, false if not
    bool IsMgpuPerfExtSupported(IAmdDxExt* pDxxExt);
}  // namespace DxxExtUtils

#endif  // _GPUPERFAPI_DXXEXTUTILS_H_
