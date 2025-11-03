//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GPA VK Context declarations
//==============================================================================

#ifndef GPU_PERF_API_VK_VK_GPA_CONTEXT_H_
#define GPU_PERF_API_VK_VK_GPA_CONTEXT_H_

#include <mutex>

#include "gpu_perf_api_common/gpa_context.h"

#include "gpu_perf_api_vk/vk_includes.h"

class VkGpaSession;
struct GpaVkContextOpenInfoType;
struct VkPhysicalDeviceGpaPropertiesAMD;

/// @brief Class for Vulkan GPA Context.
class VkGpaContext : public GpaContext
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] open_info Vulkan context info pointer.
    /// @param [in] hw_info Hardware info.
    /// @param [in] flags Context flags.
    VkGpaContext(const GpaVkContextOpenInfoType* open_info, const GpaHwInfo& hw_info, GpaOpenContextFlags flags);

    /// @brief Destructor.
    virtual ~VkGpaContext();

    /// @brief Opens the context and initializes the driver.
    ///
    /// @return GPA_STATUS_OK on success.
    GpaStatus Open();

    /// @copydoc IGpaContext::CreateSession(GpaSessionSampleType)
    GpaSessionId CreateSession(GpaSessionSampleType sample_type) override;

    /// @copydoc IGpaContext::DeleteSession(GpaSessionId)
    bool DeleteSession(GpaSessionId session_id) override;

    /// @copydoc IGpaInterfaceTrait::GetApiType()
    GpaApiType GetApiType() const override;

    /// @brief Obtain the VkDevice that is being used by this context.
    ///
    /// @return The VkDevice for this context.
    VkDevice GetVkDevice() const;

    /// @brief Obtain the VkPhysicalDevice that is being used by this context.
    ///
    /// @return The VkPhysicalDevice for this context.
    VkPhysicalDevice GetVkPhysicalDevice() const;

    /// @brief Get the number of instances of the specified block.
    ///
    /// @param [in] block The block whose number of instances is needed.
    ///
    /// @return The number of instances of the specific block. Could be zero if block does not exist.
    GpaUInt32 GetNumInstances(VkGpaPerfBlockAMD block) const;

    /// @brief Get the max event id of the specified block.
    ///
    /// @param [in] block The block whose max event id is needed.
    ///
    /// @return the max event id of the specified block. Could be zero if block does not exist.
    GpaUInt32 GetMaxEventId(VkGpaPerfBlockAMD block) const;

    /// @copydoc IGpaContext::SetStableClocks(bool)
    [[nodiscard]] GpaStatus SetStableClocks(bool use_profiling_clocks) override;

private:
    /// @brief Deletes a VkGpaSession and its associated counter data. Prerequisite: Assumes m_sessionList has been protected using session_list_mutex_.
    ///
    /// @param [in] vk_gpa_session Pointer to previously created session object.
    ///
    /// @return True if operation is successful otherwise false.
    bool DeleteVkGpaSession(VkGpaSession* vk_gpa_session);

    mutable std::mutex               session_list_mutex_;     ///< Mutex to ensure the m_sessionList doesn't change while being accessed.
    VkPhysicalDevice                 physical_device_;        ///< The physical device on which the device was created.
    VkDevice                         device_;                 ///< The device queries and counters are created on.
    VkPhysicalDeviceGpaPropertiesAMD amd_device_properties_;  ///< Physical Device properties exposed by the AMD GPA Extension.
    VkGpaDeviceClockModeAMD          clock_mode_;             ///< GPU Clock mode.
};
#endif
