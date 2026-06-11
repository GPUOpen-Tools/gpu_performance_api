//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Helper functions for Counter Generator Unit Tests.
//==============================================================================

#ifndef GPU_PERF_API_UNIT_TESTS_COUNTER_GENERATOR_TESTS_H_
#define GPU_PERF_API_UNIT_TESTS_COUNTER_GENERATOR_TESTS_H_

#ifdef _WIN32
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

#include <array>
#include <algorithm>
#include <optional>
#include <span>
#include <gtest/gtest.h>

#include "gpu_performance_api/gpu_perf_api.h"
#include "gpu_performance_api/gpu_perf_api_counters.h"
#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_common/gpa_hw_info.h"
#include "gpu_perf_api_common/gpa_hw_support.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator.h"

#include "gpu_perf_api_unit_tests/counters/gpa_counter_desc.h"

constexpr uint32_t kDevIdUnknown      = 0xFFFFFFFF;  ///< bogus device id.
constexpr uint32_t kDevIdSI           = 0x6798;      ///< 7970 Series.
constexpr uint32_t kDevIdCI           = 0x6649;      ///< FirePro W5100.
constexpr uint32_t kDevIdCIHawaii     = 0x67A0;      ///< HAWAII XTGL.
constexpr uint32_t kDevIdVI           = 0x98E4;      ///< VI (Gfx8 Stoney).
constexpr uint32_t kDevIdGfx8         = kDevIdVI;    ///< Gfx8 (Stoney).
constexpr uint32_t kDevIdGfx8Tonga    = 0x6920;      ///< Gfx8 Tonga.
constexpr uint32_t kDevIdGfx8Iceland  = 0x6900;      ///< Gfx8 R7 M260 (Iceland).
constexpr uint32_t kDevIdGfx9         = 0x6863;      ///< Gfx9.
constexpr uint32_t kDevIdMi250X       = 0x740C;      ///< GFX9_0_A (MI250X).
constexpr uint32_t kDevIdMi210        = 0x740F;      ///< GFX9_0_A (MI210).
constexpr uint32_t kDevIdMi300X       = 0x74A1;      ///< GDT_GFX9_4_2 (MI300)
constexpr uint32_t kDevIdMi300XHF     = 0x74A9;      ///< GDT_GFX9_4_2 (MI300XHF)
constexpr uint32_t kDevIdUnsupported1 = 0x1506;      ///< An unsupported device id.
constexpr uint32_t kDevIdUnsupported2 = 0x164e;      ///< An unsupported device id.
constexpr uint32_t kDevIdUnsupported3 = 0x13C0;      ///< An unsupported device id.

inline constexpr std::array kUnsupportedDeviceIds = {
    kDevIdUnknown,
    kDevIdSI,
    kDevIdCI,
    kDevIdCIHawaii,
    kDevIdVI,
    kDevIdGfx8,
    kDevIdGfx8Tonga,
    kDevIdGfx8Iceland,
    kDevIdGfx9,
    kDevIdMi250X,
    kDevIdMi210,
    kDevIdMi300X,
    kDevIdMi300XHF,
    kDevIdUnsupported1,
    kDevIdUnsupported2,
    kDevIdUnsupported3,
};

constexpr GpaUInt32 kVendorIdNvidia   = 0x10DE;  ///< NVIDIA vendor ID
constexpr GpaUInt32 kVendorIdIntel    = 0x8086;  ///< Intel vendor ID
constexpr GpaUInt32 kQualcommVendorId = 0x5143;  ///< Qualcomm vendor ID

inline constexpr std::array kUnsupportedVendorIds = {kVendorIdNvidia, kVendorIdIntel, kQualcommVendorId, 0U, 0xFFFFFFFFU};

constexpr uint32_t kDevIdGfx10       = 0x7310;  ///< Gfx10.
constexpr uint32_t kDevIdGfx10_3     = 0x73A0;  ///< Gfx10_3.
constexpr uint32_t kDevIdGfx10_3_1   = 0x73DF;  ///< Gfx10_3_1.
constexpr uint32_t kDevIdGfx10_3_3   = 0x163f;  ///< Gfx10_3_3.
constexpr uint32_t kDevIdGfx10_3_4   = 0x743F;  ///< Gfx10_3_4.
constexpr uint32_t kDevIdGfx10_3_5   = 0x164D;  ///< Gfx10_3_5.
constexpr uint32_t kDevIdGfx11       = 0x744C;  ///< Gfx11.
constexpr uint32_t kDevIdGfx11_0_1   = 0x73C8;  ///< Gfx11_0_1.
constexpr uint32_t kDevIdGfx11_0_2   = 0x7480;  ///< Gfx11_0_2.
constexpr uint32_t kDevIdGfx11_0_3   = 0x15BF;  ///< Gfx11_0_3.
constexpr uint32_t kDevIdGfx11_0_3B  = 0x15C8;  ///< Gfx11_0_3B.
constexpr uint32_t kDevIdGfx11_0_3H  = 0x1900;  ///< Gfx11_0_3.
constexpr uint32_t kDevIdGfx11_0_3H2 = 0x1901;  ///< Gfx11_0_3.
constexpr uint32_t kDevIdGfx11_5_0   = 0x150E;  ///< GFX11_5_0.
constexpr uint32_t kDevIdGfx11_5_1   = 0x1586;  ///< GFX11_5_1.
constexpr uint32_t kDevIdGfx11_5_2   = 0x1114;  ///< GFX11_5_2.
constexpr uint32_t kDevIdGfx11_5_3   = 0x1902;  ///< GFX11_5_3.
constexpr uint32_t kDevIdGfx12_0_0 = 0x7590;  ///< GFX12_0_0.
constexpr uint32_t kDevIdGfx12_0_1 = 0x7550;  ///< GFX12_0_1.

