//==============================================================================
// Copyright (c) 2012-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  HSA Counter Data Request
//==============================================================================

#include <assert.h>

#include "HSACounterDataRequest.h"
#include "HSARTModuleLoader.h"

#include "Logging.h"
#include <sstream>
#include <string>


HSACounterDataRequest::HSACounterDataRequest()
    :  m_dataReadyCount(0),
       m_pCounters(nullptr),
       m_pmu(nullptr)
{
    TRACE_PRIVATE_FUNCTION(HSACounterDataRequest::CONSTRUCTOR);
}


HSACounterDataRequest::~HSACounterDataRequest()
{
    TRACE_PRIVATE_FUNCTION(HSACounterDataRequest::DESTRUCTOR);

    ReleaseCounters();

    if (nullptr != m_pCounters)
    {
        delete[] m_pCounters;
        m_pCounters = nullptr;
    }
}


void HSACounterDataRequest::ReleaseCounters()
{
    TRACE_PRIVATE_FUNCTION(HSACounterDataRequest::ReleaseCounters);

    // For HSA, we need to destroy all the counters being created in each group
    HsaCounterGroupMap::iterator git  = m_hsaGrpIdCtrGrpMap.begin();
    HsaCounterGroupMap::iterator gend = m_hsaGrpIdCtrGrpMap.end();

    for (; git != gend ; ++git)
    {
        // For each group
        hsa_status_t status = HSAToolsRTModuleLoader::Instance()->GetAPIRTModule()->ext_tools_destroy_all_counters(git->second);

        if (HSA_STATUS_SUCCESS != status)
        {
            GPA_LogError("Failed to destroy all perf counters.");
        }

        git->second = nullptr;
    }

    m_hsaGrpIdCtrGrpMap.clear();
}


bool HSACounterDataRequest::CollectResults(GPA_CounterResults& resultStorage)
{
    TRACE_PRIVATE_FUNCTION(HSACounterDataRequest::CollectResults);

    HSAToolsRTModule* pHsaToolsRTModule = HSAToolsRTModuleLoader::Instance()->GetAPIRTModule();

    if (nullptr == pHsaToolsRTModule || !pHsaToolsRTModule->IsModuleLoaded())
    {
        GPA_LogError("HSA runtime module is NULL.");
        return false;
    }

    hsa_ext_tools_pmu_state_t state;
    hsa_status_t status = pHsaToolsRTModule->ext_tools_get_pmu_state(m_pmu, &state);

    if (HSA_STATUS_SUCCESS != status)
    {
        GPA_LogError("Failed to get perf counter state.");
        return false;
    }

    if (HSA_EXT_TOOLS_PMU_STATE_START == state)
    {
        // hsa_ext_tools_pmu_begin() has been called, but hsa_ext_tools_pmu_end() has not
        // results are not ready yet
        return false;
    }

    // Wait for data to be ready
    if (HSA_EXT_TOOLS_PMU_STATE_STOP == state)
    {
        const uint32_t TIME_OUT = 100;
        status = pHsaToolsRTModule->ext_tools_pmu_wait_for_completion(m_pmu, TIME_OUT);

        if (HSA_STATUS_SUCCESS != status)
        {
            // Time out
            return false;
        }
    }

    // Get and set the result to m_counters
    for (gpa_uint32 i = 0; i < m_activeCounters; ++i)
    {
        if (m_pCounters[i].m_isCounterResultReady)
        {
            continue;
        }

        uint64_t counterResult = 0;

        if (m_pCounters[i].m_isCounterValid)
        {
            status = pHsaToolsRTModule->ext_tools_get_counter_result(m_pCounters[i].m_hsaPerfCounter, &counterResult);

            if (HSA_STATUS_SUCCESS != status)
            {
                GPA_LogError("Failed to get perf counter result.");
                return false;
            }
        }

        resultStorage.m_pResultBuffer[i] = counterResult;

        m_pCounters[i].m_isCounterResultReady = true;
        ++m_dataReadyCount;
    }

    return m_dataReadyCount == m_activeCounters;
} // HSACounterDataRequest::CollectResults


