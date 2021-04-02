//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX12 GPA Sample implementation
//==============================================================================

#include "gpu_perf_api_dx12/dx12_gpa_sample.h"

#include "gpu_perf_api_counter_generator/gpa_hardware_counters.h"

#include "gpu_perf_api_common/gpa_context_counter_mediator.h"

#include "gpu_perf_api_dx12/dx12_gpa_command_list.h"

Dx12GpaSample::Dx12GpaSample(GpaPass* pass, IGpaCommandList* cmd_list, GpaSampleType sample_type, ClientSampleId sample_id)
    : GpaSample(pass, cmd_list, sample_type, sample_id)
{
}

bool Dx12GpaSample::UpdateResults()
{
    if (GpaSampleState::kResultsCollected == GetGpaSampleState())
    {
        return true;
    }

    bool is_updated = false;

    if (IsSecondary())
    {
        MarkAsCompleted();
        is_updated = true;
    }

    if (GpaSampleState::kPendingResults == GetGpaSampleState() && !IsSecondary())
    {
        is_updated = (nullptr != PopulateSampleResult());
    }

    return is_updated;
}

bool Dx12GpaSample::BeginRequest()
{
    return true;
}

bool Dx12GpaSample::EndRequest()
{
    return true;
}

void Dx12GpaSample::ReleaseCounters()
{
    GPA_STUB_FUNCTION;
}

GpaSampleResult* Dx12GpaSample::PopulateSampleResult()
{
    size_t sample_data_bytes = 0u;

    // Validate result space.
    sample_data_bytes = GetSampleResultLocation()->GetBufferBytes();

    if (0 != sample_data_bytes)
    {
        if (nullptr != GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer())
        {
            GpaUInt64* result_buffer  = nullptr;
            GpaUInt64  timing_data[2] = {};

            if (GetPass()->IsTimingPass())
            {
                result_buffer     = timing_data;
                sample_data_bytes = sizeof(timing_data);
            }
            else
            {
                result_buffer = GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer();
            }

            if (CopyResult(sample_data_bytes, result_buffer))
            {
                if (GetPass()->IsTimingPass())
                {
                    const GpaHardwareCounters* hardware_counters = GetPass()->GetSessionContextCounterAccessor()->GetHardwareCounters();

                    for (CounterCount i = 0; i < GetPass()->GetEnabledCounterCount(); ++i)
                    {
                        CounterIndex counter_index;
                        GetPass()->GetCounterByIndexInPass(i, &counter_index);

                        if (counter_index == hardware_counters->gpu_time_bottom_to_bottom_duration_counter_index_)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = timing_data[1] - timing_data[0];
                        }
                        else if (counter_index == hardware_counters->gpu_time_bottom_to_bottom_start_counter_index_)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = timing_data[0];
                        }
                        else if (counter_index == hardware_counters->gpu_time_bottom_to_bottom_end_counter_index_)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = timing_data[1];
                        }
                        else if (counter_index == hardware_counters->gpu_time_top_to_bottom_duration_counter_index_)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = timing_data[1] - timing_data[0];
                        }
                        else if (counter_index == hardware_counters->gpu_time_top_to_bottom_start_counter_index_)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = timing_data[0];
                        }
                        else if (counter_index == hardware_counters->gpu_time_top_to_bottom_end_counter_index_)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = timing_data[1];
                        }
                        else
                        {
                            GPA_LOG_ERROR("Unknown timing counter.");
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = 0;
                        }
                    }
                }

                if (IsSampleContinuing())
                {
                    GpaSampleResult* sample_result = reinterpret_cast<Dx12GpaSample*>(GetContinuingSample())->PopulateSampleResult();

                    for (size_t counter_iter = 0; counter_iter < GetPass()->GetEnabledCounterCount(); counter_iter++)
                    {
                        GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[counter_iter] +=
                            sample_result->GetAsCounterSampleResult()->GetResultBuffer()[counter_iter];
                    }
                }

                MarkAsCompleted();
            }
            else
            {
                GPA_LOG_ERROR("Unable to get the result from the driver.");
            }
        }
        else
        {
            GPA_LOG_ERROR("Incorrect space allocated for sample result.");
        }
    }

    return GetSampleResultLocation();
}

bool Dx12GpaSample::CopyResult(size_t sample_data_size, void* result_buffer) const
{
    bool is_data_ready                   = false;
    bool is_any_hardware_counter_enabled = GetPass()->GetEnabledCounterCount() > 0;

    if (nullptr != result_buffer)
    {
        if (is_any_hardware_counter_enabled)
        {
            Dx12GpaCommandList* dx12_gpa_cmd_list = reinterpret_cast<Dx12GpaCommandList*>(GetCmdList());

            IAmdExtGpaSession* result_session = nullptr;

            if (IsCopied())
            {
                result_session = dx12_gpa_cmd_list->GetBundleResultAmdExtSession(GetClientSampleId());
            }
            else
            {
                result_session = dx12_gpa_cmd_list->GetAmdExtSession();
            }

            if (nullptr == result_session)
            {
                GPA_LOG_ERROR("Invalid profiling session encountered while copying results.");
            }
            else
            {
                if (result_session->IsReady())
                {
                    size_t  sample_data_size_in_driver = 0u;
                    HRESULT driver_result              = result_session->GetResults(GetDriverSampleId(), &sample_data_size_in_driver, nullptr);
                    assert(SUCCEEDED(driver_result));
                    assert(sample_data_size == sample_data_size_in_driver);

                    if (SUCCEEDED(driver_result) && sample_data_size == sample_data_size_in_driver)
                    {
                        driver_result = result_session->GetResults(GetDriverSampleId(), &sample_data_size_in_driver, result_buffer);
                        assert(SUCCEEDED(driver_result));

                        if (SUCCEEDED(driver_result))
                        {
                            is_data_ready = true;
                        }
                        else
                        {
                            GPA_LOG_ERROR("Error occurred while getting sample results from driver.");
                        }
                    }
                    else
                    {
                        GPA_LOG_ERROR("Error occurred while getting sample result size from driver.");
                    }
                }
            }
        }
        else
        {
            // There is no hardware counter enabled in the driver, put zeros in all result location.
            memset(result_buffer, 0, sample_data_size);
            is_data_ready = true;
        }
    }

    return is_data_ready;
}