//==============================================================================
// Copyright (c) 2009-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A utility function to get the AMD internal performance counters'
///         interface via clGetExtensionFunctionAddress.
//==============================================================================

#ifndef _CL_PERF_COUNTER_AMD_EXTENSION_H_
#define _CL_PERF_COUNTER_AMD_EXTENSION_H_

typedef decltype(clCreatePerfCounterAMD)*       pfn_clCreatePerfCounterAMD;        ///< typedef for clCreatePerfCounterAMD function pointer
typedef decltype(clReleasePerfCounterAMD)*      pfn_clReleasePerfCounterAMD;       ///< typedef for clReleasePerfCounterAMD function pointer
typedef decltype(clRetainPerfCounterAMD)*       pfn_clRetainPerfCounterAMD;        ///< typedef for clRetainPerfCounterAMD function pointer
typedef decltype(clEnqueueBeginPerfCounterAMD)* pfn_clEnqueueBeginPerfCounterAMD;  ///< typedef for clEnqueueBeginPerfCounterAMD function pointer
typedef decltype(clEnqueueEndPerfCounterAMD)*   pfn_clEnqueueEndPerfCounterAMD;    ///< typedef for clEnqueueEndPerfCounterAMD function pointer
typedef decltype(clGetPerfCounterInfoAMD)*      pfn_clGetPerfCounterInfoAMD;       ///< typedef for clGetPerfCounterInfoAMD function pointer
typedef decltype(clSetDeviceClockModeAMD)*      pfn_clSetDeviceClockModeAMD;       ///< typedef for clSetDeviceClockModeAMD function pointer

extern pfn_clCreatePerfCounterAMD       my_clCreatePerfCounterAMD;        ///< function pointer for clCreatePerfCounterAMD
extern pfn_clReleasePerfCounterAMD      my_clReleasePerfCounterAMD;       ///< function pointer for clReleasePerfCounterAMD
extern pfn_clRetainPerfCounterAMD       my_clRetainPerfCounterAMD;        ///< function pointer for clRetainPerfCounterAMD
extern pfn_clEnqueueBeginPerfCounterAMD my_clEnqueueBeginPerfCounterAMD;  ///< function pointer for clEnqueueBeginPerfCounterAMD
extern pfn_clEnqueueEndPerfCounterAMD   my_clEnqueueEndPerfCounterAMD;    ///< function pointer for clEnqueueEndPerfCounterAMD
extern pfn_clGetPerfCounterInfoAMD      my_clGetPerfCounterInfoAMD;       ///< function pointer for clGetPerfCounterInfoAMD
extern pfn_clSetDeviceClockModeAMD      my_clSetDeviceClockModeAMD;       ///< function pointer for clSetDeviceClockModeAMD

/// Initialize the AMD performance counters' function addresses
/// \param platform the platform whose extension is needed
/// \return true if successful, false otherwise
bool InitPerfCounterAMDExtension(cl_platform_id platform);

#endif  // _CL_PERF_COUNTER_AMD_EXTENSION_H_
