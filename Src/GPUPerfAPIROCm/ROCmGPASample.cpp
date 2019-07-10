//==============================================================================
// Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  ROCm GPA Sample Implementation
//==============================================================================

#include <cctype>
#include <sstream>

#include "rocprofiler.h"

#include "ROCmGPAContext.h"
#include "GPAHardwareCounters.h"
#include "GPAPass.h"
#include "ROCmGPASample.h"
#include "HSARTModuleLoader.h"
#include "GPAContextCounterMediator.h"
#include "GPUPerfAPIROCmGlobals.h"

ROCmGPASample::ROCmGPASample(GPAPass* pPass, IGPACommandList* pCmdList, GpaSampleType sampleType, ClientSampleId sampleId)
    : GPASample(pPass, pCmdList, sampleType, sampleId)
    , m_pROCmGpaContext(nullptr)
    , m_pDispatchData(nullptr)
{
    if (nullptr != pPass)
    {
        IGPASession* pGpaSession = pPass->GetGpaSession();

        if (nullptr != pGpaSession)
        {
            m_pROCmGpaContext = reinterpret_cast<ROCmGPAContext*>(pGpaSession->GetParentContext());
        }
    }
}

ROCmGPASample::~ROCmGPASample()
{
    DestroyBlockCounters();
}

bool ROCmGPASample::UpdateResults()
{
    bool isComplete = m_pDispatchData->m_isDataReady;

    if (isComplete)
    {
        CounterCount counterCount = GetPass()->GetEnabledCounterCount();

        gpa_uint64* pResultBuffer = GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer();

        // Get and set the result to m_counters
        for (gpa_uint32 i = 0; i < counterCount; ++i)
        {
            // copy results from m_pDispatchData to result buffer
            pResultBuffer[i] = m_pDispatchData->m_counterResults[i];
        }

        MarkAsCompleted();
        DestroyBlockCounters();
    }

    return isComplete;
}

std::string ROCmGPASample::GetRocmProfilerCounterName(const char* pGroupName, gpa_uint32 blockInstance, gpa_uint64 counterIndexInGroup) const
{
    std::stringstream ss;

    std::string cleanedGroupName(pGroupName);

    // first remove any numbers from group name (the block instance will be added below)
    cleanedGroupName.erase(std::remove_if(cleanedGroupName.begin(), cleanedGroupName.end(), (int (*)(int))std::isdigit), cleanedGroupName.end());

    ss << cleanedGroupName << "[" << blockInstance << "]:" << counterIndexInGroup;

    return ss.str();
}

