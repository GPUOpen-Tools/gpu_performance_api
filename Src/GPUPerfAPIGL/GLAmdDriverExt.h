//==============================================================================
// Copyright (c) 2019 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GL AMD driver extensions
//==============================================================================

#ifndef _GL_AMD_DRIVER_EXT_H_
#define _GL_AMD_DRIVER_EXT_H_

namespace oglUtils
{
/// constant for the AMD-specific extended timer result
#define GL_QUERY_EXTENDED_TIMER_RESULT_AMDX 0x8870

    /// ClockMode enum defined by OpenGL driver
    enum AMDXClockMode
    {
        AMDX_DefaultMode     = 0,           ///< Device clocks and other power settings are restored to default.
        AMDX_QueryClockRatio = 1,           ///< Queries the current device clock ratios. Leaves the clock mode of the device unchanged.
        AMDX_ProfilingClock  = 2,           ///< Scale down from peak ratio. Clocks are set to a constant amount which is
                                            ///  known to be power and thermal sustainable. The engine/memory clock ratio
                                            ///  will be kept the same as much as possible.
        AMDX_MinimumMemoryClock = 3,        ///< Memory clock is set to the lowest available level. Engine clock is set to
                                            ///  thermal and power sustainable level.
        AMDX_MinimumEngineClock = 4,        ///< Engine clock is set to the lowest available level. Memory clock is set to
                                            ///  thermal and power sustainable level.
        AMDX_PeakClock = 5,                 ///< Clocks set to maximum when possible. Fan set to maximum. Note: Under power
                                            ///  and thermal constraints device will clock down.
        AMDX_QueryProfilingClockRatio = 6,  ///< Queries the profiling device clock ratios. Leaves the clock mode of the device unchanged.
        AMDX_QueryPeakClockRatio      = 7   ///< Queries the peak device clock ratios. Leaves the clock mode of the device unchanged.

    };

    /// ClockModeInfo enum defined by OpenGL driver
    typedef struct
    {
        enum AMDXClockMode clockmode;               ///< Clock mode
        float              memoryClockRatioToPeak;  ///< Ratio of current mem clock to peak clock as obtained from maxMemClock.
        float              engineClockRatioToPeak;  ///< Ratio of current gpu core clock to peak clock as obtained from maxGpuClock.
    } ClockModeInfo;

    /// ClockMode Status enum defined by OpenGL driver
    enum GL_SETCLOCK_STATUS
    {
        GL_SETCLOCK_FAIL = 0,               ///< SetClock Fails
        GL_SETCLOCK_SUCCESS,                ///< SetClock Successful
        GL_SETCLOCK_QUERY_ONLY,             ///< SetClock for Query only
        GL_SETCLOCK_INVALID_CLOCKMODE,      ///< SetClock - invalid clock mode
        GL_SETCLOCK_INVALID_CLOCKMODE_INFO  /// Undefined reference Clock Mode info
    };
}  // namespace oglUtils

#endif  // _GL_AMD_DRIVER_EXT_H_