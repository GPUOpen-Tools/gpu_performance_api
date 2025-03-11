//==============================================================================
// Copyright (c) 2017-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief DX11 GPA Session Implementation
//==============================================================================

#include "gpu_perf_api_dx11/dx11_gpa_session.h"
#include "gpu_perf_api_dx11/dx11_gpa_pass.h"

Dx11GpaSession::Dx11GpaSession(IGpaContext* parent_context, GpaSessionSampleType sample_type)
    : GpaSession(parent_context, sample_type)
{
}

GpaApiType Dx11GpaSession::GetApiType() const
{
    return kGpaApiDirectx11;
}

GpaPass* Dx11GpaSession::CreateApiPass(PassIndex pass_index)
{
    GpaPass* ret_pass = nullptr;

    CounterList* pass_counters = GetCountersForPass(pass_index);
    assert(pass_counters != nullptr);
    if (pass_counters != nullptr && pass_counters->size() > 0)
    {
        GpaCounterSource counter_source = GetCounterSource((*pass_counters)[0]);

        Dx11GpaPass* dx11_pass = new (std::nothrow) Dx11GpaPass(this, pass_index, counter_source, pass_counters);

        if (nullptr == dx11_pass)
        {
            GPA_LOG_ERROR("Unable to allocate memory for the pass.");
        }
        else
        {
            ret_pass = dx11_pass;
        }
    }

    return ret_pass;
}
