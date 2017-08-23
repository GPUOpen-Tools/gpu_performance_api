//==============================================================================
// Copyright (c) 2012-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Helper functions for Counter Generator Unit Tests
//==============================================================================

#define NOMINMAX
#include "CounterGeneratorTests.h"
#include "GPAHWInfo.h"
#include "GPAContextState.h"
#include <map>
#include <algorithm>

LibHandle LoadLib(const char* pLibName)
{
    LibHandle retVal = nullptr;
#ifdef _WIN32
    retVal = LoadLibraryA(pLibName);
#else
    retVal = dlopen(pLibName, RTLD_NOW);
#endif

    return retVal;
}

void UnloadLib(LibHandle libHandle)
{
#ifdef _WIN32
    BOOL freed = FreeLibrary(libHandle);
    EXPECT_EQ(TRUE, freed);
#else
    int freed = dlclose(libHandle);
    EXPECT_EQ(0, freed);
#endif
}

void* GetEntryPoint(LibHandle libHandle, const char* pEntrypointName)
{
    void* pRetVal = nullptr;
#ifdef _WIN32
    pRetVal = GetProcAddress(libHandle, pEntrypointName);
#else
    pRetVal = dlsym(libHandle, pEntrypointName);
#endif
    EXPECT_NE(nullptr, pRetVal);

    return pRetVal;
}

void VerifyNotImplemented(GPA_API_Type api, unsigned int deviceId)
{
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle)nullptr, libHandle);
    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetEntryPoint(libHandle, "GPA_GetAvailableCounters");

    if (nullptr != GPA_GetAvailableCounters_fn)
    {
        GPA_ICounterAccessor* pCounterAccessor = nullptr;
        GPA_ICounterScheduler* pCounterScheduler = nullptr;
        GPA_Status status = GPA_GetAvailableCounters_fn(api, AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, &pCounterAccessor, &pCounterScheduler);
        EXPECT_EQ(GPA_STATUS_ERROR_NOT_FOUND, status);
    }

    UnloadLib(libHandle);
}

void VerifyNotImplemented(GPA_API_Type api, GPA_HW_GENERATION generation)
{
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle)nullptr, libHandle);
    GPA_GetAvailableCountersByGenerationProc GPA_GetAvailableCountersByGeneration_fn = (GPA_GetAvailableCountersByGenerationProc)GetEntryPoint(libHandle, "GPA_GetAvailableCountersByGeneration");

    if (nullptr != GPA_GetAvailableCountersByGeneration_fn)
    {
        GPA_ICounterAccessor* pCounterAccessor = nullptr;
        GPA_Status status = GPA_GetAvailableCountersByGeneration_fn(api, generation, &pCounterAccessor);
        EXPECT_EQ(GPA_STATUS_ERROR_NOT_FOUND, status);
    }

    UnloadLib(libHandle);
}

void VerifyHardwareNotSupported(GPA_API_Type api, unsigned int deviceId)
{
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle)nullptr, libHandle);
    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetEntryPoint(libHandle, "GPA_GetAvailableCounters");

    if (nullptr != GPA_GetAvailableCounters_fn)
    {
        GPA_ICounterAccessor* pCounterAccessor = nullptr;
        GPA_ICounterScheduler* pCounterScheduler = nullptr;
        GPA_Status status = GPA_GetAvailableCounters_fn(api, AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, &pCounterAccessor, &pCounterScheduler);
        EXPECT_EQ(GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED, status);
        EXPECT_EQ(nullptr, pCounterAccessor);
        EXPECT_EQ(nullptr, pCounterScheduler);
    }

    UnloadLib(libHandle);
}

void VerifyHardwareNotSupported(GPA_API_Type api, GPA_HW_GENERATION generation)
{
    LibHandle libHandle = LoadLib(countersLibName);
    GPA_GetAvailableCountersByGenerationProc GPA_GetAvailableCountersByGeneration_fn = (GPA_GetAvailableCountersByGenerationProc)GetEntryPoint(libHandle, "GPA_GetAvailableCountersByGeneration");

    if (nullptr != GPA_GetAvailableCountersByGeneration_fn)
    {
        GPA_ICounterAccessor* pCounterAccessor = nullptr;
        GPA_Status status = GPA_GetAvailableCountersByGeneration_fn(api, generation, &pCounterAccessor);
        EXPECT_EQ(GPA_STATUS_ERROR_HARDWARE_NOT_SUPPORTED, status);
        EXPECT_EQ(nullptr, pCounterAccessor);
    }

    UnloadLib(libHandle);
}

