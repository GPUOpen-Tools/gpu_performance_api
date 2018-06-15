//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for HSA counter generation
//==============================================================================

#ifndef _GPA_COUNTER_GENERATOR_HSA_H_
#define _GPA_COUNTER_GENERATOR_HSA_H_

#include "GPACounterGeneratorBase.h"
#include "GPACounterGeneratorSchedulerManager.h"

/// The HSA-specific counter generator
class GPA_CounterGeneratorHSA : public GPA_CounterGeneratorBase
{

public:
    /// Constructor
    GPA_CounterGeneratorHSA();

protected:

    GPA_Status GeneratePublicCounters(
        GDT_HW_GENERATION desiredGeneration,
        GDT_HW_ASIC_TYPE asicType,
        gpa_uint8 generateAsicSpecificCounters,
        GPA_DerivedCounters* pPublicCounters) override;

    GPA_Status GenerateHardwareCounters(
        GDT_HW_GENERATION desiredGeneration,
        GDT_HW_ASIC_TYPE asicType,
        gpa_uint8 generateAsicSpecificCounters,
        GPA_HardwareCounters* pHardwareCounters) override;

    GPA_Status GenerateSoftwareCounters(
        GDT_HW_GENERATION desiredGeneration,
        GDT_HW_ASIC_TYPE asicType,
        gpa_uint8 generateAsicSpecificCounters,
        GPA_SoftwareCounters* pSoftwareCounters) override;
};

#endif //_GPA_COUNTER_GENERATOR_HSA_H_
