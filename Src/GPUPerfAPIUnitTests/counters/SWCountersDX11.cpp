//==============================================================================
// Copyright (c) 2014-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  DX11 SW counters assignment
//==============================================================================

#include "SWCountersDX11.h"

const GPACounterDesc DX11SW_COUNTERS[DX11SW_COUNTER_COUNT] =
{
    {"D3DGPUTime", "D3D11", "Time spent in GPU", GPA_DATA_TYPE_FLOAT64, GPA_USAGE_TYPE_MILLISECONDS},
    {"Occlusion", "D3D11", "Get the number of samples that passed the depth and stencil tests.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"IAVertices", "D3D11", "Number of vertices read by input assembler.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"IAPrimitives", "D3D11", "Number of primitives read by the input assembler.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"VSInvocations", "D3D11", "Number of times a vertex shader was invoked.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"GSInvocations", "D3D11", "Number of times a geometry shader was invoked.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"GSPrimitives", "D3D11", "Number of primitives output by a geometry shader.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"CInvocations", "D3D11", "Number of primitives that were sent to the rasterizer.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"CPrimitives", "D3D11", "Number of primitives that were rendered.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"PSInvocations", "D3D11", "Number of times a pixel shader was invoked.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"HSInvocations", "D3D11", "Number of times a hull shader was invoked.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"DSInvocations", "D3D11", "Number of times a domain shader was invoked.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"CSInvocations", "D3D11", "Number of times a compute shader was invoked.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"OcclusionPredicate", "D3D11", "Did any samples pass the depth and stencil tests?", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"PrimsWritten", "D3D11", "Number of primitives written to the stream-output buffers.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"PrimsStorageNeed", "D3D11", "Primitives not written to the SO buffers due to limited space.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"OverflowPred", "D3D11", "Determines if any of the streaming output buffers overflowed.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"PrimsWritten_S0", "D3D11", "Number of primitives written to the stream 0 buffer.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"PrimsStorageNeed_S0", "D3D11", "Primitives not written to stream 0 due to limited space.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"OverflowPred_S0", "D3D11", "Determines if the stream 0 buffer overflowed.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"PrimsWritten_S1", "D3D11", "Number of primitives written to the stream 1 buffer.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"PrimsStorageNeed_S1", "D3D11", "Primitives not written to stream 1 due to limited space.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"OverflowPred_S1", "D3D11", "Determines if the stream 1 buffer overflowed.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"PrimsWritten_S2", "D3D11", "Number of primitives written to the stream 2 buffer.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"PrimsStorageNeed_S2", "D3D11", "Primitives not written to stream 2 due to limited space.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"OverflowPred_S2", "D3D11", "Determines if the stream 2 buffer overflowed.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"PrimsWritten_S3", "D3D11", "Number of primitives written to the stream 3 buffer.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"PrimsStorageNeed_S3", "D3D11", "Primitives not written to stream 3 due to limited space.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
    {"OverflowPred_S3", "D3D11", "Determines if the stream 3 buffer overflowed.", GPA_DATA_TYPE_UINT64, GPA_USAGE_TYPE_ITEMS},
};

