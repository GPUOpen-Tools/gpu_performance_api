//==============================================================================
// Copyright (c) 2016-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Interfaces used for counter splitting
//==============================================================================

#ifndef _GPA_SPLIT_COUNTER_INTERFACES_H_
#define _GPA_SPLIT_COUNTER_INTERFACES_H_

#include "GPAPublicCounters.h"
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

#ifdef DEBUG_PUBLIC_COUNTER_SPLITTER
    #include "Logging.h"
    #include <sstream>
#endif

/// enum to represent the different SQ shader stages
enum GPA_SQShaderStage
{
    SQ_ALL,         ///< All stages
    SQ_ES,          ///< ES Stage
    SQ_GS,          ///< GS Stage
    SQ_VS,          ///< VS Stage
    SQ_PS,          ///< PS Stage
    SQ_LS,          ///< LS Stage
    SQ_HS,          ///< HS Stage
    SQ_CS,          ///< CS Stage
    SQ_LAST = SQ_CS ///< last known stage
};

/// structure representing an SQ counter group
struct GPA_SQCounterGroupDesc
{
    gpa_uint32 m_groupIndex;            ///< 0-based index of the group
    gpa_uint32 m_shaderEngine;          ///< 0-based index of the shader engine for this group
    GPA_SQShaderStage m_stage;          ///< the shader stage for this group
};

/// structure to store the counters that are assigned to a particular pass.
struct GPACounterPass
{
    /// The counters assigned to a profile pass.
    std::vector<unsigned int> m_counters;
};

typedef std::list<GPACounterPass> GPACounterPassList; ///< Typedef for a list of counter passes

/// Stores the number of counters from each block that are used in a particular pass.
struct PerPassData
{
    /// The list of counters used from each HW block. Map from group index to list of counters
    std::map<unsigned int, std::vector<gpa_uint32> > m_numUsedCountersPerBlock;
};

/// Stores the counter indices for hardware counters
struct GPAHardwareCounterIndices
{
    unsigned int m_publicIndex;   ///< The index of the hardware counter as exposed by GPUPerfAPI (first hw counter is after all public counters)
    unsigned int m_hardwareIndex; ///< The 0-based index of the hardware counter
};

/// Stores the counter indices for software counters
struct GPASoftwareCounterIndices
{
    unsigned int m_publicIndex;   ///< The index of the software counter as exposed by GPUPerfAPI (first sw counter is after all public counters)
    unsigned int m_softwareIndex; ///< The 0-based index of the software counter
};

/// Records where to locate the results of a counter query in session requests
class GPA_CounterResultLocation
{
public:
    gpa_uint16 m_pass;   ///< index of the pass
    gpa_uint16 m_offset; ///< offset within pass ( 0 is first counter )
};

/// Interface for accessing information of an internal counter.
class IGPACounterGroupAccessor
{
public:

    /// Initializes an instance of the IGPACounterAccessor interface.
    IGPACounterGroupAccessor() {};

    /// Virtual destructor
    virtual ~IGPACounterGroupAccessor() {};

    /// Sets the counter index of which to get the group and counter Id.
    /// \param index The counter index.
    virtual void SetCounterIndex(unsigned int index) = 0;

    /// Get the 0-based group index of the internal counter.
    /// \return The group index.
    virtual unsigned int GroupIndex() const = 0;

    /// Get the 0-based counter index of the internal counter.
    /// \return The counter index.
    virtual unsigned int CounterIndex() const = 0;

    /// Get the hardware counter bool
    /// \return True if the counter is a hardware counter
    virtual bool IsHWCounter() const = 0;

    /// Get the software counter bool
    /// \return True if the counter is a software counter
    virtual bool  IsSWCounter() const = 0;

    /// Get the global group group index (the full index of the software groups that come after the hardware groups)
    /// \return The total number of groups
    virtual unsigned int GlobalGroupIndex() const = 0;
};

