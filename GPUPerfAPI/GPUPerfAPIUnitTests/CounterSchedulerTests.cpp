//==============================================================================
// Copyright (c) 2012-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Unit tests for Counter Scheduler
//==============================================================================

#include "CounterGeneratorTests.h"
#include "GPASplitCountersInterfaces.h"

#include "counters/PublicCountersDX11Gfx6.h"
#include "counters/PublicCountersDX11Gfx7.h"
#include "counters/PublicCountersDX11Gfx8.h"

#include "GPAInternalCounter.h"
#include "InternalCountersDX11Gfx6.h"
#include "InternalCountersDX11Gfx7.h"
#include "InternalCountersDX11Gfx8.h"

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

    VerifyPassCount(GPA_API_OPENCL, gDevIdSI, counters, 1);
}

// Test the openCL counter names on CI hardware
TEST(CounterDLLTests, OpenCLCounterSchedulingCI)
{
    std::vector<unsigned int> counters;
    counters.push_back(0);
    counters.push_back(1);
    counters.push_back(2);

    VerifyPassCount(GPA_API_OPENCL, gDevIdCI, counters, 1);
}

// Test the openCL counter names on VI hardware
TEST(CounterDLLTests, OpenCLCounterSchedulingVI)
{
    std::vector<unsigned int> counters;
    counters.push_back(0);
    counters.push_back(1);
    counters.push_back(2);

    VerifyPassCount(GPA_API_OPENCL, gDevIdVI, counters, 1);
}

TEST(CounterDLLTests, OpenCLResultLocations)
{
    // counters to enable (Wavefronts, VALUInsts, SALUInsts, VFetchInsts, SFetchInsts, VWriteInsts, VALUUtilization, VALUBusy, SALUBusy)
    std::vector<unsigned int> counters;
    counters.push_back(0); // Wavefronts
    counters.push_back(1); // VALUInsts
    counters.push_back(2); // SALUInsts
    counters.push_back(3); // VFetchInsts
    counters.push_back(4); // SFetchInsts
    counters.push_back(5); // VWriteInsts
    counters.push_back(8); // VALUUtilization
    counters.push_back(9); // VALUBusy
    counters.push_back(10); // SALUBusy

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsWavefronts;
    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsVALUInsts;
    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsSALUInsts;
    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsVFetchInsts;
    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsSFetchInsts;
    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsVWriteInsts;
    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsVALUUtilization;
    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsVALUBusy;
    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsSALUBusy;

    std::vector<unsigned int> expectedCountersPass1;
    // Wavefronts
    expectedCountersPass1.push_back(1639); expectedLocationsWavefronts[1639] = MakeLocation(0, 0);
    // VALUInsts
    expectedCountersPass1.push_back(1649); expectedLocationsVALUInsts[1649] = MakeLocation(0, 1);
    /* expectedCountersPass1.push_back(1639); */ expectedLocationsVALUInsts[1639] = MakeLocation(0, 0);
    // SALUInsts
    expectedCountersPass1.push_back(1653); expectedLocationsSALUInsts[1653] = MakeLocation(0, 2);
    /* expectedCountersPass1.push_back(1639); */ expectedLocationsSALUInsts[1639] = MakeLocation(0, 0);
    // VFetchInsts
    expectedCountersPass1.push_back(1651); expectedLocationsVFetchInsts[1651] = MakeLocation(0, 3);
    /*expectedCountersPass1.push_back(1639); */ expectedLocationsVFetchInsts[1639] = MakeLocation(0, 0);
    // SFetchInsts
    expectedCountersPass1.push_back(1654); expectedLocationsSFetchInsts[1654] = MakeLocation(0, 4);
    /*expectedCountersPass1.push_back(1639); */ expectedLocationsSFetchInsts[1639] = MakeLocation(0, 0);
    // VWriteInsts
    expectedCountersPass1.push_back(1650); expectedLocationsVWriteInsts[1650] = MakeLocation(0, 5);
    /* expectedCountersPass1.push_back(1639); */ expectedLocationsVWriteInsts[1639] = MakeLocation(0, 0);
    // VALUUtilization
    expectedCountersPass1.push_back(1693); expectedLocationsVALUUtilization[1693] = MakeLocation(0, 6);
    expectedCountersPass1.push_back(1685); expectedLocationsVALUUtilization[1685] = MakeLocation(0, 7);
    // VALUUBusy
    /* expectedCountersPass1.push_back(1685); */ expectedLocationsVALUBusy[1685] = MakeLocation(0, 7);
    expectedCountersPass1.push_back(976); expectedLocationsVALUBusy[976] = MakeLocation(0, 8);

    std::vector<unsigned int> expectedCountersPass2;
    // SALUBusy
    expectedCountersPass2.push_back(1690); expectedLocationsSALUBusy[1690] = MakeLocation(1, 0);
    expectedCountersPass2.push_back(976);  expectedLocationsSALUBusy[976] = MakeLocation(1, 1);

    std::vector< std::vector<unsigned int> > expectedHwCountersPerPass;
    expectedHwCountersPerPass.push_back(expectedCountersPass1);
    expectedHwCountersPerPass.push_back(expectedCountersPass2);

    std::map< unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > expectedResultLocations;
    expectedResultLocations[0] = expectedLocationsWavefronts;
    expectedResultLocations[1] = expectedLocationsVALUInsts;
    expectedResultLocations[2] = expectedLocationsSALUInsts;
    expectedResultLocations[3] = expectedLocationsVFetchInsts;
    expectedResultLocations[4] = expectedLocationsSFetchInsts;
    expectedResultLocations[5] = expectedLocationsVWriteInsts;
    expectedResultLocations[8] = expectedLocationsVALUUtilization;
    expectedResultLocations[9] = expectedLocationsVALUBusy;
    expectedResultLocations[10] = expectedLocationsSALUBusy;

    VerifyCountersInPass(GPA_API_OPENCL, gDevIdSI, counters, expectedHwCountersPerPass, expectedResultLocations);
}

