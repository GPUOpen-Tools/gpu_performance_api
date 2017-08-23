//==============================================================================
// Copyright (c) 2014-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  This file implements the "consolidated" counter splitter
//==============================================================================


#ifndef _GPA_SPLITCOUNTERSCONSOLIDATED_H_
#define _GPA_SPLITCOUNTERSCONSOLIDATED_H_

#include <vector>
#ifdef DEBUG_PUBLIC_COUNTER_SPLITTER
    #include <sstream>
#endif
#include "GPASplitCountersInterfaces.h"
#include "GPAInternalCounter.h"
#include "GPASwCounterManager.h"

#if defined(WIN32)
    #include <Windows.h>
#endif // WIN32

/// Splits counters such that no individual public counter will be split into any more passes than minimally required.
/// This is done by splitting the public counter on its own, and then finding a set of passes that allows each of the public counter's
/// passes to be scheduled.
class GPASplitCountersConsolidated : public IGPASplitCounters
{
public:
    /// Initialize an instance of the GPASplitCountersConsolidated class.
    /// \param gpuTimestampGroupIndex The index of the GPUTimestamp group
    /// \param gpuTimestampBottomToBottomCounterIndex The global counter index of the bottom-bottom counter
    /// \param gpuTimestampTopToBottomCounterIndex The global counter index of the top-bottom counter
    /// \param maxSQCounters The maximum number of counters that can be simultaneously enabled on the SQ block
    /// \param numSQGroups The number of SQ counter groups.
    /// \param pSQCounterBlockInfo The list of SQ counter groups.
    /// \param numIsolatedFromSqGroups The number of counter groups that must be isolated from SQ counter groups
    /// \param pIsolatedFromSqGroups The list of counter groups that must be isolated from SQ counter groups
    GPASplitCountersConsolidated(unsigned int gpuTimestampGroupIndex,
                                 unsigned int gpuTimestampBottomToBottomCounterIndex,
                                 unsigned int gpuTimestampTopToBottomCounterIndex,
                                 unsigned int maxSQCounters,
                                 unsigned int numSQGroups,
                                 GPA_SQCounterGroupDesc* pSQCounterBlockInfo,
                                 unsigned int numIsolatedFromSqGroups,
                                 const unsigned int* pIsolatedFromSqGroups)
        :   IGPASplitCounters(gpuTimestampGroupIndex, gpuTimestampBottomToBottomCounterIndex,
                              gpuTimestampTopToBottomCounterIndex, maxSQCounters,
                              numSQGroups, pSQCounterBlockInfo, 
                              numIsolatedFromSqGroups, pIsolatedFromSqGroups)
    {
    };

    /// Destructor
    virtual ~GPASplitCountersConsolidated() {};

