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

// TODO: Implement HSA_PreDispatchCallback
/// Pre-dispatch callback function
/// \param pRTParam the pre-dispatch callback params
/// \param pUserArgs the user arguments
void HSA_PreDispatchCallback(const hsa_dispatch_callback_t* pRTParam, void* pUserArgs)
{
    assert(nullptr != pRTParam && true == pRTParam->pre_dispatch);

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
            UNREFERENCED_PARAMETER(pRTParam);
            //GPA_ContextStateHSA* pContextState = getCurrentContext();

            //if (nullptr != pContextState)
            //{
            //    pContextState->m_pAqlTranslationHandle = pRTParam->aql_translation_handle;

            //    if (pContextState->m_currentPass > 0)
            //    {
            //        // issue request for counter data
            //        GPA_DataRequest* pRequest = pContextState->GetDataRequest(g_pCurrentContext->m_currentPass - 1);

            //        if (nullptr != pRequest)
            //        {
            //            pRequest->SetSampleID(HSAGlobalFlags::Instance()->m_sampleID);

            //            bool requestOk = pRequest->Begin(pContextState, nullptr, pContextState->m_selectionID, pContextState->m_pCounterScheduler->GetCountersForPass(pContextState->m_currentPass - 1));

            //            if (!requestOk)
            //            {
            //                GPA_LogError("Failed to begin request.");
            //                return;
            //            }

            //            // add new request to current session requests list
            //            g_pCurrentContext->m_pCurrentSessionRequests->Begin(pContextState->m_currentPass - 1, HSAGlobalFlags::Instance()->m_sampleID, pRequest);
            //        }
            //        else
            //        {
            //            GPA_LogError("Failed to get data request.");
            //        }
            //    }
            //}
        }
    }
}

// TODO: Implement HSA_PostDispatchCallback
/// Post-dispatch callback function
/// \param pRTParam the post-dispatch callback params
/// \param pUserArgs the user arguments
void HSA_PostDispatchCallback(const hsa_dispatch_callback_t* pRTParam, void* pUserArgs)
{
    UNREFERENCED_PARAMETER(pRTParam);

    assert(nullptr != pRTParam && false == pRTParam->pre_dispatch);

    HSAGPAContext* pContext = reinterpret_cast<HSAGPAContext*>(pUserArgs);

    if (nullptr != pContext)
    {
        //if (g_pCurrentContext->m_currentPass > 0)
        //{
        //    bool endedOk = g_pCurrentContext->m_pCurrentSessionRequests->End(g_pCurrentContext->m_currentPass - 1, g_pCurrentContext->m_currentSample);

        //    if (!endedOk)
        //    {
        //        GPA_LogError("Failed to end request.");
        //        return;
        //    }
        //}
    }
}


HSAGPAContext::HSAGPAContext(GPA_HWInfo& pHwInfo,
                             GPA_OpenContextFlags contextFlags) :
                             GPAContext(pHwInfo, contextFlags),
                             m_hsaPmu(nullptr)
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

GPA_SessionId HSAGPAContext::CreateSession()
{
    GPA_SessionId pRetSessionId = nullptr;

    HSAGPASession* pNewGpaHSAGpaSession = new(std::nothrow) HSAGPASession(this);

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

const GPA_HSA_Context& HSAGPAContext::GetHSAContext() const
{
    return m_hsaContext;
}

const hsa_ext_tools_pmu_t HSAGPAContext::GetHSAPMU() const
{
    return m_hsaPmu;
}
