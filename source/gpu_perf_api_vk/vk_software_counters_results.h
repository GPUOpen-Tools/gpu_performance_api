//==============================================================================
// Copyright (c) 2015-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Struct used to store VK query counter results
//==============================================================================

#ifndef GPU_PERF_API_VK_VK_SOFTWARE_COUNTERS_RESULTS_H_
#define GPU_PERF_API_VK_VK_SOFTWARE_COUNTERS_RESULTS_H_

#include "gpu_perf_api_vk/vk_includes.h"

/// Enum of the different Vulkan queries used by GPA.
/// These are used as both identifiers and indexes into arrays of VkQueryPools.
/// These indices need to match up with the indices exposed in GpaCounterGeneratorVK::kVkSoftwareCounters
typedef enum
{
    kGpaVkQueryTypeOcclusion,           ///< Occlusion query, with the PRECISE flag.
    kGpaVkQueryTypeOcclusionBinary,     ///< Occlusion query, without the PRECISE flag.
    kGpaVkQueryTypeTimestamp,           ///< Timestamp query, will automatically enable both begin and end timestamps.
    kGpaVkQueryTypePipelineStatistics,  ///< Pipeline Statistics query, which collects the stats from the entire pipeline.
    kGpaVkQueryTypeCount                ///< The number of GPA_VK_SW_QUERY_TYPE types; not to be used as an actual enum value.
} GpaVkSwQueryType;

/// Struct used to store Vk query results.
struct GpaVkSoftwareQueryResults
{
    uint64_t occlusion;                                ///< Occlusion results.
    uint64_t occlusionAvailable;                       ///< Occlusion results are Available.
    uint64_t occlusionBinary;                          ///< Occlusion binary results.
    uint64_t occlusionBinaryAvailable;                 ///< Occlusion binary results are Available.
    uint64_t timestampBegin;                           ///< TimestampBegin results.
    uint64_t timestampBeginAvailable;                  ///< TimestampBegin results are available.
    uint64_t timestampEnd;                             ///< TimestampEnd results.
    uint64_t timestampEndAvailable;                    ///< TimestampEnd results are available.
    uint64_t inputAssemblyVertices;                    ///< Pipeline Stats: Input Assembly vertices results.
    uint64_t inputAssemblyPrimitives;                  ///< Pipeline Stats: Input Assembly primitives results.
    uint64_t vertexShaderInvocations;                  ///< Pipeline Stats: Vertex shader invocations results.
    uint64_t geometryShaderInvocations;                ///< Pipeline Stats: Geometry shader invocations results.
    uint64_t geometryShaderPrimitives;                 ///< Pipeline Stats: Geometry shader primitives results.
    uint64_t clippingInvocations;                      ///< Pipeline Stats: Clipping invocations results.
    uint64_t clippingPrimitives;                       ///< Pipeline Stats: Clipping primitives results.
    uint64_t fragmentShaderInvocations;                ///< Pipeline Stats: Gragment shader invocations results.
    uint64_t tessellationControlShaderPatches;         ///< Pipeline Stats: Tessellation control shader patches results.
    uint64_t tessellationEvaluationShaderInvocations;  ///< Pipeline Stats: Tessellation evaluation shader invocations results.
    uint64_t computeShaderInvocations;                 ///< Pipeline Stats: Compute shader invocations results.
    uint64_t pipelineStatsAvailable;                   ///< Pipeline Stats results are available.
};

/// An array whose indexes correspond to the GPA_VK_SW_QUERY_TYPE enums and
/// whose values indicate the memory size (in bytes) needed to store the results.
/// Occlusion queries only need two 64-bit uints (one for the result, and one for the availability bit).
/// Timestamps need four 64-bit uints because we collect both 'begin' and 'end' timestamps.
/// Pipeline Stats have 11 64-bit uint results, plus an availability bit.
static const size_t kGpaVkSoftwareResultSizes[] = {sizeof(uint64_t) * 2, sizeof(uint64_t) * 2, sizeof(uint64_t) * 4, sizeof(uint64_t) * 12};

/// An array whose indexes correspond to the GPA_VK_SW_QUERY_TYPE enums and
/// whose values indicate the memory stride (in bytes) to collect the query results.
/// Occlusion and Timestamps only need to stride two 64-bit uints (the result and the availability bit).
/// Pipeline Stat queries need to stride over all 11 results and the availability bit.
static const size_t kGpaVkSoftwareResultStrides[] = {sizeof(uint64_t) * 2, sizeof(uint64_t) * 2, sizeof(uint64_t) * 2, sizeof(uint64_t) * 12};

#endif  // GPU_PERF_API_VK_VK_SOFTWARE_COUNTERS_RESULTS_H_