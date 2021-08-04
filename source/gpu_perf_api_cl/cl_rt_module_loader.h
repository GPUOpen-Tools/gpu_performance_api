//==============================================================================
// Copyright (c) 2015-2020 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  This file provides access to the ocl runtime modules
//==============================================================================

#ifndef _CL_RT_MODULE_LOADER_H_
#define _CL_RT_MODULE_LOADER_H_

#include "api_rt_module_loader.h"
#include "OpenCLModule.h"

typedef ApiRuntimeModuleLoader<OpenCLModule> ClRuntimeModuleLoader;  ///< Typedef for the OpenCL RT Module Loader

#endif  //_CL_RT_MODULE_LOADER_H_
