//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPA CL Context declarations
//==============================================================================

#ifndef _CL_GPA_CONTEXT_H_
#define _CL_GPA_CONTEXT_H_

#include <CL/cl.h>
#include <CL/internal/cl_profile_amd.h>

// GPA Common
#include "GPAContext.h"

/// Class for OpenCL GPA Context
class CLGPAContext : public GPAContext
{
public:
    /// Constructor
    /// \param[in] clCommandQueue the CL Command queue used to create the context
    /// \param[in] hwInfo the hardware info used to create the context
    /// \param[in] contextFlags the flags used to create the context
    CLGPAContext(cl_command_queue& clCommandQueue, GPA_HWInfo& hwInfo, GPA_OpenContextFlags contextFlags);

    /// Destructor
    ~CLGPAContext();

    /// \copydoc IGPAContext::CreateSession()
    GPA_SessionId CreateSession(GPA_Session_Sample_Type sampleType) override;

    /// \copydoc IGPAContext::DeleteSession()
    bool DeleteSession(GPA_SessionId sessionId) override;

    /// \copydoc IGPAContext::GetMaxGPASessions()
    gpa_uint32 GetMaxGPASessions() const override;

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

    /// Enable/disable the stable power state, using the stable clock mode specified when opening the context
    /// \param[in] useProfilingClocks true to use GPU clocks for profiling, false to use default clock mode
    /// \return GPA_STATUS_OK on success
    GPA_Status SetStableClocks(bool useProfilingClocks);

private:
    /// Parses a version number returned from clGetDeviceInfo(CL_DRIVER_VERSION)
    /// The string has the format: "2840.16 (PAL,HSAIL)", and we want to extract the "2840" portion.
    /// \param pVersion the version string to extract the number from
    /// \return 0 on failure, the build version number on success
    int ExtractDriverVersion(const char* pVersion) const;

    cl_command_queue       m_clCommandQueue;   ///< CL command queue for this context
    cl_device_id           m_clDeviceId;       ///< CL device id for this context
    cl_DeviceClockMode_AMD m_clockMode;        ///< GPU Clock mode
    int                    m_clDriverVersion;  ///> CL driver version
};

#endif  // _CL_GPA_CONTEXT_H_
