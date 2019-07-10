//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class that will get the correct Generator and Scheduler for an API/Generation combination
//==============================================================================

#ifndef _GPA_COUNTER_GENERATOR_SCHEDULER_MANAGER_H_
#define _GPA_COUNTER_GENERATOR_SCHEDULER_MANAGER_H_

#include <map>

#include <DeviceInfo.h>
#include <TSingleton.h>

#include "GPUPerfAPITypes.h"

class GPA_CounterGeneratorBase;  ///< forward declaration
class IGPACounterScheduler;      ///< forward declaration

/// Class that will get the correct Generator and Scheduler for an API/Generation combination
class CounterGeneratorSchedulerManager : public TSingleton<CounterGeneratorSchedulerManager>
{
    friend class TSingleton<CounterGeneratorSchedulerManager>;  ///< friend declaration to allow access to the constructor

public:
    /// Registers an API/HwGen-specific counter generator
    /// \param apiType the API the generator is being registered for
    /// \param generation the hardware generation the generator is being registered for
    /// \param pCounterGenerator the generator to register
    /// \param replaceExisting flag indicating whether an existing generator for the specified api/generation combination should be replaced by this one. If false, then this one is ignored if an existing registration is found
    void RegisterCounterGenerator(GPA_API_Type apiType, GDT_HW_GENERATION generation, GPA_CounterGeneratorBase* pCounterGenerator, bool replaceExisting = true);

    /// Get the registered generator for the specified API/HwGen
    /// \param apiType the API whose generator is needed
    /// \param generation the hardware generation whose generator is needed
    /// \param[out] pCounterGeneratorOut the generator registered for the specified API/HwGen
    /// \return true if there is a generator registered for the API/HwGen, false otherwise
    bool GetCounterGenerator(GPA_API_Type apiType, GDT_HW_GENERATION generation, GPA_CounterGeneratorBase*& pCounterGeneratorOut);

    /// Registers an API/HwGen-specific counter scheduler
    /// \param apiType the API the scheduler is being registered for
    /// \param generation the hardware generation the scheduler is being registered for
    /// \param pCounterScheduler the scheduler to register
    /// \param replaceExisting flag indicating whether an existing scheduler for the specified api/generation combination should be replaced by this one. If false, then this one is ignored if an existing registration is found
    void RegisterCounterScheduler(GPA_API_Type apiType, GDT_HW_GENERATION generation, IGPACounterScheduler* pCounterScheduler, bool replaceExisting = true);

    /// Get the registered scheduler for the specified API/HwGen
    /// \param apiType the API whose scheduler is needed
    /// \param generation the hardware generation whose scheduler is needed
    /// \param[out] pCounterSchedulerOut the scheduler registered for the specified API/HwGen
    /// \return true if there is a scheduler registered for the API/HwGen, false otherwise
    bool GetCounterScheduler(GPA_API_Type apiType, GDT_HW_GENERATION generation, IGPACounterScheduler*& pCounterSchedulerOut);

protected:
    /// Constructor
    CounterGeneratorSchedulerManager();

    /// Destructor
    virtual ~CounterGeneratorSchedulerManager();

    /// typedef for HWGen to Generator Map
    typedef std::map<GDT_HW_GENERATION, GPA_CounterGeneratorBase*> GenerationGeneratorMap;

    /// typedef for API to GenerationGeneratorMap Map
    typedef std::map<GPA_API_Type, GenerationGeneratorMap> APITypeGenerationGeneratorMap;

    /// Map of registered generators
    APITypeGenerationGeneratorMap m_counterGeneratorItems;

    /// typedef for HWGen to Scheduler Map
    typedef std::map<GDT_HW_GENERATION, IGPACounterScheduler*> GenerationSchedulerMap;

    /// typedef for HWGen to Scheduler Map
    typedef std::map<GPA_API_Type, GenerationSchedulerMap> APITypeGenerationSchedulerMap;

    /// Map of registered schedulers
    APITypeGenerationSchedulerMap m_counterSchedulerItems;
};

#endif  // _GPA_COUNTER_GENERATOR_SCHEDULER_MANAGER_H_
