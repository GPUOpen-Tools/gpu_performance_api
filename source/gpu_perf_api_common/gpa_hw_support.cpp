//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Utility functions to determine HW counter support based on
//          GPU generation, GPU id, driver version, etc.
//==============================================================================
#include "gpa_hw_support.h"

#include "gpa_hw_info.h"
#include "logging.h"
#include "utility.h"

#include "device_info.hpp"

#include <array>
#include <algorithm>
#include <cassert>
#include <regex>
#include <string_view>
#ifdef _WIN32
#include <Windows.h>
#endif

namespace
{
#ifdef _WIN32
    GpaDriverInfo QueryRegistryForDriverVersion()
    {
        constexpr size_t                    version_length = 256;
        std::array<wchar_t, version_length> value          = {};
        DWORD                               value_length   = version_length;

        constexpr const wchar_t* folder = L"SOFTWARE\\ATI Technologies\\Install";
        constexpr const wchar_t* file   = L"ReleaseVersion";

        GpaDriverInfo driver_info = {};

        // Look for the registry variable with the version numbers.
        const LSTATUS status = RegGetValueW(HKEY_LOCAL_MACHINE, folder, file, REG_SZ, nullptr, value.data(), &value_length);
        if (status == ERROR_FILE_NOT_FOUND)
        {
            GpaLogger::Instance().LogError("Location of registry variable with GPU driver version was not found");
            assert(driver_info.driver_type == kIgnoreDriver);
            return driver_info;
        }

        // Make sure the registry string is null-terminated.
        value.back() = L'\0';

        // Driver version string changes depending on how the driver is installed.
        // When you install the public drivers it looks like: 25.10.25.01-250724a-417878C-AMD-Software-Adrenalin-Edition
        // When you install test drivers it looks like: 25.30-250926n-419617E-ATI
        const std::wstring driver_ver_str(value.data());

        // This regex only requires the major/minor version.
        const std::wregex version_regex(LR"((\d+)\.(\d+)(?:\.(\d+))?)");

        std::wsmatch match;

        if (std::regex_search(driver_ver_str, match, version_regex))
        {
            driver_info.major = std::stoul(match[1].str());
            driver_info.minor = std::stoul(match[2].str());

            // Update version is optional.
            if (match.size() > 3 && match[3].matched)
            {
                driver_info.update = std::stoul(match[3].str());
            }

            driver_info.driver_type = kAmdProprietaryDriver;
        }
        else
        {
            constexpr const char* err_message = "Registry variable value with GPU driver version is not in expected format!";
            assert(!err_message);
            assert(driver_info.driver_type == kIgnoreDriver);
            GpaLogger::Instance().LogError("{}", err_message);
        }

        return driver_info;
    }
#endif
}  // namespace

GpaDriverInfo GpaQueryDriverInfo()
{
#ifdef _WIN32
    static const GpaDriverInfo info = QueryRegistryForDriverVersion();
#else
    constexpr GpaDriverInfo info = {};
    static_assert(info.driver_type == kIgnoreDriver);
#endif
    return info;
}

