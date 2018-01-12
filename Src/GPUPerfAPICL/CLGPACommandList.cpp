//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief CL GPA Command List Implementation
//==============================================================================

#include "CLGPACommandList.h"

CLGPACommandList::CLGPACommandList(IGPASession* pGpaSession, GPAPass* pGpaPass):
    GPACommandList(pGpaSession, pGpaPass)
{
}

GPA_API_Type CLGPACommandList::GetAPIType() const
{
    return GPA_API_OPENCL;
}

