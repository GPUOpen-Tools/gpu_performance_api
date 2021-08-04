//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief DX11 GPA Command List Implementation
//==============================================================================

#include "gpu_perf_api_dx11/dx11_gpa_command_list.h"

Dx11GpaCommandList::Dx11GpaCommandList(IGpaSession* gpa_session, GpaPass* gpa_pass, CommandListId command_list_id)
    : GpaCommandList(gpa_session, gpa_pass, command_list_id)
{
}

GpaApiType Dx11GpaCommandList::GetApiType() const
{
    return kGpaApiDirectx11;
}

bool Dx11GpaCommandList::BeginCommandListRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

bool Dx11GpaCommandList::EndCommandListRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

bool Dx11GpaCommandList::BeginSampleRequest(ClientSampleId client_sample_id, GpaSample* gpa_sample)
{
    GPA_STUB_FUNCTION;
    UNREFERENCED_PARAMETER(client_sample_id);
    UNREFERENCED_PARAMETER(gpa_sample);
    return true;
}

bool Dx11GpaCommandList::CloseLastSampleRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}