void HSACounterDataRequest::Reset(
    gpa_uint32 selectionID,
    const vector<gpa_uint32>* pCounters)
{
    TRACE_PRIVATE_FUNCTION(HSACounterDataRequest::Reset);

    assert(!m_isRequestStarted);
    assert(!m_isRequestActive);
    assert(nullptr != pCounters);

    if (nullptr == pCounters)
    {
        return;
    }

    const gpa_uint32 newActiveCounters = static_cast<gpa_uint32>(pCounters->size());

    // We can only re-use resources if and only if the counters
    // are exactly the same.
    if (m_counterSelectionID != selectionID || m_activeCounters != newActiveCounters)
    {
        // Release existing counters
        ReleaseCounters();

        if (m_activeCounters != newActiveCounters)
        {
            // Reallocate buffers
            if (nullptr != m_pCounters)
            {
                delete[] m_pCounters;
                m_pCounters = nullptr;
            }

            m_pCounters = new(std::nothrow) HSACounter[newActiveCounters];

            if (nullptr == m_pCounters)
            {
                GPA_LogError("Unable to allocate memory for HSA counters.");
                return;
            }
        }

        m_counterSelectionID = selectionID;
        m_activeCounters = newActiveCounters;
    }

    assert(nullptr != m_pCounters);
    assert(m_activeCounters == newActiveCounters);

    for (gpa_uint32 i = 0 ; i < m_activeCounters ; ++i)
    {
        m_pCounters[i].m_isCounterResultReady = false;
    }

    m_dataReadyCount = 0;
} // HSACounterDataRequest::Reset


