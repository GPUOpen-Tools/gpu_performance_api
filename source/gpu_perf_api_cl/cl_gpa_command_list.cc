//==============================================================================
// Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief CL GPA Command List Implementation
//==============================================================================

#include "cl_gpa_command_list.h"

ClGpaCommandList::ClGpaCommandList(IGpaSession* gpa_session, GpaPass* gpa_pass, CommandListId command_list_id)
    : GpaCommandList(gpa_session, gpa_pass, command_list_id)
{
}

GpaApiType ClGpaCommandList::GetApiType() const
{
    return kGpaApiOpencl;
}

bool ClGpaCommandList::BeginCommandListRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

bool ClGpaCommandList::EndCommandListRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

bool ClGpaCommandList::BeginSampleRequest(ClientSampleId client_sample_id, GpaSample* gpa_sample)
{
    GPA_STUB_FUNCTION;
    UNREFERENCED_PARAMETER(client_sample_id);
    UNREFERENCED_PARAMETER(gpa_sample);
    return true;
}

bool ClGpaCommandList::CloseLastSampleRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}