void VerifyCounterNames(GPA_API_Type api, unsigned int deviceId, std::vector<const char*> expectedNames)
{
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle)nullptr, libHandle);
    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetEntryPoint(libHandle, "GPA_GetAvailableCounters");

    if (nullptr != GPA_GetAvailableCounters_fn)
    {
        GPA_ICounterAccessor* pCounterAccessor = nullptr;
        GPA_ICounterScheduler* pCounterScheduler = nullptr;
        GPA_Status status = GPA_GetAvailableCounters_fn(api, AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, &pCounterAccessor, &pCounterScheduler);
        EXPECT_EQ(GPA_STATUS_OK, status);
        EXPECT_NE((GPA_ICounterAccessor*)nullptr, pCounterAccessor);
        EXPECT_NE((GPA_ICounterScheduler*)nullptr, pCounterScheduler);

        if (nullptr != pCounterAccessor)
        {
            size_t numCounters = pCounterAccessor->GetNumCounters();
            EXPECT_EQ(expectedNames.size(), numCounters);

            // verify as many counter names as possible.
            numCounters = std::min(expectedNames.size(), numCounters);

#ifdef AMDT_INTERNAL

            for (unsigned int i = 0; i < numCounters; ++i)
            {
                const char* pCounterName = pCounterAccessor->GetCounterName(i);
                EXPECT_STREQ(expectedNames[i], pCounterName);

                if (strcmp(expectedNames[i], pCounterName) != 0)
                {
                    printf("Counter names are different at index %d: expected %s, got %s\n", i, expectedNames[i], pCounterName);
                }

                const char* pGroup = pCounterAccessor->GetCounterCategory(i);
                EXPECT_NE((const char*)nullptr, pGroup);
                EXPECT_NE("", pGroup);

                const char* pDesc = pCounterAccessor->GetCounterDescription(i);
                EXPECT_NE((const char*)nullptr, pDesc);
                EXPECT_NE("", pDesc);

                // the format of the description used to be "#GROUP#counter description", but isn't any longer, so make sure the description does NOT start with '#'
                EXPECT_NE('#', pDesc[0]);
            }

#else // not AMDT_INTERNAL

            if (expectedNames.size() == numCounters)
            {
                for (unsigned int i = 0; i < numCounters; ++i)
                {
                    const char* pCounterName = pCounterAccessor->GetCounterName(i);
                    EXPECT_STREQ(expectedNames[i], pCounterName);

                    const char* pGroup = pCounterAccessor->GetCounterCategory(i);
                    EXPECT_NE((const char*)nullptr, pGroup);
                    EXPECT_NE("", pGroup);

                    const char* pDesc = pCounterAccessor->GetCounterDescription(i);
                    EXPECT_NE((const char*)nullptr, pDesc);
                    EXPECT_NE("", pDesc);

                    // the format of the description used to be "#GROUP#counter description", but isn't any longer, so make sure the description does NOT start with '#'
                    EXPECT_NE('#', pDesc[0]);
                }
            }

#endif // AMDT_INTERNAL
        }
    }

    UnloadLib(libHandle);
}

