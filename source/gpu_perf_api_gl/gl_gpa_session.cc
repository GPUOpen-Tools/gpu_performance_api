//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GL GPA Session Implementation
//==============================================================================

#include "gpu_perf_api_gl/gl_gpa_session.h"

#include "gpu_perf_api_common/gpa_context_counter_mediator.h"

#include "gpu_perf_api_gl/gl_gpa_pass.h"

GlGpaSession::GlGpaSession(IGpaContext* parent_context, GpaSessionSampleType sample_type)
    : GpaSession(parent_context, sample_type)
{
}

GpaApiType GlGpaSession::GetApiType() const
{
    return kGpaApiOpengl;
}

GpaPass* GlGpaSession::CreateApiPass(PassIndex pass_index)
{
    GpaPass* ret_pass = nullptr;

    CounterList*     pass_counters  = GetCountersForPass(pass_index);
    GpaCounterSource counter_source = GetParentContext()->GetCounterSource((*pass_counters)[0]);

    GlGpaPass* gl_pass = new (std::nothrow) GlGpaPass(this, pass_index, counter_source, pass_counters);

    if (nullptr == gl_pass)
    {
        GPA_LOG_ERROR("Unable to allocate memory for the pass.");
    }
    else
    {
        ret_pass = gl_pass;
    }

    return ret_pass;
}
