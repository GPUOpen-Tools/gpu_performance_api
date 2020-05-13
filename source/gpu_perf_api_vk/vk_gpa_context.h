//==============================================================================
// Copyright (c) 2017-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA VK Context declarations
//==============================================================================

#ifndef _VK_GPA_CONTEXT_H_
#define _VK_GPA_CONTEXT_H_

#include <mutex>
#include "vk_includes.h"
#include "gpa_context.h"

// Predeclared objects
class VkGPASession;
struct GPA_vkContextOpenInfo;

struct VkPhysicalDeviceGpaPropertiesAMD;

/// Class for Vulkan GPA Context
class VkGPAContext : public GPAContext
{
public:
    /// Constructor
    /// \param[in] openInfo Vulkan context info pointer
    /// \param[in] hwInfo hardware info
    /// \param[in] flags context flags
    VkGPAContext(const GPA_vkContextOpenInfo* openInfo, GPA_HWInfo& hwInfo, GPA_OpenContextFlags flags);

    /// Destructor
    virtual ~VkGPAContext();

    /// Opens the context and initializes the driver
    /// \return GPA_STATUS_OK on success
    GPA_Status Open();

    /// \copydoc IGPAContext::CreateSession()
    GPA_SessionId CreateSession(GPA_Session_Sample_Type sampleType) override;

    /// \copydoc IGPAContext::DeleteSession()
    bool DeleteSession(GPA_SessionId sessionId) override;

    /// \copydoc IGPAContext::GetMaxGPASessions()
    gpa_uint32 GetMaxGPASessions() const override;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

    /// Obtain the VkDevice that is being used by this context.
    /// \return The VkDevice for this context.
    VkDevice GetVkDevice() const;

    /// Obtain the VkPhysicalDevice that is being used by this context.
    /// \return The VkPhysicalDevice for this context.
    VkPhysicalDevice GetVkPhysicalDevice() const;

    /// Get the number of instances of the specified block
    /// \param[in] block the block whose number of instances is needed
    /// \return the number of instances of the specific block. Could be zero if block does not exist
    gpa_uint32 GetInstanceCount(VkGpaPerfBlockAMD block) const;

    /// Get the max event id of the specified block
    /// \param[in] block the block whose max event id is needed
    /// \return the max event id of the specified block. Could be zero if block does not exist
    gpa_uint32 GetMaxEventIdCount(VkGpaPerfBlockAMD block) const;

    /// \copydoc IGPAContext::SetStableClocks()
    GPA_Status SetStableClocks(bool useProfilingClocks) override;

private:
    /// Deletes a VkGPASession and its associated counter data
    /// Prerequisite: Assumes m_sessionList has been protected using m_sessionListMutex.
    /// \param[in] pVkGpaSession pointer to previously created session object
    /// \return true if operation is successful otherwise false
    bool DeleteVkGpaSession(VkGPASession* pVkGpaSession);

    mutable std::mutex               m_sessionListMutex;     ///< Mutex to ensure the m_sessionList doesn't change while being accessed
    VkPhysicalDevice                 m_physicalDevice;       ///< The physical device on which the device was created
    VkDevice                         m_device;               ///< The device queries and counters are created on
    VkPhysicalDeviceGpaPropertiesAMD m_amdDeviceProperties;  ///< Physical Device properties exposed by the AMD GPA Extension
    VkGpaDeviceClockModeAMD          m_clockMode;            ///< GPU Clock mode
};
#endif  //_VK_GPA_CONTEXT_H_
