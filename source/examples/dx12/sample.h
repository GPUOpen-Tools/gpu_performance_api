//==============================================================================
// Copyright (c) 2019-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Sample implementation.
//==============================================================================

#ifndef GPU_PERF_API_EXAMPLES_DX12_SAMPLE_H_
#define GPU_PERF_API_EXAMPLES_DX12_SAMPLE_H_

#include <string>

/// @brief Struct to hold values of command line arguments.
struct CommandLineArgs
{
    /// Flag indicating if GPU should be used to collect performance counters.
    bool use_gpa = true;

    /// Number of frames to execute -- zero indicates that the app should run until the user closes it.
    unsigned int num_frames = 0;

    /// Flag indicating if the bundles created by the application should be profiled.
    /// Starting with the Adrenaline 19.1.1 driver, profiling bundles is no longer supported.
    bool profile_bundles = false;

    /// Flag indicating if some counter values should be verified (experimental).
    bool verify_counters = false;

    /// Flag indicating whether the application should verify some counter values and confirm successful results.
    bool confirm_success = false;

    /// Flag indicating whether or not to include hardware counters in non-internal builds.
    bool include_hw_counters = false;

    /// Flag indicating whether the counter file is given or not.
    bool counter_provided = false;

    /// Counter file name.
    std::string counter_file_name;
};

/// Command line arguments.
extern CommandLineArgs args;

#endif GPU_PERF_API_EXAMPLES_DX12_SAMPLE_H_