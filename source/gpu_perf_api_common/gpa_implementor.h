//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Common GPA Implementation declarations
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_IMPLEMENTOR_H_
#define GPU_PERF_API_COMMON_GPA_IMPLEMENTOR_H_

#include <mutex>

#include "gpu_perf_api_common/gpa_context_interface.h"
#include "gpu_perf_api_common/gpa_implementor_interface.h"

using GpaContextInfoPtr                 = void*;                                         ///< Type alias for context info pointer.
using GpaDeviceIdentifier               = void*;                                         ///< Type alias for API-specific device identifier.
using GpaDeviceIdentifierGpaContextPair = std::pair<GpaDeviceIdentifier, IGpaContext*>;  ///< Type alias for application and GPA context pair.
using GpaDeviceIdentifierGpaContextMap  = std::map<GpaDeviceIdentifier, IGpaContext*>;   ///< Type alias for application and GPA context map.

/// @brief Class for common GPA Implementation.
class GpaImplementor : public IGpaImplementor
{
public:
    /// @brief Constructor.
    GpaImplementor();

    /// @brief Virtual Destructor.
    virtual ~GpaImplementor() = default;

    /// @copydoc IGpaImplementor::Initialize()
    GpaStatus Initialize(GpaInitializeFlags flags) override;

    /// @copydoc IGpaImplementor::Destroy()
    GpaStatus Destroy() override;

    /// @copydoc IGpaImplementor::OpenContext()
    GpaStatus OpenContext(void* context, GpaOpenContextFlags flags, GpaContextId* gpa_context_id) override;

    /// @copydoc IGpaImplementor::CloseContext()
    GpaStatus CloseContext(GpaContextId gpa_context_id) override;

    /// @copydoc IGpaImplementor::ObjectType()
    GpaObjectType ObjectType() const override;

    /// @copydoc IGpaImplementor::DoesContextExist()
    bool DoesContextExist(GpaContextId gpa_context_id) const override;

    /// @copydoc IGpaImplementor::DoesSessionExist()
    bool DoesSessionExist(GpaSessionId gpa_session_id) const override;

    /// @copydoc IGpaImplementor::DoesCommandListExist()
    bool DoesCommandListExist(GpaCommandListId command_list_id) const override;

    /// @copydoc IGpaImplementor::GetInitializeFlags()
    GpaInitializeFlags GetInitializeFlags() const override;

    /// @copydoc IGpaImplementor::IsCommandListRequired()
    bool IsCommandListRequired() const override;

    /// @copydoc IGpaImplementor::IsContinueSampleOnCommandListSupported()
    bool IsContinueSampleOnCommandListSupported() const override;

    /// @copydoc IGpaImplementor::IsCopySecondarySampleSupported()
    bool IsCopySecondarySampleSupported() const override;

protected:
    /// @brief Checks whether the device is supported.
    ///
    /// @param [in] context_info Context info pointer.
    /// @param [out] hw_info Hardware information if device is supported.
    ///
    /// @return kGpaStatusOk if operation is successful.
    GpaStatus IsDeviceSupported(GpaContextInfoPtr context_info, GpaHwInfo* hw_info) const;

    /// @brief Gets the API level hardware info.
    ///
    /// @param [in] context_info Context info pointer.
    /// @param [out] hw_info Hardware info.
    ///
    /// @return True if operation is successful otherwise false.
    virtual bool GetHwInfoFromApi(const GpaContextInfoPtr context_info, GpaHwInfo& hw_info) const = 0;

    /// @brief Compares two hardware info objects.
    ///
    /// @param [in] first First hardware info.
    /// @param [in] second Second hardware info.
    ///
    /// @return True if the hardware info objects are identical, otherwise false.
    virtual bool CompareHwInfo(const GpaHwInfo& first, const GpaHwInfo& second) const;

    /// @brief Verifies the API level hardware support.
    ///
    /// @param [in] context_info Context info object pointer.
    /// @param [in] hw_info Hardware info.
    ///
    /// @return True if API supports the hardware otherwise false.
    virtual bool VerifyApiHwSupport(const GpaContextInfoPtr context_info, const GpaHwInfo& hw_info) const = 0;

    /// @brief Checks whether the context info exists or not.
    ///
    /// @param [in] context_info Context info pointer.
    ///
    /// @return True if context exist otherwise false.
    bool DoesContextInfoExist(GpaContextInfoPtr context_info) const;

private:
    /// @brief Performs the API-specific tasks needed to open a context.
    ///
    /// @param [in] context_info Context info pointer.
    /// @param [out] hw_info Hardware info.
    /// @param [in] flags Context flags.
    ///
    /// @return IGpaContext pointer if operation is successful otherwise nullptr.
    virtual IGpaContext* OpenApiContext(GpaContextInfoPtr context_info, GpaHwInfo& hw_info, GpaOpenContextFlags flags) = 0;

    /// @brief Performs the API-specific tasks needed to close the context and release the relevant resources.
    ///
    /// @param [in] device_identifier API-Specific device identifier.
    /// @param [in] gpa_context Context object pointer.
    ///
    /// @return True if closing of the context was successful otherwise false.
    virtual bool CloseApiContext(GpaDeviceIdentifier device_identifier, IGpaContext* gpa_context) = 0;

    /// @brief Returns the API specific device identifier.
    ///
    /// @param [in] context_info Pointer to context info.
    ///
    /// @return Device identifier for the passed context info.
    virtual GpaDeviceIdentifier GetDeviceIdentifierFromContextInfo(GpaContextInfoPtr context_info) const = 0;

    /// @brief Returns whether the device generation is supported or not.
    ///
    /// @param [in] hw_info Hardware information.
    ///
    /// @return True if device generation is supported otherwise false.
    bool IsDeviceGenerationSupported(const GpaHwInfo& hw_info) const;

    mutable std::mutex               device_gpa_context_map_mutex_;      ///< Mutex for context manager.
    GpaDeviceIdentifierGpaContextMap app_context_info_gpa_context_map_;  ///< Map of application context info and GPA context.
    bool                             is_initialized_;                    ///< Flag indicating if GPA has been initialized or not.
    GpaInitializeFlags               init_flags_;                        ///< Flags specified when initializing GPA.
};

#endif  // GPU_PERF_API_COMMON_GPA_IMPLEMENTOR_H_
