//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief DX11 GPA Command List Implementation
//==============================================================================

#include "DX11GPACommandList.h"

DX11GPACommandList::DX11GPACommandList(IGPASession* pGpaSession, GPAPass* pGpaPass, CommandListId commandListId):
    GPACommandList(pGpaSession, pGpaPass, commandListId)
{
}

GPA_API_Type DX11GPACommandList::GetAPIType() const
{
    return GPA_API_DIRECTX_11;
}

bool DX11GPACommandList::BeginCommandListRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

bool DX11GPACommandList::EndCommandListRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

bool DX11GPACommandList::BeginSampleRequest(ClientSampleId clientSampleId,
                                            GPASample* pGpaSample)
{
    GPA_STUB_FUNCTION;
    UNREFERENCED_PARAMETER(clientSampleId);
    UNREFERENCED_PARAMETER(pGpaSample);
    return true;
}

bool DX11GPACommandList::CloseLastSampleRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}