    //--------------------------------------------------------------------------
    // public counters that can fit in a single pass will be enabled in the same pass,
    // single-pass counters should not be split into multiple passes,
    // multi-pass counters should not take more passes than required,
    // no more than a fixed number of counters per pass.
    std::list<GPACounterPass> SplitCounters(const std::vector<const GPA_PublicCounter*>& publicCountersToSplit,
                                            const std::vector<GPAHardwareCounterIndices> internalCountersToSchedule,
                                            const std::vector<GPASoftwareCounterIndices> softwareCountersToSchedule,
                                            IGPACounterAccessor* accessor,
                                            const std::vector<unsigned int>& maxCountersPerGroup,
                                            unsigned int& numScheduledCounters)
    {
        // The maximum number of internal counters to enable in a single pass. This may be updated if any of the public counters require more than this value
        // to be enabled in a single pass, otherwise the algorithm would get stuck in an infinite loop trying to find a viable pass for the public counter.
        // Adjusting this value makes a big difference in the number of passes that will be generated. Currently a very low value (2) will results in 39 passes.
        // A high value (~180) will result in 17 passes; lowering down to 120 still results in 17 passes, but the actual counters in each pass are slightly changed.
        // Other values I tried: 40=33 passes, 50=28 passes, 60=24 passes, 100=19passes, 120+ = 17 passes.
        unsigned int maxInternalCountersPerPass = 120;

        // this will eventually be the return value
        std::list<GPACounterPass> passPartitions;

        // temporary variable to hold the number of counters assigned to each block during each of the passes.
        std::list<PerPassData> numUsedCountersPerPassPerBlock;

        // Handle the public counters
        //InsertPublicCounters(passPartitions, numUsedCountersPerPassPerBlock, numBlocks, numScheduledCounters, publicCountersToSplit, accessor, maxCountersPerGroup, maxInternalCountersPerPass);
        InsertPublicCounters(passPartitions, publicCountersToSplit,      accessor, numUsedCountersPerPassPerBlock, maxCountersPerGroup, numScheduledCounters, maxInternalCountersPerPass);

        // Handle the internal counters
        InsertHardwareCounters(passPartitions, internalCountersToSchedule, accessor, numUsedCountersPerPassPerBlock, maxCountersPerGroup, numScheduledCounters);

        // Handle the software counters
        InsertSoftwareCounters(passPartitions, softwareCountersToSchedule, accessor, numUsedCountersPerPassPerBlock, maxCountersPerGroup, numScheduledCounters);

        return passPartitions;
    };

protected:
    /// Test if this is a timestamp query based counter.
    /// Normally only the time counter is based on the timestamp query.
    /// \return True if the counter is based on the timestamp query, false if not
    /// \param[in] swCounterIndex The SW counter index
    virtual bool IsTimestampQueryCounter(const gpa_uint32 swCounterIndex) const
    {
        bool isTimestampQuery = false;
        const SwCounterDescVec* pSwCounters = s_pSwCounterManager->GetSwCounters();
        const gpa_uint32        amdCounters = s_pSwCounterManager->GetNumAmdCounters();

        if (0 == swCounterIndex && 0 == amdCounters && 0 == (gpa_uint32)pSwCounters->size())
        {
            s_pSwCounterManager->SetSwGPUTimeCounterIndex(swCounterIndex);
            s_pSwCounterManager->SetSwGPUTimeCounterEnabled(true);
            return true;
        }

        if (swCounterIndex >= amdCounters)
        {
            gpa_uint32 swCounterGroupIndex = swCounterIndex - amdCounters;

            if (swCounterGroupIndex < (gpa_uint32)pSwCounters->size())
            {
                const std::string gpuTime       = "GPUTime";
                const std::string d3dGPUTime    = "D3DGPUTime";
                const std::string vkGPUTime     = "VKGPUTime";
                const std::string preTimeStamp  = "PreBottomTimestamp";
                const std::string postTimeStamp = "PostBottomTimestamp";
                const std::string counterName   = pSwCounters->at(swCounterGroupIndex).m_name;

                if (counterName == d3dGPUTime || 
                    counterName == vkGPUTime ||
                    counterName == gpuTime || 
                    counterName == preTimeStamp || 
                    counterName == postTimeStamp)
                {
                    isTimestampQuery = true;

                    if (counterName == gpuTime || counterName == d3dGPUTime || counterName == vkGPUTime)
                    {
                        s_pSwCounterManager->SetSwGPUTimeCounterIndex(swCounterIndex);
                        s_pSwCounterManager->SetSwGPUTimeCounterEnabled(true);
                    }
                }
            }
        }

        return isTimestampQuery;
    }

private:

    /// Checks passes created for previous public counters to see if the counters in the specified pass are already all scheduled in the same pass
    /// If they are, then we can reuse that pass rather than creating a new pass for the current counter
    /// \param passPartitions the list of passes created for all previously scheduled public counters
    /// \param pass the pass whose counters we are checking to see if they are all already scheduled in a single pass
    /// \param[out] passIndex if the specified pass' counters are already scheduled, this will contain the passindex where they are scheduled
    /// \return true if the specifed pass' counters are already scheduled in a single pass, false otherwise
    bool CheckAllCountersScheduledInSamePass(std::list<GPACounterPass>& passPartitions, GPACounterPass pass, unsigned int& passIndex)
    {
        bool retVal = false;

        passIndex = 0;

        for (auto iterator = passPartitions.cbegin(); iterator != passPartitions.cend(); ++iterator, passIndex++)
        {
            if (iterator->m_counters.size() < pass.m_counters.size())
            {
                // current pass has fewer counters than pass to be scheduled
                continue;
            }

            // for each pre-existing pass, see if the current pass' counters are already scheduled
            bool allCountersInSamePass = true;

            for (auto passIter = pass.m_counters.cbegin(); passIter != pass.m_counters.cend(); ++passIter)
            {
                if (VectorContains<unsigned int>(iterator->m_counters, *passIter) == -1)
                {
                    allCountersInSamePass = false;
                    break;
                }
            }

            if (allCountersInSamePass)
            {
                retVal = true;
                break;
            }
        }

        return retVal;
    }

