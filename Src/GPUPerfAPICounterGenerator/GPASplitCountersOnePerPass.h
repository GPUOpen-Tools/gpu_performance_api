//==============================================================================
// Copyright (c) 2016-2018 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Counter splitter that puts one hardware counter per pass -- not used
///         in production, but can be useful for testing
//==============================================================================

#include "GPASplitCountersInterfaces.h"
#include "GPAInternalCounter.h"
#include <vector>

/// Splits counters such that each public counter is in its own pass (or multiple passes as needed).
/// In internal builds, the additional internal counters will also each go into their own pass.
class GPASplitCountersOnePerPass : public IGPASplitCounters
{
public:

    /// Initializes a new instance of the GPASplitCountersOnePerPass class
    /// \param timestampBlockIds Set of timestamp block id's
    /// \param timeCounterIndices Set of timestamp counter indices
    /// \param maxSQCounters The maximum number of counters that can be simultaneously enabled on the SQ block
    /// \param numSQBlocks The number of SQ counter blocks.
    /// \param pSQCounterBlockInfo The list of SQ counter groups.
    /// \param numIsolatedFromSqGroups The number of counter groups that must be isolated from SQ counter groups
    /// \param pIsolatedFromSqGroups The list of counter groups that must be isolated from SQ counter groups
    GPASplitCountersOnePerPass(const std::set<unsigned int>& timestampBlockIds,
                               const std::set<unsigned int>& timeCounterIndices,
                               unsigned int maxSQCounters,
                               unsigned int numSQBlocks,
                               GPA_SQCounterGroupDesc* pSQCounterBlockInfo,
                               unsigned int numIsolatedFromSqGroups,
                               const unsigned int* pIsolatedFromSqGroups)
        :   IGPASplitCounters(timestampBlockIds, timeCounterIndices,
                              maxSQCounters,
                              numSQBlocks, pSQCounterBlockInfo,
                              numIsolatedFromSqGroups, pIsolatedFromSqGroups)
    {
    };

    /// Destructor
    virtual ~GPASplitCountersOnePerPass() {};

    //--------------------------------------------------------------------------
    // puts each public counter into its own pass (or set of passes) and each hardware counter into its own pass if not already scheduled
    std::list<GPACounterPass> SplitCounters(const std::vector<const GPA_DerivedCounter*>& publicCountersToSplit,
                                            const std::vector<GPAHardwareCounterIndices> internalCountersToSchedule,
                                            const std::vector<GPASoftwareCounterIndices>  softwareCountersToSchedule,
                                            IGPACounterGroupAccessor* accessor,
                                            const std::vector<unsigned int>& maxCountersPerGroup,
                                            unsigned int& numScheduledCounters)
    {
        UNREFERENCED_PARAMETER(softwareCountersToSchedule);
        // this will be the return value
        std::list<GPACounterPass> passPartitions;

        // make sure there are counters to schedule
        if (publicCountersToSplit.size() == 0 && internalCountersToSchedule.size() == 0)
        {
            return passPartitions;
        }

        // temporary variable to hold the number of counters assigned to each block during each of the passes.
        std::list<PerPassData> numUsedCountersPerPassPerBlock;

        // add initial pass partition and used counters per block
        AddNewPassInfo(1, &passPartitions, &numUsedCountersPerPassPerBlock);

        unsigned int passIndex = 0;
        std::list<PerPassData>::iterator countersUsedIter = numUsedCountersPerPassPerBlock.begin();
        std::list<GPACounterPass>::iterator counterPassIter = passPartitions.begin();

        // iterate through each public counter
        for (std::vector<const GPA_DerivedCounter*>::const_iterator publicIter = publicCountersToSplit.begin(); publicIter != publicCountersToSplit.end(); ++publicIter)
        {
            unsigned int initialPassForThisPubCounter = passIndex;
            unsigned int currentPassForThisIntCounter = passIndex;

            // iterate through the internal counters and put them into the appropriate pass
            for (std::vector<gpa_uint32>::const_iterator counterIter = (*publicIter)->m_internalCountersRequired.begin(); counterIter != (*publicIter)->m_internalCountersRequired.end(); ++counterIter)
            {
                // each internal counter should try to go into the first pass of this public counter
                // reset iterators...
                for (unsigned int i = currentPassForThisIntCounter; i > initialPassForThisPubCounter; --i)
                {
                    --countersUsedIter;
                    --counterPassIter;
                }

                // .. and reset current pass for this internal counter
                currentPassForThisIntCounter = initialPassForThisPubCounter;

                bool doneAllocatingCounter = false;

                while (doneAllocatingCounter == false)
                {
                    accessor->SetCounterIndex(*counterIter);
                    unsigned int groupIndex = accessor->GroupIndex();

                    size_t countersSize = counterPassIter->m_counters.size();

                    // try to add the counter to the current pass
                    if (countersSize == 0 ||
                        (CheckForTimestampCounters(accessor, *counterPassIter) &&
                         CanCounterBeAdded(accessor, *countersUsedIter, maxCountersPerGroup) &&
                         CheckForSQCounters(accessor, *countersUsedIter, m_maxSQCounters) &&
                         CheckCountersAreCompatible(accessor, *countersUsedIter) &&
                         countersSize < 300))
                    {
                        counterPassIter->m_counters.push_back(*counterIter);
                        countersUsedIter->m_numUsedCountersPerBlock[groupIndex].push_back(accessor->CounterIndex());
                        numScheduledCounters += 1;
                        doneAllocatingCounter = true;

                        // record where to get the result from
                        AddCounterResultLocation((*publicIter)->m_index, *counterIter, currentPassForThisIntCounter, (unsigned int)counterPassIter->m_counters.size() - 1);
                    }
                    else
                    {
                        // the counters needs to go into the next pass. Increment the pass index and let the loop happen again
                        ++currentPassForThisIntCounter;

                        if (currentPassForThisIntCounter > passIndex)
                        {
                            ++passIndex;

                            AddNewPassInfo(passIndex + 1, &passPartitions, &numUsedCountersPerPassPerBlock);
                        }

                        ++countersUsedIter;
                        ++counterPassIter;
                    }
                } // end while loop to find a suitable pass for the current counter
            } // end for loop over each of the internal counters

            if (publicIter != publicCountersToSplit.end() - 1)
            {
                // next counter will be in another pass
                ++passIndex;

                GPACounterPass counterPass;
                passPartitions.push_back(counterPass);

                PerPassData newPass;
                numUsedCountersPerPassPerBlock.push_back(newPass);

                // point to the last item in this case so the next public counter can start at the pass just added
                countersUsedIter = numUsedCountersPerPassPerBlock.end();
                --countersUsedIter;
                counterPassIter = passPartitions.end();
                --counterPassIter;
            }
        }

        InsertInternalCounters(passPartitions, internalCountersToSchedule, accessor, numUsedCountersPerPassPerBlock, numScheduledCounters);

        return passPartitions;
    };

private:

