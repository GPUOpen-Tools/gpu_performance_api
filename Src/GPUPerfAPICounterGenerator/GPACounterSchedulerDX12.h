//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Class for counter scheduling for DX12
//==============================================================================

#ifndef _GPA_COUNTER_SCHEDULER_DX12_H_
#define _GPA_COUNTER_SCHEDULER_DX12_H_

#include "GPACounterSchedulerBase.h"

/// Class for counter scheduling for DX12
class GPA_CounterSchedulerDX12 : public GPA_CounterSchedulerBase
{
public:
    /// Constructor
    GPA_CounterSchedulerDX12();

protected:
    /// For DirectX 12, the preferred splitting algorithm is the consolidated one.
    /// This keeps the overall number of passes down to a reasonable number, but splits the counters up
    /// in a manner that allows them to be more consistent.
    /// \copydoc GPA_CounterSchedulerBase::GetPreferredSplittingAlgorithm
    virtual GPACounterSplitterAlgorithm GetPreferredSplittingAlgorithm() const override;
};

#endif  // _GPA_COUNTER_SCHEDULER_DX12_H_
