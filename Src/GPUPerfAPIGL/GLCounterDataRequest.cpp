//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GL Counter Data Request
//==============================================================================

#include <assert.h>

#include "GLCounterDataRequest.h"
#include "GLPerfMonitorCache.h"

#include "Logging.h"
#include "GLEntryPoints.h"
#include <sstream>
#ifdef _LINUX
    #include <string.h>
    #include <stdlib.h>
#endif

#if defined(GLES)
    #ifndef GL_TIMESTAMP
        #define GL_TIMESTAMP GL_TIMESTAMP_EXT
    #endif // GL_TIMESTAMP
#endif // GLES

GLCounterDataRequest::GLCounterDataRequest()
    :  m_dataReadyCount(0),
       m_counters(nullptr),
       m_appsCurrentTimerQuery(0),
       m_appsCurrentOcclusionQuery(0),
       m_appsCurrentOcclusionQuery2(0),
       m_appsCurrentTransformFeedbackQuery(0),
       m_monitor(static_cast<GLuint>(-1)),
       m_areAllResultsSaved(false)

{
    TRACE_PRIVATE_FUNCTION(GLCounterDataRequest::CONSTRUCTOR);
    m_counterResults.m_numResults    = 0;
    m_counterResults.m_pResultBuffer = nullptr;
    m_gpuTimeQuery[0] = 0;
    m_gpuTimeQuery[1] = 0;
#ifdef DEBUG_GL_ERRORS
    CheckForGLErrors("ERROR in GLCounterDataRequest constructor");
#endif
}

GLCounterDataRequest::~GLCounterDataRequest()
{
    TRACE_PRIVATE_FUNCTION(GLCounterDataRequest::DESTRUCTOR);

    ReleaseCountersInGLDataRequest();

    delete[] m_counters;
    m_counters = nullptr;

    delete[] m_counterResults.m_pResultBuffer;
    m_counterResults.m_numResults    = 0;
    m_counterResults.m_pResultBuffer = nullptr;
}

void GLCounterDataRequest::CreateGPUTimeQuery()
{
    // create the timer query
    _oglGenQueries(2, &m_gpuTimeQuery[0]);
    GPA_LogDebugMessage("Created Queries: %u, %u.", m_gpuTimeQuery[0], m_gpuTimeQuery[1]);

#ifdef DEBUG_GL_ERRORS
    CheckForGLErrors("glGenQueries(..) caused an error.");
#endif
}

void GLCounterDataRequest::ReleaseCounters()
{
    TRACE_PRIVATE_FUNCTION(GLCounterDataRequest::ReleaseCounters);
    ReleaseCountersInGLDataRequest();
}

void GLCounterDataRequest::ReleaseCountersInGLDataRequest()
{
    TRACE_PRIVATE_FUNCTION(GLCounterDataRequest::ReleaseCountersInGLDataRequest);

    for (gpa_uint32 i = 0; i < m_activeCounters; i++)
    {
        if (IsTimeStamp(i))
        {
            if (m_haveAlreadyBegunGPUTimeQuery)
            {
                m_haveAlreadyBegunGPUTimeQuery = false;

#ifdef DEBUG_GL_ERRORS
                // clear any error that might be caused by ending a query that was not started
                CheckForGLErrors("GPA ended a TIME_ELAPSED query which had not been started.");
#endif
            }
        }
        else
        {
            if (m_monitor != static_cast<GLuint>(-1))
            {
                GLPerfMonitorCache::Instance()->DoneMonitor(m_monitor);
                m_monitor = static_cast<GLuint>(-1);
            }
        }
    }

    GPA_LogDebugMessage("Deleting Query: %u.", m_gpuTimeQuery);

    // Checks added to workaround a potential driver bug. Normally, queries with nameID of 0
    // should be ignored. What is happening though is that deleting a query with name 0 is
    // marking name 0 as free so it can be used again. Subsequent calls to GenQueries will
    // return a name id of 0, which should never happen.
    if (m_gpuTimeQuery[0] != 0)
    {
        _oglDeleteQueries(1, &m_gpuTimeQuery[0]);
    }

    if (m_gpuTimeQuery[1] != 0)
    {
        _oglDeleteQueries(1, &m_gpuTimeQuery[1]);
    }

#ifdef DEBUG_GL_ERRORS
    CheckForGLErrors("Error detected after glDeleteQueries(2, &m_gpuTimeQuery[0]).");
#endif
    m_gpuTimeQuery[0] = 0;
    m_gpuTimeQuery[1] = 0;
}