bool ROCmGPASample::BeginRequest()
{
    bool success = false;

    if (nullptr != m_pROCmGpaContext)
    {
        CounterCount counterCount = GetPass()->GetEnabledCounterCount();

        rocprofiler_feature_t* pRocProfilerFeatures = new (std::nothrow) rocprofiler_feature_t[counterCount];

        if (nullptr == pRocProfilerFeatures)
        {
            GPA_LogError("Unable to allocate memory for ROCm counters.");
        }
        else
        {
            IGPACounterAccessor*        pCounterAccessor  = GPAContextCounterMediator::Instance()->GetCounterAccessor(m_pROCmGpaContext);
            const GPA_HardwareCounters* pHardwareCounters = pCounterAccessor->GetHardwareCounters();

            m_rocmCounters.clear();

            // Check number of groups
            gpa_uint32 numGroups = static_cast<gpa_uint32>(pHardwareCounters->m_groupCount);

            auto EnableROCmCounter = [&](const CounterIndex& counterIndex) -> bool {
                // need to Enable counters
                const GPA_HardwareCounterDescExt* pCounter = pCounterAccessor->GetHardwareCounterExt(counterIndex);

                gpa_uint32 groupIndex = pCounter->m_groupIdDriver;
                assert(groupIndex <= numGroups);

                if (groupIndex <= numGroups)
                {
                    // Check number of counters
                    gpa_uint64 numCounters = pHardwareCounters->m_pGroups[groupIndex].m_numCounters;
                    assert(pCounter->m_pHardwareCounter->m_counterIndexInGroup <= numCounters);

                    if (pCounter->m_pHardwareCounter->m_counterIndexInGroup <= numCounters)
                    {
                        std::string counterName = GetRocmProfilerCounterName(pHardwareCounters->m_pGroups[groupIndex].m_pName,
                                                                             pHardwareCounters->m_pGroups[groupIndex].m_blockInstance,
                                                                             pCounter->m_pHardwareCounter->m_counterIndexInGroup);
                        m_rocmCounters.push_back(counterName);
                    }
                }

                return true;
            };

            // Loop through requested counters and add them the the counter list
            GetPass()->IterateEnabledCounterList(EnableROCmCounter);

            if (m_rocmCounters.size() > 0)
            {
                rocprofiler_feature_t* pFeatures = new (std::nothrow) rocprofiler_feature_t[m_rocmCounters.size()];

                if (nullptr == pFeatures)
                {
                    GPA_LogError("Unable to allocate memory for ROCm counters.");
                }
                else
                {
                    for (size_t i = 0; i < m_rocmCounters.size(); i++)
                    {
                        pFeatures[i].kind              = ROCPROFILER_FEATURE_KIND_METRIC;
                        pFeatures[i].name              = m_rocmCounters[i].c_str();
                        pFeatures[i].parameters        = nullptr;
                        pFeatures[i].parameter_count   = 0;
                        pFeatures[i].data.result_int64 = 0;
                    }
                }

                m_pDispatchData = new (std::nothrow) DispatchData;

                if (nullptr == m_pDispatchData)
                {
                    GPA_LogError("Unable to allocate memory for dispatch data.");
                }
                else
                {
                    m_pDispatchData->m_pFeatures    = pFeatures;
                    m_pDispatchData->m_featureCount = static_cast<unsigned int>(m_rocmCounters.size());
                    m_pDispatchData->m_groupIndex   = 0;  // groupIndex shouldn't be needed since GPA splits counters among passes itself

                    if (ROCmGlobalFlags::Instance()->m_wasInitializeCalled)
                    {
                        ROCProfilerModule* pROCProfilerModule = ROCProfilerModuleLoader::Instance()->GetAPIRTModule();

                        if (nullptr == pROCProfilerModule || !pROCProfilerModule->IsModuleLoaded())
                        {
                            GPA_LogError("ROC Profiler module is not loaded.");
                        }
                        else
                        {
                            rocprofiler_queue_callbacks_t queueCallbacks;
                            queueCallbacks.dispatch = DispatchCallback;
                            queueCallbacks.destroy  = QueueDestroyCallback;

                            hsa_status_t status = pROCProfilerModule->rocprofiler_set_queue_callbacks(queueCallbacks, m_pDispatchData);

                            if (HSA_STATUS_SUCCESS != status)
                            {
                                GPA_LogError("Unable to set queue callbacks.");
                            }
                            else
                            {
                                success = true;
                            }
                        }
                    }
                    else
                    {
                        rocprofiler_callback_data_t callbackData;
                        callbackData.agent = *m_pROCmGpaContext->ROCmContext().m_pAgent;
                        DispatchCallback(&callbackData, m_pDispatchData, nullptr);
                        success = true;
                    }
                }
            }
        }
    }

    return success;
}

bool ROCmGPASample::EndRequest()
{
    TRACE_PRIVATE_FUNCTION(ROCmGPASample::EndRequest);

    bool success = true;
    return success;
}

void ROCmGPASample::ReleaseCounters()
{
    DestroyBlockCounters();
}

void ROCmGPASample::DestroyBlockCounters()
{
    TRACE_PRIVATE_FUNCTION(ROCmGPASample::ReleaseBlockCounters);
    delete m_pDispatchData;
    m_pDispatchData = nullptr;
}

hsa_status_t ROCmGPASample::DispatchCallback(const rocprofiler_callback_data_t* pCallbackData, void* pUserData, rocprofiler_group_t* pGroup)
{
    hsa_status_t status = HSA_STATUS_ERROR;

    ROCProfilerModule* pROCProfilerModule = ROCProfilerModuleLoader::Instance()->GetAPIRTModule();

    if (nullptr == pROCProfilerModule || !pROCProfilerModule->IsModuleLoaded())
    {
        GPA_LogError("ROC Profiler module is NULL.");
    }
    else
    {
        DispatchData* pDispatchData = reinterpret_cast<DispatchData*>(pUserData);
        assert(nullptr != pDispatchData && nullptr != pCallbackData);

        if (nullptr == pDispatchData || nullptr == pCallbackData)
        {
            return status;
        }

        rocprofiler_t* pContext = nullptr;

        rocprofiler_properties_t properties = {};
        properties.handler                  = DispatchCompletionCallback;
        properties.handler_arg              = reinterpret_cast<void*>(pDispatchData);

        status =
            pROCProfilerModule->rocprofiler_open(pCallbackData->agent, pDispatchData->m_pFeatures, pDispatchData->m_featureCount, &pContext, 0, &properties);

        if (HSA_STATUS_SUCCESS == status)
        {
            if (nullptr != ROCmGlobalFlags::Instance()->m_pSetContextCallback)
            {
                ROCmGlobalFlags::Instance()->m_pSetContextCallback(pContext);
                pDispatchData->m_pContext = pContext;
            }
            else
            {
                uint32_t groupCount = 0;
                status              = pROCProfilerModule->rocprofiler_group_count(pContext, &groupCount);
                assert(groupCount == 1);

                if (HSA_STATUS_SUCCESS == status)
                {
                    const uint32_t groupIndex = 0;
                    status                    = pROCProfilerModule->rocprofiler_get_group(pContext, groupIndex, pGroup);

                    if (HSA_STATUS_SUCCESS == status)
                    {
                        pDispatchData->m_group = *pGroup;
                    }
                    else
                    {
                        GPA_LogError("Unable to retrieve the rocprofiler group.");
                    }
                }
                else
                {
                    GPA_LogError("Unable to query rocprofiler group count.");
                }
            }
        }
        else
        {
            GPA_LogError("Unable to open rocprofiler library.");
        }
    }

    return status;
}