/// Interface for a class that can split public and internal counters into separate passes.
class IGPASplitCounters
{
public:
    /// Initializes a new instance of the IGPASplitCounters interface.
    /// \param gpuTimestampGroupIndex The index of the GPUTimestamp group
    /// \param gpuTimestampBottomToBottomCounterIndex The global counter index of the bottom-bottom counter
    /// \param gpuTimestampTopToBottomCounterIndex The global counter index of the top-bottom counter
    /// \param maxSQCounters The maximum number of counters that can be simultaneously enabled on the SQ block
    /// \param numSQGroups The number of SQ counter groups.
    /// \param pSQCounterBlockInfo The list of SQ counter groups.
    /// \param numIsolatedFromSqGroups The number of counter groups that must be isolated from SQ counter groups
    /// \param pIsolatedFromSqGroups The list of counter groups that must be isolated from SQ counter groups
    IGPASplitCounters(unsigned int gpuTimestampGroupIndex,
                      unsigned int gpuTimestampBottomToBottomCounterIndex,
                      unsigned int gpuTimestampTopToBottomCounterIndex,
                      unsigned int maxSQCounters,
                      unsigned int numSQGroups,
                      GPA_SQCounterGroupDesc* pSQCounterBlockInfo,
                      unsigned int numIsolatedFromSqGroups,
                      const unsigned int* pIsolatedFromSqGroups)
        : m_gpuTimestampGroupIndex(gpuTimestampGroupIndex),
          m_gpuTimestampBottomToBottomCounterIndex(gpuTimestampBottomToBottomCounterIndex),
          m_gpuTimestampTopToBottomCounterIndex(gpuTimestampTopToBottomCounterIndex),
          m_maxSQCounters(maxSQCounters)
    {
        for (unsigned int i = 0; i < numSQGroups; i++)
        {
            m_sqCounterIndexMap[pSQCounterBlockInfo[i].m_groupIndex] = pSQCounterBlockInfo[i];
            m_sqShaderStageGroupMap[pSQCounterBlockInfo[i].m_stage].push_back(pSQCounterBlockInfo[i].m_groupIndex);
            m_sqCounterIndexSet.insert(pSQCounterBlockInfo[i].m_groupIndex);
        }

        for (uint32_t i = 0; i < numIsolatedFromSqGroups; ++i)
        {
            m_isolatedFromSqGroupIndexSet.insert(pIsolatedFromSqGroups[i]);
        }
    }

    /// Destructor
    virtual ~IGPASplitCounters()
    {
        m_sqCounterIndexMap.clear();
        m_sqShaderStageGroupMap.clear();
    }

    /// Splits counters into multiple passes.
    /// \param publicCountersToSplit The set of public counters that need to be split into passes.
    /// \param internalCountersToSchedule Additional internal counters that need to be scheduled (used by internal builds).
    /// \param softwareCountersToSchedule Additional software counters that need to be scheduled
    /// \param pAccessor A class to access the internal counters.
    /// \param maxCountersPerGroup The maximum number of counters that can be enabled in a single pass on each HW block or SW group.
    /// \param[out] numScheduledCounters Indicates the total number of internal counters that were assigned to a pass.
    /// \return The list of passes that the counters are separated into.
    virtual std::list<GPACounterPass> SplitCounters(const std::vector<const GPA_PublicCounter*>& publicCountersToSplit,
                                                    const std::vector<GPAHardwareCounterIndices> internalCountersToSchedule,
                                                    const std::vector<GPASoftwareCounterIndices>  softwareCountersToSchedule,
                                                    IGPACounterGroupAccessor* pAccessor,
                                                    const std::vector<unsigned int>& maxCountersPerGroup,
                                                    unsigned int& numScheduledCounters) = 0;

    /// Get the counter result locations
    /// \return The map of counter result locations
    std::map< unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > GetCounterResultLocations()
    {
        return m_counterResultLocationMap;
    }

protected:

    unsigned int m_gpuTimestampGroupIndex; ///< index of the GPUTimestamp group (-1 if it doesn't exist)
    unsigned int m_gpuTimestampBottomToBottomCounterIndex;   ///< index of the Bottom-to-Bottom GPUTime counter (-1 if it doesn't exist)
    unsigned int m_gpuTimestampTopToBottomCounterIndex;      ///< index of the Top-to-Bottom GPUTime counter (-1 if it doesn't exist)
    unsigned int m_maxSQCounters; ///< The maximum number of counters that can be enabled in the SQ group