bool GLCounterDataRequest::CollectResults(GPA_CounterResults& resultStorage)
{
    TRACE_PRIVATE_FUNCTION(GLCounterDataRequest::CollectResults);

#ifdef DEBUG_GL_ERRORS
    // clear GL errors that may have been caused by the app
    CheckForGLErrors("ERROR: before GLCounterDataRequest::CollectResults");
#endif

    // if either top->Bottom or Bottom->Bottom was requested, then we need to check the query
    if ((GPUTimeTopToBottomPresent() && m_counters[GPUTimeTopToBottomOffset()].m_isCounterResultReady == false) ||
        (GPUTimeBottomToBottomPresent() && m_counters[GPUTimeBottomToBottomOffset()].m_isCounterResultReady == false))
    {
        // get the results
        GLuint64EXT gpuTimeResults[2];
        gpuTimeResults[0] = 0ull;
        gpuTimeResults[1] = 0ull;
        _oglGetQueryObjectui64vEXT(m_gpuTimeQuery[0], GL_QUERY_RESULT, &gpuTimeResults[0]);
        _oglGetQueryObjectui64vEXT(m_gpuTimeQuery[1], GL_QUERY_RESULT, &gpuTimeResults[1]);
#ifdef DEBUG_GL_ERRORS
        CheckForGLErrors("ERROR: After calling GetQueryObjectui64vEXT to get the results");
#endif

        // put the results in the correct place
        if (GPUTimeTopToBottomPresent())
        {
            GLuint64 timeDelta = gpuTimeResults[1] - gpuTimeResults[0];
            m_counters[GPUTimeTopToBottomOffset()].m_isCounterResultReady = true;
            memcpy(&(resultStorage.m_pResultBuffer[GPUTimeTopToBottomOffset()]), &timeDelta, sizeof(GLuint) * 2);

            m_dataReadyCount += 1;
        }
        else // if ( m_GPUTimeBottomToBottomPresent )
        {
            GLuint64 timeDelta = gpuTimeResults[1] - gpuTimeResults[0];
            m_counters[GPUTimeBottomToBottomOffset()].m_isCounterResultReady = true;
            memcpy(&(resultStorage.m_pResultBuffer[GPUTimeBottomToBottomOffset()]), &timeDelta, sizeof(GLuint) * 2);

            m_dataReadyCount += 1;
        }

        // if that was the only thing requested, then we are done
        return m_dataReadyCount == m_activeCounters;
    }
    else
    {
        if (!m_areAllResultsSaved)
        {
            if (!GetResults(this))
            {
                GPA_LogError("GL Counter results not collected.");
                return false;
            }
        }

        memcpy(resultStorage.m_pResultBuffer, m_counterResults.m_pResultBuffer, m_counterResults.m_numResults * sizeof(gpa_uint64));
    }

    return m_dataReadyCount == m_activeCounters;
}


