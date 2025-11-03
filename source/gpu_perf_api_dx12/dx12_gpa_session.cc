//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief DX12 GPA Session implementation
//==============================================================================

#include "dx12_gpa_session.h"

#include <inttypes.h>

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_common/gpa_context_counter_mediator.h"
#include "gpu_perf_api_counter_generator/gpa_counter_accessor_interface.h"

#include "gpu_perf_api_common/gpa_sample.h"
#include "gpu_perf_api_common/gpa_unique_object.h"

#include "gpu_perf_api_dx12/dx12_gpa_command_list.h"
#include "gpu_perf_api_dx12/dx12_gpa_context.h"
#include "gpu_perf_api_dx12/dx12_gpa_pass.h"
#include "gpu_perf_api_dx12/dx12_utils.h"

namespace
{
    constexpr UINT32 kInvalidSampleIndex        = UINT32_MAX;  ///< Invalid GPA session sample index.
    constexpr UINT32 kMinSpmTraceSampleInterval = 32;          ///< The hardware reg spec says: minimum of 32
    constexpr UINT32 kRgpSpmTraceSampleInterval = 4096;        ///< This default value works well for large game titles

    bool InvalidSpmConfig(AmdExtGpaSampleConfig const& cfg)
    {
        return (cfg.perfCounters.spmTraceSampleInterval < kMinSpmTraceSampleInterval);
    }

    bool InvalidSqttConfig(AmdExtGpaSampleConfig const& cfg)
    {
        return (cfg.sqtt.flags.enable == 0);
    }
}  // namespace

Dx12GpaSession::Dx12GpaSession(Dx12GpaContext* dx12_gpa_context, GpaSessionSampleType sample_type, IAmdExtGpaInterface* amd_ext_gpa_session)
    : GpaSession(dx12_gpa_context, sample_type)
    , sqtt_amd_ext_session_(nullptr)
    , sqtt_started_(false)
    , sqtt_driver_sample_id_(0)
    , spm_amd_ext_session_(nullptr)
    , spm_started_(false)
    , spm_driver_sample_id_(0)
    , spm_sampling_interval_(kRgpSpmTraceSampleInterval)
    , spm_duration_(0)
    , spm_data_(nullptr)
{
    amd_ext_gpa_interface_ = amd_ext_gpa_session;
    amd_ext_gpa_interface_->AddRef();
}

Dx12GpaSession::~Dx12GpaSession()
{
    if (nullptr != sqtt_amd_ext_session_)
    {
        ULONG session_ref_count = sqtt_amd_ext_session_->Release();
        if (session_ref_count != 0)
        {
            amd_ext_gpa_interface_->DestroyGpaSession(sqtt_amd_ext_session_);
        }
        sqtt_amd_ext_session_ = nullptr;
    }

    if (nullptr != spm_amd_ext_session_)
    {
        ULONG session_ref_count = spm_amd_ext_session_->Release();
        if (session_ref_count != 0)
        {
            amd_ext_gpa_interface_->DestroyGpaSession(spm_amd_ext_session_);
        }
        spm_amd_ext_session_ = nullptr;
    }

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

                sample_indices.reserve(num_samples);
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

    GpaSessionSampleType sample_type = GetSampleType();

    CounterList*     pass_counters  = nullptr;
    GpaCounterSource counter_source = GpaCounterSource::kUnknown;

    switch (sample_type)
    {
    case kGpaSessionSampleTypeDiscreteCounter:
        pass_counters = GetCountersForPass(pass_index);
        assert(pass_counters != nullptr);
        if (pass_counters != nullptr && pass_counters->size() > 0)
        {
            counter_source = GetCounterSource((*pass_counters)[0]);
        }
        break;
    case kGpaSessionSampleTypeStreamingCounter:
    case kGpaSessionSampleTypeStreamingCounterAndSqtt:
        pass_counters = GetCountersForPass(pass_index);
        assert(pass_counters != nullptr);
        if (pass_counters != nullptr && pass_counters->size() > 0)
        {
            counter_source = GetCounterSource((*pass_counters)[0]);
        }
        break;
    case kGpaSessionSampleTypeSqtt:
        break;
    default:
        GPA_LOG_ERROR("Invalid sample type.");
        return nullptr;
    }

    Dx12GpaPass* dx12_pass = new (std::nothrow) Dx12GpaPass(this, pass_index, counter_source, pass_counters);
    if (nullptr != dx12_pass)
    {
        ret_pass = dx12_pass;
    }

    return ret_pass;
}