TEST(CounterDLLTests, OpenGLCounterScheduling)
{
    std::vector<unsigned int> counters;
    counters.push_back(0);
    counters.push_back(1);
    counters.push_back(2);

    VerifyHardwareNotSupported(GPA_API_OPENGL, gDevIdUnknown);

    VerifyPassCount(GPA_API_OPENGL, gDevIdSI,   counters, 2);
    VerifyPassCount(GPA_API_OPENGL, gDevIdCI,   counters, 2);
    VerifyPassCount(GPA_API_OPENGL, gDevIdVI,   counters, 2);
}

TEST(CounterDLLTests, DX11CounterScheduling)
{
    std::vector<unsigned int> counters;
    counters.push_back(0);
    counters.push_back(1);
    counters.push_back(2);

    VerifyHardwareNotSupported(GPA_API_DIRECTX_11, gDevIdUnknown);

    VerifyPassCount(GPA_API_DIRECTX_11, gDevIdSI,   counters, 2);
    VerifyPassCount(GPA_API_DIRECTX_11, gDevIdCI,   counters, 2);
    VerifyPassCount(GPA_API_DIRECTX_11, gDevIdVI,   counters, 2);
}

TEST(CounterDLLTests, DX11CIBusyCounters)
{
    // counters to enable (VSBusy, HSBusy, DSBusy, GSBusy, PSBusy, CSBusy)
    std::vector<unsigned int> counters;
    counters.push_back(3);
    counters.push_back(5);
    counters.push_back(7);
    counters.push_back(9);
    counters.push_back(11);
    counters.push_back(13);

    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsVSBusy;
    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsHSBusy;
    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsDSBusy;
    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsGSBusy;
    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsPSBusy;
    std::map<unsigned int, GPA_CounterResultLocation> expectedLocationsCSBusy;


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
    expectedCountersPass1.push_back(7886);  expectedLocationsVSBusy[7886]  = MakeLocation(0, 24);

    std::vector<unsigned int> expectedCountersPass2;
    // VSBusy
    expectedCountersPass2.push_back(10359); expectedLocationsVSBusy[10359] = MakeLocation(1, 0);
    expectedCountersPass2.push_back(10545); expectedLocationsVSBusy[10545] = MakeLocation(1, 1);
    expectedCountersPass2.push_back(10731); expectedLocationsVSBusy[10731] = MakeLocation(1, 2);
    expectedCountersPass2.push_back(10917); expectedLocationsVSBusy[10917] = MakeLocation(1, 3);
    // HSBusy
    expectedCountersPass2.push_back(10343); expectedLocationsHSBusy[10343] = MakeLocation(1, 4);
    expectedCountersPass2.push_back(10529); expectedLocationsHSBusy[10529] = MakeLocation(1, 5);
    expectedCountersPass2.push_back(10715); expectedLocationsHSBusy[10715] = MakeLocation(1, 6);
    expectedCountersPass2.push_back(10901); expectedLocationsHSBusy[10901] = MakeLocation(1, 7);
    expectedCountersPass2.push_back(10349); expectedLocationsHSBusy[10349] = MakeLocation(1, 8);
    expectedCountersPass2.push_back(10535); expectedLocationsHSBusy[10535] = MakeLocation(1, 9);
    expectedCountersPass2.push_back(10721); expectedLocationsHSBusy[10721] = MakeLocation(1, 10);
    expectedCountersPass2.push_back(10907); expectedLocationsHSBusy[10907] = MakeLocation(1, 11);
    expectedCountersPass2.push_back(7886);  expectedLocationsHSBusy[7886]  = MakeLocation(1, 12);
    // GSBusy
    expectedCountersPass2.push_back(10322); expectedLocationsGSBusy[10322] = MakeLocation(1, 13);
    expectedCountersPass2.push_back(10508); expectedLocationsGSBusy[10508] = MakeLocation(1, 14);
    expectedCountersPass2.push_back(10694); expectedLocationsGSBusy[10694] = MakeLocation(1, 15);
    expectedCountersPass2.push_back(10880); expectedLocationsGSBusy[10880] = MakeLocation(1, 16);
    expectedCountersPass2.push_back(10325); expectedLocationsGSBusy[10325] = MakeLocation(1, 17);
    expectedCountersPass2.push_back(10511); expectedLocationsGSBusy[10511] = MakeLocation(1, 18);
    expectedCountersPass2.push_back(10697); expectedLocationsGSBusy[10697] = MakeLocation(1, 19);
    expectedCountersPass2.push_back(10883); expectedLocationsGSBusy[10883] = MakeLocation(1, 20);
    /*internalCounters.push_back(7886); */  expectedLocationsGSBusy[7886]  = MakeLocation(1, 12); // reused from HSBusy

    std::vector<unsigned int> expectedCountersPass3;
    // DSBusy
    expectedCountersPass3.push_back(10306); expectedLocationsDSBusy[10306] = MakeLocation(2, 0);
    expectedCountersPass3.push_back(10492); expectedLocationsDSBusy[10492] = MakeLocation(2, 1);
    expectedCountersPass3.push_back(10678); expectedLocationsDSBusy[10678] = MakeLocation(2, 2);
    expectedCountersPass3.push_back(10864); expectedLocationsDSBusy[10864] = MakeLocation(2, 3);
    expectedCountersPass3.push_back(10331); expectedLocationsDSBusy[10331] = MakeLocation(2, 4);
    expectedCountersPass3.push_back(10517); expectedLocationsDSBusy[10517] = MakeLocation(2, 5);
    expectedCountersPass3.push_back(10703); expectedLocationsDSBusy[10703] = MakeLocation(2, 6);
    expectedCountersPass3.push_back(10889); expectedLocationsDSBusy[10889] = MakeLocation(2, 7);
    expectedCountersPass3.push_back(10375); expectedLocationsDSBusy[10375] = MakeLocation(2, 8);
    expectedCountersPass3.push_back(10561); expectedLocationsDSBusy[10561] = MakeLocation(2, 9);
    expectedCountersPass3.push_back(10747); expectedLocationsDSBusy[10747] = MakeLocation(2, 10);
    expectedCountersPass3.push_back(10933); expectedLocationsDSBusy[10933] = MakeLocation(2, 11);
    expectedCountersPass3.push_back(10337); expectedLocationsDSBusy[10337] = MakeLocation(2, 12);
    expectedCountersPass3.push_back(10523); expectedLocationsDSBusy[10523] = MakeLocation(2, 13);
    expectedCountersPass3.push_back(10709); expectedLocationsDSBusy[10709] = MakeLocation(2, 14);
    expectedCountersPass3.push_back(10895); expectedLocationsDSBusy[10895] = MakeLocation(2, 15);
    expectedCountersPass3.push_back(10359); expectedLocationsDSBusy[10359] = MakeLocation(2, 16);
    expectedCountersPass3.push_back(10545); expectedLocationsDSBusy[10545] = MakeLocation(2, 17);
    expectedCountersPass3.push_back(10731); expectedLocationsDSBusy[10731] = MakeLocation(2, 18);
    expectedCountersPass3.push_back(10917); expectedLocationsDSBusy[10917] = MakeLocation(2, 19);
    expectedCountersPass3.push_back(7886);  expectedLocationsDSBusy[7886]  = MakeLocation(2, 20);

    // PSBusy
    /*expectedCountersPass3.push_back(10375); */ expectedLocationsPSBusy[10375] = MakeLocation(2, 8); // reused from DSBusy
    /*expectedCountersPass3.push_back(10561); */ expectedLocationsPSBusy[10561] = MakeLocation(2, 9); // reused from DSBusy
    /*expectedCountersPass3.push_back(10747); */ expectedLocationsPSBusy[10747] = MakeLocation(2, 10); // reused from DSBusy
    /*expectedCountersPass3.push_back(10933); */ expectedLocationsPSBusy[10933] = MakeLocation(2, 11); // reused from DSBusy
    expectedCountersPass3.push_back(10380);      expectedLocationsPSBusy[10380] = MakeLocation(2, 21);
    expectedCountersPass3.push_back(10566);      expectedLocationsPSBusy[10566] = MakeLocation(2, 22);
    expectedCountersPass3.push_back(10752);      expectedLocationsPSBusy[10752] = MakeLocation(2, 23);
    expectedCountersPass3.push_back(10938);      expectedLocationsPSBusy[10938] = MakeLocation(2, 24);
    /*expectedCountersPass3.push_back(7886); */  expectedLocationsPSBusy[7886]  = MakeLocation(2, 20); // reused from DSBusy

    std::vector<unsigned int> expectedCountersPass4;
    // CSBusy
    expectedCountersPass4.push_back(10363); expectedLocationsCSBusy[10363] = MakeLocation(3, 0);
    expectedCountersPass4.push_back(10549); expectedLocationsCSBusy[10549] = MakeLocation(3, 1);
    expectedCountersPass4.push_back(10735); expectedLocationsCSBusy[10735] = MakeLocation(3, 2);
    expectedCountersPass4.push_back(10921); expectedLocationsCSBusy[10921] = MakeLocation(3, 3);
    expectedCountersPass4.push_back(10367); expectedLocationsCSBusy[10367] = MakeLocation(3, 4);
    expectedCountersPass4.push_back(10553); expectedLocationsCSBusy[10553] = MakeLocation(3, 5);
    expectedCountersPass4.push_back(10739); expectedLocationsCSBusy[10739] = MakeLocation(3, 6);
    expectedCountersPass4.push_back(10925); expectedLocationsCSBusy[10925] = MakeLocation(3, 7);
    expectedCountersPass4.push_back(7886);  expectedLocationsCSBusy[7886]  = MakeLocation(3, 8);

    std::vector< std::vector<unsigned int> > expectedHwCountersPerPass;
    expectedHwCountersPerPass.push_back(expectedCountersPass1);
    expectedHwCountersPerPass.push_back(expectedCountersPass2);
    expectedHwCountersPerPass.push_back(expectedCountersPass3);
    expectedHwCountersPerPass.push_back(expectedCountersPass4);

    std::map< unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > expectedResultLocations;
    expectedResultLocations[3]  = expectedLocationsVSBusy;
    expectedResultLocations[5]  = expectedLocationsHSBusy;
    expectedResultLocations[7]  = expectedLocationsDSBusy;
    expectedResultLocations[9]  = expectedLocationsGSBusy;
    expectedResultLocations[11] = expectedLocationsPSBusy;
    expectedResultLocations[13] = expectedLocationsCSBusy;

    VerifyCountersInPass(GPA_API_DIRECTX_11, gDevIdCI, counters, expectedHwCountersPerPass, expectedResultLocations);
}

