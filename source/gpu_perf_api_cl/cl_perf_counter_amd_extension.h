//==============================================================================
// Copyright (c) 2009-2018 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  A utility function to get the AMD internal performance counters'
///         interface via clGetExtensionFunctionAddress.
//==============================================================================

#ifndef _CL_PERF_COUNTER_AMD_EXTENSION_H_
#define _CL_PERF_COUNTER_AMD_EXTENSION_H_

typedef decltype(clCreatePerfCounterAMD)*       PfnClCreatePerfCounterAmd;        ///< typedef for clCreatePerfCounterAMD function pointer
typedef decltype(clReleasePerfCounterAMD)*      PfnClReleasePerfCounterAmd;       ///< typedef for clReleasePerfCounterAMD function pointer
typedef decltype(clRetainPerfCounterAMD)*       PfnClRetainPerfCounterAmd;        ///< typedef for clRetainPerfCounterAMD function pointer
typedef decltype(clEnqueueBeginPerfCounterAMD)* PfnClEnqueueBeginPerfCounterAmd;  ///< typedef for clEnqueueBeginPerfCounterAMD function pointer
typedef decltype(clEnqueueEndPerfCounterAMD)*   PfnClEnqueueEndPerfCounterAmd;    ///< typedef for clEnqueueEndPerfCounterAMD function pointer
typedef decltype(clGetPerfCounterInfoAMD)*      PfnClGetPerfCounterInfoAmd;       ///< typedef for clGetPerfCounterInfoAMD function pointer
typedef decltype(clSetDeviceClockModeAMD)*      PfnClSetDeviceClockModeAmd;       ///< typedef for clSetDeviceClockModeAMD function pointer

extern PfnClCreatePerfCounterAmd       my_cl_create_perf_counter_amd;         ///< function pointer for clCreatePerfCounterAMD
extern PfnClReleasePerfCounterAmd      my_cl_release_perf_counter_amd;        ///< function pointer for clReleasePerfCounterAMD
extern PfnClRetainPerfCounterAmd       my_cl_retain_perf_counter_amd;         ///< function pointer for clRetainPerfCounterAMD
extern PfnClEnqueueBeginPerfCounterAmd my_cl_enqueue_begin_perf_counter_amd;  ///< function pointer for clEnqueueBeginPerfCounterAMD
extern PfnClEnqueueEndPerfCounterAmd   my_cl_enqueue_end_perf_counter_amd;    ///< function pointer for clEnqueueEndPerfCounterAMD
extern PfnClGetPerfCounterInfoAmd      my_cl_get_perf_counter_info_amd;       ///< function pointer for clGetPerfCounterInfoAMD
extern PfnClSetDeviceClockModeAmd      my_cl_set_device_clock_mode_amd;       ///< function pointer for clSetDeviceClockModeAMD

/// Initialize the AMD performance counters' function addresses
/// @param platform the platform whose extension is needed
/// @return true if successful, false otherwise
bool InitPerfCounterAmdExtension(cl_platform_id platform);

#endif  // _CL_PERF_COUNTER_AMD_EXTENSION_H_
