//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA HSA Context Implementation
//==============================================================================

#include "HSAGPAContext.h"
#include "GPAUniqueObject.h"
#include "HSAGPAImplementor.h"
#include "HSAGPASession.h"
#include "HSARTModuleLoader.h"
#include "GPUPerfAPIHSAGlobals.h"
#include "HSAGPASample.h"


void HSA_PreDispatchCallback(const hsa_dispatch_callback_t* pRTParam, void* pUserArgs)
{
    assert(nullptr != pRTParam && pRTParam->pre_dispatch);
    UNREFERENCED_PARAMETER(pRTParam);

    // It is safe to cast user argument to HSAGPAContext as
    // we are setting pUserArgs to be HSAGPAContext while opening the context
    HSAGPAContext* pContext = reinterpret_cast<HSAGPAContext*>(pUserArgs);

    if (nullptr != pContext)
    {
        HSAToolsRTModule* pHsaToolsRTModule = HSAToolsRTModuleLoader::Instance()->GetAPIRTModule();

        if (nullptr == pHsaToolsRTModule || !pHsaToolsRTModule->IsModuleLoaded())
        {
            GPA_LogError("Unable to load HSA tools runtime module.");
        }
        else
        {
            pContext->HSAContext().m_pAgent = &pRTParam->agent;
            pContext->HSAContext().m_pAqlTranslationHandle = pRTParam->aql_translation_handle;
            bool success = pContext->GetRunningHSASample()->BeginInternalRequest();

            if (!success)
            {
                GPA_LogError("Unable to start the sample.");
            }
        }
    }
}


void HSA_PostDispatchCallback(const hsa_dispatch_callback_t* pRTParam, void* pUserArgs)
{
    UNREFERENCED_PARAMETER(pRTParam);

    assert(nullptr != pRTParam && !pRTParam->pre_dispatch);

    HSAGPAContext* pContext = reinterpret_cast<HSAGPAContext*>(pUserArgs);

    if (nullptr != pContext)
    {
        bool success = pContext->GetRunningHSASample()->EndInternalRequest();

        if (!success)
        {
            GPA_LogError("Unable to end the sample.");
        }
        else
        {
            pContext->CloseHSASample();
        }
    }
}


HSAGPAContext::HSAGPAContext(GPA_HWInfo& pHwInfo,
                             GPA_OpenContextFlags contextFlags) :
    GPAContext(pHwInfo, contextFlags),
    m_hsaPmu(nullptr),
    m_pRunningHsaSample(nullptr)
{
}

HSAGPAContext::~HSAGPAContext()
{
    if (nullptr != m_hsaPmu)
    {
        hsa_status_t status = HSAToolsRTModuleLoader::Instance()->GetAPIRTModule()->ext_tools_release_pmu(m_hsaPmu);

        if (HSA_STATUS_SUCCESS != status)
        {
            GPA_LogError("Error when deleting pmu object.");
        }
    }

    if (HSAGlobalFlags::Instance()->m_softCPModeEnabled)
    {
        hsa_status_t status = HSAToolsRTModuleLoader::Instance()->GetAPIRTModule()->ext_tools_set_callback_functions(const_cast<hsa_queue_t*>(m_hsaContext.m_pQueue), nullptr, nullptr);

        if (HSA_STATUS_SUCCESS != status)
        {
            GPA_LogError("Unable to remove dispatch callback functions.");
        }
    }
}

GPA_SessionId HSAGPAContext::CreateSession(GPA_Session_Sample_Type sampleType)
{
    GPA_SessionId pRetSessionId = nullptr;

    HSAGPASession* pNewGpaHSAGpaSession = new(std::nothrow) HSAGPASession(this, sampleType);

    if (nullptr == pNewGpaHSAGpaSession)
    {
        GPA_LogError("Unable to allocate memory for the session.");
    }
    else
    {
        AddGpaSession(pNewGpaHSAGpaSession);

        if (nullptr != pNewGpaHSAGpaSession)
        {
            pRetSessionId = reinterpret_cast<GPA_SessionId>(GPAUniqueObjectManager::Instance()->CreateObject(pNewGpaHSAGpaSession));
        }
    }

    return pRetSessionId;
}

