//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
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
    /// @brief Constructor
    ///
    /// @param [in] sample_type The type of samples for which to schedule counters.
    explicit GpaCounterSchedulerGl(GpaSessionSampleType sample_type);

    /// @brief Delete default constructor.
    GpaCounterSchedulerGl() = delete;
};

#endif