void GLCounterDataRequest::Reset(gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters)
{
    TRACE_PRIVATE_FUNCTION(GLCounterDataRequest::Reset);

    // reset object
    const gpa_uint32 newActiveCounters = static_cast<gpa_uint32>(pCounters->size());

    // GL counters must be disabled before being able to reuse the monitor
    ReleaseCounters();

    // see if we can keep the same # of GLCounter objects or if we need to reallocate
    if (m_counterSelectionID != selectionID || m_activeCounters != newActiveCounters)
    {
        if (m_activeCounters != newActiveCounters)
        {
            // need to reallocate buffers
            delete[] m_counters;
            m_counters = new(std::nothrow) GLCounter[newActiveCounters];

            if (nullptr == m_counters)
            {
                GPA_LogError("Unable to allocate memory for counters.");
                return;
            }
        }

        m_counterSelectionID = selectionID;
        m_activeCounters = newActiveCounters;
    }

    GPA_HardwareCounters* pHardwareCounters = getCurrentContext()->m_pCounterAccessor->GetHardwareCounters();

    // refresh timestamp details
    ResetGPUTimeState(pCounters, pHardwareCounters->m_gpuTimeTopToBottomCounterIndex, pHardwareCounters->m_gpuTimeBottomToBottomCounterIndex,
                      pHardwareCounters->m_gpuTimestampTopCounterIndex, pHardwareCounters->m_gpuTimestampPreBottomCounterIndex, pHardwareCounters->m_gpuTimestampPostBottomCounterIndex);

    // Only create the type of object that is needed.
    if (GPUTimeTopToBottomPresent() || GPUTimeBottomToBottomPresent())
    {
        CreateGPUTimeQuery();
    }

#ifdef DEBUG_GL_ERRORS
    CheckForGLErrors("Error detected in Reset.");
#endif

    assert(m_activeCounters == newActiveCounters);

    for (gpa_uint32 i = 0; i < m_activeCounters; i++)
    {
        m_counters[i].m_isCounterResultReady = false;
    }

    m_dataReadyCount = 0;
}

