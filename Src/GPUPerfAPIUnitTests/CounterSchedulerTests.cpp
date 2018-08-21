//==============================================================================
// Copyright (c) 2012-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit tests for Counter Scheduler
//==============================================================================

#include "CounterGeneratorTests.h"
#include "GPASplitCountersInterfaces.h"

#ifdef _WIN32
    #include "GPAInternalCounter.h"

    #include "counters/PublicCountersDX11Gfx6.h"
    #include "counters/PublicCountersDX11Gfx7.h"
    #include "counters/PublicCountersDX11Gfx8.h"
    #include "counters/PublicCountersDX11Gfx9.h"

    #include "InternalCountersDX11Gfx6.h"
    #include "InternalCountersDX11Gfx7.h"
    #include "InternalCountersDX11Gfx8.h"
    #include "InternalCountersDX11Gfx9.h"

    #include "counters/PublicCountersDX12Gfx7.h"
    #include "counters/PublicCountersDX12Gfx8.h"
    #include "counters/PublicCountersDX12Gfx9.h"

    #include "InternalCountersDX12Gfx7.h"
    #include "InternalCountersDX12Gfx8.h"
    #include "InternalCountersDX12Gfx9.h"
#endif

#include "counters/PublicCountersCLGfx6.h"
#include "counters/PublicCountersGLGfx6.h"
#include "counters/PublicCountersGLGfx7.h"
#include "counters/PublicCountersGLGfx8.h"

#define MakeExpectedCounterLocationEntry(x, y) { expectedCountersPass##x[y], MakeLocation(x, y) },

GPA_CounterResultLocation MakeLocation(gpa_uint16 pass, gpa_uint16 offset)
{
    GPA_CounterResultLocation location;
    location.m_pass = pass;
    location.m_offset = offset;

    return location;
}

// Test the openCL counter names on SI hardware
TEST(CounterDLLTests, OpenCLCounterSchedulingSI)
{
    std::vector<unsigned int> counters;
    counters.push_back(0);
    counters.push_back(1);
    counters.push_back(2);

    VerifyPassCount(GPA_API_OPENCL, gDevIdSI, FALSE, counters, 1);
}

// Test the openCL counter names on CI hardware
TEST(CounterDLLTests, OpenCLCounterSchedulingCI)
{
    std::vector<unsigned int> counters;
    counters.push_back(0);
    counters.push_back(1);
    counters.push_back(2);

    VerifyPassCount(GPA_API_OPENCL, gDevIdCI, FALSE, counters, 1);
}

// Test the openCL counter names on VI hardware
TEST(CounterDLLTests, OpenCLCounterSchedulingVI)
{
    std::vector<unsigned int> counters;
    counters.push_back(0);
    counters.push_back(1);
    counters.push_back(2);

    VerifyPassCount(GPA_API_OPENCL, gDevIdVI, FALSE, counters, 1);
}

