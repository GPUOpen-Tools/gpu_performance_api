//==============================================================================
// Copyright (c) 2017-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Interface for GPA API specific implementor
//==============================================================================

#ifndef _I_GPA_IMPLEMENTOR_H_
#define _I_GPA_IMPLEMENTOR_H_

#include "GPUPerfAPITypes.h"
#include "IGPAInterfaceTrait.h"

/// Interface for API specific GPA Implmentation
class IGPAImplementor : public IGPAInterfaceTrait
{
public:
    /// Virtual Destructor
    virtual ~IGPAImplementor() = default;

    /// Initializes the driver so that counters are exposed.
    /// \param[in] flags Flags used to initialize GPA. Should be a combination of GPA_Initialize_Bits.
    /// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
    virtual GPA_Status Initialize(GPA_InitializeFlags flags) = 0;

    /// Undo any initialization to ensure proper behavior in applications that are not being profiled.
    /// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
    virtual GPA_Status Destroy() = 0;

    /// Opens the counters in the specified context for reading.
    /// \param[in] pContext The context to open counters for. Typically a device pointer. Refer to GPA API specific documentation for further details.
    /// \param[in] flags Flags used to initialize the context. Should be a combination of GPA_OpenContext_Bits
    /// \param[out] pContextId Unique identifier of the opened context
    /// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
    virtual GPA_Status OpenContext(
        void* pContext,
        GPA_OpenContextFlags flags,
        GPA_ContextId* pContextId) = 0;

    /// Closes the counters in the specified context.
    /// \param[in] contextId Unique identifier of the opened context
    /// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
    virtual GPA_Status CloseContext(
        GPA_ContextId contextId) = 0;

    /// Checks whether the context exists or not
    /// \param[in] contextId context id
    /// \return true if context is opened otherwise false
    virtual bool DoesContextExist(
        GPA_ContextId contextId) const = 0;

    /// Checks whether the session exists or not
    /// \param[in] sessionId session id
    /// \return true if session exists otherwise false
    virtual bool DoesSessionExist(
        GPA_SessionId sessionId) const = 0;

    /// Checks whether the command list exists or not
    /// \param[in] commandListId command list id
    /// \return true if command list exists otherwise false
    virtual bool DoesCommandListExist(
        GPA_CommandListId commandListId) const = 0;

    /// Gets the flags used to initialize GPA. This is a mask of GPA_Initialize_Bits
    /// \return the flags used to initialize GPA
    virtual GPA_InitializeFlags GetInitializeFlags() const = 0;

    /// Returns whether the command list is required or not
    /// \return true if command list is required otherwise false
    virtual bool IsCommandListRequired() const = 0;

    /// Returns whether the sample continuation on command list is supported or not
    /// \return true if sample continuation is supported otherwise false
    virtual bool IsContinueSampleOnCommandListSupported() const = 0;

    /// Returns whether the secondary sample copy is supported or not
    /// \return true if copy secondary sample is supported otherwise false
    virtual bool IsCopySecondarySampleSupported() const = 0;
};

#endif // _I_GPA_IMPLEMENTOR_H_