bool GLCounterDataRequest::GetResults(GLCounterDataRequest* pRequest)
{

#ifdef DEBUG_GL_ERRORS

    // clear GL errors that may have been caused by the app
    if (glGetError() != GL_NO_ERROR)
    {
        GPA_LogDebugMessage("Error before GLCounterDataRequest::GetResults.");
    }

#endif

    // wait and read results for previous request
    GLuint uResultsAvailable = GL_FALSE;

    while (uResultsAvailable == GL_FALSE)
    {
        _oglGetPerfMonitorCounterDataAMD(pRequest->m_monitor, GL_PERFMON_RESULT_AVAILABLE_AMD, sizeof(GLuint), &uResultsAvailable, nullptr);

#ifdef DEBUG_GL_ERRORS

        if (uResultsAvailable == GL_FALSE && glGetError() != GL_NO_ERROR)
        {
            std::stringstream error;
            error << "glGetError:" << glGetError() << " from _oglGetPerfMonitorCounterDataAMD.";
            GPA_LogDebugMessage(error.str().c_str());
            return false; // return on error to avoid infinite loop
        }

#endif
    }

    // results now ready, read them and save them to be returned in CollectResults

    if (uResultsAvailable == GL_TRUE)
    {
        // get size of the results array
        GLuint resultSize = 0;
        _oglGetPerfMonitorCounterDataAMD(pRequest->m_monitor, GL_PERFMON_RESULT_SIZE_AMD, sizeof(GLint), &resultSize, nullptr);

#ifdef DEBUG_GL_ERRORS
        CheckForGLErrors("glGetPerfMonitorCounterDataAMD( .. GL_PERFMON_RESULT_SIZE_AMD .. ) caused an error");
#endif
        // obtain the actual results
        GLuint* pCounterData = reinterpret_cast<GLuint*>(malloc(resultSize));
        assert(nullptr != pCounterData);

        GLsizei bytesWritten = 0;
        _oglGetPerfMonitorCounterDataAMD(pRequest->m_monitor, GL_PERFMON_RESULT_AMD, resultSize, pCounterData, &bytesWritten);

#ifdef DEBUG_GL_ERRORS
        CheckForGLErrors("glGetPerfMonitorCounterDataAMD( .. GL_PERFMON_RESULT_AMD .. ) caused an error");
#endif
        // the returned data is structured like this:
        // -----------------------------------------------------
        // |  BlockID  |  CounterID  |  result data |  BlockID ...
        // -----------------------------------------------------
        // so it may not be in the same order it was specified

        // cycle through all the counters and store the data
        GLsizei wordIndex = 0;

        pRequest->m_counterResults.m_numResults = pRequest->m_activeCounters;
        pRequest->m_counterResults.m_pResultBuffer = new(std::nothrow) gpa_uint64[pRequest->m_activeCounters];

        for (gpa_uint32 i = 0; i < pRequest->m_activeCounters; i++)
        {
            // GL may return the data in a different order than expected.
            // find the correct counter to assign the data to.
            GLuint groupID = pCounterData[wordIndex++];
            GLuint counterID = pCounterData[wordIndex++];

            GLuint* pData = &pCounterData[wordIndex];

            GLCounter* pCounter = nullptr;

            // figure out which counter index this result is for; keep the index so that the results can be written into the correct location.
            gpa_uint32 curCounterResultIndex = 0;

            for (curCounterResultIndex = 0; curCounterResultIndex < pRequest->m_activeCounters; curCounterResultIndex++)
            {
                if (pRequest->m_counters[curCounterResultIndex].m_counterGroup == groupID &&
                    pRequest->m_counters[curCounterResultIndex].m_counterIndex == counterID)
                {
                    pCounter = &(pRequest->m_counters[curCounterResultIndex]);
                    break;
                }
            }

            assert(nullptr != pCounter);

            if (nullptr == pCounter)
            {
                GPA_LogDebugError("Unable to find the counter at group %d, counter %d. This caused a NULL pCounter, so the results could not be returned.", groupID, counterID);
                return false;
            }

            GLuint* pDest = reinterpret_cast<GLuint*>(&pRequest->m_counterResults.m_pResultBuffer[curCounterResultIndex]);
            pDest[0] = 0;
            pDest[1] = 0;

            if (pCounter->m_counterType == GL_UNSIGNED_INT64_AMD)
            {
                wordIndex += 2;
                memcpy(pDest, pData, sizeof(GLuint) * 2);
            }
            else if (pCounter->m_counterType == GL_FLOAT)
            {
                wordIndex += 1;
                memcpy(pDest, pData, sizeof(GLfloat));
            }
            else if (pCounter->m_counterType == GL_UNSIGNED_INT)
            {
                wordIndex += 1;
                memcpy(pDest, pData, sizeof(GLuint));
            }
            else if (pCounter->m_counterType == GL_PERCENTAGE_AMD)
            {
                wordIndex += 1;
                memcpy(pDest, pData, sizeof(GLfloat));
            }
            else if (pCounter->m_counterType == GL_INT)
            {
                wordIndex += 1;
                memcpy(pDest, pData, sizeof(GLint));
            }
            else
            {
                assert(!"CounterType not recognized");
                return false;
            }

            pCounter->m_isCounterResultReady = true;
            pRequest->m_dataReadyCount++;
        }

        pRequest->m_areAllResultsSaved = pRequest->m_dataReadyCount == pRequest->m_activeCounters;
        free(pCounterData);
    }

    return true;
}


