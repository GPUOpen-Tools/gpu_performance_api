//==============================================================================
// Copyright (c) 2015-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  VkGpaSoftwareSample implementation
//==============================================================================

#include "gpu_perf_api_vk/vk_gpa_software_sample.h"

#include "gpu_perf_api_common/gpa_context_counter_mediator.h"

#include "gpu_perf_api_counter_generator/gpa_hardware_counters.h"
#include "gpu_perf_api_counter_generator/gpa_software_counters.h"

#include "gpu_perf_api_vk/vk_gpa_command_list.h"
#include "gpu_perf_api_vk/vk_gpa_context.h"
#include "gpu_perf_api_vk/vk_gpa_pass.h"

VkGpaSoftwareSample::VkGpaSoftwareSample(GpaPass* pass, IGpaCommandList* command_list, unsigned int sample_id)
    : VkGpaSample(pass, command_list, GpaSampleType::kSoftware, sample_id)
    , context_state_(nullptr)
    , active_counter_list_()
    , active_queries_(0)
    , command_list_(vk_gpa_command_list_->GetVkCommandBuffer())
    , sw_sample_id_(kUninitializedSampleId)
    , sw_queries_(nullptr)
{
}

VkGpaSoftwareSample::~VkGpaSoftwareSample()
{
    context_state_ = nullptr;
    active_counter_list_.clear();
    active_queries_ = 0;
    sw_sample_id_   = kUninitializedSampleId;
}

void VkGpaSoftwareSample::AssignQueries(VkCommandListSwQueries* sw_queries)
{
    sw_queries_ = sw_queries;
}

bool VkGpaSoftwareSample::BeginRequest()
{
    bool result = true;

    if ((nullptr != context_state_) || (nullptr == vk_gpa_command_list_))
    {
        result = false;
    }
    else
    {
        VkGpaPass* gpa_pass        = reinterpret_cast<VkGpaPass*>(GetPass());
        context_state_             = reinterpret_cast<VkGpaContext*>(gpa_pass->GetGpaSession()->GetParentContext());
        const size_t counter_count = gpa_pass->GetEnabledCounterCount();

        const IGpaCounterAccessor* counter_accessory = GpaContextCounterMediator::Instance()->GetCounterAccessor(context_state_);
        const GpaSoftwareCounters* sw_counters       = counter_accessory->GetSoftwareCounters();
        const GpaHardwareCounters* hw_counters       = counter_accessory->GetHardwareCounters();
        active_counter_list_.resize(counter_count);

        GpaUInt32 hw_counters_count = hw_counters->GetNumCounters();

        unsigned int counter_iter           = 0u;
        bool         counter_info_collected = true;

        auto populate_software_counter_info = [&](const CounterIndex& counter_index) -> bool {
            bool      is_counter_enabled             = true;
            GpaUInt32 sw_counter_index               = counter_index;
            active_counter_list_[counter_iter].index = SwCounterManager::Instance()->GetSwCounterPubIndex(sw_counter_index);

            // Software counter indices are after the hardware counter.
            GpaUInt32 counter_id_driver                   = sw_counters->software_counter_list_[sw_counter_index - hw_counters_count].counter_id_driver;
            active_counter_list_[counter_iter].query_type = static_cast<GpaVkSwQueryType>(counter_id_driver);
            is_counter_enabled                            = (counter_id_driver < sizeof(active_queries_));

            if (is_counter_enabled)
            {
                active_queries_ |= (0x1 << counter_id_driver);
            }

            counter_iter++;
            counter_info_collected &= is_counter_enabled;
            return is_counter_enabled;
        };

        gpa_pass->IterateEnabledCounterList(populate_software_counter_info);
        result = counter_info_collected;

        if (result)
        {
            unsigned int active_queries = active_queries_;
            bool         begin_query    = (0 != active_queries);
            result                      = sw_queries_->BeginSwSample(sw_sample_id_);

            if (result)
            {
                while (begin_query)
                {
                    GpaVkSwQueryType query_type;
#ifdef _WIN32
                    _BitScanForward(reinterpret_cast<unsigned long*>(&query_type), active_queries);
#else
                    query_type = static_cast<GpaVkSwQueryType>(__builtin_clz(active_queries));
#endif
                    sw_queries_->BeginSwQuery(sw_sample_id_, query_type);
                    active_queries &= ~(0x1 << static_cast<unsigned int>(query_type));
                    begin_query = (0 != active_queries);
                }
            }
        }
    }

    return result;
}

bool VkGpaSoftwareSample::EndRequest()
{
    bool result = true;

    if (nullptr == context_state_)
    {
        result = false;
    }
    else
    {
        unsigned int active_queries = active_queries_;
        bool         end_query      = (0 != active_queries);

        while (end_query)
        {
            GpaVkSwQueryType query_type;
#ifdef _WIN32
            _BitScanForward(reinterpret_cast<unsigned long*>(&query_type), active_queries);
#else
            query_type = static_cast<GpaVkSwQueryType>(__builtin_clz(active_queries));
#endif
            sw_queries_->EndSwQuery(sw_sample_id_, query_type);
            active_queries &= ~(0x1 << static_cast<unsigned int>(query_type));
            end_query = (0 != active_queries);
        }

        sw_queries_->EndSwSample(sw_sample_id_);
    }

    return result;
}