hsa_status_t ROCmGPASample::QueueDestroyCallback(hsa_queue_t*, void*)
{
    // no implementation needed
    return HSA_STATUS_SUCCESS;
}

bool ROCmGPASample::DispatchCompletionCallback(rocprofiler_group_t group, void* pUserData)
{
    bool               retVal             = false;
    hsa_status_t       status             = HSA_STATUS_ERROR;
    ROCProfilerModule* pROCProfilerModule = ROCProfilerModuleLoader::Instance()->GetAPIRTModule();

    if (nullptr == pROCProfilerModule || !pROCProfilerModule->IsModuleLoaded())
    {
        GPA_LogError("ROC Profiler module is NULL.");
    }
    else
    {
        DispatchData* pDispatchData = reinterpret_cast<DispatchData*>(pUserData);

        if (ROCmGlobalFlags::Instance()->m_wasInitializeCalled)
        {
            status = pROCProfilerModule->rocprofiler_remove_queue_callbacks();
        }
        else
        {
            status = HSA_STATUS_SUCCESS;
        }

        if (HSA_STATUS_SUCCESS == status)
        {
            const rocprofiler_feature_t* pFeatures = pDispatchData->m_pFeatures;

            if (nullptr != pFeatures)
            {
                rocprofiler_group_t localGroup;

                if (nullptr != pDispatchData->m_pContext)
                {
                    uint32_t groupCount = 0;
                    status              = pROCProfilerModule->rocprofiler_group_count(pDispatchData->m_pContext, &groupCount);
                    assert(groupCount == 1);

                    if (HSA_STATUS_SUCCESS == status)
                    {
                        const uint32_t groupIndex = 0;
                        status                    = pROCProfilerModule->rocprofiler_get_group(pDispatchData->m_pContext, groupIndex, &localGroup);

                        if (HSA_STATUS_SUCCESS != status)
                        {
                            GPA_LogError("Unable to retrieve the rocprofiler group.");
                        }
                    }
                    else
                    {
                        GPA_LogError("Unable to query rocprofiler group count.");
                    }
                }
                else
                {
                    localGroup = pDispatchData->m_group;
                }

                status = pROCProfilerModule->rocprofiler_group_get_data(&localGroup);

                if (HSA_STATUS_SUCCESS == status)
                {
                    status = pROCProfilerModule->rocprofiler_get_metrics(localGroup.context);  // is this needed?

                    if (HSA_STATUS_SUCCESS == status)
                    {
                        for (unsigned i = 0; i < pDispatchData->m_featureCount; ++i)
                        {
                            const rocprofiler_feature_t* pFeature = &pFeatures[i];

                            if (ROCPROFILER_DATA_KIND_INT64 == pFeature->data.kind)
                            {
                                uint64_t result = pFeature->data.result_int64;
                                pDispatchData->m_counterResults.push_back(result);

                                std::stringstream ss;
                                ss << "Result of " << pFeature->name << " is: " << result << ".";
                                GPA_LogDebugMessage(ss.str().c_str());
                            }
                        }

                        retVal = true;
                    }
                    else
                    {
                        GPA_LogError("Unable to get metrics.");
                    }
                }
                else
                {
                    GPA_LogError("Unable to get group.");
                }
            }

            status                       = pROCProfilerModule->rocprofiler_close(group.context);
            pDispatchData->m_isDataReady = true;
        }
        else
        {
            GPA_LogError("Unable to remove queue calbacks.");
        }
    }

    if (nullptr != ROCmGlobalFlags::Instance()->m_pDispatchCompleteCallback)
    {
        ROCmGlobalFlags::Instance()->m_pDispatchCompleteCallback();
    }

    return retVal;
}
