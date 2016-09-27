//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  HSA Agent (tools lib) implementation
//==============================================================================


#include <cstdlib>
#include <cstring>

#include <hsa_api_trace.h>

#include "HSAAPITable1_0.h"
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

decltype(hsa_queue_create)* g_realQueueCreateFn = nullptr;

std::map<hsa_queue_t*, hsa_agent_t> g_queueAgentMap; ///< typedef for a map from queue to agent

/// replacement function for hsa_queue_create
hsa_status_t HSA_API
my_hsa_queue_create(hsa_agent_t agent, uint32_t size, hsa_queue_type_t type,
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
extern "C" bool GPADLL_EXPORT OnLoad(void* pTable, uint64_t runtimeVersion, uint64_t /*failedToolCount*/, const char* const* /*pFailedToolNames*/)
{

    if (0 == runtimeVersion)
    {
        g_realQueueCreateFn = reinterpret_cast<ApiTable1_0*>(pTable)->hsa_queue_create_fn;
        reinterpret_cast<ApiTable1_0*>(pTable)->hsa_queue_create_fn = my_hsa_queue_create;
    }
    else
    {
        g_realQueueCreateFn = reinterpret_cast<HsaApiTable*>(pTable)->core_->hsa_queue_create_fn;
        reinterpret_cast<HsaApiTable*>(pTable)->core_->hsa_queue_create_fn = my_hsa_queue_create;
    }

    return true;
}

/// exported function called when tools libs are unloaded
extern "C" void GPADLL_EXPORT OnUnload()
{
}
