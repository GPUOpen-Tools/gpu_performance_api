//==============================================================================
// Copyright (c) 2016 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  definitions for internal counters
//==============================================================================

#ifndef _GPA_INTERNAL_COUNTER_H_
#define _GPA_INTERNAL_COUNTER_H_

#include "GPUPerfAPITypes.h"
#include "GPASplitCountersInterfaces.h"

// TODO: This file needs to be split to two header files:
//      The 1st part will declare the GPA_* structs
//      The 2nd part will declare GPACounterGroupAccessor
//      This split requires regenerating all the counter files.

/// macro to remove counter names from public builds
#ifdef AMDT_INTERNAL
    #define GPA_HIDE_NAME(_CounterName) (_CounterName)
#else
    #define GPA_HIDE_NAME(_CounterName) ""
#endif

/// Contains all information pertaining to an hardware counter
struct GPA_HardwareCounterDesc
{
    gpa_uint64 m_counterIndexInGroup;   ///< 0-based index of counter within the group
    char* m_pName;                      ///< name of the counter
    char* m_pDescription;               ///< description of the counter
    GPA_Type m_type;                    ///< data type
    gpa_uint64 m_min;                   ///< min possible value
    gpa_uint64 m_max;                   ///< max possible value
};

/// Contains all information pertaining to an internal counter group (aka a hardware block instance).
struct GPA_CounterGroupDesc
{
    gpa_uint32 m_groupIndex;            ///< 0-based index of the group
    char* m_pName;                      ///< name of the group
    gpa_uint32 m_blockInstance;         ///< 0-based index of this block instance
    gpa_uint32 m_numCounters;           ///< number of counters in the group
    gpa_uint32 m_maxActiveCounters;     ///< number of counters that can be active in this group in a single monitor
};

const int maxSoftwareCounterNameLength = 20;                ///< maximum length for a software counter name
const int maxSoftwareCounterDescriptionLength = 86;         ///< maximum length for a software counter name

/// Contains all information pertaining to an software counter
struct GPA_SoftwareCounterDesc
{
    gpa_uint64 m_counterIndexInGroup;                         ///< 0-based index of counter within the group
    char m_name[maxSoftwareCounterNameLength];                ///< name of the counter
    char m_description[maxSoftwareCounterDescriptionLength];  ///< description of the counter
    GPA_Type m_type;                                          ///< data type
};

/// Indexes into an array of internal groups and counters and can access data from the internal counter.
class GPACounterGroupAccessor : IGPACounterAccessor
{
public:

    /// Initializes a new instance of the GPACounterGroupAccessor class.
    GPACounterGroupAccessor(GPA_CounterGroupDesc* pHardwareGroups,
                            unsigned int hardwareGroupCount,
                            GPA_CounterGroupDesc* pHardwareAdditionalGroups,
                            unsigned int hardwareAdditionalGroupCount,
                            GPA_CounterGroupDesc* pSoftwareGroups,
                            unsigned int softwareGroupCount)
        : m_pHardwareGroups(pHardwareGroups),
          m_hardwareGroupCount(hardwareGroupCount),
          m_pHardwareAdditionalGroups(pHardwareAdditionalGroups),
          m_hardwareAdditionalGroupCount(hardwareAdditionalGroupCount),
          m_pSoftwareGroups(pSoftwareGroups),
          m_softwareGroupCount(softwareGroupCount),
          m_groupIndex(0),
          m_counterIndex(0)
    {
    };

    /// Destructor
    virtual ~GPACounterGroupAccessor() {};

    /// Sets the counter index of which to get the group and counter Id.
    /// \param index The counter index.
    void SetCounterIndex(unsigned int index)
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
            internalCounters += (unsigned int)m_pHardwareGroups[i].m_numCounters;
        }

        for (unsigned int i = 0; i < m_hardwareGroupCount; ++i)
        {
            tmpSum = prevGroupCounters + (unsigned int)m_pHardwareGroups[i].m_numCounters;

            if (tmpSum > index)
            {
                // this group contains the desired counter index.
                // this is the right group, and we can calculate the right counter.
                this->m_groupIndex = i;
                this->m_counterIndex = index - prevGroupCounters;

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
            tmpSum = prevGroupCounters + (unsigned int)m_pHardwareAdditionalGroups[i].m_numCounters;

            if (tmpSum > index)
            {
                // this group contains the desired counter index.
                // this is the right group, and we can calculate the right counter.
                this->m_groupIndex = i;
                this->m_counterIndex = index - prevGroupCounters;

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

#if defined(WIN32)

        this->m_groupIndex = 0;
        m_isSW = true;

        if (index >= internalCounters)
        {
            this->m_counterIndex = index - internalCounters;
        }
        else
        {
            this->m_counterIndex = index;
        }

        return;

#endif // WIN32

    }

    /// Get the 0-based group index of the internal counter.
    /// \return The group index.
    virtual unsigned int GroupIndex() const
    {
        return this->m_groupIndex;
    };

    /// Get the 0-based counter index of the internal counter.
    /// \return The counter index.
    virtual unsigned int CounterIndex() const
    {
        return this->m_counterIndex;
    };

    /// Get the hardware counter bool
    /// \return True if the counter is a hardware counter
    bool IsHWCounter() const
    {
        return m_isHW;
    }

    /// Get the additional hardware counter bool
    /// \return True if the counter is an additional hardware counter (one exposed by the driver, but not by GPA)
    bool IsAdditionalHWCounter() const
    {
        return m_isAdditionalHW;
    }

    /// Get the software counter bool
    /// \return True if the counter is a software counter
    bool IsSWCounter() const
    {
        return m_isSW;
    }

    /// Get the global group group index (the full index of the software groups that come after the hardware groups)
    /// \return The total number of groups
    unsigned int GlobalGroupIndex() const
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

private:

    /// Points to the array of internal counter groups
    GPA_CounterGroupDesc* m_pHardwareGroups;

    /// stores the number of groups in the array.
    unsigned int m_hardwareGroupCount;


    /// Points to the array of internal counter groups
    GPA_CounterGroupDesc* m_pHardwareAdditionalGroups;

    /// stores the number of groups in the array.
    unsigned int m_hardwareAdditionalGroupCount;

    /// Points to the array of internal counter groups
    GPA_CounterGroupDesc* m_pSoftwareGroups;

    /// stores the number of groups in the array.
    unsigned int m_softwareGroupCount;

    /// Stores the group index of the set counter index.
    unsigned int m_groupIndex;

    /// Stores the counter index within the group of the set counter index.
    unsigned int m_counterIndex;

    /// bool to record if the counter is HW
    bool m_isHW;

    /// bool to record if the counter is an additional HW counter (one exposed by the driver but not by GPA)
    bool m_isAdditionalHW;

    /// bool to record if the counter is SW
    bool m_isSW;
};

#endif //_GPA_INTERNAL_COUNTER_H_
