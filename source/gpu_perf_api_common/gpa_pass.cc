//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GPA Pass Object Implementation.
//==============================================================================

#include "gpu_perf_api_common/gpa_pass.h"

#include <algorithm>

#include "gpu_perf_api_counter_generator/gpa_hardware_counters.h"

#include "gpu_perf_api_common/gpa_command_list.h"
#include "gpu_perf_api_common/gpa_context_counter_mediator.h"

GpaPass::GpaPass(IGpaSession* gpa_session, PassIndex pass_index, GpaCounterSource counter_source, CounterList* pass_counters)
    : gpa_session_(gpa_session)
    , pass_index_(pass_index)
    , counter_source_(counter_source)
    , is_result_collected_(false)
    , is_result_ready_(false)
    , is_timing_pass_(false)
    , gpa_internal_sample_counter_(0U)
    , command_list_counter_(0U)
    , is_all_sample_valid_in_pass_(false)
    , is_pass_complete_(false)
    , is_sqtt_pass_(false)
    , is_spm_pass_(false)
{
    counter_list_ = pass_counters;

    if (nullptr != counter_list_ && !counter_list_->empty())
    {
        const IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::GetCounterAccessor(GetGpaSession());
        assert(counter_accessor != nullptr);
        if (nullptr != counter_accessor)
        {
            const GpaHardwareCounters& hardware_counters = counter_accessor->GetHardwareCounters();
            const CounterIndex         front             = counter_list_->front();
            if (hardware_counters.IsTimeCounterIndex(front))
            {
                is_timing_pass_ = true;
            }
        }
    }

    GpaSessionSampleType session_sample_type = gpa_session_->GetSampleType();

    if (kGpaSessionSampleTypeSqtt == session_sample_type)
    {
        is_sqtt_pass_ = true;
    }

    if (kGpaSessionSampleTypeStreamingCounter == session_sample_type)
    {
        is_spm_pass_ = true;
    }
}

GpaPass::~GpaPass()
{
    gpa_cmd_list_mutex_.lock();

    for (auto it = gpa_cmd_lists_.begin(); it != gpa_cmd_lists_.end(); ++it)
    {
        delete (*it);
    }

    gpa_cmd_lists_.clear();
    gpa_cmd_list_mutex_.unlock();

    std::lock_guard<std::mutex> lock(samples_unordered_map_mutex_);

    for (auto sample_pair : samples_unordered_map_)
    {
        GpaSample* sample = sample_pair.second;
        delete sample;
    }

    samples_unordered_map_.clear();
}

GpaCounterSource GpaPass::GetCounterSource() const
{
    return counter_source_;
}

GpaSample* GpaPass::GetSampleById(ClientSampleId sample_id) const
{
    std::lock_guard<std::mutex> lock(samples_unordered_map_mutex_);

    return GetSampleByIdNotThreadSafe(sample_id);
}

GpaSample* GpaPass::GetSampleByIdNotThreadSafe(ClientSampleId client_sample_id) const
{
    GpaSample* ret_val = nullptr;

    if (samples_unordered_map_.find(client_sample_id) != samples_unordered_map_.end())
    {
        ret_val = samples_unordered_map_.at(client_sample_id);
    }

    return ret_val;
}

GpaSample* GpaPass::CreateAndBeginSample(ClientSampleId client_sample_id, IGpaCommandList* gpa_cmd_list)
{
    std::lock_guard<std::mutex> lock(samples_unordered_map_mutex_);

    GpaSample* sample = nullptr;

    if (!DoesSampleExistNotThreadSafe(client_sample_id))
    {
        if (is_sqtt_pass_)
        {
            sample = CreateApiSpecificSample(gpa_cmd_list, GpaSampleType::kSqtt, client_sample_id);
        }
        else if (is_spm_pass_)
        {
            sample = CreateApiSpecificSample(gpa_cmd_list, GpaSampleType::kSpm, client_sample_id);
        }
        else if (GpaCounterSource::kHardware == counter_source_)
        {
            sample = CreateApiSpecificSample(gpa_cmd_list, GpaSampleType::kHardware, client_sample_id);
        }

        if (nullptr != sample)
        {
            if (!gpa_cmd_list->BeginSample(client_sample_id, sample))
            {
                GPA_LOG_ERROR("Unable to begin sample in pass.");
                delete sample;
                sample = nullptr;
            }
            else
            {
                samples_unordered_map_.insert(std::pair<ClientSampleId, GpaSample*>(client_sample_id, sample));
            }
        }
        else
        {
            GPA_LOG_ERROR("Unable to create sample.");
        }
    }
    else
    {
        GPA_LOG_ERROR("Sample Id already exists.");
    }

    return sample;
}

