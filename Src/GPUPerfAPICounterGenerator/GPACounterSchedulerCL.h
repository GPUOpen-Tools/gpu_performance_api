//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for counter scheduling for CL
//==============================================================================

#ifndef _GPA_COUNTER_SCHEDULER_CL_H_
#define _GPA_COUNTER_SCHEDULER_CL_H_

#include "GPACounterSchedulerBase.h"

/// Class for counter scheduling for CL
class GPA_CounterSchedulerCL : public GPA_CounterSchedulerBase
{
public:
    /// Constructor
    GPA_CounterSchedulerCL();

protected:
    /// For CL, the preferred splitting algorithm is the consolidated one.
    /// This keeps the overall number of passes down to a reasonable number, but splits the counters up
    /// in a manner that allows them to be more consistent.
    /// \return The splitting algorithm to use.
    virtual GPACounterSplitterAlgorithm GetPreferredSplittingAlgorithm() const;
};

#endif //_GPA_COUNTER_SCHEDULER_CL_H_
