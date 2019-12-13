//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GL GPA Sample Implementation
//==============================================================================

#include <chrono>
#include <thread>
#include "GLGPASample.h"
#include "GLEntryPoints.h"

GLGPASample::GLGPASample(GPAPass* pPass, IGPACommandList* pCmdList, GpaSampleType sampleType, ClientSampleId sampleId)
    : GPASample(pPass, pCmdList, sampleType, sampleId)
    , m_pGlGpaPass(reinterpret_cast<GLGPAPass*>(pPass))
{
    if (m_pGlGpaPass->IsTimingPass())
    {
        CreateGPUTimeQuery();
    }
}

GLGPASample::~GLGPASample()
{
    if (m_pGlGpaPass->IsTimingPass())
    {
        DeleteGPUTimeQueries();
    }
}

bool GLGPASample::UpdateResults()
{
    bool isDataCollected = IsResultCollected();

    if (!isDataCollected)
    {
        const uint32_t timeout   = 10000;  // ms
        auto           startTime = std::chrono::high_resolution_clock::now();

        do
        {
            isDataCollected = CopyResults();

            if (!isDataCollected)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(0));

                auto                                      endTime     = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsedTime = endTime - startTime;

                if (elapsedTime.count() > timeout)
                {
                    GPA_LogError("Failed to collect counter data due to elapsed timeout.");
                    break;
                }
            }
        } while (!isDataCollected);

        if (isDataCollected)
        {
            MarkAsCompleted();
        }
    }

    return isDataCollected;
}

bool GLGPASample::BeginRequest()
{
    bool success = false;

    if (m_pGlGpaPass->IsTimingPass())
    {
        // handle timing pass
        oglUtils::_oglQueryCounter(m_sampleDataBuffer.m_gpuTimeQuery[0], GL_TIMESTAMP);

        if (!oglUtils::CheckForGLError("Unable to begin the GL timing query."))
        {
            success = true;
        }
    }
    else
    {
        if (m_pGlGpaPass->GetPerfMonitor(m_sampleDataBuffer.m_glPerfMonitorId))
        {
            oglUtils::_oglBeginPerfMonitorAMD(m_sampleDataBuffer.m_glPerfMonitorId);

            if (!oglUtils::CheckForGLError("Unable to begin the GL perf monitor."))
            {
                success = true;
            }
        }
    }

    return success;
}

bool GLGPASample::EndRequest()
{
    bool success = false;

    if (m_pGlGpaPass->IsTimingPass())
    {
        // handle timing pass
        oglUtils::_oglQueryCounter(m_sampleDataBuffer.m_gpuTimeQuery[1], GL_TIMESTAMP);

        if (!oglUtils::CheckForGLError("Unable to begin the GL timing query."))
        {
            success = true;
        }
    }
    else
    {
        // Inserting a glFlush() before and after the EndPerfMonitor call appears to make a number of the results more consistent.
        // The effects of the first glFlush() is extremely noticeable with the GLFiveQuarterQuads test and the PostZSamplesPassing counter.
        // The effects of the second glFlush() are noticeable with last draw call of the GLFiveQuarterQuads test and the PreZSamplesPassing counter.
        // The effects of the second glFlush() are also noticeable with last draw call of the GLFiveQuarterQuads test and the CBMemWritten counter.
        oglUtils::_oglFlush();

        oglUtils::_oglEndPerfMonitorAMD(m_sampleDataBuffer.m_glPerfMonitorId);

        if (!oglUtils::CheckForGLError("Unable to end the GL perf monitor."))
        {
            success = true;
        }

        oglUtils::_oglFlush();
    }

    return success;
}

void GLGPASample::ReleaseCounters()
{
    GPA_STUB_FUNCTION;
}