    /// Inserts each public counter into the earliest possible pass.
    /// \param[in,out] passPartitions The pass partitions that are generated
    /// \param publicCountersToSplit The incoming counters we need to split
    /// \param accessor A interface that accesses the public counters
    /// \param numUsedCountersPerPassPerBlock A list of passes, each consisting of the number of counters scheduled on each block
    /// \param maxCountersPerGroup A vector containing the maximum number of simultaneous counters for each block
    /// \param[in,out] numScheduledCounters The total number of counters that were scheduled
    /// \param maxInternalCountersPerPass the maximum number of counters per pass
    void InsertPublicCounters(std::list<GPACounterPass>& passPartitions,
                              const std::vector<const GPA_PublicCounter*>& publicCountersToSplit,
                              IGPACounterAccessor* accessor,
                              std::list<PerPassData>& numUsedCountersPerPassPerBlock,
                              const std::vector<unsigned int>& maxCountersPerGroup,
                              unsigned int& numScheduledCounters,
                              unsigned int maxInternalCountersPerPass)
    {
#ifdef DEBUG_PUBLIC_COUNTER_SPLITTER
        std::stringstream ss;
#endif
        // iterate through each public counter
        for (auto publicIter = publicCountersToSplit.cbegin(); publicIter != publicCountersToSplit.cend(); ++publicIter)
        {
            // Scheduling the counter is an iterative process, and this variable will keep track of which pass index the scheduling is starting from
            unsigned int startCounterPassIndex = 0;

            // make sure there is enough space for the next pass
            AddNewPassInfo(1, passPartitions, numUsedCountersPerPassPerBlock);

            // reset the iterators to the beginning each time we are trying to schedule a different public counter
            auto countersUsedIter = numUsedCountersPerPassPerBlock.begin();
            auto counterPassIter = passPartitions.begin();


            // find out the minimum required passes for the public counter
            const std::list<GPACounterPass> singleCounterPasses = SplitSingleCounter(*publicIter, accessor, maxCountersPerGroup);
#ifdef DEBUG_PUBLIC_COUNTER_SPLITTER
            ss.str("");
            ss << "Splitting Counter: " << (*publicIter)->m_pName << ". counterIndex: " << (*publicIter)->m_index << " numpasses: " << singleCounterPasses.size();
            GPA_LogDebugCounterDefs(ss.str().c_str());
#endif

            /// contains a map between the pass index for a single split public counter and the pass index
            /// for a previously scheduled pass that contains all of the hw counters for that pass
            /// For example, consider if counter XX can be split into 3 passes, and previously scheduled counters have been scheduled over 5 passes.
            /// If out of those five passes, pass 0, 4, and 5 already contain the counters from the single counter's pass 0, 1, and 2 repsectively,
            /// then this map will contain:
            ///   0 = 0
            ///   1 = 4
            ///   2 = 5
            /// This mapping is used later when setting up the results slots for the current counter
            std::map<unsigned int, unsigned int> existingPasses;

            // compare that to the existing passes
            // loop until we find a good pass to put the counter in.
            bool scheduledCounter = false;

            while (scheduledCounter == false)
            {
                // these variables keep track of which pass within the single counter is currently being evaluated
                unsigned int singleCounterPassIndex = 0;
                auto tmpCountersUsedIter = countersUsedIter;
                auto tmpCounterPassIter = counterPassIter;

                bool allPassesAreGood = true;
                unsigned int singlePassIndex = 0;
                existingPasses.clear();

                // loop through the singleCounterPasses and make sure there are no conflicts
                for (auto singleCounterPassIter = singleCounterPasses.cbegin(); singleCounterPassIter != singleCounterPasses.cend(); ++singleCounterPassIter)
                {
                    unsigned int passIndex;

                    if (CheckAllCountersScheduledInSamePass(passPartitions, *singleCounterPassIter, passIndex))
                    {
                        existingPasses[singlePassIndex++] = passIndex;
                        continue;
                    }

                    singlePassIndex++;
                    // update the max number of internal counters allowed per pass to ensure that this singleCounterPass will have a chance of fitting.
                    maxInternalCountersPerPass = std::max<unsigned int>(maxInternalCountersPerPass, (unsigned int)singleCounterPassIter->m_counters.size());

                    // make sure there is enough space for the next pass
                    AddNewPassInfo(singleCounterPassIndex + startCounterPassIndex + 1, passPartitions, numUsedCountersPerPassPerBlock);

                    if (singleCounterPassIndex > 0)
                    {
                        ++tmpCountersUsedIter;
                        ++tmpCounterPassIter;
                    }

                    // limit the pass to a maximum number of counters
                    if (tmpCounterPassIter->m_counters.size() + singleCounterPassIter->m_counters.size() > maxInternalCountersPerPass)
                    {
                        allPassesAreGood = false;
                    }
                    else
                    {
                        // local temp copy of the current pass info so that internal counters can be properly tracked for our 'testing' of the counters.
                        PerPassData tmpCurCountersUsed = *tmpCountersUsedIter;

                        // test each internal counter to see if they can all fit in the current consolidated passes
                        for (auto internalCounterIter = singleCounterPassIter->m_counters.cbegin(); internalCounterIter != singleCounterPassIter->m_counters.cend(); ++internalCounterIter)
                        {
                            // if the counter is already there, no need to add it
                            if (VectorContains<unsigned int>(tmpCounterPassIter->m_counters, *internalCounterIter) == -1)
                            {
                                // check to see if the counter can be added
                                accessor->SetCounterIndex(*internalCounterIter);
                                unsigned int groupIndex = accessor->GroupIndex();

                                if (CheckForTimestampCounters(accessor, *tmpCounterPassIter) == false || //use tmpCounterPassIter
                                    CanCounterBeAdded(accessor, tmpCurCountersUsed, maxCountersPerGroup) == false ||
                                    CheckForSQCounters(accessor, tmpCurCountersUsed, m_maxSQCounters) == false ||
                                    CheckCountersAreCompatible(accessor, tmpCurCountersUsed) == false)
                                {
                                    allPassesAreGood = false;
                                    break;
                                }
                                else
                                {
                                    // track that the internal counters was 'scheduled'
                                    tmpCurCountersUsed.m_numUsedCountersPerBlock[groupIndex].push_back(accessor->CounterIndex());
                                }
                            }
                        }
                    }

                    // The necessary passes for the single public counter did not fit with the previously scheduled counters.
                    // Update iterators to try the next pass.
                    if (allPassesAreGood == false)
                    {
                        // iterate to the next pass and see if the counters are better here.
                        ++singleCounterPassIndex;
                        AddNewPassInfo(singleCounterPassIndex + startCounterPassIndex + 1, passPartitions, numUsedCountersPerPassPerBlock);
                        ++countersUsedIter;
                        ++counterPassIter;
                        break;
                    }
                    else
                    {
                        ++singleCounterPassIndex;
                    }
                }

                if (allPassesAreGood)
                {
                    // schedule the counter
                    scheduledCounter = true;
                }
                else
                {
                    // the counter could not get scheduled starting from the current passIndex,
                    // so continue and try the next one
                    ++startCounterPassIndex;
                }
            }

            assert(scheduledCounter == true);

            // now actually add the counter to the found pass
            // iterate through all the internal counters and add them to the appropriate passes
            unsigned int passIndex = startCounterPassIndex;

            unsigned int singlePassIndex = 0;

            for (auto singleCounterPassIter = singleCounterPasses.cbegin(); singleCounterPassIter != singleCounterPasses.cend(); ++singleCounterPassIter)
            {
                // Check if the existingPasses mapping contains this pass -- if so, then we have to use the counter result location already added to the m_counterResultLocationMap member
                if (existingPasses.find(singlePassIndex) != existingPasses.cend())
                {
                    passIndex = existingPasses[singlePassIndex];

                    for (auto internalCounterIter = singleCounterPassIter->m_counters.cbegin(); internalCounterIter != singleCounterPassIter->m_counters.cend(); ++internalCounterIter)
                    {
                        unsigned int publicCounterIndex = (*publicIter)->m_index;
                        unsigned int hardwareCounterIndex = *internalCounterIter;

                        unsigned int curPass = 0;
                        auto it = passPartitions.cbegin();

                        for (; it != passPartitions.cend(); ++it, curPass++)
                        {
                            if (curPass == passIndex)
                            {
                                break;
                            }
                        }

                        int existingIndex = VectorContains<unsigned int>(it->m_counters, hardwareCounterIndex);

                        // we don't expect this to fail since we found these counters in "existingPasses"
                        assert(-1 != existingIndex);

                        unsigned int offset = (unsigned int)existingIndex;
                        AddCounterResultLocation(publicCounterIndex, hardwareCounterIndex, passIndex, offset);
                    }
                }
                else
                {
                    for (auto internalCounterIter = singleCounterPassIter->m_counters.cbegin(); internalCounterIter != singleCounterPassIter->m_counters.cend(); ++internalCounterIter)
                    {
                        unsigned int publicCounterIndex = (*publicIter)->m_index;
                        unsigned int hardwareCounterIndex = *internalCounterIter;

                        // only add the counter if it is not already there
                        int existingIndex = VectorContains<unsigned int>(counterPassIter->m_counters, hardwareCounterIndex);

                        if (existingIndex == -1)
                        {
                            accessor->SetCounterIndex(*internalCounterIter);
                            counterPassIter->m_counters.push_back(*internalCounterIter);
                            countersUsedIter->m_numUsedCountersPerBlock[accessor->GroupIndex()].push_back(accessor->CounterIndex());
                            numScheduledCounters += 1;

                            unsigned int offset = (unsigned int)counterPassIter->m_counters.size() - 1;

                            // find the correct pass that the counter was added to
                            passIndex = 0;

                            for (auto itt = passPartitions.begin(); itt != passPartitions.end() && itt != counterPassIter; ++itt)
                            {
                                ++passIndex;
                            }

                            AddCounterResultLocation(publicCounterIndex, hardwareCounterIndex, passIndex, offset);
                        }
                        else
                        {
                            unsigned int offset = (unsigned int)existingIndex;
                            AddCounterResultLocation(publicCounterIndex, hardwareCounterIndex, passIndex, offset);
                        }
                    }

                    // increment to the next pass
                    ++counterPassIter;
                    ++countersUsedIter;
                }

                singlePassIndex++;
                passIndex++;
            }
        }

#ifdef DEBUG_PUBLIC_COUNTER_SPLITTER
        ss.str("");
        ss << "total passes: " << passPartitions.size();
        GPA_LogDebugCounterDefs(ss.str().c_str());

        for (auto it : passPartitions)
        {
            ss.str("*****PASS*****");
            GPA_LogDebugCounterDefs(ss.str().c_str());

            for (auto it1 : it.m_counters)
            {
                ss.str("");
                ss << it1;
                GPA_LogDebugCounterDefs(ss.str().c_str());
            }

        }
#endif
    }

