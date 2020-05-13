//==============================================================================
// Copyright (c) 2017-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GPA Command List Implementation
//==============================================================================

#include "gpa_command_list.h"

GPACommandList::GPACommandList(IGPASession* pGpaSession, GPAPass* pGpaPass, CommandListId commandListId, GPA_Command_List_Type commandListType)
    : m_pGpaSession(pGpaSession)
    , m_pGpaPass(pGpaPass)
    , m_pLastSample(nullptr)
    , m_commandListState(CommandListState::UNDEFINED)
    , m_commandListType(commandListType)
    , m_commandListId(commandListId)
{
}

IGPASession* GPACommandList::GetParentSession() const
{
    return m_pGpaSession;
}

bool GPACommandList::Begin()
{
    bool success = false;

    if (CommandListState::UNDEFINED == m_commandListState)
    {
        m_cmdListMutex.lock();
        m_commandListState = CommandListState::SAMPLE_RECORDING_BEGIN;
        m_pLastSample      = nullptr;
        m_cmdListMutex.unlock();
        success = BeginCommandListRequest();

        if (!success)
        {
            GPA_LogError("Failed to begin the command list.");
        }
    }
    else
    {
        GPA_LogError("Command list is already running.");
    }

    return success;
}

bool GPACommandList::End()
{
    bool success = false;

    if (CommandListState::UNDEFINED == m_commandListState)
    {
        GPA_LogError("Command list is not yet opened for sampling.");
    }
    else if (CommandListState::SAMPLE_RECORDING_END == m_commandListState)
    {
        GPA_LogError("Command List already ended.");
    }
    else if (CommandListState::SAMPLE_RECORDING_BEGIN == m_commandListState)
    {
        // Close any outstanding opened sample
        if (nullptr != m_pLastSample)
        {
            if (!CloseLastSample(false))
            {
                GPA_LogError("Unable to close the last sample.");
            }
        }

        success = EndCommandListRequest();

        if (!success)
        {
            GPA_LogError("Unable to end the command list.");
        }
        else
        {
            m_cmdListMutex.lock();
            m_commandListState = CommandListState::SAMPLE_RECORDING_END;
            m_cmdListMutex.unlock();
        }
    }

    return success;
}

bool GPACommandList::IsCommandListRunning() const
{
    return CommandListState::SAMPLE_RECORDING_BEGIN == m_commandListState;
}

GPAPass* GPACommandList::GetPass() const
{
    return m_pGpaPass;
}

gpa_uint32 GPACommandList::GetSampleCount() const
{
    std::lock_guard<std::mutex> lockCmdList(m_cmdListMutex);
    return static_cast<gpa_uint32>(m_clientSampleIdGpaSampleUnorderedMap.size());
}

bool GPACommandList::BeginSample(ClientSampleId clientSampleIndex, GPASample* pSample)
{
    bool succeeded = false;

    if (CommandListState::SAMPLE_RECORDING_BEGIN != m_commandListState)
    {
        GPA_LogError("Command list must be in recording state to start/end a sample.");
    }
    else if (nullptr != GetSample(clientSampleIndex))
    {
        GPA_LogError("Sample Id already exists.");
    }
    else if (nullptr != m_pLastSample)
    {
        GPA_LogError("Previous sample must be ended before starting a new one.");
    }
    else
    {
        if (nullptr != pSample)
        {
            succeeded = BeginSampleRequest(clientSampleIndex, pSample);

            if (succeeded)
            {
                succeeded = pSample->Begin();

                if (succeeded)
                {
                    m_cmdListMutex.lock();
                    m_pLastSample = pSample;
                    m_cmdListMutex.unlock();
                    AddSample(clientSampleIndex, pSample);
                }
            }
            else
            {
                GPA_LogError("Failed to begin sample on command list.");
            }
        }
    }

    return succeeded;
}

bool GPACommandList::CloseLastSample(bool closingByClient)
{
    bool succeeded = false;

    if (CommandListState::SAMPLE_RECORDING_BEGIN != m_commandListState)
    {
        GPA_LogError("Command list must be in recording state to start/end a sample.");
    }
    else if (nullptr == m_pLastSample)
    {
        GPA_LogError("Sample must be started before ending one.");
    }
    else
    {
        succeeded = CloseLastSampleRequest();

        if (!succeeded)
        {
            GPA_LogError("Unable to end the sample on command list.");
        }
        else
        {
            succeeded = m_pLastSample->End();

            if (!succeeded)
            {
                GPA_LogError("Unable to end the sample.");
            }
            else
            {
                m_cmdListMutex.lock();

                if (closingByClient)
                {
                    succeeded = m_pLastSample->SetAsClosedByClient();
                }

                m_pLastSample = nullptr;
                m_cmdListMutex.unlock();
            }
        }
    }

    return succeeded;
}

GPASample* GPACommandList::GetLastSample() const
{
    return m_pLastSample;
}

GPASample* GPACommandList::GetSample(ClientSampleId clientSampleId) const
{
    std::lock_guard<std::mutex> lockCmdList(m_cmdListMutex);

    GPASample* pRetGpaSample = nullptr;

    ClientSampleIdGpaSampleUnorderedMap::const_iterator iter = m_clientSampleIdGpaSampleUnorderedMap.find(clientSampleId);

    if (iter != m_clientSampleIdGpaSampleUnorderedMap.end())
    {
        pRetGpaSample = iter->second;
    }

    return pRetGpaSample;
}

bool GPACommandList::IsLastSampleClosed() const
{
    return nullptr == m_pLastSample;
}

bool GPACommandList::IsResultReady() const
{
    return true;
}

GPA_Command_List_Type GPACommandList::GetCmdType() const
{
    return m_commandListType;
}

GPAObjectType GPACommandList::ObjectType() const
{
    return GPAObjectType::GPA_OBJECT_TYPE_COMMAND_LIST;
}

CommandListId GPACommandList::GetId() const
{
    return m_commandListId;
}

void GPACommandList::IterateSampleUnorderedMap(std::function<bool(ClientSampleIdGpaSamplePair)> function) const
{
    bool next = true;

    for (auto it = m_clientSampleIdGpaSampleUnorderedMap.cbegin(); it != m_clientSampleIdGpaSampleUnorderedMap.cend() && next; ++it)
    {
        next = function(*it);
    }
}

void GPACommandList::AddSample(ClientSampleId clientSampleId, GPASample* pGpaSample)
{
    std::lock_guard<std::mutex> lockCmdList(m_cmdListMutex);
    m_clientSampleIdGpaSampleUnorderedMap.insert(ClientSampleIdGpaSamplePair(clientSampleId, pGpaSample));
}
