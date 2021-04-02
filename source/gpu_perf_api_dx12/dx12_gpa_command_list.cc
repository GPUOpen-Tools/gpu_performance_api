//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief DX12 GPA Command List Implementation
//==============================================================================

#include "gpu_perf_api_dx12/dx12_gpa_command_list.h"

#include "ADLUtil.h"

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_common/logging.h"

#include "gpu_perf_api_dx12/dx12_gpa_context.h"
#include "gpu_perf_api_dx12/dx12_gpa_pass.h"
#include "gpu_perf_api_dx12/dx12_gpa_session.h"
#include "gpu_perf_api_dx12/dx12_utils.h"

static const UINT32 kSInvalidSampleIndex = static_cast<UINT32>(-1);  ///< Invalid sample index.

Dx12GpaCommandList::Dx12GpaCommandList(Dx12GpaSession*    dx12_gpa_session,
                                       GpaPass*           dx12_gpa_pass,
                                       void*              cmd,
                                       CommandListId      command_list_id,
                                       GpaCommandListType cmd_type)
    : GpaCommandList(dx12_gpa_session, dx12_gpa_pass, command_list_id, cmd_type)
    , use_pre1850_config_(false)
{
    cmd_list_             = reinterpret_cast<ID3D12GraphicsCommandList*>(cmd);
    unsigned int refCount = cmd_list_->AddRef();
    UNREFERENCED_PARAMETER(refCount);
    amd_ext_session_                = nullptr;
    is_command_list_open_in_driver_ = false;
    is_non_gpa_resource_released_   = false;

    // Hardware counters are requested from the client even though it is not available in the driver.
    has_any_hardware_counters_ = dx12_gpa_pass->GetEnabledCounterCount() > 0;

    // BeginSample configuration struct can change based on driver versions.
    uint32_t major_ver     = 0;
    uint32_t minor_ver     = 0;
    uint32_t sub_minor_ver = 0;
    AMDTADLUtils::Instance()->GetDriverVersion(major_ver, minor_ver, sub_minor_ver);

    // If the driver is unsigned, or the version is >= 18.50 use the default configuration.
    if (!(major_ver || minor_ver || sub_minor_ver) || (major_ver > 18) || (major_ver == 18 && minor_ver >= 50))
    {
        use_pre1850_config_ = false;
    }
    else
    {
        use_pre1850_config_ = true;
    }
}

Dx12GpaCommandList::~Dx12GpaCommandList()
{
    ReleaseNonGPAResources();
}

bool Dx12GpaCommandList::BeginCommandListRequest()
{
    std::lock_guard<std::mutex> lock(dx12_cmd_list_mutex_);
    bool                        success = false;

    if (!is_command_list_open_in_driver_)
    {
        if (nullptr == amd_ext_session_)
        {
            Dx12GpaSession* dx12_gpa_session = reinterpret_cast<Dx12GpaSession*>(GetParentSession());
            amd_ext_session_                 = dx12_gpa_session->GetAmdExtInterface()->CreateGpaSession();
            amd_ext_session_->AddRef();  // Holding a reference is not required here, but we are doing so in order to work around an issue in older drivers.
        }

        HRESULT extension_op_result = amd_ext_session_->Begin(cmd_list_);
        success                     = S_OK == extension_op_result;

        if (!success)
        {
            GPA_LOG_ERROR("The driver extension is unable to begin the command list.");
        }
        else
        {
            is_command_list_open_in_driver_ = true;
        }
    }
    else
    {
        GPA_LOG_ERROR("The command list has already been started.");
    }

    return success;
}

bool Dx12GpaCommandList::EndCommandListRequest()
{
    std::lock_guard<std::mutex> lock(dx12_cmd_list_mutex_);
    bool                        success = false;

    if (is_command_list_open_in_driver_)
    {
        HRESULT status = amd_ext_session_->End(cmd_list_);

        if (S_OK == status)
        {
            success                         = true;
            is_command_list_open_in_driver_ = false;
        }
        else
        {
            GPA_LOG_ERROR(
                "The driver extension is unable to end the command list. This can occur if GPA_EndCommandList is called after the command list has been "
                "closed.");
        }
    }
    else
    {
        GPA_LOG_ERROR("The command list has not been started.");
    }

    return success;
}

