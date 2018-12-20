//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief Get internal derived counters -- stub for open source build
//==============================================================================

#ifdef AMDT_INTERNAL

#include "GPADerivedCounters.h"

GPA_Status GPA_GetInternalDerivedCounters(
    GPA_API_Type,
    GPA_Hw_Generation,
    const GPACounterDesc**,
    size_t*)
{
    return GPA_STATUS_ERROR_FAILED;
}

#endif
