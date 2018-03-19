//==============================================================================
// Copyright (c) 2014-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX12 SW counters assignment
//==============================================================================

#include "SWCountersDX12.h"

const GPACounterDesc DX12SW_COUNTERS[DX12SW_COUNTER_COUNT] =
{
    {"D3DGPUTime", "D3D12", "Time spent in GPU", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS},
    {"PreBottomTimestamp", "D3D12", "Bottom of the pipeline GPU timestamp", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"PostBottomTimestamp", "D3D12", "Bottom of the pipeline GPU timestamp", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"Occlusion", "D3D12", "Get the number of samples that passed the depth and stencil tests.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"BinaryOcclusion", "D3D12", "True/false if any samples passed depth and stencil tests.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"IAVertices", "D3D12", "Number of vertices read by input assembler.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"IAPrimitives", "D3D12", "Number of primitives read by the input assembler.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"VSInvocations", "D3D12", "Number of times a vertex shader was invoked.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"GSInvocations", "D3D12", "Number of times a geometry shader was invoked.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"GSPrimitives", "D3D12", "Number of primitives output by a geometry shader.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"CInvocations", "D3D12", "Number of primitives that were sent to the rasterizer.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"CPrimitives", "D3D12", "Number of primitives that were rendered.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"PSInvocations", "D3D12", "Number of times a pixel shader was invoked.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"HSInvocations", "D3D12", "Number of times a hull shader was invoked.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"DSInvocations", "D3D12", "Number of times a domain shader was invoked.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"CSInvocations", "D3D12", "Number of times a compute shader was invoked.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
};

