//==============================================================================
// Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA Helper class implementation
//==============================================================================

#include "GPAHelper.h"
#include <chrono>
#include <thread>

GPAApiManager*    GPAApiManager::m_pGpaApiManager = nullptr;
GPAHelper*        GPAHelper::m_pGpaHelper         = nullptr;
GPAFuncTableInfo* g_pFuncTableInfo                = nullptr;

GPAHelper* GPAHelper::Instance()
{
    if (nullptr == m_pGpaHelper)
    {
        m_pGpaHelper = new (std::nothrow) GPAHelper();
    }

    return m_pGpaHelper;
}

void GPALogger(GPA_Logging_Type logType, const char* logMsg)
{
    std::string logMessage;

    switch (logType)
    {
    case GPA_LOGGING_ERROR:
        logMessage                           = "GPA ERROR: ";
        GPAHelper::Instance()->m_anyGpaError = true;
        break;

    case GPA_LOGGING_TRACE:
        logMessage = "GPA TRACE: ";
        break;

    default:
        logMessage = "GPA: ";
        break;
    }

    if (static_cast<unsigned int>(logType) == static_cast<unsigned int>(GL_ERROR))
    {
        logMessage.clear();
        logMessage = "GL ERROR: ";
    }

    if (static_cast<unsigned int>(logType) == static_cast<unsigned int>(WIN_ERROR))
    {
        logMessage.clear();
        logMessage = "WINDOWS ERROR: ";
    }

    if (static_cast<unsigned int>(logType) == static_cast<unsigned int>(X_SERVER_ERROR))
    {
        logMessage.clear();
        logMessage = "X SERVER ERROR: ";
    }

    logMessage.append(logMsg);

    if (!GPAHelper::Instance()->m_gpaLogFileStream.is_open())
    {
        GPAHelper::Instance()->m_gpaLogFileStream.open(GPAHelper::Instance()->m_gpaLogFileName.c_str(), std::ios_base::out | std::ios_base::app);
    }

    GPAHelper::Instance()->m_gpaLogFileStream << logMessage << std::endl;
}

bool GPAHelper::SetUpGPA()
{
    bool success = GPA_STATUS_OK == GPAApiManager::Instance()->LoadApi(GPA_API_OPENGL);

    if (success)
    {
        m_pGpaFuncTable = GPAApiManager::Instance()->GetFunctionTable(GPA_API_OPENGL);

        if (nullptr != m_pGpaFuncTable)
        {
            m_pGpaFuncTable->GPA_RegisterLoggingCallback(GPA_LOGGING_ERROR, GPALogger);
            success = GPA_STATUS_OK == m_pGpaFuncTable->GPA_Initialize(GPA_INITIALIZE_DEFAULT_BIT);
        }
    }

#ifdef _WIN32
    wchar_t modulepath[GPA_MAX_PATH];
    ::GetModuleFileNameW(NULL, modulepath, _countof(modulepath));

    std::wstring moduleString(modulepath);
    size_t       lastSlashPosition = moduleString.find_last_of('\\');

    std::wstring executablePath = std::wstring(moduleString.begin(), moduleString.begin() + (lastSlashPosition + 1));
#else
    int  len;
    char modulepath[GPA_MAX_PATH];
    len = readlink("/proc/self/exe", modulepath, GPA_MAX_PATH - 1);

    if (len != -1)
    {
        modulepath[len] = '\0';
    }

    std::string moduleString(modulepath);
    size_t      lastSlashPosition = moduleString.find_last_of('/');

    std::string executablePath(modulepath);

    if (std::string::npos != lastSlashPosition)
    {
        executablePath = std::string(moduleString.begin(), moduleString.begin() + (lastSlashPosition + 1));
    }

#endif

    m_counterFileName = std::string(executablePath.begin(), executablePath.end()).append(m_counterFileName);
    m_gpaLogFileName  = std::string(executablePath.begin(), executablePath.end()).append(m_gpaLogFileName);
    std::remove(m_counterFileName.c_str());
    std::remove(m_gpaLogFileName.c_str());
    m_counterDataFileStream.open(m_counterFileName.c_str(), std::ios_base::out | std::ios_base::app);

    return success;
}

bool GPAHelper::OpenContext(GLContext glContext, bool includeHwCounters)
{
    GPA_OpenContextFlags openContextFlags = includeHwCounters ? GPA_OPENCONTEXT_ENABLE_HARDWARE_COUNTERS_BIT : GPA_OPENCONTEXT_DEFAULT_BIT;

    bool success = GPA_STATUS_OK == m_pGpaFuncTable->GPA_OpenContext(glContext, openContextFlags, &m_gpaContextId);

    return success;
}

bool GPAHelper::CloseContext()
{
    bool success   = true;
    success        = GPA_STATUS_OK == m_pGpaFuncTable->GPA_CloseContext(m_gpaContextId);
    m_gpaContextId = nullptr;
    return success;
}

