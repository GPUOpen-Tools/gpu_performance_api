//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief ROCm GPA Command List Implementation
//==============================================================================

#include "ROCmGPACommandList.h"

ROCmGPACommandList::ROCmGPACommandList(IGPASession* pGpaSession, GPAPass* pGpaPass, CommandListId commandListId)
    : GPACommandList(pGpaSession, pGpaPass, commandListId)
{
}

GPA_API_Type ROCmGPACommandList::GetAPIType() const
{
    return GPA_API_ROCM;
}

bool ROCmGPACommandList::BeginCommandListRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

bool ROCmGPACommandList::EndCommandListRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

bool ROCmGPACommandList::BeginSampleRequest(ClientSampleId clientSampleId, GPASample* pGpaSample)
{
    GPA_STUB_FUNCTION;
    UNREFERENCED_PARAMETER(clientSampleId);
    UNREFERENCED_PARAMETER(pGpaSample);
    return true;
}

bool ROCmGPACommandList::CloseLastSampleRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}