bool GLGPASample::CopyResults()
{
    bool success = false;

    GPASampleResult* pSampleResult = GetSampleResultLocation();

    if (m_pGlGpaPass->IsTimingPass())
    {
        // get the results
        GLuint64EXT gpuTimeResults[2];
        gpuTimeResults[0] = 0ull;
        gpuTimeResults[1] = 0ull;
        oglUtils::_oglGetQueryObjectui64vEXT(m_sampleDataBuffer.m_gpuTimeQuery[0], GL_QUERY_RESULT, &gpuTimeResults[0]);

        if (!oglUtils::CheckForGLError("Unable to get first timing data."))
        {
            oglUtils::_oglGetQueryObjectui64vEXT(m_sampleDataBuffer.m_gpuTimeQuery[1], GL_QUERY_RESULT, &gpuTimeResults[1]);

            if (!oglUtils::CheckForGLError("Unable to get second timing data."))
            {
                gpa_uint64 timingDifference = gpuTimeResults[1] - gpuTimeResults[0];
                memcpy(pSampleResult->GetAsCounterSampleResult()->GetResultBuffer(), &timingDifference, sizeof(gpa_uint64));
                success = true;
            }
        }
    }
    else
    {
        GLuint          resultsAvailable = GL_FALSE;
        GLPerfMonitorId perfMonitorId    = m_sampleDataBuffer.m_glPerfMonitorId;
        oglUtils::_oglGetPerfMonitorCounterDataAMD(perfMonitorId, GL_PERFMON_RESULT_AVAILABLE_AMD, sizeof(GLuint), &resultsAvailable, nullptr);

        if (!oglUtils::CheckForGLError("Unable to get the data."))
        {
            if (GL_TRUE == resultsAvailable)
            {
                CounterCount counterCount = m_pGlGpaPass->GetEnabledCounterCount();

                // get size of the results array
                GLuint resultSize = 0;
                oglUtils::_oglGetPerfMonitorCounterDataAMD(perfMonitorId, GL_PERFMON_RESULT_SIZE_AMD, sizeof(GLint), &resultSize, nullptr);

                if (!oglUtils::CheckForGLError("Unable to get the counter data size."))
                {
                    // obtain the actual results
                    GLuint* pCounterData = reinterpret_cast<GLuint*>(malloc(resultSize));
                    assert(nullptr != pCounterData);

                    GLsizei bytesWritten = 0;
                    oglUtils::_oglGetPerfMonitorCounterDataAMD(perfMonitorId, GL_PERFMON_RESULT_AMD, resultSize, pCounterData, &bytesWritten);

                    if (!oglUtils::CheckForGLError("Unable to get the counter data."))
                    {
                        // the returned data is structured like this:
                        // -----------------------------------------------------
                        // |  BlockID  |  CounterID  |  result data |  BlockID ...
                        // -----------------------------------------------------
                        // so it may not be in the same order it was specified

                        // cycle through all the counters and store the data
                        GLsizei wordIndex = 0;

                        for (CounterCount counterCountIter = 0; counterCountIter < counterCount; counterCountIter++)
                        {
                            // GL may return the data in a different order than expected.
                            // find the correct counter to assign the data to.
                            GLuint       groupID               = pCounterData[wordIndex++];
                            GLuint       counterID             = pCounterData[wordIndex++];
                            GLuint*      pData                 = &pCounterData[wordIndex];
                            unsigned int curCounterResultIndex = 0u;

                            const GLCounter* pGlCounter = m_pGlGpaPass->GetGLCounter(groupID, counterID, curCounterResultIndex);

                            if (nullptr != pGlCounter)
                            {
                                GLuint* pDest = reinterpret_cast<GLuint*>(&pSampleResult->GetAsCounterSampleResult()->GetResultBuffer()[curCounterResultIndex]);
                                pDest[0]      = 0;
                                pDest[1]      = 0;

                                // TODO: Revisit this
                                // None of the enabled counter data type turn out to be other than GL_UNSIGNED_INT,
                                // Letting this as it was in previous implementation
                                if (pGlCounter->m_counterType == GL_UNSIGNED_INT64_AMD)
                                {
                                    wordIndex += 2;
                                    memcpy(pDest, pData, sizeof(GLuint) * 2);
                                    success = true;
                                }
                                else if (pGlCounter->m_counterType == GL_FLOAT)
                                {
                                    wordIndex += 1;
                                    memcpy(pDest, pData, sizeof(GLfloat));
                                    success = true;
                                }
                                else if (pGlCounter->m_counterType == GL_UNSIGNED_INT)
                                {
                                    wordIndex += 1;
                                    memcpy(pDest, pData, sizeof(GLuint));
                                    success = true;
                                }
                                else if (pGlCounter->m_counterType == GL_PERCENTAGE_AMD)
                                {
                                    wordIndex += 1;
                                    memcpy(pDest, pData, sizeof(GLfloat));
                                    success = true;
                                }
                                else if (pGlCounter->m_counterType == GL_INT)
                                {
                                    wordIndex += 1;
                                    memcpy(pDest, pData, sizeof(GLint));
                                    success = true;
                                }
                                else
                                {
                                    assert(!"CounterType not recognized.");
                                }
                            }
                        }
                    }

                    free(pCounterData);
                }
            }
        }
    }

    return success;
}

bool GLGPASample::CreateGPUTimeQuery()
{
    // create the timer query
    oglUtils::_oglGenQueries(2, m_sampleDataBuffer.m_gpuTimeQuery);
    return !oglUtils::CheckForGLError("Unable to create GPU time queries.");
}

bool GLGPASample::DeleteGPUTimeQueries()
{
    bool success = false;

    // Checks added to workaround a potential driver bug. Normally, queries with nameID of 0
    // should be ignored. What is happening though is that deleting a query with name 0 is
    // marking name 0 as free so it can be used again. Subsequent calls to GenQueries will
    // return a name id of 0, which should never happen.
    if (m_sampleDataBuffer.m_gpuTimeQuery[0] != 0)
    {
        oglUtils::_oglDeleteQueries(1, &m_sampleDataBuffer.m_gpuTimeQuery[0]);
        success = !oglUtils::CheckForGLError("Unable to delete the first GPU time query.");
    }

    if (success && m_sampleDataBuffer.m_gpuTimeQuery[1] != 0)
    {
        oglUtils::_oglDeleteQueries(1, &m_sampleDataBuffer.m_gpuTimeQuery[1]);
        success = !oglUtils::CheckForGLError("Unable to delete the second GPU time query.");
    }

    m_sampleDataBuffer.m_gpuTimeQuery[0] = 0;
    m_sampleDataBuffer.m_gpuTimeQuery[1] = 0;

    return success;
}
