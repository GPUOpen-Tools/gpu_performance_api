//==============================================================================
// Copyright (c) 2016-2020 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  A factory which can produce various counter splitting implementations.
//==============================================================================

#ifndef _GPA_SPLIT_COUNTER_FACTORY_H_
#define _GPA_SPLIT_COUNTER_FACTORY_H_

#include <list>
#include "logging.h"
#include "gpa_split_counters_interfaces.h"
#include "gpa_split_counters_max_per_pass.h"
#include "gpa_split_counters_one_per_pass.h"
#include "gpa_split_counters_consolidated.h"
#include "gpa_hardware_counters.h"

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
};

/// A factory which can produce various counter splitting implementations.
class GPASplitCounterFactory
{
public:
    /// Generates a new counter splitter object which will need to be deleted by the caller.
    /// \param algorithm The type of algorithm to generate a splitter for.
    /// \param timestampBlockIds Set of timestamp block id's
    /// \param timeCounterIndices Set of timestamp counter indices
    /// \param maxSQCounters The maximum number of simultaneous counters in the SQ block.
    /// \param numSQGroups The number of SQ counter groups.
    /// \param pSQCounterBlockInfo The list of SQ counter groups.
    /// \param numIsolatedFromSqGroups The number of counter groups that must be isolated from SQ counter groups
    /// \param pIsolatedFromSqGroups The list of counter groups that must be isolated from SQ counter groups
    /// \return the counter splitter
    static IGPASplitCounters* GetNewCounterSplitter(GPACounterSplitterAlgorithm   algorithm,
                                                    const std::set<unsigned int>& timestampBlockIds,
                                                    const std::set<unsigned int>& timeCounterIndices,
                                                    unsigned int                  maxSQCounters,
                                                    unsigned int                  numSQGroups,
                                                    GPA_SQCounterGroupDesc*       pSQCounterBlockInfo,
                                                    unsigned int                  numIsolatedFromSqGroups,
                                                    const unsigned int*           pIsolatedFromSqGroups)
    {
        IGPASplitCounters* pSplitter = nullptr;

        if (MAX_PER_PASS == algorithm)
        {
            pSplitter = new (std::nothrow) GPASplitCountersMaxPerPass(
                timestampBlockIds, timeCounterIndices, maxSQCounters, numSQGroups, pSQCounterBlockInfo, numIsolatedFromSqGroups, pIsolatedFromSqGroups);
        }
        else if (ONE_PUBLIC_COUNTER_PER_PASS == algorithm)
        {
            pSplitter = new (std::nothrow) GPASplitCountersOnePerPass(
                timestampBlockIds, timeCounterIndices, maxSQCounters, numSQGroups, pSQCounterBlockInfo, numIsolatedFromSqGroups, pIsolatedFromSqGroups);
        }
        else if (CONSOLIDATED == algorithm)
        {
            pSplitter = new (std::nothrow) GPASplitCountersConsolidated(
                timestampBlockIds, timeCounterIndices, maxSQCounters, numSQGroups, pSQCounterBlockInfo, numIsolatedFromSqGroups, pIsolatedFromSqGroups);
        }
        else
        {
            assert(!"Unhandled GPACounterSplitAlgorithm supplied to factory.");
        }

        if (nullptr == pSplitter)
        {
            GPA_LogError("Unable to allocate memory for counter splitter.");
        }

        return pSplitter;
    };

private:
    /// private constructor to enforce use of static factory method
    GPASplitCounterFactory(void){};

    /// private virtual destructor
    virtual ~GPASplitCounterFactory(void){};
};

#endif  //_GPA_SPLIT_COUNTER_FACTORY_H_
