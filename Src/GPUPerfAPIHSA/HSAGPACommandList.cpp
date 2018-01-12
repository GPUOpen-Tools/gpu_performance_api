//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief HSA GPA Command List Implementation
//==============================================================================

#include "HSAGPACommandList.h"

HSAGPACommandList::HSAGPACommandList(IGPASession* pGpaSession, GPAPass* pGpaPass):
    GPACommandList(pGpaSession, pGpaPass)
{
}

GPA_API_Type HSAGPACommandList::GetAPIType() const
{
    return GPA_API_HSA;
}
