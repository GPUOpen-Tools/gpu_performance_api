//==============================================================================
// Copyright (c) 2012-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A class for managing data requests for an entire session
//==============================================================================

#include "GPASessionRequests.h"
#include <assert.h>
#include <list>

/// define a type which is a pair containing a pass index and a sample id. It is used while identifying if all samples in all passes of a session are complete.
typedef std::pair<gpa_uint32, gpa_uint32> PassIndexAndSampleIdPair;

GPA_SessionRequests::GPA_SessionRequests()
    : m_sessionID(0)
{
    TRACE_PRIVATE_FUNCTION(GPA_SessionRequests::CONSTRUCTOR);
}

//-----------------------------------------------------------------------------
GPA_SessionRequests::~GPA_SessionRequests()
{
    TRACE_PRIVATE_FUNCTION(GPA_SessionRequests::DESTRUCTOR);

    Flush();

    //delete allocated result buffers from Begin()
    for (auto buffer : m_allocatedResultBuffer)
    {
        delete[] buffer;
    }

    // clean up the passes
    for (auto pass : m_passes)
    {
        pass.m_samples.clear();
        pass.m_results.clear();
    }

    m_allocatedResultBuffer.clear();
}

//-----------------------------------------------------------------------------
void GPA_SessionRequests::Flush()
{
    TRACE_PRIVATE_FUNCTION(GPA_SessionRequests::Flush);

    // block until the session is complete
    while (IsComplete() == false)
    {
    }
}

//-----------------------------------------------------------------------------
void GPA_SessionRequests::CheckForAvailableResults(gpa_uint32 passIndex)
{
    TRACE_PRIVATE_FUNCTION(GPA_SessionRequests::CheckForAvailableResults);

    UNREFERENCED_PARAMETER(passIndex);

    // check to see if this session is complete.
    IsComplete();
}

//-----------------------------------------------------------------------------
void GPA_SessionRequests::SetPassCount(gpa_uint32 passCount)
{
    TRACE_PRIVATE_FUNCTION(GPA_SessionRequests::SetPassCount);
    // resize each of the arrays so that the data isn't continually allocated throughout the profile pass
    m_passes.resize(passCount);
}

//-----------------------------------------------------------------------------
gpa_uint32 GPA_SessionRequests::GetPassCount()
{
    TRACE_PRIVATE_FUNCTION(GPA_SessionRequests::GetPassCount);

    return (gpa_uint32)m_passes.size();
}

