//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class that will get the correct Generator and Scheduler for an API/Generation combination
//==============================================================================

#include "GPACounterGeneratorSchedulerManager.h"

CounterGeneratorSchedulerManager::CounterGeneratorSchedulerManager()
{
}

CounterGeneratorSchedulerManager::~CounterGeneratorSchedulerManager()
{
}

void CounterGeneratorSchedulerManager::RegisterCounterGenerator(GPA_API_Type apiType, GDT_HW_GENERATION generation, GPA_CounterGeneratorBase* pCounterGenerator, bool replaceExisting)
{

    GenerationGeneratorMap localMap;

    if (0 < m_counterGeneratorItems.count(apiType))
    {
        localMap = m_counterGeneratorItems[apiType];
    }

    if (0 == localMap.count(generation) || replaceExisting == true)
    {
        localMap[generation] = pCounterGenerator;
    }

    m_counterGeneratorItems[apiType] = localMap;
}

bool CounterGeneratorSchedulerManager::GetCounterGenerator(GPA_API_Type apiType, GDT_HW_GENERATION generation, GPA_CounterGeneratorBase*& pCounterGeneratorOut)
{
    bool retVal = false;

    if (0 < m_counterGeneratorItems.count(apiType))
    {
        if (0 < m_counterGeneratorItems[apiType].count(generation))
        {
            pCounterGeneratorOut = m_counterGeneratorItems[apiType][generation];
            retVal = true;
        }
    }

    return retVal;
}

void CounterGeneratorSchedulerManager::RegisterCounterScheduler(GPA_API_Type apiType, GDT_HW_GENERATION generation, GPA_ICounterScheduler* pCounterScheduler, bool replaceExisting)
{
    GenerationSchedulerMap localMap;

    if (0 < m_counterSchedulerItems.count(apiType))
    {
        localMap = m_counterSchedulerItems[apiType];
    }

    if (0 == localMap.count(generation) || replaceExisting == true)
    {
        localMap[generation] = pCounterScheduler;
    }

    m_counterSchedulerItems[apiType] = localMap;
}

bool CounterGeneratorSchedulerManager::GetCounterScheduler(GPA_API_Type apiType, GDT_HW_GENERATION generation, GPA_ICounterScheduler*& pCounterSchedulerOut)
{
    bool retVal = false;

    if (0 < m_counterSchedulerItems.count(apiType))
    {
        if (0 < m_counterSchedulerItems[apiType].count(generation))
        {
            pCounterSchedulerOut = m_counterSchedulerItems[apiType][generation];
            retVal = true;
        }
    }

    return retVal;
}
