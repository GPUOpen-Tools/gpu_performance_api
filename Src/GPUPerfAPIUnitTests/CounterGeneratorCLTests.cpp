//==============================================================================
// Copyright (c) 2012-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit Tests for CL Counter Generator
//==============================================================================

#include <algorithm>

#include "CounterGeneratorTests.h"
#include "GPUPerfAPITypes.h"
#include "GPAInternalCounter.h"

#include "counters/PublicDerivedCountersCLGfx6.h"
#include "counters/PublicDerivedCountersCLGfx7.h"
#include "counters/PublicDerivedCountersCLGfx8.h"
#include "counters/PublicDerivedCountersCLGfx9.h"

#ifdef AMDT_INTERNAL
    #include "InternalCountersCLGfx6.h"
    #include "InternalCountersCLGfx7.h"
    #include "InternalCountersCLGfx8.h"
    #include "InternalCountersCLGfx9.h"
#endif

static void GetExpectedCountersForGeneration(GPA_Hw_Generation gen, std::vector<const char*>& counterNames)
{
    counterNames.clear();

    const GPACounterDesc* pPublicDerivedCounters = nullptr;
    size_t publicDerivedCounterCount = 0;

    GPA_CounterGroupDesc* pHardwareGroups = nullptr;
    GPA_HardwareCounterDesc** ppHardwareCounters = nullptr;
    unsigned int hwGroupCount = 0;

    switch (gen)
    {
        case GPA_HW_GENERATION_GFX6:
            pPublicDerivedCounters = CLGFX6_PUBLIC_COUNTERS;
            publicDerivedCounterCount = CLGFX6_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWCLGroupsGfx6;
            hwGroupCount = HWCLGroupCountGfx6;
            ppHardwareCounters = CLCounterGroupArrayGfx6;
#endif
            break;

        case GPA_HW_GENERATION_GFX7:
            pPublicDerivedCounters = CLGFX7_PUBLIC_COUNTERS;
            publicDerivedCounterCount = CLGFX7_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWCLGroupsGfx7;
            hwGroupCount = HWCLGroupCountGfx7;
            ppHardwareCounters = CLCounterGroupArrayGfx7;
#endif
            break;

        case GPA_HW_GENERATION_GFX8:
            pPublicDerivedCounters = CLGFX8_PUBLIC_COUNTERS;
            publicDerivedCounterCount = CLGFX8_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWCLGroupsGfx8;
            hwGroupCount = HWCLGroupCountGfx8;
            ppHardwareCounters = CLCounterGroupArrayGfx8;
#endif
            break;

        case GPA_HW_GENERATION_GFX9:
            pPublicDerivedCounters = CLGFX9_PUBLIC_COUNTERS;
            publicDerivedCounterCount = CLGFX9_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWCLGroupsGfx9;
            hwGroupCount = HWCLGroupCountGfx9;
            ppHardwareCounters = CLCounterGroupArrayGfx9;
#endif
            break;

        default:
            break;
    }

    for (size_t i = 0; i < publicDerivedCounterCount; i++)
    {
        counterNames.push_back(pPublicDerivedCounters[i].m_pName);
    }

    // Optionally, get internal derived counters
    const GPACounterDesc* pInternalDerivedCounters = nullptr;
    size_t internalDerivedCounterCount = 0;

#ifdef AMDT_INTERNAL
    GPA_GetInternalDerivedCounters(GPA_API_OPENCL, gen, &pInternalDerivedCounters, &internalDerivedCounterCount);
#endif

    for (size_t i = 0; i < internalDerivedCounterCount; i++)
    {
        counterNames.push_back(pInternalDerivedCounters[i].m_pName);
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
    VerifyHardwareNotSupported(GPA_API_OPENCL, gDevIdUnknown, FALSE);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX6, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, gDevIdSI, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX7, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, gDevIdCI, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, gDevIdVI, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, gDevIdGfx9, FALSE, counterNames);
}

