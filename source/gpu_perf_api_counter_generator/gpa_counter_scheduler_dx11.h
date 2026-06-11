//==============================================================================
// Copyright Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class for counter scheduling for DX11.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_DX11_GPA_COUNTER_SCHEDULER_DX11_H_
#define GPU_PERF_API_COUNTER_GENERATOR_DX11_GPA_COUNTER_SCHEDULER_DX11_H_

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_base.h"

/// @brief Class for counter scheduling for DX11.
class GpaCounterSchedulerDx11 : public GpaCounterSchedulerBase
{
public:
    /// @brief Constructor
    ///
    /// @param [in] sample_type The type of samples for which to schedule counters.
    explicit GpaCounterSchedulerDx11(GpaSessionSampleType sample_type);

    /// @copydoc GpaCounterSchedulerBase::EnableCounter()
    virtual GpaStatus EnableCounter(GpaUInt32 index) override;

    /// @copydoc GpaCounterSchedulerBase::DoDisableCounter()
    virtual GpaStatus DoDisableCounter(GpaUInt32 index) override;

    /// @copydoc GpaCounterSchedulerBase::DisableAllCounters()
    virtual void DisableAllCounters() override;

    /// @brief Delete default constructor.
    GpaCounterSchedulerDx11() = delete;
};

#endif
