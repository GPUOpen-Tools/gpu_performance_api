//==============================================================================
// Copyright (c) 2016-2021 Advanced Micro Devices, Inc. All rights reserved.
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
    GenerationGeneratorMap local_map;

    if (0 < counter_generator_items_.count(api_type))
    {
        local_map = counter_generator_items_[api_type];
    }

    if (0 == local_map.count(generation) || replace_existing)
    {
        local_map[generation] = counter_generator;
    }

    counter_generator_items_[api_type] = local_map;
}

bool CounterGeneratorSchedulerManager::GetCounterGenerator(GpaApiType api_type, GDT_HW_GENERATION generation, GpaCounterGeneratorBase*& counter_generator_out)
{
    bool ret_val = false;

    if (0 < counter_generator_items_.count(api_type))
    {
        if (0 < counter_generator_items_[api_type].count(generation))
        {
            counter_generator_out = counter_generator_items_[api_type][generation];
            ret_val               = true;
        }
    }

    return ret_val;
}

void CounterGeneratorSchedulerManager::RegisterCounterScheduler(GpaApiType            api_type,
                                                                GDT_HW_GENERATION     generation,
                                                                IGpaCounterScheduler* counter_scheduler,
                                                                bool                  replace_existing)
{
    GenerationSchedulerMap local_map;

    if (0 < counter_scheduler_items_.count(api_type))
    {
        local_map = counter_scheduler_items_[api_type];
    }

    if (0 == local_map.count(generation) || replace_existing)
    {
        local_map[generation] = counter_scheduler;
    }

    counter_scheduler_items_[api_type] = local_map;
}

bool CounterGeneratorSchedulerManager::GetCounterScheduler(GpaApiType api_type, GDT_HW_GENERATION generation, IGpaCounterScheduler*& counter_scheduler_out)
{
    bool ret_val = false;

    if (0 < counter_scheduler_items_.count(api_type))
    {
        if (0 < counter_scheduler_items_[api_type].count(generation))
        {
            counter_scheduler_out = counter_scheduler_items_[api_type][generation];
            ret_val               = true;
        }
    }

    return ret_val;
}
