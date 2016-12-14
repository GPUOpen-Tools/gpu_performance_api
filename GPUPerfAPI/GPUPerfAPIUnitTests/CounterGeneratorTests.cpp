//==============================================================================
// Copyright (c) 2012-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Helper functions for Counter Generator Unit Tests
//==============================================================================

#include "CounterGeneratorTests.h"
#include "GPAHWInfo.h"
#include "GPAContextState.h"
#include <map>

void VerifyNotImplemented(GPA_API_Type api, unsigned int deviceId)
{
    HMODULE hDll = LoadLibraryA("GPUPerfAPICounters" AMDT_PROJECT_SUFFIX ".dll");
    ASSERT_NE((HMODULE)nullptr, hDll);

    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetProcAddress(hDll, "GPA_GetAvailableCounters");
    ASSERT_NE((GPA_GetAvailableCountersProc)nullptr, GPA_GetAvailableCounters_fn);

    GPA_ICounterAccessor* pCounterAccessor = nullptr;
    GPA_ICounterScheduler* pCounterScheduler = nullptr;
    GPA_Status status = GPA_GetAvailableCounters_fn(api, AMD_VENDOR_ID, deviceId, 0, &pCounterAccessor, &pCounterScheduler);
    EXPECT_EQ(GPA_STATUS_ERROR_NOT_FOUND, status);

    BOOL freed = FreeLibrary(hDll);
    EXPECT_EQ(TRUE, freed);
}

void VerifyNotImplemented(GPA_API_Type api, GPA_HW_GENERATION generation)
{
    HMODULE hDll = LoadLibraryA("GPUPerfAPICounters" AMDT_PROJECT_SUFFIX ".dll");
    ASSERT_NE((HMODULE)nullptr, hDll);

    GPA_GetAvailableCountersByGenerationProc GPA_GetAvailableCountersByGeneration_fn = (GPA_GetAvailableCountersByGenerationProc)GetProcAddress(hDll, "GPA_GetAvailableCountersByGeneration");
    ASSERT_NE((GPA_GetAvailableCountersByGenerationProc)nullptr, GPA_GetAvailableCountersByGeneration_fn);

    GPA_ICounterAccessor* pCounterAccessor = nullptr;
    GPA_Status status = GPA_GetAvailableCountersByGeneration_fn(api, generation, &pCounterAccessor);
    EXPECT_EQ(GPA_STATUS_ERROR_NOT_FOUND, status);

    BOOL freed = FreeLibrary(hDll);
    EXPECT_EQ(TRUE, freed);
}

void VerifyHardwareNotSupported(GPA_API_Type api, unsigned int deviceId)
{
    HMODULE hDll = LoadLibraryA("GPUPerfAPICounters" AMDT_PROJECT_SUFFIX ".dll");
    ASSERT_NE((HMODULE)nullptr, hDll);
    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetProcAddress(hDll, "GPA_GetAvailableCounters");
    ASSERT_NE((GPA_GetAvailableCountersProc)nullptr, GPA_GetAvailableCounters_fn);

    GPA_ICounterAccessor* pCounterAccessor = nullptr;
    GPA_ICounterScheduler* pCounterScheduler = nullptr;
    GPA_Status status = GPA_GetAvailableCounters_fn(api, AMD_VENDOR_ID, deviceId, 0, &pCounterAccessor, &pCounterScheduler);
    EXPECT_EQ(GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED, status);
    EXPECT_EQ(nullptr, pCounterAccessor);
    EXPECT_EQ(nullptr, pCounterScheduler);

    BOOL freed = FreeLibrary(hDll);
    EXPECT_EQ(TRUE, freed);
}

void VerifyHardwareNotSupported(GPA_API_Type api, GPA_HW_GENERATION generation)
{
    HMODULE hDll = LoadLibraryA("GPUPerfAPICounters" AMDT_PROJECT_SUFFIX ".dll");
    ASSERT_NE((HMODULE)nullptr, hDll);

    GPA_GetAvailableCountersByGenerationProc GPA_GetAvailableCountersByGeneration_fn = (GPA_GetAvailableCountersByGenerationProc)GetProcAddress(hDll, "GPA_GetAvailableCountersByGeneration");
    ASSERT_NE((GPA_GetAvailableCountersByGenerationProc)nullptr, GPA_GetAvailableCountersByGeneration_fn);

    GPA_ICounterAccessor* pCounterAccessor = nullptr;
    GPA_Status status = GPA_GetAvailableCountersByGeneration_fn(api, generation, &pCounterAccessor);
    EXPECT_EQ(GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED, status);
    EXPECT_EQ(nullptr, pCounterAccessor);

    BOOL freed = FreeLibrary(hDll);
    EXPECT_EQ(TRUE, freed);
}

