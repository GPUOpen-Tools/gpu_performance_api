//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Singleton class containing globals used by the ROCm version of GPUPerfAPI
//==============================================================================

#ifndef _GPUPERFAPI_ROCM_GLOBALS_H_
#define _GPUPERFAPI_ROCM_GLOBALS_H_

#include <TSingleton.h>

#include <map>

#include "GPUPerfAPITypes.h"
#include "GPUPerfAPI-ROCm.h"

/// Singleton class containing globals used by the ROCm version of GPUPerfAPI
class ROCmGlobalFlags : public TSingleton <ROCmGlobalFlags>
{
public:
    typedef std::map<hsa_queue_t*, hsa_agent_t> HSAQueueAgentMapType; ///< Typedef for a map from queue to agent

    bool                         m_rocpInterceptEnabled      = false;   ///< flag indicating whether ROCP interception enabled
    bool                         m_isToolsLibSet             = false;   ///< flag indicating whether the tools lib env variable is set
    bool                         m_wasInitializeCalled       = false;   ///< flag indicating whether GPA_Initialize was called
    HSAQueueAgentMapType         m_queueAgentMap;                       ///< map of queue to agent
    ROCmDispatchCompleteCallback m_pDispatchCompleteCallback = nullptr; ///< callback called when ROCm dispatch is complete
    ROCmSetContextCallback       m_pSetContextCallback       = nullptr; ///< callback called to set the RocProfiler context
};

#endif // _GPUPERFAPI_ROCM_GLOBALS_H_
