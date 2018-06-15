//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for DX11 counter generation for AMD HW
//==============================================================================

#ifndef _GPA_COUNTER_GENERATOR_DX11_H_
#define _GPA_COUNTER_GENERATOR_DX11_H_

#include "GPACounterGeneratorDX11Base.h"

/// Class for DX11 counter generation for AMD HW
class GPA_CounterGeneratorDX11 : public GPA_CounterGeneratorDX11Base
{
public:

    /// Constructor
    GPA_CounterGeneratorDX11();

protected:

    /// \copydoc GPA_CounterGeneratorBase::GeneratePublicCounters
    GPA_Status GeneratePublicCounters(
        GDT_HW_GENERATION desiredGeneration,
        GDT_HW_ASIC_TYPE asicType,
        gpa_uint8 generateAsicSpecificCounters,
        GPA_DerivedCounters* pPublicCounters) override;

    /// \copydoc GPA_CounterGeneratorBase::GenerateHardwareCounters
    GPA_Status GenerateHardwareCounters(
        GDT_HW_GENERATION desiredGeneration,
        GDT_HW_ASIC_TYPE asicType,
        gpa_uint8 generateAsicSpecificCounters,
        GPA_HardwareCounters* pHardwareCounters) override;
};

#endif //_GPA_COUNTER_GENERATOR_DX11_H_
