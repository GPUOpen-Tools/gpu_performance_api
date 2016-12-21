//==============================================================================
// Copyright (c) 2012-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit Tests for GL Counter Generator
//==============================================================================

#include "CounterGeneratorTests.h"
#include "GPUPerfAPITypes-Private.h"
#include "GPAInternalCounter.h"

#include "counters/PublicCountersGLGfx6.h"
#include "counters/PublicCountersGLGfx7.h"
#include "counters/PublicCountersGLGfx8.h"

#ifdef AMDT_INTERNAL
    #include "InternalCountersGLGfx6.h"
    #include "InternalCountersGLGfx7.h"
    #include "InternalCountersGLGfx8.h"
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
        case GPA_HW_GENERATION_NVIDIA:
            break;

        case GPA_HW_GENERATION_SOUTHERNISLAND:
            pPublicCounters = GLGFX6_PUBLIC_COUNTERS;
            publicCounterCount = GLGFX6_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWGLGroupsGfx6;
            hwGroupCount = HWGLGroupCountGfx6;
            ppHardwareCounters = GLCounterGroupArrayGfx6;
#endif
            break;

        case GPA_HW_GENERATION_SEAISLAND:
            pPublicCounters = GLGFX7_PUBLIC_COUNTERS;
            publicCounterCount = GLGFX7_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWGLGroupsGfx7;
            hwGroupCount = HWGLGroupCountGfx7;
            ppHardwareCounters = GLCounterGroupArrayGfx7;
#endif
            break;

        case GPA_HW_GENERATION_VOLCANICISLAND:
            pPublicCounters = GLGFX8_PUBLIC_COUNTERS;
            publicCounterCount = GLGFX8_PUBLIC_COUNTER_COUNT;
#ifdef AMDT_INTERNAL
            pHardwareGroups = HWGLGroupsGfx8;
            hwGroupCount = HWGLGroupCountGfx8;
            ppHardwareCounters = GLCounterGroupArrayGfx8;
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
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_SOUTHERNISLAND, counterNames);
    VerifyCounterNames(GPA_API_OPENGL, gDevIdSI, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_SEAISLAND, counterNames);
    VerifyCounterNames(GPA_API_OPENGL, gDevIdCI, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_VOLCANICISLAND, counterNames);
    VerifyCounterNames(GPA_API_OPENGL, gDevIdVI, counterNames);
}

// Test the OpenGL counter names on all generations
TEST(CounterDLLTests, OpenGLCounterNamesByGeneration)
{
    VerifyHardwareNotSupported(GPA_API_OPENGL, GPA_HW_GENERATION_NVIDIA);
    VerifyHardwareNotSupported(GPA_API_OPENGL, GPA_HW_GENERATION_INTEL);

    std::vector<const char*> counterNames;
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_SOUTHERNISLAND, counterNames);
    VerifyCounterNames(GPA_API_OPENGL, GPA_HW_GENERATION_SOUTHERNISLAND, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_SEAISLAND, counterNames);
    VerifyCounterNames(GPA_API_OPENGL, GPA_HW_GENERATION_SEAISLAND, counterNames);
    GetExpectedCountersForGeneration(GPA_HW_GENERATION_VOLCANICISLAND, counterNames);
    VerifyCounterNames(GPA_API_OPENGL, GPA_HW_GENERATION_VOLCANICISLAND, counterNames);
}
