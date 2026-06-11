//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  A class for managing hardware information.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_HW_INFO_H_
#define GPU_PERF_API_COMMON_GPA_HW_INFO_H_

#include <algorithm>
#include <optional>
#include <string>
#include <vector>

#include "device_info.hpp"

#include "gpu_performance_api/gpu_perf_api_types.h"
#include "gpu_performance_api/gpu_perf_api_counters.h"

/// @brief Stores information about the hardware installed in the machine.
class GpaHwInfo
{
public:
    /// @brief Default constructor.
    GpaHwInfo() = default;

    /// @brief Destructor.
    ~GpaHwInfo() = default;

    /// @brief Sets the revision ID.
    ///
    /// @param id The revision ID of the available device.
    void SetRevisionId(const GpaUInt32& id);

    /// @brief Sets the device ID.
    ///
    /// @param [in] id The ID of the available device.
    void SetDeviceId(const GpaUInt32& id);

    /// @brief Sets the vendor ID.
    ///
    /// @param [in] vendor_id The vendor ID of the available device.
    void SetVendorId(const GpaUInt32& vendor_id);

    /// @brief Sets the hardware generation that the device belongs to.
    ///
    /// @param [in] generation The hardware generation.
    void SetHwGeneration(device_info::HwGeneration generation)
    {
        generation_ = generation;
    }

    /// Sets the device name
    ///
    /// @param [in] device_name A name of the device (ie "ATI Radeon HD 2600 series").
    void SetDeviceName(const char* device_name);

    /// @brief Set the GPU index of the GPU in the system.
    ///
    /// @param [in] gpu_index The GPU index in the system.
    void SetGpuIndex(const unsigned int& gpu_index);

    /// @brief Sets the frequency of the clock that the timestamps are based on.
    ///
    /// @param [in] frequency The timestamp clock frequency.
    void SetTimeStampFrequency(const GpaUInt64& frequency);

    /// @brief Sets the number of SIMDs.
    ///
    /// @param [in] num_simd The number of SIMDs.
    void SetNumberSimds(const GpaUInt32 num_simd);

    /// @brief Sets the number of compute units.
    ///
    /// @param [in] num_cu The number of compute units.
    void SetNumberCus(const GpaUInt32 num_cu);

    /// @brief Sets the number of waves per SIMD.
    ///
    /// @param [in] numWaves The number of waves per SIMD.
    void SetWavesPerSimd(const GpaUInt32 numWaves);

    /// @brief Sets the number of shader engines.
    ///
    /// @param [in] num_se The number of shader engines.
    void SetNumberShaderEngines(const GpaUInt32 num_se);

    /// @brief Sets the number of shader arrays.
    ///
    /// @param [in] num_sa The number of shader arrays.
    void SetNumberShaderArrays(const GpaUInt32 num_sa);

    /// @brief Sets the SU clock primitives.
    ///
    /// @param [in] su_clock_primitives The number of SU clock primitives.
    void SetSuClocksPrim(const GpaUInt32 su_clock_primitives);

    /// @brief Sets the number of primitive pipes.
    ///
    /// @param [in] num_primitive_pipes The number of primitive pipes.
    void SetNumberPrimPipes(const GpaUInt32 num_primitive_pipes);

    /// @brief Sets the number of VGPRs.
    ///
    /// @param [in] num_vgpr The number of VGPRs.
    void SetNumberVgprs(const GpaUInt32 num_vgpr);

    /// @brief Gets the number of shader engines.
    ///
    /// @return The number of shader engines.
    [[nodiscard]] GpaUInt32 GetNumberShaderEngines() const
    {
        return num_shader_engines_;
    }

    /// @brief Gets the number of shader arrays.
    ///
    /// @return The number of shader arrays.
    [[nodiscard]] GpaUInt32 GetNumberShaderArrays() const
    {
        return num_shader_arrays_;
    }

    /// @brief Gets the number of SIMDs.
    ///
    /// @return The number of SIMDs.
    [[nodiscard]] GpaUInt32 GetNumberSimds() const
    {
        return num_simd_;
    }