bool GpaPass::ContinueSample(ClientSampleId src_sample_id, IGpaCommandList* primary_gpa_cmd_list)
{
    std::lock_guard<std::mutex> lock(samples_unordered_map_mutex_);

    // 1. Validate that sample already exists in the pass.
    // 2. Create a new sample on the cmd.
    // 3. Link the new GPA Sample to the old GPA Sample.
    // 4. Update the sample map.

    // In continuing a sample, we need to check only that the srcSampleId exists (it may not be closed at this point)
    // and primary command list is not same as that of that of the src_sample_id.
    // Rather than closing the sample over here, we will let the sample close upon closing the command list.
    // In this way, we do not need to synchronize the samples on different command list (in multi-thread application they might be on different thread).
    // We will mark the parent sample as to be continued by the client.

    bool success = false;

    if (is_sqtt_pass_ || is_spm_pass_)
    {
        // Do nothing
    }
    else
    {
        GpaSample* parent_sample = GetSampleByIdNotThreadSafe(src_sample_id);

        if (nullptr != parent_sample)
        {
            IGpaCommandList* parent_sample_cmd_list = parent_sample->GetCmdList();

            // Validate that both command list are different and passed command list is not secondary.
            if (nullptr != parent_sample_cmd_list && nullptr != primary_gpa_cmd_list && kGpaCommandListSecondary != primary_gpa_cmd_list->GetCmdType() &&
                primary_gpa_cmd_list != parent_sample_cmd_list)
            {
                if (nullptr != parent_sample && primary_gpa_cmd_list->IsCommandListRunning() && primary_gpa_cmd_list->IsLastSampleClosed())
                {
                    GpaSampleType sample_type = (GpaCounterSource::kHardware == GetCounterSource()) ? GpaSampleType::kHardware : GpaSampleType::kSoftware;
                    // We don't need to add this sample to the sample map as it will be linked to the parent sample.
                    GpaSample* new_sample = CreateApiSpecificSample(primary_gpa_cmd_list, sample_type, src_sample_id);

                    if (nullptr != new_sample)
                    {
                        if (!primary_gpa_cmd_list->BeginSample(src_sample_id, new_sample))
                        {
                            GPA_LOG_ERROR("Unable to begin continued sample in pass.");
                            delete new_sample;
                            new_sample = nullptr;
                        }
                        else
                        {
                            parent_sample->SetAsContinuedByClient();
                            // Link the sample to the parent sample.
                            parent_sample->LinkContinuingSample(new_sample);

                            success = true;
                        }
                    }
                }
                else
                {
                    GPA_LOG_ERROR(
                        "Unable to continue sample: Either the specified command list has already been closed or the previous sample has not been closed.");
                }
            }
            else
            {
                GPA_LOG_ERROR(
                    "Unable to continue sample: The specified command list must be a secondary command list and it must be different than the parent sample's "
                    "command list.");
            }
        }
        else
        {
            GPA_LOG_ERROR("Unable to continue sample: The specified sample id was not found in this pass.");
        }
    }

    return success;
}

IGpaCommandList* GpaPass::CreateCommandList(void* cmd_list, GpaCommandListType cmd_type)
{
    IGpaCommandList* ret_cmd_list = CreateApiSpecificCommandList(cmd_list, command_list_counter_, cmd_type);
    command_list_counter_++;

    if (nullptr != ret_cmd_list)
    {
        AddCommandList(ret_cmd_list);
    }

    return ret_cmd_list;
}

