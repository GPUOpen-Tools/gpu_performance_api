//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  This file provides access to the hsa runtime modules
//==============================================================================

#ifndef _HSA_RT_MODULE_LOADER_H_
#define _HSA_RT_MODULE_LOADER_H_

#include "APIRTModuleLoader.h"
#include "HSAModule.h"
#include "HSAToolsRTModule.h"

typedef APIRTModuleLoader<HSAModule> HSARTModuleLoader;             ///< Typedef for the HSA RT Module Loader
typedef APIRTModuleLoader<HSAToolsRTModule> HSAToolsRTModuleLoader; ///< Typedef for the HSA RT Tools Module Loader

#endif  //_HSA_RT_MODULE_LOADER_H_
