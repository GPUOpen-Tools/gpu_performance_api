//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA CL Context Implementation
//==============================================================================

#include "CLGPAContext.h"
#include "GPAUniqueObject.h"
#include "CLGPAImplementor.h"
#include "CLGPASession.h"

CLGPAContext::CLGPAContext(cl_command_queue& clCommandQueue,
                           GPA_HWInfo& hwInfo,
                           GPA_OpenContextFlags contextFlags) :
    GPAContext(hwInfo, contextFlags),
    m_clCommandQueue(clCommandQueue),
    m_clDeviceId(nullptr)
{
}

GPA_SessionId CLGPAContext::CreateSession(GPA_Session_Sample_Type sampleType)
{
    GPA_SessionId pRetSessionId = nullptr;

    CLGPASession* pNewGpaCLGpaSession = new(std::nothrow) CLGPASession(this, sampleType);

    if (nullptr == pNewGpaCLGpaSession)
    {
        GPA_LogError("Unable to allocate memory for the session.");
    }
    else
    {
        AddGpaSession(pNewGpaCLGpaSession);

        if (nullptr != pNewGpaCLGpaSession)
        {
            pRetSessionId = reinterpret_cast<GPA_SessionId>(GPAUniqueObjectManager::Instance()->CreateObject(pNewGpaCLGpaSession));
        }
    }

    return pRetSessionId;
}

bool CLGPAContext::DeleteSession(GPA_SessionId sessionId)
{
    bool isDeleted = false;

    CLGPASession* pCLSession = reinterpret_cast<CLGPASession*>(sessionId->Object());

    if (nullptr != pCLSession)
    {
        RemoveGpaSession(pCLSession);
        GPAUniqueObjectManager::Instance()->DeleteObject(pCLSession);
        delete pCLSession;
        isDeleted = true;
    }

    return isDeleted;
}

gpa_uint32 CLGPAContext::GetMaxGPASessions() const
{
    // maximum latency is 4 for dx10-capable cards
    return 4;
}

GPA_API_Type CLGPAContext::GetAPIType() const
{
    return GPA_API_OPENCL;
}

bool CLGPAContext::Initialize(cl_device_id& clDeviceId)
{
    m_clDeviceId = clDeviceId;

    bool success = OpenCounters();

    if (success)
    {
        SetAsOpened(true);
    }

    return success;
}

const cl_device_id& CLGPAContext::GetCLDeviceId() const
{
    return m_clDeviceId;
}

const cl_command_queue& CLGPAContext::GetCLCommandQueue() const
{
    return m_clCommandQueue;
}

