//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  VK GPA Implementation declarations
//==============================================================================

#ifndef GPU_PERF_API_VK_VK_GPA_IMPLEMENTOR_H_
#define GPU_PERF_API_VK_VK_GPA_IMPLEMENTOR_H_

#include "gpu_perf_api_common/gpa_implementor.h"

#include "gpu_perf_api_vk/vk_gpa_context.h"

/// @brief Class for Vulkan GPA Implementation.
class VkGpaImplementor final : public GpaImplementor
{
public:
    /// @brief Singleton instance accessor.
    ///
    /// @return The singleton instance of the VkGpaImplementor.
    [[nodiscard]] static VkGpaImplementor& Instance()
    {
        static VkGpaImplementor instance;
        return instance;
    }

    /// @brief Deleted copy constructor. Use Instance() to get the singleton instance.
    VkGpaImplementor(const VkGpaImplementor&) = delete;
    /// @brief Deleted copy assignment operator. Use Instance() to get the singleton instance.
    void operator=(const VkGpaImplementor&) = delete;
    /// @brief Deleted move constructor. Use Instance() to get the singleton instance.
    VkGpaImplementor(VkGpaImplementor&&) = delete;
    /// @brief Deleted move assignment operator. Use Instance() to get the singleton instance.
    void operator=(VkGpaImplementor&&) = delete;

    /// @copydoc IGpaInterfaceTrait::GetApiType()
    [[nodiscard]] GpaApiType GetApiType() const override
    {
        return kGpaApiVulkan;
    }

    /// @copydoc GpaImplementor::GetHwInfoFromApi(const GpaContextInfoPtr, GpaHwInfo&)
    [[nodiscard]] GpaStatus GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, GpaHwInfo& hardware_info) const override;

    /// @copydoc GpaImplementor::VerifyApiHwSupport(const GpaContextInfoPtr, const GpaHwInfo&)
    [[nodiscard]] bool VerifyApiHwSupport(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, const GpaHwInfo& hardware_info) const override;

    /// @copydoc IGpaImplementor::IsCommandListRequired()
    [[nodiscard]] bool IsCommandListRequired() const override;

    /// @copydoc IGpaImplementor::IsContinueSampleOnCommandListSupported()
    [[nodiscard]] bool IsContinueSampleOnCommandListSupported() const override;

    /// @copydoc IGpaImplementor::IsCopySecondarySampleSupported()
    [[nodiscard]] bool IsCopySecondarySampleSupported() const override;

private:
    /// @brief Constructor.
    VkGpaImplementor() = default;

    /// @brief Destructor.
    ~VkGpaImplementor() override
    {
        Destroy();
    }

    /// @brief Stores the instance that this GPA implementation is using.
    VkInstance vk_instance_ = VK_NULL_HANDLE;

    /// @copydoc GpaImplementor::OpenApiContext()
    [[nodiscard]] std::unique_ptr<IGpaContext> OpenApiContext(GpaContextInfoPtr context_info, const GpaHwInfo& hw_info, GpaOpenContextFlags flags) override;

    /// @copydoc GpaImplementor::CloseApiContext()
    [[nodiscard]] bool CloseApiContext(std::unique_ptr<IGpaContext> context) override;

    /// @copydoc GpaImplementor::GetDeviceIdentifierFromContextInfo()
    [[nodiscard]] GpaDeviceIdentifier GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const override;
};

#endif
