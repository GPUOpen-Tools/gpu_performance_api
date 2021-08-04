//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA Command List Implementation.
//==============================================================================

#include "gpu_perf_api_common/gpa_command_list.h"

GpaCommandList::GpaCommandList(IGpaSession* gpa_session, GpaPass* gpa_pass, CommandListId command_list_id, GpaCommandListType command_list_type)
    : gpa_session_(gpa_session)
    , gpa_pass_(gpa_pass)
    , last_sample_(nullptr)
    , command_list_state_(CommandListState::kUndefined)
    , command_list_type_(command_list_type)
    , command_list_id_(command_list_id)
{
}

IGpaSession* GpaCommandList::GetParentSession() const
{
    return gpa_session_;
}

bool GpaCommandList::Begin()
{
    bool success = false;

    if (CommandListState::kUndefined == command_list_state_)
    {
        cmd_list_mutex_.lock();
        command_list_state_ = CommandListState::kSampleRecordingBegin;
        last_sample_        = nullptr;
        cmd_list_mutex_.unlock();
        success = BeginCommandListRequest();

        if (!success)
        {
            GPA_LOG_ERROR("Failed to begin the command list.");
        }
    }
    else
    {
        GPA_LOG_ERROR("Command list is already running.");
    }

    return success;
}

bool GpaCommandList::End()
{
    bool success = false;

    if (CommandListState::kUndefined == command_list_state_)
    {
        GPA_LOG_ERROR("Command list is not yet opened for sampling.");
    }
    else if (CommandListState::kSampleRecordingEnd == command_list_state_)
    {
        GPA_LOG_ERROR("Command List already ended.");
    }
    else if (CommandListState::kSampleRecordingBegin == command_list_state_)
    {
        // Close any outstanding opened sample.
        if (nullptr != last_sample_)
        {
            if (!CloseLastSample(false))
            {
                GPA_LOG_ERROR("Unable to close the last sample.");
            }
        }

        success = EndCommandListRequest();

        if (!success)
        {
            GPA_LOG_ERROR("Unable to end the command list.");
        }
        else
        {
            cmd_list_mutex_.lock();
            command_list_state_ = CommandListState::kSampleRecordingEnd;
            cmd_list_mutex_.unlock();
        }
    }

    return success;
}

bool GpaCommandList::IsCommandListRunning() const
{
    return CommandListState::kSampleRecordingBegin == command_list_state_;
}

GpaPass* GpaCommandList::GetPass() const
{
    return gpa_pass_;
}

GpaUInt32 GpaCommandList::GetSampleCount() const
{
    std::lock_guard<std::mutex> lock_cmd_list(cmd_list_mutex_);
    return static_cast<GpaUInt32>(client_sample_id_to_gpa_sample_id_umap_.size());
}

bool GpaCommandList::BeginSample(ClientSampleId client_sample_index, GpaSample* sample)
{
    bool succeeded = false;

    if (CommandListState::kSampleRecordingBegin != command_list_state_)
    {
        GPA_LOG_ERROR("Command list must be in recording state to start/end a sample.");
    }
    else if (nullptr != GetSample(client_sample_index))
    {
        GPA_LOG_ERROR("Sample Id already exists.");
    }
    else if (nullptr != last_sample_)
    {
        GPA_LOG_ERROR("Previous sample must be ended before starting a new one.");
    }
    else
    {
        if (nullptr != sample)
        {
            succeeded = BeginSampleRequest(client_sample_index, sample);

            if (succeeded)
            {
                succeeded = sample->Begin();

                if (succeeded)
                {
                    cmd_list_mutex_.lock();
                    last_sample_ = sample;
                    cmd_list_mutex_.unlock();
                    AddSample(client_sample_index, sample);
                }
            }
            else
            {
                GPA_LOG_ERROR("Failed to begin sample on command list.");
            }
        }
    }

    return succeeded;
}

bool GpaCommandList::CloseLastSample(bool closing_by_client)
{
    bool succeeded = false;

    if (CommandListState::kSampleRecordingBegin != command_list_state_)
    {
        GPA_LOG_ERROR("Command list must be in recording state to start/end a sample.");
    }
    else if (nullptr == last_sample_)
    {
        GPA_LOG_ERROR("Sample must be started before ending one.");
    }
    else
    {
        succeeded = CloseLastSampleRequest();

        if (!succeeded)
        {
            GPA_LOG_ERROR("Unable to end the sample on command list.");
        }
        else
        {
            succeeded = last_sample_->End();

            if (!succeeded)
            {
                GPA_LOG_ERROR("Unable to end the sample.");
            }
            else
            {
                cmd_list_mutex_.lock();

                if (closing_by_client)
                {
                    succeeded = last_sample_->SetAsClosedByClient();
                }

                last_sample_ = nullptr;
                cmd_list_mutex_.unlock();
            }
        }
    }

    return succeeded;
}

GpaSample* GpaCommandList::GetLastSample() const
{
    return last_sample_;
}

GpaSample* GpaCommandList::GetSample(ClientSampleId client_sample_id) const
{
    std::lock_guard<std::mutex> lock_cmd_list(cmd_list_mutex_);

    GpaSample* ret_gpa_sample = nullptr;

    ClientSampleIdGpaSampleUnorderedMap::const_iterator iter = client_sample_id_to_gpa_sample_id_umap_.find(client_sample_id);

    if (iter != client_sample_id_to_gpa_sample_id_umap_.end())
    {
        ret_gpa_sample = iter->second;
    }

    return ret_gpa_sample;
}

bool GpaCommandList::IsLastSampleClosed() const
{
    return nullptr == last_sample_;
}

bool GpaCommandList::IsResultReady() const
{
    return true;
}

GpaCommandListType GpaCommandList::GetCmdType() const
{
    return command_list_type_;
}

GpaObjectType GpaCommandList::ObjectType() const
{
    return GpaObjectType::kGpaObjectTypeCommandList;
}

CommandListId GpaCommandList::GetId() const
{
    return command_list_id_;
}

void GpaCommandList::IterateSampleUnorderedMap(std::function<bool(ClientSampleIdGpaSamplePair)> function) const
{
    bool next = true;

    for (auto it = client_sample_id_to_gpa_sample_id_umap_.cbegin(); it != client_sample_id_to_gpa_sample_id_umap_.cend() && next; ++it)
    {
        next = function(*it);
    }
}

void GpaCommandList::AddSample(ClientSampleId client_sample_id, GpaSample* gpa_sample)
{
    std::lock_guard<std::mutex> lock_cmd_list(cmd_list_mutex_);
    client_sample_id_to_gpa_sample_id_umap_.insert(ClientSampleIdGpaSamplePair(client_sample_id, gpa_sample));
}