bool GPAHelper::CreateGpaSession()
{
    return GPA_STATUS_OK == m_pGpaFuncTable->GPA_CreateSession(m_gpaContextId, GPA_SESSION_SAMPLE_TYPE_DISCRETE_COUNTER, &m_gpaSessionId);
}

bool GPAHelper::DestroyGpaSession()
{
    bool success   = true;
    success        = GPA_STATUS_OK == m_pGpaFuncTable->GPA_DeleteSession(m_gpaSessionId);
    m_gpaSessionId = nullptr;
    return success;
}

bool GPAHelper::EnableAllCounters()
{
    bool success = GPA_STATUS_OK == m_pGpaFuncTable->GPA_EnableAllCounters(m_gpaSessionId);
    success      = success && GPA_STATUS_OK == m_pGpaFuncTable->GPA_GetPassCount(m_gpaSessionId, &m_numOfPassReq);
    return success;
}

bool GPAHelper::EnableCounterByName(const char* pName)
{
    bool success = GPA_STATUS_OK == m_pGpaFuncTable->GPA_EnableCounterByName(m_gpaSessionId, pName);
    success = success && GPA_STATUS_OK == m_pGpaFuncTable->GPA_GetPassCount(m_gpaSessionId, &m_numOfPassReq);
    return success;
}

bool GPAHelper::OnGpaSessionStart()
{
    m_currentPassIndex = -1;
    m_gpaCommandListId = nullptr;
    m_samples.clear();
    return GPA_STATUS_OK == m_pGpaFuncTable->GPA_BeginSession(m_gpaSessionId);
}

bool GPAHelper::OnGpaSessionEnd()
{
    return GPA_STATUS_OK == m_pGpaFuncTable->GPA_EndSession(m_gpaSessionId);
}

bool GPAHelper::OnPassStart()
{
    m_currentPassIndex++;
    m_sampleCounter = -1;
    m_samples.clear();
    bool success = true;

    if (nullptr == m_gpaCommandListId)
    {
        success = GPA_STATUS_OK ==
                  m_pGpaFuncTable->GPA_BeginCommandList(m_gpaSessionId, m_currentPassIndex, GPA_NULL_COMMAND_LIST, GPA_COMMAND_LIST_NONE, &m_gpaCommandListId);
    }

    return success;
}

bool GPAHelper::OnPassEnd()
{
    bool success = true;

    if (nullptr != m_pGpaFuncTable && nullptr != m_gpaSessionId)
    {
        success                  = GPA_STATUS_OK == m_pGpaFuncTable->GPA_EndCommandList(m_gpaCommandListId);
        bool           isReady   = false;
        const uint32_t timeout   = 10000;  // ms
        auto           startTime = std::chrono::high_resolution_clock::now();

        do
        {
            isReady = GPA_STATUS_OK == m_pGpaFuncTable->GPA_IsPassComplete(m_gpaSessionId, m_currentPassIndex);

            if (!isReady)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(0));

                auto                                      endTime     = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsedTime = endTime - startTime;

                if (elapsedTime.count() > timeout)
                {
                    success = false;
                    break;
                }
            }
        } while (!isReady);
    }

    m_gpaCommandListId = nullptr;
    return success;
    ;
}

bool GPAHelper::BeginSample()
{
    bool success = true;
    m_sampleCounter++;

    success = GPA_STATUS_OK == m_pGpaFuncTable->GPA_BeginSample(m_sampleCounter, m_gpaCommandListId);
    m_samples.push_back(m_sampleCounter);
    return success;
}

bool GPAHelper::EndSample()
{
    bool success = true;
    success      = GPA_STATUS_OK == m_pGpaFuncTable->GPA_EndSample(m_gpaCommandListId);
    return success;
}

