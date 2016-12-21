//==============================================================================
// Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Counter splitter for DX12
//==============================================================================

#ifndef _GPA_SPLITCOUNTERSCONSOLIDATEDDX12_H_
#define _GPA_SPLITCOUNTERSCONSOLIDATEDDX12_H_

#include "GPASplitCountersConsolidated.h"

/// Consolidated counter splitter for DX12
class GPASplitCountersConsolidatedDX12 : public GPASplitCountersConsolidated
{
public:
    /// Construct a consolidated DX12 counter splitter instance
    GPASplitCountersConsolidatedDX12(
        unsigned int gpuTimestampGroupIndex,
        unsigned int gpuTimestampBottomToBottomCounterIndex,
        unsigned int gpuTimestampTopToBottomCounterIndex,
        unsigned int maxSQCounters,
        unsigned int numSQGroups,
        GPA_SQCounterGroupDesc* pSQCounterBlockInfo);

    /// Destroy this consolidated DX12 counter splitter instance
    virtual ~GPASplitCountersConsolidatedDX12();

protected:
    virtual bool IsTimestampQueryCounter(const gpa_uint32 swCounterIndex) const;
}; // end of class GPASplitCountersConsolidatedDX12

#endif // _GPA_SPLITCOUNTERSCONSOLIDATEDDX12_H_