    /// Inserts each hardware counter into the earliest possible pass.
    /// NOTE: This could potentially do some load balancing by preferring passes with fewer counters in them.
    /// \param[in,out] passPartitions The pass partitions that are generated
    /// \param internalCounters The internal counters that need to be scheduled
    /// \param pAccessor A interface that accesses the internal counters
    /// \param numUsedCountersPerPassPerBlock A list of passes, each consisting of the number of counters scheduled on each block
    /// \param maxCountersPerGroup A vector containing the maximum number of simultaneous counters for each block
    /// \param[in,out] numScheduledCounters The total number of internal counters that were scheduled
    void InsertHardwareCounters(std::list<GPACounterPass>& passPartitions,
                                const std::vector<GPAHardwareCounterIndices> internalCounters,
                                IGPACounterAccessor* pAccessor,
                                std::list<PerPassData>& numUsedCountersPerPassPerBlock,
                                const std::vector<unsigned int>& maxCountersPerGroup,
                                unsigned int& numScheduledCounters)
    {
        // schedule each of the internal counters
        for (auto internalCounterIter = internalCounters.cbegin(); internalCounterIter != internalCounters.cend(); ++internalCounterIter)
        {
            // if the counter is already scheduled in any pass, there is no reason to add it again.
            bool counterAlreadyScheduled = false;
            unsigned int passIndex = 0;

            for (auto passIter = passPartitions.cbegin(); passIter != passPartitions.cend(); ++passIter)
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
            AddNewPassInfo(1, passPartitions, numUsedCountersPerPassPerBlock);

            pAccessor->SetCounterIndex(internalCounterIter->m_hardwareIndex);

            // Iterate through the passes again and find one where the counter can be inserted.
            passIndex = 0;
            auto countersUsedIter = numUsedCountersPerPassPerBlock.begin();

            for (auto passIter = passPartitions.begin(); passIter != passPartitions.end(); ++passIter)
            {
                if (CheckForTimestampCounters(pAccessor, *passIter) == true &&
                    CanCounterBeAdded(pAccessor, *countersUsedIter, maxCountersPerGroup) == true &&
                    CheckForSQCounters(pAccessor, *countersUsedIter, m_maxSQCounters) == true &&
                    CheckCountersAreCompatible(pAccessor, *countersUsedIter) == true)
                {
                    // the counter can be scheduled here.
                    passIter->m_counters.push_back(internalCounterIter->m_hardwareIndex);
                    countersUsedIter->m_numUsedCountersPerBlock[pAccessor->GroupIndex()].push_back(pAccessor->CounterIndex());
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
                    AddNewPassInfo(passIndex + 1, passPartitions, numUsedCountersPerPassPerBlock);

                    // increment the iterator after any necessary new passes have been allocated.
                    ++countersUsedIter;
                }
            }
        }
    }

