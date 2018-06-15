//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA Sample Implementation
//==============================================================================

#include "GPASample.h"
#include "GPAPass.h"
#include "IGPACommandList.h"

GPASample::GPASample(GPAPass* pPass,
                     IGPACommandList* pGpaCmdList,
                     GpaSampleType sampleType,
                     ClientSampleId clientSampleId):
    m_pPass(pPass),
    m_pGpaCmdList(pGpaCmdList),
    m_gpaSampleType(sampleType),
    m_clientSampleId(clientSampleId),
    m_driverSampleId(0),
    m_gpaSampleState(GPASampleState::INITIALIZED),
    m_pSampleResult(nullptr),
    m_pContinuingSample(nullptr),
    m_isOpened(false),
    m_isClosedByClient(false),
    m_isContinuedByClient(false),
    m_isCopiedSample(false)
{
    m_isSecondary = (GPA_COMMAND_LIST_SECONDARY == pGpaCmdList->GetCmdType());

    // First, only allocate result space for primary samples.
    // If a secondary sample gets copied, then it will also get space allocated for the results.
    if (!m_isSecondary)
    {
        AllocateSampleResultSpace();
    }
}

GPA_THREAD_SAFE_FUNCTION bool GPASample::Begin()
{
    bool result = false;

    std::lock_guard<std::mutex> lockSample(m_sampleMutex);
    result = BeginRequest();

    if (result)
    {
        m_gpaSampleState = GPASampleState::STARTED;
        m_isOpened = true;
    }

    return result;
}

/// Ends a counter sample.
/// \return True on success; false on error.
bool GPASample::End()
{
    // make sure this request is valid before trying to end it.
    if (m_gpaSampleState != GPASampleState::STARTED)
    {
        return false;
    }

    bool result = EndRequest();

    if (result)
    {
        m_gpaSampleState = GPASampleState::PENDING_RESULTS;
    }

    return result;
}

bool GPASample::GetResult(CounterIndex counterIndexInSample, gpa_uint64* pResult) const
{
    bool hasResult = false;

    if (!IsSecondary() || IsCopied())
    {
        if (nullptr != pResult &&
            IsResultCollected())
        {
            if (nullptr != m_pSampleResult &&
                counterIndexInSample < m_pSampleResult->GetNumCounters() &&
                nullptr != m_pSampleResult->GetResultBuffer())
            {
                hasResult = true;
                *pResult = m_pSampleResult->GetResultBuffer()[counterIndexInSample];
            }
            else
            {
                GPA_LogError("Counter Index out of range.");
            }
        }
        else
        {
            GPA_LogError("Either the sample is not completed or incorrect result location.");
        }
    }

    return hasResult;
}

void GPASample::SetDriverSampleId(const DriverSampleId& driverSampleId)
{
    m_driverSampleId = driverSampleId;
}

DriverSampleId GPASample::GetDriverSampleId() const
{
    return m_driverSampleId;
}

ClientSampleId GPASample::GetClientSampleId() const
{
    return m_clientSampleId;
}

void GPASample::AllocateSampleResultSpace()
{
    if (nullptr == m_pSampleResult)
    {
        m_pSampleResult = new(std::nothrow) GPASampleResult(m_pPass->GetEnabledCounterCount());
    }
}

bool GPASample::IsSecondary() const
{
    return m_isSecondary;
}

GpaSampleType GPASample::GetGpaSampleType() const
{
    return m_gpaSampleType;
}

GPASampleState GPASample::GetGpaSampleState() const
{
    return m_gpaSampleState;
}

GPASampleResult* GPASample::GetSampleResultLocation() const
{
    return m_pSampleResult;
}

GPASample* GPASample::GetContinuingSample() const
{
    return m_pContinuingSample;
}

GPA_THREAD_SAFE_FUNCTION bool GPASample::SetAsClosedByClient()
{
    bool success = false;
    std::lock_guard<std::mutex> lockSample(m_sampleMutex);

    if (!m_isContinuedByClient)
    {
        m_isClosedByClient = true;
        success = true;
    }
    else
    {
        GPA_LogError("Sample has already been continued by client.");
    }

    return success;
}

bool GPASample::SetAsCopied()
{
    bool success = false;
    std::lock_guard<std::mutex> lockSample(m_sampleMutex);
    m_gpaSampleState = GPASampleState::PENDING_RESULTS;

    if (!m_isCopiedSample)
    {
        m_isCopiedSample = true;
        AllocateSampleResultSpace();
        success = true;
    }
    else
    {
        GPA_LogError("Sample has already been copied by client.");
    }

    return success;
}

bool GPASample::IsCopied() const
{
    return m_isCopiedSample;
}

bool GPASample::IsClosedByClient() const
{
    return m_isClosedByClient;
}

bool GPASample::IsContinuedByClient() const
{
    return m_isContinuedByClient;
}

GPA_THREAD_SAFE_FUNCTION bool GPASample::SetAsContinuedByClient()
{
    std::lock_guard<std::mutex> lockSample(m_sampleMutex);
    bool success = false;

    if (!m_isClosedByClient)
    {
        m_isContinuedByClient = true;
        success = true;
    }
    else
    {
        GPA_LogError("Sample has already been closed by client.");
    }

    return success;

}

bool GPASample::IsSampleValid() const
{
    // A sample is only valid if it is opened and either it is continued/copied on another command list or closed on the same command list on which it was created
    return m_isOpened &&
           ((m_isClosedByClient && !m_isContinuedByClient) ||
            (!m_isClosedByClient && m_isContinuedByClient)) ||
           m_isCopiedSample;
}

bool GPASample::IsClosed() const
{
    return m_isClosedByClient || m_isContinuedByClient;
}

void GPASample::MarkAsCompleted()
{
    m_gpaSampleState = GPASampleState::RESULTS_COLLECTED;
}

bool GPASample::IsSampleContinuing() const
{
    return nullptr != m_pContinuingSample;
}

IGPACommandList* GPASample::GetCmdList() const
{
    return m_pGpaCmdList;
}

bool GPASample::LinkContinuingSample(GPASample* pContinuingSample)
{
    std::lock_guard<std::recursive_mutex> lock(m_continueSampleMutex);

    if (nullptr == pContinuingSample)
    {
        return false;
    }

    bool success = true;

    if (nullptr != m_pContinuingSample)
    {
        success &= m_pContinuingSample->LinkContinuingSample(pContinuingSample);
    }
    else
    {
        // Check whether the continuing sample is on different command list or not
        if (pContinuingSample->m_pGpaCmdList == m_pGpaCmdList)
        {
            success = false;
        }
        else
        {
            m_pContinuingSample = pContinuingSample;
            success = true;
        }
    }

    return success;
}

GPAPass* GPASample::GetPass() const
{
    return m_pPass;
}

GPASample::~GPASample()
{
    if (nullptr != m_pContinuingSample)
    {
        delete m_pContinuingSample;
    }

    delete m_pSampleResult;
}
