//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GPA Common Context class.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_CONTEXT_H_
#define GPU_PERF_API_COMMON_GPA_CONTEXT_H_

#include <functional>
#include <list>
#include <mutex>
#include <numeric>

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_common/gpa_common_defs.h"
#include "gpu_perf_api_common/gpa_context_interface.h"
#include "gpu_perf_api_common/gpa_session_interface.h"

/// @brief Type alias for list of IGpaSession objects.
using GpaSessionList = std::list<IGpaSession*>;

/// @brief Abstract GPAContext for common context code.
class GpaContext : public IGpaContext
{
public:
    /// @brief Delete default constructor.
    GpaContext() = delete;

    /// @brief Virtual Destructor.
    virtual ~GpaContext() = default;

    /// @copydoc IGpaContext::GetSupportedSampleTypes()
    GpaContextSampleTypeFlags GetSupportedSampleTypes() const override;

    /// @copydoc IGpaContext::ArePublicCountersExposed()
    bool ArePublicCountersExposed() const override;

    /// @copydoc IGpaContext::AreHardwareCountersExposed()
    bool AreHardwareCountersExposed() const override;

    /// @copydoc IGpaContext::GetHwInfo()
    const GpaHwInfo& GetHwInfo() const override;

    /// @copydoc IGpaContext::UpdateHwInfo()
    void UpdateHwInfo(GpaUInt32 num_shader_engines, GpaUInt32 num_compute_units, GpaUInt32 num_simds, GpaUInt32 num_waves_per_simd) override;

    /// @copydoc IGpaContext::IsOpen()
    bool IsOpen() const override;

    /// @copydoc IGpaContext::GetDeviceClockMode()
    DeviceClockMode GetDeviceClockMode() const override;

    /// @copydoc IGpaInterfaceTrait::ObjectType()
    GpaObjectType ObjectType() const override;

    /// @copydoc IGpaContext::DoesSessionExist()
    bool DoesSessionExist(GpaSessionId gpa_session_id) const override;

    /// @copydoc IGpaContext::BeginSession()
    GpaStatus BeginSession(IGpaSession* gpa_session) override;

    /// @copydoc IGpaContext::EndSession()
    GpaStatus EndSession(IGpaSession* gpa_session, bool force_end) override;

    /// @copydoc IGpaContext::GetShaderEngineCount()
    uint32_t GetShaderEngineCount() const override;

    /// @copydoc IGpaContext::GetContextFlags()
    GpaOpenContextFlags GetContextFlags() const override
    {
        return context_flags_;
    }

    /// @copydoc IGpaContext::GetActiveSession()
    const IGpaSession* GetActiveSession() const override;

protected:
    /// @brief Protected constructor.
    ///
    /// @param [in] hw_info The hardware info for the context.
    /// @param [in] flags Creation flags for context.
    GpaContext(const GpaHwInfo& hw_info, GpaOpenContextFlags flags);

    /// @brief Marks the context to be opened.
    ///
    /// @param [in] open Flag indicating context to be marked open or closed.
    void SetAsOpened(bool open);

    /// @brief Returns whether the device is AMD device or not.
    ///
    /// @return true if context device is AMD device otherwise false.
    bool IsAmdDevice() const;

    /// @brief Adds the GPA session to the session list.
    ///
    /// @param [in] gpa_session GPA session object pointer.
    GPA_THREAD_SAFE_FUNCTION void AddGpaSession(IGpaSession* gpa_session);

    /// @brief Removes the GPA session from the session list.
    ///
    /// @param [in] gpa_session GPA session object pointer.
    GPA_THREAD_SAFE_FUNCTION void RemoveGpaSession(IGpaSession* gpa_session);

    /// @brief Iterate over GPA session list for the passed function.
    ///
    /// @param [in] function Function to be executed for each object in the list. The function may return false to terminate iteration.
    GPA_THREAD_SAFE_FUNCTION void IterateGpaSessionList(const std::function<bool(IGpaSession* gpa_session)>& function) const;

    /// @brief Clears the list of the GPA session.
    GPA_THREAD_SAFE_FUNCTION void ClearSessionList();

    /// @brief Returns the index of the GPA session if it exists.
    ///
    /// @param [in] gpa_session GPA session.
    /// @param [out] index Index of the the GPA session in the list.
    ///
    /// @return True if the index was found, false otherwise.
    bool GetIndex(IGpaSession* gpa_session, unsigned int* index = nullptr) const;

private:
    GpaOpenContextFlags context_flags_;                          ///< Context flags.
    GpaHwInfo           hw_info_;                                ///< Hw info.
    bool                is_open_;                                ///< Flag indicating context is open or not.
    GpaSessionList      gpa_session_list_;                       ///< List of GPA sessions in the context.
    bool                is_amd_device_;                          ///< Flag indicating whether the device is AMD or not.
    mutable std::mutex  gpa_session_list_mutex_;                 ///< Mutex for GPA session list.
    IGpaSession*        active_session_;                         ///< Gpa session to keep track of active session.
    mutable std::mutex  active_session_mutex_;                   ///< Mutex for the active session.

#ifdef _WIN32
    inline static HANDLE gpa_mutex_handle = NULL;  // IPC Mutex to prevent TDRs from multiple apps trying to profile GPU
#endif
};

#endif
