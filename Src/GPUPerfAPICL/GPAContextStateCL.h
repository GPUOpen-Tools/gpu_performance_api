//==============================================================================
// Copyright (c) 2009-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Maintains the available OpenCL internal counters for the currently installed hardware.
//==============================================================================

#ifndef _GPA_CONTEXTSTATE_CL_H_
#define _GPA_CONTEXTSTATE_CL_H_

#include "GPAContextState.h"

#include "GPUPerfAPICL.h"

/// Maintains the available OpenCL internal counters for the currently installed hardware.
class GPA_ContextStateCL : public GPA_ContextState
{
public:

    /// Initializes an instance of the GPA_ContextStateCL class.
    GPA_ContextStateCL() : m_clDevice(nullptr)
    {
    }

    /// The OpenCL device ID
    cl_device_id m_clDevice;
};

#endif // _GPA_CONTEXTSTATE_CL_H_

