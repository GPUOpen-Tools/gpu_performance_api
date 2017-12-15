//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Base class to handle the scheduling of the D3D Query counters
//==============================================================================

#ifndef _GPA_COUNTER_SCHEDULER_DX11_H_
#define _GPA_COUNTER_SCHEDULER_DX11_H_

#include "GPACounterSchedulerBase.h"

/// Base class to handle the scheduling of the D3D Query counters
class GPA_CounterSchedulerDX11 : public GPA_CounterSchedulerBase
{
public:
    /// Constructor
    GPA_CounterSchedulerDX11();

    /// Overridden methods -- see base for documentation
    virtual GPA_Status EnableCounter(gpa_uint32 index);
    virtual GPA_Status DoDisableCounter(gpa_uint32 index);
    virtual void DisableAllCounters();

protected:
    /// For DirectX 11, the preferred splitting algorithm is the consolidated one.
    /// This keeps the overall number of passes down to a reasonable number, but splits the counters up
    /// in a manner that allows them to be more consistent.
    /// \return The splitting algorithm to use.
    virtual GPACounterSplitterAlgorithm GetPreferredSplittingAlgorithm() const;
};

#endif //_GPA_COUNTER_SCHEDULER_DX11_H_