inline constexpr std::array kSupportedDeviceIds = {
    kDevIdGfx10,     kDevIdGfx10_3,    kDevIdGfx10_3_1,  kDevIdGfx10_3_3,   kDevIdGfx10_3_4, kDevIdGfx10_3_5, kDevIdGfx11,     kDevIdGfx11_0_1, kDevIdGfx11_0_2,
    kDevIdGfx11_0_3, kDevIdGfx11_0_3B, kDevIdGfx11_0_3H, kDevIdGfx11_0_3H2, kDevIdGfx11_5_0, kDevIdGfx11_5_1, kDevIdGfx11_5_2, kDevIdGfx11_5_3,
    kDevIdGfx12_0_0, kDevIdGfx12_0_1,
};

static_assert(std::ranges::none_of(kSupportedDeviceIds,
                                   [](uint32_t id) { return std::ranges::find(kUnsupportedDeviceIds, id) != kUnsupportedDeviceIds.end(); }),
              "A supported device ID is also listed as unsupported.");

inline constexpr std::array kUnsupportedHardwareGenerations = {
    kGpaHwGenerationNone,
    kGpaHwGenerationNvidia,
    kGpaHwGenerationIntel,
    kGpaHwGenerationGfx6,
    kGpaHwGenerationGfx7,
    kGpaHwGenerationGfx8,
    kGpaHwGenerationGfx9,
    kGpaHwGenerationCdna,
    kGpaHwGenerationCdna2,
    kGpaHwGenerationCdna3,
    kGpaHwGenerationCdna4,
};

static_assert(kSupportedGenerations.size() + kUnsupportedHardwareGenerations.size() == static_cast<size_t>(kGpaHwGenerationLast),
              "The number of supported and unsupported hardware generations should equal the total number of hardware generations.");

/// @brief RAII wrapper for LibHandle that unloads the library on destruction.
class LibHandleGuard
{
public:
    explicit LibHandleGuard(LibHandle h)
        : handle_(h)
    {
        if (handle_ == nullptr) [[unlikely]]
        {
            throw std::runtime_error("Tried to create LibHandleGuard with a null handle.");
        }
    }

    LibHandleGuard(const LibHandleGuard&)            = delete;
    LibHandleGuard& operator=(const LibHandleGuard&) = delete;

    LibHandleGuard(LibHandleGuard&& other) noexcept
        : handle_(other.handle_)
    {
        other.handle_ = nullptr;
    }

    LibHandleGuard& operator=(LibHandleGuard&& other) noexcept
    {
        if (this != &other)
        {
            Reset();
            handle_       = other.handle_;
            other.handle_ = nullptr;
        }
        return *this;
    }

    ~LibHandleGuard()
    {
        Reset();
    }

    void Reset();

    explicit operator bool() const
    {
        return handle_ != nullptr;
    }

private:
    LibHandle handle_ = nullptr;
};

/// @brief Loads the GPUPerfAPICounterLib and populates the function table.
///
/// The returned LibHandleGuard automatically unloads the library when destroyed.
///
/// @param [out] fn_table The populated function table.
///
/// @return A LibHandleGuard wrapping the loaded library, or an empty guard on failure.
[[nodiscard]] std::optional<LibHandleGuard> LoadAndVerifyCounterLib(void* fn_table);

/// @brief Get an entrypoint within a library.
///
/// @param [in] lib_handle The handle of the loaded library.
/// @param [in] entry_point_name The name of the entrypoint.
///
/// @return Function pointer to the loaded entrypoint.
void* GetEntryPoint(LibHandle lib_handle, const char* entrypoint_name);

