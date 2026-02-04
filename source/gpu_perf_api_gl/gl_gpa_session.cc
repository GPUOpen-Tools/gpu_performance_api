//==============================================================================
// Copyright (c) 2018-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GL GPA Session Implementation
//==============================================================================

#include "gpu_perf_api_gl/gl_gpa_session.h"

#include "gpu_perf_api_common/gpa_context_counter_mediator.h"

#include "gpu_perf_api_gl/gl_gpa_context.h"
#include "gpu_perf_api_gl/gl_gpa_pass.h"

GlGpaSession::GlGpaSession(IGpaContext* parent_context, GpaSessionSampleType sample_type)
    : GpaSession(parent_context, sample_type)
{
    GlGpaContext* gl_gpa_context = reinterpret_cast<GlGpaContext*>(parent_context);
    assert(gl_gpa_context != nullptr);

    if (gl_gpa_context != nullptr)
    {
        if (!gl_gpa_context->ValidateAndUpdateGlCounters(this))
        {
            GPA_LOG_ERROR("Failed to validate the available counters.");
            assert(!"Failed to validate the available counters.");
        }
    }
}

GpaApiType GlGpaSession::GetApiType() const
{
    return kGpaApiOpengl;
}

std::unique_ptr<GpaPass> GlGpaSession::CreateApiPass(PassIndex pass_index)
{
    CounterList* pass_counters = GetCountersForPass(pass_index);
    assert(pass_counters != nullptr);
    if (pass_counters != nullptr && pass_counters->size() > 0)
    {
        GpaCounterSource counter_source = GetCounterSource((*pass_counters)[0]);
        return std::make_unique<GlGpaPass>(this, pass_index, counter_source, pass_counters);
    }
    return nullptr;
}
