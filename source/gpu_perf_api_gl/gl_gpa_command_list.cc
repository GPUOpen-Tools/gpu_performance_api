//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GL GPA Command List Implementation
//==============================================================================

#include "gpu_perf_api_gl/gl_gpa_command_list.h"

GlGpaCommandList::GlGpaCommandList(IGpaSession* gpa_session, GpaPass* gpa_pass, CommandListId command_list_id)
    : GpaCommandList(gpa_session, gpa_pass, command_list_id)
    , previous_sample_(nullptr)
{
}

GpaApiType GlGpaCommandList::GetApiType() const
{
    return kGpaApiOpengl;
}

bool GlGpaCommandList::BeginCommandListRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

bool GlGpaCommandList::EndCommandListRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}

bool GlGpaCommandList::BeginSampleRequest(ClientSampleId client_sample_id, GpaSample* gpa_sample)
{
    UNREFERENCED_PARAMETER(client_sample_id);

    bool success = true;

    if (!GetPass()->IsTimingPass() && nullptr != previous_sample_)
    {
        // Last sample already exist - collect its data first before proceeding.
        success &= previous_sample_->UpdateResults();
    }

    if (!GetPass()->IsTimingPass())
    {
        previous_sample_ = reinterpret_cast<GlGpaSample*>(gpa_sample);
    }

    return success;
}

bool GlGpaCommandList::CloseLastSampleRequest()
{
    GPA_STUB_FUNCTION;
    return true;
}