void VerifyCounterNames(GPA_API_Type api, GPA_HW_GENERATION generation, std::vector<const char*> expectedNames)
{
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle)nullptr, libHandle);
    GPA_GetAvailableCountersByGenerationProc GPA_GetAvailableCountersByGeneration_fn = (GPA_GetAvailableCountersByGenerationProc)GetEntryPoint(libHandle, "GPA_GetAvailableCountersByGeneration");

    if (nullptr != GPA_GetAvailableCountersByGeneration_fn)
    {
        GPA_ICounterAccessor* pCounterAccessor = nullptr;
        GPA_Status status = GPA_GetAvailableCountersByGeneration_fn(api, generation, &pCounterAccessor);
        EXPECT_EQ(GPA_STATUS_OK, status);
        EXPECT_NE((GPA_ICounterAccessor*)nullptr, pCounterAccessor);

        if (nullptr != pCounterAccessor)
        {
            size_t numCounters = pCounterAccessor->GetNumCounters();
            EXPECT_EQ(expectedNames.size(), numCounters);

            // verify as many counter names as possible.
            numCounters = std::min(expectedNames.size(), numCounters);

#ifdef AMDT_INTERNAL

            for (unsigned int i = 0; i < numCounters; ++i)
            {
                const char* pCounterName = pCounterAccessor->GetCounterName(i);
                EXPECT_STREQ(expectedNames[i], pCounterName);

                if (strcmp(expectedNames[i], pCounterName) != 0)
                {
                    printf("Counter names are different at index %d: expected %s, got %s\n", i, expectedNames[i], pCounterName);
                }

                const char* pGroup = pCounterAccessor->GetCounterCategory(i);
                EXPECT_NE((const char*)nullptr, pGroup);
                EXPECT_NE("", pGroup);

                const char* pDesc = pCounterAccessor->GetCounterDescription(i);
                EXPECT_NE((const char*)nullptr, pDesc);
                EXPECT_NE("", pDesc);

                // the format of the description used to be "#GROUP#counter description", but isn't any longer, so make sure the description does NOT start with '#'
                EXPECT_NE('#', pDesc[0]);
            }

#else // not AMDT_INTERNAL

            if (expectedNames.size() == numCounters)
            {
                for (unsigned int i = 0; i < numCounters; ++i)
                {
                    const char* pCounterName = pCounterAccessor->GetCounterName(i);
                    EXPECT_STREQ(expectedNames[i], pCounterName);

                    const char* pGroup = pCounterAccessor->GetCounterCategory(i);
                    EXPECT_NE((const char*)nullptr, pGroup);
                    EXPECT_NE("", pGroup);

                    const char* pDesc = pCounterAccessor->GetCounterDescription(i);
                    EXPECT_NE((const char*)nullptr, pDesc);
                    EXPECT_NE("", pDesc);

                    // the format of the description used to be "#GROUP#counter description", but isn't any longer, so make sure the description does NOT start with '#'
                    EXPECT_NE('#', pDesc[0]);
                }
            }

#endif // AMDT_INTERNAL
        }
    }

    UnloadLib(libHandle);
}


void VerifyPassCount(GPA_API_Type api, unsigned int deviceId, const std::vector<unsigned int>& countersToEnable, unsigned int expectedNumPasses)
{
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle)nullptr, libHandle);
    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetEntryPoint(libHandle, "GPA_GetAvailableCounters");

    if (nullptr != GPA_GetAvailableCounters_fn)
    {
        GPA_ICounterAccessor* pCounterAccessor = nullptr;
        GPA_ICounterScheduler* pCounterScheduler = nullptr;
        GPA_Status status = GPA_GetAvailableCounters_fn(api, AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, &pCounterAccessor, &pCounterScheduler);
        EXPECT_EQ(GPA_STATUS_OK, status);
        EXPECT_NE((GPA_ICounterAccessor*)nullptr, pCounterAccessor);
        EXPECT_NE((GPA_ICounterScheduler*)nullptr, pCounterScheduler);

        if (nullptr != pCounterScheduler)
        {
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
    }

    UnloadLib(libHandle);
}

