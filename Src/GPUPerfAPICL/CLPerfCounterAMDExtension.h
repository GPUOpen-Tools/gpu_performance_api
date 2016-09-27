//==============================================================================
// Copyright (c) 2009-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A utility function to get the AMD internal performance counters' interface via
///         clGetExtensionFunctionAddress.
//==============================================================================

#ifndef _CLPERFCOUNTERAMDEXTENSION_H_
#define _CLPERFCOUNTERAMDEXTENSION_H_

/// typedef for clCreatePerfCounterAMD function pointer
typedef CL_API_ENTRY cl_perfcounter_amd(CL_API_CALL* pfn_clCreatePerfCounterAMD)(
    cl_device_id,
    cl_perfcounter_property*,
    cl_int*);

/// typedef for clReleasePerfCounterAMD function pointer
typedef CL_API_ENTRY cl_int(CL_API_CALL* pfn_clReleasePerfCounterAMD)(
    cl_perfcounter_amd);

/// typedef for clRetainPerfCounterAMD function pointer
typedef CL_API_ENTRY cl_int(CL_API_CALL* pfn_clRetainPerfCounterAMD)(
    cl_perfcounter_amd);

/// typedef for clEnqueueBeginPerfCounterAMD function pointer
typedef CL_API_ENTRY cl_int(CL_API_CALL* pfn_clEnqueueBeginPerfCounterAMD)(
    cl_command_queue,
    cl_uint,
    cl_perfcounter_amd*,
    cl_uint,
    const cl_event*,
    cl_event*);

/// typedef for clEnqueueEndPerfCounterAMD function pointer
typedef CL_API_ENTRY cl_int(CL_API_CALL* pfn_clEnqueueEndPerfCounterAMD)(
    cl_command_queue,
    cl_uint,
    cl_perfcounter_amd*,
    cl_uint,
    const cl_event*,
    cl_event*);

/// typedef for clGetPerfCounterInfoAMD function pointer
typedef CL_API_ENTRY cl_int(CL_API_CALL* pfn_clGetPerfCounterInfoAMD)(
    cl_perfcounter_amd,
    cl_perfcounter_info,
    size_t,
    void*,
    size_t*);

extern pfn_clCreatePerfCounterAMD       my_clCreatePerfCounterAMD;        ///< function pointer for clCreatePerfCounterAMD
extern pfn_clReleasePerfCounterAMD      my_clReleasePerfCounterAMD;       ///< function pointer for clReleasePerfCounterAMD
extern pfn_clRetainPerfCounterAMD       my_clRetainPerfCounterAMD;        ///< function pointer for clRetainPerfCounterAMD
extern pfn_clEnqueueBeginPerfCounterAMD my_clEnqueueBeginPerfCounterAMD;  ///< function pointer for clEnqueueBeginPerfCounterAMD
extern pfn_clEnqueueEndPerfCounterAMD   my_clEnqueueEndPerfCounterAMD;    ///< function pointer for clEnqueueEndPerfCounterAMD
extern pfn_clGetPerfCounterInfoAMD      my_clGetPerfCounterInfoAMD;       ///< function pointer for clGetPerfCounterInfoAMD

/// Initialize the AMD performance counters' function addresses
/// \param platform the platform whose extension is needed
/// \return true if successful, false otherwise
bool InitPerfCounterAMDExtension(cl_platform_id platform);

#endif
