//==============================================================================
// Copyright (c) 2018-2020 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief CL GPA Session Implementation
//==============================================================================

#include "cl_gpa_session.h"
#include "cl_gpa_pass.h"

ClGpaSession::ClGpaSession(IGpaContext* parent_context, GpaSessionSampleType sample_type)
    : GpaSession(parent_context, sample_type)
{
}

GpaApiType ClGpaSession::GetApiType() const
{
    return kGpaApiOpencl;
}

GpaPass* ClGpaSession::CreateApiPass(PassIndex pass_index)
{
    GpaPass* ret_pass = nullptr;

    CounterList*     pass_counters  = GetCountersForPass(pass_index);
    GpaCounterSource counter_source = GetParentContext()->GetCounterSource((*pass_counters)[0]);

    ClGpaPass* cl_pass = new (std::nothrow) ClGpaPass(this, pass_index, counter_source, pass_counters);

    if (nullptr == cl_pass)
    {
        GPA_LOG_ERROR("Unable to allocate memory for the pass.");
    }
    else
    {
        ret_pass = cl_pass;
    }

    return ret_pass;
}
