//==============================================================================
// Copyright (c) 2019-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief GPA API Helper class Implementation
//==============================================================================

#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <assert.h>
#include <locale>

#ifdef _WIN32
#include <codecvt>
#endif

#include "gpa_helper.h"

GPAHelper::GPAHelper()
    : m_pGpaFuncTable(nullptr)
    , m_bHeaderWritten(false)
{
}

GPAHelper::~GPAHelper()
{
    if (IsLoaded())
    {
        Unload();
    }
}

bool GPAHelper::IsLoaded() const
{
    return m_pGpaFuncTable != nullptr;
}

bool GPAHelper::Load()
{
    std::remove(GetGPALogFileName().c_str());

    bool success = GPA_STATUS_OK == GPAApiManager::Instance()->LoadApi(GPA_API_VULKAN);

    if (success)
    {
        m_pGpaFuncTable = GPAApiManager::Instance()->GetFunctionTable(GPA_API_VULKAN);
    }

    return success;
}

void GPAHelper::Unload()
{
    if (IsLoaded())
    {
        GPAApiManager::Instance()->UnloadApi(GPA_API_VULKAN);
    }

    if (ms_gpaLogFileStream.is_open())
    {
        ms_gpaLogFileStream.close();
    }

    m_pGpaFuncTable = nullptr;
}

void GPAHelper::PrintGPACounterInfo(GPA_ContextId contextId) const
{
    gpa_uint32  deviceId, revisionId;
    char        deviceName[255];
    const char* pDeviceName = deviceName;

    GPA_Status gpaStatus = m_pGpaFuncTable->GPA_GetDeviceAndRevisionId(contextId, &deviceId, &revisionId);

    if (GPA_STATUS_OK != gpaStatus)
    {
        std::cout << "ERROR: Failed to get device and revision id.\n";
        return;
    }

    gpaStatus = m_pGpaFuncTable->GPA_GetDeviceName(contextId, &pDeviceName);

    if (GPA_STATUS_OK != gpaStatus)
    {
        std::cout << "ERROR: Failed to get the device name.\n";
        return;
    }
    std::string deviceNameString(pDeviceName);

    std::cout << "Device Id: " << std::hex << deviceId << std::endl;
    std::cout << "Revision Id: " << std::hex << revisionId << std::endl;
    std::cout << "Device Name: " << deviceNameString.c_str() << std::endl;

    gpa_uint32 numCounters = 0;
    gpaStatus              = m_pGpaFuncTable->GPA_GetNumCounters(contextId, &numCounters);

    if (GPA_STATUS_OK != gpaStatus)
    {
        std::cout << "ERROR: Failed to get the number of available counters." << std::endl;
        return;
    }

    for (gpa_uint32 counterIndex = 0; counterIndex < numCounters; counterIndex++)
    {
        const char* pName      = NULL;
        GPA_Status  nameStatus = m_pGpaFuncTable->GPA_GetCounterName(contextId, counterIndex, &pName);

        const char* pGroup      = NULL;
        GPA_Status  groupStatus = m_pGpaFuncTable->GPA_GetCounterGroup(contextId, counterIndex, &pGroup);

        const char* pDescription = NULL;
        GPA_Status  descStatus   = m_pGpaFuncTable->GPA_GetCounterDescription(contextId, counterIndex, &pDescription);

        if (GPA_STATUS_OK == nameStatus && GPA_STATUS_OK == groupStatus && GPA_STATUS_OK == descStatus)
        {
            std::cout << counterIndex << ": " << pName << " \"" << pGroup << "\" - " << pDescription << std::endl;
        }
        else
        {
            std::cout << "ERROR: Failed to get counter name, group, or description." << std::endl;
        }
    }
}

std::string GPAHelper::GetExecutablePath()
{
#ifdef _WIN32
    wchar_t modulepath[GPA_MAX_PATH];
    ::GetModuleFileNameW(NULL, modulepath, _countof(modulepath));

    std::wstring moduleString(modulepath);
    size_t       lastSlashPosition = moduleString.find_last_of('\\');

    std::wstring executablePath = std::wstring(moduleString.begin(), moduleString.begin() + (lastSlashPosition + 1));

    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> wideToUtf8Converter;

    std::string utf8ExecutablePath = wideToUtf8Converter.to_bytes(executablePath);
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

    std::string utf8ExecutablePath;
	utf8ExecutablePath.append(executablePath.begin(), executablePath.end());
#endif


    return utf8ExecutablePath;
}

