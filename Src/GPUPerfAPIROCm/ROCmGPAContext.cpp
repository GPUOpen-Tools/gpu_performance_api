//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA ROCm Context Implementation
//==============================================================================

#include "ROCmGPAContext.h"
#include "GPAUniqueObject.h"
#include "ROCmGPAImplementor.h"
#include "ROCmGPASession.h"
#include "HSARTModuleLoader.h"
#include "GPUPerfAPIROCmGlobals.h"
#include "ROCmGPASample.h"

ROCmGPAContext::ROCmGPAContext(GPA_HWInfo& pHwInfo, GPA_OpenContextFlags contextFlags)
    : GPAContext(pHwInfo, contextFlags)
    , m_pRunningROCmSample(nullptr)
{
}

ROCmGPAContext::~ROCmGPAContext()
{
}

GPA_SessionId ROCmGPAContext::CreateSession(GPA_Session_Sample_Type sampleType)
{
    GPA_SessionId pRetSessionId = nullptr;

    ROCmGPASession* pNewGpaROCmGpaSession = new (std::nothrow) ROCmGPASession(this, sampleType);

    if (nullptr == pNewGpaROCmGpaSession)
    {
        GPA_LogError("Unable to allocate memory for the session.");
    }
    else
    {
        AddGpaSession(pNewGpaROCmGpaSession);

        if (nullptr != pNewGpaROCmGpaSession)
        {
            pRetSessionId = reinterpret_cast<GPA_SessionId>(GPAUniqueObjectManager::Instance()->CreateObject(pNewGpaROCmGpaSession));
        }
    }

    return pRetSessionId;
}

bool ROCmGPAContext::DeleteSession(GPA_SessionId sessionId)
{
    bool isDeleted = false;

    ROCmGPASession* pROCmSession = reinterpret_cast<ROCmGPASession*>(sessionId->Object());

    if (nullptr != pROCmSession)
    {
        RemoveGpaSession(pROCmSession);
        GPAUniqueObjectManager::Instance()->DeleteObject(pROCmSession);
        delete pROCmSession;
        isDeleted = true;
    }

    return isDeleted;
}

gpa_uint32 ROCmGPAContext::GetMaxGPASessions() const
{
    // maximum latency is 4 for dx10-capable cards
    return 4;
}

GPA_API_Type ROCmGPAContext::GetAPIType() const
{
    return GPA_API_ROCM;
}

bool ROCmGPAContext::OpenCounters()
{
    bool retVal = GPAContext::OpenCounters();

    return retVal;
}

bool ROCmGPAContext::Initialize(GPA_ROCm_Context* pROCmContext)
{
    bool success = false;

    if (nullptr == pROCmContext)
    {
        GPA_LogError("Invalid ROCm Context.");
    }
    else
    {
        memcpy(&m_rocmContext, pROCmContext, sizeof(m_rocmContext));

        success = OpenCounters();

        if (success)
        {
            SetAsOpened(true);
        }
    }

    return success;
}

GPA_ROCm_Context& ROCmGPAContext::ROCmContext()
{
    return m_rocmContext;
}

ROCmGPASample* ROCmGPAContext::GetRunningROCmSample() const
{
    return m_pRunningROCmSample;
}

bool ROCmGPAContext::SetRunningROCmSample(ROCmGPASample* pRunningROCmSample)
{
    bool success = false;

    if (nullptr == m_pRunningROCmSample)
    {
        if (nullptr != pRunningROCmSample)
        {
            m_pRunningROCmSample = pRunningROCmSample;
            success              = true;
        }
    }

    return success;
}

void ROCmGPAContext::CloseROCmSample()
{
    m_pRunningROCmSample = nullptr;
}