GpaContextSampleTypeFlags CalculateSupportedSampleTypes(const device_info::AdapterId& adapter_id, const GpaApiType api, const GpaDriverInfo& driver_info)
{
    // By default assume everything works.
    // Flags will be removed as appropriate.
    GpaContextSampleTypeFlags flags = kGpaContextSampleTypeDiscreteCounter | kGpaContextSampleTypeStreamingCounter | kGpaContextSampleTypeSqtt;

    // All APIs besides DX12 only support Discrete Counters at the moment.
    if (api != kGpaApiDirectx12)
    {
        flags &= ~kGpaContextSampleTypeStreamingCounter;
        flags &= ~kGpaContextSampleTypeSqtt;
    }

    const std::optional<device_info::CardInfo> card_info = device_info::GetCardInfo(adapter_id);

    // The function call will validate the vendor_id, device_id, revision_id, and get the hw generation.
    if (!card_info.has_value())
    {
        return 0;
    }

    if (!IsHardwareGenerationSupported(card_info->generation) || !IsDeviceStable(adapter_id))
    {
        return 0;
    }

    // Phoenix doesn't currently have Stable Power State functionality.
    const bool is_phoenix = (adapter_id.device_id == 0x15BF || adapter_id.device_id == 0x15C8);
    if (is_phoenix)
    {
        // Do not enable SPM on Gfx11_0_3 (Phoenix/Phoenix2)
        // SPM data comes back, but the values do not appear to be correct. ie: this leads to incorrect WaveDistribution, L0CacheHit, and L1CacheHit graphs.
        flags &= ~kGpaContextSampleTypeStreamingCounter;
        // Do not enable SQTT on Gfx11_0_3 (Phoenix/Phoenix2)
        flags &= ~kGpaContextSampleTypeSqtt;
    }

#ifdef _WIN32
    if (driver_info.driver_type == kAmdProprietaryDriver)
    {
        // 19.30 is the min driver version for Windows.
        {
            constexpr GpaUInt32 kMinMajorVersion = 19;
            constexpr GpaUInt32 kMinMinorVersion = 30;

            if (driver_info.major < kMinMajorVersion || (driver_info.major == kMinMajorVersion && driver_info.minor < kMinMinorVersion))
            {
                GpaLogger::Instance().LogError("Driver is too old. Update to at least 19.30!");
                return 0;
            }
        }

        // Phoenix is not supported at all until 22.40
        if (is_phoenix)
        {
            if (driver_info.major < 22 || (driver_info.major == 22 && driver_info.minor <= 40))
            {
                GpaLogger::Instance().LogError("The current driver does not support GPUPerfAPI on this hardware, please update to a newer driver.");
                return 0;
            }
        }

        if (card_info->generation == device_info::HwGeneration::kGfx11 || card_info->generation == device_info::HwGeneration::kGfx11_5)
        {
            // The 23.10 driver fixed a lot of the issues that GPA/PIX was experiencing with SPM on GFX11/GFX115
            if (driver_info.major < 23 || (driver_info.major == 23 && driver_info.minor < 10))
            {
                GpaLogger::Instance().LogError("The current driver does not support SPM on this hardware, please update to newer driver.");
                flags &= ~kGpaContextSampleTypeStreamingCounter;
            }
        }
    }
#endif

    // Check if SPM is supported
    {
        constexpr auto kUnsupportedSpmDevices = std::to_array<GpaUInt32>({
            // Do not enable SPM on Navi24 due to GPO. GPO is also using SPM and causes TDRs.
            0x7420,
            0x7422,
            0x743F,
            0x7421,
            0x7423,
            // Do not enable SPM on Navi22 due to GPO. GPO is also using SPM and causes TDRs.
            0x73C0,
            0x73C1,
            0x73C3,
            0x73DF,
            // Do not enable SPM on Gfx10_3_3 because it does not properly support SPM.
            0x163f,
            // Do not enable SPM on Gfx10_3_5 because it does not properly support SPM.
            0x164D,
            0x1681,
            // These GFX11_0_3 HawkPoint devices are variants of Phoenix that should support SQTT, but not support SPM.
            0x1900,
            0x1901,
        });

        const bool found = std::ranges::find(kUnsupportedSpmDevices, adapter_id.device_id) != kUnsupportedSpmDevices.end();
        if (found)
        {
            flags &= ~kGpaContextSampleTypeStreamingCounter;
        }
    }

#ifdef _WIN32
    // Allow the user to force enable via environment variables for DX12 only.
    if (api == kGpaApiDirectx12)
    {
        if (gpa_util::IsEnvVarForceEnabled("AMD_GPA_ENABLE_SPM"))
        {
            GpaLogger::Instance().LogMessage("SPM has been force enabled via environment variable.");
            flags |= kGpaContextSampleTypeStreamingCounter;
        }

        if (gpa_util::IsEnvVarForceEnabled("AMD_GPA_ENABLE_SQTT"))
        {
            GpaLogger::Instance().LogMessage("SQTT has been force enabled via environment variable.");
            flags |= kGpaContextSampleTypeSqtt;
        }
    }
#endif

    return flags;
}
