//==============================================================================
// Copyright (c) 2017-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Interface for GPA API specific implementor.
//==============================================================================

#ifndef GPU_PERF_API_COMMON_GPA_IMPLEMENTOR_INTERFACE_H_
#define GPU_PERF_API_COMMON_GPA_IMPLEMENTOR_INTERFACE_H_

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_common/gpa_interface_trait_interface.h"

/// @brief Interface for API specific GPA Implementation.
class IGpaImplementor : public IGpaInterfaceTrait
{
public:
    /// @brief Virtual Destructor.
    virtual ~IGpaImplementor() = default;

    /// @brief Initializes the driver so that counters are exposed.
    ///
    /// @param [in] flags Flags used to initialize GPA. Should be a combination of GPA_Initialize_Bits.
    ///
    /// @return The GPA result status of the operation. kGpaStatusOk is returned if the operation is successful.
    virtual GpaStatus Initialize(GpaInitializeFlags flags) = 0;

    /// @brief Undo any initialization to ensure proper behavior in applications that are not being profiled.
    ///
    /// @return The GPA result status of the operation. kGpaStatusOk is returned if the operation is successful.
    virtual GpaStatus Destroy() = 0;

    /// @brief Opens the counters in the specified context for reading.
    ///
    /// @param [in] context The context to open counters for. Typically a device pointer. Refer to GPA API specific documentation for further details.
    /// @param [in] flags Flags used to initialize the context. Should be a combination of GPA_OpenContext_Bits.
    /// @param [out] gpa_context_id Unique identifier of the opened context.
    ///
    /// @return The GPA result status of the operation. kGpaStatusOk is returned if the operation is successful.
    virtual GpaStatus OpenContext(void* context, GpaOpenContextFlags flags, GpaContextId* gpa_context_id) = 0;

    /// @brief Closes the counters in the specified context.
    ///
    /// @param [in] gpa_context_id Unique identifier of the opened context.
    ///
    /// @return The GPA result status of the operation. kGpaStatusOk is returned if the operation is successful.
    virtual GpaStatus CloseContext(GpaContextId gpa_context_id) = 0;

    /// @brief Checks whether the context exists or not.
    ///
    /// @param [in] gpa_context_id Context id.
    ///
    /// @return True if context is opened otherwise false.
    virtual bool DoesContextExist(GpaContextId gpa_context_id) const = 0;

    /// @brief Checks whether the session exists or not.
    ///
    /// @param [in] gpa_session_id Session id.
    ///
    /// @return True if session exists otherwise false.
    virtual bool DoesSessionExist(GpaSessionId gpa_session_id) const = 0;

    /// @brief Checks whether the command list exists or not.
    ///
    /// @param [in] command_list_id Command list id.
    ///
    /// @return True if command list exists otherwise false.
    virtual bool DoesCommandListExist(GpaCommandListId command_list_id) const = 0;

    /// @brief Gets the flags used to initialize GPA. This is a mask of GPA_Initialize_Bits.
    ///
    /// @return The flags used to initialize GPA.
    virtual GpaInitializeFlags GetInitializeFlags() const = 0;

    /// @brief Returns whether the command list is required or not.
    ///
    /// @return True if command list is required otherwise false.
    virtual bool IsCommandListRequired() const = 0;

    /// @brief Returns whether the sample continuation on command list is supported or not.
    ///
    /// @return True if sample continuation is supported otherwise false.
    virtual bool IsContinueSampleOnCommandListSupported() const = 0;

    /// @brief Returns whether the secondary sample copy is supported or not.
    ///
    /// @return True if copy secondary sample is supported otherwise false.
    virtual bool IsCopySecondarySampleSupported() const = 0;
};

#endif
