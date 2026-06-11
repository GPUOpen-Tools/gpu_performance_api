//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Common GPA Implementation declarations
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_IMPLEMENTOR_H_
#define GPU_PERF_API_COMMON_GPA_IMPLEMENTOR_H_

#include <memory>
#include <mutex>
#include <map>

#include "gpu_perf_api_common/gpa_context_interface.h"
#include "gpu_perf_api_common/gpa_implementor_interface.h"
#include "gpu_perf_api_common/gpa_context_counter_mediator.h"

using GpaContextInfoPtr                = void*;                                                        ///< Type alias for context info pointer.
using GpaDeviceIdentifier              = void*;                                                        ///< Type alias for API-specific device identifier.
using GpaDeviceIdentifierGpaContextMap = std::map<GpaDeviceIdentifier, std::unique_ptr<IGpaContext>>;  ///< Type alias for application and GPA context map.

/// @brief Class for common GPA Implementation.
class GpaImplementor : public IGpaImplementor
{
public:
    /// @brief Constructor.
    GpaImplementor();

    /// @brief Virtual Destructor.
    virtual ~GpaImplementor() = default;

    /// @copydoc IGpaImplementor::Initialize()
    [[nodiscard]] GpaStatus Initialize(GpaInitializeFlags flags) override;

    /// @copydoc IGpaImplementor::Destroy()
    void Destroy() override;

    /// @copydoc IGpaImplementor::OpenContext()
    [[nodiscard]] GpaStatus OpenContext(void* context, GpaOpenContextFlags flags, GpaContextId* gpa_context_id) override;

    /// @copydoc IGpaImplementor::CloseContext()
    [[nodiscard]] GpaStatus CloseContext(GpaContextId gpa_context_id) override;

    /// @copydoc IGpaImplementor::ObjectType()
    [[nodiscard]] GpaObjectType ObjectType() const override;

    /// @copydoc IGpaImplementor::DoesContextExist()
    [[nodiscard]] bool DoesContextExist(GpaContextId gpa_context_id) const override;

    /// @copydoc IGpaImplementor::DoesSessionExist()
    [[nodiscard]] bool DoesSessionExist(GpaSessionId gpa_session_id) const override;

    /// @copydoc IGpaImplementor::DoesCommandListExist()
    [[nodiscard]] bool DoesCommandListExist(GpaCommandListId command_list_id) const override;

    /// @copydoc IGpaImplementor::GetInitializeFlags()
    [[nodiscard]] GpaInitializeFlags GetInitializeFlags() const override;

    /// @copydoc IGpaImplementor::IsCommandListRequired()
    [[nodiscard]] bool IsCommandListRequired() const override;

    /// @copydoc IGpaImplementor::IsContinueSampleOnCommandListSupported()
    [[nodiscard]] bool IsContinueSampleOnCommandListSupported() const override;

    /// @copydoc IGpaImplementor::IsCopySecondarySampleSupported()
    [[nodiscard]] bool IsCopySecondarySampleSupported() const override;

protected:
    /// @brief Checks whether the device is supported.
    ///
    /// @param [in] context_info Context info pointer.
    /// @param [in] flags Context flags
    /// @param [in] driver_info Driver Version and type
    /// @param [out] hw_info Hardware information if device is supported.
    ///
    /// @return kGpaStatusOk if operation is successful.
    [[nodiscard]] GpaStatus IsDeviceSupported(GpaContextInfoPtr    context_info,
                                              GpaOpenContextFlags  flags,
                                              GpaDriverInfo const& driver_info,
                                              GpaHwInfo*           hw_info) const;

    /// @brief Checks whether the driver is supported.
    ///
    /// @param [in] context_info Context info pointer.
    ///
    /// @return True if operation is successful.
    [[nodiscard]] virtual bool IsDriverSupported(GpaContextInfoPtr context_info) const;

    /// @brief Gets the API level hardware info.
    ///
    /// @param [in] context_info Context info pointer.
    /// @param [out] hw_info Hardware info.
    ///
    /// @return kGpaStatusOk if operation is successful.
    [[nodiscard]] virtual GpaStatus GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, GpaHwInfo& hw_info) const = 0;

    /// @brief Verifies the API level hardware support.
    ///
    /// @param [in] context_info Context info object pointer.
    /// @param [in] hw_info Hardware info.
    ///
    /// @return True if API supports the hardware otherwise false.
    [[nodiscard]] virtual bool VerifyApiHwSupport(const GpaContextInfoPtr context_info, GpaOpenContextFlags flags, const GpaHwInfo& hw_info) const = 0;

    /// @brief Checks whether the context info exists or not.
    ///
    /// @param [in] context_info Context info pointer.
    ///
    /// @return True if context exist otherwise false.
    [[nodiscard]] bool DoesContextInfoExist(GpaContextInfoPtr context_info) const;

private:
    /// @brief Performs the API-specific tasks needed to open a context.
    ///
    /// @param [in] context_info Context info pointer.
    /// @param [out] hw_info Hardware info.
    /// @param [in] flags Context flags.
    ///
    /// @return Owning IGpaContext pointer if operation is successful otherwise nullptr.
    [[nodiscard]] virtual std::unique_ptr<IGpaContext> OpenApiContext(GpaContextInfoPtr context_info, const GpaHwInfo& hw_info, GpaOpenContextFlags flags) = 0;

    /// @brief Performs the API-specific tasks needed to close the context and release the relevant resources.
    ///
    /// @param [in] gpa_context Owning context object pointer. The context is destroyed when this function returns.
    ///
    /// @return True if closing of the context was successful otherwise false.
    [[nodiscard]] virtual bool CloseApiContext(std::unique_ptr<IGpaContext> gpa_context) = 0;

    /// @brief Returns the API specific device identifier.
    ///
    /// @param [in] context_info Pointer to context info.
    ///
    /// @return Device identifier for the passed context info.
    [[nodiscard]] virtual GpaDeviceIdentifier GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const = 0;

    mutable std::mutex                             device_gpa_context_map_mutex_;      ///< Mutex for context manager.
    GpaDeviceIdentifierGpaContextMap               app_context_info_gpa_context_map_;  ///< Map of application context info and GPA context.
    GpaContextCounterMediator::GpaCtxStatusInfoMap session_info_map_;                  ///< Map of sessions to corresponding info.
    bool                                           is_initialized_;                    ///< Flag indicating if GPA has been initialized or not.
    GpaInitializeFlags                             init_flags_;                        ///< Flags specified when initializing GPA.
};

#endif