void VerifyCountersInPass(GPA_API_Type api,
                          unsigned int deviceId,
                          const std::vector<unsigned int>& countersToEnable,
                          const std::vector< std::vector<unsigned int> >& expectedHwCountersPerPass,
                          const std::map< unsigned int, std::map<unsigned int, GPA_CounterResultLocation> >& expectedResultLocations)
{
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle)nullptr, libHandle);
    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetEntryPoint(libHandle, "GPA_GetAvailableCounters");

    if (nullptr != GPA_GetAvailableCounters_fn)
    {
        GPA_ICounterAccessor* pCounterAccessor = nullptr;
        GPA_ICounterScheduler* pCounterScheduler = nullptr;

        // Get all the counters (based on API and the deviceID), an accessor, and a scheduler
        GPA_Status status = GPA_GetAvailableCounters_fn(api, AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, &pCounterAccessor, &pCounterScheduler);

        EXPECT_EQ(GPA_STATUS_OK, status);
        EXPECT_NE((GPA_ICounterAccessor*)nullptr, pCounterAccessor);
        EXPECT_NE((GPA_ICounterScheduler*)nullptr, pCounterScheduler);

        if (nullptr != pCounterScheduler)
        {
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
            EXPECT_EQ(expectedNumPasses, requiredPasses);

            // make sure each pass has the expected set of hw counters
            for (unsigned int passIndex = 0; passIndex < expectedNumPasses; passIndex++)
            {
                std::vector<gpa_uint32>* pScheduledCountersInPass = pCounterScheduler->GetCountersForPass(passIndex);

                const std::vector<unsigned int>& expectedCountersInPass = expectedHwCountersPerPass[passIndex];

                // make sure the number of scheduled counters matches the expected number of scheduled counters
                EXPECT_EQ(expectedCountersInPass.size(), pScheduledCountersInPass->size());

                // make sure all the counters match what we expect
                for (unsigned int counterIndex = 0; counterIndex < expectedCountersInPass.size(); counterIndex++)
                {
                    EXPECT_EQ(expectedCountersInPass[counterIndex], pScheduledCountersInPass->at(counterIndex));
                }
            }

            EXPECT_EQ(expectedResultLocations.size(), countersToEnable.size());

            std::map<unsigned int, GPA_CounterResultLocation>* pCounterResultLocation = nullptr;

            for (unsigned int i = 0; i < countersToEnable.size(); ++i)
            {
                pCounterResultLocation = pCounterScheduler->GetCounterResultLocations(countersToEnable[i]);
                EXPECT_NE((void*)nullptr, pCounterResultLocation);

                if (nullptr != pCounterResultLocation)
                {
                    const auto expectedResultiter = expectedResultLocations.find(countersToEnable[i]);
                    if (expectedResultiter == expectedResultLocations.end())
                    {
                        // Counter not found in expected results
                        ADD_FAILURE();
                    }
                    const std::map<unsigned int, GPA_CounterResultLocation> expectedResultLocation = expectedResultiter->second;

                    EXPECT_EQ(expectedResultLocation.size(), pCounterResultLocation->size());

                    if (expectedResultLocation.size() == pCounterResultLocation->size())
                    {
                        for (auto hardwareCounterIter = expectedResultLocation.begin(); hardwareCounterIter != expectedResultLocation.end(); hardwareCounterIter++)
                        {
                            unsigned int expectedOffset = hardwareCounterIter->second.m_offset;
                            unsigned int expectedPass = hardwareCounterIter->second.m_pass;

                            auto locationIter = pCounterResultLocation->find(hardwareCounterIter->first);

                            if (pCounterResultLocation->end() != locationIter)
                            {
                                EXPECT_EQ(expectedOffset, locationIter->second.m_offset) << "Unexpected result offset for counter " << countersToEnable[i];
                                EXPECT_EQ(expectedPass, locationIter->second.m_pass) << "Unexpected result pass for counter " << countersToEnable[i];
                            }
                            else
                            {
                                // The locationIter should always be valid; if the code got here, that means a counter was not in the expected place
                                ADD_FAILURE();
                            }
                        }
                    }
                }
            }

            // disable the counters
            pCounterScheduler->DisableAllCounters();
        }
    }

    UnloadLib(libHandle);
}