    std::map<gpa_uint32, GPA_SQCounterGroupDesc> m_sqCounterIndexMap;           ///< map from group index to the SQ counter group description for that group
    std::map<GPA_SQShaderStage, vector<unsigned int> > m_sqShaderStageGroupMap; ///< map from shader stage to the list of SQ groups for that stage
    std::set<gpa_uint32> m_sqCounterIndexSet;                                   ///< set of SQ counter groups

    std::set<gpa_uint32> m_isolatedFromSqGroupIndexSet;  ///< set of groups that must be isolated from SQ groups

    /// A map between a public counter index and the set of hardware counters that compose the public counter.
    /// For each hardware counter, there is a map from the hardware counter to the counter result location (pass and offset) for that specific counter.
    /// Multiple public counters may be enabled which require the same hardware counter, but the hardware counter may be profiled in multiple passes so
    /// that the public counters will be consistent. This complex set of maps allows us to find the correct pass and offset for the instance of a
    /// hardware counter that is required for a specific public counter.
    std::map< unsigned int, std::map<unsigned int, GPA_CounterResultLocation> > m_counterResultLocationMap;

    /// Adds a counter result location.
    /// \param publicCounterIndex the index of the public counter whose result location is being added.
    /// \param hardwareCounterIndex the index of a particular hardware counter that makes up the public counter specified by publicCounterIndex.
    /// \param passIndex the index of the pass in which the counter is scheduled.
    /// \param offset the offset of the result within that pass.
    void AddCounterResultLocation(unsigned int publicCounterIndex, unsigned int hardwareCounterIndex, unsigned int passIndex, unsigned int offset)
    {
        GPA_CounterResultLocation location;
        location.m_offset = static_cast<gpa_uint16>(offset);
        location.m_pass = static_cast<gpa_uint16>(passIndex);

        m_counterResultLocationMap[publicCounterIndex][hardwareCounterIndex] = location;
#ifdef DEBUG_PUBLIC_COUNTER_SPLITTER
        std::stringstream ss;
        ss << "Result location for public counter: " << publicCounterIndex << ", hardwarecounter: " << hardwareCounterIndex << " is offset: " << offset << " in pass: " << passIndex;
        GPA_LogDebugCounterDefs(ss.str().c_str());
#endif
    }

    /// Scans a vector to determine if it contains a specified element.
    /// \param array The vector to scan.
    /// \param element The item to search for.
    /// \return -1 if the vector does not contain the element.
    /// \return The index of the element if the vector does contain it.
    template <class T> int VectorContains(const vector<T>& array, const T& element)
    {
        int arraySize = static_cast<int>(array.size());

        for (int i = 0; i < arraySize; i++)
        {
            if (array[i] == element)
            {
                return i;
            }
        }

        return -1;
    };

    //--------------------------------------------------------------------------
    /// Tests to see if the counter group is an SQ counter group
    /// \param pAccessor The counter accessor that describes the counter that needs to be scheduled.
    /// \return True if a counter is an SQ group counter
    bool IsSqCounterGroup(const IGPACounterGroupAccessor* pAccessor) const
    {
        unsigned int groupIndex = pAccessor->GlobalGroupIndex();
        return m_sqCounterIndexSet.find(groupIndex) != m_sqCounterIndexSet.end();
    }

    //--------------------------------------------------------------------------
    /// Tests to see if the counter group must be isolated from an SQ counter group
    /// \param pAccessor The counter accessor that describes the counter that needs to be scheduled.
    /// \return True if a counter must be isolated from SQ group counters
    bool IsCounterGroupIsolatedFromSqCounterGroup(const IGPACounterGroupAccessor* pAccessor) const
    {
        unsigned int groupIndex = pAccessor->GlobalGroupIndex();
        return m_isolatedFromSqGroupIndexSet.find(groupIndex) != m_isolatedFromSqGroupIndexSet.end();
    }