// Counters to enable (Wavefronts, VALUInsts, SALUInsts, VFetchInsts, SFetchInsts, VWriteInsts, VALUUtilization, VALUBusy, SALUBusy)
TEST(CounterDLLTests, OpenCLResultLocations)
{
    std::vector<unsigned int> counters =
    {
        WavefrontsCLGfx6,
        VALUInstsCLGfx6,
        SALUInstsCLGfx6,
        VFetchInstsCLGfx6,
        SFetchInstsCLGfx6,
        VWriteInstsCLGfx6,
        VALUUtilizationCLGfx6,
        VALUBusyCLGfx6,
        SALUBusyCLGfx6,
    };

    std::vector<uint32_t> expectedCountersPass0 =
    {
        1649, 1639, 1653, 1651, 1654, 1650, 1693, 1685, 976
    };

    std::vector<uint32_t> expectedCountersPass1 =
    {
        1690, 976,
    };

    std::vector< std::vector<uint32_t> > expectedHwCountersPerPass =
    {
        expectedCountersPass0,
        expectedCountersPass1,
    };

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsWavefronts =
    {
        MakeExpectedCounterLocationEntry(0, 1)
    };

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsVALUInsts =
    {
        MakeExpectedCounterLocationEntry(0, 1)
        MakeExpectedCounterLocationEntry(0, 0)
    };

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsSALUInsts =
    {
        MakeExpectedCounterLocationEntry(0, 1)
        MakeExpectedCounterLocationEntry(0, 2)
    };

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsVFetchInsts =
    {
        MakeExpectedCounterLocationEntry(0, 1)
        MakeExpectedCounterLocationEntry(0, 3)
    };

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsSFetchInsts =
    {
        MakeExpectedCounterLocationEntry(0, 1)
        MakeExpectedCounterLocationEntry(0, 4)
    };

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsVWriteInsts =
    {
        MakeExpectedCounterLocationEntry(0, 1)
        MakeExpectedCounterLocationEntry(0, 5)
    };

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsVALUUtilization =
    {
        MakeExpectedCounterLocationEntry(0, 7)
        MakeExpectedCounterLocationEntry(0, 6)
    };

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsVALUBusy =
    {
        MakeExpectedCounterLocationEntry(0, 8)
        MakeExpectedCounterLocationEntry(0, 7)
    };

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsSALUBusy =
    {
        MakeExpectedCounterLocationEntry(1, 1)
        MakeExpectedCounterLocationEntry(1, 0)
    };

    std::map< unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > expectedResultLocations =
    {
        { WavefrontsCLGfx6, expectedLocationsWavefronts },
        { VALUInstsCLGfx6, expectedLocationsVALUInsts },
        { SALUInstsCLGfx6, expectedLocationsSALUInsts },
        { VFetchInstsCLGfx6, expectedLocationsVFetchInsts },
        { SFetchInstsCLGfx6, expectedLocationsSFetchInsts },
        { VWriteInstsCLGfx6, expectedLocationsVWriteInsts },
        { VALUUtilizationCLGfx6, expectedLocationsVALUUtilization },
        { VALUBusyCLGfx6, expectedLocationsVALUBusy },
        { SALUBusyCLGfx6, expectedLocationsSALUBusy }
    };

    VerifyCountersInPass(GPA_API_OPENCL, gDevIdSI, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
}

TEST(CounterDLLTests, OpenGLCounterScheduling)
{
    std::vector<unsigned int> counters;
    counters.push_back(GPUTimeGLGfx6);
    counters.push_back(GPUBusyGLGfx6);
    counters.push_back(TessellatorBusyGLGfx6);

    VerifyHardwareNotSupported(GPA_API_OPENGL, gDevIdUnknown, FALSE);
    VerifyPassCount(GPA_API_OPENGL, gDevIdSI, FALSE, counters, 2);

    counters.clear();
    counters.push_back(GPUTimeGLGfx7);
    counters.push_back(GPUBusyGLGfx7);
    counters.push_back(TessellatorBusyGLGfx7);
    VerifyPassCount(GPA_API_OPENGL, gDevIdCI, FALSE, counters, 2);

    counters.clear();
    counters.push_back(GPUTimeGLGfx8);
    counters.push_back(GPUBusyGLGfx8);
    counters.push_back(TessellatorBusyGLGfx8);
    VerifyPassCount(GPA_API_OPENGL, gDevIdVI, FALSE, counters, 2);
}

#ifdef _WIN32

TEST(CounterDLLTests, DX11CounterScheduling)
{
    std::vector<unsigned int> counters;
    counters.push_back(GPUTimeDX11Gfx6);
    counters.push_back(GPUBusyDX11Gfx6);
    counters.push_back(TessellatorBusyDX11Gfx6);
    VerifyHardwareNotSupported(GPA_API_DIRECTX_11, gDevIdUnknown, FALSE);
    VerifyPassCount(GPA_API_DIRECTX_11, gDevIdSI, FALSE, counters, 2);

    counters.clear();
    counters.push_back(GPUTimeDX11Gfx7);
    counters.push_back(GPUBusyDX11Gfx7);
    counters.push_back(TessellatorBusyDX11Gfx7);
    VerifyPassCount(GPA_API_DIRECTX_11, gDevIdCI, FALSE, counters, 2);

    counters.clear();
    counters.push_back(GPUTimeDX11Gfx8);
    counters.push_back(GPUBusyDX11Gfx8);
    counters.push_back(TessellatorBusyDX11Gfx8);
    VerifyPassCount(GPA_API_DIRECTX_11, gDevIdVI, FALSE, counters, 2);
}

TEST(CounterDLLTests, DX11CIBusyCounters)
{
    std::vector<unsigned int> counters =
    {
        VSBusyDX11Gfx7,
        HSBusyDX11Gfx7,
        DSBusyDX11Gfx7,
        GSBusyDX11Gfx7,
        PSBusyDX11Gfx7,
        CSBusyDX11Gfx7
    };

    std::vector<uint32_t> expectedCountersPass0 =
    {
        10306, 10492, 10678, 10864, 10331, 10517, 10703, 10889, 10353, 10539,
        10725, 10911, 10375, 10561, 10747, 10933, 10315, 10501, 10687, 10873,
        10337, 10523, 10709, 10895, 7886
    };

    std::vector<uint32_t> expectedCountersPass1 =
    {
        10306, 10492, 10678, 10864, 10331, 10517, 10703, 10889, 10375, 10561,
        10747, 10933, 10337, 10523, 10709, 10895, 10359, 10545, 10731, 10917,
        7886, 10380, 10566, 10752, 10938
    };

    std::vector<uint32_t> expectedCountersPass2 =
    {
        10343, 10529, 10715, 10901, 10349, 10535, 10721, 10907, 7886, 10322,
        10508, 10694, 10880, 10325, 10511, 10697, 10883, 10363, 10549, 10735,
        10921, 10367, 10553, 10739, 10925
    };

    std::vector< std::vector<uint32_t> > expectedHwCountersPerPass =
    {
        expectedCountersPass0,
        expectedCountersPass1,
        expectedCountersPass2
    };

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsVSBusyDX11Gfx7 =
    {
        MakeExpectedCounterLocationEntry(0, 24)
        MakeExpectedCounterLocationEntry(0, 0)
        MakeExpectedCounterLocationEntry(0, 16)
        MakeExpectedCounterLocationEntry(0, 4)
        MakeExpectedCounterLocationEntry(0, 20)
        MakeExpectedCounterLocationEntry(0, 8)
        MakeExpectedCounterLocationEntry(1, 16)
        MakeExpectedCounterLocationEntry(0, 12)
        MakeExpectedCounterLocationEntry(0, 1)
        MakeExpectedCounterLocationEntry(0, 17)
        MakeExpectedCounterLocationEntry(0, 5)
        MakeExpectedCounterLocationEntry(0, 21)
        MakeExpectedCounterLocationEntry(0, 9)
        MakeExpectedCounterLocationEntry(1, 17)
        MakeExpectedCounterLocationEntry(0, 13)
        MakeExpectedCounterLocationEntry(0, 2)
        MakeExpectedCounterLocationEntry(0, 18)
        MakeExpectedCounterLocationEntry(0, 6)
        MakeExpectedCounterLocationEntry(0, 22)
        MakeExpectedCounterLocationEntry(0, 10)
        MakeExpectedCounterLocationEntry(1, 18)
        MakeExpectedCounterLocationEntry(0, 14)
        MakeExpectedCounterLocationEntry(0, 3)
        MakeExpectedCounterLocationEntry(0, 19)
        MakeExpectedCounterLocationEntry(0, 7)
        MakeExpectedCounterLocationEntry(0, 23)
        MakeExpectedCounterLocationEntry(0, 11)
        MakeExpectedCounterLocationEntry(1, 19)
        MakeExpectedCounterLocationEntry(0, 15)
    };

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsHSBusyDX11Gfx7 =
    {
        MakeExpectedCounterLocationEntry(2, 8)
        MakeExpectedCounterLocationEntry(2, 0)
        MakeExpectedCounterLocationEntry(2, 4)
        MakeExpectedCounterLocationEntry(2, 1)
        MakeExpectedCounterLocationEntry(2, 5)
        MakeExpectedCounterLocationEntry(2, 2)
        MakeExpectedCounterLocationEntry(2, 6)
        MakeExpectedCounterLocationEntry(2, 3)
        MakeExpectedCounterLocationEntry(2, 7)
    };

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsDSBusyDX11Gfx7 =
    {
        MakeExpectedCounterLocationEntry(1, 20)
        MakeExpectedCounterLocationEntry(1, 0)
        MakeExpectedCounterLocationEntry(1, 4)
        MakeExpectedCounterLocationEntry(1, 12)
        MakeExpectedCounterLocationEntry(1, 16)
        MakeExpectedCounterLocationEntry(1, 8)
        MakeExpectedCounterLocationEntry(1, 1)
        MakeExpectedCounterLocationEntry(1, 5)
        MakeExpectedCounterLocationEntry(1, 13)
        MakeExpectedCounterLocationEntry(1, 17)
        MakeExpectedCounterLocationEntry(1, 9)
        MakeExpectedCounterLocationEntry(1, 2)
        MakeExpectedCounterLocationEntry(1, 6)
        MakeExpectedCounterLocationEntry(1, 14)
        MakeExpectedCounterLocationEntry(1, 18)
        MakeExpectedCounterLocationEntry(1, 10)
        MakeExpectedCounterLocationEntry(1, 3)
        MakeExpectedCounterLocationEntry(1, 7)
        MakeExpectedCounterLocationEntry(1, 15)
        MakeExpectedCounterLocationEntry(1, 19)
        MakeExpectedCounterLocationEntry(1, 11)
    };

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsGSBusyDX11Gfx7 =
    {
        MakeExpectedCounterLocationEntry(2, 8)
        MakeExpectedCounterLocationEntry(2, 9)
        MakeExpectedCounterLocationEntry(2, 13)
        MakeExpectedCounterLocationEntry(2, 10)
        MakeExpectedCounterLocationEntry(2, 14)
        MakeExpectedCounterLocationEntry(2, 11)
        MakeExpectedCounterLocationEntry(2, 15)
        MakeExpectedCounterLocationEntry(2, 12)
        MakeExpectedCounterLocationEntry(2, 16)
    };

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsPSBusyDX11Gfx7 =
    {
        MakeExpectedCounterLocationEntry(1, 20)
        MakeExpectedCounterLocationEntry(1, 8)
        MakeExpectedCounterLocationEntry(1, 21)
        MakeExpectedCounterLocationEntry(1, 9)
        MakeExpectedCounterLocationEntry(1, 22)
        MakeExpectedCounterLocationEntry(1, 10)
        MakeExpectedCounterLocationEntry(1, 23)
        MakeExpectedCounterLocationEntry(1, 11)
        MakeExpectedCounterLocationEntry(1, 24)
    };

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsCSBusyDX11Gfx7 =
    {
        MakeExpectedCounterLocationEntry(2, 8)
        MakeExpectedCounterLocationEntry(2, 17)
        MakeExpectedCounterLocationEntry(2, 21)
        MakeExpectedCounterLocationEntry(2, 18)
        MakeExpectedCounterLocationEntry(2, 22)
        MakeExpectedCounterLocationEntry(2, 19)
        MakeExpectedCounterLocationEntry(2, 23)
        MakeExpectedCounterLocationEntry(2, 20)
        MakeExpectedCounterLocationEntry(2, 24)
    };

    std::map< unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > expectedResultLocations =
    {
        { VSBusyDX11Gfx7, expectedLocationsVSBusyDX11Gfx7 },
        { HSBusyDX11Gfx7, expectedLocationsHSBusyDX11Gfx7 },
        { DSBusyDX11Gfx7, expectedLocationsDSBusyDX11Gfx7 },
        { GSBusyDX11Gfx7, expectedLocationsGSBusyDX11Gfx7 },
        { PSBusyDX11Gfx7, expectedLocationsPSBusyDX11Gfx7 },
        { CSBusyDX11Gfx7, expectedLocationsCSBusyDX11Gfx7 }
    };

    VerifyCountersInPass(GPA_API_DIRECTX_11, gDevIdCI, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
}

// regression test for GPA-123
TEST(CounterDLLTests, DX11CIHSBusyHSTimeGSTime)
{
    std::vector<unsigned int> counters;
    counters.push_back(HSBusyDX11Gfx7); // HSBusy
    counters.push_back(HSTimeDX11Gfx7); // HSTime
    counters.push_back(GSTimeDX11Gfx7); // GSTime

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsHSBusy;
    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsHSTime;
    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsGSTime;


    std::vector<unsigned int> expectedCountersPass1;
    std::vector<unsigned int> expectedCountersPass2;
    // HSBusy
    expectedCountersPass1.push_back(10343); expectedLocationsHSBusy[10343] = MakeLocation(0, 0);
    expectedCountersPass1.push_back(10529); expectedLocationsHSBusy[10529] = MakeLocation(0, 1);
    expectedCountersPass1.push_back(10715); expectedLocationsHSBusy[10715] = MakeLocation(0, 2);
    expectedCountersPass1.push_back(10901); expectedLocationsHSBusy[10901] = MakeLocation(0, 3);
    expectedCountersPass1.push_back(10349); expectedLocationsHSBusy[10349] = MakeLocation(0, 4);
    expectedCountersPass1.push_back(10535); expectedLocationsHSBusy[10535] = MakeLocation(0, 5);
    expectedCountersPass1.push_back(10721); expectedLocationsHSBusy[10721] = MakeLocation(0, 6);
    expectedCountersPass1.push_back(10907); expectedLocationsHSBusy[10907] = MakeLocation(0, 7);
    expectedCountersPass1.push_back(7886);  expectedLocationsHSBusy[7886] = MakeLocation(0, 8);
    // HSTime
    expectedCountersPass2.push_back(36851);  expectedLocationsHSTime[36851] = MakeLocation(1, 0);
    /*expectedCountersPass1.push_back(10343); */ expectedLocationsHSTime[10343] = MakeLocation(0, 0);  //reused from HSBusy
    /*expectedCountersPass1.push_back(10529); */ expectedLocationsHSTime[10529] = MakeLocation(0, 1);  //reused from HSBusy
    /*expectedCountersPass1.push_back(10715); */ expectedLocationsHSTime[10715] = MakeLocation(0, 2);  //reused from HSBusy
    /*expectedCountersPass1.push_back(10901); */ expectedLocationsHSTime[10901] = MakeLocation(0, 3);  //reused from HSBusy
    /*expectedCountersPass1.push_back(10349); */ expectedLocationsHSTime[10349] = MakeLocation(0, 4);  //reused from HSBusy
    /*expectedCountersPass1.push_back(10535); */ expectedLocationsHSTime[10535] = MakeLocation(0, 5);  //reused from HSBusy
    /*expectedCountersPass1.push_back(10721); */ expectedLocationsHSTime[10721] = MakeLocation(0, 6); //reused from HSBusy
    /*expectedCountersPass1.push_back(10907); */ expectedLocationsHSTime[10907] = MakeLocation(0, 7); //reused from HSBusy
    /*expectedCountersPass1.push_back(7886);  */ expectedLocationsHSTime[7886] = MakeLocation(0, 8);  //reused from HSBusy
    // GSTime
    /*expectedCountersPass2.push_back(36851); */expectedLocationsGSTime[36851] = MakeLocation(1, 0);  //reused from HSTime
    expectedCountersPass1.push_back(10322); expectedLocationsGSTime[10322] = MakeLocation(0, 9);
    expectedCountersPass1.push_back(10508); expectedLocationsGSTime[10508] = MakeLocation(0, 10);
    expectedCountersPass1.push_back(10694); expectedLocationsGSTime[10694] = MakeLocation(0, 11);
    expectedCountersPass1.push_back(10880); expectedLocationsGSTime[10880] = MakeLocation(0, 12);
    expectedCountersPass1.push_back(10325); expectedLocationsGSTime[10325] = MakeLocation(0, 13);
    expectedCountersPass1.push_back(10511); expectedLocationsGSTime[10511] = MakeLocation(0, 14);
    expectedCountersPass1.push_back(10697); expectedLocationsGSTime[10697] = MakeLocation(0, 15);
    expectedCountersPass1.push_back(10883); expectedLocationsGSTime[10883] = MakeLocation(0, 16);
    /*expectedCountersPass1.push_back(7886); */ expectedLocationsGSTime[7886] = MakeLocation(0, 8);  //reused from HSBusy

    std::vector< std::vector<unsigned int> > expectedHwCountersPerPass;
    expectedHwCountersPerPass.push_back(expectedCountersPass1);
    expectedHwCountersPerPass.push_back(expectedCountersPass2);

    std::map< unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > expectedResultLocations;
    expectedResultLocations[HSBusyDX11Gfx7] = expectedLocationsHSBusy;
    expectedResultLocations[HSTimeDX11Gfx7] = expectedLocationsHSTime;
    expectedResultLocations[GSTimeDX11Gfx7] = expectedLocationsGSTime;

    VerifyCountersInPass(GPA_API_DIRECTX_11, gDevIdCI, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
}

// regression test related to GPA-123
TEST(CounterDLLTests, DX11CIHSTimeGSTime)
{
    std::vector<unsigned int> counters =
    {
        HSTimeDX11Gfx7,
        GSTimeDX11Gfx7,
    };


    std::vector<uint32_t> expectedCountersPass0 =
    {
        10343, 10529, 10715, 10901, 10349, 10535, 10721, 10907, 7886,
        10322, 10508, 10694, 10880, 10325, 10511, 10697, 10883
    };

    std::vector<uint32_t> expectedCountersPass1 =
    {
        36851
    };

    std::vector< std::vector<uint32_t> > expectedHwCountersPerPass =
    {
        expectedCountersPass0,
        expectedCountersPass1
    };

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsHSTimeDX11Gfx7 =
    {
        MakeExpectedCounterLocationEntry(0, 8)
        MakeExpectedCounterLocationEntry(0, 0)
        MakeExpectedCounterLocationEntry(0, 4)
        MakeExpectedCounterLocationEntry(0, 1)
        MakeExpectedCounterLocationEntry(0, 5)
        MakeExpectedCounterLocationEntry(0, 2)
        MakeExpectedCounterLocationEntry(0, 6)
        MakeExpectedCounterLocationEntry(0, 3)
        MakeExpectedCounterLocationEntry(0, 7)
        MakeExpectedCounterLocationEntry(1, 0)
    };

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsGSTimeDX11Gfx7 =
    {
        MakeExpectedCounterLocationEntry(0, 8)
        MakeExpectedCounterLocationEntry(0, 9)
        MakeExpectedCounterLocationEntry(0, 13)
        MakeExpectedCounterLocationEntry(0, 10)
        MakeExpectedCounterLocationEntry(0, 14)
        MakeExpectedCounterLocationEntry(0, 11)
        MakeExpectedCounterLocationEntry(0, 15)
        MakeExpectedCounterLocationEntry(0, 12)
        MakeExpectedCounterLocationEntry(0, 16)
        MakeExpectedCounterLocationEntry(1, 0)
    };

    std::map< unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > expectedResultLocations =
    {
        { HSTimeDX11Gfx7, expectedLocationsHSTimeDX11Gfx7 },
        { GSTimeDX11Gfx7, expectedLocationsGSTimeDX11Gfx7 }
    };

    VerifyCountersInPass(GPA_API_DIRECTX_11, gDevIdCI, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
}

TEST(CounterDLLTests, DX11CIVSBusy)
{
    std::vector<unsigned int> counters;
    counters.push_back(VSBusyDX11Gfx7);

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsVSBusy;


    std::vector<unsigned int> expectedCountersPass1;
    // VSBusy
    expectedCountersPass1.push_back(10306); expectedLocationsVSBusy[10306] = MakeLocation(0, 0);
    expectedCountersPass1.push_back(10492); expectedLocationsVSBusy[10492] = MakeLocation(0, 1);
    expectedCountersPass1.push_back(10678); expectedLocationsVSBusy[10678] = MakeLocation(0, 2);
    expectedCountersPass1.push_back(10864); expectedLocationsVSBusy[10864] = MakeLocation(0, 3);
    expectedCountersPass1.push_back(10331); expectedLocationsVSBusy[10331] = MakeLocation(0, 4);
    expectedCountersPass1.push_back(10517); expectedLocationsVSBusy[10517] = MakeLocation(0, 5);
    expectedCountersPass1.push_back(10703); expectedLocationsVSBusy[10703] = MakeLocation(0, 6);
    expectedCountersPass1.push_back(10889); expectedLocationsVSBusy[10889] = MakeLocation(0, 7);
    expectedCountersPass1.push_back(10353); expectedLocationsVSBusy[10353] = MakeLocation(0, 8);
    expectedCountersPass1.push_back(10539); expectedLocationsVSBusy[10539] = MakeLocation(0, 9);
    expectedCountersPass1.push_back(10725); expectedLocationsVSBusy[10725] = MakeLocation(0, 10);
    expectedCountersPass1.push_back(10911); expectedLocationsVSBusy[10911] = MakeLocation(0, 11);
    expectedCountersPass1.push_back(10375); expectedLocationsVSBusy[10375] = MakeLocation(0, 12);
    expectedCountersPass1.push_back(10561); expectedLocationsVSBusy[10561] = MakeLocation(0, 13);
    expectedCountersPass1.push_back(10747); expectedLocationsVSBusy[10747] = MakeLocation(0, 14);
    expectedCountersPass1.push_back(10933); expectedLocationsVSBusy[10933] = MakeLocation(0, 15);
    expectedCountersPass1.push_back(10315); expectedLocationsVSBusy[10315] = MakeLocation(0, 16);
    expectedCountersPass1.push_back(10501); expectedLocationsVSBusy[10501] = MakeLocation(0, 17);
    expectedCountersPass1.push_back(10687); expectedLocationsVSBusy[10687] = MakeLocation(0, 18);
    expectedCountersPass1.push_back(10873); expectedLocationsVSBusy[10873] = MakeLocation(0, 19);
    expectedCountersPass1.push_back(10337); expectedLocationsVSBusy[10337] = MakeLocation(0, 20);
    expectedCountersPass1.push_back(10523); expectedLocationsVSBusy[10523] = MakeLocation(0, 21);
    expectedCountersPass1.push_back(10709); expectedLocationsVSBusy[10709] = MakeLocation(0, 22);
    expectedCountersPass1.push_back(10895); expectedLocationsVSBusy[10895] = MakeLocation(0, 23);
    expectedCountersPass1.push_back(7886);  expectedLocationsVSBusy[7886] = MakeLocation(0, 24);

    std::vector<unsigned int> expectedCountersPass2;
    // VSBusy
    expectedCountersPass2.push_back(10359); expectedLocationsVSBusy[10359] = MakeLocation(1, 0);
    expectedCountersPass2.push_back(10545); expectedLocationsVSBusy[10545] = MakeLocation(1, 1);
    expectedCountersPass2.push_back(10731); expectedLocationsVSBusy[10731] = MakeLocation(1, 2);
    expectedCountersPass2.push_back(10917); expectedLocationsVSBusy[10917] = MakeLocation(1, 3);

    std::vector< std::vector<unsigned int> > expectedHwCountersPerPass;
    expectedHwCountersPerPass.push_back(expectedCountersPass1);
    expectedHwCountersPerPass.push_back(expectedCountersPass2);

    std::map< unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > expectedResultLocations;
    expectedResultLocations[VSBusyDX11Gfx7] = expectedLocationsVSBusy;

    VerifyCountersInPass(GPA_API_DIRECTX_11, gDevIdCI, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
}

void TestGPUTimeVSBusyVSTimeCountersForDevice(unsigned int deviceId)
{
    // checks that different combinations of GPUTime / VSBusy / VSTime are scheduled correctly regardless of order of inclusion
    static uint32_t GPUTimeIndex;
    static uint32_t VSBusyIndex;
    static uint32_t VSTimeIndex;
    uint32_t expectedPasses = 0;

    if (gDevIdSI == deviceId)
    {
        GPUTimeIndex = GPUTimeDX11Gfx6;
        VSBusyIndex = VSBusyDX11Gfx6;
        VSTimeIndex = VSTimeDX11Gfx6;
        expectedPasses = 3;
    }
    else if (gDevIdCI == deviceId)
    {
        GPUTimeIndex = GPUTimeDX11Gfx7;
        VSBusyIndex = VSBusyDX11Gfx7;
        VSTimeIndex = VSTimeDX11Gfx7;
        expectedPasses = 3;
    }
    else if (gDevIdVI == deviceId)
    {
        GPUTimeIndex = GPUTimeDX11Gfx8;
        VSBusyIndex = VSBusyDX11Gfx8;
        VSTimeIndex = VSTimeDX11Gfx8;
        expectedPasses = 3;
    }
    else if (gDevIdGfx9 == deviceId)
    {
        GPUTimeIndex = GPUTimeDX11Gfx9;
        VSBusyIndex = VSBusyDX11Gfx9;
        VSTimeIndex = VSTimeDX11Gfx9;
        expectedPasses = 2;
    }

    // counters to enable (GPUTime, VSBusy)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> { GPUTimeIndex, VSBusyIndex }, expectedPasses);

    // counters to enable (VSBusy, GPUTime)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> { VSBusyIndex, GPUTimeIndex }, expectedPasses);

    // counters to enable (VSBusy, VSTime)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> { VSBusyIndex, VSTimeIndex }, expectedPasses);

    // counters to enable (VSTime, VSBusy)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> { VSTimeIndex, VSBusyIndex }, expectedPasses);

    // counters to enable (GPUTime, VSTime)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> { GPUTimeIndex, VSTimeIndex }, expectedPasses);

    // counters to enable (VSTime, GPUTime)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> { VSTimeIndex, GPUTimeIndex}, expectedPasses);

    // counters to enable (GPUTime, VSBusy, VSTime)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> { GPUTimeIndex, VSBusyIndex, VSTimeIndex}, expectedPasses);

    // counters to enable (GPUTime, VSTime, VSBusy)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> { GPUTimeIndex, VSTimeIndex, VSBusyIndex }, expectedPasses);

    // counters to enable (VSTime, GPUTime, VSBusy)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> { VSTimeIndex, GPUTimeIndex, VSBusyIndex }, expectedPasses);

    // counters to enable (VSTime, VSBusy, GPUTime)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> { VSTimeIndex, VSBusyIndex, GPUTimeIndex}, expectedPasses);

    // counters to enable (VSBusy, GPUTime, VSTime)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> { VSBusyIndex, GPUTimeIndex, VSTimeIndex }, expectedPasses);

    // counters to enable (VSBusy, VSTime, GPUTime)
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, FALSE, std::vector<uint32_t> { VSBusyIndex, VSTimeIndex, GPUTimeIndex}, expectedPasses);
}

TEST(CounterDLLTests, DX11VIGPUTimeVSBusyVSTimeCounters)
{
    TestGPUTimeVSBusyVSTimeCountersForDevice(gDevIdVI);
}

TEST(CounterDLLTests, DX11CIGPUTimeVSBusyVSTimeCounters)
{
    TestGPUTimeVSBusyVSTimeCountersForDevice(gDevIdCI);
}

TEST(CounterDLLTests, DX11SIGPUTimeVSBusyVSTimeCounters)
{
    TestGPUTimeVSBusyVSTimeCountersForDevice(gDevIdSI);
}

TEST(CounterDLLTests, DX11Gfx9GPUTimeVSBusyVSTimeCounters)
{
    TestGPUTimeVSBusyVSTimeCountersForDevice(gDevIdGfx9);
}

void TestD3D11QueryCounter(unsigned int deviceId, unsigned int D3DQueryCounterIndex, unsigned int publicCounterCount, unsigned int hardwareCounterCount, unsigned int gpuTimeHWCounterIndex = 0)
{
    std::vector<unsigned int> counters;

    static const int GPUTimePublicCounterIndex = 0; // public GPUTime counter is always index 0

    if (gpuTimeHWCounterIndex != 0)
    {
        counters.push_back(GPUTimePublicCounterIndex);
    }

    // the D3D query counters appear after the public counters
    unsigned int queryCounterIndex = publicCounterCount + D3DQueryCounterIndex;

#ifdef AMDT_INTERNAL
    // in the internal build, the D3D query counters are also after the hardware counters
    queryCounterIndex += hardwareCounterCount;
#endif

    counters.push_back(queryCounterIndex);

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsGPUTime;
    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsD3DQuery;

    std::vector<unsigned int> expectedCountersPass1;
    std::vector<unsigned int> expectedCountersPass2;

    if (gpuTimeHWCounterIndex != 0)
    {
        // GPUTime
        expectedCountersPass1.push_back(gpuTimeHWCounterIndex); // the internal counter
        expectedLocationsGPUTime[gpuTimeHWCounterIndex] = MakeLocation(0, 0);

        // D3DQuery
        expectedCountersPass2.push_back(hardwareCounterCount + D3DQueryCounterIndex);
        expectedLocationsD3DQuery[hardwareCounterCount + D3DQueryCounterIndex] = MakeLocation(1, 0);
    }
    else
    {
        // D3DQuery
        expectedCountersPass1.push_back(hardwareCounterCount + D3DQueryCounterIndex);
        expectedLocationsD3DQuery[hardwareCounterCount + D3DQueryCounterIndex] = MakeLocation(0, 0);
    }

    std::vector< std::vector<unsigned int> > expectedHwCountersPerPass;
    expectedHwCountersPerPass.push_back(expectedCountersPass1);

    if (!expectedCountersPass2.empty())
    {
        expectedHwCountersPerPass.push_back(expectedCountersPass2);
    }

    std::map< unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > expectedResultLocations;

    if (gpuTimeHWCounterIndex != 0)
    {
        // GPUTime
        expectedResultLocations[GPUTimePublicCounterIndex] = expectedLocationsGPUTime;
    }

    expectedResultLocations[queryCounterIndex] = expectedLocationsD3DQuery;

    VerifyCountersInPass(GPA_API_DIRECTX_11, deviceId, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
}

// Disable Software counter tests
/*
static unsigned int GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_Hw_Generation generation, unsigned int* pBottomToBottomIndex = nullptr )
{
    unsigned int numHwCounters = 0;

    GPA_CounterGroupDesc* pHardwareGroups = nullptr;
    unsigned int hwGroupCount = 0;

    switch (generation)
    {
        case GPA_HW_GENERATION_GFX6:
            pHardwareGroups = HWDX11GroupsGfx6;
            hwGroupCount = HWDX11GroupCountGfx6;
            if (pBottomToBottomIndex)
            {
                *pBottomToBottomIndex = HWDX11GPUTimeBottomToBottomIndexGfx6;
            }
            break;

        case GPA_HW_GENERATION_GFX7:
            pHardwareGroups = HWDX11GroupsGfx7;
            hwGroupCount = HWDX11GroupCountGfx7;
            if (pBottomToBottomIndex)
            {
                *pBottomToBottomIndex = HWDX11GPUTimeBottomToBottomIndexGfx7;
            }
            break;

        case GPA_HW_GENERATION_GFX8:
            pHardwareGroups = HWDX11GroupsGfx8;
            hwGroupCount = HWDX11GroupCountGfx8;
            if (pBottomToBottomIndex)
            {
                *pBottomToBottomIndex = HWDX11GPUTimeBottomToBottomIndexGfx8;
            }
            break;
    }

    for (unsigned int i = 0; i < hwGroupCount; i++)
    {
        numHwCounters += pHardwareGroups[i].m_numCounters;
    }

    return numHwCounters;
}

/// Test the D3D11 QUERY counters (software counters) across different generations
TEST(CounterDLLTests, DX11D3DCounters)
{
    unsigned int D3DCounterIndex      = 0;  // this is the index into the software counters of "OCCLUSION" - see GPASwCounterManager.h
    unsigned int publicCounterCount   = 0;  // this is the number of public counters exposed
    unsigned int hardwareCounterCount = 0;  // this is the number of hardware counters exposed, which is used to offset the sw counter index

    // Gfx6
    D3DCounterIndex      = 1;
    publicCounterCount  = DX11GFX6_PUBLIC_COUNTER_COUNT;
    hardwareCounterCount = GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION_GFX6);
    TestD3D11QueryCounter(gDevIdSI, D3DCounterIndex, publicCounterCount, hardwareCounterCount);

    // Gfx7
    D3DCounterIndex      = 1;
    publicCounterCount  = DX11GFX7_PUBLIC_COUNTER_COUNT;
    hardwareCounterCount = GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION_GFX7);
    TestD3D11QueryCounter(gDevIdCI, D3DCounterIndex, publicCounterCount, hardwareCounterCount);

    // Gfx8
    D3DCounterIndex      = 1;
    publicCounterCount  = DX11GFX8_PUBLIC_COUNTER_COUNT;
    hardwareCounterCount = GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION_GFX8);
    TestD3D11QueryCounter(gDevIdVI, D3DCounterIndex, publicCounterCount, hardwareCounterCount);
}

TEST(CounterDLLTests, DX11D3DCountersAndGPUTime)
{
    unsigned int gpuTimeHWIndex = 0;
    unsigned int D3DCounterIndex      = 0;  // this is the index into the software counters of "OCCLUSION" - see GPASwCounterManager.h
    unsigned int publicCounterCount   = 0;  // this is the number of public counters exposed
    unsigned int hardwareCounterCount = 0;  // this is the number of hardware counters exposed, which is used to offset the sw counter index

    // Gfx6
    D3DCounterIndex      = 1;
    publicCounterCount   = DX11GFX6_PUBLIC_COUNTER_COUNT;
    hardwareCounterCount = GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION_GFX6, &gpuTimeHWIndex);
    TestD3D11QueryCounter(gDevIdSI, D3DCounterIndex, publicCounterCount, hardwareCounterCount, gpuTimeHWIndex);

    // Gfx7
    D3DCounterIndex      = 1;
    publicCounterCount   = DX11GFX7_PUBLIC_COUNTER_COUNT;
    hardwareCounterCount = GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION_GFX7, &gpuTimeHWIndex);
    TestD3D11QueryCounter(gDevIdCI, D3DCounterIndex, publicCounterCount, hardwareCounterCount, gpuTimeHWIndex);

    // Gfx8
    D3DCounterIndex      = 1;
    publicCounterCount   = DX11GFX8_PUBLIC_COUNTER_COUNT;
    hardwareCounterCount = GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION_GFX8, &gpuTimeHWIndex);
    TestD3D11QueryCounter(gDevIdVI, D3DCounterIndex, publicCounterCount, hardwareCounterCount, gpuTimeHWIndex);
}

void TestAllD3D11QueryCounters(unsigned int deviceId, unsigned int D3DQueryCounterCount, unsigned int publicCounterCount, unsigned int hardwareCounterCount)
{
    std::vector<unsigned int> counters;
    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsD3DQuery;
    std::vector<unsigned int> expectedCountersPass1;
    std::vector<unsigned int> expectedCountersPass2;
    std::map< unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > expectedResultLocations;

    for (gpa_uint16 i = 0; i < D3DQueryCounterCount; i++)
    {
        // the D3D query counters appear after the public counters
        unsigned int queryCounterIndex = publicCounterCount + i;

#ifdef AMDT_INTERNAL
        // in the internal build, the D3D query counters are also after the hardware counters
        queryCounterIndex += hardwareCounterCount;
#endif

        counters.push_back(queryCounterIndex);
        expectedLocationsD3DQuery.clear();

        if (0 == i) //SW GPUTime counter need a separate pass
        {
            expectedCountersPass1.push_back(hardwareCounterCount + i);
            expectedLocationsD3DQuery[hardwareCounterCount + i] = MakeLocation(0, i);
        }
        else
        {
            expectedCountersPass2.push_back(hardwareCounterCount + i);
            expectedLocationsD3DQuery[hardwareCounterCount + i] = MakeLocation(1, i - 1);
        }

        expectedResultLocations[queryCounterIndex] = expectedLocationsD3DQuery;
    }

    std::vector< std::vector<unsigned int> > expectedHwCountersPerPass;
    expectedHwCountersPerPass.push_back(expectedCountersPass1);
    expectedHwCountersPerPass.push_back(expectedCountersPass2);

    VerifyCountersInPass(GPA_API_DIRECTX_11, deviceId, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
}

TEST(CounterDLLTests, AllDX11D3DCounters)
{
    unsigned int publicCounterCount = 0;  // this is the number of public counters exposed
    unsigned int hardwareCounterCount = 0;  // this is the number of hardware counters exposed, which is used to offset the sw counter index
    unsigned int D3DQueryCounterCount = 29; // there are currently 29 D3D11 query counters

    // Gfx6
    publicCounterCount   = DX11GFX6_PUBLIC_COUNTER_COUNT;
    hardwareCounterCount = GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION_GFX6);
    TestAllD3D11QueryCounters(gDevIdSI, D3DQueryCounterCount, publicCounterCount, hardwareCounterCount);

    // Gfx7
    publicCounterCount   = DX11GFX7_PUBLIC_COUNTER_COUNT;
    hardwareCounterCount = GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION_GFX7);
    TestAllD3D11QueryCounters(gDevIdCI, D3DQueryCounterCount, publicCounterCount, hardwareCounterCount);

    // Gfx8
    publicCounterCount   = DX11GFX8_PUBLIC_COUNTER_COUNT;
    hardwareCounterCount = GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION_GFX8);
    TestAllD3D11QueryCounters(gDevIdVI, D3DQueryCounterCount, publicCounterCount, hardwareCounterCount);
}
*/

TEST(CounterDLLTests, DX11CIPSBusyCounterResult)
{
    // test the result of PSBusy, which uses 9 internal counters
    unsigned int requiredCount = 9;

    // fabricate some results that will allow us to confirm the PSBusy counter
    // each result is 64 bit, so 8 chars.
    gpa_uint64* pAllResults = new(std::nothrow) gpa_uint64[requiredCount * 8];
    ASSERT_TRUE(nullptr != pAllResults);
    memset(pAllResults, 0, requiredCount * 8);

    pAllResults[0 * 8] = 1;
    pAllResults[1 * 8] = 1;
    pAllResults[2 * 8] = 1;
    pAllResults[3 * 8] = 1;
    pAllResults[4 * 8] = 1;
    pAllResults[5 * 8] = 1;
    pAllResults[6 * 8] = 1;
    pAllResults[7 * 8] = 1;
    pAllResults[8 * 8] = 2; // GUI_ACTIVE

    // copy results into the vector
    std::vector< gpa_uint64* > sampleResults;

    for (unsigned int i = 0; i < requiredCount; i++)
    {
        sampleResults.push_back(&(pAllResults[i * 8]));
    }

    VerifyCounterCalculation(GPA_API_DIRECTX_11, gDevIdCI, FALSE, "PSBusy", sampleResults, 50);

    delete[] pAllResults;

}

TEST(CounterDLLTests, DX11VIPSBusyCounterResult)
{
    // test the result of PSBusy, which uses 9 internal counters
    unsigned int requiredCount = 9;

    // fabricate some results that will allow us to confirm the PSBusy counter
    // each result is 64 bit, so 8 chars.
    gpa_uint64* pAllResults = new(std::nothrow) gpa_uint64[requiredCount * 8];
    ASSERT_TRUE(nullptr != pAllResults);
    memset(pAllResults, 0, requiredCount * 8);

    pAllResults[0 * 8] = 1;
    pAllResults[1 * 8] = 1;
    pAllResults[2 * 8] = 1;
    pAllResults[3 * 8] = 1;
    pAllResults[4 * 8] = 1;
    pAllResults[5 * 8] = 1;
    pAllResults[6 * 8] = 1;
    pAllResults[7 * 8] = 1;
    pAllResults[8 * 8] = 2; // GUI_ACTIVE

    // copy results into the vector
    std::vector< gpa_uint64* > sampleResults;

    for (unsigned int i = 0; i < requiredCount; i++)
    {
        sampleResults.push_back(&(pAllResults[i * 8]));
    }

    VerifyCounterCalculation(GPA_API_DIRECTX_11, gDevIdVI, FALSE, "PSBusy", sampleResults, 50);

    delete[] pAllResults;

}

TEST(CounterDLLTests, DX11EnableAndDisable)
{
    GPA_API_Type api = GPA_API_DIRECTX_11;
    unsigned int deviceId = gDevIdVI;

    HMODULE hDll = LoadLibraryA("GPUPerfAPICounters" AMDT_PROJECT_SUFFIX ".dll");
    ASSERT_NE((HMODULE)nullptr, hDll);

    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetProcAddress(hDll, "GPA_GetAvailableCounters");
    ASSERT_NE((GPA_GetAvailableCountersProc)nullptr, GPA_GetAvailableCounters_fn);

    IGPACounterAccessor* pCounterAccessor = nullptr;
    IGPACounterScheduler* pCounterScheduler = nullptr;
    GPA_Status status = GPA_GetAvailableCounters_fn(api, AMD_VENDOR_ID, deviceId, REVISION_ID_ANY, GPA_OPENCONTEXT_DEFAULT_BIT, FALSE, &pCounterAccessor, &pCounterScheduler);
    EXPECT_EQ(GPA_STATUS_OK, status);
    EXPECT_NE((IGPACounterAccessor*)nullptr, pCounterAccessor);
    ASSERT_NE((IGPACounterScheduler*)nullptr, pCounterScheduler);

    // enable a counter
    GPA_Status enabled = pCounterScheduler->EnableCounter(0);
    EXPECT_EQ(GPA_STATUS_OK, enabled);

    gpa_uint32 requiredPasses = 0;
    GPA_Status passCountStatus = pCounterScheduler->GetNumRequiredPasses(&requiredPasses);
    EXPECT_EQ(GPA_STATUS_OK, passCountStatus);
    EXPECT_EQ(1, requiredPasses);

    // enable another counter
    enabled = pCounterScheduler->EnableCounter(1);
    EXPECT_EQ(GPA_STATUS_OK, enabled);

    passCountStatus = pCounterScheduler->GetNumRequiredPasses(&requiredPasses);
    EXPECT_EQ(GPA_STATUS_OK, passCountStatus);
    EXPECT_EQ(2, requiredPasses);

    // disable the counters
    pCounterScheduler->DisableAllCounters();

    passCountStatus = pCounterScheduler->GetNumRequiredPasses(&requiredPasses);
    EXPECT_EQ(GPA_STATUS_OK, passCountStatus);
    EXPECT_EQ(0, requiredPasses);

    // enable the second counter again
    enabled = pCounterScheduler->EnableCounter(1);
    EXPECT_EQ(GPA_STATUS_OK, enabled);

    passCountStatus = pCounterScheduler->GetNumRequiredPasses(&requiredPasses);
    EXPECT_EQ(GPA_STATUS_OK, passCountStatus);
    EXPECT_EQ(1, requiredPasses);
}

#endif

TEST(CounterDLLTests, HSACounterScheduling)
{
    std::vector<unsigned int> counters;
    counters.push_back(0);
    counters.push_back(1);
    counters.push_back(2);

    VerifyHardwareNotSupported(GPA_API_HSA, gDevIdUnknown, FALSE);
    VerifyHardwareNotSupported(GPA_API_HSA, gDevIdSI, FALSE);

    VerifyPassCount(GPA_API_HSA, gDevIdCI, FALSE, counters, 1);
    VerifyPassCount(GPA_API_HSA, gDevIdVI, FALSE, counters, 1);
}

/// GPA-127 Validation test.
/// SQ counters must be isolated from TCC/TA/TCP/TCA/TD counters because PAL is now setting the
/// SQ_PERF_CTRL register field to enable all shader waves when counters from the texture blocks are used.

#ifdef _WIN32

TEST(CounterDLLTests, SqIsolatedCounterSplitScheduler)
{
    // CSVFetchInstsDX11Gfx8 TA and SQ counters
    std::vector<uint32_t> counters = { CSVFetchInstsDX11Gfx8 };

    // Pass: 0  Counters: 64
    std::vector<uint32_t> expectedCountersPass0 =
    {
        23512, 23631, 23750, 23869, 23988, 24107, 24226, 24345, 24464, 24583,
        24702, 24821, 24940, 25059, 25178, 25297, 25416, 25535, 25654, 25773,
        25892, 26011, 26130, 26249, 26368, 26487, 26606, 26725, 26844, 26963,
        27082, 27201, 27320, 27439, 27558, 27677, 27796, 27915, 28034, 28153,
        28272, 28391, 28510, 28629, 28748, 28867, 28986, 29105, 29224, 29343,
        29462, 29581, 29700, 29819, 29938, 30057, 30176, 30295, 30414, 30533,
        30652, 30771, 30890, 31009
    };

    // Pass: 1  Counters: 16
    std::vector<uint32_t> expectedCountersPass1 =
    {
        22243, 22542, 22841, 23140, 22219, 22518, 22817, 23116, 13114, 13311,
        13508, 13705, 13120, 13317, 13514, 13711
    };

    std::vector< std::vector<uint32_t> > expectedHwCountersPerPass =
    {
        expectedCountersPass0,
        expectedCountersPass1
    };

    // Pass: 0  Counters: 74
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations0
    {
        MakeExpectedCounterLocationEntry(1, 8)
        MakeExpectedCounterLocationEntry(1, 12)
        MakeExpectedCounterLocationEntry(1, 9)
        MakeExpectedCounterLocationEntry(1, 13)
        MakeExpectedCounterLocationEntry(1, 10)
        MakeExpectedCounterLocationEntry(1, 14)
        MakeExpectedCounterLocationEntry(1, 11)
        MakeExpectedCounterLocationEntry(1, 15)
        MakeExpectedCounterLocationEntry(1, 4)
        MakeExpectedCounterLocationEntry(1, 0)
        MakeExpectedCounterLocationEntry(1, 5)
        MakeExpectedCounterLocationEntry(1, 1)
        MakeExpectedCounterLocationEntry(1, 6)
        MakeExpectedCounterLocationEntry(1, 2)
        MakeExpectedCounterLocationEntry(1, 7)
        MakeExpectedCounterLocationEntry(1, 3)
        MakeExpectedCounterLocationEntry(0, 0)
        MakeExpectedCounterLocationEntry(0, 1)
        MakeExpectedCounterLocationEntry(0, 2)
        MakeExpectedCounterLocationEntry(0, 3)
        MakeExpectedCounterLocationEntry(0, 4)
        MakeExpectedCounterLocationEntry(0, 5)
        MakeExpectedCounterLocationEntry(0, 6)
        MakeExpectedCounterLocationEntry(0, 7)
        MakeExpectedCounterLocationEntry(0, 8)
        MakeExpectedCounterLocationEntry(0, 9)
        MakeExpectedCounterLocationEntry(0, 10)
        MakeExpectedCounterLocationEntry(0, 11)
        MakeExpectedCounterLocationEntry(0, 12)
        MakeExpectedCounterLocationEntry(0, 13)
        MakeExpectedCounterLocationEntry(0, 14)
        MakeExpectedCounterLocationEntry(0, 15)
        MakeExpectedCounterLocationEntry(0, 16)
        MakeExpectedCounterLocationEntry(0, 17)
        MakeExpectedCounterLocationEntry(0, 18)
        MakeExpectedCounterLocationEntry(0, 19)
        MakeExpectedCounterLocationEntry(0, 20)
        MakeExpectedCounterLocationEntry(0, 21)
        MakeExpectedCounterLocationEntry(0, 22)
        MakeExpectedCounterLocationEntry(0, 23)
        MakeExpectedCounterLocationEntry(0, 24)
        MakeExpectedCounterLocationEntry(0, 25)
        MakeExpectedCounterLocationEntry(0, 26)
        MakeExpectedCounterLocationEntry(0, 27)
        MakeExpectedCounterLocationEntry(0, 28)
        MakeExpectedCounterLocationEntry(0, 29)
        MakeExpectedCounterLocationEntry(0, 30)
        MakeExpectedCounterLocationEntry(0, 31)
        MakeExpectedCounterLocationEntry(0, 32)
        MakeExpectedCounterLocationEntry(0, 33)
        MakeExpectedCounterLocationEntry(0, 34)
        MakeExpectedCounterLocationEntry(0, 35)
        MakeExpectedCounterLocationEntry(0, 36)
        MakeExpectedCounterLocationEntry(0, 37)
        MakeExpectedCounterLocationEntry(0, 38)
        MakeExpectedCounterLocationEntry(0, 39)
        MakeExpectedCounterLocationEntry(0, 40)
        MakeExpectedCounterLocationEntry(0, 41)
        MakeExpectedCounterLocationEntry(0, 42)
        MakeExpectedCounterLocationEntry(0, 43)
        MakeExpectedCounterLocationEntry(0, 44)
        MakeExpectedCounterLocationEntry(0, 45)
        MakeExpectedCounterLocationEntry(0, 46)
        MakeExpectedCounterLocationEntry(0, 47)
        MakeExpectedCounterLocationEntry(0, 48)
        MakeExpectedCounterLocationEntry(0, 49)
        MakeExpectedCounterLocationEntry(0, 50)
        MakeExpectedCounterLocationEntry(0, 51)
        MakeExpectedCounterLocationEntry(0, 52)
        MakeExpectedCounterLocationEntry(0, 53)
        MakeExpectedCounterLocationEntry(0, 54)
        MakeExpectedCounterLocationEntry(0, 55)
        MakeExpectedCounterLocationEntry(0, 56)
        MakeExpectedCounterLocationEntry(0, 57)
        MakeExpectedCounterLocationEntry(0, 58)
        MakeExpectedCounterLocationEntry(0, 59)
        MakeExpectedCounterLocationEntry(0, 60)
        MakeExpectedCounterLocationEntry(0, 61)
        MakeExpectedCounterLocationEntry(0, 62)
        MakeExpectedCounterLocationEntry(0, 63)
    };

    std::map< unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > expectedResultLocations =
    {
        { CSVFetchInstsDX11Gfx8, expectedLocations0 }
    };

    VerifyCountersInPass(GPA_API_DIRECTX_11, gDevIdGfx8, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
}

/// GPA-159 Validation Test
/// Select the "HSBusyCycles", "HSTime (ns)", "PSBusyCycles", "PSTime (ns)" counters together

TEST(CounterDLLTests, Gpa159MultipleTimingCounters)
{
    std::vector<uint32_t> counters =
    {
        HSBusyCyclesDX12Gfx8,
        HSTimeDX12Gfx8,
        PSBusyCyclesDX12Gfx8,
        PSTimeDX12Gfx8,
    };

    // Pass: 0  Counters: 17
    std::vector<uint32_t> expectedCountersPass0 =
    {
        2893, 3090, 3287, 3484, 2899, 3096, 3293, 3490, 49743, 2925,
        3122, 3319, 3516, 2930, 3127, 3324, 3521
    };

    // Pass: 1  Counters: 1
    std::vector<uint32_t> expectedCountersPass1 =
    {
        51131
    };

    std::vector< std::vector<uint32_t> > expectedHwCountersPerPass =
    {
        expectedCountersPass0,
        expectedCountersPass1,
    };


    // Result locations (Pass, Offset)

    // Pass: 0  Counters: 9
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations0
    {
        MakeExpectedCounterLocationEntry(0, 0)
        MakeExpectedCounterLocationEntry(0, 4)
        MakeExpectedCounterLocationEntry(0, 1)
        MakeExpectedCounterLocationEntry(0, 5)
        MakeExpectedCounterLocationEntry(0, 2)
        MakeExpectedCounterLocationEntry(0, 6)
        MakeExpectedCounterLocationEntry(0, 3)
        MakeExpectedCounterLocationEntry(0, 7)
    };

    // Pass: 1  Counters: 10
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations1
    {
        MakeExpectedCounterLocationEntry(0, 0)
        MakeExpectedCounterLocationEntry(0, 4)
        MakeExpectedCounterLocationEntry(0, 1)
        MakeExpectedCounterLocationEntry(0, 5)
        MakeExpectedCounterLocationEntry(0, 2)
        MakeExpectedCounterLocationEntry(0, 6)
        MakeExpectedCounterLocationEntry(0, 3)
        MakeExpectedCounterLocationEntry(0, 7)
        MakeExpectedCounterLocationEntry(0, 8)
        MakeExpectedCounterLocationEntry(1, 0)
    };

    // Pass: 2  Counters: 18
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations2
    {
        MakeExpectedCounterLocationEntry(0, 9)
        MakeExpectedCounterLocationEntry(0, 13)
        MakeExpectedCounterLocationEntry(0, 10)
        MakeExpectedCounterLocationEntry(0, 14)
        MakeExpectedCounterLocationEntry(0, 11)
        MakeExpectedCounterLocationEntry(0, 15)
        MakeExpectedCounterLocationEntry(0, 12)
        MakeExpectedCounterLocationEntry(0, 16)
    };

    // Pass: 3  Counters: 19
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations3
    {
        MakeExpectedCounterLocationEntry(0, 9)
        MakeExpectedCounterLocationEntry(0, 13)
        MakeExpectedCounterLocationEntry(0, 10)
        MakeExpectedCounterLocationEntry(0, 14)
        MakeExpectedCounterLocationEntry(0, 11)
        MakeExpectedCounterLocationEntry(0, 15)
        MakeExpectedCounterLocationEntry(0, 12)
        MakeExpectedCounterLocationEntry(0, 16)
        MakeExpectedCounterLocationEntry(0, 8)
        MakeExpectedCounterLocationEntry(1, 0)
    };

    std::map< uint32_t, std::map<uint32_t, GPA_CounterResultLocation> > expectedResultLocations =
    {
        { HSBusyCyclesDX12Gfx8, expectedLocations0 },
        { HSTimeDX12Gfx8, expectedLocations1 },
        { PSBusyCyclesDX12Gfx8, expectedLocations2 },
        { PSTimeDX12Gfx8, expectedLocations3 }
    };

    VerifyCountersInPass(GPA_API_DIRECTX_12, gDevIdGfx8, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
}

/// GPA-85 Validation Test
/// Enable the following counters in this order:
/// VSVerticesIn
/// VSVALUInstCount
/// VSVALUBusy
/// VSSALUInstCount
/// VSSALUBusy
/// CSBusy
/// CSTime
/// DSBusy
/// DSTime
/// DepthStencilTestBusy
/// GPUBusy
/// GPUTime
/// GSBusy
/// GSTime
/// PSBusy
/// PSTime
/// PrimitiveAssemblyBusy
/// TessallatorBusy
/// TexUnitBusy
/// HSTime
/// HSBusy
/// VSBusy
/// VSTime

TEST(CounterDLLTests, Gpa85MultipleTimingCounters)
{
    std::vector<uint32_t> counters =
    {
        VSVerticesInDX12Gfx8,
        VSVALUInstCountDX12Gfx8,
        VSVALUBusyDX12Gfx8,
        VSSALUInstCountDX12Gfx8,
        VSSALUBusyDX12Gfx8,
        CSBusyDX12Gfx8,
        CSTimeDX12Gfx8,
        DSBusyDX12Gfx8,
        DSTimeDX12Gfx8,
        DepthStencilTestBusyDX12Gfx8,
        GPUBusyDX12Gfx8,
        GPUTimeDX12Gfx8,
        GSBusyDX12Gfx8,
        GSTimeDX12Gfx8,
        PSBusyDX12Gfx8,
        PSTimeDX12Gfx8,
        PrimitiveAssemblyBusyDX12Gfx8,
        TessellatorBusyDX12Gfx8,
        TexUnitBusyDX12Gfx8,
        HSTimeDX12Gfx8,
        HSBusyDX12Gfx8,
        VSBusyDX12Gfx8,
        VSTimeDX12Gfx8,
    };

    // Pass: 0  Counters: 118
    std::vector<uint32_t> expectedCountersPass0 =
    {
        13362, 13481, 13600, 13719, 13838, 13957, 14076, 14195, 14314, 14433,
        14552, 14671, 14790, 14909, 15028, 15147, 15266, 15385, 15504, 15623,
        15742, 15861, 15980, 16099, 16218, 16337, 16456, 16575, 16694, 16813,
        16932, 17051, 17170, 17289, 17408, 17527, 17646, 17765, 17884, 18003,
        18122, 18241, 18360, 18479, 18598, 18717, 18836, 18955, 19074, 19193,
        19312, 19431, 19550, 19669, 19788, 19907, 20026, 20145, 20264, 20383,
        20502, 20621, 20740, 20859, 49743, 2856, 3053, 3250, 3447, 2881,
        3078, 3275, 3472, 2903, 3100, 3297, 3494, 2925, 3122, 3319,
        3516, 2865, 3062, 3259, 3456, 2887, 3084, 3281, 3478, 39289,
        39546, 39803, 40060, 40317, 40574, 40831, 41088, 41345, 41602, 41859,
        42116, 42373, 42630, 42887, 43144, 87, 234, 381, 528, 68,
        215, 362, 509, 163, 310, 457, 604, 49741
    };

    // Pass: 1  Counters: 69
    std::vector<uint32_t> expectedCountersPass1 =
    {
        2856, 3053, 3250, 3447, 2881, 3078, 3275, 3472, 2925, 3122,
        3319, 3516, 2887, 3084, 3281, 3478, 2909, 3106, 3303, 3500,
        49743, 760, 913, 1066, 1219, 764, 917, 1070, 1223, 716,
        869, 1022, 1175, 728, 881, 1034, 1187, 4865, 5164, 5463,
        5762, 4843, 5142, 5441, 5740, 4853, 5152, 5451, 5750, 4869,
        5168, 5467, 5766, 2930, 3127, 3324, 3521, 4920, 5219, 5518,
        5817, 4925, 5224, 5523, 5822, 191, 338, 485, 632
    };

    // Pass: 2  Counters: 57
    std::vector<uint32_t> expectedCountersPass2 =
    {
        2913, 3110, 3307, 3504, 2917, 3114, 3311, 3508, 2919, 3116,
        3313, 3510, 2923, 3120, 3317, 3514, 49743, 9649, 9948, 10247,
        10546, 9627, 9926, 10225, 10524, 9637, 9936, 10235, 10534, 9653,
        9952, 10251, 10550, 2872, 3069, 3266, 3463, 2875, 3072, 3269,
        3466, 9704, 10003, 10302, 10601, 9709, 10008, 10307, 10606, 717,
        870, 1023, 1176, 729, 882, 1035, 1188
    };

    // Pass: 3  Counters: 29
    std::vector<uint32_t> expectedCountersPass3 =
    {
        2893, 3090, 3287, 3484, 2899, 3096, 3293, 3490, 49743, 7257,
        7556, 7855, 8154, 7235, 7534, 7833, 8132, 7261, 7560, 7859,
        8158, 7312, 7611, 7910, 8209, 7317, 7616, 7915, 8214
    };

    // Pass: 4  Counters: 1
    std::vector<uint32_t> expectedCountersPass4 =
    {
        51131
    };

    std::vector< std::vector<uint32_t> > expectedHwCountersPerPass =
    {
        expectedCountersPass0,
        expectedCountersPass1,
        expectedCountersPass2,
        expectedCountersPass3,
        expectedCountersPass4,
    };


    // Result locations (Pass, Offset)

    // Pass: 0  Counters: 23
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations0
    {
        MakeExpectedCounterLocationEntry(0, 109)
        MakeExpectedCounterLocationEntry(0, 105)
        MakeExpectedCounterLocationEntry(0, 113)
        MakeExpectedCounterLocationEntry(0, 110)
        MakeExpectedCounterLocationEntry(0, 106)
        MakeExpectedCounterLocationEntry(0, 114)
        MakeExpectedCounterLocationEntry(0, 111)
        MakeExpectedCounterLocationEntry(0, 107)
        MakeExpectedCounterLocationEntry(0, 115)
        MakeExpectedCounterLocationEntry(0, 112)
        MakeExpectedCounterLocationEntry(0, 108)
        MakeExpectedCounterLocationEntry(0, 116)
    };

    // Pass: 1  Counters: 24
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations1
    {
        MakeExpectedCounterLocationEntry(1, 41)
        MakeExpectedCounterLocationEntry(1, 45)
        MakeExpectedCounterLocationEntry(1, 37)
        MakeExpectedCounterLocationEntry(1, 42)
        MakeExpectedCounterLocationEntry(1, 46)
        MakeExpectedCounterLocationEntry(1, 38)
        MakeExpectedCounterLocationEntry(1, 43)
        MakeExpectedCounterLocationEntry(1, 47)
        MakeExpectedCounterLocationEntry(1, 39)
        MakeExpectedCounterLocationEntry(1, 44)
        MakeExpectedCounterLocationEntry(1, 48)
        MakeExpectedCounterLocationEntry(1, 40)
        MakeExpectedCounterLocationEntry(3, 13)
        MakeExpectedCounterLocationEntry(3, 9)
        MakeExpectedCounterLocationEntry(3, 14)
        MakeExpectedCounterLocationEntry(3, 10)
        MakeExpectedCounterLocationEntry(3, 15)
        MakeExpectedCounterLocationEntry(3, 11)
        MakeExpectedCounterLocationEntry(3, 16)
        MakeExpectedCounterLocationEntry(3, 12)
        MakeExpectedCounterLocationEntry(2, 21)
        MakeExpectedCounterLocationEntry(2, 25)
        MakeExpectedCounterLocationEntry(2, 17)
        MakeExpectedCounterLocationEntry(2, 22)
        MakeExpectedCounterLocationEntry(2, 26)
        MakeExpectedCounterLocationEntry(2, 18)
        MakeExpectedCounterLocationEntry(2, 23)
        MakeExpectedCounterLocationEntry(2, 27)
        MakeExpectedCounterLocationEntry(2, 19)
        MakeExpectedCounterLocationEntry(2, 24)
        MakeExpectedCounterLocationEntry(2, 28)
        MakeExpectedCounterLocationEntry(2, 20)
    };

    // Pass: 2  Counters: 26
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations2
    {
        MakeExpectedCounterLocationEntry(1, 45)
        MakeExpectedCounterLocationEntry(1, 57)
        MakeExpectedCounterLocationEntry(1, 46)
        MakeExpectedCounterLocationEntry(1, 58)
        MakeExpectedCounterLocationEntry(1, 47)
        MakeExpectedCounterLocationEntry(1, 59)
        MakeExpectedCounterLocationEntry(1, 48)
        MakeExpectedCounterLocationEntry(1, 60)
        MakeExpectedCounterLocationEntry(3, 21)
        MakeExpectedCounterLocationEntry(3, 22)
        MakeExpectedCounterLocationEntry(3, 23)
        MakeExpectedCounterLocationEntry(3, 24)
        MakeExpectedCounterLocationEntry(2, 25)
        MakeExpectedCounterLocationEntry(2, 41)
        MakeExpectedCounterLocationEntry(2, 26)
        MakeExpectedCounterLocationEntry(2, 42)
        MakeExpectedCounterLocationEntry(2, 27)
        MakeExpectedCounterLocationEntry(2, 43)
        MakeExpectedCounterLocationEntry(2, 28)
        MakeExpectedCounterLocationEntry(2, 44)
        MakeExpectedCounterLocationEntry(3, 8)
    };

    // Pass: 3  Counters: 25
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations3
    {
        MakeExpectedCounterLocationEntry(1, 41)
        MakeExpectedCounterLocationEntry(1, 45)
        MakeExpectedCounterLocationEntry(1, 49)
        MakeExpectedCounterLocationEntry(1, 42)
        MakeExpectedCounterLocationEntry(1, 46)
        MakeExpectedCounterLocationEntry(1, 50)
        MakeExpectedCounterLocationEntry(1, 43)
        MakeExpectedCounterLocationEntry(1, 47)
        MakeExpectedCounterLocationEntry(1, 51)
        MakeExpectedCounterLocationEntry(1, 44)
        MakeExpectedCounterLocationEntry(1, 48)
        MakeExpectedCounterLocationEntry(1, 52)
        MakeExpectedCounterLocationEntry(3, 13)
        MakeExpectedCounterLocationEntry(3, 17)
        MakeExpectedCounterLocationEntry(3, 14)
        MakeExpectedCounterLocationEntry(3, 18)
        MakeExpectedCounterLocationEntry(3, 15)
        MakeExpectedCounterLocationEntry(3, 19)
        MakeExpectedCounterLocationEntry(3, 16)
        MakeExpectedCounterLocationEntry(3, 20)
        MakeExpectedCounterLocationEntry(2, 21)
        MakeExpectedCounterLocationEntry(2, 25)
        MakeExpectedCounterLocationEntry(2, 29)
        MakeExpectedCounterLocationEntry(2, 22)
        MakeExpectedCounterLocationEntry(2, 26)
        MakeExpectedCounterLocationEntry(2, 30)
        MakeExpectedCounterLocationEntry(2, 23)
        MakeExpectedCounterLocationEntry(2, 27)
        MakeExpectedCounterLocationEntry(2, 31)
        MakeExpectedCounterLocationEntry(2, 24)
        MakeExpectedCounterLocationEntry(2, 28)
        MakeExpectedCounterLocationEntry(2, 32)
    };

    // Pass: 4  Counters: 28
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations4
    {
        MakeExpectedCounterLocationEntry(1, 45)
        MakeExpectedCounterLocationEntry(1, 61)
        MakeExpectedCounterLocationEntry(1, 46)
        MakeExpectedCounterLocationEntry(1, 62)
        MakeExpectedCounterLocationEntry(1, 47)
        MakeExpectedCounterLocationEntry(1, 63)
        MakeExpectedCounterLocationEntry(1, 48)
        MakeExpectedCounterLocationEntry(1, 64)
        MakeExpectedCounterLocationEntry(3, 25)
        MakeExpectedCounterLocationEntry(3, 26)
        MakeExpectedCounterLocationEntry(3, 27)
        MakeExpectedCounterLocationEntry(3, 28)
        MakeExpectedCounterLocationEntry(2, 25)
        MakeExpectedCounterLocationEntry(2, 45)
        MakeExpectedCounterLocationEntry(2, 26)
        MakeExpectedCounterLocationEntry(2, 46)
        MakeExpectedCounterLocationEntry(2, 27)
        MakeExpectedCounterLocationEntry(2, 47)
        MakeExpectedCounterLocationEntry(2, 28)
        MakeExpectedCounterLocationEntry(2, 48)
        MakeExpectedCounterLocationEntry(3, 8)
    };

    // Pass: 5  Counters: 20
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations5
    {
        MakeExpectedCounterLocationEntry(2, 0)
        MakeExpectedCounterLocationEntry(2, 4)
        MakeExpectedCounterLocationEntry(2, 8)
        MakeExpectedCounterLocationEntry(2, 12)
        MakeExpectedCounterLocationEntry(2, 1)
        MakeExpectedCounterLocationEntry(2, 5)
        MakeExpectedCounterLocationEntry(2, 9)
        MakeExpectedCounterLocationEntry(2, 13)
        MakeExpectedCounterLocationEntry(2, 2)
        MakeExpectedCounterLocationEntry(2, 6)
        MakeExpectedCounterLocationEntry(2, 10)
        MakeExpectedCounterLocationEntry(2, 14)
        MakeExpectedCounterLocationEntry(2, 3)
        MakeExpectedCounterLocationEntry(2, 7)
        MakeExpectedCounterLocationEntry(2, 11)
        MakeExpectedCounterLocationEntry(2, 15)
        MakeExpectedCounterLocationEntry(2, 16)
    };

    // Pass: 6  Counters: 22
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations6
    {
        MakeExpectedCounterLocationEntry(2, 0)
        MakeExpectedCounterLocationEntry(2, 4)
        MakeExpectedCounterLocationEntry(2, 8)
        MakeExpectedCounterLocationEntry(2, 12)
        MakeExpectedCounterLocationEntry(2, 1)
        MakeExpectedCounterLocationEntry(2, 5)
        MakeExpectedCounterLocationEntry(2, 9)
        MakeExpectedCounterLocationEntry(2, 13)
        MakeExpectedCounterLocationEntry(2, 2)
        MakeExpectedCounterLocationEntry(2, 6)
        MakeExpectedCounterLocationEntry(2, 10)
        MakeExpectedCounterLocationEntry(2, 14)
        MakeExpectedCounterLocationEntry(2, 3)
        MakeExpectedCounterLocationEntry(2, 7)
        MakeExpectedCounterLocationEntry(2, 11)
        MakeExpectedCounterLocationEntry(2, 15)
        MakeExpectedCounterLocationEntry(2, 16)
        MakeExpectedCounterLocationEntry(4, 0)
    };

    // Pass: 7  Counters: 11
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations7
    {
        MakeExpectedCounterLocationEntry(1, 0)
        MakeExpectedCounterLocationEntry(1, 4)
        MakeExpectedCounterLocationEntry(1, 12)
        MakeExpectedCounterLocationEntry(1, 16)
        MakeExpectedCounterLocationEntry(1, 8)
        MakeExpectedCounterLocationEntry(1, 1)
        MakeExpectedCounterLocationEntry(1, 5)
        MakeExpectedCounterLocationEntry(1, 13)
        MakeExpectedCounterLocationEntry(1, 17)
        MakeExpectedCounterLocationEntry(1, 9)
        MakeExpectedCounterLocationEntry(1, 2)
        MakeExpectedCounterLocationEntry(1, 6)
        MakeExpectedCounterLocationEntry(1, 14)
        MakeExpectedCounterLocationEntry(1, 18)
        MakeExpectedCounterLocationEntry(1, 10)
        MakeExpectedCounterLocationEntry(1, 3)
        MakeExpectedCounterLocationEntry(1, 7)
        MakeExpectedCounterLocationEntry(1, 15)
        MakeExpectedCounterLocationEntry(1, 19)
        MakeExpectedCounterLocationEntry(1, 11)
        MakeExpectedCounterLocationEntry(1, 20)
    };

    // Pass: 8  Counters: 13
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations8
    {
        MakeExpectedCounterLocationEntry(1, 0)
        MakeExpectedCounterLocationEntry(1, 4)
        MakeExpectedCounterLocationEntry(1, 12)
        MakeExpectedCounterLocationEntry(1, 16)
        MakeExpectedCounterLocationEntry(1, 8)
        MakeExpectedCounterLocationEntry(1, 1)
        MakeExpectedCounterLocationEntry(1, 5)
        MakeExpectedCounterLocationEntry(1, 13)
        MakeExpectedCounterLocationEntry(1, 17)
        MakeExpectedCounterLocationEntry(1, 9)
        MakeExpectedCounterLocationEntry(1, 2)
        MakeExpectedCounterLocationEntry(1, 6)
        MakeExpectedCounterLocationEntry(1, 14)
        MakeExpectedCounterLocationEntry(1, 18)
        MakeExpectedCounterLocationEntry(1, 10)
        MakeExpectedCounterLocationEntry(1, 3)
        MakeExpectedCounterLocationEntry(1, 7)
        MakeExpectedCounterLocationEntry(1, 15)
        MakeExpectedCounterLocationEntry(1, 19)
        MakeExpectedCounterLocationEntry(1, 11)
        MakeExpectedCounterLocationEntry(1, 20)
        MakeExpectedCounterLocationEntry(4, 0)
    };

    // Pass: 9  Counters: 103
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations9
    {
        MakeExpectedCounterLocationEntry(0, 89)
        MakeExpectedCounterLocationEntry(0, 90)
        MakeExpectedCounterLocationEntry(0, 91)
        MakeExpectedCounterLocationEntry(0, 92)
        MakeExpectedCounterLocationEntry(0, 93)
        MakeExpectedCounterLocationEntry(0, 94)
        MakeExpectedCounterLocationEntry(0, 95)
        MakeExpectedCounterLocationEntry(0, 96)
        MakeExpectedCounterLocationEntry(0, 97)
        MakeExpectedCounterLocationEntry(0, 98)
        MakeExpectedCounterLocationEntry(0, 99)
        MakeExpectedCounterLocationEntry(0, 100)
        MakeExpectedCounterLocationEntry(0, 101)
        MakeExpectedCounterLocationEntry(0, 102)
        MakeExpectedCounterLocationEntry(0, 103)
        MakeExpectedCounterLocationEntry(0, 104)
        MakeExpectedCounterLocationEntry(0, 64)
    };

    // Pass: 10  Counters: 1
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations10
    {
        MakeExpectedCounterLocationEntry(0, 117)
        MakeExpectedCounterLocationEntry(0, 64)
    };

    // Pass: 11  Counters: 0
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations11
    {
        MakeExpectedCounterLocationEntry(4, 0)
    };

    // Pass: 12  Counters: 14
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations12
    {
        MakeExpectedCounterLocationEntry(2, 33)
        MakeExpectedCounterLocationEntry(2, 37)
        MakeExpectedCounterLocationEntry(2, 34)
        MakeExpectedCounterLocationEntry(2, 38)
        MakeExpectedCounterLocationEntry(2, 35)
        MakeExpectedCounterLocationEntry(2, 39)
        MakeExpectedCounterLocationEntry(2, 36)
        MakeExpectedCounterLocationEntry(2, 40)
        MakeExpectedCounterLocationEntry(2, 16)
    };

    // Pass: 13  Counters: 16
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations13
    {
        MakeExpectedCounterLocationEntry(2, 33)
        MakeExpectedCounterLocationEntry(2, 37)
        MakeExpectedCounterLocationEntry(2, 34)
        MakeExpectedCounterLocationEntry(2, 38)
        MakeExpectedCounterLocationEntry(2, 35)
        MakeExpectedCounterLocationEntry(2, 39)
        MakeExpectedCounterLocationEntry(2, 36)
        MakeExpectedCounterLocationEntry(2, 40)
        MakeExpectedCounterLocationEntry(2, 16)
        MakeExpectedCounterLocationEntry(4, 0)
    };

    // Pass: 14  Counters: 17
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations14
    {
        MakeExpectedCounterLocationEntry(1, 8)
        MakeExpectedCounterLocationEntry(1, 53)
        MakeExpectedCounterLocationEntry(1, 9)
        MakeExpectedCounterLocationEntry(1, 54)
        MakeExpectedCounterLocationEntry(1, 10)
        MakeExpectedCounterLocationEntry(1, 55)
        MakeExpectedCounterLocationEntry(1, 11)
        MakeExpectedCounterLocationEntry(1, 56)
        MakeExpectedCounterLocationEntry(1, 20)
    };

    // Pass: 15  Counters: 19
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations15
    {
        MakeExpectedCounterLocationEntry(1, 8)
        MakeExpectedCounterLocationEntry(1, 53)
        MakeExpectedCounterLocationEntry(1, 9)
        MakeExpectedCounterLocationEntry(1, 54)
        MakeExpectedCounterLocationEntry(1, 10)
        MakeExpectedCounterLocationEntry(1, 55)
        MakeExpectedCounterLocationEntry(1, 11)
        MakeExpectedCounterLocationEntry(1, 56)
        MakeExpectedCounterLocationEntry(1, 20)
        MakeExpectedCounterLocationEntry(4, 0)
    };

    // Pass: 16  Counters: 52
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations16
    {
        MakeExpectedCounterLocationEntry(1, 29)
        MakeExpectedCounterLocationEntry(2, 49)
        MakeExpectedCounterLocationEntry(1, 33)
        MakeExpectedCounterLocationEntry(2, 53)
        MakeExpectedCounterLocationEntry(1, 21)
        MakeExpectedCounterLocationEntry(1, 25)
        MakeExpectedCounterLocationEntry(1, 30)
        MakeExpectedCounterLocationEntry(2, 50)
        MakeExpectedCounterLocationEntry(1, 34)
        MakeExpectedCounterLocationEntry(2, 54)
        MakeExpectedCounterLocationEntry(1, 22)
        MakeExpectedCounterLocationEntry(1, 26)
        MakeExpectedCounterLocationEntry(1, 31)
        MakeExpectedCounterLocationEntry(2, 51)
        MakeExpectedCounterLocationEntry(1, 35)
        MakeExpectedCounterLocationEntry(2, 55)
        MakeExpectedCounterLocationEntry(1, 23)
        MakeExpectedCounterLocationEntry(1, 27)
        MakeExpectedCounterLocationEntry(1, 32)
        MakeExpectedCounterLocationEntry(2, 52)
        MakeExpectedCounterLocationEntry(1, 36)
        MakeExpectedCounterLocationEntry(2, 56)
        MakeExpectedCounterLocationEntry(1, 24)
        MakeExpectedCounterLocationEntry(1, 28)
        MakeExpectedCounterLocationEntry(1, 20)
    };

    // Pass: 17  Counters: 3
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations17
    {
        MakeExpectedCounterLocationEntry(1, 65)
        MakeExpectedCounterLocationEntry(1, 66)
        MakeExpectedCounterLocationEntry(1, 67)
        MakeExpectedCounterLocationEntry(1, 68)
        MakeExpectedCounterLocationEntry(1, 20)
    };

    // Pass: 18  Counters: 94
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations18
    {
        MakeExpectedCounterLocationEntry(0, 0)
        MakeExpectedCounterLocationEntry(0, 1)
        MakeExpectedCounterLocationEntry(0, 2)
        MakeExpectedCounterLocationEntry(0, 3)
        MakeExpectedCounterLocationEntry(0, 4)
        MakeExpectedCounterLocationEntry(0, 5)
        MakeExpectedCounterLocationEntry(0, 6)
        MakeExpectedCounterLocationEntry(0, 7)
        MakeExpectedCounterLocationEntry(0, 8)
        MakeExpectedCounterLocationEntry(0, 9)
        MakeExpectedCounterLocationEntry(0, 10)
        MakeExpectedCounterLocationEntry(0, 11)
        MakeExpectedCounterLocationEntry(0, 12)
        MakeExpectedCounterLocationEntry(0, 13)
        MakeExpectedCounterLocationEntry(0, 14)
        MakeExpectedCounterLocationEntry(0, 15)
        MakeExpectedCounterLocationEntry(0, 16)
        MakeExpectedCounterLocationEntry(0, 17)
        MakeExpectedCounterLocationEntry(0, 18)
        MakeExpectedCounterLocationEntry(0, 19)
        MakeExpectedCounterLocationEntry(0, 20)
        MakeExpectedCounterLocationEntry(0, 21)
        MakeExpectedCounterLocationEntry(0, 22)
        MakeExpectedCounterLocationEntry(0, 23)
        MakeExpectedCounterLocationEntry(0, 24)
        MakeExpectedCounterLocationEntry(0, 25)
        MakeExpectedCounterLocationEntry(0, 26)
        MakeExpectedCounterLocationEntry(0, 27)
        MakeExpectedCounterLocationEntry(0, 28)
        MakeExpectedCounterLocationEntry(0, 29)
        MakeExpectedCounterLocationEntry(0, 30)
        MakeExpectedCounterLocationEntry(0, 31)
        MakeExpectedCounterLocationEntry(0, 32)
        MakeExpectedCounterLocationEntry(0, 33)
        MakeExpectedCounterLocationEntry(0, 34)
        MakeExpectedCounterLocationEntry(0, 35)
        MakeExpectedCounterLocationEntry(0, 36)
        MakeExpectedCounterLocationEntry(0, 37)
        MakeExpectedCounterLocationEntry(0, 38)
        MakeExpectedCounterLocationEntry(0, 39)
        MakeExpectedCounterLocationEntry(0, 40)
        MakeExpectedCounterLocationEntry(0, 41)
        MakeExpectedCounterLocationEntry(0, 42)
        MakeExpectedCounterLocationEntry(0, 43)
        MakeExpectedCounterLocationEntry(0, 44)
        MakeExpectedCounterLocationEntry(0, 45)
        MakeExpectedCounterLocationEntry(0, 46)
        MakeExpectedCounterLocationEntry(0, 47)
        MakeExpectedCounterLocationEntry(0, 48)
        MakeExpectedCounterLocationEntry(0, 49)
        MakeExpectedCounterLocationEntry(0, 50)
        MakeExpectedCounterLocationEntry(0, 51)
        MakeExpectedCounterLocationEntry(0, 52)
        MakeExpectedCounterLocationEntry(0, 53)
        MakeExpectedCounterLocationEntry(0, 54)
        MakeExpectedCounterLocationEntry(0, 55)
        MakeExpectedCounterLocationEntry(0, 56)
        MakeExpectedCounterLocationEntry(0, 57)
        MakeExpectedCounterLocationEntry(0, 58)
        MakeExpectedCounterLocationEntry(0, 59)
        MakeExpectedCounterLocationEntry(0, 60)
        MakeExpectedCounterLocationEntry(0, 61)
        MakeExpectedCounterLocationEntry(0, 62)
        MakeExpectedCounterLocationEntry(0, 63)
        MakeExpectedCounterLocationEntry(0, 64)
    };

    // Pass: 19  Counters: 10
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations19
    {
        MakeExpectedCounterLocationEntry(3, 0)
        MakeExpectedCounterLocationEntry(3, 4)
        MakeExpectedCounterLocationEntry(3, 1)
        MakeExpectedCounterLocationEntry(3, 5)
        MakeExpectedCounterLocationEntry(3, 2)
        MakeExpectedCounterLocationEntry(3, 6)
        MakeExpectedCounterLocationEntry(3, 3)
        MakeExpectedCounterLocationEntry(3, 7)
        MakeExpectedCounterLocationEntry(3, 8)
        MakeExpectedCounterLocationEntry(4, 0)
    };

    // Pass: 20  Counters: 8
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations20
    {
        MakeExpectedCounterLocationEntry(3, 0)
        MakeExpectedCounterLocationEntry(3, 4)
        MakeExpectedCounterLocationEntry(3, 1)
        MakeExpectedCounterLocationEntry(3, 5)
        MakeExpectedCounterLocationEntry(3, 2)
        MakeExpectedCounterLocationEntry(3, 6)
        MakeExpectedCounterLocationEntry(3, 3)
        MakeExpectedCounterLocationEntry(3, 7)
        MakeExpectedCounterLocationEntry(3, 8)
    };

    // Pass: 21  Counters: 5
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations21
    {
        MakeExpectedCounterLocationEntry(0, 65)
        MakeExpectedCounterLocationEntry(0, 81)
        MakeExpectedCounterLocationEntry(0, 69)
        MakeExpectedCounterLocationEntry(0, 85)
        MakeExpectedCounterLocationEntry(0, 73)
        MakeExpectedCounterLocationEntry(1, 16)
        MakeExpectedCounterLocationEntry(0, 77)
        MakeExpectedCounterLocationEntry(0, 66)
        MakeExpectedCounterLocationEntry(0, 82)
        MakeExpectedCounterLocationEntry(0, 70)
        MakeExpectedCounterLocationEntry(0, 86)
        MakeExpectedCounterLocationEntry(0, 74)
        MakeExpectedCounterLocationEntry(1, 17)
        MakeExpectedCounterLocationEntry(0, 78)
        MakeExpectedCounterLocationEntry(0, 67)
        MakeExpectedCounterLocationEntry(0, 83)
        MakeExpectedCounterLocationEntry(0, 71)
        MakeExpectedCounterLocationEntry(0, 87)
        MakeExpectedCounterLocationEntry(0, 75)
        MakeExpectedCounterLocationEntry(1, 18)
        MakeExpectedCounterLocationEntry(0, 79)
        MakeExpectedCounterLocationEntry(0, 68)
        MakeExpectedCounterLocationEntry(0, 84)
        MakeExpectedCounterLocationEntry(0, 72)
        MakeExpectedCounterLocationEntry(0, 88)
        MakeExpectedCounterLocationEntry(0, 76)
        MakeExpectedCounterLocationEntry(1, 19)
        MakeExpectedCounterLocationEntry(0, 80)
        MakeExpectedCounterLocationEntry(0, 64)
    };

    // Pass: 22  Counters: 7
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations22
    {
        MakeExpectedCounterLocationEntry(0, 65)
        MakeExpectedCounterLocationEntry(0, 81)
        MakeExpectedCounterLocationEntry(0, 69)
        MakeExpectedCounterLocationEntry(0, 85)
        MakeExpectedCounterLocationEntry(0, 73)
        MakeExpectedCounterLocationEntry(1, 16)
        MakeExpectedCounterLocationEntry(0, 77)
        MakeExpectedCounterLocationEntry(0, 66)
        MakeExpectedCounterLocationEntry(0, 82)
        MakeExpectedCounterLocationEntry(0, 70)
        MakeExpectedCounterLocationEntry(0, 86)
        MakeExpectedCounterLocationEntry(0, 74)
        MakeExpectedCounterLocationEntry(1, 17)
        MakeExpectedCounterLocationEntry(0, 78)
        MakeExpectedCounterLocationEntry(0, 67)
        MakeExpectedCounterLocationEntry(0, 83)
        MakeExpectedCounterLocationEntry(0, 71)
        MakeExpectedCounterLocationEntry(0, 87)
        MakeExpectedCounterLocationEntry(0, 75)
        MakeExpectedCounterLocationEntry(1, 18)
        MakeExpectedCounterLocationEntry(0, 79)
        MakeExpectedCounterLocationEntry(0, 68)
        MakeExpectedCounterLocationEntry(0, 84)
        MakeExpectedCounterLocationEntry(0, 72)
        MakeExpectedCounterLocationEntry(0, 88)
        MakeExpectedCounterLocationEntry(0, 76)
        MakeExpectedCounterLocationEntry(1, 19)
        MakeExpectedCounterLocationEntry(0, 80)
        MakeExpectedCounterLocationEntry(0, 64)
        MakeExpectedCounterLocationEntry(4, 0)
    };

    std::map< uint32_t, std::map<uint32_t, GPA_CounterResultLocation> > expectedResultLocations =
    {
        { VSVerticesInDX12Gfx8, expectedLocations0 },
        { VSVALUInstCountDX12Gfx8, expectedLocations1 },
        { VSVALUBusyDX12Gfx8, expectedLocations2 },
        { VSSALUInstCountDX12Gfx8, expectedLocations3 },
        { VSSALUBusyDX12Gfx8, expectedLocations4 },
        { CSBusyDX12Gfx8, expectedLocations5 },
        { CSTimeDX12Gfx8, expectedLocations6 },
        { DSBusyDX12Gfx8, expectedLocations7 },
        { DSTimeDX12Gfx8, expectedLocations8 },
        { DepthStencilTestBusyDX12Gfx8, expectedLocations9 },
        { GPUBusyDX12Gfx8, expectedLocations10 },
        { GPUTimeDX12Gfx8, expectedLocations11 },
        { GSBusyDX12Gfx8, expectedLocations12 },
        { GSTimeDX12Gfx8, expectedLocations13 },
        { PSBusyDX12Gfx8, expectedLocations14 },
        { PSTimeDX12Gfx8, expectedLocations15 },
        { PrimitiveAssemblyBusyDX12Gfx8, expectedLocations16 },
        { TessellatorBusyDX12Gfx8, expectedLocations17 },
        { TexUnitBusyDX12Gfx8, expectedLocations18 },
        { HSTimeDX12Gfx8, expectedLocations19 },
        { HSBusyDX12Gfx8, expectedLocations20 },
        { VSBusyDX12Gfx8, expectedLocations21 },
        { VSTimeDX12Gfx8, expectedLocations22 },
    };

    VerifyCountersInPass(GPA_API_DIRECTX_12, gDevIdGfx8, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
}

// GPA-83: Consolidated counter scheduler no longer schedules multi-pass public
// counters in consecutive passes  This consolidates 4 passes into 3 passes
// VSVerticeIn, GPUTime, and VSBusy should be scheduled in 3 passes
TEST(CounterDLLTests, Gpa83ThreePassTest)
{
    std::vector<uint32_t> counters =
    {
        VSVerticesInDX12Gfx8,
        GPUTimeDX12Gfx8,
        VSBusyDX12Gfx8
    };

    // Pass: 0  Counters: 37
    std::vector<uint32_t> expectedCountersPass0 =
    {
        2856, 3053, 3250, 3447, 2881, 3078, 3275, 3472, 2903, 3100,
        3297, 3494, 2925, 3122, 3319, 3516, 2865, 3062, 3259, 3456,
        2887, 3084, 3281, 3478, 49743, 87, 234, 381, 528, 68,
        215, 362, 509, 163, 310, 457, 604
    };

    // Pass: 1  Counters: 4
    std::vector<uint32_t> expectedCountersPass1 =
    {
        2909, 3106, 3303, 3500
    };

    // Pass: 2  Counters: 1
    std::vector<uint32_t> expectedCountersPass2 =
    {
        51131
    };

    std::vector< std::vector<uint32_t> > expectedHwCountersPerPass =
    {
        expectedCountersPass0,
        expectedCountersPass1,
        expectedCountersPass2,
    };


    // Result locations (Pass, Offset)

    // Pass: 0  Counters: 23
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations0
    {
        MakeExpectedCounterLocationEntry(0, 29)
        MakeExpectedCounterLocationEntry(0, 25)
        MakeExpectedCounterLocationEntry(0, 33)
        MakeExpectedCounterLocationEntry(0, 30)
        MakeExpectedCounterLocationEntry(0, 26)
        MakeExpectedCounterLocationEntry(0, 34)
        MakeExpectedCounterLocationEntry(0, 31)
        MakeExpectedCounterLocationEntry(0, 27)
        MakeExpectedCounterLocationEntry(0, 35)
        MakeExpectedCounterLocationEntry(0, 32)
        MakeExpectedCounterLocationEntry(0, 28)
        MakeExpectedCounterLocationEntry(0, 36)
    };

    // Pass: 1  Counters: 0
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations1
    {
        MakeExpectedCounterLocationEntry(2, 0)
    };

    // Pass: 2  Counters: 5
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations2
    {
        MakeExpectedCounterLocationEntry(0, 0)
        MakeExpectedCounterLocationEntry(0, 16)
        MakeExpectedCounterLocationEntry(0, 4)
        MakeExpectedCounterLocationEntry(0, 20)
        MakeExpectedCounterLocationEntry(0, 8)
        MakeExpectedCounterLocationEntry(1, 0)
        MakeExpectedCounterLocationEntry(0, 12)
        MakeExpectedCounterLocationEntry(0, 1)
        MakeExpectedCounterLocationEntry(0, 17)
        MakeExpectedCounterLocationEntry(0, 5)
        MakeExpectedCounterLocationEntry(0, 21)
        MakeExpectedCounterLocationEntry(0, 9)
        MakeExpectedCounterLocationEntry(1, 1)
        MakeExpectedCounterLocationEntry(0, 13)
        MakeExpectedCounterLocationEntry(0, 2)
        MakeExpectedCounterLocationEntry(0, 18)
        MakeExpectedCounterLocationEntry(0, 6)
        MakeExpectedCounterLocationEntry(0, 22)
        MakeExpectedCounterLocationEntry(0, 10)
        MakeExpectedCounterLocationEntry(1, 2)
        MakeExpectedCounterLocationEntry(0, 14)
        MakeExpectedCounterLocationEntry(0, 3)
        MakeExpectedCounterLocationEntry(0, 19)
        MakeExpectedCounterLocationEntry(0, 7)
        MakeExpectedCounterLocationEntry(0, 23)
        MakeExpectedCounterLocationEntry(0, 11)
        MakeExpectedCounterLocationEntry(1, 3)
        MakeExpectedCounterLocationEntry(0, 15)
        MakeExpectedCounterLocationEntry(0, 24)
    };

    std::map< unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > expectedResultLocations =
    {
        { VSVerticesInDX12Gfx8, expectedLocations0 },
        { GPUTimeDX12Gfx8, expectedLocations1 },
        { VSBusyDX12Gfx8, expectedLocations2 }
    };

    VerifyCountersInPass(GPA_API_DIRECTX_12, gDevIdGfx8, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
}

// SWDEV-140743: DX11 Vega L1 Cache Counters (TCP Block Instance) Always Zero
// Implemented as a test for convenience as we need to explain to the driver team the scheduling of the counters
TEST(CounterDLLTests, SwDev140743)
{
    std::vector<uint32_t> counters =
    {
        L1CacheHitCountDX11Gfx9
    };

    // Pass: 0  Counters: 256
    std::vector<uint32_t> expectedCountersPass0 =
    {
        40871, 40956, 41041, 41126, 41211, 41296, 41381, 41466, 41551, 41636,
        41721, 41806, 41891, 41976, 42061, 42146, 42231, 42316, 42401, 42486,
        42571, 42656, 42741, 42826, 42911, 42996, 43081, 43166, 43251, 43336,
        43421, 43506, 43591, 43676, 43761, 43846, 43931, 44016, 44101, 44186,
        44271, 44356, 44441, 44526, 44611, 44696, 44781, 44866, 44951, 45036,
        45121, 45206, 45291, 45376, 45461, 45546, 45631, 45716, 45801, 45886,
        45971, 46056, 46141, 46226, 40880, 40965, 41050, 41135, 41220, 41305,
        41390, 41475, 41560, 41645, 41730, 41815, 41900, 41985, 42070, 42155,
        42240, 42325, 42410, 42495, 42580, 42665, 42750, 42835, 42920, 43005,
        43090, 43175, 43260, 43345, 43430, 43515, 43600, 43685, 43770, 43855,
        43940, 44025, 44110, 44195, 44280, 44365, 44450, 44535, 44620, 44705,
        44790, 44875, 44960, 45045, 45130, 45215, 45300, 45385, 45470, 45555,
        45640, 45725, 45810, 45895, 45980, 46065, 46150, 46235, 40881, 40966,
        41051, 41136, 41221, 41306, 41391, 41476, 41561, 41646, 41731, 41816,
        41901, 41986, 42071, 42156, 42241, 42326, 42411, 42496, 42581, 42666,
        42751, 42836, 42921, 43006, 43091, 43176, 43261, 43346, 43431, 43516,
        43601, 43686, 43771, 43856, 43941, 44026, 44111, 44196, 44281, 44366,
        44451, 44536, 44621, 44706, 44791, 44876, 44961, 45046, 45131, 45216,
        45301, 45386, 45471, 45556, 45641, 45726, 45811, 45896, 45981, 46066,
        46151, 46236, 40882, 40967, 41052, 41137, 41222, 41307, 41392, 41477,
        41562, 41647, 41732, 41817, 41902, 41987, 42072, 42157, 42242, 42327,
        42412, 42497, 42582, 42667, 42752, 42837, 42922, 43007, 43092, 43177,
        43262, 43347, 43432, 43517, 43602, 43687, 43772, 43857, 43942, 44027,
        44112, 44197, 44282, 44367, 44452, 44537, 44622, 44707, 44792, 44877,
        44962, 45047, 45132, 45217, 45302, 45387, 45472, 45557, 45642, 45727,
        45812, 45897, 45982, 46067, 46152, 46237
    };

    // Pass: 1  Counters: 64
    std::vector<uint32_t> expectedCountersPass1 =
    {
        40883, 40968, 41053, 41138, 41223, 41308, 41393, 41478, 41563, 41648,
        41733, 41818, 41903, 41988, 42073, 42158, 42243, 42328, 42413, 42498,
        42583, 42668, 42753, 42838, 42923, 43008, 43093, 43178, 43263, 43348,
        43433, 43518, 43603, 43688, 43773, 43858, 43943, 44028, 44113, 44198,
        44283, 44368, 44453, 44538, 44623, 44708, 44793, 44878, 44963, 45048,
        45133, 45218, 45303, 45388, 45473, 45558, 45643, 45728, 45813, 45898,
        45983, 46068, 46153, 46238
    };

    std::vector< std::vector<uint32_t> > expectedHwCountersPerPass =
    {
        expectedCountersPass0,
        expectedCountersPass1,
    };

    // Result locations (Pass, Offset)

    // Pass: 0  Counters: 77
    std::map<uint32_t, GPA_CounterResultLocation> expectedLocations0
    {
        MakeExpectedCounterLocationEntry(0, 0)
        MakeExpectedCounterLocationEntry(0, 64)
        MakeExpectedCounterLocationEntry(0, 128)
        MakeExpectedCounterLocationEntry(0, 192)
        MakeExpectedCounterLocationEntry(1, 0)
        MakeExpectedCounterLocationEntry(0, 1)
        MakeExpectedCounterLocationEntry(0, 65)
        MakeExpectedCounterLocationEntry(0, 129)
        MakeExpectedCounterLocationEntry(0, 193)
        MakeExpectedCounterLocationEntry(1, 1)
        MakeExpectedCounterLocationEntry(0, 2)
        MakeExpectedCounterLocationEntry(0, 66)
        MakeExpectedCounterLocationEntry(0, 130)
        MakeExpectedCounterLocationEntry(0, 194)
        MakeExpectedCounterLocationEntry(1, 2)
        MakeExpectedCounterLocationEntry(0, 3)
        MakeExpectedCounterLocationEntry(0, 67)
        MakeExpectedCounterLocationEntry(0, 131)
        MakeExpectedCounterLocationEntry(0, 195)
        MakeExpectedCounterLocationEntry(1, 3)
        MakeExpectedCounterLocationEntry(0, 4)
        MakeExpectedCounterLocationEntry(0, 68)
        MakeExpectedCounterLocationEntry(0, 132)
        MakeExpectedCounterLocationEntry(0, 196)
        MakeExpectedCounterLocationEntry(1, 4)
        MakeExpectedCounterLocationEntry(0, 5)
        MakeExpectedCounterLocationEntry(0, 69)
        MakeExpectedCounterLocationEntry(0, 133)
        MakeExpectedCounterLocationEntry(0, 197)
        MakeExpectedCounterLocationEntry(1, 5)
        MakeExpectedCounterLocationEntry(0, 6)
        MakeExpectedCounterLocationEntry(0, 70)
        MakeExpectedCounterLocationEntry(0, 134)
        MakeExpectedCounterLocationEntry(0, 198)
        MakeExpectedCounterLocationEntry(1, 6)
        MakeExpectedCounterLocationEntry(0, 7)
        MakeExpectedCounterLocationEntry(0, 71)
        MakeExpectedCounterLocationEntry(0, 135)
        MakeExpectedCounterLocationEntry(0, 199)
        MakeExpectedCounterLocationEntry(1, 7)
        MakeExpectedCounterLocationEntry(0, 8)
        MakeExpectedCounterLocationEntry(0, 72)
        MakeExpectedCounterLocationEntry(0, 136)
        MakeExpectedCounterLocationEntry(0, 200)
        MakeExpectedCounterLocationEntry(1, 8)
        MakeExpectedCounterLocationEntry(0, 9)
        MakeExpectedCounterLocationEntry(0, 73)
        MakeExpectedCounterLocationEntry(0, 137)
        MakeExpectedCounterLocationEntry(0, 201)
        MakeExpectedCounterLocationEntry(1, 9)
        MakeExpectedCounterLocationEntry(0, 10)
        MakeExpectedCounterLocationEntry(0, 74)
        MakeExpectedCounterLocationEntry(0, 138)
        MakeExpectedCounterLocationEntry(0, 202)
        MakeExpectedCounterLocationEntry(1, 10)
        MakeExpectedCounterLocationEntry(0, 11)
        MakeExpectedCounterLocationEntry(0, 75)
        MakeExpectedCounterLocationEntry(0, 139)
        MakeExpectedCounterLocationEntry(0, 203)
        MakeExpectedCounterLocationEntry(1, 11)
        MakeExpectedCounterLocationEntry(0, 12)
        MakeExpectedCounterLocationEntry(0, 76)
        MakeExpectedCounterLocationEntry(0, 140)
        MakeExpectedCounterLocationEntry(0, 204)
        MakeExpectedCounterLocationEntry(1, 12)
        MakeExpectedCounterLocationEntry(0, 13)
        MakeExpectedCounterLocationEntry(0, 77)
        MakeExpectedCounterLocationEntry(0, 141)
        MakeExpectedCounterLocationEntry(0, 205)
        MakeExpectedCounterLocationEntry(1, 13)
        MakeExpectedCounterLocationEntry(0, 14)
        MakeExpectedCounterLocationEntry(0, 78)
        MakeExpectedCounterLocationEntry(0, 142)
        MakeExpectedCounterLocationEntry(0, 206)
        MakeExpectedCounterLocationEntry(1, 14)
        MakeExpectedCounterLocationEntry(0, 15)
        MakeExpectedCounterLocationEntry(0, 79)
        MakeExpectedCounterLocationEntry(0, 143)
        MakeExpectedCounterLocationEntry(0, 207)
        MakeExpectedCounterLocationEntry(1, 15)
        MakeExpectedCounterLocationEntry(0, 16)
        MakeExpectedCounterLocationEntry(0, 80)
        MakeExpectedCounterLocationEntry(0, 144)
        MakeExpectedCounterLocationEntry(0, 208)
        MakeExpectedCounterLocationEntry(1, 16)
        MakeExpectedCounterLocationEntry(0, 17)
        MakeExpectedCounterLocationEntry(0, 81)
        MakeExpectedCounterLocationEntry(0, 145)
        MakeExpectedCounterLocationEntry(0, 209)
        MakeExpectedCounterLocationEntry(1, 17)
        MakeExpectedCounterLocationEntry(0, 18)
        MakeExpectedCounterLocationEntry(0, 82)
        MakeExpectedCounterLocationEntry(0, 146)
        MakeExpectedCounterLocationEntry(0, 210)
        MakeExpectedCounterLocationEntry(1, 18)
        MakeExpectedCounterLocationEntry(0, 19)
        MakeExpectedCounterLocationEntry(0, 83)
        MakeExpectedCounterLocationEntry(0, 147)
        MakeExpectedCounterLocationEntry(0, 211)
        MakeExpectedCounterLocationEntry(1, 19)
        MakeExpectedCounterLocationEntry(0, 20)
        MakeExpectedCounterLocationEntry(0, 84)
        MakeExpectedCounterLocationEntry(0, 148)
        MakeExpectedCounterLocationEntry(0, 212)
        MakeExpectedCounterLocationEntry(1, 20)
        MakeExpectedCounterLocationEntry(0, 21)
        MakeExpectedCounterLocationEntry(0, 85)
        MakeExpectedCounterLocationEntry(0, 149)
        MakeExpectedCounterLocationEntry(0, 213)
        MakeExpectedCounterLocationEntry(1, 21)
        MakeExpectedCounterLocationEntry(0, 22)
        MakeExpectedCounterLocationEntry(0, 86)
        MakeExpectedCounterLocationEntry(0, 150)
        MakeExpectedCounterLocationEntry(0, 214)
        MakeExpectedCounterLocationEntry(1, 22)
        MakeExpectedCounterLocationEntry(0, 23)
        MakeExpectedCounterLocationEntry(0, 87)
        MakeExpectedCounterLocationEntry(0, 151)
        MakeExpectedCounterLocationEntry(0, 215)
        MakeExpectedCounterLocationEntry(1, 23)
        MakeExpectedCounterLocationEntry(0, 24)
        MakeExpectedCounterLocationEntry(0, 88)
        MakeExpectedCounterLocationEntry(0, 152)
        MakeExpectedCounterLocationEntry(0, 216)
        MakeExpectedCounterLocationEntry(1, 24)
        MakeExpectedCounterLocationEntry(0, 25)
        MakeExpectedCounterLocationEntry(0, 89)
        MakeExpectedCounterLocationEntry(0, 153)
        MakeExpectedCounterLocationEntry(0, 217)
        MakeExpectedCounterLocationEntry(1, 25)
        MakeExpectedCounterLocationEntry(0, 26)
        MakeExpectedCounterLocationEntry(0, 90)
        MakeExpectedCounterLocationEntry(0, 154)
        MakeExpectedCounterLocationEntry(0, 218)
        MakeExpectedCounterLocationEntry(1, 26)
        MakeExpectedCounterLocationEntry(0, 27)
        MakeExpectedCounterLocationEntry(0, 91)
        MakeExpectedCounterLocationEntry(0, 155)
        MakeExpectedCounterLocationEntry(0, 219)
        MakeExpectedCounterLocationEntry(1, 27)
        MakeExpectedCounterLocationEntry(0, 28)
        MakeExpectedCounterLocationEntry(0, 92)
        MakeExpectedCounterLocationEntry(0, 156)
        MakeExpectedCounterLocationEntry(0, 220)
        MakeExpectedCounterLocationEntry(1, 28)
        MakeExpectedCounterLocationEntry(0, 29)
        MakeExpectedCounterLocationEntry(0, 93)
        MakeExpectedCounterLocationEntry(0, 157)
        MakeExpectedCounterLocationEntry(0, 221)
        MakeExpectedCounterLocationEntry(1, 29)
        MakeExpectedCounterLocationEntry(0, 30)
        MakeExpectedCounterLocationEntry(0, 94)
        MakeExpectedCounterLocationEntry(0, 158)
        MakeExpectedCounterLocationEntry(0, 222)
        MakeExpectedCounterLocationEntry(1, 30)
        MakeExpectedCounterLocationEntry(0, 31)
        MakeExpectedCounterLocationEntry(0, 95)
        MakeExpectedCounterLocationEntry(0, 159)
        MakeExpectedCounterLocationEntry(0, 223)
        MakeExpectedCounterLocationEntry(1, 31)
        MakeExpectedCounterLocationEntry(0, 32)
        MakeExpectedCounterLocationEntry(0, 96)
        MakeExpectedCounterLocationEntry(0, 160)
        MakeExpectedCounterLocationEntry(0, 224)
        MakeExpectedCounterLocationEntry(1, 32)
        MakeExpectedCounterLocationEntry(0, 33)
        MakeExpectedCounterLocationEntry(0, 97)
        MakeExpectedCounterLocationEntry(0, 161)
        MakeExpectedCounterLocationEntry(0, 225)
        MakeExpectedCounterLocationEntry(1, 33)
        MakeExpectedCounterLocationEntry(0, 34)
        MakeExpectedCounterLocationEntry(0, 98)
        MakeExpectedCounterLocationEntry(0, 162)
        MakeExpectedCounterLocationEntry(0, 226)
        MakeExpectedCounterLocationEntry(1, 34)
        MakeExpectedCounterLocationEntry(0, 35)
        MakeExpectedCounterLocationEntry(0, 99)
        MakeExpectedCounterLocationEntry(0, 163)
        MakeExpectedCounterLocationEntry(0, 227)
        MakeExpectedCounterLocationEntry(1, 35)
        MakeExpectedCounterLocationEntry(0, 36)
        MakeExpectedCounterLocationEntry(0, 100)
        MakeExpectedCounterLocationEntry(0, 164)
        MakeExpectedCounterLocationEntry(0, 228)
        MakeExpectedCounterLocationEntry(1, 36)
        MakeExpectedCounterLocationEntry(0, 37)
        MakeExpectedCounterLocationEntry(0, 101)
        MakeExpectedCounterLocationEntry(0, 165)
        MakeExpectedCounterLocationEntry(0, 229)
        MakeExpectedCounterLocationEntry(1, 37)
        MakeExpectedCounterLocationEntry(0, 38)
        MakeExpectedCounterLocationEntry(0, 102)
        MakeExpectedCounterLocationEntry(0, 166)
        MakeExpectedCounterLocationEntry(0, 230)
        MakeExpectedCounterLocationEntry(1, 38)
        MakeExpectedCounterLocationEntry(0, 39)
        MakeExpectedCounterLocationEntry(0, 103)
        MakeExpectedCounterLocationEntry(0, 167)
        MakeExpectedCounterLocationEntry(0, 231)
        MakeExpectedCounterLocationEntry(1, 39)
        MakeExpectedCounterLocationEntry(0, 40)
        MakeExpectedCounterLocationEntry(0, 104)
        MakeExpectedCounterLocationEntry(0, 168)
        MakeExpectedCounterLocationEntry(0, 232)
        MakeExpectedCounterLocationEntry(1, 40)
        MakeExpectedCounterLocationEntry(0, 41)
        MakeExpectedCounterLocationEntry(0, 105)
        MakeExpectedCounterLocationEntry(0, 169)
        MakeExpectedCounterLocationEntry(0, 233)
        MakeExpectedCounterLocationEntry(1, 41)
        MakeExpectedCounterLocationEntry(0, 42)
        MakeExpectedCounterLocationEntry(0, 106)
        MakeExpectedCounterLocationEntry(0, 170)
        MakeExpectedCounterLocationEntry(0, 234)
        MakeExpectedCounterLocationEntry(1, 42)
        MakeExpectedCounterLocationEntry(0, 43)
        MakeExpectedCounterLocationEntry(0, 107)
        MakeExpectedCounterLocationEntry(0, 171)
        MakeExpectedCounterLocationEntry(0, 235)
        MakeExpectedCounterLocationEntry(1, 43)
        MakeExpectedCounterLocationEntry(0, 44)
        MakeExpectedCounterLocationEntry(0, 108)
        MakeExpectedCounterLocationEntry(0, 172)
        MakeExpectedCounterLocationEntry(0, 236)
        MakeExpectedCounterLocationEntry(1, 44)
        MakeExpectedCounterLocationEntry(0, 45)
        MakeExpectedCounterLocationEntry(0, 109)
        MakeExpectedCounterLocationEntry(0, 173)
        MakeExpectedCounterLocationEntry(0, 237)
        MakeExpectedCounterLocationEntry(1, 45)
        MakeExpectedCounterLocationEntry(0, 46)
        MakeExpectedCounterLocationEntry(0, 110)
        MakeExpectedCounterLocationEntry(0, 174)
        MakeExpectedCounterLocationEntry(0, 238)
        MakeExpectedCounterLocationEntry(1, 46)
        MakeExpectedCounterLocationEntry(0, 47)
        MakeExpectedCounterLocationEntry(0, 111)
        MakeExpectedCounterLocationEntry(0, 175)
        MakeExpectedCounterLocationEntry(0, 239)
        MakeExpectedCounterLocationEntry(1, 47)
        MakeExpectedCounterLocationEntry(0, 48)
        MakeExpectedCounterLocationEntry(0, 112)
        MakeExpectedCounterLocationEntry(0, 176)
        MakeExpectedCounterLocationEntry(0, 240)
        MakeExpectedCounterLocationEntry(1, 48)
        MakeExpectedCounterLocationEntry(0, 49)
        MakeExpectedCounterLocationEntry(0, 113)
        MakeExpectedCounterLocationEntry(0, 177)
        MakeExpectedCounterLocationEntry(0, 241)
        MakeExpectedCounterLocationEntry(1, 49)
        MakeExpectedCounterLocationEntry(0, 50)
        MakeExpectedCounterLocationEntry(0, 114)
        MakeExpectedCounterLocationEntry(0, 178)
        MakeExpectedCounterLocationEntry(0, 242)
        MakeExpectedCounterLocationEntry(1, 50)
        MakeExpectedCounterLocationEntry(0, 51)
        MakeExpectedCounterLocationEntry(0, 115)
        MakeExpectedCounterLocationEntry(0, 179)
        MakeExpectedCounterLocationEntry(0, 243)
        MakeExpectedCounterLocationEntry(1, 51)
        MakeExpectedCounterLocationEntry(0, 52)
        MakeExpectedCounterLocationEntry(0, 116)
        MakeExpectedCounterLocationEntry(0, 180)
        MakeExpectedCounterLocationEntry(0, 244)
        MakeExpectedCounterLocationEntry(1, 52)
        MakeExpectedCounterLocationEntry(0, 53)
        MakeExpectedCounterLocationEntry(0, 117)
        MakeExpectedCounterLocationEntry(0, 181)
        MakeExpectedCounterLocationEntry(0, 245)
        MakeExpectedCounterLocationEntry(1, 53)
        MakeExpectedCounterLocationEntry(0, 54)
        MakeExpectedCounterLocationEntry(0, 118)
        MakeExpectedCounterLocationEntry(0, 182)
        MakeExpectedCounterLocationEntry(0, 246)
        MakeExpectedCounterLocationEntry(1, 54)
        MakeExpectedCounterLocationEntry(0, 55)
        MakeExpectedCounterLocationEntry(0, 119)
        MakeExpectedCounterLocationEntry(0, 183)
        MakeExpectedCounterLocationEntry(0, 247)
        MakeExpectedCounterLocationEntry(1, 55)
        MakeExpectedCounterLocationEntry(0, 56)
        MakeExpectedCounterLocationEntry(0, 120)
        MakeExpectedCounterLocationEntry(0, 184)
        MakeExpectedCounterLocationEntry(0, 248)
        MakeExpectedCounterLocationEntry(1, 56)
        MakeExpectedCounterLocationEntry(0, 57)
        MakeExpectedCounterLocationEntry(0, 121)
        MakeExpectedCounterLocationEntry(0, 185)
        MakeExpectedCounterLocationEntry(0, 249)
        MakeExpectedCounterLocationEntry(1, 57)
        MakeExpectedCounterLocationEntry(0, 58)
        MakeExpectedCounterLocationEntry(0, 122)
        MakeExpectedCounterLocationEntry(0, 186)
        MakeExpectedCounterLocationEntry(0, 250)
        MakeExpectedCounterLocationEntry(1, 58)
        MakeExpectedCounterLocationEntry(0, 59)
        MakeExpectedCounterLocationEntry(0, 123)
        MakeExpectedCounterLocationEntry(0, 187)
        MakeExpectedCounterLocationEntry(0, 251)
        MakeExpectedCounterLocationEntry(1, 59)
        MakeExpectedCounterLocationEntry(0, 60)
        MakeExpectedCounterLocationEntry(0, 124)
        MakeExpectedCounterLocationEntry(0, 188)
        MakeExpectedCounterLocationEntry(0, 252)
        MakeExpectedCounterLocationEntry(1, 60)
        MakeExpectedCounterLocationEntry(0, 61)
        MakeExpectedCounterLocationEntry(0, 125)
        MakeExpectedCounterLocationEntry(0, 189)
        MakeExpectedCounterLocationEntry(0, 253)
        MakeExpectedCounterLocationEntry(1, 61)
        MakeExpectedCounterLocationEntry(0, 62)
        MakeExpectedCounterLocationEntry(0, 126)
        MakeExpectedCounterLocationEntry(0, 190)
        MakeExpectedCounterLocationEntry(0, 254)
        MakeExpectedCounterLocationEntry(1, 62)
        MakeExpectedCounterLocationEntry(0, 63)
        MakeExpectedCounterLocationEntry(0, 127)
        MakeExpectedCounterLocationEntry(0, 191)
        MakeExpectedCounterLocationEntry(0, 255)
        MakeExpectedCounterLocationEntry(1, 63)
    };

    std::map< uint32_t, std::map<uint32_t, GPA_CounterResultLocation> > expectedResultLocations =
    {
        { L1CacheHitCountDX11Gfx9, expectedLocations0 }
    };

    VerifyCountersInPass(GPA_API_DIRECTX_11, gDevIdGfx9, FALSE, counters, expectedHwCountersPerPass, expectedResultLocations);
}
#endif // _WIN32