    /// Inserts each software counter into the earliest possible pass.
    /// NOTE: This could potentially do some load balancing by preferring passes with fewer counters in them.
    /// \param[in,out] passPartitions The pass partitions that are generated
    /// \param swCountersToSchedule The software counters that need to be scheduled
    /// \param pAccessor A interface that accesses the internal counters
    /// \param numUsedCountersPerPassPerBlock A list of passes, each consisting of the number of counters scheduled on each block
    /// \param maxCountersPerGroup A vector containing the maximum number of simultaneous counters for each block
    /// \param[in,out] numScheduledCounters The total number of internal counters that were scheduled
    void InsertSoftwareCounters(std::list<GPACounterPass>& passPartitions,
                                const std::vector<GPASoftwareCounterIndices> swCountersToSchedule,
                                IGPACounterAccessor* pAccessor,
                                std::list<PerPassData>& numUsedCountersPerPassPerBlock,
                                const std::vector<unsigned int>& maxCountersPerGroup,
                                unsigned int& numScheduledCounters)
    {
        if (0 < swCountersToSchedule.size())
        {
            UNREFERENCED_PARAMETER(maxCountersPerGroup);
            // Add the first SW pass
            unsigned int existingPassCount = static_cast<unsigned int>(passPartitions.size());
            AddNewPassInfo(existingPassCount + 1, passPartitions, numUsedCountersPerPassPerBlock);
            static const unsigned int maxScheduledCountersInPassCount = 120;
            s_pSwCounterManager->ClearSwCounterMap();
            s_pSwCounterManager->SetSwGPUTimeCounterEnabled(false);
            bool firstNonTimeCounter = true;

            for (const auto& swCounter : swCountersToSchedule)
            {
                unsigned int passIndex       = 0;
                bool counterAlreadyScheduled = false;
                auto passIter                = passPartitions.begin();
                bool swTimePass              = false;

                while ((passPartitions.end() != passIter) && (!counterAlreadyScheduled))
                {
                    int existingOffset =
                        VectorContains<unsigned int>(passIter->m_counters, swCounter.m_softwareIndex);

                    if (existingOffset >= 0)
                    {
                        counterAlreadyScheduled = true;
                        AddCounterResultLocation(
                            swCounter.m_publicIndex, swCounter.m_softwareIndex, passIndex, existingOffset);
                    }

                    ++passIndex;
                    ++passIter;
                }

                if (!counterAlreadyScheduled)
                {
                    auto revPassIter = passPartitions.rbegin();
                    passIndex = static_cast<unsigned int>(passPartitions.size() - 1);
                    auto countersUsedIter = numUsedCountersPerPassPerBlock.begin();
                    swTimePass = IsTimestampQueryCounter(swCounter.m_publicIndex);

                    if ((revPassIter->m_counters.size() >= maxScheduledCountersInPassCount) || (!swTimePass && s_pSwCounterManager->SwGPUTimeCounterEnabled()))
                    {
                        if (firstNonTimeCounter)
                        {
                            ++passIndex;
                            AddNewPassInfo(passIndex + 1, passPartitions, numUsedCountersPerPassPerBlock);
                            revPassIter = passPartitions.rbegin();
                            firstNonTimeCounter = false;
                        }
                    }

                    revPassIter->m_counters.push_back(swCounter.m_softwareIndex);
                    pAccessor->SetCounterIndex(swCounter.m_softwareIndex);
                    countersUsedIter->m_numUsedCountersPerBlock[pAccessor->GroupIndex()].push_back(
                        pAccessor->CounterIndex());
                    unsigned int offset = static_cast<unsigned int>(revPassIter->m_counters.size() - 1);
                    AddCounterResultLocation(
                        swCounter.m_publicIndex, swCounter.m_softwareIndex, passIndex, offset);
                    s_pSwCounterManager->AddSwCounterMap(
                        swCounter.m_publicIndex, swCounter.m_softwareIndex);
                    ++numScheduledCounters;
                }
            }
        }
    }


