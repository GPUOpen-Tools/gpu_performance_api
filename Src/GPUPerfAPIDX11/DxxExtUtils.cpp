//==============================================================================
// Copyright (c) 2014-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DXX Utility functions
//==============================================================================

#include "GPACommonDefs.h"
#include "DxxExtUtils.h"

/// Generate a single int from a DX extension version struct
#define GENERATE_DXX_EXT_VERSION(major, minor) ((major << 16) + minor)

bool DxxExtUtils::IsMgpuPerfExtSupported(IAmdDxExt* pDxxExt)
{
    static const unsigned int dxExtVersion8p1 = GENERATE_DXX_EXT_VERSION(8, 1);
    AmdDxExtVersion extVersion;
    HRESULT hr = pDxxExt->GetVersion(&extVersion);
    unsigned int dxExtVersion = GENERATE_DXX_EXT_VERSION(extVersion.majorVersion, extVersion.minorVersion);
    return (SUCCEEDED(hr) && (dxExtVersion8p1 < dxExtVersion));
}
