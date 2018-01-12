//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GPA Command List Implementation
//==============================================================================

#include "GPACommandList.h"

GPACommandList::GPACommandList(IGPASession* pGpaSession, GPAPass* pGpaPass):
    m_pLastSample(nullptr)
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

    if (!m_isCmdRunning)
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

    if (m_isCmdRunning)
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
    bool retVal = false;

    UNREFERENCED_PARAMETER(clientSampleIndex);

    if (nullptr != pSample)
    {
        retVal = pSample->Begin(m_pGpaSession->GetParentContext(), pCounterList);

        if (retVal)
        {
            m_pLastSample = pSample;
        }
    }

    return retVal;
}

GPASample* GPACommandList::GetLastSample() const
{
    return m_pLastSample;
}

bool GPACommandList::CloseLastSample(bool closingByClient)
{
    bool retVal = false;

    UNREFERENCED_PARAMETER(closingByClient);

    if (nullptr != m_pLastSample)
    {
        retVal = m_pLastSample->End();

        if (retVal)
        {
            m_pLastSample = nullptr;
        }
    }

    return retVal;
}

bool GPACommandList::IsLastSampleClosed() const
{
    return nullptr == m_pLastSample;
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