bool Dx12GpaCommandList::BeginSampleRequest(ClientSampleId client_sample_id, GpaSample* gpa_sample)
{
    bool success = false;

    DriverSampleId   driver_sample_id = 0;
    GpaCounterSource counter_source   = GetPass()->GetCounterSource();

    if (GpaCounterSource::kHardware == counter_source)
    {
        if (OpenHwSample(client_sample_id, &driver_sample_id))
        {
            success = true;
        }
    }
    else if (GpaCounterSource::kSoftware == counter_source)
    {
        if (OpenSwSample(client_sample_id, &driver_sample_id))
        {
            success = true;
        }
    }

    if (success)
    {
        gpa_sample->SetDriverSampleId(driver_sample_id);
    }
    else
    {
        GPA_LOG_ERROR("Unable to begin sample in command list.");
    }

    return success;
}

bool Dx12GpaCommandList::CloseLastSampleRequest()
{
    GpaCounterSource counter_source = GetPass()->GetCounterSource();

    if (GpaCounterSource::kHardware == counter_source)
    {
        CloseHwSample();
    }
    else if (GpaCounterSource::kSoftware == counter_source)
    {
        CloseSwSample();
    }

    return true;
}

bool Dx12GpaCommandList::IsResultReady() const
{
    bool is_result_ready = true;

    is_result_ready = amd_ext_session_->IsReady();

    for (auto bundleIter = secondary_sample_amd_ext_session_map_.cbegin(); bundleIter != secondary_sample_amd_ext_session_map_.cend(); ++bundleIter)
    {
        is_result_ready &= bundleIter->first->IsReady();
    }

    return is_result_ready;
}

GpaApiType Dx12GpaCommandList::GetApiType() const
{
    return kGpaApiDirectx12;
}

ID3D12GraphicsCommandList* Dx12GpaCommandList::GetCmdList() const
{
    return cmd_list_;
}

bool Dx12GpaCommandList::CopyBundleSamples(std::vector<ClientSampleId>  client_sample_ids,
                                           SecondaryDx12Cmd*            dx12_secondary_cmd,
                                           std::vector<ClientSampleId>& original_client_sample_ids)
{
    bool success = false;

    if (kGpaCommandListPrimary == GetCmdType() && nullptr == GetBundleResultAmdExtSession(client_sample_ids.at(0)))
    {
        Dx12GpaSession*    dx12_gpa_session         = reinterpret_cast<Dx12GpaSession*>(GetParentSession());
        IAmdExtGpaSession* copy_amd_ext_gpa_session = dx12_gpa_session->GetAmdExtInterface()->CopyGpaSession(dx12_secondary_cmd->GetAmdExtSession());

        copy_amd_ext_gpa_session->CopyResults(cmd_list_);
        BundleSamplesOnPrimaryCmd bundle_samples_on_primary_cmd(client_sample_ids.begin(), client_sample_ids.end());

        // Holding a reference is not required here, but we are doing so in order to work around an issue in older drivers.
        secondary_sample_amd_ext_session_map_.insert(
            BundleResultAmdExtSessionBundleSamplesOnPrimaryCmdPair(copy_amd_ext_gpa_session, bundle_samples_on_primary_cmd));
        copy_amd_ext_gpa_session->AddRef();

        auto insert_original_client_sample_id = [&](ClientSampleIdGpaSamplePair client_sample_id_gpa_sample_pair) -> bool {
            original_client_sample_ids.push_back(client_sample_id_gpa_sample_pair.first);
            return true;
        };

        dx12_secondary_cmd->IterateSampleUnorderedMap(insert_original_client_sample_id);

        success = true;
    }
    else
    {
        GPA_LOG_ERROR("Unable to copy bundle samples. Copying is only supported on primary command lists for samples that do not already exist.");
    }

    return success;
}

