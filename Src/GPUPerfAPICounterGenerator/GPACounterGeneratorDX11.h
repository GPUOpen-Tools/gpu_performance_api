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

    /// Overridden methods -- see base for documentation
    virtual GPA_Status GeneratePublicCounters(GDT_HW_GENERATION desiredGeneration, GPA_PublicCounters* pPublicCounters);
    virtual GPA_Status GenerateHardwareCounters(GDT_HW_GENERATION desiredGeneration, GPA_HardwareCounters* pHardwareCounters);
};

#endif //_GPA_COUNTER_GENERATOR_DX11_H_