// Test the openCL counter names on each generation
TEST(CounterDLLTests, OpenCLCounterNamesByGeneration)
{
    VerifyHardwareNotSupported(GPA_API_OPENCL, GPA_HW_GENERATION_NVIDIA, FALSE);
    VerifyHardwareNotSupported(GPA_API_OPENCL, GPA_HW_GENERATION_INTEL, FALSE);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX6, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, GPA_HW_GENERATION_GFX6, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX7, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, GPA_HW_GENERATION_GFX7, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, GPA_HW_GENERATION_GFX8, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, GPA_HW_GENERATION_GFX9, FALSE, counterNames);
}

TEST(CounterDLLTests, OpenCLMultipleGenerations)
{
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle)nullptr, libHandle);
    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetEntryPoint(libHandle, "GPA_GetAvailableCounters");

    if (nullptr != GPA_GetAvailableCounters_fn)
    {
        // First, attempt to get EG counters
        IGPACounterAccessor* pCounterAccessor = nullptr;
        IGPACounterScheduler* pCounterScheduler = nullptr;
        GPA_Status status = GPA_GetAvailableCounters_fn(GPA_API_OPENCL, AMD_VENDOR_ID, gDevIdCI, 0, GPA_OPENCONTEXT_DEFAULT_BIT, FALSE, &pCounterAccessor, &pCounterScheduler);
        EXPECT_EQ(GPA_STATUS_OK, status);
        EXPECT_NE((IGPACounterAccessor*)nullptr, pCounterAccessor);
        EXPECT_NE((IGPACounterScheduler*)nullptr, pCounterScheduler);

        std::vector<const char*> counterNames;
        GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX7, counterNames);

        if (nullptr != pCounterAccessor)
        {
            size_t numCounters = pCounterAccessor->GetNumCounters();
            EXPECT_EQ(counterNames.size(), numCounters);

            // verify as many counter names as possible.
            numCounters = std::min(counterNames.size(), numCounters);

            if (counterNames.size() == numCounters)
            {
                for (unsigned int i = 0; i < numCounters; ++i)
                {
                    const char* pCounterName = pCounterAccessor->GetCounterName(i);
                    EXPECT_STREQ(counterNames[i], pCounterName);

                    const char* pDesc = pCounterAccessor->GetCounterDescription(i);
                    EXPECT_NE((const char*)nullptr, pDesc);
#ifndef AMDT_INTERNAL
                    EXPECT_NE(0, strcmp("", pDesc));
#endif
                }
            }

            // Second, attempt to get SI counters
            pCounterAccessor = nullptr;
            pCounterScheduler = nullptr;
            status = GPA_GetAvailableCounters_fn(GPA_API_OPENCL, AMD_VENDOR_ID, gDevIdSI, 0, GPA_OPENCONTEXT_DEFAULT_BIT, FALSE, &pCounterAccessor, &pCounterScheduler);
            EXPECT_EQ(GPA_STATUS_OK, status);
            EXPECT_NE((IGPACounterAccessor*)nullptr, pCounterAccessor);
            EXPECT_NE((IGPACounterScheduler*)nullptr, pCounterScheduler);

            GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX6, counterNames);

            if (nullptr != pCounterAccessor)
            {
                numCounters = pCounterAccessor->GetNumCounters();
                EXPECT_EQ(counterNames.size(), numCounters);

                // verify as many counter names as possible.
                numCounters = std::min(counterNames.size(), numCounters);

                if (counterNames.size() == numCounters)
                {
                    for (unsigned int i = 0; i < numCounters; ++i)
                    {
                        const char* pCounterName = pCounterAccessor->GetCounterName(i);
                        EXPECT_STREQ(counterNames[i], pCounterName);

                        const char* pDesc = pCounterAccessor->GetCounterDescription(i);
                        EXPECT_NE((const char*)nullptr, pDesc);
#ifndef AMDT_INTERNAL
                        EXPECT_NE(0, strcmp("", pDesc));
#endif
                    }
                }
            }
        }
    }

    UnloadLib(libHandle);
}