void VkGpaSoftwareSample::ReleaseCounters()
{
}

bool VkGpaSoftwareSample::GetTimestampQueryCounterResult(const GpaVkSoftwareQueryResults& query_results,
                                                         const GpaUInt32                  counter_index,
                                                         GpaUInt64&                       counter_result) const
{
    bool result = true;

    IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(context_state_);
    const char*          counter_name     = counter_accessor->GetCounterName(counter_index);

    if (0 == strcmp("VKGPUTime", counter_name))
    {
        counter_result = (query_results.timestampEnd - query_results.timestampBegin);
    }
    else if (0 == strcmp("PreBottomTimestamp", counter_name))
    {
        counter_result = query_results.timestampBegin;
    }
    else if (0 == strcmp("PostBottomTimestamp", counter_name))
    {
        counter_result = query_results.timestampEnd;
    }
    else
    {
        result = false;
    }

    return result;
}

bool VkGpaSoftwareSample::GetPipelineQueryCounterResult(const GpaVkSoftwareQueryResults& query_results,
                                                        const GpaUInt32                  counter_index,
                                                        GpaUInt64&                       counter_result) const
{
    bool                       result           = true;
    const IGpaCounterAccessor* counter_accessor = GpaContextCounterMediator::Instance()->GetCounterAccessor(context_state_);
    const char*                counter_name     = counter_accessor->GetCounterName(counter_index);

    if (0 == strcmp("IAVertices", counter_name))
    {
        counter_result = query_results.inputAssemblyVertices;
    }
    else if (0 == strcmp("IAPrimitives", counter_name))
    {
        counter_result = query_results.inputAssemblyPrimitives;
    }
    else if (0 == strcmp("VSInvocations", counter_name))
    {
        counter_result = query_results.vertexShaderInvocations;
    }
    else if (0 == strcmp("GSInvocations", counter_name))
    {
        counter_result = query_results.geometryShaderInvocations;
    }
    else if (0 == strcmp("GSPrimitives", counter_name))
    {
        counter_result = query_results.geometryShaderPrimitives;
    }
    else if (0 == strcmp("CInvocations", counter_name))
    {
        counter_result = query_results.clippingInvocations;
    }
    else if (0 == strcmp("CPrimitives", counter_name))
    {
        counter_result = query_results.clippingPrimitives;
    }
    else if (0 == strcmp("PSInvocations", counter_name))
    {
        counter_result = query_results.fragmentShaderInvocations;
    }
    else if (0 == strcmp("TCSInvocations", counter_name))
    {
        counter_result = query_results.tessellationControlShaderPatches;
    }
    else if (0 == strcmp("TESInvocations", counter_name))
    {
        counter_result = query_results.tessellationEvaluationShaderInvocations;
    }
    else if (0 == strcmp("CSInvocations", counter_name))
    {
        counter_result = query_results.computeShaderInvocations;
    }
    else
    {
        result = false;
    }

    return result;
}

bool VkGpaSoftwareSample::UpdateResults()
{
    if (GpaSampleState::kResultsCollected == GetGpaSampleState())
    {
        return true;
    }

    bool is_updated = false;

    if (IsSecondary())
    {
        MarkAsCompleted();
        is_updated = true;
    }

    if (GpaSampleState::kPendingResults == GetGpaSampleState() && !IsSecondary())
    {
        GpaVkSoftwareQueryResults query_results = {};
        memset(&query_results, 0, sizeof(query_results));

        if (nullptr != sw_queries_)
        {
            if (sw_queries_->GetSwSampleResults(sw_sample_id_, query_results))
            {
                GetSampleResultLocation()->GetAsCounterSampleResult()->SetNumCounters(active_counter_list_.size());
                const size_t counter_count = active_counter_list_.size();
                is_updated                 = (counter_count == GetSampleResultLocation()->GetAsCounterSampleResult()->GetNumCounters());

                for (size_t ci = 0; is_updated && (counter_count > ci); ++ci)
                {
                    switch (active_counter_list_[ci].query_type)
                    {
                    case kGpaVkQueryTypeOcclusion:
                        GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[ci] = query_results.occlusion;
                        break;

                    case kGpaVkQueryTypeOcclusionBinary:
                        GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[ci] = query_results.occlusionBinary;
                        break;

                    case kGpaVkQueryTypeTimestamp:
                        is_updated = GetTimestampQueryCounterResult(
                            query_results, active_counter_list_[ci].index, GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[ci]);
                        break;

                    case kGpaVkQueryTypePipelineStatistics:
                        is_updated = GetPipelineQueryCounterResult(
                            query_results, active_counter_list_[ci].index, GetSampleResultLocation()->GetAsCounterSampleResult()->GetResultBuffer()[ci]);
                        break;

                    default:
                        is_updated = false;
                        break;
                    }
                }

                sw_queries_->ReleaseSwSample(sw_sample_id_);
            }
        }
    }

    if (is_updated)
    {
        MarkAsCompleted();
    }

    return is_updated;
}