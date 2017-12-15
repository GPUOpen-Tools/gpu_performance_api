//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
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
    /// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
    virtual GPA_Status Initialize() = 0;

    /// Undo any initialization to ensure proper behavior in applications that are not being profiled.
    /// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
    virtual GPA_Status Destroy() = 0;

    /// Opens the counters in the specified context for reading.
    /// \param[in] pContext The context to open counters for. Typically a device pointer. Refer to GPA API specific documentation for further details.
    /// \param[in] flags Flags used to initialize the context. Should be a combination of GPA_OpenContext_Bits
    /// \param[out] pGpaContextId Unique identifier of the opened context
    /// \return The GPA result status of the operation. GPA_STATUS_OK is returned if the operation is successful.
    virtual GPA_Status OpenContext(
        void* pContext,
        GPA_OpenContextFlags flags,
        GPA_ContextId* pGpaContextId) = 0;

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
};

#endif // _I_GPA_IMPLEMENTOR_H_