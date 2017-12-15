//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief DX11 GPA Session Implementation
//==============================================================================

#include "DX11GPASession.h"

DX11GPASession::~DX11GPASession()
{
    GPA_FUNCTION_NOT_IMPLEMENTED;
}

bool DX11GPASession::Begin()
{
    GPA_FUNCTION_NOT_IMPLEMENTED;
    return true;
}

bool DX11GPASession::End()
{
    GPA_FUNCTION_NOT_IMPLEMENTED;
    return true;
}

GPA_CommandListId DX11GPASession::CreateCommandList(gpa_uint32 passIndex,
    void* pCmd,
    GPA_Command_List_Type cmdType)
{
    GPA_FUNCTION_NOT_IMPLEMENTED;
    UNREFERENCED_PARAMETER(passIndex);
    UNREFERENCED_PARAMETER(pCmd);
    UNREFERENCED_PARAMETER(cmdType);
    return nullptr;
}

bool DX11GPASession::BeginSample(ClientSampleId sampleId,
    GPA_CommandListId commandListId)
{
    GPA_FUNCTION_NOT_IMPLEMENTED;
    UNREFERENCED_PARAMETER(sampleId);
    UNREFERENCED_PARAMETER(commandListId);
    return true;
}

bool DX11GPASession::EndSample(GPA_CommandListId commandListId)
{
    GPA_FUNCTION_NOT_IMPLEMENTED;
    UNREFERENCED_PARAMETER(commandListId);
    return true;
}

gpa_uint32 DX11GPASession::GetSampleCount() const
{
    GPA_FUNCTION_NOT_IMPLEMENTED;
    return 0u;
}

GPA_API_Type DX11GPASession::GetAPIType() const
{
    return GPA_API_DIRECTX_11;
}