IAmdExtGpaSession* Dx12GpaCommandList::GetAmdExtSession() const
{
    return amd_ext_session_;
}

IAmdExtGpaSession* Dx12GpaCommandList::GetBundleResultAmdExtSession(ClientSampleId client_sample_id) const
{
    bool               sample_found              = false;
    IAmdExtGpaSession* bundle_result_ext_session = nullptr;

    for (auto iter = secondary_sample_amd_ext_session_map_.cbegin(); iter != secondary_sample_amd_ext_session_map_.cend() && !sample_found; ++iter)
    {
        if (iter->second.find(client_sample_id) != iter->second.end())
        {
            // Search the client sample id in each set.
            bundle_result_ext_session = iter->first;
            sample_found              = true;
        }
    }

    return bundle_result_ext_session;
}

bool Dx12GpaCommandList::OpenHwSample(ClientSampleId client_sample_id, DriverSampleId* driver_sample_id) const
{
    UNREFERENCED_PARAMETER(client_sample_id);
    bool success = false;

    if (nullptr != driver_sample_id)
    {
        if (is_command_list_open_in_driver_)
        {
            success = true;

            if (has_any_hardware_counters_)
            {
                // If the driver is unsigned, or the version is >= 18.50 use the default configuration.
                if (use_pre1850_config_)
                {
                    auto older_config = reinterpret_cast<Dx12GpaPass*>(GetPass())->GetPre1850DriverExtSampleConfig();

                    *driver_sample_id = amd_ext_session_->BeginSample(cmd_list_, *(AmdExtGpaSampleConfig*)(&older_config));
                }
                else
                {
                    *driver_sample_id = amd_ext_session_->BeginSample(cmd_list_, reinterpret_cast<Dx12GpaPass*>(GetPass())->GetDriverExtSampleConfig());
                }

                if (*driver_sample_id == kSInvalidSampleIndex)
                {
                    success = false;
                    GPA_LOG_ERROR("Unable to begin request due to invalid sample index.");
                }
                else
                {
                    success = true;
                }
            }
        }
    }

    return success;
}

bool Dx12GpaCommandList::CloseHwSample() const
{
    bool success = false;

    if (is_command_list_open_in_driver_ && nullptr != GetLastSample())
    {
        if (has_any_hardware_counters_)
        {
            amd_ext_session_->EndSample(cmd_list_, GetLastSample()->GetDriverSampleId());
        }

        success = true;
    }

    return success;
}

bool Dx12GpaCommandList::OpenSwSample(ClientSampleId client_sample_id, DriverSampleId* driver_sample_id) const
{
    GPA_STUB_FUNCTION;
    UNREFERENCED_PARAMETER(client_sample_id);
    UNREFERENCED_PARAMETER(driver_sample_id);
    return true;
}

bool Dx12GpaCommandList::CloseSwSample()
{
    GPA_STUB_FUNCTION;
    return true;
}

void Dx12GpaCommandList::ReleaseNonGPAResources()
{
    if (!is_non_gpa_resource_released_)
    {
        unsigned int ref_count = cmd_list_->Release();
        UNREFERENCED_PARAMETER(ref_count);
        cmd_list_                     = nullptr;
        is_non_gpa_resource_released_ = true;

        // We won't rely on Release() to delete extension session objects because of an issue in older drivers,
        // rather we will use DestroyGpaSession to delete the session object.
        Dx12GpaSession* dx12_gpa_session = reinterpret_cast<Dx12GpaSession*>(GetParentSession());
        dx12_gpa_session->GetAmdExtInterface()->DestroyGpaSession(amd_ext_session_);
        amd_ext_session_ = nullptr;

        for (auto iter = secondary_sample_amd_ext_session_map_.begin(); iter != secondary_sample_amd_ext_session_map_.end(); ++iter)
        {
            dx12_gpa_session->GetAmdExtInterface()->DestroyGpaSession(iter->first);
        }

        secondary_sample_amd_ext_session_map_.clear();
    }
}
