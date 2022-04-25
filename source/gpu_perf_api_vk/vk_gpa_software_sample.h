//==============================================================================
// Copyright (c) 2015-2021 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  Class to manage a single sample of SW counters
//==============================================================================

#ifndef GPU_PERF_API_VK_VK_GPA_SOFTWARE_SAMPLE_H_
#define GPU_PERF_API_VK_VK_GPA_SOFTWARE_SAMPLE_H_

#include <vector>

#include "gpu_perf_api_vk/vk_gpa_context.h"
#include "gpu_perf_api_vk/vk_gpa_sample.h"
#include "gpu_perf_api_vk/vk_command_list_sw_queries.h"
#include "gpu_perf_api_vk/vk_includes.h"
#include "gpu_perf_api_vk/vk_software_counters_results.h"

/// @brief Contains the list of enabled counters in the sample.
///
/// Can detect when counter results are available.
/// Give access to counter results.
class VkGpaSoftwareSample : public VkGpaSample
{
public:
    /// @brief Constructor.
    ///
    /// @param [in] pass Pass object.
    /// @param [in] command_list Gpa command list.
    /// @param [in] sample_id Sample Id.
    VkGpaSoftwareSample(GpaPass* pass, IGpaCommandList* command_list, unsigned int sample_id);

    /// @brief Destructor.
    virtual ~VkGpaSoftwareSample();

    /// @brief Assigns the already-initialized queries to the software sample.
    ///
    /// Needed because Vulkan requires that the queries be reset at the
    /// very beginning of the command buffer, and at that time we don't
    /// know if there will be any samples on the command list, so we
    /// initialize them anyway, and assign the queries to the sample
    /// prior to GPASample::Begin() being called.
    ///
    /// @param [in] sw_queries Pointer to the VkCommandListSwQueries object
    ///        that contains all the query pools and queries.
    void AssignQueries(VkCommandListSwQueries* sw_queries);

    /// @copydoc VkGpaSample::BeginRequest()
    virtual bool BeginRequest() override final;

    /// @copydoc VkGpaSample::EndRequest()
    virtual bool EndRequest() override final;

    /// @copydoc VkGpaSample::ReleaseCounters()
    virtual void ReleaseCounters() override final;

    /// @brief Default Constructor deleted.
    VkGpaSoftwareSample() = delete;

private:
    /// @brief Struct to describe active counter.
    struct ActiveCounter
    {
        GpaUInt32        index;       ///< Index of counter.
        GpaVkSwQueryType query_type;  ///< Query type of counter.
    };

    /// Typedef for a list of counters.
    typedef std::vector<ActiveCounter> ActiveCounterListType;

    /// Value of an uninitialized sample id.
    static const GpaUInt32 kUninitializedSampleId = 0xFFFFFFFF;

    /// @brief Copy constructor - private override to disable usage.
    VkGpaSoftwareSample(const VkGpaSoftwareSample&) = delete;

    /// @brief Move constructor - private override to disable usage.
    VkGpaSoftwareSample(VkGpaSoftwareSample&&) = delete;

    /// @brief Copy operator - private override to disable usage.
    ///
    /// @return reference to object.
    VkGpaSoftwareSample& operator=(const VkGpaSoftwareSample&) = delete;

    /// @brief Move operator - private override to disable usage.
    ///
    /// @return reference to object.
    VkGpaSoftwareSample& operator=(VkGpaSoftwareSample&&) = delete;

    /// @brief Get counter result for a counter derived from a timestamp query.
    ///
    /// @param [in] query_results The SW queries results.
    /// @param [in] counter_index The counter index.
    /// @param [out] counter_result Counter result.
    ///
    /// @return True if counter results were collected, false if not.
    bool GetTimestampQueryCounterResult(const GpaVkSoftwareQueryResults& query_results, const GpaUInt32 counter_index, GpaUInt64& counter_result) const;

    /// @brief Get counter result for a counter derived from the pipeline statistics query.
    ///
    /// @param [in] query_results The SW queries results.
    /// @param [in] counter_index The counter index.
    /// @param [out] counter_result Counter result.
    ///
    /// @return True if counter results were collected, false if not.
    bool GetPipelineQueryCounterResult(const GpaVkSoftwareQueryResults& query_results, const GpaUInt32 counter_index, GpaUInt64& counter_result) const;

    /// @copydoc VkGpaSample::UpdateResults()
    virtual bool UpdateResults() override;

    VkGpaContext*           context_state_;        ///< The context the SW Sample is executed on.
    ActiveCounterListType   active_counter_list_;  ///< The list of active counters.
    unsigned int            active_queries_;       ///< The number of active queries.
    VkCommandBuffer         command_list_;         ///< The command list the sample is executed on.
    GpaUInt32               sw_sample_id_;         ///< The SW sample ID executed on the context.
    VkCommandListSwQueries* sw_queries_;           ///< The Software queries being used by this sample.
};

#endif  // GPU_PERF_API_VK_VK_GPA_SOFTWARE_SAMPLE_H_
