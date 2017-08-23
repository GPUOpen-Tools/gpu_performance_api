//==============================================================================
// Copyright (c) 2012-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  HSA version of GPUPerfAPI
//==============================================================================

// using double-underscore in header guards to avoid conflict with header guards in GPUPerfAPI-Common\GPUPerfAPI-HSA.h
#ifndef __GPUPERFAPI_HSA_H__
#define __GPUPERFAPI_HSA_H__

#include <hsa_ext_profiler.h>
#include <hsa_ext_amd.h>

#include "GPAContextStateHSA.h"
#include "GPUPerfAPI-HSA.h"

/// Gets the current HSA ContextState
/// \return the HSA-specific context state
GPA_ContextStateHSA* getCurrentContext();

#endif // __GPUPERFAPI_HSA_H__