SampleCount GpaPass::GetSampleCount() const
{
    std::lock_guard<std::mutex> lock(samples_unordered_map_mutex_);
    return static_cast<SampleCount>(samples_unordered_map_.size());
}

bool GpaPass::GetSampleIdByIndex(SampleIndex sample_index, ClientSampleId& client_sample_id) const
{
    std::lock_guard<std::mutex> lock(samples_unordered_map_mutex_);
    bool                        found = client_gpa_samples_map_.find(sample_index) != client_gpa_samples_map_.end();

    if (found)
    {
        client_sample_id = client_gpa_samples_map_.at(sample_index);
    }

    return found;
}

bool GpaPass::IsAllSampleValidInPass() const
{
    if (!is_all_sample_valid_in_pass_)
    {
        bool                        success = true;
        std::lock_guard<std::mutex> lock_samples(samples_unordered_map_mutex_);

        for (auto sample_iter = samples_unordered_map_.cbegin(); sample_iter != samples_unordered_map_.cend(); ++sample_iter)
        {
            success &= sample_iter->second->IsSampleValid();
        }

        if (success)
        {
            is_all_sample_valid_in_pass_ = true;
        }
    }

    return is_all_sample_valid_in_pass_;
}

CounterCount GpaPass::GetEnabledCounterCount() const
{
    return static_cast<unsigned int>(used_counter_list_for_pass_.size());
}

CounterCount GpaPass::GetSkippedCounterCount() const
{
    return static_cast<unsigned int>(skipped_counter_list_.size());
}

PassIndex GpaPass::GetIndex() const
{
    return pass_index_;
}

bool GpaPass::IsTimingPass() const
{
    return is_timing_pass_;
}

bool GpaPass::UpdateResults()
{
    std::lock_guard<std::mutex> lock(samples_unordered_map_mutex_);

    if (!is_result_collected_)
    {
        bool tmp_all_results_collected = true;

        for (auto sampleIter = samples_unordered_map_.begin(); sampleIter != samples_unordered_map_.end(); ++sampleIter)
        {
            tmp_all_results_collected &= sampleIter->second->UpdateResults();
        }

        is_result_collected_ = tmp_all_results_collected;
    }

    return is_result_collected_;
}

GpaStatus GpaPass::IsComplete() const
{
    GpaStatus ret_status = kGpaStatusOk;

    std::lock_guard<std::mutex> lock_cmd_list(gpa_cmd_list_mutex_);

    if (!is_pass_complete_)
    {
        bool completed = true;

        for (auto cmd_iter = gpa_cmd_lists_.cbegin(); cmd_iter != gpa_cmd_lists_.cend() && completed; ++cmd_iter)
        {
            completed = !(*cmd_iter)->IsCommandListRunning();
        }

        if (!completed)
        {
            ret_status = kGpaStatusErrorCommandListNotEnded;
        }
        else
        {
            completed = IsAllSampleValidInPass();

            if (!completed)
            {
                ret_status = kGpaStatusErrorSampleNotEnded;
            }
            else
            {
                is_pass_complete_ = true;
            }
        }
    }

    return ret_status;
}

bool GpaPass::IsResultReady() const
{
    std::lock_guard<std::mutex> lock_cmd_list(gpa_cmd_list_mutex_);
    bool                        is_ready = is_result_ready_;

    if (!is_ready)
    {
        is_ready = true;

        for (auto cmd_iter = gpa_cmd_lists_.cbegin(); cmd_iter != gpa_cmd_lists_.cend() && is_ready; ++cmd_iter)
        {
            is_ready &= (*cmd_iter)->IsResultReady();
        }

        if (is_ready)
        {
            is_result_ready_ = true;
        }
    }

    return is_ready;
}

bool GpaPass::IsResultCollected() const
{
    return is_result_collected_;
}

