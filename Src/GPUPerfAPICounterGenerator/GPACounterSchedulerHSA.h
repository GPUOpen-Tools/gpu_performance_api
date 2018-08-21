//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for counter scheduling for HSA
//==============================================================================

#ifndef _GPA_COUNTER_SCHEDULER_HSA_H_
#define _GPA_COUNTER_SCHEDULER_HSA_H_

#include "GPACounterSchedulerBase.h"

/// Class for counter scheduling for HSA
class GPA_CounterSchedulerHSA : public GPA_CounterSchedulerBase
{
public:
    /// Constructor
    GPA_CounterSchedulerHSA();

protected:

    /// For HSA, the preferred splitting algorithm is the consolidated one.
    /// This keeps the overall number of passes down to a reasonable number, but splits the counters up
    /// in a manner that allows them to be more consistent.
    /// \copydoc GPA_CounterSchedulerBase::GetPreferredSplittingAlgorithm
    virtual GPACounterSplitterAlgorithm GetPreferredSplittingAlgorithm() const override;
};

#endif //_GPA_COUNTER_SCHEDULER_HSA_H_