    //--------------------------------------------------------------------------
    /// Tests to see if the enabled counters include one of those in the parameter set
    /// \param currentPassData The counters enabled on each block in the current pass.
    /// \param counterSet List of counter groups to check for in the enabled set.
    /// \return True if a counter enabled in the current pass is a member of the validation set
    bool EnabledCounterGroupsContain(const PerPassData& currentPassData, const std::set<uint32_t>& counterSet) const
    {
        for (const auto& groupEntry : currentPassData.m_numUsedCountersPerBlock)
        {
            // Is the counter group in the list of interest?
            if (counterSet.find(groupEntry.first) == counterSet.end())
            {
                continue;
            }

            // Check if any counters are scheduled on it
            if (groupEntry.second.size())
            {
                return true;
            }
        }

        return false;
    }

    //--------------------------------------------------------------------------
    /// Tests to see if the counter group that needs to be scheduled is compatible with those already scheduled
    /// \param pAccessor The counter accessor that describes the counter that needs to be scheduled.
    /// \param currentPassData The counters enabled on each block in the current pass.
    /// \return True if the counter is compatible with counters already scheduled on the current pass
    bool CheckCountersAreCompatible(const IGPACounterGroupAccessor* pAccessor, const PerPassData& currentPassData) const
    {
        // SQ counters cannot be scheduled on the same pass as TCC/TA/TCP/TCA/TD counters (and vice versa)

        if (IsSqCounterGroup(pAccessor))
        {
            return !EnabledCounterGroupsContain(currentPassData, m_isolatedFromSqGroupIndexSet);
        }

        if (IsCounterGroupIsolatedFromSqCounterGroup(pAccessor))
        {
            return !EnabledCounterGroupsContain(currentPassData, m_sqCounterIndexSet);
        }

        return true;
    }

    //--------------------------------------------------------------------------
    /// Ensures that there are enough pass partitions and per pass data for the number of required passes.
    /// \param numRequiredPasses The number of passes that must be available in the arrays.
    /// \param[in,out] pPassPartitions The list to add additional pass partitions.
    /// \param[in,out] pNumUsedCountersPerPassPerBlock The list to which additional used counter info should be added.
    void AddNewPassInfo(unsigned int numRequiredPasses, std::list<GPACounterPass>* pPassPartitions, std::list<PerPassData>* pNumUsedCountersPerPassPerBlock)
    {
        while (pPassPartitions->size() < numRequiredPasses)
        {
            GPACounterPass counterPass;
            pPassPartitions->push_back(counterPass);

            PerPassData newPass;
            pNumUsedCountersPerPassPerBlock->push_back(newPass);
        }
    }

    //--------------------------------------------------------------------------
    /// Tests to see if a counter can be added to the specified groupIndex based on the number of counters allowed in a single pass for a particular block / group.
    /// \param pAccessor The counter accessor that describes the counter that needs to be scheduled.
    /// \param currentPassData Contains the number of counters enabled on each block in the current pass.
    /// \param maxCountersPerGroup Contains the maximum number of counters allowed on each block in a single pass.
    /// \return True if a counter can be added; false if not.
    bool CanCounterBeAdded(const IGPACounterGroupAccessor* pAccessor, PerPassData& currentPassData, const std::vector<unsigned int>& maxCountersPerGroup)
    {
        unsigned int groupIndex = pAccessor->GlobalGroupIndex();
        size_t newGroupUsedCount = 1;

        if (currentPassData.m_numUsedCountersPerBlock.count(groupIndex) > 0)
        {
            newGroupUsedCount += currentPassData.m_numUsedCountersPerBlock[groupIndex].size();
        }

        unsigned int groupLimit = maxCountersPerGroup[groupIndex];

        return newGroupUsedCount <= groupLimit;
    }

