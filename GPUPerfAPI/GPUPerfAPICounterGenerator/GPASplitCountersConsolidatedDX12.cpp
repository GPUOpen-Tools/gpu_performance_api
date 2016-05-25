//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Counter splitter for DX12
//==============================================================================

#include "GPASplitCountersConsolidatedDX12.h"

#include "GPACounterGeneratorDX12.h"

GPASplitCountersConsolidatedDX12::GPASplitCountersConsolidatedDX12(
    unsigned int gpuTimestampGroupIndex,
    unsigned int gpuTimestampBottomToBottomCounterIndex,
    unsigned int gpuTimestampTopToBottomCounterIndex,
    unsigned int maxSQCounters,
    unsigned int numSQGroups,
    GPA_SQCounterGroupDesc* pSQCounterBlockInfo)
    :
    GPASplitCountersConsolidated(
       gpuTimestampGroupIndex,
       gpuTimestampBottomToBottomCounterIndex,
       gpuTimestampTopToBottomCounterIndex,
       maxSQCounters,
       numSQGroups,
       pSQCounterBlockInfo)
{
} // end of GPASplitCountersConsolidatedDX12::GPASplitCountersConsolidatedDX12

GPASplitCountersConsolidatedDX12::~GPASplitCountersConsolidatedDX12()
{
} // end of GPASplitCountersConsolidatedDX12::~GPASplitCountersConsolidatedDX12

bool GPASplitCountersConsolidatedDX12::IsTimestampQueryCounter(const gpa_uint32 swCounterIndex) const
{
    bool isTimestampQueryCounter = GPASplitCountersConsolidated::IsTimestampQueryCounter(swCounterIndex);
    return isTimestampQueryCounter;
} // end of GPASplitCountersConsolidatedDX12::IsTimestampQueryCounter