    /// @brief Gets the number of Compute Units.
    ///
    /// @return The number of Compute Units.
    [[nodiscard]] GpaUInt32 GetNumberCus() const
    {
        return num_cu_;
    }

    /// @brief Gets the max number of waves per SIMD.
    ///
    /// @return the number of waves per SIMD.
    [[nodiscard]] GpaUInt32 GetWavesPerSimd() const
    {
        return num_waves_per_simd_;
    }

    /// @brief Calculate the max wave slots
    ///
    /// @return The maximum number of wave slots
    [[nodiscard]] GpaUInt32 GetMaxWaveSlots() const
    {
        return num_simd_ * num_waves_per_simd_;
    }

    /// @brief Gets the max number of VGPRs.
    ///
    /// @return The number of VGPRs.
    [[nodiscard]] GpaUInt32 GetTotalVgprs() const
    {
        return num_vgpr_;
    }

    /// @brief Gets the total size of LDS memory on the GPU
    ///
    /// @return The number of LDS bytes
    [[nodiscard]] std::optional<GpaUInt32> GetTotalLdsBytes() const
    {
        return num_lds_bytes_;
    }

    /// @brief Gets the max number of SQ counters.
    ///
    /// @return The number of SQ counters. Will never be 0, but may be std::nullopt if the information is not available.
    [[nodiscard]] std::optional<uint8_t> GetMaxSqCounters() const
    {
        return max_sq_counters_;
    }

    /// @brief Gets the hardware generation.
    ///
    /// @return The hardware generation.
    [[nodiscard]] std::optional<device_info::HwGeneration> GetHwGeneration() const
    {
        return generation_;
    }

    /// @brief Gets the ASIC type.
    ///
    /// @return The ASIC type.
    [[nodiscard]] std::optional<device_info::AsicType> GetHwAsicType() const
    {
        return asic_type_;
    }

    /// @brief Gets the number of clocks per primitive.
    ///
    /// @return The number of clocks per primitive.
    [[nodiscard]] GpaUInt32 GetSuClocksPrim() const
    {
        return su_clock_prim_;
    }

    /// @brief Gets the number of primitive pipes.
    ///
    /// @return The number of primitive pipes.
    [[nodiscard]] GpaUInt32 GetNumberPrimPipes() const
    {
        return num_prim_pipes_;
    }

    [[nodiscard]] std::optional<device_info::AdapterId> GetDeviceDescription() const
    {
        if (device_id_set_ && vendor_id_set_ && revision_id_set_)
        {
            return device_info::AdapterId{.vendor_id = vendor_id_, .device_id = device_id_, .revision_id = revision_id_};
        }
        return std::nullopt;
    }

    /// @brief Gets the revision ID.
    ///
    /// @param [out] id The revision ID.
    ///
    /// @return True if the revision ID is available; false otherwise.
    [[nodiscard]] bool GetRevisionId(GpaUInt32& id) const;

    /// @brief Gets the device ID.
    ///
    /// @param [out] id The device ID.
    ///
    /// @return True if the device ID is available; false otherwise.
    [[nodiscard]] bool GetDeviceId(GpaUInt32& id) const;

    /// @brief Checks if the current card is unsupported based on the device ID and graphics API.
    ///
    /// @param [in] api The API being used.
    ///
    /// @return True if the current device is unsupported.
    [[nodiscard]] bool IsUnsupportedDevice(const GpaApiType api, GpaDriverInfo const& driver_info) const;

    /// @brief Gets the vendor ID.
    ///
    /// @param [out] vendor_id The vendor ID.
    ///
    /// @return True if the vendor ID is available; false otherwise.
    [[nodiscard]] bool GetVendorId(GpaUInt32& vendor_id) const;

    /// @brief Gets the device name.
    ///
    /// @param [out] device_name The device name.
    ///
    /// @return True if the device name is available; false otherwise.
    [[nodiscard]] bool GetDeviceName(const char*& device_name) const;

    /// @brief Get the GPU index in the system.
    ///
    /// @param [out] gpu_index The GPU index in the system.
    ///
    /// @return True if the gpu index is available, false otherwise.
    [[nodiscard]] bool GetGpuIndex(unsigned int& gpu_index) const;

