//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  HSA GPA Sample Implementation
//==============================================================================

#include "HSAGPAContext.h"
#include "GPAHardwareCounters.h"
#include "GPAPass.h"
#include "HSAGPASample.h"
#include "HSARTModuleLoader.h"

HSAGPASample::HSAGPASample(GPAPass* pPass,
                           IGPACommandList* pCmdList,
                           GpaSampleType sampleType,
                           ClientSampleId sampleId) :
    GPASample(pPass, pCmdList, sampleType, sampleId),
    m_pHSACounters(nullptr),
    m_dataReadyCount(0)
{
    if (nullptr != pPass)
    {
        IGPASession* pGpaSession = pPass->GetGpaSession();

        if (nullptr != pGpaSession)
        {
            m_pHSAGpaContext = reinterpret_cast<HSAGPAContext*>(pGpaSession->GetParentContext());
        }
    }
}

HSAGPASample::~HSAGPASample()
{
    DestroyBlockCounters();
    delete[] m_pHSACounters;
}

bool HSAGPASample::UpdateResults()
{
    bool isComplete = false;

    HSAToolsRTModule* pHsaToolsRTModule = HSAToolsRTModuleLoader::Instance()->GetAPIRTModule();

    if (nullptr == pHsaToolsRTModule || !pHsaToolsRTModule->IsModuleLoaded())
    {
        GPA_LogError("HSA runtime module is NULL.");
        return false;
    }

    hsa_ext_tools_pmu_t pmu = m_pHSAGpaContext->GetHSAPMU();

    if (nullptr == pmu)
    {
        GPA_LogError("NULL PMU returned from the HSA Context.");
        return false;
    }

    hsa_ext_tools_pmu_state_t state;
    hsa_status_t status = pHsaToolsRTModule->ext_tools_get_pmu_state(pmu, &state);

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
        status = pHsaToolsRTModule->ext_tools_pmu_wait_for_completion(pmu, TIME_OUT);

        if (HSA_STATUS_SUCCESS != status)
        {
            // Time out
            return false;
        }
    }

    CounterCount counterCount = GetPass()->GetEnabledCounterCount();

    // Get and set the result to m_counters
    for (gpa_uint32 i = 0; i < counterCount; ++i)
    {
        if (m_pHSACounters[i].m_isCounterResultReady)
        {
            continue;
        }

        uint64_t counterResult = 0;

        if (m_pHSACounters[i].m_isCounterValid)
        {
            status = pHsaToolsRTModule->ext_tools_get_counter_result(m_pHSACounters[i].m_hsaPerfCounter, &counterResult);

            if (HSA_STATUS_SUCCESS != status)
            {
                GPA_LogError("Failed to get perf counter result.");
                return false;
            }
        }

        GetSampleResultLocation()->m_pResultBuffer[i] = counterResult;

        m_pHSACounters[i].m_isCounterResultReady = true;
        ++m_dataReadyCount;
    }

    isComplete = m_dataReadyCount == counterCount;

    if (isComplete)
    {
        MarkAsCompleted();
    }

    return isComplete;
}

