//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  VK GPA Implementation declarations
//==============================================================================

#ifndef GPU_PERF_API_VK_VK_GPA_IMPLEMENTOR_H_
#define GPU_PERF_API_VK_VK_GPA_IMPLEMENTOR_H_

#include "TSingleton.h"

#include "gpu_perf_api_common/gpa_implementor.h"

#include "gpu_perf_api_vk/vk_gpa_context.h"

/// @brief Class for Vulkan GPA Implementation.
class VkGpaImplementor : public GpaImplementor, public TSingleton<VkGpaImplementor>
{
public:
    /// @copydoc IGpaInterfaceTrait::GetAPIType()
    GpaApiType GetApiType() const override;

    /// @copydoc GpaImplementor::GetHwInfoFromApi(const GpaContextInfoPtr, GpaHwInfo&)
    bool GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, GpaHwInfo& hardware_info) const override final;

    /// @copydoc GpaImplementor::VerifyApiHwSupport(const GpaContextInfoPtr, const GpaHwInfo&)
    bool VerifyApiHwSupport(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, const GpaHwInfo& hardware_info) const override final;

    /// @copydoc IGpaImplementor::IsCommandListRequired()
    bool IsCommandListRequired() const override;

    /// @copydoc IGpaImplementor::IsContinueSampleOnCommandListSupported()
    bool IsContinueSampleOnCommandListSupported() const override;

    /// @copydoc IGpaImplementor::IsCopySecondarySampleSupported()
    bool IsCopySecondarySampleSupported() const override;

private:
    friend class TSingleton<VkGpaImplementor>;

    /// @brief Constructor.
    VkGpaImplementor(){};

    /// @brief Destructor.
    ~VkGpaImplementor(){};

    // @brief Deleted copy constructor.
    VkGpaImplementor(const VkGpaImplementor&) = delete;

    // @brief Deleted assignment operator.
    void operator=(const VkGpaImplementor&) = delete;

    /// @brief Stores the instance that this GPA implementation is using.
    VkInstance vk_instance_;

    /// @copydoc GpaImplementor::OpenApiContext()
    IGpaContext* OpenApiContext(GpaContextInfoPtr context_info, GpaHwInfo& hw_info, GpaOpenContextFlags flags) override final;

    /// @copydoc GpaImplementor::CloseApiContext()
    bool CloseApiContext(GpaDeviceIdentifier device_identifier, IGpaContext* context) override final;

    /// @copydoc GpaImplementor::GetDeviceIdentifierFromContextInfo()
    GpaDeviceIdentifier GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const override final;
};

#endif  // GPU_PERF_API_VK_VK_GPA_IMPLEMENTOR_H_
