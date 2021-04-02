//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Base class to handle the scheduling of the D3D Query counters.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_DX11_GPA_COUNTER_SCHEDULER_DX11_H_
#define GPU_PERF_API_COUNTER_GENERATOR_DX11_GPA_COUNTER_SCHEDULER_DX11_H_

#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_base.h"

/// @brief Base class to handle the scheduling of the D3D Query counters.
class GpaCounterSchedulerDx11 : public GpaCounterSchedulerBase
{
public:
    /// @brief Constructor.
    GpaCounterSchedulerDx11();

    /// @copydoc GpaCounterSchedulerBase::EnableCounter()
    virtual GpaStatus EnableCounter(GpaUInt32 index) override;

    /// @copydoc GpaCounterSchedulerBase::DoDisableCounter()
    virtual GpaStatus DoDisableCounter(GpaUInt32 index) override;

    /// @copydoc GpaCounterSchedulerBase::DisableAllCounters()
    virtual void DisableAllCounters() override;

protected:
    /// @copydoc GpaCounterSchedulerBase::GetPreferredSplittingAlgorithm()
    ///
    /// For DirectX 11, the preferred splitting algorithm is the consolidated one.
    /// This keeps the overall number of passes down to a reasonable number, but splits the counters up
    /// in a manner that allows them to be more consistent.
    virtual GpaCounterSplitterAlgorithm GetPreferredSplittingAlgorithm() const override;
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_DX11_GPA_COUNTER_SCHEDULER_DX11_H_
