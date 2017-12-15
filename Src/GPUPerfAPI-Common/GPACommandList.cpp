//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GPA Command List Implementation
//==============================================================================

#include "GPACommandList.h"

GPACommandList::GPACommandList(IGPASession* pGpaSession, GPAPass* pGpaPass)
{
    m_pGpaSession = pGpaSession;
    m_pGpaPass = pGpaPass;
    m_isCmdRunning = false;
}

IGPASession* GPACommandList::GetParentSession() const
{
    return m_pGpaSession;
}

bool GPACommandList::Begin()
{
    bool success = false;

    if (false == m_isCmdRunning)
    {
        m_isCmdRunning = true;
        success = true;
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

    if (true == m_isCmdRunning)
    {
        m_isCmdRunning = false;
        success = true;
    }
    else
    {
        GPA_LogError("Command list is already ended.");
    }

    return success;
}

bool GPACommandList::IsCommandListRunning() const
{
    return m_isCmdRunning;
}

GPAPass* GPACommandList::GetPass() const
{
    return m_pGpaPass;
}

gpa_uint32 GPACommandList::GetSampleCount() const
{
    return 0u;
}

bool GPACommandList::BeginSample(ClientSampleId clientSampleIndex,
    GPASample* pSample,
    const std::vector<CounterIndex>* pCounterList)
{
    UNREFERENCED_PARAMETER(clientSampleIndex);
    if (nullptr != pSample)
    {
        return pSample->Begin(m_pGpaSession->GetParentContext(), pCounterList);
    }

    return false;
}

GPASample* GPACommandList::GetLastSample() const
{
    return nullptr;
}

bool GPACommandList::CloseLastSample(bool closingByClient)
{
    UNREFERENCED_PARAMETER(closingByClient);
    return true;
}

bool GPACommandList::IsLastSampleClosed() const
{
    return true;
}

bool GPACommandList::IsComplete() const
{
    return true;
}

GPA_Command_List_Type GPACommandList::GetCmdType() const
{
    return GPA_COMMAND_LIST_NONE;
}

GPAObjectType GPACommandList::ObjectType() const
{
    return GPAObjectType::GPA_OBJECT_TYPE_COMMAND_LIST;
}