void VerifyCounterNames(GPA_API_Type api, unsigned int deviceId, std::vector<const char*> expectedNames)
{
    HMODULE hDll = LoadLibraryA("GPUPerfAPICounters" AMDT_PROJECT_SUFFIX ".dll");
    ASSERT_NE((HMODULE)nullptr, hDll);

    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetProcAddress(hDll, "GPA_GetAvailableCounters");
    ASSERT_NE((GPA_GetAvailableCountersProc)nullptr, GPA_GetAvailableCounters_fn);

    GPA_ICounterAccessor* pCounterAccessor = nullptr;
    GPA_ICounterScheduler* pCounterScheduler = nullptr;
    GPA_Status status = GPA_GetAvailableCounters_fn(api, AMD_VENDOR_ID, deviceId, 0, &pCounterAccessor, &pCounterScheduler);
    EXPECT_EQ(GPA_STATUS_OK, status);
    EXPECT_NE((GPA_ICounterAccessor*)nullptr, pCounterAccessor);
    EXPECT_NE((GPA_ICounterScheduler*)nullptr, pCounterScheduler);

    size_t numCounters = pCounterAccessor->GetNumCounters();
    EXPECT_EQ(expectedNames.size(), numCounters);

    // verify as many counter names as possible.
    numCounters = min(expectedNames.size(), numCounters);

#ifdef AMDT_INTERNAL

    for (unsigned int i = 0; i < numCounters; ++i)
    {
        const char* pCounterName = pCounterAccessor->GetCounterName(i);
        EXPECT_STREQ(expectedNames[i], pCounterName);

        if (strcmp(expectedNames[i], pCounterName) != 0)
        {
            printf("Counter names are different at index %d: expected %s, got %s\n", i, expectedNames[i], pCounterName);
        }

        const char* pDesc = pCounterAccessor->GetCounterDescription(i);
        EXPECT_NE((const char*)nullptr, pDesc);
        EXPECT_NE("", pDesc);

        // the format of the description should be "#GROUP#counter description", so make sure the description starts with '#'
        EXPECT_EQ('#', pDesc[0]);
    }

#else // not AMDT_INTERNAL

    if (expectedNames.size() == numCounters)
    {
        for (unsigned int i = 0; i < numCounters; ++i)
        {
            const char* pCounterName = pCounterAccessor->GetCounterName(i);
            EXPECT_STREQ(expectedNames[i], pCounterName);

            const char* pDesc = pCounterAccessor->GetCounterDescription(i);
            EXPECT_NE((const char*)nullptr, pDesc);
            EXPECT_NE("", pDesc);

            // the format of the description should be "#GROUP#counter description", so make sure the description starts with '#'
            EXPECT_EQ('#', pDesc[0]);
        }
    }

#endif // AMDT_INTERNAL

    BOOL freed = FreeLibrary(hDll);
    EXPECT_EQ(TRUE, freed);
}

void VerifyCounterNames(GPA_API_Type api, GPA_HW_GENERATION generation, std::vector<const char*> expectedNames)
{
    HMODULE hDll = LoadLibraryA("GPUPerfAPICounters" AMDT_PROJECT_SUFFIX ".dll");
    ASSERT_NE((HMODULE)nullptr, hDll);

    GPA_GetAvailableCountersByGenerationProc GPA_GetAvailableCountersByGeneration_fn = (GPA_GetAvailableCountersByGenerationProc)GetProcAddress(hDll, "GPA_GetAvailableCountersByGeneration");
    ASSERT_NE((GPA_GetAvailableCountersByGenerationProc)nullptr, GPA_GetAvailableCountersByGeneration_fn);

    GPA_ICounterAccessor* pCounterAccessor = nullptr;
    GPA_Status status = GPA_GetAvailableCountersByGeneration_fn(api, generation, &pCounterAccessor);
    EXPECT_EQ(GPA_STATUS_OK, status);
    EXPECT_NE((GPA_ICounterAccessor*)nullptr, pCounterAccessor);

    size_t numCounters = pCounterAccessor->GetNumCounters();
    EXPECT_EQ(expectedNames.size(), numCounters);

    // verify as many counter names as possible.
    numCounters = min(expectedNames.size(), numCounters);

#ifdef AMDT_INTERNAL

    for (unsigned int i = 0; i < numCounters; ++i)
    {
        const char* pCounterName = pCounterAccessor->GetCounterName(i);
        EXPECT_STREQ(expectedNames[i], pCounterName);

        if (strcmp(expectedNames[i], pCounterName) != 0)
        {
            printf("Counter names are different at index %d: expected %s, got %s\n", i, expectedNames[i], pCounterName);
        }

        const char* pDesc = pCounterAccessor->GetCounterDescription(i);
        EXPECT_NE((const char*)nullptr, pDesc);
        EXPECT_NE("", pDesc);

        // the format of the description should be "#GROUP#counter description", so make sure the description starts with '#'
        EXPECT_EQ('#', pDesc[0]);
    }

#else // not AMDT_INTERNAL

    if (expectedNames.size() == numCounters)
    {
        for (unsigned int i = 0; i < numCounters; ++i)
        {
            const char* pCounterName = pCounterAccessor->GetCounterName(i);
            EXPECT_STREQ(expectedNames[i], pCounterName);

            const char* pDesc = pCounterAccessor->GetCounterDescription(i);
            EXPECT_NE((const char*)nullptr, pDesc);
            EXPECT_NE("", pDesc);

            // the format of the description should be "#GROUP#counter description", so make sure the description starts with '#'
            EXPECT_EQ('#', pDesc[0]);
        }
    }

#endif // AMDT_INTERNAL

    BOOL freed = FreeLibrary(hDll);
    EXPECT_EQ(TRUE, freed);
}


