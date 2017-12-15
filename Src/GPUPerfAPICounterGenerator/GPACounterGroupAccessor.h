//==============================================================================
// Copyright (c) 2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Counter group accessor class
//==============================================================================

#ifndef _GPA_COUNTER_GROUP_ACCESSOR_H_
#define _GPA_COUNTER_GROUP_ACCESSOR_H_

#include "GPAInternalCounter.h"
#include "GPASplitCountersInterfaces.h"

/// Indexes into an array of internal groups and counters and can access data from the internal counter.
class GPACounterGroupAccessor : IGPACounterGroupAccessor
{
public:

    /// Initializes a new instance of the GPACounterGroupAccessor class.
    GPACounterGroupAccessor(GPA_CounterGroupDesc* pHardwareGroups,
                            unsigned int hardwareGroupCount,
                            GPA_CounterGroupDesc* pHardwareAdditionalGroups,
                            unsigned int hardwareAdditionalGroupCount,
                            GPA_CounterGroupDesc* pSoftwareGroups,
                            unsigned int softwareGroupCount)
        :
        m_pHardwareGroups(pHardwareGroups),
        m_hardwareGroupCount(hardwareGroupCount),
        m_pHardwareAdditionalGroups(pHardwareAdditionalGroups),
        m_hardwareAdditionalGroupCount(hardwareAdditionalGroupCount),
        m_pSoftwareGroups(pSoftwareGroups),
        m_softwareGroupCount(softwareGroupCount),
        m_groupIndex(0),
        m_counterIndex(0)
    {
        m_isHW = false;
        m_isAdditionalHW = false;
        m_isSW = false;
    }

    /// Destructor
    virtual ~GPACounterGroupAccessor() = default;

    /// \copydoc IGPACounterGroupAccessor::SetCounterIndex()
    void SetCounterIndex(unsigned int index) override
    {
        // count the number of counters that belong to groups that do not include the desired index
        unsigned int prevGroupCounters = 0;
        unsigned int tmpSum = 0;

        m_isHW = false;
        m_isAdditionalHW = false;
        m_isSW = false;

        unsigned int internalCounters = 0;

        for (unsigned int i = 0; i < m_hardwareGroupCount; ++i)
        {
            internalCounters += static_cast<unsigned int>(m_pHardwareGroups[i].m_numCounters);
        }

        for (unsigned int i = 0; i < m_hardwareGroupCount; ++i)
        {
            tmpSum = prevGroupCounters + static_cast<unsigned int>(m_pHardwareGroups[i].m_numCounters);

            if (tmpSum > index)
            {
                // this group contains the desired counter index.
                // this is the right group, and we can calculate the right counter.
                m_groupIndex = i;
                m_counterIndex = index - prevGroupCounters;

                // This is a HW counter
                m_isHW = true;

                // break from the loop
                break;
            }
            else
            {
                // this group does not include the desired counter index.
                // update the count and let the loop continue.
                prevGroupCounters = tmpSum;
            }
        }

        if (m_isHW == true)
        {
            return;
        }

        for (unsigned int i = 0; i < m_hardwareAdditionalGroupCount; ++i)
        {
            tmpSum = prevGroupCounters + static_cast<unsigned int>(m_pHardwareAdditionalGroups[i].m_numCounters);

            if (tmpSum > index)
            {
                // this group contains the desired counter index.
                // this is the right group, and we can calculate the right counter.
                m_groupIndex = i;
                m_counterIndex = index - prevGroupCounters;

                // This is an additional HW counter
                m_isAdditionalHW = true;

                // break from the loop
                break;
            }
            else
            {
                // this group does not include the desired counter index.
                // update the count and let the loop continue.
                prevGroupCounters = tmpSum;
            }
        }

        if (m_isAdditionalHW == true)
        {
            return;
        }

        m_groupIndex = 0;
        m_isSW = true;

        if (index >= internalCounters)
        {
            m_counterIndex = index - internalCounters;
        }
        else
        {
            m_counterIndex = index;
        }
    }

    /// \copydoc IGPACounterGroupAccessor::GroupIndex()
    unsigned int GroupIndex() const  override
    {
        return m_groupIndex;
    }

    /// \copydoc IGPACounterGroupAccessor::CounterIndex()
    unsigned int CounterIndex() const  override
    {
        return m_counterIndex;
    }

    /// \copydoc IGPACounterGroupAccessor::IsHWCounter()
    bool IsHWCounter() const  override
    {
        return m_isHW;
    }

    /// \copydoc IGPACounterGroupAccessor::IsSWCounter()
    bool IsSWCounter() const  override
    {
        return m_isSW;
    }

    /// \copydoc IGPACounterGroupAccessor::GlobalGroupIndex()
    unsigned int GlobalGroupIndex() const  override
    {
        unsigned int globalGroupIndex = GroupIndex();

        if (m_isAdditionalHW)
        {
            // If this is a software counter then add in the HW group count
            globalGroupIndex += m_hardwareGroupCount;
        }

        if (m_isSW)
        {
            // If this is a software counter then add in the HW group count
            globalGroupIndex += m_hardwareAdditionalGroupCount;
        }

        return globalGroupIndex;
    }

    /// Get the additional hardware counter bool
    /// \return True if the counter is an additional hardware counter (one exposed by the driver, but not by GPA)
    bool IsAdditionalHWCounter() const
    {
        return m_isAdditionalHW;
    }

private:

    GPA_CounterGroupDesc*             m_pHardwareGroups;                    ///< Points to the array of internal hardware counter groups
    unsigned int                      m_hardwareGroupCount;                 ///< stores the number of hardware counter groups in the array.
    GPA_CounterGroupDesc*             m_pHardwareAdditionalGroups;          ///< Points to the array of internal additional hardware counter groups
    unsigned int                      m_hardwareAdditionalGroupCount;       ///< stores the number of additional hardware counter groups in the array.
    GPA_CounterGroupDesc*             m_pSoftwareGroups;                    ///< Points to the array of internal software counter groups
    unsigned int                      m_softwareGroupCount;                 ///< stores the number of software counter groups in the array.
    unsigned int                      m_groupIndex;                         ///< Stores the group index of the set counter index.
    unsigned int                      m_counterIndex;                       ///< Stores the counter index within the group of the set counter index.
    bool                              m_isHW;                               ///< flag to record if the counter is hardware or not
    bool                              m_isAdditionalHW;                     ///< flag to record if the counter is an additional HW counter (one exposed by the driver but not by GPA)
    bool                              m_isSW;                               ///< flag to record if the counter is SW
};

#endif  // _GPA_COUNTER_GROUP_ACCESSOR_H_
