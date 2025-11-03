//==============================================================================
// Copyright (c) 2017-2025 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  DX12 GPA Implementation declarations
//==============================================================================

#ifndef GPU_PERF_API_DX12_DX12_GPA_IMPLEMENTOR_H_
#define GPU_PERF_API_DX12_DX12_GPA_IMPLEMENTOR_H_

#include "TSingleton.h"

#include "gpu_perf_api_common/gpa_implementor.h"

#include "gpu_perf_api_dx12/dx12_gpa_context.h"

/// @brief Class for DX12 GPA Implementation.
class Dx12GpaImplementor : public GpaImplementor, public TSingleton<Dx12GpaImplementor>
{
public:
    /// @copydoc IGpaInterfaceTrait::GetApiType()
    GpaApiType GetApiType() const override;

    /// @copydoc GpaImplementor::GetHwInfoFromApi()
    bool GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, GpaHwInfo& hw_info) const override final;

    /// @copydoc GpaImplementor::VerifyApiHwSupport()
    bool VerifyApiHwSupport(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, const GpaHwInfo& hw_info) const override final;

    /// @copydoc IGpaImplementor::Destroy()
    GpaStatus Destroy() override;

    /// @copydoc Dx12GpaImplementor::Initialize(GpaInitializeFlags)
    GpaStatus Initialize(GpaInitializeFlags flags);

    /// @copydoc IGpaImplementor::IsCommandListRequired()
    bool IsCommandListRequired() const override;

    /// @copydoc IGpaImplementor::IsContinueSampleOnCommandListSupported()
    bool IsContinueSampleOnCommandListSupported() const override;

    /// @copydoc IGpaImplementor::IsCopySecondarySampleSupported()
    bool IsCopySecondarySampleSupported() const override;

private:
    friend class TSingleton<Dx12GpaImplementor>;  ///< Friend declaration to allow access to the constructor.

    /// @brief Constructor.
    Dx12GpaImplementor() = default;

    /// @brief Destructor.
    virtual ~Dx12GpaImplementor();

    /// @brief Singleton; Do not allow copies.
    Dx12GpaImplementor(const Dx12GpaImplementor&) = delete;

    /// @brief Singleton; Do not allow assignment.
    void operator=(const Dx12GpaImplementor&) = delete;

    /// @copydoc GpaImplementor::OpenApiContext()
    IGpaContext* OpenApiContext(GpaContextInfoPtr context_info, const GpaHwInfo& hw_info, GpaOpenContextFlags flags) override final;

    /// @copydoc GpaImplementor::CloseApiContext()
    [[nodiscard]] bool CloseApiContext(IGpaContext* context) override final;

    /// @copydoc GpaImplementor::GetDeviceIdentifierFromContextInfo()
    GpaDeviceIdentifier GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const override final;
};

#endif