void TestGPUTimeVSBusyVSTimeCountersForDevice(unsigned int deviceId)
{
    // checks that different combinations of GPUTime (0) / VSBusy (3) / VSTime (4) are scheduled correctly regardless of order of inclusion

    static const int GPUTimeIndex = 0;
    static const int VSBusyIndex  = 3;
    static const int VSTimeIndex  = 4;
    std::vector<unsigned int> counters;

    // counters to enable (GPUTime, VSBusy)
    counters.clear();
    counters.push_back(GPUTimeIndex);
    counters.push_back(VSBusyIndex);
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, counters, 3);

    // counters to enable (VSBusy, GPUTime)
    counters.clear();
    counters.push_back(VSBusyIndex);
    counters.push_back(GPUTimeIndex);
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, counters, 3);

    // counters to enable (VSBusy, VSTime)
    counters.clear();
    counters.push_back(VSBusyIndex);
    counters.push_back(VSTimeIndex);
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, counters, 3);

    // counters to enable (VSTime, VSBusy)
    counters.clear();
    counters.push_back(VSTimeIndex);
    counters.push_back(VSBusyIndex);
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, counters, 3);

    // counters to enable (GPUTime, VSTime)
    counters.clear();
    counters.push_back(GPUTimeIndex);
    counters.push_back(VSTimeIndex);
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, counters, 3);

    // counters to enable (VSTime, GPUTime)
    counters.clear();
    counters.push_back(VSTimeIndex);
    counters.push_back(GPUTimeIndex);
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, counters, 3);

    // counters to enable (GPUTime, VSBusy, VSTime)
    counters.clear();
    counters.push_back(GPUTimeIndex);
    counters.push_back(VSBusyIndex);
    counters.push_back(VSTimeIndex);
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, counters, 3);

    // counters to enable (GPUTime, VSTime, VSBusy)
    counters.clear();
    counters.push_back(GPUTimeIndex);
    counters.push_back(VSTimeIndex);
    counters.push_back(VSBusyIndex);
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, counters, 3);

    // counters to enable (VSTime, GPUTime, VSBusy)
    counters.clear();
    counters.push_back(4);
    counters.push_back(GPUTimeIndex);
    counters.push_back(VSBusyIndex);
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, counters, 3);

    // counters to enable (VSTime, VSBusy, GPUTime)
    counters.clear();
    counters.push_back(VSTimeIndex);
    counters.push_back(VSBusyIndex);
    counters.push_back(GPUTimeIndex);
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, counters, 3);

    // counters to enable (VSBusy, GPUTime, VSTime)
    counters.clear();
    counters.push_back(VSBusyIndex);
    counters.push_back(GPUTimeIndex);
    counters.push_back(VSTimeIndex);
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, counters, 3);

    // counters to enable (VSBusy, VSTime, GPUTime)
    counters.clear();
    counters.push_back(VSBusyIndex);
    counters.push_back(VSTimeIndex);
    counters.push_back(GPUTimeIndex);
    VerifyPassCount(GPA_API_DIRECTX_11, deviceId, counters, 3);
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

