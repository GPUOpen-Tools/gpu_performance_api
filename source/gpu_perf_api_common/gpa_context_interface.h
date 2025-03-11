//==============================================================================
// Copyright (c) 2017-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Interface representing the GPA context.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_CONTEXT_INTERFACE_H_
#define GPU_PERF_API_COMMON_GPA_CONTEXT_INTERFACE_H_

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_counter_generator/gpa_counter_accessor_interface.h"
#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_interface.h"

#include "gpu_perf_api_common/gpa_hw_info.h"
#include "gpu_perf_api_common/gpa_interface_trait_interface.h"

class IGpaSession;

/// @brief Device clock mode enum used to decode usage of GPA_OpenContext mode flag.
enum class DeviceClockMode : uint32_t
{
    kDefault,        ///< Device clocks and other power settings are restored to default.
    kMinimumEngine,  ///< Engine clock is set to the lowest available level. Memory clock is set to thermal and power sustainable level.
    kMinimumMemory,  ///< Memory clock is set to the lowest available level. Engine clock is set to thermal and power sustainable level.
    kPeak,           ///< Clocks set to maximum when possible. Fan set to maximum. Note: Under power and thermal constraints device will clock down.
    kProfiling,  ///< Scale down from peak ratio. Clocks are set to a constant amount which is known to be power and thermal sustainable. The engine/memory clock ratio will be kept the same as much as possible.
};

/// @brief Interface for GPA Context Object.
class IGpaContext : public IGpaInterfaceTrait
{
public:
    /// @brief Virtual Destructor.
    virtual ~IGpaContext() = default;

    /// @brief Creates a session Container.
    ///
    /// @param sample_type The sample type that will be created for this session.
    ///
    /// @return GPA_Session Id object.
    virtual GpaSessionId CreateSession(GpaSessionSampleType sample_type) = 0;

    /// @brief Deletes a session and its associated counter data.
    ///
    /// @param [in] session_id Pointer to previously created session object.
    ///
    /// @return True if operation is successful otherwise false.
    virtual bool DeleteSession(GpaSessionId session_id) = 0;

    /// @brief Returns the maximum number of sessions possible in the context.
    ///
    /// @return Maximum number of possible sessions.
    virtual GpaUInt32 GetMaxGpaSessions() const = 0;

    /// @brief Returns the count of created sessions in the context.
    ///
    /// @return Number of sessions created in the context.
    virtual GpaUInt32 GetSessionCount() const = 0;

    /// @brief Checks whether the session current exist or not.
    ///
    /// @param [in] session_id Pointer to GPA Session id object.
    ///
    /// @return True if session exist otherwise false.
    virtual bool DoesSessionExist(GpaSessionId session_id) const = 0;

    /// @brief Gets a mask of the sample types supported by this context.
    ///
    /// @param [out] sample_types The value that will be set to the the mask of the sample types supported by this context. This will be a combination of GPA_Context_Sample_Type_Bits.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus GetSupportedSampleTypes(GpaContextSampleTypeFlags* sample_types) const = 0;

    /// @brief Check to see if public counters should be exposed.
    ///
    /// @return True if public counters should be exposed; false otherwise.
    virtual bool ArePublicCountersExposed() const = 0;

    /// @brief Check to see if hardware counters should be exposed.
    ///
    /// @return True if hardware counters should be exposed; false otherwise.
    virtual bool AreHardwareCountersExposed() const = 0;

    /// @brief Sets a flag to invalidate and flush the L2 cache around the next counter sample.
    ///
    /// @param [in] should_invalidate_and_flush_l2_cache Flag indicating to enable invalidation and flushing of the L2 cache.
    virtual void SetInvalidateAndFlushL2Cache(bool should_invalidate_and_flush_l2_cache) = 0;

    /// @brief Returns the status of the flag indicating the invalidation and flushing of L2 cache.
    ///
    /// @return Flag indicating the invalidation and flushing of L2 cache.
    virtual bool IsInvalidateAndFlushL2CacheEnabled() const = 0;

    /// @brief Returns the hardware info.
    ///
    /// @return Pointer to the context hardware info.
    virtual const GpaHwInfo* GetHwInfo() const = 0;

    /// @brief Update the hardware information.
    ///
    /// @param [in] numShaderEngines The number of shader engines to use for calculating counter equations.
    /// @param [in] numComputeUnits The total number of compute units to use for calculating counter equations.
    /// @param [in] numSimds The total number of SIMDs to use for calculating counter equations.
    /// @param [in] numWavesPerSimd The maximum number of waves per SIMD to use for calculating counter equations.
    virtual void UpdateHwInfo(GpaUInt32 numShaderEngines, GpaUInt32 numComputeUnits, GpaUInt32 numSimds, GpaUInt32 numWavesPerSimd) = 0;

    /// @brief Checks whether the context is open or not.
    ///
    /// @return True if context is open otherwise false.
    virtual bool IsOpen() const = 0;

    /// @brief Gets device clock mode behavior.
    ///
    /// @return DeviceClockMode enum indicating clock mode behavior.
    virtual DeviceClockMode GetDeviceClockMode() const = 0;

    /// @brief Begins the session on current context.
    ///
    /// @param [in] gpa_session Pointer to previously created session object.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus BeginSession(IGpaSession* gpa_session) = 0;

    /// @brief Ends the session on current context.
    ///
    /// @param [in] gpa_session Pointer to previously created session object.
    /// @param [in] force_end true to ignore errors and force an end to the session. Default usage is false.
    ///
    /// @return kGpaStatusOk on successful execution.
    virtual GpaStatus EndSession(IGpaSession* gpa_session, bool force_end) = 0;

    /// @brief Returns the active session for the context.
    ///
    /// @return Active session if any session is active otherwise nullptr.
    virtual const IGpaSession* GetActiveSession() const = 0;

    /// Returns the number of GPU shader engines.
    ///
    /// @return number of GPU shader engines.
    virtual uint32_t GetShaderEngineCount() const = 0;

    /// Gets the flags that the context was created with.
    ///
    /// @return The context flags.
    virtual GpaOpenContextFlags GetContextFlags() const = 0;

    /// @brief Enable/disable the stable power state, using the stable clock mode specified when opening the context.
    ///
    /// @param [in] use_profiling_clocks True to use GPU clocks for profiling, false to use default clock mode.
    ///
    /// @return kGpaStatusOk on success.
    virtual GpaStatus SetStableClocks(bool use_profiling_clocks) = 0;
};

#endif  // GPU_PERF_API_COMMON_GPA_CONTEXT_INTERFACE_H_