void DecodeCountersInPassAndResultLocations(
    GPA_API_Type api,
    unsigned int deviceId,
    const std::vector<unsigned int>& countersToEnable,
    std::stringstream* pOutputStream
)
{
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle)nullptr, libHandle);
    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetEntryPoint(libHandle, "GPA_GetAvailableCounters");

    if (nullptr != GPA_GetAvailableCounters_fn)
    {
        GPA_ICounterAccessor* pCounterAccessor = nullptr;
        GPA_ICounterScheduler* pCounterScheduler = nullptr;

        // Get all the counters (based on API and the deviceID), an accessor, and a scheduler
        GPA_Status status = GPA_GetAvailableCounters_fn(api, AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, &pCounterAccessor, &pCounterScheduler);

        EXPECT_EQ(GPA_STATUS_OK, status);
        EXPECT_NE((GPA_ICounterAccessor*)nullptr, pCounterAccessor);
        EXPECT_NE((GPA_ICounterScheduler*)nullptr, pCounterScheduler);

        if (nullptr != pCounterScheduler)
        {
            pCounterScheduler->DisableAllCounters();

            for (unsigned int i = 0; i < countersToEnable.size(); ++i)
            {
                GPA_Status enabled = pCounterScheduler->EnableCounter(countersToEnable[i]);
                EXPECT_EQ(GPA_STATUS_OK, enabled);
            }

            gpa_uint32 requiredPasses = 0;

            GPA_Status passCountStatus = pCounterScheduler->GetNumRequiredPasses(&requiredPasses);
            EXPECT_EQ(GPA_STATUS_OK, passCountStatus);

            *pOutputStream << "Expected number of passes: " << requiredPasses << "\n";

            // make sure each pass has the expected set of hw counters
            for (unsigned int passIndex = 0; passIndex < requiredPasses; passIndex++)
            {
                std::vector<gpa_uint32>* pScheduledCountersInPass = pCounterScheduler->GetCountersForPass(passIndex);

                *pOutputStream << "Pass: " << passIndex << "\n";
                *pOutputStream << "Counter Count: " << pScheduledCountersInPass->size() << "\n";
                *pOutputStream << "Counters: ";

                // make sure all the counters match what we expect
                for (unsigned int counterIndex = 0; counterIndex < pScheduledCountersInPass->size(); counterIndex++)
                {
                    if (counterIndex)
                        *pOutputStream << ",";
                    *pOutputStream << pScheduledCountersInPass->at(counterIndex);
                }
                *pOutputStream << "\n";
            }

            std::map<unsigned int, GPA_CounterResultLocation>* pCounterResultLocation = nullptr;

            *pOutputStream << "\nResult locations (Pass, Offset)\n";

            for (unsigned int i = 0; i < countersToEnable.size(); ++i)
            {
                *pOutputStream << "Counter: " << countersToEnable[i] << "\n";

                pCounterResultLocation = pCounterScheduler->GetCounterResultLocations(countersToEnable[i]);
                EXPECT_NE((void*)nullptr, pCounterResultLocation);

                if (nullptr != pCounterResultLocation)
                {
                    for (auto hardwareCounterIter = pCounterResultLocation->begin(); hardwareCounterIter != pCounterResultLocation->end(); hardwareCounterIter++)
                    {
                        unsigned int expectedOffset = hardwareCounterIter->second.m_offset;
                        unsigned int expectedPass = hardwareCounterIter->second.m_pass;

                        *pOutputStream << "(" << expectedPass << ", " << expectedOffset << ")\n";

                        auto locationIter = pCounterResultLocation->find(hardwareCounterIter->first);

                        if (pCounterResultLocation->end() != locationIter)
                        {
                            EXPECT_EQ(expectedOffset, locationIter->second.m_offset) << "Unexpected result offset for counter " << countersToEnable[i];
                            EXPECT_EQ(expectedPass, locationIter->second.m_pass) << "Unexpected result pass for counter " << countersToEnable[i];
                        }
                        else
                        {
                            // The locationIter should always be valid; if the code got here, that means a counter was not in the expected place
                            ADD_FAILURE();
                        }
                    }
                }
            }

            // disable the counters
            pCounterScheduler->DisableAllCounters();

            *pOutputStream << "\n";
        }
    }

    UnloadLib(libHandle);
}

void VerifyCounterCalculation(GPA_API_Type api, unsigned int deviceId, char* counterName, std::vector<char*>& sampleResults, gpa_float64 expectedResult)
{
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle)nullptr, libHandle);
    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetEntryPoint(libHandle, "GPA_GetAvailableCounters");

    if (nullptr != GPA_GetAvailableCounters_fn)
    {
        GPA_ICounterAccessor* pCounterAccessor = nullptr;
        GPA_ICounterScheduler* pCounterScheduler = nullptr;
        GPA_Status status = GPA_GetAvailableCounters_fn(api, AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, &pCounterAccessor, &pCounterScheduler);
        EXPECT_EQ(GPA_STATUS_OK, status);
        EXPECT_NE((GPA_ICounterAccessor*)nullptr, pCounterAccessor);
        EXPECT_NE((GPA_ICounterScheduler*)nullptr, pCounterScheduler);

        if (nullptr != pCounterScheduler)
        {
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

            EXPECT_EQ(expectedResult, result);

            // disable the counters
            pCounterScheduler->DisableAllCounters();
        }
    }

    UnloadLib(libHandle);
}
