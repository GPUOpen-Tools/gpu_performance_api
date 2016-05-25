//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A factory which can produce various counter splitting implementations.
//==============================================================================

#ifndef _GPA_SPLIT_COUNTER_FACTORY_H_
#define _GPA_SPLIT_COUNTER_FACTORY_H_

#include "Logging.h"
#include "GPASplitCountersInterfaces.h"
#include "GPASplitCountersMaxPerPass.h"
#include "GPASplitCountersOnePerPass.h"
#include "GPASplitCountersConsolidated.h"
#ifdef _WIN32
    #include "GPASplitCountersConsolidatedDX12.h"
#endif // _WIN32
#include "GPAHardwareCounters.h"
#include <list>

/// Available algorithms for splitting counters into multiple passes
enum GPACounterSplitterAlgorithm
{
    /// fit as many counters in the first pass as possible, but no more than a fixed number in a single pass
    MAX_PER_PASS = 0,

    /// each public counter gets its own pass (or as many passes as it needs)
    ONE_PUBLIC_COUNTER_PER_PASS,

    /// public counters that can fit in a single pass will be enabled in the same pass,
    /// single-pass counters should not be split into multiple passes,
    /// multi-pass counters should not take more passes than required,
    /// no more than a fixed number of counters per pass,
    CONSOLIDATED,

    // Consolidated algorithm for DX12
    CONSOLIDATED_DX12,
};

/// A factory which can produce various counter splitting implementations.
class GPASplitCounterFactory
{
public:
    /// Generates a new counter splitter object which will need to be deleted by the caller.
    /// \param algorithm The type of algorithm to generate a splitter for.
    /// \param gpuTimestampGroupIndex The index of the GPU Timestamp group.
    /// \param gpuTimestampBottomToBottomCounterIndex The index of the bottom to bottom timestamp counter.
    /// \param gpuTimestampTopToBottomCounterIndex The index of the top to bottom timestamp counter.
    /// \param maxSQCounters The maximum number of simultaneous counters in the SQ block.
    /// \param numSQGroups The number of SQ counter groups.
    /// \param pSQCounterBlockInfo The list of SQ counter groups.
    /// \return the counter splitter
    static IGPASplitCounters* GetNewCounterSplitter(GPACounterSplitterAlgorithm algorithm,
                                                    unsigned int gpuTimestampGroupIndex,
                                                    unsigned int gpuTimestampBottomToBottomCounterIndex,
                                                    unsigned int gpuTimestampTopToBottomCounterIndex,
                                                    unsigned int maxSQCounters,
                                                    unsigned int numSQGroups,
                                                    GPA_SQCounterGroupDesc* pSQCounterBlockInfo)
    {
        IGPASplitCounters* pSplitter = nullptr;

        if (MAX_PER_PASS == algorithm)
        {
            pSplitter = new(std::nothrow) GPASplitCountersMaxPerPass(gpuTimestampGroupIndex, gpuTimestampBottomToBottomCounterIndex,
                                                       gpuTimestampTopToBottomCounterIndex, maxSQCounters,
                                                       numSQGroups, pSQCounterBlockInfo);
        }
        else if (ONE_PUBLIC_COUNTER_PER_PASS == algorithm)
        {
            pSplitter = new(std::nothrow) GPASplitCountersOnePerPass(gpuTimestampGroupIndex, gpuTimestampBottomToBottomCounterIndex,
                                                       gpuTimestampTopToBottomCounterIndex, maxSQCounters,
                                                       numSQGroups, pSQCounterBlockInfo);
        }
        else if (CONSOLIDATED == algorithm)
        {
            pSplitter = new(std::nothrow) GPASplitCountersConsolidated(gpuTimestampGroupIndex, gpuTimestampBottomToBottomCounterIndex,
                                                         gpuTimestampTopToBottomCounterIndex, maxSQCounters,
                                                         numSQGroups, pSQCounterBlockInfo);
        }

#ifdef _WIN32
        else if (CONSOLIDATED_DX12 == algorithm)
        {
            pSplitter = new(std::nothrow) GPASplitCountersConsolidatedDX12(gpuTimestampGroupIndex, gpuTimestampBottomToBottomCounterIndex,
                                                             gpuTimestampTopToBottomCounterIndex, maxSQCounters,
                                                             numSQGroups, pSQCounterBlockInfo);
        }

#endif // _WIN32
        else
        {
            assert(!"Unhandled GPACounterSplitAlgorithm supplied to factory.");
        }

        if (nullptr == pSplitter)
        {
            GPA_LogError("Unable to allocate memory for counter splitter");
        }

        return pSplitter;
    };

private:
    /// private constructor to enforce use of static factory method
    GPASplitCounterFactory(void) {};

    /// private virtual destructor
    virtual ~GPASplitCounterFactory(void) {};
};

#endif //_GPA_SPLIT_COUNTER_FACTORY_H_
