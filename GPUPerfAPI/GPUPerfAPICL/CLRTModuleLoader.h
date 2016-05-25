//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  This file provides access to the ocl runtime modules
//==============================================================================

#ifndef _OCL_RT_MODULE_LOADER_H_
#define _OCL_RT_MODULE_LOADER_H_


#include "APIRTModuleLoader.h"
#include "OpenCLModule.h"

typedef APIRTModuleLoader<OpenCLModule> OCLRTModuleLoader; ///< Typedef for the OpenCL RT Module Loader

#endif  //_OCL_RT_MODULE_LOADER_H_
