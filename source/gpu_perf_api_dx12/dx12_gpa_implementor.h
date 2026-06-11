//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX12 GPA Implementation declarations
//==============================================================================

#ifndef GPU_PERF_API_DX12_DX12_GPA_IMPLEMENTOR_H_
#define GPU_PERF_API_DX12_DX12_GPA_IMPLEMENTOR_H_

#include "gpu_perf_api_common/gpa_implementor.h"

#include "gpu_perf_api_dx12/dx12_gpa_context.h"

/// @brief Class for DX12 GPA Implementation.
class Dx12GpaImplementor final : public GpaImplementor
{
public:
    /// @brief Singleton instance accessor.
    ///
    /// @return The singleton instance of the Dx12GpaImplementor.
    [[nodiscard]] static Dx12GpaImplementor& Instance()
    {
        static Dx12GpaImplementor instance;
        return instance;
    }

    /// @brief Deleted copy constructor. Use Instance() to get the singleton instance.
    Dx12GpaImplementor(const Dx12GpaImplementor&) = delete;
    /// @brief Deleted copy assignment operator. Use Instance() to get the singleton instance.
    void operator=(const Dx12GpaImplementor&) = delete;
    /// @brief Deleted move constructor. Use Instance() to get the singleton instance.
    Dx12GpaImplementor(Dx12GpaImplementor&&) = delete;
    /// @brief Deleted move assignment operator. Use Instance() to get the singleton instance.
    void operator=(Dx12GpaImplementor&&) = delete;

    /// @copydoc IGpaInterfaceTrait::GetApiType()
    [[nodiscard]] GpaApiType GetApiType() const override
    {
        return kGpaApiDirectx12;
    }

    /// @copydoc GpaImplementor::GetHwInfoFromApi()
    [[nodiscard]] GpaStatus GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, GpaHwInfo& hw_info) const override;

    /// @copydoc GpaImplementor::VerifyApiHwSupport()
    [[nodiscard]] bool VerifyApiHwSupport(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, const GpaHwInfo& hw_info) const override;

    /// @copydoc GpaImplementor::Initialize(GpaInitializeFlags)
    [[nodiscard]] GpaStatus Initialize(GpaInitializeFlags flags) override;

    /// @copydoc IGpaImplementor::IsCommandListRequired()
    [[nodiscard]] bool IsCommandListRequired() const override;

    /// @copydoc IGpaImplementor::IsContinueSampleOnCommandListSupported()
    [[nodiscard]] bool IsContinueSampleOnCommandListSupported() const override;

    /// @copydoc IGpaImplementor::IsCopySecondarySampleSupported()
    [[nodiscard]] bool IsCopySecondarySampleSupported() const override;

private:
    /// @brief Constructor.
    Dx12GpaImplementor() = default;

    /// @brief Destructor.
    ~Dx12GpaImplementor() override
    {
        Destroy();
    }

    /// @copydoc GpaImplementor::OpenApiContext()
    [[nodiscard]] std::unique_ptr<IGpaContext> OpenApiContext(GpaContextInfoPtr context_info, const GpaHwInfo& hw_info, GpaOpenContextFlags flags) override;

    /// @copydoc GpaImplementor::CloseApiContext()
    [[nodiscard]] bool CloseApiContext(std::unique_ptr<IGpaContext> context) override;

    /// @copydoc GpaImplementor::GetDeviceIdentifierFromContextInfo()
    [[nodiscard]] GpaDeviceIdentifier GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const override;
};

#endif
