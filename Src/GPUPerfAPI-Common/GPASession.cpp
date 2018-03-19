//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief A base-class implementation of the GPA Session interface
//==============================================================================

// std
#include <list>
#include <chrono>
#include <thread>

// GPA Common
#include "GPASession.h"
#include "GPAUniqueObject.h"
#include "IGPACommandList.h"
#include "GPASplitCountersInterfaces.h"
#include "GPAPass.h"
#include "GPUPerfAPITypes.h"

// TODO: these are placeholder values (rough estimates) for right now. We should replace with reasonable values after testing
static const gpa_uint32 DEFAULT_SPM_INTERVAL = 4096;                  ///< default SPM sampling interval (4096 clock cycles)
static const gpa_uint64 DEFAULT_SPM_MEMORY_LIMIT = 16 * 1024 * 1024;  ///< default SPM memory limit size (16 MB)
static const gpa_uint64 DEFAULT_SQTT_MEMORY_LIMIT = 80 * 1024 * 1024; ///< default SQTT memory limit size (80 MB) -- will likely need to be larger (512MB) if instruction-level trace is performed

GPASession::GPASession(IGPAContext* pParentContext, IGPACounterScheduler* pCounterScheduler, GPA_Session_Sample_Type sampleType):
    m_state(GPA_SESSION_STATE_NOT_STARTED),
    m_pCounterScheduler(pCounterScheduler),
    m_pParentContext(pParentContext),
    m_maxPassIndex(0u),
    m_sampleType(sampleType),
    m_spmInterval(DEFAULT_SPM_INTERVAL),
    m_spmMemoryLimit(DEFAULT_SPM_MEMORY_LIMIT),
    m_sqttInstructionMask(GPA_SQTT_INSTRUCTION_TYPE_NONE),
    m_sqttComputeUnitId(0),
    m_sqttMemoryLimit(DEFAULT_SQTT_MEMORY_LIMIT)
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
    if (GPA_SESSION_SAMPLE_TYPE_DISCRETE_COUNTER != m_sampleType &&
        GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER != m_sampleType &&
        GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER_AND_SQTT != m_sampleType)
    {
        GPA_LogError("Unable to enable counter. Session was not created with a GPA_Session_Sample_Type value that supports counter collection.");
        return GPA_STATUS_ERROR_INCOMPATIBLE_SAMPLE_TYPES;
    }

    if (IsSessionRunning())
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    GPA_Status status = (nullptr == m_pCounterScheduler) ? GPA_STATUS_ERROR_FAILED : m_pCounterScheduler->EnableCounter(index);

    if (GPA_STATUS_OK == status &&
        ((GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER == m_sampleType) ||
         (GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER_AND_SQTT == m_sampleType)))
    {
        // if we're sampling streaming counters, then only enable the counter if the set of counters remains single-pass
        gpa_uint32 numPasses = 0;
        status = m_pCounterScheduler->GetNumRequiredPasses(&numPasses);

        if (GPA_STATUS_OK == status)
        {
            if (1 < numPasses)
            {
                m_pCounterScheduler->DisableCounter(index);
                GPA_LogError("Unable to enable counter. Multi-pass counter sets not supported for streaming counters.");
                status = GPA_STATUS_ERROR_NOT_ENABLED;
            }
        }
    }

    return status;
}

GPA_Status GPASession::DisableCounter(gpa_uint32 index)
{
    if (IsSessionRunning())
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    return (nullptr == m_pCounterScheduler) ? GPA_STATUS_ERROR_FAILED : m_pCounterScheduler->DisableCounter(index);
}

GPA_Status GPASession::DisableAllCounters()
{
    if (nullptr == m_pCounterScheduler)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    m_pCounterScheduler->DisableAllCounters();

    return GPA_STATUS_OK;
}

