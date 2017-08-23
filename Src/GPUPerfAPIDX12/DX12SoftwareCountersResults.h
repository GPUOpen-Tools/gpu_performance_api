//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Struct used to store DX12 query counter results
//==============================================================================

#ifndef _DX12_SOFTWARE_COUNTERS_RESULTS_H_
#define _DX12_SOFTWARE_COUNTERS_RESULTS_H_

#include <Windows.h>
#include <D3D12.h>

/// Struct used to store DX12 query counter results
struct DX12SoftwareCountersResults
{
    /// Offset of the Occlusion query results
    static const UINT64 OcclusionOffset = 0;

    /// Offset of the BinaryOcclusion query results
    static const UINT64 BinaryOcclusionOffset = OcclusionOffset + sizeof(UINT64);

    /// Offset of the TimestampBegin query results
    static const UINT64 TimestampBeginOffset = BinaryOcclusionOffset + sizeof(UINT64);

    /// Offset of the TimestampEnd query results
    static const UINT64 TimestampEndOffset = TimestampBeginOffset + sizeof(UINT64);

    /// Offset of the PipelineStatistics query results
    static const UINT64 PipelineStatisticsOffset = TimestampEndOffset + sizeof(UINT64);

    /// Offset of the QueryReadyEvent query results
    static const UINT64 QueryReadyEventOffset =
        PipelineStatisticsOffset + sizeof(D3D12_QUERY_DATA_PIPELINE_STATISTICS);

    UINT64 occlusion;                                        ///< Occlusion results
    UINT64 binaryOcclusion;                                  ///< BinaryOcclusion results
    UINT64 timestampBegin;                                   ///< TimestampBegin results
    UINT64 timestampEnd;                                     ///< TimestampEnd results
    D3D12_QUERY_DATA_PIPELINE_STATISTICS pipelineStatistics; ///< PipelineStatistics results
    UINT64 queryReadyEvent;                                  ///< QueryReadyEvent results
};

#endif // _DX12_SOFTWARE_COUNTERS_RESULTS_H_

