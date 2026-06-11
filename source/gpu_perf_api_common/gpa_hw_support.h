//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Helper functions to determine HW support and features.
//==============================================================================
#ifndef GPU_PERF_API_COMMON_GPA_HW_SUPPORT_H_
#define GPU_PERF_API_COMMON_GPA_HW_SUPPORT_H_

#include <array>
#include <algorithm>

#include "gpu_performance_api/gpu_perf_api_counters.h"
#include "gpu_performance_api/gpu_perf_api_types.h"

#include "device_info.hpp"

// Checks if an AMD device is stable and supports stable power state.
constexpr bool IsDeviceStable(const device_info::AdapterId& adapter_id)
{
    // These are AMD devices
    if (adapter_id.vendor_id != device_info::kAmdVendorId)
    {
        return false;
    }

    // These devices are APUs that do not support stable power state for profiling
    // therefore they do not properly support GPA, and GPA will not support them.
    // They need to be explicitly handled in the common case that there is also a discrete GPU in the system,
    // and GPA needs to avoid reporting an error about these unsupported devices.
    constexpr auto kUnsupportedDevices = std::to_array<uint32_t>({0x1506, 0x164e, 0x13c0});

    return std::ranges::find(kUnsupportedDevices, adapter_id.device_id) == kUnsupportedDevices.end();
}

// We can update kGpaHwGenerationNone whenever we want since it's not part of the public API.
// But kGpaHwGeneration is part of the public API, so we need to ensure that the values remain
// unchanged to avoid an ABI break.
static_assert(kGpaHwGenerationNone == 0, "ABI break");
static_assert(kGpaHwGenerationNvidia == 1, "ABI break");  // GPA no longer supports Nvidia, but keep the value for ABI compatibility.
static_assert(kGpaHwGenerationIntel == 2, "ABI break");   // GPA no longer supports Intel, but keep the value for ABI compatibility.
static_assert(kGpaHwGenerationGfx6 == 3, "ABI break");
static_assert(kGpaHwGenerationGfx7 == 4, "ABI break");
static_assert(kGpaHwGenerationGfx8 == 5, "ABI break");
static_assert(kGpaHwGenerationGfx9 == 6, "ABI break");
static_assert(kGpaHwGenerationGfx10 == 7, "ABI break");
static_assert(kGpaHwGenerationGfx103 == 8, "ABI break");
static_assert(kGpaHwGenerationGfx11 == 9, "ABI break");
static_assert(kGpaHwGenerationCdna == 10, "ABI break");
static_assert(kGpaHwGenerationCdna2 == 11, "ABI break");
static_assert(kGpaHwGenerationCdna3 == 12, "ABI break");
static_assert(kGpaHwGenerationGfx12 == 13, "ABI break");
static_assert(kGpaHwGenerationCdna4 == 14, "ABI break");
static_assert(kGpaHwGenerationGfx115 == 15, "ABI break");

// Ensure duplicate enum values truly are the same value.
static_assert(kGpaHwGenerationSouthernIsland == kGpaHwGenerationGfx6);
static_assert(kGpaHwGenerationSeaIsland == kGpaHwGenerationGfx7);
static_assert(kGpaHwGenerationVolcanicIsland == kGpaHwGenerationGfx8);

static_assert(static_cast<uint32_t>(device_info::HwGeneration::kTotalHwGenerations) == 16,
              "device_info::HwGeneration has been extended, please update the supported generations list.");

constexpr std::array kSupportedGenerations = {
    device_info::HwGeneration::kGfx10,
    device_info::HwGeneration::kGfx10_3,
    device_info::HwGeneration::kGfx11,
    device_info::HwGeneration::kGfx11_5,
    device_info::HwGeneration::kGfx12,
};

// Helper function to determine if a hardware generation is supported by GPA.
//
// We don't support CDNA; these are MI (Machine Inferencing) devices that do not have a full graphics pipeline and are not currently supported by GPA.
// Furthermore, devices like GFX9 and older no longer have driver support and thus are not supported by GPA.
constexpr bool IsHardwareGenerationSupported(const device_info::HwGeneration gen)
{
    return std::ranges::find(kSupportedGenerations, gen) != kSupportedGenerations.end();
}

