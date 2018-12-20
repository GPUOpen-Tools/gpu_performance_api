//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Internal counter loader -- stub for open source build
//==============================================================================

#ifdef AMDT_INTERNAL

#include "GPADerivedCounters.h"

GPA_Status GPA_LoadInternalCounters(
    GPA_API_Type,
    GDT_HW_GENERATION,
    GDT_HW_ASIC_TYPE,
    gpa_uint8,
    GPA_DerivedCounters*)
{
    return GPA_STATUS_ERROR_FAILED;
}

#endif