bool GLCounterDataRequest::BeginRequest(GPA_ContextState* pContextState, void* pSampleList, gpa_uint32 selectionID, const vector<gpa_uint32>* pCounters)
{
    TRACE_PRIVATE_FUNCTION(GLCounterDataRequest::Begin);

    UNREFERENCED_PARAMETER(pSampleList);

    gpa_uint32 vendorId = 0;
    pContextState->m_hwInfo.GetVendorID(vendorId);
    m_isAMD = AMD_VENDOR_ID == vendorId;

#ifdef DEBUG_GL_ERRORS

    // clear GL errors that may have been caused by the app
    if (glGetError() != GL_NO_ERROR)
    {
        GPA_LogDebugMessage("Error before GLCounterDataRequest::Begin.");
    }

#endif

    // reset object since may be reused
    Reset(selectionID, pCounters);

    GPA_HardwareCounters* pHardwareCounters = pContextState->m_pCounterAccessor->GetHardwareCounters();

    m_haveAlreadyBegunGPUTimeQuery = false;

    bool bNewPerfMonitor = false;
    GLCounterDataRequest* pPreviousRequest = nullptr;
    // make sure that we're not looking only at timestamp counters;
    bool bOnlyTimestampCounters = (m_activeCounters == 1 && IsTimeStamp(0)) || (m_activeCounters == 2 && IsTimeStamp(0) && IsTimeStamp(1));

    if (!bOnlyTimestampCounters)
    {
        bNewPerfMonitor = GLPerfMonitorCache::Instance()->GetMonitorForCounters(pCounters, this, m_monitor, pPreviousRequest);
    }

    // loop through requested counters and enable them
    for (gpa_uint32 i = 0; i < m_activeCounters; i++)
    {
        if (IsTimeStamp(i))
        {
            if (m_haveAlreadyBegunGPUTimeQuery == false)
            {
                m_haveAlreadyBegunGPUTimeQuery = true;
                _oglQueryCounter(m_gpuTimeQuery[0], GL_TIMESTAMP);

#ifdef DEBUG_GL_ERRORS

                // if that produced an error, then the Timing functionality isn't available
                if (CheckForGLErrorsCond("glQueryCounter(..) on GL_TIMESTAMP produced an error, please verify that the extension is available."))
                {
                    return false;
                }

#endif
            }
        }
        else
        {
            // need to Enable counters
            const GPA_HardwareCounterDescExt* pCounter = pContextState->m_pCounterAccessor->GetHardwareCounterExt((*pCounters)[i]);

            unsigned int uGroupIndex = pCounter->m_groupIndex;

            GLint nCounters = 0;

            if (uGroupIndex < pHardwareCounters->m_groupCount)
            {
                nCounters = static_cast<GLint>(pHardwareCounters->m_pGroups[uGroupIndex].m_numCounters);
            }
            else
            {
                nCounters = static_cast<GLint>(pHardwareCounters->m_pAdditionalGroups[uGroupIndex - pHardwareCounters->m_groupCount].m_numCounters);
            }

            assert(pCounter->m_pHardwareCounter->m_counterIndexInGroup <= static_cast<unsigned int>(nCounters));

            // validate Counter result type
            GLuint resultType = 0;
            _oglGetPerfMonitorCounterInfoAMD(pCounter->m_groupIdDriver, static_cast<GLuint>(pCounter->m_pHardwareCounter->m_counterIndexInGroup), GL_COUNTER_TYPE_AMD, &resultType);

#ifdef DEBUG_GL_ERRORS

            if (CheckForGLErrorsCond("glGetPerfMonitorCounterInfoAMD failed getting result type"))
            {
                return false;
            }

#endif

            if (bNewPerfMonitor)
            {
                GLPerfMonitorCache::Instance()->EnableCounterInMonitor(m_monitor, pCounter->m_groupIdDriver, pCounter->m_pHardwareCounter->m_counterIndexInGroup);
            }

#ifdef DEBUG_GL_ERRORS

            //TODO revisit this code....
            if (CheckForGLErrorsCond("glSelectPerfMonitorCountersAMD caused an error"))
            {
                // since one of them failed; we need to release all of the previous ones before returning
                Reset(selectionID, counters);
                char groupName[256];
                char counterName[256];
                memset(groupName, 0, 256);
                memset(counterName, 0, 256);
                GLsizei nLength = 0;

                if (uGroupIndex <= (pHardwareCounters->m_groupCount + pHardwareCounters->m_pAdditionalGroupCount))
                {
                    _oglGetPerfMonitorGroupStringAMD(pCounter->m_groupIdDriver, 256, &nLength, groupName);

                    if (CheckForGLErrorsCond("glGetPerfMonitorGroupStringAMD failed getting group name"))
                    {
                        return false;
                    }
                }

                if (pCounter->m_pHardwareCounter->m_counterIndexInGroup <= (unsigned int) nCounters)
                {
                    _oglGetPerfMonitorCounterStringAMD(pCounter->m_groupIdDriver, (GLuint)pCounter->m_pHardwareCounter->m_counterIndexInGroup, 256, &nLength, counterName);

                    if (CheckForGLErrorsCond("glGetPerfMonitorCounterStringAMD failed getting counter name"))
                    {
                        return false;
                    }
                }

                GPA_LogDebugMessage("CheckCounter failed on counter %d: %s (%d) - %s (%d).", (*counters)[i], groupName, pCounter->m_groupIdDriver, counterName, pCounter->m_pHardwareCounter->m_counterIndexInGroup);
                return false;
            }

#endif
            GPA_LogDebugMessage("ENABLED COUNTER: %u.", (*pCounters)[i]);
            m_counters[i].m_counterType = resultType;
            m_counters[i].m_counterID = (*pCounters)[i];
            m_counters[i].m_counterGroup = pCounter->m_groupIdDriver;
            m_counters[i].m_counterIndex = static_cast<GLuint>(pCounter->m_pHardwareCounter->m_counterIndexInGroup);
        }
    }

#ifdef DEBUG_GL_ERRORS
    CheckForGLErrors("There was an error before glBeginPerfMonitorAMD was called");
#endif

    if (!bOnlyTimestampCounters && !bNewPerfMonitor)
    {
        if (!GetResults(pPreviousRequest)) // if there was a previous pending request, we need to get the results from the driver now before starting this new request.
        {
            GPA_LogError("GL Counter results for previous request not collected.");
            return false;
        }
    }

    // GPUTime queries happen in their own pass, so only perform the PerfMonitor if neither GPUTime is present
    if (GPUTimeTopToBottomPresent() == false && GPUTimeBottomToBottomPresent() == false)
    {
        _oglBeginPerfMonitorAMD(m_monitor);
        GPA_LogDebugMessage("glBeginPerfMonitorAMD: %u.", m_monitor);

#ifdef DEBUG_GL_ERRORS

        if (CheckForGLErrorsCond("glBeginPerfMonitorAMD caused an error"))
        {
            Reset(selectionID, counters);
            return false;
        }

#endif
    }

    return true;
}