    //--------------------------------------------------------------------------
    /// Checks the current pass data to see if there are SQ counters on it, and will only allow counters belonging to the same SQ stage.
    /// \param pAccessor counter accessor that describes the counter that needs to be scheduled.
    /// \param currentPassData The number of counters enabled on each block in the current pass.
    /// \param maxSQCounters The maximum number of simultaneous counters allowed on the SQ block.
    /// \return True if a counter can be added to the block specified by blockIndex; false if the counter cannot be scheduled.
    bool CheckForSQCounters(const IGPACounterGroupAccessor* pAccessor, PerPassData& currentPassData, unsigned int maxSQCounters)
    {
        unsigned int groupIndex = pAccessor->GlobalGroupIndex();
        unsigned int counterIndex = pAccessor->CounterIndex();

        if (m_sqCounterIndexMap.count(groupIndex) == 0)
        {
            // this counter is not an SQ counter so return true
            return true;
        }

        GPA_SQCounterGroupDesc sqCounterGroup = m_sqCounterIndexMap[groupIndex];
        vector<unsigned int> groups = m_sqShaderStageGroupMap[sqCounterGroup.m_stage]; // groups for this stage

        vector<unsigned int> thisStageCounters;

        // check if this counter has already been added (either via the current or a different shader engine)
        for (vector<unsigned int>::const_iterator it = groups.begin(); it != groups.end(); ++it)
        {
            unsigned int thisGroupIndex = m_sqCounterIndexMap[*it].m_groupIndex;

            if (currentPassData.m_numUsedCountersPerBlock.count(thisGroupIndex) > 0)
            {
                for (unsigned int i = 0; i < currentPassData.m_numUsedCountersPerBlock[thisGroupIndex].size(); i++)
                {
                    unsigned int curCounter = currentPassData.m_numUsedCountersPerBlock[thisGroupIndex][i];
                    vector<unsigned int>::const_iterator it2 = std::find(thisStageCounters.begin(), thisStageCounters.end(), curCounter);

                    if (it2 == thisStageCounters.end())
                    {
                        thisStageCounters.push_back(curCounter);
                    }

                    if (currentPassData.m_numUsedCountersPerBlock[thisGroupIndex][i] == counterIndex)
                    {
                        // this counter was already added via a different shader engine so allow it here
                        return true;
                    }
                }
            }
        }

        // now check that we haven't exceeded the max number of SQ counters in this stage
        if (thisStageCounters.size() >= maxSQCounters)
        {
            return false;
        }

        // check that no counters from other stages are enabled

        for (unsigned int i = SQ_ALL; i <= SQ_LAST; i++)
        {
            if (static_cast<GPA_SQShaderStage>(i) == sqCounterGroup.m_stage)
            {
                continue;
            }

            for (vector<unsigned int>::const_iterator it = m_sqShaderStageGroupMap[static_cast<GPA_SQShaderStage>(i)].begin(); it != m_sqShaderStageGroupMap[static_cast<GPA_SQShaderStage>(i)].end(); ++it)
            {
                if (currentPassData.m_numUsedCountersPerBlock[*it].size() > 0)
                {
                    return false;
                }
            }
        }

        return true;
    }
    //--------------------------------------------------------------------------
    /// Checks if there are timestamp counters -- the counters need to go in their own pass.
    /// This is because idles must not be active when they are read, and when measuring counters idles are used.
    /// \param pAccessor counter accessor that describes the counter that needs to be scheduled.
    /// \param currentPassCounters list of counters in current pass.
    /// \return true if the counter passes this check (not a timestamp, or it is a timestamp and can be added); false if the counter is a timestamp and cannot be added.
    bool CheckForTimestampCounters(const IGPACounterGroupAccessor* pAccessor, const GPACounterPass& currentPassCounters)
    {
        unsigned int blockIndex = pAccessor->GlobalGroupIndex();

        // if this is not a gpuTime counter, it can potentially be added.
        if (blockIndex != m_gpuTimestampGroupIndex)
        {
            // but only if there are no timestamp counters in the current pass.
            bool passContainsGPUTimeCounter = false;

            for (size_t i = 0; i < currentPassCounters.m_counters.size(); i++)
            {
                if (currentPassCounters.m_counters[i] == m_gpuTimestampBottomToBottomCounterIndex ||
                    currentPassCounters.m_counters[i] == m_gpuTimestampTopToBottomCounterIndex)
                {
                    passContainsGPUTimeCounter = true;
                    break;
                }
            }

            return !passContainsGPUTimeCounter;
        }

        // the counter is a GPUTimestamp counter.
        // If there are no other counters in this pass,
        // check if can add timestamp
        size_t numCountersInPass = currentPassCounters.m_counters.size();

        if (numCountersInPass == 0)
        {
            //it's the first counter so it's ok
            return true;
        }

        return false;
    }
};

#endif //_GPA_SPLIT_COUNTER_INTERFACES_H_