GpaStatus GpaPass::GetResult(ClientSampleId client_sample_id, CounterIndex internal_counter_index, GpaUInt64* result_buffer) const
{
    *result_buffer = 0;

    std::lock_guard<std::mutex> lock(samples_unordered_map_mutex_);

    GpaStatus                  status      = kGpaStatusOk;
    SamplesMap::const_iterator sample_iter = samples_unordered_map_.find(client_sample_id);

    if (sample_iter == samples_unordered_map_.cend())
    {
        GPA_LOG_ERROR("Invalid SampleId supplied while getting pass results.");
        status = kGpaStatusErrorInvalidParameter;
    }
    else
    {
        CounterIndex counter_index_within_sample;

        if (GetCounterIndexInPass(internal_counter_index, &counter_index_within_sample))
        {
            if (!sample_iter->second->GetResult(counter_index_within_sample, result_buffer))
            {
                GPA_LOG_ERROR("Failed to get counter result within pass.");
                status = kGpaStatusErrorFailed;
            }
        }
        else if (skipped_counter_list_.find(internal_counter_index) == skipped_counter_list_.end())
        {
            // We didn't skip the counter, so we wrongly think it was in this pass.
            GPA_LOG_ERROR("Failed to find internal counter index within pass counters.");
            status = kGpaStatusErrorInvalidParameter;
        }
    }

    return status;
}

bool GpaPass::DoesSampleExist(ClientSampleId client_sample_id) const
{
    std::lock_guard<std::mutex> lock(samples_unordered_map_mutex_);
    return DoesSampleExistNotThreadSafe(client_sample_id);
}

bool GpaPass::DoesSampleExistNotThreadSafe(ClientSampleId client_sample_id) const
{
    bool exists = false;

    if (samples_unordered_map_.find(client_sample_id) != samples_unordered_map_.end())
    {
        exists = true;
    }

    return exists;
}

bool GpaPass::DoesCommandListExist(IGpaCommandList* gpa_cmd_list) const
{
    bool exists = false;

    std::lock_guard<std::mutex> lock(gpa_cmd_list_mutex_);

    for (auto const_iter = gpa_cmd_lists_.cbegin(); !exists && const_iter != gpa_cmd_lists_.cend(); ++const_iter)
    {
        if (*const_iter == gpa_cmd_list)
        {
            exists = true;
        }
    }

    return exists;
}

const GpaCommandLists& GpaPass::GetCmdList() const
{
    return gpa_cmd_lists_;
}

void GpaPass::EnableCounterForPass(const CounterIndex& counter_index)
{
    std::lock_guard<std::mutex> lock_pass(counter_list_mutex_);
    used_counter_list_for_pass_.push_back(counter_index);
}

void GpaPass::DisableCounterForPass(const CounterIndex& counter_index)
{
    std::lock_guard<std::mutex> lock_pass(counter_list_mutex_);
    skipped_counter_list_.insert(counter_index);
}

void GpaPass::EnableAllCountersForPass()
{
    std::lock_guard<std::mutex> lock_pass(counter_list_mutex_);
    used_counter_list_for_pass_ = *counter_list_;
    skipped_counter_list_.clear();
}

void GpaPass::DisableAllCountersForPass()
{
    std::lock_guard<std::mutex> lock_pass(counter_list_mutex_);
    skipped_counter_list_.clear();
    skipped_counter_list_.insert(counter_list_->begin(), counter_list_->end());
    used_counter_list_for_pass_.clear();
}

CounterCount GpaPass::GetNumEnabledCountersForPass() const
{
    std::lock_guard<std::mutex> lock_pass(counter_list_mutex_);
    return static_cast<CounterCount>(counter_list_->size() - skipped_counter_list_.size());
}

bool GpaPass::GetCounterIndexInPass(CounterIndex internal_counter_index, CounterIndex* counter_indices_in_pass) const
{
    bool found = false;
    if (!used_counter_list_for_pass_.empty())
    {
        CounterList::const_iterator iter = std::find(used_counter_list_for_pass_.begin(), used_counter_list_for_pass_.end(), internal_counter_index);

        if (used_counter_list_for_pass_.end() != iter)
        {
            *counter_indices_in_pass = static_cast<CounterIndex>(iter - used_counter_list_for_pass_.begin());
            found                    = true;
        }
    }

    return found;
}