std::string GPAHelper::GetCSVFileName() const
{
#ifdef ANDROID
    // This path is dedicated to the app
    std::string tempString("/sdcard/Android/data/com.amd.gpa.vkcolorcube/");
    tempString.append(m_csvFileName);
    return tempString;
#else
    return GetExecutablePath().append(m_csvFileName);
#endif
}

std::string GPAHelper::GetGPALogFileName()
{
#ifdef ANDROID
    // This path is dedicated to the app
    std::string tempString("/sdcard/Android/data/com.amd.gpa.vkcolorcube/");
    tempString.append(ms_gpaLogFileName);
    return tempString;
#else
    return GetExecutablePath().append(ms_gpaLogFileName);
#endif
}

bool GPAHelper::OpenCSVFile()
{
    m_csvFile.open(GetCSVFileName().c_str(), std::ios_base::out | std::ios_base::app);
    return m_csvFile.is_open();
}

void GPAHelper::CloseCSVFile()
{
    m_csvFile.close();
}

void GPAHelper::gpaLoggingCallback(GPA_Logging_Type type, const char* msg)
{
    std::string logMessage;

    switch (type)
    {
    case GPA_LOGGING_ERROR:
        logMessage            = "GPA ERROR: ";
        ms_anyGPAErrorsLogged = true;
        break;

    case GPA_LOGGING_TRACE:
        logMessage = "GPA TRACE: ";
        break;

    default:
        logMessage = "GPA: ";
        break;
    }

    logMessage.append(msg);

    if (!ms_gpaLogFileStream.is_open())
    {
        ms_gpaLogFileStream.open(GetGPALogFileName().c_str(), std::ios_base::out | std::ios_base::app);
    }

    ms_gpaLogFileStream << logMessage << std::endl;
}

bool GPAHelper::CounterValueCompare(unsigned int sampleIndex,
                                    const char*  pCounterName,
                                    gpa_float64  counterValue,
                                    CompareType  compareType,
                                    gpa_float64  compareVal)
{
    bool              retVal = false;
    std::stringstream errorString;

    errorString << "Incorrect value for counter " << pCounterName << "(sample " << sampleIndex << "). Counter value is " << counterValue
                << ". Expected counter to be ";

    switch (compareType)
    {
    case COMPARE_TYPE_EQUAL:
        retVal = counterValue == compareVal;
        errorString << "equal to " << compareVal;
        break;

    case COMPARE_TYPE_GREATER_THAN:
        retVal = counterValue > compareVal;
        errorString << "greater than " << compareVal;
        break;

    case COMPARE_TYPE_GREATER_THAN_OR_EQUAL_TO:
        retVal = counterValue >= compareVal;
        errorString << "greater than or equal to " << compareVal;
        break;

    case COMPARE_TYPE_LESS_THAN:
        retVal = counterValue < compareVal;
        errorString << "less than " << compareVal;
        break;

    case COMPARE_TYPE_LESS_THAN_OR_EQUAL_TO:
        retVal = counterValue <= compareVal;
        errorString << "less than or equal to " << compareVal;
        break;
    }

    if (!retVal)
    {
        gpaLoggingCallback(GPA_LOGGING_ERROR, errorString.str().c_str());
    }

    return retVal;
}