    /// @brief Gets the ASIC type.
    ///
    /// @param [out] type The ASIC type.
    ///
    /// @return True if the ASIC type is available; false otherwise.
    [[nodiscard]] bool GetHwAsicType(device_info::AsicType& type) const;

    /// @brief Gets the timestamp clock frequency.
    ///
    /// @param [out] timestamp_frequency timestamp frequency.
    ///
    /// @return The clock frequency.
    [[nodiscard]] bool GetTimeStampFrequency(GpaUInt64& timestamp_frequency) const
    {
        timestamp_frequency = timestamp_frequency_;
        return timestamp_frequency_set_;
    }

    /// @brief Uses the DeviceId to find the correct DeviceMapping and DeviceInfo.
    ///
    /// Sets devInfo and sets DeviceName and HWGeneration if not previously set.
    ///
    /// @return True if HW should be supported and information is obtained correctly.
    [[nodiscard]] bool UpdateDeviceInfoBasedOnDeviceDescription();

    /// @brief Check if the current hardware is AMD hardware.
    ///
    /// @return True if the current hardware is AMD hardware.
    [[nodiscard]] bool IsAmd() const
    {
        return vendor_id_set_ && device_info::kAmdVendorId == vendor_id_;
    };

private:
    GpaUInt32 device_id_     = {};  ///< The device ID.
    bool      device_id_set_ = {};  ///< Indicates if the Device ID has been set.

    GpaUInt32 revision_id_     = {};  ///< The revision ID.
    bool      revision_id_set_ = {};  ///< Indicates if the Revision ID has been set.

    GpaUInt32 vendor_id_     = {};  ///< The vendor ID.
    bool      vendor_id_set_ = {};  ///< Indicates if the vendor ID has been set.

    std::string device_name_     = {};  ///< The device name.
    bool        device_name_set_ = {};  ///< Indicates if the device name has been set.

    GpaUInt32 gpu_index_     = {};  ///< Index of the GPU in the system.
    bool      gpu_index_set_ = {};  ///< Indicates the GPU index has been set.

    GpaUInt64 timestamp_frequency_     = 1;   ///< The frequency of the time stamp clock.
    bool      timestamp_frequency_set_ = {};  ///< Indicates if the timestamp frequency has been set.

    GpaUInt32 num_simd_     = {};  ///< Number of SIMDs.
    bool      num_simd_set_ = {};  ///< Indicates if the number of SIMDs has been set.

    GpaUInt32 num_cu_     = {};  ///< Number of Compute Units.
    bool      num_cu_set_ = {};  ///< Indicates if the Compute Units has been set.

    GpaUInt32 num_waves_per_simd_     = {};  ///< Maximum number of waves per SIMD.
    bool      num_waves_per_simd_set_ = {};  ///< Indicates the WavesPerSimd has been set.

    GpaUInt32 num_shader_engines_     = {};  ///< Number of shader engines.
    bool      num_shader_engines_set_ = {};  ///< Indicates if the shader engines has been set.

    GpaUInt32 num_shader_arrays_     = {};  ///< Number of shader arrays.
    bool      num_shader_arrays_set_ = {};  ///< Indicates if the shader engines has been set.

    GpaUInt32 su_clock_prim_     = {};  ///< Number of clocks it takes to process a primitive.
    bool      su_clock_prim_set_ = {};  ///< Indicates whether the SU Clock prim is set or not.

    GpaUInt32 num_prim_pipes_     = {};  ///< Number of primitive pipes.
    bool      num_prim_pipes_set_ = {};  ///< Indicates whether primitive pipes is set or not.

    GpaUInt32 num_vgpr_     = {};  ///< Maximum number of VGPRs.
    bool      num_vgpr_set_ = {};  ///< Indicates the number of VGPRs has been set.

    std::optional<GpaUInt32> num_lds_bytes_;  ///< Amount of LDS memory available

    std::optional<uint8_t> max_sq_counters_;  ///< Max number of SQ counters, used for counter scheduling.

    std::optional<device_info::AsicType> asic_type_;  ///< Indicates the ASIC type of this device.

    std::optional<device_info::HwGeneration> generation_;  ///< The hardware generation of the device.
};

#endif
