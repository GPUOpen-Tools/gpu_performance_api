//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief A base-class implementation of the GPA Session interface
//==============================================================================

// std
#include <list>
#include <sstream>
#include <chrono>
#include <thread>

// GPA Common
#include "GPASession.h"
#include "GPAUniqueObject.h"
#include "IGPACommandList.h"
#include "GPASplitCountersInterfaces.h"
#include "GPAPass.h"
#include "GPUPerfAPITypes.h"

GPASession::GPASession(IGPAContext* pParentContext, IGPACounterScheduler* pCounterScheduler):
    m_state(GPA_SESSION_STATE_NOT_STARTED),
    m_pCounterScheduler(pCounterScheduler),
    m_pParentContext(pParentContext),
    m_maxPassIndex(0u)
{
    TRACE_PRIVATE_FUNCTION(GPASession::CONSTRUCTOR);
}

GPASession::~GPASession()
{
    TRACE_PRIVATE_FUNCTION(GPASession::DESTRUCTOR);

    std::lock_guard<std::mutex> lockResources(m_gpaSessionMutex);

    // clean up the passes
    for (auto passIter = m_passes.begin(); passIter != m_passes.end(); ++passIter)
    {
        const GPACommandLists passCmdList = (*passIter)->GetCmdList();

        for (auto cmdListIter = passCmdList.cbegin(); cmdListIter != passCmdList.cend(); ++cmdListIter)
        {
            GPAUniqueObjectManager::Instance()->DeleteObject(*cmdListIter);
        }

        delete *passIter;
    }

    m_passes.clear();
}

GPAObjectType GPASession::ObjectType() const
{
    return GPAObjectType::GPA_OBJECT_TYPE_SESSION;
}

IGPAContext* GPASession::GetParentContext() const
{
    return m_pParentContext;
}

GPASessionState GPASession::GetState() const
{
    return m_state;
}

GPA_Status GPASession::EnableCounter(gpa_uint32 index)
{
    if (IsSessionRunning())
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    return (m_pCounterScheduler == nullptr) ? GPA_STATUS_ERROR_FAILED : m_pCounterScheduler->EnableCounter(index);
}

GPA_Status GPASession::DisableCounter(gpa_uint32 index)
{
    if (IsSessionRunning())
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    return (m_pCounterScheduler == nullptr) ? GPA_STATUS_ERROR_FAILED : m_pCounterScheduler->DisableCounter(index);
}

GPA_Status GPASession::DisableAllCounters()
{
    if (m_pCounterScheduler == nullptr)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    m_pCounterScheduler->DisableAllCounters();

    return GPA_STATUS_OK;
}

GPA_Status GPASession::GetNumEnabledCounters(gpa_uint32* pCount) const
{
    if (pCount == nullptr)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (m_pCounterScheduler == nullptr)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    *pCount = m_pCounterScheduler->GetNumEnabledCounters();

    return GPA_STATUS_OK;
}

GPA_Status GPASession::GetEnabledIndex(gpa_uint32 enabledNumber, gpa_uint32* pEnabledCounterIndex) const
{
    return (m_pCounterScheduler == nullptr) ? GPA_STATUS_ERROR_FAILED : m_pCounterScheduler->GetEnabledIndex(enabledNumber, pEnabledCounterIndex);
}

GPA_Status GPASession::IsCounterEnabled(gpa_uint32 counterIndex) const
{
    return (m_pCounterScheduler == nullptr) ? GPA_STATUS_ERROR_FAILED : m_pCounterScheduler->IsCounterEnabled(counterIndex);
}

GPA_Status GPASession::GetNumRequiredPasses(gpa_uint32* pNumPasses)
{
    return (m_pCounterScheduler == nullptr) ? GPA_STATUS_ERROR_FAILED : m_pCounterScheduler->GetNumRequiredPasses(pNumPasses);
}

