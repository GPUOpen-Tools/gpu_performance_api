//==============================================================================
// Copyright (c) 2018-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  GPA CL Context declarations
//==============================================================================

#ifndef _CL_GPA_CONTEXT_H_
#define _CL_GPA_CONTEXT_H_

#include <CL/cl.h>
#include <CL/internal/cl_profile_amd.h>

// GPA Common
#include "gpa_context.h"

/// Class for OpenCL GPA Context
class ClGpaContext : public GpaContext
{
public:
    /// Constructor
    /// @param [in] cl_command_queue the CL Command queue used to create the context
    /// @param [in] hw_info the hardware info used to create the context
    /// @param [in] context_flags the flags used to create the context
    ClGpaContext(cl_command_queue& cl_command_queue, GpaHwInfo& hw_info, GpaOpenContextFlags context_flags);

    /// Destructor
    ~ClGpaContext();

    /// @copydoc IGpaContext::CreateSession()
    GpaSessionId CreateSession(GpaSessionSampleType sample_type) override;

    /// @copydoc IGpaContext::DeleteSession()
    bool DeleteSession(GpaSessionId session_id) override;

    /// @copydoc IGpaContext::GetMaxGpaSessions()
    GpaUInt32 GetMaxGpaSessions() const override;

    /// @copydoc IGpaInterfaceTrait::GetApiType()
    GpaApiType GetApiType() const override;

    /// Initializes the OpenCL context
    /// @param [in] cl_device_id_param the CL Device ID for this context
    /// @return true if initialization is successful otherwise false
    bool Initialize(cl_device_id& cl_device_id_param);

    /// Gets the CL device id
    /// @return the CL device id
    const cl_device_id& GetClDeviceId() const;

    /// Gets the CL command queue
    /// @return the CL command queue
    const cl_command_queue& GetClCommandQueue() const;

    /// @copydoc IGpaContext::SetStableClocks()
    GpaStatus SetStableClocks(bool use_profiling_clocks) override;

private:
    /// Parses a version_str number returned from clGetDeviceInfo(CL_DRIVER_VERSION)
    /// The string has the format: "2840.16 (PAL,HSAIL)", and we want to extract the "2840" portion.
    /// @param version_str the version string to extract the number from
    /// @return 0 on failure, the build version number on success
    int ExtractDriverVersion(const char* version_str) const;

    cl_command_queue       cl_command_queue_;   ///< CL command queue for this context
    cl_device_id           cl_device_id_;       ///< CL device id for this context
    cl_DeviceClockMode_AMD clock_mode_;         ///< GPU Clock mode
    int                    cl_driver_version_;  ///< CL driver version
};

#endif  // _CL_GPA_CONTEXT_H_