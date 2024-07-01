//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GPA Sample Implementation.
//==============================================================================

#include "gpu_perf_api_common/gpa_sample.h"

#include "gpu_perf_api_common/gpa_command_list_interface.h"
#include "gpu_perf_api_common/gpa_context_interface.h"
#include "gpu_perf_api_common/gpa_pass.h"

GpaSample::GpaSample(GpaPass* gpa_pass, IGpaCommandList* gpa_cmd_list, GpaSampleType sample_type, ClientSampleId client_sample_id)
    : gpa_pass_(gpa_pass)
    , gpa_cmd_list_(gpa_cmd_list)
    , gpa_sample_type_(sample_type)
    , client_sample_id_(client_sample_id)
    , driver_sample_id_(0)
    , gpa_sample_state_(GpaSampleState::kInitialized)
    , sample_result_(nullptr)
    , continuing_sample_(nullptr)
    , is_opened_(false)
    , is_closed_by_client_(false)
    , is_continued_by_client_(false)
    , is_copied_sample_(false)
{
    is_secondary_ = (kGpaCommandListSecondary == gpa_cmd_list->GetCmdType());

    // First, only allocate result space for primary samples.
    // If a secondary sample gets copied, then it will also get space allocated for the results.
    if (!is_secondary_)
    {
        AllocateSampleResultSpace();
    }
}

GPA_THREAD_SAFE_FUNCTION bool GpaSample::Begin()
{
    bool result = false;

    std::lock_guard<std::mutex> lock_sample(sample_mutex_);
    result = BeginRequest();

    if (result)
    {
        gpa_sample_state_ = GpaSampleState::kStarted;
        is_opened_        = true;
    }

    return result;
}

bool GpaSample::End()
{
    // Make sure this request is valid before trying to end it.
    if (gpa_sample_state_ != GpaSampleState::kStarted)
    {
        return false;
    }

    bool result = EndRequest();

    if (result)
    {
        gpa_sample_state_ = GpaSampleState::kPendingResults;
    }

    return result;
}

bool GpaSample::GetResult(CounterIndex counter_index_in_sample, GpaUInt64* counter_result) const
{
    bool has_result = false;

    if (!IsSecondary() || IsCopied())
    {
        if (nullptr != counter_result && IsResultCollected())
        {
            if (nullptr != sample_result_ && counter_index_in_sample < sample_result_->GetAsCounterSampleResult()->GetNumCounters() &&
                nullptr != sample_result_->GetAsCounterSampleResult()->GetResultBuffer())
            {
                has_result      = true;
                *counter_result = sample_result_->GetAsCounterSampleResult()->GetResultBuffer()[counter_index_in_sample];
            }
            else
            {
                GPA_LOG_ERROR("Counter Index out of range.");
            }
        }
        else
        {
            GPA_LOG_ERROR("Either the sample is not completed or the result buffer is invalid.");
        }
    }

    return has_result;
}

void GpaSample::SetDriverSampleId(const DriverSampleId& driver_sample_id)
{
    driver_sample_id_ = driver_sample_id;
}

DriverSampleId GpaSample::GetDriverSampleId() const
{
    return driver_sample_id_;
}

ClientSampleId GpaSample::GetClientSampleId() const
{
    return client_sample_id_;
}

void GpaSample::AllocateSampleResultSpace()
{
    if (nullptr == sample_result_)
    {
        {
            sample_result_ = new (std::nothrow) GpaCounterSampleResult(gpa_pass_->GetEnabledCounterCount());
        }
    }
}

bool GpaSample::IsSecondary() const
{
    return is_secondary_;
}

GpaSampleType GpaSample::GetGpaSampleType() const
{
    return gpa_sample_type_;
}

GpaSampleState GpaSample::GetGpaSampleState() const
{
    return gpa_sample_state_;
}

GpaSampleResult* GpaSample::GetSampleResultLocation() const
{
    return sample_result_;
}

GpaSample* GpaSample::GetContinuingSample() const
{
    return continuing_sample_;
}

GPA_THREAD_SAFE_FUNCTION bool GpaSample::SetAsClosedByClient()
{
    bool                        success = false;
    std::lock_guard<std::mutex> lock_sample(sample_mutex_);

    if (!is_continued_by_client_)
    {
        is_closed_by_client_ = true;
        success              = true;
    }
    else
    {
        GPA_LOG_ERROR("Sample has already been continued by client.");
    }

    return success;
}

bool GpaSample::SetAsCopied()
{
    bool                        success = false;
    std::lock_guard<std::mutex> lock_sample(sample_mutex_);
    gpa_sample_state_ = GpaSampleState::kPendingResults;

    if (!is_copied_sample_)
    {
        is_copied_sample_ = true;
        AllocateSampleResultSpace();
        success = true;
    }
    else
    {
        GPA_LOG_ERROR("Sample has already been copied by client.");
    }

    return success;
}

bool GpaSample::IsCopied() const
{
    return is_copied_sample_;
}

bool GpaSample::IsClosedByClient() const
{
    return is_closed_by_client_;
}

bool GpaSample::IsContinuedByClient() const
{
    return is_continued_by_client_;
}

GPA_THREAD_SAFE_FUNCTION bool GpaSample::SetAsContinuedByClient()
{
    std::lock_guard<std::mutex> lock_sample(sample_mutex_);
    bool                        success = false;

    if (!is_closed_by_client_)
    {
        is_continued_by_client_ = true;
        success                 = true;
    }
    else
    {
        GPA_LOG_ERROR("Sample has already been closed by client.");
    }

    return success;
}

bool GpaSample::IsSampleValid() const
{
    // A sample is only valid if it is opened and either it is continued/copied on another command list or closed on the same command list on which it was created.
    bool valid =
        (is_opened_ && ((is_closed_by_client_ && !is_continued_by_client_) || (!is_closed_by_client_ && is_continued_by_client_))) || is_copied_sample_;
    return valid;
}

bool GpaSample::IsClosed() const
{
    return is_closed_by_client_ || is_continued_by_client_;
}

void GpaSample::MarkAsCompleted()
{
    gpa_sample_state_ = GpaSampleState::kResultsCollected;
}

bool GpaSample::IsSampleContinuing() const
{
    return nullptr != continuing_sample_;
}

IGpaCommandList* GpaSample::GetCmdList() const
{
    return gpa_cmd_list_;
}

bool GpaSample::LinkContinuingSample(GpaSample* continuing_sample)
{
    std::lock_guard<std::recursive_mutex> lock(continue_sample_mutex_);

    if (nullptr == continuing_sample)
    {
        return false;
    }

    bool success = true;

    if (nullptr != continuing_sample_)
    {
        success &= continuing_sample_->LinkContinuingSample(continuing_sample);
    }
    else
    {
        // Check whether the continuing sample is on different command list or not.
        if (continuing_sample->gpa_cmd_list_ == gpa_cmd_list_)
        {
            success = false;
        }
        else
        {
            continuing_sample_ = continuing_sample;
            success            = true;
        }
    }

    return success;
}

GpaPass* GpaSample::GetPass() const
{
    return gpa_pass_;
}

GpaSample::~GpaSample()
{
    if (nullptr != continuing_sample_)
    {
        delete continuing_sample_;
    }

    delete sample_result_;
}
