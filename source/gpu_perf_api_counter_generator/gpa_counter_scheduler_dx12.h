//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for counter scheduling for DX12.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_DX12_GPA_COUNTER_SCHEDULER_DX12_H_
#define GPU_PERF_API_COUNTER_GENERATOR_DX12_GPA_COUNTER_SCHEDULER_DX12_H_

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_base.h"

/// @brief Class for counter scheduling for DX12.
class GpaCounterSchedulerDx12 : public GpaCounterSchedulerBase
{
public:
    /// Constructor
    explicit GpaCounterSchedulerDx12(GpaSessionSampleType sample_type);

    /// @brief Delete default constructor.
    GpaCounterSchedulerDx12() = delete;
};

#endif
