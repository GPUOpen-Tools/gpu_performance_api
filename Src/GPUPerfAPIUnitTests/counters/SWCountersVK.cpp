//==============================================================================
// Copyright (c) 2014-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  VK SW counters assignment
//==============================================================================

#include "SWCountersVK.h"

const GPACounterDesc VKSW_COUNTERS[VKSW_COUNTER_COUNT] =
{
    {"VKGPUTime", "VK", "Time spent in GPU", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS},
    {"PreBottomTimestamp", "VK", "Bottom of the pipeline GPU timestamp", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"PostBottomTimestamp", "VK", "Bottom of the pipeline GPU timestamp", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"Occlusion", "VK", "Get the number of samples that passed the depth and stencil tests.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"BinaryOcclusion", "VK", "True/false if any samples passed depth and stencil tests.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"IAVertices", "VK", "Number of vertices read by input assembler.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"IAPrimitives", "VK", "Number of primitives read by the input assembler.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"VSInvocations", "VK", "Number of times a vertex shader was invoked.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"GSInvocations", "VK", "Number of times a geometry shader was invoked.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"GSPrimitives", "VK", "Number of primitives output by a geometry shader.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"CInvocations", "VK", "Number of primitives that were sent to the rasterizer.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"CPrimitives", "VK", "Number of primitives that were rendered.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"PSInvocations", "VK", "Number of times a pixel shader was invoked.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"TCSInvocations", "VK", "Number of times a tessellation control shader was invoked.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"TESInvocations", "VK", "Number of times a tessellation evaluation shader was invoked.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"CSInvocations", "VK", "Number of times a compute shader was invoked.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
};