/// Verifies the internal counter count.
///
/// @param [in] api The API being used in the test.
/// @param [in] generation The hardware generation being used.
/// @param [in] public_counters Public descriptions of the counter.
void VerifyDerivedCounterCount(const GpaApiType api, const GpaHwGeneration generation, const gpa_array_view<GpaCounterDesc> counter_descriptions);

void VerifyInvalidOpenContextParameters(GpaApiType api, uint32_t device_id);

void VerifyHardwareNotSupported(GpaApiType api, uint32_t device_id);

void VerifyHardwareNotSupported(GpaApiType api, GpaHwGeneration generation);

void VerifySupportedSampleTypes(GpaApiType api);

void VerifyCounterNames(GpaApiType                      api,
                        uint32_t                        device_id,
                        const std::vector<const char*>& expected_names,
                        const std::vector<const char*>& expected_hardware_names);

void VerifyCounterNames(GpaApiType                      api,
                        GpaHwGeneration                 generation,
                        const std::vector<const char*>& expected_names,
                        const std::vector<const char*>& expected_hardware_names);

void VerifyOpenCounterContext(GpaApiType api, GpaHwGeneration generation);

/// @brief Calls VerifyOpenCounterContext for every generation in kSupportedGenerations.
///
/// Zero-maintenance: adding a new generation to kSupportedGenerations automatically
/// exercises it here without touching individual API test files.
inline void VerifyOpenCounterContextAllGenerations(GpaApiType api)
{
    for (const device_info::HwGeneration gen : kSupportedGenerations)
    {
        VerifyOpenCounterContext(api, ConvertDeviceInfoHwGenerationToGpaHwGeneration(gen));
    }
}

void VerifyCounterLibInterface(GpaApiType api, uint32_t device_id, uint32_t revision_id);

void VerifyCounterByPassCounterLibEntry(GpaApiType api, uint32_t device_id, uint32_t revision_id);

template <GpaSessionSampleType SampleType>
[[nodiscard]] GpaUInt32 GetPassCount(GpaApiType api, uint32_t device_id, std::span<const uint32_t> counters_to_enable)
{
    GpaUInt32              pass_count = 0u;
    GpaCounterLibFuncTable fn_table   = {};
    auto                   lib_guard  = LoadAndVerifyCounterLib(&fn_table);
    if (lib_guard)
    {
        GpaCounterContext             gpa_counter_context           = nullptr;
        GpaCounterContextHardwareInfo counter_context_hardware_info = {device_info::kAmdVendorId, device_id, device_info::kRevisionIdAny, nullptr, 0};
        GpaStatus                     gpa_status =
            fn_table.GpaCounterLibOpenCounterContext(api, SampleType, counter_context_hardware_info, kGpaOpenContextDefaultBit, &gpa_counter_context);
        EXPECT_EQ(kGpaStatusOk, gpa_status);

        if (gpa_status == kGpaStatusOk)
        {
            gpa_status = fn_table.GpaCounterLibGetPassCount(
                gpa_counter_context, counters_to_enable.data(), static_cast<GpaUInt32>(counters_to_enable.size()), &pass_count);
            EXPECT_EQ(kGpaStatusOk, gpa_status);

            gpa_status = fn_table.GpaCounterLibCloseCounterContext(gpa_counter_context);
            EXPECT_EQ(kGpaStatusOk, gpa_status);
        }
    }

    return pass_count;
}

/// @brief Verifies the number of passes, the counters in each pass, and the internal consistency of the expected
/// result-location mapping with the expected per-pass schedule.
///
/// @param [in] api The API being used in the test.
/// @param [in] device_id The hardware being used.
/// @param [in] counters_to_enable The list of exposed counters being tested.
/// @param [in] expected_hw_counters_per_pass A list of counters in each pass (list of lists).
/// @param [in] expected_result_location A list of maps describing the expected result locations for each counter.
void VerifyCountersInPass(GpaApiType                                                              api,
                          uint32_t                                                                device_id,
                          const std::vector<uint32_t>&                                            counters_to_enable,
                          const std::vector<std::vector<uint32_t>>&                               expected_hw_counters_per_pass,
                          const std::map<uint32_t, std::map<uint32_t, GpaCounterResultLocation>>& expected_result_location);

/// @brief Verifies the counter calculation.
///
/// @param [in] public_counters Public descriptions of the counter
void VerifyCounterFormula(const gpa_array_view<GpaCounterDesc> public_counters);

/// @brief Verifies the counter calculation.
///
/// @param [in] api The API being used in the test
/// @param [in] device_id The hardware being used
/// @param [in] counter_name Name of the counter
/// @param [in] sample_results List of sample results
///
/// @return The result of derived counter calculation.
[[nodiscard]] GpaFloat64 GetCounterCalculation(GpaApiType api, uint32_t device_id, const char* counter_name, std::span<const GpaUInt64> sample_results);

#endif