bool HSAGPAContext::DeleteSession(GPA_SessionId sessionId)
{
    bool isDeleted = false;

    HSAGPASession* pHSASession = reinterpret_cast<HSAGPASession*>(sessionId->Object());

    if (nullptr != pHSASession)
    {
        RemoveGpaSession(pHSASession);
        GPAUniqueObjectManager::Instance()->DeleteObject(pHSASession);
        delete pHSASession;
        isDeleted = true;
    }

    return isDeleted;
}

gpa_uint32 HSAGPAContext::GetMaxGPASessions() const
{
    // maximum latency is 4 for dx10-capable cards
    return 4;
}

GPA_API_Type HSAGPAContext::GetAPIType() const
{
    return GPA_API_HSA;
}

bool HSAGPAContext::OpenCounters()
{
    bool retVal = GPAContext::OpenCounters();

    if (retVal)
    {
        HSAToolsRTModule* pHsaToolsRTModule = HSAToolsRTModuleLoader::Instance()->GetAPIRTModule();

        if (nullptr == pHsaToolsRTModule || !pHsaToolsRTModule->IsModuleLoaded())
        {
            GPA_LogError("Unable to load HSA tools runtime module.");
            retVal = false;
        }
        else
        {
            bool isOk = true;
            hsa_status_t status;

            if (HSAGlobalFlags::Instance()->m_softCPModeEnabled)
            {
                status = pHsaToolsRTModule->ext_tools_set_callback_functions(const_cast<hsa_queue_t*>(m_hsaContext.m_pQueue), HSA_PreDispatchCallback, HSA_PostDispatchCallback);

                if (HSA_STATUS_SUCCESS != status)
                {
                    GPA_LogError("Unable to set dispatch callback functions.");
                    isOk = false;
                }
                else
                {
                    status = pHsaToolsRTModule->ext_tools_set_callback_arguments(const_cast<hsa_queue_t*>(m_hsaContext.m_pQueue), this, this);

                    if (HSA_STATUS_SUCCESS != status)
                    {
                        GPA_LogError("Unable to set dispatch callback arguments.");
                        isOk = false;
                    }
                }
            }

            if (isOk)
            {
                status = pHsaToolsRTModule->ext_tools_create_pmu(*m_hsaContext.m_pAgent, &m_hsaPmu);

                if (HSA_STATUS_SUCCESS != status)
                {
                    GPA_LogError("Cannot create pmu object.");
                    retVal = false;
                }
            }
        }
    }

    return retVal;
}


bool HSAGPAContext::Initialize(GPA_HSA_Context* pHsaContext)
{
    bool success = false;

    if (nullptr == pHsaContext)
    {
        GPA_LogError("Invalid HSA Context.");
    }
    else
    {
        memcpy(&m_hsaContext, pHsaContext, sizeof(m_hsaContext));

        success = OpenCounters();

        if (success)
        {
            SetAsOpened(true);
        }
    }

    return success;
}

GPA_HSA_Context& HSAGPAContext::HSAContext()
{
    return m_hsaContext;
}

const hsa_ext_tools_pmu_t HSAGPAContext::GetHSAPMU() const
{
    return m_hsaPmu;
}

HSAGPASample* HSAGPAContext::GetRunningHSASample() const
{
    return m_pRunningHsaSample;
}

bool HSAGPAContext::SetRunningHSASample(HSAGPASample* pRunningHsaSample)
{
    bool success = false;

    if (nullptr == m_pRunningHsaSample)
    {
        if (nullptr != pRunningHsaSample)
        {
            m_pRunningHsaSample = pRunningHsaSample;
            success = true;
        }
    }

    return success;
}

void HSAGPAContext::CloseHSASample()
{
    m_pRunningHsaSample = nullptr;
}
