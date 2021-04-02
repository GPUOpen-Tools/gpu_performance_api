//==============================================================================
// Copyright (c) 2009-2018 Advanced Micro Devices, Inc. All rights reserved.
/// @author AMD Developer Tools Team
/// @file
/// @brief  A utility class for interfacing with the performance counter from the OpenCL runtime.
//==============================================================================

#ifndef _CL_PERF_COUNTER_BLOCK_H_
#define _CL_PERF_COUNTER_BLOCK_H_

#include <math.h>
#include <CL/internal/cl_profile_amd.h>

/// Handle the creation of HW performance counter block using the OpenCL runtime
/// Example usage:
///     cl_event event;
///     ClPerfCounterBlock sqBlock(clDevice, R7xxPerfCtrBlockSQ, 1, pSQCounters);
///     for (cl_uint i = 0; i < sqBlock.GetNumPasses(); ++i)
///     {
///         clEnqueueBeginPerfCounterAMD(cmdQueue, sqBlock.GetMaxActive(), sqBlock.GetCounterArray(i), 0, 0, 0);
///         error = clEnqueueNDRangeKernel(cmdQueue, kernel, 1, nullptr, globalWorkSize, localWorkSize, 0, nullptr, nullptr);
///         clEnqueueEndPerfCounterAMD(cmdQueue, sqBlock.GetMaxActive(), sqBlock.GetCounterArray(i), 0, 0, &event);
///     }
///     sqBlock.CollectData(&event);
///
///     if (sqBlock.IsComplete())
///     {
///        for (cl_uint i = 0; i < pSqCounters.size(); i++)
///        {
///           cl_ulong result = sqBlock.GetResult(pSqCounters[i]);
///        }
///     }
///
class ClPerfCounterBlock
{
public:
    /// Constructor
    /// @param [in] cl_device   the OpenCL device id
    /// @param [in] block_id    the HW block id (for example R7xxPerfCtrBlockSQ)
    /// @param [in] max_active  the maximum counters that can be queried for the block in a single pass
    /// @param [in] counters  the list of counter ids for the block.
    ClPerfCounterBlock(cl_device_id cl_device, cl_ulong block_id, cl_uint max_active, std::vector<cl_ulong> counters);

    /// Destructor
    virtual ~ClPerfCounterBlock();

    /// Release the counters that were created in the CL runtime
    void ReleaseCounters();

    /// Collect data from the HW performance counters
    /// @param cl_event_param  event to synchronize the result (this should be the event from clEnqueueEndPerfCounterAMD())
    /// @return true if successful, false otherwise
    bool CollectData(const cl_event* cl_event_param);

    /// Get the starting address of a list of perf-counters (max_active_ items).
    /// @param [in] pass_id  the pass ID
    /// @return the starting address for the list of perf-counters
    cl_perfcounter_amd* GetCounterArray(cl_uint pass_id) const
    {
        return (pass_id * max_active_ <= counters_list_.size() && nullptr != cl_perf_counters_amd_) ? &cl_perf_counters_amd_[pass_id * max_active_] : nullptr;
    }

    /// Get the all the counter ids for this block
    /// @return the counter ids for this block
    const std::vector<cl_ulong>& GetCounterIDs() const
    {
        return counters_list_;
    }

    /// Get the total number of counters specified for the block
    /// @return the total number of counters
    cl_uint GetCounterCount() const
    {
        return static_cast<cl_uint>(counters_list_.size());
    }

    /// Get the max counters that can be queried in this block in a single pass
    /// @return the maximum active counters
    cl_uint GetMaxActive() const
    {
        return max_active_;
    }

    /// Get the total number of passes required to iterate through all the counters
    /// @return the total runs
    cl_uint GetNumPasses() const
    {
        return static_cast<cl_uint>(ceilf(static_cast<float>(counters_list_.size()) / max_active_));
    }

    /// Given a counter index, get the result (CollectData needs to be called prior to calling this function)
    /// @param [in] counter_id  the counter index (from example R7xxPerfCtrSQ_PERF_SEL_THREADS_PER_TYPE)
    /// @return the counter result for a specific counter id
    cl_ulong GetResult(cl_ulong counter_id)
    {
        return counter_result_map_[counter_id];
    }

    /// Get the block id
    /// @return the block id for this block (for example R7xxPerfCtrBlockSQ)
    cl_ulong GetBlockID() const
    {
        return block_id_;
    }

    /// Check whether the result has been completed (CollectData has been called and completed successfully)
    /// @return the ready flag
    bool IsComplete() const
    {
        return is_counter_result_ready_;
    }

private:
    /// Initial creation, called by the constructor
    void Create();

    ClPerfCounterBlock()                          = delete;             ///< disable the default constructor
    ClPerfCounterBlock(const ClPerfCounterBlock&) = delete;             ///< disable the copy constructor
    ClPerfCounterBlock& operator=(const ClPerfCounterBlock&) = delete;  ///< disable the assignment operator \return item being assigned

protected:
    cl_device_id                 cl_device_;                ///< OpenCL device
    cl_ulong                     block_id_;                 ///< the HW block ID (for example R7xxPerfCtrBlockSQ)
    cl_uint                      max_active_;               ///< max active counters in this block that can be queued/queried in a single pass
    const std::vector<cl_ulong>  counters_list_;            ///< store the id for the counters
    cl_perfcounter_amd*          cl_perf_counters_amd_;     ///< store the OpenCL HW counters
    std::map<cl_ulong, cl_ulong> counter_result_map_;       ///< store the results indexed by the counter id.
    bool                         is_counter_result_ready_;  ///< true if CollectData has been called successfully, false otherwise
};

#endif  // _CL_PERF_COUNTER_BLOCK_H_
