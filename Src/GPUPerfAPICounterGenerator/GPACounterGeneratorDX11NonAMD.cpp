//==============================================================================
// Copyright (c) 2016-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Class for DX11 counter generation for non-AMD hardware (used simply to register the generator)
//==============================================================================

#include "GPACounterGeneratorDX11NonAMD.h"
#include "GPACounterGeneratorSchedulerManager.h"

GPA_CounterGeneratorDX11NonAMD::GPA_CounterGeneratorDX11NonAMD()
{
    GPA_CounterGeneratorBase::SetAllowedCounters(false, false, true); //enable sw counters

    CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(GPA_API_DIRECTX_11, GDT_HW_GENERATION_INTEL, this, false);  // allow future registrations to override this default one
    CounterGeneratorSchedulerManager::Instance()->RegisterCounterGenerator(GPA_API_DIRECTX_11, GDT_HW_GENERATION_NVIDIA, this, false); // allow future registrations to override this default one
}
