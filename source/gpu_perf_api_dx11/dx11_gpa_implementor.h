//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief DX11 GPA Implementation declarations
//==============================================================================

#ifndef GPU_PERF_API_DX11_DX11_GPA_IMPLEMENTOR_H_
#define GPU_PERF_API_DX11_DX11_GPA_IMPLEMENTOR_H_

#include "gpu_perf_api_common/gpa_implementor.h"

#include "gpu_perf_api_dx11/dx11_include.h"

/// @brief Class for DX11 GPA Implementation.
class Dx11GpaImplementor final : public GpaImplementor
{
public:
    /// @brief Singleton instance accessor.
    ///
    /// @return The singleton instance of the Dx11GpaImplementor.
    [[nodiscard]] static Dx11GpaImplementor& Instance()
    {
        static Dx11GpaImplementor instance;
        return instance;
    }

    /// @brief Deleted copy constructor. Use Instance() to get the singleton instance.
    Dx11GpaImplementor(const Dx11GpaImplementor&) = delete;
    /// @brief Deleted copy assignment operator. Use Instance() to get the singleton instance.
    void operator=(const Dx11GpaImplementor&) = delete;
    /// @brief Deleted move constructor. Use Instance() to get the singleton instance.
    Dx11GpaImplementor(Dx11GpaImplementor&&) = delete;
    /// @brief Deleted move assignment operator. Use Instance() to get the singleton instance.
    void operator=(Dx11GpaImplementor&&) = delete;

    /// @copydoc IGpaInterfaceTrait::GetApiType()
    [[nodiscard]] GpaApiType GetApiType() const override
    {
        return kGpaApiDirectx11;
    }

    /// @copydoc GpaImplementor::GetHwInfoFromApi()
    [[nodiscard]] GpaStatus GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, GpaHwInfo& hw_info) const override;

    /// @copydoc GpaImplementor::VerifyApiHwSupport()
    [[nodiscard]] bool VerifyApiHwSupport(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, const GpaHwInfo& hw_info) const override;

    /// @brief Returns the AMD extension function pointer.
    //
    /// @return DirectX 11 AMD extension function pointer.
    [[nodiscard]] PFNAmdDxExtCreate11 GetAmdExtFuncPointer() const;

private:
    /// @brief Constructor.
    Dx11GpaImplementor() = default;

    /// @brief Destructor.
    ~Dx11GpaImplementor() override
    {
        Destroy();
    }

    /// @brief Initializes the AMD extension function pointer.
    ///
    /// @return True upon successful initialization otherwise false.
    [[nodiscard]] bool InitializeAmdExtFunction() const;

    /// @copydoc GpaImplementor::OpenApiContext(GpaContextInfoPtr, GpaHwInfo&, GpaOpenContextFlags)
    [[nodiscard]] std::unique_ptr<IGpaContext> OpenApiContext(GpaContextInfoPtr context_info, const GpaHwInfo& hw_info, GpaOpenContextFlags flags) override;

    /// @copydoc GpaImplementor::CloseApiContext(std::unique_ptr<IGpaContext>)
    [[nodiscard]] bool CloseApiContext(std::unique_ptr<IGpaContext> context) override;

    /// @copydoc GpaImplementor::GetDeviceIdentifierFromContextInfo()
    [[nodiscard]] GpaDeviceIdentifier GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const override;

    mutable PFNAmdDxExtCreate11 amd_dx_ext_create11_func_ptr_ = {};  ///< AMD DirectX 11 extension Function pointer.
};

#endif