bool GpaPass::GetCounterByIndexInPass(CounterIndex counter_index_in_pass, CounterIndex* internal_counter_index) const
{
    if (!internal_counter_index)
    {
        assert(0);
        return false;
    }

    bool found              = counter_index_in_pass < used_counter_list_for_pass_.size();
    *internal_counter_index = static_cast<CounterIndex>(-1);

    if (found)
    {
        *internal_counter_index = used_counter_list_for_pass_[counter_index_in_pass];
    }

    return found;
}

bool GpaPass::IsResultsCollectedFromDriver() const
{
    return is_result_collected_;
}

const IGpaCounterAccessor* GpaPass::GetSessionContextCounterAccessor() const
{
    return GpaContextCounterMediator::GetCounterAccessor(GetGpaSession());
}

void GpaPass::AddCommandList(IGpaCommandList* gpa_command_list)
{
    std::lock_guard<std::mutex> lock_cmd_list(gpa_cmd_list_mutex_);
    gpa_cmd_lists_.push_back(gpa_command_list);
}

void GpaPass::LockCommandListMutex() const
{
    gpa_cmd_list_mutex_.lock();
}

void GpaPass::UnlockCommandListMutex() const
{
    gpa_cmd_list_mutex_.unlock();
}

void GpaPass::AddClientSample(ClientSampleId sample_id, GpaSample* gpa_sample)
{
    samples_unordered_map_mutex_.lock();
    samples_unordered_map_.insert(std::pair<ClientSampleId, GpaSample*>(sample_id, gpa_sample));
    unsigned int internal_sample_id = gpa_internal_sample_counter_.fetch_add(1);
    client_gpa_samples_map_.insert(std::pair<unsigned int, unsigned int>(internal_sample_id, sample_id));
    samples_unordered_map_mutex_.unlock();
}

void GpaPass::IteratePassCounterList(const std::function<bool(const CounterIndex& counter_index)>& function) const
{
    bool next = true;

    for (auto it = (*counter_list_).cbegin(); it != (*counter_list_).cend() && next; ++it)
    {
        next = function(*it);
    }
}

void GpaPass::IterateEnabledCounterList(const std::function<bool(const CounterIndex& counter_index)>& function) const
{
    bool next = true;

    for (auto it = used_counter_list_for_pass_.cbegin(); it != used_counter_list_for_pass_.cend() && next; ++it)
    {
        next = function(*it);
    }
}

void GpaPass::IterateSkippedCounterList(const std::function<bool(const CounterIndex& counter_index)>& function) const
{
    bool next = true;

    for (auto it = skipped_counter_list_.cbegin(); it != skipped_counter_list_.cend() && next; ++it)
    {
        next = function(*it);
    }
}

bool GpaPass::FindBottomToBottomTimingDurationCounter() const
{
    const IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::GetCounterAccessor(GetGpaSession());
    assert(counter_accessor != nullptr);
    if (counter_accessor == nullptr)
    {
        return false;
    }

    const GpaHardwareCounters& hardware_counters = counter_accessor->GetHardwareCounters();

    const auto it = std::find(counter_list_->begin(), counter_list_->end(), hardware_counters.gpu_time_bottom_to_bottom_duration_counter_index_);
    const bool found = (it != counter_list_->end());

    return found;
}

bool GpaPass::FindTopToBottomTimingDurationCounter() const
{
    const IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::GetCounterAccessor(GetGpaSession());
    assert(counter_accessor != nullptr);
    if (counter_accessor == nullptr)
    {
        return false;
    }

    const GpaHardwareCounters& hardware_counters = counter_accessor->GetHardwareCounters();

    const auto it = std::find(counter_list_->begin(), counter_list_->end(), hardware_counters.gpu_time_top_to_bottom_duration_counter_index_);
    const bool found = (it != counter_list_->end());

    return found;
}

IGpaSession* GpaPass::GetGpaSession() const
{
    return gpa_session_;
}