    /// Separate a single counter into multiple passes based on the maxCountersPerGroup
    /// \param pPublicCounter the counter that needs to be split
    /// \param pAccessor the counter accessor for the counter
    /// \param maxCountersPerGroup the list of max counters per group
    /// \return a list of passes
    std::list<GPACounterPass> SplitSingleCounter(const GPA_PublicCounter* pPublicCounter, IGPACounterAccessor* pAccessor, const std::vector<unsigned int>& maxCountersPerGroup)
    {
        // this will eventually be the return value
        std::list<GPACounterPass> passPartitions;
        GPACounterPass counterPass;
        passPartitions.push_back(counterPass);

        // temporary variable to hold the number of counters assigned to each block during each of the passes.
        std::list<PerPassData> numUsedCountersPerPassPerBlock;
        PerPassData newPass;
        numUsedCountersPerPassPerBlock.push_back(newPass);

        // copy the set of unallocated counters
        std::vector<gpa_uint32> countersUnallocated = pPublicCounter->m_internalCountersRequired;

        // iterate through the unallocated counters and put them into the appropriate pass
        for (auto counterIter = countersUnallocated.cbegin(); counterIter != countersUnallocated.cend(); ++counterIter)
        {
            unsigned int passIndex = 0;
            auto countersUsedIter = numUsedCountersPerPassPerBlock.begin();
            auto counterPassIter = passPartitions.begin();

            bool doneAllocatingCounter = false;

            while (doneAllocatingCounter == false)
            {
                // make sure there is a partition for current pass
                while (passIndex >= passPartitions.size())
                {
                    GPACounterPass counterPassInner;
                    passPartitions.push_back(counterPassInner);
                }

                // make sure there are counts for the number of used counters for current pass
                while (passIndex >= numUsedCountersPerPassPerBlock.size())
                {
                    PerPassData newPassInner;
                    numUsedCountersPerPassPerBlock.push_back(newPassInner);
                }

                // increment the pass iterator if past the first loop
                if (passIndex > 0)
                {
                    ++countersUsedIter;
                    ++counterPassIter;
                }

                pAccessor->SetCounterIndex(*counterIter);
                unsigned int groupIndex = pAccessor->GroupIndex();

                // try to add the counter to the current pass
                if (CheckForTimestampCounters(pAccessor, *counterPassIter) &&
                    CanCounterBeAdded(pAccessor, *countersUsedIter, maxCountersPerGroup) &&
                    CheckForSQCounters(pAccessor, *countersUsedIter, m_maxSQCounters) &&
                    CheckCountersAreCompatible(pAccessor, *countersUsedIter))
                {
                    counterPassIter->m_counters.push_back(*counterIter);
                    countersUsedIter->m_numUsedCountersPerBlock[groupIndex].push_back(pAccessor->CounterIndex());
                    doneAllocatingCounter = true;
                }
                else
                {
                    // the counters needs to go into the next pass. Increment the pass index and let the loop happen again
                    ++passIndex;
                }
            } // end while loop to find a suitable pass for the current counter
        } // end for loop over each of the internal counters

        // return the passes
        return passPartitions;
    }
};

#endif // _GPA_SPLITCOUNTERSCONSOLIDATED_H_