bool GPAHelper::ValidateData(unsigned int sampleIndex, const char* pCounterName, gpa_float64 counterValue, GPA_Usage_Type counterUsageType)
{
    bool retVal = true;

    std::string counterName(pCounterName);

    if (GPA_USAGE_TYPE_PERCENTAGE == counterUsageType)
    {
        retVal = CounterValueCompare(sampleIndex, pCounterName, counterValue, COMPARE_TYPE_GREATER_THAN_OR_EQUAL_TO, 0.0f) &&
            CounterValueCompare(sampleIndex, pCounterName, counterValue, COMPARE_TYPE_LESS_THAN_OR_EQUAL_TO, 100.0f);
    }

    if (retVal)
    {
        if (0 == counterName.compare("GPUTime"))
        {
            retVal = CounterValueCompare(sampleIndex, pCounterName, counterValue, COMPARE_TYPE_GREATER_THAN, 0.0f);
        }
        else if (0 == counterName.compare("GPUBusy"))
        {
            retVal = CounterValueCompare(sampleIndex, pCounterName, counterValue, COMPARE_TYPE_GREATER_THAN, 0.0f) &
                CounterValueCompare(sampleIndex, pCounterName, counterValue, COMPARE_TYPE_LESS_THAN_OR_EQUAL_TO, 100.0f);
        }
        /* temporarily disable additional counter validation
        else if (0 == counterName.compare("VSBusy"))
        {
            retVal = CounterValueCompare(sampleIndex, pCounterName, counterValue, COMPARE_TYPE_GREATER_THAN, 0.0f) &
                CounterValueCompare(sampleIndex, pCounterName, counterValue, COMPARE_TYPE_LESS_THAN_OR_EQUAL_TO, 100.0f);
        }
        else if (0 == counterName.compare("VSTime"))
        {
            retVal = CounterValueCompare(sampleIndex, pCounterName, counterValue, COMPARE_TYPE_GREATER_THAN, 0.0f);
        }
        else if (0 == counterName.compare("PSBusy"))
        {
            retVal = CounterValueCompare(sampleIndex, pCounterName, counterValue, COMPARE_TYPE_GREATER_THAN, 0.0f) &
                CounterValueCompare(sampleIndex, pCounterName, counterValue, COMPARE_TYPE_LESS_THAN_OR_EQUAL_TO, 100.0f);
        }
        else if (0 == counterName.compare("PSTime"))
        {
            retVal = CounterValueCompare(sampleIndex, pCounterName, counterValue, COMPARE_TYPE_GREATER_THAN, 0.0f);
        }
        else if (0 == counterName.compare("VSVerticesIn"))
        {
            gpa_float64 expectedVsVerticesIn = 36;

            if (2 == sampleIndex)
            {
                expectedVsVerticesIn = 72;
            }

            retVal = CounterValueCompare(sampleIndex, pCounterName, counterValue, COMPARE_TYPE_EQUAL, expectedVsVerticesIn);
        }
        else if (0 == counterName.compare("PSPixelsOut"))
        {
            gpa_float64 expectedPsPixelsOut = 11662;

            if (1 == sampleIndex)
            {
                expectedPsPixelsOut = 2820;
            }
            else if (2 == sampleIndex)
            {
                expectedPsPixelsOut = 14482;
            }

            retVal = CounterValueCompare(sampleIndex, pCounterName, counterValue, COMPARE_TYPE_GREATER_THAN_OR_EQUAL_TO, expectedPsPixelsOut);
        }
        else if (0 == counterName.compare("PrimitivesIn"))
        {
            gpa_float64 expectedPrimiteivesIn = 12;

            if (2 == sampleIndex)
            {
                expectedPrimiteivesIn = 24;
            }

            retVal = CounterValueCompare(sampleIndex, pCounterName, counterValue, COMPARE_TYPE_EQUAL, expectedPrimiteivesIn);
        }
        */
    }

    return retVal;
}

