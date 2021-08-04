//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for counter scheduling for CL.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_CL_GPA_COUNTER_SCHEDULER_CL_H_
#define GPU_PERF_API_COUNTER_GENERATOR_CL_GPA_COUNTER_SCHEDULER_CL_H_

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_base.h"

/// @brief Class for counter scheduling for CL.
class GpaCounterSchedulerCl : public GpaCounterSchedulerBase
{
public:
    /// @brief Constructor.
    GpaCounterSchedulerCl();

protected:
    /// @copydoc GpaCounterSchedulerBase::GetPreferredSplittingAlgorithm()
    ///
    /// For CL, the preferred splitting algorithm is the consolidated one.
    /// This keeps the overall number of passes down to a reasonable number, but splits the counters up
    /// in a manner that allows them to be more consistent.
    virtual GpaCounterSplitterAlgorithm GetPreferredSplittingAlgorithm() const override;
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_CL_GPA_COUNTER_SCHEDULER_CL_H_