    /// Inserts each internal counter into a separate pass
    /// \param[in,out] passPartitions The pass partitions that are generated
    /// \param internalCounters The internal counters that need to be scheduled
    /// \param pAccessor A interface that accesses the internal counters
    /// \param numUsedCountersPerPassPerBlock A list of passes, each consisting of the number of counters scheduled on each block
    /// \param[in,out] numScheduledCounters The total number of internal counters that were scheduled
    void InsertInternalCounters(std::list<GPACounterPass>& passPartitions, const std::vector<GPAHardwareCounterIndices> internalCounters, IGPACounterGroupAccessor* pAccessor, std::list<PerPassData> numUsedCountersPerPassPerBlock, unsigned int& numScheduledCounters)
    {
        if (internalCounters.size() == 0)
        {
            return;
        }

        // if there are no passes, then the first pass added below will be empty.
        // In this case, we have to special handle things further down.
        bool firstPassEmpty = (numScheduledCounters == 0);

        // make sure there is room for the first pass
        AddNewPassInfo(1, &passPartitions, &numUsedCountersPerPassPerBlock);

        std::list<GPACounterPass>::iterator currentPassIter = passPartitions.end();
        std::list<PerPassData>::iterator currentUsedCountersIter = numUsedCountersPerPassPerBlock.end();
        unsigned int passIndex = (unsigned int)passPartitions.size();

        // back up the iterators so that they point to the last pass.
        --currentPassIter;
        --currentUsedCountersIter;

        // schedule each of the internal counters in its own pass, unless it is already scheduled from one of the public counters
        for (std::vector<GPAHardwareCounterIndices>::const_iterator internalCounterIter = internalCounters.begin(); internalCounterIter != internalCounters.end(); ++internalCounterIter)
        {
            // if the counter is already scheduled in any pass, there is no reason to add it again.
            bool counterAlreadyScheduled = false;
            gpa_uint16 searchPassIndex = 0;

            for (std::list<GPACounterPass>::iterator tmpPassIter = passPartitions.begin(); tmpPassIter != passPartitions.end(); ++tmpPassIter)
            {
                int existingOffset = VectorContains<unsigned int>(tmpPassIter->m_counters, internalCounterIter->m_hardwareIndex);

                if (existingOffset >= 0)
                {
                    counterAlreadyScheduled = true;

                    // record where to get the result from
                    AddCounterResultLocation(internalCounterIter->m_publicIndex, internalCounterIter->m_hardwareIndex, searchPassIndex, existingOffset);
                    break;
                }

                searchPassIndex++;
            }

            if (counterAlreadyScheduled)
            {
                // Don't need to schedule this counter,
                // continue on to the next internal counter that needs to be scheduled.
                continue;
            }

            // The counter needs to be scheduled.
            // if the first pass is not empty, then skip over the addition of another pass for this current counter.
            if (firstPassEmpty == false)
            {
                // make sure there is enough space for the next pass
                ++passIndex;
                AddNewPassInfo(passIndex, &passPartitions, &numUsedCountersPerPassPerBlock);
                ++currentPassIter;
                ++currentUsedCountersIter;
            }
            else
            {
                // the first counter is about to be scheduled in the pass, so
                // the pass will no longer be empty
                firstPassEmpty = false;
            }

            // the counter can be scheduled here.
            currentPassIter->m_counters.push_back(internalCounterIter->m_hardwareIndex);

            currentUsedCountersIter->m_numUsedCountersPerBlock[pAccessor->GroupIndex()].push_back(pAccessor->CounterIndex());
            numScheduledCounters += 1;

            // record where the result will be located
            unsigned int offset = (unsigned int)currentPassIter->m_counters.size() - 1;
            AddCounterResultLocation(internalCounterIter->m_publicIndex, internalCounterIter->m_hardwareIndex, passIndex, offset);
        }
    }
};
