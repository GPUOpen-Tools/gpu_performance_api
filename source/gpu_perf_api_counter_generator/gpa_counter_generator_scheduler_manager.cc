//==============================================================================
// Copyright (c) 2016-2024 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief Class that will get the correct Generator and Scheduler for an API/Generation combination.
//==============================================================================

#include "gpu_perf_api_counter_generator/gpa_counter_generator_scheduler_manager.h"

void CounterGeneratorSchedulerManager::RegisterCounterGenerator(GpaApiType               api_type,
                                                                GDT_HW_GENERATION        generation,
                                                                GpaCounterGeneratorBase* counter_generator,
                                                                bool                     replace_existing)
{
    ApiGenerationSampleType type{ api_type, generation, counter_generator->GetGeneratorSampleType()};

    auto iter = counter_generator_items_.find(type);
    if (counter_generator_items_.end() == iter || replace_existing)
    {
        counter_generator_items_[type] = counter_generator;
    }
}

bool CounterGeneratorSchedulerManager::GetCounterGenerator(GpaApiType                api_type,
                                                           GpaSessionSampleType      sample_type,
                                                           GDT_HW_GENERATION         generation,
                                                           GpaCounterGeneratorBase*& counter_generator_out)
{
    ApiGenerationSampleType type{api_type, generation, sample_type };

    auto iter = counter_generator_items_.find(type);
    if (counter_generator_items_.end() != iter)
    {
        counter_generator_out = iter->second;
    }

    return counter_generator_items_.end() != iter;
}

void CounterGeneratorSchedulerManager::RegisterCounterScheduler(GpaApiType            api_type,
                                                                GDT_HW_GENERATION     generation,
                                                                IGpaCounterScheduler* counter_scheduler,
                                                                bool                  replace_existing)
{
    ApiGenerationSampleType type{ api_type, generation, counter_scheduler->GetSampleType() };

    auto iter = counter_scheduler_items_.find(type);
    if (counter_scheduler_items_.end() == iter || replace_existing)
    {
        counter_scheduler_items_[type] = counter_scheduler;
    }
}

bool CounterGeneratorSchedulerManager::GetCounterScheduler(GpaApiType             api_type,
                                                           GpaSessionSampleType   sample_type,
                                                           GDT_HW_GENERATION      generation,
                                                           IGpaCounterScheduler*& counter_scheduler_out)
{
    ApiGenerationSampleType type{ api_type, generation, sample_type };
    auto                    iter = counter_scheduler_items_.find(type);
    if (counter_scheduler_items_.end() != iter)
    {
        counter_scheduler_out = iter->second;
    }

    return counter_scheduler_items_.end() != iter;
}
