//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief CL GPA Command List Implementation
//==============================================================================

#include "CLGPACommandList.h"

CLGPACommandList::CLGPACommandList(IGPASession* pGpaSession,
                                   GPAPass* pGpaPass,
                                   CommandListId commandListId) :
    GPACommandList(pGpaSession, pGpaPass, commandListId)
{
}

GPA_API_Type CLGPACommandList::GetAPIType() const
{
    return GPA_API_OPENCL;
}

bool CLGPACommandList::BeginCommandListRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

bool CLGPACommandList::EndCommandListRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

bool CLGPACommandList::BeginSampleRequest(ClientSampleId clientSampleId,
                                          GPASample* pGpaSample)
{
    GPA_STUB_FUNCTION;
    UNREFERENCED_PARAMETER(clientSampleId);
    UNREFERENCED_PARAMETER(pGpaSample);
    return true;
}

bool CLGPACommandList::CloseLastSampleRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

