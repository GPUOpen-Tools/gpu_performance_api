//==============================================================================
// Copyright (c) 2017-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief DX12 GPA Session implementation
//==============================================================================

#include "dx12_gpa_session.h"

#include <inttypes.h>

#include "gpu_perf_api_common/gpa_common_defs.h"

#include "gpu_perf_api_common/gpa_sample.h"
#include "gpu_perf_api_common/gpa_unique_object.h"

#include "gpu_perf_api_dx12/dx12_gpa_command_list.h"
#include "gpu_perf_api_dx12/dx12_gpa_context.h"
#include "gpu_perf_api_dx12/dx12_gpa_pass.h"
#include "gpu_perf_api_dx12/dx12_utils.h"

Dx12GpaSession::Dx12GpaSession(Dx12GpaContext* dx12_gpa_context, GpaSessionSampleType sample_type, IAmdExtGpaInterface* amd_ext_gpa_session)
    : GpaSession(dx12_gpa_context, sample_type)
{
    amd_ext_gpa_interface_ = amd_ext_gpa_session;
    amd_ext_gpa_interface_->AddRef();
}

Dx12GpaSession::~Dx12GpaSession()
{

    if (nullptr != amd_ext_gpa_interface_)
    {
        amd_ext_gpa_interface_->Release();
        amd_ext_gpa_interface_ = nullptr;
    }
}

void Dx12GpaSession::GetDriverVersion(uint32_t& major, uint32_t& minor, uint32_t& sub_minor)
{
    Dx12GpaContext* dx12_gpa_context = dynamic_cast<Dx12GpaContext*>(this->GetParentContext());
    if (dx12_gpa_context != nullptr)
    {
        dx12_gpa_context->GetDriverVersion(major, minor, sub_minor);
    }
}

GpaStatus Dx12GpaSession::ContinueSampleOnCommandList(GpaUInt32 src_sample_id, GpaCommandListId primary_command_list_id)
{
    bool succeed = false;

    if (primary_command_list_id->Object()->GetApiType() == kGpaApiDirectx12 &&
        primary_command_list_id->ObjectType() == GpaObjectType::kGpaObjectTypeCommandList)
    {
        Dx12GpaCommandList* dx12_cmd      = reinterpret_cast<Dx12GpaCommandList*>(primary_command_list_id->Object());
        Dx12GpaPass*        dx12_gpa_pass = reinterpret_cast<Dx12GpaPass*>(dx12_cmd->GetPass());

        if (nullptr != dx12_gpa_pass)
        {
            // Continue the sample.
            if (dx12_gpa_pass->ContinueSample(src_sample_id, dx12_cmd))
            {
                succeed = true;
            }
            else
            {
                GPA_LOG_ERROR("Unable to continue sample.");
            }
        }
        else
        {
            GPA_LOG_ERROR("Pass doesn't exist.");
        }
    }
    else
    {
        GPA_LOG_ERROR("Invalid Parameter.");
    }

    return succeed ? kGpaStatusOk : kGpaStatusErrorFailed;
}

GpaStatus Dx12GpaSession::CopySecondarySamples(GpaCommandListId secondary_cmd_list_id,
                                               GpaCommandListId primary_cmd_list_id,
                                               GpaUInt32        num_samples,
                                               GpaUInt32*       new_sample_ids)
{
    bool succeed = false;

    if (secondary_cmd_list_id->Object()->GetApiType() == kGpaApiDirectx12 && secondary_cmd_list_id->ObjectType() == GpaObjectType::kGpaObjectTypeCommandList &&
        primary_cmd_list_id->Object()->GetApiType() == kGpaApiDirectx12 && primary_cmd_list_id->ObjectType() == GpaObjectType::kGpaObjectTypeCommandList)
    {
        Dx12GpaCommandList* dx12_primary_cmd      = reinterpret_cast<Dx12GpaCommandList*>(primary_cmd_list_id->Object());
        Dx12GpaCommandList* dx12_secondary_cmd    = reinterpret_cast<Dx12GpaCommandList*>(secondary_cmd_list_id->Object());
        Dx12GpaPass*        dx12_primary_cmd_pass = reinterpret_cast<Dx12GpaPass*>(dx12_primary_cmd->GetPass());

        if (nullptr != dx12_primary_cmd_pass)
        {
            if (GpaCounterSource::kHardware == dx12_primary_cmd_pass->GetCounterSource())
            {
                std::vector<ClientSampleId> sample_indices;

                for (size_t sample_id_iter = 0; sample_id_iter < num_samples; sample_id_iter++)
                {
                    sample_indices.push_back(new_sample_ids[sample_id_iter]);
                }

                if (dx12_primary_cmd_pass->CopySecondarySamples(sample_indices, dx12_primary_cmd, dx12_secondary_cmd))
                {
                    succeed = true;
                }
            }
        }
    }
    else
    {
        GPA_LOG_ERROR("Invalid Parameter.");
    }

    return succeed ? kGpaStatusOk : kGpaStatusErrorFailed;
}

GpaApiType Dx12GpaSession::GetApiType() const
{
    return kGpaApiDirectx12;
}

IAmdExtGpaInterface* Dx12GpaSession::GetAmdExtInterface() const
{
    return amd_ext_gpa_interface_;
}

GpaPass* Dx12GpaSession::CreateApiPass(PassIndex pass_index)
{
    GpaPass* ret_pass = nullptr;

    CounterList*     pass_counters  = GetCountersForPass(pass_index);
    GpaCounterSource counter_source = GetParentContext()->GetCounterSource((*pass_counters)[0]);

    Dx12GpaPass* dx12_pass = new (std::nothrow) Dx12GpaPass(this, pass_index, counter_source, pass_counters);
    if (nullptr != dx12_pass)
    {
        ret_pass = dx12_pass;
    }

    return ret_pass;
}