void GPAHelper::PrintGPASampleResults(GPA_ContextId contextId, GPA_SessionId sessionId, gpa_uint32 sampleId, bool outputToConsole, bool verifyCounters)
{
    gpa_uint32  deviceId, revisionId;
    char        deviceName[255];
    const char* pDeviceName = deviceName;

    GPA_Status gpaStatus = m_pGpaFuncTable->GPA_GetDeviceAndRevisionId(contextId, &deviceId, &revisionId);

    if (GPA_STATUS_OK != gpaStatus)
    {
        std::cout << "ERROR: Failed to get device and revision id.\n";
        return;
    }

    gpaStatus = m_pGpaFuncTable->GPA_GetDeviceName(contextId, &pDeviceName);

    if (GPA_STATUS_OK != gpaStatus)
    {
        std::cout << "ERROR: Failed to get the device name.\n";
        return;
    }

    std::string deviceNameString(pDeviceName);

    if (outputToConsole)
    {
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Device Id: " << std::hex << deviceId << std::endl;
        std::cout << "Revision Id: " << std::hex << revisionId << std::endl;
        std::cout << "Device Name: " << deviceNameString.c_str() << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "Sample ID: " << sampleId << std::endl;
    }

    std::stringstream csvHeader;

    csvHeader << "Device Id: " << std::hex << deviceId << std::endl;
    csvHeader << "Revision Id: " << std::hex << revisionId << std::endl;
    csvHeader << "Device Name: " << deviceNameString.c_str() << std::endl;

    size_t sampleResultSizeInBytes = 0;
    gpaStatus                      = m_pGpaFuncTable->GPA_GetSampleResultSize(sessionId, sampleId, &sampleResultSizeInBytes);

    if (GPA_STATUS_OK != gpaStatus)
    {
        std::cout << "ERROR: Failed to get GPA sample result size." << std::endl;
        return;
    }

    gpa_uint64* pResultsBuffer = (gpa_uint64*)malloc(sampleResultSizeInBytes);

    if (pResultsBuffer == nullptr)
    {
        std::cout << "ERROR: Failed to allocate memory for GPA results." << std::endl;
        return;
    }

    gpaStatus = m_pGpaFuncTable->GPA_GetSampleResult(sessionId, sampleId, sampleResultSizeInBytes, pResultsBuffer);

    if (GPA_STATUS_OK != gpaStatus)
    {
        std::cout << "ERROR: Failed to get GPA sample results." << std::endl;
    }
    else
    {
        gpa_uint32 enabledCount = 0;
        gpaStatus               = m_pGpaFuncTable->GPA_GetNumEnabledCounters(sessionId, &enabledCount);

        if (GPA_STATUS_OK != gpaStatus)
        {
            std::cout << "ERROR: Failed to get the number of enabled counters from GPA." << std::endl;
        }
        else
        {
            std::stringstream csvContent;

            for (gpa_uint32 i = 0; i < enabledCount; i++)
            {
                gpa_uint32 counterIndex = 0;
                gpaStatus               = m_pGpaFuncTable->GPA_GetEnabledIndex(sessionId, i, &counterIndex);

                if (GPA_STATUS_OK != gpaStatus)
                {
                    std::cout << "ERROR: Failed to get the exposed GPA counter id of the enabled counter at index " << counterIndex << "." << std::endl;
                }
                else
                {
                    GPA_Data_Type counterType = GPA_DATA_TYPE_UINT64;
                    gpaStatus                 = m_pGpaFuncTable->GPA_GetCounterDataType(contextId, counterIndex, &counterType);
                    assert(GPA_STATUS_OK == gpaStatus);

                    const char* pCounterName = NULL;
                    gpaStatus                = m_pGpaFuncTable->GPA_GetCounterName(contextId, counterIndex, &pCounterName);
                    assert(GPA_STATUS_OK == gpaStatus);

                    GPA_Usage_Type counterUsageType = GPA_USAGE_TYPE__LAST;
                    gpaStatus = m_pGpaFuncTable->GPA_GetCounterUsageType(contextId, counterIndex, &counterUsageType);
                    assert(GPA_STATUS_OK == gpaStatus);

                    if (outputToConsole)
                    {
                        printf("Counter %u %s result: ", counterIndex, pCounterName);
                    }

                    if (m_csvFile.is_open() && !m_bHeaderWritten)
                    {
                        csvHeader << pCounterName << ",";
                    }

                    if (counterType == GPA_DATA_TYPE_UINT64)
                    {
                        if (outputToConsole)
                        {
                            printf("%llu\n", pResultsBuffer[i]);
                        }

                        if (m_csvFile.is_open())
                        {
                            csvContent << pResultsBuffer[i] << ",";
                        }

                        if (verifyCounters)
                        {
                            ValidateData(sampleId, pCounterName, static_cast<gpa_float64>(pResultsBuffer[i]), counterUsageType);
                        }
                    }
                    else if (counterType == GPA_DATA_TYPE_FLOAT64)
                    {
                        gpa_float64 fResult = ((gpa_float64*)pResultsBuffer)[i];

                        if (outputToConsole)
                        {
                            printf("%f\n", fResult);
                        }

                        if (m_csvFile.is_open())
                        {
                            csvContent << fResult << ",";
                        }

                        if (verifyCounters)
                        {
                            ValidateData(sampleId, pCounterName, fResult, counterUsageType);
                        }
                    }
                    else
                    {
                        if (outputToConsole)
                        {
                            printf("unhandled type (%d).\n", counterType);
                        }

                        if (m_csvFile.is_open())
                        {
                            csvContent << "unhandled type,";
                        }
                    }
                }
            }

            // Output the counter results to the csv file
            if (m_csvFile.is_open())
            {
                if (!m_bHeaderWritten)
                {
                    m_csvFile << csvHeader.str() << std::endl;
                    m_bHeaderWritten = true;
                }

                m_csvFile << csvContent.str() << std::endl;
            }
        }
    }

    free(pResultsBuffer);
}
