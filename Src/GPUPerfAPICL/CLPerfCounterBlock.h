//==============================================================================
// Copyright (c) 2009-2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A utility class for interfacing with the performance counter from the OpenCL runtime.
//==============================================================================

#ifndef _CLPERFCOUNTERBLOCK_H_
#define _CLPERFCOUNTERBLOCK_H_

/// Handle the creation of HW performance counter block using the OpenCL runtime
/// Example usage:
///     cl_event event;
///     clPerfCounterBlock sqBlock(clDevice, R7xxPerfCtrBlockSQ, 1, pSQCounters);
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
class clPerfCounterBlock
{
public:
    /// Constructor
    /// \param[in] clDevice   the OpenCL device id
    /// \param[in] blockID    the HW block id (for example R7xxPerfCtrBlockSQ)
    /// \param[in] maxActive  the maximum counters that can be queried for the block in a single pass
    /// \param[in] pCounters  the list of counter ids for the block.
    clPerfCounterBlock(cl_device_id    clDevice,
                       cl_ulong        blockID,
                       cl_uint         maxActive,
                       std::vector< cl_ulong > pCounters);

    /// Destructor
    virtual ~clPerfCounterBlock();

    /// Release the counters that were created in the CL runtime
    void ReleaseCounters();

    /// Collect data from the HW performance counters
    /// \param clEvent  event to synchronize the result (this should be the event from clEnqueueEndPerfCounterAMD())
    /// \return true if successfull, false otherwise
    bool CollectData(const cl_event* clEvent);

    /// Get the starting address of a list of perfcounters (m_maxActive items).
    /// \param[in] passID  the pass ID
    /// \return the starting address for the list of perfcounters
    cl_perfcounter_amd* GetCounterArray(cl_uint passID) const
    {
        return (passID * m_maxActive <= m_pCounters.size() && nullptr != m_pclCounters) ?
               &m_pclCounters[passID * m_maxActive] : nullptr;
    }

    /// Get the all the counter ids for this block
    /// \return the counter ids for this block
    const std::vector< cl_ulong >& GetCounterIDs() const { return m_pCounters; }

    /// Get the total number of counters specified for the block
    /// \return the total number of counters
    cl_uint GetCounterCount() const { return (cl_uint) m_pCounters.size(); }

    /// Get the max counters that can be queried in this block in a single pass
    /// \return the maximum active counters
    cl_uint GetMaxActive() const { return m_maxActive; }

    /// Get the total number of passes required to iterate through all the counters
    /// \return the total runs
    cl_uint GetNumPasses() const { return (cl_uint)(ceilf((float) m_pCounters.size() / m_maxActive)); }

    /// Given a counter index, get the result (CollectData needs to be called prior to calling this function)
    /// \param[in] counterID  the counter index (from example R7xxPerfCtrSQ_PERF_SEL_THREADS_PER_TYPE)
    /// \return the counter result for a specific counter id
    cl_ulong GetResult(cl_ulong counterID) { return m_results[counterID]; }

    /// Get the block id
    /// \return the block id for this block (for example R7xxPerfCtrBlockSQ)
    cl_ulong GetBlockID() const { return m_blockID; }

    /// Check whether the result has been completed (CollectData has been called and completed succesfully)
    /// \return the ready flag
    bool IsComplete() const { return m_isResultReady; }

private:
    /// Initial creation, called by the constructor
    void Create();

    clPerfCounterBlock();                              ///< disable the default constructor
    clPerfCounterBlock(const clPerfCounterBlock&);     ///< disable the copy constructor
    clPerfCounterBlock& operator=(const clPerfCounterBlock&);     ///< disable the assignment operator

protected:
    cl_device_id                   m_clDevice;      ///< opencl device
    cl_ulong                       m_blockID;       ///< the HW block ID (for example R7xxPerfCtrBlockSQ)
    cl_uint                        m_maxActive;     ///< max active counters in this block that can be queued/queried in a single pass
    const std::vector< cl_ulong >  m_pCounters;     ///< store the id for the counters
    cl_perfcounter_amd*            m_pclCounters;   ///< store the OpenCL HW counters
    std::map< cl_ulong, cl_ulong > m_results;       ///< store the results indexed by the counter id.
    bool                           m_isResultReady; ///< true if CollectData has been called succesfully, false otherwise
};

#endif // _CLPERFCOUNTERBLOCK_H