bool GPASession::Begin()
{
    /*
    * In begin, we will validate how many counters are enabled
    * and how many passes are required for them
    * Depending on that we will pre-create passes for the Session
    */
    bool isSucceeded = false;

    if (GPA_SESSION_STATE_STARTED <= m_state)
    {
        GPA_LogError("Session is already started.");
    }
    else
    {
        if (nullptr != m_pCounterScheduler &&
            m_pCounterScheduler->GetNumEnabledCounters() > 0)
        {
            std::lock_guard<std::mutex> lockResources(m_gpaSessionMutex);
            m_state = GPA_SESSION_STATE_STARTED;
            gpa_uint32 passCount;

            if (GPA_STATUS_OK == m_pCounterScheduler->GetNumRequiredPasses(&passCount))
            {
                // assume the loop below will succeed, it will get set to false if the loop fails
                isSucceeded = true;

                for (gpa_uint32 passIndexIter = 0; passIndexIter < passCount && isSucceeded; passIndexIter++)
                {
                    GPAPass* pCurrentPass = CreateAPIPass(passIndexIter);

                    if (nullptr != pCurrentPass)
                    {
                        m_passes.push_back(pCurrentPass);
                    }
                    else
                    {
                        // Unable to create API specific pass object
                        isSucceeded = false;
                        break;
                    }
                }
            }
            else
            {
                GPA_LogError("Session failed to get number of required passes.");
            }
        }
        else
        {
            GPA_LogError("Session can't be started without any enabled counters.");
        }
    }

    return isSucceeded;
}

bool GPASession::End()
{
    bool success = false;

    if (GPA_SESSION_STATE_STARTED == m_state)
    {
        std::lock_guard<std::mutex> lockResources(m_gpaSessionMutex);

        // Check whether that sufficient command list have been created for all passes
        if (m_maxPassIndex == m_passes.size() - 1)
        {
            if (CheckWhetherPassesAreConsistent())
            {
                m_state = GPA_SESSION_STATE_ENDED_PENDING_RESULTS;
                success = true;
            }
            else
            {
                GPA_LogError("Not all passes have same number of samples.");
            }
        }
        else
        {
            GPA_LogError("Work load has not been executed for all passes.");
        }
    }
    else
    {
        GPA_LogError("Session is not started.");
    }

    return success;
}

GPA_CommandListId GPASession::CreateCommandList(gpa_uint32 passIndex, void* pCmd, GPA_Command_List_Type cmdType)
{
    GPA_CommandListId pRetCmdId = nullptr;

    // Validate
    // 1. passIndex is less than the passes required
    // 2. Check for valid command list

    std::lock_guard<std::mutex> lockResources(m_gpaSessionMutex);

    if (passIndex >= 0 &&
        passIndex < m_passes.size())
    {
        GPAPass* pTmpPass = m_passes[passIndex];

        if (nullptr != pTmpPass)
        {
            IGPACommandList* pGpaCmd = pTmpPass->CreateCommandList(pCmd, cmdType);

            if (nullptr != pGpaCmd)
            {
                pRetCmdId = reinterpret_cast<GPA_CommandListId>(GPAUniqueObjectManager::Instance()->CreateObject(pGpaCmd));
            }
        }

        if (passIndex > m_maxPassIndex)
        {
            m_maxPassIndex = passIndex;
        }
    }
    else
    {
        GPA_LogError("Invalid pass index.");
    }

    return pRetCmdId;
}

gpa_uint32 GPASession::GetSampleCount() const
{
    TRACE_PRIVATE_FUNCTION(GPASession::GetSampleCount);

    gpa_uint32 sampleCount = 0;

    // make sure there is at least one request
    if (!m_passes.empty())
    {
        std::lock_guard<std::mutex> lockResources(m_gpaSessionMutex);
        sampleCount = static_cast<gpa_uint32>(m_passes[0]->GetSampleCount());
    }

    return sampleCount;
}

bool GPASession::DoesCommandListExist(gpa_uint32 passIndex, GPA_CommandListId pCommandListId) const
{
    bool exists = false;

    if (nullptr != pCommandListId)
    {
        std::lock_guard<std::mutex> lockResources(m_gpaSessionMutex);

        if (passIndex >= 0 &&
            passIndex < m_passes.size())
        {
            GPAPass* pTmpPass = m_passes[passIndex];

            if (nullptr != pTmpPass)
            {
                exists = pTmpPass->DoesCommandListExist(pCommandListId->Object());
            }
        }
        else
        {
            GPA_LogError("Invalid pass index.");
        }
    }

    return exists;
}

bool GPASession::UpdateResults()
{
    bool areAllPassesComplete = true;

    std::lock_guard<std::mutex> lockResources(m_gpaSessionMutex);
    for (PassInfo::iterator passIter = m_passes.begin(); passIter != m_passes.end(); ++passIter)
    {
        areAllPassesComplete &= (*passIter)->UpdateResults();
    }

    if (areAllPassesComplete)
    {
        m_state = GPA_SESSION_STATE_COMPLETED;
    }

    return areAllPassesComplete;
}

