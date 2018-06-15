//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Struct used to store VK query counter results
//==============================================================================

#ifndef _VK_SOFTWARE_COUNTERS_RESULTS_H_
#define _VK_SOFTWARE_COUNTERS_RESULTS_H_

#include <vulkan/vulkan.h>

/// Enum of the different Vulkan queries used by GPA.
/// These are used as both identifiers and indexes into arrays of VkQueryPools.
/// These indices need to match up with the indices exposed in GPA_CounterGeneratorVK::s_VKSWCounters
typedef enum
{
    GPA_VK_QUERY_TYPE_OCCLUSION,            //!< Occlusion query, with the PRECISE flag
    GPA_VK_QUERY_TYPE_OCCLUSION_BINARY,     //!< Occlusion query, without the PRECISE flag
    GPA_VK_QUERY_TYPE_TIMESTAMP,            //!< Timestamp query, will automatically enable both begin and end timestamps
    GPA_VK_QUERY_TYPE_PIPELINE_STATISTICS,  //!< Pipeline Statistics query, which collects the stats from the entire pipeline
    GPA_VK_QUERY_TYPE_COUNT                 //!< The number of GPA_VK_SW_QUERY_TYPE types; not to be used as an actual enum value.
} GPA_VK_SW_QUERY_TYPE;

/// Struct used to store Vk query results
struct GpaVkSoftwareQueryResults
{
    uint64_t occlusion;                                        ///< Occlusion results
    uint64_t occlusionAvailable;                               ///< Occlusion results are Available
    uint64_t occlusionBinary;                                  ///< Occlusion binary results
    uint64_t occlusionBinaryAvailable;                         ///< Occlusion binary results are Available
    uint64_t timestampBegin;                                   ///< TimestampBegin results
    uint64_t timestampBeginAvailable;                          ///< TImestampBegin results are available
    uint64_t timestampEnd;                                     ///< TimestampEnd results
    uint64_t timestampEndAvailable;                            ///< TImestampEnd results are available
    uint64_t inputAssemblyVertices;                            ///< Pipeline Stats: Input Assembly vertices results
    uint64_t inputAssemblyPrimitives;                          ///< Pipeline Stats: Input Assembly primitives results
    uint64_t vertexShaderInvocations;                          ///< Pipeline Stats: vertex shader invocations results
    uint64_t geometryShaderInvocations;                        ///< Pipeline Stats: geometry shader invocations results
    uint64_t geometryShaderPrimitives;                         ///< Pipeline Stats: geometry shader primitives results
    uint64_t clippingInvocations;                              ///< Pipeline Stats: clipping invocations results
    uint64_t clippingPrimitives;                               ///< Pipeline Stats: clipping primitives results
    uint64_t fragmentShaderInvocations;                        ///< Pipeline Stats: fragment shader invocations results
    uint64_t tessellationControlShaderPatches;                 ///< Pipeline Stats: tessellation control shader patches results
    uint64_t tessellationEvaluationShaderInvocations;          ///< Pipeline Stats: tessellation evalutation shader invocations results
    uint64_t computeShaderInvocations;                         ///< Pipeline Stats: compute shader invocations results
    uint64_t pipelineStatsAvailable;                           ///< Pipeline Stats results are available
};

/// An array whose indexes correspond to the GPA_VK_SW_QUERY_TYPE enums and
/// whose values indicate the memory size (in bytes) needed to store the results.
/// Occlusion queries only need two 64-bit uints (one for the result, and one for the availability bit).
/// Timestamps need four 64-bit uints because we collect both 'begin' and 'end' timestamps.
/// Pipeline Stats have 11 64-bit uint results, plus an availablity bit.
static const size_t ms_gpaVkSoftwareResultSizes[] =
{
    sizeof(uint64_t) * 2,
    sizeof(uint64_t) * 2,
    sizeof(uint64_t) * 4,
    sizeof(uint64_t) * 12
};

/// An array whose indexes correspond to the GPA_VK_SW_QUERY_TYPE enums and
/// whose values indicate the memory stride (in bytes) to collect the query results.
/// Occlusion and Timestamps only need to stride two 64-bit uints (the result and the availability bit).
/// Pipeline Stat queries need to stride over all 11 results and the availability bit.
static const size_t ms_gpaVkSoftwareResultStrides[] =
{
    sizeof(uint64_t) * 2,
    sizeof(uint64_t) * 2,
    sizeof(uint64_t) * 2,
    sizeof(uint64_t) * 12
};

#endif // _VK_SOFTWARE_COUNTERS_RESULTS_H_

