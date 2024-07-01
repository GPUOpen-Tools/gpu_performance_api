//==============================================================================
// Copyright (c) 2016-2023 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief A factory which can produce various counter splitting implementations.
//==============================================================================

#ifndef GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SPLIT_COUNTER_FACTORY_H_
#define GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SPLIT_COUNTER_FACTORY_H_

#include <list>

#include "gpu_perf_api_common/logging.h"

#include "gpu_perf_api_counter_generator/gpa_split_counters_interfaces.h"
#include "gpu_perf_api_counter_generator/gpa_split_counters_max_per_pass.h"
#include "gpu_perf_api_counter_generator/gpa_split_counters_one_per_pass.h"
#include "gpu_perf_api_counter_generator/gpa_split_counters_consolidated.h"
#include "gpu_perf_api_counter_generator/gpa_hardware_counters.h"

/// @brief Available algorithms for splitting counters into multiple passes.
enum GpaCounterSplitterAlgorithm
{
    /// Fit as many counters in the first pass as possible, but no more than a fixed number in a single pass.
    kMaxPerPass = 0,

    /// Each public counter gets its own pass (or as many passes as it needs).
    kOnePublicCounterPerPass,

    /// Public counters that can fit in a single pass will be enabled in the same pass,
    /// single-pass counters should not be split into multiple passes,
    /// multi-pass counters should not take more passes than required,
    /// no more than a fixed number of counters per pass.
    kConsolidated,
};

/// @brief A factory which can produce various counter splitting implementations.
class GpaSplitCounterFactory
{
public:
    /// @brief Generates a new counter splitter object which will need to be deleted by the caller.
    ///
    /// @param [in] algorithm The type of algorithm to generate a splitter for.
    /// @param [in] timestamp_block_ids Set of timestamp block id's.
    /// @param [in] time_counter_indices Set of timestamp counter indices.
    /// @param [in] max_sq_counters The maximum number of simultaneous counters in the SQ block.
    /// @param [in] num_sq_groups The number of SQ counter groups.
    /// @param [in] sq_counter_block_info The list of SQ counter groups.
    /// @param [in] num_isolated_from_sq_groups The number of counter groups that must be isolated from SQ counter groups.
    /// @param [in] isolated_from_sq_groups The list of counter groups that must be isolated from SQ counter groups.
    ///
    /// @return The counter splitter.
    static IGpaSplitCounters* GetNewCounterSplitter(GpaCounterSplitterAlgorithm   algorithm,
                                                    const std::set<unsigned int>& timestamp_block_ids,
                                                    const std::set<unsigned int>& time_counter_indices,
                                                    unsigned int                  max_sq_counters,
                                                    unsigned int                  num_sq_groups,
                                                    GpaSqCounterGroupDesc*        sq_counter_block_info,
                                                    unsigned int                  num_isolated_from_sq_groups,
                                                    const unsigned int*           isolated_from_sq_groups)
    {
        IGpaSplitCounters* splitter = nullptr;

        if (kMaxPerPass == algorithm)
        {
            splitter = new (std::nothrow) GpaSplitCountersMaxPerPass(timestamp_block_ids,
                                                                     time_counter_indices,
                                                                     max_sq_counters,
                                                                     num_sq_groups,
                                                                     sq_counter_block_info,
                                                                     num_isolated_from_sq_groups,
                                                                     isolated_from_sq_groups);
        }
        else if (kOnePublicCounterPerPass == algorithm)
        {
            splitter = new (std::nothrow) GpaSplitCountersOnePerPass(timestamp_block_ids,
                                                                     time_counter_indices,
                                                                     max_sq_counters,
                                                                     num_sq_groups,
                                                                     sq_counter_block_info,
                                                                     num_isolated_from_sq_groups,
                                                                     isolated_from_sq_groups);
        }
        else if (kConsolidated == algorithm)
        {
            splitter = new (std::nothrow) GpaSplitCountersConsolidated(timestamp_block_ids,
                                                                        time_counter_indices,
                                                                        max_sq_counters,
                                                                        num_sq_groups,
                                                                        sq_counter_block_info,
                                                                        num_isolated_from_sq_groups,
                                                                        isolated_from_sq_groups);
        }
        else
        {
            assert(!"Unhandled GpaCounterSplitAlgorithm supplied to factory.");
        }

        if (nullptr == splitter)
        {
            GPA_LOG_ERROR("Unable to allocate memory for counter splitter.");
        }

        return splitter;
    };

private:
    /// @brief Private constructor to enforce use of static factory method.
    GpaSplitCounterFactory(void){};

    /// @brief Private virtual destructor.
    virtual ~GpaSplitCounterFactory(void){};
};

#endif  // GPU_PERF_API_COUNTER_GENERATOR_COMMON_GPA_SPLIT_COUNTER_FACTORY_H_