//-----------------------------------------------------------------------------
GPA_Status GPA_SessionRequests::GetSampleCount(gpa_uint32* pSamples)
{
    TRACE_PRIVATE_FUNCTION(GPA_SessionRequests::GetSampleCount);

    GPA_Status status = GPA_STATUS_OK;

    if (nullptr == pSamples)
    {
        GPA_LogDebugError("pSamples is NULL in GPA_SessionRequests::GetSampleCount.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    // make sure there is at least one request
    if (m_passes.size() == 0)
    {
        std::stringstream message;
        message << "No counters were enabled in session " << m_sessionID << ".";
        GPA_LogError(message.str().c_str());
        status = GPA_STATUS_ERROR_NOT_FOUND;
    }
    else
    {
        *pSamples = (gpa_uint32)(m_passes[0].m_results.size());
    }

    return status;
}

//-----------------------------------------------------------------------------
void GPA_SessionRequests::Begin(gpa_uint32 passIndex, gpa_uint32 sampleId, GPA_DataRequest* pRequest)
{
    TRACE_PRIVATE_FUNCTION(GPA_SessionRequests::Begin);
    assert(nullptr != pRequest);

    GPA_CounterResults result = { 0, nullptr };

    // Prevent memory leak by making sure we clear up all profiler results we allocate.
    // We will delete all the memory allocated in the destructor.

    assert(passIndex < m_passes.size());
    //add the request to the pending requests list
    m_passes[passIndex].m_samples[sampleId] = pRequest;
    result.m_numResults    = pRequest->NumActiveCounters();
    result.m_pResultBuffer = new(std::nothrow) gpa_uint64[result.m_numResults];

    if (nullptr == result.m_pResultBuffer)
    {
        GPA_LogError("Unable to allocate memory for session results.");
    }
    else
    {
        m_passes[passIndex].m_results[sampleId] = result;
        m_allocatedResultBuffer.push_back(result.m_pResultBuffer);
    }
}

//-----------------------------------------------------------------------------
bool GPA_SessionRequests::End(gpa_uint32 passIndex, gpa_uint32 sampleId)
{
    TRACE_PRIVATE_FUNCTION(GPA_SessionRequests::End);

    if (ContainsSampleRequest(passIndex, sampleId) == false)
    {
        return false;
    }

    return m_passes[passIndex].m_samples[sampleId]->End();
}

//-----------------------------------------------------------------------------
bool GPA_SessionRequests::ContainsSampleRequest(gpa_uint32 passIndex, gpa_uint32 sampleId)
{
    TRACE_PRIVATE_FUNCTION(GPA_SessionRequests::ContainsSampleRequest);

    if (passIndex >= m_passes.size())
    {
        return false;
    }

    return m_passes[passIndex].m_samples.find(sampleId) != m_passes[passIndex].m_samples.end();
}

//-----------------------------------------------------------------------------
bool GPA_SessionRequests::ContainsSampleResult(gpa_uint32 passIndex, gpa_uint32 sampleId)
{
    TRACE_PRIVATE_FUNCTION(GPA_SessionRequests::ContainsSampleResult);

    if (passIndex >= m_passes.size())
    {
        return false;
    }

    if (ContainsSampleRequest(passIndex, sampleId))
    {
        return false;
    }
    else
    {
        return m_passes[passIndex].m_results.find(sampleId) != m_passes[passIndex].m_results.end();
    }
}

//-----------------------------------------------------------------------------
GPA_Status GPA_SessionRequests::IsSampleReady(gpa_uint32 sampleId, bool* pIsSampleReady)
{
    TRACE_PRIVATE_FUNCTION(GPA_SessionRequests::IsSampleReady);

    GPA_Status status = GPA_STATUS_OK;

    if (nullptr == pIsSampleReady)
    {
        GPA_LogDebugError("pIsSampleReady is NULL in GPA_SessionRequests::IsSampleReady.");
        status = GPA_STATUS_ERROR_NULL_POINTER;
    }
    else
    {
        *pIsSampleReady = true;

        IsComplete();

        for (gpa_uint32 passIndex = 0; passIndex < m_passes.size(); ++passIndex)
        {
            if (ContainsSampleResult(passIndex, sampleId) == false)
            {
                // the result was not ready for this pass / sample.
                *pIsSampleReady = false;

                // make sure the request is available
                if (ContainsSampleRequest(passIndex, sampleId) == false)
                {
                    // request was not available
                    status = GPA_STATUS_ERROR_SAMPLE_NOT_FOUND_IN_ALL_PASSES;
                    GPA_LogError("All passes must contain the same number of samples in order for the data to be collected successfully.");
                    break;
                }
            }
        }
    }

    return status;
}

//-----------------------------------------------------------------------------
bool GPA_SessionRequests::IsComplete()
{
    TRACE_PRIVATE_FUNCTION(GPA_SessionRequests::IsComplete);

    bool result = true;


    // this will contain the pass index and sample id of the results which became available and got copied into the
    // results buffer. This list is then used to remove the requests so that they are not checked the next time this
    // function is called.
    std::list<PassIndexAndSampleIdPair> completedSamples;

    gpa_uint32 passIndex = 0;

    for (std::vector<GPA_PassRequests>::iterator passIter = m_passes.begin(); passIter != m_passes.end(); ++passIter)
    {
        for (std::map<gpa_uint32, GPA_DataRequest*>::iterator requestIter = passIter->m_samples.begin(); requestIter != passIter->m_samples.end(); ++requestIter)
        {
            gpa_uint32 sampleId = requestIter->first;

            // only need to check to see if it is complete if the result is not already back.
            if (ContainsSampleResult(passIndex, sampleId) == false)
            {
                // check sample within the pass
                if (!requestIter->second->IsRequestComplete(passIter->m_results[sampleId]))
                {
                    result = false;
                }
                else
                {
                    // The request is complete and the results are available.

                    // Now mark the data request to be removed.
                    PassIndexAndSampleIdPair pair;
                    pair.first = passIndex;
                    pair.second = sampleId;
                    completedSamples.push_back(pair);
                }
            }
        }

        ++passIndex;
    }

    // remove the completed samples
    for (std::list<PassIndexAndSampleIdPair>::iterator iter = completedSamples.begin(); iter != completedSamples.end(); ++iter)
    {
        // since the results are backed up, now we can delete the data request
        delete m_passes[iter->first].m_samples[iter->second];
        m_passes[iter->first].m_samples[iter->second] = nullptr;
        m_passes[iter->first].m_samples.erase(iter->second);
    }

    completedSamples.clear();

    return result;
}

//-----------------------------------------------------------------------------
GPA_Status GPA_SessionRequests::GetResult(gpa_uint32 passIndex, gpa_uint32 sampleId, gpa_uint16 counterOffset, void* pResult)
{
    TRACE_PRIVATE_FUNCTION(GPA_SessionRequests::GetResult);

    if (nullptr == pResult)
    {
        GPA_LogDebugError("pResult is NULL in GPA_SessionRequests::GetResult.");
        return GPA_STATUS_ERROR_NULL_POINTER;
    }

    // ensure counter pass is valid
    if (passIndex >= m_passes.size())
    {
        std::stringstream message;
        message << "'passIndex' is " << passIndex << " but must be less than the number of pass requests (" << m_passes.size() << ").";
        GPA_LogDebugError(message.str().c_str());
        return GPA_STATUS_ERROR_INDEX_OUT_OF_RANGE;
    }

    // block until results are available
    Flush();

    // first look for the existing result
    if (ContainsSampleResult(passIndex, sampleId))
    {
        // already have the result, return it
        GPA_CounterResults& counterResults = m_passes[passIndex].m_results[sampleId];

        if (counterOffset < counterResults.m_numResults)
        {
            gpa_uint64* pBuf = (gpa_uint64*)pResult;
            assert(nullptr != counterResults.m_pResultBuffer);

            if (nullptr != counterResults.m_pResultBuffer)
            {
                *pBuf = counterResults.m_pResultBuffer[counterOffset];
            }
            else
            {
                *pBuf = 0;
            }
        }
        else
        {
            std::stringstream message;
            message << "Counter results do not contain a result for counter index " << counterOffset << ".";
            GPA_LogDebugError(message.str().c_str());
            return GPA_STATUS_ERROR_READING_COUNTER_RESULT;
        }
    }
    else
    {
        std::stringstream message;
        message << "Pass " << passIndex << " does not contain a result for sample ID " << sampleId << ".";
        GPA_LogDebugError(message.str().c_str());
        return GPA_STATUS_ERROR_SAMPLE_NOT_FOUND;
    }

    return GPA_STATUS_OK;
}