bool HSACounterDataRequest::BeginRequest(
    GPA_ContextState* pContextState,
    gpa_uint32 selectionID,
    const vector<gpa_uint32>* pCounters)
{
    TRACE_PRIVATE_FUNCTION(HSACounterDataRequest::Begin);

    assert(pContextState != nullptr);
    assert(pCounters != nullptr);

    if (!pContextState || !pCounters)
    {
        return false;
    }

    GPA_ContextStateHSA* pContextStateHSA = dynamic_cast<GPA_ContextStateHSA*>(pContextState);
    assert(pContextStateHSA != nullptr);

    if (pContextStateHSA == nullptr)
    {
        return false;
    }

    m_pmu = pContextStateHSA->m_pmu;

    assert(nullptr != m_pmu);

    if (nullptr == m_pmu)
    {
        return false;
    }

    HSAToolsRTModule* pHsaToolsRTModule = HSAToolsRTModuleLoader::Instance()->GetAPIRTModule();

    if (nullptr == pHsaToolsRTModule || !pHsaToolsRTModule->IsModuleLoaded())
    {
        GPA_LogError("HSA runtime module is NULL.");
        return false;
    }

    // Reset object since may be reused
    Reset(selectionID, pCounters);

    GPA_HardwareCounters* pHardwareCounters = getCurrentContext()->m_pCounterAccessor->GetHardwareCounters();

    // Check number of groups
    gpa_uint32 numGroups = (gpa_uint32)(pHardwareCounters->m_groupCount);

    hsa_status_t status;

    // Loop through requested counters and group them by their group id
    for (gpa_uint32 i = 0 ; i < m_activeCounters ; ++i)
    {
        bool isCounterValid = false;

        // need to Enable counters
        GPA_HardwareCounterDescExt* pCounter = getCurrentContext()->m_pCounterAccessor->GetHardwareCounterExt((*pCounters)[i]);

        gpa_uint32 groupIndex = pCounter->m_groupIdDriver;
        assert(groupIndex <= numGroups);

        if (groupIndex > numGroups)
        {
            return false;
        }

        // Check number of counters
        gpa_uint64 numCounters = pHardwareCounters->m_pGroups[groupIndex].m_numCounters;
        assert(pCounter->m_pHardwareCounter->m_counterIndexInGroup <= numCounters);

        if (pCounter->m_pHardwareCounter->m_counterIndexInGroup > numCounters)
        {
            return false;
        }

        hsa_ext_tools_counter_block_t block;
        status = pHsaToolsRTModule->ext_tools_get_counter_block_by_id(m_pmu, groupIndex, &block);

        hsa_ext_tools_counter_t counter = nullptr;

        if (HSA_STATUS_SUCCESS != status)
        {
            std::stringstream ss;
            ss << "Failed to get counter block for group: " << groupIndex << ".";
            GPA_LogError(ss.str().c_str());
        }
        else
        {
            // Check if we already have seen this group
            HsaCounterGroupMap::iterator it = m_hsaGrpIdCtrGrpMap.find(groupIndex);

            if (it == m_hsaGrpIdCtrGrpMap.end())
            {
                // If this is the first time seeing group, store this group in the map
                m_hsaGrpIdCtrGrpMap.insert(HsaCounterGroupMap::value_type(groupIndex, block));
            }

            // Create counter
            status = pHsaToolsRTModule->ext_tools_create_counter(block, &counter);

            if (HSA_STATUS_SUCCESS != status)
            {
                std::stringstream ss;
                ss << "Failed to create perf counter with index: "
                   << pCounter->m_pHardwareCounter->m_counterIndexInGroup
                   << " in group "
                   << groupIndex << ".";
                GPA_LogError(ss.str().c_str());
            }
            else
            {

                status = pHsaToolsRTModule->ext_tools_set_counter_parameter(counter,
                                                                            static_cast<uint32_t>(HSA_EXT_TOOLS_COUNTER_PARAMETER_EVENT_INDEX),
                                                                            sizeof(pCounter->m_pHardwareCounter->m_counterIndexInGroup),
                                                                            static_cast<void*>(&pCounter->m_pHardwareCounter->m_counterIndexInGroup));

                // Setup the counter
                if (HSA_STATUS_SUCCESS != status)
                {
                    std::stringstream ss;
                    ss << "Failed to setup counter with index: "
                       << pCounter->m_pHardwareCounter->m_counterIndexInGroup
                       << " in group "
                       << groupIndex << ".";
                    GPA_LogError(ss.str().c_str());
                }
                else
                {
                    // Enable the counter
                    status = pHsaToolsRTModule->ext_tools_set_counter_enabled(counter, true);

                    if (HSA_STATUS_SUCCESS != status)
                    {
                        std::stringstream ss;
                        ss << "Failed to enable counter with index: "
                           << pCounter->m_pHardwareCounter->m_counterIndexInGroup
                           << " in group "
                           << groupIndex << ".";
                        GPA_LogError(ss.str().c_str());
                    }
                    else
                    {
                        isCounterValid = true;
                    }
                }
            }
        }

        // Update the list of currently active counters
        m_pCounters[i].m_counterID       = (*pCounters)[i];
        m_pCounters[i].m_counterGroup    = pCounter->m_groupIndex;
        m_pCounters[i].m_counterIndex    = (gpa_uint32)pCounter->m_pHardwareCounter->m_counterIndexInGroup;
        m_pCounters[i].m_hsaPerfCounter  = counter;
        m_pCounters[i].m_isCounterValid  = isCounterValid;
    } // for each counter

    // Begin

    status = pHsaToolsRTModule->ext_tools_pmu_begin(m_pmu, pContextStateHSA->m_pQueue, pContextStateHSA->m_pAqlTranslationHandle, true);

    if (HSA_STATUS_SUCCESS != status)
    {
        GPA_LogError("Failed to begin perf counter request.");

        Reset(selectionID, pCounters);
        return false;
    }

    return true;
} //HSACounterDataRequest::BeginRequest


bool HSACounterDataRequest::EndRequest()
{
    TRACE_PRIVATE_FUNCTION(HSACounterDataRequest::End);

    GPA_ContextStateHSA* pContextStateHSA = dynamic_cast<GPA_ContextStateHSA*>(getCurrentContext());

    if (pContextStateHSA == nullptr)
    {
        return false;
    }

    hsa_status_t status = HSAToolsRTModuleLoader::Instance()->GetAPIRTModule()->ext_tools_pmu_end(m_pmu, pContextStateHSA->m_pQueue, pContextStateHSA->m_pAqlTranslationHandle);

    if (HSA_STATUS_SUCCESS != status)
    {
        GPA_LogError("Failed to end perf counter request.");
        return false;
    }

    return HSA_STATUS_SUCCESS == status;
}
