//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA CL Context declarations
//==============================================================================

#ifndef _CL_GPA_CONTEXT_H_
#define _CL_GPA_CONTEXT_H_

// std
#include <list>

#include <CL/cl.h>


// GPA Common
#include "GPAContext.h"

/// Class for OpenCL GPA Context
class CLGPAContext : public GPAContext
{
public:

    /// Constructor
    /// \param[in] clCommandQueue the CL Command queue used to create the context
    /// \param[in] pHwInfo the hardware info used to create the context
    /// \param[in] contextFlags the flags used to create the context
    CLGPAContext(cl_command_queue& clCommandQueue, GPA_HWInfo& pHwInfo, GPA_OpenContextFlags contextFlags);

    /// Destructor
    ~CLGPAContext();

    /// \copydoc IGPAContext::CreateSession()
    GPA_SessionId CreateSession() override;

    /// \copydoc IGPAContext::DeleteSession()
    bool DeleteSession(GPA_SessionId sessionId) override;

    /// \copydoc IGPAContext::GetMaxGPASessions()
    gpa_uint32 GetMaxGPASessions() const override;

    /// \copydoc IGPAContext::DoesSessionExist()
    bool DoesSessionExist(GPA_SessionId pSessionId) const override;

    /// \copydoc IGPAInterfaceTrait::GetAPIType()
    GPA_API_Type GetAPIType() const override;

    /// Initializes the OpenCL context
    /// \param[in] clDeviceId the CL Device ID for this context
    /// \return true if initialization is successful otherwise false
    bool Initialize(cl_device_id& clDeviceId);

    /// Gets the CL device id
    /// \return the CL device id
    const cl_device_id& GetCLDeviceId() const;

    /// Gets the CL command queue
    /// \return the CL command queue
    const cl_command_queue& GetCLCommandQueue() const;

private:

    cl_command_queue m_clCommandQueue;   ///< CL command queue for this context
    cl_device_id     m_clDeviceId;       ///< CL device id for this context
};

#endif // _CL_GPA_CONTEXT_H_
