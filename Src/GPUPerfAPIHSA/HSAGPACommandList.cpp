//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief HSA GPA Command List Implementation
//==============================================================================

#include "HSAGPACommandList.h"

HSAGPACommandList::HSAGPACommandList(IGPASession* pGpaSession,
                                     GPAPass* pGpaPass,
                                     CommandListId commandListId) :
    GPACommandList(pGpaSession, pGpaPass, commandListId)
{
}

GPA_API_Type HSAGPACommandList::GetAPIType() const
{
    return GPA_API_HSA;
}

bool HSAGPACommandList::BeginCommandListRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

bool HSAGPACommandList::EndCommandListRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

bool HSAGPACommandList::BeginSampleRequest(ClientSampleId clientSampleId,
                                           GPASample* pGpaSample)
{
    GPA_STUB_FUNCTION;
    UNREFERENCED_PARAMETER(clientSampleId);
    UNREFERENCED_PARAMETER(pGpaSample);
    return true;
}

bool HSAGPACommandList::CloseLastSampleRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}