void VerifyPassCount(GPA_API_Type api, unsigned int deviceId, std::vector<unsigned int> countersToEnable, unsigned int expectedNumPasses)
{
    HMODULE hDll = LoadLibraryA("GPUPerfAPICounters" AMDT_PROJECT_SUFFIX ".dll");
    ASSERT_NE((HMODULE)nullptr, hDll);

    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetProcAddress(hDll, "GPA_GetAvailableCounters");
    ASSERT_NE((GPA_GetAvailableCountersProc)nullptr, GPA_GetAvailableCounters_fn);

    GPA_ICounterAccessor* pCounterAccessor = nullptr;
    GPA_ICounterScheduler* pCounterScheduler = nullptr;
    GPA_Status status = GPA_GetAvailableCounters_fn(api, AMD_VENDOR_ID, deviceId, 0, &pCounterAccessor, &pCounterScheduler);
    EXPECT_EQ(GPA_STATUS_OK, status);
    EXPECT_NE((GPA_ICounterAccessor*)nullptr, pCounterAccessor);
    ASSERT_NE((GPA_ICounterScheduler*)nullptr, pCounterScheduler);

    pCounterScheduler->DisableAllCounters();

    for (unsigned int i = 0; i < countersToEnable.size(); ++i)
    {
        GPA_Status enabled = pCounterScheduler->EnableCounter(countersToEnable[i]);
        EXPECT_EQ(GPA_STATUS_OK, enabled);
    }

    gpa_uint32 requiredPasses = 0;
    GPA_Status passCountStatus = pCounterScheduler->GetNumRequiredPasses(&requiredPasses);
    EXPECT_EQ(GPA_STATUS_OK, passCountStatus);
    EXPECT_EQ(expectedNumPasses, requiredPasses);

    // disable the counters
    pCounterScheduler->DisableAllCounters();
}

