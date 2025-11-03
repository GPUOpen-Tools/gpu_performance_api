//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Class to manage a single sample of HW counters
//==============================================================================

#include "gpu_perf_api_vk/vk_gpa_hardware_sample.h"

#include "gpu_perf_api_common/gpa_context_counter_mediator.h"

#include "gpu_perf_api_counter_generator/gpa_hardware_counters.h"

#include "gpu_perf_api_vk/vk_entry_points.h"
#include "gpu_perf_api_vk/vk_gpa_command_list.h"
#include "gpu_perf_api_vk/vk_gpa_pass.h"

static const uint32_t kInvalidSampleIndex = static_cast<uint32_t>(-1);  ///< Invalid sample index.

VkGpaHardwareSample::VkGpaHardwareSample(GpaPass* pass, IGpaCommandList* command_list, unsigned int sample_id)
    : VkGpaSample(pass, command_list, GpaSampleType::kHardware, sample_id)
    , num_counters_(0)
    , sample_index_(kInvalidSampleIndex)
    , command_buffer_(vk_gpa_command_list_->GetVkCommandBuffer())
    , has_any_hardware_counters_(false)
{
    VkGpaCommandList* gpa_command_list = dynamic_cast<VkGpaCommandList*>(command_list);
    gpa_session_                       = (nullptr != gpa_command_list) ? gpa_command_list->GetAmdExtSession() : VK_NULL_HANDLE;
}

VkGpaHardwareSample::~VkGpaHardwareSample()
{
    if (VK_NULL_HANDLE != command_buffer_)
    {
        command_buffer_ = VK_NULL_HANDLE;
    }
}

bool VkGpaHardwareSample::BeginRequest()
{
    bool result = false;

    num_counters_              = GetPass()->GetEnabledCounterCount();
    has_any_hardware_counters_ = num_counters_ > 0;

    VkGpaPass* gpa_pass = dynamic_cast<VkGpaPass*>(GetPass());

    if (nullptr == gpa_pass)
    {
        GPA_LOG_ERROR("Invalid GPAPass encountered in hardware sample begin request.");
    }
    else
    {
        if (GetPass()->IsTimingPass() || has_any_hardware_counters_)
        {
            VkResult begin_result = _vkCmdBeginGpaSampleAMD(command_buffer_, gpa_session_, gpa_pass->GetVkSampleBeginInfo(), &sample_index_);
            result                = (VK_SUCCESS == begin_result && kInvalidSampleIndex != sample_index_);

            if (result)
            {
                GpaSample::SetDriverSampleId(sample_index_);
            }
        }
        else
        {
            // Sample doesn't have any available hardware counters for this specific hardware revision, so we need to pretend this succeeded.
            result = true;
        }
    }

    return result;
}

bool VkGpaHardwareSample::EndRequest()
{
    if (GetPass()->IsTimingPass() || has_any_hardware_counters_)
    {
        _vkCmdEndGpaSampleAMD(command_buffer_, gpa_session_, sample_index_);
    }

    return true;
}

void VkGpaHardwareSample::ReleaseCounters()
{
    GPA_STUB_FUNCTION;
}

bool VkGpaHardwareSample::UpdateResults()
{
    if (GpaSampleState::kResultsCollected == GetGpaSampleState())
    {
        return true;
    }

    bool is_updated = false;

    // Samples that are the original secondary samples will not have results.
    if (IsSecondary() && !IsCopied())
    {
        MarkAsCompleted();
        is_updated = true;
    }

    if (GpaSampleState::kPendingResults == GetGpaSampleState())
    {
        is_updated = (nullptr != PopulateSampleResults());
    }

    return is_updated;
}