#ifdef GDT_INTERNAL
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

    VerifyCountersInPass(GPA_API_DIRECTX_11, deviceId, counters, expectedHwCountersPerPass, expectedResultLocations);
}

static unsigned int GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION generation, unsigned int& gpuTimeHWCounterIndex)
{
    unsigned int numHwCounters = 0;
    gpuTimeHWCounterIndex = 0;

    GPA_CounterGroupDesc* pHardwareGroups = nullptr;
    GPA_HardwareCounterDesc** ppHardwareCounters = nullptr;
    unsigned int hwGroupCount = 0;
    unsigned int hwGPUTimeGroupIndex = 0;

    switch (generation)
    {
        case GPA_HW_GENERATION_SOUTHERNISLAND:
            pHardwareGroups = HWDX11GroupsGfx6;
            hwGroupCount = HWDX11GroupCountGfx6;
            ppHardwareCounters = DX11CounterGroupArrayGfx6;
            hwGPUTimeGroupIndex = HWDX11GPUTimeIndexGfx6;
            break;

        case GPA_HW_GENERATION_SEAISLAND:
            pHardwareGroups = HWDX11GroupsGfx7;
            hwGroupCount = HWDX11GroupCountGfx7;
            ppHardwareCounters = DX11CounterGroupArrayGfx7;
            hwGPUTimeGroupIndex = HWDX11GPUTimeIndexGfx7;
            break;

        case GPA_HW_GENERATION_VOLCANICISLAND:
            pHardwareGroups = HWDX11GroupsGfx8;
            hwGroupCount = HWDX11GroupCountGfx8;
            ppHardwareCounters = DX11CounterGroupArrayGfx8;
            hwGPUTimeGroupIndex = HWDX11GPUTimeIndexGfx8;
            break;
    }

    for (unsigned int i = 0; i < hwGroupCount; i++)
    {
        if (hwGPUTimeGroupIndex == i)
        {
            gpuTimeHWCounterIndex = numHwCounters;
        }

        numHwCounters += pHardwareGroups[i].m_numCounters;
    }

    return numHwCounters;
}

