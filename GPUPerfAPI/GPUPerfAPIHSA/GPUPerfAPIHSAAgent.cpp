//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
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

ApiTable* g_pOriginalApiTable; ///< original api table
ExtTable* g_pOriginalExtTable; ///< original extesion table

std::map<hsa_queue_t*, hsa_agent_t> g_queueAgentMap; ///< typedef for a map from queue to agent

/// replacement function for hsa_queue_create
hsa_status_t HSA_API
my_hsa_queue_create(hsa_agent_t agent, uint32_t size, hsa_queue_type_t type,
                    void(*pCallback)(hsa_status_t status, hsa_queue_t* pSource, void* pData),
                    void* pData, uint32_t private_segment_size,
                    uint32_t group_segment_size, hsa_queue_t** ppQueue)
{
    hsa_status_t retVal = g_pOriginalApiTable->hsa_queue_create_fn(agent, size, type, pCallback, pData, private_segment_size, group_segment_size, ppQueue);

    if (HSA_STATUS_SUCCESS == retVal)
    {
        HSAGlobalFlags::Instance()->m_queueAgentMap[*ppQueue] = agent;
    }

    return retVal;
}

/// exported function called when tools libs are loaded
extern "C" bool GPADLL_EXPORT OnLoad(ApiTable* pTable, uint64_t /*runtimeVersion*/, uint64_t /*failedToolCount*/, const char* const* /*pFailedToolNames*/)
{
    g_pOriginalApiTable = (ApiTable*)malloc(sizeof(ApiTable));
    memcpy(g_pOriginalApiTable, pTable, sizeof(ApiTable));

    g_pOriginalExtTable = (ExtTable*)malloc(sizeof(ExtTable));
    memcpy(g_pOriginalExtTable, pTable->std_exts_, sizeof(ExtTable));

    pTable->hsa_queue_create_fn = my_hsa_queue_create;

    return true;
}

/// exported function called when tools libs are unloaded
extern "C" void GPADLL_EXPORT OnUnload()
{
    free(g_pOriginalApiTable);
    free(g_pOriginalExtTable);
}
