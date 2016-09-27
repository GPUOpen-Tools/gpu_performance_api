//==============================================================================
// Copyright (c) 2014-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPACounterDesc declaration
//==============================================================================

#ifndef _GPA_TESTS_COUNTERS_GPACOUNTERDESC_H_
#define _GPA_TESTS_COUNTERS_GPACOUNTERDESC_H_

#include <GPUPerfAPITypes.h>

/// GPA public counter description
struct GPACounterDesc
{
    const char*    m_pName;        ///< Counter name
    const char*    m_pDescription; ///< Counter description
    GPA_Type       m_type;         ///< Counter type
    GPA_Usage_Type m_usage;        ///< Counter usage
}; // end of struct GPAPublicCounterDesc

#endif // _GPA_TESTS_COUNTERS_GPACOUNTERDESC_H_