GpaStatus Dx12GpaSession::SqttBegin(void* command_list)
{
    if (sqtt_started_)
    {
        GPA_LOG_ERROR("SQTT data collection already started.");
        return kGpaStatusErrorAlreadyEnabled;
    }

    if (nullptr == sqtt_amd_ext_session_)
    {
        sqtt_amd_ext_session_ = GetAmdExtInterface()->CreateGpaSession();
    }
    else
    {
        sqtt_amd_ext_session_->Reset();
    }

    HRESULT hr = sqtt_amd_ext_session_->Begin((ID3D12GraphicsCommandList*)command_list);
    if (FAILED(hr))
    {
        GPA_LOG_ERROR("The driver extension is unable to begin the command list.");
        return kGpaStatusErrorFailed;
    }

    session_sample_config_.Initialize(this, GpaCounterSource::kHardware, nullptr, nullptr, false);

    const AmdExtGpaSampleConfig& config = session_sample_config_.GetDriverExtSampleConfig();
    if (InvalidSqttConfig(config))
    {
        GPA_LOG_ERROR("Sqtt wasn't properly configured.");
        return kGpaStatusErrorFailed;
    }

    sqtt_driver_sample_id_ = sqtt_amd_ext_session_->BeginSample((ID3D12GraphicsCommandList*)command_list, config);
    if (kInvalidSampleIndex == sqtt_driver_sample_id_)
    {
        GPA_LOG_ERROR("The driver extension is unable to begin sample on the command list.");
        sqtt_amd_ext_session_->End((ID3D12GraphicsCommandList*)command_list);
        return kGpaStatusErrorFailed;
    }

    sqtt_started_ = true;

    return kGpaStatusOk;
}

GpaStatus Dx12GpaSession::SqttEnd(void* command_list)
{
    if (!sqtt_started_)
    {
        GPA_LOG_ERROR("SQTT data collection not started.");
        return kGpaStatusErrorNotEnabled;
    }

    sqtt_amd_ext_session_->EndSample((ID3D12GraphicsCommandList*)command_list, sqtt_driver_sample_id_);

    HRESULT hr = sqtt_amd_ext_session_->End((ID3D12GraphicsCommandList*)command_list);
    if (FAILED(hr))
    {
        GPA_LOG_ERROR("The driver extension is unable to end the command list.");
        return kGpaStatusErrorFailed;
    }

    return kGpaStatusOk;
}