/// Test the D3D11 QUERY counters (software counters) across different generations
TEST(CounterDLLTests, DX11D3DCounters)
{
    unsigned int dummyGpuTimeHWIndex  = 0;  // this is the index of the GPUTime hw counter (i.e. GPUTime_Bottom_To_Bottom)
    unsigned int D3DCounterIndex      = 0;  // this is the index into the software counters of "OCCLUSION" - see GPASwCounterManager.h
    unsigned int publicCounterCount   = 0;  // this is the number of public counters exposed
    unsigned int hardwareCounterCount = 0;  // this is the number of hardware counters exposed, which is used to offset the sw counter index

    // Gfx6
    D3DCounterIndex      = 1;
    publicCounterCount  = DX11GFX6_PUBLIC_COUNTER_COUNT;
    hardwareCounterCount = GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION_SOUTHERNISLAND, dummyGpuTimeHWIndex);
    TestD3D11QueryCounter(gDevIdSI, D3DCounterIndex, publicCounterCount, hardwareCounterCount);

    // Gfx7
    D3DCounterIndex      = 1;
    publicCounterCount  = DX11GFX7_PUBLIC_COUNTER_COUNT;
    hardwareCounterCount = GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION_SEAISLAND, dummyGpuTimeHWIndex);
    TestD3D11QueryCounter(gDevIdCI, D3DCounterIndex, publicCounterCount, hardwareCounterCount);

    // Gfx8
    D3DCounterIndex      = 1;
    publicCounterCount  = DX11GFX8_PUBLIC_COUNTER_COUNT;
    hardwareCounterCount = GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION_VOLCANICISLAND, dummyGpuTimeHWIndex);
    TestD3D11QueryCounter(gDevIdVI, D3DCounterIndex, publicCounterCount, hardwareCounterCount);
}

