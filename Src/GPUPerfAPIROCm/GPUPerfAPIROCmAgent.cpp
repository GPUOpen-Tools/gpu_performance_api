//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  ROCm Agent (tools lib) implementation
//==============================================================================

#include <cstdlib>
#include <cstring>

#include <hsa_api_trace.h>

#ifdef _LINUX
    #define GPALIB_DECL extern "C"
#else
    #define GPALIB_DECL extern "C" __declspec( dllexport )
#endif

#include "GPUPerfAPIROCmGlobals.h"

decltype(hsa_queue_create)* g_realQueueCreateFn = nullptr; ///< pointer to the real hsa_queue_create function

std::map<hsa_queue_t*, hsa_agent_t> g_queueAgentMap; ///< typedef for a map from queue to agent

/// replacement function for hsa_queue_create
/// \param agent parameter to hsa_queue_create
/// \param size parameter to hsa_queue_create
/// \param type parameter to hsa_queue_create
/// \param pCallback parameter to hsa_queue_create
/// \param pData parameter to hsa_queue_create
/// \param private_segment_size parameter to hsa_queue_create
/// \param group_segment_size parameter to hsa_queue_create
/// \param ppQueue parameter to hsa_queue_create
/// \return the hsa_status_t result of the real API function
hsa_status_t HSA_API
my_hsa_queue_create(hsa_agent_t agent, uint32_t size, hsa_queue_type32_t type,
                    void(*pCallback)(hsa_status_t status, hsa_queue_t* pSource, void* pData),
                    void* pData, uint32_t private_segment_size,
                    uint32_t group_segment_size, hsa_queue_t** ppQueue)
{
    hsa_status_t retVal = g_realQueueCreateFn(agent, size, type, pCallback, pData, private_segment_size, group_segment_size, ppQueue);

    if (HSA_STATUS_SUCCESS == retVal)
    {
        ROCmGlobalFlags::Instance()->m_queueAgentMap[*ppQueue] = agent;
    }

    return retVal;
}

/// exported function called when tools libs are loaded
/// \param pTable pointer to hsa function table
/// \param runtimeVersion the major version of the HSA runtime
/// \return true if the hsa_queue_create function can be replaced
GPALIB_DECL bool OnLoad(void* pTable, uint64_t runtimeVersion, uint64_t /*failedToolCount*/, const char* const* /*pFailedToolNames*/)
{
    bool retVal = 0 < runtimeVersion;

    if (retVal)
    {
        g_realQueueCreateFn = reinterpret_cast<HsaApiTable*>(pTable)->core_->hsa_queue_create_fn;
        reinterpret_cast<HsaApiTable*>(pTable)->core_->hsa_queue_create_fn = my_hsa_queue_create;
    }

    return retVal;
}

/// exported function called when tools libs are unloaded
GPALIB_DECL void OnUnload()
{
}

/// exported function calles when rocprofiler tools lib are loaded
GPALIB_DECL void OnLoadTool()
{
    // not needed, but rocprofiler library requires tool libraries to export OnLoadTool and OnUnloadTool
}

/// exported function calles when rocprofiler tools lib are unloaded
GPALIB_DECL void OnUnloadTool()
{
    // not needed, but rocprofiler library requires tool libraries to export OnLoadTool and OnUnloadTool
}

// The following 2 exported functions are required if the user of GPA is also intercepting
// dispatches using rocprofiler. For instance, RCP does this, so we need a way to pass
// interception callbacks/data between GPA and RCP.

/// exported function called to give GPA a callback function to be called when dispatches are complete
/// \param pDispatchCompleteCallback the callback function
GPALIB_DECL void SetROCmDispatchCompleteCallback(ROCmDispatchCompleteCallback pDispatchCompleteCallback)
{
    ROCmGlobalFlags::Instance()->m_pDispatchCompleteCallback = pDispatchCompleteCallback;
}

/// exported function called to give GPA a callback function to be called in order to share the rocprofiler context
/// \param pSetContextCallback the callback function
GPALIB_DECL void SetROCmSetContextCallback(ROCmSetContextCallback pSetContextCallback)
{
    ROCmGlobalFlags::Instance()->m_pSetContextCallback = pSetContextCallback;
}