bool GPAHelper::PrintGPASampleResults(bool verify)
{
    gpa_uint32 sampleCount         = 0u;
    GPA_Status status              = m_pGpaFuncTable->GPA_GetSampleCount(m_gpaSessionId, &sampleCount);
    bool       success             = GPA_STATUS_OK == status;
    bool       verificationSuccess = true;

    for (std::vector<unsigned int>::iterator sampleIter = m_samples.begin(); sampleIter != m_samples.end(); ++sampleIter)
    {
        if (success && sampleCount == m_samples.size())
        {
            size_t sampleDataSize = 0u;
            success               = GPA_STATUS_OK == m_pGpaFuncTable->GPA_GetSampleResultSize(m_gpaSessionId, *sampleIter, &sampleDataSize);

            void* pSampleResult = malloc(sampleDataSize);

            success = success && GPA_STATUS_OK == m_pGpaFuncTable->GPA_GetSampleResult(m_gpaSessionId, *sampleIter, sampleDataSize, pSampleResult);

            if (nullptr != pSampleResult)
            {
                gpa_uint32 numEnabledCounters = 0;
                success = success && GPA_STATUS_OK == m_pGpaFuncTable->GPA_GetNumEnabledCounters(m_gpaSessionId, &numEnabledCounters);

                for (gpa_uint32 i = 0; i < numEnabledCounters; i++)
                {
                    // printf("Counter %u %s result: ", counterIter->m_counterIndex, counterIter->m_counterName);
                    gpa_uint32 enabledIndex = 0;
                    success = success && GPA_STATUS_OK == m_pGpaFuncTable->GPA_GetEnabledIndex(m_gpaSessionId, i, &enabledIndex);

                    const char* pCounterName = nullptr;
                    success = success && GPA_STATUS_OK == m_pGpaFuncTable->GPA_GetCounterName(m_gpaContextId, enabledIndex, &pCounterName);

                    if (!m_isHeaderWritten)
                    {
                        m_header << pCounterName << ",";
                    }

                    GPA_Usage_Type usageType = GPA_USAGE_TYPE__LAST;
                    success = success && GPA_STATUS_OK == m_pGpaFuncTable->GPA_GetCounterUsageType(m_gpaContextId, enabledIndex, &usageType);

                    GPA_Data_Type dataType = GPA_DATA_TYPE_FLOAT64;
                    success = success && GPA_STATUS_OK == m_pGpaFuncTable->GPA_GetCounterDataType(m_gpaContextId, enabledIndex, &dataType);

                    gpa_float64 fResult = 0.0f;

                    if (dataType == GPA_DATA_TYPE_UINT64)
                    {
                        gpa_uint64 result           = reinterpret_cast<gpa_uint64*>(pSampleResult)[i];
                        fResult = static_cast<gpa_float64>(result);
                        m_content << result << ",";
                        //printf("%llu\n", result);
                    }
                    else if (dataType == GPA_DATA_TYPE_FLOAT64)
                    {
                        fResult         = reinterpret_cast<gpa_float64*>(pSampleResult)[i];
                        m_content << fResult << ",";
                        /*printf("%f\n", fResult);*/
                    }

                    if (verify)
                    {
                        verificationSuccess = true;
                        std::stringstream errorString;
                        errorString << "Incorrect value for counter ";
                        std::string counterName(pCounterName);

                        if (GPA_USAGE_TYPE_PERCENTAGE == usageType)
                        {
                            verificationSuccess &= (fResult >= 0.0f && fResult <= 100.0f);

                            if (!verificationSuccess)
                            {
                                errorString << pCounterName << " Counter Value is " << fResult
                                    << ". Expected counter value to be in interval [0.0f,100.0f]";
                                GPALogger(GPA_LOGGING_ERROR, errorString.str().c_str());
                            }
                        }

                        if (counterName == "GPUTime")
                        {
                            verificationSuccess &= fResult > 0.0f;

                            if (!verificationSuccess)
                            {
                                errorString << "GPUTime. Counter Value is " << fResult
                                            << ". Expected counter value to be greater than 0.0f";
                                GPALogger(GPA_LOGGING_ERROR, errorString.str().c_str());
                            }
                        }
                        else if (counterName == "GPUBusy")
                        {
                            verificationSuccess &= (fResult > 0.0f && fResult <= 100.0f);

                            if (!verificationSuccess)
                            {
                                errorString << "GPUBusy. Counter Value is " << fResult
                                            << ". Expected counter value to be in interval [0.0f,100.0f]";
                                GPALogger(GPA_LOGGING_ERROR, errorString.str().c_str());
                            }
                        }
                        else if (counterName == "PSBusy")
                        {
                            verificationSuccess &= (fResult > 0.0f);

                            if (!verificationSuccess)
                            {
                                errorString << "PSBusy. Counter Value is " << fResult << ". Expected counter value to be greater than 0.0f";
                                GPALogger(GPA_LOGGING_ERROR, errorString.str().c_str());
                            }
                        }
                    }
                }

                if (m_counterDataFileStream.is_open())
                {
                    if (!m_isHeaderWritten)
                    {
                        m_counterDataFileStream << "Frame"
                                                << "," << m_header.str() << std::endl;
                        m_isHeaderWritten = true;
                    }

                    m_counterDataFileStream << m_frameCounter << "," << m_content.str() << std::endl;
                    m_content.str(std::string());
                    m_header.str(std::string());
                }
            }

            free(pSampleResult);
        }
    }

    return verificationSuccess;
}

unsigned int GPAHelper::GetPassRequired() const
{
    return m_numOfPassReq;
}

void GPAHelper::IncrementFrameCounter()
{
    ++m_frameCounter;
}

unsigned GPAHelper::GetCurrentFrameCount() const
{
    return m_frameCounter;
}

GPAHelper::~GPAHelper()
{
    m_gpaLogFileStream.close();
    m_counterDataFileStream.close();
    m_pGpaFuncTable->GPA_Destroy();
}

GPAHelper::GPAHelper()
    : m_anyGpaError(false)
    , m_pGpaFuncTable(nullptr)
    , m_gpaContextId(nullptr)
    , m_gpaSessionId(nullptr)
    , m_gpaCommandListId(nullptr)
    , m_numOfPassReq(0u)
    , m_currentPassIndex(0u)
{
}