bool Dx12GpaSession::FlushSession(IAmdExtGpaSession* pSession, uint32_t timeout)
{
    TRACE_PRIVATE_FUNCTION(GPASession::Flush);

    bool retVal = true;

    auto startTime = std::chrono::steady_clock::now();

    // block until the session is complete or the timeout (if any) is reached
    while (!pSession->IsReady())
    {
        if (timeout != kGpaTimeoutInfinite)
        {
            auto currentTime = std::chrono::steady_clock::now();
            auto duration    = currentTime - startTime;

            if (std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() > timeout)
            {
                GPA_LOG_ERROR("GPA session completion timeout occurred.");
                retVal = false;
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    return retVal;
}

GpaStatus Dx12GpaSession::SqttGetSampleResultSize(size_t* sample_result_size_in_bytes)
{
    assert(sample_result_size_in_bytes);

    if (!sqtt_started_)
    {
        GPA_LOG_ERROR("SQTT data collection not started.");
        return kGpaStatusErrorNotEnabled;
    }

    if (!FlushSession(sqtt_amd_ext_session_, flush_timeout_))
    {
        GPA_LOG_ERROR("Failed to retrieve sample data due to timeout.");
        return kGpaStatusErrorTimeout;
    }

    *sample_result_size_in_bytes = 0;

    HRESULT driverResult = sqtt_amd_ext_session_->GetResults(sqtt_driver_sample_id_, sample_result_size_in_bytes, nullptr);
    if (FAILED(driverResult))
    {
        GPA_LOG_ERROR("Failed to retrieve driver result size");
        return kGpaStatusErrorFailed;
    }

    return kGpaStatusOk;
}

GpaStatus Dx12GpaSession::SqttGetSampleResult(size_t sample_result_size_in_bytes, void* sqtt_results)
{
    assert(sample_result_size_in_bytes);
    assert(sqtt_results);

    if (!sqtt_started_)
    {
        GPA_LOG_ERROR("SQTT data collection not started.");
        return kGpaStatusErrorNotEnabled;
    }

    if (!FlushSession(sqtt_amd_ext_session_, flush_timeout_))
    {
        GPA_LOG_ERROR("Failed to retrieve sample data due to timeout.");
        return kGpaStatusErrorTimeout;
    }

    size_t expected_sample_result_size_in_bytes = 0;

    auto hr = sqtt_amd_ext_session_->GetResults(sqtt_driver_sample_id_, &expected_sample_result_size_in_bytes, nullptr);
    if (FAILED(hr))
    {
        GPA_LOG_ERROR("Failed to retrieve driver result size");
        return kGpaStatusErrorFailed;
    }

    if (expected_sample_result_size_in_bytes != sample_result_size_in_bytes)
    {
        GPA_LOG_ERROR("Invalid result size");
        return kGpaStatusErrorFailed;
    }

    hr = sqtt_amd_ext_session_->GetResults(sqtt_driver_sample_id_, &expected_sample_result_size_in_bytes, sqtt_results);
    if (FAILED(hr))
    {
        GPA_LOG_ERROR("Failed to retrieve driver result set");
        return kGpaStatusErrorFailed;
    }

    sqtt_started_ = false;

    return kGpaStatusOk;
}

GpaStatus Dx12GpaSession::SqttSpmBegin(void* command_list)
{
    if (sqtt_started_)
    {
        GPA_LOG_ERROR("SQTT + SPM data collection already started.");
        return kGpaStatusErrorAlreadyEnabled;
    }

    if (nullptr == sqtt_amd_ext_session_)
    {
        sqtt_amd_ext_session_ = GetAmdExtInterface()->CreateGpaSession();
    }
    else
    {
        sqtt_amd_ext_session_->Reset();
    }

    auto          dx12_list = reinterpret_cast<ID3D12GraphicsCommandList*>(command_list);
    const HRESULT hr        = sqtt_amd_ext_session_->Begin(dx12_list);
    if (FAILED(hr))
    {
        GPA_LOG_ERROR("The driver extension is unable to begin the command list.");
        return kGpaStatusErrorFailed;
    }

    auto current_pass = dynamic_cast<Dx12GpaPass*>(GetPasses()[0]);
    if (current_pass == nullptr)
    {
        GPA_LOG_ERROR("Unable to get current pass.");
        return kGpaStatusErrorFailed;
    }

    const AmdExtGpaSampleConfig& config = current_pass->GetAmdExtSampleConfig().GetDriverExtSampleConfig();
    if (InvalidSqttConfig(config))
    {
        GPA_LOG_ERROR("Sqtt wasn't properly configured.");
        return kGpaStatusErrorFailed;
    }
    if (InvalidSpmConfig(config))
    {
        GPA_LOG_ERROR("SPM wasn't properly configured.");
        return kGpaStatusErrorFailed;
    }
    sqtt_driver_sample_id_ = sqtt_amd_ext_session_->BeginSample(dx12_list, config);

    if (kInvalidSampleIndex == sqtt_driver_sample_id_)
    {
        GPA_LOG_ERROR("The driver extension is unable to begin sample on the command list.");
        sqtt_amd_ext_session_->End(dx12_list);
        return kGpaStatusErrorFailed;
    }

    // SPM will also use the same driver sample id
    spm_driver_sample_id_ = sqtt_driver_sample_id_;

    sqtt_started_ = true;
    spm_started_  = true;

    return kGpaStatusOk;
}

GpaStatus Dx12GpaSession::SqttSpmEnd(void* command_list)
{
    if (!sqtt_started_)
    {
        GPA_LOG_ERROR("SPM data collection not started.");
        return kGpaStatusErrorNotEnabled;
    }

    auto dx12_list = reinterpret_cast<ID3D12GraphicsCommandList*>(command_list);
    sqtt_amd_ext_session_->EndSample(dx12_list, sqtt_driver_sample_id_);

    const HRESULT hr = sqtt_amd_ext_session_->End(dx12_list);
    if (FAILED(hr))
    {
        GPA_LOG_ERROR("The driver extension is unable to end the command list.");
        return kGpaStatusErrorFailed;
    }

    // sqtt_started_ set to false after calling SqttGetSampleResult
    spm_started_ = false;

    return kGpaStatusOk;
}

GpaStatus Dx12GpaSession::SpmSetSampleInterval(GpaUInt32 interval)
{
    constexpr UINT32 kMaxSpmTraceSampleInterval = 65536 - kMinSpmTraceSampleInterval;
    static_assert(kMaxSpmTraceSampleInterval == 65504);
    if (interval < kMinSpmTraceSampleInterval || interval > kMaxSpmTraceSampleInterval)
    {
        GPA_LOG_ERROR("SPM sampling interval range: [32 - 65504].");
        return kGpaStatusErrorInvalidParameter;
    }

    spm_sampling_interval_ = interval;

    return kGpaStatusOk;
}

GpaStatus Dx12GpaSession::SpmSetDuration(GpaUInt32 ns_duration)
{
    spm_duration_ = ns_duration;

    return kGpaStatusOk;
}

GpaStatus Dx12GpaSession::SpmBegin(void* command_list)
{
    if (spm_started_)
    {
        GPA_LOG_ERROR("SPM data collection already started.");
        return kGpaStatusErrorAlreadyEnabled;
    }

    if (nullptr == spm_amd_ext_session_)
    {
        spm_amd_ext_session_ = GetAmdExtInterface()->CreateGpaSession();
    }
    else
    {
        spm_amd_ext_session_->Reset();
    }

    HRESULT hr = spm_amd_ext_session_->Begin((ID3D12GraphicsCommandList*)command_list);
    if (FAILED(hr))
    {
        GPA_LOG_ERROR("The driver extension is unable to begin the command list.");
        return kGpaStatusErrorFailed;
    }

    auto current_pass = dynamic_cast<Dx12GpaPass*>(GetPasses()[0]);
    if (current_pass == nullptr)
    {
        GPA_LOG_ERROR("Unable to get current pass.");
        return kGpaStatusErrorFailed;
    }

    const AmdExtGpaSampleConfig& config = current_pass->GetAmdExtSampleConfig().GetDriverExtSampleConfig();
    if (InvalidSpmConfig(config))
    {
        GPA_LOG_ERROR("SPM wasn't properly configured.");
        return kGpaStatusErrorFailed;
    }

    spm_driver_sample_id_ = spm_amd_ext_session_->BeginSample((ID3D12GraphicsCommandList*)command_list, config);

    if (kInvalidSampleIndex == spm_driver_sample_id_)
    {
        GPA_LOG_ERROR("The driver extension is unable to begin sample on the command list.");
        spm_amd_ext_session_->End((ID3D12GraphicsCommandList*)command_list);
        return kGpaStatusErrorFailed;
    }

    spm_started_ = true;

    return kGpaStatusOk;
}

GpaStatus Dx12GpaSession::SpmEnd(void* command_list)
{
    if (!spm_started_)
    {
        GPA_LOG_ERROR("SPM data collection not started.");
        return kGpaStatusErrorNotEnabled;
    }

    spm_amd_ext_session_->EndSample((ID3D12GraphicsCommandList*)command_list, spm_driver_sample_id_);

    HRESULT hr = spm_amd_ext_session_->End((ID3D12GraphicsCommandList*)command_list);
    if (FAILED(hr))
    {
        GPA_LOG_ERROR("The driver extension is unable to end the command list.");
        return kGpaStatusErrorFailed;
    }

    spm_started_ = false;

    return kGpaStatusOk;
}

// For the SQTT + SPM combined session, we only initialize the SqttExtSession.
IAmdExtGpaSession* Dx12GpaSession::GetSpmSession()
{
    const bool         is_sqtt_spm_sample = GetSampleType() == kGpaSessionSampleTypeStreamingCounterAndSqtt;
    IAmdExtGpaSession* amd_ext_session    = is_sqtt_spm_sample ? sqtt_amd_ext_session_ : spm_amd_ext_session_;
    return amd_ext_session;
}

GpaStatus Dx12GpaSession::SpmGetSampleResultSize(size_t* sample_result_size_in_bytes)
{
    assert(sample_result_size_in_bytes != nullptr);
    IAmdExtGpaSession* amd_ext_session = GetSpmSession();
    if (!FlushSession(amd_ext_session, flush_timeout_))
    {
        GPA_LOG_ERROR("Failed to retrieve sample data due to timeout.");
        return kGpaStatusErrorTimeout;
    }

    *sample_result_size_in_bytes = 0;

    HRESULT driverResult = amd_ext_session->GetResults(spm_driver_sample_id_, sample_result_size_in_bytes, nullptr);
    if (FAILED(driverResult))
    {
        GPA_LOG_ERROR("Failed to retrieve driver result size");
        return kGpaStatusErrorFailed;
    }

    return kGpaStatusOk;
}

GpaStatus Dx12GpaSession::SpmGetSampleResult(size_t sample_result_size_in_bytes, void* spm_results)
{
    assert(sample_result_size_in_bytes > 0);
    assert(spm_results != nullptr);
    IAmdExtGpaSession* amd_ext_session = GetSpmSession();
    if (!FlushSession(amd_ext_session, flush_timeout_))
    {
        GPA_LOG_ERROR("Failed to retrieve sample data due to timeout.");
        return kGpaStatusErrorTimeout;
    }

    size_t expected_sample_result_size_in_bytes = 0;

    auto hr = amd_ext_session->GetResults(spm_driver_sample_id_, &expected_sample_result_size_in_bytes, nullptr);
    if (FAILED(hr))
    {
        GPA_LOG_ERROR("Failed to retrieve driver result size");
        return kGpaStatusErrorFailed;
    }

    if (expected_sample_result_size_in_bytes != sample_result_size_in_bytes)
    {
        GPA_LOG_ERROR("Invalid result size");
        return kGpaStatusErrorFailed;
    }

    hr = amd_ext_session->GetResults(spm_driver_sample_id_, &expected_sample_result_size_in_bytes, spm_results);
    if (FAILED(hr))
    {
        GPA_LOG_ERROR("Failed to retrieve driver result set");
        return kGpaStatusErrorFailed;
    }

    return kGpaStatusOk;
}

GpaStatus Dx12GpaSession::SpmCalculateDerivedCounters(const GpaSpmData* spm_data, GpaUInt32 num_derived_counters, GpaUInt64* derived_counter_results)
{
    assert(spm_data != nullptr);
    assert(derived_counter_results != nullptr);

    uint32_t counters_enabled = 0;
    GetNumEnabledCounters(&counters_enabled);

    if (num_derived_counters != counters_enabled * spm_data->number_of_timestamps)
    {
        GPA_LOG_ERROR("SPM size of derived counter results doesn't match count of enabled counters * number of samples.");
        return kGpaStatusErrorFailed;
    }

    GpaStatus status = kGpaStatusOk;

    const auto current_pass = dynamic_cast<Dx12GpaPass*>(GetPasses()[0]);
    if (current_pass == nullptr)
    {
        GPA_LOG_ERROR("Unable to get current pass.");
        return kGpaStatusErrorFailed;
    }

#ifdef _DEBUG
    const auto& sample_config = current_pass->GetAmdExtSampleConfig().GetDriverExtSampleConfig();

    // Validate that expected hardware block id's and instances match those returned by SPM
    if (spm_data->number_of_spm_counter_info != sample_config.perfCounters.numCounters)
    {
        GPA_LOG_ERROR("SPM number of returned hardware counter info structs does not match number expected.");
        return kGpaStatusErrorFailed;
    }

    for (uint32_t i = 0; i < spm_data->number_of_spm_counter_info; ++i)
    {
        if (spm_data->spm_counter_info[i].gpu_block_id != static_cast<uint32_t>(sample_config.perfCounters.pIds[i].block))
        {
            GPA_LOG_ERROR("SPM hardware counter info order does not match expected block id.");
            return kGpaStatusErrorFailed;
        }

        if (spm_data->spm_counter_info[i].gpu_block_instance != sample_config.perfCounters.pIds[i].instance)
        {
            GPA_LOG_ERROR("SPM hardware counter info order does not match expected block instance number.");
            return kGpaStatusErrorFailed;
        }
    }
#endif

    // Generally the SPM data is 16-bits, but some blocks only support 32-bit.
    // Track if the data is returned as 32-bit data, so it can be processed correctly.
    bool is_32bit_data = (spm_data->number_of_bytes_per_counter_data == 4);

    // Build num_derived_counters (sample) number of derived counter sets that can be passed into the equation calculator.
    // sample_sets' outer vector has an entry corresponding to each timestamp.
    // sample_sets' inner vector has an entry for each counter that was collected for that timestamp sample.
    std::vector<std::vector<uint64_t>> sample_sets;

    for (size_t current_sample = 0; current_sample < spm_data->number_of_timestamps; ++current_sample)
    {
        std::vector<uint64_t> sample_set;

        for (uint32_t i = 0; i < spm_data->number_of_spm_counter_info; ++i)
        {
            const GpaSpmCounterInfo& counter_info = spm_data->spm_counter_info[i];
            if (is_32bit_data)
            {
                GpaUInt32* array_u32 = (GpaUInt32*)(spm_data->counter_data_16bit);
                assert(array_u32 != nullptr);
                if (array_u32 != nullptr)
                {
                    try
                    {
                        GpaUInt32 value_u32 = array_u32[counter_info.data_offset + current_sample];

                        // Note there is a conversion here from 32-bit to 64-bit. Since it is expected that the
                        // incoming values are never negative, these should always be reasonable positive values.
                        // However, _LEVEL_ counters may actually be negative 32-bit values will appear as
                        // "likely too high" 64-bit values (up to 4,294,967,295). These will be detected and converted
                        // farther down in the code.
                        uint64_t value = value_u32;

                        sample_set.push_back(value);
                    }
                    catch (const std::exception& e)
                    {
                        GPA_LOG_ERROR("Exception occurred while processing SPM data: %s", e.what());
                        sample_set.push_back(0);
                    }
                }
                else
                {
                    sample_set.push_back(0);
                }
            }
            else
            {
                try
                {
                    GpaUInt16 value_u16 = spm_data->counter_data_16bit[counter_info.data_offset + current_sample];

                    // Note there is a conversion here from 16-bit to 64-bit. Since it is expected that the
                    // incoming values are never negative, these should always be reasonable positive values.
                    // However, _LEVEL_ counters may actually be negative 16-bit values will appear as
                    // "potentially reasonable" 64-bit values (up to 65,535). These will be detected and converted
                    // farther down in the code.
                    uint64_t value = value_u16;

                    sample_set.push_back(value);
                }
                catch (const std::exception& e)
                {
                    GPA_LOG_ERROR("Exception occurred while processing SPM data: %s", e.what());
                    sample_set.push_back(0);
                }
            }
        }

        sample_sets.push_back(sample_set);
    }

    // Calculate return counter values - grouped by counter id
    uint64_t* dest_results = derived_counter_results;

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(this);

    const std::vector<CounterResultEntry>& spm_counter_result_entries = current_pass->GetAmdExtSampleConfig().GetSpmCounterResultEntries();

    // Build counter map
    std::map<uint32_t, const CounterResultEntry*> counter_result_map;

    for (size_t i = 0; i < spm_counter_result_entries.size(); ++i)
    {
        counter_result_map[spm_counter_result_entries[i].counter_id] = &spm_counter_result_entries[i];
    }

    for (uint32_t enabled_counter_index = 0; enabled_counter_index < counters_enabled; enabled_counter_index++)
    {
        GpaUInt32 exposed_counter_index;

        if (kGpaStatusOk != GetEnabledIndex(enabled_counter_index, &exposed_counter_index))
        {
            GPA_LOG_ERROR("Invalid counter found while identifying enabled counter.");
            return kGpaStatusErrorIndexOutOfRange;
        }

        const std::variant<gpa_array_view<GpaUInt32>, GpaUInt32> internal_counters_required =
            GpaContextCounterMediator::Instance()->GetCounterAccessor(this)->GetInternalCountersRequired(exposed_counter_index);
        auto result_locations_map = GetCounterResultLocations();
        auto result_locations     = result_locations_map[exposed_counter_index];

        GpaUInt32        source_local_index = 0;
        GpaCounterSource source             = GpaCounterSource::kUnknown;

        if (!GetCounterSourceLocalIndex(exposed_counter_index, &source, &source_local_index))
        {
            GPA_LOG_ERROR("Invalid counter index found while identifying counter source.");
            return kGpaStatusErrorIndexOutOfRange;
        }

        // Perform conversion and summation of raw *_LEVEL_* counter values before evaluating the counter formula.

        GDT_HW_GENERATION hw_generation;
        assert(GetParentContext() != nullptr);
        const GpaHwInfo& hw_info = GetParentContext()->GetHwInfo();
        if (!hw_info.GetHwGeneration(hw_generation))
        {
            GPA_LOG_ERROR("Unable to get HW generation while calculating SPM derived counter.");
            return kGpaStatusErrorFailed;
        }

        const uint64_t max_waves_per_shader_engine = (hw_info.GetNumberSimds() * hw_info.GetWavesPerSimd()) / hw_info.GetNumberShaderEngines();

        const std::set<unsigned int>& level_counters = counter_accessor->GetHardwareCounters().level_waves_indices_;

        // Store the running sum of a particular level counter.
        std::map<uint32_t, int64_t> level_counter_summations;

        // Sometimes a timing issue will cause a negative number (ie: waves ending) before any waves have started.
        // Track the number of invalid values to report an error (warning) after processing the data.
        GpaUInt32 num_invalid_level_waves = 0;

        for (size_t entry = 0; entry < spm_counter_result_entries.size(); ++entry)
        {
            const uint32_t counter_id    = spm_counter_result_entries[entry].counter_id;
            const uint32_t result_offset = spm_counter_result_entries[entry].offset;

            if (level_counters.find(counter_id) != level_counters.end() && spm_counter_result_entries[entry].in_use)
            {
                // The required counter is a *_LEVEL_* counter, so initialize the summation to 0.
                level_counter_summations[counter_id] = 0;

                for (uint32_t sample_index = 0; sample_index < sample_sets.size(); ++sample_index)
                {
                    const int64_t  pre_sum         = level_counter_summations[counter_id];
                    const uint64_t raw_level_value = sample_sets[sample_index][result_offset];
                    int64_t        post_sum        = 0;

                    // NOTE: On Gfx11 and earlier hardware, the SPM counters can be treated as either 16-bit or 32-bit values.
                    // *_LEVEL_* counters can be positive or negative, but are always returned as an unsigned value.
                    // However, there could be some data truncation anywhere between the hardware, driver, RGP, or GPA,
                    // so use the actual raw value to determine whether it should be positive or negative, and how many bits
                    // are used in the result. Convert it as needed, then add it to the accumulated result.
                    if (raw_level_value <= max_waves_per_shader_engine)
                    {
                        // This is a positive value.
                        if (is_32bit_data)
                        {
                            uint32_t u_32bit = (uint32_t)raw_level_value;
                            post_sum         = pre_sum + u_32bit;
                        }
                        else
                        {
                            uint16_t u_16bit = (uint16_t)raw_level_value;
                            post_sum         = pre_sum + u_16bit;
                        }
                    }
                    else if (raw_level_value <= 0x000000000000FFFF)
                    {
                        // This is a negative 16-bit value.
                        uint16_t u_16bit      = (uint16_t)raw_level_value;
                        int16_t  signed_16bit = (short)u_16bit;
                        post_sum              = pre_sum + signed_16bit;
                    }
                    else
                    {
                        // raw_level_value <= 0x00000000FFFFFFFF
                        // This is a negative 32-bit value.
                        uint32_t u_32bit      = (uint32_t)raw_level_value;
                        int32_t  signed_32bit = (int32_t)u_32bit;
                        post_sum              = pre_sum + signed_32bit;
                    }

                    // The post_sum should always be greater than zero, but it can go negative due to race conditions on the hardware or if the SPM buffer wraps.
                    // Trigger an assert if we detect it, and also treat it as an error if the value is "too" negative.
                    assert(post_sum >= 0);
                    if (post_sum < 0)
                    {
                        if (post_sum >= max_waves_per_shader_engine * -0.05)
                        {
                            // Allow for the number of running waves to go 5% below 0 and filter them out by resetting the post_sum to zero.
                            post_sum = 0;

                            ++num_invalid_level_waves;
                        }
                        else
                        {
                            // If the post_sum went "too" negative then return an error since the values may be too inaccurate to be trustworthy.
                            GPA_LOG_ERROR("Detected incorrect data (%" PRId64
                                          ") while collecting WaveDistribution or WaveOccupancyPct, please refresh that graph to try again.",
                                          post_sum);
                            return kGpaStatusErrorFailed;
                        }
                    }

                    level_counter_summations[counter_id] = post_sum;

                    sample_sets[sample_index][result_offset] = post_sum;
                }
            }
        }

        if (num_invalid_level_waves > 0)
        {
            GPA_LOG_ERROR("Fixed up %u invalid values in Wave Distribution.", num_invalid_level_waves);
        }

        for (uint32_t current_sample = 0; current_sample < spm_data->number_of_timestamps; ++current_sample, ++dest_results)
        {
            switch (source)
            {
            case GpaCounterSource::kPublic:
            {
                const auto& samples = sample_sets[current_sample];

                constexpr uint32_t              kCounterSourcePublic       = static_cast<uint32_t>(GpaCounterSource::kPublic);
                const gpa_array_view<GpaUInt32> required_hardware_counters = std::get<kCounterSourcePublic>(internal_counters_required);

                const size_t required_count = required_hardware_counters.size();

                std::vector<GpaUInt64> results(required_count);

                unsigned int result_index = 0;
                for (const GpaUInt32 counter : required_hardware_counters)
                {
                    GpaUInt64* result_buffer = &results[result_index];
                    ++result_index;

                    auto counter_result_entry = counter_result_map[counter];

                    if (!counter_result_entry->in_use)
                    {
                        *result_buffer = 0;
                    }
                    else
                    {
                        *result_buffer = samples[counter_result_entry->offset];
                    }
                }

                // The code below is only valid while the only data types supported are Float64 and Uint64
                static_assert(kGpaDataTypeLast == 2);

                status = counter_accessor->ComputePublicCounterValue(source_local_index, results, &dest_results, GetParentContext()->GetHwInfo());

                break;
            }

            case GpaCounterSource::kHardware:
            {
                const auto& results = sample_sets[current_sample];
                *dest_results       = results[enabled_counter_index];
                break;
            }

            default:
                status = kGpaStatusErrorFailed;
                GPA_LOG_ERROR("Unknown counter source type.");
                assert(0);
                break;
            }

            if (status != kGpaStatusOk)
            {
                break;
            }
        }

        if (status != kGpaStatusOk)
        {
            break;
        }
    }

    return status;
}
