//==============================================================================
// Copyright (c) 2016-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class that will get the correct Generator and Scheduler for an API/Generation combination.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_COUNTER_GENERATOR_SCHEDULER_MANAGER_H_
#define GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_COUNTER_GENERATOR_SCHEDULER_MANAGER_H_

#include <map>

#include <DeviceInfo.h>
#include <TSingleton.h>

#include "gpu_performance_api/gpu_perf_api_types.h"

#include "gpu_perf_api_counter_generator/gpa_counter_generator_base.h"
#include "gpu_perf_api_counter_generator/gpa_counter_scheduler_interface.h"

/// @brief Class that will get the correct Generator and Scheduler for an API/Generation combination.
class CounterGeneratorSchedulerManager : public TSingleton<CounterGeneratorSchedulerManager>
{
    friend class TSingleton<CounterGeneratorSchedulerManager>;  ///< Friend declaration to allow access to the constructor.

public:
    /// @brief Registers an API/HwGen-specific counter generator.
    ///
    /// @param [in] api_type The API the generator is being registered for.
    /// @param [in] generation The hardware generation the generator is being registered for.
    /// @param [in] counter_generator The generator to register.
    /// @param [in] replace_existing Flag indicating whether an existing generator for the specified api/generation combination should be replaced by this one. If false, then this one is ignored if an existing registration is found.
    void RegisterCounterGenerator(GpaApiType api_type, GDT_HW_GENERATION generation, GpaCounterGeneratorBase* counter_generator, bool replace_existing = true);

    /// @brief Get the registered generator for the specified API/HwGen.
    ///
    /// @param [in] api_type The API whose generator is needed.
    /// @param [in] sampleType The sample type of the counters.
    /// @param [in] generation The hardware generation whose generator is needed.
    /// @param [out] counter_generator_out The generator registered for the specified API/HwGen.
    ///
    /// @return True if there is a generator registered for the API/HwGen, false otherwise.
    bool GetCounterGenerator(GpaApiType                api_type,
                             GpaSessionSampleType      sampleType,
                             GDT_HW_GENERATION         generation,
                             GpaCounterGeneratorBase*& counter_generator_out);

    /// @brief Registers an API/HwGen-specific counter scheduler.
    ///
    /// @param [in] api_type The API the scheduler is being registered for.
    /// @param [in] generation The hardware generation the scheduler is being registered for.
    /// @param [in] counter_scheduler The scheduler to register.
    /// @param [in] replace_existing Flag indicating whether an existing scheduler for the specified api/generation combination should be replaced by this one. If false, then this one is ignored if an existing registration is found.
    void RegisterCounterScheduler(GpaApiType api_type, GDT_HW_GENERATION generation, IGpaCounterScheduler* counter_scheduler, bool replace_existing = true);

    /// @brief Get the registered scheduler for the specified API/HwGen.
    ///
    /// @param [in] api_type The API whose scheduler is needed.
    /// @param [in] sampleType The sample type of the counters.
    /// @param [in] generation The hardware generation whose scheduler is needed.
    /// @param [out] counter_scheduler_out The scheduler registered for the specified API/HwGen.
    ///
    /// @return True if there is a scheduler registered for the API/HwGen, false otherwise.
    bool GetCounterScheduler(GpaApiType             api_type,
                             GpaSessionSampleType   sample_type,
                             GDT_HW_GENERATION      generation,
                             IGpaCounterScheduler*& counter_scheduler_out);

protected:
    /// @brief Constructor.
    CounterGeneratorSchedulerManager() = default;

    /// @brief Virtual destructor.
    virtual ~CounterGeneratorSchedulerManager() = default;

    /// Key tuple of API + Generation + Sample Type
    struct ApiGenerationSampleType
    {
        GpaApiType           m_api;
        GDT_HW_GENERATION    m_generation;
        GpaSessionSampleType m_sampleType;

        bool operator==(const ApiGenerationSampleType& sampleType) const
        {
            return m_api == sampleType.m_api && m_generation == sampleType.m_generation && m_sampleType == sampleType.m_sampleType;
        }

        bool operator<(const ApiGenerationSampleType& sampleType) const
        {
            return m_api < sampleType.m_api || ((m_api == sampleType.m_api) && m_generation < sampleType.m_generation) ||
                   ((m_api == sampleType.m_api) && (m_generation == sampleType.m_generation) && m_sampleType < sampleType.m_sampleType);
        }
    };

    /// Map of registered generators
    std::map<ApiGenerationSampleType, GpaCounterGeneratorBase*> counter_generator_items_;

    /// Map of registered schedulers
    std::map<ApiGenerationSampleType, IGpaCounterScheduler*> counter_scheduler_items_;
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_COUNTER_GENERATOR_SCHEDULER_MANAGER_H_