constexpr GpaHwGeneration ConvertDeviceInfoHwGenerationToGpaHwGeneration(const device_info::HwGeneration di_generation)
{
    // Compile-time validation that device_info and GPA enums match in value.
    auto Validate = []() consteval -> bool {
        constexpr std::array kDiGpaMapping = {
            std::pair{device_info::HwGeneration::kUndefinedGeneration, kGpaHwGenerationNone},
            std::pair{device_info::HwGeneration::kNvidia, kGpaHwGenerationNvidia},
            std::pair{device_info::HwGeneration::kIntel, kGpaHwGenerationIntel},
            std::pair{device_info::HwGeneration::kSouthernIsland, kGpaHwGenerationSouthernIsland},
            std::pair{device_info::HwGeneration::kSeaIsland, kGpaHwGenerationGfx7},
            std::pair{device_info::HwGeneration::kVolcanicIsland, kGpaHwGenerationGfx8},
            std::pair{device_info::HwGeneration::kGfx9, kGpaHwGenerationGfx9},
            std::pair{device_info::HwGeneration::kGfx10, kGpaHwGenerationGfx10},
            std::pair{device_info::HwGeneration::kGfx10_3, kGpaHwGenerationGfx103},
            std::pair{device_info::HwGeneration::kGfx11, kGpaHwGenerationGfx11},
            std::pair{device_info::HwGeneration::kCdna, kGpaHwGenerationCdna},
            std::pair{device_info::HwGeneration::kCdna2, kGpaHwGenerationCdna2},
            std::pair{device_info::HwGeneration::kCdna3, kGpaHwGenerationCdna3},
            std::pair{device_info::HwGeneration::kGfx12, kGpaHwGenerationGfx12},
            std::pair{device_info::HwGeneration::kCdna4, kGpaHwGenerationCdna4},
            std::pair{device_info::HwGeneration::kGfx11_5, kGpaHwGenerationGfx115},
        };
        for (const auto& [di, gpa] : kDiGpaMapping)
        {
            if (static_cast<uint64_t>(di) != static_cast<uint64_t>(gpa))
            {
                return false;
            }
        }
        return true;
    };
    static_assert(Validate(), "device_info and GPA hardware generation enums are out of sync");

    return static_cast<GpaHwGeneration>(di_generation);
}

/// @brief Returns the appropriate driver information if possible. Check the driver_type before using.
///
/// @return The driver version + type of driver.
[[nodiscard]] GpaDriverInfo GpaQueryDriverInfo();

/// @brief Used to calculate supported sample types for a given AMD GPU
///
/// @param [in] adapter_id       The adapter ID of the device to check
/// @param [in] api              The graphics API being used
/// @param [in] driver_version   The driver version for the device
///
/// @return Returns the supported sample types for a given GPU given all the aforementioned context.
[[nodiscard]] GpaContextSampleTypeFlags CalculateSupportedSampleTypes(const device_info::AdapterId& adapter_id,
                                                                      const GpaApiType              api,
                                                                      const GpaDriverInfo&          driver_info);

/// @brief Checks if an AMD device is not suitable for GPA profiling
///
/// @param [in] adapter_id       The adapter ID of the device to check
/// @param [in] api              The graphics API being used
/// @param [in] driver_version   The driver version for the device
///
/// @return True if the device does not support any sample types (i.e., cannot be use for perf analysis)
[[nodiscard]] inline bool IsDeviceUnprofilable(const device_info::AdapterId& adapter_id, const GpaApiType api, const GpaDriverInfo& driver_info)
{
    const GpaContextSampleTypeFlags supported_sample_types = CalculateSupportedSampleTypes(adapter_id, api, driver_info);

    // If no sample types are supported, the device is unprofilable.
    return supported_sample_types == 0;
}

#endif
