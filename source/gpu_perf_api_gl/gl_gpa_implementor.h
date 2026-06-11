//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GL GPA Implementation declarations
//==============================================================================

#ifndef GPU_PERF_API_GL_GPA_IMPLEMENTOR_H_
#define GPU_PERF_API_GL_GPA_IMPLEMENTOR_H_

#include "gpu_perf_api_common/gpa_implementor.h"

/// @brief Class for GL GPA Implementation.
class GlGpaImplementor final : public GpaImplementor
{
public:
    /// @brief Singleton instance accessor.
    ///
    /// @return The singleton instance of the GlGpaImplementor.
    [[nodiscard]] static GlGpaImplementor& Instance()
    {
        static GlGpaImplementor instance;
        return instance;
    }

    /// @brief Deleted copy constructor. Use Instance() to get the singleton instance.
    GlGpaImplementor(const GlGpaImplementor&) = delete;
    /// @brief Deleted copy assignment operator. Use Instance() to get the singleton instance.
    void operator=(const GlGpaImplementor&) = delete;
    /// @brief Deleted move constructor. Use Instance() to get the singleton instance.
    GlGpaImplementor(GlGpaImplementor&&) = delete;
    /// @brief Deleted move assignment operator. Use Instance() to get the singleton instance.
    void operator=(GlGpaImplementor&&) = delete;

    /// @copydoc IGpaInterfaceTrait::GetApiType()
    [[nodiscard]] GpaApiType GetApiType() const override
    {
        return kGpaApiOpengl;
    }

    /// @copydoc GpaImplementor::GetHwInfoFromApi()
    [[nodiscard]] GpaStatus GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, GpaHwInfo& hw_info) const override;

    /// @copydoc GpaImplementor::VerifyApiHwSupport()
    [[nodiscard]] bool VerifyApiHwSupport(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, const GpaHwInfo& hw_info) const override;

private:
    /// @brief Constructor.
    GlGpaImplementor();

    /// @brief Destructor.
    ~GlGpaImplementor() override
    {
        Destroy();
    };

    /// @copydoc GpaImplementor::OpenApiContext()
    [[nodiscard]] std::unique_ptr<IGpaContext> OpenApiContext(GpaContextInfoPtr context_info, const GpaHwInfo& hw_info, GpaOpenContextFlags flags) override;

    /// @copydoc GpaImplementor::CloseApiContext()
    [[nodiscard]] bool CloseApiContext(std::unique_ptr<IGpaContext> context) override;

    /// @copydoc GpaImplementor::GetDeviceIdentifierFromContextInfo()
    [[nodiscard]] GpaDeviceIdentifier GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const override;

    /// @brief Checks whether the driver is supported.
    ///
    /// @param [in] context_info Context info pointer.
    ///
    /// @return True if operation is successful.
    [[nodiscard]] bool IsDriverSupported(GpaContextInfoPtr context_info) const override;

    mutable bool is_gl_entry_points_initialized_;  ///< Flag indicating the GL entry point has been initialized or not.
};

#endif