GPA_Status GPASession::GetNumEnabledCounters(gpa_uint32* pCount) const
{
    if (nullptr == pCount)
    {
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    if (nullptr == m_pCounterScheduler)
    {
        return GPA_STATUS_ERROR_FAILED;
    }

    *pCount = m_pCounterScheduler->GetNumEnabledCounters();

    return GPA_STATUS_OK;
}

GPA_Status GPASession::GetEnabledIndex(gpa_uint32 enabledNumber, gpa_uint32* pEnabledCounterIndex) const
{
    return (nullptr == m_pCounterScheduler) ? GPA_STATUS_ERROR_FAILED : m_pCounterScheduler->GetEnabledIndex(enabledNumber, pEnabledCounterIndex);
}

GPA_Status GPASession::IsCounterEnabled(gpa_uint32 counterIndex) const
{
    return (nullptr == m_pCounterScheduler) ? GPA_STATUS_ERROR_FAILED : m_pCounterScheduler->IsCounterEnabled(counterIndex);
}

GPA_Status GPASession::GetNumRequiredPasses(gpa_uint32* pNumPasses)
{
    return (nullptr == m_pCounterScheduler) ? GPA_STATUS_ERROR_FAILED : m_pCounterScheduler->GetNumRequiredPasses(pNumPasses);
}

GPA_Status GPASession::Begin()
{
    GPA_Status status = GPA_STATUS_OK;

    if (GPA_SESSION_STATE_STARTED <= m_state)
    {
        GPA_LogError("Session has already been started.");
        status = GPA_STATUS_ERROR_SESSION_ALREADY_STARTED;
    }
    else if (GPA_SESSION_SAMPLE_TYPE_DISCRETE_COUNTER == m_sampleType ||
             GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER == m_sampleType ||
             GPA_SESSION_SAMPLE_TYPE_STREAMING_COUNTER_AND_SQTT == m_sampleType)
    {
        // If we are collecting counters, we will check to make sure at least one counter is enabled.
        // If so, we will then check how many passes are required and pre-create passes for the Session
        if (nullptr != m_pCounterScheduler &&
            m_pCounterScheduler->GetNumEnabledCounters() > 0)
        {
            gpa_uint32 passCount;

            if (GPA_STATUS_OK == m_pCounterScheduler->GetNumRequiredPasses(&passCount))
            {
                // assume the loop below will succeed, it will get set to false if the loop fails
                bool success = true;

                for (gpa_uint32 passIndexIter = 0; passIndexIter < passCount && success; passIndexIter++)
                {
                    GPAPass* pCurrentPass = CreateAPIPass(passIndexIter);

                    if (nullptr != pCurrentPass)
                    {
                        m_passes.push_back(pCurrentPass);
                    }
                    else
                    {
                        // Unable to create API specific pass object
                        success = false;
                        break;
                    }
                }

                if (!success)
                {
                    GPA_LogError("Unable to create passes for the session.");
                    status = GPA_STATUS_ERROR_FAILED;
                }
            }
            else
            {
                GPA_LogError("The session failed to get the number of required passes.");
                status = GPA_STATUS_ERROR_FAILED;
            }
        }
        else
        {
            GPA_LogError("The session can't be started without any enabled counters.");
            status = GPA_STATUS_ERROR_NO_COUNTERS_ENABLED;
        }
    }

    // if we can successfully start the session, then mark the session as started
    if (GPA_STATUS_OK == status)
    {
        std::lock_guard<std::mutex> lockResources(m_gpaSessionMutex);
        m_state = GPA_SESSION_STATE_STARTED;
    }

    return status;
}

GPA_Status GPASession::End()
{
    GPA_Status status = GPA_STATUS_ERROR_FAILED;

    if (GPA_SESSION_STATE_STARTED == m_state)
    {
        std::lock_guard<std::mutex> lockResources(m_gpaSessionMutex);

        // Check whether that sufficient command list have been created for all passes
        if (m_maxPassIndex == m_passes.size() - 1)
        {
            if (CheckWhetherPassesAreFinishedAndConsistent())
            {
                m_state = GPA_SESSION_STATE_ENDED_PENDING_RESULTS;
                status  = GPA_STATUS_OK;
            }
            else
            {
                GPA_LogError("Some passes have an incorrect number of samples.");
                status = GPA_STATUS_ERROR_VARIABLE_NUMBER_OF_SAMPLES_IN_PASSES;
            }
        }
        else
        {
            GPA_LogError("Not all passes have been executed.");
            status = GPA_STATUS_ERROR_NOT_ENOUGH_PASSES;
        }
    }
    else
    {
        GPA_LogError("Session has not been started.");
        status = GPA_STATUS_ERROR_SESSION_NOT_STARTED;
    }

    return status;
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

bool GPASession::DoesSampleExist(gpa_uint32 sampleIndex) const
{
    bool retVal = false;

    if (!m_passes.empty())
    {
        retVal = m_passes[0]->DoesSampleExist(sampleIndex);
    }

    return retVal;
}

bool GPASession::UpdateResults()
{
    bool areAllPassesComplete = true;

    for (PassInfo::iterator passIter = m_passes.begin(); passIter != m_passes.end(); ++passIter)
    {
        areAllPassesComplete &= UpdateResults((*passIter)->GetIndex());

        if (!areAllPassesComplete)
        {
            GPA_LogError("Pass is not complete.");
        }
    }

    if (areAllPassesComplete)
    {
        m_state = GPA_SESSION_STATE_RESULT_COLLECTED;
    }

    return areAllPassesComplete;
}

bool GPASession::UpdateResults(gpa_uint32 passIndex)
{
    bool success = false;

    if (passIndex <= m_maxPassIndex)
    {
        std::lock_guard<std::mutex> lockResources(m_gpaSessionMutex);
        success = m_passes.at(passIndex)->IsResultCollected();

        if (!success)
        {
            success = GPA_STATUS_OK == m_passes.at(passIndex)->IsComplete();

            if (success)
            {
                success = m_passes.at(passIndex)->IsResultReady();

                if (success)
                {
                    success = m_passes.at(passIndex)->UpdateResults();
                }
            }
            else
            {
                GPA_LogError("Some samples in the pass have not finished.");
            }
        }
    }
    else
    {
        GPA_LogError("Incorrect pass index.");
    }

    return success;
}

bool GPASession::IsSessionRunning() const
{
    return GPA_SESSION_STATE_STARTED == m_state;
}

GPA_Status GPASession::IsPassComplete(gpa_uint32 passIndex) const
{
    GPA_Status retStatus = GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE;

    if (passIndex < m_passes.size() && passIndex <= m_maxPassIndex)
    {
        retStatus = m_passes[passIndex]->IsComplete();
    }

    return retStatus;
}

bool GPASession::IsResultReady() const
{
    TRACE_PRIVATE_FUNCTION(GPASession::IsComplete);
    return GPA_SESSION_STATE_RESULT_COLLECTED == m_state;
}

size_t GPASession::GetSampleResultSizeInBytes(gpa_uint32 sampleId) const
{
    size_t sizeInBytes = 0;

    if (nullptr == m_pCounterScheduler)
    {
        GPA_LogError("Unable to GetSampleResultSizeInBytes, counter scheduler is invalid.");
    }
    else if (GPA_SESSION_SAMPLE_TYPE_DISCRETE_COUNTER == m_sampleType)
    {
        sizeInBytes = sizeof(gpa_uint64) * m_pCounterScheduler->GetNumEnabledCounters();
    }
    else
    {
        UNREFERENCED_PARAMETER(sampleId);
        // TODO: retrieve data size for GPA_SAMPLE_TYPE_STREAMING_COUNTER and/or GPA_SAMPLE_TYPE_SQTT
    }

    return sizeInBytes;
}

GPA_Status GPASession::GetSampleResult(gpa_uint32 sampleId, size_t sampleResultSizeInBytes, void* pCounterSampleResults)
{
    TRACE_PRIVATE_FUNCTION(GPASession::GetSampleResult);

    if (sampleResultSizeInBytes < GetSampleResultSizeInBytes(sampleId))
    {
        GPA_LogError("The value of sampleResultSizeInBytes indicates that the buffer is too small to contain the results.");
        return GPA_STATUS_ERROR_READING_SAMPLE_RESULT;
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
        GPA_LogError("Results cannot be queried from secondary samples.");
        return GPA_STATUS_ERROR_SAMPLE_IN_SECONDARY_COMMAND_LIST;
    }

    const uint32_t timeout = 5 * 1000; // 5 second timeout
    Flush(timeout); // TODO: how do we handle the timeout case?

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
                        return GPA_STATUS_ERROR_READING_SAMPLE_RESULT;
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

GPA_Session_Sample_Type GPASession::GetSampleType() const
{
    return m_sampleType;
}

gpa_uint32 GPASession::GetSPMInterval() const
{
    return m_spmInterval;
}

void GPASession::SetSPMInterval(gpa_uint32 interval)
{
    m_spmInterval = interval;
}

gpa_uint64 GPASession::GetSPMMemoryLimit() const
{
    return m_spmMemoryLimit;
}

void GPASession::SetSPMMemoryLimit(gpa_uint64 memoryLimit)
{
    m_spmMemoryLimit = memoryLimit;
}

GPA_SQTTInstructionFlags GPASession::GetSQTTInstructionMask() const
{
    return m_sqttInstructionMask;
}

void GPASession::SetSQTTInstructionMask(GPA_SQTTInstructionFlags sqttInstructionMask)
{
    m_sqttInstructionMask = sqttInstructionMask;
}

gpa_uint32 GPASession::GetSQTTComputeUnitId() const
{
    return m_sqttComputeUnitId;
}

void GPASession::SetSQTTComputeUnitId(gpa_uint32 sqttComputeUnitId)
{
    m_sqttComputeUnitId = sqttComputeUnitId;
}

gpa_uint64 GPASession::GetSQTTMemoryLimit() const
{
    return m_sqttMemoryLimit;
}

void GPASession::SetSQTTMemoryLimit(gpa_uint64 memoryLimit)
{
    m_sqttMemoryLimit = memoryLimit;
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
    while (!IsResultReady())
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


bool GPASession::CheckWhetherPassesAreFinishedAndConsistent() const
{
    bool isConsistent = true;
    bool isFinished = true;

    if (m_passes.size() > 1)
    {
        unsigned int sampleCount = m_passes.at(0)->GetSampleCount();

        for (auto passIter = m_passes.cbegin();
             passIter != m_passes.cend() && isFinished && isConsistent; ++passIter)
        {
            isFinished &= (GPA_STATUS_OK == (*passIter)->IsComplete());
            isConsistent &= (*passIter)->GetSampleCount() == sampleCount;
        }
    }

    if (!isFinished)
    {
        GPA_LogError("Some passes have not ended.");
    }

    if (!isConsistent)
    {
        GPA_LogError("Some passes have an incorrect number of samples.");
    }

    return isFinished && isConsistent;
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