bool HSAGPASample::BeginRequest()
{
    bool success = false;

    if (nullptr != m_pHSAGpaContext)
    {
        HSAToolsRTModule* pHsaToolsRTModule = HSAToolsRTModuleLoader::Instance()->GetAPIRTModule();

        if (nullptr == pHsaToolsRTModule || !pHsaToolsRTModule->IsModuleLoaded())
        {
            GPA_LogError("HSA runtime module is NULL.");
        }
        else
        {
            CounterCount counterCount = GetPass()->GetEnabledCounterCount();
            hsa_ext_tools_pmu_t pmu = m_pHSAGpaContext->GetHSAPMU();

            if (nullptr == pmu)
            {
                GPA_LogError("NULL PMU returned from the HSA Context.");
            }
            else
            {
                const GPA_HardwareCounters* pHardwareCounters = m_pHSAGpaContext->GetCounterAccessor()->GetHardwareCounters();

                // Check number of groups
                gpa_uint32 numGroups = static_cast<gpa_uint32>(pHardwareCounters->m_groupCount);

                m_pHSACounters = new(std::nothrow) HSACounter[counterCount];

                if (nullptr == m_pHSACounters)
                {
                    GPA_LogError("Unable to allocate memory for HSA counters.");
                }
                else
                {
                    hsa_status_t status;
                    bool HSAPerfMonitorCollectionStatus = true;
                    unsigned int enabledCounterIter = 0u;

                    auto PopulateHSAPerForEnabledCounters = [&](const CounterIndex& counterIndex)-> bool
                    {
                        bool bEnabledCounter = true;
                        bool isCounterValid = false;

                        // need to Enable counters
                        const GPA_HardwareCounterDescExt* pCounter = m_pHSAGpaContext->GetCounterAccessor()->GetHardwareCounterExt(counterIndex);

                        gpa_uint32 groupIndex = pCounter->m_groupIdDriver;
                        assert(groupIndex <= numGroups);

                        if (groupIndex > numGroups)
                        {
                            bEnabledCounter = false;
                        }
                        else
                        {
                            // Check number of counters
                            gpa_uint64 numCounters = pHardwareCounters->m_pGroups[groupIndex].m_numCounters;
                            assert(pCounter->m_pHardwareCounter->m_counterIndexInGroup <= numCounters);

                            if (pCounter->m_pHardwareCounter->m_counterIndexInGroup > numCounters)
                            {
                                bEnabledCounter = false;
                            }
                            else
                            {

                                hsa_ext_tools_counter_block_t block;
                                status = pHsaToolsRTModule->ext_tools_get_counter_block_by_id(pmu, groupIndex, &block);

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
                                m_pHSACounters[enabledCounterIter].m_counterID = counterIndex;
                                m_pHSACounters[enabledCounterIter].m_counterGroup = pCounter->m_groupIndex;
                                m_pHSACounters[enabledCounterIter].m_counterIndex = static_cast<gpa_uint32>(pCounter->m_pHardwareCounter->m_counterIndexInGroup);
                                m_pHSACounters[enabledCounterIter].m_hsaPerfCounter = counter;
                                m_pHSACounters[enabledCounterIter].m_isCounterValid = isCounterValid;
                                enabledCounterIter++;
                            }
                        }

                        HSAPerfMonitorCollectionStatus &= bEnabledCounter;
                        return bEnabledCounter;
                    };

                    // Loop through requested counters and group them by their group id
                    GetPass()->IterateEnabledCounterList(PopulateHSAPerForEnabledCounters);

                    if (HSAPerfMonitorCollectionStatus)
                    {
                        // Begin
                        status = pHsaToolsRTModule->ext_tools_pmu_begin(pmu, m_pHSAGpaContext->GetHSAContext().m_pQueue, m_pHSAGpaContext->GetHSAContext().m_pAqlTranslationHandle, true);

                        if (HSA_STATUS_SUCCESS != status)
                        {
                            GPA_LogError("Failed to begin perf counter request.");
                            //Reset(selectionID, pCounters);
                        }
                        else
                        {
                            success = true;
                        }
                    }
                }
            }
        }
    }

    return success;
}

bool HSAGPASample::EndRequest()
{
    TRACE_PRIVATE_FUNCTION(HSAGPASample::EndRequest);

    bool success = true;

    hsa_ext_tools_pmu_t pmu = m_pHSAGpaContext->GetHSAPMU();

    if (nullptr == pmu)
    {
        GPA_LogError("NULL PMU returned from the HSA Context.");
        success = false;
    }
    else
    {
        hsa_status_t status = HSAToolsRTModuleLoader::Instance()->GetAPIRTModule()->ext_tools_pmu_end(pmu, m_pHSAGpaContext->GetHSAContext().m_pQueue, m_pHSAGpaContext->GetHSAContext().m_pAqlTranslationHandle);

        if (HSA_STATUS_SUCCESS != status)
        {
            GPA_LogError("Failed to end perf counter request.");
            success = false;
        }
    }

    return success;
}

void HSAGPASample::ReleaseCounters()
{
    DestroyBlockCounters();
}

void HSAGPASample::DestroyBlockCounters()
{
    TRACE_PRIVATE_FUNCTION(HSAGPASample::ReleaseBlockCounters);

    // For HSA, we need to destroy all the counters being created in each group
    HsaCounterGroupMap::iterator git = m_hsaGrpIdCtrGrpMap.begin();
    HsaCounterGroupMap::iterator gend = m_hsaGrpIdCtrGrpMap.end();

    for (; git != gend; ++git)
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

