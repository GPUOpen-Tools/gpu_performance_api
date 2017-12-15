//==============================================================================
// Copyright (c) 2012-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit Tests for GL Counter Generator
//==============================================================================

#include "CounterGeneratorTests.h"
#include "GPUPerfAPITypes.h"
#include "GPAInternalCounter.h"

#include "counters/PublicCountersGLGfx6.h"
#include "counters/PublicCountersGLGfx7.h"
#include "counters/PublicCountersGLGfx8.h"
#include "counters/PublicCountersGLGfx9.h"

#ifdef AMDT_INTERNAL
    #include "InternalCountersGLGfx6.h"
    #include "InternalCountersGLGfx7.h"
    #include "InternalCountersGLGfx8.h"
    #include "InternalCountersGLGfx9.h"
#endif

static void GetExpectedCountersForGeneration(GPA_Hw_Generation gen, std::vector<const char*>& counterNames)
{
    counterNames.clear();

    const GPACounterDesc* pPublicCounters = nullptr;
    size_t publicCounterCount = 0;

    GPA_CounterGroupDesc* pHardwareGroups = nullptr;
    GPA_HardwareCounterDesc** ppHardwareCounters = nullptr;
    unsigned int hwGroupCount = 0;

    switch (gen)
    {
        case GPA_HW_GENERATION_NVIDIA:
            break;

        case GPA_HW_GENERATION_GFX6:
            pPublicCounters = GLGFX6_PUBLIC_COUNTERS;
            publicCounterCount = GLGFX6_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWGLGroupsGfx6;
            hwGroupCount = HWGLGroupCountGfx6;
            ppHardwareCounters = GLCounterGroupArrayGfx6;
#endif
            break;

        case GPA_HW_GENERATION_GFX7:
            pPublicCounters = GLGFX7_PUBLIC_COUNTERS;
            publicCounterCount = GLGFX7_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWGLGroupsGfx7;
            hwGroupCount = HWGLGroupCountGfx7;
            ppHardwareCounters = GLCounterGroupArrayGfx7;
#endif
            break;

        case GPA_HW_GENERATION_GFX8:
            pPublicCounters = GLGFX8_PUBLIC_COUNTERS;
            publicCounterCount = GLGFX8_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWGLGroupsGfx8;
            hwGroupCount = HWGLGroupCountGfx8;
            ppHardwareCounters = GLCounterGroupArrayGfx8;
#endif
            break;

        case GPA_HW_GENERATION_GFX9:
            pPublicCounters = GLGFX9_PUBLIC_COUNTERS;
            publicCounterCount = GLGFX9_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWGLGroupsGfx9;
            hwGroupCount = HWGLGroupCountGfx9;
            ppHardwareCounters = GLCounterGroupArrayGfx9;
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

// Test the OpenGL counter names on all supported hardware
TEST(CounterDLLTests, OpenGLCounterNames)
{
    VerifyHardwareNotSupported(GPA_API_OPENGL, gDevIdUnknown);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX6, counterNames);
    VerifyCounterNames(GPA_API_OPENGL, gDevIdSI, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX7, counterNames);
    VerifyCounterNames(GPA_API_OPENGL, gDevIdCI, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_OPENGL, gDevIdVI, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_OPENGL, gDevIdGfx9, counterNames);
}

// Test the OpenGL counter names on all generations
TEST(CounterDLLTests, OpenGLCounterNamesByGeneration)
{
    VerifyHardwareNotSupported(GPA_API_OPENGL, GPA_HW_GENERATION_NVIDIA);
    VerifyHardwareNotSupported(GPA_API_OPENGL, GPA_HW_GENERATION_INTEL);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX6, counterNames);
    VerifyCounterNames(GPA_API_OPENGL, GPA_HW_GENERATION_GFX6, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX7, counterNames);
    VerifyCounterNames(GPA_API_OPENGL, GPA_HW_GENERATION_GFX7, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX8, counterNames);
    VerifyCounterNames(GPA_API_OPENGL, GPA_HW_GENERATION_GFX8, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_GFX9, counterNames);
    VerifyCounterNames(GPA_API_OPENGL, GPA_HW_GENERATION_GFX9, counterNames);
}
