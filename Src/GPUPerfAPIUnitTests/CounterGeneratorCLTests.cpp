//==============================================================================
// Copyright (c) 2012-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit Tests for CL Counter Generator
//==============================================================================

#include "CounterGeneratorTests.h"
#include "GPUPerfAPITypes-Private.h"
#include "GPAInternalCounter.h"

#include "counters/PublicCountersCLGfx6.h"
#include "counters/PublicCountersCLGfx7.h"
#include "counters/PublicCountersCLGfx8.h"

#ifdef AMDT_INTERNAL
    #include "InternalCountersCLGfx6.h"
    #include "InternalCountersCLGfx7.h"
    #include "InternalCountersCLGfx8.h"
#endif

static void GetExpectedCountersForGeneration(GPA_HW_GENERATION gen, std::vector<const char*>& counterNames)
{
    counterNames.clear();

    const GPACounterDesc* pPublicCounters = nullptr;
    size_t publicCounterCount = 0;

    GPA_CounterGroupDesc* pHardwareGroups = nullptr;
    GPA_HardwareCounterDesc** ppHardwareCounters = nullptr;
    unsigned int hwGroupCount = 0;

    switch (gen)
    {
        case GPA_HW_GENERATION_SOUTHERNISLAND:
            pPublicCounters = CLGFX6_PUBLIC_COUNTERS;
            publicCounterCount = CLGFX6_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWCLGroupsGfx6;
            hwGroupCount = HWCLGroupCountGfx6;
            ppHardwareCounters = CLCounterGroupArrayGfx6;
#endif
            break;

        case GPA_HW_GENERATION_SEAISLAND:
            pPublicCounters = CLGFX7_PUBLIC_COUNTERS;
            publicCounterCount = CLGFX7_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWCLGroupsGfx7;
            hwGroupCount = HWCLGroupCountGfx7;
            ppHardwareCounters = CLCounterGroupArrayGfx7;
#endif
            break;

        case GPA_HW_GENERATION_VOLCANICISLAND:
            pPublicCounters = CLGFX8_PUBLIC_COUNTERS;
            publicCounterCount = CLGFX8_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWCLGroupsGfx8;
            hwGroupCount = HWCLGroupCountGfx8;
            ppHardwareCounters = CLCounterGroupArrayGfx8;
#endif
            break;
    }

    for (size_t i = 0; i < publicCounterCount; i++)
    {
        counterNames.push_back(pPublicCounters[i].m_pName);
    }

    for (unsigned int i = 0; i < hwGroupCount; i++)
    {
        for (unsigned int j = 0; j < pHardwareGroups[i].m_numCounters; j++)
        {
            counterNames.push_back(ppHardwareCounters[i][j].m_pName);
        }
    }
}

// Test the openCL counter names on all supported hardware
TEST(CounterDLLTests, OpenCLCounterNames)
{
    VerifyHardwareNotSupported(GPA_API_OPENCL, gDevIdUnknown);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_SOUTHERNISLAND, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, gDevIdSI, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_SEAISLAND, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, gDevIdCI, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_VOLCANICISLAND, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, gDevIdVI, counterNames);
}

// Test the openCL counter names on each generation
TEST(CounterDLLTests, OpenCLCounterNamesByGeneration)
{
    VerifyHardwareNotSupported(GPA_API_OPENCL, GPA_HW_GENERATION_NVIDIA);
    VerifyHardwareNotSupported(GPA_API_OPENCL, GPA_HW_GENERATION_INTEL);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_SOUTHERNISLAND, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, GPA_HW_GENERATION_SOUTHERNISLAND, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_SEAISLAND, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, GPA_HW_GENERATION_SEAISLAND, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_VOLCANICISLAND, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, GPA_HW_GENERATION_VOLCANICISLAND, counterNames);
}

TEST(CounterDLLTests, OpenCLMultipleGenerations)
{
    // open the DLL
    HMODULE hDll = LoadLibraryA("GPUPerfAPICounters" AMDT_PROJECT_SUFFIX ".dll");
    ASSERT_NE((HMODULE)nullptr, hDll);

    // get the entrypoints
    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetProcAddress(hDll, "GPA_GetAvailableCounters");
    ASSERT_NE((GPA_GetAvailableCountersProc)nullptr, GPA_GetAvailableCounters_fn);

    // First, attempt to get EG counters
    GPA_ICounterAccessor* pCounterAccessor = nullptr;
    GPA_ICounterScheduler* pCounterScheduler = nullptr;
    GPA_Status status = GPA_GetAvailableCounters_fn(GPA_API_OPENCL, AMD_VENDOR_ID, gDevIdCI, 0, &pCounterAccessor, &pCounterScheduler);
    EXPECT_EQ(GPA_STATUS_OK, status);
    EXPECT_NE((GPA_ICounterAccessor*)nullptr, pCounterAccessor);
    EXPECT_NE((GPA_ICounterScheduler*)nullptr, pCounterScheduler);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_SEAISLAND, counterNames);

    size_t numCounters = pCounterAccessor->GetNumCounters();
    EXPECT_EQ(counterNames.size(), numCounters);

    // verify as many counter names as possible.
    numCounters = min(counterNames.size(), numCounters);

    if (counterNames.size() == numCounters)
    {
        for (unsigned int i = 0; i < numCounters; ++i)
        {
            const char* pCounterName = pCounterAccessor->GetCounterName(i);
            EXPECT_STREQ(counterNames[i], pCounterName);

            const char* pDesc = pCounterAccessor->GetCounterDescription(i);
            EXPECT_NE((const char*)nullptr, pDesc);
            EXPECT_NE("", pDesc);
        }
    }

    // Second, attempt to get SI counters
    pCounterAccessor = nullptr;
    pCounterScheduler = nullptr;
    status = GPA_GetAvailableCounters_fn(GPA_API_OPENCL, AMD_VENDOR_ID, gDevIdSI, 0, &pCounterAccessor, &pCounterScheduler);
    EXPECT_EQ(GPA_STATUS_OK, status);
    EXPECT_NE((GPA_ICounterAccessor*)nullptr, pCounterAccessor);
    EXPECT_NE((GPA_ICounterScheduler*)nullptr, pCounterScheduler);

    GetExpectedCountersForGeneration(GPA_HW_GENERATION_SOUTHERNISLAND, counterNames);
    numCounters = pCounterAccessor->GetNumCounters();
    EXPECT_EQ(counterNames.size(), numCounters);

    // verify as many counter names as possible.
    numCounters = min(counterNames.size(), numCounters);

    if (counterNames.size() == numCounters)
    {
        for (unsigned int i = 0; i < numCounters; ++i)
        {
            const char* pCounterName = pCounterAccessor->GetCounterName(i);
            EXPECT_STREQ(counterNames[i], pCounterName);

            const char* pDesc = pCounterAccessor->GetCounterDescription(i);
            EXPECT_NE((const char*)nullptr, pDesc);
            EXPECT_NE("", pDesc);
        }
    }

    // delete DLL
    BOOL freed = FreeLibrary(hDll);
    EXPECT_EQ(TRUE, freed);
}