bool GPASession::UpdateResults(gpa_uint32 passIndex)
{
    bool isPassComplete = false;

    if (passIndex <= m_maxPassIndex)
    {
        std::lock_guard<std::mutex> lockResources(m_gpaSessionMutex);
        isPassComplete = m_passes.at(passIndex)->UpdateResults();
    }
    else
    {
        GPA_LogError("Incorrect pass index.");
    }

    return isPassComplete;
}

bool GPASession::IsSessionRunning() const
{
    return GPA_SESSION_STATE_STARTED == m_state;
}

bool GPASession::IsComplete() const
{
    TRACE_PRIVATE_FUNCTION(GPASession::IsComplete);
    return GPA_SESSION_STATE_COMPLETED == m_state;
}

gpa_uint64 GPASession::GetPerSampleResultSizeInBytes() const
{
    gpa_uint64 sizeInBytes = 0;

    if (m_pCounterScheduler == nullptr)
    {
        GPA_LogError("Unable to GetPerSampleResultSizeInBytes, counter scheduler is invalid.");
    }
    else
    {
        sizeInBytes = sizeof(gpa_uint64) * m_pCounterScheduler->GetNumEnabledCounters();
    }

    return sizeInBytes;
}

GPA_Status GPASession::GetSampleResult(gpa_uint32 sampleId, gpa_uint64 sampleResultSizeInBytes, void* pCounterSampleResults)
{
    TRACE_PRIVATE_FUNCTION(GPASession::GetSampleResult);

    if (sampleResultSizeInBytes < GetPerSampleResultSizeInBytes())
    {
        GPA_LogError("The value of sampleResultSizeInBytes indicates that the buffer is too small to contain the results.");
        return GPA_STATUS_ERROR_FAILED;
    }

    if (nullptr == pCounterSampleResults)
    {
        GPA_LogError("pCounterSampleResults is NULL in GPASession::GetSampleResult.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    // It is not allowed to get sample results from a sample that was done on a secondary command list.
    // The app MUST call GPA_CopySecondarySamples() and supply new unique sampleIds, then they may get
    // the results from those copied samples.
    // NOTE: All the passes should have the same SampleIds, so it's safe for us to simply use pass 0 to
    // test for the sample being secondary and/or copied.
    GPASample* pFirstPassSample = m_passes[0]->GetSampleById(sampleId);
    if (nullptr != pFirstPassSample &&
        pFirstPassSample->IsSecondary() &&
        !pFirstPassSample->IsCopied())
    {
        GPA_LogError("Results cannot be queried from secondary samples");
        return GPA_STATUS_ERROR_SAMPLE_IN_SECONDARY_COMMAND_LIST;
    }

    const uint32_t timeout = 5 * 1000; // 5 second timeout
    Flush(timeout);

    // For each counter
    // Get the interal counter result locations that are needed
    // get the necessary results from each pass
    // plug them into the counter equation (where does this come from?)
    // put the result in the appropriate spot in the supplied buffer.

    gpa_uint32 numEnabled = 0;
    GetNumEnabledCounters(&numEnabled);

    for (gpa_uint32 counterIndexIter = 0; counterIndexIter < numEnabled; counterIndexIter++)
    {
        gpa_uint32 exposedCounterIndex;

        if (GPA_STATUS_OK != GetEnabledIndex(counterIndexIter, &exposedCounterIndex))
        {
            GPA_LogError("Invalid counter found while identifying enabled counter.");
            return GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE;
        }

        vector<gpa_uint64*> results;
        vector<GPA_Data_Type> types;
        vector<gpa_uint32> internalCountersRequired = m_pParentContext->GetCounterAccessor()->GetInternalCountersRequired(exposedCounterIndex);
        CounterResultLocationMap* pResultLocations = m_pCounterScheduler->GetCounterResultLocations(exposedCounterIndex);

        gpa_uint32 sourceLocalIndex = 0;
        GPACounterSource source = GPACounterSource::UNKNOWN;

        if (!m_pParentContext->GetCounterSourceLocalIndex(exposedCounterIndex, &source, &sourceLocalIndex))
        {
            GPA_LogError("Invalid counter index found while identifying counter source.");
            return GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE;
        }

        switch (source)
        {
            case GPACounterSource::PUBLIC:
            {
                size_t requiredCount = internalCountersRequired.size();
                results.reserve(requiredCount);
                types.reserve(requiredCount);

                gpa_uint64* pAllResults = new(std::nothrow) gpa_uint64[requiredCount];

                unsigned int resultIndex = 0;

                for (std::vector<gpa_uint32>::iterator requiredCounterIter = internalCountersRequired.begin(); requiredCounterIter != internalCountersRequired.end(); ++requiredCounterIter)
                {
                    gpa_uint64* pResultBuffer = &(pAllResults[resultIndex]);
                    ++resultIndex;
                    results.push_back(pResultBuffer);
                    GPA_Data_Type type = GPA_DATA_TYPE_UINT64; // all hardware counters are UINT64
                    types.push_back(type);

                    std::map<unsigned int, GPA_CounterResultLocation>::iterator resultLocationIter = pResultLocations->find(*requiredCounterIter);

                    if (resultLocationIter == pResultLocations->end())
                    {
                        GPA_LogError("Could not find required counter among the results.");
                        delete[] pAllResults;
                        return GPA_STATUS_ERROR_FAILED;
                    }

                    *pResultBuffer = m_passes[resultLocationIter->second.m_pass]->GetResult(sampleId, *requiredCounterIter);

#ifdef AMDT_INTERNAL
                    gpa_uint32 numPublicCounters = m_pParentContext->GetCounterAccessor()->GetNumPublicCounters();
                    const char* pInternalName = m_pParentContext->GetCounterAccessor()->GetCounterName(numPublicCounters + *requiredCounterIter);
                    const char* pPublicName = m_pParentContext->GetCounterAccessor()->GetCounterName(*requiredCounterIter);

                    std::stringstream message;
                    message << "Sample " << sampleId << ", pubCounter '" << pPublicName << "', iCounter: '" << pInternalName << "', [" << *requiredCounterIter << "] = ";

                    if (type == GPA_DATA_TYPE_UINT64)
                    {
                        gpa_uint64* pValue = pResultBuffer;

                        message << *pValue;
                    }
                    else if (type == GPA_DATA_TYPE_FLOAT64)
                    {
                        gpa_float64* pValue = reinterpret_cast<gpa_float64*>(pResultBuffer);

                        message << *pValue;
                    }
                    else
                    {
                        // case not covered
                        assert(false);
                    }

                    message << ".";
                    GPA_LogDebugCounterDefs(message.str().c_str());
#endif
                }

                GPA_Data_Type currentCounterType = m_pParentContext->GetCounterAccessor()->GetCounterDataType(exposedCounterIndex);

                // compute using supplied function. value order is as defined when registered
                if (GPA_DATA_TYPE_FLOAT64 == currentCounterType)
                {
                    m_pParentContext->GetCounterAccessor()->ComputePublicCounterValue(sourceLocalIndex,
                                                                                      results,
                                                                                      types,
                                                                                      reinterpret_cast<gpa_float64*>(pCounterSampleResults) + counterIndexIter,
                                                                                      m_pParentContext->GetHwInfo());
                }
                else if (GPA_DATA_TYPE_UINT64 == currentCounterType)
                {
                    m_pParentContext->GetCounterAccessor()->ComputePublicCounterValue(sourceLocalIndex,
                                                                                      results,
                                                                                      types,
                                                                                      reinterpret_cast<gpa_uint64*>(pCounterSampleResults) + counterIndexIter,
                                                                                      m_pParentContext->GetHwInfo());
                }

                delete[] pAllResults;
                break;
            }

            case GPACounterSource::HARDWARE:
            {
                gpa_uint64* pUint64Results = reinterpret_cast<gpa_uint64*>(pCounterSampleResults) + counterIndexIter;

                gpa_uint16 counterResultPass = (*pResultLocations)[sourceLocalIndex].m_pass;
                *pUint64Results = m_passes[counterResultPass]->GetResult(sampleId, internalCountersRequired[0]);
                break;
            }

            case GPACounterSource::SOFTWARE:
            {
                gpa_uint64 buf = 0;

                auto iter = pResultLocations->begin();
                gpa_uint16 counterResultPass = iter->second.m_pass;
                buf = m_passes[counterResultPass]->GetResult(sampleId, internalCountersRequired[0]);

                gpa_uint64* pUint64Results = reinterpret_cast<gpa_uint64*>(pCounterSampleResults) + counterIndexIter;

                // compute using supplied function. value order is as defined when registered
                m_pParentContext->GetCounterAccessor()->ComputeSWCounterValue(sourceLocalIndex, buf, pUint64Results, m_pParentContext->GetHwInfo());
                break;
            }

            case GPACounterSource::UNKNOWN: break;

            default: ;
        }
    }

    return GPA_STATUS_OK;
}

IGPACounterScheduler* GPASession::GetCounterScheduler() const
{
    return m_pCounterScheduler;
}

bool GPASession::Flush(uint32_t timeout)
{
    TRACE_PRIVATE_FUNCTION(GPASession::Flush);

    bool retVal = true;

    auto startTime = std::chrono::steady_clock::now();

    // block until the session is complete or the timeout (if any) is reached
    while (false == IsComplete())
    {
        if (timeout != GPA_TIMEOUT_INFINITE)
        {
            auto currentTime = std::chrono::steady_clock::now();
            auto duration = currentTime - startTime;
            if (std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() > timeout)
            {
                GPA_LogError("GPA session completion timeout occurred.");
                retVal = false;
                break;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        UpdateResults();
    }

    return retVal;
}

bool GPASession::BeginSample(ClientSampleId sampleId, GPA_CommandListId commandListId)
{
    bool bStarted = false;

    if (commandListId->Object()->GetAPIType() == GetAPIType() &&
        commandListId->ObjectType() == GPAObjectType::GPA_OBJECT_TYPE_COMMAND_LIST)
    {
        IGPACommandList* pCmd = commandListId->Object();

        if (nullptr != pCmd)
        {
            GPAPass* pCmdPass = pCmd->GetPass();

            if (nullptr != pCmdPass)
            {
                // Create a sample
                if (nullptr != pCmdPass->CreateAndBeginSample(sampleId, pCmd))
                {
                    bStarted = true;
                }
                else
                {
                    GPA_LogError("Unable to create sample.");
                }
            }
            else
            {
                GPA_LogError("Pass does not exist.");
            }
        }
        else
        {
            GPA_LogError("Command List does not exist.");
        }
    }
    else
    {
        GPA_LogError("Invalid Parameter.");
    }

    return bStarted;
}


bool GPASession::CheckWhetherPassesAreConsistent() const
{
    bool isConsistent = true;

    if (m_passes.size() > 1)
    {
        unsigned int sampleCount = m_passes.at(0)->GetSampleCount();

        for (auto passIter = m_passes.cbegin(); passIter != m_passes.cend(); ++passIter)
        {
            isConsistent &= (*passIter)->GetSampleCount() == sampleCount;
        }
    }

    return isConsistent;
}

bool GPASession::EndSample(GPA_CommandListId commandListId)
{
    bool bEnded = false;

    if (commandListId->Object()->GetAPIType() == GetAPIType() &&
        commandListId->ObjectType() == GPAObjectType::GPA_OBJECT_TYPE_COMMAND_LIST)
    {
        IGPACommandList* pCmd = commandListId->Object();

        if (nullptr != pCmd)
        {
            GPAPass* pCmdPass = pCmd->GetPass();

            if (nullptr != pCmdPass)
            {
                // End the sample
                if (pCmdPass->EndSample(pCmd))
                {
                    bEnded = true;
                }
                else
                {
                    GPA_LogError("Unable to end sample.");
                }
            }
            else
            {
                GPA_LogError("Pass does not exist.");
            }
        }
        else
        {
            GPA_LogError("Command List does not exist.");
        }
    }
    else
    {
        GPA_LogError("Invalid Parameter.");
    }

    return bEnded;
}

GPA_Status GPASession::ContinueSampleOnCommandList(gpa_uint32 srcSampleId, GPA_CommandListId primaryCommandListId)
{
    UNREFERENCED_PARAMETER(srcSampleId);
    UNREFERENCED_PARAMETER(primaryCommandListId);
    return GPA_STATUS_ERROR_API_NOT_SUPPORTED;
}

GPA_Status GPASession::CopySecondarySamples(GPA_CommandListId secondaryCmdListId, GPA_CommandListId primaryCmdListId, gpa_uint32 numSamples, gpa_uint32* pNewSampleIds)
{
    UNREFERENCED_PARAMETER(secondaryCmdListId);
    UNREFERENCED_PARAMETER(primaryCmdListId);
    UNREFERENCED_PARAMETER(numSamples);
    UNREFERENCED_PARAMETER(pNewSampleIds);
    return GPA_STATUS_ERROR_API_NOT_SUPPORTED;
}
