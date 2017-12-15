//==============================================================================
// Copyright (c) 2016-2017 Advanced Micro Devices, Inc. All rights reserved.
/// \author AMD Developer Tools Team
/// \file
/// \brief  Maintains a set of software counters
//==============================================================================

#ifndef _GPA_SOFTWARE_COUNTERS_H_
#define _GPA_SOFTWARE_COUNTERS_H_

#include "GPAInternalCounter.h"
#include "Logging.h"
#include "GPASwCounterManager.h"
#include <sstream>

/// Struct to describe a software counter
struct GPA_SoftwareCounterDescExt
{
    gpa_uint32               m_groupIndex;        ///< index of group containing this counter
    gpa_uint32               m_groupIdDriver;     ///< group ID according to the driver
    gpa_uint32               m_counterIdDriver;   ///< counter ID according to the driver
    GPA_SoftwareCounterDesc* m_pSoftwareCounter;  ///< the internal counter
};

/// Maintains a set of software counters
class GPA_SoftwareCounters
{
public:
    /// Initializes an instance of the GPA_SoftwareCounters class.
    GPA_SoftwareCounters()
    {
        Clear();
    }

    /// Destructor
    virtual ~GPA_SoftwareCounters()
    {
    }

    /// Clears all counter data
    void Clear()
    {
        m_counters.clear();
        m_ppCounterGroupArray = nullptr;
        m_pGroups = nullptr;
        m_groupCount = 0;
        m_countersGenerated = false;
    }

    /// Obtains the number of software counters
    /// \return the number of software counters
    gpa_uint32 GetNumCounters() const
    {
        return static_cast<gpa_uint32>(m_counters.size());
    }

    /// Gets the name of the specified counter
    /// \param index the index of the counter whose name is needed
    /// \return the name of the specified counter
    const char* GetCounterName(gpa_uint32 index) const
    {
        return m_counters[index].m_pSoftwareCounter->m_name;
    }

    /// Gets the group name of the specified counter
    /// \param index the index of the counter whose group is needed
    /// \return the group name of the specified counter
    const char* GetCounterGroup(gpa_uint32 index) const
    {
        return m_counters[index].m_pSoftwareCounter->m_group;
    }

    /// Gets the description of the specified counter
    /// \param index the index of the counter whose description is needed
    /// \return the description of the specified counter
    const char* GetCounterDescription(gpa_uint32 index) const
    {
        return m_counters[index].m_pSoftwareCounter->m_description;
    }

    /// Gets a counter's UUID
    /// \param index the index of the requested counter
    /// \return the counter's UUID
    GPA_UUID GetCounterUuid(gpa_uint32 index) const
    {
        return ::GetCounterUuid(GetCounterName(index), GetCounterDescription(index));
    }

    /// Gets the type of the specified counter
    /// \param index the index of the counter whose type is needed
    /// \return the type of the specified counter
    GPA_Data_Type GetCounterType(gpa_uint32 index) const
    {
        return m_counters[index].m_pSoftwareCounter->m_type;
    }

    GPA_SoftwareCounterDesc**                   m_ppCounterGroupArray;            ///< List of counter groups as defined by the list of counters in each group.
    GPA_CounterGroupDesc*                       m_pGroups;                        ///< List of internal counter groups
    bool                                        m_countersGenerated;              ///< Indicates that the counters have been generated
    std::vector<GPA_SoftwareCounterDescExt>     m_counters;                       ///< The list of software counters
    unsigned int                                m_groupCount;                     ///< The number of internal counter groups
};

#endif //_GPA_SOFTWARE_COUNTERS_H_