void VerifyCountersInPass(GPA_API_Type api,
                          unsigned int deviceId,
                          std::vector<unsigned int> countersToEnable,
                          std::vector< std::vector<unsigned int> >& expectedHwCountersPerPass,
                          std::map< unsigned int, std::map<unsigned int, GPA_CounterResultLocation> >& expectedResultLocations)
{
    HMODULE hDll = LoadLibraryA("GPUPerfAPICounters" AMDT_PROJECT_SUFFIX ".dll");
    ASSERT_NE((HMODULE)nullptr, hDll);

    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetProcAddress(hDll, "GPA_GetAvailableCounters");
    ASSERT_NE((GPA_GetAvailableCountersProc)nullptr, GPA_GetAvailableCounters_fn);

    GPA_ICounterAccessor* pCounterAccessor = nullptr;
    GPA_ICounterScheduler* pCounterScheduler = nullptr;

    // Get all the counters (based on API and the deviceID), an accessor, and a scheduler
    GPA_Status status = GPA_GetAvailableCounters_fn(api, AMD_VENDOR_ID, deviceId, 0, &pCounterAccessor, &pCounterScheduler);

    EXPECT_EQ(GPA_STATUS_OK, status);
    EXPECT_NE((GPA_ICounterAccessor*)nullptr, pCounterAccessor);
    ASSERT_NE((GPA_ICounterScheduler*)nullptr, pCounterScheduler);

    pCounterScheduler->DisableAllCounters();

    for (unsigned int i = 0; i < countersToEnable.size(); ++i)
    {
        GPA_Status enabled = pCounterScheduler->EnableCounter(countersToEnable[i]);
        EXPECT_EQ(GPA_STATUS_OK, enabled);
    }

    gpa_uint32 requiredPasses = 0;

    GPA_Status passCountStatus = pCounterScheduler->GetNumRequiredPasses(&requiredPasses);
    EXPECT_EQ(GPA_STATUS_OK, passCountStatus);

    gpa_uint32 expectedNumPasses = (gpa_uint32)expectedHwCountersPerPass.size();
    ASSERT_EQ(expectedNumPasses, requiredPasses);

    // make sure each pass has the expected set of hw counters
    for (unsigned int passIndex = 0; passIndex < expectedNumPasses; passIndex++)
    {
        std::vector<gpa_uint32>* pScheduledCountersInPass = pCounterScheduler->GetCountersForPass(passIndex);

        std::vector<unsigned int>& expectedCountersInPass = expectedHwCountersPerPass[passIndex];

        // make sure the number of scheduled counters matches the expected number of scheduled counters
        ASSERT_EQ(expectedCountersInPass.size(), pScheduledCountersInPass->size());

        // make sure all the counters match what we expect
        for (unsigned int counterIndex = 0; counterIndex < expectedCountersInPass.size(); counterIndex++)
        {
            EXPECT_EQ(expectedCountersInPass[counterIndex], pScheduledCountersInPass->at(counterIndex));
        }
    }

    ASSERT_EQ(expectedResultLocations.size(), countersToEnable.size());

    std::map<unsigned int, GPA_CounterResultLocation>* pCounterResultLocation = nullptr;

    for (unsigned int i = 0; i < countersToEnable.size(); ++i)
    {
        pCounterResultLocation = pCounterScheduler->GetCounterResultLocations(countersToEnable[i]);
        ASSERT_NE((void*)nullptr, pCounterResultLocation);

        std::map<unsigned int, GPA_CounterResultLocation> expectedResultLocation = expectedResultLocations[countersToEnable[i]];
        ASSERT_EQ(expectedResultLocation.size(), pCounterResultLocation->size());

        for (std::map<unsigned int, GPA_CounterResultLocation>::iterator hardwareCounterIter = expectedResultLocation.begin(); hardwareCounterIter != expectedResultLocation.end(); hardwareCounterIter++)
        {
            unsigned int expectedOffset = hardwareCounterIter->second.m_offset;
            unsigned int expectedPass = hardwareCounterIter->second.m_pass;

            std::map<unsigned int, GPA_CounterResultLocation>::iterator locationIter = pCounterResultLocation->find(hardwareCounterIter->first);

            if (pCounterResultLocation->end() != locationIter)
            {
                EXPECT_EQ(expectedOffset, locationIter->second.m_offset);
                EXPECT_EQ(expectedPass, locationIter->second.m_pass);
            }
            else
            {
                // The locationIter should always be valid; if the code got here, that means a counter was not in the expected place
                ADD_FAILURE();
            }
        }
    }

    // disable the counters
    pCounterScheduler->DisableAllCounters();
}

void VerifyCounterCalculation(GPA_API_Type api, unsigned int deviceId, char* counterName, std::vector<char*>& sampleResults, gpa_float64 expectedResult)
{
    HMODULE hDll = LoadLibraryA("GPUPerfAPICounters" AMDT_PROJECT_SUFFIX ".dll");
    ASSERT_NE((HMODULE)nullptr, hDll);

    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetProcAddress(hDll, "GPA_GetAvailableCounters");
    ASSERT_NE((GPA_GetAvailableCountersProc)nullptr, GPA_GetAvailableCounters_fn);

    GPA_ICounterAccessor* pCounterAccessor = nullptr;
    GPA_ICounterScheduler* pCounterScheduler = nullptr;
    GPA_Status status = GPA_GetAvailableCounters_fn(api, AMD_VENDOR_ID, deviceId, 0, &pCounterAccessor, &pCounterScheduler);
    EXPECT_EQ(GPA_STATUS_OK, status);
    EXPECT_NE((GPA_ICounterAccessor*)nullptr, pCounterAccessor);
    ASSERT_NE((GPA_ICounterScheduler*)nullptr, pCounterScheduler);

    std::vector<GPA_Type> internalCounterTypes;
    gpa_float64 result = 0;
    GPA_HWInfo hwInfo;                              ///< TODO ? Find this from the scheduler

    size_t numResults = sampleResults.size();

    for (size_t i = 0; i < numResults; i++)
    {
        internalCounterTypes.push_back(GPA_TYPE_UINT64);
    }

    gpa_uint32 numCounters = pCounterAccessor->GetNumCounters();

    gpa_uint32 counterIndex = gpa_uint32(-1);

    for (gpa_uint32 i = 0; i < numCounters; i++)
    {
        if (strcmp(pCounterAccessor->GetCounterName(i), counterName) == 0)
        {
            counterIndex = i;
            break;
        }
    }

    pCounterAccessor->ComputePublicCounterValue(counterIndex, sampleResults, internalCounterTypes, &result, &hwInfo);

    ASSERT_EQ(expectedResult, result);

    // disable the counters
    pCounterScheduler->DisableAllCounters();
}
