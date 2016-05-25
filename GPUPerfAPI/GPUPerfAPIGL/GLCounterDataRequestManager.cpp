//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A manager for GL Data Requests
//==============================================================================

#include "GLCounterDataRequestManager.h"
#include "GLCounterDataRequest.h"

GLCounterDataRequestManager::GLCounterDataRequestManager()
{
}

GPA_DataRequest* GLCounterDataRequestManager::GetDefaultDataRequest()
{
    return new(std::nothrow) GLCounterDataRequest;
}