GpaSampleResult* VkGpaHardwareSample::PopulateSampleResults()
{
    size_t sample_data_size = 0u;

    // Validate result space.
    if (GetPass()->IsTimingPass())
    {
        sample_data_size = 2 * sizeof(uint64_t);
    }
    else
    {
        sample_data_size = GetSampleResultLocation()->GetBufferBytes();
    }

    GpaUInt64* result_buffer  = nullptr;
    GpaUInt64  timing_data[2] = {};

    if (sample_data_size > 0)
    {
        if (nullptr == GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer())
        {
            GPA_LOG_ERROR("Incorrect space allocated for sample result.");
        }
        else
        {
            if (GetPass()->IsTimingPass())
            {
                result_buffer = timing_data;
            }
            else
            {
                result_buffer = GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer();
            }

            if (CopyResult(sample_data_size, result_buffer))
            {
                if (GetPass()->IsTimingPass())
                {
                    const GpaHardwareCounters& hardware_counters = GetPass()->GetSessionContextCounterAccessor()->GetHardwareCounters();

                    for (CounterCount i = 0; i < GetPass()->GetEnabledCounterCount(); ++i)
                    {
                        CounterIndex counter_index;
                        GetPass()->GetCounterByIndexInPass(i, &counter_index);

                        if (counter_index == hardware_counters.gpu_time_bottom_to_bottom_duration_counter_index_)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = timing_data[1] - timing_data[0];
                        }
                        else if (counter_index == hardware_counters.gpu_time_bottom_to_bottom_start_counter_index_)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = timing_data[0];
                        }
                        else if (counter_index == hardware_counters.gpu_time_bottom_to_bottom_end_counter_index_)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = timing_data[1];
                        }
                        else if (counter_index == hardware_counters.gpu_time_top_to_bottom_duration_counter_index_)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = timing_data[1] - timing_data[0];
                        }
                        else if (counter_index == hardware_counters.gpu_time_top_to_bottom_start_counter_index_)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[i] = timing_data[0];
                        }
                        else if (counter_index == hardware_counters.gpu_time_top_to_bottom_end_counter_index_)
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
                    GpaSampleResult* sample_result = dynamic_cast<VkGpaHardwareSample*>(GetContinuingSample())->PopulateSampleResults();

                    if (nullptr == sample_result)
                    {
                        GPA_LOG_ERROR("Invalid GPASample encountered when populating results of continued sample.");
                    }
                    else
                    {
                        for (size_t counter_iter = 0; counter_iter < GetSampleResultLocation()->GetAsCounterSampleResult()->GetNumCounters(); counter_iter++)
                        {
                            GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[counter_iter] +=
                                sample_result->GetAsCounterSampleResult()->GetResultBuffer()[counter_iter];
                        }
                    }
                }

                MarkAsCompleted();
            }
            else
            {
                GPA_LOG_ERROR("Unable to get the result from the driver.");
            }
        }
    }

    return GetSampleResultLocation();
}

bool VkGpaHardwareSample::CopyResult(size_t sample_data_size, void* result_buffer) const
{
    bool is_data_ready = false;

    if (nullptr != result_buffer)
    {
        VkGpaCommandList* gpa_command_list = dynamic_cast<VkGpaCommandList*>(GetCmdList());

        if (nullptr == gpa_command_list)
        {
            GPA_LOG_ERROR("Invalid GPACommandList encountered while copying hardware counter results.");
        }
        else
        {
            VkGpaSessionAMD ext_session_amd = gpa_command_list->GetAmdExtSession();

            if (IsCopied())
            {
                ext_session_amd = gpa_command_list->GetCopiedAmdExtSession(GetClientSampleId());
                assert(VK_NULL_HANDLE != ext_session_amd);
            }
            else
            {
                ext_session_amd = gpa_command_list->GetAmdExtSession();
                assert(VK_NULL_HANDLE != ext_session_amd);
            }

            VkGpaContext* gpa_context = dynamic_cast<VkGpaContext*>(gpa_command_list->GetParentSession()->GetParentContext());

            if (nullptr == gpa_context)
            {
                GPA_LOG_ERROR("Invalid GPAContext encountered while copying hardware counter results.");
            }
            else
            {
                VkDevice device = gpa_context->GetVkDevice();

                if (VK_NULL_HANDLE == ext_session_amd)
                {
                    GPA_LOG_ERROR("Invalid profiling session encountered while copying results.");
                }
                else
                {
                    VkResult is_ready = _vkGetGpaSessionStatusAMD(gpa_context->GetVkDevice(), ext_session_amd);

                    if (VK_SUCCESS == is_ready)
                    {
                        size_t   sample_data_size_in_driver = 0u;
                        VkResult got_result_size =
                            _vkGetGpaSessionResultsAMD(device, ext_session_amd, GetDriverSampleId(), &sample_data_size_in_driver, nullptr);
                        assert(VK_SUCCESS == got_result_size);
                        assert(sample_data_size == sample_data_size_in_driver);

                        if (VK_SUCCESS == got_result_size && sample_data_size == sample_data_size_in_driver)
                        {
                            VkResult result =
                                _vkGetGpaSessionResultsAMD(device, ext_session_amd, GetDriverSampleId(), &sample_data_size_in_driver, result_buffer);
                            assert(VK_SUCCESS == result);

                            if (VK_SUCCESS == result)
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
        }
    }

    return is_data_ready;
}