TEST(CounterDLLTests, DX11D3DCountersAndGPUTime)
{
    unsigned int gpuTimeHWIndex       = 0;  // this is the index of the GPUTime hw counter (i.e. GPUTime_Bottom_To_Bottom)
    unsigned int D3DCounterIndex      = 0;  // this is the index into the software counters of "OCCLUSION" - see GPASwCounterManager.h
    unsigned int publicCounterCount   = 0;  // this is the number of public counters exposed
    unsigned int hardwareCounterCount = 0;  // this is the number of hardware counters exposed, which is used to offset the sw counter index

    // Gfx6
    D3DCounterIndex      = 1;
    publicCounterCount   = DX11GFX6_PUBLIC_COUNTER_COUNT;
    hardwareCounterCount = GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION_SOUTHERNISLAND, gpuTimeHWIndex);
    TestD3D11QueryCounter(gDevIdSI, D3DCounterIndex, publicCounterCount, hardwareCounterCount, gpuTimeHWIndex);

    // Gfx7
    D3DCounterIndex      = 1;
    publicCounterCount   = DX11GFX7_PUBLIC_COUNTER_COUNT;
    hardwareCounterCount = GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION_SEAISLAND, gpuTimeHWIndex);
    TestD3D11QueryCounter(gDevIdCI, D3DCounterIndex, publicCounterCount, hardwareCounterCount, gpuTimeHWIndex);

    // Gfx8
    D3DCounterIndex      = 1;
    publicCounterCount   = DX11GFX8_PUBLIC_COUNTER_COUNT;
    hardwareCounterCount = GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION_VOLCANICISLAND, gpuTimeHWIndex);
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

#ifdef GDT_INTERNAL
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

    VerifyCountersInPass(GPA_API_DIRECTX_11, deviceId, counters, expectedHwCountersPerPass, expectedResultLocations);
}

