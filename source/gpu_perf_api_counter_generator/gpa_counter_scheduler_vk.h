//==============================================================================
// Copyright (c) 2016-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Class for counter scheduling for VK
//==============================================================================

#ifndef _GPA_COUNTER_SCHEDULER_VK_H_
#define _GPA_COUNTER_SCHEDULER_VK_H_

#include "gpa_counter_scheduler_base.h"

/// Class for counter scheduling for VK
class GPA_CounterSchedulerVK : public GPA_CounterSchedulerBase
{
public:
    /// Constructor
    GPA_CounterSchedulerVK();

protected:
    /// For Vulkan, the preferred splitting algorithm is the consolidated one.
    /// This keeps the overall number of passes down to a reasonable number, but splits the counters up
    /// in a manner that allows them to be more consistent.
    /// \copydoc GPA_CounterSchedulerBase::GetPreferredSplittingAlgorithm
    virtual GPACounterSplitterAlgorithm GetPreferredSplittingAlgorithm() const override;
};

#endif  // _GPA_COUNTER_SCHEDULER_VK_H_
