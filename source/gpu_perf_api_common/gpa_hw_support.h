//==============================================================================
// Copyright (c) 2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Helper functions to determine HW support and features.
//==============================================================================
#ifndef GPA_HW_SUPPORT
#define GPA_HW_SUPPORT

#include "gpu_performance_api/gpu_perf_api_counters.h"
#include "gpu_performance_api/gpu_perf_api_types.h"

class GpaHwInfo;

/// @brief Returns the appropriate driver information if possible. Check the driver_type before using.
///
/// @return The driver version + type of driver.
[[nodiscard]] GpaDriverInfo QueryDriverInfo();

/// @brief Used to calculate supported sample types for a given AMD GPU
///
/// @param [in] device_id        The ID of the device to check
/// @param [in] api              The graphics API being used
/// @param [in] driver_version   The driver version for the device
///
/// @return Returns the supported sample types for a given GPU given all the aforementioned context.
[[nodiscard]] GpaContextSampleTypeFlags CalculateSupportedSampleTypes(const GpaUInt32      device_id,
                                                                      const GpaUInt32      revision_id,
                                                                      const GpaApiType     api,
                                                                      const GpaDriverInfo& driver_info);

/// @brief Checks if an AMD device is not suitable for GPA profiling
///
/// @param [in] device_id        The ID of the device to check
/// @param [in] api              The graphics API being used
/// @param [in] driver_version   The driver version for the device
///
/// @return True if the device does not support any sample types (i.e., cannot be use for perf analysis)
[[nodiscard]] inline bool IsDeviceUnprofilable(const GpaUInt32 device_id, const GpaUInt32 revision_id, const GpaApiType api, const GpaDriverInfo& driver_info)
{
    const GpaContextSampleTypeFlags supported_sample_types = CalculateSupportedSampleTypes(device_id, revision_id, api, driver_info);

    // If no sample types are supported, the device is unprofilable.
    return supported_sample_types == 0;
}

#endif
