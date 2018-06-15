//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Counter splitter that puts max number of hardware counter per pass
///         not used in production, but can be useful for testing
//==============================================================================

#ifndef _GPA_SPLIT_COUNTERS_MAX_PER_PASS_H_
#define _GPA_SPLIT_COUNTERS_MAX_PER_PASS_H_

#include "GPASplitCountersInterfaces.h"
#include "GPAInternalCounter.h"
#include <vector>

/// Splits counters such that as many internal counters will be scheduled per pass as possible.
class GPASplitCountersMaxPerPass : public IGPASplitCounters
{
public:

    /// Initializes a new instance of the GPASplitCountersMaxPerPass class
    /// \param timestampBlockIds Set of timestamp block id's
    /// \param timeCounterIndices Set of timestamp counter indices
    /// \param maxSQCounters The maximum number of counters that can be simultaneously enabled on the SQ block
    /// \param numSQGroups The number of SQ counter groups.
    /// \param pSQCounterBlockInfo The list of SQ counter groups.
    /// \param numIsolatedFromSqGroups The number of counter groups that must be isolated from SQ counter groups
    /// \param pIsolatedFromSqGroups The list of counter groups that must be isolated from SQ counter groups
    GPASplitCountersMaxPerPass(const std::set<unsigned int>& timestampBlockIds,
                               const std::set<unsigned int>& timeCounterIndices,
                               unsigned int maxSQCounters,
                               unsigned int numSQGroups,
                               GPA_SQCounterGroupDesc* pSQCounterBlockInfo,
                               unsigned int numIsolatedFromSqGroups,
                               const unsigned int* pIsolatedFromSqGroups)
        :   IGPASplitCounters(timestampBlockIds, timeCounterIndices,
                              maxSQCounters,
                              numSQGroups, pSQCounterBlockInfo,
                              numIsolatedFromSqGroups, pIsolatedFromSqGroups)
    {
    };

    //--------------------------------------------------------------------------
    /// Destructor
    virtual ~GPASplitCountersMaxPerPass() {};

    //--------------------------------------------------------------------------
    // puts as many counters in the first pass as will fit based on the maxCountersPerGroup, will expand to additional passes as required by the hardware.
    std::list<GPACounterPass> SplitCounters(const std::vector<const GPA_DerivedCounter*>& publicCountersToSplit,
                                            const std::vector<GPAHardwareCounterIndices> internalCountersToSchedule,
                                            const std::vector<GPASoftwareCounterIndices> softwareCountersToSchedule,
                                            IGPACounterGroupAccessor* accessor,
                                            const std::vector<unsigned int>& maxCountersPerGroup,
                                            unsigned int& numScheduledCounters)
    {
        // this will eventually be the return value
        std::list<GPACounterPass> passPartitions;

        // make sure there are counters to schedule
        if (publicCountersToSplit.size() == 0 && internalCountersToSchedule.size() == 0)
        {
            return passPartitions;
        }

        // temporary variable to hold the number of counters assigned to each block during each of the passes.
        std::list<PerPassData> numUsedCountersPerPassPerBlock;

        // add initial pass information
        AddNewPassInfo(1, &passPartitions, &numUsedCountersPerPassPerBlock);

        // will store the locations for each scheduled internal counter to help ensure that we don't duplicate any scheduling
        std::map<unsigned int, GPA_CounterResultLocation> internalCounterResultLocations;

        // iterate through each public counter
        for (std::vector<const GPA_DerivedCounter*>::const_iterator publicIter = publicCountersToSplit.begin(); publicIter != publicCountersToSplit.end(); ++publicIter)
        {
            // iterate through the internal counters and put them into the appropriate pass (first available pass)
            for (std::vector<gpa_uint32>::const_iterator counterIter = (*publicIter)->m_internalCountersRequired.begin(); counterIter != (*publicIter)->m_internalCountersRequired.end(); ++counterIter)
            {
                // see if the internal counter has already been scheduled
                std::map<unsigned int, GPA_CounterResultLocation>::iterator foundCounter = internalCounterResultLocations.find(*counterIter);

                if (foundCounter != internalCounterResultLocations.end())
                {
                    // counter has been scheduled
                    // so use the same result location for this instance of the counter
                    AddCounterResultLocation((*publicIter)->m_index, *counterIter, foundCounter->second.m_pass, foundCounter->second.m_offset);
                }
                else
                {
                    // counter has not been scheduled
                    // so need to find a pass to put it in
                    unsigned int passIndex = 0;
                    std::list<PerPassData>::iterator countersUsedIter = numUsedCountersPerPassPerBlock.begin();
                    std::list<GPACounterPass>::iterator counterPassIter = passPartitions.begin();

                    bool doneAllocatingCounter = false;

                    while (doneAllocatingCounter == false)
                    {
                        // make sure there is a partition for current pass
                        AddNewPassInfo(passIndex + 1, &passPartitions, &numUsedCountersPerPassPerBlock);

                        // increment the pass iterator if past the first loop
                        if (passIndex > 0)
                        {
                            ++countersUsedIter;
                            ++counterPassIter;
                        }

                        accessor->SetCounterIndex(*counterIter);
                        unsigned int groupIndex = accessor->GroupIndex();

                        // try to add the counter to the current pass
                        if (CheckForTimestampCounters(accessor, *counterPassIter) &&
                            CanCounterBeAdded(accessor, *countersUsedIter, maxCountersPerGroup) &&
                            CheckForSQCounters(accessor, *countersUsedIter, m_maxSQCounters) &&
                            CheckCountersAreCompatible(accessor, *countersUsedIter) &&
                            counterPassIter->m_counters.size() < 300)
                        {
                            counterPassIter->m_counters.push_back(*counterIter);
                            countersUsedIter->m_numUsedCountersPerBlock[groupIndex].push_back(accessor->CounterIndex());
                            doneAllocatingCounter = true;

                            // record where the internal counter was scheduled
                            GPA_CounterResultLocation location;
                            location.m_pass = (gpa_uint16)passIndex;
                            location.m_offset = (gpa_uint16)counterPassIter->m_counters.size() - 1;
                            internalCounterResultLocations[*counterIter] = location;

                            // record where to get the result from
                            AddCounterResultLocation((*publicIter)->m_index, *counterIter, location.m_pass, location.m_offset);
                        }
                        else
                        {
                            // the counters needs to go into the next pass. Increment the pass index and let the loop happen again
                            ++passIndex;
                        }
                    } // end while loop to find a suitable pass for the current counter
                }
            } // end loop over each internal counter
        } // end loop over each public counter

        // set the number of scheduled internal counters
        numScheduledCounters = (unsigned int)internalCounterResultLocations.size();

        InsertHardwareCounters(passPartitions, internalCountersToSchedule, accessor, numUsedCountersPerPassPerBlock, maxCountersPerGroup, numScheduledCounters);

        return passPartitions;
    }

private:

    /// Inserts each hardware counter into the earliest possible pass.
    /// \param[in,out] passPartitions The pass partitions that are generated
    /// \param internalCounters The internal counters that need to be scheduled
    /// \param accessor A interface that accesses the internal counters
    /// \param numUsedCountersPerPassPerBlock A list of passes, each consisting of the number of counters scheduled on each block
    /// \param maxCountersPerGroup A vector containing the maximum number of simultaneous counters for each block
    /// \param[in,out] numScheduledCounters The total number of internal counters that were scheduled
    void InsertHardwareCounters(std::list<GPACounterPass>& passPartitions, const std::vector<GPAHardwareCounterIndices> internalCounters, IGPACounterGroupAccessor* accessor, std::list<PerPassData> numUsedCountersPerPassPerBlock, const std::vector<unsigned int>& maxCountersPerGroup, unsigned int& numScheduledCounters)
    {
        // schedule each of the internal counters
        for (std::vector<GPAHardwareCounterIndices>::const_iterator internalCounterIter = internalCounters.begin(); internalCounterIter != internalCounters.end(); ++internalCounterIter)
        {
            // if the counter is already scheduled in any pass, there is no reason to add it again.
            bool counterAlreadyScheduled = false;
            unsigned int passIndex = 0;

            for (std::list<GPACounterPass>::iterator passIter = passPartitions.begin(); passIter != passPartitions.end(); ++passIter)
            {
                int existingOffset = VectorContains<unsigned int>(passIter->m_counters, internalCounterIter->m_hardwareIndex);

                if (existingOffset >= 0)
                {
                    counterAlreadyScheduled = true;

                    // record where to get the result from
                    AddCounterResultLocation(internalCounterIter->m_publicIndex, internalCounterIter->m_hardwareIndex, passIndex, existingOffset);
                    break;
                }

                passIndex++;
            }

            if (counterAlreadyScheduled)
            {
                // Don't need to schedule this counter,
                // continue on to the next internal counter that needs to be scheduled.
                continue;
            }

            // The counter needs to be scheduled
            // make sure there is enough space for the first pass
            AddNewPassInfo(1, &passPartitions, &numUsedCountersPerPassPerBlock);

            accessor->SetCounterIndex(internalCounterIter->m_hardwareIndex);

            // Iterate through the passes again and find one where the counter can be inserted.
            passIndex = 0;
            std::list<PerPassData>::iterator countersUsedIter = numUsedCountersPerPassPerBlock.begin();

            for (std::list<GPACounterPass>::iterator passIter = passPartitions.begin(); passIter != passPartitions.end(); ++passIter)
            {
                if (CheckForTimestampCounters(accessor, *passIter) == true &&
                    CanCounterBeAdded(accessor, *countersUsedIter, maxCountersPerGroup) == true &&
                    CheckForSQCounters(accessor, *countersUsedIter, m_maxSQCounters) == true &&
                    CheckCountersAreCompatible(accessor, *countersUsedIter) == true)
                {
                    // the counter can be scheduled here.
                    passIter->m_counters.push_back(internalCounterIter->m_hardwareIndex);
                    countersUsedIter->m_numUsedCountersPerBlock[accessor->GroupIndex()].push_back(accessor->CounterIndex());
                    numScheduledCounters += 1;

                    // record where the result will be located
                    unsigned int offset = (unsigned int)passIter->m_counters.size() - 1;
                    AddCounterResultLocation(internalCounterIter->m_publicIndex, internalCounterIter->m_hardwareIndex, passIndex, offset);
                    break;
                }
                else
                {
                    ++passIndex;

                    // make sure there is enough space for the next pass
                    AddNewPassInfo(passIndex + 1, &passPartitions, &numUsedCountersPerPassPerBlock);

                    // increment the iterator after any necessary new passes have been allocated.
                    ++countersUsedIter;
                }
            }
        }
    }
};

#endif //_GPA_SPLIT_COUNTERS_MAX_PER_PASS_H_
