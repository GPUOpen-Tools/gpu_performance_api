//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Singleton class containing globals used by the HSA version of GPUPerfAPI
//==============================================================================

#ifndef _GPUPERFAPI_HSA_GLOBALS_H_
#define _GPUPERFAPI_HSA_GLOBALS_H_

#include <TSingleton.h>

#include <map>

#include "../GPUPerfAPI-Common/GPUPerfAPITypes.h"

/// Singleton class containing globals used by the HSA version of GPUPerfAPI
class HSAGlobalFlags : public TSingleton <HSAGlobalFlags>
{
public:
    typedef std::map<hsa_queue_t*, hsa_agent_t> HSAQueueAgentMapType; ///< Typedef for a map from queue to agent
    static const gpa_uint32 ms_UNDEFINED_SAMPLE_ID = 0xFFFFFFFF;      ///< Const for undefined sample id

    bool                 m_softCPModeEnabled = false;         ///< flag indicating whether SoftCP mode is enabled
    bool                 m_isToolsLibSet = false;             ///< flag indicating whether the tools lib env variable is set
    bool                 m_wasInitializeCalled = false;       ///< flag indicating whether GPA_Initialize was called
    gpa_uint32           m_sampleID = ms_UNDEFINED_SAMPLE_ID; ///< the sample id fo rthe active sample
    HSAQueueAgentMapType m_queueAgentMap;                     ///< map of queue to agent
};

#endif // _GPUPERFAPI_HSA_GLOBALS_H_
