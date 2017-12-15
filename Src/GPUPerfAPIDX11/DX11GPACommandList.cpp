//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief DX11 GPA Command List Implementation
//==============================================================================

#include "DX11GPACommandList.h"

DX11GPACommandList::DX11GPACommandList(IGPASession* pGpaSession, GPAPass* pGpaPass):
    GPACommandList(pGpaSession, pGpaPass)
{
}

GPA_API_Type DX11GPACommandList::GetAPIType() const
{
    return GPA_API_DIRECTX_11;
}

