//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A manager for DX11 Software Counter Data Requests
//==============================================================================

#include "DX11SoftwareCounterDataRequestManager.h"
#include "DX11CounterDataRequest.h"

DX11SoftwareCounterDataRequestManager::DX11SoftwareCounterDataRequestManager()
{
}

ICounterDataRequest* DX11SoftwareCounterDataRequestManager::GetDefaultDataRequest()
{
    return nullptr;
}
