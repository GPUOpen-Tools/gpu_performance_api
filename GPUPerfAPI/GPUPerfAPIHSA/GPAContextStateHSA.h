//==============================================================================
// Copyright (c) 2012-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  HSA Context State
//==============================================================================

#ifndef _GPA_CONTEXTSTATE_HSA_H_
#define _GPA_CONTEXTSTATE_HSA_H_

#include "../GPUPerfAPI-Common/GPAContextState.h"

#include "GPUPerfAPIHSA.h"

//------------------------------------------------------------------------------------
/// Maintains the available HSA internal counters for the currently installed hardware.
//------------------------------------------------------------------------------------
class GPA_ContextStateHSA : public GPA_ContextState
{
public:

    /// Constructor
    GPA_ContextStateHSA() : GPA_ContextState(), m_pDevice(nullptr), m_pmu(nullptr), m_pQueue(nullptr), m_pAqlTranslationHandle(nullptr)
    {
    };

    /// Pointer to HSA agent handle
    const hsa_agent_t* m_pDevice;

    /// Pointer to hsa PMU for the current device.
    hsa_ext_tools_pmu_t m_pmu;

    /// Pointer to hsa queue
    const hsa_queue_t* m_pQueue;

    /// Pointer to the AQL translation handle
    void* m_pAqlTranslationHandle;
};

#endif // _GPA_CONTEXTSTATE_HSA_H_