TEST(CounterDLLTests, AllDX11D3DCounters)
{
    unsigned int dummyGpuTimeHWIndex  = 0;  // this is the index of the GPUTime hw counter (i.e. GPUTime_Bottom_To_Bottom)
    unsigned int publicCounterCount = 0;  // this is the number of public counters exposed
    unsigned int hardwareCounterCount = 0;  // this is the number of hardware counters exposed, which is used to offset the sw counter index
    unsigned int D3DQueryCounterCount = 29; // there are currently 29 D3D11 query counters

    // Gfx6
    publicCounterCount   = DX11GFX6_PUBLIC_COUNTER_COUNT;
    hardwareCounterCount = GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION_SOUTHERNISLAND, dummyGpuTimeHWIndex);
    TestAllD3D11QueryCounters(gDevIdSI, D3DQueryCounterCount, publicCounterCount, hardwareCounterCount);

    // Gfx7
    publicCounterCount   = DX11GFX7_PUBLIC_COUNTER_COUNT;
    hardwareCounterCount = GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION_SEAISLAND, dummyGpuTimeHWIndex);
    TestAllD3D11QueryCounters(gDevIdCI, D3DQueryCounterCount, publicCounterCount, hardwareCounterCount);

    // Gfx8
    publicCounterCount   = DX11GFX8_PUBLIC_COUNTER_COUNT;
    hardwareCounterCount = GetNumberOfDX11HardwareCountersAndGPUTimeIndex(GPA_HW_GENERATION_VOLCANICISLAND, dummyGpuTimeHWIndex);
    TestAllD3D11QueryCounters(gDevIdVI, D3DQueryCounterCount, publicCounterCount, hardwareCounterCount);
}

TEST(CounterDLLTests, DX11CIPSBusyCounterResult)
{
    // test the result of PSBusy, which uses 9 internal counters
    unsigned int requiredCount = 9;

    // fabricate some results that will allow us to confirm the PSBusy counter
    // each result is 64 bit, so 8 chars.
    char* pAllResults = new(std::nothrow) char[requiredCount * 8];
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
    std::vector< char* > sampleResults;

    for (unsigned int i = 0; i < requiredCount; i++)
    {
        sampleResults.push_back(&(pAllResults[i * 8]));
    }

    VerifyCounterCalculation(GPA_API_DIRECTX_11, gDevIdCI, "PSBusy", sampleResults, 50);

    delete[] pAllResults;

}

TEST(CounterDLLTests, DX11VIPSBusyCounterResult)
{
    // test the result of PSBusy, which uses 9 internal counters
    unsigned int requiredCount = 9;

    // fabricate some results that will allow us to confirm the PSBusy counter
    // each result is 64 bit, so 8 chars.
    char* pAllResults = new(std::nothrow) char[requiredCount * 8];
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
    std::vector< char* > sampleResults;

    for (unsigned int i = 0; i < requiredCount; i++)
    {
        sampleResults.push_back(&(pAllResults[i * 8]));
    }

    VerifyCounterCalculation(GPA_API_DIRECTX_11, gDevIdVI, "PSBusy", sampleResults, 50);

    delete[] pAllResults;

}

TEST(CounterDLLTests, HSACounterScheduling)
{
    std::vector<unsigned int> counters;
    counters.push_back(0);
    counters.push_back(1);
    counters.push_back(2);

    VerifyHardwareNotSupported(GPA_API_HSA, gDevIdUnknown);
    VerifyHardwareNotSupported(GPA_API_HSA, gDevIdSI);

    VerifyPassCount(GPA_API_HSA, gDevIdCI, counters, 1);
    VerifyPassCount(GPA_API_HSA, gDevIdVI, counters, 1);
}

TEST(CounterDLLTests, DX11EnableAndDisable)
{
    std::vector<unsigned int> counters;
    counters.push_back(0);
    counters.push_back(1);
    counters.push_back(2);

    GPA_API_Type api = GPA_API_DIRECTX_11;
    unsigned int deviceId = gDevIdVI;

    HMODULE hDll = LoadLibraryA("GPUPerfAPICounters" GDT_PROJECT_SUFFIX ".dll");
    ASSERT_NE((HMODULE)nullptr, hDll);

    GPA_GetAvailableCountersProc GPA_GetAvailableCounters_fn = (GPA_GetAvailableCountersProc)GetProcAddress(hDll, "GPA_GetAvailableCounters");
    ASSERT_NE((GPA_GetAvailableCountersProc)nullptr, GPA_GetAvailableCounters_fn);

    GPA_ICounterAccessor* pCounterAccessor = nullptr;
    GPA_ICounterScheduler* pCounterScheduler = nullptr;
    GPA_Status status = GPA_GetAvailableCounters_fn(api, AMD_VENDOR_ID, deviceId, 0, &pCounterAccessor, &pCounterScheduler);
    EXPECT_EQ(GPA_STATUS_OK, status);
    EXPECT_NE((GPA_ICounterAccessor*)nullptr, pCounterAccessor);
    ASSERT_NE((GPA_ICounterScheduler*)nullptr, pCounterScheduler);

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
