//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief GL GPA Implementation declarations
//==============================================================================

#ifndef GPU_PERF_API_GL_GPA_IMPLEMENTOR_H_
#define GPU_PERF_API_GL_GPA_IMPLEMENTOR_H_

#include "TSingleton.h"

#include "gpu_perf_api_common/gpa_implementor.h"

/// @brief Class for GL GPA Implementation.
class GlGpaImplementor : public GpaImplementor, public TSingleton<GlGpaImplementor>
{
public:
    /// @copydoc IGpaInterfaceTrait::GetApiType()
    GpaApiType GetApiType() const override final;

    /// @copydoc GpaImplementor::GetHwInfoFromApi()
    bool GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaHwInfo& hw_info) const override final;

    /// @copydoc GpaImplementor::VerifyApiHwSupport()
    bool VerifyApiHwSupport(const GpaContextInfoPtr context_info, const GpaHwInfo& hw_info) const override final;

private:
    friend class TSingleton<GlGpaImplementor>;  ///< Friend declaration to allow access to the constructor.

    /// @brief Constructor.
    GlGpaImplementor();

    /// @brief Destructor.
    ~GlGpaImplementor(){};

    /// @brief Singleton; don't allow copies.
    GlGpaImplementor(const GlGpaImplementor&) = delete;

    /// @brief Singleton; don't allow assignment.
    void operator=(const GlGpaImplementor&) = delete;

    /// @copydoc GpaImplementor::OpenApiContext()
    IGpaContext* OpenApiContext(GpaContextInfoPtr context_info, GpaHwInfo& hw_info, GpaOpenContextFlags flags) override final;

    /// @copydoc GpaImplementor::CloseApiContext()
    bool CloseApiContext(GpaDeviceIdentifier device_identifier, IGpaContext* context) override final;

    /// @copydoc GpaImplementor::GetDeviceIdentifierFromContextInfo()
    GpaDeviceIdentifier GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const override final;

    /// @brief Attempt to retrieve the device ID from platform-specific OpenGL extensions.
    ///
    /// @param [out] driver_device_id If the calls to the extensions are successful, this will be set to the device ID.
    ///
    /// @return True if the driver_device_id has been set, and false otherwise.
    bool GetDeviceIdFromPlatformExt(unsigned int& driver_device_id) const;
    
    /// @brief Checks whether the driver is supported.
    ///
    /// @param [in] context_info Context info pointer.
    ///
    /// @return True if operation is successful.
    bool IsDriverSupported(GpaContextInfoPtr context_info) const override;

    mutable bool is_gl_entry_points_initialized_;  ///< Flag indicating the GL entry point has been initialized or not.
    mutable int  gl_driver_version_;               ///< GL driver version returned in the ASIC info.
};

#endif  // GPU_PERF_API_GL_GPA_IMPLEMENTOR_H_
