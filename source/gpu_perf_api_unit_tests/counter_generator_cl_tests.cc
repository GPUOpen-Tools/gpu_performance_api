//==============================================================================
// Copyright (c) 2012-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit Tests for CL Counter Generator
//==============================================================================

#include <algorithm>

#include "counter_generator_tests.h"
#include "gpu_perf_api_types.h"
#include "gpa_counter.h"

#include "counters/public_derived_counters_cl_gfx8.h"
#include "counters/public_derived_counters_cl_gfx9.h"
#include "counters/public_derived_counters_cl_gfx10.h"

#ifdef AMDT_INTERNAL
#include "gpa_hw_counter_cl_gfx8.h"
#include "gpa_hw_counter_cl_gfx9.h"
#include "gpa_hw_counter_cl_gfx10.h"
#endif

static void GetExpectedCountersForGeneration(GPA_Hw_Generation gen, std::vector<const char*>& counterNames)
{
    counterNames.clear();

    const GPACounterDesc* pPublicDerivedCounters    = nullptr;
    size_t                publicDerivedCounterCount = 0;

    GPA_CounterGroupDesc*     pHardwareGroups    = nullptr;
    GPA_HardwareCounterDesc** ppHardwareCounters = nullptr;
    unsigned int              hwGroupCount       = 0;

    switch (gen)
    {
    case GPA_HW_GENERATION_GFX8:
        pPublicDerivedCounters    = CLGFX8_PUBLIC_COUNTERS;
        publicDerivedCounterCount = CLGFX8_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
        pHardwareGroups    = countergfx8::hw_cl_groups_gfx8;
        hwGroupCount       = countergfx8::hw_cl_group_count_gfx8;
        ppHardwareCounters = countergfx8::cl_counter_group_array_gfx8;
#endif
        break;

    case GPA_HW_GENERATION_GFX9:
        pPublicDerivedCounters    = CLGFX9_PUBLIC_COUNTERS;
        publicDerivedCounterCount = CLGFX9_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
        pHardwareGroups    = countergfx9::hw_cl_groups_gfx9;
        hwGroupCount       = countergfx9::hw_cl_group_count_gfx9;
        ppHardwareCounters = countergfx9::cl_counter_group_array_gfx9;
#endif
        break;

    case GPA_HW_GENERATION_GFX10:
        pPublicDerivedCounters    = CLGFX10_PUBLIC_COUNTERS;
        publicDerivedCounterCount = CLGFX10_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
        pHardwareGroups    = countergfx10::hw_cl_groups_gfx10;
        hwGroupCount       = countergfx10::hw_cl_group_count_gfx10;
        ppHardwareCounters = countergfx10::cl_counter_group_array_gfx10;
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
    const GPACounterDesc* pInternalDerivedCounters    = nullptr;
    size_t                internalDerivedCounterCount = 0;

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
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, gDevIdVI, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, gDevIdGfx9, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX10, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, gDevIdGfx10, FALSE, counterNames);
}

// Test the openCL counter names on each generation
TEST(CounterDLLTests, OpenCLCounterNamesByGeneration)
{
    VerifyHardwareNotSupported(GPA_API_OPENCL, GPA_HW_GENERATION_NVIDIA, FALSE);
    VerifyHardwareNotSupported(GPA_API_OPENCL, GPA_HW_GENERATION_INTEL, FALSE);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, GPA_HW_GENERATION_GFX8, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, GPA_HW_GENERATION_GFX9, FALSE, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX10, counterNames);
    VerifyCounterNames(GPA_API_OPENCL, GPA_HW_GENERATION_GFX10, FALSE, counterNames);
}

TEST(CounterDLLTests, ClCounterLibTest)
{
    VerifyCounterLibInterface(GPA_API_OPENCL, gDevIdVI, REVISION_ID_ANY, false);
    VerifyCounterLibInterface(GPA_API_OPENCL, gDevIdGfx9, REVISION_ID_ANY, false);
    VerifyCounterLibInterface(GPA_API_OPENCL, gDevIdGfx10, REVISION_ID_ANY, false);
}


