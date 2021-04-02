//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for counter scheduling for GL.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_GL_GPA_COUNTER_SCHEDULER_GL_H_
#define GPU_PERF_API_COUNTER_GENERATOR_GL_GPA_COUNTER_SCHEDULER_GL_H_

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_base.h"

/// @brief Class for counter scheduling for GL.
class GpaCounterSchedulerGl : public GpaCounterSchedulerBase
{
public:
    /// @brief Constructor.
    GpaCounterSchedulerGl();

protected:
    /// @copydoc GpaCounterSchedulerBase::GetPreferredSplittingAlgorithm()
    ///
    /// For GL, the preferred splitting algorithm is the consolidated one.
    /// This keeps the overall number of passes down to a reasonable number, but splits the counters up
    /// in a manner that allows them to be more consistent.
    virtual GpaCounterSplitterAlgorithm GetPreferredSplittingAlgorithm() const override;
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_GL_GPA_COUNTER_SCHEDULER_GL_H_