bool GLCounterDataRequest::EndRequest()
{
    TRACE_PRIVATE_FUNCTION(GLCounterDataRequest::End);

#ifdef DEBUG_GL_ERRORS
    CheckForGLErrors("An error occurred before GLCounterDataRequest::End was called");
#endif

    // if GPUTime was requested, need to handle the query, otherwise handle the PerfMonitor (this only works because GPUTime is handled in its own pass)
    if (GPUTimeTopToBottomPresent() || GPUTimeBottomToBottomPresent())
    {
        if (m_haveAlreadyBegunGPUTimeQuery)
        {
            _oglQueryCounter(m_gpuTimeQuery[1], GL_TIMESTAMP);
            m_haveAlreadyBegunGPUTimeQuery = false;

#ifdef DEBUG_GL_ERRORS
            // See if that produced an error, it shouldn't have though
            CheckForGLErrors("Could not end query for TIME_ELAPSED");
#endif
        }
    }
    else
    {
        // Inserting a glFlush() before and after the EndPerfMonitor call appears to make a number of the results more consistent.
        // The effects of the first glFlush() is extremely noticeable with the GLFiveQuarterQuads test and the PostZSamplesPassing counter.
        // The effects of the second glFlush() are noticeable with last draw call of the GLFiveQuarterQuads test and the PreZSamplesPassing counter.
        // The effects of the second glFlush() are also noticeable with last draw call of the GLFiveQuarterQuads test and the CBMemWritten counter.
        _oglFlush();

        _oglEndPerfMonitorAMD(m_monitor);
        GPA_LogDebugMessage("glEndPerfMonitorAMD: %u.", m_monitor);

        _oglFlush();

    }

    return true;
}