TEST(CounterDLLTests, OpenCLMultipleGenerations)
{
    LibHandle libHandle = LoadLib(countersLibName);
    ASSERT_NE((LibHandle) nullptr, libHandle);
//    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetEntryPoint(libHandle, "GPA_GetAvailableCounters");
//
//    if (nullptr != GPA_GetAvailableCounters_fn)
//    {
//        // First, attempt to get EG counters
//        IGPACounterAccessor*  pCounterAccessor  = nullptr;
//        IGPACounterScheduler* pCounterScheduler = nullptr;
//        GPA_Status            status = GPA_GetAvailableCounters_fn(GPA_API_OPENCL, AMD_VENDOR_ID, gDevIdVI, 0, GPA_OPENCONTEXT_DEFAULT_BIT, FALSE, &pCounterAccessor, &pCounterScheduler);
//        EXPECT_EQ(GPA_STATUS_OK, status);
//        EXPECT_NE((IGPACounterAccessor*)nullptr, pCounterAccessor);
//        EXPECT_NE((IGPACounterScheduler*)nullptr, pCounterScheduler);
//
//        std::vector<const char*> counterNames;
//        GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
//
//        if (nullptr != pCounterAccessor)
//        {
//            size_t numCounters = pCounterAccessor->GetNumCounters();
//            EXPECT_EQ(counterNames.size(), numCounters);
//
//            // verify as many counter names as possible.
//            numCounters = std::min(counterNames.size(), numCounters);
//
//            if (counterNames.size() == numCounters)
//            {
//                for (unsigned int i = 0; i < numCounters; ++i)
//                {
//                    const char* pCounterName = pCounterAccessor->GetCounterName(i);
//                    EXPECT_STREQ(counterNames[i], pCounterName);
//
//                    const char* pDesc = pCounterAccessor->GetCounterDescription(i);
//                    EXPECT_NE((const char*)nullptr, pDesc);
//#ifndef AMDT_INTERNAL
//                    EXPECT_NE(0, strcmp("", pDesc));
//#endif
//                }
//            }
//
//            // Second, attempt to get SI counters
//            pCounterAccessor  = nullptr;
//            pCounterScheduler = nullptr;
//            status            = GPA_GetAvailableCounters_fn(
//                GPA_API_OPENCL, AMD_VENDOR_ID, gDevIdGfx9, 0, GPA_OPENCONTEXT_DEFAULT_BIT, FALSE, &pCounterAccessor, &pCounterScheduler);
//            EXPECT_EQ(GPA_STATUS_OK, status);
//            EXPECT_NE((IGPACounterAccessor*)nullptr, pCounterAccessor);
//            EXPECT_NE((IGPACounterScheduler*)nullptr, pCounterScheduler);
//
//            GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
//
//            if (nullptr != pCounterAccessor)
//            {
//                numCounters = pCounterAccessor->GetNumCounters();
//                EXPECT_EQ(counterNames.size(), numCounters);
//
//                // verify as many counter names as possible.
//                numCounters = std::min(counterNames.size(), numCounters);
//
//                if (counterNames.size() == numCounters)
//                {
//                    for (unsigned int i = 0; i < numCounters; ++i)
//                    {
//                        const char* pCounterName = pCounterAccessor->GetCounterName(i);
//                        EXPECT_STREQ(counterNames[i], pCounterName);
//
//                        const char* pDesc = pCounterAccessor->GetCounterDescription(i);
//                        EXPECT_NE((const char*)nullptr, pDesc);
//#ifndef AMDT_INTERNAL
//                        EXPECT_NE(0, strcmp("", pDesc));
//#endif
//                    }
//                }
//            }
//        }
//    }

    UnloadLib(libHandle);
}
