//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  HSA Agent (tools lib) implementation
//==============================================================================


#include <cstdlib>
#include <cstring>

#include <hsa_api_trace.h>

#include "GPUPerfAPIHSAGlobals.h"

#ifndef GPADLL_EXPORT
    #if defined(_WIN32) || defined(__CYGWIN__)
        #ifdef __GNUC__
            #define GPADLL_EXPORT __attribute__ ((dllexport))
        #else
            #define GPADLL_EXPORT __declspec(dllexport)
        #endif
    #else
        #if __GNUC__ >= 4
            #define GPADLL_EXPORT __attribute__ ((visibility ("default")))
        #else
            #define GPADLL_EXPORT
        #endif
    #endif
#endif //DLL_EXPORT

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
        HSAGlobalFlags::Instance()->m_queueAgentMap[*ppQueue] = agent;
    }

    return retVal;
}

/// exported function called when tools libs are loaded
/// \param pTable pointer to hsa function table
/// \param runtimeVersion the major version of the HSA runtime
/// \return true if the hsa_queue_create function can be replaced
extern "C" bool GPADLL_EXPORT OnLoad(void* pTable, uint64_t runtimeVersion, uint64_t /*failedToolCount*/, const char* const* /*pFailedToolNames*/)
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
extern "C" void GPADLL_EXPORT OnUnload()
{
}
