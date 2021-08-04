//==============================================================================
// Copyright (c) 2019-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GL AMD driver extensions
//==============================================================================

#ifndef GPU_PERF_API_GL_GL_AMD_DRIVER_EXT_H_
#define GPU_PERF_API_GL_GL_AMD_DRIVER_EXT_H_

namespace ogl_utils
{
/// @brief Constant for the AMD-specific extended timer result.
#define GL_QUERY_EXTENDED_TIMER_RESULT_AMD_X 0x8870

    /// @brief ClockMode enumeration defined by OpenGL driver.
    enum AmdXClockMode
    {
        /// Device clocks and other power settings are restored to default.
        kAmdXDefaultMode = 0,

        /// Queries the current device clock ratios. Leaves the clock mode of the device unchanged.
        kAmdXQueryClockRatio = 1,

        /// Scale down from peak ratio. Clocks are set to a constant amount which is
        /// known to be power and thermal sustainable. The engine/memory clock ratio
        /// will be kept the same as much as possible.
        kAmdXProfilingClock = 2,

        /// Memory clock is set to the lowest available level. Engine clock is set to
        /// thermal and power sustainable level.
        kAmdXMinimumMemoryClock = 3,

        /// Engine clock is set to the lowest available level. Memory clock is set to
        /// thermal and power sustainable level.
        kAmdXMinimumEngineClock = 4,

        /// Clocks set to maximum when possible. Fan set to maximum. Note: Under power
        /// and thermal constraints device will clock down.
        kAmdXPeakClock = 5,

        /// Queries the profiling device clock ratios. Leaves the clock mode of the device unchanged.
        kAmdXQueryProfilingClockRatio = 6,

        /// Queries the peak device clock ratios. Leaves the clock mode of the device unchanged.
        kAmdXQueryPeakClockRatio = 7
    };

    /// @brief ClockModeInfo enumeration defined by OpenGL driver.
    typedef struct
    {
        enum AmdXClockMode clock_mode;                  ///< Clock mode.
        float              memory_clock_ratio_to_peak;  ///< Ratio of current memory clock to peak clock as obtained from maximum memory clock.
        float              engine_clock_ratio_to_peak;  ///< Ratio of current GPU core clock to peak clock as obtained from maximum GPU clock.
    } ClockModeInfo;

    /// @brief ClockMode Status enumeration defined by OpenGL driver.
    enum GlSetClockStatus
    {
        kGlSetClockFail = 0,             ///< SetClock Fails.
        kGlSetClockSuccess,              ///< SetClock Successful.
        kGlSetClockQueryOnly,            ///< SetClock for Query only.
        kGlSetClockInvalidClockMode,     ///< SetClock - invalid clock mode.
        kGlSetClockInvalidClockModeInfo  ///< Undefined reference Clock Mode info.
    };
}  // namespace ogl_utils

#endif  // GPU_PERF_API_GL_GL_AMD_DRIVER_EXT_H_