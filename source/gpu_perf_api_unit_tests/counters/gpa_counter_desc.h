//==============================================================================
// Copyright (c) 2014-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  GPACounterDesc declaration
//==============================================================================

#ifndef _GPA_TESTS_COUNTERS_GPACOUNTERDESC_H_
#define _GPA_TESTS_COUNTERS_GPACOUNTERDESC_H_

#include <cstddef>
#include <GPUPerfAPITypes.h>

/// GPA public counter description
struct GPACounterDesc
{
    const char*    m_pName;                 ///< Counter name
    const char*    m_pGroup;                ///< Counter group name
    const char*    m_pDescription;          ///< Counter description
    const char*    m_pEqn;                  ///< Counter equation
    gpa_uint32     m_internalCounterCount;  ///< NUmber of internal counters required
    GPA_Data_Type  m_type;                  ///< Counter type
    GPA_Usage_Type m_usage;                 ///< Counter usage
    GPA_UUID       m_uuid;                  ///< Counter UUID
};

#endif  // _GPA_TESTS_COUNTERS_GPACOUNTERDESC_H_
